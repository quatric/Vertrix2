"""Prove the live lift_host.c single boundaries and lift_call EDX transport against original math."""
import argparse
import ctypes as c
import json
import random
import struct
import subprocess
from pathlib import Path
from original import Original, original_image
from verify_rtl_single import MODES as ADD_MODES, REGISTERS
from verify_rtl_single_multiply import MODES as MULTIPLY_MODES
from verify_rtl_single_divide_hardware import MODES as DIVIDE_HARDWARE_MODES, EDGE

ENTRIES = ((0x4d809c, 'subtract'), (0x4d80a6, 'add'),
           (0x4d8177, 'multiply'), (0x4d81fe, 'divide'))
MODES = {'subtract': ADD_MODES, 'add': ADD_MODES, 'multiply': MULTIPLY_MODES,
         'divide': [('software_cached', 0x4d8227, 1, 0x37f),
                    ('software_lazy', 0x4d82bb, 0, 0x37f)] + DIVIDE_HARDWARE_MODES}


def caches(name, label, selected, rng):
    values = [rng.getrandbits(32) for _ in range(3)]
    slot = 1 if name == 'multiply' else 2 if name == 'divide' else 0
    if name == 'divide' and label.startswith('hardware'):
        values[0] = selected
        values[2] = 0x4d82bb if label.endswith('_1') else 0x4d8204 if int(label[8]) else 0x4d8217
    else:
        values[slot] = selected
    return values

from unicorn import UC_HOOK_CODE
from unicorn.x86_const import UC_X86_REG_ESP, UC_X86_REG_EIP, UC_X86_REG_FPCW

