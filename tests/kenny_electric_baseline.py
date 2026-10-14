"""Read-only original UI header snapshot; no checkout/reset or source mutation."""
from pathlib import Path
import subprocess
root=Path(__file__).resolve().parents[1];work=root/'.verification';snapshot=work/'electric-baseline';snapshot.mkdir(parents=True,exist_ok=True)
base='a374ad0b6b38ef1a9a4bd3cbb231c9c779df3f08'
for path in (root/'jni').glob('*.h'):
 try:data=subprocess.check_output(['git','show',base+':jni/'+path.name],cwd=root,stderr=subprocess.DEVNULL)
 except subprocess.CalledProcessError:continue
 (snapshot/path.name).write_bytes(data)
source=work/'electric_baseline_capture.cpp'
source.write_text('''#define KENNY_C3_CAPTURE_NO_MAIN
#include "kenny_c3_capture.cpp"
int main(){InitializeC3Capture();menu.appearance.theme=KennyAppearance::Theme::Classic;Frame();Frame();ResetScroll();Save("electric-original-classic");menu.appearance.theme=KennyAppearance::Theme::Aurora;menu.aurora={};menu.aurora.time=3;Frame();Save("electric-original-aurora");menu.appearance.theme=KennyAppearance::Theme::Anime;Frame();Save("electric-original-anime");ImGui::DestroyContext();}
''')
subprocess.run(['g++','-std=c++17','-O1','-DIMGUI_ENABLE_TEST_ENGINE','-I',str(snapshot),'-I','jni','-I','.verification','-I','tests',str(source),'jni/imgui/imgui.cpp','jni/imgui/imgui_draw.cpp','jni/imgui/imgui_widgets.cpp','jni/imgui/imgui_tables.cpp','-lz','-o',str(work/'electric-baseline-capture')],cwd=root,check=True,timeout=180)
subprocess.run([str(work/'electric-baseline-capture')],cwd=root,check=True,timeout=60)
