/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_13.h"

uint32_t lifted_f4d2710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D2710_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D2710_STACK, 0, entry);
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
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x30u;
    ebp = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cccc0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4d2729;
    esi = esi ^ esi;
    goto L_4d272c;
L_4d2729:
    esi = lift_load(&env, edx, 0x1cu, 4);
L_4d272c:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4d276d;
    {
        (void)lift_and(32, ebx, 0x40000000u, &fl);
    }
    if (fl.zf)
        goto L_4d2744;
    {
        uint32_t v = lift_load(&env, ebp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19c8u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    goto L_4d2750;
L_4d2744:
    {
        uint32_t v = 0x4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a04u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_4d2750:
    esi = eax;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4d276d;
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
        uint32_t v = 0x36bu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d276d;
    esi = eax;
L_4d276d:
    eax = esp;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19f8u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, ebx, 0x40000000u, &fl);
    }
    if (!fl.zf)
        goto L_4d27d6;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4d27a0;
    {
        uint32_t v = 0xfffffff0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19f0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, 0x10000000u, &fl);
    }
    if (fl.zf)
        goto L_4d279e;
    {
        (void)lift_and(32, eax, 0x20000000u, &fl);
    }
    if (fl.zf)
        goto L_4d27a0;
L_4d279e:
    esi = esi ^ esi;
L_4d27a0:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x14u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x30u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1af4u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4d27c7;
    ecx = 0x4u;
    edi = (esp + 0x20u);
    esi = (esp + 0x10u);
    lift_string(&env, 0, 4, 1, &eax, &ecx, &esi, &edi, &fl);
    goto L_4d280c;
