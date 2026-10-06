"""Compare complete original sound object routines with the native recovery."""
import ctypes as c, random, struct
from original import Original
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX
import verify_support as vs

OBJ, POOL = vs.SCRATCH, vs.SCRATCH + 0x1000
SIZE = 0x100
Call = c.CFUNCTYPE(c.c_int32, c.c_void_p, c.c_uint32, c.c_uint32, c.c_uint32)
Build = c.CFUNCTYPE(c.c_uint32, c.c_void_p, c.c_uint32, c.c_uint32)
BUILDERS = (0x476aa0, 0x477390, 0x477b10)
#(address, native name, handle fields as(offset), kind)
RELEASE = ((0x476cc0, 'vertrix_sound_release_primary', (0x10, 0xc), (8,), (4,)),
           (0x477320, 'vertrix_sound_release_stream', (0xc, 8), (4,), (0x10,)),
           (0x477d10, 'vertrix_sound_release_looped', (0x30, 4), (8,), (0xc,)))
CLEAR = ((0x4756d0, 'vertrix_sound_simple_clear'), (0x4768e0, 'vertrix_sound_bank_clear'),
         (0x476d20, 'vertrix_sound_bank_clear_tail'), (0x4779c0, 'vertrix_sound_slider_clear'),
         (0x477910, 'vertrix_sound_range_clear'))


def main():
    args = vs.parse(__doc__)
    n = vs.build(args, 'sound-object', ['sound_object.c'])
    U8P, U, S = c.POINTER(c.c_uint8), c.c_uint32, c.c_size_t
    for _, name in CLEAR:
        getattr(n, name).argtypes = [U8P, S]
    n.vertrix_sound_simple_set.argtypes = [U8P, S, c.c_uint8, U, U, U]
    n.vertrix_sound_key_is_control.argtypes = [U]
    n.vertrix_sound_check_primary.argtypes = [U8P, S, Call, c.c_void_p]
    for _, name, *_ in RELEASE:
        getattr(n, name).argtypes = [U8P, S, Call, c.c_void_p]
    n.vertrix_sound_open_keys.argtypes = [U8P, S, U, U, c.c_uint8, U, Build, c.c_void_p]
    n.vertrix_sound_open_keys.restype = U
    n.vertrix_sound_open_stream.argtypes = [U8P, S, U, c.c_uint8, U, Build, c.c_void_p]
    n.vertrix_sound_open_stream.restype = U
    n.vertrix_sound_open_looped.argtypes = [U8P, S, U, c.c_uint8, U, Build, c.c_void_p]
    n.vertrix_sound_open_looped.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    stubs = vs.VirtualStubs(cpu, register=False)
    rng = random.Random(0x4756d0)
    native_events, built, native_built, returns = [], [], [], []
    for address in BUILDERS:
        cpu.mem_write(address, b'\xc3')

    def builder_hook(cpu_, address, size, user):
        built.append((cpu_.reg_read(UC_X86_REG_EAX), cpu_.reg_read(UC_X86_REG_EDX)))
        cpu_.reg_write(UC_X86_REG_EAX, returns[0])

    for address in BUILDERS:
        cpu.hook_add(UC_HOOK_CODE, builder_hook, begin=address, end=address)

    @Call
    def call(context, handle, slot, argument):
        native_events.append((handle, slot))
        return stubs_returns.pop(0)

    @Build
    def build(context, handle, argument):
        native_built.append((handle, argument))
        return returns[0]

    stubs_returns = []
    pool = [POOL + 0x40 * k for k in range(6)]
    for handle in pool:
        cpu.mem_write(handle, struct.pack('<I', stubs.VTABLE) + rng.randbytes(0x3c))
    totals = {}

    def native_buffer(data):
        return (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))

    def count(name):
        totals[name] = totals.get(name, 0) + 1

    def compare(name, data, buffer, case):
        want = bytes(cpu.mem_read(OBJ, SIZE))
        assert bytes(buffer) == want, (case, name, [(hex(i), buffer[i], want[i]) for i in range(SIZE)
                                                   if buffer[i] != want[i]][:8])
        count(name)

    def fresh(handle_fields=()):
        data = bytearray(rng.randbytes(SIZE))
        for field in handle_fields:
            struct.pack_into('<I', data, field, rng.choice([0] + pool))
        cpu.mem_write(OBJ, bytes(data))
        stubs.events.clear()
        native_events.clear()
        built.clear()
        native_built.clear()
        values = [rng.getrandbits(32) | (rng.random() < 0.4) * 0x80000000 for _ in range(4)]
        stubs.returns[:] = values
        stubs_returns[:] = values
        return data

    for case in range(args.cases):
        for address, name in CLEAR:
            data = fresh()
            original.call(address, eax=OBJ)
            assert getattr(n, name)(buf := native_buffer(data), SIZE) == 1
            compare(hex(address), data, buf, case)
        data = fresh()
        kind, first, second, third = rng.getrandbits(8), rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32)
        original.call(0x475790, eax=OBJ, edx=kind | rng.getrandbits(24) << 8, ebx=first, ecx=second, args=(third,))
        assert n.vertrix_sound_simple_set(buf := native_buffer(data), SIZE, kind, first, second, third)
        compare('0x475790', data, buf, case)
        key = rng.choice([rng.getrandbits(32), rng.getrandbits(16), 0x70 + rng.randrange(8) - 1, 0xbe + rng.randrange(8) - 1,
                          rng.getrandbits(16) << 16 | 0x72])
        original.call(0x476650, eax=key)
        got = n.vertrix_sound_key_is_control(key)
        expected = c.c_uint32(original.cpu.reg_read(UC_X86_REG_EAX)).value
        assert got == expected, (case, hex(key))
        count('0x476650')
        data = fresh((0x10,))
        original.call(0x476c80, eax=OBJ)
        result = original.cpu.reg_read(UC_X86_REG_EAX)
        assert n.vertrix_sound_check_primary(buf := native_buffer(data), SIZE, call, None) == result
        assert [e[:2] for e in stubs.events] == native_events
        compare('0x476c80', data, buf, case)
        for address, name, handles, owner, playing in RELEASE:
            data = fresh(handles)
            for offset in owner:
                data[offset] = rng.choice([0, 0, 0, 1, 7])
            for offset in playing:
                struct.pack_into('<I', data, offset, rng.choice([0, 1, 1, 2]))
            cpu.mem_write(OBJ, bytes(data))
            original.call(address, eax=OBJ)
            assert getattr(n, name)(buf := native_buffer(data), SIZE, call, None) == 1
            assert [e[:2] for e in stubs.events] == native_events, (case, name)
            totals['virtual_calls'] = totals.get('virtual_calls', 0) + len(native_events)
            compare(hex(address), data, buf, case)
