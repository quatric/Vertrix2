/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_43.h"

uint32_t lifted_mixer_set_effect_40d490(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_MIXER_SET_EFFECT_40D490_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_MIXER_SET_EFFECT_40D490_STACK, 0,
               entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x531b4cu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_40d4b7;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x4u, 1)) & 0xffu);
    lift_store(&env, eax, 0x10u, 4, edx);
    {
        (void)lift_sub(32, edx, 0x40u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40d4ad;
    lift_store(&env, eax, 0x10u, 4, 0x40u);
L_40d4ad:
    edx = lift_load(&env, eax, 0x10u, 4);
    lift_store(&env, eax, 0x14u, 4, edx);
    {
        uint32_t r = lift_or(8, lift_load(&env, eax, 0x1u, 1), 0x2u, &fl);
        lift_store(&env, eax, 0x1u, 1, r);
    }
L_40d4b7:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_sequence_extended_effect(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_SEQUENCE_EXTENDED_EFFECT_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_SEQUENCE_EXTENDED_EFFECT_STACK, 0,
               entry);
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
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x4u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0xfu, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_40d55a;
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_40d55a;
            case 1:
                goto L_40d55f;
            case 2:
                goto L_40d5a4;
            case 3:
                goto L_40d5ec;
            case 4:
                goto L_40d606;
            case 5:
                goto L_40d62d;
            case 6:
                goto L_40d66a;
            case 7:
                goto L_40d6e0;
            case 8:
                goto L_40d70a;
            case 9:
                goto L_40d730;
            case 10:
                goto L_40d76d;
            case 11:
                goto L_40d7a7;
            case 12:
                goto L_40d7ec;
            case 13:
                goto L_40d818;
            case 14:
                goto L_40d842;
            case 15:
                goto L_40d55a;
            default:
                return 0u;
        }
    }
L_40d55a:
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
L_40d55f:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x531b4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0x4u, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0xfu, &fl);
    }
    if (!fl.zf)
        goto L_40d598;
L_40d570:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x6au, 1)) & 0xffu);
    edx = lift_load(&env, ecx, 0x24u, 4);
    edx = edx - eax;
    lift_store(&env, ecx, 0x24u, 4, edx);
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_40d589;
    lift_store(&env, ecx, 0x24u, 4, 0x1u);
L_40d589:
    eax = lift_load(&env, ecx, 0x24u, 4);
    lift_store(&env, ecx, 0x28u, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0x1u, 1), 0x1u, &fl);
        lift_store(&env, ecx, 0x1u, 1, r);
    }
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
L_40d598:
    eax = (eax & 0xffffff00u) | ((((eax >> 8) & 0xffu)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_shl(8, a, 0x2u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, ecx, 0x6au, 1, (eax & 0xffu));
    goto L_40d570;
L_40d5a4:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x531b4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, ecx, 0x4u, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((ebx >> 8) & 0xffu), 0xfu, &fl);
    }
    if (!fl.zf)
        goto L_40d5e0;
L_40d5b5:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x6bu, 1)) & 0xffu);
    ebx = lift_load(&env, ecx, 0x24u, 4);
    ebx = ebx + eax;
    lift_store(&env, ecx, 0x24u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x7cffu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40d5d1;
    lift_store(&env, ecx, 0x24u, 4, 0x7cffu);
L_40d5d1:
    eax = lift_load(&env, ecx, 0x24u, 4);
    lift_store(&env, ecx, 0x28u, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0x1u, 1), 0x1u, &fl);
        lift_store(&env, ecx, 0x1u, 1, r);
    }
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
L_40d5e0:
    eax = (eax & 0xffffff00u) | ((((ebx >> 8) & 0xffu)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_shl(8, a, 0x2u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, ecx, 0x6bu, 1, (eax & 0xffu));
    goto L_40d5b5;
L_40d5ec:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x531b4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x4u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (eax & 0xffu), 0xfu, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, ecx, 0x3du, 1, (eax & 0xffu));
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
L_40d606:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x531b4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ecx, 0x3cu, 1)) & 0xffu) << 8);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0xf0u) & 0xffu) << 8);
    lift_store(&env, ecx, 0x3cu, 1, ((edx >> 8) & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x4u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    ebx = (ebx & 0xffffff00u) | ((((edx >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_or(8, (ebx & 0xffu), (eax & 0xffu), &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, ecx, 0x3cu, 1, (ebx & 0xffu));
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
L_40d62d:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x531b4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x4u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    eax = eax & 0xffu;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax - 0x80u;
    lift_store(&env, ecx, 0x8u, 4, eax);
    ebx = eax;
    edx = lift_load(&env, ecx, 0xcu, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x7u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ce80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x28u, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0x1u, 1), 0x1u, &fl);
        lift_store(&env, ecx, 0x1u, 1, r);
    }
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
L_40d66a:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x531b4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x4u, 1), 0xfu, &fl);
    }
    if (fl.zf)
        goto L_40d6d0;
    eax = lift_load(&env, ecx, 0xb0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_40d6c5;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x4u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, ecx, 0xb0u, 4, eax);
L_40d697:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0xb0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40d55a;
    eax = lift_load(&env, ecx, 0xacu, 4);
    lift_store(&env, 0u, 0x531b74u, 4, eax);
    eax = lift_load(&env, 0u, 0x531b5cu, 4);
    lift_store(&env, 0u, 0x531b70u, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, 0u, 0x531b44u, 1), 0x1u, &fl);
        lift_store(&env, 0u, 0x531b44u, 1, r);
    }
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
L_40d6c5:
    edx = (eax + 0xffffffffu);
    lift_store(&env, ecx, 0xb0u, 4, edx);
    goto L_40d697;
