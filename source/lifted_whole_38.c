/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_38.h"

uint32_t lifted_f4ca7b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA7B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA7B0_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x18u, &fl);
        esp = r;
    }
    lift_store(&env, 0u, 0x500b80u, 4, 0x4cb390u);
    lift_store(&env, 0u, 0x500b84u, 4, 0x0u);
    lift_store(&env, 0u, 0x500b88u, 4, 0x0u);
    lift_store(&env, esp, 0x0u, 4, 0x4cb3a0u);
    lift_store(&env, esp, 0x4u, 4, 0x0u);
    esi = esp;
    edi = 0x5c5c0cu;
    lift_store(&env, esp, 0x8u, 4, 0x0u);
    lift_store(&env, esp, 0xcu, 4, 0x4cb3b0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x10u, 4, 0x0u);
    eax = lift_load(&env, 0u, 0x5c5c0cu, 4);
    esi = (esp + 0xcu);
    lift_store(&env, 0u, 0x500ba0u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c5c10u, 4);
    edi = 0x5c5c18u;
    lift_store(&env, 0u, 0x500ba4u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c5c14u, 4);
    lift_store(&env, esp, 0x14u, 4, 0x0u);
    lift_store(&env, 0u, 0x500ba8u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, 0u, 0x5c5c18u, 4);
    edx = 0x500becu;
    lift_store(&env, 0u, 0x500bc0u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c5c1cu, 4);
    lift_store(&env, 0u, 0x500be0u, 4, 0x0u);
    lift_store(&env, 0u, 0x500bc4u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c5c20u, 4);
    lift_store(&env, 0u, 0x500be4u, 4, 0x0u);
    lift_store(&env, 0u, 0x500bc8u, 4, eax);
    eax = 0x5c5c24u;
    lift_store(&env, 0u, 0x500be8u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x500820u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec1f7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0x18u, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cb3d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CB3D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CB3D0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x500fbcu, 4, 0x0u);
    lift_store(&env, 0u, 0x500fc0u, 4, 0x0u);
    lift_store(&env, 0u, 0x500fc4u, 4, 0x0u);
    lift_store(&env, 0u, 0x500fc8u, 4, 0x0u);
    lift_store(&env, 0u, 0x500fccu, 4, 0x0u);
    lift_store(&env, 0u, 0x500fd0u, 4, 0x0u);
    lift_store(&env, 0u, 0x500ff0u, 4, 0x0u);
    lift_store(&env, 0u, 0x500ff4u, 4, 0x0u);
    lift_store(&env, 0u, 0x500ff8u, 4, 0x0u);
    lift_store(&env, 0u, 0x500ffcu, 4, 0x0u);
    lift_store(&env, 0u, 0x501000u, 4, 0x0u);
    edx = 0x501038u;
    eax = 0x5c5c4cu;
    lift_store(&env, 0u, 0x501004u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4cbe60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CBE60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CBE60_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x501368u;
    eax = 0x5c5c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4ce0e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CE0E0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CE0E0_STACK, 0, entry);
    eax = 0x501fc0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec1f7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x501fd0u;
    goto L_4ec1f7;
L_4df2e1:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = 0x50817eu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e14b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x50818eu, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = 0x50817eu;
    lift_store(&env, 0u, 0x50818eu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e14b7u, eax, edx, ebx, ecx, 0, esp);
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
L_4ec1f7:
    goto L_4df2e1;
}

