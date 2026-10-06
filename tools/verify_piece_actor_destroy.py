"""Compare complete original actor base and piece parent destructors."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX

PARENT, ACTORS, VTABLE, STUB, FREE = 0x801000, 0x802000, 0x804000, 0x804100, 0x4ca050
Destroy = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'piece-actor-destroy.dylib'
    names = ['piece_actor_destroy.c', 'player_piece.c', 'piece_actor_construct.c', 'piece_actor_layout.c',
             'piece_child_update.c', 'actor_storage.c', 'timer.c', 'timing.c', 'dword_transition.c',
             'frame_resource.c', 'piece_actor_update.c']
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    *[str(source / n) for n in names], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_actor_base_destroy.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32, c.c_uint32, Destroy, c.c_void_p]
    native.vertrix_piece_actor_destroy.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32, c.c_uint32,
                                                   Destroy, c.c_void_p, Destroy, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_write(STUB, b'\xc3')
    cpu.mem_write(FREE, b'\xc3')
    events = []

    def child(cpu, address, size, context):
        events.append(('child', cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX)))

    def free(cpu, address, size, context):
        events.append(('free', cpu.reg_read(UC_X86_REG_EAX)))

    cpu.hook_add(UC_HOOK_CODE, child, begin=STUB, end=STUB)
    cpu.hook_add(UC_HOOK_CODE, free, begin=FREE, end=FREE)
    native_events = []

    @Destroy
    def destroy_child(handle, context):
        native_events.append(('child', handle, 2))
        return 1

    @Destroy
    def release(handle, context):
        native_events.append(('free', handle))
        return 1

    rng = random.Random(0x42ab10)
    parent_cases = base_cases = rejected = 0
    for case in range(4096):
        raw = bytearray(rng.randbytes(0x1a0))
        handles = [rng.choice([0, ACTORS + i * 0x200]) for i in range(7)]
        struct.pack_into('<7I', raw, 0x15c, *handles)
        flags = rng.choice([0, 1, 2, 3, 8, 0x102, rng.getrandbits(32) & ~4])
        for i in range(7):
            cpu.mem_write(ACTORS + i * 0x200 + 0x158, struct.pack('<I', VTABLE))
        cpu.mem_write(VTABLE, struct.pack('<I', STUB))
        for base in (False, True):
            events.clear()
            native_events.clear()
            parent = c.create_string_buffer(bytes(raw), len(raw))
            cpu.mem_write(PARENT, bytes(raw))
            result = original.call(0x4ac130 if base else 0x42ab10, eax=PARENT, edx=flags)
            assert result == PARENT
            if base:
                assert native.vertrix_actor_base_destroy(parent, len(raw), PARENT, flags, release, None)
            else:
                assert native.vertrix_piece_actor_destroy(parent, len(raw), PARENT, flags, destroy_child,
                                                          None, release, None)
            assert parent.raw == bytes(cpu.mem_read(PARENT, len(raw))), (case, base)
            assert [tuple(e) for e in events] == [tuple(e) for e in native_events], (case, base, events, native_events)
            if base:
                assert events == ([('free', PARENT)] if flags & 2 else [])
                base_cases += 1
            else:
                expected = [('child', h, 2) for h in handles if h] + ([('free', PARENT)] if flags & 2 else [])
                assert events == expected, case
                parent_cases += 1
        before = parent.raw
        native_events.clear()
        assert not native.vertrix_piece_actor_destroy(parent, 0x18b, PARENT, flags, destroy_child, None, release, None)
        assert not native.vertrix_piece_actor_destroy(parent, len(raw), PARENT, flags | 4, destroy_child, None, release, None)
        assert not native.vertrix_actor_base_destroy(parent, 0x15b, PARENT, flags, release, None)
        assert not native.vertrix_actor_base_destroy(parent, len(raw), PARENT, flags | 4, release, None)
        assert parent.raw == before and not native_events
        rejected += 4
    report = {'status':
        'passed',
            'complete_original_piece_destructor_cases' : parent_cases,
                                                         'complete_original_base_destructor_cases'
            : base_cases,
              'rejected_cases' : rejected,
                                 'scope'
            : 'Complete 42ab10 and 4ac130 execute with only the child virtual destructor and ' 'heap free supplied as recorded boundaries (stub ret). Whole parent storage, child ' 'destruction order/identity/flag2 and free argument match. Flag4 virtual-base ' 'cleanup is not modelled. Child destructor bodies remain separate.'
        }
        (build / 'piece-actor-destroy-verification.json')
                .write_text(json.dumps(report, indent = 2) + '\n')
                    print(json.dumps(report, indent = 2))

                        if __name__ == '__main__' : main()
