/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_33.h"

uint32_t lifted_f40b0a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F40B0A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F40B0A0_STACK, 0, entry);
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
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    eax = eax + 0x2u;
    ebx = 0x1eu;
    edx = 0x50c7fcu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x0u, 2, 0x104u);
    lift_store(&env, ecx, 0x20u, 4, 0xfffu);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f40b0d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F40B0D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F40B0D0_STACK, 0, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x4u;
    ebx = ebx ^ ebx;
    edx = (ebp + 0xfffffff4u);
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40b040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_40b0f4;
    eax = 0x5u;
    esp = (ebp + 0xfffffff8u);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_40b0f4:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40b080u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    esp = (ebp + 0xfffffff8u);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
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

uint32_t lifted_f40b110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F40B110_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F40B110_STACK, 0, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
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
    {
        uint32_t v = edx;
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
    esp = esp - 0x9cu;
    esi = eax;
    ebx = 0x1cu;
    edx = edx ^ edx;
    eax = 0x52f150u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    edx = 0x52f150u;
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40b040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_40b152;
    eax = 0x5u;
    esp = (ebp + 0xffffffecu);
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
        edx = v;
    }
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_40b152:
    eax = lift_load(&env, 0u, 0x52f150u, 4);
    ebx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1994u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x52f150u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x18u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_40b28f;
    lift_store(&env, ebp, 0xffffff50u, 4, 0x60u);
    eax = lift_load(&env, 0u, 0x52f150u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = (ebp + 0xffffff50u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x10u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_40b28f;
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xffffff54u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_40b1a6;
    lift_store(&env, esi, 0x5u, 1, lift_load(&env, esi, 0x5u, 1) & 0xfeu);
L_40b1a6:
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xffffff55u, 1), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_40b1b3;
    lift_store(&env, esi, 0x4u, 1, lift_load(&env, esi, 0x4u, 1) & 0xfeu);
L_40b1b3:
    lift_store(&env, ebp, 0xffffffd8u, 2, 0x1u);
    {
        (void)lift_and(8, lift_load(&env, esi, 0x5u, 1), 0x1u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffdau, 2, (eax & 0xffffu));
    {
        (void)lift_and(8, lift_load(&env, esi, 0x4u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_40b2a8;
    eax = 0x10u;
L_40b1d9:
    lift_store(&env, ebp, 0xffffffe6u, 2, (eax & 0xffffu));
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x6u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x6u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 2, 0x1u);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffe8u, 2, (ecx & 0xffffu));
    {
        (void)lift_and(8, lift_load(&env, esi, 0x5u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_40b20d;
    ebx = (eax + eax);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe4u, 2, 0x2u);
L_40b20d:
    {
        (void)lift_and(8, lift_load(&env, esi, 0x4u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_40b224;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    edi = edi + edi;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = eax + eax;
    lift_store(&env, ebp, 0xffffffe4u, 2, (eax & 0xffffu));
L_40b224:
    ebx = 0x14u;
    edx = edx ^ edx;
    eax = (ebp + 0xffffffb0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb0u, 4, 0x14u);
    lift_store(&env, ebp, 0xffffffb4u, 4, 0x1u);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffb8u, 4, ecx);
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    eax = lift_load(&env, 0u, 0x52f150u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x52f154u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffffb0u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0xcu, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_40b28f;
L_40b264:
    eax = lift_load(&env, 0u, 0x52f154u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = (ebp + 0xffffffd8u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x38u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_40b2d6;
    {
        (void)lift_sub(16, lift_load(&env, esi, 0x6u, 2), 0x2b11u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_40b2b2;
    {
        uint32_t a = lift_load(&env, ebp, 0xffffffdcu, 4);
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        lift_store(&env, ebp, 0xffffffdcu, 4, r);
    }
    {
        uint32_t a = lift_load(&env, ebp, 0xffffffe0u, 4);
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        lift_store(&env, ebp, 0xffffffe0u, 4, r);
    }
    {
        uint32_t a = lift_load(&env, ebp, 0xffffffe4u, 2);
        uint32_t r = lift_shr(16, a, 0x1u, &fl);
        lift_store(&env, ebp, 0xffffffe4u, 2, r);
    }
    {
        uint32_t a = lift_load(&env, esi, 0x6u, 2);
        uint32_t r = lift_shr(16, a, 0x1u, &fl);
        lift_store(&env, esi, 0x6u, 2, r);
    }
    goto L_40b264;
L_40b28f:
    eax = lift_load(&env, 0u, 0x52f150u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40b080u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5u;
    esp = (ebp + 0xffffffecu);
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
        edx = v;
    }
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_40b2a8:
    eax = 0x8u;
    goto L_40b1d9;
L_40b2b2:
    eax = lift_load(&env, 0u, 0x52f154u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, 0u, 0x52f150u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40b080u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5u;
    esp = (ebp + 0xffffffecu);
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
        edx = v;
    }
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_40b2d6:
    lift_store(&env, ebp, 0xffffffc4u, 4, 0x14u);
    eax = lift_load(&env, 0u, 0x52f154u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    ecx = (ebp + 0xffffffc4u);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_40b2b2;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = ((edx * 4u));
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax + edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = 0x3e8u;
    edx = edx ^ edx;
    lift_div1(32, ecx, &eax, &edx, &fl);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffccu, 4), &fl);
    }
    if (!fl.cf)
        goto L_40b315;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
L_40b315:
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = ((edx * 4u));
    eax = eax + edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = 0x3e8u;
    edx = edx ^ edx;
    lift_div1(32, ecx, &eax, &edx, &fl);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffccu, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_40b335;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
L_40b335:
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xffffff54u, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_40b364;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = ((edx * 4u));
    eax = eax + edx;
    eax = eax + eax;
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax - edx;
    ecx = 0x3e8u;
    edx = edx ^ edx;
    lift_div1(32, ecx, &eax, &edx, &fl);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffccu, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_40b364;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
L_40b364:
    edi = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, edi);
    eax = ((edi * 4u));
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    ebx = 0x14u;
    edx = edx ^ edx;
    eax = (ebp + 0xffffffb0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb0u, 4, 0x14u);
    lift_store(&env, ebp, 0xffffffb4u, 4, 0x14000u);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    eax = (ebp + 0xffffffd8u);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = lift_load(&env, 0u, 0x52f150u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x52f158u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffffb0u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0xcu, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_40b3d3;
    eax = lift_load(&env, 0u, 0x52f150u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40b080u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5u;
    esp = (ebp + 0xffffffecu);
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
        edx = v;
    }
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_40b3d3:
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x52f160u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    lift_store(&env, 0u, 0x52f164u, 4, eax);
    eax = lift_load(&env, 0u, 0x52f154u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x30u, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    eax = lift_load(&env, 0u, 0x52f158u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x30u, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x52f168u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x52f16au, 2, (eax & 0xffffu));
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    esp = (ebp + 0xffffffecu);
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
        edx = v;
    }
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f40b490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F40B490_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F40B490_STACK, 0, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
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
    {
        uint32_t v = edx;
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
    esp = esp - 0x1cu;
    ebx = eax;
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x52f16bu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_40b4a8;
    ebx = ebx + ebx;
L_40b4a8:
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x52f16au, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_40b4b3;
    ebx = ebx + ebx;
L_40b4b3:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_40b4bf;
    {
        (void)lift_sub(32, ebx, lift_load(&env, 0u, 0x52f164u, 4), &fl);
    }
    if (fl.cf)
        goto L_40b4c5;
L_40b4bf:
    ebx = lift_load(&env, 0u, 0x52f164u, 4);
L_40b4c5:
    eax = lift_load(&env, 0u, 0x52f158u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = (ebp + 0xffffffe4u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffffe0u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x10u, 4), eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_40b507;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = lift_load(&env, 0u, 0x52f160u, 4);
    eax = eax - ecx;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40b513;
L_40b4ee:
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0xffffffe8u, 4), &fl);
    }
    if (fl.cf)
        goto L_40b51d;
L_40b4f3:
    lift_store(&env, ebp, 0xffffffe8u, 1, lift_load(&env, ebp, 0xffffffe8u, 1) & 0xfcu);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = edx - 0x80u;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_40b522;
L_40b507:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    esp = (ebp + 0xffffffecu);
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
        edx = v;
    }
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_40b513:
    eax = lift_load(&env, 0u, 0x52f164u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, lift_load(&env, ebp, 0xffffffe8u, 4) + eax);
    goto L_40b4ee;
L_40b51d:
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    goto L_40b4f3;
L_40b522:
    eax = lift_load(&env, 0u, 0x52f158u, 4);
    ebx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffffdcu);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffffd4u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffffd8u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffffd0u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, 0u, 0x52f160u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x2cu, 4), eax, edx, ebx, ecx, 8, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 32u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_40b5eb;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x52f15cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40b5cb;
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40b57b;
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_40b57b:
    eax = lift_load(&env, 0u, 0x52f158u, 4);
    ebx = lift_load(&env, eax, 0x0u, 4);
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4cu, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = lift_load(&env, 0u, 0x52f160u, 4);
    ebx = ebx + eax;
    lift_store(&env, 0u, 0x52f160u, 4, ebx);
    esi = lift_load(&env, 0u, 0x52f164u, 4);
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.cf)
        goto L_40b507;
    edi = ebx;
    edi = edi - esi;
    lift_store(&env, 0u, 0x52f160u, 4, edi);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    esp = (ebp + 0xffffffecu);
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
        edx = v;
    }
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_40b5cb:
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x52f15cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_40b57b;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x52f15cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_40b57b;
L_40b5eb:
    eax = lift_load(&env, 0u, 0x52f158u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x50u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    esp = (ebp + 0xffffffecu);
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
        edx = v;
    }
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f40ccf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F40CCF0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F40CCF0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x52fc18u, 4), &fl);
    }
    if (!fl.cf)
        goto L_40cd21;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_40cd04;
    eax = 0x2u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_40cd04:
    ecx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax - ecx;
    {
        (void)lift_and(8, lift_load(&env, 0u, (eax * 8u) + 0x52f92eu, 1), 0x1u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, edx, 0x0u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_40cd21:
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f48b2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    static uint8_t stack[LIFTED_F48B2F0_STACK + 4 + 4 * 0 + 4];
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
    static int active;
    if (active)
    {
        lift_reentered(0x48b2f0);
    }
    active = 1;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48B2F0_STACK, 0, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
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
    esp = esp - 0x6788u;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    edx = edx ^ edx;
    eax = 0x1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    edx = 0x61a80u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = (ebp + 0xffff9868u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x405d60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffdcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x2000u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aa70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aa80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = (ebp + 0xffffdfd8u);
    edx = eax;
    eax = (ebp + 0xffff9868u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x405f70u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ebx = eax;
    ecx = eax;
    eax = (ebp + 0xffff987cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_48b3c0;
L_48b366:
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    esi = (ebp + 0xffffdfd8u);
    edi = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = ecx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    lift_string(&env, 0, 4, 3, &eax, &ecx, &esi, &edi, &fl);
    ecx = (ecx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_and(8, (ecx & 0xffu), 0x3u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_string(&env, 0, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = edx ^ edx;
    ecx = (edi + eax);
    ebx = ebx + eax;
    eax = (ebp + 0xffffffdcu);
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    ecx = (ebp + 0xffffdfd8u);
    {
        uint32_t v = 0x2000u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    eax = (ebp + 0xffff9868u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x405f70u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48b366;
L_48b3c0:
    {
        (void)lift_sub(32, ecx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_48b488;
    edx = 0x18u;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48b488;
    lift_store(&env, eax, 0x16u, 2, 0x1u);
    eax = lift_load(&env, ebp, 0xffff98a0u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, (eax * 4u) + 0x4f41acu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xcu, 4, 0x0u);
    lift_store(&env, ecx, 0x14u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ecx, 0x8u, 4, eax);
    eax = ecx;
    lift_store(&env, ecx, 0x10u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ac50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48b434;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x0u, 4, 0x0u);
L_48b434:
    edi = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = lift_load(&env, edi, 0x0u, 4);
    edx = edx ^ edx;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = ecx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    lift_string(&env, 0, 4, 3, &eax, &ecx, &esi, &edi, &fl);
    ecx = (ecx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_and(8, (ecx & 0xffu), 0x3u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_string(&env, 0, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40acd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, eax, 0x0u, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x598dacu, 4);
    eax = lift_load(&env, ecx, 0x8u, 4);
    esi = esi + eax;
    lift_store(&env, 0u, 0x598dacu, 4, esi);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    esp = (ebp + 0xfffffff0u);
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
        ecx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    active = 0;
    return env.failed ? 0u : eax;
L_48b488:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0xbu;
    esp = (ebp + 0xfffffff0u);
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
        ecx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    active = 0;
    return env.failed ? 0u : eax;
}
