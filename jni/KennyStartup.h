#pragma once
#include <array>
#include <pthread.h>
#ifndef KPH_DIAGNOSTIC_NO_AUDIO
#define KPH_DIAGNOSTIC_NO_AUDIO 0
#endif
#ifndef KPH_DIAGNOSTIC_NO_ARTWORK
#define KPH_DIAGNOSTIC_NO_ARTWORK 0
#endif
#ifndef KPH_DIAGNOSTIC_NO_PREFERENCES
#define KPH_DIAGNOSTIC_NO_PREFERENCES 0
#endif
#ifndef KPH_DIAGNOSTIC_CLASSIC
#define KPH_DIAGNOSTIC_CLASSIC 0
#endif
#ifndef KPH_DIAGNOSTIC_NO_MENU
#define KPH_DIAGNOSTIC_NO_MENU 0
#endif
namespace KennyStartup {
// Fixed bounded handoff: input callbacks never touch ImGui or renderer state.
struct Input {enum Kind {Motion,Key} kind=Motion;float x=0,y=0;int code=0,modifiers=0;bool down=false;bool transition=false;};
struct Queue {
    pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
    std::array<Input,64> events{};
    unsigned head=0,count=0;
    bool Push(Input event){
        pthread_mutex_lock(&mutex);
        if(count&&event.kind==Input::Motion&&!event.transition){auto& last=events[(head+count-1)%events.size()];if(last.kind==Input::Motion&&!last.transition){last=event;pthread_mutex_unlock(&mutex);return true;}}
        if(count==events.size()){
            // Recovery cancels a possibly dropped press instead of leaving a
            // permanently held UI button. Queue remains strictly bounded.
            head=count=0;Input cancel;cancel.transition=true;
            events[count++]=cancel;events[count++]=event;
            pthread_mutex_unlock(&mutex);return false;
        }
        events[(head+count++)%events.size()]=event;pthread_mutex_unlock(&mutex);return true;
    }
    template<class Apply> void Drain(Apply apply){
        pthread_mutex_lock(&mutex);unsigned n=0;bool button=false;
        while(count&&n++<events.size()){
            const Input event=events[head];if(event.transition&&button)break;
            head=(head+1)%events.size();--count;apply(event);button|=event.transition;
        }
        pthread_mutex_unlock(&mutex);
    }
};
inline Queue& Inputs(){static Queue queue;return queue;}
struct RenderGuard {
    bool acquired=false;
    static pthread_mutex_t& Mutex(){static pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;return mutex;}
    RenderGuard(){acquired=pthread_mutex_trylock(&Mutex())==0;}
    void Release(){if(acquired){acquired=false;pthread_mutex_unlock(&Mutex());}}
    ~RenderGuard(){Release();}
};
} // namespace KennyStartup
