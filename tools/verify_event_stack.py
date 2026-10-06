"""Compare the complete original nine-record event stack routines with the native recovery."""
import argparse, ctypes as c, json, random, struct, subprocess
from pathlib import Path
from original import Original

OBJECT, SIZE, OUTS = 0x801000, 0x4000, 0x808000
U8, U16, U32 = c.c_uint8, c.c_uint16, c.c_uint32
#(name, ctype, width) in the original stack - argument order after b00, b01 and d04.
TAIL = (('b08', U8), ('d0c', U32), ('d10', U32), ('b14', U8), ('d2c', U32), ('d18', U32),
        ('d1c', U32), ('w20', U16), ('w22', U16), ('d24', U32), ('d28', U32))
FIELDS = (('b00', U8), ('b01', U8), ('d04', U32)) + TAIL
MASKS = {U8: 0xff, U16: 0xffff, U32: 0xffffffff}


class Record(c.Structure):
    _fields_ = [(name, kind) for name, kind in
                (('b00', U8), ('b01', U8), ('d04', U32), ('b08', U8), ('d0c', U32), ('d10', U32),
                 ('b14', U8), ('d18', U32), ('d1c', U32), ('w20', U16), ('w22', U16),
                 ('d24', U32), ('d28', U32), ('d2c', U32))]


def refs_type(const):
    order = ('b00', 'b01', 'd04', 'b08', 'd0c', 'd10', 'b14', 'd2c', 'd18', 'd1c', 'w20', 'w22',
             'd24', 'd28')
    kinds = dict(FIELDS)
    return type('Refs', (c.Structure,), {'_fields_': [(n, c.POINTER(kinds[n])) for n in order]})


Refs = refs_type(False)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    source = Path(__file__).resolve().parents[1] / 'source'
    library = build / 'event-stack.dylib'
    subprocess.run(['cc', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    str(source / 'event_stack.c'), str(source / 'actor_storage.c'), '-o', str(library)],
                   check=True)
    n = c.CDLL(str(library))
    n.vertrix_event_stack_push.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(Record)]
    n.vertrix_event_stack_pop.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(Refs)]
    n.vertrix_event_stack_replace_top.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(Refs)]
    n.vertrix_event_stack_empty.argtypes = [c.c_void_p, c.c_size_t, c.POINTER(U32)]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x482060)
    totals = {'push': 0, 'pop': 0, 'replace_top': 0, 'empty': 0}
    for case in range(args.cases):
        raw = bytearray(rng.randbytes(SIZE))
        raw[0x208] = rng.choice([0, 1, 2, 8, 9, 10, rng.randrange(256), rng.randrange(0, 9)])
#push 0x482060
        values = {name: rng.getrandbits(32) for name, _ in FIELDS}
        cpu.mem_write(OBJECT, bytes(raw))
        original.call(0x482060, eax=OBJECT, edx=values['b00'], ebx=values['b01'], ecx=values['d04'],
                      args=tuple(values[name] for name, _ in TAIL))
        native = c.create_string_buffer(bytes(raw), SIZE)
        record = Record(**{
name: values[name] & MASKS[kind] for name, kind in FIELDS})
        n.vertrix_event_stack_push(native, SIZE, c.byref(record))
        assert native.raw == bytes(cpu.mem_read(OBJECT, SIZE)), ('push', case)
        totals['push'] += 1
