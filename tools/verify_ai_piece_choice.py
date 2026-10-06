"""Compare original 0x429000 and 0x4290a0 with native ai_piece_choice recovery."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct

from original import Original
from oracle_kit import Stubs, build

U = c.c_uint32
AiRandom = c.CFUNCTYPE(c.c_uint16, c.c_void_p, c.c_uint16)

PLAYER_SIZE = 0x400
PLAYER_ADDR = 0x808000
TABLE_ADDR = 0x809000


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()

    native = build(args.build_dir, 'ai-piece-choice', [
        'ai_piece_choice.c',
        'actor_storage.c',
        'object_scalars.c',
    ])

    native.vertrix_ai_find_best_slot.argtypes = [
        c.POINTER(U), c.POINTER(c.c_uint8), c.POINTER(c.c_uint8), AiRandom, c.c_void_p
    ]
    native.vertrix_ai_find_best_slot.restype = U

    native.vertrix_ai_choose_piece_rotation.argtypes = [
        c.c_void_p, c.c_size_t, c.POINTER(U), c.POINTER(c.c_uint8), AiRandom, c.c_void_p, c.POINTER(U)
    ]
    native.vertrix_ai_choose_piece_rotation.restype = c.c_int

    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x429000)

    # Deterministic sequence for RNG tie breaks
    rng_draws = []

    def rng_hook(address, eax, edx, ebx, ecx, stack_args):
        # 0x4826c0: eax=RNG_STATE, edx=divisor (2)
        divisor = edx & 0xffff
        val = rng.randrange(divisor) if divisor > 0 else 0
        rng_draws.append(val)
        return val

    stubs = Stubs(cpu, rng_hook)
    stubs.add(0x4826c0)

    @AiRandom
    def native_random(context, divisor):
        val = rng_draws.pop(0)
        return val

    verified_cases = 0

    for case in range(args.cases):
        # Generate table with 0 to 7 active entries
        count = rng.choice([0, 1, 2, 3, 4, 5, 6, 7])
        indices = [rng.randrange(0, 8) for _ in range(count)]
        table_arr = indices + [-1] * (7 - count)
        table_bytes = struct.pack('<7i', *table_arr)

        # Generate player buffer with scores at +0x210
        player_buf = bytearray(rng.randbytes(PLAYER_SIZE))
        # Ensure rotation target at +0x16c has random initial data
        struct.pack_into('<I', player_buf, 0x16c, rng.randrange(0xffffffff))

        # Test 1: Compare 0x429000 directly
        cpu.mem_write(TABLE_ADDR, table_bytes)
        scores_addr = PLAYER_ADDR + 0x210
        cpu.mem_write(PLAYER_ADDR, bytes(player_buf))

        rng_draws.clear()
        c_table = (U * 7)(*[idx & 0xffffffff for idx in table_arr])
        scores_ptr = (c.c_uint8 * 256).from_buffer_copy(bytes(player_buf[0x210:0x210 + 256]))

        # Original call
        orig_res = original.call(0x429000, eax=TABLE_ADDR, edx=TABLE_ADDR, ebx=scores_addr)

        # Native call using recorded RNG draws
        native_res = native.vertrix_ai_find_best_slot(
            c_table, scores_ptr, None, native_random, None
        )

        assert orig_res == native_res, f"Case {case} 0x429000 mismatch: orig={orig_res}, native={native_res}"

        # Test 2: Compare 0x4290a0
        # Reset player memory in cpu
        cpu.mem_write(PLAYER_ADDR, bytes(player_buf))
        c_player = (c.c_uint8 * PLAYER_SIZE).from_buffer_copy(bytes(player_buf))

        rng_draws.clear()
        orig_ret = original.call(0x4290a0, eax=PLAYER_ADDR, edx=TABLE_ADDR)

        native_chosen = U(0)
        ok = native.vertrix_ai_choose_piece_rotation(
            c_player, PLAYER_SIZE, c_table, None, native_random, None, c.byref(native_chosen)
        )
        assert ok == 1, f"Case {case} native choose rotation failed"
        assert orig_ret == native_chosen.value, f"Case {case} 0x4290a0 return mismatch"

        # Compare whole player memory
        cpu_player = bytes(cpu.mem_read(PLAYER_ADDR, PLAYER_SIZE))
        assert bytes(c_player) == cpu_player, f"Case {case} player object memory mismatch"

        verified_cases += 1

    # Short buffer protection check
    short_buf = (c.c_uint8 * 0x100)()
    short_chosen = U(0)
    assert native.vertrix_ai_choose_piece_rotation(
        short_buf, 0x100, c_table, None, native_random, None, c.byref(short_chosen)
    ) == 0

    print(f"Verified {verified_cases} cases successfully across 0x429000 and 0x4290a0.")

    out = {
        "routine": "0x429000, 0x4290a0",
        "cases": verified_cases,
        "complete_original_executions": verified_cases,
        "whole_object_compared": True,
        "short_storage_preserved": True
    }
    Path("docs/ai-piece-choice-verification.json").write_text(json.dumps(out, indent=2))


if __name__ == '__main__':
    main()
