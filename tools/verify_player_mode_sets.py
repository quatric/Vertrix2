"""Compare original 0x43bb40/0x43baf0 (player mode setters) with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path
from original import Original
from oracle_kit import Pool, Stubs, build
U = c.c_uint32
SIZE = 0x1000
Refresh = c.CFUNCTYPE(None, U, c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'player-mode-sets', ['player_slots.c', 'actor_storage.c', 'actor_fields.c', 'timing.c', 'piece.c', 'piece_actor_construct.c', 'piece_children.c', 'object_scalars.c', 'random.c', 'piece_child_update.c', 'dword_transition.c', 'frame_resource.c', 'timer.c'])
    n.vertrix_player_set_mode_and_refresh.argtypes = [c.c_void_p, c.c_size_t, U, U, Refresh, c.c_void_p]
    n.vertrix_player_set_b00_and_refresh.argtypes = [c.c_void_p, c.c_size_t, U, c.c_uint8, Refresh, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43bb40)
    pool = Pool(cpu, 4, SIZE)
    stubs = Stubs(cpu, lambda address, eax, edx, ebx, ecx, stack: None)
    stubs.add(0x4726d0)
    native_log = []
    @ Refresh
    def refresh(handle, context):
        native_log.append(handle)
    totals = {}
    player = pool.handles[0]
    for case in range(args.cases):
        pool.fill(rng)
        stubs.log.clear()
        native_log.clear()
        mode = rng.choice([0x22, 0x28, 0x29, 0x2a, 0x2d, 0x2e, 0, 1, rng.getrandbits(32)])
        original.call(0x43bb40, eax=player, edx=mode)
        assert n.vertrix_player_set_mode_and_refresh(pool.buffers[player], SIZE, player, mode, refresh, None) == 1, case
        assert pool.same(), (case, '43bb40', pool.diff())
        assert [e[1] for e in stubs.log] == native_log, (case, '43bb40-refresh')
        totals['0x43bb40'] = totals.get('0x43bb40', 0) + 1
        pool.fill(rng)
        stubs.log.clear()
        native_log.clear()
        value = rng.getrandbits(8)
        original.call(0x43baf0, eax=player, edx=value)
        assert n.vertrix_player_set_b00_and_refresh(pool.buffers[player], SIZE, player, value, refresh, None) == 1, case
        assert pool.same(), (case, '43baf0', pool.diff())
        assert [e[1] for e in stubs.log] == native_log, (case, '43baf0-refresh')
        totals['0x43baf0'] = totals.get('0x43baf0', 0) + 1
    short = c.create_string_buffer(b'\xaa' * 0x4c4, 0x4c4)
    assert not n.vertrix_player_set_mode_and_refresh(short, 0x4c4, 0, 0, refresh, None)
    assert not n.vertrix_player_set_b00_and_refresh(short, 0x4c4, 0, 0, refresh, None)
    assert short.raw == b'\xaa' * 0x4c4
    report = {'status': 'passed', 'complete_original_executions': totals, 'scope': 'Complete 43bb40 and 43baf0 execute in the original (refresh 4726d0 ' 'stubbed and logged); whole objects and refresh events compare, plus ' 'short-storage preservation checks.'}
    (args.build_dir / 'player-mode-sets-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
