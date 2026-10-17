/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_12.h"

uint32_t lifted_f4cae30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CAE30_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CAE30_STACK, 0, entry);
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
    esp = esp - 0x34u;
    ebx = eax;
    lift_store(&env, esp, 0x30u, 4, edx);
    {
        (void)lift_and(8, lift_load(&env, esp, 0x30u, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4cae69;
    lift_store(&env, esp, 0x20u, 4, 0x1u);
    edx = 0x518bc0u;
    lift_store(&env, esp, 0x0u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4cafc5;
L_4cae69:
    lift_store(&env, eax, 0x0u, 4, 0x518a94u);
    lift_store(&env, esp, 0x24u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0x30u, 1)) & 0xffu);
    lift_store(&env, esp, 0x28u, 1, (eax & 0xffu));
    eax = (esp + 0x14u);
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
    lift_store(&env, esp, 0x18u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x1cu, 4, 0x518944u);
    lift_store(&env, esp, 0x20u, 4, 0x3u);
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x78u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caebd;
    eax = lift_load(&env, ebx, 0x78u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4caebd;
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4caebd:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0xa0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caedb;
    eax = lift_load(&env, ebx, 0xa0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4caedb;
    ecx = lift_load(&env, eax, 0x1cu, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x14u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4caedb:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x14u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4caf2e;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c5c08u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caf0a;
    if (fl.zf)
        goto L_4caf00;
    eax = lift_load(&env, 0u, 0x5c5c08u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4caf00:
    lift_store(&env, 0u, 0x5c5c08u, 4, 0x0u);
L_4caf0a:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c5c04u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caf2e;
    if (fl.zf)
        goto L_4caf24;
    eax = lift_load(&env, 0u, 0x5c5c04u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4caf24:
    lift_store(&env, 0u, 0x5c5c04u, 4, 0x0u);
L_4caf2e:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x8cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caf42;
    {
        uint32_t v = lift_load(&env, ebx, 0x8cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dc4b0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4caf42:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x90u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caf56;
    {
        uint32_t v = lift_load(&env, ebx, 0x90u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dc4b0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4caf56:
    eax = lift_load(&env, ebx, 0xa8u, 2);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4caf69;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c10u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4caf69:
    eax = lift_load(&env, ebx, 0xaau, 2);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4caf7c;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c10u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4caf7c:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0xa4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caf99;
    eax = lift_load(&env, ebx, 0xa4u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4caf99;
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4caf99:
    edx = 0x1u;
    eax = ebx;
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cbfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(8, lift_load(&env, esp, 0x30u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4cafbb;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4cafbb:
    eax = lift_load(&env, esp, 0x14u, 4);
    env.chain = eax;
L_4cafc5:
    eax = ebx;
    {
        uint32_t r = lift_add(32, esp, 0x34u, &fl);
        esp = r;
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

uint32_t lifted_f4cd819(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CD819_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CD819_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = eax;
    eax = lift_load(&env, ebx, 0x4u, 4);
    eax = eax + lift_load(&env, esi, 0x4u, 4);
    ebx = lift_load(&env, eax, 0x4u, 1);
    {
        (void)lift_and(32, ebx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4cd82c;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4cd82c:
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + lift_load(&env, esi, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC970_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC970_STACK, 0, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
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
    esp = esp - 0x40u;
    esi = eax;
    ecx = ebx;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x15u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x15u, 1)) & 0xffu);
    ebx = lift_load(&env, ebx, 0x8u, 4);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x5fu) & 0xffu);
    eax = eax & 0xffu;
    {
        (void)lift_sub(32, eax, 0x47u, &fl);
    }
    if (!fl.zf)
        goto L_4ec9ba;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4ec9a0;
    ebx = 0x1u;
L_4ec9a0:
    lift_store(&env, ebp, 0xffffffbcu, 4, 0x4u);
    edi = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = 0x1u;
    edi = edi - 0x2u;
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
    goto L_4ec9d9;
L_4ec9ba:
    {
        (void)lift_sub(32, eax, 0x45u, &fl);
    }
    if (!fl.zf)
        goto L_4ec9cc;
    edi = 0x1u;
    lift_store(&env, ebp, 0xffffffbcu, 4, edi);
    lift_store(&env, ebp, 0xffffffb8u, 4, edi);
    goto L_4ec9d9;
L_4ec9cc:
    edi = 0x2u;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffbcu, 4, edi);
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
L_4ec9d9:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4ec9e3;
    lift_store(&env, ebp, 0xffffffbcu, 1, lift_load(&env, ebp, 0xffffffbcu, 1) | 0x10u);
L_4ec9e3:
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x8u;
    lift_store(&env, edx, 0x0u, 4, eax);
    edx = eax;
    eax = lift_load(&env, eax, 0xfffffff8u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = lift_load(&env, edx, 0xfffffffcu, 4);
    edx = (ebp + 0xffffffe0u);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    eax = (ebp + 0xffffffecu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e53b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4eca0d;
    ebx = 0x6u;
L_4eca0d:
    eax = (ebp + 0xffffffe0u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
    ebx = (esi + 0x1u);
    edx = (ebp + 0xffffffb4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eccb9u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, ecx, 0x28u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ecx, 0x2cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ecx, 0x30u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ecx, 0x34u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffc8u, 4), 0x0u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4eca50;
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x2du);
    goto L_4eca79;
L_4eca50:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4eca67;
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x2bu);
    goto L_4eca79;
L_4eca67:
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4eca79;
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x20u);
L_4eca79:
    edx = 0u;
    eax = esi;
    esp = (ebp + 0xfffffff4u);
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
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}
