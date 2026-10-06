"""Compare original4123d0 complete actor styling with portable storage."""
import argparse
import ctypes as c
import json
from pathlib import Path
import random
import subprocess
from original import Original, BOARD


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    args = parser.parse_args()
    args.build_dir.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = args.build_dir.resolve() / 'actor-style.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-Wall', '-Wextra', '-Werror',
        str(source / 'actor_style_storage.c'), str(source / 'actor_storage.c'),
        '-o', str(library)], check=True)
    native = c.CDLL(str(library))
    native.vertrix_actor_storage_style.argtypes = [c.c_void_p, c.c_size_t, c.c_void_p]
    original = Original(args.executable)
    rng = random.Random(0x4123d0)
    for case in range(2048):
        records = rng.randbytes(128 * 12)
        index = rng.randrange(128)
        raw = rng.randbytes(0x160)
        original.cpu.mem_write(0x804000, records)
        original.cpu.mem_write(BOARD, raw)
        original.call(0x4123d0, eax=0x804000, edx=index, ebx=BOARD)
        storage = c.create_string_buffer(raw, len(raw))
        record = c.create_string_buffer(records[index * 12:index * 12 + 12], 12)
        assert native.vertrix_actor_storage_style(storage, len(raw), record)
        assert storage.raw == bytes(original.cpu.mem_read(BOARD, len(raw))), case
        prior = storage.raw
        assert not native.vertrix_actor_storage_style(storage, 0x15b, record)
        assert not native.vertrix_actor_storage_style(storage, len(storage), None)
        assert storage.raw == prior
    report = {
        'status': 'passed',
        'cases': 2048,
        'scope': 'Complete original4123d0 executes without hooks. Whole actor bytes '
                 'match native12-byte record styling with randomized table indices and '
                 'records, preserving unrelated fields. Short/null inputs preserve storage. '
                 'Configuration loading, companion constructor471100 and full application '
                 'integration remain unfinished.'
    }
    (args.build_dir / 'actor-style-storage-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
