"""Private C3 evidence from real production ImGui geometry and C1 PCM output."""
from pathlib import Path
import base64, hashlib, html, json, shutil, struct, subprocess, zipfile
from PIL import Image, ImageChops, ImageDraw, ImageFont

root = Path(__file__).resolve().parents[1]
work = root / '.verification'
out = root / 'previews/phase_c3'
out.mkdir(parents=True, exist_ok=True, mode=0o700)
labels = {
    'anime-style': 'Anime / Appearance — Rias artwork missing',
    'anime-player': 'Anime / Player — safe artwork fallback',
    'anime-settings': 'Anime / Settings — Cici Fyre alternative installed',
    'anime-voice': 'Anime / voice — English alternative, host audio unavailable',
    'host-pcm-test-settings': 'Voice controls / actual host PCM test sink, not Android',
    'anime-launcher-fallback': 'Anime / K launcher — character image missing',
    'anime-voice-640': 'Anime / scrollable settings at 640 × 360',
    'aurora-player': 'Approved Aurora / Player ESP',
    'classic-player': 'Approved Classic / Player ESP',
}
paths = [work / ('c3-' + name + '.draw') for name in labels]
subprocess.run([str(work / 'kenny_host_rasterize'), str(work / 'c3-atlas.rgba'),
                *map(str, paths)], check=True, timeout=60, stdout=subprocess.DEVNULL)
for name, path in zip(labels, paths):
    raw = path.with_suffix('.rgba').read_bytes()
    width, height = struct.unpack_from('<ii', raw)
    assert len(raw) == 8 + width * height * 4
    Image.frombytes('RGBA', (width, height), raw[8:]).save(out / (name + '.png'))
