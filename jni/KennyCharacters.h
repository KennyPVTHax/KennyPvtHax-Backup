#pragma once
#include "KennyAssetIO.h"
#include "KennyEmbeddedMedia.h"
#include "KennyAudio.h"
#include "KennyThemeBackground.h"
#include "Includes/json.hpp"
#include <array>
#include <dirent.h>

namespace KennyCharacters {
enum class VoiceEvent:unsigned {Open,Close,Navigation,LoginSuccess,LoginFailure,Enabled,Disabled,Skins,Bullet,Confirmation,Error,ThemeSwitch,SettingsNavigation,AimEnabled,AimDisabled,BulletDisabled,ExtraNavigation,Count};
constexpr unsigned EventCount=unsigned(VoiceEvent::Count);
inline constexpr const char* EventNames[]={"launcher_open","launcher_close","menu_navigation","login_success","login_failure","feature_enabled","feature_disabled","skins_enabled","bullet_track_enabled","confirmation","error","theme_switch","settings_navigation","aim_enabled","aim_disabled","bullet_track_disabled","extra_features_navigation"};
struct EventClips {std::array<KennyAudio::Recording,3> clips;unsigned count=0,last=3;};
struct VoicePack {std::string id,name;std::array<bool,EventCount> decodeFailed{},mappingDefined{};std::array<EventClips,EventCount> events;bool Available()const{for(const auto& e:events)if(e.count)return true;return false;}};
struct Character {
    std::string id="highschool_dxd_rias",name="Rias Gremory",series="High School DxD";
    std::string artwork="character.png",launcher="launcher.png",status="Assets missing; K launcher and UI tones remain available.";
    KennyAssets::Image image,logo;std::array<VoicePack,4> packs;unsigned packCount=0;
    KennyThemeBackground::ArtworkFrame artworkTexture,launcherTexture;
    bool artTried=false,logoTried=false;
    bool Installed()const{return !image.rgba.empty()&&!logo.rgba.empty()&&packCount&&packs[0].Available();}
};
using Upload=KennyThemeBackground::ArtworkFrame (*)(void*,const KennyAssets::Image&);
using Release=void (*)(void*,KennyThemeBackground::ArtworkFrame);
struct Registry {
    std::array<Character,8> characters;unsigned count=1;bool configured=false,directoryWarned=false;
    Upload upload=nullptr;Release release=nullptr;void* textureUser=nullptr;
    double nextVoice=0,lastTime=0;std::array<double,EventCount> nextEvent{};uint32_t random=0x7139c5;
    void ResetCooldowns(){nextVoice=0;nextEvent.fill(0);}
    size_t decodedBytes=0;
    const char* mediaStatus="Private media has not been checked.";
    KennyAudioDiagnostics::Result lastResult=KennyAudioDiagnostics::Result::Idle,testResult=KennyAudioDiagnostics::Result::Idle;
    uint64_t testStartedBefore=0,testCallbacksBefore=0;
    VoiceEvent testEvent=VoiceEvent::AimEnabled;bool testAttempted=false;
    bool Report(KennyAudioDiagnostics::Result result,VoiceEvent event){
        lastResult=result;using namespace KennyAudioDiagnostics;
        const auto code=result==Result::Queued?Code::Submitted:result==Result::QueueFull?Code::QueueFailed:result==Result::MissingRecording||result==Result::WrongPack?Code::Unmapped:Code::Suppressed;
        Log(code,Reason(result),0,unsigned(event)<EventCount?EventNames[unsigned(event)]:"invalid");
        // Preserve the existing router convention: cooldown consumes feedback,
        // while missing/disabled recordings allow the existing C1 tone fallback.
        return result==Result::Queued||result==Result::Cooldown||result==Result::QueueFull;
    }
    Registry(){for(unsigned i=1;i<characters.size();++i){characters[i].id.clear();characters[i].name.clear();characters[i].series.clear();}}
    // Registry recordings are immutable once configured and must outlive the
    // C1 mixer/player. No reload/file I/O occurs during event dispatch.
    Character* Find(const std::string& id){for(unsigned i=0;i<count;++i)if(characters[i].id==id)return &characters[i];return nullptr;}
    Character& Selected(KennyAppearance::Preferences& p){auto* c=Find(p.characterId);if(!c){p.characterId=characters[0].id;c=&characters[0];}return *c;}
    VoicePack* Pack(Character& c,const std::string& id){for(unsigned i=0;i<c.packCount;++i)if(c.packs[i].id==id)return &c.packs[i];return nullptr;}
    static bool JSON(const std::vector<uint8_t>& raw,nlohmann::json& json){
        int depth=0;bool quoted=false,escape=false;
        for(char c:raw){if(quoted){if(escape)escape=false;else if(c=='\\')escape=true;else if(c=='"')quoted=false;}else if(c=='"')quoted=true;else if(c=='{'||c=='['){if(++depth>12)return false;}else if(c=='}'||c==']'){if(--depth<0)return false;}}
        if(depth||quoted)return false;
        json=nlohmann::json::parse(raw.begin(),raw.end(),nullptr,false);return !json.is_discarded()&&json.is_object();
    }
    static std::string Text(const nlohmann::json& j,const char* key,const std::string& fallback=""){
        auto it=j.find(key);if(it==j.end()||!it->is_string())return fallback;
        auto s=it->get<std::string>();
        if(s.empty()||s.size()>160)return fallback;
        for(char c:s)if(static_cast<unsigned char>(c)<32)return fallback;
        return s;
    }
    static bool AssetRead(int fd,const std::string& file,size_t limit,std::vector<uint8_t>& bytes){
        return fd==-2?KennyEmbedded::Read(("assets/anime/highschool_dxd_rias/"+file).c_str(),limit,bytes):KennyAssets::Read(fd,file,limit,bytes);
    }
    bool Image(int fd,const std::string& file,KennyAssets::Image& image){
        std::vector<uint8_t> bytes;if(file.size()<4||file.substr(file.size()-4)!=".png"||!AssetRead(fd,file,8*1024*1024,bytes)||!KennyAssets::PNG(bytes,image))return false;
        if(decodedBytes+image.rgba.size()>32*1024*1024){image={};return false;}decodedBytes+=image.rgba.size();return true;
    }
private:
    bool Load(int root,const std::string& folder){
        if(!KennyAssets::Token(folder))return false;
        int fd=root==-2?-2:openat(root,folder.c_str(),O_RDONLY|O_DIRECTORY|O_CLOEXEC|O_NOFOLLOW);if(fd<0&&fd!=-2){KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::ManifestFailed,"character_directory_missing",errno);return false;}
        std::vector<uint8_t> bytes;nlohmann::json j;
        bool valid=AssetRead(fd,"manifest.json",32768,bytes)&&JSON(bytes,j);
        auto schema=valid?j.find("schema"):j.end();valid=valid&&schema!=j.end()&&schema->is_number_integer()&&*schema==1&&Text(j,"id")==folder;
        if(!valid){KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::ManifestFailed,"missing_or_invalid_manifest");if(fd>=0)close(fd);return false;}KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::ManifestLoaded,"validated_local_manifest");Character* c=Find(folder);
        if(!c){if(count>=characters.size()){if(fd>=0)close(fd);return false;}c=&characters[count++];}
        c->id=folder;c->name=Text(j,"name",folder);c->series=Text(j,"series","Unknown series");
        c->artwork=Text(j,"artwork","character.png");c->launcher=Text(j,"launcher","launcher.png");
        const bool artwork=Image(fd,c->artwork,c->image),logo=Image(fd,c->launcher,c->logo);
        auto voices=j.find("voice_packs");if(voices!=j.end()&&voices->is_array()&&voices->size()<=4){
            for(const auto& v:*voices){if(!v.is_object())continue;auto id=Text(v,"id");if(!KennyAssets::Token(id)||Pack(*c,id))continue;
                auto& pack=c->packs[c->packCount];pack.id=id;pack.name=Text(v,"name",id);auto mapping=v.find("events");
                if(mapping!=v.end()&&mapping->is_object())for(unsigned e=0;e<EventCount;++e){
                    auto clips=mapping->find(EventNames[e]);if(clips==mapping->end()||!clips->is_array()||clips->size()>3)continue;
                    pack.mappingDefined[e]=!clips->empty();auto& event=pack.events[e];
                    for(const auto& value:*clips){if(!value.is_string())continue;auto path=value.get<std::string>();
                        if(path.size()<4||path.substr(path.size()-4)!=".wav"||!AssetRead(fd,path,1048576,bytes)){KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::FileMissing,"missing_or_invalid_local_file",errno,EventNames[e]);continue;}
                        auto& clip=event.clips[event.count];if(!KennyAssets::WAV(bytes,clip.samples)){pack.decodeFailed[e]=true;KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::DecodeFailed,"invalid_pcm_wav",0,EventNames[e]);continue;}
                        if(decodedBytes+clip.samples.size()*2>32*1024*1024){clip=KennyAudio::Recording{};continue;}
                        decodedBytes+=clip.samples.size()*2;++event.count;KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::FileLoaded,"decoded_pcm_cached",0,EventNames[e]);
                    }
                }
                if(pack.Available())++c->packCount;else pack={};
            }
        }
        c->status=c->Installed()?"Artwork, launcher and optional voices loaded.":artwork||logo||c->packCount?"Partially installed; missing assets use safe fallbacks.":"Assets missing or invalid; K launcher and UI tones remain available.";
        if(fd>=0)close(fd);return true;
    }
