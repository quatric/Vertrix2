"""Compare the complete original letter step handler 0x459be0 with the native recovery."""
import ctypes as c, random, struct
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_WRITE
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


def verify_full_fight_effect(args, native, wave=False):
    """Compare normal fight or wave ABI and live state at every supplied call."""
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x45a440)
    original_events, native_events = [], []
    running = c.c_uint32()
    running_mutations = []
    returns, patches = [], []
    buffer = None
    total, shapes = {}, {}
    mutation_calls, draw_calls, running_mutation_calls = 0, 0, 0

    def original_boundary(address, eax, edx, ebx, ecx, stack):
        index = len(original_events)
        original_events.append((address, eax, edx, ebx, ecx, bytes(cpu.mem_read(OBJ, SIZE)),
                                struct.unpack('<I', bytes(cpu.mem_read(0x532bd0, 4)))[0] if wave else 0))
        for offset, data in patches[index]:
            cpu.mem_write(OBJ + offset, data)
        if wave and running_mutations[index] is not None:
            cpu.mem_write(0x532bd0, struct.pack('<I', running_mutations[index]))
        return returns[index]

    stubs = Stubs(cpu, original_boundary)
    stubs.add(0x4826c0)
    stubs.add(0x457890)

    @Call
    def boundary(site, context):
        call = site.contents
        index = len(native_events)
        native_events.append((call.target, call.eax, call.edx, call.ebx, call.ecx, bytes(buffer),
                              running.value if wave else 0))
        for offset, data in patches[index]:
            c.memmove(c.addressof(buffer) + offset, data, len(data))
        if wave and running_mutations[index] is not None:
            running.value = running_mutations[index]
        return returns[index]

    calls = Calls(boundary, None)
    entries = ((0x45a750, 'first'), (0x45a830, 'second')) if wave else (
        (0x45a3e0, 'settle'), (0x45a440, 'restart'))
    for address, name in entries:
        function = native.vertrix_title_letter_wave_call if wave else getattr(
            native, 'vertrix_title_letter_fight_' + name + '_call')
        function.argtypes = [c.POINTER(Calls), c.POINTER(c.c_uint8), c.c_size_t,
                             c.c_uint32, c.c_uint32, c.c_uint32, c.c_uint32] + (
                                 [c.c_uint32] if name == 'restart' else [])
        if wave:
            function.argtypes = [c.POINTER(Calls), c.POINTER(c.c_uint8), c.c_size_t,
                                 c.c_uint32, c.c_uint32, c.c_uint32, c.POINTER(c.c_uint32),
                                 c.c_uint32, c.c_uint32, c.c_uint32]
        function.restype = c.c_uint32
        for case in range(args.cases):
            data = bytearray(rng.randbytes(SIZE))
            fixture_shapes = ('not_due', 'moving', 'arrived', 'stopped', 'wrapped', 'random') if wave else (
                'not_due', 'moving', 'arrived', 'wrapped', 'random')
            shape = fixture_shapes[case % len(fixture_shapes)]
            running.value = rng.choice([0, 1, 0xffffffff, rng.getrandbits(32)])
            period, counter = rng.choice([0, 1, 12, 60, rng.getrandbits(32)]), rng.getrandbits(32)
            elapsed = rng.choice([0, 1, 16, 0xffffffff, rng.getrandbits(32)])
            current, target = rng.randrange(-32768, 32768), rng.randrange(-32768, 32768)
            step = rng.choice([-32768, -1, 0, 1, 32767, rng.randrange(-32768, 32768)])
            if shape == 'not_due':
                counter, elapsed, period = 0, 0, 1
            elif shape == 'moving':
                counter, elapsed, period = 1, 0, 1
                current, target, step = -200, 200, 1
                running.value = 1
            elif shape == 'arrived':
                counter, elapsed, period = rng.getrandbits(32), 0, 0
                current = target
                running.value = 1
            elif shape == 'stopped':
                counter, elapsed, period = 1, 0, 1
                running.value = 0
            elif shape == 'wrapped':
                counter, elapsed, period = 0xffffffff, 1, 1
            struct.pack_into('<II', data, 0xbc, counter, period)
            struct.pack_into('<hhh', data, 0x48, current, target, step)
            cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
            if wave:
                cpu.mem_write(0x532bd0, struct.pack('<I', running.value))
            cpu.mem_write(OBJ, bytes(data))
            edx, ebx, ecx = [rng.getrandbits(32) for _ in range(3)]
            # Full-width draw returns deliberately exercise narrowing and wrapped rate +10.
            returns = [rng.choice([0, 1, 0xffffffff, 0xfffffff6, rng.getrandbits(32)])
                       for _ in range(3)]
            patches = [[(offset, rng.randbytes(width)) for offset, width in
                        ((0x08, 4), (0x24, 2), (0x28, 12), (0x48, 6),
                         (0xbc, 8), (0x154, 4), (0x15c, 4))] if case % 3 else []
                       for _ in range(3)]
            running_mutations = [rng.choice([0, 1, 0xffffffff, rng.getrandbits(32)]) if case % 2 else None
                                 for _ in range(3)]
            original_events.clear()
            native_events.clear()
            result = original.call(address, eax=OBJ, edx=edx, ebx=ebx, ecx=ecx)
            want = bytes(cpu.mem_read(OBJ, SIZE))
            buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
            extra = (ecx,) if name == 'restart' else ()
            if wave:
                got = function(c.byref(calls), buffer, SIZE, OBJ, elapsed, int(name == 'second'),
                               c.byref(running), edx, ebx, ecx)
                assert running.value == struct.unpack('<I', bytes(cpu.mem_read(0x532bd0, 4)))[0]
            else:
                got = function(c.byref(calls), buffer, SIZE, OBJ, elapsed, edx, ebx, *extra)
            assert got == result == returns[len(original_events) - 1], (name, case, got, result)
            assert original_events == native_events, (name, case, original_events, native_events)
            assert original_events[-1][0] == 0x457890
            assert bytes(buffer) == want, (name, case)
            total[hex(address)] = total.get(hex(address), 0) + 1
            shapes[name + '_' + shape] = shapes.get(name + '_' + shape, 0) + 1
            mutation_calls += sum(bool(patches[i]) for i in range(len(original_events)))
            draw_calls += sum(event[0] == 0x4826c0 for event in original_events)
            if wave:
                running_mutation_calls += sum(running_mutations[i] is not None
                                              for i in range(len(original_events)))
        guard_buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
        before = bytes(guard_buffer)
        before_running = running.value
        empty_calls = Calls(Call(), None)
        for missing in (None, c.byref(empty_calls)):
            if wave:
                assert function(missing, guard_buffer, SIZE, OBJ, elapsed, int(name == 'second'),
                                c.byref(running), edx, ebx, ecx) == 0
            else:
                assert function(missing, guard_buffer, SIZE, OBJ, elapsed, edx, ebx, *extra) == 0
            assert bytes(guard_buffer) == before
        if wave:
            assert function(c.byref(calls), guard_buffer, SIZE, OBJ, elapsed, 2,
                            c.byref(running), edx, ebx, ecx) == 0
            assert function(c.byref(calls), guard_buffer, SIZE, OBJ, elapsed, 0,
                            None, edx, ebx, ecx) == 0
            assert bytes(guard_buffer) == before
            assert running.value == before_running
    assert total == {hex(address): args.cases for address, _ in entries}
    if args.cases >= 5:
        assert draw_calls > 0 and mutation_calls > 0
    return {'complete_original_executions': total, 'branch_fixtures': shapes,
            'draw_boundary_calls': draw_calls, 'live_actor_mutation_calls': mutation_calls,
            'live_running_mutation_calls': running_mutation_calls,
            'native_missing_boundary_guard_cases': 8 if wave else 4,
            'scope': ('Complete normal 45a3e0 and 45a440 run unchanged with real timer, quotient, '
                     'remainder, signed transition and setters. Only draws 4826c0 and final '
                     'centering 457890 are supplied; every target/eax/edx/ebx/ecx, entire 0x160 '
                     'actor before each call and after completion, and final original EAX '
                     'compare. Arbitrary caller registers, wrapped timer values, full-width draw '
                     'returns and live actor mutations at either draw and centering are covered. '
                     'Callbacks preserve input registers other than returned EAX; faults and '
                     'exceptional unwinding remain outside the normal boundary.') if not wave else
                     'Complete normal 45a750 and 45a830 execute unchanged. Only draws 4826c0 and '
                     'final 457890 are supplied; target/eax/edx/ebx/ecx, complete actor state and '
                     'live running 532bd0 state compare before every callback and after completion, '
                     'along with final EAX. Running is read only once after due timer consumption; '
                     'callback mutations to running and actor do not re-enter that branch. '
                     'Faults and register-clobbering callbacks remain outside this boundary.'}


