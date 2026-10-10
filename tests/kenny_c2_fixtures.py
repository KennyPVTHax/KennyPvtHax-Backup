"""Diagnostic fixtures ONLY: RGBA test pixels and generated test tone, not Rias art/voice."""
from pathlib import Path
from PIL import Image
import json,math,struct,wave
root=Path('.verification/c2-assets');pack=root/'assets/anime/highschool_dxd_rias';pack.mkdir(parents=True,exist_ok=True)
image=Image.new('RGBA',(32,64));image.putdata([(x*7,y*3,91,0 if x<8 else 128 if x<16 else 255) for y in range(64) for x in range(32)])
image.save(pack/'character.png');image.resize((32,32)).save(pack/'launcher.png')
image.tobytes();(root/'expected.rgba').write_bytes(image.tobytes())
Image.new('RGBA',(32,64),(255,255,255,255)).save(pack/'opaque.png')
(pack/'voice').mkdir(exist_ok=True)
for name,frequency in [('a',330),('b',550)]:
 with wave.open(str(pack/'voice'/f'{name}.wav'),'wb') as out:
  out.setnchannels(2);out.setsampwidth(2);out.setframerate(24000)
  out.writeframes(b''.join(struct.pack('<hh',int(math.sin(i*frequency*math.tau/24000)*5000),int(math.sin(i*frequency*math.tau/24000)*5000)) for i in range(4800)))
manifest=json.loads(Path('assets/anime/highschool_dxd_rias/manifest.json').read_text())
manifest['voice_packs']=manifest['voice_packs'][:1] # fixtures never depend on installed optional production packs
for event in manifest['voice_packs'][0]['events']:manifest['voice_packs'][0]['events'][event]=['voice/a.wav','voice/b.wav']
alternate=json.loads(json.dumps(manifest['voice_packs'][0]));alternate['id']='alternate';alternate['name']='Diagnostic alternate';manifest['voice_packs'].append(alternate)
(pack/'manifest.json').write_text(json.dumps(manifest))
# No additional real character is installed. This ID is a registry-only unit test.
future=root/'assets/anime/test_registry_extension';future.mkdir(exist_ok=True)
(future/'manifest.json').write_text(json.dumps({'schema':1,'id':'test_registry_extension','name':'Test registry entry','series':'Diagnostic only'}))
Path('.verification/c2-missing').mkdir(exist_ok=True)
print('Diagnostic transparent pixels/tone fixtures generated under ignored .verification only; no character media generated.')
