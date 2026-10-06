"""Compare the original options screen builder 0x461fc0 with the native recovery."""
import ctypes as c
import struct

from original import STACK
from oracle_screen import run_screen

U = c.c_uint32
FRAME = STACK - 4
CALLEES = {0x4ca070: 0, 0x4ca280: 0, 0x4cdfb0: 3, 0x415ed0: 0, 0x4ca370: 0, 0x460a40: 5,
           0x460c50: 11, 0x460ad0: 5, 0x4ac4f0: 0, 0x460ed0: 12, 0x460fa0: 17, 0x460b60: 12,
           0x4ca000: 0, 0x4b5c60: 0, 0x4abd70: 0, 0x4ac8f0: 0, 0x4ac7b0: 0, 0x4b5e70: 0,
           0x4cda10: 0}
RANGES = ((0x4f9bf5, 12), (0x4f7b8e, 4), (0x532b98, 0x28), (0x558c7c, 4))
SELECTION = U(0xdeadbeef)


def string_effect(cpu, rng, eax, edx, ebx, ecx, stack):
    value = rng.getrandbits(32)
    cpu.mem_write(eax, struct.pack('<I', value))
    return value


def generate(rng, pool, cpu):
    cpu.mem_write(0x558c7c, struct.pack('<I', rng.choice(pool.handles)))
    stale = struct.unpack('<H', bytes(cpu.mem_read(FRAME - 0x32, 2)))[0]
    SELECTION.value = 0xdeadbeef
    cpu.mem_write(0x532a48, struct.pack('<I', 0x1234567))
    return {}, (), (FRAME, stale, c.byref(SELECTION))


def post(cpu, args):
    assert SELECTION.value == struct.unpack('<I', bytes(cpu.mem_read(0x532a48, 4)))[0]


run_screen('options-screen', 0x461fc0, ['options_screen.c'], 'vertrix_options_build',
           [U, U, c.POINTER(U)], U, CALLEES, generate,
           'The original executes completely with its callees stubbed and logged (0x4cdfb0 as a '
           'cdecl call; 0x4ca280 and 0x4ca370 store a random dword through their local pointer and '
           'the native reads it back); the settings, the glyph dwords and the screen object '
           'hold random data. Every call with its registers and stack arguments (up to 17), the '
           'stored dword 0x532a48 and every pool object compare.',
           globals_ranges=RANGES, effects={0x4ca280: string_effect, 0x4ca370: string_effect},
           handle_returns=(0x4b5c60, 0x4abd70), pool_size=0x200, post=post, compare=False)
