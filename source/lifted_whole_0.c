/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_0.h"

uint32_t lifted_f406170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F406170_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F406170_STACK, 0, entry);
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
    esp = esp - 0xecu;
    lift_store(&env, esp, 0x0u, 4, eax);
    esi = 0xfffffc00u;
    edi = 0xffffffd2u;
    ebp = 0x40000000u;
L_40618e:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0xbfd00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    eax = eax ^ eax;
    edx = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9921u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x523698u, 4, eax);
    esi = esi + 0x4u;
    edi = edi + 1u;
    {
        (void)lift_sub(32, esi, 0x1e8u, &fl);
    }
    if (!fl.zf)
        goto L_40618e;
    esi = esi ^ esi;
    edi = edi ^ edi;
    ebp = 0x55555554u;
L_4061ce:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebp;
    ecx = 0x3ff55555u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9921u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x524288u, 4, eax);
    edi = edi + 0x4u;
    esi = esi + 1u;
    {
        (void)lift_sub(32, esi, 0x200fu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4061ce;
    edx = edx ^ edx;
    lift_store(&env, esp, 0x20u, 4, edx);
    esi = esi ^ esi;
L_406200:
    eax = lift_load(&env, esi, 0x4f5e28u, 4);
    edx = lift_load(&env, esi, 0x4f5e2cu, 4);
    ebx = eax;
    ecx = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x3ff00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9b10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    edi = edx;
    eax = eax ^ eax;
    edx = 0x3ff00000u;
    ebx = ebp;
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x20u, 4);
    lift_store(&env, edx, 0x5238a0u, 4, eax);
    eax = lift_load(&env, esi, 0x4f5e28u, 4);
    edx = lift_load(&env, esi, 0x4f5e2cu, 4);
    ebx = ebp;
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x20u, 4);
    lift_store(&env, edx, 0x523880u, 4, eax);
    ecx = (edx + 0x4u);
    lift_store(&env, esp, 0x20u, 4, ecx);
    esi = esi + 0x8u;
    {
        (void)lift_sub(32, ecx, 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_406200;
    lift_store(&env, esp, 0x24u, 4, 0x37u);
    ebp = 0x25u;
    esi = esi ^ esi;
    lift_store(&env, esp, 0x28u, 4, 0x13u);
    edi = 0x1u;
L_406298:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x4ae74487u;
    ecx = 0x3fa65718u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dafu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0xe8u, 4, eax);
    lift_store(&env, esp, 0x4u, 4, edx);
    eax = lift_load(&env, esp, 0x28u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x54442d18u;
    ecx = 0x400921fbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x40520000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    eax = lift_load(&env, esp, 0xe8u, 4);
    edx = lift_load(&env, esp, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x523b90u, 4, eax);
    lift_store(&env, esi, 0x523b00u, 4, eax);
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x4ae74487u;
    ecx = 0x3fa65718u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dafu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0xe8u, 4, eax);
    lift_store(&env, esp, 0x4u, 4, edx);
    eax = lift_load(&env, esp, 0x24u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x54442d18u;
    ecx = 0x400921fbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x40520000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    eax = lift_load(&env, esp, 0xe8u, 4);
    edx = lift_load(&env, esp, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x523cf8u, 4, eax);
    lift_store(&env, esi, 0x523b48u, 4, eax);
    lift_store(&env, esp, 0x24u, 4, lift_load(&env, esp, 0x24u, 4) + 0x2u);
    ebp = ebp + 0x2u;
    esi = esi + 0x4u;
    lift_store(&env, esp, 0x28u, 4, lift_load(&env, esp, 0x28u, 4) + 0x2u);
    edi = edi + 0x2u;
    {
        (void)lift_sub(32, edi, 0x25u, &fl);
    }
    if (!fl.zf)
        goto L_406298;
    edi = 0x1u;
    lift_store(&env, esp, 0x2cu, 4, 0x1fu);
    lift_store(&env, esp, 0x30u, 4, 0xdu);
    ebp = 0x43u;
    lift_store(&env, esp, 0x34u, 4, 0x2bu);
    esi = esi ^ esi;
    lift_store(&env, esp, 0x38u, 4, 0x37u);
L_4063e0:
    eax = lift_load(&env, esp, 0x38u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x54442d18u;
    ecx = 0x400921fbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x40520000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    eax = eax ^ eax;
    edx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x523bd8u, 4, eax);
    eax = lift_load(&env, esp, 0x34u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x54442d18u;
    ecx = 0x400921fbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x40520000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    eax = eax ^ eax;
    edx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x523ce0u, 4, eax);
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x54442d18u;
    ecx = 0x400921fbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x40520000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0xe8u, 4, eax);
    lift_store(&env, esp, 0x4u, 4, edx);
    eax = lift_load(&env, esp, 0x30u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x382d7365u;
    ecx = 0x3fc0c152u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dafu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, esp, 0xe8u, 4);
    ecx = lift_load(&env, esp, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x523bf0u, 4, eax);
    edx = edx ^ edx;
    lift_store(&env, esi, 0x523cb0u, 4, edx);
    lift_store(&env, esi, 0x523c08u, 4, edx);
    eax = lift_load(&env, esp, 0x2cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x54442d18u;
    ecx = 0x400921fbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x40520000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x4u, 4, eax);
    lift_store(&env, esp, 0xe8u, 4, edx);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x382d7365u;
    ecx = 0x3fc0c152u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dafu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, esp, 0x4u, 4);
    ecx = lift_load(&env, esp, 0xe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x523cc8u, 4, eax);
    edi = edi + 0x2u;
    lift_store(&env, esp, 0x2cu, 4, lift_load(&env, esp, 0x2cu, 4) + 0x2u);
    lift_store(&env, esp, 0x30u, 4, lift_load(&env, esp, 0x30u, 4) + 0x2u);
    ebp = ebp + 0x2u;
    lift_store(&env, esp, 0x34u, 4, lift_load(&env, esp, 0x34u, 4) + 0x2u);
    esi = esi + 0x4u;
    lift_store(&env, esp, 0x38u, 4, lift_load(&env, esp, 0x38u, 4) + 0x2u);
    {
        (void)lift_sub(32, edi, 0xdu, &fl);
    }
    if (!fl.zf)
        goto L_4063e0;
    esi = esi ^ esi;
    edi = edi ^ edi;
L_40658c:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x4ae74489u;
    ecx = 0x3fc65718u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x52c2c4u, 4, eax);
    edi = edi + 0x4u;
    esi = esi + 1u;
    {
        (void)lift_sub(32, esi, 0x9u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40658c;
    edi = edi ^ edi;
    esi = 0x1u;
    ebp = 0x3fe00000u;
L_4065c7:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x54442d18u;
    ecx = 0x400921fbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x40420000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    eax = eax ^ eax;
    edx = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x52c2e8u, 4, eax);
    edi = edi + 0x4u;
    esi = esi + 0x2u;
    {
        (void)lift_sub(32, esi, 0x13u, &fl);
    }
    if (!fl.zf)
        goto L_4065c7;
    edi = edi ^ edi;
    esi = 0x1u;
    ebp = 0x3fe00000u;
L_40661d:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x54442d18u;
    ecx = 0x400921fbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x40280000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    eax = eax ^ eax;
    edx = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x524274u, 4, eax);
    edi = edi + 0x4u;
    esi = esi + 0x2u;
    {
        (void)lift_sub(32, esi, 0x7u, &fl);
    }
    if (!fl.zf)
        goto L_40661d;
    eax = 0x382d7366u;
    edx = 0x3fe0c152u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x524284u, 4, eax);
    eax = 0x382d7367u;
    edx = 0x3ff0c152u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x524280u, 4, eax);
    ecx = ecx ^ ecx;
    lift_store(&env, esp, 0xd8u, 4, ecx);
    lift_store(&env, esp, 0x40u, 4, 0x18u);
    lift_store(&env, esp, 0x44u, 4, 0xeu);
    lift_store(&env, esp, 0x48u, 4, ecx);
    lift_store(&env, esp, 0x4cu, 4, 0x1u);
L_4066be:
    esi = lift_load(&env, esp, 0xd8u, 4);
    esi = esi + esi;
    eax = lift_load(&env, esp, 0x4cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x382d7365u;
    ecx = 0x3fc0c152u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dafu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    edi = edx;
    esi = esi + 0x7u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x54442d18u;
    ecx = 0x400921fbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x40380000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    eax = ebp;
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x48u, 4);
    lift_store(&env, edx, 0x523c20u, 4, eax);
    edi = lift_load(&env, esp, 0xd8u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edi = r;
    }
    edi = edi - lift_load(&env, esp, 0xd8u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edi = r;
    }
    ebp = lift_load(&env, esp, 0x44u, 4);
    {
        uint32_t r = lift_imul(32, esi, 0x0u, &fl);
        eax = r;
    }
    esi = esi + eax;
    eax = lift_load(&env, esp, 0x40u, 4);
    lift_store(&env, esp, 0x3cu, 4, eax);
