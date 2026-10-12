#!/usr/bin/env python3
"""Bounded real host builds/tests; no SDK substitutes or device claims."""
import argparse, concurrent.futures, json, os, subprocess, time
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--sanitizers',action='store_true');p.add_argument('--label',default='audit');p.add_argument('--only',default='');a=p.parse_args()
out=Path('.verification')/a.label;out.mkdir(parents=True,exist_ok=True)
def command(args,log,limit=180):
    with log.open('w') as f:
        try: subprocess.run(args,stdout=f,stderr=subprocess.STDOUT,check=True,timeout=limit)
        except (subprocess.CalledProcessError,subprocess.TimeoutExpired):
            f.flush();print(log.read_text()[-6000:],flush=True);raise
for script in ('kenny_host_fixture.py','kenny_startup_audit.py','kenny_c2_fixtures.py'):
    command(['python3','tests/'+script],out/(script+'.log'),45)
imgui=['jni/imgui/'+s+'.cpp' for s in ('imgui','imgui_draw','imgui_widgets','imgui_tables')]
cases={'menu':('kenny_menu_host_check.cpp',True,True),'launcher':('kenny_c1_check.cpp',True,True),
'audio':('kenny_audio_check.cpp',False,False),'theme':('kenny_theme_check.cpp',True,False),
'aurora':('kenny_aurora_check.cpp',True,False),'effects':('kenny_effects_check.cpp',True,False),
'characters':('kenny_c2_check.cpp',True,False),'media':('kenny_c3_check.cpp',False,False),
'diagnostics':('kenny_diagnostics_check.cpp',False,False),'fonts':('../.verification/kenny_font_check.cpp',True,False)}
for name in ('storage','input','gl_state'):
    file='kenny_'+name+'_stability_check.cpp'
    if Path('tests/'+file).exists(): cases[name]=(file,False,False)
if a.only: cases={k:v for k,v in cases.items() if k in a.only.split(',')}
result=[]
def run(item):
    name,(source,gui,engine)=item;start=time.monotonic();exe=out/name
    flags=['g++','-std=c++17','-O1','-g','-pthread','-I','jni','-I','.verification']
    if engine: flags+=['-DIMGUI_ENABLE_TEST_ENGINE']
    if a.sanitizers:flags+=['-fsanitize=address,undefined','-fno-omit-frame-pointer','-fno-pie','-no-pie']
    if name=='storage':flags+=['-Wl,--wrap=write','-Wl,--wrap=fsync']
    command(flags+['tests/'+source]+(imgui if gui else [])+['-lz','-o',str(exe)],out/(name+'-build.log'))
    command([str(exe.resolve())],out/(name+'-test.log'),120)
    return {'test':name,'result':'PASS','elapsed_seconds':round(time.monotonic()-start,3)}
with concurrent.futures.ThreadPoolExecutor(max_workers=2) as pool:
    for value in pool.map(run,cases.items()):result.append(value);print(value,flush=True)
(out/'results.json').write_text(json.dumps({'commit':subprocess.check_output(['git','rev-parse','HEAD'],text=True).strip(),'sanitizers':a.sanitizers,'tests':result},indent=2)+'\n')
