"""Verify exact original double multiplication registers, software/errors and masked x87 modes."""
import ctypes as c
import json
import random
import struct
from original import Original, STACK
from oracle_kit import build
from verify_rtl_single import State, Call
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX,
                               UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP,
                               UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_FPCW)
import verify_support as vs
REGS = (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX)
MODES = [('software', 0, 0x37f)] + [(f'hardware_pc{pc}_rc{rc}', 1, 0x7f | (pc << 8) | (rc << 10))
                                   for pc in (0, 2, 3) for rc in range(4)]
EDGE = (0, 0x8000000000000000, 1, 0x8000000000000001, 0xffffffff, 0x100000000,
        0xfffffffffffff, 0x10000000000000, 0x3ff0000000000000, 0xbff0000000000000,
        0x3ca0000000000000, 0x7fefffffffffffff, 0xffefffffffffffff,
        0x7ff0000000000000, 0xfff0000000000000, 0x7ff8000000000001,
        0xfff8000000000002, 0x7ff0000000000001, 0xfff0000000000002)


def main():
    args = vs.parse(__doc__, 4096)
    native = build(args.build_dir, 'rtl-double-multiply', ['rtl_double_multiply.c'])
    function = native.vertrix_rtl_double_multiply_full
    function.argtypes = [c.POINTER(State), Call, c.c_void_p]
    original = Original(args.executable); cpu = original.cpu
    rng = random.Random(0x4db507)
    oracle_calls, native_calls, outputs, contexts = [], [], [], []
    paths = {hex(a): 0 for a in (0x4db539, 0x4db52a, 0x4db572, 0x4db58d,
                                0x4db66f, 0x4e236c, 0x4e2389)}
    def hook(cpu, address, size, context):
        if hex(address) in paths:
            paths[hex(address)] += 1; return
        oracle_calls.append((address, *[cpu.reg_read(reg) for reg in REGS]))
        values = tuple(rng.getrandbits(32) for _ in REGS); outputs.append(values)
        for register, value in zip(REGS, values): cpu.reg_write(register, value)
        esp = cpu.reg_read(UC_X86_REG_ESP)
        cpu.reg_write(UC_X86_REG_EIP, int.from_bytes(cpu.mem_read(esp, 4), 'little'))
        cpu.reg_write(UC_X86_REG_ESP, esp + 4)
    hooks = [cpu.hook_add(UC_HOOK_CODE, hook, begin=a, end=a)
             for a in [int(a,16) for a in paths] + [0x4dae94, 0x4e7280]]
    @Call
    def call(target, pointer, context):
        state = pointer.contents
        native_calls.append((target, state.eax, state.edx, state.ebx, state.ecx)); contexts.append(context)
        index = len(native_calls) - 1
        state.eax, state.edx, state.ebx, state.ecx = outputs[index] if index < len(outputs) else (0,0,0,0)
    def compare(a, b, hardware, control):
        state = State(a & 0xffffffff, a >> 32, b & 0xffffffff, b >> 32,
                      rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32),
                      hardware, rng.getrandbits(8), control)
        unchanged = (state.helper, state.multiply, state.divide, state.hardware, state.capability, state.control)
        cpu.mem_write(0x5054a1, bytes([hardware])); cpu.reg_write(UC_X86_REG_FPCW, control)
        others = tuple(rng.getrandbits(32) for _ in range(3))
        for register, value in zip((UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP), others): cpu.reg_write(register,value)
        oracle_calls.clear(); native_calls.clear(); outputs.clear(); contexts.clear()
        original.call(0x4db507, eax=state.eax, edx=state.edx, ebx=state.ebx, ecx=state.ecx)
        expected = tuple(cpu.reg_read(reg) for reg in REGS)
        assert function(c.byref(state), call, 0x1234)
        got = (state.eax, state.edx, state.ebx, state.ecx)
        assert got == expected, (hex(a), hex(b), hardware, hex(control), tuple(hex(v) for v in got), tuple(hex(v) for v in expected))
        assert oracle_calls == native_calls, (hex(a),hex(b),oracle_calls,native_calls)
        assert all(context == 0x1234 for context in contexts)
        assert (state.helper, state.multiply, state.divide, state.hardware, state.capability, state.control) == unchanged
        assert tuple(cpu.reg_read(reg) for reg in (UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP)) == others
        assert cpu.reg_read(UC_X86_REG_ESP) == STACK + 4
        return (state.edx << 32) | state.eax
    counts = {name: 0 for name, _, _ in MODES}
    for case in range(args.cases):
        a = EDGE[case // len(EDGE)] if case < len(EDGE)**2 else rng.getrandbits(64)
        b = EDGE[case % len(EDGE)] if case < len(EDGE)**2 else rng.getrandbits(64)
        for name, hardware, control in MODES:
            compare(a,b,hardware,control); counts[name] += 1
    for h in hooks: cpu.hook_del(h)
    assert all(count == args.cases for count in counts.values())
    if args.cases >= len(EDGE)**2: assert all(paths.values()), paths
    early = 0
    for a,b in [(0,0),(0x8000000000000000,0x7ff0000000000000),
                (0x3ff0000000000000,0x8000000000000000),(0x7ff8000000000001,0),
                (0,0xfff8000000000002)]:
        compare(a,b,1,0); early += 1
    # PC64 intermediate rounding creates a final double tie absent at PC53.
    double_rounding = 0; nearest_results = {}
    for sign in (0, 0x8000000000000000):
        for pc in (0,2,3):
            for rc in range(4):
                value = compare(0x3ff0000000000002 | sign, 0x3fefffffffffffff,
                                1, 0x7f | (pc << 8) | (rc << 10))
                if not sign and rc == 0: nearest_results[str(pc)] = hex(value)
                double_rounding += 1
    assert double_rounding == 24 and nearest_results == {
        '0':'0x3ff0000000000000','2':'0x3ff0000000000001','3':'0x3ff0000000000002'}
    cleanup = 0
    for pc in (0,2,3):
        for rc in range(4):
            assert compare(0x8010000000000000, 0x3cb0000000000000,
                           1, 0x7f | (pc << 8) | (rc << 10)) == 0
            cleanup += 1
    shift_cases = 0; shift_results = {}
    for exponent in (-1,-2,-33,-53,-54):
        value = compare(0x0010000000000001, (exponent + 1022) << 52, 0, 0x37f)
        shift_results[str(exponent)] = hex(value)
        shift_cases += 1
    assert shift_results['-1'] == '0x1' and shift_results['-33'] == '0x1'
    assert shift_results['-54'] == '0x0'
    guards = 0
    for hardware,control in [(1,0x37e),(1,0x17f),(0,0x37f)]:
        state = State(0xffffffff,0x7fefffff,0xffffffff,0x7fefffff,1,2,3,hardware,4,control)
        before = bytes(state)
        assert not function(c.byref(state),Call(),None) and bytes(state) == before
        guards += 1
    assert not function(None,Call(),None); guards += 1
    vs.write_report(args,'rtl-double-multiply',{
        'status':'passed','cases_per_mode':args.cases,'complete_original_executions':counts,
        'register_callback_comparisons':sum(counts.values()),'original_path_counts':paths,
        'early_zero_cases':early,
        'targeted_double_rounding_cases':double_rounding,'nearest_results_by_pc':nearest_results,
        'negative_subnormal_high_word_cleanup_cases':cleanup,
        'software_masked_shift_cases':shift_cases,'software_masked_shift_results':shift_results,'unsupported_or_missing_error_boundary_guards':guards,
        'scope':'Whole 4db507, software bit arithmetic/error tails and masked hardware PC24/53/64 '
                'all four rounding controls. EAX/EDX/EBX/ECX, error boundary calls/context/register '
                'mutations, unchanged cache fields and preserved ESI/EDI/EBP/stack compare. '
                'Unmasked traps, x87 status/environment and error callee internals are excluded.'})


if __name__ == '__main__': main()
