"""Compare four complete original active-piece child callbacks."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from verify_frame_resource import Resource
from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI


class Bounds(c.Structure):
    _fields_ = [(name, c.c_int16) for name in ['x_min', 'x_max', 'y_min', 'y_max']]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'piece-child-update.dylib'
    names = ['piece_child_update.c', 'actor_storage.c', 'timer.c', 'dword_transition.c', 'frame_resource.c']
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', * [str(source / name) for name in names], '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_piece_child_update.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32, c.c_uint32, c.POINTER(Resource), c.c_size_t]
    native.vertrix_piece_child_frame_update.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32, c.c_int, c.c_uint32, c.POINTER(Resource), c.c_size_t]
    native.vertrix_piece_child_construct.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32, c.POINTER(Bounds), c.c_int]
    descriptors = (c.c_uint32 * 4)(* [0x806000 + i * 40 for i in range(4)])
    resource = Resource(0, 4, descriptors, None, None)
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_write(0x804000, bytes(descriptors))
    cpu.mem_write(0x544bd8, struct.pack('<6I', 0x804000, 4, 0, 0, 0, 0))
    rng = random.Random(0x44c2b0)
    for case in range(2048):
        raw = rng.randbytes(0x180)
        storage = c.create_string_buffer(raw, len(raw))
        bounds = Bounds(* [rng.randrange(- 32768, 32768) for _ in range(4)])
        frame, last = rng.getrandbits(32), case % 2
        cpu.mem_write(0x800000, raw)
        original.call(0x4abd70, eax=0x800000, edx=0)
        ebp = 0x707000
        for offset, value in [(- 0x18, bounds.x_min), (- 0x24, bounds.x_max), (- 0x1c, bounds.y_min), (- 0x28, bounds.y_max), (- 0x14, frame), (- 0xc, 1 if last else 0), (- 0x2c, 1)]:
            cpu.mem_write(ebp + offset, struct.pack('<I', value & 0xffffffff))
        cpu.reg_write(UC_X86_REG_EBP, ebp)
        cpu.reg_write(UC_X86_REG_ESI, 0x800000)
        cpu.reg_write(UC_X86_REG_EDI, 0x802000)
        original.call(0x42ae11, stop=0x42aea5)
        assert native.vertrix_piece_child_construct(storage, len(raw), frame, c.byref(bounds), last)
        assert storage.raw == bytes(cpu.mem_read(0x800000, len(raw))), case
        before = storage.raw
        assert not native.vertrix_piece_child_construct(storage, 0x15b, frame, c.byref(bounds), last)
        assert not native.vertrix_piece_child_construct(storage, len(raw), frame, None, last)
        assert storage.raw == before
    changes = 0
    for case in range(16384):
        raw = bytearray(rng.randbytes(0x180))
        handler = [0x44c2a0, 0x44c2b0, 0x44c310, 0x44c370][case % 4]
        token = 0 if case % 3 == 0 else 0x544bd8
        struct.pack_into('<I', raw, 0x154, handler)
        struct.pack_into('<I', raw, 0xb0, token)
        struct.pack_into('<I', raw, 0xb8, rng.randrange(4))
        struct.pack_into('<2I', raw, 0xbc, rng.getrandbits(32), rng.choice([0, 1, 24, 0xffffffff]))
        struct.pack_into('<I', raw, 0x58, rng.choice([0, 60, rng.getrandbits(32)]))
        storage = c.create_string_buffer(bytes(raw), len(raw))
        cpu.mem_write(0x800000, bytes(raw))
        elapsed = rng.choice([0, 1, 100, rng.getrandbits(32)])
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        original.call(handler, eax=0x800000)
        assert native.vertrix_piece_child_update(storage, len(raw), elapsed, 0x544bd8, c.byref(resource), 1)
        assert storage.raw == bytes(cpu.mem_read(0x800000, len(raw))), case
        changes += struct.unpack_from('<I', storage.raw, 0x154)[0] != handler
        before = storage.raw
        assert not native.vertrix_piece_child_update(storage, 0x15b, elapsed, 0x544bd8, c.byref(resource), 1)
        assert storage.raw == before
        if token:
            assert not native.vertrix_piece_child_update(storage, len(raw), elapsed, 0x544bd8, c.byref(resource), 0)
            assert storage.raw == before
            struct.pack_into('<I', raw, 0x158, 0x517af4)
            struct.pack_into('<2I', raw, 0x104, 0, 0)
            framed = c.create_string_buffer(bytes(raw), len(raw))
            cpu.mem_write(0x800000, bytes(raw))
            cpu.mem_write(0x5bb710, struct.pack('<I', case % 2))
            original.call(0x4ae150, eax=0x800000)
            assert native.vertrix_piece_child_frame_update(framed, len(raw), elapsed, case % 2, 0x544bd8, c.byref(resource), 1)
            assert framed.raw == bytes(cpu.mem_read(0x800000, len(raw))), case
            c.memmove(c.addressof(framed) + 0x158, struct.pack('<I', 0x514814), 4)
            before = framed.raw
            assert not native.vertrix_piece_child_frame_update(framed, len(raw), elapsed, 1, 0x544bd8, c.byref(resource), 1)
            assert framed.raw == before
    report = {'status': 'passed', 'complete_original_callback_cases': 16384, 'handler_changes': changes, 'short_storage_preservation_cases': 16384, 'complete_original_child_virtual_update_cases': 16384, 'unsupported_class_preservation_cases': 16384, 'original_piece_child_setup_cases': 2048, 'child_setup_failure_preservation_cases': 4096, 'scope': 'Complete44c2a0/44c2b0/44c310/44c370 without hooks, including actual ' 'timers, signed DWORD transitions and4877f0 binding. Entire extended actor ' 'storage matches direct resource/null-resource fixtures. Complete4ae150 ' 'virtual updates also match conditional refresh and callbacks. Resource ' 'publication, full player scheduling and Wii game remain separate.'}
    (build / 'piece-child-update-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
