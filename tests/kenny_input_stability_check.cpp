#include "KennyStartup.h"
#include <cassert>
#include <thread>
#include <atomic>
#include <vector>
#include <cstdio>
int main(){using namespace KennyStartup;Queue q;std::array<Pointer,2> p{{{4,20,30},{9,60,70}}};auto point=[&](size_t i){return p[i];};
 assert(q.Motion(Action::Down,0,1,point));assert(q.count==1);q.Drain([](Input e){assert(e.transition&&e.down&&e.x==20);});
 assert(q.Motion(Action::PointerDown,1,2,point));assert(q.count==0);
 std::swap(p[0],p[1]);p[1].x=40;assert(q.Motion(Action::Move,0,2,point));q.Drain([](Input e){assert(!e.transition&&e.x==40);});
 assert(q.Motion(Action::PointerUp,0,2,point));assert(q.count==0);
 assert(q.Motion(Action::Up,1,2,point));q.Drain([](Input e){assert(e.transition&&!e.down&&e.x==40);});assert(q.primary==-1);
 assert(q.Motion(Action::Move,0,1,point));assert(!q.count);
 q.Motion(Action::Down,0,1,point);q.Drain([](Input){});q.Motion(Action::Cancel,0,0,point);q.Drain([](Input e){assert(e.transition&&!e.down);});
 // Fast keys are visible for separate frames; overflow clears both device types.
 Input key;key.kind=Input::Key;key.code=31;key.down=true;q.Push(key);key.down=false;q.Push(key);
 q.Drain([](Input e){assert(e.down);});assert(q.count==1);q.Drain([](Input e){assert(!e.down);});
 for(int i=0;i<65;++i){key.down=i%2;q.Push(key);}bool reset=false;q.Drain([&](Input e){reset=e.kind==Input::Reset;});assert(reset);while(q.count)q.Drain([](Input){});
 // Missing primary and invalid coordinates cancel instead of switching fingers.
 p[0]={1,10,10};q.Motion(Action::Down,0,1,point);q.Drain([](Input){});p[0].id=2;q.Motion(Action::Move,0,1,point);q.Drain([](Input e){assert(!e.down&&e.transition);});
 std::atomic<bool> done{false};std::thread writer([&]{for(int i=0;i<50000;++i){key.kind=Input::Key;key.down=i%2;q.Push(key);}done=true;});
 unsigned events=0;while(!done.load()||q.Pending())q.Drain([&](Input){++events;});writer.join();assert(events&&q.count==0);
 std::puts("PASS single primary pointer ID/reordered multitouch/secondary release/cancel/missing pointer, keyboard frame transitions, overflow reset and 50000 concurrent input submissions; no Android input runtime claim.");
}
