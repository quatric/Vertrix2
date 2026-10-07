"""Compare the original resource table loops with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Stubs, build

U = c.c_uint32


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next')]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Dims(c.Structure):
    _fields_ = [(name, U) for name in ('count', 'columns', 'cell_width', 'cell_height')]


class Row(c.Structure):
    _fields_ = [(name, U) for name in ('left', 'top', 'spacing', 'row_spacing')]


CALLEES = (0x4877f0, 0x4831b0, 0x487640, 0x487850, 0x418270, 0x482e10, 0x483ed0, 0x483ce0)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'table-loops', ['table_loops.c', 'call_glue.c', 'actor_storage.c'])
    P = c.POINTER(Calls)
    n.vertrix_resource_rows_build.argtypes = [P, U]
    n.vertrix_resource_column_build.argtypes = [P]
    n.vertrix_resource_grid_finish.argtypes = [P, c.POINTER(Dims), U]
    n.vertrix_resource_single_finish.argtypes = [P, U, U]
    n.vertrix_resource_cell_rows.argtypes = [P, c.POINTER(Row * 3), U, U, U]
    n.vertrix_resource_paired_finish.argtypes = [P, c.POINTER(U * 13), c.POINTER(U * 13), U]
    n.vertrix_resource_indexed_finish.argtypes = [P, c.c_char_p, c.c_char_p, U, U, U]
    n.vertrix_resource_stride_finish.argtypes = [P, U]
    n.vertrix_resource_flagged_finish.argtypes = [P, U, U, U]
    n.vertrix_table_identity_cells.argtypes = [c.c_char_p]
    for name in ('rows_build', 'column_build', 'grid_finish', 'single_finish', 'cell_rows',
                 'paired_finish', 'indexed_finish', 'stride_finish', 'flagged_finish'):
        getattr(n, 'vertrix_resource_' + name).restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x45e590)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address in CALLEES:
        stubs.add(address, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}

    def run(name, address, native, **registers):
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(address, **registers) & 0xffffffff
        replay[:] = list(returns)
        got = native()
        assert got == result, (name, hex(got), hex(result))
        assert native_log == stubs.log, (name, native_log[:3], stubs.log[:3])
        assert not replay, name
        totals[hex(address)] = totals.get(hex(address), 0) + 1

    for case in range(args.cases):
        ebx = rng.getrandbits(32)
        run('rows', 0x45e590, lambda: n.vertrix_resource_rows_build(c.byref(calls), ebx), ebx=ebx)
        run('column', 0x45e6b0, lambda: n.vertrix_resource_column_build(c.byref(calls)))
        dims = Dims(rng.choice([0, rng.randrange(1, 12)]), rng.randrange(1, 5), rng.randrange(0, 40),
                    rng.randrange(0, 40))
        cpu.mem_write(0x4f90b0, struct.pack('<IIII', dims.count, dims.columns, dims.cell_width,
                                            dims.cell_height))
        argument = rng.getrandbits(32)
        run('grid', 0x45ec50, lambda: n.vertrix_resource_grid_finish(c.byref(calls), c.byref(dims),
                                                                      argument), eax=argument)
    first13 = (U * 13).from_buffer_copy(bytes(cpu.mem_read(0x4fbfe0, 52)))
    second13 = (U * 13).from_buffer_copy(bytes(cpu.mem_read(0x4fc014, 52)))
    first7 = bytes(cpu.mem_read(0x4fc050, 7))
    second7 = bytes(cpu.mem_read(0x4fc058, 7))
    for case in range(args.cases):
        argument, selector = rng.getrandbits(32), rng.getrandbits(32)
        run('single', 0x45ed10, lambda: n.vertrix_resource_single_finish(c.byref(calls), selector,
                                                                          argument),
            eax=selector, edx=argument)
        rows = (Row * 3)(*[Row(*(rng.randrange(0, 200) for _ in range(4))) for _ in range(3)])
        for base, row in zip((0x4f9090, 0x4f9080, 0x4f90a0), rows):
            cpu.mem_write(base, struct.pack('<IIII', row.left, row.top, row.spacing,
                                            row.row_spacing))
        ebx, ecx = rng.getrandbits(32), rng.getrandbits(32)
        run('cells', 0x45ee30, lambda: n.vertrix_resource_cell_rows(c.byref(calls), c.byref(rows),
                                                                     argument, ebx, ecx),
            eax=argument, ebx=ebx, ecx=ecx)
        run('paired', 0x45f020, lambda: n.vertrix_resource_paired_finish(
            c.byref(calls), c.byref(first13), c.byref(second13), argument), eax=argument)
        line, column = rng.randrange(0, 7), rng.randrange(0, 7)
        run('indexed', 0x45f140, lambda: n.vertrix_resource_indexed_finish(
            c.byref(calls), first7, second7, line, column, argument), eax=argument, edx=line,
            ebx=column)
        run('stride', 0x45f1f0, lambda: n.vertrix_resource_stride_finish(c.byref(calls), argument),
            eax=argument)
        flag, count = rng.choice([0, 1, 1, 2]), rng.choice([0, rng.randrange(1, 9)])
        run('flagged', 0x45f250, lambda: n.vertrix_resource_flagged_finish(
            c.byref(calls), argument, flag, count), eax=argument, edx=flag, ebx=count)
    # 0x45f1e0 initializes the fixed comparison table to 0..6; exercise it in place.
    clear_rng = random.Random(0x45f1e0)
    for _ in range(args.cases):
        cells = bytes(clear_rng.getrandbits(8) for _ in range(7))
        cpu.mem_write(0x53bcc8, cells)
        original.call(0x45f1e0)
        host = c.create_string_buffer(cells, 7)
        n.vertrix_table_identity_cells(host)
        assert host.raw == bytes(cpu.mem_read(0x53bcc8, 7)) == bytes(range(7))
        totals['0x45f1e0'] = totals.get('0x45f1e0', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each loop executes completely in the original with its callees stubbed and '
                       'logged; every callee call (address and registers) and the returned eax '
                       'compare.'}
    (args.build_dir / 'table-loops-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
