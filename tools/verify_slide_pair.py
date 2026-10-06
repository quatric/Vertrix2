"""Compare the original slide actor pair 0x4711a0 with the native recovery."""
import ctypes as c

from oracle_screen import run_screen

U = c.c_uint32
CALLEES = {0x4ca000: 0, 0x4abd70: 0, 0x4adf20: 5, 0x4ac490: 0, 0x4ac7b0: 0, 0x4ac8d0: 0,
           0x4ac710: 0, 0x4ac8f0: 0, 0x4b5e70: 0}


def generate(rng, pool, cpu):
    value = rng.getrandbits(32)
    return {'eax': value}, (), (value,)


run_screen('slide-pair', 0x4711a0, ['slide_pair.c'], 'vertrix_slide_pair', [U], c.c_int, CALLEES,
           generate,
           'The original executes completely with its callees stubbed and logged; the globals '
           '0x4f8a48..0x4f8a56 hold random data. Every call with the registers the previous call '
           'left and every pool object compare. The original returns the saved exception chain '
           'head, which is not modeled.',
           wrappers=(0x4abd70,), globals_ranges=((0x4f8a48, 0x10),), compare=False)
