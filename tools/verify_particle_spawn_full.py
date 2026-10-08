"""Verify full spread/sparkle spawn returns, register calls and mutable storage."""
import ctypes as c
import random
import struct
from original import Original
from oracle_kit import Stubs
from verify_call_glue import Call, Calls
import verify_support as vs

U = c.c_uint32
Read = c.CFUNCTYPE(c.c_int, U, c.c_uint, c.POINTER(U), c.c_void_p)
Write = c.CFUNCTYPE(c.c_int, U, c.c_uint, U, c.c_void_p)
CHILD, SCENE, SCREEN, SCRATCH, TABLE = 0x80a000, 0x80b000, 0x5b9c8e, 0x540fd4, 0x4fb93c


def main():
    args = vs.parse(__doc__, 4096)
    native = vs.build(args, 'particle-spawn-full', ['particle_spawn.c', 'actor_storage.c',
                      'actor_fields.c', 'actor_chain_visit.c', 'call_glue.c'])
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x43dea0)
    regions = {}
    oracle_log, native_log, contexts, returns = [], [], [], []
    address, mode, failure = 0, 0, None

    def locate(a, width):
        for base, data in regions.items():
            if base <= a and a + width <= base + len(data):
                return data, a - base
        return None, None

    def host_store(a, data):
        region, offset = locate(a, len(data))
        region[offset:offset + len(data)] = data

    def effects(index, store):
        if address == 0x43dea0:
            if mode == 1 and index == 0:
                store(SCENE + 0x94c, struct.pack('<I', 1))
                store(SCRATCH, struct.pack('<4H', 711, 577, 17, 23))
            if mode == 2 and index == 1:
                store(SCRATCH + 2, struct.pack('<3H', 311, 79, 81))
                store(SCENE + 0x94c, struct.pack('<I', 0))
            if mode == 3 and index == 2:
                store(SCENE + 0x94c, struct.pack('<I', 1))
                store(SCRATCH + 6, struct.pack('<H', 0x8001))
            if mode == 4 and index == 3:
                store(SCENE + 0x94c, struct.pack('<I', 0))
                store(CHILD + 0x28, struct.pack('<H', 999))
        else:
            if mode in (1, 4) and index == 0:
                store(TABLE, bytes([0x99]) * 40)
                store(CHILD + 0xb8, struct.pack('<I', 2))
            if mode == 2 and index == 0:
                store(CHILD + 0xa, struct.pack('<H', 0x612))
                store(CHILD + 0xb8, struct.pack('<I', 0))
            if mode == 3 and index == 1:
                store(CHILD + 0x95, bytes([33]))
                store(CHILD + 0xe, struct.pack('<H', 999))

    def handler(target, eax, edx, ebx, ecx, stack):
        index = len(oracle_log)
        oracle_log.append((target, eax, edx, ebx, ecx))
        effects(index, cpu.mem_write)
        value = rng.getrandbits(32) if target == 0x4ac8a0 else \
            (rng.getrandbits(16) << 16) | rng.randrange(max(1, edx & 0xffff))
        returns.append(value)
        return value

    stubs = Stubs(cpu, handler)
    stubs.add(0x4ac8a0); stubs.add(0x4826c0)

    @Read
    def read(a, width, value, context):
        contexts.append(context)
        data, offset = locate(a, width)
        if data is None or failure == ('read', a, len(native_log)):
            return 0
        value[0] = int.from_bytes(data[offset:offset + width], 'little')
        return 1

    @Write
    def write(a, width, value, context):
        contexts.append(context)
        data, offset = locate(a, width)
        if data is None or failure == ('write', a, len(native_log)):
            return 0
        data[offset:offset + width] = value.to_bytes(4, 'little')[:width]
        return 1

    @Call
    def call(pointer, context):
        site = pointer.contents
        index = len(native_log)
        native_log.append((site.target, site.eax, site.edx, site.ebx, site.ecx))
        contexts.append(context)
        effects(index, host_store)
        return returns[index] if index < len(returns) else 0

    calls = Calls(call, 0x1234)
    functions = {0x43dea0: native.vertrix_spawn_spread_full,
                 0x43e920: native.vertrix_spawn_place_full}
    for function in functions.values():
        function.argtypes = [U, U, Read, Write, c.c_void_p, c.POINTER(Calls), c.POINTER(U)]
    totals, mutations = {}, {}
    initial = {}
    for address, function in functions.items():
        for case in range(args.cases + 4):
            mode = 0 if case < args.cases else case - args.cases + 1
            regions = {CHILD: bytearray(rng.randbytes(0x1000)), SCENE: bytearray(rng.randbytes(0x1000)),
                       SCREEN: bytearray(struct.pack('<2H', rng.randrange(1, 900), rng.randrange(1, 900))),
                       SCRATCH: bytearray(rng.randbytes(8)), TABLE: bytearray(rng.randbytes(40))}
            struct.pack_into('<I', regions[SCENE], 0x94c, 1 if case % 2 else 0)
            struct.pack_into('<I', regions[CHILD], 0xb8,
                             (2 if mode in (2, 3) else 1) if mode else case % 4)
            struct.pack_into('<2H', regions[CHILD], 8, rng.randrange(1, 900), rng.randrange(0x137, 0x600))
            initial = {base: bytes(data) for base, data in regions.items()}
            for base, data in initial.items(): cpu.mem_write(base, data)
            oracle_log.clear(); native_log.clear(); contexts.clear(); returns.clear()
            ebx = rng.getrandbits(32)
            wanted = original.call(address, eax=SCENE if address == 0x43dea0 else CHILD,
                                   edx=CHILD if address == 0x43dea0 else rng.getrandbits(32),
                                   ebx=ebx, ecx=rng.getrandbits(32))
            result = U(0xdeadbeef)
            assert function(SCENE if address == 0x43dea0 else CHILD,
                            CHILD if address == 0x43dea0 else ebx,
                            read, write, 0x1234, c.byref(calls), c.byref(result))
            assert result.value == wanted, (address, case, wanted, result.value)
            assert native_log == oracle_log, (address, case, oracle_log, native_log)
            assert all(bytes(data) == bytes(cpu.mem_read(base, len(data)))
                       for base, data in regions.items()), (address, case)
            assert contexts and all(x == 0x1234 for x in contexts)
            totals[hex(address)] = totals.get(hex(address), 0) + 1
            mutations[hex(address)] = mutations.get(hex(address), 0) + bool(mode)
    failed = 0
    for address, failures in {
        0x43dea0: [('read', SCENE + 0x94c, 1), ('write', CHILD + 8, 2),
                   ('read', SCENE + 0x94c, 3), ('write', CHILD + 0x60, 4)],
        0x43e920: [('read', CHILD + 0xa, 1), ('write', CHILD + 0x16, 2)]}.items():
        function = functions[address]
        for failure in failures:
            mode = 2
            regions = {base: bytearray(data) for base, data in initial.items()}
            struct.pack_into('<I', regions[CHILD], 0xb8, 2)
            native_log.clear(); contexts.clear()
            returns[:] = [0x12340002] * 4
            result = U(0xdeadbeef)
            assert not function(SCENE if address == 0x43dea0 else CHILD,
                                CHILD if address == 0x43dea0 else 123,
                                read, write, 0x1234, c.byref(calls), c.byref(result))
            assert result.value == 0xdeadbeef and len(native_log) == failure[2]
            assert all(x == 0x1234 for x in contexts)
            if address == 0x43dea0:
                assert struct.unpack_from('<I', regions[CHILD], 0xb0)[0] == 0x544c10
            else:
                assert struct.unpack_from('<H', regions[CHILD], 0xe)[0] == 2
            failed += 1
    assert totals == {hex(address): args.cases + 4 for address in functions}
    assert mutations == {hex(address): 4 for address in functions} and failed == 6
    vs.write_report(args, 'particle-spawn-full', {
        'status': 'passed', 'complete_original_executions': totals,
        'mutable_callback_cases': mutations, 'native_late_failure_cases': failed,
        'scope': 'Whole 43dea0 and 43e920: independent actor/scene/screen/scratch/table storage, '
                 'exact EAX and callback register order/context. Binding/draw mutations cover '
                 'scratch words, scene mode before/after final draw, live height, table snapshots '
                 'and callback actor writes. Random results have nonzero upper-word probes.'})


if __name__ == '__main__':
    main()
