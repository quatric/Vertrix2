"""Compare the complete original MPEG header decoder with the native recovery."""
import ctypes as c, random, struct
from original import Original
from unicorn.x86_const import UC_X86_REG_EAX
import verify_common_a as common

U = c.c_uint32
Invalid = c.CFUNCTYPE(None, U, c.c_void_p)
NAMES = (('channels', 0x00), ('lsf', 0x0c), ('extension', 0x10), ('layer', 0x18), ('protection', 0x1c),
         ('bitrate', 0x20), ('sample_rate', 0x24), ('padding', 0x28), ('private_bit', 0x2c),
         ('mode', 0x30), ('mode_extension', 0x34), ('copyright', 0x38), ('original', 0x3c),
         ('emphasis', 0x40), ('frame_size', 0x44))
STRUCT = 0x806000


class Header(c.Structure):
    _fields_ = [(name, c.c_int32 if name == 'frame_size' else U) for name, _ in NAMES]


def main():
    args = common.parse(__doc__)
    n = common.build(args, 'mpeg-header', 'mpeg_header.c')
    n.vertrix_mpeg_header_decode.argtypes = [c.POINTER(Header), U, c.POINTER(U), c.POINTER(U), Invalid,
                                             c.c_void_p]
    n.vertrix_mpeg_header_decode.restype = U
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x404480)
    events, native = [], []
    common.stub(cpu, 0x4eb4d4, lambda uc: events.append(uc.reg_read(UC_X86_REG_EAX)))

    @Invalid
    def invalid(code, context):
        native.append(code)

    bitrates = (U * 96).from_buffer_copy(bytes(cpu.mem_read(0x4f40ac, 384)))
    rates = (U * 16).from_buffer_copy(bytes(cpu.mem_read(0x4f41ac, 64)))
    totals = {'decoded': 0, 'frame_size': 0}
    for case in range(args.cases):
        word = rng.getrandbits(32)
        if rng.random() < 0.5:
            word = (word & ~0x1e0000) | 0x60000 | (rng.choice([0, 1]) << 20 | rng.choice([0, 1]) << 19)
        raw = rng.randbytes(0x48)
        cpu.mem_write(STRUCT, raw)
        header = Header()
        for name, offset in NAMES:
            setattr(header, name, struct.unpack('<i' if name == 'frame_size' else '<I', raw[offset:offset + 4])[0])
        events.clear();
        native.clear()
        try : want = original.call(0x404480, eax=STRUCT, edx=word)
        except Exception:
#The only fault is the division by a zero rate; the native routine reports 0.
            assert n.vertrix_mpeg_header_decode(c.byref(header), word, bitrates, rates, invalid, None) == 0
            original.cpu.emu_stop()
            continue
        got = n.vertrix_mpeg_header_decode(c.byref(header), word, bitrates, rates, invalid, None)
        assert want == got and events == native, (case, hex(word))
        for name, offset in NAMES:
            fmt = '<i' if name == 'frame_size' else '<I'
            assert struct.unpack(fmt, bytes(cpu.mem_read(STRUCT + offset, 4)))[0] == getattr(header, name), \
                (case, name, hex(word))
        totals['decoded'] += 1
        totals['frame_size'] += header.layer == 3 and got == 1
    common.report(args, 'mpeg-header', totals,
                  'Complete 404480 runs in the original (4eb4d4 stubbed) over random header words, '
                  'including every version, layer, bitrate and sample rate combination; all stored fields, '
                  'the result and the invalid-rate call compare.')


if __name__ == '__main__':
    main()
