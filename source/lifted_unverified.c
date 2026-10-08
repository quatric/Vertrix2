/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md) that did NOT pass
 * tools/verify_lifted.py: unverified, used only when explicitly enabled. */
#include "lift_runtime.h"

#include "lifted_unverified.h"

uint32_t lifted_f411f50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F411F50_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F411F50_STACK, 0, entry);
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
    ecx = eax;
    eax = lift_load(&env, 0u, 0x5328b4u, 4);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418870u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5328b8u, 4, edx);
    ebx = lift_load(&env, 0u, 0x5328b4u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_411fa0;
L_411f73:
    esi = esi ^ esi;
    lift_store(&env, 0u, 0x5328b4u, 4, esi);
    lift_store(&env, ecx, 0x1cu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b94u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x20u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1cb4u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    lift_store(&env, 0u, 0x5328b0u, 4, edi);
    {
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
L_411fa0:
    eax = ebx;
    ebx = lift_load(&env, ebx, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_411f73;
}

uint32_t lifted_f413bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F413BD0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F413BD0_STACK, 0, entry);
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
    esp = esp - 0x174u;
    eax = (ebp + 0xffffff94u);
    edx = 0x4ec1ecu;
    ecx = 0x5139a4u;
    esi = 0x1u;
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
    eax = (ebp + 0xffffff7cu);
    lift_store(&env, ebp, 0xffffff98u, 4, edx);
    lift_store(&env, ebp, 0xffffff9cu, 4, ecx);
    lift_store(&env, ebp, 0xffffffa0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489f90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x50cbfdu;
    edx = 0x4fcde8u;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50cc09u;
    lift_store(&env, ebp, 0xffffffa0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x4cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x532d8cu;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cc0au;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50cc1au;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x4cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x532ebcu;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cc1bu;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50cc2du;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x2fu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x5330a8u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cc2eu;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50cc44u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x1cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x532fecu;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cc45u;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ecx = 0x50cc5au;
    ebx = 0x13u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x53305cu;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cc5bu;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50cc72u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x14u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x5332c0u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ecx = 0x50cc73u;
    ebx = 0x14u;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x533450u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cc74u;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50cc87u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x14u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x533310u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cc88u;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50cc9bu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x14u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x533d7cu;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ecx = 0x50cc9cu;
    ebx = 0x14u;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x533dccu;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cc9du;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ecx = 0x50ccafu;
    ebx = 0x14u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x533360u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ecx = 0x50ccb0u;
    ebx = 0x14u;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x5333b0u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x50ccb1u;
    ebx = 0x14u;
    edx = 0x533400u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50ccb2u;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50ccc5u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x14u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x53ba88u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50ccc6u;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50ccd6u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x1a2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x533e1cu;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ecx = 0x533e1cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ecx + 0x688u);
L_413fdf:
    eax = ecx;
    ecx = ecx + 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.zf)
        goto L_413fdf;
    ebx = 0x50ccd7u;
    edx = 0x4fcde8u;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50cce5u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x13u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x53453cu;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x50cce6u;
    ebx = 0x13u;
    edx = 0x534588u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x50cce7u;
    ebx = 0x13u;
    edx = 0x5345d4u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cce8u;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50ccfcu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x36u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x5334a0u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x50ccfdu;
    ebx = 0x36u;
    edx = 0x533578u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50ccfeu;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50cd11u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x17u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x533650u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cd12u;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x50cd29u;
    ebx = 0x14u;
    edx = 0x534620u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x50cd2au;
    ebx = 0x14u;
    edx = 0x534670u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x50cd2bu;
    ebx = 0x14u;
    edx = 0x5346c0u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cd2cu;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50cd49u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x14u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x534750u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cd4au;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x32u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x14u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x5347a0u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cd5eu;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    edi = 0x5336acu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_414274:
    ecx = 0x32u;
    ebx = 0x14u;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff7cu);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    esi = esi + 1u;
    edi = edi + 0x50u;
    {
        (void)lift_sub(32, esi, 0xeu, &fl);
    }
    if (fl.cf)
        goto L_414274;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cd6du;
    edx = 0x4fcde8u;
    ecx = 0x50cd7eu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    esi = 0x53483cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x13u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x53483cu;
    eax = (ebp + 0xffffff7cu);
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = 0x13u;
    edx = 0x534888u;
    eax = (ebp + 0xffffff7cu);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffa8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = 0x13u;
    edx = 0x5348d4u;
    eax = (ebp + 0xffffff7cu);
    ecx = ecx ^ ecx;
    edi = 0x534f5cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    edx = 0x5396e8u;
    ecx = 0x53612cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x53a8b8u;
    lift_store(&env, ebp, 0xffffffbcu, 4, edx);
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
L_414346:
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    ebx = ebx ^ ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = 0x50cd7fu;
    lift_store(&env, eax, 0x53969cu, 4, ebx);
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    eax = lift_load(&env, esi, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4149ca;
L_41436b:
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    edx = lift_load(&env, ebp, 0xffffffbcu, 4);
    ecx = lift_load(&env, ebp, 0xffffffc0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
    esi = esi + 0x4u;
    edi = edi + 0xf0u;
    eax = eax + 0xf0u;
    edx = edx + 0xf0u;
    ecx = ecx + 0xf0u;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    lift_store(&env, ebp, 0xffffffbcu, 4, edx);
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffa8u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x13u, &fl);
    }
    if (fl.cf)
        goto L_414346;
    ebx = 0x50cd82u;
    edx = 0x4fcde8u;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x1u;
    edi = 0x534920u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x534c18u;
    lift_store(&env, ebp, 0xffffffc8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
L_4143e0:
    ecx = 0x50cd97u;
    ebx = 0x13u;
    eax = (esi + esi);
    edx = edi;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff7cu);
    edi = edi + 0x4cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = lift_load(&env, ebp, 0xffffffc8u, 4);
    edx = lift_load(&env, ebp, 0xffffffc4u, 4);
    eax = (ebp + 0xffffff7cu);
    ecx = ecx ^ ecx;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = 0x13u;
    esi = esi + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = eax + 0x4cu;
    edx = edx + 0x2u;
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    {
        (void)lift_sub(32, esi, 0xau, &fl);
    }
    if (fl.cf)
        goto L_4143e0;
    eax = (ebp + 0xffffff7cu);
    ecx = 0x2f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
L_414444:
    esi = 0x534920u;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    ecx = edi;
    ebx = ebx ^ ebx;
    ecx = ecx + 0x534920u;
    esi = esi + eax;
    lift_store(&env, edi, 0x534f10u, 4, ebx);
    ebx = edi;
L_414460:
    edx = 0x50cd98u;
    eax = lift_load(&env, ecx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_414484;
    edx = lift_load(&env, ebx, 0x534f10u, 4);
    edx = edx + 1u;
    ecx = ecx + 0x4cu;
    lift_store(&env, ebx, 0x534f10u, 4, edx);
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.cf)
        goto L_414460;
L_414484:
    ecx = lift_load(&env, ebp, 0xffffffccu, 4);
    ecx = ecx + 0x4u;
    edi = edi + 0x4u;
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    {
        (void)lift_sub(32, edi, 0x4cu, &fl);
    }
    if (!fl.zf)
        goto L_414444;
    ebx = 0x50cd99u;
    edx = 0x4fcde8u;
    eax = (ebp + 0xfffffe78u);
    ecx = 0x50cdabu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x5u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x540050u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = 0x5u;
    edx = 0x540064u;
    eax = (ebp + 0xffffff7cu);
    ecx = ecx ^ ecx;
    esi = 0x540050u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = 0x5u;
    edx = 0x540078u;
    eax = (ebp + 0xffffff7cu);
    ecx = ecx ^ ecx;
    edi = 0x540294u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    edx = 0x5400f0u;
    ecx = 0x54008cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    eax = 0x540230u;
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
L_41453b:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx ^ ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = 0x50cdacu;
    lift_store(&env, eax, 0x54021cu, 4, ebx);
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    eax = lift_load(&env, esi, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_414617;
    edx = 0x4fcde8u;
    eax = (ebp + 0xfffffe78u);
    ebx = lift_load(&env, esi, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_414617;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ecx = 0x50cdadu;
    ebx = 0x5u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x50cdaeu;
    ebx = 0x5u;
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = 0x5u;
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = (ebp + 0xffffff7cu);
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x3u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = 0x5u;
    eax = (ebp + 0xffffff7cu);
    edx = edi;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edx, 0x54021cu, 4, eax);
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_414617:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = esi + 0x4u;
    edi = edi + 0x14u;
    eax = eax + 0x14u;
    edx = edx + 0x14u;
    ecx = ecx + 0x14u;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_41453b;
    ebx = 0x50cdafu;
    edx = 0x4fcde8u;
    eax = (ebp + 0xfffffe78u);
    esi = 0x53c0ccu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_414675:
    ecx = 0x50cdc4u;
    ebx = 0x3cu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff7cu);
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edi = edi + 1u;
    esi = esi + 0xf0u;
    {
        (void)lift_sub(32, edi, 0x9u, &fl);
    }
    if (fl.cf)
        goto L_414675;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cdc5u;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    edi = 0x53c93cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4146d1:
    ecx = 0x50cdd5u;
    ebx = 0x72u;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff7cu);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    esi = esi + 1u;
    edi = edi + 0x1c8u;
    {
        (void)lift_sub(32, esi, 0x9u, &fl);
    }
    if (fl.cf)
        goto L_4146d1;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50cdd6u;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    edi = 0x53d998u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41472d:
    ecx = 0x50cde5u;
    ebx = 0x39u;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff7cu);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    esi = esi + 1u;
    edi = edi + 0xe4u;
    {
        (void)lift_sub(32, esi, 0x28u, &fl);
    }
    if (fl.cf)
        goto L_41472d;
    eax = (ebp + 0xffffff7cu);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
L_414764:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
L_414772:
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    ebx = (edi + 0x22bcu);
    esi = 0x28u;
    ebx = ebx + eax;
    ecx = 0x27u;
    ebx = ebx + 0x53d998u;
L_41478d:
    edx = 0x50cde6u;
    eax = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4147a9;
    ebx = ebx - 0xe4u;
    ecx = ecx - 1u;
    esi = esi - 1u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_41478d;
L_4147a9:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = edi + 0x4u;
    edx = (eax + 0xcu);
    lift_store(&env, eax, 0x53fd38u, 4, esi);
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    {
        (void)lift_sub(32, edi, 0x4cu, &fl);
    }
    if (!fl.zf)
        goto L_414772;
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ecx = ecx + edi;
    ebx = ebx + 0x4u;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0xcu, &fl);
    }
    if (!fl.zf)
        goto L_414764;
    ebx = 0x50cde7u;
    edx = 0x4fcde8u;
    eax = (ebp + 0xfffffe78u);
    edi = 0x53fe20u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_414803:
    ecx = 0x50cdf3u;
    ebx = 0x3u;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff7cu);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    esi = esi + 1u;
    edi = edi + 0xcu;
    {
        (void)lift_sub(32, esi, 0x28u, &fl);
    }
    if (fl.cf)
        goto L_414803;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi ^ edi;
L_414831:
    esi = 0x28u;
    ebx = (edi + 0x1d4u);
    ecx = 0x27u;
    ebx = ebx + 0x53fe20u;
L_414847:
    edx = 0x50cdf4u;
    eax = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_414860;
    ebx = ebx - 0xcu;
    ecx = ecx - 1u;
    esi = esi - 1u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_414847;
L_414860:
    edi = edi + 0x4u;
    lift_store(&env, edi, 0x53fffcu, 4, esi);
    {
        (void)lift_sub(32, edi, 0xcu, &fl);
    }
    if (!fl.zf)
        goto L_414831;
    ebx = 0x50cdf5u;
    edx = 0x4fcde8u;
    eax = (ebp + 0xfffffe78u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x13u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x532d3cu;
    eax = (ebp + 0xffffff7cu);
    ecx = lift_load(&env, 0u, 0x532d88u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50ce03u;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x13u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x532ca4u;
    eax = (ebp + 0xffffff7cu);
    ecx = lift_load(&env, 0u, 0x532d88u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50ce13u;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x13u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x532cf0u;
    eax = (ebp + 0xffffff7cu);
    ecx = lift_load(&env, 0u, 0x532d88u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    ebx = 0x50ce20u;
    edx = 0x4fcde8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ebx = 0x13u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x5347f0u;
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = (ebp + 0xffffff7cu);
    lift_store(&env, ebp, 0xffffffa0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489fa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    lift_store(&env, ebp, 0xffffffa0u, 4, edi);
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
L_4149ca:
    edx = 0x4fcde8u;
    eax = (ebp + 0xfffffe78u);
    ebx = lift_load(&env, esi, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe78u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_41436b;
    edx = (ebp + 0xfffffe78u);
    eax = (ebp + 0xffffff7cu);
    ecx = 0x50cd80u;
    ebx = 0x3cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff7cu);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x50cd81u;
    ebx = 0x3cu;
    edx = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a4a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = 0x3cu;
    edx = lift_load(&env, ebp, 0xffffffbcu, 4);
    eax = (ebp + 0xffffff7cu);
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x3u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = 0x3cu;
    edx = lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = (ebp + 0xffffff7cu);
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a560u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xffffff7cu);
    edx = lift_load(&env, ebp, 0xffffffacu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edx, 0x53969cu, 4, eax);
    eax = (ebp + 0xffffff7cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_41436b;
}

uint32_t lifted_f415580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F415580_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F415580_STACK, 0, entry);
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
    esp = esp - 0x344u;
    eax = (ebp + 0xffffffd8u);
    edx = 0x4ec1ecu;
    ecx = 0x513a14u;
    esi = 0x1u;
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
    eax = 0x50d395u;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4895e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x3cu;
    lift_store(&env, 0u, 0x532b3cu, 4, eax);
    eax = 0x50d3a2u;
    edx = 0x4fd310u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4895e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x532b38u, 4, ebx);
    lift_store(&env, 0u, 0x532b40u, 4, ebx);
    lift_store(&env, 0u, 0x532b44u, 4, ebx);
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x532b48u, 4, ebx);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    ebx = 0x3du;
    lift_store(&env, 0u, 0x532a34u, 1, ((eax >> 8) & 0xffu));
    eax = (ebp + 0xfffffed4u);
    lift_store(&env, 0u, 0x532b94u, 4, ebx);
    ebx = 0x50d3afu;
    lift_store(&env, 0u, 0x532b90u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffca8u);
    edx = (ebp + 0xfffffed4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4290c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffca8u);
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x429530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffca8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x429660u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, 0u, 0x532b4cu, 4, edx);
    edx = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, 0u, 0x532b54u, 4, edx);
    edx = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, 0u, 0x532b58u, 4, edx);
    edx = lift_load(&env, eax, 0xcu, 4);
    lift_store(&env, 0u, 0x532b5cu, 4, edx);
    edx = lift_load(&env, eax, 0x10u, 4);
    lift_store(&env, 0u, 0x532b60u, 4, edx);
    edx = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, 0u, 0x532b64u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x18u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x532b6cu, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x1au, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x532b6eu, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x1cu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x532b70u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x1eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x532b72u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x20u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x532b74u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x22u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x532b76u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x24u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x532b78u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x26u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x532b7au, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x28u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x532b7cu, 2, (edx & 0xffffu));
    edx = lift_load(&env, eax, 0x44u, 4);
    lift_store(&env, 0u, 0x532b80u, 4, edx);
    edx = lift_load(&env, eax, 0x48u, 4);
    lift_store(&env, 0u, 0x532b84u, 4, edx);
    edx = lift_load(&env, eax, 0x2cu, 4);
    lift_store(&env, 0u, 0x532b98u, 4, edx);
    edx = lift_load(&env, eax, 0x30u, 4);
    lift_store(&env, 0u, 0x532b9cu, 4, edx);
    edx = lift_load(&env, eax, 0x34u, 4);
    lift_store(&env, 0u, 0x532ba0u, 4, edx);
    edx = lift_load(&env, eax, 0x38u, 4);
    lift_store(&env, 0u, 0x532ba4u, 4, edx);
    edx = lift_load(&env, eax, 0x3cu, 4);
    lift_store(&env, 0u, 0x532ba8u, 4, edx);
    edx = lift_load(&env, eax, 0x40u, 4);
    lift_store(&env, 0u, 0x532bacu, 4, edx);
    edx = lift_load(&env, eax, 0x4cu, 4);
    ecx = ecx ^ ecx;
    lift_store(&env, 0u, 0x532b88u, 4, edx);
    edx = lift_load(&env, eax, 0x50u, 4);
    edi = eax;
    lift_store(&env, 0u, 0x532bb4u, 4, edx);
    edx = lift_load(&env, eax, 0x54u, 4);
    ebx = eax;
    lift_store(&env, 0u, 0x532bb8u, 4, edx);
L_41574b:
    ecx = ecx + 1u;
    eax = lift_load(&env, ebx, 0x58u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, 0u, (ecx * 4u) + 0x533290u, 4, eax);
    {
        (void)lift_sub(32, ecx, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_41574b;
    esi = (edi + 0x6cu);
    ebx = 0x5332a8u;
    ecx = esi;
    esi = esi + 0x14u;
L_41576b:
    edx = ecx;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx + 0x4u;
    ebx = ebx + 0x4u;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.zf)
        goto L_41576b;
    eax = lift_load(&env, 0u, 0x532b4cu, 4);
    lift_store(&env, 0u, 0x532b50u, 4, eax);
    eax = lift_load(&env, 0u, 0x532b64u, 4);
    lift_store(&env, 0u, 0x532b68u, 4, eax);
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x532bb0u, 4, eax);
    eax = lift_load(&env, edi, 0x80u, 4);
    lift_store(&env, 0u, 0x532bd4u, 4, eax);
    eax = lift_load(&env, edi, 0x84u, 4);
    lift_store(&env, 0u, 0x532bd8u, 4, eax);
    eax = lift_load(&env, edi, 0x88u, 4);
    edx = 0xau;
    lift_store(&env, 0u, 0x532bdcu, 4, eax);
    eax = lift_load(&env, edi, 0x8cu, 4);
    lift_store(&env, 0u, 0x532b34u, 4, edx);
    lift_store(&env, 0u, 0x532be0u, 4, eax);
    eax = lift_load(&env, edi, 0x90u, 4);
    edx = (edi + 0x94u);
    lift_store(&env, 0u, 0x532be4u, 4, eax);
    eax = 0x532be8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x532becu;
    edx = (edi + 0xf8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x532bf0u;
    edx = (edi + 0x15cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x532bf4u;
    edx = (edi + 0x1c0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532b3cu, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41582d;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532b38u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_415837;
L_41582d:
    lift_store(&env, 0u, 0x532b88u, 4, 0x1u);
L_415837:
    eax = (ebp + 0xfffffca8u);
    edi = edi ^ edi;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x429350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
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

uint32_t lifted_f418270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F418270_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F418270_STACK, 0, entry);
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
        uint32_t v = 0x540020u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = lift_load(&env, 0u, 0x540044u, 4);
    edx = edx + ebx;
    {
        uint32_t v = 0x540020u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x540044u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, eax, 0x4u, 4);
    edx = edx ^ edx;
    eax = lift_load(&env, eax, 0x1cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a040u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4189f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4189F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4189F0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x532a38u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x415580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x413bd0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f418a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F418A10_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F418A10_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xd8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_418acb;
L_418a20:
    eax = 0xau;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, edx, 0xd8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_418a38;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417c80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418a38:
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, edx, 0xd8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_418a50;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x425f40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418a50:
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, edx, 0xd8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_418a68;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b9050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418a68:
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, edx, 0xd8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_418a80;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x484550u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418a80:
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, edx, 0xd8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_418a98;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x480730u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418a98:
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, edx, 0xd8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_418ad5;
L_418aab:
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7c00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
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
L_418acb:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x475090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_418a20;
L_418ad5:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_418aab;
}

uint32_t lifted_f41a040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41A040_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41A040_STACK, 0, entry);
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
    edx = lift_load(&env, 0u, 0x54004cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4182c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (!fl.zf)
        goto L_41a061;
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41a061;
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
L_41a061:
    ebx = lift_load(&env, 0u, 0x540048u, 4);
    eax = ecx;
    lift_store(&env, 0u, 0x54004cu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a2b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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

uint32_t lifted_f41a080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41A080_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41A080_STACK, 0, entry);
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
    esi = eax;
    eax = (ebp + 0xffffffd0u);
    edx = 0x4ec1ecu;
    ecx = 0x513fc4u;
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
    eax = esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4189f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x484b30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_41a10f;
L_41a0c4:
    edx = edx ^ edx;
    eax = esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x532b4cu, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418ce0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_41a21b;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
L_41a0df:
    ecx = lift_load(&env, edx, 0x4f8128u, 4);
    {
        (void)lift_sub(32, ecx, lift_load(&env, 0u, 0x532b4cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_41a0ef;
    ebx = eax;
L_41a0ef:
    eax = eax + 1u;
    edx = edx + 0x4u;
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_41a0df;
    ebx = ebx - 1u;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_41a19c;
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x4f8128u, 4);
    lift_store(&env, 0u, 0x532b4cu, 4, eax);
    goto L_41a0c4;
L_41a10f:
    edx = 0x50d9f1u;
    eax = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = 0x1u;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a4cu, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    edx = 0x50da58u;
    eax = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a4cu, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    edx = 0x50dab9u;
    eax = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a4cu, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418870u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5327f0u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x411f50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe4u);
L_41a17e:
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
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
L_41a19c:
    edx = 0x50dafbu;
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = 0x3u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a4cu, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    edx = 0x50db62u;
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a4cu, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    edx = 0x50dbc3u;
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a4cu, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    eax = esi;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418870u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5327f0u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x411f50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe8u);
    goto L_41a17e;
L_41a21b:
    edx = 0x41a540u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
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

uint32_t lifted_f41a320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41A320_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41A320_STACK, 0, entry);
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
    esp = esp - 0x20cu;
    edi = eax;
    esi = edx;
    ebx = 0x5334a0u;
    ecx = ((edx * 4u));
    eax = (ebp + 0xfffffde4u);
    edx = 0x4fc4a0u;
    ebx = lift_load(&env, ecx, ebx + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx + 0x533578u;
    edx = 0x4fc4a0u;
    eax = (ebp + 0xfffffee8u);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c1eu, 1)) & 0xffu);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf)
        goto L_41a41c;
    edx = (ebp + 0xfffffee8u);
    eax = (ebp + 0xfffffde4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, edi, 0xccu, 4);
    ecx = lift_load(&env, edx, 0x8u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, edx, 0x4u, 4);
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
    ecx = ecx ^ ecx;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    esi = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47e200u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    edx = 0x5b9c60u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47e360u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4182c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, 0u, 0x540048u, 4);
    ebx = eax;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a2f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x280u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_41a3e4;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4413b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41a3e4:
    {
        uint32_t v = 0x50dc38u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xdu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x10u;
    edx = (ebp + 0xfffffde4u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x544070u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x441530u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = lift_load(&env, 0u, 0x544070u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x441b70u, eax, edx, ebx, ecx, 0, esp);
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
L_41a41c:
    edx = (ebp + 0xfffffde4u);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a960u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f41a540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41A540_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41A540_STACK, 0, entry);
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
    esp = esp - 0x208u;
    esi = eax;
    {
        uint32_t v = 0x540020u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = 0x1u;
    lift_store(&env, eax, 0xd4u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c30u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x5b9c50u;
    ecx = 0x17cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4856a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = (ebp + 0xfffffde8u);
    lift_store(&env, 0u, 0x540044u, 4, edx);
    lift_store(&env, 0u, 0x540048u, 4, ecx);
    ecx = ecx ^ ecx;
    lift_store(&env, 0u, 0x5bb710u, 4, ebx);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c38u, 1)) & 0xffu);
    ebx = 0x5334a0u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    edx = 0x4fc4a0u;
    ebx = lift_load(&env, ecx, ebx + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx + 0x533578u;
    edx = 0x4fc4a0u;
    eax = (ebp + 0xfffffeecu);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffeecu);
    eax = (ebp + 0xfffffde8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0xccu, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c39u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x5334a0u;
    edx = 0x4fc4a0u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffde8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffde8u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x441d60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c1bu, 1)) & 0xffu);
    lift_store(&env, esi, 0xd0u, 4, eax);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aa20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aaf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487020u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418a10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    edx = 0x41a680u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a940u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x41a520u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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

uint32_t lifted_f423ea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F423EA0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F423EA0_STACK, 0, entry);
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
    esp = esp - 0x208u;
    esi = eax;
    ecx = ecx ^ ecx;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_423eba;
    esi = 0x50dec5u;
L_423eba:
    edi = (ebp + 0xfffffde8u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_423ec1:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_423ed9;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_423ec1;
L_423ed9:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_423f1b;
    edi = (ebp + 0xfffffeecu);
    esi = edx;
L_423ee6:
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_423ee7:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_423eff;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_423ee7;
L_423eff:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    eax = (ebp + 0xfffffde8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_423f28;
L_423f10:
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
L_423f1b:
    esi = 0x50dec6u;
    edi = (ebp + 0xfffffeecu);
    goto L_423ee6;
L_423f28:
    eax = (ebp + 0xfffffde8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423d70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_423f10;
    esi = 0x1u;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_423f68;
L_423f44:
    {
        (void)lift_sub(32, esi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_423f10;
    eax = ecx;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478f10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4799f0u, eax, edx, ebx, ecx, 0, esp);
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
L_423f68:
    eax = (ebp + 0xfffffeecu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.zf)
        goto L_423f44;
    edx = 0x50def5u;
    eax = (ebp + 0xfffffeecu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489b40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.zf)
        goto L_423f44;
    edx = (ebp + 0xfffffeecu);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4797f0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f429530(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F429530_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F429530_STACK, 0, entry);
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
    esp = esp - 0x128u;
    ecx = eax;
    eax = (ebp + 0xffffffdcu);
    ebx = 0x4ec1ecu;
    esi = 0x514528u;
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
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    eax = edx;
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4895e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_429584;
L_429572:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_429584:
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4895b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_429572;
    eax = (ebp + 0xfffffec8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = (ebp + 0xfffffec8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4295cc;
    edx = (ebp + 0xfffffec8u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4293e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffec8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a8c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4295cc:
    eax = (ebp + 0xfffffec8u);
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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

uint32_t lifted_f42a200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F42A200_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F42A200_STACK, 0, entry);
L_429dc3:
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
    esp = esp - 0x14u;
    edi = eax;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe8u, 1, ((eax >> 8) & 0xffu));
L_42a212:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x1cu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_429dc3;
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
    eax = eax - edx - fl.cf;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    edx = ((eax * 4u));
    ecx = ecx - edx;
    edx = ecx;
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x278u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_42a265;
    ecx = 0x4u;
    ecx = ecx - edx;
    ecx = ecx - 1u;
L_42a24e:
    ebx = eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        ebx = r;
    }
    ebx = ebx + edi;
    esi = lift_load(&env, ebx, (edx * 4u) + 0x15cu, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_42a269;
    lift_store(&env, ebp, 0xffffffe8u, 1, lift_load(&env, ebp, 0xffffffe8u, 1) + 1u);
    goto L_42a212;
L_42a265:
    ecx = edx;
    goto L_42a24e;
L_42a269:
    edx = lift_load(&env, 0u, 0x4f9060u, 4);
    edx = edx + lift_load(&env, edi, 0x27cu, 4);
    {
        uint32_t r = lift_imul(32, ecx, edx, &fl);
        ecx = r;
    }
    edx = lift_load(&env, edi, 0xcu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx + ecx;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    ecx = lift_load(&env, edi, 0x280u, 4);
    edx = lift_load(&env, 0u, 0x4f9064u, 4);
    edx = edx + ecx;
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    edx = lift_load(&env, edi, 0x14u, 4);
    ebx = lift_load(&env, 0u, 0x4f9064u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx + eax;
    ecx = lift_load(&env, 0u, 0x4f9060u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    eax = esi;
    ebx = lift_load(&env, ebp, 0xffffffe2u, 4);
    edx = lift_load(&env, ebp, 0xffffffdeu, 4);
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
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = (ebp + 0xffffffdcu);
    edx = (ebp + 0xffffffd8u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_42a2f8;
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = lift_load(&env, 0u, 0x4f9060u, 4);
    eax = eax - edx;
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = ecx + eax;
    eax = lift_load(&env, 0u, 0x4f9064u, 4);
    eax = eax - ebx;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = edx + eax;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
L_42a2f8:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, esi, 0xeu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
    lift_store(&env, ebp, 0xffffffe8u, 1, lift_load(&env, ebp, 0xffffffe8u, 1) + 1u);
    goto L_42a212;
}

uint32_t lifted_player_mode_in_group_a(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PLAYER_MODE_IN_GROUP_A_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_PLAYER_MODE_IN_GROUP_A_STACK, 0,
               entry);
L_43bd74:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
    eax = lift_load(&env, eax, 0x4c8u, 4);
    {
        (void)lift_sub(32, eax, 0x25u, &fl);
    }
    if (fl.zf)
        goto L_43d3c9;
    {
        (void)lift_sub(32, eax, 0x26u, &fl);
    }
    if (fl.zf)
        goto L_43d3c9;
    {
        (void)lift_sub(32, eax, 0x27u, &fl);
    }
    if (!fl.zf)
        goto L_43bd74;
L_43d3c9:
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_player_mode_in_group_b(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PLAYER_MODE_IN_GROUP_B_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_PLAYER_MODE_IN_GROUP_B_STACK, 0,
               entry);
L_43bd74:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
    eax = lift_load(&env, eax, 0x4c8u, 4);
    {
        (void)lift_sub(32, eax, 0x32u, &fl);
    }
    if (fl.zf)
        goto L_43d3e9;
    {
        (void)lift_sub(32, eax, 0x33u, &fl);
    }
    if (fl.zf)
        goto L_43d3e9;
    {
        (void)lift_sub(32, eax, 0x34u, &fl);
    }
    if (!fl.zf)
        goto L_43bd74;
L_43d3e9:
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_font_measure(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_FONT_MEASURE_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_FONT_MEASURE_STACK, 1, entry);
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
    esp = esp - 0x38u;
    lift_store(&env, ebp, 0xfffffff0u, 1, (eax & 0xffu));
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    lift_store(&env, ebp, 0xfffffff4u, 1, (ebx & 0xffu));
    edi = ecx;
    eax = (ebp + 0xffffffc0u);
    edx = 0x4ec1ecu;
    ecx = 0x514f2cu;
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
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, edi, 0x0u, 4, ebx);
    edx = 0x50e12cu;
    lift_store(&env, eax, 0x0u, 4, ebx);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_440747;
L_440666:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4407f5;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_44080e;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_44069f;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
L_44069f:
    esi = eax;
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
    eax = esi;
    ecx = ecx ^ ecx;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    lift_store(&env, esi, 0x44u, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffedu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, 0x20cu, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x8eu, 1, 0x0u);
    lift_store(&env, esi, 0x8fu, 1, 0x1u);
    eax = eax + 0x541988u;
    lift_store(&env, esi, 0x91u, 1, 0x0u);
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esi, 0xf4u, 4, edx);
    ebx = (ebp + 0xffffffd8u);
    eax = lift_load(&env, eax, 0x4u, 4);
    edx = (ebp + 0xffffffd4u);
    lift_store(&env, esi, 0xf8u, 4, eax);
    eax = esi;
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_440723;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    ebx = lift_load(&env, edi, 0x0u, 4);
    ebx = ebx + eax;
    lift_store(&env, edi, 0x0u, 4, ebx);
    esi = (ebx + 0x1u);
    lift_store(&env, edi, 0x0u, 4, esi);
    edx = lift_load(&env, ebp, 0x8u, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x0u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_440723;
    lift_store(&env, edx, 0x0u, 4, eax);
L_440723:
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_44073a;
    ebx = lift_load(&env, ebx, 0x158u, 4);
    edx = 0x2u;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_44073a:
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffccu, 4, esi);
L_44073f:
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) + 1u);
    goto L_440666;
L_440747:
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_440807;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
L_440760:
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
    eax = esi;
    ecx = ecx ^ ecx;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = lift_load(&env, ebp, 0xffffffedu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x44u, 1, (eax & 0xffu));
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        eax = r;
    }
    eax = eax + edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax - edx;
    lift_store(&env, esi, 0x8eu, 1, 0x0u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x8fu, 1, 0x1u);
    eax = eax + 0x541988u;
    lift_store(&env, esi, 0x91u, 1, 0x0u);
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esi, 0xf4u, 4, edx);
    ebx = (ebp + 0xffffffd8u);
    eax = lift_load(&env, eax, 0x4u, 4);
    edx = (ebp + 0xffffffd4u);
    lift_store(&env, esi, 0xf8u, 4, eax);
    eax = esi;
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4407df;
    lift_store(&env, edi, 0x0u, 4, 0x0u);
    edx = lift_load(&env, ebp, 0x8u, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
L_4407df:
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4407f5;
    ebx = lift_load(&env, esi, 0x158u, 4);
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4407f5:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
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
L_440807:
    esi = ebx;
    goto L_440760;
L_44080e:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffedu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f420u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_44073f;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_44084a;
    ecx = 0x3u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
L_44084a:
    esi = eax;
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
    eax = esi;
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
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    lift_store(&env, esi, 0x8eu, 1, 0x0u);
    ebx = (ebp + 0xffffffd8u);
    lift_store(&env, esi, 0x8fu, 1, 0x1u);
    edx = (ebp + 0xffffffd4u);
    lift_store(&env, esi, 0x44u, 1, (eax & 0xffu));
    eax = esi;
    lift_store(&env, esi, 0x91u, 1, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4408ab;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    esi = lift_load(&env, edi, 0x0u, 4);
    esi = esi + eax;
    lift_store(&env, edi, 0x0u, 4, esi);
    eax = (esi + 0x1u);
    lift_store(&env, edi, 0x0u, 4, eax);
    edx = lift_load(&env, ebp, 0x8u, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x0u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4408ab;
    lift_store(&env, edx, 0x0u, 4, eax);
L_4408ab:
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_44073a;
    ebx = lift_load(&env, ebx, 0x158u, 4);
    edx = 0x2u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffccu, 4, esi);
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) + 1u);
    goto L_440666;
}

uint32_t lifted_text_layout(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_TEXT_LAYOUT_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_TEXT_LAYOUT_STACK, 4, entry);
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
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, esi, 0x0u, 2, 0x0u);
    lift_store(&env, edx, 0x0u, 2, 0x0u);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, esp, 0xcu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4409f0;
