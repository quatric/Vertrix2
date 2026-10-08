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
ENTRIES = ((0x4d8227, 'software_full'), (0x4d81fe, 'software_entry'), (0x4d81fe, 'full'))
MODES = [('software_cached', 0x4d80d5, 0, 0x37f), ('software_lazy', 0x4d82a5, 0, 0x37f)]
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
    native = build(args.build_dir, 'rtl-single-divide', ['rtl_single_divide.c'])
    for _, name in ENTRIES:
        fn = getattr(native, 'vertrix_rtl_single_divide_' + name)
        fn.argtypes = [c.POINTER(State), Call, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4d809c)
    original_calls, native_calls, outputs = [], [], []
    exception_targets = {0x4dae94: 0, 0x4e7280: 0}
    paths = {'software_underflow_tail': 0, 'software_overflow_tail': 0,
             'software_math': 0, 'divide_zero': 0, 'lazy_initializer': 0}
    hit_names = {0x4e236e: 'software_underflow_tail', 0x4e23b5: 'software_overflow_tail',
                 0x4d8227: 'software_math', 0x4e23a9: 'divide_zero',
                 0x4d82c6: 'lazy_initializer'}

    def hit(cpu, address, size, context):
        if address in hit_names:
            paths[hit_names[address]] += 1
            return
        exception_targets[address] += 1
        registers = tuple(cpu.reg_read(reg) for reg in REGISTERS)
        live = tuple(int.from_bytes(cpu.mem_read(location, 4), 'little') for location in (0x503ea0, 0x503ea4, 0x503ea8)) + (int.from_bytes(cpu.mem_read(0x5054a1, 1), 'little'), int.from_bytes(cpu.mem_read(0x508798, 1), 'little'), cpu.reg_read(UC_X86_REG_FPCW))
        original_calls.append((address,) + registers + live)
        output = tuple(rng.getrandbits(32) for _ in range(4))
        output += tuple(rng.getrandbits(32) for _ in range(3)) + (rng.getrandbits(8), rng.getrandbits(8), 0x7f | (rng.choice((0, 2, 3)) << 8) | (rng.randrange(4) << 10))
        outputs.append(output)
        for location, value in zip((0x503ea0, 0x503ea4, 0x503ea8), output[4:7]):
            cpu.mem_write(location, struct.pack('<I', value))
        cpu.mem_write(0x5054a1, bytes([output[7]]))
        cpu.mem_write(0x508798, bytes([output[8]]))
        cpu.reg_write(UC_X86_REG_FPCW, output[9])
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
        native_calls.append((target,) + tuple(getattr(s, field) for field in FIELDS))
        output = outputs[len(native_calls) - 1]
        for field, value in zip(FIELDS, output):
            setattr(s, field, value)

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
                    state = State(a, b, rng.getrandbits(32), rng.getrandbits(32), helper,
                                  rng.getrandbits(32), 0x4d82bb if label == 'software_lazy' else 0x4d8227, hardware, capability, control)
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
    assert exception_targets[0x4dae94] == paths['software_overflow_tail']
    assert exception_targets[0x4e7280] == paths['software_overflow_tail'] + paths['divide_zero']
    if args.cases >= len(EDGE) ** 2:
        assert all(paths.values()), paths
    guards = 0
    for name in ('software_full', 'software_entry'):
        fn = getattr(native, 'vertrix_rtl_single_divide_' + name)
        assert not fn(None, Call(), None)
        guards += 1
        for a, b in ((1, 0), (0x7f000000, 0x00800000)):
            state = State(a, b, 3, 4, 0x4d80d5, 0x4d8198, 0x4d8227, 0, 0, 0x37f)
            before = bytes(state)
            assert not fn(c.byref(state), Call(), None)
            assert bytes(state) == before
            guards += 1
    for divide, hardware in ((0xdeadbeef, 0), (0x4d8204, 1), (0x4d8217, 1), (0x4d82bb, 1)):
        state = State(0, 0, 3, 4, 5, 6, divide, hardware, 0, 0x37f)
        before = bytes(state)
        assert not native.vertrix_rtl_single_divide_software_entry(c.byref(state), call, None)
        assert bytes(state) == before
        guards += 1
    assert guards == 10
    report = {'status': 'passed', 'cases_per_entry_and_mode': args.cases,
              'complete_original_executions': totals, 'register_cache_and_callback_comparisons': executions,
              'original_path_counts': paths,
              'unsupported_or_missing_boundary_guards': guards,
              'callback_register_cache_control_mutations': sum(exception_targets.values()),
              'error_boundary_calls': {hex(a): n for a, n in exception_targets.items()},
              'scope': 'Full software helper 4d8227, legacy software-only entry and full entry software cached/lazy routes of 4d81fe. Raw EAX/EDX/EBX/ECX, cache writes, callback live register/cache/control inputs and arbitrary mutations, preserved ESI/EDI/EBP and stack compare against executable. Hardware routes and capability helper as used by single division are verified separately in rtl-single-divide-hardware-verification.json. Unmasked exceptions and extended x87 environment remain outside scope.'}
    (args.build_dir / 'rtl-single-divide-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))

if __name__ == '__main__':
    main()
