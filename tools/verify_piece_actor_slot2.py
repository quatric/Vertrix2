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
    names = ['piece_actor_destroy.c', 'player_piece.c', 'piece_actor_construct.c', 'piece_actor_layout.c',
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

    def hook(cpu, address, size, context):
        events.append((cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX)))

    cpu.hook_add(UC_HOOK_CODE, hook, begin=STUB, end=STUB)

    @Vtable
    def vtable_of(handle, out, context):
        out[0] = VTABLE
        return 1

    @Slot2
    def call(handle, vtable, arg, context):
        assert vtable == VTABLE
        native_events.append((handle, arg))
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
    report = {'status': 'passed', 'complete_original_cases': cases, 'rejected_cases': 8192,
              'scope': 'Complete 42abf0 and 42ac30 execute with the slot-2 target supplied as a recorded stub. '
                       'Call order, identity and edx argument match; storage is unchanged. Slot-2 bodies '
                       'remain separate.'}
    (build / 'piece-actor-slot2-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
