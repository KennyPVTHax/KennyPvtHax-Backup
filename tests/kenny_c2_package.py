"""Actual production C2 host captures. Missing character media remain missing."""
from pathlib import Path
import base64,hashlib,html,json,struct,subprocess,zipfile
from PIL import Image,ImageDraw,ImageFont,ImageChops
root=Path(__file__).resolve().parents[1];work=root/'.verification';out=root/'previews/phase_c2';out.mkdir(parents=True,exist_ok=True)
labels={'anime-style':'Anime / Appearance — Rias assets missing','anime-player':'Anime / Player — safe artwork fallback','anime-settings':'Anime / Settings','anime-voice':'Rias Gremory / character and voice settings','anime-launcher-fallback':'Anime / K launcher — character image missing','anime-voice-640':'Anime / settings at 640 × 360','aurora-player':'Approved Aurora / Player ESP','classic-player':'Approved Classic / Player ESP'}
paths=[work/('c2-'+n+'.draw') for n in labels]
subprocess.run([str(work/'kenny_host_rasterize'),str(work/'c2-atlas.rgba'),*map(str,paths)],check=True,timeout=60,stdout=subprocess.DEVNULL)
for name,path in zip(labels,paths):
 raw=path.with_suffix('.rgba').read_bytes();w,h=struct.unpack_from('<ii',raw);assert len(raw)==8+w*h*4
 Image.frombytes('RGBA',(w,h),raw[8:]).save(out/(name+'.png'))
 with Image.open(out/(name+'.png')) as image:image.verify()
 with Image.open(out/(name+'.png')) as image:image.load()
states=[json.loads(p.with_suffix('.state.json').read_text()) for p in paths];assert all(s==states[0] for s in states)
font=ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf',30)
sheet=Image.new('RGB',(3912,3848),(8,7,10));draw=ImageDraw.Draw(sheet)
for i,name in enumerate(labels):
 x=24+(i%2)*1944;y=24+(i//2)*956;draw.text((x,y),labels[name],font=font,fill='#F6CCD5')
 image=Image.open(out/(name+'.png')).convert('RGB');sheet.paste(image,(x,y+60))
sheet.save(out/'contact-sheet.png');labels['contact-sheet']='C2 actual host captures / missing Rias artwork and audio explicitly shown'
comparison={}
for theme in ['aurora','classic']:
 baseline=work/('c2-baseline-'+theme+'-player.draw');assert baseline.exists(),'Generate read-only C1 baseline first.'
 subprocess.run([str(work/'kenny_host_rasterize'),str(work/'c2-baseline-atlas.rgba'),str(baseline)],check=True,timeout=30,stdout=subprocess.DEVNULL)
 raw=baseline.with_suffix('.rgba').read_bytes();w,h=struct.unpack_from('<ii',raw);before=Image.frombytes('RGBA',(w,h),raw[8:]);after=Image.open(out/(theme+'-player.png'))
 assert before.size==after.size==(1920,872)
 diff=ImageChops.difference(before.convert('RGB'),after.convert('RGB'));comparison[theme]={'changed_bbox':diff.getbbox(),'max_channel_delta':max(v[1] for v in diff.getextrema())}
 before.save(out/('c1-'+theme+'.png'));labels['c1-'+theme]='C1 baseline / '+theme.title()+' / actual commit c5e9ef0'
panel=Image.new('RGB',(3912,1936),(8,7,10));draw=ImageDraw.Draw(panel)
for row,theme in enumerate(['aurora','classic']):
 for col,name in enumerate(['c1-'+theme,theme+'-player']):
  x=24+col*1944;y=24+row*956;draw.text((x,y),('C1 — ' if col==0 else 'C2 — ')+theme.title(),font=font,fill='#F6CCD5');panel.paste(Image.open(out/(name+'.png')).convert('RGB'),(x,y+60))
panel.save(out/'non-regression.png');labels['non-regression']='C1 versus C2 / unchanged Aurora and Classic design'
def sha(p):return hashlib.sha256(p.read_bytes()).hexdigest()
sources=['jni/main.cpp',*map(str,Path('jni').glob('Kenny*.h')),'tests/kenny_c2_capture.cpp','tests/kenny_c2_check.cpp','tests/kenny_host_rasterize.cpp','assets/anime/highschool_dxd_rias/manifest.json']
manifest={'baseline_commit':'c5e9ef0','renderer':'Actual C++/ImGui production UI and extracted unchanged original controls/fonts, native indexed geometry CPU-rasterized. Not Android captures. No Rias artwork or voice acquired; no diagnostic test media is included in previews.','sources':{str(p):sha(root/p) for p in sources},'feature_snapshot':states[0],'non_regression':comparison,'images':{n+'.png':sha(out/(n+'.png')) for n in labels}}
(out/'verification.json').write_text(json.dumps(manifest,indent=2)+'\n')
page='<!doctype html><html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>KennyPvtHax — C2</title><style>body{margin:20px;background:#08070a;color:#f5f2f2;font:16px system-ui}img{max-width:100%;height:auto}article{margin:30px 0}a{color:#f0a5b3}</style><h1>C2 — Rias character integration</h1><p>Actual C++/ImGui host output. Rias artwork, launcher artwork and authorized voice recordings are missing. The fallback and disabled asset controls are intentional. No substitute artwork/voices or Android playback/GPU claims. This local viewer has not been published.</p>'
for name,label in labels.items():
 uri='data:image/png;base64,'+base64.b64encode((out/(name+'.png')).read_bytes()).decode();page+=f'<article><h2>{html.escape(label)}</h2><a href="{uri}" download="{name}.png">Download PNG</a><br><img src="{uri}" alt="{html.escape(label)}"></article>'
(out/'index.html').write_text(page+'</html>')
(out/'README.txt').write_text('Actual production native UI host captures, not Android.\nNo permitted Rias media acquired; missing assets remain unfilled.\nOpen index.html offline. No online runtime loading or publication.\nThe C1 comparison uses actual read-only headers from c5e9ef0, without altering working-tree history.\n')
with zipfile.ZipFile(out/'kennypvthax-c2-previews.zip','w',zipfile.ZIP_DEFLATED) as z:
 for p in sorted(out.iterdir()):
  if p.suffix!='.zip':z.write(p,p.name)
with zipfile.ZipFile(out/'kennypvthax-c2-previews.zip') as z:assert z.testzip() is None and len(z.namelist())==15
print('PASS 12 PNGs, original feature snapshots identical, native C1 comparison, source hashes, offline viewer and 15-entry ZIP. Comparison:',comparison)
