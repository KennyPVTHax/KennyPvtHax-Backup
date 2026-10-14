"""Verify each private resource byte-for-byte in the final stripped ELF."""
import argparse,hashlib,json,struct,zipfile
from pathlib import Path
p=argparse.ArgumentParser();p.add_argument('--library',required=True);p.add_argument('--media',required=True);p.add_argument('--output',required=True);a=p.parse_args()
blob=Path(a.library).read_bytes();assert blob[:5]==b'\x7fELF\x02' and blob[5]==1
assert struct.unpack_from('<H',blob,18)[0]==183,'not AArch64'
inv=json.loads((Path(a.media)/'inventory.json').read_text());verified=[]
for entry in inv['assets']:
 payload=(Path(a.media)/entry['id']).read_bytes();assert len(payload)==entry['size'] and hashlib.sha256(payload).hexdigest()==entry['sha256']
 offset=blob.find(payload);assert offset>=0,'missing embedded '+entry['id']
 verified.append(dict(entry,elf_offset=offset))
report={'architecture':'ELF64 AArch64','library_bytes':len(blob),'library_sha256':hashlib.sha256(blob).hexdigest(),'resources_verified':verified,'android_runtime_verified':False,'public_distribution_authorized':False}
Path(a.output).write_text(json.dumps(report,indent=2)+'\n');print('PASS ELF64 AArch64;',len(verified),'exact embedded payloads;',report['library_sha256'])
