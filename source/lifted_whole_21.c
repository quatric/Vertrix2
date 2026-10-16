/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_21.h"

uint32_t lifted_window_tables(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_WINDOW_TABLES_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_WINDOW_TABLES_STACK, 0, entry);
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
    esp = esp - 0x28u;
    lift_store(&env, esp, 0x18u, 4, eax);
    edx = edx ^ edx;
    lift_store(&env, esp, 0x14u, 4, edx);
    lift_store(&env, esp, 0xcu, 4, edx);
L_40a5a7:
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x14u, 1)) & 0xffu);
    eax = 0x10u;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x20u, 4, eax);
    eax = 0x40u;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x1cu, 4, eax);
    eax = lift_load(&env, esp, 0xcu, 4);
    eax = lift_load(&env, eax, 0x4f5f90u, 4);
    esi = esi ^ esi;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x20u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_40a666;
    lift_store(&env, esp, 0x24u, 4, eax);
L_40a5dc:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x40000000u;
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
    ebx = 0x54442d18u;
    ecx = 0x400921fbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    ebx = edx;
    eax = lift_load(&env, esp, 0x1cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    ebp = edx;
    eax = ecx;
    edx = ebx;
    ebx = edi;
    ecx = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9dd6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x40000000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    eax = eax ^ eax;
    edx = 0x3ff00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esp, 0x24u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    edi = (edx + 0x4u);
    lift_store(&env, esp, 0x24u, 4, edi);
    esi = esi + 1u;
    {
        (void)lift_sub(32, esi, lift_load(&env, esp, 0x20u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_40a5dc;
L_40a666:
    lift_store(&env, esp, 0xcu, 4, lift_load(&env, esp, 0xcu, 4) + 0x4u);
    edx = lift_load(&env, esp, 0x14u, 4);
    edx = edx + 1u;
    lift_store(&env, esp, 0x14u, 4, edx);
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40a5a7;
    edi = 0x52e784u;
    lift_store(&env, esp, 0x18u, 4, 0u - lift_load(&env, esp, 0x18u, 4));
    esi = esi ^ esi;
    ebp = ebp ^ ebp;
    lift_store(&env, esp, 0x10u, 4, esi);
L_40a68e:
    {
        (void)lift_sub(32, edi, 0x52efc4u, &fl);
    }
    if (fl.cf)
        goto L_40a741;
L_40a69a:
    eax = esi;
    edx = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    ecx = 0x20u;
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    {
        (void)lift_sub(32, edx, 0x1fu, &fl);
    }
    if (!fl.zf)
        goto L_40a6b3;
    edi = edi - 0xffcu;
L_40a6b3:
    eax = esi;
    edx = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    ecx = 0x40u;
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    {
        (void)lift_sub(32, edx, 0x3fu, &fl);
    }
    if (!fl.zf)
        goto L_40a6ca;
    lift_store(&env, esp, 0x18u, 4, 0u - lift_load(&env, esp, 0x18u, 4));
L_40a6ca:
    esi = esi + 1u;
    lift_store(&env, esp, 0x10u, 4, lift_load(&env, esp, 0x10u, 4) + 0x4u);
    ebp = ebp + 1u;
    edi = edi + 0x80u;
    {
        (void)lift_sub(32, esi, 0x100u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_40a68e;
    eax = ((ebp * 4u));
    lift_store(&env, esp, 0x8u, 4, eax);
L_40a6ea:
    {
        (void)lift_sub(32, esi, 0x200u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_40a7f1;
    {
        (void)lift_sub(32, edi, 0x52efc4u, &fl);
    }
    if (fl.cf)
        goto L_40a78d;
L_40a702:
    eax = esi;
    edx = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    ecx = 0x20u;
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    {
        (void)lift_sub(32, edx, 0x1fu, &fl);
    }
    if (!fl.zf)
        goto L_40a71b;
    edi = edi - 0xffcu;
L_40a71b:
    eax = esi;
    edx = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    ecx = 0x40u;
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    {
        (void)lift_sub(32, edx, 0x3fu, &fl);
    }
    if (fl.zf)
        goto L_40a7db;
    esi = esi + 1u;
    lift_store(&env, esp, 0x8u, 4, lift_load(&env, esp, 0x8u, 4) - 0x4u);
    ebp = ebp - 1u;
    edi = edi + 0x80u;
    goto L_40a6ea;
L_40a741:
    eax = lift_load(&env, esp, 0x10u, 4);
    eax = lift_load(&env, eax, 0x4f5fa4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x3ef00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x4u, 4, eax);
    ecx = edx;
    eax = lift_load(&env, esp, 0x18u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    lift_store(&env, esp, 0x0u, 4, edx);
    eax = lift_load(&env, esp, 0x4u, 4);
    edx = ecx;
    ecx = lift_load(&env, esp, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x0u, 4, eax);
    lift_store(&env, edi, 0x40u, 4, eax);
    goto L_40a69a;
L_40a78d:
    eax = lift_load(&env, esp, 0x8u, 4);
    eax = lift_load(&env, eax, 0x4f5fa4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    ecx = 0x3ef00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    ebx = edx;
    eax = lift_load(&env, esp, 0x18u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6768u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x0u, 4, eax);
    lift_store(&env, esp, 0x4u, 4, edx);
    eax = ecx;
    edx = ebx;
    ebx = lift_load(&env, esp, 0x0u, 4);
    ecx = lift_load(&env, esp, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x0u, 4, eax);
    lift_store(&env, edi, 0x40u, 4, eax);
    goto L_40a702;
L_40a7db:
    lift_store(&env, esp, 0x18u, 4, 0u - lift_load(&env, esp, 0x18u, 4));
    esi = esi + 1u;
    lift_store(&env, esp, 0x8u, 4, lift_load(&env, esp, 0x8u, 4) - 0x4u);
    ebp = ebp - 1u;
    edi = edi + 0x80u;
    goto L_40a6ea;
L_40a7f1:
    {
        uint32_t r = lift_add(32, esp, 0x28u, &fl);
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

uint32_t lifted_f41cc30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41CC30_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41CC30_STACK, 0, entry);
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
    esi = eax;
    eax = (ebp + 0xffffffd4u);
    edx = 0x4ec1ecu;
    ecx = 0x514058u;
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
    edi = lift_load(&env, 0u, 0x532a84u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41cf2f;
L_41cc76:
    edx = lift_load(&env, 0u, 0x532a80u, 4);
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41cf5f;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a7cu, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41d00c;
L_41cc92:
    eax = lift_load(&env, 0u, 0x532a68u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41e310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532a68u, 4);
    edi = lift_load(&env, 0u, 0x532a6cu, 4);
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.zf)
        goto L_41ccb2;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41e310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41ccb2:
    edx = lift_load(&env, 0u, 0x532a70u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (ebp + 0xffffffe8u);
    edx = edx + 0x5332c0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = 0x4fc290u;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = (ebp + 0xfffffed0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffed0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_41cd10;
    ebx = 0x5334a0u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c1au, 1)) & 0xffu);
    edx = 0x4fc398u;
    ebx = lift_load(&env, ebx, (eax * 4u) + 0x0u, 4);
    eax = (ebp + 0xfffffed0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41cd10:
    edx = (ebp + 0xfffffed0u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a960u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532a70u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41df30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x532a70u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (ebp + 0xffffffe8u);
    edx = edx + 0x53ba88u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = 0x4fcad0u;
    eax = (ebp + 0xfffffed0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffed0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_41cd80;
    eax = (ebp + 0xfffffed0u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x423ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_41cd80;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f020u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41cd80:
    ebx = 0x1u;
    edx = lift_load(&env, 0u, 0x4f852cu, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4191b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f770u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x532b40u, 4);
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_41cda9;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41cda9:
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4760f0u, eax, edx, ebx, ecx, 0, esp);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477d70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x46a9c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    eax = lift_load(&env, eax, 0x268u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4719f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4719e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x50u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, 0u, 0x4f880cu, 4);
    ebx = lift_load(&env, 0u, 0x4f8804u, 4);
    eax = lift_load(&env, 0u, 0x544070u, 4);
    edx = lift_load(&env, 0u, 0x4f8800u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, eax, 0x268u, 4);
    ecx = lift_load(&env, 0u, 0x4f8808u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47a040u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        uint32_t v = 0x50u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x4f881cu, 4);
    ecx = lift_load(&env, 0u, 0x4f8818u, 4);
    eax = lift_load(&env, 0u, 0x544070u, 4);
    edx = lift_load(&env, 0u, 0x4f8810u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, eax, 0x268u, 4);
    ebx = lift_load(&env, 0u, 0x4f8814u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47a040u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        uint32_t v = 0x50u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, 0u, 0x4f8864u, 4);
    ecx = lift_load(&env, 0u, 0x4f8860u, 4);
    ebx = lift_load(&env, 0u, 0x4f885cu, 4);
    eax = lift_load(&env, 0u, 0x544070u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8858u, 4);
    eax = lift_load(&env, eax, 0x268u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47a040u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    edx = edx ^ edx;
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x469480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532a98u, 4);
    lift_store(&env, 0u, 0x532a54u, 4, eax);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aa20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ab00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    edx = 0x3u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aaa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_and(32, eax, 0xffffu, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_41d0ac;
    edx = 0x4223d0u;
    eax = esi;
    lift_store(&env, esi, 0xc8u, 1, 0x1u);
L_41cef7:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41cefc:
    edx = 0x41d0e0u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
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
L_41cf2f:
    eax = lift_load(&env, 0u, 0x5bb490u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c7cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x5bb440u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d6c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb454u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d6c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb468u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d6c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_41cc76;
L_41cf5f:
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_41cc92;
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5bb4a8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x3u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1cf8u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_41cfcc;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41cfdf;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_41cc92;
    edx = lift_load(&env, 0u, 0x5bb494u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c7cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = 0x41c6d0u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
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
L_41cfcc:
    ebx = lift_load(&env, 0u, 0x5bb47cu, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c7cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    goto L_41cc92;
L_41cfdf:
    ecx = lift_load(&env, 0u, 0x5bb488u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c7cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = 0x41c6d0u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
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
L_41d00c:
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5bb4b4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x3u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1cf8u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_41d048;
    eax = lift_load(&env, 0u, 0x5bb484u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c7cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_41d039:
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_41cc92;
L_41d048:
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41d07f;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_41d039;
    ebx = lift_load(&env, 0u, 0x5bb494u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c7cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = 0x41b5e0u;
    eax = esi;
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
L_41d07f:
    edi = lift_load(&env, 0u, 0x5bb488u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c7cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = 0x41b5e0u;
    eax = esi;
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
L_41d0ac:
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41d0cd;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_41cefc;
    edx = 0x422f50u;
    eax = esi;
    lift_store(&env, esi, 0xc8u, 1, 0x4u);
    goto L_41cef7;
L_41d0cd:
    edx = 0x423bc0u;
    eax = esi;
    goto L_41cef7;
}

uint32_t lifted_f41e780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41E780_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41E780_STACK, 0, entry);
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
    esi = eax;
    eax = (ebp + 0xffffffccu);
    edx = 0x4ec1ecu;
    ecx = 0x5140d0u;
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
    edi = lift_load(&env, 0u, 0x532a84u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41ea34;
L_41e7c6:
    edx = lift_load(&env, 0u, 0x532a70u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (ebp + 0xffffffe0u);
    edx = edx + 0x5332c0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = (ebp + 0xfffffec8u);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    edx = 0x4fc290u;
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
    if (!fl.zf)
        goto L_41e82a;
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c1au, 1)) & 0xffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    ebx = ebx + 0x5334a0u;
    edx = 0x4fc398u;
    eax = (ebp + 0xfffffec8u);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41e82a:
    edx = (ebp + 0xfffffec8u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a960u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, 0u, 0x532a90u, 4);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_41ea46;
    edi = ecx;
L_41e848:
    eax = lift_load(&env, 0u, 0x532a84u, 4);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_41eaa0;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x532a7cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_41ea78;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf)
        goto L_41ea65;
L_41e86a:
    eax = lift_load(&env, 0u, 0x4f8520u, 4);
L_41e86f:
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
L_41e872:
    ebx = 0x1u;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4191b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f770u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, 0u, 0x532b40u, 4);
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_41e898;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_41e898:
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476090u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4760f0u, eax, edx, ebx, ecx, 0, esp);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477d70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edi;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x46a9c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    eax = lift_load(&env, eax, 0x268u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4719f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4719e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x50u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f880cu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f8800u, 4);
    ecx = lift_load(&env, 0u, 0x4f8808u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, 0u, 0x544070u, 4);
    ebx = lift_load(&env, 0u, 0x4f8804u, 4);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0x268u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47a040u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        uint32_t v = 0x50u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f881cu, 4);
    ecx = lift_load(&env, 0u, 0x4f8818u, 4);
    eax = lift_load(&env, 0u, 0x4f8814u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, 0u, 0x544070u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, 0u, 0x4f8810u, 4);
    eax = lift_load(&env, eax, 0x268u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47a040u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        uint32_t v = 0x50u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, 0u, 0x4f8864u, 4);
    eax = lift_load(&env, 0u, 0x4f885cu, 4);
    edx = lift_load(&env, 0u, 0x4f8858u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, 0u, 0x544070u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ecx = lift_load(&env, 0u, 0x4f8860u, 4);
    eax = lift_load(&env, eax, 0x268u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47a040u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    eax = 0x1u;
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x469480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532a98u, 4);
    lift_store(&env, 0u, 0x532a54u, 4, eax);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aa20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ab00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    edx = 0x422c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aaa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    lift_store(&env, esi, 0xc8u, 1, 0x4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x41eab0u;
    eax = esi;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe0u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
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
L_41ea34:
    eax = lift_load(&env, 0u, 0x5bb490u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c7cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    goto L_41e7c6;
L_41ea46:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a94u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_41ea59;
    edi = 0x2u;
    goto L_41e848;
L_41ea59:
    eax = lift_load(&env, 0u, 0x4f851cu, 4);
    edi = edi ^ edi;
    goto L_41e86f;
L_41ea65:
    {
        (void)lift_sub(32, edi, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_41e872;
    eax = lift_load(&env, 0u, 0x4f8524u, 4);
    goto L_41e86f;
L_41ea78:
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x532a80u, 4), &fl);
    }
    if (!fl.zf)
        goto L_41e872;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf)
        goto L_41ea92;
    eax = lift_load(&env, 0u, 0x4f8524u, 4);
    goto L_41e86f;
L_41ea92:
    {
        (void)lift_sub(32, edi, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_41e872;
    goto L_41e86a;
L_41eaa0:
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_41ea92;
    eax = lift_load(&env, 0u, 0x4f8524u, 4);
    goto L_41e86f;
}

uint32_t lifted_ai_fallback(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_AI_FALLBACK_STACK + 4 + 4 * 6 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_AI_FALLBACK_STACK, 6, entry);
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
    esp = esp - 0x90u;
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    ebx = 0x5u;
    eax = (ebp + 0xffffffbcu);
    esi = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = edx ^ edx;
    ecx = 0x41u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x5u;
    eax = (ebp + 0xffffffacu);
    edx = edx ^ edx;
    edi = (ebp + 0xffffff68u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x5u;
    eax = (ebp + 0xffffffb4u);
    edx = edx ^ edx;
    esi = esi + 0x184u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
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
    edx = lift_load(&env, ebp, 0x18u, 4);
    ecx = lift_load(&env, ebp, 0x14u, 4);
    ebx = (ebp + 0xffffffc4u);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edi = edi ^ edi;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffff68u);
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4261b0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ecx = ecx ^ ecx;
    ebx = (ebx & 0xffffff00u) | ((0xffu) & 0xffu);
L_4262c8:
    eax = (eax & 0xffff00ffu) | (((0xdu) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, ebp + 0xffffffc4u, 1)) & 0xffu);
    lift_store(&env, ecx, ebp + 0xffffffbcu, 1, ((eax >> 8) & 0xffu));
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_426325;
    eax = esi;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, esi, ebp + 0xffffff68u, 1)) & 0xffu) << 8);
    edx = edx ^ edx;
    {
        (void)lift_sub(8, (ebx & 0xffu), ((ebx >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4262ff;
L_4262e5:
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, ecx, ebp + 0xffffffbcu, 1)) & 0xffu) << 8);
    eax = eax + 1u;
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) + (ebx & 0xffu)) & 0xffu) << 8);
    edx = edx + 1u;
    lift_store(&env, ecx, ebp + 0xffffffbcu, 1, ((ebx >> 8) & 0xffu));
    {
        (void)lift_sub(32, edx, 0xdu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4262ff;
    {
        (void)lift_sub(8, (ebx & 0xffu), lift_load(&env, eax, ebp + 0xffffff68u, 1), &fl);
    }
    if (fl.zf)
        goto L_4262e5;
L_4262ff:
    eax = eax ^ eax;
    edx = 0xdu;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, ebp + 0xffffffbcu, 1)) & 0xffu);
    edx = edx - eax;
    eax = edx;
    {
        (void)lift_sub(32, ecx, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4267c0;
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4267c0;
    lift_store(&env, ecx, ebp + 0xffffffbcu, 1, 0xdu);
L_426325:
    ecx = ecx + 1u;
    esi = esi + 0xdu;
    {
        (void)lift_sub(32, ecx, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4262c8;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4267d1;
    eax = lift_load(&env, ebp, 0xcu, 4);
    lift_store(&env, eax, 0x0u, 4, 0x2u);
L_42633f:
    ebx = lift_load(&env, ebp, 0x1cu, 4);
    eax = 0xffffffffu;
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_42636d;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (fl.zf)
        goto L_4268ab;
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf)
        goto L_4268bb;
    {
        (void)lift_sub(32, edi, edx, &fl);
    }
    if (fl.zf)
        goto L_4268ce;
L_42636d:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4267a9;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x1cu, 4), 0x2u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4267a9;
    edx = lift_load(&env, ebp, 0xcu, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    ecx = ecx ^ ecx;
    ebx = 0xcu;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffffbcu, 1)) & 0xffu);
    ebx = ebx - ecx;
    esi = edx;
    ecx = ebx;
    {
        (void)lift_sub(32, ebx, 0x2u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4267a9;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4268e1;
    ebx = (ebx & 0xffffff00u) | ((0xfeu) & 0xffu);
    lift_store(&env, ebp, 0xffffffe4u, 1, (ebx & 0xffu));
    lift_store(&env, ebp, 0xfffffff0u, 1, (ebx & 0xffu));
    edx = (edx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (ebx & 0xffu));
    lift_store(&env, ebp, 0xffffffe8u, 1, (ebx & 0xffu));
L_4263b7:
    {
        (void)lift_sub(32, esi, 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_426955;
    ecx = (ecx & 0xffffff00u) | ((0xfeu) & 0xffu);
    ebx = (ebx & 0xffff00ffu) | ((((ecx & 0xffu)) & 0xffu) << 8);
    edx = (edx & 0xffff00ffu) | ((((ecx & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffecu, 1, (ecx & 0xffu));
    ebx = (ebx & 0xffffff00u) | (((ecx & 0xffu)) & 0xffu);
L_4263cb:
    esi = lift_load(&env, ebp, 0xfffffff1u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, esi, 0xffffffffu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4263fe;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4263fe;
    esi = lift_load(&env, ebp, 0xfffffff1u, 4);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf)
        goto L_4268ab;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268bb;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ce;
L_4263fe:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426506;
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)(ebx & 0xffu);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426434;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xfffffff4u, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_426434;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)(ebx & 0xffu);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf)
        goto L_4268ab;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268bb;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ce;
L_426434:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426506;
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)(edx & 0xffu);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426469;
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_426469;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)(edx & 0xffu);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf)
        goto L_4268ce;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ab;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268bb;
L_426469:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426506;
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)((edx >> 8) & 0xffu);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_42649e;
    {
        (void)lift_sub(8, (edx & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_42649e;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)((edx >> 8) & 0xffu);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf)
        goto L_4268ce;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ab;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268bb;
L_42649e:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426506;
    esi = lift_load(&env, ebp, 0xffffffedu, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4264d5;
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4264d5;
    esi = lift_load(&env, ebp, 0xffffffedu, 4);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf)
        goto L_4268bb;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ce;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ab;
L_4264d5:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426506;
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)((edx >> 8) & 0xffu);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426506;
    {
        (void)lift_sub(8, (edx & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_426506;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)((ebx >> 8) & 0xffu);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf)
        goto L_4268bb;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ce;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ab;
L_426506:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426654;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x1cu, 4), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_426654;
    esi = lift_load(&env, ebp, 0xffffffe5u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_42654b;
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_42654b;
    esi = lift_load(&env, ebp, 0xffffffe5u, 4);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf)
        goto L_4268ab;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268bb;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ce;
L_42654b:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426654;
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)((edx >> 8) & 0xffu);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426581;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xffffffe8u, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_426581;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)((edx >> 8) & 0xffu);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf)
        goto L_4268ab;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268bb;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ce;
L_426581:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426654;
    esi = lift_load(&env, ebp, 0xfffffff1u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4265bc;
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4265bc;
    esi = lift_load(&env, ebp, 0xfffffff1u, 4);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf)
        goto L_4268ce;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ab;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268bb;
L_4265bc:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426654;
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)((ebx >> 8) & 0xffu);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4265f2;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xfffffff4u, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4265f2;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)((ebx >> 8) & 0xffu);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf)
        goto L_4268ce;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ab;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268bb;
