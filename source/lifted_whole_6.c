/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_6.h"

uint32_t lifted_f4e8abc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8ABC_STACK + 4 + 4 * 1 + 4];
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e8ace:
    eax = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8ae1;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e8ae1:
    eax = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8cc8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e8b0a;
L_4e8aed:
    eax = 0x7u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8b00;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e8b00:
    eax = 0x7u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8cc8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e8b19:
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8b24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8B24_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8B24_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x7u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8cc8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8CC8_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8CC8_STACK, 0, entry);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebx + 0xffffffffu);
    ecx = eax;
    {
        (void)lift_sub(32, edx, 0xbu, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e8d29;
    {
        uint32_t i = edx;
        switch (i)
        {
            case 0:
                goto L_4e8cf0;
            case 1:
                goto L_4e8ce4;
            case 2:
                goto L_4e8cfa;
            case 3:
                goto L_4e8cfa;
            case 4:
                goto L_4e8cfa;
            case 5:
                goto L_4e8cfa;
            case 6:
                goto L_4e8cfa;
            case 7:
                goto L_4e8cfa;
            case 8:
                goto L_4e8cfa;
            case 9:
                goto L_4e8cfa;
            case 10:
                goto L_4e8cfa;
            case 11:
                goto L_4e8cfa;
            default:
                return 0u;
        }
    }
L_4e8ce4:
    eax = 0x8cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8bd4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e8d32;
L_4e8cf0:
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e8cfa;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea2a8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e8cfa:
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e8d19;
    {
        (void)lift_sub(32, ecx, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e8d19;
    {
        (void)lift_sub(32, ecx, 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4e8d19;
    edx = 0x2u;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8a10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ecx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e8d19:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8b24u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8d32;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8b8cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e8d32;
L_4e8d29:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e8d32:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8d80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8D80_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8D80_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8b24u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e8dad;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8b8cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x2u;
    eax = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8a10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x2u;
    eax = 0x7u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8a10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e8dad:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8dcb(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8DCB_STACK + 4 + 4 * 0 + 4];
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
    esp = esp - 0x1cu;
    ecx = eax;
    ebp = lift_load(&env, eax, 0x4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x25u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1u) & 0xffu);
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
    ebx = ebx + eax;
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
    edi = edi ^ edi;
    esi = esi ^ esi;
L_4e8e17:
    eax = lift_load(&env, esp, 0x14u, 4);
    eax = eax + 1u;
    lift_store(&env, esp, 0x10u, 4, eax);
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0x0u, 4), &fl);
    }
    if (fl.cf)
        goto L_4e8e43;
    lift_store(&env, esp, 0x4u, 4, lift_load(&env, esp, 0x4u, 4) + 0x4u);
    lift_store(&env, esp, 0x14u, 4, eax);
    goto L_4e8e00;
L_4e8e30:
    eax = lift_load(&env, esp, 0x14u, 4);
    eax = eax + 1u;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e8e3d:
    esi = esi + 0x8u;
    edi = edi + 1u;
    goto L_4e8e17;
L_4e8e43:
    eax = lift_load(&env, esp, 0xcu, 4);
    eax = eax + esi;
    lift_store(&env, ecx, 0x14u, 4, eax);
    ebx = lift_load(&env, esp, 0x8u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_load(&env, esp, 0x18u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3846u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e8e3d;
    eax = lift_load(&env, esp, 0x10u, 4);
    goto L_4e8e35;
L_4e8e65:
    eax = eax ^ eax;
    goto L_4e8e35;
}

uint32_t lifted_f4e8e69(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8E69_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8dcbu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e8e90:
    {
        (void)lift_sub(32, lift_load(&env, ecx, (eax * 4u) + 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e8e7f;
    eax = eax ^ eax;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8dcbu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8fa7(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8FA7_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8FA7_STACK, 0, entry);
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
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e8fd1;
L_4e8faf:
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, ecx, 0x0u, 4, edx);
    lift_store(&env, eax, 0x4u, 4, edx);
    ebx = lift_load(&env, edx, 0x8u, 4);
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_load(&env, ecx, 0x8u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e8fd8;
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4e8fdd;
            case 1:
                goto L_4e8fe7;
            case 2:
                goto L_4e8fe7;
            case 3:
                goto L_4e8fd8;
            case 4:
                goto L_4e8fe7;
            default:
                return 0u;
        }
    }
L_4e8fd1:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e8faf;
L_4e8fd8:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e8fdd:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8ecau, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_4e8fe7:
    {
        uint32_t r = lift_xor(8, (eax & 0xffu), (eax & 0xffu), &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
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

uint32_t lifted_f4e8ff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8FF0_STACK + 4 + 4 * 0 + 4];
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
    ebx = ebx ^ ebx;
L_4e8ff6:
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7b50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e900d;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3a90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx + 1u;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9020_STACK + 4 + 4 * 0 + 4];
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
    edx = edx & 0xffu;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x5c8961u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x1u) & 0xffu);
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4e905b;
    eax = eax & 0xffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9060_STACK + 4 + 4 * 0 + 4];
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
    edx = edx ^ edx;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9194(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9194_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e91b8:
    if (fl.sf != fl.of)
        goto L_4e91d9;
L_4e91ba:
    edx = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e909cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edx = ebx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e909cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e91e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E91E0_STACK + 4 + 4 * 0 + 4];
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
    esp = esp - 0x1cu;
    ecx = eax;
    eax = lift_load(&env, 0u, 0x50b0d8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    esi = esi ^ esi;
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e948c;
    edx = 0x50afacu;
    eax = 0x50af88u;
    ebx = lift_load(&env, ecx, 0x14u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9194u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    eax = eax + 0x76cu;
    ebp = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    eax = eax - edx;
    lift_store(&env, esp, 0x10u, 4, eax);
    edx = edx ^ edx;
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
    edx = edx + 0x7u;
    edx = edx - eax;
    lift_store(&env, esp, 0x18u, 4, 0x7u);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x18u, 4), &eax, &edx, &fl);
    eax = lift_load(&env, ecx, 0xcu, 4);
    eax = eax - edx;
    edx = lift_load(&env, ecx, 0x18u, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    edx = edx + 0x6u;
    edx = edx - lift_load(&env, edi, 0x18u, 4);
    lift_store(&env, esp, 0x18u, 4, 0x7u);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x18u, 4), &eax, &edx, &fl);
    eax = lift_load(&env, ecx, 0xcu, 4);
    eax = eax - 1u;
    eax = eax - edx;
    edx = lift_load(&env, edi, 0xcu, 4);
    lift_store(&env, esp, 0xcu, 4, eax);
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_4e930b;
    eax = lift_load(&env, esp, 0x10u, 4);
    edx = lift_load(&env, esp, 0x8u, 4);
    eax = eax - 0x7u;
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
    edx = edx - eax;
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
    eax = eax + 0x76cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    edx = edx + 1u;
L_4e9355:
    edx = edx - 1u;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e949cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    esi = eax;
    esi = esi & 0xffu;
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
    edx = edx ^ edx;
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
    esi = esi ^ esi;
    goto L_4e946d;
L_4e93b6:
    if (!fl.zf)
        goto L_4e946d;
    edx = lift_load(&env, ecx, 0x18u, 4);
    edi = lift_load(&env, ebx, 0x18u, 4);
    edx = edx + 0x7u;
    edx = edx - edi;
    edi = 0x7u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    ebp = lift_load(&env, ecx, 0xcu, 4);
    ebp = ebp - edx;
    edx = lift_load(&env, ecx, 0x18u, 4);
    eax = lift_load(&env, ebx, 0x18u, 4);
    edx = edx + 0x6u;
    edx = edx - eax;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    eax = lift_load(&env, ecx, 0xcu, 4);
    eax = eax - 1u;
    eax = eax - edx;
    edx = lift_load(&env, ebx, 0xcu, 4);
    esi = esi ^ esi;
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_4e9417;
    edx = lift_load(&env, esp, 0x10u, 4);
    edx = edx - edi;
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
    edx = edx - edi;
    edx = edx + 1u;
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
    eax = eax + 0x76cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    edi = edi + ebp;
L_4e945f:
    edi = edi - 1u;
L_4e9460:
    eax = lift_load(&env, ecx, 0x1cu, 4);
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e946d;
    esi = esi ^ esi;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e949cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
L_4e947e:
    ebp = lift_load(&env, esp, 0x14u, 4);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4e948c;
    eax = ebp;
    eax = eax - esi;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e949c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E949C_STACK + 4 + 4 * 0 + 4];
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
    ebx = ebx ^ ebx;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9670_STACK + 4 + 4 * 0 + 4];
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
    edx = edx ^ edx;
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
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = eax + 1u;
    edx = edx + ebx;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, eax, 0x0u, 1)) & 0xffu) << 8);
    edx = edx - 0x30u;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9980_STACK + 4 + 4 * 0 + 4];
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
    ebp = ebp ^ ebp;
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
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) & 0xf8u) & 0xffu);
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
    ebx = ebx ^ ebx;
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
    ebx = ebx + 1u;
    edx = edx - ecx;
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
    lift_store(&env, edi, 0x1cu, 4, lift_load(&env, edi, 0x1cu, 4) - 1u);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9c94(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9C94_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9C94_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8660u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9bd8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9ca8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9CA8_STACK + 4 + 4 * 0 + 4];
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
    eax = eax + 0x7u;
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xf8u) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9cf4;
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = eax + 0x3cu;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e9cc5:
    ecx = lift_load(&env, 0u, 0x50b218u, 4);
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.cf)
        goto L_4e9cd3;
    eax = ecx;
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfeu) & 0xffu);
L_4e9cd3:
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = eax + 0xfffu;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e9ce3:
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) & 0xf0u) & 0xffu) << 8);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9D10_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b98u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9F00_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ea536;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea13c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA13C_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA13C_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x50b208u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea144(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA144_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA144_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x50b20cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA190_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA190_STACK, 0, entry);
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
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ea291;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, 0u, 0x5c8ad0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea1ee;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea1be;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea1be:
    edx = ecx;
    ecx = lift_load(&env, ecx, 0x4u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea1d7;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea1d7;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea1d7:
    ecx = lift_load(&env, edx, 0x8u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea1ee;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea1ee;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea1ee:
    ecx = lift_load(&env, 0u, 0x50af00u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea22c;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea204;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea204:
    edx = ecx;
    ecx = lift_load(&env, ecx, 0x4u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea219;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea219;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea219:
    ecx = lift_load(&env, edx, 0x8u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea22c;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea22c;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea22c:
    ecx = lift_load(&env, 0u, 0x50aefcu, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea28b;
L_4ea236:
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea242;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea242:
    ecx = lift_load(&env, ecx, 0x8u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4ea236;
    goto L_4ea28b;
L_4ea24b:
    eax = 0x50aefcu;
    edx = 0u;
    edx = edx & 0xffffu;
    ebx = ecx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9a30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x50af00u, 4);
    lift_store(&env, 0u, 0x5c8ad0u, 4, ecx);
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.cf)
        goto L_4ea283;
    ebx = lift_load(&env, 0u, 0x50af04u, 4);
    eax = lift_load(&env, ecx, 0x14u, 4);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ea283;
    lift_store(&env, 0u, 0x50af04u, 4, eax);
L_4ea283:
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5c8ac0u, 1, ((eax >> 8) & 0xffu));
L_4ea28b:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cc0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ea291:
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

uint32_t lifted_f4ea2a8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA2A8_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA2A8_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0xffu;
    eax = 0x5130c4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e628cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA310_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA310_STACK, 0, entry);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c8950u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ea342;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x50a820u, 4), 0x3a4u, &fl);
    }
    if (fl.zf)
        goto L_4ea32f;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ea344;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ea32f:
    eax = eax & 0xffu;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x50b2a9u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x8u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ea342:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4ea344:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA350_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA350_STACK, 0, entry);
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
    esp = esp - 0xcu;
    lift_store(&env, esp, 0x4u, 4, eax);
    ebp = edx;
    lift_store(&env, esp, 0x0u, 4, ebx);
    ebx = ebx ^ ebx;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ea3db;
