/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_21.h"

uint32_t lifted_mixer_playback_tick(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_MIXER_PLAYBACK_TICK_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_MIXER_PLAYBACK_TICK_STACK, 0, entry);
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
    ebx = lift_load(&env, eax, 0x34u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_40e05b;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40e05b;
    eax = lift_load(&env, ecx, 0x7cu, 4);
    edx = lift_load(&env, ecx, 0x78u, 4);
    edx = edx - eax;
    lift_store(&env, ecx, 0x78u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40e29e;
L_40e057:
    lift_store(&env, ecx, 0x1u, 1, lift_load(&env, ecx, 0x1u, 1) | 0x2u);
L_40e05b:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_40e3c3;
    {
        (void)lift_and(8, lift_load(&env, ebx, 0xbcu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_40e3c3;
    eax = (ebx + 0x88u);
    edx = lift_load(&env, ecx, 0x88u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, (edx * 4u) + 0x0u, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    esi = lift_load(&env, ecx, 0x80u, 4);
    esi = esi + 1u;
    lift_store(&env, ecx, 0x80u, 4, esi);
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_40e38b;
    {
        (void)lift_and(8, lift_load(&env, ebx, 0xbcu, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_40e2b1;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0xb9u, 1)) & 0xffu);
    esi = lift_load(&env, ecx, 0x88u, 4);
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (!fl.zf)
        goto L_40e2b1;
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40e2b1;
    edx = esi;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, (edx * 4u) + 0x0u, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    lift_store(&env, ecx, 0x80u, 4, edx);
    edx = lift_load(&env, ecx, 0x88u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, (edx * 4u) + 0x2u, 2)) & 0xffffu);
    eax = eax & 0xffffu;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
L_40e0ec:
    lift_store(&env, ecx, 0x84u, 4, eax);
L_40e0f2:
    eax = lift_load(&env, ecx, 0x84u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, ecx, 0x14u, 4), &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, ecx, 0x78u, 4), &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x15u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x18u, 4, eax);
    lift_store(&env, ecx, 0x1u, 1, lift_load(&env, ecx, 0x1u, 1) | 0x2u);
L_40e10d:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_40e4ff;
    {
        (void)lift_and(8, lift_load(&env, ebx, 0xf4u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_40e4ff;
    eax = (ebx + 0xc0u);
    edx = lift_load(&env, ecx, 0x98u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, (edx * 4u) + 0x0u, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    edi = lift_load(&env, ecx, 0x90u, 4);
    edi = edi + 1u;
    lift_store(&env, ecx, 0x90u, 4, edi);
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_40e4c0;
    {
        (void)lift_and(8, lift_load(&env, ebx, 0xf4u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_40e3e6;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0xf1u, 1)) & 0xffu);
    ebp = lift_load(&env, ecx, 0x98u, 4);
    {
        (void)lift_sub(32, edx, ebp, &fl);
    }
    if (!fl.zf)
        goto L_40e3e6;
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40e3e6;
    edx = ebp;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, (edx * 4u) + 0x0u, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    lift_store(&env, ecx, 0x90u, 4, edx);
    edx = lift_load(&env, ecx, 0x98u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, (edx * 4u) + 0x2u, 2)) & 0xffffu);
    eax = eax & 0xffffu;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
L_40e19e:
    lift_store(&env, ecx, 0x94u, 4, eax);
L_40e1a4:
    eax = lift_load(&env, ecx, 0x1cu, 4);
    eax = eax - 0x80u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40e4f8;
L_40e1b4:
    edx = 0x80u;
    edx = edx - eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    eax = lift_load(&env, ecx, 0x94u, 4);
    eax = eax - 0x2000u;
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_load(&env, ecx, 0x1cu, 4);
    eax = eax + edx;
    lift_store(&env, ecx, 0x20u, 4, eax);
    lift_store(&env, ecx, 0x1u, 1, lift_load(&env, ecx, 0x1u, 1) | 0x4u);
L_40e1db:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_40e56d;
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x84u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40e56d;
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40e22e;
    ebp = lift_load(&env, ecx, 0xa8u, 4);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_40e22e;
    eax = ebp;
    edx = lift_load(&env, ecx, 0xa4u, 4);
    edx = edx + ebp;
    lift_store(&env, ecx, 0xa4u, 4, edx);
    eax = eax ^ ebp;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x84u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_40e22e;
    lift_store(&env, ecx, 0xa4u, 4, eax);
    lift_store(&env, ecx, 0xa8u, 4, 0x0u);
L_40e22e:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x85u, 1)) & 0xffu);
    lift_store(&env, ecx, 0xa0u, 4, lift_load(&env, ecx, 0xa0u, 4) + eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0xa0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0x82u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x3u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_40e548;
    edx = edx & 0xffu;
    {
        uint32_t i = edx;
        switch (i)
        {
            case 0:
                goto L_40e260;
            case 1:
                goto L_40e50a;
            case 2:
                goto L_40e522;
            case 3:
                goto L_40e532;
            default:
                return 0u;
        }
    }
L_40e260:
    eax = lift_load(&env, eax, 0x4f7341u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
L_40e269:
    edx = ((eax * 4u));
    {
        uint32_t r = lift_imul(32, edx, lift_load(&env, ecx, 0xa4u, 4), &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_load(&env, ecx, 0x28u, 4);
    eax = eax + edx;
    lift_store(&env, ecx, 0x2cu, 4, eax);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_40e54f;
    eax = 0x1u;
L_40e290:
    lift_store(&env, ecx, 0x2cu, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0x1u, 1), 0x1u, &fl);
        lift_store(&env, ecx, 0x1u, 1, r);
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
L_40e29e:
    lift_store(&env, ecx, 0x7cu, 4, 0x0u);
    lift_store(&env, ecx, 0x78u, 4, 0x0u);
    goto L_40e057;
L_40e2b1:
    {
        (void)lift_and(8, lift_load(&env, ebx, 0xbcu, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_40e2da;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0xbbu, 1)) & 0xffu);
    edi = lift_load(&env, ecx, 0x88u, 4);
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (!fl.zf)
        goto L_40e2da;
    edx = edx ^ edi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0xbau, 1)) & 0xffu);
    lift_store(&env, ecx, 0x88u, 4, edx);
L_40e2da:
    edx = lift_load(&env, ecx, 0x88u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, (edx * 4u) + 0x0u, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    lift_store(&env, ecx, 0x80u, 4, edx);
    edx = lift_load(&env, ecx, 0x88u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, (edx * 4u) + 0x2u, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    lift_store(&env, ecx, 0x84u, 4, edx);
    esi = lift_load(&env, ecx, 0x88u, 4);
    esi = esi + 1u;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0xb8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40e32c;
    lift_store(&env, ecx, 0x8cu, 4, 0x0u);
    goto L_40e0f2;
L_40e32c:
    edx = lift_load(&env, ecx, 0x88u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = eax + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    esi = esi ^ esi;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = edx - esi;
    esi = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40e376;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x6u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x2u, 2)) & 0xffffu);
    eax = eax & 0xffffu;
    edx = edx - eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, esi, &eax, &edx, &fl);
    lift_store(&env, ecx, 0x8cu, 4, eax);
    lift_store(&env, ecx, 0x88u, 4, lift_load(&env, ecx, 0x88u, 4) + 1u);
    goto L_40e0f2;