L_4265f2:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426654;
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)(edx & 0xffu);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426623;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_426623;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)(edx & 0xffu);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf)
        goto L_4268bb;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ce;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ab;
L_426623:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426654;
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)(ecx & 0xffu);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426654;
    {
        (void)lift_sub(8, (edx & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_426654;
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = (uint32_t)(int32_t)(int8_t)(uint8_t)(ecx & 0xffu);
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.zf)
        goto L_4268bb;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ce;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ab;
L_426654:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4267a9;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x1cu, 4), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4267a9;
    ecx = lift_load(&env, ebp, 0xffffffe9u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ecx = r;
    }
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426699;
    {
        (void)lift_sub(8, (edx & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_426699;
    ecx = lift_load(&env, ebp, 0xffffffe9u, 4);
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ecx = r;
    }
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.zf)
        goto L_4268ab;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268bb;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ce;
L_426699:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4267a9;
    ecx = (uint32_t)(int32_t)(int8_t)(uint8_t)(edx & 0xffu);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4266cf;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xffffffecu, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4266cf;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = (uint32_t)(int32_t)(int8_t)(uint8_t)(edx & 0xffu);
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (fl.zf)
        goto L_4268ab;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268bb;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ce;
L_4266cf:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4267a9;
    ecx = (uint32_t)(int32_t)(int8_t)(uint8_t)(ebx & 0xffu);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426705;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xfffffff0u, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_426705;
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = (uint32_t)(int32_t)(int8_t)(uint8_t)(ebx & 0xffu);
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.zf)
        goto L_4268ce;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ab;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268bb;
L_426705:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4267a9;
    ecx = lift_load(&env, ebp, 0xffffffedu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ecx = r;
    }
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426740;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_426740;
    ecx = lift_load(&env, ebp, 0xffffffedu, 4);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ecx = r;
    }
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (fl.zf)
        goto L_4268ce;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ab;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268bb;