uint32_t lifted_f4ceaa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CEAA0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CEAA0_STACK, 0, entry);
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
    esp = esp - 0x240u;
    {
        uint32_t v = 0x5123acu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esp, 0x124u, 4, 0x4d2ea0u);
    lift_store(&env, esp, 0x128u, 4, 0x0u);
    lift_store(&env, esp, 0x12cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a70u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, 0u, 0x5c5c68u, 4, eax);
    edx = edx ^ edx;
    eax = 0x5c5c6cu;
    edi = (esp + 0xcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf3a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5023f0u;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec1f7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5c5ca8u;
    esi = (esp + 0x120u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf3a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x502400u;
    edx = 0xffffffffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec1f7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5c5ce4u;
    lift_store(&env, esp, 0x18u, 4, 0x4d2ea0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf3a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x502410u;
    edx = 0xfffffffeu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec1f7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5c5d20u;
    lift_store(&env, esp, 0x1cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf3a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x502420u;
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec1f7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0xcu, 4);
    edi = (esp + 0x24u);
    lift_store(&env, 0u, 0x50279cu, 4, eax);
    eax = lift_load(&env, esp, 0x10u, 4);
    esi = (esp + 0x18u);
    lift_store(&env, 0u, 0x5027a0u, 4, eax);
    eax = lift_load(&env, esp, 0x14u, 4);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    lift_store(&env, 0u, 0x5027a4u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, esp, 0x24u, 4);
    lift_store(&env, 0u, 0x5027bcu, 4, eax);
    eax = lift_load(&env, esp, 0x28u, 4);
    lift_store(&env, 0u, 0x5027c0u, 4, eax);
    eax = lift_load(&env, esp, 0x2cu, 4);
    lift_store(&env, 0u, 0x5027c4u, 4, eax);
    lift_store(&env, esp, 0x30u, 4, 0x4d2ea0u);
    lift_store(&env, esp, 0x34u, 4, 0x0u);
    edi = (esp + 0x3cu);
    esi = (esp + 0x30u);
    lift_store(&env, esp, 0x38u, 4, 0x0u);
    lift_store(&env, esp, 0x48u, 4, 0x4d2ea0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x4cu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, esp, 0x50u, 4, 0x0u);
    lift_store(&env, 0u, 0x5027dcu, 4, eax);
    eax = lift_load(&env, esp, 0x40u, 4);
    edi = (esp + 0x54u);
    lift_store(&env, 0u, 0x5027e0u, 4, eax);
    eax = lift_load(&env, esp, 0x44u, 4);
    esi = (esp + 0x48u);
    lift_store(&env, 0u, 0x5027e4u, 4, eax);
    lift_store(&env, esp, 0x60u, 4, 0x4d2ea0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x64u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x54u, 4);
    lift_store(&env, esp, 0x68u, 4, 0x0u);
    lift_store(&env, 0u, 0x5027fcu, 4, eax);
    eax = lift_load(&env, esp, 0x58u, 4);
    edi = (esp + 0x6cu);
    lift_store(&env, 0u, 0x502800u, 4, eax);
    eax = lift_load(&env, esp, 0x5cu, 4);
    esi = (esp + 0x60u);
    lift_store(&env, 0u, 0x502804u, 4, eax);
    lift_store(&env, esp, 0x78u, 4, 0x4d2ea0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x7cu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x6cu, 4);
    lift_store(&env, esp, 0x80u, 4, 0x0u);
    lift_store(&env, 0u, 0x50281cu, 4, eax);
    eax = lift_load(&env, esp, 0x70u, 4);
    edi = (esp + 0x84u);
    lift_store(&env, 0u, 0x502820u, 4, eax);
    eax = lift_load(&env, esp, 0x74u, 4);
    esi = (esp + 0x78u);
    lift_store(&env, 0u, 0x502824u, 4, eax);
    lift_store(&env, esp, 0x90u, 4, 0x4d2ea0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x94u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x84u, 4);
    lift_store(&env, esp, 0x98u, 4, 0x0u);
    lift_store(&env, 0u, 0x50283cu, 4, eax);
    eax = lift_load(&env, esp, 0x88u, 4);
    edi = (esp + 0x9cu);
    lift_store(&env, 0u, 0x502840u, 4, eax);
    eax = lift_load(&env, esp, 0x8cu, 4);
    esi = (esp + 0x90u);
    lift_store(&env, 0u, 0x502844u, 4, eax);
    lift_store(&env, esp, 0xa8u, 4, 0x4d2eb0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0xacu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x9cu, 4);
    edi = (esp + 0xb4u);
    lift_store(&env, 0u, 0x50285cu, 4, eax);
    eax = lift_load(&env, esp, 0xa0u, 4);
    esi = (esp + 0xa8u);
    lift_store(&env, 0u, 0x502860u, 4, eax);
    eax = lift_load(&env, esp, 0xa4u, 4);
    lift_store(&env, esp, 0xb0u, 4, 0x0u);
    lift_store(&env, 0u, 0x502864u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, esp, 0xb4u, 4);
    lift_store(&env, 0u, 0x50287cu, 4, eax);
    eax = lift_load(&env, esp, 0xb8u, 4);
    lift_store(&env, 0u, 0x502880u, 4, eax);
    eax = lift_load(&env, esp, 0xbcu, 4);
    lift_store(&env, 0u, 0x502884u, 4, eax);
    lift_store(&env, esp, 0xc0u, 4, 0x4d2ec0u);
    lift_store(&env, esp, 0xc4u, 4, 0x0u);
    edi = (esp + 0xccu);
    esi = (esp + 0xc0u);
    lift_store(&env, esp, 0xc8u, 4, 0x0u);
    lift_store(&env, esp, 0xd8u, 4, 0x4d2ed0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0xdcu, 4, 0x0u);
    eax = lift_load(&env, esp, 0xccu, 4);
    lift_store(&env, esp, 0xe0u, 4, 0x0u);
    lift_store(&env, 0u, 0x50289cu, 4, eax);
    eax = lift_load(&env, esp, 0xd0u, 4);
    edi = (esp + 0xe4u);
    lift_store(&env, 0u, 0x5028a0u, 4, eax);
    eax = lift_load(&env, esp, 0xd4u, 4);
    esi = (esp + 0xd8u);
    lift_store(&env, 0u, 0x5028a4u, 4, eax);
    lift_store(&env, esp, 0xf0u, 4, 0x4d2ee0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0xf4u, 4, 0x0u);
    eax = lift_load(&env, esp, 0xe4u, 4);
    lift_store(&env, esp, 0xf8u, 4, 0x0u);
    lift_store(&env, 0u, 0x5028bcu, 4, eax);
    eax = lift_load(&env, esp, 0xe8u, 4);
    edi = (esp + 0xfcu);
    lift_store(&env, 0u, 0x5028c0u, 4, eax);
    eax = lift_load(&env, esp, 0xecu, 4);
    esi = (esp + 0xf0u);
    lift_store(&env, 0u, 0x5028c4u, 4, eax);
    lift_store(&env, esp, 0x108u, 4, 0x4d2ef0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x10cu, 4, 0x0u);
    eax = lift_load(&env, esp, 0xfcu, 4);
    lift_store(&env, esp, 0x110u, 4, 0x0u);
    lift_store(&env, 0u, 0x5028dcu, 4, eax);
    eax = lift_load(&env, esp, 0x100u, 4);
    edi = (esp + 0x114u);
    lift_store(&env, 0u, 0x5028e0u, 4, eax);
    eax = lift_load(&env, esp, 0x104u, 4);
    esi = (esp + 0x108u);
    lift_store(&env, 0u, 0x5028e4u, 4, eax);
    lift_store(&env, esp, 0x228u, 4, 0x4d2f00u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x22cu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x114u, 4);
    lift_store(&env, esp, 0x230u, 4, 0x0u);
    lift_store(&env, 0u, 0x5028fcu, 4, eax);
    eax = lift_load(&env, esp, 0x118u, 4);
    edi = (esp + 0x12cu);
    lift_store(&env, 0u, 0x502900u, 4, eax);
    eax = lift_load(&env, esp, 0x11cu, 4);
    esi = (esp + 0x228u);
    lift_store(&env, 0u, 0x502904u, 4, eax);
    lift_store(&env, esp, 0x138u, 4, 0x4d2f10u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x13cu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x12cu, 4);
    edi = (esp + 0x144u);
    lift_store(&env, 0u, 0x50291cu, 4, eax);
    eax = lift_load(&env, esp, 0x130u, 4);
    esi = (esp + 0x138u);
    lift_store(&env, 0u, 0x502920u, 4, eax);
    eax = lift_load(&env, esp, 0x134u, 4);
    lift_store(&env, esp, 0x140u, 4, 0x0u);
    lift_store(&env, 0u, 0x502924u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, esp, 0x144u, 4);
    lift_store(&env, 0u, 0x50293cu, 4, eax);
    eax = lift_load(&env, esp, 0x148u, 4);
    lift_store(&env, 0u, 0x502940u, 4, eax);
    eax = lift_load(&env, esp, 0x14cu, 4);
    lift_store(&env, 0u, 0x502944u, 4, eax);
    lift_store(&env, esp, 0x150u, 4, 0x4d2f20u);
    lift_store(&env, esp, 0x154u, 4, 0x0u);
    lift_store(&env, esp, 0x158u, 4, 0x0u);
    edi = (esp + 0x15cu);
    esi = (esp + 0x150u);
    lift_store(&env, esp, 0x168u, 4, 0x4d2f30u);
    lift_store(&env, esp, 0x16cu, 4, 0x0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x170u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x15cu, 4);
    lift_store(&env, esp, 0x180u, 4, 0x4d2f40u);
    lift_store(&env, 0u, 0x50295cu, 4, eax);
    eax = lift_load(&env, esp, 0x160u, 4);
    edi = (esp + 0x174u);
    lift_store(&env, 0u, 0x502960u, 4, eax);
    eax = lift_load(&env, esp, 0x164u, 4);
    esi = (esp + 0x168u);
    lift_store(&env, 0u, 0x502964u, 4, eax);
    lift_store(&env, esp, 0x184u, 4, 0x0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x188u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x174u, 4);
    lift_store(&env, esp, 0x198u, 4, 0x4d2f60u);
    lift_store(&env, 0u, 0x50297cu, 4, eax);
    eax = lift_load(&env, esp, 0x178u, 4);
    edi = esp;
    lift_store(&env, 0u, 0x502980u, 4, eax);
    eax = lift_load(&env, esp, 0x17cu, 4);
    esi = (esp + 0x180u);
    lift_store(&env, 0u, 0x502984u, 4, eax);
    lift_store(&env, esp, 0x19cu, 4, 0x0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x1a0u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x0u, 4);
    lift_store(&env, 0u, 0x5029bcu, 4, 0x4d2f50u);
    lift_store(&env, 0u, 0x5029c0u, 4, 0x0u);
    edi = (esp + 0x1a4u);
    lift_store(&env, 0u, 0x50299cu, 4, eax);
    eax = lift_load(&env, esp, 0x4u, 4);
    esi = (esp + 0x198u);
    lift_store(&env, 0u, 0x5029a0u, 4, eax);
    eax = lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, 0u, 0x5029c4u, 4, 0x0u);
    lift_store(&env, 0u, 0x5029a4u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, esp, 0x1a4u, 4);
    lift_store(&env, 0u, 0x5029fcu, 4, 0x4d2f70u);
    lift_store(&env, 0u, 0x5029dcu, 4, eax);
    eax = lift_load(&env, esp, 0x1a8u, 4);
    lift_store(&env, 0u, 0x502a00u, 4, 0x0u);
    lift_store(&env, 0u, 0x5029e0u, 4, eax);
    eax = lift_load(&env, esp, 0x1acu, 4);
    lift_store(&env, 0u, 0x502a04u, 4, 0x0u);
    lift_store(&env, 0u, 0x5029e4u, 4, eax);
    lift_store(&env, esp, 0x1b0u, 4, 0x4d2f80u);
    lift_store(&env, esp, 0x1b4u, 4, 0x0u);
    edi = (esp + 0x1bcu);
    esi = (esp + 0x1b0u);
    lift_store(&env, esp, 0x1b8u, 4, 0x0u);
    lift_store(&env, esp, 0x1c8u, 4, 0x4d2f90u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x1ccu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x1bcu, 4);
    lift_store(&env, esp, 0x1d0u, 4, 0x0u);
    lift_store(&env, 0u, 0x502a1cu, 4, eax);
    eax = lift_load(&env, esp, 0x1c0u, 4);
    edi = (esp + 0x1d4u);
    lift_store(&env, 0u, 0x502a20u, 4, eax);
    eax = lift_load(&env, esp, 0x1c4u, 4);
    esi = (esp + 0x1c8u);
    lift_store(&env, 0u, 0x502a24u, 4, eax);
    lift_store(&env, esp, 0x1e0u, 4, 0x4d2fa0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x1e4u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x1d4u, 4);
    lift_store(&env, esp, 0x1e8u, 4, 0x0u);
    lift_store(&env, 0u, 0x502a3cu, 4, eax);
    eax = lift_load(&env, esp, 0x1d8u, 4);
    edi = (esp + 0x18cu);
    lift_store(&env, 0u, 0x502a40u, 4, eax);
    eax = lift_load(&env, esp, 0x1dcu, 4);
    esi = (esp + 0x1e0u);
    lift_store(&env, 0u, 0x502a44u, 4, eax);
    lift_store(&env, esp, 0x1f8u, 4, 0x4d2fb0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x1fcu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x18cu, 4);
    lift_store(&env, esp, 0x200u, 4, 0x0u);
    lift_store(&env, 0u, 0x502a5cu, 4, eax);
    eax = lift_load(&env, esp, 0x190u, 4);
    edi = (esp + 0x204u);
    lift_store(&env, 0u, 0x502a60u, 4, eax);
    eax = lift_load(&env, esp, 0x194u, 4);
    esi = (esp + 0x1f8u);
    lift_store(&env, 0u, 0x502a64u, 4, eax);
    lift_store(&env, esp, 0x210u, 4, 0x4d2fc0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x214u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x204u, 4);
    lift_store(&env, esp, 0x218u, 4, 0x0u);
    lift_store(&env, 0u, 0x502a7cu, 4, eax);
    eax = lift_load(&env, esp, 0x208u, 4);
    edi = (esp + 0x21cu);
    lift_store(&env, 0u, 0x502a80u, 4, eax);
    eax = lift_load(&env, esp, 0x20cu, 4);
    esi = (esp + 0x210u);
    lift_store(&env, 0u, 0x502a84u, 4, eax);
    lift_store(&env, esp, 0x1ecu, 4, 0x4d2fd0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x1f0u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x21cu, 4);
    edi = (esp + 0x234u);
    lift_store(&env, 0u, 0x502a9cu, 4, eax);
    eax = lift_load(&env, esp, 0x220u, 4);
    esi = (esp + 0x1ecu);
    lift_store(&env, 0u, 0x502aa0u, 4, eax);
    eax = lift_load(&env, esp, 0x224u, 4);
    lift_store(&env, esp, 0x1f4u, 4, 0x0u);
    lift_store(&env, 0u, 0x502aa4u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, esp, 0x234u, 4);
    edx = 0x502ae8u;
    lift_store(&env, 0u, 0x502abcu, 4, eax);
    eax = lift_load(&env, esp, 0x238u, 4);
    lift_store(&env, 0u, 0x502adcu, 4, 0x0u);
    lift_store(&env, 0u, 0x502ac0u, 4, eax);
    eax = lift_load(&env, esp, 0x23cu, 4);
    lift_store(&env, 0u, 0x502ae0u, 4, 0x0u);
    lift_store(&env, 0u, 0x502ac4u, 4, eax);
    eax = 0x5c755cu;
    lift_store(&env, 0u, 0x502ae4u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0x240u, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d2fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D2FE0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D2FE0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x502e48u;
    eax = 0x5c7560u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4d3140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D3140_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D3140_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x30cu, &fl);
        esp = r;
    }
    lift_store(&env, 0u, 0x5c7564u, 4, 0x80000000u);
    lift_store(&env, 0u, 0x5c7568u, 4, 0x80000000u);
    lift_store(&env, 0u, 0x5c756cu, 4, 0x0u);
    lift_store(&env, 0u, 0x5c7570u, 4, 0x0u);
    lift_store(&env, esp, 0x0u, 4, 0x4d6490u);
    lift_store(&env, esp, 0x4u, 4, 0x0u);
    lift_store(&env, esp, 0x8u, 4, 0x0u);
    edi = (esp + 0xcu);
    esi = esp;
    lift_store(&env, esp, 0x18u, 4, 0x4d64a0u);
    lift_store(&env, esp, 0x1cu, 4, 0x0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    eax = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, esp, 0x30u, 4, 0x4d64b0u);
    lift_store(&env, 0u, 0x50316cu, 4, eax);
    eax = lift_load(&env, esp, 0x10u, 4);
    edi = (esp + 0x24u);
    lift_store(&env, 0u, 0x503170u, 4, eax);
    eax = lift_load(&env, esp, 0x14u, 4);
    esi = (esp + 0x18u);
    lift_store(&env, 0u, 0x503174u, 4, eax);
    lift_store(&env, esp, 0x34u, 4, 0x0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x38u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x24u, 4);
    lift_store(&env, esp, 0x48u, 4, 0x4d64c0u);
    lift_store(&env, 0u, 0x50318cu, 4, eax);
    eax = lift_load(&env, esp, 0x28u, 4);
    edi = (esp + 0x3cu);
    lift_store(&env, 0u, 0x503190u, 4, eax);
    eax = lift_load(&env, esp, 0x2cu, 4);
    esi = (esp + 0x30u);
    lift_store(&env, 0u, 0x503194u, 4, eax);
    lift_store(&env, esp, 0x4cu, 4, 0x0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x50u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, esp, 0x60u, 4, 0x4d64e0u);
    lift_store(&env, 0u, 0x5031acu, 4, eax);
    eax = lift_load(&env, esp, 0x40u, 4);
    edi = (esp + 0x54u);
    lift_store(&env, 0u, 0x5031b0u, 4, eax);
    eax = lift_load(&env, esp, 0x44u, 4);
    esi = (esp + 0x48u);
    lift_store(&env, 0u, 0x5031b4u, 4, eax);
    lift_store(&env, esp, 0x64u, 4, 0x0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x68u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x54u, 4);
    lift_store(&env, 0u, 0x5031ecu, 4, 0x4d64d0u);
    lift_store(&env, 0u, 0x5031f0u, 4, 0x0u);
    edi = (esp + 0x6cu);
    lift_store(&env, 0u, 0x5031ccu, 4, eax);
    eax = lift_load(&env, esp, 0x58u, 4);
    esi = (esp + 0x60u);
    lift_store(&env, 0u, 0x5031d0u, 4, eax);
    eax = lift_load(&env, esp, 0x5cu, 4);
    lift_store(&env, 0u, 0x5031f4u, 4, 0x0u);
    lift_store(&env, 0u, 0x5031d4u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, esp, 0x6cu, 4);
    lift_store(&env, 0u, 0x50320cu, 4, eax);
    eax = lift_load(&env, esp, 0x70u, 4);
    lift_store(&env, 0u, 0x503210u, 4, eax);
    eax = lift_load(&env, esp, 0x74u, 4);
    lift_store(&env, 0u, 0x503214u, 4, eax);
    lift_store(&env, esp, 0x78u, 4, 0x4d64f0u);
    lift_store(&env, esp, 0x7cu, 4, 0x0u);
    edi = (esp + 0x84u);
    esi = (esp + 0x78u);
    lift_store(&env, esp, 0x80u, 4, 0x0u);
    lift_store(&env, esp, 0x90u, 4, 0x4d6500u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x94u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x84u, 4);
    lift_store(&env, esp, 0x98u, 4, 0x0u);
    lift_store(&env, 0u, 0x50322cu, 4, eax);
    eax = lift_load(&env, esp, 0x88u, 4);
    edi = (esp + 0x9cu);
    lift_store(&env, 0u, 0x503230u, 4, eax);
    eax = lift_load(&env, esp, 0x8cu, 4);
    esi = (esp + 0x90u);
    lift_store(&env, 0u, 0x503234u, 4, eax);
    lift_store(&env, esp, 0xa8u, 4, 0x4d6510u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0xacu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x9cu, 4);
    lift_store(&env, esp, 0xb0u, 4, 0x0u);
    lift_store(&env, 0u, 0x50324cu, 4, eax);
    eax = lift_load(&env, esp, 0xa0u, 4);
    edi = (esp + 0xb4u);
    lift_store(&env, 0u, 0x503250u, 4, eax);
    eax = lift_load(&env, esp, 0xa4u, 4);
    esi = (esp + 0xa8u);
    lift_store(&env, 0u, 0x503254u, 4, eax);
    lift_store(&env, esp, 0xc0u, 4, 0x4d6520u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0xc4u, 4, 0x0u);
    eax = lift_load(&env, esp, 0xb4u, 4);
    edi = (esp + 0xccu);
    lift_store(&env, 0u, 0x50326cu, 4, eax);
    eax = lift_load(&env, esp, 0xb8u, 4);
    esi = (esp + 0xc0u);
    lift_store(&env, 0u, 0x503270u, 4, eax);
    eax = lift_load(&env, esp, 0xbcu, 4);
    lift_store(&env, esp, 0xc8u, 4, 0x0u);
    lift_store(&env, 0u, 0x503274u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, esp, 0xccu, 4);
    lift_store(&env, 0u, 0x5032acu, 4, 0x4d6530u);
    lift_store(&env, 0u, 0x5032b0u, 4, 0x0u);
    lift_store(&env, 0u, 0x5032b4u, 4, 0x0u);
    lift_store(&env, 0u, 0x5032ccu, 4, 0x4d6540u);
    lift_store(&env, 0u, 0x50328cu, 4, eax);
    eax = lift_load(&env, esp, 0xd0u, 4);
    lift_store(&env, 0u, 0x5032d0u, 4, 0x0u);
    lift_store(&env, 0u, 0x503290u, 4, eax);
    eax = lift_load(&env, esp, 0xd4u, 4);
    lift_store(&env, 0u, 0x5032d4u, 4, 0x0u);
    lift_store(&env, 0u, 0x503294u, 4, eax);
    lift_store(&env, esp, 0xd8u, 4, 0x4d6550u);
    lift_store(&env, esp, 0xdcu, 4, 0x0u);
    edi = (esp + 0xe4u);
    esi = (esp + 0xd8u);
    lift_store(&env, esp, 0xe0u, 4, 0x0u);
    lift_store(&env, esp, 0xf0u, 4, 0x4d6560u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0xf4u, 4, 0x0u);
    eax = lift_load(&env, esp, 0xe4u, 4);
    lift_store(&env, esp, 0xf8u, 4, 0x0u);
    lift_store(&env, 0u, 0x5032ecu, 4, eax);
    eax = lift_load(&env, esp, 0xe8u, 4);
    edi = (esp + 0xfcu);
    lift_store(&env, 0u, 0x5032f0u, 4, eax);
    eax = lift_load(&env, esp, 0xecu, 4);
    esi = (esp + 0xf0u);
    lift_store(&env, 0u, 0x5032f4u, 4, eax);
    lift_store(&env, esp, 0x108u, 4, 0x4d6570u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x10cu, 4, 0x0u);
    eax = lift_load(&env, esp, 0xfcu, 4);
    lift_store(&env, esp, 0x110u, 4, 0x0u);
    lift_store(&env, 0u, 0x50330cu, 4, eax);
    eax = lift_load(&env, esp, 0x100u, 4);
    edi = (esp + 0x114u);
    lift_store(&env, 0u, 0x503310u, 4, eax);
    eax = lift_load(&env, esp, 0x104u, 4);
    esi = (esp + 0x108u);
    lift_store(&env, 0u, 0x503314u, 4, eax);
    lift_store(&env, esp, 0x120u, 4, 0x4d6580u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x124u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x114u, 4);
    lift_store(&env, esp, 0x128u, 4, 0x0u);
    lift_store(&env, 0u, 0x50332cu, 4, eax);
    eax = lift_load(&env, esp, 0x118u, 4);
    edi = (esp + 0x12cu);
    lift_store(&env, 0u, 0x503330u, 4, eax);
    eax = lift_load(&env, esp, 0x11cu, 4);
    esi = (esp + 0x120u);
    lift_store(&env, 0u, 0x503334u, 4, eax);
    lift_store(&env, esp, 0x138u, 4, 0x4d6590u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x13cu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x12cu, 4);
    lift_store(&env, esp, 0x140u, 4, 0x0u);
    lift_store(&env, 0u, 0x50334cu, 4, eax);
    eax = lift_load(&env, esp, 0x130u, 4);
    edi = (esp + 0x144u);
    lift_store(&env, 0u, 0x503350u, 4, eax);
    eax = lift_load(&env, esp, 0x134u, 4);
    esi = (esp + 0x138u);
    lift_store(&env, 0u, 0x503354u, 4, eax);
    lift_store(&env, esp, 0x150u, 4, 0x4d65a0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x154u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x144u, 4);
    edi = (esp + 0x15cu);
    lift_store(&env, 0u, 0x50336cu, 4, eax);
    eax = lift_load(&env, esp, 0x148u, 4);
    esi = (esp + 0x150u);
    lift_store(&env, 0u, 0x503370u, 4, eax);
    eax = lift_load(&env, esp, 0x14cu, 4);
    lift_store(&env, esp, 0x158u, 4, 0x0u);
    lift_store(&env, 0u, 0x503374u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, esp, 0x15cu, 4);
    lift_store(&env, 0u, 0x50338cu, 4, eax);
    eax = lift_load(&env, esp, 0x160u, 4);
    lift_store(&env, 0u, 0x503390u, 4, eax);
    eax = lift_load(&env, esp, 0x164u, 4);
    lift_store(&env, 0u, 0x503394u, 4, eax);
    lift_store(&env, esp, 0x168u, 4, 0x4d65b0u);
    lift_store(&env, esp, 0x16cu, 4, 0x0u);
    edi = (esp + 0x174u);
    esi = (esp + 0x168u);
    lift_store(&env, esp, 0x170u, 4, 0x0u);
    lift_store(&env, esp, 0x180u, 4, 0x4d65c0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x184u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x174u, 4);
    lift_store(&env, esp, 0x188u, 4, 0x0u);
    lift_store(&env, 0u, 0x5033acu, 4, eax);
    eax = lift_load(&env, esp, 0x178u, 4);
    edi = (esp + 0x18cu);
    lift_store(&env, 0u, 0x5033b0u, 4, eax);
    eax = lift_load(&env, esp, 0x17cu, 4);
    esi = (esp + 0x180u);
    lift_store(&env, 0u, 0x5033b4u, 4, eax);
    lift_store(&env, esp, 0x198u, 4, 0x4d65d0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x19cu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x18cu, 4);
    lift_store(&env, esp, 0x1a0u, 4, 0x0u);
    lift_store(&env, 0u, 0x5033ccu, 4, eax);
    eax = lift_load(&env, esp, 0x190u, 4);
    edi = (esp + 0x1a4u);
    lift_store(&env, 0u, 0x5033d0u, 4, eax);
    eax = lift_load(&env, esp, 0x194u, 4);
    esi = (esp + 0x198u);
    lift_store(&env, 0u, 0x5033d4u, 4, eax);
    lift_store(&env, esp, 0x1b0u, 4, 0x4d65e0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x1b4u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x1a4u, 4);
    lift_store(&env, esp, 0x1b8u, 4, 0x0u);
    lift_store(&env, 0u, 0x5033ecu, 4, eax);
    eax = lift_load(&env, esp, 0x1a8u, 4);
    edi = (esp + 0x1bcu);
    lift_store(&env, 0u, 0x5033f0u, 4, eax);
    eax = lift_load(&env, esp, 0x1acu, 4);
    esi = (esp + 0x1b0u);
    lift_store(&env, 0u, 0x5033f4u, 4, eax);
    lift_store(&env, esp, 0x1c8u, 4, 0x4d65f0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x1ccu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x1bcu, 4);
    lift_store(&env, esp, 0x1d0u, 4, 0x0u);
    lift_store(&env, 0u, 0x50340cu, 4, eax);
    eax = lift_load(&env, esp, 0x1c0u, 4);
    edi = (esp + 0x1d4u);
    lift_store(&env, 0u, 0x503410u, 4, eax);
    eax = lift_load(&env, esp, 0x1c4u, 4);
    esi = (esp + 0x1c8u);
    lift_store(&env, 0u, 0x503414u, 4, eax);
    lift_store(&env, esp, 0x1e0u, 4, 0x4d6600u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x1e4u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x1d4u, 4);
    edi = (esp + 0x1ecu);
    lift_store(&env, 0u, 0x50342cu, 4, eax);
    eax = lift_load(&env, esp, 0x1d8u, 4);
    esi = (esp + 0x1e0u);
    lift_store(&env, 0u, 0x503430u, 4, eax);
    eax = lift_load(&env, esp, 0x1dcu, 4);
    lift_store(&env, esp, 0x1e8u, 4, 0x0u);
    lift_store(&env, 0u, 0x503434u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, esp, 0x1ecu, 4);
    lift_store(&env, 0u, 0x50344cu, 4, eax);
    eax = lift_load(&env, esp, 0x1f0u, 4);
    lift_store(&env, 0u, 0x503450u, 4, eax);
    eax = lift_load(&env, esp, 0x1f4u, 4);
    lift_store(&env, 0u, 0x503454u, 4, eax);
    lift_store(&env, esp, 0x1f8u, 4, 0x4d6610u);
    lift_store(&env, esp, 0x1fcu, 4, 0x0u);
    edi = (esp + 0x204u);
    esi = (esp + 0x1f8u);
    lift_store(&env, esp, 0x200u, 4, 0x0u);
    lift_store(&env, esp, 0x210u, 4, 0x4d6620u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x214u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x204u, 4);
    lift_store(&env, esp, 0x218u, 4, 0x0u);
    lift_store(&env, 0u, 0x50346cu, 4, eax);
    eax = lift_load(&env, esp, 0x208u, 4);
    edi = (esp + 0x21cu);
    lift_store(&env, 0u, 0x503470u, 4, eax);
    eax = lift_load(&env, esp, 0x20cu, 4);
    esi = (esp + 0x210u);
    lift_store(&env, 0u, 0x503474u, 4, eax);
    lift_store(&env, esp, 0x228u, 4, 0x4d6630u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x22cu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x21cu, 4);
    lift_store(&env, esp, 0x230u, 4, 0x0u);
    lift_store(&env, 0u, 0x50348cu, 4, eax);
    eax = lift_load(&env, esp, 0x220u, 4);
    edi = (esp + 0x234u);
    lift_store(&env, 0u, 0x503490u, 4, eax);
    eax = lift_load(&env, esp, 0x224u, 4);
    esi = (esp + 0x228u);
    lift_store(&env, 0u, 0x503494u, 4, eax);
    lift_store(&env, esp, 0x240u, 4, 0x4d6640u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x244u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x234u, 4);
    lift_store(&env, esp, 0x248u, 4, 0x0u);
    lift_store(&env, 0u, 0x5034acu, 4, eax);
    eax = lift_load(&env, esp, 0x238u, 4);
    esi = (esp + 0x240u);
    lift_store(&env, 0u, 0x5034b0u, 4, eax);
    eax = lift_load(&env, esp, 0x23cu, 4);
    edi = 0x5c7574u;
    lift_store(&env, 0u, 0x5034b4u, 4, eax);
    lift_store(&env, esp, 0x24cu, 4, 0x4d6650u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x250u, 4, 0x0u);
    eax = lift_load(&env, 0u, 0x5c7574u, 4);
    lift_store(&env, esp, 0x254u, 4, 0x0u);
    lift_store(&env, 0u, 0x5034ccu, 4, eax);
    eax = lift_load(&env, 0u, 0x5c7578u, 4);
    esi = (esp + 0x24cu);
    lift_store(&env, 0u, 0x5034d0u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c757cu, 4);
    edi = 0x5c7580u;
    lift_store(&env, 0u, 0x5034d4u, 4, eax);
    lift_store(&env, esp, 0x258u, 4, 0x4d6640u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x25cu, 4, 0x0u);
    eax = lift_load(&env, 0u, 0x5c7580u, 4);
    esi = (esp + 0x258u);
    lift_store(&env, 0u, 0x5034ecu, 4, eax);
    eax = lift_load(&env, 0u, 0x5c7584u, 4);
    edi = 0x5c758cu;
    lift_store(&env, 0u, 0x5034f0u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c7588u, 4);
    lift_store(&env, esp, 0x260u, 4, 0x0u);
    lift_store(&env, 0u, 0x5034f4u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, 0u, 0x5c758cu, 4);
    lift_store(&env, 0u, 0x50350cu, 4, eax);
    eax = lift_load(&env, 0u, 0x5c7590u, 4);
    lift_store(&env, 0u, 0x503510u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c7594u, 4);
    lift_store(&env, 0u, 0x503514u, 4, eax);
    lift_store(&env, esp, 0x264u, 4, 0x4d6650u);
    lift_store(&env, esp, 0x268u, 4, 0x0u);
    esi = (esp + 0x264u);
    edi = 0x5c7598u;
    lift_store(&env, esp, 0x26cu, 4, 0x0u);
    lift_store(&env, esp, 0x270u, 4, 0x4d6660u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x274u, 4, 0x0u);
    eax = lift_load(&env, 0u, 0x5c7598u, 4);
    lift_store(&env, esp, 0x278u, 4, 0x0u);
    lift_store(&env, 0u, 0x50352cu, 4, eax);
    eax = lift_load(&env, 0u, 0x5c759cu, 4);
    esi = (esp + 0x270u);
    lift_store(&env, 0u, 0x503530u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75a0u, 4);
    edi = 0x5c75a4u;
    lift_store(&env, 0u, 0x503534u, 4, eax);
    lift_store(&env, esp, 0x27cu, 4, 0x4d6660u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x280u, 4, 0x0u);
    eax = lift_load(&env, 0u, 0x5c75a4u, 4);
    lift_store(&env, esp, 0x284u, 4, 0x0u);
    lift_store(&env, 0u, 0x50354cu, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75a8u, 4);
    esi = (esp + 0x27cu);
    lift_store(&env, 0u, 0x503550u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75acu, 4);
    edi = 0x5c75b0u;
    lift_store(&env, 0u, 0x503554u, 4, eax);
    lift_store(&env, esp, 0x288u, 4, 0x4d6660u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x28cu, 4, 0x0u);
    eax = lift_load(&env, 0u, 0x5c75b0u, 4);
    lift_store(&env, esp, 0x290u, 4, 0x0u);
    lift_store(&env, 0u, 0x50356cu, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75b4u, 4);
    esi = (esp + 0x288u);
    lift_store(&env, 0u, 0x503570u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75b8u, 4);
    edi = 0x5c75bcu;
    lift_store(&env, 0u, 0x503574u, 4, eax);
    lift_store(&env, esp, 0x294u, 4, 0x4d6660u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x298u, 4, 0x0u);
    eax = lift_load(&env, 0u, 0x5c75bcu, 4);
    lift_store(&env, esp, 0x29cu, 4, 0x0u);
    lift_store(&env, 0u, 0x50358cu, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75c0u, 4);
    esi = (esp + 0x294u);
    lift_store(&env, 0u, 0x503590u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75c4u, 4);
    edi = 0x5c75c8u;
    lift_store(&env, 0u, 0x503594u, 4, eax);
    lift_store(&env, esp, 0x2a0u, 4, 0x4d6670u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x2a4u, 4, 0x0u);
    eax = lift_load(&env, 0u, 0x5c75c8u, 4);
    esi = (esp + 0x2a0u);
    lift_store(&env, 0u, 0x5035acu, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75ccu, 4);
    edi = 0x5c75d4u;
    lift_store(&env, 0u, 0x5035b0u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75d0u, 4);
    lift_store(&env, esp, 0x2a8u, 4, 0x0u);
    lift_store(&env, 0u, 0x5035b4u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, 0u, 0x5c75d4u, 4);
    lift_store(&env, 0u, 0x5035ccu, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75d8u, 4);
    lift_store(&env, 0u, 0x5035d0u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75dcu, 4);
    lift_store(&env, 0u, 0x5035d4u, 4, eax);
    lift_store(&env, esp, 0x2acu, 4, 0x4d6680u);
    lift_store(&env, esp, 0x2b0u, 4, 0x0u);
    esi = (esp + 0x2acu);
    edi = 0x5c75e0u;
    lift_store(&env, esp, 0x2b4u, 4, 0x0u);
    lift_store(&env, esp, 0x2b8u, 4, 0x4d6680u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x2bcu, 4, 0x0u);
    eax = lift_load(&env, 0u, 0x5c75e0u, 4);
    lift_store(&env, esp, 0x2c0u, 4, 0x0u);
    lift_store(&env, 0u, 0x5035ecu, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75e4u, 4);
    esi = (esp + 0x2b8u);
    lift_store(&env, 0u, 0x5035f0u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75e8u, 4);
    edi = 0x5c75ecu;
    lift_store(&env, 0u, 0x5035f4u, 4, eax);
    lift_store(&env, esp, 0x2c4u, 4, 0x4d6690u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x2c8u, 4, 0x0u);
    eax = lift_load(&env, 0u, 0x5c75ecu, 4);
    lift_store(&env, esp, 0x2ccu, 4, 0x0u);
    lift_store(&env, 0u, 0x50360cu, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75f0u, 4);
    edi = (esp + 0x2d0u);
    lift_store(&env, 0u, 0x503610u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c75f4u, 4);
    esi = (esp + 0x2c4u);
    lift_store(&env, 0u, 0x503614u, 4, eax);
    lift_store(&env, esp, 0x2dcu, 4, 0x4d66a0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x2e0u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x2d0u, 4);
    lift_store(&env, esp, 0x2e4u, 4, 0x0u);
    lift_store(&env, 0u, 0x50362cu, 4, eax);
    eax = lift_load(&env, esp, 0x2d4u, 4);
    edi = (esp + 0x2e8u);
    lift_store(&env, 0u, 0x503630u, 4, eax);
    eax = lift_load(&env, esp, 0x2d8u, 4);
    esi = (esp + 0x2dcu);
    lift_store(&env, 0u, 0x503634u, 4, eax);
    lift_store(&env, esp, 0x2f4u, 4, 0x4d66b0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x2f8u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x2e8u, 4);
    edi = (esp + 0x300u);
    lift_store(&env, 0u, 0x50364cu, 4, eax);
    eax = lift_load(&env, esp, 0x2ecu, 4);
    esi = (esp + 0x2f4u);
    lift_store(&env, 0u, 0x503650u, 4, eax);
    eax = lift_load(&env, esp, 0x2f0u, 4);
    lift_store(&env, esp, 0x2fcu, 4, 0x0u);
    lift_store(&env, 0u, 0x503654u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, esp, 0x300u, 4);
    edx = 0x503698u;
    lift_store(&env, 0u, 0x50366cu, 4, eax);
    eax = lift_load(&env, esp, 0x304u, 4);
    lift_store(&env, 0u, 0x50368cu, 4, 0x0u);
    lift_store(&env, 0u, 0x503670u, 4, eax);
    eax = lift_load(&env, esp, 0x308u, 4);
    lift_store(&env, 0u, 0x503690u, 4, 0x0u);
    lift_store(&env, 0u, 0x503674u, 4, eax);
    eax = 0x5c75f8u;
    lift_store(&env, 0u, 0x503694u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5036b0u;
    eax = 0x5c75f9u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5036c8u;
    eax = 0x5c75fau;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0x30cu, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d6830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D6830_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D6830_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x90u, &fl);
        esp = r;
    }
    lift_store(&env, esp, 0x0u, 4, 0x4d7430u);
    lift_store(&env, esp, 0x4u, 4, 0x0u);
    lift_store(&env, esp, 0x8u, 4, 0x0u);
    edi = (esp + 0xcu);
    esi = esp;
    lift_store(&env, esp, 0x18u, 4, 0x4d7460u);
    lift_store(&env, esp, 0x1cu, 4, 0x0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    eax = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, 0u, 0x503a3cu, 4, 0x4d7440u);
    lift_store(&env, 0u, 0x503a40u, 4, 0x0u);
    lift_store(&env, 0u, 0x503a44u, 4, 0x0u);
    lift_store(&env, 0u, 0x503a5cu, 4, 0x4d7450u);
    lift_store(&env, 0u, 0x503a60u, 4, 0x0u);
    lift_store(&env, 0u, 0x503a64u, 4, 0x0u);
    lift_store(&env, 0u, 0x503a1cu, 4, eax);
    eax = lift_load(&env, esp, 0x10u, 4);
    edi = (esp + 0x24u);
    lift_store(&env, 0u, 0x503a20u, 4, eax);
    eax = lift_load(&env, esp, 0x14u, 4);
    esi = (esp + 0x18u);
    lift_store(&env, 0u, 0x503a24u, 4, eax);
    lift_store(&env, esp, 0x30u, 4, 0x4d7470u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x34u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x24u, 4);
    lift_store(&env, esp, 0x38u, 4, 0x0u);
    lift_store(&env, 0u, 0x503a7cu, 4, eax);
    eax = lift_load(&env, esp, 0x28u, 4);
    edi = (esp + 0x3cu);
    lift_store(&env, 0u, 0x503a80u, 4, eax);
    eax = lift_load(&env, esp, 0x2cu, 4);
    esi = (esp + 0x30u);
    lift_store(&env, 0u, 0x503a84u, 4, eax);
    lift_store(&env, esp, 0x48u, 4, 0x4d7480u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x4cu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, esp, 0x50u, 4, 0x0u);
    lift_store(&env, 0u, 0x503a9cu, 4, eax);
    eax = lift_load(&env, esp, 0x40u, 4);
    edi = (esp + 0x54u);
    lift_store(&env, 0u, 0x503aa0u, 4, eax);
    eax = lift_load(&env, esp, 0x44u, 4);
    esi = (esp + 0x48u);
    lift_store(&env, 0u, 0x503aa4u, 4, eax);
    lift_store(&env, esp, 0x60u, 4, 0x4d7490u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x64u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x54u, 4);
    lift_store(&env, esp, 0x68u, 4, 0x0u);
    lift_store(&env, 0u, 0x503abcu, 4, eax);
    eax = lift_load(&env, esp, 0x58u, 4);
    edi = (esp + 0x6cu);
    lift_store(&env, 0u, 0x503ac0u, 4, eax);
    eax = lift_load(&env, esp, 0x5cu, 4);
    esi = (esp + 0x60u);
    lift_store(&env, 0u, 0x503ac4u, 4, eax);
    lift_store(&env, esp, 0x78u, 4, 0x4d74a0u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x7cu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x6cu, 4);
    edi = (esp + 0x84u);
    lift_store(&env, 0u, 0x503adcu, 4, eax);
    eax = lift_load(&env, esp, 0x70u, 4);
    esi = (esp + 0x78u);
    lift_store(&env, 0u, 0x503ae0u, 4, eax);
    eax = lift_load(&env, esp, 0x74u, 4);
    lift_store(&env, esp, 0x80u, 4, 0x0u);
    lift_store(&env, 0u, 0x503ae4u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, esp, 0x84u, 4);
    edx = 0x503b28u;
    lift_store(&env, 0u, 0x503afcu, 4, eax);
    eax = lift_load(&env, esp, 0x88u, 4);
    lift_store(&env, 0u, 0x503b1cu, 4, 0x0u);
    lift_store(&env, 0u, 0x503b00u, 4, eax);
    eax = lift_load(&env, esp, 0x8cu, 4);
    lift_store(&env, 0u, 0x503b20u, 4, 0x0u);
    lift_store(&env, 0u, 0x503b04u, 4, eax);
    eax = 0x5c75fcu;
    lift_store(&env, 0u, 0x503b24u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0x90u, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d74f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D74F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D74F0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x503e68u;
    eax = 0x5c7600u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4d8320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8320_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8320_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x5041a8u;
    eax = 0x5c7604u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4d8630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8630_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8630_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x5044b8u;
    eax = 0x5c7610u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4d8a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8A90_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8A90_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x5047d8u;
    eax = 0x5c7614u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4d9150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D9150_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D9150_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x2cu;
    eax = esp;
    edx = 0x504e08u;
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
    lift_store(&env, esp, 0x8u, 4, 0x51a308u);
    eax = 0x5c7618u;
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x504e20u;
    eax = 0x5c7619u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x20u, 4, 0x5c761cu);
    lift_store(&env, esp, 0x24u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, 0x5c761cu);
    eax = 0x5c761cu;
    edx = edx ^ edx;
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d92f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5c7628u, 4, 0x0u);
    lift_store(&env, 0u, 0x5c762cu, 4, 0x0u);
    lift_store(&env, 0u, 0x5c761cu, 4, 0x51a524u);
    lift_store(&env, 0u, 0x5c76b0u, 4, 0xf023u);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    eax = 0x504af0u;
    edx = 0x504e38u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec1f7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5c76b4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x20u, 4, 0x5c76b8u);
    lift_store(&env, esp, 0x24u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, 0x5c76b8u);
    eax = 0x5c76b8u;
    edx = edx ^ edx;
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d92f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5c76c4u, 4, 0x0u);
    lift_store(&env, 0u, 0x5c76c8u, 4, 0x0u);
    lift_store(&env, 0u, 0x5c76b8u, 4, 0x51a544u);
    lift_store(&env, 0u, 0x5c774cu, 4, 0xf021u);
    eax = 0x504b00u;
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec1f7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    {
        uint32_t r = lift_add(32, esp, 0x2cu, &fl);
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
}

