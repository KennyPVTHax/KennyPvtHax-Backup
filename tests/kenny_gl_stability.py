#!/usr/bin/env python3
"""Real software EGL/OpenGL driver, no mocked GL/SDK headers."""
import ctypes as c, subprocess
from pathlib import Path
Path('.verification').mkdir(exist_ok=True)
args=['g++','-std=c++17','-O1','-fPIC','-shared','-I','jni','tests/kenny_gl_stability_check.cpp']
args+=['jni/imgui/'+s+'.cpp' for s in ('imgui','imgui_draw','imgui_widgets','imgui_tables')]
args+=['jni/imgui/backends/imgui_impl_opengl3.cpp','-ldl','-o','.verification/gl-stability.so']
with open('.verification/gl-build.log','w') as log:subprocess.run(args,check=True,timeout=150,stdout=log,stderr=subprocess.STDOUT)
e=c.CDLL('libEGL.so.1')
def bind(name,result,types):f=getattr(e,name);f.restype=result;f.argtypes=types;return f
ptr=c.c_void_p;integer=c.c_int;ip=c.POINTER(integer)
get=bind('eglGetProcAddress',ptr,[c.c_char_p]);platform=c.CFUNCTYPE(ptr,c.c_uint,ptr,ip)(get(b'eglGetPlatformDisplayEXT'))
d=platform(0x31DD,None,None);assert d
major=integer();minor=integer();assert bind('eglInitialize',c.c_uint,[ptr,ip,ip])(d,c.byref(major),c.byref(minor))
assert bind('eglBindAPI',c.c_uint,[c.c_uint])(0x30A2)
attrs=(integer*7)(0x3033,1,0x3040,8,0x3024,8,0x3038);config=ptr();count=integer()
assert bind('eglChooseConfig',c.c_uint,[ptr,ip,c.POINTER(ptr),integer,ip])(d,attrs,c.byref(config),1,c.byref(count)) and count.value
end=(integer*1)(0x3038);context=bind('eglCreateContext',ptr,[ptr,ptr,ptr,ip])(d,config,None,end);assert context
size=(integer*5)(0x3057,16,0x3056,16,0x3038);surface=bind('eglCreatePbufferSurface',ptr,[ptr,ptr,ip])(d,config,size);assert surface
current=bind('eglMakeCurrent',c.c_uint,[ptr,ptr,ptr,ptr]);assert current(d,surface,surface,context)
lib=c.CDLL(str(Path('.verification/gl-stability.so').resolve()));assert lib.KennyGLStabilityCheck()==0
assert current(d,None,None,None)
bind('eglDestroySurface',c.c_uint,[ptr,ptr])(d,surface);bind('eglDestroyContext',c.c_uint,[ptr,ptr])(d,context);bind('eglTerminate',c.c_uint,[ptr])(d)
