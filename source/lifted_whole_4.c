/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_4.h"

uint32_t lifted_object_write_18(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_WRITE_18_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_WRITE_18_STACK, 0, entry);
    lift_store(&env, eax, 0x18u, 4, edx);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_return_unchanged_47f8f0(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RETURN_UNCHANGED_47F8F0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RETURN_UNCHANGED_47F8F0_STACK, 0,
               entry);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_checked_calls(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_CHECKED_CALLS_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_CHECKED_CALLS_STACK, 0, entry);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47e7d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_47f9c7;
L_47f9c1:
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
L_47f9c7:
    edx = 0x51698cu;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47fd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47f9c1;
    ebx = eax;
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

uint32_t lifted_f47f9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47F9E0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47F9E0_STACK, 0, entry);
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
    edi = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47ea20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ebx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = esi ^ esi;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_47fa02;
L_47f9fc:
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
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_47fa02:
    edx = edi;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f770u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47f9fc;
    esi = eax;
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
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f47fa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47FA20_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47FA20_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47ea20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f750u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f47fa40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47FA40_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47FA40_STACK, 0, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x8u;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_47fa53;
    edi = lift_load(&env, eax, 0x30u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_47fa5b;
L_47fa53:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    esp = (ebp + 0xfffffffcu);
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
L_47fa5b:
    {
        uint32_t v = 0x80000028u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ebp + 0xfffffff4u);
    lift_store(&env, ebp, 0xfffffff8u, 4, edx);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x1cu, 4), eax, edx, ebx, ecx, 8, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 32u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_47fa53;
    eax = 0x1u;
    esp = (ebp + 0xfffffffcu);
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
}

uint32_t lifted_f47fa90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47FA90_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47FA90_STACK, 0, entry);
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
    esp = esp - 0xcu;
    esi = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_47faa4;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x30u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_47faac;
L_47faa4:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    esp = (ebp + 0xfffffffcu);
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
L_47faac:
    {
        uint32_t v = 0x28u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xfffffff4u, 4, edx);
    edx = (ebp + 0xfffffff8u);
    {
        uint32_t v = edx;
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xfffffff0u);
    lift_store(&env, ebp, 0xfffffff0u, 4, ecx);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x1cu, 4), eax, edx, ebx, ecx, 8, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 32u;
    {
        (void)lift_sub(32, eax, 0x15800eu, &fl);
    }
    if (!fl.zf)
        goto L_47fadd;
    eax = 0x1u;
    esp = (ebp + 0xfffffffcu);
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
L_47fadd:
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x480080u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    esp = (ebp + 0xfffffffcu);
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

uint32_t lifted_object_set_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_SET_TEXT_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_SET_TEXT_STACK, 0, entry);
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
    esp = esp - 0x4u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    edi = edx;
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
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_47fb71;
    {
        (void)lift_sub(32, ecx, 0x100u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47fb75;
    ebx = 0x100u;
L_47fb1a:
    edi = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = ebx;
    esi = edx;
    edi = edi + 0xb9u;
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
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
    ebx = ebx + edx;
    ecx = 0x102u;
    edx = edx + 0xb8u;
    lift_store(&env, ebx, 0xb9u, 1, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = lift_load(&env, edx, 0xffffff80u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47fa40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_47fb59:
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
L_47fb71:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    goto L_47fb59;
L_47fb75:
    ebx = ecx;
    goto L_47fb1a;
}

uint32_t lifted_f47fc10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47FC10_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47FC10_STACK, 0, entry);
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
    esi = edx;
    edi = ecx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_47fc4c;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_47fc4c;
    {
        (void)lift_sub(32, ecx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_47fc32;
    edi = ebx;
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
    edi = (ecx + 0x1u);
L_47fc32:
    ecx = (edi + 0xffffffffu);
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
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c6cu, eax, edx, ebx, ecx, 6, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 24u;
    lift_store(&env, esi, (edi * 2u) + 0xfffffffeu, 2, 0x0u);
L_47fc4c:
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

uint32_t lifted_f47fc50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47FC50_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47FC50_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = edx;
    edx = ebx;
    ebx = ecx;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_47fc8a;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_47fc8a;
    {
        (void)lift_sub(32, ecx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_47fc6e;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (eax + 0x1u);
L_47fc6e:
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
    eax = (ebx + 0xffffffffu);
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
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1d00u, eax, edx, ebx, ecx, 8, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 32u;
    lift_store(&env, esi, ebx + 0xffffffffu, 1, 0x0u);
L_47fc8a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f47fce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47FCE0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47FCE0_STACK, 0, entry);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_47fcec;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_47fcec;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_47fced;
L_47fcec:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_47fced:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47fc10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_display_notify(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_DISPLAY_NOTIFY_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_DISPLAY_NOTIFY_STACK, 0, entry);
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
    edx = lift_load(&env, eax, 0x1bcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_47fe36;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x1c0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_47fe3a;
L_47fe36:
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
L_47fe3a:
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
    ebx = lift_load(&env, eax, 0x1c0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x20u, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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

uint32_t lifted_f47fe50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47FE50_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47FE50_STACK, 0, entry);
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
    edx = lift_load(&env, eax, 0x1bcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_47fe66;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x1c0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_47fe6a;
L_47fe66:
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
L_47fe6a:
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
    ebx = lift_load(&env, eax, 0x1c0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x20u, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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

uint32_t lifted_f47fe80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47FE80_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47FE80_STACK, 0, entry);
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
    edx = lift_load(&env, eax, 0x1bcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_47fe96;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x1c0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_47fe9a;
L_47fe96:
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
L_47fe9a:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, eax, 0x1c0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x20u, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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

uint32_t lifted_f480030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F480030_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F480030_STACK, 0, entry);
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
    ebx = 0x5cu;
    esi = (eax + 0x48u);
    edx = edx ^ edx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_480051;
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
L_480051:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ecx, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, ecx, 0x38u, 4);
    lift_store(&env, ecx, 0x48u, 4, 0x5cu);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x88u, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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

uint32_t lifted_palette_expand_vga(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PALETTE_EXPAND_VGA_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PALETTE_EXPAND_VGA_STACK, 0, entry);
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
    ebx = ebx ^ ebx;
L_480898:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, eax, 0x100u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4808dc;
    edx = (eax + (eax * 2u));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, esi + 0x0u, 1)) & 0xffu);
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_shl(8, a, 0x2u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, 0u, (eax * 4u) + 0x598630u, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, esi + 0x1u, 1)) & 0xffu);
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_shl(8, a, 0x2u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, 0u, (eax * 4u) + 0x598631u, 1, (ecx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, esi + 0x2u, 1)) & 0xffu);
    {
        uint32_t a = (edx & 0xffu);
        uint32_t r = lift_shl(8, a, 0x2u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, 0u, (eax * 4u) + 0x598632u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((0x2u) & 0xffu);
    ebx = ebx + 1u;
    lift_store(&env, 0u, (eax * 4u) + 0x598633u, 1, (edx & 0xffu));
    goto L_480898;
L_4808dc:
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

uint32_t lifted_f4808f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4808F0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4808F0_STACK, 0, entry);
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
    ebx = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x598628u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x598630u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, eax, 0x14u, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_480916;
    eax = 0x1u;
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
L_480916:
    eax = 0x5b9c50u;
    edx = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x50f6bbu;
    edx = 0x1u;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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

uint32_t lifted_f480940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F480940_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F480940_STACK, 0, entry);
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
    ebx = eax;
    ecx = lift_load(&env, 0u, 0x598628u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, eax, 0x7cu, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_48095f;
    eax = 0x1u;
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
L_48095f:
    eax = 0x5b9c50u;
    edx = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x50f6edu;
    edx = 0x1u;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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

uint32_t lifted_f480d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F480D60_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F480D60_STACK, 0, entry);
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
    esp = esp - 0xa0u;
    edi = eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aad0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = (eax + 0x80u);
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aad0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = 0x80u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aa70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax + edx;
    ebx = 0x1u;
    eax = eax - 0x300u;
    edx = (ebp + 0xffffff54u);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffff5au, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff5cu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax + 1u;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff96u, 4);
    eax = eax - edx;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    edx = esi;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aaf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd4u, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_480e32;
L_480de9:
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_480e17;
L_480df0:
    ecx = 0x1u;
    edx = (ebp + 0xfffffff0u);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0xbfu, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_480e40;
    edi = edi + 1u;
    esi = esi - 1u;
    lift_store(&env, edi, 0xffffffffu, 1, (eax & 0xffu));
L_480e13:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_480df0;
L_480e17:
    if (!fl.zf)
        goto L_480e27;
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aa90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_480e27:
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = ecx - 1u;
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_480de9;
L_480e32:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_480e75;
L_480e38:
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
L_480e40:
    ecx = 0x1u;
    eax = eax - 0xc0u;
    edx = (ebp + 0xfffffff0u);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    ebx = ecx;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd8u, 4), 0x0u, &fl);
    }
L_480e5e:
    if (fl.zf)
        goto L_480e13;
    esi = esi - 1u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_480e6c;
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    lift_store(&env, edi, 0xffffffffu, 1, (eax & 0xffu));
L_480e6c:
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    goto L_480e5e;
L_480e75:
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aaf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = esi ^ esi;
    edi = 0x1u;
L_480e87:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, eax, 0x300u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_480e38;
    edx = (ebp + 0xfffffff0u);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = edi;
    ebx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = esi + 1u;
    eax = eax ^ eax;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    edx = edx + 1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, edx, 0xffffffffu, 1, (eax & 0xffu));
    goto L_480e87;
}

uint32_t lifted_rle_decode(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RLE_DECODE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RLE_DECODE_STACK, 0, entry);
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
    esp = esp - 0x10u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    edi = edx;
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    lift_store(&env, ebp, 0xfffffff0u, 4, ecx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_481507;
L_48149b:
    ecx = 0x1u;
    edx = (ebp + 0xfffffff4u);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax - 1u;
    esi = lift_load(&env, ebp, 0xfffffff4u, 1);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_sub(32, esi, 0xc0u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4814fa;
    ecx = 0x1u;
    edx = (ebp + 0xfffffff4u);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = edx - 1u;
    esi = esi - 0xc0u;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
L_4814df:
    edx = 0xffffffffu;
L_4814e4:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_481501;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    ecx = lift_load(&env, ebp, 0xfffffff0u, 4);
    edi = edi + 1u;
    esi = esi - 1u;
    ecx = ecx + edx;
    lift_store(&env, edi, 0xffffffffu, 1, (eax & 0xffu));
    lift_store(&env, ebp, 0xfffffff0u, 4, ecx);
    goto L_4814e4;
L_4814fa:
    esi = 0x1u;
    goto L_4814df;
L_481501:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48149b;
L_481507:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xfffffff0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_481514;
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
L_481514:
    {
        uint32_t v = 0x50f725u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d85c0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0x4u;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb4d4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
}

uint32_t lifted_rle_decode_bitmap(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RLE_DECODE_BITMAP_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RLE_DECODE_BITMAP_STACK, 0, entry);
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
    esp = esp - 0x10u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = edx;
    edx = ebx;
    esi = eax;
    {
        uint32_t r = lift_imul(32, esi, ebx, &fl);
        esi = r;
    }
    ebx = 0x1u;
    lift_store(&env, ebp, 0xffffffecu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    edi = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_481609;
L_4815ab:
    ecx = 0x1u;
    edx = (ebp + 0xfffffff0u);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, ebp, 0xfffffff0u, 1);
    {
        (void)lift_sub(32, esi, 0xbfu, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4815e9;
    esi = 0x1u;
L_4815ce:
    edx = 0xffffffffu;
L_4815d3:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_481603;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    edi = edi + 1u;
    esi = esi - 1u;
    ebx = ebx + edx;
    lift_store(&env, edi, 0xffffffffu, 1, (eax & 0xffu));
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    goto L_4815d3;
L_4815e9:
    ecx = 0x1u;
    edx = (ebp + 0xfffffff0u);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ecx;
    esi = esi - 0xc0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4815ce;
L_481603:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4815ab;
L_481609:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
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

uint32_t lifted_object_create_with_class(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_CREATE_WITH_CLASS_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_CREATE_WITH_CLASS_STACK, 0,
               entry);
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
    esp = esp - 0x20u;
    ecx = eax;
    eax = (ebp + 0xffffffd0u);
    edx = 0x4ec1ecu;
    ebx = 0x516b20u;
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
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    ebx = 0x516ba0u;
    edx = 0xau;
    lift_store(&env, ebp, 0xffffffe8u, 1, ((eax >> 8) & 0xffu));
    eax = ecx;
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccf3bu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    lift_store(&env, eax, 0x20cu, 4, 0x516b84u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    env.chain = eax;
    eax = edx;
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
}

uint32_t lifted_object_destroy_b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_DESTROY_B_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_DESTROY_B_STACK, 0, entry);
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
    esp = esp - 0x34u;
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_482026;
    edx = 0x4ec1ecu;
    esi = 0x516b24u;
    lift_store(&env, eax, 0x20cu, 4, 0x516b84u);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffe8u, 1, (ebx & 0xffu));
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
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    eax = ecx;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4823b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_482012;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_482012:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    env.chain = eax;
    eax = ecx;
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
L_482026:
    ebx = 0x1u;
    edx = 0x516bc0u;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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

uint32_t lifted_object_clear_208(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_CLEAR_208_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_CLEAR_208_STACK, 0, entry);
    lift_store(&env, eax, 0x208u, 1, 0x0u);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_event_stack_push(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_EVENT_STACK_PUSH_STACK + 4 + 4 * 11 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_EVENT_STACK_PUSH_STACK, 11, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x4u;
    esi = eax;
    lift_store(&env, esp, 0x0u, 1, (edx & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x208u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x9u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_48207d;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48207d:
    eax = (eax & 0xffff00ffu) | ((((eax & 0xffu)) & 0xffu) << 8);
    edx = edx ^ edx;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) + 1u) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | ((((eax >> 8) & 0xffu)) & 0xffu);
    lift_store(&env, esi, 0x208u, 1, ((eax >> 8) & 0xffu));
    eax = ((edx * 4u));
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + edx;
    lift_store(&env, esi, (eax * 4u) + 0x1u, 1, (ebx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    lift_store(&env, esi, (eax * 4u) + 0x4u, 4, ecx);
    lift_store(&env, esi, (eax * 4u) + 0x0u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esp, 0xcu, 1)) & 0xffu);
    lift_store(&env, esi, (eax * 4u) + 0x8u, 1, (edx & 0xffu));
    edx = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, esi, (eax * 4u) + 0xcu, 4, edx);
    edx = lift_load(&env, esp, 0x14u, 4);
    lift_store(&env, esi, (eax * 4u) + 0x10u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esp, 0x18u, 1)) & 0xffu);
    lift_store(&env, esi, (eax * 4u) + 0x14u, 1, (edx & 0xffu));
    edx = lift_load(&env, esp, 0x1cu, 4);
    lift_store(&env, esi, (eax * 4u) + 0x2cu, 4, edx);
    edx = lift_load(&env, esp, 0x20u, 4);
    lift_store(&env, esi, (eax * 4u) + 0x18u, 4, edx);
    edx = lift_load(&env, esp, 0x24u, 4);
    lift_store(&env, esi, (eax * 4u) + 0x1cu, 4, edx);
    edx = lift_load(&env, esp, 0x28u, 4);
    lift_store(&env, esi, (eax * 4u) + 0x20u, 2, (edx & 0xffffu));
    edx = lift_load(&env, esp, 0x2cu, 4);
    lift_store(&env, esi, (eax * 4u) + 0x22u, 2, (edx & 0xffffu));
    edx = lift_load(&env, esp, 0x30u, 4);
    lift_store(&env, esi, (eax * 4u) + 0x24u, 4, edx);
    edx = lift_load(&env, esp, 0x34u, 4);
    lift_store(&env, esi, (eax * 4u) + 0x28u, 4, edx);
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
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

uint32_t lifted_event_stack_pop(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_EVENT_STACK_POP_STACK + 4 + 4 * 11 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_EVENT_STACK_POP_STACK, 11, entry);
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
    edi = ecx;
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0x208u, 1)) & 0xffu);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4821f5;
    eax = ((ecx * 4u));
    eax = eax - ecx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + ecx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + esi;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4821fb;
L_482142:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_48214b;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x1u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x0u, 1, (edx & 0xffu));
L_48214b:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_482154;
    edx = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, edi, 0x0u, 4, edx);
L_482154:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x10u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_482164;
    ecx = lift_load(&env, esp, 0x10u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x8u, 1)) & 0xffu);
    lift_store(&env, ecx, 0x0u, 1, (edx & 0xffu));
L_482164:
    ecx = lift_load(&env, esp, 0x14u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_482171;
    edx = lift_load(&env, eax, 0xcu, 4);
    lift_store(&env, ecx, 0x0u, 4, edx);
L_482171:
    ebx = lift_load(&env, esp, 0x18u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_48217e;
    edx = lift_load(&env, eax, 0x10u, 4);
    lift_store(&env, ebx, 0x0u, 4, edx);
L_48217e:
    edi = lift_load(&env, esp, 0x1cu, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_48218b;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x14u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (edx & 0xffu));
L_48218b:
    ebp = lift_load(&env, esp, 0x20u, 4);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_482199;
    edx = lift_load(&env, eax, 0x2cu, 4);
    lift_store(&env, ebp, 0x0u, 4, edx);
L_482199:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x24u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4821a9;
    ecx = lift_load(&env, esp, 0x24u, 4);
    edx = lift_load(&env, eax, 0x18u, 4);
    lift_store(&env, ecx, 0x0u, 4, edx);
L_4821a9:
    ecx = lift_load(&env, esp, 0x28u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4821b6;
    edx = lift_load(&env, eax, 0x1cu, 4);
    lift_store(&env, ecx, 0x0u, 4, edx);
L_4821b6:
    ebx = lift_load(&env, esp, 0x2cu, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4821c5;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x20u, 2)) & 0xffffu);
    lift_store(&env, ebx, 0x0u, 2, (edx & 0xffffu));
L_4821c5:
    edi = lift_load(&env, esp, 0x30u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4821d4;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x22u, 2)) & 0xffffu);
    lift_store(&env, edi, 0x0u, 2, (edx & 0xffffu));
L_4821d4:
    ebp = lift_load(&env, esp, 0x34u, 4);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4821e2;
    edx = lift_load(&env, eax, 0x24u, 4);
    lift_store(&env, ebp, 0x0u, 4, edx);
L_4821e2:
    edx = lift_load(&env, esp, 0x38u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4821ef;
    eax = lift_load(&env, eax, 0x28u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
L_4821ef:
    {
        uint32_t a = lift_load(&env, esi, 0x208u, 1);
        uint32_t r = lift_dec(8, a, &fl, 1);
        lift_store(&env, esi, 0x208u, 1, r);
    }
L_4821f5:
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
L_4821fb:
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x0u, 1, (ecx & 0xffu));
    goto L_482142;
}