uint32_t lifted_f4d9910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D9910_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D9910_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x5051a8u;
    eax = 0x5c7750u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4db8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DB8B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DB8B0_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e58b8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e59f4;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e59f4:
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e55d4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x5c7b9cu, 4);
    lift_store(&env, 0u, 0x5c8910u, 4, eax);
    lift_store(&env, 0u, 0x5c8914u, 4, ebx);
    lift_store(&env, 0u, 0x507cd0u, 4, ecx);
    lift_store(&env, 0u, 0x507cd4u, 4, esi);
    eax = lift_load(&env, edx, 0xdau, 4);
    lift_store(&env, 0u, 0x507cd8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ce0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dd190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DD190_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DD190_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x2cu;
    eax = esp;
    edx = 0x506a48u;
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
    lift_store(&env, esp, 0x8u, 4, 0x51afa0u);
    eax = 0x5c7800u;
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x20u, 4, 0x5c7804u);
    lift_store(&env, esp, 0x24u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, 0x5c7804u);
    eax = 0x5c7804u;
    edx = edx ^ edx;
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d92f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5c7810u, 4, 0x0u);
    lift_store(&env, 0u, 0x5c7814u, 4, 0x0u);
    lift_store(&env, 0u, 0x5c7804u, 4, 0x51b534u);
    lift_store(&env, 0u, 0x5c7898u, 4, 0xf022u);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    eax = 0x506730u;
    edx = 0x506a60u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec1f7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5c789cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x20u, 4, 0x5c78a0u);
    lift_store(&env, esp, 0x24u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, 0x5c78a0u);
    eax = 0x5c78a0u;
    edx = edx ^ edx;
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d92f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5c78acu, 4, 0x0u);
    lift_store(&env, 0u, 0x5c78b0u, 4, 0x0u);
    lift_store(&env, esp, 0xcu, 4, 0x5u);
    lift_store(&env, 0u, 0x5c78a0u, 4, 0x51b554u);
    lift_store(&env, 0u, 0x5c7934u, 4, 0xf024u);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    eax = 0x506740u;
    edx = 0x506a78u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec1f7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5c7938u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x506a90u;
    eax = 0x5c7939u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x506aa8u;
    eax = 0x5c793au;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x506ac0u;
    eax = 0x5c793bu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x506ad8u;
    eax = 0x5c793cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x506af0u;
    eax = 0x5c793du;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x506b08u;
    eax = 0x5c793eu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x506b20u;
    eax = 0x5c793fu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x506b38u;
    eax = 0x5c7940u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x506b50u;
    eax = 0x5c7941u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x506b68u;
    eax = 0x5c7942u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    {
        uint32_t r = lift_add(32, esp, 0x2cu, &fl);
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
}

