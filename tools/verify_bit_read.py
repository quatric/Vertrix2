"""Compare the original one-bit read 0x4046e0 with the address-space port."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import Resolve, build

U = c.c_uint32
GLOBALS = 0x51f000
GLOBALS_SIZE = 0x1000
DATA = 0x900000
DATA_SIZE = 0x2000
POINTER = 0x51f014
INDEX = 0x51f018


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)
GlobalRead = c.CFUNCTYPE(U, U, c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Globals(c.Structure):
    _fields_ = [('read', GlobalRead), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


class Memory(c.Structure):
    _fields_ = [('calls', c.POINTER(Calls)), ('services', c.POINTER(Services)),
                ('globals', c.POINTER(Globals)), ('ok', c.c_int)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'bit-read', ['native_ports.c', 'native_memory.c', 'call_glue.c',
                                           'actor_storage.c'])
    n.vertrix_port_bit_read.argtypes = [c.POINTER(Memory)]
    n.vertrix_port_bit_read.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(DATA, DATA_SIZE)
    rng = random.Random(0x4046e0)
    regions = {GLOBALS: c.create_string_buffer(GLOBALS_SIZE), DATA: c.create_string_buffer(DATA_SIZE)}
    sizes = {GLOBALS: GLOBALS_SIZE, DATA: DATA_SIZE}
    data_object = [True]

    def locate(address):
        for base, size in sizes.items():
            if base <= address < base + size:
                return base
        raise AssertionError(hex(address))

    @Resolve
    def resolve(address, storage, size, context):
        if data_object[0] and DATA <= address < DATA + DATA_SIZE:
            storage[0] = c.addressof(regions[DATA]) + address - DATA
            size[0] = DATA + DATA_SIZE - address
            return 1
        return 0

    @GlobalRead
    def read(address, context):
        base = locate(address)
        raw = regions[base].raw[address - base:address - base + 4]
        return int.from_bytes(raw.ljust(4, b'\0'), 'little')

    log = []

    @Call
    def call(site, context):
        s = site.contents
        assert s.target == 0xf0000000, hex(s.target)
        base = locate(s.eax)
        c.memmove(c.addressof(regions[base]) + s.eax - base, s.edx.to_bytes(4, 'little'), s.stack)
        log.append(s.eax)
        return 0

    calls = Calls(call, None)
    services = Services(resolve)
    globals_ = Globals(read, None)
    totals = {}
    for case in range(args.cases):
        for base, size in sizes.items():
            blob = rng.randbytes(size)
            cpu.mem_write(base, blob)
            c.memmove(regions[base], blob, size)
        data_object[0] = rng.random() < 0.7
        index = rng.choice([rng.randrange(8), rng.randrange(8), rng.randrange(40),
                            (-rng.randrange(1, 0x2000)) & 0xffffffff, rng.randrange(0x100, 0x2000),
                            0x7fffffff, 0xffffffff])
        delta = (index + 1) & 0xffffffff
        step = (delta - (1 << 32) if delta & 0x80000000 else delta) >> 3
        low = max(DATA, DATA - step)
        high = min(DATA + DATA_SIZE, DATA + DATA_SIZE - step)
        if low >= high:
            low, high = DATA, DATA + DATA_SIZE
        pointer = rng.randrange(low, high)
        for address, value in ((POINTER, pointer), (INDEX, index)):
            raw = value.to_bytes(4, 'little')
            cpu.mem_write(address, raw)
            c.memmove(c.addressof(regions[GLOBALS]) + address - GLOBALS, raw, 4)
        want = original.call(0x4046e0) & 0xffffffff
        memory = Memory(c.pointer(calls), c.pointer(services), c.pointer(globals_), 1)
        log.clear()
        got = n.vertrix_port_bit_read(c.byref(memory))
        assert memory.ok and got == want, (case, got, want)
        assert log == [INDEX, POINTER, INDEX], log
        for base, size in sizes.items():
            assert regions[base].raw == bytes(cpu.mem_read(base, size)), (case, hex(base))
        key = '%s byte, index %s' % ('object' if data_object[0] else 'global',
                                     'below 8' if index < 8 else 'large')
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4046e0': totals},
              'scope': 'Complete original 0x4046e0 executions against the address-space port: '
                       'bit indexes below 8, shift counts of 8 to 31 and wider (the eight bit '
                       'shift leaves zero), negative and huge indexes moving the pointer back or '
                       'forward; the byte is read from an object or from globals. The result, '
                       'the order of the three global stores and both memory regions compare.'}
    (args.build_dir / 'bit-read-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
