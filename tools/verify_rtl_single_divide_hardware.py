"""Execute original software single division, comparing registers and cached helper selection."""
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
ENTRIES = ((0x4d81fe, 'full'),)
MODES = [(f'hardware{cap}_pc{pc}_rc{rc}_{lazy}', 0x4d82a5 if lazy else 0x4d80b7, 1, 0x7f | (pc << 8) | (rc << 10)) for cap in (0, 1) for pc in (0, 2, 3) for rc in range(4) for lazy in (0, 1)]
EDGE = (0, 0x80000000, 1, 0x80000001, 0x7fffff, 0x800000, 0x3f800000, 0xbf800000,
        0x33800000, 0x33800001, 0x7f7fffff, 0xff7fffff, 0x7f800000, 0xff800000,
        0x7fc00001, 0xffc00002, 0x7f800001, 0xff800002, 0x3f8f0000, 0x3fa70000, 0x3fbf0000, 0x3fd70000, 0x3fef0000)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    if args.cases < 1:
        parser.error('--cases must be positive')
    native = build(args.build_dir, 'rtl-single-divide', ['rtl_single_divide.c'])
    for _, name in ENTRIES:
        fn = getattr(native, 'vertrix_rtl_single_divide_' + name)
        fn.argtypes = [c.POINTER(State), Call, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4d809c)
    original_calls, native_calls, outputs = [], [], []
    exception_targets = {0x4dae94: 0, 0x4e7280: 0}
    paths = {'hardware_capability': 0, 'hardware_direct': 0, 'lazy_initializer': 0, 'capability_scale': 0, 'capability_nonfinite': 0, 'capability_regular': 0}
    hit_names = {0x4d8204: 'hardware_capability', 0x4d8217: 'hardware_direct', 0x4d82c6: 'lazy_initializer', 0x4e1c94: 'capability_scale', 0x4e2280: 'capability_nonfinite', 0x4e1c70: 'capability_regular'}

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
        output = outputs[len(native_calls) - 1]
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
                    capability = int(label[8])
                    state = State(a, b, rng.getrandbits(32), rng.getrandbits(32), helper,
                                  rng.getrandbits(32), 0x4d82bb if label.endswith('_1') else 0x4d8204 if capability else 0x4d8217, hardware, capability, control)
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
                    original.call(address, eax=a, edx=b, ebx=state.ebx, ecx=state.ecx)
                    expected = tuple(cpu.reg_read(reg) for reg in REGISTERS)
                    cached = tuple(int.from_bytes(cpu.mem_read(location, 4), 'little')
                                   for location in (0x503ea0, 0x503ea4, 0x503ea8))
                    assert getattr(native, 'vertrix_rtl_single_divide_' + name)(c.byref(state), call, None)
                    got = (state.eax, state.edx, state.ebx, state.ecx)
                    assert got == expected, (case, name, label, hex(a), hex(b),
                                             tuple(hex(v) for v in got), tuple(hex(v) for v in expected))
                    assert (state.helper, state.multiply, state.divide) == cached, (case, name, label, 'cache')
                    assert (state.hardware, state.capability, state.control) == (int.from_bytes(cpu.mem_read(0x5054a1, 1), 'little'), int.from_bytes(cpu.mem_read(0x508798, 1), 'little'), cpu.reg_read(UC_X86_REG_FPCW))
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
    assert not any(exception_targets.values())
    if args.cases >= len(EDGE) ** 2:
        assert all(paths.values()), paths
    guards = 0
    fn = native.vertrix_rtl_single_divide_full
    for divide in (0x4d8204, 0x4d8217, 0x4d82bb):
        for control in (0x37e, 0x17f):
            state = State(0x3f800000, 0x40400000, 3, 4, 5, 6, divide, 1, 1, control)
            before = bytes(state)
            assert not fn(c.byref(state), call, None)
            assert bytes(state) == before
            guards += 1
    state = State(0, 0, 3, 4, 5, 6, 0xdeadbeef, 0, 0, 0x37f)
    before = bytes(state)
    assert not fn(c.byref(state), call, None)
    assert bytes(state) == before
    assert not fn(None, call, None)
    guards += 2
    assert guards == 8
    report = {'status': 'passed', 'cases_per_mode': args.cases, 'complete_original_executions': totals,
              'register_control_cache_comparisons': executions, 'original_path_counts': paths,
              'unsupported_control_or_cache_guards': guards,
              'scope': 'Hardware cached/lazy 4d81fe, both 4d8204 and 4d8217, masked precision24/53/64 and all rounding controls. Capability helper4e223c as used by single division (single ST0 numerator and single stack denominator) executes original FDIV workaround including scale15/16 and control restoration. EAX/EDX/EBX/ECX, cache globals, control word, preserved registers and stack compare. FPSW, extended x87 stack contents, pending exceptions and unmasked traps remain outside scope.'}
    (args.build_dir / 'rtl-single-divide-hardware-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))

if __name__ == '__main__':
    main()
