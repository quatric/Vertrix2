"""Execute original single multiplication math, comparing registers and cached helper selection."""
import argparse
import ctypes as c
import json
import random
import struct
from pathlib import Path
from original import Original, STACK
from oracle_kit import build
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX,
                               UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP,
                               UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_FPCW)

U = c.c_uint32
FIELDS = ('eax', 'edx', 'ebx', 'ecx', 'helper', 'multiply', 'divide',
          'hardware', 'capability', 'control')


class State(c.Structure):
    _fields_ = [(name, U) for name in FIELDS]


Call = c.CFUNCTYPE(None, U, c.POINTER(State), c.c_void_p)
REGISTERS = (UC_X86_REG_EAX, UC_X86_REG_EDX, UC_X86_REG_EBX, UC_X86_REG_ECX)
ENTRIES = ((0x4d8177, 'multiply'),)
MODES = [('software_cached', 0x4d8198, 1, 0x37f),
         ('software_lazy', 0x4d82b0, 0, 0x37f)] + [
    (f'hardware_pc{pc}_rc{rc}', 0x4d8188, 0, 0x7f | (pc << 8) | (rc << 10))
    for pc in (0, 2, 3) for rc in range(4)] + [
    ('hardware_lazy_cap0', 0x4d82b0, 1, 0x37f),
    ('hardware_lazy_cap1', 0x4d82b0, 1, 0x37f)]
