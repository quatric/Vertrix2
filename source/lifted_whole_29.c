/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_29.h"

uint32_t lifted_f43e320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F43E320_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F43E320_STACK, 0, entry);
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
    edi = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    lift_store(&env, 0u, 0x540fe8u, 2, (eax & 0xffffu));
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((ecx & 0xffffu)) & 0xffffu);
    lift_store(&env, 0u, 0x540fecu, 2, (eax & 0xffffu));
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x540feau, 2, (ecx & 0xffffu));
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x540feeu, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x540fdcu, 4, edx);
L_43e371:
    eax = lift_load(&env, 0u, 0x540fdcu, 4);
    eax = lift_load(&env, edi, (eax * 4u) + 0x15cu, 4);
    lift_store(&env, 0u, 0x540fe4u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_43e3be;
L_43e386:
    eax = lift_load(&env, 0u, 0x540fdcu, 4);
    eax = eax + 1u;
    lift_store(&env, 0u, 0x540fdcu, 4, eax);
    {
        (void)lift_sub(32, eax, 0x1c2u, &fl);
    }
    if (fl.cf)
        goto L_43e371;
    edx = 0x1u;
    eax = (edi + 0x870u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b23c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3u;
    eax = (edi + 0x864u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b23c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_43e3be:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x540fe4u, 4);
    ecx = 0x3ff00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac560u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    esi = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb57cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf != fl.of)
        goto L_43e409;
    eax = lift_load(&env, 0u, 0x540fe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = esi;
    eax = lift_load(&env, 0u, 0x540fe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad720u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_43e409;
    edx = lift_load(&env, 0u, 0x540fe4u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43e740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43e409:
    ecx = lift_load(&env, 0u, 0x540fe4u, 4);
    edx = 0xc8u;
    eax = lift_load(&env, ecx, 0x58u, 4);
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x540ff8u, 4, edx);
    if (fl.zf)
        goto L_43e4b1;
    edx = lift_load(&env, ecx, 0x6u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    esi = lift_load(&env, 0u, 0x540ff8u, 4);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, esi, &eax, &edx, &fl);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x540fecu, 2)) & 0xffffu);
    eax = eax + edx;
    edx = lift_load(&env, ecx, 0x8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, esi, &eax, &edx, &fl);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x540feeu, 2)) & 0xffffu);
    eax = eax + edx;
    edx = esi;
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edx = r;
    }
    esi = 0xc8u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, esi, &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    eax = (edx + 0xffffffffu);
    lift_store(&env, 0u, 0x541004u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_43e490;
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    goto L_43e386;
L_43e490:
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x540fe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x540fe4u, 4);
    lift_store(&env, eax, 0x44u, 1, 0x10u);
    goto L_43e386;
L_43e4b1:
    lift_store(&env, ecx, 0xeu, 2, 0x0u);
    lift_store(&env, ecx, 0x16u, 2, 0x0u);
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    goto L_43e386;
}