L_4ea36a:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ea3fd;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, ebp, 0x0u, 2)) & 0xffffu);
    {
        (void)lift_and(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4ea39d;
    edx = edx ^ edx;
    eax = (esp + 0x8u);
    edx = (edx & 0xffff0000u) | (((ecx & 0xffffu)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e62e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4ea3ff;
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x0u, 4), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea3fd;
    goto L_4ea3a6;
L_4ea39d:
    eax = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x0u, 1, 0x0u);
    goto L_4ea3fd;
L_4ea3a6:
    esi = (esp + 0x8u);
    edi = lift_load(&env, esp, 0x4u, 4);
    ecx = eax;
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
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
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
    ebp = ebp + 0x2u;
    ebx = ebx + edx;
    eax = lift_load(&env, esp, 0x0u, 4);
    edi = edi + edx;
    eax = eax - edx;
    lift_store(&env, esp, 0x4u, 4, edi);
    lift_store(&env, esp, 0x0u, 4, eax);
    goto L_4ea36a;
L_4ea3db:
    {
        (void)lift_sub(16, lift_load(&env, ebp, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ea3fd;
    edx = edx ^ edx;
    eax = (esp + 0x8u);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0x0u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e62e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4ea3ff;
    ebp = ebp + 0x2u;
    ebx = ebx + eax;
    goto L_4ea3db;
L_4ea3fd:
    eax = ebx;
L_4ea3ff:
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
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

uint32_t lifted_f4ea410(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA410_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ba8u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ea429;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e081cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea450(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA450_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c64u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ea465;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA540_STACK + 4 + 4 * 0 + 4];
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
    esp = esp - 0x10u;
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
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) + 1u) & 0xffu);
    eax = eax & 0xffu;
    {
        (void)lift_and(8, lift_load(&env, eax, 0x507d58u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ea573;
    edx = edx + 1u;
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
    edx = edx + 1u;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
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
    edx = edx + 0x2u;
L_4ea5e5:
    lift_store(&env, esp, 0x0u, 4, edx);
    ebp = ((esi * 4u));
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) ^ (ecx & 0xffu)) & 0xffu);
    ebx = ebx ^ ebx;
L_4ea5f3:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea6b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    ebx = ebx + edi;
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (!fl.cf)
        goto L_4ea619;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
L_4ea619:
    edx = edx + 1u;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ea683:
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ea68a;
    ebx = 0u - ebx;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea6a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA6A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA6A0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea6b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA6B0_STACK + 4 + 4 * 0 + 4];
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
    eax = eax & 0xffu;
    {
        uint32_t r = lift_sub(32, eax, 0x30u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ea6c3:
    eax = eax & 0xffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e82f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    eax = eax ^ eax;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    eax = eax & 0xffu;
    {
        uint32_t r = lift_sub(32, eax, 0x57u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    eax = eax & 0xffu;
    {
        uint32_t r = lift_sub(32, eax, 0x57u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ea704:
    eax = 0x25u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea8cc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA8CC_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA8CC_STACK, 0, entry);
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
    esp = esp - 0xcu;
    lift_store(&env, esp, 0x4u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ea8e7;
    eax = 0xffffffffu;
    goto L_4eaa70;
L_4ea8e7:
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ea901;
    edx = (eax + 0x1u);
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ea901;
L_4ea8f4:
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x3du, &fl);
    }
    if (fl.zf)
        goto L_4ea901;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x1u, 1)) & 0xffu);
    edx = edx + 1u;
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4ea8f4;
L_4ea901:
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ea915;
    eax = 0xffffffffu;
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ea915:
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x1u, 1), 0x0u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    ebp = (eax & 0xffu);
    eax = lift_load(&env, 0u, 0x5c81d4u, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ea96d;
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4eaa70;
    eax = 0x9u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ea955;
    eax = 0xffffffffu;
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ea955:
    lift_store(&env, 0u, 0x5c81d4u, 4, eax);
    eax = eax + 0x8u;
    lift_store(&env, eax, 0xfffffff8u, 4, ebp);
    lift_store(&env, eax, 0xfffffffcu, 4, ebp);
    lift_store(&env, 0u, 0x5c81d0u, 4, eax);
    goto L_4eaa52;
L_4ea96d:
    eax = lift_load(&env, esp, 0x4u, 4);
    edx = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eaa7cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4eaa6e;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4eaa4f;
    ebp = eax;
    ebp = 0u - ebp;
    ebx = (ebp + 0x1u);
    ecx = ((ebp * 4u));
    eax = (ecx + 0x8u);
    esi = lift_load(&env, 0u, 0x5c81d0u, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = eax + ebx;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4ea9f7;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ea9c6;
    eax = 0xffffffffu;
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ea9c6:
    esi = lift_load(&env, 0u, 0x5c81d4u, 4);
    edi = eax;
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
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
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
    eax = lift_load(&env, esp, 0x0u, 4);
    eax = eax + edx;
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5c81d0u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4eaa33;
L_4ea9f7:
    edx = eax;
    eax = lift_load(&env, esp, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4eaa19;
    eax = 0xffffffffu;
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4eaa19:
    ecx = lift_load(&env, esp, 0x0u, 4);
    edx = lift_load(&env, 0u, 0x5c81d0u, 4);
    ecx = ecx + eax;
    ebx = ebp;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5c81d0u, 4, ecx);
L_4eaa33:
    edi = lift_load(&env, esp, 0x8u, 4);
    eax = ((ebp * 4u));
    eax = eax + edi;
    lift_store(&env, 0u, 0x5c81d4u, 4, edi);
    lift_store(&env, eax, 0x4u, 4, 0x0u);
    goto L_4eaa52;
L_4eaa4f:
    ebp = (eax + 0xffffffffu);
L_4eaa52:
    edx = lift_load(&env, esp, 0x8u, 4);
    eax = ((ebp * 4u));
    eax = eax + edx;
    edx = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
    eax = lift_load(&env, 0u, 0x5c81d0u, 4);
    lift_store(&env, eax, ebp + 0x0u, 1, 0x0u);
L_4eaa6e:
    eax = eax ^ eax;
L_4eaa70:
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eaa7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EAA7C_STACK + 4 + 4 * 0 + 4];
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
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dabb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dabb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    edi = edi - edx;
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
    ecx = ecx + 0x4u;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4eab06:
    ebp = lift_load(&env, 0u, 0x5c81d4u, 4);
    esi = ecx;
    esi = esi - ebp;
    edx = lift_load(&env, 0u, 0x5c81d0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        esi = r;
    }
    eax = ecx;
    ebx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5c81d0u, 4, ecx);
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4eab3a;
    eax = (edi + ecx);
L_4eab2f:
    eax = eax + 1u;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edi = edi + 1u;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4eab4b:
    edx = edx + 1u;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebx, 0x1u, 1)) & 0xffu);
    ebx = ebx + 1u;
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4eaa9c;
L_4eab58:
    esi = esi + 0x4u;
