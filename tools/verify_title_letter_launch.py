"""Compare the original letter launch 0x45a0c0 and handlers 0x45a1c0 and 0x45a4f0 with the native recovery."""
import ctypes as c, random, struct
from unicorn import UC_HOOK_CODE, UC_HOOK_MEM_READ, UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_EDX
from original import Original, STACK
from oracle_kit import Stubs
from verify_call_glue import Calls, Call
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


def verify_full_launch(args, native):
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x45a0c1)
    Read = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint, c.POINTER(c.c_uint32), c.c_void_p)
    function = native.vertrix_title_letter_launch_call
    function.argtypes = [c.POINTER(Calls), c.POINTER(c.c_uint8), c.c_size_t, c.c_uint32, Read, c.c_void_p]
    function.restype = c.c_uint32
    regions = ((0x4f81b0,4), (0x532b9c,4), (0x533160,40), (0x598dc4,56))
    host = {}
    buffer = None
    patches, returns = [], []
    global_patches = []
    original_events, native_events, errors = [], [], []
    callbacks = reads = completed = negative_lookups = 0

    def snapshot(read_actor,read_mem):
        return read_actor(), tuple(read_mem(a,w) for a,w in regions)
    def oracle(target,eax,edx,ebx,ecx,stack):
        index = len(stubs.log)-1
        original_events.append(('call',target,eax,edx,ebx,ecx,
                                *snapshot(lambda:bytes(cpu.mem_read(OBJ,SIZE)),lambda a,w:bytes(cpu.mem_read(a,w)))))
        for offset,data in patches[index]: cpu.mem_write(OBJ+offset,data)
        for at,data in global_patches[index]: cpu.mem_write(at,data)
        return returns[index]
    stubs = Stubs(cpu,oracle)
    for target in(0x484680,0x484700,0x482a60):stubs.add(target)
    def track(cpu,access,address,width,value,context):
        original_events.append(('read',address,width,int.from_bytes(cpu.mem_read(address,width),'little')))
    for base,size in regions[:3]:cpu.hook_add(UC_HOOK_MEM_READ,track,begin=base,end=base+size-1)

    def locate(address,width):
        for base,size in regions:
            if base <= address and address+width <= base+size:return host[base],address-base
        return None,0
    @Call
    def boundary(site,context):
        x=site.contents
        index=sum(e[0]=='call' for e in native_events)
        native_events.append(('call',x.target,x.eax,x.edx,x.ebx,x.ecx,
                              *snapshot(lambda:bytes(buffer),lambda a,w:bytes(host[a]))))
        if index>=4:errors.append(('extra_call',index));return 0
        for offset,data in patches[index]:c.memmove(c.addressof(buffer)+offset,data,len(data))
        for at,data in global_patches[index]:
            memory,offset=locate(at,len(data))
            if memory is None:errors.append(('mutation',at));return 0
            memory[offset:offset+len(data)]=data
        return returns[index]
    @Read
    def read(address,width,value,context):
        memory,offset=locate(address,width)
        if memory is None or width!=4:errors.append(('read',address,width));return 0
        value[0]=int.from_bytes(memory[offset:offset+width],'little')
        native_events.append(('read',address,width,value[0]));return 1
    calls=Calls(boundary,None)
    for case in range(args.cases):
        data=bytearray(rng.randbytes(SIZE))
        struct.pack_into('<hh',data,8,rng.randrange(-32768,32768),rng.randrange(-32768,32768))
        host={a:bytearray(rng.randbytes(w)) for a,w in regions}
        index=rng.choice([0,1,7,0xffffffff]);host[0x4f81b0][:]=index.to_bytes(4,'little')
        for at,memory in host.items():cpu.mem_write(at,bytes(memory))
        cpu.mem_write(OBJ,bytes(data))
        patches=[[(off,rng.randbytes(w)) for off,w in((8,4),(0x24,16),(0xbc,8),(0x64,12),(0x154,4),(0x15c,4))] for _ in range(4)]
        global_patches=[]
        for _ in range(4):
            changed_index=rng.choice([0,1,7,0xffffffff])
            global_patches.append([(0x4f81b0,changed_index.to_bytes(4,'little')),(0x532b9c,rng.randbytes(4)),
                                   (0x533160,rng.randbytes(40)),(0x598dc4,rng.randbytes(56))])
        returns=[rng.getrandbits(32) for _ in range(4)]
        original_events.clear();native_events.clear();errors.clear();stubs.log.clear()
        expected=original.call(0x45a0c0,eax=OBJ,edx=rng.getrandbits(32),ebx=rng.getrandbits(32),ecx=rng.getrandbits(32))
        buffer=(c.c_uint8*SIZE).from_buffer_copy(bytes(data))
        got=function(c.byref(calls),buffer,SIZE,OBJ,read,None)
        assert not errors,(case,errors)
        assert got==expected==OBJ,(case,got,expected)
        assert native_events==original_events,(case,[(i,a[:6],b[:6]) for i,(a,b) in enumerate(zip(native_events,original_events)) if a!=b])
        assert bytes(buffer)==bytes(cpu.mem_read(OBJ,SIZE)),case
        assert all(bytes(mem)==bytes(cpu.mem_read(a,len(mem))) for a,mem in host.items()),case
        assert len(stubs.log)==4
        callbacks+=len(stubs.log);reads+=sum(e[0]=='read' for e in original_events)
        negative_lookups+=sum(e[:2]==('read',0x533160) for e in original_events)
        completed+=1
    assert completed==args.cases and callbacks==4*completed and reads==6*completed
    guard=(c.c_uint8*SIZE).from_buffer_copy(bytes(data));before=bytes(guard)
    for runtime,reader,size in((None,read,SIZE),(c.byref(Calls(Call(),None)),read,SIZE),
                              (c.byref(calls),Read(),SIZE),(c.byref(calls),read,0x157)):
        assert function(runtime,guard,size,OBJ,reader,None)==0
        assert bytes(guard)==before
    return {'complete_original_executions':{'0x45a0c0':completed},
            'exact_callback_register_state_comparisons':callbacks,'ordered_raw_global_reads':reads,
            'wrapping_negative_sound_entry_reads':negative_lookups,'native_missing_boundary_input_guards':4,
            'scope':'Complete normal launch with original distance/heading/sound runtime boundaries. '
                    'Every call register and independent actor/math-scratch/sound-global state compares '
                    'before and after callbacks. Callback mutations drive live position, sound index, '
                    'volume/table rereads; full-width geometry returns verify word truncation and '
                    'heading modulo. Exact original EAX actor handle compares. Faulting runtime '
                    'geometry and register-clobbering callbacks remain outside normal boundary.'}


