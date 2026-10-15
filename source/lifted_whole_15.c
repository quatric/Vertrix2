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

uint32_t lifted_f42fb60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F42FB60_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F42FB60_STACK, 0, entry);
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
    ecx = eax;
    edx = lift_load(&env, eax, 0xb70u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_42fd87;
L_42fb75:
    esi = lift_load(&env, ecx, 0xb78u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_42fbba;
    eax = lift_load(&env, ecx, 0xb88u, 4);
    lift_store(&env, esi, 0x17cu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_42fe28;
    eax = lift_load(&env, ecx, 0xb78u, 4);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42b110u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xb78u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42fbab:
    eax = lift_load(&env, ecx, 0xb78u, 4);
    edx = lift_load(&env, eax, 0x158u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42fbba:
    eax = lift_load(&env, ecx, 0xa60u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_42fc56;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xce8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x4ccu, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_42fe9e;
    edx = lift_load(&env, ecx, 0xb80u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_42fe9e;
    eax = lift_load(&env, ecx, 0xa60u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42aa20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xa60u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xa60u, 4);
    edx = lift_load(&env, eax, 0x18u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_42fc56;
    eax = lift_load(&env, ecx, 0xa60u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_42fc56;
L_42fc2d:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431b80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_42fe81;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431c60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_42fe72;
    lift_store(&env, ecx, 0xbd8u, 4, 0x0u);
L_42fc56:
    esi = lift_load(&env, ecx, 0xa60u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_42fc93;
    edx = lift_load(&env, ecx, 0xa61u, 4);
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42a960u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ecx, 0xa62u, 4);
    eax = lift_load(&env, ecx, 0xa60u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42a970u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xa60u, 4);
    edx = lift_load(&env, eax, 0x158u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42fc93:
    edx = 0x41u;
    eax = (ecx + 0x220u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b23c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x41u;
    eax = (ecx + 0x87cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b23c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5u;
    eax = (ecx + 0x988u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b23c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xdu;
    eax = (ecx + 0x9e8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b23c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xdu;
    eax = (ecx + 0xa2cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b23c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x104u;
    eax = (ecx + 0x324u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b23c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x41u;
    eax = (ecx + 0xbdcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b23c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = lift_load(&env, ecx, 0xce0u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_42fd18;
    edx = lift_load(&env, edi, 0x158u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42fd18:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0xb8cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_42fef6;
L_42fd25:
    ebx = (ecx + 0xcecu);
    eax = ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6200u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5f50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f850u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ef00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ef10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ef20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ef30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ef40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ef50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f870u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f880u, eax, edx, ebx, ecx, 0, esp);
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
L_42fd87:
    eax = lift_load(&env, eax, 0xb84u, 4);
    lift_store(&env, edx, 0x15cu, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0xb84u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_42fdc8;
    eax = lift_load(&env, ecx, 0xb70u, 4);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42bab0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xb70u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xb70u, 4);
    edx = lift_load(&env, eax, 0x158u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_42fb75;
L_42fdc8:
    edx = 0x1u;
    eax = lift_load(&env, ecx, 0xb70u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42bab0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xb70u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xb70u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_42fe09;
    eax = lift_load(&env, ecx, 0xb70u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xb70u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ba70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42fe09:
    eax = lift_load(&env, ecx, 0xb70u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xb70u, 4);
    edx = lift_load(&env, eax, 0x158u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_42fb75;
L_42fe28:
    edx = 0x1u;
    eax = lift_load(&env, ecx, 0xb78u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42b110u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xb78u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xb78u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_42fbab;
    eax = lift_load(&env, ecx, 0xb78u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xb78u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42b0f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_42fbab;
L_42fe72:
    lift_store(&env, ecx, 0xbd8u, 4, 0x1u);
    goto L_42fc56;
L_42fe81:
    eax = lift_load(&env, ecx, 0xa60u, 4);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, eax, 0x16u, 2)) & 0xffffu);
    ebx = ebx + 1u;
    edx = edx - 1u;
    lift_store(&env, eax, 0x16u, 2, (ebx & 0xffffu));
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_42fc2d;
    goto L_42fc56;
L_42fe9e:
    ebx = lift_load(&env, ecx, 0xb90u, 4);
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_42fee6;
    edx = ebx;
    eax = lift_load(&env, ecx, 0xa60u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42aa20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xa60u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xa60u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_42fee6;
    eax = lift_load(&env, ecx, 0xa60u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0xa60u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42a9d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42fee6:
    eax = lift_load(&env, ecx, 0xa60u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_42fc56;
L_42fef6:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x430930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_42fd25;
}
