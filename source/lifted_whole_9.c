/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_9.h"

uint32_t lifted_f4ec68c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC68C_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC68C_STACK, 0, entry);
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
    edi = edx;
    ebp = ecx;
    eax = (ebx + 0xbu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xf8u) & 0xffu);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.cf)
        goto L_4ec6aa;
    eax = 0xffffffffu;
    goto L_4ec6b4;
L_4ec6aa:
    {
        (void)lift_sub(32, eax, 0x10u, &fl);
    }
    if (!fl.cf)
        goto L_4ec6b4;
    eax = 0x10u;
L_4ec6b4:
    edx = (edi + 0xfffffffcu);
    lift_store(&env, esp, 0x0u, 4, edx);
    edx = lift_load(&env, edx, 0x0u, 4);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xfeu) & 0xffu);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ec7d2;
    ecx = lift_load(&env, esp, 0x0u, 4);
    eax = eax - edx;
    ecx = ecx + edx;
L_4ec6ce:
    lift_store(&env, ebp, 0x0u, 4, eax);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ec6e2;
    ebx = 0x2u;
    goto L_4ec82f;
L_4ec6e2:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4ec7c4;
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = lift_load(&env, ecx, 0x4u, 4);
    edx = 0u;
    lift_store(&env, esp, 0x4u, 4, eax);
    eax = 0x50aefcu;
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, esp, 0xcu, 2), &fl);
    }
    if (!fl.zf)
        goto L_4ec728;
    esi = lift_load(&env, 0u, 0x50aefcu, 4);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ec728;
L_4ec713:
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ec71f;
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax + esi;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ec728;
L_4ec71f:
    esi = lift_load(&env, esi, 0x8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ec713;
L_4ec728:
    edx = lift_load(&env, esi, 0xcu, 4);
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4ec735;
    eax = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, esi, 0xcu, 4, eax);
L_4ec735:
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0x0u, 4), &fl);
    }
    if (fl.cf)
        goto L_4ec746;
    eax = ebx;
    edx = lift_load(&env, ebp, 0x0u, 4);
    eax = eax - edx;
    {
        (void)lift_sub(32, eax, 0x10u, &fl);
    }
    if (!fl.cf)
        goto L_4ec77a;
L_4ec746:
    eax = lift_load(&env, esp, 0x4u, 4);
    edx = lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, eax, 0x8u, 4, edx);
    eax = edx;
    edx = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x4u, 4, edx);
    eax = lift_load(&env, esp, 0x0u, 4);
    lift_store(&env, eax, 0x0u, 4, lift_load(&env, eax, 0x0u, 4) + ebx);
    eax = lift_load(&env, esi, 0x1cu, 4);
    eax = eax - 1u;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    lift_store(&env, esi, 0x1cu, 4, eax);
    lift_store(&env, 0u, 0x5c8ac1u, 1, (edx & 0xffu));
    edx = lift_load(&env, ebp, 0x0u, 4);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.cf)
        goto L_4ec7b9;
    goto L_4ec82d;
L_4ec77a:
    ecx = ecx + edx;
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, ecx, 0x8u, 4, eax);
    eax = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x8u, 4, ecx);
    eax = lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, eax, 0x4u, 4, ecx);
    edx = lift_load(&env, esp, 0x0u, 4);
    eax = lift_load(&env, ebp, 0x0u, 4);
    ecx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx ^ ebx;
    ecx = ecx + eax;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, edx, 0x0u, 4, ecx);
    lift_store(&env, 0u, 0x5c8ac1u, 1, ((eax >> 8) & 0xffu));
    eax = ebx;
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
L_4ec7b9:
    eax = edx;
    eax = eax - ebx;
    ecx = ecx + ebx;
    goto L_4ec6ce;
L_4ec7c4:
    ebx = 0x1u;
    eax = ebx;
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
L_4ec7d2:
    edx = edx - eax;
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.cf)
        goto L_4ec82d;
    ebx = eax;
    ecx = lift_load(&env, esp, 0x0u, 4);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | 0x1u) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) | 0x1u) & 0xffu);
    lift_store(&env, ecx, 0x0u, 4, ebx);
    ebx = (ecx + eax);
    eax = 0x50aefcu;
    lift_store(&env, esp, 0x0u, 4, ebx);
    lift_store(&env, ebx, 0x0u, 4, edx);
    edx = 0u;
    ebx = lift_load(&env, esp, 0xcu, 4);
    {
        (void)lift_sub(16, (edx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4ec81f;
    esi = lift_load(&env, 0u, 0x50aefcu, 4);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ec81f;
L_4ec80a:
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ec816;
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax + esi;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ec81f;
L_4ec816:
    esi = lift_load(&env, esi, 0x8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ec80a;
L_4ec81f:
    lift_store(&env, esi, 0x18u, 4, lift_load(&env, esi, 0x18u, 4) + 1u);
    eax = lift_load(&env, esp, 0x0u, 4);
    eax = eax + 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ec82d:
    ebx = ebx ^ ebx;
L_4ec82f:
    eax = ebx;
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
