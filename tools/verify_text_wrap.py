"""Compare the original text line breaker 0x4b25b0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x600
FRAME = STACK - 4
FRAME_REGION = 0x10
CALLEES = {0x4ca370: 0, 0x4ca280: 0, 0x4ca630: 0, 0x440610: 1, 0x4ca210: 0}


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


class Wrap(c.Structure):
    _fields_ = [(name, U) for name in ('object', 'text', 'font', 'ecx', 'left', 'right', 'bottom',
                                       'margin_left', 'margin_right', 'spacing_a', 'spacing_b',
                                       'flag_a', 'flag_b', 'flag_c')]


def sentence(rng):
    words = []
    for _ in range(rng.randrange(0, 16)):
        words.append(bytes(rng.randrange(0x61, 0x6a) for _ in range(rng.randrange(1, 9))))
    out = bytes(rng.randrange(0, 3) * b' ')
    for word in words:
        out += word + b' ' * rng.randrange(1, 4)
    if out and rng.random() < 0.5:
        out = out.rstrip(b' ')
    return out + b'\0'


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'text-wrap', ['text_wrap.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_text_wrap.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, c.POINTER(Wrap)]
    n.vertrix_text_wrap.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4b25b0)
    pool = Pool(cpu, 4, SIZE)
    obj, text_handle, copy_handle, _ = pool.handles
    frame = c.create_string_buffer(4)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == FRAME - FRAME_REGION:
            storage[0], size[0] = c.addressof(frame), 4
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, outs, native_log, replay = [], [], [], []
    chosen = [text_handle]

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca370:
            cpu.mem_write(eax, struct.pack('<I', chosen[0]))
            outs.append(chosen[0])
        elif address in (0x4ca280, 0x4ca630):
            value = rng.getrandbits(32) | 1
            cpu.mem_write(eax, struct.pack('<I', value))
            outs.append(value)
        elif address == 0x440610:
            width = rng.randrange(0, 10)
            cpu.mem_write(ecx, struct.pack('<I', width))
            cpu.mem_write(stack[0], struct.pack('<I', rng.getrandbits(32)))
            outs.append(width)
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) + (
            (s.stack,) if s.target == 0x440610 else ()))
        if s.target == 0x440610:
            s.out_ecx = outs.pop(0)
        elif s.target in (0x4ca370, 0x4ca280, 0x4ca630):
            s.out_value = outs.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        data = sentence(rng)
        chosen[0] = text_handle if rng.random() < 0.5 else copy_handle
        for handle in (text_handle, copy_handle):
            blob = bytearray(cpu.mem_read(handle, SIZE))
            blob[:len(data)] = data
            cpu.mem_write(handle, bytes(blob))
            c.memmove(pool.buffers[handle], bytes(blob), SIZE)
        junk = rng.randbytes(4)
        cpu.mem_write(FRAME - FRAME_REGION, junk)
        frame.raw = junk
        stubs.log.clear()
        returns.clear()
        outs.clear()
        native_log.clear()
        wrap = Wrap(obj, text_handle, rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32),
                    rng.randrange(95, 220), rng.getrandbits(32), rng.randrange(0, 8),
                    rng.randrange(0, 8), rng.getrandbits(32), rng.getrandbits(32),
                    rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32))
        original.call(0x4b25b0, eax=obj, edx=text_handle, ebx=wrap.font, ecx=wrap.ecx,
                      args=(wrap.left, wrap.right, wrap.bottom, wrap.margin_left,
                            wrap.margin_right, wrap.spacing_a, wrap.spacing_b, wrap.flag_a,
                            wrap.flag_b, wrap.flag_c))
        replay[:] = list(returns)
        assert n.vertrix_text_wrap(c.byref(calls), c.byref(services), FRAME, c.byref(wrap)), case
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log),
                                         [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2])
        assert not replay and pool.same(), (case, pool.diff())
        lines = bytes(cpu.mem_read(obj + 0x161, 1))[0]
        totals[min(lines, 6)] = totals.get(min(lines, 6), 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4b25b0': args.cases},
              'lines': {str(k): v for k, v in sorted(totals.items())},
              'scope': 'The routine executes completely in the original with the string runtime '
                       'and the font measure stubbed and logged (the string pointers and widths '
                       'mirrored for the native; the frame word above the width local is also '
                       'mirrored); every call with its registers, the stored arguments, the line '
                       'counts, starts and lengths compare.'}
    (args.build_dir / 'text-wrap-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