uint32_t lifted_f4823b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4823B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4823B0_STACK, 0, entry);
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
    esp = esp - 0x10u;
    ecx = eax;
    eax = (ebp + 0xffffffe4u);
    edx = 0x4ec1ecu;
    ebx = 0x516b4cu;
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
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    eax = ecx;
    ebx = 0x516ba0u;
    edx = 0xau;
    lift_store(&env, ebp, 0xfffffff0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cea15u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    env.chain = eax;
    eax = edx;
    esp = (ebp + 0xfffffff4u);
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

uint32_t lifted_forward_first_dword(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_FORWARD_FIRST_DWORD_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_FORWARD_FIRST_DWORD_STACK, 0, entry);
    eax = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f482770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F482770_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F482770_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = edx;
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_48277f;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48277f:
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((ecx & 0xffffu)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
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

uint32_t lifted_f4828a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4828A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4828A0_STACK, 0, entry);
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
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x4u;
    ecx = 0x1u;
    {
        (void)lift_sub(32, ecx, lift_load(&env, 0u, 0x598d60u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4828c6;
    eax = eax & 0xffu;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x598d68u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4828cf;
L_4828c6:
    eax = ecx;
    esp = (ebp + 0xfffffff8u);
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
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4828cf:
    edx = (ebp + 0xfffffff4u);
    eax = lift_load(&env, eax, 0x598d88u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ae60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xfffffff4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4828c6;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = ecx;
    esp = (ebp + 0xfffffff8u);
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
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4829c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4829C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4829C0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x598d60u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4829f1;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x598da8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4829d5;
    ebx = ebx ^ ebx;
L_4829d5:
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482b40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4829f5;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x598d68u, 4, edx);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4829f1:
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
L_4829f5:
    eax = lift_load(&env, ecx, 0x598d88u, 4);
    lift_store(&env, ecx, 0x598d68u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40adb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ecx, 0x598d68u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0x14u, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    eax = lift_load(&env, ecx, 0x598d88u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40adf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ebx;
    eax = lift_load(&env, ecx, 0x598d88u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ae00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_call_unless_zero(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_CALL_UNLESS_ZERO_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_CALL_UNLESS_ZERO_STACK, 0, entry);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_482b35;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_482b35:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b8170u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_event_frame_draw_blend(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_EVENT_FRAME_DRAW_BLEND_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_EVENT_FRAME_DRAW_BLEND_STACK, 1,
               entry);
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
    esp = esp - 0x24u;
    esi = edx;
    edi = ebx;
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    edx = lift_load(&env, eax, 0x0u, 4);
    ebx = lift_load(&env, eax, 0x8u, 4);
    ecx = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x27u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    edx = edx ^ edx;
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_shl(8, a, 0x3u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = (ebp + 0xffffffd4u);
    lift_store(&env, ebp, 0xffffffe0u, 1, (ebx & 0xffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    edx = ecx;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = (ebp + 0xffffffd4u);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    edx = lift_load(&env, ebp, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478da0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
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
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = esi;
    ebx = ebx ^ ebx;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    eax = (ebp + 0xffffffd4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47c930u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
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
}

uint32_t lifted_event_frame_draw_scaled(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_EVENT_FRAME_DRAW_SCALED_STACK + 4 + 4 * 5 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_EVENT_FRAME_DRAW_SCALED_STACK, 5,
               entry);
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
    esp = esp - 0x24u;
    esi = edx;
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    edx = lift_load(&env, eax, 0x0u, 4);
    ebx = lift_load(&env, eax, 0x8u, 4);
    edi = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x27u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    edx = edx ^ edx;
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_shl(8, a, 0x3u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = (ebp + 0xffffffd4u);
    lift_store(&env, ebp, 0xffffffe0u, 1, (ebx & 0xffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edi, eax, &fl);
        edi = r;
    }
    edx = lift_load(&env, ebp, 0x18u, 4);
    eax = (ebp + 0xffffffd4u);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478da0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, ebp, 0x10u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = esi;
    ebx = lift_load(&env, ebp, 0x8u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0xcu, 4);
    eax = (ebp + 0xffffffd4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47cb40u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
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
}

uint32_t lifted_f4831b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4831B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4831B0_STACK, 0, entry);
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
    esp = esp - 0x58u;
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    lift_store(&env, ebp, 0xffffffa0u, 4, ebx);
    eax = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    eax = lift_load(&env, edx, 0x8u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    {
        uint32_t v = 0x4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, eax, 0x8u, 4);
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = eax + eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffb4u, 4);
    eax = eax + eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx + eax;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0xffffffacu, 4);
    ebx = lift_load(&env, ebp, 0xffffffa4u, 4);
    ecx = lift_load(&env, ecx, 0x10u, 4);
    esi = lift_load(&env, ebp, 0xffffffa8u, 4);
    ecx = ecx + ebx;
    ebx = lift_load(&env, ebp, 0xffffffacu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    ebx = lift_load(&env, ebx, 0xcu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx + esi;
    lift_store(&env, ebp, 0xffffff9cu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x483060u, eax, edx, ebx, ecx, 8, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 32u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, edi);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_48331a;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    {
        uint32_t r = lift_imul(32, edx, 0x0u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
L_483269:
    ecx = ecx ^ ecx;
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4832fd;
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
L_483282:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        eax = r;
    }
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4832dd;
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    esi = lift_load(&env, ebp, 0xffffffccu, 4);
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    edi = lift_load(&env, ebp, 0xffffffd0u, 4);
    esi = lift_load(&env, esi, 0x0u, 4);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    esi = esi + ebx;
    edx = lift_load(&env, edx, 0x0u, 4);
    esi = esi + edi;
    edi = edi ^ edi;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4832dd;
L_4832ab:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xfffffff0u, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4832d0;
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    eax = esi;
    ebx = ebx + esi;
L_4832bb:
    ecx = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        ecx = r;
    }
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4832c6;
    lift_store(&env, eax, 0x0u, 4, lift_load(&env, eax, 0x0u, 4) + 1u);
L_4832c6:
    eax = eax + 0x4u;
    edx = edx + 0x4u;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.cf)
        goto L_4832bb;
L_4832d0:
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    edi = edi + 1u;
    esi = esi + ecx;
    {
        (void)lift_sub(32, edi, ebx, &fl);
    }
    if (fl.cf)
        goto L_4832ab;
L_4832dd:
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    esi = esi + 0x4u;
    edi = edi + 0x4u;
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf)
        goto L_483282;
L_4832fd:
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    edx = lift_load(&env, ebp, 0xffffffb8u, 4);
    ecx = lift_load(&env, ebp, 0xffffffbcu, 4);
    ebx = lift_load(&env, ebp, 0xffffffb4u, 4);
    edx = edx + eax;
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffffb8u, 4, edx);
    lift_store(&env, ebp, 0xffffffbcu, 4, ecx);
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.cf)
        goto L_483269;
L_48331a:
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    esi = esi ^ esi;
    edi = lift_load(&env, ebp, 0xffffff9cu, 4);
    lift_store(&env, ebp, 0xffffffc4u, 4, esi);
    edx = lift_load(&env, edx, 0x0u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_483376;
    edi = 0xffu;
L_483330:
    ebx = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = ecx ^ ecx;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_483368;
L_483339:
    eax = lift_load(&env, edx, 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48335d;
    {
        (void)lift_sub(32, eax, 0xffu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_483348;
    eax = edi;
L_483348:
    esi = eax;
    ebx = eax;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        esi = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ebx = r;
    }
    ebx = ebx | esi;
    eax = eax | ebx;
    eax = eax | 0xff000000u;
    lift_store(&env, edx, 0x0u, 4, eax);
L_48335d:
    esi = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = ecx + 1u;
    edx = edx + 0x4u;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.cf)
        goto L_483339;
L_483368:
    esi = lift_load(&env, ebp, 0xffffffc4u, 4);
    esi = esi + 1u;
    ecx = lift_load(&env, ebp, 0xffffff9cu, 4);
    lift_store(&env, ebp, 0xffffffc4u, 4, esi);
    {
        (void)lift_sub(32, esi, ecx, &fl);
    }
    if (fl.cf)
        goto L_483330;
L_483376:
    ebx = lift_load(&env, ebp, 0xffffffa0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4833db;
    esi = lift_load(&env, ebp, 0xffffffa4u, 4);
    edi = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        uint32_t r = lift_imul(32, esi, edi, &fl);
        esi = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = lift_load(&env, edx, 0x0u, 4);
    ecx = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    edx = lift_load(&env, ebp, 0xffffffb4u, 4);
    esi = esi + eax;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4833db;
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edi = r;
    }
L_4833aa:
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4833cb;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    eax = esi;
    ebx = ebx + esi;
L_4833b8:
    edx = lift_load(&env, ecx, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        edx = r;
    }
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4833e6;
L_4833c1:
    eax = eax + 0x4u;
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.cf)
        goto L_4833b8;
L_4833cb:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, ebp, 0xffffffb4u, 4);
    eax = eax + 1u;
    esi = esi + edi;
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf)
        goto L_4833aa;
L_4833db:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
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
L_4833e6:
    edx = lift_load(&env, eax, 0x0u, 4);
    edx = edx & 0xffffffu;
    lift_store(&env, eax, 0x0u, 4, edx);
    goto L_4833c1;
}

uint32_t lifted_f483ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F483CE0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F483CE0_STACK, 0, entry);
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
    esp = esp - 0x8u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    lift_store(&env, esp, 0x0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    lift_store(&env, esp, 0x4u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x27u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_483d56;
    ebx = lift_load(&env, esp, 0x4u, 4);
    edi = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_483d38;
L_483d0b:
    ebx = ebx ^ ebx;
L_483d0d:
    ecx = lift_load(&env, esp, 0xfffffffeu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edx = ecx;
    eax = ecx;
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
    edx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_483d41;
    eax = lift_load(&env, esp, 0x4u, 4);
    {
        uint32_t r = lift_add(32, edi, ecx, &fl);
        edi = r;
    }
    {
        uint32_t a = (eax & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, esp, 0x4u, 4, eax);
    if (!fl.zf)
        goto L_483d0b;
L_483d38:
    {
        uint32_t r = lift_add(32, esp, 0x8u, &fl);
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
L_483d41:
    ecx = ecx - 1u;
    ecx = ecx - eax;
    esi = (edi + eax);
    eax = ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, edi, eax + 0x0u, 1)) & 0xffu) << 8);
    lift_store(&env, esi, 0x0u, 1, ((edx >> 8) & 0xffu));
    ebx = ebx + 1u;
    lift_store(&env, edi, eax + 0x0u, 1, (edx & 0xffu));
    goto L_483d0d;
L_483d56:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_483d38;
    edx = lift_load(&env, esp, 0x4u, 4);
    edi = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
L_483d64:
    if (fl.zf)
        goto L_483d38;
    ebx = ebx ^ ebx;
L_483d68:
    ecx = lift_load(&env, esp, 0xfffffffeu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edx = ecx;
    eax = ecx;
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
    edx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_483d96;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, edi, ecx, &fl);
        edi = r;
    }
    ecx = lift_load(&env, esp, 0x4u, 4);
    {
        uint32_t a = (ecx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, esp, 0x4u, 4, ecx);
    goto L_483d64;
L_483d96:
    edx = ((eax * 4u));
    ecx = ecx - 1u;
    ecx = ecx - eax;
    eax = ecx;
    ecx = lift_load(&env, edi, (eax * 4u) + 0x0u, 4);
    esi = lift_load(&env, edx, edi + 0x0u, 4);
    lift_store(&env, edx, edi + 0x0u, 4, ecx);
    ebx = ebx + 1u;
    lift_store(&env, edi, (eax * 4u) + 0x0u, 4, esi);
    goto L_483d68;
}

uint32_t lifted_f4844b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4844B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4844B0_STACK, 0, entry);
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
    esi = eax;
    edi = edx;
    ecx = 0x14u;
    eax = 0x3e8u;
    edx = eax;
    ebx = ebx & 0xffffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (!fl.cf)
        goto L_4844d5;
    ecx = eax;
L_4844d5:
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    {
        uint32_t v = 0x484530u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (edx & 0xffff0000u) | (((ecx & 0xffffu)) & 0xffffu);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax & 0xffffu;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1734u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    lift_store(&env, 0u, 0x598db0u, 4, eax);
    lift_store(&env, esi, 0x0u, 4, edi);
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

uint32_t lifted_f484500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F484500_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F484500_STACK, 0, entry);
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
    edx = lift_load(&env, 0u, 0x598db0u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1730u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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

uint32_t lifted_f484530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F484530_STACK + 4 + 4 * 5 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F484530_STACK, 5, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
    eax = lift_load(&env, ebp, 0x10u, 4);
    edx = lift_load(&env, ebp, 0x8u, 4);
    {
        (void)lift_sub(32, edx, lift_load(&env, 0u, 0x598db0u, 4), &fl);
    }
    if (fl.zf)
        goto L_484545;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_484545:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x484520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4848f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4848F0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4848F0_STACK, 0, entry);
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
    esp = esp - 0x22cu;
    edi = eax;
    esi = edx;
    ecx = ebx;
    eax = (ebp + 0xffffffe0u);
    edx = 0x4ec1ecu;
    ebx = 0x516cc0u;
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
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    eax = eax ^ eax;
    edx = 0x4fd208u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    ebx = edi;
    eax = (ebp + 0xfffffedcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffedcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_48495c;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    env.chain = eax;
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
L_48495c:
    eax = (ebp + 0xfffffdc8u);
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffdc8u);
    ebx = lift_load(&env, 0u, 0x5466c8u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = (ebp + 0xfffffedcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4849b3;
    eax = (ebp + 0xfffffdc8u);
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = esi;
    eax = (ebp + 0xfffffdc8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffdc8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a8c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4849b3:
    eax = (ebp + 0xfffffdc8u);
    ecx = ecx ^ ecx;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    env.chain = eax;
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

uint32_t lifted_f485700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F485700_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F485700_STACK, 0, entry);
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
    esi = ebx;
    edi = 0x5b9a48u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_48570a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485722;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48570a;
L_485722:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    esi = ecx;
    {
        (void)lift_sub(32, ecx, 0x8876019au, &fl);
    }
    if (!fl.cf)
        goto L_48666c;
    {
        (void)lift_sub(32, ecx, 0x887600d7u, &fl);
    }
    if (!fl.cf)
        goto L_486a3e;
    {
        (void)lift_sub(32, ecx, 0x8876005fu, &fl);
    }
    if (!fl.cf)
        goto L_486bbf;
    {
        (void)lift_sub(32, ecx, 0x88760005u, &fl);
    }
    if (!fl.cf)
        goto L_486c82;
    {
        (void)lift_sub(32, ecx, 0x800401f0u, &fl);
    }
    if (!fl.cf)
        goto L_486cd8;
    {
        (void)lift_sub(32, ecx, 0x80004001u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_48651c;
    {
        (void)lift_sub(32, ecx, 0x80004005u, &fl);
    }
    if (fl.zf)
        goto L_4859f4;
L_48577b:
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
L_48577e:
    esi = 0x50fe91u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48578c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4857a4;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48578c;
L_4857a4:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4857a8:
    esi = 0x50feaau;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4857b6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4857ce;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4857b6;
L_4857ce:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4857d2:
    esi = 0x50fec0u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4857e0:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4857f8;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4857e0;
L_4857f8:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4857fc:
    esi = 0x50fedau;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48580a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485822;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48580a;
L_485822:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485826:
    esi = 0x50fef4u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485834:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48584c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485834;
L_48584c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485850:
    esi = 0x50ff1bu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48585e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485876;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48585e;
L_485876:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48587a:
    esi = 0x50ff31u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485888:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4858a0;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485888;
L_4858a0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4858a4:
    esi = 0x50ff44u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4858b2:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4858ca;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4858b2;
L_4858ca:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4858ce:
    esi = 0x50ff59u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4858dc:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4858f4;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4858dc;
L_4858f4:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4858f8:
    esi = 0x50ff72u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485906:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48591e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485906;
L_48591e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485922:
    esi = 0x50ff87u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485930:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485948;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485930;
L_485948:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48594c:
    esi = 0x50ff9fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48595a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485972;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48595a;
L_485972:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485976:
    esi = 0x50ffb6u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485984:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48599c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485984;
L_48599c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4859a0:
    esi = 0x50ffd5u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4859ae:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4859c6;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4859ae;
L_4859c6:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4859ca:
    esi = 0x50ffe5u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4859d8:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4859f0;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4859d8;
L_4859f0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4859f4:
    esi = 0x510003u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485a02:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485a1a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485a02;
L_485a1a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485a1e:
    esi = 0x510011u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485a2c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485a44;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485a2c;
L_485a44:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485a48:
    esi = 0x510023u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485a56:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485a6e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485a56;
L_485a6e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485a72:
    esi = 0x51004du;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485a80:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485a98;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485a80;
L_485a98:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485a9c:
    esi = 0x510065u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485aaa:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485ac2;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485aaa;
L_485ac2:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485ac6:
    esi = 0x51007fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485ad4:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485aec;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485ad4;
L_485aec:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485af0:
    esi = 0x510091u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485afe:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485b16;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485afe;
L_485b16:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485b1a:
    esi = 0x5100a7u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485b28:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485b40;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485b28;
L_485b40:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485b44:
    esi = 0x5100c3u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485b52:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485b6a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485b52;
L_485b6a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485b6e:
    esi = 0x5100d5u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485b7c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485b94;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485b7c;
L_485b94:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485b98:
    esi = 0x5100e9u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485ba6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485bbe;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485ba6;
L_485bbe:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485bc2:
    esi = 0x5100fdu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485bd0:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485be8;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485bd0;
L_485be8:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485bec:
    esi = 0x51012cu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485bfa:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485c12;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485bfa;
L_485c12:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485c16:
    esi = 0x51013eu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485c24:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485c3c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485c24;
L_485c3c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485c40:
    esi = 0x510157u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485c4e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485c66;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485c4e;
L_485c66:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485c6a:
    esi = 0x51016cu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485c78:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485c90;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485c78;
L_485c90:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485c94:
    esi = 0x510177u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485ca2:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485cba;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485ca2;
L_485cba:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485cbe:
    esi = 0x510187u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485ccc:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485ce4;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485ccc;
L_485ce4:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485ce8:
    esi = 0x510195u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485cf6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485d0e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485cf6;
L_485d0e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485d12:
    esi = 0x5101a6u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485d20:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485d38;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485d20;
L_485d38:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485d3c:
    esi = 0x5101beu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485d4a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485d62;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485d4a;
L_485d62:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485d66:
    esi = 0x5101d2u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485d74:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485d8c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485d74;
L_485d8c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485d90:
    esi = 0x5101e3u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485d9e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485db6;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485d9e;
L_485db6:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485dba:
    esi = 0x5101f6u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485dc8:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485de0;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485dc8;
L_485de0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485de4:
    esi = 0x510243u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485df2:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485e0a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485df2;
L_485e0a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485e0e:
    esi = 0x51025du;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485e1c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485e34;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485e1c;
L_485e34:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485e38:
    esi = 0x51026fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485e46:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485e5e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485e46;
L_485e5e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485e62:
    esi = 0x510285u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485e70:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485e88;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485e70;
L_485e88:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485e8c:
    esi = 0x510294u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485e9a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485eb2;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485e9a;
L_485eb2:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485eb6:
    esi = 0x5102a0u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485ec4:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485edc;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485ec4;
L_485edc:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485ee0:
    esi = 0x5102adu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485eee:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485f06;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485eee;
L_485f06:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485f0a:
    esi = 0x5102beu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485f18:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485f30;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485f18;
L_485f30:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485f34:
    esi = 0x5102cfu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485f42:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485f5a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485f42;
L_485f5a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485f5e:
    esi = 0x5102e3u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485f6c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485f84;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485f6c;
L_485f84:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485f88:
    esi = 0x5102f5u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485f96:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485fae;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485f96;
L_485fae:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485fb2:
    esi = 0x51031fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485fc0:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485fd8;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485fc0;
L_485fd8:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485fdc:
    esi = 0x510332u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485fea:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486002;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485fea;
L_486002:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486006:
    esi = 0x510345u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486014:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48602c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486014;
L_48602c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486030:
    esi = 0x510357u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48603e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486056;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48603e;
L_486056:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48605a:
    esi = 0x51036au;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486068:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486080;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486068;
L_486080:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486084:
    esi = 0x510382u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486092:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4860aa;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486092;
L_4860aa:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4860ae:
    esi = 0x510395u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4860bc:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4860d4;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4860bc;
L_4860d4:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4860d8:
    esi = 0x5103aeu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4860e6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4860fe;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4860e6;
L_4860fe:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486102:
    esi = 0x5103c0u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486110:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486128;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486110;
L_486128:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48612c:
    esi = 0x5103d3u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48613a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486152;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48613a;
L_486152:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486156:
    esi = 0x5103e2u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486164:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48617c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486164;
L_48617c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486180:
    esi = 0x5103f7u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48618e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4861a6;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48618e;
L_4861a6:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4861aa:
    esi = 0x510407u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4861b8:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4861d0;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4861b8;
L_4861d0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4861d4:
    esi = 0x51042fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4861e2:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4861fa;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4861e2;
L_4861fa:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4861fe:
    esi = 0x51043fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48620c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486224;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48620c;
L_486224:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486228:
    esi = 0x510451u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486236:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48624e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486236;
L_48624e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486252:
    esi = 0x510464u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486260:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486278;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486260;
L_486278:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48627c:
    esi = 0x510474u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48628a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4862a2;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48628a;
L_4862a2:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4862a6:
    esi = 0x510486u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4862b4:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4862cc;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4862b4;
L_4862cc:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4862d0:
    esi = 0x51049du;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4862de:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4862f6;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4862de;
L_4862f6:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4862fa:
    esi = 0x5104b3u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486308:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486320;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486308;
L_486320:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486324:
    esi = 0x5104d6u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486332:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48634a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486332;
L_48634a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48634e:
    esi = 0x5104eeu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48635c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486374;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48635c;
L_486374:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486378:
    esi = 0x510500u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486386:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48639e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486386;
L_48639e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4863a2:
    esi = 0x510537u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4863b0:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4863c8;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4863b0;
L_4863c8:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4863cc:
    esi = 0x510554u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4863da:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4863f2;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4863da;
L_4863f2:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4863f6:
    esi = 0x510572u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486404:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48641c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486404;
L_48641c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486420:
    esi = 0x510584u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48642e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486446;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48642e;
L_486446:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48644a:
    esi = 0x51059cu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486458:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486470;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486458;
L_486470:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486474:
    esi = 0x5105aeu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486482:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48649a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486482;
L_48649a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48649e:
    esi = 0x5105c7u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4864ac:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4864c4;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4864ac;
L_4864c4:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4864c8:
    esi = 0x5105dau;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4864d6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4864ee;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4864d6;
L_4864ee:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4864f2:
    esi = 0x5105ebu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486500:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486518;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486500;
L_486518:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48651c:
    esi = 0x5105fdu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48652a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486542;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48652a;
L_486542:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486546:
    esi = 0x51060fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486554:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48656c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486554;
L_48656c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486570:
    esi = 0x510627u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48657e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486596;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48657e;
L_486596:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48659a:
    esi = 0x51063du;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4865a8:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4865c0;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4865a8;
L_4865c0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4865c4:
    esi = 0x510653u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4865d2:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4865ea;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4865d2;
L_4865ea:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4865ee:
    esi = 0x510671u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4865fc:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486614;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4865fc;
L_486614:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486618:
    esi = 0x510687u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486626:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48663e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486626;
L_48663e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486642:
    esi = 0x510697u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486650:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486668;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486650;
L_486668:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48666c:
    if (fl.cf || fl.zf)
        goto L_4863a2;
    {
        (void)lift_sub(32, ecx, 0x8876023bu, &fl);
    }
    if (!fl.cf)
        goto L_4866bf;
    {
        (void)lift_sub(32, ecx, 0x88760219u, &fl);
    }
    if (!fl.cf)
        goto L_4868c4;
    {
        (void)lift_sub(32, ecx, 0x887601ccu, &fl);
    }
    if (!fl.cf)
        goto L_4869c1;
    {
        (void)lift_sub(32, ecx, 0x887601b3u, &fl);
    }
    if (!fl.cf)
        goto L_486a17;
    {
        (void)lift_sub(32, ecx, 0x887601a4u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_4863cc;
    {
        (void)lift_sub(32, ecx, 0x887601aeu, &fl);
    }
    if (fl.zf)
        goto L_4863f6;
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
L_4866bf:
    if (fl.cf || fl.zf)
        goto L_485a48;
    {
        (void)lift_sub(32, ecx, 0x88760248u, &fl);
    }
    if (!fl.cf)
        goto L_48671b;
    {
        (void)lift_sub(32, ecx, 0x88760241u, &fl);
    }
    if (!fl.cf)
        goto L_486802;
    {
        (void)lift_sub(32, ecx, 0x8876023eu, &fl);
    }
    if (!fl.cf)
        goto L_486888;
    {
        (void)lift_sub(32, ecx, 0x8876023cu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485f88;
    esi = 0x51030du;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4866ff:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486717;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4866ff;
L_486717:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48671b:
    if (fl.cf || fl.zf)
        goto L_486180;
    {
        (void)lift_sub(32, ecx, 0x8876024eu, &fl);
    }
    if (!fl.cf)
        goto L_48676b;
    {
        (void)lift_sub(32, ecx, 0x8876024bu, &fl);
    }
    if (!fl.cf)
        goto L_4867c6;
    {
        (void)lift_sub(32, ecx, 0x88760249u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485826;
    esi = 0x510212u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48674f:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486767;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48674f;
L_486767:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48676b:
    if (fl.cf || fl.zf)
        goto L_48659a;
    {
        (void)lift_sub(32, ecx, 0x8876026cu, &fl);
    }
    if (!fl.cf)
        goto L_486794;
    {
        (void)lift_sub(32, ecx, 0x8876024fu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485ee0;
    {
        (void)lift_sub(32, ecx, 0x88760250u, &fl);
    }
    if (fl.zf)
        goto L_485c16;
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
L_486794:
    if (fl.cf || fl.zf)
        goto L_48594c;
    {
        (void)lift_sub(32, ecx, 0x88760294u, &fl);
    }
    if (!fl.cf)
        goto L_4867b1;
    {
        (void)lift_sub(32, ecx, 0x88760280u, &fl);
    }
    if (fl.zf)
        goto L_48587a;
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
L_4867b1:
    if (fl.cf || fl.zf)
        goto L_4858a4;
    {
        (void)lift_sub(32, ecx, 0x887602a8u, &fl);
    }
    if (fl.zf)
        goto L_4861aa;
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
L_4867c6:
    if (fl.cf || fl.zf)
        goto L_486618;
    {
        (void)lift_sub(32, ecx, 0x8876024cu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485a72;
    esi = 0x51041bu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4867e6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4867fe;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4867e6;
L_4867fe:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486802:
    if (fl.cf || fl.zf)
        goto L_486324;
    {
        (void)lift_sub(32, ecx, 0x88760244u, &fl);
    }
    if (!fl.cf)
        goto L_486846;
    {
        (void)lift_sub(32, ecx, 0x88760242u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485f34;
    esi = 0x510116u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48682a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486842;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48682a;
L_486842:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486846:
    if (fl.cf || fl.zf)
        goto L_4860ae;
    {
        (void)lift_sub(32, ecx, 0x88760246u, &fl);
    }
    if (fl.cf)
        goto L_4859ca;
    if (fl.cf || fl.zf)
        goto L_486102;
    esi = 0x50ff07u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48686c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486884;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48686c;
L_486884:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486888:
    if (fl.cf || fl.zf)
        goto L_4857a8;
    {
        (void)lift_sub(32, ecx, 0x8876023fu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485cbe;
    esi = 0x51021du;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4868a8:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4868c0;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4868a8;
L_4868c0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4868c4:
    if (fl.cf || fl.zf)
        goto L_4865c4;
    {
        (void)lift_sub(32, ecx, 0x88760234u, &fl);
    }
    if (!fl.cf)
        goto L_4868ff;
    {
        (void)lift_sub(32, ecx, 0x88760231u, &fl);
    }
    if (!fl.cf)
        goto L_486985;
    {
        (void)lift_sub(32, ecx, 0x8876021cu, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_4865ee;
    {
        (void)lift_sub(32, ecx, 0x88760230u, &fl);
    }
    if (fl.zf)
        goto L_486642;
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
L_4868ff:
    if (fl.cf || fl.zf)
        goto L_486378;
    {
        (void)lift_sub(32, ecx, 0x88760237u, &fl);
    }
    if (!fl.cf)
        goto L_486943;
    {
        (void)lift_sub(32, ecx, 0x88760235u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485e0e;
    esi = 0x510522u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486927:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48693f;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486927;
L_48693f:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486943:
    if (fl.cf || fl.zf)
        goto L_4858ce;
    {
        (void)lift_sub(32, ecx, 0x88760239u, &fl);
    }
    if (fl.cf)
        goto L_485d12;
    if (fl.cf || fl.zf)
        goto L_485eb6;
    esi = 0x510038u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486969:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486981;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486969;
L_486981:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486985:
    if (fl.cf || fl.zf)
        goto L_485b1a;
    {
        (void)lift_sub(32, ecx, 0x88760232u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485976;
    esi = 0x51022eu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4869a5:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4869bd;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4869a5;
L_4869bd:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4869c1:
    if (fl.cf || fl.zf)
        goto L_486474;
    {
        (void)lift_sub(32, ecx, 0x887601eau, &fl);
    }
    if (!fl.cf)
        goto L_4869f0;
    {
        (void)lift_sub(32, ecx, 0x887601d6u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_48649e;
    {
        (void)lift_sub(32, ecx, 0x887601e0u, &fl);
    }
    if (fl.zf)
        goto L_4864c8;
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
L_4869f0:
    if (fl.cf || fl.zf)
        goto L_4864f2;
    {
        (void)lift_sub(32, ecx, 0x887601feu, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_486546;
    {
        (void)lift_sub(32, ecx, 0x88760208u, &fl);
    }
    if (fl.zf)
        goto L_486570;
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
L_486a17:
    if (fl.cf || fl.zf)
        goto L_485850;
    {
        (void)lift_sub(32, ecx, 0x887601b8u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_486420;
    {
        (void)lift_sub(32, ecx, 0x887601c2u, &fl);
    }
    if (fl.zf)
        goto L_48644a;
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
L_486a3e:
    if (fl.cf || fl.zf)
        goto L_485d66;
    {
        (void)lift_sub(32, ecx, 0x8876013cu, &fl);
    }
    if (!fl.cf)
        goto L_486a85;
    {
        (void)lift_sub(32, ecx, 0x887600fau, &fl);
    }
    if (!fl.cf)
        goto L_486b42;
    {
        (void)lift_sub(32, ecx, 0x887600e1u, &fl);
    }
    if (!fl.cf)
        goto L_486b98;
    {
        (void)lift_sub(32, ecx, 0x887600dcu, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_485d90;
    {
        (void)lift_sub(32, ecx, 0x887600deu, &fl);
    }
    if (fl.zf)
        goto L_485de4;
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
L_486a85:
    if (fl.cf || fl.zf)
        goto L_486030;
    {
        (void)lift_sub(32, ecx, 0x8876015eu, &fl);
    }
    if (!fl.cf)
        goto L_486aba;
    {
        (void)lift_sub(32, ecx, 0x8876014au, &fl);
    }
    if (!fl.cf)
        goto L_486b1b;
    {
        (void)lift_sub(32, ecx, 0x8876013du, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_48605a;
    {
        (void)lift_sub(32, ecx, 0x88760140u, &fl);
    }
    if (fl.zf)
        goto L_486084;
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
L_486aba:
    if (fl.cf || fl.zf)
        goto L_486228;
    {
        (void)lift_sub(32, ecx, 0x8876017eu, &fl);
    }
    if (!fl.cf)
        goto L_486ae9;
    {
        (void)lift_sub(32, ecx, 0x88760168u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_486252;
    {
        (void)lift_sub(32, ecx, 0x8876017cu, &fl);
    }
    if (fl.zf)
        goto L_4862a6;
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
L_486ae9:
    if (fl.cf || fl.zf)
        goto L_4862d0;
    {
        (void)lift_sub(32, ecx, 0x88760183u, &fl);
    }
    if (!fl.cf)
        goto L_486b06;
    {
        (void)lift_sub(32, ecx, 0x88760180u, &fl);
    }
    if (fl.zf)
        goto L_4862fa;
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
L_486b06:
    if (fl.cf || fl.zf)
        goto L_48634e;
    {
        (void)lift_sub(32, ecx, 0x88760190u, &fl);
    }
    if (fl.zf)
        goto L_4858f8;
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
L_486b1b:
    if (fl.cf || fl.zf)
        goto L_4860d8;
    {
        (void)lift_sub(32, ecx, 0x8876014fu, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_4861d4;
    {
        (void)lift_sub(32, ecx, 0x88760154u, &fl);
    }
    if (fl.zf)
        goto L_4861fe;
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
L_486b42:
    if (fl.cf || fl.zf)
        goto L_485f0a;
    {
        (void)lift_sub(32, ecx, 0x88760118u, &fl);
    }
    if (!fl.cf)
        goto L_486b71;
    {
        (void)lift_sub(32, ecx, 0x887600ffu, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_48612c;
    {
        (void)lift_sub(32, ecx, 0x88760104u, &fl);
    }
    if (fl.zf)
        goto L_485f5e;
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
L_486b71:
    if (fl.cf || fl.zf)
        goto L_485fb2;
    {
        (void)lift_sub(32, ecx, 0x88760122u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_485fdc;
    {
        (void)lift_sub(32, ecx, 0x88760136u, &fl);
    }
    if (fl.zf)
        goto L_486006;
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
L_486b98:
    if (fl.cf || fl.zf)
        goto L_485e38;
    {
        (void)lift_sub(32, ecx, 0x887600e6u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_485e62;
    {
        (void)lift_sub(32, ecx, 0x887600f0u, &fl);
    }
    if (fl.zf)
        goto L_485e8c;
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
L_486bbf:
    if (fl.cf || fl.zf)
        goto L_485a9c;
    {
        (void)lift_sub(32, ecx, 0x88760096u, &fl);
    }
    if (!fl.cf)
        goto L_486bfa;
    {
        (void)lift_sub(32, ecx, 0x88760078u, &fl);
    }
    if (!fl.cf)
        goto L_486c5b;
    {
        (void)lift_sub(32, ecx, 0x88760064u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_485ac6;
    {
        (void)lift_sub(32, ecx, 0x8876006eu, &fl);
    }
    if (fl.zf)
        goto L_485af0;
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
L_486bfa:
    if (fl.cf || fl.zf)
        goto L_485bec;
    {
        (void)lift_sub(32, ecx, 0x887600b4u, &fl);
    }
    if (!fl.cf)
        goto L_486c29;
    {
        (void)lift_sub(32, ecx, 0x887600a0u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_485c40;
    {
        (void)lift_sub(32, ecx, 0x887600aau, &fl);
    }
    if (fl.zf)
        goto L_485c6a;
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
L_486c29:
    if (fl.cf || fl.zf)
        goto L_485c94;
    {
        (void)lift_sub(32, ecx, 0x887600d2u, &fl);
    }
    if (!fl.cf)
        goto L_486c46;
    {
        (void)lift_sub(32, ecx, 0x887600cdu, &fl);
    }
    if (fl.zf)
        goto L_485ce8;
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
L_486c46:
    if (fl.cf || fl.zf)
        goto L_485d3c;
    {
        (void)lift_sub(32, ecx, 0x887600d4u, &fl);
    }
    if (fl.zf)
        goto L_485dba;
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
L_486c5b:
    if (fl.cf || fl.zf)
        goto L_485b44;
    {
        (void)lift_sub(32, ecx, 0x88760082u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_485b6e;
    {
        (void)lift_sub(32, ecx, 0x88760091u, &fl);
    }
    if (fl.zf)
        goto L_485bc2;
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
L_486c82:
    if (fl.cf || fl.zf)
        goto L_48577e;
    {
        (void)lift_sub(32, ecx, 0x88760028u, &fl);
    }
    if (!fl.cf)
        goto L_486cb1;
    {
        (void)lift_sub(32, ecx, 0x8876000au, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_4857d2;
    {
        (void)lift_sub(32, ecx, 0x88760014u, &fl);
    }
    if (fl.zf)
        goto L_4857fc;
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
L_486cb1:
    if (fl.cf || fl.zf)
        goto L_485922;
    {
        (void)lift_sub(32, ecx, 0x88760037u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_4859a0;
    {
        (void)lift_sub(32, ecx, 0x8876005au, &fl);
    }
    if (fl.zf)
        goto L_485a1e;
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
L_486cd8:
    if (fl.cf || fl.zf)
        goto L_486156;
    {
        (void)lift_sub(32, ecx, 0x8007000eu, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_48627c;
    {
        (void)lift_sub(32, ecx, 0x80070057u, &fl);
    }
    if (fl.zf)
        goto L_485b98;
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

uint32_t lifted_f486ed0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F486ED0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F486ED0_STACK, 0, entry);
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
    esp = esp - 0x10u;
    ebx = eax;
L_486edd:
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x48u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_sub(32, eax, 0x8876021cu, &fl);
    }
    if (fl.zf)
        goto L_486edd;
    esi = esi ^ esi;
L_486ef1:
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x21u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5b9bd0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x64u, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    lift_store(&env, 0u, 0x5b9bccu, 4, eax);
    {
        (void)lift_sub(32, eax, 0x887601c2u, &fl);
    }
    if (fl.zf)
        goto L_486f61;
    esi = esi ^ esi;
L_486f11:
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x11u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5b9bd0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x64u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x64u, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    lift_store(&env, 0u, 0x5b9bccu, 4, eax);
    {
        (void)lift_sub(32, eax, 0x887601c2u, &fl);
    }
    if (!fl.zf)
        goto L_486f7f;
    eax = lift_load(&env, ebx, 0x64u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x6cu, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_486f47;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487080u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_486f11;
L_486f47:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x80u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_486f55:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_486f57:
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
L_486f61:
    eax = lift_load(&env, ebx, 0x64u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x6cu, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_486f55;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487080u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_486ef1;
    goto L_486f57;
L_486f7f:
    edx = edx ^ edx;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x3eu, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = eax ^ eax;
    {
        uint32_t v = 0x10u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x40u, 2)) & 0xffffu);
    ecx = (ebp + 0xffffffdcu);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = lift_load(&env, ebx, 0x64u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x1cu, 4), eax, edx, ebx, ecx, 6, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 24u;
    lift_store(&env, 0u, 0x5b9bccu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_486ff6;
L_486fb9:
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x34u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_sub(32, eax, 0x8876021cu, &fl);
    }
    if (fl.zf)
        goto L_486fb9;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x64u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x80u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x80u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    eax = 0x1u;
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
L_486ff6:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1000000u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffffdcu);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, ebx, 0x64u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x14u, 4), eax, edx, ebx, ecx, 6, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 24u;
    goto L_486fb9;
}

uint32_t lifted_f487060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F487060_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F487060_STACK, 0, entry);
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
L_487065:
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x48u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_sub(32, eax, 0x8876021cu, &fl);
    }
    if (fl.zf)
        goto L_487065;
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

uint32_t lifted_f487080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F487080_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F487080_STACK, 0, entry);
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
    esp = esp - 0x64u;
    esi = eax;
    ebx = ebx ^ ebx;
    edi = edi ^ edi;
L_487091:
    lift_store(&env, ebp, 0xffffff88u, 4, 0x64u);
    edx = (ebp + 0xffffff88u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1000400u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x68u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x14u, 4), eax, edx, ebx, ecx, 6, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 24u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4870cd;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4870b6:
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
L_4870c0:
    ebx = ebx + 1u;
    {
        (void)lift_sub(32, ebx, 0x2u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_487091;
    eax = 0x1u;
    goto L_4870b6;
L_4870cd:
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x64u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x2cu, 4), eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4870c0;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
}

uint32_t lifted_f487130(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F487130_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F487130_STACK, 0, entry);
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
    esp = esp - 0x74u;
    edx = eax;
    ecx = 0x64u;
    ebx = ebx ^ ebx;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffff7cu, 4, ecx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edx, 0x3eu, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edx, 0x40u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, edx, 0x5cu, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_487191;
    {
        uint32_t v = 0x10u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ebp + 0xffffffe0u);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = lift_load(&env, edx, 0x64u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, edx, 0x68u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x1cu, 4), eax, edx, ebx, ecx, 6, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 24u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
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
L_487191:
    ebx = (ebp + 0xffffff7cu);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1000000u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (ebp + 0xffffffe0u);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, edx, 0x64u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, edx, 0x68u, 4);
    edx = (ebp + 0xffffffe0u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x14u, 4), eax, edx, ebx, ecx, 6, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 24u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
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
}

uint32_t lifted_f4871d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4871D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4871D0_STACK, 0, entry);
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
    esp = esp - 0x68u;
    esi = eax;
    lift_store(&env, ebp, 0xffffffecu, 1, (edx & 0xffu));
    ebx = ebx ^ ebx;
    edi = edi ^ edi;
L_4871e3:
    ecx = (ebp + 0xffffff88u);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    {
        uint32_t v = 0x1000400u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x64u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffff88u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x68u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x14u, 4), eax, edx, ebx, ecx, 6, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 24u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_487224;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_48720e:
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
L_487217:
    ebx = ebx + 1u;
    {
        (void)lift_sub(32, ebx, 0x2u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4871e3;
    eax = 0x1u;
    goto L_48720e;
L_487224:
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x64u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x2cu, 4), eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_487217;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_forward_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_FORWARD_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_FORWARD_CALL_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4873d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4873D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4873D0_STACK, 0, entry);
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
    esp = esp - 0x12cu;
    ecx = eax;
    eax = (ebp + 0xffffffd8u);
    ebx = 0x4ec1ecu;
    esi = 0x516d6cu;
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
    edi = edi ^ edi;
    eax = (ebp + 0xfffffec4u);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    ebx = lift_load(&env, 0u, 0x5466c8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (ebp + 0xfffffec4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4874c2;
    edx = (ebp + 0xffffffecu);
    eax = (ebp + 0xfffffec4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482bb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    ebx = ebx ^ ebx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    edx = 0x4u;
    lift_store(&env, ecx, 0x4u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ecx, 0x4u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_487490;
    edx = edx ^ edx;
L_487460:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, edx, eax + 0x0u, 4, 0x0u);
    eax = (ebp + 0xfffffec4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, edx, esi + 0x0u, 4, eax);
    ebx = ebx + 1u;
    esi = lift_load(&env, ecx, 0x4u, 4);
    edx = edx + 0x4u;
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.cf)
        goto L_487460;
L_487490:
    eax = (ebp + 0xfffffec4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a8c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi ^ edi;
    edx = edx ^ edx;
    eax = (ebp + 0xfffffec4u);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    env.chain = eax;
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
L_4874c2:
    eax = (ebp + 0xfffffec4u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    env.chain = eax;
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

uint32_t lifted_array_list_release(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ARRAY_LIST_RELEASE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ARRAY_LIST_RELEASE_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, eax, 0x14u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48754a;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48753d;
    edx = lift_load(&env, ebx, 0x4u, 4);
    ecx = ecx ^ ecx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_487530;
    edx = edx ^ edx;
L_48750d:
    eax = lift_load(&env, ebx, 0x0u, 4);
    eax = lift_load(&env, edx, eax + 0x0u, 4);
    ecx = ecx + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4830f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, ebx, 0x4u, 4);
    edx = edx + 0x4u;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.cf)
        goto L_48750d;
L_487530:
    eax = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, 0x0u);
L_48753d:
    lift_store(&env, ebx, 0x4u, 4, 0x0u);
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
L_48754a:
    ecx = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_48755f;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x8u, 4, 0x0u);
L_48755f:
    esi = lift_load(&env, ebx, 0xcu, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_487574;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0xcu, 4, 0x0u);
L_487574:
    edi = lift_load(&env, ebx, 0x10u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_487589;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x10u, 4, 0x0u);
L_487589:
    lift_store(&env, ebx, 0x14u, 4, 0x0u);
    lift_store(&env, ebx, 0x4u, 4, 0x0u);
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

uint32_t lifted_table_object_construct(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_TABLE_OBJECT_CONSTRUCT_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_TABLE_OBJECT_CONSTRUCT_STACK, 0,
               entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0xcu, 4, 0x516dc4u);
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    edx = lift_load(&env, 0u, 0x4f81ccu, 4);
    lift_store(&env, eax, 0x8u, 4, 0x0u);
    lift_store(&env, eax, 0x4u, 4, edx);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f487920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F487920_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F487920_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, eax, 0x0u, 4, 0x516e34u);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_list_empty(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_LIST_EMPTY_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_LIST_EMPTY_STACK, 0, entry);
    eax = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.cf || fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_release_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_RELEASE_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_RELEASE_CALL_STACK, 0, entry);
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
    ecx = 0x1u;
    esi = lift_load(&env, eax, 0x8u, 4);
    ebx = edx;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d88a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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

uint32_t lifted_forward_registers_487a10(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_FORWARD_REGISTERS_487A10_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_FORWARD_REGISTERS_487A10_STACK, 0,
               entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487a20u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_list_item(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_LIST_ITEM_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_LIST_ITEM_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.cf)
        goto L_487a30;
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, eax, (edx * 4u) + 0x0u, 4);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_487a30:
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

uint32_t lifted_object_construct_g(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_CONSTRUCT_G_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_CONSTRUCT_G_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x488b10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, eax, 0x0u, 4, 0x516f04u);
    lift_store(&env, eax, 0x10u, 4, 0x0u);
    lift_store(&env, eax, 0x14u, 4, 0x0u);
    lift_store(&env, eax, 0x18u, 4, 0x0u);
    lift_store(&env, eax, 0x1cu, 4, 0x0u);
    lift_store(&env, eax, 0x20u, 4, 0x0u);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f487be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F487BE0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F487BE0_STACK, 0, entry);
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
    esp = esp - 0x2cu;
    esi = eax;
    eax = (ebp + 0xffffffc4u);
    ecx = 0x4ec1ecu;
    ebx = 0x516e8cu;
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
    edi = edi ^ edi;
    eax = (ebp + 0xffffffe8u);
    lift_store(&env, ebp, 0xffffffc8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x1u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x488c50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_487ce5;
    ecx = 0x8u;
    edx = (ebp + 0xffffffd8u);
    ebx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489230u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(32, edx, 0xau, &fl);
    }
    if (!fl.zf)
        goto L_487d0b;
    lift_store(&env, esi, 0x10u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, esi, 0x14u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_487ce0;
    edx = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x20u, 4, eax);
    edx = 0x4u;
    eax = lift_load(&env, esi, 0x14u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x1cu, 4, eax);
    edx = 0x4u;
    eax = lift_load(&env, esi, 0x14u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = lift_load(&env, esi, 0x14u, 4);
    lift_store(&env, esi, 0x18u, 4, eax);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_487ce0;
    edi = edi ^ edi;
L_487c99:
    ecx = 0x8u;
    ebx = 0x1u;
    edx = (ebp + 0xffffffe0u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489230u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4893c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esi, 0x20u, 4);
    lift_store(&env, edx, edi + 0x0u, 4, eax);
    eax = lift_load(&env, esi, 0x1cu, 4);
    edx = (eax + edi);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    edx = lift_load(&env, esi, 0x18u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, edx, edi + 0x0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    edi = edi + 0x4u;
    eax = eax + 1u;
    edx = lift_load(&env, esi, 0x14u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf)
        goto L_487c99;
L_487ce0:
    edi = 0x1u;
L_487ce5:
    eax = (ebp + 0xffffffe8u);
    ecx = ecx ^ ecx;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    env.chain = eax;
    eax = edi;
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
L_487d0b:
    edx = lift_load(&env, esi, 0x0u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x54u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe8u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    env.chain = eax;
    eax = edi;
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

uint32_t lifted_list_find_name(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_LIST_FIND_NAME_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_LIST_FIND_NAME_STACK, 0, entry);
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
    esp = esp - 0x4u;
    esi = eax;
    edi = edx;
    edx = 0xffffffffu;
    ebx = lift_load(&env, eax, 0x14u, 4);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_488007;
    ebx = ebx ^ ebx;
L_487ff1:
    eax = lift_load(&env, esi, 0x20u, 4);
    eax = eax + ebx;
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_488013;
L_487ffc:
    ecx = ecx + 1u;
    eax = lift_load(&env, esi, 0x14u, 4);
    ebx = ebx + 0x4u;
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.cf)
        goto L_487ff1;
L_488007:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
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
L_488013:
    eax = edx;
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_487ffc;
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
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

uint32_t lifted_table_item(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_TABLE_ITEM_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_TABLE_ITEM_STACK, 0, entry);
    eax = lift_load(&env, eax, 0x18u, 4);
    eax = lift_load(&env, eax, (edx * 4u) + 0x0u, 4);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_table_item_488040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_TABLE_ITEM_488040_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_TABLE_ITEM_488040_STACK, 0, entry);
    eax = lift_load(&env, eax, 0x1cu, 4);
    eax = lift_load(&env, eax, (edx * 4u) + 0x0u, 4);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f488050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F488050_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F488050_STACK, 0, entry);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487fd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = esi ^ esi;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_488067;
L_488061:
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_488067:
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x488040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489b20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_488061;
    esi = 0x1u;
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_path_last_separator(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PATH_LAST_SEPARATOR_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PATH_LAST_SEPARATOR_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    eax = edx;
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4885b3;
L_4885a9:
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x5cu, &fl);
    }
    if (fl.zf)
        goto L_4885b3;
    eax = eax - 1u;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4885a9;
L_4885b3:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_path_is_network(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PATH_IS_NETWORK_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PATH_IS_NETWORK_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x5cu, &fl);
    }
    if (!fl.zf)
        goto L_488954;
    {
        (void)lift_sub(8, (edx & 0xffu), lift_load(&env, eax, 0x1u, 1), &fl);
    }
    if (!fl.zf)
        goto L_488954;
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_488954:
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

uint32_t lifted_f489170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F489170_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F489170_STACK, 0, entry);
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
    esp = esp - 0x68u;
    esi = eax;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    eax = (ebp + 0xffffffc4u);
    edx = 0x4ec1ecu;
    ecx = 0x517144u;
    edi = 0x1u;
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
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    eax = (ebp + 0xffffffd8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d93f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x2u);
    eax = (ebp + 0xffffff90u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9f06u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (!fl.zf)
        goto L_489211;
    ecx = 0x4u;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    esi = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4da6b6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, esi);
L_4891eb:
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9430u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    env.chain = eax;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
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
L_489211:
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t r = lift_imul(32, ebx, lift_load(&env, ebp, 0xfffffff4u, 4), &fl);
        ebx = r;
    }
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d79c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4891eb;
}

uint32_t lifted_f489230(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F489230_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F489230_STACK, 0, entry);
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
    esp = esp - 0x6cu;
    esi = eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    eax = (ebp + 0xffffffc0u);
    edx = 0x4ec1ecu;
    ecx = 0x517168u;
    edi = 0x1u;
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
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
    lift_store(&env, ebp, 0xffffffc8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    eax = (ebp + 0xffffffd4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d93f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffccu, 4, 0x2u);
    eax = (ebp + 0xffffff8cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9f06u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.zf)
        goto L_4892dc;
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t r = lift_imul(32, ebx, lift_load(&env, ebp, 0xffffffe0u, 4), &fl);
        ebx = r;
    }
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d7980u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_4892a1:
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffccu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9430u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffccu, 4, edi);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4892c3;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, ebp, 0xffffffe0u, 4), &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffecu, 4), &fl);
    }
    if (fl.zf)
        goto L_4892c3;
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
L_4892c3:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    env.chain = eax;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
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
L_4892dc:
    ecx = 0x4u;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    esi = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4da6b6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffccu, 4, esi);
    goto L_4892a1;
}

uint32_t lifted_f4893c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4893C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4893C0_STACK, 0, entry);
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
    esp = esp - 0x1cu;
    edi = eax;
    eax = (ebp + 0xffffffd0u);
    edx = 0x4ec1ecu;
    ecx = 0x517190u;
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
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    eax = edi;
    ecx = 0x4u;
    ebx = 0x1u;
    edx = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489230u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_489423;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
L_48940e:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    env.chain = eax;
    eax = esi;
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
L_489423:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = 0x1u;
    eax = eax + 1u;
    ecx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    esi = eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    edx = eax;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489230u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_489457;
    {
        uint32_t r = lift_add(32, esi, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
        esi = r;
    }
    lift_store(&env, esi, 0x0u, 1, 0x0u);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    goto L_48940e;
L_489457:
    eax = esi;
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    goto L_48940e;
}

uint32_t lifted_rtl_write_text_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_WRITE_TEXT_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_WRITE_TEXT_CALL_STACK, 0, entry);
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
    esp = esp - 0x8u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    esi = edx;
    edi = edx;
    ebx = 0x4u;
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
    edx = (ebp + 0xffffffe8u);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d79c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d79c0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_find_attribute_flag(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_FIND_ATTRIBUTE_FLAG_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_FIND_ATTRIBUTE_FLAG_STACK, 0, entry);
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
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x118u;
    edx = (ebp + 0xfffffee0u);
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
    eax = lift_call(&env, 0x4d9060u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xfffffef0u, 1), 0x1u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    esp = (ebp + 0xfffffff8u);
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
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f489a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F489A10_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F489A10_STACK, 0, entry);
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
    esp = esp - 0x60u;
    edx = eax;
    eax = (ebp + 0xffffffc0u);
    ecx = 0x4ec1ecu;
    ebx = 0x517210u;
    edi = 0x2u;
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
    esi = esi ^ esi;
    eax = (ebp + 0xffffffd4u);
    lift_store(&env, ebp, 0xffffffc4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffc8u, 4, ebx);
    lift_store(&env, ebp, 0xffffffccu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d93f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffff8cu);
    lift_store(&env, ebp, 0xffffffccu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9f06u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_489ace;
    lift_store(&env, ebp, 0xffffffccu, 4, 0x4u);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_489a96;
    edx = eax;
    eax = (ebp + 0xffffffdcu);
    ecx = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x488d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffdcu);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
L_489a96:
    edi = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4da6b6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffccu, 4, edi);
L_489aa3:
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9430u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    env.chain = eax;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
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
L_489ace:
    ecx = lift_load(&env, edx, 0x0u, 4);
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x38u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    goto L_489aa3;
}

uint32_t lifted_f489b20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F489B20_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F489B20_STACK, 0, entry);
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
    ecx = lift_load(&env, eax, 0x0u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x30u, 4), eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f489fa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F489FA0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F489FA0_STACK, 0, entry);
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
    esp = esp - 0x34u;
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_48a024;
    edx = 0x4ec1ecu;
    esi = 0x5175a0u;
    lift_store(&env, eax, 0x14u, 4, 0x517644u);
    edi = 0x3u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffe8u, 1, (ebx & 0xffu));
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
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    eax = ecx;
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b78e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_48a010;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48a010:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    env.chain = eax;
    eax = ecx;
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
L_48a024:
    ebx = 0x1u;
    edx = 0x513f10u;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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

uint32_t lifted_f48a100(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48A100_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48A100_STACK, 0, entry);
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
    esp = esp - 0x2cu;
    esi = eax;
    edi = edx;
    eax = (ebp + 0xffffffc4u);
    edx = 0x4ec1ecu;
    ecx = 0x5175c8u;
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
    ebx = ebx ^ ebx;
    eax = (ebp + 0xffffffd8u);
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x1u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48a14b:
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48a1b7;
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
L_48a164:
    eax = esi;
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_48a282;
    edi = edi ^ edi;
L_48a178:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.cf)
        goto L_48a27a;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (ebp + 0xffffffe4u);
    ecx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a300u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    edi = edi + edx;
    goto L_48a178;
L_48a1b7:
    eax = 0x14u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48a1dd;
    edx = 0x2u;
    ecx = 0x1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
L_48a1dd:
    ebx = 0x1u;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
L_48a1e7:
    ebx = (ebp + 0xffffffd8u);
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a3c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffd8u);
    eax = (ebp + 0xffffffe0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x4u);
    edx = eax;
    eax = ecx;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe0u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edi;
    eax = esi;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a420u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_48a233;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_48a233:
    ebx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_48a1e7;
    eax = lift_load(&env, ecx, 0x8u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_48a25e;
    edx = ecx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b79a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48a252:
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x1u);
    goto L_48a14b;
L_48a25e:
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_48a252;
    ebx = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x2u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x1u);
    goto L_48a14b;
L_48a27a:
    lift_store(&env, ebp, 0xffffffe8u, 4, lift_load(&env, ebp, 0xffffffe8u, 4) + 1u);
    goto L_48a164;
L_48a282:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_48a2b0;
    eax = (ebp + 0xffffffd8u);
    edx = edx ^ edx;
    edi = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    env.chain = eax;
    eax = edi;
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
L_48a2b0:
    eax = (ebp + 0xffffffd8u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    env.chain = eax;
    eax = edi;
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

uint32_t lifted_f48a710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48A710_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48A710_STACK, 0, entry);
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
    esp = esp - 0x24u;
    edi = eax;
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    esi = ebx;
    eax = (ebp + 0xffffffd0u);
    edx = 0x4ec1ecu;
    ecx = 0x51765cu;
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
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_48a82a;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4895e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48a7ee;
    eax = 0x10u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48a783;
    esi = 0x1u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x488b10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    esi = eax;
L_48a783:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = esi;
    lift_store(&env, ebp, 0xffffffecu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x488c50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48a7d5;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489a10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48a7ca;
    ebx = 0x1u;
    edx = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x0u, 4, eax);
    ebx = 0x1u;
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489230u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48a7ca:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x54u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48a7d5:
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_48a7e9;
    ecx = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x2u;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48a7e9:
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
L_48a7ee:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48a88e;
L_48a7f7:
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
L_48a7fa:
    edi = edi + 0xcu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_48a7fe:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48a816;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48a7fe;
L_48a816:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    env.chain = eax;
    eax = ebx;
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
L_48a82a:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x488050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48a7ee;
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487fd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x488030u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x488040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_48a7ee;
    ebx = 0x1u;
    eax = ecx;
    edx = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x0u, 4, eax);
    ebx = 0x1u;
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489230u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_48a7f7;
L_48a88e:
    esi = 0x510ab9u;
    goto L_48a7fa;
}

uint32_t lifted_f48ac50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48AC50_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48AC50_STACK, 0, entry);
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
    esp = esp - 0x128u;
    edx = eax;
    eax = (ebp + 0xffffffd8u);
    ecx = 0x4ec1ecu;
    ebx = 0x5176c0u;
    edi = 0x1u;
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
    esi = esi ^ esi;
    eax = (ebp + 0xfffffec4u);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffec4u);
    ebx = lift_load(&env, 0u, 0x5466c8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx ^ ecx;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.zf)
        goto L_48acdd;
L_48acb1:
    eax = eax ^ eax;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (ebp + 0xfffffec4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    env.chain = eax;
    eax = ecx;
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
L_48acdd:
    eax = (ebp + 0xfffffec4u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48ae00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = (ebp + 0xfffffec4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a8c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_48acb1;
}

uint32_t lifted_f48ad00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48AD00_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48AD00_STACK, 0, entry);
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
    esp = esp - 0x154u;
    edi = eax;
    esi = edx;
    eax = (ebp + 0xffffffdcu);
    edx = 0x4ec1ecu;
    ecx = 0x5176ccu;
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
    ebx = ebx ^ ebx;
    eax = (ebp + 0xffffffb0u);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481b20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    {
        uint32_t v = 0xff000000u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0xffu;
    ebx = 0xff00u;
    edx = 0xff0000u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = (ebp + 0xffffffb0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481bc0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48add1;
    eax = (ebp + 0xfffffe9cu);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe9cu);
    ebx = lift_load(&env, 0u, 0x5466c8u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    edx = edi;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48adaf;
    eax = (ebp + 0xfffffe9cu);
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48ae00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = (ebp + 0xfffffe9cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a8c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48adaf:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = ecx;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
    eax = esi;
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
L_48add1:
    eax = (ebp + 0xffffffb0u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481b30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
    eax = esi;
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

uint32_t lifted_f48ae00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48AE00_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48AE00_STACK, 0, entry);
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
    esp = esp - 0x2f0u;
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    eax = (ebp + 0xffffffb4u);
    edx = 0x4ec1ecu;
    ecx = 0x5176e0u;
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
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffb8u, 4, edx);
    lift_store(&env, ebp, 0xffffffbcu, 4, ecx);
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    eax = (ebp + 0xfffffed0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c3fa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xfffffd00u, 4, eax);
    lift_store(&env, ebp, 0xfffffed0u, 4, 0x48ac10u);
    eax = (ebp + 0xffffff54u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9f06u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    edx = (edx & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_48aeaa;
    eax = (ebp + 0xfffffd00u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b9310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48ae90;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48ae90:
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, edi);
L_48ae95:
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    env.chain = eax;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
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
L_48aeaa:
    ebx = 0x1d0u;
    edx = 0x3eu;
    eax = (ebp + 0xfffffd00u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b9220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = (ebp + 0xfffffd00u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b9cf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = (ebp + 0xfffffd00u);
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b9540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xfffffd50u, 4, ecx);
    lift_store(&env, ebp, 0xfffffd58u, 4, ecx);
    eax = (ebp + 0xfffffd00u);
    esi = 0x1u;
    ecx = 0xffu;
    ebx = 0xff00u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b97c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffff88u);
    edx = 0xff0000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481b20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0xff000000u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff88u);
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481bc0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48b02c;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48b03e;
    lift_store(&env, ebp, 0xffffffecu, 1, 0x4u);
L_48af38:
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    edx = lift_load(&env, ebp, 0xfffffd74u, 4);
    eax = lift_load(&env, ebp, 0xfffffd70u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48af63;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x14u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, eax, 0xdu, 1, (edx & 0xffu));
L_48af63:
    eax = lift_load(&env, ebp, 0xfffffd70u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = lift_load(&env, ebp, 0xfffffd74u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = lift_load(&env, ebp, 0xfffffd70u, 4);
    edx = lift_load(&env, ebp, 0xfffffd7cu, 4);
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ecx = 0x1u;
    eax = (ebp + 0xfffffd00u);
    edx = ecx;
    esi = lift_load(&env, ebp, 0xfffffd04u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xfffffd78u, 4), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_48b202;
L_48afb0:
    eax = lift_load(&env, ebp, 0xfffffd8cu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xfffffd74u, 4), &fl);
    }
    if (!fl.cf)
        goto L_48b202;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = 0x1u;
    eax = (ebp + 0xfffffd00u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b99b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, ebp, 0xfffffd8cu, 4);
    esi = esi - 1u;
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = lift_load(&env, ecx, 0x0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_48b04b;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        uint32_t r = lift_imul(32, esi, lift_load(&env, eax, 0x4u, 4), &fl);
        esi = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    edx = edx + esi;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_48afb0;
L_48afff:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1u, 1)) & 0xffu);
    esi = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        esi = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        eax = r;
    }
    esi = esi | eax;
    eax = eax ^ eax;
    edx = edx + 0x4u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x2u, 1)) & 0xffu);
    ecx = ecx + 0x3u;
    eax = eax | esi;
    ebx = ebx + 0x3u;
    lift_store(&env, edx, 0xfffffffcu, 4, eax);
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_48afff;
    goto L_48afb0;
L_48b02c:
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = (ebp + 0xffffff88u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481b30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_48ae95;
L_48b03e:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffecu, 1, (eax & 0xffu));
    goto L_48af38;
L_48b04b:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48b0b1;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        uint32_t r = lift_imul(32, esi, lift_load(&env, eax, 0x4u, 4), &fl);
        esi = r;
    }
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    edi = lift_load(&env, eax, 0x0u, 4);
    edi = edi + esi;
    esi = esi ^ esi;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_48afb0;
L_48b06d:
    eax = eax ^ eax;
    edx = edx ^ edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx | eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x2u, 1)) & 0xffu);
    edx = edx | eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (ebp + 0xffffff88u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481d90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    ecx = ecx + 0x3u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    esi = esi + 0x3u;
    lift_store(&env, edi, 0xffffffffu, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_48afb0;
    goto L_48b06d;
L_48b0b1:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_48b119;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        uint32_t r = lift_imul(32, esi, lift_load(&env, eax, 0x4u, 4), &fl);
        esi = r;
    }
    esi = esi + esi;
    edi = lift_load(&env, ebp, 0xffffffd0u, 4);
    edi = lift_load(&env, edi, 0x0u, 4);
    edi = edi + esi;
    esi = esi ^ esi;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_48afb0;
L_48b0d2:
    eax = eax ^ eax;
    edx = edx ^ edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx | eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x2u, 1)) & 0xffu);
    edx = edx | eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (ebp + 0xffffff88u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481d90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi + 0x2u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    ecx = ecx + 0x3u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = esi + 0x3u;
    lift_store(&env, edi, 0xfffffffeu, 2, (eax & 0xffffu));
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_48afb0;
    goto L_48b0d2;
L_48b119:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_48b197;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        uint32_t r = lift_imul(32, esi, lift_load(&env, eax, 0x4u, 4), &fl);
        esi = r;
    }
    eax = (esi + (esi * 2u));
    esi = lift_load(&env, ebp, 0xffffffd0u, 4);
    esi = lift_load(&env, esi, 0x0u, 4);
    edi = edi ^ edi;
    esi = esi + eax;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_48afb0;
L_48b13b:
    eax = eax ^ eax;
    edx = edx ^ edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = eax | edx;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x2u, 1)) & 0xffu);
    eax = eax | edx;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = eax;
    eax = (ebp + 0xffffff88u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481d90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = eax & 0xff0000u;
    esi = esi + 1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0xffffffffu, 1, (eax & 0xffu));
    eax = eax ^ eax;
    esi = esi + 1u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe8u, 2)) & 0xffffu);
    esi = esi + 1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        eax = r;
    }
    ecx = ecx + 0x3u;
    lift_store(&env, esi, 0xfffffffeu, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    edi = edi + 0x3u;
    lift_store(&env, esi, 0xffffffffu, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_48afb0;
    goto L_48b13b;
L_48b197:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_48afb0;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        uint32_t r = lift_imul(32, esi, lift_load(&env, eax, 0x4u, 4), &fl);
        esi = r;
    }
    edx = ((esi * 4u));
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    esi = lift_load(&env, eax, 0x0u, 4);
    edi = edi ^ edi;
    esi = esi + edx;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_48afb0;
L_48b1c1:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1u, 1)) & 0xffu);
    edx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax | edx;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x2u, 1)) & 0xffu);
    eax = eax | edx;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = eax;
    esi = esi + 0x4u;
    ecx = ecx + 0x3u;
    eax = (ebp + 0xffffff88u);
    edi = edi + 0x3u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481d90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0xfffffffcu, 4, eax);
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_48afb0;
    goto L_48b1c1;
