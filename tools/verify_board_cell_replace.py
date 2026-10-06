"""Compare the original board cell replacement 0x4365c0 and 0x436440 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0xd00
FRAME = STACK - 4


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


CALLEES = (0x436030, 0x4826c0, 0x435fe0, 0x4360b0, 0x4ac8f0, 0x4ac7b0, 0x430800, 0x4ac490,
           0x4ac710, 0x4ac510, 0x4ac380, 0x430440, 0x430660, 0x4726d0, 0x43ad50)
OUTPUTS = (0x435fe0, 0x4360b0)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'board-cell-replace',
              ['board_cell_replace.c', 'call_glue.c', 'actor_storage.c'])
    P, V, S = c.POINTER(Calls), c.c_void_p, c.c_size_t
    for name in ('vertrix_board_replace_cell', 'vertrix_board_replace_random_cell'):
        function = getattr(n, name)
        function.argtypes = [P, c.POINTER(Services), U, V, S, U, U, U, U]
        function.restype = U
    n.vertrix_board_view_setup.argtypes = [P, c.POINTER(Services), U, V, S, U]
    n.vertrix_board_view_setup.restype = U
    n.vertrix_board_view_setup_forward.argtypes = n.vertrix_board_view_setup.argtypes
    n.vertrix_board_view_setup_forward.restype = U
    n.vertrix_board_burst_occupied.argtypes = [P, U, V, S, U, V, S]
    n.vertrix_board_burst_occupied.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4365c0)
    pool = Pool(cpu, 6, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x436030:
            value = rng.choice([0, 1, 5, rng.getrandbits(32)])
        elif address == 0x4826c0:
            value = rng.randrange(max(1, edx & 0xffff))
        elif address == 0x430800:
            value = rng.choice(pool.handles[1:])
        else:
            value = rng.getrandbits(32)
        if address == 0x482110:
            column = rng.getrandbits(32)
            cpu.mem_write(stack[4], struct.pack('<I', column))
            returns.append((value, column, 0))
        elif address in OUTPUTS:
            column, row = rng.randrange(0, 5), rng.randrange(0, 13)
            cpu.mem_write(ebx, struct.pack('<I', column))
            cpu.mem_write(ecx, struct.pack('<I', row))
            returns.append((value, column, row))
        else:
            returns.append((value, 0, 0))
        return value

    stubs = Stubs(cpu, handler)
    for address in CALLEES:
        stubs.add(address, 0)
    stubs.add(0x482110, 11)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        if s.target == 0x482110:
            native_log[-1] += (s.stack, s.stack_next, s.stack_third) + tuple(
                getattr(s, 'rest%d' % i) for i in range(8))
        value, column, row = replay.pop(0)
        s.out_value = column
        s.out_ebx, s.out_ecx = column, row
        return value

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    totals = {}

    def patch(handle, data):
        for column in range(5):
            for row in range(13):
                struct.pack_into('<I', data, 0x220 + 0x34 * column + 4 * row,
                                 rng.choice(pool.handles[1:]))

    def run(name, address, native, **registers):
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(address, **registers) & 0xffffffff
        replay[:] = list(returns)
        got = native()
        assert native_log == stubs.log, (name, native_log[:3], stubs.log[:3], len(native_log), len(stubs.log))
        assert got == result, (name, hex(got), hex(result))
        assert not replay, name
        assert pool.same(), (name, pool.diff())
        totals[hex(address)] = totals.get(hex(address), 0) + 1

    for case in range(args.cases):
        pool.fill(rng, patch)
        board = pool.handles[0]
        buffer = pool.buffers[board]
        arg, ebx, ecx = rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32)
        for address, name in ((0x4365c0, 'cell'), (0x436440, 'random_cell')):
            function = getattr(n, 'vertrix_board_replace_' + name)
            run(name, address, lambda: function(c.byref(calls), c.byref(services), board, buffer,
                                                SIZE, arg, FRAME, ebx, ecx),
                eax=board, edx=arg, ebx=ebx, ecx=ecx)
    for case in range(args.cases):
        pool.fill(rng, patch)
        for handle in pool.handles:
            for column in range(5):
                for row in range(13):
                    offset = 0x220 + 0x34 * column + 4 * row
                    value = struct.pack('<I', rng.choice([0, 0, rng.choice(pool.handles)]))
                    cpu.mem_write(handle + offset, value)
                    pool.buffers[handle][offset:offset + 4] = value
        first, second = rng.sample(pool.handles, 2)
        run('occupied', 0x433040, lambda: n.vertrix_board_burst_occupied(
            c.byref(calls), first, pool.buffers[first], SIZE, second, pool.buffers[second], SIZE),
            eax=first, edx=second)
    for case in range(args.cases):
        pool.fill(rng)
        obj = pool.handles[0]
        for handle in pool.handles:
            value = struct.pack('<I', rng.choice(pool.handles))
            cpu.mem_write(handle + 0x15c, value)
            pool.buffers[handle][0x15c:0x160] = value
        run('view', 0x43bbf0, lambda: n.vertrix_board_view_setup(
            c.byref(calls), c.byref(services), obj, pool.buffers[obj], SIZE, FRAME), eax=obj)
        run('view_forward', 0x43bd80, lambda: n.vertrix_board_view_setup_forward(
            c.byref(calls), c.byref(services), obj, pool.buffers[obj], SIZE, FRAME), eax=obj)
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each routine executes completely in the original with its callees stubbed '
                       'and logged (the cell coordinates stored through the ebx and ecx locals and '
                       'replayed); every callee call, the returned eax and every pool object '
                       'compare.'}
    (args.build_dir / 'board-cell-replace-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
