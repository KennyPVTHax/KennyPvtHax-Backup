#include "KennyCharacters.h"
#include "KennyAppearanceStore.h"
#include <cassert>
#include <cstdlib>
#include <new>
#include <cstdio>
#include <fstream>
#include <memory>
#include <limits>
using namespace KennyCharacters;
static std::atomic<size_t> allocations{0};
__attribute__((noinline)) void* operator new(size_t n){allocations.fetch_add(1);if(void* p=std::malloc(n))return p;throw std::bad_alloc();}
__attribute__((noinline)) void* operator new[](size_t n){return ::operator new(n);}
__attribute__((noinline)) void operator delete(void* p) noexcept {std::free(p);}
__attribute__((noinline)) void operator delete[](void* p) noexcept {std::free(p);}
__attribute__((noinline)) void operator delete(void* p,size_t) noexcept {std::free(p);}
__attribute__((noinline)) void operator delete[](void* p,size_t) noexcept {std::free(p);}
static unsigned uploads=0,releases=0;
static KennyThemeBackground::ArtworkFrame UploadFixture(void*,const KennyAssets::Image& image){++uploads;return {reinterpret_cast<ImTextureID>(uintptr_t(uploads+2)),int(image.width),int(image.height)};}
static void ReleaseFixture(void*,KennyThemeBackground::ArtworkFrame){++releases;}
int main(){
    auto registry=std::make_unique<Registry>();registry->Configure(".verification/c2-assets");
    assert(registry->count==2);auto* c=registry->Find("highschool_dxd_rias");assert(c&&c->Installed()&&c->image.transparent&&c->packCount==2);
    std::ifstream expected(".verification/c2-assets/expected.rgba",std::ios::binary);std::vector<uint8_t> expectedBytes((std::istreambuf_iterator<char>(expected)),{});assert(c->image.rgba==expectedBytes);
    auto limited=std::make_unique<Registry>();limited->decodedBytes=32*1024*1024-12288-19200;limited->Configure(".verification/c2-assets");
    assert(limited->decodedBytes==32*1024*1024&&limited->characters[0].packCount==1);
    for(const auto& pack:limited->characters[0].packs)for(const auto& event:pack.events)for(unsigned i=event.count;i<event.clips.size();++i)assert(event.clips[i].samples.capacity()==0);
    const char* folder=".verification/c2-assets/assets/anime/highschool_dxd_rias";int fd=open(folder,O_RDONLY|O_DIRECTORY);assert(fd>=0);
    std::vector<uint8_t> bytes;KennyAssets::Image image;
    assert(!KennyAssets::Read(fd,"../manifest.json",10000,bytes)&&!KennyAssets::Read(fd,"/etc/passwd",10000,bytes)&&!KennyAssets::Read(fd,"voice/../../a.wav",10000,bytes));
    assert(!KennyAssets::Read(fd,"character.png",1,bytes));
    unlink(".verification/c2-assets/assets/anime/highschool_dxd_rias/symlink.png");assert(symlink("character.png",".verification/c2-assets/assets/anime/highschool_dxd_rias/symlink.png")==0);assert(!KennyAssets::Read(fd,"symlink.png",1048576,bytes));
    const char* fifo=".verification/c2-assets/assets/anime/highschool_dxd_rias/fifo.png";unlink(fifo);assert(mkfifo(fifo,0600)==0);assert(!KennyAssets::Read(fd,"fifo.png",1024,bytes));unlink(fifo);
    assert(KennyAssets::Read(fd,"opaque.png",1048576,bytes)&&!KennyAssets::PNG(bytes,image));
    assert(KennyAssets::Read(fd,"character.png",1048576,bytes));auto png=bytes;
    bytes[bytes.size()/2]^=1;assert(!KennyAssets::PNG(bytes,image));for(size_t size=0;size<png.size();size+=11){bytes.assign(png.begin(),png.begin()+size);assert(!KennyAssets::PNG(bytes,image));}
    assert(KennyAssets::Read(fd,"voice/a.wav",1048576,bytes));std::vector<int16_t> samples;assert(KennyAssets::WAV(bytes,samples)&&samples.size()==9600);
    bytes[20]=3;assert(!KennyAssets::WAV(bytes,samples));bytes.assign(200,0);assert(!KennyAssets::WAV(bytes,samples));close(fd);
    nlohmann::json json;std::vector<uint8_t> deep(20,'[');deep.insert(deep.end(),20,']');assert(!Registry::JSON(deep,json));
    KennyAppearance::Preferences p;p.theme=KennyAppearance::Theme::Anime;p.characterId="unknown";
    registry->Selected(p);assert(p.characterId=="highschool_dxd_rias");
    auto bank=std::make_unique<KennyAudio::Bank>();bank->Initialize();KennyAudio::Mixer mixer;mixer.bank=bank.get();KennyAudio::Dispatcher audio;audio.mixer=&mixer;
    registry->upload=UploadFixture;registry->release=ReleaseFixture;registry->Prepare(p,&audio);assert(uploads==2&&c->artworkTexture.Valid());
    for(unsigned i=0;i<1000;++i)registry->Prepare(p,&audio);
    assert(uploads==2);
    std::array<int16_t,2048> block{};assert(audio.Emit(KennyAudio::Event::MenuOpen,p,1));mixer.Render(block.data(),block.size());assert(mixer.character);
    unsigned last=c->packs[0].events[0].last;assert(audio.Emit(KennyAudio::Event::MenuClose,p,1.1)); // cooldown: no overlapping voice
    mixer.Render(block.data(),block.size());assert(mixer.character);
    p.theme=KennyAppearance::Theme::Classic;registry->Prepare(p,&audio);mixer.Render(block.data(),block.size());assert(!mixer.character);
    p.theme=KennyAppearance::Theme::Anime;registry->Prepare(p,&audio);assert(audio.Emit(KennyAudio::Event::MenuOpen,p,3));mixer.Render(block.data(),block.size());assert(c->packs[0].events[0].last!=last);
    p.characterVoice=false;registry->Prepare(p,&audio);mixer.Render(block.data(),block.size());assert(!mixer.character);
    p.characterVoice=true;p.uiSounds=false;registry->Prepare(p,&audio);assert(!audio.Emit(KennyAudio::Event::MenuOpen,p,4));mixer.Render(block.data(),block.size());for(auto sample:block)assert(sample==0);
    p.uiSounds=true;p.characterVolume=22;registry->Prepare(p,&audio);assert(mixer.voiceVolume==2200);
    assert(audio.Emit(KennyAudio::Event::CheckboxOn,p,5,"Enable bullet track"));mixer.Render(block.data(),block.size());assert(c->packs[0].events[unsigned(VoiceEvent::Bullet)].last<2);
    p.voicePack="alternate";assert(audio.Emit(KennyAudio::Event::MenuOpen,p,6));const auto switchedEpoch=mixer.voiceEpoch.load();
    registry->Prepare(p,&audio);assert(mixer.voiceEpoch.load()==switchedEpoch);mixer.Render(block.data(),block.size());assert(mixer.character&&c->packs[1].events[0].last<2);
    p.voicePack="default";registry->Prepare(p,&audio);
    for(unsigned i=0;i<500;++i){p.theme=i%2?KennyAppearance::Theme::Anime:KennyAppearance::Theme::Aurora;registry->Prepare(p,&audio);audio.Emit(KennyAudio::Event::MenuOpen,p,6+i);mixer.Render(block.data(),block.size());}assert(uploads==2);
    p.theme=KennyAppearance::Theme::Anime;registry->Prepare(p,&audio);
    const size_t allocated=allocations.load();
    for(unsigned i=0;i<10000;++i){registry->Prepare(p,&audio);audio.Emit(KennyAudio::Event::MenuOpen,p,1000+i);mixer.Render(block.data(),block.size());}
    assert(allocations.load()==allocated); // cached dispatch/render never load or allocate
    registry->ClearTextures();assert(releases==2&&!c->artworkTexture.Valid());p.theme=KennyAppearance::Theme::Anime;registry->Prepare(p,&audio);assert(uploads==4);registry->ClearTextures(true);assert(releases==2);
    // Missing production pack routes to the original C1 tone, never a voice.
    auto missing=std::make_unique<Registry>();missing->Configure(".");assert(missing->count==1&&!missing->characters[0].Installed());
    missing->Prepare(p,&audio);assert(audio.Emit(KennyAudio::Event::MenuOpen,p,21000));mixer.Render(block.data(),block.size());assert(!mixer.character);
    bool fallback=false;for(auto sample:block)fallback|=sample!=0;assert(fallback);
    char pattern[]="/tmp/kenny-c2-prefs-XXXXXX";const char* path=mkdtemp(pattern);assert(path);KennyAppearance::Store store;store.Configure(path,p);
    p.characterVoice=false;p.characterVolume=43;p.characterLauncher=false;p.voicePack="custom";store.Sync(p,true);
    KennyAppearance::Preferences restored;KennyAppearance::Store fresh;fresh.Configure(path,restored);assert(KennyAppearance::Equal(p,restored));
    {std::ofstream old(store.path);old<<"KennyPvtHaxAppearance 2\n2 88 1 1 40 30 0 0 80 0\n0 66 2\n";}
    KennyAppearance::Preferences migrated;KennyAppearance::Store legacy;legacy.Configure(path,migrated);
    assert(migrated.opacity==88&&migrated.theme==KennyAppearance::Theme::Classic&&!migrated.uiSounds&&migrated.uiVolume==66&&migrated.characterId=="highschool_dxd_rias");
    {std::ofstream bad(store.path);bad<<"KennyPvtHaxAppearance 3\n2 88 1 1 40 30 0 0 80 0\n1 66 2\n../bad ../pack /etc/passwd 1 43 1\n";}
    KennyAppearance::Preferences safe;KennyAppearance::Store invalid;invalid.Configure(path,safe);assert(safe.opacity==88&&safe.uiVolume==66&&safe.characterId=="highschool_dxd_rias"&&safe.voicePack=="default"&&safe.characterArtwork=="character.png");
    unlink(store.path.c_str());rmdir(path);
    KennyAppearance::Preferences whitespace;whitespace.characterArtwork="bad art.png";KennyAppearance::Normalize(whitespace);assert(whitespace.characterArtwork=="character.png");
    ImGui::CreateContext();auto& io=ImGui::GetIO();io.IniFilename=nullptr;io.DisplaySize=ImVec2(1920,872);unsigned char* pixels;int w,h;io.Fonts->GetTexDataAsRGBA32(&pixels,&w,&h);ImGui::NewFrame();auto* draw=ImGui::GetBackgroundDrawList();
    DrawCharacter(draw,ImVec2(10,10),ImVec2(1100,700),34,174,{reinterpret_cast<ImTextureID>(3),32,64},p);assert(draw->VtxBuffer.Size==4);
    const auto& a=draw->VtxBuffer[0];const auto& b=draw->VtxBuffer[2];assert(std::abs((b.pos.x-a.pos.x)/(b.pos.y-a.pos.y)-.5f)<.001f&&a.pos.y>=184&&a.uv.x==0&&b.uv.x==1);
    ImGui::EndFrame();ImGui::DestroyContext();std::puts("PASS C2 real local registry/loaders: byte-exact PNG alpha, corruption/truncation/opaque rejection, safe path/symlink/FIFO handling, bounded JSON/WAV decoding/resampling/cache budget, registry extension/selection, GPU lifecycle interface, actual C1 voice mix/volume/mute/cooldown/variation/semantic event routing, 500 switches, 10000 allocation-free cached dispatch/mix iterations, schema 1/2 migration and schema 3 persistence, transparent character geometry. Diagnostic test media only; no Rias artwork/recordings installed or Android claims.");
}
