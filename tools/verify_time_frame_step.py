"""Compare the complete original frame-delta limiter 0x4b7d10 with the native recovery."""
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
NOW_GLOBAL = 0x5bd838
PREV_GLOBAL = 0x5bd844
CAPPED_GLOBAL = 0x5bd834

Clock = c.CFUNCTYPE(U, c.c_void_p)


def main():
    args = common.parse(__doc__, default_cases=1024)
    n = build(args.build_dir, 'time-frame-step', ['timing.c', 'random.c'])
    n.vertrix_time_frame_step.argtypes = [Clock, c.c_void_p, c.POINTER(U), c.POINTER(U),
                                          c.POINTER(U)]
    n.vertrix_time_frame_step.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4b7d10)
    cpu.mem_write(IAT_SLOT, struct.pack('<I', STUB))
    totals = {}

    def on_tick(uc):
        cpu.mem_write(common.DATA, struct.pack('<I', tick[0]))

    common.stub(cpu, STUB, on_tick)
    for case in range(args.cases):
        tick = [rng.getrandbits(32)]
        prev = rng.choice([rng.getrandbits(32), (tick[0] - rng.randrange(0, 70000)) & 0xffffffff,
                           (tick[0] + rng.randrange(0, 100)) & 0xffffffff])
        cpu.mem_write(PREV_GLOBAL, struct.pack('<I', prev))
        cpu.mem_write(NOW_GLOBAL, struct.pack('<I', rng.getrandbits(32)))
        cpu.mem_write(CAPPED_GLOBAL, struct.pack('<I', rng.getrandbits(32)))
        now, previous, capped = U(), U(prev), U()
        expect = original.call(0x4b7d10) & 0xffffffff
        want = struct.unpack('<III', cpu.mem_read(NOW_GLOBAL, 4) + cpu.mem_read(CAPPED_GLOBAL, 4)
                             + cpu.mem_read(PREV_GLOBAL, 4))

        @Clock
        def clock(context):
            return tick[0]

        got = n.vertrix_time_frame_step(clock, None, c.byref(now), c.byref(previous),
                                        c.byref(capped))
        assert got == expect, (case, hex(got), hex(expect))
        assert (now.value, capped.value, previous.value) == (want[0], want[1], want[2]), \
            (case, now.value, capped.value, previous.value, want)
        totals['0x4b7d10'] = totals.get('0x4b7d10', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete original 0x4b7d10 executions with the timeGetTime import '
                       'redirected to a scripted stub (normal, wrap-around and saturation '
                       'cases); the returned delta and all three globals compare.'}
    (args.build_dir / 'time-frame-step-verification.json').write_text(json.dumps(report, indent=2)
                                                                       + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
