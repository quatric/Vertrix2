"""Compare complete original slot-array release and small initialiser routines with the native
recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, build
from verify_support import VirtualStubs

U = c.c_uint32
SIZE = 0xb00
Destroy = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-slots',
              ['object_slots.c', 'actor_storage.c', 'actor_fields.c'])
    P, SZ, UP = c.c_void_p, c.c_size_t, c.POINTER(U)
    n.vertrix_object_release_slots.argtypes = [P, SZ, SZ, U, Destroy, P]
    n.vertrix_piece_release_children.argtypes = [P, SZ, c.c_int, Destroy, P]
    n.vertrix_effects_release_all.argtypes = [P, SZ, Destroy, P]
    n.vertrix_arena_release_all.argtypes = [P, SZ, Destroy, P]
    n.vertrix_board_release_piece_children.argtypes = [P, SZ, Resolve, Destroy, P]
    n.vertrix_marker_actor_construct.argtypes = [P, SZ]
    n.vertrix_object_address_plus_4.argtypes = [U]
    n.vertrix_object_address_plus_4.restype = U
    n.vertrix_object_list_filled.argtypes = [P, SZ, Resolve, P, UP]
    n.vertrix_object_triple.argtypes = [P, SZ, UP]
    n.vertrix_record_clear_flag.argtypes = [P, SZ, U]
    n.vertrix_record_set_flag.argtypes = [P, SZ, U]
    n.vertrix_actors_handler_from_ec.argtypes = [P, U, Resolve, P]
    n.vertrix_actors_handler_from_ec_unlinked.argtypes = [P, U, U, Resolve, P]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x42a480)
    stubs = VirtualStubs(cpu, register=True, slots=1)
    pool = Pool(cpu, 4, SIZE)
    obj, others = pool.handles[0], pool.handles[1:]
    events = []
    totals = {}

    @Destroy
    def destroy(handle, flag, context):
        events.append((handle, 0, flag))

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def fresh(slot_ranges=()):
        def patch(handle, data):
            struct.pack_into('<I', data, 0x158, stubs.VTABLE)
            if handle == obj:
                for offset, slots in slot_ranges:
                    for i in range(slots):
                        struct.pack_into('<I', data, offset + 4 * i,
                                         rng.choice(others + [obj, 0, 0]))
                struct.pack_into('<I', data, 0x468, rng.choice(others + [obj]))
                for other in (handle,):
                    struct.pack_into('<I', data, 8, rng.choice([0, 1, 2]))
        pool.fill(rng, patch)

    def buf():
        return pool.buffers[obj]

    def release(address, name, native, ranges, **registers):
        fresh(ranges)
        stubs.events.clear()
        events.clear()
        original.call(address, eax=obj, **registers)
        assert native(), (name, 'rejected')
        assert pool.same(), (name, pool.diff())
        assert [(h, f) for h, _s, f in events] == [(e, d) for e, _s, d in stubs.events], name
        count(name)

    for case in range(args.cases):
        release(0x42a480, '0x42a480',
                lambda: n.vertrix_piece_release_children(buf(), SIZE, 0, destroy, None),
                [(0x15c, 3)])
        release(0x42a4a0, '0x42a4a0',
                lambda: n.vertrix_piece_release_children(buf(), SIZE, 1, destroy, None),
                [(0x170, 3)])
        release(0x43d800, '0x43d800',
                lambda: n.vertrix_effects_release_all(buf(), SIZE, destroy, None),
                [(0x15c, 500), (0x92c, 8)])
        release(0x43e260, '0x43e260',
                lambda: n.vertrix_arena_release_all(buf(), SIZE, destroy, None),
                [(0x15c, 450), (0x864, 3), (0x870, 1)])
        board = others[0]
        fresh([(0x170, 3)])
        struct.pack_into('<I', pool.buffers[board], 0xa60, rng.choice([obj, 0]))
        cpu.mem_write(board, bytes(pool.buffers[board].raw))
        stubs.events.clear()
        events.clear()
        original.call(0x42eba0, eax=board)
        assert n.vertrix_board_release_piece_children(pool.buffers[board], SIZE, pool.resolve,
                                                      destroy, None)
        assert pool.same(), ('0x42eba0', pool.diff())
        assert [(h, f) for h, _s, f in events] == [(e, d) for e, _s, d in stubs.events]
        count('0x42eba0')
        fresh()
        original.call(0x429670, eax=obj)
        assert n.vertrix_marker_actor_construct(buf(), SIZE)
        assert pool.same(), (case, pool.diff())
        count('0x429670')
        assert original.call(0x429660, eax=obj) == n.vertrix_object_address_plus_4(obj)
        count('0x429660')
        fresh()
        expect = original.call(0x43d300, eax=obj) & 0xff
        out = U()
        assert n.vertrix_object_list_filled(buf(), SIZE, pool.resolve, None, c.byref(out))
        assert out.value == expect, case
        count('0x43d300')
        fresh()
        cpu.mem_write(0x80e000, bytes(12))
        original.call(0x475da0, eax=obj, edx=0x80e000, ebx=0x80e004, ecx=0x80e008)
        values = (U * 3)()
        assert n.vertrix_object_triple(buf(), SIZE, values)
        assert bytes(values) == bytes(cpu.mem_read(0x80e000, 12)), case
        count('0x475da0')
        index = rng.choice([0, 1, 2, 5, 9, 26, 0x10000, 0x10001])
        for address, name, native in ((0x476120, '0x476120', n.vertrix_record_clear_flag),
                                      (0x476140, '0x476140', n.vertrix_record_set_flag)):
            fresh()
            original.call(address, eax=obj, edx=index)
            ok = native(buf(), SIZE, index)
            if (index & 0xffff) * 0x60 < SIZE:
                assert ok and pool.same(), (name, index)
                count(name)
        for address, array, counter in ((0x471bb0, 0x546720, 0x546724),
                                        (0x471d90, 0x546748, 0x54674c),
                                        (0x471dd0, 0x546734, 0x546738),
                                        (0x471bf0, 0x546720, 0x546724)):
            fresh()
            listed = [rng.choice(others) for _ in range(rng.randrange(0, 4))]
            link = rng.choice([0, 1, rng.getrandbits(32)])
            for handle in others:
                if rng.random() < 0.5:
                    cpu.mem_write(handle + 0x14c, struct.pack('<I', link))
                    buffer = pool.buffers[handle]
                    struct.pack_into('<I', buffer, 0x14c, link)
            cpu.mem_write(0x80e100, struct.pack('<%dI' % max(len(listed), 1), *(listed or [0])))
            cpu.mem_write(array, struct.pack('<I', 0x80e100))
            cpu.mem_write(counter, struct.pack('<I', len(listed)))
            handles = (U * max(len(listed), 1))(*(listed or [0]))
            if address == 0x471bf0:
                original.call(address, eax=link)
                assert n.vertrix_actors_handler_from_ec_unlinked(handles, len(listed), link,
                                                                 pool.resolve, None)
            else:
                original.call(address, eax=0)
                assert n.vertrix_actors_handler_from_ec(handles, len(listed), pool.resolve, None)
            assert pool.same(), (hex(address), pool.diff())
            count(hex(address))
    assert not n.vertrix_marker_actor_construct(buf(), 0x163)
    assert not n.vertrix_object_release_slots(buf(), SIZE, SIZE - 28, 8, destroy, None)
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 43e260, 42eba0, 42a480, 42a4a0, 43d800, 429660, 429670, 43d300, 475da0, 476120 '
                       '476140, 471bb0, 471bf0, 471d90 and 471dd0 execute in the original (virtual destructors stubbed and '
                       'logged); whole objects, destroy events and returned values compare.'}
    (args.build_dir / 'object-slots-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
