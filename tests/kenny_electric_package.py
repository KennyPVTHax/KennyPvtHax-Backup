"""Actual ImGui triangles/atlas → PNGs, continuous MP4, offline viewer."""
from pathlib import Path
import subprocess,struct,json,hashlib,base64,zipfile
from PIL import Image,ImageDraw,ImageFont,ImageChops
root=Path(__file__).resolve().parents[1];work=root/'.verification';out=root/'previews/classic-electric';out.mkdir(parents=True,exist_ok=True)
labels={'classic-00':'Classic / 0 seconds','classic-03':'Classic / 3 seconds','classic-06':'Classic / 6 seconds','classic-10':'Classic / 10 seconds','pulse':'Traveling energy / native output','settings':'Classic Background Effects / scrolled Settings','reduced':'Reduced motion / held atmosphere','small':'Classic / 640 × 360','large':'Classic / 2560 × 1440','aurora':'Aurora / unchanged','anime':'Anime / safe missing-media fallback','original-classic':'Before / actual a374ad0 Classic','original-aurora':'Before / actual a374ad0 Aurora','original-anime':'Before / actual a374ad0 Anime'}
labels.update({f'panel-{i}':name for i,name in enumerate(['Player ESP','World ESP','Aim','Bullet track','Extra features'],1)})
paths=[work/f'electric-{name}.draw' for name in labels]
# Actual renderer captures must exist; never fabricate missing baseline images.
for p in paths:assert p.is_file(),p
subprocess.run([str(work/'electric-rasterize'),str(work/'c3-atlas.rgba'),*map(str,paths)],check=True,timeout=120,stdout=subprocess.DEVNULL)
for name,p in zip(labels,paths):
 raw=p.with_suffix('.rgba').read_bytes();w,h=struct.unpack_from('<ii',raw);assert len(raw)==8+w*h*4
 Image.frombytes('RGBA',(w,h),raw[8:]).save(out/f'{name}.png')
font=ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf',28)
sheet=Image.new('RGB',(3888,1880),'#08070A');d=ImageDraw.Draw(sheet)
for i,name in enumerate(['original-classic','classic-03','pulse','settings']):
 im=Image.open(out/f'{name}.png').convert('RGB');x=16+(i%2)*1944;y=16+(i//2)*936;d.text((x,y),labels[name],font=font,fill='#F6F2F3');sheet.paste(im,(x,y+44))
sheet.save(out/'contact-sheet.png');labels['contact-sheet']='Actual native renderer comparison and settings'
comparison=Image.new('RGB',(3888,936),'#08070A');d=ImageDraw.Draw(comparison)
for i,name in enumerate(['original-classic','classic-03']):
 d.text((16+i*1944,16),labels[name],font=font,fill='#F6F2F3');comparison.paste(Image.open(out/f'{name}.png').convert('RGB'),(16+i*1944,60))
comparison.save(out/'before-after.png');labels['before-after']='Baseline versus Electric Starfield / same state and viewport'
# Require identical actual geometry-rasterized Aurora and Anime pixels.
nonregression={}
for theme in ['aurora','anime']:
 a=Image.open(out/f'original-{theme}.png').convert('RGB');b=Image.open(out/f'{theme}.png').convert('RGB');diff=ImageChops.difference(a,b)
 nonregression[theme]={'changed_bbox':diff.getbbox(),'max_channel_delta':max(x[1] for x in diff.getextrema())}
 assert diff.getbbox() is None,(theme,nonregression[theme])
motion=[work/f'electric-motion-{i:03}.draw' for i in range(145)]
subprocess.run([str(work/'electric-rasterize'),str(work/'c3-atlas.rgba'),*map(str,motion)],check=True,timeout=240,stdout=subprocess.DEVNULL)
frameDir=work/'electric-video';frameDir.mkdir(exist_ok=True)
for i,p in enumerate(motion):
 raw=p.with_suffix('.rgba').read_bytes();w,h=struct.unpack_from('<ii',raw);assert (w,h)==(1280,720)
 Image.frombytes('RGBA',(w,h),raw[8:]).convert('RGB').save(frameDir/f'{i:03}.png')
subprocess.run(['ffmpeg','-v','error','-y','-framerate','12','-i',str(frameDir/'%03d.png'),'-c:v','libx264','-crf','18','-pix_fmt','yuv420p','-movflags','+faststart',str(out/'electric-starfield.mp4')],check=True,timeout=90)
files={}
for name in labels:
 p=out/f'{name}.png'
 with Image.open(p) as im:im.verify()
 files[p.name]={'sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'bytes':p.stat().st_size,'label':labels[name]}
mp4=out/'electric-starfield.mp4';files[mp4.name]={'sha256':hashlib.sha256(mp4.read_bytes()).hexdigest(),'bytes':mp4.stat().st_size}
provenance={'baseline':'a374ad0b6b38ef1a9a4bd3cbb231c9c779df3f08','renderer':'Production C++/ImGui, original feature statements/fonts, CPU rasterized actual emitted triangles; not Android GPU captures','motion':'145 consecutive 1280×720 captures, 60 Hz native frames / 12 fps offline output; not Android FPS','unchanged_theme_comparison':nonregression,'files':files}
(out/'verification.json').write_text(json.dumps(provenance,indent=2)+'\n')
html=['<!doctype html><meta charset="utf-8"><meta name="viewport" content="width=device-width"><title>Classic Electric Starfield</title><style>body{background:#08070a;color:#f6f2f3;font:16px system-ui;margin:20px}img,video{max-width:100%;height:auto}section{margin-bottom:36px}a{color:#ff8194}</style><h1>Classic / Electric Starfield</h1><p>Actual native ImGui host rendering. Android GPU/audio/performance require device testing.</p>']
html.append('<video controls loop muted src="data:video/mp4;base64,'+base64.b64encode(mp4.read_bytes()).decode()+'"></video>')
for name,label in labels.items():html.append(f'<section><h2>{label}</h2><img src="data:image/png;base64,'+base64.b64encode((out/f'{name}.png').read_bytes()).decode()+'"></section>')
(out/'index.html').write_text('\n'.join(html))
with zipfile.ZipFile(out/'Classic-Electric-Starfield-Previews.zip','w',zipfile.ZIP_DEFLATED) as archive:
 for name in [*(f'{n}.png' for n in labels),'electric-starfield.mp4','verification.json','index.html']:archive.write(out/name,name)
print('PASS actual renderer PNG/MP4/offline viewer packaging; Aurora/Anime pixel-identical to baseline.')
