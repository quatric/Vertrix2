"""Verify configured UI sprite loading and ownership directly from original VF."""
import argparse
import ctypes as c
import json
from pathlib import Path
import struct
import subprocess
from verify_sprite_clone import Frame, Image
from original import Original, BOARD


class Bank(c.Structure):
    _fields_ = [('frames', c.POINTER(Frame)), ('count', c.c_size_t)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('archive', type=Path)
    p.add_argument('--executable', type=Path, required=True)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'ui-sprite-vf.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    *[str(source / name) for name in ['ui_sprite_bank.c', 'image_clone.c',
                        'image_mirror.c', 'image.c', 'vf.c', 'sprite_actor_image.c',
                        'actor_storage.c']], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_vf_find.argtypes = [c.c_void_p, c.c_char_p, c.POINTER(c.c_uint32)]
    native.vertrix_vf_size.argtypes = [c.c_void_p, c.c_uint32, c.POINTER(c.c_uint32)]
    native.vertrix_vf_read.argtypes = [c.c_void_p, c.c_uint32, c.c_uint32, c.c_void_p, c.c_size_t]
    native.vertrix_ui_sprite_bank_load.argtypes = [c.c_void_p, c.c_char_p, c.POINTER(c.c_uint32),
                                                 c.c_size_t, c.POINTER(Bank)]
    native.vertrix_ui_sprite_bank_free.argtypes = [c.POINTER(Bank)]
    native.vertrix_sprite_actor_image.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(Bank),
        c.POINTER(c.POINTER(Image)), c.POINTER(c.c_uint32), c.POINTER(c.c_uint32)]
    original = Original(a.executable)
    archive = native.vertrix_vf_open(str(a.archive.resolve()).encode())
    assert archive
    name = b'sprite/damier.spr'
    index, size = c.c_uint32(), c.c_uint32()
    assert native.vertrix_vf_find(archive, name, c.byref(index))
    assert native.vertrix_vf_size(archive, index, c.byref(size))
    raw = c.create_string_buffer(size.value)
    assert native.vertrix_vf_read(archive, index, 0, raw, size.value)
    blob = raw.raw
    count = struct.unpack_from('<H', blob)[0]
    references = []
    cursor = 2
    for frame in range(count):
        header = blob[cursor:cursor + 48]
        width, height = struct.unpack_from('<2I', header, 12)
        cursor += 48
        pixels = blob[cursor:cursor + width * height * 4]
        cursor += len(pixels)
        references.append((width, height, struct.unpack_from('<10I', header, 8), pixels))
    retained = []
    pixels_checked = 0
    for reverse in [False, True]:
        masks = (c.c_uint32 * 3)(*([0xff, 0xff00, 0xff0000] if reverse else [0xff0000, 0xff00, 0xff]))
        for first in [0, 9, 10, 24, 29]:
            bank = Bank()
            assert native.vertrix_ui_sprite_bank_load(archive, name, masks, first, c.byref(bank))
            assert bank.count == count
            original.cpu.mem_write(0x803000, struct.pack('<' + 'I' * count, *range(count)))
            original.cpu.mem_write(0x5449fc, struct.pack('<6I', 0x803000, count, 0, 0, 0, 0))
            replacements = {1: first, 10: 9, 12: 11, 29: 28, 25: 24}
            expected_bank = []
            for i in range(count):
                width, height, metadata, payload = references[replacements.get(i, i)]
                expected = bytearray(payload)
                if not reverse:
                    expected[0::4], expected[2::4] = payload[2::4], payload[0::4]
                expected[3::4] = bytes(255 if alpha == 0 else 0 for alpha in payload[3::4])
                if i in replacements:
                    row_size = width * 4
                    expected = b''.join(b''.join(expected[y * row_size + x * 4:y * row_size + x * 4 + 4]
                        for x in reversed(range(width))) for y in range(height))
                actual = bank.frames[i]
                assert (actual.image.width, actual.image.height, actual.frame_count) == (width, height, count)
                assert tuple(actual.metadata) == metadata
                assert c.string_at(actual.image.rgba, len(expected)) == expected, (first, i)
                actor = bytearray(b'\xa5' * 0x160)
                struct.pack_into('<3I', actor, 0xb0, 0x5449fc, 0xffffffff, i)
                original.cpu.mem_write(BOARD, bytes(actor))
                original.call(0x4ac8a0, eax=BOARD)
                storage = c.create_string_buffer(bytes(actor), len(actor))
                image = c.POINTER(Image)()
                x, y = c.c_uint32(), c.c_uint32()
                assert native.vertrix_sprite_actor_image(storage, len(actor), c.byref(bank),
                    c.byref(image), c.byref(x), c.byref(y))
                assert storage.raw == bytes(original.cpu.mem_read(BOARD, len(actor)))
                assert c.addressof(image.contents) == c.addressof(bank.frames[i].image)
                assert (x.value, y.value) == (metadata[3], metadata[4])
                assert c.string_at(image.contents.rgba, len(expected)) == expected
                expected_bank.append(bytes(expected))
                pixels_checked += width * height
            before = bytes(bank)
            assert not native.vertrix_ui_sprite_bank_load(archive, name, masks, first, c.byref(bank))
            assert bytes(bank) == before
            retained.append((bank, expected_bank))
            bad_actor = bytearray(storage.raw)
            struct.pack_into('<I', bad_actor, 0xb8, count)
            bad_storage = c.create_string_buffer(bytes(bad_actor), len(bad_actor))
            prior_image, prior_origin = c.addressof(image.contents), (x.value, y.value)
            assert not native.vertrix_sprite_actor_image(bad_storage, len(bad_actor), c.byref(bank),
                c.byref(image), c.byref(x), c.byref(y))
            assert bad_storage.raw == bytes(bad_actor)
            assert (c.addressof(image.contents), (x.value, y.value)) == (prior_image, prior_origin)
        invalid = Bank()
        assert not native.vertrix_ui_sprite_bank_load(archive, name, masks, 1, c.byref(invalid))
        assert bytes(invalid) == bytes(Bank())
    native.vertrix_vf_close(archive)
    for bank, expected_bank in retained:
        for actual, expected in zip(bank.frames[:bank.count], expected_bank):
            assert c.string_at(actual.image.rgba, len(expected)) == expected
        native.vertrix_ui_sprite_bank_free(c.byref(bank))
        assert bytes(bank) == bytes(Bank())
    report = {'status': 'passed', 'banks': 10, 'frames_per_bank': count, 'pixels': pixels_checked,
              'scope': 'Direct original VF caller-selected damier.spr loading, independently parsed '
                       'frames, binary alpha/color order and five configured substitutions match. '
                       'Ownership after archive closure verified. Companion descriptor binding '
                       'matches complete original4ac8a0/4877f0 for all470 frames using local '
                       'descriptor IDs, and resolves verified VF pixels/origins. Invalid frame '
                       'preserves actor and outputs. Startup selector/default first '
                       'source and full generated artwork/application remain unfinished.'}
    (a.build_dir / 'ui-sprite-vf-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
