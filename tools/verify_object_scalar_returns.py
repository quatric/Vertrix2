"""Prove complete object/piece/player scalar EAX and live address-boundary ordering."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path
from original import Original
from oracle_kit import build
from unicorn import UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE, UC_MEM_READ

U = c.c_uint32
Read = c.CFUNCTYPE(c.c_int, U, c.c_uint, c.POINTER(U), c.c_void_p)
Write = c.CFUNCTYPE(c.c_int, U, c.c_uint, U, c.c_void_p)
SIZE = 0x1000
RAW = (
    (0x418820, 'vertrix_object_set_period_full', 'store', 0xc4),
    (0x418840, 'vertrix_object_set_counter_full', 'store', 0xc0),
    (0x418870, 'vertrix_object_clear_counter_full', 'clear', 0xc0),
    (0x42a940, 'vertrix_piece_clear_offset_x_full', 'clear', 0x16d),
    (0x42a950, 'vertrix_piece_clear_offset_y_full', 'clear', 0x16e),
    (0x42ba40, 'vertrix_object_y_above_limit_full', 'read', 0xb0),
    (0x43b860, 'vertrix_player_set_e0_full', 'store', 0x4e4),
    (0x43b870, 'vertrix_player_e0_full', 'read', 0x4e4),
    (0x43bad0, 'vertrix_player_set_cd_full', 'store', 0x4ce),
    (0x43bae0, 'vertrix_player_set_cc_full', 'store', 0x4cd),
    (0x43cde0, 'vertrix_player_enter_state_full', 'clear', 0x4dd),
)
BOUNDARY = (
    (0x4126d0, 'vertrix_object_toggle_flag_full', 'toggle'),
    (0x4126f0, 'vertrix_object_flag_full', 'flag'),
    (0x43cc90, 'vertrix_player_partner_not_cc_one_full', 'partner'),
    (0x43bd60, 'vertrix_player_partner_free_full', 'partner'),
)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    if args.cases < 1:
        parser.error('--cases must be positive')
    native = build(args.build_dir, 'object-scalar-returns', ['object_scalars.c', 'actor_storage.c'])
    P, SZ = c.c_void_p, c.c_size_t
    for _, name, operation, _ in RAW:
        fn = getattr(native, name)
        fn.argtypes = [P, SZ] + ([U, U] if operation == 'store' else [U] if operation == 'clear' else [])
        fn.restype = U
    native.vertrix_object_toggle_flag_full.argtypes = [U, U, Read, Write, P, c.POINTER(U)]
    native.vertrix_object_flag_full.argtypes = [U, U, Read, P, c.POINTER(U)]
    for name in ('vertrix_player_partner_not_cc_one_full', 'vertrix_player_partner_free_full'):
        getattr(native, name).argtypes = [U, Read, P, c.POINTER(U)]
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(0xfffff000, 0x1000)

    def put(address, data):
        length = min(len(data), 0x100000000 - address)
        cpu.mem_write(address, bytes(data[:length]))
        if length < len(data):
            cpu.mem_write(0, bytes(data[length:]))

    def get(address, size):
        length = min(size, 0x100000000 - address)
        result = bytes(cpu.mem_read(address, length))
        return result + bytes(cpu.mem_read(0, size - length)) if length < size else result

    rng = random.Random(0x43cc90)
    totals = {hex(a): 0 for a, *_ in RAW + BOUNDARY}
    mutation_cases = 0
    for case in range(args.cases):
        token = (0x806000, 0x806025, 0x80a000, 0xfffffffc)[case % 4]
        for address, name, operation, _ in RAW:
            raw = bytearray(rng.randbytes(SIZE))
            value = rng.choice([0, 1, 0xffffffff, rng.getrandbits(32)])
            if address == 0x42ba40:
                signed = (0, 1, 0x7fff, 0x8000, 0xffff)
                struct.pack_into('<H', raw, 0x16, signed[case % 5])
                struct.pack_into('<H', raw, 0xae, signed[(case // 5) % 5])
            put(token, raw)
            storage = c.create_string_buffer(bytes(raw), SIZE)
            expected = original.call(address, eax=token, edx=value)
            params = (token, value) if operation == 'store' else (token,) if operation == 'clear' else ()
            got = getattr(native, name)(storage, SIZE, *params)
            assert got == expected and storage.raw == get(token, SIZE), (case, hex(address), got, expected)
            totals[hex(address)] += 1
        for address, name, operation in BOUNDARY:
            index = (0, 1, 0x40000000, 0xffffffff, 0xfffffe8d, 0x80000001)[case % 6]
            if operation == 'partner':
                partner = (0x807000, token, 0xfffffffc, 0xffffffff)[case % 4]
                handle_address = (token + 0x3b0) & 0xffffffff
                byte_address = (partner + 0x4cc) & 0xffffffff
                cells = {handle_address: (4, 0x808000), byte_address: (1, rng.getrandbits(8))}
                # The first read obtains the updated handle. The second keeps that captured
                # handle even when the owner's partner changes before the byte is read.
                updates = [(handle_address, partner), (handle_address, 0x808000),
                           (byte_address, (0, 1, 4, 255)[case % 4])]
            else:
                cell_address = (token + index * 4 + 0x5cc) & 0xffffffff
                cells = {cell_address: (4, rng.getrandbits(32))}
                updates = [(cell_address, (0, 1, 2, 0xffffffff)[case % 4]),
                           (cell_address, rng.getrandbits(32))]
            for location, (width, value) in cells.items():
                put(location, value.to_bytes(width, 'little'))
            model = dict(cells)
            original_log, native_log = [], []

            def mutate(step, guest):
                changes = updates[:1] if step == 0 else updates[1:]
                for location, value in changes:
                    width = cells[location][0]
                    if guest:
                        put(location, value.to_bytes(width, 'little'))
                    else:
                        model[location] = (width, value)

            def memory_event(cpu, access, location, width, value, context):
                if location not in cells:
                    return
                assert cells[location][0] == width
                mutate(len(original_log), True)
                if access == UC_MEM_READ:
                    value = int.from_bytes(get(location, width), 'little')
                    kind = 'read'
                else:
                    kind = 'write'
                original_log.append((kind, location, width, value))

            hook = cpu.hook_add(UC_HOOK_MEM_READ | UC_HOOK_MEM_WRITE, memory_event)
            try:
                expected = original.call(address, eax=token, edx=index)
            finally:
                cpu.hook_del(hook)

            @Read
            def read(location, width, out, context):
                assert location in model and model[location][0] == width
                mutate(len(native_log), False)
                value = model[location][1]
                native_log.append(('read', location, width, value))
                out[0] = value
                return 1

            @Write
            def write(location, width, value, context):
                assert location in model and model[location][0] == width
                mutate(len(native_log), False)
                native_log.append(('write', location, width, value))
                model[location] = (width, value)
                return 1

            out = U(0x12345678)
            fn = getattr(native, name)
            params = (token, index, read, write, None, c.byref(out)) if operation == 'toggle' else (
                (token, index, read, None, c.byref(out)) if operation == 'flag' else
                (token, read, None, c.byref(out)))
            assert fn(*params) and out.value == expected, (case, name, out.value, expected)
            assert native_log == original_log, (case, name, native_log, original_log)
            assert all(value == int.from_bytes(get(location, width), 'little')
                       for location, (width, value) in model.items()), (case, name, 'memory')
            assert len(original_log) == (1 if operation == 'flag' else 2), (case, name, 'coverage')
            totals[hex(address)] += 1
            mutation_cases += 1
    assert totals == {hex(a): args.cases for a, *_ in RAW + BOUNDARY}
    assert sum(totals.values()) == args.cases * 15
    assert mutation_cases == args.cases * 4
    guards = 0
    for _, name, operation, extent in RAW:
        raw = rng.randbytes(SIZE)
        storage = c.create_string_buffer(raw, SIZE)
        params = (0x806000, 0xffffffff) if operation == 'store' else (0x806000,) if operation == 'clear' else ()
        for pointer, size in ((storage, extent - 1), (None, SIZE)):
            assert getattr(native, name)(pointer, size, *params) == 0
            assert storage.raw == raw
            guards += 1
    for _, name, operation in BOUNDARY:
        for fault in ('null_read', 'null_result', 'fail_first', 'fail_second', 'null_write'):
            if operation == 'flag' and fault in ('fail_second', 'null_write'):
                continue
            if operation == 'partner' and fault == 'null_write':
                continue
            events = []

            @Read
            def guarded_read(location, width, out, context):
                events.append(('read', location, width))
                if fault == 'fail_first' or (fault == 'fail_second' and len(events) == 2):
                    return 0
                out[0] = 0x807000 if operation == 'partner' and len(events) == 1 else 1
                return 1

            @Write
            def guarded_write(location, width, value, context):
                events.append(('write', location, width, value))
                return 0 if fault == 'fail_second' else 1

            out = U(0x89abcdef)
            read = Read() if fault == 'null_read' else guarded_read
            write = Write() if fault == 'null_write' else guarded_write
            result = None if fault == 'null_result' else c.byref(out)
            params = (0x806000, 0, read, write, None, result) if operation == 'toggle' else (
                (0x806000, 0, read, None, result) if operation == 'flag' else
                (0x806000, read, None, result))
            assert not getattr(native, name)(*params), (name, fault)
            assert out.value == 0x89abcdef, (name, fault, 'result changed')
            expected_events = 0 if fault.startswith('null_') else 1 if fault == 'fail_first' else 2
            assert len(events) == expected_events, (name, fault, events)
            guards += 1
    assert guards == 38
    report = {
        'status': 'passed', 'complete_original_executions': totals,
        'exact_eax_comparisons': sum(totals.values()),
        'live_memory_boundary_trace_comparisons': mutation_cases,
        'native_invalid_storage_boundary_guards': guards,
        'scope': 'All 15 original entrypoints execute unchanged through complete normal returns. '
                 'Eleven bounded full APIs compare exact EAX and all 0x1000 actor bytes. Four '
                 'address-boundary APIs compare exact EAX, ordered read/write address-width-value '
                 'traces and complete supplied memory cells, with mutations before every memory '
                 'event. Indexed multiplication and effective addresses wrap in 32 bits; toggle '
                 'returns object+index*4. Partner pointers are captured before the second read '
                 'even when the owner pointer then changes. Fixtures include self-partners, '
                 'high/wrapping object and partner tokens, signed-word comparison edges, full-width '
                 'indexed parameters and truncated byte writes. Availability errors preserve '
                 'the output token and stop at the failed boundary. Duplicate projected helpers '
                 '43b970/43bd40/418830 retain separate accessor canonical full APIs. Existing '
                 'global full APIs, compare_unsigned and table_used_count are outside this report.'}
    (args.build_dir / 'object-scalar-returns-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
