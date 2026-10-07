"""Compare the original colour table builder 0x441e30 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from unicorn import UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX
from oracle_kit import Stubs, build

U = c.c_uint32
FRAME = STACK - 4


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                'stack_third', 'out_ebx', 'out_ecx')] + [('rest%d' % i, U) for i in range(14)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


CALLEES = {0x481b20: 0, 0x481bc0: 1, 0x481e10: 0, 0x481b30: 0}


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'color-table', ['color_table.c', 'call_glue.c', 'actor_storage.c'])
    Read = c.CFUNCTYPE(c.c_int, U, c.c_uint, c.POINTER(U), c.c_void_p)
    Write = c.CFUNCTYPE(c.c_int, U, c.c_uint, U, c.c_void_p)
    n.vertrix_color_table_build_full.argtypes = [c.POINTER(Calls), U, U, U, Read, Write, c.c_void_p]
    n.vertrix_color_table_build_full.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x441e30)
    ranges = ((0x4fb9ec, 92), (0x5440f4, 92))
    host = {}
    events, native_events, native_log, errors = [], [], [], []
    tokens = []
    setup = 0

    def track_read(cpu, access, address, width, value, context):
        events.append(('read', address, width, int.from_bytes(cpu.mem_read(address, width), 'little')))

    def track_write(cpu, access, address, width, value, context):
        events.append(('write', address, width, value & 0xffffffff))

    for base, size in ranges:
        cpu.hook_add(UC_HOOK_MEM_READ, track_read, begin=base, end=base + size - 1)
        cpu.hook_add(UC_HOOK_MEM_WRITE, track_write, begin=base, end=base + size - 1)

    def mutation(index):
        # Each callback changes a future color and an output, exposing snapshot reads
        # and ensuring stores/cleanup retain the original temporal order.
        return [(0x4fb9f0 + 4 * (index % 21), tokens[index] ^ 0x11111111),
                (0x5440f8 + 4 * ((index + 3) % 21), tokens[index] ^ 0x22222222)]

    def handler(address, eax, edx, ebx, ecx, stack):
        index = len(stubs.log) - 1
        entry = (address, eax, edx, ebx, ecx, *stack)
        events.append(('call', *entry))
        for at, value in mutation(index):
            cpu.mem_write(at, struct.pack('<I', value))
        return setup if address == 0x481bc0 else tokens[index]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    def locate(address, width):
        for base, size in ranges:
            if base <= address and address + width <= base + size:
                return host[base], address - base
        return None, 0

    @Call
    def call(site, context):
        x = site.contents
        index = len(native_log)
        if x.target not in CALLEES or index >= len(tokens):
            errors.append(('call', x.target, index))
            return 0
        entry = (x.target, x.eax, x.edx, x.ebx, x.ecx) + ((x.stack,) if CALLEES[x.target] else ())
        native_log.append(entry)
        native_events.append(('call', *entry))
        for at, value in mutation(index):
            memory, offset = locate(at, 4)
            memory[offset:offset + 4] = value.to_bytes(4, 'little')
        return setup if x.target == 0x481bc0 else tokens[index]

    @Read
    def read(address, width, value, context):
        memory, offset = locate(address, width)
        if memory is None or width != 4:
            errors.append(('read', address, width))
            return 0
        value[0] = int.from_bytes(memory[offset:offset + width], 'little')
        native_events.append(('read', address, width, value[0]))
        return 1

    @Write
    def write(address, width, value, context):
        memory, offset = locate(address, width)
        if memory is None or width != 4:
            errors.append(('write', address, width))
            return 0
        memory[offset:offset + width] = value.to_bytes(width, 'little')
        native_events.append(('write', address, width, value))
        return 1

    calls = Calls(call, None)
    totals, paths = {}, {}
    callback_comparisons = reads = writes = 0
    for case in range(args.cases):
        argument = rng.getrandbits(32)
        previous = (0, 0xffffffff)[case] if case < 2 else rng.getrandbits(32)
        setup = 0 if case % 3 == 0 else (1 if case % 3 == 1 else 0x80000000)
        tokens = [rng.getrandbits(32) for _ in range(24)]
        host = {base: bytearray(rng.randbytes(size)) for base, size in ranges}
        for base, memory in host.items():
            cpu.mem_write(base, bytes(memory))
        cpu.mem_write(0, struct.pack('<I', previous))
        stubs.log.clear()
        native_log.clear()
        events.clear()
        native_events.clear()
        errors.clear()
        edx, ebx, ecx = (rng.getrandbits(32) for _ in range(3))
        expected = original.call(0x441e30, eax=argument, edx=edx, ebx=ebx, ecx=ecx)
        got = n.vertrix_color_table_build_full(c.byref(calls), FRAME, argument, previous,
                                              read, write, None)
        assert not errors, (case, errors)
        assert expected == got == previous, (case, expected, got, previous)
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert native_events == events, (case, native_events, events)
        assert all(bytes(memory) == bytes(cpu.mem_read(base, len(memory))) for base, memory in host.items()), case
        assert int.from_bytes(cpu.mem_read(0, 4), 'little') == previous, case
        assert [cpu.reg_read(reg) for reg in (UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX)] == [edx, ebx, ecx], case
        callback_comparisons += len(native_log)
        reads += sum(event[0] == 'read' for event in events)
        writes += sum(event[0] == 'write' for event in events)
        paths[len(stubs.log)] = paths.get(len(stubs.log), 0) + 1
        totals['0x441e30'] = totals.get('0x441e30', 0) + 1
    assert totals['0x441e30'] == args.cases and set(paths) == {3, 24}
    assert reads == writes == paths[24] * 21
    missing = [(None, read, write), (c.byref(Calls(Call(), None)), read, write),
               (c.byref(calls), Read(), write), (c.byref(calls), read, Write())]
    for runtime, reader, writer in missing:
        before = {base: bytes(memory) for base, memory in host.items()}
        native_log.clear()
        assert n.vertrix_color_table_build_full(runtime, FRAME, 0, 0x12345678, reader, writer, None) == 0
        assert not native_log and all(bytes(host[base]) == memory for base, memory in before.items())
    report = {'status': 'passed', 'complete_original_executions': totals,
              'call_counts_seen': {str(key): value for key, value in sorted(paths.items())},
              'exact_callback_register_stack_comparisons': callback_comparisons,
              'original_live_color_reads': reads, 'original_output_writes': writes,
              'callback_mutation_cases': args.cases, 'native_missing_boundary_rejections': len(missing),
              'scope': 'Full normal returns equal saved exception-chain tokens; exact callback '
                       'register/stack inputs, ordered live color reads/output writes and 184 '
                       'independent color/output bytes including guards compare under callback '
                       'mutation. Both setup paths and original restored exception chain/caller '
                       'registers compare. Exception-stack bookkeeping and unwinding are outside '
                       'the runtime boundary.'}
    (args.build_dir / 'color-table-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
