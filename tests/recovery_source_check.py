"""Golden-reference source gates. No SDK substitutes or runtime-hook changes."""
from pathlib import Path
import subprocess,json,hashlib,re
manifest=json.loads(Path('RECOVERY_ORIGINAL_MANIFEST.json').read_text())
base=subprocess.check_output(['git','show',manifest['original_commit']+':jni/main.cpp'],text=True,timeout=15)
source=Path('jni/main.cpp').read_text()
for begin,end in [('int32_t (*orig_ANativeWindow_getHeight)','bool logged = false;'),('void *RunGame',None),('void (*oReceiveDrawHUD)','void FixGameCrash()')]:
 a=base[base.index(begin):base.index(end)] if end else base[base.index(begin):]
 b=source[source.index(begin):source.index(end)] if end else source[source.index(begin):]
 assert a==b,begin+' changed'
start='EGLBoolean (*orig_eglSwapBuffers)';end='    // Persistent state'
assert base[base.index(start):base.index(end)]==source[source.index(start):source.index(end)],'EGL/fonts/context/backend/NewFrame changed'
start='    // Persistent state';end='    // Main window'
def code(text):return '\n'.join(line for line in text.splitlines() if line.strip() and not line.strip().startswith('//'))
assert code(base[base.index(start):base.index(end)])==code(source[source.index(start):source.index('    // Recovery Stage 1')]),'Original toggle changed'
start='    ImGui::Render();';end='void (*oReceiveDrawHUD)'
assert base[base.index(start):base.index(end)]==source[source.index(start):source.index(end)],'Render submission changed'
start=base.index('                if (Settings::Tab == 1)');end=base.index('            ImGui::EndChild();',start)
panel=base[start:end].removesuffix('            }\n')
assert panel in source,'Original feature control body/conditions/callback changed'
pattern=r'ImGui::(?:Checkbox|SliderFloat|SliderInt)\([^;\n]+;'
calls=re.findall(pattern,panel);assert len(calls)==37
assert len(re.findall(r'ImGui::Button\("Guest Reset"',panel))==1
allowed={'jni/main.cpp','jni/ClaudeTheme.h','jni/Helper/definition.h','jni/Lua_Buffer.cpp'}
unchanged=[]
for item in manifest['archive_files']:
 name=item['path']
 if name.endswith('.bak'):continue # Original unused backups remain local, not published.
 p=Path(name);assert p.is_file(),name
 if name not in allowed:
  assert hashlib.sha256(p.read_bytes()).hexdigest()==item['sha256'],name+' changed';unchanged.append(name)
for file,new,old in [('jni/Helper/definition.h','FString("KennyPvtHax")','FString("Anoy")'),('jni/Lua_Buffer.cpp','Msg.Show(1, "KennyPvtHax", message','Msg.Show(1, "Anoy Hax", message')]:
 raw=Path(file).read_text().replace(new,old,1).encode();expected=next(i['sha256'] for i in manifest['archive_files'] if i['path']==file)
 assert hashlib.sha256(raw).hexdigest()==expected,'Non-branding native/Lua change'
fix=source[source.index('void FixGameCrash()'):source.index('void *RunGame')]
assert 'system(' not in fix and 'chmod' not in fix
assert all(x not in source for x in ['KennyStartup','KennyDiagnostics','KennyAurora','KennyCharacters','KennyLauncher','KennyAndroidAudio','NativeGlobalsReady','RenderGuard'])
assert 'FontDataOwnedByAtlas' not in source # Golden font initialization is untouched.
assert not list(Path('jni').glob('Kenny*Audio*')) and not Path('assets').exists()
assert len(list(Path('jni').rglob('*.a')))==40
assert len(list(Path('jni/SDK').glob('*')))==2391
assert '-lOpenSLES' not in Path('jni/Android.mk').read_text()
# SDK/config-free fixture: genuine original definitions, exact control statements.
Path('.verification').mkdir(exist_ok=True)
d=Path('jni/Helper/definition.h').read_text();enums=d[:d.index('namespace Cheat')]
config=d[d.index('    namespace Esp'):d.index('\n}\n\nfloat Xpos;')]
prelude='''#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <map>
#include <string>
#include <set>
#include <vector>
#include "imgui/imgui_internal.h"
#include "KennyMenu.h"
#include "ANOY/CustomFont.h"
#include "ANOY/fontAwesome.hpp"
'''+enums+'namespace Cheat {\n'+config+'\n}\nnamespace Settings { int Tab=1; }\nvoid ResetLogin(){std::abort();}\n'
# Register native widgets only for tests; production remains exact original calls.
pattern=r'ImGui::(?:Checkbox|SliderFloat|SliderInt)\("([^"]+)"[^;\n]*\);'
body=re.sub(pattern,lambda m:m[0]+' Record("'+m[1]+'");',panel)
prelude+='''std::map<std::string,ImRect> controls;
void Record(const char* label){controls[label]=ImRect(ImGui::GetItemRectMin(),ImGui::GetItemRectMax());}
void Panels(){
'''+body+'\n}\n'
Path('.verification/recovery_fixture.h').write_text(prelude)
print('PASS exact original worker/constructor, hooks/input, EGL/fonts/backends/NewFrame/render/toggle; 37 original feature bindings plus Guest Reset with unchanged ranges/conditions;',len(unchanged),'original dependency files unchanged; owner SDK and 40 libraries present. Only UI/branding and disabled destructive routine differ.')
