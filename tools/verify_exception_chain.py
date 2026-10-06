"""Compare the original exception chain step 0x4da6b6 with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original, STACK
from oracle_kit import Resolve, Stubs, build

U = c.c_uint32
REGION = STACK - 0x28
REGION_SIZE = 0x1c
RECORD = 0x800100
RECORD_SIZE = 0x10
DESCRIPTOR = 0x800200
DESCRIPTOR_SIZE = 8
CALLEES = (0x4e0f8b, 0x4e0a95, 0x4e0eaf, 0x4e0ec7, 0x4e0b7c, 0x4e0b9e)


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'exception-chain',
              ['exception_chain.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_exception_chain_step.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U, U,
                                               U, c.POINTER(U)]
    n.vertrix_exception_chain_step.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4da6b6)
    frame = c.create_string_buffer(REGION_SIZE)
    head = c.create_string_buffer(4)
    record = c.create_string_buffer(RECORD_SIZE)
    descriptor = c.create_string_buffer(DESCRIPTOR_SIZE)
    regions = {REGION: (frame, REGION_SIZE), 0: (head, 4), RECORD: (record, RECORD_SIZE),
               DESCRIPTOR: (descriptor, DESCRIPTOR_SIZE)}

    @Resolve
    def resolve(handle, storage, size, context):
        if handle in regions:
            buffer, length = regions[handle]
            storage[0], size[0] = c.addressof(buffer), length
            return 1
        return 0

    services = Services(resolve)
    returns, fills, native_log, replay = [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        value = DESCRIPTOR if address == 0x4e0a95 else rng.getrandbits(32)
        if address in (0x4e0b7c, 0x4e0b9e):
            data = rng.randbytes(8)
            cpu.mem_write(REGION, data)
            fills.append(data)
        returns.append(value)
        return value

    stubs = Stubs(cpu, handler)
    for address in CALLEES:
        stubs.add(address, 0)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        if s.target in (0x4e0b7c, 0x4e0b9e):
            c.memmove(c.addressof(frame), fills.pop(0), 8)
        return replay.pop(0)

    calls = Calls(call, None)
    for case in range(args.cases):
        blob = rng.randbytes(REGION_SIZE)
        frame.raw = blob
        cpu.mem_write(REGION, blob)
        rec = rng.randbytes(RECORD_SIZE)
        record.raw = rec
        cpu.mem_write(RECORD, rec)
        desc = rng.randbytes(DESCRIPTOR_SIZE)
        descriptor.raw = desc
        cpu.mem_write(DESCRIPTOR, desc)
        head.raw = RECORD.to_bytes(4, 'little')
        cpu.mem_write(0, head.raw)
        stubs.log.clear()
        returns.clear()
        fills.clear()
        native_log.clear()
        eax, edx, ebx, ecx = (rng.getrandbits(32) for _ in range(4))
        want = original.call(0x4da6b6, eax=eax, edx=edx, ebx=ebx, ecx=ecx) & 0xffffffff
        replay[:] = list(returns)
        result = U()
        assert n.vertrix_exception_chain_step(c.byref(calls), c.byref(services), STACK, eax, edx,
                                              ebx, ecx, c.byref(result)), case
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert result.value == want, (case, hex(result.value), hex(want))
        assert not replay, case
        assert frame.raw == bytes(cpu.mem_read(REGION, REGION_SIZE)), case
        assert record.raw == bytes(cpu.mem_read(RECORD, RECORD_SIZE)), case
    report = {'status': 'passed',
              'complete_original_executions': {'0x4da6b6': {'6': args.cases}},
              'scope': 'The routine executes completely in the original over the chain head at '
                       'fs:[0], a record and a descriptor, with its six callees stubbed and '
                       'logged; every call with its registers, the result, the stack locals and '
                       'the record compare.'}
    (args.build_dir / 'exception-chain-verification.json').write_text(
        json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
