"""Compare the original bitmap loader 0x473cf0 with the native recovery."""
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
FRAME_SIZE = 0x80
CALLEES = (0x48a8a0, 0x48aad0, 0x48a930, 0x478d10, 0x48aaf0, 0x48aa90, 0x479b50)


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
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'bitmap-load', ['bitmap_load.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_bitmap_load.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U, U, U,
                                      c.POINTER(U)]
    n.vertrix_bitmap_load.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x473cf0)
    pool = Pool(cpu, 3, SIZE)
    frame = c.create_string_buffer(FRAME_SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == FRAME - FRAME_SIZE:
            storage[0], size[0] = c.addressof(frame), FRAME_SIZE
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, fills, native_log, replay = [], [], [], []
    valid = [True]

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x48a930:
            if ecx == 0xe:
                data = bytearray(rng.randbytes(0xe))
            elif ecx == 0x2c:
                good = valid[0]
                data = bytearray(rng.randbytes(0x2c))
                struct.pack_into('<I', data, 0, 0x28 if good else rng.getrandbits(32))
                struct.pack_into('<ii', data, 4, rng.randrange(0, 7), rng.randrange(-4, 4))
                struct.pack_into('<HH', data, 12, 1 if good else rng.randrange(0, 3),
                                 0x18 if good else rng.randrange(0, 40))
                struct.pack_into('<I', data, 16, 0 if good else rng.getrandbits(32))
            else:
                data = bytearray(rng.randbytes(max(1, ebx * ecx)))
            cpu.mem_write(edx, bytes(data))
            fills.append((edx, bytes(data)))
            returns.append(rng.getrandbits(32))
        elif address == 0x478d10:
            returns.append(pool.handles[0])
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address in CALLEES:
        stubs.add(address, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        if s.target == 0x48a930:
            address, data = fills.pop(0)
            offset = address - (FRAME - FRAME_SIZE)
            c.memmove(c.addressof(frame) + offset, data, len(data))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {'loaded': 0, 'rejected': 0, 'empty': 0}
    for case in range(args.cases):
        pool.fill(rng)
        surface, pixels, _ = pool.handles
        data = bytearray(cpu.mem_read(surface, SIZE))
        struct.pack_into('<I', data, 0, pixels)
        cpu.mem_write(surface, bytes(data))
        c.memmove(pool.buffers[surface], bytes(data), SIZE)
        stack = bytes(cpu.mem_read(FRAME - FRAME_SIZE, FRAME_SIZE))
        c.memmove(frame, stack, FRAME_SIZE)
        valid[0] = rng.random() < 0.85
        stream, edx, ebx, ecx = (rng.getrandbits(32) for _ in range(4))
        stubs.log.clear()
        returns.clear()
        fills.clear()
        native_log.clear()
        want = original.call(0x473cf0, eax=stream, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
        replay[:] = list(returns)
        result = U()
        assert n.vertrix_bitmap_load(c.byref(calls), c.byref(services), FRAME, stream, edx, ebx,
                                     ecx, c.byref(result)), case
        assert result.value == want, (case, result.value, want)
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log),
                                         [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2])
        assert not replay and pool.same(), (case, pool.diff())
        if want == 0:
            totals['rejected'] += 1
        elif not any(e[0] == 0x48aa90 for e in stubs.log):
            totals['empty'] += 1
        else:
            totals['loaded'] += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x473cf0': totals},
              'scope': 'The routine executes completely in the original with the stream and '
                       'surface callees stubbed and logged (0x48a930 filling the frame locals and '
                       'mirrored for the native); every call with its registers, the returned '
                       'surface and the converted pixels compare.'}
    (args.build_dir / 'bitmap-load-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