L_48b202:
    eax = (ebp + 0xfffffd00u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b9710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffd00u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b9310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = (ebp + 0xffffff88u);
    edi = edi ^ edi;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481b30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
    goto L_48ae95;
}

uint32_t lifted_f48b550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48B550_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48B550_STACK, 0, entry);
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
    esp = esp - 0x20u;
    edx = eax;
    eax = (ebp + 0xffffffccu);
    ecx = 0x4ec1ecu;
    ebx = 0x517740u;
    edi = 0x1u;
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
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    ecx = 0x3u;
    lift_store(&env, ebp, 0xffffffe4u, 1, ((eax >> 8) & 0xffu));
    eax = edx;
    ebx = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47e4f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x2u;
    eax = eax + 0x1ecu;
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax + 0x14u;
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax + 0x14u;
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (eax + 0xfffffdecu);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    lift_store(&env, 0u, 0x5bb47cu, 4, esi);
    lift_store(&env, edx, 0x1c8u, 4, 0x517994u);
    lift_store(&env, 0u, 0x5bb480u, 4, esi);
    lift_store(&env, edx, 0x1ccu, 1, 0x3u);
    lift_store(&env, 0u, 0x5bb484u, 4, esi);
    lift_store(&env, edx, 0x1d0u, 1, 0x4u);
    lift_store(&env, 0u, 0x5bb488u, 4, esi);
    lift_store(&env, edx, 0x1d8u, 1, 0x5u);
    lift_store(&env, 0u, 0x5bb48cu, 4, esi);
    lift_store(&env, edx, 0x1e0u, 1, 0x6u);
    lift_store(&env, 0u, 0x5bb490u, 4, esi);
    lift_store(&env, edx, 0x1e2u, 1, 0x7u);
    lift_store(&env, 0u, 0x5bb494u, 4, esi);
    lift_store(&env, edx, 0x1e4u, 1, 0x8u);
    lift_store(&env, 0u, 0x5bb498u, 4, esi);
    lift_store(&env, edx, 0x1e5u, 1, 0x9u);
    lift_store(&env, 0u, 0x5bb49cu, 4, esi);
    lift_store(&env, edx, 0x1e6u, 1, 0xau);
    lift_store(&env, 0u, 0x5bb4a0u, 4, esi);
    lift_store(&env, edx, 0x1e7u, 1, 0x2u);
    lift_store(&env, 0u, 0x5bb4a4u, 4, esi);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, 0u, 0x558cccu, 4, edx);
    env.chain = eax;
    eax = edx;
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
}

