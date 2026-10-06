"""Compare original packed-row skipping, including empty patterns."""
import argparse, ctypes, json, random, struct, subprocess
from pathlib import Path
from original import Original, BLOCKS


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'seek-row.dylib'
    subprocess.run(['cc', '-std=c11', '-Wall', '-Wextra', '-Werror', '-shared', '-fPIC', * [str(source / n) for n in ('xm.c', 'vf.c', 'audio.c')], '-o', str(library)], check=True)
    native = ctypes.CDLL(str(library))
    function = native.vertrix_xm_seek_row
    function.argtypes = [ctypes.c_void_p, ctypes.c_size_t, ctypes.c_int32, ctypes.c_int32, ctypes.POINTER(ctypes.c_size_t)]
    original = Original(args.executable)
    rng = random.Random(0x40ea45)
    cases = 16000
    skipped = 0
    for index in range(cases):
        data = bytearray()
        for cell in range(96):
            fields = rng.randbytes(5)
            if rng.randrange(2):
                header = rng.randrange(128, 256)
                data.append(header)
                data.extend(fields[i] for i in range(5) if header & (1 << i))
            else:
                data.extend(bytes([fields[0] & 127]) + fields[1:])
        empty = index % 7 == 0
        row = rng.randrange(- 3, 13)
        channels = rng.randrange(- 2, 9)
        if empty:
            storage = None
            size = 0
        else:
            storage = (ctypes.c_uint8 * len(data)).from_buffer_copy(data)
            size = len(data)
            original.cpu.mem_write(BLOCKS, bytes(data))
            original.cpu.mem_write(0x531b50, struct.pack('<i', row))
            original.cpu.mem_write(0x531b48, struct.pack('<i', channels))
            original.cpu.mem_write(0x530440, struct.pack('<I', 0 if empty else BLOCKS))
            original.call(0x40ea45, stop=0x40ea79)
        pointer = struct.unpack('<I', original.cpu.mem_read(0x530440, 4))[0]
        cursor = ctypes.c_size_t(rng.getrandbits(32))
        assert function(storage, size, row, channels, ctypes.byref(cursor))
        assert cursor.value == (0 if empty else pointer - BLOCKS), (index, row, channels)
        if row > 0 and channels > 0:
            skipped += row * channels
            cursor = ctypes.c_size_t(123)
            truncated = (ctypes.c_uint8 * 2)(0x9f, 1)
            assert not function(truncated, 2, 1, 1, ctypes.byref(cursor)) and cursor.value == 123
            assert not function(truncated, 2, 2147483647, 2147483647, ctypes.byref(cursor)) and cursor.value == 123
            assert not function(None, 1, 0, 0, ctypes.byref(cursor)) and cursor.value == 123
            assert function(None, 0, 2147483647, 2147483647, ctypes.byref(cursor)) and cursor.value == 0
            assert not function(None, 0, 0, 0, None)
    report = {'status': 'passed', 'row_seek_cases': cases, 'skipped_events': skipped, 'scope': 'Original 0x40ea45..0x40ea79 nested packed event skip loop, mixed packed/unpacked/zero-field cells, signed zero/negative rows and channels, empty patterns. Cursor matches original. Native truncation and oversized request preserve output. Excludes channel initialization and complete sequencer integration.'}
    (build / 'xm-seek-row-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
