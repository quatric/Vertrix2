"""Compare the original frame header read 0x407280 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x400
WORDS = 0x4f5918
WORDS_SIZE = 0x500
TABLES = 0x4f5e78
TABLES_SIZE = 0x20


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
    n = build(args.build_dir, 'bits-header', ['bits_fill.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_bits_header.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, c.c_int32, U, U, U]
    n.vertrix_bits_header.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x407280)
    pool = Pool(cpu, 2, SIZE)
    words = c.create_string_buffer(bytes(cpu.mem_read(WORDS, WORDS_SIZE)), WORDS_SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == WORDS:
            storage[0] = c.addressof(words)
            size[0] = WORDS_SIZE
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address in (0x404610, 0x404680):
            returns.append(rng.getrandbits(eax) if 0 < eax < 32 else rng.getrandbits(32))
        elif address == 0x4046e0:
            returns.append(rng.choice([0, 1]))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address in (0x404610, 0x404680, 0x4046e0, 0x4eb4d4):
        stubs.add(address, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        record = pool.handles[0]
        count = rng.choice([0, 1, 1, 2, 3, 0xffffffff])
        flag = rng.choice([0, 1, rng.getrandbits(32)])
        selector = rng.choice([8, rng.randrange(0, 8), rng.randrange(0, 9)])
        mode = rng.choice([3, 3, rng.randrange(0, 5)])
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        original.call(0x407280, eax=record, edx=count, ebx=flag, ecx=selector, args=(mode,))
        replay[:] = list(returns)
        assert n.vertrix_bits_header(c.byref(calls), c.byref(services), record,
                                     c.c_int32(count).value if count < 0x80000000 else count - (1 << 32),
                                     flag, selector, mode), case
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log), native_log[:3], stubs.log[:3])
        assert not replay and pool.same(), (case, pool.diff())
        totals[str(count if count < 8 else 'neg')] = totals.get(str(count if count < 8 else 'neg'), 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x407280': totals},
              'scope': 'The routine executes completely in the original with 0x404610, 0x404680, '
                       '0x4046e0 and 0x4eb4d4 stubbed and logged (bit reads return values below 2^width); '
                       'every call with its registers and every record dword compare.'}
    (args.build_dir / 'bits-header-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
