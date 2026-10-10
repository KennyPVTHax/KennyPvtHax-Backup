"""Render the approved C1 UI without checkout/reset or history changes."""
from pathlib import Path
import subprocess
root=Path(__file__).resolve().parents[1];work=root/'.verification';snapshot=work/'c2-baseline';snapshot.mkdir(parents=True,exist_ok=True)
paths=subprocess.check_output(['git','ls-tree','-r','--name-only','c5e9ef0','jni'],cwd=root,text=True,timeout=10).splitlines()
for name in paths:
 if Path(name).name.startswith('Kenny') or Path(name).name=='ClaudeTheme.h':
  (snapshot/Path(name).name).write_bytes(subprocess.check_output(['git','show','c5e9ef0:'+name],cwd=root,timeout=10))
for name in ['kenny_menu_host_check.cpp','kenny_phase_b_capture.cpp']:
 text=subprocess.check_output(['git','show','c5e9ef0:tests/'+name],cwd=root,text=True,timeout=10).replace('phase_b','c2-baseline')
 (snapshot/name).write_text(text)
(snapshot/'kenny_host_fixture.h').write_bytes((work/'kenny_host_fixture.h').read_bytes())
core=[root/'jni/imgui'/name for name in ['imgui.cpp','imgui_draw.cpp','imgui_widgets.cpp','imgui_tables.cpp']]
subprocess.run(['g++','-std=c++17','-O1','-DIMGUI_ENABLE_TEST_ENGINE','-I',str(snapshot),'-I',str(root/'jni'),str(snapshot/'kenny_phase_b_capture.cpp'),*map(str,core),'-o',str(work/'c2_baseline_capture')],cwd=root,check=True,timeout=120)
subprocess.run([str(work/'c2_baseline_capture')],cwd=root,check=True,timeout=60)
