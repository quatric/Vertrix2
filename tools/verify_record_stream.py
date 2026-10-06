"""Compare the original saved-block loader 0x4293e0 with the native recovery."""
import argparse, ctypes as c, json, random, struct
from pathlib import Path
from original import Original
from oracle_kit import build

OBJECT, STREAM, BLOCK, DATA = 0x801000, 0x802000, 0x802100, 0x804000
OSIZE, SSIZE, DSIZE = 0x240, 0x20, 0x800
U = c.c_uint32
Fetch = c.CFUNCTYPE(None, c.c_void_p, U, c.POINTER(c.c_uint8), U)
Read = c.CFUNCTYPE(c.c_int, U, U, c.POINTER(U), c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'record-stream',
              ['record_stream.c', 'stream_read.c', 'object_dwords.c', 'actor_storage.c',
               'actor_fields.c', 'board_cells.c', 'actor_gate.c'])
    n.vertrix_record_table_load.argtypes = [c.c_void_p, c.c_size_t, c.c_void_p, c.c_size_t, Read,
                                           c.c_void_p, Fetch, c.c_void_p]
    n.vertrix_saved_block_load.argtypes = [c.c_void_p, c.c_size_t, c.c_void_p, c.c_size_t, Read,
                                           c.c_void_p, Fetch, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4293e0)
    totals = {}

    @Fetch
    def fetch(context, address, destination, count):
        assert DATA <= address and address + count <= DATA + DSIZE, hex(address)
        c.memmove(destination, bytes(cpu.mem_read(address, count)), count)

    @Read
    def read(address, width, value, context):
        value[0] = int.from_bytes(bytes(cpu.mem_read(address, width)), 'little')
        return 1

    for case in range(args.cases):
        data = bytearray(rng.randbytes(DSIZE))
        state = rng.choice([0, 1, 1, 2, rng.getrandbits(32)])
        struct.pack_into('<I', data, 0, state)
        cpu.mem_write(DATA, bytes(data))
        length = rng.choice([0x228, 0x228, 0x228, 0x227, 0x229, rng.randrange(0x400)])
        start = DATA + rng.choice([0, 0, rng.randrange(0x100)])
        cpu.mem_write(BLOCK, struct.pack('<II', start, length))
        stream = bytearray(rng.randbytes(SSIZE))
        struct.pack_into('<I', stream, 0, BLOCK)
        obj = bytearray(rng.randbytes(OSIZE))
        cpu.mem_write(STREAM, bytes(stream))
        cpu.mem_write(OBJECT, bytes(obj))
        original.call(0x4293e0, eax=OBJECT, edx=STREAM)
        native_obj = c.create_string_buffer(bytes(obj), OSIZE)
        native_stream = c.create_string_buffer(bytes(stream), SSIZE)
        assert n.vertrix_saved_block_load(native_obj, OSIZE, native_stream, SSIZE, read, None,
                                          fetch, None), case
        assert native_obj.raw == bytes(cpu.mem_read(OBJECT, OSIZE)), ('object', case)
        assert native_stream.raw == bytes(cpu.mem_read(STREAM, SSIZE)), ('stream', case)
        key = 'loaded' if length == 0x228 else 'skipped'
        totals[key] = totals.get(key, 0) + 1
# 4121e0 : record table load
    TABLE, TSIZE = 0x806000, 0x7b8
    for case in range(args.cases):
        data = bytearray(rng.randbytes(DSIZE))
            count = rng.choice([
                           0, 1, 5, 122, rng.randrange(123)
                       ]) struct.pack_into('<II', data, 0, rng.getrandbits(32), count)
                        cpu.mem_write(DATA, bytes(data))
                            end_trim = rng.choice([ 0, 0, 0, rng.randrange(0x600) ])
                                           cpu.mem_write(BLOCK,
                                                         struct.pack('<II', DATA, DSIZE - end_trim))
                                               stream =
                bytearray(rng.randbytes(SSIZE)) struct.pack_into('<I', stream, 0, BLOCK)
                    table = bytearray(rng.randbytes(TSIZE)) cpu.mem_write(STREAM, bytes(stream))
                                cpu.mem_write(TABLE, bytes(table))
                                    original.call(0x4121e0, eax = TABLE, edx = STREAM)
                                        native_table = c.create_string_buffer(bytes(table), TSIZE)
                                                           native_stream =
                    c.create_string_buffer(bytes(stream), SSIZE)
                        assert n.vertrix_record_table_load(native_table, TSIZE, native_stream,
                                                           SSIZE, read, None, fetch, None),
        case assert native_table.raw == bytes(cpu.mem_read(TABLE, TSIZE)),
        ('table', case)assert native_stream.raw == bytes(cpu.mem_read(STREAM, SSIZE)),
        ('stream', case)totals['table_load'] = totals.get('table_load', 0) + 1 report = {'status':
        'passed', 'complete_original_executions' : totals,
                                                   'scope'
            : 'Complete 4293e0 and 4121e0 execute in the original (stream, block, data and object ' 'compare byte for byte).'
        }
        (args.build_dir / 'record-stream-verification.json')
                .write_text(json.dumps(report, indent = 2) + '\n')
                    print(json.dumps(report, indent = 2))

                        if __name__ == '__main__' : main()