L_426740:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4267a9;
    ecx = (uint32_t)(int32_t)(int8_t)(uint8_t)((edx >> 8) & 0xffu);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426772;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xffffffe4u, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_426772;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = (uint32_t)(int32_t)(int8_t)(uint8_t)((edx >> 8) & 0xffu);
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (fl.zf)
        goto L_4268bb;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ce;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ab;
L_426772:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4267a9;
    ecx = lift_load(&env, ebp, 0xffffffe1u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ecx = r;
    }
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4267a9;
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4267a9;
    edx = lift_load(&env, ebp, 0xffffffe1u, 4);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (fl.zf)
        goto L_4268bb;
    {
        (void)lift_sub(32, edx, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ce;
    {
        (void)lift_sub(32, edx, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4268ab;
L_4267a9:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4269be;
    edx = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
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
L_4267c0:
    {
        (void)lift_sub(8, lift_load(&env, ecx, ebp + 0xffffffbcu, 1), 0xdu, &fl);
    }
    if (fl.zf)
        goto L_426325;
    edi = edi + 1u;
    goto L_426325;
L_4267d1:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffbcu, 1)) & 0xffu);
    eax = eax ^ eax;
    {
        (void)lift_sub(8, (edx & 0xffu), 0xdu, &fl);
    }
    if (!fl.zf)
        goto L_4267e8;
L_4267db:
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4267e8;
    {
        (void)lift_sub(8, lift_load(&env, eax, ebp + 0xffffffbcu, 1), 0xdu, &fl);
    }
    if (fl.zf)
        goto L_4267db;
L_4267e8:
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_426855;
    ecx = 0x2u;
    edi = 0xcu;
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
L_4267fe:
    ebx = 0xffffffffu;
    ecx = 0x4u;
    esi = esi ^ esi;
L_42680a:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, ebp + 0xffffffbcu, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (!fl.zf)
        goto L_426816;
    ebx = esi;
L_426816:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, ebp + 0xffffffbcu, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (!fl.zf)
        goto L_426827;
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_42687c;
L_426825:
    ebx = ecx;
L_426827:
    ecx = ecx - 1u;
    esi = esi + 1u;
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426833;
    {
        (void)lift_sub(32, esi, 0x2u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_42680a;
L_426833:
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426842;
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        (void)lift_sub(32, ecx, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_426842;
    ebx = ecx;
L_426842:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x180u, 4, ebx);
    eax = lift_load(&env, ebp, 0xcu, 4);
    lift_store(&env, eax, 0x0u, 4, ebx);
    goto L_42633f;
L_426855:
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = eax + 1u;
    edi = lift_load(&env, eax, ebp + 0xffffffbbu, 1);
L_42685e:
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4267fe;
    {
        (void)lift_sub(8, lift_load(&env, eax, ebp + 0xffffffc4u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_426879;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, ebp + 0xffffffbcu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_426879;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    edi = edx;
L_426879:
    eax = eax + 1u;
    goto L_42685e;
L_42687c:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = lift_load(&env, eax, 0x180u, 4);
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.zf)
        goto L_42688d;
    ebx = edx;
    goto L_426827;
L_42688d:
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.zf)
        goto L_426827;
    edx = 0x2u;
    eax = 0x598d48u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(16, (eax & 0xffffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_426827;
    goto L_426825;
L_4268ab:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
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
L_4268bb:
    eax = 0x1u;
    edx = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
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
L_4268ce:
    eax = 0x2u;
    edx = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
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
L_4268e1:
    {
        (void)lift_sub(32, ebx, 0x3u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426946;
    ebx = (edx + 0xffffffffu);
    edx = ((ebx * 4u));
    edx = edx - ebx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    edx = edx + ebx;
    edx = edx + ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffff65u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 1, (edx & 0xffu));
L_426903:
    ebx = (esi + 0xffffffffu);
    edx = ((ebx * 4u));
    edx = edx - ebx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    edx = edx + ebx;
    ebx = (edx + ecx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, ebp + 0xffffff66u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, ebp + 0xffffff67u, 1)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ebx, ebp + 0xffffff68u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xfffffff0u, 1, ((edx >> 8) & 0xffu));
    {
        (void)lift_sub(32, ecx, 0xcu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_42694c;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ebx, ebp + 0xffffff69u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe4u, 1, ((edx >> 8) & 0xffu));
    goto L_4263b7;
L_426946:
    lift_store(&env, ebp, 0xffffffe8u, 1, 0xfeu);
    goto L_426903;
L_42694c:
    lift_store(&env, ebp, 0xffffffe4u, 1, 0xfeu);
    goto L_4263b7;
L_426955:
    {
        (void)lift_sub(32, ecx, 0x3u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4269b1;
    ebx = (esi + 0x1u);
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    edi = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    ebx = ebx - edi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    ebx = ebx + edi;
    ebx = ebx + ecx;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ebx, ebp + 0xffffff65u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffecu, 1, ((edx >> 8) & 0xffu));
L_426979:
    esi = esi + 1u;
    ebx = ((esi * 4u));
    ebx = ebx - esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    ebx = ebx + esi;
    esi = (ebx + ecx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, ebp + 0xffffff66u, 1)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, esi, ebp + 0xffffff67u, 1)) & 0xffu) << 8);
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, esi, ebp + 0xffffff68u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(32, ecx, 0xcu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4269b7;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esi, ebp + 0xffffff69u, 1)) & 0xffu);
    goto L_4263cb;
L_4269b1:
    lift_store(&env, ebp, 0xffffffecu, 1, 0xfeu);
    goto L_426979;
L_4269b7:
    ecx = (ecx & 0xffffff00u) | ((0xfeu) & 0xffu);
    goto L_4263cb;
L_4269be:
    edx = 0x3u;
    eax = 0x598d48u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_and(32, eax, 0xffffu, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
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

uint32_t lifted_ai_chain_search(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_AI_CHAIN_SEARCH_STACK + 4 + 4 * 6 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_AI_CHAIN_SEARCH_STACK, 6, entry);
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
    esp = esp - 0x1acu;
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffc4u, 4, ecx);
    eax = (eax & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    ebx = 0x5u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xfffffff4u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    eax = (ebp + 0xffffffa4u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x5u;
    eax = (ebp + 0xffffffb4u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x5u;
    eax = (ebp + 0xffffff94u);
    edx = edx ^ edx;
    ecx = 0x41u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x5u;
    eax = (ebp + 0xffffff9cu);
    edx = edx ^ edx;
    edi = (ebp + 0xffffff50u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    edx = lift_load(&env, ebp, 0x18u, 4);
    eax = eax + 0x184u;
    ebx = (ebp + 0xffffffacu);
    esi = eax;
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
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
    ecx = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    edx = (ebp + 0xffffff50u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4261b0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ecx = ecx ^ ecx;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
L_426a8e:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, ebp + 0xffffffacu, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_426b86;
L_426a9c:
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = edx + 0xdu;
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_426a8e;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xfffffff4u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_426b71;
    ebx = 0xffffffffu;
    esi = lift_load(&env, ebp, 0x1cu, 4);
    edx = ebx;
    {
        (void)lift_sub(32, esi, 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_426af4;
    eax = eax ^ eax;
L_426acc:
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, ebp + 0xffffff9cu, 1)) & 0xffu);
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_426aee;
    esi = (ecx & 0xffu);
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, ebp + 0xffffff94u, 1)) & 0xffu);
    ecx = ecx + esi;
    esi = lift_load(&env, eax, ebp + 0xffffffa4u, 1);
    ecx = ecx + esi;
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426aee;
    edx = ecx;
    ebx = eax;
L_426aee:
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_426acc;
L_426af4:
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426b23;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x1cu, 4), 0x2u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_426b23;
    eax = eax ^ eax;
L_426b01:
    {
        (void)lift_sub(8, lift_load(&env, eax, ebp + 0xffffff94u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_426b1d;
    ecx = ecx ^ ecx;
    esi = lift_load(&env, eax, ebp + 0xffffffa4u, 1);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, ebp + 0xffffff94u, 1)) & 0xffu);
    ecx = ecx + esi;
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426b1d;
    edx = ecx;
    ebx = eax;
L_426b1d:
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_426b01;
L_426b23:
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_427053;
L_426b2c:
    eax = 0xffffffffu;
    ecx = 0x4u;
    edx = edx ^ edx;
L_426b38:
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_42707c;
    eax = edx;
L_426b48:
    ecx = ecx - 1u;
    edx = edx + 1u;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426b54;
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_426b38;
L_426b54:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_426b5e;
    eax = 0x2u;
L_426b5e:
    edx = lift_load(&env, ebp, 0xcu, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, ebp + 0xffffffb4u, 1)) & 0xffu);
    edx = lift_load(&env, ebp, 0x8u, 4);
    eax = eax & 0xffu;
    lift_store(&env, edx, 0x0u, 4, eax);
