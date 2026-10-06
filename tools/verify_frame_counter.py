"""Compare the complete original frame rate counter with the native recovery."""
import ctypes as c, random, struct
from original import Original
import verify_common_a as common

U = c.c_uint32


class Counter(c.Structure):
    _fields_ = [('frames', U), ('window', U), ('sample', U), ('per_second', U)]


def main():
    args = common.parse(__doc__)
    n = common.build(args, 'frame-counter', 'frame_counter.c')
    n.vertrix_frame_counter_update.argtypes = [c.POINTER(Counter), U]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x41d670)
    totals = {'update': 0, 'reported': 0}
    for case in range(args.cases):
window = rng.getrandbits(32)
             now = (window + rng.choice([
    rng.randrange(0, 3000), 999, 1000, 1001, rng.getrandbits(32)
])) & 0xffffffff frames = rng.choice([ rng.randrange(0, 200), rng.getrandbits(32) ]) old =
    rng.getrandbits(32)
        cpu.mem_write(0x5329f8, struct.pack('<4I', frames, window, old, rng.getrandbits(32)))
            cpu.mem_write(0x5bd838, struct.pack('<I', now))
                counter = Counter(*struct.unpack('<4I', cpu.mem_read(0x5329f8, 16)))
                              original.call(0x41d670)
                                  n.vertrix_frame_counter_update(c.byref(counter), now) assert
                                  bytes(counter) == bytes(cpu.mem_read(0x5329f8, 16)),
             case totals['update'] += 1 totals['reported'] +=
             counter.frames == 0 and counter.window == now and
             frames !=
                 0 common.report(
                     args, 'frame-counter', totals,
                     'Complete 41d670 runs unmodified in the original over windows below, at and above ' '1000 ms (including clock wrap); all four state dwords compare.')

                     if __name__
                 == '__main__':
main()