L_40675f:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x382d7365u;
    ecx = 0x3fc0c152u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x523d40u, 4, eax);
    edi = edi + 0x4u;
    esi = esi + ebp;
    {
        (void)lift_sub(32, edi, lift_load(&env, esp, 0x3cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_40675f;
    lift_store(&env, esp, 0x40u, 4, lift_load(&env, esp, 0x40u, 4) + 0x18u);
    lift_store(&env, esp, 0x44u, 4, lift_load(&env, esp, 0x44u, 4) + 0x4u);
    lift_store(&env, esp, 0x48u, 4, lift_load(&env, esp, 0x48u, 4) + 0x4u);
    lift_store(&env, esp, 0x4cu, 4, lift_load(&env, esp, 0x4cu, 4) + 0x2u);
    ebp = lift_load(&env, esp, 0xd8u, 4);
    ebp = ebp + 1u;
    lift_store(&env, esp, 0xd8u, 4, ebp);
    {
        (void)lift_sub(32, ebp, 0xcu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4066be;
    esi = esi ^ esi;
    edi = edi ^ edi;
    ebp = 0x1u;
L_4067c5:
    edx = edx ^ edx;
    ebx = esi;
    eax = edi;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x4f5e68u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4067ee;
L_4067d4:
    ecx = lift_load(&env, eax, 0x523b00u, 4);
    lift_store(&env, eax, 0x5238c0u, 4, ecx);
    eax = eax + 0x8u;
    edx = edx + 0x2u;
    {
        (void)lift_sub(32, edx, lift_load(&env, ebx, 0x4f5e68u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4067d4;
L_4067ee:
    ecx = ebp;
    ebx = esi;
    edx = (edi + 0x4u);
    {
        (void)lift_sub(32, ebp, lift_load(&env, esi, 0x4f5e68u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_40681c;
L_4067fd:
    eax = lift_load(&env, edx, 0x523b00u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edx, 0x5238c0u, 4, eax);
    edx = edx + 0x8u;
    ecx = ecx + 0x2u;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebx, 0x4f5e68u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4067fd;
L_40681c:
    esi = esi + 0x4u;
    edi = edi + 0x90u;
    {
        (void)lift_sub(32, esi, 0x10u, &fl);
    }
    if (!fl.zf)
        goto L_4067c5;
    edx = edx ^ edx;
    lift_store(&env, esp, 0xd4u, 4, edx);
    lift_store(&env, esp, 0x54u, 4, edx);
L_406837:
    eax = lift_load(&env, esp, 0xd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x54442d18u;
    ecx = 0x400921fbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x40280000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9e00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    lift_store(&env, esp, 0x8u, 4, edx);
    ebx = ebx ^ ebx;
    ecx = 0x3ff00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edi = edx;
    eax = ebp;
    edx = lift_load(&env, esp, 0x8u, 4);
    ebx = esi;
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x54u, 4);
    lift_store(&env, edx, 0x523218u, 4, eax);
    eax = eax ^ eax;
    edx = 0x3ff00000u;
    ebx = esi;
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x54u, 4);
    lift_store(&env, edx, 0x523198u, 4, eax);
    eax = ebp;
    edx = lift_load(&env, esp, 0x8u, 4);
    ebx = 0x667f3bccu;
    ecx = 0x3ff6a09eu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = esi;
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x54u, 4);
    lift_store(&env, edx, 0x523258u, 4, eax);
    eax = 0x667f3bccu;
    edx = 0x3ff6a09eu;
    ebx = esi;
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x54u, 4);
    lift_store(&env, edx, 0x5231d8u, 4, eax);
    ebx = ebx ^ ebx;
    lift_store(&env, esp, 0xdcu, 4, ebx);
    lift_store(&env, esp, 0x50u, 4, edx);
L_406912:
    eax = lift_load(&env, esp, 0xdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x3ff00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0xbfd00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    eax = eax ^ eax;
    edx = 0x40000000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9921u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0xcu, 4, eax);
    lift_store(&env, esp, 0x10u, 4, edx);
    ebp = ebp ^ ebp;
    esi = 0x3ff00000u;
    lift_store(&env, esp, 0x14u, 4, ebp);
    edi = esi;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0xd4u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4069a9;
    {
        (void)lift_and(8, lift_load(&env, esp, 0xd4u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_406fdd;
    eax = lift_load(&env, esp, 0xd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    eax = lift_load(&env, esp, 0xcu, 4);
    edx = lift_load(&env, esp, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9921u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    esi = edx;
L_4069a9:
    eax = ebp;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x50u, 4);
    lift_store(&env, edx, 0x523118u, 4, eax);
    eax = lift_load(&env, esp, 0x14u, 4);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x50u, 4);
    lift_store(&env, edx, 0x523018u, 4, eax);
    eax = ebp;
    edx = esi;
    ebx = 0x667f3bccu;
    ecx = 0x3ff6a09eu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x50u, 4);
    lift_store(&env, edx, 0x523098u, 4, eax);
    eax = lift_load(&env, esp, 0x14u, 4);
    edx = edi;
    ebx = 0x667f3bccu;
    ecx = 0x3ff6a09eu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x50u, 4);
    lift_store(&env, edx, 0x522f98u, 4, eax);
    edx = edx + 0x40u;
    lift_store(&env, esp, 0x50u, 4, edx);
    ecx = lift_load(&env, esp, 0xdcu, 4);
    ecx = ecx + 1u;
    lift_store(&env, esp, 0xdcu, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0x2u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406912;
    lift_store(&env, esp, 0x54u, 4, lift_load(&env, esp, 0x54u, 4) + 0x4u);
    edi = lift_load(&env, esp, 0xd4u, 4);
    edi = edi + 1u;
    lift_store(&env, esp, 0xd4u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x10u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406837;
    ebp = 0x521210u;
    lift_store(&env, esp, 0x58u, 4, 0x4f5918u);
    lift_store(&env, esp, 0x5cu, 4, 0x51fc20u);
    lift_store(&env, esp, 0x60u, 4, 0x522770u);
    ebx = ebx ^ ebx;
    lift_store(&env, esp, 0x64u, 4, ebx);
L_406a76:
    eax = lift_load(&env, esp, 0x58u, 4);
    lift_store(&env, esp, 0x18u, 4, eax);
    eax = lift_load(&env, esp, 0x64u, 4);
    lift_store(&env, eax, 0x524208u, 4, ebp);
    eax = ebp;
    ecx = lift_load(&env, esp, 0x58u, 4);
    ecx = ecx + 0x2eu;
    edi = edi ^ edi;
    edx = edx ^ edx;
L_406a95:
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, ecx, 0x0u, 2);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        ebx = r;
    }
    lift_store(&env, eax, 0x0u, 4, ebx);
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x0u, 4, edi);
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x0u, 4, 0x3u);
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x0u, 4, edx);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, ecx, 0x0u, 2);
    eax = eax + 0x4u;
    edx = edx + 1u;
    ecx = ecx + 0x2u;
    edi = edi + ebx;
    {
        (void)lift_sub(32, edx, 0x8u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406a95;
    edx = lift_load(&env, esp, 0x18u, 4);
    edx = edx + 0x7cu;
    lift_store(&env, esp, 0xe4u, 4, edx);
    ebx = 0x3u;
L_406ad3:
    esi = lift_load(&env, esp, 0xe4u, 4);
    esi = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, esi, 0x0u, 2);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        esi = r;
    }
    edx = edx ^ edx;
    lift_store(&env, esp, 0xe4u, 4, lift_load(&env, esp, 0xe4u, 4) + 0x2u);
    ecx = edi;
L_406aeb:
    lift_store(&env, eax, 0x0u, 4, esi);
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x0u, 4, ecx);
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x0u, 4, edx);
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x0u, 4, ebx);
    eax = eax + 0x4u;
    ecx = ecx + 1u;
    edx = edx + 1u;
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406aeb;
    {
        uint32_t r = lift_imul(32, esi, 0x6u, &fl);
        esi = r;
    }
    edi = edi + esi;
    ebx = ebx + 1u;
    {
        (void)lift_sub(32, ebx, 0xdu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406ad3;
    edx = lift_load(&env, esp, 0x64u, 4);
    lift_store(&env, edx, 0x523e60u, 4, eax);
    eax = lift_load(&env, esp, 0x5cu, 4);
    lift_store(&env, edx, 0x52420cu, 4, eax);
    edx = lift_load(&env, esp, 0x18u, 4);
    edx = edx + 0x76u;
    lift_store(&env, esp, 0xe0u, 4, edx);
    edi = edi ^ edi;
    ebx = ebx ^ ebx;
L_406b37:
    esi = lift_load(&env, esp, 0xe0u, 4);
    esi = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, esi, 0x0u, 2);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        esi = r;
    }
    edx = edx ^ edx;
    lift_store(&env, esp, 0xe0u, 4, lift_load(&env, esp, 0xe0u, 4) + 0x2u);
    ecx = edi;
L_406b4f:
    lift_store(&env, eax, 0x0u, 4, esi);
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x0u, 4, ecx);
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x0u, 4, edx);
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x0u, 4, ebx);
    eax = eax + 0x4u;
    ecx = ecx + 1u;
    edx = edx + 1u;
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406b4f;
    {
        uint32_t r = lift_imul(32, esi, 0x6u, &fl);
        esi = r;
    }
    edi = edi + esi;
    ebx = ebx + 1u;
    {
        (void)lift_sub(32, ebx, 0xdu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406b37;
    edx = lift_load(&env, esp, 0x64u, 4);
    lift_store(&env, edx, 0x523e64u, 4, eax);
    eax = lift_load(&env, esp, 0x60u, 4);
    lift_store(&env, edx, 0x524210u, 4, eax);
    ecx = lift_load(&env, esp, 0x18u, 4);
    ecx = ecx + 0x2eu;
    edx = edx ^ edx;
L_406b92:
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, ecx, 0x0u, 2);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        ebx = r;
    }
    lift_store(&env, eax, 0x0u, 4, ebx);
    ecx = ecx + 0x2u;
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x0u, 4, edx);
    eax = eax + 0x4u;
    edx = edx + 1u;
    {
        (void)lift_sub(32, edx, 0x16u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406b92;
    edx = lift_load(&env, esp, 0x64u, 4);
    lift_store(&env, edx, 0x523e68u, 4, eax);
    ebp = ebp + 0x260u;
    lift_store(&env, esp, 0x58u, 4, lift_load(&env, esp, 0x58u, 4) + 0x90u);
    lift_store(&env, esp, 0x5cu, 4, lift_load(&env, esp, 0x5cu, 4) + 0x270u);
    lift_store(&env, esp, 0x60u, 4, lift_load(&env, esp, 0x60u, 4) + 0xb0u);
    eax = (edx + 0xcu);
    lift_store(&env, esp, 0x64u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x6cu, &fl);
    }
    if (!fl.zf)
        goto L_406a76;
    edi = edi ^ edi;
    lift_store(&env, esp, 0x68u, 4, 0x2eu);
    lift_store(&env, esp, 0x6cu, 4, edi);
    ebp = 0x1cu;
    lift_store(&env, esp, 0x70u, 4, edi);
L_406bf9:
    {
        uint32_t r = lift_imul(32, edi, 0x90u, &fl);
        ebx = r;
    }
    ecx = lift_load(&env, esp, 0x6cu, 4);
    esi = lift_load(&env, esp, 0x68u, 4);
L_406c07:
    edx = lift_load(&env, ebx, 0x4f5916u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx + 0x7u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0xe8u, 4, 0x12u);
    lift_idiv1(32, lift_load(&env, esp, 0xe8u, 4), &eax, &edx, &fl);
    eax = eax + 1u;
    lift_store(&env, ecx, 0x523eccu, 4, eax);
    edx = lift_load(&env, esp, 0x0u, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_406c3e;
    lift_store(&env, ecx, 0x523eccu, 4, edx);
L_406c3e:
    ecx = ecx + 0x4u;
    ebx = ebx + 0x2u;
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (!fl.zf)
        goto L_406c07;
    {
        uint32_t r = lift_imul(32, edi, 0x90u, &fl);
        ebx = r;
    }
    ecx = lift_load(&env, esp, 0x70u, 4);
    esi = ebp;
L_406c54:
    edx = lift_load(&env, ebx, 0x4f5970u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx - 1u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0xe8u, 4, 0x12u);
    lift_idiv1(32, lift_load(&env, esp, 0xe8u, 4), &eax, &edx, &fl);
    eax = eax + 1u;
    lift_store(&env, ecx, 0x522da0u, 4, eax);
    edx = lift_load(&env, esp, 0x0u, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_406c89;
    lift_store(&env, ecx, 0x522da0u, 4, edx);
L_406c89:
    ecx = ecx + 0x4u;
    ebx = ebx + 0x2u;
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (!fl.zf)
        goto L_406c54;
    lift_store(&env, esp, 0x68u, 4, lift_load(&env, esp, 0x68u, 4) + 0x90u);
    lift_store(&env, esp, 0x6cu, 4, lift_load(&env, esp, 0x6cu, 4) + 0x5cu);
    ebp = ebp + 0x90u;
    lift_store(&env, esp, 0x70u, 4, lift_load(&env, esp, 0x70u, 4) + 0x38u);
    edi = edi + 1u;
    {
        (void)lift_sub(32, edi, 0x9u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406bf9;
    edi = edi ^ edi;
    lift_store(&env, esp, 0xd0u, 4, edi);
    ebp = ebp ^ ebp;
    lift_store(&env, esp, 0x80u, 4, edi);
L_406cc7:
    lift_store(&env, esp, 0x7cu, 4, ebp);
    edi = ebp;
    eax = lift_load(&env, esp, 0x80u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x74u, 4, eax);
    eax = eax + 0x18u;
    lift_store(&env, esp, 0x78u, 4, eax);
L_406ce2:
    ebx = lift_load(&env, esp, 0xd0u, 4);
    ebx = ebx | edi;
    eax = lift_load(&env, esp, 0x74u, 4);
    eax = eax + lift_load(&env, esp, 0x7cu, 4);
    edx = edx ^ edx;
    esi = lift_load(&env, esp, 0x7cu, 4);
    esi = esi + lift_load(&env, esp, 0x78u, 4);
L_406cfd:
    ecx = ebx;
    ecx = ecx | edx;
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) | 0x30u) & 0xffu) << 8);
    lift_store(&env, eax, 0x51f820u, 4, ecx);
    eax = eax + 0x4u;
    edx = edx + 0x40u;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.zf)
        goto L_406cfd;
    lift_store(&env, esp, 0x7cu, 4, lift_load(&env, esp, 0x7cu, 4) + 0x18u);
    edi = edi + 0x8u;
    {
        (void)lift_sub(32, edi, 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_406ce2;
    lift_store(&env, esp, 0x80u, 4, lift_load(&env, esp, 0x80u, 4) + 0x24u);
    edi = lift_load(&env, esp, 0xd0u, 4);
    edi = edi + 1u;
    lift_store(&env, esp, 0xd0u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406cc7;
    edx = edx ^ edx;
    lift_store(&env, esp, 0xccu, 4, edx);
    lift_store(&env, esp, 0x90u, 4, edx);
    ebp = ebp ^ ebp;
L_406d4f:
    edi = ebp;
    lift_store(&env, esp, 0x8cu, 4, ebp);
    eax = lift_load(&env, esp, 0x90u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x84u, 4, eax);
    eax = eax + 0x10u;
    lift_store(&env, esp, 0x88u, 4, eax);
L_406d73:
    esi = lift_load(&env, esp, 0xccu, 4);
    esi = esi | lift_load(&env, esp, 0x8cu, 4);
    eax = lift_load(&env, esp, 0x84u, 4);
    eax = eax + edi;
    edx = edx ^ edx;
    ebx = lift_load(&env, esp, 0x88u, 4);
    ebx = ebx + edi;
L_406d95:
    ecx = esi;
    ecx = ecx | edx;
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) | 0x40u) & 0xffu) << 8);
    lift_store(&env, eax, 0x51faf0u, 4, ecx);
    eax = eax + 0x4u;
    edx = edx + 0x40u;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_406d95;
    edi = edi + 0x10u;
    esi = lift_load(&env, esp, 0x8cu, 4);
    esi = esi + 0x8u;
    lift_store(&env, esp, 0x8cu, 4, esi);
    {
        (void)lift_sub(32, esi, 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_406d73;
    lift_store(&env, esp, 0x90u, 4, lift_load(&env, esp, 0x90u, 4) + 0x10u);
    ecx = lift_load(&env, esp, 0xccu, 4);
    ecx = ecx + 1u;
    lift_store(&env, esp, 0xccu, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406d4f;
    esi = esi ^ esi;
    ebp = 0xcu;
    lift_store(&env, esp, 0x94u, 4, esi);
L_406df3:
    eax = lift_load(&env, esp, 0x94u, 4);
    edx = edx ^ edx;
    edi = ebp;
L_406dfe:
    ecx = esi;
    ecx = ecx | edx;
    ebx = ecx;
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) | 0x50u) & 0xffu) << 8);
    lift_store(&env, eax, 0x51fbf0u, 4, ebx);
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) | 0xa0u) & 0xffu) << 8);
    lift_store(&env, eax, 0x51f7f0u, 4, ecx);
    eax = eax + 0x4u;
    edx = edx + 0x8u;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (!fl.zf)
        goto L_406dfe;
    ebp = ebp + 0xcu;
    lift_store(&env, esp, 0x94u, 4, lift_load(&env, esp, 0x94u, 4) + 0xcu);
    esi = esi + 1u;
    {
        (void)lift_sub(32, esi, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406df3;
    edx = edx ^ edx;
    lift_store(&env, esp, 0xc8u, 4, edx);
    lift_store(&env, esp, 0xacu, 4, edx);
L_406e41:
    ebx = ebx ^ ebx;
    lift_store(&env, esp, 0xa4u, 4, ebx);
    lift_store(&env, esp, 0xa8u, 4, ebx);
    eax = lift_load(&env, esp, 0xacu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x98u, 4, eax);
    eax = eax + 0x10u;
    lift_store(&env, esp, 0x9cu, 4, eax);
L_406e6c:
    eax = lift_load(&env, esp, 0xc8u, 4);
    edi = lift_load(&env, esp, 0xa4u, 4);
    eax = eax | edi;
    lift_store(&env, esp, 0x1cu, 4, eax);
    edi = edi ^ edi;
    ebp = ebp ^ ebp;
    eax = lift_load(&env, esp, 0xa8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = lift_load(&env, esp, 0x98u, 4);
    edx = edx + eax;
    lift_store(&env, esp, 0xc0u, 4, edx);
    edx = lift_load(&env, esp, 0x9cu, 4);
    edx = edx + eax;
    lift_store(&env, esp, 0xa0u, 4, edx);
L_406eae:
    ebx = lift_load(&env, esp, 0x1cu, 4);
    ebx = ebx | ebp;
    eax = lift_load(&env, esp, 0xc0u, 4);
    eax = eax + edi;
    edx = edx ^ edx;
    esi = lift_load(&env, esp, 0xa0u, 4);
    esi = esi + edi;
L_406ec8:
    ecx = ebx;
    ecx = ecx | edx;
    lift_store(&env, eax, 0x51f020u, 4, ecx);
    eax = eax + 0x4u;
    edx = edx + 0x200u;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.zf)
        goto L_406ec8;
    edi = edi + 0x10u;
    ebp = ebp + 0x40u;
    {
        (void)lift_sub(32, edi, 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_406eae;
    ebp = lift_load(&env, esp, 0xa4u, 4);
    ebp = ebp + 0x8u;
    lift_store(&env, esp, 0xa4u, 4, ebp);
    lift_store(&env, esp, 0xa8u, 4, lift_load(&env, esp, 0xa8u, 4) + 0x10u);
    {
        (void)lift_sub(32, ebp, 0x28u, &fl);
    }
    if (!fl.zf)
        goto L_406e6c;
    lift_store(&env, esp, 0xacu, 4, lift_load(&env, esp, 0xacu, 4) + 0x50u);
    ebx = lift_load(&env, esp, 0xc8u, 4);
    ebx = ebx + 1u;
    lift_store(&env, esp, 0xc8u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406e41;
    edi = edi ^ edi;
    lift_store(&env, esp, 0xc4u, 4, edi);
    ebp = ebp ^ ebp;
    lift_store(&env, esp, 0xbcu, 4, edi);
L_406f3e:
    lift_store(&env, esp, 0xb8u, 4, ebp);
    edi = ebp;
    eax = lift_load(&env, esp, 0xbcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0xb0u, 4, eax);
    eax = eax + 0x10u;
    lift_store(&env, esp, 0xb4u, 4, eax);
L_406f62:
    ebx = lift_load(&env, esp, 0xc4u, 4);
    ebx = ebx | edi;
    eax = lift_load(&env, esp, 0xb0u, 4);
    eax = eax + lift_load(&env, esp, 0xb8u, 4);
    edx = edx ^ edx;
    esi = lift_load(&env, esp, 0xb8u, 4);
    esi = esi + lift_load(&env, esp, 0xb4u, 4);
L_406f89:
    ecx = ebx;
    ecx = ecx | edx;
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) | 0x10u) & 0xffu) << 8);
    lift_store(&env, eax, 0x51f660u, 4, ecx);
    eax = eax + 0x4u;
    edx = edx + 0x40u;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.zf)
        goto L_406f89;
    lift_store(&env, esp, 0xb8u, 4, lift_load(&env, esp, 0xb8u, 4) + 0x10u);
    edi = edi + 0x8u;
    {
        (void)lift_sub(32, edi, 0x28u, &fl);
    }
    if (!fl.zf)
        goto L_406f62;
    lift_store(&env, esp, 0xbcu, 4, lift_load(&env, esp, 0xbcu, 4) + 0x14u);
    edi = lift_load(&env, esp, 0xc4u, 4);
    edi = edi + 1u;
    lift_store(&env, esp, 0xc4u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_406f3e;
    {
        uint32_t r = lift_add(32, esp, 0xecu, &fl);
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
L_406fdd:
    eax = lift_load(&env, esp, 0xd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    eax = lift_load(&env, esp, 0xcu, 4);
    edx = lift_load(&env, esp, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9921u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x14u, 4, eax);
    edi = edx;
    goto L_4069a9;
}

uint32_t lifted_f407020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F407020_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F407020_STACK, 1, entry);
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
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    ebx = ecx;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x8u, 4), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4071f8;
    eax = 0x4u;
L_407041:
    edi = eax;
    eax = 0x9u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x0u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4071ff;
    eax = 0x5u;
L_40705e:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x4u, 4, eax);
    ecx = ecx ^ ecx;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_407090;
    edx = esi;
L_407070:
    lift_store(&env, edx, 0x8u, 4, 0xffffffffu);
    eax = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edx, 0x70u, 4, eax);
    edx = edx + 0xd0u;
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffecu, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_407070;
L_407090:
    edx = ebx;
    eax = ((ebx * 8u));
    eax = eax + ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    esi = esi + 0x8u;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    edx = edx ^ ebx;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
L_4070b2:
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4071da;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    edi = edi + lift_load(&env, ebp, 0xffffffdcu, 4);
L_4070c7:
    ecx = edi;
    eax = 0xcu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x4u, 4, eax);
    eax = 0x9u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x8u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x120u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4070f1;
    lift_store(&env, edi, 0x8u, 4, 0x120u);
L_4070f1:
    eax = 0x8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = 0x523698u;
    edx = edx - eax;
    eax = edx;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = edx + eax;
    lift_store(&env, ecx, 0x64u, 4, edx);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40711b;
    esi = (edx + 0x8u);
    lift_store(&env, ecx, 0x64u, 4, esi);
L_40711b:
    eax = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0xcu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ecx + 0xcu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_407209;
    eax = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x10u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x14u, 4, eax);
    eax = 0x5u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x18u, 4, eax);
    eax = 0x5u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x1cu, 4, eax);
    lift_store(&env, ecx, 0x20u, 4, 0x0u);
    edx = ecx;
    esi = ebx;
L_407172:
    eax = 0x3u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ecx, 0x64u, 4);
    eax = eax + ebx;
    lift_store(&env, edx, 0x58u, 4, eax);
    edx = edx + 0x4u;
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (!fl.zf)
        goto L_407172;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40719e;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb4d4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_40719e:
    lift_store(&env, ecx, 0x44u, 4, 0x12u);
    lift_store(&env, ecx, 0x48u, 4, 0x120u);
L_4071ac:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x4cu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x50u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x54u, 4, eax);
    edi = edi + 0xd0u;
    esi = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = esi + 1u;
    lift_store(&env, ebp, 0xfffffff4u, 4, esi);
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffecu, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4070c7;
L_4071da:
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = ecx + 0x68u;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0xd0u, &fl);
    }
    if (!fl.zf)
        goto L_4070b2;
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
L_4071f8:
    eax = eax ^ eax;
    goto L_407041;
L_4071ff:
    eax = 0x3u;
    goto L_40705e;
L_407209:
    edx = ecx;
    esi = 0x5u;
L_407210:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edx, 0x18u, 4, eax);
    edx = edx + 0x4u;
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_407210;
    eax = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x3u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (edx + edx);
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    ebx = ebx + esi;
    ebx = lift_load(&env, ebx, 0x4f5918u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        ebx = r;
    }
    lift_store(&env, ecx, 0x44u, 4, ebx);
    eax = eax + edx;
    eax = eax + eax;
    eax = eax + esi;
    eax = lift_load(&env, eax, 0x4f591au, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x48u, 4, eax);
    lift_store(&env, ecx, 0x10u, 4, 0x0u);
    lift_store(&env, ecx, 0x14u, 4, 0x0u);
    goto L_4071ac;
}

uint32_t lifted_f407830(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F407830_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F407830_STACK, 1, entry);
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
    esp = esp - 0xa4u;
    lift_store(&env, ebp, 0xffffff70u, 4, eax);
    lift_store(&env, ebp, 0xffffff74u, 4, edx);
    lift_store(&env, ebp, 0xffffff78u, 4, ebx);
    lift_store(&env, ebp, 0xffffff7cu, 4, ecx);
    eax = lift_load(&env, ebx, 0x50u, 4);
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffff80u, 4, eax);
    ebx = lift_load(&env, ebp, 0xffffff70u, 4);
    esi = lift_load(&env, ebp, 0xffffff78u, 4);
    esi = lift_load(&env, esi, 0x4u, 4);
    esi = esi - lift_load(&env, ebp, 0x8u, 4);
    eax = lift_load(&env, ebp, 0xffffff78u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    edx = lift_load(&env, ebp, 0xffffff78u, 4);
    edx = lift_load(&env, edx, 0x44u, 4);
    ecx = lift_load(&env, ebp, 0xffffff78u, 4);
    ecx = lift_load(&env, ecx, 0x48u, 4);
    edi = 0x120u;
    edi = edi - eax;
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffff84u, 4, edi);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_407ab2;
    lift_store(&env, ebp, 0xffffff64u, 4, edx);
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_407acb;
    eax = eax - edx;
    lift_store(&env, ebp, 0xffffff68u, 4, eax);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffff6cu, 4, ecx);
