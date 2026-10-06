"""Compare the original column search 0x4270a0 with the native recovery."""
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
FRAME_SIZE = 0x190
SCORE = 0x434ee0
CHECKED = [(FRAME - 0x8c, 0x41), (FRAME - 0x48, 0x14), (FRAME - 0x10, 2)]


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


class Search(c.Structure):
    _fields_ = [(name, U) for name in ('object', 'b', 'c', 'a', 'kind_out', 'column_out',
                                       'pressure', 'start', 'row', 'level')]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'ai-search', ['ai_search.c', 'ai_features.c', 'call_glue.c',
                                            'actor_storage.c'])
    n.vertrix_ai_search.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, c.POINTER(Search),
                                    c.POINTER(U)]
    n.vertrix_ai_search.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4270a0)
    pool = Pool(cpu, 3, SIZE)
    frame = c.create_string_buffer(FRAME_SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == FRAME - FRAME_SIZE:
            storage[0], size[0] = c.addressof(frame), FRAME_SIZE
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, outs, native_log, replay = [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        word = rng.choice([0, 1, 5, 40, 255, 256, 300, rng.randrange(0, 0x10000)])
        cpu.mem_write(stack[0], struct.pack('<H', word))
        outs.append(word)
        returns.append(1 if rng.random() < 0.7 else rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    stubs.add(SCORE, 1)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx, s.stack))
        s.out_value = outs.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {'short': 0, 'found': 0, 'none': 0}
    for case in range(args.cases):
        start, row = rng.randrange(0, 6), rng.randrange(0, 13)
        level = rng.choice([0, 1, 2, 3, 4, 5, 9])
        obj, kind_out, column_out = pool.handles

        def patch(handle, data):
            if handle == obj:
                for i in range(0x41):
                    data[0x184 + i] = rng.choice([0xff, 0xff, rng.randrange(0, 8)])

        pool.fill(rng, patch)
        blob = rng.randbytes(FRAME_SIZE)
        cpu.mem_write(FRAME - FRAME_SIZE, blob)
        c.memmove(frame, blob, FRAME_SIZE)
        stubs.log.clear()
        returns.clear()
        outs.clear()
        native_log.clear()
        search = Search(obj, rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32),
                        kind_out, column_out, rng.getrandbits(32), start, row, level)
        want = original.call(0x4270a0, eax=obj, edx=search.b, ebx=search.c, ecx=search.a,
                             args=(kind_out, column_out, search.pressure, start, row, level)) & 0xffffffff
        replay[:] = list(returns)
        result = U()
        assert n.vertrix_ai_search(c.byref(calls), c.byref(services), FRAME, c.byref(search),
                                   c.byref(result)), case
        assert result.value == want, (case, result.value, want)
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log))
        assert not replay and pool.same(), (case, pool.diff())
        for address, length in CHECKED:
            offset = address - (FRAME - FRAME_SIZE)
            assert frame.raw[offset:offset + length] == bytes(cpu.mem_read(address, length)), \
                (case, hex(address))
        if level <= 2:
            totals['short'] += 1
        elif want:
            totals['found'] += 1
        else:
            totals['none'] += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4270a0': totals},
              'scope': 'The routine executes completely in the original with 0x434ee0 stubbed and '
                       'logged (storing its score word through its stack pointer, mirrored for the '
                       'native; 0x4261b0 and the fill run unstubbed); the returned eax, the '
                       'selected column and rotation, every call with its registers and the '
                       'copied board, the reach, best and rotation frame locals compare.'}
    (args.build_dir / 'ai-search-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
