"""Compare original 0x43ba80/bad0/bae0 (player field stores) with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import build

U = c.c_uint32
SIZE = 0x1000
PLAYER = 0x807000


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'player-stores',
              ['player_slots.c', 'piece.c', 'piece_children.c', 'actor_storage.c', 'actor_fields.c',
               'object_scalars.c', 'timing.c', 'random.c', 'piece_actor_construct.c', 'piece_child_update.c', 'dword_transition.c', 'frame_resource.c', 'timer.c'])
    n.vertrix_player_clear_field_18c.argtypes = [c.c_void_p, c.c_size_t]
    n.vertrix_player_set_b08.argtypes = [c.c_void_p, c.c_size_t, c.c_uint8]
    n.vertrix_player_set_b14.argtypes = [c.c_void_p, c.c_size_t, c.c_uint8]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43bad0)
    totals = {}
    for _ in range(args.cases):
        player = bytearray(rng.getrandbits(8) for _ in range(SIZE))
        cpu.mem_write(PLAYER, bytes(player))
        original.call(0x43ba80, eax=PLAYER)
        host = c.create_string_buffer(bytes(player), SIZE)
        assert n.vertrix_player_clear_field_18c(host, SIZE) == 1
        assert bytes(cpu.mem_read(PLAYER, SIZE)) == host.raw, 'clear'
        totals['0x43ba80'] = totals.get('0x43ba80', 0) + 1
    for address, native, name in ((0x43bad0, n.vertrix_player_set_b14, '0x43bad0'),
                                  (0x43bae0, n.vertrix_player_set_b08, '0x43bae0')):
        for _ in range(args.cases):
            value = rng.getrandbits(8)
            player = bytearray(rng.getrandbits(8) for _ in range(SIZE))
            cpu.mem_write(PLAYER, bytes(player))
            original.call(address, eax=PLAYER, edx=value)
            host = c.create_string_buffer(bytes(player), SIZE)
            assert native(host, SIZE, value) == 1, name
            assert bytes(cpu.mem_read(PLAYER, SIZE)) == host.raw, name
            totals[name] = totals.get(name, 0) + 1
    tiny = c.create_string_buffer(b'\xaa' * 0x18c, 0x18c)
    assert not n.vertrix_player_clear_field_18c(tiny, 0x18c)
    assert tiny.raw == b'\xaa' * 0x18c
    assert not n.vertrix_player_set_b08(tiny, 0x18c, 1)
    assert not n.vertrix_player_set_b14(tiny, 0x18c, 1)
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 43ba80, 43bad0 and 43bae0 execute in the original over random '
                       'player storage; whole objects compare, plus short-storage preservation '
                       'checks.'}
    (args.build_dir / 'player-stores-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