L_4078b9:
    eax = lift_load(&env, ebp, 0xffffff78u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_407f2e;
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffff90u, 4, edi);
    lift_store(&env, ebp, 0xffffff94u, 4, edi);
    lift_store(&env, ebp, 0xffffff98u, 4, edi);
    lift_store(&env, ebp, 0xffffff9cu, 4, edi);
    edx = lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = ((edx * 4u));
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0xffffff78u, 4);
    {
        (void)lift_sub(32, lift_load(&env, edx, 0x14u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_407ae2;
    lift_store(&env, ebp, 0xffffff60u, 4, 0xffffffffu);
    edi = 0x2u;
    lift_store(&env, ebp, 0xffffff5cu, 4, edi);
    lift_store(&env, ebp, 0xffffff58u, 4, edi);
    lift_store(&env, ebp, 0xffffff54u, 4, edi);
    edx = lift_load(&env, eax, 0x524208u, 4);
    lift_store(&env, ebp, 0xffffffa0u, 4, edx);
    eax = lift_load(&env, eax, 0x523e60u, 4);
L_407929:
    lift_store(&env, ebp, 0xffffff88u, 4, eax);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffa4u, 4, edi);
    lift_store(&env, ebp, 0xffffff8cu, 4, edi);
    eax = lift_load(&env, ebp, 0xffffff78u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
L_40793d:
    eax = lift_load(&env, ebp, 0xffffff8cu, 4);
    eax = lift_load(&env, ebp, (eax * 4u) + 0xffffff64u, 4);
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, eax, 0x18u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = 0x4f5808u;
    edx = edx + eax;
    lift_store(&env, ebp, 0xffffffacu, 4, edx);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffa8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_407a59;
L_407967:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffa4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_407b13;
L_407971:
    edx = lift_load(&env, ebp, 0xffffffacu, 4);
    edx = lift_load(&env, edx, 0x4u, 4);
L_407977:
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, edx, 0x0u, 2);
    edx = edx + 0x2u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_407bcc;
    edx = ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        edx = r;
    }
    ecx = ecx & 0xfu;
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, edx, 0xfu, &fl);
    }
    if (!fl.zf)
        goto L_407bf0;
    edi = lift_load(&env, ebp, 0xffffff98u, 4);
    lift_store(&env, eax, ebp + 0xffffff54u, 4, edi);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + 1u;
    esi = esi - eax;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx + eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_407be5;
    eax = lift_load(&env, edx, 0x524288u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4079d5:
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
L_4079df:
    eax = lift_load(&env, ebp, 0xffffff90u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebx = ebx + eax;
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, ecx, 0xfu, &fl);
    }
    if (!fl.zf)
        goto L_407c3f;
    edx = lift_load(&env, ebp, 0xffffff98u, 4);
    lift_store(&env, eax, ebp + 0xffffff54u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + 1u;
    esi = esi - eax;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx + eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = ((ecx * 4u));
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_407c34;
    eax = lift_load(&env, eax, 0x524288u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_407a35:
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
L_407a3f:
    eax = lift_load(&env, ebp, 0xffffff90u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebx = ebx + eax;
    edi = lift_load(&env, ebp, 0xffffffa8u, 4);
    edi = edi - 1u;
    lift_store(&env, ebp, 0xffffffa8u, 4, edi);
    lift_store(&env, ebp, 0xffffffa4u, 4, lift_load(&env, ebp, 0xffffffa4u, 4) - 1u);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_407967;
L_407a59:
    lift_store(&env, ebp, 0xffffffe0u, 4, lift_load(&env, ebp, 0xffffffe0u, 4) + 0x4u);
    edi = lift_load(&env, ebp, 0xffffff8cu, 4);
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffff8cu, 4, edi);
    {
        (void)lift_sub(32, edi, 0x2u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40793d;
L_407a6d:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffff84u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_407c87;
L_407a77:
    ecx = 0x3u;
    edx = 0x4u;
L_407a81:
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffff88u, 4), &fl);
    }
    if (!fl.cf)
        goto L_407e77;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffa4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_407e34;
L_407a97:
    lift_store(&env, ebx, 0x0u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffff90u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, lift_load(&env, ebp, 0xffffffa4u, 4) - 1u);
    ebx = ebx + eax;
    lift_store(&env, ebx, 0x0u, 4, 0x0u);
    ebx = ebx + eax;
    goto L_407a81;
L_407ab2:
    lift_store(&env, ebp, 0xffffff64u, 4, eax);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffff68u, 4, edi);
    lift_store(&env, ebp, 0xffffff6cu, 4, edi);
    goto L_4078b9;
L_407acb:
    edi = ecx;
    edi = edi - edx;
    lift_store(&env, ebp, 0xffffff68u, 4, edi);
    eax = eax - ecx;
    lift_store(&env, ebp, 0xffffff6cu, 4, eax);
    goto L_4078b9;
L_407ae2:
    edx = 0xffffffffu;
    lift_store(&env, ebp, 0xffffff60u, 4, edx);
    lift_store(&env, ebp, 0xffffff5cu, 4, edx);
    lift_store(&env, ebp, 0xffffff58u, 4, edx);
    lift_store(&env, ebp, 0xffffff54u, 4, edx);
    edx = lift_load(&env, eax, 0x52420cu, 4);
    lift_store(&env, ebp, 0xffffffa0u, 4, edx);
    eax = lift_load(&env, eax, 0x523e64u, 4);
    goto L_407929;
L_407b13:
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    ecx = lift_load(&env, ebp, 0xffffffa0u, 4);
    ecx = ecx + 0x4u;
    lift_store(&env, ebp, 0xffffffa0u, 4, ecx);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    edi = (ecx + 0x4u);
    lift_store(&env, ebp, 0xffffffa0u, 4, edi);
    ebx = ebx + lift_load(&env, ebp, 0xffffff70u, 4);
    eax = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, ebp, 0xffffff94u, 4, eax);
    edx = (edi + 0x4u);
    lift_store(&env, ebp, 0xffffffa0u, 4, edx);
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
    ecx = (edx + 0x4u);
    lift_store(&env, ebp, 0xffffffa0u, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffff74u, 4);
    eax = eax + 0x4u;
    edi = lift_load(&env, ebp, 0xffffff94u, 4);
    {
        (void)lift_sub(32, edi, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_407b93;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff80u, 1)) & 0xffu);
    edx = lift_load(&env, ebp, 0xffffff74u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        edx = r;
    }
    ecx = ((edx * 4u));
    edx = lift_load(&env, ebp, 0xffffff78u, 4);
    edx = lift_load(&env, edx, 0x64u, 4);
    lift_store(&env, ebp, 0xffffff74u, 4, eax);
    eax = (edx + ecx);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    lift_store(&env, ebp, 0xffffff90u, 4, 0x1u);
    goto L_407971;
L_407b93:
    edx = ((edi * 4u));
    edi = lift_load(&env, ebp, 0xffffff78u, 4);
    edi = edi + edx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff80u, 1)) & 0xffu);
    edx = lift_load(&env, ebp, 0xffffff74u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        edx = r;
    }
    ecx = edx;
    edx = lift_load(&env, edi, 0x58u, 4);
    lift_store(&env, ebp, 0xffffff74u, 4, eax);
    eax = lift_load(&env, edx, (ecx * 4u) + 0x0u, 4);
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    lift_store(&env, ebp, 0xffffff90u, 4, 0x3u);
    goto L_407971;
L_407bcc:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_407bdb;
    esi = esi - 1u;
    goto L_407977;
L_407bdb:
    ecx = ecx + ecx;
    edx = edx - ecx;
    esi = esi - 1u;
    goto L_407977;
L_407be5:
    eax = lift_load(&env, edx, 0x524288u, 4);
    goto L_4079d5;
