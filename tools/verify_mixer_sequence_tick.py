"""Verify original tick advancement decision and pending-update scheduling."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_ESP, UC_X86_REG_EIP
from original import Original, RETURN


class State(ctypes.Structure):
    _fields_ = [(name, ctypes.c_uint32) for name in ('tick', 'speed', 'delay', 'tempo')] + [('flags', ctypes.c_uint8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'sequence-tick.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', str(source / 'mixer.c'), '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    native.vertrix_mixer_sequence_begin.argtypes = [ctypes.POINTER(State)]
    native.vertrix_mixer_sequence_pending.argtypes = [ctypes.POINTER(State), ctypes.POINTER(ctypes.c_uint8), ctypes.c_size_t, ctypes.POINTER(ctypes.c_uint32), ctypes.POINTER(ctypes.c_int)]
    original = Original(args.executable)
    rng = random.Random(0x40eb10)
    rows = []
    tempos = []
    def called(cpu, address, size, data):
        if address == 0x40e940:
            rows.append(1)
        else:
            tempos.append(cpu.reg_read(UC_X86_REG_EAX))
        stack = cpu.reg_read(UC_X86_REG_ESP)
        target = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_ESP, stack + 4)
        cpu.reg_write(UC_X86_REG_EIP, target)
    def stopped(cpu, address, size, data):
        cpu.reg_write(UC_X86_REG_EIP, 0x40eb3a)
    hooks = [original.cpu.hook_add(UC_HOOK_CODE, called, begin=a, end=a) for a in (0x40e940, 0x40ac20)]
    hooks.append(original.cpu.hook_add(UC_HOOK_CODE, stopped, begin=0x40ec24, end=0x40ec24))
    cases = 40000
    try:
        for index in range(cases):
            region = bytearray(rng.randbytes(64))
            flags = index % 256
            tick = (0, 0xffffffff, rng.getrandbits(32))[index % 3]
            speed = rng.getrandbits(32)
            region[0] = flags
            struct.pack_into('<I', region, 8, tick)
            struct.pack_into('<I', region, 28, speed)
            state = State(tick, speed, 0, 0, flags)
            original.cpu.mem_write(0x531b44, bytes(region))
            rows.clear()
            original.call(0x40eb10, stop=0x40eb3a)
            result = native.vertrix_mixer_sequence_begin(ctypes.byref(state))
            assert result == (0 if flags & 0x20 else 2 if rows else 1), index
            actual = bytearray(region)
            struct.pack_into('<I', actual, 8, state.tick)
            actual[0] = state.flags
            assert bytes(actual) == bytes(original.cpu.mem_read(0x531b44, 64)), index
        for index in range(cases):
            region = bytearray(rng.randbytes(64))
            flags = index % 256
            tick = 0 if index % 3 == 0 else rng.getrandbits(32)
            delay = (0, 1, 2, rng.getrandbits(32))[index % 4]
            tempo = rng.getrandbits(32)
            channels = index % 7
            region[0] = flags
            struct.pack_into('<I', region, 4, channels)
            struct.pack_into('<I', region, 8, tick)
            struct.pack_into('<I', region, 32, tempo)
            struct.pack_into('<I', region, 52, delay)
            state = State(tick, struct.unpack_from('<I', region, 28)[0], delay, tempo, flags)
            records = bytearray(rng.randbytes(7 * 180))
            native_flags = (ctypes.c_uint8 * channels)(* [records[i * 180 + 1] for i in range(channels)])
            output = ctypes.c_uint32(rng.getrandbits(32))
            prior = output.value
            changed = ctypes.c_int(- 1)
            original.cpu.mem_write(0x531b44, bytes(region))
            original.cpu.mem_write(0x530444, bytes(records))
            tempos.clear()
            original.call(0x40eb6e, stop=0x40ebf3)
            assert native.vertrix_mixer_sequence_pending(ctypes.byref(state), native_flags, channels, ctypes.byref(output), ctypes.byref(changed))
            assert changed.value == bool(tempos) and output.value == (tempos[0] if tempos else prior)
            actual = bytearray(region)
            actual[0] = state.flags
            struct.pack_into('<I', actual, 52, state.delay)
            assert bytes(actual) == bytes(original.cpu.mem_read(0x531b44, 64)), index
            for i in range(channels):
                records[i * 180 + 1] = native_flags[i]
            assert bytes(records) == bytes(original.cpu.mem_read(0x530444, len(records))), index
    finally:
        for hook in hooks:
            original.cpu.hook_del(hook)
    assert native.vertrix_mixer_sequence_begin(None) == - 1
    before = bytes(state)
    assert not native.vertrix_mixer_sequence_pending(ctypes.byref(state), None, 1, ctypes.byref(output), ctypes.byref(changed)) and bytes(state) == before
    report = {'status': 'passed', 'tick_decision_cases': cases, 'pending_update_cases': cases, 'scope': 'Original 0x40eb10..0x40eb3a decision, row call captured without executing row advancement; original 0x40eb6e..0x40ebf3 pending phase with captured tempo setter. Whole globals/channels, signed wrapping, stopped gate, delay flags and dirty-channel propagation. Excludes row body and effects/envelope/publication orchestration.'}
    (build / 'mixer-sequence-tick-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
