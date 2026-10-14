#define KENNY_C3_CAPTURE_NO_MAIN
#include "kenny_c3_capture.cpp"
#include "KennyPresentationMedia.h"
#include <set>
static KennyPresentation::Assets media;
static KennyAssets::Image video;
static KennyThemeBackground::ArtworkFrame UploadMedia(void*,const KennyAssets::Image& im){return {reinterpret_cast<ImTextureID>(uintptr_t(im.width==im.height?3:4)),int(im.width),int(im.height)};}
static KennyThemeBackground::ArtworkFrame UploadCharacter(void*,const KennyAssets::Image& im){return {reinterpret_cast<ImTextureID>(2),int(im.width),int(im.height)};}
static void SaveMedia(const char* name){
 const auto* data=ImGui::GetDrawData();std::set<uint64_t> used;
 for(int i=0;i<data->CmdListsCount;++i)for(const auto& c:data->CmdLists[i]->CmdBuffer)used.insert(reinterpret_cast<uintptr_t>(c.GetTexID()));
 if(std::strstr(name,"anime-video-")&&std::strcmp(name,"anime-video-off")!=0)assert(!used.count(2));
 std::vector<std::pair<uint64_t,const KennyAssets::Image*>> textures;
 auto add=[&](uint64_t id,const KennyAssets::Image& image){if(used.count(id)&&!image.rgba.empty())textures.emplace_back(id,&image);};
 add(2,menu.characters.characters[0].image);add(3,media.logo);add(4,media.poster);add(5,video);
 std::ofstream out(std::string(".verification/video-logo-")+name+".draw",std::ios::binary);
 const int header[]={-int(viewport.x),int(viewport.y),data->CmdListsCount};out.write((char*)header,sizeof(header));uint32_t count=textures.size();out.write((char*)&count,4);
 for(auto t:textures){out.write((char*)&t.first,8);out.write((char*)&t.second->width,4);out.write((char*)&t.second->height,4);out.write((char*)t.second->rgba.data(),t.second->rgba.size());}
 for(int i=0;i<data->CmdListsCount;++i){const auto* list=data->CmdLists[i];int sizes[]={list->VtxBuffer.Size,list->IdxBuffer.Size,list->CmdBuffer.Size};out.write((char*)sizes,sizeof(sizes));out.write((char*)list->VtxBuffer.Data,list->VtxBuffer.Size*sizeof(ImDrawVert));out.write((char*)list->IdxBuffer.Data,list->IdxBuffer.Size*sizeof(ImDrawIdx));
  for(const auto& c:list->CmdBuffer){assert(!c.UserCallback);out.write((char*)&c.ClipRect,sizeof(ImVec4));unsigned fields[]={c.ElemCount,c.IdxOffset,c.VtxOffset};out.write((char*)fields,sizeof(fields));uint64_t id=reinterpret_cast<uintptr_t>(c.GetTexID());out.write((char*)&id,8);}
 }
}
int main(int argc,char** argv){
 assert(argc==3);InitializeC3Capture();const auto features=SnapshotFeatures();
 media.Configure(argv[1]);media.upload=UploadMedia;media.Prepare();assert(media.logoTexture.Valid()&&media.posterTexture.Valid());
 menu.characters.Configure(argv[2]);menu.characters.upload=UploadCharacter;menu.appearance.theme=KennyAppearance::Theme::Anime;
 menu.appearance.voicePack="user_supplied_events";menu.animeVideoFrame=media.posterTexture;menu.brandLogo=media.logoTexture;
 menu.videoStatus="Actual supplied video frame / offline FFmpeg decode. Android decoder unverified.";
 for(int i=0;i<40;++i)Frame();ResetScroll();SaveMedia("anime-still-fallback");
 Primary(4);ResetScroll();Frame();Frame();
 auto control=Native("Anime Video Background");ImGui::SetScrollY(panelWindow,panelWindow->Scroll.y+control.min.y-panelWindow->InnerRect.Min.y-45);Frame();Frame();SaveMedia("anime-settings");
 Click(NativeCenter("Anime Video Background"));assert(!menu.appearance.animeVideo);Click(NativeCenter("Anime Video Background"));assert(menu.appearance.animeVideo);
 Primary(0);ResetScroll();Frame();
 menu.appearance.animeVideo=false;Frame();SaveMedia("anime-video-off");menu.appearance.animeVideo=true;
 KennyLauncher::State launcher;launcher.logo.Set(media.logoTexture);auto& io=ImGui::GetIO();
 io.MousePos=ImVec2(-100,-100);io.MouseDown[0]=false;ImGui::NewFrame();KennyLauncher::Draw(launcher,menu.appearance,nullptr,viewport);ImGui::Render();SaveMedia("photo-launcher");
 // New art changes no hitboxes: native tap/drag remain the existing functions.
 auto launcherFrame=[&](ImVec2 p,bool down){io.DisplaySize=viewport;io.MousePos=p;io.MouseDown[0]=down;ImGui::NewFrame();KennyLauncher::Draw(launcher,menu.appearance,nullptr,viewport);ImGui::Render();};
 launcherFrame(ImVec2(30,30),false);launcherFrame(ImVec2(30,30),true);launcherFrame(ImVec2(80,90),true);launcherFrame(ImVec2(80,90),false);assert(!launcher.target&&launcher.dragged);
 const ImVec2 touch(launcher.position.x+20,launcher.position.y+20);launcherFrame(touch,false);launcherFrame(touch,true);launcherFrame(touch,false);assert(launcher.target);
 Frame();viewport=ImVec2(1280,720);menu.centerRequested=true;Frame();Frame();
 for(int i=0;i<49;++i){char file[100];std::snprintf(file,sizeof(file),".verification/video-logo-frames/%03d.png",i);std::ifstream f(file,std::ios::binary);std::vector<uint8_t> bytes((std::istreambuf_iterator<char>(f)),{});assert(KennyAssets::PNG(bytes,video,false));
  menu.animeVideoFrame={reinterpret_cast<ImTextureID>(5),int(video.width),int(video.height)};for(int j=0;j<5;++j)Frame();char name[32];std::snprintf(name,sizeof(name),"motion-%03d",i);SaveMedia(name);
  if(i==0||i==24||i==48){std::snprintf(name,sizeof(name),"anime-video-%02d",i/12);SaveMedia(name);}
 }
 viewport=ImVec2(640,360);menu.centerRequested=true;Frame();Frame();SaveMedia("anime-small");
 menu.appearance.reducedMotion=true;const auto held=menu.animeVideoFrame;for(int i=0;i<30;++i)Frame();assert(menu.animeVideoFrame.texture==held.texture);SaveMedia("anime-reduced-still");
 menu.animeVideoFrame={};menu.characters.ClearTextures(true);Frame();SaveMedia("missing-media-fallback");
 assert(features==SnapshotFeatures());ImGui::DestroyContext();puts("PASS actual native menu/photo input, supplied decoded video frames behind controls without foreground Rias, toggle/off/reduced/missing/small states, unchanged feature snapshot. Android hardware decoding/GPU playback remains unverified.");
}
