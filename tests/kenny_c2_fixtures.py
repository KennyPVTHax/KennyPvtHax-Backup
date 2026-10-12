"""Diagnostic fixtures ONLY: RGBA test pixels and generated test tone, not Rias art/voice."""
from pathlib import Path
import json,math,struct,wave,zlib
root=Path('.verification/c2-assets');pack=root/'assets/anime/highschool_dxd_rias';pack.mkdir(parents=True,exist_ok=True)
# Tiny standards-compliant RGBA fixtures need only the Python standard library.
# Exact character test pixels remain unchanged; no real media is synthesized.
def png(path,width,height,pixels):
 def chunk(kind,data):return struct.pack('>I',len(data))+kind+data+struct.pack('>I',zlib.crc32(kind+data))
 rows=b''.join(b'\0'+pixels[y*width*4:(y+1)*width*4] for y in range(height))
 path.write_bytes(b'\x89PNG\r\n\x1a\n'+chunk(b'IHDR',struct.pack('>IIBBBBB',width,height,8,6,0,0,0))+chunk(b'IDAT',zlib.compress(rows))+chunk(b'IEND',b''))
pixels=bytes(v for y in range(64) for x in range(32) for v in (x*7,y*3,91,0 if x<8 else 128 if x<16 else 255))
png(pack/'character.png',32,64,pixels);(root/'expected.rgba').write_bytes(pixels)
png(pack/'launcher.png',32,32,b''.join(pixels[y*2*128:(y*2+1)*128] for y in range(32)))
png(pack/'opaque.png',32,64,bytes((255,255,255,255))*32*64)
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