U = c.c_uint32
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
    fixture = build / 'host-single-fixture.c'
    fixture.write_text(HARNESS)
    library = build / 'host-single.dylib'
    subprocess.run(['cc', '-std=c11', '-shared', '-fPIC', '-O2', '-Wall', '-Wextra', '-Werror',
                    '-I', str(root / 'source'), str(fixture),
                    *[str(root / 'source' / (name + '.c')) for name in
                      ('lift_host', 'rtl_float', 'rtl_single_multiply', 'rtl_single_divide',
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
    rng = random.Random(0x503ea0)
    log, outputs = [], []
    exception_counts = {0x4dae94: 0, 0x4e7280: 0}
    error_codes = {0x83: 0, 0x84: 0}

    def exception(cpu, address, size, context):
        cache = tuple(int.from_bytes(cpu.mem_read(a, 4), 'little') for a in (0x503ea0, 0x503ea4, 0x503ea8))
        live = cache + (int.from_bytes(cpu.mem_read(0x5054a1, 1), 'little'),
                        int.from_bytes(cpu.mem_read(0x508798, 1), 'little'), cpu.reg_read(UC_X86_REG_FPCW))
        registers = tuple(cpu.reg_read(reg) for reg in REGISTERS)
        log.append((address,) + registers + live)
        if address == 0x4e7280:
            assert registers[0] in error_codes
            error_codes[registers[0]] += 1
        output = tuple(rng.getrandbits(32) for _ in range(4))
        output += tuple(rng.getrandbits(32) for _ in range(3)) + (rng.getrandbits(8), rng.getrandbits(8),
                    0x7f | (rng.choice((0, 2, 3)) << 8) | (rng.randrange(4) << 10))
        outputs.extend(output)
        for location, value in zip((0x503ea0, 0x503ea4, 0x503ea8), output[4:7]):
            cpu.mem_write(location, struct.pack('<I', value))
        cpu.mem_write(0x5054a1, bytes([output[7]])); cpu.mem_write(0x508798, bytes([output[8]]))
        cpu.reg_write(UC_X86_REG_FPCW, output[9])
        for reg, value in zip(REGISTERS, output):
            cpu.reg_write(reg, value)
        exception_counts[address] += 1
        esp = cpu.reg_read(UC_X86_REG_ESP)
        ret = int.from_bytes(cpu.mem_read(esp, 4), 'little')
        cpu.reg_write(UC_X86_REG_ESP, esp + 4)
        cpu.reg_write(UC_X86_REG_EIP, ret)

    hooks = [cpu.hook_add(UC_HOOK_CODE, exception, begin=a, end=a) for a in exception_counts]
    double_rounding = {}
    totals = {name: {label: 0 for label, *_ in MODES[name]} for _, name in ENTRIES}
    try:
        for case in range(args.cases):
            a = EDGE[case // len(EDGE)] if case < len(EDGE) ** 2 else rng.getrandbits(32)
            b = EDGE[case % len(EDGE)] if case < len(EDGE) ** 2 else rng.getrandbits(32)
            if case in (len(EDGE) ** 2, len(EDGE) ** 2 + 1):
                a = 0x00800001 | (0x80000000 if case == len(EDGE) ** 2 + 1 else 0)
                b = 0x337fffff
            for target, name in ENTRIES:
                for label, selected, hardware, control in MODES[name]:
                    capability = int(label[8]) if name == 'divide' and label.startswith('hardware') else (
                        0 if label == 'hardware_lazy_cap0' else 1 if label == 'hardware_lazy_cap1' else rng.getrandbits(8))
                    helper, multiply, divide = caches(name, label, selected, rng)
                    ebx, ecx = rng.getrandbits(32), rng.getrandbits(32)
                    for location, value in ((0x503ea0, helper), (0x503ea4, multiply), (0x503ea8, divide)):
                        cpu.mem_write(location, struct.pack('<I', value))
                    cpu.mem_write(0x5054a1, bytes([hardware]))
                    cpu.mem_write(0x508798, bytes([capability]))
                    cpu.reg_write(UC_X86_REG_FPCW, control)
                    log.clear(); outputs.clear()
                    original.call(target, eax=a, edx=b, ebx=ebx, ecx=ecx)
                    expected = tuple(cpu.reg_read(reg) for reg in REGISTERS)
                    if case == len(EDGE) ** 2 and name == 'multiply' and label in (
                            'hardware_pc0_rc0', 'hardware_pc2_rc0', 'hardware_pc3_rc0'):
                        double_rounding[label] = expected[0]
                    cached = tuple(int.from_bytes(cpu.mem_read(location, 4), 'little') for location in (0x503ea0, 0x503ea4, 0x503ea8))
                    live = cached + (int.from_bytes(cpu.mem_read(0x5054a1, 1), 'little'),
                                     int.from_bytes(cpu.mem_read(0x508798, 1), 'little'), cpu.reg_read(UC_X86_REG_FPCW))
                    replay = (U * 20)(*(outputs + [0] * (20 - len(outputs))))
                    for transport in (0, 1):
                        for mutation_style in (0, 1):
                            n.fixture_config(host, helper, multiply, divide, hardware, capability,
                                             control, replay, 1, mutation_style)
                            out, trace = (U * 13)(), (U * 22)()
                            n.fixture_run(host, target, a, b, ebx, ecx, transport, out, trace)
                            assert tuple(out[:2]) == expected[:2], (case, name, label, transport,
                                                                  mutation_style, tuple(out[:2]), expected[:2])
                            if not transport:
                                assert tuple(out[2:5]) == expected[1:]
                            assert tuple(out[5:8]) + tuple(out[10:13]) == live, (case, name, label, 'live state')
                            assert out[8] == 0 and out[9] == len(log), (case, name, label, 'availability')
                            assert [tuple(trace[i * 11:(i + 1) * 11]) for i in range(out[9])] == log, (case, name, label, 'boundary trace')
                    totals[name][label] += 1
        assert all(count == args.cases for modes in totals.values() for count in modes.values())
        assert exception_counts[0x4e7280] == sum(error_codes.values())
        assert exception_counts[0x4dae94] == error_codes[0x84]
        assert args.cases < len(EDGE) ** 2 or exception_counts[0x4dae94] > 0
        if args.cases > len(EDGE) ** 2:
            assert double_rounding == {'hardware_pc0_rc0': 0, 'hardware_pc2_rc0': 1, 'hardware_pc3_rc0': 1}
        guards = 0
        for target, name in ENTRIES:
            hardware_pointer = 0x4d8188 if name == 'multiply' else 0x4d8217 if name == 'divide' else 0x4d80b7
            software_pointer = 0x4d8198 if name == 'multiply' else 0x4d8227 if name == 'divide' else 0x4d80d5
            for selected, control, a, b in ((0xdeadbeef, 0x37f, 0x3f800000, 0x3f000000),
                                            (hardware_pointer, 0x37e, 0x3f800000, 0x3f000000),
                                            (hardware_pointer, 0x17f, 0x3f800000, 0x3f000000),
                                            (software_pointer, 0x37f, 0x7f7fffff if name == 'multiply' else 0x7f800000,
                                             0x7f7fffff if name == 'multiply' else 0 if name == 'divide' else 0xff800000 if name == 'subtract' else 0x7f800000)):
                helper, multiply, divide = caches(name, 'software_cached', selected, rng)
                for transport in (0, 1):
                    n.fixture_config(host, helper, multiply, divide, 0, 0, control, (U * 20)(), 0, 0)
                    out, trace = (U * 13)(), (U * 22)()
                    n.fixture_run(host, target, a, b, 3, 4, transport, out, trace)
                    assert tuple(out[:2]) == (a, b) and tuple(out[5:8]) == (helper, multiply, divide), (name, hex(selected), hex(control), transport, tuple(out), (a,b,helper,multiply,divide))
                    assert out[8] == 1 and out[9] == 0
                    guards += 1
        assert guards == 32
    finally:
        for hook in hooks:
            cpu.hook_del(hook)
        n.fixture_destroy(host)
    original_count = args.cases * sum(len(modes) for modes in MODES.values())
    report = {
        'status': 'passed', 'cases_per_entry_and_mode': args.cases,
        'complete_original_executions': totals, 'original_math_executions': original_count,
        'actual_host_and_lift_call_comparisons': original_count * 4,
        'software_error_calls_per_original_target': {hex(a): count for a, count in exception_counts.items()},
        'targeted_multiply_double_rounding': double_rounding,
        'software_error_codes': {hex(code): count for code, count in error_codes.items()},
        'unsupported_host_execution_guards': guards, 'initialized_host_control': '0x037f',
        'scope': 'Compile actual live source/lift_host.c and call public host.inner.calls, '
                 'then actual lift_call/call_glue EAX/EDX transport. Neither copies math branches. '
                 'Unrelated lifted dispatch is isolated; complete game callers are not claimed. '
                 'All four single entries execute actual software and masked hardware math. '
                 'Each route repeats with direct host-global and explicit callback-state mutations. '
                 'Direct host EAX/EDX/EBX/ECX and caller EAX/EDX, helper cache initialization and '
                 'live cache/hardware/capability/control snapshots compare. Divide covers both '
                 'hardware helper targets, lazy/cached selection, PC24/53/64 and all four RC modes. '
                 'Software overflow and zero-divisor callbacks mutate all register/global fields; '
                 'their changes remain live through subsequent calls and return. Callee internals '
                 'are delegated, not verified. Unmasked traps, FPSW/x87 stack/pending exceptions '
                 'remain outstanding. Host failures preserve inputs/caches and increment '
                 'rtl_single_failures. Double helper math and caller flags are outside this proof.'
    }
    (build / 'host-rtl-single-verification.json').write_text(json.dumps(report, indent=2) + '\n')
    print(json.dumps(report, indent=2))


if __name__ == '__main__':
    main()