#pop 0x482110 and replace top 0x482210 : random subset of non - null pointers
        for address, name in ((0x482110, 'pop'), (0x482210, 'replace_top')):
            cpu.mem_write(OBJECT, bytes(raw))
            sentinel = rng.randbytes(0x100)
            cpu.mem_write(OUTS, sentinel)
            slots = {}
            addrs = []
            offset = 0
            native_refs = Refs()
            holders = {}
            for field, kind in FIELDS:
                if rng.random() < 0.7:
                    slots[field] = OUTS + offset
                    holders[field] = kind(struct.unpack('<I', sentinel[offset:offset + 4])[0] & MASKS[kind])
                    setattr(native_refs, field, c.pointer(holders[field]))
                    offset += 8
                else:
                    slots[field] = 0
            order = [f for f, _ in FIELDS]
            call_order = ['b00', 'b01', 'd04'] + [f for f, _ in TAIL]
            native_buffer = c.create_string_buffer(bytes(raw), SIZE)
            original.call(address, eax=OBJECT, edx=slots['b00'], ebx=slots['b01'], ecx=slots['d04'],
                          args=tuple(slots[f] for f in call_order[3:]))
            result = getattr(n, 'vertrix_event_stack_' + name)(native_buffer, SIZE, c.byref(native_refs))
            assert native_buffer.raw == bytes(cpu.mem_read(OBJECT, SIZE)), (name, case)
            out = bytes(cpu.mem_read(OUTS, 0x100))
            for field, kind in FIELDS:
                if slots[field]:
                    expected = struct.unpack('<I', out[slots[field] - OUTS:slots[field] - OUTS + 4])[0]
                    assert holders[field].value == expected & MASKS[kind], (name, field, case)
            totals[name] += 1
#empty 0x482300
        cpu.mem_write(OBJECT, bytes(raw))
        got = original.call(0x482300, eax=OBJECT) & 0xff
        flag = U32()
        assert n.vertrix_event_stack_empty(c.create_string_buffer(bytes(raw), SIZE), SIZE, c.byref(flag)) and flag.value == got, case
        totals['empty'] += 1
#short storage is rejected unchanged
    short = c.create_string_buffer(0x208)
    assert not n.vertrix_event_stack_push(short, 0x208, c.byref(Record()))
    # 0x478cd0 / 0x478da0 over manual event buffers (no RNG involved).
    EVT = 0x807000
    n.vertrix_event_key_index.argtypes = [c.c_void_p, c.c_size_t, c.c_uint32]
    n.vertrix_event_scale_fields.argtypes = [c.c_void_p, c.c_size_t]
    e_rng = random.Random(0x478cd0)
    for _ in range(args.cases):
        key = e_rng.choice([0, 8, 0xf, 0x10, 0x18, 0x20, 0x21, 0xff, e_rng.getrandbits(32)])
        data = bytes(e_rng.getrandbits(8) for _ in range(0x40))
        cpu.mem_write(EVT, data)
        original.call(0x478cd0, eax=EVT, edx=key)
        expected = bytes(cpu.mem_read(EVT, 0x40))
        host = c.create_string_buffer(data, 0x40)
        assert n.vertrix_event_key_index(host, 0x40, key) == 1
        assert host.raw == expected, hex(key)
        totals['0x478cd0'] = totals.get('0x478cd0', 0) + 1
        data = bytes(e_rng.getrandbits(8) for _ in range(0x40))
        cpu.mem_write(EVT, data)
        # Full-width edx: the original only consumes the low byte here.
        edx = e_rng.getrandbits(32)
        expect = original.call(0x478da0, eax=EVT, edx=edx)
        host = c.create_string_buffer(data, 0x40)
        assert n.vertrix_event_scale_fields(host, 0x40) == (expect & 0xffffffff)
        assert host.raw == bytes(cpu.mem_read(EVT, 0x40)), hex(edx)
        totals['0x478da0'] = totals.get('0x478da0', 0) + 1
    tiny = c.create_string_buffer(b'\xaa' * 8, 8)
    assert not n.vertrix_event_key_index(tiny, 8, 8)
    assert tiny.raw == b'\xaa' * 8
    assert not n.vertrix_event_scale_fields(tiny, 8)
    assert tiny.raw == b'\xaa' * 8
    report = {'status': 'passed', 'complete_original_executions': totals,
              'scope': 'Complete 482060, 482110, 482210, 482300, 478cd0 and 478da0 execute in the '
                       'original; whole object and every output pointer compare for random counts '
                       '(0..255), contents and random null/non-null pointer subsets.'}
    (build / 'event-stack-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
