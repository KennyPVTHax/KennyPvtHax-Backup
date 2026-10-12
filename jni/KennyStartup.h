#pragma once
#include <array>
#include <pthread.h>
#include <cmath>
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
struct Input {enum Kind {Motion,Key,Reset} kind=Motion;float x=0,y=0;int code=0,modifiers=0;bool down=false;bool transition=false;};
enum class Action {Down,Up,Move,Cancel,PointerDown,PointerUp};
struct Pointer {int id;float x,y;};
struct Queue {
    pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
    std::array<Input,64> events{};
    unsigned head=0,count=0;
    int primary=-1;
    float lastX=0,lastY=0;
private:
    bool PushLocked(Input event){
        if(count&&event.kind==Input::Motion&&!event.transition){auto& last=events[(head+count-1)%events.size()];if(last.kind==Input::Motion&&!last.transition){last=event;return true;}}
        if(count==events.size()){
            head=count=0;Input cancel;cancel.kind=Input::Reset;cancel.transition=true;
            events[count++]=cancel;events[count++]=event;return false;
        }
        events[(head+count++)%events.size()]=event;return true;
    }
public:
    bool Push(Input event){pthread_mutex_lock(&mutex);const bool ok=PushLocked(event);pthread_mutex_unlock(&mutex);return ok;}
    bool Pending(){pthread_mutex_lock(&mutex);const bool value=count!=0;pthread_mutex_unlock(&mutex);return value;}
    // Called only by the existing Android queue callback. Index order may change;
    // an additional finger never owns/releases the initiating finger's gesture.
    template<class Get> bool Motion(Action action,size_t changed,size_t pointers,Get get){
        pthread_mutex_lock(&mutex);bool ok=true;Input event;
        auto cancel=[&]{if(primary>=0){event={};event.x=lastX;event.y=lastY;event.transition=true;ok=PushLocked(event);}primary=-1;};
        if(action==Action::Cancel){cancel();}
        else if(pointers>32 || (action!=Action::Move&&changed>=pointers)){cancel();ok=false;}
        else if(action==Action::Down){
            cancel();const Pointer point=get(changed);
            if(point.id>=0&&std::isfinite(point.x)&&std::isfinite(point.y)){primary=point.id;lastX=point.x;lastY=point.y;event.x=lastX;event.y=lastY;event.transition=true;event.down=true;ok=PushLocked(event);}else ok=false;
        }else if(action==Action::Move&&primary>=0){
            bool found=false;for(size_t i=0;i<pointers;++i){const Pointer point=get(i);if(point.id!=primary)continue;
                if(std::isfinite(point.x)&&std::isfinite(point.y)){lastX=point.x;lastY=point.y;event.x=lastX;event.y=lastY;ok=PushLocked(event);found=true;}break;}
            if(!found)cancel();
        }else if((action==Action::Up||action==Action::PointerUp)&&primary>=0){
            const Pointer point=get(changed);if(point.id==primary){if(std::isfinite(point.x)&&std::isfinite(point.y)){lastX=point.x;lastY=point.y;}cancel();}
        }
        pthread_mutex_unlock(&mutex);return ok;
    }
    template<class Apply> void Drain(Apply apply){
        pthread_mutex_lock(&mutex);unsigned n=0;bool button=false;
        while(count&&n++<events.size()){
            const Input event=events[head];if(event.transition&&button)break;
            head=(head+1)%events.size();--count;apply(event);button|=event.transition;
            // Preserve the physical press origin for this frame. Applying a
            // later move before NewFrame would turn an outside-origin drag
            // into an apparent click inside the menu.
            if(event.transition||event.kind==Input::Key||event.kind==Input::Reset)break;
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
