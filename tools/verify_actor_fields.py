"""Compare full actor field entrypoints, including original EAX and whole storage."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, STACK
from unicorn.x86_const import (UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX,
                              UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP,
                              UC_X86_REG_ESP)

ACTOR = 0x801000
SIZE = 0x1000
# Address, complete API suffix, operation, field offset, required native storage extent.
ROUTINES = (
    (0x4ac510, 'clear_field', 'clear', 0xbc, 0xc0),
    (0x4ac380, 'clear_field', 'clear', 0xcc, 0xd0),
    (0x4ac700, 'clear_field', 'clear', 0xb8, 0xbc),
    (0x4ac7d0, 'store_field', 'store', 0xc0, 0xc4),
    (0x4ac8f0, 'store_field', 'store', 0x154, 0x158),
    (0x4ac490, 'store_field', 'store', 0xd0, 0xd4),
    (0x4ac710, 'store_field', 'store', 0xb8, 0xbc),
    (0x4ac860, 'store_field', 'store', 0xe0, 0xe4),
    (0x4ac910, 'store_field', 'store', 0xec, 0xf0),
    (0x4ac930, 'store_field', 'store', 0xf0, 0xf4),
    (0x4ac950, 'store_field', 'store', 0xb4, 0xb8),
    (0x4ac4f0, 'store_field', 'store', 0x11c, 0x120),
    (0x4ac740, 'step_frame', 'increment', 0xb8, 0xbc),
    (0x4ac750, 'step_frame', 'decrement', 0xb8, 0xbc),
    (0x4ac900, 'read_field', 'read', 0x154, 0x158),
    (0x4ac960, 'read_field', 'read', 0xb4, 0xb8),
    (0x4ac540, 'divide_counter', 'divide', 0xbc, 0xc4),
    (0x4ac640, 'divide_counter', 'divide', 0xdc, 0xe4),
    (0x4ac7a0, 'test_frame_zero', 'test', 0xb8, 0xbc),
    (0x4ac4e0, 'store_pair_114', 'pair', 0x114, 0x11c),
    (0x4ad510, 'store_word_triple', 'words', 0x2a, 0x30),
    (0x4ad520, 'store_word_triple', 'words', 0x3a, 0x40),
    (0x4b54d0, 'store_box', 'box', 0xe, 0xfc),
)


FULL_NAMES = {4900112: 'vertrix_actor_clear_counter_full',
 4899712: 'vertrix_actor_clear_cc_full',
 4900608: 'vertrix_actor_reset_frame_counter_full',
 4900816: 'vertrix_actor_set_period_full',
 4901104: 'vertrix_actor_set_handler_full',
 4899984: 'vertrix_actor_set_d0_full',
 4900624: 'vertrix_actor_set_frame_index_full',
 4900960: 'vertrix_actor_set_e0_full',
 4901136: 'vertrix_actor_set_ec_full',
 4901168: 'vertrix_actor_set_f0_full',
 4901200: 'vertrix_actor_set_b4_full',
 4900080: 'vertrix_actor_set_11c_full',
 4900672: 'vertrix_actor_next_frame_counter_full',
 4900688: 'vertrix_actor_previous_frame_counter_full',
 4901120: 'vertrix_actor_get_handler_full',
 4901216: 'vertrix_actor_get_b4_full',
 4900160: 'vertrix_actor_counter_quotient_full',
 4900416: 'vertrix_actor_progress_quotient_full',
 4900768: 'vertrix_actor_frame_counter_is_zero_full',
 4900064: 'vertrix_actor_set_114_full',
 4904208: 'vertrix_actor_set_words_2a_full',
 4904224: 'vertrix_actor_set_words_3a_full',
 4936912: 'vertrix_actor_set_box_full'}
FULL_ARITIES = {'vertrix_actor_clear_counter_full': 1,
 'vertrix_actor_clear_cc_full': 1,
 'vertrix_actor_reset_frame_counter_full': 1,
 'vertrix_actor_set_period_full': 2,
 'vertrix_actor_set_handler_full': 2,
 'vertrix_actor_set_d0_full': 2,
 'vertrix_actor_set_frame_index_full': 2,
 'vertrix_actor_set_e0_full': 2,
 'vertrix_actor_set_ec_full': 2,
 'vertrix_actor_set_f0_full': 2,
 'vertrix_actor_set_b4_full': 2,
 'vertrix_actor_set_11c_full': 2,
 'vertrix_actor_next_frame_counter_full': 1,
 'vertrix_actor_previous_frame_counter_full': 1,
 'vertrix_actor_get_handler_full': 0,
 'vertrix_actor_get_b4_full': 0,
 'vertrix_actor_counter_quotient_full': 0,
 'vertrix_actor_progress_quotient_full': 0,
 'vertrix_actor_frame_counter_is_zero_full': 0,
 'vertrix_actor_set_114_full': 3,
 'vertrix_actor_set_words_2a_full': 4,
 'vertrix_actor_set_words_3a_full': 4,
 'vertrix_actor_set_box_full': 4}

def full_parameters(operation, token, values):
    edx, ebx, ecx, height = values
    return {
        'clear': (token,), 'store': (token, edx),
        'increment': (token,), 'decrement': (token,),
        'read': (), 'divide': (), 'test': (),
        'pair': (token, ebx, edx), 'words': (token, edx, ebx, ecx),
        'box': (edx, ebx, ecx, height),
    }[operation]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    if args.cases < 1:
        parser.error('--cases must be positive')
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'actor-fields.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    str(source / 'actor_fields.c'), str(source / 'actor_storage.c'),
                    '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    arities = {'clear_field': 2, 'store_field': 3, 'step_frame': 2, 'read_field': 1,
               'divide_counter': 2, 'test_frame_zero': 0, 'store_pair_114': 3,
               'store_word_triple': 5, 'store_box': 4}
    for name, arity in arities.items():
        fn = getattr(native, 'vertrix_actor_' + name)
        fn.argtypes = [c.c_void_p, c.c_size_t] + [c.c_uint32] * arity
        fn.restype = c.c_uint32
    for name, arity in FULL_ARITIES.items():
        fn = getattr(native, name)
        fn.argtypes = [c.c_void_p, c.c_size_t] + [c.c_uint32] * arity
        fn.restype = c.c_uint32
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(0xfffff000, 0x1000)

    def write_object(token, data):
        length = min(len(data), 0x100000000 - token)
        cpu.mem_write(token, bytes(data[:length]))
        if length < len(data):
            cpu.mem_write(0, bytes(data[length:]))

    def read_object(token):
        length = min(SIZE, 0x100000000 - token)
        data = bytes(cpu.mem_read(token, length))
        return data + bytes(cpu.mem_read(0, SIZE - length)) if length < SIZE else data

    rng = random.Random(0x4ac8f0)
    totals = {f'0x{a:06x}': 0 for a, *_ in ROUTINES}
    preserved = (UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX,
                 UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP)
    for case in range(args.cases):
        token = (ACTOR, ACTOR + 37, ACTOR + 0x4000, 0xfffffffc)[case % 4]
        for address, name, operation, offset, extent in ROUTINES:
            raw = bytearray(rng.randbytes(SIZE))
            values = tuple(rng.getrandbits(32) for _ in range(4))
            # Explicit zero, full-width and wrapping boundary values supplement randomness.
            edges = (0, 1, 0xffffffff, 0x80000000)
            if case % 8 < 4:
                struct.pack_into('<I', raw, offset, edges[case % 8])
                values = (edges[case % 8],) + values[1:]
            if operation == 'divide' and case % 4 < 3:
                struct.pack_into('<I', raw, offset + 4, (0, 1, 0xffffffff)[case % 4])
            write_object(token, raw)
            actor = c.create_string_buffer(bytes(raw), SIZE)
            others = tuple(rng.getrandbits(32) for _ in range(3))
            for register, value in zip(preserved[3:], others):
                cpu.reg_write(register, value)
            expected = original.call(address, eax=token, edx=values[0], ebx=values[1],
                                     ecx=values[2], args=(values[3],) if operation == 'box' else ())
            params = full_parameters(operation, token, values)
            result = getattr(native, FULL_NAMES[address])(actor, SIZE, *params)
            assert result == expected, (case, hex(address), 'eax', result, expected)
            assert actor.raw == read_object(token), (case, hex(address), 'whole storage')
            assert tuple(cpu.reg_read(reg) for reg in preserved) == values[:3] + others, (
                case, hex(address), 'preserved registers')
            assert cpu.reg_read(UC_X86_REG_ESP) == STACK + (8 if operation == 'box' else 4), (
                case, hex(address), 'stack cleanup')
            totals[f'0x{address:06x}'] += 1
    expected_counts = {f'0x{a:06x}': args.cases for a, *_ in ROUTINES}
    assert totals == expected_counts and sum(totals.values()) == len(ROUTINES) * args.cases
    guards = 0
    for address, name, operation, offset, extent in ROUTINES:
        raw = rng.randbytes(SIZE)
        actor = c.create_string_buffer(raw, SIZE)
        params = full_parameters(operation, ACTOR, (0xffffffff,) * 4)
        fn = getattr(native, FULL_NAMES[address])
        for storage, size in ((actor, extent - 1), (None, SIZE)):
            assert fn(storage, size, *params) == 0, (hex(address), 'invalid storage result')
            assert actor.raw == raw, (hex(address), 'invalid storage mutation')
            guards += 1
    # Bounded generic field APIs must also reject overflowing/out-of-bounds offsets.
    for name, params in (('clear_field', (ACTOR, 0xffffffff)),
                         ('store_field', (ACTOR, 0xffffffff, 1)),
                         ('read_field', (0xffffffff,)),
                         ('divide_counter', (0xbc, 0xffffffff)),
                         ('store_word_triple', (ACTOR, 0xffffffff, 1, 2, 3))):
        actor = c.create_string_buffer(raw, SIZE)
        assert getattr(native, "vertrix_actor_" + name)(actor, SIZE, *params) == 0
        assert actor.raw == raw
        guards += 1
    assert guards == 51
    report = {
        'status': 'passed', 'complete_original_executions': totals,
        'exact_eax_and_whole_storage_comparisons': sum(totals.values()),
        'preserved_register_and_stack_comparisons': sum(totals.values()),
        'native_invalid_storage_guard_cases': guards,
        'scope': 'All 23 listed complete original entrypoints execute unchanged through normal '
                 'return. Exact 32-bit EAX and every byte of 0x1000 actor storage compare against '
                 'the individually named full native APIs. Original EDX/EBX/ECX/ESI/EDI/EBP preservation and stack '
                 'cleanup are checked separately. '
                 'Guest object tokens include unaligned storage and 0xfffffffc with wrapping '
                 'guest memory. Fixtures cover unsigned division with zero divisor treated as '
                 'one, frame counter wrap, full-width scalar values and truncated word stores. '
                 'Box EAX is the zero-extended height, not the object token. Legacy status-only '
                 'helpers remain fragments and are not claimed to preserve original EAX. '
                 'Invalid native storage/offsets return zero without writes.'}
    (build / 'actor-fields-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