L_426b71:
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xfffffff4u, 1), 0x0u, &fl);
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
L_426b86:
    ecx = 0x41u;
    esi = lift_load(&env, ebp, 0xffffffd0u, 4);
    edi = (ebp + 0xffffff50u);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
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
    esi = 0xcu;
    edx = edx + esi;
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffff50u, 1)) & 0xffu);
    eax = edx;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_426bd5;
L_426bbf:
    edi = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = edi - 1u;
    eax = eax - 1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_426bd5;
    {
        (void)lift_sub(8, lift_load(&env, eax, ebp + 0xffffff50u, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_426bbf;
L_426bd5:
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, ecx, 0xffffffffu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426a9c;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffc4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff50u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426bfe;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff4fu, 1, (edx & 0xffu));
L_426bfe:
    edi = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426c15;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + edi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff4eu, 1, (edx & 0xffu));
L_426c15:
    eax = (ebp + 0xfffffe4cu);
    ecx = (ebp + 0xfffffff0u);
    edx = (ebp + 0xfffffe4cu);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x10u, 1)) & 0xffu);
    eax = (ebp + 0xffffff50u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4346b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_426c6f;
    eax = (ebp + 0xfffffe4cu);
    ecx = ecx ^ ecx;
    edx = edx ^ edx;
L_426c48:
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = eax + 0x4u;
    edx = edx + 1u;
    ecx = ecx + ebx;
    {
        (void)lift_sub(32, edx, 0x41u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_426c48;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426c6f;
    lift_store(&env, edx, ebp + 0xffffffa4u, 1, (ecx & 0xffu));
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) ^ (ecx & 0xffu)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (ecx & 0xffu));
    lift_store(&env, edx, ebp + 0xffffffb4u, 1, (ecx & 0xffu));
L_426c6f:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff50u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426c8f;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffc4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff4fu, 1, (edx & 0xffu));
L_426c8f:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426ca5;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff4eu, 1, (edx & 0xffu));
L_426ca5:
    eax = (ebp + 0xfffffe4cu);
    ecx = (ebp + 0xfffffff0u);
    edx = (ebp + 0xfffffe4cu);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x10u, 1)) & 0xffu);
    eax = (ebp + 0xffffff50u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4346b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_426d02;
    eax = (ebp + 0xfffffe4cu);
    ecx = ecx ^ ecx;
    edx = edx ^ edx;
L_426cd8:
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = eax + 0x4u;
    edx = edx + 1u;
    ecx = ecx + ebx;
    {
        (void)lift_sub(32, edx, 0x41u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_426cd8;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426d02;
    eax = edx;
    lift_store(&env, edx, ebp + 0xffffffa4u, 1, (ecx & 0xffu));
    lift_store(&env, eax, ebp + 0xffffffb4u, 1, 0x1u);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xfffffff4u, 1, ((edx >> 8) & 0xffu));
L_426d02:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff50u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426d22;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff4fu, 1, (edx & 0xffu));
L_426d22:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426d38;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffc4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff4eu, 1, (edx & 0xffu));
L_426d38:
    eax = (ebp + 0xfffffe4cu);
    ecx = (ebp + 0xfffffff0u);
    edx = (ebp + 0xfffffe4cu);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x10u, 1)) & 0xffu);
    eax = (ebp + 0xffffff50u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4346b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_426d93;
    eax = (ebp + 0xfffffe4cu);
    ecx = ecx ^ ecx;
    edx = edx ^ edx;
L_426d6b:
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = eax + 0x4u;
    edx = edx + 1u;
    ecx = ecx + ebx;
    {
        (void)lift_sub(32, edx, 0x41u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_426d6b;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426d93;
    lift_store(&env, edx, ebp + 0xffffffb4u, 1, 0x2u);
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, edx, ebp + 0xffffffa4u, 1, (ecx & 0xffu));
    lift_store(&env, ebp, 0xfffffff4u, 1, ((ebx >> 8) & 0xffu));
L_426d93:
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426a9c;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x1cu, 4), 0x2u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_426a9c;
    ecx = 0x41u;
    esi = lift_load(&env, ebp, 0xffffffccu, 4);
    edi = (ebp + 0xffffff50u);
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
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffffb4u, 1)) & 0xffu);
    eax = eax + edi;
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_426fb5;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_427001;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff50u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426e01;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffc4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff4fu, 1, (edx & 0xffu));
L_426e01:
    edi = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_426fed;