L_4409ab:
    eax = lift_load(&env, esp, 0x14u, 4);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, esp, 0x18u, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4409dd;
    eax = lift_load(&env, esp, 0x16u, 4);
    edx = lift_load(&env, esp, 0x12u, 4);
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
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ecx & 0xffffu);
    eax = eax + 1u;
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
    lift_store(&env, edi, 0x0u, 2, (eax & 0xffffu));
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4409eb;
L_4409dd:
    eax = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, esi, 0x0u, 2, lift_load(&env, esi, 0x0u, 2) + (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t r = lift_add(16, lift_load(&env, edi, 0x0u, 2), (eax & 0xffffu), &fl);
        lift_store(&env, edi, 0x0u, 2, r);
    }
L_4409eb:
    {
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
L_4409f0:
    edx = lift_load(&env, esp, 0xau, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = eax - edx;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    eax = eax + 1u;
    eax = eax - edx;
    eax = eax + 1u;
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
    lift_store(&env, esi, 0x0u, 2, (eax & 0xffffu));
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4409eb;
    goto L_4409ab;
}

uint32_t lifted_object_corner_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_CORNER_CALL_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_CORNER_CALL_STACK, 4, entry);
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
    edi = eax;
    eax = (ebp + 0xffffffd0u);
    esi = 0x4ec1ecu;
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
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ecx & 0xffffu);
    eax = 0x514f58u;
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = (ebp + 0xfffffff0u);
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xfffffff4u);
    esi = esi ^ esi;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe8u);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe4u);
    esi = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x44u, 1)) & 0xffu);
    esi = lift_load(&env, ebp, 0x10u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xau, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0x6u, 4);
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)(edx & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    eax = lift_load(&env, ebp, 0x14u, 4);
    edx = lift_load(&env, ebp, 0x10u, 4);
    ecx = lift_load(&env, ebp, 0xffffffeeu, 4);
    ebx = lift_load(&env, ebp, 0xfffffff2u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = edi;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x440a20u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
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
}

uint32_t lifted_f441b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F441B70_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F441B70_STACK, 0, entry);
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
    esp = esp - 0x128u;
    ecx = eax;
    eax = (ebp + 0xffffffdcu);
    ebx = 0x4ec1ecu;
    esi = 0x51506cu;
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
    eax = (ebp + 0xfffffec8u);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x1u);
    lift_store(&env, ecx, 0x268u, 4, edi);
    lift_store(&env, ecx, 0x274u, 4, edi);
    lift_store(&env, ecx, 0x278u, 4, edi);
    lift_store(&env, ecx, 0x270u, 4, edi);
    lift_store(&env, ecx, 0x26cu, 4, edi);
    lift_store(&env, ecx, 0x268u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_441d29;
    ebx = (ecx + 0x104u);
    edx = 0x50e13du;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_441c18;
    eax = ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4816f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    lift_store(&env, ecx, 0x274u, 4, eax);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4816f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x278u, 4, eax);
L_441c18:
    eax = lift_load(&env, ecx, 0x268u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ecx, 0x208u, 4, eax);
    eax = lift_load(&env, ecx, 0x268u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ecx, 0x20cu, 4, eax);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x208u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x544070u, 4, ecx);
    eax = eax - edx;
    lift_store(&env, ecx, 0x220u, 1, 0x0u);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    lift_store(&env, ecx, 0x222u, 1, 0x0u);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_441d46;
L_441c65:
    lift_store(&env, ecx, 0x210u, 2, (eax & 0xffffu));
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x20cu, 2)) & 0xffffu);
    eax = eax - ebx;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_441d4d;
L_441c87:
    lift_store(&env, ecx, 0x214u, 2, 0x0u);
    lift_store(&env, ecx, 0x212u, 2, (eax & 0xffffu));
    edx = edx ^ edx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x208u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    lift_store(&env, ecx, 0x216u, 2, 0x0u);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_441cb9;
    eax = edx;
L_441cb9:
    lift_store(&env, ecx, 0x218u, 2, (eax & 0xffffu));
    ebx = ebx ^ ebx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x20cu, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_441cd9;
    eax = ebx;
L_441cd9:
    lift_store(&env, ecx, 0x21cu, 2, 0x1u);
    lift_store(&env, ecx, 0x21eu, 2, 0x1u);
    lift_store(&env, ecx, 0x226u, 2, 0x0u);
    lift_store(&env, ecx, 0x228u, 1, 0x0u);
    edx = edx ^ edx;
    lift_store(&env, ecx, 0x21au, 2, (eax & 0xffffu));
    ecx = ecx ^ ecx;
    eax = (ebp + 0xfffffec8u);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_441d29:
    eax = (ebp + 0xfffffec8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_441d46:
    eax = eax ^ eax;
    goto L_441c65;
L_441d4d:
    eax = eax ^ eax;
    goto L_441c87;
}

uint32_t lifted_f441d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F441D60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F441D60_STACK, 0, entry);
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
    esp = esp - 0x18u;
    esi = eax;
    eax = (ebp + 0xffffffd4u);
    edx = 0x4ec1ecu;
    ecx = 0x515078u;
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
    eax = (ebp + 0xffffffe8u);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, 0x1u);
    eax = (ebp + 0xffffffe8u);
    ecx = ecx ^ ecx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489640u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = 0x50e13eu;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x50e143u;
    ecx = eax;
    ebx = eax;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_441e11;
L_441dd7:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_441e18;
    edx = 0x5b9c60u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x474490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_441de8:
    edi = eax;
L_441dea:
    eax = (ebp + 0xffffffe8u);
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    env.chain = eax;
    eax = edi;
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
L_441e11:
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_441dd7;
    goto L_441dea;
L_441e18:
    edx = 0x5b9c60u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48ad00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_441de8;
}

uint32_t lifted_f45dca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F45DCA0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F45DCA0_STACK, 0, entry);
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
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x104u;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c4eu, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x5449c4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c4fu, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x5449e0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x53bd09u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x4fc188u;
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x5449fcu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5449fcu;
    ebx = lift_load(&env, 0u, 0x5466c4u, 4);
    edx = lift_load(&env, 0u, 0x4fbf28u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487790u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5449fcu;
    edx = lift_load(&env, 0u, 0x4fbf28u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4877d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5449fcu;
    ebx = lift_load(&env, 0u, 0x4fbf48u, 4);
    edx = lift_load(&env, 0u, 0x4fbf4cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487790u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5449fcu;
    edx = lift_load(&env, 0u, 0x4fbf4cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4877d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5449fcu;
    ebx = lift_load(&env, 0u, 0x4fbf50u, 4);
    edx = lift_load(&env, 0u, 0x4fbf54u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487790u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5449fcu;
    edx = lift_load(&env, 0u, 0x4fbf54u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4877d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5449fcu;
    ebx = lift_load(&env, 0u, 0x4fbf94u, 4);
    edx = lift_load(&env, 0u, 0x4fbf98u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487790u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5449fcu;
    edx = lift_load(&env, 0u, 0x4fbf98u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4877d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5449fcu;
    ebx = lift_load(&env, 0u, 0x4fbf84u, 4);
    edx = lift_load(&env, 0u, 0x4fbf88u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487790u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5449fcu;
    edx = lift_load(&env, 0u, 0x4fbf88u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4877d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c4du, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x544a18u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c51u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x544c10u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c53u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x4fc188u;
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x544c48u;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c52u, 1)) & 0xffu);
    eax = 0x1u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    edx = 0x4fc188u;
    ebx = ebx + 0x533650u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffef4u);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x544c2cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c54u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x544c64u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c55u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x544d0cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c56u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x4fc188u;
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x544c80u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c57u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x544c9cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c58u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x544cb8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c59u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x544cd4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c5au, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x4fc188u;
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x544cf0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    ebx = 0x533650u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c5bu, 1)) & 0xffu);
    edx = 0x4fc188u;
    ebx = lift_load(&env, ebx, (eax * 4u) + 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x546500u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c5cu, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x54651cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c5du, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x546538u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45ec00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e400u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c50u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45eac0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e3c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    ebx = ebx + 0x533650u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebx, 0x0u, 4);
    edx = 0x4fc188u;
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x546650u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    ebx = 0x533650u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c5eu, 1)) & 0xffu);
    edx = 0x4fc188u;
    ebx = lift_load(&env, ebx, (eax * 4u) + 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x54666cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c5fu, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffef4u);
    eax = 0x546688u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = (ebp + 0xfffffff8u);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4726d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4726D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4726D0_STACK, 0, entry);
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
    esp = esp - 0x134u;
    esi = lift_load(&env, 0u, 0x540f8cu, 4);
    eax = lift_load(&env, esi, 0x3b8u, 4);
    ebx = lift_load(&env, 0u, 0x540f90u, 4);
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    eax = lift_load(&env, ebx, 0x3b8u, 4);
    edx = lift_load(&env, esi, 0x178u, 4);
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_472714;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532bc4u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4728ef;
L_472714:
    lift_store(&env, ebp, 0xffffffc8u, 4, 0x3u);
L_47271b:
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_472720:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
L_47272b:
    eax = lift_load(&env, esi, 0x488u, 4);
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
    eax = eax ^ eax;
    edx = edx ^ edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff98u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((ecx & 0xffu)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4178d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4728f7;
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffc8u, 4), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4728f7;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, ebp + 0xfffffeb8u, 4, 0x1u);
L_472762:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = ecx + 1u;
    edi = edi + 1u;
    eax = eax + 0x4u;
    edx = edx + 0x4u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    {
        (void)lift_sub(32, edi, 0x4u, &fl);
    }
    if (fl.cf)
        goto L_47272b;
    edi = lift_load(&env, ebp, 0xffffffc0u, 4);
    edi = edi + 0x10u;
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x70u, &fl);
    }
    if (!fl.zf)
        goto L_472720;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x4c4u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_472908;
L_472797:
    eax = 0x10u;
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
L_4727a1:
    ecx = edi;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        ecx = r;
    }
L_4727a9:
    ecx = ecx + 0x4u;
    edx = edx ^ edx;
    lift_store(&env, ecx, ebp + 0xfffffeb4u, 4, edx);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (!fl.zf)
        goto L_4727a9;
    ecx = lift_load(&env, ebp, 0xffffffacu, 4);
    ecx = ecx + 0x10u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffacu, 4, ecx);
    {
        (void)lift_sub(32, edi, 0x7u, &fl);
    }
    if (fl.cf)
        goto L_4727a1;
L_4727c8:
    edi = lift_load(&env, ebx, 0x178u, 4);
    {
        (void)lift_sub(32, edi, 0x3u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4729cc;
L_4727d7:
    lift_store(&env, ebp, 0xffffffc4u, 4, 0x3u);
L_4727de:
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffbcu, 4, ecx);
L_4727e3:
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
L_4727ee:
    eax = lift_load(&env, ebx, 0x488u, 4);
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
    eax = eax ^ eax;
    edx = edx ^ edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff98u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((ecx & 0xffu)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4178d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4729e1;
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffc4u, 4), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4729e1;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, eax, ebp + 0xffffff28u, 4, 0x1u);
L_472825:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = ecx + 1u;
    edi = edi + 1u;
    eax = eax + 0x4u;
    edx = edx + 0x4u;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    {
        (void)lift_sub(32, edi, 0x4u, &fl);
    }
    if (fl.cf)
        goto L_4727ee;
    edi = lift_load(&env, ebp, 0xffffffbcu, 4);
    edi = edi + 0x10u;
    lift_store(&env, ebp, 0xffffffbcu, 4, edi);
    {
        (void)lift_sub(32, edi, 0x70u, &fl);
    }
    if (!fl.zf)
        goto L_4727e3;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x4c4u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4729f2;
L_47285a:
    eax = 0x10u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
L_472864:
    ecx = edx;
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        ecx = r;
    }
L_47286c:
    ecx = ecx + 0x4u;
    edi = edi ^ edi;
    lift_store(&env, ecx, ebp + 0xffffff24u, 4, edi);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (!fl.zf)
        goto L_47286c;
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = eax + 0x10u;
    edx = edx + 1u;
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    {
        (void)lift_sub(32, edx, 0x7u, &fl);
    }
    if (fl.cf)
        goto L_472864;
L_47288b:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d3b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_472ab6;
L_47289b:
    esi = 0x10u;
    ebx = ebx ^ ebx;
    edi = edi ^ edi;
L_4728a4:
    ecx = ebx;
    edx = esi;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        ecx = r;
    }
L_4728ab:
    ecx = ecx + 0x4u;
    lift_store(&env, ecx, ebp + 0xffffff24u, 4, edi);
    lift_store(&env, ecx, ebp + 0xfffffeb4u, 4, edi);
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4728ab;
    ebx = ebx + 1u;
    esi = esi + 0x10u;
    {
        (void)lift_sub(32, ebx, 0x7u, &fl);
    }
    if (fl.cf)
        goto L_4728a4;
L_4728c9:
    edx = (ebp + 0xfffffeb8u);
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x429df0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffff28u);
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x429df0u, eax, edx, ebx, ecx, 0, esp);
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
L_4728ef:
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    goto L_47271b;
L_4728f7:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = edx ^ edx;
    lift_store(&env, eax, ebp + 0xfffffeb8u, 4, edx);
    goto L_472762;
L_472908:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x4c5u, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_472797;
    ecx = ecx ^ ecx;
    edi = 0x10u;
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffa8u, 4, edi);
L_472923:
    edi = lift_load(&env, ebp, 0xffffffb4u, 4);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
L_47292f:
    eax = lift_load(&env, esi, 0x488u, 4);
    {
        uint32_t r = lift_imul(32, eax, 0x1cu, &fl);
        eax = r;
    }
    edx = (eax + ecx);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x4f9320u, 1)) & 0xffu);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, edx, 0x4f9538u, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_47297a;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_47297a;
    eax = eax & 0xffu;
    eax = eax - 1u;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x4c4u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4729a0;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x4f9750u, 1)) & 0xffu);
L_47296d:
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_47297a;
    edx = edx ^ edx;
    lift_store(&env, edi, ebp + 0xfffffeb8u, 4, edx);
L_47297a:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    edi = edi + 0x4u;
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf)
        goto L_47292f;
    edx = lift_load(&env, ebp, 0xffffffa8u, 4);
    edi = lift_load(&env, ebp, 0xffffffb4u, 4);
    edx = edx + 0x10u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffa8u, 4, edx);
    lift_store(&env, ebp, 0xffffffb4u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x7u, &fl);
    }
    if (!fl.cf)
        goto L_4727c8;
    goto L_472923;
L_4729a0:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x4c5u, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4729b5;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x4f9788u, 1)) & 0xffu);
    goto L_47296d;
L_4729b5:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d3d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47296d;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x4f97c0u, 1)) & 0xffu);
    goto L_47296d;
L_4729cc:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532bc4u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4727d7;
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    goto L_4727de;
L_4729e1:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = edx ^ edx;
    lift_store(&env, eax, ebp + 0xffffff28u, 4, edx);
    goto L_472825;
L_4729f2:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x4c5u, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_47285a;
    ecx = ecx ^ ecx;
    edi = 0x10u;
    lift_store(&env, ebp, 0xffffffb8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffb0u, 4, edi);
L_472a0d:
    edi = lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
L_472a19:
    eax = lift_load(&env, ebx, 0x488u, 4);
    {
        uint32_t r = lift_imul(32, eax, 0x1cu, &fl);
        eax = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x4f9320u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x4f9538u, 1)) & 0xffu);
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_472a64;
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_472a64;
    edx = edx & 0xffu;
    edx = edx - 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x4c4u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_472a8a;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x4f9750u, 1)) & 0xffu);
L_472a57:
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_472a64;
    edx = edx ^ edx;
    lift_store(&env, edi, ebp + 0xffffff28u, 4, edx);
L_472a64:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    edi = edi + 0x4u;
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf)
        goto L_472a19;
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    edi = lift_load(&env, ebp, 0xffffffb8u, 4);
    edx = edx + 0x10u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffb0u, 4, edx);
    lift_store(&env, ebp, 0xffffffb8u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x7u, &fl);
    }
    if (!fl.cf)
        goto L_47288b;
    goto L_472a0d;
L_472a8a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x4c5u, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_472a9f;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x4f9788u, 1)) & 0xffu);
    goto L_472a57;
L_472a9f:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d3d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_472a57;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x4f97c0u, 1)) & 0xffu);
    goto L_472a57;
L_472ab6:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d3b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_47289b;
    goto L_4728c9;
}

uint32_t lifted_palette_rgb(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PALETTE_RGB_STACK + 4 + 4 * 2 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_PALETTE_RGB_STACK, 2, entry);
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
    edi = edx;
    esi = ebx;
    ebp = ecx;
    ebx = 0x10101010u;
    eax = eax & 0xffffu;
    ecx = 0x3f701010u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6775u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546840u, 4, eax);
    eax = eax ^ eax;
    ebx = 0x10101010u;
    eax = (eax & 0xffff0000u) | (((edi & 0xffffu)) & 0xffffu);
    ecx = 0x3f701010u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6775u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546844u, 4, eax);
    eax = eax ^ eax;
    ebx = 0x10101010u;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3f701010u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6775u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x546844u, 4);
    lift_store(&env, 0u, 0x546848u, 4, eax);
    eax = lift_load(&env, 0u, 0x546840u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.zf || fl.sf != fl.of)
        goto L_474760;
    esi = lift_load(&env, 0u, 0x546840u, 4);
L_4745ee:
    edx = lift_load(&env, 0u, 0x546848u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.zf || fl.sf != fl.of)
        goto L_47476b;
L_474601:
    eax = lift_load(&env, 0u, 0x546840u, 4);
    edx = lift_load(&env, 0u, 0x546844u, 4);
    lift_store(&env, 0u, 0x54685cu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_474776;
    esi = lift_load(&env, 0u, 0x546840u, 4);
L_474623:
    edx = lift_load(&env, 0u, 0x546848u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_474781;
    edx = esi;
L_474638:
    eax = lift_load(&env, 0u, 0x54685cu, 4);
    lift_store(&env, 0u, 0x546858u, 4, edx);
    lift_store(&env, 0u, 0x546854u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47478c;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x54685cu, 4);
    esi = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d81feu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546850u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_474796;
L_47466f:
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x54684cu, 4, edx);
    lift_store(&env, 0u, 0x54686cu, 4, edx);
L_47467d:
    ecx = 0x40590000u;
    eax = lift_load(&env, 0u, 0x546850u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x40590000u;
    lift_store(&env, 0u, 0x546850u, 4, eax);
    eax = lift_load(&env, 0u, 0x546854u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546854u, 4, eax);
    eax = lift_load(&env, 0u, 0x54684cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0x0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x546850u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546850u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546864u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb57cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_4748e6;
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, eax, 0x0u, 2, (esi & 0xffffu));
L_474710:
    eax = lift_load(&env, 0u, 0x546854u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546854u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546868u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb57cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_4748f8;
    eax = lift_load(&env, esp, 0x14u, 4);
    lift_store(&env, eax, 0x0u, 2, (esi & 0xffffu));
    eax = lift_load(&env, 0u, 0x54686cu, 4);
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
L_474760:
    esi = lift_load(&env, 0u, 0x546844u, 4);
    goto L_4745ee;
L_47476b:
    esi = lift_load(&env, 0u, 0x546848u, 4);
    goto L_474601;
L_474776:
    esi = lift_load(&env, 0u, 0x546844u, 4);
    goto L_474623;
L_474781:
    edx = lift_load(&env, 0u, 0x546848u, 4);
    goto L_474638;
L_47478c:
    lift_store(&env, 0u, 0x546850u, 4, eax);
    goto L_47466f;
L_474796:
    eax = 0x1u;
    edx = lift_load(&env, 0u, 0x54685cu, 4);
    lift_store(&env, 0u, 0x54686cu, 4, eax);
    eax = lift_load(&env, 0u, 0x546840u, 4);
    lift_store(&env, 0u, 0x546860u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.zf)
        goto L_474860;
    eax = lift_load(&env, 0u, 0x546844u, 4);
    edx = lift_load(&env, 0u, 0x54685cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.zf)
        goto L_47489f;
    eax = lift_load(&env, 0u, 0x546848u, 4);
    edx = lift_load(&env, 0u, 0x54685cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (!fl.zf)
        goto L_474835;
    eax = lift_load(&env, 0u, 0x546840u, 4);
    edx = lift_load(&env, 0u, 0x546844u, 4);
    ecx = 0x404e0000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    eax = esi;
    edi = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    ecx = edx;
    eax = ebx;
    edx = edi;
    ebx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x406e0000u;
L_474824:
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_47482b:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54684cu, 4, eax);
L_474835:
    eax = lift_load(&env, 0u, 0x54684cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_47467d;
    edx = 0x43b40000u;
    eax = lift_load(&env, 0u, 0x54684cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d80a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54684cu, 4, eax);
    goto L_47467d;
L_474860:
    eax = lift_load(&env, 0u, 0x546844u, 4);
    edx = lift_load(&env, 0u, 0x546848u, 4);
    ecx = 0x404e0000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = esi;
    ebx = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edi = edx;
    eax = ecx;
    edx = ebx;
    ebx = esi;
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_47482b;
L_47489f:
    eax = lift_load(&env, 0u, 0x546848u, 4);
    edx = lift_load(&env, 0u, 0x546840u, 4);
    ecx = 0x404e0000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = esi;
    ebx = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edi = edx;
    eax = ecx;
    edx = ebx;
    ebx = esi;
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x405e0000u;
    goto L_474824;
L_4748e6:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    edx = lift_load(&env, esp, 0x10u, 4);
    eax = eax + 1u;
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    goto L_474710;
L_4748f8:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    edx = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x54686cu, 4);
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

uint32_t lifted_palette_color(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PALETTE_COLOR_STACK + 4 + 4 * 2 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_PALETTE_COLOR_STACK, 2, entry);
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
    edi = ecx;
    eax = eax & 0xffffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54687cu, 4, eax);
    eax = eax ^ eax;
    ebx = 0x47ae147bu;
    eax = (eax & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    ecx = 0x3f847ae1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6775u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546880u, 4, eax);
    eax = eax ^ eax;
    ebx = 0x47ae147bu;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3f847ae1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6775u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x546880u, 4);
    lift_store(&env, 0u, 0x546884u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_474bc5;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x54687cu, 4), 0x43b40000u, &fl);
    }
    if (!fl.zf)
        goto L_47498d;
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x54687cu, 4, ebx);
L_47498d:
    ebx = 0x11111111u;
    eax = lift_load(&env, 0u, 0x54687cu, 4);
    ecx = 0x3f911111u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54687cu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54689cu, 2, (eax & 0xffffu));
    eax = eax & 0xffffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x54687cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546888u, 4, eax);
    eax = lift_load(&env, 0u, 0x546884u, 4);
    edx = lift_load(&env, 0u, 0x546880u, 4);
    lift_store(&env, 0u, 0x54688cu, 4, eax);
    eax = 0x3f800000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546884u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x546888u, 4);
    lift_store(&env, 0u, 0x546898u, 4, eax);
    eax = 0x3f800000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546880u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x3f800000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546884u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x546888u, 4);
    lift_store(&env, 0u, 0x546890u, 4, eax);
    eax = lift_load(&env, 0u, 0x546880u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x3f800000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546884u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x54689cu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x546894u, 4, eax);
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_474bd9;
    eax = lift_load(&env, 0u, 0x54688cu, 4);
    lift_store(&env, 0u, 0x546870u, 4, eax);
    eax = lift_load(&env, 0u, 0x546890u, 4);
    lift_store(&env, 0u, 0x546874u, 4, eax);
    eax = lift_load(&env, 0u, 0x546898u, 4);
L_474a90:
    lift_store(&env, 0u, 0x546878u, 4, eax);
L_474a95:
    ecx = 0x406fe000u;
    eax = lift_load(&env, 0u, 0x546870u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x406fe000u;
    lift_store(&env, 0u, 0x546870u, 4, eax);
    eax = lift_load(&env, 0u, 0x546874u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x406fe000u;
    lift_store(&env, 0u, 0x546874u, 4, eax);
    eax = lift_load(&env, 0u, 0x546878u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546878u, 4, eax);
    eax = lift_load(&env, 0u, 0x546870u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546870u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5468a0u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb57cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_474c9c;
    lift_store(&env, edi, 0x0u, 2, (esi & 0xffffu));
L_474b36:
    eax = lift_load(&env, 0u, 0x546874u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546874u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5468a4u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb57cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_474caa;
    eax = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, eax, 0x0u, 2, (esi & 0xffffu));
L_474b7b:
    eax = lift_load(&env, 0u, 0x546878u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546878u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5468a8u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb57cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_474cbc;
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, eax, 0x0u, 2, (esi & 0xffffu));
    {
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
L_474bc5:
    lift_store(&env, 0u, 0x546878u, 4, eax);
    lift_store(&env, 0u, 0x546874u, 4, eax);
    lift_store(&env, 0u, 0x546870u, 4, eax);
    goto L_474a95;
L_474bd9:
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_474bfa;
    edx = lift_load(&env, 0u, 0x54688cu, 4);
    lift_store(&env, 0u, 0x546870u, 4, eax);
    eax = lift_load(&env, 0u, 0x546898u, 4);
    lift_store(&env, 0u, 0x546874u, 4, edx);
    goto L_474a90;
L_474bfa:
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_474c23;
    eax = lift_load(&env, 0u, 0x54688cu, 4);
    lift_store(&env, 0u, 0x546874u, 4, eax);
    eax = lift_load(&env, 0u, 0x546890u, 4);
    lift_store(&env, 0u, 0x546878u, 4, eax);
    eax = lift_load(&env, 0u, 0x546898u, 4);
    lift_store(&env, 0u, 0x546870u, 4, eax);
    goto L_474a95;
L_474c23:
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_474c49;
    edx = lift_load(&env, 0u, 0x54688cu, 4);
    lift_store(&env, 0u, 0x546874u, 4, eax);
    eax = lift_load(&env, 0u, 0x546898u, 4);
    lift_store(&env, 0u, 0x546878u, 4, edx);
    lift_store(&env, 0u, 0x546870u, 4, eax);
    goto L_474a95;
L_474c49:
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_474c72;
    eax = lift_load(&env, 0u, 0x54688cu, 4);
    lift_store(&env, 0u, 0x546878u, 4, eax);
    eax = lift_load(&env, 0u, 0x546890u, 4);
    lift_store(&env, 0u, 0x546870u, 4, eax);
    eax = lift_load(&env, 0u, 0x546898u, 4);
    lift_store(&env, 0u, 0x546874u, 4, eax);
    goto L_474a95;
L_474c72:
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_474a95;
    edx = lift_load(&env, 0u, 0x54688cu, 4);
    lift_store(&env, 0u, 0x546878u, 4, eax);
    eax = lift_load(&env, 0u, 0x546898u, 4);
    lift_store(&env, 0u, 0x546870u, 4, edx);
    lift_store(&env, 0u, 0x546874u, 4, eax);
    goto L_474a95;
L_474c9c:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    eax = eax + 1u;
    lift_store(&env, edi, 0x0u, 2, (eax & 0xffffu));
    goto L_474b36;
L_474caa:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    edx = lift_load(&env, esp, 0xcu, 4);
    eax = eax + 1u;
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    goto L_474b7b;
L_474cbc:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    edx = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    {
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

uint32_t lifted_palette_channels(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PALETTE_CHANNELS_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_PALETTE_CHANNELS_STACK, 0, entry);
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
    esp = esp - 0x30u;
    eax = (ebp + 0xffffffbcu);
    edx = 0x4ec1ecu;
    ecx = 0x516410u;
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
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    lift_store(&env, ebp, 0xffffffc4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffc8u, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((0xffu) & 0xffu);
L_474d06:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((edi & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, eax, 0xc9u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_474d33;
    esi = esi ^ esi;
L_474d14:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, eax, 0x65u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_474d30;
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | (((edi & 0xffffu)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, ecx, 0x65u, &fl);
        ecx = r;
    }
    esi = esi + 1u;
    lift_store(&env, ecx, eax + 0x5468b0u, 1, (ebx & 0xffu));
    goto L_474d14;
L_474d30:
    edi = edi + 1u;
    goto L_474d06;
L_474d33:
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
L_474d38:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe4u, 2)) & 0xffffu);
    {
        (void)lift_sub(32, eax, 0x65u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_474d87;
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
L_474d48:
    esi = esi ^ esi;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffdcu, 2)) & 0xffffu);
    {
        (void)lift_sub(32, esi, 0x65u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_474d82;
    edi = edi ^ edi;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe4u, 2)) & 0xffffu);
    ebx = edi;
    {
        uint32_t r = lift_imul(32, edi, 0x65u, &fl);
        edi = r;
    }
    eax = (ebp + 0xffffffe0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe8u);
    ecx = (ebp + 0xffffffd8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = esi;
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x474910u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    lift_store(&env, edi, esi + 0x5468b0u, 1, (eax & 0xffu));
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    goto L_474d48;
L_474d82:
    lift_store(&env, ebp, 0xffffffe4u, 4, lift_load(&env, ebp, 0xffffffe4u, 4) + 1u);
    goto L_474d38;
L_474d87:
    edx = edx ^ edx;
L_474d89:
    edi = edi ^ edi;
    edi = (edi & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, edi, 0x65u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_474dc5;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edi, 0x549024u, 1)) & 0xffu);
    edi = edi ^ edx;
L_474d9b:
    ecx = 0x65u;
    eax = eax ^ eax;
    esi = esi ^ esi;
    eax = (eax & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    esi = (esi & 0xffff0000u) | (((edi & 0xffffu)) & 0xffffu);
    ecx = ecx - eax;
    {
        (void)lift_sub(32, esi, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_474dc2;
    ecx = (esi + 0x64u);
    {
        uint32_t r = lift_imul(32, ecx, 0x65u, &fl);
        ecx = r;
    }
    eax = eax + esi;
    edi = edi + 1u;
    lift_store(&env, ecx, eax + 0x5468b0u, 1, (ebx & 0xffu));
    goto L_474d9b;
L_474dc2:
    edx = edx + 1u;
    goto L_474d89;
L_474dc5:
    edi = edi ^ edx;
L_474dc7:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((edi & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, eax, 0x2fdu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_474ddf;
    esi = esi ^ esi;
    edi = edi + 1u;
    lift_store(&env, 0u, (eax * 4u) + 0x54c1d4u, 4, esi);
    goto L_474dc7;
L_474ddf:
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
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

uint32_t lifted_palette_tables_build(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PALETTE_TABLES_BUILD_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_PALETTE_TABLES_BUILD_STACK, 0, entry);
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
    esp = esp - 0x19cu;
    eax = (ebp + 0xffffff64u);
    edx = 0x4ec1ecu;
    ecx = 0x516430u;
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
    eax = 0x40000u;
    lift_store(&env, ebp, 0xffffff68u, 4, edx);
    lift_store(&env, ebp, 0xffffff6cu, 4, ecx);
    lift_store(&env, ebp, 0xffffff70u, 4, ebx);
    edx = 0x4u;
    lift_store(&env, ebp, 0xffffff9cu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    lift_store(&env, 0u, 0x54b800u, 4, eax);
    eax = 0x40000u;
    lift_store(&env, ebp, 0xffffff98u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54b804u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x474cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_475104:
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0xcu, &fl);
        eax = r;
    }
    eax = eax & 0xffu;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    lift_store(&env, ebp, 0xffffffbcu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x3fu) & 0xffu);
    eax = eax & 0xffu;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    lift_store(&env, ebp, 0xffffffb8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff9cu, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x3fu) & 0xffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    ecx = (ebp + 0xffffffa4u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd0u, 2, (eax & 0xffffu));
    eax = (ebp + 0xffffffb0u);
    edx = edx ^ edx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffacu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffc0u, 2)) & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffc8u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffb4u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x474560u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4754b1;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffa4u, 2, (edx & 0xffffu));
L_475172:
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe0u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, ebp, 0xffffffe8u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, ebp, 0xffffffdcu, 1, ((eax >> 8) & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffb0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, 0x65u, &fl);
        eax = r;
    }
    esi = 0x100u;
    ecx = 0x5468b0u;
    edi = esi;
    ecx = ecx + eax;
    eax = eax ^ eax;
    ebx = esi;
    lift_store(&env, ebp, 0xffffff7cu, 4, eax);
L_4751a4:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffff88u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffbau, 4);
    edx = lift_load(&env, ebp, 0xffffff88u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;
    eax = eax ^ edx;
    eax = eax - edx;
    {
        (void)lift_sub(16, (eax & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4751cb;
    esi = eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe0u, 1, (eax & 0xffu));
L_4751cb:
    edx = lift_load(&env, ebp, 0xffffffb6u, 4);
    eax = eax ^ eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    edx = edx - eax;
    eax = edx;
    edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;
    eax = eax ^ edx;
    eax = eax - edx;
    {
        (void)lift_sub(16, (eax & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4751ee;
    edi = eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 1, (eax & 0xffu));
L_4751ee:
    edx = lift_load(&env, ebp, 0xffffffceu, 4);
    eax = eax ^ eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    edx = edx - eax;
    eax = edx;
    edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;
    eax = eax ^ edx;
    eax = eax - edx;
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_475211;
    ebx = eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffdcu, 1, (eax & 0xffu));
L_475211:
    eax = lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = eax + 1u;
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffff7cu, 4, eax);
    {
        (void)lift_sub(32, eax, 0x65u, &fl);
    }
    if (fl.cf)
        goto L_4751a4;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    edx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x18u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx | eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffdcu, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    eax = eax | edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffc4u, 2)) & 0xffffu);
    ecx = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = eax | edx;
    edx = lift_load(&env, 0u, 0x54b800u, 4);
    esi = lift_load(&env, ebp, 0xffffff9cu, 4);
    edx = edx + ecx;
    esi = esi + 1u;
    ebx = (ecx + 0x4u);
    lift_store(&env, edx, 0x0u, 4, eax);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = lift_load(&env, 0u, 0x54b804u, 4);
    lift_store(&env, ebp, 0xffffff98u, 4, ebx);
    edx = edx + eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffff9cu, 4, esi);
    lift_store(&env, edx, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, esi, 0x40000u, &fl);
    }
    if (fl.cf)
        goto L_475104;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffff84u, 4, eax);
    lift_store(&env, ebp, 0xffffff78u, 4, eax);