L_407bf0:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_407c2d;
    edi = lift_load(&env, ebp, 0xffffff98u, 4);
    lift_store(&env, eax, ebp + 0xffffff54u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_407c25;
    eax = lift_load(&env, edx, 0x524288u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_407c15:
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
    esi = esi - 1u;
    goto L_4079df;
L_407c25:
    eax = lift_load(&env, edx, 0x524288u, 4);
    goto L_407c15;
L_407c2d:
    lift_store(&env, ebx, 0x0u, 4, edx);
    goto L_4079df;
L_407c34:
    eax = lift_load(&env, eax, 0x524288u, 4);
    goto L_407a35;
L_407c3f:
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_407c80;
    edx = lift_load(&env, ebp, 0xffffff98u, 4);
    lift_store(&env, eax, ebp + 0xffffff54u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ((ecx * 4u));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_407c78;
    eax = lift_load(&env, edx, 0x524288u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_407c68:
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
    esi = esi - 1u;
    goto L_407a3f;
L_407c78:
    eax = lift_load(&env, edx, 0x524288u, 4);
    goto L_407c68;
L_407c80:
    lift_store(&env, ebx, 0x0u, 4, ecx);
    goto L_407a3f;
L_407c87:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_407a77;
    edx = lift_load(&env, ebp, 0xffffff78u, 4);
    edx = lift_load(&env, edx, 0x54u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    edx = edx + 0x4f5908u;
    edx = lift_load(&env, edx, 0x4u, 4);
    ecx = ecx ^ ecx;
L_407ca6:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xfffffff0u, 2, (eax & 0xffffu));
    edx = edx + 0x2u;
    {
        (void)lift_sub(16, (ecx & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_407d25;
L_407cb5:
    edx = edx ^ edx;
L_407cb7:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffa4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_407d60;
L_407cc1:
    lift_store(&env, ebp, 0xffffffa4u, 4, lift_load(&env, ebp, 0xffffffa4u, 4) - 1u);
    eax = lift_load(&env, ebp, 0xffffff90u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    edi = lift_load(&env, ebp, 0xffffff94u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edi = r;
    }
L_407cd3:
    ecx = (ecx & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = 0x8u;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffeeu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        (void)lift_and(32, ecx, eax, &fl);
    }
    if (fl.zf)
        goto L_407e29;
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    lift_store(&env, edi, ebp + 0xffffff54u, 4, eax);
    esi = esi - 1u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_407e18;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_407e21;
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_407d12:
    lift_store(&env, ebx, 0x0u, 4, eax);
L_407d14:
    ebx = ebx + lift_load(&env, ebp, 0xffffffb0u, 4);
    edx = edx + 1u;
    {
        (void)lift_sub(32, edx, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_407d52;
    lift_store(&env, ebp, 0xffffff84u, 4, lift_load(&env, ebp, 0xffffff84u, 4) - 1u);
    goto L_407a6d;
L_407d25:
    esi = esi - 1u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_407d46;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_407ca6;
    eax = lift_load(&env, ebp, 0xffffffeeu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax + eax;
    edx = edx - eax;
    goto L_407ca6;
L_407d46:
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xfffffff0u, 2, (eax & 0xffffu));
    esi = esi + 1u;
    goto L_407cb5;
L_407d52:
    {
        (void)lift_and(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_407cb7;
    goto L_407cd3;
L_407d60:
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    ecx = lift_load(&env, ebp, 0xffffffa0u, 4);
    ecx = ecx + 0x4u;
    lift_store(&env, ebp, 0xffffffa0u, 4, ecx);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    edi = (ecx + 0x4u);
    lift_store(&env, ebp, 0xffffffa0u, 4, edi);
    ebx = ebx + lift_load(&env, ebp, 0xffffff70u, 4);
    eax = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, ebp, 0xffffff94u, 4, eax);
    ecx = (edi + 0x4u);
    lift_store(&env, ebp, 0xffffffa0u, 4, ecx);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
    edi = (ecx + 0x4u);
    lift_store(&env, ebp, 0xffffffa0u, 4, edi);
    eax = lift_load(&env, ebp, 0xffffff74u, 4);
    eax = eax + 0x4u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_407ddf;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff80u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffff74u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = eax;
    eax = lift_load(&env, ebp, 0xffffff78u, 4);
    eax = lift_load(&env, eax, 0x64u, 4);
    edi = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, ebp, 0xffffff74u, 4, edi);
    eax = lift_load(&env, eax, (ecx * 4u) + 0x0u, 4);
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    lift_store(&env, ebp, 0xffffff90u, 4, 0x1u);
    goto L_407cc1;
L_407ddf:
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edi = lift_load(&env, ebp, 0xffffff78u, 4);
    edi = edi + eax;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff80u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffff74u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, edi, 0x58u, 4);
    edi = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, ebp, 0xffffff74u, 4, edi);
    eax = lift_load(&env, ecx, eax + 0x0u, 4);
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    lift_store(&env, ebp, 0xffffff90u, 4, 0x3u);
    goto L_407cc1;
L_407e18:
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffff84u, 4, lift_load(&env, ebp, 0xffffff84u, 4) - 1u);
    goto L_407a6d;
L_407e21:
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    goto L_407d12;
L_407e29:
    lift_store(&env, ebx, 0x0u, 4, 0x0u);
    goto L_407d14;
L_407e34:
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    eax = eax + edx;
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
    ebx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    edi = (eax + edx);
    lift_store(&env, ebp, 0xffffffa0u, 4, edi);
    ebx = ebx + lift_load(&env, ebp, 0xffffff70u, 4);
    eax = edi;
    edi = edi + edx;
    lift_store(&env, ebp, 0xffffffa0u, 4, edi);
    {
        (void)lift_sub(32, ecx, lift_load(&env, eax, 0x0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_407e6c;
    lift_store(&env, ebp, 0xffffff90u, 4, 0x1u);
    lift_store(&env, ebp, 0xffffffa0u, 4, lift_load(&env, ebp, 0xffffffa0u, 4) + edx);
    goto L_407a97;
L_407e6c:
    lift_store(&env, ebp, 0xffffff90u, 4, ecx);
    lift_store(&env, ebp, 0xffffffa0u, 4, lift_load(&env, ebp, 0xffffffa0u, 4) + edx);
    goto L_407a97;
L_407e77:
    eax = lift_load(&env, ebp, 0xffffff54u, 4);
    eax = eax + 1u;
    edx = lift_load(&env, ebp, 0xffffff78u, 4);
    lift_store(&env, edx, 0x30u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff58u, 4);
    eax = eax + 1u;
    lift_store(&env, edx, 0x34u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff5cu, 4);
    eax = eax + 1u;
    lift_store(&env, edx, 0x38u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff60u, 4);
    eax = eax + 1u;
    lift_store(&env, edx, 0x3cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff54u, 4);
    edx = lift_load(&env, ebp, 0xffffff58u, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_407f00;
L_407eb5:
    ecx = lift_load(&env, ebp, 0xffffff5cu, 4);
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_407f04;
L_407ebf:
    ecx = (eax + 0x1u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_407f08;
    eax = lift_load(&env, ebp, 0xffffff7cu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax - edx;
    eax = lift_load(&env, eax, (ecx * 4u) + 0x522da0u, 4);
L_407edd:
    edx = lift_load(&env, ebp, 0xffffff78u, 4);
    lift_store(&env, edx, 0x40u, 4, eax);
    edx = 0x10u;
L_407eeb:
    {
        (void)lift_sub(32, esi, 0x10u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40836c;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = esi - 0x10u;
    goto L_407eeb;
L_407f00:
    eax = edx;
    goto L_407eb5;
L_407f04:
    eax = ecx;
    goto L_407ebf;
L_407f08:
    ecx = lift_load(&env, ebp, 0xffffff60u, 4);
    edx = lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = ((edx * 4u));
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = lift_load(&env, eax, (ecx * 4u) + 0x523ed0u, 4);
    goto L_407edd;
L_407f2e:
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_408141;
    eax = 0x4f5ee0u;
L_407f3d:
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    lift_store(&env, ebp, 0xffffffbcu, 4, 0xffffffffu);
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    edx = lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = ((edx * 4u));
    eax = eax - edx;
    eax = lift_load(&env, 0u, (eax * 4u) + 0x524210u, 4);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffc8u, 4, edi);
    lift_store(&env, ebp, 0xffffffb8u, 4, edi);
    eax = lift_load(&env, ebp, 0xffffff78u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
L_407f76:
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = lift_load(&env, ebp, (eax * 4u) + 0xffffff64u, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_load(&env, eax, 0x18u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = 0x4f5808u;
    edx = edx + eax;
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffccu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40808c;
L_407fa0:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffc8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40814b;
L_407faa:
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    edx = lift_load(&env, edx, 0x4u, 4);
L_407fb0:
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, edx, 0x0u, 2);
    edx = edx + 0x2u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_408195;
    eax = ecx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    ecx = ecx & 0xfu;
    eax = (ebx + 0x4u);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        (void)lift_sub(32, edx, 0xfu, &fl);
    }
    if (!fl.zf)
        goto L_4081b9;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + 1u;
    esi = esi - eax;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx + eax;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4081ae;
    eax = lift_load(&env, eax, 0x524288u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_408018:
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
L_408024:
    eax = (ebx + 0x4u);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_sub(32, ecx, 0xfu, &fl);
    }
    if (!fl.zf)
        goto L_40820d;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + 1u;
    esi = esi - eax;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx + eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = ((ecx * 4u));
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_408202;
    eax = lift_load(&env, eax, 0x524288u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_40806e:
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
L_40807a:
    ecx = lift_load(&env, ebp, 0xffffffccu, 4);
    ecx = ecx - 1u;
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    lift_store(&env, ebp, 0xffffffc8u, 4, lift_load(&env, ebp, 0xffffffc8u, 4) - 1u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_407fa0;
L_40808c:
    lift_store(&env, ebp, 0xffffffdcu, 4, lift_load(&env, ebp, 0xffffffdcu, 4) + 0x4u);
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_407f76;
L_4080a0:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffff84u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_408316;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_408316;
    eax = lift_load(&env, ebp, 0xffffff78u, 4);
    eax = lift_load(&env, eax, 0x54u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax + 0x4f5908u;
    edx = lift_load(&env, eax, 0x4u, 4);
    ecx = ecx ^ ecx;
L_4080c8:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xfffffff4u, 2, (eax & 0xffffu));
    edx = edx + 0x2u;
    {
        (void)lift_sub(16, (ecx & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_408251;
L_4080db:
    edx = edx ^ edx;
L_4080dd:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffc8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40828c;
L_4080e7:
    lift_store(&env, ebp, 0xffffffc8u, 4, lift_load(&env, ebp, 0xffffffc8u, 4) - 1u);
L_4080ea:
    ecx = (ecx & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = 0x8u;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = lift_load(&env, ebp, 0xfffffff2u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = (ebx + 0x4u);
    {
        (void)lift_and(32, lift_load(&env, ebp, 0xffffffd8u, 4), eax, &fl);
    }
    if (fl.zf)
        goto L_4082fc;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    esi = esi - 1u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4082e1;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4082ea;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
    ebx = ecx;
    edx = edx + 1u;
    {
        (void)lift_sub(32, edx, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40827e;
    lift_store(&env, ebp, 0xffffff84u, 4, lift_load(&env, ebp, 0xffffff84u, 4) - 1u);
    goto L_4080a0;
L_408141:
    eax = 0x4f5f38u;
    goto L_407f3d;
L_40814b:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff74u, 4);
    edx = lift_load(&env, ebp, 0xffffffb4u, 4);
    lift_store(&env, ebp, 0xffffffc4u, 4, lift_load(&env, ebp, 0xffffffc4u, 4) + 0x4u);
    ecx = (eax + 0x4u);
    lift_store(&env, ebp, 0xffffff74u, 4, ecx);
    edi = (edx + 0x4u);
    lift_store(&env, ebp, 0xffffffb4u, 4, edi);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + lift_load(&env, edx, 0x0u, 4);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff80u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0xffffff78u, 4);
    edx = lift_load(&env, edx, 0x64u, 4);
    edi = lift_load(&env, edx, (eax * 4u) + 0x0u, 4);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    lift_store(&env, ebp, 0xffffffc4u, 4, lift_load(&env, ebp, 0xffffffc4u, 4) + 0x4u);
    goto L_407faa;
L_408195:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4081a4;
    esi = esi - 1u;
    goto L_407fb0;
L_4081a4:
    ecx = ecx + ecx;
    edx = edx - ecx;
    esi = esi - 1u;
    goto L_407fb0;
L_4081ae:
    eax = lift_load(&env, eax, 0x524288u, 4);
    goto L_408018;
L_4081b9:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4081f9;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4081f1;
    eax = lift_load(&env, eax, 0x524288u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4081df:
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    esi = esi - 1u;
    goto L_408024;
L_4081f1:
    eax = lift_load(&env, eax, 0x524288u, 4);
    goto L_4081df;
L_4081f9:
    lift_store(&env, ebx, 0x0u, 4, edx);
    ebx = eax;
    goto L_408024;
L_408202:
    eax = lift_load(&env, eax, 0x524288u, 4);
    goto L_40806e;
L_40820d:
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_408248;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_408240;
    eax = lift_load(&env, ecx, 0x524288u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_40822e:
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = esi - 1u;
    goto L_40807a;
L_408240:
    eax = lift_load(&env, ecx, 0x524288u, 4);
    goto L_40822e;
L_408248:
    lift_store(&env, ebx, 0x0u, 4, ecx);
    ebx = eax;
    goto L_40807a;
L_408251:
    esi = esi - 1u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_408272;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4046e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4080c8;
    eax = lift_load(&env, ebp, 0xfffffff2u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax + eax;
    edx = edx - eax;
    goto L_4080c8;
L_408272:
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xfffffff4u, 2, (edx & 0xffffu));
    esi = esi + 1u;
    goto L_4080db;
L_40827e:
    {
        (void)lift_and(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4080dd;
    goto L_4080ea;
L_40828c:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    edi = lift_load(&env, ebp, 0xffffffc4u, 4);
    edi = edi + 0x4u;
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    eax = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff74u, 4);
    ecx = lift_load(&env, ebp, 0xffffffb4u, 4);
    edi = edi + 0x4u;
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    edi = (eax + 0x4u);
    lift_store(&env, ebp, 0xffffff74u, 4, edi);
    edi = (ecx + 0x4u);
    lift_store(&env, ebp, 0xffffffb4u, 4, edi);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + lift_load(&env, ecx, 0x0u, 4);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff80u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = ((eax * 4u));
    eax = lift_load(&env, ebp, 0xffffff78u, 4);
    eax = lift_load(&env, eax, 0x64u, 4);
    edi = lift_load(&env, ecx, eax + 0x0u, 4);
    goto L_4080e7;
L_4082e1:
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffff84u, 4, lift_load(&env, ebp, 0xffffff84u, 4) - 1u);
    goto L_4080a0;
L_4082ea:
    lift_store(&env, ebx, 0x0u, 4, edi);
    ebx = ecx;
    edx = edx + 1u;
    {
        (void)lift_sub(32, edx, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40827e;
    lift_store(&env, ebp, 0xffffff84u, 4, lift_load(&env, ebp, 0xffffff84u, 4) - 1u);
    goto L_4080a0;
L_4082fc:
    lift_store(&env, ebx, 0x0u, 4, 0x0u);
    ebx = ecx;
    edx = edx + 1u;
    {
        (void)lift_sub(32, edx, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40827e;
    lift_store(&env, ebp, 0xffffff84u, 4, lift_load(&env, ebp, 0xffffff84u, 4) - 1u);
    goto L_4080a0;
L_408316:
    edx = lift_load(&env, ebp, 0xffffff70u, 4);
    edx = edx + 0x900u;
    edx = edx - ebx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        edx = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_40833a;
    eax = eax ^ eax;
L_40832d:
    lift_store(&env, ebx, 0x0u, 4, eax);
    ebx = ebx + 0x4u;
    lift_store(&env, ebx, 0x0u, 4, eax);
    {
        uint32_t r = lift_add(32, ebx, 0x4u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    if (!fl.zf)
        goto L_40832d;
L_40833a:
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    eax = eax + 1u;
    edx = lift_load(&env, ebp, 0xffffff78u, 4);
    lift_store(&env, edx, 0x3cu, 4, eax);
    ecx = eax;
    edx = lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = ((edx * 4u));
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = lift_load(&env, eax, (ecx * 4u) + 0x523eccu, 4);
    goto L_407edd;
L_40836c:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_408382;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x404610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_408377:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_408382:
    if (fl.sf == fl.of)
        goto L_408377;
    eax = 0x1u;
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

uint32_t lifted_f4083a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4083A0_STACK + 4 + 4 * 2 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4083A0_STACK, 2, entry);
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
    lift_store(&env, esp, 0x38u, 4, edx);
    lift_store(&env, esp, 0x3cu, 4, ebx);
    ebx = lift_load(&env, esp, 0x70u, 4);
    lift_store(&env, esp, 0x40u, 4, eax);
    eax = ((ecx * 8u));
    eax = eax + ecx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    ecx = 0x4f5918u;
    ecx = ecx + eax;
    lift_store(&env, esp, 0x24u, 4, ecx);
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x74u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4084b9;
    eax = lift_load(&env, esp, 0x3cu, 4);
    eax = lift_load(&env, eax, 0xcu, 4);
    eax = eax & 0x1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4084a4;
    ecx = 0x523098u;
    ecx = ecx + eax;
    lift_store(&env, esp, 0x44u, 4, ecx);
    ecx = 0x522f98u;
L_4083fd:
    ecx = ecx + eax;
    lift_store(&env, esp, 0x48u, 4, ecx);
L_408403:
    eax = lift_load(&env, esp, 0x3cu, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4086d8;
    ecx = ecx ^ ecx;
    lift_store(&env, esp, 0x4u, 4, ecx);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x14u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4084e7;
L_408421:
    edi = edi ^ edi;
    lift_store(&env, esp, 0x4cu, 4, edi);
    eax = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    lift_store(&env, esp, 0xcu, 4, 0x21u);
L_408437:
    eax = lift_load(&env, esp, 0x8u, 4);
    eax = lift_load(&env, eax, 0x30u, 4);
    lift_store(&env, esp, 0x54u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_40857d;
L_40844b:
    eax = lift_load(&env, esp, 0x54u, 4);
    eax = (eax + (eax * 2u));
    ebx = lift_load(&env, esp, 0x4cu, 4);
    eax = eax + ebx;
    lift_store(&env, esp, 0x50u, 4, eax);
    eax = lift_load(&env, esp, 0x54u, 4);
    eax = eax + eax;
    esi = lift_load(&env, esp, 0x24u, 4);
    eax = eax + esi;
    lift_store(&env, esp, 0x58u, 4, eax);
L_40846c:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x54u, 4), 0xcu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4085f6;
    eax = lift_load(&env, esp, 0x50u, 4);
    ecx = lift_load(&env, esp, 0x3cu, 4);
    eax = eax - lift_load(&env, ecx, 0x14u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + lift_load(&env, esp, 0x38u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_sub(32, eax, 0x7u, &fl);
    }
    if (!fl.zf)
        goto L_408588;
L_408494:
    lift_store(&env, esp, 0x50u, 4, lift_load(&env, esp, 0x50u, 4) + 0x3u);
    lift_store(&env, esp, 0x58u, 4, lift_load(&env, esp, 0x58u, 4) + 0x2u);
    lift_store(&env, esp, 0x54u, 4, lift_load(&env, esp, 0x54u, 4) + 1u);
    goto L_40846c;
L_4084a4:
    ecx = 0x523118u;
    ecx = ecx + eax;
    lift_store(&env, esp, 0x44u, 4, ecx);
    ecx = 0x523018u;
    goto L_4083fd;
L_4084b9:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4084d2;
    lift_store(&env, esp, 0x44u, 4, 0x523258u);
    lift_store(&env, esp, 0x48u, 4, 0x5231d8u);
    goto L_408403;
L_4084d2:
    lift_store(&env, esp, 0x44u, 4, 0x523218u);
    lift_store(&env, esp, 0x48u, 4, 0x523198u);
    goto L_408403;
L_4084e7:
    lift_store(&env, esp, 0x4u, 4, 0x1u);
    goto L_408421;
L_4084f4:
    lift_store(&env, esp, 0x8u, 4, lift_load(&env, esp, 0x8u, 4) + 0x4u);
    lift_store(&env, esp, 0xcu, 4, lift_load(&env, esp, 0xcu, 4) + 1u);
    ebp = lift_load(&env, esp, 0x4cu, 4);
    ebp = ebp + 1u;
    lift_store(&env, esp, 0x4cu, 4, ebp);
    {
        (void)lift_sub(32, ebp, 0x3u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_408437;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_408574;
    eax = lift_load(&env, esp, 0x3cu, 4);
    eax = lift_load(&env, eax, 0x3cu, 4);
    lift_store(&env, esp, 0x28u, 4, eax);
    ecx = (eax + eax);
    ecx = ecx + lift_load(&env, esp, 0x24u, 4);
    edi = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, ecx, 0x0u, 2);
    {
        (void)lift_sub(32, eax, 0x8u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_408574;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, esp, 0x38u, 4);
    eax = eax + ebx;
    lift_store(&env, esp, 0x10u, 4, eax);
    lift_store(&env, esp, 0x18u, 4, ecx);
L_408541:
    esi = lift_load(&env, esp, 0x18u, 4);
    esi = lift_load(&env, esi, 0x2cu, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        esi = r;
    }
    eax = lift_load(&env, esp, 0x10u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_sub(32, eax, 0x7u, &fl);
    }
    if (!fl.zf)
        goto L_408684;
    edi = edi + esi;
L_40855c:
    lift_store(&env, esp, 0x10u, 4, lift_load(&env, esp, 0x10u, 4) + 0x4u);
    lift_store(&env, esp, 0x18u, 4, lift_load(&env, esp, 0x18u, 4) + 0x2u);
    eax = lift_load(&env, esp, 0x28u, 4);
    eax = eax + 1u;
    lift_store(&env, esp, 0x28u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x8u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_408541;
L_408574:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_40857d:
    ecx = ecx ^ ecx;
    lift_store(&env, esp, 0x4u, 4, ecx);
    goto L_40844b;
L_408588:
    esi = lift_load(&env, esp, 0x58u, 4);
    esi = lift_load(&env, esi, 0x74u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        esi = r;
    }
    edi = lift_load(&env, esp, 0x58u, 4);
    edi = lift_load(&env, edi, 0x58u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    edi = edi + lift_load(&env, esp, 0x4cu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebp = lift_load(&env, esp, 0x44u, 4);
    ebp = lift_load(&env, eax, ebp + 0x0u, 4);
    eax = eax + lift_load(&env, esp, 0x48u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esp, 0x5cu, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_408494;
    ecx = ((edi * 4u));
    ecx = ecx + lift_load(&env, esp, 0x40u, 4);
L_4085c7:
    ebx = lift_load(&env, ecx, 0x0u, 4);
    eax = ebx;
    edx = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = ebx;
    edx = lift_load(&env, esp, 0x5cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x900u, 4, eax);
    esi = esi - 1u;
    ecx = ecx + 0xcu;
    edi = edi + 0x3u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_408494;
    goto L_4085c7;
L_4085f6:
    eax = lift_load(&env, esp, 0xcu, 4);
    ecx = lift_load(&env, esp, 0x3cu, 4);
    eax = eax - lift_load(&env, ecx, 0x14u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + lift_load(&env, esp, 0x38u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    esi = lift_load(&env, esp, 0x24u, 4);
    esi = lift_load(&env, esi, 0x8cu, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        esi = r;
    }
    ebp = lift_load(&env, esp, 0x24u, 4);
    ebp = lift_load(&env, ebp, 0x70u, 4);
    {
        uint32_t a = ebp;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebp = r;
    }
    ebp = ebp + lift_load(&env, esp, 0x4cu, 4);
    {
        (void)lift_sub(32, eax, 0x7u, &fl);
    }
    if (fl.zf)
        goto L_4084f4;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edi = lift_load(&env, esp, 0x44u, 4);
    edi = lift_load(&env, edi, eax + 0x0u, 4);
    eax = eax + lift_load(&env, esp, 0x48u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esp, 0x30u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4084f4;
    ecx = ((ebp * 4u));
    ecx = ecx + lift_load(&env, esp, 0x40u, 4);
L_408655:
    ebx = lift_load(&env, ecx, 0x0u, 4);
    eax = ebx;
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = ebx;
    edx = lift_load(&env, esp, 0x30u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x900u, 4, eax);
    esi = esi - 1u;
    ecx = ecx + 0xcu;
    ebp = ebp + 0x3u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4084f4;
    goto L_408655;
L_408684:
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebp = lift_load(&env, esp, 0x44u, 4);
    ebp = lift_load(&env, eax, ebp + 0x0u, 4);
    eax = eax + lift_load(&env, esp, 0x48u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esp, 0x2cu, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40855c;
    ecx = ((edi * 4u));
    ecx = ecx + lift_load(&env, esp, 0x40u, 4);
L_4086ab:
    ebx = lift_load(&env, ecx, 0x0u, 4);
    eax = ebx;
    edx = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = ebx;
    edx = lift_load(&env, esp, 0x2cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x900u, 4, eax);
    esi = esi - 1u;
    ecx = ecx + 0x4u;
    edi = edi + 1u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40855c;
    goto L_4086ab;
L_4086d8:
    eax = lift_load(&env, eax, 0x3cu, 4);
    lift_store(&env, esp, 0x20u, 4, eax);
    esi = (eax + eax);
    esi = esi + lift_load(&env, esp, 0x24u, 4);
    edi = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, esi, 0x0u, 2);
    edx = lift_load(&env, esp, 0x20u, 4);
    {
        (void)lift_sub(32, edx, 0x15u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_408786;
    eax = ((edx * 4u));
    ebp = lift_load(&env, esp, 0x38u, 4);
    eax = eax + ebp;
    lift_store(&env, esp, 0x14u, 4, eax);
    lift_store(&env, esp, 0x1cu, 4, esi);
L_40870b:
    esi = lift_load(&env, esp, 0x1cu, 4);
    esi = lift_load(&env, esi, 0x2cu, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        esi = r;
    }
    eax = lift_load(&env, esp, 0x14u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_sub(32, eax, 0x7u, &fl);
    }
    if (fl.zf)
        goto L_4087f2;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebp = lift_load(&env, esp, 0x44u, 4);
    ebp = lift_load(&env, eax, ebp + 0x0u, 4);
    eax = eax + lift_load(&env, esp, 0x48u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esp, 0x34u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40876e;
    ecx = ((edi * 4u));
    ecx = ecx + lift_load(&env, esp, 0x40u, 4);
L_408747:
    ebx = lift_load(&env, ecx, 0x0u, 4);
    eax = ebx;
    edx = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = ebx;
    edx = lift_load(&env, esp, 0x34u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x900u, 4, eax);
    esi = esi - 1u;
    ecx = ecx + 0x4u;
    edi = edi + 1u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_408747;
L_40876e:
    lift_store(&env, esp, 0x14u, 4, lift_load(&env, esp, 0x14u, 4) + 0x4u);
    lift_store(&env, esp, 0x1cu, 4, lift_load(&env, esp, 0x1cu, 4) + 0x2u);
    ecx = lift_load(&env, esp, 0x20u, 4);
    ecx = ecx + 1u;
    lift_store(&env, esp, 0x20u, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0x15u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40870b;
L_408786:
    eax = lift_load(&env, esp, 0x38u, 4);
    eax = lift_load(&env, eax, 0x50u, 4);
    {
        (void)lift_sub(32, eax, 0x7u, &fl);
    }
    if (fl.zf)
        goto L_408574;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebp = lift_load(&env, esp, 0x44u, 4);
    ebp = lift_load(&env, eax, ebp + 0x0u, 4);
    eax = eax + lift_load(&env, esp, 0x48u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    esi = lift_load(&env, esp, 0x24u, 4);
    esi = lift_load(&env, esi, 0x56u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_408574;
    ecx = ((edi * 4u));
    ecx = ecx + lift_load(&env, esp, 0x40u, 4);
L_4087c6:
    ebx = lift_load(&env, ecx, 0x0u, 4);
    eax = ebx;
    edx = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = ebx;
    edx = lift_load(&env, esp, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x900u, 4, eax);
    esi = esi - 1u;
    ecx = ecx + 0x4u;
    edi = edi + 1u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_408574;
    goto L_4087c6;
L_4087f2:
    edi = edi + esi;
    goto L_40876e;
}

uint32_t lifted_curve_table_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_CURVE_TABLE_BUILD_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_CURVE_TABLE_BUILD_STACK, 0, entry);
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
    esp = esp - 0x8u;
    edi = edx;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_40ba23;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_40ba23;
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (fl.zf)
        goto L_40ba23;
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.zf)
        goto L_40ba23;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_40ba87;
L_40ba23:
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_40ba7c;
    {
        (void)lift_sub(32, edi, 0x100u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_40ba7c;
    lift_store(&env, 0u, 0x52f1fcu, 4, 0xffffd8f0u);
    eax = eax ^ eax;
    edx = 0x3f700000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9e2fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    lift_store(&env, esp, 0x0u, 4, edx);
    lift_store(&env, esp, 0x4u, 4, edi);
    esi = 0x4u;
L_40ba54:
    eax = edi;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_40ba8e;
    edx = 0xc0c38800u;
L_40ba62:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb892u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x52f1fcu, 4, eax);
    edi = edi + lift_load(&env, esp, 0x4u, 4);
    esi = esi + 0x4u;
    {
        (void)lift_sub(32, esi, 0x104u, &fl);
    }
    if (!fl.zf)
        goto L_40ba54;
L_40ba7c:
    eax = eax ^ eax;
L_40ba7e:
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
L_40ba87:
    eax = 0x2u;
    goto L_40ba7e;
L_40ba8e:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x3f700000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9e2fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0xc09f4000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebp;
    ecx = lift_load(&env, esp, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_40ba62;
}

uint32_t lifted_object_free_tree(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_FREE_TREE_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_FREE_TREE_STACK, 0, entry);
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
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_40f059;
    edx = lift_load(&env, eax, 0x150u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_40efe0;
    ecx = ecx ^ ecx;
L_40efb2:
    eax = eax ^ eax;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x28u, 2)) & 0xffffu);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (!fl.cf)
        goto L_40efd5;
    ebx = lift_load(&env, edx, 0x8u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_40efcc;
L_40efc6:
    ecx = ecx + 1u;
    edx = edx + 0xcu;
    goto L_40efb2;
L_40efcc:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_40efc6;
L_40efd5:
    eax = lift_load(&env, ebx, 0x150u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_40efe0:
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = lift_load(&env, esi, 0x154u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_40f043;
    edi = edi ^ edi;
L_40efef:
    eax = eax ^ eax;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edx, 0x2au, 2)) & 0xffffu);
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.cf)
        goto L_40f038;
    ebx = lift_load(&env, esi, 0xf8u, 4);
    ecx = ecx ^ ecx;
    edx = (ebx + 0x24u);
L_40f007:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x80u, 2)) & 0xffffu);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (!fl.cf)
        goto L_40f024;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40aca0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx + 1u;
    edx = edx + 0x3cu;
    ebx = ebx + 0x3cu;
    goto L_40f007;
L_40f024:
    eax = lift_load(&env, esi, 0xf8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi + 1u;
    esi = esi + 0xfcu;
    goto L_40efef;
L_40f038:
    eax = lift_load(&env, edx, 0x154u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_40f043:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
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
L_40f059:
    ecx = 0x2u;
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

uint32_t lifted_object_attach_item(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_ATTACH_ITEM_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_ATTACH_ITEM_STACK, 0, entry);
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
    ebx = 0x16u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x18u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40f9ce;
    edx = 0x3cu;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_40f94b;
    eax = 0x8u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_40f94b:
    lift_store(&env, edi, 0x80u, 2, 0x1u);
    lift_store(&env, edi, 0xf8u, 4, eax);
    lift_store(&env, eax, 0x3au, 2, 0x0u);
    edx = lift_load(&env, ecx, 0x18u, 4);
    lift_store(&env, eax, 0x2cu, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x25u, 1)) & 0xffu);
    lift_store(&env, eax, 0x20u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x24u, 1)) & 0xffu);
    lift_store(&env, eax, 0x23u, 1, (edx & 0xffu));
    lift_store(&env, eax, 0x21u, 1, 0x80u);
    edx = lift_load(&env, ecx, 0x1cu, 4);
    edx = edx + 0x2u;
    ebx = lift_load(&env, ecx, 0x20u, 4);
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (!fl.cf)
        goto L_40f998;
    {
        (void)lift_sub(32, ebx, lift_load(&env, ecx, 0x18u, 4), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_40f998;
    lift_store(&env, eax, 0x3au, 1, lift_load(&env, eax, 0x3au, 1) | 0x10u);
    edx = lift_load(&env, ecx, 0x1cu, 4);
    lift_store(&env, eax, 0x30u, 4, edx);
    edx = lift_load(&env, ecx, 0x20u, 4);
    lift_store(&env, eax, 0x34u, 4, edx);
L_40f998:
    eax = (esi + 0x24u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ac50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_40f9d0;
    edx = lift_load(&env, esi, 0x2cu, 4);
    eax = lift_load(&env, esi, 0x24u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40c220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esi, 0x24u, 4);
    ebx = lift_load(&env, esi, 0x2cu, 4);
L_40f9b5:
    ebx = ebx - 1u;
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_40f9c1;
    lift_store(&env, eax, 0x0u, 1, lift_load(&env, eax, 0x0u, 1) ^ 0x80u);
    eax = eax + 1u;
    goto L_40f9b5;
L_40f9c1:
    ebx = lift_load(&env, esi, 0x2cu, 4);
    eax = (esi + 0x24u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40acd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_40f9ce:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_40f9d0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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

uint32_t lifted_f416140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F416140_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F416140_STACK, 0, entry);
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
    esp = esp - 0x2cu;
    eax = (ebp + 0xffffffc4u);
    edx = 0x4ec1ecu;
    ecx = 0x513a58u;
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
    eax = lift_load(&env, 0u, 0x4f819cu, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f819cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417290u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f3d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    edx = lift_load(&env, 0u, 0x532bf4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47fa20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_41635e;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c3b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_41631c;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c3d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4162d9;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48b7e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_416297;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f0f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_416247;
    edx = 0x50d430u;
    eax = (ebp + 0xffffffd8u);
    ecx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffd8u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f7b70u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    lift_store(&env, 0u, 0x532a4cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    env.chain = eax;
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
L_416247:
    edx = 0x50d441u;
    eax = (ebp + 0xffffffdcu);
    esi = 0x3u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffffd0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffdcu);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48b970u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    env.chain = eax;
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
L_416297:
    edx = 0x50d45du;
    eax = (ebp + 0xffffffe0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x5u);
    edx = eax;
    eax = 0x532c24u;
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
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    env.chain = eax;
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
L_4162d9:
    edx = 0x50d47bu;
    eax = (ebp + 0xffffffe4u);
    esi = 0x7u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffffd0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe4u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    env.chain = eax;
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
L_41631c:
    edx = 0x50d499u;
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x9u);
    edx = eax;
    eax = 0x532c24u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe8u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    env.chain = eax;
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
L_41635e:
    edx = 0x50d4b6u;
    eax = (ebp + 0xffffffecu);
    esi = 0xbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffffd0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffecu);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    env.chain = eax;
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

uint32_t lifted_f416500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F416500_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F416500_STACK, 0, entry);
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
    esp = esp - 0x44u;
    eax = (ebp + 0xffffffa8u);
    edx = 0x4ec1ecu;
    ecx = 0x513ae0u;
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
    eax = lift_load(&env, 0u, 0x4f819cu, 4);
    lift_store(&env, ebp, 0xffffffacu, 4, edx);
    lift_store(&env, ebp, 0xffffffb0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f819cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417290u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f410u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4168b5;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = (ebp + 0xffffffbcu);
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_416673;
    {
        (void)lift_sub(32, edx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4166c7;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c680u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, 0u, 0x4f7b40u, 4);
    edx = ebx;
    ecx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418150u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_41671a;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c390u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_41687a;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c460u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_416842;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f3d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48b7e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_416803;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41679e;
    edx = 0x50d5afu;
    eax = (ebp + 0xffffffd8u);
    ecx = 0xcu;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffd8u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48b970u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_416649:
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
L_41664c:
    eax = eax ^ eax;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    eax = (ebp + 0xffffffbcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffb4u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
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
L_416673:
    edx = 0x50d53fu;
    eax = (ebp + 0xffffffc0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    lift_store(&env, ebp, 0xffffffb4u, 4, 0x2u);
    eax = 0x532c24u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ebx;
    eax = (ebp + 0xffffffc0u);
    edx = edx ^ ebx;
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffbcu);
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    edx = edx ^ edx;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
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
L_4166c7:
    edx = 0x50d557u;
    eax = (ebp + 0xffffffc4u);
    ecx = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = esi ^ esi;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffc4u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffbcu);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb4u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 4, esi);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
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
L_41671a:
    eax = (ebp + 0xffffffc8u);
    edx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418170u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x6u;
    eax = (ebp + 0xffffffccu);
    lift_store(&env, ebp, 0xffffffb4u, 4, edx);
    edx = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418170u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = lift_load(&env, ebp, 0xffffffc8u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x50d576u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffbcu);
    ecx = 0x7u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffffbcu);
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0x10u;
    eax = (ebp + 0xffffffd0u);
    edi = 0x8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffffb4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffd0u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
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
L_41679e:
    edx = 0x50d59fu;
    eax = (ebp + 0xffffffd4u);
    ecx = 0xau;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi ^ edi;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffd4u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f7b74u, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x532a4cu, 4, eax);
    eax = (ebp + 0xffffffbcu);
    lift_store(&env, ebp, 0xffffffb4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 4, edi);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
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
L_416803:
    edx = 0x50d5cbu;
    eax = (ebp + 0xffffffdcu);
    edi = 0xeu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffffb4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    eax = (ebp + 0xffffffdcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 4, 0x1u);
    goto L_41664c;
L_416842:
    edx = 0x50d5e9u;
    eax = (ebp + 0xffffffe0u);
    ecx = 0x10u;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe0u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_416649;
L_41687a:
    edx = 0x50d605u;
    eax = (ebp + 0xffffffe4u);
    esi = 0x12u;
    edi = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffffb4u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe4u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 4, edi);
    goto L_41664c;
L_4168b5:
    edx = 0x50d622u;
    eax = (ebp + 0xffffffe8u);
    esi = 0x14u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x532c24u;
    lift_store(&env, ebp, 0xffffffb4u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b76d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe8u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
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

uint32_t lifted_point_list_add(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_POINT_LIST_ADD_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_POINT_LIST_ADD_STACK, 0, entry);
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
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    edx = eax;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    {
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

uint32_t lifted_f418af0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F418AF0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F418AF0_STACK, 0, entry);
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
    esp = esp - 0x104u;
    esi = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xd8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_418c17;
    eax = 0x4cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418b16:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c21u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x5334a0u;
    edx = 0x4fc5a8u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffeecu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffeecu);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4816f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x441f20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482720u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482550u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x598d34u, 1, ((eax >> 8) & 0xffu));
    eax = 0x598d48u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482720u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x598d48u;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482550u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    lift_store(&env, 0u, 0x598d4cu, 1, (edx & 0xffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7da0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_418bb1;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7c00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418bb1:
    eax = 0x5536c8u;
    edx = esi;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476a00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_418bd0;
    eax = 0x5536c8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476d20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418bd0:
    ecx = 0x1u;
    eax = 0x553798u;
    edx = esi;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476a00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_418bf2;
    eax = 0x553798u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476d20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418bf2:
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = esi;
    ebx = ebx ^ ebx;
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477af0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_418c21;
L_418c0e:
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
L_418c17:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x415db0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_418b16;
L_418c21:
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477d70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532b64u, 4);
    edx = esi;
    lift_store(&env, 0u, 0x55893cu, 4, eax);
    eax = 0x1u;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x55608cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4772f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_418c0e;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4760c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4765b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c60u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x441e30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c60u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x474e00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45dca0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f418d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F418D50_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F418D50_STACK, 0, entry);
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
    esp = esp - 0x234u;
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = (ebp + 0xffffffc0u);
    edx = 0x4ec1ecu;
    ecx = 0x513f84u;
    esi = 0x533450u;
    edi = 0x5332c0u;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43eab0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx ^ ecx;
L_418da6:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = 0x50d7c7u;
    eax = lift_load(&env, eax, 0x0u, 4);
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_41914e;
L_418dbf:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_418e12;
    edx = 0x50d7c8u;
    eax = lift_load(&env, edi, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_418e12;
    edx = 0x4fc290u;
    eax = (ebp + 0xfffffebcu);
    ebx = lift_load(&env, edi, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_418e12;
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423d70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45ecd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418e0b:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418e12:
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = edi + 0x4u;
    eax = eax + 0x4u;
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_sub(32, ecx, 0x14u, &fl);
    }
    if (fl.cf)
        goto L_418da6;
    ecx = ecx ^ ecx;
    ebx = 0x5334a0u;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c1fu, 1)) & 0xffu);
    edx = 0x4fc5a8u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = (ebp + 0xfffffebcu);
    ebx = lift_load(&env, ecx, ebx + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx + 0x533578u;
    edx = 0x4fc5a8u;
    eax = (ebp + 0xfffffdb8u);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffdb8u);
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_418e90;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45ec50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418e90:
    eax = 0x1u;
    ebx = 0x5334a0u;
    ecx = ecx ^ ecx;
    edx = 0x4fc5a8u;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c20u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = (ebp + 0xfffffebcu);
    ebx = lift_load(&env, ecx, ebx + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx + 0x533578u;
    edx = 0x4fc5a8u;
    eax = (ebp + 0xfffffdb8u);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffdb8u);
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_418ef8;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f1f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418ef8:
    eax = 0x1u;
    ebx = 0x5334a0u;
    ecx = ecx ^ ecx;
    edx = 0x4fc5a8u;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c23u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = (ebp + 0xfffffebcu);
    ebx = lift_load(&env, ecx, ebx + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx + 0x533578u;
    edx = 0x4fc5a8u;
    eax = (ebp + 0xfffffdb8u);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffdb8u);
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    edi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_418fc0;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45ed60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x5334a0u;
    edx = 0x4fc5a8u;
    esi = lift_load(&env, 0u, 0x513c3au, 1);
    eax = (ebp + 0xfffffebcu);
    ebx = lift_load(&env, ebx, (esi * 4u) + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x533578u;
    edx = 0x4fc5a8u;
    eax = (ebp + 0xfffffdb8u);
    ebx = lift_load(&env, ebx, (esi * 4u) + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffdb8u);
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_418fb9;
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45ef40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418fb9:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_418fc0:
    eax = 0x1u;
    ebx = 0x5334a0u;
    ecx = ecx ^ ecx;
    edx = 0x4fc5a8u;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c22u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = (ebp + 0xfffffebcu);
    ebx = lift_load(&env, ecx, ebx + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx + 0x533578u;
    edx = 0x4fc5a8u;
    eax = (ebp + 0xfffffdb8u);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffdb8u);
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_419192;
L_419020:
    eax = 0x1u;
    ecx = 0x53612cu;
    ebx = 0x534f5cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x414a90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x414b10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e690u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
L_419058:
    {
        uint32_t r = lift_imul(32, edi, 0xf0u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = 0x4fc9c8u;
    ebx = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = 0x4fc9c8u;
    eax = (ebp + 0xfffffdb8u);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = (ebp + 0xfffffdb8u);
    eax = (ebp + 0xfffffebcu);
    ebx = lift_load(&env, ebx, 0x5347f0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423dc0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4190cd;
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = eax;
    eax = edi;
    ecx = lift_load(&env, ecx, 0x5384ccu, 4);
    ebx = lift_load(&env, ebx, 0x5372fcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4190cd:
    eax = 0x1u;
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi + 1u;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    esi = esi + 0x4u;
    edx = edx + 0xf0u;
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    eax = eax + 0xf0u;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_sub(32, edi, 0x13u, &fl);
    }
    if (fl.cf)
        goto L_419058;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e6b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41e5e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45ed40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41d640u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    env.chain = eax;
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
L_41914e:
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = 0x4fc8c0u;
    eax = (ebp + 0xfffffebcu);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_418dbf;
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423d70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45ed10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_418e0b;
L_419192:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45ee30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_419020;
}

uint32_t lifted_f4192a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4192A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4192A0_STACK, 0, entry);
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
    eax = (ebp + 0xffffffd4u);
    edx = 0x4ec1ecu;
    ecx = 0x513f94u;
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
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9ca6u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4192f2;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
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
L_4192f2:
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x50d7d4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe8u);
    esi = 0x1u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
L_41930e:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4895e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_419331;
    edx = edx + eax;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x50d7e0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    goto L_41930e;
L_419331:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, 0u, 0x558c7cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x473e60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f81a8u, 4);
    ebx = lift_load(&env, 0u, 0x532b9cu, 4);
    eax = eax ^ eax;
    edx = lift_load(&env, 0u, (edx * 4u) + 0x533164u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482a60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f81a8u, 4);
    eax = 0x4u;
    ebx = lift_load(&env, 0u, 0x532b9cu, 4);
    edx = lift_load(&env, 0u, (edx * 4u) + 0x533164u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482a60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472c10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = (ebp + 0xffffffe8u);
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
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

uint32_t lifted_f4193b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4193B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4193B0_STACK, 0, entry);
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
    eax = (ebp + 0xffffffd4u);
    edx = 0x4ec1ecu;
    ecx = 0x513fa0u;
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
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9ca6u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_419402;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
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
L_419402:
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x50d7ecu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe8u);
    esi = 0x1u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
L_41941e:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4895e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_419441;
    edx = edx + eax;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x50d7f8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    goto L_41941e;
L_419441:
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, 0u, 0x558c7cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x473e60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486da0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = (ebp + 0xffffffe8u);
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
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

uint32_t lifted_f41acc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41ACC0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41ACC0_STACK, 0, entry);
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
    esp = esp - 0x320u;
    ecx = eax;
    eax = (ebp + 0xffffffdcu);
    edx = 0x4ec1ecu;
    ebx = 0x513ff4u;
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
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    ebx = ebx ^ ebx;
    esi = esi ^ esi;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x53bd08u, 1)) & 0xffu);
    eax = (ebp + 0xfffffcd0u);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    ebx = ebx + 0x5334a0u;
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    edx = 0x4fc398u;
    ebx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c18u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x5334a0u;
    edx = 0x4fc398u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffdd4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c19u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x5334a0u;
    edx = 0x4fc398u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffed8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ebp + 0xfffffdd4u);
    edx = (ebp + 0xfffffcd0u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a9a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x1u;
    edx = lift_load(&env, 0u, 0x533cccu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4191b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532ab4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4651b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f84b8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41e310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f84ccu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41e310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472db0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffed8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472ad0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472f80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f84ccu, 4);
    eax = lift_load(&env, 0u, 0x4f84b8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4731a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4760c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4765b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3bu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3cu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3du;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3eu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5fu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476120u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x60u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476120u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477d70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417f40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532a98u, 4);
    lift_store(&env, 0u, 0x532a4cu, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aa20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471b00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ab60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ab30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ab00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aaa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f81b4u, 4);
    ebx = lift_load(&env, 0u, 0x532b9cu, 4);
    eax = eax ^ eax;
    edx = lift_load(&env, 0u, (edx * 4u) + 0x533164u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482a60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f81b4u, 4);
    eax = 0x4u;
    ebx = lift_load(&env, 0u, 0x532b9cu, 4);
    edx = lift_load(&env, 0u, (edx * 4u) + 0x533164u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482a60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5588f8u;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477e30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4766b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x422800u;
    eax = ecx;
    lift_store(&env, ecx, 0xc8u, 1, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x41af30u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
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

uint32_t lifted_f41df30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41DF30_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41DF30_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x368u, &fl);
        esp = r;
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    edi = (ebp + 0xffffffccu);
    esi = 0x4f9e78u;
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 2, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 1, 0, &eax, &ecx, &esi, &edi, &fl);
    esi = ((eax * 4u));
    edx = lift_load(&env, esi, 0x4f8554u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_41df7f;
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41dfee;
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_41e0b1;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e590u, eax, edx, ebx, ecx, 0, esp);
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
L_41df7f:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e440u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x533360u;
    edx = 0x4fc6b0u;
    eax = (ebp + 0xfffffd88u);
    ebx = lift_load(&env, esi, ebx + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x5333b0u;
    edx = 0x4fc6b0u;
    eax = (ebp + 0xfffffc84u);
    ebx = lift_load(&env, esi, ebx + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffc84u);
    eax = (ebp + 0xfffffd88u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_41dfd7;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f0a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41dfd7:
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x415330u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e590u, eax, edx, ebx, ecx, 0, esp);
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
L_41dfee:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e440u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x53ba88u;
    eax = eax + esi;
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
L_41dfff:
    edx = 0x12u;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = esi ^ esi;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, ebp + 0xffffffccu, 1)) & 0xffu);
    esi = (esi & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x6u, &fl);
    }
    if (!fl.zf)
        goto L_41e031;
    edx = ((esi * 4u));
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = edx + 0x53ba88u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41e031:
    ebx = 0x533360u;
    edx = 0x4fc6b0u;
    eax = (ebp + 0xfffffd88u);
    ebx = lift_load(&env, ebx, (esi * 4u) + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x5333b0u;
    edx = 0x4fc6b0u;
    eax = (ebp + 0xfffffc84u);
    ebx = lift_load(&env, ebx, (esi * 4u) + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffc84u);
    eax = (ebp + 0xfffffd88u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_41e086;
    edx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f0c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41e086:
    edx = edx ^ edx;
    eax = esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, ebp + 0xffffffccu, 1)) & 0xffu);
    ecx = ecx + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x415350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ecx, 0x7u, &fl);
    }
    if (fl.cf)
        goto L_41dfff;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f1e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e590u, eax, edx, ebx, ecx, 0, esp);
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
L_41e0b1:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e440u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x12u;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = 0x6u;
    eax = eax & 0xffffu;
    edx = 0x5u;
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    ebx = ebx ^ ebx;
    esi = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax ^ eax;
L_41e0de:
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.zf)
        goto L_41e100;
    ebx = ebx + 1u;
    ebx = ebx + 1u;
    lift_store(&env, ebp, (ebx * 4u) + 0xfffffe84u, 4, eax);
    lift_store(&env, ebp, (ebx * 4u) + 0xffffff24u, 4, edi);
    lift_store(&env, ebp, (ebx * 4u) + 0xfffffe88u, 4, eax);
    lift_store(&env, ebp, (ebx * 4u) + 0xffffff28u, 4, edx);
L_41e100:
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0x12u, &fl);
    }
    if (fl.cf)
        goto L_41e0de;
    edi = edi ^ edi;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_41e170;
    ecx = ecx ^ ecx;
L_41e10e:
    edx = edx ^ edx;
    eax = 0x598d30u;
    edx = (edx & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax & 0xffffu;
    ecx = ecx + 0x4u;
    edx = lift_load(&env, ebp, (eax * 4u) + 0xfffffe8cu, 4);
    esi = lift_load(&env, ecx, ebp + 0xfffffe88u, 4);
    lift_store(&env, ecx, ebp + 0xfffffe88u, 4, edx);
    edx = lift_load(&env, ebp, (eax * 4u) + 0xffffff2cu, 4);
    lift_store(&env, ebp, (eax * 4u) + 0xfffffe8cu, 4, esi);
    esi = lift_load(&env, ecx, ebp + 0xffffff28u, 4);
    lift_store(&env, ecx, ebp + 0xffffff28u, 4, edx);
    edi = edi + 1u;
    lift_store(&env, ebp, (eax * 4u) + 0xffffff2cu, 4, esi);
    {
        (void)lift_sub(32, edi, ebx, &fl);
    }
    if (fl.cf)
        goto L_41e10e;
L_41e170:
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = 0x53ba88u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = ecx ^ ecx;
    edx = edx + eax;
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
L_41e185:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, ebp + 0xffffffccu, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_41e23f;
    edx = 0x5u;
    edi = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
L_41e19d:
    {
        (void)lift_sub(8, lift_load(&env, ecx, ebp + 0xffffffccu, 1), 0x6u, &fl);
    }
    if (!fl.zf)
        goto L_41e1b9;
    edx = ((edi * 4u));
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = edx + 0x53ba88u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41e1b9:
    ebx = 0x533360u;
    edx = 0x4fc6b0u;
    eax = (ebp + 0xfffffd88u);
    ebx = lift_load(&env, ebx, (edi * 4u) + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x5333b0u;
    edx = 0x4fc6b0u;
    eax = (ebp + 0xfffffc84u);
    ebx = lift_load(&env, ebx, (edi * 4u) + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffc84u);
    eax = (ebp + 0xfffffd88u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_41e211;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41e211:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx ^ ebx;
    eax = edi;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, ebp + 0xffffffccu, 1)) & 0xffu);
    ecx = ecx + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4153e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ecx, 0x7u, &fl);
    }
    if (fl.cf)
        goto L_41e185;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f1e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e590u, eax, edx, ebx, ecx, 0, esp);
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
L_41e23f:
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x6u, &fl);
    }
    if (!fl.zf)
        goto L_41e254;
    eax = 0x6u;
    edi = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    goto L_41e19d;
L_41e254:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    edi = lift_load(&env, ebp, 0xffffffe4u, 4);
    esi = esi + 0x4u;
    eax = lift_load(&env, eax, ebp + 0xffffff2cu, 4);
    edi = lift_load(&env, edi, ebp + 0xfffffe8cu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    goto L_41e19d;
}

uint32_t lifted_f41e310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41E310_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41E310_STACK, 0, entry);
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
    esp = esp - 0x264u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (ebp + 0xffffffa8u);
    edx = 0x4ec1ecu;
    ecx = 0x5140a0u;
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
    eax = (ebp + 0xffffff90u);
    lift_store(&env, ebp, 0xffffffb0u, 4, ecx);
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffffacu, 4, edx);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489f90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = lift_load(&env, ecx, 0x53969cu, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, esi);
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_41e571;
    eax = edi;
    eax = eax - esi;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45ea60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    edi = edi ^ edi;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_41e462;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax - edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = 0x534f5cu;
    eax = eax + lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + 0x4u;
    lift_store(&env, ebp, 0xffffffc4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
L_41e3ab:
    eax = ((edi * 4u));
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    ecx = (eax + 0x4u);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = 0x50dd31u;
    eax = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_41e44d;
    eax = 0x534f5cu;
    eax = eax + lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = 0x4fc9c8u;
    ebx = lift_load(&env, ecx, eax + 0x0u, 4);
    eax = (ebp + 0xfffffe8cu);
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x53612cu;
    eax = eax + esi;
    edx = 0x4fc9c8u;
    ebx = lift_load(&env, ecx, eax + 0x0u, 4);
    eax = (ebp + 0xfffffd88u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffc4u, 4);
    edx = (ebp + 0xfffffd88u);
    eax = (ebp + 0xfffffe8cu);
    ebx = lift_load(&env, ebx, 0x5347f0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423dc0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_41e44d;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffd0u, 4);
    ebx = esi;
    ecx = lift_load(&env, eax, 0x5384d0u, 4);
    edx = edi;
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x537300u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e9e0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41e44d:
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffccu, 4);
    edx = edx + 0x4u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    {
        (void)lift_sub(32, edi, ecx, &fl);
    }
    if (fl.cf)
        goto L_41e3ab;
L_41e462:
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    eax = lift_load(&env, ebx, 0x534f10u, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_41e5b1;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = 0x544d7cu;
    ebx = ebx + 0x534920u;
    edx = edx + eax;
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
L_41e49e:
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = 0x4fd100u;
    eax = (ebp + 0xfffffe8cu);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffe8cu);
    eax = (ebp + 0xffffff90u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffff90u);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e950u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41e4d8:
    eax = (ebp + 0xffffff90u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (!fl.cf)
        goto L_41e58e;
    edx = (ebp + 0xffffffbcu);
    eax = (ebp + 0xffffff90u);
    ebx = esi;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a300u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 4, 0x2u);
    ebx = 0x1u;
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ebx;
    edi = eax;
    eax = (ebp + 0xffffffbcu);
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffc0u);
    eax = (ebp + 0xffffff90u);
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    ebx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a300u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 4, 0x4u);
    eax = lift_load(&env, eax, 0x0u, 4);
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    ecx = eax;
    eax = (ebp + 0xffffffc0u);
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e990u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffb4u, 4, edx);
    esi = esi + edx;
    goto L_41e4d8;
L_41e571:
    eax = (ebp + 0xffffff90u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489fa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
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
L_41e58e:
    eax = (ebp + 0xffffff90u);
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a2d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx + 0x4cu;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.cf)
        goto L_41e49e;
L_41e5b1:
    eax = eax ^ eax;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    eax = (ebp + 0xffffff90u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489fa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffb4u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
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

uint32_t lifted_f41e5e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41E5E0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41E5E0_STACK, 0, entry);
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
    esp = esp - 0x24cu;
    eax = (ebp + 0xffffffc0u);
    edx = 0x4ec1ecu;
    ecx = 0x5140c4u;
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
    eax = 0x54008cu;
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
    lift_store(&env, ebp, 0xffffffc8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
L_41e623:
    eax = (ebp + 0xffffffa8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489f90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = 0x1u;
    ecx = lift_load(&env, eax, 0x54021cu, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_41e754;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = ecx;
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi ^ edi;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_41e70d;
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        uint32_t r = lift_imul(32, edx, 0x14u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
L_41e66a:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = 0x50dd32u;
    eax = lift_load(&env, eax, 0x0u, 4);
    ecx = ((edi * 4u));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_41e6f8;
    eax = 0x54008cu;
    eax = eax + lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = 0x4fc9c8u;
    ebx = lift_load(&env, ecx, eax + 0x0u, 4);
    eax = (ebp + 0xfffffea4u);
    esi = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x5400f0u;
    ebx = ebx + esi;
    edx = 0x4fc9c8u;
    eax = (ebp + 0xfffffda0u);
    ebx = lift_load(&env, ecx, ebx + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffda0u);
    eax = (ebp + 0xfffffea4u);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423dc0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_41e6f8;
    ecx = ecx + lift_load(&env, ebp, 0xffffffd4u, 4);
    ebx = esi;
    edx = lift_load(&env, ecx, 0x5401b8u, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ecx, 0x540154u, 4);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e850u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41e6f8:
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    esi = esi + 0x4u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (fl.cf)
        goto L_41e66a;
L_41e70d:
    eax = (ebp + 0xffffffa8u);
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489fa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx + 0x4u;
    esi = esi + 0x14u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_41e623;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
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
L_41e754:
    eax = (ebp + 0xffffffa8u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489fa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
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

uint32_t lifted_f41f080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41F080_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41F080_STACK, 0, entry);
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
    esp = esp - 0x118u;
    ecx = eax;
    eax = (ebp + 0xffffffdcu);
    edx = 0x4ec1ecu;
    ebx = 0x514100u;
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
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x415d60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x415d90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41df30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    ebx = 0x5334a0u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c2cu, 1)) & 0xffu);
    edx = 0x4fc398u;
    ebx = lift_load(&env, ebx, (eax * 4u) + 0x0u, 4);
    eax = (ebp + 0xfffffed8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffed8u);
    eax = ecx;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a960u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f854cu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4191b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f770u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x46ea30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472bd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4760c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4765b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3bu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3cu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3du;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5fu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476120u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x60u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476120u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477d70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532a98u, 4);
    lift_store(&env, 0u, 0x532a4cu, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aa20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ab60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ab00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    edx = 0x423960u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aaa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x41f210u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
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

uint32_t lifted_f41f500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41F500_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41F500_STACK, 0, entry);
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
    esp = esp - 0x118u;
    ecx = eax;
    eax = (ebp + 0xffffffdcu);
    edx = 0x4ec1ecu;
    ebx = 0x514110u;
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
    eax = 0x13u;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41df30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c2cu, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x5334a0u;
    edx = 0x4fc398u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffed8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffed8u);
    eax = ecx;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a960u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f854cu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4191b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f770u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x54000cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x46eda0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472bd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4760c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4765b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3bu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3cu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3du;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5fu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476120u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x60u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476120u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477d70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532a98u, 4);
    lift_store(&env, 0u, 0x532a4cu, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aa20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ab60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ab00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    edx = 0x423960u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aaa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x41f680u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
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

uint32_t lifted_f420040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F420040_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F420040_STACK, 0, entry);
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
    esp = esp - 0x120u;
    ecx = eax;
    eax = (ebp + 0xffffffd0u);
    edx = 0x4ec1ecu;
    ebx = 0x514134u;
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
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    edx = lift_load(&env, 0u, 0x532a70u, 4);
    eax = (ebp + 0xffffffe4u);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    edx = edx + 0x5332c0u;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = 0x4fc290u;
    eax = (ebp + 0xfffffeccu);
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffeccu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4200d5;
    ebx = 0x5334a0u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c1au, 1)) & 0xffu);
    edx = 0x4fc398u;
    ebx = lift_load(&env, ebx, (eax * 4u) + 0x0u, 4);
    eax = (ebp + 0xfffffeccu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4200d5:
    edx = (ebp + 0xfffffeccu);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a960u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x532a70u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (ebp + 0xffffffe4u);
    edx = edx + 0x533310u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = 0x4fcff8u;
    eax = (ebp + 0xfffffeccu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x7b8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_420278;
L_42011e:
    edx = (ebp + 0xfffffeccu);
    lift_store(&env, 0u, 0x532928u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4122f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f770u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4760c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4765b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3du;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x2u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x6u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x7u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x8u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x9u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x2eu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x2fu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4871d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x532a70u, 4);
    ebx = 0x1u;
    eax = ecx;
    edx = lift_load(&env, 0u, (edx * 4u) + 0x533cd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4191b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aa20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    edx = 0x4202a0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aaa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe4u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
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
L_420278:
    edx = 0x2u;
    ebx = 0x1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    edx = 0x7au;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4120a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    goto L_42011e;
}

uint32_t lifted_f421ac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F421AC0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F421AC0_STACK, 0, entry);
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
    esp = esp - 0x11cu;
    ecx = eax;
    eax = (ebp + 0xffffffd4u);
    edx = 0x4ec1ecu;
    ebx = 0x5141c8u;
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
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    eax = ecx;
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ab90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ac20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a9e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f9f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4719e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edx = 0x50ddebu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45e670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x4fc080u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_421b65;
L_421b3a:
    edx = 0x421f10u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x41c6d0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
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
L_421b65:
    edx = lift_load(&env, 0u, 0x532a70u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (ebp + 0xffffffe8u);
    edx = edx + 0x534750u;
    edi = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = 0x4fcff8u;
    eax = (ebp + 0xfffffed0u);
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffed0u);
    eax = lift_load(&env, 0u, 0x532928u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x412240u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532928u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_421bbd;
    ebx = lift_load(&env, eax, 0x7b4u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_421bbd:
    eax = (ebp + 0xffffffe8u);
    edx = edx ^ edx;
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    goto L_421b3a;
}

uint32_t lifted_f421be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F421BE0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F421BE0_STACK, 0, entry);
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
    ecx = eax;
    eax = (ebp + 0xffffffd4u);
    edx = 0x4ec1ecu;
    ebx = 0x5141d4u;
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
    eax = (ebp + 0xffffffbcu);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489f90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x532a70u, 4);
    edi = 0x1u;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (ebp + 0xffffffe8u);
    edx = edx + 0x5332c0u;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x2u;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = 0x4fc290u;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = (ebp + 0xfffffeb8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffeb8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_421db6;
L_421c6c:
    edx = (ebp + 0xfffffeb8u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a960u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532a68u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41e310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f770u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4760c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4765b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3bu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3cu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3du;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3eu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3fu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x40u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x41u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x42u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x43u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x44u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4871d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x532a70u, 4);
    ebx = 0x1u;
    eax = ecx;
    edx = lift_load(&env, 0u, (edx * 4u) + 0x533cd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4191b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aa20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    edx = 0x421de0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aaa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
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
L_421db6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c1au, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x5334a0u;
    edx = 0x4fc398u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffeb8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_421c6c;
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

uint32_t lifted_f424230(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F424230_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F424230_STACK, 0, entry);
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
    esp = esp - 0x124u;
    ecx = eax;
    eax = (ebp + 0xffffffccu);
    edx = 0x4ec1ecu;
    ebx = 0x5143a0u;
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
    eax = (ebp + 0xffffffe0u);
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe4u);
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd8u, 4, 0x2u);
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532a70u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = 0x3u;
    eax = eax + 0x5332c0u;
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    edx = 0x4fc290u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffec8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffec8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_42432f;
L_4242c4:
    edx = (ebp + 0xfffffec8u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a960u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aa20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aaa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x532a70u, 4);
    ebx = 0x1u;
    eax = ecx;
    edx = lift_load(&env, 0u, (edx * 4u) + 0x533cd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4191b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4237d0u;
    eax = ecx;
    lift_store(&env, ecx, 0xc8u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x424360u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
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
L_42432f:
    ebx = 0x5334a0u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c1au, 1)) & 0xffu);
    edx = 0x4fc398u;
    ebx = lift_load(&env, ebx, (eax * 4u) + 0x0u, 4);
    eax = (ebp + 0xfffffec8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4242c4;
}

uint32_t lifted_piece_init_from_kind(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PIECE_INIT_FROM_KIND_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_PIECE_INIT_FROM_KIND_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (ebx & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    edx = lift_load(&env, 0u, (edx * 4u) + 0x4f8cecu, 4);
    lift_store(&env, eax, 0x15cu, 4, edx);
    {
        (void)lift_sub(32, edx, 0xcu, &fl);
    }
    if (fl.zf)
        goto L_425f41;
    {
        (void)lift_sub(32, edx, 0x7u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_425f48;
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_425f4f;
    edx = 0x2u;
L_425f18:
    lift_store(&env, eax, 0x160u, 4, edx);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    edx = lift_load(&env, 0u, (edx * 4u) + 0x4f8d38u, 4);
    lift_store(&env, eax, 0x180u, 4, 0xffffffffu);
    lift_store(&env, eax, 0x164u, 4, edx);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_425f41:
    edx = 0x4u;
    goto L_425f18;
L_425f48:
    edx = 0x3u;
    goto L_425f18;
L_425f4f:
    edx = 0x1u;
    goto L_425f18;
}

uint32_t lifted_object_compare_regions(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_COMPARE_REGIONS_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_COMPARE_REGIONS_STACK, 0,
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
    esp = esp - 0x94u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, edx, 0x3b0u, 4);
    ecx = 0x41u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    esi = lift_load(&env, esi, 0x15cu, 4);
    edx = lift_load(&env, eax, 0x15cu, 4);
    eax = esi;
    edi = (ebp + 0xffffff5cu);
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
    edi = (ebp + 0xffffffa0u);
    esi = (edx + 0x1deu);
    ebx = (ebp + 0xffffffa0u);
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
    esi = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = (ebp + 0xffffff5cu);
    esi = esi + 0x1c5u;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = esi;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x427c10u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = 0x4fb500u;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = esi;
    ebx = lift_load(&env, ebx, 0x160u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x428610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax & 0xffu;
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_427bf8;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427bff;
    eax = 0xffffffffu;
L_427bef:
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
L_427bf8:
    eax = 0x1u;
    goto L_427bef;
L_427bff:
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

uint32_t lifted_ai_compare_boards(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_AI_COMPARE_BOARDS_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_AI_COMPARE_BOARDS_STACK, 0, entry);
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
    esp = esp - 0x6cu;
    lift_store(&env, esp, 0x38u, 4, eax);
    lift_store(&env, esp, 0x54u, 4, edx);
    lift_store(&env, esp, 0x48u, 4, ebx);
    lift_store(&env, esp, 0x3cu, 4, ecx);
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    esi = esi ^ esi;
    eax = eax ^ eax;
    lift_store(&env, esp, 0x30u, 4, edx);
    lift_store(&env, esp, 0x5cu, 4, edx);
    lift_store(&env, esp, 0x60u, 4, edx);
    lift_store(&env, esp, 0x64u, 4, edx);
    lift_store(&env, esp, 0x2cu, 4, edx);
    edx = 0xdu;
L_428147:
    eax = eax + 0x4u;
    lift_store(&env, esp, eax + 0xfffffffcu, 4, edx);
    lift_store(&env, esp, eax + 0x10u, 4, edx);
    {
        (void)lift_sub(32, eax, 0x14u, &fl);
    }
    if (!fl.zf)
        goto L_428147;
    ebp = ebp ^ ebp;
    eax = lift_load(&env, esp, 0x54u, 4);
    lift_store(&env, esp, 0x44u, 4, ebp);
    lift_store(&env, esp, 0x40u, 4, ebp);
    lift_store(&env, esp, 0x58u, 4, eax);
    eax = lift_load(&env, esp, 0x48u, 4);
    lift_store(&env, esp, 0x28u, 4, ebp);
    lift_store(&env, esp, 0x34u, 4, eax);
L_428175:
    eax = lift_load(&env, esp, 0x58u, 4);
    edi = lift_load(&env, esp, 0x28u, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = edx ^ edx;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_428199;
L_428186:
    ebx = lift_load(&env, esp, edi + 0x0u, 4);
    eax = eax + 1u;
    ebx = ebx - 1u;
    edx = edx + 1u;
    lift_store(&env, esp, edi + 0x0u, 4, ebx);
    {
        (void)lift_sub(32, edx, 0xdu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_428199;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_428186;
L_428199:
    eax = lift_load(&env, esp, 0x34u, 4);
    edi = lift_load(&env, esp, 0x28u, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = edx ^ edx;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4281bf;
L_4281aa:
    ebp = lift_load(&env, esp, edi + 0x14u, 4);
    eax = eax + 1u;
    ebp = ebp - 1u;
    edx = edx + 1u;
    lift_store(&env, esp, edi + 0x14u, 4, ebp);
    {
        (void)lift_sub(32, edx, 0xdu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4281bf;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_4281aa;
L_4281bf:
    eax = lift_load(&env, esp, 0x28u, 4);
    {
        (void)lift_sub(32, lift_load(&env, esp, eax + 0x0u, 4), 0x6u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4281cd;
    lift_store(&env, esp, 0x40u, 4, lift_load(&env, esp, 0x40u, 4) + 1u);
L_4281cd:
    eax = lift_load(&env, esp, 0x28u, 4);
    {
        (void)lift_sub(32, lift_load(&env, esp, eax + 0x14u, 4), 0x6u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4281dc;
    lift_store(&env, esp, 0x44u, 4, lift_load(&env, esp, 0x44u, 4) + 1u);
L_4281dc:
    eax = lift_load(&env, esp, 0x58u, 4);
    edx = lift_load(&env, esp, 0x34u, 4);
    ebx = lift_load(&env, esp, 0x28u, 4);
    eax = eax + 0xdu;
    edx = edx + 0xdu;
    ebx = ebx + 0x4u;
    lift_store(&env, esp, 0x58u, 4, eax);
    lift_store(&env, esp, 0x34u, 4, edx);
    lift_store(&env, esp, 0x28u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x14u, &fl);
    }
    if (!fl.zf)
        goto L_428175;
    edx = lift_load(&env, esp, 0x54u, 4);
    edx = edx + 0xdu;
    lift_store(&env, esp, 0x50u, 4, edx);
    edx = lift_load(&env, esp, 0x48u, 4);
    eax = eax ^ eax;
    lift_store(&env, esp, 0x4cu, 4, edx);
L_42821b:
    {
        uint32_t r = lift_imul(32, eax, 0xdu, &fl);
        edx = r;
    }
    ebp = lift_load(&env, esp, 0x54u, 4);
    edi = lift_load(&env, esp, 0x4cu, 4);
    edx = edx + ebp;
    ebp = lift_load(&env, esp, 0x50u, 4);
L_42822c:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, edi, 0x0u, 1)) & 0xffu) << 8);
    lift_store(&env, esp, 0x68u, 1, ((ebx >> 8) & 0xffu));
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_42823d;
    lift_store(&env, esp, 0x64u, 4, lift_load(&env, esp, 0x64u, 4) + 1u);
L_42823d:
    {
        (void)lift_sub(8, lift_load(&env, esp, 0x68u, 1), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_428248;
    lift_store(&env, esp, 0x2cu, 4, lift_load(&env, esp, 0x2cu, 4) + 1u);
L_428248:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_428297;
    lift_store(&env, esp, 0x30u, 4, lift_load(&env, esp, 0x30u, 4) + 1u);
L_428251:
    {
        (void)lift_sub(8, lift_load(&env, esp, 0x68u, 1), 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_42825c;
    lift_store(&env, esp, 0x5cu, 4, lift_load(&env, esp, 0x5cu, 4) + 1u);
L_42825c:
    edx = edx + 1u;
    edi = edi + 1u;
    {
        (void)lift_sub(32, edx, ebp, &fl);
    }
    if (!fl.zf)
        goto L_42822c;
    edi = lift_load(&env, esp, 0x50u, 4);
    ebp = lift_load(&env, esp, 0x4cu, 4);
    eax = eax + 1u;
    edi = edi + 0xdu;
    ebp = ebp + 0xdu;
    lift_store(&env, esp, 0x50u, 4, edi);
    lift_store(&env, esp, 0x4cu, 4, ebp);
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_42821b;
    eax = 0x1u;
L_428283:
    {
        uint32_t r = lift_imul(32, eax, 0xdu, &fl);
        edx = r;
    }
    edx = edx + lift_load(&env, esp, 0x54u, 4);
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_4282c2;
L_42828f:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4282a2;
    eax = eax - 1u;
    esi = esi + 1u;
    goto L_42828f;
L_428297:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x6u, &fl);
    }
    if (!fl.zf)
        goto L_428251;
    lift_store(&env, esp, 0x60u, 4, lift_load(&env, esp, 0x60u, 4) + 1u);
    goto L_428251;
L_4282a2:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_428283;
    eax = 0x3u;
    edi = lift_load(&env, esp, 0x54u, 4);
L_4282af:
    {
        uint32_t r = lift_imul(32, eax, 0xdu, &fl);
        edx = r;
    }
    edx = edx + edi;
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_4282e5;
L_4282b9:
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4282c5;
    eax = eax + 1u;
    esi = esi + 1u;
    goto L_4282b9;
L_4282c2:
    eax = eax - 1u;
    goto L_4282a2;
L_4282c5:
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4282af;
    eax = 0x1u;
    ebp = lift_load(&env, esp, 0x48u, 4);
L_4282d3:
    {
        uint32_t r = lift_imul(32, eax, 0xdu, &fl);
        edx = r;
    }
    edx = edx + ebp;
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_42830a;
L_4282dd:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4282e8;
    eax = eax - 1u;
    ecx = ecx + 1u;
    goto L_4282dd;
L_4282e5:
    eax = eax + 1u;
    goto L_4282c5;
L_4282e8:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4282d3;
    eax = 0x3u;
L_4282f1:
    {
        uint32_t r = lift_imul(32, eax, 0xdu, &fl);
        edx = r;
    }
    edx = edx + lift_load(&env, esp, 0x48u, 4);
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_428429;
L_428301:
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_42830d;
    eax = eax + 1u;
    ecx = ecx + 1u;
    goto L_428301;
L_42830a:
    eax = eax - 1u;
    goto L_4282e8;
L_42830d:
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4282f1;
    edi = lift_load(&env, esp, 0x64u, 4);
    {
        (void)lift_sub(32, edi, 0xdu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_42842f;
    eax = eax ^ eax;
L_428321:
    ebx = lift_load(&env, esp, 0x2cu, 4);
    {
        (void)lift_sub(32, ebx, 0xdu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_428466;
    edx = edx ^ edx;
L_428330:
    edi = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    lift_store(&env, edi, 0x5u, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_42849d;
    ebx = (ebx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) - (edx & 0xffu)) & 0xffu);
    lift_store(&env, edi, 0xau, 1, (ebx & 0xffu));
L_428348:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4284a6;
    eax = 0x4u;
L_428355:
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4284e3;
    edx = 0x4u;
L_428362:
    ecx = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, ecx, 0x2u, 1, (eax & 0xffu));
    lift_store(&env, ecx, 0x7u, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_428520;
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - (edx & 0xffu)) & 0xffu);
    lift_store(&env, ecx, 0xcu, 1, (eax & 0xffu));
L_428379:
    ebp = lift_load(&env, esp, 0x30u, 4);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf)
        goto L_428529;
    eax = eax ^ eax;
L_428387:
    ebx = lift_load(&env, esp, 0x5cu, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_428560;
    edx = edx ^ edx;
L_428395:
    ecx = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, ecx, 0x3u, 1, (eax & 0xffu));
    lift_store(&env, ecx, 0x8u, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_428597;
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - (edx & 0xffu)) & 0xffu);
    lift_store(&env, ecx, 0xdu, 1, (eax & 0xffu));
L_4283ac:
    eax = lift_load(&env, esp, 0x60u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4285a0;
L_4283b8:
    ecx = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, ecx, 0x4u, 1, (eax & 0xffu));
    lift_store(&env, ecx, 0x9u, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4285c5;
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - (edx & 0xffu)) & 0xffu);
    lift_store(&env, ecx, 0xeu, 1, (eax & 0xffu));
L_4283cf:
    eax = lift_load(&env, esp, 0x54u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x1au, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4285ce;
    eax = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, eax, 0x10u, 1, 0x0u);
L_4283e5:
    eax = lift_load(&env, esp, 0x48u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x1au, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4285db;
    eax = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, eax, 0x11u, 1, 0x0u);
L_4283fb:
    eax = lift_load(&env, esp, 0x38u, 4);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, eax, 0x17cu, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((ecx >> 8) & 0xffu), ((ecx >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4285f7;
    eax = lift_load(&env, esp, 0x48u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0xdu, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4285e8;
    eax = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, eax, 0x12u, 1, ((ecx >> 8) & 0xffu));
    {
        uint32_t r = lift_add(32, esp, 0x6cu, &fl);
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
L_428429:
    eax = eax + 1u;
    goto L_42830d;
L_42842f:
    {
        (void)lift_sub(32, edi, 0x14u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_42843e;
    eax = 0x1u;
    goto L_428321;
L_42843e:
    {
        (void)lift_sub(32, edi, 0x1au, &fl);
    }
    if (fl.sf == fl.of)
        goto L_42844d;
    eax = 0x2u;
    goto L_428321;
L_42844d:
    {
        (void)lift_sub(32, edi, 0x27u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_42845c;
    eax = 0x3u;
    goto L_428321;
L_42845c:
    eax = 0x4u;
    goto L_428321;
L_428466:
    {
        (void)lift_sub(32, ebx, 0x14u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_428475;
    edx = 0x1u;
    goto L_428330;
L_428475:
    {
        (void)lift_sub(32, ebx, 0x1au, &fl);
    }
    if (fl.sf == fl.of)
        goto L_428484;
    edx = 0x2u;
    goto L_428330;
L_428484:
    {
        (void)lift_sub(32, ebx, 0x27u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_428493;
    edx = 0x3u;
    goto L_428330;
L_428493:
    edx = 0x4u;
    goto L_428330;
L_42849d:
    lift_store(&env, edi, 0xau, 1, 0x0u);
    goto L_428348;
L_4284a6:
    ebx = lift_load(&env, esp, 0x40u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4284b5;
    eax = eax ^ eax;
    goto L_428355;
L_4284b5:
    {
        (void)lift_sub(32, ebx, 0x3u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4284c4;
    eax = 0x1u;
    goto L_428355;
L_4284c4:
    {
        (void)lift_sub(32, ebx, 0x5u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4284d3;
    eax = 0x2u;
    goto L_428355;
L_4284d3:
    if (!fl.zf)
        goto L_428355;
    eax = 0x3u;
    goto L_428355;
L_4284e3:
    ecx = lift_load(&env, esp, 0x44u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4284f2;
    edx = edx ^ edx;
    goto L_428362;
L_4284f2:
    {
        (void)lift_sub(32, ecx, 0x3u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_428501;
    edx = 0x1u;
    goto L_428362;
L_428501:
    {
        (void)lift_sub(32, ecx, 0x5u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_428510;
    edx = 0x2u;
    goto L_428362;
L_428510:
    if (!fl.zf)
        goto L_428362;
    edx = 0x3u;
    goto L_428362;
L_428520:
    lift_store(&env, ecx, 0xcu, 1, 0x0u);
    goto L_428379;
L_428529:
    {
        (void)lift_sub(32, ebp, 0x7u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_428538;
    eax = 0x1u;
    goto L_428387;
L_428538:
    {
        (void)lift_sub(32, ebp, 0xfu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_428547;
    eax = 0x2u;
    goto L_428387;
L_428547:
    {
        (void)lift_sub(32, ebp, 0x14u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_428556;
    eax = 0x3u;
    goto L_428387;
L_428556:
    eax = 0x4u;
    goto L_428387;
L_428560:
    {
        (void)lift_sub(32, ebx, 0x7u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_42856f;
    edx = 0x1u;
    goto L_428395;
L_42856f:
    {
        (void)lift_sub(32, ebx, 0xfu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_42857e;
    edx = 0x2u;
    goto L_428395;
L_42857e:
    {
        (void)lift_sub(32, ebx, 0x14u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_42858d;
    edx = 0x3u;
    goto L_428395;
L_42858d:
    edx = 0x4u;
    goto L_428395;
L_428597:
    lift_store(&env, ecx, 0xdu, 1, 0x0u);
    goto L_4283ac;
L_4285a0:
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4283b8;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4283b8;
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4283b8;
    eax = 0x4u;
    goto L_4283b8;
L_4285c5:
    lift_store(&env, ecx, 0xeu, 1, 0x0u);
    goto L_4283cf;
L_4285ce:
    eax = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, eax, 0x10u, 1, 0x4u);
    goto L_4283e5;
L_4285db:
    eax = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, eax, 0x11u, 1, 0x4u);
    goto L_4283fb;
L_4285e8:
    eax = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, eax, 0x12u, 1, 0x4u);
    {
        uint32_t r = lift_add(32, esp, 0x6cu, &fl);
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
L_4285f7:
    eax = lift_load(&env, esp, 0x48u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x27u, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4285e8;
    eax = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, eax, 0x12u, 1, 0x0u);
    {
        uint32_t r = lift_add(32, esp, 0x6cu, &fl);
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

uint32_t lifted_ai_record_score(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_AI_RECORD_SCORE_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_AI_RECORD_SCORE_STACK, 0, entry);
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
    esp = esp - 0x34u;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    ebx = 0x6u;
    eax = (ebp + 0xffffffccu);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x6u;
    eax = (ebp + 0xffffffc4u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4286b6;
    edx = (ecx + 0x5u);
L_428660:
    esi = lift_load(&env, edx, 0x2u, 1);
    edi = lift_load(&env, edx, 0x4u, 1);
    eax = eax ^ eax;
    ebx = ebx ^ ebx;
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, 0x1u, 1)) & 0xffu);
    edi = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    ebx = ebx + edi;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x3u, 1)) & 0xffu);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.cf)
        goto L_4286a5;
    {
        (void)lift_sub(32, esi, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_42875a;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, eax, ebp + 0xffffffccu, 1)) & 0xffu) << 8);
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + (ebx & 0xffu)) & 0xffu) << 8);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, ebp + 0xffffffc4u, 1)) & 0xffu);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) + 1u) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffffccu, 1, ((ecx >> 8) & 0xffu));
    lift_store(&env, eax, ebp + 0xffffffc4u, 1, (ebx & 0xffu));
L_4286a5:
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = ecx + 1u;
    edx = edx + 0x5u;
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.cf)
        goto L_428660;
L_4286b6:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xfffffff0u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_428821;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffc4u, 1)) & 0xffu) << 8);
    esi = esi ^ esi;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4286d6;
L_4286c9:
    esi = esi + 1u;
    {
        (void)lift_sub(32, esi, 0x6u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4286d6;
    {
        (void)lift_sub(8, lift_load(&env, esi, ebp + 0xffffffc4u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4286c9;
L_4286d6:
    {
        (void)lift_sub(32, esi, 0x6u, &fl);
    }
    if (fl.zf)
        goto L_428833;
    ecx = esi;
    if (fl.sf == fl.of)
        goto L_428705;
L_4286e3:
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, ebp + 0xffffffc4u, 1)) & 0xffu);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4286ff;
    edx = lift_load(&env, ecx, ebp + 0xffffffc9u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    lift_store(&env, ecx, ebp + 0xffffffccu, 1, (eax & 0xffu));
L_4286ff:
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, ecx, 0x6u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4286e3;
L_428705:
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        (void)lift_sub(32, edi, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_428842;
    ebx = ebx ^ ebx;
    eax = esi;
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    {
        (void)lift_sub(32, esi, 0x6u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_42873f;
L_42871d:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, ebp + 0xffffffc4u, 1)) & 0xffu);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_428739;
    edx = lift_load(&env, eax, ebp + 0xffffffc9u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = edx + edx;
    esi = esi + edx;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
L_428739:
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0x6u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_42871d;
L_42873f:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_428750;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
L_428750:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
L_42875a:
    {
        (void)lift_sub(32, esi, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_428778;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, eax, ebp + 0xffffffccu, 1)) & 0xffu) << 8);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, ebp + 0xffffffc4u, 1)) & 0xffu);
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) - (ebx & 0xffu)) & 0xffu) << 8);
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) + 1u) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffffccu, 1, ((ebx >> 8) & 0xffu));
    lift_store(&env, eax, ebp + 0xffffffc4u, 1, (ecx & 0xffu));
    goto L_4286a5;
L_428778:
    {
        (void)lift_sub(32, esi, 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_428799;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, eax, ebp + 0xffffffccu, 1)) & 0xffu) << 8);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, eax, ebp + 0xffffffc4u, 1)) & 0xffu) << 8);
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) + 0x4u) & 0xffu) << 8);
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + 1u) & 0xffu) << 8);
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) - (ebx & 0xffu)) & 0xffu) << 8);
    lift_store(&env, eax, ebp + 0xffffffc4u, 1, ((ecx >> 8) & 0xffu));
    lift_store(&env, eax, ebp + 0xffffffccu, 1, ((ebx >> 8) & 0xffu));
    goto L_4286a5;
