"""Compare the original text seek 0x4b46e0 with the native recovery."""
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
CALLEES = {0x4cdb70: 0, 0x440610: 1, 0x4ca210: 0}
OLD = {0x4ca280: 0, 0x4ca070: 0, 0x4cdb70: 0, 0x4cdaf0: 0, 0x4ca310: 0, 0x4ca210: 0,
           0x4ca430: 3, 0x4ca370: 0, 0x4cda10: 0}


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
    n = build(args.build_dir, 'text-seek', ['list_text.c', 'rtl_glue.c', 'call_glue.c',
                                               'actor_storage.c'])
    P, V, O = c.POINTER(Calls), c.POINTER(Services), c.POINTER(U)
    n.vertrix_object_text_row.argtypes = [P, V, U, U, U, O]
    n.vertrix_object_text_nearest.argtypes = [P, V, U, U, U, O]
    n.vertrix_object_text_seek.argtypes = [P, V, U, U, U]
    n.vertrix_object_cursor_row.argtypes = [P, V, U, U, O]
    n.vertrix_object_cursor_row.restype = c.c_int
    for name in ('clamp', 'home', 'end'):
        getattr(n, 'vertrix_object_cursor_' + name).argtypes = [V, U]
        getattr(n, 'vertrix_object_cursor_' + name).restype = c.c_int
    n.vertrix_object_cursor_step.argtypes = [V, U, c.c_int32]
    n.vertrix_object_cursor_step.restype = c.c_int
    n.vertrix_object_cursor_at_end.argtypes = [V, U, O]
    n.vertrix_object_cursor_at_end.restype = c.c_int
    n.vertrix_object_text_row.restype = c.c_int
    n.vertrix_object_text_nearest.restype = c.c_int
    n.vertrix_object_text_seek.restype = c.c_int
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4b46e0)
    pool = Pool(cpu, 4, SIZE)
    returns, native_log, replay = [], [], []

    outs = []

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4cdb70:
            outs.append(pool.handles[1] + 0xc)
            cpu.mem_write(edx, struct.pack('<I', outs[-1]))
        elif address == 0x440610:
            outs.append(rng.getrandbits(32))
            cpu.mem_write(ecx, struct.pack('<I', outs[-1]))
        returns.append(rng.getrandbits(32))
        return returns[-1]

    stubs = Stubs(cpu, handler)
    for address, count in CALLEES.items():
        stubs.add(address, count)

    @Call
    def call(site, context):
        s = site.contents
        native_log.append((s.target, s.eax, s.edx, s.ebx, s.ecx) + ((s.stack,) if s.target == 0x440610 else ()))
        if s.target == 0x4cdb70:
            s.out_value = outs.pop(0)
        elif s.target == 0x440610:
            s.out_ecx = outs.pop(0)
        return replay.pop(0)

    calls = Calls(call, None)
    services = Services(pool.resolve)
    totals = {}
    for case in range(args.cases):
        pool.fill(rng)
        obj, parent, text, header = pool.handles
        length = rng.randrange(0, 6)
        blob = bytes(rng.randrange(1, 255) for _ in range(length)) + b'\0' * (SIZE - length)
        data = bytearray(cpu.mem_read(header, SIZE))
        struct.pack_into('<I', data, 4, rng.choice([0, 0, 1, rng.getrandbits(32)]))
        odata = bytearray(cpu.mem_read(obj, SIZE))
        struct.pack_into('<I', odata, 0x160, parent)
        pdata = bytearray(cpu.mem_read(parent, SIZE))
        struct.pack_into('<I', pdata, 0x15c, text)
        struct.pack_into('<I', pdata, 0xc, rng.choice([rng.getrandbits(32), rng.randrange(-80, 80) << 16 & 0xffffffff]))
        for handle, buf in ((obj, odata), (parent, pdata), (text, blob), (header, data)):
            cpu.mem_write(handle, bytes(buf))
            c.memmove(pool.buffers[handle], bytes(buf), SIZE)
        entry = STACK
        for name, address in (('row', 0x4b46e0), ('nearest', 0x4b4700), ('seek', 0x4b4780)):
            stubs.log.clear()
            returns.clear()
            native_log.clear()
            outs.clear()
            edx = rng.choice([rng.getrandbits(32), rng.randrange(0, 6), 0xffffffff, rng.randrange(-90, 90) & 0xffffffff])
            want = original.call(address, eax=obj, edx=edx, ebx=rng.getrandbits(32),
                                 ecx=rng.getrandbits(32)) & 0xffffffff
            replay[:] = list(returns)
            result = U()
            if name == 'row':
                assert n.vertrix_object_text_row(c.byref(calls), c.byref(services), entry, obj, edx,
                                                 c.byref(result)), case
                assert result.value == want, (case, name, result.value, want)
            elif name == 'nearest':
                assert n.vertrix_object_text_nearest(c.byref(calls), c.byref(services), entry - 4,
                                                     obj, edx, c.byref(result)), case
                assert result.value == want, (case, name, result.value, want)
            else:
                assert n.vertrix_object_text_seek(c.byref(calls), c.byref(services), entry, obj, edx), case
            assert native_log == stubs.log, (case, name, native_log[:4], stubs.log[:4])
            assert not replay and pool.same(), (case, name, pool.diff())
            totals[name] = totals.get(name, 0) + 1
        sv = c.byref(services)
        for name, address, native in (
                ('clamp', 0x4b4690, lambda: n.vertrix_object_cursor_clamp(sv, obj)),
                ('previous', 0x4b4600, lambda: n.vertrix_object_cursor_step(sv, obj, -1)),
                ('next', 0x4b4610, lambda: n.vertrix_object_cursor_step(sv, obj, 1)),
                ('home', 0x4b4620, lambda: n.vertrix_object_cursor_home(sv, obj)),
                ('end', 0x4b4630, lambda: n.vertrix_object_cursor_end(sv, obj)),
                ('at_end', 0x4b4660, None), ('row_at', 0x4b45f0, None)):
            cursor = rng.choice([0xffffffff, 0xfffffff0, rng.randrange(0, 9), length, length - 1 & 0xffffffff])
            struct.pack_into('<I', odata, 0x170, cursor)
            cpu.mem_write(obj, bytes(odata))
            c.memmove(pool.buffers[obj], bytes(odata), SIZE)
            stubs.log.clear()
            returns.clear()
            native_log.clear()
            outs.clear()
            want = original.call(address, eax=obj, ebx=rng.getrandbits(32), ecx=rng.getrandbits(32),
                                 edx=rng.getrandbits(32)) & 0xffffffff
            replay[:] = list(returns)
            result = U()
            if name == 'at_end':
                assert n.vertrix_object_cursor_at_end(sv, obj, c.byref(result))
                assert result.value == want & 0xff, (case, name, result.value, want)
            elif name == 'row_at':
                assert n.vertrix_object_cursor_row(c.byref(calls), sv, entry, obj, c.byref(result))
                assert result.value == want, (case, name, result.value, want)
            else:
                assert native()
            assert native_log == stubs.log, (case, name, native_log[:4], stubs.log[:4])
            assert not replay and pool.same(), (case, name, pool.diff())
            totals[name] = totals.get(name, 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'The routine executes completely in the original with the string runtime '
                       'stubbed and logged (0x4cdb70 and 0x440610 storing their out dwords); the returned value compares; every callee call '
                       'and every pool object compare.'}
    (args.build_dir / 'text-seek-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