L_4d27c7:
    eax = (esp + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19f8u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    goto L_4d280c;
L_4d27d6:
    {
        uint32_t v = lift_load(&env, ebp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19c8u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = eax;
    eax = (esp + 0x10u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f196cu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    eax = (esp + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f196cu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x24u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a48u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
L_4d280c:
    edx = lift_load(&env, esp, 0x20u, 4);
    edx = edx + lift_load(&env, esp, 0x28u, 4);
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
    esi = lift_load(&env, esp, 0x8u, 4);
    esi = esi - lift_load(&env, esp, 0x0u, 4);
    ebx = eax;
    edx = esi;
    eax = esi;
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
    edx = lift_load(&env, esp, 0x24u, 4);
    edx = edx + lift_load(&env, esp, 0x2cu, 4);
    ebx = ebx - eax;
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
    edx = lift_load(&env, esp, 0xcu, 4);
    edx = edx - lift_load(&env, esp, 0x4u, 4);
    ecx = eax;
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
    ecx = ecx - eax;
    {
        (void)lift_sub(32, ebx, lift_load(&env, esp, 0x10u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4d2865;
    ebx = lift_load(&env, esp, 0x10u, 4);
    goto L_4d2874;
L_4d2865:
    eax = (ebx + esi);
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x18u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4d2874;
    ebx = lift_load(&env, esp, 0x18u, 4);
    ebx = ebx - esi;
L_4d2874:
    {
        (void)lift_sub(32, ecx, lift_load(&env, esp, 0x14u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4d2880;
    ecx = lift_load(&env, esp, 0x14u, 4);
    goto L_4d2897;
L_4d2880:
    eax = lift_load(&env, esp, 0xcu, 4);
    eax = eax - lift_load(&env, esp, 0x4u, 4);
    edx = (ecx + eax);
    {
        (void)lift_sub(32, edx, lift_load(&env, esp, 0x1cu, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4d2897;
    ecx = lift_load(&env, esp, 0x1cu, 4);
    ecx = ecx - eax;
L_4d2897:
    {
        uint32_t v = 0x15u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = ebp;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccd80u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        uint32_t r = lift_add(32, esp, 0x30u, &fl);
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

uint32_t lifted_f4dfac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DFAC0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DFAC0_STACK, 0, entry);
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
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x4u;
    (void)(edx);
    edi = eax;
    edx = lift_load(&env, ebx, 0x28u, 4);
    ebp = ecx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4dfb19;
L_4dfad4:
    edx = edx ^ edx;
    eax = esp;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edi, 0x0u, 2)) & 0xffffu);
    edi = edi + 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e62e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4dfaf8;
    {
        (void)lift_sub(32, eax, lift_load(&env, ebx, 0x28u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4dfb12;
    esi = esp;
L_4dfaf2:
    ecx = ecx - 1u;
    {
        (void)lift_sub(32, ecx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dfb00;
L_4dfaf8:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x28u, 4), 0x0u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4dfad4;
    goto L_4dfb19;
L_4dfb00:
    edx = edx ^ edx;
    eax = ebx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebp, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebx, 0x28u, 4);
    eax = eax - 1u;
    esi = esi + 1u;
    lift_store(&env, ebx, 0x28u, 4, eax);
    goto L_4dfaf2;
L_4dfb12:
    lift_store(&env, ebx, 0x28u, 4, 0x0u);
L_4dfb19:
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
        (void)(v);
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

uint32_t lifted_f4dfb24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DFB24_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DFB24_STACK, 0, entry);
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
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x10u;
    esi = eax;
    ecx = ebx;
    eax = 0u;
    (void)(eax);
    lift_store(&env, ebx, 0x20u, 4, 0x0u);
    lift_store(&env, ebx, 0x24u, 4, 0x0u);
    lift_store(&env, ebx, 0x28u, 4, 0x0u);
    lift_store(&env, ebx, 0x2cu, 4, 0x0u);
    lift_store(&env, ebx, 0x30u, 4, 0x0u);
    edi = esi;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x15u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x34u, 4, 0x0u);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x69u, &fl);
    }
    if (fl.cf)
        goto L_4dfb84;
    if (fl.cf || fl.zf)
        goto L_4dfbfe;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x75u, &fl);
    }
    if (fl.cf)
        goto L_4dfb7b;
    if (fl.cf || fl.zf)
        goto L_4dfb97;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4dfb97;
    goto L_4dfcdb;
L_4dfb7b:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6fu, &fl);
    }
    if (fl.zf)
        goto L_4dfb97;
    goto L_4dfcdb;
L_4dfb84:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x58u, &fl);
    }
    if (fl.cf)
        goto L_4dfcdb;
    if (fl.cf || fl.zf)
        goto L_4dfb97;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x64u, &fl);
    }
    if (fl.zf)
        goto L_4dfbfe;
    goto L_4dfcdb;
L_4dfb97:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1fu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfbbd;
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    eax = lift_load(&env, ebp, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x4u, 4, eax);
    goto L_4dfcdb;
L_4dfbbd:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4dfbd6;
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    goto L_4dfcdb;
L_4dfbd6:
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    eax = lift_load(&env, ebp, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4dfcdb;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esp, 0x8u, 2)) & 0xffffu);
    lift_store(&env, esp, 0x8u, 4, eax);
    goto L_4dfcdb;
L_4dfbfe:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1fu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfc21;
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x4u, 4, eax);
    goto L_4dfc54;
L_4dfc21:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4dfc33;
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    eax = lift_load(&env, ebp, 0xfffffffcu, 4);
    goto L_4dfc50;
