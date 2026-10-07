"""Compare complete original actor frame decay/switch routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Stubs, build
from verify_object_tails import Call, Calls
from verify_resource_record import Read
from unicorn import UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE

U = c.c_uint32
ACTOR, STATE = 0x801000, 0x5bb710
SIZE = 0x200
Cb2 = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_void_p)
Cb1 = c.CFUNCTYPE(None, c.c_uint32, c.c_void_p)
Write = c.CFUNCTYPE(c.c_int, U, c.c_uint, U, c.c_void_p)


class Ops(c.Structure):
    _fields_ = [('attach', Cb2), ('set_frame', Cb2), ('bind', Cb1)]


class State(c.Structure):
    _fields_ = [('gate', U), ('refresh', U * 6)]


def verify_full(n, original, stubs, args):
    cpu = original.cpu
    GLOBAL_BASE, GLOBAL_SIZE = 0x59b714, 0x40000
    rng = random.Random(0x449390fe)
    host_globals = bytearray(rng.randbytes(GLOBAL_SIZE))
    cpu.mem_write(GLOBAL_BASE, bytes(host_globals))
    host_actor = None
    original_writes, native_writes = [], []
    original_reads, native_reads = [], []
    native_calls = []
    errors = []
    mutations = False
    mutation_indices = []
    tokens = []
    mutated_callbacks = 0
    counts = {'0x449360': 0, '0x449390': 0, '0x4adfb0': 0, '0x4adfe0': 0}
    index_counts = {'sentinel': 0, 'negative': 0, 'bounded': 0, 'positive_outside': 0}
    same_frame_cases = 0
    decay_zero_cases = 0
    global_write_comparisons = 0
    callback_register_comparisons = 0

    def track_write(cpu, access, address, width, value, context):
        original_writes.append((address, width, value))

    def track_read(cpu, access, address, width, value, context):
        original_reads.append((address, width))

    cpu.hook_add(UC_HOOK_MEM_WRITE, track_write, begin=0x400000, end=0x5fffff)
    cpu.hook_add(UC_HOOK_MEM_READ, track_read, begin=0x400000, end=0x5fffff)

    @Write
    def write(address, width, value, context):
        native_writes.append((address, width, value))
        offset = address - GLOBAL_BASE
        if width != 4 or not 0 <= offset <= GLOBAL_SIZE - width:
            errors.append(('write', address, width))
            return 0
        host_globals[offset:offset + width] = value.to_bytes(width, 'little')
        return 1

    @Read
    def read(address, width, value, context):
        native_reads.append((address, width))
        offset = address - GLOBAL_BASE
        if width != 4 or not 0 <= offset <= GLOBAL_SIZE - width:
            errors.append(('read', address, width))
            return 0
        value[0] = int.from_bytes(host_globals[offset:offset + width], 'little')
        return 1

    def handler(address, eax, edx, ebx, ecx, stack):
        index = len(stubs.log) - 1
        if mutations:
            cpu.mem_write(ACTOR + 0x148, struct.pack('<H', mutation_indices[index]))
            cpu.mem_write(ACTOR + 0xb8, struct.pack('<I', tokens[index]))
        return tokens[index]

    @Call
    def call(site, context):
        x = site.contents
        index = len(native_calls)
        native_calls.append((x.target, x.eax, x.edx, x.ebx, x.ecx))
        if index >= len(tokens):
            errors.append(('extra_call', x.target))
            return 0
        if mutations:
            c.memmove(c.addressof(host_actor) + 0x148, struct.pack('<H', mutation_indices[index]), 2)
            c.memmove(c.addressof(host_actor) + 0xb8, struct.pack('<I', tokens[index]), 4)
        return tokens[index]

    runtime = Calls(call, None)
    stubs.handler = handler
    n.vertrix_actor_refresh_value_full.argtypes = [c.c_void_p, c.c_size_t, Read, c.c_void_p]
    n.vertrix_actor_refresh_arm_full.argtypes = [c.c_void_p, c.c_size_t, U, Write, c.c_void_p]
    n.vertrix_actor_frame_decay_full.argtypes = [c.c_void_p, c.c_size_t, U, U, Write, c.c_void_p]
    n.vertrix_actor_frame_switch_full.argtypes = [c.c_void_p, c.c_size_t, U, U,
                                                c.POINTER(Calls), Write, c.c_void_p]
    for name in ('vertrix_actor_refresh_value_full', 'vertrix_actor_refresh_arm_full',
                 'vertrix_actor_frame_decay_full', 'vertrix_actor_frame_switch_full'):
        getattr(n, name).restype = U

    def fresh_actor(raw):
        nonlocal host_actor
        cpu.mem_write(ACTOR, bytes(raw))
        host_actor = c.create_string_buffer(bytes(raw), SIZE)
        original_writes.clear()
        native_writes.clear()
        original_reads.clear()
        native_reads.clear()
        stubs.log.clear()
        native_calls.clear()
        errors.clear()

    def check(address, case, expected, got):
        nonlocal global_write_comparisons, callback_register_comparisons
        assert not errors, (address, case, errors)
        assert expected == got, (address, case, hex(expected), hex(got))
        assert host_actor.raw == bytes(cpu.mem_read(ACTOR, SIZE)), (address, case, 'actor')
        assert host_globals == bytes(cpu.mem_read(GLOBAL_BASE, GLOBAL_SIZE)), (address, case, 'globals')
        assert native_writes == original_writes, (address, case, native_writes, original_writes)
        assert native_reads == original_reads, (address, case, native_reads, original_reads)
        assert native_calls == stubs.log, (address, case, native_calls, stubs.log)
        global_write_comparisons += len(native_writes)
        callback_register_comparisons += len(native_calls)
        counts[address] += 1

    edge_indices = (0xffff, 0, 1, 5, 6, 0xfffe, 0x8000, 0x7fff, 0x8001, 0xff00)
    for case in range(args.refresh_cases):
        word = case if args.refresh_cases == 65536 else edge_indices[case % len(edge_indices)]
        raw = bytearray(rng.randbytes(SIZE))
        struct.pack_into('<H', raw, 0x148, word)
        if word == 0xffff:
            index_counts['sentinel'] += 1
        elif word >= 0x8000:
            index_counts['negative'] += 1
        elif word < 6:
            index_counts['bounded'] += 1
        else:
            index_counts['positive_outside'] += 1
        for address in ('0x4adfb0', '0x4adfe0'):
            fresh_actor(raw)
            expected = original.call(int(address, 16), eax=ACTOR, edx=rng.getrandbits(32),
                                     ebx=rng.getrandbits(32), ecx=rng.getrandbits(32))
            if address == '0x4adfb0':
                got = n.vertrix_actor_refresh_value_full(host_actor, SIZE, read, None)
            else:
                got = n.vertrix_actor_refresh_arm_full(host_actor, SIZE, ACTOR, write, None)
            check(address, case, expected, got)

    for case in range(args.full_cases):
        raw = bytearray(rng.randbytes(SIZE))
        word = rng.choice([0, 1, -1, 32767, -32768, rng.randrange(-32768, 32768)])
        struct.pack_into('<h', raw, 0x48, word)
        struct.pack_into('<H', raw, 0x148, edge_indices[case % len(edge_indices)])
        frame = rng.getrandbits(32)
        same_frame = case % 4 == 1
        struct.pack_into('<I', raw, 0xb8, frame if same_frame else (frame + 1) & 0xffffffff)
        cycles = rng.choice([0, 1, 2, 0xffffffff, 0x80000000, rng.getrandbits(32)])
        tokens = [0 if case % 7 == 0 else rng.getrandbits(32) for _ in range(3)]
        mutation_indices = [edge_indices[(case + i + 1) % len(edge_indices)] for i in range(3)]
        for address in ('0x449360', '0x449390'):
            fresh_actor(raw)
            mutations = address == '0x449390' and case % 4 == 0
            edx = cycles if address == '0x449360' else frame
            expected = original.call(int(address, 16), eax=ACTOR, edx=edx,
                                     ebx=rng.getrandbits(32), ecx=rng.getrandbits(32))
            if address == '0x449360':
                got = n.vertrix_actor_frame_decay_full(host_actor, SIZE, ACTOR, cycles, write, None)
                decay_zero_cases += word == 0
            else:
                got = n.vertrix_actor_frame_switch_full(host_actor, SIZE, ACTOR, frame,
                                                        c.byref(runtime), write, None)
                same_frame_cases += same_frame
                mutated_callbacks += mutations and bool(native_calls)
            check(address, case, expected, got)
    assert counts['0x449360'] == counts['0x449390'] == args.full_cases
    assert counts['0x4adfb0'] == counts['0x4adfe0'] == args.refresh_cases
    assert all(value > 0 for value in index_counts.values())
    assert same_frame_cases > 0 and decay_zero_cases > 0 and mutated_callbacks > 0
    return {'complete_original_executions': counts, 'signed_index_categories': index_counts,
            'same_frame_return_cases': same_frame_cases, 'zero_decay_return_cases': decay_zero_cases,
            'callback_mutation_cases': mutated_callbacks,
            'exact_callback_register_comparisons': callback_register_comparisons,
            'exact_raw_global_write_comparisons': global_write_comparisons,
            'independent_global_memory_base': hex(GLOBAL_BASE),
            'independent_global_memory_bytes': GLOBAL_SIZE,
            'all_65536_refresh_index_patterns': args.refresh_cases == 65536}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=8192)
    parser.add_argument('--full-cases', type=int, default=8192)
    parser.add_argument('--refresh-cases', type=int, default=65536)
    args = parser.parse_args()
    n = build(args.build_dir, 'actor-frame-switch',
              ['actor_frame_switch.c', 'actor_refresh_state.c', 'word_transition.c', 'actor_storage.c',
               'piece_actor_destroy.c', 'call_glue.c', 'player_piece.c', 'piece_actor_construct.c',
               'piece_actor_layout.c', 'piece_child_update.c', 'timer.c', 'timing.c',
               'dword_transition.c', 'frame_resource.c', 'piece_actor_update.c'])
    n.vertrix_actor_frame_decay.argtypes = [c.POINTER(State), c.c_void_p, c.c_size_t, U]
    n.vertrix_actor_frame_switch.argtypes = [c.POINTER(State), c.c_void_p, c.c_size_t, U, U,
                                             c.POINTER(Ops), c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    stubs = Stubs(cpu, lambda *a: None)
    for address in (0x4ac8d0, 0x4ac710, 0x4ac8a0):
        stubs.add(address)
    native = []
    ops = Ops(Cb2(lambda a, r, ctx: native.append((0x4ac8d0, a, r))),
              Cb2(lambda a, f, ctx: native.append((0x4ac710, a, f))),
              Cb1(lambda a, ctx: native.append((0x4ac8a0, a))))
    rng = random.Random(0x449360)
    totals = {}
    for case in range(args.cases):
        memory = bytearray(rng.randbytes(SIZE))
        struct.pack_into('<h', memory, 0x148, rng.choice([-1, 0, 1, 2, 3, 4, 5]))
        word = rng.choice([0, 1, 3, 4, 100, 0x7fff, -1, -400, rng.randrange(-32768, 32768)])
        struct.pack_into('<h', memory, 0x48, word)
        frame = rng.choice([0, 1, 2, 0xffffffff, rng.getrandbits(32)])
        struct.pack_into('<I', memory, 0xb8, frame if rng.random() < 0.3 else rng.getrandbits(32))
        state = struct.pack('<7I', *[rng.choice([0, 1, rng.getrandbits(32)]) for _ in range(7)])
        buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(memory))
        cycles = rng.choice([0, 1, 2, 5, 100, 0x10000, 0xffffffff, rng.getrandbits(32)])
        for name, address, edx in (('decay', 0x449360, cycles), ('switch', 0x449390, frame)):
            cpu.mem_write(ACTOR, bytes(memory))
            cpu.mem_write(STATE, state)
            stubs.log.clear()
            native.clear()
            c.memmove(buffer, bytes(memory), SIZE)
            native_state = State.from_buffer_copy(state)
            original.call(address, eax=ACTOR, edx=edx)
            if name == 'decay':
                n.vertrix_actor_frame_decay(c.byref(native_state), buffer, SIZE, cycles)
            else:
                n.vertrix_actor_frame_switch(c.byref(native_state), buffer, SIZE, ACTOR, frame,
                                             c.byref(ops), None)
            assert bytes(buffer) == bytes(cpu.mem_read(ACTOR, SIZE)), (case, name)
            assert bytes(native_state) == bytes(cpu.mem_read(STATE, 28)), (case, name)
            events = [(e[0], e[1]) if e[0] == 0x4ac8a0 else (e[0], e[1], e[2]) for e in stubs.log]
            assert events == native, (case, name)
            totals[name] = totals.get(name, 0) + 1
    full_report = verify_full(n, original, stubs, args)
    report = {'status': 'passed', 'full_runtime_boundary': full_report, 'complete_original_executions': totals,
              'scope': 'Complete 449360 and 449390 execute in the original (4ac8d0, 4ac710 and '
                       '4ac8a0 stubbed and logged; 4ad530 and 4adfe0 run for real); the whole '
                       'actor, the bounded refresh state at 5bb710 and the ordered calls compare for '
                       'legacy indices -1 and 0..5. Full APIs compare exact EAX, all callback '
                       'registers and callback mutations, every 16-bit refresh index, exact '
                       'raw-memory reads/writes and all262144 bytes of independent globals '
                       'from59b714 through5db713, including signed negative and out-of-range writes.'}
    (args.build_dir / 'actor-frame-switch-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
