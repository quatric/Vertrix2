"""Compare the original mask routine 0x4ab200 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Stubs, build

U = c.c_uint32
SIZE = 0x800


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


SURFACE_OBJECT, SURFACE, SOURCE, MASK = 0x800a00, 0x800e00, 0x801400, 0x801000
CALLEE = 0x478eb0


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'surface-mask', ['surface_mask.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_surface_mask32.argtypes = [c.POINTER(Calls), U, U, U, U, U, U, U, U, c.c_void_p,
                                         c.c_void_p]
    n.vertrix_surface_mask32.restype = None
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4ab200)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        returns.append(MASK)
        return MASK

    stubs = Stubs(cpu, handler)
    stubs.add(CALLEE, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    count = 0
    for case in range(args.cases):
        width, height = rng.randrange(0, 9), rng.randrange(0, 5)
        mask_width = rng.randrange(8, 17)
        skip = rng.randrange(0, 7)
        x, y = rng.getrandbits(32), rng.getrandbits(32)
        wide = width | rng.choice([0, 0x10000 * rng.getrandbits(16)])
        tall = height | rng.choice([0, 0x10000 * rng.getrandbits(16)])
        pixels = struct.pack('<256I', *[rng.choice([0, 0x00ffffff, 0x01000000, rng.getrandbits(32)])
                                        for _ in range(256)])
        mask = rng.randbytes(0x100)
        cpu.mem_write(0x544070, struct.pack('<I', SURFACE_OBJECT))
        cpu.mem_write(SURFACE_OBJECT + 0x274, struct.pack('<I', SURFACE))
        cpu.mem_write(SURFACE + 4, struct.pack('<I', mask_width))
        cpu.mem_write(0x5bb764, struct.pack('<I', SOURCE))
        cpu.mem_write(0x5bb79c, struct.pack('<I', skip))
        cpu.mem_write(SOURCE, pixels)
        cpu.mem_write(MASK, mask)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        original.call(0x4ab200, eax=x, edx=y, ebx=wide, ecx=tall)
        replay[:] = list(returns)
        host_mask = c.create_string_buffer(mask, 0x100)
        n.vertrix_surface_mask32(c.byref(calls), SURFACE, mask_width, SOURCE, skip, x, y, wide,
                                 tall, pixels, host_mask)
        assert native_log == stubs.log and not replay, (native_log, stubs.log)
        assert host_mask.raw == bytes(cpu.mem_read(MASK, 0x100)), (width, height, mask_width, skip)
        count += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4ab200': count},
              'scope': 'The routine executes completely in the original with 0x478eb0 stubbed '
                       '(returning the mask) and logged; the call registers and the mask bytes '
                       'compare, with zero and 16 bit wrapped counts.'}
    (args.build_dir / 'surface-mask-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
