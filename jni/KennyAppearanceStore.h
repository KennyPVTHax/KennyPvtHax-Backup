#pragma once
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctime>
#include "KennyThemePreferences.h"

namespace KennyAppearance {
// The native activity supplies its app-private directory. No hardcoded package,
// external storage, new Android permission, or feature persistence is involved.
struct Store {
    std::string path, temporary;
    Preferences observed, attempted;
    bool retryPending=false;
    unsigned failures=0;
    double retryAt=0;
    static double Clock(){timespec now{};return clock_gettime(CLOCK_MONOTONIC,&now)==0 ? now.tv_sec+now.tv_nsec*1e-9 : 0;}
    bool configured = false, available = false;
    const char* status = "Appearance storage unavailable; changes last for this session.";

    void Configure(const char* directory, Preferences& p) {
        if(configured) return;
        configured=true;
        if(!directory || !*directory) { observed=p; return; }
        path=std::string(directory)+"/kennypvthax-appearance-v1.conf";
        temporary=path+".tmp-XXXXXX";
        available=true;
        status="Appearance saves automatically when you finish an adjustment.";
        const int fd=open(path.c_str(),O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_NOFOLLOW);
        if(fd>=0) {
            char text[1024]{};
            struct stat info{};
            ssize_t length=-1;
            if(fstat(fd,&info)==0 && S_ISREG(info.st_mode) && info.st_size>0 && info.st_size<ssize_t(sizeof(text)-1)){
                size_t n=0;bool ok=true;
                while(n<size_t(info.st_size)){
                    const ssize_t done=read(fd,text+n,size_t(info.st_size)-n);
                    if(done<0&&errno==EINTR)continue;
                    if(done<=0){ok=false;break;}n+=size_t(done);
                }
                char extra;ssize_t more;
                do{more=read(fd,&extra,1);}while(more<0&&errno==EINTR);
                if(ok&&more==0)length=ssize_t(n);
            }
            close(fd);
            int theme=0,compact=0,reduced=0,stars=0,touch=0,cover=0,consumed=0,version=0,sounds=1,profile=0;
            Preferences loaded;
            const int fields=length>0 && length<ssize_t(sizeof(text)-1) ? std::sscanf(text,
                "KennyPvtHaxAppearance %d\n%d %f %d %d %f %f %d %d %f %d %n",
                &version,&theme,&loaded.opacity,&compact,&reduced,&loaded.auroraIntensity,
                &loaded.particleActivity,&stars,&touch,&loaded.artworkDim,&cover,&consumed) : 0;
            int audioConsumed=0;
            const bool audioValid=version==1 ? consumed==length : (version==2 || version==3) &&
                std::sscanf(text+consumed,"%d %f %d %n",&sounds,&loaded.uiVolume,&profile,&audioConsumed)==3 &&
                (version==3 || consumed+audioConsumed==length) && sounds>=0 && sounds<=1 && profile>=0 && profile<=2 && std::isfinite(loaded.uiVolume);
            if(fields==11 && audioValid && theme>=0 && theme<=2 &&
                compact>=0 && compact<=1 && reduced>=0 && reduced<=1 && stars>=0 && stars<=1 &&
                touch>=0 && touch<=1 && cover>=0 && cover<=1 &&
                std::isfinite(loaded.opacity) && std::isfinite(loaded.auroraIntensity) &&
                std::isfinite(loaded.particleActivity) && std::isfinite(loaded.artworkDim)) {
                loaded.theme=static_cast<Theme>(theme);loaded.compactRows=compact;loaded.reducedMotion=reduced;
                loaded.starsVisible=stars;loaded.touchAttraction=touch;loaded.artworkCover=cover;
                loaded.uiSounds=sounds;loaded.soundProfile=profile;
                if(version==3){
                    char character[64]{},pack[64]{},artwork[64]{};int enabled=1,launcher=1,end=0;float voiceVolume=70;
                    int fields3=std::sscanf(text+consumed+audioConsumed,"%63s %63s %63s %d %f %d %n",character,pack,artwork,&enabled,&voiceVolume,&launcher,&end);
                    if(fields3==6 && consumed+audioConsumed+end==length && enabled>=0 && enabled<=1 && launcher>=0 && launcher<=1 && std::isfinite(voiceVolume)){
                        loaded.characterId=character;loaded.voicePack=pack;loaded.characterArtwork=artwork;
                        loaded.characterVoice=enabled;loaded.characterVolume=voiceVolume;loaded.characterLauncher=launcher;
                    }else status="Anime preferences were invalid; existing appearance/audio preferences retained.";
                }
                Normalize(loaded);p=loaded;
            } else status="Saved appearance was invalid; using defaults. Change a preference to replace it.";
        } else if(errno!=ENOENT) status="Could not read saved appearance; using session preferences.";
        observed=p;
    }
    bool Save(const Preferences& p) {
        char text[512];
        const int length=std::snprintf(text,sizeof(text),
            "KennyPvtHaxAppearance 3\n%d %.9g %d %d %.9g %.9g %d %d %.9g %d\n%d %.9g %d\n%s %s %s %d %.9g %d\n",
            static_cast<int>(p.theme),p.opacity,p.compactRows,p.reducedMotion,p.auroraIntensity,
            p.particleActivity,p.starsVisible,p.touchAttraction,p.artworkDim,p.artworkCover,
            p.uiSounds,p.uiVolume,p.soundProfile,p.characterId.c_str(),p.voicePack.c_str(),p.characterArtwork.c_str(),p.characterVoice,p.characterVolume,p.characterLauncher);
        if(length<=0 || size_t(length)>=sizeof(text))return false;
        // Unique 0600 staging survives stale files from an interrupted save.
        char staging[1024];
        if(temporary.size()>=sizeof(staging)) return false;
        std::memcpy(staging,temporary.c_str(),temporary.size()+1);
        const int fd=mkstemp(staging);
        if(fd<0) return false;
        fcntl(fd,F_SETFD,FD_CLOEXEC);
        size_t n=0;bool written=true;
        while(n<size_t(length)){
            const ssize_t done=write(fd,text+n,size_t(length)-n);
            if(done<0&&errno==EINTR)continue;
            if(done<=0){written=false;break;}n+=size_t(done);
        }
        int synced=-1;
        if(written){do{synced=fsync(fd);}while(synced<0&&errno==EINTR);}
        written=written&&synced==0;
        const bool closed=close(fd)==0;
        const bool renamed=written && closed && rename(staging,path.c_str())==0;
        if(!renamed) unlink(staging);
        if(!renamed)return false;
        const auto slash=path.rfind('/');if(slash==std::string::npos)return false;
        const std::string parent=path.substr(0,slash);
        const int directory=open(parent.c_str(),O_RDONLY|O_DIRECTORY|O_NOFOLLOW|O_CLOEXEC);
        if(directory<0)return false;
        do{synced=fsync(directory);}while(synced<0&&errno==EINTR);
        close(directory);return synced==0;
    }
    void Sync(Preferences& p, bool finished, double now=Clock()) {
        Normalize(p);
        if(!available || !finished)return;
        if(Equal(p,observed)){retryPending=false;failures=0;return;}
        if(retryPending && Equal(p,attempted) && now<retryAt)return;
        attempted=p;
        if(Save(p)){
            observed=p;retryPending=false;failures=0;
            status="Appearance saved on this device.";
        }else{
            retryPending=true;failures=std::min(failures+1,6u);
            retryAt=now+double(1u<<(failures-1));
            status="Appearance save/durability failed; session state retained, retry scheduled.";
        }
    }
};
} // namespace KennyAppearance
