#pragma once
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>
#include <cmath>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <zlib.h>

namespace KennyAssets {
inline bool Token(const std::string& s){if(s.empty() || s.size()>63)return false;
for(char c:s)if(!((c>='a'&&c<='z')||(c>='0'&&c<='9')||c=='_'||c=='-'))return false;
return true;}
inline bool Path(const std::string& s){
    if(s.empty() || s.size()>160 || s.front()=='/' || s.back()=='/')return false;
    unsigned depth=0;size_t start=0;
    for(size_t i=0;i<=s.size();++i)if(i==s.size() || s[i]=='/'){
        if(++depth>4 || i==start || s[start]=='.')return false;
        for(size_t j=start;j<i;++j){char c=s[j];if(!((c>='a'&&c<='z')||(c>='0'&&c<='9')||c=='_'||c=='-'||c=='.'))return false;}
        start=i+1;
    }return true;
}
inline bool Read(int directory,const std::string& path,size_t limit,std::vector<uint8_t>& out){
    out.clear();if(directory<0 || !Path(path))return false;
    int fd=dup(directory);if(fd<0)return false;
    size_t start=0;
    while(true){const size_t slash=path.find('/',start);const auto part=path.substr(start,slash==std::string::npos?slash:slash-start);
        const int next=openat(fd,part.c_str(),O_RDONLY|O_NONBLOCK|O_CLOEXEC|O_NOFOLLOW|(slash==std::string::npos?0:O_DIRECTORY));close(fd);fd=next;
        if(fd<0)return false;
        if(slash==std::string::npos)break;
        start=slash+1;
    }
    struct stat st{};bool ok=fstat(fd,&st)==0 && S_ISREG(st.st_mode) && st.st_size>0 && size_t(st.st_size)<=limit;
    if(ok){out.resize(size_t(st.st_size));size_t readBytes=0;while(readBytes<out.size()){ssize_t n=read(fd,out.data()+readBytes,out.size()-readBytes);if(n<=0){ok=false;break;}readBytes+=size_t(n);}uint8_t extra;if(ok && read(fd,&extra,1)!=0)ok=false;}
    close(fd);if(!ok)out.clear();return ok;
}
inline uint32_t BE(const uint8_t* p){return uint32_t(p[0])<<24|uint32_t(p[1])<<16|uint32_t(p[2])<<8|p[3];}
inline uint32_t LE(const uint8_t* p){return uint32_t(p[0])|uint32_t(p[1])<<8|uint32_t(p[2])<<16|uint32_t(p[3])<<24;}
inline unsigned LE16(const uint8_t* p){return unsigned(p[0])|unsigned(p[1])<<8;}
struct Image {unsigned width=0,height=0;std::vector<uint8_t> rgba;bool transparent=false;};
// Deliberately narrow PNG support: non-interlaced 8-bit RGBA. Original alpha
// remains straight/unpremultiplied; no matte/background is added.
inline bool PNG(const std::vector<uint8_t>& input,Image& image){
    image={};constexpr size_t MaxPixels=2097152;
    const uint8_t signature[]={137,80,78,71,13,10,26,10};
    if(input.size()<57 || input.size()>8*1024*1024 || std::memcmp(input.data(),signature,8))return false;
    unsigned w=0,h=0;bool header=false,end=false,data=false,closedData=false;
    std::vector<uint8_t> compressed;
    for(size_t p=8;p<input.size();){
        if(input.size()-p<12)return false;
        const size_t n=BE(&input[p]);if(n>input.size()-p-12)return false;
        const uint8_t* type=&input[p+4];const uint8_t* chunk=&input[p+8];
        if(crc32(0,type,uInt(n+4))!=BE(chunk+n))return false;
        if(!std::memcmp(type,"IHDR",4)){
            if(header || p!=8 || n!=13)return false;
            w=BE(chunk);h=BE(chunk+4);
            if(!w||!h||w>4096||h>4096||size_t(w)*h>MaxPixels||chunk[8]!=8||chunk[9]!=6||chunk[10]||chunk[11]||chunk[12])return false;
            header=true;
        }else if(!header)return false;
        else if(!std::memcmp(type,"IDAT",4)){if(closedData || !n)return false;
        data=true;compressed.insert(compressed.end(),chunk,chunk+n);}
        else if(!std::memcmp(type,"IEND",4)){if(n || !data || p+12!=input.size())return false;
        end=true;break;}
        else {if(data)closedData=true;if(!(type[0]&32))return false;}
        p+=n+12;
    }
    if(!end)return false;
    const size_t stride=size_t(w)*4;uLongf length=(stride+1)*h;
    std::vector<uint8_t> raw(length);z_stream stream{};stream.next_in=compressed.data();stream.avail_in=uInt(compressed.size());
    stream.next_out=raw.data();stream.avail_out=uInt(raw.size());
    if(inflateInit(&stream)!=Z_OK)return false;
    const int result=inflate(&stream,Z_FINISH);const bool valid=result==Z_STREAM_END && stream.total_out==raw.size() && stream.total_in==compressed.size();
    inflateEnd(&stream);if(!valid)return false;
    image.rgba.resize(stride*h);
    for(unsigned y=0;y<h;++y){const uint8_t filter=raw[y*(stride+1)];if(filter>4){image={};return false;}
        for(size_t x=0;x<stride;++x){int a=x>=4?image.rgba[y*stride+x-4]:0,b=y?image.rgba[(y-1)*stride+x]:0,c=y&&x>=4?image.rgba[(y-1)*stride+x-4]:0,v=0;
            if(filter==1)v=a;else if(filter==2)v=b;else if(filter==3)v=(a+b)/2;else if(filter==4){int p=a+b-c,pa=std::abs(p-a),pb=std::abs(p-b),pc=std::abs(p-c);v=pa<=pb&&pa<=pc?a:pb<=pc?b:c;}
            image.rgba[y*stride+x]=uint8_t(raw[y*(stride+1)+1+x]+v);
        }
    }
    bool visible=false;for(size_t i=3;i<image.rgba.size();i+=4){visible|=image.rgba[i]>0;image.transparent|=image.rgba[i]<255;}
    if(!visible || !image.transparent){image={};return false;}image.width=w;image.height=h;return true;
}
inline bool WAV(const std::vector<uint8_t>& input,std::vector<int16_t>& output){
    output.clear();if(input.size()<44 || input.size()>1048576 || std::memcmp(input.data(),"RIFF",4)||std::memcmp(input.data()+8,"WAVE",4)||LE(input.data()+4)!=input.size()-8)return false;
    unsigned rate=0,channels=0;const uint8_t* samples=nullptr;size_t bytes=0;bool fmt=false;
    for(size_t p=12;p<input.size();){if(input.size()-p<8)return false;
    size_t n=LE(input.data()+p+4);if(n>input.size()-p-8)return false;
        const auto* chunk=input.data()+p+8;
        if(!std::memcmp(input.data()+p,"fmt ",4)){
            if(fmt||n<16||LE16(chunk)!=1)return false;
            channels=LE16(chunk+2);rate=LE(chunk+4);
            if((channels!=1&&channels!=2)||rate<8000||rate>48000||LE16(chunk+14)!=16||LE16(chunk+12)!=channels*2||LE(chunk+8)!=rate*channels*2)return false;
            fmt=true;
        }else if(!std::memcmp(input.data()+p,"data",4)){if(samples)return false;
        samples=chunk;bytes=n;}
        p+=8+n+(n&1);if(p>input.size())return false;
    }
    if(!fmt||!samples||!bytes||bytes%(channels*2))return false;
    size_t frames=bytes/(channels*2);
    if(frames<rate/100 || frames>rate*4)return false;
    const size_t count=frames*48000/rate;output.resize(count);
    auto sample=[&](size_t frame){float v=int16_t(LE16(samples+frame*channels*2));if(channels==2)v=(v+int16_t(LE16(samples+frame*4+2)))*.5f;return v;};
    for(size_t i=0;i<count;++i){double pos=double(i)*rate/48000;size_t a=std::min(size_t(pos),frames-1),b=std::min(a+1,frames-1);output[i]=int16_t(sample(a)+(sample(b)-sample(a))*(pos-a));}
    return true;
}
} // namespace KennyAssets
