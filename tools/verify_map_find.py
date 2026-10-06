"""Compare the original hash map find-or-add 0x4df160 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x100
CALLEES = {0x4df0f0: 0, 0x4def50: 0, 0x4e23e0: 3}


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
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'map-find', ['node_pool.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_map_find_or_add.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U,
                                          c.POINTER(U)]
    n.vertrix_map_find_or_add.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4df160)
    pool = Pool(cpu, 5, SIZE)
    returns, hashes, native_log, replay = [], [], [], []
    local = STACK - 16

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4e23e0:
            returns.append(pool.handles[2])
        elif address == 0x4df0f0:
            hashes.append(rng.randrange(0, 8))
            cpu.mem_write(ebx, struct.pack('<I', hashes[-1]))
            returns.append(rng.choice([0, 0, pool.handles[4] + 0]))
        elif address == 0x4def50:
            cpu.mem_write(eax + 4, struct.pack('<I', pool.handles[3]))
            returns.append(rng.getrandbits(32))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)
    replay_hash = []

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) + (
            (s.stack, s.stack_next, s.stack_third) if s.target == 0x4e23e0 else ()))
        if s.target == 0x4def50:
            struct.pack_into('<I', pool.buffers[s.eax], 4, pool.handles[3])
        if s.target == 0x4df0f0:
            s.out_value = replay_hash.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        owner, head, block, array, found = pool.handles
        assert array == pool.handles[3]
        data = bytearray(rng.randbytes(SIZE))
        has_buckets = rng.random() < 0.6
        struct.pack_into('<IIIIII', data, 4, array if has_buckets else 0, rng.randrange(1, 9),
                         rng.randrange(0, 100), head if rng.random() < 0.5 else 0,
                         rng.getrandbits(32), rng.choice([1, 2, 3, 5]))
        cpu.mem_write(owner, bytes(data))
        c.memmove(pool.buffers[owner], bytes(data), SIZE)
        # a found node is a pool handle with the value word at +0xc
        key = rng.getrandbits(32)
        stubs.log.clear()
        returns.clear()
        hashes.clear()
        native_log.clear()
        cpu.mem_write(local, bytes(4))
        result = original.call(0x4df160, eax=owner, edx=key) & 0xffffffff
        replay[:] = list(returns)
        replay_hash[:] = list(hashes)
        value = U()
        ok = n.vertrix_map_find_or_add(c.byref(calls), c.byref(services), local, owner, key,
                                       c.byref(value))
        assert ok, case
        assert value.value == result, (case, hex(value.value), hex(result))
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and pool.same(), (case, pool.diff())
        kind = 'found' if returns[0] != 0 else 'added'
        totals[kind] = totals.get(kind, 0) + 1
    assert totals.get('found', 0) > 50 and totals.get('added', 0) > 50, totals
    report = {'status': 'passed', 'complete_original_executions': {'0x4df160': totals},
              'scope': 'The routine executes completely in the original with 0x4df0f0, 0x4def50 '
                       'and 0x4e23e0 stubbed and logged (0x4df070 unstubbed); every callee call, '
                       'the returned value address and every pool object compare.'}
    (args.build_dir / 'map-find-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
