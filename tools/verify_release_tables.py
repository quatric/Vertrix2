"""Compare the complete original shutdown release loops with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Stubs, build

U = c.c_uint32
Release = c.CFUNCTYPE(None, c.c_uint32, c.c_void_p)
TABLE_A, STATE_A, TABLE_B = 0x5410f8, 0x54406c, 0x54414c


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'release-tables', ['release_tables.c'])
    n.vertrix_release_table_a.argtypes = [c.POINTER(U), c.POINTER(U), Release, c.c_void_p]
    n.vertrix_release_table_b.argtypes = [c.POINTER(U), Release, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    stubs = Stubs(cpu, lambda *a: None)
    stubs.add(0x4830f0)
    stubs.add(0x4ea190)
    native = []

    @Release
    def release(handle, context):
        native.append(handle)

    rng = random.Random(0x43f3f0)
    totals = {'table_a': 0, 'table_b': 0}
    for case in range(args.cases):
        density = rng.choice([0.0, 0.3, 1.0])
        a = [rng.getrandbits(32) if rng.random() < density else 0 for _ in range(548)]
        b = [rng.getrandbits(32) if rng.random() < density else 0 for _ in range(115)]
        cpu.mem_write(TABLE_A, struct.pack('<548I', *a))
        cpu.mem_write(TABLE_B, struct.pack('<115I', *b))
        cpu.mem_write(STATE_A, struct.pack('<I', rng.getrandbits(32)))
        stubs.log.clear()
        native.clear()
        original.call(0x43f3f0)
        state = U(7)
        n.vertrix_release_table_a((U * 548)(*a), c.byref(state), release, None)
        assert [e[1] for e in stubs.log] == native, case
        assert state.value == struct.unpack('<I', cpu.mem_read(STATE_A, 4))[0], case
        assert bytes(cpu.mem_read(TABLE_A, 548 * 4)) == struct.pack('<548I', *a), case
        totals['table_a'] += 1
        stubs.log.clear()
        native.clear()
        original.call(0x442110)
        n.vertrix_release_table_b((U * 115)(*b), release, None)
        assert [e[1] for e in stubs.log] == native, case
        totals['table_b'] += 1
    report = {'status':
        'passed', 'complete_original_executions' : totals,
                                                   'scope'
            : 'Complete 43f3f0 and 442110 execute in the original with the release ' 'routines 4830f0 and 4ea190 stubbed; the ordered release events, the ' 'state dword and the unchanged tables compare.'
        }
        (args.build_dir / 'release-tables-verification.json')
                .write_text(json.dumps(report, indent = 2) + '\n')
                    print(json.dumps(report, indent = 2))

                        if __name__ == '__main__' : main()