L_426e0d:
    eax = (ebp + 0xfffffe4cu);
    ecx = (ebp + 0xfffffff0u);
    edx = (ebp + 0xfffffe4cu);
    edi = 0x34u;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x10u, 1)) & 0xffu);
    eax = (ebp + 0xffffff50u);
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4346b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
L_426e3b:
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ecx = edi;
    {
        uint32_t r = lift_imul(32, esi, 0x34u, &fl);
        eax = r;
    }
L_426e43:
    {
        (void)lift_sub(32, lift_load(&env, eax, ebp + 0xfffffe4cu, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_426e55;
    lift_store(&env, edx, ebp + 0xffffff50u, 1, 0xffu);
L_426e55:
    eax = eax + 0x4u;
    edx = edx + 1u;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.zf)
        goto L_426e43;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edi = edi + 0x34u;
    eax = eax + 0xdu;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_sub(32, esi, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_426e3b;
    eax = (ebp + 0xffffff50u);
    ecx = (ebp + 0xfffffff0u);
    edx = (ebp + 0xfffffe4cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432980u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    eax = (ebp + 0xfffffe4cu);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x10u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffff50u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4346b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_426a9c;
    eax = (ebp + 0xfffffe4cu);
    ecx = ecx ^ ecx;
    edx = edx ^ edx;
L_426eb1:
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = eax + 0x4u;
    edx = edx + 1u;
    ecx = ecx + ebx;
    {
        (void)lift_sub(32, edx, 0x41u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_426eb1;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = lift_load(&env, ebp, 0x1cu, 4);
    lift_store(&env, eax, ebp + 0xffffff94u, 1, (ecx & 0xffu));
    {
        (void)lift_sub(32, esi, 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_426a9c;
    edi = 0x34u;
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffbcu, 4, edi);
    edi = edi ^ edi;
L_426edd:
    ecx = lift_load(&env, ebp, 0xffffffbcu, 4);
    edx = edi;
    {
        uint32_t r = lift_imul(32, esi, 0x34u, &fl);
        eax = r;
    }
L_426ee5:
    {
        (void)lift_sub(32, lift_load(&env, eax, ebp + 0xfffffe4cu, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_427039;
L_426ef3:
    eax = eax + 0x4u;
    edx = edx + 1u;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.zf)
        goto L_426ee5;
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    edi = edi + 0xdu;
    eax = eax + 0x34u;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    {
        (void)lift_sub(32, esi, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_426edd;
    eax = (ebp + 0xffffff50u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432980u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffe4cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_426f23:
    ecx = (ebp + 0xfffffff0u);
    edx = (ebp + 0xfffffe4cu);
    ebx = ebx ^ ebx;
    eax = (ebp + 0xffffff50u);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x10u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4346b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_426a9c;
    edx = (ebp + 0xfffffe4cu);
    ecx = ecx ^ ecx;
    eax = eax ^ eax;
L_426f4f:
    ebx = lift_load(&env, edx, 0x0u, 4);
    edx = edx + 0x4u;
    eax = eax + 1u;
    ecx = ecx + ebx;
    {
        (void)lift_sub(32, eax, 0x41u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_426f4f;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edi = 0x34u;
    esi = esi ^ esi;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, eax, ebp + 0xffffff9cu, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffecu, 4, edi);
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + (ecx & 0xffu)) & 0xffu) << 8);
    edi = edi ^ edi;
    lift_store(&env, eax, ebp + 0xffffff9cu, 1, ((ecx >> 8) & 0xffu));
L_426f75:
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = edi;
    {
        uint32_t r = lift_imul(32, esi, 0x34u, &fl);
        eax = r;
    }
L_426f7d:
    {
        (void)lift_sub(32, lift_load(&env, eax, ebp + 0xfffffe4cu, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_427046;
L_426f8b:
    eax = eax + 0x4u;
    edx = edx + 1u;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.zf)
        goto L_426f7d;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    edi = edi + 0xdu;
    eax = eax + 0x34u;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_sub(32, esi, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_426f75;
    eax = (ebp + 0xffffff50u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432980u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_426f23;
L_426fb5:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffc4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff50u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426fcd;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff4fu, 1, (edx & 0xffu));
L_426fcd:
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426e0d;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + ebx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff4eu, 1, (edx & 0xffu));
    goto L_426e0d;
L_426fed:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + edi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff4eu, 1, (edx & 0xffu));
    goto L_426e0d;
L_427001:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff50u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427019;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff4fu, 1, (edx & 0xffu));
L_427019:
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426e0d;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffc4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff4eu, 1, (edx & 0xffu));
    goto L_426e0d;
L_427039:
    lift_store(&env, edx, ebp + 0xffffff50u, 1, 0xffu);
    goto L_426ef3;
L_427046:
    lift_store(&env, edx, ebp + 0xffffff50u, 1, 0xffu);
    goto L_426f8b;
L_427053:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x1cu, 4), 0x1u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_426b2c;
    edx = 0x1u;
    eax = eax ^ eax;
L_427064:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), lift_load(&env, eax, ebp + 0xffffffa4u, 1), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_427070;
    eax = edx;
L_427070:
    edx = edx + 1u;
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_426b5e;
    goto L_427064;
L_42707c:
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, ebp + 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_426b48;
    eax = ecx;
    goto L_426b48;
}

uint32_t lifted_ai_bomb_search(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_AI_BOMB_SEARCH_STACK + 4 + 4 * 8 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_AI_BOMB_SEARCH_STACK, 8, entry);
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
    esp = esp - 0x8cu;
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    ebx = lift_load(&env, ebp, 0x14u, 4);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = lift_load(&env, ebp, 0x1cu, 4);
    lift_store(&env, ebp, 0xfffffff0u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, ebp, 0xfffffff4u, 1, ((eax >> 8) & 0xffu));
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4275cb;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe0u, 4), 0x6u, &fl);
    }
    if (fl.zf)
        goto L_4273c4;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x6u, &fl);
    }
    if (fl.zf)
        goto L_4273c4;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x6u, &fl);
    }
    if (!fl.zf)
        goto L_4275cb;