EDGE = (0, 0x80000000, 1, 0x80000001, 0x7fffff, 0x800000, 0x3f800000, 0xbf800000,
        0x33800000, 0x33800001, 0x7f7fffff, 0xff7fffff, 0x7f800000, 0xff800000,
        0x7fc00001, 0xffc00002, 0x7f800001, 0xff800002)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    if args.cases < 1:
        parser.error('--cases must be positive')
    native = build(args.build_dir, 'rtl-single-multiply', ['rtl_single_multiply.c'])
    for _, name in ENTRIES:
        fn = getattr(native, 'vertrix_rtl_single_' + name + '_full')
        fn.argtypes = [c.POINTER(State), Call, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4d8177)
    original_calls, native_calls, outputs, contexts = [], [], [], []
    exception_targets = {0x4dae94: 0, 0x4e7280: 0}
    paths = {'software_underflow_tail': 0, 'software_overflow_tail': 0,
             'software_math': 0, 'hardware_math': 0, 'lazy_initializer': 0}
    hit_names = {0x4e236e: 'software_underflow_tail', 0x4e23b5: 'software_overflow_tail',
                 0x4d8198: 'software_math', 0x4d8188: 'hardware_math',
                 0x4d82c6: 'lazy_initializer'}

    def hit(cpu, address, size, context):
        if address in hit_names:
            paths[hit_names[address]] += 1
            return
        exception_targets[address] += 1
        registers = tuple(cpu.reg_read(reg) for reg in REGISTERS)
        original_calls.append((address,) + registers)
        output = tuple(rng.getrandbits(32) for _ in range(4))
        outputs.append(output)
        for reg, value in zip(REGISTERS, output):
            cpu.reg_write(reg, value)
        esp = cpu.reg_read(UC_X86_REG_ESP)
        target = int.from_bytes(cpu.mem_read(esp, 4), 'little')
        cpu.reg_write(UC_X86_REG_ESP, esp + 4)
        cpu.reg_write(UC_X86_REG_EIP, target)

    hooks = [cpu.hook_add(UC_HOOK_CODE, hit, begin=a, end=a)
             for a in tuple(hit_names) + (0x4dae94, 0x4e7280)]

    @Call
    def call(target, state, context):
        s = state.contents
        native_calls.append((target, s.eax, s.edx, s.ebx, s.ecx))
        contexts.append(context)
        output = outputs[len(native_calls) - 1] if len(native_calls) <= len(outputs) else (0, 0, 0, 0)
        s.eax, s.edx, s.ebx, s.ecx = output

    totals = {name: {label: 0 for label, *_ in MODES} for _, name in ENTRIES}
    try:
        for case in range(args.cases):
            # All edge pairs execute before random words; random bit patterns include
            # subnormals, infinities and NaNs without treating software as IEEE arithmetic.
            a = EDGE[case // len(EDGE)] if case < len(EDGE) ** 2 else rng.getrandbits(32)
            b = EDGE[case % len(EDGE)] if case < len(EDGE) ** 2 else rng.getrandbits(32)
            for address, name in ENTRIES:
                for label, helper, hardware, control in MODES:
                    capability = 0 if label == 'hardware_lazy_cap0' else 1 if label == 'hardware_lazy_cap1' else rng.getrandbits(8)
                    state = State(a, b, rng.getrandbits(32), rng.getrandbits(32),
                                  rng.getrandbits(32), helper, rng.getrandbits(32), hardware, capability, control)
                    for location, value in zip((0x503ea0, 0x503ea4, 0x503ea8),
                                               (state.helper, state.multiply, state.divide)):
                        cpu.mem_write(location, struct.pack('<I', value))
                    cpu.mem_write(0x5054a1, bytes([hardware]))
                    cpu.mem_write(0x508798, bytes([capability]))
                    cpu.reg_write(UC_X86_REG_FPCW, control)
                    others = tuple(rng.getrandbits(32) for _ in range(3))
                    for reg, value in zip((UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP), others):
                        cpu.reg_write(reg, value)
                    original_calls.clear()
                    native_calls.clear()
                    outputs.clear()
                    contexts.clear()
                    original.call(address, eax=a, edx=b, ebx=state.ebx, ecx=state.ecx)
                    expected = tuple(cpu.reg_read(reg) for reg in REGISTERS)
                    cached = tuple(int.from_bytes(cpu.mem_read(location, 4), 'little')
                                   for location in (0x503ea0, 0x503ea4, 0x503ea8))
                    assert getattr(native, 'vertrix_rtl_single_' + name + '_full')(c.byref(state), call, 0x1234)
                    got = (state.eax, state.edx, state.ebx, state.ecx)
                    assert got == expected, (case, name, label, hex(a), hex(b),
                                             tuple(hex(v) for v in got), tuple(hex(v) for v in expected))
                    assert (state.helper, state.multiply, state.divide) == cached, (case, name, label, 'cache')
                    assert all(x == 0x1234 for x in contexts)
                    assert original_calls == native_calls, (case, name, label, original_calls, native_calls)
                    assert tuple(cpu.reg_read(reg) for reg in (UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP)) == others
                    assert cpu.reg_read(UC_X86_REG_ESP) == STACK + 4
                    totals[name][label] += 1
    finally:
        for hook in hooks:
            cpu.hook_del(hook)
    assert all(count == args.cases for modes in totals.values() for count in modes.values())
    executions = sum(sum(modes.values()) for modes in totals.values())
    assert executions == args.cases * len(MODES) * len(ENTRIES)
    assert exception_targets[0x4dae94] == paths['software_overflow_tail']
    assert exception_targets[0x4e7280] == paths['software_overflow_tail']
    if args.cases >= len(EDGE) ** 2:
        assert all(paths.values()), paths
    early = 0
    for address, name in ENTRIES:
        fn = getattr(native, 'vertrix_rtl_single_' + name + '_full')
        for a, b in ((0, 0), (0x3f800000, 0), (0, 0x3f800000), (0, 0x80000000)):
            state = State(a, b, 3, 4, 0xdeadbeef, 5, 6, 1, 1, 0)
            for location, value in zip((0x503ea0, 0x503ea4, 0x503ea8),
                                       (state.helper, state.multiply, state.divide)):
                cpu.mem_write(location, struct.pack('<I', value))
            cpu.reg_write(UC_X86_REG_FPCW, 0)
            expected = original.call(address, eax=a, edx=b, ebx=3, ecx=4)
            edx = cpu.reg_read(UC_X86_REG_EDX)
            assert fn(c.byref(state), Call(), None)
            assert (state.eax, state.edx, state.ebx, state.ecx) == (expected, edx, 3, 4)
            assert (state.helper, state.multiply, state.divide) == (0xdeadbeef, 5, 6)
            assert tuple(int.from_bytes(cpu.mem_read(location, 4), 'little')
                         for location in (0x503ea0, 0x503ea4, 0x503ea8)) == (0xdeadbeef, 5, 6)
            early += 1
    assert early == 4
    # Exact product lies just above half the smallest single subnormal. PC24 rounds
    # the intermediate down to the halfway value; PC53/64 retain the deciding bits.
    double_rounding = 0
    double_results = {}
    fn = native.vertrix_rtl_single_multiply_full
    for sign in (0, 0x80000000):
        for pc in (0, 2, 3):
            for rc in range(4):
                control = 0x7f | (pc << 8) | (rc << 10)
                state = State(0x00800001 | sign, 0x337fffff, 0x12345678, 0xabcdef01,
                              5, 0x4d8188, 6, 0, 0, control)
                cpu.mem_write(0x503ea4, struct.pack('<I', state.multiply))
                cpu.reg_write(UC_X86_REG_FPCW, control)
                wanted = original.call(0x4d8177, eax=state.eax, edx=state.edx,
                                       ebx=state.ebx, ecx=state.ecx)
                assert fn(c.byref(state), Call(), None)
                assert (state.eax, state.edx, state.ebx, state.ecx) == \
                    (wanted, 0x337fffff, 0x12345678, 0xabcdef01)
                if not sign and rc == 0:
                    double_results[str(pc)] = wanted
                double_rounding += 1
    assert double_rounding == 24 and double_results == {'0': 0, '2': 1, '3': 1}
    guards = 0
    for _, name in ENTRIES:
        fn = getattr(native, 'vertrix_rtl_single_' + name + '_full')
        for helper, control, a, b in ((0xdeadbeef, 0x37f, 0x3f800000, 0x3f000000),
                                      (0x4d8188, 0x37e, 0x3f800000, 0x3f000000),
                                      (0x4d8188, 0x17f, 0x3f800000, 0x3f000000),
                                      (0x4d8198, 0x37f, 0x7f7fffff, 0x7f7fffff)):
            state = State(a, b, 3, 4, 5, helper, 6, 0, 0, control)
            before = bytes(state)
            assert not fn(c.byref(state), Call(), None)
            assert bytes(state) == before
            guards += 1
        assert not fn(None, Call(), None)
        guards += 1
    assert guards == 5
    report = {
        'status': 'passed', 'cases_per_entry_and_mode': args.cases,
        'complete_original_executions': totals, 'register_cache_and_callback_comparisons': executions,
        'original_path_counts': paths,
        'software_overflow_boundary_calls': {hex(a): count for a, count in exception_targets.items()},
        'unconfigured_early_zero_cases': early,
        'targeted_subnormal_double_rounding_cases': double_rounding,
        'positive_nearest_double_rounding_results_by_pc': double_results,
        'unsupported_or_missing_boundary_guards': guards,
        'scope': 'Original 4d8177 multiplication executes its actual software '
                 '4d8198 and hardware 4d8188 arithmetic. EAX/EDX/EBX/ECX, lazy helper cache writes, '
                 'preserved ESI/EDI/EBP and stack cleanup compare exactly. Software overflow '
                 '4dae94/4e7280 callees are explicit boundaries with matching input registers '
                 'and arbitrary returned register mutations; their callee internals are outside '
                 'this proof. Software underflow tail 4e236e executes unchanged. Hardware proves '
                 'masked x87 rounding with precision 24/53/64 and all four rounding controls, '
                 'including signed zero, subnormals, NaNs and infinities. Early-zero paths execute '
                 'before cache initialization. Unmasked x87 exceptions, FPSW/environment, pending '
                 'x87 exceptions and arbitrary custom helper pointers remain unsupported and '
                 'unverified; native rejects unsupported execution without changing supplied state.'}
    (args.build_dir / 'rtl-single-multiply-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
