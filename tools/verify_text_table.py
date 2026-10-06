"""Compare the original text table refresh 0x415180 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x100
REGION = 0x53bd00
REGION_SIZE = 0x3d0
TABLE = 0x53bdfc


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=256)
    args = parser.parse_args()
    n = build(args.build_dir, 'text-table', ['text_table.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_text_table_refresh.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U]
    n.vertrix_text_table_refresh.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x415180)
    pool = Pool(cpu, 4, SIZE)
    region = c.create_string_buffer(REGION_SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == REGION:
            storage[0] = c.addressof(region)
            size[0] = REGION_SIZE
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(rng.choice([0, 1]) if address == 0x4ccfe0 and eax else
                       0 if address == 0x4ccfe0 else rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    stubs.add(0x4ca310, 0)
    stubs.add(0x4ccfe0, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    for case in range(args.cases):
        pool.fill(rng)
        blob = bytearray(rng.randbytes(REGION_SIZE))
        for row in range(20):
            for column in range(9):
                value = rng.choice(pool.handles) + 0xc if rng.random() < 0.8 else 0
                struct.pack_into('<I', blob, TABLE - REGION + row * 0x24 + column * 4, value)
        cpu.mem_write(REGION, bytes(blob))
        c.memmove(region, bytes(blob), REGION_SIZE)
        for handle in pool.handles:
            data = bytearray(cpu.mem_read(handle, SIZE))
            struct.pack_into('<I', data, 4, rng.randrange(0, 100))
            cpu.mem_write(handle, bytes(data))
            c.memmove(pool.buffers[handle], bytes(data), SIZE)
        first, second = rng.getrandbits(32), rng.getrandbits(32)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        original.call(0x415180, eax=first, edx=second)
        replay[:] = list(returns)
        assert n.vertrix_text_table_refresh(c.byref(calls), c.byref(services), first, second), case
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log))
        assert not replay and pool.same(), (case, pool.diff())
        want = bytes(cpu.mem_read(REGION, REGION_SIZE))
        diff = [hex(REGION + i) for i in range(REGION_SIZE) if region.raw[i] != want[i]]
        assert not diff, (case, diff[:10], region.raw[8:16].hex(), want[8:16].hex())
    report = {'status': 'passed', 'complete_original_executions': {'0x415180': args.cases},
              'scope': 'The routine executes completely in the original with 0x4ca310 and 0x4ccfe0 '
                       'stubbed and logged; every callee call (about 300 a run), the table region '
                       'and every string header object compare. The original eax is scratch.'}
    (args.build_dir / 'text-table-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