L_4dfc33:
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu) << 8);
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_and(8, ((ebx >> 8) & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4dfc54;
    eax = lift_load(&env, esp, 0x6u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
L_4dfc50:
    lift_store(&env, esp, 0x8u, 4, eax);
L_4dfc54:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1fu, 1)) & 0xffu);
    eax = eax ^ eax;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfc67;
    {
        (void)lift_and(8, lift_load(&env, esp, 0x7u, 1), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4dfc6e;
    goto L_4dfc72;
L_4dfc67:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dfc72;
L_4dfc6e:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dfcb4;
L_4dfc72:
    eax = lift_load(&env, ecx, 0x20u, 4);
    ebx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, ebx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x2du);
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1fu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfcae;
    ebx = lift_load(&env, esp, 0x0u, 4);
    ebp = lift_load(&env, esp, 0x4u, 4);
    {
        uint32_t a = ebx;
        ebx = (~a) & lift_mask(4);
    }
    {
        uint32_t a = ebp;
        ebp = (~a) & lift_mask(4);
    }
    lift_store(&env, esp, 0x0u, 4, ebx);
    eax = (ebx + 0x1u);
    lift_store(&env, esp, 0x4u, 4, ebp);
    lift_store(&env, esp, 0x0u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dfca6;
    eax = (ebp + 0x1u);
    goto L_4dfca8;
L_4dfca6:
    eax = ebp;
L_4dfca8:
    lift_store(&env, esp, 0x4u, 4, eax);
    goto L_4dfcdb;
L_4dfcae:
    lift_store(&env, esp, 0x8u, 4, 0u - lift_load(&env, esp, 0x8u, 4));
    goto L_4dfcdb;
L_4dfcb4:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4dfcca;
    eax = lift_load(&env, ecx, 0x20u, 4);
    ebx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, ebx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x2bu);
    goto L_4dfcdb;
L_4dfcca:
    {
        (void)lift_and(8, (eax & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4dfcdb;
    eax = lift_load(&env, ecx, 0x20u, 4);
    ebx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, ebx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x20u);
L_4dfcdb:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x15u, 1)) & 0xffu);
    ebx = 0xau;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x64u, &fl);
    }
    if (fl.cf)
        goto L_4dfd48;
    if (fl.cf || fl.zf)
        goto L_4dfef8;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6fu, &fl);
    }
    if (fl.cf)
        goto L_4dfd29;
    if (fl.cf || fl.zf)
        goto L_4dfed8;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x73u, &fl);
    }
    if (fl.cf)
        goto L_4dfd1c;
    if (fl.cf || fl.zf)
        goto L_4dfdf1;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x75u, &fl);
    }
    if (fl.cf)
        goto L_4e010d;
    if (fl.cf || fl.zf)
        goto L_4dfef8;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4dfe93;
    goto L_4e010d;
L_4dfd1c:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x70u, &fl);
    }
    if (fl.zf)
        goto L_4dffad;
    goto L_4e010d;
L_4dfd29:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x66u, &fl);
    }
    if (fl.cf)
        goto L_4dfdce;
    if (fl.cf || fl.zf)
        goto L_4dfd99;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x67u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4dfdce;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x69u, &fl);
    }
    if (fl.zf)
        goto L_4dfef8;
    goto L_4e010d;
L_4dfd48:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x47u, &fl);
    }
    if (fl.cf)
        goto L_4dfd84;
    if (fl.cf || fl.zf)
        goto L_4dfdce;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x53u, &fl);
    }
    if (fl.cf)
        goto L_4dfd77;
    if (fl.cf || fl.zf)
        goto L_4dfdf1;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x58u, &fl);
    }
    if (fl.cf)
        goto L_4e010d;
    if (fl.cf || fl.zf)
        goto L_4dfe93;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x63u, &fl);
    }
    if (fl.zf)
        goto L_4e0040;
    goto L_4e010d;
L_4dfd77:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x50u, &fl);
    }
    if (fl.zf)
        goto L_4dffad;
    goto L_4e010d;
L_4dfd84:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x45u, &fl);
    }
    if (fl.cf)
        goto L_4dfd8c;
    if (fl.cf || fl.zf)
        goto L_4dfdce;
    goto L_4dfd99;
L_4dfd8c:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x43u, &fl);
    }
    if (fl.zf)
        goto L_4e00cc;
    goto L_4e010d;
L_4dfd99:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4dfdce;
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    ebx = ecx;
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df978u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xffffffffu;
    edx = 0u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x28u, 4, eax);
    goto L_4e0120;
L_4dfdce:
    ebx = ecx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dfa74u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dfa7cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0u;
    edi = (esi + 0x1u);
    (void)(eax);
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4dfdf1:
    lift_store(&env, esi, 0x0u, 1, 0x0u);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4dfe18;
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x8u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    eax = lift_load(&env, ebp, 0xfffffff8u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xfffffffcu, 2)) & 0xffffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dfe12;
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4dfe40;
L_4dfe12:
    (void)(edx);
    edi = eax;
    goto L_4dfe40;
