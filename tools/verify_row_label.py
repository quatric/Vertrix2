"""Compare the original labelled row builder 0x470b20 with the native recovery."""
import argparse
import ctypes as c
import random
from pathlib import Path

from original import Original
from oracle_kit import Pool, Stubs, build
from oracle_screen import (Call, Calls, Globals, Services, global_reader, site_log, write_report)

U = c.c_uint32
SIZE = 0x200
CALLEES = {0x4ca000: 0, 0x4b3100: 0, 0x4b6350: 0, 0x4adf20: 5, 0x4b54d0: 1, 0x4ac7b0: 0,
           0x4b65d0: 3, 0x4b3210: 2}
GLOBALS = ((0x4f88ac, 4), (0x4f9c08, 4))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'row-label', ['row_label.c', 'call_glue.c', 'actor_storage.c',
                                            'block_factory.c', 'actor_fields.c', 'board_cells.c'])
    n.vertrix_row_label.argtypes = [c.POINTER(Calls), c.POINTER(Services), c.POINTER(Globals), U, U,
                                    U]
    n.vertrix_row_label.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x470b20)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            returns.append(rng.choice(pool.handles))
        elif address in (0x4b3100, 0x4b6350):
            returns.append(eax)
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append(site_log(s, CALLEES[s.target]))
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    reader = global_reader(cpu)
    globals_ = Globals(reader, None)
    for case in range(args.cases):
        pool.fill(rng)
        for address, length in GLOBALS:
            cpu.mem_write(address, rng.randbytes(length))
        eax, edx, ebx = (rng.getrandbits(32) for _ in range(3))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x470b20, eax=eax, edx=edx, ebx=ebx) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_row_label(c.byref(calls), c.byref(services), c.byref(globals_), eax, edx,
                                  ebx)
        assert got == result, (case, hex(got), hex(result))
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and pool.same(), (case, pool.diff())
    write_report(args.build_dir, 'row-label', {
        'status': 'passed', 'complete_original_executions': {'0x470b20': args.cases},
        'scope': 'The original executes completely with its callees stubbed and logged; the '
                 'globals 0x4f88ac and 0x4f9c08 hold random data. Every call with its registers '
                 'and stack arguments, the returned frame actor and every pool object compare.'})


if __name__ == '__main__':
    main()