uint32_t lifted_f48b770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48B770_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48B770_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48b970u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (edx + 0x1ecu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d6c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (edx + 0x200u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d6c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (edx + 0x214u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d6c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47e780u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f48b7e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48B7E0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48B7E0_STACK, 0, entry);
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5bb47cu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5bb480u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5bb484u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5bb488u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5bb48cu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5bb490u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5bb494u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5bb498u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5bb49cu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5bb4a0u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    lift_store(&env, 0u, 0x5bb4a4u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb47cu, 4);
    lift_store(&env, 0u, 0x5bb4a8u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb488u, 4);
    lift_store(&env, 0u, 0x5bb4acu, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb494u, 4);
    lift_store(&env, 0u, 0x5bb4b0u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb484u, 4);
    lift_store(&env, 0u, 0x5bb4b4u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb488u, 4);
    lift_store(&env, 0u, 0x5bb4b8u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb494u, 4);
    lift_store(&env, 0u, 0x5bb4bcu, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb48cu, 4);
    lift_store(&env, 0u, 0x5bb4c0u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb488u, 4);
    lift_store(&env, 0u, 0x5bb4c4u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb494u, 4);
    lift_store(&env, 0u, 0x5bb4c8u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb490u, 4);
    lift_store(&env, 0u, 0x5bb4ccu, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb488u, 4);
    lift_store(&env, 0u, 0x5bb4d0u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb49cu, 4);
    lift_store(&env, 0u, 0x5bb4d4u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb488u, 4);
    lift_store(&env, 0u, 0x5bb4d8u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb494u, 4);
    lift_store(&env, 0u, 0x5bb4dcu, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb4a0u, 4);
    lift_store(&env, 0u, 0x5bb4e0u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb488u, 4);
    lift_store(&env, 0u, 0x5bb4e4u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb494u, 4);
    lift_store(&env, 0u, 0x5bb4e8u, 4, eax);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f48bca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48BCA0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48BCA0_STACK, 0, entry);
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
    ebx = edx;
    {
        uint32_t v = 0x5328d8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ecx = (esi + 0x1ecu);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d5f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_48bd20;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48bd20;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x8u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x8u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x9u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x9u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xau, 1)) & 0xffu);
    lift_store(&env, ebx, 0xau, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xbu, 1)) & 0xffu);
    lift_store(&env, ebx, 0xbu, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xcu, 1)) & 0xffu);
    lift_store(&env, ebx, 0xcu, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xdu, 1)) & 0xffu);
    lift_store(&env, ebx, 0xdu, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xeu, 1)) & 0xffu);
    lift_store(&env, ebx, 0xeu, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xfu, 1)) & 0xffu);
    lift_store(&env, ebx, 0xfu, 1, (edx & 0xffu));
    edx = lift_load(&env, eax, 0x2cu, 4);
    lift_store(&env, ebx, 0x2cu, 4, edx);
    edx = lift_load(&env, eax, 0x20u, 4);
    lift_store(&env, ebx, 0x20u, 4, edx);
    eax = lift_load(&env, eax, 0x14u, 4);
    edx = edx ^ edx;
    lift_store(&env, ebx, 0x14u, 4, eax);
    ebx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48bd20:
    eax = (esi + 0x1ecu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d5f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_48bd40;
    {
        uint32_t v = 0x5328d8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
L_48bd40:
    edx = lift_load(&env, 0u, 0x5bb49cu, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c7cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x5328d8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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

uint32_t lifted_f48be70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48BE70_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48BE70_STACK, 0, entry);
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
    ebx = edx;
    {
        uint32_t v = 0x5328f0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ecx = (esi + 0x200u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d5f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_48bef4;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48bef4;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x0u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x1u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x1u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x2u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x2u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x3u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x3u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x4u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x4u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x5u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x5u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x6u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x6u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x7u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x7u, 1, (edx & 0xffu));
    edx = lift_load(&env, eax, 0x20u, 4);
    lift_store(&env, ebx, 0x20u, 4, edx);
    edx = lift_load(&env, eax, 0x2cu, 4);
    lift_store(&env, ebx, 0x2cu, 4, edx);
    edx = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, ebx, 0x14u, 4, edx);
    eax = lift_load(&env, eax, 0x18u, 4);
    edx = edx ^ edx;
    lift_store(&env, ebx, 0x18u, 4, eax);
    ebx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48bef4:
    eax = (esi + 0x200u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d5f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_48bf14;
    {
        uint32_t v = 0x5328f0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
L_48bf14:
    edx = lift_load(&env, 0u, 0x5bb4a0u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c7cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x5328f0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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

uint32_t lifted_f48c0f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48C0F0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48C0F0_STACK, 0, entry);
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
    esp = esp - 0x14u;
    esi = eax;
    edi = ebx;
    ecx = lift_load(&env, edx, 0x2cu, 4);
    {
        (void)lift_sub(32, ecx, 0xffu, &fl);
    }
    if (!fl.cf)
        goto L_48c200;
    eax = ecx;
L_48c10e:
    ebx = lift_load(&env, edx, 0x20u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(32, ebx, 0xffu, &fl);
    }
    if (!fl.cf)
        goto L_48c20a;
    eax = ebx;
L_48c123:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, 0x2u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe0u, 2, (eax & 0xffffu));
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, edx, 0x4u, 1)) & 0xffu) << 8);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, edx, 0x0u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffecu, 1, ((ebx >> 8) & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x1u, 1)) & 0xffu);
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, edx, 0x5u, 1)) & 0xffu) << 8);
    {
        uint32_t a = ((eax >> 8) & 0xffu);
        uint32_t r = lift_shl(8, a, 0x3u, &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    lift_store(&env, ebp, 0xfffffff0u, 1, ((ebx >> 8) & 0xffu));
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_shl(8, a, 0x2u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, edx, 0x7u, 1)) & 0xffu) << 8);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) | (eax & 0xffu)) & 0xffu) << 8);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) + (ebx & 0xffu)) & 0xffu);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | ((eax >> 8) & 0xffu)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_shl(8, a, 0x7u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu) << 8);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, edx, 0x3u, 1)) & 0xffu) << 8);
    {
        uint32_t a = ((eax >> 8) & 0xffu);
        uint32_t r = lift_shl(8, a, 0x6u, &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x6u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) | ((eax >> 8) & 0xffu)) & 0xffu);
    eax = (eax & 0xffff00ffu) | ((((ecx & 0xffu)) & 0xffu) << 8);
    {
        uint32_t a = ((eax >> 8) & 0xffu);
        uint32_t r = lift_shl(8, a, 0x5u, &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | ((ecx >> 8) & 0xffu)) & 0xffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) | (eax & 0xffu)) & 0xffu) << 8);
    eax = (eax & 0xffffff00u) | ((((ebx >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_shl(8, a, 0x4u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) | ((eax >> 8) & 0xffu)) & 0xffu);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | (eax & 0xffu)) & 0xffu);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe4u, 2)) & 0xffffu);
    lift_store(&env, edx, 0x2cu, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe0u, 2)) & 0xffffu);
    lift_store(&env, edx, 0x20u, 4, eax);
    eax = 0x38u;
    lift_store(&env, ebp, 0xffffffe8u, 1, (ebx & 0xffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48c198;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d330u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48c198:
    ebx = eax;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d3e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x5328f0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (esi + 0x214u);
    edx = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x5328f0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    lift_store(&env, esi, 0x1e8u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_store(&env, esi, 0x1e9u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    edx = (esi + 0x1e7u);
    lift_store(&env, esi, 0x1eau, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48c214;
    ebx = 0x4u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c9b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_48c200:
    eax = 0xffu;
    goto L_48c10e;
L_48c20a:
    eax = 0xffu;
    goto L_48c123;
L_48c214:
    ebx = 0x4u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c9d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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

uint32_t lifted_object_notify_choice(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_NOTIFY_CHOICE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_NOTIFY_CHOICE_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, eax, 0x44u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48c2d7;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x532a68u, 1)) & 0xffu);
L_48c2be:
    lift_store(&env, eax, 0x1e1u, 1, (edx & 0xffu));
    ebx = 0x2u;
    edx = (eax + 0x1e0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c9b0u, eax, edx, ebx, ecx, 0, esp);
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
L_48c2d7:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x532a6cu, 1)) & 0xffu);
    goto L_48c2be;
}

uint32_t lifted_object_notify_byte(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_NOTIFY_BYTE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_NOTIFY_BYTE_STACK, 0, entry);
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
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x532a70u, 1)) & 0xffu);
    lift_store(&env, eax, 0x1e3u, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x44u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_48c2f9;
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
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48c2f9:
    ebx = 0x2u;
    edx = (eax + 0x1e2u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c9b0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_object_notify_field_48c310(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_NOTIFY_FIELD_48C310_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_NOTIFY_FIELD_48C310_STACK, 0,
               entry);
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
    ebx = 0x1u;
    edx = (eax + 0x1e4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c9b0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f48c390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48C390_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48C390_STACK, 0, entry);
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
    edx = lift_load(&env, 0u, 0x532becu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f790u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f48c3b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48C3B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48C3B0_STACK, 0, entry);
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
    edx = lift_load(&env, 0u, 0x532becu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f830u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f48c3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48C3D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48C3D0_STACK, 0, entry);
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
    edx = lift_load(&env, 0u, 0x532be8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47ed50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x2u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f8e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532be0u, 4);
    edx = lift_load(&env, 0u, 0x532be4u, 4);
    eax = eax + eax;
    edx = edx | eax;
    eax = lift_load(&env, 0u, 0x532bdcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax | edx;
    edx = lift_load(&env, 0u, 0x532bd8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    eax = eax | edx;
    edx = lift_load(&env, 0u, 0x532bd4u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x7u, &fl);
        edx = r;
    }
    edx = edx | eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47ed60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f7b40u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47ed70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x532b88u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47ed80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47ed90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47eda0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f48c460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48C460_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48C460_STACK, 0, entry);
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
    edx = lift_load(&env, 0u, 0x532becu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f4b0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f48c480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48C480_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48C480_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = 0x532c04u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7020u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f430u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f48c4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48C4A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48C4A0_STACK, 0, entry);
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
    esp = esp - 0x24u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = (ebp + 0xffffffc8u);
    edx = 0x4ec1ecu;
    ecx = 0x5177acu;
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
    ebx = ebx ^ ebx;
    eax = 0x532c04u;
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7020u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x558c9cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_48c5d0;
L_48c500:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48c5c4;
    eax = 0x28u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48c537;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b74c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
L_48c537:
    ecx = eax;
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax & 0x180u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x7u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax & 0x78u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x3u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax & 0x4u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x8u, 4, eax);
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax & 0x2u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0xcu, 4, eax);
    eax = lift_load(&env, esi, 0x0u, 4);
    edx = (ebp + 0xffffffe0u);
    eax = eax & 0x1u;
    ebx = edi;
    lift_store(&env, ecx, 0x10u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f1b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, 0x3u);
    ebx = (ecx + 0x14u);
    edx = eax;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = (ebp + 0xffffffe0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    eax = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, ecx, 0x1cu, 4, eax);
    eax = lift_load(&env, esi, 0x8u, 4);
    lift_store(&env, ecx, 0x20u, 4, eax);
    eax = lift_load(&env, esi, 0xcu, 4);
    edx = ecx;
    lift_store(&env, ecx, 0x18u, 4, eax);
    eax = 0x532c04u;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6f70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
