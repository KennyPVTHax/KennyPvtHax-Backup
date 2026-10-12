#include "KennyAppearanceStore.h"
#include <cassert>
#include <fstream>
#include <sys/stat.h>
#include <sys/wait.h>
#include <signal.h>
static bool shortWrites=false,interrupt=false,full=false,failDirectorySync=false;
static unsigned writes=0;
extern "C" ssize_t __real_write(int,const void*,size_t);
extern "C" int __real_fsync(int);
extern "C" ssize_t __wrap_write(int fd,const void* data,size_t n){++writes;if(full){errno=ENOSPC;return -1;}if(interrupt){interrupt=false;errno=EINTR;return -1;}return __real_write(fd,data,shortWrites?std::min(n,size_t(7)):n);}
extern "C" int __wrap_fsync(int fd){struct stat st{};if(failDirectorySync&&fstat(fd,&st)==0&&S_ISDIR(st.st_mode)){errno=EIO;return -1;}return __real_fsync(fd);}
static std::string Read(const std::string& p){std::ifstream f(p);return {std::istreambuf_iterator<char>(f),{}};}
int main(){using namespace KennyAppearance;char temp[]="/tmp/kenny-storage-audit-XXXXXX";assert(mkdtemp(temp));Preferences p;Store store;store.Configure(temp,p);p.opacity=89;
 shortWrites=interrupt=true;assert(store.Save(p));assert(writes>5);shortWrites=false;
 Store restart;Preferences q;restart.Configure(temp,q);assert(Equal(p,q));
 const auto original=Read(store.path);full=true;p.opacity=90;assert(!store.Save(p));assert(Read(store.path)==original);full=false;
 // A failed adjustment remains dirty, retries are bounded and recover unchanged state.
 p.opacity=91;writes=0;full=true;store.Sync(p,true,100);unsigned once=writes;
 for(unsigned i=0;i<1000;++i)store.Sync(p,true,100.2);assert(writes==once);
 full=false;store.Sync(p,true,102);Store recovered;recovered.Configure(temp,q);assert(Equal(p,q));
 unsigned saved=writes;for(unsigned i=0;i<1000;++i)store.Sync(p,true,200+i);assert(writes==saved);
 // Final file remains usable when directory durability cannot be confirmed.
 p.opacity=92;failDirectorySync=true;assert(!store.Save(p));failDirectorySync=false;Store disk;disk.Configure(temp,q);assert(Equal(p,q));
 // Oversized direct Save cannot read beyond its format buffer or touch old evidence.
 const auto before=Read(store.path);p.characterId.assign(2000,'a');assert(!store.Save(p));assert(Read(store.path)==before);
 unlink(store.path.c_str());assert(mkfifo(store.path.c_str(),0600)==0);
 pid_t child=fork();assert(child>=0);if(!child){alarm(2);Store fifo;Preferences value;fifo.Configure(temp,value);assert(Equal(value,Preferences{}));_exit(0);}int status;waitpid(child,&status,0);assert(WIFEXITED(status)&&WEXITSTATUS(status)==0);
 unlink(store.path.c_str());assert(symlink("/dev/zero",store.path.c_str())==0);Store symlink;Preferences value;symlink.Configure(temp,value);assert(Equal(value,Preferences{}));unlink(store.path.c_str());
 {std::ofstream f(store.path);f<<std::string(2048,'x');}Store oversized;oversized.Configure(temp,value);assert(Equal(value,Preferences{}));
 // Interrupted staging files cannot replace the committed file.
 std::ofstream(store.path+".tmp-stale")<<"partial";assert(Read(store.path).size()==2048);
 unlink(store.path.c_str());unlink((store.path+".tmp-stale").c_str());rmdir(temp);
 std::puts("PASS regular bounded preference reads; real FIFO/symlink/oversize fallback; EINTR and short writes; ENOSPC preserves old file; directory-fsync failure; bounded retry/recovery without idle writes; oversized formatting and interrupted staging.");
}
