"""Compare the original title letter builder 0x4713d0 and 0x4715a0 with the native recovery."""
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
CALLEES = {0x4ca070: 0, 0x4ca000: 0, 0x4abd70: 0, 0x4adf20: 5,
           0x43f420: 0, 0x4ac950: 0, 0x4ac8a0: 0, 0x4ac8f0: 0, 0x4ad510: 0, 0x4826c0: 0,
           0x4ac7d0: 0, 0x4ac510: 0, 0x4b5e70: 0, 0x4ca210: 0, 0x4cdfb0: 3}
GLOBALS = [0x4f8a48, 0x4f8a4c, 0x4f8a50, 0x4f8a54, 0x4f9c02]


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
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'title-letter', ['title_letter.c', 'call_glue.c', 'actor_storage.c'])
    for name in ('vertrix_title_letter_first', 'vertrix_title_letter_second'):
        getattr(n, name).argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U]
        getattr(n, name).restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x46f000)
    pool = Pool(cpu, 24, SIZE)
    globs = {g: c.create_string_buffer(4) for g in GLOBALS}
    length = [0]
    string_handle = pool.handles[23]

    @Resolve
    def resolve(handle, storage, size, context):
        if handle in globs:
            storage[0], size[0] = c.addressof(globs[handle]), 4
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, outs, native_log, replay = [], [], [], []
    free = []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4cdfb0:
            cpu.mem_write(stack[0], struct.pack('<I', string_handle + 0xc))
            outs.append(string_handle + 0xc)
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
            (s.stack, s.stack_next, s.stack_third) if s.target == 0x4cdfb0 else
            ((s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1) if s.target == 0x4adf20 else ())))
        if s.target == 0x4cdfb0:
            s.out_value = outs.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        for g, buffer in globs.items():
            word = struct.pack('<I', rng.getrandbits(32))
            buffer.raw = word
            cpu.mem_write(g, word)
        free[:] = pool.handles[:1]
        stubs.log.clear()
        returns.clear()
        outs.clear()
        native_log.clear()
        which = rng.choice([(0x4713d0, 'vertrix_title_letter_first'),
                            (0x4715a0, 'vertrix_title_letter_second')])
        mode = rng.choice([1, 1, 0, 2, rng.getrandbits(32)])
        original.call(which[0], eax=mode)
        replay[:] = list(returns)
        free[:] = pool.handles[:1]
        assert getattr(n, which[1])(c.byref(calls), c.byref(services), FRAME, mode), case
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log),
                                         [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2])
        assert not replay and pool.same(), (case, pool.diff())
        totals[hex(which[0])] = totals.get(hex(which[0]), 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              
              'scope': 'The routine executes completely in the original with the string runtime, '
                       'the allocation and the actor setters stubbed and logged (0x4cdfb0 storing '
                       'the new string through its stack pointer); every '
                       'call with its registers and stack arguments and every actor object compare.'}
    (args.build_dir / 'title-letter-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
