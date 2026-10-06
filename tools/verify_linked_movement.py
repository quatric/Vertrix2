"""Compare all linked movement phases and local/shared refresh with original x86."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, BOARD, MASK
from verify_number_transition import Timer
from verify_linked_alternating import ObjectList, Resolve


class Movement(c.Structure):
    _fields_ = [(name, c.c_uint32) for name in
                ['threshold', 'source', 'active', 'refresh', 'handler']] + [
                (name, c.c_int16) for name in
                ['origin_y', 'y', 'target_y', 'step_y', 'refresh_index']] + [
                ('primary', Timer), ('secondary', Timer)]


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'linked-movement.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
                    *[str(source / name) for name in
                      ['linked_movement.c', 'timer.c', 'word_transition.c',
                       'ui_companion_update.c', 'actor_storage.c', 'actor_lookup.c', 'object_list.c',
                       'ui_indicator_update.c', 'linked_indicator.c', 'byte_transition.c', 'ui_border_update.c', 'linked_burst.c', 'random.c', 'ui_actor_frame.c', 'ui_actor_update.c', 'linked_alternating.c',
                       'block_resource.c', 'frame_resource.c', 'animation.c', 'dword_transition.c']],
                    '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_linked_movement_update.argtypes = [c.POINTER(Movement), c.c_int,
        c.c_uint32, c.c_uint32, c.c_int16, c.c_uint32, c.POINTER(c.c_uint32), c.c_size_t]
    native.vertrix_ui_companion_storage_update.argtypes = [c.c_void_p, c.c_size_t, c.c_int,
        c.c_uint32, c.c_uint32, c.c_int16, c.c_uint32, c.POINTER(c.c_uint32), c.c_size_t]
    native.vertrix_ui_companion_storage_update_list.argtypes = [c.c_void_p, c.c_size_t,
        c.POINTER(ObjectList), Resolve, c.c_void_p, c.c_int16, c.c_uint32,
        c.POINTER(c.c_uint32), c.c_size_t]
    native.vertrix_ui_actor_frame_update.argtypes = [c.c_void_p, c.c_size_t,
        c.POINTER(ObjectList), Resolve, c.c_void_p, c.c_int, c.c_int16, c.c_uint32,
        c.POINTER(c.c_uint32), c.c_size_t, c.c_void_p, c.c_void_p, c.c_size_t]
    buffers = {}
    @Resolve
    def resolve(handle, storage, size, context):
        if handle not in buffers:
            return 0
        storage[0], size[0] = c.addressof(buffers[handle]), len(buffers[handle])
        return 1
    original = Original(a.executable)
    cpu = original.cpu
    rng = random.Random(0x450860)
    changes = 0
    for case in range(12288):
        handler = [0x450860, 0x4508c0, 0x450920, 0x450960, 0x4509a0, 0x4509d0][case % 6]
        present = (case // 6) % 3 != 0
        linked_value = rng.choice([0, 1, 2, rng.getrandbits(32)])
        linked_state = rng.getrandbits(32)
        start_y = rng.randrange(-32768, 32768)
        elapsed = rng.choice([0, 1, 100, rng.getrandbits(32)])
        state = Movement(*[rng.getrandbits(32) for _ in range(4)], handler,
                         *[rng.randrange(-32768, 32768) for _ in range(4)],
                         rng.choice([-1, 0, 1, 7]),
                         Timer(rng.getrandbits(32), rng.choice([0, 1, 100, 0xffffffff])),
                         Timer(rng.getrandbits(32), rng.choice([0, 1, 100, 0xffffffff])))
        if case % 12 == 1:
            state.y = state.target_y
        raw = bytearray(rng.randbytes(0x160))
        offsets = [('threshold', 0x58, 'I'), ('source', 0x134, 'I'), ('active', 0x124, 'I'),
                   ('refresh', 0x120, 'I'), ('handler', 0x154, 'I'), ('origin_y', 0xa, 'h'),
                   ('y', 0x16, 'h'), ('target_y', 0x18, 'h'), ('step_y', 0x1a, 'h'),
                   ('refresh_index', 0x148, 'h')]
        for name, offset, fmt in offsets:
            struct.pack_into('<' + fmt, raw, offset, getattr(state, name))
        for timer, offset in [(state.primary, 0xbc), (state.secondary, 0xdc)]:
            struct.pack_into('<2I', raw, offset, timer.counter, timer.period)
        identity = rng.getrandbits(32)
        struct.pack_into('<I', raw, 4, identity)
        linked = bytearray(rng.randbytes(0x160))
        struct.pack_into('<I', linked, 0, identity)
        struct.pack_into('<I', linked, 0x58, linked_value)
        struct.pack_into('<I', linked, 0x64, linked_state)
        cpu.mem_write(BOARD, bytes(raw))
        cpu.mem_write(0x804000, bytes(linked))
        duplicate = bytearray(linked)
        struct.pack_into('<I', duplicate, 0x58, (1 - linked_value) & 0xffffffff)
        struct.pack_into('<I', duplicate, 0x64, linked_state ^ 0xffffffff)
        cpu.mem_write(0x804200, bytes(duplicate))
        cpu.mem_write(MASK, struct.pack('<2I', 0x804000, 0x804200))
        cpu.mem_write(0x54671c, struct.pack('<3I', 0, MASK, 2 if present else 0))
        buffers = {0x804000: c.create_string_buffer(bytes(linked), len(linked)),
                   0x804200: c.create_string_buffer(bytes(duplicate), len(duplicate))}
        handles = (c.c_uint32 * 2)(0x804000, 0x804200)
        listed = ObjectList(handles, 2 if present else 0, 2)
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        cpu.mem_write(0x533d78, struct.pack('<h', start_y))
        refresh = (c.c_uint32 * 8)(*[rng.getrandbits(32) for _ in range(8)])
        cpu.mem_write(0x5bb714, bytes(refresh))
        portable = c.create_string_buffer(bytes(raw), len(raw))
        portable_refresh = (c.c_uint32 * 8).from_buffer_copy(bytes(refresh))
        listed_storage = c.create_string_buffer(bytes(raw), len(raw))
        listed_refresh = (c.c_uint32 * 8).from_buffer_copy(bytes(refresh))
        frame_raw = bytearray(raw)
        struct.pack_into('<2I', frame_raw, 0x104, 0, 0)
        struct.pack_into('<I', frame_raw, 0x158, 0x517af4)
        cpu.mem_write(BOARD, bytes(frame_raw))
        cpu.mem_write(0x5bb710, struct.pack('<I', case % 2))
        framed = c.create_string_buffer(bytes(frame_raw), len(frame_raw))
        frame_refresh = (c.c_uint32 * 8).from_buffer_copy(bytes(refresh))
        original.call(0x4ae150, eax=BOARD)
        assert native.vertrix_ui_actor_frame_update(framed, len(frame_raw), c.byref(listed),
            resolve, None, case % 2, start_y, elapsed, frame_refresh, 8, None, None, 1)
        assert framed.raw == bytes(cpu.mem_read(BOARD, len(frame_raw))), (case, 'frame')
        assert bytes(frame_refresh) == bytes(cpu.mem_read(0x5bb714, 32)), (case, 'frame refresh')
        cpu.mem_write(BOARD, bytes(raw))
        cpu.mem_write(0x5bb714, bytes(refresh))
        original.call(handler, eax=BOARD)
        assert native.vertrix_ui_companion_storage_update_list(listed_storage, len(raw),
            c.byref(listed), resolve, None, start_y, elapsed, listed_refresh, 8)
        assert listed_storage.raw == bytes(cpu.mem_read(BOARD, len(raw))), (case, 'list')
        assert bytes(listed_refresh) == bytes(cpu.mem_read(0x5bb714, 32)), (case, 'list refresh')
        assert native.vertrix_ui_companion_storage_update(portable, len(raw), present,
            linked_value, linked_state, start_y, elapsed, portable_refresh, 8)
        assert portable.raw == bytes(cpu.mem_read(BOARD, len(raw))), (case, 'storage')
        assert bytes(portable_refresh) == bytes(cpu.mem_read(0x5bb714, 32)), (case, 'refresh')
        assert native.vertrix_linked_movement_update(c.byref(state), present, linked_value,
                                                     linked_state, start_y, elapsed, refresh, 8)
        for name, offset, fmt in offsets:
            struct.pack_into('<' + fmt, raw, offset, getattr(state, name))
        for timer, offset in [(state.primary, 0xbc), (state.secondary, 0xdc)]:
            struct.pack_into('<2I', raw, offset, timer.counter, timer.period)
        assert bytes(raw) == bytes(cpu.mem_read(BOARD, len(raw))), (case, hex(handler))
        assert bytes(linked) == bytes(cpu.mem_read(0x804000, len(linked))), case
        assert bytes(refresh) == bytes(cpu.mem_read(0x5bb714, 32)), case
        changes += state.handler != handler
    raw = bytearray(portable.raw)
    struct.pack_into('<I', raw, 0x154, 0x450960)
    struct.pack_into('<2I', raw, 0xdc, 1, 1)
    struct.pack_into('<h', raw, 0x148, 8)
    invalid = c.create_string_buffer(bytes(raw), len(raw))
    before_refresh = bytes(portable_refresh)
    assert not native.vertrix_ui_companion_storage_update(invalid, len(raw), 1, 1, 0,
        0, 1, portable_refresh, 8)
    assert invalid.raw == bytes(raw) and bytes(portable_refresh) == before_refresh
    before_listed, before_listed_refresh = listed_storage.raw, bytes(listed_refresh)
    buffers.pop(0x804000)
    listed.count = 2
    assert not native.vertrix_ui_companion_storage_update_list(listed_storage, len(listed_storage),
        c.byref(listed), resolve, None, start_y, elapsed, listed_refresh, 8)
    assert listed_storage.raw == before_listed and bytes(listed_refresh) == before_listed_refresh
    assert not native.vertrix_ui_companion_storage_update(invalid, 0x15b, 1, 1, 0,
        0, 1, portable_refresh, 8)
    assert invalid.raw == bytes(raw) and bytes(portable_refresh) == before_refresh
    report = {'status': 'passed', 'cases': 12288, 'handler_changes': changes,
              'scope': 'All six complete original handlers without hooks. Whole effect object, '
                       'unchanged linked object and local/shared refresh match; actual lookup, '
                       'timers and signed-word movement execute. Portable companion-storage '
                       'dispatch also matches entire original actor and shared refresh storage '
                       'in every case. Invalid required refresh index and short actor preserve '
                       'both outputs. Scene-linked storage dispatch also matches all cases with '
                       'duplicate IDs/different values, selecting first field0 match; unresolved '
                       'handles preserve both outputs. Complete virtual frame wrapper4ae150/4ade20 '
                       'also matches actor/refresh output in12288 no-interaction/no-chain cases '
                       'with conditional refresh clearing. Full scene/application remains unfinished.'}
    (a.build_dir / 'linked-movement-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
