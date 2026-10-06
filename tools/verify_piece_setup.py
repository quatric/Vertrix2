"""Compare original 0x43ab30 (piece init + delay draws) with the native recovery."""
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
#Keep clear of the oracle RNG sample buffer at 0x804000..0x806002.
PLAYER = 0x807000
PIECE = 0x808000
RNG_STATE = 0x598d48
DIFFICULTY = 0x532bbc
KIND = 0x488
LEVEL = 0x17c
TARGET = 0x450
PIECE_FIELDS = (0x15c, 0x160, 0x164, 0x180)
DELAY_FIELDS = (0x458, 0x45c, 0x460)


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
    library = args.build_dir.resolve() / 'piece-setup.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    str(root / 'source/player_slots.c'), str(root / 'source/piece.c'),
                    str(root / 'source/piece_children.c'), str(root / 'source/actor_storage.c'),
                    str(root / 'source/actor_fields.c'), str(root / 'source/timing.c'),
                    str(root / 'source/random.c'), '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    Resolve = c.CFUNCTYPE(c.c_int, U, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)
    n.vertrix_player_init_piece_and_delays.argtypes = [c.c_void_p, c.c_size_t,
                                                       c.POINTER(NativeRandom), U, Resolve,
                                                       c.c_void_p]
    n.vertrix_random_seed.argtypes = [c.POINTER(NativeRandom), c.c_uint32]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43ab30)
    totals = {'0x43ab30': 0}
    seeds = [0, 1, 0x12345678, 0xffffffff]
    kinds = list(range(19))
    levels = list(range(10))
    difficulties = [0, 1, 2]
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
    host_piece = c.create_string_buffer(SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle != PIECE:
            return 0
        storage[0] = c.cast(host_piece, c.c_void_p)
        size[0] = SIZE
        return 1

    for seed in seeds:
        state = NativeRandom()
        n.vertrix_random_seed(c.byref(state), seed)
        original.timing_seed(seed)
        for difficulty, kind, level in combos:
            player = bytearray(SIZE)
            piece = bytearray(rng.getrandbits(8) for _ in range(SIZE))
            struct.pack_into('<I', player, KIND, kind)
            struct.pack_into('<I', player, LEVEL, level)
            struct.pack_into('<I', player, TARGET, PIECE)
            cpu.mem_write(PLAYER, bytes(player))
            cpu.mem_write(PIECE, bytes(piece))
            cpu.mem_write(DIFFICULTY, struct.pack('<I', difficulty))
            original.call(0x43ab30, eax=PLAYER)
            expected_piece = bytes(cpu.mem_read(PIECE, SIZE))
            expected_delays = struct.unpack('<3I', cpu.mem_read(PLAYER + DELAY_FIELDS[0], 12))
            expected_pos = struct.unpack('<H', cpu.mem_read(RNG_STATE + 12, 2))[0]
            host_player = c.create_string_buffer(bytes(player), SIZE)
            host_piece.raw = bytes(piece)
            assert n.vertrix_player_init_piece_and_delays(host_player, SIZE, c.byref(state),
                                                          difficulty, resolve, None) == 1
            assert bytes(host_piece.raw) == expected_piece, (seed, difficulty, kind, level)
            assert struct.unpack('<3I', bytes(host_player[DELAY_FIELDS[0]:DELAY_FIELDS[0] + 12])) \
                == expected_delays, (seed, difficulty, kind, level)
            assert state.position == expected_pos, (seed, difficulty, kind, level)
            totals['0x43ab30'] += 1
#Invalid kind(>= 19) preserves everything natively; the original would
#read beyond its tables there, so it is never executed for such inputs.
    before_pos = state.position
    host_player = c.create_string_buffer(SIZE)
    struct.pack_into('<I', host_player, KIND, 19)
    struct.pack_into('<I', host_player, TARGET, PIECE)
    host_piece.raw = bytes(piece)
    assert not n.vertrix_player_init_piece_and_delays(host_player, SIZE, c.byref(state), 0,
                                                      resolve, None)
    assert struct.unpack('<I', bytes(host_player[KIND:KIND + 4]))[0] == 19
    assert state.position == before_pos
    tiny = c.create_string_buffer(b'\xaa' * KIND, KIND)
    assert not n.vertrix_player_init_piece_and_delays(tiny, KIND, c.byref(state), 0, resolve,
                                                      None)
    assert tiny.raw == b'\xaa' * KIND
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 43ab30 executes in the original with seeded RNG; initialized '
                       'piece bytes, delay fields and RNG position compare.'}
    (args.build_dir / 'piece-setup-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
