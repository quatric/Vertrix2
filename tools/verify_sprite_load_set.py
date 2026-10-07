"""Compare all owned planned VF banks with independent SPR decoding."""
import argparse
import ctypes as c
import itertools
import json
from pathlib import Path
import struct
import subprocess
from verify_sprite_load_plan import Plan
from verify_ui_sprite_vf import Bank
from verify_wii_platform_check import resource


class Binding(c.Structure):
    _fields_ = [('token', c.c_uint32), ('bank', c.POINTER(Bank))]


class Map(c.Structure):
    _fields_ = [('bindings', c.POINTER(Binding)), ('count', c.c_size_t)]


class LoadSet(c.Structure):
    _fields_ = [('banks', Bank*20), ('bindings', Binding*20), ('map', Map), ('ready', c.c_uint)]


# Recovered 45dca0 direct-load order, recorded by verify_sprite_load_plan's
# original-executable hooks and corroborated by sprite_load_plan.c resources.
INITIAL_TOKENS = (0x5449c4, 0x5449e0, 0x5449fc, 0x544a18, 0x544c10, 0x544c48,
    0x544c2c, 0x544c64, 0x544d0c, 0x544c80, 0x544c9c, 0x544cb8, 0x544cd4,
    0x544cf0, 0x546500, 0x54651c, 0x546538, 0x546650, 0x54666c, 0x546688)


def validated_initial_plan(report):
    if not isinstance(report, dict) or report.get('status') != 'passed':
        raise ValueError('Initial sprite plan report must have passed status')
    entries = report.get('initial_image_settings_plan')
    if not isinstance(entries, list) or len(entries) != len(INITIAL_TOKENS):
        raise ValueError('Initial sprite plan must contain exactly 20 entries')
    for index, (entry, expected) in enumerate(zip(entries, INITIAL_TOKENS)):
        if not isinstance(entry, dict) or entry.get('token') != hex(expected):
            raise ValueError(f'Initial sprite plan token order mismatch at entry {index}')
        slot = entry.get('slot')
        if type(slot) is not int or not 0 <= slot < 23:
            raise ValueError(f'Initial sprite plan slot invalid at entry {index}')
    return entries


def frames(data, slots):
    result = []
    count = struct.unpack_from('<H', data)[0]
    cursor = 2
    for _ in range(count):
        metadata = struct.unpack_from('<10I', data, cursor+8)
        width, height = metadata[1:3]
        cursor += 48
        original = data[cursor:cursor+width*height*4]
        cursor += len(original)
        converted = bytearray(len(original))
        for i in range(width*height):
            b, g, r, a = original[i*4:i*4+4]
