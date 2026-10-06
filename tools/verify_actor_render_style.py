"""Compare direct actor rendering state extraction with original preparation."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, BOARD
from unicorn.x86_const import UC_X86_REG_EBP


class Flags(c.Structure):
    _fields_ = [(name, c.c_uint8) for name in ['flag73a', 'flag739', 'effect', 'amount',
        'format000', 'format730', 'transform']] + [('word', c.c_uint16)]


class Style(c.Structure):
    _fields_ = [('flags', Flags)] + [(name, c.c_uint8) for name in ['clip', 'clip_flag', 'cycle', 'scale']]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'actor-render-style.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
        str(source / 'actor_render_style.c'), str(source / 'actor_storage.c'),
        '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_actor_render_style.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(Style)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4ae4e5)
    addresses = [0x5bb73a, 0x5bb739, 0x5bc00d, 0x5bc00e, 0x5bc000, 0x5bb730, 0x5bc00c]
    for case in range(4096):
raw = bytearray(rng.randbytes(0x160)) if case % 7 == 0:
            raw[0x4e] = 100
        cpu.mem_write(BOARD, bytes(raw))
        cpu.mem_write(0x709080 - 0x18, struct.pack('<I', BOARD))
        cpu.mem_write(0x709080 - 0x1c, struct.pack('<I', 1))
        cpu.reg_write(UC_X86_REG_EBP, 0x709080)
        original.call(0x4ae4e5, eax=BOARD, stop=0x4ae571)
        original.call(0x4ae5db, eax=BOARD, stop=0x4ae5e6)
        original.call(0x4ae672, eax=BOARD, stop=0x4ae69d)
        original.call(0x4ae69d, eax=BOARD, stop=0x4ae6b5)
        storage = c.create_string_buffer(bytes(raw), len(raw))
        style = Style()
        assert native.vertrix_actor_render_style(storage, len(raw), c.byref(style))
        expected = [cpu.mem_read(address, 1)[0] for address in addresses]
        assert [getattr(style.flags, name) for name in ['flag73a', 'flag739', 'effect', 'amount',
            'format000', 'format730', 'transform']] == expected, case
        assert style.flags.word == struct.unpack('<H', cpu.mem_read(0x5bc002, 2))[0]
        assert [style.clip, style.clip_flag, style.cycle, style.scale] == [cpu.mem_read(address, 1)[0]
            for address in [0x5bbffe, 0x5bc005, 0x5bb7b8, 0x5bb738]]
        assert bytes(cpu.mem_read(BOARD, len(raw))) == bytes(raw)
    before = bytes(style)
    assert not native.vertrix_actor_render_style(storage, 0x15b, c.byref(style))
    assert bytes(style) == before
    report = {'status':
            'passed', 'cases' : 4096,
                'scope'
                : 'Original direct-preparation fragments execute unchanged. All extracted ' 'render flags, effect/amount/stage/word, scale, clip bytes and cycle match ' 'portable actor state, including amount100 disabling blend. Whole actor ' 'storage remains unchanged. Complete preparation/clipping/pixels and ' 'application integration remain unfinished.'
            }
            (args.build_dir / 'actor-render-style-verification.json')
                    .write_text(json.dumps(report, indent = 2) + '\n')
                        print(json.dumps(report, indent = 2))

                            if __name__ == '__main__' : main()
