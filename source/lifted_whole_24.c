/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_24.h"

uint32_t lifted_f4b41f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B41F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B41F0_STACK, 0, entry);
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
    eax = lift_load(&env, eax, 0x17cu, 4);
    ecx = lift_load(&env, eax, 0x158u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, edx, 0x180u, 4);
    ecx = lift_load(&env, eax, 0x158u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b3390u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, edx, 0x17cu, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edx, 0xeu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    ecx = lift_load(&env, edx, 0x17cu, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edx, 0x16u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edx, 0xeu, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, edx, 0xf4u, 2)) & 0xffffu);
    ebx = ebx + eax;
    eax = lift_load(&env, edx, 0x180u, 4);
    ecx = lift_load(&env, eax, 0xb4u, 4);
    esi = (esi & 0xffff0000u) | ((lift_load(&env, ecx, 0x4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(32, ebx, esi, &fl);
        ebx = r;
    }
    lift_store(&env, eax, 0xeu, 2, (ebx & 0xffffu));
    ecx = lift_load(&env, edx, 0x180u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edx, 0x16u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
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