L_40d6d0:
    eax = lift_load(&env, 0u, 0x531b50u, 4);
    lift_store(&env, ecx, 0xacu, 4, eax);
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
L_40d6e0:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x531b4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x3cu, 1)) & 0xffu);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) & 0xfu) & 0xffu);
    lift_store(&env, ecx, 0x3cu, 1, (ebx & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x4u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_shl(8, a, 0x4u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    ebx = (ebx & 0xffff00ffu) | ((((ebx & 0xffu)) & 0xffu) << 8);
    {
        uint32_t r = lift_or(8, ((ebx >> 8) & 0xffu), (eax & 0xffu), &fl);
        ebx = (ebx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    lift_store(&env, ecx, 0x3cu, 1, ((ebx >> 8) & 0xffu));
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
L_40d70a:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x531b4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x4u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    eax = eax & 0xffu;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x1cu, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0x1u, 1), 0x4u, &fl);
        lift_store(&env, ecx, 0x1u, 1, r);
    }
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
L_40d730:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x531b4cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40d761;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x4u, 1)) & 0xffu);
    {
        (void)lift_and(8, (edx & 0xffu), 0xfu, &fl);
    }
    if (fl.zf)
        goto L_40d55a;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = lift_load(&env, 0u, 0x531b4cu, 4);
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
L_40d761:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40e670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_40d76d:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x531b4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x4u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    eax = eax & 0xffu;
    edi = lift_load(&env, ecx, 0x10u, 4);
    edi = edi + eax;
    lift_store(&env, ecx, 0x10u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x40u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40d798;
    lift_store(&env, ecx, 0x10u, 4, 0x40u);
L_40d798:
    eax = lift_load(&env, ecx, 0x10u, 4);
    lift_store(&env, ecx, 0x14u, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0x1u, 1), 0x2u, &fl);
        lift_store(&env, ecx, 0x1u, 1, r);
    }
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
L_40d7a7:
    edi = lift_load(&env, 0u, 0x531b4cu, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x4u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    eax = eax & 0xffu;
    edx = lift_load(&env, ecx, 0x10u, 4);
    edx = edx - eax;
    lift_store(&env, ecx, 0x10u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40d7da;
    eax = lift_load(&env, ecx, 0x10u, 4);
    lift_store(&env, ecx, 0x14u, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0x1u, 1), 0x2u, &fl);
        lift_store(&env, ecx, 0x1u, 1, r);
    }
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
L_40d7da:
    lift_store(&env, ecx, 0x10u, 4, edi);
    eax = lift_load(&env, ecx, 0x10u, 4);
    lift_store(&env, ecx, 0x14u, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0x1u, 1), 0x2u, &fl);
        lift_store(&env, ecx, 0x1u, 1, r);
    }
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
L_40d7ec:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x4u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    eax = eax & 0xffu;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x531b4cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    lift_store(&env, ecx, 0x14u, 4, 0x0u);
    eax = lift_load(&env, ecx, 0x14u, 4);
    lift_store(&env, ecx, 0x10u, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0x1u, 1), 0x2u, &fl);
        lift_store(&env, ecx, 0x1u, 1, r);
    }
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
L_40d818:
    lift_store(&env, ecx, 0x1u, 1, lift_load(&env, ecx, 0x1u, 1) & 0x10u);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x4u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    eax = eax & 0xffu;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x531b4cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40e670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0x1u, 1), 0x6u, &fl);
        lift_store(&env, ecx, 0x1u, 1, r);
    }
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
L_40d842:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x531b4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x531b44u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_40d55a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x4u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    eax = eax & 0xffu;
    eax = eax + 1u;
    lift_store(&env, 0u, 0x531b78u, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, 0u, 0x531b44u, 1), 0x4u, &fl);
        lift_store(&env, 0u, 0x531b44u, 1, r);
    }
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

uint32_t lifted_mixer_global_effect(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_MIXER_GLOBAL_EFFECT_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_MIXER_GLOBAL_EFFECT_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x531b4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40d897;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x4u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x20u, &fl);
    }
    if (!fl.cf)
        goto L_40d899;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (!fl.cf)
        goto L_40d8ae;
L_40d897:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_40d899:
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, 0u, 0x531b64u, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, 0u, 0x531b44u, 1), 0x8u, &fl);
        lift_store(&env, 0u, 0x531b44u, 1, r);
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_40d8ae:
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x531b60u, 4, eax);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}
