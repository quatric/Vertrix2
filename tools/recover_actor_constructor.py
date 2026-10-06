"""Recover and execute original4abd70 actor constructor's exact storage writes."""
import argparse
import json
import random
import ctypes as c
import subprocess
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from capstone.x86 import X86_OP_MEM, X86_OP_IMM, X86_REG_EAX
from original import Original, BOARD, EXECUTABLE_SHA256


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--output', type=Path, required=True)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'actor-storage.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
        str(source / 'actor_storage.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_actor_storage_construct.argtypes = [c.c_void_p, c.c_size_t]
    native.vertrix_actor_storage_read.argtypes = [c.c_void_p, c.c_size_t, c.c_size_t,
                                                c.c_uint, c.POINTER(c.c_uint32)]
    native.vertrix_actor_storage_write.argtypes = [c.c_void_p, c.c_size_t, c.c_size_t,
                                                 c.c_uint, c.c_uint32]
    original = Original(args.executable)
    image = original.pe.get_memory_mapped_image()
    disassembler = Cs(CS_ARCH_X86, CS_MODE_32)
    disassembler.detail = True
    start, end = 0x4abd70, 0x4ac122
    instructions = list(disassembler.disasm(image[start - 0x400000:end - 0x400000], start))
    assert sum(i.size for i in instructions) == end - start
    assert instructions[-1].mnemonic == 'ret'
    writes = []
    coverage = set()
    for instruction in instructions[:-1]:
        assert instruction.mnemonic == 'mov'
        destination, source = instruction.operands
        assert destination.type == X86_OP_MEM and source.type == X86_OP_IMM
        assert destination.mem.base == X86_REG_EAX and not destination.mem.index
        offset, size = destination.mem.disp, destination.size
        assert 0 <= offset and offset + size <= 0x15c
        value = source.imm & ((1 << (size * 8)) - 1)
        writes.append({'instruction': hex(instruction.address), 'offset': offset,
                       'size': size, 'value': value})
        coverage.update(range(offset, offset + size))
    rng = random.Random(start)
    for case in range(512):
        raw = rng.randbytes(0x160)
        expected = bytearray(raw)
        for write in writes:
            offset, size, value = write['offset'], write['size'], write['value']
            expected[offset:offset + size] = value.to_bytes(size, 'little')
        original.cpu.mem_write(BOARD, raw)
        assert original.call(start) == BOARD
        assert bytes(original.cpu.mem_read(BOARD, len(raw))) == bytes(expected), case
        storage = c.create_string_buffer(raw, len(raw))
        assert native.vertrix_actor_storage_construct(storage, len(raw))
        assert storage.raw == bytes(expected), case
        for write in writes:
            value = c.c_uint32()
            assert native.vertrix_actor_storage_read(storage, len(raw), write['offset'],
                                                     write['size'], c.byref(value))
            assert value.value == write['value']
    storage = c.create_string_buffer(rng.randbytes(0x160), 0x160)
    prior = storage.raw
    assert not native.vertrix_actor_storage_construct(storage, 0x15b)
    assert storage.raw == prior
    assert not native.vertrix_actor_storage_construct(None, 0x160)
    for offset, width in [(0x15f, 4), (0, 3), (c.c_size_t(-1).value, 4)]:
        value = c.c_uint32(123)
        assert not native.vertrix_actor_storage_read(storage, 0x160, offset, width, c.byref(value))
        assert value.value == 123
        assert not native.vertrix_actor_storage_write(storage, 0x160, offset, width, 999)
        assert storage.raw == prior
    untouched = [offset for offset in range(0x15c) if offset not in coverage]
    report = {'status': 'passed', 'executable_sha256': EXECUTABLE_SHA256,
              'address': hex(start), 'end': hex(end), 'cases': 512,
              'allocation_size': 0x15c, 'writes': writes, 'untouched_offsets': untouched,
              'scope': 'Complete original4abd70 constructor executes without hooks. '
                       'Native portable constructor and field reads match whole storage, '
                       'including untouched bytes, and immediate-write plan. Invalid bounds '
                       'and short storage preserve outputs; byte order is explicit. '
                       'The original517af4 class metadata address is recorded as evidence, '
                       'not a dereferenceable Wii pointer. Allocation/list insertion, derived '
                       'classes and full actor runtime remain unfinished.'}
    args.output.write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps({'status': 'passed', 'cases': 512, 'writes': len(writes),
                      'untouched_bytes': len(untouched), 'output': str(args.output)}))


if __name__ == '__main__':
    main()
