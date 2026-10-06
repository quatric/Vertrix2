"""Compare complete alternating linked display phases with original x86."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, BOARD, MASK
from verify_timer import Timer
from verify_animation import Animation
from verify_frame_resource import Resource


class Display(c.Structure):
    _fields_ = [(name, c.c_uint32) for name in ['threshold', 'source', 'phase', 'handler', 'descriptor']] + [(name, c.c_int16) for name in ['origin_y', 'y', 'target_y', 'step_y', 'effect', 'effect_target', 'effect_step']] + [(name, c.c_int32) for name in ['delay', 'delay_target', 'delay_step']] + [('primary', Timer), ('secondary', Timer), ('animation', Animation), ('resource', c.POINTER(Resource))]


class ObjectList(c.Structure):
    _fields_ = [('items', c.POINTER(c.c_uint32)), ('count', c.c_size_t), ('capacity', c.c_size_t)]
Resolve = c.CFUNCTYPE(c.c_int, c.c_uint32, c.POINTER(c.c_void_p), c.POINTER(c.c_size_t), c.c_void_p)


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    a = p.parse_args()
    a.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = a.build_dir.resolve() / 'linked-alternating.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror', * [str(source / name) for name in ['linked_alternating.c', 'block_resource.c', 'frame_resource.c', 'animation.c', 'timer.c', 'word_transition.c', 'dword_transition.c', 'ui_actor_update.c', 'actor_storage.c', 'object_list.c', 'actor_lookup.c', 'ui_indicator_update.c', 'linked_indicator.c', 'byte_transition.c', 'ui_border_update.c', 'linked_burst.c', 'random.c', 'ui_actor_frame.c', 'ui_companion_update.c', 'linked_movement.c']], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_linked_alternating_update.argtypes = [c.POINTER(Display), c.c_int, c.c_uint32, c.c_uint32, c.c_int16, c.c_uint32, c.POINTER(Resource), c.POINTER(Resource), c.c_size_t]
    native.vertrix_ui_actor_storage_update.argtypes = [c.c_void_p, c.c_size_t, c.c_int, c.c_uint32, c.c_uint32, c.c_int16, c.c_uint32, c.POINTER(Resource), c.POINTER(Resource), c.c_size_t]
    native.vertrix_ui_actor_storage_update_list.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(ObjectList), Resolve, c.c_void_p, c.c_int16, c.c_uint32, c.POINTER(Resource), c.POINTER(Resource), c.c_size_t]
    native.vertrix_ui_actor_frame_update.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(ObjectList), Resolve, c.c_void_p, c.c_int, c.c_int16, c.c_uint32, c.c_void_p, c.c_size_t, c.POINTER(Resource), c.POINTER(Resource), c.c_size_t]
    linked_buffers = {}
    @ Resolve
    def resolve(handle, storage, size, context):
        if handle not in linked_buffers:
            return 0
        storage[0] = c.addressof(linked_buffers[handle])
        size[0] = len(linked_buffers[handle])
        return 1
    original = Original(a.executable)
    cpu = original.cpu
    rng = random.Random(0x450a10)
    addresses = [0x546618, 0x546634, MASK]
    changes = bindings = 0
    offsets = [('threshold', 0x58, 'I'), ('source', 0x134, 'I'), ('phase', 0x7c, 'I'), ('handler', 0x154, 'I'), ('descriptor', 0xb4, 'I'), ('origin_y', 0xa, 'h'), ('y', 0x16, 'h'), ('target_y', 0x18, 'h'), ('step_y', 0x1a, 'h'), ('effect', 0x48, 'h'), ('effect_target', 0x4a, 'h'), ('effect_step', 0x4c, 'h'), ('delay', 0x70, 'i'), ('delay_target', 0x74, 'i'), ('delay_step', 0x78, 'i')]
    for case in range(12288):
        frames = [(c.c_uint32 * 4)(* [rng.getrandbits(32) for _ in range(4)]) for _ in range(3)]
        resources = [Resource(0, 4, values, None, None) for values in frames]
        for index, address in enumerate(addresses):
            storage = 0x803000 + index * 256
            cpu.mem_write(storage, bytes(frames[index]))
            cpu.mem_write(address, struct.pack('<6I', storage, 4, 0, 0, 0, 0))
        state = Display()
        for name, _, fmt in offsets:
            setattr(state, name, rng.getrandbits(32) if fmt == 'I' else rng.randrange(- 32768, 32768) if fmt == 'h' else rng.randrange(- 2147483648, 2147483648))
        state.handler = [0x450a10, 0x450aa0, 0x450b30, 0x450b90, 0x450bf0, 0x450c70][case % 6]
        handler = state.handler
        state.phase = rng.choice([0, 1, 2, 0xffffffff])
        if case % 12 == 1:
            state.y = state.target_y
        if case % 12 == 3:
            state.effect = state.effect_target
        for name in ['primary', 'secondary']:
            setattr(state, name, Timer(rng.getrandbits(32), rng.choice([0, 1, 100, 0xffffffff])))
        state.animation = Animation(Timer(rng.getrandbits(32), rng.getrandbits(32)), rng.randrange(4), 4)
        state.resource = c.pointer(resources[rng.randrange(2)])
        raw = bytearray(rng.randbytes(0x160))
        def encode():
            for name, offset, fmt in offsets:
                struct.pack_into('<' + fmt, raw, offset, getattr(state, name))
            for timer, offset in [(state.primary, 0xbc), (state.secondary, 0xdc), (state.animation.timer, 0xcc)]:
                struct.pack_into('<2I', raw, offset, timer.counter, timer.period)
            selected = next(i for i, resource in enumerate(resources) if c.addressof(resource) == c.addressof(state.resource.contents))
            struct.pack_into('<I', raw, 0xb0, addresses[selected])
            struct.pack_into('<I', raw, 0xb8, state.animation.frame)
            return selected
        initial_resource = encode()
        identity = rng.getrandbits(32)
        struct.pack_into('<I', raw, 4, identity)
        linked = bytearray(rng.randbytes(0x160))
        linked_value = rng.choice([0, 1, 2, rng.getrandbits(32)])
        linked_state = rng.getrandbits(32)
        struct.pack_into('<I', linked, 0, identity)
        struct.pack_into('<I', linked, 0x58, linked_value)
        struct.pack_into('<I', linked, 0x64, linked_state)
        present = (case // 6) % 3 != 0
        cpu.mem_write(0x804000, bytes(linked))
        duplicate = bytearray(linked)
        struct.pack_into('<I', duplicate, 0x58, 1 - linked_value & 0xffffffff)
        struct.pack_into('<I', duplicate, 0x64, linked_state ^ 0xffffffff)
        cpu.mem_write(0x804200, bytes(duplicate))
        cpu.mem_write(0x802000, struct.pack('<2I', 0x804000, 0x804200))
        cpu.mem_write(0x54671c, struct.pack('<3I', 0, 0x802000, 2 if present else 0))
        linked_buffers = {0x804000: c.create_string_buffer(bytes(linked), len(linked)), 0x804200: c.create_string_buffer(bytes(duplicate), len(duplicate))}
        handles = (c.c_uint32 * 2)(0x804000, 0x804200)
        scene_list = ObjectList(handles, 2 if present else 0, 2)
        start_y = rng.randrange(- 32768, 32768)
        elapsed = rng.choice([0, 1, 100, rng.getrandbits(32)])
        cpu.mem_write(0x533d78, struct.pack('<h', start_y))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        cpu.mem_write(BOARD, bytes(raw))
        portable_storage = c.create_string_buffer(bytes(raw), len(raw))
        listed_storage = c.create_string_buffer(bytes(raw), len(raw))
        frame_raw = bytearray(raw)
        struct.pack_into('<2I', frame_raw, 0x104, 0, 0)
        struct.pack_into('<I', frame_raw, 0x158, 0x517af4)
        cpu.mem_write(BOARD, bytes(frame_raw))
        cpu.mem_write(0x5bb710, struct.pack('<I', case % 2))
        framed = c.create_string_buffer(bytes(frame_raw), len(frame_raw))
        original.call(0x4ae150, eax=BOARD)
        assert native.vertrix_ui_actor_frame_update(framed, len(frame_raw), c.byref(scene_list), resolve, None, case % 2, start_y, elapsed, None, 0, c.byref(resources[0]), c.byref(resources[1]), 8)
        assert framed.raw == bytes(cpu.mem_read(BOARD, len(frame_raw))), (case, 'frame')
        cpu.mem_write(BOARD, bytes(raw))
        original.call(handler, eax=BOARD)
        assert native.vertrix_ui_actor_storage_update_list(listed_storage, len(raw), c.byref(scene_list), resolve, None, start_y, elapsed, c.byref(resources[0]), c.byref(resources[1]), 8)
        assert listed_storage.raw == bytes(cpu.mem_read(BOARD, len(raw))), (case, 'list')
        assert native.vertrix_ui_actor_storage_update(portable_storage, len(raw), present, linked_value, linked_state, start_y, elapsed, c.byref(resources[0]), c.byref(resources[1]), 8)
        assert portable_storage.raw == bytes(cpu.mem_read(BOARD, len(raw))), (case, hex(handler), 'storage')
        assert native.vertrix_linked_alternating_update(c.byref(state), present, linked_value, linked_state, start_y, elapsed, c.byref(resources[0]), c.byref(resources[1]), 8)
        bindings += encode() != initial_resource
        assert bytes(raw) == bytes(cpu.mem_read(BOARD, len(raw))), (case, hex(handler))
        assert bytes(linked) == bytes(cpu.mem_read(0x804000, len(linked))), case
        changes += state.handler != handler
    before = portable_storage.raw
    assert not native.vertrix_ui_actor_storage_update(portable_storage, 0x15b, 1, 1, 0, 0, 1, c.byref(resources[0]), c.byref(resources[1]), 8)
    assert portable_storage.raw == before
    invalid = bytearray(before)
    struct.pack_into('<I', invalid, 0xb0, 0x12345678)
    invalid_storage = c.create_string_buffer(bytes(invalid), len(invalid))
    assert not native.vertrix_ui_actor_storage_update(invalid_storage, len(invalid), 1, 1, 0, 0, 1, c.byref(resources[0]), c.byref(resources[1]), 8)
    assert invalid_storage.raw == bytes(invalid)
    listed_before = listed_storage.raw
    linked_buffers.pop(0x804000)
    scene_list.count = 2
    assert not native.vertrix_ui_actor_storage_update_list(listed_storage, len(listed_storage), c.byref(scene_list), resolve, None, start_y, elapsed, c.byref(resources[0]), c.byref(resources[1]), 8)
    assert listed_storage.raw == listed_before
    for offset, value in [(0x104, 1), (0x108, 1), (0x158, 0), (0x154, 0x12345678)]:
        unsupported = bytearray(frame_raw)
        struct.pack_into('<I', unsupported, offset, value)
        candidate = c.create_string_buffer(bytes(unsupported), len(unsupported))
        assert not native.vertrix_ui_actor_frame_update(candidate, len(candidate), c.byref(scene_list), resolve, None, 1, start_y, elapsed, None, 0, c.byref(resources[0]), c.byref(resources[1]), 8)
        assert candidate.raw == bytes(unsupported)
    idle = bytearray(frame_raw)
    struct.pack_into('<I', idle, 0x154, 0)
    cpu.mem_write(BOARD, bytes(idle))
    cpu.mem_write(0x5bb710, struct.pack('<I', 1))
    original.call(0x4ae150, eax=BOARD)
    candidate = c.create_string_buffer(bytes(idle), len(idle))
    assert native.vertrix_ui_actor_frame_update(candidate, len(candidate), c.byref(scene_list), resolve, None, 1, start_y, elapsed, None, 0, c.byref(resources[0]), c.byref(resources[1]), 8)
    assert candidate.raw == bytes(cpu.mem_read(BOARD, len(idle)))
    report = {'status': 'passed', 'cases': 12288, 'handler_changes': changes, 'resource_switches': bindings, 'scope': 'All six complete original handlers without hooks. Whole display state and ' 'unchanged linked storage match timers, movement, effects, phase arithmetic ' 'and resource/frame/descriptor switches. Fixtures use direct resources; ' 'linked resource helpers have separate proof. Portable actor-storage dispatch ' 'also matches every complete original object, preserving unrelated bytes and ' 'mapping resource identity tokens to native resources. Scene-list adapter ' 'also matches complete original lookup/updates with duplicate IDs and ' 'different linked values, selecting the first field0 match. Complete virtual ' 'frame wrapper4ae150/4ade20 also matches all12288 no-interaction/no-chain ' 'cases with conditional refresh clearing. Actual VF/application integration remains unfinished.'}
    (a.build_dir / 'linked-alternating-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
