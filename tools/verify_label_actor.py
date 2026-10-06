"""Compare the original label actor constructors 0x45fb00, 0x45fc80, 0x45fe10 and 0x45fee0 with
the native recovery."""
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


CALLEES = {0x4ca000: 0, 0x4b3100: 0, 0x4b6350: 0, 0x4b5400: 0, 0x4adf20: 5, 0x4b54d0: 1,
           0x4ac7b0: 0, 0x4ac4e0: 0, 0x4ac4f0: 0, 0x4b65d0: 3, 0x4b3210: 2}
FRAMES = ((0x45fb00, 0), (0x45fc80, 1))
BOXES = ((0x45fe10, 0), (0x45fee0, 1))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'label-actor', ['label_actor.c', 'call_glue.c', 'actor_storage.c',
                                              'block_factory.c', 'actor_fields.c',
                                              'board_cells.c'])
    n.vertrix_label_frame.argtypes = [c.POINTER(Calls), c.POINTER(Services), c.c_uint, U, U, U, U,
                                      U * 5]
    n.vertrix_label_frame.restype = U
    n.vertrix_label_box.argtypes = [c.POINTER(Calls), c.POINTER(Services), c.c_uint, U, U, U, U, U]
    n.vertrix_label_box.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x45fb00)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            returns.append(rng.choice(pool.handles))
        elif address in (0x4b3100, 0x4b6350, 0x4b5400):
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
        count = CALLEES[s.target]
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) +
                          (s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1)[:count])
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    totals = {}
    for case in range(args.cases):
        for address, variant in FRAMES + BOXES:
            pool.fill(rng)
            p, dw, bx, cx = (rng.getrandbits(32) for _ in range(4))
            arguments = [rng.getrandbits(32) for _ in range(5)]
            stubs.log.clear()
            returns.clear()
            native_log.clear()
            if (address, variant) in FRAMES:
                result = original.call(address, eax=p, edx=dw, ebx=bx, ecx=cx,
                                       args=tuple(arguments)) & 0xffffffff
                replay[:] = list(returns)
                got = n.vertrix_label_frame(c.byref(calls), c.byref(services), variant, p, dw, bx,
                                            cx, (U * 5)(*arguments))
            else:
                stale = struct.unpack('<H', bytes(cpu.mem_read(STACK - 0xe, 2)))[0]
                result = original.call(address, eax=p, edx=dw, ebx=bx, ecx=cx) & 0xffffffff
                replay[:] = list(returns)
                got = n.vertrix_label_box(c.byref(calls), c.byref(services), variant, p, dw, bx,
                                          cx, stale)
            assert got == result, (hex(address), hex(got), hex(result))
            assert native_log == stubs.log, (hex(address), native_log, stubs.log)
            assert not replay and pool.same(), (hex(address), pool.diff())
            totals[hex(address)] = totals.get(hex(address), 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each routine executes completely in the original with its callees '
                       'stubbed and logged (registers and stack arguments); every call, the '
                       'returned actor and every pool object compare. The 0x45fe10 and 0x45fee0 '
                       'stale stack halfword is read from the oracle stack.'}
    (args.build_dir / 'label-actor-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