L_48c5c4:
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = edi + 1u;
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (fl.cf)
        goto L_48c500;
L_48c5d0:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x532c00u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t v = 0x558c9cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x532c18u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    env.chain = eax;
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
}

uint32_t lifted_f48c610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48C610_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48C610_STACK, 0, entry);
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
    eax = lift_call(&env, 0x47f900u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_48c625;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48c625:
    eax = lift_load(&env, edx, 0x20u, 4);
    eax = eax & 0x180u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x7u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x532bbcu, 4, eax);
    eax = lift_load(&env, edx, 0x20u, 4);
    eax = eax & 0x78u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x3u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x532bc0u, 4, eax);
    eax = lift_load(&env, edx, 0x20u, 4);
    eax = eax & 0x4u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x532bc4u, 4, eax);
    eax = lift_load(&env, edx, 0x20u, 4);
    eax = eax & 0x2u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x532bc8u, 4, eax);
    eax = lift_load(&env, edx, 0x20u, 4);
    {
        uint32_t r = lift_and(32, eax, ecx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x532bccu, 4, eax);
    eax = lift_load(&env, edx, 0x28u, 4);
    lift_store(&env, 0u, 0x532b8cu, 4, eax);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f48c680(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48C680_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48C680_STACK, 0, entry);
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
    ebx = edx;
    {
        uint32_t v = 0x558c9cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = ebx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x558c9cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_48c6b5;
    eax = lift_load(&env, ebx, 0x4u, 4);
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
L_48c6b5:
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

uint32_t lifted_f48c6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48C6C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48C6C0_STACK, 0, entry);
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
    esp = esp - 0x1cu;
    edx = eax;
    eax = (ebp + 0xffffffd0u);
    ecx = 0x4ec1ecu;
    ebx = 0x5177c8u;
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
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    eax = edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = (edx + 0x40u);
    edi = lift_load(&env, edx, 0x44u, 4);
    ebx = (edx + 0x3cu);
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48c7f0;
    eax = 0x532c1cu;
    edx = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x532c20u;
    edx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x510c68u;
    eax = lift_load(&env, 0u, 0x532c20u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_48c7dd;
    ebx = lift_load(&env, 0u, 0x5bb498u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c7cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_48c74a:
    esi = lift_load(&env, 0u, 0x5bb490u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_48c751:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c7cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_48c758:
    ebx = 0xeu;
    edx = (ebp + 0xffffffe4u);
    eax = 0x532c1cu;
    edi = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdb70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x532c1cu;
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = (ebp + 0xffffffe4u);
    ebx = 0xeu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = 0x532c20u;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    edx = (ebp + 0xffffffe8u);
    ecx = 0x3u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdb70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    eax = 0x532c20u;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe8u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    env.chain = eax;
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
L_48c7dd:
    ecx = lift_load(&env, 0u, 0x5bb498u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ca0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    goto L_48c74a;
L_48c7f0:
    eax = 0x532c1cu;
    edx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x532c20u;
    edx = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x510c69u;
    eax = lift_load(&env, 0u, 0x532c1cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_48c827;
    edx = lift_load(&env, 0u, 0x5bb498u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    goto L_48c751;
L_48c827:
    eax = lift_load(&env, 0u, 0x5bb498u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ca0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    goto L_48c758;
}

uint32_t lifted_f48c860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48C860_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48C860_STACK, 0, entry);
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
    esp = esp - 0x95cu;
    edi = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x1bcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48c883;
L_48c879:
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
L_48c883:
    edx = 0x104u;
    eax = (ebp + 0xfffffeb0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dabbeu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48c879;
    ecx = 0xffffffffu;
    ebx = (ebp + 0xfffffeb0u);
    edx = (ebp + 0xfffff898u);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47fc10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0xffffffffu;
    ebx = 0x510c9du;
    edx = (ebp + 0xfffff690u);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47fc10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0xffffffffu;
    ebx = 0x510ca6u;
    edx = (ebp + 0xfffffaa0u);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47fc10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0xffffffffu;
    ebx = 0x510cb3u;
    edx = (ebp + 0xfffffca8u);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47fc10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x38u;
    eax = (ebp + 0xffffffb4u);
    edx = edx ^ edx;
    ecx = 0x38u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    edx = lift_load(&env, edi, 0x1c8u, 4);
    esi = (ebp + 0xffffffbcu);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x20u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffff898u);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = (ebp + 0xfffffca8u);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = (ebp + 0xfffff690u);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = (ebp + 0xfffffaa0u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = (ebp + 0xfffff898u);
    edx = (ebp + 0xffffffb4u);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, edi, 0x1bcu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x10u, 4), eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
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
}

uint32_t lifted_f48c970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48C970_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48C970_STACK, 0, entry);
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
    esp = esp - 0x10u;
    edx = lift_load(&env, eax, 0x1bcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_48c98d;
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
L_48c98d:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x1c8u, 4);
    esi = (ebp + 0xffffffe0u);
    ebx = lift_load(&env, edx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x20u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffffe0u);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x14u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
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
}

uint32_t lifted_object_delegate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_DELEGATE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_DELEGATE_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ebx;
    ebx = lift_load(&env, eax, 0x38u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_48c9be;
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
L_48c9be:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47fa40u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f48c9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48C9D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48C9D0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ebx;
    ebx = lift_load(&env, eax, 0x38u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_48c9de;
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
L_48c9de:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47fa90u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f48ca20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48CA20_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48CA20_STACK, 0, entry);
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
    esp = esp - 0x44u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    ebx = edx;
    eax = (ebp + 0xffffffacu);
    edx = 0x4ec1ecu;
    ecx = 0x5177e4u;
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
    esi = esi ^ esi;
    eax = (ebp + 0xffffffd8u);
    lift_store(&env, ebp, 0xffffffb0u, 4, edx);
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffb8u, 4, esi);
    lift_store(&env, ebp, 0xffffffd0u, 4, esi);
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb8u, 4, edx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_48ca94;
L_48ca70:
    eax = (ebp + 0xffffffd8u);
    edi = edi ^ edi;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, ebp, 0xffffffb8u, 4, edi);
    env.chain = eax;
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
L_48ca94:
    edx = (ebp + 0xffffffc0u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = 0x51698cu;
    esi = (ebp + 0xffffffc0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, eax, 0x2cu, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ecx = 0x10u;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_string(&env, 4, 1, 2, &eax, &ecx, &esi, &edi, &fl);
    if (fl.zf)
        goto L_48cab6;
    {
        uint32_t r = lift_sbb(32, eax, eax, &fl);
        eax = r;
    }
    eax = eax - 0xffffffffu - fl.cf;
L_48cab6:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_48ca70;
    esi = 0x2u;
    edx = 0x510dd7u;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = (ebp + 0xffffffd8u);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffdcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffd0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x510dedu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ebx, 0x0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x40u, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_sub(32, eax, 0x80158100u, &fl);
    }
    if (!fl.zf)
        goto L_48cb25;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd0u, 4), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_48cb25;
    eax = (ebp + 0xffffffdcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffd0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffd4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x510df7u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ebx, 0x0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x40u, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_48cb25;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x510e01u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffd8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
L_48cb25:
    edx = (ebp + 0xffffffd8u);
    eax = (ebp + 0xffffffe0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x2u;
    ecx = 0x1u;
    lift_store(&env, ebp, 0xffffffb8u, 4, edx);
    edx = eax;
    eax = 0x532c24u;
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe0u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb8u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x510e0fu;
    eax = (ebp + 0xffffffd8u);
    lift_store(&env, ebp, 0xffffffb8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffdcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffd0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x510e27u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ebx, 0x0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x40u, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_sub(32, eax, 0x80158100u, &fl);
    }
    if (!fl.zf)
        goto L_48cbf4;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = eax + eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9ff0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = (ebp + 0xffffffdcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffd0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x510e39u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ebx, 0x0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x40u, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_48cbe6;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9ff0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = edi;
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
    esi = eax;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47fc50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x510e4bu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffd8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_48cbe6;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48cbe6:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_48cbf4;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48cbf4:
    edx = (ebp + 0xffffffd8u);
    eax = (ebp + 0xffffffe4u);
    ecx = 0x4u;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffffb8u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe4u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb8u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb8u, 4, ebx);
    goto L_48ca70;
}

uint32_t lifted_f48cc30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48CC30_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48CC30_STACK, 0, entry);
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
    esp = esp - 0x74u;
    edi = eax;
    eax = (ebp + 0xffffff78u);
    edx = 0x4ec1ecu;
    ecx = 0x517808u;
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
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    lift_store(&env, ebp, 0xffffff80u, 4, ecx);
    lift_store(&env, ebp, 0xffffff84u, 4, ebx);
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x1bcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48cc8d;
L_48cc73:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
L_48cc75:
    eax = lift_load(&env, ebp, 0xffffff78u, 4);
    env.chain = eax;
    eax = edx;
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
L_48cc8d:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffff8cu);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffff8cu, 4, ebx);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, edi, 0x1c0u, 4);
    eax = lift_load(&env, edi, 0x1bcu, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x28u, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x80158100u, &fl);
    }
    if (fl.zf)
        goto L_48cd32;
L_48ccb9:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_48cd0b;
    ebx = lift_load(&env, esi, 0x50u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_48ccd1;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x50u, 4, 0x0u);
L_48ccd1:
    eax = eax ^ eax;
    edx = lift_load(&env, esi, 0x58u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_48cd0b;
    ebx = ebx ^ ebx;
L_48ccdf:
    eax = lift_load(&env, esi, 0x54u, 4);
    eax = eax + ebx;
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_48ccfa;
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ecx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, esi, 0x54u, 4);
    lift_store(&env, ebx, eax + 0x0u, 4, 0x0u);
L_48ccfa:
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx + 0x4u;
    ecx = ecx + 1u;
    edx = lift_load(&env, esi, 0x58u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (fl.cf)
        goto L_48ccdf;
L_48cd0b:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_48cd16;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48cd16:
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, edi, 0x14u, 4, 0x0u);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_48cc73;
    edx = 0x1u;
    goto L_48cc75;
L_48cd32:
    eax = lift_load(&env, ebp, 0xffffff8cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9ff0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_48cd4e;
    lift_store(&env, ebp, 0xffffffd8u, 4, 0x80004005u);
    goto L_48ccb9;
L_48cd4e:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffff8cu);
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
    edx = lift_load(&env, edi, 0x1c0u, 4);
    eax = lift_load(&env, edi, 0x1bcu, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x28u, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_48ccb9;
    ecx = 0x80004005u;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebx, 0x4u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48d054;
    edx = 0x510f85u;
    eax = (ebp + 0xffffffa4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, 0xbu);
    edx = eax;
    eax = 0x532c24u;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffa4u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c390u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48d2ea;
    edx = 0x510fafu;
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = (ebp + 0xffffffa8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, 0xdu);
    edx = eax;
    eax = 0x532c24u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffa8u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    eax = edi;
    edx = lift_load(&env, ebx, 0x50u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48ca20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (edi + 0x10u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ebx, 0x54u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, edx, 0x0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ebx, 0x50u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx + 0x8u;
    eax = lift_load(&env, edi, 0x0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x64u, 4), eax, edx, ebx, ecx, 12, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 48u;
    {
        (void)lift_sub(32, eax, 0x15800eu, &fl);
    }
    if (!fl.zf)
        goto L_48d1d8;
L_48ce3b:
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f172cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
L_48ce57:
    {
        uint32_t v = 0x558c9cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = edi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x558c9cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_48d1e5;
L_48ce85:
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48cff9;
    {
        uint32_t v = 0x558c9cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = edi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48cfed;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffacu, 4, edx);
    edx = (ebp + 0xffffffacu);
    eax = lift_load(&env, eax, 0x48u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x14u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_48cfed;
    {
        uint32_t v = 0x80000000u;
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
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, esi, 0x54u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, edi, 0x0u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (esi + 0x8u);
    ecx = ecx ^ ecx;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x18u, 4), eax, edx, ebx, ecx, 12, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 48u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_48d295;
    eax = 0x5bb254u;
    lift_store(&env, edi, 0x30u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48b7e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48d25e;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48d21a;
    ecx = lift_load(&env, 0u, 0x4f7b40u, 4);
    ebx = lift_load(&env, edi, 0x24u, 4);
    edx = ecx;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418150u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48d20c;
    eax = (ebp + 0xffffffb0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0xfu;
    edx = ebx;
    lift_store(&env, ebp, 0xffffff84u, 4, eax);
    eax = (ebp + 0xffffffb4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418170u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x10u;
    eax = (ebp + 0xffffffb8u);
    lift_store(&env, ebp, 0xffffff84u, 4, edx);
    edx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418170u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffb8u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x510fcdu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffb0u);
    ecx = 0x11u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0x10u;
    edx = (ebp + 0xffffffb0u);
    eax = (ebp + 0xffffffbcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, 0x12u);
    edx = eax;
    eax = 0x532c24u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffbcu);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48b970u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48cfd8:
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48cfed;
    edx = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, eax, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffacu, 4, ecx);
L_48cfed:
    {
        uint32_t v = 0x558c9cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_48cff9:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd4u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48d031;
    edx = 0x51104cu;
    eax = (ebp + 0xffffffccu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, 0x1au);
    edx = eax;
    eax = 0x532c24u;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffccu);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
L_48d031:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48d2d4;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f3d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, edx);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    goto L_48ccb9;
L_48d054:
    edx = 0x510eeau;
    eax = (ebp + 0xffffff90u);
    ecx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, eax);
    eax = (ebp + 0xffffff90u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = 0x5bb254u;
    lift_store(&env, ebp, 0xffffff84u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c3b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.zf)
        goto L_48d19b;
    edx = lift_load(&env, edi, 0x1c8u, 4);
    eax = edi;
    lift_store(&env, edi, 0x14u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x44u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.zf)
        goto L_48d15f;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48b7e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.zf)
        goto L_48d123;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.zf)
        goto L_48d0e2;
    edx = edx ^ edx;
    lift_store(&env, edi, 0xb4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
L_48d0d8:
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    goto L_48ccb9;
L_48d0e2:
    edx = 0x510f10u;
    eax = (ebp + 0xffffff94u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, 0x3u);
    edx = eax;
    eax = 0x532c24u;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffff94u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48b970u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    goto L_48d0d8;
L_48d123:
    edx = 0x510f2cu;
    eax = (ebp + 0xffffff98u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, 0x5u);
    edx = eax;
    eax = 0x532c24u;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffff98u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    goto L_48ccb9;
L_48d15f:
    edx = 0x510f4au;
    eax = (ebp + 0xffffff9cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, 0x7u);
    edx = eax;
    eax = 0x532c24u;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffff9cu);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    goto L_48ccb9;
L_48d19b:
    edx = 0x510f68u;
    eax = (ebp + 0xffffffa0u);
    ecx = 0x9u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffa0u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, ebx);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    goto L_48ccb9;
L_48d1d8:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_48ce3b;
    goto L_48cff9;
L_48d1e5:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f172cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax - lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        (void)lift_sub(32, eax, 0x2710u, &fl);
    }
    if (!fl.cf)
        goto L_48ce85;
    {
        uint32_t v = 0x64u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1cfcu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    goto L_48ce57;
L_48d20c:
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    lift_store(&env, edi, 0xb4u, 4, eax);
    goto L_48cfd8;
L_48d21a:
    edx = 0x510ff6u;
    eax = (ebp + 0xffffffc0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, 0x14u);
    edx = eax;
    eax = 0x532c24u;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffc0u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48b970u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    goto L_48cfd8;
L_48d25e:
    edx = 0x511012u;
    eax = (ebp + 0xffffffc4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, 0x16u);
    edx = eax;
    eax = 0x532c24u;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffc4u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    goto L_48cfd8;
L_48d295:
    edx = 0x511030u;
    eax = (ebp + 0xffffffc8u);
    ecx = 0x18u;
    lift_store(&env, edi, 0x30u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffc8u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, ebx);
    goto L_48cfd8;
L_48d2d4:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f0f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, edx);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    goto L_48ccb9;
L_48d2ea:
    edx = 0x511065u;
    eax = (ebp + 0xffffffd0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, 0x1cu);
    edx = eax;
    eax = 0x532c24u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffd0u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    goto L_48ccb9;
}

uint32_t lifted_record_copy(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RECORD_COPY_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RECORD_COPY_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    lift_store(&env, eax, 0x0u, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x1u, 1)) & 0xffu);
    lift_store(&env, eax, 0x1u, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x2u, 1)) & 0xffu);
    lift_store(&env, eax, 0x2u, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x3u, 1)) & 0xffu);
    lift_store(&env, eax, 0x3u, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x8u, 1)) & 0xffu);
    lift_store(&env, eax, 0x8u, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x9u, 1)) & 0xffu);
    lift_store(&env, eax, 0x9u, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0xau, 1)) & 0xffu);
    lift_store(&env, eax, 0xau, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0xbu, 1)) & 0xffu);
    lift_store(&env, eax, 0xbu, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x4u, 1)) & 0xffu);
    lift_store(&env, eax, 0x4u, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x5u, 1)) & 0xffu);
    lift_store(&env, eax, 0x5u, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x6u, 1)) & 0xffu);
    lift_store(&env, eax, 0x6u, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x7u, 1)) & 0xffu);
    lift_store(&env, eax, 0x7u, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0xcu, 1)) & 0xffu);
    lift_store(&env, eax, 0xcu, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0xdu, 1)) & 0xffu);
    lift_store(&env, eax, 0xdu, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0xeu, 1)) & 0xffu);
    lift_store(&env, eax, 0xeu, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0xfu, 1)) & 0xffu);
    lift_store(&env, eax, 0xfu, 1, (ecx & 0xffu));
    ecx = lift_load(&env, edx, 0x10u, 4);
    lift_store(&env, eax, 0x10u, 4, ecx);
    ecx = lift_load(&env, edx, 0x14u, 4);
    lift_store(&env, eax, 0x14u, 4, ecx);
    ecx = lift_load(&env, edx, 0x18u, 4);
    lift_store(&env, eax, 0x18u, 4, ecx);
    ecx = lift_load(&env, edx, 0x1cu, 4);
    lift_store(&env, eax, 0x1cu, 4, ecx);
    ecx = lift_load(&env, edx, 0x20u, 4);
    lift_store(&env, eax, 0x20u, 4, ecx);
    ecx = lift_load(&env, edx, 0x24u, 4);
    lift_store(&env, eax, 0x24u, 4, ecx);
    ecx = lift_load(&env, edx, 0x28u, 4);
    lift_store(&env, eax, 0x28u, 4, ecx);
    ecx = lift_load(&env, edx, 0x2cu, 4);
    lift_store(&env, eax, 0x2cu, 4, ecx);
    edx = lift_load(&env, edx, 0x30u, 4);
    lift_store(&env, eax, 0x30u, 4, edx);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f48d530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48D530_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48D530_STACK, 0, entry);
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
    esp = esp - 0x40u;
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_48d5c2;
    edx = 0x4ec1ecu;
    esi = 0x517a50u;
    edi = 0x3u;
    lift_store(&env, eax, 0x0u, 4, 0x517a94u);
    eax = (eax & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffdcu, 1, ((eax >> 8) & 0xffu));
    eax = (ebp + 0xffffffc4u);
    lift_store(&env, ebp, 0xffffffe8u, 1, (ebx & 0xffu));
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
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, esi);
    eax = ecx;
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d6c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d86d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_48d5ae;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48d5ae:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    env.chain = eax;
    eax = ecx;
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
L_48d5c2:
    ebx = 0x1u;
    edx = 0x517ab0u;
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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

uint32_t lifted_list_empty_48d5f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_LIST_EMPTY_48D5F0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_LIST_EMPTY_48D5F0_STACK, 0, entry);
    eax = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.cf || fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_release_call_48d600(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_RELEASE_CALL_48D600_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_RELEASE_CALL_48D600_STACK, 0,
               entry);
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
    ecx = 0x1u;
    esi = lift_load(&env, eax, 0x8u, 4);
    ebx = edx;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d88a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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

uint32_t lifted_forward_registers_48d620(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_FORWARD_REGISTERS_48D620_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_FORWARD_REGISTERS_48D620_STACK, 0,
               entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d630u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_list_item_48d630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_LIST_ITEM_48D630_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_LIST_ITEM_48D630_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.cf)
        goto L_48d640;
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, eax, (edx * 4u) + 0x0u, 4);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48d640:
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

uint32_t lifted_f48d650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48D650_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48D650_STACK, 0, entry);
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
    esp = esp - 0xcu;
    edi = eax;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    ebx = edx;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (ebx + edx);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    ecx = ebx;
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = ebx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf)
        goto L_48d699;
L_48d67a:
    eax = lift_load(&env, edi, 0x4u, 4);
    eax = lift_load(&env, ecx, eax + 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48d68e;
    esi = lift_load(&env, eax, 0x34u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48d68e:
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    ebx = ebx + 1u;
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.cf)
        goto L_48d67a;
L_48d699:
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8950u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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

uint32_t lifted_forward_call_48d6b0(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_FORWARD_CALL_48D6B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_FORWARD_CALL_48D6B0_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8950u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f48d6c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48D6C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48D6C0_STACK, 0, entry);
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
    esp = esp - 0x4u;
    edi = eax;
    eax = lift_load(&env, eax, 0x8u, 4);
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_48d6fa;
    ecx = ecx ^ ecx;
L_48d6db:
    eax = lift_load(&env, edi, 0x4u, 4);
    eax = lift_load(&env, ecx, eax + 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48d6ef;
    esi = lift_load(&env, eax, 0x34u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48d6ef:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx + 1u;
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.cf)
        goto L_48d6db;
L_48d6fa:
    ebx = 0xffffffffu;
    eax = edi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8770u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
}

uint32_t lifted_f4ac1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4AC1C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4AC1C0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
L_4ac1c3:
    eax = eax + 0x4u;
    edx = edx ^ edx;
    lift_store(&env, eax, 0x5bb710u, 4, edx);
    {
        (void)lift_sub(32, eax, 0x18u, &fl);
    }
    if (!fl.zf)
        goto L_4ac1c3;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ac1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4AC1E0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4AC1E0_STACK, 0, entry);
    lift_store(&env, 0u, (eax * 4u) + 0x5bb714u, 4, 0x1u);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_animation_tick_4ac310(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ANIMATION_TICK_4AC310_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ANIMATION_TICK_4AC310_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4ac370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac390u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4ac32a;
L_4ac326:
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
L_4ac32a:
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac3b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = eax;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac420u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
L_4ac33e:
    if (fl.cf || fl.zf)
        goto L_4ac326;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ac357;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac720u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx - 1u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    goto L_4ac33e;
L_4ac357:
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx - 1u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    goto L_4ac33e;
}

uint32_t lifted_f4ac590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4AC590_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4AC590_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0xc0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4ac5a0;
    ecx = 0x1u;
