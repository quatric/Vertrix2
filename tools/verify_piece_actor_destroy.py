"""Compare complete original actor base and piece parent destructors."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original
from oracle_kit import Stubs
from verify_object_tails import Site, Call, Calls
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
    names = ['piece_actor_destroy.c', 'call_glue.c', 'player_piece.c', 'piece_actor_construct.c', 'piece_actor_layout.c', 'piece_child_update.c', 'actor_storage.c', 'timer.c', 'timing.c', 'dword_transition.c', 'frame_resource.c', 'piece_actor_update.c']
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', * [str(source / n) for n in names], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_actor_base_destroy.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32, c.c_uint32, Destroy, c.c_void_p]
    native.vertrix_piece_actor_destroy.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32, c.c_uint32, Destroy, c.c_void_p, Destroy, c.c_void_p]
    native.vertrix_actor_base_destroy_full.argtypes = native.vertrix_actor_base_destroy.argtypes + [c.POINTER(Calls), c.c_uint32, c.c_uint32]
    native.vertrix_actor_base_destroy_full.restype = c.c_uint32
    native.vertrix_piece_actor_destroy_full.argtypes = native.vertrix_piece_actor_destroy.argtypes + [c.POINTER(Calls), c.c_uint32, c.c_uint32]
    native.vertrix_piece_actor_destroy_full.restype = c.c_uint32
    mutate_children = False
    mutation_target = 0
    parent = None
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_write(STUB, b'\xc3')
    cpu.mem_write(FREE, b'\xc3')
    events = []
    def child(cpu, address, size, context):
        events.append(('child', cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX)))
        if mutate_children and sum(event[0] == 'child' for event in events) == 1:
            cpu.mem_write(PARENT + 0x174, struct.pack('<I', mutation_target))
            cpu.mem_write(PARENT + 0x180, struct.pack('<I', 0xfedcba98))
    def free(cpu, address, size, context):
        events.append(('free', cpu.reg_read(UC_X86_REG_EAX)))
    cpu.hook_add(UC_HOOK_CODE, child, begin=STUB, end=STUB)
    cpu.hook_add(UC_HOOK_CODE, free, begin=FREE, end=FREE)
    native_events = []
    @ Destroy
    def destroy_child(handle, context):
        native_events.append(('child', handle, 2))
        if mutate_children and sum(event[0] == 'child' for event in native_events) == 1:
            struct.pack_into('<I', parent, 0x174, mutation_target)
            struct.pack_into('<I', parent, 0x180, 0xfedcba98)
        return 1
    @ Destroy
    def release(handle, context):
        native_events.append(('free', handle))
        return 1
    rng = random.Random(0x42ab10)
    parent_cases = base_cases = rejected = 0
    for case in range(4096):
        raw = bytearray(rng.randbytes(0x1a0))
        handles = [rng.choice([0, ACTORS + i * 0x200]) for i in range(7)]
        struct.pack_into('<7I', raw, 0x15c, * handles)
        flags = rng.choice([0, 1, 2, 3, 8, 0x102, rng.getrandbits(32) & ~ 4])
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
                assert native.vertrix_piece_actor_destroy(parent, len(raw), PARENT, flags, destroy_child, None, release, None)
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
    cleanup_result = 0
    free_result = 0
    runtime_events = []
    def runtime_handler(target, eax, edx, ebx, ecx, args):
        return cleanup_result if target == 0x4ccb9f else free_result
    runtime_stubs = Stubs(cpu, runtime_handler)
    runtime_stubs.add(0x4ccb9f)
    runtime_stubs.add(0x4ca040)
    @ Call
    def runtime_call(site, context):
        entry = site.contents
        runtime_events.append((entry.target, entry.eax, entry.edx, entry.ebx, entry.ecx))
        assert entry.stack == 0 and entry.stack_next == 0
        return cleanup_result if entry.target == 0x4ccb9f else free_result
    runtime = Calls(runtime_call, None)
    full_cases = {False: 0, True: 0}
    cleanup_cases = {False: 0, True: 0}
    normal_cases = {False: 0, True: 0}
    mutation_cases = zero_cleanup_token_cases = combined_flag_cases = 0
    for case in range(4096):
        raw = bytearray(rng.randbytes(0x1a0))
        handles = [ACTORS] + [rng.choice([0, ACTORS + i * 0x200]) for i in range(1, 7)]
        struct.pack_into('<7I', raw, 0x15c, *handles)
        flags = (rng.getrandbits(32) & ~15) | case % 16
        ebx, ecx = rng.getrandbits(32), rng.getrandbits(32)
        cleanup_result = rng.choice([0, PARENT - 4, 0x812340, rng.getrandbits(32)])
        free_result = rng.getrandbits(32)
        mutation_target = 0 if case % 32 < 16 else ACTORS + 0x200
        for i in range(7):
            cpu.mem_write(ACTORS + i * 0x200 + 0x158, struct.pack('<I', VTABLE))
        cpu.mem_write(VTABLE, struct.pack('<I', STUB))
        for base in (False, True):
            mutate_children = not base and not (flags & 4) and case % 8 == 0
            events.clear()
            native_events.clear()
            runtime_events.clear()
            runtime_stubs.log.clear()
            parent = c.create_string_buffer(bytes(raw), len(raw))
            cpu.mem_write(PARENT, bytes(raw))
            expected_return = original.call(0x4ac130 if base else 0x42ab10,
                                            eax=PARENT, edx=flags, ebx=ebx, ecx=ecx)
            release_arg = Destroy() if flags & 4 else release
            child_arg = Destroy() if flags & 4 else destroy_child
            if base:
                result = native.vertrix_actor_base_destroy_full(parent, len(raw), PARENT, flags,
                    release_arg, None, c.byref(runtime), ebx, ecx)
            else:
                result = native.vertrix_piece_actor_destroy_full(parent, len(raw), PARENT, flags,
                    child_arg, None, release_arg, None, c.byref(runtime), ebx, ecx)
            assert result == expected_return == PARENT, (case, base, 'return')
            assert parent.raw == bytes(cpu.mem_read(PARENT, len(raw))), (case, base, 'storage')
            assert native_events == events, (case, base, 'callbacks')
            expected_runtime = [entry[:5] for entry in runtime_stubs.log]
            assert runtime_events == expected_runtime, (case, base, 'runtime registers')
            if flags & 4:
                class_token = 0x517b10 if base else 0x514790
                cleanup_ecx = PARENT if base else ecx
                assert runtime_events == [(0x4ccb9f, PARENT, class_token, ebx, cleanup_ecx),
                                          (0x4ca040, cleanup_result, 0, ebx, cleanup_ecx)]
                assert not native_events
                cleanup_cases[base] += 1
                zero_cleanup_token_cases += cleanup_result == 0
                combined_flag_cases += bool(flags & 2)
            else:
                assert not runtime_events
                normal_cases[base] += 1
                mutation_cases += mutate_children
            full_cases[base] += 1
    assert full_cases == {False: 4096, True: 4096}
    assert cleanup_cases == {False: 2048, True: 2048}
    assert normal_cases == {False: 2048, True: 2048}
    assert mutation_cases == 512
    assert zero_cleanup_token_cases > 0
    assert combined_flag_cases == 2048
    report = {'status': 'passed',
              'complete_original_piece_destructor_cases': full_cases[False],
              'complete_original_base_destructor_cases': full_cases[True],
              'flag4_piece_cleanup_cases': cleanup_cases[False],
              'flag4_base_cleanup_cases': cleanup_cases[True],
              'normal_piece_cases': normal_cases[False], 'normal_base_cases': normal_cases[True],
              'mutating_child_callback_cases': mutation_cases,
              'zero_cleanup_token_cases': zero_cleanup_token_cases,
              'flag4_and_flag2_cases': combined_flag_cases,
              'partial_piece_wrapper_cases': parent_cases, 'partial_base_wrapper_cases': base_cases,
              'rejected_partial_wrapper_cases': rejected,
              'scope': 'Complete 42ab10 and 4ac130 across full-width flags including every low-bit '
                       'combination. Whole parent storage, original eax returns, child destruction '
                       'order/flag2 and normal heap free match. Flag4 cleanup takes precedence over '
                       'flag2: 4ccb9f class token and caller registers, its arbitrary returned token '
                       '(including zero), and the subsequent 4ca040 registers match recorded '
                       'runtime boundaries. Mutating child callbacks change later slots and parent '
                       'storage identically, verifying sequential slot reads. Runtime cleanup, '
                       'heap free and child destructor bodies remain supplied boundaries. Existing '
                       'partial wrappers retain flag4 rejection and their 4096-case normal checks.'}
    (build / 'piece-actor-destroy-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