L_47528a:
    eax = lift_load(&env, ebp, 0xffffff84u, 4);
    ecx = 0xfeu;
    edx = edx ^ edx;
    lift_div1(32, ecx, &eax, &edx, &fl);
    ebx = 0x64u;
    lift_store(&env, ebp, 0xffffffacu, 4, ebx);
    lift_store(&env, ebp, 0xffffffb0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffa4u, 2, (eax & 0xffffu));
    eax = (ebp + 0xffffffc8u);
    ebx = 0x64u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffc0u);
    ecx = (ebp + 0xffffffb4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    edx = ebx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffa4u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x474910u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffb0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, ecx, 0x65u, &fl);
        ecx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) ^ (ebx & 0xffu)) & 0xffu);
    lift_store(&env, ebp, 0xffffffccu, 2, (eax & 0xffffu));
    lift_store(&env, ebp, 0xffffffd4u, 1, (ebx & 0xffu));
    lift_store(&env, ebp, 0xffffffe4u, 1, (ebx & 0xffu));
    lift_store(&env, ebp, 0xffffffd8u, 1, (ebx & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    ebx = 0x100u;
    lift_store(&env, ebp, 0xffffffa0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    esi = ebx;
    lift_store(&env, ebp, 0xffffffa8u, 2, (eax & 0xffffu));
    eax = eax ^ eax;
    edi = ebx;
    lift_store(&env, ebp, 0xffffff7cu, 4, eax);
    ecx = ecx + 0x5468b0u;
L_475302:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffff88u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffcau, 4);
    edx = lift_load(&env, ebp, 0xffffff88u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;
    eax = eax ^ edx;
    eax = eax - edx;
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_475329;
    ebx = eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffd4u, 1, (eax & 0xffu));
L_475329:
    edx = lift_load(&env, ebp, 0xffffff9eu, 4);
    eax = eax ^ eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    edx = edx - eax;
    eax = edx;
    edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;
    eax = eax ^ edx;
    eax = eax - edx;
    {
        (void)lift_sub(16, (eax & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_47534c;
    esi = eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe4u, 1, (eax & 0xffu));
L_47534c:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffff88u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa6u, 4);
    edx = lift_load(&env, ebp, 0xffffff88u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;
    eax = eax ^ edx;
    eax = eax - edx;
    {
        (void)lift_sub(16, (eax & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_475373;
    edi = eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffd8u, 1, (eax & 0xffu));
L_475373:
    eax = lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = eax + 1u;
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffff7cu, 4, eax);
    {
        (void)lift_sub(32, eax, 0x65u, &fl);
    }
    if (fl.cf)
        goto L_475302;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    edx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x18u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx | eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    edx = edx | eax;
    eax = eax ^ eax;
    ecx = lift_load(&env, ebp, 0xffffff84u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffb0u, 2)) & 0xffffu);
    ecx = ecx + 0x167u;
    eax = eax | edx;
    edx = lift_load(&env, ebp, 0xffffff78u, 4);
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    ebx = (edx + 0x4u);
    lift_store(&env, edx, 0x54c1d4u, 4, eax);
    lift_store(&env, ebp, 0xffffff78u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x3fcu, &fl);
    }
    if (!fl.zf)
        goto L_47528a;
    edi = 0x64u;
    eax = eax ^ eax;
L_4753e4:
    eax = eax + 0x4u;
    edx = lift_load(&env, eax, 0x54c1d0u, 4);
    lift_store(&env, eax, 0x54c9c8u, 4, edi);
    lift_store(&env, eax, 0x54c5ccu, 4, edx);
    {
        (void)lift_sub(32, eax, 0x3fcu, &fl);
    }
    if (!fl.zf)
        goto L_4753e4;
    edx = 0x5468b0u;
    eax = eax ^ eax;
L_475407:
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x54b86cu, 4, edx);
    {
        (void)lift_sub(32, eax, 0x320u, &fl);
    }
    if (!fl.zf)
        goto L_475407;
    eax = eax ^ eax;
L_475419:
    lift_store(&env, eax, 0x54bb90u, 4, edx);
    eax = eax + 0x4u;
    edx = edx + 0x65u;
    {
        (void)lift_sub(32, eax, 0x324u, &fl);
    }
    if (!fl.zf)
        goto L_475419;
    ecx = 0x54b798u;
    eax = eax ^ eax;
L_475433:
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x54beb0u, 4, ecx);
    {
        (void)lift_sub(32, eax, 0x320u, &fl);
    }
    if (!fl.zf)
        goto L_475433;
    ebx = 0xc8u;
    esi = 0x54c9ccu;
    eax = 0x54c1d4u;
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffff7cu, 4, ebx);
    lift_store(&env, 0u, 0x54d1d0u, 4, esi);
    lift_store(&env, ebp, 0xffffff7cu, 4, edi);
L_475466:
    edx = lift_load(&env, ebp, 0xffffff7cu, 4);
    lift_store(&env, 0u, (edx * 4u) + 0x54d1d4u, 4, eax);
    edx = edx + 1u;
    eax = eax + 0x4u;
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    {
        (void)lift_sub(32, edx, 0xffu, &fl);
    }
    if (fl.cf)
        goto L_475466;
    ebx = 0x54bb90u;
    esi = 0x54d1d0u;
    eax = lift_load(&env, ebp, 0xffffff64u, 4);
    lift_store(&env, 0u, 0x54cdc8u, 4, ebx);
    lift_store(&env, 0u, 0x54cdccu, 4, esi);
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
L_4754b1:
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffa4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, edx, 0xfeu, &fl);
        edx = r;
    }
    ecx = 0x167u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffa4u, 2, (eax & 0xffffu));
    goto L_475172;
}

uint32_t lifted_f478860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F478860_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F478860_STACK, 0, entry);
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
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x30u;
    edi = 0x1u;
    edx = edx ^ edx;
    eax = (ebp + 0xfffffff0u);
    lift_store(&env, 0u, 0x5589e0u, 4, edx);
    lift_store(&env, 0u, 0x598dacu, 4, edx);
    lift_store(&env, 0u, 0x5589d4u, 4, edx);
    lift_store(&env, 0u, 0x598d60u, 4, edx);
    lift_store(&env, 0u, 0x598da8u, 4, edi);
    lift_store(&env, 0u, 0x5589dcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40a950u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4788a8;
L_4788a0:
    esp = (ebp + 0xfffffff4u);
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
L_4788a8:
    edx = (ebp + 0xffffffc4u);
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    ebx = 0xac44u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40a8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = 0x101u;
    lift_store(&env, ebp, 0xffffffeeu, 2, (ebx & 0xffffu));
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = (ebp + 0xffffffe8u);
    lift_store(&env, ebp, 0xffffffecu, 2, (edx & 0xffffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40a9d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4788a0;
    lift_store(&env, 0u, 0x5589e0u, 4, edi);
    esp = (ebp + 0xfffffff4u);
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

uint32_t lifted_object_describe(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_DESCRIBE_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_DESCRIBE_STACK, 0, entry);
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
    edx = 0x4ec1ecu;
    ebx = 0x516840u;
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
    eax = (ebp + 0xffffffecu);
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x50ea1eu;
    eax = (ebp + 0xffffffecu);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0xdu, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_478e7d;
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_478e84;
    edx = 0x50ea2du;
L_478e31:
    eax = (ebp + 0xffffffecu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_478e39:
    edx = 0x50ea3cu;
    eax = (ebp + 0xffffffecu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x10u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_478ea8;
    edx = 0x50ea48u;
L_478e51:
    eax = (ebp + 0xffffffecu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffecu);
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
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
L_478e7d:
    edx = 0x50ea2bu;
    goto L_478e31;
L_478e84:
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_478e9a;
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_478ea1;
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_478e39;
    edx = 0x50ea36u;
    goto L_478e31;
L_478e9a:
    edx = 0x50ea30u;
    goto L_478e31;
L_478ea1:
    edx = 0x50ea33u;
    goto L_478e31;
L_478ea8:
    edx = 0x50ea4cu;
    goto L_478e51;
}

uint32_t lifted_surface_fill(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_SURFACE_FILL_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_SURFACE_FILL_STACK, 0, entry);
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
    ecx = lift_load(&env, 0u, 0x5589fcu, 4);
    ebx = lift_load(&env, 0u, 0x5589f4u, 4);
    esi = lift_load(&env, 0u, 0x558a08u, 4);
    edi = lift_load(&env, 0u, 0x5589f8u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x479a40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, 0u, 0x558a0cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0xcu, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_479011;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x18u, &fl);
        ebx = r;
    }
    ebx = ebx + eax;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = eax + ebx;
    ecx = lift_load(&env, 0u, 0x5589fcu, 4);
L_478fb0:
    esi = esi + eax;
L_478fb2:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_479031;
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, ebx, 0x8u, 4), &fl);
        eax = r;
    }
    edi = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edi, 0xcu, 1)) & 0xffu);
    edi = eax;
    {
        uint32_t r = lift_imul(32, edi, ebx, &fl);
        edi = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        edi = r;
    }
    ebx = lift_load(&env, ebx, 0x0u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_478ff0;
L_478fe2:
    {
        uint32_t r = lift_add(32, ebx, 0x4u, &fl);
        ebx = r;
    }
    lift_store(&env, ebx, 0xfffffffcu, 4, esi);
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
    if (!fl.zf)
        goto L_478fe2;
L_478ff0:
    lift_store(&env, 0u, 0x5589f8u, 4, edi);
    lift_store(&env, 0u, 0x558a08u, 4, esi);
    lift_store(&env, 0u, 0x5589f4u, 4, ebx);
    lift_store(&env, 0u, 0x5589fcu, 4, ecx);
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
L_479011:
    esi = lift_load(&env, 0u, 0x558a08u, 4);
    ecx = lift_load(&env, 0u, 0x5589fcu, 4);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_479027;
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    goto L_478fb0;
L_479027:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_478fb2;
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    goto L_478fb2;
L_479031:
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0xcu, 1)) & 0xffu);
    edi = lift_load(&env, ebx, 0x4u, 4);
    {
        uint32_t r = lift_imul(32, edi, eax, &fl);
        edi = r;
    }
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = lift_load(&env, eax, 0x18u, 4);
    lift_store(&env, 0u, 0x558a04u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        edi = r;
    }
    lift_store(&env, 0u, 0x558a00u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
L_47905c:
    if (fl.zf)
        goto L_478ff0;
    ecx = edi;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_47906d;
L_479064:
    {
        uint32_t r = lift_add(32, ebx, 0x4u, &fl);
        ebx = r;
    }
    lift_store(&env, ebx, 0xfffffffcu, 4, esi);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    if (!fl.zf)
        goto L_479064;
L_47906d:
    eax = ebx;
    ebx = lift_load(&env, 0u, 0x558a04u, 4);
    {
        uint32_t r = lift_add(32, ebx, eax, &fl);
        ebx = r;
    }
    eax = lift_load(&env, 0u, 0x558a00u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, 0u, 0x558a00u, 4, eax);
    goto L_47905c;
}

uint32_t lifted_f4797f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4797F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4797F0_STACK, 0, entry);
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
    ecx = lift_load(&env, 0u, 0x558a24u, 4);
    ebx = lift_load(&env, 0u, 0x558a28u, 4);
    esi = lift_load(&env, 0u, 0x558a20u, 4);
    edi = eax;
    eax = edx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4816f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47988a;
    edx = lift_load(&env, edi, 0x4u, 4);
    {
        uint32_t r = lift_imul(32, edx, lift_load(&env, edi, 0x8u, 4), &fl);
        edx = r;
    }
    esi = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, 0u, 0x558a20u, 4, esi);
    lift_store(&env, 0u, 0x558a2cu, 4, edx);
    ebx = edx;
    ecx = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, 0u, 0x558a28u, 4, edx);
    lift_store(&env, 0u, 0x558a24u, 4, ecx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_479882;
L_479847:
    esi = lift_load(&env, 0u, 0x558a20u, 4);
    ebx = lift_load(&env, 0u, 0x558a28u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    ecx = lift_load(&env, 0u, 0x558a24u, 4);
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_479899;
    edx = lift_load(&env, ecx, 0x0u, 4);
    edx = edx & 0xffffffu;
L_479867:
    lift_store(&env, ecx, 0x0u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, 0x4u, &fl);
        ecx = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    lift_store(&env, 0u, 0x558a24u, 4, ecx);
    lift_store(&env, 0u, 0x558a20u, 4, esi);
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    lift_store(&env, 0u, 0x558a28u, 4, ebx);
    if (!fl.zf)
        goto L_479847;
L_479882:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_47988a:
    ecx = lift_load(&env, 0u, 0x558a24u, 4);
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
L_479899:
    edx = lift_load(&env, ecx, 0x0u, 4);
    edx = edx | 0xff000000u;
    goto L_479867;
}

uint32_t lifted_f47c520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47C520_STACK + 4 + 4 * 7 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47C520_STACK, 7, entry);
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
    esp = esp - 0x58u;
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edi = ebx;
    esi = ecx;
    edx = lift_load(&env, ebp, 0x10u, 4);
    ebx = lift_load(&env, ebp, 0x14u, 4);
    ecx = lift_load(&env, ebp, 0x18u, 4);
    eax = (ebp + 0xffffffccu);
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
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x4ec1ecu);
    lift_store(&env, ebp, 0xffffffd4u, 4, 0x51684cu);
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x20u, 4), 0xff000000u, &fl);
    }
    if (fl.zf)
        goto L_47c6df;
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, edi);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, ebp, 0xcu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    {
        (void)lift_sub(32, edi, ecx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_47c6df;
    {
        (void)lift_sub(32, edx, lift_load(&env, ebp, 0x8u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_47c6df;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0x1cu, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_47c6df;
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0xcu, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_47c6df;
    {
        (void)lift_sub(32, esi, ebx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_47c5a8;
    esi = ebx;
L_47c5a8:
    {
        (void)lift_sub(32, edi, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_47c5ae;
    edi = edx;
L_47c5ae:
    eax = lift_load(&env, ebp, 0xcu, 4);
    edx = lift_load(&env, ebp, 0x1cu, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_47c5bb;
    lift_store(&env, ebp, 0xcu, 4, edx);
L_47c5bb:
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0x8u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_47c5c3;
    lift_store(&env, ebp, 0x8u, 4, ecx);
L_47c5c3:
    eax = lift_load(&env, ebp, 0x8u, 4);
    eax = eax - edi;
    eax = eax + 1u;
    lift_store(&env, 0u, 0x558b84u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xcu, 4);
    eax = eax - esi;
    eax = eax + 1u;
    lift_store(&env, 0u, 0x558b86u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x558b82u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_47c6df;
    eax = lift_load(&env, 0u, 0x558b84u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_47c6df;
    eax = (ebp + 0xffffffa0u);
    ecx = 0xffu;
    ebx = 0xff00u;
    edx = 0xff0000u;
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
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = (ebp + 0xffffffa0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481bc0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47c6f1;
    ebx = lift_load(&env, ebp, 0x20u, 4);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = (ebp + 0xffffffa0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481e10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ebp, 0x20u, 4, eax);
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (!fl.zf)
        goto L_47c65f;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, 0u, 0x558b82u, 4);
    ebx = edx;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47c3b0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_47c65f:
    eax = lift_load(&env, ebp, 0xcu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xfffffff0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_47c683;
    ebx = lift_load(&env, ebp, 0x20u, 4);
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, 0u, 0x558b82u, 4);
    edx = edi;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    ebx = lift_load(&env, ebp, 0xcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47c3b0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_47c683:
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffecu, 4), &fl);
    }
    if (!fl.zf)
        goto L_47c6a6;
    edx = lift_load(&env, ebp, 0x20u, 4);
    ecx = 0x1u;
    eax = lift_load(&env, 0u, 0x558b84u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ebx = esi;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edi;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47c3b0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_47c6a6:
    eax = lift_load(&env, ebp, 0x8u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffe0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_47c6cd;
    ebx = lift_load(&env, ebp, 0x20u, 4);
    ecx = 0x1u;
    eax = lift_load(&env, 0u, 0x558b84u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0x8u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = esi;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47c3b0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_47c6cd:
    eax = (ebp + 0xffffffa0u);
    esi = esi ^ esi;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481b30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
L_47c6df:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
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
L_47c6f1:
    eax = (ebp + 0xffffffa0u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481b30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
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
}

uint32_t lifted_f47e360(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47E360_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47E360_STACK, 0, entry);
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
    esp = esp - 0x64u;
    esi = eax;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    eax = (ebp + 0xffffffb8u);
    edx = 0x4ec1ecu;
    ecx = 0x516870u;
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
    eax = (ebp + 0xffffff8cu);
    lift_store(&env, ebp, 0xffffffbcu, 4, edx);
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffc4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481b20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0xff000000u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0xffu;
    ebx = 0xff00u;
    edx = 0xff0000u;
    eax = (ebp + 0xffffff8cu);
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481bc0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47e483;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffecu, 1, (eax & 0xffu));
    eax = lift_load(&env, esi, 0x4u, 4);
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, esi, 0x8u, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    edi = lift_load(&env, eax, 0x0u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x14u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    lift_store(&env, eax, 0xdu, 1, (edx & 0xffu));
    ecx = edi;
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = eax ^ eax;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47e45a;
L_47e414:
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = esi ^ esi;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47e44c;
L_47e41d:
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = (ebp + 0xffffff8cu);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481d90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    edx = eax;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47e491;
    edi = edi + 1u;
    lift_store(&env, edi, 0xffffffffu, 1, (eax & 0xffu));
L_47e43b:
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = ebx + 0x4u;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.cf)
        goto L_47e41d;
L_47e44c:
    ebx = lift_load(&env, ebp, 0xffffffccu, 4);
    ebx = ebx + 1u;
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.cf)
        goto L_47e414;
L_47e45a:
    esi = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = (ebp + 0xffffff8cu);
    edi = edi ^ edi;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481b30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
L_47e46f:
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
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
L_47e483:
    eax = (ebp + 0xffffff8cu);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481b30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    goto L_47e46f;
L_47e491:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_47e4a4;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = (eax + 0x2u);
    lift_store(&env, eax, 0x0u, 2, (edx & 0xffffu));
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    goto L_47e43b;
L_47e4a4:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_47e4ca;
    eax = eax & 0xff0000u;
    ecx = ecx + 1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0xffffffffu, 1, (eax & 0xffu));
    eax = eax ^ eax;
    ecx = ecx + 1u;
    eax = (eax & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    ecx = ecx + 1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0xfffffffeu, 1, (eax & 0xffu));
    lift_store(&env, ecx, 0xffffffffu, 1, (edx & 0xffu));
    goto L_47e43b;
L_47e4ca:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_47e43b;
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    edx = edx + 0x4u;
    lift_store(&env, edx, 0xfffffffcu, 4, eax);
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    goto L_47e43b;
}

uint32_t lifted_render_weights_build(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RENDER_WEIGHTS_BUILD_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_RENDER_WEIGHTS_BUILD_STACK, 0, entry);
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
    esp = esp - 0x24u;
    edx = 0x100u;
    ebp = ebp ^ ebp;
    lift_store(&env, esp, 0x4u, 4, edx);
    lift_store(&env, esp, 0x8u, 4, ebp);
L_480748:
    edi = lift_load(&env, esp, 0x8u, 4);
    ebx = ebp;
    esi = lift_load(&env, esp, 0x4u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_imul(32, ebp, 0x0u, &fl);
        ecx = r;
    }
L_480758:
    lift_store(&env, esp, 0x20u, 4, 0x64u);
    eax = ecx;
    edx = edx ^ edx;
    lift_div1(32, lift_load(&env, esp, 0x20u, 4), &eax, &edx, &fl);
    ebx = ebx + 1u;
    ecx = ecx + edi;
    lift_store(&env, ebx, 0x558cefu, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (!fl.zf)
        goto L_480758;
    ebx = lift_load(&env, esp, 0x4u, 4);
    esi = lift_load(&env, esp, 0x8u, 4);
    ebp = ebp + 1u;
    ebx = ebx + 0x100u;
    esi = esi + 1u;
    lift_store(&env, esp, 0x4u, 4, ebx);
    lift_store(&env, esp, 0x8u, 4, esi);
    {
        (void)lift_sub(32, ebp, 0x65u, &fl);
    }
    if (fl.cf)
        goto L_480748;
    edi = 0x400u;
    ebp = ebp ^ ebp;
    lift_store(&env, esp, 0x0u, 4, edi);
    lift_store(&env, esp, 0x14u, 4, ebp);
L_4807a0:
    esi = lift_load(&env, esp, 0x14u, 4);
    ecx = ebp;
    edi = lift_load(&env, esp, 0x0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, ebp, 0x0u, &fl);
        ebx = r;
    }
L_4807af:
    lift_store(&env, esp, 0x20u, 4, 0x64u);
    eax = ebx;
    edx = edx ^ edx;
    lift_div1(32, lift_load(&env, esp, 0x20u, 4), &eax, &edx, &fl);
    ecx = ecx + 0x2u;
    ebx = ebx + esi;
    lift_store(&env, ecx, 0x55f1f6u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (!fl.zf)
        goto L_4807af;
    edx = lift_load(&env, esp, 0x0u, 4);
    ecx = lift_load(&env, esp, 0x14u, 4);
    ebp = ebp + 1u;
    edx = edx + 0x400u;
    ecx = ecx + 1u;
    lift_store(&env, esp, 0x0u, 4, edx);
    lift_store(&env, esp, 0x14u, 4, ecx);
    {
        (void)lift_sub(32, ebp, 0x65u, &fl);
    }
    if (fl.cf)
        goto L_4807a0;
    esi = 0x100u;
    ebx = ebx ^ ebx;
    ebp = 0xff00u;
    lift_store(&env, esp, 0x1cu, 4, ebx);
    lift_store(&env, esp, 0x18u, 4, esi);
    lift_store(&env, esp, 0x10u, 4, ebx);
    lift_store(&env, esp, 0xcu, 4, ebp);
L_480806:
    ecx = lift_load(&env, esp, 0x1cu, 4);
    esi = lift_load(&env, esp, 0xcu, 4);
    ebp = lift_load(&env, esp, 0x10u, 4);
    eax = lift_load(&env, esp, 0x1cu, 4);
    edi = lift_load(&env, esp, 0x18u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, eax, 0x0u, &fl);
        ebx = r;
    }
L_480820:
    lift_store(&env, esp, 0x20u, 4, 0xffu);
    eax = ebx;
    edx = edx ^ edx;
    lift_div1(32, lift_load(&env, esp, 0x20u, 4), &eax, &edx, &fl);
    ecx = ecx + 1u;
    esi = esi + 1u;
    ebx = ebx + ebp;
    lift_store(&env, ecx, 0x5785ffu, 1, (eax & 0xffu));
    lift_store(&env, esi, 0x5885ffu, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (!fl.zf)
        goto L_480820;
    edx = lift_load(&env, esp, 0x18u, 4);
    ecx = lift_load(&env, esp, 0x10u, 4);
    ebx = lift_load(&env, esp, 0xcu, 4);
    esi = lift_load(&env, esp, 0x1cu, 4);
    edx = edx + 0x100u;
    ecx = ecx + 1u;
    ebx = ebx - 0x100u;
    esi = esi + 1u;
    lift_store(&env, esp, 0x18u, 4, edx);
    lift_store(&env, esp, 0x10u, 4, ecx);
    lift_store(&env, esp, 0xcu, 4, ebx);
    lift_store(&env, esp, 0x1cu, 4, esi);
    {
        (void)lift_sub(32, esi, 0x100u, &fl);
    }
    if (fl.cf)
        goto L_480806;
    {
        uint32_t r = lift_add(32, esp, 0x24u, &fl);
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

uint32_t lifted_palette_cube(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PALETTE_CUBE_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_PALETTE_CUBE_STACK, 0, entry);
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
    esp = esp - 0x18u;
    edi = eax;
    edx = edx ^ edx;
    lift_store(&env, esp, 0x10u, 4, edx);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0x10u, 1)) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_shl(8, a, 0x3u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, esp, 0xcu, 4, edx);
    lift_store(&env, esp, 0x14u, 1, (eax & 0xffu));
    ebp = 0x4u;
L_480cc5:
    eax = lift_load(&env, esp, 0xcu, 4);
    ebx = ebx ^ ebx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x14u, 1)) & 0xffu);
    lift_store(&env, esp, 0x4u, 4, ebx);
    lift_store(&env, esp, 0x0u, 4, eax);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, esp, 0x4u, 1)) & 0xffu) << 8);
    lift_store(&env, esp, 0x8u, 4, ebx);
    {
        uint32_t a = ((ecx >> 8) & 0xffu);
        uint32_t r = lift_shl(8, a, 0x3u, &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
L_480ce1:
    esi = lift_load(&env, esp, 0x0u, 4);
    ebx = (ebx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu)) & 0xffu) << 8);
    eax = eax ^ eax;
    edx = lift_load(&env, esp, 0x8u, 4);
    ebx = (ebx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    esi = esi | edx;
    {
        uint32_t a = (ebx & 0xffu);
        uint32_t r = lift_shl(8, a, 0x4u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
L_480cf3:
    edx = esi;
    edx = edx | eax;
    edx = (edx + (edx * 2u));
    lift_store(&env, edx, edi + 0x0u, 1, (ecx & 0xffu));
    lift_store(&env, edx, edi + 0x1u, 1, ((ebx >> 8) & 0xffu));
    eax = eax + 1u;
    lift_store(&env, edx, edi + 0x2u, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) + 0x10u) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.cf)
        goto L_480cf3;
    ebx = lift_load(&env, esp, 0x8u, 4);
    esi = lift_load(&env, esp, 0x4u, 4);
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + 0x8u) & 0xffu) << 8);
    ebx = ebx + ebp;
    esi = esi + 1u;
    lift_store(&env, esp, 0x8u, 4, ebx);
    lift_store(&env, esp, 0x4u, 4, esi);
    {
        (void)lift_sub(32, esi, 0x8u, &fl);
    }
    if (fl.cf)
        goto L_480ce1;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esp, 0x14u, 1)) & 0xffu) << 8);
    edx = lift_load(&env, esp, 0xcu, 4);
    ecx = lift_load(&env, esp, 0x10u, 4);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) + 0x8u) & 0xffu) << 8);
    edx = edx + 0x20u;
    ecx = ecx + 1u;
    lift_store(&env, esp, 0x14u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, esp, 0xcu, 4, edx);
    lift_store(&env, esp, 0x10u, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0x8u, &fl);
    }
    if (fl.cf)
        goto L_480cc5;
    {
        uint32_t r = lift_add(32, esp, 0x18u, &fl);
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

uint32_t lifted_f4816f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4816F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4816F0_STACK, 0, entry);
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
    esp = esp - 0x128u;
    esi = eax;
    edi = edx;
    eax = (ebp + 0xffffffdcu);
    edx = 0x4ec1ecu;
    ecx = 0x516accu;
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
    eax = (ebp + 0xfffffec8u);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    ebx = lift_load(&env, 0u, 0x5466c8u, 4);
    edx = esi;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = (ebp + 0xfffffec8u);
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_48177e;
L_481755:
    eax = (ebp + 0xfffffec8u);
    edx = edx ^ edx;
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
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
L_48177e:
    eax = (ebp + 0xfffffec8u);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x480ec0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = (ebp + 0xfffffec8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a8c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_481755;
}

