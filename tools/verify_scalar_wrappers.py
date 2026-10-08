"""Verify repeat counters, frame count and raw glyph-index register wrappers."""
import argparse
import ctypes as c
import json
import random
from pathlib import Path
from original import Original, BOARD, STACK
from oracle_kit import build
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX,
                               UC_X86_REG_ECX, UC_X86_REG_ESI, UC_X86_REG_EDI,
                               UC_X86_REG_EBP, UC_X86_REG_ESP)
U = c.c_uint32
P = c.POINTER(U)
ENTRIES = ((0x475de0, 'input_repeat_counter_clear_full'),
           (0x475e30, 'input_repeat_counter_advance_full'),
           (0x487860, 'frame_resource_count_full'),
           (0x48ac00, 'font_glyph_index_full'))
REGISTERS = (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX,
             UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP)

def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    if args.cases < 1: parser.error('--cases must be positive')
    native = build(args.build_dir, 'scalar-wrappers', ['input.c', 'frame_resource.c',
                   'font_map.c', 'actor_storage.c', 'call_glue.c'])
    functions = {address: getattr(native, 'vertrix_' + name) for address, name in ENTRIES}
    functions[0x475de0].argtypes = [c.c_void_p, c.c_size_t, U, P]
    functions[0x475e30].argtypes = [c.c_void_p, c.c_size_t, U, U, P]
    functions[0x487860].argtypes = [c.c_void_p, c.c_size_t, P]
    functions[0x48ac00].argtypes = [c.c_void_p, c.c_size_t, U, U, P, P]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x48ac00)
    handles = [0, BOARD]
    for i in range(30):
        handle = 0x10000000 + i * 0x1000000
        cpu.mem_map(handle, 0x1000)
        handles.append(handle + 0x100)
    totals = {hex(address): 0 for address, _ in ENTRIES}
    glyph_codes = set()
    high_words = set()
    for case in range(args.cases):
        handle = handles[case % len(handles)]
        initial = rng.randbytes(0x240)
        edx = (rng.getrandbits(24) << 8) | (case & 255)
        if case < 4: edx = (0, 1, 0xffffffff, 0x80000000)[case]
        others = tuple(rng.getrandbits(32) for _ in range(5))
        for address, _ in ENTRIES:
            cpu.mem_write(handle, initial)
            for reg, value in zip(REGISTERS[4:], others[2:]): cpu.reg_write(reg, value)
            expected_eax = original.call(address, eax=handle, edx=edx,
                                         ebx=others[0], ecx=others[1])
            expected = tuple(cpu.reg_read(reg) for reg in REGISTERS)
            storage = c.create_string_buffer(initial, len(initial))
            result = U(0xdeadbeef)
            masked = U(0xcafebabe)
            fn = functions[address]
            if address == 0x475de0:
                status = fn(storage, len(initial), handle, c.byref(result))
            elif address == 0x475e30:
                status = fn(storage, len(initial), handle, edx, c.byref(result))
            elif address == 0x487860:
                status = fn(storage, len(initial), c.byref(result))
            else:
                status = fn(storage, len(initial), handle, edx, c.byref(result), c.byref(masked))
                glyph_codes.add(edx & 255)
                high_words.add(handle >> 16)
            assert status
            native_edx = masked.value if address == 0x48ac00 else edx
            assert expected == (result.value, native_edx, *others), (case, hex(address), expected, result.value, native_edx)
            assert result.value == expected_eax
            assert storage.raw == bytes(cpu.mem_read(handle, len(initial))), (case, hex(address), 'storage')
            assert cpu.reg_read(UC_X86_REG_ESP) == STACK + 4
            totals[hex(address)] += 1
    guards = 0
    for address, _ in ENTRIES:
        for invalid in ('null', 'short', 'result'):
            storage = c.create_string_buffer(bytes([0xa5]) * 0x240)
            before = storage.raw
            result = U(0xdeadbeef)
            masked = U(0xcafebabe)
            ptr = None if invalid == 'null' else storage
            size = 0 if invalid == 'short' else len(before)
            out = None if invalid == 'result' else c.byref(result)
            fn = functions[address]
            if address == 0x475de0: status = fn(ptr, size, 0, out)
            elif address == 0x475e30: status = fn(ptr, size, 0, 1, out)
            elif address == 0x487860: status = fn(ptr, size, out)
            else: status = fn(ptr, size, 0, 255, out, c.byref(masked))
            assert not status
            assert storage.raw == before and result.value == 0xdeadbeef and masked.value == 0xcafebabe
            guards += 1
    assert guards == 12 and all(n == args.cases for n in totals.values())
    if args.cases >= 256: assert len(glyph_codes) == 256
    report = {'status': 'passed', 'cases_per_entry': args.cases,
              'complete_original_executions': totals, 'whole_storage_and_register_comparisons': sum(totals.values()),
              'glyph_byte_codes': len(glyph_codes), 'incoming_eax_high_words': len(high_words),
              'invalid_storage_or_output_guards': guards,
              'scope': 'Unmodified original475de0 clear and475e30 wrapping advance of input repeat counter+44,487860 resource frame count+4,48ac00 glyph-index word+8+2*(EDX&255). Entire raw storage, exact EAX/EDX, preserved EBX/ECX/ESI/EDI/EBP and stack compare independently. Raw glyph lookup preserves incoming EAX highword, unlike signed index projections. Native invalid storage/output guards are adaptations, not original fault behavior.'}
    (args.build_dir / 'scalar-wrappers-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))

if __name__ == '__main__': main()
