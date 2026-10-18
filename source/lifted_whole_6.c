/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_6.h"

uint32_t lifted_rtl_segment_dispatch(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_SEGMENT_DISPATCH_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_SEGMENT_DISPATCH_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    ecx = edx;
    edx = 0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dee8e;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb4d4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4dee8e:
    edx = ecx;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6250u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e628c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E628C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E628C_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    ecx = edx;
    edx = 0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e62a6;
    edx = ecx;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6250u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e62a6:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e6c98(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6C98_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6C98_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e37feu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x8u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e6cca;
    edx = (edx & 0xffu);
    {
        uint32_t i = edx;
        switch (i)
        {
            case 0:
                goto L_4e6cb0;
            case 1:
                goto L_4e6cc0;
            case 2:
                goto L_4e6cca;
            case 3:
                goto L_4e6cb8;
            case 4:
                goto L_4e6cb0;
            case 5:
                goto L_4e6cca;
            case 6:
                goto L_4e6cc0;
            case 7:
                goto L_4e6cc0;
            case 8:
                goto L_4e6cb8;
            default:
                return 0u;
        }
    }
L_4e6cb0:
    ecx = lift_load(&env, eax, 0x10u, 4);
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e6cb8:
    ecx = lift_load(&env, eax, 0x4u, 4);
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e6cc0:
    ecx = 0x4u;
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e6cca:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e88bf(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E88BF_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E88BF_STACK, 0, entry);
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4e88dd;
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    if (fl.zf)
        goto L_4e88dc;
    ebx = ebx + 1u;
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e88d4;
    ecx = eax;
    eax = edx;
    edx = edx - edx;
    lift_div1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t t = ecx;
        ecx = eax;
        eax = t;
    }
L_4e88d4:
    lift_div1(32, ebx, &eax, &edx, &fl);
    ebx = edx;
    edx = ecx;
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
L_4e88dc:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e88dd:
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (fl.cf)
        goto L_4e88fd;
    if (!fl.zf)
        goto L_4e88f5;
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e88f5;
    eax = eax - ebx;
    ebx = eax;
    ecx = ecx - ecx;
    {
        uint32_t r = lift_sub(32, edx, edx, &fl);
        edx = r;
    }
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e88f5:
    ecx = ecx - ecx;
    {
        uint32_t r = lift_sub(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t t = ebx;
        ebx = eax;
        eax = t;
    }
    {
        uint32_t t = edx;
        edx = ecx;
        ecx = t;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e88fd:
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = esi - esi;
    edi = esi;
    ebp = esi;
L_4e8906:
    {
        uint32_t r = lift_add(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_adc(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (fl.cf)
        goto L_4e891f;
    ebp = ebp + 1u;
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (fl.cf)
        goto L_4e8906;
    if (!fl.cf && !fl.zf)
        goto L_4e8917;
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e8906;
L_4e8917:
    fl.cf = 0;
L_4e8918:
    {
        uint32_t r = lift_adc(32, esi, esi, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_adc(32, edi, edi, &fl);
        edi = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebp = r;
    }
    if (fl.sf)
        goto L_4e8941;
L_4e891f:
    {
        uint32_t a = ecx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_sub(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sbb(32, edx, ecx, &fl);
        edx = r;
    }
    fl.cf = !fl.cf;
    if (fl.cf)
        goto L_4e8918;
L_4e892a:
    {
        uint32_t r = lift_add(32, esi, esi, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_adc(32, edi, edi, &fl);
        edi = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebp = r;
    }
    if (fl.sf)
        goto L_4e893d;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, ecx, &fl);
        edx = r;
    }
    if (!fl.cf)
        goto L_4e892a;
    goto L_4e8918;
L_4e893d:
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, ecx, &fl);
        edx = r;
    }
L_4e8941:
    ebx = eax;
    ecx = edx;
    eax = esi;
    edx = edi;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA540_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA540_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x10u;
    lift_store(&env, esp, 0xcu, 4, eax);
    lift_store(&env, esp, 0x4u, 4, edx);
    esi = ebx;
    lift_store(&env, esp, 0x8u, 4, ecx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4ea55a;
    lift_store(&env, edx, 0x0u, 4, eax);
L_4ea55a:
    edx = lift_load(&env, esp, 0xcu, 4);
L_4ea55e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) + 1u) & 0xffu);
    eax = eax & 0xffu;
    {
        (void)lift_and(8, lift_load(&env, eax, 0x507d58u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ea573;
    edx = edx + 1u;
    goto L_4ea55e;
L_4ea573:
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, edx, 0x0u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2bu, &fl);
    }
    if (fl.zf)
        goto L_4ea57f;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ea580;
L_4ea57f:
    edx = edx + 1u;
L_4ea580:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4ea5b0;
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4ea59d;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x1u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4ea596;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x58u, &fl);
    }
    if (!fl.zf)
        goto L_4ea59d;
L_4ea596:
    esi = 0x10u;
    goto L_4ea5d0;
L_4ea59d:
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4ea5a9;
    esi = 0x8u;
    goto L_4ea5e5;
L_4ea5a9:
    esi = 0xau;
    goto L_4ea5e5;
L_4ea5b0:
    {
        (void)lift_sub(32, esi, 0x2u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ea5ba;
    {
        (void)lift_sub(32, esi, 0x24u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ea5cb;
L_4ea5ba:
    eax = 0xdu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    goto L_4ea68c;
L_4ea5cb:
    {
        (void)lift_sub(32, esi, 0x10u, &fl);
    }
    if (!fl.zf)
        goto L_4ea5e5;
L_4ea5d0:
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4ea5e5;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, edx, 0x1u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4ea5e2;
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), 0x58u, &fl);
    }
    if (!fl.zf)
        goto L_4ea5e5;
L_4ea5e2:
    edx = edx + 0x2u;
L_4ea5e5:
    lift_store(&env, esp, 0x0u, 4, edx);
    ebp = ((esi * 4u));
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) ^ (ecx & 0xffu)) & 0xffu);
    ebx = ebx ^ ebx;
L_4ea5f3:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea6b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ea61c;
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0x50b214u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ea60c;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
L_4ea60c:
    eax = ebx;
    {
        uint32_t r = lift_imul(32, ebx, esi, &fl);
        ebx = r;
    }
    ebx = ebx + edi;
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (!fl.cf)
        goto L_4ea619;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
L_4ea619:
    edx = edx + 1u;
    goto L_4ea5f3;
L_4ea61c:
    {
        (void)lift_sub(32, edx, lift_load(&env, esp, 0x0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4ea625;
    edx = lift_load(&env, esp, 0xcu, 4);
L_4ea625:
    edi = lift_load(&env, esp, 0x4u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4ea62f;
    lift_store(&env, edi, 0x0u, 4, edx);
L_4ea62f:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4ea645;
    {
        (void)lift_sub(32, ebx, 0x80000000u, &fl);
    }
    if (fl.cf)
        goto L_4ea645;
    if (!fl.zf)
        goto L_4ea649;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ea649;
L_4ea645:
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4ea683;
L_4ea649:
    eax = 0xeu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ea666;
    eax = 0xffffffffu;
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ea666:
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ea677;
    eax = 0x80000000u;
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ea677:
    eax = 0x7fffffffu;
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ea683:
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ea68a;
    ebx = 0u - ebx;
L_4ea68a:
    eax = ebx;
L_4ea68c:
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}
