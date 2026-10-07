"""Compare complete original slot-array release and small initialiser routines with the native
recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build
from verify_object_tails import Call, Calls
from verify_resource_record import Read
from verify_support import VirtualStubs

U = c.c_uint32
SIZE = 0xb00
Destroy = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)


def verify_full(n, args, only_marker=False):
    original = Original(args.executable)
    cpu = original.cpu
    OBJ, BOARD = 0x806000, 0x807000
    ACTORS = (0x808000, 0x809000, 0x80a000, 0x80b000)
    TABLE1, TABLE2, METHOD1, METHOD2 = 0x707500, 0x707504, 0x707100, 0x707110
    runtime_pointer = c.POINTER(Calls)
    n.vertrix_object_release_slots_full.argtypes = [c.c_void_p, c.c_size_t, c.c_size_t,
                                                   c.c_int32, U, runtime_pointer, Read, c.c_void_p]
    n.vertrix_piece_release_children_full.argtypes = [c.c_void_p, c.c_size_t, c.c_int,
                                                      U, runtime_pointer, Read, c.c_void_p]
    for name in ('vertrix_effects_release_all_full', 'vertrix_arena_release_all_full'):
        getattr(n, name).argtypes = [c.c_void_p, c.c_size_t, U, runtime_pointer, Read, c.c_void_p]
    n.vertrix_marker_actor_construct_full.argtypes = [c.c_void_p, c.c_size_t, U]
    n.vertrix_marker_actor_construct_full.restype = U
    n.vertrix_board_release_piece_children_full.argtypes = [c.c_void_p, c.c_size_t, U,
                                                            Resolve, c.c_void_p, runtime_pointer,
                                                            Read, c.c_void_p]
    for name in ('vertrix_object_release_slots_full', 'vertrix_piece_release_children_full',
                 'vertrix_effects_release_all_full', 'vertrix_arena_release_all_full',
                 'vertrix_board_release_piece_children_full'):
        getattr(n, name).restype = U
    rng = random.Random(0x4b22c042)
    host = {}
    native_calls = []
    tokens = []
    mutates = False
    mutation_applied = False
    native_mutation_applied = False
    replacement = 0
    full_counts = {}
    mutation_counts = {}
    no_call_counts = {}
    changed_vtable_cases = {}
    zero_count_cases = 0
    negative_count_cases = 0
    callback_count = 0
    marker_handles = {}

    def writes(slot):
        return [(slot, replacement), (slot + 4, ACTORS[2]),
                (ACTORS[1] + 0x158, TABLE2), (OBJ + 0x92c, ACTORS[1]),
                (OBJ + 0x870, ACTORS[1]), (BOARD + 0xa60, ACTORS[3])]

    def handler(address, eax, edx, ebx, ecx, stack):
        nonlocal mutation_applied
        index = len(stubs.log) - 1
        if mutates and not mutation_applied:
            mutation_applied = True
            for at, value in writes(ecx):
                cpu.mem_write(at, struct.pack('<I', value))
        return tokens[index % len(tokens)]

    stubs = Stubs(cpu, handler)
    stubs.add(METHOD1)
    stubs.add(METHOD2)

    @Call
    def call(site, context):
        nonlocal native_mutation_applied
        x = site.contents
        index = len(native_calls)
        native_calls.append((x.target, x.eax, x.edx, x.ebx, x.ecx))
        if mutates and not native_mutation_applied:
            native_mutation_applied = True
            for at, value in writes(x.ecx):
                for base, buffer in host.items():
                    if base <= at and at + 4 <= base + SIZE:
                        c.memmove(c.addressof(buffer) + at - base, struct.pack('<I', value), 4)
                        break
        return tokens[index % len(tokens)]

    @Read
    def read(address, width, value, context):
        for base, buffer in host.items():
            if base <= address and address + width <= base + SIZE:
                value[0] = int.from_bytes(buffer.raw[address - base:address - base + width], 'little')
                return 1
        if address in (TABLE1, TABLE2) and width == 4:
            value[0] = METHOD1 if address == TABLE1 else METHOD2
            return 1
        return 0

    @Resolve
    def resolve(handle, storage, size, context):
        buffer = host.get(handle)
        if buffer is None:
            return 0
        storage[0] = c.addressof(buffer)
        size[0] = SIZE
        return 1

    runtime = Calls(call, None)
    routines = [(0x4b22c0, [(0x15c, 16)]), (0x42a480, [(0x15c, 3)]),
                (0x42a4a0, [(0x170, 3)]), (0x43d800, [(0x15c, 500), (0x92c, 8)]),
                (0x43e260, [(0x15c, 450), (0x864, 3), (0x870, 1)]),
                (0x42eba0, [(0x170, 3)]), (0x429670, [])]
    if only_marker:
        routines = [(0x429670, [])]
    for address, ranges in routines:
        key = hex(address)
        full_counts[key] = mutation_counts[key] = no_call_counts[key] = changed_vtable_cases[key] = 0
        for case in range(args.full_cases):
            initial = {base: bytearray(rng.randbytes(SIZE)) for base in (OBJ, BOARD, *ACTORS)}
            for actor in ACTORS:
                struct.pack_into('<I', initial[actor], 0x158, TABLE1)
            for offset, count in ranges:
                for slot in range(count):
                    handle = 0 if case % 8 == 1 else rng.choice((*ACTORS, 0, 0))
                    struct.pack_into('<I', initial[OBJ], offset + 4 * slot, handle)
            mutates = address != 0x429670 and (case % 4 == 0 or (address == 0x4b22c0 and case % 8 == 7))
            if mutates:
                first = ranges[0][0]
                struct.pack_into('<III', initial[OBJ], first, ACTORS[0], ACTORS[1], ACTORS[1])
            piece = 0 if case % 8 == 1 else OBJ
            struct.pack_into('<I', initial[BOARD], 0xa60, piece)
            host = {base: c.create_string_buffer(bytes(raw), SIZE) for base, raw in initial.items()}
            for base, raw in initial.items():
                cpu.mem_write(base, bytes(raw))
            cpu.mem_write(TABLE1, struct.pack('<I', METHOD1))
            cpu.mem_write(TABLE2, struct.pack('<I', METHOD2))
            stubs.log.clear()
            native_calls.clear()
            mutation_applied = native_mutation_applied = False
            tokens = [0 if case % 7 == 0 else rng.getrandbits(32) for _ in range(512)]
            replacement = rng.getrandbits(32)
            ebx, ecx, edx = (rng.getrandbits(32) for _ in range(3))
            if address == 0x429670:
                marker_object = rng.choice((OBJ, *ACTORS))
                marker_handles[hex(marker_object)] = marker_handles.get(hex(marker_object), 0) + 1
                expect = original.call(address, eax=marker_object, edx=edx, ebx=ebx, ecx=ecx)
                got = n.vertrix_marker_actor_construct_full(host[marker_object], SIZE, marker_object)
                assert got == marker_object, (key, case)
            elif address == 0x4b22c0:
                count = (-0x80000000, -1, 0, 1, 2, 7, 8, 13)[case % 8]
                zero_count_cases += count == 0
                negative_count_cases += count < 0
                expect = original.call(address, eax=OBJ + 0x15c, edx=count & 0xffffffff,
                                         ebx=ebx, ecx=ecx)
                got = n.vertrix_object_release_slots_full(host[OBJ], SIZE, 0x15c, count, OBJ,
                                                          c.byref(runtime), read, None)
            elif address in (0x42a480, 0x42a4a0):
                expect = original.call(address, eax=OBJ, edx=edx, ebx=ebx, ecx=ecx)
                got = n.vertrix_piece_release_children_full(host[OBJ], SIZE, address == 0x42a4a0,
                                                             OBJ, c.byref(runtime), read, None)
            elif address == 0x43d800:
                expect = original.call(address, eax=OBJ, edx=edx, ebx=ebx, ecx=ecx)
                got = n.vertrix_effects_release_all_full(host[OBJ], SIZE, OBJ, c.byref(runtime), read, None)
            elif address == 0x43e260:
                expect = original.call(address, eax=OBJ, edx=edx, ebx=ebx, ecx=ecx)
                got = n.vertrix_arena_release_all_full(host[OBJ], SIZE, OBJ, c.byref(runtime), read, None)
            else:
                expect = original.call(address, eax=BOARD, edx=edx, ebx=ebx, ecx=ecx)
                got = n.vertrix_board_release_piece_children_full(host[BOARD], SIZE, BOARD,
                                                                  resolve, None, c.byref(runtime), read, None)
            assert got == expect, (key, case, hex(got), hex(expect))
            assert native_calls == stubs.log, (key, case, native_calls[:5], stubs.log[:5])
            assert mutation_applied == native_mutation_applied, (key, case)
            for base, buffer in host.items():
                assert buffer.raw == bytes(cpu.mem_read(base, SIZE)), (key, case, hex(base))
            full_counts[key] += 1
            mutation_counts[key] += mutation_applied
            no_call_counts[key] += not native_calls
            changed_vtable_cases[key] += any(call[0] == METHOD2 for call in native_calls)
            callback_count += len(native_calls)
    assert all(count == args.full_cases for count in full_counts.values())
    assert all(count > 0 for key, count in mutation_counts.items() if key != '0x429670')
    assert all(count > 0 for count in no_call_counts.values())
    assert all(count > 0 for key, count in changed_vtable_cases.items() if key != '0x429670')
    if not only_marker:
        assert zero_count_cases > 0 and negative_count_cases > 0
    assert sum(marker_handles.values()) == args.full_cases
    assert len(marker_handles) > 1
    return {'complete_original_executions': full_counts,
            'marker_constructor_object_handles': marker_handles,
            'callback_mutation_cases': mutation_counts, 'no_callback_cases': no_call_counts,
            'changed_later_vtable_cases': changed_vtable_cases,
            'zero_count_cases': zero_count_cases, 'negative_count_single_slot_cases': negative_count_cases,
            'exact_callback_register_comparisons': callback_count}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    parser.add_argument('--full-cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-slots',
              ['object_slots.c', 'actor_storage.c', 'actor_fields.c', 'call_glue.c'])
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
    full_report = verify_full(n, args)
    report = {'status': 'passed', 'full_runtime_boundary': full_report, 'complete_original_executions': totals,
              'scope': 'Complete 43e260, 42eba0, 42a480, 42a4a0, 43d800, 429660, 429670, 43d300, 475da0, 476120 '
                       '476140, 471bb0, 471bf0, 471d90 and 471dd0 execute in the original (virtual destructors stubbed and '
                       'logged); whole objects and destroy events compare, with return checks on scalar '
                       'helpers. Full slot release '
                       'APIs additionally compare six whole release routines and the complete marker constructor with exact EAX and callback '
                       'registers, independent native memory, late slot/vtable mutations, overwritten '
                       'current-slot writes, zero counts, negative counts processing one slot and empty final groups.'}
    (args.build_dir / 'object-slots-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
