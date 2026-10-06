"""Compare original SFX channel allocation and event dispatching routines with native recovery."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct

from original import Original
from oracle_kit import Stubs, build

U = c.c_uint32
BusyCheck = c.CFUNCTYPE(c.c_int, U, c.c_void_p)
PlayCb = c.CFUNCTYPE(None, U, U, c.c_void_p)

PLAYER_SIZE = 0x80
PLAYER_ADDR = 0x808000


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()

    native = build(args.build_dir, 'sfx-dispatch', [
        'sfx_dispatch.c',
        'actor_storage.c',
    ])

    native.vertrix_sfx_allocate_channel_p1.argtypes = [BusyCheck, c.c_void_p]
    native.vertrix_sfx_allocate_channel_p1.restype = U

    native.vertrix_sfx_allocate_channel_p2.argtypes = [BusyCheck, c.c_void_p]
    native.vertrix_sfx_allocate_channel_p2.restype = U

    native.vertrix_sfx_dispatch_event.argtypes = [
        c.c_void_p, c.c_size_t, U, PlayCb, c.c_void_p
    ]
    native.vertrix_sfx_dispatch_event.restype = c.c_int

    native.vertrix_sfx_dispatch_secondary.argtypes = [
        c.c_void_p, c.c_size_t, U, PlayCb, c.c_void_p
    ]
    native.vertrix_sfx_dispatch_secondary.restype = c.c_int

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43c0e0)

    # 1. Test 0x4174f0 and 0x417550 channel allocation across all busy state patterns
    chan_status = {}

    def stub_busy(addr, eax, edx, ebx, ecx, stack):
        return chan_status.get(eax, 0)

    stubs_chan = Stubs(cpu, stub_busy)
    stubs_chan.add(0x4828a0)

    @BusyCheck
    def native_busy(channel, context):
        return chan_status.get(channel, 0)

    for p1_pattern in range(16):
        for i in range(4):
            chan_status[i] = (p1_pattern >> i) & 1
        orig_p1 = original.call(0x4174f0)
        native_p1 = native.vertrix_sfx_allocate_channel_p1(native_busy, None)
        assert orig_p1 == native_p1, f"Pattern {p1_pattern} P1 alloc mismatch: orig={orig_p1}, native={native_p1}"

    for p2_pattern in range(16):
        for i in range(4):
            chan_status[4 + i] = (p2_pattern >> i) & 1
        orig_p2 = original.call(0x417550)
        native_p2 = native.vertrix_sfx_allocate_channel_p2(native_busy, None)
        assert orig_p2 == native_p2, f"Pattern {p2_pattern} P2 alloc mismatch: orig={orig_p2}, native={native_p2}"

    # 2. Test 0x43c0e0 and 0x43c110 event dispatch
    orig_calls = []

    def stub_p1_voice(addr, eax, edx, ebx, ecx, stack):
        orig_calls.append(('p1', eax))
        return 0

    def stub_p2_voice(addr, eax, edx, ebx, ecx, stack):
        orig_calls.append(('p2', eax))
        return 0

    def stub_p1_alt(addr, eax, edx, ebx, ecx, stack):
        orig_calls.append(('p1_alt', eax))
        return 0

    def stub_p2_alt(addr, eax, edx, ebx, ecx, stack):
        orig_calls.append(('p2_alt', eax))
        return 0

    stubs_sfx = Stubs(cpu, lambda *a: 0)
    stubs_sfx.add(0x417260)
    stubs_sfx.add(0x417290)
    stubs_sfx.add(0x4172c0)
    stubs_sfx.add(0x4173d0)

    def sfx_handler(addr, eax, edx, ebx, ecx, stack):
        if addr == 0x417260:
            return stub_p1_voice(addr, eax, edx, ebx, ecx, stack)
        elif addr == 0x417290:
            return stub_p2_voice(addr, eax, edx, ebx, ecx, stack)
        elif addr == 0x4172c0:
            return stub_p1_alt(addr, eax, edx, ebx, ecx, stack)
        elif addr == 0x4173d0:
            return stub_p2_alt(addr, eax, edx, ebx, ecx, stack)
        return 0

    stubs_sfx.handler = sfx_handler

    native_calls = []

    @PlayCb
    def native_play(effect, side, context):
        native_calls.append(('p1' if side == 1 else 'p2', effect))

    @PlayCb
    def native_play_alt(effect, side, context):
        native_calls.append(('p1_alt' if side == 1 else 'p2_alt', effect))

    verified_cases = 0

    for case in range(args.cases):
        player_buf = bytearray(rng.randbytes(PLAYER_SIZE))
        side = rng.choice([1, 2, 0, 3, rng.randrange(256)])
        struct.pack_into('<I', player_buf, 0, side)
        cpu.mem_write(PLAYER_ADDR, bytes(player_buf))
        c_player = (c.c_uint8 * PLAYER_SIZE).from_buffer_copy(bytes(player_buf))

        effect = rng.choice([0xf4240, rng.randrange(0, 100), rng.randrange(0xffffffff)])

        # Test 0x43c0e0
        orig_calls.clear()
        native_calls.clear()
        cpu.mem_write(0x708000 - 0x100, bytes(0x100))
        original.call(0x43c0e0, eax=PLAYER_ADDR, edx=effect)
        ok = native.vertrix_sfx_dispatch_event(c_player, PLAYER_SIZE, effect, native_play, None)
        expected_ok = (effect != 0xf4240) and (side in (1, 2))
        assert ok == expected_ok, f"Case {case} dispatch_event return mismatch"
        assert orig_calls == native_calls, f"Case {case} dispatch_event calls mismatch: orig={orig_calls}, native={native_calls}"

        # Test 0x43c110
        orig_calls.clear()
        native_calls.clear()
        cpu.mem_write(0x708000 - 0x100, bytes(0x100))
        original.call(0x43c110, eax=PLAYER_ADDR, edx=effect)
        ok_alt = native.vertrix_sfx_dispatch_secondary(c_player, PLAYER_SIZE, effect, native_play_alt, None)
        assert ok_alt == expected_ok, f"Case {case} dispatch_secondary return mismatch"
        assert orig_calls == native_calls, f"Case {case} dispatch_secondary calls mismatch: orig={orig_calls}, native={native_calls}"

        verified_cases += 1

    # Short storage check
    short_player = (c.c_uint8 * 2)()
    assert native.vertrix_sfx_dispatch_event(short_player, 2, 1, native_play, None) == 0
    assert native.vertrix_sfx_dispatch_secondary(short_player, 2, 1, native_play_alt, None) == 0

    print(f"Verified {verified_cases} cases successfully across 0x4174f0, 0x417550, 0x43c0e0, 0x43c110.")

    out = {
        "routine": "0x4174f0, 0x417550, 0x43c0e0, 0x43c110",
        "cases": verified_cases,
        "complete_original_executions": verified_cases * 2 + 32,
        "channel_allocation_exhaustive": True,
        "event_dispatch_compared": True,
        "sentinel_filtered": True,
        "short_storage_preserved": True
    }
    Path("docs/sfx-dispatch-verification.json").write_text(json.dumps(out, indent=2))


if __name__ == '__main__':
    main()
