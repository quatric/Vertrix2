"""Compare the complete original pitch curve with the native recovery."""
import ctypes as c, random
from original import Original
import verify_common_a as common


def main():
    args = common.parse(__doc__)
    n = common.build(args, 'pitch-curve', 'pitch_curve.c')
    n.vertrix_pitch_curve.argtypes = [c.c_uint32]
    n.vertrix_pitch_curve.restype = c.c_int32
    original = Original(args.executable)
    rng = random.Random(0x410150)
    totals = {'curve': 0}
    for case in range(args.cases):
rate = rng.choice([
    rng.randrange(0, 200000), rng.getrandbits(32), rng.randrange(0, 70000), 8363,
    rng.randrange(8000, 9000), rng.getrandbits(18)
]) want =
    c.c_int32(original.call(0x410150, eax = rate)).value assert n.vertrix_pitch_curve(rate) == want,
   (case, rate)totals['curve'] +=
   1 common.report(
       args, 'pitch-curve', totals,
       'Complete 410150 runs unmodified in the original over rates from zero to 32-bit ' 'extremes (including shift wrap and the halving loop); results compare.')

       if __name__
   == '__main__' : main()