uint32_t lifted_f482d00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F482D00_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F482D00_STACK, 0, entry);
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
    esp = esp - 0x3cu;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    edx = 0x28u;
    eax = 0x1u;
    ecx = 0x30u;
    ebx = 0x1u;
    esi = (ebp + 0xffffffb8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffb0u);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edi = lift_load(&env, ebp, 0xffffffe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x28u;
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
    ecx = lift_load(&env, edi, 0x4u, 4);
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, edi, 0x8u, 4), &fl);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x27u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_482d72;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_482db1;
L_482d65:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
L_482d72:
    edx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffb0u, 1)) & 0xffu) << 8);
    esi = eax;
    {
        (void)lift_and(8, ((edx >> 8) & 0xffu), ((edx >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_482d9d;
    ebx = 0x1u;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_482d96:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x0u, 4, esi);
    goto L_482d65;
L_482d9d:
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_482d96;
    ebx = lift_load(&env, ebp, 0xffffffb4u, 4);
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_482d96;
L_482db1:
    eax = eax & 0xffu;
    {
        uint32_t r = lift_imul(32, ecx, eax, &fl);
        ecx = r;
    }
    edx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffb0u, 1)) & 0xffu);
    esi = eax;
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_482ddd;
    ebx = 0x1u;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_482ddd:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = 0x5b9c60u;
    lift_store(&env, eax, 0x0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x483750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x483ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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

uint32_t lifted_f483110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F483110_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F483110_STACK, 0, entry);
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
    esp = esp - 0x8u;
    ebx = eax;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_483133;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
L_483133:
    edx = 0x28u;
    eax = 0x1u;
    ecx = 0x28u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = ebx;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    edi = eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
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
    edx = lift_load(&env, ebx, 0x4u, 4);
    {
        uint32_t r = lift_imul(32, edx, lift_load(&env, ebx, 0x8u, 4), &fl);
        edx = r;
    }
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebx, 0x27u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, ecx, edx, &fl);
        ecx = r;
    }
    edx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    esi = lift_load(&env, ebx, 0x0u, 4);
    edx = eax;
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
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ecx, 0x0u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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

uint32_t lifted_f484b60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F484B60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F484B60_STACK, 0, entry);
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
    esp = esp - 0x10cu;
    esi = eax;
    edi = edx;
    eax = eax + 0x60u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    {
        uint32_t v = 0x51e580u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x4u, 4, 0x0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, 0x0u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0xcu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f0806u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485014;
    edx = lift_load(&env, esi, 0x60u, 4);
    {
        uint32_t v = 0x17u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x5328b4u, 4);
    ecx = lift_load(&env, edx, 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485038;
L_484bbb:
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
    eax = lift_call(&env, lift_load(&env, ecx, 0x50u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485040;
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_485064;
    lift_store(&env, esi, 0x3eu, 2, 0x140u);
    lift_store(&env, esi, 0x40u, 2, 0xc8u);
L_484bde:
    lift_store(&env, esi, 0x54u, 2, 0x8u);
L_484be4:
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x54u, 2)) & 0xffffu);
    eax = edx;
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
    eax = eax - edx - fl.cf;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    lift_store(&env, esi, 0x56u, 2, (eax & 0xffffu));
    eax = eax ^ eax;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x3eu, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x40u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x56u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    lift_store(&env, esi, 0x48u, 4, edx);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x4cu, 4, eax);
    eax = lift_load(&env, esi, 0x48u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x50u, 4, eax);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x56u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x3eu, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    lift_store(&env, esi, 0x42u, 2, (eax & 0xffffu));
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
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x42u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x44u, 2, (eax & 0xffffu));
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
    eax = eax - edx - fl.cf;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x54u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x58u, 1, 0xdu);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x40u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x46u, 2, (eax & 0xffffu));
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    eax = lift_load(&env, esi, 0x60u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x3eu, 2)) & 0xffffu);
    lift_store(&env, esi, 0x3cu, 1, (ebx & 0xffu));
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
    eax = lift_call(&env, lift_load(&env, ecx, 0x54u, 4), eax, edx, ebx, ecx, 6, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 24u;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4852f0;
    eax = lift_load(&env, esi, 0x60u, 4);
    {
        uint32_t v = 0x17u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x5328b4u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_485316;
L_484ca6:
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
    eax = lift_call(&env, lift_load(&env, ecx, 0x50u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_48531e;
    ebx = 0x7cu;
    eax = (ebp + 0xffffff64u);
    edx = edx ^ edx;
    ecx = 0x21u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x7cu;
    ebx = 0x218u;
    eax = 0x1u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffff68u, 4, ecx);
    lift_store(&env, ebp, 0xffffff64u, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    ecx = (esi + 0x64u);
    lift_store(&env, ebp, 0xffffff78u, 4, eax);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ebp + 0xffffff64u);
    eax = lift_load(&env, esi, 0x60u, 4);
    {
        uint32_t v = ecx;
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
    eax = lift_call(&env, lift_load(&env, edx, 0x18u, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485344;
    ebx = 0x10u;
    eax = (ebp + 0xffffffe0u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = (esi + 0x68u);
    edx = 0x4u;
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ebp + 0xffffffe0u);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x64u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x30u, 4), eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_48536a;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x68u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48536a;
    ebx = 0x7cu;
    eax = (ebp + 0xfffffee8u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = 0x7cu;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ebp + 0xfffffee8u);
    lift_store(&env, ebp, 0xfffffee8u, 4, ebx);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x68u, 4);
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
    eax = lift_call(&env, lift_load(&env, edx, 0x64u, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485390;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffff0cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4853b6;
    {
        (void)lift_sub(16, lift_load(&env, esi, 0x54u, 2), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_4853c9;
    lift_store(&env, esi, 0x0u, 4, 0xe0u);
    lift_store(&env, esi, 0x4u, 4, 0x1cu);
    lift_store(&env, esi, 0x8u, 4, 0x3u);
    lift_store(&env, esi, 0xcu, 4, 0x0u);
L_484dbc:
    eax = (esi + 0x10u);
    edx = lift_load(&env, esi, 0xcu, 4);
    ecx = lift_load(&env, esi, 0x8u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, esi, 0x4u, 4);
    edx = lift_load(&env, esi, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481bc0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4853b6;
    ebx = lift_load(&env, ebp, 0xfffffef0u, 4);
    edx = lift_load(&env, ebp, 0xfffffef4u, 4);
    eax = lift_load(&env, ebp, 0xffffff0cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    lift_store(&env, 0u, 0x558c7cu, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x24u, 1)) & 0xffu);
    lift_store(&env, edx, 0xdu, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xfffffef8u, 4);
    lift_store(&env, edx, 0x14u, 4, eax);
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478da0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x50fd86u;
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478dd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x68u, 4);
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
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485406;
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xffffff51u, 1), 0x40u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, esi, 0x5cu, 4, eax);
    {
        (void)lift_sub(16, lift_load(&env, esi, 0x54u, 2), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_484e85;
    eax = 0x598a30u;
    ebx = 0x400u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x480ca0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = 0x598630u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x598a30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x480890u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
    edx = lift_load(&env, esi, 0x60u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4808f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
    edx = lift_load(&env, esi, 0x64u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x480940u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_484e85:
    ebx = 0x7cu;
    eax = (ebp + 0xffffff64u);
    edx = edx ^ edx;
    ecx = 0x7cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x7u;
    eax = 0x4040u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffff64u, 4, ecx);
    lift_store(&env, ebp, 0xffffff68u, 4, ebx);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = eax ^ eax;
    ecx = (esi + 0x6cu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x40u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xfffffff0u, 4, ecx);
    lift_store(&env, ebp, 0xffffff6cu, 4, eax);
    eax = eax ^ eax;
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x3eu, 2)) & 0xffffu);
    ecx = (ebp + 0xffffff64u);
    lift_store(&env, ebp, 0xffffff70u, 4, eax);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x60u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x18u, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    ebx = eax;
    {
        (void)lift_sub(32, eax, 0x8876017cu, &fl);
    }
    if (!fl.zf)
        goto L_484f4f;
    ebx = 0x7cu;
    eax = (ebp + 0xffffff64u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x7cu;
    eax = 0x7u;
    edx = 0x840u;
    lift_store(&env, ebp, 0xffffff64u, 4, ebx);
    lift_store(&env, ebp, 0xffffff68u, 4, eax);
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    eax = eax ^ eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x40u, 2)) & 0xffffu);
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, ebp, 0xffffff6cu, 4, eax);
    eax = eax ^ eax;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x3eu, 2)) & 0xffffu);
    edx = (ebp + 0xffffff64u);
    lift_store(&env, ebp, 0xffffff70u, 4, eax);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x60u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x18u, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    ebx = eax;
L_484f4f:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_48542c;
    ebx = 0x7cu;
    eax = (ebp + 0xfffffee8u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x7cu;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xfffffee8u);
    lift_store(&env, ebp, 0xfffffee8u, 4, eax);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x6cu, 4);
    {
        uint32_t v = 0x0u;
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
    eax = lift_call(&env, lift_load(&env, ecx, 0x64u, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485452;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffff0cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4853b6;
    ebx = lift_load(&env, ebp, 0xfffffef0u, 4);
    edx = lift_load(&env, ebp, 0xfffffef4u, 4);
    eax = lift_load(&env, ebp, 0xffffff0cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    lift_store(&env, 0u, 0x558c84u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x24u, 1)) & 0xffu);
    lift_store(&env, edx, 0xdu, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xfffffef8u, 4);
    lift_store(&env, edx, 0x14u, 4, eax);
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478da0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, 0u, 0x558c84u, 4);
    eax = lift_load(&env, ebp, 0xffffff0cu, 4);
    edx = 0x50fe55u;
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478dd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x6cu, 4);
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
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485476;
    eax = 0x1u;
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
L_485014:
    edx = edi;
    eax = esi;
    ebx = 0x50fc3eu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_485038:
    eax = lift_load(&env, eax, 0x1cu, 4);
    goto L_484bbb;
L_485040:
    edx = edi;
    eax = esi;
    ebx = 0x50fc5du;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_485064:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48507a;
    lift_store(&env, esi, 0x3eu, 2, 0x280u);
    lift_store(&env, esi, 0x40u, 2, 0x190u);
    goto L_484bde;
L_48507a:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_485090;
    lift_store(&env, esi, 0x3eu, 2, 0x280u);
    lift_store(&env, esi, 0x40u, 2, 0x1e0u);
    goto L_484bde;
L_485090:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4850a6;
    lift_store(&env, esi, 0x3eu, 2, 0x320u);
    lift_store(&env, esi, 0x40u, 2, 0x258u);
    goto L_484bde;
L_4850a6:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4850bc;
    lift_store(&env, esi, 0x3eu, 2, 0x400u);
    lift_store(&env, esi, 0x40u, 2, 0x300u);
    goto L_484bde;
L_4850bc:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_4850d2;
    lift_store(&env, esi, 0x3eu, 2, 0x500u);
    lift_store(&env, esi, 0x40u, 2, 0x400u);
    goto L_484bde;
L_4850d2:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x6u, &fl);
    }
    if (!fl.zf)
        goto L_4850ee;
    lift_store(&env, esi, 0x3eu, 2, 0x140u);
    lift_store(&env, esi, 0x40u, 2, 0xc8u);
    lift_store(&env, esi, 0x54u, 2, 0x10u);
    goto L_484be4;
L_4850ee:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x7u, &fl);
    }
    if (!fl.zf)
        goto L_48510a;
    lift_store(&env, esi, 0x3eu, 2, 0x280u);
    lift_store(&env, esi, 0x40u, 2, 0x190u);
    lift_store(&env, esi, 0x54u, 2, 0x10u);
    goto L_484be4;
L_48510a:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_485126;
    lift_store(&env, esi, 0x3eu, 2, 0x280u);
    lift_store(&env, esi, 0x40u, 2, 0x1e0u);
    lift_store(&env, esi, 0x54u, 2, 0x10u);
    goto L_484be4;
L_485126:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x9u, &fl);
    }
    if (!fl.zf)
        goto L_485142;
    lift_store(&env, esi, 0x3eu, 2, 0x320u);
    lift_store(&env, esi, 0x40u, 2, 0x258u);
    lift_store(&env, esi, 0x54u, 2, 0x10u);
    goto L_484be4;
L_485142:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xau, &fl);
    }
    if (!fl.zf)
        goto L_48515e;
    lift_store(&env, esi, 0x3eu, 2, 0x400u);
    lift_store(&env, esi, 0x40u, 2, 0x300u);
    lift_store(&env, esi, 0x54u, 2, 0x10u);
    goto L_484be4;
L_48515e:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xbu, &fl);
    }
    if (!fl.zf)
        goto L_48517a;
    lift_store(&env, esi, 0x3eu, 2, 0x500u);
    lift_store(&env, esi, 0x40u, 2, 0x400u);
    lift_store(&env, esi, 0x54u, 2, 0x10u);
    goto L_484be4;
L_48517a:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xcu, &fl);
    }
    if (!fl.zf)
        goto L_485196;
    lift_store(&env, esi, 0x3eu, 2, 0x140u);
    lift_store(&env, esi, 0x40u, 2, 0xc8u);
    lift_store(&env, esi, 0x54u, 2, 0x18u);
    goto L_484be4;
L_485196:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xdu, &fl);
    }
    if (!fl.zf)
        goto L_4851b2;
    lift_store(&env, esi, 0x3eu, 2, 0x280u);
    lift_store(&env, esi, 0x40u, 2, 0x190u);
    lift_store(&env, esi, 0x54u, 2, 0x18u);
    goto L_484be4;
L_4851b2:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xeu, &fl);
    }
    if (!fl.zf)
        goto L_4851ce;
    lift_store(&env, esi, 0x3eu, 2, 0x280u);
    lift_store(&env, esi, 0x40u, 2, 0x1e0u);
    lift_store(&env, esi, 0x54u, 2, 0x18u);
    goto L_484be4;
L_4851ce:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xfu, &fl);
    }
    if (!fl.zf)
        goto L_4851ea;
    lift_store(&env, esi, 0x3eu, 2, 0x320u);
    lift_store(&env, esi, 0x40u, 2, 0x258u);
    lift_store(&env, esi, 0x54u, 2, 0x18u);
    goto L_484be4;
L_4851ea:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x10u, &fl);
    }
    if (!fl.zf)
        goto L_485206;
    lift_store(&env, esi, 0x3eu, 2, 0x400u);
    lift_store(&env, esi, 0x40u, 2, 0x300u);
    lift_store(&env, esi, 0x54u, 2, 0x18u);
    goto L_484be4;
L_485206:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x11u, &fl);
    }
    if (!fl.zf)
        goto L_485222;
    lift_store(&env, esi, 0x3eu, 2, 0x500u);
    lift_store(&env, esi, 0x40u, 2, 0x400u);
    lift_store(&env, esi, 0x54u, 2, 0x18u);
    goto L_484be4;
L_485222:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x12u, &fl);
    }
    if (!fl.zf)
        goto L_48523e;
    lift_store(&env, esi, 0x3eu, 2, 0x140u);
    lift_store(&env, esi, 0x40u, 2, 0xc8u);
    lift_store(&env, esi, 0x54u, 2, 0x20u);
    goto L_484be4;
L_48523e:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x13u, &fl);
    }
    if (!fl.zf)
        goto L_48525a;
    lift_store(&env, esi, 0x3eu, 2, 0x280u);
    lift_store(&env, esi, 0x40u, 2, 0x190u);
    lift_store(&env, esi, 0x54u, 2, 0x20u);
    goto L_484be4;
L_48525a:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x14u, &fl);
    }
    if (!fl.zf)
        goto L_485276;
    lift_store(&env, esi, 0x3eu, 2, 0x280u);
    lift_store(&env, esi, 0x40u, 2, 0x1e0u);
    lift_store(&env, esi, 0x54u, 2, 0x20u);
    goto L_484be4;
L_485276:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x15u, &fl);
    }
    if (!fl.zf)
        goto L_485292;
    lift_store(&env, esi, 0x3eu, 2, 0x320u);
    lift_store(&env, esi, 0x40u, 2, 0x258u);
    lift_store(&env, esi, 0x54u, 2, 0x20u);
    goto L_484be4;
L_485292:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x16u, &fl);
    }
    if (!fl.zf)
        goto L_4852ae;
    lift_store(&env, esi, 0x3eu, 2, 0x400u);
    lift_store(&env, esi, 0x40u, 2, 0x300u);
    lift_store(&env, esi, 0x54u, 2, 0x20u);
    goto L_484be4;
L_4852ae:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x17u, &fl);
    }
    if (!fl.zf)
        goto L_4852ca;
    lift_store(&env, esi, 0x3eu, 2, 0x500u);
    lift_store(&env, esi, 0x40u, 2, 0x400u);
    lift_store(&env, esi, 0x54u, 2, 0x20u);
    goto L_484be4;
L_4852ca:
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ebx = 0x50fc7fu;
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_4852f0:
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ebx;
    ebx = 0x50fc9fu;
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_485316:
    edx = lift_load(&env, edx, 0x1cu, 4);
    goto L_484ca6;
L_48531e:
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ebx;
    ebx = 0x50fcc6u;
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_485344:
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ebx;
    ebx = 0x50fcecu;
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_48536a:
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ebx;
    ebx = 0x50fd08u;
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_485390:
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ebx;
    ebx = 0x50fd32u;
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_4853b6:
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_4853c9:
    eax = lift_load(&env, ebp, 0xffffff40u, 4);
    lift_store(&env, esi, 0x0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff44u, 4);
    lift_store(&env, esi, 0x4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff48u, 4);
    lift_store(&env, esi, 0x8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff4cu, 4);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, esi, 0x54u, 2)) & 0xffffu);
    lift_store(&env, esi, 0xcu, 4, eax);
    {
        (void)lift_sub(16, (ecx & 0xffffu), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_484dbc;
    lift_store(&env, esi, 0xcu, 4, 0xff000000u);
    goto L_484dbc;
L_485406:
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ebx;
    ebx = 0x50fd9cu;
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_48542c:
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ebx;
    ebx = 0x50fddeu;
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_485452:
    edx = edi;
    eax = esi;
    ebx = 0x50fdfau;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_485476:
    edx = edi;
    eax = esi;
    ebx = 0x50fe69u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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

uint32_t lifted_f485520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F485520_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F485520_STACK, 0, entry);
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
    eax = lift_load(&env, eax, 0x6cu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x80u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, 0u, 0x5b99c0u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f485550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F485550_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F485550_STACK, 0, entry);
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
L_48555d:
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
        goto L_48555d;
    esi = esi ^ esi;
L_485571:
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
        uint32_t v = 0x5b99c8u;
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
    lift_store(&env, 0u, 0x5b99c4u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x887601c2u, &fl);
    }
    if (fl.zf)
        goto L_4855e1;
    esi = esi ^ esi;
L_485591:
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
        uint32_t v = 0x5b99c8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x6cu, 4);
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
    lift_store(&env, 0u, 0x5b99c4u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x887601c2u, &fl);
    }
    if (!fl.zf)
        goto L_4855ff;
    eax = lift_load(&env, ebx, 0x6cu, 4);
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
        goto L_4855c7;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487080u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485591;
L_4855c7:
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
L_4855d5:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4855d7:
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
L_4855e1:
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
        goto L_4855d5;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487080u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485571;
    goto L_4855d7;
L_4855ff:
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
    esi = lift_load(&env, ebx, 0x6cu, 4);
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
    lift_store(&env, 0u, 0x5b99c4u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485676;
L_485639:
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
        goto L_485639;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x6cu, 4);
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
L_485676:
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
    edi = lift_load(&env, ebx, 0x6cu, 4);
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
    goto L_485639;
}

uint32_t lifted_f486da0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F486DA0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F486DA0_STACK, 0, entry);
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
    eax = lift_load(&env, eax, 0x68u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x80u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, 0u, 0x5b9bc8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f486e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F486E20_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F486E20_STACK, 0, entry);
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
    esi = eax;
    ecx = lift_load(&env, 0u, 0x558c7cu, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_486ea0;
L_486e34:
    ebx = lift_load(&env, 0u, 0x558c84u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_486e45;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4872b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_486e45:
    eax = lift_load(&env, esi, 0x60u, 4);
    {
        uint32_t v = 0x8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_486ea9;
L_486e50:
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
    eax = lift_call(&env, lift_load(&env, ecx, 0x50u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_486e6c;
    ebx = 0x5106a7u;
    edx = 0x1u;
    ecx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_486e6c:
    edi = lift_load(&env, esi, 0x6cu, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_486e80;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, edi, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x6cu, 4, 0x0u);
L_486e80:
    eax = lift_load(&env, esi, 0x64u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_486e94;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x64u, 4, 0x0u);
L_486e94:
    edx = lift_load(&env, esi, 0x60u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_486eae;
    {
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
L_486ea0:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4872b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_486e34;
L_486ea9:
    edx = lift_load(&env, edx, 0x1cu, 4);
    goto L_486e50;
L_486eae:
    eax = edx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, edx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4cu, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, esi, 0x60u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x60u, 4, 0x0u);
    {
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

uint32_t lifted_array_list_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ARRAY_LIST_BUILD_STACK + 4 + 4 * 10 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_ARRAY_LIST_BUILD_STACK, 10, entry);
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
    edi = eax;
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    lift_store(&env, eax, 0x4u, 4, edx);
    eax = edx;
    edx = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, edi, 0x4u, 4);
    edx = edx ^ edx;
    lift_store(&env, edi, 0x0u, 4, eax);
    lift_store(&env, ebp, 0xfffffff4u, 4, edx);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_487630;
    esi = esi ^ esi;
L_4875cf:
    eax = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, esi, eax + 0x0u, 4, 0x0u);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0x2cu, 1)) & 0xffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0x25u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0x21u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0x20u, 1)) & 0xffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, ebp, 0x1cu, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0x18u, 4);
    edx = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0x10u, 4);
    ebx = lift_load(&env, ebp, 0x8u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0xcu, 4);
    esi = esi + 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x483060u, eax, edx, ebx, ecx, 8, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 32u;
    edx = lift_load(&env, edi, 0x0u, 4);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, edx, esi + 0xfffffffcu, 4, eax);
    ebx = ebx + 1u;
    edx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.cf)
        goto L_4875cf;
L_487630:
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

uint32_t lifted_object_construct_e(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_CONSTRUCT_E_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_CONSTRUCT_E_STACK, 0, entry);
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
    esp = esp - 0x30u;
    edx = eax;
    eax = (ebp + 0xffffffbcu);
    ecx = 0x4ec1ecu;
    ebx = 0x517008u;
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
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffc4u, 4, ebx);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffc8u, 4, esi);
    lift_store(&env, ebp, 0xffffffe4u, 1, ((eax >> 8) & 0xffu));
    eax = edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d7510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc8u, 4, edi);
    ecx = eax;
    lift_store(&env, eax, 0x0u, 4, 0x5174b4u);
    eax = (ebp + 0xffffffd0u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d7510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffc8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d7630u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, edi);
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
}

uint32_t lifted_f488c50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F488C50_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F488C50_STACK, 0, entry);
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
    esp = esp - 0x4cu;
    esi = eax;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    eax = (ebp + 0xffffffb8u);
    edx = 0x4ec1ecu;
    ecx = 0x517038u;
    edi = 0x3u;
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
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffc8u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffbcu, 4, edx);
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffc4u, 4, ebx);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) & 0xfeu) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    lift_store(&env, ebp, 0xffffffc8u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, ebp, 0xffffffdcu, 1, (edx & 0xffu));
    eax = (ebp + 0xffffffa4u);
    edx = 0x517494u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffb4u);
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x4u;
    edi = 0x1u;
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    lift_store(&env, ebp, 0xffffffacu, 4, ebx);
    ebx = 0xffffffffu;
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    edx = edx ^ edx;
    eax = (ebp + 0xffffffb4u);
    lift_store(&env, ebp, 0xffffffb0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    ecx = (ebp + 0xffffffa4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    ebx = 0x8000u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = esi;
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x28u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_488d51;
    edi = 0x1u;
L_488cff:
    ecx = 0x517494u;
    eax = (ebp + 0xffffffa4u);
    ebx = 0x8u;
    esi = 0x517454u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffa4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    lift_store(&env, ebp, 0xffffffdcu, 1, (edx & 0xffu));
    eax = (ebp + 0xffffffb4u);
    lift_store(&env, ebp, 0xffffffc4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edx = (ebp + 0xffffffa4u);
    lift_store(&env, ebp, 0xffffffd0u, 1, (eax & 0xffu));
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, esi);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
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
L_488d51:
    edx = (ebp + 0xffffffa4u);
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x488d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc4u, 4, 0x1u);
    goto L_488cff;
}

uint32_t lifted_object_kind_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_KIND_TEXT_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_KIND_TEXT_STACK, 0, entry);
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
    ebx = edx;
    eax = (ebp + 0xffffffdcu);
    edx = 0x4ec1ecu;
    esi = 0x5170bcu;
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
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    eax = ecx;
    edx = 0x510737u;
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebx, 0x8u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_488e5e;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_488e7e;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_488e9e;
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (fl.zf)
        goto L_488ebe;
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.zf)
        goto L_488ede;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.zf)
        goto L_488efe;
    {
        (void)lift_sub(32, eax, 0x6u, &fl);
    }
    if (fl.zf)
        goto L_488f1e;
    {
        (void)lift_sub(32, eax, 0x7u, &fl);
    }
    if (fl.zf)
        goto L_488f3e;
    {
        (void)lift_sub(32, eax, 0x8u, &fl);
    }
    if (fl.zf)
        goto L_488f5e;
    {
        (void)lift_sub(32, eax, 0x9u, &fl);
    }
    if (fl.zf)
        goto L_488f7e;
    {
        (void)lift_sub(32, eax, 0xau, &fl);
    }
    if (fl.zf)
        goto L_488f9e;
    {
        (void)lift_sub(32, eax, 0xbu, &fl);
    }
    if (fl.zf)
        goto L_488fbe;
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (fl.zf)
        goto L_488fde;
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (fl.zf)
        goto L_488ffe;
    {
        (void)lift_sub(32, eax, 0xeu, &fl);
    }
    if (fl.zf)
        goto L_48901e;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488e5e:
    edx = 0x510755u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488e7e:
    edx = 0x510768u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488e9e:
    edx = 0x510787u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488ebe:
    edx = 0x5107a6u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488ede:
    edx = 0x5107cau;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488efe:
    edx = 0x5107fbu;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488f1e:
    edx = 0x51081bu;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488f3e:
    edx = 0x51084fu;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488f5e:
    edx = 0x510880u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488f7e:
    edx = 0x5108a5u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488f9e:
    edx = 0x5108d8u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488fbe:
    edx = 0x5108f4u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488fde:
    edx = 0x51092du;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_488ffe:
    edx = 0x51096du;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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
L_48901e:
    edx = 0x51097fu;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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

uint32_t lifted_find_succeeded(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_FIND_SUCCEEDED_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_FIND_SUCCEEDED_STACK, 0, entry);
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
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
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

uint32_t lifted_f489640(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F489640_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F489640_STACK, 1, entry);
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
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    lift_store(&env, ebp, 0xfffffff0u, 4, ecx);
    edi = 0x5b9cd0u;
    ecx = 0x5b9ee0u;
    esi = eax;
    ebx = 0x5b9de0u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_489663:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48967b;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_489663;
L_48967b:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t v = 0x5b9fe0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x5b9dd8u;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4daae8u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4896c9;
L_489693:
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4896a6;
    edx = 0x5b9de0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4896a6:
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4896b9;
    edx = 0x5b9ee0u;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4896b9:
    esi = lift_load(&env, ebp, 0x8u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4896d8;
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
L_4896c9:
    edx = 0x5b9dd8u;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_489693;
L_4896d8:
    edx = 0x5b9fe0u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f48a050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48A050_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48A050_STACK, 0, entry);
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
    esp = esp - 0x128u;
    esi = eax;
    eax = (ebp + 0xffffffdcu);
    ecx = 0x4ec1ecu;
    ebx = 0x5175bcu;
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
    eax = (ebp + 0xfffffec8u);
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    ebx = lift_load(&env, 0u, 0x5466c8u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = (ebp + 0xfffffec8u);
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_48a0da;
L_48a0b1:
    eax = (ebp + 0xfffffec8u);
    edx = edx ^ edx;
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
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
L_48a0da:
    edx = (ebp + 0xfffffec8u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a100u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = (ebp + 0xfffffec8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a8c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_48a0b1;
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

uint32_t lifted_stream_read_token(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_STREAM_READ_TOKEN_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_STREAM_READ_TOKEN_STACK, 0, entry);
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
    ecx = edx;
    esi = ebx;
    edx = 0x510a59u;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48a3d2:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48a3ee;
L_48a3dd:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce030u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_48a3ee:
    eax = ecx;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aa80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aa90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x5cu, &fl);
    }
    if (fl.zf)
        goto L_48a3dd;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xau, &fl);
    }
    if (fl.zf)
        goto L_48a3dd;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xdu, &fl);
    }
    if (fl.zf)
        goto L_48a3dd;
    edx = edx ^ edx;
    eax = esi;
    edx = (edx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca630u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_48a3d2;
}

uint32_t lifted_list_parse_texts(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_LIST_PARSE_TEXTS_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_LIST_PARSE_TEXTS_STACK, 1, entry);
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
    edi = eax;
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    eax = (ebp + 0xffffffd4u);
    ecx = 0x4ec1ecu;
    ebx = 0x5175fcu;
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
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
L_48a4da:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xfffffff4u, 2)) & 0xffffu);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.cf)
        goto L_48a4f6;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
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
L_48a4f6:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (!fl.cf)
        goto L_48a545;
    edx = esi;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0x8u, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_48a545;
    ecx = edx;
    ebx = esi;
    eax = edi;
    edx = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a300u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    edx = eax;
    ebx = ebx ^ ebx;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe8u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    goto L_48a550;
L_48a545:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48a550:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = edx + 0x4u;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    goto L_48a4da;
}

uint32_t lifted_list_parse_values(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_LIST_PARSE_VALUES_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_LIST_PARSE_VALUES_STACK, 1, entry);
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
    edi = eax;
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    eax = (ebp + 0xffffffd4u);
    ecx = 0x4ec1ecu;
    ebx = 0x517608u;
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
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
L_48a59a:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xfffffff4u, 2)) & 0xffffu);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.cf)
        goto L_48a5b6;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
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
L_48a5b6:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.cf)
        goto L_48a5cb;
L_48a5c1:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    goto L_48a60e;
L_48a5cb:
    edx = esi;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0x8u, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_48a5c1;
    ecx = edx;
    ebx = esi;
    eax = edi;
    edx = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a300u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, 0x1u);
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = (ebp + 0xffffffe8u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
L_48a60e:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = edx + 0x4u;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    goto L_48a59a;
}