L_4ac5a0:
    eax = lift_load(&env, eax, 0xbcu, 4);
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    lift_div1(32, ecx, &eax, &edx, &fl);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ac610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4AC610_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4AC610_STACK, 0, entry);
    lift_store(&env, eax, 0xdcu, 4, 0x0u);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_actor_randomize_period(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_RANDOMIZE_PERIOD_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_RANDOMIZE_PERIOD_STACK, 0,
               entry);
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
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0xc8u, 2)) & 0xffffu);
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    ebx = lift_load(&env, ecx, 0xc4u, 4);
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = ecx;
    edx = edx + ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0, esp);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_actor_randomize_d0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_RANDOMIZE_D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_RANDOMIZE_D0_STACK, 0, entry);
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
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0xd8u, 2)) & 0xffffu);
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    ebx = lift_load(&env, ecx, 0xd4u, 4);
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = ecx;
    edx = edx + ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac490u, eax, edx, ebx, ecx, 0, esp);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_actor_get_b4_full(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_GET_B4_FULL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_GET_B4_FULL_STACK, 0, entry);
    eax = lift_load(&env, eax, 0xb4u, 4);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_step_toward(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_STEP_TOWARD_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_STEP_TOWARD_STACK, 1, entry);
    eax = ebx;
    {
        uint32_t r = lift_imul(32, edx, lift_load(&env, esp, 0x4u, 4), &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ac996;
    eax = eax - edx;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ac993;
    eax = ecx;
L_4ac993:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ac996:
    if (fl.sf == fl.of)
        goto L_4ac993;
    eax = eax + edx;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ac993;
    eax = ecx;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_dword_transition(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_DWORD_TRANSITION_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_DWORD_TRANSITION_STACK, 0, entry);
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
    ebx = edx;
    esi = lift_load(&env, ecx, 0x88u, 4);
    {
        uint32_t r = lift_imul(32, ebx, esi, &fl);
        ebx = r;
    }
    eax = lift_load(&env, eax, 0x80u, 4);
    edx = lift_load(&env, ecx, 0x84u, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4accb2;
    eax = eax - ebx;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4acc98;
L_4acc96:
    eax = edx;
L_4acc98:
    edx = lift_load(&env, ecx, 0x84u, 4);
    lift_store(&env, ecx, 0x80u, 4, eax);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
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
L_4accb2:
    if (fl.sf == fl.of)
        goto L_4acc98;
    eax = eax + ebx;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4acc98;
    goto L_4acc96;
}

uint32_t lifted_f4accc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ACCC0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ACCC0_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    edi = 0x1u;
    ebx = ebx ^ ebx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4accf4;
L_4accd3:
    eax = lift_load(&env, ecx, 0x88u, 4);
    edx = lift_load(&env, ecx, 0x80u, 4);
    edx = edx + eax;
    lift_store(&env, ecx, 0x80u, 4, edx);
    {
        (void)lift_sub(32, edx, 0xffu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4acd07;
L_4accef:
    ebx = ebx + 1u;
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.cf)
        goto L_4accd3;
L_4accf4:
    eax = edi;
    lift_store(&env, 0u, 0x5bb5ccu, 4, edi);
    lift_store(&env, 0u, 0x5bb5d0u, 4, ebx);
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
L_4acd07:
    eax = (edx + 0xffffff01u);
    edx = eax;
    edi = 0xffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_store(&env, ecx, 0x80u, 4, eax);
    lift_idiv1(32, edi, &eax, &edx, &fl);
    edi = edi ^ edi;
    lift_store(&env, ecx, 0x80u, 4, edx);
    goto L_4accef;
}

uint32_t lifted_f4acd30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ACD30_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ACD30_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    edi = 0x1u;
    ebx = ebx ^ ebx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4acd60;
L_4acd43:
    eax = lift_load(&env, ecx, 0x88u, 4);
    edx = lift_load(&env, ecx, 0x80u, 4);
    edx = edx - eax;
    lift_store(&env, ecx, 0x80u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4acd73;
L_4acd5b:
    ebx = ebx + 1u;
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.cf)
        goto L_4acd43;
L_4acd60:
    eax = edi;
    lift_store(&env, 0u, 0x5bb5d4u, 4, edi);
    lift_store(&env, 0u, 0x5bb5d8u, 4, ebx);
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
L_4acd73:
    eax = (edx + 0xffu);
    edx = eax;
    edi = 0xffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_store(&env, ecx, 0x80u, 4, eax);
    lift_idiv1(32, edi, &eax, &edx, &fl);
    edi = edi ^ edi;
    lift_store(&env, ecx, 0x80u, 4, edx);
    goto L_4acd5b;
}

uint32_t lifted_actor_turn_toward(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_TURN_TOWARD_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_TURN_TOWARD_STACK, 0, entry);
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
    ecx = eax;
    esi = lift_load(&env, eax, 0x22u, 4);
    ebx = lift_load(&env, eax, 0x24u, 4);
    eax = lift_load(&env, eax, 0x26u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        esi = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    lift_store(&env, 0u, 0x5bb5e4u, 4, eax);
    {
        (void)lift_sub(32, esi, ebx, &fl);
    }
    if (fl.zf)
        goto L_4acea4;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4acea4;
    if (fl.zf || fl.sf != fl.of)
        goto L_4acee7;
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ace79;
    ebx = ebx + 0x168u;
L_4ace79:
    edx = ebx;
    edi = lift_load(&env, 0u, 0x5bb5e4u, 4);
    edx = edx - esi;
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4acec6;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb5e4u, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, ecx, 0x24u, 2)) & 0xffffu);
    edi = edi + eax;
    lift_store(&env, ecx, 0x24u, 2, (edi & 0xffffu));
    eax = lift_load(&env, ecx, 0x22u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0x168u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4aced0;
L_4acea4:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x24u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, ecx, 0x26u, 2), &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb5dcu, 4, esi);
    lift_store(&env, 0u, 0x5bb5e0u, 4, ebx);
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
L_4acec6:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x26u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x24u, 2, (eax & 0xffffu));
    goto L_4acea4;
L_4aced0:
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((edi & 0xffffu)) & 0xffffu);
    edi = 0x168u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    lift_store(&env, ecx, 0x24u, 2, (edx & 0xffffu));
    goto L_4acea4;
L_4acee7:
    ebp = eax;
    ebp = 0u - ebp;
    lift_store(&env, 0u, 0x5bb5e4u, 4, ebp);
    {
        (void)lift_sub(32, esi, ebx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4acefb;
    esi = esi + 0x168u;
L_4acefb:
    edx = esi;
    eax = lift_load(&env, 0u, 0x5bb5e4u, 4);
    edx = edx - ebx;
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4acec6;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb5e4u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x24u, 2)) & 0xffffu);
    edx = edx - eax;
    lift_store(&env, ecx, 0x24u, 2, (edx & 0xffffu));
    eax = lift_load(&env, ecx, 0x22u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4acea4;
    eax = edx;
    eax = eax + 0x168u;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    edi = 0x168u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    lift_store(&env, ecx, 0x24u, 2, (edx & 0xffffu));
    goto L_4acea4;
}

uint32_t lifted_actor_spin(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_SPIN_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_SPIN_STACK, 0, entry);
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
    ebx = lift_load(&env, 0u, 0x5bb600u, 4);
    ecx = eax;
    edi = edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x38u, 2)) & 0xffffu);
    esi = 0x1u;
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4ad161;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ad161;
    ebx = ebx ^ ebx;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ad161;
L_4ad136:
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x38u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x34u, 2)) & 0xffffu);
    eax = eax + edx;
    lift_store(&env, ecx, 0x34u, 2, (eax & 0xffffu));
    edx = lift_load(&env, ecx, 0x32u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, edx, 0x168u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ad174;
L_4ad152:
    edx = lift_load(&env, ecx, 0x32u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ad18d;
L_4ad15c:
    ebx = ebx + 1u;
    {
        (void)lift_sub(32, ebx, edi, &fl);
    }
    if (fl.cf)
        goto L_4ad136;
L_4ad161:
    eax = esi;
    lift_store(&env, 0u, 0x5bb5fcu, 4, esi);
    lift_store(&env, 0u, 0x5bb600u, 4, ebx);
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
L_4ad174:
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    esi = 0x168u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, esi, &eax, &edx, &fl);
    esi = esi ^ esi;
    lift_store(&env, ecx, 0x34u, 2, (edx & 0xffffu));
    goto L_4ad152;
L_4ad18d:
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x34u, 2)) & 0xffffu);
    edx = edx + 0x168u;
    edx = edx & 0xffffu;
    esi = 0x168u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, esi, &eax, &edx, &fl);
    esi = esi ^ esi;
    lift_store(&env, ecx, 0x34u, 2, (edx & 0xffffu));
    goto L_4ad15c;
}

uint32_t lifted_actor_polar_offset_second(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_POLAR_OFFSET_SECOND_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_POLAR_OFFSET_SECOND_STACK, 1,
               entry);
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
    esi = eax;
    eax = lift_load(&env, eax, 0x32u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_load(&env, 0u, (eax * 4u) + 0x59939cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4849e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = lift_load(&env, esi, 0x32u, 4);
    edx = ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_load(&env, 0u, (eax * 4u) + 0x598dfcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4849e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0x8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, edx, 0x0u, 4, eax);
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

uint32_t lifted_actor_orbit_point(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_ORBIT_POINT_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_ORBIT_POINT_STACK, 0, entry);
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
    esp = esp - 0x4u;
    esi = eax;
    edi = edx;
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    edx = lift_load(&env, eax, 0x28u, 4);
    {
        uint32_t v = 0x5bb608u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = 0x5bb604u;
    ebx = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad1c0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb604u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x2cu, 2)) & 0xffffu);
    edx = edx + ebx;
    lift_store(&env, edi, 0x0u, 2, (edx & 0xffffu));
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb608u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x2eu, 2)) & 0xffffu);
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t r = lift_sub(32, edx, ecx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x0u, 2, (edx & 0xffffu));
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

uint32_t lifted_f4ad2c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4AD2C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4AD2C0_STACK, 0, entry);
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
    esp = esp - 0x4u;
    esi = eax;
    edi = edx;
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    edx = lift_load(&env, eax, 0x28u, 4);
    {
        uint32_t v = 0x5bb610u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = 0x5bb60cu;
    ebx = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad1c0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb60cu, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x2cu, 2)) & 0xffffu);
    edx = edx + ebx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb610u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb614u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x2eu, 2)) & 0xffffu);
    edx = edx - ecx;
    {
        uint32_t v = 0x5bb610u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5bb616u, 2, (edx & 0xffffu));
    edx = lift_load(&env, esi, 0x38u, 4);
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = 0x5bb60cu;
    ebx = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad210u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb614u, 2)) & 0xffffu);
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb60cu, 2)) & 0xffffu);
    edx = edx + esi;
    lift_store(&env, edi, 0x0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb616u, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb610u, 2)) & 0xffffu);
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t r = lift_sub(32, edx, edi, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x0u, 2, (edx & 0xffffu));
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

uint32_t lifted_actor_chain_orbit_point(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_CHAIN_ORBIT_POINT_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_CHAIN_ORBIT_POINT_STACK, 0,
               entry);
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
    esp = esp - 0x4u;
    esi = eax;
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    edi = ebx;
    {
        uint32_t v = 0x5bb630u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x5bb62cu;
    ebx = lift_load(&env, eax, 0x28u, 4);
    edx = lift_load(&env, eax, 0x38u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad1c0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x5bb630u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb62cu, 2)) & 0xffffu);
    ecx = 0x5bb62cu;
    lift_store(&env, 0u, 0x5bb634u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb630u, 2)) & 0xffffu);
    edx = lift_load(&env, 0u, 0x5bb632u, 4);
    lift_store(&env, 0u, 0x5bb636u, 2, (eax & 0xffffu));
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ebx = lift_load(&env, 0u, 0x5bb634u, 4);
    eax = esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad210u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x5bb630u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb62cu, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb630u, 2)) & 0xffffu);
    ecx = 0x5bb62cu;
    eax = eax - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x2cu, 2)) & 0xffffu);
    ebx = lift_load(&env, 0u, 0x5bb632u, 4);
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    edx = lift_load(&env, 0u, 0x5bb634u, 4);
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad210u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb630u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb62cu, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x2eu, 2)) & 0xffffu);
    eax = eax + ebx;
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, edi, 0x0u, 2, (eax & 0xffffu));
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

uint32_t lifted_actor_set_words_2a_full(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_SET_WORDS_2A_FULL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_SET_WORDS_2A_FULL_STACK, 0,
               entry);
    lift_store(&env, eax, 0x2au, 2, (edx & 0xffffu));
    lift_store(&env, eax, 0x2cu, 2, (ebx & 0xffffu));
    lift_store(&env, eax, 0x2eu, 2, (ecx & 0xffffu));
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_byte_transition_4ad580(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_BYTE_TRANSITION_4AD580_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_BYTE_TRANSITION_4AD580_STACK, 0,
               entry);
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
    esi = edx;
    edi = lift_load(&env, eax, 0x4eu, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_imul(32, esi, edi, &fl);
        esi = r;
    }
    ebx = ebx ^ ebx;
    ecx = ecx ^ ecx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x4eu, 1)) & 0xffu);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0x4fu, 1)) & 0xffu);
    edx = ebx;
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ad5b9;
    edx = edx - esi;
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ad5a7;
    edx = ecx;
L_4ad5a7:
    lift_store(&env, eax, 0x4eu, 1, (edx & 0xffu));
    {
        (void)lift_sub(8, (edx & 0xffu), lift_load(&env, eax, 0x4fu, 1), &fl);
    }
    edx = (edx & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
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
L_4ad5b9:
    if (fl.sf == fl.of)
        goto L_4ad5a7;
    edx = (ebx + esi);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ad5a7;
    edx = ecx;
    lift_store(&env, eax, 0x4eu, 1, (edx & 0xffu));
    {
        (void)lift_sub(8, (edx & 0xffu), lift_load(&env, eax, 0x4fu, 1), &fl);
    }
    edx = (edx & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
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

uint32_t lifted_word_transition_4ad5e0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_WORD_TRANSITION_4AD5E0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_WORD_TRANSITION_4AD5E0_STACK, 0,
               entry);
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
    ecx = eax;
    esi = edx;
    edi = lift_load(&env, eax, 0x30u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_imul(32, esi, edi, &fl);
        esi = r;
    }
    ebx = lift_load(&env, eax, 0x28u, 4);
    edx = lift_load(&env, eax, 0x2eu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = ebx;
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ad623;
    eax = eax - esi;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ad60b;
L_4ad609:
    eax = edx;
L_4ad60b:
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x30u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x2au, 2, (eax & 0xffffu));
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ad623:
    if (fl.sf == fl.of)
        goto L_4ad60b;
    eax = (ebx + esi);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ad60b;
    goto L_4ad609;
}

uint32_t lifted_word_transition_4ad630(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_WORD_TRANSITION_4AD630_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_WORD_TRANSITION_4AD630_STACK, 0,
               entry);
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
    ecx = eax;
    esi = edx;
    edi = lift_load(&env, eax, 0x40u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_imul(32, esi, edi, &fl);
        esi = r;
    }
    ebx = lift_load(&env, eax, 0x38u, 4);
    edx = lift_load(&env, eax, 0x3eu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = ebx;
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ad673;
    eax = eax - esi;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ad65b;
L_4ad659:
    eax = edx;
L_4ad65b:
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x40u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x3au, 2, (eax & 0xffffu));
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ad673:
    if (fl.sf == fl.of)
        goto L_4ad65b;
    eax = (ebx + esi);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ad65b;
    goto L_4ad659;
}

uint32_t lifted_object_step_dword(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_STEP_DWORD_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_STEP_DWORD_STACK, 0, entry);
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
    ebx = edx;
    esi = lift_load(&env, ecx, 0x6cu, 4);
    {
        uint32_t r = lift_imul(32, ebx, esi, &fl);
        ebx = r;
    }
    eax = lift_load(&env, eax, 0x64u, 4);
    edx = lift_load(&env, ecx, 0x68u, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ad783;
    eax = eax - ebx;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ad76f;
L_4ad76d:
    eax = edx;
L_4ad76f:
    edx = lift_load(&env, ecx, 0x68u, 4);
    lift_store(&env, ecx, 0x64u, 4, eax);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
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
L_4ad783:
    if (fl.sf == fl.of)
        goto L_4ad76f;
    eax = eax + ebx;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ad76f;
    goto L_4ad76d;
}

uint32_t lifted_actor_dword_transition_4ad790(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_DWORD_TRANSITION_4AD790_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_DWORD_TRANSITION_4AD790_STACK, 0,
               entry);
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
    ebx = edx;
    esi = lift_load(&env, ecx, 0x78u, 4);
    {
        uint32_t r = lift_imul(32, ebx, esi, &fl);
        ebx = r;
    }
    eax = lift_load(&env, eax, 0x70u, 4);
    edx = lift_load(&env, ecx, 0x74u, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ad7c3;
    eax = eax - ebx;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ad7af;
L_4ad7ad:
    eax = edx;
L_4ad7af:
    edx = lift_load(&env, ecx, 0x74u, 4);
    lift_store(&env, ecx, 0x70u, 4, eax);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
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
L_4ad7c3:
    if (fl.sf == fl.of)
        goto L_4ad7af;
    eax = eax + ebx;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ad7af;
    goto L_4ad7ad;
}

uint32_t lifted_f4adfa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ADFA0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ADFA0_STACK, 0, entry);
    lift_store(&env, eax, 0x134u, 4, edx);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b0b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B0B70_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B0B70_STACK, 0, entry);
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
    esp = esp - 0x38u;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb700u, 2)) & 0xffffu);
    esi = lift_load(&env, 0u, 0x5bb764u, 4);
    edi = lift_load(&env, 0u, 0x5bb7d4u, 4);
    ebp = lift_load(&env, 0u, 0x5bb7d8u, 4);
    lift_store(&env, esp, 0x4u, 4, eax);
    lift_store(&env, esp, 0x2cu, 2, (edx & 0xffffu));
    lift_store(&env, esp, 0x30u, 2, (ebx & 0xffffu));
    eax = lift_load(&env, eax, 0xb4u, 4);
    lift_store(&env, 0u, 0x5bb734u, 4, eax);
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a4u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb740u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x16u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a6u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb742u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x8eu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bbffeu, 1, (eax & 0xffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x1eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7aeu, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    edx = lift_load(&env, 0u, 0x5bb734u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x44u, 1)) & 0xffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb738u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4b0ef2;
    eax = edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0xcu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x10u, 2)) & 0xffffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x27u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb7b2u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bb731u, 1, (eax & 0xffu));
L_4b0c3b:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bb738u, 1), 0x10u, &fl);
    }
    if (!fl.zf)
        goto L_4b0fc5;
    edx = lift_load(&env, 0u, 0x5bb734u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4b0f07;
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xf4u, 2)) & 0xffffu);
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5bb7b4u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, 0u, 0x5bb6e6u, 2, (edx & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xf8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e4u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bb7b6u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb6e0u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbfffu, 1, ((edx >> 8) & 0xffu));
    lift_store(&env, 0u, 0x5bb6e2u, 2, (eax & 0xffffu));
L_4b0ca8:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b0u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    edx = edx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (edx & 0xffffu));
    ebx = ebx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6ecu, 2, (edx & 0xffffu));
    ebx = ebx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6eeu, 2, (ebx & 0xffffu));
    edx = edx + eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (edx & 0xffffu));
    ebx = ebx + eax;
    eax = edx;
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) + lift_load(&env, 0u, 0x5bb6e0u, 2)) & 0xffffu);
    eax = eax - 1u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb748u, 2, (eax & 0xffffu));
    eax = ebx;
    eax = eax + edx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb74au, 2, (eax & 0xffffu));
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bbffeu, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b0e07;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    eax = eax - 1u;
    lift_store(&env, esp, 0x24u, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    eax = eax - 1u;
    lift_store(&env, esp, 0x1cu, 4, eax);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, 0u, 0x5bbffeu, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b0f58;
    eax = eax ^ eax;
L_4b0d49:
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x1cu, 4);
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5bbff8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x24u, 4);
    lift_store(&env, 0u, 0x5bbffau, 2, (edx & 0xffffu));
L_4b0d66:
    lift_store(&env, 0u, 0x5bbffcu, 2, (eax & 0xffffu));
L_4b0d6c:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff8u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0faf;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b0faf;
    {
        (void)lift_sub(16, (ebx & 0xffffu), lift_load(&env, 0u, 0x5bbffcu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0faf;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffau, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b0faf;
    {
        (void)lift_sub(16, (ebx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b0dbc;
    ebx = edx;
L_4b0dbc:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff6u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b0dd5;
    lift_store(&env, 0u, 0x5bb7a0u, 2, (edx & 0xffffu));
L_4b0dd5:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffcu, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b0dee;
    lift_store(&env, 0u, 0x5bb74au, 2, (edx & 0xffffu));
L_4b0dee:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff8u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b0e07;
    lift_store(&env, 0u, 0x5bb748u, 2, (edx & 0xffffu));
L_4b0e07:
    eax = lift_load(&env, esp, 0x2cu, 4);
    lift_store(&env, 0u, 0x5bb6e8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x30u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6eau, 2, (eax & 0xffffu));
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, esp, 0x2cu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0fba;
    {
        (void)lift_sub(16, (ebx & 0xffffu), lift_load(&env, esp, 0x30u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0fba;
    eax = lift_load(&env, esp, 0x2cu, 4);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb748u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0fba;
    eax = lift_load(&env, esp, 0x30u, 4);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb74au, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0fba;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bbfffu, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b14a8;
    edx = lift_load(&env, esp, 0x2eu, 4);
    eax = lift_load(&env, 0u, 0x5bb6ecu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx - eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = lift_load(&env, 0u, 0x5bb734u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = edx + eax;
    eax = lift_load(&env, esp, 0x2au, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb6eau, 4);
    esi = lift_load(&env, esp, 0x8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    esi = esi - eax;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    esi = esi + edx;
    eax = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0x8u, 1)) & 0xffu);
L_4b0eba:
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4b14a8;
L_4b0ec2:
    lift_store(&env, esp, 0x34u, 1, (eax & 0xffu));
L_4b0ec6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0x34u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bb7d8u, 4, ebp);
    lift_store(&env, 0u, 0x5bb7d4u, 4, edi);
    lift_store(&env, 0u, 0x5bb764u, 4, esi);
    lift_store(&env, 0u, 0x5bb700u, 2, (ecx & 0xffffu));
    {
        uint32_t r = lift_add(32, esp, 0x38u, &fl);
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
L_4b0ef2:
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5bb7b2u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bb7b0u, 2, (edx & 0xffffu));
    goto L_4b0c3b;
L_4b0f07:
    eax = edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0x4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b4u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b6u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x1cu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x20u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e2u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x14u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e4u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x18u, 2)) & 0xffffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x25u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb6e6u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bbfffu, 1, (eax & 0xffu));
    goto L_4b0ca8;
L_4b0f58:
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4b0f63;
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    goto L_4b0d49;
L_4b0f63:
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4b0d6c;
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xa8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaau, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xacu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbffau, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaeu, 2)) & 0xffffu);
    goto L_4b0d66;
L_4b0faf:
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, esp, 0x34u, 1, ((edx >> 8) & 0xffu));
    goto L_4b0ec6;
L_4b0fba:
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    lift_store(&env, esp, 0x34u, 1, (edx & 0xffu));
    goto L_4b0ec6;
L_4b0fc5:
    eax = lift_load(&env, 0u, 0x5bb734u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4b0fba;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b4u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b6u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x1cu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x20u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e2u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x14u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e4u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x18u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e6u, 2, (edx & 0xffffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x25u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bbfffu, 1, (edx & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x27u, 1)) & 0xffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb731u, 1, (eax & 0xffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    eax = eax - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e4u, 2)) & 0xffffu);
    edx = edx + eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    ebx = ebx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e6u, 2)) & 0xffffu);
    ebx = ebx - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e0u, 2)) & 0xffffu);
    ebx = ebx + eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    eax = eax + edx;
    eax = eax - 1u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb748u, 2, (eax & 0xffffu));
    eax = ebx;
    eax = eax + edx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb74au, 2, (eax & 0xffffu));
    eax = eax ^ eax;
    edx = edx ^ edx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb738u, 1)) & 0xffu);
    lift_store(&env, esp, 0x18u, 4, eax);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb6f8u, 2, (eax & 0xffffu));
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, esp, 0xcu, 4, edx);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    edx = lift_load(&env, esp, 0x8u, 4);
    eax = eax & 0xffffu;
    eax = eax + edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x5c1b00u, 1)) & 0xffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f8u, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx + eax;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb6f8u, 2, (edx & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    edx = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb6fau, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    edx = lift_load(&env, esp, 0x8u, 4);
    eax = eax & 0xffffu;
    eax = eax + edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x5c1b00u, 1)) & 0xffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6fau, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx + eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6fau, 2, (edx & 0xffffu));
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b13fa;
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b13fa;
    eax = lift_load(&env, 0u, 0x5bb7a2u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x10u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb79eu, 4);
    edx = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx - eax;
    eax = edx;
    edx = lift_load(&env, 0u, 0x5bb6f6u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0xcu, 4, edx);
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x18u, 4), &eax, &edx, &fl);
    edx = lift_load(&env, esp, 0x10u, 4);
    edx = edx - eax;
    eax = lift_load(&env, 0u, 0x5bb7a4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x8u, 4, eax);
    lift_store(&env, 0u, 0x5bb6f0u, 2, (edx & 0xffffu));
    edx = lift_load(&env, esp, 0x8u, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    edx = edx - eax;
    eax = edx;
    edx = lift_load(&env, 0u, 0x5bb7acu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x10u, 4, edx);
    eax = eax - edx;
    edx = lift_load(&env, 0u, 0x5bb6f8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x14u, 4, edx);
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x0u, 4), &eax, &edx, &fl);
    edx = lift_load(&env, esp, 0x8u, 4);
    edx = edx - eax;
    eax = edx;
    eax = eax - lift_load(&env, esp, 0x10u, 4);
    edx = lift_load(&env, 0u, 0x5bb6deu, 4);
    lift_store(&env, 0u, 0x5bb6f2u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0xcu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x18u, 4), &eax, &edx, &fl);
    edx = lift_load(&env, 0u, 0x5bb6e0u, 4);
    lift_store(&env, 0u, 0x5bb6fcu, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x0u, 4), &eax, &edx, &fl);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6fcu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6feu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f0u, 2)) & 0xffffu);
    eax = eax + edx;
    eax = eax - 1u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6feu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6f4u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f2u, 2)) & 0xffffu);
    eax = eax + edx;
    eax = eax - 1u;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bbffeu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb6f6u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b1333;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    eax = eax - 1u;
    lift_store(&env, esp, 0x20u, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    eax = eax - 1u;
    lift_store(&env, esp, 0x28u, 4, eax);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1405;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x28u, 4);
    edx = edx ^ edx;
