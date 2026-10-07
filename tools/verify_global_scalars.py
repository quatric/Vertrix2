"""Verify complete global scalar entrypoints, exact access order and EAX against the executable."""
import ctypes as c
import random
import struct
from unicorn import UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE, UC_MEM_WRITE
from original import Original
import verify_support as vs

U = c.c_uint32
Read = c.CFUNCTYPE(c.c_int, U, c.c_uint, c.POINTER(U), c.c_void_p)
Write = c.CFUNCTYPE(c.c_int, U, c.c_uint, U, c.c_void_p)
ROUTINES = {0x415b30: 'set_first_cell', 0x415b40: 'set_second_cell',
            0x415d90: 'set_current_cell', 0x415d60: 'read_current_cell',
            0x41a930: 'clear', 0x41d660: 'increment', 0x415b10: 'clear_tables',
            0x415d40: 'next_index', 0x415530: 'reset_pair'}
REGIONS = {0x532980: 0x240, 0x534400: 0x200, 0x53ba40: 0x180, 0x540000: 0x100}


def main():
    args = vs.parse(__doc__, 2048)
    native = vs.build(args, 'global-scalars', ['object_scalars.c', 'actor_storage.c'])
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x415b10)
    regions = {}
    oracle_log, native_log, contexts = [], [], []
    failure = None

    def locate(address, width):
        for base, data in regions.items():
            if base <= address and address + width <= base + len(data):
                return data, address - base
        return None, None

    def oracle_access(cpu, access, address, width, value, context):
        data, offset = locate(address, width)
        if data is not None:
            kind = 'w' if access == UC_MEM_WRITE else 'r'
            if kind == 'r':
                value = int.from_bytes(cpu.mem_read(address, width), 'little')
            oracle_log.append((kind, address, width, value & ((1 << (width * 8)) - 1)))

    cpu.hook_add(UC_HOOK_MEM_READ | UC_HOOK_MEM_WRITE, oracle_access)

    @Read
    def read(address, width, value, context):
        contexts.append(context)
        data, offset = locate(address, width)
        number = 0 if data is None else int.from_bytes(data[offset:offset + width], 'little')
        native_log.append(('r', address, width, number))
        if data is None or len(native_log) - 1 == failure:
            return 0
        value[0] = number
        return 1

    @Write
    def write(address, width, value, context):
        contexts.append(context)
        native_log.append(('w', address, width, value))
        data, offset = locate(address, width)
        if data is None or len(native_log) - 1 == failure:
            return 0
        data[offset:offset + width] = value.to_bytes(width, 'little')
        return 1

    totals, failed = {}, 0
    indices = list(range(32)) + [0x40000000, 0x80000000, 0xc0000000, 0xffffffff,
                                 0x3fffffff, 0x7fffffff, 0xbfffffff, 0xfffffff9]
    for address, name in ROUTINES.items():
        function = getattr(native, 'vertrix_global_' + name + '_full')
        function.argtypes = [U, Read, Write, c.c_void_p, c.POINTER(U)]
        for case in range(args.cases):
            initial = {base: rng.randbytes(size) for base, size in REGIONS.items()}
            regions = {base: bytearray(raw) for base, raw in initial.items()}
            index = indices[case % len(indices)]
            data, offset = locate(0x53bb10, 4)
            struct.pack_into('<I', data, offset, index)
            data, offset = locate(0x5329f8, 4)
            struct.pack_into('<I', data, offset, (0xffffffff if case % 4 == 0 else rng.getrandbits(32)))
            data, offset = locate(0x532b40, 4)
            struct.pack_into('<I', data, offset, [0, 1, 2, 0xffffffff][case % 4])
            initial = {base: bytes(data) for base, data in regions.items()}
            for base, data in initial.items():
                cpu.mem_write(base, data)
            eax = index if address in (0x415b30, 0x415b40) else rng.getrandbits(32)
            oracle_log.clear(); native_log.clear(); contexts.clear()
            wanted = original.call(address, eax=eax, edx=rng.getrandbits(32),
                                   ebx=rng.getrandbits(32), ecx=rng.getrandbits(32))
            result = U(0xdeadbeef)
            assert function(eax, read, write, 0x1234, c.byref(result)), (address, case)
            assert result.value == wanted, (address, case, wanted, result.value)
            assert native_log == oracle_log, (address, case, oracle_log, native_log)
            assert all(bytes(data) == bytes(cpu.mem_read(base, len(data)))
                       for base, data in regions.items()), (address, case)
            assert contexts and all(x == 0x1234 for x in contexts)
            totals[hex(address)] = totals.get(hex(address), 0) + 1
            # Fail every boundary of a representative execution. Earlier effects must persist.
            if case == 1:
                for failure in range(len(oracle_log)):
                    regions = {base: bytearray(raw) for base, raw in initial.items()}
                    expected = {base: bytearray(raw) for base, raw in initial.items()}
                    for kind, token, width, value in oracle_log[:failure]:
                        if kind == 'w':
                            for base, data in expected.items():
                                if base <= token < base + len(data):
                                    data[token - base:token - base + width] = value.to_bytes(width, 'little')
                    native_log.clear(); contexts.clear(); result = U(0xdeadbeef)
                    assert not function(eax, read, write, 0x1234, c.byref(result))
                    assert result.value == 0xdeadbeef and regions == expected, (address, failure)
                    assert native_log == oracle_log[:failure + 1], (address, failure)
                    assert all(x == 0x1234 for x in contexts)
                    failed += 1
                failure = None
        before = {base: bytes(data) for base, data in regions.items()}
        native_log.clear(); contexts.clear()
        assert not function(1, read, write, 0x1234, None)
        assert not native_log and all(bytes(regions[b]) == raw for b, raw in before.items())
    assert totals == {hex(address): args.cases for address in ROUTINES}
    assert failed == 52, failed
    vs.write_report(args, 'global-scalars', {
        'status': 'passed', 'complete_original_executions': totals,
        'native_boundary_failure_cases': failed, 'null_result_no_effect_cases': len(ROUTINES),
        'scope': 'Nine complete original routines; independent guarded global storage, exact EAX, '
                 'ordered reads/writes and context. Indexed addressing includes high-bit wrapping, '
                 'negative-offset indices and index/global aliasing. Increment wrap and all reset modes '
                 'compare. Every access in representative executions is failed to verify retained effects.'})


if __name__ == '__main__':
    main()
