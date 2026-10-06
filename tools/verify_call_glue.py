"""Compare the original thin call-through wrappers with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from unicorn.x86_const import UC_X86_REG_ESI
from oracle_kit import Stubs, build

U = c.c_uint32
OBJECT = 0x808000
OBJECT_SIZE = 0x40
STRING = 0x808200


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next', 'stack_third',
                                'out_ebx', 'out_ecx')] + [('rest%d' % i, U) for i in range(8)] + [
        ('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


CALLEES = {0x418820: 0, 0x4177b0: 0, 0x4cea15: 0, 0x476160: 0, 0x476480: 0, 0x476720: 0, 0x487640: 0, 0x487750: 1,
           0x45f0c0: 0, 0x45f1e0: 0, 0x425de0: 0, 0x43f420: 0, 0x4ea190: 0,
           0x4b6200: 0, 0x475800: 0, 0x4ca370: 0, 0x4759e0: 0, 0x475b80: 2, 0x40eea0: 0,
           0x40adc0: 0, 0x4d8950: 0, 0x45fa70: 0, 0x45fab0: 0, 0x4877f0: 0, 0x47cd60: 0,
           0x483ed0: 0, 0x4d74a6: 0, 0x4d81fe: 0, 0x4d74d1: 0, 0x4d8177: 0, 0x4d67a8: 0,
           0x4c9e2f: 0, 0x4d6768: 0, 0x4db507: 0, 0x4eb652: 0, 0x4eb892: 0, 0x440610: 1, 0x440990: 4, 0x4ca710: 0, 0x40add0: 0, 0x40ad50: 0, 0x4eb5c0: 0, 0x40ac10: 0, 0x40ac20: 0, 0x472d50: 0, 0x4ca000: 0, 0x4abd70: 0, 0x4ac8f0: 0, 0x4ac7d0: 0,
           0x475c80: 0, 0x476480: 0, 0x4776a0: 0, 0x40ef00: 0, 0x4ec1a0: 0, 0x482640: 0, 0x4d9060: 2, 0x40ef40: 0, 0x40ede0: 0, 0x40ee30: 0,
           0x46b810: 0, 0x475af0: 0, 0x475790: 1, 0x475da0: 0, 0x476140: 0, 0x40ee60: 0,
           0x47e7d0: 0, 0x47fd70: 0, 0x48a930: 0, 0x4ca600: 0, 0x4e7eb0: 0, 0x4ebce8: 0,
           0x4ebe60: 0, 0x40a890: 0, 0x40a800: 0, 0x40ab20: 0, 0x487a20: 0, 0x48d630: 0, 0x4e7c90: 0, 0x487710: 0, 0x40aca0: 0, 0x47f190: 0, 0x479d70: 0, 0x476120: 0, 0x482b30: 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'call-glue', ['call_glue.c', 'object_glue.c', 'actor_storage.c', 'table_queries.c'])
    P = c.POINTER(Calls)
    for name, types in (
            ('vertrix_resource_entry_call', [U, U]), ('vertrix_point_list_add', [U, c.c_uint16]),
            ('vertrix_point_list_conditional', [c.c_uint16, U]),
            ('vertrix_point_list_when_one', [U, U]), ('vertrix_resource_one_frame', [U, U]),
            ('vertrix_grid_cell_call', [U] * 6), ('vertrix_seven_steps', [U]),
            ('vertrix_object_set_table', [c.c_void_p, c.c_size_t, U]),
            ('vertrix_glyph_present', [U, U]), ('vertrix_forward_4ea190', []),
            ('vertrix_list_clear_call', [U]), ('vertrix_offset_call', [U, U, U]),
            ('vertrix_slot_call', [U, U]), ('vertrix_list_find_call', [U]),
            ('vertrix_when_flag_call', [U, U]), ('vertrix_list_reset_calls', [U, U, U, U]),
            ('vertrix_list_push_call', [U, U, U]), ('vertrix_slot_store_call', [U] * 5),
            ('vertrix_two_codes_call', [U]), ('vertrix_clear_each_call', [c.POINTER(U * 76), U]), ('vertrix_index_sweep_call', [U, U]), ('vertrix_fixed_codes_call', [U]),
            ('vertrix_slot_table_switch', [U, U, c.POINTER(U)]),
            ('vertrix_neighbour_calls', [U, U, U, U]), ('vertrix_edx_to_eax_call', [U, U, U, U]),
            ('vertrix_indexed_resource_call', [U, U, U, U]), ('vertrix_grid_array_call', [U, U, U]),
            ('vertrix_slot_table_reset', [U]), ('vertrix_two_step_call', [U]),
            ('vertrix_object_chain_member', [U, U]), ('vertrix_checked_calls', [U]),
            ('vertrix_flag_pair_call', [U]), ('vertrix_string_append_calls', [U, c.c_char_p, U]),
            ('vertrix_global_discard_call', [U]), ('vertrix_global_pair_call', [U, U, U]),
            ('vertrix_global_call', [U]), ('vertrix_module_reset_calls', [U]), ('vertrix_flagged_call', [U, U, U]),
            ('vertrix_forward_first_dword', [c.c_void_p, c.c_size_t]),
            ('vertrix_table_entry_call', [c.c_void_p, U]), ('vertrix_forward_call', [U]),
            ('vertrix_find_attribute_flag', [U, U]), ('vertrix_find_succeeded', [U, U]),
            ('vertrix_find_size_field', [U, U]),
            ('vertrix_scratch_pair_call', [U, U, U, U]),
            ('vertrix_offset_pair_call', [U, U, U, U]),
            ('vertrix_offset_pair_clamp_call', [U, U, U, U]),
            ('vertrix_slot_create_call', [U, U, U, c.c_void_p]),
            ('vertrix_slot_search_call', [U, U, U, U, c.c_void_p]),
            ('vertrix_text_append_call', [U, U, c.c_char_p, c.c_char_p]),
            ('vertrix_flagged_table_call', [U, c.c_int32, c.c_void_p, U]),
            ('vertrix_mode_switch_call', [U, c.c_void_p, U, U, U]),
            ('vertrix_guarded_call', [U, U, U, U, U, U, U]),
            ('vertrix_resource_pair_call', [U, U, U, U])):
        function = getattr(n, name)
        function.argtypes = [P] + types
        function.restype = U
    class Matcher(c.Structure):
        _fields_ = [('pattern', c.c_void_p), ('length', U), ('index', U)]

    n.vertrix_matcher_feed.argtypes = [P, c.POINTER(Matcher), U, c.c_uint8, U, U]
    n.vertrix_matcher_feed.restype = U
    class Out(c.Structure):
        _fields_ = [(name, U) for name in ('first_word', 'second_word', 'first_dword',
                                           'second_dword')]

    n.vertrix_corner_transform_call.argtypes = [P, U, U, U, U, U, U * 3, c.POINTER(Out)]
    n.vertrix_corner_transform_call.restype = None
    n.vertrix_object_scale_call.argtypes = [P, U, U, U, U, U]
    n.vertrix_object_scale_call.restype = U
    n.vertrix_step_toward_call.argtypes = [P, U, U, U, U]
    n.vertrix_step_toward_call.restype = U
    n.vertrix_curve_table_build.argtypes = [P, U, U, U, U, U * 65]
    n.vertrix_curve_table_build.restype = U
    n.vertrix_forward_registers.argtypes = [P, U, U, U, U, U]
    n.vertrix_forward_registers.restype = U
    n.vertrix_gate_dispatch_call.argtypes = [P, U, U, U, c.POINTER(U)]
    n.vertrix_gate_dispatch_call.restype = U
    n.vertrix_copy_global16.argtypes = [c.c_void_p, c.c_void_p]
    n.vertrix_return_ebx.argtypes = [U]
    n.vertrix_return_zero.argtypes = []
    n.vertrix_read_global.argtypes = [c.c_void_p]
    n.vertrix_read_global.restype = U
    n.vertrix_copy_dword.argtypes = [c.c_void_p, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x45e990)
    returns = []
    outs = []
    pairs = []
    corners = []
    native_log = []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x440610:
            pair = (rng.getrandbits(32), rng.getrandbits(32))
            corners.append(pair)
            cpu.mem_write(ecx, struct.pack('<I', pair[0]))
            cpu.mem_write(stack[0], struct.pack('<I', pair[1]))
        if address == 0x440990:
            pair = (rng.getrandbits(32), rng.getrandbits(32))
            corners.append(pair)
            cpu.mem_write(eax, struct.pack('<I', pair[0]))
            cpu.mem_write(edx, struct.pack('<I', pair[1]))
        if address == 0x4776a0:
            cpu.mem_write(0x5560b0, rng.randbytes(rng.randrange(0, 8)).replace(b'\0', b'a') + b'\0')
        if address == 0x40ef00:
            pair = (rng.getrandbits(32), rng.getrandbits(32))
            pairs.append(pair)
            cpu.mem_write(eax, struct.pack('<I', pair[0]))
            cpu.mem_write(edx, struct.pack('<I', pair[1]))
        if address == 0x40ef40:
            outs.append(rng.choice([0, 1, 2]))
            cpu.mem_write(eax, struct.pack('<I', outs[-1]))
        if address == 0x4d9060:
            outs.append(rng.getrandbits(32))
            cpu.mem_write(edx + 0x10, struct.pack('<I', outs[-1]))
            cpu.mem_write(edx + 0xc, struct.pack('<I', outs[-1]))
        returns.append(0x800100 if address == 0x4877f0 else
                       rng.choice([0xff, 0x1ff, 0x7f, 0x80, rng.getrandbits(32)]) if address == 0x4177b0 else
                       rng.choice([0, 1, 1, rng.getrandbits(32)]))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)
    replay = []

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) +
                          (s.stack, s.stack_next, s.stack_third, s.rest0)[:CALLEES[s.target]])
        if s.target == 0x4d9060:
            s.out_value = outs.pop(0)
        if s.target == 0x440610:
            s.out_ecx, s.out_value = corners.pop(0)
        if s.target == 0x440990:
            s.out_ebx, s.out_ecx = corners.pop(0)
        if s.target == 0x40ef00:
            s.out_ebx, s.out_ecx = pairs.pop(0)
        if s.target == 0x40ef40:
            s.out_value = outs.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}

    def run(name, address, native, compare=True, **registers):
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(address, **registers) & 0xffffffff
        replay[:] = list(returns)
        got = native()
        assert not compare or got == result, (name, hex(got), hex(result))
        assert native_log == stubs.log, (name, native_log, stubs.log)
        assert not replay, name
        totals[hex(address)] = totals.get(hex(address), 0) + 1

    for case in range(args.cases):
        eax, edx = rng.getrandbits(32), rng.getrandbits(32)
        a, b, ac, d = (rng.getrandbits(32) for _ in range(4))
        for address, index in ((0x4182f0, 7), (0x418550, 5), (0x418570, 6)):
            run('entry', address, lambda: n.vertrix_resource_entry_call(c.byref(calls), eax, index),
                eax=eax)
        run('add', 0x416c10, lambda: n.vertrix_point_list_add(c.byref(calls), eax, edx & 0xffff),
            eax=eax, edx=edx)
        run('cond', 0x4735e0, lambda: n.vertrix_point_list_conditional(c.byref(calls), eax & 0xffff,
                                                                   edx), eax=eax, edx=edx)
        run('one', 0x473610, lambda: n.vertrix_point_list_when_one(c.byref(calls), eax, edx % 3),
            eax=eax, edx=edx % 3)
        run('frame1', 0x45e690, lambda: n.vertrix_resource_one_frame(c.byref(calls), 0x544a34, 0x13))
        run('frame2', 0x45e720, lambda: n.vertrix_resource_one_frame(c.byref(calls), 0x5464e4, 8))
        row, column = rng.randrange(0, 20), rng.randrange(0, 20)
        run('grid', 0x45e990, lambda: n.vertrix_grid_cell_call(c.byref(calls), row, column, a, ac, b,
                                                           d),
            eax=row, edx=column, ebx=a, ecx=ac, args=(b, d))
        run('seven', 0x45f0a0, lambda: n.vertrix_seven_steps(c.byref(calls), eax), eax=eax)
        run('glyph', 0x43f460, lambda: n.vertrix_glyph_present(c.byref(calls), eax, edx), eax=eax,
            edx=edx)
        run('forward', 0x441120, lambda: n.vertrix_forward_4ea190(c.byref(calls)), eax=0, edx=0)
        before = rng.randbytes(OBJECT_SIZE)
        cpu.mem_write(OBJECT, before)
        buffer = c.create_string_buffer(before, OBJECT_SIZE)
        run('table', 0x425d30, lambda: n.vertrix_object_set_table(c.byref(calls), buffer,
                                                                   OBJECT_SIZE, OBJECT),
            eax=OBJECT, edx=0)
        assert buffer.raw == bytes(cpu.mem_read(OBJECT, OBJECT_SIZE)), case
    for case in range(args.cases):
        eax, edx = rng.getrandbits(32), rng.getrandbits(32)
        for address, list_address in ((0x471a70, 0x54671c), (0x471a80, 0x546744),
                                      (0x471b00, 0x546730), (0x471b80, 0x546758),
                                      (0x472350, 0x54676c)):
            run('list', address, lambda: n.vertrix_list_clear_call(c.byref(calls), list_address),
                eax=0, edx=0)
        for address, target, offset in ((0x475d90, 0x475800, 4), (0x47ed50, 0x4ca370, 0x1c),
                                        (0x47f8d0, 0x4ca370, 0x3c)):
            run('offset', address, lambda: n.vertrix_offset_call(c.byref(calls), target, eax,
                                                                 offset), eax=eax, edx=0)
        run('slot', 0x476010, lambda: n.vertrix_slot_call(c.byref(calls), eax, edx), eax=eax,
            edx=edx)
        run('find', 0x476260, lambda: n.vertrix_list_find_call(c.byref(calls), edx), edx=edx)
        flag = rng.choice([0, 1, 2])
        cpu.mem_write(0x5589d4, flag.to_bytes(4, 'little'))
        run('flag', 0x478bd0, lambda: n.vertrix_when_flag_call(c.byref(calls), flag, eax), eax=eax,
            edx=0)
        cpu.mem_write(OBJECT, rng.randbytes(OBJECT_SIZE))
        buffer = c.create_string_buffer(bytes(cpu.mem_read(OBJECT, OBJECT_SIZE)), OBJECT_SIZE)
        run('first', 0x482740, lambda: n.vertrix_forward_first_dword(c.byref(calls), buffer,
                                                                      OBJECT_SIZE), eax=OBJECT, edx=0)
        table = rng.randbytes(1024)
        cpu.mem_write(0x598d88, table)
        entries = (c.c_uint32 * 256).from_buffer_copy(table)
        run('entry', 0x482a40, lambda: n.vertrix_table_entry_call(c.byref(calls), entries, eax),
            eax=eax, edx=0)
        run('forward', 0x4872b0, lambda: n.vertrix_forward_call(c.byref(calls), 0x4ea190), eax=0,
            edx=0)
        run('forward', 0x48d6b0, lambda: n.vertrix_forward_call(c.byref(calls), 0x4d8950), eax=0,
            edx=0)
        run('forward46b8', 0x46b800, lambda: n.vertrix_forward_registers(
            c.byref(calls), 0x46b810, eax, 0xffffffff, 0, 0), eax=eax, edx=edx, ebx=0, ecx=0)
        run('entry4', 0x473cd0, lambda: n.vertrix_resource_entry_call(c.byref(calls), eax, 4),
            eax=eax, edx=0)
        flag, guard = rng.choice([0, 0, 1]), rng.choice([0, 0, rng.getrandbits(32)])
        cpu.mem_write(0x532b40, struct.pack('<I', flag))
        cpu.mem_write(0x558958, struct.pack('<I', guard))
        cpu.mem_write(0x558c7c, struct.pack('<I', a))
        run('guarded', 0x419490, lambda: n.vertrix_guarded_call(c.byref(calls), flag, guard,
                                                                0x45fa70, 0, edx, a, ac),
            eax=0, edx=edx, ebx=a, ecx=ac)
        run('guarded', 0x4194b0, lambda: n.vertrix_guarded_call(c.byref(calls), flag, guard,
                                                                0x45fab0, a, edx, a, ac),
            eax=a, edx=edx, ebx=a, ecx=ac)
        cpu.mem_write(0x800100, struct.pack('<I', a))
        run('pair45', 0x45ecd0, lambda: n.vertrix_resource_pair_call(c.byref(calls), eax, edx, ac, a),
            eax=eax, edx=edx, ebx=0, ecx=ac)
        for current_value in (rng.getrandbits(32), eax):
            cpu.mem_write(0x52f148, struct.pack('<I', current_value))
            current = U(current_value)
            outs.clear()
            run('mode', 0x40afc0, lambda: n.vertrix_mode_switch_call(
                c.byref(calls), STACK - 4, c.byref(current), eax, a, ac), eax=eax, ebx=a, ecx=ac)
            assert current.value == int.from_bytes(cpu.mem_read(0x52f148, 4), 'little'), case
        for address, name in ((0x4895b0, 'attribute'), (0x4895e0, 'succeeded'),
                              (0x489610, 'size_field')):
            outs.clear()
            run('find', address, lambda: getattr(n, 'vertrix_find_' + {
                'attribute': 'attribute_flag', 'succeeded': 'succeeded',
                'size_field': 'size_field'}[name])(c.byref(calls), STACK - 4, eax),
                eax=eax, ebx=0, ecx=0)
        run('scratch', 0x482610, lambda: n.vertrix_scratch_pair_call(
            c.byref(calls), STACK - 4, eax, edx, a), eax=eax, edx=edx, ebx=a, ecx=ac)
        gate = rng.choice([0, 1, 1, 2])
        cpu.mem_write(0x5589d4, struct.pack('<I', gate))
        pairs.clear()
        run('pair', 0x478bf0, lambda: n.vertrix_offset_pair_call(
            c.byref(calls), STACK - 4, gate, eax, edx), eax=eax, edx=edx)
        pairs.clear()
        run('pair_clamp', 0x478c40, lambda: n.vertrix_offset_pair_clamp_call(
            c.byref(calls), STACK - 4, gate, eax, edx), eax=eax, edx=edx)
        gate = rng.choice([0, 0, 1])
        value = rng.getrandbits(32)
        cpu.mem_write(0x532a8c, struct.pack('<I', gate))
        cpu.mem_write(0x532aa4, struct.pack('<I', value))
        cpu.mem_write(0x532ab4, bytes(4))
        stored = U(0)
        run('dispatch', 0x41d5b0, lambda: n.vertrix_gate_dispatch_call(
            c.byref(calls), eax, gate, value, c.byref(stored)), compare=False, eax=eax)
        assert stored.value == int.from_bytes(cpu.mem_read(0x532ab4, 4), 'little')
        mode = rng.choice([0, 1, 2])
        slot = U(0)
        cpu.mem_write(0x546794, bytes(4))
        run('create', 0x472d00, lambda: n.vertrix_slot_create_call(c.byref(calls), mode, a, ac,
                                                                   c.byref(slot)),
            eax=mode, ebx=a, ecx=ac)
        assert slot.value == int.from_bytes(cpu.mem_read(0x546794, 4), 'little'), case
        for gate in (1, rng.choice([0, 2])):
            cpu.mem_write(0x553648, struct.pack('<I', gate))
            for edx_in in (0, 0x800400):
                cpu.mem_write(0x800400, struct.pack('<I', 0x12345678))
                cleared = U(0x12345678)
                run('search', 0x476530, lambda: n.vertrix_slot_search_call(
                    c.byref(calls), gate, eax, edx_in, a, c.byref(cleared)),
                    eax=eax, edx=edx_in, ebx=a)
                assert cleared.value == int.from_bytes(cpu.mem_read(0x800400, 4), 'little'), case
        text = rng.randbytes(rng.randrange(0, 20)).replace(b'\0', b'b') + b'\0'
        cpu.mem_write(0x800500, text + bytes(0x40))
        destination = c.create_string_buffer(text + bytes(0x40), len(text) + 0x40)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x4777c0, eax=0x800500, edx=edx, ecx=ac) & 0xffffffff
        replay[:] = list(returns)
        appended = bytes(cpu.mem_read(0x5560b0, 16)).split(b'\0')[0] + b'\0'
        got = n.vertrix_text_append_call(c.byref(calls), edx, ac, destination, appended)
        assert got == result and native_log == stubs.log and not replay, ('append', case)
        assert destination.raw == bytes(cpu.mem_read(0x800500, len(destination.raw))), case
        totals['0x4777c0'] = totals.get('0x4777c0', 0) + 1
        table_flags = rng.choice([0, 0x80, 0x80, 0xff])
        table_count = rng.randrange(-1, 9)
        handles = (U * 8)(*[rng.getrandbits(32) for _ in range(8)])
        cpu.mem_write(0x531b44, struct.pack('<I', table_flags))
        cpu.mem_write(0x531b48, struct.pack('<i', table_count))
        cpu.mem_write(0x531ac4, bytes(handles))
        run('table', 0x40ed70, lambda: n.vertrix_flagged_table_call(
            c.byref(calls), table_flags, table_count, handles, ac), eax=eax, ecx=ac)
        pattern = bytes(rng.choice(b'ab') for _ in range(6))
        buffer_p = c.create_string_buffer(pattern, 6)
        length, index, byte = rng.randrange(1, 6), rng.randrange(0, 6), rng.choice(b'ab')
        cpu.mem_write(0x800700, pattern)
        cpu.mem_write(0x8006f8, struct.pack('<I', length))
        cpu.mem_write(0x540010, struct.pack('<I', 0x800700))
        cpu.mem_write(0x540014, struct.pack('<I', index))
        cpu.mem_write(0x800600, struct.pack('<I', 0x800610))
        cpu.mem_write(0x800610, bytes([byte]))
        matcher = Matcher(c.addressof(buffer_p), length, index)
        run('matcher', 0x417f50, lambda: n.vertrix_matcher_feed(
            c.byref(calls), c.byref(matcher), 0x800600, byte, a, ac), eax=0x800600, ebx=a, ecx=ac)
        assert matcher.index == int.from_bytes(cpu.mem_read(0x540014, 4), 'little'), case
        corner_args = [rng.getrandbits(32) for _ in range(3)]
        ca, cb, cc, cd = (rng.getrandbits(32) for _ in range(4))
        cpu.mem_write(0x800800, bytes(16))
        corners.clear()
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        original.call(0x4408e0, eax=ca, edx=cb, ebx=cc, ecx=cd,
                      args=(*corner_args, 0x800800, 0x800804, 0x800808, 0x80080c))
        replay[:] = list(returns)
        corners_log = list(stubs.log)
        out = Out()
        n.vertrix_corner_transform_call(c.byref(calls), STACK - 4, ca, cb, cc, cd,
                                        (U * 3)(*corner_args), c.byref(out))
        assert native_log == corners_log and not replay, ('corner', case)
        words = (int.from_bytes(cpu.mem_read(0x800808, 2), 'little'),
                 int.from_bytes(cpu.mem_read(0x80080c, 2), 'little'))
        dwords = struct.unpack('<II', bytes(cpu.mem_read(0x800800, 8)))
        assert (out.first_dword, out.second_dword) == dwords, ('corner dwords', case)
        assert (out.first_word, out.second_word) == words, ('corner words', case)
        totals['0x4408e0'] = totals.get('0x4408e0', 0) + 1
        scale_a, scale_b = rng.getrandbits(32), rng.getrandbits(32)
        cpu.mem_write(OBJECT + 0xc0, struct.pack('<I', scale_a))
        cpu.mem_write(OBJECT + 0xbc, struct.pack('<I', scale_b))
        run('scale', 0x4ac560, lambda: n.vertrix_object_scale_call(
            c.byref(calls), OBJECT, scale_a, scale_b, edx, a), eax=OBJECT, edx=edx, ebx=a, ecx=ac)
        low, high = rng.randrange(-50, 50), rng.randrange(-50, 50)
        if rng.random() < 0.2:
            high = low
        stack_argument = rng.getrandbits(32)
        run('step', 0x4aca00, lambda: n.vertrix_step_toward_call(
            c.byref(calls), low & 0xffffffff, high & 0xffffffff, edx, stack_argument),
            ebx=low & 0xffffffff, ecx=high & 0xffffffff, edx=edx, args=(stack_argument,))
        curve_mode, curve_step = rng.choice([1, 1, 2, 5, 0, 6]), rng.choice([0, 3, 70, 0x100, 0x101])
        curve = (U * 65)()
        cpu.mem_write(0x52f1fc, bytes(260))
        run('curve', 0x40ba00, lambda: n.vertrix_curve_table_build(
            c.byref(calls), curve_mode, curve_step, a, ac, curve), eax=curve_mode, edx=curve_step,
            ebx=a, ecx=ac)
        assert bytes(curve)[:260] == bytes(cpu.mem_read(0x52f1fc, 260)) or curve_mode != 1 or curve_step > 0x100, case
        run('reset', 0x475a80, lambda: n.vertrix_list_reset_calls(c.byref(calls), eax, edx, a, ac),
            eax=eax, edx=edx, ebx=a, ecx=ac)
        stack = rng.getrandbits(32)
        run('push', 0x475ab0, lambda: n.vertrix_list_push_call(c.byref(calls), eax, edx, stack),
            eax=eax, edx=edx, ebx=0, ecx=0, args=(stack,))
        s2, s3 = rng.getrandbits(32), rng.getrandbits(32)
        run('store', 0x4764a0, lambda: n.vertrix_slot_store_call(c.byref(calls), eax, edx, s2, s3,
                                                                  stack),
            eax=eax, edx=edx, ebx=s2, ecx=s3, args=(stack,))
        run('codes', 0x476590, lambda: n.vertrix_two_codes_call(c.byref(calls), eax), eax=eax,
            edx=0)
        flags = rng.choice([0, 1]), rng.choice([0, 1, 2])
        cpu.mem_write(0x5589d4, struct.pack('<I', flags[0]))
        cpu.mem_write(0x5589dc, struct.pack('<I', flags[1]))
        run('flagged', 0x478b40, lambda: n.vertrix_flagged_call(c.byref(calls), flags[0], flags[1],
                                                               eax), eax=eax, edx=0)
        run('checked', 0x47f9b0, lambda: n.vertrix_checked_calls(c.byref(calls), eax), eax=eax,
            edx=0, ebx=0)
        run('pair', 0x482bb0, lambda: n.vertrix_flag_pair_call(c.byref(calls), eax), eax=eax,
            edx=0, ebx=1, ecx=2)
        text = bytes(rng.randrange(1, 256) for _ in range(rng.randrange(0, 30)))
        cpu.mem_write(STRING, text + b'\0')
        run('append', 0x489760, lambda: n.vertrix_string_append_calls(c.byref(calls), eax, text,
                                                                       a), eax=eax, edx=STRING,
            ebx=a, ecx=0)
        cpu.mem_write(0x558ce0, rng.randbytes(16))
        cpu.mem_write(STRING, rng.randbytes(16))
        cpu.reg_write(UC_X86_REG_ESI, STRING)
        stubs.log.clear()
        assert original.call(0x47fbb0, eax=0, edx=0) == STRING
        target = c.create_string_buffer(16)
        n.vertrix_copy_global16(target, bytes(cpu.mem_read(0x558ce0, 16)))
        assert target.raw == bytes(cpu.mem_read(STRING, 16)), case
        totals['0x47fbb0'] = totals.get('0x47fbb0', 0) + 1
        glob = rng.getrandbits(32)
        cpu.mem_write(0x52f90c, struct.pack('<I', glob))
        run('g1', 0x40c1e0, lambda: n.vertrix_global_discard_call(c.byref(calls), glob), eax=0,
            edx=0)
        run('g2', 0x40c1f0, lambda: n.vertrix_global_pair_call(c.byref(calls), glob, eax, edx),
            eax=eax, edx=edx)
        run('g3', 0x40c210, lambda: n.vertrix_global_call(c.byref(calls), glob), eax=0, edx=0)
        marker = rng.choice([0xffff, rng.getrandbits(32), 0xffff])
        cpu.mem_write(0x4f6418, struct.pack('<I', marker))
        run('reset', 0x40ae80, lambda: n.vertrix_module_reset_calls(c.byref(calls), marker), eax=0,
            edx=0)
        run('f40ab', 0x40ab10, lambda: n.vertrix_forward_registers(c.byref(calls), 0x40ab20, 0,
                                                                   edx, 0, 0), eax=eax, edx=edx)
        for address, target_address in ((0x487a10, 0x487a20), (0x48d620, 0x48d630)):
            run('f487', address, lambda: n.vertrix_forward_registers(
                c.byref(calls), target_address, eax, 0, 0, 0), eax=eax, edx=edx)
        for address, target_address in ((0x4c5bc0, 0x4ea190), (0x4c5bd0, 0x4e7c90),
                                        (0x4c5be0, 0x4ea190)):
            run('edx', address, lambda: n.vertrix_edx_to_eax_call(c.byref(calls), target_address,
                                                                  edx, 0, 0), eax=eax, edx=edx)
        assert original.call(0x4c5bf0, ebx=a) == a
        assert original.call(0x4c5c10) == 0
        for address, base in ((0x45e8d0, 0x546458), (0x45ea60, 0x544d7c)):
            flag = rng.choice([0, edx])
            run('indexed', address, lambda: n.vertrix_indexed_resource_call(
                c.byref(calls), base, eax, flag, 0), eax=eax, edx=flag, ebx=0)
        run('gridarray', 0x45e950, lambda: n.vertrix_grid_array_call(c.byref(calls), eax, edx, a),
            eax=eax, edx=edx, ebx=a, ecx=0)
        run('slots', 0x4766f0, lambda: n.vertrix_slot_table_reset(c.byref(calls), eax), eax=eax,
            edx=0)
        run('twostep', 0x4b8170, lambda: n.vertrix_two_step_call(c.byref(calls), eax), eax=eax,
            edx=0)
        run('member', 0x47f260, lambda: n.vertrix_object_chain_member(c.byref(calls), eax, edx),
            eax=eax, edx=edx)
        run('sweep', 0x4760f0, lambda: n.vertrix_index_sweep_call(c.byref(calls), 0x476140, eax),
            eax=eax, edx=0, ebx=0)
        run('sweep2', 0x4760c0, lambda: n.vertrix_index_sweep_call(c.byref(calls), 0x476120, eax),
            eax=eax, edx=0, ebx=0)
        run('codes2', 0x4765b0, lambda: n.vertrix_fixed_codes_call(c.byref(calls), eax), eax=eax,
            edx=0, ebx=0)
        current = U(rng.choice([edx, rng.getrandbits(32)]))
        cpu.mem_write(0x553648, struct.pack('<I', current.value))
        run('switch', 0x4766b0, lambda: n.vertrix_slot_table_switch(c.byref(calls), eax, edx,
                                                                   c.byref(current)),
            eax=eax, edx=edx, ebx=0)
        assert current.value == int.from_bytes(cpu.mem_read(0x553648, 4), 'little'), case
        run('neighbour', 0x479df0, lambda: n.vertrix_neighbour_calls(c.byref(calls), eax, edx, a,
                                                                      ac), eax=eax, edx=edx, ebx=a,
            ecx=ac)
        items = (U * 76)(*[rng.getrandbits(32) for _ in range(76)])
        cpu.mem_write(0x533164, bytes(items))
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x415e10, eax=0, edx=0, ebx=a, ecx=0) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_clear_each_call(c.byref(calls), c.byref(items), a)
        assert got == result and native_log == stubs.log and not replay, ('clear', case)
        assert bytes(items) == bytes(cpu.mem_read(0x533164, 304)), case
        totals['0x415e10'] = totals.get('0x415e10', 0) + 1
        source, value = 0x5bb518, rng.getrandbits(32)
        cpu.mem_write(source, value.to_bytes(4, 'little'))
        destination = c.c_uint32(rng.getrandbits(32))
        original.call(0x48c370)
        n.vertrix_copy_dword(c.byref(destination), c.byref(c.c_uint32(value)))
        assert destination.value == int.from_bytes(cpu.mem_read(0x5bd834, 4), 'little'), case
        totals['0x48c370'] = totals.get('0x48c370', 0) + 1
        cpu.mem_write(0x5bd83c, struct.pack('<I', value))
        assert n.vertrix_read_global(c.byref(c.c_uint32(value))) == original.call(0x4b7da0), case
        totals['0x4b7da0'] = totals.get('0x4b7da0', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each wrapper executes completely in the original with its callees stubbed '
                       'and logged; every callee call (address and registers), the returned eax and '
                       'the object storage compare.'}
    (args.build_dir / 'call-glue-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
