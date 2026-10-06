"""Compare shared volume-column and main pitch-effect state with original dispatch."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD
from verify_mixer_row import State as Row
from verify_mixer_volume_column import State as Column, NAMES, OFFSETS
from verify_sequence_advance import row_state, reconstruct, INSTRUMENT_BASE, SAMPLE_BASE
from verify_mixer_timed_trigger import Instrument
from verify_mixer_sample_selection import Pitch


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
    library = build / 'sequence-note.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / n) for n in ('sequencer.c', 'mixer.c', 'xm.c', 'vf.c', 'audio.c')], '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_sequence_volume.argtypes = [ctypes.c_int32, ctypes.POINTER(Row), ctypes.POINTER(Column)]
    native.vertrix_sequence_note_effect.argtypes = [ctypes.c_int32, ctypes.c_int, ctypes.POINTER(Instrument), ctypes.POINTER(Row), ctypes.POINTER(Column), ctypes.POINTER(Memory)]
    original = Original(args.executable)
    rng = random.Random(0x40dc51)
    sequences = 12000
    ticks = 6
    effects = (20, 27)
    for index in range(sequences):
        data = bytearray(rng.randbytes(180))
        present = index % 3 != 0
        struct.pack_into('<II', data, 52, INSTRUMENT_BASE if present else 0, SAMPLE_BASE + 240 + rng.randrange(4) * 60)
        data[110] %= 16
        data[7] = rng.randrange(256)
        descriptor = bytearray(rng.randbytes(252))
        sample_bytes = rng.randbytes(240)
        mapping = (ctypes.c_uint8 * 96)(* [rng.randrange(7) for _ in range(96)])
        pitches = (Pitch * 4)(* [Pitch(* struct.unpack_from('<bb', sample_bytes, i * 60 + 34)) for i in range(4)])
        descriptor[32: 128] = bytes(mapping)
        struct.pack_into('<H', descriptor, 128, 4)
        struct.pack_into('<I', descriptor, 248, SAMPLE_BASE)
        instrument = Instrument(mapping, pitches, 4, 0, descriptor[188], 0, 0, 0)
        original.cpu.mem_write(INSTRUMENT_BASE, bytes(descriptor))
        original.cpu.mem_write(SAMPLE_BASE, sample_bytes)
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
            assert native.vertrix_sequence_note_effect(tick, linear, ctypes.byref(instrument) if present else None, ctypes.byref(row), ctypes.byref(column), ctypes.byref(memory))
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
    assert not native.vertrix_sequence_note_effect(0, 0, None, ctypes.byref(row), ctypes.byref(column), ctypes.byref(memory))
    assert (bytes(row), bytes(column), bytes(memory)) == before
    row.selection.effect = 27
    memory.retrigger_transform = 16
    memory.retrigger_interval = 0
    before = bytes(row), bytes(column), bytes(memory)
    assert not native.vertrix_sequence_note_effect(1, 0, None, ctypes.byref(row), ctypes.byref(column), ctypes.byref(memory))
    assert (bytes(row), bytes(column), bytes(memory)) == before
    report = {'status': 'passed', 'sequences': sequences, 'integrated_ticks': sequences * ticks, 'scope': 'Original complete volume-column dispatch followed by main dispatch for effects 20/27 with present/absent instruments, cross-instrument retained samples and envelope release flags; whole 180-byte channel comparisons, persistent shared memories and flags, both pitch modes. Unsupported effect preserves all native state. Sample selection and counter wrapping covered; envelope counters/resets remain intact. Other effects, full instrument playback and audio excluded.'}
    (build / 'sequence-note-effect-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
