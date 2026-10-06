"""Compare complete original scene-list virtual updates for recovered interface actors."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original, MASK
from verify_linked_alternating import ObjectList, Resolve
from verify_frame_resource import Resource
from verify_random import NativeRandom
from verify_ui_scene_render import Options


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'ui-scene-frame.dylib'
    names = ['ui_scene_frame.c', 'ui_indicator_update.c', 'linked_indicator.c', 'byte_transition.c', 'ui_border_update.c', 'linked_burst.c', 'random.c', 'ui_actor_frame.c', 'ui_actor_update.c', 'ui_companion_update.c',
             'actor_storage.c', 'actor_lookup.c', 'object_list.c', 'linked_movement.c',
             'linked_alternating.c', 'block_resource.c', 'frame_resource.c', 'animation.c',
             'timer.c', 'word_transition.c', 'dword_transition.c']
    names.append('ui_player_preview_update.c')
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
        *[str(source / name) for name in names], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_ui_scene_frame_update.argtypes = [c.POINTER(ObjectList), Resolve, c.c_void_p,
        c.c_int, c.c_int16, c.c_uint32, c.POINTER(c.c_uint32), c.c_size_t,
        c.POINTER(Resource), c.POINTER(Resource), c.c_size_t]
    native.vertrix_ui_scene_frame_update_random.argtypes = [
        *native.vertrix_ui_scene_frame_update.argtypes, c.POINTER(NativeRandom)]
    native.vertrix_ui_player_preview_update.argtypes = [c.c_void_p,c.c_size_t,
        c.POINTER(ObjectList),Resolve,c.c_void_p,c.POINTER(Options),c.POINTER(NativeRandom)]
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(0x900000, 0x10000)
    buffers = {}
    @Resolve
    def resolve(handle, storage, size, context):
        if handle not in buffers:
            return 0
        storage[0], size[0] = c.addressof(buffers[handle]), len(buffers[handle])
        return 1
    descriptors = [(c.c_uint32 * 1)(i) for i in range(2)]
    resources = [Resource(0, 1, values, None, None) for values in descriptors]
    for i, address in enumerate([0x546618, 0x546634]):
        table = 0x805000 + i * 16
        cpu.mem_write(table, struct.pack('<I', i))
        cpu.mem_write(address, struct.pack('<6I', table, 1, 0, 0, 0, 0))
    rng = random.Random(0x4b6200)
    random_state = NativeRandom()
    samples = [rng.randrange(65536) for _ in range(4097)]
    random_state.samples[:] = samples
    cpu.mem_write(0x908000, struct.pack('<4097H', *samples))
    handlers = [0, 0x450860, 0x4508c0, 0x450920, 0x450960, 0x4509a0, 0x4509d0,
                0x450a10, 0x450aa0, 0x450b30, 0x450b90, 0x450bf0, 0x450c70,
                0x44ff90, 0x44fff0, 0x450040, 0x4500b0, 0x450100,
                0x450130, 0x4501a0, 0x450200, 0x450270, 0x450300]
    actor_updates = 0
    random_draws = 0
    handlers_seen = set()
    nested_updates = 0
    for case in range(512):
        count = rng.randrange(25)
        handles = (c.c_uint32 * max(1, count))(*[0x900000 + i * 0x200 for i in range(count)])
        buffers = {}
        for i in range(count):
            raw = bytearray(rng.randbytes(0x160))
            struct.pack_into('<2I', raw, 0, rng.randrange(4), rng.randrange(4))
            struct.pack_into('<2I', raw, 0x104, 0, 0)
            struct.pack_into('<I', raw, 0x158, 0x517af4)
            handler = rng.choice(handlers)
            handlers_seen.add(handler)
            struct.pack_into('<I', raw, 0x154, handler)
            struct.pack_into('<I', raw, 0x7c, rng.randrange(2))
            resource_index = rng.randrange(2)
            struct.pack_into('<3I', raw, 0xb0, [0x546618, 0x546634][resource_index], resource_index, 0)
            struct.pack_into('<h', raw, 0x148, rng.choice([-1, 0, 1, 7]))
            struct.pack_into('<I', raw, 0x58, rng.randrange(13))
            struct.pack_into('<I', raw, 0x64, rng.randrange(13))
            for offset in [0xbc, 0xdc]:
                struct.pack_into('<2I', raw, offset, rng.randrange(1000), rng.choice([0, 1, 10, 500]))
            cpu.mem_write(handles[i], bytes(raw))
            buffers[handles[i]] = c.create_string_buffer(bytes(raw), len(raw))
        cpu.mem_write(0x803000, bytes(handles))
        cpu.mem_write(MASK, struct.pack('<3I', 0, 0x803000, count))
        cpu.mem_write(0x54671c, struct.pack('<3I', 0, 0x803000, count))
        start_y, elapsed = rng.randrange(-32768, 32768), rng.randrange(1000)
        clear = case % 2
        cpu.mem_write(0x533d78, struct.pack('<h', start_y))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        cpu.mem_write(0x5bb710, struct.pack('<I', clear))
        refresh = (c.c_uint32 * 8)(*[rng.getrandbits(32) for _ in range(8)])
        cpu.mem_write(0x5bb714, bytes(refresh))
        position = rng.randrange(4000)
        random_state.position = position
        cpu.mem_write(0x598d38, struct.pack('<IH', 0x908000 + 2 * position, position))
        original.call(0x4b6200, eax=MASK)
        listed = ObjectList(handles, count, count)
        assert native.vertrix_ui_scene_frame_update_random(c.byref(listed), resolve, None,
            clear, start_y, elapsed, refresh, 8, c.byref(resources[0]), c.byref(resources[1]), 1,
            c.byref(random_state))
        cursor, original_position = struct.unpack('<IH', cpu.mem_read(0x598d38, 6))
        assert original_position == random_state.position, case
        assert cursor == 0x908000 + 2 * random_state.position, case
        random_draws += random_state.position - position
        for i in range(count):
            assert buffers[handles[i]].raw == bytes(cpu.mem_read(handles[i], 0x160)), (case, i)
        assert bytes(refresh) == bytes(cpu.mem_read(0x5bb714, 32)), case
        assert bytes(handles) == bytes(cpu.mem_read(0x803000, len(bytes(handles)))), case
        actor_updates += count
        parent_raw = bytearray(rng.randbytes(0x180))
        struct.pack_into('<I',parent_raw,0x158,0x514814)
        struct.pack_into('<I',parent_raw,0x154,0)
        struct.pack_into('<2I',parent_raw,0x104,0,0)
        nested_handles = [rng.choice([0,*list(handles)[:count]]) for _ in range(6)]
        struct.pack_into('<6I',parent_raw,0x15c,*nested_handles)
        parent = c.create_string_buffer(bytes(parent_raw),len(parent_raw))
        cpu.mem_write(0x800000,bytes(parent_raw))
        options = Options(clear,start_y,elapsed,refresh,8,
                          c.pointer(resources[0]),c.pointer(resources[1]),1)
        original.call(0x42b310,eax=0x800000)
        assert native.vertrix_ui_player_preview_update(parent,len(parent_raw),c.byref(listed),
            resolve,None,c.byref(options),c.byref(random_state))
        assert parent.raw == bytes(cpu.mem_read(0x800000,len(parent_raw))),case
        for i in range(count):
            assert buffers[handles[i]].raw == bytes(cpu.mem_read(handles[i],0x160)),(case,i)
        assert bytes(refresh) == bytes(cpu.mem_read(0x5bb714,32)),case
        cursor, original_position = struct.unpack('<IH',cpu.mem_read(0x598d38,6))
        assert original_position == random_state.position,case
        assert cursor == 0x908000 + 2*random_state.position,case
        nested_updates += sum(bool(handle) for handle in nested_handles)
    assert handlers_seen == set(handlers)
    assert random_draws > 0
    report = {'status':
            'passed', 'scenes' : 512, 'actor_updates' : actor_updates,
                                                        'handlers_exercised' : len(handlers_seen),
                                                                               'shared_random_draws'
                : random_draws,
                  'original_parent_preview_updates' : 512,
                  'nested_actor_updates' : nested_updates,
                                           'scope'
                : 'Complete original4b6200 virtual scene-list updates without hooks, invoking ' 'actual4ae150/4ade20, lookup and all twenty-two recovered handlers plus idle actors. ' 'Whole actor storage, shared refresh and list order match mixed scenes with ' 'duplicate identities. Shared random cursor matches update order. ' 'Complete42b310 parent preview update also matches parent/child bytes, ' 'refresh and RNG with missing and repeated handles. ' 'Direct resource fixtures; no interaction targets/child ' 'chains. Other actor classes, full scene construction, rendering and application ' 'execution remain unfinished.'
            }
            (args.build_dir / 'ui-scene-frame-verification.json')
                    .write_text(json.dumps(report, indent = 2) + '\n')
                        print(json.dumps(report, indent = 2))

                            if __name__ == '__main__' : main()
