#pragma once
#include "KennyEmbeddedMedia.h"
#ifdef KPH_EMBEDDED_MEDIA
#include <openssl/sha.h>
#include <atomic>
#include <thread>
#include <string>
#include <array>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <cerrno>
#include <chrono>
#include <algorithm>
#include <system_error>
namespace KennyEmbedded {
// API 21 MediaExtractor needs an FD. Only the movie is extracted, on a bounded
// worker, to an app-owned cache. Images/voices continue to decode from memory.
struct VideoCache {
    std::thread worker;std::atomic<bool> done{false},cancel{false};
    std::atomic<int> result{-1};bool started=false;std::string directory;
    ~VideoCache(){cancel.store(true);if(worker.joinable())worker.join();int fd=result.exchange(-1);if(fd>=0)close(fd);}
    static bool Matches(int fd,const Entry& e){
        struct stat st{};if(fstat(fd,&st)||!S_ISREG(st.st_mode)||uint64_t(st.st_size)!=e.size)return false;
        SHA256_CTX hash;SHA256_Init(&hash);std::array<uint8_t,65536> buffer{};size_t offset=0;
        while(offset<e.size){ssize_t got=pread(fd,buffer.data(),std::min(buffer.size(),e.size-offset),offset);if(got<0&&errno==EINTR)continue;if(got<=0)return false;SHA256_Update(&hash,buffer.data(),got);offset+=got;}
        unsigned char digest[32];SHA256_Final(digest,&hash);char hex[65];constexpr char digits[]="0123456789abcdef";
        for(int i=0;i<32;++i){hex[2*i]=digits[digest[i]>>4];hex[2*i+1]=digits[digest[i]&15];}hex[64]=0;return std::strcmp(hex,e.sha256)==0;
    }
    void Start(const char* path){
        if(started||!path||!*path)return;started=true;directory=path;
        const Entry* e=Lookup("assets/presentation/anime-background.mp4");
        if(!e||e->size<12||e->size>64u*1024u*1024u||std::memcmp(e->data+4,"ftyp",4)){done.store(true);return;}
        try{worker=std::thread([this,e]{
            int base=open(directory.c_str(),O_RDONLY|O_DIRECTORY|O_NOFOLLOW|O_CLOEXEC);
            if(base<0){done.store(true);return;}
            if(mkdirat(base,"kenny-media-cache",0700)&&errno!=EEXIST){close(base);done.store(true);return;}
            int root=openat(base,"kenny-media-cache",O_RDONLY|O_DIRECTORY|O_NOFOLLOW|O_CLOEXEC);close(base);
            if(root<0){done.store(true);return;}
            std::string name=std::string(e->sha256)+".mp4";
            int existing=openat(root,name.c_str(),O_RDONLY|O_NONBLOCK|O_NOFOLLOW|O_CLOEXEC);
            if(existing>=0&&Matches(existing,*e)){result.store(existing);close(root);done.store(true);return;}
            if(existing>=0)close(existing);
            // Each process owns its temp file; interrupted old temps never become
            // valid cache entries. Do not touch unrelated app files or reports.
            std::string temporary=name+"."+std::to_string(getpid())+"."+std::to_string(std::chrono::steady_clock::now().time_since_epoch().count())+".tmp";
            int fd=openat(root,temporary.c_str(),O_RDWR|O_CREAT|O_EXCL|O_NOFOLLOW|O_CLOEXEC,0600);
            if(fd<0){close(root);done.store(true);return;}
            size_t offset=0;bool okay=true;
            while(offset<e->size&&!cancel.load()){
                ssize_t n=write(fd,e->data+offset,std::min(size_t(65536),e->size-offset));
                if(n<0&&errno==EINTR)continue;if(n<=0){okay=false;break;}offset+=n;
            }
            okay=okay&&!cancel.load()&&offset==e->size&&fsync(fd)==0&&Matches(fd,*e);
            if(okay)okay=renameat(root,temporary.c_str(),root,name.c_str())==0;
            if(okay){fsync(root);close(fd);fd=openat(root,name.c_str(),O_RDONLY|O_NOFOLLOW|O_CLOEXEC);if(fd>=0&&!Matches(fd,*e)){close(fd);fd=-1;}result.store(fd);}
            else{close(fd);unlinkat(root,temporary.c_str(),0);}
            close(root);done.store(true);
        });}catch(const std::system_error&){done.store(true);}
    }
    int Take(){if(!done.load())return -1;if(worker.joinable())worker.join();return result.exchange(-1);}
};
}
#endif