L_4eab5b:
    edx = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4eaa90;
    eax = lift_load(&env, 0u, 0x5c81d4u, 4);
    eax = eax - esi;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eada0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EADA0_STACK + 4 + 4 * 0 + 4];
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
    edi = edi ^ edi;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8230u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4eadd1:
    lift_store(&env, esi, 0x0u, 2, 0x0u);
    goto L_4eae0e;
L_4eadd8:
    eax = ecx;
    ebp = ebp - 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3a90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = esi + 0x2u;
    edi = edi + 1u;
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
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8230u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4eae10;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3a90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi + 1u;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eafb8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EAFB8_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EAFB8_STACK, 0, entry);
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
    esp = esp - 0x8u;
    edi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4eafd1;
    eax = 0xffffffffu;
    goto L_4eb134;
L_4eafd1:
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4eaff2;
    edx = (eax + 0x2u);
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4eaff2;
L_4eafe0:
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x0u, 2), 0x3du, &fl);
    }
    if (fl.zf)
        goto L_4eaff2;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, edx, 0x2u, 2)) & 0xffffu);
    edx = edx + 0x2u;
    {
        (void)lift_and(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4eafe0;
L_4eaff2:
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x0u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4eb007;
    eax = 0xffffffffu;
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
L_4eb007:
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x2u, 2), 0x0u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    ebx = ebx ^ ebx;
    ecx = lift_load(&env, 0u, 0x5c81d8u, 4);
    ebx = (ebx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4eb05e;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4eb132;
    eax = 0x9u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4eb044;
    eax = 0xffffffffu;
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
L_4eb044:
    lift_store(&env, 0u, 0x5c81d8u, 4, eax);
    eax = eax + 0x8u;
    lift_store(&env, eax, 0xfffffff8u, 4, ebx);
    esi = esi ^ esi;
    lift_store(&env, eax, 0xfffffffcu, 4, ebx);
    lift_store(&env, 0u, 0x5c81d0u, 4, eax);
    goto L_4eb126;
L_4eb05e:
    edx = ebx;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4eb132;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4eb123;
    eax = 0u - eax;
    ebp = lift_load(&env, 0u, 0x5c81d0u, 4);
    esi = eax;
    eax = eax + 1u;
    ebx = ((esi * 4u));
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = (ebx + 0x8u);
    edx = lift_load(&env, esp, 0x0u, 4);
    lift_store(&env, esp, 0x4u, 4, eax);
    eax = eax + edx;
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4eb0da;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4eb0b8;
    eax = 0xffffffffu;
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
L_4eb0b8:
    edx = lift_load(&env, 0u, 0x5c81d8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0x4u, 4);
    ebx = lift_load(&env, esp, 0x0u, 4);
    eax = eax + ebp;
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5c81d0u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4eb113;
L_4eb0da:
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4eb0f8;
    eax = 0xffffffffu;
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
L_4eb0f8:
    ebp = lift_load(&env, esp, 0x4u, 4);
    edx = lift_load(&env, 0u, 0x5c81d0u, 4);
    ebp = ebp + eax;
    ebx = esi;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5c81d0u, 4, ebp);
L_4eb113:
    lift_store(&env, 0u, 0x5c81d8u, 4, ecx);
    lift_store(&env, ecx, (esi * 4u) + 0x4u, 4, 0x0u);
    goto L_4eb126;
L_4eb123:
    esi = (eax + 0xffffffffu);
L_4eb126:
    eax = lift_load(&env, 0u, 0x5c81d0u, 4);
    lift_store(&env, ecx, (esi * 4u) + 0x0u, 4, edi);
    lift_store(&env, esi, eax + 0x0u, 1, 0x0u);
L_4eb132:
    eax = eax ^ eax;
L_4eb134:
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

uint32_t lifted_f4eb140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB140_STACK + 4 + 4 * 0 + 4];
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
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb400u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x0u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb400u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    edi = edi - edx;
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
    ecx = ecx + 0x4u;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4eb1d0:
    ebp = lift_load(&env, 0u, 0x5c81d8u, 4);
    esi = ecx;
    esi = esi - ebp;
    edx = lift_load(&env, 0u, 0x5c81d0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        esi = r;
    }
    eax = ecx;
    ebx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5c81d0u, 4, ecx);
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4eb204;
    eax = (edi + ecx);
L_4eb1f9:
    eax = eax + 1u;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edi = edi + 1u;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4eb215:
    edx = edx + 0x2u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x2u, 2)) & 0xffffu);
    ebx = ebx + 0x2u;
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4eb162;
L_4eb228:
    esi = esi + 0x4u;
L_4eb22b:
    edx = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4eb154;
    eax = lift_load(&env, 0u, 0x5c81d8u, 4);
    eax = eax - esi;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB250_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB250_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb410u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB270_STACK + 4 + 4 * 0 + 4];
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
    eax = eax + 0x2u;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb2a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB2A0_STACK + 4 + 4 * 0 + 4];
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
    esp = esp - 0x4u;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c98u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    goto L_4eb389;
