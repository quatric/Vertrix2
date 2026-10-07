"""Compare the original notice routine 0x416010 with the native recovery."""
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


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(14)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


CALLEES = (0x47f9b0, 0x4ca280, 0x4b76d0, 0x4ca210)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'notice', ['call_glue.c', 'actor_storage.c'])
    Read = c.CFUNCTYPE(c.c_int, U, c.c_uint, c.POINTER(U), c.c_void_p)
    Write = c.CFUNCTYPE(c.c_int, U, c.c_uint, U, c.c_void_p)
    n.vertrix_notice_call_full.argtypes = [c.POINTER(Calls), U, U, Read, Write, c.c_void_p]
    n.vertrix_notice_call_full.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x416010)
    frame = STACK - 4
    addresses = (0x532bf8, 0x4f8160, 0x532c40,
                 frame - 0x20, frame - 0x1c, frame - 0x18)
    host, initial = {}, {}
    native_log, events, native_events, errors = [], [], [], []
    tokens = []
    probe = 0

    def track_read(cpu, access, address, width, value, context):
        events.append(('read', address, width, int.from_bytes(cpu.mem_read(address, width), 'little')))

    def track_write(cpu, access, address, width, value, context):
        events.append(('write', address, width, value & 0xffffffff))

    for address in addresses[:3]:
        cpu.hook_add(UC_HOOK_MEM_READ, track_read, begin=address, end=address + 3)
        cpu.hook_add(UC_HOOK_MEM_WRITE, track_write, begin=address, end=address + 3)

    def mutations(address, eax, index):
        writes = [(0x532bf8, tokens[index] ^ 0x11111111),
                  (0x4f8160, tokens[index] ^ 0x22222222),
                  (0x532c40, tokens[index])]
        if address == 0x4ca280:
            writes.append((eax, tokens[index]))
        elif address == 0x4ca210:
            writes.append((eax, 0))
        return writes

    def handler(address, eax, edx, ebx, ecx, stack):
        index = len(stubs.log) - 1
        events.append(('call', address, eax, edx, ebx, ecx))
        for at, value in mutations(address, eax, index):
            cpu.mem_write(at, struct.pack('<I', value))
        return probe if address == 0x47f9b0 else tokens[index]

    stubs = Stubs(cpu, handler)
    for address in CALLEES:
        stubs.add(address)

    @Call
    def call(site, context):
        x = site.contents
        index = len(native_log)
        entry = (x.target, x.eax, x.edx, x.ebx, x.ecx)
        native_log.append(entry)
        native_events.append(('call', *entry))
        if index >= len(tokens):
            errors.append(('extra_call', index))
            return 0
        if x.target in (0x4ca280, 0x4ca210) and x.eax not in addresses[3:]:
            errors.append(('local_handle', x.eax))
            return 0
        for at, value in mutations(x.target, x.eax, index):
            host[at] = value
        return probe if x.target == 0x47f9b0 else tokens[index]

    @Read
    def read(address, width, value, context):
        if address not in addresses[:3] or width != 4:
            errors.append(('read', address, width))
            return 0
        value[0] = host[address]
        native_events.append(('read', address, width, value[0]))
        return 1

    @Write
    def write(address, width, value, context):
        if address != 0x532c40 or width != 4:
            errors.append(('write', address, width))
            return 0
        host[address] = value
        native_events.append(('write', address, width, value))
        return 1

    calls = Calls(call, None)
    branches = {'mismatch': 0, 'single_text': 0, 'two_texts': 0}
    count = register_comparisons = mutation_cases = 0
    for case in range(args.cases):
        initial = {address: rng.getrandbits(32) for address in addresses}
        branch = case % 3
        if branch:
            initial[0x4f8160] = initial[0x532bf8]
        else:
            initial[0x4f8160] = initial[0x532bf8] ^ 0xffffffff
        host = dict(initial)
        for address, value in initial.items():
            cpu.mem_write(address, struct.pack('<I', value))
        previous = (0, 0xffffffff)[case] if case < 2 else rng.getrandbits(32)
        cpu.mem_write(0, struct.pack('<I', previous))
        probe = 1 if branch == 1 else (0, 0xffffffff, 0x80000001)[(case // 3) % 3]
        tokens = [rng.getrandbits(32) for _ in range(7)]
        events.clear()
        native_events.clear()
        native_log.clear()
        stubs.log.clear()
        errors.clear()
        eax, edx, ebx, ecx = (rng.getrandbits(32) for _ in range(4))
        expected = original.call(0x416010, eax=eax, edx=edx, ebx=ebx, ecx=ecx)
        got = n.vertrix_notice_call_full(c.byref(calls), frame, previous, read, write, None)
        assert not errors, (case, errors)
        assert expected == got == previous, (case, expected, got, previous)
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert native_events == events, (case, native_events, events)
        assert all(host[at] == int.from_bytes(cpu.mem_read(at, 4), 'little') for at in addresses), case
        assert int.from_bytes(cpu.mem_read(0, 4), 'little') == previous, case
        assert [cpu.reg_read(reg) for reg in (UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX)] == [edx, ebx, ecx], case
        count += 1
        register_comparisons += len(native_log)
        mutation_cases += bool(native_log)
        branches[('mismatch', 'single_text', 'two_texts')[branch]] += 1
    assert count == args.cases and sum(branches.values()) == count
    assert all(branches.values())
    missing = [(None, read, write), (c.byref(Calls(Call(), None)), read, write),
               (c.byref(calls), Read(), write), (c.byref(calls), read, Write())]
    for runtime, reader, writer in missing:
        before = dict(host)
        native_log.clear()
        assert n.vertrix_notice_call_full(runtime, frame, 0x12345678, reader, writer, None) == 0
        assert not native_log and host == before
    report = {'status': 'passed', 'complete_original_executions': {'0x416010': count},
              'branch_counts': branches, 'exact_callback_register_comparisons': register_comparisons,
              'callback_global_and_local_mutation_cases': mutation_cases,
              'native_missing_boundary_rejections': len(missing),
              'scope': 'Full normal return equals saved exception-chain token; independent global '
                       'and text-local storage, ordered raw global reads/writes and all callback '
                       'registers compare. Every callback mutates globals; assign/release mutate '
                       'local text storage. Original exception chain and caller registers restore. '
                       'Exception-stack bookkeeping and unwinding remain outside the runtime boundary.'}
    (args.build_dir / 'notice-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
