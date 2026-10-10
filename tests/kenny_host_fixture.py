from pathlib import Path
import re
s=Path('jni/main.cpp').read_text()
a=s.index('            if (Settings::Tab == 1) {',s.index('KennyMenu::Draw('));b=s.index('\n        });',a)
body=s[a:b]
pattern=r'KennyControls::(?:Checkbox|SliderFloat|SliderInt)\("([^"]+)"[^;\n]*\);'
assert len(re.findall(pattern,body)) == 37, 'original binding inventory changed'
Path('.verification').mkdir(exist_ok=True)
body=re.sub(pattern,lambda m:'RecordBefore("'+m[1]+'"); '+m[0]+' RecordAfter("'+m[1]+'");',body)
d=Path('jni/Helper/definition.h').read_text();enums=d[:d.index('namespace Cheat')]
config=d[d.index('    namespace Esp'):d.index('\n}\n\nfloat Xpos;')]
prelude='''#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include "KennyMenu.h"
#include "KennyPanels.h"
#include "imgui/imgui_internal.h"
#include "ANOY/CustomFont.h"
#include "ANOY/fontAwesome.hpp"
'''+enums+'namespace Cheat {\n'+config+'\n}\nnamespace Settings { int Tab = 1; }\nvoid ResetLogin() { std::abort(); }\n'
prelude+='''struct Control { ImGuiID id; ImVec2 min, max; };
std::map<std::pair<int,std::string>,Control> controls;
std::set<std::pair<int,std::string>> rendered;
void RecordBefore(const char* label) { controls[{Settings::Tab,label}].id=ImGui::GetID(label); }
void RecordAfter(const char* label) {
 auto& c=controls[{Settings::Tab,label}];c.min=ImGui::GetItemRectMin();c.max=ImGui::GetItemRectMax();
 rendered.insert({Settings::Tab,label});
 const std::string name(label);
 if(name.rfind("Aim ",0)==0 || name=="Recoil compensation" || name=="Tracking accuracy")
  assert(ImGui::CalcTextSize(label).x<=c.max.x-c.min.x+1);
 auto* table=ImGui::GetCurrentTable();
 if(table && c.max.x > table->Columns[table->CurrentColumn].WorkMaxX+1) {
  std::fprintf(stderr,"CLIPPED control: tab=%d label=%s x=%.1f bound=%.1f\\n", Settings::Tab,label,c.max.x,table->Columns[table->CurrentColumn].WorkMaxX);
  std::abort();
 }
}
void Panels() {
'''+body+'\n}\n'
Path('.verification/kenny_host_fixture.h').write_text(prelude)
print('Host fixture extracts all 37 real panel binding statements; no SDK replacement.')
