"""Compare complete original block creation routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Allocate = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
Range = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_void_p)
SIZE = 0x400


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', Allocate), ('draw', Draw), ('range', Range),
                ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'block-factory',
              ['block_factory.c', 'actor_storage.c', 'actor_fields.c', 'board_cells.c'])
    S = c.POINTER(Services)
    P, SZ, UP = c.c_void_p, c.c_size_t, c.POINTER(U)
    n.vertrix_actor_attach_resource.argtypes = [P, SZ, U]
    n.vertrix_actor_initialize.argtypes = [P, SZ, c.c_uint16, c.c_uint16, c.c_uint16, U, U, U, U]
    n.vertrix_block_construct.argtypes = [P, SZ]
    n.vertrix_block_create.argtypes = [c.c_uint8, U, U, U, S, UP]
    n.vertrix_block_spawn.argtypes = [P, SZ, U, S, UP]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x430800)
    pool = Pool(cpu, 6, SIZE)
    board, fresh_objects = pool.handles[0], pool.handles[1:]
    draws, allocations = [], []
    replay = {'draws': [], 'allocs': []}

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            handle = fresh_objects[len(allocations) % len(fresh_objects)]
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
        assert size == 0x160
        return replay['allocs'].pop(0)

    @Range
    def table_range(index, lo, hi, context):
        lo[0] = struct.unpack('<I', bytes(cpu.mem_read((0x53bcd0 + 8 * index) & 0xffffffff, 4)))[0]
        hi[0] = struct.unpack('<I', bytes(cpu.mem_read((0x53bcd4 + 8 * index) & 0xffffffff, 4)))[0]
        return 1

    services = Services(pool.resolve, allocate, draw, table_range, None)
    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def fresh():
        def patch(handle, data):
            if handle == board:
                struct.pack_into('<H', data, 0xe, rng.getrandbits(16))
                struct.pack_into('<H', data, 0x16, rng.getrandbits(16))
        pool.fill(rng, patch)
        draws.clear()
        allocations.clear()

    def begin():
        replay['draws'] = list(draws)
        replay['allocs'] = list(allocations)

    for case in range(args.cases):
# 4ac8d0, 4adf20 and 42bb00 on one fresh object
        fresh()
        resource = rng.getrandbits(32)
        original.call(0x4ac8d0, eax=fresh_objects[0], edx=resource)
        assert n.vertrix_actor_attach_resource(pool.buffers[fresh_objects[0]], SIZE, resource)
        assert pool.same(), (case, pool.diff())
        count('0x4ac8d0')
        fresh()
        words = [rng.getrandbits(16) for _ in range(3)]
        dwords = [rng.getrandbits(32) for _ in range(4)]
        original.call(0x4adf20, eax=fresh_objects[0], edx=words[0], ebx=words[1], ecx=words[2],
                      args=(dwords[0], dwords[1], dwords[2], dwords[3], 0))
        assert n.vertrix_actor_initialize(pool.buffers[fresh_objects[0]], SIZE, *words, *dwords)
        assert pool.same(), (case, pool.diff())
        count('0x4adf20')
        fresh()
        original.call(0x42bb00, eax=fresh_objects[0])
        assert n.vertrix_block_construct(pool.buffers[fresh_objects[0]], SIZE)
        assert pool.same(), (case, pool.diff())
        count('0x42bb00')
# 42bbd0 : create
        fresh()
        kind = rng.choice([0, 1, 5, 12, 18, 0x7f, 0x80, 0xff, rng.getrandbits(8)])
        d0, steps, handle_token = rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32)
        result = original.call(0x42bbd0, eax=kind, edx=d0, ebx=steps, ecx=handle_token)
        begin()
        out = U()
        assert n.vertrix_block_create(kind, d0, steps, handle_token, c.byref(services),
                                      c.byref(out))
        assert out.value == result, (case, hex(out.value), hex(result))
        assert pool.same(), (case, pool.diff())
        count('0x42bbd0')
# 430800 : spawn on the board
        fresh()
        index = rng.randrange(0, 20)
        lo = struct.unpack('<I', bytes(cpu.mem_read(0x53bcd0 + 8 * index, 4)))[0]
        hi = struct.unpack('<I', bytes(cpu.mem_read(0x53bcd4 + 8 * index, 4)))[0]
        if (hi - lo + 1) & 0xffff == 0:
            continue
        result = original.call(0x430800, eax=board, edx=index)
        begin()
        out = U()
        assert n.vertrix_block_spawn(pool.buffers[board], SIZE, index, c.byref(services),
                                     c.byref(out))
        assert out.value == result, (case, hex(out.value), hex(result))
        assert pool.same(), (case, pool.diff())
        assert not replay['draws'] and not replay['allocs']
        count('0x430800')
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 4ac8d0, 4adf20, 42bb00, 42bbd0 and 430800 execute in the original '
                       '(operator new 4ca000 and the random draw 4826c0 stubbed and replayed, '
                       'the recovered 4abd70, 4ac490, 4ac7b0 and 42ff10 executed); returned '
                       'handles, whole objects and the draws consumed compare.'}
    (args.build_dir / 'block-factory-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