L_4dfe18:
    {
        (void)lift_and(8, (eax & 0xffu), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4dfe2c;
    esi = lift_load(&env, edx, 0x0u, 4);
    esi = esi + 0x4u;
    lift_store(&env, edx, 0x0u, 4, esi);
    eax = lift_load(&env, esi, 0xfffffffcu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dfe40;
    goto L_4dfe3a;
L_4dfe2c:
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dfe40;
L_4dfe3a:
    edx = 0u;
    edi = eax;
    (void)(edx);
L_4dfe40:
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x53u, &fl);
    }
    if (!fl.zf)
        goto L_4dfe4e;
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4dfe54;
    goto L_4dfe62;
L_4dfe4e:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4dfe62;
L_4dfe54:
    edx = 0u;
    eax = edi;
    ebx = lift_load(&env, ecx, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df8a8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4dfe6e;
L_4dfe62:
    edx = 0u;
    eax = edi;
    ebx = lift_load(&env, ecx, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dfe6e:
    edx = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, ecx, 0x28u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e0120;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e0120;
    lift_store(&env, ecx, 0x28u, 4, edx);
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4dfe93:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfed3;
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1fu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfeae;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dfeb5;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dfed3;
    goto L_4dfeb5;
L_4dfeae:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dfed3;
L_4dfeb5:
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x30u);
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    edx = (esi + eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x15u, 1)) & 0xffu);
    lift_store(&env, edx, 0x0u, 1, (eax & 0xffu));
L_4dfed3:
    ebx = 0x10u;
L_4dfed8:
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x6fu, &fl);
    }
    if (!fl.zf)
        goto L_4dfef8;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    ebx = 0x8u;
    {
        (void)lift_and(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfef8;
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x30u);
L_4dfef8:
    edx = 0u;
    eax = lift_load(&env, ecx, 0x20u, 4);
    (void)(edx);
    eax = eax + esi;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ecx, 0x1fu, 1)) & 0xffu) << 8);
    edi = eax;
    {
        (void)lift_and(8, ((edx >> 8) & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dff41;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff26;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff26;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff26;
    lift_store(&env, eax, 0x0u, 1, 0x0u);
    eax = eax ^ eax;
    goto L_4dff7f;
L_4dff26:
    edx = lift_load(&env, ecx, 0x20u, 4);
    eax = esp;
    edx = edx + esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e63b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x58u, &fl);
    }
    if (!fl.zf)
        goto L_4dff71;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e012cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4dff71;
L_4dff41:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff56;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff56;
    lift_store(&env, eax, 0x0u, 1, 0x0u);
    eax = eax ^ eax;
    goto L_4dff7f;
L_4dff56:
    edx = lift_load(&env, ecx, 0x20u, 4);
    eax = lift_load(&env, esp, 0x8u, 4);
    edx = edx + esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e64a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x58u, &fl);
    }
    if (!fl.zf)
        goto L_4dff71;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e012cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dff71:
    ebx = 0xffffffffu;
    edx = 0u;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dff7f:
    lift_store(&env, ecx, 0x28u, 4, eax);
    edx = eax;
    eax = lift_load(&env, ecx, 0x8u, 4);
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4dff90;
    eax = eax - edx;
    lift_store(&env, ecx, 0x24u, 4, eax);
L_4dff90:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x8u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e0120;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dfa7cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4dffad:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dffc9;
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4dffc2;
    lift_store(&env, ecx, 0x4u, 4, 0xdu);
    goto L_4dffc9;
L_4dffc2:
    lift_store(&env, ecx, 0x4u, 4, 0x8u);
L_4dffc9:
    lift_store(&env, ecx, 0x1eu, 1, lift_load(&env, ecx, 0x1eu, 1) & 0xf9u);
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    ebp = lift_load(&env, eax, 0xfffffffcu, 4);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4e0008;
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    ebx = 0x4u;
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    edx = esi;
    eax = eax & 0xffffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df914u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x8u;
    edx = (esi + 0x5u);
    eax = ebp;
    lift_store(&env, esi, 0x4u, 1, 0x3au);
    goto L_4e0011;
L_4e0008:
    ebx = 0x8u;
    edx = esi;
    eax = ebp;