states = [json.loads(p.with_suffix('.state.json').read_text()) for p in paths]
assert all(state == states[0] for state in states)
font = ImageFont.truetype('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf', 30)
sheet = Image.new('RGB', (3912, 4804), (8, 7, 10))
draw = ImageDraw.Draw(sheet)
for i, name in enumerate(labels):
    x, y = 24 + (i % 2) * 1944, 24 + (i // 2) * 956
    draw.text((x, y), labels[name], font=font, fill='#F6CCD5')
    with Image.open(out / (name + '.png')) as image:
        sheet.paste(image.convert('RGB'), (x, y + 60))
sheet.save(out / 'contact-sheet.png')
labels['contact-sheet'] = 'C3 actual host output / no Rias artwork or original recordings'

comparison = {}
panel = Image.new('RGB', (3912, 1936), (8, 7, 10))
draw = ImageDraw.Draw(panel)
for row, theme in enumerate(('aurora', 'classic')):
    baseline = root / 'previews/phase_c2' / (theme + '-player.png')
    with Image.open(baseline) as before, Image.open(out / (theme + '-player.png')) as after:
        assert before.size == after.size == (1920, 872)
        diff = ImageChops.difference(before.convert('RGB'), after.convert('RGB'))
        comparison[theme] = {'baseline_sha256': hashlib.sha256(baseline.read_bytes()).hexdigest(),
                             'changed_bbox': diff.getbbox(),
                             'max_channel_delta': max(v[1] for v in diff.getextrema())}
        for col, image in enumerate((before, after)):
            x, y = 24 + col * 1944, 24 + row * 956
            draw.text((x, y), ('C2 — ' if col == 0 else 'C3 — ') + theme.title(),
                      font=font, fill='#F6CCD5')
            panel.paste(image.convert('RGB'), (x, y + 60))
panel.save(out / 'non-regression.png')
labels['non-regression'] = 'Actual C2 versus C3 / Aurora and Classic comparison'
for name in labels:
    with Image.open(out / (name + '.png')) as image:
        image.verify()
    with Image.open(out / (name + '.png')) as image:
        image.load()

audio_name = 'cici-c1-mixer-demo.wav'
shutil.copyfile(work / 'c3-mixer-demo.wav', out / audio_name)
subprocess.run(['ffmpeg', '-nostdin', '-v', 'error', '-xerror', '-i', str(out / audio_name),
                '-f', 'null', '-'], check=True, timeout=20)
def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()
sources = ['jni/main.cpp', *map(str, Path('jni').glob('Kenny*.h')),
           'tests/kenny_c3_capture.cpp', 'tests/kenny_c3_check.cpp',
           'tests/kenny_c3_validate.py', 'tests/kenny_c3_package.py',
           'tests/kenny_host_rasterize.cpp',
           'assets/anime/highschool_dxd_rias/manifest.json',
           'assets/anime/highschool_dxd_rias/ASSET_VALIDATION.json']
manifest = {
    'parent_commit': '6f300ae',
    'renderer': 'Actual C++/ImGui production UI, original controls/fonts and emitted indexed geometry CPU-rasterized. Not Android captures or generated character artwork.',
    'asset_status': 'Five CC0 Cici Fyre English alternative clips installed; no Rias artwork, launcher artwork or original Rias recordings installed.',
    'audio_demo': 'Actual C1 portable mixer playing full licensed alternative clips with existing effects; not OpenSL ES or Android playback.',
    'privacy': 'Local/private only; no publication or GitHub upload authorized.',
    'sources': {p: sha(root / p) for p in sources},
    'feature_snapshot': states[0], 'non_regression': comparison,
    'images': {n + '.png': sha(out / (n + '.png')) for n in labels},
    'audio': {audio_name: sha(out / audio_name)},
}
(out / 'verification.json').write_text(json.dumps(manifest, indent=2) + '\n')
page = '<!doctype html><html lang="en"><meta charset="utf-8"><meta name="viewport" content="width=device-width,initial-scale=1"><title>KennyPvtHax C3</title><style>body{margin:20px;background:#08070a;color:#f5f2f2;font:16px system-ui}img{max-width:100%;height:auto}article{margin:30px 0}a{color:#f0a5b3}</style><h1>C3 — verified licensed alternative</h1><p>Private actual C++/ImGui host output. Cici Fyre is an English alternative, NOT Rias or Yoko Hikasa. Original Rias media remain uninstalled pending permission/content verification. English content was corroborated by offline speech recognition, not human listening. Native screenshots show the unavailable Android backend; the separate PCM-test screenshot exercises the actual portable mixer. No Android playback/GPU claim.</p>'
uri = 'data:audio/wav;base64,' + base64.b64encode((out / audio_name).read_bytes()).decode()
page += f'<h2>Actual C1 mixer demo / Cici Fyre alternative</h2><audio controls src="{uri}"></audio><p>Open, checkbox on, navigation, confirmation, close; two seconds apart. Original clips are full-length.</p>'
for name, label in labels.items():
    uri = 'data:image/png;base64,' + base64.b64encode((out / (name + '.png')).read_bytes()).decode()
    page += f'<article><h2>{html.escape(label)}</h2><a href="{uri}" download="{name}.png">Download PNG</a><br><img src="{uri}" alt="{html.escape(label)}"></article>'
(out / 'index.html').write_text(page + '</html>')
(out / 'README.txt').write_text('Private actual production native UI host captures, not Android.\nFive CC0 Cici Fyre English alternative clips; no Rias artwork/original voices.\nOpen index.html offline; it embeds images and the actual portable-mixer audio demo.\nNever upload this bundle to GitHub without separate authorization.\n')
expected = {n + '.png' for n in labels} | {audio_name, 'verification.json', 'index.html', 'README.txt'}
with zipfile.ZipFile(out / 'kennypvthax-c3-previews.zip', 'w', zipfile.ZIP_DEFLATED) as archive:
    for name in sorted(expected):
        archive.write(out / name, name)
with zipfile.ZipFile(out / 'kennypvthax-c3-previews.zip') as archive:
    assert archive.testzip() is None and set(archive.namelist()) == expected and len(expected) == 15
out.chmod(0o700)
for path in out.iterdir():
    if path.is_file():
        path.chmod(0o600)
print('PASS 11 PNG full decodes, identical original feature snapshots, actual C1 mixer WAV, source hashes, self-contained viewer and 15-entry private ZIP. Comparison:', comparison)
