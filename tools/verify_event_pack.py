"""Compare the original track event packer 0x40f1a0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x400
SPECIAL = ((1, 0), (2, 0), (0xa, 0), (0xe, 0x10), (0xe, 0x20), (0xe, 0xa0), (0xe, 0xb0), (8, 0x80))


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(14)] + [('out_value', U)]


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
    n = build(args.build_dir, 'event-pack', ['event_pack.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_event_pack.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U, c.POINTER(U)]
    n.vertrix_event_pack.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x40f1a0)
    pool = Pool(cpu, 2, SIZE)
    services = Services(pool.resolve)
    returns, fills, native_log, replay = [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x40c220:
            data = bytearray()
            for _ in range(edx // 4):
                if rng.random() < 0.3:
                    low, b3 = rng.choice(SPECIAL)
                else:
                    low, b3 = rng.randrange(16), rng.randrange(256)
                data += bytes([rng.randrange(256), rng.randrange(256),
                               rng.randrange(16) << 4 | low, b3])
            cpu.mem_write(eax, bytes(data))
            fills.append((eax, bytes(data)))
            returns.append(rng.getrandbits(32))
        elif address in (0x4e7c90, 0x4ec0e0):
            returns.append(0 if rng.random() < 0.1 else pool.handles[1])
        elif address == 0x40f170:
            returns.append(rng.choice([0, rng.getrandbits(32)]))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address in (0x4e7c90, 0x40c220, 0x40f170, 0x4ec0e0):
        stubs.add(address, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        if s.target == 0x40c220:
            address, data = fills.pop(0)
            offset = address - pool.handles[1]
            c.memmove(c.addressof(pool.buffers[pool.handles[1]]) + offset, data, len(data))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        number = rng.choice([0, 1, 2, 3, 3])
        ebx = rng.getrandbits(32)
        stubs.log.clear()
        returns.clear()
        fills.clear()
        native_log.clear()
        want = original.call(0x40f1a0, eax=number, edx=pool.handles[0], ebx=ebx) & 0xffffffff
        replay[:] = list(returns)
        fills_native = list(fills)
        fills[:] = fills_native
        result = U()
        assert n.vertrix_event_pack(c.byref(calls), c.byref(services), number, pool.handles[0],
                                    ebx, c.byref(result)), case
        assert result.value == want, (case, result.value, want)
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log),
                                         [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2])
        assert not replay and pool.same(), (case, pool.diff())
        totals[number] = totals.get(number, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x40f1a0': {str(k): v for k, v in totals.items()}},
              'scope': 'The routine executes completely in the original with 0x4e7c90, 0x40c220, '
                       '0x40f170 and 0x4ec0e0 stubbed and logged (0x40c220 filling the source '
                       'bytes, with the dropped commands); every call with its registers, the '
                       'returned eax, the record and the packed buffer compare.'}
    (args.build_dir / 'event-pack-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
