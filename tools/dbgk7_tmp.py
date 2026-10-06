"""Compare the complete original match scan 0x432480 with the native recovery."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path

from original import Original
from oracle_kit import Resolve, Stubs, build

U = c.c_uint32
PLAYER = 0x900000
PLAYER_SIZE = 0x1000
BASE = 0x901000
CELL_SIZE = 0x180
IMAGE = 0x5407b8
MASK_ADDR = 0x5406b0
DISPATCH_GLOBAL = 0x532a70
DISPATCH_TABLE = 0x4fb7b0
METHOD = 0x707000
SEED = 0x598d30
PA, PB, RW, MU = 0x701000, 0x701004, 0x701008, 0x70100c


class Site(c.Structure):
    _fields_ = [(name, U) for name in ('target', 'eax', 'edx', 'ebx', 'ecx', 'stack', 'stack_next')]


Call = c.CFUNCTYPE(U, c.POINTER(Site), c.c_void_p)


class Calls(c.Structure):
    _fields_ = [('call', Call), ('context', c.c_void_p)]


class Services(c.Structure):
    _fields_ = [('resolve', Resolve), ('allocate', c.c_void_p), ('draw', c.c_void_p),
                ('range', c.c_void_p), ('context', c.c_void_p)]


Allocate = c.CFUNCTYPE(U, U, c.c_void_p)
Draw = c.CFUNCTYPE(c.c_uint16, c.c_uint16, c.c_void_p)
Bind = c.CFUNCTYPE(None, U, c.c_uint16, c.c_void_p)
Append = c.CFUNCTYPE(None, U, U, c.c_void_p)


class Hooks(c.Structure):
    _fields_ = [('allocate', Allocate), ('draw', Draw), ('bind_frame', Bind), ('append', Append),
                ('context', c.c_void_p)]


Read = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint, c.POINTER(c.c_uint32), c.c_void_p)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=128)
    args = parser.parse_args()
    n = build(args.build_dir, 'match-scan',
              ['match_scan.c', 'match.c', 'board.c', 'call_glue.c', 'actor_storage.c',
               'actor_fields.c', 'block_factory.c', 'board_cells.c', 'board_markers.c',
               'actor_spawn.c', 'table_queries.c', 'engine_helpers.c', 'random.c'])
    n.vertrix_match_scan.argtypes = [c.POINTER(Calls), c.POINTER(Services), Read, c.c_void_p, U,
                                     c.c_void_p, c.c_size_t, c.c_uint8, c.POINTER(U),
                                     c.POINTER(U), c.POINTER(U), c.POINTER(U),
                                     c.c_char * 65, c.c_uint32 * 65, U, c.POINTER(Hooks)]
    n.vertrix_match_scan.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x432480)
    cpu.mem_map(PLAYER, 0x1000)
    cpu.mem_map(BASE, 0x100000)
    top = [BASE]
    buffers = {}
    alloc_order, divisors, binds, appends, method_calls = [], [], [], [], []
    method_returns = []
    script = []

    def take(size):
        handle = top[0]
        top[0] += (size + 0xf) & ~0xf
        assert top[0] < BASE + 0x100000, 'object space exhausted'
        buffers[handle] = c.create_string_buffer(size)
        return handle

    @Resolve
    def resolve(handle, storage, size, context):
        buffer = buffers.get(handle)
        if buffer is None:
            return 0
        storage[0] = c.addressof(buffer)
        size[0] = len(buffer.raw)
        return 1

    def handler(address, eax, edx, ebx, ecx, stack):
        if address == 0x4ca000:
            assert eax == 0x15c, hex(eax)
            handle = take(0x200)
            alloc_order.append(handle)
            return handle
        if address == 0x4826c0:
            assert eax == SEED, hex(eax)
            divisors.append(edx)
            return script.pop(0)
        if address == 0x4ac8a0:
            binds.append((eax, edx))
            return None
        if address == 0x4b5e70:
            appends.append((eax, edx))
            return 0
        if address == METHOD:
            method_calls.append((eax, edx, ebx, ecx))
            return method_returns.pop(0)
        raise AssertionError(hex(address))

    stubs = Stubs(cpu, handler)
    stubs.add(0x4ca000)
    stubs.add(0x4826c0)
    stubs.add(0x4ac8a0)
    stubs.add(0x4b5e70)
    stubs.add(METHOD)
    from unicorn import UC_HOOK_CODE as _HC
    _k7 = []
    def _k(uc, address, size, ctx):
        from unicorn.x86_const import UC_X86_REG_EDX as _EDX, UC_X86_REG_EBX as _EBX
        _k7.append((uc.reg_read(_EDX), uc.reg_read(_EBX)))
    cpu.hook_add(_HC, _k, begin=0x430190, end=0x430190)

    @Allocate
    def allocate(size, context):
        assert size == 0x15c, hex(size)
        return alloc_order.pop(0)

    @Draw
    def draw(divisor, context):
        return script.pop(0)

    @Bind
    def bind(actor, descriptor, context):
        binds.append((actor, descriptor))

    @Append
    def append(list_handle, item, context):
        appends.append((list_handle, item))

    @Call
    def call(site, context):
        s = site.contents
        if s.target == 0x4ca000:
            return alloc_order.pop(0)
        if s.target == METHOD:
            method_calls.append((s.eax, s.edx, s.ebx, s.ecx))
            return method_returns.pop(0)
        raise AssertionError(hex(s.target))

    @Read
    def read(address, width, value, context):
        value[0] = int.from_bytes(bytes(cpu.mem_read(address, width)), 'little')
        return 1

    hooks = Hooks(allocate, draw, bind, append, None)
    calls = Calls(call, None)
    services = Services(resolve, None, None, None, None)
    totals = {}
    for case in range(args.cases):
        top[0] = BASE
        buffers.clear()
        host = c.create_string_buffer(PLAYER_SIZE)
        data = bytearray(rng.randbytes(PLAYER_SIZE))
        slots, taps = [], []
        for _ in range(65):
            handle = take(CELL_SIZE)
            slots.append(handle)
            block = bytearray(rng.randbytes(CELL_SIZE))
            block[0x15c] = rng.choice([0, 1, 2, 3, 4, 5, 6, 7, 0xff])
            cpu.mem_write(handle, bytes(block))
            buffers[handle].raw = bytes(block)
        for _ in range(260):
            handle = take(CELL_SIZE)
            taps.append(handle)
            block = bytes(rng.randbytes(CELL_SIZE))
            cpu.mem_write(handle, block)
            buffers[handle].raw = block
        for i in range(65):
            struct.pack_into('<I', data, 0x220 + i * 4, slots[i])
        for b in range(5):
            for i in range(13):
                for t in range(4):
                    struct.pack_into('<I', data, b * 0xd0 + i * 16 + t * 4 + 0x324,
                                     taps[(b * 13 + i) * 4 + t])
        data[0x1de:0x1de + 65] = bytes(rng.choice([0, 1, 2, 3, 4, 5, 6, 7, 0xff])
                                       for _ in range(65))
        cpu.mem_write(PLAYER, bytes(data))
        host.raw = bytes(data)
        image = bytes(rng.choice([0, 1, 2, 3, 4, 5, 6, 7, 0xff]) for _ in range(65))
        cpu.mem_write(IMAGE, image)
        cimage = (c.c_char * 65).from_buffer_copy(image)
        mask = [rng.getrandbits(32) for _ in range(65)]
        cpu.mem_write(MASK_ADDR, struct.pack('<65I', *mask))
        cmask = (c.c_uint32 * 65)(*mask)
        side = rng.choice([1, 1, 2, 3, rng.randrange(256)])
        dispatch_index = rng.randrange(8)
        cpu.mem_write(DISPATCH_GLOBAL, struct.pack('<I', dispatch_index))
        cpu.mem_write(DISPATCH_TABLE + dispatch_index * 4, struct.pack('<I', METHOD))
        values = [rng.getrandbits(16) for _ in range(128)]
        returns = [rng.getrandbits(32) for _ in range(65)]
        for log in (alloc_order, divisors, binds, appends, method_calls):
            log.clear()
        script[:] = list(values)
        method_returns[:] = list(returns)
        cpu.mem_write(PA, bytes(16))
        expect = original.call(0x432480, eax=PLAYER, edx=MU, ebx=RW, ecx=side,
                               args=(PA, PB)) & 0xffffffff
        orig_binds, orig_appends = list(binds), list(appends)
        orig_divisors = list(divisors)
        orig_methods = list(method_calls)
        for log in (divisors, binds, appends, method_calls):
            log.clear()
        script[:] = list(values)
        method_returns[:] = list(returns)
        fa, fb, rw, mu = U(), U(), U(), U()
        got = n.vertrix_match_scan(c.byref(calls), c.byref(services), read, None, PLAYER, host,
                                   PLAYER_SIZE, side, c.byref(fa), c.byref(fb), c.byref(rw),
                                   c.byref(mu), cimage, cmask, dispatch_index, c.byref(hooks))
        assert got == expect, (case, hex(got), hex(expect))
        assert len(alloc_order) + len([1]) > 0
        assert fa.value == struct.unpack('<I', cpu.mem_read(PA, 4))[0], (case, fa.value)
        assert fb.value == struct.unpack('<I', cpu.mem_read(PB, 4))[0], (case, fb.value)
        assert rw.value == struct.unpack('<I', cpu.mem_read(RW, 4))[0], (case, rw.value)
        assert mu.value == struct.unpack('<I', cpu.mem_read(MU, 4))[0], (case, mu.value)
        assert host.raw == bytes(cpu.mem_read(PLAYER, PLAYER_SIZE)), case
        assert bytes(cimage) == bytes(cpu.mem_read(IMAGE, 65)), case
        assert list(cmask) == list(struct.unpack('<65I', cpu.mem_read(MASK_ADDR, 260))), case
        for handle, buffer in buffers.items():
            assert buffer.raw == bytes(cpu.mem_read(handle, len(buffer.raw))), (case, hex(handle))
        print('ORIG K7:', _k7)
        assert divisors == orig_divisors, (case, divisors, orig_divisors)
        assert binds == orig_binds, (case, binds, orig_binds)
        assert appends == orig_appends, (case, appends, orig_appends)
        assert method_calls == orig_methods, (case, method_calls, orig_methods)
        totals['0x432480'] = totals.get('0x432480', 0) + 1
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete original 0x432480 executions.'}
    (args.build_dir / 'match-scan-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
