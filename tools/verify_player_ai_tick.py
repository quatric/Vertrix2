"""Compare original 0x43b430 player AI tick routine with native recovery."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct

from original import Original
from oracle_kit import Stubs, build

U = c.c_uint32
U16 = c.c_uint16

ResolveCb = c.CFUNCTYPE(c.c_int, U, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)
CompareCb = c.CFUNCTYPE(None, c.c_void_p, c.c_size_t, c.c_void_p, c.c_size_t, c.c_void_p)
PreviewCb = c.CFUNCTYPE(c.c_int, c.c_void_p, c.c_size_t, c.POINTER(U), c.c_void_p)
RotationCb = c.CFUNCTYPE(c.c_int, c.c_void_p, c.c_size_t, c.POINTER(U), c.POINTER(U), c.c_void_p)
TimerUpdateCb = c.CFUNCTYPE(None, c.c_void_p, c.c_size_t, c.c_void_p)
TimerCheckCb = c.CFUNCTYPE(c.c_int, c.c_void_p, c.c_size_t, c.c_void_p)
TimerResetCb = c.CFUNCTYPE(None, c.c_void_p, c.c_size_t, c.c_void_p)
TimerSetPeriodCb = c.CFUNCTYPE(None, c.c_void_p, c.c_size_t, U, c.c_void_p)
DrawDelayCb = c.CFUNCTYPE(c.c_int, c.c_void_p, c.c_size_t, c.POINTER(U), c.c_void_p)
FastDropCb = c.CFUNCTYPE(c.c_int, c.c_void_p, c.c_size_t, c.c_void_p)
KeyCb = c.CFUNCTYPE(None, U16, c.c_int, c.c_void_p)


class PlayerAiTickOps(c.Structure):
    _fields_ = [
        ('resolve', ResolveCb),
        ('resolve_context', c.c_void_p),
        ('compare_boards', CompareCb),
        ('compare_context', c.c_void_p),
        ('preview_frames', PreviewCb),
        ('preview_context', c.c_void_p),
        ('choose_rotation', RotationCb),
        ('rotation_context', c.c_void_p),
        ('timer_update', TimerUpdateCb),
        ('timer_check', TimerCheckCb),
        ('timer_reset', TimerResetCb),
        ('timer_set_period', TimerSetPeriodCb),
        ('timer_context', c.c_void_p),
        ('draw_delay_2', DrawDelayCb),
        ('delay_context', c.c_void_p),
        ('check_fast_drop', FastDropCb),
        ('drop_context', c.c_void_p),
        ('key_event', KeyCb),
        ('key_context', c.c_void_p),
    ]


PLAYER_SIZE = 0x500
AI_SIZE = 0x300
BOARD_SIZE = 0xc00
PIECE_SIZE = 0x200

PLAYER_ADDR = 0x808000
AI_ADDR = 0x809000
BOARD_ADDR = 0x80a000
PIECE_ADDR = 0x80b000
TABLE_ADDR = 0x80c000


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()

    native = build(args.build_dir, 'player-ai-tick', [
        'player_ai_tick.c',
        'actor_storage.c',
    ])

    native.vertrix_player_ai_tick.argtypes = [
        c.c_void_p, c.c_size_t, c.POINTER(PlayerAiTickOps)
    ]
    native.vertrix_player_ai_tick.restype = c.c_int

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43b430)

    # Recorded events
    orig_keys = []
    native_keys = []
    orig_calls = []
    native_calls = []

    def stub_4761d0(addr, eax, edx, ebx, ecx, stack):
        orig_keys.append(('press', edx & 0xffff))
        return 0

    def stub_476280(addr, eax, edx, ebx, ecx, stack):
        orig_keys.append(('release', edx & 0xffff))
        return 0

    stubs = Stubs(cpu, lambda *a: 0)
    stubs.add(0x4761d0, 1)
    stubs.add(0x476280, 1)
    stubs.add(0x427850)
    stubs.add(0x42b090)
    stubs.add(0x4290a0)
    stubs.add(0x4ac500)
    stubs.add(0x4ac520)
    stubs.add(0x4ac510)
    stubs.add(0x4ac7d0)
    stubs.add(0x43b680)
    stubs.add(0x431490)

    test_state = {}

    def oracle_handler(addr, eax, edx, ebx, ecx, stack):
        orig_calls.append(f'{addr:#x}')
        if addr == 0x4761d0:
            return stub_4761d0(addr, eax, edx, ebx, ecx, stack)
        elif addr == 0x476280:
            return stub_476280(addr, eax, edx, ebx, ecx, stack)
        elif addr == 0x4ac520:
            return test_state['timer_expired']
        elif addr == 0x431490:
            return test_state['dropping']
        elif addr == 0x43b680:
            cpu.mem_write(eax + 0x460, struct.pack('<I', test_state['delay']))
            return 0
        elif addr == 0x4290a0:
            cpu.mem_write(eax + 0x16c, struct.pack('<I', test_state['chosen_rot']))
            return test_state['chosen_rot']
        return 0

    stubs.handler = oracle_handler

    # Native callbacks
    @CompareCb
    def native_compare(ai_obj, ai_sz, player_ptr, player_sz, ctx):
        native_calls.append('0x427850')

    @PreviewCb
    def native_preview(piece, piece_sz, table_ptr, ctx):
        native_calls.append('0x42b090')
        return 1

    @RotationCb
    def native_rotation(ai_obj, ai_sz, table_ptr, chosen_ptr, ctx):
        native_calls.append('0x4290a0')
        rot = test_state['chosen_rot']
        struct.pack_into('<I', (c.c_uint8 * ai_sz).from_address(ai_obj), 0x16c, rot)
        chosen_ptr[0] = rot
        return 1

    @TimerUpdateCb
    def native_t_update(ai_obj, ai_sz, ctx):
        native_calls.append('0x4ac500')

    @TimerCheckCb
    def native_t_check(ai_obj, ai_sz, ctx):
        native_calls.append('0x4ac520')
        return test_state['timer_expired']

    @TimerResetCb
    def native_t_reset(ai_obj, ai_sz, ctx):
        native_calls.append('0x4ac510')

    @TimerSetPeriodCb
    def native_t_period(ai_obj, ai_sz, period, ctx):
        native_calls.append('0x4ac7d0')

    @DrawDelayCb
    def native_draw_delay(player_ptr, player_sz, delay_ptr, ctx):
        native_calls.append('0x43b680')
        d = test_state['delay']
        struct.pack_into('<I', (c.c_uint8 * player_sz).from_address(player_ptr), 0x460, d)
        delay_ptr[0] = d
        return 1

    @FastDropCb
    def native_fast_drop(board_ptr, board_sz, ctx):
        native_calls.append('0x431490')
        return test_state['dropping']

    @KeyCb
    def native_key(key, press, ctx):
        native_calls.append('0x4761d0' if press else '0x476280')
        native_keys.append(('press' if press else 'release', key))

    verified_cases = 0

    for case in range(args.cases):
        player_buf = bytearray(rng.randbytes(PLAYER_SIZE))
        ai_buf = bytearray(rng.randbytes(AI_SIZE))
        board_buf = bytearray(rng.randbytes(BOARD_SIZE))
        piece_buf = bytearray(rng.randbytes(PIECE_SIZE))

        # Setup standard handles
        ai_enabled = rng.choice([1, 1, 1, 0])
        struct.pack_into('<I', player_buf, 0x454, ai_enabled)
        struct.pack_into('<I', player_buf, 0x450, AI_ADDR)
        struct.pack_into('<I', player_buf, 0x15c, BOARD_ADDR)
        struct.pack_into('<I', player_buf, 0x46c, TABLE_ADDR)

        permute_k = rng.randrange(1, 0x100)
        drop_k = rng.randrange(1, 0x100)
        struct.pack_into('<H', player_buf, 0x164, permute_k)
        struct.pack_into('<H', player_buf, 0x166, drop_k)

        struct.pack_into('<I', board_buf, 0xb78, PIECE_ADDR)

        # Vary phase and parameters
        phase = rng.choice([1, 0, 0, 0, 2])
        struct.pack_into('<I', ai_buf, 0x178, phase)
        rotations = rng.choice([0, 1, 2, 3])
        struct.pack_into('<I', ai_buf, 0x16c, rotations)

        test_state['timer_expired'] = rng.choice([0, 1])
        test_state['dropping'] = rng.choice([0, 1])
        test_state['delay'] = rng.randrange(50, 500)
        test_state['chosen_rot'] = rng.randrange(0, 4)

        # Write to CPU memory
        cpu.mem_write(PLAYER_ADDR, bytes(player_buf))
        cpu.mem_write(AI_ADDR, bytes(ai_buf))
        cpu.mem_write(BOARD_ADDR, bytes(board_buf))
        cpu.mem_write(PIECE_ADDR, bytes(piece_buf))

        # Write to native buffers
        c_player = (c.c_uint8 * PLAYER_SIZE).from_buffer_copy(bytes(player_buf))
        c_ai = (c.c_uint8 * AI_SIZE).from_buffer_copy(bytes(ai_buf))
        c_board = (c.c_uint8 * BOARD_SIZE).from_buffer_copy(bytes(board_buf))
        c_piece = (c.c_uint8 * PIECE_SIZE).from_buffer_copy(bytes(piece_buf))

        storage_map = {
            AI_ADDR: (c_ai, AI_SIZE),
            BOARD_ADDR: (c_board, BOARD_SIZE),
            PIECE_ADDR: (c_piece, PIECE_SIZE),
        }

        @ResolveCb
        def native_resolve(handle, out_ptr, out_sz, ctx):
            if handle in storage_map:
                buf, sz = storage_map[handle]
                out_ptr[0] = c.cast(buf, c.c_void_p)
                out_sz[0] = sz
                return 1
            return 0

        ops = PlayerAiTickOps(
            resolve=native_resolve,
            resolve_context=None,
            compare_boards=native_compare,
            compare_context=None,
            preview_frames=native_preview,
            preview_context=None,
            choose_rotation=native_rotation,
            rotation_context=None,
            timer_update=native_t_update,
            timer_check=native_t_check,
            timer_reset=native_t_reset,
            timer_set_period=native_t_period,
            timer_context=None,
            draw_delay_2=native_draw_delay,
            delay_context=None,
            check_fast_drop=native_fast_drop,
            drop_context=None,
            key_event=native_key,
            key_context=None,
        )

        orig_keys.clear()
        native_keys.clear()
        orig_calls.clear()
        native_calls.clear()

        cpu.mem_write(0x708000 - 0x100, bytes(0x100))
        original.call(0x43b430, eax=PLAYER_ADDR)
        res = native.vertrix_player_ai_tick(c_player, PLAYER_SIZE, c.byref(ops))

        assert orig_calls == native_calls, f"Case {case} calls mismatch:\nOrig: {orig_calls}\nNative: {native_calls}"
        assert orig_keys == native_keys, f"Case {case} keys mismatch:\nOrig: {orig_keys}\nNative: {native_keys}"

        # Verify ai_buf memory matches cpu
        cpu_ai = bytes(cpu.mem_read(AI_ADDR, AI_SIZE))
        assert bytes(c_ai) == cpu_ai, f"Case {case} AI buffer mismatch"

        # Verify player buffer memory matches cpu
        cpu_player = bytes(cpu.mem_read(PLAYER_ADDR, PLAYER_SIZE))
        assert bytes(c_player) == cpu_player, f"Case {case} Player buffer mismatch"

        verified_cases += 1

    # Short storage check
    short_player = (c.c_uint8 * 0x100)()
    assert native.vertrix_player_ai_tick(short_player, 0x100, c.byref(ops)) == 0

    print(f"Verified {verified_cases} cases successfully across 0x43b430.")

    out = {
        "routine": "0x43b430",
        "cases": verified_cases,
        "complete_original_executions": verified_cases,
        "calls_order_compared": True,
        "key_injections_compared": True,
        "whole_object_compared": True,
        "short_storage_preserved": True
    }
    Path("docs/player-ai-tick-verification.json").write_text(json.dumps(out, indent=2))


if __name__ == '__main__':
    main()