uint32_t lifted_stream_read_exact(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_STREAM_READ_EXACT_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_STREAM_READ_EXACT_STACK, 0, entry);
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
    esp = esp - 0x4u;
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    {
        uint32_t r = lift_imul(32, ebx, ecx, &fl);
        ebx = r;
    }
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, 0u, 0x5bb234u, 4, ebx);
    ebx = lift_load(&env, ecx, 0x4u, 4);
    eax = eax - ebx;
    lift_store(&env, 0u, 0x5bb238u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb234u, 4);
    esi = lift_load(&env, 0u, 0x5bb238u, 4);
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_48a986;
    edi = 0x1u;
    ebx = eax;
    lift_store(&env, 0u, 0x5bb230u, 4, edi);
L_48a970:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_48a991;
    eax = lift_load(&env, 0u, 0x5bb230u, 4);
    lift_store(&env, 0u, 0x5bb22cu, 4, ebx);
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
L_48a986:
    eax = eax ^ eax;
    ebx = esi;
    lift_store(&env, 0u, 0x5bb230u, 4, eax);
    goto L_48a970;
L_48a991:
    esi = lift_load(&env, ebp, 0xfffffff4u, 4);
    ecx = ebx;
    edi = edx;
    lift_store(&env, 0u, 0x5bb22cu, 4, ebx);
    esi = lift_load(&env, esi, 0x4u, 4);
    edx = lift_load(&env, ebp, 0xfffffff4u, 4);
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
    ebx = lift_load(&env, 0u, 0x5bb22cu, 4);
    {
        uint32_t r = lift_add(32, lift_load(&env, edx, 0x4u, 4), ebx, &fl);
        lift_store(&env, edx, 0x4u, 4, r);
    }
    eax = lift_load(&env, 0u, 0x5bb230u, 4);
    lift_store(&env, 0u, 0x5bb22cu, 4, ebx);
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

uint32_t lifted_f48ac10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48AC10_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48AC10_STACK, 0, entry);
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
    esp = esp - 0xc8u;
    ecx = lift_load(&env, eax, 0x0u, 4);
    ebx = ecx;
    edx = (ebp + 0xffffff2cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = (ecx + 0x84u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9f45u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = (ebp + 0xfffffff4u);
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

uint32_t lifted_f4aa660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4AA660_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4AA660_STACK, 0, entry);
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
    esp = esp - 0x4u;
    edx = lift_load(&env, 0u, 0x5bb774u, 4);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    esi = lift_load(&env, 0u, 0x5bb778u, 4);
    ebp = lift_load(&env, 0u, 0x54d5d0u, 4);
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x5bb752u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4aa7c7;
L_4aa690:
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aa7a7;
L_4aa6a0:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    eax = esi;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xe0u) & 0xffu);
    ecx = edx;
    ecx = ecx & 0xffu;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        ecx = r;
    }
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x1cu) & 0xffu);
    edx = edx & 0xffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        edx = r;
    }
    ecx = ecx | edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x3u) & 0xffu);
    edx = edx & 0xffu;
    edx = edx | ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    esi = edx;
    ecx = edx;
    esi = esi & 0xfc0000u;
    ecx = ecx & 0xfc00u;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        esi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    edx = edx & 0xfcu;
    ecx = ecx | esi;
    edx = edx | ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        edx = r;
    }
    ecx = ((edx * 4u));
    edx = lift_load(&env, 0u, 0x54b800u, 4);
    edx = lift_load(&env, ecx, edx + 0x0u, 4);
    lift_store(&env, 0u, 0x54d5d4u, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x54d5d4u, 1)) & 0xffu);
    ecx = ((edx * 4u));
    edx = lift_load(&env, 0u, 0x54cdc8u, 4);
    ebp = lift_load(&env, ecx, edx + 0x0u, 4);
    ecx = lift_load(&env, 0u, 0x54d5d4u, 4);
    edx = lift_load(&env, 0u, 0x54d5d4u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x0u, 4, ecx);
    edi = (edx & 0xffu);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    edx = ebp;
    esi = (ecx & 0xffu);
    edi = lift_load(&env, edx, edi + 0x0u, 1);
    esi = lift_load(&env, edx, esi + 0x0u, 1);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        esi = r;
    }
    esi = esi | edi;
    edi = edi ^ edi;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5d4u, 2)) & 0xffffu);
    ecx = edi;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ecx = r;
    }
    edi = (ecx & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, edi + 0x0u, 1)) & 0xffu);
    edx = edx & 0xffu;
    edx = edx | esi;
    edi = edx;
    esi = edx;
    edi = edi & 0xe00000u;
    esi = esi & 0xe000u;
    {
        uint32_t a = edi;
        uint32_t r = lift_shr(32, a, 0xau, &fl);
        edi = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x5u, &fl);
        esi = r;
    }
    esi = esi | edi;
    edi = edx;
    edi = edi & 0xc0u;
    esi = esi | edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        esi = r;
    }
    lift_store(&env, esp, 0x0u, 4, esi);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    esi = (eax + 0x1u);
    lift_store(&env, eax, 0x0u, 1, (ecx & 0xffu));
    {
        uint32_t a = (ebx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ebx = (ebx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4aa6a0;
L_4aa7a7:
    eax = esi;
    esi = lift_load(&env, 0u, 0x5bb7c8u, 4);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t a = (edi & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb752u, 2, (edi & 0xffffu));
    if (!fl.zf)
        goto L_4aa690;
L_4aa7c7:
    lift_store(&env, 0u, 0x54d5d0u, 4, ebp);
    lift_store(&env, 0u, 0x5bb778u, 4, esi);
    lift_store(&env, 0u, 0x5bc016u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bb774u, 4, edx);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4aa950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4AA950_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4AA950_STACK, 0, entry);
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
    edx = lift_load(&env, 0u, 0x5bb774u, 4);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    esi = lift_load(&env, 0u, 0x5bb778u, 4);
    edi = lift_load(&env, 0u, 0x54d5ecu, 4);
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x5bb752u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4aaa15;
L_4aa97f:
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aa9f7;
L_4aa98b:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xe0u) & 0xffu);
    eax = esi;
    esi = (edx & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        esi = r;
    }
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x1cu) & 0xffu);
    edx = edx & 0xffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        edx = r;
    }
    esi = esi | edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x3u) & 0xffu);
    edx = edx & 0xffu;
    esi = esi | edx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        esi = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        esi = r;
    }
    esi = esi & 0x7f7f7fu;
    edx = (edi + esi);
    ecx = edx;
    esi = edx;
    ecx = ecx & 0xe00000u;
    esi = esi & 0xe000u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0xau, &fl);
        ecx = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x5u, &fl);
        esi = r;
    }
    esi = esi | ecx;
    ecx = edx;
    ecx = ecx & 0xc0u;
    ecx = ecx | esi;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        ecx = r;
    }
    lift_store(&env, esp, 0x0u, 4, ecx);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    esi = (eax + 0x1u);
    lift_store(&env, eax, 0x0u, 1, (ecx & 0xffu));
    {
        uint32_t a = (ebx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ebx = (ebx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4aa98b;
L_4aa9f7:
    eax = esi;
    esi = lift_load(&env, 0u, 0x5bb7c8u, 4);
    {
        uint32_t r = lift_add(32, esi, eax, &fl);
        esi = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    {
        uint32_t a = (eax & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb752u, 2, (eax & 0xffffu));
    if (!fl.zf)
        goto L_4aa97f;
L_4aaa15:
    lift_store(&env, 0u, 0x54d5ecu, 4, edi);
    lift_store(&env, 0u, 0x5bb778u, 4, esi);
    lift_store(&env, 0u, 0x5bc016u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bb774u, 4, edx);
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

uint32_t lifted_f4aabe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4AABE0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4AABE0_STACK, 0, entry);
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
    esp = esp - 0x4u;
    edx = lift_load(&env, 0u, 0x5bb774u, 4);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    esi = lift_load(&env, 0u, 0x5bb778u, 4);
    ebp = lift_load(&env, 0u, 0x54d5d0u, 4);
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x5bb752u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4aad62;
L_4aac10:
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aad42;
L_4aac20:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    eax = esi;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xe0u) & 0xffu);
    ecx = edx;
    ecx = ecx & 0xffu;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        ecx = r;
    }
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x1cu) & 0xffu);
    edx = edx & 0xffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        edx = r;
    }
    ecx = ecx | edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x3u) & 0xffu);
    edx = edx & 0xffu;
    edx = edx | ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    ecx = lift_load(&env, 0u, 0x54d5ecu, 4);
    edx = edx & 0x7f7f7fu;
    edx = edx + ecx;
    esi = edx;
    ecx = edx;
    esi = esi & 0xfc0000u;
    ecx = ecx & 0xfc00u;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        esi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    edx = edx & 0xfcu;
    ecx = ecx | esi;
    edx = edx | ecx;
    ecx = lift_load(&env, 0u, 0x54b800u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        edx = r;
    }
    edx = lift_load(&env, ecx, (edx * 4u) + 0x0u, 4);
    lift_store(&env, 0u, 0x54d5d4u, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x54d5d4u, 1)) & 0xffu);
    ecx = ((edx * 4u));
    edx = lift_load(&env, 0u, 0x54cdc8u, 4);
    ebp = lift_load(&env, ecx, edx + 0x0u, 4);
    edx = lift_load(&env, 0u, 0x54d5d4u, 4);
    ecx = ecx ^ ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        edx = r;
    }
    ecx = (ecx & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    edx = ebp;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, edx + 0x0u, 1)) & 0xffu);
    edi = ecx;
    ecx = lift_load(&env, 0u, 0x54d5d4u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ecx = r;
    }
    edi = edi & 0xffu;
    lift_store(&env, esp, 0x0u, 4, ecx);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        edi = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    esi = lift_load(&env, ecx, edx + 0x0u, 1);
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5d4u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ecx = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        esi = r;
    }
    lift_store(&env, esp, 0x0u, 4, ecx);
    esi = esi | edi;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, edx + 0x0u, 1)) & 0xffu);
    edx = edx & 0xffu;
    edx = edx | esi;
    edi = edx;
    ecx = edx;
    esi = edx;
    edi = edi & 0xe00000u;
    ecx = ecx & 0xe000u;
    {
        uint32_t a = edi;
        uint32_t r = lift_shr(32, a, 0xau, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x5u, &fl);
        ecx = r;
    }
    esi = esi & 0xc0u;
    ecx = ecx | edi;
    ecx = ecx | esi;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        ecx = r;
    }
    lift_store(&env, esp, 0x0u, 4, ecx);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    esi = (eax + 0x1u);
    lift_store(&env, eax, 0x0u, 1, (ecx & 0xffu));
    {
        uint32_t a = (ebx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ebx = (ebx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4aac20;
L_4aad42:
    eax = esi;
    esi = lift_load(&env, 0u, 0x5bb7c8u, 4);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t a = (edi & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb752u, 2, (edi & 0xffffu));
    if (!fl.zf)
        goto L_4aac10;
L_4aad62:
    lift_store(&env, 0u, 0x54d5d0u, 4, ebp);
    lift_store(&env, 0u, 0x5bb778u, 4, esi);
    lift_store(&env, 0u, 0x5bc016u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bb774u, 4, edx);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_actor_gate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_GATE_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_GATE_STACK, 0, entry);
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
    esp = esp - 0xcu;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68eu, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = lift_load(&env, eax, 0x13cu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4aec54;
L_4ae40c:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    eax = lift_load(&env, eax, 0xb4u, 4);
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb734u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4af1fc;
    ebx = lift_load(&env, 0u, 0x5bc010u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4aec63;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x27u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb731u, 1, (edx & 0xffu));
    edx = ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebx, 0xcu, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0xdu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb732u, 1, (ebx & 0xffu));
    lift_store(&env, 0u, 0x5bb733u, 1, (edx & 0xffu));
    {
        (void)lift_sub(8, (edx & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4aec63;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0xeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a4u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bb740u, 2, (edx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0x16u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a6u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bb742u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (edx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0x1eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7aeu, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0xcu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x10u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b2u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b4u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x26u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bbfffu, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x93u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb739u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb790u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, 0u, 0x5bb7b6u, 2, (edx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x94u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x8fu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc00cu, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, 0u, 0x5bc005u, 1, (edx & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x95u, 1)) & 0xffu);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, 0u, 0x5bc00du, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x8eu, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x4eu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bbffeu, 1, (edx & 0xffu));
    lift_store(&env, 0u, 0x5bc00eu, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x64u, &fl);
    }
    if (!fl.zf)
        goto L_4ae552;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) ^ (ebx & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x5bb739u, 1, (ebx & 0xffu));
L_4ae552:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x8cu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb73au, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x80u, 1)) & 0xffu);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, 0u, 0x5bb7b8u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4ae5db;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x208u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb744u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x20cu, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb746u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x214u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    ebx = ebx - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x216u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x226u, 2)) & 0xffffu);
    ecx = ecx - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (ebx & 0xffffu));
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bb7aeu, 2, (edx & 0xffffu));
L_4ae5db:
    ebx = (ebx & 0xffff00ffu) | (((0xdu) & 0xffu) << 8);
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, 0u, 0x5bb730u, 1, ((ebx >> 8) & 0xffu));
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4ae668;
    eax = lift_load(&env, 0u, 0x5bb73eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aec6a;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb740u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb744u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ae619;
    eax = ebx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb740u, 2, (eax & 0xffffu));
L_4ae619:
    eax = lift_load(&env, 0u, 0x5bb740u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aec78;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb742u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb746u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ae644;
    eax = edx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb742u, 2, (eax & 0xffffu));
L_4ae644:
    edx = lift_load(&env, 0u, 0x5bb742u, 4);
    eax = lift_load(&env, 0u, 0x5bb740u, 4);
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
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = lift_load(&env, 0u, 0x5bb73eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb73cu, 4, edx);
L_4ae668:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4aec86;
L_4ae672:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x44u, 1)) & 0xffu);
L_4ae678:
    lift_store(&env, 0u, 0x5bb738u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bb738u, 1), 0x10u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, 0u, 0x5bb694u, 4, eax);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4aecc8;
L_4ae69d:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x52u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x48u, 2)) & 0xffffu);
L_4ae6af:
    lift_store(&env, 0u, 0x5bc002u, 2, (eax & 0xffffu));
L_4ae6b5:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb694u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4aed56;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb74cu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb74eu, 2, (eax & 0xffffu));
L_4ae6da:
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74cu, 2)) & 0xffffu);
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aec63;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    {
        (void)lift_and(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aec63;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b0u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb750u, 2, (ebx & 0xffffu));
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    edx = edx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb752u, 2, (ecx & 0xffffu));
    ebx = ebx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    ecx = ebx;
    lift_store(&env, 0u, 0x5bb7a0u, 2, (edx & 0xffffu));
    ecx = ecx - eax;
    eax = edx;
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) + lift_load(&env, 0u, 0x5bb74cu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ebx & 0xffffu));
    eax = eax - 1u;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb748u, 2, (eax & 0xffffu));
    eax = ecx;
    eax = eax + ebx;
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ecx & 0xffffu));
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bbff4u, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bb74au, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bbffeu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bbff2u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ae80a;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4aee2d;
    ebx = ebx ^ ebx;
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    lift_store(&env, 0u, 0x5bbff6u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bbffau, 2, (ebx & 0xffffu));
L_4ae7a7:
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    edx = edx - 1u;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bbff8u, 2, (edx & 0xffffu));
L_4ae7b8:
    lift_store(&env, 0u, 0x5bbffcu, 2, (eax & 0xffffu));
L_4ae7be:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff8u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4aec63;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aec63;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffcu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4aec63;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffau, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aec63;
L_4ae80a:
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x5bc014u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bbffeu, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ae8f4;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffau, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ae86e;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb694u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ae85a;
    edx = lift_load(&env, 0u, 0x5bbff8u, 4);
    eax = lift_load(&env, 0u, 0x5bb7a0u, 4);
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
    eax = lift_load(&env, 0u, 0x5bb74au, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb790u, 4, lift_load(&env, 0u, 0x5bb790u, 4) + eax);
L_4ae85a:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffau, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, (edx & 0xffu));
L_4ae86e:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ae8b3;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb694u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ae89f;
    edx = lift_load(&env, 0u, 0x5bbff4u, 4);
    eax = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    lift_store(&env, 0u, 0x5bb790u, 4, lift_load(&env, 0u, 0x5bb790u, 4) + edx);
L_4ae89f:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff6u, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, ((edx >> 8) & 0xffu));
L_4ae8b3:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffcu, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ae8d4;
    ebx = (ebx & 0xffffff00u) | ((0x1u) & 0xffu);
    lift_store(&env, 0u, 0x5bb74au, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, (ebx & 0xffu));
L_4ae8d4:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff8u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ae8f4;
    lift_store(&env, 0u, 0x5bb748u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, 0x1u);
L_4ae8f4:
    edx = edx ^ edx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bc014u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb79cu, 4, edx);
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4ae967;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) - lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    eax = eax + 1u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb750u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    eax = eax - edx;
    eax = eax + 1u;
    edx = lift_load(&env, 0u, 0x5bb74au, 4);
    lift_store(&env, 0u, 0x5bb752u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x5bb74eu, 4);
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
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb79cu, 4, edx);
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aec63;
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x5bb752u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4aec63;
L_4ae967:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb694u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4aeab0;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb738u, 1)) & 0xffu);
    edx = 0x5c1c00u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        eax = r;
    }
    edx = edx + eax;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, 0u, 0x5bc014u, 1)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb7d4u, 4, edx);
    lift_store(&env, 0u, 0x5bb7d8u, 4, edx);
    {
        (void)lift_and(8, ((ecx >> 8) & 0xffu), ((ecx >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4aea50;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68au, 2, (eax & 0xffffu));
    if (fl.zf)
        goto L_4aea06;
    ecx = ecx ^ ecx;
    lift_store(&env, 0u, 0x5bb690u, 2, (ecx & 0xffffu));
L_4ae9c0:
    eax = lift_load(&env, 0u, 0x5bb7d4u, 4);
    eax = eax + 1u;
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xffffffffu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb7d4u, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb690u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68au, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb690u, 2, (eax & 0xffffu));
    {
        uint32_t a = (edx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edx = (edx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68au, 2, (edx & 0xffffu));
    if (!fl.zf)
        goto L_4ae9c0;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb790u, 4, lift_load(&env, 0u, 0x5bb790u, 4) + eax);
L_4aea06:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff2u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(16, (eax & 0xffffu), (ecx & 0xffffu), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68au, 2, (eax & 0xffffu));
    if (fl.zf)
        goto L_4aea50;
L_4aea1e:
    eax = lift_load(&env, 0u, 0x5bb7d8u, 4);
    eax = eax + 1u;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xffffffffu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb7d8u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb790u, 4);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68au, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb790u, 4, eax);
    {
        uint32_t a = (edx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edx = (edx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68au, 2, (edx & 0xffffu));
    if (!fl.zf)
        goto L_4aea1e;
L_4aea50:
    eax = lift_load(&env, 0u, 0x5bb7d4u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, 0u, 0x5bb7ccu, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7e0u, 2, (ecx & 0xffffu));
    {
        uint32_t a = (eax & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68au, 2, (eax & 0xffffu));
    if (fl.zf)
        goto L_4aeab0;
L_4aea73:
    eax = lift_load(&env, 0u, 0x5bb7ccu, 4);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7e0u, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68au, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = eax + 1u;
    {
        uint32_t r = lift_add(32, ebx, edx, &fl);
        ebx = r;
    }
    lift_store(&env, 0u, 0x5bb7ccu, 4, eax);
    lift_store(&env, 0u, 0x5bb7e0u, 2, (ebx & 0xffffu));
    {
        uint32_t a = (ecx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68au, 2, (ecx & 0xffffu));
    if (!fl.zf)
        goto L_4aea73;
L_4aeab0:
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, 0u, 0x5bb68eu, 2, (esi & 0xffffu));
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x5bc016u, 2, (edi & 0xffffu));
    lift_store(&env, 0u, 0x5bbff0u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4af21c;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x274u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4af21c;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bc005u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4af21c;
    ebx = lift_load(&env, 0u, 0x5bb74eu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    eax = 0x5bb7ecu;
    ebx = ebx + ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a6u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b2u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    eax = eax - edx;
    eax = eax + ebx;
    eax = eax - 1u;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7aau, 2, (eax & 0xffffu));
    eax = eax - ecx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a8u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, 0u, 0x5bb7aau, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4aeb49;
    lift_store(&env, 0u, 0x5bb7aau, 2, (edx & 0xffffu));
L_4aeb49:
    eax = lift_load(&env, 0u, 0x5bb7a8u, 4);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68eu, 2)) & 0xffffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aee93;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aau, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb746u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aeb82;
    eax = ebx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb7aau, 2, (eax & 0xffffu));
L_4aeb82:
    eax = lift_load(&env, 0u, 0x5bb7a6u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aeea1;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a8u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb746u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aebad;
    eax = edx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb7a8u, 2, (eax & 0xffffu));
L_4aebad:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aau, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) - lift_load(&env, 0u, 0x5bb7a8u, 2)) & 0xffffu);
    eax = eax + 1u;
    lift_store(&env, 0u, 0x5bb7acu, 2, (eax & 0xffffu));
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb68cu, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb68au, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x544070u, 4);
    ecx = lift_load(&env, 0u, 0x5bb79eu, 4);
    edx = lift_load(&env, eax, 0x274u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x214u, 2)) & 0xffffu);
    edx = edx + ecx;
    eax = eax & 0xffffu;
    ecx = (edx + eax);
    edx = lift_load(&env, 0u, 0x5bb742u, 4);
    eax = lift_load(&env, 0u, 0x5bb7a8u, 4);
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
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    ecx = ecx + eax;
    eax = lift_load(&env, 0u, 0x5bb7aau, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb7ccu, 4, ecx);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4aef1f;
    ebx = (ebx & 0xffffff00u) | ((0x3u) & 0xffu);
L_4aec25:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68au, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb750u, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4aef74;
    eax = lift_load(&env, 0u, 0x5bb7ccu, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x0u, 1), (ebx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4aeeaf;
L_4aec45:
    lift_store(&env, 0u, 0x5bb7ccu, 4, lift_load(&env, 0u, 0x5bb7ccu, 4) + 1u);
    lift_store(&env, 0u, 0x5bb68au, 2, lift_load(&env, 0u, 0x5bb68au, 2) + 1u);
    goto L_4aec25;
L_4aec54:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    goto L_4ae40c;
L_4aec63:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    goto L_4af1fc;
L_4aec6a:
    ecx = ecx ^ ecx;
    lift_store(&env, 0u, 0x5bb740u, 2, (ecx & 0xffffu));
    goto L_4ae619;
L_4aec78:
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x5bb742u, 2, (ebx & 0xffffu));
    goto L_4ae644;
L_4aec86:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x91u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ae672;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x220u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4aecaf;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x221u, 1)) & 0xffu);
    goto L_4ae678;
L_4aecaf:
    eax = lift_load(&env, eax, 0x270u, 4);
    edx = lift_load(&env, 0u, 0x5bb73cu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) + 1u) & 0xffu);
    goto L_4ae678;
L_4aecc8:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x92u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ae69d;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x222u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4aed05;
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x223u, 1)) & 0xffffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x224u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc002u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    goto L_4ae6b5;
L_4aed05:
    eax = lift_load(&env, eax, 0x26cu, 4);
    ebx = lift_load(&env, 0u, 0x5bb73cu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + ebx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc004u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bc004u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bc004u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x7u) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - 0x5u) & 0xffu);
    edx = (edx & 0xffff0000u) | (((uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu)) & 0xffffu);
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    lift_store(&env, 0u, 0x5bc002u, 2, (edx & 0xffffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aed4e;
    {
        uint32_t r = lift_imul(32, edx, 0x28u, &fl);
        eax = r;
    }
    goto L_4ae6af;
L_4aed4e:
    {
        uint32_t r = lift_imul(32, edx, 0x14u, &fl);
        eax = r;
    }
    goto L_4ae6af;
L_4aed56:
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    eax = eax ^ eax;
    edx = ecx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb738u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x5bb74cu, 2, (edx & 0xffffu));
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = ecx;
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((ecx >> 8) & 0xffu)) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xfu) & 0xffu);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = edx & 0xffffu;
    edx = edx + ebx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x5c1b00u, 1)) & 0xffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74cu, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    ebx = ebx + edx;
    lift_store(&env, 0u, 0x5bb74cu, 2, (ebx & 0xffffu));
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    edx = ebx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb74eu, 2, (eax & 0xffffu));
    eax = ebx;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax & 0xffffu;
    eax = eax + edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x5c1b00u, 1)) & 0xffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x5bb74au, 4);
    lift_store(&env, 0u, 0x5bb74eu, 2, (edx & 0xffffu));
    edx = lift_load(&env, 0u, 0x5bb7aeu, 4);
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
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    edx = lift_load(&env, 0u, 0x5bb74cu, 4);
    lift_store(&env, 0u, 0x5bb7b0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x5bb7b0u, 4);
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
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    lift_store(&env, 0u, 0x5bb7b2u, 2, (eax & 0xffffu));
    goto L_4ae6da;
L_4aee2d:
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4aee4b;
    ecx = ecx ^ ecx;
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    lift_store(&env, 0u, 0x5bbff6u, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bbffau, 2, (ecx & 0xffffu));
    goto L_4ae7a7;
L_4aee4b:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4ae7be;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xa8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaau, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xacu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbffau, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaeu, 2)) & 0xffffu);
    goto L_4ae7b8;
L_4aee93:
    ecx = ecx ^ ecx;
    lift_store(&env, 0u, 0x5bb7aau, 2, (ecx & 0xffffu));
    goto L_4aeb82;
L_4aeea1:
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x5bb7a8u, 2, (ebx & 0xffffu));
    goto L_4aebad;
L_4aeeaf:
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7acu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7d0u, 4, eax);
    {
        (void)lift_and(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aeedf;
L_4aeec0:
    eax = lift_load(&env, 0u, 0x5bb7d0u, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x0u, 1), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4aeedf;
    edx = lift_load(&env, 0u, 0x5bb742u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = eax - edx;
    esi = esi - 1u;
    lift_store(&env, 0u, 0x5bb7d0u, 4, eax);
    {
        (void)lift_and(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4aeec0;
L_4aeedf:
    {
        (void)lift_and(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4aec45;
    edx = 0x1u;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68cu, 2)) & 0xffffu);
    eax = lift_load(&env, 0u, 0x5bb688u, 4);
    ecx = ecx + edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb68cu, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, (eax * 2u) + 0x5bb7ecu, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bb7ccu, 4, lift_load(&env, 0u, 0x5bb7ccu, 4) + 1u);
    lift_store(&env, 0u, 0x5bb68au, 2, lift_load(&env, 0u, 0x5bb68au, 2) + 1u);
    goto L_4aec25;
L_4aef1f:
    ecx = 0x1u;
L_4aef24:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68au, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb750u, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4aef74;
    eax = lift_load(&env, 0u, 0x5bb7ccu, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x0u, 1), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4aef5b;
L_4aef3d:
    ebx = lift_load(&env, 0u, 0x5bb7ccu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68au, 2)) & 0xffffu);
    ebx = ebx + 1u;
    edx = edx + 1u;
    lift_store(&env, 0u, 0x5bb7ccu, 4, ebx);
    lift_store(&env, 0u, 0x5bb68au, 2, (edx & 0xffffu));
    goto L_4aef24;
L_4aef5b:
    eax = lift_load(&env, 0u, 0x5bb688u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, (eax * 2u) + 0x5bb7ecu, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bb68cu, 2, lift_load(&env, 0u, 0x5bb68cu, 2) + (ecx & 0xffffu));
    goto L_4aef3d;
L_4aef74:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68cu, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb68eu, 2, (esi & 0xffffu));
    lift_store(&env, 0u, 0x5bc016u, 2, (edi & 0xffffu));
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4af213;
L_4aef98:
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff0u, 1, (ecx & 0xffu));
L_4aefae:
    eax = lift_load(&env, 0u, 0x544070u, 4);
    ecx = lift_load(&env, 0u, 0x5bb79eu, 4);
    edx = lift_load(&env, eax, 0x274u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edx = lift_load(&env, edx, 0x0u, 4);
    ecx = ecx + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x214u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x216u, 2)) & 0xffffu);
    ecx = ecx + edx;
    edx = lift_load(&env, 0u, 0x5bb748u, 4);
    eax = eax & 0xffffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x5bb742u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    edx = 0x5bb7ecu;
    ecx = ecx + eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7e4u, 4, ecx);
    lift_store(&env, 0u, 0x5bbfecu, 4, edx);
    lift_store(&env, 0u, 0x5bb68cu, 2, (eax & 0xffffu));
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4af09a;
L_4af01b:
    eax = lift_load(&env, 0u, 0x5bbfecu, 4);
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4af06e;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    edx = lift_load(&env, 0u, 0x5bb7e4u, 4);
    lift_store(&env, eax, 0x0u, 2, 0x0u);
    lift_store(&env, 0u, 0x5bb7e8u, 4, edx);
    {
        (void)lift_and(16, (edi & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4af06e;
L_4af043:
    eax = lift_load(&env, 0u, 0x5bb7e8u, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x0u, 1), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4af06e;
    ecx = lift_load(&env, 0u, 0x5bb742u, 4);
    edx = lift_load(&env, 0u, 0x5bbfecu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(32, eax, ecx, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    lift_store(&env, 0u, 0x5bb7e8u, 4, eax);
    lift_store(&env, edx, 0x0u, 2, (ebx & 0xffffu));
    {
        uint32_t a = (edi & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4af043;
L_4af06e:
    ecx = lift_load(&env, 0u, 0x5bb7e4u, 4);
    ebx = lift_load(&env, 0u, 0x5bbfecu, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68cu, 2)) & 0xffffu);
    ecx = ecx + 1u;
    {
        uint32_t r = lift_add(32, ebx, 0x2u, &fl);
        ebx = r;
    }
    lift_store(&env, 0u, 0x5bb7e4u, 4, ecx);
    lift_store(&env, 0u, 0x5bbfecu, 4, ebx);
    {
        uint32_t a = (eax & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68cu, 2, (eax & 0xffffu));
    if (!fl.zf)
        goto L_4af01b;
L_4af09a:
    eax = lift_load(&env, 0u, 0x544070u, 4);
    ecx = lift_load(&env, 0u, 0x5bb79eu, 4);
    edx = lift_load(&env, eax, 0x274u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edx = lift_load(&env, edx, 0x0u, 4);
    ecx = ecx + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x214u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x216u, 2)) & 0xffffu);
    ecx = ecx + edx;
    edx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    eax = eax & 0xffffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, 0u, 0x5bb742u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    ecx = ecx + eax;
    lift_store(&env, 0u, 0x5bb7e4u, 4, ecx);
    lift_store(&env, 0u, 0x5bb7e8u, 4, ecx);
L_4af0ee:
    eax = lift_load(&env, 0u, 0x5bb790u, 4);
    edx = lift_load(&env, 0u, 0x5bb734u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = lift_load(&env, edx, 0x0u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    lift_store(&env, 0u, 0x5bb764u, 4, edx);
    lift_store(&env, 0u, 0x5bb76cu, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb798u, 2, (edx & 0xffffu));
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7c0u, 4, edx);
    edx = lift_load(&env, 0u, 0x5bb796u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = lift_load(&env, 0u, 0x5bb796u, 4);
    lift_store(&env, 0u, 0x5bb7bcu, 4, edx);
    edx = lift_load(&env, 0u, 0x5bb74eu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = ecx - edx;
    edx = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, 0u, 0x5bb7c4u, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb732u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edx, ecx, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x5bb794u, 4, ecx);
    ecx = lift_load(&env, eax, 0x18u, 4);
    edx = edx + ecx;
    lift_store(&env, 0u, 0x5bb68eu, 2, (esi & 0xffffu));
    lift_store(&env, 0u, 0x5bb7c8u, 4, edx);
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, 0u, 0x5bb732u, 1)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bc016u, 2, (edi & 0xffffu));
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4af23d;
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5bb768u, 4, eax);
    lift_store(&env, 0u, 0x5bb770u, 4, eax);
L_4af1b1:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x13cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4af1e9;
    eax = lift_load(&env, 0u, 0x5bb750u, 4);
    ecx = lift_load(&env, 0u, 0x5bb74eu, 4);
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4af1e9:
    eax = 0x1u;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68eu, 2)) & 0xffffu);