L_4b1272:
    lift_store(&env, 0u, 0x5bbff8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x20u, 4);
    lift_store(&env, 0u, 0x5bbffau, 2, (edx & 0xffffu));
L_4b1283:
    lift_store(&env, 0u, 0x5bbffcu, 2, (eax & 0xffffu));
L_4b1289:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff8u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b1468;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f4u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1468;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f2u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffcu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b1468;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f6u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffau, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1468;
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, 0u, 0x5bb6f2u, 2), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b12e8;
    lift_store(&env, 0u, 0x5bb6f2u, 2, (edx & 0xffffu));
L_4b12e8:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f0u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff6u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b1301;
    lift_store(&env, 0u, 0x5bb6f0u, 2, (edx & 0xffffu));
L_4b1301:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f6u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffcu, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b131a;
    lift_store(&env, 0u, 0x5bb6f6u, 2, (edx & 0xffffu));
L_4b131a:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f4u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff8u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b1333;
    lift_store(&env, 0u, 0x5bb6f4u, 2, (edx & 0xffffu));
L_4b1333:
    eax = lift_load(&env, esp, 0x2cu, 4);
    lift_store(&env, 0u, 0x5bb6e8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x30u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6eau, 2, (eax & 0xffffu));
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, esp, 0x2cu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0faf;
    eax = lift_load(&env, esp, 0x30u, 4);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb6f2u, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b0faf;
    eax = lift_load(&env, esp, 0x2cu, 4);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb6f4u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0faf;
    eax = lift_load(&env, esp, 0x30u, 4);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb6f6u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0faf;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bbfffu, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b14a8;
    edi = lift_load(&env, 0u, 0x5bb738u, 1);
    esi = lift_load(&env, 0u, 0x5bb734u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        edi = r;
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f2u, 2)) & 0xffffu);
    edi = edi + 0x5c1c00u;
    esi = lift_load(&env, esi, 0x0u, 4);
    ebp = edi;
    {
        uint32_t r = lift_sub(16, (eax & 0xffffu), (ecx & 0xffffu), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    ecx = eax;
    if (!fl.zf)
        goto L_4b146f;
L_4b13c5:
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e8u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(16, (ecx & 0xffffu), lift_load(&env, 0u, 0x5bb6f0u, 2), &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4b13f0;
L_4b13d5:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    ebp = ebp + 1u;
    {
        uint32_t r = lift_add(32, esi, edx, &fl);
        esi = r;
    }
    {
        uint32_t a = (ecx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4b13d5;
L_4b13f0:
    eax = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        eax = r;
    }
    goto L_4b0eba;
L_4b13fa:
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, esp, 0x34u, 1, ((eax >> 8) & 0xffu));
    goto L_4b0ec6;
L_4b1405:
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4b141c;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x28u, 4);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    goto L_4b1272;
L_4b141c:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4b1289;
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xa8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaau, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xacu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbffau, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaeu, 2)) & 0xffffu);
    goto L_4b1283;
L_4b1468:
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    goto L_4b0ec2;
L_4b146f:
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb702u, 2, (eax & 0xffffu));
L_4b1477:
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb702u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edi, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, 0u, 0x5bb702u, 2, (eax & 0xffffu));
    {
        uint32_t a = (ecx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4b1477;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    esi = esi + eax;
    goto L_4b13c5;
L_4b14a8:
    lift_store(&env, esp, 0x34u, 1, 0x1u);
    goto L_4b0ec6;
}

uint32_t lifted_object_release_slots_full(const VertrixCalls *calls,
                                          const VertrixFactoryServices *services,
                                          const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_RELEASE_SLOTS_FULL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_RELEASE_SLOTS_FULL_STACK, 0,
               entry);
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
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b22f6;
    esi = ((edx * 4u));
    ecx = eax;
    esi = esi + eax;
L_4b22d2:
    edx = lift_load(&env, ecx, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4b22ef;
    eax = edx;
    if (fl.zf)
        goto L_4b22e9;
    ebx = lift_load(&env, edx, 0x158u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b22e9:
    lift_store(&env, ecx, 0x0u, 4, 0x0u);
L_4b22ef:
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.cf)
        goto L_4b22d2;
L_4b22f6:
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

uint32_t lifted_f4b2300(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B2300_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B2300_STACK, 0, entry);
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
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b2326;
    ecx = ((edx * 4u));
    ecx = ecx + eax;
L_4b2311:
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4b231f;
    {
        (void)lift_sub(32, ebx, lift_load(&env, edx, 0x154u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4b232e;
L_4b231f:
    eax = eax + 0x4u;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.cf)
        goto L_4b2311;
L_4b2326:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4b232e:
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
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b2340(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B2340_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B2340_STACK, 0, entry);
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
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b235e;
    esi = ((edx * 4u));
    ecx = eax;
    esi = esi + eax;
L_4b2351:
    edx = lift_load(&env, ecx, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4b2361;
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.cf)
        goto L_4b2351;
L_4b235e:
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
L_4b2361:
    eax = edx;
    edx = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.cf)
        goto L_4b2351;
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

uint32_t lifted_f4b2a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B2A00_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B2A00_STACK, 0, entry);
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
    esp = esp - 0x6cu;
    esi = eax;
    lift_store(&env, ebp, 0xffffffa0u, 4, edx);
    edx = edx ^ edx;
    edi = (eax + 0x15cu);
    lift_store(&env, ebp, 0xffffff9cu, 4, edx);
    edi = lift_load(&env, edi, 0x0u, 4);
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffacu, 4, edi);
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
    eax = (ecx + 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, esi, 0x304u, 4);
    edi = eax;
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b2aef;
    {
        (void)lift_sub(32, ecx, lift_load(&env, esi, 0x2fcu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4b2aef;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x161u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe0u, 1, (eax & 0xffu));
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffecu, 1, ((eax >> 8) & 0xffu));
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b2aef;
L_4b2a69:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    eax = eax + eax;
    ebx = ebx ^ ebx;
    ecx = (esi + eax);
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x162u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    edx = edx + eax;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    lift_store(&env, edi, eax + 0x0u, 1, 0x0u);
    eax = (ebp + 0xffffffc8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffb0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff88u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff84u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x44u, 1)) & 0xffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    eax = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    eax = lift_load(&env, ebp, 0xffffff84u, 4);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b2c74;
L_4b2ad9:
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu) << 8);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) + 1u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    lift_store(&env, ebp, 0xffffffecu, 1, ((edx >> 8) & 0xffu));
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.cf)
        goto L_4b2a69;
L_4b2aef:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x300u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b2c7b;
    ebx = ebx ^ ebx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x161u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffd4u, 2, (ebx & 0xffffu));
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe4u, 1, (eax & 0xffu));
    lift_store(&env, ebp, 0xffffffe8u, 1, ((ebx >> 8) & 0xffu));
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b2ba0;
L_4b2b18:
    ecx = ecx ^ ecx;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    edx = edx ^ edx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, (ecx * 2u) + 0x162u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, esi, (ecx * 2u) + 0x22au, 2)) & 0xffffu);
    edx = edx + eax;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, (ecx * 2u) + 0x22au, 2)) & 0xffffu);
    lift_store(&env, edi, eax + 0x0u, 1, 0x0u);
    eax = (ebp + 0xffffffb4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffc0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff94u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff8cu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x44u, 1)) & 0xffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    eax = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + 1u;
    ecx = ecx + eax;
    lift_store(&env, ebp, 0xffffffd4u, 2, (ecx & 0xffffu));
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu) << 8);
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + 1u) & 0xffu) << 8);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe8u, 1, ((ecx >> 8) & 0xffu));
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.cf)
        goto L_4b2b18;
L_4b2ba0:
    edx = lift_load(&env, esi, 0xf6u, 4);
    eax = lift_load(&env, ebp, 0xffffffd2u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx - eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x2f6u, 2)) & 0xffffu);
    edx = edx - eax;
    eax = edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x2f8u, 2)) & 0xffffu);
    eax = eax - edx;
    edx = eax;
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
    edx = eax;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b2c7b;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x16u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) + lift_load(&env, esi, 0x2f6u, 2)) & 0xffffu);
L_4b2be8:
    eax = eax + edx;
    lift_store(&env, ebp, 0xffffffccu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xeu, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, esi, 0x2f2u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    eax = eax + ecx;
    lift_store(&env, ebp, 0xffffffd8u, 1, (edx & 0xffu));
    lift_store(&env, ebp, 0xffffffbcu, 2, (eax & 0xffffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x161u, 1)) & 0xffu);
    edx = lift_load(&env, esi, 0x2fcu, 4);
    lift_store(&env, ebp, 0xffffffdcu, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b2c55;
    {
        (void)lift_sub(32, edx, lift_load(&env, esi, 0x304u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4b2c8b;
    ebx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = lift_load(&env, esi, 0xf2u, 4);
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x2f2u, 2)) & 0xffffu);
    eax = eax - ebx;
    eax = eax - edx;
    edx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x2f4u, 2)) & 0xffffu);
    edx = edx - eax;
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b2c55;
    lift_store(&env, ebp, 0xffffffbcu, 2, lift_load(&env, ebp, 0xffffffbcu, 2) + (eax & 0xffffu));
L_4b2c55:
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
L_4b2c58:
    lift_store(&env, ebp, 0xffffffd0u, 2, (eax & 0xffffu));
L_4b2c5c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), lift_load(&env, ebp, 0xffffffdcu, 1), &fl);
    }
    if (fl.cf)
        goto L_4b2ca4;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
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
L_4b2c74:
    eax = edx;
    goto L_4b2ad9;
L_4b2c7b:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x16u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x2f6u, 2)) & 0xffffu);
    goto L_4b2be8;
L_4b2c8b:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xeu, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0xf4u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, esi, 0x2f4u, 2)) & 0xffffu);
    eax = eax + edx;
    eax = eax - ebx;
    eax = eax - 1u;
    goto L_4b2c58;
L_4b2ca4:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    eax = eax + eax;
    ebx = ebx ^ ebx;
    ecx = (esi + eax);
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x162u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    edx = edx + eax;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    lift_store(&env, edi, eax + 0x0u, 1, 0x0u);
    eax = (ebp + 0xffffffb8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffc4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff98u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff90u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x44u, 1)) & 0xffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffcau, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    ecx = eax;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffbau, 4);
    ebx = lift_load(&env, ebp, 0xffffffceu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
    eax = lift_load(&env, esi, 0x15du, 4);
    edx = lift_load(&env, ebp, 0xffffffa8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    ecx = lift_load(&env, esi, 0x304u, 4);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b2d62;
    {
        (void)lift_sub(32, ecx, lift_load(&env, esi, 0x2fcu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4b2d62;
    ecx = lift_load(&env, ebp, 0xffffffa4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    edx = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x440a20u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_4b2d48:
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    eax = eax + 1u;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) + 1u) & 0xffu);
    edx = edx + eax;
    lift_store(&env, ebp, 0xffffffd8u, 1, (ebx & 0xffu));
    lift_store(&env, ebp, 0xffffffccu, 2, (edx & 0xffffu));
    goto L_4b2c5c;
L_4b2d62:
    eax = lift_load(&env, ebp, 0xffffffcau, 4);
    ecx = lift_load(&env, ebp, 0xffffffceu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, ebp, 0xffffffbau, 4);
    edx = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x440ca0u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    goto L_4b2d48;
}

uint32_t lifted_f4b2d90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B2D90_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B2D90_STACK, 0, entry);
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
    esp = esp - 0x60u;
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    edi = lift_load(&env, eax, 0x15cu, 4);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffacu, 4, edi);
    lift_store(&env, ebp, 0xffffffb0u, 4, edx);
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
    edx = 0x1u;
    eax = (ecx + 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    ecx = lift_load(&env, eax, 0x304u, 4);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b2e84;
    {
        (void)lift_sub(32, ecx, lift_load(&env, eax, 0x2fcu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4b2e84;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x161u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 1, (eax & 0xffu));
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd8u, 1, ((eax >> 8) & 0xffu));
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b2e84;
    edi = lift_load(&env, ebp, 0xffffffacu, 4);
L_4b2dfc:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    ecx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = eax + eax;
    ebx = ebx ^ ebx;
    ecx = ecx + eax;
    edx = edx ^ edx;
    eax = esi;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x162u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    edx = edx + edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    lift_store(&env, esi, eax + 0x0u, 1, 0x0u);
    eax = (ebp + 0xffffffbcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffb4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff90u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff8cu);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x44u, 1)) & 0xffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    eax = lift_load(&env, edx, 0x15du, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    eax = lift_load(&env, ebp, 0xffffff8cu, 4);
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b3035;
L_4b2e6e:
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu) << 8);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) + 1u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    lift_store(&env, ebp, 0xffffffd8u, 1, ((edx >> 8) & 0xffu));
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.cf)
        goto L_4b2dfc;
L_4b2e84:
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x300u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b304c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x161u, 1)) & 0xffu);
    edi = edi ^ edi;
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe4u, 1, (eax & 0xffu));
    lift_store(&env, ebp, 0xffffffdcu, 1, ((ebx >> 8) & 0xffu));
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b2f30;
L_4b2eac:
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffdcu, 1)) & 0xffu);
    ebx = lift_load(&env, ebp, 0xffffff9cu, 4);
    ecx = ecx + ecx;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    ecx = ecx + ebx;
    edx = edx ^ edx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x162u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    edx = edx + eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    lift_store(&env, esi, eax + 0x0u, 1, 0x0u);
    eax = (ebp + 0xffffffb8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffd0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff98u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff94u);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x44u, 1)) & 0xffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    eax = lift_load(&env, edx, 0x15du, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffdcu, 1)) & 0xffu) << 8);
    eax = eax + 1u;
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + 1u) & 0xffu) << 8);
    edi = edi + eax;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffdcu, 1, ((ecx >> 8) & 0xffu));
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.cf)
        goto L_4b2eac;
L_4b2f30:
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    edx = lift_load(&env, edx, 0xf6u, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)(edi & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx - eax;
    ecx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x2f6u, 2)) & 0xffffu);
    eax = eax - edx;
    edx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x2f8u, 2)) & 0xffffu);
    edx = edx - eax;
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
    edi = eax;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b303c;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) + lift_load(&env, ecx, 0x2f6u, 2)) & 0xffffu);
    edi = edi + eax;
L_4b2f7f:
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xeu, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, edx, 0x2f2u, 2)) & 0xffffu);
    eax = eax + ebx;
    lift_store(&env, ebp, 0xffffffc8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x161u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe0u, 1, (eax & 0xffu));
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    lift_store(&env, ebp, 0xffffffd4u, 1, (edx & 0xffu));
    edx = lift_load(&env, eax, 0x2fcu, 4);
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b2ff6;
    {
        (void)lift_sub(32, edx, lift_load(&env, eax, 0x304u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4b305c;
    ebx = lift_load(&env, ebp, 0xffffffb0u, 4);
    ecx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = lift_load(&env, eax, 0xf2u, 4);
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x2f2u, 2)) & 0xffffu);
    eax = eax - ebx;
    eax = eax - edx;
    edx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x2f4u, 2)) & 0xffffu);
    edx = edx - eax;
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b2ff6;
    lift_store(&env, ebp, 0xffffffc8u, 2, lift_load(&env, ebp, 0xffffffc8u, 2) + (eax & 0xffffu));
L_4b2ff6:
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
L_4b2ff9:
    lift_store(&env, ebp, 0xffffffc4u, 2, (eax & 0xffffu));
L_4b2ffd:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), lift_load(&env, ebp, 0xffffffe0u, 1), &fl);
    }
    if (fl.cf)
        goto L_4b3078;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = lift_load(&env, eax, 0x14u, 4);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edi & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx - eax;
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        (void)lift_sub(32, edx, lift_load(&env, eax, 0xf8u, 4), &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.cf || fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
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
L_4b3035:
    eax = edx;
    goto L_4b2e6e;
L_4b303c:
    edi = (edi & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) + lift_load(&env, ecx, 0x2f6u, 2)) & 0xffffu);
    goto L_4b2f7f;
L_4b304c:
    edi = (edi & 0xffff0000u) | ((lift_load(&env, eax, 0x16u, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) + lift_load(&env, eax, 0x2f6u, 2)) & 0xffffu);
    goto L_4b2f7f;
L_4b305c:
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xeu, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, edx, 0xf4u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, edx, 0x2f4u, 2)) & 0xffffu);
    eax = eax + ecx;
    eax = eax - ebx;
    eax = eax - 1u;
    goto L_4b2ff9;
L_4b3078:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    ecx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = eax + eax;
    ebx = ebx ^ ebx;
    ecx = ecx + eax;
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x162u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    edx = edx + eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    lift_store(&env, esi, eax + 0x0u, 1, 0x0u);
    eax = (ebp + 0xffffffc0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffccu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffa4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffa0u);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    ebx = lift_load(&env, ebp, 0xffffffc2u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x44u, 1)) & 0xffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffc6u, 4);
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edi & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
    eax = lift_load(&env, edx, 0x15du, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0xffffffa8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) + 1u) & 0xffu);
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffd4u, 1, (ebx & 0xffu));
    edi = edi + eax;
    goto L_4b2ffd;
}

uint32_t lifted_object_place_label(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_PLACE_LABEL_STACK + 4 + 4 * 2 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_PLACE_LABEL_STACK, 2, entry);
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
    esp = esp - 0x1cu;
    esi = eax;
    eax = (ebp + 0xffffffdcu);
    edi = 0x4ec1ecu;
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
    eax = 0x517c2cu;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    edi = edi ^ edi;
    eax = (ebp + 0xfffffff0u);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x1u);
    lift_store(&env, esi, 0x160u, 4, edx);
    lift_store(&env, esi, 0x164u, 2, (ebx & 0xffffu));
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, esi, 0x166u, 2, (ecx & 0xffffu));
    lift_store(&env, esi, 0x168u, 4, eax);
    eax = lift_load(&env, ebp, 0xcu, 4);
    edx = lift_load(&env, esi, 0x160u, 4);
    lift_store(&env, esi, 0x16cu, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4b32a4;
L_4b3280:
    eax = (ebp + 0xfffffff0u);
    esi = esi ^ esi;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    env.chain = eax;
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
L_4b32a4:
    eax = (ebp + 0xfffffff0u);
    edx = lift_load(&env, edx, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esi, 0x160u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x160u, 1)) & 0xffu);
    ecx = lift_load(&env, esi, 0x168u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4b3318;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0xeu, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, esi, 0x164u, 2)) & 0xffffu);
    edx = edx + ebx;
    ecx = edx;
L_4b32da:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x16cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b3328;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x16u, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, esi, 0x166u, 2)) & 0xffffu);
    eax = eax + edi;
    ebx = eax;
L_4b32f2:
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ebx = lift_load(&env, ebp, 0xfffffff1u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)(ecx & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = lift_load(&env, esi, 0x160u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    goto L_4b3280;
L_4b3318:
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0xeu, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, esi, 0xf4u, 2)) & 0xffffu);
    ecx = ecx + edx;
    ecx = ecx - 1u;
    goto L_4b32da;
L_4b3328:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x16u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, esi, 0xf8u, 2)) & 0xffffu);
    ebx = ebx + eax;
    ebx = ebx - 1u;
    goto L_4b32f2;
}

uint32_t lifted_f4b34d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B34D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B34D0_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b3100u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, eax, 0x158u, 4, 0x517cf4u);
    lift_store(&env, eax, 0x170u, 4, 0x0u);
    lift_store(&env, eax, 0x174u, 4, 0x0u);
    lift_store(&env, eax, 0x178u, 4, 0x0u);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b3500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B3500_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B3500_STACK, 0, entry);
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
    esp = esp - 0x34u;
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4b3579;
    edx = 0x4ec1ecu;
    esi = 0x517ca0u;
    lift_store(&env, eax, 0x158u, 4, 0x517cf4u);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffe8u, 1, (ebx & 0xffu));
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
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    eax = ecx;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b3140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b3565;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b3565:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    env.chain = eax;
    eax = ecx;
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
L_4b3579:
    ebx = 0x1u;
    edx = 0x517d10u;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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

uint32_t lifted_object_set_pair_4b35b0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_SET_PAIR_4B35B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_SET_PAIR_4B35B0_STACK, 0,
               entry);
    lift_store(&env, eax, 0x170u, 4, edx);
    lift_store(&env, eax, 0x174u, 4, ebx);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b3a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B3A00_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B3A00_STACK, 0, entry);
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
    esp = esp - 0x24u;
    esi = eax;
    eax = (ebp + 0xffffffc8u);
    edx = 0x4ec1ecu;
    ecx = 0x517d30u;
    edi = 0x1u;
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
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 1, ((eax >> 8) & 0xffu));
    eax = esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b3100u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    lift_store(&env, eax, 0x158u, 4, 0x517dc4u);
    lift_store(&env, eax, 0x170u, 4, ebx);
    lift_store(&env, eax, 0x174u, 4, ebx);
    esi = eax;
    lift_store(&env, eax, 0x178u, 4, ebx);
    eax = 0x160u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b3b18;
L_4b3a7b:
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
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    lift_store(&env, esi, 0x17cu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x17cu, 4);
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x160u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b3b30;
L_4b3ab7:
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
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    lift_store(&env, esi, 0x180u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x180u, 4);
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x184u, 4, 0x0u);
    lift_store(&env, esi, 0x188u, 4, 0x0u);
    lift_store(&env, esi, 0x18cu, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    env.chain = eax;
    eax = esi;
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
L_4b3b18:
    edx = 0x2u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    goto L_4b3a7b;
L_4b3b30:
    ebx = 0x4u;
    edi = 0x1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    goto L_4b3ab7;
}

uint32_t lifted_object_set_pair_4b3c30(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_SET_PAIR_4B3C30_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_SET_PAIR_4B3C30_STACK, 0,
               entry);
    lift_store(&env, eax, 0x184u, 4, edx);
    lift_store(&env, eax, 0x188u, 4, ebx);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_label_format_alternate(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_LABEL_FORMAT_ALTERNATE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_LABEL_FORMAT_ALTERNATE_STACK, 0,
               entry);
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
    esp = esp - 0x18u;
    ecx = eax;
    eax = (ebp + 0xffffffd8u);
    ebx = 0x4ec1ecu;
    esi = 0x517d70u;
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
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    eax = (ebp + 0xffffffecu);
    lift_store(&env, ecx, 0x18cu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 4, 0x1u);
    edx = lift_load(&env, ecx, 0x18cu, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x51108eu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffecu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
    eax = lift_load(&env, ecx, 0x160u, 4);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax + 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffecu);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    env.chain = eax;
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

uint32_t lifted_f4b3ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B3CE0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B3CE0_STACK, 0, entry);
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
    esp = esp - 0x14u;
    ecx = eax;
    esi = edx;
    eax = (ebp + 0xffffffdcu);
    edx = 0x4ec1ecu;
    ebx = 0x517d7cu;
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
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    edx = lift_load(&env, ecx, 0x18cu, 4);
    eax = lift_load(&env, ecx, 0x184u, 4);
    ebx = ebx ^ ebx;
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b3d43;
    eax = edx;
    ebx = lift_load(&env, ecx, 0x184u, 4);
    eax = eax - ebx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4b3d57;
    edx = ebx;