L_4e0011:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df914u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x50u, &fl);
    }
    if (!fl.zf)
        goto L_4e0023;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e012cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e0023:
    ebx = 0xffffffffu;
    edx = 0u;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x20u, 4, eax);
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4e0040:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    lift_store(&env, ecx, 0x20u, 4, 0x1u);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4e00b4;
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0xfffffffcu, 2)) & 0xffffu);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = (esp + 0xcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e62e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4e0120;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0xcu, 1)) & 0xffu);
    ebp = lift_load(&env, 0u, 0x5c8950u, 4);
    lift_store(&env, esi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4e0120;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0xcu, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x5c8961u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4e0120;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0xdu, 1)) & 0xffu);
    lift_store(&env, esi, 0x1u, 1, (eax & 0xffu));
    lift_store(&env, ecx, 0x20u, 4, lift_load(&env, ecx, 0x20u, 4) + 1u);
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4e00b4:
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0xfffffffcu, 1)) & 0xffu);
    lift_store(&env, esi, 0x0u, 1, (eax & 0xffu));
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4e00cc:
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xfffffffcu, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e62e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4e00fa;
    lift_store(&env, ecx, 0x20u, 4, eax);
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4e00fa:
    lift_store(&env, ecx, 0x20u, 4, 0x0u);
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4e010d:
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x15u, 1)) & 0xffu);
    lift_store(&env, esi, 0x0u, 1, (eax & 0xffu));
    lift_store(&env, ecx, 0x20u, 4, 0x1u);
L_4e0120:
    edx = 0u;
    eax = edi;
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
        (void)(v);
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

uint32_t lifted_f4e63b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E63B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E63B0_STACK, 0, entry);
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
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x44u;
    esi = eax;
    lift_store(&env, esp, 0x3cu, 4, edx);
    edi = (esp + 0x34u);
    ebp = (esp + 0x1u);
    eax = 0u;
    lift_store(&env, esp, 0x40u, 4, edx);
    (void)(eax);
    edx = edx ^ edx;
    {
        uint32_t r = lift_xor(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x24u, 4, ebx);
    lift_store(&env, esp, 0x28u, 4, edx);
    lift_store(&env, esp, 0x0u, 1, ((eax >> 8) & 0xffu));
L_4e63df:
    edi = (esp + 0x2cu);
    esi = (esp + 0x34u);
    ebx = (esp + 0x24u);
    eax = (esp + 0x34u);
    edx = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    ecx = lift_load(&env, ebx, 0x4u, 4);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e88bfu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x4u, 4, edx);
    lift_store(&env, esi, 0x0u, 4, eax);
    lift_store(&env, edi, 0x4u, 4, ecx);
    lift_store(&env, edi, 0x0u, 4, ebx);
    eax = lift_load(&env, esp, 0x2cu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x50979cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0x0u, 1, (eax & 0xffu));
    ebx = lift_load(&env, esp, 0x34u, 4);
    ebp = ebp + 1u;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e63df;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x38u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e63df;
