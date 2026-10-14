"""Generate private .incbin resources. Never commits or downloads media."""
import argparse,hashlib,json,shutil,zipfile
from pathlib import Path
from PIL import Image,ImageDraw
p=argparse.ArgumentParser();p.add_argument('--bundle',required=True);p.add_argument('--logo',required=True);p.add_argument('--output',required=True);a=p.parse_args()
root=Path(a.output).resolve();root.mkdir(parents=True,exist_ok=True)
expected='1ee9216403aa13f2d99266cb22b3491e4c115945293a2054b516a568bc1248fe'
assert hashlib.sha256(Path(a.bundle).read_bytes()).hexdigest()==expected,'wrong verified private bundle'
with zipfile.ZipFile(a.bundle) as z:
 assert z.testzip() is None
 inv=json.loads(z.read('FILE_INVENTORY.json'))
 # Only fixed runtime assets; originals remain in the unchanged private ZIP.
 for name in z.namelist():
  if not name.startswith('assets/') or name.endswith('/'):continue
  assert '..' not in Path(name).parts and not Path(name).is_absolute()
  dest=root/name;dest.parent.mkdir(parents=True,exist_ok=True);dest.write_bytes(z.read(name))
# Circular photograph is JPEG with black outer padding, not transparent PNG.
# User-authorized geometric mask preserves original RGB pixels; no artwork redraw.
i=Image.open(a.logo).convert('RGB');assert i.size==(1260,1280)
bounds=(99,107,1131,1139);crop=i.crop(bounds).convert('RGBA')
mask=Image.new('L',crop.size,0);ImageDraw.Draw(mask).ellipse((0,0,crop.width-1,crop.height-1),fill=255)
crop.putalpha(mask);crop.save(root/'assets/presentation/launcher.png')
manifest=json.loads((root/'assets/anime/highschool_dxd_rias/manifest.json').read_text())
manifest['asset_status']='Embedded artwork and supplied event voices; character launcher optional/missing.'
(root/'assets/anime/highschool_dxd_rias/manifest.json').write_text(json.dumps(manifest,indent=2)+'\n')
entries=[]
for path in sorted((root/'assets').rglob('*')):
 if path.is_file():
  data=path.read_bytes();entries.append({'id':path.relative_to(root).as_posix(),'size':len(data),'sha256':hashlib.sha256(data).hexdigest()})
asm=['.section .rodata.kph_media,"a"']
cpp=['#include "KennyEmbeddedMedia.h"','namespace KennyEmbedded {']
for n,e in enumerate(entries):
 symbol=f'kph_media_{n}'
 asm+=['.balign 16',f'.global {symbol}',f'.hidden {symbol}',f'{symbol}:',f'.incbin "{(root/e["id"]).as_posix()}"']
 cpp.append(f'extern "C" const unsigned char {symbol}[];')
cpp+=['const Entry* Lookup(const char* id) {','static constexpr Entry entries[] = {']
for n,e in enumerate(entries):cpp.append('{"%s", kph_media_%d, %d, "%s"},'%(e['id'],n,e['size'],e['sha256']))
cpp+=['};','if(!id)return nullptr;for(const auto& e:entries)if(std::strcmp(id,e.id)==0)return &e;return nullptr;','}','}']
(root/'payload.S').write_text('\n'.join(asm)+'\n.section .note.GNU-stack,""\n')
(root/'resources.cpp').write_text('\n'.join(cpp)+'\n')
(root/'inventory.json').write_text(json.dumps({'bundle_sha256':expected,'logo_original_sha256':hashlib.sha256(Path(a.logo).read_bytes()).hexdigest(),'logo_crop':bounds,'rgb_preserved':True,'assets':entries},indent=2)+'\n')
print('Prepared',len(entries),'private read-only resources,',sum(e['size'] for e in entries),'bytes.')