L_4273c4:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    ecx = 0x41u;
    eax = eax + 0x184u;
    edi = (ebp + 0xffffff6cu);
    esi = eax;
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
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
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x24u, 4), 0x23u, &fl);
    }
    if (!fl.zf)
        goto L_4275d6;
    ecx = 0x2710u;
    esi = lift_load(&env, ebp, 0x18u, 4);
    edx = (ebp + 0xffffff6cu);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ebx;
    ebx = (ebp + 0xffffffb0u);
    lift_store(&env, ebp, 0xffffffecu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4261b0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
L_427423:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, ebp + 0xffffffb0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_427590;
    ecx = 0x41u;
    esi = lift_load(&env, ebp, 0xffffffccu, 4);
    edi = (ebp + 0xffffff6cu);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
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
    ecx = 0xcu;
    edx = edx + ecx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffff6cu, 1)) & 0xffu);
    eax = edx;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_427477;
L_427467:
    ecx = ecx - 1u;
    eax = eax - 1u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_427477;
    {
        (void)lift_sub(8, lift_load(&env, eax, ebp + 0xffffff6cu, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_427467;
L_427477:
    {
        (void)lift_sub(32, ecx, 0xffffffffu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427590;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6cu, 1, (edx & 0xffu));
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_42749d;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6bu, 1, (edx & 0xffu));
L_42749d:
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4274b1;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6au, 1, (edx & 0xffu));
L_4274b1:
    ebx = lift_load(&env, ebp, 0x1du, 4);
    edx = (ebp + 0xffffffbcu);
    eax = (ebp + 0xffffff6cu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4344e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4274db;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff0u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (eax & 0xffu));
L_4274db:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6cu, 1, (edx & 0xffu));
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4274f8;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6bu, 1, (edx & 0xffu));
L_4274f8:
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_42750c;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6au, 1, (edx & 0xffu));
L_42750c:
    ebx = lift_load(&env, ebp, 0x1du, 4);
    edx = (ebp + 0xffffffbcu);
    eax = (ebp + 0xffffff6cu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4344e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_427537;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff0u, 1, (eax & 0xffu));
    lift_store(&env, ebp, 0xfffffff4u, 1, 0x1u);