uint32_t lifted_f4de5a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DE5A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DE5A0_STACK, 0, entry);
    eax = 0x5c7944u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4de630u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x506c30u;
    goto L_4ec1f7;
L_4df2e1:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = 0x50817eu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e14b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x50818eu, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = 0x50817eu;
    lift_store(&env, 0u, 0x50818eu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e14b7u, eax, edx, ebx, ecx, 0, esp);
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
L_4ec1f7:
    goto L_4df2e1;
}

uint32_t lifted_f4dea80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DEA80_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DEA80_STACK, 0, entry);
    eax = 0x507250u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec1f7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x507260u;
    goto L_4ec1f7;
L_4df2e1:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = 0x50817eu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e14b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x50818eu, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = 0x50817eu;
    lift_store(&env, 0u, 0x50818eu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e14b7u, eax, edx, ebx, ecx, 0, esp);
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
L_4ec1f7:
    goto L_4df2e1;
}

uint32_t lifted_f4deea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DEEA0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DEEA0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x507c08u;
    eax = 0x5c7b88u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4df307(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DF307_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DF307_STACK, 0, entry);
    eax = 0x24u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e62b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5c5c54u, 4, eax);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e04f4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E04F4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E04F4_STACK, 0, entry);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e08b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E08B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E08B0_STACK, 0, entry);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e1190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E1190_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E1190_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x508158u;
    eax = 0x5c81c0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4e3f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3F70_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3F70_STACK, 0, entry);
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
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, 0u, 0x505275u, 1)) & 0xffu) << 8);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) & 0xf8u) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | ((((eax >> 8) & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x505275u, 1, ((eax >> 8) & 0xffu));
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) | 0x4u) & 0xffu);
    lift_store(&env, 0u, 0x505275u, 1, (edx & 0xffu));
    edx = lift_load(&env, 0u, 0x505240u, 4);
    ebx = 0x505234u;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e4003;
