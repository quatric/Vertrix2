"""Verify full block scalar/constructor/create/spawn EAX, calls and live storage."""
import ctypes as c
import random
import struct
from original import Original
from oracle_kit import Stubs, Resolve
from verify_call_glue import Call, Calls
import verify_support as vs
U = c.c_uint32
Read = c.CFUNCTYPE(c.c_int, U, c.c_uint, c.POINTER(U), c.c_void_p)
Write = c.CFUNCTYPE(c.c_int, U, c.c_uint, U, c.c_void_p)
BOARD, BLOCK, TABLE, SIZE = 0x808000, 0x80a000, 0x53bcd0, 0x400


def main():
    args = vs.parse(__doc__, 2048)
    native = vs.build(args, 'block-factory-full', ['block_factory.c', 'actor_storage.c',
                      'actor_fields.c', 'board_cells.c', 'call_glue.c'])
    original = Original(args.executable); cpu = original.cpu
    rng = random.Random(0x42bbd0)
    regions, buffers = {}, {}
    oracle_log, native_log, contexts, returned = [], [], [], []
    mutation = 0; active = 0; failure = None; allocation = BLOCK; index = 0

    def locate(a, width):
        for base, data in regions.items():
            if base <= a and a + width <= base + len(data): return data, a - base
        return None, None

    def host_store(a, data):
        region, offset = locate(a, len(data)); region[offset:offset + len(data)] = data
        for base, buffer in buffers.items():
            if base <= a and a + len(data) <= base + SIZE:
                c.memmove(c.addressof(buffer) + a - base, data, len(data))

    def sync_buffers():
        for base, buffer in buffers.items(): regions[base][:] = buffer.raw

    def effects(target, count, store):
        if mutation == 1 and target == 0x4826c0 and count == 0:
            store((TABLE + index * 8) & 0xffffffff, struct.pack('<2I', 333, 399))
        if mutation == 2 and target == 0x4826c0 and count == 1:
            store((TABLE + index * 8) & 0xffffffff, struct.pack('<I', 0xfffffff9))
        if active == 0x42bbd0 and target == 0x4ca000 and mutation == 1:
            store(allocation + 0x156, b'ab')
            store(allocation + 0x15f, b'!')
        if active == 0x42bbd0 and target == 0x4ca000 and mutation == 2:
            store(allocation + 0x154, struct.pack('<I', 0x12345678))
            store(BOARD + 0x38, b'abcd')
        if mutation == 3 and target == 0x4ca000:
            store(BOARD + 0xc, struct.pack('<I', 0xfff10019))
            store(BOARD + 0x14, struct.pack('<I', 0x81230027))
            store(allocation + 0x156, b'xy')

    def handler(target, eax, edx, ebx, ecx, stack):
        count = len(oracle_log); oracle_log.append((target, eax, edx, ebx, ecx))
        effects(target, count, cpu.mem_write)
        value = allocation if target == 0x4ca000 else \
            (rng.getrandbits(16) << 16) | rng.randrange(max(1, edx & 0xffff))
        returned.append(value); return value
    stubs = Stubs(cpu, handler); stubs.add(0x4ca000); stubs.add(0x4826c0)

    @Read
    def read(a, width, value, context):
        contexts.append(context); sync_buffers(); data, offset = locate(a, width)
        if data is None or failure == ('read', a, len(native_log)): return 0
        value[0] = int.from_bytes(data[offset:offset + width], 'little'); return 1
    @Write
    def write(a, width, value, context):
        contexts.append(context); sync_buffers(); data, offset = locate(a, width)
        if data is None or failure == ('write', a, len(native_log)): return 0
        host_store(a, value.to_bytes(4, 'little')[:width]); return 1
    @Resolve
    def resolve(token, pointer, size, context):
        contexts.append(context)
        if token not in buffers or failure == ('resolve', token, len(native_log)): return 0
        pointer[0] = c.addressof(buffers[token]); size[0] = SIZE; return 1
    @Call
    def call(pointer, context):
        site = pointer.contents; count = len(native_log)
        native_log.append((site.target, site.eax, site.edx, site.ebx, site.ecx)); contexts.append(context)
        effects(site.target, count, host_store)
        return returned[count] if count < len(returned) else 0
    calls = Calls(call, 0x1234)
    P, SZ, UP = c.c_void_p, c.c_size_t, c.POINTER(U)
    scalar = {0x4ac8d0: 'actor_attach_resource', 0x4adf20: 'actor_initialize',
              0x42bb00: 'block_construct', 0x43a080: 'block_construct_kind_one',
              0x4b5400: 'actor_construct_518174'}
    totals = {}; guard_failures = 0
    for address, name in scalar.items():
        function = getattr(native, 'vertrix_' + name + '_full')
        extra = [U] if address == 0x4ac8d0 else ([c.c_uint16] * 3 + [U] * 4 if address == 0x4adf20 else [])
        function.argtypes = [P, SZ, U, *extra, UP]
        for case in range(args.cases):
            token = BLOCK + (case % 2) * 0x1000; raw = rng.randbytes(SIZE); cpu.mem_write(token, raw)
            words = [rng.getrandbits(16) for _ in range(3)]; dwords = [rng.getrandbits(32) for _ in range(4)]
            wanted = original.call(address, eax=token, edx=words[0] if address == 0x4adf20 else dwords[0],
                                   ebx=words[1] if address == 0x4adf20 else rng.getrandbits(32),
                                   ecx=words[2] if address == 0x4adf20 else rng.getrandbits(32),
                                   args=(*dwords, rng.getrandbits(32)) if address == 0x4adf20 else ())
            guard = bytes([0x57]) * 16; host = c.create_string_buffer(guard + raw + guard, SIZE + 32)
            values = dwords[:1] if address == 0x4ac8d0 else (words + dwords if address == 0x4adf20 else [])
            result = U(0xdeadbeef)
            assert function(c.byref(host, 16), SIZE, token, *values, c.byref(result))
            assert result.value == wanted == token
            assert host.raw == guard + bytes(cpu.mem_read(token, SIZE)) + guard
            totals[hex(address)] = totals.get(hex(address), 0) + 1
        required = 0xb4 if address == 0x4ac8d0 else (0x158 if address == 0x4adf20 else 0x160)
        for size in (0, 1, required - 4, required - 1):
            host = c.create_string_buffer(raw, SIZE); result = U(0xdeadbeef)
            assert not function(host, size, token, *values, c.byref(result))
            assert host.raw == raw and result.value == 0xdeadbeef
            guard_failures += 1
        host = c.create_string_buffer(raw, SIZE)
        assert not function(host, SIZE, token, *values, None) and host.raw == raw
        guard_failures += 1
    native.vertrix_block_create_full.argtypes = [U, U, U, U, Resolve, P, c.POINTER(Calls), UP]
    native.vertrix_block_spawn_full.argtypes = [U, U, U, Read, Write, P, Resolve, P, c.POINTER(Calls), UP]
    mutations = {}; failures = 0
    initial = {}
    def fresh():
        nonlocal regions, buffers, initial
        regions = {BOARD: bytearray(rng.randbytes(SIZE)), BLOCK: bytearray(rng.randbytes(SIZE)),
                   0: bytearray(rng.randbytes(SIZE)), TABLE: bytearray(rng.randbytes(0x800))}
        struct.pack_into('<2I', regions[TABLE], (index * 8) & 0x7ff, 10, 71)
        for base, data in regions.items(): cpu.mem_write(base, bytes(data))
        buffers = {base: c.create_string_buffer(bytes(regions[base]), SIZE) for base in (BLOCK, 0)}
        initial = {base: bytes(data) for base, data in regions.items()}
        oracle_log.clear(); native_log.clear(); contexts.clear(); returned.clear()
    for active in (0x42bbd0, 0x430800):
        for case in range(args.cases + 3):
            mutation = 0 if case < args.cases else case - args.cases + 1
            allocation = 0 if case % 31 == 0 else BLOCK
            index = [0, 1, 18, 127, 128, 255, 0x40000001, 0x80000012][case % 8]
            fresh(); kind = index & 0xff; d0, steps, handler_token, ebx = [rng.getrandbits(32) for _ in range(4)]
            wanted = original.call(active, eax=kind if active == 0x42bbd0 else BOARD,
                                   edx=d0 if active == 0x42bbd0 else index,
                                   ebx=steps if active == 0x42bbd0 else ebx, ecx=handler_token)
            result = U(0xdeadbeef)
            if active == 0x42bbd0:
                status = native.vertrix_block_create_full(kind, d0, steps, handler_token,
                         resolve, 0x1234, c.byref(calls), c.byref(result))
            else:
                status = native.vertrix_block_spawn_full(BOARD, index, ebx, read, write, 0x1234,
                         resolve, 0x1234, c.byref(calls), c.byref(result))
            assert status and result.value == wanted == allocation, (active, case, result.value, wanted)
            assert oracle_log == native_log, (active, case, oracle_log, native_log)
            sync_buffers()
            assert all(bytes(data) == bytes(cpu.mem_read(base, len(data))) for base, data in regions.items()), (active, case)
            assert contexts and all(x == 0x1234 for x in contexts)
            totals[hex(active)] = totals.get(hex(active), 0) + 1
            mutations[hex(active)] = mutations.get(hex(active), 0) + bool(mutation)
    mutation = 3; allocation = BLOCK
    for failure in [('resolve', BLOCK, 3), ('read', BOARD + 0x14, 3), ('write', BLOCK + 0xae, 3)]:
        fresh(); returned[:] = [0x11110003, 0x22220005, BLOCK]
        result = U(0xdeadbeef)
        assert not native.vertrix_block_spawn_full(BOARD, index, 123, read, write, 0x1234,
                    resolve, 0x1234, c.byref(calls), c.byref(result))
        assert result.value == 0xdeadbeef and len(native_log) == 3
        assert contexts and all(x == 0x1234 for x in contexts)
        sync_buffers()
        assert regions[BOARD][0xc:0x10] == struct.pack('<I', 0xfff10019)
        if failure[0] != 'resolve':
            assert struct.unpack_from('<I', regions[BLOCK], 0x158)[0] == 0x514914
        if failure[0] == 'read':
            assert regions[BLOCK][0x8e] == 1
            assert regions[BLOCK][0xa8:0xb0] == bytes(8)
        if failure[0] == 'write':
            assert regions[BLOCK][0x8e] == 3
            assert struct.unpack_from('<4H', regions[BLOCK], 0xa8) == (0xfff1, 0x68, 0x8123, 0)
        if failure[0] == 'resolve':
            assert regions[BLOCK][0x156:0x158] == b'xy'
            assert regions[BLOCK][0x158:] == initial[BLOCK][0x158:]
        failures += 1
    assert totals == {**{hex(a): args.cases for a in scalar}, '0x42bbd0': args.cases + 3, '0x430800': args.cases + 3}
    assert guard_failures == 25 and failures == 3
    vs.write_report(args, 'block-factory-full', {'status': 'passed', 'complete_original_executions': totals,
        'callback_mutation_cases': mutations, 'scalar_guard_failure_cases': guard_failures,
        'late_spawn_failure_cases': failures,
        'scope': 'Seven whole routines: exact EAX and guarded storage, allocation/draw registers/order/context, '
                 'signed byte kinds and wrapping range indices. Independent callback mutations change '
                 'ranges before first lookup, low after second draw, and board clip during allocation. '
                 'Zero allocations execute the original null-token storage path with explicitly supplied backing.'})


if __name__ == '__main__':
    main()
