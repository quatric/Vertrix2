"""Compare the complete original letter step handler 0x459be0 with the native recovery."""
import ctypes as c, random, struct
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EDX
from oracle_kit import Stubs
from verify_call_glue import Calls, Call
from original import Original
import verify_support as vs

OBJ, DESC, SCREEN = vs.SCRATCH, vs.SCRATCH + 0x400, vs.SCRATCH + 0x800
SIZE = 0x160
X_TABLE, Y_TABLE = 0x59939c, 0x598dfc
VOICE_BASE = 0x4f81b8


class Tables(c.Structure):
    _fields_ = [('x', c.c_int32 * 360), ('y', c.c_int32 * 360)]


class Trace(c.Structure):
    _fields_ = [('iterations', c.c_uint32), ('unwrapped', c.c_uint32)]


class Dimensions(c.Structure):
    _fields_ = [('width', c.c_uint16), ('height', c.c_uint16)]


FightFn = c.CFUNCTYPE(None, c.c_void_p)
Draw = c.CFUNCTYPE(c.c_uint32, c.c_void_p, c.c_uint32)


class Fight(c.Structure):
    _fields_ = [('fight', FightFn), ('draw', Draw), ('context', c.c_void_p)]


class Voice(c.Structure):
    _fields_ = [('played', c.c_int), ('voice', c.c_uint32), ('variant', c.c_int)]


def verify_full_effect(args, native):
    """Normal complete restart/settle ABI, with only final centering supplied as a boundary."""
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x459e00)
    total, branches, mutations = {}, {}, 0
    expected_calls, native_calls = [], []
    callback_result = 0
    patches = []
    buffer = None

    def original_center(address, eax, edx, ebx, ecx, stack):
        expected_calls.append((address, eax, edx, ebx, ecx))
        for offset, data in patches:
            cpu.mem_write(eax + offset, data)
        return callback_result

    stubs = Stubs(cpu, original_center)
    stubs.add(0x457890)

    @Call
    def center(site, context):
        call = site.contents
        native_calls.append((call.target, call.eax, call.edx, call.ebx, call.ecx))
        for offset, data in patches:
            c.memmove(c.addressof(buffer) + offset, data, len(data))
        return callback_result

    calls = Calls(center, None)
    for address, name in ((0x459d60, 'settle'), (0x459e00, 'restart')):
        function = getattr(native, 'vertrix_title_letter_' + name + '_call')
        function.argtypes = [c.POINTER(Calls), c.POINTER(c.c_uint8), c.c_size_t,
                             c.c_uint32, c.c_uint32, c.c_uint32]
        function.restype = c.c_uint32
        for case in range(args.cases):
            data = bytearray(rng.randbytes(SIZE))
            shape = ('not_due', 'moving', 'arrived', 'wrapped', 'random')[case % 5]
            period = rng.choice([1, 12, 60, rng.randrange(1, 400)])
            elapsed = rng.choice([0, 1, 16, 0xffffffff, rng.getrandbits(32)])
            counter = rng.getrandbits(32)
            current, target = rng.randrange(-32768, 32768), rng.randrange(-32768, 32768)
            step = rng.choice([-32768, -1, 0, 1, 32767, rng.randrange(-32768, 32768)])
            if shape == 'not_due':
                counter, elapsed, period = 0, 0, 1
            elif shape == 'moving':
                counter, elapsed, period = 1, 0, 1
                current, target, step = -200, 200, 1
            elif shape == 'arrived':
                counter, elapsed, period = rng.getrandbits(32), 0, 0
                current = target
            elif shape == 'wrapped':
                counter, elapsed = 0xffffffff, 1
            struct.pack_into('<II', data, 0xbc, counter, period)
            struct.pack_into('<hhh', data, 0x48, current, target, step)
            previous_exception = rng.choice([0, 0xffffffff, rng.getrandbits(32)])
            cpu.mem_write(0, struct.pack('<I', previous_exception))
            cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
            cpu.mem_write(OBJ, bytes(data))
            callback_result = rng.getrandbits(32)
            # Mutate fields consumed before centering, fields centering owns, and unrelated tail.
            patches = [(offset, rng.randbytes(width)) for offset, width in
                       ((0x08, 4), (0x0e, 2), (0x16, 2), (0x48, 6),
                        (0xbc, 8), (0x154, 4), (0x15c, 4))] if case % 3 else []
            expected_calls.clear()
            native_calls.clear()
            result = original.call(address, eax=OBJ, edx=rng.getrandbits(32),
                                   ebx=rng.getrandbits(32), ecx=rng.getrandbits(32))
            want = bytes(cpu.mem_read(OBJ, SIZE))
            buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
            got = function(c.byref(calls), buffer, SIZE, OBJ, elapsed, previous_exception)
            assert got == result == previous_exception, (name, case, got, result)
            assert len(expected_calls) == len(native_calls) == 1
            assert expected_calls == native_calls, (name, case, expected_calls, native_calls)
            assert bytes(buffer) == want, (name, case)
            assert struct.unpack('<I', bytes(cpu.mem_read(0, 4)))[0] == previous_exception
            total[hex(address)] = total.get(hex(address), 0) + 1
            branches[name + '_' + shape] = branches.get(name + '_' + shape, 0) + 1
            mutations += bool(patches)
        guard_buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
        before = bytes(guard_buffer)
        empty_calls = Calls(Call(), None)
        for missing in (None, c.byref(empty_calls)):
            assert function(missing, guard_buffer, SIZE, OBJ, elapsed, previous_exception) == 0
            assert bytes(guard_buffer) == before
    assert total == {'0x459d60': args.cases, '0x459e00': args.cases}
    return {'complete_original_executions': total, 'branch_fixtures': branches,
            'live_actor_mutation_cases': mutations, 'native_missing_boundary_guard_cases': 4,
            'scope': 'Complete normal 459d60 and 459e00 execute unmodified with real timer, '
                     'quotient, remainder, transition and setters; only final 457890 is supplied. '
                     'Every final call target/eax/edx/ebx/ecx, full 0x160 actor bytes and original '
                     'EAX compare. Random saved FS:[0] tokens restore and return, independently '
                     'of callback EAX; final callback actor mutations remain live. Exceptional '
                     'unwinding and callbacks that alter the saved exception stack local are '
                     'outside this boundary.'}


