"""Compare sequencer volume effects followed by full instrument playback."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BOARD, MASK
from verify_mixer_publish import Command
from verify_sequence_pitch_effect import Memory
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP
from verify_sequence_advance import row_state, reconstruct, INSTRUMENT_BASE
from verify_mixer_row import State as Row
from verify_mixer_volume_column import State as Column, OFFSETS
from verify_mixer_playback_tick import State as Playback, Instrument, Envelope
from verify_mixer_envelope import Point, State as EnvelopeState
from verify_mixer_instrument_vibrato import State as Vibrato


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'sequence-playback.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / n) for n in ('sequencer.c', 'mixer.c', 'xm.c', 'vf.c', 'audio.c')], '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_sequence_volume.argtypes = [ctypes.c_int32, ctypes.POINTER(Row), ctypes.POINTER(Column)]
    native.vertrix_sequence_playback.argtypes = [ctypes.POINTER(Instrument), ctypes.POINTER(Row), ctypes.POINTER(Playback)]
    native.vertrix_sequence_channel_effect.argtypes = [ctypes.c_int32, ctypes.c_int, ctypes.POINTER(Row), ctypes.POINTER(Column), ctypes.POINTER(Memory)]
    native.vertrix_sequence_publish.argtypes = [ctypes.c_uint32, ctypes.c_int, ctypes.c_uint32, ctypes.c_uint32, ctypes.POINTER(Row), ctypes.POINTER(Playback), ctypes.POINTER(Command), ctypes.POINTER(ctypes.c_size_t)]
    original = Original(args.executable)
    rng = random.Random(0x40e031)
    sequences = 8000
    ticks = 6
    events = []
    addresses = (0x40adb0, 0x40ade0, 0x40add0, 0x40adf0, 0x40ae00, 0x40ae10, 0x40adc0)
    def capture(cpu, address, size, context):
        kind = addresses.index(address)
        value = cpu.reg_read(UC_X86_REG_EDX)
        assert cpu.reg_read(UC_X86_REG_EAX) == MASK
        if kind == 0:
            value = (value - 36) & 0xffffffff
            if kind in (2, 6):
                value = 0
                events.append((kind, value))
                stack = cpu.reg_read(UC_X86_REG_ESP)
                target = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
                cpu.reg_write(UC_X86_REG_ESP, stack + 4)
                cpu.reg_write(UC_X86_REG_EIP, target)
    hooks = [original.cpu.hook_add(UC_HOOK_CODE, capture, begin=a, end=a) for a in addresses]
    effects = (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 25, 29, 30, 33, 18, 19, 21, 22, 23, 24, 26, 28, 31, 32, 34, 36, 255)
    for index in range(sequences):
        data = bytearray(rng.randbytes(180))
        descriptor = bytearray(rng.randbytes(248))
        present = (index // 256) % 2
        struct.pack_into('<II', data, 52, INSTRUMENT_BASE if present else 0, 0)
        points = []
        envelopes = []
        for po, mo, so in ((136, 184, 128), (192, 240, 144)):
            array = (Point * 12)(* [Point(rng.randrange(65536), rng.randrange(65536)) for _ in range(12)])
            points.append(array)
            descriptor[po: po + 48] = bytes(array)
            count, flags, sustain, start, end = rng.randrange(13), rng.randrange(256), rng.randrange(12), rng.randrange(12), rng.randrange(12)
            descriptor[mo: mo + 5] = bytes((count, sustain, start, end, flags))
            envelopes.append(Envelope(array, 12, count, flags, sustain, start, end))
            struct.pack_into('<I', data, so + 8, rng.randrange(12))
        instrument = Instrument(* envelopes, descriptor[130], descriptor[132], descriptor[133])
        data[3] = effects[index % len(effects)]
        memory = Memory(* [struct.unpack_from('<I', data, o)[0] for o in (88, 92, 80, 84, 116)], * [data[o] for o in (104, 105, 113, 108, 109, 110, 111)])
        row = row_state(data)
        column = Column(* [struct.unpack_from('<I', data, o)[0] for o in OFFSETS], data[60], data[1])
        playback = Playback(* struct.unpack_from('<4I', data, 20), * struct.unpack_from('<II', data, 120), EnvelopeState(* struct.unpack_from('<4I', data, 128)), EnvelopeState(* struct.unpack_from('<4I', data, 144)), Vibrato(* struct.unpack_from('<III', data, 160), * struct.unpack_from('<II', data, 40), data[0], data[1]))
        original.cpu.mem_write(INSTRUMENT_BASE, bytes(descriptor))
        for ti in range(ticks):
            tick = ti % 3
            if not tick:
                data[2] = index % 256 if not ti else rng.randrange(256)
                data[4] = rng.randrange(256)
                row.selection.volume = data[2]
                row.parameter = data[4]
                if ti:
                    data[3] = rng.choice(effects)
                    row.selection.effect = data[3]
            original.cpu.mem_write(BOARD, bytes(data))
            original.cpu.mem_write(0x531b4c, struct.pack('<i', tick))
            linear = index % 2
            original.cpu.mem_write(0x531b46, bytes([linear]))
            original.call(0x40dc80, eax=BOARD)
            original.call(0x40dc50, eax=BOARD)
            original.call(0x40e030, eax=BOARD)
            assert native.vertrix_sequence_volume(tick, ctypes.byref(row), ctypes.byref(column))
            assert native.vertrix_sequence_channel_effect(tick, linear, ctypes.byref(row), ctypes.byref(column), ctypes.byref(memory))
            assert native.vertrix_sequence_playback(ctypes.byref(instrument) if present else None, ctypes.byref(row), ctypes.byref(playback))
            actual = bytearray(reconstruct(data, row))
            for name, offset in (('portamento_speed', 96), ('portamento_target', 100), ('vibrato_depth', 68), ('vibrato_speed', 72)):
                struct.pack_into('<I', actual, offset, getattr(column, name))
            for name, offset in zip(('down', 'up', 'tremolo_depth', 'tremolo_speed', 'sample_offset'), (88, 92, 80, 84, 116)):
                struct.pack_into('<I', actual, offset, getattr(memory, name))
            for name, offset in zip(('volume', 'pan', 'tremor', 'extra_decrease', 'extra_increase', 'retrigger_transform', 'retrigger_interval'), (104, 105, 113, 108, 109, 110, 111)):
                actual[offset] = getattr(memory, name)
            struct.pack_into('<I', actual, 24, playback.output_volume)
            struct.pack_into('<I', actual, 32, playback.output_pan)
            struct.pack_into('<I', actual, 44, playback.vibrato.output)
            for offset, env in ((128, playback.volume), (144, playback.pan)):
                struct.pack_into('<4I', actual, offset, env.tick, env.value, env.point, env.slope)
            assert bytes(actual) == bytes(original.cpu.mem_read(BOARD, 180)), (index, ti)
            assert playback.vibrato.flags == row.selection.flags
            sample = struct.unpack_from('<I', actual, 56)[0]
            offset = struct.unpack_from('<I', actual, 116)[0]
            global_volume = rng.getrandbits(32) if index % 3 else rng.randrange(65)
            linear = index % 2
            original.cpu.mem_write(0x531b46, bytes([linear]))
            original.cpu.mem_write(0x531b68, struct.pack('<I', global_volume))
            events.clear()
            original.call(0x40e8a0, eax=MASK, edx=BOARD)
            commands = (Command * 7)()
            count = ctypes.c_size_t()
            assert native.vertrix_sequence_publish(global_volume, linear, sample, offset, ctypes.byref(row), ctypes.byref(playback), commands, ctypes.byref(count))
            assert [(commands[i].kind, commands[i].value) for i in range(count.value)] == events, (index, ti)
            actual[1] = row.selection.flags
            assert not row.defaults.flags and not playback.vibrato.flags
            assert bytes(actual) == bytes(original.cpu.mem_read(BOARD, 180)), (index, ti, 'publication')
            data = actual
    instrument.volume.flags = 1
    instrument.volume.points = None
    before = bytes(row), bytes(playback)
    assert not native.vertrix_sequence_playback(ctypes.byref(instrument), ctypes.byref(row), ctypes.byref(playback))
    assert (bytes(row), bytes(playback)) == before
    before = bytes(row), bytes(playback)
    assert not native.vertrix_sequence_publish(64, 0, 0, 0, ctypes.byref(row), ctypes.byref(playback), None, ctypes.byref(count))
    assert (bytes(row), bytes(playback)) == before
    for hook in hooks:
        original.cpu.hook_del(hook)
    report = {'status': 'passed', 'sequences': sequences, 'ticks_per_sequence': ticks, 'integrated_playback_ticks': sequences * ticks, 'scope': 'Consecutive original 0x40dc80, 0x40dc50 for integrated channel effects, complete 0x40e030 and 0x40e8a0 per tick, whole 180-byte channels across persistent row/column/playback state. All volume commands, present/absent instruments, envelope metadata, arbitrary state and shared dirty flags. Invalid native envelope preserves row and playback. Publication order/arguments match with mixer wrappers captured. Invalid command storage preserves row/playback. Covers main effects 0..10, 12, 25, 29, 30, 33 and no-op entries. Other main effects and execution of emitted mixer commands excluded.'}
    (build / 'sequence-playback-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
