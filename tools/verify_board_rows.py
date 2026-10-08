"""Compare the original row dealing routines 0x431780 and 0x431930 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX

U = c.c_uint32
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Allocate = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
Range = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_void_p)
Destroy = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
SIZE = 0xd00
GRID, COMPANION = 0x220, 0x87c
PATTERN, PERIOD = 0x4f9ad8, 0x4f9ad0
ROWS = ((0x431780, 'first', 0x9e8), (0x431930, 'second', 0xa2c))
VTABLE, VSTUB = 0x80f000, 0x80f100


class Table(c.Structure):
    _fields_ = [('pattern', c.c_char_p), ('pattern_size', c.c_size_t), ('period_steps', c.c_uint8)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', Draw), ('range', Range),
                ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'board-rows',
              ['board_conversions.c', 'block_factory.c', 'call_glue.c', 'board_markers.c', 'board.c',
               'board_cells.c', 'actor_storage.c', 'actor_fields.c', 'fixed_point.c',
               'board_actions.c', 'random.c'])
    for name in ('first', 'second'):
        function = getattr(n, 'vertrix_board_deal_%s_row' % name)
        function.argtypes = [c.c_void_p, c.c_size_t, c.c_int32, c.c_int32, c.POINTER(Table),
                             c.POINTER(Services), Destroy, c.c_void_p, c.POINTER(U)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4316c0)
    pool = Pool(cpu, 8, SIZE)
    board = pool.handles[0]
    targets = pool.handles[1:]
    draws, allocations, replay = [], [], {'draws': [], 'allocs': []}
    events, native_events = [], []
    cpu.mem_write(VSTUB, b'\xc3')
    cpu.mem_write(VTABLE, struct.pack('<I', VSTUB))
    cpu.hook_add(UC_HOOK_CODE, lambda cpu, a, s, x: events.append(
        (cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX))), begin=VSTUB, end=VSTUB)

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            handle = targets[len(allocations) % len(targets)]
            allocations.append(handle)
            return handle
        draws.append(rng.randrange(edx & 0xffff))
        return draws[-1]

    stubs = Stubs(cpu, handler)
    stubs.add(0x4ca000)
    stubs.add(0x4826c0)

    @Draw
    def draw(divisor, context):
        value = replay['draws'].pop(0)
        assert value < divisor
        return value

    @Allocate
    def allocate(size, context):
        return replay['allocs'].pop(0)

    @Range
    def table_range(index, lo, hi, context):
        lo[0] = struct.unpack('<I', bytes(cpu.mem_read(0x53bcd0 + 8 * index, 4)))[0]
        hi[0] = struct.unpack('<I', bytes(cpu.mem_read(0x53bcd4 + 8 * index, 4)))[0]
        return 1

    @Destroy
    def destroy(handle, flag, context):
        native_events.append((handle, flag))

    services = Services(pool.resolve, allocate, draw, table_range, None)
    totals = {}
    for case in range(args.cases):
        address, name, collection = ROWS[case % 2]
        values = collection - 0xe if name == 'first' else collection - 0x10

        def patch(handle, data):
            struct.pack_into('<I', data, 0x158, VTABLE)
            if handle == board:
                density = rng.choice([0.0, 0.5, 1.0])
                for grid in (GRID, COMPANION):
                    for i in range(65):
                        struct.pack_into('<I', data, grid + 4 * i,
                                         rng.choice(targets) if rng.random() < density else 0)
                for i in range(13):
                    # bytes the pattern leaves alone keep their value: make them valid kinds
                    data[values + i] = rng.choice([0, 1, 2, 3, 4, 5, 0xff])
                    struct.pack_into('<I', data, collection + 4 * i,
                                     rng.choice(targets) if rng.random() < 0.6 else 0)
            else:
                data[0x15c] = rng.choice([0, 1, 2, 3, 4, 5, 6, 0xff])
        pool.fill(rng, patch)
        pattern = bytes(rng.choice([0, 1, 1, 2, 3]) for _ in range(13 * 12))
        period = rng.randrange(1, 9)
        cpu.mem_write(PATTERN, pattern)
        cpu.mem_write(PERIOD, bytes([period]))
        draws.clear()
        allocations.clear()
        events.clear()
        native_events.clear()
        a = rng.randrange(0, 6)
        b = rng.choice([0, 0, 0, 1, -1, -2])
        result = original.call(address, eax=board, edx=a, ebx=b & 0xffffffff) & 0xff
        replay['draws'] = list(draws)
        replay['allocs'] = list(allocations)
        dealt = U()
        function = getattr(n, 'vertrix_board_deal_%s_row' % name)
        table = Table(pattern, len(pattern), period)
        assert function(pool.buffers[board], SIZE, a, b, c.byref(table), c.byref(services),
                        destroy, None, c.byref(dealt)), case
        assert dealt.value == result, (case, dealt.value, result)
        assert events == native_events, case
        assert pool.same(), (case, pool.diff())
        assert not replay['draws'] and not replay['allocs'], case
        key = '%s_%s' % (name, 'dealt' if result else 'skipped')
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 431780 and 431930 execute in the original (operator new 4ca000 and the draw '
                       '4826c0 stubbed and replayed, the destructor calls logged); the result, '
                       'the destroy events, the board and every object compare.'}
    (args.build_dir / 'board-rows-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
