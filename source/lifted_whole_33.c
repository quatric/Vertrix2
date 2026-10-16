/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_33.h"

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
