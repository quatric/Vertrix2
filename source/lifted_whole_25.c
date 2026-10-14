/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_25.h"

uint32_t lifted_f4b3de0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B3DE0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B3DE0_STACK, 0, entry);
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
    esp = esp - 0x10u;
    esi = eax;
    edi = edx;
    eax = lift_load(&env, eax, 0x17cu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x48u, 2)) & 0xffffu);
    lift_store(&env, eax, 0x48u, 2, (edx & 0xffffu));
    edx = lift_load(&env, esi, 0x180u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x48u, 2)) & 0xffffu);
    lift_store(&env, edx, 0x48u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esi, 0x18cu, 4);
    edx = lift_load(&env, esi, 0x184u, 4);
    ecx = lift_load(&env, esi, 0xf4u, 4);
    eax = eax - edx;
    {
        uint32_t r = lift_imul(32, eax, ecx, &fl);
        eax = r;
    }
    ebx = lift_load(&env, esi, 0x188u, 4);
    ebx = ebx - edx;
    edx = edx ^ edx;
    lift_div1(32, ebx, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0xeu, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    ecx = lift_load(&env, esi, 0xf8u, 4);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    ecx = ecx ^ ecx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x16u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe8u, 2)) & 0xffffu);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    eax = lift_load(&env, esi, 0x17cu, 4);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe4u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0xeu, 2)) & 0xffffu);
    ecx = lift_load(&env, esi, 0xf4u, 4);
    edx = edx + ebx;
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x16u, 2)) & 0xffffu);
    ecx = ecx - ebx;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    ecx = lift_load(&env, esi, 0xf8u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    ecx = ecx ^ ecx;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe8u, 2)) & 0xffffu);
    eax = lift_load(&env, esi, 0x180u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe4u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, esi, 0x17cu, 4);
    ecx = lift_load(&env, eax, 0x158u, 4);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esi, 0x180u, 4);
    ecx = lift_load(&env, eax, 0x158u, 4);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esi, 0x160u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b3f11;
L_4b3ed7:
    eax = lift_load(&env, esi, 0x170u, 4);
    ecx = lift_load(&env, eax, 0x158u, 4);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esi, 0x174u, 4);
    ecx = lift_load(&env, eax, 0x158u, 4);
    edx = edi;
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
L_4b3f11:
    ecx = lift_load(&env, eax, 0x158u, 4);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4b3ed7;
}
