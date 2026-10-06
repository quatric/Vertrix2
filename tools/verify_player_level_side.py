"""Compare the complete original level-side handler 0x431400 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, build

U = c.c_uint32
SIZE = 0x1000
CHILD_SIZE = 0x200
ALTER_GLOBAL = 0x532bbc
DELAY_TABLE = 0x4f7d50
FRAME_TABLE = 0x4f7dc8
TABLE_DWORDS = 128
TABLE_WORDS = 256


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'player-level-side',
              ['player_slots.c', 'piece.c', 'piece_children.c', 'actor_storage.c',
               'actor_fields.c', 'object_scalars.c', 'timing.c', 'random.c', 'object_glue.c',
               'call_glue.c', 'table_queries.c', 'engine_helpers.c', 'piece_actor_construct.c',
               'block_factory.c', 'board_cells.c', 'particle_spawn.c', 'actor_chain_visit.c',
               'piece_child_update.c', 'timer.c', 'dword_transition.c', 'frame_resource.c'])
    n.vertrix_player_level_side.argtypes = [Resolve, c.c_void_p, U, c.c_void_p, c.c_size_t, U,
                                            U, c.POINTER(U), c.POINTER(c.c_uint16)]
    n.vertrix_player_level_side.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x431400)
    pool = Pool(cpu, 4, SIZE)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        holder = rng.choice(pool.handles)
        child = rng.choice([h for h in pool.handles if h != holder] + [0])
        if child and rng.random() < 0.5:
            struct.pack_into('<I', pool.buffers[child], 0x168, 0)
            cpu.mem_write(child + 0x168, struct.pack('<I', 0))
        level = rng.randrange(16)
        alter = rng.randrange(10)
        cpu.mem_write(ALTER_GLOBAL, struct.pack('<I', alter))
        delays = bytes(rng.randbytes(TABLE_DWORDS * 4))
        frames = bytes(rng.randbytes(TABLE_WORDS * 2))
        cpu.mem_write(DELAY_TABLE, delays)
        cpu.mem_write(FRAME_TABLE, frames)
        cdelays = (U * TABLE_DWORDS).from_buffer_copy(bytes(cpu.mem_read(DELAY_TABLE,
                                                                         TABLE_DWORDS * 4)))
        cframes = (c.c_uint16 * TABLE_WORDS).from_buffer_copy(bytes(cpu.mem_read(FRAME_TABLE,
                                                                                 TABLE_WORDS * 2)))
        buffer = pool.buffers[holder]
        struct.pack_into('<I', buffer, 0xa60, child)
        cpu.mem_write(holder + 0xa60, struct.pack('<I', child))
        expect = original.call(0x431400, eax=holder, edx=level) & 0xffffffff
        got = n.vertrix_player_level_side(pool.resolve, None, holder, buffer, SIZE, level,
                                          alter, cdelays, cframes)
        assert got == expect, (case, hex(got), hex(expect))
        assert pool.same(), (case, pool.diff())
        totals['0x431400'] = totals.get('0x431400', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete original 0x431400 executions with the delay setter 0x4ac7d0 '
                       'and the counter clearer 0x4ac510 executing for real on both sides; '
                       'the returned handle, the holder bytes and every pool object compare.'}
    (args.build_dir / 'player-level-side-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
