"""Compare player indicator phases with original x86, intercepting audio only."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, BOARD
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP, UC_X86_REG_EIP
from verify_number_transition import Timer


class Indicator(c.Structure):
    _fields_ = [('value', c.c_uint32), ('state', c.c_uint32), ('handler', c.c_uint32), ('primary', Timer), ('secondary', Timer)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'player-indicator.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', str(source / 'player_indicator.c'), str(source / 'timer.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_player_indicator_update.argtypes = [c.POINTER(Indicator), c.c_uint32, c.c_uint32, c.POINTER(c.c_int)]
    original = Original(a.executable)
    cpu = original.cpu
    requests = []
    def audio(cpu, address, size, context):
        requests.append((cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX)))
        esp = cpu.reg_read(UC_X86_REG_ESP)
        cpu.reg_write(UC_X86_REG_EIP, struct.unpack('<I', cpu.mem_read(esp, 4))[0])
        cpu.reg_write(UC_X86_REG_ESP, esp + 4)
    cpu.hook_add(UC_HOOK_CODE, audio, begin=0x43c0e0, end=0x43c0e0)
    rng = random.Random(0x44fe80)
    audio_count = 0
    for case in range(8192):
        handler = [0x44fe80, 0x44fed0, 0x44ff30, 0x44ff60][case % 4]
        player_state = rng.choice([0, 1, 2, 3, 4, 0xffffffff])
        elapsed = rng.choice([0, 1, 100, rng.getrandbits(32)])
        state = Indicator(rng.getrandbits(32), rng.getrandbits(32), handler, Timer(rng.getrandbits(32), rng.choice([0, 1, 100, 0xffffffff])), Timer(rng.getrandbits(32), rng.choice([0, 1, 100, 0xffffffff])))
        raw = bytearray(rng.randbytes(0x160))
        offsets = [('value', 0x58), ('state', 0x64), ('handler', 0x154)]
        for name, offset in offsets:
            struct.pack_into('<I', raw, offset, getattr(state, name))
        for timer, offset in [(state.primary, 0xbc), (state.secondary, 0xdc)]:
            struct.pack_into('<2I', raw, offset, timer.counter, timer.period)
        index = rng.randrange(4)
        struct.pack_into('<I', raw, 4, index)
        cpu.mem_write(BOARD, bytes(raw))
        cpu.mem_write(0x540f88 + 4 * index, struct.pack('<I', 0x804000))
        cpu.mem_write(0x80418c, struct.pack('<I', player_state))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        command = rng.getrandbits(32)
        cpu.mem_write(0x4f81a0, struct.pack('<I', command))
        requests.clear()
        original.call(handler, eax=BOARD)
        notify = c.c_int(- 1)
        assert native.vertrix_player_indicator_update(c.byref(state), player_state, elapsed, c.byref(notify))
        assert requests == ([(0x804000, command)] if notify.value else []), case
        audio_count += notify.value
        for name, offset in offsets:
            struct.pack_into('<I', raw, offset, getattr(state, name))
        for timer, offset in [(state.primary, 0xbc), (state.secondary, 0xdc)]:
            struct.pack_into('<2I', raw, offset, timer.counter, timer.period)
        assert bytes(raw) == bytes(cpu.mem_read(BOARD, len(raw))), case
    report = {'status': 'passed', 'cases': 8192, 'audio_requests': audio_count, 'scope': 'All four original indicator handlers with actual player-state predicate ' 'and timer helpers. Whole object and audio request match; only43c0e0 ' 'audio routing is intercepted. Full player/application scheduling remains unfinished.'}
    (a.build_dir / 'player-indicator-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
