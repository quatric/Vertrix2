"""Compare the original double split 0x4dae1e with the native recovery."""
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
FRAME_SIZE = 0x10


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
    n = build(args.build_dir, 'float-split', ['float_split.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_float_split.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U, U, U,
                                      c.POINTER(c.c_uint64)]
    n.vertrix_float_split.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4dae1e)
    pool = Pool(cpu, 1, SIZE)
    destination = pool.handles[0]
    frame = c.create_string_buffer(FRAME_SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == FRAME - FRAME_SIZE:
            storage[0], size[0] = c.addressof(frame), FRAME_SIZE
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, fills, native_log, replay = [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        for pointer in (edx, eax):
            data = rng.randbytes(8)
            cpu.mem_write(pointer, data)
            fills.append((pointer, data))
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    stubs.add(0x4e509c, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        for _ in range(2):
            address, data = fills.pop(0)
            offset = address - (FRAME - FRAME_SIZE)
            c.memmove(c.addressof(frame) + offset, data, 8)
        return replay.pop(0)

    calls = Calls(call, None)
    for case in range(args.cases):
        pool.fill(rng)
        blob = rng.randbytes(FRAME_SIZE)
        cpu.mem_write(FRAME - FRAME_SIZE, blob)
        frame.raw = blob
        stubs.log.clear()
        returns.clear()
        fills.clear()
        native_log.clear()
        low, high, ecx = (rng.getrandbits(32) for _ in range(3))
        want_low = original.call(0x4dae1e, eax=low, edx=high, ebx=destination, ecx=ecx)
        from unicorn.x86_const import UC_X86_REG_EDX
        want = (cpu.reg_read(UC_X86_REG_EDX) << 32) | (want_low & 0xffffffff)
        replay[:] = list(returns)
        result = c.c_uint64()
        assert n.vertrix_float_split(c.byref(calls), c.byref(services), FRAME, low, high,
                                     destination, ecx, c.byref(result)), case
        assert result.value == want, (case, hex(result.value), hex(want))
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and pool.same(), (case, pool.diff())
    report = {'status': 'passed', 'complete_original_executions': {'0x4dae1e': args.cases},
              'scope': 'The routine executes completely in the original with 0x4e509c stubbed and '
                       'logged (writing the integer and fractional doubles in the frame, mirrored '
                       'for the native); the call registers, the returned edx:eax and the integer '
                       'part stored through ebx compare.'}
    (args.build_dir / 'float-split-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
