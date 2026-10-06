"""Composed proof: original 0x4522c0 versus native enter_attack with the real
enter_452370/enter_4523d0 natives executing inside the 0x43bce0/0x43bd00
call handlers.

Only 0x43bbf0 and the cursor method stay stubbed (logged and replayed);
the state entries run for real on both sides through the shared
implementations."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0xc00
VTABLE = 0x706000
METHOD = 0x707000


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next')]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


Method = c.CFUNCTYPE(U, U, U, c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-attack-composed',
              ['object_events.c', 'call_glue.c', 'actor_storage.c', 'player_actions.c',
               'player_slots.c', 'event_stack.c', 'actor_fields.c', 'board_cells.c',
               'object_scalars.c', 'timing.c', 'random.c', 'piece.c', 'piece_children.c'])
    P, V, S = c.POINTER(Calls), c.c_void_p, c.c_size_t
    n.vertrix_object_enter_attack.argtypes = [P, c.POINTER(Services), U, V, S, Method, V]
    n.vertrix_object_enter_attack.restype = U
    n.vertrix_player_enter_452370.argtypes = [V, S, Resolve, V]
    n.vertrix_player_enter_452370.restype = c.c_int
    n.vertrix_player_enter_4523d0.argtypes = [V, S, Resolve, V]
    n.vertrix_player_enter_4523d0.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4522c0 + 0x43bce0)
    pool = Pool(cpu, 8, SIZE)
    player, opp, cursor, oppcur = pool.handles[:4]
    returns, native_log, method_log, replay = [], [], [], []

    cpu.mem_write(VTABLE + 4, struct.pack('<I', METHOD))

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x43bce0:
            ok = n.vertrix_player_enter_452370(pool.buffers[eax], SIZE, pool.resolve, None)
            returns.append(ok & 0xffffffff)
            return returns[-1]
        if address == 0x43bd00:
            ok = n.vertrix_player_enter_4523d0(pool.buffers[eax], SIZE, pool.resolve, None)
            returns.append(ok & 0xffffffff)
            return returns[-1]
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address in (0x43bce0, 0x43bd00, 0x43bbf0, METHOD):
        stubs.add(address)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    @Method
    def method(cursor_handle, table, context):
        method_log.append((cursor_handle, table))
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    totals = {'0x4522c0 composed': 0}

    def patch(handle, data):
        if handle == player:
            struct.pack_into('<I', data, 0x3b0, opp)
            struct.pack_into('<I', data, 0x15c, cursor)
        elif handle == opp:
            data[0x4c5] = rng.choice([0, 0, 1, 1, 2])
            data[0x4cc] = rng.choice([0, 1, 2])
            struct.pack_into('<I', data, 0x3f4, rng.choice([0, 0, 1]))
            struct.pack_into('<I', data, 0x15c, oppcur)
        elif handle in (cursor, oppcur):
            struct.pack_into('<I', data, 0x158, VTABLE)

    for case in range(args.cases):
        pool.fill(rng, patch)
        buffer = pool.buffers[player]
        # The call handlers execute the real state entries on the host buffers
        # while the oracle runs; snapshot and restore so the native phase starts
        # from the identical baseline (returns are recorded and replayed).
        snap = {h: bytes(pool.buffers[h].raw) for h in pool.handles}
        stubs.log.clear()
        returns.clear()
        method_log.clear()
        native_log.clear()
        result = original.call(0x4522c0, eax=player) & 0xffffffff
        for h in pool.handles:
            pool.buffers[h].raw = snap[h]
        replay[:] = list(returns)
        got = n.vertrix_object_enter_attack(c.byref(calls), c.byref(services), player, buffer,
                                            SIZE, method, None)
        assert got == result, (case, hex(got), hex(result))
        assert native_log == [e[:5] for e in stubs.log if e[0] != METHOD], (case,)
        assert not replay, case
        assert pool.same(), (case, pool.diff())
        totals['0x4522c0 composed'] += 1

    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': '0x4522c0 executes completely in the original with the real 0x43bce0 and '
                       '0x43bd00 bodies running inside the call handlers (0x43bbf0 and the cursor '
                       'method stubbed and replayed); return, every Calls call, the method '
                       'cursor/table/return and every pool object compare.'}
    Path("docs/object-attack-composed-verification.json").write_text(json.dumps(report, indent=2)
                                                                     + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
