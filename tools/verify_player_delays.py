"""Compare original 0x43b5b0/660/680/590 (player delay draws) with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path

from original import Original

U = c.c_uint32
SIZE = 0x1000
#The oracle timing / piece RNG sample buffer lives at 0x804000..0x806002. Test
#objects must stay clear of it; 0x807000 + is safe within the mapped region.
PLAYER = 0x807000
RNG_STATE = 0x598d48
DIFFICULTY = 0x532bbc
KIND = 0x488
LEVEL = 0x17c
FIELDS = (0x458, 0x45c, 0x460)
ROUTINES = (0x43b5b0, 0x43b660, 0x43b680)


class NativeRandom(c.Structure):
    _fields_ = [
        ("samples", c.c_uint16 * 4097),
        ("position", c.c_uint16),
        ("seed", c.c_uint32),
        ("clock", c.c_void_p),
        ("clock_context", c.c_void_p),
    ]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / 'player-delays.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    str(root / 'source/player_slots.c'), str(root / 'source/piece.c'),
                    str(root / 'source/piece_children.c'), str(root / 'source/actor_storage.c'),
                    str(root / 'source/actor_fields.c'), str(root / 'source/timing.c'),
                    str(root / 'source/random.c'), '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    n.vertrix_player_draw_delay_0.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(NativeRandom), U]
    n.vertrix_player_draw_delay_1.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(NativeRandom), U]
    n.vertrix_player_draw_delay_2.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(NativeRandom), U]
    n.vertrix_player_draw_all_delays.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(NativeRandom),
                                                 U]
    n.vertrix_random_seed.argtypes = [c.POINTER(NativeRandom), c.c_uint32]
    natives = (n.vertrix_player_draw_delay_0, n.vertrix_player_draw_delay_1,
               n.vertrix_player_draw_delay_2)
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43b590)
    totals = {}
    seeds = [0, 1, 0x12345678, 0xffffffff, 0xdeadbeef, 0xabcdef01]
    kinds = list(range(19))
    levels = list(range(10))
    difficulties = [0, 1, 2]
#Full structured grid first(3x19x10), then random levels to reach the
#requested per - routine count.
    per_seed = (args.cases + len(seeds) - 1) // len(seeds)
    combos = []
    made = 0
    while len(combos) < per_seed:
        for difficulty in difficulties:
            for kind in kinds:
                if len(combos) >= per_seed:
                    break
                if made < len(difficulties) * len(kinds) * len(levels):
                    level = levels[(made // (len(difficulties) * len(kinds))) % len(levels)]
                else:
                    level = rng.getrandbits(32)
                combos.append((difficulty, kind, level))
                made += 1
            if len(combos) >= per_seed:
                break
    for seed in seeds:
        state = NativeRandom()
        n.vertrix_random_seed(c.byref(state), seed)
        original.timing_seed(seed)
        for combo in combos[:per_seed]:
            difficulty, kind, level = combo
            for index in range(3):
                player = bytearray(SIZE)
                struct.pack_into('<I', player, KIND, kind)
                struct.pack_into('<I', player, LEVEL, level)
                cpu.mem_write(PLAYER, bytes(player))
                cpu.mem_write(DIFFICULTY, struct.pack('<I', difficulty))
                original.call(ROUTINES[index], eax=PLAYER)
                expected = struct.unpack('<I', cpu.mem_read(PLAYER + FIELDS[index], 4))[0]
                expected_pos = struct.unpack('<H', cpu.mem_read(RNG_STATE + 12, 2))[0]
                host = c.create_string_buffer(bytes(player), SIZE)
                assert natives[index](host, SIZE, c.byref(state), difficulty) == 1, combo
                assert struct.unpack('<I', bytes(host[FIELDS[index]:FIELDS[index] + 4]))[0] == \
                    expected, (combo, index)
                assert state.position == expected_pos, (combo, index)
                totals[hex(ROUTINES[index])] = totals.get(hex(ROUTINES[index]), 0) + 1
            player = bytearray(SIZE)
            struct.pack_into('<I', player, KIND, kind)
            struct.pack_into('<I', player, LEVEL, level)
            cpu.mem_write(PLAYER, bytes(player))
            cpu.mem_write(DIFFICULTY, struct.pack('<I', difficulty))
            original.call(0x43b590, eax=PLAYER)
            expected = struct.unpack('<3I', cpu.mem_read(PLAYER + FIELDS[0], 12))
            expected_pos = struct.unpack('<H', cpu.mem_read(RNG_STATE + 12, 2))[0]
            host = c.create_string_buffer(bytes(player), SIZE)
            assert n.vertrix_player_draw_all_delays(host, SIZE, c.byref(state), difficulty) == 1
            assert struct.unpack('<3I', bytes(host[FIELDS[0]:FIELDS[0] + 12])) == expected, combo
            assert state.position == expected_pos, combo
            totals['0x43b590'] = totals.get('0x43b590', 0) + 1
    short = c.create_string_buffer(b'\xaa' * KIND, KIND)
    assert not n.vertrix_player_draw_delay_0(short, KIND, c.byref(state), 0)
    assert not n.vertrix_player_draw_all_delays(short, KIND, c.byref(state), 0)
    assert short.raw == b'\xaa' * KIND
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 43b5b0, 43b660, 43b680 and 43b590 execute in the original '
                       'with seeded RNG; stored delay fields and RNG position compare, plus '
                       'short-storage preservation checks.'}
    (args.build_dir / 'player-delays-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
