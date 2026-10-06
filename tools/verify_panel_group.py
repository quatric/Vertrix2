"""Compare the original panel group builder 0x470d20 with the native recovery."""
import argparse
import ctypes as c
import random
from pathlib import Path

from original import Original
from oracle_kit import Pool, Stubs, build
from oracle_screen import (Call, Calls, Globals, Services, global_reader, site_log, write_report)

U = c.c_uint32
SIZE = 0x200
CALLEES = {0x4ca000: 0, 0x4b2400: 0, 0x4b6350: 0, 0x4adf20: 5, 0x4b25b0: 10, 0x4ac7b0: 0,
           0x4b65d0: 3, 0x4b5e70: 0}
GLOBALS = ((0x4f87fe, 0x24), (0x4f9bff, 4), (0x540019, 4))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'panel-group', ['panel_group.c', 'call_glue.c', 'actor_storage.c',
                                              'block_factory.c', 'actor_fields.c',
                                              'board_cells.c'])
    n.vertrix_panel_group.argtypes = [c.POINTER(Calls), c.POINTER(Services), c.POINTER(Globals), U,
                                      U, U, U]
    n.vertrix_panel_group.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x470d20)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            returns.append(rng.choice(pool.handles))
        elif address in (0x4b2400, 0x4b6350):
            returns.append(eax)
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    callees = dict(CALLEES)
    stubs = Stubs(cpu, handler)
    for address, count in callees.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append(site_log(s, callees[s.target]))
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    reader = global_reader(cpu)
    globals_ = Globals(reader, None)
    for case in range(args.cases):
        pool.fill(rng)
        for address, length in GLOBALS:
            cpu.mem_write(address, rng.randbytes(length))
        texts = [rng.choice([0, rng.getrandbits(32) | 1]) for _ in range(4)]
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x470d20, eax=texts[0], edx=texts[1], ebx=texts[2],
                               ecx=texts[3]) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_panel_group(c.byref(calls), c.byref(services), c.byref(globals_), *texts)
        assert got == result, (case, hex(got), hex(result))
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and pool.same(), (case, pool.diff())
    write_report(args.build_dir, 'panel-group', {
        'status': 'passed', 'complete_original_executions': {'0x470d20': args.cases},
        'scope': 'The original executes completely with its callees stubbed and logged (0x4b25b0 '
                 'with its ten stack arguments, 0x4adf20 with five); each of the four texts is '
                 'zero in half of the cases and the layout globals hold random data. Every call '
                 'with the registers the previous call left, the returned eax and every pool '
                 'object compare.'})


if __name__ == '__main__':
    main()
