// Real production draw lists. No host test-engine hooks/map instrumentation.
#include "kenny_benchmark_fixture.h"
#include "KennyLauncher.h"
#include "KennyDiagnostics.h"
#include <chrono>
#include <algorithm>
#include <memory>
static size_t calls=0,live=0;
static void* Allocate(size_t n,void*){void* p=std::malloc(n);if(p){++calls;++live;}return p;}
static void Free(void* p,void*){if(p){--live;std::free(p);}}
using Clock=std::chrono::steady_clock;
static double Ms(Clock::time_point t){return std::chrono::duration<double,std::milli>(Clock::now()-t).count();}
int main(){
 ImGui::SetAllocatorFunctions(Allocate,Free);auto start=Clock::now();ImGui::CreateContext();
 auto& io=ImGui::GetIO();io.IniFilename=io.LogFilename=nullptr;io.DisplaySize=ImVec2(1920,872);
 ImFontConfig cfg;cfg.FontDataOwnedByAtlas=false;io.Fonts->AddFontFromMemoryTTF((void*)Custom_data,Custom_size,16,&cfg);
 cfg.MergeMode=true;cfg.PixelSnapH=true;static const ImWchar range[]={ICON_MIN_FA,ICON_MAX_FA,0};
 io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome,sizeof(fontAwesome),15,&cfg,range);
 cfg.MergeMode=false;KennyMenu::Font=io.Fonts->AddFontFromMemoryTTF((void*)Custom_data,Custom_size,32,&cfg);
 cfg.MergeMode=true;io.Fonts->AddFontFromMemoryTTF((void*)fontAwesome,sizeof(fontAwesome),30,&cfg,range);
 unsigned char* pixels=nullptr;int width=0,height=0;io.Fonts->GetTexDataAsRGBA32(&pixels,&width,&height);Claude::Apply();
 std::printf("{\"host_only\":true,\"viewport\":[1920,872],\"font_cpu_init_ms\":%.4f,\"font_rgba_bytes\":%zu,\"cases\":[",Ms(start),size_t(width)*height*4);
 KennyMenu::State menu;KennyLauncher::State launcher;int tab=1;bool opened=true,first=true;
 for(int mode=0;mode<5;++mode)for(int fps:{30,60,90,120}){
  menu.appearance.theme=mode==1?KennyAppearance::Theme::Classic:mode==2?KennyAppearance::Theme::Anime:KennyAppearance::Theme::Aurora;
  menu.appearance.reducedMotion=mode==3;menu.category=KennyMenu::Category::Visual;tab=1;
  std::vector<double> times;times.reserve(600);unsigned vertices=0,indices=0,commands=0;size_t allocated=0,before=0;
  for(int f=0;f<720;++f){io.DeltaTime=1.0f/fps;io.MousePos=ImVec2(-100,-100);io.MouseDown[0]=false;
   if(f==120){before=calls;allocated=live;}auto tick=Clock::now();ImGui::NewFrame();
   if(mode==4)KennyLauncher::Draw(launcher,menu.appearance,nullptr,io.DisplaySize);
   else KennyMenu::Draw(menu,opened,tab,io.DisplaySize,[]{Panels();});
   ImGui::Render();if(f>=120)times.push_back(Ms(tick));auto* d=ImGui::GetDrawData();vertices=std::max(vertices,unsigned(d->TotalVtxCount));indices=std::max(indices,unsigned(d->TotalIdxCount));
   unsigned n=0;for(int j=0;j<d->CmdListsCount;++j)n+=d->CmdLists[j]->CmdBuffer.Size;commands=std::max(commands,n);
  }
  assert(live==allocated);const size_t newCalls=calls-before;double sum=0;for(double t:times)sum+=t;std::sort(times.begin(),times.end());
  std::printf("%s{\"mode\":\"%s\",\"hz\":%d,\"cpu_mean_ms\":%.5f,\"cpu_p95_ms\":%.5f,\"cpu_max_ms\":%.5f,\"vertices\":%u,\"indices\":%u,\"draw_commands\":%u,\"imgui_allocations_600\":%zu,\"live_allocations\":%zu}",first?"":",",mode==0?"aurora":mode==1?"classic":mode==2?"anime_missing":mode==3?"aurora_reduced":"launcher",fps,sum/times.size(),times[times.size()*95/100],times.back(),vertices,indices,commands,newCalls,live);first=false;
 }
 std::printf("],");start=Clock::now();auto bank=std::make_unique<KennyAudio::Bank>();bank->Initialize();std::printf("\"pcm_bank_init_ms\":%.5f,",Ms(start));
 char path[]="/tmp/kenny-perf-XXXXXX";assert(mkdtemp(path));start=Clock::now();assert(KennyDiagnostics::SetStorage(path));double storage=Ms(start);
 start=Clock::now();for(unsigned i=0;i<32;++i)KennyDiagnostics::Event(41,KennyDiagnostics::Severity::Info,0,true,"benchmark milestone");
 std::printf("\"logger_storage_ms\":%.5f,\"logger_32_durable_events_ms\":%.5f,\"sizeof_aurora\":%zu,\"sizeof_audio_bank\":%zu}\n",storage,Ms(start),sizeof(KennyAurora::State),sizeof(KennyAudio::Bank));
 ImGui::DestroyContext();assert(!live);
}