def verify_full_count(args, native):
    """Count ABI with real arithmetic and live voice/final-center boundaries."""
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x459be0)
    xs, ys = [[c.c_int32(rng.getrandbits(32)).value for _ in range(360)] for _ in range(2)]
    cpu.mem_write(X_TABLE, struct.pack('<360i', *xs))
    cpu.mem_write(Y_TABLE, struct.pack('<360i', *ys))
    tables = Tables((c.c_int32 * 360)(*xs), (c.c_int32 * 360)(*ys))
    voice_base = c.c_uint32()
    original_events, native_events = [], []
    patches, base_mutations, returns = [], [], []
    buffer = None

    def original_boundary(address, eax, edx, ebx, ecx, stack):
        index = len(original_events)
        original_events.append((address, eax, edx, ebx, ecx, bytes(cpu.mem_read(OBJ, SIZE)),
                                struct.unpack('<I', bytes(cpu.mem_read(VOICE_BASE, 4)))[0]))
        for offset, data in patches[index]:
            cpu.mem_write(OBJ + offset, data)
        if base_mutations[index] is not None:
            cpu.mem_write(VOICE_BASE, struct.pack('<I', base_mutations[index]))
        return returns[index]

    stubs = Stubs(cpu, original_boundary)
    for address in (0x417260, 0x417290, 0x457890):
        stubs.add(address)

    @Call
    def boundary(site, context):
        call = site.contents
        index = len(native_events)
        native_events.append((call.target, call.eax, call.edx, call.ebx, call.ecx,
                              bytes(buffer), voice_base.value))
        for offset, data in patches[index]:
            c.memmove(c.addressof(buffer) + offset, data, len(data))
        if base_mutations[index] is not None:
            voice_base.value = base_mutations[index]
        return returns[index]

    calls = Calls(boundary, None)
    function = native.vertrix_title_letter_count_call
    function.argtypes = [c.POINTER(Calls), c.POINTER(c.c_uint8), c.c_size_t, c.c_uint32,
                         c.c_uint32, c.POINTER(Tables), c.POINTER(c.c_uint32), c.c_uint32]
    function.restype = c.c_uint32
    shapes, voices = {}, {}
    mutations, base_mutation_count, completed = 0, 0, 0
    for case in range(args.cases):
        data = bytearray(rng.randbytes(SIZE))
        shape = ('not_due', 'opaque', 'fading', 'parked_other', 'parked_one',
                 'wrapped', 'signed', 'zero_rate')[case % 8]
        period = rng.choice([1, 2, 60, 100, rng.randrange(1, 400)])
        counter, elapsed = rng.randrange(period * 3), rng.randrange(500)
        if counter + elapsed < period:
            counter = period
        limit = rng.choice([1, 16, 60, rng.randrange(1, 200)])
        radius, angle_rate = rng.randrange(1, limit + 1), rng.choice([0, 1, -3, 90, -90, 32767, -32768])
        mode = rng.choice([0, 1, 2, rng.getrandbits(32)])
        if shape == 'not_due':
            counter, elapsed, period = 0, 0, 1
        elif shape == 'opaque':
            radius = limit + rng.randrange(1, 100)
        elif shape.startswith('parked'):
            radius = 0
            mode = 1 if shape == 'parked_one' else rng.choice([0, 2, 0xffffffff])
        elif shape == 'wrapped':
            counter, elapsed, period = 0xffffffff, 1, 1
        elif shape == 'signed':
            radius, limit = rng.choice([-32768, -1, 0, 1, 32767]), rng.choice([-32768, -1, 1, 32767])
        elif shape == 'zero_rate':
            counter, elapsed, period, angle_rate = rng.getrandbits(32), 0, 0, 0
        struct.pack_into('<II', data, 0xbc, counter, period)
        struct.pack_into('<I', data, 4, mode)
        struct.pack_into('<I', data, 0x58, rng.getrandbits(32))
        struct.pack_into('<Hh', data, 0x24, rng.randrange(360), rng.randrange(-32768, 32768))
        struct.pack_into('<hh', data, 0x28, angle_rate, radius)
        struct.pack_into('<hh', data, 0x30, limit, rng.randrange(-32768, 32768))
        struct.pack_into('<hhh', data, 0x48, rng.randrange(-32768, 32768),
                         rng.randrange(-32768, 32768), rng.randrange(-32768, 32768))
        previous_exception = rng.choice([0, 0xffffffff, rng.getrandbits(32)])
        voice_base.value = rng.getrandbits(32)
        cpu.mem_write(VOICE_BASE, struct.pack('<I', voice_base.value))
        cpu.mem_write(0, struct.pack('<I', previous_exception))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        cpu.mem_write(OBJ, bytes(data))
        patches = [[(offset, rng.randbytes(width)) for offset, width in
                    ((4, 8), (0x24, 16), (0x44, 1), (0x48, 6), (0x58, 4),
                     (0xbc, 8), (0x154, 4), (0x15c, 4))] if case % 3 else [] for _ in range(2)]
        base_mutations = [rng.getrandbits(32) if case % 2 else None for _ in range(2)]
        returns = [rng.getrandbits(32) for _ in range(2)]
        original_events.clear()
        native_events.clear()
        result = original.call(0x459be0, eax=OBJ, edx=rng.getrandbits(32),
                               ebx=rng.getrandbits(32), ecx=rng.getrandbits(32))
        want = bytes(cpu.mem_read(OBJ, SIZE))
        buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
        got = function(c.byref(calls), buffer, SIZE, OBJ, elapsed, c.byref(tables),
                       c.byref(voice_base), previous_exception)
        assert got == result == previous_exception, (shape, case, got, result)
        assert native_events == original_events, (shape, case, native_events, original_events)
        assert original_events[-1][0] == 0x457890
        assert bytes(buffer) == want, (shape, case)
        assert voice_base.value == struct.unpack('<I', bytes(cpu.mem_read(VOICE_BASE, 4)))[0]
        assert struct.unpack('<I', bytes(cpu.mem_read(0, 4)))[0] == previous_exception
        for event in original_events:
            if event[0] != 0x457890:
                key = hex(event[0])
                voices[key] = voices.get(key, 0) + 1
        shapes[shape] = shapes.get(shape, 0) + 1
        mutations += sum(bool(patches[i]) for i in range(len(original_events)))
        base_mutation_count += sum(base_mutations[i] is not None for i in range(len(original_events)))
        completed += 1
    assert completed == args.cases
    if args.cases >= 8:
        assert set(voices) == {'0x417260', '0x417290'}
    guard = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
    before = bytes(guard)
    empty_calls = Calls(Call(), None)
    for missing in (None, c.byref(empty_calls)):
        assert function(missing, guard, SIZE, OBJ, elapsed, c.byref(tables),
                        c.byref(voice_base), previous_exception) == 0
        assert bytes(guard) == before
    for table_arg, base_arg, size_arg in ((None, c.byref(voice_base), SIZE),
                                          (c.byref(tables), None, SIZE),
                                          (c.byref(tables), c.byref(voice_base), 0x157)):
        assert function(c.byref(calls), guard, size_arg, OBJ, elapsed, table_arg, base_arg,
                        previous_exception) == 0
        assert bytes(guard) == before
    return {'complete_original_executions': {'0x459be0': completed}, 'branch_fixtures': shapes,
            'voice_calls': voices, 'live_actor_mutation_calls': mutations,
            'live_voice_base_mutation_calls': base_mutation_count,
            'native_missing_boundary_guard_cases': 2, 'native_missing_input_guard_cases': 3,
            'scope': 'Complete normal 459be0 executes unchanged with real timer, quotient, remainder, '
                     'angle/orbit, signed transition and setters; only voice 417260/417290 and '
                     'final 457890 are supplied. Every call register and complete 0x160 actor/live '
                     'voice-base state compare before callbacks and after completion. EAX returns '
                     'random saved FS:[0], independent of callback results; SEH chain restores. '
                     'Fixtures include arbitrary signed radius/limit/step, full-width factors, '
                     'wrapped timers and full-width quotient with zero angle rate. Faulting '
                     'division/table inputs, callback register clobbers and exceptional unwinding '
                     'or mutations to the saved exception stack local remain outside the boundary.'}


