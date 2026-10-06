"""Compare original companion setup before image binding."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
from original import Original
from unicorn.x86_const import UC_X86_REG_EBP, UC_X86_REG_ESI, UC_X86_REG_EDI


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    library = build / 'ui-companion-actor.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror', str(root / 'source/ui_companion_actor.c'), str(root / 'source/actor_storage.c'), str(root / 'source/actor_style_storage.c'), str(root / 'source/call_glue.c'), str(root / 'source/ui_actor_storage.c'), str(root / 'source/block_factory.c'), str(root / 'source/ui_display_layout.c'), str(root / 'source/actor_fields.c'), str(root / 'source/board_cells.c'), '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    construct = native.vertrix_ui_companion_actor_construct
    construct.argtypes = [c.c_void_p, c.c_size_t, c.c_int16, c.c_int16, c.c_uint32, c.c_uint32, c.c_size_t]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x42b3f3)
    for case in range(2048):
        raw = rng.randbytes(0x180)
        storage = c.create_string_buffer(raw, len(raw))
        x, y = rng.randrange(- 32768, 32768), rng.randrange(- 32768, 32768)
        linked, source = rng.randrange(2 ** 32), rng.randrange(2 ** 32)
        index = case % 3
        cpu.mem_write(0x800000, raw)
        original.call(0x4abd70, eax=0x800000, edx=0)
        ebp = 0x707000
        cpu.mem_write(ebp - 0x1c, struct.pack('<I', 0x805000))
        cpu.mem_write(ebp - 0x18, struct.pack('<h', y))
        cpu.mem_write(ebp - 0x26, struct.pack('<I', (x & 65535) << 16))
        cpu.mem_write(0x805000, struct.pack('<I', linked))
        cpu.mem_write(0x4fbf74, struct.pack('<I', source))
        cpu.reg_write(UC_X86_REG_EBP, ebp)
        cpu.reg_write(UC_X86_REG_ESI, 0x802000)
        cpu.reg_write(UC_X86_REG_EDI, index)
        original.call(0x42b3f3, eax=0x800000, stop=0x42b499)
        assert construct(storage, len(raw), x, y, linked, source, index)
        assert storage.raw == bytes(cpu.mem_read(0x800000, len(raw))), case
        before = storage.raw
        for size, slot in [(0x15b, index), (len(raw), 3)]:
            assert not construct(storage, size, x, y, linked, source, slot)
            assert storage.raw == before
            assert not construct(None, 0x15c, 0, 0, 0, 0, 0)
    report = {'status': 'passed', 'original_companion_setup_cases': 2048, 'failure_preservation_cases': 4096, 'scope': 'Original base constructor and42b3f3..42b499 execute without hooks. ' 'Entire extended actor storage compares. Allocation, parent attachment, ' 'subsequent image/callback binding and full gameplay remain separate.'}
    (build / 'ui-companion-actor-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