#Builders : 0x476a00(mode in ecx, flag in bl), 0x4772f0, 0x477af0.
        for address, which in ((0x476a00, 'keys'), (0x4772f0, 'stream'), (0x477af0, 'looped')):
            data = fresh()
            flag = rng.choice([0, 0, 1, 0x80, rng.getrandbits(8)])
            mode = rng.choice([0, 1, 0, 1, 2, rng.getrandbits(32)])
            argument = rng.getrandbits(32)
            returns[:] = [rng.choice([0, 1, rng.getrandbits(32)])]
            original.call(address, eax=OBJ, edx=argument, ebx=flag | rng.getrandbits(24) << 8, ecx=mode)
            result = original.cpu.reg_read(UC_X86_REG_EAX)
            buf = native_buffer(data)
            if which == 'keys':
                got = n.vertrix_sound_open_keys(buf, SIZE, OBJ, mode, flag, argument, build, None)
            elif which == 'stream':
                got = n.vertrix_sound_open_stream(buf, SIZE, OBJ, flag, argument, build, None)
            else:
                got = n.vertrix_sound_open_looped(buf, SIZE, OBJ, flag, argument, build, None)
            assert built == native_built and all(b[0] == OBJ for b in built), (case, which)
            assert got == result, (case, which, got, result)
            compare(hex(address), data, buf, case)
    vs.write_report(args, 'sound-object', {
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'Complete 4756d0, 475790, 4768e0, 476d20, 4779c0, 477910, 476650, 476c80, 476cc0, '
                 '477320, 477d10, 476a00, 4772f0 and 477af0 execute in the original with COM-style '
                 'vtable stubs (data-driven results) and neutralised builders 476aa0/477390/477b10; '
                 'object bytes, every virtual call, builder invocation and return value compare.'})


if __name__ == '__main__':
    main()
