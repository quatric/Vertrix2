"""Compare the original slot kind snapshot 0x4327e0 with the address-space port."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from unicorn import UcError

from original import Original
from oracle_kit import Resolve, build

U = c.c_uint32
BASE = 0x900000
SIZE = 0x20000
OBJECTS = 0x910000
OBJECT_SIZE = 0x200


class Calls(c.Structure):
    _fields_ = [('call', c.c_void_p), ('context', c.c_void_p)]


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)
GlobalRead = c.CFUNCTYPE(U, U, c.c_void_p)


class Globals(c.Structure):
    _fields_ = [('read', GlobalRead), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


class Memory(c.Structure):
    _fields_ = [('calls', c.c_void_p), ('services', c.c_void_p), ('globals', c.c_void_p),
                ('ok', c.c_int)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'kind-snapshot', ['native_ports.c', 'native_memory.c', 'call_glue.c',
                                                'actor_storage.c'])
    n.vertrix_port_kind_snapshot.argtypes = [c.POINTER(Memory), U, U, U]
    n.vertrix_port_kind_snapshot.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(BASE, SIZE)
    # The oracle maps page zero for constructors' exception chains; this routine has none, and a
    # slot pointer overwritten by an overlapping kind store must fault as it does on Windows.
    cpu.mem_unmap(0, 0x1000)
    rng = random.Random(0x4327e0)
    image = c.create_string_buffer(SIZE)
    hidden = [None]  # (lo, hi): the range served as globals instead of an object

    @Resolve
    def resolve(address, storage, size, context):
        if not BASE <= address < BASE + SIZE:
            return 0
        if hidden[0] and hidden[0][0] <= address < hidden[0][1]:
            return 0
        storage[0] = c.addressof(image) + address - BASE
        size[0] = BASE + SIZE - address
        if hidden[0] and address < hidden[0][0]:
            size[0] = hidden[0][0] - address
        return 1

    @GlobalRead
    def read(address, context):
        assert BASE <= address and address + 4 <= BASE + SIZE, hex(address)
        return int.from_bytes(image.raw[address - BASE:address - BASE + 4], 'little')

    stores = [0]

    @Call
    def call(site, context):
        s = site.contents
        assert s.target == 0xf0000000, hex(s.target)
        c.memmove(c.addressof(image) + s.eax - BASE, s.edx.to_bytes(4, 'little'), s.stack)
        stores[0] += 1
        return 0

    calls = Calls(c.cast(call, c.c_void_p), None)
    services = Services(resolve)
    globals_ = Globals(read, None)
    totals = {}
    faults = 0
    case = 0
    while case < args.cases:
        objects = [OBJECTS + OBJECT_SIZE * i for i in range(16)]
        blob = bytearray(rng.randbytes(SIZE))
        count = rng.choice([0, 1, 2, 13, 65, 65, rng.randrange(1, 300), 0x40000000, 0xffffffff,
                            0xc0000000, rng.getrandbits(32)])
        slots = BASE + 4 * rng.randrange(0x400) + rng.choice([0, 0, 0, 1, 2, 3])
        if rng.random() < 0.15:
            kinds = slots + rng.randrange(-8, 9)
        else:
            kinds = BASE + 0x2000 + rng.randrange(0x1000)
        for i in range(min(count, 600)):
            at = slots - BASE + 4 * i
            if at + 4 <= 0x10000:
                value = rng.choice([0, 0] + objects)
                blob[at:at + 4] = value.to_bytes(4, 'little')
        cpu.mem_write(BASE, bytes(blob))
        c.memmove(image, bytes(blob), SIZE)
        mode = rng.choice(['objects', 'globals', 'globals'])
        hidden[0] = None
        if mode == 'globals':
            hidden[0] = rng.choice([(kinds, kinds + 0x400), (slots, slots + 0x2000),
                                    (OBJECTS, OBJECTS + 0x2000)])
        try:
            want = original.call(0x4327e0, eax=slots, edx=kinds, ebx=count) & 0xffffffff
        except UcError:
            faults += 1  # the original faults too (an overwritten slot pointer); not a case
            continue
        memory = Memory(c.cast(c.pointer(calls), c.c_void_p).value,
                        c.cast(c.pointer(services), c.c_void_p).value,
                        c.cast(c.pointer(globals_), c.c_void_p).value if mode == 'globals' else None,
                        1)
        got = n.vertrix_port_kind_snapshot(c.byref(memory), slots, kinds, count)
        assert memory.ok, case
        assert got == want, (case, hex(got), hex(want))
        assert image.raw == bytes(cpu.mem_read(BASE, SIZE)), (case, mode, hex(count))
        key = '%s, %s' % (mode, 'zero' if count == 0 else 'overlap' if abs(kinds - slots) < 9
                          else 'wrap' if count >= 0x40000000 else 'count')
        totals[key] = totals.get(key, 0) + 1
        case += 1
    assert stores[0], 'the globals path stored nothing'
    report = {'status': 'passed', 'complete_original_executions': {'0x4327e0': totals},
              'skipped_original_faults': faults,
              'scope': 'Complete original 0x4327e0 executions against the address-space port: '
                       'zero, ordinary, wrapping and huge counts, unaligned and overlapping slot '
                       'and kind arrays, empty and occupied slots; two thirds of the cases serve '
                       'the kinds, the slots or the objects as globals (read through the globals '
                       'reader, stored through the 0xf0000000 pseudo call). The returned eax and '
                       'the whole 0x20000 byte memory compare. Cases where the original itself '
                       'faults on an overwritten slot pointer are skipped and counted.'}
    (args.build_dir / 'kind-snapshot-verification.json').write_text(json.dumps(report, indent=2)
                                                                     + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
