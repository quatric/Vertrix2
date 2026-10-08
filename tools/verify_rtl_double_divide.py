"""Verify exact original double division registers, software/errors and masked x87 modes."""
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
    native = build(args.build_dir, 'rtl-double-divide', ['rtl_double_divide.c'])
    function = native.vertrix_rtl_double_divide_full
    function.argtypes = [c.POINTER(State), Call, c.c_void_p]
    original = Original(args.executable); cpu = original.cpu
    rng = random.Random(0x4eb652)
    oracle_calls, native_calls, outputs, contexts = [], [], [], []
    paths = {hex(a): 0 for a in (0x4eb6a5, 0x4eb675, 0x4eb6e8, 0x4eb703,
                                0x4eb82c, 0x4e236c, 0x4e2389, 0x4e237d, 0x4e2288, 0x4e1c94)}
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
    def compare(a, b, hardware, control, capability=None):
        state = State(a & 0xffffffff, a >> 32, b & 0xffffffff, b >> 32,
                      rng.getrandbits(32), rng.getrandbits(32), rng.getrandbits(32),
                      hardware, rng.getrandbits(8), control)
        if capability is not None: state.capability = capability
        unchanged = (state.helper, state.divide, state.divide, state.hardware, state.capability, state.control)
        cpu.mem_write(0x5054a1, bytes([hardware])); cpu.mem_write(0x508798, bytes([state.capability])); cpu.reg_write(UC_X86_REG_FPCW, control)
        others = tuple(rng.getrandbits(32) for _ in range(3))
        for register, value in zip((UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP), others): cpu.reg_write(register,value)
        oracle_calls.clear(); native_calls.clear(); outputs.clear(); contexts.clear()
        original.call(0x4eb652, eax=state.eax, edx=state.edx, ebx=state.ebx, ecx=state.ecx)
        expected = tuple(cpu.reg_read(reg) for reg in REGS)
        assert function(c.byref(state), call, 0x1234)
        got = (state.eax, state.edx, state.ebx, state.ecx)
        assert got == expected, (hex(a), hex(b), hardware, hex(control), tuple(hex(v) for v in got), tuple(hex(v) for v in expected))
        assert oracle_calls == native_calls, (hex(a),hex(b),oracle_calls,native_calls)
        assert all(context == 0x1234 for context in contexts)
        assert (state.helper, state.divide, state.divide, state.hardware, state.capability, state.control) == unchanged
        assert tuple(cpu.reg_read(reg) for reg in (UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP)) == others
        assert cpu.reg_read(UC_X86_REG_ESP) == STACK + 4
        return (state.edx << 32) | state.eax
    counts = {name: 0 for name, _, _ in MODES}
    for case in range(args.cases):
        a = EDGE[case // len(EDGE)] if case < len(EDGE)**2 else rng.getrandbits(64)
        b = EDGE[case % len(EDGE)] if case < len(EDGE)**2 else rng.getrandbits(64)
        for name, hardware, control in MODES:
            compare(a,b,hardware,control); counts[name] += 1
    workaround = 0
    for index in (1,4,7,10,13):
        divisor = 0x3ff0000000000000 | (((index<<28)|0x0e000000)>>1 & 0x7fffffff)<<21
        for pc in (0,2,3):
            for rc in range(4):
                for capability in (0,1,254,255):
                    compare(0x400921fb54442d18, divisor, 1, 0x7f|(pc<<8)|(rc<<10), capability)
                    workaround += 1
    double_rounding = 0; nearest_results = {}
    for sign in (0,0x8000000000000000):
        for pc in (0,2,3):
            for rc in range(4):
                for capability in (0,1):
                    value=compare(0x3ff32c02ce07e098|sign,0x3ff29fb52745aa10,1,0x7f|(pc<<8)|(rc<<10),capability)
                    if not sign and rc==0: nearest_results[str(pc)]=hex(value)
                    double_rounding += 1
    assert nearest_results['2']=='0x3ff0788953000dc9' and nearest_results['3']=='0x3ff0788953000dca'
    cleanup=0
    for pc in (0,2,3):
        for rc in range(4):
            assert compare(0x8010000000000000,0x4330000000000000,1,0x7f|(pc<<8)|(rc<<10),1)==0
            cleanup += 1
    shift_results={}
    for exponent in (-1,-2,-32,-33,-52,-53):
        shift_results[str(exponent)]=hex(compare(0x0010000000000001,(1024-exponent)<<52,0,0x37f))
    early = 0
    for numerator,denominator in ((0,0x3ff0000000000000),(0x8000000000000000,0x3ff0000000000000),(0,0),(0x8000000000000000,0x8000000000000000)):
        compare(numerator,denominator,1,0,1); early += 1
    guards = 0
    for hardware, control, numerator, denominator in ((1,0x37e,0x3ff0000000000000,0x3ff0000000000000),(1,0x17f,0x3ff0000000000000,0x3ff0000000000000),(0,0x37f,0x3ff0000000000000,0),(0,0x37f,0x7fefffffffffffff,1)):
        state=State(numerator&0xffffffff,numerator>>32,denominator&0xffffffff,denominator>>32,1,2,3,hardware,1,control)
        before=bytes(state)
        assert not function(c.byref(state),Call(),None) and bytes(state)==before
        guards += 1
    assert not function(None,Call(),None); guards += 1
    for h in hooks: cpu.hook_del(h)
    assert all(count == args.cases for count in counts.values())
    if args.cases >= len(EDGE)**2: assert all(paths.values()), paths
    vs.write_report(args,'rtl-double-divide',{'status':'passed','cases_per_mode':args.cases,
        'complete_original_executions':counts,'register_callback_comparisons':sum(counts.values()),
        'original_path_counts':paths,'targeted_workaround_dispatch_cases':workaround,'targeted_double_rounding_cases':double_rounding,'nearest_results_by_pc':nearest_results,'negative_subnormal_high_word_cleanup_cases':cleanup,'software_masked_shift_results':shift_results,'early_zero_or_error_precedence_cases':early,'unsupported_or_missing_error_boundary_guards':guards,'scope':'Whole 4eb652 software/error and masked hardware PC24/53/64 all rounding modes. Exact registers, callback inputs/outputs/context and preserved callee registers/stack. Unmasked traps, x87 status/environment and error callee internals excluded.'})

if __name__ == '__main__': main()
