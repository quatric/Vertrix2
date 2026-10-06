"""Compare original 0x43d260 (preview generation) with the native recovery."""
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
#NOTE : the oracle's RNG sample buffer lives at 0x804000..0x806002. Test objects
#must stay clear of it(and of BOARD / MASK / COUNTER / BLOCKS); 0x807000 + is safe
#within the mapped 0x800000 region.
PLAYER = 0x807000
PREVIEW_OBJ = 0x808000
PREVIEW = 0x3b4
MODE = 0x4c8
KINDS = 0x168
RNG_STATE = 0x598d30


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
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = args.build_dir.resolve() / 'preview-generate.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    str(root / 'source/player_slots.c'), str(root / 'source/piece.c'),
                    str(root / 'source/piece_children.c'), str(root / 'source/actor_storage.c'),
                    str(root / 'source/actor_fields.c'), str(root / 'source/random.c'), str(root / 'source/timing.c'), str(root / 'source/piece_actor_construct.c'), str(root / 'source/object_scalars.c'), str(root / 'source/piece_child_update.c'), str(root / 'source/dword_transition.c'), str(root / 'source/frame_resource.c'), str(root / 'source/timer.c'), '-o',
                    str(library)], check=True)
    n = c.CDLL(str(library))
    Resolve = c.CFUNCTYPE(c.c_int, U, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)
    n.vertrix_player_generate_preview.argtypes = [c.c_void_p, c.c_size_t,
                                                  c.POINTER(NativeRandom), Resolve, c.c_void_p]
    n.vertrix_random_seed.argtypes = [c.POINTER(NativeRandom), c.c_uint32]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43d260)
    totals = {'0x43d260': 0}
    seeds = [0, 1, 0x12345678, 0xffffffff]
    modes = [0x22, 0x28, 0x29, 0x2a, 0x2d, 0x2e, 0, 1, 5]
    per = max(1, args.cases // (len(seeds) * len(modes)))
    host_preview = c.create_string_buffer(SIZE)
    host_player = c.create_string_buffer(SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle != PREVIEW_OBJ:
            return 0
        storage[0] = c.cast(host_preview, c.c_void_p)
        size[0] = SIZE
        return 1

    for seed in seeds:
        state = NativeRandom()
        n.vertrix_random_seed(c.byref(state), seed)
        original.piece_seed(seed)
        for mode in modes:
            for _ in range(per):
                player = bytearray(SIZE)
                preview = bytearray(rng.getrandbits(8) for _ in range(SIZE))
                struct.pack_into('<I', player, MODE, mode)
                struct.pack_into('<I', player, PREVIEW, PREVIEW_OBJ)
                cpu.mem_write(PLAYER, bytes(player))
                cpu.mem_write(PREVIEW_OBJ, bytes(preview))
                original.call(0x43d260, eax=PLAYER)
                expected_kinds = bytes(cpu.mem_read(PREVIEW_OBJ + KINDS, 3))
                expected_pos = struct.unpack('<H', cpu.mem_read(RNG_STATE + 12, 2))[0]
                host_player.raw = bytes(player)
                host_preview.raw = bytes(preview)
                assert n.vertrix_player_generate_preview(host_player, SIZE, c.byref(state),
                                                         resolve, None) == 1, (seed, mode)
                assert bytes(host_preview[KINDS:KINDS + 3]) == expected_kinds, (seed, mode)
                assert state.position == expected_pos, (seed, mode)
                totals['0x43d260'] += 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 43d260 executes in the original with seeded RNG; preview kind '
                       'bytes and RNG position compare across modes and buffer wrap.'}
    (args.build_dir / 'preview-generate-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
