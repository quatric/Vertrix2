"""Compare the original tracker module loader 0x40f360 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import POOL, Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x2000
COUNT = 70
SCRATCH = 0x531b8c
SCRATCH_SIZE = 0x460
TABLE = 0x4f7594
TABLE_SIZE = 0xa0
CALLEES = {0x40c1c0: 0, 0x40c1f0: 0, 0x4ec160: 0, 0x40c1e0: 0, 0x40c220: 0, 0x40c360: 0,
           0x40c320: 0, 0x40ef90: 0, 0x40f1a0: 0, 0x40ac50: 0, 0x40acd0: 0, 0x4ec180: 0, 0x4eb5e0: 0}


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next',
                                       'stack_third', 'out_ebx', 'out_ecx')] + [
        ('rest%d' % i, U) for i in range(14)] + [('out_value', U)]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


def text(rng, size):
    length = rng.randrange(0, size + 1)
    return bytes(rng.randrange(0x20, 0x7f) for _ in range(length)) + bytes(size - length)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=1024)
    args = parser.parse_args()
    n = build(args.build_dir, 'module-load', ['module_load.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_module_load.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U, U,
                                      c.POINTER(U)]
    n.vertrix_module_load.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(0x810000, 0x83000)
    rng = random.Random(0x40f360)
    pool = Pool(cpu, COUNT, SIZE)
    scratch = c.create_string_buffer(SCRATCH_SIZE)
    table = c.create_string_buffer(bytes(cpu.mem_read(TABLE, TABLE_SIZE)), TABLE_SIZE)
    handles = pool.handles
    module, patterns, samples, out = handles[0], handles[1], handles[2], handles[65]
    sounds, buffers = handles[3:34], handles[34:65]

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == SCRATCH:
            storage[0], size[0] = c.addressof(scratch), SCRATCH_SIZE
            return 1
        if handle == TABLE:
            storage[0], size[0] = c.addressof(table), TABLE_SIZE
            return 1
        if handle in pool.buffers:
            storage[0] = c.addressof(pool.buffers[handle])
            size[0] = SIZE
            return 1
        return 0

    services = Services(resolve)
    returns, fills, native_log, replay = [], [], [], []
    free_sounds, free_buffers = [], []

    def sample_field(address):
        offset = address - (SCRATCH + 0x14)
        return divmod(offset, 30) if 0 <= offset < 30 * 31 else None

    def data_for(address, count):
        if address == SCRATCH:
            return text(rng, count)
        found = sample_field(address)
        if found:
            _, field = found
            length = rng.choice([0, 0, 1, 2, 100, 0x400, rng.randrange(0, 0x800)])
            if field == 0:
                return text(rng, count)
            if field == 0x16:
                value = length
            elif field == 0x18:
                value = rng.getrandbits(8)
            elif field == 0x19:
                value = rng.choice([0, 0x20, 0x40, 0x41, 0x60, rng.getrandbits(8)])
            elif field == 0x1a:
                value = rng.choice([0, 1, 50, 0x500, rng.randrange(0, 0x800)])
            else:
                value = rng.choice([0, 1, 2, 0x200, rng.randrange(0, 0x800)])
            return struct.pack('<I', value)[:count]
        if address == SCRATCH + 0x3b6 or address == SCRATCH + 0x3b7:
            return bytes([rng.getrandbits(8)])
        if address == SCRATCH + 0x3b8:
            return bytes(rng.randrange(0, 0x11) if rng.random() < 0.95 else rng.randrange(0, 0x80)
                         for _ in range(count))
        if address == SCRATCH + 0x438:
            if rng.random() < 0.8:
                entry = rng.randrange(0, 20)
                return bytes(table.raw[8 * entry:8 * entry + 4])
            return rng.randbytes(4)
        return rng.randbytes(count)

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x40c220:
            data = data_for(eax, edx)
            cpu.mem_write(eax, data)
            fills.append((eax, data))
            returns.append(0)
        elif address in (0x40c360, 0x40c320):
            data = data_for(eax, 2 if address == 0x40c360 else 1)
            cpu.mem_write(eax, data)
            fills.append((eax, data))
            returns.append(0)
        elif address == 0x4ec180:
            same = bytes(cpu.mem_read(eax, ebx)) == bytes(cpu.mem_read(edx, ebx))
            returns.append(0 if same else 1)
        elif address == 0x4eb5e0:
            data = bytes(cpu.mem_read(edx, ebx))
            cpu.mem_write(eax, data)
            fills.append((eax, data))
            returns.append(eax)
        elif address == 0x40c1c0:
            returns.append(0 if rng.random() < 0.97 else rng.randrange(1, 0x100))
        elif address == 0x4ec160:
            if rng.random() < 0.006:
                returns.append(0)
            elif edx == 0x158:
                returns.append(module)
            elif edx == 0xc:
                returns.append(patterns)
            elif edx == 0xfc:
                returns.append(samples)
            else:
                returns.append(free_sounds.pop(0))
        elif address == 0x40ac50:
            handle = free_buffers.pop(0)
            cpu.mem_write(eax, struct.pack('<I', handle))
            fills.append((eax, struct.pack('<I', handle)))
            returns.append(0 if rng.random() < 0.997 else rng.randrange(1, 0x100))
        elif address == 0x40f1a0:
            returns.append(0 if rng.random() < 0.999 else rng.randrange(1, 0x100))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    def mirror(address, data):
        if SCRATCH <= address < SCRATCH + SCRATCH_SIZE:
            c.memmove(c.addressof(scratch) + address - SCRATCH, data, len(data))
            return
        for handle in handles:
            if handle <= address < handle + SIZE:
                c.memmove(c.addressof(pool.buffers[handle]) + address - handle, data, len(data))
                return
        raise AssertionError(hex(address))

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        if s.target in (0x40c220, 0x40c360, 0x40c320, 0x40ac50, 0x4eb5e0):
            mirror(*fills.pop(0))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}

    def patch(handle, data):
        if handle == module:
            struct.pack_into('<H', data, 0x26, 0 if rng.random() < 0.5 else rng.randrange(1, 9))
            struct.pack_into('<H', data, 0x28, rng.randrange(0, 4))

    for case in range(args.cases):
        pool.fill(rng, patch)
        blob = rng.randbytes(SCRATCH_SIZE)
        scratch.raw = blob
        cpu.mem_write(SCRATCH, blob)
        stubs.log.clear()
        returns.clear()
        fills.clear()
        native_log.clear()
        free_sounds[:] = list(sounds)
        free_buffers[:] = list(buffers)
        eax, stream, ecx = (rng.getrandbits(32) for _ in range(3))
        try:
            want = original.call(0x40f360, eax=eax, edx=out, ebx=stream, ecx=ecx) & 0xffffffff
        except Exception:
            from unicorn.x86_const import UC_X86_REG_EIP, UC_X86_REG_ESI, UC_X86_REG_EDI
            print('fault at', hex(cpu.reg_read(UC_X86_REG_EIP)), 'esi', hex(cpu.reg_read(UC_X86_REG_ESI)),
                  'edi', hex(cpu.reg_read(UC_X86_REG_EDI)), 'case', case)
            print([tuple(hex(v) for v in entry) for entry in stubs.log[-4:]])
            raise
        replay[:] = list(returns)
        free_sounds[:] = list(sounds)
        free_buffers[:] = list(buffers)
        result = U()
        assert n.vertrix_module_load(c.byref(calls), c.byref(services), eax, stream, out, ecx,
                                     c.byref(result)), case
        assert result.value == want, (case, result.value, want)
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log),
                                         [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2])
        assert not replay and pool.same(), (case, pool.diff())
        assert scratch.raw == bytes(cpu.mem_read(SCRATCH, SCRATCH_SIZE)), case
        key = {0: 'loaded', 0xa: 'open failed', 8: 'no memory', 0xb: 'unknown signature'}.get(
            want, 'callee error')
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x40f360': totals},
              'scope': 'The routine executes completely in the original with the file reads, the '
                       'allocation, the release, the pattern packer and the sound buffer calls '
                       'stubbed and logged (the file data, the allocated objects and the buffer '
                       'pointers and the header copy mirrored for the native; 0x4eb860 runs '
                       'unstubbed); every call with its registers, the returned code, '
                       'the objects and the scratch compare.'}
    (args.build_dir / 'module-load-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
