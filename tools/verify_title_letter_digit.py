"""Compare the complete original digit step handler 0x459ec0 with the native recovery."""
import ctypes as c, random, struct
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_ESP
from original import Original
import verify_support as vs

OBJ, DESC, SCREEN, TEXT = vs.SCRATCH, vs.SCRATCH + 0x400, vs.SCRATCH + 0x800, vs.SCRATCH + 0xc00
SIZE = 0x160
X_TABLE, Y_TABLE = 0x59939c, 0x598dfc
LEVEL_GLOBAL, FINISHED, TABLE = 0x4f9c05, 0x532a3c, 0x540f88


class Tables(c.Structure):
    _fields_ = [('x', c.c_int32 * 360), ('y', c.c_int32 * 360)]


class Trace(c.Structure):
    _fields_ = [('iterations', c.c_uint32), ('unwrapped', c.c_uint32)]


class Dimensions(c.Structure):
    _fields_ = [('width', c.c_uint16), ('height', c.c_uint16)]


Glyph = c.CFUNCTYPE(c.c_uint32, c.c_void_p, c.c_uint8, c.c_int8)
Bind = c.CFUNCTYPE(c.c_uint32, c.c_void_p, c.c_uint32, c.c_uint32)
Related = c.CFUNCTYPE(c.c_int, c.c_void_p, c.c_uint32)


class Services(c.Structure):
    _fields_ = [('glyph', Glyph), ('bind', Bind), ('related', Related), ('context', c.c_void_p)]


