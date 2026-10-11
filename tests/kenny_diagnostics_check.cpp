#include "KennyDiagnostics.h"
#include "KennyStartup.h"
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <signal.h>
#include <sys/wait.h>

static std::string Read(const std::string& path){std::ifstream f(path);return {std::istreambuf_iterator<char>(f),{}};}
static void Run(const char* self,const char* root,const char* label,bool crash=false){
    pid_t pid=fork();assert(pid>=0);
    if(pid==0){execl(self,self,root,label,crash?"crash":"normal",nullptr);_exit(127);}
    int status=0;assert(waitpid(pid,&status,0)==pid);
    if(crash)assert(WIFSIGNALED(status)&&WTERMSIG(status)==SIGKILL);else assert(WIFEXITED(status)&&WEXITSTATUS(status)==0);
}
int main(int argc,char** argv){
    using namespace KennyDiagnostics;
    if(argc==4){
        Event(1,Severity::Info,0,true,"early %s",argv[2]);
        assert(SetStorage(argv[1]));Event(2,Severity::Info,0,true,"durable %s",argv[2]);
        if(std::strcmp(argv[3],"crash")==0)kill(getpid(),SIGKILL);
        return 0;
    }
    char temp[]="/tmp/kenny-diagnostics-XXXXXX";assert(mkdtemp(temp));
    const std::string root=temp,reports=root+"/KennyPvtHax/CrashReports/";
    assert(!SetStorage(nullptr));assert(!SetStorage("relative"));assert(!SetStorage("/definitely-missing-kph-storage"));
    const std::string link=root+"/link";assert(symlink(root.c_str(),link.c_str())==0);assert(!SetStorage(link.c_str()));
    // Simulate an interrupted pending report without deleting its evidence.
    assert(mkdir((root+"/KennyPvtHax").c_str(),0700)==0);assert(mkdir(reports.c_str(),0700)==0);
    {std::ofstream f(reports+"startup-report.pending");f<<"interrupted evidence";}
    Run(argv[0],temp,"A",true);assert(Read(reports+"startup-report.txt").find("durable A")!=std::string::npos);
    assert(Read(reports+"startup-report.interrupted.txt")=="interrupted evidence");
    Run(argv[0],temp,"B");Run(argv[0],temp,"C");Run(argv[0],temp,"D");Run(argv[0],temp,"E");
    assert(Read(reports+"startup-report.txt").find("durable E")!=std::string::npos);
    assert(Read(reports+"startup-report.previous-1.txt").find("durable D")!=std::string::npos);
    assert(Read(reports+"startup-report.previous-2.txt").find("durable C")!=std::string::npos);
    assert(Read(reports+"startup-report.previous-3.txt").find("durable B")!=std::string::npos);
    const std::string denied=root+"/denied";assert(mkdir(denied.c_str(),0000)==0);
    if(geteuid()!=0)assert(!SetStorage(denied.c_str()));
    for(unsigned i=0;i<80;++i)Event(3,Severity::Info,0,true,"bounded-early-%u",i);
    assert(Get().count==EarlyCount);assert(SetStorage(temp));
    const std::string text=Read(reports+"startup-report.txt");assert(text.find("bounded-early-0\n")==std::string::npos);assert(text.find("bounded-early-79")!=std::string::npos);
    assert(text.find("tid=")!=std::string::npos&&text.find("code=")!=std::string::npos&&text.find("Z KPH-")!=std::string::npos);
    const size_t before=Get().bytes;
    for(unsigned i=0;i<20000;++i)Once(40,Severity::Info,0,true,"one event only");
    assert(Get().bytes>before&&Get().bytes<before+LineSize);
    std::vector<std::thread> threads;
    for(unsigned t=0;t<4;++t)threads.emplace_back([=]{for(unsigned n=0;n<200;++n)Event(41,Severity::Info,0,true,"thread=%u step=%u",t,n);});
    for(auto& t:threads)t.join();
    struct stat info{};assert(stat((reports+"startup-report.txt").c_str(),&info)==0);assert(size_t(info.st_size)<=ReportLimit);assert((info.st_mode&0777)==0600);
    int out=open((root+"/export.txt").c_str(),O_RDWR|O_CREAT|O_TRUNC,0600);assert(out>=0);assert(ExportToFd(out));close(out);
    assert(Read(root+"/export.txt")==Read(reports+"startup-report.txt"));
    assert(!ExportToFd(-1));out=open("/dev/full",O_WRONLY);assert(out>=0);assert(!ExportToFd(out));close(out);
    out=open((reports+"startup-report.txt").c_str(),O_WRONLY);assert(out>=0);assert(!ExportToFd(out));close(out);
    KennyStartup::Queue queue;KennyStartup::Input down;down.transition=true;down.down=true;
    auto up=down;up.down=false;assert(queue.Push(down));assert(queue.Push(up));unsigned applied=0;
    queue.Drain([&](auto event){++applied;assert(event.down);});assert(applied==1&&queue.count==1);
    queue.Drain([&](auto event){++applied;assert(!event.down);});assert(applied==2&&queue.count==0);
    down.x=-10;assert(queue.Push(down));KennyStartup::Input moved;moved.x=100;assert(queue.Push(moved));
    queue.Drain([](auto event){assert(event.transition&&event.x==-10);});assert(queue.count==1);
    queue.Drain([](auto event){assert(!event.transition&&event.x==100);});assert(queue.count==0);
    for(unsigned i=0;i<10000;++i){KennyStartup::Input move;move.x=float(i);queue.Push(move);}
    assert(queue.count==1);queue.Drain([](auto event){assert(event.x==9999);});
    for(unsigned i=0;i<65;++i)queue.Push(down);
    assert(queue.count<=64);
    // A real persistent append failure must degrade safely, independently of
    // the already-tested destination-export failure.
    const int reportFd=Get().report;
    const size_t reportBytes=Get().bytes;
    const int full=open("/dev/full",O_WRONLY);assert(full>=0);Get().report=full;
    Get().bytes=0; // Prior cap test must not bypass this separate I/O test.
    Event(42,Severity::Error,0,false,"persistent write failure test");
    assert(Get().ioFailed&&!SetStorage(temp));
    Get().report=reportFd;Get().bytes=reportBytes;close(full);
    std::puts("PASS independent startup logger: early bounded buffering, timestamps/TIDs/status, symlink/unavailable/permission failure, SIGKILL-persistent checkpoints, safe rotation/interrupted evidence, 64KiB cap, 0600 reports, concurrent writes, one-time events, authorized FD export/write failures; fixed input queue, coalescing/press-release/overflow recovery.");
}