L_4e3f9d:
    eax = 0x1du;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e3fcc;
    eax = 0x1du;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e3fce;
    edx = 0x1u;
    eax = 0x512904u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e628cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e3fce;
L_4e3fcc:
    ecx = eax;
L_4e3fce:
    eax = lift_load(&env, 0u, 0x5c7760u, 4);
    lift_store(&env, ecx, 0x4u, 4, ebx);
    lift_store(&env, ecx, 0x0u, 4, eax);
    lift_store(&env, ebx, 0x8u, 4, ecx);
    lift_store(&env, ecx, 0x8u, 4, 0x0u);
    eax = lift_load(&env, ebx, 0x8u, 4);
    lift_store(&env, eax, 0x14u, 1, 0x0u);
    eax = lift_load(&env, ebx, 0x8u, 4);
    lift_store(&env, eax, 0xcu, 4, 0x0u);
    lift_store(&env, 0u, 0x5c7760u, 4, ecx);
    ecx = lift_load(&env, ebx, 0x26u, 4);
    ebx = ebx + 0x1au;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4e3f9d;
L_4e4003:
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, 0u, 0x5c7764u, 4, esi);
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

uint32_t lifted_f4e5ef0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5EF0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5EF0_STACK, 0, entry);
    eax = eax ^ eax;
    goto L_4e6f60;