L_4af1fc:
    lift_store(&env, 0u, 0x5bc016u, 2, (edi & 0xffffu));
    lift_store(&env, 0u, 0x5bb68eu, 2, (esi & 0xffffu));
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
L_4af213:
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4aef98;
L_4af21c:
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, 0u, 0x5bbff0u, 1)) & 0xffu) << 8);
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68eu, 2)) & 0xffffu);
    {
        (void)lift_and(8, ((ecx >> 8) & 0xffu), ((ecx >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4aefae;
    goto L_4af0ee;
L_4af23d:
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4af271;
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4af1b1;
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5bb778u, 4, eax);
    lift_store(&env, 0u, 0x5bb77cu, 4, eax);
    goto L_4af1b1;
L_4af271:
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5bb780u, 4, eax);
    lift_store(&env, 0u, 0x5bb784u, 4, eax);
    goto L_4af1b1;
}

uint32_t lifted_actor_chain_paint(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_CHAIN_PAINT_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_CHAIN_PAINT_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    lift_store(&env, 0u, 0x5bc010u, 4, edx);
    edx = lift_load(&env, eax, 0x144u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae3e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4af8da;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4af8da:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4af560u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4b17e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B17E0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B17E0_STACK, 0, entry);
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
    esi = eax;
    edi = edx;
    edx = lift_load(&env, eax, 0x13cu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4b1d35;
L_4b17f6:
    eax = lift_load(&env, esi, 0xb4u, 4);
    lift_store(&env, 0u, 0x5bb734u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b1d44;
    ebx = lift_load(&env, 0u, 0x5bc010u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4b1d30;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0xcu, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0xdu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb732u, 1, (edx & 0xffu));
    lift_store(&env, 0u, 0x5bb733u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a4u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb740u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x16u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a6u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb742u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x1eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7aeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xf4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b4u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xf8u, 2)) & 0xffffu);
    ebx = (ebx & 0xffffff00u) | ((0x4u) & 0xffu);
    lift_store(&env, 0u, 0x5bb7b6u, 2, (eax & 0xffffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x8eu, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x5bbffeu, 1, (eax & 0xffu));
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb739u, 1, (edx & 0xffu));
    lift_store(&env, 0u, 0x5bb790u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x94u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb731u, 1, (ebx & 0xffu));
    lift_store(&env, 0u, 0x5bc00cu, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x8cu, 1)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((0x64u) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb73au, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x80u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc00eu, 1, ((edx >> 8) & 0xffu));
    lift_store(&env, 0u, 0x5bb7b8u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4b1941;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x208u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb744u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x20cu, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb746u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x214u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    ebx = ebx - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x216u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x226u, 2)) & 0xffffu);
    ecx = ecx - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (ebx & 0xffffu));
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bb7aeu, 2, (edx & 0xffffu));
L_4b1941:
    lift_store(&env, 0u, 0x5bb730u, 1, 0xdu);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4b19ca;
    eax = lift_load(&env, 0u, 0x5bb73eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1d4b;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb740u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb744u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b197b;
    eax = ebx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb740u, 2, (eax & 0xffffu));
L_4b197b:
    eax = lift_load(&env, 0u, 0x5bb740u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1d59;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb742u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb746u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b19a6;
    eax = edx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb742u, 2, (eax & 0xffffu));
L_4b19a6:
    edx = lift_load(&env, 0u, 0x5bb742u, 4);
    eax = lift_load(&env, 0u, 0x5bb740u, 4);
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
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = lift_load(&env, 0u, 0x5bb73eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb73cu, 4, edx);
L_4b19ca:
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1d67;
L_4b19d3:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x44u, 1)) & 0xffu);
L_4b19d6:
    lift_store(&env, 0u, 0x5bb738u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bb738u, 1), 0x10u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, 0u, 0x5bb70cu, 4, eax);
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1da6;
L_4b19f8:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x52u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x48u, 2)) & 0xffffu);
L_4b1a04:
    lift_store(&env, 0u, 0x5bc002u, 2, (eax & 0xffffu));
L_4b1a0a:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb70cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1e31;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb74cu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb74eu, 2, (eax & 0xffffu));
L_4b1a2f:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74cu, 2)) & 0xffffu);
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb750u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74cu, 2)) & 0xffffu);
    ebx = ebx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    eax = eax + ecx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb748u, 2, (eax & 0xffffu));
    eax = ebx;
    lift_store(&env, 0u, 0x5bb752u, 2, (edx & 0xffffu));
    eax = eax + edx;
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ebx & 0xffffu));
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bbff4u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bb74au, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bbffeu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bbff2u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b1b35;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1eb5;
    ebx = ebx ^ ebx;
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    lift_store(&env, 0u, 0x5bbff6u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bbffau, 2, (ebx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    edx = edx - 1u;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bbff8u, 2, (edx & 0xffffu));
L_4b1ae3:
    lift_store(&env, 0u, 0x5bbffcu, 2, (eax & 0xffffu));
L_4b1ae9:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff8u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b1d44;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1d44;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffcu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b1d44;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffau, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1d44;
L_4b1b35:
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x5bc014u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bbffeu, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b1f27;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffau, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b1b9b;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb70cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1b87;
    eax = lift_load(&env, 0u, 0x5bbff8u, 4);
    edx = lift_load(&env, 0u, 0x5bb7a0u, 4);
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
    edx = eax;
    eax = lift_load(&env, 0u, 0x5bb74au, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb790u, 4, lift_load(&env, 0u, 0x5bb790u, 4) + eax);
L_4b1b87:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffau, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, (edx & 0xffu));
L_4b1b9b:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b1be8;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb70cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1bd4;
    edx = lift_load(&env, 0u, 0x5bbff4u, 4);
    eax = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    ebx = lift_load(&env, 0u, 0x5bb790u, 4);
    edx = edx - eax;
    ebx = ebx + edx;
    lift_store(&env, 0u, 0x5bb790u, 4, ebx);
L_4b1bd4:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff6u, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, ((edx >> 8) & 0xffu));
L_4b1be8:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffcu, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b1c08;
    lift_store(&env, 0u, 0x5bb74au, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, 0x1u);
L_4b1c08:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff8u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b1f27;
    lift_store(&env, 0u, 0x5bb748u, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, 0x1u);
L_4b1c2c:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) - lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    eax = eax + 1u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb750u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    eax = eax - edx;
    eax = eax + 1u;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb752u, 2, (eax & 0xffffu));
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
L_4b1c6f:
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb798u, 2, (edx & 0xffffu));
    edx = lift_load(&env, 0u, 0x5bb796u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = lift_load(&env, 0u, 0x5bb796u, 4);
    lift_store(&env, 0u, 0x5bb7bcu, 4, edx);
    edx = lift_load(&env, 0u, 0x5bb74eu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = ecx - edx;
    edx = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, 0u, 0x5bb7c4u, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb732u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edx, ecx, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x5bb794u, 4, ecx);
    ecx = lift_load(&env, eax, 0x18u, 4);
    edx = edx + ecx;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, 0u, 0x5bb732u, 1)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb7c8u, 4, edx);
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4b1f39;
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5bb768u, 4, eax);
    lift_store(&env, 0u, 0x5bb770u, 4, eax);
L_4b1cf7:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x13cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1d2b;
    eax = lift_load(&env, 0u, 0x5bb750u, 4);
    ecx = lift_load(&env, 0u, 0x5bb74eu, 4);
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4b1d2b:
    eax = 0x1u;
L_4b1d30:
    {
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
L_4b1d35:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    goto L_4b17f6;
L_4b1d44:
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4b1d4b:
    ecx = ecx ^ ecx;
    lift_store(&env, 0u, 0x5bb740u, 2, (ecx & 0xffffu));
    goto L_4b197b;
L_4b1d59:
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x5bb742u, 2, (ebx & 0xffffu));
    goto L_4b19a6;
L_4b1d67:
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x91u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b19d3;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x220u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1d8d;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x221u, 1)) & 0xffu);
    goto L_4b19d6;
L_4b1d8d:
    eax = lift_load(&env, eax, 0x270u, 4);
    edx = lift_load(&env, 0u, 0x5bb73cu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) + 1u) & 0xffu);
    goto L_4b19d6;
L_4b1da6:
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x92u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b19f8;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x222u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1de0;
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x223u, 1)) & 0xffffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x224u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc002u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    goto L_4b1a0a;
L_4b1de0:
    eax = lift_load(&env, eax, 0x26cu, 4);
    ecx = lift_load(&env, 0u, 0x5bb73cu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + ecx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc004u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bc004u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bc004u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x7u) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - 0x5u) & 0xffu);
    edx = (edx & 0xffff0000u) | (((uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu)) & 0xffffu);
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    lift_store(&env, 0u, 0x5bc002u, 2, (edx & 0xffffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1e29;
    {
        uint32_t r = lift_imul(32, edx, 0x28u, &fl);
        eax = r;
    }
    goto L_4b1a04;
L_4b1e29:
    {
        uint32_t r = lift_imul(32, edx, 0x14u, &fl);
        eax = r;
    }
    goto L_4b1a04;
L_4b1e31:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    edx = eax;
    eax = eax ^ eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb738u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    ecx = ecx ^ ecx;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) & 0xfu) & 0xffu);
    lift_store(&env, 0u, 0x5bb74cu, 2, (edx & 0xffffu));
    edx = eax;
    ecx = (ecx & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, edx + 0x5c1b00u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb74cu, 2, lift_load(&env, 0u, 0x5bb74cu, 2) + (ebx & 0xffffu));
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, eax, ecx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb74eu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    eax = eax & 0xffffu;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x5c1b00u, 1)) & 0xffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edi = edi + eax;
    lift_store(&env, 0u, 0x5bb74eu, 2, (edi & 0xffffu));
    goto L_4b1a2f;
L_4b1eb5:
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4b1eeb;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    edx = edx - 1u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff8u, 2, (edx & 0xffffu));
    eax = eax - 1u;
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5bbffcu, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bbffau, 2, (edx & 0xffffu));
    goto L_4b1ae9;
L_4b1eeb:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4b1ae9;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xa8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xaau, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xacu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbffau, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xaeu, 2)) & 0xffffu);
    goto L_4b1ae3;
L_4b1f27:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bc014u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1c2c;
    goto L_4b1c6f;
L_4b1f39:
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b1f6d;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1cf7;
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5bb778u, 4, eax);
    lift_store(&env, 0u, 0x5bb77cu, 4, eax);
    goto L_4b1cf7;
L_4b1f6d:
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5bb780u, 4, eax);
    lift_store(&env, 0u, 0x5bb784u, 4, eax);
    goto L_4b1cf7;
}

uint32_t lifted_f4b6240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B6240_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B6240_STACK, 0, entry);
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
    edi = eax;
    ecx = edx;
    eax = lift_load(&env, eax, 0x8u, 4);
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x5bd822u, 2, (eax & 0xffffu));
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b6290;
L_4b6258:
    edx = edx ^ edx;
    eax = lift_load(&env, edi, 0x4u, 4);
    edx = (edx & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    eax = lift_load(&env, eax, (edx * 4u) + 0x0u, 4);
    lift_store(&env, 0u, (edx * 4u) + 0x5bc01cu, 4, eax);
    lift_store(&env, 0u, 0x5bd824u, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x16u, 2)) & 0xffffu);
    ebx = ebx + 1u;
    lift_store(&env, 0u, (edx * 2u) + 0x5bd01cu, 2, (eax & 0xffffu));
    {
        (void)lift_sub(16, (ebx & 0xffffu), lift_load(&env, 0u, 0x5bd822u, 2), &fl);
    }
    if (fl.cf)
        goto L_4b6258;
L_4b6290:
    edi = 0x7d00u;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd822u, 2)) & 0xffffu);
    ebx = ebx ^ ebx;
    {
        (void)lift_and(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b62c5;
L_4b62a3:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    eax = eax + eax;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x5bd01cu, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (edx & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b62b8;
    edi = edx;
L_4b62b8:
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd822u, 2)) & 0xffffu);
    ebx = ebx + 1u;
    {
        (void)lift_sub(16, (ebx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.cf)
        goto L_4b62a3;
L_4b62c5:
    {
        (void)lift_sub(16, (edi & 0xffffu), 0x7d00u, &fl);
    }
    if (fl.zf)
        goto L_4b633b;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd822u, 2)) & 0xffffu);
    ebx = ebx ^ ebx;
    {
        (void)lift_and(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b6290;
L_4b62da:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, (eax * 2u) + 0x5bd01cu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bd81cu, 2, (edi & 0xffffu));
    {
        (void)lift_sub(16, (edx & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4b6322;
    eax = lift_load(&env, 0u, (eax * 4u) + 0x5bc01cu, 4);
    esi = lift_load(&env, eax, 0x158u, 4);
    edx = ecx;
    lift_store(&env, 0u, 0x5bd820u, 2, (ebx & 0xffffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd820u, 2)) & 0xffffu);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    lift_store(&env, 0u, (eax * 2u) + 0x5bd01cu, 2, 0x7d00u);
L_4b6322:
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd81cu, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd822u, 2)) & 0xffffu);
    ebx = ebx + 1u;
    {
        (void)lift_sub(16, (ebx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.cf)
        goto L_4b62da;
    goto L_4b6290;
L_4b633b:
    lift_store(&env, 0u, 0x5bd81cu, 2, (edi & 0xffffu));
    lift_store(&env, 0u, 0x5bd820u, 2, (ebx & 0xffffu));
    {
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

uint32_t lifted_object_construct_labeled_box(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_CONSTRUCT_LABELED_BOX_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_CONSTRUCT_LABELED_BOX_STACK, 0,
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
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x20u;
    ecx = eax;
    eax = (ebp + 0xffffffccu);
    edx = 0x4ec1ecu;
    ebx = 0x518360u;
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
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    lift_store(&env, ebp, 0xffffffe4u, 1, ((eax >> 8) & 0xffu));
    eax = ecx;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax + 0x15cu;
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = (eax + 0xfffffea4u);
    eax = 0x2u;
    edx = 0x5110b7u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = (ecx + 0x15cu);
    lift_store(&env, ecx, 0x158u, 4, 0x518404u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x160u, 1, 0x0u);
    lift_store(&env, ecx, 0x162u, 2, 0x0u);
    lift_store(&env, ecx, 0x164u, 2, 0x0u);
    lift_store(&env, ecx, 0x166u, 2, 0x0u);
    lift_store(&env, ecx, 0x168u, 2, 0x0u);
    lift_store(&env, ecx, 0x16au, 2, 0x0u);
    lift_store(&env, ecx, 0x16cu, 2, 0x0u);
    lift_store(&env, ecx, 0x16eu, 2, 0x0u);
    lift_store(&env, ecx, 0x170u, 2, 0x0u);
    lift_store(&env, ecx, 0x94u, 1, 0x0u);
    lift_store(&env, ecx, 0x95u, 1, 0x3u);
    lift_store(&env, ecx, 0x172u, 2, 0x0u);
    lift_store(&env, ecx, 0x17au, 2, 0xff9cu);
    lift_store(&env, ecx, 0x17cu, 2, 0xff9cu);
    lift_store(&env, ecx, 0x174u, 4, esi);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
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
}

uint32_t lifted_object_label_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_LABEL_TEXT_STACK + 4 + 4 * 3 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_LABEL_TEXT_STACK, 3, entry);
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
    esp = esp - 0x14u;
    esi = eax;
    lift_store(&env, ebp, 0xfffffff8u, 1, (ebx & 0xffu));
    ebx = ecx;
    ecx = (eax + 0x15cu);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff8u, 1)) & 0xffu);
    lift_store(&env, esi, 0x160u, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, esi, 0x164u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xcu, 4);
    lift_store(&env, esi, 0x166u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, esi, 0x168u, 2, (eax & 0xffffu));
    eax = (ebp + 0xfffffff4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xfffffff0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffecu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe8u);
    lift_store(&env, esi, 0x162u, 2, (ebx & 0xffffu));
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    edx = lift_load(&env, esi, 0x160u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x44u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ecx, 0x0u, 4);
    ebx = lift_load(&env, esi, 0x162u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x166u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, esi, 0x164u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
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
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, esi, 0xeu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, esi, 0xf4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, esi, 0xf8u, 4, eax);
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

uint32_t lifted_f4b68a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B68A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B68A0_STACK, 0, entry);
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
    esi = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae150u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffecu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe0u);
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
    eax = (esi + 0x15cu);
    ecx = lift_load(&env, esi, 0x164u, 4);
    ebx = lift_load(&env, esi, 0x162u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, esi, 0x160u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x166u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
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
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
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
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, esi, 0xeu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, esi, 0xf4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, esi, 0xf8u, 4, eax);
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

uint32_t lifted_f4b7610(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B7610_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B7610_STACK, 0, entry);
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
        goto L_4b76a2;
    edx = 0x4ec1ecu;
    esi = 0x518620u;
    edi = 0x3u;
    lift_store(&env, eax, 0x0u, 4, 0x518694u);
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
    eax = lift_call(&env, 0x4b7830u, eax, edx, ebx, ecx, 0, esp);
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
        goto L_4b768e;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b768e:
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
L_4b76a2:
    ebx = 0x1u;
    edx = 0x513ea0u;
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

uint32_t lifted_list_text_indexed(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_LIST_TEXT_INDEXED_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_LIST_TEXT_INDEXED_STACK, 0, entry);
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
    ecx = edx;
    eax = (ebp + 0xffffffe0u);
    edx = 0x4ec1ecu;
    edi = 0x51863cu;
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
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    eax = eax ^ eax;
    edx = 0x5110cau;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = ecx;
    edi = lift_load(&env, esi, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ebx, edi, &fl);
    }
    if (fl.cf)
        goto L_4b776a;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    env.chain = eax;
    eax = ecx;
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
L_4b776a:
    edx = lift_load(&env, esi, 0x4u, 4);
    eax = ecx;
    edx = lift_load(&env, edx, (ebx * 4u) + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    env.chain = eax;
    eax = ecx;
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

uint32_t lifted_list_release_entries(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_LIST_RELEASE_ENTRIES_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_LIST_RELEASE_ENTRIES_STACK, 0, entry);
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
    eax = (ebp + 0xffffffdcu);
    edx = 0x4ec1ecu;
    ecx = 0x51864cu;
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
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    eax = lift_load(&env, esi, 0x8u, 4);
    edi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b78a1;
    ecx = ecx ^ ecx;
L_4b786f:
    eax = lift_load(&env, esi, 0x4u, 4);
    eax = lift_load(&env, ecx, eax + 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4b7894;
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x1u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b7894:
    ecx = ecx + 0x4u;
    eax = eax ^ eax;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_sub(32, ebx, edi, &fl);
    }
    if (fl.cf)
        goto L_4b786f;
L_4b78a1:
    ebx = 0xffffffffu;
    eax = esi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8770u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
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

uint32_t lifted_list_text_lookup(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_LIST_TEXT_LOOKUP_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_LIST_TEXT_LOOKUP_STACK, 0, entry);
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
    esp = esp - 0x18u;
    edi = eax;
    esi = edx;
    eax = (ebp + 0xffffffe0u);
    edx = 0x4ec1ecu;
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
    eax = 0x5186ccu;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    eax = esi;
    edx = 0x5110cbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ebx;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b79c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b7a43;
L_4b7a2c:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    env.chain = eax;
    eax = esi;
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
L_4b7a43:
    edx = (ebp + 0xfffffff4u);
    ebx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    edx = eax;
    ebx = ebx ^ ebx;
    eax = esi;
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffff4u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    goto L_4b7a2c;
}

uint32_t lifted_f4b7c00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B7C00_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B7C00_STACK, 0, entry);
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
    esp = esp - 0x8u;
    ebx = 0x46u;
    edx = 0x4b7b80u;
    eax = 0x5bd82cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4844b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x8u;
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
    eax = lift_call(&env, 0x4f1728u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b7c7a;
    eax = edx;
L_4b7c35:
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.cf)
        goto L_4b7c88;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b7c81;
    eax = ebx;
L_4b7c46:
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5bd848u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1720u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
    esi = 0x1u;
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
    lift_store(&env, 0u, 0x5bd83cu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    lift_store(&env, 0u, 0x5bd840u, 4, eax);
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
L_4b7c7a:
    eax = 0x1u;
    goto L_4b7c35;
L_4b7c81:
    eax = 0x1u;
    goto L_4b7c46;
L_4b7c88:
    eax = ecx;
    goto L_4b7c46;
}

uint32_t lifted_f4b9710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B9710_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B9710_STACK, 0, entry);
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
    ecx = lift_load(&env, eax, 0x14u, 4);
    {
        (void)lift_sub(32, ecx, 0xcdu, &fl);
    }
    if (!fl.zf)
        goto L_4b974f;
L_4b971f:
    {
        (void)lift_sub(32, lift_load(&env, edx, 0x40u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b9759;
L_4b9725:
    eax = lift_load(&env, edx, 0x14u, 4);
    {
        (void)lift_sub(32, eax, 0xcfu, &fl);
    }
    if (!fl.zf)
        goto L_4b9780;
L_4b972f:
    lift_store(&env, edx, 0x14u, 4, 0xd2u);
L_4b9736:
    eax = lift_load(&env, edx, 0x1b4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x14u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b97a0;
    ecx = eax;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b9736;
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
L_4b974f:
    {
        (void)lift_sub(32, ecx, 0xceu, &fl);
    }
    if (fl.zf)
        goto L_4b971f;
    goto L_4b9725;
L_4b9759:
    eax = lift_load(&env, edx, 0x8cu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x74u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4b9773;
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x43u);
    ecx = lift_load(&env, edx, 0x0u, 4);
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b9773:
    ecx = lift_load(&env, edx, 0x1a4u, 4);
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4b972f;
L_4b9780:
    {
        (void)lift_sub(32, eax, 0xd2u, &fl);
    }
    if (fl.zf)
        goto L_4b9736;
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x14u);
    ecx = lift_load(&env, edx, 0x0u, 4);
    eax = lift_load(&env, edx, 0x14u, 4);
    lift_store(&env, ecx, 0x18u, 4, eax);
    ecx = lift_load(&env, edx, 0x0u, 4);
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4b9736;
L_4b97a0:
    ecx = lift_load(&env, edx, 0x18u, 4);
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x18u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b9170u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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

uint32_t lifted_f4c4d20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C4D20_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C4D20_STACK, 0, entry);
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
    ecx = eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_sub(32, ebx, 0x3b9ac9f0u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4c4e3e;
L_4c4d43:
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = eax & 0x7u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c4d5c;
    edx = 0x8u;
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = edx - eax;
    ebx = ebx + edx;
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
L_4c4d5c:
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c4d68;
    {
        (void)lift_sub(32, esi, 0x2u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c4d7f;
L_4c4d68:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0xeu);
    eax = lift_load(&env, ecx, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c4d7f:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + edx;
    eax = lift_load(&env, eax, 0x34u, 4);
    edi = edi ^ edi;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c4d9f;
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
L_4c4d96:
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x8u, 4), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4c4e4f;
L_4c4d9f:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4c4e19;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = eax + 0x10u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4c4e60;
    ebx = lift_load(&env, ebx, 0x4fffb0u, 4);
L_4c4dc0:
    eax = 0x3b9aca00u;
    eax = eax - lift_load(&env, ebp, 0xffffffecu, 4);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4c4e6b;
L_4c4dd0:
    esi = lift_load(&env, ebp, 0xffffffecu, 4);
    esi = esi + ebx;
    eax = ecx;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c5bb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c4e72;
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ecx, 0x4cu, 4, lift_load(&env, ecx, 0x4cu, 4) + esi);
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    ecx = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, eax, 0x4u, 4, 0x0u);
    ecx = ecx + ebx;
    lift_store(&env, eax, 0x8u, 4, ecx);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4c4e8e;
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    ecx = ecx + edi;
    lift_store(&env, ecx, 0x34u, 4, eax);
L_4c4e19:
    edx = (eax + 0x10u);
    ecx = lift_load(&env, eax, 0x4u, 4);
    ebx = lift_load(&env, eax, 0x4u, 4);
    edx = edx + ecx;
    ecx = lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = lift_load(&env, eax, 0x8u, 4);
    ebx = ebx + ecx;
    {
        uint32_t r = lift_sub(32, esi, ecx, &fl);
        esi = r;
    }
    lift_store(&env, eax, 0x4u, 4, ebx);
    lift_store(&env, eax, 0x8u, 4, esi);
    eax = edx;
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
L_4c4e3e:
    edx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c4d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c4d43;
L_4c4e4f:
    edi = eax;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4c4d96;
    goto L_4c4d9f;
L_4c4e60:
    ebx = lift_load(&env, ebx, 0x4fffb8u, 4);
    goto L_4c4dc0;
L_4c4e6b:
    ebx = eax;
    goto L_4c4dd0;
L_4c4e72:
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, ebx, 0x32u, &fl);
    }
    if (!fl.cf)
        goto L_4c4dd0;
    edx = 0x2u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c4d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c4dd0;
L_4c4e8e:
    lift_store(&env, edi, 0x0u, 4, eax);
    goto L_4c4e19;
}

uint32_t lifted_f4c4f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C4F60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C4F60_STACK, 0, entry);
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
    esp = esp - 0x14u;
    edi = eax;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    ecx = lift_load(&env, eax, 0x4u, 4);
    edx = edx ^ edx;
    eax = 0x3b9ac9f0u;
    lift_div1(32, ebx, &eax, &edx, &fl);
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c500b;
L_4c4f89:
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c5023;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
L_4c4f97:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    lift_store(&env, ecx, 0x50u, 4, eax);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c4d20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = esi ^ esi;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c5001;
L_4c4fb9:
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = ecx - esi;
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c4fc7;
    ecx = ebx;
L_4c4fc7:
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t r = lift_imul(32, ebx, ecx, &fl);
        ebx = r;
    }
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = edi;
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c4ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ecx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c4ffc;
    ecx = ((esi * 4u));
L_4c4fe7:
    ebx = ecx;
    ebx = ebx + lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = esi + 1u;
    edx = edx - 1u;
    lift_store(&env, ebx, 0x0u, 4, eax);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    ecx = ecx + 0x4u;
    eax = eax + ebx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4c4fe7;
L_4c4ffc:
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffe8u, 4), &fl);
    }
    if (fl.cf)
        goto L_4c4fb9;
L_4c5001:
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
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
L_4c500b:
    eax = edi;
    eax = lift_load(&env, eax, 0x0u, 4);
    ebx = edi;
    lift_store(&env, eax, 0x14u, 4, 0x46u);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c4f89;
L_4c5023:
    lift_store(&env, ebp, 0xffffffecu, 4, esi);
    goto L_4c4f97;
}

uint32_t lifted_f4c5a40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C5A40_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C5A40_STACK, 0, entry);
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
    esp = esp - 0x8u;
    ebx = eax;
    edx = 0x54u;
    lift_store(&env, eax, 0x4u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c5c10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c5bb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c5b16;
L_4c5a70:
    lift_store(&env, ecx, 0x0u, 4, 0x4c4d20u);
    lift_store(&env, ecx, 0x4u, 4, 0x4c4ea0u);
    lift_store(&env, ecx, 0x8u, 4, 0x4c4f60u);
    lift_store(&env, ecx, 0xcu, 4, 0x4c5030u);
    lift_store(&env, ecx, 0x10u, 4, 0x4c5120u);
    lift_store(&env, ecx, 0x14u, 4, 0x4c5190u);
    lift_store(&env, ecx, 0x18u, 4, 0x4c5200u);
    lift_store(&env, ecx, 0x1cu, 4, 0x4c55a0u);
    lift_store(&env, ecx, 0x20u, 4, 0x4c5740u);
    lift_store(&env, ecx, 0x24u, 4, 0x4c58e0u);
    lift_store(&env, ecx, 0x28u, 4, 0x4c5a00u);
    lift_store(&env, ecx, 0x30u, 4, 0x3b9aca00u);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = 0x1u;
    lift_store(&env, ecx, 0x2cu, 4, eax);
    eax = (ecx + 0x4u);
L_4c5ad1:
    eax = eax - 0x4u;
    lift_store(&env, eax, 0x38u, 4, 0x0u);
    edx = edx - 1u;
    lift_store(&env, eax, 0x40u, 4, 0x0u);
    {
        (void)lift_sub(32, edx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4c5ad1;
    lift_store(&env, ecx, 0x44u, 4, 0x0u);
    lift_store(&env, ecx, 0x48u, 4, 0x0u);
    lift_store(&env, ecx, 0x4cu, 4, 0x54u);
    eax = 0x51232fu;
    lift_store(&env, ebx, 0x4u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dac40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4c5b36;
L_4c5b0e:
    esp = (ebp + 0xfffffff4u);
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
L_4c5b16:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c5c20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x36u);
    eax = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, ecx);
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c5a70;
L_4c5b36:
    lift_store(&env, ebp, 0xfffffff0u, 1, 0x78u);
    edx = (ebp + 0xfffffff0u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffffecu);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x512337u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dacf8u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0x10u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c5b0e;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x6du, &fl);
    }
    if (fl.zf)
        goto L_4c5b61;
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x4du, &fl);
    }
    if (!fl.zf)
        goto L_4c5b7f;
L_4c5b61:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = ((edx * 4u));
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax + edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + edx;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_4c5b7f:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = ((edx * 4u));
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax + edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
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
    lift_store(&env, ecx, 0x2cu, 4, eax);
    esp = (ebp + 0xfffffff4u);
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

uint32_t lifted_rtl_string_unique(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_STRING_UNIQUE_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_STRING_UNIQUE_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    edx = edx - 0xcu;
    {
        (void)lift_sub(32, lift_load(&env, edx, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ca192;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca110u, eax, edx, ebx, ecx, 0, esp);
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
L_4ca192:
    edx = 0x5c5c00u;
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

uint32_t lifted_f4ca5a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA5A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA5A0_STACK, 0, entry);
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
    ecx = edx;
    edx = ebx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ca5fb;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebx + 0xfffffff4u);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x1u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ca5c1;
    edi = lift_load(&env, eax, 0x4u, 4);
    edi = edi + ecx;
    {
        (void)lift_sub(32, edi, lift_load(&env, eax, 0x8u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ca5db;
L_4ca5c1:
    ebx = lift_load(&env, esi, 0x0u, 4);
    edi = (ebx + 0xfffffff4u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    edx = lift_load(&env, edi, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca3f0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca150u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
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
L_4ca5db:
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = eax + ebx;
    ebx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0xfffffff8u, 4, lift_load(&env, eax, 0xfffffff8u, 4) + ecx);
    {
        uint32_t r = lift_sub(32, eax, 0xcu, &fl);
        eax = r;
    }
    edx = lift_load(&env, esi, 0x0u, 4);
    eax = (edx + 0xfffffff4u);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, edx, eax + 0x0u, 1, 0x0u);
L_4ca5fb:
    {
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

uint32_t lifted_rtl_byte_local_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_BYTE_LOCAL_CALL_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_BYTE_LOCAL_CALL_STACK, 0, entry);
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
    esp = esp - 0x4u;
    ecx = eax;
    lift_store(&env, esp, 0x0u, 1, (edx & 0xffu));
    ebx = esp;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca5a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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

uint32_t lifted_f4ccf3b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCF3B_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCF3B_STACK, 0, entry);
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
    esp = esp - 0x24u;
    ecx = eax;
    esi = ebx;
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
    lift_store(&env, esp, 0x8u, 4, 0x518f20u);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x14u, 4, 0x1u);
    lift_store(&env, esp, 0x18u, 4, 0x0u);
    lift_store(&env, esp, 0x1cu, 4, ebx);
    lift_store(&env, esp, 0x20u, 4, ecx);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    ebx = lift_load(&env, ebx, 0x4u, 4);
    esi = lift_load(&env, esi, 0x10u, 4);
L_4ccf93:
    {
        (void)lift_sub(32, edx, lift_load(&env, esp, 0x18u, 4), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ccfd1;
    lift_store(&env, esp, 0x14u, 4, 0x0u);
    ecx = lift_load(&env, esp, 0x20u, 4);
    eax = (esp + 0x14u);
    edx = edx ^ edx;
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce9fdu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0x0u, 4);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    env.chain = eax;
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x24u, &fl);
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
L_4ccfd1:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x18u, 4, lift_load(&env, esp, 0x18u, 4) + 1u);
    ecx = ecx + esi;
    goto L_4ccf93;
}

