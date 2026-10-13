/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_35.h"

uint32_t lifted_f410f20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F410F20_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F410F20_STACK, 0, entry);
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
    esp = esp - 0x34u;
    esi = eax;
    {
        uint32_t v = 0x34u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffbcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f173cu, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_410f65;
L_410f3f:
    eax = (esi + 0x2u);
    ebx = 0x1eu;
    edx = (ebp + 0xffffffc4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x0u, 2, 0x100u);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, esi, 0x20u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    esp = (ebp + 0xfffffff0u);
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
L_410f65:
    ebx = 0x20u;
    edx = 0x50c814u;
    eax = (ebp + 0xffffffc4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    goto L_410f3f;
}

uint32_t lifted_f410fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F410FA0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F410FA0_STACK, 0, entry);
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
    esp = esp - 0x44u;
    esi = eax;
    ebx = 0x78u;
    edx = edx ^ edx;
    eax = 0x532500u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x34u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffa8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f173cu, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_410ffd;
    {
        (void)lift_and(16, lift_load(&env, ebp, 0xffffffd0u, 2), 0xaaau, &fl);
    }
    if (!fl.zf)
        goto L_410fdd;
    lift_store(&env, esi, 0x5u, 1, lift_load(&env, esi, 0x5u, 1) & 0xfeu);
L_410fdd:
    {
        (void)lift_and(16, lift_load(&env, ebp, 0xffffffd0u, 2), 0xcccu, &fl);
    }
    if (!fl.zf)
        goto L_410fe9;
    lift_store(&env, esi, 0x4u, 1, lift_load(&env, esi, 0x4u, 1) & 0xfeu);
L_410fe9:
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xffffffd1u, 1), 0xfu, &fl);
    }
    if (!fl.zf)
        goto L_410ffd;
    {
        (void)lift_sub(16, lift_load(&env, esi, 0x6u, 2), 0x5622u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_410ffd;
    lift_store(&env, esi, 0x6u, 2, 0x5622u);
L_410ffd:
    lift_store(&env, ebp, 0xffffffdcu, 2, 0x1u);
    {
        (void)lift_and(8, lift_load(&env, esi, 0x5u, 1), 0x1u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffdeu, 2, (eax & 0xffffu));
    {
        (void)lift_and(8, lift_load(&env, esi, 0x4u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41110d;
    eax = 0x10u;
L_411023:
    lift_store(&env, ebp, 0xffffffeau, 2, (eax & 0xffffu));
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x6u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x6u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 2, 0x1u);
    {
        (void)lift_and(8, lift_load(&env, esi, 0x5u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_411053;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = edx + edx;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    lift_store(&env, ebp, 0xffffffe8u, 2, 0x2u);
L_411053:
    {
        (void)lift_and(8, lift_load(&env, esi, 0x4u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41106a;
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ecx = ecx + ecx;
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx + ebx;
    lift_store(&env, ebp, 0xffffffe8u, 2, (ebx & 0xffffu));
L_41106a:
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
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffdcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x532500u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1744u, eax, edx, ebx, ecx, 6, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 24u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_411117;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x6u, 2)) & 0xffffu);
    ebx = 0x14u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    edi = eax;
    {
        (void)lift_and(8, lift_load(&env, esi, 0x4u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4110a6;
    edi = edi + edi;
L_4110a6:
    {
        (void)lift_and(8, lift_load(&env, esi, 0x5u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_41111e;
L_4110ac:
    edi = edi + 0xfu;
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) & 0xfff0u) & 0xffffu);
    ebx = ebx ^ ebx;
    esi = esi ^ esi;
L_4110b7:
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x2002u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c0cu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    lift_store(&env, esi, 0x532504u, 4, eax);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c24u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, ebx, 0x532510u, 4, eax);
    lift_store(&env, ebx, 0x532514u, 4, edi);
    lift_store(&env, ebx, 0x532520u, 4, 0x1u);
    ecx = ecx ^ ecx;
    lift_store(&env, ebx, 0x532524u, 4, ecx);
    lift_store(&env, ebx, 0x53251cu, 4, ecx);
    ebx = ebx + 0x20u;
    esi = esi + 0x4u;
    {
        (void)lift_sub(32, esi, 0xcu, &fl);
    }
    if (!fl.zf)
        goto L_4110b7;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_411103:
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
L_41110d:
    eax = 0x8u;
    goto L_411023;
L_411117:
    eax = 0x5u;
    goto L_411103;
L_41111e:
    edi = edi + edi;
    goto L_4110ac;
}
