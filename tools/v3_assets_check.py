"""Check the shared loaders on every Vertrix 3 texture and sound effect against Pillow and wave.

Builds tools/v3_assets_check.c with source/png.c, source/image.c and source/vf.c for the host,
runs it over vertrix3.vf and compares each decoded image (RGBA for PNG; indices and palette for
PCX) with Pillow's decode of the same archive entry, and each WAV's samples with Python's wave.

usage: v3_assets_check.py VERTRIX3_VF [--json OUT]
"""
import argparse
import io
import json
import subprocess
import sys
import tempfile
import wave
from pathlib import Path

from PIL import Image

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'tools'))
from vf_entries import entries  # noqa: E402


def fnv(data, h=1469598103934665603):
    for b in data:
        h = ((h ^ b) * 1099511628211) & 0xffffffffffffffff
    return h


def reference(name, data):
    if name.lower().endswith('.wav'):
        with wave.open(io.BytesIO(data)) as w:
            frames = w.readframes(w.getnframes())
            return '%d@%d' % (8 * w.getsampwidth(), w.getframerate()), '%016x' % fnv(frames)
    image = Image.open(io.BytesIO(data))
    if name.lower().endswith('.png'):
        rgba = image.convert('RGBA')
        return '%dx%d' % rgba.size, '%016x' % fnv(rgba.tobytes())
    if image.mode == 'P':
        palette = bytes(image.getpalette()[:768]).ljust(768, b'\0')
    elif image.mode == 'L':
        # Pillow reports an 8-bit PCX whose palette is the grey ramp as greyscale.
        palette = bytes(v for v in range(256) for _ in range(3))
    else:
        return None
    return '%dx%d' % image.size, '%016x' % fnv(palette, fnv(image.tobytes()))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('archive', type=Path)
    parser.add_argument('--json', type=Path, default=ROOT / 'docs' / 'v3-assets-verification.json')
    args = parser.parse_args()
    with tempfile.TemporaryDirectory() as tmp:
        exe = Path(tmp) / 'v3_assets_check'
        subprocess.run(['cc', '-O2', '-std=c11', '-Wall', '-Wextra', '-Werror',
                        '-I', str(ROOT / 'source'), str(ROOT / 'tools' / 'v3_assets_check.c'),
                        str(ROOT / 'source' / 'png.c'), str(ROOT / 'source' / 'image.c'),
                        str(ROOT / 'source' / 'vf.c'), str(ROOT / 'source' / 'audio.c'), '-o', str(exe)], check=True)
        run = subprocess.run([str(exe), str(args.archive)], capture_output=True, text=True)
    ours = {}
    for line in run.stdout.splitlines():
        parts = line.split('\t')
        ours[parts[0]] = tuple(parts[1:])
    files = entries(args.archive)
    counts = {'png': [0, 0], 'pcx': [0, 0], 'wav': [0, 0]}
    mismatches = []
    for name, data in files.items():
        kind = name.lower().rsplit('.', 1)[-1]
        if kind not in counts:
            continue
        counts[kind][1] += 1
        expected = reference(name, data)
        if expected is not None and ours.get(name) == expected:
            counts[kind][0] += 1
        else:
            mismatches.append(dict(name=name, ours=ours.get(name), pillow=expected))
    result = dict(archive=args.archive.name, png_matching=counts['png'][0], png=counts['png'][1],
                  pcx_matching=counts['pcx'][0], pcx=counts['pcx'][1],
                  wav_matching=counts['wav'][0], wav=counts['wav'][1], mismatches=mismatches[:20])
    args.json.write_text(json.dumps(result, indent=1) + '\n')
    print(json.dumps({k: v for k, v in result.items() if k != 'mismatches'}), len(mismatches))
    return 1 if mismatches else 0


if __name__ == '__main__':
    sys.exit(main())
