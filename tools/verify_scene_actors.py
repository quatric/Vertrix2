"""Compare the original delay actor 0x471340 and banner actor 0x472620 with the native
recovery."""
import ctypes as c
import struct

from oracle_screen import run_screen

U = c.c_uint32
DELAY = {0x4ca000: 0, 0x4abd70: 0, 0x4adf20: 5, 0x4ac8f0: 0, 0x4ac7d0: 0, 0x4b5e70: 0}
BANNER = {0x4ca000: 0, 0x4abd70: 0, 0x4adf20: 5, 0x4ac8d0: 0, 0x4ac710: 0, 0x4ac8a0: 0,
          0x4ac7b0: 0, 0x4ac8f0: 0, 0x4b5e70: 0}


def registers(rng, pool, cpu):
    values = [rng.getrandbits(32) for _ in range(3)]
    return {'edx': values[0], 'ebx': values[1], 'ecx': values[2]}, (), tuple(values)


def delay_case(rng, pool, cpu):
    cpu.mem_write(0x532a64, struct.pack('<I', rng.randrange(0, 8)))
    return registers(rng, pool, cpu)


run_screen('delay-actor', 0x471340, ['scene_actors.c'], 'vertrix_delay_actor_spawn', [U, U, U], U,
           DELAY, delay_case,
           'The original executes completely with its callees stubbed and logged; the delay index '
           'is below eight and the table 0x53bdac holds random dwords. Every call with the '
           'caller registers, the returned eax and every pool object compare.',
           wrappers=(0x4abd70,), globals_ranges=((0x53bdac, 0x20),))
run_screen('banner-actor', 0x472620, ['scene_actors.c'], 'vertrix_banner_actor_spawn', [U, U, U],
           U, BANNER, registers,
           'The original executes completely with its callees stubbed and logged (0x4adf20 with '
           'its five stack arguments); the frame global 0x532a68 holds random data. Every call, '
           'the returned eax and every pool object compare.',
           wrappers=(0x4abd70,), globals_ranges=((0x532a68, 4),))
