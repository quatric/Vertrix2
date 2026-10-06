"""Compare the original control message dispatcher 0x4d2020 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original, STACK
from oracle_kit import Pool, Resolve, Stubs, build

U = c.c_uint32
SIZE = 0x200
FRAME = 0x1c
FRAME_SIZE = 0x14
CALLEES = {0x4d0c84: 1, 0x4cb820: 1}
MESSAGES = (list(range(0x28, 0x32)) + [0x38, 0x39, 0x3a, 0x4d, 0x4e, 0x4f, 0x110, 0x111, 0x112,
            0x113, 0x114, 0x115, 0x116, 0x131, 0x132, 0x133, 0x134, 0x135, 0x136, 0x137, 0x138,
            0x139, 0x20f, 0x210, 0x211, 0, 1])


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


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    n = build(args.build_dir, 'message-dispatch',
              ['message_dispatch.c', 'call_glue.c', 'actor_storage.c'])
    n.vertrix_message_dispatch.argtypes = [c.POINTER(Calls), c.POINTER(Services), U, U, U, U, U, U,
                                           c.POINTER(U)]
    n.vertrix_message_dispatch.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4d2020)
    pool = Pool(cpu, 3, SIZE)
    flag, record, _ = pool.handles
    frame = c.create_string_buffer(FRAME_SIZE)

    @Resolve
    def resolve(handle, storage, size, context):
        if handle == STACK - FRAME:
            storage[0], size[0] = c.addressof(frame), FRAME_SIZE
            return 1
        return pool._resolve(handle, storage, size, context)

    services = Services(resolve)
    returns, fills, native_log, replay = [], [], [], []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4d0c84:
            value = struct.pack('<I', rng.choice([0, 1, 5]))
            cpu.mem_write(stack[0], value)
            fills.append((stack[0], value))
        returns.append(rng.getrandbits(32) if rng.random() < 0.7 else 0)
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx, s.stack))
        if s.target == 0x4d0c84:
            address, value = fills.pop(0)
            c.memmove(c.addressof(pool.buffers[flag]) + address - flag, value, 4)
        return replay.pop(0)

    calls = Calls(call, None)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        blob = rng.randbytes(FRAME_SIZE)
        cpu.mem_write(STACK - FRAME, blob)
        frame.raw = blob
        stubs.log.clear()
        returns.clear()
        fills.clear()
        native_log.clear()
        message = rng.choice(MESSAGES) if rng.random() < 0.9 else rng.getrandbits(32)
        obj, ebx = rng.getrandbits(32), rng.getrandbits(32)
        ecx = record if rng.random() < 0.8 else rng.getrandbits(32)
        if message == 0x4e:
            ecx = record
        pointer = flag if (message != 0x111 or rng.random() < 0.7) else 0
        want = original.call(0x4d2020, eax=obj, edx=message, ebx=ebx, ecx=ecx,
                             args=(pointer,)) & 0xffffffff
        replay[:] = list(returns)
        result = U()
        assert n.vertrix_message_dispatch(c.byref(calls), c.byref(services), STACK, obj, message,
                                          ebx, ecx, pointer, c.byref(result)), case
        assert result.value == want, (case, hex(message), result.value, want)
        assert native_log == stubs.log, (case, native_log, stubs.log)
        assert not replay and pool.same(), (case, pool.diff())
        assert frame.raw == bytes(cpu.mem_read(STACK - FRAME, FRAME_SIZE)), case
        totals[hex(message) if message in MESSAGES else 'other'] = \
            totals.get(hex(message) if message in MESSAGES else 'other', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': {'0x4d2020': args.cases},
              'messages': dict(sorted(totals.items())),
              'scope': 'The routine executes completely in the original with 0x4d0c84 and 0x4cb820 '
                       'stubbed and logged (0x4d0c84 setting the handled flag, mirrored for the '
                       'native); every call with its registers and stack argument, the returned '
                       'eax, the flag and the stack locals compare.'}
    (args.build_dir / 'message-dispatch-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
