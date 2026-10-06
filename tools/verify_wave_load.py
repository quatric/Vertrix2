"""Compare the original wave loader 0x4b7e80 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x200
STATE = 0x5bd850
STATE_SIZE = 0x28
TOTAL = 0x598dac
RIFF, WAVE, FMT, DATA = 0x46464952, 0x45564157, 0x20746d66, 0x61746164
CALLEES = {0x4ec160: 0, 0x48a930: 0, 0x48aa90: 0, 0x4b8170: 0, 0x40ac50: 0, 0x40acd0: 0}


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
    parser.add_argument('--cases', type=int, default=2048)
    args = parser.parse_args()
    n = build(args.build_dir, 'wave-load', ['wave_load.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_wave_load.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U, U, c.POINTER(U)]
    n.vertrix_wave_load.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4b7e80)
    pool = Pool(cpu, 3, SIZE)
    obj, buffer, out = pool.handles
    state = c.create_string_buffer(STATE_SIZE)
    total = c.create_string_buffer(4)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == STATE:
            storage[0], size[0] = c.addressof(state), STATE_SIZE
            return 1
        if handle == TOTAL:
            storage[0], size[0] = c.addressof(total), 4
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, fills, native_log, replay = [], [], [], []

    def header(address, count):
        pick = rng.random()
        if address == STATE:
            value = RIFF if pick < 0.9 else rng.getrandbits(32)
        elif address == STATE + 4:
            value = rng.choice([0, 1, 2, 4, 5, 6, 20, 60, 100, 200, rng.randrange(0, 0x180)])
        elif address == STATE + 8:
            value = WAVE if pick < 0.9 else rng.getrandbits(32)
        elif address == STATE + 0x10:
            value = FMT if pick < 0.4 else DATA if pick < 0.75 else rng.getrandbits(32)
        elif address == STATE + 0x14:
            value = rng.randrange(0, 0x100)
        elif address == STATE + 0x18:
            value = 1 if pick < 0.8 else rng.getrandbits(16)
        elif address == STATE + 0x1a:
            value = rng.choice([1, 2, rng.getrandbits(16)])
        elif address == STATE + 0x26:
            value = rng.choice([8, 16, rng.getrandbits(16)])
        else:
            value = rng.getrandbits(8 * count)
        return struct.pack('<I', value)[:count]

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x48a930:
            if STATE <= edx < STATE + STATE_SIZE:
                data = header(edx, ecx)
            else:
                data = rng.randbytes(ecx)
            cpu.mem_write(edx, data)
            fills.append((edx, data))
            returns.append(rng.getrandbits(32))
        elif address == 0x4ec160:
            returns.append(obj if rng.random() < 0.9 else 0)
        elif address == 0x40ac50:
            cpu.mem_write(eax, struct.pack('<I', buffer))
            fills.append((eax, struct.pack('<I', buffer)))
            returns.append(0 if rng.random() < 0.7 else rng.randrange(1, 0x100))
        else:
            returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    def mirror(address, data):
        if STATE <= address < STATE + STATE_SIZE:
            c.memmove(c.addressof(state) + address - STATE, data, len(data))
        else:
            for handle in pool.handles:
                if handle <= address < handle + SIZE:
                    c.memmove(c.addressof(pool.buffers[handle]) + address - handle, data, len(data))

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx))
        if s.target in (0x48a930, 0x40ac50):
            mirror(*fills.pop(0))
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        blob = rng.randbytes(STATE_SIZE)
        state.raw = blob
        cpu.mem_write(STATE, blob)
        word = rng.randbytes(4)
        total.raw = word
        cpu.mem_write(TOTAL, word)
        stubs.log.clear()
        returns.clear()
        fills.clear()
        native_log.clear()
        stream, ebx, ecx = (rng.getrandbits(32) for _ in range(3))
        pointer = out if rng.random() < 0.95 else 0
        want = original.call(0x4b7e80, eax=stream, edx=pointer, ebx=ebx, ecx=ecx) & 0xffffffff
        replay[:] = list(returns)
        result = U()
        assert n.vertrix_wave_load(c.byref(calls), c.byref(services), stream, pointer, ebx, ecx,
                                   c.byref(result)), case
        assert result.value == want, (case, result.value, want)
        assert native_log == stubs.log, (case, len(native_log), len(stubs.log),
                                         [(i, a, b) for i, (a, b) in enumerate(zip(native_log, stubs.log)) if a != b][:2])
        assert not replay and pool.same(), (case, pool.diff())
        assert state.raw == bytes(cpu.mem_read(STATE, STATE_SIZE)), case
        assert total.raw == bytes(cpu.mem_read(TOTAL, 4)), case
        key = {0: 'loaded', 2: 'no pointer', 8: 'no memory', 0xb: 'rejected'}.get(want, 'buffer failure')
        totals[key] = totals.get(key, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4b7e80': totals},
              'scope': 'The routine executes completely in the original with the stream reads, the '
                       'allocation, the buffer calls and the release stubbed and logged (the '
                       'chunk reads and the buffer pointer mirrored for the native); every call '
                       'with its registers, the returned code, the chunk scratch, the sound total '
                       'and the objects and sample buffer compare.'}
    (args.build_dir / 'wave-load-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
