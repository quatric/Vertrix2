"""Compare the original letter grid builder 0x46eda0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x200
FRAME = STACK - 4
TEXT = 0x50e61f
GLOBAL = 0x4f9c0a
CALLEES = {0x4ca070: 0, 0x4ca310: 0, 0x4ac910: 0, 0x440610: 1, 0x4ca000: 0, 0x4abd70: 0, 0x4adf20: 5,
           0x43f420: 0, 0x4ac950: 0, 0x4ac8a0: 0, 0x4ac8f0: 0, 0x4ad510: 0, 0x4826c0: 0,
           0x4ac7d0: 0, 0x4ac510: 0, 0x4b5e70: 0, 0x4ca210: 0}


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
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'letter-grid', ['letter_row.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_letter_grid.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U]
    n.vertrix_letter_grid.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x46eda0)
    pool = Pool(cpu, 40, SIZE)
    counts = {0x540000 + 4 * k: c.create_string_buffer(4) for k in range(4)}
    glob = c.create_string_buffer(bytes(cpu.mem_read(GLOBAL, 4)), 4)
    length = [0]
    string_handle = pool.handles[39]

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == GLOBAL:
            storage[0], size[0] = c.addressof(glob), 4
            return 1
        if handle in counts:
            storage[0], size[0] = c.addressof(counts[handle]), 4
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, outs, native_log, replay = [], [], [], []
    free = []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca310:
            cpu.mem_write(eax, struct.pack('<I', string_handle + 0xc))
            outs.append(string_handle + 0xc)
        if address == 0x440610:
            outs.append(rng.randrange(0, 0x200))
            outs.append(rng.randrange(0, 0x40))
            cpu.mem_write(ecx, struct.pack('<I', outs[-2]))
            cpu.mem_write(stack[0], struct.pack('<I', outs[-1]))
        if address == 0x4ca000:
            returns.append(1)
        elif address == 0x4abd70:
            returns.append(free.pop(0))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) + (
            (s.stack,) if s.target == 0x440610 else
            ((s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1) if s.target == 0x4adf20 else ())))
        if s.target == 0x440610:
            s.out_ecx = outs.pop(0)
            s.out_value = outs.pop(0)
        elif s.target == 0x4ca310:
            s.out_value = outs.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        length[0] = rng.randrange(0, 7)
        index = rng.randrange(0, 4)
        number = rng.randrange(0, 5)
        counts[0x540000 + 4 * index].raw = struct.pack('<I', number)
        cpu.mem_write(0x540000 + 4 * index, struct.pack('<I', number))
        blob = bytearray(cpu.mem_read(string_handle, SIZE))
        struct.pack_into('<I', blob, 4, length[0])
        cpu.mem_write(string_handle, bytes(blob))
        c.memmove(pool.buffers[string_handle], bytes(blob), SIZE)
        free[:] = pool.handles[:max(length[0] * number, 1)]
        stubs.log.clear()
        returns.clear()
        outs.clear()
        native_log.clear()
        original.call(0x46eda0, eax=index)
        replay[:] = list(returns)
        free[:] = pool.handles[:max(length[0] * number, 1)]
        assert n.vertrix_letter_grid(c.byref(calls), c.byref(services), FRAME, index), case
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log),
                                         [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2])
        assert not replay and pool.same(), (case, pool.diff())
        totals[number] = totals.get(number, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': args.cases, 'row_counts': totals,
              
              'scope': 'The routine executes completely in the original with the string runtime, '
                       'the allocation and the actor setters stubbed and logged (0x440610 storing '
                       'the width through its ecx pointer, 0x4ca310 storing the copied string); every '
                       'call with its registers and stack arguments and every actor object compare.'}
    (args.build_dir / 'letter-grid-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