L_4e6425:
    ebx = lift_load(&env, esp, 0x40u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffffu, 1)) & 0xffu);
    ebp = ebp - 1u;
    esi = (ebx + 0x1u);
    lift_store(&env, ebx, 0x0u, 1, (eax & 0xffu));
    lift_store(&env, esp, 0x40u, 4, esi);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4e6425;
    eax = lift_load(&env, esp, 0x3cu, 4);
    {
        uint32_t r = lift_add(32, esp, 0x44u, &fl);
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
        (void)(v);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7f18(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7F18_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7F18_STACK, 0, entry);
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
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x4u;
    ebp = eax;
    lift_store(&env, esp, 0x0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9d10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ebx = r;
    }
    edi = ebp;
    ebx = ebx | eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9e30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4e7f3b:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e7f53;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e7f3b;
L_4e7f53:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
    ecx = ecx - ecx;
    ecx = ecx - 1u;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    {
        uint32_t a = ecx;
        ecx = (~a) & lift_mask(4);
    }
    ecx = ecx - 1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    esi = (ecx + ebp);
    edx = (esi + 0x4u);
    lift_store(&env, esi, 0x0u, 1, 0x74u);
    ecx = esi;
L_4e7f6f:
    eax = ebx;
    eax = eax & 0xfu;
    edx = edx - 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7f0cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        ebx = r;
    }
    lift_store(&env, edx, 0x1u, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4e7f6f;
    eax = lift_load(&env, esp, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax & 0xfu;
    lift_store(&env, esi, 0x5u, 1, 0x5fu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7f0cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x6u, 1, (eax & 0xffu));
    eax = lift_load(&env, esp, 0x0u, 4);
    eax = eax & 0xfu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7f0cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x8u, 1, 0x2eu);
    lift_store(&env, esi, 0x9u, 1, 0x74u);
    lift_store(&env, esi, 0xau, 1, 0x6du);
    lift_store(&env, esi, 0xbu, 1, 0x70u);
    lift_store(&env, esi, 0xcu, 1, 0x0u);
    lift_store(&env, esi, 0x7u, 1, (eax & 0xffu));
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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

uint32_t lifted_f4e843c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E843C_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E843C_STACK, 0, entry);
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
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cc8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ba0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, 0u, 0x5c8aa0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e8464;
L_4e8459:
    {
        (void)lift_sub(32, eax, lift_load(&env, ebx, 0x4u, 4), &fl);
    }
    if (fl.zf)
        goto L_4e8464;
    ebx = lift_load(&env, ebx, 0x0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e8459;
L_4e8464:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0xcu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e848f;
    edx = lift_load(&env, 0u, 0x509768u, 4);
    eax = lift_load(&env, ebx, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e84dc;
    edx = 0x1u;
    eax = 0x513020u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e628cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e84dc;
L_4e848f:
    eax = 0x1u;
    edx = lift_load(&env, 0u, 0x509768u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e84b4;
    edx = 0x1u;
    eax = 0x513048u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e628cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e84b4:
    esi = lift_load(&env, ebx, 0x8u, 4);
    edi = ebp;
    ecx = lift_load(&env, esi, 0xf0u, 4);
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    lift_store(&env, ebx, 0xcu, 4, 0x1u);
L_4e84dc:
    lift_store(&env, ebx, 0x8u, 4, ebp);
    eax = lift_load(&env, 0u, 0x509768u, 4);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0x52u, 1, 0x1u);
    esi = lift_load(&env, 0u, 0x507c98u, 4);
    lift_store(&env, ebp, 0x53u, 1, 0x0u);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xf0u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ce0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cccu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebp;
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

uint32_t lifted_f4e969c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E969C_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E969C_STACK, 0, entry);
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
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x14u;
    ebp = eax;
    lift_store(&env, esp, 0x0u, 4, edx);
    lift_store(&env, esp, 0x10u, 4, ebx);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x3au, &fl);
    }
    if (!fl.zf)
        goto L_4e96b2;
    ebp = ebp + 1u;
L_4e96b2:
    esi = ebp;
L_4e96b4:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e96d7;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2cu, &fl);
    }
    if (fl.zf)
        goto L_4e96d7;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2du, &fl);
    }
    if (fl.zf)
        goto L_4e96d7;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2bu, &fl);
    }
    if (fl.zf)
        goto L_4e96d7;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x30u, &fl);
    }
    if (fl.cf)
        goto L_4e96d4;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x39u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e96d7;
L_4e96d4:
    ebp = ebp + 1u;
    goto L_4e96b4;
L_4e96d7:
    ebx = ebp;
    ebx = ebx - esi;
    {
        (void)lift_sub(32, ebx, 0x80u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e96e8;
    ebx = 0x80u;
L_4e96e8:
    edi = lift_load(&env, esp, 0x0u, 4);
    ecx = ebx;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    ebx = ebx + edi;
    eax = (ebp + 0x1u);
    esi = esi ^ esi;
    lift_store(&env, ebx, 0x0u, 1, 0x0u);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4e9719;
    esi = 0x1u;
    goto L_4e971e;
L_4e9719:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2bu, &fl);
    }
    if (!fl.zf)
        goto L_4e9720;
L_4e971e:
    ebp = eax;
L_4e9720:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x30u, &fl);
    }
    if (fl.cf)
        goto L_4e97a8;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x39u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e97a8;
    edx = (esp + 0xcu);
    edi = edi ^ edi;
    eax = ebp;
    lift_store(&env, esp, 0x4u, 4, edi);
    lift_store(&env, esp, 0x8u, 4, edi);
    lift_store(&env, esp, 0xcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ebp = eax;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x3au, &fl);
    }
    if (!fl.zf)
        goto L_4e9774;
    edx = (esp + 0x8u);
    eax = eax + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, eax, 0x0u, 1)) & 0xffu) << 8);
    ebp = eax;
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x3au, &fl);
    }
    if (!fl.zf)
        goto L_4e9774;
    edx = (esp + 0x4u);
    eax = eax + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