L_427537:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6cu, 1, (edx & 0xffu));
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427554;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6bu, 1, (edx & 0xffu));
L_427554:
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427566;
    ecx = ecx + lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    lift_store(&env, ecx, ebp + 0xffffff6au, 1, (eax & 0xffu));
L_427566:
    ebx = lift_load(&env, ebp, 0x1du, 4);
    edx = (ebp + 0xffffffbcu);
    eax = (ebp + 0xffffff6cu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4344e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_427590;
    edx = (edx & 0xffffff00u) | ((0x2u) & 0xffu);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (edx & 0xffu));
    lift_store(&env, ebp, 0xfffffff0u, 1, (eax & 0xffu));
L_427590:
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = ecx + 0xdu;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_427423;
L_4275a9:
    eax = eax ^ eax;
    edx = lift_load(&env, ebp, 0xcu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x0u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0x8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    lift_store(&env, edx, 0x0u, 4, eax);
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
L_4275cb:
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
L_4275d6:
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ebp, 0x20u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_42780f;
L_4275e7:
    eax = 0xcu;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffff92u, 1)) & 0xffu) << 8);
    edx = edx ^ edx;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_42760e;
L_4275f6:
    {
        (void)lift_sub(8, lift_load(&env, eax, ebp + 0xffffff86u, 1), 0x6u, &fl);
    }
    if (!fl.zf)
        goto L_427602;
    edx = 0x1u;
