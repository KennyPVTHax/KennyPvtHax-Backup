#!/usr/bin/env python3
"""Repeatable optimized host CPU/draw/allocation measurement, not mobile FPS."""
from pathlib import Path
import argparse, subprocess
p=argparse.ArgumentParser();p.add_argument('--label',required=True);a=p.parse_args()
subprocess.run(['python3','tests/kenny_host_fixture.py'],check=True,timeout=30,stdout=subprocess.DEVNULL)
s=Path('.verification/kenny_host_fixture.h').read_text()
start=s.index('void RecordBefore(');end=s.index('void Panels()',start)
# Remove only fixture bookkeeping; retain production configuration/panel code.
s=s[:start]+'void RecordBefore(const char*) {}\nvoid RecordAfter(const char*) {}\n'+s[end:]
Path('.verification/kenny_benchmark_fixture.h').write_text(s)
args=['g++','-std=c++17','-O2','-I','jni','-I','.verification','tests/kenny_performance_baseline.cpp']
args+=['jni/imgui/'+x+'.cpp' for x in ('imgui','imgui_draw','imgui_widgets','imgui_tables')]
args+=['-lz','-pthread','-o','.verification/performance']
with open('.verification/benchmark-build.log','w') as log:subprocess.run(args,check=True,timeout=120,stdout=log,stderr=subprocess.STDOUT)
with open('.verification/benchmark-'+a.label+'.json','w') as log:subprocess.run(['.verification/performance'],check=True,timeout=60,stdout=log)
print('.verification/benchmark-'+a.label+'.json')