uint32_t lifted_f4cd8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CD8B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CD8B0_STACK, 0, entry);
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
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = edx;
    edi = ebx;
    lift_store(&env, edx, 0x4u, 4, ebx);
    eax = lift_load(&env, ebx, 0x8u, 4);
    lift_store(&env, edx, 0x8u, 4, eax);
    eax = (esp + 0x4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0b7cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0x0u, 4);
    lift_store(&env, esp, 0xcu, 4, eax);
    eax = (esp + 0x4u);
    lift_store(&env, esp, 0x11u, 1, lift_load(&env, esp, 0x11u, 1) | 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd7dcu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x14u, 4, eax);
    goto L_4cd95e;
L_4cd8ec:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4cd8f1:
    eax = lift_load(&env, esi, 0x4u, 4);
    ebx = lift_load(&env, esi, 0xcu, 4);
    edx = lift_load(&env, esi, 0x8u, 4);
L_4cd8fa:
    eax = lift_load(&env, edi, eax + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cea15u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4cd95e;
L_4cd904:
    ebx = (esi + 0xffffffffu);
    edx = edi;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd836u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4cd95e;
L_4cd912:
    ebx = esi;
    edx = edi;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd847u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4cd95e;
L_4cd91f:
    ecx = 0x11u;
L_4cd924:
    edx = 0x1u;
    ebx = ebp;
    eax = esi;
L_4cd92d:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd819u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4cd95e;
L_4cd934:
    ecx = 0x10u;
    goto L_4cd924;
L_4cd93b:
    ecx = 0x10u;
    ebx = ebp;
    eax = esi;
    edx = edx ^ edx;
    goto L_4cd92d;
L_4cd948:
    eax = lift_load(&env, esi, 0x4u, 4);
    ebx = lift_load(&env, edi, eax + 0x4u, 4);
    edx = lift_load(&env, edi, eax + 0x8u, 4);
    goto L_4cd8fa;
L_4cd955:
    eax = lift_load(&env, esi, 0x4u, 4);
L_4cd958:
    eax = lift_load(&env, edi, eax + 0x0u, 4);
L_4cd95b:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4cd95e:
    eax = lift_load(&env, esp, 0x8u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x0u, 4), &fl);
    }
    if (fl.zf)
        goto L_4cd9e5;
    if (!fl.cf)
        goto L_4cd972;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4cd972:
    eax = (esp + 0x4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0b9eu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (esp + 0x4u);
    esi = lift_load(&env, esp, 0x14u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd7dcu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x14u, 4, eax);
    eax = lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, edi, 0xcu, 4, eax);
    ebx = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4cd9d7;
    esi = lift_load(&env, esi, 0x4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x10u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4cd8ec;
    eax = (eax & 0xffu);
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4cd8f1;
            case 1:
                goto L_4cd8ec;
            case 2:
                goto L_4cd95e;
            case 3:
                goto L_4cd904;
            case 4:
                goto L_4cd912;
            case 5:
                goto L_4cd8ec;
            case 6:
                goto L_4cd91f;
            case 7:
                goto L_4cd934;
            case 8:
                goto L_4cd93b;
            case 9:
                goto L_4cd948;
            case 10:
                goto L_4cd955;
            case 11:
                goto L_4cd9bb;
            case 12:
                goto L_4cd9b0;
            case 13:
                goto L_4cd9c3;
            case 14:
                goto L_4cd8ec;
            case 15:
                goto L_4cd934;
            case 16:
                goto L_4cd934;
            default:
                return 0u;
        }
    }
L_4cd9b0:
    eax = lift_load(&env, esi, 0x4u, 4);
    eax = lift_load(&env, edi, eax + 0x0u, 4);
    eax = eax - 0x4u;
    goto L_4cd95b;
L_4cd9bb:
    eax = lift_load(&env, esi, 0x4u, 4);
    edx = lift_load(&env, esi, 0xcu, 4);
    goto L_4cd958;
L_4cd9c3:
    eax = lift_load(&env, esi, 0x4u, 4);
    eax = lift_load(&env, edi, eax + 0x0u, 4);
    eax = eax - 0x4u;
    edx = lift_load(&env, esi, 0xcu, 4);
    {
        uint32_t r = lift_imul(32, edx, lift_load(&env, eax, 0x0u, 4), &fl);
        edx = r;
    }
    edx = edx + 0x4u;
    goto L_4cd95b;
L_4cd9d7:
    eax = lift_load(&env, esi, 0x4u, 4);
    edx = edx ^ edx;
    eax = eax + edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4cd95e;
L_4cd9e5:
    lift_store(&env, edi, 0xcu, 4, eax);
    {
        uint32_t r = lift_add(32, esp, 0x18u, &fl);
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

uint32_t lifted_f4cda10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CDA10_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CDA10_STACK, 0, entry);
    eax = eax ^ eax;
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
    esp = esp - 0xcu;
    ecx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0f8bu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = esp;
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = env.chain;
    ebx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd8b0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
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

uint32_t lifted_f4cdbe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CDBE0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CDBE0_STACK, 0, entry);
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
    esp = esp - 0x10u;
    lift_store(&env, esp, 0x4u, 4, eax);
    lift_store(&env, esp, 0xcu, 4, edx);
    esi = ebx;
    eax = lift_load(&env, ebx, 0x0u, 4);
    edi = edi ^ edi;
    lift_store(&env, esp, 0x0u, 4, eax);
    ebx = edx;
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc16;
    goto L_4cdf71;
L_4cdc04:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cdf71;
L_4cdc16:
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x25u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc29;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x25u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc34;
L_4cdc29:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e105au, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi + eax;
    goto L_4cdc04;
L_4cdc34:
    edx = edx ^ edx;
    ebp = ebp ^ ebp;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc4d;
    goto L_4cdc7a;
L_4cdc3f:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cdc7a;
L_4cdc4d:
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x23u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc57;
    edi = edi + 0x2u;
    goto L_4cdc3f;
L_4cdc57:
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x2au, &fl);
    }
    if (!fl.zf)
        goto L_4cdc66;
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    ebp = lift_load(&env, eax, 0xfffffffcu, 4);
    goto L_4cdc3f;
L_4cdc66:
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x2du, &fl);
    }
    if (fl.zf)
        goto L_4cdc3f;
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x2bu, &fl);
    }
    if (fl.zf)
        goto L_4cdc3f;
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x30u, &fl);
    }
    if (fl.zf)
        goto L_4cdc3f;
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4cdc3f;
L_4cdc7a:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4cdca8;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc9c;
    goto L_4cdca8;
L_4cdc8e:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cdca8;
L_4cdc9c:
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, ebx, 0x0u, 1);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cdc8e;
L_4cdca8:
    lift_store(&env, esp, 0x8u, 4, 0x0u);
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x2eu, &fl);
    }
    if (!fl.zf)
        goto L_4cdd0a;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x2au, &fl);
    }
    if (!fl.zf)
        goto L_4cdce0;
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    goto L_4cdd0a;
L_4cdce0:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cdcfe;
    goto L_4cdd0a;
L_4cdcf0:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cdd0a;
L_4cdcfe:
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, ebx, 0x0u, 1);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cdcf0;
L_4cdd0a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ecx = ecx ^ ecx;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x4eu, &fl);
    }
    if (fl.cf)
        goto L_4cdd5b;
    if (fl.cf || fl.zf)
        goto L_4cdd4d;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x68u, &fl);
    }
    if (fl.cf)
        goto L_4cdd69;
    if (fl.cf || fl.zf)
        goto L_4cdd27;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6cu, &fl);
    }
    if (fl.zf)
        goto L_4cdd3a;
    goto L_4cdd69;
L_4cdd27:
    eax = ebx;
    ecx = 0x10000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    goto L_4cdd69;
L_4cdd3a:
    eax = ebx;
    ecx = 0x20000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    goto L_4cdd69;
L_4cdd4d:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    goto L_4cdd69;
L_4cdd5b:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x46u, &fl);
    }
    if (fl.cf)
        goto L_4cdd69;
    if (fl.cf || fl.zf)
        goto L_4cdd4d;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x4cu, &fl);
    }
    if (fl.zf)
        goto L_4cdd4d;
L_4cdd69:
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, ebx, 0x0u, 1);
    eax = eax | ecx;
    {
        (void)lift_sub(32, eax, 0x10053u, &fl);
    }
    if (fl.cf)
        goto L_4cde4a;
    if (fl.cf || fl.zf)
        goto L_4cddf0;
    {
        (void)lift_sub(32, eax, 0x20043u, &fl);
    }
    if (fl.cf)
        goto L_4cde34;
    if (fl.cf || fl.zf)
        goto L_4cdda5;
    {
        (void)lift_sub(32, eax, 0x20063u, &fl);
    }
    if (fl.cf)
        goto L_4cde2b;
    if (fl.cf || fl.zf)
        goto L_4cdda5;
    {
        (void)lift_sub(32, eax, 0x20073u, &fl);
    }
    if (fl.zf)
        goto L_4cde10;
    goto L_4cde81;
L_4cdda5:
    edx = 0x2u;
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    goto L_4cde89;
L_4cddb2:
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t v = lift_load(&env, eax, 0xfffffffcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1d24u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cddcb;
    eax = 0x1u;
L_4cddcb:
    edx = eax;
    goto L_4cde81;
L_4cddd2:
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cdde9;
    eax = 0x1u;
L_4cdde9:
    edx = eax;
    goto L_4cde81;
L_4cddf0:
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t v = lift_load(&env, eax, 0xfffffffcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1d24u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cde09;
    eax = 0x1u;
L_4cde09:
    edx = eax;
    goto L_4cde81;
L_4cde10:
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cde27;
    eax = 0x1u;
L_4cde27:
    edx = eax;
    goto L_4cde81;
L_4cde2b:
    {
        (void)lift_sub(32, eax, 0x20053u, &fl);
    }
    if (fl.zf)
        goto L_4cde10;
    goto L_4cde81;
L_4cde34:
    {
        (void)lift_sub(32, eax, 0x10063u, &fl);
    }
    if (fl.cf)
        goto L_4cde81;
    if (fl.cf || fl.zf)
        goto L_4cdda5;
    {
        (void)lift_sub(32, eax, 0x10073u, &fl);
    }
    if (fl.zf)
        goto L_4cddf0;
    goto L_4cde81;
L_4cde4a:
    {
        (void)lift_sub(32, eax, 0x63u, &fl);
    }
    if (fl.cf)
        goto L_4cde6d;
    if (fl.cf || fl.zf)
        goto L_4cdda5;
    {
        (void)lift_sub(32, eax, 0x73u, &fl);
    }
    if (fl.cf)
        goto L_4cde81;
    if (fl.cf || fl.zf)
        goto L_4cddb2;
    {
        (void)lift_sub(32, eax, 0x10043u, &fl);
    }
    if (fl.zf)
        goto L_4cdda5;
    goto L_4cde81;
L_4cde6d:
    {
        (void)lift_sub(32, eax, 0x43u, &fl);
    }
    if (fl.cf)
        goto L_4cde81;
    if (fl.cf || fl.zf)
        goto L_4cdda5;
    {
        (void)lift_sub(32, eax, 0x53u, &fl);
    }
    if (fl.zf)
        goto L_4cddd2;
L_4cde81:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4cdf03;
L_4cde89:
    {
        (void)lift_sub(32, edx, ebp, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4cde8f;
    ebp = edx;
L_4cde8f:
    edx = ebp;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cdf6a;
    {
        (void)lift_sub(32, ebp, lift_load(&env, esp, 0x8u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4cdf6a;
    edx = lift_load(&env, esp, 0x8u, 4);
    edi = edi + edx;
    goto L_4cdc04;
L_4cdeb1:
    ebp = ebp + lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    {
        (void)lift_sub(32, ebp, 0x20u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cdec9;
    edx = 0x20u;
    edi = edi + edx;
    goto L_4cdc04;
L_4cdec9:
    edx = ebp;
    edi = edi + edx;
    goto L_4cdc04;
L_4cded2:
    edx = ebp;
    edi = edi + edx;
    goto L_4cdc04;
L_4cdedb:
    edx = lift_load(&env, esp, 0x8u, 4);
    edx = edx + ebp;
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    {
        (void)lift_sub(32, edx, 0x20u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cdf6a;
    edx = 0x20u;
    edi = edi + edx;
    goto L_4cdc04;
L_4cdef9:
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    edi = edi + edx;
    goto L_4cdc04;
L_4cdf03:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x67u, &fl);
    }
    if (fl.cf)
        goto L_4cdf37;
    if (fl.cf || fl.zf)
        goto L_4cdf41;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6fu, &fl);
    }
    if (fl.cf)
        goto L_4cdf26;
    if (fl.cf || fl.zf)
        goto L_4cdeb1;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x75u, &fl);
    }
    if (fl.cf)
        goto L_4cdf1b;
    if (fl.cf || fl.zf)
        goto L_4cdeb1;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x78u, &fl);
    }
    goto L_4cdf64;
L_4cdf1b:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x70u, &fl);
    }
    if (fl.zf)
        goto L_4cdedb;
    edi = edi + edx;
    goto L_4cdc04;
L_4cdf26:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x69u, &fl);
    }
    if (fl.cf)
        goto L_4cdf6a;
    if (fl.cf || fl.zf)
        goto L_4cdeb1;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6eu, &fl);
    }
    if (fl.zf)
        goto L_4cdef9;
    edi = edi + edx;
    goto L_4cdc04;
L_4cdf37:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x64u, &fl);
    }
    if (fl.cf)
        goto L_4cdf5c;
    if (fl.cf || fl.zf)
        goto L_4cdeb1;
L_4cdf41:
    ebp = ebp + lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x8u);
    {
        (void)lift_sub(32, ebp, 0x80u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cded2;
    edx = 0x80u;
    edi = edi + edx;
    goto L_4cdc04;
L_4cdf5c:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x47u, &fl);
    }
    if (fl.cf)
        goto L_4cdf6a;
    if (fl.cf || fl.zf)
        goto L_4cdf41;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x58u, &fl);
    }
L_4cdf64:
    if (fl.zf)
        goto L_4cdeb1;
L_4cdf6a:
    edi = edi + edx;
    goto L_4cdc04;
L_4cdf71:
    eax = lift_load(&env, esp, 0x4u, 4);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0x4u, 4);
    ebx = esp;
    edx = lift_load(&env, esp, 0xcu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd0a4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xffffffffu;
    eax = lift_load(&env, esp, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca6c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x0u, 4, 0x0u);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cdfb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CDFB0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CDFB0_STACK, 0, entry);
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
    esp = esp - 0x4u;
    ebx = (esp + 0x18u);
    edx = lift_load(&env, esp, 0x14u, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, esp, 0x0u, 4, ebx);
    ebx = esp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdbe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x0u, 4, 0x0u);
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_rtl_string_trim_start(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_STRING_TRIM_START_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_STRING_TRIM_START_STACK, 0, entry);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca1a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ecx, 0x0u, 4);
L_4ce03d:
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, edx, 0x0u, 1);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e10d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ce054;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    goto L_4ce03d;
L_4ce054:
    eax = lift_load(&env, ecx, 0x0u, 4);
    ebx = (eax + 0xfffffff4u);
    esi = edx;
    ebx = lift_load(&env, ebx, 0x4u, 4);
    esi = esi - eax;
    ebx = ebx - esi;
    esi = ebx;
    ebx = ebx + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0xfffffff8u, 4, esi);
    {
        uint32_t r = lift_sub(32, eax, 0xcu, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ce740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CE740_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CE740_STACK, 0, entry);
L_4ce730:
    edx = 0x4ce810u;
    eax = 0x5c5c64u;
    goto L_4dc030;
    edx = 0x4ce7c0u;
    eax = 0x5c5c60u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbf80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ce730;
    eax = lift_load(&env, eax, 0x4u, 4);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4dc030:
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
    esp = esp - 0x54u;
    ebx = eax;
    lift_store(&env, esp, 0x44u, 4, edx);
    eax = (esp + 0x34u);
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
    lift_store(&env, esp, 0x38u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x3cu, 4, 0x51abacu);
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c77e8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc0c6;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, 0x80000000u, &fl);
    }
    if (fl.zf)
        goto L_4dc092;
    eax = (edx & 0xffu);
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4dc092;
    edx = 0x1u;
    goto L_4dc094;
L_4dc092:
    edx = edx ^ edx;
L_4dc094:
    eax = 0x5c77b0u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dc0a2;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbac0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dc0a2:
    lift_store(&env, 0u, 0x5c77e8u, 4, eax);
    goto L_4dc0c6;
L_4dc0a9:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esp, 0x44u, 4, 0x3u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4da66eu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dc0c6:
    eax = esp;
    lift_store(&env, esp, 0x40u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9f06u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dc0a9;
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc0fb;
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbb30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
L_4dc0fb:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    edx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbcd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x4cu, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc12c;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esp, 0x44u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x4cu, 4, eax);
    ecx = lift_load(&env, esp, 0x4cu, 4);
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    edx = lift_load(&env, ebx, 0x0u, 4);
    ebx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbd20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dc12c:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x4cu, 4);
    lift_store(&env, esp, 0x48u, 4, eax);
    eax = lift_load(&env, esp, 0x34u, 4);
    env.chain = eax;
    eax = lift_load(&env, esp, 0x48u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x54u, &fl);
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

uint32_t lifted_f4ce780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CE780_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CE780_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4ce7a0u;
    eax = eax + 0x1038u;
    goto L_4dbf80;
L_4dbf80:
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
    ebx = eax;
    esi = edx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbfba;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c77a8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbfae;
    eax = 0x5c7770u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dbfa9;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbac0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dbfa9:
    lift_store(&env, 0u, 0x5c77a8u, 4, eax);
