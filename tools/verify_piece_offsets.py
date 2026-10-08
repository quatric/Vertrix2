"""Verify named piece/pending-board X/Y byte setters against the original executable."""
import ctypes as c
import random
from original import Original
from unicorn.x86_const import UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX
import verify_support as vs

U = c.c_uint32
ROUTINES = {0x42a960: ('piece_set_offset_x_full', 0x16c),
            0x42a970: ('piece_set_offset_y_full', 0x16d),
            0x42f890: ('board_piece_set_offset_x_full', 0xa64),
            0x42f8a0: ('board_piece_set_offset_y_full', 0xa65)}
SIZE = 0xb00


def main():
    args = vs.parse(__doc__, 4096)
    native = vs.build(args, 'piece-offsets', ['piece_offsets.c', 'actor_storage.c'])
    original = Original(args.executable); cpu = original.cpu
    rng = random.Random(0x42a960)
    counts = {}; guards = 0
    for address, (name, offset) in ROUTINES.items():
        function = getattr(native, 'vertrix_' + name)
        function.argtypes = [c.c_void_p, c.c_size_t, U, U, c.POINTER(U)]
        for case in range(args.cases):
            token = 0x808000 + ((case // 256) % 2) * 0x1000
            raw = rng.randbytes(SIZE)
            cpu.mem_write(token, raw)
            # Exhaustive low byte cycle, with independent random upper EDX bits.
            edx = (rng.getrandbits(24) << 8) | (case % 256)
            ebx, ecx = rng.getrandbits(32), rng.getrandbits(32)
            wanted = original.call(address, eax=token, edx=edx, ebx=ebx, ecx=ecx)
            expected = bytes(cpu.mem_read(token, SIZE))
            prefix = bytes([0x57]) * 16; suffix = bytes([0xa9]) * 16
            host = c.create_string_buffer(prefix + raw + suffix, SIZE + 32)
            result = U(0xdeadbeef)
            size = offset + 1 + (case % 16)
            assert function(c.byref(host, 16), size, token, edx, c.byref(result)), (address, case)
            assert result.value == wanted == token
            assert host.raw == prefix + expected + suffix, (address, case)
            assert tuple(cpu.reg_read(r) for r in (UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX)) == (edx, ebx, ecx)
            counts[hex(address)] = counts.get(hex(address), 0) + 1
        for size in (0, offset - 1, offset):
            host = c.create_string_buffer(raw, SIZE); result = U(0xdeadbeef)
            assert not function(host, size, token, edx, c.byref(result))
            assert result.value == 0xdeadbeef and host.raw == raw
            guards += 1
        result = U(0xdeadbeef)
        assert not function(None, SIZE, token, edx, c.byref(result))
        assert result.value == 0xdeadbeef
        host = c.create_string_buffer(raw, SIZE)
        assert not function(host, SIZE, token, edx, None) and host.raw == raw
        guards += 2
    assert counts == {hex(address): args.cases for address in ROUTINES} and guards == 20
    vs.write_report(args, 'piece-offsets', {
        'status': 'passed', 'complete_original_executions': counts, 'native_guard_cases': guards,
        'scope': 'Four complete byte setters: all low byte values, random upper EDX/caller registers, '
                 'two actor identities, minimum valid storage and whole guarded object storage. '
                 'Original unchanged EAX and untouched fields compare; invalid boundaries preserve effects.',
        'naming_evidence': {
            'piece_x_y': '42a800 child positioning sign-extends 16c at 0x42a821/0x42a86c and adds to X; '
                         '16d at 0x42a843/0x42a88e adds to Y. source/piece_children.[ch] uses PIECE_OFFSET_X/Y.',
            'board_pending_x_y': '42fc60 reads+a61/SAR24 (signed byte +0xa64), calls 0x42a960 at 0x42fc6b; '
                                 '42fc70 reads+a62/SAR24 (signed byte +0xa65), calls 0x42a970 at 0x42fc7f.'}})


if __name__ == '__main__':
    main()