def main():
    args = vs.parse(__doc__)
    n = vs.build(args, 'title-letter-step', ['title_letter_step.c', 'actor_angle.c', 'actor_fields.c', 'actor_storage.c', 'fixed_point.c', 'rotation.c', 'word_transition.c', 'dword_transition.c', 'ui_slide_setup.c', 'render_geometry.c', 'surface.c', 'render_dispatch.c'])
    for name in ('settle', 'restart'):
        getattr(n, 'vertrix_title_letter_' + name).argtypes = [c.POINTER(c.c_uint8), c.c_size_t, c.c_uint32, c.POINTER(Dimensions), c.c_uint8, c.c_uint8]
    fargs = [c.POINTER(c.c_uint8), c.c_size_t, c.c_uint32, c.POINTER(Dimensions), c.c_uint8, c.c_uint8]
    n.vertrix_title_letter_fight_settle.argtypes = fargs
    n.vertrix_title_letter_fight_restart.argtypes = fargs + [c.POINTER(Fight)]
    n.vertrix_title_letter_wave_count.argtypes = [c.POINTER(c.c_uint8), c.c_size_t, c.c_uint32, c.POINTER(Tables), c.POINTER(Trace), c.POINTER(Dimensions), c.c_uint8, c.c_uint8]
    n.vertrix_title_letter_wave.argtypes = [c.POINTER(c.c_uint8), c.c_size_t, c.c_uint32, c.c_int, c.c_uint32, c.POINTER(Dimensions), c.c_uint8, c.c_uint8, c.POINTER(Fight)]
    n.vertrix_title_letter_fight_count.argtypes = [c.POINTER(c.c_uint8), c.c_size_t, c.c_uint32, c.POINTER(Tables), c.POINTER(Trace), c.POINTER(Dimensions), c.c_uint8, c.c_uint8, c.POINTER(Fight)]
    n.vertrix_title_letter_count.argtypes = [c.POINTER(c.c_uint8), c.c_size_t, c.c_uint32, c.POINTER(Tables), c.POINTER(Trace), c.c_uint32, c.POINTER(Dimensions), c.c_uint8, c.c_uint8, c.POINTER(Voice)]
    original = Original(args.executable)
    cpu = original.cpu
    original.call(0x4b9050)
    rng = random.Random(0x459be0)
    voices = []
    for address in (0x417260, 0x417290):
        cpu.mem_write(address, b'\xc3')
        cpu.hook_add(UC_HOOK_CODE, lambda cpu_, a, size, user: voices.append((a, cpu_.reg_read(UC_X86_REG_EAX))), begin=address, end=address)
    xs = [rng.randrange(-70000, 70000) for _ in range(360)]
    ys = [rng.randrange(-70000, 70000) for _ in range(360)]
    cpu.mem_write(X_TABLE, struct.pack('<360i', *xs))
    cpu.mem_write(Y_TABLE, struct.pack('<360i', *ys))
    tables = Tables((c.c_int32 * 360)(*xs), (c.c_int32 * 360)(*ys))
    cpu.mem_write(VOICE_BASE, struct.pack('<I', 14))
    totals = {'not_due': 0, 'opaque': 0, 'fading': 0, 'parked': 0, 'voices': 0}
    for case in range(args.cases):
        data = bytearray(rng.randbytes(SIZE))
        shape = rng.choice(['not_due', 'opaque', 'fading', 'parked'])
        period = rng.choice([1, 2, 60, 100, rng.randrange(1, 400)])
        elapsed = rng.choice([0, 1, 16, 50, rng.randrange(0, 500)])
        counter = rng.randrange(0, period * 3)
        if shape == 'not_due':
            counter = rng.randrange(0, period)
            elapsed = rng.randrange(0, period - counter) if period - counter > 0 else 0
        elif counter + elapsed < period:
            counter = period
        limit = rng.choice([1, 16, 60, 0x3c, rng.randrange(1, 200)])
        if shape == 'opaque':
            radius = limit + rng.randrange(1, 100)
        elif shape == 'fading':
            radius = rng.randrange(1, limit + 1)
        elif shape == 'parked':
            radius = rng.choice([0, 0, 1, 2, 3])
        else:
            radius = rng.randrange(0, 300)
        if shape == 'parked':
            radius = 0
            step = 0
        struct.pack_into('<I', data, 0xbc, counter)
        struct.pack_into('<I', data, 0xc0, period)
        struct.pack_into('<h', data, 0x30, limit)
        struct.pack_into('<h', data, 0x2a, radius)
        struct.pack_into('<h', data, 0x32, rng.choice([0, 1, 2, 3, 7, -1, rng.randrange(-40, 40)]))
        struct.pack_into('<H', data, 0x24, rng.randrange(360))
        struct.pack_into('<h', data, 0x28, rng.choice([0, 1, 5, -3, 90, -90, rng.randrange(-400, 400)]))
        struct.pack_into('<hhh', data, 0x48, rng.randrange(-300, 300), rng.randrange(-300, 300), rng.choice([0, 1, 4, -4, rng.randrange(-50, 50)]))
        struct.pack_into('<I', data, 0x04, rng.choice([1, 2, rng.getrandbits(32)]))
        struct.pack_into('<I', data, 0x58, rng.choice([1, 2, 3, rng.getrandbits(32)]))
        data[0x44] = rng.randrange(17)
        with_descriptor = rng.random() < 0.5
        data[0x91] = rng.choice([0, 1])
        for offset_ in (0xf4, 0xf8):
            struct.pack_into('<H', data, offset_, rng.choice([0, 1, 7, 16, 24, rng.getrandbits(16) & 0x1ff]))
        descriptor = None
        if with_descriptor:
            dims = (rng.choice([0, 3, 24, rng.getrandbits(16) & 0x1ff]), rng.choice([0, 5, 24, rng.getrandbits(16) & 0x1ff]))
            struct.pack_into('<I', data, 0xb4, DESC)
            cpu.mem_write(DESC, bytes(rng.randbytes(0x40)))
            cpu.mem_write(DESC + 4, struct.pack('<H', dims[0]))
            cpu.mem_write(DESC + 8, struct.pack('<H', dims[1]))
            descriptor = Dimensions(*dims)
        else:
            struct.pack_into('<I', data, 0xb4, 0)
        unscaled, screen_mode = rng.choice([0, 1]), rng.randrange(17)
        cpu.mem_write(SCREEN, bytes(0x300))
        cpu.mem_write(SCREEN + 0x220, bytes([unscaled, screen_mode]))
        cpu.mem_write(0x544070, struct.pack('<I', SCREEN))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        cpu.mem_write(OBJ, bytes(data))
        voices.clear()
        original.call(0x459be0, eax=OBJ)
        want = bytes(cpu.mem_read(OBJ, SIZE))
        buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
        voice = Voice()
        result = n.vertrix_title_letter_count(buffer, SIZE, elapsed, c.byref(tables), c.byref(Trace()), 14, c.byref(descriptor) if descriptor else None, unscaled, screen_mode, c.byref(voice))
        assert result == 1, (case, shape)
        got = bytes(buffer)
        assert got == want, (case, shape, [(hex(i), got[i], want[i]) for i in range(SIZE) if got[i] != want[i]])
        if voice.played:
            assert voices == [(0x417290 if voice.variant else 0x417260, voice.voice & 0xffffffff)], (case, voices, voice.voice, voice.variant)
            totals['voices'] += 1
        else:
            assert voices == [], (case, voices)
        totals[shape] += 1
    sounds = []
    draws = []
    for address in (0x4171e0, 0x417220):
        cpu.mem_write(address, b'\xc3')
        cpu.hook_add(UC_HOOK_CODE, lambda cpu_, a, size, user: sounds.append((a, cpu_.reg_read(UC_X86_REG_EAX), cpu_.reg_read(UC_X86_REG_EDX))), begin=address, end=address)
    cpu.mem_write(0x4826c0, b'\xc3')

    def draw_hook(cpu_, a, size, user):
        modulus = cpu_.reg_read(UC_X86_REG_EDX)
        value = rng.randrange(modulus)
        draws.append((cpu_.reg_read(UC_X86_REG_EAX), modulus, value))
        cpu_.reg_write(UC_X86_REG_EAX, value)
    cpu.hook_add(UC_HOOK_CODE, draw_hook, begin=0x4826c0, end=0x4826c0)
    fight_value = 0x4f81c4
    replay = []
    played = [0]

    @c.CFUNCTYPE(None, c.c_void_p)
    def on_fight(context):
        played[0] += 1

    @c.CFUNCTYPE(c.c_uint32, c.c_void_p, c.c_uint32)
    def on_draw(context, modulus):
        e = replay.pop(0)
        assert e[0] == 0x598d30 and e[1] == modulus, (e, modulus)
        return e[2]
    services = Fight(on_fight, on_draw, None)
    for case, which in ((i, w) for w in ('fight', 'wave') for i in range(args.cases)):
        data = bytearray(rng.randbytes(SIZE))
        shape = rng.choice(['not_due', 'opaque', 'fading', 'parked'])
        period = rng.choice([1, 2, 60, 100, rng.randrange(1, 400)])
        elapsed = rng.choice([0, 1, 16, 50, rng.randrange(0, 500)])
        counter = rng.randrange(0, period * 3)
        if shape == 'not_due':
            counter = rng.randrange(0, period)
            elapsed = rng.randrange(0, period - counter) if period - counter > 0 else 0
        elif counter + elapsed < period:
            counter = period
        limit = rng.choice([1, 16, 60, 0x3c, rng.randrange(1, 200)])
        radius = {'opaque': limit + rng.randrange(1, 100), 'fading': rng.randrange(1, limit + 1), 'parked': 0, 'not_due': rng.randrange(0, 300)}[shape]
        struct.pack_into('<II', data, 0xbc, counter, period)
        struct.pack_into('<h', data, 0x30, limit)
        struct.pack_into('<h', data, 0x2a, radius)
        struct.pack_into('<h', data, 0x32, rng.choice([0, 1, 2, 3, 7, -1, rng.randrange(-40, 40)]))
        struct.pack_into('<H', data, 0x24, rng.randrange(360))
        struct.pack_into('<h', data, 0x28, rng.choice([0, 1, 5, -3, 90, -90, rng.randrange(-400, 400)]))
        struct.pack_into('<hhh', data, 0x48, rng.randrange(-300, 300), rng.randrange(-300, 300), rng.choice([0, 1, 4, -4, rng.randrange(-50, 50)]))
        data[0x44] = rng.randrange(17)
        data[0x91] = rng.choice([0, 1])
        for offset_ in (0xf4, 0xf8):
            struct.pack_into('<H', data, offset_, rng.choice([0, 1, 7, 16, 24, rng.getrandbits(16) & 0x1ff]))
        struct.pack_into('<I', data, 0xb4, 0)
        unscaled, screen_mode = rng.choice([0, 1]), rng.randrange(17)
        cpu.mem_write(SCREEN, bytes(0x300))
        cpu.mem_write(SCREEN + 0x220, bytes([unscaled, screen_mode]))
        cpu.mem_write(0x544070, struct.pack('<I', SCREEN))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        cpu.mem_write(OBJ, bytes(data))
        sounds.clear()
        draws.clear()
        original.call(0x45a290 if which == 'fight' else 0x45a620, eax=OBJ)
        want = bytes(cpu.mem_read(OBJ, SIZE))
        replay[:] = list(draws)
        played[0] = 0
        buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
        if which == 'fight':
            assert n.vertrix_title_letter_fight_count(buffer, SIZE, elapsed, c.byref(tables), c.byref(Trace()), None, unscaled, screen_mode, c.byref(services)) == 1
        else:
            assert n.vertrix_title_letter_wave_count(buffer, SIZE, elapsed, c.byref(tables), c.byref(Trace()), None, unscaled, screen_mode) == 1
        got = bytes(buffer)
        assert got == want, (which, case, shape, [(hex(i), got[i], want[i]) for i in range(SIZE) if got[i] != want[i]])
        if which == 'fight':
            assert played[0] * 2 == len(sounds) and all(e[2] == 0x32 for e in sounds), (case, sounds)
            assert [e[0] for e in sounds] == ([0x4171e0, 0x417220] if sounds else []), (case, sounds)
            totals['fight_count'] = totals.get('fight_count', 0) + 1
            totals['fight_played'] = totals.get('fight_played', 0) + played[0]
        else:
            assert not sounds and not draws, (case, sounds)
            totals['wave_count'] = totals.get('wave_count', 0) + 1
    for handler, name in ((0x459d60, 'settle'), (0x459e00, 'restart'), (0x45a3e0, 'fight_settle'), (0x45a440, 'fight_restart'), (0x45a750, 'wave_first'), (0x45a830, 'wave_second')):
        for case in range(args.cases):
            data = bytearray(rng.randbytes(SIZE))
            period = rng.choice([1, 2, 60, 100, rng.randrange(1, 400)])
            counter = rng.randrange(0, period * 3)
            elapsed = rng.choice([0, 1, 16, 50, rng.randrange(0, 300)])
            struct.pack_into('<II', data, 0xbc, counter, period)
            effect = rng.randrange(-300, 300)
            target = rng.choice([effect, effect + rng.randrange(-30, 30), rng.randrange(-300, 300)])
            struct.pack_into('<hhh', data, 0x48, effect, target, rng.choice([0, 1, 4, 5, -5, rng.randrange(-50, 50)]))
            data[0x44] = rng.randrange(17)
            data[0x91] = rng.choice([0, 1])
            for offset_ in (0xf4, 0xf8):
                struct.pack_into('<H', data, offset_, rng.choice([0, 1, 7, 16, 24, rng.getrandbits(16) & 0x1ff]))
            struct.pack_into('<I', data, 0xb4, 0)
            unscaled, screen_mode = rng.choice([0, 1]), rng.randrange(17)
            cpu.mem_write(SCREEN, bytes(0x300))
            cpu.mem_write(SCREEN + 0x220, bytes([unscaled, screen_mode]))
            cpu.mem_write(0x544070, struct.pack('<I', SCREEN))
            cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
            cpu.mem_write(OBJ, bytes(data))
            flag = rng.choice([0, 1, 1, 2, rng.getrandbits(32)])
            cpu.mem_write(0x532bd0, struct.pack('<I', flag))
            draws.clear()
            original.call(handler, eax=OBJ)
            want = bytes(cpu.mem_read(OBJ, SIZE))
            replay[:] = list(draws)
            buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
            if name.startswith('wave'):
                assert n.vertrix_title_letter_wave(buffer, SIZE, elapsed, int(name == 'wave_second'), flag, None, unscaled, screen_mode, c.byref(services)) == 1
            else:
                extra = (c.byref(services),) if name == 'fight_restart' else ()
                assert getattr(n, 'vertrix_title_letter_' + name)(buffer, SIZE, elapsed, None, unscaled, screen_mode, *extra) == 1
            assert not replay, (name, case, replay)
            got = bytes(buffer)
            assert got == want, (name, case, [(hex(i), got[i], want[i]) for i in range(SIZE) if got[i] != want[i]])
            totals[name] = totals.get(name, 0) + 1
            if struct.unpack_from('<I', want, 0x154)[0] != struct.unpack_from('<I', data, 0x154)[0]:
                totals[name + '_arrivals'] = totals.get(name + '_arrivals', 0) + 1
    full_effect = verify_full_effect(args, n)
    vs.write_report(args, 'title-letter-step', {
        'full_effect_abi': full_effect,
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'State comparisons only for the legacy status APIs: original handlers 0x459be0, 0x459d60, 0x459e00, 0x45a290, 0x45a3e0, 0x45a440, 0x45a620, 0x45a750 and 0x45a830 (with the real 0x4ac500/0x4ac540/0x4ac5b0, 0x4ad060, 0x4ad260, 0x4ad530 and 0x457890/0x4b14c0) runs in the oracle; only the sound players 0x417260/0x417290/0x4171e0/0x417220 and the generator draw 0x4826c0 are observed and returned. The first 0x160 actor bytes, including the handler token at +0x154, compare after every call.'})


if __name__ == '__main__':
    main()
