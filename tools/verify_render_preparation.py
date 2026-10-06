"""Compare complete original4ae250 preparation decisions and resulting state."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from verify_render_color import Color
from verify_render_color_bank import Bank
from verify_render_dispatch import FlagState
from verify_render_weights import Weights


class Preparation(c.Structure):
    _fields_ = [('color', Color), ('source_weights', c.c_void_p),
                ('destination_weights', c.c_void_p), ('source_words', c.c_void_p),
                ('destination_words', c.c_void_p), ('map_shift', c.c_int16),
                ('cycle_enabled', c.c_uint8), ('cycle', c.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'render-preparation.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
        *[str(source / name) for name in ('render_preparation.c', 'render_color.c',
                                        'render_weights.c')], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_render_prepare.argtypes = [FlagState, c.c_uint8, c.POINTER(Weights),
        c.POINTER(Bank), c.c_void_p, c.c_size_t, c.POINTER(Preparation)]
    native.vertrix_render_weights_build.argtypes = [c.POINTER(Weights)]
    weights = Weights()
    assert native.vertrix_render_weights_build(c.byref(weights)) == 1
    original = Original(args.executable)
    original.cpu.mem_map(0x900000, 0x40000)
    rng = random.Random(0x4ae250)
    hue_bytes = rng.randbytes(262144)
    hues = c.create_string_buffer(hue_bytes, len(hue_bytes))
    original.cpu.mem_write(0x900000, hue_bytes)
    original.cpu.mem_write(0x54b804, struct.pack('<I', 0x900000))
    bases = [rng.getrandbits(32) for _ in range(256)]
    original.cpu.mem_write(0x54d1d0, struct.pack('<256I', *bases))
    output = Preparation()
    for case in range(4096):
        state = FlagState()
        state.format_000 = rng.randrange(13)
        state.format_730 = rng.choice([state.format_000, 13])
        state.amount_00e = rng.randrange(101)
        state.flag_739 = rng.choice([0, 1, 2, 255])
        state.flag_73a = rng.choice([0, 1, 2, 255])
        state.word_002 = rng.randrange(65536)
        cycle = rng.randrange(256)
        bank = Bank()
        for i in range(13):
            bank.lookup[i], bank.colors[i] = rng.getrandbits(32), rng.getrandbits(32)
        original.cpu.mem_write(0x54b808, struct.pack('<13I', *bank.lookup))
        original.cpu.mem_write(0x54b83c, struct.pack('<13I', *bank.colors))
        original.cpu.mem_write(0x5bc000, struct.pack('<BBH', state.format_000, 0, state.word_002))
        original.cpu.mem_write(0x5bb730, bytes([state.format_730]))
        original.cpu.mem_write(0x5bb739, bytes([state.flag_739, state.flag_73a]))
        original.cpu.mem_write(0x5bc00e, bytes([state.amount_00e]))
        original.cpu.mem_write(0x5bb7b8, bytes([cycle]))
        for address, payload in (
                (0x54d5d4, struct.pack('<I', output.color.lookup_entry)),
                (0x5bc008, struct.pack('<I', output.color.color)),
                (0x54d5ec, struct.pack('<I', output.color.half_color)),
                (0x54d5dc, struct.pack('<3H', *output.color.indices)),
                (0x54d5e8, bytes(output.color.channels)),
                (0x54d5f0, bytes([output.color.hue]))):
            original.cpu.mem_write(address, payload)
        for address, pointer, native_base, original_base in (
                (0x55f1f0, output.source_weights, c.addressof(weights.bytes), 0x558cf0),
                (0x55f1f4, output.destination_weights, c.addressof(weights.bytes), 0x558cf0),
                (0x5785f8, output.source_words, c.addressof(weights.words), 0x55f1f8),
                (0x5785fc, output.destination_words, c.addressof(weights.words), 0x55f1f8)):
            original.cpu.mem_write(address, struct.pack('<I',
                original_base + pointer - native_base if pointer else 0))
        previous = (output.source_weights, output.destination_weights,
                    output.source_words, output.destination_words)
        original.call(0x4ae250)
        assert native.vertrix_render_prepare(state, cycle, c.byref(weights), c.byref(bank),
            hues, len(hue_bytes), c.byref(output)) == 1
        color = output.color
        assert color.lookup_entry == struct.unpack('<I', original.cpu.mem_read(0x54d5d4, 4))[0]
        assert color.color == struct.unpack('<I', original.cpu.mem_read(0x5bc008, 4))[0]
        assert color.half_color == struct.unpack('<I', original.cpu.mem_read(0x54d5ec, 4))[0]
        assert tuple(color.indices) == struct.unpack('<3H', original.cpu.mem_read(0x54d5dc, 6))
        assert bytes(color.channels) == bytes(original.cpu.mem_read(0x54d5e8, 3))
        assert color.hue == original.cpu.mem_read(0x54d5f0, 1)[0]
        expected_shift = state.word_002 if state.word_002 < 32768 else state.word_002 - 65536
        selected = struct.unpack('<I', original.cpu.mem_read(0x54cdc8, 4))[0]
        assert selected == (0x54bb90 + expected_shift * 4) & 0xffffffff
        assert output.map_shift == expected_shift
        if state.flag_739 == 1:
            assert output.source_weights == c.addressof(weights.bytes[state.amount_00e])
            assert output.destination_weights == c.addressof(weights.bytes[100 - state.amount_00e])
            assert output.source_words == c.addressof(weights.words[state.amount_00e])
            assert output.destination_words == c.addressof(weights.words[100 - state.amount_00e])
            assert struct.unpack('<2I', original.cpu.mem_read(0x55f1f0, 8)) == (
                0x558cf0 + state.amount_00e * 256, 0x558cf0 + (100 - state.amount_00e) * 256)
        else:
            assert (output.source_weights, output.destination_weights,
                    output.source_words, output.destination_words) == previous
        enabled = state.flag_73a == 1
        assert output.cycle_enabled == enabled and output.cycle == (cycle if enabled else 0)
        assert struct.unpack('<I', original.cpu.mem_read(0x54cdcc, 4))[0] == (
            0x54cdd0 if enabled else 0x54d1d0)
        if enabled:
            pointers = struct.unpack('<256I', original.cpu.mem_read(0x54cdd0, 1024))
            assert pointers == tuple((value + cycle * 4) & 0xffffffff for value in bases)
    before = bytes(output)
    state.flag_739, state.amount_00e = 1, 255
    assert native.vertrix_render_prepare(state, cycle, c.byref(weights), c.byref(bank),
        hues, len(hue_bytes), c.byref(output)) == 0
    assert bytes(output) == before
    report = {'status': 'passed', 'cases': 4096,
        'scope': 'Complete original4ae250 executes unchanged including4754e0. '
                 'Fixed color, conditional weight bindings, signed map shifts and '
                 'auxiliary cycling decisions match native preparation. Native bindings '
                 'borrow table arrays rather than original addresses. Full actor draw '
                 'preparation, selected map resolution and playable application remain unfinished.'}
    (args.build_dir / 'render-preparation-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