def verify_full_fly_out(args, native):
    fight = False
    original = Original(args.executable)
    cpu = original.cpu
    address = 0x45a1c0
    rng = random.Random(address)
    factors = [[c.c_int32(rng.getrandbits(32)).value for _ in range(360)] for _ in range(2)]
    for base, values in zip((X_TABLE, Y_TABLE), factors):
        cpu.mem_write(base, struct.pack('<360i', *values))
    tables = Tables(*[(c.c_int32 * 360)(*values) for values in factors])
    from original import STACK
    frame = STACK - 4
    Write = c.CFUNCTYPE(c.c_int, c.c_uint32, c.c_uint, c.c_uint32, c.c_void_p)
    function = native.vertrix_title_letter_fly_out_call
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
                     'Dword/radius transition returns and handler arrival compare. Arithmetic faults, callback register '
                     'clobbers and exceptional execution remain outside the normal boundary.'}


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
    full_launch=verify_full_launch(args,n)
    full_fly_out=verify_full_fly_out(args,n)
    vs.write_report(args, 'title-letter-launch', {
        'full_launch_abi':full_launch, 'full_fly_out_abi':full_fly_out,
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'Complete original 0x45a0c0 (with the real 0x484680, 0x484700 and 0x4ad510; the sound player 0x482a60 observed and its table lookup checked) and handlers 0x45a1c0, 0x45a4f0 and 0x45a910 (with the real actor helpers, 0x4ad750, 0x4ad5e0, 0x4ad530 and 0x4b14c0) run in the oracle. The first 0x160 actor bytes, handler token included, and the flag 0x532a40 compare after every call.'})


if __name__ == '__main__':
    main()
