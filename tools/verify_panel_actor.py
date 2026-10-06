"""Compare the original panel builder 0x471020 with the native recovery."""
import argparse
import ctypes as c
import random
from pathlib import Path

from original import Original
from oracle_kit import Pool, Stubs, build
from oracle_screen import (Call, Calls, Globals, Services, global_reader, site_log, write_report)

U = c.c_uint32
SIZE = 0x200
CALLEES = {0x4ca000: 0, 0x4b2400: 0, 0x4adf20: 5, 0x4b25b0: 10, 0x4b2d90: 0}
VIRTUAL = {0x4ac130: 0, 0x4b3140: 0}
TABLES = (0x517af4, 0x517c64)
GLOBALS = ((0x4f87fe, 4), (0x4f8802, 4), (0x4f8806, 4), (0x4f880c, 2), (0x4f9bff, 4))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'panel-actor', ['panel_actor.c', 'call_glue.c', 'actor_storage.c',
                                              'block_factory.c', 'actor_fields.c',
                                              'board_cells.c'])
    n.vertrix_panel_spawn.argtypes = [c.POINTER(Calls), c.POINTER(Services), c.POINTER(Globals), U,
                                      U, U, U]
    n.vertrix_panel_spawn.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x471020)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            returns.append(rng.choice(pool.handles + [0] * 2))
        elif address == 0x4b2400:
            returns.append(eax)
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    callees = dict(CALLEES)
    callees.update(VIRTUAL)
    stubs = Stubs(cpu, handler)
    for address, count in callees.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append(site_log(s, callees[s.target]))
        return replay.pop(0)

    def patch(handle, data):
        data[0x158:0x15c] = rng.choice(TABLES).to_bytes(4, 'little')

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    reader = global_reader(cpu)
    globals_ = Globals(reader, None)
    for case in range(args.cases):
        pool.fill(rng, patch)
        for address, length in GLOBALS:
            cpu.mem_write(address, rng.randbytes(length))
        text, edx, ebx, ecx = (rng.getrandbits(32) for _ in range(4))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x471020, eax=text, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_panel_spawn(c.byref(calls), c.byref(services), c.byref(globals_), text,
                                    edx, ebx, ecx)
        assert got == result, (case, hex(got), hex(result))
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and pool.same(), (case, pool.diff())
    write_report(args.build_dir, 'panel-actor', {
        'status': 'passed', 'complete_original_executions': {'0x471020': args.cases},
        'scope': 'The original executes completely with its callees stubbed and logged (0x4b25b0 '
                 'with its ten stack arguments, the virtual call through the vtable at +0x158, '
                 'two real vtables used); the layout globals hold random data. Every call, the '
                 'returned eax and every pool object compare; the allocator also fails (zero) in a third of the cases.'})


if __name__ == '__main__':
    main()
