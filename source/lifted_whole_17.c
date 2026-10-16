/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_17.h"

uint32_t lifted_f427850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F427850_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F427850_STACK, 0, entry);
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
    esp = esp - 0x138u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, edx, 0x3b0u, 4);
    ecx = 0x41u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    esi = lift_load(&env, esi, 0x15cu, 4);
    edx = lift_load(&env, eax, 0x15cu, 4);
    eax = esi;
    edi = (ebp + 0xffffff6cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
    esi = esi + 0x1deu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    ecx = 0x41u;
    edi = (ebp + 0xffffff28u);
    esi = (edx + 0x1deu);
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
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (ebp + 0xfffffeb8u);
    eax = lift_load(&env, eax, 0x3b8u, 4);
    esi = lift_load(&env, ebp, 0xffffffecu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x429e80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = esi + 0x1c5u;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x427e10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = esi;
    ebx = (ebp + 0xffffff28u);
    edx = (ebp + 0xffffff6cu);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x428110u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = lift_load(&env, eax, 0x164u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, eax, 0x180u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax - 0xcu;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, eax, 0x180u, 4);
    eax = eax - 0xcu;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = lift_load(&env, eax, 0x178u, 4);
    edx = lift_load(&env, edx, 0x17cu, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = lift_load(&env, eax, 0x17cu, 4);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = lift_load(&env, ecx, 0x178u, 4);
    edi = lift_load(&env, ebp, 0xffffffecu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x427c10u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    edi = edi + 0x1f4u;
    ebx = lift_load(&env, eax, 0x160u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffb0u);
    ecx = esi;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = edi;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4288d0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    esi = lift_load(&env, eax, 0x160u, 4);
    ecx = (ebp + 0xfffffeb8u);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edi;
    ebx = (eax + 0x210u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x428e70u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
