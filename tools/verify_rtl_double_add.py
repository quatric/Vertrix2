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
ENTRIES = ((0x4db350, 'full'),)
MODES = [('software', 0, 0, 0x37f)] + [(f'hardware_pc{pc}_rc{rc}', 0, 1, 0x7f | (pc << 8) | (rc << 10)) for pc in (0, 2, 3) for rc in range(4)]
EDGE = (0, 0x8000000000000000, 1, 0x8000000000000001, 0xffffffff, 0x80000000ffffffff,
        0xfffffffffffff, 0x10000000000000, 0x3ff0000000000000, 0xbff0000000000000,
        0x3ca0000000000000, 0x3ca0000000000001, 0x7fefffffffffffff, 0xffefffffffffffff,
        0x7ff0000000000000, 0xfff0000000000000, 0x7ff8000000000001, 0xfff8000000000002,
        0x7ff0000000000001, 0xfff0000000000002)


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('executable', type=Path)
    parser.add_argument('--build-dir', type=Path, required=True)
    parser.add_argument('--cases', type=int, default=4096)
    args = parser.parse_args()
    if args.cases < 1:
        parser.error('--cases must be positive')
    native = build(args.build_dir, 'rtl-double-add', ['rtl_double_add.c'])
    for _, name in ENTRIES:
        fn = getattr(native, 'vertrix_rtl_double_add_' + name)
        fn.argtypes = [c.POINTER(State), Call, c.c_void_p]
    original = Original(args.executable)
    cpu = original.cpu
    rng = random.Random(0x4d809c)
    original_calls, native_calls, outputs = [], [], []
    exception_targets = {0x4dae94: 0, 0x4e7280: 0}
    paths = {'software_math': 0, 'hardware_math': 0, 'software_overflow': 0, 'software_large_gap': 0, 'software_opposite_sign': 0, 'software_negative_sum': 0, 'software_normalize': 0, 'software_subnormal': 0, 'software_round': 0, 'software_round_carry': 0}
    hit_names = {0x4db393: 'software_math', 0x4db372: 'hardware_math', 0x4e2389: 'software_overflow', 0x4db3fc: 'software_large_gap', 0x4db41f: 'software_opposite_sign', 0x4db45c: 'software_negative_sum', 0x4db492: 'software_normalize', 0x4db4f3: 'software_subnormal', 0x4db4ba: 'software_round', 0x4db4d1: 'software_round_carry'}

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
            a = EDGE[case // len(EDGE)] if case < len(EDGE) ** 2 else rng.getrandbits(64)
            b = EDGE[case % len(EDGE)] if case < len(EDGE) ** 2 else rng.getrandbits(64)
            if case >= len(EDGE) ** 2 and case % 2:
                exponent = (a >> 52) & 2047
                adjusted = max(0, min(2047, exponent + rng.randrange(-55, 56)))
                b = (b & 0x800fffffffffffff) | (adjusted << 52)
            if case >= len(EDGE) ** 2 and case % 16 == 0:
                sign = a & (1 << 63)
                a = (a & 0xfffffffffffff) | sign | (2046 << 52)
                b = (b & 0xfffffffffffff) | sign | (2046 << 52)
            for address, name in ENTRIES:
                for label, helper, hardware, control in MODES:
                    capability = 0 if label == 'hardware_lazy_cap0' else 1 if label == 'hardware_lazy_cap1' else rng.getrandbits(8)
                    state = State(a & 0xffffffff, a >> 32, b & 0xffffffff, b >> 32, rng.getrandbits(32),
                                  rng.getrandbits(32), rng.getrandbits(32), hardware, capability, control)
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
                    original.call(address, eax=state.eax, edx=state.edx, ebx=state.ebx, ecx=state.ecx)
                    expected = tuple(cpu.reg_read(reg) for reg in REGISTERS)
                    cached = tuple(int.from_bytes(cpu.mem_read(location, 4), 'little')
                                   for location in (0x503ea0, 0x503ea4, 0x503ea8))
                    assert getattr(native, 'vertrix_rtl_double_add_' + name)(c.byref(state), call, None)
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
    assert exception_targets[0x4dae94] == paths['software_overflow']
    assert exception_targets[0x4e7280] == paths['software_overflow']
    if args.cases >= len(EDGE) ** 2:
        assert all(paths.values()), paths
    early = 0
    for hardware in (0, 1):
        for a, b in ((0x3ff0000000000000, 0), (0, 0x3ff0000000000000),
                     (0, 0x8000000000000000), (0x3ff0000000000000, 0x8000000000000000)):
            state = State(a & 0xffffffff, a >> 32, b & 0xffffffff, b >> 32, 5, 6, 7, hardware, 9, 0)
            cpu.mem_write(0x5054a1, bytes([hardware]))
            cpu.reg_write(UC_X86_REG_FPCW, 0)
            original.call(0x4db350, eax=state.eax, edx=state.edx, ebx=state.ebx, ecx=state.ecx)
            expected = tuple(cpu.reg_read(reg) for reg in REGISTERS)
            assert native.vertrix_rtl_double_add_full(c.byref(state), Call(), None)
            assert tuple(getattr(state, name) for name in FIELDS[:4]) == expected
            assert (state.helper, state.multiply, state.divide, state.hardware, state.capability, state.control) == (5, 6, 7, hardware, 9, 0)
            assert cpu.reg_read(UC_X86_REG_ESP) == STACK + 4
            early += 1
    assert early == 8
    guards = 0
    fn = native.vertrix_rtl_double_add_full
    assert not fn(None, Call(), None)
    guards += 1
    for control in (0x37e, 0x17f):
        state = State(1, 0x3ff00000, 2, 0x40000000, 5, 6, 7, 1, 0, control)
        before = bytes(state)
        assert not fn(c.byref(state), Call(), None)
        assert bytes(state) == before
        guards += 1
    state = State(0xffffffff, 0x7fefffff, 0xffffffff, 0x7fefffff, 5, 6, 7, 0, 0, 0)
    before = bytes(state)
    assert not fn(c.byref(state), Call(), None)
    assert bytes(state) == before
    guards += 1
    assert guards == 4
    report = {'status': 'passed', 'cases_per_mode': args.cases, 'complete_original_executions': totals,
              'register_cache_control_callback_comparisons': executions, 'original_path_counts': paths,
              'unconfigured_early_zero_original_executions': early,
              'unsupported_control_or_missing_boundary_guards': guards,
              'live_callback_register_cache_control_mutations': sum(exception_targets.values()),
              'error_boundary_calls': {hex(a): n for a, n in exception_targets.items()},
              'scope': 'Original4db350 double addition EDX:EAX plus ECX:EBX, software integer arithmetic and masked hardware precision24/53/64 at all rounding modes. Exact EAX/EDX/EBX/ECX, helper globals, hardware/capability/control, preserved registers/stack and arbitrary error-boundary register/global mutations compare independently. FPSW/x87 stack/pending exceptions and unmasked traps remain outside scope.'}
    (args.build_dir / 'rtl-double-add-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))

if __name__ == '__main__': main()
