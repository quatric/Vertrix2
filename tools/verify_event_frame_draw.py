"""Compare original 0x482e10, 0x482e80, and 0x482f00 with native event_frame_draw recovery."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct

from original import Original
from oracle_kit import Stubs, build

U = c.c_uint32
DirectCb = c.CFUNCTYPE(None, c.c_void_p, U, U, U, c.POINTER(U), c.c_void_p)
BlendCb = c.CFUNCTYPE(None, c.c_void_p, U, U, U, c.POINTER(U), c.c_void_p)
ScaledCb = c.CFUNCTYPE(None, c.c_void_p, U, U, U, c.POINTER(U), c.c_void_p)

ITEM_SIZE = 0x40
ITEM_ADDR = 0x808000


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()

    native = build(args.build_dir, 'event-frame-draw', [
        'event_frame_draw.c',
        'actor_storage.c',
        'event_stack.c',
    ])

    native.vertrix_event_frame_draw_direct.argtypes = [
        c.c_void_p, c.c_size_t, U, U, U, DirectCb, c.c_void_p
    ]
    native.vertrix_event_frame_draw_direct.restype = c.c_int

    native.vertrix_event_frame_draw_blend.argtypes = [
        c.c_void_p, c.c_size_t, U, U, U, U, BlendCb, c.c_void_p
    ]
    native.vertrix_event_frame_draw_blend.restype = c.c_int

    native.vertrix_event_frame_draw_scaled.argtypes = [
        c.c_void_p, c.c_size_t, U, U, U, c.POINTER(U), ScaledCb, c.c_void_p
    ]
    native.vertrix_event_frame_draw_scaled.restype = c.c_int

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x482e10)

    orig_calls = []

    def stub_direct(addr, eax, edx, ebx, ecx, stack):
        event = bytes(cpu.mem_read(eax, 0x1c))
        orig_calls.append(('direct', edx, ebx, ecx, stack[:4], event))
        return 0

    def stub_blend(addr, eax, edx, ebx, ecx, stack):
        event = bytes(cpu.mem_read(eax, 0x1c))
        orig_calls.append(('blend', edx, ebx, ecx, stack[:5], event))
        return 0

    def stub_scaled(addr, eax, edx, ebx, ecx, stack):
        event = bytes(cpu.mem_read(eax, 0x1c))
        orig_calls.append(('scaled', edx, ebx, ecx, stack[:5], event))
        return 0

    stubs = Stubs(cpu, lambda *a: None)
    stubs.add(0x47ce10, 4)
    stubs.handler = stub_direct

    stubs_blend = Stubs(cpu, stub_blend)
    stubs_blend.add(0x47c930, 5)

    stubs_scaled = Stubs(cpu, stub_scaled)
    stubs_scaled.add(0x47cb40, 6)

    native_calls = []

    @DirectCb
    def native_direct(event_ptr, edx, ebx, ecx, stack_ptr, context):
        event = bytes((c.c_uint8 * 0x1c).from_address(event_ptr))
        stack = tuple(stack_ptr[i] for i in range(4))
        native_calls.append(('direct', edx, ebx, ecx, stack, event))

    @BlendCb
    def native_blend(event_ptr, edx, ebx, ecx, stack_ptr, context):
        event = bytes((c.c_uint8 * 0x1c).from_address(event_ptr))
        stack = tuple(stack_ptr[i] for i in range(5))
        native_calls.append(('blend', edx, ebx, ecx, stack, event))

    @ScaledCb
    def native_scaled(event_ptr, edx, ebx, ecx, stack_ptr, context):
        event = bytes((c.c_uint8 * 0x1c).from_address(event_ptr))
        stack = tuple(stack_ptr[i] for i in range(5))
        native_calls.append(('scaled', edx, ebx, ecx, stack, event))

    verified_cases = 0

    for case in range(args.cases):
        item_buf = bytearray(rng.randbytes(ITEM_SIZE))
        # Ensure interesting key values
        item_buf[0x27] = rng.choice([0, 1, 2, 3, 4, 8, 15, 16, 24, 32, rng.randrange(256)])
        cpu.mem_write(ITEM_ADDR, bytes(item_buf))
        c_item = (c.c_uint8 * ITEM_SIZE).from_buffer_copy(bytes(item_buf))

        edx = rng.randrange(0xffffffff)
        ebx = rng.randrange(0xffffffff)
        ecx = rng.randrange(0xffffffff)

        # 1. Test 0x482e10 (direct)
        orig_calls.clear()
        native_calls.clear()
        stubs.handler = stub_direct
        cpu.mem_write(0x708000 - 0x100, bytes(0x100))
        original.call(0x482e10, eax=ITEM_ADDR, edx=edx, ebx=ebx, ecx=ecx)
        assert native.vertrix_event_frame_draw_direct(
            c_item, ITEM_SIZE, edx, ebx, ecx, native_direct, None
        ) == 1
        assert orig_calls == native_calls, f"Case {case} direct mismatch:\nOrig: {orig_calls}\nNative: {native_calls}"

        # 2. Test 0x482e80 (blend)
        extra = rng.randrange(0xffffffff)
        orig_calls.clear()
        native_calls.clear()
        stubs.handler = stub_blend
        stubs.arguments[0x47c930] = 5
        cpu.mem_write(0x708000 - 0x100, bytes(0x100))
        original.call(0x482e80, eax=ITEM_ADDR, edx=edx, ebx=ebx, ecx=ecx, args=(extra,))
        assert native.vertrix_event_frame_draw_blend(
            c_item, ITEM_SIZE, edx, ebx, ecx, extra, native_blend, None
        ) == 1
        assert orig_calls == native_calls, f"Case {case} blend mismatch:\nOrig: {orig_calls}\nNative: {native_calls}"

        # 3. Test 0x482f00 (scaled)
        scaled_args = [rng.randrange(0xffffffff) for _ in range(5)]
        orig_calls.clear()
        native_calls.clear()
        stubs.handler = stub_scaled
        stubs.arguments[0x47cb40] = 6
        cpu.mem_write(0x708000 - 0x100, bytes(0x100))
        original.call(0x482f00, eax=ITEM_ADDR, edx=edx, ebx=ebx, ecx=ecx, args=tuple(scaled_args))
        c_args = (U * 5)(*scaled_args)
        assert native.vertrix_event_frame_draw_scaled(
            c_item, ITEM_SIZE, edx, ebx, ecx, c_args, native_scaled, None
        ) == 1
        assert orig_calls == native_calls, f"Case {case} scaled mismatch:\nOrig: {orig_calls}\nNative: {native_calls}"

        verified_cases += 1

    # Short buffer protection check
    short_item = (c.c_uint8 * 0x20)()
    assert native.vertrix_event_frame_draw_direct(
        short_item, 0x20, 0, 0, 0, native_direct, None
    ) == 0
    assert native.vertrix_event_frame_draw_blend(
        short_item, 0x20, 0, 0, 0, 0, native_blend, None
    ) == 0
    assert native.vertrix_event_frame_draw_scaled(
        short_item, 0x20, 0, 0, 0, c_args, native_scaled, None
    ) == 0

    print(f"Verified {verified_cases} cases successfully across 0x482e10, 0x482e80, 0x482f00.")

    out = {
        "routine": "0x482e10, 0x482e80, 0x482f00",
        "cases": verified_cases,
        "complete_original_executions": verified_cases * 3,
        "registers_compared": True,
        "stack_arguments_compared": True,
        "event_buffer_compared": True,
        "short_storage_preserved": True
    }
    Path("docs/event-frame-draw-verification.json").write_text(json.dumps(out, indent=2))


if __name__ == '__main__':
    main()