L_40e376:
    lift_store(&env, ecx, 0x8cu, 4, 0x0u);
    lift_store(&env, ecx, 0x88u, 4, lift_load(&env, ecx, 0x88u, 4) + 1u);
    goto L_40e0f2;
L_40e38b:
    eax = lift_load(&env, ecx, 0x8cu, 4);
    ebp = lift_load(&env, ecx, 0x84u, 4);
    ebp = ebp + eax;
    lift_store(&env, ecx, 0x84u, 4, ebp);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40e3b5;
    {
        (void)lift_sub(32, ebp, 0x4000u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40e3bc;
    eax = 0x4000u;
    goto L_40e0ec;
L_40e3b5:
    eax = eax ^ eax;
    goto L_40e0ec;
L_40e3bc:
    eax = ebp;
    goto L_40e0ec;
L_40e3c3:
    eax = lift_load(&env, ecx, 0x14u, 4);
    lift_store(&env, ecx, 0x18u, 4, eax);
    edi = lift_load(&env, ecx, 0x78u, 4);
    {
        (void)lift_sub(32, edi, 0x7fffu, &fl);
    }
    if (fl.zf)
        goto L_40e10d;
    {
        uint32_t r = lift_imul(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0xfu, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x18u, 4, eax);
    goto L_40e10d;
L_40e3e6:
    {
        (void)lift_and(8, lift_load(&env, ebx, 0xf4u, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_40e40f;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0xf3u, 1)) & 0xffu);
    esi = lift_load(&env, ecx, 0x98u, 4);
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (!fl.zf)
        goto L_40e40f;
    edx = edx ^ esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0xf2u, 1)) & 0xffu);
    lift_store(&env, ecx, 0x98u, 4, edx);