L_4eb2c6:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax + eax;
    ecx = (eax + 0x1u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    esi = esi ^ esi;
    goto L_4eb316;
L_4eb2eb:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax + eax;
    ecx = (eax + 0x1u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4eb316;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
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
L_4eb316:
    edx = lift_load(&env, esp, 0x0u, 4);
    ebx = ecx;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4eb344;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb339;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4eb339:
    eax = eax ^ eax;
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
L_4eb344:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb36a;
    ebx = ecx;
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4eb36a;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c94u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    edx = eax;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb387;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB3A0_STACK + 4 + 4 * 0 + 4];
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
    esi = esi + 0x4u;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4eb3ef;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8ff0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (eax + 0x1u);
    eax = ((ebx * 2u));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4eb3ae;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eada0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4eb3e6;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eafb8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4eb3ae;
L_4eb3e6:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB400_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB400_STACK, 0, entry);
    {
        (void)lift_sub(16, (eax & 0xffffu), 0x61u, &fl);
    }
    if (fl.cf)
        goto L_4eb40f;
    {
        (void)lift_sub(16, (eax & 0xffffu), 0x7au, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4eb40f;
    {
        uint32_t r = lift_sub(32, eax, 0x20u, &fl);
        eax = r;
    }
L_4eb40f:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb4d4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB4D4_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x50b3acu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5c7b90u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4eb4f6;
    edx = 0xffu;
    eax = 0x10u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6bacu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4eb4f6:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb526(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB526_STACK + 4 + 4 * 0 + 4];
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
    edx = edx | 0x7ff00000u;
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
    eax = eax ^ edx;
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx - ecx;
L_4eb553:
    ecx = ecx + 0x800000u;
    edx = edx + edx;
    {
        (void)lift_and(32, edx, 0x800000u, &fl);
    }
    if (fl.zf)
        goto L_4eb553;
    eax = eax | edx;
    edx = edx - ecx;
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
    eax = eax & 0xeu;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb57c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB57C_STACK + 4 + 4 * 0 + 4];
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
    edx = edx - edx;
L_4eb587:
    {
        (void)lift_and(32, ecx, 0x7ff00000u, &fl);
    }
    if (!fl.zf)
        goto L_4eb591;
    ecx = ecx - ecx;
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
    edx = edx ^ ecx;
L_4eb5a8:
    {
        uint32_t r = lift_add(32, edx, edx, &fl);
        edx = r;
    }
    ebp = ebp - 0x0u - fl.cf;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_rtl_single_negate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_SINGLE_NEGATE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_SINGLE_NEGATE_STACK, 0, entry);
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4eb5bd;
    {
        uint32_t r = lift_xor(32, eax, 0x80000000u, &fl);
        eax = r;
    }
L_4eb5bd:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb5c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB5C0_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb606(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB606_STACK + 4 + 4 * 0 + 4];
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
    ebx = ebx - ebx;
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
    edx = edx - 0x70000000u;
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    edx = edx + edx + fl.cf;
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    edx = edx + edx + fl.cf;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB860_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB860_STACK, 0, entry);
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
    if (fl.zf)
        goto L_4eb877;
L_4eb868:
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4eb877;
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
    lift_store(&env, eax, 0xffffffffu, 1, (ecx & 0xffu));
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4eb868;
L_4eb877:
    edx = edx ^ edx;
L_4eb879:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4eb884;
    eax = eax + 1u;
    ebx = ebx - 1u;
    lift_store(&env, eax, 0xffffffffu, 1, (edx & 0xffu));
    goto L_4eb879;
L_4eb884:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb892(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB892_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB892_STACK, 0, entry);
    eax = (eax & 0xffffff00u) | ((0x1fu) & 0xffu);
    goto L_4eb898;
L_4eb898:
    {
        uint32_t r = lift_add(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t a = ((eax >> 8) & 0xffu);
        uint32_t r = lift_rcr(8, a, 0x1u, &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    {
        uint32_t a = ((eax >> 8) & 0xffu);
        uint32_t r = lift_shr(8, a, 0x1u, &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) | (eax & 0xffu)) & 0xffu) << 8);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = edx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x14u, &fl);
        ecx = r;
    }
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) & 0x7ffu) & 0xffffu);
    {
        uint32_t r = lift_sub(16, (ecx & 0xffffu), 0x3feu, &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.sf != fl.of)
        goto L_4eb907;
    {
        (void)lift_sub(16, (ecx & 0xffffu), 0x20u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4eb900;
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x3fu) & 0xffu);
    {
        (void)lift_sub(8, (ecx & 0xffu), (eax & 0xffu), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4eb900;
    ecx = (ecx & 0xffff00ffu) | (((((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx & 0xfffffu;
    eax = eax & 0xfff00000u;
    {
        uint32_t r = lift_or(32, edx, eax, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_rol(32, a, 0xcu, &fl);
        edx = r;
    }
    fl.cf = 1;
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = ((ecx >> 8) & 0xffu);
        uint32_t r = lift_rcr(8, a, 0x1u, &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4eb8e2;
    eax = edx;
    {
        uint32_t r = lift_add(8, ((ecx >> 8) & 0xffu), ((ecx >> 8) & 0xffu), &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    goto L_4eb8ed;
L_4eb8e2:
    eax = eax - eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shld(32, a, edx, (ecx & 0xffu), &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        edx = r;
    }
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + ((ecx >> 8) & 0xffu)) & 0xffu) << 8);
    {
        uint32_t r = lift_add(32, edx, edx, &fl);
        edx = r;
    }
L_4eb8ed:
    ecx = (ecx & 0xffffff00u) | ((0xffu) & 0xffu);
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_rcr(8, a, 0x1u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) & (ecx & 0xffu)) & 0xffu) << 8);
    {
        uint32_t r = lift_add(8, ((ecx >> 8) & 0xffu), ((ecx >> 8) & 0xffu), &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    eax = eax + 0x0u + fl.cf;
    {
        uint32_t r = lift_add(8, ((ecx >> 8) & 0xffu), ((ecx >> 8) & 0xffu), &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    if (!fl.cf)
        goto L_4eb8fe;
    {
        uint32_t a = eax;
        uint32_t r = lift_sub(32, 0, a, &fl);
        eax = r;
    }
L_4eb8fe:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4eb900:
    eax = 0x80000000u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4eb907:
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
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

uint32_t lifted_f4eb910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB910_STACK + 4 + 4 * 0 + 4];
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
    esp = esp - 0x4u;
    ecx = eax;
    esi = edx;
    edx = 0x1u;
    ebx = ebx ^ ebx;
    edi = edi ^ edi;
    ebp = ebp ^ ebp;
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
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | 0x1u) & 0xffu);
    goto L_4eb970;
L_4eb955:
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | 0x2u) & 0xffu);
    goto L_4eb970;
L_4eb95a:
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | 0x82u) & 0xffu);
    goto L_4eb970;
L_4eb95f:
    eax = 0x9u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    goto L_4eba3f;
L_4eb970:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0x1u, 1)) & 0xffu) << 8);
    ecx = ecx + 1u;
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
    edx = edx ^ edx;
    goto L_4eba1e;
L_4eb9c7:
    eax = 0x1u;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | 0x3u) & 0xffu);
    lift_store(&env, esp, 0x0u, 4, eax);
    goto L_4eba1e;
L_4eb9d4:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4eb9dc;
    edx = edx ^ edx;
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
    edx = edx ^ edx;
    goto L_4eba1e;
L_4eb9eb:
    edi = 0x1u;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | 0x40u) & 0xffu);
    goto L_4eba1e;
L_4eb9f5:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4eb9fd;
    edx = edx ^ edx;
    goto L_4eba1e;
L_4eb9fd:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) | 0x1u) & 0xffu);
    ebp = 0x1u;
    lift_store(&env, esi, 0x0u, 1, (eax & 0xffu));
    goto L_4eba1e;
L_4eba0a:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4eba12;
    edx = edx ^ edx;
    goto L_4eba1e;