L_427602:
    eax = eax - 1u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_42760e;
    {
        (void)lift_sub(8, lift_load(&env, eax, ebp + 0xffffff86u, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4275f6;
L_42760e:
    ecx = 0xcu;
    ecx = ecx - eax;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_42781d;
L_42761d:
    edx = lift_load(&env, ebp, 0x18u, 4);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    ecx = ebx;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (ebp + 0xffffffb0u);
    edx = (ebp + 0xffffff6cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4261b0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ecx = ecx ^ ecx;
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    eax = eax + 0x184u;
    lift_store(&env, ebp, 0xffffffb8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
L_427647:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, ebp + 0xffffffb0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4277f1;
    ecx = 0x41u;
    esi = lift_load(&env, ebp, 0xffffffd0u, 4);
    edi = (ebp + 0xffffff6cu);
    edx = lift_load(&env, ebp, 0xffffffb8u, 4);
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
    esi = 0xcu;
    edx = edx + esi;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffff6cu, 1)) & 0xffu);
    eax = edx;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_42769b;
L_42768b:
    esi = esi - 1u;
    eax = eax - 1u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_42769b;
    {
        (void)lift_sub(8, lift_load(&env, eax, ebp + 0xffffff6cu, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_42768b;
L_42769b:
    {
        (void)lift_sub(32, esi, 0xffffffffu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4277f1;
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6cu, 1, (edx & 0xffu));
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4276c1;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6bu, 1, (edx & 0xffu));
L_4276c1:
    {
        (void)lift_sub(32, esi, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4276d5;
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6au, 1, (edx & 0xffu));
L_4276d5:
    ecx = lift_load(&env, ebp, 0x1du, 4);
    ebx = (ebp + 0xffffffc0u);
    edx = (ebp + 0xffffffbcu);
    eax = (ebp + 0xffffff6cu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ecx = r;
    }
    edi = lift_load(&env, ebp, 0x1cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x434300u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, edi, 0x2u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_427701;
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    edx = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = eax + eax;
    eax = eax + edx;
L_427701:
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427714;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) ^ (ecx & 0xffu)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (ecx & 0xffu));
    lift_store(&env, ebp, 0xfffffff0u, 1, (eax & 0xffu));
L_427714:
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6cu, 1, (edx & 0xffu));
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427731;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6bu, 1, (edx & 0xffu));
L_427731:
    {
        (void)lift_sub(32, esi, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427745;
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6au, 1, (edx & 0xffu));
L_427745:
    ecx = lift_load(&env, ebp, 0x1du, 4);
    ebx = (ebp + 0xffffffc0u);
    edx = (ebp + 0xffffffbcu);
    eax = (ebp + 0xffffff6cu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x434300u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0x1cu, 4);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, ebx, 0x2u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_427771;
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    edi = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = eax + eax;
    eax = eax + edi;
L_427771:
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427784;
    ecx = (ecx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, ((ecx >> 8) & 0xffu));
    lift_store(&env, ebp, 0xfffffff0u, 1, (eax & 0xffu));
L_427784:
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6cu, 1, (edx & 0xffu));
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4277a1;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff6bu, 1, (edx & 0xffu));
L_4277a1:
    {
        (void)lift_sub(32, esi, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4277b3;
    esi = esi + lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    lift_store(&env, esi, ebp + 0xffffff6au, 1, (eax & 0xffu));
L_4277b3:
    ecx = lift_load(&env, ebp, 0x1du, 4);
    ebx = (ebp + 0xffffffc0u);
    edx = (ebp + 0xffffffbcu);
    eax = (ebp + 0xffffff6cu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x434300u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0x1cu, 4);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, ebx, 0x2u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4277df;
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    esi = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = eax + eax;
    eax = eax + esi;
L_4277df:
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4277f1;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff0u, 1, (eax & 0xffu));
    lift_store(&env, ebp, 0xfffffff4u, 1, 0x2u);
L_4277f1:
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax + 0xdu;
    edx = edx + 1u;
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_427647;
    goto L_4275a9;
L_42780f:
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4275e7;
    goto L_42761d;
L_42781d:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_42761d;
    {
        (void)lift_sub(32, ecx, 0x8u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_42761d;
    eax = lift_load(&env, ebp, 0xcu, 4);
    lift_store(&env, eax, 0x0u, 4, 0x2u);
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
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

uint32_t lifted_effects_release_all_full(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_EFFECTS_RELEASE_ALL_FULL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_EFFECTS_RELEASE_ALL_FULL_STACK, 0,
               entry);
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
    ecx = eax;
    edx = 0x1f4u;
    eax = eax + 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b22c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x8u;
    eax = (ecx + 0x92cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b22c0u, eax, edx, ebx, ecx, 0, esp);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_delay_actor_spawn(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_DELAY_ACTOR_SPAWN_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_DELAY_ACTOR_SPAWN_STACK, 0, entry);
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
    eax = lift_load(&env, 0u, 0x532a64u, 4);
    esi = lift_load(&env, 0u, (eax * 4u) + 0x53bdacu, 4);
    eax = ((esi * 4u));
    eax = eax - esi;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    esi = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax - esi;
    edi = (eax + 0x1388u);
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4713c1;
L_471378:
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
    edx = 0x457770u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x0u, 4, 0xc8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
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
L_4713c1:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_471378;
}

uint32_t lifted_surface_bounds(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_SURFACE_BOUNDS_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_SURFACE_BOUNDS_STACK, 1, entry);
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
    esp = esp - 0x2cu;
    edi = eax;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = eax - 1u;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, edi, 0x8u, 4);
    eax = eax - 1u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffecu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    lift_store(&env, ebp, 0xffffffe8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xfffffff4u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    esi = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 2, (eax & 0xffffu));
L_479318:
    eax = eax ^ eax;
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_47939e;
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
L_47932b:
    eax = eax ^ eax;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = (eax & 0xffff0000u) | (((ecx & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_47933a;
    esi = esi + 1u;
    goto L_479318;
L_47933a:
    eax = edi;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    ebx = (ebx & 0xffff0000u) | (((ecx & 0xffffu)) & 0xffffu);
    edx = (edx & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478f10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47939b;
    eax = eax ^ eax;
    edx = lift_load(&env, ebp, 0xffffffeau, 4);
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_479362;
    lift_store(&env, ebp, 0xffffffecu, 2, (esi & 0xffffu));
L_479362:
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xfffffff2u, 4);
    edx = (edx & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_479375;
    lift_store(&env, ebp, 0xfffffff4u, 2, (esi & 0xffffu));
L_479375:
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffe6u, 4);
    edx = (edx & 0xffff0000u) | (((ecx & 0xffffu)) & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_479388;
    lift_store(&env, ebp, 0xffffffe8u, 2, (ecx & 0xffffu));
L_479388:
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffeeu, 4);
    edx = (edx & 0xffff0000u) | (((ecx & 0xffffu)) & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_47939b;
    lift_store(&env, ebp, 0xfffffff0u, 2, (ecx & 0xffffu));
L_47939b:
    ecx = ecx + 1u;
    goto L_47932b;
L_47939e:
    edx = lift_load(&env, ebp, 0xffffffeau, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4793fd;
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = (ebx + 0x1u);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, ebp, 0x8u, 4);
    eax = eax + 1u;
    lift_store(&env, edx, 0x0u, 4, eax);
L_4793c9:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4793ef;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4793ef;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    ebx = lift_load(&env, edi, 0x4u, 4);
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4793ef;
    eax = lift_load(&env, ebp, 0x8u, 4);
    esi = lift_load(&env, edi, 0x8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.zf)
        goto L_479437;
L_4793ef:
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
L_4793fd:
    eax = lift_load(&env, ebp, 0xffffffeau, 4);
    ebx = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, ebx, 0x0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe6u, 4);
    ebx = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, ebx, 0x0u, 4, eax);
    eax = lift_load(&env, ebp, 0xfffffff2u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = eax + 1u;
    lift_store(&env, edx, 0x0u, 4, eax);
    edx = lift_load(&env, ebp, 0xffffffeeu, 4);
    eax = lift_load(&env, ebp, 0xffffffe6u, 4);
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
    eax = lift_load(&env, ebp, 0x8u, 4);
    edx = edx + 1u;
    lift_store(&env, eax, 0x0u, 4, edx);
    goto L_4793c9;
L_479437:
    {
        uint32_t r = lift_xor(32, eax, esi, &fl);
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

uint32_t lifted_object_is_idle(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_IS_IDLE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_IS_IDLE_STACK, 0, entry);
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
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c0b77;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x12cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c0b83;
L_4c0b77:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4c0c82;
L_4c0b83:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x28u, 4), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4c0b95;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x24u, 4), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4c0b97;
L_4c0b95:
    goto L_4c0ba0;
L_4c0b97:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x2cu, 4), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4c0ba2;
L_4c0ba0:
    goto L_4c0bab;
L_4c0ba2:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x78u, 4), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4c0bb7;
L_4c0bab:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4c0c82;
L_4c0bb7:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4c0bd5;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x5cu, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4c0bd7;
L_4c0bd5:
    goto L_4c0be9;
L_4c0bd7:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xb0u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4c0beb;
L_4c0be9:
    goto L_4c0bfa;
L_4c0beb:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xcu, 4), 0x2u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c0bfc;
L_4c0bfa:
    goto L_4c0c0b;
L_4c0bfc:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x60u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4c0c0d;
L_4c0c0b:
    goto L_4c0c1f;
L_4c0c0d:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xb4u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4c0c28;
L_4c0c1f:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4c0c82;
L_4c0c28:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    edx = lift_load(&env, eax, 0x24u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, edx, lift_load(&env, eax, 0x13cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4c0c56;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    edx = lift_load(&env, eax, 0x78u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, edx, lift_load(&env, eax, 0x13cu, 4), &fl);
    }
    if (fl.zf)
        goto L_4c0c58;
L_4c0c56:
    goto L_4c0c72;
L_4c0c58:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    edx = lift_load(&env, eax, 0xccu, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, edx, lift_load(&env, eax, 0x13cu, 4), &fl);
    }
    if (fl.zf)
        goto L_4c0c7b;
L_4c0c72:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4c0c82;
L_4c0c7b:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x1u);
L_4c0c82:
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

uint32_t lifted_scaled_round(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_SCALED_ROUND_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_SCALED_ROUND_STACK, 0, entry);
    ebx = ebx + ebx;
    edx = (ebx + 0x1u);
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = (eax + ecx);
    eax = edx;
    ecx = ecx + ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_rtl_range_table_find(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_RANGE_TABLE_FIND_STACK + 4 + 4 * 4 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_RANGE_TABLE_FIND_STACK, 4, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x8u, 4);
    ecx = lift_load(&env, esp, 0xcu, 4);
    ebx = lift_load(&env, esp, 0x10u, 4);
    edx = lift_load(&env, esp, 0x14u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d0b63;
L_4d0b47:
    {
        (void)lift_sub(32, ecx, lift_load(&env, eax, 0x0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d0b5a;
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x4u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d0b5a;
    {
        (void)lift_sub(32, edx, lift_load(&env, eax, 0x8u, 4), &fl);
    }
    if (fl.cf)
        goto L_4d0b5a;
    {
        (void)lift_sub(32, edx, lift_load(&env, eax, 0xcu, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d0b65;
L_4d0b5a:
    eax = eax + 0x20u;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4d0b47;
L_4d0b63:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4d0b65:
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