L_4e6f60:
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
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x14u;
    esi = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e6f7d;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b7cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    goto L_4e7015;
L_4e6f7d:
    {
        (void)lift_sub(32, eax, 0xfffffffeu, &fl);
    }
    if (!fl.zf)
        goto L_4e6f90;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1bd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    goto L_4e7015;
L_4e6f90:
    {
        (void)lift_sub(32, eax, 0xfffffffdu, &fl);
    }
    if (!fl.zf)
        goto L_4e6fbb;
    ebx = 0x101u;
    eax = 0x5c8960u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5c8950u, 4, edx);
    lift_store(&env, 0u, 0x50a820u, 4, edx);
    goto L_4e70ba;
L_4e6fbb:
    {
        (void)lift_sub(32, eax, 0xfffffffcu, &fl);
    }
    if (!fl.zf)
        goto L_4e7015;
    ebx = 0x101u;
    eax = 0x5c8960u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x81u;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
L_4e6fd8:
    eax = eax + 1u;
    lift_store(&env, eax, 0x5c8960u, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, eax, 0x9fu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e6fd8;
    eax = 0xe0u;
    edx = (edx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
L_4e6fed:
    eax = eax + 1u;
    lift_store(&env, eax, 0x5c8960u, 1, ((edx >> 8) & 0xffu));
    {
        (void)lift_sub(32, eax, 0xfcu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e6fed;
    ebp = 0x1u;
    eax = 0x3a4u;
    lift_store(&env, 0u, 0x5c8950u, 4, ebp);
    lift_store(&env, 0u, 0x50a820u, 4, eax);
    goto L_4e70b8;
L_4e7015:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e701e;
    esi = 0x1u;
L_4e701e:
    eax = esp;
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
    eax = lift_call(&env, 0x4f1b80u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e703b;
    eax = 0x1u;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4e703b:
    ebx = 0x101u;
    eax = 0x5c8960u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx ^ ecx;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esp, 0x6u, 1)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5c8950u, 4, ecx);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e7066;
    lift_store(&env, 0u, 0x5c8950u, 4, 0x1u);
L_4e7066:
    ebx = ebx ^ ebx;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
    goto L_4e7088;
L_4e706c:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, ebx + 0x6u, 1)) & 0xffu);
    goto L_4e707b;
