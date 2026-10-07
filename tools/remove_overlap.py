"""Drop lifted routines whose hand port is verified and that nothing lifted can still reach.

A routine is removed when docs/lifted-overlap.json (tools/lifted_overlap.py) shows both a hand
port and a passing verification record, and
  - no other lifted routine lists it as a direct or pointer callee,
  - its address does not appear as a dword in the original image (a vtable or function pointer
    could call it through the dispatcher), and
  - it is not one of the four screen entry points.
The addresses go to docs/lifted-removed.json; tools/lift_batch.py combine skips them."""
import glob
import json
import struct
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SCREEN_FILES = {'hud_decor': 0x46b810, 'title_screen': 0x465af0, 'select_screen': 0x466d60,
                'game_screen': 0x46c9d0}
SCREENS = set(SCREEN_FILES.values())

overlap = json.loads((ROOT / 'docs' / 'lifted-overlap.json').read_text())
candidates = {int(a, 16) for a, r in overlap.items() if r['hand_files'] and r['verification']}
candidates -= SCREENS

metas = {}
for path in glob.glob(str(ROOT / 'docs' / 'lift' / '*.json')):
    data = json.loads(Path(path).read_text())
    if 'stack' in data:  # a screen: its own file, with no address of its own in the record
        screen = SCREEN_FILES.get(Path(path).stem)
        if screen:
            metas[screen] = data
        continue
    for meta in data.values():
        if meta.get('address'):
            metas[meta['address']] = meta


def targets(meta):
    for target in list(meta.get('callees', {})) + list(meta.get('pointer_callees', [])):
        try:
            yield int(target, 16) if isinstance(target, str) else target
        except ValueError:
            pass  # virtual_<address> and slot_<address> are calls through memory


image = (ROOT / 'build' / 'image.bin').read_bytes()
base = 0x400000
dwords = {struct.unpack_from('<I', image, i)[0] for i in range(len(image) - 3)}

removed = set()
while True:
    called = {t for a, m in metas.items() if a not in removed for t in targets(m)}
    more = {a for a in candidates if a not in called and a not in dwords and a not in removed}
    if not more:
        break
    removed |= more
removed = sorted(removed)
(ROOT / 'docs' / 'lifted-removed.json').write_text(json.dumps([hex(a) for a in removed], indent=1))
print('candidates', len(candidates), 'address in the image data', len(candidates & dwords),
      'removed', len(removed))
