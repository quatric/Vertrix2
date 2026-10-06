"""Compare the original game screen decor builder 0x46b810 with the native recovery."""
import ctypes as c
import struct

from oracle_screen import run_screen

U = c.c_uint32
CALLEES = {0x471100: 2, 0x4178d0: 0, 0x4126f0: 0, 0x4123d0: 0, 0x4ca000: 0, 0x4b6350: 0,
           0x4adf20: 5, 0x4b65d0: 3, 0x4b5e70: 0}
RANGES = ((0x4f888a, 0x4f8ce0 - 0x4f888a), (0x4fbf28, 0xc0), (0x5466c4, 4), (0x5345d4, 0x50),
          (0x4f9c07, 4))


def generate(rng, pool, cpu):
    mode = rng.getrandbits(32)
    selector = rng.choice([0xffffffff, 0xffffffff, 0x20, 0x21, 0x22, rng.getrandbits(32)])
    cpu.mem_write(0x532a68, struct.pack('<I', rng.randrange(0, 19)))
    cpu.mem_write(0x532a6c, struct.pack('<I', rng.randrange(0, 19)))
    return {'eax': mode, 'edx': selector}, (), (mode, selector)


run_screen('hud-builder', 0x46b810, ['hud_builder.c'], 'vertrix_hud_build', [U, U], U, CALLEES,
           generate,
           'The original executes completely with its callees stubbed and logged (0x471100 as a '
           'stdcall routine with two stack arguments); the layout tables, the frame table and the '
           'name table hold random data, the selected characters are small. The slot test '
           '0x4178d0 answers -1 or 0, the name box test 0x4126f0 one or zero. Every call with its '
           'registers (stale ebx and ecx included), the returned eax and every pool object '
           'compare.',
           globals_ranges=RANGES, handle_returns=(0x4b6350,),
           choices={0x4178d0: [0xffffffff, 0xffffffff, 0, 5], 0x4126f0: [1, 1, 0]})
