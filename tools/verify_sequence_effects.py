"""Compare shared volume-column and main pitch-effect state with original dispatch."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK
from verify_mixer_row import State as Row
from verify_mixer_volume_column import State as Column, NAMES, OFFSETS
from verify_sequence_advance import row_state, reconstruct, INSTRUMENT_BASE, SAMPLE_BASE
from verify_mixer_timed_trigger import Instrument
from verify_mixer_sample_selection import Pitch
from verify_mixer_sequence_row import State as Sequence, NAMES as SN, OFFSETS as SO
from verify_mixer_global_effects import State as Global
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ESP, UC_X86_REG_EIP


class Memory(ctypes.Structure):
    _fields_ = [(n, ctypes.c_uint32) for n in ('down', 'up', 'tremolo_depth', 'tremolo_speed', 'sample_offset')] + [(n, ctypes.c_uint8) for n in ('volume', 'pan', 'tremor', 'extra_decrease', 'extra_increase', 'retrigger_transform', 'retrigger_interval')]


class Extended(ctypes.Structure):
    _fields_ = [('start', ctypes.c_uint32), ('remaining', ctypes.c_uint32), ('decrease', ctypes.c_uint8), ('increase', ctypes.c_uint8), ('glissando', ctypes.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'sequence-effects.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / n) for n in ('sequencer.c', 'mixer.c', 'xm.c', 'vf.c', 'audio.c')], '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_sequence_volume.argtypes = [ctypes.c_int32, ctypes.POINTER(Row), ctypes.POINTER(Column)]
    Callback = ctypes.CFUNCTYPE(None, ctypes.c_uint8, ctypes.c_uint32, ctypes.c_uint32, ctypes.c_void_p)
    native.vertrix_sequence_effect.argtypes = [ctypes.c_int32, ctypes.c_int, ctypes.c_uint16, ctypes.POINTER(Instrument), ctypes.POINTER(Row), ctypes.POINTER(Column), ctypes.POINTER(Memory), ctypes.POINTER(Extended), ctypes.POINTER(Sequence), ctypes.POINTER(Global), ctypes.POINTER(ctypes.c_uint32), Callback, ctypes.c_void_p]
    original = Original(args.executable)
    rng = random.Random(0x40dc51)
    sequences = 12000
    ticks = 6
    effects = tuple(range(256))
    events = []
    native_events = []
    callback_address = 0x700100
    def capture(cpu, address, size, context):
        events.append((cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX), cpu.reg_read(UC_X86_REG_EBX)))
        stack = cpu.reg_read(UC_X86_REG_ESP)
        target = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_ESP, stack + 4)
        cpu.reg_write(UC_X86_REG_EIP, target)
        hook = original.cpu.hook_add(UC_HOOK_CODE, capture, begin=callback_address, end=callback_address)
        def native_capture(parameter, order, row, context):
            assert context == 123
            native_events.append((parameter, order, row))
            callback = Callback(native_capture)
            absent_callback = Callback()
    callback_calls = 0
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
        instrument = Instrument(mapping, pitches, 4, struct.unpack_from('<H', descriptor, 134)[0], descriptor[188], descriptor[244], descriptor[131], descriptor[132])
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
        extended = Extended(* struct.unpack_from('<II', data, 172), data[106], data[107], data[61])
        region = bytearray(rng.randbytes(64))
        sequence = Sequence(* [struct.unpack_from('<I', region, o)[0] for o in SO], region[0])
        delay = ctypes.c_uint32(struct.unpack_from('<I', region, 52)[0])
        global_state = Global(* struct.unpack_from('<4I', region, 28), region[0])
        song_length = rng.randrange(65536)
        song = bytearray(344)
        struct.pack_into('<H', song, 34, song_length)
        original.cpu.mem_write(MASK, bytes(song))
        original.cpu.mem_write(0x53043c, struct.pack('<I', MASK))
        callback_present = index % 2 == 0
        struct.pack_into('<I', region, 56, callback_address if callback_present else 0)
        for ti in range(ticks):
            tick = ti % 3
            if not tick:
                if ti:
                    data[3] = rng.choice(effects)
                    row.selection.effect = data[3]
                    data[2] = rng.randrange(256)
                    data[4] = index % 256 if not ti else rng.randrange(256)
                    row.selection.volume = data[2]
                    row.parameter = data[4]
                    region[2] = linear
                    struct.pack_into('<i', region, 8, tick)
                    sequence.tick = tick
                    original.cpu.mem_write(0x531b44, bytes(region))
                    original.cpu.mem_write(BOARD, bytes(data))
                    original.cpu.mem_write(0x531b4c, struct.pack('<i', tick))
                    original.cpu.mem_write(0x531b46, bytes([linear]))
                    events.clear()
                    native_events.clear()
                    original.call(0x40dc80, eax=BOARD)
                    original.call(0x40dc50, eax=BOARD)
            assert native.vertrix_sequence_volume(tick, ctypes.byref(row), ctypes.byref(column))
            assert native.vertrix_sequence_effect(tick, linear, song_length, ctypes.byref(instrument) if present else None, ctypes.byref(row), ctypes.byref(column), ctypes.byref(memory), ctypes.byref(extended), ctypes.byref(sequence), ctypes.byref(global_state), ctypes.byref(delay), callback if callback_present else absent_callback, 123)
            actual = bytearray(reconstruct(data, row))
            for name, offset in zip(NAMES, OFFSETS):
                struct.pack_into('<I', actual, offset, getattr(column, name))
            for name, offset in zip(('down', 'up', 'tremolo_depth', 'tremolo_speed', 'sample_offset'), (88, 92, 80, 84, 116)):
                struct.pack_into('<I', actual, offset, getattr(memory, name))
            for name, offset in zip(('volume', 'pan', 'tremor', 'extra_decrease', 'extra_increase', 'retrigger_transform', 'retrigger_interval'), (104, 105, 113, 108, 109, 110, 111)):
                actual[offset] = getattr(memory, name)
            struct.pack_into('<II', actual, 172, extended.start, extended.remaining)
            actual[106] = extended.decrease
            actual[107] = extended.increase
            actual[61] = extended.glissando
            global_actual = bytearray(region)
            global_actual[0] = sequence.flags
            for name, offset in zip(SN, SO):
                struct.pack_into('<I', global_actual, offset, getattr(sequence, name))
            struct.pack_into('<4I', global_actual, 28, global_state.speed, global_state.tempo, global_state.volume, global_state.memory)
            struct.pack_into('<I', global_actual, 52, delay.value)
            assert events == native_events, (index, ti, 'callback')
            callback_calls += len(events)
            assert bytes(global_actual) == bytes(original.cpu.mem_read(0x531b44, 64)), (index, ti, 'globals')
            region = global_actual
            assert bytes(actual) == bytes(original.cpu.mem_read(BOARD, 180)), (index, ti, data[3])
            assert row.selection.flags == row.defaults.flags == column.flags
            data = actual
            before = bytes(row), bytes(column), bytes(memory), bytes(extended), bytes(sequence), bytes(global_state), delay.value
            assert not native.vertrix_sequence_effect(0, 0, 1, None, ctypes.byref(row), ctypes.byref(column), ctypes.byref(memory), None, ctypes.byref(sequence), ctypes.byref(global_state), ctypes.byref(delay), absent_callback, None)
            assert (bytes(row), bytes(column), bytes(memory), bytes(extended), bytes(sequence), bytes(global_state), delay.value) == before
            original.cpu.hook_del(hook)
            assert callback_calls
    report = {'status': 'passed', 'sequences': sequences, 'integrated_ticks': sequences * ticks, 'callback_calls': callback_calls, 'scope': 'Complete original volume-column and all 36 main dispatcher entries plus ignored commands, whole 180-byte channels and 64-byte globals across six consecutive ticks. Both pitch modes, present/absent instruments, retained sample ownership, reset and effect memory, pattern/global controls and callbacks. Only application callback is captured. Invalid native storage preserves state. Excludes full instrument playback, row advancement and audio.'}
    (build / 'sequence-effects-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
