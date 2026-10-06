"""Compare the original high score insertion 0x4177b0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Stubs, build

U = c.c_uint32
SCORES = 0x533294


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third')]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'score-table', ['score_table.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_high_score_insert.argtypes = [c.POINTER(Calls), c.POINTER(U * 5), U, U]
    n.vertrix_high_score_insert.restype = U
    n.vertrix_quad_average.argtypes = [c.POINTER(Calls), c.c_uint8, c.c_uint8, U, c.POINTER(U),
                                       c.POINTER(U)]
    n.vertrix_quad_average.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4177b0)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x417970:
            returns.append(rng.choice([0xffffffff, 0xffffffff, rng.randrange(0, 5000)]))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address in (0x4ca310, 0x4ca370, 0x417970):
        stubs.add(address, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    ranks = {}
    for case in range(args.cases):
        scores = sorted((rng.randrange(0, 50) * 100 for _ in range(5)), reverse=True)
        score = rng.choice([rng.randrange(0, 5000), scores[rng.randrange(5)],
                            scores[rng.randrange(5)] + 1])
        ebx = rng.getrandbits(32)
        cpu.mem_write(SCORES, struct.pack('<5I', *scores))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x4177b0, eax=score, ebx=ebx) & 0xffffffff
        replay[:] = list(returns)
        table = (U * 5)(*scores)
        got = n.vertrix_high_score_insert(c.byref(calls), c.byref(table), score, ebx)
        assert got == result, (case, hex(got), hex(result))
        assert list(table) == list(struct.unpack('<5I', bytes(cpu.mem_read(SCORES, 20)))), case
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay, case
        ranks[got & 0xff] = ranks.get(got & 0xff, 0) + 1
    quads = 0
    for case in range(args.cases):
        a, index = rng.randrange(256), rng.randrange(256)
        outputs = 0x808500
        cpu.mem_write(outputs, bytes(8))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x4179d0, eax=a, edx=index, ebx=outputs, ecx=outputs + 4) & 0xffffffff
        replay[:] = list(returns)
        total, average = U(7), U(7)
        got = n.vertrix_quad_average(c.byref(calls), a, index, outputs, c.byref(total),
                                     c.byref(average))
        assert got == result, ('quad', case, hex(got), hex(result))
        assert (total.value, average.value) == struct.unpack('<II', bytes(cpu.mem_read(outputs, 8))), case
        assert native_log == stubs.log and not replay, ('quad', case)
        quads += 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4177b0': args.cases,
                                                                    '0x4179d0': quads},
              'ranks_seen': {hex(key): value for key, value in sorted(ranks.items())},
              'scope': 'The original executes completely with 0x4ca310 and 0x4ca370 stubbed and '
                       'logged; every call, the returned eax and the score table compare.'}
    (args.build_dir / 'score-table-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
