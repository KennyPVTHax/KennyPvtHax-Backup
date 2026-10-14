"""Repository asset reproducibility/integrity tests; no generated substitute media."""
import importlib.util
import json
import shutil
import tempfile
from pathlib import Path

spec = importlib.util.spec_from_file_location('media_generator', 'tools/generate_embedded_media.py')
module = importlib.util.module_from_spec(spec)
spec.loader.exec_module(module)
root = Path.cwd()
with tempfile.TemporaryDirectory(prefix='kenny-repository-media-') as tmp:
    tmp = Path(tmp)
    checkout = tmp / 'checkout'
    inv = json.loads((root / 'assets/embedded-media-inventory.json').read_text())
    for entry in inv['assets']:
        target = checkout / entry['id']
        target.parent.mkdir(parents=True, exist_ok=True)
        shutil.copyfile(root / entry['id'], target)
    shutil.copyfile(root / 'assets/embedded-media-inventory.json', checkout / 'assets/embedded-media-inventory.json')
    output = tmp / 'generated'
    module.generate(checkout, output)
    before = {p.name: (p.read_bytes(), p.stat().st_mtime_ns) for p in output.iterdir()}
    module.generate(checkout, output)
    assert before == {p.name: (p.read_bytes(), p.stat().st_mtime_ns) for p in output.iterdir()}, 'needless generated-file rewrite'
    assert '/workspace/kenny-full-ui/' not in (output / 'payload.S').read_text()
    assert len(json.loads((output / 'inventory.json').read_text())['assets']) == 16
    def rejected():
        try:
            module.generate(checkout, output)
        except (ValueError, FileNotFoundError):
            return
        raise AssertionError('invalid input accepted')
    victim = checkout / inv['assets'][0]['id']
    original = victim.read_bytes()
    victim.write_bytes(original[:-1])
    rejected()
    victim.write_bytes(original)
    victim.unlink()
    rejected()
    victim.symlink_to(root / inv['assets'][0]['id'])
    rejected()
    victim.unlink()
    victim.write_bytes(original)
    manifest = checkout / 'assets/embedded-media-inventory.json'
    malformed = json.loads(manifest.read_text())
    malformed['assets'][0]['id'] = '../outside.png'
    manifest.write_text(json.dumps(malformed))
    rejected()
print('PASS relocated checkout generates all 16 exact resources; stable writes; missing/corrupt/symlink/traversal rejected')