L_4eba12:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esi, 0x0u, 1)) & 0xffu) << 8);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) & 0xfeu) & 0xffu) << 8);
    ebp = 0x1u;
    lift_store(&env, esi, 0x0u, 1, ((eax >> 8) & 0xffu));
L_4eba1e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1u, 1)) & 0xffu);
    ecx = ecx + 1u;
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
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | 0x40u) & 0xffu);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eba4c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBA4C_STACK + 4 + 4 * 2 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EBA4C_STACK, 2, entry);
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
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    edx = ecx;
    ecx = lift_load(&env, esp, 0x14u, 4);
    lift_store(&env, ecx, 0xcu, 1, lift_load(&env, ecx, 0xcu, 1) & 0xfcu);
    lift_store(&env, ecx, 0xcu, 4, lift_load(&env, ecx, 0xcu, 4) | ebx);
    eax = eax & 0xffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e82f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x72u, &fl);
    }
    if (!fl.zf)
        goto L_4eba90;
    eax = eax ^ eax;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4eba7a;
    eax = 0x2u;
L_4eba7a:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4eba84;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) | 0x2u) & 0xffu) << 8);
    goto L_4eba87;
L_4eba84:
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) | 0x1u) & 0xffu) << 8);
L_4eba87:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    goto L_4ebac0;
L_4eba90:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x1u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    eax = eax + 0x21u;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4ebaa7;
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) | 0x10u) & 0xffu);
    goto L_4ebaa9;
L_4ebaa7:
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) | 0x40u) & 0xffu);
L_4ebaa9:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4ebab3;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) | 0x2u) & 0xffu) << 8);
    goto L_4ebab6;
L_4ebab3:
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) | 0x1u) & 0xffu) << 8);
L_4ebab6:
    {
        uint32_t v = 0x180u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4ebac0:
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
    eax = lift_call(&env, 0x4cd544u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0x10u;
    lift_store(&env, ecx, 0x10u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x10u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ebade;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7e44u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    goto L_4ebb2c;
L_4ebade:
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, ecx, 0x14u, 4, 0x0u);
    lift_store(&env, eax, 0xcu, 4, 0x0u);
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, eax, 0x10u, 4, edx);
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, eax, 0x15u, 4, 0x0u);
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, eax, 0x8u, 4, 0x0u);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4ebb23;
    ebx = 0x2u;
    eax = ecx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ebce8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ebb23:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7bf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
L_4ebb2c:
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

uint32_t lifted_f4ebb78(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBB78_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EBB78_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ebb34u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebb84(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBB84_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7fc4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ebbb1:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ebbf0:
    edx = eax;
    goto L_4ebbc8;
L_4ebbf4:
    eax = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebc90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBC90_STACK + 4 + 4 * 0 + 4];
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
    ebx = ebx - ecx;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ebcc5;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, 0xcu, 1)) & 0xffu);
    esi = lift_load(&env, edx, 0x0u, 4);
    edi = lift_load(&env, edx, 0x4u, 4);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) & 0xefu) & 0xffu);
    esi = esi + eax;
    lift_store(&env, edx, 0xcu, 1, (ebx & 0xffu));
    edi = edi - eax;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebcd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBCD0_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebce8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBCE8_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3ce0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ebd27:
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ebd39:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4ebd41;
    esi = esi - lift_load(&env, ecx, 0x4u, 4);
L_4ebd41:
    eax = lift_load(&env, ecx, 0x8u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    lift_store(&env, ecx, 0x0u, 4, eax);
L_4ebd50:
    lift_store(&env, ecx, 0xcu, 1, lift_load(&env, ecx, 0xcu, 1) & 0xebu);
    edx = esi;
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0150u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ebe4b;
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ebc90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ebe4b;
    edx = esi;
    eax = lift_load(&env, ecx, 0x10u, 4);
    edx = edx - edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0150u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ebdc8;
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ebdc8:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ebcd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4ebe4b;
L_4ebdd4:
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ecx, 0x4u, 4);
    edi = esi;
    eax = eax - edx;
    edi = edi - eax;
    edx = ecx;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ebc90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ebe4b;
    edx = esi;
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0150u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ebdc8;
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ebe13:
    edx = (edx & 0xffffff00u) | ((((eax >> 8) & 0xffu)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xefu) & 0xffu);
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, ecx, 0xcu, 1, (edx & 0xffu));
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    edx = esi;
    eax = lift_load(&env, ecx, 0x10u, 4);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0150u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ebe4b;
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ebe4b:
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebe60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBE60_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dabd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ebe79:
    eax = lift_load(&env, edx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4ebeb4;
    eax = lift_load(&env, edx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    ecx = ecx - esi;
L_4ebea9:
    eax = lift_load(&env, edx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebec0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBEC0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EBEC0_STACK, 0, entry);
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
    lift_store(&env, esp, 0x0u, 4, eax);
    lift_store(&env, esp, 0x4u, 4, edx);
    ebp = ecx;
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(8, lift_load(&env, ecx, 0xcu, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4ebf01;
    eax = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ecx, 0xcu, 1)) & 0xffu) << 8);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) | 0x20u) & 0xffu) << 8);
    eax = lift_load(&env, ecx, 0x10u, 4);
    lift_store(&env, ecx, 0xcu, 1, ((edx >> 8) & 0xffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    goto L_4ec0ca;
L_4ebf01:
    {
        uint32_t r = lift_imul(32, ebx, edx, &fl);
        ebx = r;
    }
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4ebf1a;
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_4ebf1a:
    eax = lift_load(&env, ecx, 0x8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ebf2a;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3b60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ebf2a:
    esi = esi ^ esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xcu, 1)) & 0xffu);
    lift_store(&env, esp, 0x8u, 4, esi);
    {
        (void)lift_and(8, (edx & 0xffu), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4ec038;
    lift_store(&env, esp, 0xcu, 4, ebx);
L_4ebf40:
    edx = lift_load(&env, ebp, 0x4u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4ebf99;
    ebx = lift_load(&env, esp, 0xcu, 4);
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ebf51;
    edx = ebx;
L_4ebf51:
    edi = lift_load(&env, esp, 0x0u, 4);
    ecx = edx;
    esi = lift_load(&env, ebp, 0x0u, 4);
    ebx = lift_load(&env, esp, 0x8u, 4);
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
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
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
    eax = lift_load(&env, esp, 0xcu, 4);
    ecx = lift_load(&env, ebp, 0x0u, 4);
    esi = (edi + edx);
    ebx = ebx + edx;
    lift_store(&env, esp, 0x0u, 4, esi);
    lift_store(&env, esp, 0x8u, 4, ebx);
    edi = lift_load(&env, ebp, 0x4u, 4);
    ecx = ecx + edx;
    eax = eax - edx;
    edi = edi - edx;
    lift_store(&env, ebp, 0x0u, 4, ecx);
    lift_store(&env, esp, 0xcu, 4, eax);
    lift_store(&env, ebp, 0x4u, 4, edi);
L_4ebf99:
    ecx = lift_load(&env, esp, 0xcu, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ec0b5;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0x14u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4ebfb4;
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xdu, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4ec024;
L_4ebfb4:
    eax = lift_load(&env, ebp, 0x8u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ebp, 0x4u, 4, 0x0u);
    ebx = lift_load(&env, esp, 0xcu, 4);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xdu, 1)) & 0xffu);
    lift_store(&env, ebp, 0x0u, 4, eax);
    {
        (void)lift_and(8, (ecx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4ebfdd;
    {
        (void)lift_sub(32, ebx, 0x200u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ebfdd;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) ^ (ebx & 0xffu)) & 0xffu);
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) & 0xfeu) & 0xffu) << 8);
L_4ebfdd:
    edx = lift_load(&env, esp, 0x0u, 4);
    eax = lift_load(&env, ebp, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec3e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ebff6;
    lift_store(&env, ebp, 0xcu, 1, lift_load(&env, ebp, 0xcu, 1) | 0x20u);
    goto L_4ec0b5;
L_4ebff6:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ec003;
    lift_store(&env, ebp, 0xcu, 1, lift_load(&env, ebp, 0xcu, 1) | 0x10u);
    goto L_4ec0b5;
L_4ec003:
    edx = lift_load(&env, esp, 0x0u, 4);
    ebx = lift_load(&env, esp, 0xcu, 4);
    ecx = lift_load(&env, esp, 0x8u, 4);
    edx = edx + eax;
    ebx = ebx - eax;
    ecx = ecx + eax;
    lift_store(&env, esp, 0x0u, 4, edx);
    lift_store(&env, esp, 0xcu, 4, ebx);
    lift_store(&env, esp, 0x8u, 4, ecx);
    goto L_4ebf40;
L_4ec024:
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec578u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ec0b5;
    goto L_4ebf40;
L_4ec038:
    edx = lift_load(&env, esp, 0x0u, 4);
    edi = edx;
    ebx = ebx + edx;
    ecx = (ecx & 0xffffff00u) | ((0xffu) & 0xffu);
    edi = edi ^ edx;
L_4ec043:
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0x4u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4ec053;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec578u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ec0b5;
L_4ec053:
    esi = lift_load(&env, ebp, 0x4u, 4);
    esi = esi - 1u;
    eax = lift_load(&env, ebp, 0x0u, 4);
    lift_store(&env, ebp, 0x4u, 4, esi);
    esi = (eax + 0x1u);
    lift_store(&env, ebp, 0x0u, 4, esi);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & (ecx & 0xffu)) & 0xffu);
    eax = eax & 0xffu;
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (!fl.zf)
        goto L_4ec09a;
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0x4u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4ec081;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec578u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ec0b5;
L_4ec081:
    esi = lift_load(&env, ebp, 0x4u, 4);
    esi = esi - 1u;
    eax = lift_load(&env, ebp, 0x0u, 4);
    lift_store(&env, ebp, 0x4u, 4, esi);
    esi = (eax + 0x1u);
    lift_store(&env, ebp, 0x0u, 4, esi);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & (ecx & 0xffu)) & 0xffu);
    eax = eax & 0xffu;
