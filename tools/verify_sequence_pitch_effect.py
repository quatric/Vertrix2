"""Compare shared volume-column and main pitch-effect state with original dispatch."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD
from verify_mixer_row import State as Row
from verify_mixer_volume_column import State as Column, NAMES, OFFSETS
from verify_sequence_advance import row_state, reconstruct


class Memory(ctypes.Structure):
    _fields_ = [(n, ctypes.c_uint32) for n in ('down', 'up', 'tremolo_depth', 'tremolo_speed', 'sample_offset')] + [(n, ctypes.c_uint8) for n in ('volume', 'pan', 'tremor', 'extra_decrease', 'extra_increase', 'retrigger_transform', 'retrigger_interval')]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'sequence-pitch.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / n) for n in ('sequencer.c', 'mixer.c', 'xm.c', 'vf.c', 'audio.c')], '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_sequence_volume.argtypes = [ctypes.c_int32, ctypes.POINTER(Row), ctypes.POINTER(Column)]
    native.vertrix_sequence_channel_effect.argtypes = [ctypes.c_int32, ctypes.c_int, ctypes.POINTER(Row), ctypes.POINTER(Column), ctypes.POINTER(Memory)]
    original = Original(args.executable)
    rng = random.Random(0x40dc51)
    sequences = 12000
    ticks = 6
    effects = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 25, 29, 30, 33, 18, 19, 21, 22, 23, 24, 26, 28, 31, 32, 34, 36, 255)
    for index in range(sequences):
        data = bytearray(rng.randbytes(180))
        struct.pack_into('<II', data, 52, 0, 0)
        data[3] = effects[index % len(effects)]
        linear = index % 2
        if index % 3 == 0:
            struct.pack_into('<II', data, 16, rng.randrange(65), rng.randrange(65))
            struct.pack_into('<II', data, 36, rng.randrange(1, 0x7d00), rng.randrange(1, 0x7d00))
            struct.pack_into('<ii', data, 8, rng.randrange(- 128, 128), rng.randrange(- 12, 13))
            data[7] = rng.randrange(1, 97)
        row = row_state(data)
        column = Column(* [struct.unpack_from('<I', data, o)[0] for o in OFFSETS], data[60], data[1])
        memory = Memory(* [struct.unpack_from('<I', data, o)[0] for o in (88, 92, 80, 84, 116)], * [data[o] for o in (104, 105, 113, 108, 109, 110, 111)])
        for ti in range(ticks):
            tick = ti % 3
            if not tick:
                if ti:
                    data[3] = rng.choice(effects)
                    row.selection.effect = data[3]
                data[2] = rng.randrange(256)
                data[4] = rng.randrange(256)
                row.selection.volume = data[2]
                row.parameter = data[4]
            original.cpu.mem_write(BOARD, bytes(data))
            original.cpu.mem_write(0x531b4c, struct.pack('<i', tick))
            original.cpu.mem_write(0x531b46, bytes([linear]))
            original.call(0x40dc80, eax=BOARD)
            original.call(0x40dc50, eax=BOARD)
            assert native.vertrix_sequence_volume(tick, ctypes.byref(row), ctypes.byref(column))
            assert native.vertrix_sequence_channel_effect(tick, linear, ctypes.byref(row), ctypes.byref(column), ctypes.byref(memory))
            actual = bytearray(reconstruct(data, row))
            for name, offset in zip(NAMES, OFFSETS):
                struct.pack_into('<I', actual, offset, getattr(column, name))
            for name, offset in zip(('down', 'up', 'tremolo_depth', 'tremolo_speed', 'sample_offset'), (88, 92, 80, 84, 116)):
                struct.pack_into('<I', actual, offset, getattr(memory, name))
            for name, offset in zip(('volume', 'pan', 'tremor', 'extra_decrease', 'extra_increase', 'retrigger_transform', 'retrigger_interval'), (104, 105, 113, 108, 109, 110, 111)):
                actual[offset] = getattr(memory, name)
            assert bytes(actual) == bytes(original.cpu.mem_read(BOARD, 180)), (index, ti, data[3])
            assert row.selection.flags == row.defaults.flags == column.flags
            data = actual
    row.selection.effect = 11
    before = bytes(row), bytes(column), bytes(memory)
    assert not native.vertrix_sequence_channel_effect(0, 0, ctypes.byref(row), ctypes.byref(column), ctypes.byref(memory))
    assert (bytes(row), bytes(column), bytes(memory)) == before
    report = {'status': 'passed', 'sequences': sequences, 'integrated_ticks': sequences * ticks, 'scope': 'Original complete volume-column dispatch followed by main dispatch for effects 0..10, 12, 25, 29, 30, 33 and no-op entries; whole 180-byte channel comparisons, persistent shared memories and flags, both pitch modes. Unsupported effect preserves all native state. Other main effects, instrument playback and audio excluded.'}
    (build / 'sequence-pitch-effect-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
