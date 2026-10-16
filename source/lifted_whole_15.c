/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_15.h"

uint32_t lifted_f42f910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F42F910_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F42F910_STACK, 0, entry);
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
    esp = esp - 0x20u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    esi = edx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xb8cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_42fb16;
    ecx = (ecx & 0xffffff00u) | ((0x10u) & 0xffu);
    edi = edi ^ edi;
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
L_42f935:
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = edi + lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
L_42f943:
    edi = lift_load(&env, ebp, 0xffffffd4u, 4);
    edi = edi + eax;
    edx = lift_load(&env, edi, 0x220u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_42f961;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), ((ebx >> 8) & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_42f95b;
    ebx = (ebx & 0xffff00ffu) | ((((ebx & 0xffu)) & 0xffu) << 8);
L_42f95b:
    {
        (void)lift_sub(8, (ebx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (!fl.cf)
        goto L_42f961;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_42f961:
    edi = lift_load(&env, ebp, 0xffffffd8u, 4);
    edi = edi + eax;
    edx = lift_load(&env, edi, 0x87cu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_42f97f;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), ((ebx >> 8) & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_42f979;
    ebx = (ebx & 0xffff00ffu) | ((((ebx & 0xffu)) & 0xffu) << 8);
L_42f979:
    {
        (void)lift_sub(8, (ebx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (!fl.cf)
        goto L_42f97f;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_42f97f:
    eax = eax + 0x4u;
    {
        (void)lift_sub(32, eax, 0x34u, &fl);
    }
    if (!fl.zf)
        goto L_42f943;
    edi = lift_load(&env, ebp, 0xffffffd0u, 4);
    edi = edi + eax;
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x104u, &fl);
    }
    if (!fl.zf)
        goto L_42f935;
    ebx = (ebx & 0xffffff00u) | (((ecx & 0xffu)) & 0xffu);
    {
        (void)lift_sub(8, (ecx & 0xffu), ((ebx >> 8) & 0xffu), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_42fa3f;
L_42f9a1:
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
L_42f9a6:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
L_42f9b1:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = eax + ecx;
    edx = lift_load(&env, eax, 0x220u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_42f9d2;
    eax = edx;
    {
        (void)lift_sub(8, (ebx & 0xffu), lift_load(&env, edx, 0x44u, 1), &fl);
    }
    if (!fl.zf)
        goto L_42f9d2;
    edi = lift_load(&env, eax, 0x158u, 4);
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42f9d2:
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, ecx, 0x34u, &fl);
    }
    if (!fl.zf)
        goto L_42f9b1;
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = ecx + 0x34u;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0x104u, &fl);
    }
    if (!fl.zf)
        goto L_42f9a6;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
L_42f9f0:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffe4u, 4);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_42f9fb:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax + ecx;
    edi = lift_load(&env, eax, 0x87cu, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_42fa1e;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, edi, 0x44u, 1)) & 0xffu) << 8);
    eax = edi;
    {
        (void)lift_sub(8, (ebx & 0xffu), ((edx >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_42fa1e;
    edi = lift_load(&env, edi, 0x158u, 4);
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42fa1e:
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, ecx, 0x34u, &fl);
    }
    if (!fl.zf)
        goto L_42f9fb;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = eax + ecx;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x104u, &fl);
    }
    if (!fl.zf)
        goto L_42f9f0;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) + 1u) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), ((ebx >> 8) & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_42f9a1;
L_42fa3f:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = 0x5u;
    ebx = esi;
    eax = eax + 0x988u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b2380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = 0xdu;
    ebx = esi;
    eax = eax + 0x9e8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b2380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = 0xdu;
    ebx = esi;
    eax = eax + 0xa2cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b2380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = 0x104u;
    ebx = esi;
    eax = eax + 0x324u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b2380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = lift_load(&env, eax, 0xa60u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_42faa9;
    eax = ecx;
    ecx = lift_load(&env, ecx, 0x158u, 4);
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42faa9:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = lift_load(&env, eax, 0xb70u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_42fac3;
    ecx = lift_load(&env, ebx, 0x158u, 4);
    eax = ebx;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42fac3:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = lift_load(&env, eax, 0xb78u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_42fadd;
    ecx = lift_load(&env, edi, 0x158u, 4);
    eax = edi;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42fadd:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = 0x41u;
    ebx = esi;
    eax = eax + 0xbdcu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b2380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = esi;
    eax = eax + 0xcecu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = lift_load(&env, eax, 0xce0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_42fb40;
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
    return env.failed ? 0u : eax;
L_42fb16:
    edx = 0x41u;
    eax = eax + 0x220u;
    ebx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b2380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = 0x41u;
    ebx = esi;
    eax = eax + 0x87cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b2380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_42fa3f;
L_42fb40:
    ecx = lift_load(&env, edx, 0x158u, 4);
    eax = edx;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    return env.failed ? 0u : eax;
}
