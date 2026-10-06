"""Validate the diagnostic DOL and its actual VF-to-frame composition helper."""
import argparse
import hashlib
import json
from pathlib import Path
import struct
import subprocess


def resource(data, wanted):
    version, count = struct.unpack_from('<II', data)
    assert version == 10
    cursor = 8
    for _ in range(count):
        size, offset, length = struct.unpack_from('<III', data, cursor)
        cursor += 12
        name = data[cursor: cursor + length].replace(b'\\', b'/').lower()
        while name.startswith(b'./'):
            name = name[2:
                ]
        cursor += length
        if name == wanted:
            return data[offset: offset + size]
    raise AssertionError(wanted)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('archive', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    source = (root / 'tools/wii_platform_check.c').read_text()
    helper = source[source.index('static int load_check_frame('): source.index('\nint main(')]
    harness = '#include "image.h"\n#include "surface.h"\n#include <assert.h>\n#include <stdio.h>\n#include <stdlib.h>\n' + helper + r''' int main(int argc, char **argv)
{
    assert(argc == 3);
    VertrixVf *vf = vertrix_vf_open(argv[1]);
    assert(vf);
    VertrixSurface frame = {NULL, 640 * 480 * 4, 640, 480, 640 * 4, 4};
    frame.data = calloc(1, frame.size);
    assert(frame.data);
    assert(load_check_frame(vf, &frame));
    FILE *f = fopen(argv[2], "wb");
    assert(f);
    assert(fwrite(frame.data, 1, frame.size, f) == frame.size);
    assert(!fclose(f));
    free(frame.data);
    vertrix_vf_close(vf);
    return 0;
}
'''
    (build / 'frame-helper.c').write_text(harness)
    executable = build / 'verify-frame-helper'
    subprocess.run(['cc', '-std=c11', '-O2', '-Wall', '-Wextra', '-Werror', '-ffunction-sections', '-fdata-sections', '-Wl,-dead_strip', '-I', str(root / 'source'), str(build / 'frame-helper.c'), * [str(root / 'source' / name) for name in ('vf.c', 'image.c', 'surface.c')], '-o', str(executable)], check=True)
    frame_path = build / 'check-frame.rgba'
    subprocess.run([str(executable), str(args.archive.resolve()), str(frame_path)], check=True)
    original = args.archive.read_bytes()
    sprite = resource(original, b'sprite/damier.spr')
    assert struct.unpack_from('<H', sprite)[0] > 9
    cursor = 2
    for index in range(10):
        width, height = struct.unpack_from('<II', sprite, cursor + 12)
        cursor += 48
        pixels = sprite[cursor: cursor + width * height * 4]
        cursor += len(pixels)
    expected = bytearray(640 * 480 * 4)
    visible = 0
    for y in range(height):
        for x in range(width):
            b, g, r, a = pixels[(y * width + x) * 4: (y * width + x + 1) * 4]
            if a == 0:
                destination = (((480 - height) // 2 + y) * 640 + (640 - width) // 2 + x) * 4
                expected[destination: destination + 4] = bytes((r, g, b, 255))
                visible += 1
    assert visible and frame_path.read_bytes() == expected
    subprocess.run(['make', '-s', '-C', str(root), 'wii-platform-check', f'BUILD={build / "powerpc"}'], check=True)
    elf = build / 'powerpc/vertrix2-platform-check.elf'
    dol = build / 'powerpc/vertrix2-platform-check.dol'
    undefined = subprocess.check_output(['/opt/devkitpro/devkitPPC/bin/powerpc-eabi-nm', '-u', str(elf)])
    assert not undefined.strip()
    elf_bytes = elf.read_bytes()
    assert elf_bytes[: 6] == b'\x7fELF\x01\x02'
    assert struct.unpack_from('>H', elf_bytes, 18)[0] == 20
# PowerPC
    entry = struct.unpack_from('>I', elf_bytes, 24)[0]
    data = dol.read_bytes()
    offsets = struct.unpack_from('>18I', data, 0)
    addresses = struct.unpack_from('>18I', data, 0x48)
    sizes = struct.unpack_from('>18I', data, 0x90)
    assert struct.unpack_from('>I', data, 0xe0)[0] == entry
    populated = []
    for index, (offset, address, size) in enumerate(zip(offsets, addresses, sizes)):
        if size:
            assert offset >= 256 and offset + size <= len(data)
            assert 0x80000000 <= address and address + size <= 0x81800000
            populated.append((index, address, size))
    assert any(i < 7 and address <= entry < address + size for i, address, size in populated)
    report = {'status': 'passed', 'archive_sha256': hashlib.sha256(original).hexdigest(), 'diagnostic_frame_pixels_checked': 640 * 480, 'visible_sprite_pixels': visible, 'dol_sha256': hashlib.sha256(data).hexdigest(), 'dol_bytes': len(data), 'dol_populated_sections': len(populated), 'entry': hex(entry), 'scope': 'Actual diagnostic composition helper reads original VF; every CPU pixel ' 'matches independent VF/SPR decoding. Wii executable fully links without ' 'undefined symbols; PowerPC ELF and DOL segment/entry bounds validate. ' 'Not executed on Wii; controller/SD/video hardware and complete game unverified.'}
    (build / 'wii-platform-check-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
