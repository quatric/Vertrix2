/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_34.h"

uint32_t lifted_f40b6e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F40B6E0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F40B6E0_STACK, 0, entry);
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
    esp = esp - 0x88u;
    esi = eax;
    ebx = 0x79cu;
    edx = edx ^ edx;
    eax = 0x52f170u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_40b714;
    eax = 0x2u;
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
L_40b714:
    ebx = ebx ^ ebx;
    edx = 0x52f170u;
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40b620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_40b735;
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
L_40b735:
    eax = lift_load(&env, 0u, 0x52f170u, 4);
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
    edx = lift_load(&env, 0u, 0x52f170u, 4);
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
        goto L_40b876;
    lift_store(&env, ebp, 0xffffff64u, 4, 0x60u);
    eax = lift_load(&env, 0u, 0x52f170u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    ecx = (ebp + 0xffffff64u);
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
    eax = lift_call(&env, lift_load(&env, edx, 0x10u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_40b876;
    lift_store(&env, esi, 0x6u, 2, 0xac44u);
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xffffff68u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_40b78f;
    lift_store(&env, esi, 0x5u, 1, lift_load(&env, esi, 0x5u, 1) & 0xfeu);
L_40b78f:
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xffffff68u, 1), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_40b79c;
    lift_store(&env, esi, 0x4u, 1, lift_load(&env, esi, 0x4u, 1) & 0xfeu);
L_40b79c:
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
        goto L_40b88f;
    eax = 0x10u;
L_40b7c2:
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
        goto L_40b7f6;
    ebx = (eax + eax);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe4u, 2, 0x2u);
L_40b7f6:
    {
        (void)lift_and(8, lift_load(&env, esi, 0x4u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_40b80d;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    edi = edi + edi;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = eax + eax;
    lift_store(&env, ebp, 0xffffffe4u, 2, (eax & 0xffffu));
L_40b80d:
    ebx = 0x14u;
    edx = edx ^ edx;
    eax = (ebp + 0xffffffc4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc4u, 4, 0x14u);
    lift_store(&env, ebp, 0xffffffc8u, 4, 0x1u);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    eax = lift_load(&env, 0u, 0x52f170u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x52f174u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_40b876;
L_40b84b:
    eax = lift_load(&env, 0u, 0x52f174u, 4);
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
        goto L_40b899;
    {
        (void)lift_sub(16, lift_load(&env, esi, 0x6u, 2), 0x2b11u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_40b876;
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
    goto L_40b84b;
L_40b876:
    eax = lift_load(&env, 0u, 0x52f170u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40b660u, eax, edx, ebx, ecx, 0, esp);
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
L_40b88f:
    eax = 0x8u;
    goto L_40b7c2;
L_40b899:
    eax = lift_load(&env, 0u, 0x52f174u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x52f900u, 4, eax);
    esi = esi ^ esi;
    lift_store(&env, 0u, 0x52f904u, 4, esi);
    edx = 0x60u;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ba00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    esi = 0xfffc1800u;
L_40b8d4:
    edx = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x7u, &fl);
        edx = r;
    }
    lift_store(&env, eax, 0x52f300u, 4, edx);
    eax = eax + 0x4u;
    esi = esi + 0x7d0u;
    {
        (void)lift_sub(32, eax, 0x400u, &fl);
    }
    if (!fl.zf)
        goto L_40b8d4;
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
