"""Compare the complete 0x48c370 copy and return against the original executable."""
import ctypes as c
import json
from pathlib import Path
import random
import struct
import subprocess
import tempfile

from original import Original


def main():
    root = Path(__file__).resolve().parents[1]
    with tempfile.TemporaryDirectory(prefix='vertrix-copy-dword-') as directory:
        library = Path(directory) / 'copy.so'
        subprocess.run(['cc', '-std=c11', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra',
                        '-Werror', str(root / 'source/call_glue.c'),
                        str(root / 'source/actor_storage.c'), '-o', str(library)], check=True)
        native = c.CDLL(str(library))
        native.vertrix_copy_dword_full.argtypes = [c.POINTER(c.c_uint32)] * 2
        native.vertrix_copy_dword_full.restype = c.c_uint32
        original = Original(root / 'Vertrix2.exe')
        rng = random.Random(0x48c370)
        for case in range(4096):
            value = [0, 1, 0x7fffffff, 0x80000000, 0xffffffff][case] if case < 5 else rng.getrandbits(32)
            before = rng.randbytes(12)
            original.cpu.mem_write(0x5bb518, struct.pack('<I', value))
            original.cpu.mem_write(0x5bd830, before)
            wanted = original.call(0x48c370, eax=rng.getrandbits(32), edx=rng.getrandbits(32),
                                   ebx=rng.getrandbits(32), ecx=rng.getrandbits(32))
            storage = (c.c_uint32 * 3).from_buffer_copy(before)
            source = c.c_uint32(value)
            destination = c.cast(c.byref(storage, 4), c.POINTER(c.c_uint32))
            assert native.vertrix_copy_dword_full(destination, c.byref(source)) == wanted == value
            assert bytes(storage) == bytes(original.cpu.mem_read(0x5bd830, 12))
            assert source.value == struct.unpack('<I', original.cpu.mem_read(0x5bb518, 4))[0] == value
        value = c.c_uint32(0xabcdef01)
        assert native.vertrix_copy_dword_full(c.byref(value), c.byref(value)) == value.value
        assert native.vertrix_copy_dword_full(None, c.byref(value)) == 0
        assert native.vertrix_copy_dword_full(c.byref(value), None) == 0
        assert value.value == 0xabcdef01
    report = {'status': 'passed', 'original_address': '0x48c370',
              'complete_original_executions': 4096,
              'scope': 'Exact EAX, destination and its adjacent dwords, and unchanged source; randomized incoming EAX/EDX/EBX/ECX. Native alias and null checks are additional API checks.',
              'native_additional_cases': 3}
    (root / 'docs/copy-dword-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report))


if __name__ == '__main__':
    main()
