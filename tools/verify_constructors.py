"""Compare original actor constructors with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import build

U = c.c_uint32
SIZE = 0x400
BUFS = (0x807000, 0x807400, 0x807800)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'constructors',
              ['player_piece.c', 'piece_actor_construct.c', 'piece_actor_layout.c',
               'piece_child_update.c', 'actor_storage.c', 'timer.c', 'timing.c',
               'dword_transition.c', 'frame_resource.c', 'piece_actor_update.c',
               'block_factory.c', 'actor_fields.c', 'board_cells.c', 'piece_children.c'])
    n.vertrix_piece_actor_construct_empty.argtypes = [c.c_void_p, c.c_size_t]
    n.vertrix_block_construct_kind_one.argtypes = [c.c_void_p, c.c_size_t]
    n.vertrix_player_piece_initialize.argtypes = [c.c_void_p, c.c_size_t]
    n.vertrix_piece_actor_construct_slots.argtypes = [c.c_void_p, c.c_size_t]
    n.vertrix_piece_child_slots_init.argtypes = [c.c_void_p, c.c_size_t]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x42b5c0)
    totals = {}
    members = ((0x42b5c0, n.vertrix_piece_actor_construct_empty, '0x42b5c0'),
               (0x43a080, n.vertrix_block_construct_kind_one, '0x43a080'),
               (0x425e20, n.vertrix_player_piece_initialize, '0x425e20'),
               (0x429880, n.vertrix_piece_actor_construct_slots, '0x429880'),
               (0x43a160, n.vertrix_piece_child_slots_init, '0x43a160'))
    for index, (address, native, name) in enumerate(members):
        for _ in range(args.cases):
            buf = BUFS[index % len(BUFS)]
            data = bytes(rng.getrandbits(8) for _ in range(SIZE))
            cpu.mem_write(buf, data)
            original.call(address, eax=buf)
            expected = bytes(cpu.mem_read(buf, SIZE))
            host = c.create_string_buffer(data, SIZE)
            assert native(host, SIZE) == 1, name
            assert host.raw == expected, name
            totals[name] = totals.get(name, 0) + 1
    tiny = c.create_string_buffer(b'\xaa' * 8, 8)
    for _, native, name in members:
        assert not native(tiny, 8), name
    assert tiny.raw == b'\xaa' * 8
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 42b5c0, 43a080, 425e20, 429880 and 43a160 execute in the original '
                       'over random storage; whole objects compare, plus short-storage '
                       'preservation checks.'}
    (args.build_dir / 'constructors-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
