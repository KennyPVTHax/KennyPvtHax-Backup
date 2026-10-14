#!/usr/bin/env python3
"""Offline conversion only; private inputs/output are never committed or downloaded."""
import argparse,array,hashlib,json,shutil,subprocess,wave
from pathlib import Path
from PIL import Image
p=argparse.ArgumentParser();p.add_argument('--media-dir',type=Path,required=True);p.add_argument('--output',type=Path,required=True);p.add_argument('--character',type=Path);a=p.parse_args()
a.output.mkdir(parents=True,exist_ok=True);originals=a.output/'originals';originals.mkdir(exist_ok=True)
runtime=a.output/'assets/anime/highschool_dxd_rias';runtime.mkdir(parents=True,exist_ok=True);(runtime/'voice').mkdir(exist_ok=True)
events={'extrafeatures.ogg':'extra_features_navigation','bullet.ogg':'bullet_track_enabled','aimoff.ogg':'aim_disabled','aim.ogg':'aim_enabled'}
inventory=[]
for file in sorted(a.media_dir.iterdir()):
 if not file.is_file():continue
 name=file.name.split('-',1)[1] if file.name[0].isdigit() and '-' in file.name else file.name
 if name=='images-3-.jpg':name='images (3).jpg'
 role='character source' if file.suffix.lower()=='.jpg' else 'event voice'
 entry={'original_filename':name,'attachment_filename':file.name,'role':role,'bytes':file.stat().st_size,'sha256':hashlib.sha256(file.read_bytes()).hexdigest(),'authorization':'User supplied for private integration; no public redistribution license asserted'}
 shutil.copyfile(file,originals/name)
 if file.suffix.lower()=='.ogg':
  if name not in events:entry['status']='Unmapped: requires explicit event confirmation';inventory.append(entry);continue
  entry['intended_event']=events[name]
  probe=json.loads(subprocess.check_output(['ffprobe','-v','error','-show_entries','format=duration:stream=codec_name,channels,sample_rate','-of','json',str(file)],timeout=30));entry['source_probe']=probe
  # Analyze decoded samples first; attenuation only when needed. Never trim/time-stretch.
  raw=subprocess.check_output(['ffmpeg','-nostdin','-v','error','-i',str(file),'-f','f32le','-acodec','pcm_f32le','-ac','1','-ar','48000','pipe:1'],timeout=30)
  samples=array.array('f');samples.frombytes(raw);peak=max(map(abs,samples),default=0);gain=min(1,.95/peak) if peak>.98 else 1
  dest=runtime/'voice'/('user_'+name[:-4]+'.wav')
  command=['ffmpeg','-nostdin','-v','error','-y','-i',str(file),'-map','0:a:0','-vn','-ac','1','-ar','48000','-af','volume='+format(gain,'.12g'),'-c:a','pcm_s16le','-map_metadata','-1','-fflags','+bitexact',str(dest)]
  subprocess.run(command,check=True,timeout=30)
  with wave.open(str(dest)) as wav:
   assert wav.getnchannels()==1 and wav.getsampwidth()==2 and wav.getframerate()==48000
   pcm=array.array('h');pcm.frombytes(wav.readframes(wav.getnframes()));duration=wav.getnframes()/48000
   assert 0<duration<=4 and dest.stat().st_size<=1048576
   assert abs(duration-float(probe['format']['duration']))<.05
  entry.update(runtime_path=str(dest.relative_to(a.output)),runtime_bytes=dest.stat().st_size,runtime_sha256=hashlib.sha256(dest.read_bytes()).hexdigest(),runtime_duration=duration,channels=1,sample_rate=48000,sample_format='PCM signed 16-bit WAV',source_decoded_peak=peak,attenuation_gain=gain,pcm_peak=max(map(abs,pcm),default=0),conversion='ffmpeg: decode Vorbis, resample 48kHz mono, optional constant attenuation, pcm_s16le; no trimming/pitch/tempo change')
 else:
  im=Image.open(file);im.verify();im=Image.open(file);entry.update(format=im.format,width=im.width,height=im.height,transparency='none: RGB JPEG with white background',status='Original preserved; runtime requires approved alpha cutout')
 inventory.append(entry)
manifest=json.loads(Path('assets/anime/highschool_dxd_rias/manifest.json').read_text())
# Keep existing approved alternative files and identities intact, with supplied pack first
# only in the install bundle. Saved valid voice-pack selections are never overwritten.
user=next(v for v in manifest['voice_packs'] if v['id']=='user_supplied_events')
manifest['voice_packs']=[user]+[v for v in manifest['voice_packs'] if v['id']!=user['id']]
for file in Path('assets/anime/highschool_dxd_rias/voice').glob('cici_*.wav'):shutil.copyfile(file,runtime/'voice'/file.name)
if a.character:
 im=Image.open(a.character).convert('RGBA');alpha=im.getchannel('A');assert alpha.getextrema()[0]<255 and alpha.getextrema()[1]>0
 assert im.width<=4096 and im.height<=4096 and im.width*im.height<=2097152
 im.save(runtime/'character.png',compress_level=6)
 inventory.append({'original_filename':a.character.name,'role':'User-approved background-removal derivative','runtime_path':'assets/anime/highschool_dxd_rias/character.png','width':im.width,'height':im.height,'format':'RGBA8 noninterlaced PNG','alpha_min':alpha.getextrema()[0],'alpha_max':alpha.getextrema()[1],'sha256':hashlib.sha256((runtime/'character.png').read_bytes()).hexdigest(),'bytes':(runtime/'character.png').stat().st_size})
(runtime/'manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
(a.output/'assets/anime/index.json').write_text('{"schema":1,"characters":["highschool_dxd_rias"]}\n')
(a.output/'SUPPLIED_MEDIA_MANIFEST.json').write_text(json.dumps({'files':inventory,'missing':['Separate KennyPvtHax launcher logo','bt.ogg (bullet.ogg supplied instead)','btoff.ogg'],'mapping_confirmation':'User confirmed extrafeatures.ogg: opening Extra features section','private_only':True},indent=2)+'\n')
print('Prepared private runtime pack and byte-exact originals:',a.output)
