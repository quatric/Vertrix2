"""Compare the original power 0x4c9921 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from unicorn.x86_const import UC_X86_REG_EDX, UC_X86_REG_EFLAGS

from original import Original, STACK
from oracle_kit import Resolve, Stubs, build

U = c.c_uint32
FRAME = STACK - 4
REGION = FRAME - 0x24
REGION_SIZE = 0x1c
DOUBLES = (0x4dae62, 0x4dae1e, 0x4db507, 0x4eb652, 0x4dad38, 0x4dae4a, 0x4c9e2f, 0x4daed8)
CALLEES = {address: 0 for address in DOUBLES + (0x4eb57c, 0x4eb892, 0x4dad19, 0x4dae94)}


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
    n = build(args.build_dir, 'float-power', ['float_power.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_float_power.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U, U, U,
                                      c.POINTER(c.c_uint64)]
    n.vertrix_float_power.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4c9921)
    frame = c.create_string_buffer(REGION_SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == REGION:
            storage[0], size[0] = c.addressof(frame), REGION_SIZE
            return 1
        return 0

    services = Services(resolve)
    returns, outs, fills, native_log, replay = [], [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address in DOUBLES:
            high = 0 if rng.random() < 0.2 else rng.getrandbits(32)
            cpu.reg_write(UC_X86_REG_EDX, high)
            outs.append(high)
            if address == 0x4dae1e:
                data = rng.randbytes(8)
                cpu.mem_write(ebx, data)
                fills.append((ebx, data))
            returns.append(rng.getrandbits(32))
        elif address == 0x4eb57c:
            value = 1 if rng.random() < 0.2 else rng.choice([-1, 0])
            cpu.reg_write(UC_X86_REG_EFLAGS, {-1: 0x282, 0: 0x246, 1: 0x202}[value])
            returns.append(value & 0xffffffff)
        elif address == 0x4eb892:
            value = rng.choice([0, 1, -1, 2, 3, -2, 5, 7, -7, 0x80000000, rng.randrange(-100, 100)])
            returns.append(value & 0xffffffff)
        else:
            returns.append(rng.choice([0xffffffff, 0, 0, 1, rng.getrandbits(32)]))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        if s.target in DOUBLES:
            s.out_value = outs.pop(0)
        if s.target == 0x4dae1e:
            address, data = fills.pop(0)
            c.memmove(c.addressof(frame) + address - REGION, data, 8)
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}
    for case in range(args.cases):
        blob = rng.randbytes(REGION_SIZE)
        frame.raw = blob
        cpu.mem_write(REGION, blob)
        stubs.log.clear()
        returns.clear()
        outs.clear()
        fills.clear()
        native_log.clear()
        low, high, ebx, ecx = (rng.getrandbits(32) for _ in range(4))
        if rng.random() < 0.3:
            ecx = rng.choice([0, 0x80000000 | ecx, ecx & 0x7fffffff])
        want_low = original.call(0x4c9921, eax=low, edx=high, ebx=ebx, ecx=ecx)
        want = (cpu.reg_read(UC_X86_REG_EDX) << 32) | (want_low & 0xffffffff)
        replay[:] = list(returns)
        result = c.c_uint64()
        assert n.vertrix_float_power(c.byref(calls), c.byref(services), FRAME, low, high, ebx, ecx,
                                     c.byref(result)), case
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert result.value == want, (case, hex(result.value), hex(want))
        assert not replay, case
        assert frame.raw == bytes(cpu.mem_read(REGION, REGION_SIZE)), case
        key = len(stubs.log)
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4c9921': {str(k): v for k, v in sorted(totals.items())}},
              'scope': 'The routine executes completely in the original with every float helper '
                       'stubbed and logged (double results returned in eax and edx, the compare '
                       'answering through the flags it sets, the split writing its integer part '
                       'in the frame, mirrored for the native); every call with its registers, the '
                       'returned edx:eax and the stack locals compare.'}
    (args.build_dir / 'float-power-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
