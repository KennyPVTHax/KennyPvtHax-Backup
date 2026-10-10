#pragma once
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <string>
#include <fcntl.h>
#include <unistd.h>
#include "KennyThemePreferences.h"

namespace KennyAppearance {
// The native activity supplies its app-private directory. No hardcoded package,
// external storage, new Android permission, or feature persistence is involved.
struct Store {
    std::string path, temporary;
    Preferences observed;
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
        const int fd=open(path.c_str(),O_RDONLY|O_CLOEXEC|O_NOFOLLOW);
        if(fd>=0) {
            char text[1024]{};
            const ssize_t length=read(fd,text,sizeof(text)-1);
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
        // Unique 0600 staging survives stale files from an interrupted save.
        char staging[1024];
        if(temporary.size()>=sizeof(staging)) return false;
        std::memcpy(staging,temporary.c_str(),temporary.size()+1);
        const int fd=mkstemp(staging);
        if(fd<0) return false;
        fcntl(fd,F_SETFD,FD_CLOEXEC);
        const bool written=write(fd,text,length)==length && fsync(fd)==0;
        const bool closed=close(fd)==0;
        const bool renamed=written && closed && rename(staging,path.c_str())==0;
        if(!renamed) unlink(staging);
        return renamed;
    }
    void Sync(Preferences& p, bool finished) {
        Normalize(p);
        if(!available || !finished || Equal(p,observed)) return;
        status=Save(p) ? "Appearance saved on this device." :
            "Could not save appearance; changes remain active for this session.";
        observed=p; // A failed write is reported, never retried every frame.
    }
};
} // namespace KennyAppearance