L_4dbfae:
    eax = lift_load(&env, 0u, 0x5c77a8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbb30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
L_4dbfba:
    eax = lift_load(&env, 0u, 0x5c77a8u, 4);
    {
        uint32_t v = lift_load(&env, eax, 0x0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1cdcu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dbfd3;
    {
        (void)lift_sub(32, edi, lift_load(&env, eax, 0x8u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dbfd7;
L_4dbfd3:
    eax = eax ^ eax;
    goto L_4dbfdd;
L_4dbfd7:
    eax = lift_load(&env, eax, 0xcu, 4);
    eax = lift_load(&env, eax, (edi * 4u) + 0x0u, 4);
L_4dbfdd:
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dbff8;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, esi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x5c77a8u, 4);
    ecx = eax;
    edx = lift_load(&env, ebx, 0x0u, 4);
    ebx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbd20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dbff8:
    eax = ecx;
    {
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

uint32_t lifted_f4ce7a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CE7A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CE7A0_STACK, 0, entry);
L_4ce370:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x20u;
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
    lift_store(&env, esp, 0x8u, 4, 0x518fdcu);
    lift_store(&env, esp, 0x14u, 4, edx);
    edx = edx + 0x8u;
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    lift_store(&env, edx, 0x4u, 4, 0x0u);
    eax = (edx + 0x28u);
    lift_store(&env, edx, 0x0u, 4, 0x0u);
    edx = 0xau;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4deec0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xau;
    eax = eax + 0x1cu;
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4deec0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xau;
    eax = eax + 0x1cu;
    lift_store(&env, esp, 0xcu, 4, 0x2u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8340u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (eax + 0xffffff98u);
    lift_store(&env, esp, 0xcu, 4, 0x3u);
    eax = (edx + 0x8u);
    lift_store(&env, edx, 0x0u, 4, 0x519364u);
    lift_store(&env, eax, 0x4u, 4, 0x54u);
    lift_store(&env, edx, 0x28u, 4, 0x4c9fe0u);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
    {
        uint32_t v = 0x84u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dba80u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ce370;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ce7c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CE7C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CE7C0_STACK, 0, entry);
L_4ce100:
    lift_store(&env, eax, 0x0u, 4, 0x519334u);
    lift_store(&env, eax, 0xd8u, 4, 0xffffffffu);
    lift_store(&env, eax, 0x104u, 4, 0xffffffffu);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
    {
        uint32_t v = 0x114u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dba80u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ce100;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d67e4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D67E4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D67E4_STACK, 0, entry);
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.sf)
        goto L_4d67f0;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = eax;
        uint32_t r = lift_sub(32, 0, a, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d67f0:
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4d6829;
    eax = eax + eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_rol(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(8, (eax & 0xffu), 0x7fu, &fl);
    }
    if (fl.cf)
        goto L_4d6829;
    ecx = (ecx & 0xffff00ffu) | ((((eax & 0xffu)) & 0xffu) << 8);
    fl.cf = 1;
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), (ecx & 0xffu), &fl);
    }
    if (!fl.cf)
        goto L_4d681c;
    {
        uint32_t r = lift_sub(8, ((ecx >> 8) & 0xffu), 0x96u, &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    if (!fl.cf)
        goto L_4d6815;
    {
        uint32_t t = ((ecx >> 8) & 0xffu);
        ecx = (ecx & 0xffff00ffu) | ((((ecx & 0xffu)) & 0xffu) << 8);
        ecx = (ecx & 0xffffff00u) | ((t) & 0xffu);
    }
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_sub(8, 0, a, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d6815:
    if (fl.zf)
        goto L_4d681b;
    ecx = (ecx & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
L_4d681b:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d681c:
    eax = 0xffffffffu;
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) - 0x9fu) & 0xffu);
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_sub(8, 0, a, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d6829:
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d77d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D77D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D77D0_STACK, 0, entry);
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
    esp = esp - 0x120u;
    esi = eax;
    edi = edx;
    lift_store(&env, esp, 0x11cu, 4, ebx);
    ebx = ecx;
    eax = eax + 0xcu;
    lift_store(&env, eax, 0xfffffffcu, 4, 0x0u);
    lift_store(&env, eax, 0xfffffff8u, 4, 0xffffffffu);
    lift_store(&env, esp, 0x110u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca180u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = lift_load(&env, esp, 0x124u, 4);
    lift_store(&env, esp, 0x125u, 1, lift_load(&env, esp, 0x125u, 1) & 0x7fu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d7c40u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    edx = esp;
    eax = lift_load(&env, esp, 0x110u, 4);
    ebp = ebp & 0x3u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ebp, 0x1u, &fl);
    }
    if (fl.cf)
        goto L_4d7863;
    if (fl.cf || fl.zf)
        goto L_4d7849;
    {
        (void)lift_sub(32, ebp, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4d7856;
    goto L_4d7867;
L_4d783c:
    lift_store(&env, esp, 0x114u, 4, 0x80000000u);
    goto L_4d7867;
L_4d7849:
    lift_store(&env, esp, 0x114u, 4, 0x40000000u);
    goto L_4d7867;
L_4d7856:
    lift_store(&env, esp, 0x114u, 4, 0xc0000000u);
    goto L_4d7867;
L_4d7863:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4d783c;
L_4d7867:
    eax = lift_load(&env, esp, 0x11cu, 4);
    eax = eax & 0x70u;
    {
        (void)lift_sub(32, eax, 0x20u, &fl);
    }
    if (fl.cf)
        goto L_4d78ba;
    if (fl.cf || fl.zf)
        goto L_4d7893;
    {
        (void)lift_sub(32, eax, 0x30u, &fl);
    }
    if (fl.cf)
        goto L_4d78c3;
    if (fl.cf || fl.zf)
        goto L_4d78a0;
    {
        (void)lift_sub(32, eax, 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4d78ad;
    goto L_4d78c3;
L_4d7886:
    lift_store(&env, esp, 0x118u, 4, 0x0u);
    goto L_4d78c3;
L_4d7893:
    lift_store(&env, esp, 0x118u, 4, 0x1u);
    goto L_4d78c3;
L_4d78a0:
    lift_store(&env, esp, 0x118u, 4, 0x2u);
    goto L_4d78c3;
L_4d78ad:
    lift_store(&env, esp, 0x118u, 4, 0x3u);
    goto L_4d78c3;
L_4d78ba:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d7886;
    {
        (void)lift_sub(32, eax, 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4d7886;
L_4d78c3:
    lift_store(&env, esp, 0x104u, 4, 0xcu);
    lift_store(&env, esp, 0x108u, 4, 0x0u);
    {
        (void)lift_and(8, lift_load(&env, esp, 0x11cu, 1), 0x80u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
    lift_store(&env, esp, 0x10cu, 4, eax);
    {
        (void)lift_and(8, lift_load(&env, esp, 0x11du, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4d7910;
    {
        (void)lift_and(8, lift_load(&env, esp, 0x11du, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4d7909;
    eax = 0x4u;
    goto L_4d7915;
L_4d7909:
    eax = 0x2u;
    goto L_4d7915;
L_4d7910:
    eax = 0x3u;
L_4d7915:
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
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x110u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x128u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x128u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b34u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4d7965;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4d7961;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1bbcu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebx, 0xcu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9ae0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = edi;
    lift_store(&env, ebx, 0x8u, 4, eax);
    eax = (ebx + 0x10u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4d7961:
    eax = eax ^ eax;
    goto L_4d7974;
L_4d7965:
    lift_store(&env, esi, 0x8u, 4, 0x1u);
    lift_store(&env, esi, 0x4u, 4, eax);
    eax = 0x1u;
L_4d7974:
    {
        uint32_t r = lift_add(32, esp, 0x120u, &fl);
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

uint32_t lifted_f4d7980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D7980_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D7980_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x4u;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4d798f;
    eax = eax ^ eax;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
L_4d798f:
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
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x4u, 4);
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
        goto L_4d79b4;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1bbcu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9930u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_4d79b4:
    eax = lift_load(&env, esp, 0x0u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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

uint32_t lifted_f4d7a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D7A10_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D7A10_STACK, 0, entry);
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
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ca8u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    ebx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4d7a35;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1bbcu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9930u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_4d7a35:
    eax = ebx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d7bb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D7BB0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D7BB0_STACK, 0, entry);
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
    esi = lift_load(&env, eax, 0x0u, 4);
    ebx = 0x1u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x30u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x2u;
    edi = eax;
    esi = lift_load(&env, ecx, 0x0u, 4);
    edx = edx ^ edx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x30u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edx = edi;
    ebp = lift_load(&env, ecx, 0x0u, 4);
    ebx = ebx ^ ebx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebp, 0x30u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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

uint32_t lifted_f4d7c40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D7C40_STACK + 4 + 4 * 2 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D7C40_STACK, 2, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
    esp = esp - 0x164u;
    eax = (ebp + 0xffffffdcu);
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
    eax = (ebp + 0xfffffff0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x104u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffe0u, 4, 0x4ec1ecu);
    lift_store(&env, ebp, 0xffffffe4u, 4, 0x519d30u);
    {
        uint32_t v = lift_load(&env, ebp, 0xcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1bb8u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d7ca3;
    {
        uint32_t v = 0x104u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0xcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1d20u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    goto L_4d7d54;
L_4d7ca3:
    eax = (ebp + 0xfffffff4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffff4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d7d70u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
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
    eax = (ebp + 0xfffffff8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xfffffffcu);
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
        uint32_t v = lift_load(&env, ebp, 0xfffffff4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c04u, eax, edx, ebx, ecx, 8, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 32u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d7cf9;
    eax = (ebp + 0xfffffff4u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
    eax = ecx;
    esp = ebp;
    ebp = lift_load(&env, esp, 0u, 4);
    esp += 4u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d7cf9:
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xfffffff8u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4d7d09;
    {
        uint32_t v = lift_load(&env, ebp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1904u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4d7d09:
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xfffffff8u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4d7d3e;
    eax = (ebp + 0xfffffe9cu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0xcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b60u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4d7d3e;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b5cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (ebp + 0xfffffec8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0xfffffff0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1d1cu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_4d7d3e:
    ecx = 0x1u;
    eax = (ebp + 0xfffffff4u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4d7d54:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
    eax = ecx;
    esp = ebp;
    ebp = lift_load(&env, esp, 0u, 4);
    esp += 4u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d9060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D9060_STACK + 4 + 4 * 2 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D9060_STACK, 2, entry);
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
    esp = esp - 0x14cu;
    esi = lift_load(&env, esp, 0x15cu, 4);
    {
        uint32_t v = lift_load(&env, esp, 0x158u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esi + 0x12u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d7c40u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d908c;
    lift_store(&env, esi, 0x12u, 1, 0x0u);
    goto L_4d9136;
L_4d908c:
    eax = esp;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x15cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b60u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4d90af;
    eax = eax ^ eax;
    {
        uint32_t r = lift_add(32, esp, 0x14cu, &fl);
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
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d90af:
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b5cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x7fu) & 0xffu);
    lift_store(&env, esi, 0x10u, 1, (eax & 0xffu));
    ebx = 0xffffffffu;
    eax = lift_load(&env, esp, 0x20u, 4);
    edx = (esp + 0x4u);
    lift_store(&env, esi, 0xcu, 4, eax);
    eax = (esp + 0x140u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xffffffffu;
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = (esp + 0xcu);
    lift_store(&env, esi, 0x0u, 4, eax);
    eax = (esp + 0x144u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (esi + 0x8u);
    eax = lift_load(&env, eax, 0x0u, 4);
    ebx = 0xffffffffu;
    lift_store(&env, edx, 0x0u, 4, eax);
    edx = (esp + 0x14u);
    eax = (esp + 0x148u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = (esi + 0x4u);
    edx = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
    edx = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4d9123;
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esi, 0x0u, 4, eax);
L_4d9123:
    eax = (esi + 0x8u);
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4d9131;
    edx = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
L_4d9131:
    eax = 0x1u;
L_4d9136:
    {
        uint32_t r = lift_add(32, esp, 0x14cu, &fl);
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
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_rtl_static_init_call(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_STATIC_INIT_CALL_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_STATIC_INIT_CALL_STACK, 0, entry);
    esp = esp - 0x4u;
    edx = 0x51a560u;
    eax = esp;
    lift_store(&env, esp, 0x0u, 4, 0x5c761cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4da71bu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_rtl_jump_capture(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_JUMP_CAPTURE_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_JUMP_CAPTURE_STACK, 0, entry);
    lift_store(&env, eax, 0x0u, 4, ebx);
    lift_store(&env, eax, 0x4u, 4, ecx);
    lift_store(&env, eax, 0x8u, 4, edx);
    lift_store(&env, eax, 0xcu, 4, esi);
    lift_store(&env, eax, 0x10u, 4, edi);
    lift_store(&env, eax, 0x14u, 4, ebp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        lift_store(&env, eax, 0x18u, 4, v);
    }
    lift_store(&env, eax, 0x1cu, 4, esp);
    {
        uint32_t v = lift_load(&env, eax, 0x18u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x20u, 2, 0u);
    lift_store(&env, eax, 0x22u, 2, 0u);
    lift_store(&env, eax, 0x24u, 2, 0u);
    lift_store(&env, eax, 0x26u, 2, 0u);
    lift_store(&env, eax, 0x28u, 2, 0u);
    lift_store(&env, eax, 0x2au, 2, 0u);
    {
        uint32_t v = env.chain;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        lift_store(&env, eax, 0x2cu, 4, v);
    }
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4da3ba(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DA3BA_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DA3BA_STACK, 0, entry);
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
    ebp = esp;
    esp = esp - 0x9cu;
    ebp = ebp - 0x82u;
    esi = eax;
    eax = (ebp + 0x4eu);
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
    lift_store(&env, ebp, 0x52u, 4, 0x4ec1ecu);
    lift_store(&env, ebp, 0x56u, 4, 0x51a910u);
    lift_store(&env, ebp, 0x5au, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0f8bu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0x72u, 4, eax);
    lift_store(&env, eax, 0xcu, 4, 0x0u);
    eax = (ebp + 0x1eu);
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
    ecx = (ebp + 0x72u);
    eax = (ebp + 0xffffffe6u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e38ffu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e08a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x10u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4da463;
L_4da41d:
    lift_store(&env, ebp, 0x7eu, 4, 0x0u);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x16u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4da5cf;
    lift_store(&env, ebp, 0xau, 1, 0x3u);
L_4da432:
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xbu, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4da61a;
    edx = 0x1u;
    eax = 0x512672u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dee73u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4da44b:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0x4eu, 4);
    env.chain = eax;
    esp = (ebp + 0x82u);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4da463:
    {
        uint32_t v = 0x10u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e08f0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x10u;
    esp = esp - eax;
    goto L_4da41d;
L_4da473:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x1au, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4da47e;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4da47e:
    eax = lift_load(&env, ebp, 0x1au, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0xcu, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4da50e;
    eax = (eax & 0xffu);
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4da496;
            case 1:
                goto L_4da50e;
            case 2:
                goto L_4da50e;
            case 3:
                goto L_4da4e1;
            case 4:
                goto L_4da50e;
            case 5:
                goto L_4da4f0;
            case 6:
                goto L_4da4ff;
            default:
                return 0u;
        }
    }
L_4da496:
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xbu, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4da545;
    eax = eax ^ eax;
L_4da4a2:
    ecx = 0x3u;
    edx = (ebp + 0x72u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    eax = (ebp + 0x3au);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e36d2u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = lift_load(&env, ebp, 0x72u, 4);
    eax = 0x5125b0u;
    lift_store(&env, ebp, 0x5au, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0c0cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0x3au);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0x5au, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e36e4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0x5au, 4, 0x0u);
L_4da4e1:
    edx = 0x1u;
    eax = 0x5125f2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dee73u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4da4f0:
    edx = 0x1u;
    eax = 0x51261bu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dee73u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4da4ff:
    edx = 0x1u;
    eax = 0x512643u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dee73u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4da50e:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4da513:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x7eu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4da550;
L_4da519:
    edx = lift_load(&env, ebp, 0xffffffe6u, 4);
    eax = lift_load(&env, ebp, 0x6u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd9f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4da524:
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xau, 1), 0x2u, &fl);
    }
    if (!fl.cf)
        goto L_4da65d;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xau, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4da44b;
L_4da538:
    eax = (ebp + 0xffffffe6u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4da26au, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4da432;
L_4da545:
    eax = lift_load(&env, ebp, 0x72u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    goto L_4da4a2;
L_4da550:
    lift_store(&env, ebp, 0x7eu, 4, 0x1u);
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xbu, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4da592;
    eax = lift_load(&env, ebp, 0xfffffff2u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xcu, 1)) & 0xffu);
    lift_store(&env, eax, 0xdu, 1, (edx & 0xffu));
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xbu, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4da57b;
    ebx = lift_load(&env, ebp, 0xfffffff2u, 4);
    eax = lift_load(&env, ebp, 0xfffffffeu, 4);
    lift_store(&env, ebx, 0x18u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe6u, 4);
    lift_store(&env, ebx, 0x20u, 4, eax);
L_4da57b:
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xau, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4da5b2;
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xbu, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4da524;
    eax = lift_load(&env, ebp, 0xfffffff2u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xdu, 1)) & 0xffu);
    lift_store(&env, eax, 0xcu, 1, (edx & 0xffu));
    goto L_4da524;
L_4da592:
    ebx = (ebp + 0x72u);
    edx = lift_load(&env, ebp, 0xffffffeau, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0c56u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    lift_store(&env, ebp, 0xfffffff2u, 4, eax);
    eax = lift_load(&env, ebp, 0xfffffffeu, 4);
    lift_store(&env, edx, 0x18u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe6u, 4);
    lift_store(&env, edx, 0x20u, 4, eax);
    goto L_4da57b;
L_4da5b2:
    eax = lift_load(&env, ebp, 0xfffffff2u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0xcu, 1, 0x0u);
    eax = (ebp + 0x1eu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x2au, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0xffffffe6u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f06b6u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    goto L_4da519;
L_4da5cf:
    eax = (ebp + 0x32u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x2eu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x22u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x1eu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c70u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xau, 1), 0x2u, &fl);
    }
    if (!fl.cf)
        goto L_4da5f8;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xau, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4da513;
    goto L_4da524;
L_4da5f8:
    if (fl.cf || fl.zf)
        goto L_4da513;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xau, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4da473;
    goto L_4da524;
L_4da60d:
    eax = (ebp + 0xffffffe6u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9fcau, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4da538;
L_4da61a:
    ecx = 0x3u;
    edx = (ebp + 0x72u);
    eax = (ebp + 0x62u);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3698u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0x72u, 4);
    eax = 0x51269du;
    lift_store(&env, ebp, 0x5au, 4, 0x3u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0c0cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0x62u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0x5au, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e36c4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0x5au, 4, 0x0u);
    goto L_4da44b;
L_4da65d:
    if (fl.cf || fl.zf)
        goto L_4da60d;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xau, 1), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4da432;
    goto L_4da44b;
}

uint32_t lifted_f4daae8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DAAE8_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DAAE8_STACK, 1, entry);
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
    esi = eax;
    lift_store(&env, esp, 0x4u, 4, ebx);
    lift_store(&env, esp, 0x0u, 4, ecx);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dab17;
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x1u, 1), 0x3au, &fl);
    }
    if (!fl.zf)
        goto L_4dab17;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4dab12;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x1u, 1, 0x3au);
    lift_store(&env, edx, 0x2u, 1, 0x0u);
    lift_store(&env, edx, 0x0u, 1, (ebx & 0xffu));
L_4dab12:
    esi = esi + 0x2u;
    goto L_4dab1e;
L_4dab17:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4dab1e;
    lift_store(&env, edx, 0x0u, 1, 0x0u);
L_4dab1e:
    ebp = esi;
    lift_store(&env, esp, 0x8u, 4, esi);
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, esi, 0x0u, 1)) & 0xffu) << 8);
    edi = edi ^ edi;
    {
        (void)lift_and(8, ((ebx >> 8) & 0xffu), ((ebx >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4dab5b;
L_4dab2c:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3a50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_sub(32, eax, 0x2eu, &fl);
    }
    if (!fl.zf)
        goto L_4dab3f;
    edi = esi;
    esi = esi + 1u;
    goto L_4dab56;
L_4dab3f:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3a90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        (void)lift_sub(32, edx, 0x5cu, &fl);
    }
    if (fl.zf)
        goto L_4dab52;
    {
        (void)lift_sub(32, edx, 0x2fu, &fl);
    }
    if (!fl.zf)
        goto L_4dab56;
L_4dab52:
    ebp = esi;
    edi = edi ^ edi;
L_4dab56:
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dab2c;
L_4dab5b:
    edx = lift_load(&env, esp, 0x8u, 4);
    ecx = 0xffu;
    ebx = ebp;
    eax = lift_load(&env, esp, 0x4u, 4);
    ebx = ebx - edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4daab0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4dab77;
    edi = esi;
L_4dab77:
    ecx = 0xffu;
    eax = lift_load(&env, esp, 0x0u, 4);
    ebx = edi;
    edx = ebp;
    ebx = ebx - ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4daab0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0xffu;
    eax = lift_load(&env, esp, 0x1cu, 4);
    ebx = esi;
    edx = edi;
    ebx = ebx - edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4daab0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dac10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DAC10_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DAC10_STACK, 0, entry);
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
    esp = esp - 0x4u;
    eax = (esp + 0x18u);
    ebx = esp;
    edx = lift_load(&env, esp, 0x14u, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd0a4u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dac40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DAC40_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DAC40_STACK, 0, entry);
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
    ebp = eax;
    esi = lift_load(&env, 0u, 0x5c81d4u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4dac91;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dac91;
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
    edi = ecx;
    goto L_4dac8b;
L_4dac6c:
    ebx = edi;
    edx = ebp;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e4080u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dac88;
    {
        (void)lift_sub(8, lift_load(&env, ecx, edi + 0x0u, 1), 0x3du, &fl);
    }
    if (!fl.zf)
        goto L_4dac88;
    eax = (edi + 0x1u);
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    goto L_4dac93;
L_4dac88:
    esi = esi + 0x4u;
L_4dac8b:
    ecx = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4dac6c;
L_4dac91:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4dac93:
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

uint32_t lifted_f4dbb30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DBB30_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DBB30_STACK, 0, entry);
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
    esp = esp - 0x4u;
    edi = eax;
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = lift_load(&env, edi, 0x8u, 4);
    esi = lift_load(&env, edi, 0xcu, 4);
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4dbb5d;
    eax = lift_load(&env, edi, 0x14u, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, (esi * 8u) + 0x0u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dbc26;
L_4dbb5d:
    esi = 0x1u;
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4dbb72;
    goto L_4dbb7d;
L_4dbb68:
    esi = esi + 1u;
    eax = eax + 0x8u;
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dbb78;
    goto L_4dbb7d;
L_4dbb72:
    eax = lift_load(&env, edi, 0x14u, 4);
    eax = eax + 0x8u;
L_4dbb78:
    {
        (void)lift_and(8, lift_load(&env, eax, 0x0u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4dbb68;
L_4dbb7d:
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dbc26;
    ebp = lift_load(&env, edi, 0x8u, 4);
    ebp = ebp + 0x20u;
    eax = ((ebp * 8u));
    lift_store(&env, esp, 0x0u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x14u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbbaa;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x2002u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c0cu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    goto L_4dbbcf;
L_4dbbaa:
    {
        uint32_t v = lift_load(&env, edi, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c20u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x2002u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c28u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
L_4dbbcf:
    ebx = eax;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4dbbf7;
    {
        uint32_t v = lift_load(&env, edi, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c20u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c24u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (edi + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dbbf7:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c24u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ecx = eax;
    ebx = ebp;
    edx = edx ^ edx;
    eax = lift_load(&env, edi, 0x8u, 4);
    ebx = ebx - lift_load(&env, edi, 0x8u, 4);
    eax = ((eax * 8u));
    ebx = ((ebx * 8u));
    eax = eax + ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x8u, 4, ebp);
    lift_store(&env, edi, 0x14u, 4, ecx);
L_4dbc26:
    {
        (void)lift_sub(32, esi, lift_load(&env, edi, 0x10u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dbc31;
    eax = (esi + 0x1u);
    lift_store(&env, edi, 0x10u, 4, eax);
L_4dbc31:
    eax = lift_load(&env, edi, 0x14u, 4);
    edi = edi + 0x20u;
    lift_store(&env, eax, (esi * 8u) + 0x0u, 1, lift_load(&env, eax, (esi * 8u) + 0x0u, 1) | 0x1u);
    eax = (esi + 0x1u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, edi, 0xffffffecu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = esi;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dbd20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DBD20_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DBD20_STACK, 0, entry);
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
    esi = eax;
    lift_store(&env, esp, 0x0u, 4, edx);
    ebp = ebx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbd43;
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edi = lift_load(&env, esi, 0x4u, 4);
    goto L_4dbd4e;
L_4dbd43:
    {
        uint32_t v = lift_load(&env, eax, 0x0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1cdcu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edi = eax;
L_4dbd4e:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4dbd5e;
    eax = lift_load(&env, esp, 0x0u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edi, 0x8u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dbe43;
L_4dbd5e:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4dbe4c;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4dbdb5;
    {
        uint32_t v = 0x10u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dba80u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dbd7b;
    lift_store(&env, eax, 0x0u, 4, 0x51ac34u);
L_4dbd7b:
    lift_store(&env, eax, 0x8u, 4, 0x0u);
    lift_store(&env, eax, 0xcu, 4, 0x0u);
    edi = eax;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbd9b;
    eax = (esi + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4dbd9b:
    eax = (esi + 0x18u);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dba10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbdb5;
    eax = (esi + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4dbdb5:
    {
        (void)lift_sub(32, lift_load(&env, edi, 0xcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbdd1;
    eax = lift_load(&env, esi, 0x10u, 4);
    eax = ((eax * 4u));
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c4cu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    goto L_4dbde8;
L_4dbdd1:
    eax = lift_load(&env, esi, 0x10u, 4);
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = ((eax * 4u));
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, edi, 0xcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c58u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
L_4dbde8:
    lift_store(&env, edi, 0xcu, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, edi, 0xcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbe06;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbe01;
    eax = (esi + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4dbe01:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dbe06:
    eax = lift_load(&env, esi, 0x10u, 4);
    eax = eax - lift_load(&env, edi, 0x8u, 4);
    ebx = ((eax * 4u));
    eax = lift_load(&env, edi, 0x8u, 4);
    edx = lift_load(&env, edi, 0xcu, 4);
    eax = ((eax * 4u));
    eax = eax + edx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esi, 0x10u, 4);
    lift_store(&env, edi, 0x8u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4dbe40;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ce0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    goto L_4dbe43;
L_4dbe40:
    lift_store(&env, esi, 0x4u, 4, edi);
L_4dbe43:
    eax = lift_load(&env, esp, 0x0u, 4);
    ebx = lift_load(&env, edi, 0xcu, 4);
    lift_store(&env, ebx, (eax * 4u) + 0x0u, 4, ebp);
L_4dbe4c:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbe5c;
    esi = esi + 0x20u;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dbe5c:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dbf80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DBF80_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DBF80_STACK, 0, entry);
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
    ebx = eax;
    esi = edx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbfba;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c77a8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbfae;
    eax = 0x5c7770u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dbfa9;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbac0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dbfa9:
    lift_store(&env, 0u, 0x5c77a8u, 4, eax);
L_4dbfae:
    eax = lift_load(&env, 0u, 0x5c77a8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbb30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
L_4dbfba:
    eax = lift_load(&env, 0u, 0x5c77a8u, 4);
    {
        uint32_t v = lift_load(&env, eax, 0x0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1cdcu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dbfd3;
    {
        (void)lift_sub(32, edi, lift_load(&env, eax, 0x8u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dbfd7;
L_4dbfd3:
    eax = eax ^ eax;
    goto L_4dbfdd;
L_4dbfd7:
    eax = lift_load(&env, eax, 0xcu, 4);
    eax = lift_load(&env, eax, (edi * 4u) + 0x0u, 4);
L_4dbfdd:
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dbff8;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, esi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x5c77a8u, 4);
    ecx = eax;
    edx = lift_load(&env, ebx, 0x0u, 4);
    ebx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbd20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dbff8:
    eax = ecx;
    {
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

uint32_t lifted_f4df320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DF320_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DF320_STACK, 0, entry);
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
    esp = esp - 0x70u;
    esi = ebx;
    edi = ecx;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) ^ (ebx & 0xffu)) & 0xffu);
    ecx = 0x64u;
    lift_store(&env, esp, 0x6cu, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, esp, 0x0u, 4, eax);
    lift_store(&env, esp, 0x1eu, 2, (ebx & 0xffffu));
    ebx = ebx ^ ebx;
    lift_store(&env, esp, 0x1cu, 2, (ecx & 0xffffu));
    lift_store(&env, esp, 0x10u, 4, ebx);
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, edx, 0x0u, 1)) & 0xffu) << 8);
    lift_store(&env, esp, 0x68u, 4, edx);
    {
        (void)lift_and(8, ((ebx >> 8) & 0xffu), ((ebx >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4df6ba;
L_4df359:
    eax = lift_load(&env, esp, 0x68u, 4);
    ebp = lift_load(&env, esp, 0x68u, 4);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, eax, 0x0u, 1)) & 0xffu) << 8);
    ebp = ebp + 1u;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x25u, &fl);
    }
    if (fl.zf)
        goto L_4df37a;
    edx = edx ^ edx;
    eax = esp;
    edx = (edx & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
    lift_store(&env, esp, 0x68u, 4, ebp);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4df692;
L_4df37a:
    ebx = esp;
    eax = lift_load(&env, esi, 0x0u, 4);
    edx = (esp + 0x60u);
    lift_store(&env, esp, 0x60u, 4, eax);
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df6c8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    eax = lift_load(&env, esp, 0x60u, 4);
    ebp = ebp + 1u;
    lift_store(&env, esi, 0x0u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffffu, 1)) & 0xffu);
    lift_store(&env, esp, 0x68u, 4, ebp);
    lift_store(&env, esp, 0x15u, 1, (eax & 0xffu));
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4df6ba;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6eu, &fl);
    }
    if (!fl.zf)
        goto L_4df521;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esp, 0x1eu, 1)) & 0xffu);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4df409;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4df3de;
    edx = lift_load(&env, esi, 0x0u, 4);
    edx = edx + 0x8u;
    lift_store(&env, esi, 0x0u, 4, edx);
    edx = lift_load(&env, edx, 0xfffffff8u, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    goto L_4df6ba;
L_4df3de:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4df4cf;
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, esi, 0x0u, 4, eax);
    edx = lift_load(&env, eax, 0xfffffffcu, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    goto L_4df6ba;
L_4df409:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4df49b;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4df442;
    ecx = lift_load(&env, esi, 0x0u, 4);
    ecx = ecx + 0x8u;
    lift_store(&env, esi, 0x0u, 4, ecx);
    edx = lift_load(&env, ecx, 0xfffffff8u, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x70u, &fl);
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
L_4df442:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4df471;
    ebx = lift_load(&env, esi, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, esi, 0x0u, 4, ebx);
    edx = lift_load(&env, ebx, 0xfffffffcu, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x70u, &fl);
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
L_4df471:
    edx = lift_load(&env, esi, 0x0u, 4);
    edx = edx + 0x4u;
    lift_store(&env, esi, 0x0u, 4, edx);
    edx = lift_load(&env, edx, 0xfffffffcu, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x70u, &fl);
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
L_4df49b:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4df4ca;
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax + 0x8u;
    lift_store(&env, esi, 0x0u, 4, eax);
    edx = lift_load(&env, eax, 0xfffffff8u, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x70u, &fl);
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
L_4df4ca:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4df4f8;
L_4df4cf:
    ebp = lift_load(&env, esi, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, esi, 0x0u, 4, ebp);
    edx = lift_load(&env, ebp, 0xfffffffcu, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x70u, &fl);
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
L_4df4f8:
    ecx = lift_load(&env, esi, 0x0u, 4);
    ecx = ecx + 0x4u;
    lift_store(&env, esi, 0x0u, 4, ecx);
    edx = lift_load(&env, ecx, 0xfffffffcu, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x70u, &fl);
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
L_4df521:
    ecx = (esp + 0x6cu);
    ebx = esp;
    eax = lift_load(&env, esi, 0x0u, 4);
    edx = (esp + 0x64u);
    lift_store(&env, esp, 0x64u, 4, eax);
    eax = (esp + 0x38u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dfb24u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    eax = lift_load(&env, esp, 0x64u, 4);
    (void)(edx);
    lift_store(&env, esi, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x20u, 4);
    ecx = lift_load(&env, esp, 0x24u, 4);
    edx = lift_load(&env, esp, 0x28u, 4);
    eax = eax + ecx;
    ebx = lift_load(&env, esp, 0x2cu, 4);
    eax = eax + edx;
    ecx = lift_load(&env, esp, 0x30u, 4);
    eax = eax + ebx;
    edx = lift_load(&env, esp, 0x34u, 4);
    eax = eax + ecx;
    ebx = lift_load(&env, esp, 0x4u, 4);
    eax = eax + edx;
    ebx = ebx - eax;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esp, 0x1eu, 1)) & 0xffu);
    lift_store(&env, esp, 0x4u, 4, ebx);
    {
        (void)lift_and(8, (edx & 0xffu), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_4df596;
    {
        (void)lift_sub(8, lift_load(&env, esp, 0x16u, 1), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4df596;
L_4df580:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df596;
    edx = 0x20u;
    eax = esp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x4u, 4, lift_load(&env, esp, 0x4u, 4) - 1u);
    goto L_4df580;
L_4df596:
    eax = lift_load(&env, esp, 0x20u, 4);
    ebx = (esp + 0x38u);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df5b8;
L_4df5a2:
    edx = edx ^ edx;
    eax = esp;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x20u, 4);
    edx = edx - 1u;
    ebx = ebx + 1u;
    lift_store(&env, esp, 0x20u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4df5a2;
L_4df5b8:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x24u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df5ce;
    edx = 0x30u;
    eax = esp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x24u, 4, lift_load(&env, esp, 0x24u, 4) - 1u);
    goto L_4df5b8;
L_4df5ce:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esp, 0x15u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x73u, &fl);
    }
    if (!fl.zf)
        goto L_4df60a;
    {
        (void)lift_and(8, lift_load(&env, esp, 0x1eu, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4df5ed;
    ebx = esp;
    ecx = edi;
    edx = 0u;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dfac0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4df63b;
L_4df5ed:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x28u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df63b;
    edx = edx ^ edx;
    eax = esp;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x28u, 4);
    edx = edx - 1u;
    ebp = ebp + 1u;
    lift_store(&env, esp, 0x28u, 4, edx);
    goto L_4df5ed;
L_4df60a:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x53u, &fl);
    }
    if (!fl.zf)
        goto L_4df61e;
    ebx = esp;
    ecx = edi;
    edx = 0u;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dfac0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4df63b;
L_4df61e:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x28u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df63b;
    edx = edx ^ edx;
    eax = esp;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, esp, 0x28u, 4);
    ecx = ecx - 1u;
    ebp = ebp + 1u;
    lift_store(&env, esp, 0x28u, 4, ecx);
    goto L_4df61e;
L_4df63b:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x2cu, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df651;
    edx = 0x30u;
    eax = esp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x2cu, 4, lift_load(&env, esp, 0x2cu, 4) - 1u);
    goto L_4df63b;
L_4df651:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x30u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df66e;
    edx = edx ^ edx;
    eax = esp;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x30u, 4);
    edx = edx - 1u;
    ebp = ebp + 1u;
    lift_store(&env, esp, 0x30u, 4, edx);
    goto L_4df651;
L_4df66e:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x34u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df684;
    edx = 0x30u;
    eax = esp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x34u, 4, lift_load(&env, esp, 0x34u, 4) - 1u);
    goto L_4df66e;
L_4df684:
    {
        (void)lift_and(8, lift_load(&env, esp, 0x1eu, 1), 0x8u, &fl);
    }
    if (fl.zf)
        goto L_4df692;
L_4df68b:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4df6ab;
L_4df692:
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x70u, &fl);
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
L_4df6ab:
    edx = 0x20u;
    eax = esp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x4u, 4, lift_load(&env, esp, 0x4u, 4) - 1u);
    goto L_4df68b;
L_4df6ba:
    eax = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x70u, &fl);
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

uint32_t lifted_f4e04ec(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E04EC_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E04EC_STACK, 0, entry);
    eax = lift_load(&env, 0u, 0x5c7b9cu, 4);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e08a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E08A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E08A0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = esp;
    {
        uint32_t r = lift_sub(32, eax, lift_load(&env, edx, 0x0u, 4), &fl);
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

uint32_t lifted_f4e0c0c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0C0C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0C0C_STACK, 0, entry);
L_4dee73:
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
    ecx = edx;
    edx = 0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dee8e;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb4d4u, eax, edx, ebx, ecx, 0, esp);
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
L_4dee8e:
    edx = ecx;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6250u, eax, edx, ebx, ecx, 0, esp);
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
    lift_store(&env, edx, 0xcu, 4, eax);
    eax = lift_load(&env, edx, 0x8u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e0c1a;
    lift_store(&env, eax, 0xcu, 1, 0x3u);
L_4e0c1a:
    lift_store(&env, edx, 0x4u, 1, lift_load(&env, edx, 0x4u, 1) | 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6c37u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = 0x5127fbu;
    goto L_4dee73;
}

uint32_t lifted_f4e0f8b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0F8B_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0F8B_STACK, 0, entry);
    esp = esp - 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax + lift_load(&env, 0u, 0x5c5c54u, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x4u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e0fac;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e0fb0;
    {
        (void)lift_and(8, lift_load(&env, eax, 0x4u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e0fb0;
L_4e0fac:
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e0fb0:
    eax = esp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6d16u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e10d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E10D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E10D0_STACK, 0, entry);
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
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x50a820u, 4), 0x3a4u, &fl);
    }
    if (!fl.zf)
        goto L_4e10ed;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_4e10ed;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e1135;
L_4e10ed:
    edx = (esp + 0x4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7120u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (esp + 0x4u);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6f30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, eax + 0x4u, 1, (edx & 0xffu));
    edx = esp;
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
    eax = (esp + 0xcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x400u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1becu, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4e1133;
    eax = lift_load(&env, esp, 0x0u, 4);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x8u) & 0xffu);
    eax = eax & 0xffffu;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e1133:
    eax = eax ^ eax;
L_4e1135:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e33d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E33D0_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E33D0_STACK, 4, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x24u;
    esi = eax;
    eax = lift_load(&env, esp, 0x34u, 4);
    lift_store(&env, esp, 0xcu, 4, ecx);
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x30u, 4);
    ebx = ebx - 1u;
    lift_store(&env, esp, 0x4u, 4, eax);
    eax = lift_load(&env, esp, 0x2cu, 4);
    edx = edx - 0x76cu;
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = lift_load(&env, esp, 0x38u, 4);
    lift_store(&env, esp, 0x10u, 4, ebx);
    lift_store(&env, esp, 0x20u, 4, eax);
    eax = esp;
    lift_store(&env, esp, 0x14u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7850u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x0u, 4, eax);
    eax = esi;
    {
        uint32_t r = lift_add(32, esp, 0x24u, &fl);
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

uint32_t lifted_f4e3470(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3470_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3470_STACK, 0, entry);
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
    esp = esp - 0x1cu;
    esi = eax;
    eax = (esp + 0x10u);
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
    eax = lift_call(&env, 0x4f1b54u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e34aa;
    eax = esp;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x14u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b58u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e34aa;
    edx = esp;
    eax = (esp + 0x18u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3420u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0x18u, 4);
L_4e34aa:
    lift_store(&env, esi, 0x0u, 4, eax);
    eax = esi;
    {
        uint32_t r = lift_add(32, esp, 0x1cu, &fl);
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

uint32_t lifted_f4e3698(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3698_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3698_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = eax;
    lift_store(&env, eax, 0x0u, 4, ebx);
    lift_store(&env, eax, 0x4u, 4, edx);
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = lift_load(&env, eax, 0x20u, 4);
    lift_store(&env, esi, 0x8u, 4, eax);
    lift_store(&env, esi, 0xcu, 1, (ecx & 0xffu));
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, eax, 0x20u, 4, esi);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e36b8;
    eax = esi;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e36b8:
    eax = env.chain;
    lift_store(&env, esi, 0x0u, 4, eax);
    eax = esi;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

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

uint32_t lifted_f4e960c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E960C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E960C_STACK, 0, entry);
L_4e9514:
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
    esp = esp - 0xacu;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, 0u, 0x50b0e8u, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e9532;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e95ff;
L_4e9532:
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, 0u, 0x50b0e8u, 1)) & 0xffu) << 8);
    eax = esp;
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) | 0x2u) & 0xffu) << 8);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x50b0e8u, 1, ((edx >> 8) & 0xffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1bfcu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.cf)
        goto L_4e95ff;
    if (fl.cf || fl.zf)
        goto L_4e958b;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e95ff;
    lift_store(&env, 0u, 0x50b0e0u, 4, 0x1u);
    edx = lift_load(&env, esp, 0xa8u, 4);
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebx = eax;
    lift_store(&env, 0u, 0x50b0e4u, 4, eax);
    ebx = 0u - ebx;
    lift_store(&env, 0u, 0x50b0e4u, 4, ebx);
    goto L_4e9593;
L_4e958b:
    ecx = ecx ^ ecx;
    lift_store(&env, 0u, 0x50b0e0u, 4, ecx);
L_4e9593:
    edx = lift_load(&env, esp, 0x54u, 4);
    esi = lift_load(&env, esp, 0x0u, 4);
    edx = edx + esi;
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax - edx;
    ebx = 0x80u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = (esp + 0x4u);
    lift_store(&env, 0u, 0x50b0dcu, 4, eax);
    eax = 0x50afd0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e95cd;
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x50afd0u, 1, ((ebx >> 8) & 0xffu));
    goto L_4e95d5;
L_4e95cd:
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) ^ (ebx & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x50b050u, 1, (ebx & 0xffu));
L_4e95d5:
    ebx = 0x80u;
    edx = (esp + 0x58u);
    eax = 0x50b051u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e95f7;
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) ^ ((ecx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x50b051u, 1, ((ecx >> 8) & 0xffu));
    goto L_4e95ff;
L_4e95f7:
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) ^ (ecx & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x50b0d1u, 1, (ecx & 0xffu));
L_4e95ff:
    {
        uint32_t r = lift_add(32, esp, 0xacu, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
    eax = 0x513080u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dac40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9514;
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
    esp = esp - 0x4u;
    esi = lift_load(&env, 0u, 0x50b0e4u, 4);
    edx = edx ^ edx;
    ebx = 0x50b0dcu;
    lift_store(&env, 0u, 0x50b0e0u, 4, edx);
    edx = 0x50afd0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e969cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, eax, 0x0u, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4e98a2;
    esi = lift_load(&env, 0u, 0x50b0e4u, 4);
    lift_store(&env, 0u, 0x50b051u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, 0u, 0x50b0e4u, 4, esi);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e98a2:
    ebx = 0x1u;
    edx = 0x50b051u;
    eax = lift_load(&env, 0u, 0x50b0dcu, 4);
    lift_store(&env, 0u, 0x50b0e0u, 4, ebx);
    eax = eax - 0xe10u;
    ebx = esp;
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e969cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, esp, 0x0u, 4);
    esi = lift_load(&env, 0u, 0x50b0dcu, 4);
    edx = eax;
    esi = esi - ecx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x50b0e4u, 4, esi);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2cu, &fl);
    }
    if (!fl.zf)
        goto L_4e98ef;
    edx = 0x50af88u;
    eax = eax + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e97b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
L_4e98ef:
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, edx, 0x0u, 1)) & 0xffu) << 8);
    esi = lift_load(&env, 0u, 0x50b0e4u, 4);
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), 0x2cu, &fl);
    }
    if (!fl.zf)
        goto L_4e9963;
    eax = (edx + 0x1u);
    edx = 0x50afacu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e97b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x50b0e4u, 4);
    ebx = 0xe10u;
    edx = esi;
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    edi = lift_load(&env, 0u, 0x50afb4u, 4);
    ebx = 0x3cu;
    edx = esi;
    edi = edi - eax;
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    ebp = lift_load(&env, 0u, 0x50afb0u, 4);
    ebp = ebp - edx;
    edx = esi;
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    eax = lift_load(&env, 0u, 0x50afacu, 4);
    lift_store(&env, 0u, 0x50afb4u, 4, edi);
    eax = eax - edx;
    lift_store(&env, 0u, 0x50afb0u, 4, ebp);
    lift_store(&env, 0u, 0x50afacu, 4, eax);
L_4e9963:
    lift_store(&env, 0u, 0x50b0e4u, 4, esi);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}
