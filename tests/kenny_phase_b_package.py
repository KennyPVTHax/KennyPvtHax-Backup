"""Rasterize actual C++/ImGui captures and package inspectable Phase B evidence."""
from pathlib import Path
import base64
import hashlib
import html
import json
import struct
import subprocess
import zipfile
from PIL import Image, ImageDraw, ImageFont

root=Path(__file__).resolve().parents[1]
work=root/'.verification';out=root/'previews/phase_b';out.mkdir(parents=True,exist_ok=True)
labels={
    'aurora-player':'Aurora / Player ESP','aurora-world':'Aurora / World ESP',
    'aurora-aim':'Aurora / Aim','aurora-bullet':'Aurora / Bullet track',
    'aurora-extra':'Aurora / Extra features','aurora-style':'Aurora / Style cards',
    'aurora-settings':'Aurora / Settings','aurora-preferences':'Aurora / preference controls (scrolled)',
    'anime-style':'Anime / Style — awaiting user artwork','anime-player':'Anime / safe missing-artwork surface',
    'classic-style':'Classic / Style','classic-player':'Classic / minimal Player ESP',
    'style-640':'Theme cards / 640 × 360 landscape',
}
captures=[work/('phase_b-'+name+'.draw') for name in labels]
assert all(p.exists() for p in captures)
subprocess.run([str(work/'kenny_host_rasterize'),str(work/'phase_b-atlas.rgba'),*map(str,captures)],
               check=True,timeout=60,stdout=subprocess.DEVNULL)
states=[]
for name,p in zip(labels,captures):
    raw=p.with_suffix('.rgba').read_bytes();w,h=struct.unpack_from('<ii',raw)
    assert (w,h)==((640,360) if name=='style-640' else (1920,872)) and len(raw)==8+w*h*4
    Image.frombytes('RGBA',(w,h),raw[8:]).save(out/(name+'.png'))
    with Image.open(out/(name+'.png')) as img: assert img.format=='PNG';img.verify()
    states.append(json.loads(p.with_suffix('.state.json').read_text()))
assert all(state==states[0] for state in states), 'feature state changed across captures'
font=ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf',30)
for filename,names,columns in [('theme-contact-sheet',['aurora-style','anime-style','classic-style'],1),
                             ('aurora-seven-panels',list(labels)[:7],2)]:
    rows=(len(names)+columns-1)//columns
    sheet=Image.new('RGB',(columns*1944+24,rows*956+24),(9,9,14));draw=ImageDraw.Draw(sheet)
    for i,name in enumerate(names):
        x=24+(i%columns)*1944;y=24+(i//columns)*956
        draw.text((x,y),labels[name],font=font,fill='#EDCAD3')
        sheet.paste(Image.open(out/(name+'.png')).convert('RGB'),(x,y+60))
    sheet.save(out/(filename+'.png'))
    labels[filename]='Three selectable themes' if columns==1 else 'Approved Aurora across all seven panels'

for name in labels:
    with Image.open(out/(name+'.png')) as image:
        assert image.format=='PNG';image.load()

def sha(p): return hashlib.sha256(p.read_bytes()).hexdigest()
sources=['jni/main.cpp',*map(str,Path('jni').glob('Kenny*.h')),'jni/ClaudeTheme.h',
         'tests/kenny_host_fixture.py','tests/kenny_phase_b_capture.cpp','tests/kenny_host_rasterize.cpp']
manifest={'base_commit':'58cbf6c','workspace_head':subprocess.check_output(['git','rev-parse','HEAD'],cwd=root,text=True,timeout=10).strip(),
          'renderer':'Actual production C++ UI headers, extracted original main.cpp panel/callback body, bundled ImGui core and embedded fonts; actual native draw triangles CPU-rasterized. Not Android captures. No supplied anime artwork.',
          'source_sha256':{str(p):sha(root/p) for p in sources},'original_feature_snapshot':states[0],
          'images':{name+'.png':{'sha256':sha(out/(name+'.png')),'size':list(Image.open(out/(name+'.png')).size)} for name in labels}}
(out/'verification.json').write_text(json.dumps(manifest,indent=2)+'\n')
page='''<!doctype html><html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>KennyPvtHax — Phase B themes</title><style>body{margin:20px;background:#08070a;color:#f5f2f2;font:16px system-ui}article{margin:28px 0}img{max-width:100%;height:auto;border-radius:8px}a{color:#f0a5b3}p{max-width:900px;line-height:1.5}</style><h1>KennyPvtHax — Phase B</h1><p>Actual C++ / ImGui host renders. Aurora is integrated into all seven panels. Anime uses a safe dark fallback until your artwork is supplied; no substitute artwork is included. Classic performs no Aurora rendering or physics. These previews do not verify Android GPU appearance or performance.</p>'''
for name,label in labels.items():
    data=base64.b64encode((out/(name+'.png')).read_bytes()).decode()
    uri='data:image/png;base64,'+data
    page+=f'<article><h2>{html.escape(label)}</h2><a download="{name}.png" href="{uri}">Download PNG</a><br><img alt="{html.escape(label)}" src="{uri}"></article>'
page+='</html>';assert page.count('data:image/png;base64,')==30
(out/'index.html').write_text(page)
(out/'README.txt').write_text('Phase B: actual C++ / ImGui host-rendered previews.\nOpen index.html offline; each image includes its own download link.\nAnime has no user-supplied artwork yet, so its dark fallback is intentional.\nAndroid SDK/NDK compilation, real storage/touch/GPU behavior and device performance remain unverified.\nverification.json records source hashes and the unchanged original feature snapshot.\n')
with zipfile.ZipFile(out/'kennypvthax-phase-b-previews.zip','w',zipfile.ZIP_DEFLATED) as z:
    for p in sorted(out.iterdir()):
        if p.suffix!='.zip':z.write(p,p.name)
with zipfile.ZipFile(out/'kennypvthax-phase-b-previews.zip') as z: assert z.testzip() is None and len(z.namelist())==18
print('PASS 15 valid PNGs, 13 actual captures with unchanged original feature state, two labeled contact sheets, self-contained viewer and 18-entry ZIP. No substitute artwork or Android capture claims.')