L_4ec09a:
    {
        (void)lift_sub(32, eax, 0x1au, &fl);
    }
    if (!fl.zf)
        goto L_4ec0a5;
    lift_store(&env, ebp, 0xcu, 1, lift_load(&env, ebp, 0xcu, 1) | 0x10u);
    goto L_4ec0b5;
L_4ec0a5:
    lift_store(&env, edx, 0x0u, 1, (eax & 0xffu));
    eax = lift_load(&env, esp, 0x8u, 4);
    eax = eax + 1u;
    edx = edx + 1u;
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4ec043;
L_4ec0b5:
    eax = lift_load(&env, ebp, 0x10u, 4);
    esi = lift_load(&env, esp, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = lift_load(&env, esp, 0x8u, 4);
    lift_div1(32, esi, &eax, &edx, &fl);
L_4ec0ca:
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

uint32_t lifted_f4ec0e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC0E0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC0E0_STACK, 0, entry);
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
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ec0f6;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4ec158;
L_4ec0f6:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4ec107;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ec107:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec640u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ec156;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ec14d;
    ecx = esi;
    edi = eax;
    esi = ebx;
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
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
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
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4ec156;
L_4ec14d:
    edx = esi;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ec156:
    eax = ebp;
L_4ec158:
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

uint32_t lifted_f4ec160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC160_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ec176;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ec176:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec1d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC1D0_STACK + 4 + 4 * 0 + 4];
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
    eax = eax + 1u;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec1ec(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC1EC_STACK + 4 + 4 * 0 + 4];
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
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd9f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e6e43:
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e6e4a:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, 0u, 0x5c5c54u, 4);
    ecx = ecx + eax;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e6e64:
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax & 0x3fffffffu;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e6eda:
    edx = ebx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8fa7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC2D0_STACK, 0, entry);
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec300;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec307u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec307(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC307_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec380(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC380_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ec3a4:
    edx = lift_load(&env, 0u, 0x507c8cu, 4);
    edx = lift_load(&env, edx, (ebx * 4u) + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ca8u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    edx = eax;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, edx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ec3d5;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC3E0_STACK + 4 + 4 * 0 + 4];
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
    esp = esp - 0x4u;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0xffffffffu;
    goto L_4ec472;
L_4ec404:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x507d24u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ec437;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cfcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ec437;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507d24u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c78u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ec467;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ec467:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec548(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC548_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec578u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ec55f:
    ebx = lift_load(&env, edx, 0x4u, 4);
    ecx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx - 1u;
    ecx = ecx + 1u;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec578(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC578_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3b60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3f28u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ec5a5:
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ecx, 0xcu, 1)) & 0xffu) << 8);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0xfbu) & 0xffu) << 8);
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, ecx, 0xcu, 1, ((edx >> 8) & 0xffu));
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = lift_load(&env, ecx, 0xcu, 4);
    eax = eax & 0x2400u;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ecaa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec3e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec640(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC640_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC640_STACK, 0, entry);
    eax = eax - 0x4u;
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfeu) & 0xffu);
    {
        uint32_t r = lift_sub(32, eax, 0x4u, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec8f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC8F0_STACK + 4 + 4 * 4 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ecad0u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC910_STACK + 4 + 4 * 2 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC910_STACK, 2, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esp, 0x4u, 1)) & 0xffu);
    lift_store(&env, eax, 0x14u, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ec92d;
    eax = 0xfffffffdu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ecb50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ec92d:
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC940_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec910u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eca85(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECA85_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ECA85_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = edx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ed79fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
    lift_store(&env, ebx, 0x4u, 4, edx);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ecaa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECAA0_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ed984u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eda00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ecad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECAD0_STACK + 4 + 4 * 4 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1990u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ecb34;
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x88u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ecb34;
    esi = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x54u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x5cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ecb22:
    ebx = lift_load(&env, edi, 0x0u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x6cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4ecb32;
L_4ecb2b:
    esi = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x58u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ecb32:
    esi = eax;
L_4ecb34:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eda70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ecb50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECB50_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6f60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ecb7b:
    {
        (void)lift_sub(32, eax, 0x3a4u, &fl);
    }
    if (!fl.zf)
        goto L_4ecb87;
    eax = 0xfffffffcu;
L_4ecb87:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6f60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ecc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECC60_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ecc03u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx - 0x1000u;
    goto L_4ecc98;
L_4ecc80:
    {
        (void)lift_sub(32, edx, 0xfffff000u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ecc98;
    edx = 0xfffff000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ecc03u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx + 0x1000u;
L_4ecc98:
    edx = ebx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ecc03u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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

uint32_t lifted_f4ecf60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECF60_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ECF60_STACK, 0, entry);
    ecx = (ecx & 0xffffff00u) | ((0xau) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), (ecx & 0xffu), &fl);
    }
    {
        uint32_t t = ((eax >> 8) & 0xffu);
        eax = (eax & 0xffff00ffu) | ((((eax & 0xffu)) & 0xffu) << 8);
        eax = (eax & 0xffffff00u) | ((t) & 0xffu);
    }
    if (fl.cf)
        goto L_4ecf6c;
    {
        uint32_t t = ((eax >> 8) & 0xffu);
        eax = (eax & 0xffff00ffu) | ((((eax & 0xffu)) & 0xffu) << 8);
        eax = (eax & 0xffffff00u) | ((t) & 0xffu);
    }
    lift_div1(8, (ecx & 0xffu), &eax, &edx, &fl);
L_4ecf6c:
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) + 0x30u) & 0xffu) << 8);
    {
        uint32_t r = lift_add(8, (eax & 0xffu), 0x30u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, ebx, 0x0u, 1, (eax & 0xffu));
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    lift_store(&env, ebx, 0x0u, 1, ((eax >> 8) & 0xffu));
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eda00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDA00_STACK + 4 + 4 * 0 + 4];
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
    esp = esp - 0x8u;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cfcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507d38u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4eda5b;
