"""Compare the original object accessor wrappers with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x400
GLOBAL_HIT = 0x5bd828
BIG = 0x900000
BIG_SIZE = 0x6200
GLOBAL_FLAG = 0x553648


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next')]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


CALLEES = {0x4ca370: 0, 0x4abd70: 0, 0x4b65a0: 1, 0x4d74d1: 0, 0x4d8177: 0, 0x4d67a8: 0, 0x4ccf3b: 0, 0x482050: 0, 0x478d80: 0, 0x48a910: 0, 0x477e10: 1, 0x4d86d0: 0, 0x4d7630: 0, 0x478460: 0, 0x4ca210: 0, 0x4823b0: 0, 0x4ca070: 0, 0x478480: 0, 0x48aa80: 0, 0x48aa90: 0, 0x4ac130: 0, 0x4ca050: 0, 0x4d7510: 0, 0x47fa40: 0, 0x4d8b30: 0, 0x476090: 0, 0x4760f0: 0, 0x4766b0: 0, 0x418840: 0, 0x4d4060: 0, 0x4d83f0: 0, 0x4d01a0: 0, 0x4ccb9f: 0, 0x4ca040: 0, 0x4ac980: 0, 0x4b6540: 0, 0x440610: 1, 0x43f460: 0, 0x4d88a0: 0, 0x4ae010: 0, 0x4ec160: 0, 0x478d10: 0, 0x47fa40: 0,
           0x43f460: 0, 0x4d8650: 0, 0x4b79c0: 0,
           0x475af0: 0, 0x475790: 1, 0x4759e0: 0, 0x40a860: 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'object-glue', ['object_glue.c', 'call_glue.c', 'actor_storage.c', 'table_queries.c'])
    P, V, S = c.POINTER(Calls), c.c_void_p, c.c_size_t
    for name, types in (
            ('vertrix_object_set_mode', [c.POINTER(Services), U, V, S, U]),
            ('vertrix_object_parent_append', [U, V, S, S]),
            ('vertrix_object_start_5182c4', [c.POINTER(Services), U, U]),
            ('vertrix_object_glyph_layout', [V, S, U, U]),
            ('vertrix_object_glyph_present', [V, S, U]),
            ('vertrix_object_release_call', [U, V, S, U]),
            ('vertrix_object_match_append', [U, V, S, V, S]),
            ('vertrix_object_alloc_pair', [U, V, S]),
            ('vertrix_object_list_init', [U, V, S, U, U, U]),
            ('vertrix_slot_select', [U, V, S, U, c.POINTER(U)]),
            ('vertrix_literal_copy_call', [U, V, S, V, S]), ('vertrix_object_notify_field', [U, V, S, U]),
            ('vertrix_object_notify_global', [U, V, S, U]),
            ('vertrix_object_notify_choice', [U, V, S, c.c_uint8, c.c_uint8]),
            ('vertrix_object_notify_byte', [U, V, S, c.c_uint8]),
            ('vertrix_object_parent_glyph', [c.POINTER(Services), V, S, U]),
            ('vertrix_object_table_new', [c.POINTER(Services), U, U, U]),
            ('vertrix_object_first_field8', [c.POINTER(Services), U, U]),
            ('vertrix_object_alloc_arrays', [V, S, U, U]),
            ('vertrix_object_delegate', [U, U, U, V, S])):
        function = getattr(n, name)
        function.argtypes = [P] + types
        function.restype = U
    n.vertrix_object_destroy_call.argtypes = [P, U, V, S, U]
    n.vertrix_object_destroy_call.restype = U
    n.vertrix_object_unknown_init.argtypes = [V, S, U]
    n.vertrix_object_unknown_init.restype = U
    n.vertrix_object_unknown_reset.argtypes = [P, V, S, U, U]
    n.vertrix_object_unknown_reset.restype = U
    n.vertrix_stream_skip_line.argtypes = [P, c.POINTER(Services), U, U]
    n.vertrix_stream_skip_line.restype = U
    n.vertrix_object_step_field.argtypes = [P, V, S, U]
    n.vertrix_object_step_field.restype = U
    n.vertrix_object_create_with_class.argtypes = [P, c.POINTER(Services), U]
    n.vertrix_object_create_with_class.restype = U
    n.vertrix_object_step_toggle.argtypes = [P, U, V, S, U, U]
    n.vertrix_object_step_toggle.restype = U
    n.vertrix_object_record_new.argtypes = [P, c.POINTER(Services), U, U, U, c.c_uint8]
    n.vertrix_object_record_new.restype = U
    n.vertrix_object_surface_format.argtypes = [P, c.POINTER(Services), U, V, S]
    n.vertrix_object_surface_format.restype = U
    for name in ('vertrix_object_text_length_matches', 'vertrix_object_clamp_text_length'):
        getattr(n, name).argtypes = [c.POINTER(Services), V, S]
        getattr(n, name).restype = U
    n.vertrix_object_init_4c3fa0.argtypes = [V, S]
    n.vertrix_object_reset_block.argtypes = [V, S, V]
    n.vertrix_object_chain_at.argtypes = [c.POINTER(Services), V, S, U]
    n.vertrix_object_chain_at.restype = U
    n.vertrix_object_contains.argtypes = [V, S, c.c_int16, c.c_int16, c.POINTER(U)]
    n.vertrix_object_contains.restype = U
    n.vertrix_stream_skip_blank.argtypes = [P, V, U, U, U]
    n.vertrix_stream_skip_blank.restype = U
    n.vertrix_object_center_setup.argtypes = [P, V, S, U, U, U]
    n.vertrix_object_center_setup.restype = U
    n.vertrix_object_construct_labeled.argtypes = [P, V, U]
    n.vertrix_object_construct_labeled.restype = U
    n.vertrix_object_construct_labeled_box.argtypes = [P, V, U]
    n.vertrix_object_construct_labeled_box.restype = U
    for name in ('a', 'b', 'd', 'e'):
        getattr(n, 'vertrix_object_destroy_' + name).argtypes = [P, V, U, U]
        getattr(n, 'vertrix_object_destroy_' + name).restype = U
    n.vertrix_object_center_place.argtypes = [P, V, S, U, U, U, U, U]
    n.vertrix_object_center_place.restype = U
    n.vertrix_object_center_titled.argtypes = [P, V, U, U, U]
    n.vertrix_object_center_titled.restype = U
    n.vertrix_object_construct_e.argtypes = [P, V, U, U]
    n.vertrix_object_construct_e.restype = U
    n.vertrix_object_construct_f.argtypes = [P, V, U, c.POINTER(U)]
    n.vertrix_object_construct_f.restype = U
    n.vertrix_object_construct_g.argtypes = [P, V, U, U]
    n.vertrix_object_construct_g.restype = U
    n.vertrix_object_set_text.argtypes = [P, V, U, c.c_char_p]
    n.vertrix_object_set_text.restype = U
    n.vertrix_object_destroy_g.argtypes = [P, V, U, U, U]
    n.vertrix_object_destroy_g.restype = U
    n.vertrix_object_destroy_h.argtypes = [P, V, U, U, U]
    n.vertrix_object_destroy_h.restype = U
    n.vertrix_object_is_idle.argtypes = [V, U]
    n.vertrix_object_is_idle.restype = U
    n.vertrix_object_destroy_f.argtypes = [P, V, U, U]
    n.vertrix_object_destroy_f.restype = U
    n.vertrix_object_destroy_c.argtypes = [P, V, U, U, U]
    n.vertrix_object_destroy_c.restype = U
    n.vertrix_object_reset_center.argtypes = [P, V, S, U, U, U]
    n.vertrix_object_reset_center.restype = U
    n.vertrix_forward_registers.argtypes = [P, U, U, U, U, U]
    n.vertrix_forward_registers.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4b4510)
    pool = Pool(cpu, 8, SIZE)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ccf3b and use_big:
            returns.append(BIG)
        elif address in (0x4abd70, 0x4ec160, 0x478d10, 0x4d8650, 0x4ccf3b, 0x4d7510):
            returns.append(rng.choice(pool.handles))
        elif address == 0x4ca070:
            returns.append(rng.choice(pool.handles) + 0x15c)
        elif address == 0x48aa80:
            returns.append(rng.choice(pool.handles))
        elif address == 0x4b79c0:
            returns.append(rng.choice(pool.handles + [0]))
        else:
            returns.append(rng.choice([0, 1, 0xfffffff6, rng.getrandbits(32)]))
        return returns[-1]

    use_big = []
    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) +
                          (s.stack, s.stack_next)[:CALLEES[s.target]])
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve, None, None, None, None)
    totals = {}
    idle_hits = {}
    titled = c.create_string_buffer(0x80)
    big = c.create_string_buffer(BIG_SIZE)
    cpu.mem_map(BIG, 0x10000)

    @Resolve
    def resolve_titled(handle, storage, size, context):
        if handle == BIG:
            storage[0] = c.addressof(big)
            size[0] = BIG_SIZE
            return 1
        if handle == 0x5588f8:
            storage[0] = c.addressof(titled)
            size[0] = 0x80
            return 1
        return pool._resolve(handle, storage, size, context)

    titled_services = Services(resolve_titled, None, None, None, None)

    def patch(handle, data):
        struct.pack_into('<I', data, 0x160, rng.choice(pool.handles))
        left, top = rng.randrange(-50, 50), rng.randrange(-50, 50)
        struct.pack_into('<hhhh', data, 0x16a, left, left + rng.randrange(-5, 120),
                         top, top + rng.randrange(-5, 120))
        struct.pack_into('<hh', data, 0x16c, left + rng.randrange(-5, 120),
                         left + rng.randrange(-5, 120))
        struct.pack_into('<I', data, 0xc, rng.choice(pool.handles + [0]))
        struct.pack_into('<I', data, 0x60, rng.choice(pool.handles + [0]))
        struct.pack_into('<II', data, 0x38, rng.randrange(1, 4), 0)
        struct.pack_into('<I', data, 0x4, rng.randrange(1, 4))
        data[0x1f0] = 0
        struct.pack_into('<I', data, 0x15c, rng.choice(pool.handles))
        struct.pack_into('<I', data, 0x44, rng.choice([1, 1, 0, 2]))
        struct.pack_into('<i', data, 0x170, rng.randrange(-3, 6))
        data[rng.randrange(0, 4)] = rng.choice([0, 7])
        struct.pack_into('<h', data, 0x16e, top)
        struct.pack_into('<h', data, 0x170, top + rng.randrange(-5, 120))

    def run(name, address, native, **registers):
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(address, **registers) & 0xffffffff
        replay[:] = list(returns)
        got = native()
        assert got == result, (name, hex(got), hex(result))
        assert native_log == stubs.log, (name, native_log, stubs.log)
        assert not replay, name
        assert pool.same(), (name, pool.diff())
        totals[hex(address)] = totals.get(hex(address), 0) + 1

    for case in range(args.cases):
        pool.fill(rng, patch)
        obj = rng.choice(pool.handles)
        ebx = rng.getrandbits(32)
        buffer = pool.buffers[obj]
        value = rng.choice([1, 1, 0, 2, rng.getrandbits(32)])
        run('mode', 0x4b4510, lambda: n.vertrix_object_set_mode(
            c.byref(calls), c.byref(services), obj, buffer, SIZE, value), eax=obj, edx=value)
        for address, field in ((0x4b4c90, 0x188), (0x4b4cd0, 0x18c)):
            run('append', address, lambda: n.vertrix_object_parent_append(
                c.byref(calls), obj, buffer, SIZE, field), eax=obj, edx=0)
        edx = rng.getrandbits(32)
        eax_in = rng.getrandbits(32)
        run('start', 0x4b5c60, lambda: n.vertrix_object_start_5182c4(
            c.byref(calls), c.byref(services), obj, edx), eax=obj, edx=edx)
        x, y = rng.randrange(-80, 200), rng.randrange(-80, 200)
        cpu.mem_write(GLOBAL_HIT, bytes(4))
        hit = U(5)
        result = original.call(0x4b66c0, eax=obj, edx=x & 0xffff, ebx=y & 0xffff) & 0xffffffff
        got = n.vertrix_object_contains(buffer, SIZE, x, y, c.byref(hit))
        assert got == result, ('contains', got, result)
        assert hit.value == int.from_bytes(cpu.mem_read(GLOBAL_HIT, 4), 'little'), case
        totals['0x4b66c0'] = totals.get('0x4b66c0', 0) + 1
        ebx = rng.getrandbits(32)
        run('layout', 0x4b69f0, lambda: n.vertrix_object_glyph_layout(
            c.byref(calls), buffer, SIZE, edx, ebx), eax=obj, edx=edx, ebx=ebx)
        run('present', 0x4b6a10, lambda: n.vertrix_object_glyph_present(
            c.byref(calls), buffer, SIZE, edx), eax=obj, edx=edx)
        run('release', 0x4b6f70, lambda: n.vertrix_object_release_call(
            c.byref(calls), obj, buffer, SIZE, edx), eax=obj, edx=edx)
        other = rng.choice(pool.handles)
        run('match', 0x47ecd0, lambda: n.vertrix_object_match_append(
            c.byref(calls), obj, buffer, SIZE, pool.buffers[other], SIZE), eax=obj, edx=other)
        index = rng.randrange(0, 7)
        stubs.log.clear()
        result = original.call(0x47f190, eax=obj, edx=index) & 0xffffffff
        got = n.vertrix_object_chain_at(c.byref(services), buffer, SIZE, index)
        assert got == result, ('chain', hex(got), hex(result))
        totals['0x47f190'] = totals.get('0x47f190', 0) + 1
        for address in (0x4879f0, 0x48d600, 0x4b79a0):
            run('release2', address, lambda: n.vertrix_object_release_call(
                c.byref(calls), obj, buffer, SIZE, edx), eax=obj, edx=edx)
        run('pair', 0x482720, lambda: n.vertrix_object_alloc_pair(c.byref(calls), obj, buffer,
                                                                   SIZE), eax=obj, edx=0)
        a, b = rng.getrandbits(32), rng.getrandbits(32)
        glob = rng.randrange(256)
        cpu.mem_write(0x5b9ca6, bytes([glob]))
        run('record', 0x487280, lambda: n.vertrix_object_record_new(
            c.byref(calls), c.byref(services), a, b, ebx, glob), eax=a, edx=b, ebx=ebx)
        count = rng.getrandbits(32)
        run('arrays', 0x487710, lambda: n.vertrix_object_alloc_arrays(
            c.byref(calls), buffer, SIZE, obj, count), eax=obj, edx=count)
        run('surface', 0x4872c0, lambda: n.vertrix_object_surface_format(
            c.byref(calls), c.byref(services), obj, buffer, SIZE), eax=obj, edx=0, ebx=0)
        if rng.random() < 0.3:
            struct.pack_into('<I', buffer, 0x38, 0)
            cpu.mem_write(obj + 0x38, bytes(4))
        run('delegate', 0x48c9b0, lambda: n.vertrix_object_delegate(
            c.byref(calls), obj, edx, ebx, buffer, SIZE), eax=obj, edx=edx, ebx=ebx)
        for handle in pool.handles:
            pointer = struct.pack('<I', rng.choice(pool.handles))
            cpu.mem_write(handle + 0x160, pointer)
            pool.buffers[handle][0x160:0x164] = pointer
        for address, offset in ((0x48c260, 0x1cc), (0x48c310, 0x1e4), (0x48c330, 0x1e5)):
            run('field', address, lambda: n.vertrix_object_notify_field(c.byref(calls), obj, buffer, SIZE,
                                                                       offset),
                eax=obj, edx=0)
        glob = rng.getrandbits(32)
        cpu.mem_write(0x598d40, struct.pack('<I', glob))
        run('global', 0x48c280, lambda: n.vertrix_object_notify_global(
            c.byref(calls), obj, buffer, SIZE, glob), eax=obj, edx=0)
        bytes3 = [rng.randrange(256) for _ in range(3)]
        cpu.mem_write(0x532a68, bytes([bytes3[0], 0, 0, 0, bytes3[1], 0, 0, 0, bytes3[2]]))
        run('choice', 0x48c2b0, lambda: n.vertrix_object_notify_choice(
            c.byref(calls), obj, buffer, SIZE, bytes3[0], bytes3[1]), eax=obj, edx=0)
        run('byte', 0x48c2e0, lambda: n.vertrix_object_notify_byte(
            c.byref(calls), obj, buffer, SIZE, bytes3[2]), eax=obj, edx=0)
        step_state = rng.choice([0, 1, 1, 2])
        struct.pack_into('<I', buffer, 0x64, step_state)
        cpu.mem_write(obj + 0x64, struct.pack('<I', step_state))
        run('step', 0x45d820, lambda: n.vertrix_object_step_toggle(
            c.byref(calls), obj, buffer, SIZE, edx, 0x1234), eax=obj, edx=edx, ebx=0x1234)
        destroy_flags = rng.getrandbits(32) if rng.random() < 0.5 else rng.randrange(0, 8)
        run('destroy', 0x4b5420, lambda: n.vertrix_object_destroy_call(
            c.byref(calls), obj, buffer, SIZE, destroy_flags), eax=obj, edx=destroy_flags)
        run('unknown', 0x48a620, lambda: n.vertrix_object_unknown_init(buffer, SIZE, obj), eax=obj)
        owner = rng.choice([0, rng.getrandbits(32)])
        struct.pack_into('<I', buffer, 0, owner)
        cpu.mem_write(obj, struct.pack('<I', owner))
        run('unknown_reset', 0x48a8c0, lambda: n.vertrix_object_unknown_reset(
            c.byref(calls), buffer, SIZE, obj, a), eax=obj, ebx=a)
        run('skip', 0x48a380, lambda: n.vertrix_stream_skip_line(
            c.byref(calls), c.byref(services), edx, a), edx=edx, ebx=a, eax=0)
        for handle in pool.handles:
            first = bytes([rng.choice(b' \n\r/x/ ')])
            cpu.mem_write(handle, first)
            c.memmove(pool.buffers[handle], first, 1)
        run('blank', 0x48a310, lambda: n.vertrix_stream_skip_blank(
            c.byref(calls), c.byref(services), edx, a, edx), edx=edx, eax=a)
        width, height = rng.randrange(1, 0x10000), rng.randrange(1, 0x10000)
        cpu.mem_write(0x5b9c8e, struct.pack('<H', width))
        cpu.mem_write(0x5b9c90, struct.pack('<H', height))
        run('center', 0x477d70, lambda: n.vertrix_object_center_setup(
            c.byref(calls), buffer, SIZE, obj, width, height), eax=obj)
        for offset in (0x58, 0x5c, 0x60):
            small = rng.randrange(-40, 40) & 0xffffffff
            struct.pack_into('<I', buffer, offset, small)
            cpu.mem_write(obj + offset, struct.pack('<I', small))
        run('step_field', 0x4ad720, lambda: n.vertrix_object_step_field(
            c.byref(calls), buffer, SIZE, edx), eax=obj, edx=edx)
        run('create', 0x481f30, lambda: n.vertrix_object_create_with_class(
            c.byref(calls), c.byref(services), eax_in), eax=eax_in)
        run('parent', 0x4b4cb0, lambda: n.vertrix_object_parent_glyph(
            c.byref(calls), c.byref(services), buffer, SIZE, edx), eax=obj, edx=edx)
        for address, table in ((0x4b78d0, 0x518704), (0x48d520, 0x517a94)):
            run('table', address, lambda: n.vertrix_object_table_new(
                c.byref(calls), c.byref(services), 0, 0, table), eax=0, edx=0)
        run('field8', 0x4b7a80, lambda: n.vertrix_object_first_field8(
            c.byref(calls), c.byref(services), 0, 0), eax=0, edx=0)
        for handle in pool.handles:
            pointer = struct.pack('<I', rng.choice(pool.handles))
            cpu.mem_write(handle + 0x15c, pointer)
            pool.buffers[handle][0x15c:0x160] = pointer
        run('text', 0x4b4660, lambda: n.vertrix_object_text_length_matches(
            c.byref(services), buffer, SIZE), eax=obj, edx=0)
        run('clamp', 0x4b4690, lambda: n.vertrix_object_clamp_text_length(
            c.byref(services), buffer, SIZE), eax=obj, edx=0)
        original.call(0x4c3fa0, eax=obj)
        assert n.vertrix_object_init_4c3fa0(buffer, SIZE)
        assert pool.same(), ('init', pool.diff())
        totals['0x4c3fa0'] = totals.get('0x4c3fa0', 0) + 1
        source = rng.randbytes(16)
        cpu.mem_write(0x558ce0, source)
        original.call(0x47f070, eax=obj)
        assert n.vertrix_object_reset_block(buffer, SIZE, source)
        assert pool.same(), ('block', pool.diff())
        totals['0x47f070'] = totals.get('0x47f070', 0) + 1
        run('listinit', 0x475a20, lambda: n.vertrix_object_list_init(
            c.byref(calls), obj, buffer, SIZE, 0, 0, 0), eax=obj, edx=0, ebx=0, ecx=0)
        index = rng.randrange(0, 5)
        for slot in range(5):
            value = rng.choice([0, 1, 1, 7])
            buffer[0x60 * slot] = value
            cpu.mem_write(obj + 0x60 * slot, bytes([value]))
        selected = U(0)
        run('select', 0x4762e0, lambda: n.vertrix_slot_select(
            c.byref(calls), obj, buffer, SIZE, index, c.byref(selected)), eax=obj, edx=index,
            ebx=0, ecx=0)
        assert selected.value == int.from_bytes(cpu.mem_read(0x54d630, 4), 'little'), case
        text = bytes(cpu.mem_read(0x50e99f, 64)).split(b'\0')[0] + b'\0'
        out = c.create_string_buffer(128)
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        result = original.call(0x478c90, eax=obj, edx=0, ebx=0, ecx=0) & 0xffffffff
        replay[:] = list(returns)
        got = n.vertrix_literal_copy_call(c.byref(calls), obj, out, 128, text, len(text))
        assert got == result and native_log == stubs.log, ('copy', got, result)
        assert out.raw[:len(text)] == bytes(cpu.mem_read(0x558970, len(text))), case
        totals['0x478c90'] = totals.get('0x478c90', 0) + 1
        regs = [rng.getrandbits(32) for _ in range(4)]
        run('forward', 0x4b6890, lambda: n.vertrix_forward_registers(c.byref(calls), 0x4ae010,
                                                                      *regs),
            eax=regs[0], edx=regs[1], ebx=regs[2], ecx=regs[3])
        for name, address, function in (('labeled', 0x4b2400, n.vertrix_object_construct_labeled),
                                        ('labeled_box', 0x4b6350,
                                         n.vertrix_object_construct_labeled_box)):
            pool.fill(rng, patch)
            run(name, address, lambda: function(c.byref(calls), c.byref(services), obj), eax=obj)
        flags, ebx_in = rng.randrange(0, 8), rng.getrandbits(32)
        pool.fill(rng, patch)
        run('destroy_a', 0x4b5dc0, lambda: n.vertrix_object_destroy_a(
            c.byref(calls), c.byref(services), obj, flags), eax=obj, edx=flags)
        pool.fill(rng, patch)
        run('destroy_b', 0x481fb0, lambda: n.vertrix_object_destroy_b(
            c.byref(calls), c.byref(services), obj, flags), eax=obj, edx=flags)
        pool.fill(rng, patch)
        run('destroy_c', 0x429350, lambda: n.vertrix_object_destroy_c(
            c.byref(calls), c.byref(services), obj, flags, ebx_in), eax=obj, edx=flags, ebx=ebx_in)
        for name, address in (('d', 0x4b6460), ('e', 0x488b90)):
            pool.fill(rng, patch)
            run('destroy_' + name, address, lambda: getattr(n, 'vertrix_object_destroy_' + name)(
                c.byref(calls), c.byref(services), obj, flags), eax=obj, edx=flags)
        pool.fill(rng, patch)
        run('construct_e', 0x488b10, lambda: n.vertrix_object_construct_e(
            c.byref(calls), c.byref(services), STACK - 4, obj), eax=obj)
        pool.fill(rng, patch)
        data = rng.randbytes(BIG_SIZE)
        cpu.mem_write(BIG, data)
        big.raw = data
        cpu.mem_write(GLOBAL_FLAG, bytes(4))
        flag = U(0)
        use_big.append(1)
        run('construct_f', 0x475ec0, lambda: n.vertrix_object_construct_f(
            c.byref(calls), c.byref(titled_services), obj, c.byref(flag)), eax=obj)
        use_big.clear()
        assert flag.value == int.from_bytes(cpu.mem_read(GLOBAL_FLAG, 4), 'little')
        assert big.raw == bytes(cpu.mem_read(BIG, BIG_SIZE))
        pool.fill(rng, patch)
        run('construct_g', 0x487b00, lambda: n.vertrix_object_construct_g(
            c.byref(calls), c.byref(services), STACK - 4, obj), eax=obj)
        pool.fill(rng, patch)
        text = bytes(rng.randrange(1, 256) for _ in range(rng.choice([0, 1, 5, 0x40, 0xff, 0x100, 0x101, 0x180])))
        cpu.mem_write(0x80c000, text + b'\0')
        run('set_text', 0x47faf0, lambda: n.vertrix_object_set_text(
            c.byref(calls), c.byref(services), obj, text), eax=obj, edx=0x80c000)
        pool.fill(rng, patch)
        run('destroy_g', 0x4d8b80, lambda: n.vertrix_object_destroy_g(
            c.byref(calls), c.byref(services), obj, flags, ebx_in), eax=obj, edx=flags, ebx=ebx_in)
        pool.fill(rng, patch)
        owner = rng.choice([0, rng.getrandbits(32)])
        struct.pack_into('<I', pool.buffers[obj], 0, owner)
        cpu.mem_write(obj, struct.pack('<I', owner))
        run('destroy_h', 0x48a670, lambda: n.vertrix_object_destroy_h(
            c.byref(calls), c.byref(services), obj, flags, ebx_in), eax=obj, edx=flags, ebx=ebx_in)
        other = rng.choice([h for h in pool.handles if h != obj])
        shared = rng.getrandbits(32)

        def idle_patch(handle, data):
            if handle == obj:
                struct.pack_into('<I', data, 0xd8, other)
                wanted = {0x4c: 0, 0x12c: 0, 0x28: 3, 0x24: 3, 0x2c: 2, 0x78: 3, 0x13c: shared}
            else:
                wanted = {0x8: 2, 0x5c: 1, 0xb0: 1, 0xc: rng.choice([0, 1, 2, 3, 0xffffffff]),
                          0x60: 1, 0xb4: 1, 0x24: shared, 0x78: shared, 0xcc: shared}
            for offset, value in wanted.items():
                if rng.random() < 0.97:
                    struct.pack_into('<I', data, offset, value)

        pool.fill(rng, idle_patch)
        idle = n.vertrix_object_is_idle(c.byref(services), obj)
        idle_hits[idle] = idle_hits.get(idle, 0) + 1
        run('idle', 0x4c0b51, lambda: n.vertrix_object_is_idle(c.byref(services), obj), eax=obj)
        pool.fill(rng, patch)
        run('destroy_f', 0x4d3f70, lambda: n.vertrix_object_destroy_f(
            c.byref(calls), c.byref(services), obj, flags), eax=obj, edx=flags)
        pool.fill(rng, patch)
        buffer = pool.buffers[obj]
        state = rng.choice([1, 1, 0, 2])
        struct.pack_into('<I', buffer, 0x60, state)
        cpu.mem_write(obj + 0x60, struct.pack('<I', state))
        width, height = rng.randrange(1, 0x10000), rng.randrange(1, 0x10000)
        cpu.mem_write(0x5b9c8e, struct.pack('<H', width))
        cpu.mem_write(0x5b9c90, struct.pack('<H', height))
        place_state = rng.choice([0, 0, 1])
        struct.pack_into('<I', buffer, 0x60, place_state)
        cpu.mem_write(obj + 0x60, struct.pack('<I', place_state))
        place_ebx, place_ecx = rng.getrandbits(32), rng.getrandbits(32)
        run('center_place', 0x477e30, lambda: n.vertrix_object_center_place(
            c.byref(calls), buffer, SIZE, obj, place_ebx, place_ecx, width, height), eax=obj,
            edx=place_ecx, ebx=place_ebx)
        struct.pack_into('<I', buffer, 0x60, state)
        cpu.mem_write(obj + 0x60, struct.pack('<I', state))
        data = bytearray(rng.randbytes(0x80))
        struct.pack_into('<I', data, 0x60, rng.choice([0, 0, 1]))
        cpu.mem_write(0x5588f8, bytes(data))
        titled.raw = bytes(data)
        run('center_titled', 0x424760, lambda: n.vertrix_object_center_titled(
            c.byref(calls), c.byref(titled_services), obj, width, height), eax=obj)
        assert titled.raw == bytes(cpu.mem_read(0x5588f8, 0x80))
        run('reset_center', 0x477ed0, lambda: n.vertrix_object_reset_center(
            c.byref(calls), buffer, SIZE, obj, width, height), eax=obj)
    assert idle_hits.get(1, 0) > 5 and idle_hits.get(0, 0) > 5, idle_hits
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Each wrapper executes completely in the original with its callees stubbed '
                       'and logged; every callee call (address and registers), the returned eax, '
                       'the global 0x5bd828 and every pool object compare.'}
    (args.build_dir / 'object-glue-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
