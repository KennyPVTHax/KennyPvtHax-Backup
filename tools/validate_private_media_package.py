#!/usr/bin/env python3
"""Validate a private installation payload offline; never guesses Android paths."""
import argparse,hashlib,json,stat,zipfile,io,wave
from pathlib import Path
from PIL import Image
p=argparse.ArgumentParser();p.add_argument('archive',type=Path);p.add_argument('--stage',type=Path);a=p.parse_args()
with zipfile.ZipFile(a.archive) as z:
 entries=z.infolist();assert len(entries)<=64 and len({i.filename for i in entries})==len(entries)
 assert sum(i.file_size for i in entries)<=48*1024*1024 and z.testzip() is None
 for e in entries:
  name=Path(e.filename);assert e.filename==name.as_posix() and '\\' not in e.filename and ':' not in e.filename and not name.is_absolute() and '..' not in name.parts and not stat.S_ISLNK(e.external_attr>>16)
 index=json.loads(z.read('INSTALLATION_INDEX.json'));assert index['schema']==1 and index['character']=='highschool_dxd_rias'
 files=index['files'];assert len(files)<=32;names={f['path'] for f in files};assert len(names)==len(files)
 assert names=={e.filename for e in entries if e.filename.startswith('assets/')}
 for f in files:
  assert f['path']=='assets/anime/index.json' or f['path'].startswith('assets/anime/highschool_dxd_rias/')
  content=z.read(f['path']);assert len(content)==f['bytes'] and hashlib.sha256(content).hexdigest()==f['sha256']
  if f['path'].endswith('.wav'):
   with wave.open(io.BytesIO(content)) as w:assert w.getnchannels() in (1,2) and w.getsampwidth()==2 and 8000<=w.getframerate()<=48000 and 0<w.getnframes()/w.getframerate()<=4
   assert len(content)<=1048576
  elif f['path'].endswith('.png'):
   im=Image.open(io.BytesIO(content));im.verify();im=Image.open(io.BytesIO(content));assert im.mode=='RGBA' and im.width*im.height<=2097152 and im.getchannel('A').getextrema()[0]<255
  else:assert f['path'].endswith('.json');json.loads(content)
 m=json.loads(z.read('assets/anime/highschool_dxd_rias/manifest.json'));assert m['schema']==1 and m['id']==index['character']
 user=next(v for v in m['voice_packs'] if v['id']=='user_supplied_events')
 for event in ['bullet_track_enabled','aim_enabled','aim_disabled','extra_features_navigation']:
  assert len(user['events'][event])==1 and 'assets/anime/highschool_dxd_rias/'+user['events'][event][0] in names
 if a.stage:
  assert not a.stage.exists();a.stage.mkdir(parents=True)
  for f in files:
   out=a.stage/f['path'];out.parent.mkdir(parents=True,exist_ok=True);out.write_bytes(z.read(f['path']))
 print(json.dumps({'files_verified':len(files),'sha256':hashlib.sha256(a.archive.read_bytes()).hexdigest(),'restart_required':True,'android_installation':'Not performed; authorized host must consume this verified payload'},indent=2))
