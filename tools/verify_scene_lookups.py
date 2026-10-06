"""Compare the original lookup routines 0x471e10 and 0x4725f0 with the native recovery."""
import ctypes as c

from oracle_screen import run_screen

U = c.c_uint32
PAIR = {0x4b5eb0: 0, 0x4123d0: 0}


def lookup_handler_note():
    return ('The original executes completely with 0x4b5eb0 and 0x4123d0 stubbed and logged '
            '(0x4b5eb0 finds nothing in a third of the cases); ')


def pair_case(rng, pool, cpu):
    eax, ebx = rng.getrandbits(32), rng.getrandbits(32)
    return {'eax': eax, 'ebx': ebx}, (), (eax, ebx)


def marker_case(rng, pool, cpu):
    ebx, ecx = rng.getrandbits(32), rng.getrandbits(32)
    return {'ebx': ebx, 'ecx': ecx}, (), (ebx, ecx)


run_screen('scene-lookup-pair', 0x471e10, ['scene_lookups.c'], 'vertrix_scene_lookup_pair',
           [U, U], U, PAIR, pair_case,
           lookup_handler_note() + 'every call with its registers and the returned eax compare.',
           leading=('calls',), lookups=(0x4b5eb0,))
run_screen('scene-clear-marker', 0x4725f0, ['scene_lookups.c'], 'vertrix_scene_clear_marker',
           [U, U], U, {0x4b5eb0: 0}, marker_case,
           lookup_handler_note() + 'every call, the returned eax and every pool object compare.',
           leading=('calls', 'services'), lookups=(0x4b5eb0,), pool_size=0x1000)
