/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_38.h"

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
