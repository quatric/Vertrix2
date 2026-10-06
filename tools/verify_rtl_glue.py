"""Compare the original Delphi runtime wrappers with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from unicorn.x86_const import UC_X86_REG_DS, UC_X86_REG_EAX, UC_X86_REG_EDX
from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
S = c.c_int32
SIZE = 0x200


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(14)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


RECORD_ROUTINES = (0x4ce780, 0x4ce220, 0x4ce740, 0x4cba70)
CALLEES = RECORD_ROUTINES + (0x4db719, 0x4db710, 0x4db7c8, 0x4c9b6a, 0x4dd3e0, 0x4ddbe0, 0x4ded70,
                             0x4eb5c0, 0x4d49a0, 0x4e0eaf, 0x4e0ec7, 0x4ca370, 0x4ca110, 0x4ca0d0,
                             0x4d67e4, 0x4ce9c0, 0x4dba20, 0x4cf880, 0x4cce90, 0x4d79c0, 0x4cbf90, 0x4cea15, 0x4ca5a0, 0x4ca2e0, 0x4da71b, 0x4dad38, 0x4e2434, 0x4dacd0, 0x4df1c0, 0x4dbcd0, 0x4ca060, 0x4eb5e0, 0x4ca150, 0x4d1890, 0x4df0f0, 0x4d9ae0, 0x4d9a10, 0x4db507, 0x4db6a4, 0x48a930, 0x4d85c0, 0x4daae8, 0x4ca600, 0x478d10, 0x4e6220, 0x4eb4d4, 0x4e6250, 0x4e10d0, 0x4e1054, 0x4e1140, 0x4e39a0, 0x4e39d0, 0x4e39f0, 0x4ca070, 0x4e14b0, 0x4e14b7, 0x4cd56c, 0x4d85f0, 0x4def50, 0x4d3e20, 0x4db950, 0x4e53b4, 0x4db131, 0x4e543c, 0x4da3ba, 0x4d3010, 0x4df320, 0x4e0f8b, 0x4cd8b0,
                             0x4de900, 0x4cccc0, 0x4cf800, 0x4d1ae0, 0x4cf850)
ARGUMENTS = {0x4db950: 3, 0x4ca150: 1, 0x4d1890: 1, 0x4d85c0: 1, 0x4daae8: 1, 0x4d9ae0: 3, 0x4d9a10: 1, 0x4d1ae0: 6}
VAR, TEXT, POINTED = 0x800500, 0x800610, 0x800400


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'rtl-glue', ['rtl_glue.c', 'call_glue.c', 'actor_storage.c'])
    P, V = c.POINTER(Calls), c.POINTER(Services)
    r = [U, U, U, U]
    for name, types in (
            ('record_field', [V, U, U, U, U, U, U]), ('record_increment', [V] + r), ('record_set_argument', [V] + r + [U]),
            ('record_mark', [V] + r), ('scope_refresh', [V] + r), ('flagged_call', [U, U, U] + r), ('pair_call', [U, U, U, U]),
            ('zero_call', [U, U, U]), ('deref_call', [U, U, U, U]), ('chain_call', [U, U, U]),
            ('stream_init_derived', [V, U, U, U]), ('block_call', [U, U, U]),
            ('terminate_call', [U, U, U, c.c_void_p, c.c_size_t]), ('local_call', [U, U, U, U]),
            ('mode_call', [U, U, U, U]), ('release_inner', [U, U, U, U]),
            ('record_forward', [U, U, U]), ('triple_call', [U, U, U]),
            ('write_text_call', [U, U, U, U]), ('string_unique', [U, U, S, U, U]), ('string_reserve', [U, U, U, S, U, U])):
        function = getattr(n, 'vertrix_rtl_' + name)
        function.argtypes = [P] + types
        function.restype = U
    n.vertrix_rtl_byte_local_call.argtypes = [P, U, U, U]
    n.vertrix_rtl_byte_local_call.restype = U
    n.vertrix_rtl_swapped_call.argtypes = [P, U, U, U]
    n.vertrix_rtl_swapped_call.restype = U
    n.vertrix_rtl_static_init_call.argtypes = [P, U, U, U, U]
    n.vertrix_rtl_static_init_call.restype = U
    n.vertrix_rtl_ebx_from_edx_call.argtypes = [P, U, U, U]
    n.vertrix_rtl_ebx_from_edx_call.restype = U
    n.vertrix_rtl_copy_blocks.argtypes = [c.c_void_p, c.c_void_p, U]
    n.vertrix_rtl_copy_blocks.restype = U
    n.vertrix_rtl_sign_of.argtypes = [U]
    n.vertrix_rtl_sign_of.restype = U
    n.vertrix_rtl_stack_pair_call.argtypes = [P, U, U, U, U, U]
    n.vertrix_rtl_stack_pair_call.restype = U
    n.vertrix_rtl_flags_call.argtypes = [P, U, U, U, U]
    n.vertrix_rtl_flags_call.restype = U
    n.vertrix_rtl_scratch_triple_call.argtypes = [P, U, U, U, U, U]
    n.vertrix_rtl_scratch_triple_call.restype = U
    n.vertrix_rtl_zero_call3.argtypes = [P, U]
    n.vertrix_rtl_zero_call3.restype = U
    for name in ('list', 'flag'):
        getattr(n, 'vertrix_rtl_construct_' + name).argtypes = [U, c.c_void_p]
        getattr(n, 'vertrix_rtl_construct_' + name).restype = U
    n.vertrix_rtl_select_float_helpers.argtypes = [c.c_uint8, c.c_uint8, c.POINTER(U * 3)]
    n.vertrix_rtl_select_float_helpers.restype = None
    n.vertrix_rtl_construct_chunk_list.argtypes = [U, c.c_void_p, U, U]
    n.vertrix_rtl_construct_chunk_list.restype = U
    for name in ('list_head', 'string_member'):
        getattr(n, 'vertrix_rtl_release_' + name).argtypes = [P, V, U, U]
        getattr(n, 'vertrix_rtl_release_' + name).restype = U
    n.vertrix_rtl_lookup_call.argtypes = [P, V, U, U, U, U]
    n.vertrix_rtl_lookup_call.restype = U
    n.vertrix_rtl_distribute_slack.argtypes = [U, c.c_void_p, c.c_size_t]
    n.vertrix_rtl_distribute_slack.restype = U
    n.vertrix_rtl_construct_table.argtypes = [U, c.c_void_p, U]
    n.vertrix_rtl_construct_table.restype = U
    n.vertrix_rtl_probe_call.argtypes = [P, V, U, U, U]
    n.vertrix_rtl_probe_call.restype = U
    n.vertrix_rtl_integer_to_double.argtypes = [U]
    n.vertrix_rtl_integer_to_double.restype = c.c_uint64
    n.vertrix_rtl_float_to_integer.argtypes = [U, c.c_uint8]
    n.vertrix_rtl_float_to_integer.restype = U
    n.vertrix_rtl_string_append_pair.argtypes = [P, V, U, U, U, U, U]
    n.vertrix_rtl_string_append_pair.restype = U
    n.vertrix_rtl_string_fill.argtypes = [P, V, U, U, U, U]
    n.vertrix_rtl_string_fill.restype = U
    n.vertrix_rtl_string_copy_pair.argtypes = [P, V, U, U, U, U, U]
    n.vertrix_rtl_string_copy_pair.restype = U
    n.vertrix_rtl_string_unique_size.argtypes = [P, V, U, U, U]
    n.vertrix_rtl_string_unique_size.restype = U
    n.vertrix_rtl_string_set_length.argtypes = [P, V, U, U]
    n.vertrix_rtl_string_set_length.restype = U
    n.vertrix_rtl_construct_buffer_stream.argtypes = [P, V, U, U, c.c_int]
    n.vertrix_rtl_construct_buffer_stream.restype = U
    n.vertrix_rtl_string_make_unique.argtypes = [P, V, U, U]
    n.vertrix_rtl_string_make_unique.restype = U
    n.vertrix_rtl_class_chain_contains.argtypes = [V, U, U]
    n.vertrix_rtl_class_chain_contains.restype = U
    n.vertrix_rtl_wide_length.argtypes = [c.c_void_p]
    n.vertrix_rtl_wide_length.restype = U
    n.vertrix_rtl_ancestor_search.argtypes = [P, U, U, U, U]
    n.vertrix_rtl_ancestor_search.restype = U
    n.vertrix_rtl_table_lookup_value.argtypes = [P, V, U, U, U, U]
    n.vertrix_rtl_table_lookup_value.restype = U
    n.vertrix_rtl_forward_pair.argtypes = [P, U, U, U, U, U]
    n.vertrix_rtl_forward_pair.restype = U
    n.vertrix_rtl_link_owner.argtypes = [P, V, U, U, U]
    n.vertrix_rtl_link_owner.restype = U
    n.vertrix_rtl_range_table_find.argtypes = [c.c_void_p, c.c_size_t, U, U, U, U]
    n.vertrix_rtl_range_table_find.restype = U
    n.vertrix_rtl_bracket_call.argtypes = [P, U, U, U, U]
    n.vertrix_rtl_bracket_call.restype = U
    n.vertrix_rtl_construct_derived_stream.argtypes = [P, V, U, U, U, U]
    n.vertrix_rtl_construct_derived_stream.restype = U
    n.vertrix_rtl_construct_event_table.argtypes = [P, V, U, U, U, U]
    n.vertrix_rtl_construct_event_table.restype = U
    n.vertrix_rtl_store_in_slot.argtypes = [P, V, U, U, U]
    n.vertrix_rtl_store_in_slot.restype = U
    n.vertrix_rtl_vararg_call.argtypes = [P, U, U, U, U]
    n.vertrix_rtl_vararg_call.restype = U
    n.vertrix_rtl_test_and_set.argtypes = [P, V, U, U]
    n.vertrix_rtl_test_and_set.restype = U
    n.vertrix_rtl_local_chain_call.argtypes = [P, U, U, U, U, U]
    n.vertrix_rtl_local_chain_call.restype = U
    n.vertrix_rtl_string_concat.argtypes = [P, V, U, U, U, U, U]
    n.vertrix_rtl_string_concat.restype = U
    n.vertrix_rtl_split_exponent.argtypes = [U, U, c.POINTER(U)]
    n.vertrix_rtl_split_exponent.restype = c.c_uint64
    n.vertrix_rtl_parse_integer.argtypes = [c.c_void_p]
    n.vertrix_rtl_parse_integer.restype = U
    n.vertrix_rtl_copy_terminated.argtypes = [P, V, U, U, U, U]
    n.vertrix_rtl_copy_terminated.restype = U
    for name in ('end', 'start'):
        getattr(n, 'vertrix_rtl_string_trim_' + name).argtypes = [P, V, U, U, U]
        getattr(n, 'vertrix_rtl_string_trim_' + name).restype = U
    n.vertrix_rtl_segment_dispatch.argtypes = [P, U, U, U]
    n.vertrix_rtl_segment_dispatch.restype = U
    for name in ('negate', 'absolute'):
        getattr(n, 'vertrix_rtl_' + name + '_double').argtypes = [U, U]
        getattr(n, 'vertrix_rtl_' + name + '_double').restype = c.c_uint64
    n.vertrix_rtl_parse_format_flags.argtypes = [c.c_void_p, U, c.c_void_p, c.c_size_t]
    n.vertrix_rtl_parse_format_flags.restype = U
    n.vertrix_rtl_string_tail.argtypes = [P, V, U, U, U, U]
    n.vertrix_rtl_string_tail.restype = U
    n.vertrix_record_copy.argtypes = [U, c.c_void_p, c.c_void_p]
    n.vertrix_record_copy.restype = U
    n.vertrix_record_prefix_sum.argtypes = [U, U, c.c_void_p]
    n.vertrix_record_prefix_sum.restype = None
    n.vertrix_rle_decode.argtypes = [P, U, U, U, U, U, c.c_void_p]
    n.vertrix_rle_decode.restype = U
    n.vertrix_rle_decode_bitmap.argtypes = [P, V, U, U, U, U, U, c.c_void_p]
    n.vertrix_rle_decode_bitmap.restype = U
    n.vertrix_path_split_a.argtypes = [P, U, c.c_void_p, c.c_void_p]
    n.vertrix_path_split_b.argtypes = [P, U, U, c.c_void_p, c.c_void_p]
    n.vertrix_path_split_c.argtypes = [P, c.c_void_p, U, U, U, U, c.c_void_p]
    for name in ('a', 'b', 'c'):
        getattr(n, 'vertrix_path_split_' + name).restype = U
    n.vertrix_rtl_stream_init.argtypes = [V, U]
    n.vertrix_rtl_stream_init.restype = U
    n.vertrix_rtl_class_address.argtypes = []
    n.vertrix_rtl_class_address.restype = U
    n.vertrix_rtl_record_clear.argtypes = [V, U]
    n.vertrix_rtl_record_clear.restype = U
    n.vertrix_rtl_sign_compare.argtypes = [U, U]
    n.vertrix_rtl_sign_compare.restype = U
    n.vertrix_round_up.argtypes = [S, S]
    n.vertrix_round_up.restype = S
    original = Original(args.executable)
    pure = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4cbe80)
    pool = Pool(cpu, 4, SIZE)
    services = Services(pool.resolve)
    returns, native_log, replay = [], [], []

    rle_bytes, rle_plan = [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x48a930:
            value = rle_plan.pop(0)
            rle_bytes.append(value)
            cpu.mem_write(edx, bytes([value]))
        returns.append(rng.choice(pool.handles) if address in RECORD_ROUTINES or address in (0x4ca060, 0x4d3e20, 0x478d10, 0x4cf800)
                       else rng.choice(pool.handles + [0]) if address in (0x4df0f0, 0x4d85f0)
                       else rng.randrange(0, 8) if address == 0x4df320
                       else rng.choice([0, 1]) if address == 0x4e10d0
                       else eax + 1 if address == 0x4e1054
                       else rng.randrange(0, 0x100) if address == 0x4e39f0
                       else rng.choice([0, 0, ebx, ebx, rng.getrandbits(32)]) if address == 0x4d1890
                       else rng.choice([0, rng.getrandbits(32)]) if address == 0x4db950
                       else rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address in CALLEES:
        stubs.add(address, ARGUMENTS.get(address, 0), address == 0x4d85c0)

    @Call
    def call(site, context):
        s = site.contents
        if s.target == 0x48a930:
            s.out_value = rle_bytes.pop(0)
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) +
                          (s.stack, s.stack_next, s.stack_third, s.rest0, s.rest1, s.rest2)[:ARGUMENTS.get(s.target, 0)])
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}

    def run(address, native, compare=True, **registers):
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(address, **registers) & 0xffffffff
        replay[:] = list(returns)
        got = native()
        assert not compare or got == result, (hex(address), hex(got), hex(result))
        assert native_log == stubs.log, (hex(address), native_log, stubs.log)
        assert not replay and pool.same(), (hex(address), pool.diff())
        totals[hex(address)] = totals.get(hex(address), 0) + 1

    def patch(handle, data):
        for offset in (4, 0x1c):
            if rng.random() < 0.3:
                struct.pack_into('<I', data, offset, 0)

    byref_c, byref_s = c.byref(calls), c.byref(services)
    for case in range(args.cases):
        pool.fill(rng, patch)
        eax, edx, ebx, ecx = (rng.getrandbits(32) for _ in range(4))
        regs = dict(eax=eax, edx=edx, ebx=ebx, ecx=ecx)
        run(0x4cbe80, lambda: n.vertrix_rtl_record_field(byref_c, byref_s, 0x4ce780, 4, eax, edx, ebx, ecx),
            **regs)
        run(0x4cba60, lambda: n.vertrix_rtl_record_field(byref_c, byref_s, 0x4ce220, 0xc8, eax, edx, ebx,
                                                  ecx), **regs)
        run(0x4dec60, lambda: n.vertrix_rtl_record_increment(byref_c, byref_s, eax, edx, ebx, ecx), **regs)
        argument = rng.getrandbits(32)
        run(0x4dd170, lambda: n.vertrix_rtl_record_set_argument(byref_c, byref_s, eax, edx, ebx, ecx,
                                                         argument), args=(argument,), **regs)
        scope_object = rng.choice(pool.handles)
        for handle in pool.handles:
            value = struct.pack('<I', rng.choice([scope_object, rng.getrandbits(32)]))
            cpu.mem_write(handle + 0x1c, value)
            pool.buffers[handle][0x1c:0x20] = value
            for offset in (4, 8, 0xc):
                value = struct.pack('<I', rng.choice(pool.handles))
                cpu.mem_write(handle + offset, value)
                pool.buffers[handle][offset:offset + 4] = value
        run(0x4d2390, lambda: n.vertrix_rtl_scope_refresh(byref_c, byref_s, scope_object, edx, ebx, ecx),
            eax=scope_object, edx=edx, ebx=ebx, ecx=ecx)
        run(0x4d16b0, lambda: n.vertrix_rtl_record_mark(byref_c, byref_s, eax, edx, ebx, ecx), **regs)
        flag = rng.choice([0, 1, 7])
        cpu.mem_write(0x5054a1, bytes([flag]))
        for address, direct, fallback in ((0x4c9daf, 0x4db719, 0), (0x4c9dd6, 0x4db710, 2),
                                          (0x4c9e00, 0x4db7c8, 1)):
            run(address, lambda: n.vertrix_rtl_flagged_call(byref_c, flag, direct, fallback, eax,
                                                            edx, ebx, ecx), **regs)
        for address, first in ((0x4dd440, 0x4dd3e0), (0x4ddc40, 0x4ddbe0)):
            run(address, lambda: n.vertrix_rtl_pair_call(byref_c, first, argument, ebx, ecx),
                eax=eax, edx=edx, ebx=ebx, ecx=ecx, args=(argument,))
        run(0x4c98f0, lambda: n.vertrix_rtl_zero_call(byref_c, eax, edx, ecx), **regs)
        pointed = rng.getrandbits(32)
        cpu.mem_write(POINTED, struct.pack('<I', pointed))
        run(0x4d4990, lambda: n.vertrix_rtl_deref_call(byref_c, eax, POINTED, pointed, ecx),
            eax=eax, edx=POINTED, ebx=ebx, ecx=ecx)
        run(0x4cd836, lambda: n.vertrix_rtl_chain_call(byref_c, eax, edx, ebx), **regs)
        refcount, capacity = rng.choice([-1, 0, 1, 2]), rng.randrange(-3, 6)
        cpu.mem_write(VAR, struct.pack('<I', TEXT))
        cpu.mem_write(TEXT - 0xc, struct.pack('<iII', refcount, 0, 0) + struct.pack('<i', 0))
        cpu.mem_write(TEXT - 0x4, struct.pack('<i', capacity))
        run(0x4ca180, lambda: n.vertrix_rtl_string_unique(byref_c, VAR, TEXT, refcount, ebx, ecx),
            eax=VAR, edx=edx, ebx=ebx, ecx=ecx)
        want = rng.randrange(-3, 6)
        run(0x4ca1e0, lambda: n.vertrix_rtl_string_reserve(byref_c, VAR, TEXT, want & 0xffffffff,
                                                          refcount, capacity, ebx),
            eax=VAR, edx=want & 0xffffffff, ebx=ebx, ecx=ecx)
        record = rng.choice(pool.handles)
        run(0x4cb460, lambda: n.vertrix_rtl_stream_init(byref_s, record), eax=record, edx=edx)
        record = rng.choice(pool.handles)
        run(0x4cbf10, lambda: n.vertrix_rtl_stream_init_derived(byref_c, byref_s, record, ebx, ecx),
            eax=record, ebx=ebx, ecx=ecx)
        header = rng.getrandbits(32)
        cpu.mem_write(0x800800, struct.pack('<I', header))
        for block in (0, 0x800804):
            run(0x4ccb9f, lambda: n.vertrix_rtl_block_call(byref_c, block, edx, header if block
                                                           else 0), eax=block, edx=edx, ebx=ebx,
                ecx=ecx)
        text_buffer = c.create_string_buffer(rng.randbytes(16).replace(b'\0', b'z'), 16)
        cpu.mem_write(0x800700, text_buffer.raw)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x4cd0a4, eax=0x800700, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_rtl_terminate_call(byref_c, 0x800700, edx, ebx, text_buffer, 16)
        assert got == result and native_log == stubs.log, ('terminate', case)
        assert text_buffer.raw == bytes(cpu.mem_read(0x800700, 16)), case
        totals['0x4cd0a4'] = totals.get('0x4cd0a4', 0) + 1
        run(0x4cd9f0, lambda: n.vertrix_rtl_local_call(byref_c, STACK - 0x14, eax, edx, ebx),
            **regs)
        run(0x4d67b2, lambda: n.vertrix_rtl_mode_call(byref_c, eax, edx, ebx, ecx), **regs)
        inner = rng.choice([0, rng.getrandbits(32)])
        cpu.mem_write(0x800a00, struct.pack('<I', inner))
        run(0x4ce9fd, lambda: n.vertrix_rtl_release_inner(byref_c, 0x800a00, inner, edx, ebx),
            eax=0x800a00, edx=edx, ebx=ebx, ecx=ecx)
        for address, target in ((0x4ca630, 0x4ca5a0), (0x4cdad0, 0x4ca2e0)):
            run(address, lambda: n.vertrix_rtl_byte_local_call(byref_c, target, STACK - 0xc, eax),
                **regs)
        run(0x4d3020, lambda: n.vertrix_rtl_swapped_call(byref_c, eax, edx, ebx), **regs)
        run(0x4d3020, lambda: n.vertrix_rtl_swapped_call(byref_c, eax, 0, ebx), eax=eax, edx=0, ebx=ebx,
            ecx=ecx)
        for address, table in ((0x4d9510, 0x51a560), (0x4d9530, 0x51a5a0), (0x4dde50, 0x51b7d0)):
            run(address, lambda: n.vertrix_rtl_static_init_call(byref_c, STACK - 4, table, ebx, ecx),
                **regs)
        run(0x4dad2e, lambda: n.vertrix_rtl_ebx_from_edx_call(byref_c, eax, edx, ecx), **regs)
        for address, target in ((0x4dabe0, 0x4e2434), (0x4dacf8, 0x4dacd0)):
            first, second = rng.getrandbits(32), rng.getrandbits(32)
            run(address, lambda: n.vertrix_rtl_stack_pair_call(byref_c, target, STACK - 12, first,
                                                               second, ecx),
                eax=eax, edx=edx, ebx=ebx, ecx=ecx, args=(first, second))
        sample = rng.choice([0, edx, edx | 0x80000000, 1])
        assert n.vertrix_rtl_sign_of(sample) == pure.call(0x4dad19, edx=sample) & 0xffffffff
        totals['0x4dad19'] = totals.get('0x4dad19', 0) + 1
        run(0x4db866, lambda: n.vertrix_rtl_flags_call(byref_c, STACK - 12, edx, ebx, ecx), **regs)
        run(0x4db866, lambda: n.vertrix_rtl_flags_call(byref_c, STACK - 12, 0, ebx | 8, ecx),
            eax=eax, edx=0, ebx=ebx | 8, ecx=ecx)
        run(0x4db866, lambda: n.vertrix_rtl_flags_call(byref_c, STACK - 12, 0, ebx & ~0x1f, ecx),
            eax=eax, edx=0, ebx=ebx & ~0x1f, ecx=ecx)
        run(0x4db10a, lambda: n.vertrix_rtl_scratch_triple_call(byref_c, STACK - 8, STACK - 20, eax,
                                                                ebx, ecx), **regs)
        run(0x4da66e, lambda: n.vertrix_rtl_zero_call3(byref_c, ecx), compare=False, **regs)
        holder = rng.choice(pool.handles)
        run(0x4ddc60, lambda: n.vertrix_rtl_release_list_head(byref_c, byref_s, holder, edx),
            eax=holder, edx=edx, ebx=ebx, ecx=ecx)
        run(0x4cf980, lambda: n.vertrix_rtl_release_string_member(byref_c, byref_s, holder, edx),
            eax=holder, edx=edx, ebx=ebx, ecx=ecx)
        table = rng.choice([0, rng.getrandbits(32)])
        cpu.mem_write(0x5c77e8, struct.pack('<I', table))
        run(0x4dc160, lambda: n.vertrix_rtl_lookup_call(byref_c, byref_s, holder, table, ebx, ecx),
            eax=holder, edx=edx, ebx=ebx, ecx=ecx)
        run(0x4d94a0, lambda: n.vertrix_rtl_probe_call(byref_c, byref_s, holder, edx, ecx),
            eax=holder, edx=edx, ebx=ebx, ecx=ecx)
        text_argument = rng.getrandbits(32)
        for pair in ((edx, ecx), (0, 0), ((-ecx) & 0xffffffff, ecx)):
            run(0x4ca3f0, lambda: n.vertrix_rtl_string_append_pair(
                byref_c, byref_s, holder, pair[0], ebx, pair[1], text_argument),
                eax=holder, edx=pair[0], ebx=ebx, ecx=pair[1], args=(text_argument,))
        count = rng.choice([ebx, rng.randrange(0, 5), 0xffffffff])
        run(0x4cda90, lambda: n.vertrix_rtl_string_fill(byref_c, byref_s, holder, edx, count, ecx),
            eax=holder, edx=edx, ebx=count, ecx=ecx)
        other = rng.choice([h for h in pool.handles if h != holder])
        for address, pair in ((0x4ca240, (edx, ecx)), (0x4ca240, ((-ebx) & 0xffffffff, ecx))):
            run(address, lambda: n.vertrix_rtl_string_copy_pair(
                byref_c, byref_s, holder, other, ebx, pair[1], pair[0]),
                eax=holder, edx=other, ebx=ebx, ecx=pair[1], args=(pair[0],))
        header = other
        for handle, content in ((holder, struct.pack('<I', header + 0xc)),
                                (header, struct.pack('<III', rng.choice([0, 1, 2]),
                                                     rng.randrange(0, 8), rng.randrange(0, 8)))):
            raw = bytearray(pool.buffers[handle].raw)
            raw[0:len(content)] = content
            cpu.mem_write(handle, bytes(raw))
            pool.buffers[handle] = c.create_string_buffer(bytes(raw), SIZE)
        wanted = rng.randrange(0, 9)
        run(0x4ca1a0, lambda: n.vertrix_rtl_string_make_unique(byref_c, byref_s, holder, edx),
            eax=holder, edx=edx, ebx=ebx, ecx=ecx)
        run(0x4ca670, lambda: n.vertrix_rtl_string_unique_size(byref_c, byref_s, holder, wanted,
                                                               ebx),
            eax=holder, edx=wanted, ebx=ebx, ecx=ecx)
        run(0x4ca6f0, lambda: n.vertrix_rtl_string_set_length(byref_c, byref_s, holder, wanted),
            eax=holder, edx=wanted, ebx=ebx, ecx=ecx)
        built = rng.choice(pool.handles)
        run(0x4cf320, lambda: n.vertrix_rtl_construct_buffer_stream(byref_c, byref_s, built, 0, 0),
            eax=built, edx=edx, ebx=ebx, ecx=ecx)
        run(0x4cf3a0, lambda: n.vertrix_rtl_construct_buffer_stream(byref_c, byref_s, built, edx, 1),
            eax=built, edx=edx, ebx=ebx, ecx=ecx)
        run(0x4cf3a0, lambda: n.vertrix_rtl_construct_buffer_stream(byref_c, byref_s, built, 0, 1),
            eax=built, edx=0, ebx=ebx, ecx=ecx)
        candidate, start = rng.getrandbits(32), rng.choice([rng.getrandbits(32), 0])
        for first, second in ((candidate, start), (candidate, candidate)):
            run(0x4d4390, lambda: n.vertrix_rtl_ancestor_search(byref_c, eax, ecx, first, second),
                eax=eax, edx=edx, ebx=ebx, ecx=ecx, args=(first, second))
        out_handle = rng.choice(pool.handles)
        run(0x4df140, lambda: n.vertrix_rtl_table_lookup_value(byref_c, byref_s, STACK - 8, eax, edx,
                                                               out_handle),
            eax=eax, edx=edx, ebx=out_handle, ecx=ecx)
        for first in (rng.getrandbits(32), 0):
            second = rng.getrandbits(32)
            run(0x4d9930, lambda: n.vertrix_rtl_forward_pair(byref_c, edx, ebx, ecx, first, second),
                eax=eax, edx=edx, ebx=ebx, ecx=ecx, args=(first, second))
        run(0x4db6d9, lambda: n.vertrix_rtl_bracket_call(byref_c, eax, edx, ebx, ecx), **regs)
        run(0x418760, lambda: n.vertrix_rtl_construct_derived_stream(byref_c, byref_s, eax, edx, ebx,
                                                                     ecx), **regs)
        run(0x4decd0, lambda: n.vertrix_rtl_construct_event_table(byref_c, byref_s, built, edx, ebx,
                                                                  ecx),
            eax=built, edx=edx, ebx=ebx, ecx=ecx)
        run(0x4d8620, lambda: n.vertrix_rtl_store_in_slot(byref_c, byref_s, eax, ebx, ecx), **regs)
        va = [rng.getrandbits(32) for _ in range(4)]
        run(0x4cd544, lambda: n.vertrix_rtl_vararg_call(byref_c, STACK - 16, va[0], va[1], va[2]),
            args=tuple(va), **regs)
        run(0x4cd520, lambda: n.vertrix_rtl_vararg_call(byref_c, STACK - 44, va[0], va[1], 0),
            args=tuple(va[:3]), **regs)
        mask = rng.choice([edx, 1 << rng.randrange(0, 8), 0x100, 0xffffffff])
        run(0x4d66cd, lambda: n.vertrix_rtl_test_and_set(byref_c, byref_s, holder, mask),
            eax=holder, edx=mask, ebx=ebx, ecx=ecx)
        chain = struct.unpack('<I', bytes(cpu.mem_read(0, 4)))[0]
        run(0x4cda12, lambda: n.vertrix_rtl_local_chain_call(byref_c, STACK - 24, eax, edx, ebx,
                                                             chain), **regs)
        run(0x4cda10, lambda: n.vertrix_rtl_local_chain_call(byref_c, STACK - 24, 0, edx, ebx,
                                                             chain), **regs)
        target, var_a, var_b, hdr = pool.handles
        for handle, content in ((var_a, struct.pack('<I', hdr + 0xc)),
                                (var_b, struct.pack('<I', hdr + 0xc)),
                                (hdr, struct.pack('<II', 1, rng.randrange(0, 5)))):
            raw = bytearray(pool.buffers[handle].raw)
            raw[0:len(content)] = content
            cpu.mem_write(handle, bytes(raw))
            pool.buffers[handle] = c.create_string_buffer(bytes(raw), SIZE)
        run(0x4ca430, lambda: n.vertrix_rtl_string_concat(byref_c, byref_s, target, var_a, var_b,
                                                          ebx, ecx),
            eax=0, edx=0, ebx=ebx, ecx=ecx, args=(target, var_a, var_b))
        for dest in (holder, 0):
            run(0x4daab0, lambda: n.vertrix_rtl_copy_terminated(byref_c, byref_s, dest, edx, ebx, ecx),
                eax=dest, edx=edx, ebx=ebx, ecx=ecx)
        for address, name in ((0x4cdfe0, 'end'), (0x4ce030, 'start')):
            body = bytes(rng.choice(b' \t abc') for _ in range(rng.randrange(0, 8))) + bytes(0x20)
            for handle, content in ((target, struct.pack('<I', hdr + 0xc)),
                                    (hdr, struct.pack('<III', rng.choice([1, 1, 2]),
                                                      rng.randrange(0, 8), 8) + body)):
                raw = bytearray(pool.buffers[handle].raw)
                raw[0:len(content)] = content
                cpu.mem_write(handle, bytes(raw))
                pool.buffers[handle] = c.create_string_buffer(bytes(raw), SIZE)
            run(address, lambda: getattr(n, 'vertrix_rtl_string_trim_' + name)(
                byref_c, byref_s, target, edx, ebx), eax=target, edx=edx, ebx=ebx, ecx=ecx)
        run(0x4dee73, lambda: n.vertrix_rtl_segment_dispatch(byref_c, eax, edx,
                                                             cpu.reg_read(UC_X86_REG_DS)), **regs)
        start = rng.choice([ebx, rng.randrange(0, 8), 0xfffffffe])
        for handle, content in ((var_a, struct.pack('<I', hdr + 0xc)),
                                (hdr, struct.pack('<II', 1, rng.randrange(0, 8)))):
            raw = bytearray(pool.buffers[handle].raw)
            raw[0:len(content)] = content
            cpu.mem_write(handle, bytes(raw))
            pool.buffers[handle] = c.create_string_buffer(bytes(raw), SIZE)
        run(0x4cdaf0, lambda: n.vertrix_rtl_string_tail(byref_c, byref_s, var_a, target, start, ecx),
            eax=var_a, edx=target, ebx=start, ecx=ecx)
        for variant in range(3):
            rle_bytes.clear()
            rle_plan.clear()
            rle_remaining = rng.randrange(0, 7) if variant != 1 else 0
            consumed, produced = 0, 0
            while consumed < rle_remaining:
                if rle_remaining - consumed >= 2 and rng.random() < 0.5:
                    run_length = rng.randrange(0, 4)
                    rle_plan.extend([0xc0 + run_length, rng.randrange(256)])
                    consumed += 2
                    produced += run_length
                else:
                    rle_plan.append(rng.randrange(0, 0xc0))
                    consumed += 1
                    produced += 1
            rle_expected = produced if variant != 2 else produced + 1
            destination = pool.handles[1] + 0x40
            output_buffer = pool.buffers[pool.handles[1]]
            run(0x481480, lambda: n.vertrix_rle_decode(
                byref_c, STACK - 16, eax, destination, rle_remaining, rle_expected,
                c.addressof(output_buffer) + 0x40),
                compare=False, eax=eax, edx=destination, ebx=rle_remaining, ecx=rle_expected)
        rle_bytes.clear()
        rle_plan.clear()
        width, height = rng.randrange(0, 5), rng.randrange(0, 5)
        total, produced = width * height, 0
        while produced < total:
            if total - produced >= 2 and rng.random() < 0.5:
                run_length = rng.randrange(1, min(4, total - produced) + 1)
                rle_plan.extend([0xc0 + run_length, rng.randrange(256)])
                produced += run_length
            else:
                rle_plan.append(rng.randrange(0, 0xc0))
                produced += 1
        pixel_address = pool.handles[2] + 0x40
        pixel_buffer = pool.buffers[pool.handles[2]]
        for handle in pool.handles:
            cpu.mem_write(handle, struct.pack('<I', pixel_address))
            c.memmove(pool.buffers[handle], struct.pack('<I', pixel_address), 4)
        run(0x481580, lambda: n.vertrix_rle_decode_bitmap(
            byref_c, byref_s, STACK - 20, eax, width, height, ecx,
            c.addressof(pixel_buffer) + 0x40), eax=eax, edx=width, ebx=height, ecx=ecx)
        path_text = bytes(rng.choice(b'abc:\\/.') for _ in range(rng.randrange(0, 9))) + b'\0'
        cpu.mem_write(0x800c80, path_text)
        cpu.mem_write(0x800ca0, struct.pack('<I', 0x800c80))
        path_buffer = c.create_string_buffer(path_text, len(path_text))
        path_out = c.create_string_buffer(0x20)
        for address, copy_to, native in (
                (0x4896f0, 0x5ba0e0, lambda: n.vertrix_path_split_a(byref_c, holder, path_buffer,
                                                                    path_out)),
                (0x489ba0, 0x5baa08, lambda: n.vertrix_path_split_b(byref_c, holder, edx, path_buffer,
                                                                    path_out))):
            regs_for = dict(eax=holder, edx=0x800c80, ebx=ebx, ecx=ecx)
            if address == 0x489ba0:
                cpu.mem_write(holder, struct.pack('<I', 0x800c80))
                pool.buffers[holder] = c.create_string_buffer(
                    struct.pack('<I', 0x800c80) + bytes(pool.buffers[holder].raw[4:]), SIZE)
                regs_for = dict(eax=holder, edx=edx, ebx=ebx, ecx=ecx)
            run(address, native, **regs_for)
            assert path_out.raw[:len(path_text)] == bytes(cpu.mem_read(copy_to, len(path_text))), (
                hex(address), path_text)
        fourth = rng.choice([0, rng.getrandbits(32)])
        path_args = [rng.choice([0, rng.getrandbits(32)]) for _ in range(3)]
        run(0x489640, lambda: n.vertrix_path_split_c(byref_c, path_buffer, path_args[0], path_args[1],
                                                     path_args[2], fourth, path_out),
            eax=0x800c80, edx=path_args[0], ebx=path_args[1], ecx=path_args[2], args=(fourth,))
        assert path_out.raw[:len(path_text)] == bytes(cpu.mem_read(0x5b9cd0, len(path_text)))
        blocks = rng.randrange(0, 4)
        source_data = rng.randbytes(0x200)
        pure.cpu.mem_write(0x800e00, source_data)
        pure.cpu.mem_write(0x801200, bytes(0x200))
        copy_source = c.create_string_buffer(source_data, 0x200)
        copy_target = c.create_string_buffer(0x200)
        assert pure.call(0x4c98d0, eax=0x800e00, edx=0x801200, ebx=blocks) & 0xffffffff == \
            n.vertrix_rtl_copy_blocks(copy_target, copy_source, blocks)
        assert copy_target.raw == bytes(pure.cpu.mem_read(0x801200, 0x200))
        totals['0x4c98d0'] = totals.get('0x4c98d0', 0) + 1
        run(0x4d4060, lambda: n.vertrix_rtl_record_forward(byref_c, eax, edx, ecx), **regs)
        run(0x4cf8e0, lambda: n.vertrix_rtl_triple_call(byref_c, argument, ebx, ecx), eax=eax,
            edx=edx, ebx=ebx, ecx=ecx, args=(argument,))
        text = rng.randbytes(rng.randrange(0, 12)).replace(b'\0', b'q') + b'\0'
        cpu.mem_write(0x800b00, text)
        run(0x489470, lambda: n.vertrix_rtl_write_text_call(byref_c, STACK - 4, eax, 0x800b00,
                                                            len(text) - 1),
            eax=eax, edx=0x800b00, ebx=ebx, ecx=ecx)
        assert n.vertrix_rtl_class_address() == pure.call(0x4cfa10)
        totals['0x4cfa10'] = totals.get('0x4cfa10', 0) + 1
        for address, name in ((0x4dd360, 'list'), (0x4d9280, 'flag')):
            record = rng.choice(pool.handles)
            data = rng.randbytes(SIZE)
            pure.cpu.mem_write(record, data)
            pool.buffers[record] = c.create_string_buffer(data, SIZE)
            result = pure.call(address, eax=record) & 0xffffffff
            got = getattr(n, 'vertrix_rtl_construct_' + name)(record, pool.buffers[record])
            assert got == result and bytes(pool.buffers[record].raw) == bytes(
                pure.cpu.mem_read(record, SIZE)), (name, case)
            totals[hex(address)] = totals.get(hex(address), 0) + 1
        fast, modes = rng.choice([0, 1, 7]), rng.getrandbits(8)
        pure.cpu.mem_write(0x5054a1, bytes([fast]))
        pure.cpu.mem_write(0x508798, bytes([modes]))
        pure.call(0x4d82c6)
        table = (U * 3)()
        n.vertrix_rtl_select_float_helpers(fast, modes, c.byref(table))
        assert list(table) == list(struct.unpack('<3I', bytes(pure.cpu.mem_read(0x503ea0, 12)))), case
        totals['0x4d82c6'] = totals.get('0x4d82c6', 0) + 1
        record = rng.choice(pool.handles)
        data = rng.randbytes(SIZE)
        pure.cpu.mem_write(record, data)
        pool.buffers[record] = c.create_string_buffer(data, SIZE)
        result = pure.call(0x4deec0, eax=record, edx=edx) & 0xffffffff
        got = n.vertrix_rtl_construct_table(record, pool.buffers[record], edx)
        assert got == result and bytes(pool.buffers[record].raw) == bytes(
            pure.cpu.mem_read(record, SIZE)), ('table', case)
        totals['0x4deec0'] = totals.get('0x4deec0', 0) + 1
        for address, klass in ((0x4d8340, 0x51a024), (0x4d8ab0, 0x51a1b4)):
            record = rng.choice(pool.handles)
            data = rng.randbytes(SIZE)
            pure.cpu.mem_write(record, data)
            pool.buffers[record] = c.create_string_buffer(data, SIZE)
            result = pure.call(address, eax=record, edx=edx) & 0xffffffff
            got = n.vertrix_rtl_construct_chunk_list(record, pool.buffers[record], klass, edx)
            assert got == result and bytes(pool.buffers[record].raw) == bytes(
                pure.cpu.mem_read(record, SIZE)), (hex(address), case)
            totals[hex(address)] = totals.get(hex(address), 0) + 1
        record = rng.choice(pool.handles)
        data = bytearray(rng.randbytes(SIZE))
        data[0x16] = rng.choice([0x30, 0x30, 0x31])
        data[0x1e] = rng.choice([0, 8, 0x10])
        struct.pack_into('<I', data, 4, rng.randrange(0, 0x3000))
        for k in range(6):
            struct.pack_into('<I', data, 0x20 + 4 * k, rng.randrange(0, 0x300))
        data = bytes(data)
        pure.cpu.mem_write(record, data)
        pool.buffers[record] = c.create_string_buffer(data, SIZE)
        pure.call(0x4dfa7c, eax=record)
        got = n.vertrix_rtl_distribute_slack(record, pool.buffers[record], SIZE)
        assert got == record and bytes(pool.buffers[record].raw) == bytes(
            pure.cpu.mem_read(record, SIZE)), ('slack', case)
        totals['0x4dfa7c'] = totals.get('0x4dfa7c', 0) + 1
        sample = rng.choice([eax, eax >> rng.randrange(0, 32), rng.randrange(0, 4), 0])
        pure.call(0x4d6775, eax=sample, ecx=ecx)
        regs_out = (pure.cpu.reg_read(UC_X86_REG_EAX), pure.cpu.reg_read(UC_X86_REG_EDX))
        assert n.vertrix_rtl_integer_to_double(sample) == (regs_out[1] << 32 | regs_out[0]), sample
        totals['0x4d6775'] = totals.get('0x4d6775', 0) + 1
        bits = rng.choice([eax, (eax & 0x807fffff) | (rng.randrange(0x70, 0xa8) << 23), 0])
        limit = rng.choice([ecx & 0xff, rng.randrange(0x7f, 0xa8)])
        result = pure.call(0x4d67f0, eax=bits, ecx=limit) & 0xffffffff
        assert n.vertrix_rtl_float_to_integer(bits, limit) == result, (hex(bits), limit)
        totals['0x4d67f0'] = totals.get('0x4d67f0', 0) + 1
        wide = b''.join(rng.randrange(1, 0x10000).to_bytes(2, 'little')
                        for _ in range(rng.randrange(0, 9))) + b'\0\0'
        pure.cpu.mem_write(0x800c00, wide)
        buffer = c.create_string_buffer(wide, len(wide))
        assert n.vertrix_rtl_wide_length(buffer) == pure.call(0x4d8580, eax=0x800c00)
        totals['0x4d8580'] = totals.get('0x4d8580', 0) + 1
        entries = rng.randrange(1, 5)
        table = bytearray()
        for k in range(entries):
            low = rng.randrange(0, 50)
            table += struct.pack('<5I', rng.randrange(0, 3), rng.randrange(0, 3), low,
                                 low + rng.randrange(0, 30), 1) + bytes(12)
        table += bytes(0x20)
        pure.cpu.mem_write(0x800d00, bytes(table))
        probe = (rng.randrange(0, 3), rng.randrange(0, 3), rng.randrange(0, 90))
        result = pure.call(0x4d0b30, args=(0x800d00,) + probe) & 0xffffffff
        table_buffer = c.create_string_buffer(bytes(table), len(table))
        got = n.vertrix_rtl_range_table_find(table_buffer, len(table), 0x800d00, *probe)
        assert got == result, ('range', probe, got, result)
        totals['0x4d0b30'] = totals.get('0x4d0b30', 0) + 1
        low_part, high_part = rng.getrandbits(32), rng.choice([rng.getrandbits(32), 0,
                                                              rng.getrandbits(32) & 0x7fffffff])
        pure.call(0x4db1fd, eax=low_part, edx=high_part, ebx=0x800e00)
        exponent = U()
        got = n.vertrix_rtl_split_exponent(low_part, high_part, c.byref(exponent))
        expected = (pure.cpu.reg_read(UC_X86_REG_EDX) << 32) | pure.cpu.reg_read(UC_X86_REG_EAX)
        assert got == expected and exponent.value == struct.unpack(
            '<I', bytes(pure.cpu.mem_read(0x800e00, 4)))[0], ('split', hex(low_part), hex(high_part))
        totals['0x4db1fd'] = totals.get('0x4db1fd', 0) + 1
        alphabet = b' \t\n\r\x0b\x0c+-0123456789abc\x80\xff'
        sample = bytes(rng.choice(alphabet) for _ in range(rng.randrange(0, 16))) + b'\0'
        pure.cpu.mem_write(0x800f00, sample)
        parse_buffer = c.create_string_buffer(sample, len(sample))
        assert n.vertrix_rtl_parse_integer(parse_buffer) == pure.call(0x4d6710, eax=0x800f00) \
            & 0xffffffff, sample
        totals['0x4d6710'] = totals.get('0x4d6710', 0) + 1
        pair = rng.choice([(eax, edx), (0, 0), (eax, 0), (0, edx), (0, 0x80000000)])
        for address, name in ((0x4dae4a, 'negate'), (0x4dae62, 'absolute')):
            pure.call(address, eax=pair[0], edx=pair[1])
            expected = (pure.cpu.reg_read(UC_X86_REG_EDX) << 32) | pure.cpu.reg_read(UC_X86_REG_EAX)
            assert getattr(n, 'vertrix_rtl_' + name + '_double')(*pair) == expected, (name, pair)
            totals[hex(address)] = totals.get(hex(address), 0) + 1
        record = rng.choice(pool.handles)
        data = rng.randbytes(SIZE)
        pure.cpu.mem_write(record, data)
        pool.buffers[record] = c.create_string_buffer(data, SIZE)
        flags_text = bytes(rng.choice(b'-#+ 0-#+ 0ab1') for _ in range(rng.randrange(0, 9))) + b'x\0'
        pure.cpu.mem_write(0x800c00, flags_text)
        flags_buffer = c.create_string_buffer(flags_text, len(flags_text))
        expected_end = pure.call(0x4df81c, eax=0x800c00, edx=record) & 0xffffffff
        got = n.vertrix_rtl_parse_format_flags(flags_buffer, 0x800c00, pool.buffers[record], SIZE)
        assert got == expected_end and bytes(pool.buffers[record].raw) == bytes(
            pure.cpu.mem_read(record, SIZE)), ('flags', flags_text)
        totals['0x4df81c'] = totals.get('0x4df81c', 0) + 1
        to_record, from_record = pool.handles[0], pool.handles[1]
        for handle in (to_record, from_record):
            data = rng.randbytes(SIZE)
            pure.cpu.mem_write(handle, data)
            pool.buffers[handle] = c.create_string_buffer(data, SIZE)
        result = pure.call(0x48d3e0, eax=to_record, edx=from_record) & 0xffffffff
        got = n.vertrix_record_copy(to_record, pool.buffers[to_record], pool.buffers[from_record])
        assert got == to_record and bytes(pool.buffers[to_record].raw) == bytes(
            pure.cpu.mem_read(to_record, SIZE)), 'record copy'
        assert result == to_record
        totals['0x48d3e0'] = totals.get('0x48d3e0', 0) + 1
        count, flag_byte = rng.randrange(0, 40), rng.getrandbits(8)
        sums = rng.randbytes(64)
        pure.cpu.mem_write(0x800e00, sums)
        record_bytes = bytearray(0x20)
        struct.pack_into('<I', record_bytes, 0, 0x800e00)
        struct.pack_into('<I', record_bytes, 8, count)
        record_bytes[0x16] = flag_byte
        pure.cpu.mem_write(0x800dc0, bytes(record_bytes))
        pure.call(0x4b8fbc, eax=0x800dc0)
        sums_buffer = c.create_string_buffer(sums, 64)
        n.vertrix_record_prefix_sum(count, flag_byte, sums_buffer)
        assert sums_buffer.raw == bytes(pure.cpu.mem_read(0x800e00, 64)), ('prefix', count, flag_byte)
        totals['0x4b8fbc'] = totals.get('0x4b8fbc', 0) + 1
        # 0x4cba70 and 0x4c9840 run in the second instance, where nothing is stubbed.
        pool_before = [h for h in pool.handles]
        record = rng.choice(pool_before)
        data = rng.randbytes(SIZE)
        pure.cpu.mem_write(record, data)
        pool.buffers[record] = c.create_string_buffer(data, SIZE)
        pure.call(0x4cba70, eax=record)
        got = n.vertrix_rtl_record_clear(byref_s, record)
        assert got == record and bytes(pool.buffers[record].raw) == bytes(
            pure.cpu.mem_read(record, SIZE)), ('clear', case)
        totals['0x4cba70'] = totals.get('0x4cba70', 0) + 1
        pair = rng.choice([(eax, edx), (eax, eax), (eax, eax ^ 0x80000000), (eax & 0x7fffffff, edx)])
        got = n.vertrix_rtl_sign_compare(*pair)
        result = pure.call(0x4d8082, eax=pair[0], edx=pair[1]) & 0xffffffff
        assert got == result, ('sign', pair, got, result)
        totals['0x4d8082'] = totals.get('0x4d8082', 0) + 1
        value, multiple = rng.randrange(-1000, 1000), rng.choice([1, 2, 3, 7, 16, 100, -4, -9])
        got = n.vertrix_round_up(value, multiple)
        result = pure.call(0x4c9840, eax=value & 0xffffffff, edx=multiple & 0xffffffff)
        assert got & 0xffffffff == result & 0xffffffff, ('round', value, multiple, got, result)
        totals['0x4c9840'] = totals.get('0x4c9840', 0) + 1
    chain_order = list(pool.handles)
    for index, handle in enumerate(chain_order):
        raw = bytearray(pool.buffers[handle].raw)
        link = chain_order[index + 1] if index + 1 < len(chain_order) and index % 3 else 0
        struct.pack_into('<I', raw, 0x10, link)
        cpu.mem_write(handle, bytes(raw))
        pool.buffers[handle] = c.create_string_buffer(bytes(raw), SIZE)
    for start in pool.handles + [0]:
        for target in pool.handles + [0, 0x12345]:
            run(0x4d3120, lambda: n.vertrix_rtl_class_chain_contains(byref_s, start, target),
                eax=start, edx=target)
    def link_patch(handle, data):
        struct.pack_into('<I', data, 0x38, rng.choice([0, 0, rng.choice(pool.handles)]))
        struct.pack_into('<I', data, 0x34, rng.choice([0, rng.getrandbits(32), rng.getrandbits(32)]))
        struct.pack_into('<I', data, 0x24, rng.choice([0, rng.choice(pool.handles)]))
        struct.pack_into('<I', data, 0xc, rng.choice(pool.handles))

    for case in range(args.cases):
        pool.fill(rng, link_patch)
        owner, member = rng.choice(pool.handles + [0]), rng.choice(pool.handles + [0])
        run(0x4ccee0, lambda: n.vertrix_rtl_link_owner(byref_c, byref_s, STACK - 16, owner, member),
            eax=owner, edx=member, ebx=rng.getrandbits(32), ecx=rng.getrandbits(32))
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each wrapper executes completely in the original with its runtime callees '
                       'stubbed and logged; every callee call (address and registers), the '
                       'returned eax and the record objects compare. 0x4cba70 and 0x4c9840 run '
                       'unstubbed in a second instance.'}
    (args.build_dir / 'rtl-glue-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