L_4e7074:
    eax = eax + 1u;
    lift_store(&env, eax, 0x5c8960u, 1, (ecx & 0xffu));
L_4e707b:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esp, ebx + 0x7u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e7074;
    ebx = ebx + 0x2u;
L_4e7088:
    {
        (void)lift_sub(8, lift_load(&env, esp, ebx + 0x6u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e706c;
    {
        (void)lift_sub(8, lift_load(&env, esp, ebx + 0x7u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e706c;
    {
        (void)lift_sub(32, esi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4e70b2;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1bd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x50a820u, 4, eax);
    eax = eax ^ eax;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4e70b2:
    lift_store(&env, 0u, 0x50a820u, 4, esi);
L_4e70b8:
    eax = eax ^ eax;
L_4e70ba:
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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

uint32_t lifted_f4e7200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7200_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7200_STACK, 0, entry);
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
    esp = esp - 0x10u;
    lift_store(&env, esp, 0x8u, 4, 0xc0000000u);
    lift_store(&env, esp, 0xcu, 4, 0x4150017eu);
    lift_store(&env, esp, 0x0u, 4, 0x80000000u);
    lift_store(&env, esp, 0x4u, 4, 0x4147ffffu);
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5054a1u, 1), 0x3u, &fl);
    }
    if (fl.cf)
        goto L_4e7277;
    eax = lift_load(&env, esp, 0x8u, 4);
    edx = lift_load(&env, esp, 0xcu, 4);
    ebx = lift_load(&env, esp, 0x0u, 4);
    ecx = lift_load(&env, esp, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, esp, 0x0u, 4);
    ecx = lift_load(&env, esp, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    eax = lift_load(&env, esp, 0x8u, 4);
    edx = lift_load(&env, esp, 0xcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db34au, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xe2308c3au;
    ecx = 0x3e45798eu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb57cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.zf || fl.sf != fl.of)
        goto L_4e7277;
    lift_store(&env, 0u, 0x508798u, 1, lift_load(&env, 0u, 0x508798u, 1) | 0x1u);
L_4e7277:
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
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

uint32_t lifted_f4e7290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7290_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7290_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x50ab28u;
    eax = 0x5c8a80u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4e7520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7520_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7520_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x50ae38u;
    eax = 0x5c8a84u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4e8098(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8098_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8098_STACK, 0, entry);
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
    edi = lift_load(&env, 0u, 0x5c81d4u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4e816d;
    ebp = lift_load(&env, 0u, 0x509729u, 4);
    ecx = ecx ^ ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    eax = ebp;
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e80d3;
L_4e80bd:
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, eax, 0x0u, 1)) & 0xffu) << 8);
    ebx = (eax + 0x1u);
    {
        (void)lift_and(8, ((edx >> 8) & 0xffu), ((edx >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e80ca;
    eax = ebx;
    goto L_4e80bd;
L_4e80ca:
    ecx = ecx + 1u;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ebx, 0x0u, 1)) & 0xffu) << 8);
    eax = ebx;
    {
        (void)lift_and(8, ((edx >> 8) & 0xffu), ((edx >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4e80bd;
L_4e80d3:
    lift_store(&env, 0u, 0x5c81d4u, 4, edi);
    {
        uint32_t r = lift_sub(32, eax, ebp, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4e80e2;
    eax = 0x1u;
L_4e80e2:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e8168;
    lift_store(&env, 0u, 0x5c8a90u, 4, eax);
    eax = ((ecx * 4u));
    eax = eax + 0x4u;
    eax = eax + ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e8161;
    edi = eax;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    esi = esi ^ esi;
    ecx = ecx ^ ecx;
    eax = ebp;
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e8136;
L_4e811c:
    edx = edi;
    lift_store(&env, ecx, edx + 0x0u, 4, ebx);
L_4e8121:
    ebx = ebx + 1u;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = eax + 1u;
    lift_store(&env, ebx, 0xffffffffu, 1, (edx & 0xffu));
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4e8121;
    ecx = ecx + 0x4u;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    esi = esi + 1u;
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4e811c;
L_4e8136:
    eax = edi;
    lift_store(&env, ecx, eax + 0x0u, 4, 0x0u);
    ecx = ecx + 0x4u;
    ebx = esi;
    eax = (edi + ecx);
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5c81d0u, 4, eax);
    lift_store(&env, 0u, 0x5c81d4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = lift_load(&env, 0u, 0x5c81d4u, 4);
    goto L_4e8168;
L_4e8161:
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e8168:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9f10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e816d:
    edi = lift_load(&env, 0u, 0x5c81d4u, 4);
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

uint32_t lifted_f4e8db0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8DB0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8DB0_STACK, 0, entry);
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
    edx = 0x4e8d38u;
    ebx = 0x4e8d80u;
    lift_store(&env, 0u, 0x507cdcu, 4, edx);
    lift_store(&env, 0u, 0x507ce0u, 4, ebx);
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

uint32_t lifted_f4ec2b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC2B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC2B0_STACK, 0, entry);
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
    edx = 0x4ec970u;
    ebx = 0x4eca85u;
    lift_store(&env, 0u, 0x509794u, 4, edx);
    lift_store(&env, 0u, 0x509798u, 4, ebx);
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

uint32_t lifted_f4ec8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC8D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC8D0_STACK, 0, entry);
    goto L_4ec8d0;
L_4df2e1:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = 0x50817eu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e14b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x50818eu, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = 0x50817eu;
    lift_store(&env, 0u, 0x50818eu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e14b7u, eax, edx, ebx, ecx, 0, esp);
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
L_4ec1f7:
    goto L_4df2e1;
L_4ec8d0:
    eax = 0x5c8ae0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec940u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x50b3c0u;
    goto L_4ec1f7;
}

uint32_t lifted_f4ecb98(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECB98_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ECB98_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax + lift_load(&env, 0u, 0x5c5c54u, 4);
    {
        uint32_t r = lift_or(8, lift_load(&env, eax, 0x4u, 1), 0x2u, &fl);
        lift_store(&env, eax, 0x4u, 1, r);
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE420_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE420_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x48u, &fl);
        esp = r;
    }
    lift_store(&env, esp, 0x0u, 4, 0x4ee7f0u);
    lift_store(&env, esp, 0x4u, 4, 0x0u);
    edi = (esp + 0xcu);
    esi = esp;
    lift_store(&env, esp, 0x8u, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 4, 0x4ee800u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x1cu, 4, 0x0u);
    eax = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    lift_store(&env, 0u, 0x50c08cu, 4, eax);
    eax = lift_load(&env, esp, 0x10u, 4);
    edi = (esp + 0x24u);
    lift_store(&env, 0u, 0x50c090u, 4, eax);
    eax = lift_load(&env, esp, 0x14u, 4);
    esi = (esp + 0x18u);
    lift_store(&env, 0u, 0x50c094u, 4, eax);
    lift_store(&env, esp, 0x30u, 4, 0x4ee810u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x34u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x24u, 4);
    edi = (esp + 0x3cu);
    lift_store(&env, 0u, 0x50c0acu, 4, eax);
    eax = lift_load(&env, esp, 0x28u, 4);
    esi = (esp + 0x30u);
    lift_store(&env, 0u, 0x50c0b0u, 4, eax);
    eax = lift_load(&env, esp, 0x2cu, 4);
    lift_store(&env, esp, 0x38u, 4, 0x0u);
    lift_store(&env, 0u, 0x50c0b4u, 4, eax);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, esp, 0x3cu, 4);
    edx = 0x50c0f8u;
    lift_store(&env, 0u, 0x50c0ccu, 4, eax);
    eax = lift_load(&env, esp, 0x40u, 4);
    lift_store(&env, 0u, 0x50c0ecu, 4, 0x0u);
    lift_store(&env, 0u, 0x50c0d0u, 4, eax);
    eax = lift_load(&env, esp, 0x44u, 4);
    lift_store(&env, 0u, 0x50c0f0u, 4, 0x0u);
    lift_store(&env, 0u, 0x50c0d4u, 4, eax);
    eax = 0x5c8b00u;
    lift_store(&env, 0u, 0x50c0f4u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0x48u, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE820_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE820_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x50c428u;
    eax = 0x5c8b04u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d30f0u, eax, edx, ebx, ecx, 0, esp);
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
