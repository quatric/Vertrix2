"""Compare the complete original clock sampler 0x4b7cd0 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import build
import verify_common_a as common

U = c.c_uint32
IAT_SLOT = 0x4f172c
STUB = 0x707000
FIRST_GLOBAL = 0x5bd838
SECOND_GLOBAL = 0x5bd844

Clock = c.CFUNCTYPE(U, c.c_void_p)


def main():
    args = common.parse(__doc__, default_cases=1024)
    n = build(args.build_dir, 'time-sample', ['timing.c', 'random.c'])
    n.vertrix_time_sample.argtypes = [Clock, c.c_void_p, c.POINTER(U), c.POINTER(U)]
    n.vertrix_time_sample.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4b7cd0)
    cpu.mem_write(IAT_SLOT, struct.pack('<I', STUB))
    totals = {}

    def on_tick(uc):
        cpu.mem_write(common.DATA, struct.pack('<I', tick[0]))

    common.stub(cpu, STUB, on_tick)
    for case in range(args.cases):
        tick = [rng.getrandbits(32)]
        first, second = U(), U()
        expect = original.call(0x4b7cd0) & 0xffffffff
        want_first = struct.unpack('<I', cpu.mem_read(FIRST_GLOBAL, 4))[0]
        want_second = struct.unpack('<I', cpu.mem_read(SECOND_GLOBAL, 4))[0]

        @Clock
        def clock(context):
            return tick[0]

        got = n.vertrix_time_sample(clock, None, c.byref(first), c.byref(second))
        assert got == expect == tick[0], (case, hex(got), hex(expect))
        assert first.value == want_first == tick[0], (case, first.value, want_first)
        assert second.value == want_second == tick[0], (case, second.value, want_second)
        totals['0x4b7cd0'] = totals.get('0x4b7cd0', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete original 0x4b7cd0 executions with the timeGetTime import '
                       'redirected to a scripted stub; the returned tick and both globals '
                       'compare.'}
    (args.build_dir / 'time-sample-verification.json').write_text(json.dumps(report, indent=2)
                                                                   + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