def verify_full_family_count(args, native, fight=False):
    """Fight/wave count ABI with real arithmetic and mutable sound/final boundaries."""
    original = Original(args.executable)
    cpu = original.cpu
    address = 0x45a290 if fight else 0x45a620
    rng = random.Random(address)
    xs, ys = [[c.c_int32(rng.getrandbits(32)).value for _ in range(360)] for _ in range(2)]
    cpu.mem_write(X_TABLE, struct.pack('<360i', *xs))
    cpu.mem_write(Y_TABLE, struct.pack('<360i', *ys))
    tables = Tables((c.c_int32 * 360)(*xs), (c.c_int32 * 360)(*ys))
    voice_base = c.c_uint32()
    original_events, native_events = [], []
    patches, base_mutations, returns = [], [], []
    buffer = None
    callback_errors = []

    def original_boundary(address, eax, edx, ebx, ecx, stack):
        index = len(original_events)
        original_events.append((address, eax, edx, ebx, ecx, bytes(cpu.mem_read(OBJ, SIZE)),
                                struct.unpack('<I', bytes(cpu.mem_read(0x4f81c4, 4)))[0]))
        for offset, data in patches[index]:
            cpu.mem_write(OBJ + offset, data)
        if base_mutations[index] is not None:
            cpu.mem_write(0x4f81c4, struct.pack('<I', base_mutations[index]))
        return returns[index]

    stubs = Stubs(cpu, original_boundary)
    for target in (0x4171e0, 0x417220, 0x457890):
        stubs.add(target)

    @Call
    def boundary(site, context):
        call = site.contents
        index = len(native_events)
        if index >= len(returns):
            callback_errors.append(('extra_callback', index))
            return 0
        native_events.append((call.target, call.eax, call.edx, call.ebx, call.ecx,
                              bytes(buffer), voice_base.value))
        for offset, data in patches[index]:
            c.memmove(c.addressof(buffer) + offset, data, len(data))
        if base_mutations[index] is not None:
            voice_base.value = base_mutations[index]
        return returns[index]

    calls = Calls(boundary, None)
    function = (native.vertrix_title_letter_fight_count_call if fight
                else native.vertrix_title_letter_wave_count_call)
    function.argtypes = [c.POINTER(Calls), c.POINTER(c.c_uint8), c.c_size_t, c.c_uint32,
                         c.c_uint32, c.POINTER(Tables)] + ([c.POINTER(c.c_uint32)] if fight else []) + [c.c_uint32, c.c_uint32]
    function.restype = c.c_uint32
    shapes, voices = {}, {}
    mutations, base_mutation_count, completed = 0, 0, 0
    for case in range(args.cases):
        data = bytearray(rng.randbytes(SIZE))
        shape = ('not_due', 'opaque', 'fading', 'parked_other', 'parked_one',
                 'wrapped', 'signed', 'zero_rate')[case % 8]
        period = rng.choice([1, 2, 60, 100, rng.randrange(1, 400)])
        counter, elapsed = rng.randrange(period * 3), rng.randrange(500)
        if counter + elapsed < period:
            counter = period
        limit = rng.choice([1, 16, 60, rng.randrange(1, 200)])
        radius, angle_rate = rng.randrange(1, limit + 1), rng.choice([0, 1, -3, 90, -90, 32767, -32768])
        mode = rng.choice([0, 1, 2, rng.getrandbits(32)])
        if shape == 'not_due':
            counter, elapsed, period = 0, 0, 1
        elif shape == 'opaque':
            radius = limit + rng.randrange(1, 100)
        elif shape.startswith('parked'):
            radius = 0
            mode = 1 if shape == 'parked_one' else rng.choice([0, 2, 0xffffffff])
        elif shape == 'wrapped':
            counter, elapsed, period = 0xffffffff, 1, 1
        elif shape == 'signed':
            radius, limit = rng.choice([-32768, -1, 0, 1, 32767]), rng.choice([-32768, -1, 1, 32767])
        elif shape == 'zero_rate':
            counter, elapsed, period, angle_rate = rng.getrandbits(32), 0, 0, 0
        struct.pack_into('<II', data, 0xbc, counter, period)
        struct.pack_into('<I', data, 4, mode)
        struct.pack_into('<I', data, 0x58, rng.getrandbits(32))
        struct.pack_into('<Hh', data, 0x24, rng.randrange(360), rng.randrange(-32768, 32768))
        struct.pack_into('<hh', data, 0x28, angle_rate, radius)
        struct.pack_into('<hh', data, 0x30, limit, rng.randrange(-32768, 32768))
        struct.pack_into('<hhh', data, 0x48, rng.randrange(-32768, 32768),
                         rng.randrange(-32768, 32768), rng.randrange(-32768, 32768))
        previous_exception = rng.choice([0, 0xffffffff, rng.getrandbits(32)])
        voice_base.value = rng.getrandbits(32)
        cpu.mem_write(0x4f81c4, struct.pack('<I', voice_base.value))
        cpu.mem_write(0, struct.pack('<I', previous_exception))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        cpu.mem_write(OBJ, bytes(data))
        patches = [[(offset, rng.randbytes(width)) for offset, width in
                    ((4, 8), (0x24, 16), (0x44, 1), (0x48, 6), (0x58, 4),
                     (0xbc, 8), (0x154, 4), (0x15c, 4))] if case % 3 else [] for _ in range(3)]
        base_mutations = [rng.getrandbits(32) if case % 2 else None for _ in range(3)]
        returns = [rng.getrandbits(32) for _ in range(3)]
        original_events.clear()
        native_events.clear()
        callback_errors.clear()
        edx, ebx, ecx = (rng.getrandbits(32) for _ in range(3))
        result = original.call(address, eax=OBJ, edx=edx, ebx=ebx, ecx=ecx)
        want = bytes(cpu.mem_read(OBJ, SIZE))
        buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
        tail = ([c.byref(voice_base)] if fight else []) + [edx, ebx]
        got = function(c.byref(calls), buffer, SIZE, OBJ, elapsed, c.byref(tables), *tail)
        assert not callback_errors, (case, callback_errors)
        assert got == result == returns[len(original_events) - 1], (shape, case, got, result)
        assert native_events == original_events, (shape, case, native_events, original_events)
        assert original_events[-1][0] == 0x457890
        assert bytes(buffer) == want, (shape, case)
        assert voice_base.value == struct.unpack('<I', bytes(cpu.mem_read(0x4f81c4, 4)))[0]
        assert struct.unpack('<I', bytes(cpu.mem_read(0, 4)))[0] == previous_exception
        for event in original_events:
            if event[0] != 0x457890:
                key = hex(event[0])
                voices[key] = voices.get(key, 0) + 1
        shapes[shape] = shapes.get(shape, 0) + 1
        mutations += sum(bool(patches[i]) for i in range(len(original_events)))
        base_mutation_count += sum(base_mutations[i] is not None for i in range(len(original_events)))
        completed += 1
    assert completed == args.cases
    if args.cases >= 8:
        assert set(voices) == ({'0x4171e0', '0x417220'} if fight else set())
    guard = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
    before = bytes(guard)
    empty_calls = Calls(Call(), None)
    tail = ([c.byref(voice_base)] if fight else []) + [edx, ebx]
    for missing in (None, c.byref(empty_calls)):
        assert function(missing, guard, SIZE, OBJ, elapsed, c.byref(tables), *tail) == 0
        assert bytes(guard) == before
    for table_arg, size_arg in ((None, SIZE), (c.byref(tables), 0x157)):
        assert function(c.byref(calls), guard, size_arg, OBJ, elapsed, table_arg, *tail) == 0
        assert bytes(guard) == before
    if fight:
        assert function(c.byref(calls), guard, SIZE, OBJ, elapsed, c.byref(tables), None, edx, ebx) == 0
        assert bytes(guard) == before
    return {'complete_original_executions': {hex(address): completed}, 'branch_fixtures': shapes,
            'sound_calls': voices, 'live_actor_mutation_calls': mutations,
            'live_sound_base_mutation_calls': base_mutation_count,
            'native_missing_boundary_guard_cases': 2, 'native_missing_input_guard_cases': 3 if fight else 2,
            'exact_callback_register_state_comparisons': sum(voices.values()) + completed,
            'scope': 'Full normal fight/wave count executes real timer/quotient/remainder, '
                     'rotation/orbit/transitions and setters; only sounds and final center supplied. '
                     'Every callback register and independent 0x160 actor/sound-base state compare '
                     'before callbacks and after completion. Returns final center EAX. First fight '
                     'sound mutations affect the second live sound-base read. Signed inputs, '
                     'wrapped timers, full-width factors and zero angle rate covered. Faulting '
                     'inputs, callback register clobbers and exception behavior outside boundary.'}