L_4e9774:
    ebx = lift_load(&env, esp, 0xcu, 4);
    eax = ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax - ebx;
    edx = lift_load(&env, esp, 0x8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = edx + eax;
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = lift_load(&env, esp, 0x4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = edx + eax;
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4e97a8;
    ebx = edx;
    ebx = 0u - ebx;
    lift_store(&env, eax, 0x0u, 4, ebx);
L_4e97a8:
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9e30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9E30_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9E30_STACK, 0, entry);
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
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x50b100u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e9eed;
    ebx = 0x50b0ecu;
    goto L_4e9e82;
L_4e9e49:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dac40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9e7f;
    edi = eax;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
    ecx = ecx - ecx;
    ecx = ecx - 1u;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    {
        uint32_t a = ecx;
        ecx = (~a) & lift_mask(4);
    }
    ecx = ecx - 1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    {
        (void)lift_sub(32, ecx, 0x103u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e9e7f;
    ebx = 0x103u;
    eax = 0x50b100u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e9e89;
L_4e9e7f:
    ebx = ebx + 0x4u;
L_4e9e82:
    eax = lift_load(&env, ebx, 0x0u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e9e49;
L_4e9e89:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x50b100u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e9ebc;
    edx = edx ^ edx;
    eax = eax ^ eax;
    edi = 0x50b100u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3ac0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4e9ea3:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e9ebb;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e9ea3;
L_4e9ebb:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
L_4e9ebc:
    edi = 0x50b100u;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
    ecx = ecx - ecx;
    ecx = ecx - 1u;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    {
        uint32_t a = ecx;
        ecx = (~a) & lift_mask(4);
    }
    ecx = ecx - 1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    eax = (ecx + 0xffffffffu);
    eax = eax + 0x50b100u;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x5cu, &fl);
    }
    if (fl.zf)
        goto L_4e9eed;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2fu, &fl);
    }
    if (fl.zf)
        goto L_4e9eed;
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, eax, 0x0u, 1, 0x5cu);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, eax, 0x0u, 1, 0x0u);
L_4e9eed:
    eax = 0x50b100u;
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
}

uint32_t lifted_f4ed2b5(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ED2B5_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ED2B5_STACK, 0, entry);
    goto L_4ed2b5;
L_4ed29b:
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
L_4ed2b5:
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
    esp = esp - 0xcu;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ed2d5;
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) + edx);
    goto L_4ed2e3;
L_4ed2d5:
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = ebx - edx;
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    ecx = (ebx + 0x1u);
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
L_4ed2e3:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = edi ^ edi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x8u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 4, edi);
    {
        (void)lift_and(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4ed30e;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffecu, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed2fe;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_4ed2fe:
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = ebx - 1u;
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed30e;
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffecu, 4, esi);
L_4ed30e:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ed32e;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    ebx = lift_load(&env, ebp, 0x8u, 4);
    edx = (eax + 0x1u);
    eax = eax + ebx;
    lift_store(&env, ebp, 0xfffffff4u, 4, edx);
    lift_store(&env, eax, 0x0u, 1, 0x30u);
    goto L_4ed3aa;
L_4ed32e:
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, edi);
    {
        (void)lift_sub(32, edi, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ed33b;
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
L_4ed33b:
    edi = lift_load(&env, ebp, 0x8u, 4);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    ecx = lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    edi = edi + ebx;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = (ebx + eax);
    esi = esi + eax;
    edi = edi - eax;
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    ebx = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed3aa;
    ecx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = ebx;
    esi = lift_load(&env, ebp, 0xfffffff4u, 4);
    eax = eax - ecx;
    edx = 0x30u;
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    eax = lift_load(&env, ebp, 0x8u, 4);
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = eax + esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    edi = (esi + eax);
    lift_store(&env, ebp, 0xfffffff4u, 4, edi);
L_4ed3aa:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, edx, 0x18u, 4, eax);
    {
        (void)lift_and(8, lift_load(&env, edx, 0x8u, 1), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_4ed3d9;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x0u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ed3c8;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x8u, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4ed3d9;
L_4ed3c8:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    edi = lift_load(&env, ebp, 0x8u, 4);
    esi = (eax + 0x1u);
    eax = eax + edi;
    lift_store(&env, ebp, 0xfffffff4u, 4, esi);
    lift_store(&env, eax, 0x0u, 1, 0x2eu);
L_4ed3d9:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed408;
    eax = lift_load(&env, ebp, 0x8u, 4);
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    ebx = edx;
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    edx = 0x30u;
    ebx = 0u - ebx;
    eax = eax + ecx;
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = (ecx + eax);
    lift_store(&env, ebp, 0xfffffff4u, 4, esi);
L_4ed408:
    edi = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ed458;
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffe0u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed417;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
L_4ed417:
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4ed444;
    edi = lift_load(&env, ebp, 0x8u, 4);
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    edi = edi + ecx;
    ecx = ebx;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) + ebx);
L_4ed444:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, edx, 0x1cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax - edi;
    lift_store(&env, edx, 0x20u, 4, eax);
L_4ed458:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xcu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ed477;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    ecx = lift_load(&env, ebp, 0x8u, 4);
    ebx = (eax + 0x1u);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = eax + ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0xcu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
L_4ed477:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + 1u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed491;
    edx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, edx, eax + 0x0u, 1, 0x2bu);
    goto L_4ed4a5;
