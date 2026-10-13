#pragma once
#include "KennyAssetIO.h"
#include "KennyAudio.h"
#include "KennyThemeBackground.h"
#include "Includes/json.hpp"
#include <array>
#include <dirent.h>

namespace KennyCharacters {
enum class VoiceEvent:unsigned {Open,Close,Navigation,LoginSuccess,LoginFailure,Enabled,Disabled,Skins,Bullet,Confirmation,Error,ThemeSwitch,SettingsNavigation,Count};
constexpr unsigned EventCount=unsigned(VoiceEvent::Count);
inline constexpr const char* EventNames[]={"launcher_open","launcher_close","menu_navigation","login_success","login_failure","feature_enabled","feature_disabled","skins_enabled","bullet_track_enabled","confirmation","error","theme_switch","settings_navigation"};
struct EventClips {std::array<KennyAudio::Recording,3> clips;unsigned count=0,last=3;};
struct VoicePack {std::string id,name;std::array<EventClips,EventCount> events;bool Available()const{for(const auto& e:events)if(e.count)return true;return false;}};
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
    std::array<Character,8> characters;unsigned count=1;bool configured=false;
    Upload upload=nullptr;Release release=nullptr;void* textureUser=nullptr;
    double nextVoice=0,lastTime=0;uint32_t random=0x7139c5;
    size_t decodedBytes=0;
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
    bool Image(int fd,const std::string& file,KennyAssets::Image& image){
        std::vector<uint8_t> bytes;if(file.size()<4||file.substr(file.size()-4)!=".png"||!KennyAssets::Read(fd,file,8*1024*1024,bytes)||!KennyAssets::PNG(bytes,image))return false;
        if(decodedBytes+image.rgba.size()>32*1024*1024){image={};return false;}decodedBytes+=image.rgba.size();return true;
    }
private:
    bool Load(int root,const std::string& folder){
        if(!KennyAssets::Token(folder))return false;
        int fd=openat(root,folder.c_str(),O_RDONLY|O_DIRECTORY|O_CLOEXEC|O_NOFOLLOW);if(fd<0)return false;
        std::vector<uint8_t> bytes;nlohmann::json j;
        bool valid=KennyAssets::Read(fd,"manifest.json",32768,bytes)&&JSON(bytes,j);
        auto schema=valid?j.find("schema"):j.end();valid=valid&&schema!=j.end()&&schema->is_number_integer()&&*schema==1&&Text(j,"id")==folder;
        if(!valid){close(fd);return false;}Character* c=Find(folder);
        if(!c){if(count>=characters.size()){close(fd);return false;}c=&characters[count++];}
        c->id=folder;c->name=Text(j,"name",folder);c->series=Text(j,"series","Unknown series");
        c->artwork=Text(j,"artwork","character.png");c->launcher=Text(j,"launcher","launcher.png");
        const bool artwork=Image(fd,c->artwork,c->image),logo=Image(fd,c->launcher,c->logo);
        auto voices=j.find("voice_packs");if(voices!=j.end()&&voices->is_array()&&voices->size()<=4){
            for(const auto& v:*voices){if(!v.is_object())continue;auto id=Text(v,"id");if(!KennyAssets::Token(id)||Pack(*c,id))continue;
                auto& pack=c->packs[c->packCount];pack.id=id;pack.name=Text(v,"name",id);auto mapping=v.find("events");
                if(mapping!=v.end()&&mapping->is_object())for(unsigned e=0;e<EventCount;++e){
                    auto clips=mapping->find(EventNames[e]);if(clips==mapping->end()||!clips->is_array()||clips->size()>3)continue;
                    auto& event=pack.events[e];
                    for(const auto& value:*clips){if(!value.is_string())continue;auto path=value.get<std::string>();
                        if(path.size()<4||path.substr(path.size()-4)!=".wav"||!KennyAssets::Read(fd,path,1048576,bytes))continue;
                        auto& clip=event.clips[event.count];if(!KennyAssets::WAV(bytes,clip.samples))continue;
                        if(decodedBytes+clip.samples.size()*2>32*1024*1024){clip=KennyAudio::Recording{};continue;}
                        decodedBytes+=clip.samples.size()*2;++event.count;
                    }
                }
                if(pack.Available())++c->packCount;else pack={};
            }
        }
        c->status=c->Installed()?"Artwork, launcher and optional voices loaded.":artwork||logo||c->packCount?"Partially installed; missing assets use safe fallbacks.":"Assets missing or invalid; K launcher and UI tones remain available.";
        close(fd);return true;
    }
public:
    void Configure(const char* activityDirectory){
        if(configured)return;
        configured=true;if(!activityDirectory||!*activityDirectory)return;
        int activity=open(activityDirectory,O_RDONLY|O_DIRECTORY|O_CLOEXEC|O_NOFOLLOW);if(activity<0)return;
        int assets=openat(activity,"assets",O_RDONLY|O_DIRECTORY|O_CLOEXEC|O_NOFOLLOW);close(activity);if(assets<0)return;
        int root=openat(assets,"anime",O_RDONLY|O_DIRECTORY|O_CLOEXEC|O_NOFOLLOW);close(assets);if(root<0)return;
        Load(root,"highschool_dxd_rias");DIR* directory=fdopendir(dup(root));
        if(directory){unsigned inspected=0;while(auto* entry=readdir(directory)){if(++inspected>256)break;
        std::string id=entry->d_name;if(id!="highschool_dxd_rias"&&KennyAssets::Token(id))Load(root,id);}closedir(directory);}close(root);
    }
    void ClearTextures(bool contextLost=false){for(unsigned i=0;i<count;++i){auto& c=characters[i];if(release&&!contextLost){if(c.artworkTexture.Valid())release(textureUser,c.artworkTexture);if(c.launcherTexture.Valid())release(textureUser,c.launcherTexture);}c.artworkTexture={};c.launcherTexture={};c.artTried=c.logoTried=false;}}
    void Prepare(KennyAppearance::Preferences& p,KennyAudio::Dispatcher* audio){
        dispatchMixer=audio?audio->mixer:nullptr;
        if(audio){audio->voiceRouter=Route;audio->voiceUser=this;audio->Refresh(p);}
        if(p.theme!=KennyAppearance::Theme::Anime)return;
        auto& c=Selected(p);if(c.packCount&&!Pack(c,p.voicePack))p.voicePack=c.packs[0].id;
        if(c.artwork.size()<=63&&KennyAssets::Path(c.artwork))p.characterArtwork=c.artwork;
        if(activeCharacter!=p.characterId || activePack!=p.voicePack){if(dispatchMixer)dispatchMixer->voiceEpoch.fetch_add(1);nextVoice=0;activeCharacter=p.characterId;activePack=p.voicePack;}
        if(upload){if(!c.artTried&&!c.image.rgba.empty()){c.artTried=true;c.artworkTexture=upload(textureUser,c.image);}
            if(!c.logoTried&&!c.logo.rgba.empty()){c.logoTried=true;c.launcherTexture=upload(textureUser,c.logo);}}
    }
    bool Emit(VoiceEvent event,const KennyAppearance::Preferences& p,KennyAudio::Mixer* mixer,double time){
        if(!mixer||p.theme!=KennyAppearance::Theme::Anime||!p.uiSounds||!p.characterVoice||p.uiVolume<=0||p.characterVolume<=0||!std::isfinite(time)||unsigned(event)>=EventCount)return false;
        auto* c=Find(p.characterId);if(!c)return false;
        auto* pack=Pack(*c,p.voicePack);if(!pack)return false;
        // A successful selector can emit before the next Prepare. Cancel the
        // old pack first so that next-frame synchronization keeps this clip.
        if(activeCharacter!=p.characterId || activePack!=p.voicePack){mixer->voiceEpoch.fetch_add(1);nextVoice=0;activeCharacter=p.characterId;activePack=p.voicePack;}
        auto& e=pack->events[unsigned(event)];if(!e.count)return false;
        if(time<lastTime)nextVoice=0;
        lastTime=time;if(time<nextVoice)return true; // mapped cooldown suppresses extra feedback
        random^=random<<13;random^=random>>17;random^=random<<5;unsigned index=random%e.count;if(e.count>1&&index==e.last)index=(index+1)%e.count;
        const auto* clip=&e.clips[index];if(!mixer->SubmitRecording(clip))return true;
        e.last=index;nextVoice=time+std::max(.7,double(clip->samples.size())/KennyAudio::SampleRate+.12);return true;
    }
    static bool Route(void* user,KennyAudio::Event event,const KennyAppearance::Preferences& p,double time,const char* label){
        auto& self=*static_cast<Registry*>(user);VoiceEvent voice;
        if(!p.controlVoiceFeedback && (event==KennyAudio::Event::CheckboxOn || event==KennyAudio::Event::CheckboxOff || event==KennyAudio::Event::ButtonPressed))return false;
        switch(event){case KennyAudio::Event::MenuOpen:voice=VoiceEvent::Open;break;
        case KennyAudio::Event::MenuClose:voice=VoiceEvent::Close;break;
        case KennyAudio::Event::ThemeChanged:voice=VoiceEvent::ThemeSwitch;break;
        case KennyAudio::Event::PrimaryNavigation:
            if(label&&std::strcmp(label,"Settings")==0){
                auto* c=self.Find(p.characterId);auto* pack=c?self.Pack(*c,p.voicePack):nullptr;
                if(pack&&pack->events[unsigned(VoiceEvent::SettingsNavigation)].count){voice=VoiceEvent::SettingsNavigation;break;}
            }
            voice=VoiceEvent::Navigation;break;
        case KennyAudio::Event::SecondaryNavigation:voice=VoiceEvent::Navigation;break;
        case KennyAudio::Event::CheckboxOn:voice=label&&std::strcmp(label,"Enable bullet track")==0?VoiceEvent::Bullet:VoiceEvent::Enabled;break;
        case KennyAudio::Event::CheckboxOff:voice=VoiceEvent::Disabled;break;
        case KennyAudio::Event::ButtonPressed:voice=VoiceEvent::Confirmation;break;
        case KennyAudio::Event::KeyAccepted:voice=VoiceEvent::LoginSuccess;break;
        case KennyAudio::Event::KeyRejected:voice=VoiceEvent::LoginFailure;break;
        default:return false;}
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
