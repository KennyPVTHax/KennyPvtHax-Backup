// CPU rasterization of actual ImGui indexed draw data and original font atlas.
// Emits RGBA for PNG/video packaging. No UI simulation or generated artwork.
#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <string>
#include <vector>
#include <map>
struct Vertex { float x,y,u,v; std::uint32_t color; };
template<typename T> T Read(std::ifstream& f) {T value{};f.read(reinterpret_cast<char*>(&value),sizeof(T));assert(f.good());return value;}
int main(int argc,char** argv) {
    assert(argc>=3);std::ifstream atlas(argv[1],std::ios::binary);
    const int tw=Read<int>(atlas),th=Read<int>(atlas);assert(tw>0 && th>0);
    std::vector<unsigned char> texture(tw*th*4);atlas.read(reinterpret_cast<char*>(texture.data()),texture.size());assert(atlas.good());
    for(int file=2;file<argc;++file) {
        std::ifstream input(argv[file],std::ios::binary);
        const int encodedWidth=Read<int>(input),h=Read<int>(input),lists=Read<int>(input);const bool multi=encodedWidth<0;const int w=std::abs(encodedWidth);assert(w>0 && h>0 && lists>=0);
        struct Texture {int width=0,height=0;std::vector<unsigned char> rgba;};std::map<uint64_t,Texture> textures;
        if(multi){unsigned count=Read<unsigned>(input);assert(count<=8);while(count--){auto id=Read<uint64_t>(input);Texture t;t.width=Read<int>(input);t.height=Read<int>(input);assert(t.width>0&&t.height>0&&size_t(t.width)*t.height<=2097152);t.rgba.resize(size_t(t.width)*t.height*4);input.read((char*)t.rgba.data(),t.rgba.size());assert(input.good());textures.emplace(id,std::move(t));}}
        std::vector<std::array<float,4>> pixels(w*h,{.10f,.115f,.15f,1});
        unsigned triangles=0;
        for(int list=0;list<lists;++list) {
            const int vc=Read<int>(input),ic=Read<int>(input),cc=Read<int>(input);
            std::vector<Vertex> vertices(vc);std::vector<std::uint16_t> indices(ic);
            static_assert(sizeof(Vertex)==20,"native draw-data layout");
            input.read(reinterpret_cast<char*>(vertices.data()),vc*sizeof(Vertex));
            input.read(reinterpret_cast<char*>(indices.data()),ic*sizeof(std::uint16_t));assert(input.good());
            for(int cmd=0;cmd<cc;++cmd) {
                std::array<float,4> clip{};for(auto& c:clip)c=Read<float>(input);
                const unsigned ec=Read<unsigned>(input),offset=Read<unsigned>(input),base=Read<unsigned>(input);
                assert(offset+ec<=indices.size() && ec%3==0);
                const uint64_t textureId=multi?Read<uint64_t>(input):0;
                const auto found=textures.find(textureId);
                const int aw=found==textures.end()?tw:found->second.width,ah=found==textures.end()?th:found->second.height;
                const auto& sourceTexture=found==textures.end()?texture:found->second.rgba;
                for(unsigned i=0;i<ec;i+=3) {
                    const Vertex a=vertices.at(indices[offset+i]+base),b=vertices.at(indices[offset+i+1]+base),c=vertices.at(indices[offset+i+2]+base);
                    const int x0=static_cast<int>(std::max(std::floor(std::min({a.x,b.x,c.x})),std::max(0.0f,clip[0])));
                    const int y0=static_cast<int>(std::max(std::floor(std::min({a.y,b.y,c.y})),std::max(0.0f,clip[1])));
                    const int x1=static_cast<int>(std::min(std::ceil(std::max({a.x,b.x,c.x})),std::min(float(w),clip[2])));
                    const int y1=static_cast<int>(std::min(std::ceil(std::max({a.y,b.y,c.y})),std::min(float(h),clip[3])));
                    const float den=(b.y-c.y)*(a.x-c.x)+(c.x-b.x)*(a.y-c.y);
                    if(std::abs(den)<1e-6f || x0>=x1 || y0>=y1) continue;
                    std::array<float,4> ca{},cb{},ccol{};
                    for(int k=0;k<4;++k){ca[k]=((a.color>>(k*8))&255)/255.0f;cb[k]=((b.color>>(k*8))&255)/255.0f;ccol[k]=((c.color>>(k*8))&255)/255.0f;}
                    for(int y=y0;y<y1;++y) for(int x=x0;x<x1;++x) {
                        const float px=x+.5f,py=y+.5f;
                        const float wa=((b.y-c.y)*(px-c.x)+(c.x-b.x)*(py-c.y))/den;
                        const float wb=((c.y-a.y)*(px-c.x)+(a.x-c.x)*(py-c.y))/den,wc=1-wa-wb;
                        if(wa < -1e-5f || wb < -1e-5f || wc < -1e-5f) continue;
                        const float tx=std::clamp((wa*a.u+wb*b.u+wc*c.u)*aw-.5f,0.0f,float(aw-1));
                        const float ty=std::clamp((wa*a.v+wb*b.v+wc*c.v)*ah-.5f,0.0f,float(ah-1));
                        const int lx=static_cast<int>(tx),ly=static_cast<int>(ty),hx=std::min(lx+1,aw-1),hy=std::min(ly+1,ah-1);
                        const float fx=tx-lx,fy=ty-ly;
                        std::array<float,4> source{};
                        for(int k=0;k<4;++k) {
                            const float sample=((sourceTexture[(ly*aw+lx)*4+k]*(1-fx)+sourceTexture[(ly*aw+hx)*4+k]*fx)*(1-fy)+
                                                (sourceTexture[(hy*aw+lx)*4+k]*(1-fx)+sourceTexture[(hy*aw+hx)*4+k]*fx)*fy)/255.0f;
                            source[k]=sample*(wa*ca[k]+wb*cb[k]+wc*ccol[k]);
                        }
                        auto& dest=pixels[y*w+x];const float alpha=source[3];
                        for(int k=0;k<3;++k)dest[k]=source[k]*alpha+dest[k]*(1-alpha);
                        dest[3]=alpha+dest[3]*(1-alpha);
                    }
                    ++triangles;
                }
            }
        }
        std::vector<unsigned char> rgba(w*h*4);
        for(int p=0;p<w*h;++p)for(int k=0;k<4;++k)rgba[p*4+k]=static_cast<unsigned char>(std::clamp(pixels[p][k],0.0f,1.0f)*255);
        std::string name(argv[file]);name=name.substr(0,name.find_last_of('.'))+".rgba";
        std::ofstream out(name,std::ios::binary);out.write(reinterpret_cast<const char*>(&w),4);out.write(reinterpret_cast<const char*>(&h),4);
        out.write(reinterpret_cast<const char*>(rgba.data()),rgba.size());assert(out.good());
        std::printf("%s actual ImGui triangles: %u\n",name.c_str(),triangles);
    }
}
