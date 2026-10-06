"""Compare persistent row/volume-column integration across consecutive ticks."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD
from verify_mixer_row import State as Row
from verify_sequence_advance import row_state, reconstruct
from verify_mixer_volume_column import State as Column, NAMES, OFFSETS


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'sequence-volume.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / n) for n in ('sequencer.c', 'mixer.c', 'xm.c', 'vf.c', 'audio.c')], '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    function = native.vertrix_sequence_volume
    function.argtypes = [ctypes.c_int32, ctypes.POINTER(Row), ctypes.POINTER(Column)]
    original = Original(args.executable)
    rng = random.Random(0x40dc81)
    sequences = 10000
    ticks = 6
    for index in range(sequences):
        data = bytearray(rng.randbytes(180))
        struct.pack_into('<II', data, 52, 0, 0)
        if index % 3 == 0:
            struct.pack_into('<II', data, 16, rng.randrange(65), rng.randrange(65))
            struct.pack_into('<I', data, 28, rng.randrange(256))
            row = row_state(data)
            column = Column(* [struct.unpack_from('<I', data, o)[0] for o in OFFSETS], data[60], data[1])
        for tick_index in range(ticks):
            tick = tick_index % 3
            if not tick:
                command = index % 256 if tick_index == 0 else rng.randrange(256)
                parameter = rng.randrange(256)
                data[2] = command
                data[4] = parameter
                row.selection.volume = command
                row.parameter = parameter
                original.cpu.mem_write(BOARD, bytes(data))
                original.cpu.mem_write(0x531b4c, struct.pack('<i', tick))
            original.call(0x40dc80, eax=BOARD)
            assert function(tick, ctypes.byref(row), ctypes.byref(column))
            actual = bytearray(reconstruct(data, row))
            for name, offset in (('portamento_speed', 96), ('portamento_target', 100), ('vibrato_depth', 68), ('vibrato_speed', 72)):
                struct.pack_into('<I', actual, offset, getattr(column, name))
            expected = bytes(original.cpu.mem_read(BOARD, 180))
            assert bytes(actual) == expected, (index, tick_index)
            for name, offset in zip(NAMES, OFFSETS):
                assert getattr(column, name) == struct.unpack_from('<I', expected, offset)[0], (index, tick_index, name)
            assert column.flags == row.selection.flags == expected[1]
            data = actual
    before = bytes(row), bytes(column)
    assert not function(0, None, ctypes.byref(column)) and (bytes(row), bytes(column)) == before
    assert not function(0, ctypes.byref(row), None) and (bytes(row), bytes(column)) == before
    report = {'status': 'passed', 'sequences': sequences, 'ticks_per_sequence': ticks, 'integrated_volume_ticks': sequences * ticks, 'scope': 'Complete original 0x40dc80 across six consecutive ticks per fixture, row-authoritative shared fields and persistent vibrato/portamento memory. Whole 180-byte channel and shared-state consistency comparisons, all command bytes and realistic/full-width initial values. Excludes main effect dispatch and complete tick orchestration.'}
    (build / 'sequence-volume-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
