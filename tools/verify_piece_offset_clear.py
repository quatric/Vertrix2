"""Verify pending piece-offset clears and adjacent cell-value initializers against original."""
import ctypes as c
import random
from original import Original, STACK
from unicorn import UC_HOOK_MEM_WRITE
from unicorn.x86_const import UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP, UC_X86_REG_ESP
import verify_support as vs

U = c.c_uint32
ROUTINES = {0x42f870: ('board_piece_clear_offset_x_full', 0xa64, 1),
            0x42f880: ('board_piece_clear_offset_y_full', 0xa65, 1),
            0x42f860: ('board_cell_values_clear_full', 0x19d, 65),
            0x42f8e0: ('board_cell_values_fill_full', 0x19d, 65)}
SIZE = 0xb00


def main():
    args = vs.parse(__doc__, 4096)
    native = vs.build(args, 'piece-offset-clear', ['piece_offset_clear.c'])
    original = Original(args.executable)
    cpu = original.cpu
    cpu.mem_map(0xfffff000, 0x1000)
    rng = random.Random(0x42f870)
    counts = {}; guards = 0; write_counts = {}; wraps = 0
    active_token = 0
    writes = []
    def write_hook(cpu, access, address, width, value, context):
        offset = (address - active_token) & 0xffffffff
        if offset < SIZE:
            writes.append((offset, width, value & ((1 << (width * 8)) - 1)))
    hook = cpu.hook_add(UC_HOOK_MEM_WRITE, write_hook)
    def put(token, raw):
        split = min(len(raw), 0x100000000 - token)
        cpu.mem_write(token, raw[:split])
        if split < len(raw): cpu.mem_write(0, raw[split:])
    def get(token):
        split = min(SIZE, 0x100000000 - token)
        return bytes(cpu.mem_read(token, split)) + (bytes(cpu.mem_read(0, SIZE - split)) if split < SIZE else b'')
    try:
        for address, (name, offset, length) in ROUTINES.items():
            function = getattr(native, 'vertrix_' + name)
            function.argtypes = ([c.c_void_p, c.c_size_t, U, U, c.POINTER(U), c.POINTER(U)]
                                 if address == 0x42f8e0 else [c.c_void_p, c.c_size_t, U, c.POINTER(U)])
            for case in range(args.cases):
                token = (0x808000, 0x809000, 0xffffffc0)[case % 3]
                raw = rng.randbytes(SIZE)
                put(token, raw)
                edx = (rng.getrandbits(24) << 8) | (case % 256)
                others = tuple(rng.getrandbits(32) for _ in range(5))
                for reg, value in zip((UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP), others[2:]): cpu.reg_write(reg, value)
                active_token = token; writes.clear()
                wanted = original.call(address, eax=token, edx=edx, ebx=others[0], ecx=others[1])
                expected = get(token)
                expected_edx = (token + 65) & 0xffffffff if address == 0x42f8e0 else edx
                value = edx & 255 if address == 0x42f8e0 else 0
                assert writes == [(offset + i, 1, value) for i in range(length)], (hex(address), case, writes)
                prefix, suffix = bytes([0x57]) * 16, bytes([0xa9]) * 16
                host = c.create_string_buffer(prefix + raw + suffix, SIZE + 32)
                result = U(0xdeadbeef); edx_result = U(0xcafebabe)
                size = offset + length + (case % 16)
                if address == 0x42f8e0:
                    status = function(c.byref(host, 16), size, token, edx, c.byref(result), c.byref(edx_result))
                    assert edx_result.value == expected_edx
                else: status = function(c.byref(host, 16), size, token, c.byref(result))
                assert status and result.value == wanted
                assert wanted == (token if length == 1 else (token + 65) & 0xffffffff)
                assert host.raw == prefix + expected + suffix, (hex(address), case)
                assert tuple(cpu.reg_read(r) for r in (UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX, UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP)) == (expected_edx, *others)
                assert cpu.reg_read(UC_X86_REG_ESP) == STACK + 4
                counts[hex(address)] = counts.get(hex(address), 0) + 1
                write_counts[hex(address)] = write_counts.get(hex(address), 0) + len(writes)
                wraps += token == 0xffffffc0
            for bad in ('zero_size', 'short', 'null_storage', 'null_result', 'null_edx'):
                if bad == 'null_edx' and address != 0x42f8e0: continue
                host = c.create_string_buffer(raw, SIZE)
                result = U(0xdeadbeef); edx_result = U(0xcafebabe)
                ptr = None if bad == 'null_storage' else host
                size = 0 if bad == 'zero_size' else offset + length - 1 if bad == 'short' else SIZE
                out = None if bad == 'null_result' else c.byref(result)
                if address == 0x42f8e0: status = function(ptr, size, token, edx, out, None if bad == 'null_edx' else c.byref(edx_result))
                else: status = function(ptr, size, token, out)
                assert not status and result.value == 0xdeadbeef and edx_result.value == 0xcafebabe and host.raw == raw
                guards += 1
    finally:
        cpu.hook_del(hook)
    assert counts == {hex(address): args.cases for address in ROUTINES} and guards == 17
    assert write_counts == {hex(address): args.cases * length for address, (_, _, length) in ROUTINES.items()}
    vs.write_report(args, 'piece-offset-clear', {
        'status': 'passed', 'cases_per_entry': args.cases, 'complete_original_executions': counts,
        'original_exact_byte_write_counts': write_counts, 'original_address_wrap_cases': wraps,
        'native_guard_cases': guards,
        'scope': 'Four complete original wrappers and actual callees execute unstubbed. Pending active-piece X/Y clear writes exactly+a64/a65, preserving incoming EAX and EDX. Cell-value clear/fill writes65 consecutive bytes+19d..1dd; EAX returns token+65, and fill EDX does too while clear restores incomingEDX. All256 low input bytes, random upper registers, whole guarded storage, exact minimum backing, all preserved registers/ESP and original32bit address/result wrapping compare. Native invalid backing/output guards are adaptations, not original fault behavior.',
        'naming_evidence': {
            'pending_piece_x_y': '42fc60 sign-extends+a64 then calls piece X setter42a960;42fc70 sign-extends+a65 then calls piece Y setter42a970. Clear42f870 calls42f890 with zero;clear42f880 calls42f8a0 with zero.',
            'cell_values': 'Original42f2e0 fills the same65 bytes+19d..1dd from board value+58; source/board_piece.[ch] explicitly labels BOARD_CELLS/BOARD_VALUE.42f860 wraps complete42f8e0 with zero and EDX save/restore.',
            'remaining_unidentified_plane': '42f850/42f8b0 clear/fill65 bytes+15c..19c; semantic field purpose remains unconfirmed and no name/recovery is claimed.'}})

if __name__ == '__main__': main()