def main():
    args = vs.parse(__doc__)
    n = vs.build(args, 'title-letter-digit', ['title_letter_step.c', 'actor_angle.c', 'actor_fields.c', 'actor_storage.c', 'fixed_point.c', 'rotation.c', 'word_transition.c', 'dword_transition.c', 'ui_slide_setup.c', 'render_geometry.c', 'surface.c', 'render_dispatch.c'])
    n.vertrix_title_letter_digit.argtypes = [c.POINTER(c.c_uint8), c.c_size_t, c.c_uint32, c.POINTER(Tables), c.POINTER(Trace), c.POINTER(Dimensions), c.c_uint8, c.c_uint8, c.c_int8, c.POINTER(Services), c.POINTER(c.c_uint32)]
    original = Original(args.executable)
    cpu = original.cpu
    original.call(0x4b9050)
    rng = random.Random(0x459ec0)
    events = []
    results = {}

    def hook(address, name):
        cpu.mem_write(address, b'\xc3')

        def run(cpu_, a, size, user):
            eax, edx = cpu_.reg_read(UC_X86_REG_EAX), cpu_.reg_read(UC_X86_REG_EDX)
            if name == 'string':
                esp = cpu_.reg_read(UC_X86_REG_ESP)
                dest, fmt, value = struct.unpack('<3I', bytes(cpu_.mem_read(esp + 4, 12)))
                text = ('%d' % value).encode() + b'\0'
                cpu_.mem_write(TEXT, text)
                cpu_.mem_write(dest, struct.pack('<I', TEXT))
                events.append(('string', fmt, value))
                return
            if name == 'release' or name == 'init':
                return
            ret = rng.getrandbits(32) if name != 'related' else rng.getrandbits(1)
            cpu_.reg_write(UC_X86_REG_EAX, ret)
            events.append((name, eax & 0xffffffff, edx & 0xffffffff, ret))
        cpu.hook_add(UC_HOOK_CODE, run, begin=address, end=address)
    for address, name in ((0x4ca070, 'init'), (0x4cdfb0, 'string'), (0x4ca210, 'release'), (0x43f420, 'glyph'), (0x4877f0, 'bind'), (0x450f80, 'related')):
        hook(address, name)
    xs = [rng.randrange(-70000, 70000) for _ in range(360)]
    ys = [rng.randrange(-70000, 70000) for _ in range(360)]
    cpu.mem_write(X_TABLE, struct.pack('<360i', *xs))
    cpu.mem_write(Y_TABLE, struct.pack('<360i', *ys))
    tables = Tables((c.c_int32 * 360)(*xs), (c.c_int32 * 360)(*ys))
    table = [rng.getrandbits(32) for _ in range(8)]
    cpu.mem_write(TABLE, struct.pack('<8I', *table))
    totals = {'not_due': 0, 'level': 0, 'moving': 0, 'arrived': 0, 'finished': 0, 'bound': 0}
    for case in range(args.cases):
        data = bytearray(rng.randbytes(SIZE))
        shape = rng.choice(['not_due', 'level', 'opaque', 'full'])
        period = rng.choice([1, 2, 60, 100, rng.randrange(1, 400)])
        elapsed = rng.choice([0, 1, 16, 50, rng.randrange(0, 500)])
        counter = rng.randrange(0, period * 3)
        if shape == 'not_due':
            counter = rng.randrange(0, period)
            elapsed = rng.randrange(0, period - counter) if period - counter > 0 else 0
        elif counter + elapsed < period:
            counter = period
        limit = rng.choice([1, 16, 60, 0x3c, rng.randrange(1, 200)])
        radius = {'level': rng.randrange(0, limit + 1), 'opaque': limit + rng.randrange(1, 100), 'full': limit, 'not_due': rng.randrange(0, 300)}[shape]
        if shape == 'level' and radius == 0 and limit == 0:
            radius = 1
        struct.pack_into('<II', data, 0xbc, counter, period)
        struct.pack_into('<h', data, 0x30, limit)
        struct.pack_into('<h', data, 0x2a, radius)
        struct.pack_into('<h', data, 0x32, rng.choice([0, 1, 2, 3, 7, -1, rng.randrange(-40, 40)]))
        struct.pack_into('<H', data, 0x24, rng.randrange(360))
        struct.pack_into('<h', data, 0x28, rng.choice([0, 1, 5, -3, 90, -90, rng.randrange(-400, 400)]))
        struct.pack_into('<hhh', data, 0x48, rng.randrange(-300, 300), rng.randrange(-300, 300), rng.choice([0, 1, 4, -4, rng.randrange(-50, 50)]))
        struct.pack_into('<I', data, 0x04, rng.randrange(8))
        current = rng.randrange(0, 12)
        struct.pack_into('<III', data, 0x58, current, max(0, rng.choice([current, current + rng.randrange(-3, 4), rng.randrange(0, 12)])), rng.choice([0, 1, 1, 2, 3, 0xffffffff]))
        data[0x44] = rng.randrange(17)
        data[0x91] = rng.choice([0, 1])
        for offset_ in (0xf4, 0xf8):
            struct.pack_into('<H', data, offset_, rng.choice([0, 1, 7, 16, 24, rng.getrandbits(16) & 0x1ff]))
        if rng.random() < 0.5:
            struct.pack_into('<I', data, 0xb0, 0)
        descriptor = None
        if rng.random() < 0.5:
            dims = (rng.choice([0, 3, 24, rng.getrandbits(16) & 0x1ff]), rng.choice([0, 5, 24, rng.getrandbits(16) & 0x1ff]))
            struct.pack_into('<I', data, 0xb4, DESC)
            cpu.mem_write(DESC, bytes(rng.randbytes(0x40)))
            cpu.mem_write(DESC + 4, struct.pack('<H', dims[0]))
            cpu.mem_write(DESC + 8, struct.pack('<H', dims[1]))
            descriptor = Dimensions(*dims)
        else:
            struct.pack_into('<I', data, 0xb4, 0)
        unscaled, screen_mode = rng.choice([0, 1]), rng.randrange(17)
        glyph_level = rng.randrange(-128, 128)
        cpu.mem_write(LEVEL_GLOBAL, struct.pack('<b', glyph_level))
        cpu.mem_write(SCREEN, bytes(0x300))
        cpu.mem_write(SCREEN + 0x220, bytes([unscaled, screen_mode]))
        cpu.mem_write(0x544070, struct.pack('<I', SCREEN))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        cpu.mem_write(FINISHED, struct.pack('<I', 0))
        cpu.mem_write(OBJ, bytes(data))
        events.clear()
        original.call(0x459ec0, eax=OBJ)
        want = bytes(cpu.mem_read(OBJ, SIZE))
        want_finished = struct.unpack('<I', bytes(cpu.mem_read(FINISHED, 4)))[0]
        replay = [e for e in events if e[0] != 'string']
        text = [e for e in events if e[0] == 'string']
        seen = []

        @Glyph
        def glyph(ctx, character, level):
            e = replay.pop(0)
            assert e[0] == 'glyph' and e[2] == character and (struct.unpack('<i', struct.pack('<I', e[1]))[0] & 0xff) == (level & 0xff), (case, e, character, level)
            seen.append('glyph')
            return e[3]

        @Bind
        def bind(ctx, bank, frame):
            e = replay.pop(0)
            assert e[0] == 'bind' and e[1] == bank and e[2] == frame, (case, e, bank, frame)
            seen.append('bind')
            return e[3]

        @Related
        def related(ctx, mode):
            e = replay.pop(0)
            assert e[0] == 'related' and e[1] == table[mode], (case, e, mode)
            seen.append('related')
            return e[3]
        services = Services(glyph, bind, related, None)
        buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
        finished = c.c_uint32(0)
        result = n.vertrix_title_letter_digit(buffer, SIZE, elapsed, c.byref(tables), c.byref(Trace()), c.byref(descriptor) if descriptor else None, unscaled, screen_mode, glyph_level, c.byref(services), c.byref(finished))
        assert result == 1, (case, shape)
        got = bytes(buffer)
        assert got == want, (case, shape, [(hex(i), got[i], want[i]) for i in range(SIZE) if got[i] != want[i]])
        assert not replay and finished.value == want_finished, (case, replay, finished.value, want_finished)
        if text:
            assert text[0][1] == 0x50e21d, text
        totals['not_due' if shape == 'not_due' else 'level'] += 1 if shape in ('not_due', 'level') else 0
        if 'glyph' in seen:
            totals['moving'] += 1
        if 'bind' in seen:
            totals['bound'] += 1
        if 'related' in seen:
            totals['arrived'] += 1
        if finished.value:
            totals['finished'] += 1
    vs.write_report(args, 'title-letter-digit', {
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'Complete original handler 0x459ec0 runs in the oracle with the real 0x4ac500/0x4ac540/0x4ac5b0, 0x4ad060, 0x4ad260, 0x4ad530, 0x4b14c0 and 0x4ad6e0; the string runtime (0x4ca070, 0x4cdfb0, 0x4ca210), the glyph map 0x43f420, the bank lookup 0x4877f0 and 0x450f80 are stubbed, logged and compared with the native service calls. The first 0x160 actor bytes (handler token included) and the finished flag 0x532a3c compare after every call.'})


if __name__ == '__main__':
    main()
