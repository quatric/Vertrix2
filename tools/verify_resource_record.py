"""Compare complete original resource record routines with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
RECORD, STRINGS, TABLE = 0x80a000, 0x80b000, 0x544790
Release = c.CFUNCTYPE(None, c.c_uint32, c.c_void_p)
Method = c.CFUNCTYPE(U, U, U, c.c_void_p)
Read = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint, c.POINTER(c.c_uint32), c.c_void_p)
Draw = c.CFUNCTYPE(None, c.c_uint32, c.c_uint32, c.c_uint32, c.c_uint32, c.POINTER(U), c.c_void_p)
SIZE = 0x300


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    parser.add_argument('--probe-release-clears-global', action='store_true',
                        help='Reproduce the known omitted release-register return; expected to fail.')
    args = parser.parse_args()
    n = build(args.build_dir, 'resource-record', ['resource_record.c', 'actor_storage.c'])
    n.vertrix_record_init.argtypes = [c.c_void_p, c.c_size_t, c.c_char_p, c.c_char_p] + [c.c_uint8] * 5
    n.vertrix_record_release.argtypes = [c.c_void_p, c.c_size_t, Release, c.c_void_p]
    n.vertrix_record_release_global.argtypes = [c.POINTER(U), c.c_void_p, c.c_size_t, Release,
                                                c.c_void_p, Method, c.c_void_p, Read, c.c_void_p]
    n.vertrix_record_release_global.restype = U
    n.vertrix_record_draw.argtypes = [c.c_void_p, c.c_size_t, Resolve, Draw, c.c_void_p]
    n.vertrix_text_width.argtypes = [c.c_char_p, c.POINTER(c.c_uint8)]
    n.vertrix_text_width.restype = c.c_uint16
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x441530)
    pool = Pool(cpu, 8)
    stubs = Stubs(cpu, lambda *a: None)
    stubs.add(0x478d80)
    stubs.add(0x47ce10, 4)
    released = []
    drawn = []

    @Release
    def release(handle, context):
        released.append(handle)

    @Draw
    def draw(first, second, ecx, ebx, stack, context):
        drawn.append((first, second, ebx, ecx, *stack[:4]))

    totals = {}

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def text(limit):
        return bytes(rng.randrange(1, 256) if rng.random() < 0.8 else 0x20
                     for _ in range(rng.randrange(limit)))

    for case in range(args.cases):
        memory = bytearray(rng.randbytes(SIZE))
        for offset in (0x268, 0x26c, 0x270, 0x274, 0x278):
            struct.pack_into('<I', memory, offset, rng.choice(pool.handles + [0, 0]))
        memory[0x220] = rng.choice([0, 1, 1, 2])
        memory[0x222] = rng.choice([0, 1, 1, 2])
        buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(memory))

        def fresh():
            cpu.mem_write(RECORD, bytes(memory))
            pool.fill(rng)
            c.memmove(buffer, bytes(memory), SIZE)

        def check(name):
            assert bytes(buffer) == bytes(cpu.mem_read(RECORD, SIZE)), (case, name)
            assert pool.same(), (case, name)
            count(name)

        name_text, path_text = text(0x103), text(0x103)
        cpu.mem_write(STRINGS, name_text + b'\0')
        cpu.mem_write(STRINGS + 0x200, path_text + b'\0')
        flags = [rng.randrange(256) for _ in range(5)]
        fresh()
        original.call(0x441530, eax=RECORD, edx=STRINGS, ebx=flags[0], ecx=flags[1],
                      args=(flags[2], flags[3], flags[4], STRINGS + 0x200))
        assert n.vertrix_record_init(buffer, SIZE, name_text, path_text, *flags)
        check('init')
        fresh()
        stubs.log.clear()
        released.clear()
        original.call(0x441a80, eax=RECORD)
        assert n.vertrix_record_release(buffer, SIZE, release, None)
        assert [e[1] for e in stubs.log] == released, case
        check('release')
        fresh()
        stubs.log.clear()
        drawn.clear()
        original.call(0x441b30, eax=RECORD)
        assert n.vertrix_record_draw(buffer, SIZE, pool.resolve, draw, None)
        assert [e[1:] for e in stubs.log] == drawn, case
        check('draw')
        table = bytes(rng.randrange(256) if rng.random() < 0.7 else rng.choice([0, 1])
                      for _ in range(256))
        cpu.mem_write(TABLE, table)
        string = text(40)
        cpu.mem_write(STRINGS, string + b'\0')
        result = original.call(0x442b00, eax=STRINGS, ebx=rng.getrandbits(32))
        assert n.vertrix_text_width(string, (c.c_uint8 * 256).from_buffer_copy(table)) == result & 0xffff, case
        count('text_width')
    # 0x41a9e0 over a manual global cell + record clear of the RNG buffer.
    # The method resolves through two levels: [record + 0x27c] names a table
    # whose first dword is the stubbed method.
    RECORD2, MTABLE = 0x807100, 0x807500
    METHOD_ADDR = 0x707000
    g_rng = random.Random(0x41a9e0)
    g_canned = [0]
    callback_events = []
    native_events = []
    mutation_value = 0
    mutate_method = False
    mutation_cases = 0
    release_mutation_cases = 0
    release_mutation = False
    release_clears_global = False
    native_reads = []
    zero_method_mutation_cases = 0
    release_mutated = False
    native_release_mutated = False
    MTABLE2 = MTABLE + 4
    host_cell = None
    host_record = None
    host_tables = {}

    def method_handler(address, eax, edx, ebx, ecx, stack):
        nonlocal release_mutated
        if address == 0x478d80 and release_mutation and not release_mutated:
            release_mutated = True
            if release_clears_global:
                cpu.mem_write(0x544070, struct.pack('<I', 0))
            else:
                cpu.mem_write(RECORD2 + 0x27c, struct.pack('<I', MTABLE2))
        if address == METHOD_ADDR:
            callback_events.append((eax, edx, struct.unpack('<I', cpu.mem_read(0x544070, 4))[0]))
            if mutate_method:
                cpu.mem_write(0x544070, struct.pack('<I', mutation_value))
                cpu.mem_write(RECORD2 + 0x280, struct.pack('<I', mutation_value))
            return g_canned[0]
        return None

    stubs.handler = method_handler
    stubs.add(METHOD_ADDR)
    method_calls = []

    @Release
    def global_release(handle, context):
        nonlocal native_release_mutated
        released.append(handle)
        if release_mutation and not native_release_mutated:
            native_release_mutated = True
            if release_clears_global:
                host_cell[0] = 0
            else:
                c.memmove(c.addressof(host_record) + 0x27c, struct.pack('<I', MTABLE2), 4)

    @Method
    def method(object, flag, context):
        method_calls.append((object, flag))
        native_events.append((object, flag, host_cell[0]))
        if mutate_method:
            host_cell[0] = mutation_value
            c.memmove(c.addressof(host_record) + 0x280, struct.pack('<I', mutation_value), 4)
        return g_canned[0]

    @Read
    def read(address, width, value, context):
        if RECORD2 <= address and address + width <= RECORD2 + SIZE:
            data = host_record.raw[address - RECORD2:address - RECORD2 + width]
        else:
            data = host_tables.get(address)
            if data is None or len(data) < width:
                return 0
            data = data[:width]
        native_reads.append((address, width))
        value[0] = int.from_bytes(data, 'little')
        return 1

    for case in range(args.cases):
        use_record = g_rng.random() < 0.7 or args.probe_release_clears_global
        record = bytearray(g_rng.getrandbits(8) for _ in range(SIZE))
        if use_record:
            # +0x268 stays zero (nonzero escapes to unrecovered 0x441b1c).
            struct.pack_into('<I', record, 0x268, 0)
            for offset in (0x26c, 0x270, 0x274, 0x278):
                if g_rng.random() < 0.5:
                    struct.pack_into('<I', record, offset, pool.handles[0])
            for offset, value in ((0x220, g_rng.choice([0, 1, 2])), (0x222, g_rng.choice([0, 1, 2]))):
                struct.pack_into('<B', record, offset, value)
            struct.pack_into('<I', record, 0x27c, MTABLE)
            cpu.mem_write(MTABLE, struct.pack('<I', METHOD_ADDR))
            host_tables[MTABLE] = struct.pack('<I', METHOD_ADDR)
        else:
            record = bytearray(SIZE)
        release_clears_global = args.probe_release_clears_global
        release_mutation = use_record and (case % 4 == 0 or release_clears_global)
        release_mutated = native_release_mutated = False
        if release_mutation:
            struct.pack_into('<I', record, 0x274, pool.handles[0])
        cpu.mem_write(MTABLE2, struct.pack('<I', METHOD_ADDR))
        host_tables[MTABLE2] = struct.pack('<I', METHOD_ADDR)
        global_value = RECORD2 if use_record else 0
        g_canned[0] = g_rng.getrandbits(32)
        cpu.mem_write(RECORD2, bytes(record))
        # The original reads its global from the fixed address 0x544070.
        cpu.mem_write(0x544070, struct.pack('<I', global_value))
        stubs.log.clear()
        released.clear()
        method_calls.clear()
        callback_events.clear()
        native_events.clear()
        native_reads.clear()
        mutate_method = use_record and case % 2 == 0
        mutation_value = 0 if case % 8 == 0 else g_rng.getrandbits(32)
        expect = original.call(0x41a9e0, eax=RECORD2, edx=0, ebx=0, ecx=0)
        if not release_clears_global:
            assert expect == (g_canned[0] if callback_events else 0), (use_record, hex(expect))
        host_cell = (U * 1)(global_value)
        host_record = c.create_string_buffer(bytes(record), SIZE)
        got = n.vertrix_record_release_global(host_cell, host_record, SIZE, global_release, None,
                                                    method, None, read, None)
        if release_clears_global:
            evidence = {'fixture': 'release_callback_clears_global', 'case': case,
                              'address': '0x41a9e0', 'input_registers': {'eax': RECORD2, 'edx': 0, 'ebx': 0, 'ecx': 0},
                              'original_return': expect, 'native_return': got,
                              'original_release_calls': [list(e) for e in stubs.log if e[0] == 0x478d80],
                              'original_method_events': callback_events, 'native_method_events': native_events}
            (args.build_dir / 'release-clears-global-mismatch.json').write_text(
                json.dumps(evidence, indent=2) + '\n')
            print(json.dumps(evidence, indent=2))
            assert got == expect, 'Known omitted original release-register return'
        assert native_events == callback_events, (case, native_events, callback_events)
        if mutate_method and callback_events:
            mutation_cases += 1
            zero_method_mutation_cases += mutation_value == 0
        if release_mutation:
            assert release_mutated and native_release_mutated
            release_mutation_cases += 1
        expected_table = MTABLE2 if release_mutation else MTABLE
        assert native_reads == ([(RECORD2 + 0x27c, 4), (expected_table, 4)] if use_record else [])
        assert got == expect, (use_record, hex(expect), hex(got))
        assert host_cell[0] == struct.unpack('<I', cpu.mem_read(0x544070, 4))[0]
        assert host_record.raw == bytes(cpu.mem_read(RECORD2, SIZE))
        assert [e[1] for e in stubs.log if e[0] == 0x478d80] == released
        assert method_calls == [(event[0], event[1]) for event in callback_events]
        count('0x41a9e0')
    assert totals['0x41a9e0'] == args.cases
    assert mutation_cases > 0 and release_mutation_cases > 0 and zero_method_mutation_cases > 0
    report = {'status': 'passed', 'complete_original_executions': totals,
              'global_method_mutation_cases': mutation_cases,
              'global_release_method_table_mutation_cases': release_mutation_cases,
              'global_method_zero_mutation_cases': zero_method_mutation_cases,
              'limitations': ['Release callbacks changing the global object cell are outside this suite: '
                              'the native void release boundary omits the original release-register '
                              'return when the cell becomes zero. Reproduce with '
                              '--probe-release-clears-global (expected failure).'],
              'scope': 'Complete 441530, 441a80, 441b30, 442b00 and 41a9e0 execute in the original '
                       '(release 478d80 and draw 47ce10 stubbed and logged, methods stubbed); the '
                       'whole record, every pool object, the global cell, events and the 16-bit '
                       'text width compare. Global-method callbacks observe and mutate the global cell and '
                       'record storage; native resolution reads independent host memory.'}
    (args.build_dir / 'resource-record-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
