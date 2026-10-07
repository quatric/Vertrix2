"""Compare complete original base actor draw slot 4ae010 and chain walk 4ade60/4ae140."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_ESP)
ACTOR, COMPANION, GLOBALS, DRAW = 0x801000, 0x802000, 0x5bb710, 0x47ce10
POINTER, VISIT_A, VISIT_B = 0x544070, 0x4ac8a0, 0x4af8c0
NODES = 0x806000
Draw = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint32, c.c_int32, c.c_int32, c.c_uint32, c.c_uint32, c.c_void_p)
Visit = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint32, c.c_void_p)
Next = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_uint32), c.c_void_p)


class State(c.Structure):
    _fields_ = [('gate', c.c_uint32), ('refresh', c.c_uint32 * 6)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'actor-draw-slot.dylib'
    names = ['actor_draw_slot.c', 'actor_refresh_state.c', 'piece_actor_destroy.c', 'call_glue.c', 'player_piece.c', 'piece_actor_construct.c', 'piece_actor_layout.c', 'piece_child_update.c', 'actor_storage.c', 'timer.c', 'timing.c', 'dword_transition.c', 'frame_resource.c', 'piece_actor_update.c']
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', * [str(source / n) for n in names], '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    P, S, SZ, U = c.POINTER(State), c.c_void_p, c.c_size_t, c.c_uint32
    n.vertrix_actor_draw_slot.argtypes = [P, S, SZ, U, U, S, SZ, Draw, S]
    n.vertrix_actor_chain_walk.argtypes = [U, U, Visit, Visit, Next, S]
    original = Original(args.executable)
    cpu = original.cpu
    for address, code in ((DRAW, b'\xc2\x10\x00'), (VISIT_A, b'\xc3'), (VISIT_B, b'\xc3')):
        cpu.mem_write(address, code)
    events, native = [], []
    mutation = None
    current_actor = current_companion = None
    current_alternate = None
    global_handle = COMPANION
    service_events = []
    expected_context = 0x1234
    GlobalRead = c.CFUNCTYPE(c.c_uint32, c.c_uint32, c.c_void_p)
    Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)
    class Globals(c.Structure):
        _fields_ = [("read", GlobalRead), ("context", c.c_void_p)]
    @GlobalRead
    def global_read(address, context):
        assert address == POINTER and context == expected_context
        service_events.append(("global", address))
        return global_handle
    @Resolve
    def resolve(handle, storage, size, context):
        assert context == expected_context
        service_events.append(("resolve", handle))
        buffer = {COMPANION: current_companion, 0x803000: current_alternate}.get(handle)
        if buffer is None: return 0
        storage[0], size[0] = c.addressof(buffer), len(buffer)
        return 1
    globals_service = Globals(global_read, expected_context)
    n.vertrix_actor_draw_slot_full.argtypes = [P, S, SZ, U, U, c.POINTER(Globals), Resolve, S, Draw, S]
    def hook_draw(cpu, a, s, x):
        esp = cpu.reg_read(UC_X86_REG_ESP)
        events.append(('draw', cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX), cpu.reg_read(UC_X86_REG_ECX), * struct.unpack('<4I', bytes(cpu.mem_read(esp + 4, 16)))))
        if len(events) == 1 and mutation is not None:
            for address, data in mutation:
                cpu.mem_write(address, data)
    cpu.hook_add(UC_HOOK_CODE, hook_draw, begin=DRAW, end=DRAW)
    cpu.hook_add(UC_HOOK_CODE, lambda cpu, a, s, x: events.append(('a', cpu.reg_read(UC_X86_REG_EAX), 0)), begin=VISIT_A, end=VISIT_A)
    cpu.hook_add(UC_HOOK_CODE, lambda cpu, a, s, x: events.append(('b', cpu.reg_read(UC_X86_REG_EAX), cpu.reg_read(UC_X86_REG_EDX))), begin=VISIT_B, end=VISIT_B)
    @ Draw
    def draw(handle, selector, x, y, a, b, context):
        nonlocal global_handle
        native.append(('draw', handle, selector, y & 0xffffffff, x & 0xffffffff, y & 0xffffffff, a, b))
        if mutation is not None:
            assert context == expected_context
        if len(native) == 1 and mutation is not None:
            for address, data in mutation:
                if ACTOR <= address < ACTOR + len(current_actor):
                    c.memmove(c.addressof(current_actor) + address - ACTOR, data, len(data))
                elif COMPANION <= address < COMPANION + len(current_companion):
                    c.memmove(c.addressof(current_companion) + address - COMPANION, data, len(data))
                elif 0x803000 <= address < 0x803000 + len(current_alternate):
                    c.memmove(c.addressof(current_alternate) + address - 0x803000, data, len(data))
                elif address == POINTER:
                    global_handle = struct.unpack('<I', data)[0]
        return 1
    @ Visit
    def visit_a(node, arg, context):
        native.append(('a', node, 0))
        return 1
    @ Visit
    def visit_b(node, arg, context):
        native.append(('b', node, arg))
        return 1
    links = {}
    @ Next
    def follow(node, out, context):
        out[0] = links[node]
        return 1
    rng = random.Random(0x4ae010)
    totals = {'draw': 0, 'full_draw': 0, 'draw_drawn': 0, 'draw_companion': 0, 'chain': 0, 'chain_nodes': 0}
    def setup():
        raw = bytearray(rng.randbytes(0x200))
        index = rng.choice([0xffff, 0xffff, 0, 1, 2, 3, 4, 5])
        struct.pack_into('<H', raw, 0x148, index)
        struct.pack_into('<I', raw, 0x124, rng.choice([1, 1, 1, 0, 2]))
        struct.pack_into('<I', raw, 0x140, rng.choice([1, 1, 0, 2]))
        struct.pack_into('<I', raw, 0x12c, rng.choice([0, rng.getrandbits(32), rng.getrandbits(32)]))
        struct.pack_into('<I', raw, 0x130, rng.choice([0, rng.getrandbits(32), rng.getrandbits(32)]))
        struct.pack_into('<I', raw, 0x138, rng.choice([1, 1, 0, rng.getrandbits(32)]))
        g = [rng.choice([0, 1, 1, rng.getrandbits(32)]) for _ in range(7)]
        companion = bytearray(rng.randbytes(0x300))
        cpu.mem_write(ACTOR, bytes(raw))
        cpu.mem_write(COMPANION, bytes(companion))
        cpu.mem_write(GLOBALS, struct.pack('<7I', * g))
        cpu.mem_write(POINTER, struct.pack('<I', COMPANION))
        return (c.create_string_buffer(bytes(raw), len(raw)), c.create_string_buffer(bytes(companion), len(companion)), State(g[0], (c.c_uint32 * 6)(* g[1:])))
    for case in range(8192):
        actor, companion, state = setup()
        surface, selector = rng.getrandbits(32), rng.getrandbits(32)
        events.clear()
        native.clear()
        original.call(0x4ae010, eax=ACTOR, edx=surface, ebx=selector)
        assert n.vertrix_actor_draw_slot(c.byref(state), actor, len(actor), surface, selector, companion, len(companion), draw, None)
        assert bytes(actor.raw) == bytes(cpu.mem_read(ACTOR, len(actor)))
        assert bytes(state) == bytes(cpu.mem_read(GLOBALS, 28))
        totals['draw'] += 1
        assert [e[0] for e in events] == [e[0] for e in native], (case, events, native)
        for e, m in zip(events, native):
            assert e[1: 3] == m[1: 3] and e[3] == m[3] and e[4:
                ] == m[4:
                    ], (case, e, m)
        current_actor, current_companion = actor, companion
        global_handle = COMPANION
        events.clear(); native.clear(); service_events.clear()
        cpu.mem_write(ACTOR, actor.raw)
        cpu.mem_write(COMPANION, companion.raw)
        cpu.mem_write(GLOBALS, bytes(state))
        cpu.mem_write(POINTER, struct.pack('<I', COMPANION))
        original.call(0x4ae010, eax=ACTOR, edx=surface, ebx=selector)
        assert n.vertrix_actor_draw_slot_full(c.byref(state), actor, len(actor), surface, selector,
            c.byref(globals_service), resolve, expected_context, draw, expected_context)
        assert events == native, (case, 'full API', events, native)
        totals['full_draw'] += 1
        totals['draw_drawn'] += bool(events)
        totals['draw_companion'] += len(events) == 2
#rejection preserves
        before = actor.raw
        native.clear()
        assert not n.vertrix_actor_draw_slot(c.byref(state), actor, 0x100, surface, selector, companion, len(companion), draw, None)
        assert not native and actor.raw == before
    mutations = [
        (0, [(ACTOR + 0x140, struct.pack('<I', 1))]),
        (1, [(ACTOR + 0x140, struct.pack('<I', 0))]),
        (1, [(ACTOR + 0x128, struct.pack('<hhII', -123, 234, 0, 0))]),
        (1, [(COMPANION + 0x274, struct.pack('<II', 91, 92))]),
        (1, [(POINTER, struct.pack('<I', 0x803000))]),
    ]
    totals['callback_mutations'] = 0
    for initial_flag, updates in mutations:
        actor, companion, state = setup()
        for offset, value in ((0x120, 1), (0x124, 1), (0x138, 1), (0x12c, 7), (0x130, 8), (0x140, initial_flag)):
            struct.pack_into('<I', actor, offset, value)
        struct.pack_into('<H', actor, 0x148, 0xffff)
        current_actor, current_companion = actor, companion
        current_alternate = c.create_string_buffer(bytes(0x300), 0x300)
        struct.pack_into('<II', current_alternate, 0x274, 101, 102)
        cpu.mem_write(ACTOR, actor.raw)
        cpu.mem_write(COMPANION, companion.raw)
        cpu.mem_write(0x803000, current_alternate.raw)
        cpu.mem_write(GLOBALS, bytes(state))
        cpu.mem_write(POINTER, struct.pack('<I', COMPANION))
        global_handle = COMPANION
        before_actor, before_companion = actor.raw, companion.raw
        mutation = updates
        events.clear(); native.clear(); service_events.clear()
        original.call(0x4ae010, eax=ACTOR, edx=4, ebx=5)
        assert n.vertrix_actor_draw_slot_full(c.byref(state), actor, len(actor), 4, 5,
            c.byref(globals_service), resolve, expected_context, draw, expected_context)
        assert events == native, ('callback mutation', events, native)
        assert actor.raw == bytes(cpu.mem_read(ACTOR, len(actor)))
        assert companion.raw == bytes(cpu.mem_read(COMPANION, len(companion)))
        assert len(service_events) == (2 if len(events) == 2 else 0)
        if not any(address == POINTER for address, _ in updates):
            c.memmove(actor, before_actor, len(actor))
            c.memmove(companion, before_companion, len(companion))
            native.clear()
            assert n.vertrix_actor_draw_slot(c.byref(state), actor, len(actor), 4, 5,
                companion, len(companion), draw, expected_context)
            assert events == native, ('fixed-companion mutation', events, native)
        totals['callback_mutations'] += 1
    # Missing late services/short companion retain the primary callback.
    late_failure_cases = 0
    for missing_globals, bad_handle, short in [(True, False, False), (False, True, False), (False, False, True)]:
        struct.pack_into('<I', actor, 0x140, 1)
        mutation = []
        global_handle = 0xdeadbeef if bad_handle else COMPANION
        current_companion = c.create_string_buffer(bytes(0x100), 0x100) if short else companion
        native.clear(); service_events.clear()
        assert not n.vertrix_actor_draw_slot_full(c.byref(state), actor, len(actor), 4, 5,
            None if missing_globals else c.byref(globals_service), resolve, expected_context, draw, expected_context)
        assert len(native) == 1
        late_failure_cases += 1
    mutation = None
    for case in range(2048):
        count = rng.randrange(0, 9)
        nodes = [NODES + 0x200 * i for i in range(count)]
        links.clear()
        for i, node in enumerate(nodes):
            nxt = nodes[i + 1] if i + 1 < count else 0
            links[node] = nxt
            cpu.mem_write(node + 0x108, struct.pack('<I', nxt))
        arg = rng.getrandbits(32)
        first = nodes[0] if nodes else 0
        for entry in (0x4ade60, 0x4ae140):
            events.clear()
            native.clear()
            original.call(entry, eax=first, edx=arg)
            assert n.vertrix_actor_chain_walk(first, arg, visit_a, visit_b, follow, None)
            assert events == native, (case, events, native)
            totals['chain'] += 1
            totals['chain_nodes'] += count
        links[NODES] = NODES
        native.clear()
        assert not n.vertrix_actor_chain_walk(NODES, 0, visit_a, visit_b, follow, None)
    report = {'status': 'passed', 'complete_original_cases': totals, 'native_late_failure_cases': late_failure_cases, 'scope': 'Complete 4ae010, 4ade60 and 4ae140 execute in the original. Draw 47ce10 and chain ' 'visits 4ac8a0/4af8c0 are recorded stubs; their eax/edx/ecx and four stack arguments ' 'and call order match. Actor storage and 5bb710..5bb728 compare whole. Native ' 'cyclic chains and short storage are rejected. Both draw APIs cover 8192 cases; five original-backed '
                       'callback mutations cover flag toggles, fresh rectangle/resource and companion fields, '
                       'and global companion replacement. Three native late failures retain the first draw.'}
    (build / 'actor-draw-slot-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