L_4b3d37:
    eax = ecx;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b3c40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b3d43:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
    eax = ebx;
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
L_4b3d57:
    edx = edx - esi;
    goto L_4b3d37;
}

uint32_t lifted_f4b3d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B3D60_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B3D60_STACK, 0, entry);
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
    esp = esp - 0x14u;
    ecx = eax;
    esi = edx;
    eax = (ebp + 0xffffffdcu);
    edx = 0x4ec1ecu;
    ebx = 0x517d80u;
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
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    edx = lift_load(&env, ecx, 0x18cu, 4);
    eax = lift_load(&env, ecx, 0x188u, 4);
    ebx = ebx ^ ebx;
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (!fl.cf)
        goto L_4b3dbf;
    eax = eax - edx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4b3dd3;
    edx = lift_load(&env, ecx, 0x188u, 4);
L_4b3db3:
    eax = ecx;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b3c40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b3dbf:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
    eax = ebx;
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
L_4b3dd3:
    edx = edx + esi;
    goto L_4b3db3;
}

uint32_t lifted_f4b3fb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B3FB0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B3FB0_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b34d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, eax, 0x158u, 4, 0x517e44u);
    lift_store(&env, eax, 0x17cu, 4, 0x0u);
    lift_store(&env, eax, 0x180u, 4, 0x0u);
    lift_store(&env, eax, 0x184u, 4, 0x0u);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_contains_point(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_CONTAINS_POINT_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_CONTAINS_POINT_STACK, 0, entry);
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
    esi = lift_load(&env, eax, 0x17cu, 4);
    ecx = lift_load(&env, eax, 0xcu, 4);
    edi = lift_load(&env, eax, 0xf4u, 4);
    esi = lift_load(&env, esi, 0xb4u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    esi = lift_load(&env, esi, 0x4u, 4);
    edi = edi + ecx;
    esi = esi + ecx;
    ecx = lift_load(&env, eax, 0x180u, 4);
    ecx = lift_load(&env, ecx, 0xb4u, 4);
    ebp = lift_load(&env, ecx, 0x4u, 4);
    ecx = lift_load(&env, eax, 0x14u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    eax = lift_load(&env, eax, 0xf8u, 4);
    edi = edi - ebp;
    eax = eax + ecx;
    edi = edi - 1u;
    eax = eax - 1u;
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b42c4;
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b42c4;
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b42c4;
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b42cb;
L_4b42c4:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4b42cb:
    eax = 0x1u;
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

uint32_t lifted_object_dword_4b4500(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_DWORD_4B4500_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_DWORD_4B4500_STACK, 0, entry);
    eax = lift_load(&env, eax, 0x174u, 4);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_set_mode(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_SET_MODE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_SET_MODE_STACK, 0, entry);
    lift_store(&env, eax, 0x174u, 4, edx);
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4b451c;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4b451c:
    edx = lift_load(&env, eax, 0x160u, 4);
    eax = eax + 0x188u;
    edx = lift_load(&env, edx, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_cursor_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_CURSOR_ROW_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_CURSOR_ROW_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x170u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b46e0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_object_step_text_length(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_STEP_TEXT_LENGTH_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_STEP_TEXT_LENGTH_STACK, 0,
               entry);
    lift_store(&env, eax, 0x170u, 4, lift_load(&env, eax, 0x170u, 4) - 1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4690u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_step_text_length_4b4610(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_STEP_TEXT_LENGTH_4B4610_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_STEP_TEXT_LENGTH_4B4610_STACK,
               0, entry);
    lift_store(&env, eax, 0x170u, 4, lift_load(&env, eax, 0x170u, 4) + 1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4690u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_step_text_length_4b4620(const VertrixCalls *calls,
                                               const VertrixFactoryServices *services,
                                               const VertrixGlobals *globals,
                                               const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_STEP_TEXT_LENGTH_4B4620_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_STEP_TEXT_LENGTH_4B4620_STACK,
               0, entry);
    lift_store(&env, eax, 0x170u, 4, 0xffffffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4690u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_text_length_reset(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_TEXT_LENGTH_RESET_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_TEXT_LENGTH_RESET_STACK, 0,
               entry);
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
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    edi = lift_load(&env, eax, 0x160u, 4);
    edi = lift_load(&env, edi, 0x15cu, 4);
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
    ecx = ecx - 1u;
    eax = edx;
    lift_store(&env, edx, 0x170u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4690u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_object_cursor_at_end(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_CURSOR_AT_END_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_CURSOR_AT_END_STACK, 0, entry);
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
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    edi = lift_load(&env, eax, 0x160u, 4);
    edi = lift_load(&env, edi, 0x15cu, 4);
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
    ecx = ecx - 1u;
    {
        (void)lift_sub(32, ecx, lift_load(&env, edx, 0x170u, 4), &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
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

uint32_t lifted_object_cursor_clamp(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_CURSOR_CLAMP_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_CURSOR_CLAMP_STACK, 0, entry);
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
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    edi = lift_load(&env, eax, 0x160u, 4);
    edi = lift_load(&env, edi, 0x15cu, 4);
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
    ebx = lift_load(&env, edx, 0x170u, 4);
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b46c0;
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b46cf;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4b46c0:
    lift_store(&env, edx, 0x170u, 4, 0xffffffffu);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4b46cf:
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, edx, 0x170u, 4, ecx);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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

uint32_t lifted_object_text_row(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_TEXT_ROW_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_TEXT_ROW_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    edx = edx + 1u;
    eax = eax ^ eax;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b46ec;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4b46ec:
    eax = lift_load(&env, ecx, 0x160u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6930u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_object_text_nearest(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_TEXT_NEAREST_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_TEXT_NEAREST_STACK, 0, entry);
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
    esp = esp - 0xcu;
    esi = eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    edi = lift_load(&env, eax, 0x160u, 4);
    edx = 0xffffffffu;
    ebx = 0x4e20u;
    edi = lift_load(&env, edi, 0x15cu, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
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
    eax = ecx;
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    ecx = edx;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b4769;
L_4b473c:
    eax = lift_load(&env, esi, 0x160u, 4);
    edx = ecx;
    edi = lift_load(&env, eax, 0xcu, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b46e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    eax = eax - edx;
    eax = eax + edi;
    edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;
    eax = eax ^ edx;
    eax = eax - edx;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b4774;
L_4b4761:
    edi = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b473c;
L_4b4769:
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
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
L_4b4774:
    lift_store(&env, ebp, 0xfffffff0u, 4, ecx);
    ebx = eax;
    goto L_4b4761;
}

uint32_t lifted_object_text_seek(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_TEXT_SEEK_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_TEXT_SEEK_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x170u, 4, eax);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_parent_append(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_PARENT_APPEND_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_PARENT_APPEND_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (eax + 0x188u);
    eax = lift_load(&env, eax, 0x160u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_object_parent_glyph(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_PARENT_GLYPH_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_PARENT_GLYPH_STACK, 0, entry);
    edx = edx & 0xffu;
    eax = lift_load(&env, eax, 0x160u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6a10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_parent_append_4b4cd0(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_PARENT_APPEND_4B4CD0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_PARENT_APPEND_4B4CD0_STACK, 0,
               entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (eax + 0x18cu);
    eax = lift_load(&env, eax, 0x160u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4b4cf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B4CF0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B4CF0_STACK, 0, entry);
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
    esp = esp - 0x24u;
    esi = eax;
    eax = (ebp + 0xffffffc8u);
    edx = 0x4ec1ecu;
    ecx = 0x518050u;
    edi = 0x1u;
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
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 1, ((eax >> 8) & 0xffu));
    eax = esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b3100u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    lift_store(&env, eax, 0x158u, 4, 0x5180f4u);
    lift_store(&env, eax, 0x170u, 4, ebx);
    lift_store(&env, eax, 0x174u, 4, ebx);
    esi = eax;
    lift_store(&env, eax, 0x178u, 4, ebx);
    eax = 0x160u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b4e6a;
L_4b4d6b:
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
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    lift_store(&env, esi, 0x17cu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x17cu, 4);
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x160u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4b4dbf;
    ebx = 0x4u;
    edi = 0x1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
L_4b4dbf:
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
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    lift_store(&env, esi, 0x184u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x184u, 4);
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x160u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b4e82;
L_4b4dff:
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
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    lift_store(&env, esi, 0x180u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x180u, 4);
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x188u, 4, 0x0u);
    lift_store(&env, esi, 0x18cu, 4, 0x0u);
    lift_store(&env, esi, 0x190u, 4, 0x0u);
    lift_store(&env, esi, 0x194u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    env.chain = eax;
    eax = esi;
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
L_4b4e6a:
    edx = 0x2u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    goto L_4b4d6b;
L_4b4e82:
    edx = 0x6u;
    ecx = 0x1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    goto L_4b4dff;
}

uint32_t lifted_object_set_pair_4b4fa0(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_SET_PAIR_4B4FA0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_SET_PAIR_4B4FA0_STACK, 0,
               entry);
    lift_store(&env, eax, 0x188u, 4, edx);
    lift_store(&env, eax, 0x18cu, 4, ebx);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_label_format(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_LABEL_FORMAT_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_LABEL_FORMAT_STACK, 0, entry);
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
    esp = esp - 0x18u;
    ecx = eax;
    eax = (ebp + 0xffffffd8u);
    ebx = 0x4ec1ecu;
    esi = 0x5180a0u;
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
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    eax = (ebp + 0xffffffecu);
    lift_store(&env, ecx, 0x190u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 4, 0x1u);
    edx = lift_load(&env, ecx, 0x190u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x511094u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffecu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
    eax = lift_load(&env, ecx, 0x160u, 4);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax + 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffecu);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    env.chain = eax;
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

uint32_t lifted_f4b5050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B5050_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B5050_STACK, 0, entry);
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
    esp = esp - 0x14u;
    ecx = eax;
    esi = edx;
    eax = (ebp + 0xffffffdcu);
    edx = 0x4ec1ecu;
    ebx = 0x5180acu;
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
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    edx = lift_load(&env, ecx, 0x190u, 4);
    eax = lift_load(&env, ecx, 0x188u, 4);
    ebx = ebx ^ ebx;
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b50b3;
    eax = edx;
    ebx = lift_load(&env, ecx, 0x188u, 4);
    eax = eax - ebx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4b50c7;
    edx = ebx;
L_4b50a7:
    eax = ecx;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4fb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b50b3:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
    eax = ebx;
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
L_4b50c7:
    edx = edx - esi;
    goto L_4b50a7;
}

uint32_t lifted_f4b50d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B50D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B50D0_STACK, 0, entry);
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
    esp = esp - 0x14u;
    ecx = eax;
    esi = edx;
    eax = (ebp + 0xffffffdcu);
    edx = 0x4ec1ecu;
    ebx = 0x5180b0u;
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
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    edx = lift_load(&env, ecx, 0x190u, 4);
    eax = lift_load(&env, ecx, 0x18cu, 4);
    ebx = ebx ^ ebx;
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (!fl.cf)
        goto L_4b512f;
    eax = eax - edx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4b5143;
    edx = lift_load(&env, ecx, 0x18cu, 4);
L_4b5123:
    eax = ecx;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4fb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b512f:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
    eax = ebx;
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
L_4b5143:
    edx = edx + esi;
    goto L_4b5123;
}

uint32_t lifted_object_destroy_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_DESTROY_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_DESTROY_CALL_STACK, 0, entry);
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
    esp = esp - 0x34u;
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4b5499;
    edx = 0x4ec1ecu;
    esi = 0x518130u;
    lift_store(&env, eax, 0x158u, 4, 0x518174u);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffe8u, 1, (ebx & 0xffu));
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
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    eax = ecx;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b5485;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b5485:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    env.chain = eax;
    eax = ecx;
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
L_4b5499:
    ebx = 0x1u;
    edx = 0x518190u;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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

uint32_t lifted_f4b5580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B5580_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B5580_STACK, 0, entry);
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
    esp = esp - 0x20u;
    edx = eax;
    eax = (ebp + 0xffffffccu);
    ecx = 0x4ec1ecu;
    ebx = 0x5181b0u;
    edi = 0x1u;
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
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    lift_store(&env, ebp, 0xffffffe4u, 1, ((eax >> 8) & 0xffu));
    eax = edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    edx = eax;
    lift_store(&env, eax, 0x158u, 4, 0x518244u);
    eax = 0x160u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b5628;
L_4b55e5:
    lift_store(&env, edx, 0x184u, 4, 0x0u);
    lift_store(&env, edx, 0x188u, 4, 0x0u);
    lift_store(&env, edx, 0x180u, 4, 0x0u);
    lift_store(&env, edx, 0x190u, 4, 0x1u);
    lift_store(&env, edx, 0x18cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    env.chain = eax;
    eax = edx;
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
L_4b5628:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4b55e5;
}

uint32_t lifted_f4b5630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B5630_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B5630_STACK, 0, entry);
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
    esp = esp - 0x34u;
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4b56ce;
    edx = 0x4ec1ecu;
    esi = 0x5181bcu;
    lift_store(&env, eax, 0x158u, 4, 0x518244u);
    edi = 0x3u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffe8u, 1, (ebx & 0xffu));
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
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    eax = lift_load(&env, ecx, 0x18cu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4b5698;
    esi = lift_load(&env, eax, 0x158u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b5698:
    eax = eax ^ eax;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6460u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b56ba;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b56ba:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    env.chain = eax;
    eax = ecx;
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
L_4b56ce:
    ebx = 0x1u;
    edx = 0x518260u;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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

uint32_t lifted_f4b5700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B5700_STACK + 4 + 4 * 3 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B5700_STACK, 3, entry);
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
    esp = esp - 0x28u;
    esi = eax;
    lift_store(&env, ebp, 0xfffffff4u, 1, (ebx & 0xffu));
    lift_store(&env, ebp, 0xfffffff0u, 2, (ecx & 0xffffu));
    eax = (ebp + 0xffffffd0u);
    ecx = 0x4ec1ecu;
    ebx = 0x5181d8u;
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
    edi = edi ^ edi;
    eax = (ebp + 0xffffffe4u);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    lift_store(&env, esi, 0x180u, 4, edx);
    {
        (void)lift_sub(32, eax, lift_load(&env, esi, 0x184u, 4), &fl);
    }
    if (fl.zf)
        goto L_4b5812;
    ecx = lift_load(&env, esi, 0x180u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x51109eu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
L_4b5772:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x190u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b5791;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x180u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b5791;
    edx = 0x5110a1u;
    eax = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b5791:
    eax = lift_load(&env, ebp, 0xeu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edi = lift_load(&env, ebp, 0xffffffeeu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xau, 4);
    ebx = lift_load(&env, ebp, 0xfffffff1u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0x6u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    eax = lift_load(&env, ebp, 0x10u, 4);
    eax = eax - lift_load(&env, ebp, 0xcu, 4);
    eax = eax + 1u;
    eax = eax & 0xffffu;
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0x8u, 4);
    edx = edi;
    eax = eax - ebx;
    ecx = ecx ^ ecx;
    eax = eax + 1u;
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = (ecx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = lift_load(&env, esi, 0x18cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = eax ^ eax;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    env.chain = eax;
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
L_4b5812:
    eax = (ebp + 0xffffffe8u);
    ebx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    edi = lift_load(&env, esi, 0x180u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x511098u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
    edx = 0x51109bu;
    eax = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = eax - 0xcu;
    eax = lift_load(&env, eax, 0x4u, 4);
    ecx = lift_load(&env, esi, 0x188u, 4);
    ebx = eax;
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b5870;
    edi = 0x51109cu;
L_4b5861:
    eax = (ebp + 0xffffffe4u);
    edx = edi;
    ecx = ecx - 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4b5861;
L_4b5870:
    edx = (ebp + 0xffffffe8u);
    eax = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, 0x1u);
    goto L_4b5772;
}

uint32_t lifted_f4b58a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B58A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B58A0_STACK, 0, entry);
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
    esp = esp - 0x1cu;
    esi = eax;
    eax = (ebp + 0xffffffd4u);
    ecx = 0x4ec1ecu;
    ebx = 0x5181ecu;
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
    edi = edi ^ edi;
    eax = (ebp + 0xffffffe8u);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, esi, 0x180u, 4, edx);
    {
        (void)lift_sub(32, eax, lift_load(&env, esi, 0x184u, 4), &fl);
    }
    if (fl.zf)
        goto L_4b598a;
    ecx = lift_load(&env, esi, 0x180u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5110a8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
L_4b590d:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x190u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b592c;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x180u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b592c;
    edx = 0x5110abu;
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b592c:
    eax = lift_load(&env, esi, 0x166u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x164u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, esi, 0x160u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x162u, 4);
    ebx = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    eax = (ebp + 0xffffffe8u);
    esi = esi ^ esi;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    env.chain = eax;
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
L_4b598a:
    eax = (ebp + 0xffffffecu);
    ebx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    edi = lift_load(&env, esi, 0x180u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5110a2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffecu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
    edx = 0x5110a5u;
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax - 0xcu;
    eax = lift_load(&env, eax, 0x4u, 4);
    ecx = lift_load(&env, esi, 0x188u, 4);
    ebx = eax;
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b59f0;
L_4b59d4:
    edx = 0x5110a6u;
    eax = (ebp + 0xffffffe8u);
    ecx = ecx - 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4b59d4;
L_4b59f0:
    edx = (ebp + 0xffffffecu);
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = (ebp + 0xffffffecu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, 0x1u);
    goto L_4b590d;
}

uint32_t lifted_object_start_5182c4(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_START_5182C4_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_START_5182C4_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, eax, 0x158u, 4, 0x5182c4u);
    lift_store(&env, eax, 0x15cu, 2, 0x0u);
    lift_store(&env, eax, 0x160u, 4, 0x0u);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_slot_present_unowned(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_SLOT_PRESENT_UNOWNED_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_SLOT_PRESENT_UNOWNED_STACK, 0,
               entry);
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
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x15cu, 2)) & 0xffffu);
    ebx = ebx ^ ebx;
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4b5d59;
L_4b5d53:
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
L_4b5d59:
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x15cu, 2)) & 0xffffu);
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b5d53;
    edx = lift_load(&env, ecx, 0x160u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4b5d86;
    ebx = 0x1u;
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
L_4b5d86:
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x15cu, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x1u;
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

uint32_t lifted_object_destroy_a(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_DESTROY_A_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_DESTROY_A_STACK, 0, entry);
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
    esp = esp - 0x40u;
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4b5e3d;
    edx = 0x4ec1ecu;
    esi = 0x518300u;
    lift_store(&env, eax, 0x0u, 4, 0x518344u);
    edi = edi ^ edi;
    eax = (eax & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffdcu, 1, ((eax >> 8) & 0xffu));
    eax = (ebp + 0xffffffc4u);
    lift_store(&env, ebp, 0xffffffe8u, 1, (ebx & 0xffu));
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
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, esi);
    eax = ecx;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d86d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b5e29;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b5e29:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    env.chain = eax;
    eax = ecx;
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
L_4b5e3d:
    ebx = 0x1u;
    edx = 0x516390u;
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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

uint32_t lifted_object_release_items(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_RELEASE_ITEMS_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_RELEASE_ITEMS_STACK, 0, entry);
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
    esi = eax;
    eax = lift_load(&env, eax, 0x8u, 4);
    ecx = ecx ^ ecx;
    edi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b604c;
    ebx = ebx ^ ebx;
L_4b6034:
    eax = lift_load(&env, esi, 0x4u, 4);
    edx = lift_load(&env, ebx, eax + 0x0u, 4);
    eax = lift_load(&env, edx, 0xb4u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b6052;
    ecx = ecx + 1u;
    ebx = ebx + 0x4u;
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (fl.cf)
        goto L_4b6034;
L_4b604c:
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
L_4b6052:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4830f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edx, 0xb4u, 4, 0x0u);
    ecx = ecx + 1u;
    ebx = ebx + 0x4u;
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (fl.cf)
        goto L_4b6034;
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

uint32_t lifted_object_destroy_d(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_DESTROY_D_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_DESTROY_D_STACK, 0, entry);
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
    esp = esp - 0x34u;
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4b64fa;
    edx = 0x4ec1ecu;
    esi = 0x518374u;
    lift_store(&env, eax, 0x158u, 4, 0x518404u);
    edi = 0x3u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffe8u, 1, (ebx & 0xffu));
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
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    eax = (ecx + 0x15cu);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = (eax + 0xfffffea4u);
    eax = eax ^ eax;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b64e6;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b64e6:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    env.chain = eax;
    eax = ecx;
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
L_4b64fa:
    ebx = 0x1u;
    edx = 0x518420u;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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

uint32_t lifted_timer_reset(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_TIMER_RESET_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_TIMER_RESET_STACK, 0, entry);
    lift_store(&env, eax, 0x17au, 2, 0x0u);
    lift_store(&env, eax, 0x178u, 1, (edx & 0xffu));
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_set_word(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_SET_WORD_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_SET_WORD_STACK, 0, entry);
    lift_store(&env, eax, 0x17au, 2, (edx & 0xffffu));
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_set_word_4b6550(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_SET_WORD_4B6550_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_SET_WORD_4B6550_STACK, 0,
               entry);
    lift_store(&env, eax, 0x17cu, 2, (edx & 0xffffu));
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_word(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_WORD_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_WORD_STACK, 0, entry);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x17cu, 2)) & 0xffffu);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_word_4b65a0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_WORD_4B65A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_WORD_4B65A0_STACK, 0, entry);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x17au, 2)) & 0xffffu);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_set_dword_4b65b0(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_SET_DWORD_4B65B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_SET_DWORD_4B65B0_STACK, 0,
               entry);
    lift_store(&env, eax, 0x174u, 4, 0x1u);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_set_four_words(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_SET_FOUR_WORDS_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_SET_FOUR_WORDS_STACK, 1, entry);
    lift_store(&env, eax, 0x16au, 2, (edx & 0xffffu));
    lift_store(&env, eax, 0x16cu, 2, (ebx & 0xffffu));
    lift_store(&env, eax, 0x16eu, 2, (ecx & 0xffffu));
    edx = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x170u, 2, (edx & 0xffffu));
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_contains(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_CONTAINS_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_CONTAINS_STACK, 0, entry);
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
    esi = (esi & 0xffff0000u) | ((lift_load(&env, eax, 0x16au, 2)) & 0xffffu);
    ecx = 0x1u;
    {
        (void)lift_sub(16, (edx & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b66ee;
    {
        (void)lift_sub(16, (ebx & 0xffffu), lift_load(&env, eax, 0x16eu, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b66ee;
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, eax, 0x16cu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b66ee;
    {
        (void)lift_sub(16, (ebx & 0xffffu), lift_load(&env, eax, 0x170u, 2), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b66f0;
L_4b66ee:
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
L_4b66f0:
    eax = ecx;
    lift_store(&env, 0u, 0x5bd828u, 4, ecx);
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

uint32_t lifted_object_slot_present_4b6700(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_SLOT_PRESENT_4B6700_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_SLOT_PRESENT_4B6700_STACK, 0,
               entry);
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
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x172u, 2)) & 0xffffu);
    ebx = ebx ^ ebx;
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4b6719;
L_4b6713:
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
L_4b6719:
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x172u, 2)) & 0xffffu);
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b6713;
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x172u, 2)) & 0xffffu);
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
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
}

uint32_t lifted_object_text_value(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_TEXT_VALUE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_TEXT_VALUE_STACK, 0, entry);
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
    ecx = eax;
    eax = (ebp + 0xffffffd0u);
    ebx = 0x4ec1ecu;
    esi = 0x51839cu;
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
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    eax = (ecx + 0x15cu);
    ebx = edx;
    edx = (ebp + 0xffffffe4u);
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdb70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, 0x1u);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = eax - 0xcu;
    eax = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b69a7;
    eax = (ebp + 0xffffffe4u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    env.chain = eax;
    eax = ecx;
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
L_4b69a7:
    eax = (ebp + 0xffffffecu);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ebx = ebx ^ ebx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    eax = lift_load(&env, ecx, 0x15du, 4);
    ecx = (ebp + 0xffffffe8u);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x440610u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (ebp + 0xffffffe4u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    env.chain = eax;
    eax = ecx;
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

uint32_t lifted_object_glyph_present(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_GLYPH_PRESENT_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_GLYPH_PRESENT_STACK, 0, entry);
    eax = lift_load(&env, eax, 0x15du, 4);
    edx = edx & 0xffu;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f460u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_release_call_4b6f70(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_RELEASE_CALL_4B6F70_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_RELEASE_CALL_4B6F70_STACK, 0,
               entry);
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
    ecx = 0x1u;
    esi = lift_load(&env, eax, 0x8u, 4);
    ebx = edx;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d88a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
