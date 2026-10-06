"""Compare complete original small engine helpers with the native recovery."""
import argparse, ctypes as c, json, random, struct
from pathlib import Path
from original import Original, BOARD
from oracle_kit import build
from verify_random import NativeRandom
OBJECT, DATA, CURSOR = 0x801000, 0x804000, 0x5bb73c
U = c.c_uint32


class Cursor(c.Structure):
    _fields_ = [('index', c.c_int32), ('x', c.c_int16), ('y', c.c_int16), ('width', c.c_int16), ('height', c.c_int16)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'engine-helpers', ['engine_helpers.c', 'actor_storage.c', 'random.c'])
    n.vertrix_random_object_construct.argtypes = [c.c_void_p, c.c_size_t]
    n.vertrix_table_object_construct.argtypes = [c.c_void_p, c.c_size_t, U]
    n.vertrix_random_inclusive.argtypes = [c.POINTER(NativeRandom), c.c_uint16, c.c_uint16, c.POINTER(U)]
    n.vertrix_rle_encoded_length.argtypes = [c.c_void_p, U]
    n.vertrix_rle_encoded_length.restype = U
    n.vertrix_cursor_clamp.argtypes = [c.POINTER(Cursor)]
    n.vertrix_random_seed.argtypes = [c.POINTER(NativeRandom), U]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x482480)
    totals, faults = {}, 0
    def count(name):
        totals[name] = totals.get(name, 0) + 1
    for case in range(args.cases):
        raw = rng.randbytes(0x40)
        cpu.mem_write(OBJECT, raw)
        original.call(0x482480, eax=OBJECT)
        native = c.create_string_buffer(raw, 0x40)
        assert n.vertrix_random_object_construct(native, 0x40)
        assert native.raw == bytes(cpu.mem_read(OBJECT, 0x40)), case
        assert not n.vertrix_random_object_construct(native, 0x13)
        count('random_object_construct')
        default = rng.getrandbits(32)
        cpu.mem_write(0x4f81cc, struct.pack('<I', default))
        cpu.mem_write(OBJECT, raw)
        original.call(0x487870, eax=OBJECT)
        native = c.create_string_buffer(raw, 0x40)
        assert n.vertrix_table_object_construct(native, 0x40, default)
        assert native.raw == bytes(cpu.mem_read(OBJECT, 0x40)), case
        count('table_object_construct')
#run - length size
        length = rng.choice([0, 1, 2, 3, 10, 70, 150, rng.randrange(300)])
        data = bytearray()
        while len(data) < length:
            value = rng.choice([0, 1, 0xbf, 0xc0, 0xff, rng.getrandbits(8)])
            data += bytes([value]) * rng.choice([1, 1, 2, 3, 62, 63, 64, 65, rng.randrange(1, 130)])
        data = bytes(data[: length]) + rng.randbytes(2)
        cpu.mem_write(DATA, data)
        result = original.call(0x481420, eax=DATA, edx=length)
        assert n.vertrix_rle_encoded_length(data, length) == result, (case, length)
        count('rle_encoded_length')
#cursor clamp
        words = [rng.choice([0, 1, - 1, 5, 100, - 300, 32767, - 32768, rng.randrange(- 20, 20), rng.randrange(- 32768, 32768)]) for _ in range(4)]
        state = struct.pack('<ihhhh', rng.randrange(- 1000, 1000), * words)
        cpu.mem_write(CURSOR, state)
        original.call(0x4ae170)
        cursor = Cursor.from_buffer_copy(state)
        assert n.vertrix_cursor_clamp(c.byref(cursor)) == 1
        assert bytes(cursor) == bytes(cpu.mem_read(CURSOR, 12)), (case, words)
        count('cursor_clamp')
#random inclusive range : seeded buffer, repeated draws over the wrap
    for seed in (1, 0x1234, 0xdeadbeef):
        native = NativeRandom()
        n.vertrix_random_seed(c.byref(native), seed)
        original.random_seed(seed)
        for draw in range(6000):
            minimum = rng.choice([0, 1, 5, 0xffff, rng.getrandbits(16)])
            maximum = rng.choice([minimum, (minimum + rng.randrange(0, 40)) & 0xffff, rng.getrandbits(16)])
            if rng.random() < 0.004:
                maximum = (minimum - 1) & 0xffff
            width = (maximum - minimum + 1) & 0xffff
            value = U(0xdeadbeef)
            ok = n.vertrix_random_inclusive(c.byref(native), minimum, maximum, c.byref(value))
            if width == 0:
                assert not ok and value.value == 0xdeadbeef
                try:
                    original.call(0x482750, eax=BOARD, edx=minimum, ebx=maximum)
                except Exception:
                    faults += 1
                else:
                    raise AssertionError('zero width did not fault in the original')
                original.random_seed(seed)
                native = NativeRandom()
                n.vertrix_random_seed(c.byref(native), seed)
                continue
            result = original.call(0x482750, eax=BOARD, edx=minimum, ebx=maximum)
            position = struct.unpack('<H', bytes(cpu.mem_read(BOARD + 12, 2)))[0]
            assert ok and value.value == result and native.position == position, (seed, draw)
            count('random_inclusive')
    report = {'status': 'passed', 'complete_original_executions': totals, 'zero_width_ranges_matched_as_faults': faults, 'scope': 'Complete 482480, 487870, 481420, 4ae170 and 482750 execute in the original; objects, ' 'cursor globals, run-length sizes, draw values and sample positions compare ' '(three seeds, including buffer wrap). Zero-width ranges fault in the original and ' 'are rejected natively.'}
    (args.build_dir / 'engine-helpers-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))
if __name__ == '__main__':
    main()
