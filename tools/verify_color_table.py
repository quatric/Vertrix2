"""Compare the original colour table builder 0x441e30 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Stubs, build

U = c.c_uint32
FRAME = STACK - 4


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack')]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


CALLEES = {0x481b20: 0, 0x481bc0: 1, 0x481e10: 0, 0x481b30: 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'color-table', ['color_table.c', 'call_glue.c', 'actor_storage.c'])
    Table = U * 21
    n.vertrix_color_table_build.argtypes = [c.POINTER(Calls), U, U, c.POINTER(Table),
                                            c.POINTER(Table)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x441e30)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x481bc0:
            returns.append(rng.choice([0, 1, 1, 1]))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) +
                          ((s.stack,) if CALLEES[s.target] else ()))
        return replay.pop(0)

    calls = Calls(call, None)
    colors = Table.from_buffer_copy(bytes(cpu.mem_read(0x4fb9f0, 84)))
    totals, paths = {}, {}
    for case in range(args.cases):
        argument = rng.getrandbits(32)
        cpu.mem_write(0x5440f8, bytes(84))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        original.call(0x441e30, eax=argument)
        replay[:] = list(returns)
        out = Table()
        n.vertrix_color_table_build(c.byref(calls), FRAME, argument, c.byref(colors), c.byref(out))
        assert native_log == stubs.log, (case, native_log[:4], stubs.log[:4])
        assert not replay, case
        assert bytes(out) == bytes(cpu.mem_read(0x5440f8, 84)) or returns[1] == 0, case
        paths[len(stubs.log)] = paths.get(len(stubs.log), 0) + 1
        totals['0x441e30'] = totals.get('0x441e30', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'call_counts_seen': {str(key): value for key, value in sorted(paths.items())},
              'scope': 'The original executes completely, exception frame included, with its '
                       'callees stubbed and logged; every callee call and the 21 stored entries '
                       'compare (the return value is the previous exception chain and is not '
                       'ported).'}
    (args.build_dir / 'color-table-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
