/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md) that did NOT pass
 * tools/verify_lifted.py: unverified, used only when explicitly enabled. */
#include "lift_runtime.h"

#include "lifted_unverified.h"

uint32_t lifted_f4e6d16(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6D16_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6D16_STACK, 0, entry);
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
    esp = esp - 0x60u;
    ebp = eax;
    edx = (esp + 0x54u);
    eax = esp;
    lift_store(&env, esp, 0x54u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6cf2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi ^ edi;
    esi = esi ^ esi;
    lift_store(&env, esp, 0x38u, 4, 0xe5671234u);
    lift_store(&env, esp, 0x3cu, 4, 0x0u);
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    lift_store(&env, esp, 0x44u, 4, 0x0u);
    lift_store(&env, esp, 0x48u, 4, 0x2u);
    eax = esp;
    lift_store(&env, esp, 0x4cu, 4, 0x0u);
    lift_store(&env, esp, 0x50u, 4, eax);
    eax = env.chain;
    ebx = eax;
L_4e6d76:
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e6d9c;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e6d8d;
    esi = lift_load(&env, esp, 0x8u, 4);
    esi = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4e6e06;
L_4e6d8d:
    eax = esi;
    lift_store(&env, ebp, 0x0u, 4, edi);
    {
        uint32_t r = lift_add(32, esp, 0x60u, &fl);
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
L_4e6d9c:
    eax = lift_load(&env, ebx, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6cd4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, eax, 0x5u, 1);
    {
        (void)lift_sub(32, edx, 0x57u, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
    edx = lift_load(&env, eax, 0x6u, 1);
    {
        (void)lift_sub(32, edx, 0x41u, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
    edx = lift_load(&env, eax, 0x7u, 1);
    {
        (void)lift_sub(32, edx, 0x54u, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
    edx = lift_load(&env, eax, 0x8u, 1);
    {
        (void)lift_sub(32, edx, 0x43u, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
    edx = lift_load(&env, eax, 0x9u, 1);
    {
        (void)lift_sub(32, edx, 0x4fu, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
    eax = lift_load(&env, eax, 0xau, 1);
    {
        (void)lift_sub(32, eax, 0x4du, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
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
    eax = (esp + 0x44u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0x10u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
    eax = lift_load(&env, esp, 0x8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edi = ebx;
    {
        (void)lift_and(8, lift_load(&env, eax, 0x4u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e6dff;
    esi = eax;
L_4e6dff:
    ebx = lift_load(&env, ebx, 0x0u, 4);
    goto L_4e6d76;
L_4e6e06:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x5c5c54u, 4);
    esi = esi + eax;
    goto L_4e6d8d;
}
