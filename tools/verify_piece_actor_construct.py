"""Compare complete original active-piece construction with heap boundary supplied."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EIP, UC_X86_REG_ESP


class Placement(c.Structure):
    _fields_ = [(name, c.c_uint32) for name in ['left_x', 'left_y', 'right_x', 'right_y', 'width', 'height']] + [('row_height', c.c_uint16)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'piece-actor-construct.dylib'
    names = ['piece_actor_construct.c', 'piece_child_update.c', 'actor_storage.c', 'timer.c', 'timing.c', 'dword_transition.c', 'frame_resource.c']
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', * [str(source / name) for name in names], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    construct = native.vertrix_piece_actor_construct
    construct.argtypes = [c.c_void_p, c.c_size_t, c.c_void_p, c.c_size_t, c.POINTER(c.c_uint32), c.POINTER(c.c_uint32), c.c_uint8, c.c_int, c.c_int, c.c_uint16]
    placed = native.vertrix_piece_actor_construct_placed
    placed.argtypes = [* construct.argtypes[: - 1], c.POINTER(Placement)]
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(0x900000, 0x3000)
    addresses = [0x900000 + i * 0x200 for i in range(7)]
    allocated = []
    def allocate(cpu, address, size, context):
        assert cpu.reg_read(UC_X86_REG_EAX) == 0x15c
        result = addresses[len(allocated)]
        allocated.append(result)
        stack = cpu.reg_read(UC_X86_REG_ESP)
        destination = struct.unpack('<I', cpu.mem_read(stack, 4))[0]
        cpu.reg_write(UC_X86_REG_EAX, result)
        cpu.reg_write(UC_X86_REG_ESP, stack + 4)
        cpu.reg_write(UC_X86_REG_EIP, destination)
    hook = cpu.hook_add(UC_HOOK_CODE, allocate, begin=0x4ca000, end=0x4ca000)
    rng = random.Random(0x42acf0)
    children_checked = 0
    try:
        for case in range(512):
            allocated.clear()
            raw = rng.randbytes(0x1a0)
            child_raw = rng.randbytes(7 * 0x15c)
            parent = c.create_string_buffer(raw, len(raw))
            children = c.create_string_buffer(child_raw, len(child_raw))
            count = case % 8
            values = [rng.getrandbits(32) for _ in range(count)] + [0xffffffff] * (7 - count)
            rng.shuffle(values)
            frames, handles = (c.c_uint32 * 7)(* values), (c.c_uint32 * 7)(* addresses)
            cpu.mem_write(0x800000, raw)
            cpu.mem_write(0x803000, bytes(frames))
            for i, address in enumerate(addresses):
                cpu.mem_write(address, child_raw[i * 0x15c: (i + 1) * 0x15c])
            side, difficulty, level = case % 256, case % 3, (case // 3) % 10
            spacing = rng.choice([14, 0, 65535, rng.randrange(65536)])
            cpu.mem_write(0x532bbc, struct.pack('<I', difficulty))
            cpu.mem_write(0x4f90ac, struct.pack('<H', spacing))
            geometry_values = [138, 248, 488, 248, 14, 202] if case % 2 == 0 else [rng.choice([0, 1, 65535, 0xffffffff, rng.getrandbits(32)]) for _ in range(6)]
            geometry = Placement(* geometry_values, spacing)
            cpu.mem_write(0x4f89e8, struct.pack('<6I', * geometry_values))
            original.call(0x42acf0, eax=0x800000, edx=side, ecx=level, ebx=0x803000)
            assert allocated == addresses[: count]
            if case % 2 == 0:
                assert construct(parent, len(raw), children, len(child_raw), frames, handles, side, difficulty, level, spacing)
            else:
                assert placed(parent, len(raw), children, len(child_raw), frames, handles, side, difficulty, level, c.byref(geometry))
            assert parent.raw == bytes(cpu.mem_read(0x800000, len(raw))), case
            for i, address in enumerate(addresses):
                assert children.raw[i * 0x15c: (i + 1) * 0x15c] == bytes(cpu.mem_read(address, 0x15c)), (case, i)
            children_checked += count
            before = parent.raw, children.raw
            assert not construct(parent, 0x18b, children, len(child_raw), frames, handles, side, difficulty, level, spacing)
            assert not construct(parent, len(raw), children, len(child_raw), frames, handles, side, 3, level, spacing)
            assert not placed(parent, len(raw), children, len(child_raw), frames, handles, side, difficulty, level, None)
            assert (parent.raw, children.raw) == before
    finally:
        cpu.hook_del(hook)
    report = {'status': 'passed', 'complete_original_piece_construction_cases': 512, 'constructed_children': children_checked, 'failure_preservation_cases': 1536, 'runtime_placement_cases': 256, 'default_placement_cases': 256, 'scope': 'Complete42acf0 with only heap allocation supplied. Parent/child bytes ' 'match original count scan, default/runtime placement globals, all difficulty/level ' 'timing, clipping, child construction and parent handles. Zero counts and ' 'sentinel gaps covered. Resource publication ' 'and full player/game-loop/Wii execution remain separate.'}
    (build / 'piece-actor-construct-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
