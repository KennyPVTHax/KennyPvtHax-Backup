"""Private previews: real ImGui layout and real supplied movie/photo pixels."""
from pathlib import Path
from PIL import Image,ImageDraw,ImageFont
import struct,subprocess,json,base64,zipfile,hashlib,shutil
root=Path(__file__).resolve().parents[1];work=root/'.verification';out=root/'previews/anime-video-logo';out.mkdir(parents=True,exist_ok=True)
labels={'anime-still-fallback':'Anime / actual first-frame fallback','anime-settings':'Existing Settings / Video ON-OFF','anime-video-off':'Video OFF / existing Rias artwork','photo-launcher':'Supplied photo / existing floating launcher','anime-video-00':'Anime / supplied video at 0 seconds','anime-video-02':'Anime / supplied video at 2 seconds','anime-video-04':'Anime / supplied video at 4 seconds','anime-small':'Anime / 640 × 360','anime-reduced-still':'Reduced motion / actual held video frame','missing-media-fallback':'Safe missing-media state'}
paths=[work/f'video-logo-{n}.draw' for n in labels];motion=[work/f'video-logo-motion-{i:03d}.draw' for i in range(49)]
subprocess.run([str(work/'electric-rasterize'),str(work/'c3-atlas.rgba'),*map(str,paths+motion)],check=True,timeout=240,stdout=subprocess.DEVNULL)
for name,p in zip(labels,paths):
 data=p.with_suffix('.rgba').read_bytes();w,h=struct.unpack_from('<ii',data);assert len(data)==8+w*h*4;Image.frombytes('RGBA',(w,h),data[8:]).save(out/f'{name}.png')
# Detail crop uses only the actual native launcher capture, nearest untouched source.
im=Image.open(out/'photo-launcher.png');im.crop((12,12,100,100)).resize((528,528),Image.Resampling.LANCZOS).save(out/'launcher-detail.png');labels['launcher-detail']='Actual launcher crop enlarged / original photo, no replacement artwork'
font=ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf',28)
sheet=Image.new('RGB',(3888,1880),'#08070A');d=ImageDraw.Draw(sheet)
for i,name in enumerate(['anime-video-00','anime-video-02','anime-settings','photo-launcher']):
 x=16+(i%2)*1944;y=16+(i//2)*936;d.text((x,y),labels[name],font=font,fill='#F6F2F3');sheet.paste(Image.open(out/f'{name}.png').convert('RGB'),(x,y+44))
sheet.save(out/'contact-sheet.png');labels['contact-sheet']='Native renderer, actual supplied assets / Android video unverified'
frames=work/'video-logo-preview-frames';frames.mkdir(exist_ok=True)
for i,p in enumerate(motion):
 data=p.with_suffix('.rgba').read_bytes();w,h=struct.unpack_from('<ii',data);assert (w,h)==(1280,720);Image.frombytes('RGBA',(w,h),data[8:]).convert('RGB').save(frames/f'{i:03d}.png')
subprocess.run(['ffmpeg','-v','error','-y','-framerate','12','-i',str(frames/'%03d.png'),'-c:v','libx264','-crf','18','-pix_fmt','yuv420p','-movflags','+faststart',str(out/'anime-ui-host-preview.mp4')],check=True,timeout=60)
files={}
for p in out.iterdir():
 if p.suffix in ['.png','.mp4']:
  if p.suffix=='.png':
   with Image.open(p) as im:im.verify()
  files[p.name]={'sha256':hashlib.sha256(p.read_bytes()).hexdigest(),'bytes':p.stat().st_size}
(out/'verification.json').write_text(json.dumps({'renderer':'Production C++/ImGui geometry/fonts/controls with actual supplied photo and video pixels. Movie frames decoded by FFmpeg on host, not Android MediaCodec. Not Android GPU captures.','motion':'49 consecutive sampled frames, 12fps offline output, 60Hz ImGui input. Original runtime video unchanged at 30fps.','files':files},indent=2)+'\n')
page=['<!doctype html><meta charset="utf-8"><meta name="viewport" content="width=device-width"><title>Anime video and photo launcher</title><style>body{background:#08070a;color:#f6f2f3;font:16px system-ui;margin:20px}img,video{max-width:100%}section{margin-bottom:32px}</style><h1>Private Anime media previews</h1><p>Real native UI and supplied video/photo pixels; host FFmpeg decode. Android MediaCodec/GPU remain unverified. Do not publish these private assets.</p>']
mp4=out/'anime-ui-host-preview.mp4';page.append('<video controls loop muted src="data:video/mp4;base64,'+base64.b64encode(mp4.read_bytes()).decode()+'"></video>')
for name,label in labels.items():page.append(f'<section><h2>{label}</h2><img src="data:image/png;base64,'+base64.b64encode((out/f'{name}.png').read_bytes()).decode()+'"></section>')
(out/'index.html').write_text('\n'.join(page))
with zipfile.ZipFile(out/'Anime-Video-Logo-Private-Previews.zip','w',zipfile.ZIP_DEFLATED) as z:
 for p in out.iterdir():
  if p.suffix in ['.png','.mp4','.json','.html']:z.write(p,p.name)
 assert z.testzip() is None
print('PASS private actual media native UI images/video/HTML/ZIP; host decode only, not Android runtime proof.')
