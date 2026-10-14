#include "KennyPresentationMedia.h"
#include "KennyAppearanceStore.h"
#include "KennyLauncher.h"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>
using namespace KennyPresentation;
static int uploads=0;
static KennyThemeBackground::ArtworkFrame Upload(void*,const KennyAssets::Image& image){++uploads;return {reinterpret_cast<ImTextureID>(uintptr_t(uploads+100)),int(image.width),int(image.height)};}
static void Wait(Assets& assets){for(int i=0;i<1000&&assets.video<0;++i){assets.Prepare(true);std::this_thread::sleep_for(std::chrono::milliseconds(2));}assert(assets.video>=0);}
int main(){
 char pattern[]="/tmp/kenny-embedded-XXXXXX";const char* temp=mkdtemp(pattern);assert(temp);
 KennyCharacters::Registry registry;registry.Configure(nullptr);assert(registry.configured);
 KennyAppearance::Preferences p;p.theme=KennyAppearance::Theme::Anime;
 KennyAudio::Mixer mixer;KennyAudio::Dispatcher dispatcher;dispatcher.mixer=&mixer;
 registry.Prepare(p,&dispatcher);assert(p.voicePack=="user_supplied_events");
 auto* pack=registry.Pack(registry.characters[0],p.voicePack);assert(pack&&pack->Available());
 for(auto event:{KennyCharacters::VoiceEvent::AimEnabled,KennyCharacters::VoiceEvent::AimDisabled,KennyCharacters::VoiceEvent::Bullet,KennyCharacters::VoiceEvent::ExtraNavigation})assert(pack->events[unsigned(event)].count==1);
 auto snapshot=registry.decodedBytes;registry.Prepare(p,&dispatcher);assert(registry.decodedBytes==snapshot);
 assert(registry.TestVoice(p,&dispatcher,10)==KennyAudioDiagnostics::Result::Queued);
 assert(registry.TestVoice(p,&dispatcher,10.01)==KennyAudioDiagnostics::Result::Cooldown);
 p.uiSounds=false;assert(registry.TestVoice(p,&dispatcher,20)==KennyAudioDiagnostics::Result::SoundDisabled);p.uiSounds=true;
 p.voicePack="cici_fyre_mature_female";registry.Prepare(p,&dispatcher);assert(p.voicePack=="cici_fyre_mature_female");p.theme=KennyAppearance::Theme::Classic;
 assert(!registry.Emit(KennyCharacters::VoiceEvent::AimEnabled,p,&mixer,30));assert(registry.lastResult==KennyAudioDiagnostics::Result::WrongTheme);
 {
 Assets assets;assets.Configure(temp);assert(assets.embedded&&assets.logo.width==1032&&assets.logo.transparent);
 const auto* movie=KennyEmbedded::Lookup("assets/presentation/anime-background.mp4");assert(movie&&movie->size==10113470);
 assets.upload=Upload;assets.Prepare(false);assert(uploads==1&&!assets.cache.started&&assets.video<0);
 Wait(assets);assert(uploads==2&&assets.posterTexture.Valid()&&KennyEmbedded::VideoCache::Matches(assets.video,*movie));
 for(int i=0;i<1000;++i)assets.Prepare(true);assert(uploads==2);
 Assets reused;reused.Configure(temp);reused.upload=Upload;Wait(reused);assert(KennyEmbedded::VideoCache::Matches(reused.video,*movie));
 assert(!std::filesystem::exists(std::filesystem::path(temp)/"assets"));
 // Corrupt known cache data are rejected and atomically replaced, not trusted by size.
 auto cached=std::filesystem::path(temp)/"kenny-media-cache"/(std::string(movie->sha256)+".mp4");
 {std::fstream f(cached,std::ios::in|std::ios::out|std::ios::binary);f.put('x');}
 Assets recovered;recovered.Configure(temp);recovered.upload=Upload;Wait(recovered);assert(KennyEmbedded::VideoCache::Matches(recovered.video,*movie));
 Assets denied;denied.Configure("/nonexistent/kenny-directory");denied.upload=Upload;denied.Prepare(true);for(int i=0;i<1000&&!denied.cache.done;++i)std::this_thread::sleep_for(std::chrono::milliseconds(1));assert(denied.video<0&&denied.posterTexture.Valid());
 }
 ImGui::CreateContext();auto& io=ImGui::GetIO();io.IniFilename=nullptr;io.DisplaySize=ImVec2(1920,1080);
 unsigned char* atlas;int w,h;io.Fonts->GetTexDataAsRGBA32(&atlas,&w,&h);ImGui::NewFrame();
 auto* draw=ImGui::GetBackgroundDrawList();draw->_ResetForNewFrame();KennyLauncher::Logo logo;
 logo.Set({reinterpret_cast<ImTextureID>(3),1032,1032});logo.Draw(draw,ImVec2(64,64),64);
 assert(draw->VtxBuffer.Size==65&&draw->IdxBuffer.Size==192);
 for(const auto& v:draw->VtxBuffer){assert(v.pos.x>=32&&v.pos.x<=96&&v.pos.y>=32&&v.pos.y<=96);assert(v.uv.x>=0&&v.uv.x<=1&&v.uv.y>=0&&v.uv.y<=1);}
 assert(draw->VtxBuffer[1].pos.x==96); // Artwork reaches the actual outer circle.
 ImGui::EndFrame();ImGui::DestroyContext();
 std::filesystem::remove_all(temp);
 std::cout<<"PASS embedded registry/4 named voices/default+saved selection/mute/cooldown/theme gating; memory PNG alpha/logo+poster; lazy verified movie-only cache/reuse/corruption recovery/unwritable fallback. Android playback unverified.\n";
}