#The verified SPR decoder swaps stored B / R first.Original483ed0
#then uses reversed mask - position ranks on those decoded channels.
            for slot, value in zip(slots, (r, g, b)):
                converted[i*4+2-slot] = value
            converted[i*4+3] = 0 if a else 255
        result.append((metadata, width, height, bytes(converted)))
    assert cursor == len(data)
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('archive', type=Path)
    parser.add_argument('plan_report', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    initial = validated_initial_plan(json.loads(args.plan_report.read_text()))
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = build / 'sprite-load-set.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
        *[str(root / 'source' / n) for n in ('sprite_load_set.c', 'sprite_load_plan.c',
        'sprite_files.c', 'ui_sprite_bank.c', 'image_clone.c', 'image_mirror.c', 'image.c', 'vf.c')],
        '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_vf_open.argtypes = [c.c_char_p]
    native.vertrix_vf_open.restype = c.c_void_p
    native.vertrix_vf_close.argtypes = [c.c_void_p]
    native.vertrix_sprite_load_plan.argtypes = [c.c_void_p, c.POINTER(c.c_uint8), c.c_uint8, c.POINTER(Plan)]
    native.vertrix_sprite_load_set.argtypes = [c.c_void_p, c.POINTER(c.c_uint8), c.c_uint8,
        c.POINTER(c.c_uint32), c.c_size_t, c.POINTER(LoadSet)]
    native.vertrix_sprite_load_set_free.argtypes = [c.POINTER(LoadSet)]
#Reconstruct explicit test selectors from the recovered initial - image plan.
    selectors = [1,2,255,0,4,6,5,7,8,9,10,11,12,13,14,15,16,3,17,18]
    settings = (c.c_uint8*19)()
    interface_slot = initial[2]['slot']
    for entry, selector in zip(initial, selectors):
        if selector != 255:
            settings[selector] = entry['slot']
    original = args.archive.read_bytes()
    checked_frames = checked_pixels = 0
    for slots in itertools.permutations(range(3)):
        for first in (0, 9):
            archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
            assert archive
            plan = Plan()
            assert native.vertrix_sprite_load_plan(archive, settings, interface_slot, c.byref(plan))
            loaded = LoadSet()
            masks = (c.c_uint32*3)(*(255 << (8*s) for s in slots))
            assert native.vertrix_sprite_load_set(archive, settings, interface_slot, masks, first, c.byref(loaded))
            before = bytes(loaded)
            assert not native.vertrix_sprite_load_set(archive, settings, interface_slot, masks, first, c.byref(loaded))
            assert bytes(loaded) == before
            native.vertrix_vf_close(archive)
            assert loaded.ready and loaded.map.count == 20
            assert c.addressof(loaded.map.bindings.contents) == c.addressof(loaded.bindings)
            for index, (entry, bank) in enumerate(zip(plan.entries, loaded.banks)):
                name = bytes(entry.filename).replace(b'\\', b'/').removeprefix(b'./').lower()
                reference = frames(resource(original, name), slots)
                if entry.token == 0x5449fc:
                    replacements = {}
                    for source, target in zip((first,9,11,28,24), (1,10,12,29,25)):
                        metadata, w, h, pixels = reference[source]
                        mirrored = b''.join(pixels[(y*w+x)*4:(y*w+x+1)*4]
                            for y in range(h) for x in reversed(range(w)))
                        replacements[target] = (metadata, w, h, mirrored)
                    for target, frame in replacements.items():
                        reference[target] = frame
                assert bank.count == len(reference)
                assert loaded.bindings[index].token == entry.token
                assert c.addressof(loaded.bindings[index].bank.contents) == c.addressof(bank)
                for frame, (metadata, w, h, pixels) in zip(bank.frames[:bank.count], reference):
                    assert tuple(frame.metadata) == metadata and frame.frame_count == bank.count
                    assert frame.image.width == w and frame.image.height == h
                    actual = c.string_at(frame.image.rgba, w*h*4)
                    assert actual == pixels, (slots, first, index, bytes(entry.filename),
                        checked_frames, next((i for i, pair in enumerate(zip(actual, pixels))
                                             if pair[0] != pair[1]), None))
                    checked_frames += 1
                    checked_pixels += w*h
            native.vertrix_sprite_load_set_free(c.byref(loaded))
            assert bytes(loaded) == bytes(LoadSet())
            native.vertrix_sprite_load_set_free(c.byref(loaded))
#Failure at the final load releases prior banks without publishing them.
    archive = native.vertrix_vf_open(str(args.archive.resolve()).encode())
    assert archive
    settings[18] = 22
    loaded = LoadSet()
    masks = (c.c_uint32*3)(0xff,0xff00,0xff0000)
    assert not native.vertrix_sprite_load_set(archive, settings, interface_slot, masks, 0, c.byref(loaded))
    assert bytes(loaded) == bytes(LoadSet())
    native.vertrix_vf_close(archive)
    report = {'status': 'passed', 'owned_load_sets': 12, 'mapped_banks_checked': 240,
        'frames_checked_after_archive_close': checked_frames, 'pixels_checked': checked_pixels,
        'scope': 'All20 planned original direct banks, two explicit interface first-source '
                 'fixtures, six RGB byte permutations. Independent VF/SPR pixel and metadata '
                 'reference includes simultaneous interface clone/mirror changes. Map pointers '
                 'bind stable owned banks. Occupied output and final missing resource preserve '
                 'output; freeing clears the set. Runtime settings selection, derived builders '
                 'and complete startup remain unverified.'}
    (build / 'sprite-load-set-verification.json').write_text(json.dumps(report, indent=2)+'\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