L_4ed491:
    edx = lift_load(&env, ebp, 0xfffffff4u, 4);
    edi = esi;
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    edi = 0u - edi;
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    lift_store(&env, edx, eax + 0x0u, 1, 0x2du);
L_4ed4a5:
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = lift_load(&env, ebx, 0x10u, 4);
    {
        (void)lift_sub(32, ebx, 0x3u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ed4ee;
    eax = ebx;
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4ed4ba;
            case 1:
                goto L_4ed4ca;
            case 2:
                goto L_4ed4d5;
            case 3:
                goto L_4ed4e0;
            default:
                return 0u;
        }
    }
L_4ed4ba:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0x3e8u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed4e9;
    ebx = 0x3u;
    goto L_4ed4ee;
L_4ed4ca:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0xau, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed4d5;
    ebx = 0x2u;
L_4ed4d5:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0x64u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed4e0;
    ebx = 0x3u;
L_4ed4e0:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0x3e8u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed4ee;
L_4ed4e9:
    ebx = 0x4u;
L_4ed4ee:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x10u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed544;
    edi = edi ^ edi;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, edi);
    {
        (void)lift_sub(32, eax, 0x3e8u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed52e;
    edx = eax;
    edi = 0x3e8u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        eax = r;
    }
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = edx - eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
L_4ed52e:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = lift_load(&env, ebp, 0x8u, 4);
    ecx = (eax + 0x1u);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) + 0x30u) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
L_4ed544:
    {
        (void)lift_sub(32, ebx, 0x3u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed592;
    edi = edi ^ edi;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, edi);
    {
        (void)lift_sub(32, eax, 0x64u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed57c;
    edx = eax;
    edi = 0x64u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = edx - eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
L_4ed57c:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = lift_load(&env, ebp, 0x8u, 4);
    ecx = (eax + 0x1u);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) + 0x30u) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
L_4ed592:
    {
        (void)lift_sub(32, ebx, 0x2u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed5da;
    edi = edi ^ edi;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, edi);
    {
        (void)lift_sub(32, eax, 0xau, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed5c4;
    edx = eax;
    ebx = 0xau;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + eax;
    edx = edx - eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
L_4ed5c4:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    ecx = lift_load(&env, ebp, 0x8u, 4);
    ebx = (eax + 0x1u);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    eax = eax + ecx;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) + 0x30u) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
L_4ed5da:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    edi = lift_load(&env, ebp, 0x8u, 4);
    esi = (eax + 0x1u);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffdcu, 1)) & 0xffu);
    eax = eax + edi;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) + 0x30u) & 0xffu);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = esi;
    eax = lift_load(&env, eax, 0x1cu, 4);
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x24u, 4, edx);
    eax = (edi + esi);
    lift_store(&env, ebp, 0xfffffff4u, 4, esi);
    lift_store(&env, eax, 0x0u, 1, 0x0u);
    goto L_4ed29b;
}
