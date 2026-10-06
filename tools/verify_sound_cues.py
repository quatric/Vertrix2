"""Compare complete original sound cue wrappers with the native recovery."""
import ctypes as c, random, struct
from original import Original
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_EAX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_EDX, UC_X86_REG_ESP
import verify_support as vs

OBJ, SIZE = vs.SCRATCH, 0x100
START, STOP = 0x4761d0, 0x476280


class Request(c.Structure):
    _fields_ = [('table', c.c_uint32), ('index', c.c_uint32), ('first', c.c_uint32),
                ('second', c.c_uint32)]


Call = c.CFUNCTYPE(None, c.c_void_p, c.c_uint32, c.POINTER(Request))
KEYS = {0x477010: (0xb8, START), 0x477040: (0xb8, STOP), 0x477070: (0xbc, START),
        0x4770a0: (0xbc, STOP), 0x4770d0: (0xc0, START), 0x477100: (0xc0, STOP),
        0x477130: (0xc4, START), 0x477160: (0xc4, STOP)}
FIXED = {0x478570: (0x72, START), 0x4785c0: (0x72, STOP), 0x478610: (0x73, START),
         0x478660: (0x73, STOP), 0x4786b0: (0x70, START), 0x478700: (0x70, STOP),
         0x478750: (0x71, START), 0x4787a0: (0x71, STOP)}


def main():
    args = vs.parse(__doc__, 2048)
    n = vs.build(args, 'sound-cues', ['sound_cues.c'])
    U8P, U, S = c.POINTER(c.c_uint8), c.c_uint32, c.c_size_t
    n.vertrix_sound_cue_key.argtypes = [U8P, S, U, U, Call, c.c_void_p]
    n.vertrix_sound_cue_offset.argtypes = [U8P, S, U, U, Call, c.c_void_p]
    n.vertrix_sound_cue_position.argtypes = [U8P, S, U, U, Call, c.c_void_p]
    n.vertrix_sound_cue_both.argtypes = [U, U, Call, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    events, native_events = [], []
    for address in (START, STOP):
        cpu.mem_write(address, b'\xc2\x04\x00')

    def hook(cpu_, address, size, user):
        esp = cpu_.reg_read(UC_X86_REG_ESP)
        events.append((address, cpu_.reg_read(UC_X86_REG_EAX), cpu_.reg_read(UC_X86_REG_EDX),
                       cpu_.reg_read(UC_X86_REG_EBX), cpu_.reg_read(UC_X86_REG_ECX),
                       struct.unpack('<I', bytes(cpu_.mem_read(esp + 4, 4)))[0]))

    for address in (START, STOP):
        cpu.hook_add(UC_HOOK_CODE, hook, begin=address, end=address)

    @Call
    def call(context, operation, request):
        r = request.contents
        native_events.append((operation, r.table, r.index, r.first, r.second))

    rng = random.Random(0x477010)
    totals = {}

    def run(name, address, native):
        data = bytearray(rng.randbytes(SIZE))
        if rng.random() < 0.5:
            struct.pack_into('<I', data, 0x60, 0)
        cpu.mem_write(OBJ, bytes(data))
        events.clear()
        native_events.clear()
        original.call(address, **native[0])
        buf = (c.c_uint8 * SIZE).from_buffer_copy(bytes(data))
        native[1](buf)
        assert len(events) == len(native_events) == native[2], (name, events, native_events)
        for (op, eax, edx, ebx, ecx, extra), (nop, table, index, first, second) in zip(events, native_events):
            assert (op, eax, edx, ebx, ecx, extra) == (nop, table, index, first, second, 0), \
                (name, hex(address), events, native_events)
        totals[name] = totals.get(name, 0) + 1

    for case in range(args.cases):
        for address, (key, op) in KEYS.items():
            run('key', address, (dict(eax=OBJ), lambda b, key=key, op=op: n.vertrix_sound_cue_key(
                b, SIZE, key, op, call, None), 1))
        for address, op in ((0x476fb0, START), (0x476fe0, STOP)):
            delta = rng.getrandbits(32)
            run('offset', address, (dict(eax=OBJ, edx=delta), lambda b, op=op, d=delta:
                                    n.vertrix_sound_cue_offset(b, SIZE, d, op, call, None), 1))
        for address, op in ((0x4784d0, START), (0x478520, STOP)):
            index = rng.getrandbits(32)
            run('position', address, (dict(eax=OBJ, edx=index), lambda b, op=op, i=index:
                                      n.vertrix_sound_cue_position(b, SIZE, i, op, call, None), 1))
        for address, (index, op) in FIXED.items():
            run('fixed', address, (dict(eax=OBJ), lambda b, op=op, i=index:
                                   n.vertrix_sound_cue_position(b, SIZE, i, op, call, None), 1))
        table, index = rng.getrandbits(32) & 0xffffff00 | 0x40, rng.getrandbits(32)
        run('both', 0x476720, (dict(eax=table, edx=index),
                               lambda b: n.vertrix_sound_cue_both(table, index, call, None), 2))
        events.clear()
    vs.write_report(args, 'sound-cues', {
        'status': 'passed', 'complete_original_executions': totals,
        'scope': 'Complete 476fb0, 476fe0, 477010..477160, 4784d0, 478520, 478570..4787a0 and '
                 '476720 execute in the original with 4761d0 and 476280 neutralised and hooked; '
                 'every call (routine, eax, edx, ebx, ecx and stack word) compares.'})


if __name__ == '__main__':
    main()
