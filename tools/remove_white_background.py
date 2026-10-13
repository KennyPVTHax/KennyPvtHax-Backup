#!/usr/bin/env python3
"""User-authorized pixel-preserving background mask, never artwork synthesis."""
import argparse,collections,json
from pathlib import Path
from PIL import Image
p=argparse.ArgumentParser();p.add_argument('source',type=Path);p.add_argument('output',type=Path);p.add_argument('--seed',action='append',default=[],help='Verified enclosed background x,y');a=p.parse_args()
im=Image.open(a.source).convert('RGB');w,h=im.size;assert w*h<=2097152
rgb=im.tobytes();candidate=bytearray(w*h);background=bytearray(w*h)
for i in range(w*h):
 r,g,b=rgb[i*3:i*3+3];candidate[i]=min(r,g,b)>=232 and max(r,g,b)-min(r,g,b)<=24
queue=collections.deque()
def seed(i):
 if candidate[i] and not background[i]:background[i]=1;queue.append(i)
for x in range(w):seed(x);seed((h-1)*w+x)
for y in range(h):seed(y*w);seed(y*w+w-1)
for location in a.seed:
 x,y=map(int,location.split(','));assert 0<=x<w and 0<=y<h and candidate[y*w+x];seed(y*w+x)
while queue:
 i=queue.popleft();x=i%w
 if x:seed(i-1)
 if x<w-1:seed(i+1)
 if i>=w:seed(i-w)
 if i<(h-1)*w:seed(i+w)
# Remove only neutral-white regions connected to the image boundary.
# Closed interior white clothing remains opaque. Feather a one-pixel fringe
# by alpha alone; RGB samples (including edge samples) stay byte-for-byte intact.
alpha=bytearray(0 if value else 255 for value in background)
for i in range(w*h):
 if background[i]:continue
 r,g,b=rgb[i*3:i*3+3]
 if min(r,g,b)<205 or max(r,g,b)-min(r,g,b)>24:continue
 x=i%w;near=(x and background[i-1]) or (x<w-1 and background[i+1]) or (i>=w and background[i-w]) or (i<(h-1)*w and background[i+w])
 if near:alpha[i]=max(1,min(255,round((255-min(r,g,b))*255/50)))
out=Image.new('RGBA',(w,h));out.putdata([(*rgb[i*3:i*3+3],alpha[i]) for i in range(w*h)])
assert out.convert('RGB').tobytes()==rgb
assert min(alpha)==0 and max(alpha)==255
a.output.parent.mkdir(parents=True,exist_ok=True);out.save(a.output,compress_level=6)
print(json.dumps({'width':w,'height':h,'background_pixels_removed':sum(background),'source_rgb_preserved':True,'alpha_min':min(alpha),'alpha_max':max(alpha),'method':'Boundary-connected neutral-white mask; alpha-only one-pixel edge feather'}))
