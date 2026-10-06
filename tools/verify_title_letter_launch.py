"""Compare the original letter launch 0x45a0c0 and handlers 0x45a1c0 and 0x45a4f0 with the native recovery."""
import ctypes as c, random, struct
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_EDX
from original import Original
import verify_support as vs

OBJ, DESC, SCREEN = vs.SCRATCH, vs.SCRATCH + 0x400, vs.SCRATCH + 0x800
SIZE = 0x160
X_TABLE, Y_TABLE, HEADING = 0x59939c, 0x598dfc, 0x59993c
FINISHED = 0x532a40


class Tables(c.Structure):
    _fields_ = [('x', c.c_int32 * 360), ('y', c.c_int32 * 360)]


class Trace(c.Structure):
    _fields_ = [('iterations', c.c_uint32), ('unwrapped', c.c_uint32)]


class Dimensions(c.Structure):
    _fields_ = [('width', c.c_uint16), ('height', c.c_uint16)]


Play = c.CFUNCTYPE(None, c.c_void_p, c.c_uint32)


def main():
    args = vs.parse(__doc__)
    n = vs.build(args, 'title-letter-launch', ['title_letter_step.c', 'actor_angle.c', 'actor_fields.c', 'actor_storage.c', 'fixed_point.c', 'rotation.c', 'word_transition.c', 'dword_transition.c', 'ui_slide_setup.c', 'render_geometry.c', 'surface.c', 'render_dispatch.c'])
    common = [c.POINTER(c.c_uint8), c.c_size_t, c.c_uint32, c.POINTER(Tables), c.POINTER(Trace), c.POINTER(Dimensions), c.c_uint8, c.c_uint8]
    n.vertrix_title_letter_fly_out.argtypes = common
    n.vertrix_title_letter_wave_fly.argtypes = common
    n.vertrix_title_letter_fight_fly.argtypes = common + [c.POINTER(c.c_uint32)]
    n.vertrix_title_letter_launch.argtypes = [c.POINTER(c.c_uint8), c.c_size_t, c.POINTER(c.c_uint16), Play, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    original.call(0x4b9050)
    rng = random.Random(0x45a0c0)
    sounds = []
    cpu.mem_write(0x482a60, b'\xc3')
    cpu.hook_add(UC_HOOK_CODE, lambda cpu_, a, size, user: sounds.append((cpu_.reg_read(UC_X86_REG_EAX), cpu_.reg_read(UC_X86_REG_EDX), cpu_.reg_read(UC_X86_REG_EBX))), begin=0x482a60, end=0x482a60)
    xs = [rng.randrange(-70000, 70000) for _ in range(360)]
    ys = [rng.randrange(-70000, 70000) for _ in range(360)]
    cpu.mem_write(X_TABLE, struct.pack('<360i', *xs))
    cpu.mem_write(Y_TABLE, struct.pack('<360i', *ys))
    tables = Tables((c.c_int32 * 360)(*xs), (c.c_int32 * 360)(*ys))
    heading = [rng.getrandbits(16) for _ in range(0x10000)]
    cpu.mem_write(HEADING, struct.pack('<65536H', *heading))
    heading_array = (c.c_uint16 * 0x10000)(*heading)
    played = []

    @Play
    def on_play(context, channel):
        played.append(channel)
    totals = {}

    def settings(data, elapsed):
        unscaled, screen_mode = rng.choice([0, 1]), rng.randrange(17)
        cpu.mem_write(SCREEN, bytes(0x300))
        cpu.mem_write(SCREEN + 0x220, bytes([unscaled, screen_mode]))
        cpu.mem_write(0x544070, struct.pack('<I', SCREEN))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        cpu.mem_write(OBJ, bytes(data))
        return unscaled, screen_mode

    for case in range(args.cases):
        # 0x45a0c0: launch
        data = bytearray(rng.randbytes(SIZE))
        struct.pack_into('<hh', data, 8, rng.choice([0, 0x140, 100, -50, 0x7fff, -0x8000, rng.randrange(-700, 700)]), rng.choice([0, 0xf0, 80, -10, 0x7fff, rng.randrange(-500, 500)]))
        cpu.mem_write(OBJ, bytes(data))
        sounds.clear()
        try:
            original.call(0x45a0c0, eax=OBJ)
        except Exception:
            totals['faulting'] = totals.get('faulting', 0) + 1
            continue
        want = bytes(cpu.mem_read(OBJ, SIZE))
        buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
        played.clear()
        assert n.vertrix_title_letter_launch(buffer, SIZE, heading_array, on_play, None) == 1, case
        got = bytes(buffer)
        assert got == want, ('launch', case, [(hex(i), got[i], want[i]) for i in range(SIZE) if got[i] != want[i]])
        assert played == [e[0] for e in sounds] == [0, 4], (case, played, sounds)
        index = struct.unpack('<I', bytes(cpu.mem_read(0x4f81b0, 4)))[0]
        entry = struct.unpack('<I', bytes(cpu.mem_read(0x533164 + 4 * index, 4)))[0]
        volume = struct.unpack('<I', bytes(cpu.mem_read(0x532b9c, 4)))[0]
        assert all(e[1] == entry and e[2] == volume for e in sounds), sounds
        totals['launch'] = totals.get('launch', 0) + 1
        # 0x45a1c0 and 0x45a4f0
        for handler, name in ((0x45a1c0, 'fly_out'), (0x45a4f0, 'fight_fly'), (0x45a910, 'wave_fly')):
            data = bytearray(rng.randbytes(SIZE))
            period = rng.choice([1, 2, 60, 100, rng.randrange(1, 400)])
            elapsed = rng.choice([0, 1, 16, 50, rng.randrange(0, 500)])
            counter = rng.randrange(0, period * 3)
            if rng.random() < 0.2:
                counter = rng.randrange(0, period)
                elapsed = rng.randrange(0, period - counter) if period - counter > 0 else 0
            elif counter + elapsed < period:
                counter = period
            limit = rng.choice([1, 16, 60, 0x3c, rng.randrange(1, 200)])
            shape = rng.choice(['opaque', 'full', 'fading'])
            radius = {'opaque': limit + rng.randrange(1, 100), 'full': limit, 'fading': rng.randrange(1, limit + 1)}[shape]
            if name == 'fly_out':
                radius = rng.choice([radius, limit, limit + rng.randrange(0, 5), limit - rng.randrange(0, 5), rng.randrange(-300, 300)])
            struct.pack_into('<II', data, 0xbc, counter, period)
            struct.pack_into('<h', data, 0x30, limit)
            struct.pack_into('<h', data, 0x2a, radius)
            struct.pack_into('<h', data, 0x32, rng.choice([0, 1, 2, 3, 7, -1, rng.randrange(-40, 40)]))
            struct.pack_into('<H', data, 0x24, rng.randrange(360))
            struct.pack_into('<h', data, 0x28, rng.choice([0, 1, 5, -3, 90, -90, rng.randrange(-400, 400)]))
            struct.pack_into('<hhh', data, 0x48, rng.randrange(-300, 300), rng.randrange(-300, 300), rng.choice([0, 1, 4, -4, rng.randrange(-50, 50)]))
            cur = rng.randrange(-20, 20)
            struct.pack_into('<III', data, 0x64, cur & 0xffffffff, rng.choice([cur, cur + rng.randrange(-8, 8)]) & 0xffffffff, rng.choice([0, 1, 2, 3, 6, 0xffffffff]))
            data[0x44] = rng.randrange(17)
            data[0x91] = rng.choice([0, 1])
            for offset_ in (0xf4, 0xf8):
                struct.pack_into('<H', data, offset_, rng.choice([0, 1, 7, 16, 24, rng.getrandbits(16) & 0x1ff]))
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
            unscaled, screen_mode = settings(data, elapsed)
            cpu.mem_write(FINISHED, struct.pack('<I', 0))
            original.call(handler, eax=OBJ)
            want = bytes(cpu.mem_read(OBJ, SIZE))
            want_finished = struct.unpack('<I', bytes(cpu.mem_read(FINISHED, 4)))[0]
            buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
            common_args = (buffer, SIZE, elapsed, c.byref(tables), c.byref(Trace()), c.byref(descriptor) if descriptor else None, unscaled, screen_mode)
            finished = c.c_uint32(0)
            if name == 'fly_out':
                assert n.vertrix_title_letter_fly_out(*common_args) == 1, (name, case)
            elif name == 'wave_fly':
                assert n.vertrix_title_letter_wave_fly(*common_args) == 1, (name, case)
            else:
                assert n.vertrix_title_letter_fight_fly(*common_args, c.byref(finished)) == 1, (name, case)
                assert finished.value == want_finished, (name, case)
            got = bytes(buffer)
            assert got == want, (name, case, [(hex(i), got[i], want[i]) for i in range(SIZE) if got[i] != want[i]])
            totals[name] = totals.get(name, 0) + 1
            if struct.unpack_from('<I', want, 0x154)[0] != struct.unpack_from('<I', data, 0x154)[0]:
                totals[name + '_done'] = totals.get(name + '_done', 0) + 1
    vs.write_report(args, 'title-letter-launch', {
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'Complete original 0x45a0c0 (with the real 0x484680, 0x484700 and 0x4ad510; the sound player 0x482a60 observed and its table lookup checked) and handlers 0x45a1c0, 0x45a4f0 and 0x45a910 (with the real actor helpers, 0x4ad750, 0x4ad5e0, 0x4ad530 and 0x4b14c0) run in the oracle. The first 0x160 actor bytes, handler token included, and the flag 0x532a40 compare after every call.'})


if __name__ == '__main__':
    main()
