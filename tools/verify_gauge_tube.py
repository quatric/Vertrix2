"""Compare the native level tube (source/gauge_tube.c) with the original beads in the oracle.

The original cell handlers 0x450a10.. and companion handlers 0x450860.. run unchanged on actors
built the way the loop at 0x46dfea builds them (ids 0x17, thresholds k + 1, periods 10, 0x1b9 -
0x28 k and 500, handlers, positions 156, 269 + 15 k) next to the controller object (+0x58 flag,
+0x64 counter) in the chain 0x54671c; the native tube gets the same flag, counter and elapsed
time.  The bead pair's y, effect word, handler and visibility flag must match every frame.
"""
import argparse
import ctypes as c
from pathlib import Path
import struct
import subprocess

from original import Original

FRAMES = 1200
BEADS = (11, 9, 7, 0)


class Timer(c.Structure):
    _fields_ = [('counter', c.c_uint32), ('period', c.c_uint32)]


class Animation(c.Structure):
    _fields_ = [('timer', Timer), ('frame', c.c_uint32), ('frame_count', c.c_uint32)]


class Cell(c.Structure):
    _fields_ = [('threshold', c.c_uint32), ('source', c.c_uint32), ('phase', c.c_uint32),
                ('handler', c.c_uint32), ('descriptor', c.c_uint32), ('origin_y', c.c_int16),
                ('y', c.c_int16), ('target_y', c.c_int16), ('step_y', c.c_int16),
                ('effect', c.c_int16), ('effect_target', c.c_int16), ('effect_step', c.c_int16),
                ('delay', c.c_int32), ('delay_target', c.c_int32), ('delay_step', c.c_int32),
                ('primary', Timer), ('secondary', Timer), ('animation', Animation),
                ('resource', c.c_void_p)]


class Companion(c.Structure):
    _fields_ = [('threshold', c.c_uint32), ('source', c.c_uint32), ('active', c.c_uint32),
                ('refresh', c.c_uint32), ('handler', c.c_uint32), ('origin_y', c.c_int16),
                ('y', c.c_int16), ('target_y', c.c_int16), ('step_y', c.c_int16),
                ('refresh_index', c.c_int16), ('primary', Timer), ('secondary', Timer)]


class Tube(c.Structure):
    _fields_ = [('cell', Cell * 12), ('companion', Companion * 12), ('refresh', c.c_uint32 * 8)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'gauge-tube.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    *[str(source / name) for name in [
                        'gauge_tube.c', 'linked_alternating.c', 'linked_movement.c',
                        'block_resource.c', 'frame_resource.c', 'animation.c', 'timer.c',
                        'word_transition.c', 'dword_transition.c', 'actor_storage.c']],
                    '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_gauge_tube_update.argtypes = [c.c_void_p, c.c_uint32, c.c_uint32, c.c_uint32]
    native.vertrix_gauge_resource_lit.restype = c.c_void_p
    tube = Tube()
    native.vertrix_gauge_tube_init(c.byref(tube))

    oracle = Original(args.executable)
    cpu = oracle.cpu
    cpu.mem_map(0x900000, 0x200000)

    def w32(address, value):
        cpu.mem_write(address, struct.pack('<I', value & 0xffffffff))

    def r32(address):
        return struct.unpack('<I', bytes(cpu.mem_read(address, 4)))[0]

    def w16(address, value):
        cpu.mem_write(address, struct.pack('<H', value & 0xffff))

    def r16(address):
        return struct.unpack('<h', bytes(cpu.mem_read(address, 2)))[0]

    chain, array, controller = 0x54671C, 0x910000, 0x901000
    cells, companions = [], []
    for k in range(12):
        y = 269 + 15 * k
        cell = 0x902000 + 0x800 * k
        cells.append(cell)
        w32(cell + 4, 0x17)
        w32(cell + 0x58, k + 1)
        w32(cell + 0xc0, 10)
        w32(cell + 0xe0, 0x1b9 - 0x28 * k)
        w32(cell + 0x154, 0x450a10)
        w32(cell + 0xb0, 0x546618)
        cpu.mem_write(cell + 0x93, b'\x01')
        cpu.mem_write(cell + 0x95, b'\x04')
        for offset in (0xa, 0xe, 0x16):
            w16(cell + offset, 156 if offset == 0xe else y)
        companion = 0x920000 + 0x800 * k
        companions.append(companion)
        w32(companion + 4, 0x17)
        w32(companion + 0x58, k + 1)
        w32(companion + 0xc0, 10)
        w32(companion + 0xe0, 500)
        w32(companion + 0x154, 0x450860)
        for offset in (0xa, 0xe, 0x16):
            w16(companion + offset, 156 if offset == 0xe else y)
    w32(controller, 0x17)
    w32(controller + 0x64, 12)
    objects = [controller] + cells + companions
    for i, address in enumerate(objects):
        w32(array + 4 * i, address)
    w32(chain + 4, array)
    w32(chain + 8, len(objects))
    w16(0x533d78, 252)

    mismatches = 0
    for frame in range(FRAMES):
        counter = 12 if frame < 20 else 8 if frame < 500 else 12 if frame < 800 else 3
        flag = 1 if 500 <= frame < 600 else 0
        w32(0x5bd834, 16)
        w32(controller + 0x58, flag)
        w32(controller + 0x64, counter)
        for address in cells + companions:
            oracle.call(r32(address + 0x154), eax=address)
        native.vertrix_gauge_tube_update(c.byref(tube), flag, counter, 16)
        for k in BEADS:
            original = (r16(cells[k] + 0x48), r16(cells[k] + 0x16), r32(cells[k] + 0x154),
                        r32(cells[k] + 0x134), r32(cells[k] + 0xb0),
                        r16(companions[k] + 0x16), r32(companions[k] + 0x154),
                        r32(companions[k] + 0x134))
            cell, companion = tube.cell[k], tube.companion[k]
            lit = cell.resource == native.vertrix_gauge_resource_lit()
            ported = (cell.effect, cell.y, cell.handler, cell.source,
                      0x546618 if lit else 0x546634, companion.y, companion.handler,
                      companion.source)
            mismatches += original != ported
    print('mismatches', mismatches, 'over', FRAMES, 'frames')
    raise SystemExit(1 if mismatches else 0)


if __name__ == '__main__':
    main()
