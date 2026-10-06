"""Compare complete original row advancement with channel initialization."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, MASK, BLOCKS
from verify_mixer_sequence_row import State as Sequence, NAMES as SN, OFFSETS as SO
from verify_mixer_row import State as Row, View
from verify_mixer_row_instrument import Instrument, Defaults
from verify_mixer_sample_selection import State as Selection, Pitch
from verify_mixer_timed_trigger import Instrument as Trigger
from verify_mixer_trigger_reset import State as Reset, NAMES, OFFSETS, BYTES


class Pattern(ctypes.Structure):
    _fields_ = [('channels', ctypes.c_uint16), ('rows', ctypes.c_uint16), ('size', ctypes.c_uint16), ('packed', ctypes.c_void_p)]


class Reader(ctypes.Structure):
    _fields_ = [('data', ctypes.c_void_p), ('size', ctypes.c_size_t), ('cursor', ctypes.c_size_t)]
INSTRUMENT_BASE = 0x808000
SAMPLE_BASE = 0x80a000


def row_state(data):
    instrument_pointer, sample_pointer = struct.unpack_from('<II', data, 52)
    selected = 0 if not instrument_pointer else (instrument_pointer - INSTRUMENT_BASE) // 252 + 1
    owner = 0 if not sample_pointer else (sample_pointer - SAMPLE_BASE) // 240 + 1
    sample = 0xffffffff if not sample_pointer else ((sample_pointer - SAMPLE_BASE) % 240) // 60
    selection = Selection(sample, struct.unpack_from('<i', data, 12)[0], struct.unpack_from('<i', data, 8)[0], * struct.unpack_from('<II', data, 36), data[7], data[0], data[6], data[3], data[2], data[1])
    reset = Reset(* [struct.unpack_from('<I', data, o)[0] for o in OFFSETS], * [data[o] for o in BYTES])
    return Row(Instrument(selected, data[5]), owner, selection, reset, Defaults(* struct.unpack_from('<II', data, 16), struct.unpack_from('<I', data, 28)[0], data[1]), data[4])


def reconstruct(data, state):
    actual = bytearray(data)
    sel = state.selection
    actual[0: 8] = bytes((sel.active, sel.flags, sel.volume, sel.effect, state.parameter, state.instrument.number, sel.mapping, sel.note))
    struct.pack_into('<ii', actual, 8, sel.finetune, sel.relative)
    struct.pack_into('<II', actual, 36, sel.base, sel.output)
    struct.pack_into('<II', actual, 16, state.defaults.base, state.defaults.output)
    struct.pack_into('<I', actual, 28, state.defaults.pan)
    struct.pack_into('<I', actual, 52, 0 if not state.instrument.selected else INSTRUMENT_BASE + (state.instrument.selected - 1) * 252)
    struct.pack_into('<I', actual, 56, 0 if sel.selected == 0xffffffff else SAMPLE_BASE + (state.owner - 1) * 240 + sel.selected * 60)
    for name, offset in zip(NAMES, OFFSETS):
        struct.pack_into('<I', actual, offset, getattr(state.reset, name))
    for name, offset in zip(('waveform', 'state_112', 'state_114', 'state_115'), BYTES):
        actual[offset] = getattr(state.reset, name)
    return bytes(actual)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'sequence-advance.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / n) for n in ('sequencer.c', 'mixer.c', 'xm.c', 'vf.c', 'audio.c')], '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    function = native.vertrix_sequence_advance
    function.argtypes = [ctypes.c_uint16, ctypes.c_uint16, ctypes.c_void_p, ctypes.c_size_t, ctypes.POINTER(Pattern), ctypes.c_uint16, ctypes.c_int32, ctypes.c_int, ctypes.c_uint8, ctypes.POINTER(View), ctypes.c_uint16, ctypes.POINTER(Sequence), ctypes.POINTER(Reader), ctypes.POINTER(Row), ctypes.c_size_t]
    original = Original(args.executable)
    rng = random.Random(0x40ea89)
    cases = 24000
    outcome = [0] * 4
    for index in range(cases):
        instrument_count = (index // 4) % 3
        views = (View * 2)()
        keep = []
        for owner in range(instrument_count):
            descriptor = bytearray(rng.randbytes(252))
            samples = rng.randbytes(240)
            mapping = (ctypes.c_uint8 * 96)(* [rng.randrange(6) for _ in range(96)])
            pitches = (Pitch * 4)(* [Pitch(* struct.unpack_from('<bb', samples, i * 60 + 34)) for i in range(4)])
            volumes = (ctypes.c_uint8 * 4)(* [samples[i * 60 + 32] for i in range(4)])
            pans = (ctypes.c_uint8 * 4)(* [samples[i * 60 + 33] for i in range(4)])
            descriptor[32: 128] = bytes(mapping)
            struct.pack_into('<H', descriptor, 128, 4)
            struct.pack_into('<I', descriptor, 248, SAMPLE_BASE + owner * 240)
            views[owner] = View(Trigger(mapping, pitches, 4, struct.unpack_from('<H', descriptor, 134)[0], descriptor[188], descriptor[244], descriptor[131], descriptor[132]), volumes, pans)
            keep.extend((mapping, pitches, volumes, pans))
            original.cpu.mem_write(INSTRUMENT_BASE + owner * 252, bytes(descriptor))
            original.cpu.mem_write(SAMPLE_BASE + owner * 240, samples)
        region = bytearray(rng.randbytes(64))
        region[0] = index % 256
        channels = index % 4
        struct.pack_into('<I', region, 4, channels)
        for offset, value in ((12, rng.randrange(5)), (16, 3), (24, rng.randrange(5)), (44, rng.randrange(5)), (48, rng.randrange(4))):
            struct.pack_into('<I', region, offset, value)
        sequence = Sequence(* [struct.unpack_from('<I', region, o)[0] for o in SO], region[0])
        orders = (ctypes.c_uint8 * 5)(* [rng.randrange(4) for _ in range(5)])
        song_length = 4
        restart = index % 6
        buffers = []
        patterns = (Pattern * 2)()
        metadata = bytearray(24)
        for p in range(3):
            data = bytearray()
            for cell in range(32):
                event = bytearray(rng.randbytes(5))
                event[1] = rng.randrange(4)
                header = rng.randrange(128, 256)
                data.append(header)
                data.extend(event[f] for f in range(5) if header & (1 << f))
            storage = (ctypes.c_uint8 * len(data)).from_buffer_copy(data)
            buffers.append(storage)
            original.cpu.mem_write(BLOCKS + p * 4096, bytes(data))
            if p < 2:
                rows = rng.randrange(2, 6)
                patterns[p] = Pattern(channels, rows, len(data), ctypes.addressof(storage))
                struct.pack_into('<H', metadata, p * 12 + 4, rows)
                struct.pack_into('<I', metadata, p * 12 + 8, BLOCKS + p * 4096)
        reader = Reader(ctypes.addressof(buffers[2]), len(buffers[2]), 0)
        records = bytearray(rng.randbytes(channels * 180))
        native_rows = (Row * channels)()
        for c in range(channels):
            selected = rng.randrange(instrument_count + 1)
            owner = rng.randrange(instrument_count + 1)
            instrument_pointer = 0 if not selected else INSTRUMENT_BASE + (selected - 1) * 252
            sample_pointer = 0 if not owner else SAMPLE_BASE + (owner - 1) * 240 + rng.randrange(4) * 60
            struct.pack_into('<II', records, c * 180 + 52, instrument_pointer, sample_pointer)
            native_rows[c] = row_state(records[c * 180: (c + 1) * 180])
        song = bytearray(344)
        struct.pack_into('<HH', song, 34, song_length, restart)
        struct.pack_into('<H', song, 40, 2)
        song[48: 53] = bytes(orders)
        struct.pack_into('<I', song, 336, MASK + 512)
        struct.pack_into('<H', song, 42, instrument_count)
        struct.pack_into('<I', song, 340, INSTRUMENT_BASE)
        original.cpu.mem_write(MASK, bytes(song))
        original.cpu.mem_write(MASK + 512, bytes(metadata))
        original.cpu.mem_write(0x53043c, struct.pack('<I', MASK))
        original.cpu.mem_write(0x530440, struct.pack('<I', BLOCKS + 8192))
        original.cpu.mem_write(0x531b44, bytes(region))
        if channels:
            original.cpu.mem_write(0x530444, bytes(records))
        linear = index % 2
        module = rng.randrange(256)
        original.cpu.mem_write(0x531b46, bytes([linear]))
        original.cpu.mem_write(0x531b47, bytes([module]))
        region[2: 4] = bytes((linear, module))
        original.call(0x40e940)
        result = function(song_length, restart, orders, 5, patterns, 2, channels, linear, module, views, instrument_count, ctypes.byref(sequence), ctypes.byref(reader), native_rows, channels)
        assert result >= 0, index
        outcome[result] += 1
        actual = bytearray(region)
        actual[0] = sequence.flags
        for name, offset in zip(SN, SO):
            struct.pack_into('<I', actual, offset, getattr(sequence, name))
        expected_globals = bytes(original.cpu.mem_read(0x531b44, 60))
        assert bytes(actual[: 60]) == expected_globals, index
        expected_pointer = 0
        if reader.data:
            p = next(p for p, b in enumerate(buffers) if ctypes.addressof(b) == reader.data)
            expected_pointer = BLOCKS + p * 4096 + reader.cursor
        assert expected_pointer == struct.unpack('<I', original.cpu.mem_read(0x530440, 4))[0], index
        for c in range(channels):
            assert reconstruct(records[c * 180: (c + 1) * 180], native_rows[c]) == bytes(original.cpu.mem_read(0x530444 + c * 180, 180)), (index, c)
    assert all(outcome)
    sequence.flags = 1
    sequence.pending_order = 0
    sequence.pending_row = 0
    orders[0] = 0
    patterns[0].size = 0
    before = bytes(sequence), bytes(reader), bytes(native_rows)
    assert function(4, 0, orders, 5, patterns, 2, 1, 0, 0, views, instrument_count, ctypes.byref(sequence), ctypes.byref(reader), native_rows, 3) == - 1
    assert (bytes(sequence), bytes(reader), bytes(native_rows)) == before
    report = {'status': 'passed', 'advance_cases': cases, 'outcomes': outcome, 'scope': 'Complete original 0x40e940, no hooks, zero through three channels and zero through two instruments, mixed packed events, row jumps/breaks, invalid patterns, restarts, seeking and complete per-channel initialization. Includes sample mappings, signed tuning, cross-instrument sample retention, envelope resets/releases and defaults. Whole globals/channels and packed cursor comparisons. Full sequencer tick execution remains unfinished.'}
    (build / 'sequence-advance-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
