"""Compare complete original generic object field routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U, I = c.c_uint32, c.c_int32
SIZE = 0x400
Read = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint, c.POINTER(c.c_uint32), c.c_void_p)


class RangeCopy(c.Structure):
    _fields_ = [('copied', U), ('flag', U), ('wanted', U), ('available', U)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-dwords', ['object_dwords.c', 'actor_storage.c'])
    P, SZ, UP = c.c_void_p, c.c_size_t, c.POINTER(U)
    n.vertrix_object_dword.argtypes = [P, SZ, SZ, UP]
    n.vertrix_object_set_dword.argtypes = [P, SZ, SZ, U]
    n.vertrix_object_set_pair.argtypes = [P, SZ, SZ, SZ, U, U]
    n.vertrix_list_empty.argtypes = [P, SZ, UP]
    n.vertrix_list_item.argtypes = [P, SZ, U, Read, P, UP]
    n.vertrix_table_item.argtypes = [P, SZ, SZ, U, Read, P, UP]
    n.vertrix_object_zero_dwords.argtypes = [P, SZ, U]
    for name in ('arm_30', 'clear_208', 'restart_range'):
        getattr(n, 'vertrix_object_' + name).argtypes = [P, SZ]
    n.vertrix_range_done.argtypes = [P, SZ, UP]
    n.vertrix_object_set_indexed_word.argtypes = [P, SZ, U, c.c_uint16]
    n.vertrix_range_start.argtypes = [P, SZ, Read, P]
    n.vertrix_range_seek.argtypes = [P, SZ, U, Read, P]
    n.vertrix_range_block_second.argtypes = [P, SZ, Read, P, UP]
    n.vertrix_range_span.argtypes = [P, SZ, Read, P, UP]
    n.vertrix_timer_reset.argtypes = [P, SZ, c.c_uint8]
    n.vertrix_object_set_word.argtypes = [P, SZ, SZ, c.c_uint16]
    n.vertrix_object_word.argtypes = [P, SZ, SZ, UP]
    n.vertrix_timer_running.argtypes = [P, SZ, UP]
    n.vertrix_object_set_four_words.argtypes = [P, SZ] + [c.c_uint16] * 4
    n.vertrix_object_reset_triple.argtypes = [P, SZ, U, U]
    n.vertrix_object_status_active.argtypes = [P, SZ, UP]
    n.vertrix_range_copy.argtypes = [P, SZ, P, SZ, U, U, Read, P, c.POINTER(RangeCopy)]
    n.vertrix_range_copy.restype = U
    n.vertrix_range_save_copy.argtypes = [P, SZ, P, SZ, Read, P]
    n.vertrix_list_node_alloc.argtypes = [P, SZ, U, c.CFUNCTYPE(U, U, c.c_void_p), Resolve, P]
    n.vertrix_list_node_alloc.restype = U
    n.vertrix_resource_table_entry.argtypes = [U, U, Read, P]
    n.vertrix_resource_table_entry.restype = U
    n.vertrix_actor_refresh_count.argtypes = [P, SZ, Read, P]
    n.vertrix_scaled_round.argtypes = [I, I, c.POINTER(I)]
    n.vertrix_object_release_links.argtypes = [P, SZ, Resolve, P]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x47e9a0)
    pool = Pool(cpu, 4, SIZE)
    obj, other = pool.handles[0], pool.handles[1]
    totals = {}

    @Read
    def read(address, width, value, context):
        value[0] = int.from_bytes(bytes(cpu.mem_read(address, width)), 'little')
        return 1

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def fresh():
        def patch(handle, data):
            if handle != obj:
                return
            struct.pack_into('<I', data, 4, other + 4 * rng.randrange(0, 4))
            struct.pack_into('<I', data, 8, rng.choice([0, 1, 2, 5, rng.getrandbits(32)]))
            struct.pack_into('<I', data, 0, other + 4 * rng.randrange(0, 4))
            struct.pack_into('<I', data, 0x18, other + 4 * rng.randrange(0, 4))
            struct.pack_into('<I', data, 0x1c, other + 4 * rng.randrange(0, 4))
            struct.pack_into('<I', data, 0x1b8, rng.choice([other, obj]))
            struct.pack_into('<I', data, 0x30, rng.choice([0, 1, rng.getrandbits(32)]))
            struct.pack_into('<I', data, 0x90, rng.choice([0, 0xe001, 0xe002, 7,
                                                           rng.getrandbits(32)]))
            struct.pack_into('<I', data, 0x174, rng.choice([0, 1, rng.getrandbits(32)]))
            struct.pack_into('<H', data, 0x17a, rng.choice([0, 5, rng.getrandbits(16)]))
            struct.pack_into('<H', data, 0x17c, rng.choice([0, 5, rng.getrandbits(16)]))
        pool.fill(rng, patch)
#the pool object lists must hold small counts for the list routines
        return

    def buf():
        return pool.buffers[obj]

    def mutate(address, name, native, expect_eax=None, **registers):
        fresh()
        registers.setdefault('eax', obj)
        result = original.call(address, **registers)
        assert native(), (name, 'rejected')
        assert pool.same(), (name, pool.diff())
        if expect_eax is not None:
            assert result == expect_eax, (name, result)
        count(name)

    def query(address, name, native, mask=0xffffffff, **registers):
        fresh()
        registers.setdefault('eax', obj)
        expect = original.call(address, **registers) & mask
        out = U()
        assert native(c.byref(out)), name
        assert out.value & mask == expect, (name, out.value, expect)
        count(name)

    for case in range(args.cases):
        v, w = rng.getrandbits(32), rng.getrandbits(32)
        words = [rng.getrandbits(16) for _ in range(4)]
        for address, offset in ((0x47e9a0, 0x1c4), (0x480070, 0x4c), (0x4877e0, 0x14),
                                (0x48a2e0, 8), (0x48aa80, 4), (0x4b4500, 0x174), (0x4d5350, 0x98)):
            query(address, hex(address), lambda o: n.vertrix_object_dword(buf(), SIZE, offset, o))
        for address, offset in ((0x47ed60, 0x20), (0x47ed70, 0x24), (0x47ed80, 0x28),
                                (0x47ed90, 0x2c), (0x47f8e0, 0x18)):
            mutate(address, hex(address), lambda: n.vertrix_object_set_dword(buf(), SIZE, offset, v),
                   edx=v)
        for address, offset, token in ((0x481b20, 0x28, 0x516b14), (0x484410, 4, 0x516c84)):
            mutate(address, hex(address),
                   lambda: n.vertrix_object_set_dword(buf(), SIZE, offset, token))
        for address, first, second in ((0x48abe0, 0, 4), (0x4b35b0, 0x170, 0x174),
                                       (0x4b3c30, 0x184, 0x188), (0x4b4fa0, 0x188, 0x18c)):
            mutate(address, hex(address),
                   lambda: n.vertrix_object_set_pair(buf(), SIZE, first, second, v, w),
                   edx=v, ebx=w)
        for address in (0x4879e0, 0x48d5f0):
            query(address, hex(address), lambda o: n.vertrix_list_empty(buf(), SIZE, o), 0xff)
        index = rng.randrange(0, 8)
        for address in (0x487a20, 0x48d630, 0x4b6fa0, 0x4b79c0):
            query(address, hex(address),
                  lambda o: n.vertrix_list_item(buf(), SIZE, index, read, None, o), edx=index)
        index = rng.randrange(0, 4)
        for address, offset in ((0x488030, 0x18), (0x488040, 0x1c)):
            query(address, hex(address),
                  lambda o: n.vertrix_table_item(buf(), SIZE, offset, index, read, None, o),
                  edx=index)
        amount = rng.randrange(0, 40)
        mutate(0x4b2290, '0x4b2290', lambda: n.vertrix_object_zero_dwords(buf(), SIZE, amount),
               edx=amount)
        mutate(0x47ecf0, '0x47ecf0', lambda: n.vertrix_object_arm_30(buf(), SIZE), expect_eax=0)
        mutate(0x482050, '0x482050', lambda: n.vertrix_object_clear_208(buf(), SIZE))
        mutate(0x482540, '0x482540', lambda: n.vertrix_object_restart_range(buf(), SIZE))
        query(0x48a910, '0x48a910', lambda o: n.vertrix_range_done(buf(), SIZE, o), 0xff)
        mutate(0x48abf0, '0x48abf0',
               lambda: n.vertrix_object_set_indexed_word(buf(), SIZE, v, words[0]), edx=v,
               ebx=words[0])
        mutate(0x48a8a0, '0x48a8a0', lambda: n.vertrix_range_start(buf(), SIZE, read, None))
        mutate(0x48aaf0, '0x48aaf0', lambda: n.vertrix_range_seek(buf(), SIZE, v, read, None),
               edx=v)
        query(0x48aa70, '0x48aa70',
              lambda o: n.vertrix_range_block_second(buf(), SIZE, read, None, o))
        fresh()
        expect = original.call(0x48aad0, eax=obj)
        out = U()
        assert n.vertrix_range_span(buf(), SIZE, read, None, c.byref(out)) and out.value == expect
        assert struct.unpack('<I', bytes(cpu.mem_read(0x5bb250, 4)))[0] == out.value, case
        count('0x48aad0')
        byte = rng.getrandbits(8)
        mutate(0x4b6530, '0x4b6530', lambda: n.vertrix_timer_reset(buf(), SIZE, byte), edx=byte)
        mutate(0x4b6540, '0x4b6540',
               lambda: n.vertrix_object_set_word(buf(), SIZE, 0x17a, words[0]), edx=words[0])
        mutate(0x4b6550, '0x4b6550',
               lambda: n.vertrix_object_set_word(buf(), SIZE, 0x17c, words[0]), edx=words[0])
        for address, offset in ((0x4b6590, 0x17c), (0x4b65a0, 0x17a)):
            query(address, hex(address), lambda o: n.vertrix_object_word(buf(), SIZE, offset, o),
                  0xffff)
        mutate(0x4b65b0, '0x4b65b0', lambda: n.vertrix_object_set_dword(buf(), SIZE, 0x174, 1))
        query(0x4b6560, '0x4b6560', lambda o: n.vertrix_timer_running(buf(), SIZE, o), 0xff)
        mutate(0x4b6690, '0x4b6690', lambda: n.vertrix_object_set_four_words(buf(), SIZE, *words),
               edx=words[0], ebx=words[1], ecx=words[2], args=(words[3],))
        mutate(0x4d2700, '0x4d2700', lambda: n.vertrix_object_reset_triple(buf(), SIZE, w, v),
               ebx=w, edx=v)
        query(0x4d2d70, '0x4d2d70', lambda o: n.vertrix_object_status_active(buf(), SIZE, o), 0xff)
        a = rng.choice([0, 1, -1, rng.getrandbits(31), -rng.getrandbits(31), rng.getrandbits(32) - (1 << 31)])
        b = rng.choice([1, -1, 2, 255, rng.randrange(1, 1000), rng.getrandbits(32) - (1 << 31)])
        if b != 0 and not ((255 * (2 * a + 1) + b) & 0xffffffff == 0x80000000 and (2 * b) & 0xffffffff == 0xffffffff):
            expect = original.call(0x4c5d60, ebx=a & 0xffffffff, ecx=b & 0xffffffff)
            out = I()
            if (2 * b) & 0xffffffff:
                assert n.vertrix_scaled_round(a, b, c.byref(out)), (a, b)
                assert out.value & 0xffffffff == expect, (case, a, b, out.value, expect)
                count('0x4c5d60')
        fresh()
        original.call(0x4c0990, eax=obj)
        assert n.vertrix_object_release_links(buf(), SIZE, pool.resolve, None)
        assert pool.same(), (case, pool.diff())
        count('0x4c0990')
    # 0x48a930 over manual source/dest clear of the RNG buffer. The +4/+8
    # fields are absolute pointers into the data area, not buffer offsets.
    SRC, DST, DATA = 0x807000, 0x807400, 0x807800
    r3 = random.Random(0x48a930)
    for _ in range(args.cases):
        base = r3.choice([0, 64, 128, 192])
        span = r3.choice([0, 1, 7, 64])
        a = r3.choice([0, 1, 2, 7, 0xffffffff, r3.getrandbits(32)])
        b = r3.choice([0, 1, 2, 7, 0xffffffff, r3.getrandbits(32)])
        src = bytearray(r3.getrandbits(8) for _ in range(SIZE))
        dst = bytearray(r3.getrandbits(8) for _ in range(SIZE))
        data = bytes(r3.getrandbits(8) for _ in range(256))
        struct.pack_into('<I', src, 4, DATA + base)
        struct.pack_into('<I', src, 8, DATA + base + span)
        cpu.mem_write(SRC, bytes(src))
        cpu.mem_write(DST, bytes(dst))
        cpu.mem_write(DATA, data)
        for g in (0x5bb22c, 0x5bb230, 0x5bb234, 0x5bb238):
            cpu.mem_write(g, struct.pack('<I', r3.getrandbits(32)))
        expect = original.call(0x48a930, eax=SRC, ebx=a, ecx=b, edx=DST)
        globals_after = struct.unpack('<4I', cpu.mem_read(0x5bb22c, 16))
        host_src = c.create_string_buffer(bytes(src), SIZE)
        host_dst = c.create_string_buffer(bytes(dst), SIZE)
        cursor_state = RangeCopy()
        assert n.vertrix_range_copy(host_src, SIZE, host_dst, SIZE, a, b, read, None,
                                     c.byref(cursor_state)) == expect
        assert (cursor_state.copied, cursor_state.flag, cursor_state.wanted,
                cursor_state.available) == globals_after
        assert host_src.raw == bytes(cpu.mem_read(SRC, SIZE))
        assert host_dst.raw == bytes(cpu.mem_read(DST, SIZE))
        count('0x48a930')
    # 0x4121e0 over a manual object/range/data clear of the RNG buffer.
    OSIZE, RSIZE = 0x800, 0x100
    OBJ, RANGE, DBLOCK = 0x808000, 0x808800, 0x808900
    r4 = random.Random(0x4121e0)
    for _ in range(args.cases):
        length = r4.choice([0, 1, 7, 64])
        obj = bytearray(r4.getrandbits(8) for _ in range(OSIZE))
        struct.pack_into('<I', obj, 0x5bc, r4.getrandbits(32))
        rngobj = bytearray(r4.getrandbits(8) for _ in range(RSIZE))
        struct.pack_into('<I', rngobj, 0, DBLOCK)
        blob = bytearray(r4.getrandbits(8) for _ in range(8 + length))
        struct.pack_into('<I', blob, 0, DBLOCK + 8)
        struct.pack_into('<I', blob, 4, length)
        cpu.mem_write(OBJ, bytes(obj))
        cpu.mem_write(RANGE, bytes(rngobj))
        cpu.mem_write(DBLOCK, bytes(blob))
        for g in (0x5bb22c, 0x5bb230, 0x5bb234, 0x5bb238):
            cpu.mem_write(g, struct.pack('<I', r4.getrandbits(32)))
        expect = original.call(0x4121e0, eax=OBJ, edx=RANGE)
        del expect
        host_obj = c.create_string_buffer(bytes(obj), OSIZE)
        host_range = c.create_string_buffer(bytes(rngobj), RSIZE)
        assert n.vertrix_range_save_copy(host_obj, OSIZE, host_range, RSIZE, read, None) == 1
        assert host_obj.raw == bytes(cpu.mem_read(OBJ, OSIZE)), 'save-copy object'
        assert host_range.raw == bytes(cpu.mem_read(RANGE, RSIZE)), 'save-copy range'
        count('0x4121e0')
# 0x487770 / 0x4ac4a0 over manual resources clear of the RNG buffer.
    RESOURCE, TABLE, ACTOR2 = 0x807000, 0x807100, 0x807200
    r2 = random.Random(0x487770)
    for _ in range(args.cases):
        flag = r2.choice([0, 1, 1, 2, r2.getrandbits(32)])
        index = r2.randrange(0, 16)
        table = [r2.getrandbits(32) for _ in range(16)]
        res = bytearray(0x18)
        struct.pack_into('<I', res, 8, TABLE)
        struct.pack_into('<I', res, 0x14, flag)
        cpu.mem_write(RESOURCE, bytes(res))
        cpu.mem_write(TABLE, struct.pack('<16I', *table))
        expect = original.call(0x487770, eax=RESOURCE, edx=index)
        assert n.vertrix_resource_table_entry(RESOURCE, index, read, None) == expect, (flag, index)
        count('0x487770')
        use_resource = r2.random() < 0.8
        actor = bytearray(r2.getrandbits(8) for _ in range(SIZE))
        struct.pack_into('<I', actor, 0xb0, RESOURCE if use_resource else 0)
        struct.pack_into('<I', actor, 0xb8, index)
        struct.pack_into('<I', actor, 0xd0, r2.getrandbits(32))
        cpu.mem_write(ACTOR2, bytes(actor))
        original.call(0x4ac4a0, eax=ACTOR2)
        host = c.create_string_buffer(bytes(actor), SIZE)
        assert n.vertrix_actor_refresh_count(host, SIZE, read, None) == 1
        assert bytes(cpu.mem_read(ACTOR2, SIZE)) == host.raw, (flag, index, use_resource)
        count('0x4ac4a0')
    # 0x487640 over manual objects clear of the RNG buffer. value * 4 wraps
    # (0x40000001 needs 4 bytes); values stay small so blocks fit the harness.
    # The heap (0x4e7c90) and fill (0x4eb5c0) services cannot run in the
    # oracle, so both are stubbed: the fill stub zeroes like the original.
    NOBJ, NBLOCK = 0x809000, 0x80a000
    BLOCK_STRIDE = 0x400
    Allocate = c.CFUNCTYPE(U, U, c.c_void_p)
    blocks_free = [NBLOCK + i * BLOCK_STRIDE for i in range(8)]
    n4 = random.Random(0x487640)
    host_blocks = {}
    heap_allocs, replay, fills = [], [], []

    @Allocate
    def node_allocate(size, context):
        return replay.pop(0)

    @Resolve
    def block_resolve(handle, storage, size, context):
        if handle not in host_blocks:
            return 0
        storage[0] = c.cast(host_blocks[handle], c.c_void_p)
        size[0] = BLOCK_STRIDE
        return 1

    def heap_handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4e7c90:
            handle = 0 if eax == 0 else blocks_free[len(heap_allocs) % len(blocks_free)]
            heap_allocs.append(handle)
            return handle
        if address == 0x4eb5c0:
            fills.append((eax, ebx))
            cpu.mem_write(eax, bytes(ebx))
            return None
        return None

    heap_stubs = Stubs(cpu, heap_handler)
    heap_stubs.add(0x4e7c90)
    heap_stubs.add(0x4eb5c0)

    for _ in range(args.cases):
        value = n4.choice([0, 1, 2, 7, 64, 0x40000001])
        obj = bytearray(n4.getrandbits(8) for _ in range(SIZE))
        cpu.mem_write(NOBJ, bytes(obj))
        block = blocks_free[len(heap_allocs) % len(blocks_free)]
        data = bytes(n4.getrandbits(8) for _ in range(BLOCK_STRIDE))
        cpu.mem_write(block, data)
        host_blocks[block] = c.create_string_buffer(data, BLOCK_STRIDE)
        start = len(heap_allocs)
        fills.clear()
        expect = original.call(0x487640, eax=NOBJ, edx=value)
        replay.extend(heap_allocs[start:])
        host_obj = c.create_string_buffer(bytes(obj), SIZE)
        assert n.vertrix_list_node_alloc(host_obj, SIZE, value, node_allocate, block_resolve,
                                         None) == expect
        assert not replay
        assert host_obj.raw == bytes(cpu.mem_read(NOBJ, SIZE))
        if expect:
            assert host_blocks[expect].raw == bytes(cpu.mem_read(expect, BLOCK_STRIDE))
            assert [f for f in fills] == [(expect, (value * 4) & 0xffffffff)]
        else:
            assert fills == []
        totals['0x487640'] = totals.get('0x487640', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete generic object field routines (47e9a0 through 4d5350, including '
                       'list, table, range, timer and link routines) plus 487770, 4ac4a0, 48a930, '
                       '4121e0 and 487640 execute in the original (heap and fill stubbed); whole '
                       'objects and returned values compare.'}
    (args.build_dir / 'object-dwords-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