public:
    void Configure(const char* activityDirectory){
        if(configured)return;
        configured=true;
        const bool embedded=KennyEmbedded::Lookup("assets/anime/highschool_dxd_rias/manifest.json")&&Load(-2,"highschool_dxd_rias");
        if(embedded)mediaStatus="Embedded character artwork and supplied event voices loaded; no private pack required.";
        if(embedded&&(!activityDirectory||!*activityDirectory))return;
        if(!activityDirectory||!*activityDirectory){mediaStatus="Activity private directory unavailable.";KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::DirectoryMissing,"activity_directory_unavailable");return;}
        int activity=open(activityDirectory,O_RDONLY|O_DIRECTORY|O_CLOEXEC|O_NOFOLLOW);if(activity<0){if(embedded)return;mediaStatus="Activity private directory cannot be opened.";KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::DirectoryMissing,"activity_directory_unreadable",errno);return;}
        int assets=openat(activity,"assets",O_RDONLY|O_DIRECTORY|O_CLOEXEC|O_NOFOLLOW);close(activity);if(assets<0){if(embedded)return;mediaStatus="Private assets directory missing; install the media package.";KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::DirectoryMissing,"private_assets_missing",errno);return;}
        int root=openat(assets,"anime",O_RDONLY|O_DIRECTORY|O_CLOEXEC|O_NOFOLLOW);close(assets);if(root<0){if(embedded)return;mediaStatus="Private Anime directory missing; install the media package.";KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::DirectoryMissing,"anime_directory_missing",errno);return;}
        mediaStatus="Private Anime directory found; verify character/pack status below.";KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::DirectoryFound,"private_anime_directory_opened");
        if(!embedded)Load(root,"highschool_dxd_rias");DIR* directory=fdopendir(dup(root));
        if(directory){unsigned inspected=0;while(auto* entry=readdir(directory)){if(++inspected>256)break;
        std::string id=entry->d_name;if(id!="highschool_dxd_rias"&&KennyAssets::Token(id))Load(root,id);}closedir(directory);}close(root);
    }
    void ClearTextures(bool contextLost=false){for(unsigned i=0;i<count;++i){auto& c=characters[i];if(release&&!contextLost){if(c.artworkTexture.Valid())release(textureUser,c.artworkTexture);if(c.launcherTexture.Valid())release(textureUser,c.launcherTexture);}c.artworkTexture={};c.launcherTexture={};c.artTried=c.logoTried=false;}}
    void Prepare(KennyAppearance::Preferences& p,KennyAudio::Dispatcher* audio){
        if(!configured&&!directoryWarned){directoryWarned=true;mediaStatus="Private media has not been configured; activity directory unavailable.";KennyAudioDiagnostics::Log(KennyAudioDiagnostics::Code::DirectoryMissing,"activity_media_not_configured");}
        dispatchMixer=audio?audio->mixer:nullptr;
        if(audio){audio->voiceRouter=Route;audio->voiceUser=this;audio->Refresh(p);}
        if(p.theme!=KennyAppearance::Theme::Anime)return;
        auto& c=Selected(p);if(c.packCount&&!Pack(c,p.voicePack))p.voicePack=c.packs[0].id;
        if(c.artwork.size()<=63&&KennyAssets::Path(c.artwork))p.characterArtwork=c.artwork;
        if(activeCharacter!=p.characterId || activePack!=p.voicePack){if(dispatchMixer)dispatchMixer->voiceEpoch.fetch_add(1);ResetCooldowns();activeCharacter=p.characterId;activePack=p.voicePack;auto* installed=Pack(c,p.voicePack);KennyAudioDiagnostics::Log(installed?KennyAudioDiagnostics::Code::PackSelected:KennyAudioDiagnostics::Code::Unmapped,installed?"selected_installed_pack":"selected_pack_missing",0,installed?installed->id.c_str():"unavailable");}
        if(upload){if(!c.artTried&&!c.image.rgba.empty()){c.artTried=true;c.artworkTexture=upload(textureUser,c.image);}
            if(!c.logoTried&&!c.logo.rgba.empty()){c.logoTried=true;c.launcherTexture=upload(textureUser,c.logo);}}
    }
    bool Emit(VoiceEvent event,const KennyAppearance::Preferences& p,KennyAudio::Mixer* mixer,double time){
        using namespace KennyAudioDiagnostics;
        Log(Code::Received,"character_router",0,unsigned(event)<EventCount?EventNames[unsigned(event)]:"invalid");
        if(!mixer)return Report(Result::EngineUnavailable,event);
        if(p.theme!=KennyAppearance::Theme::Anime)return Report(Result::WrongTheme,event);
        if(!p.uiSounds)return Report(Result::SoundDisabled,event);
        if(!p.characterVoice)return Report(Result::VoiceDisabled,event);
        if(p.uiVolume<=0)return Report(Result::UiVolumeZero,event);
        if(p.characterVolume<=0)return Report(Result::VoiceVolumeZero,event);
        if(!std::isfinite(time)||unsigned(event)>=EventCount)return Report(Result::InvalidTime,event);
        auto* c=Find(p.characterId);if(!c)return Report(Result::WrongCharacter,event);
        auto* pack=Pack(*c,p.voicePack);if(!pack)return Report(Result::WrongPack,event);
        if(activeCharacter!=p.characterId || activePack!=p.voicePack){mixer->voiceEpoch.fetch_add(1);ResetCooldowns();activeCharacter=p.characterId;activePack=p.voicePack;Log(Code::PackSelected,"selected_registered_pack",0,activePack.c_str());}
        auto& e=pack->events[unsigned(event)];if(!e.count)return Report(pack->decodeFailed[unsigned(event)]?Result::DecodeFailed:Result::MissingRecording,event);
        if(time<lastTime)ResetCooldowns();lastTime=time;
        if(time<nextVoice || time<nextEvent[unsigned(event)])return Report(Result::Cooldown,event);
        random^=random<<13;random^=random>>17;random^=random<<5;unsigned index=random%e.count;if(e.count>1&&index==e.last)index=(index+1)%e.count;
        if(!mixer->SubmitRecording(&e.clips[index]))return Report(Result::QueueFull,event);
        e.last=index;nextEvent[unsigned(event)]=time+.7;nextVoice=time+std::max(.7,double(e.clips[index].samples.size())/KennyAudio::SampleRate+.12);return Report(Result::Queued,event);
    }
    KennyAudioDiagnostics::Result TestVoice(const KennyAppearance::Preferences& p,KennyAudio::Dispatcher* audio,double time){
        testAttempted=true;
        if(audio){audio->Refresh(p);if(audio->mixer){testStartedBefore=audio->mixer->transport.recordingsStarted.load();testCallbacksBefore=audio->mixer->transport.callbacks.load();}}
        Emit(testEvent,p,audio?audio->mixer:nullptr,time);testResult=lastResult;return testResult;
    }

    static bool Route(void* user,KennyAudio::Event event,const KennyAppearance::Preferences& p,double time,const char* label){
        auto& self=*static_cast<Registry*>(user);VoiceEvent voice;

        switch(event){case KennyAudio::Event::MenuOpen:voice=VoiceEvent::Open;break;
        case KennyAudio::Event::MenuClose:voice=VoiceEvent::Close;break;
        case KennyAudio::Event::ThemeChanged:voice=VoiceEvent::ThemeSwitch;break;
        case KennyAudio::Event::PrimaryNavigation:
            if(label&&std::strcmp(label,"Extra features")==0){voice=VoiceEvent::ExtraNavigation;break;}
            if(label&&std::strcmp(label,"Settings")==0){
                auto* c=self.Find(p.characterId);auto* pack=c?self.Pack(*c,p.voicePack):nullptr;
                if(pack&&pack->events[unsigned(VoiceEvent::SettingsNavigation)].count){voice=VoiceEvent::SettingsNavigation;break;}
            }
            voice=VoiceEvent::Navigation;break;
        case KennyAudio::Event::SecondaryNavigation:voice=label&&std::strcmp(label,"Extra features")==0?VoiceEvent::ExtraNavigation:VoiceEvent::Navigation;break;
        case KennyAudio::Event::CheckboxOn:
            voice=label&&std::strcmp(label,"Enable bullet track")==0?VoiceEvent::Bullet:
                  label&&std::strcmp(label,"Enable aimbot")==0?VoiceEvent::AimEnabled:VoiceEvent::Enabled;break;
        case KennyAudio::Event::CheckboxOff:
            voice=label&&std::strcmp(label,"Enable bullet track")==0?VoiceEvent::BulletDisabled:
                  label&&std::strcmp(label,"Enable aimbot")==0?VoiceEvent::AimDisabled:VoiceEvent::Disabled;break;
        case KennyAudio::Event::ButtonPressed:voice=VoiceEvent::Confirmation;break;
        case KennyAudio::Event::KeyAccepted:voice=VoiceEvent::LoginSuccess;break;
        case KennyAudio::Event::KeyRejected:voice=VoiceEvent::LoginFailure;break;
        default:return false;}
        if(voice==VoiceEvent::AimEnabled || voice==VoiceEvent::AimDisabled || voice==VoiceEvent::BulletDisabled || voice==VoiceEvent::ExtraNavigation){
            auto* c=self.Find(p.characterId);auto* pack=c?self.Pack(*c,p.voicePack):nullptr;
            if(pack&&!pack->events[unsigned(voice)].count){
                voice=voice==VoiceEvent::AimEnabled?VoiceEvent::Enabled:
                      voice==VoiceEvent::ExtraNavigation?VoiceEvent::Navigation:VoiceEvent::Disabled;
            }
        }
        if(!p.controlVoiceFeedback && (event==KennyAudio::Event::CheckboxOn || event==KennyAudio::Event::CheckboxOff || event==KennyAudio::Event::ButtonPressed))return self.Report(KennyAudioDiagnostics::Result::ControlDisabled,voice);
        return self.Emit(voice,p,KennyAudio::current.dispatcher?KennyAudio::current.dispatcher->mixer:self.dispatchMixer,time);
    }
    // Lifecycle events are dispatched outside menu scopes too.
    KennyAudio::Mixer* dispatchMixer=nullptr;std::string activeCharacter,activePack;
};
// Transparent cutout positioned inside content bounds. Contain preserves the
// entire face/hair, avoids a matte, and leaves controls in the foreground.
inline void DrawCharacter(ImDrawList* draw,ImVec2 origin,ImVec2 size,float radius,float contentY,
                          const KennyThemeBackground::ArtworkFrame& frame,const KennyAppearance::Preferences& p){
    if(!p.artworkVisible || !frame.Valid())return;
    const float margin=std::max(radius+2,24.0f);
    float height=std::max(1.0f,size.y-contentY-margin-6),width=std::min(size.x*.42f,size.x-2*margin);
    float scale=std::min(width/frame.width,height/frame.height);ImVec2 fitted(frame.width*scale,frame.height*scale);
    ImVec2 start(origin.x+size.x-fitted.x-margin,origin.y+size.y-fitted.y-margin);
    draw->PushClipRect(ImVec2(origin.x+radius,origin.y+contentY+6),ImVec2(origin.x+size.x-radius,origin.y+size.y-radius),true);
    draw->AddImage(frame.texture,start,ImVec2(start.x+fitted.x,start.y+fitted.y),ImVec2(0,0),ImVec2(1,1),ImGui::GetColorU32(ImVec4(1,1,1,1-p.artworkDim*.01f)));
    draw->PopClipRect();
}
} // namespace KennyCharacters
