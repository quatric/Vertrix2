"""Compare the original S3M pattern converter 0x410270 with the native recovery."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path

from original import Original
from oracle_kit import Resolve, Stubs, build

U = c.c_uint32
ROW = 0x53207c
ROW_SIZE = 0x500
RECORD = 0x900000
SOURCE = 0x901000
MAP = 0x908000
OUTPUT = 0x910000
OUTPUT_SIZE = 0x10000
REGIONS = {ROW: ROW_SIZE, RECORD: 0x100, SOURCE: 0x7000, MAP: 0x100, OUTPUT: OUTPUT_SIZE}


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(8)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


GlobalRead = c.CFUNCTYPE(U, U, c.c_void_p)


class Globals(c.Structure):
    _fields_ = [('read', GlobalRead), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def pattern(rng, channels):
    """A packed S3M pattern: 64 rows of events, each row ended by a zero byte."""
    data = bytearray()
    for _ in range(64):
        for _ in range(rng.choice([0, 0, 1, 2, 4, 8])):
            flag = rng.randrange(1, 0x100)
            if flag & 0x1f == 0 and flag & 0xe0 == 0:
                flag = 1
            data.append(flag)
            if flag & 0x20:
                data.append(rng.choice([0xfe, 0xff, rng.randrange(0x100),
                                        rng.randrange(8) << 4 | rng.randrange(12)]))
                data.append(rng.randrange(0x100))
            if flag & 0x40:
                data.append(rng.choice([rng.randrange(0x41), rng.randrange(0x100), 0xff]))
            if flag & 0x80:
                command = rng.choice([rng.randrange(1, 27), rng.randrange(1, 27),
                                      rng.randrange(0x100)])
                parameter = rng.choice([0, 0, rng.randrange(0x100), rng.randrange(16) << 4,
                                        rng.randrange(16), 0xf0 | rng.randrange(16),
                                        rng.randrange(16) << 4 | 0xf, 0xe0 | rng.randrange(16),
                                        0x80, 0x7f, 0x81, 0x1f, 0x20])
                data += bytes([command, parameter])
        data.append(0)
    return bytes(data)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 's3m-pattern', ['s3m_pattern.c', 'native_memory.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_s3m_pattern.argtypes = [c.POINTER(Calls), c.POINTER(Services), c.POINTER(Globals),
                                      U, U, U, U, U, c.POINTER(U)]
    n.vertrix_s3m_pattern.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(RECORD, 0x20000)
    rng = random.Random(0x410270)
    buffers = {}
    # In the global mode the row buffer and the map are not objects: they are read through the
    # globals reader and stored through the 0xf0000000 pseudo call, as on the lifted host.
    hidden = set()

    def locate(address):
        for base, size in REGIONS.items():
            if base <= address < base + size:
                return base
        raise AssertionError('unmapped global %x' % address)

    @GlobalRead
    def read(address, context):
        base = locate(address)
        raw = buffers[base].raw
        offset = address - base
        return int.from_bytes(raw[offset:offset + 4].ljust(4, b'\0'), 'little')

    globals_ = Globals(read, None)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle not in buffers or handle in hidden:
            return 0
        storage[0], size[0] = c.addressof(buffers[handle]), REGIONS[handle]
        return 1

    services = Services(resolve)
    returns, native_log, replay = [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4e7c90:
            returns.append(0 if rng.random() < 0.05 else OUTPUT)
        else:
            returns.append(rng.choice([0, OUTPUT, rng.getrandbits(32)]))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address in (0x4e7c90, 0x4ec0e0):
        stubs.add(address, 0)

    @Call
    def call(site, context):
        s = site.contents
        if s.target == 0xf0000000:
            base = locate(s.eax)
            c.memmove(c.addressof(buffers[base]) + s.eax - base,
                      (s.edx & 0xffffffff).to_bytes(4, 'little'), s.stack)
            stores[0] += 1
            return 0
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}
    stores = [0]
    for case in range(args.cases):
        channels = rng.choice([0, 1, 2, 4, 8, 8, 16, 16, 32, 33, 40])
        data = pattern(rng, channels)
        if rng.random() < 0.2:
            data = data[:rng.randrange(len(data) + 1)]
        length = len(data)
        image = {address: bytearray(rng.randbytes(size)) for address, size in REGIONS.items()}
        image[SOURCE][:length] = data
        image[MAP][:32] = rng.choice([
            bytes(range(32)),
            bytes(rng.randrange(channels + 4) for _ in range(32)),
            bytes(rng.choice([rng.randrange(max(channels, 1)), 0xff]) for _ in range(32))])
        for address, blob in image.items():
            cpu.mem_write(address, bytes(blob))
            buffers[address] = c.create_string_buffer(bytes(blob), REGIONS[address])
        stubs.log.clear()
        returns.clear()
        native_log.clear()
        want = original.call(0x410270, eax=channels, edx=SOURCE, ebx=length, ecx=MAP,
                             args=(RECORD,)) & 0xffffffff
        replay[:] = list(returns)
        result = U()
        hidden.clear()
        if case % 2:
            hidden.update((ROW, MAP))
        assert n.vertrix_s3m_pattern(c.byref(calls), c.byref(services),
                                     c.byref(globals_) if case % 2 else None, channels, SOURCE,
                                     length, MAP, RECORD, c.byref(result)), case
        assert result.value == want, (case, result.value, want)
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay, case
        for address, size in REGIONS.items():
            assert buffers[address].raw == bytes(cpu.mem_read(address, size)), (case, hex(address))
        key = '%d channels, %s' % (channels, 'globals' if case % 2 else 'objects')
        totals[key] = totals.get(key, 0) + 1
    assert stores[0], 'the globals path stored nothing'
    report = {'status': 'passed', 'complete_original_executions': {'0x410270': totals},
              'scope': 'The routine executes completely in the original (0x4eb5c0 and 0x4ec1d0 '
                       'run unchanged) with 0x4e7c90 and 0x4ec0e0 stubbed and logged; generated '
                       'S3M patterns cover every command letter and parameter form, key off, '
                       'empty and invalid notes, out-of-range volumes, truncated data, remapped '
                       'and skipped channels, more than 32 channels and allocation failures. Odd '
                       'cases reach the row buffer and map through the globals reader and the '
                       '0xf0000000 store pseudo call (the lifted host path). '
                       'Every call with its registers, the returned eax, the record, the packed '
                       'output, the row buffer with the parameter memory and the inputs compare.'}
    (args.build_dir / 's3m-pattern-verification.json').write_text(json.dumps(report, indent=2)
                                                                   + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
