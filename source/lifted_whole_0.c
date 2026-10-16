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
