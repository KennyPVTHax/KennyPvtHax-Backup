#!/usr/bin/env python3
"""Real SDK-independent UI/audio tests with shared bundled-ImGui compilation."""
import argparse,concurrent.futures,json,subprocess,time
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--sanitizers',action='store_true');p.add_argument('--user-media');p.add_argument('--presentation-media');p.add_argument('--embedded-media');p.add_argument('--label',default='ui-regressions');a=p.parse_args()
out=Path('.verification')/a.label;out.mkdir(parents=True,exist_ok=True)
def command(args,log,limit=240):
 with log.open('w') as f:
  try:subprocess.run(args,stdout=f,stderr=subprocess.STDOUT,check=True,timeout=limit)
  except (subprocess.CalledProcessError,subprocess.TimeoutExpired):f.flush();print(log.read_text()[-4000:],flush=True);raise
for script in ('kenny_host_fixture.py','kenny_startup_audit.py','kenny_c2_fixtures.py'):command(['python3','tests/'+script],out/(script+'.log'),60)
flags=['g++','-std=c++17','-O0','-g','-pthread','-I','jni','-I','.verification']
if a.sanitizers:flags+=['-fsanitize=address,undefined','-fno-omit-frame-pointer','-fno-pie','-no-pie']
objects={False:[],True:[]}
tasks=[]
for engine in (False,True):
 for name in ('imgui','imgui_draw','imgui_widgets','imgui_tables'):
  dest=out/(name+('-engine' if engine else '')+'.o');objects[engine].append(str(dest));tasks.append((engine,name,dest))
def compile_gui(item):
 engine,name,dest=item;extra=['-DKPH_EMBEDDED_MEDIA=1'] if name=='embedded' else []
 resources=[str(Path(a.embedded_media)/'resources.cpp'),str(Path(a.embedded_media)/'payload.S')] if name=='embedded' else []
 command(flags+extra+(['-DIMGUI_ENABLE_TEST_ENGINE'] if engine else [])+['-c','jni/imgui/'+name+'.cpp','-o',str(dest)],out/(dest.stem+'-build.log'))
with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:list(pool.map(compile_gui,tasks))
cases={'menu':('kenny_menu_host_check.cpp',True,True),'launcher':('kenny_c1_check.cpp',True,True),'audio':('kenny_audio_check.cpp',False,False),'theme':('kenny_theme_check.cpp',True,False),'aurora':('kenny_aurora_check.cpp',True,False),'effects':('kenny_effects_check.cpp',True,False),'characters':('kenny_c2_check.cpp',True,False),'media':('kenny_c3_check.cpp',False,False),'diagnostics':('kenny_diagnostics_check.cpp',False,False),'fonts':('../.verification/kenny_font_check.cpp',True,False),'continuation':('kenny_full_continuation_check.cpp',True,False),'electric':('kenny_electric_check.cpp',True,False)}
if a.embedded_media:cases['embedded']=('kenny_embedded_check.cpp',True,False)
if a.presentation_media:cases['presentation']=('kenny_presentation_check.cpp',True,False)
if a.user_media:
 cases['supplied']=('kenny_supplied_media_check.cpp',True,True)
 cases['audio-recovery']=('kenny_audio_recovery_check.cpp',True,True)
def run(item):
 name,(source,gui,engine)=item;start=time.monotonic();exe=out/name
 extra=['-DKPH_EMBEDDED_MEDIA=1'] if name=='embedded' else []
 resources=[str(Path(a.embedded_media)/'resources.cpp'),str(Path(a.embedded_media)/'payload.S')] if name=='embedded' else []
 command(flags+extra+(['-DIMGUI_ENABLE_TEST_ENGINE'] if engine else [])+['tests/'+source]+(objects[engine] if gui else [])+resources+['-lz']+(['-lcrypto'] if name=='embedded' else [])+['-o',str(exe)],out/(name+'-build.log'))
 command([str(exe.resolve())]+([a.user_media] if name in ('supplied','audio-recovery') else [a.presentation_media] if name=='presentation' else []),out/(name+'-test.log'),180)
 result={'test':name,'result':'PASS','seconds':round(time.monotonic()-start,3)};print(result,flush=True);return result
with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:results=list(pool.map(run,cases.items()))
(out/'results.json').write_text(json.dumps({'commit':subprocess.check_output(['git','rev-parse','HEAD'],text=True).strip(),'sanitizers':a.sanitizers,'tests':results},indent=2)+'\n')
