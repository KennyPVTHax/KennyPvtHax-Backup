// Actual production ImGui controls and real supplied PCM. No SDK/Android mock claim.
#define KENNY_C3_CAPTURE_NO_MAIN
#include "kenny_c3_capture.cpp"
#include <cstring>
static unsigned uploads=0;
static KennyThemeBackground::ArtworkFrame UploadSupplied(void*,const KennyAssets::Image& im){++uploads;return {reinterpret_cast<ImTextureID>(2),int(im.width),int(im.height)};}
// Extended host draw-data stream embeds the actual character texture, while the
// original host rasterizer remains compatible with all old font-only captures.
static void SaveSupplied(const char* name){
    auto* data=ImGui::GetDrawData();std::ofstream out(std::string(".verification/")+name+".draw",std::ios::binary);
    const int header[]={-int(viewport.x),int(viewport.y),data->CmdListsCount};out.write((char*)header,sizeof(header));
    const auto& image=menu.characters.characters[0].image;unsigned count=image.rgba.empty()?0:1;out.write((char*)&count,4);
    if(count){uint64_t id=2;out.write((char*)&id,8);out.write((char*)&image.width,4);out.write((char*)&image.height,4);out.write((char*)image.rgba.data(),image.rgba.size());}
    for(int i=0;i<data->CmdListsCount;++i){auto* list=data->CmdLists[i];const int sizes[]={list->VtxBuffer.Size,list->IdxBuffer.Size,list->CmdBuffer.Size};out.write((char*)sizes,sizeof(sizes));out.write((char*)list->VtxBuffer.Data,list->VtxBuffer.Size*sizeof(ImDrawVert));out.write((char*)list->IdxBuffer.Data,list->IdxBuffer.Size*sizeof(ImDrawIdx));
        for(const auto& cmd:list->CmdBuffer){assert(!cmd.UserCallback);out.write((char*)&cmd.ClipRect,sizeof(ImVec4));const unsigned values[]={cmd.ElemCount,cmd.IdxOffset,cmd.VtxOffset};out.write((char*)values,sizeof(values));uint64_t id=reinterpret_cast<uintptr_t>(cmd.GetTexID());out.write((char*)&id,8);}}
}
int main(int argc,char** argv){
    assert(argc==2);InitializeC3Capture();const auto original=SnapshotFeatures();menu.characters.Configure(argv[1]);menu.characters.upload=UploadSupplied;
    menu.appearance.theme=KennyAppearance::Theme::Anime;menu.appearance.voicePack="user_supplied_events";
    auto bank=std::make_unique<KennyAudio::Bank>();bank->Initialize();KennyAudio::Mixer mixer;mixer.bank=bank.get();KennyAudio::Dispatcher audio;audio.mixer=&mixer;menu.audio=&audio;menu.audioStatus="Host PCM test sink; Android playback unverified.";Frame();Frame();
    auto& c=menu.characters.characters[0];auto* pack=menu.characters.Pack(c,"user_supplied_events");assert(pack&&pack->Available()&&c.image.transparent&&c.image.width==1035&&c.image.height==1280&&!c.launcherTexture.Valid());assert(uploads==1);
    for(auto e:{KennyCharacters::VoiceEvent::AimEnabled,KennyCharacters::VoiceEvent::AimDisabled,KennyCharacters::VoiceEvent::Bullet,KennyCharacters::VoiceEvent::ExtraNavigation})assert(pack->events[unsigned(e)].count==1);
    assert(!pack->events[unsigned(KennyCharacters::VoiceEvent::BulletDisabled)].count);
    unsigned voices=0;auto countQueued=[&](unsigned old,const KennyAudio::Recording* expected){unsigned records=0;for(unsigned i=old;i!=mixer.write.load();i=(i+1)%KennyAudio::QueueSize){auto* r=mixer.queue[i].recording;if(r){++records;if(expected)assert(r==expected);}}voices+=records;return records;};
    std::array<int16_t,800> pcm{};auto settle=[&](){for(int i=0;i<250;++i){mixer.Render(pcm.data(),pcm.size());Frame();}};
    auto clip=[&](KennyCharacters::VoiceEvent e){return &pack->events[unsigned(e)].clips[0];};
    Primary(1);ResetScroll();settle();assert(!Cheat::Aimbot::Enable);unsigned start=mixer.write.load();Click(NativeCenter("Enable aimbot"));assert(Cheat::Aimbot::Enable&&countQueued(start,clip(KennyCharacters::VoiceEvent::AimEnabled))==1);
    start=mixer.write.load();for(int i=0;i<60;++i)Frame();assert(countQueued(start,nullptr)==0); // enabled idle frames never emit
    settle();start=mixer.write.load();Click(NativeCenter("Enable aimbot"));assert(!Cheat::Aimbot::Enable&&countQueued(start,clip(KennyCharacters::VoiceEvent::AimDisabled))==1);
    settle();start=mixer.write.load();Click(NativeCenter("Enable aimbot"));Click(NativeCenter("Enable aimbot"));assert(!Cheat::Aimbot::Enable&&countQueued(start,clip(KennyCharacters::VoiceEvent::AimEnabled))==1); // rapid OFF updates immediately; speech suppressed by overlap cooldown
    settle();Primary(2);Secondary(false);ResetScroll();settle();assert(!Cheat::BulletTrack::Enable);start=mixer.write.load();Click(NativeCenter("Enable bullet track"));assert(Cheat::BulletTrack::Enable&&countQueued(start,clip(KennyCharacters::VoiceEvent::Bullet))==1);
    settle();start=mixer.write.load();Click(NativeCenter("Enable bullet track"));assert(!Cheat::BulletTrack::Enable&&countQueued(start,nullptr)==0); // no btoff supplied
    settle();start=mixer.write.load();Secondary(true);assert(countQueued(start,clip(KennyCharacters::VoiceEvent::ExtraNavigation))==1);settle();start=mixer.write.load();Secondary(true);assert(countQueued(start,nullptr)==0);
    Primary(0);settle();start=mixer.write.load();Primary(2);assert(countQueued(start,clip(KennyCharacters::VoiceEvent::ExtraNavigation))==1); // remembered Extra features
    settle();Primary(1);ResetScroll();settle();start=mixer.write.load();Click(NativeCenter("Ignore bot"));assert(countQueued(start,nullptr)==0);Click(NativeCenter("Ignore bot")); // unrelated setting never borrows these clips
    menu.appearance.uiSounds=false;Frame();start=mixer.write.load();Click(NativeCenter("Enable aimbot"));assert(Cheat::Aimbot::Enable&&countQueued(start,nullptr)==0);Cheat::Aimbot::Enable=false;Frame();menu.appearance.uiSounds=true;Frame();
    auto& other=menu.characters.characters[1];other.id="test_registry_extension";other.name="Diagnostic only";menu.characters.count=2;menu.appearance.characterId=other.id;Frame();start=mixer.write.load();Click(NativeCenter("Enable aimbot"));assert(countQueued(start,nullptr)==0);Cheat::Aimbot::Enable=false;menu.appearance.characterId=c.id;Frame();
    Primary(0);Secondary(false);ResetScroll();settle();SaveSupplied("supplied-anime-player");menu.appearance.artworkVisible=false;Frame();SaveSupplied("supplied-artwork-hidden");menu.appearance.artworkVisible=true;Frame();
    Primary(4);ResetScroll();settle();ImGui::SetScrollY(panelWindow,panelWindow->ScrollMax.y);Frame();Frame();SaveSupplied("supplied-anime-settings");
    for(int i=0;i<50;++i){menu.appearance.theme=i%2?KennyAppearance::Theme::Classic:KennyAppearance::Theme::Aurora;Frame();mixer.Render(pcm.data(),pcm.size());assert(!mixer.character);}assert(uploads==1);
    Primary(0);Secondary(false);ResetScroll();menu.appearance.theme=KennyAppearance::Theme::Classic;settle();SaveSupplied("supplied-classic");menu.appearance.theme=KennyAppearance::Theme::Aurora;settle();SaveSupplied("supplied-aurora");
    assert(original==SnapshotFeatures());assert(voices==6);menu.audio=nullptr;ImGui::DestroyContext();puts("PASS supplied media: real PNG alpha/cache/fallback, exact Aim ON/OFF/Bullet ON and Extra navigation PCM pointers once per native interaction; no enabled-frame/unrelated/Bullet OFF voice, rapid-toggle overlap suppression, global mute, selected-character isolation, visibility, 50 theme switches, original feature snapshot preserved. Host texture callback/PCM only; Android GPU/audio unverified.");
}
