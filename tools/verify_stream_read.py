"""Compare complete original memory stream read/skip routines with the native recovery."""
import argparse, ctypes as c, json, random, struct
from pathlib import Path
from original import Original
from oracle_kit import build

STREAM, SIZE, DATA, DEST = 0x801000, 0x20, 0x804000, 0x80c000
U = c.c_uint32
Fetch = c.CFUNCTYPE(None, c.c_void_p, U, c.POINTER(c.c_uint8), U)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'stream-read', ['stream_read.c', 'actor_storage.c'])
    for name in ('read_exact', 'read'):
        getattr(n, 'vertrix_stream_' + name).argtypes = [c.c_void_p, c.c_size_t, U, U, c.c_void_p, Fetch,
                                                         c.c_void_p, c.POINTER(U)]
    n.vertrix_stream_skip.argtypes = [c.c_void_p, c.c_size_t, c.c_int32, c.POINTER(U)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x48a930)
    data = rng.randbytes(0x4000)
    cpu.mem_write(DATA, data)

    @Fetch
    def fetch(context, address, destination, count):
        assert DATA <= address and address + count <= DATA + 0x4000, (hex(address), count)
        c.memmove(destination, data[address - DATA:address - DATA + count], count)

    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    for case in range(args.cases):
        position = DATA + rng.randrange(0x2000)
        end = position + rng.choice([0, 1, 7, 100, rng.randrange(0x2000), rng.randrange(40)])
        raw = bytearray(rng.randbytes(SIZE))
        struct.pack_into('<II', raw, 4, position, end)
        for address, name in ((0x48a930, 'read_exact'), (0x48a9d0, 'read')):
            item, num = rng.choice([1, 2, 4, 8, rng.randrange(20)]), rng.choice([0, 1, 3, rng.randrange(50)])
            cpu.mem_write(STREAM, bytes(raw))
            cpu.mem_write(DEST, bytes(range(256)) * 2)
            result = original.call(address, eax=STREAM, edx=DEST, ebx=item, ecx=num)
            native = c.create_string_buffer(bytes(raw), SIZE)
            dest = c.create_string_buffer(bytes(range(256)) * 2, 512)
            out = U()
            assert getattr(n, 'vertrix_stream_' + name)(native, SIZE, item, num, dest, fetch, None, c.byref(out))
            assert native.raw == bytes(cpu.mem_read(STREAM, SIZE)), (name, case)
            assert dest.raw == bytes(cpu.mem_read(DEST, 512)), (name, case)
            assert out.value == result & (0xff if name == 'read_exact' else 0xffffffff), (name, case)
            count(name)
        for delta in (rng.choice([0, 1, -1, 5, -5, 100, -100, rng.randrange(-0x800, 0x800)]),):
            cpu.mem_write(STREAM, bytes(raw))
            cpu.mem_write(0x5bb24c, bytes(4))
            original.call(0x48aa90, eax=STREAM, edx=delta & 0xffffffff)
            native = c.create_string_buffer(bytes(raw), SIZE)
            out = U()
            assert n.vertrix_stream_skip(native, SIZE, delta, c.byref(out))
            assert native.raw == bytes(cpu.mem_read(STREAM, SIZE)), ('skip', case)
            assert out.value == struct.unpack('<I', bytes(cpu.mem_read(0x5bb24c, 4)))[0], ('skip', case)
            count('skip')
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 48a930, 48a9d0 and 48aa90 execute in the original over random stream '
                       'positions/ends and requests; stream object, destination bytes, results and the '
                       'applied-delta global compare. Other scratch globals (0x5bb22c..0x5bb248) are dead '
                       'temporaries.'}
    (args.build_dir / 'stream-read-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
