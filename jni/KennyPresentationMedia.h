#pragma once
#include "KennyCharacters.h"
#include <chrono>

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
    ~Assets(){if(video>=0)close(video);if(root>=0)close(root);}
    void Configure(const char* directory){
        if(configured||!directory)return;
        configured=true;root=Directory(directory);
        if(root<0){status="Private video/logo pack missing. Install into the owning host and restart.";return;}
        std::vector<uint8_t> bytes;nlohmann::json manifest;
        bool valid=KennyAssets::Read(root,"manifest.json",32768,bytes)&&KennyCharacters::Registry::JSON(bytes,manifest)&&manifest.is_object();
        if(valid){auto schema=manifest.find("schema");valid=schema!=manifest.end()&&schema->is_number_integer()&&*schema==1&&
            KennyCharacters::Registry::Text(manifest,"logo")=="launcher.png"&&KennyCharacters::Registry::Text(manifest,"video")=="anime-background.mp4"&&KennyCharacters::Registry::Text(manifest,"fallback")=="anime-fallback.png";}
        if(!valid){close(root);root=-1;status="Presentation manifest missing or invalid; safe fallback active.";return;}
        if(KennyAssets::Read(root,"launcher.png",8u*1024u*1024u,bytes))KennyAssets::PNG(bytes,logo,false);
        video=VideoFile(root);
        status=video>=0?"Private video pack found; playback initializes only in visible Anime mode.":"Video missing or invalid; using a still fallback when available.";
    }
    void Prepare(bool background=true){
        if(!upload)return;
        if(!logoAttempted){logoAttempted=true;if(!logo.rgba.empty())logoTexture=upload(nullptr,logo);}
        if(background&&!posterLoaded){posterLoaded=true;std::vector<uint8_t> bytes;
            if(KennyAssets::Read(root,"anime-fallback.png",8u*1024u*1024u,bytes))KennyAssets::PNG(bytes,poster,false);
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
