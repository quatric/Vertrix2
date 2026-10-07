"""Compare complete original piece slot-2 forwarding methods."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX

PARENT, ACTORS, VTABLE, STUB = 0x801000, 0x802000, 0x804000, 0x804100
Slot2 = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint32, c.c_uint32, c.c_void_p)
Vtable = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'piece-actor-slot2.dylib'
    names = ['piece_actor_destroy.c', 'call_glue.c', 'player_piece.c', 'piece_actor_construct.c', 'piece_actor_layout.c',
             'piece_child_update.c', 'actor_storage.c', 'timer.c', 'timing.c', 'dword_transition.c',
             'frame_resource.c', 'piece_actor_update.c']
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    *[str(source / n) for n in names], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_piece_actor_forward_slot2.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32, Vtable,
                                                          c.c_void_p, Slot2, c.c_void_p]
    native.vertrix_piece_actor_self_slot2.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32, c.c_uint32,
                                                       Slot2, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_write(STUB, b'\xc3')
    events, native_events = [], []
    native_tables = {}
    mutate = False
    mutation_target = 0
    parent = None
    fail_vtable_handle = 0
    alternate_table, alternate_stub = VTABLE + 0x20, STUB + 0x20
    cpu.mem_write(alternate_stub, b"\xc3")

    def hook(cpu, address, size, context):
        handle = cpu.reg_read(UC_X86_REG_EAX)
        table = struct.unpack('<I', cpu.mem_read(handle + 0x158, 4))[0]
        events.append((handle, table, cpu.reg_read(UC_X86_REG_EDX)))
        if mutate and len(events) == 1:
            cpu.mem_write(PARENT + 0x174, struct.pack('<I', mutation_target))
            cpu.mem_write(ACTORS + 0x200 + 0x158, struct.pack('<I', alternate_table))

    cpu.hook_add(UC_HOOK_CODE, hook, begin=STUB, end=STUB)

    cpu.hook_add(UC_HOOK_CODE, hook, begin=alternate_stub, end=alternate_stub)

    @Vtable
    def vtable_of(handle, out, context):
        if handle == fail_vtable_handle:
            return 0
        out[0] = native_tables.get(handle, VTABLE)
        return 1

    @Slot2
    def call(handle, vtable, arg, context):
        native_events.append((handle, vtable, arg))
        if mutate and len(native_events) == 1:
            struct.pack_into('<I', parent, 0x174, mutation_target)
            native_tables[ACTORS + 0x200] = alternate_table
        return 1

    rng = random.Random(0x42abf0)
    cases = 0
    for case in range(4096):
        raw = bytearray(rng.randbytes(0x1a0))
        handles = [rng.choice([0, ACTORS + i * 0x200]) for i in range(7)]
        struct.pack_into('<7I', raw, 0x15c, *handles)
        struct.pack_into('<I', raw, 0x158, VTABLE)
        for i in range(7):
            cpu.mem_write(ACTORS + i * 0x200 + 0x158, struct.pack('<I', VTABLE))
        cpu.mem_write(VTABLE + 8, struct.pack('<I', STUB))
        arg = rng.getrandbits(32)
        parent = c.create_string_buffer(bytes(raw), len(raw))
        for address, native_call in ((0x42abf0, 'forward'), (0x42ac30, 'self')):
            events.clear()
            native_events.clear()
            cpu.mem_write(PARENT, bytes(raw))
            original.call(address, eax=PARENT, edx=arg)
            if native_call == 'forward':
                assert native.vertrix_piece_actor_forward_slot2(parent, len(raw), arg, vtable_of, None, call, None)
            else:
                assert native.vertrix_piece_actor_self_slot2(parent, len(raw), PARENT, arg, call, None)
            assert events == native_events, (case, native_call, events, native_events)
            assert parent.raw == bytes(cpu.mem_read(PARENT, len(raw)))
            assert len(events) == (sum(1 for h in handles if h) if native_call == 'forward' else 1)
            cases += 1
        before = parent.raw
        native_events.clear()
        assert not native.vertrix_piece_actor_forward_slot2(parent, 0x177, arg, vtable_of, None, call, None)
        assert not native.vertrix_piece_actor_self_slot2(parent, 0x15b, PARENT, arg, call, None)
        assert parent.raw == before and not native_events
    mutation_cases = 0
    for case in range(512):
        raw = bytearray(rng.randbytes(0x1a0))
        handles = [ACTORS + i * 0x200 for i in range(7)]
        struct.pack_into('<7I', raw, 0x15c, *handles)
        mutation_target = 0 if case % 2 == 0 else ACTORS + 0x200
        mutate = True
        native_tables.clear()
        for handle in handles:
            cpu.mem_write(handle + 0x158, struct.pack('<I', VTABLE))
        cpu.mem_write(VTABLE + 8, struct.pack('<I', STUB))
        cpu.mem_write(alternate_table + 8, struct.pack('<I', alternate_stub))
        events.clear()
        native_events.clear()
        parent = c.create_string_buffer(bytes(raw), len(raw))
        cpu.mem_write(PARENT, bytes(raw))
        arg = rng.getrandbits(32)
        original.call(0x42abf0, eax=PARENT, edx=arg)
        assert native.vertrix_piece_actor_forward_slot2(parent, len(raw), arg,
            vtable_of, None, call, None)
        assert events == native_events, (case, 'mutating slots/vtables', events, native_events)
        assert parent.raw == bytes(cpu.mem_read(PARENT, len(raw)))
        assert native_tables[ACTORS + 0x200] == struct.unpack('<I',
            cpu.mem_read(ACTORS + 0x200 + 0x158, 4))[0]
        mutation_cases += 1
    assert cases == 8192 and mutation_cases == 512
    mutate = False
    native_tables.clear()
    parent = c.create_string_buffer(0x1a0)
    struct.pack_into('<2I', parent, 0x15c, ACTORS, ACTORS + 0x200)
    fail_vtable_handle = ACTORS + 0x200
    native_events.clear()
    assert not native.vertrix_piece_actor_forward_slot2(parent, len(parent), 17,
        vtable_of, None, call, None)
    assert native_events == [(ACTORS, VTABLE, 17)]
    fail_vtable_handle = 0
    report = {'status': 'passed', 'complete_original_cases': cases + mutation_cases,
              'ordinary_forward_cases': 4096, 'self_cases': 4096,
              'mutating_forward_cases': mutation_cases, 'late_resolution_failure_cases': 1,
              'rejected_cases': 8192,
              'scope': 'Complete 42abf0 and 42ac30 execute with slot-2 targets supplied as '
                       'recorded stubs. Call order, identity, current vtable and edx argument '
                       'match. 512 forward fixtures mutate later parent slots and child vtables '
                       'during the first callback; whole parent storage and changed vtable '
                       'match, proving reads occur when each child is reached. A native-only '
                       'late resolver failure retains preceding calls. Slot-2 bodies remain '
                       'supplied boundaries.'}
    (build / 'piece-actor-slot2-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
