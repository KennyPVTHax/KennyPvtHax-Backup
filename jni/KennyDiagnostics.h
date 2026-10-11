#pragma once
// Independent of ImGui, EGL, assets and audio. Never call from signal handlers.
#include <cerrno>
#include <cstdarg>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <cstdint>
#include <atomic>
#include <fcntl.h>
#include <pthread.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <unistd.h>
#ifdef __ANDROID__
#include <android/log.h>
#endif
#ifndef KPH_BUILD_ID
#define KPH_BUILD_ID "local-unknown"
#endif

namespace KennyDiagnostics {
enum class Severity { Info, Warning, Error, Fatal };
constexpr size_t LineSize=512, EarlyCount=64, ReportLimit=65536;
struct State {
    pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
    int directory=-1, report=-1;
    size_t bytes=0, count=0, start=0;
    bool ioFailed=false;
    std::atomic<uint64_t> once{0};
    std::atomic<uint64_t> warned{0};
    char early[EarlyCount][LineSize]{};
};
inline State& Get(){static State state;return state;}
struct Lock {
    State& state;
    explicit Lock(State& s):state(s){pthread_mutex_lock(&state.mutex);}
    ~Lock(){pthread_mutex_unlock(&state.mutex);}
};
inline const char* Name(Severity s){switch(s){case Severity::Warning:return "WARNING";case Severity::Error:return "ERROR";case Severity::Fatal:return "FATAL";default:return "INFO";}}
inline bool WriteAll(int fd,const char* data,size_t size){
    while(size){ssize_t n=write(fd,data,size);if(n<0&&errno==EINTR)continue;if(n<=0)return false;data+=n;size-=size_t(n);}return true;
}
inline void Append(State& s,const char* line){
    const size_t length=strnlen(line,LineSize);
    if(s.report>=0){
        if(s.ioFailed)return;
        if(s.bytes+length>ReportLimit)return;
        bool written=WriteAll(s.report,line,length);
        if(written)s.bytes+=length;
        if(!written||fsync(s.report)!=0){
            s.ioFailed=true;
#ifdef __ANDROID__
            __android_log_print(ANDROID_LOG_ERROR,"KennyPvtHax","Persistent checkpoint write failed code=%d; retain logcat evidence",errno);
#endif
        }
    }else{
        const size_t index=(s.start+s.count)%EarlyCount;
        std::snprintf(s.early[index],LineSize,"%s",line);
        if(s.count<EarlyCount)++s.count;else s.start=(s.start+1)%EarlyCount;
    }
}
inline void Event(unsigned stage,Severity severity,int error,bool success,const char* format,...){
    char message[280]{},line[LineSize]{},time[32]{};
    va_list args;va_start(args,format);std::vsnprintf(message,sizeof(message),format,args);va_end(args);
    // Do not let arbitrary multiline messages forge report fields.
    for(char& c:message)if(c=='\n'||c=='\r')c=' ';
    timespec now{};clock_gettime(CLOCK_REALTIME,&now);tm utc{};gmtime_r(&now.tv_sec,&utc);
    std::strftime(time,sizeof(time),"%Y-%m-%dT%H:%M:%S",&utc);
    std::snprintf(line,sizeof(line),"%s.%03ldZ KPH-%03u %s tid=%ld code=%d ok=%d %s\n",time,now.tv_nsec/1000000,stage,Name(severity),long(syscall(SYS_gettid)),error,success?1:0,message);
#ifdef __ANDROID__
    const int priority=severity==Severity::Fatal?ANDROID_LOG_FATAL:severity==Severity::Error?ANDROID_LOG_ERROR:severity==Severity::Warning?ANDROID_LOG_WARN:ANDROID_LOG_INFO;
    __android_log_print(priority,"KennyPvtHax","%s",line);
#endif
    Lock lock(Get());Append(lock.state,line);
}
inline void Once(unsigned stage,Severity severity,int error,bool success,const char* message){
    if(stage>=64)return;
    const uint64_t bit=uint64_t(1)<<stage;
    auto& seen=severity==Severity::Info?Get().once:Get().warned;
    if(seen.fetch_or(bit,std::memory_order_relaxed)&bit)return;
    Event(stage,severity,error,success,"%s",message);
}
inline int Directory(int parent,const char* name){
    if(mkdirat(parent,name,0700)!=0&&errno!=EEXIST)return -1;
    return openat(parent,name,O_RDONLY|O_DIRECTORY|O_CLOEXEC|O_NOFOLLOW);
}
inline bool SetStorage(const char* activityPrivateDirectory){
    if(!activityPrivateDirectory||activityPrivateDirectory[0]!='/'||strnlen(activityPrivateDirectory,4096)>=4096)return false;
    Lock lock(Get());State& s=lock.state;if(s.report>=0)return !s.ioFailed;
    int activity=open(activityPrivateDirectory,O_RDONLY|O_DIRECTORY|O_CLOEXEC|O_NOFOLLOW);if(activity<0)return false;
    int app=Directory(activity,"KennyPvtHax");close(activity);if(app<0)return false;
    int directory=Directory(app,"CrashReports");close(app);if(directory<0)return false;
    // A single pending name bounds evidence even after termination mid-setup.
    const char* pending="startup-report.pending";
    int report=openat(directory,pending,O_WRONLY|O_CREAT|O_EXCL|O_CLOEXEC|O_NOFOLLOW,0600);
    if(report<0&&errno==EEXIST){
        if(renameat(directory,pending,directory,"startup-report.interrupted.txt")==0)
            report=openat(directory,pending,O_WRONLY|O_CREAT|O_EXCL|O_CLOEXEC|O_NOFOLLOW,0600);
    }
    if(report<0){close(directory);return false;}
    char header[160];std::snprintf(header,sizeof(header),"KennyPvtHax startup checkpoints; build=%s; no signal handler or automatic upload\n",KPH_BUILD_ID);
    size_t bytes=std::strlen(header);bool ok=WriteAll(report,header,bytes);
    for(size_t i=0;i<s.count&&ok;++i){const char* line=s.early[(s.start+i)%EarlyCount];const size_t n=std::strlen(line);ok=bytes+n<=ReportLimit&&WriteAll(report,line,n);bytes+=n;}
    ok=ok&&fsync(report)==0;
    // Only rotate after a complete replacement is durable. Keep three earlier
    // startup reports; a previous run is evidence, not proof of a native crash.
    if(ok){
        const char* from[]={"startup-report.previous-2.txt","startup-report.previous-1.txt","startup-report.txt"};
        const char* to[]={"startup-report.previous-3.txt","startup-report.previous-2.txt","startup-report.previous-1.txt"};
        for(unsigned i=0;i<3&&ok;++i)if(renameat(directory,from[i],directory,to[i])!=0&&errno!=ENOENT)ok=false;
    }
    if(ok)ok=renameat(directory,pending,directory,"startup-report.txt")==0;
    if(ok){fsync(directory);s.directory=directory;s.report=report;s.bytes=bytes;s.count=s.start=0;return true;}
    close(report);unlinkat(directory,pending,0);close(directory);return false;
}
// Host passes an authorized SAF/MediaStore destination FD, from a worker thread.
// Does not own/close that FD or request storage permissions. Index 0=current,
// 1..3=previous runs. The host must finalize its own MediaStore transaction.
inline bool ExportToFd(int destination,unsigned previous=0){
    if(destination<0||previous>3)return false;
    Lock lock(Get());State& s=lock.state;if(s.directory<0)return false;
    char name[64];if(previous)std::snprintf(name,sizeof(name),"startup-report.previous-%u.txt",previous);else std::snprintf(name,sizeof(name),"startup-report.txt");
    int source=openat(s.directory,name,O_RDONLY|O_CLOEXEC|O_NOFOLLOW|O_NONBLOCK);if(source<0)return false;
    struct stat status{},target{};bool ok=fstat(source,&status)==0&&S_ISREG(status.st_mode)&&status.st_size>=0&&size_t(status.st_size)<=ReportLimit;
    if(fstat(destination,&target)!=0 || (target.st_dev==status.st_dev&&target.st_ino==status.st_ino))ok=false;
    char block[2048];size_t copied=0;
    while(ok&&copied<size_t(status.st_size)){ssize_t n=read(source,block,sizeof(block));if(n<0&&errno==EINTR)continue;if(n<=0){ok=false;break;}ok=WriteAll(destination,block,size_t(n));copied+=size_t(n);}
    close(source);return ok;
}
} // namespace KennyDiagnostics
