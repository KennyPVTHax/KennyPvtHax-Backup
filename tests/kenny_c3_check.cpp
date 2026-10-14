#include "KennyCharacters.h"
#include "KennyAppearanceStore.h"
#include <cassert>
#include <fstream>
#include <memory>
#include <cstdio>
#include <filesystem>

// Real locally installed CC0 clips and production C1 mixer, not Android playback.
int main(){
    // Preserve the historical CC0-only/missing-character regression independently
    // of the now fully installed production pack. Copy real approved WAV bytes;
    // never depend on which production pack is first in the manifest.
    char mediaPattern[]="/tmp/kenny-c3-media-XXXXXX";
    const char* mediaDirectory=mkdtemp(mediaPattern);assert(mediaDirectory);
    const auto mediaRoot=std::filesystem::path(mediaDirectory);
    const auto packRoot=mediaRoot/"assets/anime/highschool_dxd_rias";
    std::filesystem::create_directories(packRoot/"voice");
    nlohmann::json manifest;{std::ifstream input("assets/anime/highschool_dxd_rias/manifest.json");input>>manifest;}
    nlohmann::json cici;for(const auto& item:manifest["voice_packs"])if(item["id"]=="cici_fyre_mature_female")cici=item;
    assert(!cici.is_null());manifest["voice_packs"]=nlohmann::json::array({cici});
    {std::ofstream output(packRoot/"manifest.json");output<<manifest;}
    std::filesystem::copy_file("assets/anime/index.json",mediaRoot/"assets/anime/index.json");
    for(const auto& event:cici["events"].items())for(const auto& value:event.value()){
        const std::string name=value;assert(name.find("voice/cici_")==0&&name.find("..") == std::string::npos);
        if(!std::filesystem::exists(packRoot/name))std::filesystem::copy_file(std::filesystem::path("assets/anime/highschool_dxd_rias")/name,packRoot/name);
    }
    auto registry=std::make_unique<KennyCharacters::Registry>();registry->Configure(mediaDirectory);
    assert(registry->count==1);
    auto& character=registry->characters[0];
    assert(character.id=="highschool_dxd_rias"&&character.packCount==1&&!character.Installed());
    assert(character.image.rgba.empty()&&character.logo.rgba.empty());
    assert(!registry->Pack(character,"default")); // Original Rias recordings remain missing.
    auto& pack=character.packs[0];assert(pack.id=="cici_fyre_mature_female");
    assert(pack.name=="Cici Fyre - English alternative");
    unsigned mapped=0;for(const auto& e:pack.events)mapped+=e.count!=0;assert(mapped==7);
    for(const auto& e:pack.events)for(unsigned i=0;i<e.count;++i){
        assert(e.clips[i].samples.size()>480&&e.clips[i].samples.size()<=KennyAudio::SampleRate*4);
        bool audible=false;for(auto value:e.clips[i].samples)audible|=value!=0;assert(audible);
    }
    auto bank=std::make_unique<KennyAudio::Bank>();bank->Initialize();
    KennyAudio::Mixer mixer;mixer.bank=bank.get();KennyAudio::Dispatcher dispatcher;dispatcher.mixer=&mixer;
    KennyAppearance::Preferences p;p.theme=KennyAppearance::Theme::Anime;
    registry->Prepare(p,&dispatcher);assert(p.voicePack==pack.id);
    std::array<int16_t,4096> block{};
    assert(dispatcher.Emit(KennyAudio::Event::MenuOpen,p,1));mixer.Render(block.data(),block.size());
    assert(mixer.character==&pack.events[unsigned(KennyCharacters::VoiceEvent::Open)].clips[0]);
    assert(dispatcher.Emit(KennyAudio::Event::MenuClose,p,1.2));mixer.Render(block.data(),block.size());
    assert(mixer.character==&pack.events[unsigned(KennyCharacters::VoiceEvent::Open)].clips[0]); // cooldown, no overlapping dialogue
    p.characterVoice=false;registry->Prepare(p,&dispatcher);mixer.Render(block.data(),block.size());assert(!mixer.character);
    p.characterVoice=true;p.uiSounds=false;registry->Prepare(p,&dispatcher);
    assert(!dispatcher.Emit(KennyAudio::Event::MenuOpen,p,3));mixer.Render(block.data(),block.size());for(auto x:block)assert(!x);
    p.uiSounds=true;p.characterVolume=25;registry->Prepare(p,&dispatcher);assert(mixer.voiceVolume==2500);
    assert(dispatcher.Emit(KennyAudio::Event::CheckboxOn,p,4,"Enable bullet track"));mixer.Render(block.data(),block.size());
    assert(mixer.character==&pack.events[unsigned(KennyCharacters::VoiceEvent::Bullet)].clips[0]);
    for(int i=0;i<100;++i){p.theme=i%2?KennyAppearance::Theme::Aurora:KennyAppearance::Theme::Classic;registry->Prepare(p,&dispatcher);mixer.Render(block.data(),block.size());assert(!mixer.character);}
    p.theme=KennyAppearance::Theme::Anime;registry->Prepare(p,&dispatcher);
    assert(!registry->Emit(KennyCharacters::VoiceEvent::LoginSuccess,p,&mixer,5));
    char pattern[]="/tmp/kenny-c3-prefs-XXXXXX";const char* directory=mkdtemp(pattern);assert(directory);
    KennyAppearance::Store store;store.Configure(directory,p);
    p.characterVoice=false;p.characterVolume=43;store.Sync(p,true);
    KennyAppearance::Preferences restored;KennyAppearance::Store fresh;fresh.Configure(directory,restored);
    assert(KennyAppearance::Equal(p,restored)&&restored.voicePack=="cici_fyre_mature_female");
    registry->Prepare(restored,&dispatcher);assert(restored.voicePack==pack.id&&!restored.characterVoice&&mixer.voiceVolume==0);
    unlink(store.path.c_str());rmdir(directory);p.characterVoice=true;

    // A genuine portable-mixer demonstration of existing event dispatch. No GPU/device claim.
    p.theme=KennyAppearance::Theme::Anime;p.characterVolume=70;registry->Prepare(p,&dispatcher);
    const KennyAudio::Event sequence[]={KennyAudio::Event::MenuOpen,KennyAudio::Event::CheckboxOn,KennyAudio::Event::PrimaryNavigation,KennyAudio::Event::ButtonPressed,KennyAudio::Event::MenuClose};
    std::vector<int16_t> pcm(10*KennyAudio::SampleRate);
    for(unsigned i=0;i<5;++i){assert(dispatcher.Emit(sequence[i],p,10+i*2));mixer.Render(pcm.data()+i*2*KennyAudio::SampleRate,2*KennyAudio::SampleRate);}
    std::ofstream out(".verification/c3-mixer-demo.wav",std::ios::binary);
    const uint32_t bytes=pcm.size()*2,riff=bytes+36,fmt=16,rate=KennyAudio::SampleRate,byteRate=rate*2;
    const uint16_t format=1,channels=1,align=2,bits=16;
    auto write=[&](auto value){out.write(reinterpret_cast<const char*>(&value),sizeof(value));};
    out.write("RIFF",4);write(riff);out.write("WAVEfmt ",8);write(fmt);write(format);write(channels);write(rate);write(byteRate);write(align);write(bits);out.write("data",4);write(bytes);out.write(reinterpret_cast<const char*>(pcm.data()),bytes);assert(out.good());
    std::puts("PASS C3 real installed CC0 alternative: 7 mapped events/5 source clips, truthful partial Rias status, C1 actual PCM mixing, cooldown/volume/global mute, saved pack/preferences restored in a fresh store, 100 theme cancellations, missing original-recording fallback and portable event demo. Android playback not verified.");
    std::filesystem::remove_all(mediaRoot);
}