def verify_full_family_fly(args, native, fight=False):
    original = Original(args.executable)
    cpu = original.cpu
    address = 0x45a4f0 if fight else 0x45a910
    rng = random.Random(address)
    factors = [[c.c_int32(rng.getrandbits(32)).value for _ in range(360)] for _ in range(2)]
    for base, values in zip((X_TABLE, Y_TABLE), factors):
        cpu.mem_write(base, struct.pack('<360i', *values))
    tables = Tables(*[(c.c_int32 * 360)(*values) for values in factors])
    from original import STACK
    frame = STACK - 4
    Write = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint, c.c_uint32, c.c_void_p)
    function = native.vertrix_title_letter_fight_fly_call if fight else native.vertrix_title_letter_wave_fly_call
    function.argtypes = [c.POINTER(Calls), c.POINTER(c.c_uint8), c.c_size_t,
                         c.c_uint32, c.c_uint32, c.c_uint32, c.POINTER(Tables)] + ([Write, c.c_void_p] if fight else [])
    function.restype = c.c_uint32
    buffer = None
    flag = c.c_uint32()
    patches = []
    dimensions = (0, 0)
    callback_return = 0
    original_events, native_events, errors = [], [], []

    def flag_write(cpu, access, address, width, value, context):
        original_events.append(('write', address, width, value & 0xffffffff))
    cpu.hook_add(UC_HOOK_MEM_WRITE, flag_write, begin=0x532a40, end=0x532a43)

    def original_boundary(address, eax, edx, ebx, ecx, stack):
        original_events.append(('call', address, eax, edx, ebx, ecx,
                                bytes(cpu.mem_read(OBJ, SIZE)), int.from_bytes(cpu.mem_read(0x532a40, 4), 'little')))
        for offset, data in patches:
            cpu.mem_write(OBJ + offset, data)
        cpu.mem_write(0x532a40, struct.pack('<I', changed_flag))
        cpu.mem_write(edx, struct.pack('<I', dimensions[0]))
        cpu.mem_write(ebx, struct.pack('<I', dimensions[1]))
        return callback_return
    stubs = Stubs(cpu, original_boundary)
    stubs.add(0x4b14c0)

    @Call
    def boundary(site, context):
        call = site.contents
        native_events.append(('call', call.target, call.eax, call.edx, call.ebx, call.ecx,
                              bytes(buffer), flag.value))
        if call.target != 0x4b14c0:
            errors.append(('target', call.target))
            return 0
        for offset, data in patches:
            c.memmove(c.addressof(buffer) + offset, data, len(data))
        flag.value = changed_flag
        call.out_value, call.out_ebx = dimensions
        return callback_return

    @Write
    def write(address, width, value, context):
        native_events.append(('write', address, width, value))
        if address != 0x532a40 or width != 4:
            errors.append(('write', address, width))
            return 0
        flag.value = value
        return 1

    calls = Calls(boundary, None)
    shapes, returns_seen = {}, {}
    callback_count = mutations = completed = 0
    for case in range(args.cases):
        shape = ('not_due', 'fading', 'opaque', 'full', 'wrapped', 'signed', 'zero_rate')[case % 7]
        data = bytearray(rng.randbytes(SIZE))
        period, counter, elapsed = rng.randrange(1, 400), rng.randrange(400), rng.randrange(400)
        if counter + elapsed < period:
            counter = period
        limit = rng.randrange(1, 300)
        radius, rate = rng.randrange(0, limit), rng.choice([0, 1, -3, 32767, -32768])
        if shape == 'not_due':
            counter, elapsed, period = 0, 0, 1
        elif shape == 'opaque': radius = limit + 1
        elif shape == 'full': radius = limit
        elif shape == 'wrapped': counter, elapsed, period = 0xffffffff, 1, 1
        elif shape == 'signed':
            radius, limit = rng.choice([-32768, -1, 0, 1, 32767]), rng.choice([-32768, -1, 1, 32767])
        elif shape == 'zero_rate': counter, elapsed, period, rate = rng.getrandbits(32), 0, 0, 0
        struct.pack_into('<II', data, 0xbc, counter, period)
        struct.pack_into('<Hh', data, 0x24, rng.randrange(360), rng.randrange(-32768, 32768))
        struct.pack_into('<hh', data, 0x28, rate, radius)
        struct.pack_into('<hh', data, 0x30, limit, rng.randrange(-32768, 32768))
        struct.pack_into('<hhh', data, 0x48, rng.randrange(-32768, 32768), rng.randrange(-32768, 32768), rng.randrange(-32768, 32768))
        patches = [(offset, rng.randbytes(width)) for offset, width in
                   ((8, 4), (0x24, 16), (0x48, 6), (0xbc, 8), (0x154, 4), (0x15c, 4))] if case % 2 else []
        if case % 3:
            patches.append((0x44, bytes([0 if case % 3 == 1 else rng.randrange(1, 256)])))
        dimensions = tuple(rng.choice([0, 0xffffffff, 0x80000000, rng.getrandbits(32)]) for _ in range(2))
        callback_return = rng.getrandbits(32)
        flag.value, changed_flag = rng.getrandbits(32), rng.getrandbits(32)
        cpu.mem_write(0x532a40, struct.pack('<I', flag.value))
        cpu.mem_write(0x5bd834, struct.pack('<I', elapsed))
        cpu.mem_write(OBJ, bytes(data))
        original_events.clear(); native_events.clear(); errors.clear(); stubs.log.clear()
        expected = original.call(address, eax=OBJ, edx=rng.getrandbits(32), ebx=rng.getrandbits(32), ecx=rng.getrandbits(32))
        buffer = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
        tail = [write, None] if fight else []
        got = function(c.byref(calls), buffer, SIZE, OBJ, frame, elapsed, c.byref(tables), *tail)
        assert not errors, (case, errors)
        assert got == expected, (shape, case, got, expected)
        assert native_events == original_events, (shape, case, native_events, original_events)
        assert bytes(buffer) == bytes(cpu.mem_read(OBJ, SIZE)), (shape, case)
        assert flag.value == int.from_bytes(cpu.mem_read(0x532a40, 4), 'little'), case
        key = 'object' if expected == OBJ else str(expected)
        returns_seen[key] = returns_seen.get(key, 0) + 1
        shapes[shape] = shapes.get(shape, 0) + 1
        callback_count += len(stubs.log)
        mutations += bool(patches) and bool(stubs.log)
        completed += 1
    assert completed == args.cases
    if args.cases >= 100:
        assert set(returns_seen) == {'0', '1', 'object'}, returns_seen
    guard = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
    before = bytes(guard)
    empty_calls = Calls(Call(), None)
    for runtime in (None, c.byref(empty_calls)):
        assert function(runtime, guard, SIZE, OBJ, frame, elapsed, c.byref(tables), *tail) == 0
        assert bytes(guard) == before
    for size_arg, tables_arg in ((0x157, c.byref(tables)), (SIZE, None)):
        assert function(c.byref(calls), guard, size_arg, OBJ, frame, elapsed, tables_arg, *tail) == 0
        assert bytes(guard) == before
    if fight:
        assert function(c.byref(calls), guard, SIZE, OBJ, frame, elapsed, c.byref(tables), Write(), None) == 0
        assert bytes(guard) == before
    return {'complete_original_executions': {hex(address): completed}, 'branch_fixtures': shapes,
            'exact_measure_callback_register_state_comparisons': callback_count,
            'live_actor_mutation_cases': mutations, 'return_counts': returns_seen,
            'native_missing_boundary_input_guards': 5 if fight else 4,
            'scope': 'Complete normal fly handlers execute real timer, rotation/orbit and signed '
                     'transition helpers, with only 0x4b14c0 supplied. Exact measurement registers, '
                     'full-width output dimensions, independent 0x160 actor/flag state before and '
                     'after callbacks, late actor mutation reads and exact original EAX compare. '
                     'Fight global writes compare in order. Arithmetic faults, callback register '
                     'clobbers and exceptional execution remain outside the normal boundary.'}


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
    full_fight_effect = verify_full_fight_effect(args, n)
    full_wave = verify_full_fight_effect(args, n, wave=True)
    full_count = verify_full_count(args, n)
    full_fight_count = verify_full_family_count(args, n, fight=True)
    full_wave_count = verify_full_family_count(args, n)
    full_fight_fly = verify_full_family_fly(args, n, fight=True)
    full_wave_fly = verify_full_family_fly(args, n)
    vs.write_report(args, 'title-letter-step', {
        'full_effect_abi': full_effect,
        'full_fight_effect_abi': full_fight_effect,
        'full_wave_abi': full_wave,
        'full_count_abi': full_count,
        'full_fight_count_abi': full_fight_count,
        'full_wave_count_abi': full_wave_count,
        'full_fight_fly_abi': full_fight_fly,
        'full_wave_fly_abi': full_wave_fly,
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'State comparisons only for the legacy status APIs: original handlers 0x459be0, 0x459d60, 0x459e00, 0x45a290, 0x45a3e0, 0x45a440, 0x45a620, 0x45a750 and 0x45a830 (with the real 0x4ac500/0x4ac540/0x4ac5b0, 0x4ad060, 0x4ad260, 0x4ad530 and 0x457890/0x4b14c0) runs in the oracle; only the sound players 0x417260/0x417290/0x4171e0/0x417220 and the generator draw 0x4826c0 are observed and returned. The first 0x160 actor bytes, including the handler token at +0x154, compare after every call.'})


if __name__ == '__main__':
    main()
