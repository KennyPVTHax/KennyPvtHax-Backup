"""Package actual native draw-data captures; no substitute UI or AI artwork."""
from pathlib import Path
import base64
import hashlib
import json
import os
import struct
import subprocess
import zipfile
from PIL import Image, ImageDraw, ImageFont

root = Path(__file__).resolve().parents[1]
os.chdir(root)
work = Path('.verification')
out = Path('previews/stage5_6')
out.mkdir(parents=True, exist_ok=True)
labels = {
    'aurora-00': 'Idle aurora / 0 seconds', 'aurora-02': 'Matched comparison / 2 seconds',
    'aurora-03': 'Idle aurora / 3 seconds', 'aurora-06': 'Idle aurora / 6 seconds',
    'aurora-10': 'Idle aurora / 10 seconds', 'idle-stars': 'Idle randomized stars / 10 seconds',
    'center-touch': 'Background touch held / 12 seconds', 'dragged-touch': 'Touch dragged right / 14 seconds',
    'release-00': 'First release frame / 14 seconds', 'release-02': 'Released / 2 seconds later',
    'release-10': 'Released / 10 seconds later', 'reduced': 'Reduced motion / frozen',
}
captures = [work / ('stage5_6-' + name + '.draw') for name in labels]
film = sorted(work.glob('stage5_6-film-*.draw'))
assert len(film) == 145
assert all(p.exists() for p in captures)
assert (work/'stage5_5-atlas.rgba').read_bytes() == (work/'stage5_6-atlas.rgba').read_bytes()
before_draw = work/'stage5_5-player-1920.draw'
assert before_draw.exists(), 'Retain the actual af8a337 baseline draw-data capture.'
baseline_state = json.loads((work/'stage5_5-player-1920.state.json').read_text())
baseline_provenance = json.loads(Path('previews/stage5_5/verification.json').read_text())
assert baseline_provenance['implementation_commit'].startswith('af8a337')
for p in captures + film:
    assert json.loads(p.with_suffix('.state.json').read_text()) == baseline_state
subprocess.run([str(work/'kenny_host_rasterize'), str(work/'stage5_6-atlas.rgba'),
                *map(str, captures), *map(str, film), str(before_draw)], check=True, timeout=180,
               stdout=subprocess.DEVNULL)
print('Rasterized 158 actual native captures (12 samples, 145 consecutive frames, baseline).', flush=True)

def convert(path, target):
    data = path.with_suffix('.rgba').read_bytes()
    width, height = struct.unpack_from('<ii', data)
    assert (width,height) == (1920,872) and len(data) == 8+width*height*4
    image = Image.frombytes('RGBA', (width,height), data[8:])
    image.save(target)
    with Image.open(target) as check:
        assert check.format == 'PNG' and check.size == (1920,872)
        check.verify()
    return image

for name, p in zip(labels, captures): convert(p, out/(name+'.png'))
film_dir = work/'phase-a-film-png'
film_dir.mkdir(exist_ok=True)
for i, p in enumerate(film): convert(p, film_dir/f'{i:03d}.png')
convert(before_draw,out/'before-af8a337.png')
subprocess.run(['ffmpeg','-hide_banner','-loglevel','error','-y','-framerate','12',
                '-i',str(film_dir/'%03d.png'),'-c:v','libx264','-threads','2','-crf','18',
                '-pix_fmt','yuv420p','-movflags','+faststart',str(out/'living-crimson.mp4')],
               check=True,timeout=120)
probe = json.loads(subprocess.check_output(['ffprobe','-v','error','-select_streams','v:0',
                  '-show_entries','stream=width,height,nb_frames,r_frame_rate','-of','json',
                  str(out/'living-crimson.mp4')],timeout=30))['streams'][0]
assert (probe['width'],probe['height'],probe['nb_frames'],probe['r_frame_rate']) == (1920,872,'145','12/1')
subprocess.run(['ffmpeg','-hide_banner','-loglevel','error','-i',str(out/'living-crimson.mp4'),
                '-f','null','-'],check=True,timeout=60)
