/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_0.h"

uint32_t lifted_f407020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F407020_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F407020_STACK, 1, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
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
    esi = eax;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    ebx = ecx;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x8u, 4), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4071f8;
    eax = 0x4u;
L_407041:
    edi = eax;
    eax = 0x9u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x0u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4071ff;
    eax = 0x5u;
L_40705e:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x4u, 4, eax);
    ecx = ecx ^ ecx;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_407090;
    edx = esi;
L_407070:
    lift_store(&env, edx, 0x8u, 4, 0xffffffffu);
    eax = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edx, 0x70u, 4, eax);
    edx = edx + 0xd0u;
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffecu, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_407070;
L_407090:
    edx = ebx;
    eax = ((ebx * 8u));
    eax = eax + ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    esi = esi + 0x8u;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    edx = edx ^ ebx;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
L_4070b2:
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4071da;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    edi = edi + lift_load(&env, ebp, 0xffffffdcu, 4);
L_4070c7:
    ecx = edi;
    eax = 0xcu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x4u, 4, eax);
    eax = 0x9u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x8u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x120u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4070f1;
    lift_store(&env, edi, 0x8u, 4, 0x120u);
L_4070f1:
    eax = 0x8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = 0x523698u;
    edx = edx - eax;
    eax = edx;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = edx + eax;
    lift_store(&env, ecx, 0x64u, 4, edx);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40711b;
    esi = (edx + 0x8u);
    lift_store(&env, ecx, 0x64u, 4, esi);
L_40711b:
    eax = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0xcu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ecx + 0xcu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_407209;
    eax = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x10u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x14u, 4, eax);
    eax = 0x5u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x18u, 4, eax);
    eax = 0x5u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x1cu, 4, eax);
    lift_store(&env, ecx, 0x20u, 4, 0x0u);
    edx = ecx;
    esi = ebx;
L_407172:
    eax = 0x3u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ecx, 0x64u, 4);
    eax = eax + ebx;
    lift_store(&env, edx, 0x58u, 4, eax);
    edx = edx + 0x4u;
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (!fl.zf)
        goto L_407172;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40719e;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb4d4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_40719e:
    lift_store(&env, ecx, 0x44u, 4, 0x12u);
    lift_store(&env, ecx, 0x48u, 4, 0x120u);
L_4071ac:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x4cu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x50u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x54u, 4, eax);
    edi = edi + 0xd0u;
    esi = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = esi + 1u;
    lift_store(&env, ebp, 0xfffffff4u, 4, esi);
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffecu, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4070c7;
L_4071da:
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = ecx + 0x68u;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0xd0u, &fl);
    }
    if (!fl.zf)
        goto L_4070b2;
    esp = (ebp + 0xfffffff8u);
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
L_4071f8:
    eax = eax ^ eax;
    goto L_407041;
L_4071ff:
    eax = 0x3u;
    goto L_40705e;
L_407209:
    edx = ecx;
    esi = 0x5u;
L_407210:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edx, 0x18u, 4, eax);
    edx = edx + 0x4u;
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_407210;
    eax = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x3u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (edx + edx);
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    ebx = ebx + esi;
    ebx = lift_load(&env, ebx, 0x4f5918u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        ebx = r;
    }
    lift_store(&env, ecx, 0x44u, 4, ebx);
    eax = eax + edx;
    eax = eax + eax;
    eax = eax + esi;
    eax = lift_load(&env, eax, 0x4f591au, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x48u, 4, eax);
    lift_store(&env, ecx, 0x10u, 4, 0x0u);
    lift_store(&env, ecx, 0x14u, 4, 0x0u);
    goto L_4071ac;
}

uint32_t lifted_f4193b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4193B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4193B0_STACK, 0, entry);
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
    esp = esp - 0x18u;
    eax = (ebp + 0xffffffd4u);
    edx = 0x4ec1ecu;
    ecx = 0x513fa0u;
    {
        uint32_t v = env.chain;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        lift_store(&env, eax, 0x0u, 4, v);
    }
    env.chain = eax;
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9ca6u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_419402;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    env.chain = eax;
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
L_419402:
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x50d7ecu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe8u);
    esi = 0x1u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
L_41941e:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4895e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_419441;
    edx = edx + eax;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x50d7f8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    goto L_41941e;
L_419441:
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, 0u, 0x558c7cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x473e60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486da0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = (ebp + 0xffffffe8u);
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    env.chain = eax;
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
