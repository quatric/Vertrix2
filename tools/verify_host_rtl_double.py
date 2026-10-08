"""Verify actual lift_host double arithmetic and lift_call EAX/EDX transport."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, original_image, STACK
from verify_rtl_double_add import EDGE
from verify_rtl_single import REGISTERS
from unicorn import UC_HOOK_CODE
from unicorn.x86_const import (UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_FPCW,
                               UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP)
U = c.c_uint32
ENTRIES = ((0x4db350, 'add'), (0x4db507, 'multiply'))
MODES = [('software', 0, 0x37f)] + [(f'hardware_pc{pc}_rc{rc}', 1, 0x7f | (pc << 8) | (rc << 10))
                                  for pc in (0, 2, 3) for rc in range(4)]
HARNESS = r'''
#include "lift_host.h"
#include "lift_runtime.h"
#include <stdlib.h>
#include <string.h>

/* Isolate unrelated lifted dispatch. Float math is reached through the real public
 * host.inner.calls and caller transport through the real lift_call/call_glue implementation. */
unsigned vertrix_lifted_depth(void) { return 0; }
int vertrix_lifted_has(uint32_t target) { (void)target; return 0; }
void vertrix_lifted_calls_init(VertrixLiftedCalls *a, const VertrixCalls *inner,
    const VertrixFactoryServices *s, const VertrixGlobals *g)
{
    a->calls = *inner; a->inner = inner; a->services = s; a->globals = g;
}
typedef struct
{
    LiftHost host;
    uint32_t outputs[20], logs[22], count;
    int mutation_style;
} Fixture;
static void put(Fixture *f, uint32_t address, uint32_t value)
{
    uint8_t *p = f->host.image + address - LIFT_HOST_IMAGE_BASE;
    for (unsigned i=0; i<4; i++) p[i] = (uint8_t)(value >> (i*8));
}
static void exception(uint32_t target, VertrixRtlFloatState *s, void *context)
{
    Fixture *f = context;
    unsigned offset = f->count * 11;
    f->logs[offset] = target;
    f->logs[offset+1] = s->eax; f->logs[offset+2] = s->edx;
    f->logs[offset+3] = s->ebx; f->logs[offset+4] = s->ecx;
    f->logs[offset+5] = lift_host_read(&f->host, 0x503ea0, 4);
    f->logs[offset+6] = lift_host_read(&f->host, 0x503ea4, 4);
    f->logs[offset+7] = lift_host_read(&f->host, 0x503ea8, 4);
    f->logs[offset+8] = lift_host_read(&f->host, 0x5054a1, 1);
    f->logs[offset+9] = lift_host_read(&f->host, 0x508798, 1);
    f->logs[offset+10] = f->host.rtl_single_control;
    offset = f->count++ * 10;
    s->eax=f->outputs[offset]; s->edx=f->outputs[offset+1];
    s->ebx=f->outputs[offset+2]; s->ecx=f->outputs[offset+3];
    if (f->mutation_style)
    {
        s->helper=f->outputs[offset+4]; s->multiply=f->outputs[offset+5];
        s->divide=f->outputs[offset+6]; s->hardware=f->outputs[offset+7];
        s->capability=f->outputs[offset+8]; s->control=f->outputs[offset+9];
    }
    else
    {
        put(f, 0x503ea0, f->outputs[offset+4]); put(f, 0x503ea4, f->outputs[offset+5]);
        put(f, 0x503ea8, f->outputs[offset+6]);
        f->host.image[0x5054a1-LIFT_HOST_IMAGE_BASE]=(uint8_t)f->outputs[offset+7];
        f->host.image[0x508798-LIFT_HOST_IMAGE_BASE]=(uint8_t)f->outputs[offset+8];
        f->host.rtl_single_control=f->outputs[offset+9];
    }
}
void *fixture_create(const uint8_t *original)
{
    Fixture *f = calloc(1, sizeof *f);
    uint8_t *image = malloc(LIFT_HOST_IMAGE_SIZE), *heap=calloc(1, 4096);
    if (!f || !image || !heap) abort();
    lift_host_init(&f->host, image, original, heap, 4096);
    return f;
}
void fixture_destroy(Fixture *f)
{
    free(f->host.image); free(f->host.heap); free(f);
}
uint32_t fixture_default_control(Fixture *f) { return f->host.rtl_single_control; }
void fixture_config(Fixture *f, uint32_t helper, uint32_t multiply, uint32_t divide,
    uint32_t hardware, uint32_t capability, uint32_t control, const uint32_t *outputs,
    int configure_exception, int mutation_style)
{
    put(f, 0x503ea0, helper); put(f, 0x503ea4, multiply); put(f, 0x503ea8, divide);
    f->host.image[0x5054a1-LIFT_HOST_IMAGE_BASE]=(uint8_t)hardware;
    f->host.image[0x508798-LIFT_HOST_IMAGE_BASE]=(uint8_t)capability;
    f->host.rtl_single_control=control; f->host.rtl_single_failures=0;
    f->host.rtl_single_exception=configure_exception ? exception : NULL;
    f->host.rtl_single_exception_context=f;
    memcpy(f->outputs, outputs, sizeof f->outputs);
    memset(f->logs, 0, sizeof f->logs); f->count=0; f->mutation_style=mutation_style;
}
void fixture_run(Fixture *f, uint32_t target, uint32_t eax, uint32_t edx,
    uint32_t ebx, uint32_t ecx, int transport, uint32_t *out, uint32_t *logs)
{
    VertrixCallSite site = {0};
    site.target=target; site.eax=eax; site.edx=edx; site.ebx=ebx; site.ecx=ecx;
    if (!transport)
    {
        out[0]=f->host.inner.call(&site, f->host.inner.context);
        out[1]=site.out_value; out[2]=site.edx; out[3]=site.ebx; out[4]=site.ecx;
    }
    else
    {
        LiftEnv env = {0};
        env.calls=&f->host.inner; env.services=&f->host.services; env.globals=&f->host.globals;
        out[0]=lift_call(&env, target, eax, edx, ebx, ecx, 0, 0);
        out[1]=vertrix_lift_edx;
    }
    out[5]=lift_host_read(&f->host,0x503ea0,4);
    out[6]=lift_host_read(&f->host,0x503ea4,4);
    out[7]=lift_host_read(&f->host,0x503ea8,4);
    out[8]=f->host.rtl_single_failures; out[9]=f->count;
    out[10]=lift_host_read(&f->host,0x5054a1,1);
    out[11]=lift_host_read(&f->host,0x508798,1); out[12]=f->host.rtl_single_control;
    memcpy(logs, f->logs, sizeof f->logs);
}
'''


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('executable', type=Path)
    p.add_argument('--build-dir', type=Path, required=True)
    p.add_argument('--cases', type=int, default=4096)
    args = p.parse_args()
    if args.cases < 1:
        p.error('--cases must be positive')
    build = args.build_dir.resolve()
    build.mkdir(parents=True, exist_ok=True)
    root = Path(__file__).resolve().parents[1]
    fixture = build / 'host-double-fixture.c'
    fixture.write_text(HARNESS)
    library = build / 'host-double.dylib'
    subprocess.run(['cc', '-std=c11', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    '-I', str(root / 'source'), str(fixture),
                    *[str(root / 'source' / (name + '.c')) for name in
                      ('lift_host', 'rtl_float', 'rtl_single_multiply', 'rtl_single_divide', 'rtl_double_add', 'rtl_double_multiply',
                       'palette_tables', 'palette_color', 'render_palette',
                       'lift_imports', 'vf', 'call_glue', 'actor_storage')],
                    '-o', str(library)], check=True)
    n = c.CDLL(str(library))
    n.fixture_create.argtypes = [c.c_void_p]
    n.fixture_create.restype = c.c_void_p
    n.fixture_destroy.argtypes = [c.c_void_p]
    n.fixture_default_control.argtypes = [c.c_void_p]
    n.fixture_config.argtypes = [c.c_void_p] + [U] * 6 + [c.POINTER(U), c.c_int, c.c_int]
    n.fixture_run.argtypes = [c.c_void_p] + [U] * 5 + [c.c_int, c.POINTER(U), c.POINTER(U)]
    original = Original(args.executable)
    cpu = original.cpu
    image = original_image(original.pe)
    mapped = c.create_string_buffer(image + bytes(0x200000 - len(image)), 0x200000)
    host = n.fixture_create(mapped)
    assert n.fixture_default_control(host) == 0x037f

    rng = random.Random(0x4db350)
    log, outputs = [], []
    exception_counts = {0x4dae94: 0, 0x4e7280: 0}
    error_codes = {}
    globals_addresses = (0x503ea0, 0x503ea4, 0x503ea8)
    def live_globals():
        return tuple(int.from_bytes(cpu.mem_read(a, 4), 'little') for a in globals_addresses) + (
            int.from_bytes(cpu.mem_read(0x5054a1, 1), 'little'),
            int.from_bytes(cpu.mem_read(0x508798, 1), 'little'), cpu.reg_read(UC_X86_REG_FPCW))
    def exception(cpu, address, size, context):
        registers = tuple(cpu.reg_read(reg) for reg in REGISTERS)
        log.append((address,) + registers + live_globals())
        if address == 0x4e7280:
            error_codes[registers[0]] = error_codes.get(registers[0], 0) + 1
        values = tuple(rng.getrandbits(32) for _ in range(7)) + (
            rng.getrandbits(8), rng.getrandbits(8),
            0x7f | (rng.choice((0, 2, 3)) << 8) | (rng.randrange(4) << 10))
        outputs.extend(values)
        for address_, value in zip(globals_addresses, values[4:7]):
            cpu.mem_write(address_, struct.pack('<I', value))
        cpu.mem_write(0x5054a1, bytes([values[7]]))
        cpu.mem_write(0x508798, bytes([values[8]]))
        cpu.reg_write(UC_X86_REG_FPCW, values[9])
        for reg, value in zip(REGISTERS, values): cpu.reg_write(reg, value)
        exception_counts[address] += 1
        esp = cpu.reg_read(UC_X86_REG_ESP)
        ret = int.from_bytes(cpu.mem_read(esp, 4), 'little')
        cpu.reg_write(UC_X86_REG_ESP, esp + 4)
        cpu.reg_write(UC_X86_REG_EIP, ret)
    hooks = [cpu.hook_add(UC_HOOK_CODE, exception, begin=a, end=a) for a in exception_counts]
    totals = {name: {label: 0 for label, *_ in MODES} for _, name in ENTRIES}
    comparisons = 0
    original_count = 0
    double_rounding = {name: {} for _, name in ENTRIES}
    highword_cleanup = {name: {} for _, name in ENTRIES}
    def compare(target, a, b, hardware, control):
        nonlocal original_count, comparisons
        cache = tuple(rng.getrandbits(32) for _ in globals_addresses)
        capability = rng.getrandbits(8)
        for address, value in zip(globals_addresses, cache): cpu.mem_write(address, struct.pack('<I', value))
        cpu.mem_write(0x5054a1, bytes([hardware]))
        cpu.mem_write(0x508798, bytes([capability]))
        cpu.reg_write(UC_X86_REG_FPCW, control)
        others = tuple(rng.getrandbits(32) for _ in range(3))
        for reg, value in zip((UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP), others): cpu.reg_write(reg, value)
        inputs = (a & 0xffffffff, a >> 32, b & 0xffffffff, b >> 32)
        log.clear(); outputs.clear()
        original.call(target, eax=inputs[0], edx=inputs[1], ebx=inputs[2], ecx=inputs[3])
        expected = tuple(cpu.reg_read(reg) for reg in REGISTERS)
        live = live_globals()
        assert tuple(cpu.reg_read(reg) for reg in (UC_X86_REG_ESI, UC_X86_REG_EDI, UC_X86_REG_EBP)) == others
        assert cpu.reg_read(UC_X86_REG_ESP) == STACK + 4
        assert len(outputs) <= 20
        replay = (U * 20)(*(outputs + [0] * (20 - len(outputs))))
        for transport in (0, 1):
            for mutation_style in (0, 1):
                n.fixture_config(host, *cache, hardware, capability, control, replay, 1, mutation_style)
                out, trace = (U * 13)(), (U * 22)()
                n.fixture_run(host, target, *inputs, transport, out, trace)
                assert tuple(out[:2]) == expected[:2], (hex(target), hex(a), hex(b), hardware, hex(control), transport, mutation_style, tuple(out[:2]), expected)
                if not transport: assert tuple(out[2:5]) == expected[1:], (hex(target), 'host four registers', tuple(out), expected)
                assert tuple(out[5:8]) + tuple(out[10:13]) == live, (hex(target), 'live globals', tuple(out), live)
                assert out[8] == 0 and out[9] == len(log)
                assert [tuple(trace[i * 11:(i + 1) * 11]) for i in range(out[9])] == log, (hex(target), 'callback trace')
                comparisons += 1
        original_count += 1
        return (expected[1] << 32) | expected[0]
    guards = 0
    early = 0
    try:
        for case in range(args.cases):
            base_a = EDGE[case // len(EDGE)] if case < len(EDGE) ** 2 else rng.getrandbits(64)
            base_b = EDGE[case % len(EDGE)] if case < len(EDGE) ** 2 else rng.getrandbits(64)
            for target, name in ENTRIES:
                a, b = base_a, base_b
                if case >= len(EDGE) ** 2 and case % 2 and name == 'add':
                    exponent = max(0, min(2047, ((a >> 52) & 2047) + rng.randrange(-55, 56)))
                    b = (b & 0x800fffffffffffff) | (exponent << 52)
                if case > len(EDGE) ** 2 + 1 and case % 32 == 0:
                    a = b = 0x7fefffffffffffff
                if case == len(EDGE) ** 2:
                    a, b = ((0x3ff0000000000000, 0x3ca0010000000000) if name == 'add'
                            else (0x3ff0000000000001, 0x3ff8000000000001))
                if case == len(EDGE) ** 2 + 1:
                    a, b = ((0x8000000000000001, 0x8000000000000001) if name == 'add'
                            else (0x8000000000000001, 0x3ff0000000000000))
                for label, hardware, control in MODES:
                    result = compare(target, a, b, hardware, control)
                    if case == len(EDGE) ** 2 and label in ('hardware_pc0_rc0', 'hardware_pc2_rc0', 'hardware_pc3_rc0'):
                        double_rounding[name][label] = result
                    if case == len(EDGE) ** 2 + 1 and hardware:
                        highword_cleanup[name][label] = result
                    totals[name][label] += 1
        assert all(count == args.cases for modes in totals.values() for count in modes.values())
        assert set(error_codes) <= {0x84}
        assert exception_counts[0x4dae94] == exception_counts[0x4e7280] == error_codes.get(0x84, 0)
        if args.cases > len(EDGE) ** 2 + 1:
            assert double_rounding == {
                'add': {'hardware_pc0_rc0': 0x3ff0000000000000, 'hardware_pc2_rc0': 0x3ff0000000000001, 'hardware_pc3_rc0': 0x3ff0000000000000},
                'multiply': {'hardware_pc0_rc0': 0x3ff8000000000000, 'hardware_pc2_rc0': 0x3ff8000000000003, 'hardware_pc3_rc0': 0x3ff8000000000002}}
            assert all(value == 0 for modes in highword_cleanup.values() for value in modes.values())
        for target, name in ENTRIES:
            for a, b in ((0, 0), (0x3ff0000000000000, 0x8000000000000000), (0, 0x7ff8000000000001)):
                compare(target, a, b, 1, 0)
                early += 1
            for hardware, control in ((1, 0x37e), (1, 0x17f), (0, 0x37f)):
                a, b = (0x7fefffffffffffff, 0x7fefffffffffffff) if not hardware else (0x3ff0000000000001, 0x4000000000000002)
                inputs = (a & 0xffffffff, a >> 32, b & 0xffffffff, b >> 32)
                cache = tuple(rng.getrandbits(32) for _ in range(3))
                for transport in (0, 1):
                    n.fixture_config(host, *cache, hardware, 0, control, (U * 20)(), 0, 0)
                    out, trace = (U * 13)(), (U * 22)()
                    n.fixture_run(host, target, *inputs, transport, out, trace)
                    assert tuple(out[:2]) == inputs[:2] and tuple(out[5:8]) == cache
                    if not transport: assert tuple(out[2:5]) == inputs[1:]
                    assert tuple(out[10:13]) == (hardware, 0, control)
                    assert out[8] == 1 and out[9] == 0
                    guards += 1
        assert guards == 12 and early == 6
        assert original_count == args.cases * len(ENTRIES) * len(MODES) + early
        assert comparisons == original_count * 4
    finally:
        for hook in hooks: cpu.hook_del(hook)
        n.fixture_destroy(host)
    report = {'status': 'passed', 'cases_per_entry_and_mode': args.cases,
              'complete_original_executions': totals, 'original_math_executions': original_count,
              'actual_host_and_lift_call_comparisons': comparisons,
              'software_error_calls_per_original_target': {hex(a): n for a, n in exception_counts.items()},
              'software_error_codes': {hex(a): n for a, n in error_codes.items()},
              'targeted_double_rounding': {name: {label: hex(value) for label, value in modes.items()} for name, modes in double_rounding.items()},
              'targeted_highword_negative_cleanup': highword_cleanup,
              'unconfigured_early_zero_original_cases': early, 'unsupported_host_execution_guards': guards,
              'initialized_host_control': '0x037f',
              'scope': 'Compile actual lift_host.c and call its public inner.calls, then actual lift_call/call_glue EAX/EDX transport. Both double4db350/add and4db507/multiply execute original software and12 masked hardware PC/RC controls. Direct host EAX/EDX/EBX/ECX and caller EAX/EDX compare against original, with live cache/hardware/capability/control snapshots and exact error callback inputs/outputs. Each case repeats direct host-global and explicit callback-state mutation paths. EBX/ECX transport through lift_call is not exposed or claimed; their direct-host results are verified. Targeted x87-to-double double rounding and highword-only negative-result clearing compare actual output bits. Host guards preserve all inputs/globals and increment rtl_single_failures. Unrelated lifted dispatch and palette behavior are isolated; full game callers, callee internals, FPSW/x87 stack/pending exceptions, unmasked traps and caller flags remain outside scope.'}
    (build / 'host-rtl-double-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))

if __name__ == '__main__': main()
