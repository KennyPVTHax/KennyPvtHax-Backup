"""Generate linked resources from hash-pinned repository assets; no downloads."""
import argparse
import hashlib
import json
from pathlib import Path


def generate(source, output):
    source = Path(source).resolve()
    output = Path(output).resolve()
    manifest = json.loads((source / 'assets/embedded-media-inventory.json').read_text())
    if manifest.get('schema') != 1 or len(manifest.get('assets', [])) != 16:
        raise ValueError('Expected schema 1 and all 16 approved runtime resources')
    entries = manifest['assets']
    seen = set()
    for entry in entries:
        name = entry['id']
        path = Path(name)
        if path.is_absolute() or '..' in path.parts or not name.startswith('assets/') or name in seen:
            raise ValueError('Invalid or duplicate resource path: ' + name)
        seen.add(name)
        asset = source / path
        if asset.is_symlink() or not asset.resolve().is_relative_to(source / 'assets'):
            raise ValueError('Resource must be an ordinary in-tree file: ' + name)
        data = asset.read_bytes()
        if len(data) != entry['size'] or hashlib.sha256(data).hexdigest() != entry['sha256']:
            raise ValueError('Resource size/SHA-256 mismatch: ' + name)
    # Preserve exact bytes/order of the reference constexpr table and payloads.
    asm = ['.section .rodata.kph_media,"a"']
    cpp = ['#include "KennyEmbeddedMedia.h"', 'namespace KennyEmbedded {']
    for n, entry in enumerate(entries):
        symbol = 'kph_media_' + str(n)
        asm += ['.balign 16', '.global ' + symbol, '.hidden ' + symbol,
                symbol + ':', '.incbin ' + json.dumps(str(source / entry['id']))]
        cpp.append('extern "C" const unsigned char ' + symbol + '[];')
    cpp += ['const Entry* Lookup(const char* id) {', 'static constexpr Entry entries[] = {']
    for n, entry in enumerate(entries):
        cpp.append('{%s, kph_media_%d, %d, %s},' %
                   (json.dumps(entry['id']), n, entry['size'], json.dumps(entry['sha256'])))
    cpp += ['};', 'if(!id)return nullptr;for(const auto& e:entries)if(std::strcmp(id,e.id)==0)return &e;return nullptr;', '}', '}']
    asm += ['.section .note.GNU-stack,""']
    output.mkdir(parents=True, exist_ok=True)
    # Only generated code/metadata are written; media remain at repository paths.
    products = {'resources.cpp': '\n'.join(cpp) + '\n',
                'payload.S': '\n'.join(asm) + '\n',
                'inventory.json': json.dumps(manifest, indent=2) + '\n',
                'source-root.txt': str(source) + '\n'}
    for name, text in products.items():
        target = output / name
        if not target.exists() or target.read_text() != text:
            target.write_text(text)
    return entries


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--source', default=str(Path(__file__).resolve().parents[1]))
    parser.add_argument('--output', default='.build/embedded-media')
    args = parser.parse_args()
    entries = generate(args.source, args.output)
    print('PASS generated', len(entries), 'repository resources;', sum(e['size'] for e in entries), 'bytes')
