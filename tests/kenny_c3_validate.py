"""Offline integrity checks against the reviewed C3 metadata; not a license detector."""
from pathlib import Path
import argparse,array,hashlib,json,subprocess,wave,zipfile

parser=argparse.ArgumentParser()
parser.add_argument('--review-root',type=Path,default=Path('.verification/c3-review'))
parser.add_argument('--uploads-root',type=Path,default=Path('/workspace/attachments'))
args=parser.parse_args()
report=json.loads(Path('assets/anime/highschool_dxd_rias/ASSET_VALIDATION.json').read_text())
alternative=report['licensed_alternative']
def sha(path):return hashlib.sha256(path.read_bytes()).hexdigest()
def decode(path):
    subprocess.run(['ffmpeg','-nostdin','-v','error','-xerror','-i',str(path),'-map','0:a:0','-f','null','-'],check=True,timeout=20)

archive=args.review_root/'cici-mature-female-original.zip'
assert sha(archive)==alternative['original_archive_sha256']
with zipfile.ZipFile(archive) as z:
    assert z.testzip() is None
    names=[n for n in z.namelist() if n.endswith('.wav')]
    assert len(names)==57
    for name in names:
        relative=name.removeprefix('Free Voice Clips Pack - Mature Female/')
        source=args.review_root/'cici-original'/relative
        assert source.read_bytes()==z.read(name)
        decode(source)

assert len(report['uploaded_audio'])==6
for row in report['uploaded_audio']:
    paths=list(args.uploads_root.glob('*/'+row['filename']));assert len(paths)==1
    assert sha(paths[0])==row['sha256'] and paths[0].stat().st_size==row['bytes']
    decode(paths[0])
    assert row['event'] is None and row['rights_status'].startswith('unverified')

assert len(alternative['integrated_files'])==5
for row in alternative['integrated_files']:
    path=Path(row['path']);source=args.review_root/'cici-original'/row['original_file']
    assert sha(path)==row['sha256'] and sha(source)==row['source_sha256']
    with wave.open(str(path)) as w:
        assert (w.getnchannels(),w.getsampwidth(),w.getframerate(),w.getnframes())==(1,2,48000,row['frames'])
        samples=array.array('h',w.readframes(w.getnframes()))
    original=array.array('f',subprocess.run(['ffmpeg','-nostdin','-v','error','-i',str(source),'-f','f32le','-'],check=True,capture_output=True,timeout=20).stdout)
    assert len(original)==len(samples)*2 # no cropping or stretching
    error=max(abs(v-32768*.5*(original[i*2]+original[i*2+1])) for i,v in enumerate(samples))
    assert error<2 and abs(error-row['max_error_s16_units'])<1e-9
    assert row['spoken_content'] in ('hello','see you later','okay','no problem')
    decode(path)

manifest=json.loads(Path('assets/anime/highschool_dxd_rias/manifest.json').read_text())
pack=next(p for p in manifest['voice_packs'] if p['id']=='cici_fyre_mature_female')
assert pack['authentic_rias_voice'] is False and pack['license']=='CC0-1.0'
assert len(pack['events'])==7
allowed={Path(row['path']).relative_to('assets/anime/highschool_dxd_rias').as_posix() for row in alternative['integrated_files']}
assert {p for values in pack['events'].values() for p in values}==allowed
assert not Path('assets/anime/highschool_dxd_rias/character.png').exists()
assert not Path('assets/anime/highschool_dxd_rias/launcher.png').exists()
assert all(not c['downloaded'] and not c['alpha_verified'] for c in report['artwork_candidates'])
print('PASS C3: 57 unchanged originals, 6 unchanged uploaded OGG full decodes, 5 verified full-length PCM16 derivatives (<2 LSB error), truthful pack/mapping metadata and safe missing artwork. Permissions were reviewed manually, not inferred by this test.')
