#include "KennyPresentationMedia.h"
#include "KennyAppearanceStore.h"
#include <cassert>
#include <fstream>
#include <filesystem>
#include <cstdio>
using namespace KennyPresentation;
static unsigned uploads=0,releases=0;
static KennyThemeBackground::ArtworkFrame Upload(void*,const KennyAssets::Image& image){++uploads;return {reinterpret_cast<ImTextureID>(uintptr_t(uploads+100)),int(image.width),int(image.height)};}
static void Release(void*,KennyThemeBackground::ArtworkFrame){++releases;}
int main(int argc,char** argv){
 assert(argc==2);Assets assets;assets.Configure(argv[1]);assert(assets.configured&&assets.video>=0);
 assert(assets.logo.width==1280&&assets.logo.height==1280&&!assets.logo.transparent&&!assets.logo.rgba.empty());
 assert(assets.poster.rgba.empty());assets.upload=Upload;assets.release=Release;assets.Prepare(false);assert(uploads==1&&assets.logoTexture.Valid()&&!assets.posterTexture.Valid());
 assets.Prepare(true);assert(uploads==2&&assets.posterTexture.Valid()&&assets.poster.width==1024&&assets.poster.height==576);
 for(int i=0;i<1000;++i)assets.Prepare();
 assert(uploads==2);
 assets.ClearTextures(false);assert(releases==2&&!assets.logoTexture.Valid());assets.Prepare();assert(uploads==4);
 assets.ClearTextures(true);assert(releases==2);assets.Prepare();assert(uploads==6);
 std::vector<uint8_t> bytes;assert(KennyAssets::Read(assets.root,"launcher.png",8*1024*1024,bytes));KennyAssets::Image original;
 assert(!KennyAssets::PNG(bytes,original));assert(KennyAssets::PNG(bytes,original,false)&&original.rgba==assets.logo.rgba);
 bytes[bytes.size()/2]^=1;assert(!KennyAssets::PNG(bytes,original,false));
 const auto now=std::chrono::steady_clock::now();Clock clock;assert(clock.Due(1000,now)==now);
 assert(clock.Due(34000,now)==now+std::chrono::microseconds(33000));clock.Pause();auto resumed=now+std::chrono::seconds(100);
 assert(clock.Due(1000000,resumed)==resumed);assert(clock.Due(500,resumed)==resumed);
 char pattern[]="/tmp/kenny-presentation-XXXXXX";const char* temp=mkdtemp(pattern);assert(temp);auto root=std::filesystem::path(temp);
 KennyAppearance::Preferences p;KennyAppearance::Store store;store.Configure(temp,p);p.theme=KennyAppearance::Theme::Anime;p.animeVideo=false;p.voicePack="user_supplied_events";p.electricLightning=29;
 store.Sync(p,true);KennyAppearance::Store reload;KennyAppearance::Preferences restored;reload.Configure(temp,restored);assert(KennyAppearance::Equal(p,restored));
 // A genuine schema-5 file retains all existing preferences and enables only
 // the new optional video preference by default.
 std::string schema5="KennyPvtHaxAppearance 5\n1 89 1 0 20 30 0 1 85 1\n1 50 2\nhighschool_dxd_rias user_supplied_events character.png 1 75 0\n1 1\n1 2 29 55 50 1 0\n";
 {std::ofstream f(store.path);f<<schema5;}KennyAppearance::Store legacy;KennyAppearance::Preferences migrated;legacy.Configure(temp,migrated);assert(migrated.animeVideo&&migrated.opacity==89&&migrated.electricLightning==29&&migrated.voicePack=="user_supplied_events");
 schema5.replace(schema5.find('5'),1,"6");for(const char* bad:{"2\n","0\ntrailing",""}){
  {std::ofstream f(store.path);f<<schema5<<bad;}KennyAppearance::Store invalid;KennyAppearance::Preferences value;invalid.Configure(temp,value);assert(KennyAppearance::Equal(value,migrated));assert(std::strstr(invalid.status,"Anime video preference invalid"));
 }
 std::filesystem::create_directories(root/"assets/presentation");
 std::filesystem::copy_file(std::filesystem::path(argv[1])/"assets/presentation/manifest.json",root/"assets/presentation/manifest.json");
 Assets missing;missing.Configure(temp);missing.upload=Upload;missing.Prepare();assert(missing.video<0&&!missing.logoTexture.Valid()&&!missing.posterTexture.Valid());
 // Untrusted paths and irregular files are never passed to the decoder.
 assert(KennyAssets::Path("launcher.png")&&!KennyAssets::Path("../launcher.png"));
 symlink((std::filesystem::path(argv[1])/"assets/presentation/anime-background.mp4").c_str(),(root/"assets/presentation/anime-background.mp4").c_str());
 Assets symlinked;symlinked.Configure(temp);assert(symlinked.video<0);
 unlink((root/"assets/presentation/anime-background.mp4").c_str());mkfifo((root/"assets/presentation/anime-background.mp4").c_str(),0600);
 Assets pipe;pipe.Configure(temp);assert(pipe.video<0);unlink((root/"assets/presentation/anime-background.mp4").c_str());
 {std::ofstream f(root/"assets/presentation/manifest.json");f<<"{\"schema\":1,\"logo\":\"../logo.png\"}";}Assets invalid;invalid.Configure(temp);assert(invalid.video<0&&invalid.root<0);
 std::filesystem::remove_all(root);assets.ClearTextures(false);
 puts("PASS real supplied opaque PNG decode/alpha policy, corruption, optional media/fallback, lazy uploads and owner cleanup, symlink/FIFO/path rejection, descriptor bounds, video pacing/pause/loop timestamps, schema 5 migration/6 persistence/corruption. Host checks do not validate Android MediaCodec/GPU playback.");
}