L_40e40f:
    edx = lift_load(&env, ecx, 0x98u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, (edx * 4u) + 0x0u, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    lift_store(&env, ecx, 0x90u, 4, edx);
    edx = lift_load(&env, ecx, 0x98u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, (edx * 4u) + 0x2u, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    lift_store(&env, ecx, 0x94u, 4, edx);
    esi = lift_load(&env, ecx, 0x98u, 4);
    esi = esi + 1u;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0xf0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40e461;
    lift_store(&env, ecx, 0x9cu, 4, 0x0u);
    goto L_40e1a4;
L_40e461:
    edx = lift_load(&env, ecx, 0x98u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = eax + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    esi = esi ^ esi;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = edx - esi;
    esi = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40e4ab;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x6u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x2u, 2)) & 0xffffu);
    eax = eax & 0xffffu;
    edx = edx - eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, esi, &eax, &edx, &fl);
    lift_store(&env, ecx, 0x9cu, 4, eax);
    lift_store(&env, ecx, 0x98u, 4, lift_load(&env, ecx, 0x98u, 4) + 1u);
    goto L_40e1a4;
L_40e4ab:
    lift_store(&env, ecx, 0x9cu, 4, 0x0u);
    lift_store(&env, ecx, 0x98u, 4, lift_load(&env, ecx, 0x98u, 4) + 1u);
    goto L_40e1a4;
L_40e4c0:
    eax = lift_load(&env, ecx, 0x9cu, 4);
    edx = lift_load(&env, ecx, 0x94u, 4);
    edx = edx + eax;
    lift_store(&env, ecx, 0x94u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40e4ea;
    {
        (void)lift_sub(32, edx, 0x4000u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40e4f1;
    eax = 0x4000u;
    goto L_40e19e;
L_40e4ea:
    eax = eax ^ eax;
    goto L_40e19e;
L_40e4f1:
    eax = edx;
    goto L_40e19e;
L_40e4f8:
    eax = 0u - eax;
    goto L_40e1b4;
L_40e4ff:
    eax = lift_load(&env, ecx, 0x1cu, 4);
    lift_store(&env, ecx, 0x20u, 4, eax);
    goto L_40e1db;
L_40e50a:
    {
        (void)lift_and(8, (eax & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_40e518;
    eax = 0x40u;
    goto L_40e269;
L_40e518:
    eax = 0xffffffc0u;
    goto L_40e269;
L_40e522:
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
    }
    eax = eax + 0x40u;
    eax = eax & 0x7fu;
    eax = eax - 0x40u;
    goto L_40e269;
L_40e532:
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = 0x40u;
    edx = edx - eax;
    eax = edx;
    eax = eax & 0x7fu;
    eax = eax - 0x40u;
    goto L_40e269;
L_40e548:
    eax = eax ^ eax;
    goto L_40e269;
L_40e54f:
    {
        (void)lift_sub(32, eax, 0x7cffu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40e290;
    eax = 0x7cffu;
    lift_store(&env, ecx, 0x2cu, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0x1u, 1), 0x1u, &fl);
        lift_store(&env, ecx, 0x1u, 1, r);
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
L_40e56d:
    eax = lift_load(&env, ecx, 0x28u, 4);
    lift_store(&env, ecx, 0x2cu, 4, eax);
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
