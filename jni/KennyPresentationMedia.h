#pragma once
#include "KennyCharacters.h"
#include <chrono>
#include "KennyEmbeddedVideoCache.h"

namespace KennyPresentation {
constexpr size_t VideoLimit=64u*1024u*1024u;
// Fixed filenames, app-owned directory and descriptor-relative opens. No network,
// arbitrary paths, runtime JPEG dependency or character-registry replacements.
inline int Directory(const char* privatePath){
    if(!privatePath||!*privatePath)return -1;
    int fd=open(privatePath,O_RDONLY|O_DIRECTORY|O_NOFOLLOW|O_CLOEXEC);if(fd<0)return -1;
    for(const char* part:{"assets","presentation"}){int next=openat(fd,part,O_RDONLY|O_DIRECTORY|O_NOFOLLOW|O_CLOEXEC);close(fd);fd=next;if(fd<0)return -1;}
    return fd;
}
inline int VideoFile(int root){
    if(root<0)return -1;
    int fd=openat(root,"anime-background.mp4",O_RDONLY|O_NONBLOCK|O_NOFOLLOW|O_CLOEXEC);if(fd<0)return -1;
    struct stat st{};uint8_t header[12]{};
    if(fstat(fd,&st)||!S_ISREG(st.st_mode)||st.st_size<12||uint64_t(st.st_size)>VideoLimit||pread(fd,header,12,0)!=12||std::memcmp(header+4,"ftyp",4)){close(fd);return -1;}
    return fd;
}
struct Assets {
    KennyAssets::Image logo,poster;
    KennyThemeBackground::ArtworkFrame logoTexture,posterTexture;
    KennyCharacters::Upload upload=nullptr;KennyCharacters::Release release=nullptr;
    bool configured=false,logoAttempted=false,posterAttempted=false;
    int video=-1,root=-1;bool posterLoaded=false;
    const char* status="Presentation media not configured.";
    bool embedded=false;std::string privatePath;
#ifdef KPH_EMBEDDED_MEDIA
    KennyEmbedded::VideoCache cache;
#endif
    bool Read(const char* file,size_t limit,std::vector<uint8_t>& bytes){
        return embedded?KennyEmbedded::Read((std::string("assets/presentation/")+file).c_str(),limit,bytes):KennyAssets::Read(root,file,limit,bytes);
    }
    ~Assets(){if(video>=0)close(video);if(root>=0)close(root);}
    void Configure(const char* directory){
        if(configured){if(privatePath.empty()&&directory)privatePath=directory;return;}
        embedded=KennyEmbedded::Lookup("assets/presentation/manifest.json")!=nullptr;
        if(!embedded&&!directory)return;
        configured=true;if(directory)privatePath=directory;root=embedded?-2:Directory(directory);
        if(root<0&&!embedded){status="Private video/logo pack missing. Install into the owning host and restart.";return;}
        std::vector<uint8_t> bytes;nlohmann::json manifest;
        bool valid=Read("manifest.json",32768,bytes)&&KennyCharacters::Registry::JSON(bytes,manifest)&&manifest.is_object();
        if(valid){auto schema=manifest.find("schema");valid=schema!=manifest.end()&&schema->is_number_integer()&&*schema==1&&
            KennyCharacters::Registry::Text(manifest,"logo")=="launcher.png"&&KennyCharacters::Registry::Text(manifest,"video")=="anime-background.mp4"&&KennyCharacters::Registry::Text(manifest,"fallback")=="anime-fallback.png";}
        if(!valid){close(root);root=-1;status="Presentation manifest missing or invalid; safe fallback active.";return;}
        if(Read("launcher.png",8u*1024u*1024u,bytes))KennyAssets::PNG(bytes,logo,false);
        video=embedded?-1:VideoFile(root);
        if(embedded){status="Embedded media ready; video cache initializes when Anime is visible.";return;}
        status=video>=0?"Private video pack found; playback initializes only in visible Anime mode.":"Video missing or invalid; using a still fallback when available.";
    }
    void Prepare(bool background=true){
        #ifdef KPH_EMBEDDED_MEDIA
        if(embedded&&background){cache.Start(privatePath.c_str());if(video<0)video=cache.Take();
            status=video>=0?"Embedded video cache verified; decoder ready.":cache.done.load()?"Embedded movie cache unavailable; still fallback active.":"Preparing verified embedded movie cache; still fallback active.";}
#endif
        if(!upload)return;
        if(!logoAttempted){logoAttempted=true;if(!logo.rgba.empty())logoTexture=upload(nullptr,logo);}
        if(background&&!posterLoaded){posterLoaded=true;std::vector<uint8_t> bytes;
            if(Read("anime-fallback.png",8u*1024u*1024u,bytes))KennyAssets::PNG(bytes,poster,false);
        }
        if(background&&!posterAttempted){posterAttempted=true;if(!poster.rgba.empty())posterTexture=upload(nullptr,poster);}
    }
    void ClearTextures(bool lost){
        if(!lost&&release){if(logoTexture.Valid())release(nullptr,logoTexture);if(posterTexture.Valid())release(nullptr,posterTexture);}
        logoTexture={};posterTexture={};logoAttempted=posterAttempted=false;
    }
};
// Decoder pacing resumes from the next actual presentation timestamp, not from
// hidden elapsed time. This is also exercised by portable host tests.
struct Clock {
    int64_t first=-1;
    std::chrono::steady_clock::time_point anchor;
    void Pause(){first=-1;}
    std::chrono::steady_clock::time_point Due(int64_t pts,std::chrono::steady_clock::time_point now){
        if(first<0||pts<first){first=pts;anchor=now;}
        const int64_t delta=std::clamp<int64_t>(pts-first,0,60000000);
        return anchor+std::chrono::microseconds(delta);
    }
};
} // namespace KennyPresentation