L_4eda2b:
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e89f4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1d04u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4edb48(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDB48_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4edc0eu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4edd24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDD24_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eddc4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4edf7f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDF7F_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EDF7F_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0x7fu) & 0xffu) << 8);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edfa3:
    eax = 0x2u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edfc1:
    eax = 0x4u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edfc8:
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee025(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE025_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE025_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (ebx & 0xffffff00u) | ((0x1fu) & 0xffu);
    goto L_4ee02d;
L_4ee02d:
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, eax, 0x9u, 1)) & 0xffu) << 8);
    {
        uint32_t a = ((ebx >> 8) & 0xffu);
        uint32_t r = lift_shr(8, a, 0x1u, &fl);
        ebx = (ebx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) | (ebx & 0xffu)) & 0xffu) << 8);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) & 0x7fffu) & 0xffffu);
    {
        uint32_t r = lift_sub(16, (ecx & 0xffffu), 0x3ffeu, &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.sf != fl.of)
        goto L_4ee08f;
    {
        (void)lift_sub(16, (ecx & 0xffffu), 0x20u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ee087;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) & 0x3fu) & 0xffu);
    {
        (void)lift_sub(8, (ecx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ee087;
    ecx = (ecx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t r = lift_add(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t a = ((ecx >> 8) & 0xffu);
        uint32_t r = lift_rcr(8, a, 0x1u, &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4ee066;
    {
        uint32_t r = lift_add(8, ((ecx >> 8) & 0xffu), ((ecx >> 8) & 0xffu), &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    goto L_4ee073;
L_4ee066:
    ebx = ebx - ebx;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shld(32, a, eax, (ecx & 0xffu), &fl);
        ebx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + ((ecx >> 8) & 0xffu)) & 0xffu) << 8);
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    eax = ebx;
L_4ee073:
    ecx = (ecx & 0xffffff00u) | ((0xffu) & 0xffu);
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_rcr(8, a, 0x1u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) & (ecx & 0xffu)) & 0xffu) << 8);
    {
        uint32_t r = lift_add(8, ((ecx >> 8) & 0xffu), ((ecx >> 8) & 0xffu), &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    eax = eax + 0x0u + fl.cf;
    {
        uint32_t r = lift_add(8, ((ecx >> 8) & 0xffu), ((ecx >> 8) & 0xffu), &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    if (!fl.cf)
        goto L_4ee084;
    {
        uint32_t a = eax;
        uint32_t r = lift_sub(32, 0, a, &fl);
        eax = r;
    }
L_4ee084:
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
L_4ee087:
    eax = 0x80000000u;
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
L_4ee08f:
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee094(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE094_STACK + 4 + 4 * 0 + 4];
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
    eax = 0u - eax;
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
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) - ((ecx >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
    ecx = ((ecx >> 8) & 0xffu);
    ecx = ecx + edx;
    edx = eax;
    goto L_4ee0cc;
L_4ee0c8:
    edx = edx - edx;
    ecx = ecx - ecx;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee0dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE0DC_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ee160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE160_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE160_STACK, 0, entry);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = 0x80000000u;
    goto L_4ee1e8;
L_4ee16b:
    esi = (esi & 0xffff0000u) | (((esi & 0xffffu) - 1u) & 0xffffu);
    {
        uint32_t r = lift_add(32, esi, 0x10000u, &fl);
        esi = r;
    }
    if (fl.cf)
        goto L_4ee179;
    if (fl.of)
        goto L_4ee179;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ee179:
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4ee1b1;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4ee1b1;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4ee1b1;
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4ee1b1;
    eax = esi;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(16, (esi & 0xffffu), (eax & 0xffffu), &fl);
    }
    eax = ebx;
    if (!fl.zf)
        goto L_4ee1a5;
    {
        uint32_t r = lift_or(32, edi, edi, &fl);
        edi = r;
    }
    if (!fl.zf)
        goto L_4ee1a9;
    goto L_4ee1af;
L_4ee1a5:
    {
        uint32_t r = lift_or(32, edi, edi, &fl);
        edi = r;
    }
    if (!fl.zf)
        goto L_4ee1af;
L_4ee1a9:
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        edx = r;
    }
    esi = (esi & 0xffff0000u) | ((0xffffu) & 0xffffu);
L_4ee1af:
    goto L_4ee1c6;
L_4ee1b1:
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4ee1b7;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
L_4ee1b7:
    if (!fl.cf && !fl.zf)
        goto L_4ee1c6;
    if (!fl.zf)
        goto L_4ee1bd;
    {
        uint32_t r = lift_or(32, edi, edi, &fl);
        edi = r;
    }
L_4ee1bd:
    if (fl.zf)
        goto L_4ee1c6;
    edx = ecx;
    eax = ebx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
L_4ee1c6:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ee1c8:
    edx = ecx;
    eax = ebx;
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4ee1e0;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4ee1e0;
    esi = esi ^ edi;
L_4ee1e0:
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ee1e8:
    {
        uint32_t r = lift_add(16, (esi & 0xffffu), 0x1u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.cf)
        goto L_4ee16b;
    if (fl.of)
        goto L_4ee16b;
    {
        uint32_t r = lift_add(32, esi, 0xffffu, &fl);
        esi = r;
    }
    if (fl.cf)
        goto L_4ee1c8;
    if (fl.of)
        goto L_4ee1c8;
    esi = esi - 0x10000u;
    esi = esi ^ edi;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4ee22e;
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4ee22e;
    {
        uint32_t r = lift_add(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4ee22b;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
    eax = ebx;
    edx = ecx;
    esi = esi + esi;
    ebx = (ebx & 0xffff0000u) | (((ebx & 0xffffu) | (esi & 0xffffu)) & 0xffffu);
    {
        uint32_t r = lift_or(32, ebx, edx, &fl);
        ebx = r;
    }
    if (fl.zf)
        goto L_4ee22a;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        esi = r;
    }
L_4ee22a:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ee22b:
    {
        uint32_t a = (esi & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
L_4ee22e:
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4ee23f;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4ee23f;
    {
        (void)lift_and(32, esi, 0x7fff0000u, &fl);
    }
    if (!fl.zf)
        goto L_4ee23f;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ee23f:
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t t = ecx;
        ecx = esi;
        esi = t;
    }
    edi = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edi = edi & 0x80007fffu;
    ecx = ecx & 0x80007fffu;
    ebp = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        ecx = r;
    }
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) + (edi & 0xffffu)) & 0xffffu);
    {
        uint32_t a = edi;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_sub(16, (ecx & 0xffffu), (edi & 0xffffu), &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4ee28e;
    if (!fl.cf)
        goto L_4ee27a;
    ebp = edi;
    ecx = (ecx & 0xffff0000u) | ((0u - (ecx & 0xffffu)) & 0xffffu);
    {
        uint32_t t = ebx;
        ebx = eax;
        eax = t;
    }
    {
        uint32_t t = edx;
        edx = esi;
        esi = t;
    }
L_4ee27a:
    {
        (void)lift_sub(16, (ecx & 0xffffu), 0x40u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ee28e;
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t a = (ebp & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        ebp = (ebp & 0xffff0000u) | ((r) & 0xffffu);
    }
    eax = ebx;
    edx = esi;
    esi = ebp;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ee28e:
    ecx = (ecx & 0xffff00ffu) | (((0x0u) & 0xffu) << 8);
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (!fl.sf)
        goto L_4ee2a3;
    ecx = (ecx & 0xffff00ffu) | (((0xffu) & 0xffu) << 8);
    esi = 0u - esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sub(32, 0, a, &fl);
        ebx = r;
    }
    esi = esi - 0x0u - fl.cf;
    ebp = ebp ^ 0x80000000u;
L_4ee2a3:
    edi = edi - edi;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ee2d6;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx - ebx;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x20u, &fl);
    }
    if (fl.cf)
        goto L_4ee2c8;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    ebx = (ebx & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    edi = ebx;
    ebx = ebx - ebx;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_4ee2c4;
    edi = edi | edx;
    edx = edx - edx;
L_4ee2c4:
    eax = edx;
    edx = edx - edx;
L_4ee2c8:
    {
        uint32_t a = ebx;
        uint32_t r = lift_shrd(32, a, eax, (ecx & 0xffu), &fl);
        ebx = r;
    }
    edi = edi | ebx;
    ebx = ebx - ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shrd(32, a, edx, (ecx & 0xffu), &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shrd(32, a, ebx, (ecx & 0xffu), &fl);
        edx = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
L_4ee2d6:
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, esi, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_adc(8, ((ecx >> 8) & 0xffu), 0x0u, &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    if (!fl.sf)
        goto L_4ee307;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_4ee2f8;
    {
        (void)lift_and(32, edi, 0x7fffffffu, &fl);
    }
    ebx = (ebx & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_adc(32, eax, 0x0u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, 0x0u, &fl);
        edx = r;
    }
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + 0x0u + fl.cf) & 0xffu) << 8);
L_4ee2f8:
    edx = 0u - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sub(32, 0, a, &fl);
        eax = r;
    }
    edx = edx - 0x0u - fl.cf;
    ecx = (ecx & 0xffff00ffu) | (((0x0u) & 0xffu) << 8);
    ebp = ebp ^ 0x80000000u;
L_4ee307:
    ebx = eax;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | ((ecx >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_or(32, ebx, edx, &fl);
        ebx = r;
    }
    if (fl.zf)
        goto L_4ee356;
    {
        uint32_t r = lift_or(16, (ebp & 0xffffu), (ebp & 0xffffu), &fl);
        ebp = (ebp & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4ee358;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ee327;
    {
        uint32_t a = edi;
        uint32_t r = lift_rol(32, a, 0x1u, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_ror(32, a, 0x1u, &fl);
        edi = r;
    }
L_4ee31d:
    {
        uint32_t a = (ebp & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ebp = (ebp & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4ee358;
    {
        uint32_t r = lift_adc(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.cf)
        goto L_4ee31d;
L_4ee327:
    ebp = (ebp & 0xffff0000u) | (((ebp & 0xffffu) + 1u) & 0xffffu);
    {
        (void)lift_sub(16, (ebp & 0xffffu), 0x7fffu, &fl);
    }
    if (fl.zf)
        goto L_4ee362;
    fl.cf = 1;
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    if (!fl.cf)
        goto L_4ee354;
    {
        uint32_t r = lift_add(32, edi, edi, &fl);
        edi = r;
    }
    if (!fl.zf)
        goto L_4ee33f;
    {
        uint32_t a = eax;
        uint32_t r = lift_ror(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rol(32, a, 0x1u, &fl);
        eax = r;
    }
L_4ee33f:
    {
        uint32_t r = lift_adc(32, eax, 0x0u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, 0x0u, &fl);
        edx = r;
    }
    if (!fl.cf)
        goto L_4ee354;
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    ebp = (ebp & 0xffff0000u) | (((ebp & 0xffffu) + 1u) & 0xffffu);
    {
        (void)lift_sub(16, (ebp & 0xffffu), 0x7fffu, &fl);
    }
    if (fl.zf)
        goto L_4ee362;
L_4ee354:
    goto L_4ee358;
L_4ee356:
    ebp = ebx;
L_4ee358:
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t a = (ebp & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        ebp = (ebp & 0xffff0000u) | ((r) & 0xffffu);
    }
    esi = ebp;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ee362:
    ebp = (ebp & 0xffff0000u) | ((0x7fffu) & 0xffffu);
    eax = eax - eax;
    edx = 0x80000000u;
    goto L_4ee358;
}

uint32_t lifted_f4ee370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE370_STACK + 4 + 4 * 0 + 4];
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
    edx = edx - edx;
    ecx = ecx - ecx;
    ebp = ebp - ebp;
    eax = eax - eax;
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
    edx = edx + edx + fl.cf;
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_adc(32, ecx, ecx, &fl);
        ecx = r;
    }
    edx = edx + edx + fl.cf;
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_adc(32, ecx, ebx, &fl);
        ecx = r;
    }
    edx = edx + edi + fl.cf;
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_adc(32, ecx, ecx, &fl);
        ecx = r;
    }
    edx = edx + edx + fl.cf;
    eax = eax - eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_adc(32, ecx, 0x0u, &fl);
        ecx = r;
    }
    edx = edx + 0x0u + fl.cf;
    esi = esi + 1u;
    goto L_4ee380;
L_4ee3b5:
    eax = ecx;
    edi = 0x405eu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ee3d2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee3d2(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE3D2_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE3D2_STACK, 0, entry);
    esi = esi - esi;
    esi = esi | eax;
    esi = esi | edx;
    {
        uint32_t r = lift_or(32, esi, ebp, &fl);
        esi = r;
    }
    if (fl.zf)
        goto L_4ee412;
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4ee3e9;
    edx = eax;
    eax = ebp;
    ebp = ebp - ebp;
    edi = edi - 0x20u;
L_4ee3e9:
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4ee3f6;
    edx = eax;
    eax = ebp;
    ebp = ebp - ebp;
    edi = edi - 0x20u;
L_4ee3f6:
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (fl.sf)
        goto L_4ee403;
    edi = edi - 1u;
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_adc(32, eax, eax, &fl);
        eax = r;
    }
    edx = edx + edx + fl.cf;
    goto L_4ee3f6;
L_4ee403:
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_adc(32, eax, 0x0u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, 0x0u, &fl);
        edx = r;
    }
    if (!fl.cf)
        goto L_4ee410;
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
L_4ee410:
    esi = edi;
L_4ee412:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE670_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x5cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x2u;
    esi = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE730_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_return_constant_4ee730(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RETURN_CONSTANT_4EE730_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RETURN_CONSTANT_4EE730_STACK, 0,
               entry);
    eax = 0x4ee730u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_return_constant_4ee750(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RETURN_CONSTANT_4EE750_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RETURN_CONSTANT_4EE750_STACK, 0,
               entry);
    eax = 0x4ee750u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_return_constant_4ee6a0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RETURN_CONSTANT_4EE6A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RETURN_CONSTANT_4EE6A0_STACK, 0,
               entry);
    eax = 0x4ee6a0u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE840_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE840_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x20u;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE8D0_STACK + 4 + 4 * 0 + 4];
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
L_4ee8eb:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4ee907;
    ebx = ((esi * 4u));
    eax = ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9ff0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x4u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE980_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE980_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x30u;
    ecx = eax;
    {
        (void)lift_and(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4ee9af;
    lift_store(&env, esp, 0x20u, 4, 0x1u);
    edx = 0x51c2f0u;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ee910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    {
        (void)lift_and(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4eea09;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eea20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EEA20_STACK + 4 + 4 * 0 + 4];
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
    eax = eax + 0x14u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e23e0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    ecx = lift_load(&env, ebx, 0x18u, 4);
    ecx = ecx - 1u;
    edx = ecx;
    eax = eax + 0x4u;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edx = r;
    }
    eax = eax + edx;
    edx = ecx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4eea60;
L_4eea4e:
    ecx = lift_load(&env, ebx, 0x10u, 4);
    lift_store(&env, eax, 0x0u, 4, ecx);
    edx = edx - 1u;
    lift_store(&env, ebx, 0x10u, 4, eax);
    eax = eax - 0x10u;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4eea4e;
L_4eea60:
    esi = lift_load(&env, ebx, 0x10u, 4);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, ebx, 0x10u, 4, eax);
    lift_store(&env, ebx, 0xcu, 4, lift_load(&env, ebx, 0xcu, 4) + 1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x4u;
    ecx = (esi + 0x8u);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eea90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EEA90_STACK + 4 + 4 * 0 + 4];
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
    esp = esp - 0x4u;
    edi = eax;
    esi = edx;
    eax = edx;
    ecx = ecx ^ ecx;
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
    ecx = ecx + edx;
    edx = (uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x0u, 1);
    eax = eax + 1u;
    ecx = ecx + edx;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4eeaa3;
L_4eeab8:
    eax = lift_load(&env, edi, 0x8u, 4);
    edx = edx ^ edx;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1982u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4eeadb;
    eax = ecx;
    goto L_4eeaf7;
L_4eeaf5:
    eax = eax ^ eax;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}
