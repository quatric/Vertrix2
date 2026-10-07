/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_5.h"

uint32_t lifted_f4e3a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3A90_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3A90_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c8950u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e3aba;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x5c8961u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (edx & 0xffu), 0x1u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4e3aba;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x1u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e3aba;
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e3aba:
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e3bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3BF0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3BF0_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    esi = eax;
    edi = edx;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e3c07;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x507c34u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e3c1b;
L_4e3c07:
    eax = 0x4u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
    goto L_4e3cd3;
L_4e3c1b:
    ebp = lift_load(&env, 0u, 0x507c8cu, 4);
    ebp = lift_load(&env, ebp, (esi * 4u) + 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = esi;
    eax = lift_call(&env, 0x4e01d0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(8, (eax & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4e3c5e;
    {
        uint32_t v = 0x2u;
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
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ca8u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e3c5e;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 1, esp);
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
    return env.failed ? 0u : eax;
L_4e3c5e:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x507d28u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e3c8f;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cfcu, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e3c8f;
    edx = edi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507d28u, 4), eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
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
    return env.failed ? 0u : eax;
L_4e3c8f:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x4u);
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
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1d08u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e3cb9;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 1, esp);
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
    return env.failed ? 0u : eax;
L_4e3cb9:
    {
        (void)lift_sub(32, ebx, lift_load(&env, esp, 0x0u, 4), &fl);
    }
    if (fl.zf)
        goto L_4e3cc8;
    eax = 0xcu;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
L_4e3cc8:
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, esp, 0x0u, 4);
L_4e3cd3:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e3ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3CE0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3CE0_STACK, 0, entry);
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
    ecx = eax;
    eax = lift_load(&env, eax, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0xdu, 1)) & 0xffu) << 8);
    {
        uint32_t r = lift_xor(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4e3d79;
    ebx = (ebx & 0xffff00ffu) | (((((eax >> 8) & 0xffu)) & 0xffu) << 8);
    {
        uint32_t r = lift_and(8, ((ebx >> 8) & 0xffu), 0xefu, &fl);
        ebx = (ebx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0xcu, 1)) & 0xffu);
    lift_store(&env, ecx, 0xdu, 1, ((ebx >> 8) & 0xffu));
    {
        (void)lift_and(8, (eax & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e3db4;
    edi = lift_load(&env, ecx, 0x8u, 4);
    ebx = lift_load(&env, edi, 0x8u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e3db4;
    esi = lift_load(&env, ecx, 0x4u, 4);
    edi = ebx;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4e3db4;
L_4e3d2d:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4e3db4;
    ebx = esi;
    edx = edi;
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, 0x4e3bf0u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e3d55;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0xcu, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (ebx & 0xffu), 0x20u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    ebp = eax;
    lift_store(&env, ecx, 0xcu, 1, (ebx & 0xffu));
    goto L_4e3d71;
L_4e3d55:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e3d71;
    eax = 0xcu;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0xcu, 1)) & 0xffu) << 8);
    {
        uint32_t r = lift_or(8, ((eax >> 8) & 0xffu), 0x20u, &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    ebp = 0xffffffffu;
    lift_store(&env, ecx, 0xcu, 1, ((eax >> 8) & 0xffu));
L_4e3d71:
    {
        uint32_t r = lift_add(32, edi, edx, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_sub(32, esi, edx, &fl);
        esi = r;
    }
    if (!fl.zf)
        goto L_4e3d2d;
    goto L_4e3db4;
L_4e3d79:
    eax = lift_load(&env, ecx, 0x8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e3db4;
    {
        uint32_t r = lift_and(8, lift_load(&env, ecx, 0xcu, 1), 0xefu, &fl);
        lift_store(&env, ecx, 0xcu, 1, r);
    }
    {
        (void)lift_and(8, lift_load(&env, ecx, 0xdu, 1), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4e3db4;
    eax = lift_load(&env, ecx, 0x4u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e3da4;
    edx = eax;
    ebx = 0x1u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sub(32, 0, a, &fl);
        edx = r;
    }
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, 0x4e0150u, eax, edx, ebx, ecx, 0, esp);
L_4e3da4:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e3db4;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0xcu, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (ebx & 0xffu), 0x20u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    ebp = eax;
    lift_store(&env, ecx, 0xcu, 1, (ebx & 0xffu));
L_4e3db4:
    eax = lift_load(&env, ecx, 0x8u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    lift_store(&env, ecx, 0x0u, 4, eax);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4e3ddf;
    eax = lift_load(&env, ecx, 0x8u, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x10u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e3ddf;
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, 0x4e7c30u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e3ddf;
    ebp = eax;
L_4e3ddf:
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e3f28(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3F28_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3F28_STACK, 0, entry);
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
    ecx = eax;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, 0u, 0x5c7760u, 4);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e3f59;
L_4e3f3f:
    eax = lift_load(&env, edx, 0x4u, 4);
    {
        (void)lift_and(32, lift_load(&env, eax, 0xcu, 4), ecx, &fl);
    }
    if (fl.zf)
        goto L_4e3f53;
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    {
        (void)lift_and(8, lift_load(&env, eax, 0xdu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4e3f53;
    eax = lift_call(&env, 0x4e3ce0u, eax, edx, ebx, ecx, 0, esp);
L_4e3f53:
    edx = lift_load(&env, edx, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4e3f3f;
L_4e3f59:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e4024(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E4024_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E4024_STACK, 0, entry);
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
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    esi = 0x505234u;
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, esi, eax, &fl);
        esi = r;
    }
    eax = lift_load(&env, 0u, 0x5c7760u, 4);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e4077;
L_4e4048:
    ecx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    edx = 0x1u;
    {
        (void)lift_and(8, lift_load(&env, eax, 0xdu, 1), 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_4e406b;
    {
        (void)lift_and(8, lift_load(&env, eax, 0xdu, 1), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_4e406b;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.cf)
        goto L_4e4071;
    {
        (void)lift_sub(32, eax, 0x505282u, &fl);
    }
    if (!fl.cf)
        goto L_4e406b;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
L_4e406b:
    eax = lift_call(&env, 0x4e7ef4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
L_4e4071:
    eax = ecx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4e4048;
L_4e4077:
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e4080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E4080_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E4080_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e40c8;
L_4e408c:
    eax = ecx;
    eax = lift_call(&env, 0x4e7b50u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e40c8;
    eax = esi;
    eax = lift_call(&env, 0x4e7b50u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e40c8;
    edx = esi;
    eax = ecx;
    eax = lift_call(&env, 0x4e81d0u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e40ee;
    eax = ecx;
    eax = lift_call(&env, 0x4e3a90u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    eax = esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    eax = lift_call(&env, 0x4e3a90u, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e408c;
L_4e40c8:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e40ec;
    eax = ecx;
    eax = lift_call(&env, 0x4e7b50u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e40e2;
    eax = esi;
    eax = lift_call(&env, 0x4e7b50u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e40ec;
L_4e40e2:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
L_4e40ec:
    eax = edx;
L_4e40ee:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e4110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E4110_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E4110_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x8u, &fl);
        esp = r;
    }
    esi = eax;
    lift_store(&env, esp, 0x0u, 4, edx);
    eax = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, esp, 0x4u, 4, eax);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esi, 0x10u, 1)) & 0xffu) << 8);
    {
        uint32_t r = lift_xor(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_and(8, ((eax >> 8) & 0xffu), 0xfdu, &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_store(&env, esi, 0x10u, 1, ((eax >> 8) & 0xffu));
L_4e412f:
    ebx = lift_load(&env, esp, 0x0u, 4);
    edx = (ebx + 0x1u);
    lift_store(&env, esp, 0x0u, 4, edx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(32, ebx, 0xffu, &fl);
        ebx = r;
    }
    if (fl.zf)
        goto L_4e43a8;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        (void)lift_and(8, lift_load(&env, eax, 0x507d58u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e4166;
    eax = esi;
    eax = lift_call(&env, 0x4e44c8u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, edi, eax, &fl);
        edi = r;
    }
    goto L_4e4372;
L_4e4166:
    {
        (void)lift_sub(32, ebx, 0x25u, &fl);
    }
    if (fl.zf)
        goto L_4e4190;
    eax = esi;
    eax = lift_call(&env, 0x4e4100u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e4371;
    {
        (void)lift_and(8, lift_load(&env, esi, 0x10u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e43a8;
    edx = esi;
    eax = lift_call(&env, 0x4e4108u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e43a8;
L_4e4190:
    eax = lift_load(&env, esp, 0x0u, 4);
    edx = esi;
    eax = lift_call(&env, 0x4e43c4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esp, 0x0u, 4, eax);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e41a9;
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, esp, 0x0u, 4, eax);
L_4e41a9:
    {
        (void)lift_sub(32, ebx, 0x64u, &fl);
    }
    if (fl.cf)
        goto L_4e421c;
    if (fl.cf || fl.zf)
        goto L_4e4284;
    {
        (void)lift_sub(32, ebx, 0x6fu, &fl);
    }
    if (fl.cf)
        goto L_4e41f5;
    if (fl.cf || fl.zf)
        goto L_4e42b5;
    {
        (void)lift_sub(32, ebx, 0x73u, &fl);
    }
    if (fl.cf)
        goto L_4e41e7;
    if (fl.cf || fl.zf)
        goto L_4e4308;
    {
        (void)lift_sub(32, ebx, 0x75u, &fl);
    }
    if (fl.cf)
        goto L_4e4372;
    if (fl.cf || fl.zf)
        goto L_4e42cc;
    {
        (void)lift_sub(32, ebx, 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4e42e0;
    goto L_4e4372;
L_4e41e7:
    {
        (void)lift_sub(32, ebx, 0x70u, &fl);
    }
    if (fl.zf)
        goto L_4e42e0;
    goto L_4e4372;
L_4e41f5:
    {
        (void)lift_sub(32, ebx, 0x69u, &fl);
    }
    if (fl.cf)
        goto L_4e420e;
    if (fl.cf || fl.zf)
        goto L_4e429e;
    {
        (void)lift_sub(32, ebx, 0x6eu, &fl);
    }
    if (fl.zf)
        goto L_4e4348;
    goto L_4e4372;
L_4e420e:
    {
        (void)lift_sub(32, ebx, 0x67u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e42f7;
    goto L_4e4372;
L_4e421c:
    {
        (void)lift_sub(32, ebx, 0x47u, &fl);
    }
    if (fl.cf)
        goto L_4e425d;
    if (fl.cf || fl.zf)
        goto L_4e42f7;
    {
        (void)lift_sub(32, ebx, 0x58u, &fl);
    }
    if (fl.cf)
        goto L_4e424f;
    if (fl.cf || fl.zf)
        goto L_4e42e0;
    {
        (void)lift_sub(32, ebx, 0x5bu, &fl);
    }
    if (fl.cf)
        goto L_4e4372;
    if (fl.cf || fl.zf)
        goto L_4e4315;
    {
        (void)lift_sub(32, ebx, 0x63u, &fl);
    }
    if (fl.zf)
        goto L_4e4328;
    goto L_4e4372;
L_4e424f:
    {
        (void)lift_sub(32, ebx, 0x53u, &fl);
    }
    if (fl.zf)
        goto L_4e4304;
    goto L_4e4372;
L_4e425d:
    {
        (void)lift_sub(32, ebx, 0x43u, &fl);
    }
    if (fl.cf)
        goto L_4e4276;
    if (fl.cf || fl.zf)
        goto L_4e4324;
    {
        (void)lift_sub(32, ebx, 0x45u, &fl);
    }
    if (fl.zf)
        goto L_4e42f7;
    goto L_4e4372;
L_4e4276:
    {
        (void)lift_sub(32, ebx, 0x25u, &fl);
    }
    if (fl.zf)
        goto L_4e4357;
    goto L_4e4372;
L_4e4284:
    ecx = 0x1u;
    ebx = 0xau;
    edx = (esp + 0x4u);
    eax = esi;
    eax = lift_call(&env, 0x4e4bb0u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e4333;
L_4e429e:
    ecx = 0x1u;
    edx = (esp + 0x4u);
    eax = esi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = lift_call(&env, 0x4e4bb0u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e4333;
L_4e42b5:
    ecx = 0x1u;
    ebx = 0x8u;
    edx = (esp + 0x4u);
    eax = esi;
    eax = lift_call(&env, 0x4e4bb0u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e4333;
L_4e42cc:
    ebx = 0xau;
    edx = (esp + 0x4u);
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = lift_call(&env, 0x4e4bb0u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e4333;
L_4e42e0:
    ecx = 0x1u;
    ebx = 0x10u;
    edx = (esp + 0x4u);
    eax = esi;
    eax = lift_call(&env, 0x4e4bb0u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e4333;
L_4e42f7:
    edx = (esp + 0x4u);
    eax = esi;
    eax = lift_call(&env, 0x4e48d8u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e4333;
L_4e4304:
    {
        uint32_t r = lift_or(8, lift_load(&env, esi, 0x10u, 1), 0x20u, &fl);
        lift_store(&env, esi, 0x10u, 1, r);
    }
L_4e4308:
    edx = (esp + 0x4u);
    eax = esi;
    eax = lift_call(&env, 0x4e45f0u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e4333;
L_4e4315:
    ebx = esp;
    edx = (esp + 0x4u);
    eax = esi;
    eax = lift_call(&env, 0x4e47ecu, eax, edx, ebx, ecx, 0, esp);
    goto L_4e4333;
L_4e4324:
    {
        uint32_t r = lift_or(8, lift_load(&env, esi, 0x10u, 1), 0x20u, &fl);
        lift_store(&env, esi, 0x10u, 1, r);
    }
L_4e4328:
    edx = (esp + 0x4u);
    eax = esi;
    eax = lift_call(&env, 0x4e4508u, eax, edx, ebx, ecx, 0, esp);
L_4e4333:
    ebx = eax;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e43a8;
    {
        uint32_t r = lift_add(32, edi, ebx, &fl);
        edi = r;
    }
    {
        (void)lift_and(8, lift_load(&env, esi, 0x10u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e4372;
    {
        uint32_t a = ebp;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebp = r;
    }
    goto L_4e4372;
L_4e4348:
    edx = (esp + 0x4u);
    ebx = edi;
    eax = esi;
    eax = lift_call(&env, 0x4e4748u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e4372;
L_4e4357:
    eax = esi;
    eax = lift_call(&env, 0x4e4100u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e4371;
    {
        (void)lift_and(8, lift_load(&env, esi, 0x10u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e43a8;
    edx = esi;
    eax = lift_call(&env, 0x4e4108u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e43a8;
L_4e4371:
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
L_4e4372:
    {
        (void)lift_and(8, lift_load(&env, esi, 0x10u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e412f;
    eax = lift_load(&env, esp, 0x0u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x25u, &fl);
    }
    if (!fl.zf)
        goto L_4e43a8;
    ebx = (eax + 0x1u);
    edx = esi;
    eax = ebx;
    lift_store(&env, esp, 0x0u, 4, ebx);
    eax = lift_call(&env, 0x4e43c4u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x0u, 4, eax);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x6eu, &fl);
    }
    if (!fl.zf)
        goto L_4e43a8;
    edx = (esp + 0x4u);
    ebx = edi;
    eax = esi;
    eax = lift_call(&env, 0x4e4748u, eax, edx, ebx, ecx, 0, esp);
L_4e43a8:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4e43b9;
    {
        (void)lift_and(8, lift_load(&env, esi, 0x10u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e43b9;
    eax = 0xffffffffu;
    goto L_4e43bb;
L_4e43b9:
    eax = ebp;
L_4e43bb:
    {
        uint32_t r = lift_add(32, esp, 0x8u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e43c4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E43C4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E43C4_STACK, 0, entry);
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
    edi = edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x10u, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (edx & 0xffu), 0x1u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, edi, 0x10u, 1, (edx & 0xffu));
    edx = (edx & 0xffff00ffu) | ((((edx & 0xffu)) & 0xffu) << 8);
    lift_store(&env, edi, 0xcu, 4, 0xffffffffu);
    {
        uint32_t r = lift_and(8, ((edx >> 8) & 0xffu), 0x3u, &fl);
        edx = (edx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    lift_store(&env, edi, 0x10u, 1, ((edx >> 8) & 0xffu));
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x2au, &fl);
    }
    if (!fl.zf)
        goto L_4e43f1;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, edi, 0x10u, 1)) & 0xffu) << 8);
    {
        uint32_t r = lift_and(8, ((ebx >> 8) & 0xffu), 0xfeu, &fl);
        ebx = (ebx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, edi, 0x10u, 1, ((ebx >> 8) & 0xffu));
L_4e43f1:
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t a = (edx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    {
        (void)lift_and(8, lift_load(&env, edx, 0x507d58u, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4e442d;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
L_4e440a:
    {
        uint32_t r = lift_imul(32, edx, 0xau, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, ebx, 0x30u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, edx, ebx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x1u, 1)) & 0xffu);
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    esi = (ecx & 0xffu);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, esi, 0x507d58u, 1)) & 0xffu) << 8);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        (void)lift_and(8, ((ecx >> 8) & 0xffu), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4e440a;
    lift_store(&env, edi, 0xcu, 4, edx);
L_4e442d:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (eax + 0x1u);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x4eu, &fl);
    }
    if (!fl.zf)
        goto L_4e4444;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, edi, 0x10u, 1)) & 0xffu) << 8);
    {
        uint32_t r = lift_or(8, ((ecx >> 8) & 0xffu), 0x8u, &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    eax = edx;
    lift_store(&env, edi, 0x10u, 1, ((ecx >> 8) & 0xffu));
    goto L_4e4454;
L_4e4444:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x46u, &fl);
    }
    if (!fl.zf)
        goto L_4e4454;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edi, 0x10u, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (ecx & 0xffu), 0x4u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    eax = edx;
    lift_store(&env, edi, 0x10u, 1, (ecx & 0xffu));
L_4e4454:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ebx = (eax + 0x1u);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x68u, &fl);
    }
    if (fl.cf)
        goto L_4e4471;
    if (fl.cf || fl.zf)
        goto L_4e4482;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x6cu, &fl);
    }
    if (fl.cf)
        goto L_4e44c3;
    if (fl.cf || fl.zf)
        goto L_4e448c;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x77u, &fl);
    }
    if (fl.zf)
        goto L_4e448c;
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
    return env.failed ? 0u : eax;
L_4e4471:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x49u, &fl);
    }
    if (fl.cf)
        goto L_4e44c3;
    if (fl.cf || fl.zf)
        goto L_4e44ab;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x4cu, &fl);
    }
    if (fl.zf)
        goto L_4e449b;
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
    return env.failed ? 0u : eax;
L_4e4482:
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, edi, 0x10u, 1)) & 0xffu) << 8);
    {
        uint32_t r = lift_or(8, ((edx >> 8) & 0xffu), 0x10u, &fl);
        edx = (edx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    eax = ebx;
    goto L_4e44c0;
L_4e448c:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edi, 0x10u, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (edx & 0xffu), 0x20u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, edi, 0x10u, 1, (edx & 0xffu));
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
    return env.failed ? 0u : eax;
L_4e449b:
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edi, 0x10u, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (ecx & 0xffu), 0x40u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    eax = ebx;
    lift_store(&env, edi, 0x10u, 1, (ecx & 0xffu));
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
    return env.failed ? 0u : eax;
L_4e44ab:
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x1u, 1), 0x36u, &fl);
    }
    if (!fl.zf)
        goto L_4e44c3;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x2u, 1), 0x34u, &fl);
    }
    if (!fl.zf)
        goto L_4e44c3;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, edi, 0x10u, 1)) & 0xffu) << 8);
    {
        uint32_t r = lift_or(8, ((edx >> 8) & 0xffu), 0x40u, &fl);
        edx = (edx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    {
        uint32_t r = lift_add(32, eax, 0x3u, &fl);
        eax = r;
    }
L_4e44c0:
    lift_store(&env, edi, 0x10u, 1, ((edx >> 8) & 0xffu));
L_4e44c3:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e44c8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E44C8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E44C8_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    edx = eax;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
L_4e44d3:
    eax = edx;
    eax = lift_call(&env, 0x4e4100u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x0u, 4, eax);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    esi = (ecx & 0xffu);
    {
        (void)lift_and(8, lift_load(&env, esi, 0x507d58u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e44f1;
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    goto L_4e44d3;
L_4e44f1:
    {
        (void)lift_and(8, lift_load(&env, edx, 0x10u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e44fc;
    eax = lift_call(&env, 0x4e4108u, eax, edx, ebx, ecx, 0, esp);
L_4e44fc:
    eax = ebx;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e4fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E4FD0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E4FD0_STACK, 0, entry);
    {
        (void)lift_sub(32, eax, 0x30u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e4fde;
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e4fde;
    {
        uint32_t r = lift_sub(32, eax, 0x30u, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
L_4e4fde:
    eax = lift_call(&env, 0x4e82f0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x61u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e4ff1;
    {
        (void)lift_sub(32, eax, 0x66u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e4ff1;
    {
        uint32_t r = lift_sub(32, eax, 0x57u, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
L_4e4ff1:
    eax = 0x10u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e4ff8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E4FF8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E4FF8_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = lift_load(&env, eax, 0xcu, 4);
    ebx = (eax + 0xffffffffu);
    lift_store(&env, edx, 0xcu, 4, ebx);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e5016;
    eax = edx;
    eax = lift_call(&env, 0x4e4100u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(8, lift_load(&env, edx, 0x10u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e501b;
L_4e5016:
    eax = 0xffffffffu;
L_4e501b:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5024(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5024_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5024_STACK, 0, entry);
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
    esi = eax;
    ecx = edx;
    eax = 0x2u;
    eax = lift_call(&env, 0x4e8310u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    eax = esi;
    edx = ebx;
    eax = lift_load(&env, 0u, (eax * 4u) + 0x5096c4u, 4);
    eax = lift_call(&env, 0x4e8330u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x5129b9u;
    edx = ebx;
    eax = lift_call(&env, 0x4e8330u, eax, edx, ebx, ecx, 0, esp);
    edx = ebx;
    eax = ecx;
    eax = lift_call(&env, 0x4e8330u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xau;
    edx = ebx;
    eax = lift_call(&env, 0x4e3e00u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e506c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E506C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E506C_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    eax = lift_call(&env, lift_load(&env, 0u, 0x5096e0u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e5094;
    edx = lift_load(&env, ebx, 0x4u, 4);
    eax = lift_load(&env, ebx, 0x0u, 4);
    eax = lift_call(&env, 0x4e5024u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x0u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4e508f;
    eax = lift_call(&env, 0x4dae80u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e5094;
L_4e508f:
    eax = lift_call(&env, 0x4dae94u, eax, edx, ebx, ecx, 0, esp);
L_4e5094:
    eax = lift_load(&env, ebx, 0x18u, 4);
    edx = lift_load(&env, ebx, 0x1cu, 4);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e509c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E509C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E509C_STACK, 0, entry);
    {
        uint32_t v = ebp;
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
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = edx;
    ebp = eax;
    eax = lift_load(&env, ebp, 0x0u, 4);
    edx = lift_load(&env, ebp, 0x4u, 4);
    {
        uint32_t t = esi;
        esi = ebp;
        ebp = t;
    }
    lift_store(&env, ebp, 0x0u, 4, eax);
    lift_store(&env, ebp, 0x4u, 4, edx);
    ecx = edx;
    {
        uint32_t r = lift_and(32, ecx, 0x7ff00000u, &fl);
        ecx = r;
    }
    if (fl.zf)
        goto L_4e50c7;
    {
        (void)lift_sub(32, ecx, 0x43300000u, &fl);
    }
    if (fl.cf)
        goto L_4e50d5;
    {
        uint32_t t = ebp;
        ebp = esi;
        esi = t;
    }
L_4e50c7:
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0x4u, 4, eax);
    lift_store(&env, ebp, 0x0u, 4, eax);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
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
        ebp = v;
    }
    return env.failed ? 0u : eax;
L_4e50d5:
    edi = ecx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x14u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_sub(16, (ecx & 0xffffu), 0x3ffu, &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.cf)
        goto L_4e50c7;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    edx = 0xfff00000u;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x14u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e50fa;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x15u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(8, (ecx & 0xffu), 0x15u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    goto L_4e50fc;
L_4e50fa:
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        edx = r;
    }
L_4e50fc:
    {
        uint32_t r = lift_and(32, lift_load(&env, ebp, 0x4u, 4), edx, &fl);
        lift_store(&env, ebp, 0x4u, 4, r);
    }
    {
        uint32_t r = lift_and(32, lift_load(&env, ebp, 0x0u, 4), eax, &fl);
        lift_store(&env, ebp, 0x0u, 4, r);
    }
    {
        uint32_t a = edx;
        edx = (~a) & lift_mask(4);
    }
    {
        uint32_t a = eax;
        eax = (~a) & lift_mask(4);
    }
    ebp = esi;
    {
        uint32_t r = lift_and(32, edx, lift_load(&env, ebp, 0x4u, 4), &fl);
        edx = r;
    }
    {
        uint32_t r = lift_and(32, eax, lift_load(&env, ebp, 0x0u, 4), &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4e5177u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4e5120;
    {
        uint32_t r = lift_and(32, esi, 0x80000000u, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_or(32, edx, esi, &fl);
        edx = r;
    }
L_4e5120:
    lift_store(&env, ebp, 0x4u, 4, edx);
    lift_store(&env, ebp, 0x0u, 4, eax);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
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
        ebp = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5271(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5271_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5271_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x8u, &fl);
        esp = r;
    }
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    lift_store(&env, ebp, 0xfffffff8u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e5305;
    eax = lift_load(&env, ebp, 0xfffffffau, 4);
    {
        uint32_t r = lift_and(32, eax, 0x7ff0u, &fl);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, ebx, 0x3e80u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e52a1;
    ebx = 0x3e80u;
    goto L_4e52ae;
L_4e52a1:
    {
        (void)lift_sub(32, ebx, 0xffffc180u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e52ae;
    ebx = 0xffffc180u;
L_4e52ae:
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e52ba;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    goto L_4e530b;
L_4e52ba:
    {
        (void)lift_sub(32, eax, 0x7ffu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e52ed;
    ecx = lift_load(&env, ebp, 0xfffffffau, 4);
    eax = lift_call(&env, 0x4dae94u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e52db;
    eax = lift_load(&env, 0u, 0x51ab90u, 4);
    edx = lift_load(&env, 0u, 0x51ab94u, 4);
    goto L_4e530b;
L_4e52db:
    eax = lift_load(&env, 0u, 0x51ab90u, 4);
    edx = lift_load(&env, 0u, 0x51ab94u, 4);
    eax = lift_call(&env, 0x4dae4au, eax, edx, ebx, ecx, 0, esp);
    goto L_4e530b;
L_4e52ed:
    edx = lift_load(&env, ebp, 0xfffffffau, 4);
    {
        uint32_t r = lift_and(32, edx, 0x800fu, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    ebx = edx;
    lift_store(&env, ebp, 0xfffffffau, 2, (edx & 0xffffu));
    {
        uint32_t r = lift_or(32, ebx, eax, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xfffffffau, 2, (ebx & 0xffffu));
L_4e5305:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    edx = lift_load(&env, ebp, 0xfffffff8u, 4);
L_4e530b:
    esp = (ebp + 0xfffffffcu);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e532c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E532C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E532C_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5054a1u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e534d;
    edx = 0x4e5320u;
    ebx = 0x4e5328u;
    lift_store(&env, 0u, 0x50af08u, 4, edx);
    lift_store(&env, 0u, 0x50af0cu, 4, ebx);
L_4e534d:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x50af10u, 2)) & 0xffffu);
    eax = lift_call(&env, 0x4e83d2u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5678(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5678_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5678_STACK, 0, entry);
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
    edx = lift_load(&env, 0u, 0x5c8940u, 4);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e56a3;
    ebx = 0x5c8310u;
L_4e568d:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    eax = lift_call(&env, 0x4f1b3cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ecx = lift_load(&env, 0u, 0x5c8940u, 4);
    {
        uint32_t r = lift_add(32, ebx, 0x18u, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, esi, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e568d;
L_4e56a3:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e56a8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E56A8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E56A8_STACK, 0, entry);
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
    edx = lift_load(&env, 0u, 0x5c8944u, 4);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e56e7;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
L_4e56bc:
    eax = lift_load(&env, 0u, 0x5c8948u, 4);
    ecx = lift_load(&env, ebx, eax + 0x0u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b3cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = lift_load(&env, 0u, 0x5c8948u, 4);
    eax = lift_load(&env, ebx, eax + 0x0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edi = lift_load(&env, 0u, 0x5c8944u, 4);
    {
        uint32_t r = lift_add(32, ebx, 0x4u, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e56bc;
L_4e56e7:
    ebp = lift_load(&env, 0u, 0x5c8948u, 4);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4e56f8;
    eax = ebp;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
L_4e56f8:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e571c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E571C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E571C_STACK, 0, entry);
    eax = 0x5c81e0u;
    goto L_4e5810;
L_4e5810:
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5738(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5738_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5738_STACK, 0, entry);
    {
        uint32_t r = lift_and(32, eax, 0xfu, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x5c8200u, &fl);
        eax = r;
    }
    goto L_4e5810;
L_4e5810:
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5750_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5750_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    {
        uint32_t r = lift_and(32, eax, 0xfu, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x5c8200u, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4e5700u, eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    eax = lift_call(&env, 0x4e03fcu, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5774(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5774_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5774_STACK, 0, entry);
    eax = 0x5c8300u;
    goto L_4e5810;
L_4e5810:
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5788(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5788_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5788_STACK, 0, entry);
    eax = 0x5c81f0u;
    goto L_4e5810;
L_4e5810:
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e579c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E579C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E579C_STACK, 0, entry);
    eax = 0x5c8920u;
    goto L_4e5810;
L_4e5810:
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5808(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5808_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5808_STACK, 0, entry);
    eax = 0x5c8930u;
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5810_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5810_STACK, 0, entry);
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5838(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5838_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5838_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4f1bbcu, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, 0u, 0x507c98u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = eax;
    eax = lift_call(&env, 0x4f1cdcu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e5860;
    eax = lift_call(&env, 0x4e8400u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e586b;
L_4e5860:
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x53u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e586d;
    eax = lift_call(&env, 0x4e843cu, eax, edx, ebx, ecx, 0, esp);
L_4e586b:
    ebx = eax;
L_4e586d:
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1cb0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e587c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E587C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E587C_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e58aa;
    eax = 0x1u;
    edx = lift_load(&env, 0u, 0x509768u, 4);
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e58aa;
    ebx = lift_load(&env, 0u, 0x509768u, 4);
    lift_store(&env, eax, 0x52u, 1, 0x1u);
    lift_store(&env, eax, 0xf0u, 4, ebx);
L_4e58aa:
    eax = edx;
    eax = lift_call(&env, 0x4e8620u, eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e58b8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E58B8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E58B8_STACK, 0, entry);
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
    ebx = lift_load(&env, 0u, 0x507c98u, 4);
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e5901;
    eax = lift_call(&env, 0x4f1cd4u, eax, edx, ebx, ecx, 0, esp);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x509731u, 2)) & 0xffffu);
    ebx = eax;
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x8000u, &fl);
    }
    if (fl.cf)
        goto L_4e5901;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x50972fu, 1), 0x4u, &fl);
    }
    if (!fl.cf)
        goto L_4e5901;
L_4e58e6:
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4e5901;
    {
        (void)lift_sub(32, ebx, 0x2u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e5901;
    lift_store(&env, 0u, 0x507c98u, 4, ebx);
    eax = lift_call(&env, 0x4f1cd4u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    goto L_4e58e6;
L_4e5901:
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x507c98u, 4, ebx);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5918(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5918_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5918_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, 0u, 0x507c98u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e592a;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e592a:
    eax = lift_call(&env, 0x4e587cu, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e5967;
    edx = ebx;
    eax = lift_load(&env, eax, 0xdau, 4);
    eax = lift_call(&env, 0x4e8510u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e5953;
    eax = ebx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e5953:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x507c98u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ce0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    eax = 0x1u;
L_4e5967:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e596c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E596C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E596C_STACK, 0, entry);
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
    ebx = eax;
    edx = lift_load(&env, 0u, 0x507c98u, 4);
    {
        (void)lift_sub(32, edx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4e59bb;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1cdcu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e59bb;
    esi = lift_load(&env, eax, 0xdeu, 4);
    eax = lift_load(&env, eax, 0xdau, 4);
    eax = lift_call(&env, 0x4e8574u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, 0u, 0x507c98u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ce0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4e59bb;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e59bb;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e59bb:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e59f4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E59F4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E59F4_STACK, 0, entry);
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
    edx = 0x4e5728u;
    ebx = 0x4e5738u;
    ecx = 0x4e5748u;
    esi = 0x4e5750u;
    edi = 0x4e5710u;
    ebp = 0x4e571cu;
    eax = 0x4e5794u;
    lift_store(&env, 0u, 0x507ca0u, 4, edx);
    lift_store(&env, 0u, 0x507ca4u, 4, ebx);
    lift_store(&env, 0u, 0x507ca8u, 4, ecx);
    lift_store(&env, 0u, 0x507cacu, 4, esi);
    lift_store(&env, 0u, 0x507cb0u, 4, edi);
    lift_store(&env, 0u, 0x507cb4u, 4, ebp);
    lift_store(&env, 0u, 0x507cc8u, 4, eax);
    edx = 0x4e579cu;
    ebx = 0x4e57acu;
    ecx = 0x4e5810u;
    esi = 0x4e5700u;
    edi = 0x4e576cu;
    ebp = 0x4e5780u;
    eax = 0x4e5774u;
    lift_store(&env, 0u, 0x507cccu, 4, edx);
    lift_store(&env, 0u, 0x509748u, 4, ebx);
    lift_store(&env, 0u, 0x50974cu, 4, ecx);
    lift_store(&env, 0u, 0x509750u, 4, esi);
    lift_store(&env, 0u, 0x507cb8u, 4, edi);
    lift_store(&env, 0u, 0x507cbcu, 4, ebp);
    lift_store(&env, 0u, 0x507cc0u, 4, eax);
    edx = 0x4e5788u;
    ebx = 0x1u;
    ecx = 0x4e57a4u;
    esi = 0x4e5808u;
    edi = 0x4e59c4u;
    lift_store(&env, 0u, 0x507cc4u, 4, edx);
    eax = lift_call(&env, 0x4e55d4u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, 0u, 0x5c7b9cu, 4);
    lift_store(&env, 0u, 0x5c8910u, 4, eax);
    lift_store(&env, 0u, 0x5c8914u, 4, ebx);
    lift_store(&env, 0u, 0x507cd0u, 4, ecx);
    lift_store(&env, 0u, 0x507cd4u, 4, esi);
    eax = lift_load(&env, edx, 0xdau, 4);
    lift_store(&env, 0u, 0x507cd8u, 4, edi);
    eax = lift_call(&env, 0x4e8510u, eax, edx, ebx, ecx, 0, esp);
    ebp = lift_load(&env, 0u, 0x5c7b9cu, 4);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x507c98u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ce0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    lift_store(&env, 0u, 0x507c9cu, 4, 0x4e5838u);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5bec(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5BEC_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5BEC_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e5bf9;
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
L_4e5bf9:
    eax = ecx;
    eax = lift_call(&env, lift_load(&env, ecx, 0x10u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5cd1(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5CD1_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5CD1_STACK, 1, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x14u, &fl);
        esp = r;
    }
    esi = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51bdccu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e5d16;
L_4e5d04:
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = esi;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
L_4e5d16:
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x20u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    eax = lift_call(&env, 0x4e5c2cu, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    esi = eax;
    goto L_4e5d04;
}

uint32_t lifted_f4e636c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E636C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E636C_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = edx;
    {
        (void)lift_sub(32, ebx, 0xau, &fl);
    }
    if (!fl.zf)
        goto L_4e637e;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e637e;
    {
        uint32_t a = eax;
        uint32_t r = lift_sub(32, 0, a, &fl);
        eax = r;
    }
    lift_store(&env, edx, 0x0u, 1, 0x2du);
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
L_4e637e:
    eax = lift_call(&env, 0x4e6320u, eax, edx, ebx, ecx, 0, esp);
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e6510(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6510_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6510_STACK, 0, entry);
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
    ebp = eax;
    esi = edx;
    edi = ebx;
    eax = lift_call(&env, 0x4f1c00u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_and(32, eax, 0xffffu, &fl);
        eax = r;
    }
    {
        (void)lift_sub(16, (eax & 0xffffu), 0x8000u, &fl);
    }
    if (!fl.cf)
        goto L_4e653e;
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
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1bc8u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
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
    return env.failed ? 0u : eax;
L_4e653e:
    eax = 0x208u;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e65a0;
    {
        uint32_t v = 0x208u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1bc4u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e656e;
    eax = ebx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e656e:
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c6cu, eax, edx, ebx, ecx, 6, esp);
    esp += 24u;
    ebp = eax;
    eax = ebx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4e6592;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e6592:
    eax = esi;
    lift_store(&env, esi, (edi * 2u) + 0xfffffffeu, 2, 0x0u);
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
L_4e65a0:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e6600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6600_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6600_STACK, 0, entry);
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
    edx = eax;
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    ebx = ((eax * 2u));
    eax = ebx;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e6624;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
L_4e6624:
    eax = ecx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e66a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E66A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E66A0_STACK, 0, entry);
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
        uint32_t v = 0x512a2cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c44u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e66cc;
    {
        uint32_t v = 0x512a38u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1bdcu, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e66cc;
    eax = lift_call(&env, edx, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
L_4e66cc:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e66dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E66DC_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E66DC_STACK, 0, entry);
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
    edi = ebx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e66f1;
L_4e66e9:
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, eax, 0x1u, 1)) & 0xffu) << 8);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        (void)lift_and(8, ((ecx >> 8) & 0xffu), ((ecx >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4e66e9;
L_4e66f1:
    esi = (eax + 0x9u);
L_4e66f4:
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    lift_store(&env, eax, 0x0u, 1, (ecx & 0xffu));
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e670e;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4e6709;
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x1u, 1), 0x78u, &fl);
    }
    if (!fl.zf)
        goto L_4e6709;
    ebx = esi;
L_4e6709:
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    goto L_4e66f4;
L_4e670e:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e672e;
    eax = edi;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4e672e;
L_4e6718:
    edx = eax;
    {
        uint32_t r = lift_and(32, edx, 0xfu, &fl);
        edx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x5097f4u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_store(&env, ebx, 0x1u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e6718;
L_4e672e:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e6b2c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6B2C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6B2C_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x54u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e6b41;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    env.chain = eax;
L_4e6b41:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, eax, 0x54u, 4, 0x0u);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e6bff(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6BFF_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6BFF_STACK, 0, entry);
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
    ecx = eax;
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x3u, &fl);
        eax = r;
    }
    ebx = eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_sub(32, edx, ebx, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x509810u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (edx & 0xffu), lift_load(&env, ecx, eax + 0x0u, 1), &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e6c1d(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6C1D_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6C1D_STACK, 0, entry);
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
    ecx = edx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x3u, &fl);
        ecx = r;
    }
    ebx = ecx;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_sub(32, edx, ebx, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x509818u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, lift_load(&env, ecx, eax + 0x0u, 1), (edx & 0xffu), &fl);
        lift_store(&env, ecx, eax + 0x0u, 1, r);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e6cd4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6CD4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6CD4_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4e6cd5:
    edx = lift_load(&env, eax, 0x0u, 1);
    {
        (void)lift_sub(32, edx, 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4e6cf0;
    edx = lift_load(&env, eax, 0x1u, 1);
    {
        (void)lift_sub(32, edx, 0x25u, &fl);
    }
    if (!fl.zf)
        goto L_4e6cf0;
    eax = lift_load(&env, eax, 0x2u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    goto L_4e6cd5;
L_4e6cf0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e70d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E70D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E70D0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = lift_call(&env, 0x4e9020u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e70fb;
    {
        (void)lift_sub(32, edx, 0x824fu, &fl);
    }
    if (fl.cf)
        goto L_4e70f5;
    {
        (void)lift_sub(32, edx, 0x8258u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e70f5;
    edx = 0x1u;
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e70f5:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e70fb:
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x507d58u, 1)) & 0xffu);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_and(8, (eax & 0xffu), 0x20u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7120_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7120_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    eax = edx;
    {
        (void)lift_and(8, ((ebx >> 8) & 0xffu), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_4e7136;
    edx = ebx;
    lift_store(&env, eax, 0x1u, 1, (ebx & 0xffu));
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x8u, &fl);
        edx = r;
    }
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4e7136:
    lift_store(&env, edx, 0x0u, 1, (ebx & 0xffu));
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7140_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7140_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = lift_call(&env, 0x4e9020u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e7168;
    {
        (void)lift_sub(32, edx, 0x8140u, &fl);
    }
    if (fl.zf)
        goto L_4e7159;
    {
        (void)lift_sub(32, edx, 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4e7162;
L_4e7159:
    edx = 0x1u;
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e7162:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e7168:
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x507d58u, 1)) & 0xffu);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_and(8, (eax & 0xffu), 0x2u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7280_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7280_STACK, 0, entry);
    eax = lift_call(&env, lift_load(&env, 0u, 0x509743u, 4), eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7540_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7540_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    edx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51bfbcu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, edx);
    lift_store(&env, edx, 0x0u, 4, 0x517454u);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, edx, 0x0u, 4, 0x51c024u);
    lift_store(&env, edx, 0x4u, 4, 0x0u);
    lift_store(&env, edx, 0x10u, 4, 0x0u);
    eax = lift_load(&env, edx, 0x10u, 4);
    lift_store(&env, edx, 0xcu, 4, eax);
    lift_store(&env, edx, 0x8u, 4, eax);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = edx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7660_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7660_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4e7670;
    lift_store(&env, eax, 0x10u, 4, ebx);
L_4e7670:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e768a;
    eax = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, esi);
    lift_store(&env, ecx, 0xcu, 4, esi);
    lift_store(&env, ecx, 0x8u, 4, esi);
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
    return env.failed ? 0u : eax;
L_4e768a:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e76b3;
    ebx = ((esi * 4u));
    eax = ebx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4c9ff0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0xcu, 4, esi);
    lift_store(&env, ecx, 0x8u, 4, esi);
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
    return env.failed ? 0u : eax;
L_4e76b3:
    {
        (void)lift_sub(32, esi, lift_load(&env, ecx, 0xcu, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e76e7;
    {
        (void)lift_sub(32, esi, lift_load(&env, ecx, 0x8u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e76df;
    ebx = esi;
    eax = lift_load(&env, ecx, 0x8u, 4);
    edx = lift_load(&env, ecx, 0x4u, 4);
    {
        uint32_t r = lift_sub(32, ebx, lift_load(&env, ecx, 0x8u, 4), &fl);
        ebx = r;
    }
    eax = ((eax * 4u));
    ebx = ((ebx * 4u));
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
L_4e76df:
    lift_store(&env, ecx, 0x8u, 4, esi);
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
    return env.failed ? 0u : eax;
L_4e76e7:
    eax = lift_load(&env, ecx, 0x10u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e772b;
    eax = lift_load(&env, ecx, 0x8u, 4);
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sbb(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e7711;
    {
        (void)lift_sub(32, eax, 0x400u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e7711;
    eax = 0x400u;
    goto L_4e772b;
L_4e7711:
    eax = lift_load(&env, ecx, 0x8u, 4);
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sbb(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e772b;
    eax = 0x4u;
L_4e772b:
    ebp = lift_load(&env, ecx, 0xcu, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    {
        (void)lift_sub(32, esi, ebp, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e7736;
    ebp = esi;
L_4e7736:
    eax = ((ebp * 4u));
    eax = lift_call(&env, 0x4c9ff0u, eax, edx, ebx, ecx, 0, esp);
    ebx = lift_load(&env, ecx, 0x8u, 4);
    edx = lift_load(&env, ecx, 0x4u, 4);
    ebx = ((ebx * 4u));
    edi = eax;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
    ebx = esi;
    eax = lift_load(&env, ecx, 0x8u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, ebx, lift_load(&env, ecx, 0x8u, 4), &fl);
        ebx = r;
    }
    eax = ((eax * 4u));
    ebx = ((ebx * 4u));
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, edi);
    lift_store(&env, ecx, 0x8u, 4, esi);
    lift_store(&env, ecx, 0xcu, 4, ebp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7850_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7850_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    ebp = eax;
    ecx = 0xcu;
    edx = lift_load(&env, ebp, 0x10u, 4);
    eax = lift_load(&env, eax, 0x10u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    ebx = 0x51c06cu;
    edi = lift_load(&env, ebp, 0x14u, 4);
    esi = edx;
    {
        (void)lift_sub(32, edi, 0xf4fb7ea1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e7887;
    eax = 0xffffffffu;
    goto L_4e79f5;
L_4e7887:
    eax = lift_load(&env, ebp, 0x10u, 4);
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, edi, eax, &fl);
        edi = r;
    }
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e789f;
L_4e7897:
    {
        uint32_t r = lift_add(32, esi, 0xcu, &fl);
        esi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e7897;
L_4e789f:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e78b2;
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4e78b2:
    eax = (edi + 0x76cu);
    eax = lift_call(&env, 0x4e9060u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e78c6;
    ebx = 0x51c086u;
L_4e78c6:
    edx = (edi + 0x3u);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sbb(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = eax;
    eax = ((edi * 8u));
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    eax = 0x64u;
    edx = (edi + 0x63u);
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x0u, 4), &eax, &edx, &fl);
    edx = (edi + 0x12bu);
    {
        uint32_t r = lift_sub(32, ecx, eax, &fl);
        ecx = r;
    }
    edi = 0x190u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, ebx, (esi * 2u) + 0x0u, 2);
    edx = lift_load(&env, ebp, 0xcu, 4);
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edi = (eax + 0xffffffffu);
    edx = lift_load(&env, ebp, 0x8u, 4);
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0x4u, 4);
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    esi = lift_load(&env, ebp, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, esi, eax, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e7956;
L_4e794b:
    {
        uint32_t r = lift_add(32, esi, 0x15180u, &fl);
        esi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e794b;
L_4e7956:
    ecx = ebp;
    edx = esi;
    eax = edi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = lift_call(&env, 0x4e7a00u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4e960cu, eax, edx, ebx, ecx, 0, esp);
    ebx = lift_load(&env, 0u, 0x50b0dcu, 4);
    ecx = lift_load(&env, ebp, 0x20u, 4);
    {
        uint32_t r = lift_add(32, esi, ebx, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e797e;
    eax = ebp;
    eax = lift_call(&env, 0x4e91e0u, eax, edx, ebx, ecx, 0, esp);
L_4e797e:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x20u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e798a;
    {
        uint32_t r = lift_sub(32, esi, lift_load(&env, 0u, 0x50b0e4u, 4), &fl);
        esi = r;
    }
L_4e798a:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e7997;
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
    {
        uint32_t r = lift_add(32, esi, 0x15180u, &fl);
        esi = r;
    }
    goto L_4e798a;
L_4e7997:
    {
        (void)lift_sub(32, edi, 0x63deu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e79ae;
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4e79ae:
    if (!fl.zf)
        goto L_4e79d3;
    ebx = lift_load(&env, 0u, 0x50b0dcu, 4);
    {
        uint32_t r = lift_sub(32, esi, 0x15180u, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e79c4;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e79f3;
L_4e79c4:
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4e79d3:
    eax = (edi + 0xffff9c21u);
    edi = ((eax * 8u));
    {
        uint32_t r = lift_sub(32, edi, eax, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_add(32, edi, eax, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x7u, &fl);
        edi = r;
    }
    eax = edi;
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_sub(32, edi, eax, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_add(32, esi, edi, &fl);
        esi = r;
    }
L_4e79f3:
    eax = esi;
L_4e79f5:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7A00_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7A00_STACK, 0, entry);
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
    edi = eax;
    esi = edx;
    eax = ebx;
    {
        (void)lift_sub(32, edx, 0xa8c0u, &fl);
    }
    if (!fl.cf)
        goto L_4e7a2d;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e7a2d;
    esi = (edx + 0x15180u);
    {
        uint32_t r = lift_sub(32, esi, ebx, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    ebx = 0x15180u;
    eax = esi;
    lift_div1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, edi, eax, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
    goto L_4e7a3c;
L_4e7a2d:
    ebx = 0x15180u;
    {
        uint32_t r = lift_sub(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = esi;
    lift_div1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, edi, eax, &fl);
        edi = r;
    }
L_4e7a3c:
    ebx = 0x15180u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_div1(32, ebx, &eax, &edx, &fl);
    ebx = edx;
    esi = 0xe10u;
    eax = ebx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_div1(32, esi, &eax, &edx, &fl);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ecx, 0x8u, 4, eax);
    eax = ebx;
    lift_div1(32, esi, &eax, &edx, &fl);
    ebx = edx;
    esi = 0x3cu;
    eax = ebx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_div1(32, esi, &eax, &edx, &fl);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = ebx;
    lift_div1(32, esi, &eax, &edx, &fl);
    ebx = 0x16eu;
    eax = edi;
    lift_store(&env, ecx, 0x0u, 4, edx);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_div1(32, ebx, &eax, &edx, &fl);
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    ebx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    ebx = edi;
    {
        uint32_t r = lift_sub(32, ebx, eax, &fl);
        ebx = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e7aa3;
    eax = (edx + 0xffffffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, ebx, eax, &fl);
        ebx = r;
    }
L_4e7aa3:
    eax = (edx + 0x76cu);
    eax = lift_call(&env, 0x4e9060u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, eax, 0x16du, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.cf)
        goto L_4e7abe;
L_4e7ab7:
    {
        uint32_t r = lift_sub(32, ebx, eax, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (!fl.cf)
        goto L_4e7ab7;
L_4e7abe:
    esi = 0x51c06cu;
    lift_store(&env, ecx, 0x14u, 4, edx);
    eax = (edx + 0x76cu);
    lift_store(&env, ecx, 0x1cu, 4, ebx);
    eax = lift_call(&env, 0x4e9060u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e7add;
    esi = 0x51c086u;
L_4e7add:
    ebp = 0x1fu;
    eax = ebx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_div1(32, ebp, &eax, &edx, &fl);
    edx = lift_load(&env, esi, (eax * 2u) + 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.cf)
        goto L_4e7af3;
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
L_4e7af3:
    lift_store(&env, ecx, 0x10u, 4, eax);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, esi, (eax * 2u) + 0x0u, 2);
    {
        uint32_t r = lift_sub(32, ebx, eax, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    eax = (edi + 0x1u);
    lift_store(&env, ecx, 0xcu, 4, ebx);
    ebx = 0x7u;
    lift_div1(32, ebx, &eax, &edx, &fl);
    eax = ecx;
    lift_store(&env, ecx, 0x18u, 4, edx);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7b18(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7B18_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7B18_STACK, 0, entry);
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
    lift_store(&env, edx, 0x20u, 4, 0x0u);
    ecx = edx;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    edx = eax;
    eax = 0x63dfu;
    eax = lift_call(&env, 0x4e7a00u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7B50_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7B50_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e7b5d;
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e7b5d:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c8950u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e7b88;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x5c8961u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (edx & 0xffu), 0x1u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4e7b88;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x1u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e7b88;
    eax = 0x2u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e7b88:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7B90_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7B90_STACK, 0, entry);
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
    esi = eax;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e7ba9;
L_4e7b98:
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e7ba9;
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    lift_store(&env, eax, 0xffffffffu, 1, (ecx & 0xffu));
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e7b98;
L_4e7ba9:
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e7bd9;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e7bd9;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c8950u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e7bd9;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0xffffffffu, 1)) & 0xffu);
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x5c8961u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (edx & 0xffu), 0x1u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4e7bd9;
    lift_store(&env, eax, 0xffffffffu, 1, 0x0u);
L_4e7bd9:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e7be4;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
L_4e7be4:
    eax = esi;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7BF0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7BF0_STACK, 0, entry);
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
    edx = eax;
    {
        (void)lift_and(8, lift_load(&env, eax, 0xdu, 1), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4e7c1d;
    eax = lift_load(&env, edx, 0x10u, 4);
    eax = lift_call(&env, 0x4e0a30u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e7c1d;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, 0xdu, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (ebx & 0xffu), 0x20u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, edx, 0xdu, 1, (ebx & 0xffu));
    {
        (void)lift_and(8, (ebx & 0xffu), 0x7u, &fl);
    }
    if (!fl.zf)
        goto L_4e7c1d;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_or(8, (ecx & 0xffu), 0x2u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, edx, 0xdu, 1, (ecx & 0xffu));
L_4e7c1d:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7C30_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7C30_STACK, 0, entry);
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
    ebx = eax;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e7c44;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x507c34u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e7c58;
L_4e7c44:
    eax = 0x4u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4e7c58:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, 0u, 0x507c8cu, 4);
    eax = lift_load(&env, eax, (ebx * 4u) + 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b6cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e7c7c;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
    esi = 0xffffffffu;
L_4e7c7c:
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = esi;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7e44(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7E44_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7E44_STACK, 0, entry);
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
    ebx = eax;
    edx = 0x5c7760u;
L_4e7e4e:
    eax = lift_load(&env, edx, 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e7e79;
    ecx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4e7e5f;
    edx = eax;
    goto L_4e7e4e;
L_4e7e5f:
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, 0xcu, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (ecx & 0xffu), 0x3u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, ebx, 0xcu, 1, (ecx & 0xffu));
    ebx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, edx, 0x0u, 4, ebx);
    edx = lift_load(&env, 0u, 0x5c7764u, 4);
    lift_store(&env, 0u, 0x5c7764u, 4, eax);
    lift_store(&env, eax, 0x0u, 4, edx);
L_4e7e79:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7eb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7EB0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7EB0_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, 0u, 0x5c7760u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e7ed1;
L_4e7ec3:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4e7ed1:
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x4u, 4), &fl);
    }
    if (fl.zf)
        goto L_4e7ede;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e7ec3;
    goto L_4e7ed1;
L_4e7ede:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = 0x1u;
    eax = ebx;
    eax = lift_call(&env, 0x4e7ef4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7ef4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7EF4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7EF4_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    eax = lift_call(&env, 0x4e7fc4u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    eax = ebx;
    eax = lift_call(&env, 0x4e7e44u, eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e82d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E82D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E82D0_STACK, 0, entry);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4e82db;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4e82db;
    lift_mul1(32, ebx, &eax, &edx, &fl);
    return env.failed ? 0u : eax;
L_4e82db:
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
    lift_mul1(32, ecx, &eax, &edx, &fl);
    ecx = eax;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    lift_mul1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    lift_mul1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, edx, ecx, &fl);
        edx = r;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8310_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8310_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e831a;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e831a:
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x505234u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8330_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8330_STACK, 0, entry);
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
    ebx = eax;
    ecx = edx;
    eax = lift_load(&env, edx, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, edx, 0x8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e8352;
    eax = ecx;
    eax = lift_call(&env, 0x4e3b60u, eax, edx, ebx, ecx, 0, esp);
L_4e8352:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0xdu, 1)) & 0xffu) << 8);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4e8371;
    edx = (edx & 0xffffff00u) | ((((eax >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_and(8, (edx & 0xffu), 0xf9u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, ecx, 0xdu, 1, (edx & 0xffu));
    edx = (edx & 0xffff00ffu) | ((((edx & 0xffu)) & 0xffu) << 8);
    {
        uint32_t r = lift_or(8, ((edx >> 8) & 0xffu), 0x2u, &fl);
        edx = (edx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    edi = 0x1u;
    lift_store(&env, ecx, 0xdu, 1, ((edx >> 8) & 0xffu));
L_4e8371:
    ebp = ebx;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
L_4e8375:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e838c;
    edx = ecx;
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    eax = lift_call(&env, 0x4e3e00u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e8375;
    esi = eax;
L_4e838c:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4e83ad;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0xdu, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (eax & 0xffu), 0xf9u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, ecx, 0xdu, 1, (eax & 0xffu));
    eax = (eax & 0xffff00ffu) | ((((eax & 0xffu)) & 0xffu) << 8);
    {
        uint32_t r = lift_or(8, ((eax >> 8) & 0xffu), 0x4u, &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    lift_store(&env, ecx, 0xdu, 1, ((eax >> 8) & 0xffu));
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e83ad;
    eax = ecx;
    eax = lift_call(&env, 0x4e3ce0u, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
L_4e83ad:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e83b5;
    esi = ebx;
    {
        uint32_t r = lift_sub(32, esi, ebp, &fl);
        esi = r;
    }
L_4e83b5:
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = esi;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8400_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8400_STACK, 0, entry);
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
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4e5918u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e8420;
    edx = lift_load(&env, 0u, 0x507c98u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1cdcu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ebx = eax;
L_4e8420:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e8433;
    edx = 0x1u;
    eax = 0x512ff8u;
    eax = lift_call(&env, 0x4e628cu, eax, edx, ebx, ecx, 0, esp);
L_4e8433:
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8574(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8574_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8574_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cc8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, 0u, 0x5c8aa0u, 4);
    ecx = 0x5c8aa0u;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e85b6;
L_4e858e:
    {
        (void)lift_sub(32, ebx, lift_load(&env, edx, 0x4u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4e85ae;
    {
        (void)lift_sub(32, lift_load(&env, edx, 0xcu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e85a1;
    eax = lift_load(&env, edx, 0x8u, 4);
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
L_4e85a1:
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = edx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e85b6;
L_4e85ae:
    ecx = edx;
    edx = lift_load(&env, edx, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4e858e;
L_4e85b6:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cccu, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e85c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E85C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E85C0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cc8u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, 0u, 0x5c8aa0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e85dd;
L_4e85d0:
    edx = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, edx, 0x53u, 1, 0x1u);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e85d0;
L_4e85dd:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cccu, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8620_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8620_STACK, 0, entry);
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
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e8644;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, eax, 0xcu, 4, 0x1u);
    eax = lift_call(&env, 0x4e6630u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4f1ba0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebx, 0xdau, 4, eax);
L_4e8644:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8650_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8650_STACK, 0, entry);
L_4e85e8:
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
    edx = lift_load(&env, 0u, 0x5c8aa0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e8613;
L_4e85f5:
    ecx = lift_load(&env, edx, 0xcu, 4);
    ebx = lift_load(&env, edx, 0x0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4e8606;
    eax = lift_load(&env, edx, 0x8u, 4);
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
L_4e8606:
    eax = edx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = ebx;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e85f5;
L_4e8613:
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
    return env.failed ? 0u : eax;
    goto L_4e85e8;
}

uint32_t lifted_f4e8660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8660_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8660_STACK, 0, entry);
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
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb8u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, 0u, 0x50aefcu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e868f;
L_4e8673:
    ebx = lift_load(&env, eax, 0x0u, 4);
    ecx = lift_load(&env, eax, 0x24u, 4);
    {
        uint32_t r = lift_sub(32, ebx, 0x2cu, &fl);
        ebx = r;
    }
    esi = lift_load(&env, ecx, 0x0u, 4);
    edx = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e8689;
    eax = lift_call(&env, 0x4e86fcu, eax, edx, ebx, ecx, 0, esp);
L_4e8689:
    eax = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4e8673;
L_4e868f:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cc0u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e869c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E869C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E869C_STACK, 0, entry);
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
    ebx = eax;
    {
        uint32_t v = 0x8000u;
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
    esi = lift_load(&env, eax, 0x8u, 4);
    eax = lift_call(&env, 0x4f1cf0u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e86c0;
    eax = 0xffffffffu;
    goto L_4e86f6;
L_4e86c0:
    {
        (void)lift_sub(32, ebx, lift_load(&env, 0u, 0x50af00u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4e86e4;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4e86d4;
    lift_store(&env, 0u, 0x50af00u, 4, esi);
    goto L_4e86e4;
L_4e86d4:
    eax = lift_load(&env, 0u, 0x50aefcu, 4);
    lift_store(&env, 0u, 0x50af04u, 4, esi);
    lift_store(&env, 0u, 0x50af00u, 4, eax);
L_4e86e4:
    {
        (void)lift_sub(32, ebx, lift_load(&env, 0u, 0x5c8ad0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4e86f4;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_store(&env, 0u, 0x5c8ad0u, 4, edi);
L_4e86f4:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4e86f6:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e86fc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E86FC_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E86FC_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, eax, 0x4u, 4);
    edx = lift_load(&env, eax, 0x8u, 4);
    eax = lift_call(&env, 0x4e869cu, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8723;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e8719;
    lift_store(&env, 0u, 0x50aefcu, 4, edx);
    goto L_4e871c;
L_4e8719:
    lift_store(&env, ebx, 0x8u, 4, edx);
L_4e871c:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e8723;
    lift_store(&env, edx, 0x4u, 4, ebx);
L_4e8723:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8730_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8730_STACK, 0, entry);
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
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), lift_load(&env, edx, 0x0u, 1), &fl);
    }
    if (!fl.zf)
        goto L_4e8779;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c8950u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e8760;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebx, 0x5c8961u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (ebx & 0xffu), 0x1u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, ebx, 0xffu, &fl);
        ebx = r;
    }
    if (fl.zf)
        goto L_4e8760;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x1u, 1)) & 0xffu);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x1u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4e8765;
L_4e8760:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e8765:
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    edx = (edx & 0xffffff00u) | (((ecx & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e8779:
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_sub(32, ebx, eax, &fl);
        ebx = r;
    }
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8790_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8790_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c8950u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e87bb;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebx, 0x5c8961u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (ebx & 0xffu), 0x1u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, ebx, 0xffu, &fl);
        ebx = r;
    }
    if (fl.zf)
        goto L_4e87bb;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    lift_store(&env, eax, 0x0u, 1, (ebx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x1u, 1)) & 0xffu);
    lift_store(&env, eax, 0x1u, 1, (edx & 0xffu));
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4e87bb:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8978(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8978_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8978_STACK, 0, entry);
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
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x50af14u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e89ae;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x80u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x3u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x80000000u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x513070u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b34u, eax, edx, ebx, ecx, 7, esp);
    esp += 28u;
    lift_store(&env, 0u, 0x50af14u, 4, eax);
L_4e89ae:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x50af18u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e89da;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x80u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x3u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x40000000u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x513078u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b34u, eax, edx, ebx, ecx, 7, esp);
    esp += 28u;
    lift_store(&env, 0u, 0x50af18u, 4, eax);
L_4e89da:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e89e8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E89E8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E89E8_STACK, 0, entry);
    eax = lift_call(&env, 0x4e8978u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, 0u, 0x50af14u, 4);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e89f4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E89F4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E89F4_STACK, 0, entry);
    eax = lift_call(&env, 0x4e8978u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, 0u, 0x50af18u, 4);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8a58(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8A58_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8A58_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    {
        (void)lift_sub(32, eax, 0x7u, &fl);
    }
    if (fl.zf)
        goto L_4e8a65;
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4e8a6e;
L_4e8a65:
    eax = lift_load(&env, 0u, (edx * 8u) + 0x50af1cu, 4);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e8a6e:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, (edx * 8u) + 0x58u, 4);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8a7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8A7C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8A7C_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    {
        (void)lift_sub(32, eax, 0x7u, &fl);
    }
    if (fl.zf)
        goto L_4e8a89;
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4e8a92;
L_4e8a89:
    eax = lift_load(&env, 0u, (edx * 8u) + 0x50af20u, 4);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e8a92:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, (edx * 8u) + 0x5cu, 4);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8AA0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8AA0_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    eax = lift_call(&env, 0x4e8a7cu, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8ab5;
    eax = ebx;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4e8ab5:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8abc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8ABC_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8ABC_STACK, 1, entry);
    eax = lift_load(&env, esp, 0x4u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e8ace;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e8aed;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
L_4e8ace:
    eax = 0x4u;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8ae1;
    return env.failed ? 0u : eax;
L_4e8ae1:
    eax = 0x4u;
    eax = lift_call(&env, 0x4e8cc8u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e8b0a;
L_4e8aed:
    eax = 0x7u;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8b00;
    return env.failed ? 0u : eax;
L_4e8b00:
    eax = 0x7u;
    eax = lift_call(&env, 0x4e8cc8u, eax, edx, ebx, ecx, 0, esp);
L_4e8b0a:
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e8b14;
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4e8b19;
L_4e8b14:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
L_4e8b19:
    eax = 0x1u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8b24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8B24_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8B24_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x4u;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    eax = 0x7u;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e8b45;
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4e8b4f;
L_4e8b45:
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e8b56;
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4e8b56;
L_4e8b4f:
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e8b56:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8d80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8D80_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8D80_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4e8b24u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e8dad;
    eax = lift_call(&env, 0x4e8b8cu, eax, edx, ebx, ecx, 0, esp);
    edx = 0x2u;
    eax = 0x4u;
    eax = lift_call(&env, 0x4e8a10u, eax, edx, ebx, ecx, 0, esp);
    edx = 0x2u;
    eax = 0x7u;
    eax = lift_call(&env, 0x4e8a10u, eax, edx, ebx, ecx, 0, esp);
L_4e8dad:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8dcb(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8DCB_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8DCB_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x1cu, &fl);
        esp = r;
    }
    ecx = eax;
    ebp = lift_load(&env, eax, 0x4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x25u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (eax & 0xffu), 0x1u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    eax = (eax & 0xffu);
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = (ebp + 0x4u);
    lift_store(&env, esp, 0xcu, 4, eax);
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x4u, 4, ebx);
    {
        uint32_t r = lift_add(32, ebx, eax, &fl);
        ebx = r;
    }
    lift_store(&env, esp, 0x14u, 4, 0x0u);
    lift_store(&env, esp, 0x0u, 4, ebx);
L_4e8e00:
    eax = lift_load(&env, esp, 0x4u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x0u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4e8e65;
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esp, 0x18u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e8e30;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
L_4e8e17:
    eax = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, esp, 0x10u, 4, eax);
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0x0u, 4), &fl);
    }
    if (fl.cf)
        goto L_4e8e43;
    {
        uint32_t r = lift_add(32, lift_load(&env, esp, 0x4u, 4), 0x4u, &fl);
        lift_store(&env, esp, 0x4u, 4, r);
    }
    lift_store(&env, esp, 0x14u, 4, eax);
    goto L_4e8e00;
L_4e8e30:
    eax = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
L_4e8e35:
    {
        uint32_t r = lift_add(32, esp, 0x1cu, &fl);
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
    return env.failed ? 0u : eax;
L_4e8e3d:
    {
        uint32_t r = lift_add(32, esi, 0x8u, &fl);
        esi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    goto L_4e8e17;
L_4e8e43:
    eax = lift_load(&env, esp, 0xcu, 4);
    {
        uint32_t r = lift_add(32, eax, esi, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x14u, 4, eax);
    ebx = lift_load(&env, esp, 0x8u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_load(&env, esp, 0x18u, 4);
    eax = lift_call(&env, 0x4e3846u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e8e3d;
    eax = lift_load(&env, esp, 0x10u, 4);
    goto L_4e8e35;
L_4e8e65:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    goto L_4e8e35;
}

uint32_t lifted_f4e8e69(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8E69_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8E69_STACK, 0, entry);
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
    esi = eax;
    ecx = edx;
    ebx = (edx + 0x8u);
    edx = lift_load(&env, edx, 0x4u, 4);
    eax = lift_call(&env, 0x4e8dcbu, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8e90;
L_4e8e7f:
    eax = 0x1u;
L_4e8e84:
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8e9b;
L_4e8e8a:
    eax = edx;
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
    return env.failed ? 0u : eax;
L_4e8e90:
    {
        (void)lift_sub(32, lift_load(&env, ecx, (eax * 4u) + 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e8e7f;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    goto L_4e8e84;
L_4e8e9b:
    lift_store(&env, esi, 0x18u, 4, ecx);
    goto L_4e8e8a;
}

uint32_t lifted_f4e8ea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8EA0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8EA0_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    ebx = (edx + 0x14u);
    edx = lift_load(&env, edx, 0x10u, 4);
    eax = lift_call(&env, 0x4e8dcbu, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8eba;
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
    return env.failed ? 0u : eax;
L_4e8eba:
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, ecx, 0x18u, 4, esi);
    lift_store(&env, ecx, 0x1cu, 4, eax);
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8ff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8FF0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8FF0_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
L_4e8ff6:
    eax = edx;
    eax = lift_call(&env, 0x4e7b50u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e900d;
    eax = edx;
    eax = lift_call(&env, 0x4e3a90u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    edx = eax;
    goto L_4e8ff6;
L_4e900d:
    eax = ebx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9020_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9020_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c8950u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e905b;
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x8u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x5c8961u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (edx & 0xffu), 0x1u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4e905b;
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4ea310u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e905b;
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e905b:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9060_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9060_STACK, 0, entry);
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
    ebx = eax;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4e9096;
    ecx = 0x64u;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_div1(32, ecx, &eax, &edx, &fl);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e9080;
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
L_4e9080:
    ecx = 0x190u;
    eax = ebx;
    lift_div1(32, ecx, &eax, &edx, &fl);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4e9096;
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
L_4e9096:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9194(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9194_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9194_STACK, 0, entry);
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
    ecx = edx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x20u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e91ba;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x20u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e91ba;
    esi = lift_load(&env, eax, 0x10u, 4);
    edi = lift_load(&env, ecx, 0x10u, 4);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e91b8;
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
L_4e91b8:
    if (fl.sf != fl.of)
        goto L_4e91d9;
L_4e91ba:
    edx = ebx;
    eax = lift_call(&env, 0x4e909cu, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
    edx = ebx;
    eax = ecx;
    eax = lift_call(&env, 0x4e909cu, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e91d9;
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
L_4e91d9:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e91e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E91E0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E91E0_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x1cu, &fl);
        esp = r;
    }
    ecx = eax;
    eax = lift_load(&env, 0u, 0x50b0d8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e948c;
    edx = 0x50afacu;
    eax = 0x50af88u;
    ebx = lift_load(&env, ecx, 0x14u, 4);
    eax = lift_call(&env, 0x4e9194u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x14u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9222;
    edi = 0x50afacu;
    ebx = 0x50af88u;
    goto L_4e922c;
L_4e9222:
    edi = 0x50af88u;
    ebx = 0x50afacu;
L_4e922c:
    eax = lift_load(&env, ecx, 0x14u, 4);
    {
        uint32_t r = lift_add(32, eax, 0x76cu, &fl);
        eax = r;
    }
    ebp = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, 0x4e9060u, eax, edx, ebx, ecx, 0, esp);
    edx = ((ebp * 2u));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9255;
    eax = lift_load(&env, edx, 0x51c086u, 4);
    edx = lift_load(&env, edx, 0x51c084u, 4);
    goto L_4e9261;
L_4e9255:
    eax = lift_load(&env, edx, 0x51c06cu, 4);
    edx = lift_load(&env, edx, 0x51c06au, 4);
L_4e9261:
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x10u, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_load(&env, edi, 0x20u, 4);
    lift_store(&env, esp, 0x4u, 4, edx);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e932f;
    edx = lift_load(&env, edi, 0x10u, 4);
    {
        (void)lift_sub(32, ebp, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e928f;
    esi = 0x1u;
    goto L_4e9364;
L_4e928f:
    if (!fl.zf)
        goto L_4e9364;
    edx = lift_load(&env, ecx, 0x18u, 4);
    eax = lift_load(&env, edi, 0x18u, 4);
    {
        uint32_t r = lift_add(32, edx, 0x7u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x18u, 4, 0x7u);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x18u, 4), &eax, &edx, &fl);
    eax = lift_load(&env, ecx, 0xcu, 4);
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    edx = lift_load(&env, ecx, 0x18u, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        uint32_t r = lift_add(32, edx, 0x6u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, edx, lift_load(&env, edi, 0x18u, 4), &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x18u, 4, 0x7u);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x18u, 4), &eax, &edx, &fl);
    eax = lift_load(&env, ecx, 0xcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    edx = lift_load(&env, edi, 0xcu, 4);
    lift_store(&env, esp, 0xcu, 4, eax);
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_4e930b;
    eax = lift_load(&env, esp, 0x10u, 4);
    edx = lift_load(&env, esp, 0x8u, 4);
    {
        uint32_t r = lift_sub(32, eax, 0x7u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e9364;
    edx = lift_load(&env, esp, 0xcu, 4);
    esi = 0x1u;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e9364;
    goto L_4e936b;
L_4e930b:
    eax = (edx + 0xffffffffu);
    edx = ((eax * 8u));
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    eax = (edx + 0x1u);
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x8u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e9364;
    edx = lift_load(&env, esp, 0xcu, 4);
    esi = 0x1u;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e9364;
    goto L_4e936b;
L_4e932f:
    edx = lift_load(&env, edi, 0x1cu, 4);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4e9356;
    eax = lift_load(&env, ecx, 0x14u, 4);
    {
        uint32_t r = lift_add(32, eax, 0x76cu, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4e9060u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9355;
    eax = lift_load(&env, 0u, 0x51c06eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e9355;
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
L_4e9355:
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
L_4e9356:
    eax = lift_load(&env, ecx, 0x1cu, 4);
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e9364;
    esi = 0x1u;
    if (fl.zf)
        goto L_4e936b;
L_4e9364:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e9381;
L_4e936b:
    edx = edi;
    eax = ecx;
    eax = lift_call(&env, 0x4e949cu, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    esi = eax;
    {
        uint32_t r = lift_and(32, esi, 0xffu, &fl);
        esi = r;
    }
L_4e9381:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e9398;
    eax = lift_load(&env, esp, 0x14u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e948c;
    esi = eax;
    goto L_4e948c;
L_4e9398:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edi = lift_load(&env, ebx, 0x20u, 4);
    lift_store(&env, esp, 0x0u, 4, edx);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4e9435;
    edi = lift_load(&env, ebx, 0x10u, 4);
    {
        (void)lift_sub(32, ebp, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e93b6;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    goto L_4e946d;
L_4e93b6:
    if (!fl.zf)
        goto L_4e946d;
    edx = lift_load(&env, ecx, 0x18u, 4);
    edi = lift_load(&env, ebx, 0x18u, 4);
    {
        uint32_t r = lift_add(32, edx, 0x7u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, edx, edi, &fl);
        edx = r;
    }
    edi = 0x7u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    ebp = lift_load(&env, ecx, 0xcu, 4);
    {
        uint32_t r = lift_sub(32, ebp, edx, &fl);
        ebp = r;
    }
    edx = lift_load(&env, ecx, 0x18u, 4);
    eax = lift_load(&env, ebx, 0x18u, 4);
    {
        uint32_t r = lift_add(32, edx, 0x6u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    eax = lift_load(&env, ecx, 0xcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebx, 0xcu, 4);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_4e9417;
    edx = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t r = lift_sub(32, edx, edi, &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, ebp, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e940e;
    esi = 0x1u;
    goto L_4e946d;
L_4e940e:
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e946d;
    goto L_4e9473;
L_4e9417:
    edi = (edx + 0xffffffffu);
    edx = ((edi * 8u));
    {
        uint32_t r = lift_sub(32, edx, edi, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    {
        (void)lift_sub(32, ebp, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e942f;
    esi = 0x1u;
    goto L_4e946d;
L_4e942f:
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e946d;
    goto L_4e9473;
L_4e9435:
    ebp = lift_load(&env, ebx, 0x20u, 4);
    edi = lift_load(&env, ebx, 0x1cu, 4);
    {
        (void)lift_sub(32, ebp, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4e9460;
    eax = lift_load(&env, ecx, 0x14u, 4);
    {
        uint32_t r = lift_add(32, eax, 0x76cu, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4e9060u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e945f;
    eax = lift_load(&env, 0u, 0x51c06eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e945f;
    {
        uint32_t r = lift_add(32, edi, ebp, &fl);
        edi = r;
    }
L_4e945f:
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
L_4e9460:
    eax = lift_load(&env, ecx, 0x1cu, 4);
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e946d;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9473;
L_4e946d:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e947e;
L_4e9473:
    edx = ebx;
    eax = ecx;
    eax = lift_call(&env, 0x4e949cu, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
L_4e947e:
    ebp = lift_load(&env, esp, 0x14u, 4);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4e948c;
    eax = ebp;
    {
        uint32_t r = lift_sub(32, eax, esi, &fl);
        eax = r;
    }
    esi = eax;
L_4e948c:
    eax = esi;
    lift_store(&env, ecx, 0x20u, 4, esi);
    {
        uint32_t r = lift_add(32, esp, 0x1cu, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e949c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E949C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E949C_STACK, 0, entry);
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
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x8u, 4);
    esi = lift_load(&env, edx, 0x8u, 4);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e94c0;
    if (!fl.zf)
        goto L_4e94c5;
    ecx = lift_load(&env, eax, 0x4u, 4);
    ebp = lift_load(&env, edx, 0x4u, 4);
    {
        (void)lift_sub(32, ecx, ebp, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e94c0;
    if (!fl.zf)
        goto L_4e94c5;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x0u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e94c5;
L_4e94c0:
    ebx = 0x1u;
L_4e94c5:
    eax = ebx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9670_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9670_STACK, 0, entry);
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
    ecx = edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x30u, &fl);
    }
    if (fl.cf)
        goto L_4e9696;
L_4e967d:
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x39u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e9696;
    {
        uint32_t r = lift_imul(32, edx, 0xau, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, edx, ebx, &fl);
        edx = r;
    }
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, eax, 0x0u, 1)) & 0xffu) << 8);
    {
        uint32_t r = lift_sub(32, edx, 0x30u, &fl);
        edx = r;
    }
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), 0x30u, &fl);
    }
    if (!fl.cf)
        goto L_4e967d;
L_4e9696:
    lift_store(&env, ecx, 0x0u, 4, edx);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9980_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9980_STACK, 0, entry);
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
    {
        uint32_t r = lift_xor(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9a28;
    ecx = (eax + 0xbu);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.cf)
        goto L_4e9a28;
    edi = ebx;
    {
        uint32_t r = lift_and(8, (ecx & 0xffu), 0xf8u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    eax = lift_load(&env, ebx, 0x14u, 4);
    {
        (void)lift_sub(32, ecx, 0x10u, &fl);
    }
    if (!fl.cf)
        goto L_4e99ab;
    ecx = 0x10u;
L_4e99ab:
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e9a28;
    ebx = lift_load(&env, edi, 0x10u, 4);
    eax = lift_load(&env, edi, 0xcu, 4);
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e99c2;
    eax = lift_load(&env, edi, 0x28u, 4);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
L_4e99c2:
    esi = (edi + 0x20u);
L_4e99c5:
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e99dd;
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e99d1;
    ebx = edx;
L_4e99d1:
    eax = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e99c5;
    lift_store(&env, edi, 0x14u, 4, ebx);
    goto L_4e9a28;
L_4e99dd:
    lift_store(&env, edi, 0x10u, 4, ebx);
    ebx = lift_load(&env, edi, 0x18u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    {
        uint32_t r = lift_sub(32, edx, ecx, &fl);
        edx = r;
    }
    lift_store(&env, edi, 0x18u, 4, ebx);
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.cf)
        goto L_4e9a0c;
    ebx = (eax + ecx);
    lift_store(&env, edi, 0xcu, 4, ebx);
    lift_store(&env, ebx, 0x0u, 4, edx);
    lift_store(&env, eax, 0x0u, 4, ecx);
    ecx = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ebx, 0x4u, 4, ecx);
    edx = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ebx, 0x8u, 4, edx);
    lift_store(&env, ecx, 0x8u, 4, ebx);
    lift_store(&env, edx, 0x4u, 4, ebx);
    goto L_4e9a1e;
L_4e9a0c:
    {
        uint32_t a = lift_load(&env, edi, 0x1cu, 4);
        uint32_t r = lift_dec(32, a, &fl, 1);
        lift_store(&env, edi, 0x1cu, 4, r);
    }
    edx = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, edi, 0xcu, 4, edx);
    ebx = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, edx, 0x8u, 4, ebx);
    lift_store(&env, ebx, 0x4u, 4, edx);
L_4e9a1e:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (edx & 0xffu), 0x1u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    ebp = (eax + 0x4u);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
L_4e9a28:
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
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9c94(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9C94_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9C94_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = lift_call(&env, 0x4e8660u, eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    eax = lift_call(&env, 0x4e9bd8u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9ca8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9CA8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9CA8_STACK, 0, entry);
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
    edx = eax;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t r = lift_add(32, eax, 0x7u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_and(8, (eax & 0xffu), 0xf8u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9cf4;
    lift_store(&env, edx, 0x0u, 4, eax);
    {
        uint32_t r = lift_add(32, eax, 0x3cu, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x0u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4e9cc5;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e9cc5:
    ecx = lift_load(&env, 0u, 0x50b218u, 4);
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.cf)
        goto L_4e9cd3;
    eax = ecx;
    {
        uint32_t r = lift_and(8, (eax & 0xffu), 0xfeu, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
L_4e9cd3:
    lift_store(&env, edx, 0x0u, 4, eax);
    {
        uint32_t r = lift_add(32, eax, 0xfffu, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x0u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4e9ce3;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e9ce3:
    {
        uint32_t r = lift_xor(8, (eax & 0xffu), (eax & 0xffu), &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(8, ((eax >> 8) & 0xffu), 0xf0u, &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    lift_store(&env, edx, 0x0u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
L_4e9cf4:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9D10_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9D10_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4f1b98u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9F00_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9F00_STACK, 0, entry);
    goto L_4ea520;
L_4ea520:
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
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ea536;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
L_4ea536:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea13c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA13C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA13C_STACK, 0, entry);
    eax = lift_call(&env, lift_load(&env, 0u, 0x50b208u, 4), eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea144(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA144_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA144_STACK, 0, entry);
    eax = lift_call(&env, lift_load(&env, 0u, 0x50b20cu, 4), eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea2a8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA2A8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA2A8_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0xffu;
    eax = 0x5130c4u;
    eax = lift_call(&env, 0x4e628cu, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA410_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA410_STACK, 0, entry);
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
    ebx = edx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ba8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ea429;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
L_4ea429:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ea43f;
    {
        (void)lift_and(8, (eax & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4ea43f;
    eax = 0x5u;
    eax = lift_call(&env, 0x4e081cu, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
L_4ea43f:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA450_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA450_STACK, 0, entry);
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
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c64u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ea465;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
L_4ea465:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA540_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA540_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x10u, &fl);
        esp = r;
    }
    lift_store(&env, esp, 0xcu, 4, eax);
    lift_store(&env, esp, 0x4u, 4, edx);
    esi = ebx;
    lift_store(&env, esp, 0x8u, 4, ecx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4ea55a;
    lift_store(&env, edx, 0x0u, 4, eax);
L_4ea55a:
    edx = lift_load(&env, esp, 0xcu, 4);
L_4ea55e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        (void)lift_and(8, lift_load(&env, eax, 0x507d58u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ea573;
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    goto L_4ea55e;
L_4ea573:
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, edx, 0x0u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2bu, &fl);
    }
    if (fl.zf)
        goto L_4ea57f;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ea580;
L_4ea57f:
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
L_4ea580:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4ea5b0;
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4ea59d;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x1u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4ea596;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x58u, &fl);
    }
    if (!fl.zf)
        goto L_4ea59d;
L_4ea596:
    esi = 0x10u;
    goto L_4ea5d0;
L_4ea59d:
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4ea5a9;
    esi = 0x8u;
    goto L_4ea5e5;
L_4ea5a9:
    esi = 0xau;
    goto L_4ea5e5;
L_4ea5b0:
    {
        (void)lift_sub(32, esi, 0x2u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ea5ba;
    {
        (void)lift_sub(32, esi, 0x24u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ea5cb;
L_4ea5ba:
    eax = 0xdu;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    goto L_4ea68c;
L_4ea5cb:
    {
        (void)lift_sub(32, esi, 0x10u, &fl);
    }
    if (!fl.zf)
        goto L_4ea5e5;
L_4ea5d0:
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4ea5e5;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, edx, 0x1u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4ea5e2;
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), 0x58u, &fl);
    }
    if (!fl.zf)
        goto L_4ea5e5;
L_4ea5e2:
    {
        uint32_t r = lift_add(32, edx, 0x2u, &fl);
        edx = r;
    }
L_4ea5e5:
    lift_store(&env, esp, 0x0u, 4, edx);
    ebp = ((esi * 4u));
    {
        uint32_t r = lift_xor(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
L_4ea5f3:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    eax = lift_call(&env, 0x4ea6b0u, eax, edx, ebx, ecx, 0, esp);
    edi = eax;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ea61c;
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0x50b214u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ea60c;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
L_4ea60c:
    eax = ebx;
    {
        uint32_t r = lift_imul(32, ebx, esi, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, ebx, edi, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (!fl.cf)
        goto L_4ea619;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
L_4ea619:
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    goto L_4ea5f3;
L_4ea61c:
    {
        (void)lift_sub(32, edx, lift_load(&env, esp, 0x0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4ea625;
    edx = lift_load(&env, esp, 0xcu, 4);
L_4ea625:
    edi = lift_load(&env, esp, 0x4u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4ea62f;
    lift_store(&env, edi, 0x0u, 4, edx);
L_4ea62f:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4ea645;
    {
        (void)lift_sub(32, ebx, 0x80000000u, &fl);
    }
    if (fl.cf)
        goto L_4ea645;
    if (!fl.zf)
        goto L_4ea649;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ea649;
L_4ea645:
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4ea683;
L_4ea649:
    eax = 0xeu;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ea666;
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4ea666:
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ea677;
    eax = 0x80000000u;
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
    return env.failed ? 0u : eax;
L_4ea677:
    eax = 0x7fffffffu;
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
    return env.failed ? 0u : eax;
L_4ea683:
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ea68a;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sub(32, 0, a, &fl);
        ebx = r;
    }
L_4ea68a:
    eax = ebx;
L_4ea68c:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea6a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA6A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA6A0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x1u;
    eax = lift_call(&env, 0x4ea540u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea6b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA6B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA6B0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(8, (eax & 0xffu), 0x30u, &fl);
    }
    if (fl.cf)
        goto L_4ea6c3;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x39u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea6c3;
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, 0x30u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4ea6c3:
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4e82f0u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x61u, &fl);
    }
    if (fl.cf)
        goto L_4ea6e0;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x69u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea6e0;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_sub(32, eax, 0x57u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4ea6e0:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6au, &fl);
    }
    if (fl.cf)
        goto L_4ea6f2;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x72u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea6f2;
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, 0x57u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4ea6f2:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x73u, &fl);
    }
    if (fl.cf)
        goto L_4ea704;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x7au, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea704;
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, 0x57u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4ea704:
    eax = 0x25u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eaa7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EAA7C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EAA7C_STACK, 0, entry);
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
    edi = eax;
    ebp = edx;
    esi = lift_load(&env, 0u, 0x5c81d4u, 4);
    goto L_4eab5b;
L_4eaa90:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, edi, 0x0u, 1)) & 0xffu) << 8);
    ebx = edi;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4eab58;
L_4eaa9c:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    eax = lift_call(&env, 0x4dabb0u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    eax = lift_call(&env, 0x4dabb0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (!fl.zf)
        goto L_4eab58;
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x3du, &fl);
    }
    if (!fl.zf)
        goto L_4eab4b;
    edx = lift_load(&env, 0u, 0x5c81d4u, 4);
    edi = esi;
    {
        uint32_t r = lift_sub(32, edi, edx, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        edi = r;
    }
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4eab42;
    edx = lift_load(&env, esi, 0x0u, 4);
    ecx = esi;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4eaaed;
L_4eaade:
    eax = lift_load(&env, ecx, 0x4u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    ebx = lift_load(&env, ecx, 0x4u, 4);
    {
        uint32_t r = lift_add(32, ecx, 0x4u, &fl);
        ecx = r;
    }
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4eaade;
L_4eaaed:
    esi = lift_load(&env, 0u, 0x5c81d0u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eab3a;
    eax = esi;
    {
        (void)lift_sub(8, lift_load(&env, edi, eax + 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4eab06;
    eax = edx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
L_4eab06:
    ebp = lift_load(&env, 0u, 0x5c81d4u, 4);
    esi = ecx;
    {
        uint32_t r = lift_sub(32, esi, ebp, &fl);
        esi = r;
    }
    edx = lift_load(&env, 0u, 0x5c81d0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        esi = r;
    }
    eax = ecx;
    ebx = esi;
    eax = lift_call(&env, 0x4e1140u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, 0u, 0x5c81d0u, 4, ecx);
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4eab3a;
    eax = (edi + ecx);
L_4eab2f:
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, eax, 0xffffffffu, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4eab2f;
L_4eab3a:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4eab42:
    eax = (edi + 0x1u);
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
    return env.failed ? 0u : eax;
L_4eab4b:
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebx, 0x1u, 1)) & 0xffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4eaa9c;
L_4eab58:
    {
        uint32_t r = lift_add(32, esi, 0x4u, &fl);
        esi = r;
    }
L_4eab5b:
    edx = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4eaa90;
    eax = lift_load(&env, 0u, 0x5c81d4u, 4);
    {
        uint32_t r = lift_sub(32, eax, esi, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eada0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EADA0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EADA0_STACK, 0, entry);
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
    esi = eax;
    ecx = edx;
    ebp = ebx;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4eade8;
L_4eadb0:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4eae0e;
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4eadd1;
    ebx = 0x2u;
    edx = ecx;
    eax = esi;
    eax = lift_call(&env, 0x4e8230u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4eadd8;
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
    return env.failed ? 0u : eax;
L_4eadd1:
    lift_store(&env, esi, 0x0u, 2, 0x0u);
    goto L_4eae0e;
L_4eadd8:
    eax = ecx;
    {
        uint32_t a = ebp;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebp = r;
    }
    eax = lift_call(&env, 0x4e3a90u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, esi, 0x2u, &fl);
        esi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    ecx = eax;
    goto L_4eadb0;
L_4eade8:
    esi = 0x2u;
L_4eaded:
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4eae0e;
    ebx = esi;
    edx = ecx;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4e8230u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4eae10;
    eax = ecx;
    eax = lift_call(&env, 0x4e3a90u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    ecx = eax;
    goto L_4eaded;
L_4eae0e:
    eax = edi;
L_4eae10:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB140_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB140_STACK, 0, entry);
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
    edi = eax;
    ebp = edx;
    esi = lift_load(&env, 0u, 0x5c81d8u, 4);
    goto L_4eb22b;
L_4eb154:
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, edi, 0x0u, 2)) & 0xffffu);
    ebx = edi;
    {
        (void)lift_and(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4eb228;
L_4eb162:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    eax = lift_call(&env, 0x4eb400u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x0u, 2)) & 0xffffu);
    eax = lift_call(&env, 0x4eb400u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(16, (ecx & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4eb228;
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x0u, 2), 0x3du, &fl);
    }
    if (!fl.zf)
        goto L_4eb215;
    edx = lift_load(&env, 0u, 0x5c81d8u, 4);
    edi = esi;
    {
        uint32_t r = lift_sub(32, edi, edx, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        edi = r;
    }
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4eb20c;
    edx = lift_load(&env, esi, 0x0u, 4);
    ecx = esi;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4eb1b7;
L_4eb1a8:
    eax = lift_load(&env, ecx, 0x4u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    ebx = lift_load(&env, ecx, 0x4u, 4);
    {
        uint32_t r = lift_add(32, ecx, 0x4u, &fl);
        ecx = r;
    }
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4eb1a8;
L_4eb1b7:
    esi = lift_load(&env, 0u, 0x5c81d0u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb204;
    eax = esi;
    {
        (void)lift_sub(8, lift_load(&env, edi, eax + 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4eb1d0;
    eax = edx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
L_4eb1d0:
    ebp = lift_load(&env, 0u, 0x5c81d8u, 4);
    esi = ecx;
    {
        uint32_t r = lift_sub(32, esi, ebp, &fl);
        esi = r;
    }
    edx = lift_load(&env, 0u, 0x5c81d0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        esi = r;
    }
    eax = ecx;
    ebx = esi;
    eax = lift_call(&env, 0x4e1140u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, 0u, 0x5c81d0u, 4, ecx);
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4eb204;
    eax = (edi + ecx);
L_4eb1f9:
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, eax, 0xffffffffu, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4eb1f9;
L_4eb204:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4eb20c:
    eax = (edi + 0x1u);
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
    return env.failed ? 0u : eax;
L_4eb215:
    {
        uint32_t r = lift_add(32, edx, 0x2u, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x2u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, ebx, 0x2u, &fl);
        ebx = r;
    }
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4eb162;
L_4eb228:
    {
        uint32_t r = lift_add(32, esi, 0x4u, &fl);
        esi = r;
    }
L_4eb22b:
    edx = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4eb154;
    eax = lift_load(&env, 0u, 0x5c81d8u, 4);
    {
        uint32_t r = lift_sub(32, eax, esi, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB250_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB250_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = lift_call(&env, 0x4eb410u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4eb25f;
    {
        uint32_t r = lift_sub(32, edx, 0x21u, &fl);
        edx = r;
    }
L_4eb25f:
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB270_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB270_STACK, 0, entry);
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
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    ebx = edx;
    {
        (void)lift_sub(16, (edx & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4eb293;
L_4eb27d:
    edx = eax;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_and(16, (edi & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4eb291;
    {
        (void)lift_sub(16, (ebx & 0xffffu), lift_load(&env, eax, 0x0u, 2), &fl);
    }
    if (fl.zf)
        goto L_4eb293;
    goto L_4eb27d;
L_4eb291:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4eb293:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb2a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB2A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB2A0_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    lift_store(&env, esp, 0x0u, 4, eax);
    edi = edx;
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x509731u, 2), 0x8000u, &fl);
    }
    if (!fl.cf)
        goto L_4eb2c6;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c98u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    goto L_4eb389;
L_4eb2c6:
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    ecx = (eax + 0x1u);
    eax = ecx;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    ebp = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4eb389;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4eb2eb;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    goto L_4eb316;
L_4eb2eb:
    eax = edi;
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    ecx = (eax + 0x1u);
    eax = ecx;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4eb316;
    eax = edx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
    return env.failed ? 0u : eax;
L_4eb316:
    edx = lift_load(&env, esp, 0x0u, 4);
    ebx = ecx;
    eax = ebp;
    eax = lift_call(&env, 0x4ea350u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4eb344;
    eax = ebp;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb339;
    eax = esi;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
L_4eb339:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
    return env.failed ? 0u : eax;
L_4eb344:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb36a;
    ebx = ecx;
    edx = edi;
    eax = esi;
    eax = lift_call(&env, 0x4ea350u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4eb36a;
    eax = esi;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
    return env.failed ? 0u : eax;
L_4eb36a:
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c94u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    edx = eax;
    eax = ebp;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb387;
    eax = esi;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
L_4eb387:
    eax = edx;
L_4eb389:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB3A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB3A0_STACK, 0, entry);
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
    esi = lift_load(&env, 0u, 0x5c81d4u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb3ef;
L_4eb3ae:
    edx = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t r = lift_add(32, esi, 0x4u, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4eb3ef;
    eax = edx;
    eax = lift_call(&env, 0x4e8ff0u, eax, edx, ebx, ecx, 0, esp);
    ebx = (eax + 0x1u);
    eax = ((ebx * 2u));
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4eb3ae;
    eax = lift_call(&env, 0x4eada0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4eb3e6;
    eax = ecx;
    eax = lift_call(&env, 0x4eafb8u, eax, edx, ebx, ecx, 0, esp);
    goto L_4eb3ae;
L_4eb3e6:
    eax = ecx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    goto L_4eb3ae;
L_4eb3ef:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb4d4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB4D4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB4D4_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    eax = lift_call(&env, lift_load(&env, 0u, 0x50b3acu, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5c7b90u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4eb4f6;
    edx = 0xffu;
    eax = 0x10u;
    eax = lift_call(&env, 0x4e6bacu, eax, edx, ebx, ecx, 0, esp);
L_4eb4f6:
    eax = ebx;
    eax = lift_call(&env, 0x4eb500u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb526(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB526_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB526_STACK, 0, entry);
    edx = eax;
    {
        uint32_t r = lift_and(32, edx, 0x7fffffffu, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4eb532;
    goto L_4eb57b;
L_4eb532:
    {
        (void)lift_sub(32, edx, 0x7f800000u, &fl);
    }
    if (!fl.zf)
        goto L_4eb546;
    edx = eax;
    {
        uint32_t r = lift_or(32, edx, 0x7ff00000u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    goto L_4eb57b;
L_4eb546:
    {
        (void)lift_and(32, edx, 0x7f800000u, &fl);
    }
    if (!fl.zf)
        goto L_4eb568;
    {
        uint32_t r = lift_xor(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
L_4eb553:
    {
        uint32_t r = lift_add(32, ecx, 0x800000u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, edx, edx, &fl);
        edx = r;
    }
    {
        (void)lift_and(32, edx, 0x800000u, &fl);
    }
    if (fl.zf)
        goto L_4eb553;
    {
        uint32_t r = lift_or(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, edx, ecx, &fl);
        edx = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
L_4eb568:
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_and(32, eax, 0xeu, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_ror(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, edx, 0x38000000u, &fl);
        edx = r;
    }
L_4eb57b:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb57c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB57C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB57C_STACK, 0, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_and(32, edx, 0x7ff00000u, &fl);
    }
    if (!fl.zf)
        goto L_4eb587;
    {
        uint32_t r = lift_sub(32, edx, edx, &fl);
        edx = r;
    }
L_4eb587:
    {
        (void)lift_and(32, ecx, 0x7ff00000u, &fl);
    }
    if (!fl.zf)
        goto L_4eb591;
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
L_4eb591:
    ebp = ecx;
    {
        uint32_t r = lift_xor(32, ebp, edx, &fl);
        ebp = r;
    }
    ebp = 0x0u;
    if (fl.sf)
        goto L_4eb5a8;
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4eb5a2;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
L_4eb5a2:
    if (fl.zf)
        goto L_4eb5b0;
    {
        uint32_t a = ecx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, ecx, &fl);
        edx = r;
    }
L_4eb5a8:
    {
        uint32_t r = lift_add(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sbb(32, ebp, 0x0u, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebp = r;
    }
L_4eb5b0:
    eax = ebp;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb5c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB5C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB5C0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ebx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (edx & 0xffff00ffu) | ((((edx & 0xffu)) & 0xffu) << 8);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((((edx >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((((edx >> 8) & 0xffu)) & 0xffu);
    eax = lift_call(&env, 0x4ec2d0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb606(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB606_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB606_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_and(32, edx, 0x7ff00000u, &fl);
    }
    if (fl.zf)
        goto L_4eb64e;
    {
        uint32_t r = lift_sub(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x20000000u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, 0x0u, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4eb645;
    {
        (void)lift_sub(32, edx, 0x8fe00000u, &fl);
    }
    if (!fl.cf)
        goto L_4eb645;
    {
        (void)lift_sub(32, edx, 0x70200000u, &fl);
    }
    if (fl.cf)
        goto L_4eb64e;
    {
        uint32_t r = lift_sub(32, edx, 0x70000000u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_or(32, edx, ebx, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4eb645:
    eax = 0x7f800000u;
    {
        uint32_t r = lift_or(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4eb64e:
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB910_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB910_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    ecx = eax;
    esi = edx;
    edx = 0x1u;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_xor(32, ebp, ebp, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x0u, 4, ebx);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb93c;
    {
        (void)lift_sub(32, edx, lift_load(&env, 0u, 0x50b3b8u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4eb93a;
    lift_store(&env, esi, 0x0u, 4, edx);
    goto L_4eb93c;
L_4eb93a:
    lift_store(&env, esi, 0x0u, 4, ebx);
L_4eb93c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x72u, &fl);
    }
    if (fl.cf)
        goto L_4eb94a;
    if (fl.cf || fl.zf)
        goto L_4eb950;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x77u, &fl);
    }
    if (fl.zf)
        goto L_4eb955;
    goto L_4eb95f;
L_4eb94a:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x61u, &fl);
    }
    if (fl.zf)
        goto L_4eb95a;
    goto L_4eb95f;
L_4eb950:
    {
        uint32_t r = lift_or(8, (ebx & 0xffu), 0x1u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    goto L_4eb970;
L_4eb955:
    {
        uint32_t r = lift_or(8, (ebx & 0xffu), 0x2u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    goto L_4eb970;
L_4eb95a:
    {
        uint32_t r = lift_or(8, (ebx & 0xffu), 0x82u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    goto L_4eb970;
L_4eb95f:
    eax = 0x9u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    goto L_4eba3f;
L_4eb970:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0x1u, 1)) & 0xffu) << 8);
    {
        uint32_t a = ecx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ecx = r;
    }
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4eba2a;
L_4eb97c:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4eba2a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x63u, &fl);
    }
    if (fl.cf)
        goto L_4eb9a7;
    if (fl.cf || fl.zf)
        goto L_4eb9f5;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6eu, &fl);
    }
    if (fl.cf)
        goto L_4eba1e;
    if (fl.cf || fl.zf)
        goto L_4eba0a;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x74u, &fl);
    }
    if (fl.zf)
        goto L_4eb9d4;
    goto L_4eba1e;
L_4eb9a7:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x2bu, &fl);
    }
    if (fl.cf)
        goto L_4eba1e;
    if (fl.cf || fl.zf)
        goto L_4eb9ba;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x62u, &fl);
    }
    if (fl.zf)
        goto L_4eb9e3;
    goto L_4eba1e;
L_4eb9ba:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4eb9c7;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    goto L_4eba1e;
L_4eb9c7:
    eax = 0x1u;
    {
        uint32_t r = lift_or(8, (ebx & 0xffu), 0x3u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, esp, 0x0u, 4, eax);
    goto L_4eba1e;
L_4eb9d4:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4eb9dc;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    goto L_4eba1e;
L_4eb9dc:
    edi = 0x1u;
    goto L_4eba1e;
L_4eb9e3:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4eb9eb;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    goto L_4eba1e;
L_4eb9eb:
    edi = 0x1u;
    {
        uint32_t r = lift_or(8, (ebx & 0xffu), 0x40u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    goto L_4eba1e;
L_4eb9f5:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4eb9fd;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    goto L_4eba1e;
L_4eb9fd:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (eax & 0xffu), 0x1u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    ebp = 0x1u;
    lift_store(&env, esi, 0x0u, 1, (eax & 0xffu));
    goto L_4eba1e;
L_4eba0a:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4eba12;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    goto L_4eba1e;
L_4eba12:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esi, 0x0u, 1)) & 0xffu) << 8);
    {
        uint32_t r = lift_and(8, ((eax >> 8) & 0xffu), 0xfeu, &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    ebp = 0x1u;
    lift_store(&env, esi, 0x0u, 1, ((eax >> 8) & 0xffu));
L_4eba1e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1u, 1)) & 0xffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ecx = r;
    }
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4eb97c;
L_4eba2a:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4eba3d;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x505440u, 4), 0x200u, &fl);
    }
    if (!fl.zf)
        goto L_4eba3d;
    {
        uint32_t r = lift_or(8, (ebx & 0xffu), 0x40u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
L_4eba3d:
    edx = ebx;
L_4eba3f:
    eax = edx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebb78(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBB78_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EBB78_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = lift_call(&env, 0x4ebb34u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebb84(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBB84_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EBB84_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, 0u, 0x5c7760u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ebbc3;
L_4ebb98:
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4ebbbd;
    {
        (void)lift_and(8, lift_load(&env, edx, 0xcu, 1), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4ebbb1;
    edx = 0x1u;
    eax = ebx;
    eax = lift_call(&env, 0x4e7fc4u, eax, edx, ebx, ecx, 0, esp);
L_4ebbb1:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
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
    return env.failed ? 0u : eax;
L_4ebbbd:
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ebb98;
L_4ebbc3:
    edx = 0x5c7764u;
L_4ebbc8:
    eax = lift_load(&env, edx, 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ebbf4;
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x4u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4ebbf0;
    ecx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, edx, 0x0u, 4, ecx);
    edx = lift_load(&env, 0u, 0x5c7760u, 4);
    lift_store(&env, 0u, 0x5c7760u, 4, eax);
    lift_store(&env, eax, 0x0u, 4, edx);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
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
    return env.failed ? 0u : eax;
L_4ebbf0:
    edx = eax;
    goto L_4ebbc8;
L_4ebbf4:
    eax = 0x4u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb4u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebc90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBC90_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EBC90_STACK, 0, entry);
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
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x4u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ebcc5;
    ebx = lift_load(&env, edx, 0x8u, 4);
    ecx = lift_load(&env, edx, 0x0u, 4);
    ebx = lift_load(&env, ebx, 0x8u, 4);
    {
        uint32_t r = lift_sub(32, ebx, ecx, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ebcc5;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, 0xcu, 1)) & 0xffu);
    esi = lift_load(&env, edx, 0x0u, 4);
    edi = lift_load(&env, edx, 0x4u, 4);
    {
        uint32_t r = lift_and(8, (ebx & 0xffu), 0xefu, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_add(32, esi, eax, &fl);
        esi = r;
    }
    lift_store(&env, edx, 0xcu, 1, (ebx & 0xffu));
    {
        uint32_t r = lift_sub(32, edi, eax, &fl);
        edi = r;
    }
    lift_store(&env, edx, 0x0u, 4, esi);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, edx, 0x4u, 4, edi);
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
    return env.failed ? 0u : eax;
L_4ebcc5:
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebcd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBCD0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EBCD0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_and(8, lift_load(&env, eax, 0xcu, 1), 0xefu, &fl);
        lift_store(&env, eax, 0xcu, 1, r);
    }
    edx = lift_load(&env, eax, 0x8u, 4);
    edx = lift_load(&env, edx, 0x8u, 4);
    lift_store(&env, eax, 0x4u, 4, 0x0u);
    lift_store(&env, eax, 0x0u, 4, edx);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebce8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBCE8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EBCE8_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    eax = lift_load(&env, eax, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0xcu, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x6u, &fl);
    }
    if (fl.zf)
        goto L_4ebd79;
    {
        (void)lift_and(8, lift_load(&env, ecx, 0xdu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4ebd39;
    eax = ecx;
    eax = lift_call(&env, 0x4e3ce0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ebd50;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4ebd27;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ebd27;
L_4ebd1d:
    eax = 0x9u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
L_4ebd27:
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4ebd39:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4ebd41;
    {
        uint32_t r = lift_sub(32, esi, lift_load(&env, ecx, 0x4u, 4), &fl);
        esi = r;
    }
L_4ebd41:
    eax = lift_load(&env, ecx, 0x8u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    lift_store(&env, ecx, 0x0u, 4, eax);
L_4ebd50:
    {
        uint32_t r = lift_and(8, lift_load(&env, ecx, 0xcu, 1), 0xebu, &fl);
        lift_store(&env, ecx, 0xcu, 1, r);
    }
    edx = esi;
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, 0x4e0150u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ebe4b;
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4ebd79:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (fl.cf)
        goto L_4ebd8b;
    if (fl.cf || fl.zf)
        goto L_4ebd91;
    {
        (void)lift_sub(32, ebx, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ebe13;
    goto L_4ebd1d;
L_4ebd8b:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4ebdd4;
    goto L_4ebd1d;
L_4ebd91:
    edx = ecx;
    eax = esi;
    edi = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_call(&env, 0x4ebc90u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ebe4b;
    edx = esi;
    eax = lift_load(&env, ecx, 0x10u, 4);
    {
        uint32_t r = lift_sub(32, edx, edi, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4e0150u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ebdc8;
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4ebdc8:
    eax = ecx;
    eax = lift_call(&env, 0x4ebcd0u, eax, edx, ebx, ecx, 0, esp);
    goto L_4ebe4b;
L_4ebdd4:
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, 0x4ec380u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, ecx, 0x4u, 4);
    edi = esi;
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, edi, eax, &fl);
        edi = r;
    }
    edx = ecx;
    eax = edi;
    eax = lift_call(&env, 0x4ebc90u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ebe4b;
    edx = esi;
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, 0x4e0150u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ebdc8;
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4ebe13:
    edx = (edx & 0xffffff00u) | ((((eax >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_and(8, (edx & 0xffu), 0xefu, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, ecx, 0xcu, 1, (edx & 0xffu));
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    edx = esi;
    eax = lift_load(&env, ecx, 0x10u, 4);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    eax = lift_call(&env, 0x4e0150u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ebe4b;
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4ebe4b:
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebe60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBE60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EBE60_STACK, 0, entry);
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
    edx = eax;
    {
        (void)lift_and(8, lift_load(&env, eax, 0xcu, 1), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4ebe79;
    {
        (void)lift_and(8, lift_load(&env, edx, 0xdu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4ebe79;
    eax = edx;
    eax = lift_call(&env, 0x4dabd0u, eax, edx, ebx, ecx, 0, esp);
L_4ebe79:
    eax = lift_load(&env, edx, 0x10u, 4);
    eax = lift_call(&env, 0x4ec380u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    ecx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4ebeb4;
    eax = lift_load(&env, edx, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    esi = lift_load(&env, edx, 0x4u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4ebea9;
    {
        (void)lift_and(8, lift_load(&env, edx, 0xdu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4ebea5;
    ecx = (esi + ebx);
    goto L_4ebea9;
L_4ebea5:
    ecx = ebx;
    {
        uint32_t r = lift_sub(32, ecx, esi, &fl);
        ecx = r;
    }
L_4ebea9:
    eax = lift_load(&env, edx, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = ecx;
L_4ebeb4:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC160_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC160_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    ebx = eax;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ec176;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
L_4ec176:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec1d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC1D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC1D0_STACK, 0, entry);
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
    ebx = (ebx & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), lift_load(&env, eax, 0x0u, 1), &fl);
    }
    if (fl.zf)
        goto L_4ec1e9;
L_4ec1d8:
    edx = eax;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4ec1e7;
    {
        (void)lift_sub(8, (ebx & 0xffu), lift_load(&env, eax, 0x0u, 1), &fl);
    }
    if (fl.zf)
        goto L_4ec1e9;
    goto L_4ec1d8;
L_4ec1e7:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4ec1e9:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec1ec(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC1EC_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC1EC_STACK, 0, entry);
L_4e6e19:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, esp, 0x8u, 4);
    ebx = lift_load(&env, esp, 0xcu, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e6e4a;
    {
        (void)lift_and(8, lift_load(&env, edx, 0x4u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e6e3a;
    {
        (void)lift_and(8, lift_load(&env, edx, 0x4u, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4e6e64;
    eax = lift_load(&env, ebx, 0x8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4e6e43;
L_4e6e3a:
    edx = ebx;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4cd9f0u, eax, edx, ebx, ecx, 0, esp);
L_4e6e43:
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4e6e4a:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    ecx = lift_load(&env, 0u, 0x5c5c54u, 4);
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    eax = lift_load(&env, edx, 0x18u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, eax, 0x0u, 4, ecx);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4e6e64:
    eax = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t r = lift_and(32, eax, 0x3fffffffu, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0x25671234u, &fl);
    }
    if (!fl.zf)
        goto L_4e6e43;
    ecx = lift_load(&env, edx, 0x18u, 4);
    {
        (void)lift_sub(32, ebx, lift_load(&env, ecx, 0x2cu, 4), &fl);
    }
    if (fl.zf)
        goto L_4e6e90;
L_4e6e7a:
    eax = lift_load(&env, ecx, 0x34u, 4);
L_4e6e7d:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e6ea9;
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4e6ea9;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x2cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e6ea1;
L_4e6e8b:
    eax = lift_load(&env, eax, 0x8u, 4);
    goto L_4e6e7d;
L_4e6e90:
    lift_store(&env, ecx, 0x2cu, 4, 0x0u);
    goto L_4e6e7a;
L_4e6e99:
    edx = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, ecx, 0x2cu, 4, edx);
    goto L_4e6e8b;
L_4e6ea1:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xcu, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (!fl.cf)
        goto L_4e6eba;
L_4e6ea9:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e6ec3;
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4e6ec3;
    eax = (eax & 0xffff00ffu) | (((0x4u) & 0xffu) << 8);
L_4e6eb3:
    lift_store(&env, ecx, 0x24u, 1, ((eax >> 8) & 0xffu));
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4e6eba:
    if (fl.cf || fl.zf)
        goto L_4e6e99;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x7u, &fl);
    }
    if (fl.zf)
        goto L_4e6e99;
    goto L_4e6ea9;
L_4e6ec3:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x2cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e6eda;
L_4e6ec9:
    {
        (void)lift_sub(32, ebx, lift_load(&env, ecx, 0x30u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4e6e43;
    lift_store(&env, ecx, 0x24u, 1, 0x3u);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4e6eda:
    edx = ebx;
    eax = ecx;
    eax = lift_call(&env, 0x4e8fa7u, eax, edx, ebx, ecx, 0, esp);
    eax = (eax & 0xffff00ffu) | ((((eax & 0xffu)) & 0xffu) << 8);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e6ec9;
    goto L_4e6eb3;
    goto L_4e6e19;
}

uint32_t lifted_f4ec2d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC2D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC2D0_STACK, 0, entry);
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec300;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), (edx & 0xffu), &fl);
    }
L_4ec2d6:
    {
        (void)lift_and(8, (eax & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4ec2e3;
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_ror(32, a, 0x8u, &fl);
        edx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4ec2d6;
L_4ec2e3:
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = lift_call(&env, 0x4ec307u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    {
        uint32_t r = lift_and(32, ecx, 0x3u, &fl);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec300;
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec300;
    lift_store(&env, eax, 0x1u, 1, ((edx >> 8) & 0xffu));
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec300;
    lift_store(&env, eax, 0x2u, 1, (edx & 0xffu));
L_4ec300:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec307(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC307_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC307_STACK, 0, entry);
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec372;
L_4ec30b:
    {
        (void)lift_and(8, (eax & 0xffu), 0x1fu, &fl);
    }
    if (fl.zf)
        goto L_4ec317;
    lift_store(&env, eax, 0x0u, 4, edx);
    eax = (eax + 0x4u);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4ec30b;
L_4ec317:
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec357;
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec349;
L_4ec320:
    lift_store(&env, eax, 0x0u, 4, edx);
    lift_store(&env, eax, 0x4u, 4, edx);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, eax, 0x8u, 4, edx);
    lift_store(&env, eax, 0xcu, 4, edx);
    if (fl.zf)
        goto L_4ec346;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x20u, 1), (edx & 0xffu), &fl);
    }
    lift_store(&env, eax, 0x10u, 4, edx);
    lift_store(&env, eax, 0x14u, 4, edx);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, eax, 0x18u, 4, edx);
    lift_store(&env, eax, 0x1cu, 4, edx);
    eax = (eax + 0x20u);
    if (!fl.zf)
        goto L_4ec320;
    eax = (eax + 0xfffffff0u);
L_4ec346:
    eax = (eax + 0x10u);
L_4ec349:
    lift_store(&env, eax, 0x0u, 4, edx);
    lift_store(&env, eax, 0x4u, 4, edx);
    lift_store(&env, eax, 0x8u, 4, edx);
    lift_store(&env, eax, 0xcu, 4, edx);
    eax = (eax + 0x10u);
L_4ec357:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    {
        uint32_t r = lift_and(32, ecx, 0x3u, &fl);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec372;
    lift_store(&env, eax, 0x0u, 4, edx);
    eax = (eax + 0x4u);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec372;
    lift_store(&env, eax, 0x0u, 4, edx);
    eax = (eax + 0x4u);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec372;
    lift_store(&env, eax, 0x0u, 4, edx);
    eax = (eax + 0x4u);
L_4ec372:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec380(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC380_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC380_STACK, 0, entry);
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
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ec391;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x507c34u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ec3a4;
L_4ec391:
    eax = 0x4u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4ec3a4:
    edx = lift_load(&env, 0u, 0x507c8cu, 4);
    edx = lift_load(&env, edx, (ebx * 4u) + 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
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
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ca8u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    edx = eax;
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, edx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ec3d5;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
L_4ec3d5:
    eax = edx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC3E0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC3E0_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ec3f3;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x507c34u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ec404;
L_4ec3f3:
    eax = 0x4u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
    goto L_4ec472;
L_4ec404:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x507d24u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ec437;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cfcu, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ec437;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507d24u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
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
    return env.failed ? 0u : eax;
L_4ec437:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (esp + 0x4u);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x507c8cu, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, eax, (esi * 4u) + 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c78u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ec467;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 1, esp);
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
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
    return env.failed ? 0u : eax;
L_4ec467:
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, esp, 0x0u, 4);
L_4ec472:
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec548(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC548_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC548_STACK, 0, entry);
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
    edx = eax;
    eax = lift_call(&env, 0x4ec578u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ec55f;
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4ec55f:
    ebx = lift_load(&env, edx, 0x4u, 4);
    ecx = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, edx, 0x4u, 4, ebx);
    lift_store(&env, edx, 0x0u, 4, ecx);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0xffffffffu, 1)) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec578(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC578_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC578_STACK, 0, entry);
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
    ecx = eax;
    eax = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ec58e;
    eax = ecx;
    eax = lift_call(&env, 0x4e3b60u, eax, edx, ebx, ecx, 0, esp);
L_4ec58e:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0xdu, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4ec5a5;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x6u, &fl);
    }
    if (fl.zf)
        goto L_4ec5a5;
    eax = 0x2000u;
    eax = lift_call(&env, 0x4e3f28u, eax, edx, ebx, ecx, 0, esp);
L_4ec5a5:
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ecx, 0xcu, 1)) & 0xffu) << 8);
    {
        uint32_t r = lift_and(8, ((edx >> 8) & 0xffu), 0xfbu, &fl);
        edx = (edx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, ecx, 0xcu, 1, ((edx >> 8) & 0xffu));
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = lift_load(&env, ecx, 0xcu, 4);
    {
        uint32_t r = lift_and(32, eax, 0x2400u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0x2400u, &fl);
    }
    if (!fl.zf)
        goto L_4ec5e8;
    ebx = lift_load(&env, ecx, 0x10u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4ec5e8;
    lift_store(&env, ecx, 0x4u, 4, ebx);
    eax = lift_call(&env, 0x4ecaa0u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4ec605;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
    lift_store(&env, ecx, 0x4u, 4, 0x1u);
    goto L_4ec62a;
L_4ec5e8:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0xdu, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4ec5f5;
    ebx = 0x1u;
    goto L_4ec5f8;
L_4ec5f5:
    ebx = lift_load(&env, ecx, 0x14u, 4);
L_4ec5f8:
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, 0x4ec3e0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, eax);
L_4ec605:
    esi = lift_load(&env, ecx, 0x4u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ec62a;
    if (!fl.zf)
        goto L_4ec61a;
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0xcu, 1), 0x10u, &fl);
        lift_store(&env, ecx, 0xcu, 1, r);
    }
    eax = lift_load(&env, ecx, 0x4u, 4);
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
    return env.failed ? 0u : eax;
L_4ec61a:
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, ecx, 0xcu, 1)) & 0xffu) << 8);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    {
        uint32_t r = lift_or(8, ((ebx >> 8) & 0xffu), 0x20u, &fl);
        ebx = (ebx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    lift_store(&env, ecx, 0xcu, 1, ((ebx >> 8) & 0xffu));
L_4ec62a:
    eax = lift_load(&env, ecx, 0x4u, 4);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec8f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC8F0_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC8F0_STACK, 4, entry);
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4ecad0u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC910_STACK + 4 + 4 * 2 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC910_STACK, 2, entry);
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esp, 0x4u, 1)) & 0xffu);
    lift_store(&env, eax, 0x14u, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ec92d;
    eax = 0xfffffffdu;
    eax = lift_call(&env, 0x4ecb50u, eax, edx, ebx, ecx, 0, esp);
L_4ec92d:
    eax = 0x1u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC940_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC940_STACK, 0, entry);
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
    ebx = eax;
    {
        uint32_t v = 0x410u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4ec910u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eca85(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECA85_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ECA85_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = edx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4ed79fu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebx, 0x0u, 4, eax);
    lift_store(&env, ebx, 0x4u, 4, edx);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ecaa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECAA0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ECAA0_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x509718u, 4);
    eax = lift_call(&env, 0x4ed984u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4ecabd;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4ecabd;
    eax = lift_call(&env, 0x4eda00u, eax, edx, ebx, ecx, 0, esp);
L_4ecabd:
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ecad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECAD0_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ECAD0_STACK, 4, entry);
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
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = 0xffffffffu;
    {
        uint32_t v = lift_load(&env, esp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t v = lift_load(&env, esp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = ebx;
    eax = lift_call(&env, 0x4e1990u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ecb34;
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, edx, 0x88u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ecb34;
    esi = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, esi, 0x54u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ecb2b;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x1cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ecb22;
    eax = lift_load(&env, ebx, 0x1cu, 4);
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, ebx, 0x5cu, 4), eax, edx, ebx, ecx, 0, esp);
L_4ecb22:
    ebx = lift_load(&env, edi, 0x0u, 4);
    eax = edi;
    eax = lift_call(&env, lift_load(&env, ebx, 0x6cu, 4), eax, edx, ebx, ecx, 0, esp);
    goto L_4ecb32;
L_4ecb2b:
    esi = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, esi, 0x58u, 4), eax, edx, ebx, ecx, 0, esp);
L_4ecb32:
    esi = eax;
L_4ecb34:
    eax = lift_call(&env, 0x4eda70u, eax, edx, ebx, ecx, 0, esp);
    eax = esi;
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
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ecb50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECB50_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ECB50_STACK, 0, entry);
    {
        (void)lift_sub(32, eax, 0xfffffffdu, &fl);
    }
    if (!fl.zf)
        goto L_4ecb5c;
    eax = 0xffffffffu;
    goto L_4ecb87;
L_4ecb5c:
    {
        (void)lift_sub(32, eax, 0xfffffffeu, &fl);
    }
    if (fl.zf)
        goto L_4ecb87;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ecb7b;
    eax = 0xfffffffdu;
    eax = lift_call(&env, 0x4e6f60u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    return env.failed ? 0u : eax;
L_4ecb7b:
    {
        (void)lift_sub(32, eax, 0x3a4u, &fl);
    }
    if (!fl.zf)
        goto L_4ecb87;
    eax = 0xfffffffcu;
L_4ecb87:
    eax = lift_call(&env, 0x4e6f60u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ecc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECC60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ECC60_STACK, 0, entry);
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
    ecx = eax;
    ebx = edx;
    {
        (void)lift_sub(32, edx, 0x1000u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ecc80;
    edx = 0x1000u;
    eax = lift_call(&env, 0x4ecc03u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_sub(32, ebx, 0x1000u, &fl);
        ebx = r;
    }
    goto L_4ecc98;
L_4ecc80:
    {
        (void)lift_sub(32, edx, 0xfffff000u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ecc98;
    edx = 0xfffff000u;
    eax = lift_call(&env, 0x4ecc03u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, ebx, 0x1000u, &fl);
        ebx = r;
    }
L_4ecc98:
    edx = ebx;
    eax = ecx;
    eax = lift_call(&env, 0x4ecc03u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ed60b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ED60B_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ED60B_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x34u, &fl);
        esp = r;
    }
    edi = edx;
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
L_4ed61c:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4ed62d;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x9u, &fl);
    }
    if (fl.cf)
        goto L_4ed630;
    {
        (void)lift_sub(8, (edx & 0xffu), 0xdu, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ed630;
L_4ed62d:
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    goto L_4ed61c;
L_4ed630:
    ebx = (eax + 0x1u);
    {
        uint32_t r = lift_xor(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2bu, &fl);
    }
    if (fl.zf)
        goto L_4ed641;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ed643;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
L_4ed641:
    eax = ebx;
L_4ed643:
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    edx = (edx & 0xffff00ffu) | (((0x30u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
L_4ed64a:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2eu, &fl);
    }
    if (!fl.zf)
        goto L_4ed65c;
    {
        (void)lift_and(8, (ecx & 0xffu), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_4ed684;
    {
        uint32_t r = lift_or(8, (ecx & 0xffu), 0x8u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    goto L_4ed64a;
L_4ed65c:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x30u, &fl);
    }
    if (fl.cf)
        goto L_4ed684;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x39u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ed684;
    {
        (void)lift_and(8, (ecx & 0xffu), 0x8u, &fl);
    }
    if (fl.zf)
        goto L_4ed66e;
    {
        uint32_t a = lift_load(&env, ebp, 0xffffffe4u, 4);
        uint32_t r = lift_inc(32, a, &fl, 1);
        lift_store(&env, ebp, 0xffffffe4u, 4, r);
    }
L_4ed66e:
    {
        uint32_t r = lift_or(8, ((edx >> 8) & 0xffu), (edx & 0xffu), &fl);
        edx = (edx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x30u, &fl);
    }
    if (fl.zf)
        goto L_4ed67f;
    {
        (void)lift_sub(32, ebx, 0x13u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed67e;
    lift_store(&env, ebx, ebp + 0xffffffc0u, 1, (edx & 0xffu));
L_4ed67e:
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
L_4ed67f:
    {
        uint32_t r = lift_or(8, (ecx & 0xffu), 0x4u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    goto L_4ed64a;
L_4ed684:
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_and(8, (ecx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4ed6f4;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x65u, &fl);
    }
    if (fl.zf)
        goto L_4ed699;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x45u, &fl);
    }
    if (!fl.zf)
        goto L_4ed6f0;
L_4ed699:
    edx = (eax + 0xffffffffu);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, eax, 0x0u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    edx = (eax + 0x1u);
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2bu, &fl);
    }
    if (fl.zf)
        goto L_4ed6b1;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ed6b3;
    {
        uint32_t r = lift_or(8, (ecx & 0xffu), 0x2u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
L_4ed6b1:
    eax = edx;
L_4ed6b3:
    {
        uint32_t r = lift_and(8, (ecx & 0xffu), 0xfbu, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
L_4ed6b6:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x30u, &fl);
    }
    if (fl.cf)
        goto L_4ed6df;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x39u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ed6df;
    {
        (void)lift_sub(32, esi, 0x3e8u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed6d9;
    {
        uint32_t r = lift_imul(32, esi, 0xau, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, esi);
    esi = (edx & 0xffu);
    {
        uint32_t r = lift_add(32, esi, lift_load(&env, ebp, 0xffffffecu, 4), &fl);
        esi = r;
    }
    {
        uint32_t r = lift_sub(32, esi, 0x30u, &fl);
        esi = r;
    }
L_4ed6d9:
    {
        uint32_t r = lift_or(8, (ecx & 0xffu), 0x4u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    goto L_4ed6b6;
L_4ed6df:
    {
        (void)lift_and(8, (ecx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ed6e6;
    {
        uint32_t a = esi;
        uint32_t r = lift_sub(32, 0, a, &fl);
        esi = r;
    }
L_4ed6e6:
    {
        (void)lift_and(8, (ecx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4ed6f1;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    goto L_4ed6f1;
L_4ed6f0:
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
L_4ed6f1:
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
L_4ed6f4:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ed702;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
L_4ed702:
    {
        uint32_t r = lift_sub(32, esi, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, ebx, 0x13u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ed714;
    {
        uint32_t r = lift_sub(32, ebx, 0x13u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, esi, ebx, &fl);
        esi = r;
    }
    ebx = 0x13u;
L_4ed714:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ed723;
    {
        (void)lift_sub(8, lift_load(&env, ebx, ebp + 0xffffffbfu, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4ed723;
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    goto L_4ed714;
L_4ed723:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4ed738;
    lift_store(&env, edi, 0x8u, 2, 0x0u);
    lift_store(&env, edi, 0x4u, 4, ebx);
    eax = edi;
    lift_store(&env, edi, 0x0u, 4, ebx);
    {
        uint32_t r = lift_xor(32, eax, edi, &fl);
        eax = r;
    }
    goto L_4ed797;
L_4ed738:
    {
        uint32_t r = lift_xor(8, (edx & 0xffu), (edx & 0xffu), &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    eax = (ebp + 0xffffffc0u);
    lift_store(&env, ebx, ebp + 0xffffffc0u, 1, (edx & 0xffu));
    edx = (ebp + 0xffffffd4u);
    eax = lift_call(&env, 0x4ee370u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4ed757;
    eax = (ebp + 0xffffffd4u);
    edx = esi;
    eax = lift_call(&env, 0x4ecc60u, eax, edx, ebx, ecx, 0, esp);
L_4ed757:
    {
        (void)lift_and(8, (ecx & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4ed760;
    {
        uint32_t r = lift_or(8, lift_load(&env, ebp, 0xffffffddu, 1), 0x80u, &fl);
        lift_store(&env, ebp, 0xffffffddu, 1, r);
    }
L_4ed760:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, edi, 0x8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, edi, 0x4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, edi, 0x0u, 4, eax);
    eax = (esi + ebx + 0xffffffffu);
    {
        (void)lift_sub(32, eax, 0x134u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ed784;
    eax = 0x3u;
    goto L_4ed797;
L_4ed784:
    {
        (void)lift_sub(32, eax, 0xfffffeccu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed792;
    eax = 0x2u;
    goto L_4ed797;
L_4ed792:
    eax = 0x1u;
L_4ed797:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eda00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDA00_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EDA00_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x8u, &fl);
        esp = r;
    }
    ebx = eax;
    edx = lift_load(&env, 0u, 0x507d38u, 4);
    lift_store(&env, esp, 0x4u, 1, (ebx & 0xffu));
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4eda2b;
    eax = 0x1u;
    edx = ebx;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cfcu, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507d38u, 4), eax, edx, ebx, ecx, 0, esp);
    goto L_4eda5b;
L_4eda2b:
    eax = 0x1u;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4e89f4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (esp + 0x4u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (esp + 0x10u);
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
    eax = lift_call(&env, 0x4f1d04u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    eax = 0x1u;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
L_4eda5b:
    eax = ebx;
    {
        uint32_t r = lift_add(32, esp, 0x8u, &fl);
        esp = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4edb48(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDB48_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EDB48_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = (esi & 0xffff0000u) | ((lift_load(&env, edx, 0x8u, 2)) & 0xffffu);
    ecx = lift_load(&env, edx, 0x4u, 4);
    ebx = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        esi = r;
    }
    esi = (esi & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    edx = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, 0x4edc0eu, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    lift_store(&env, ebx, 0x0u, 4, eax);
    lift_store(&env, ebx, 0x4u, 4, edx);
    lift_store(&env, ebx, 0x8u, 2, (esi & 0xffffu));
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4edd24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDD24_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EDD24_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = (esi & 0xffff0000u) | ((lift_load(&env, edx, 0x8u, 2)) & 0xffffu);
    ecx = lift_load(&env, edx, 0x4u, 4);
    ebx = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        esi = r;
    }
    esi = (esi & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    edx = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, 0x4eddc4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    lift_store(&env, ebx, 0x0u, 4, eax);
    lift_store(&env, ebx, 0x4u, 4, edx);
    lift_store(&env, ebx, 0x8u, 2, (esi & 0xffffu));
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4edf7f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDF7F_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EDF7F_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    {
        uint32_t r = lift_and(8, ((edx >> 8) & 0xffu), 0x7fu, &fl);
        edx = (edx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x7fffu, &fl);
    }
    if (!fl.zf)
        goto L_4edfaa;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4edfa3;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4edfa3;
    eax = 0x3u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4edfa3:
    eax = 0x2u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4edfaa:
    {
        (void)lift_and(16, lift_load(&env, eax, 0x8u, 2), 0x7fffu, &fl);
    }
    if (!fl.zf)
        goto L_4edfc8;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4edfc1;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4edfc1;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4edfc1:
    eax = 0x4u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4edfc8:
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee094(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE094_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE094_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = edx;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.sf)
        goto L_4ee0a4;
    {
        uint32_t a = eax;
        uint32_t r = lift_sub(32, 0, a, &fl);
        eax = r;
    }
    edx = 0xbfffu;
    goto L_4ee0ad;
L_4ee0a4:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = edx;
    edx = 0x3fffu;
L_4ee0ad:
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4ee0c8;
    {
        uint32_t a = eax;
        fl.zf = a == 0;
        if (a != 0)
        {
            ecx = lift_bsr(a);
        }
    }
    ecx = (ecx & 0xffff00ffu) | ((((ecx & 0xffu)) & 0xffu) << 8);
    ecx = (ecx & 0xffffff00u) | ((0x1fu) & 0xffu);
    {
        uint32_t r = lift_sub(8, (ecx & 0xffu), ((ecx >> 8) & 0xffu), &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
    ecx = ((ecx >> 8) & 0xffu);
    {
        uint32_t r = lift_add(32, ecx, edx, &fl);
        ecx = r;
    }
    edx = eax;
    goto L_4ee0cc;
L_4ee0c8:
    {
        uint32_t r = lift_sub(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
L_4ee0cc:
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, ebx, 0x0u, 4, eax);
    lift_store(&env, ebx, 0x4u, 4, edx);
    lift_store(&env, ebx, 0x8u, 2, (ecx & 0xffffu));
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee0dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE0DC_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE0DC_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = (esi & 0xffff0000u) | ((lift_load(&env, edx, 0x8u, 2)) & 0xffffu);
    ecx = lift_load(&env, edx, 0x4u, 4);
    ebx = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        esi = r;
    }
    esi = (esi & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    edx = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, 0x4ee160u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    lift_store(&env, ebx, 0x0u, 4, eax);
    lift_store(&env, ebx, 0x4u, 4, edx);
    lift_store(&env, ebx, 0x8u, 2, (esi & 0xffffu));
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE370_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE370_STACK, 0, entry);
    {
        uint32_t v = ebp;
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
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = eax;
    {
        uint32_t r = lift_sub(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_sub(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
L_4ee380:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ee3b5;
    edi = edx;
    ebx = ecx;
    eax = ebp;
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_adc(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_adc(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_adc(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_adc(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_adc(32, ecx, ebx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_adc(32, edx, edi, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_adc(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_adc(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (eax & 0xffu), 0xfu, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_adc(32, ecx, 0x0u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_adc(32, edx, 0x0u, &fl);
        edx = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    goto L_4ee380;
L_4ee3b5:
    eax = ecx;
    edi = 0x405eu;
    eax = lift_call(&env, 0x4ee3d2u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    lift_store(&env, ebp, 0x4u, 4, edx);
    lift_store(&env, ebp, 0x0u, 4, eax);
    lift_store(&env, ebp, 0x8u, 2, (esi & 0xffffu));
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
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
        ebp = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE670_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE670_STACK, 0, entry);
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
    ecx = eax;
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x5cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = 0x2u;
    esi = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    ebx = 0x1u;
    eax = lift_call(&env, lift_load(&env, esi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE730_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE730_STACK, 0, entry);
    {
        uint32_t v = ecx;
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
        uint32_t v = 0x401u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE840_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE840_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    ecx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51c26cu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, ecx);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, ecx, 0x0u, 4, 0x51c2d4u);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    lift_store(&env, ecx, 0x8u, 4, 0x11u);
    lift_store(&env, ecx, 0xcu, 4, 0x0u);
    lift_store(&env, ecx, 0x10u, 4, 0x0u);
    lift_store(&env, ecx, 0x14u, 4, 0x0u);
    lift_store(&env, ecx, 0x18u, 4, edx);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE8D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE8D0_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ee8eb;
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
L_4ee8eb:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4ee907;
    ebx = ((esi * 4u));
    eax = ebx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4c9ff0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
L_4ee907:
    lift_store(&env, ecx, 0x8u, 4, esi);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE910_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE910_STACK, 0, entry);
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
    ecx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ee956;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ee947;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
L_4ee926:
    edx = lift_load(&env, ecx, 0x4u, 4);
    edx = lift_load(&env, edx, esi + 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4ee93e;
L_4ee930:
    eax = (edx + 0x8u);
    eax = lift_call(&env, 0x4ca180u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, edx, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4ee930;
L_4ee93e:
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, esi, 0x4u, &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, ebx, lift_load(&env, ecx, 0x8u, 4), &fl);
    }
    if (fl.cf)
        goto L_4ee926;
L_4ee947:
    eax = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
L_4ee956:
    lift_store(&env, ecx, 0xcu, 4, 0x0u);
    eax = lift_load(&env, ecx, 0x14u, 4);
    lift_store(&env, ecx, 0x10u, 4, 0x0u);
    eax = lift_call(&env, 0x4e2400u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x14u, 4, 0x0u);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE980_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE980_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x30u, &fl);
        esp = r;
    }
    ecx = eax;
    {
        (void)lift_and(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4ee9af;
    lift_store(&env, esp, 0x20u, 4, 0x1u);
    edx = 0x51c2f0u;
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    goto L_4eea13;
L_4ee9af:
    lift_store(&env, eax, 0x0u, 4, 0x51c2d4u);
    lift_store(&env, esp, 0x24u, 4, eax);
    eax = (esp + 0x14u);
    lift_store(&env, esp, 0x28u, 1, (edx & 0xffu));
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
    lift_store(&env, esp, 0x1cu, 4, 0x51c278u);
    eax = ecx;
    lift_store(&env, esp, 0x20u, 4, 0x3u);
    eax = lift_call(&env, 0x4ee910u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    {
        (void)lift_and(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4eea09;
    eax = ecx;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
L_4eea09:
    eax = lift_load(&env, esp, 0x14u, 4);
    env.chain = eax;
L_4eea13:
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x30u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eea20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EEA20_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EEA20_STACK, 0, entry);
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
    ebx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4eea60;
    {
        uint32_t v = 0x10u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x18u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, 0x14u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4e23e0u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    ecx = lift_load(&env, ebx, 0x18u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    edx = ecx;
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = ecx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4eea60;
L_4eea4e:
    ecx = lift_load(&env, ebx, 0x10u, 4);
    lift_store(&env, eax, 0x0u, 4, ecx);
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    lift_store(&env, ebx, 0x10u, 4, eax);
    {
        uint32_t r = lift_sub(32, eax, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4eea4e;
L_4eea60:
    esi = lift_load(&env, ebx, 0x10u, 4);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, ebx, 0x10u, 4, eax);
    {
        uint32_t a = lift_load(&env, ebx, 0xcu, 4);
        uint32_t r = lift_inc(32, a, &fl, 1);
        lift_store(&env, ebx, 0xcu, 4, r);
    }
    eax = lift_call(&env, 0x4ca060u, eax, edx, ebx, ecx, 0, esp);
    ebx = 0x4u;
    ecx = (esi + 0x8u);
    edx = eax;
    eax = ecx;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
    eax = esi;
    lift_store(&env, esi, 0xcu, 4, 0x0u);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eea90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EEA90_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EEA90_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    edi = eax;
    esi = edx;
    eax = edx;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4eeab8;
L_4eeaa3:
    edx = ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, ecx, edx, &fl);
        ecx = r;
    }
    edx = (uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x0u, 1);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, ecx, edx, &fl);
        ecx = r;
    }
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4eeaa3;
L_4eeab8:
    eax = lift_load(&env, edi, 0x8u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = ecx;
    lift_div1(32, lift_load(&env, esp, 0x0u, 4), &eax, &edx, &fl);
    lift_store(&env, ebx, 0x0u, 4, edx);
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4eeaf5;
    eax = edx;
    ecx = lift_load(&env, edi, 0x4u, 4);
    ecx = lift_load(&env, ecx, (eax * 4u) + 0x0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4eeae1;
    goto L_4eeaf5;
L_4eeadb:
    ecx = lift_load(&env, ecx, 0x0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4eeaf5;
L_4eeae1:
    eax = (ecx + 0x8u);
    edx = esi;
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, 0x4e1982u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4eeadb;
    eax = ecx;
    goto L_4eeaf7;
L_4eeaf5:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4eeaf7:
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
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
    return env.failed ? 0u : eax;
}
