#include "recovery_fixture.h"
static KennyMenu::State menu;
static ImVec2 viewport(1920,872);
static bool visible=true;
static ImGuiWindow* content=nullptr;
static void Frame(ImVec2 mouse=ImVec2(-100,-100),bool down=false){
 auto& io=ImGui::GetIO();io.DisplaySize=viewport;io.DeltaTime=1.0f/60;io.MousePos=mouse;io.MouseDown[0]=down;controls.clear();ImGui::NewFrame();
 KennyMenu::Draw(menu,visible,Settings::Tab,viewport,[]{Panels();content=ImGui::GetCurrentWindow();});
 ImGui::Render();assert(ImGui::GetCurrentContext()->FontStack.Size==0&&ImGui::GetCurrentContext()->ColorStack.Size==0&&ImGui::GetCurrentContext()->StyleVarStack.Size==0);
}
static void Click(ImVec2 p){Frame(p);Frame(p,true);Frame(p);}
static void Select(KennyMenu::Category category){menu.Select(category,Settings::Tab);Frame();Frame();}
static void Capture(const char* name){auto* data=ImGui::GetDrawData();std::ofstream out(std::string(".verification/")+name+".draw",std::ios::binary);int header[]={int(viewport.x),int(viewport.y),data->CmdListsCount};out.write((char*)header,sizeof(header));
 for(int i=0;i<data->CmdListsCount;++i){auto* l=data->CmdLists[i];int sizes[]={l->VtxBuffer.Size,l->IdxBuffer.Size,l->CmdBuffer.Size};out.write((char*)sizes,sizeof(sizes));out.write((char*)l->VtxBuffer.Data,sizeof(ImDrawVert)*sizes[0]);out.write((char*)l->IdxBuffer.Data,sizeof(ImDrawIdx)*sizes[1]);for(auto& c:l->CmdBuffer){assert(!c.UserCallback);out.write((char*)&c.ClipRect,sizeof(c.ClipRect));unsigned values[]={c.ElemCount,c.IdxOffset,c.VtxOffset};out.write((char*)values,sizeof(values));}}
}
int main(){
 ImGui::CreateContext();auto& io=ImGui::GetIO();io.IniFilename=io.LogFilename=nullptr;
 // Use the original 16px base/15px merged icon inputs, with no additional menu
 // font. Test-only non-owning config permits fixture cleanup; Android init is
 // verified byte-for-byte against the device-proven source by the source gate.
 ImFontConfig cfg;cfg.FontDataOwnedByAtlas=false;io.Fonts->AddFontFromMemoryTTF((void*)Custom_data,Custom_size,16,&cfg);
 cfg.MergeMode=true;cfg.PixelSnapH=true;cfg.OversampleH=cfg.OversampleV=2;static const ImWchar ranges[]={ICON_MIN_FA,ICON_MAX_FA,0};io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome,sizeof(fontAwesome),15,&cfg,ranges);
 unsigned char* pixels;int w,h;io.Fonts->GetTexDataAsRGBA32(&pixels,&w,&h);std::ofstream atlas(".verification/recovery-atlas.rgba",std::ios::binary);atlas.write((char*)&w,4);atlas.write((char*)&h,4);atlas.write((char*)pixels,w*h*4);atlas.close();Claude::Apply();
 for(ImVec2 size:{ImVec2(2340,1080),ImVec2(1920,872),ImVec2(1280,720),ImVec2(960,540),ImVec2(640,360)}){
  viewport=size;
  for(auto category:{KennyMenu::Category::Visual,KennyMenu::Category::Aim,KennyMenu::Category::Misc,KennyMenu::Category::Style,KennyMenu::Category::Settings}){
   Select(category);auto* root=ImGui::FindWindowByName("KennyPvtHax");assert(root&&root->Pos.x>=0&&root->Pos.y>=0&&root->Pos.x+root->Size.x<=viewport.x+1&&root->Pos.y+root->Size.y<=viewport.y+1);
   if(category==KennyMenu::Category::Visual||category==KennyMenu::Category::Misc){int first=category==KennyMenu::Category::Visual?1:4;for(int tab:{first,first+1}){Settings::Tab=tab;Frame();Frame();assert(!controls.empty());ImGui::SetScrollY(content,content->ScrollMax.y);Frame();Frame();}}
  }
 }
 viewport=ImVec2(1920,872);Select(KennyMenu::Category::Visual);Settings::Tab=1;Frame();Frame();ImGui::SetScrollY(content,0);Frame();Frame();
 auto c=controls.at("ESP line");bool old=Cheat::Esp::Line;Click(c.GetCenter());assert(Cheat::Esp::Line!=old);Click(c.GetCenter());assert(Cheat::Esp::Line==old);Capture("recovery-player");
 auto* root=ImGui::FindWindowByName("KennyPvtHax");auto l=KennyMenu::Measure(viewport);ImVec2 start(root->Pos.x+l.padding+10,root->Pos.y+l.header*.3f);ImVec2 origin=root->Pos;Frame(start,true);Frame(ImVec2(start.x+40,start.y+30),true);Frame(ImVec2(start.x+40,start.y+30));assert(root->Pos.x>origin.x);
 Select(KennyMenu::Category::Aim);Capture("recovery-aim");const float range=Cheat::Aimbot::Range;
 auto r=controls.at("Aim range");Frame(r.GetCenter(),true);Frame(r.GetCenter());assert(Cheat::Aimbot::Range>=0&&Cheat::Aimbot::Range<=400);Cheat::Aimbot::Range=range;
 Select(KennyMenu::Category::Visual);Settings::Tab=2;Frame();Capture("recovery-world");Select(KennyMenu::Category::Misc);Settings::Tab=4;Frame();Capture("recovery-bullet");Settings::Tab=5;Frame();Capture("recovery-extra");
 // Native navigation hitboxes switch the real category.
 auto l2=KennyMenu::Measure(viewport);root=ImGui::FindWindowByName("KennyPvtHax");float close=std::max(36.0f,44*l2.scale);float left=l2.compact?l2.padding:l2.padding+l2.brand,right=l2.compact?l2.size.x-l2.padding:l2.size.x-l2.padding-close;
 Click(ImVec2(root->Pos.x+left+.5f*(right-left)/5,root->Pos.y+l2.navY+l2.navHeight*.5f));assert(menu.category==KennyMenu::Category::Visual);
 // Close/reopen preserves original selected feature state; no launcher/audio.
 Click(ImVec2(root->Pos.x+l2.size.x-l2.padding-close*.5f,root->Pos.y+(l2.compact?l2.navY:l2.header)*.5f));assert(!visible);visible=true;Frame();
 const int baseline=io.MetricsActiveAllocations;for(int n=0;n<1000;++n)Frame();assert(io.MetricsActiveAllocations==baseline);
 ImGui::DestroyContext();std::puts("PASS actual original widgets/ranges/conditions, 5 categories and 5 feature panels, 5 viewports/clipping/scroll, native checkbox/slider/navigation/drag/close, 1000 stable warmed allocation frames. Host fixture uses safe cleanup ownership only; production init unchanged. No Android runtime claim.");
}