print('PASS 145-frame 1920x872 / 12 fps MP4: encoded and fully decoded.', flush=True)

# Captures are pasted unchanged; captions exist only outside the render area.
font = ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf',30)
comparison = Image.new('RGB',(3904,1008),(9,9,14))
draw = ImageDraw.Draw(comparison)
draw.text((24,24),'Before / Crimson Eclipse / af8a337',font=font,fill='#DDD0D5')
draw.text((1968,24),'After / Living Crimson Aurora / Phase A',font=font,fill='#F5C5CF')
draw.text((24,76),'Actual C++ / ImGui captures. Same viewport, feature state and appearance preferences.',font=font,fill='#B7A9AC')
comparison.paste(Image.open(out/'before-af8a337.png').convert('RGB'),(24,120))
comparison.paste(Image.open(out/'aurora-02.png').convert('RGB'),(1968,120))
comparison.save(out/'before-after.png')

sheet_names = ['aurora-00','aurora-03','aurora-06','aurora-10','idle-stars','center-touch','dragged-touch','release-02']
sheet = Image.new('RGB',(3904,4*956+24),(9,9,14)); draw = ImageDraw.Draw(sheet)
for i,name in enumerate(sheet_names):
    x=24+(i%2)*1944;y=24+(i//2)*956
    draw.text((x,y),labels[name],font=font,fill='#EDDCE2')
    sheet.paste(Image.open(out/(name+'.png')).convert('RGB'),(x,y+60))
sheet.save(out/'contact-sheet.png')

def sha(p): return hashlib.sha256(p.read_bytes()).hexdigest()
source_paths = ['jni/main.cpp','jni/Helper/definition.h','jni/KennyMenu.h','jni/KennyAurora.h',
                'jni/KennyEffects.h','jni/ClaudeTheme.h','jni/KennyControls.h','jni/KennyAppearance.h',
                'jni/KennyMotion.h','jni/KennyPaint.h','jni/KennyIdentity.h','jni/KennyPanels.h',
                'jni/ANOY/CustomFont.h','jni/ANOY/fontAwesome.hpp',
                'jni/imgui/imgui.cpp','jni/imgui/imgui_draw.cpp','jni/imgui/imgui_widgets.cpp','jni/imgui/imgui_tables.cpp']
manifest = {
    'stage': '5.6 Phase A', 'viewport': [1920,872], 'baseline_commit': 'af8a337',
    'implementation': 'actual production C++/ImGui draw data; host CPU atlas rasterization; no Android/game capture',
    'source_sha256': {p:sha(Path(p)) for p in source_paths},
    'baseline_source_sha256': baseline_provenance['sources_sha256'],
    'png_sha256': {p.name:sha(p) for p in out.glob('*.png')},
    'video': {'file':'living-crimson.mp4','sha256':sha(out/'living-crimson.mp4'), 'frames':145,'fps':12,
              'timeline':'0-4s idle; 4-6s background touch held; 6-8s dragged right; 8-12s release/dispersion. 60 Hz input / 120 Hz bounded physics; 12 fps capture, not a device FPS measurement.'},
    'capture_sha256': {p.name:sha(p) for p in captures+film+[before_draw]},
    'baseline_feature_snapshot': baseline_state,
    'sample_presentation': {name:json.loads(p.with_suffix('.presentation.json').read_text()) for name,p in zip(labels,captures)},
    'limits': 'SDK/NDK/device unavailable. CPU previews omit game/overlay backend and may differ from Android GPU antialiasing/blending. Phase A only on Player ESP. Preferences are session-only.'
}
(out/'verification.json').write_text(json.dumps(manifest,indent=2)+'\n')
def uri(p,mime): return 'data:'+mime+';base64,'+base64.b64encode(p.read_bytes()).decode()
cards=[]
for name in list(labels)+['before-af8a337','before-after','contact-sheet']:
    title=labels.get(name,name.replace('-',' ').title()); src=uri(out/(name+'.png'),'image/png')
    cards.append(f'<figure><figcaption>{title}</figcaption><a download="{name}.png" href="{src}">Download PNG</a><img alt="{title}" loading="lazy" src="{src}"></figure>')
video=uri(out/'living-crimson.mp4','video/mp4')
html='''<!doctype html><html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>KennyPvtHax / Living Crimson / Phase A</title><style>body{margin:24px;background:#060609;color:#F6F2F3;font:16px system-ui}main{max-width:1500px;margin:auto}figure{margin:30px 0}img,video{width:100%;height:auto;border-radius:12px}figcaption{margin-bottom:8px}a{display:inline-block;color:#F0ADB9;margin:8px 0}p{color:#B7A9AC;line-height:1.5}</style><main><h1>Living Crimson Aurora / Phase A</h1><p>Actual C++/ImGui host output at 1920 × 872. Player ESP only. This is a capture viewer, not an application mockup or an Android capture.</p><p>Video: 0–4 seconds idle; 4–6 touch held; 6–8 dragged right; 8–12 released. Captured at 12 fps with 60 Hz input and bounded 120 Hz physics. No device performance claim.</p>'''
html+=f'<video controls playsinline preload="metadata" src="{video}"></video><a download="living-crimson.mp4" href="{video}">Download MP4</a>'
html+=''.join(cards)+'</main></html>'
(out/'index.html').write_text(html)
assert html.count('<img ')==15 and html.count('data:video/mp4;base64,')==2
# All download and display data URIs contain the exact packaged bytes.
import re
embedded = re.findall(r'data:([^;]+);base64,([A-Za-z0-9+/=]+)',html)
expected = {p.read_bytes() for p in out.glob('*.png')} | {(out/'living-crimson.mp4').read_bytes()}
assert len(embedded)==32 and all(base64.b64decode(data) in expected for _,data in embedded)
(out/'README.md').write_text('''# Stage 5.6 / Phase A — Living Crimson Aurora

Open index.html locally: it embeds all 15 PNGs and the complete MP4, with individual download links and no external requests. Extract living-crimson.mp4 for direct Android playback. Original 1920×872 frames are preserved in each PNG; comparison/contact sheet captions are outside capture areas.

Actual production menu/panels, original configuration declarations, bundled ImGui core and embedded fonts produce indexed draw data. A host CPU rasterizer converts that data with the matching atlas. This is neither AI artwork nor a replacement UI, nor Android/game/overlay-device output. Background touches in the capture are native host mouse input standing in for the existing Android mouse/touch mapping. No SDK-dependent callback is executed.

Idle samples: 0/2/3/6/10 seconds. Held touch: 12 seconds, drag: 14 seconds, release samples: immediately / +2 / +10 seconds. Video is a separate consecutive timeline (0–4 idle, 4–6 hold, 6–8 drag, 8–12 release), 145 actual frames at 12 fps. This describes capture cadence, not Android FPS.

verification.json records actual source/draw-data/image/video hashes and unchanged original configuration snapshots. Compile/regenerate using tests/README.md. The cached af8a337 baseline draw data and atlas are required for before/after packaging; prior captures remain unchanged.

SDK, NDK, Android GPU blending/input and device performance remain unverified. Stop after Phase A; do not apply the prototype to other panels without user instruction. New previews have not been uploaded to GitHub.
''')
entries=sorted(p for p in out.iterdir() if p.suffix in {'.png','.mp4','.html','.json','.md'})
with zipfile.ZipFile(out/'phase-a-previews.zip','w',zipfile.ZIP_DEFLATED) as z:
    for p in entries:z.write(p,p.name)
with zipfile.ZipFile(out/'phase-a-previews.zip') as z:
    assert z.testzip() is None and len(z.namelist())==len(entries)
for p in out.glob('*.png'):
    with Image.open(p) as check:check.verify()
    with Image.open(p) as check:check.load()
for p in out.iterdir():p.chmod(0o644)
out.chmod(0o755)
print('PASS 15 PNG integrity checks, matching feature state, self-contained 15-image/MP4 viewer and 19-entry ZIP. Artifacts:',out.resolve(),flush=True)