L_428799:
    {
        (void)lift_sub(32, esi, 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_4287ba;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, eax, ebp + 0xffffffccu, 1)) & 0xffu) << 8);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, ebp + 0xffffffc4u, 1)) & 0xffu);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) + ((ebx >> 8) & 0xffu)) & 0xffu);
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) + 1u) & 0xffu);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) - 0x4u) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffffc4u, 1, (ecx & 0xffu));
    lift_store(&env, eax, ebp + 0xffffffccu, 1, (ebx & 0xffu));
    goto L_4286a5;
L_4287ba:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4287ee;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4286a5;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xfffffff0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4287dd;
    ebx = 0x1u;
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    goto L_4286a5;
L_4287dd:
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xfffffff4u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4286a5;
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    goto L_4286a5;
L_4287ee:
    {
        (void)lift_sub(32, esi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4286a5;
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4286a5;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xfffffff0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_428810;
    lift_store(&env, ebp, 0xfffffff0u, 4, esi);
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    goto L_4286a5;
L_428810:
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xfffffff4u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4286a5;
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    goto L_4286a5;
L_428821:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
L_428833:
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
L_428842:
    edx = (esi + 0x1u);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_428883;
    eax = lift_load(&env, esi, ebp + 0xffffffc9u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x6u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_428871;
L_42885a:
    edx = lift_load(&env, eax, ebp + 0xffffffc9u, 4);
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_42886b;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
L_42886b:
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0x6u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_42885a;
L_428871:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
L_428883:
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_428750;
    eax = lift_load(&env, esi, ebp + 0xffffffc9u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x6u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4288b1;
L_42889d:
    edx = lift_load(&env, eax, ebp + 0xffffffc9u, 4);
    edi = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4288c3;
L_4288ab:
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0x6u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_42889d;
L_4288b1:
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t r = lift_add(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
L_4288c3:
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    goto L_4288ab;
}

uint32_t lifted_settings_defaults(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_SETTINGS_DEFAULTS_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_SETTINGS_DEFAULTS_STACK, 0, entry);
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
    edx = eax;
    lift_store(&env, eax, 0x228u, 4, 0x514554u);
    lift_store(&env, eax, 0x0u, 4, 0x2u);
    lift_store(&env, eax, 0x4u, 4, 0x14u);
    lift_store(&env, eax, 0x8u, 4, 0x1u);
    lift_store(&env, eax, 0xcu, 4, 0x5u);
    lift_store(&env, eax, 0x10u, 4, 0x0u);
    lift_store(&env, eax, 0x14u, 4, 0x1u);
    lift_store(&env, eax, 0x18u, 4, 0xc8u);
    lift_store(&env, eax, 0x1cu, 2, 0x5fu);
    lift_store(&env, eax, 0x1eu, 2, 0x60u);
    lift_store(&env, eax, 0x20u, 2, 0x5du);
    lift_store(&env, eax, 0x22u, 2, 0x62u);
    lift_store(&env, eax, 0x24u, 2, 0x72u);
    lift_store(&env, eax, 0x26u, 2, 0x73u);
    lift_store(&env, eax, 0x28u, 2, 0x74u);
    lift_store(&env, eax, 0x2au, 2, 0x75u);
    lift_store(&env, eax, 0x2cu, 2, 0x39u);
    lift_store(&env, eax, 0x30u, 4, 0x30u);
    lift_store(&env, eax, 0x34u, 4, 0x40u);
    eax = lift_load(&env, 0u, 0x532c98u, 4);
    lift_store(&env, edx, 0x38u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f8300u, 4);
    lift_store(&env, edx, 0x3cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f8370u, 4);
    lift_store(&env, edx, 0x40u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f81d0u, 4);
    ecx = lift_load(&env, edx, 0x30u, 4);
    lift_store(&env, edx, 0x44u, 4, eax);
    eax = ((ecx * 4u));
    eax = eax - ecx;
    esi = 0x50e095u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    lift_store(&env, edx, 0x48u, 4, 0x0u);
    eax = eax + ecx;
    lift_store(&env, edx, 0x4cu, 4, 0x0u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, edx, 0x50u, 4, 0x0u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, edx, 0x34u, 4);
    lift_store(&env, edx, 0x54u, 4, eax);
    eax = ((ecx * 4u));
    lift_store(&env, edx, 0x5cu, 4, 0x186a0u);
    eax = eax - ecx;
    lift_store(&env, edx, 0x60u, 4, 0x186a0u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    lift_store(&env, edx, 0x64u, 4, 0xc350u);
    eax = eax + ecx;
    lift_store(&env, edx, 0x68u, 4, 0x2710u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, edx, 0x6cu, 4, 0x1388u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        eax = r;
    }
    edi = (edx + 0x70u);
    lift_store(&env, edx, 0x58u, 4, eax);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4291d9:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4291f1;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4291d9;
L_4291f1:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    esi = 0x50e099u;
    edi = (edx + 0x74u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4291fb:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_429213;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4291fb;
L_429213:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    esi = 0x50e09du;
    edi = (edx + 0x78u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_42921d:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_429235;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_42921d;
L_429235:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    esi = 0x50e0a0u;
    edi = (edx + 0x7cu);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_42923f:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_429257;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_42923f;
L_429257:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    esi = 0x50e0a4u;
    edi = (edx + 0x80u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_429264:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_42927c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_429264;
L_42927c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    lift_store(&env, edx, 0x84u, 4, 0x1u);
    lift_store(&env, edx, 0x88u, 4, 0x5u);
    lift_store(&env, edx, 0x8cu, 4, 0x0u);
    esi = 0x50e0a8u;
    lift_store(&env, edx, 0x90u, 4, 0x1u);
    edi = (edx + 0x98u);
    lift_store(&env, edx, 0x94u, 4, 0x0u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4292bb:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4292d3;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4292bb;
L_4292d3:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    esi = 0x50e0adu;
    edi = (edx + 0xfcu);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4292e0:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4292f8;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4292e0;
L_4292f8:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    esi = 0x50e0b4u;
    edi = (edx + 0x160u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_429305:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_42931d;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_429305;
L_42931d:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    esi = 0x50e0c4u;
    edi = (edx + 0x1c4u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_42932a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_429342;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_42932a;
L_429342:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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

uint32_t lifted_f42a540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F42A540_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_F42A540_STACK, 4, entry);
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
    eax = 0x514688u;
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    esi = esi ^ esi;
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    lift_store(&env, edi, 0x16u, 2, (eax & 0xffffu));
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    eax = eax + 0x77u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    eax = eax + 0x137u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = 0x160u;
    lift_store(&env, edi, 0xeu, 2, (ecx & 0xffffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_42a7ca;
L_42a5a8:
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
    eax = lift_load(&env, ebp, 0xcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x415470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xau;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    edx = edx + 1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = 0x544ac0u;
    edx = edx + eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    lift_store(&env, esi, 0xa8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, esi, 0xaau, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, esi, 0xacu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, esi, 0xaeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xcu, 1)) & 0xffu);
    lift_store(&env, esi, 0x15cu, 1, (eax & 0xffu));
    eax = 0x160u;
    lift_store(&env, edi, 0x15cu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_42a668;
    ebx = 0x3u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42bb00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
L_42a668:
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
    eax = lift_load(&env, ebp, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x415470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xau;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    edx = edx + 1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0x10u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = 0x544ac0u;
    edx = edx + eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    lift_store(&env, esi, 0xa8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, esi, 0xaau, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, esi, 0xacu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, esi, 0xaeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0x10u, 1)) & 0xffu);
    lift_store(&env, esi, 0x15cu, 1, (eax & 0xffu));
    eax = 0x160u;
    lift_store(&env, edi, 0x160u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_42a7e4;
L_42a719:
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
    eax = lift_load(&env, ebp, 0x14u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x415470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xau;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    edx = edx + 1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = 0x544ac0u;
    edx = edx + eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    lift_store(&env, esi, 0xa8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, esi, 0xaau, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, esi, 0xacu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, esi, 0xaeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0x14u, 1)) & 0xffu);
    lift_store(&env, esi, 0x15cu, 1, (eax & 0xffu));
    lift_store(&env, edi, 0x164u, 4, esi);
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
L_42a7ca:
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42bb00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    esi = eax;
    goto L_42a5a8;
L_42a7e4:
    edx = 0x5u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42bb00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    goto L_42a719;
}

uint32_t lifted_piece_actor_construct_placed(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PIECE_ACTOR_CONSTRUCT_PLACED_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    (void)esp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_PIECE_ACTOR_CONSTRUCT_PLACED_STACK, 0,
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
    esp = esp - 0x28u;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x425e00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f90acu, 2)) & 0xffffu);
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t r = lift_imul(32, esi, edi, &fl);
        esi = r;
    }
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_42aed6;
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f89f0u, 2)) & 0xffffu);
    lift_store(&env, edx, 0xeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f89f4u, 2)) & 0xffffu);
    eax = eax - esi;
    lift_store(&env, edx, 0x16u, 2, (eax & 0xffffu));
    eax = lift_load(&env, edx, 0xcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = lift_load(&env, 0u, 0x4f89f8u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = eax + edx;
    eax = eax - 1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f89f4u, 4);
    esi = lift_load(&env, 0u, 0x4f89fcu, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = eax + esi;
L_42ad58:
    eax = eax - 1u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    esi = lift_load(&env, 0u, 0x532bbcu, 4);
    eax = ((esi * 4u));
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = eax + esi;
    edx = lift_load(&env, ecx, (eax * 8u) + 0x4f7d50u, 4);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x532bbcu, 4);
    eax = ((esi * 4u));
    eax = eax + esi;
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, (eax * 8u) + 0x4f7dc8u, 2)) & 0xffffu);
    lift_store(&env, edx, 0x1au, 2, (eax & 0xffffu));
    edx = 0x12cu;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, edx, 0x8eu, 1, 0x3u);
    lift_store(&env, edx, 0xa8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, edx, 0xaau, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    ecx = ecx ^ ecx;
    lift_store(&env, edx, 0xacu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    lift_store(&env, edx, 0xaeu, 2, (eax & 0xffffu));
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_42aec3;
    eax = (esi + 0xffffffffu);
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    edi = edx;
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
L_42adf5:
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_42af19;
L_42ae0f:
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
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x544bd8u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    lift_store(&env, esi, 0xa8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, esi, 0xaau, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, esi, 0xacu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, esi, 0xaeu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, edi, 0x15cu, 4, esi);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_42af23;
    edx = 0x44c2b0u;
L_42ae9e:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = lift_load(&env, ebp, 0xfffffff4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    edi = edi + 0x4u;
    eax = eax + 0x4u;
    edx = edx + 1u;
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    lift_store(&env, ebp, 0xfffffff4u, 4, edx);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.cf)
        goto L_42adf5;
L_42aec3:
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, edx, 0x188u, 4, eax);
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
L_42aed6:
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f89e8u, 2)) & 0xffffu);
    lift_store(&env, edx, 0xeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f89ecu, 2)) & 0xffffu);
    eax = eax - esi;
    lift_store(&env, edx, 0x16u, 2, (eax & 0xffffu));
    eax = lift_load(&env, edx, 0xcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edi = lift_load(&env, 0u, 0x4f89f8u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = eax + edi;
    eax = eax - 1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f89ecu, 4);
    edx = lift_load(&env, 0u, 0x4f89fcu, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = eax + edx;
    goto L_42ad58;
L_42af19:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_42ae0f;
L_42af23:
    edx = 0x44c2a0u;
    goto L_42ae9e;
}
