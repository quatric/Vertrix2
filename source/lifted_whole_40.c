/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_40.h"

uint32_t lifted_rtl_square_root(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_SQUARE_ROOT_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_SQUARE_ROOT_STACK, 0, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
    esp = esp - 0x8u;
    lift_store(&env, ebp, 0xfffffff8u, 4, eax);
    lift_store(&env, ebp, 0xfffffffcu, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c9b2f;
    edx = (ebp + 0xfffffff8u);
    eax = 0x2043u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dad2eu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c9b5a;
L_4c9b2f:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5054a1u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c9b4e;
    eax = lift_load(&env, ebp, 0xfffffff8u, 4);
    {
        uint32_t v = ebp;
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
    ebp = esp;
    lift_x87(&env, 0x4c9b40);
    lift_x87(&env, 0x4c9b43);
    lift_x87(&env, 0x4c9b45);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    goto L_4c9b5a;
L_4c9b4e:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4c9b60;
    eax = lift_load(&env, ebp, 0xfffffff8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db10au, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c9b5a:
    lift_store(&env, ebp, 0xfffffff8u, 4, eax);
    lift_store(&env, ebp, 0xfffffffcu, 4, edx);
L_4c9b60:
    eax = lift_load(&env, ebp, 0xfffffff8u, 4);
    edx = lift_load(&env, ebp, 0xfffffffcu, 4);
    esp = ebp;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}
