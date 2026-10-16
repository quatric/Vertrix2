/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_3.h"

uint32_t lifted_surface_flip_vertical(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_SURFACE_FLIP_VERTICAL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_SURFACE_FLIP_VERTICAL_STACK, 0, entry);
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
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    lift_store(&env, esp, 0x14u, 2, (edx & 0xffffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xcu, 1)) & 0xffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_479bef;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_479c76;
    edx = lift_load(&env, esp, 0x12u, 4);
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x10u, 4, eax);
    eax = (edx + 0xffffffffu);
    {
        uint32_t r = lift_imul(32, eax, ecx, &fl);
        eax = r;
    }
    ecx = lift_load(&env, esp, 0x10u, 4);
    eax = eax + eax;
    ecx = ecx + eax;
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
    lift_store(&env, esp, 0x4u, 4, ecx);
    lift_store(&env, esp, 0x14u, 2, (eax & 0xffffu));
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_479be5;
L_479bb0:
    eax = eax ^ eax;
L_479bb2:
    edx = edx ^ edx;
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_479c56;
    edx = lift_load(&env, esp, 0x4u, 4);
    ecx = ecx + ecx;
    eax = lift_load(&env, esp, 0x10u, 4);
    edx = edx - ecx;
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x4u, 4, edx);
    edx = lift_load(&env, esp, 0x14u, 4);
    lift_store(&env, esp, 0x10u, 4, eax);
    {
        uint32_t a = (edx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edx = (edx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, esp, 0x14u, 2, (edx & 0xffffu));
    if (!fl.zf)
        goto L_479bb0;
L_479be5:
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
L_479bef:
    edx = lift_load(&env, esp, 0x12u, 4);
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edi = lift_load(&env, eax, 0x0u, 4);
    eax = (edx + 0xffffffffu);
    {
        uint32_t r = lift_imul(32, eax, ecx, &fl);
        eax = r;
    }
    ecx = (edi + eax);
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
    lift_store(&env, esp, 0x8u, 4, ecx);
    lift_store(&env, esp, 0x14u, 2, (eax & 0xffffu));
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
L_479c19:
    if (fl.zf)
        goto L_479be5;
    ebp = lift_load(&env, esp, 0x8u, 4);
    edx = edx ^ edx;
L_479c21:
    eax = eax ^ eax;
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    eax = (eax & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_479c46;
    ebp = lift_load(&env, esp, 0x8u, 4);
    esi = lift_load(&env, esp, 0x14u, 4);
    ebp = ebp - ecx;
    {
        uint32_t r = lift_add(32, edi, ecx, &fl);
        edi = r;
    }
    lift_store(&env, esp, 0x8u, 4, ebp);
    {
        uint32_t a = (esi & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, esp, 0x14u, 2, (esi & 0xffffu));
    goto L_479c19;
L_479c46:
    esi = (edi + eax);
    eax = eax + ebp;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, esi, 0x0u, 1)) & 0xffu) << 8);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, esi, 0x0u, 1, (ecx & 0xffu));
    edx = edx + 1u;
    lift_store(&env, eax, 0x0u, 1, ((ecx >> 8) & 0xffu));
    goto L_479c21;
L_479c56:
    ecx = lift_load(&env, esp, 0x10u, 4);
    edx = edx + edx;
    esi = lift_load(&env, esp, 0x4u, 4);
    ecx = ecx + edx;
    edx = edx + esi;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, ecx, 0x0u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x0u, 2, (esi & 0xffffu));
    eax = eax + 1u;
    lift_store(&env, edx, 0x0u, 2, (edi & 0xffffu));
    goto L_479bb2;
L_479c76:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_479ce9;
    {
        uint32_t r = lift_imul(32, ebx, 0x3u, &fl);
        ebx = r;
    }
    edx = lift_load(&env, esp, 0x12u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edi = lift_load(&env, eax, 0x0u, 4);
    eax = (edx + 0xffffffffu);
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, ecx, &fl);
        eax = r;
    }
    ecx = (edi + eax);
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
    lift_store(&env, esp, 0xcu, 4, ecx);
    lift_store(&env, esp, 0x14u, 2, (eax & 0xffffu));
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
L_479ca8:
    if (fl.zf)
        goto L_479be5;
    ebp = lift_load(&env, esp, 0xcu, 4);
    edx = edx ^ edx;
L_479cb4:
    eax = eax ^ eax;
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    eax = (eax & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_479cd9;
    ebp = lift_load(&env, esp, 0xcu, 4);
    esi = lift_load(&env, esp, 0x14u, 4);
    ebp = ebp - ecx;
    {
        uint32_t r = lift_add(32, edi, ecx, &fl);
        edi = r;
    }
    lift_store(&env, esp, 0xcu, 4, ebp);
    {
        uint32_t a = (esi & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, esp, 0x14u, 2, (esi & 0xffffu));
    goto L_479ca8;
L_479cd9:
    esi = (edi + eax);
    eax = eax + ebp;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, eax, 0x0u, 1)) & 0xffu) << 8);
    lift_store(&env, esi, 0x0u, 1, ((ecx >> 8) & 0xffu));
    edx = edx + 1u;
    lift_store(&env, eax, 0x0u, 1, (ecx & 0xffu));
    goto L_479cb4;
L_479ce9:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_479be5;
    edx = lift_load(&env, esp, 0x12u, 4);
    ebp = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    ecx = (edx + 0xffffffffu);
    {
        uint32_t r = lift_imul(32, eax, ecx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = (eax + ebp);
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
    lift_store(&env, esp, 0x0u, 4, ecx);
    lift_store(&env, esp, 0x14u, 2, (eax & 0xffffu));
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
L_479d1e:
    if (fl.zf)
        goto L_479be5;
    eax = eax ^ eax;
L_479d26:
    edx = edx ^ edx;
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_479d4c;
    edx = lift_load(&env, esp, 0x0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    edx = edx - ecx;
    lift_store(&env, esp, 0x0u, 4, edx);
    edx = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t r = lift_add(32, ebp, ecx, &fl);
        ebp = r;
    }
    {
        uint32_t a = (edx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edx = (edx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, esp, 0x14u, 2, (edx & 0xffffu));
    goto L_479d1e;
L_479d4c:
    ecx = ((edx * 4u));
    esi = lift_load(&env, esp, 0x0u, 4);
    edx = (ecx + ebp);
    ecx = ecx + esi;
    esi = lift_load(&env, ecx, 0x0u, 4);
    edi = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, edx, 0x0u, 4, esi);
    eax = eax + 1u;
    lift_store(&env, ecx, 0x0u, 4, edi);
    goto L_479d26;
}

uint32_t lifted_surface_blit(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_SURFACE_BLIT_STACK + 4 + 4 * 4 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_SURFACE_BLIT_STACK, 4, entry);
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
    esi = eax;
    edi = edx;
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    edx = lift_load(&env, ebp, 0x8u, 4);
    eax = lift_load(&env, ebp, 0xcu, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0xcu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x558c40u, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edi, 0xcu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x558c41u, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0xdu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x558c42u, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edi, 0xdu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x558c43u, 1, (ebx & 0xffu));
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_47dbc3;
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_47dbc3;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x558c40u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_47cfb9;
    {
        (void)lift_sub(8, (ebx & 0xffu), lift_load(&env, 0u, 0x558c41u, 1), &fl);
    }
    if (!fl.zf)
        goto L_47cfb9;
    ebx = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c38u, 4, ebx);
    ebx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c3cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c38u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, 0u, 0x558c2cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c3cu, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c30u, 4, ebx);
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, 0u, 0x558c38u, 4), &fl);
        ecx = r;
    }
    ebx = lift_load(&env, esi, 0x0u, 4);
    esi = lift_load(&env, 0u, 0x558c3cu, 4);
    {
        uint32_t r = lift_imul(32, eax, esi, &fl);
        eax = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    ebx = ebx + ecx;
    ecx = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    ebx = ebx + ecx;
    ecx = lift_load(&env, edi, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = eax + ecx;
    eax = eax + edx;
    edi = lift_load(&env, 0u, 0x558c38u, 4);
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c14u, 4, ebx);
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.zf)
        goto L_47cf81;
L_47cf01:
    edi = 0x4u;
    esi = esi ^ esi;
L_47cf08:
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0x14u, 4), &fl);
    }
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf)
        goto L_47cf4c;
    ebx = edi;
L_47cf1f:
    eax = lift_load(&env, 0u, 0x558c18u, 4);
    edx = lift_load(&env, 0u, 0x558c14u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    eax = eax + ebx;
    lift_store(&env, edx, 0x0u, 4, ecx);
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    eax = lift_load(&env, 0u, 0x558c24u, 4);
    edx = edx + ebx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x558c14u, 4, edx);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (!fl.zf)
        goto L_47cf1f;
L_47cf4c:
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    ecx = lift_load(&env, 0u, 0x558c14u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = ecx + eax;
    eax = lift_load(&env, 0u, 0x558c30u, 4);
    ebx = lift_load(&env, 0u, 0x558c18u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebx = ebx + eax;
    eax = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c14u, 4, ecx);
    eax = eax - 1u;
    lift_store(&env, 0u, 0x558c18u, 4, ebx);
    lift_store(&env, ebp, 0x14u, 4, eax);
    goto L_47cf08;
L_47cf81:
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0x10u, 4), &fl);
    }
    if (!fl.zf)
        goto L_47cf01;
    ecx = lift_load(&env, ebp, 0x10u, 4);
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, ebp, 0x14u, 4), &fl);
        ecx = r;
    }
    esi = lift_load(&env, 0u, 0x558c18u, 4);
    edi = lift_load(&env, 0u, 0x558c14u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
L_47cfa0:
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
L_47cfb0:
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
L_47cfb9:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c40u, 1), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_47d0ec;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c41u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_47d0ec;
    ebx = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c38u, 4, ebx);
    ebx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c3cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c38u, 4);
    ebx = ebx - lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, 0u, 0x558c2cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c3cu, 4);
    ebx = ebx - lift_load(&env, ebp, 0x10u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    lift_store(&env, 0u, 0x558c30u, 4, ebx);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, 0u, 0x558c3cu, 4), &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x0u, 4);
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, 0u, 0x558c38u, 4), &fl);
        ecx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = edx + eax;
    lift_store(&env, 0u, 0x558c10u, 4, edx);
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = edx + ecx;
    eax = ((edx * 4u));
    eax = eax - edx;
    edx = lift_load(&env, esi, 0x0u, 4);
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c0cu, 4, edx);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
L_47d055:
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47d0ba;
L_47d067:
    eax = lift_load(&env, 0u, 0x558c10u, 4);
    edx = lift_load(&env, 0u, 0x558c0cu, 4);
    eax = eax + 1u;
    edx = edx + 1u;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0xffffffffu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x558c10u, 4, eax);
    lift_store(&env, 0u, 0x558c0cu, 4, edx);
    eax = eax + 1u;
    lift_store(&env, edx, 0xffffffffu, 1, (ecx & 0xffu));
    edx = edx + 1u;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0xffffffffu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x558c10u, 4, eax);
    lift_store(&env, 0u, 0x558c0cu, 4, edx);
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, edx, 0xffffffffu, 1, (ecx & 0xffu));
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0xfffffffeu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x558c10u, 4, eax);
    lift_store(&env, 0u, 0x558c0cu, 4, edx);
    eax = lift_load(&env, 0u, 0x558c24u, 4);
    lift_store(&env, edx, 0xffffffffu, 1, (ecx & 0xffu));
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    if (!fl.zf)
        goto L_47d067;
L_47d0ba:
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    edx = lift_load(&env, 0u, 0x558c0cu, 4);
    ecx = lift_load(&env, 0u, 0x558c10u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x558c30u, 4);
    ebx = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    lift_store(&env, 0u, 0x558c0cu, 4, edx);
    lift_store(&env, 0u, 0x558c10u, 4, ecx);
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    lift_store(&env, ebp, 0x14u, 4, ebx);
    goto L_47d055;
L_47d0ec:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c40u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_47d343;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c41u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_47d343;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x558c42u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_47d22a;
    ebx = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c38u, 4, ebx);
    ebx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c3cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c38u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, 0u, 0x558c2cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c3cu, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c30u, 4, ebx);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, 0u, 0x558c3cu, 4), &fl);
        eax = r;
    }
    eax = eax + edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = lift_load(&env, edi, 0x0u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x558c38u, 4);
    {
        uint32_t r = lift_imul(32, eax, ecx, &fl);
        eax = r;
    }
    edi = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, 0u, 0x558c18u, 4, edx);
    eax = eax + edi;
    edx = lift_load(&env, esi, 0x0u, 4);
    eax = eax + eax;
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c1cu, 4, edx);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
L_47d18b:
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47d1f3;
L_47d19d:
    eax = lift_load(&env, 0u, 0x558c18u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = edx & 0xf80000u;
    ecx = ecx & 0xfc00u;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x5u, &fl);
        edx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    ecx = ecx | edx;
    edx = lift_load(&env, eax, 0x0u, 4);
    edx = edx & 0xf8u;
    edx = edx | ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x3u, &fl);
        edx = r;
    }
    ecx = edx;
    edx = lift_load(&env, 0u, 0x558c1cu, 4);
    eax = eax + 0x4u;
    {
        uint32_t r = lift_add(32, edx, 0x2u, &fl);
        edx = r;
    }
    edi = lift_load(&env, 0u, 0x558c24u, 4);
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    lift_store(&env, edx, 0xfffffffeu, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x558c1cu, 4, edx);
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, 0u, 0x558c24u, 4, edi);
    if (!fl.zf)
        goto L_47d19d;
L_47d1f3:
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    edi = lift_load(&env, 0u, 0x558c1cu, 4);
    eax = eax + eax;
    edi = edi + eax;
    eax = lift_load(&env, 0u, 0x558c30u, 4);
    edx = lift_load(&env, 0u, 0x558c18u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x558c1cu, 4, edi);
    lift_store(&env, 0u, 0x558c18u, 4, edx);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, ebp, 0x14u, 4, ecx);
    goto L_47d18b;
L_47d22a:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47cfb0;
    ebx = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c38u, 4, ebx);
    ebx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c3cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c38u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c2cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c3cu, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, 0u, 0x558c30u, 4, ebx);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, 0u, 0x558c3cu, 4), &fl);
        eax = r;
    }
    edx = edx + eax;
    eax = lift_load(&env, edi, 0x0u, 4);
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, 0u, 0x558c38u, 4), &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = eax + edx;
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    ecx = ecx + lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = lift_load(&env, esi, 0x0u, 4);
    ecx = ecx + ecx;
    eax = eax + ecx;
    edx = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c1cu, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
L_47d2a4:
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47d30c;
L_47d2b6:
    eax = lift_load(&env, 0u, 0x558c18u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx & 0xf80000u;
    edx = edx & 0xf800u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x3u, &fl);
        edx = r;
    }
    ecx = ecx | edx;
    edx = lift_load(&env, eax, 0x0u, 4);
    edx = edx & 0xf8u;
    edx = edx | ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x3u, &fl);
        edx = r;
    }
    ecx = edx;
    edx = lift_load(&env, 0u, 0x558c1cu, 4);
    eax = eax + 0x4u;
    {
        uint32_t r = lift_add(32, edx, 0x2u, &fl);
        edx = r;
    }
    ebx = lift_load(&env, 0u, 0x558c24u, 4);
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    lift_store(&env, edx, 0xfffffffeu, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x558c1cu, 4, edx);
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    lift_store(&env, 0u, 0x558c24u, 4, ebx);
    if (!fl.zf)
        goto L_47d2b6;
L_47d30c:
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    esi = lift_load(&env, 0u, 0x558c1cu, 4);
    eax = eax + eax;
    esi = esi + eax;
    eax = lift_load(&env, 0u, 0x558c30u, 4);
    edi = lift_load(&env, 0u, 0x558c18u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x558c1cu, 4, esi);
    {
        uint32_t r = lift_add(32, edi, eax, &fl);
        edi = r;
    }
    eax = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c18u, 4, edi);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, ebp, 0x14u, 4, eax);
    goto L_47d2a4;
L_47d343:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x558c40u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_47d525;
    {
        (void)lift_sub(8, (ebx & 0xffu), lift_load(&env, 0u, 0x558c41u, 1), &fl);
    }
    if (!fl.zf)
        goto L_47d525;
    ebx = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c38u, 4, ebx);
    ebx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c3cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c38u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, 0u, 0x558c2cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c3cu, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c30u, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c3cu, 4);
    {
        uint32_t r = lift_imul(32, eax, ebx, &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x0u, 4);
    edi = lift_load(&env, 0u, 0x558c38u, 4);
    {
        uint32_t r = lift_imul(32, ecx, edi, &fl);
        ecx = r;
    }
    eax = eax + eax;
    edx = edx + eax;
    ecx = ecx + lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = lift_load(&env, esi, 0x0u, 4);
    ecx = ecx + ecx;
    lift_store(&env, 0u, 0x558c20u, 4, edx);
    eax = eax + ecx;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, ebp, 0x10u, 1)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x558c1cu, 4, eax);
    {
        (void)lift_and(8, ((ecx >> 8) & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_47d45c;
    edi = 0x2u;
    esi = esi ^ esi;
L_47d3e1:
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0x14u, 4), &fl);
    }
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf)
        goto L_47d429;
    ebx = edi;
L_47d3f8:
    eax = lift_load(&env, 0u, 0x558c20u, 4);
    edx = lift_load(&env, 0u, 0x558c1cu, 4);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    eax = eax + ebx;
    lift_store(&env, edx, 0x0u, 2, (ecx & 0xffffu));
    ecx = lift_load(&env, 0u, 0x558c24u, 4);
    lift_store(&env, 0u, 0x558c20u, 4, eax);
    edx = edx + ebx;
    ecx = ecx - 1u;
    lift_store(&env, 0u, 0x558c1cu, 4, edx);
    lift_store(&env, 0u, 0x558c24u, 4, ecx);
    {
        (void)lift_sub(32, esi, ecx, &fl);
    }
    if (!fl.zf)
        goto L_47d3f8;
L_47d429:
    ebx = lift_load(&env, ebp, 0x14u, 4);
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    edx = lift_load(&env, 0u, 0x558c1cu, 4);
    eax = eax + eax;
    ecx = lift_load(&env, 0u, 0x558c20u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x558c30u, 4);
    ebx = ebx - 1u;
    eax = eax + eax;
    lift_store(&env, ebp, 0x14u, 4, ebx);
    ecx = ecx + eax;
    lift_store(&env, 0u, 0x558c1cu, 4, edx);
    lift_store(&env, 0u, 0x558c20u, 4, ecx);
    goto L_47d3e1;
L_47d45c:
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0x10u, 4), &fl);
    }
    if (!fl.zf)
        goto L_47d46a;
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0x10u, 4), &fl);
    }
    if (fl.zf)
        goto L_47d50f;
L_47d46a:
    eax = lift_load(&env, ebp, 0x10u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c34u, 4, eax);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_47cfb0;
    ebx = 0x4u;
L_47d484:
    eax = lift_load(&env, 0u, 0x558c1cu, 4);
    lift_store(&env, 0u, 0x558c14u, 4, eax);
    eax = lift_load(&env, 0u, 0x558c20u, 4);
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    eax = lift_load(&env, 0u, 0x558c34u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47d4d3;
L_47d4a6:
    eax = lift_load(&env, 0u, 0x558c18u, 4);
    edx = lift_load(&env, 0u, 0x558c14u, 4);
    esi = lift_load(&env, 0u, 0x558c24u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    eax = eax + ebx;
    lift_store(&env, edx, 0x0u, 4, ecx);
    {
        uint32_t r = lift_add(32, edx, ebx, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    lift_store(&env, 0u, 0x558c14u, 4, edx);
    {
        uint32_t a = esi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        esi = r;
    }
    lift_store(&env, 0u, 0x558c24u, 4, esi);
    if (!fl.zf)
        goto L_47d4a6;
L_47d4d3:
    eax = lift_load(&env, 0u, 0x558c38u, 4);
    esi = lift_load(&env, 0u, 0x558c1cu, 4);
    eax = eax + eax;
    esi = esi + eax;
    eax = lift_load(&env, 0u, 0x558c3cu, 4);
    edi = lift_load(&env, 0u, 0x558c20u, 4);
    eax = eax + eax;
    lift_store(&env, 0u, 0x558c1cu, 4, esi);
    {
        uint32_t r = lift_add(32, edi, eax, &fl);
        edi = r;
    }
    eax = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c20u, 4, edi);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, ebp, 0x14u, 4, eax);
    if (fl.zf)
        goto L_47cfb0;
    goto L_47d484;
L_47d50f:
    ecx = lift_load(&env, ebp, 0x10u, 4);
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, ebp, 0x14u, 4), &fl);
        ecx = r;
    }
    edi = lift_load(&env, 0u, 0x558c1cu, 4);
    esi = edx;
    ecx = ecx + ecx;
    goto L_47cfa0;
L_47d525:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c40u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47d648;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c41u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_47d648;
    ebx = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c38u, 4, ebx);
    ebx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c3cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c38u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c2cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c3cu, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c30u, 4, ebx);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, 0u, 0x558c3cu, 4), &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x0u, 4);
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, 0u, 0x558c38u, 4), &fl);
        ecx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = edx + eax;
    ecx = ecx + lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, 0u, 0x558c18u, 4, edx);
    eax = eax + ecx;
    edx = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c0cu, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
L_47d5af:
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47d613;
L_47d5c1:
    eax = lift_load(&env, 0u, 0x558c18u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx & 0xe00000u;
    edx = edx & 0xe000u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0xau, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x5u, &fl);
        edx = r;
    }
    edx = edx | ecx;
    ecx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx & 0xc0u;
    edx = edx | ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    edx = lift_load(&env, 0u, 0x558c0cu, 4);
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    lift_store(&env, edx, 0x0u, 1, (ecx & 0xffu));
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    ecx = lift_load(&env, 0u, 0x558c24u, 4);
    lift_store(&env, 0u, 0x558c0cu, 4, edx);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, 0u, 0x558c24u, 4, ecx);
    if (!fl.zf)
        goto L_47d5c1;
L_47d613:
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    ebx = lift_load(&env, 0u, 0x558c0cu, 4);
    ebx = ebx + eax;
    eax = lift_load(&env, 0u, 0x558c30u, 4);
    esi = lift_load(&env, 0u, 0x558c18u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edi = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t r = lift_add(32, esi, eax, &fl);
        esi = r;
    }
    lift_store(&env, 0u, 0x558c0cu, 4, ebx);
    lift_store(&env, 0u, 0x558c18u, 4, esi);
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, ebp, 0x14u, 4, edi);
    goto L_47d5af;
L_47d648:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x558c40u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47d819;
    {
        (void)lift_sub(8, (ebx & 0xffu), lift_load(&env, 0u, 0x558c41u, 1), &fl);
    }
    if (!fl.zf)
        goto L_47d819;
    ebx = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c38u, 4, ebx);
    ebx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c3cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c38u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c2cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c3cu, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c30u, 4, ebx);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, 0u, 0x558c3cu, 4), &fl);
        eax = r;
    }
    ebx = lift_load(&env, edi, 0x0u, 4);
    edi = lift_load(&env, 0u, 0x558c38u, 4);
    {
        uint32_t r = lift_imul(32, ecx, edi, &fl);
        ecx = r;
    }
    eax = eax + ebx;
    eax = eax + edx;
    lift_store(&env, 0u, 0x558c10u, 4, eax);
    eax = lift_load(&env, esi, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = eax + ecx;
    edx = edx + eax;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0x10u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x558c0cu, 4, edx);
    {
        (void)lift_and(8, (ecx & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_47d74f;
    ebx = ebx ^ ebx;
L_47d6dd:
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0x14u, 4), &fl);
    }
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.zf)
        goto L_47d720;
L_47d6f2:
    edx = lift_load(&env, 0u, 0x558c0cu, 4);
    eax = lift_load(&env, 0u, 0x558c10u, 4);
    edx = edx + 1u;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = eax + 1u;
    lift_store(&env, edx, 0xffffffffu, 1, (ecx & 0xffu));
    ecx = lift_load(&env, 0u, 0x558c24u, 4);
    lift_store(&env, 0u, 0x558c10u, 4, eax);
    ecx = ecx - 1u;
    lift_store(&env, 0u, 0x558c0cu, 4, edx);
    lift_store(&env, 0u, 0x558c24u, 4, ecx);
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_47d6f2;
L_47d720:
    ecx = lift_load(&env, ebp, 0x14u, 4);
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    edi = lift_load(&env, 0u, 0x558c0cu, 4);
    edx = lift_load(&env, 0u, 0x558c10u, 4);
    ecx = ecx - 1u;
    edi = edi + eax;
    eax = lift_load(&env, 0u, 0x558c30u, 4);
    lift_store(&env, 0u, 0x558c0cu, 4, edi);
    edx = edx + eax;
    lift_store(&env, ebp, 0x14u, 4, ecx);
    lift_store(&env, 0u, 0x558c10u, 4, edx);
    goto L_47d6dd;
L_47d74f:
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0x10u, 4), &fl);
    }
    if (!fl.zf)
        goto L_47d763;
    eax = lift_load(&env, ebp, 0x10u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x558c3cu, 4), &fl);
    }
    if (fl.zf)
        goto L_47d805;
L_47d763:
    eax = lift_load(&env, ebp, 0x10u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c34u, 4, eax);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_47cfb0;
    ebx = 0x4u;
L_47d77e:
    eax = lift_load(&env, 0u, 0x558c0cu, 4);
    lift_store(&env, 0u, 0x558c14u, 4, eax);
    eax = lift_load(&env, 0u, 0x558c10u, 4);
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    eax = lift_load(&env, 0u, 0x558c34u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47d7cd;
L_47d7a0:
    edx = lift_load(&env, 0u, 0x558c18u, 4);
    eax = lift_load(&env, 0u, 0x558c14u, 4);
    esi = lift_load(&env, 0u, 0x558c24u, 4);
    ecx = lift_load(&env, edx, 0x0u, 4);
    edx = edx + ebx;
    lift_store(&env, eax, 0x0u, 4, ecx);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x558c18u, 4, edx);
    lift_store(&env, 0u, 0x558c14u, 4, eax);
    {
        uint32_t a = esi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        esi = r;
    }
    lift_store(&env, 0u, 0x558c24u, 4, esi);
    if (!fl.zf)
        goto L_47d7a0;
L_47d7cd:
    eax = lift_load(&env, 0u, 0x558c38u, 4);
    esi = lift_load(&env, 0u, 0x558c0cu, 4);
    edi = lift_load(&env, 0u, 0x558c10u, 4);
    esi = esi + eax;
    eax = lift_load(&env, 0u, 0x558c3cu, 4);
    lift_store(&env, 0u, 0x558c0cu, 4, esi);
    {
        uint32_t r = lift_add(32, edi, eax, &fl);
        edi = r;
    }
    eax = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c10u, 4, edi);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, ebp, 0x14u, 4, eax);
    if (fl.zf)
        goto L_47cfb0;
    goto L_47d77e;
L_47d805:
    ecx = lift_load(&env, ebp, 0x10u, 4);
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, ebp, 0x14u, 4), &fl);
        ecx = r;
    }
    edi = edx;
    esi = lift_load(&env, 0u, 0x558c10u, 4);
    goto L_47cfa0;
L_47d819:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c40u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_47d948;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c41u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47d948;
    ebx = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c38u, 4, ebx);
    ebx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c3cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c38u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c2cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c3cu, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c30u, 4, ebx);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, 0u, 0x558c3cu, 4), &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x0u, 4);
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, 0u, 0x558c38u, 4), &fl);
        ecx = r;
    }
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, 0u, 0x558c10u, 4, edx);
    eax = eax + ecx;
    edx = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c14u, 4, edx);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
L_47d8a6:
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47d913;
L_47d8b8:
    eax = lift_load(&env, 0u, 0x558c10u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xe0u) & 0xffu);
    ecx = edx;
    ecx = ecx & 0xffu;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
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
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x3u) & 0xffu);
    edx = edx & 0xffu;
    eax = eax + 1u;
    ecx = ecx | edx;
    edx = lift_load(&env, 0u, 0x558c14u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        ecx = r;
    }
    lift_store(&env, 0u, 0x558c10u, 4, eax);
    lift_store(&env, edx, 0x0u, 4, ecx);
    {
        uint32_t r = lift_add(32, edx, 0x4u, &fl);
        edx = r;
    }
    ecx = lift_load(&env, 0u, 0x558c24u, 4);
    lift_store(&env, 0u, 0x558c14u, 4, edx);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, 0u, 0x558c24u, 4, ecx);
    if (!fl.zf)
        goto L_47d8b8;
L_47d913:
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    ebx = lift_load(&env, 0u, 0x558c14u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    esi = lift_load(&env, 0u, 0x558c10u, 4);
    ebx = ebx + eax;
    eax = lift_load(&env, 0u, 0x558c30u, 4);
    edi = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t r = lift_add(32, esi, eax, &fl);
        esi = r;
    }
    lift_store(&env, 0u, 0x558c14u, 4, ebx);
    lift_store(&env, 0u, 0x558c10u, 4, esi);
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, ebp, 0x14u, 4, edi);
    goto L_47d8a6;
L_47d948:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c40u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_47cfb0;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, 0u, 0x558c41u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_47cfb0;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x558c43u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), ((ebx >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_47daa0;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47cfb0;
    ebx = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c38u, 4, ebx);
    ebx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c3cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c38u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c2cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c3cu, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c30u, 4, ebx);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, 0u, 0x558c3cu, 4), &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x0u, 4);
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, 0u, 0x558c38u, 4), &fl);
        ecx = r;
    }
    eax = eax + eax;
    edx = edx + eax;
    ecx = ecx + lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, 0u, 0x558c20u, 4, edx);
    eax = eax + ecx;
    edx = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c14u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
L_47d9ed:
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47da69;
L_47d9ff:
    eax = lift_load(&env, 0u, 0x558c20u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0x7cu) & 0xffu) << 8);
    ecx = edx;
    ecx = ecx & 0xffffu;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        ecx = r;
    }
    edx = edx & 0x3e0u;
    edx = edx & 0xffffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    edx = edx | ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) ^ ((ecx >> 8) & 0xffu)) & 0xffu) << 8);
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) & 0x1fu) & 0xffu);
    ecx = ecx & 0xffffu;
    edx = edx | ecx;
    ecx = ((edx * 8u));
    edx = lift_load(&env, 0u, 0x558c14u, 4);
    eax = eax + 0x2u;
    {
        uint32_t r = lift_add(32, edx, 0x4u, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x558c20u, 4, eax);
    eax = lift_load(&env, 0u, 0x558c24u, 4);
    lift_store(&env, edx, 0xfffffffcu, 4, ecx);
    lift_store(&env, 0u, 0x558c14u, 4, edx);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    if (!fl.zf)
        goto L_47d9ff;
L_47da69:
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    edx = lift_load(&env, 0u, 0x558c14u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x558c30u, 4);
    ecx = lift_load(&env, 0u, 0x558c20u, 4);
    eax = eax + eax;
    ebx = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    lift_store(&env, 0u, 0x558c14u, 4, edx);
    lift_store(&env, 0u, 0x558c20u, 4, ecx);
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    lift_store(&env, ebp, 0x14u, 4, ebx);
    goto L_47d9ed;
L_47daa0:
    ebx = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c38u, 4, ebx);
    ebx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, 0u, 0x558c3cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c38u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c2cu, 4, ebx);
    ebx = lift_load(&env, 0u, 0x558c3cu, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ebx = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) - ebx);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, 0u, 0x558c30u, 4, ebx);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, 0u, 0x558c3cu, 4), &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x0u, 4);
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, 0u, 0x558c38u, 4), &fl);
        ecx = r;
    }
    eax = eax + eax;
    edx = edx + eax;
    ecx = ecx + lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, 0u, 0x558c20u, 4, edx);
    eax = eax + ecx;
    edx = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c14u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
L_47db12:
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47db8c;
L_47db24:
    eax = lift_load(&env, 0u, 0x558c20u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0xf8u) & 0xffu) << 8);
    ecx = edx;
    ecx = ecx & 0xffffu;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        ecx = r;
    }
    edx = edx & 0x7e0u;
    edx = edx & 0xffffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    ecx = ecx | edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x1fu) & 0xffu);
    edx = edx & 0xffffu;
    ecx = ecx | edx;
    edx = lift_load(&env, 0u, 0x558c14u, 4);
    edx = edx + 0x4u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, edx, 0xfffffffcu, 4, ecx);
    lift_store(&env, 0u, 0x558c14u, 4, edx);
    edx = lift_load(&env, 0u, 0x558c24u, 4);
    lift_store(&env, 0u, 0x558c20u, 4, eax);
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    lift_store(&env, 0u, 0x558c24u, 4, edx);
    if (!fl.zf)
        goto L_47db24;
L_47db8c:
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    ecx = lift_load(&env, 0u, 0x558c14u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = ecx + eax;
    eax = lift_load(&env, 0u, 0x558c30u, 4);
    ebx = lift_load(&env, 0u, 0x558c20u, 4);
    eax = eax + eax;
    esi = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t r = lift_add(32, ebx, eax, &fl);
        ebx = r;
    }
    lift_store(&env, 0u, 0x558c14u, 4, ecx);
    lift_store(&env, 0u, 0x558c20u, 4, ebx);
    {
        uint32_t a = esi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        esi = r;
    }
    lift_store(&env, ebp, 0x14u, 4, esi);
    goto L_47db12;
L_47dbc3:
    ebx = eax;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, 0u, 0x558c44u, 4, eax);
    ebx = ecx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx ^ ecx;
    edx = lift_load(&env, ebp, 0x10u, 4);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, 0u, 0x558c40u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, ecx, edx, &fl);
        ecx = r;
    }
    edx = lift_load(&env, esi, 0x14u, 4);
    edx = edx - ecx;
    lift_store(&env, 0u, 0x558c2cu, 4, edx);
    edx = edx ^ edx;
    ebx = lift_load(&env, ebp, 0x10u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x558c41u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, ebx, edx, &fl);
        ebx = r;
    }
    lift_store(&env, 0u, 0x558c48u, 4, eax);
    lift_store(&env, 0u, 0x558c14u, 4, eax);
    lift_store(&env, 0u, 0x558c1cu, 4, eax);
    lift_store(&env, 0u, 0x558c0cu, 4, eax);
    edx = lift_load(&env, edi, 0x14u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x558c40u, 1)) & 0xffu);
    edx = edx - ebx;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, 0u, 0x558c41u, 1)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x558c30u, 4, edx);
    edx = lift_load(&env, 0u, 0x558c44u, 4);
    lift_store(&env, 0u, 0x558c18u, 4, edx);
    lift_store(&env, 0u, 0x558c20u, 4, edx);
    lift_store(&env, 0u, 0x558c10u, 4, edx);
    {
        (void)lift_sub(8, (eax & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_47dcc9;
    eax = lift_load(&env, esi, 0x14u, 4);
    lift_store(&env, 0u, 0x558c28u, 4, ecx);
    lift_store(&env, 0u, 0x558c2cu, 4, eax);
    eax = lift_load(&env, edi, 0x14u, 4);
    esi = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c30u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_47cfb0;
L_47dc6f:
    ecx = lift_load(&env, 0u, 0x558c28u, 4);
    esi = lift_load(&env, 0u, 0x558c10u, 4);
    edi = lift_load(&env, 0u, 0x558c0cu, 4);
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
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    esi = lift_load(&env, 0u, 0x558c0cu, 4);
    edi = lift_load(&env, 0u, 0x558c10u, 4);
    esi = esi + eax;
    eax = lift_load(&env, 0u, 0x558c30u, 4);
    lift_store(&env, 0u, 0x558c0cu, 4, esi);
    {
        uint32_t r = lift_add(32, edi, eax, &fl);
        edi = r;
    }
    eax = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c10u, 4, edi);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, ebp, 0x14u, 4, eax);
    if (!fl.zf)
        goto L_47dc6f;
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
L_47dcc9:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_47dd78;
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_47dd78;
    ebx = ebx ^ ebx;
L_47dcdc:
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0x14u, 4), &fl);
    }
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.zf)
        goto L_47dd47;
L_47dcf1:
    eax = lift_load(&env, 0u, 0x558c10u, 4);
    edx = lift_load(&env, 0u, 0x558c0cu, 4);
    eax = eax + 1u;
    edx = edx + 1u;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0xffffffffu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x558c10u, 4, eax);
    lift_store(&env, 0u, 0x558c0cu, 4, edx);
    eax = eax + 1u;
    lift_store(&env, edx, 0xffffffffu, 1, (ecx & 0xffu));
    edx = edx + 1u;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0xffffffffu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x558c10u, 4, eax);
    lift_store(&env, 0u, 0x558c0cu, 4, edx);
    lift_store(&env, edx, 0xffffffffu, 1, (ecx & 0xffu));
    edx = edx + 1u;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x558c0cu, 4, edx);
    lift_store(&env, edx, 0xffffffffu, 1, (ecx & 0xffu));
    edx = lift_load(&env, 0u, 0x558c24u, 4);
    eax = eax + 0x2u;
    edx = edx - 1u;
    lift_store(&env, 0u, 0x558c10u, 4, eax);
    lift_store(&env, 0u, 0x558c24u, 4, edx);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (!fl.zf)
        goto L_47dcf1;
L_47dd47:
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    esi = lift_load(&env, 0u, 0x558c0cu, 4);
    edi = lift_load(&env, 0u, 0x558c10u, 4);
    esi = esi + eax;
    edi = edi + lift_load(&env, 0u, 0x558c30u, 4);
    eax = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, 0u, 0x558c0cu, 4, esi);
    eax = eax - 1u;
    lift_store(&env, 0u, 0x558c10u, 4, edi);
    lift_store(&env, ebp, 0x14u, 4, eax);
    goto L_47dcdc;
L_47dd78:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x558c40u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_47dee8;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c41u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_47dee8;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, 0u, 0x558c42u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ecx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_47de3f;
    ebx = ebx ^ ebx;
L_47dda4:
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0x14u, 4), &fl);
    }
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.zf)
        goto L_47de0f;
L_47ddb9:
    eax = lift_load(&env, 0u, 0x558c18u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx & 0xf80000u;
    edx = edx & 0xfc00u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x5u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        edx = r;
    }
    edx = edx | ecx;
    ecx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx & 0xf8u;
    ecx = ecx | edx;
    edx = lift_load(&env, 0u, 0x558c1cu, 4);
    edx = edx + 0x2u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x3u, &fl);
        ecx = r;
    }
    lift_store(&env, edx, 0xfffffffeu, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x558c1cu, 4, edx);
    edx = lift_load(&env, 0u, 0x558c24u, 4);
    eax = eax + 0x4u;
    edx = edx - 1u;
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    lift_store(&env, 0u, 0x558c24u, 4, edx);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (!fl.zf)
        goto L_47ddb9;
L_47de0f:
    eax = lift_load(&env, 0u, 0x558c1cu, 4);
    edx = lift_load(&env, 0u, 0x558c2cu, 4);
    esi = lift_load(&env, ebp, 0x14u, 4);
    eax = eax + edx;
    edx = lift_load(&env, 0u, 0x558c30u, 4);
    lift_store(&env, 0u, 0x558c1cu, 4, eax);
    eax = lift_load(&env, 0u, 0x558c18u, 4);
    esi = esi - 1u;
    eax = eax + edx;
    lift_store(&env, ebp, 0x14u, 4, esi);
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    goto L_47dda4;
L_47de3f:
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47cfb0;
    ebx = ebx ^ ebx;
L_47de4a:
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0x14u, 4), &fl);
    }
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.zf)
        goto L_47deb7;
L_47de5f:
    eax = lift_load(&env, 0u, 0x558c18u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx & 0xf80000u;
    edx = edx & 0xf800u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x3u, &fl);
        edx = r;
    }
    edx = edx | ecx;
    ecx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx & 0xf8u;
    edx = edx | ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x3u, &fl);
        edx = r;
    }
    ecx = edx;
    edx = lift_load(&env, 0u, 0x558c1cu, 4);
    edx = edx + 0x2u;
    lift_store(&env, edx, 0xfffffffeu, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x558c1cu, 4, edx);
    edx = lift_load(&env, 0u, 0x558c24u, 4);
    eax = eax + 0x4u;
    edx = edx - 1u;
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    lift_store(&env, 0u, 0x558c24u, 4, edx);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (!fl.zf)
        goto L_47de5f;
L_47deb7:
    edx = lift_load(&env, 0u, 0x558c1cu, 4);
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    esi = lift_load(&env, ebp, 0x14u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x558c18u, 4);
    lift_store(&env, 0u, 0x558c1cu, 4, edx);
    edx = lift_load(&env, 0u, 0x558c30u, 4);
    esi = esi - 1u;
    eax = eax + edx;
    lift_store(&env, ebp, 0x14u, 4, esi);
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    goto L_47de4a;
L_47dee8:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c40u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47df9d;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c41u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_47df9d;
    ebx = ebx ^ ebx;
L_47df04:
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0x14u, 4), &fl);
    }
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.zf)
        goto L_47df6c;
L_47df19:
    eax = lift_load(&env, 0u, 0x558c18u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx & 0xe00000u;
    edx = edx & 0xe000u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0xau, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x5u, &fl);
        edx = r;
    }
    ecx = ecx | edx;
    edx = lift_load(&env, eax, 0x0u, 4);
    edx = edx & 0xc0u;
    eax = eax + 0x4u;
    edx = edx | ecx;
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        edx = r;
    }
    eax = lift_load(&env, 0u, 0x558c24u, 4);
    ecx = (ecx & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    edx = lift_load(&env, 0u, 0x558c0cu, 4);
    eax = eax - 1u;
    edx = edx + 1u;
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    lift_store(&env, edx, 0xffffffffu, 1, (ecx & 0xffu));
    lift_store(&env, 0u, 0x558c0cu, 4, edx);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (!fl.zf)
        goto L_47df19;
L_47df6c:
    esi = lift_load(&env, ebp, 0x14u, 4);
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    ecx = lift_load(&env, 0u, 0x558c0cu, 4);
    edx = lift_load(&env, 0u, 0x558c30u, 4);
    esi = esi - 1u;
    ecx = ecx + eax;
    eax = lift_load(&env, 0u, 0x558c18u, 4);
    lift_store(&env, 0u, 0x558c0cu, 4, ecx);
    eax = eax + edx;
    lift_store(&env, ebp, 0x14u, 4, esi);
    lift_store(&env, 0u, 0x558c18u, 4, eax);
    goto L_47df04;
L_47df9d:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c40u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_47e05d;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c41u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47e05d;
    ebx = ebx ^ ebx;
L_47dfb9:
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0x14u, 4), &fl);
    }
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.zf)
        goto L_47e02c;
L_47dfce:
    eax = lift_load(&env, 0u, 0x558c10u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xe0u) & 0xffu);
    ecx = edx;
    ecx = ecx & 0xffu;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
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
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x3u) & 0xffu);
    edi = lift_load(&env, 0u, 0x558c24u, 4);
    eax = eax + 1u;
    edx = edx & 0xffu;
    lift_store(&env, 0u, 0x558c10u, 4, eax);
    ecx = ecx | edx;
    edx = lift_load(&env, 0u, 0x558c14u, 4);
    edi = edi - 1u;
    edx = edx + 0x4u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        ecx = r;
    }
    lift_store(&env, 0u, 0x558c24u, 4, edi);
    lift_store(&env, edx, 0xfffffffcu, 4, ecx);
    lift_store(&env, 0u, 0x558c14u, 4, edx);
    {
        (void)lift_sub(32, ebx, edi, &fl);
    }
    if (!fl.zf)
        goto L_47dfce;
L_47e02c:
    eax = lift_load(&env, 0u, 0x558c14u, 4);
    edx = lift_load(&env, 0u, 0x558c2cu, 4);
    ecx = lift_load(&env, ebp, 0x14u, 4);
    eax = eax + edx;
    edx = lift_load(&env, 0u, 0x558c10u, 4);
    lift_store(&env, 0u, 0x558c14u, 4, eax);
    eax = lift_load(&env, 0u, 0x558c30u, 4);
    ecx = ecx - 1u;
    edx = edx + eax;
    lift_store(&env, ebp, 0x14u, 4, ecx);
    lift_store(&env, 0u, 0x558c10u, 4, edx);
    goto L_47dfb9;
L_47e05d:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x558c40u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_47cfb0;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, 0u, 0x558c41u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_47cfb0;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x558c43u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), ((edx >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_47e137;
    esi = esi ^ esi;
L_47e089:
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0x14u, 4), &fl);
    }
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.zf)
        goto L_47e107;
L_47e09e:
    eax = lift_load(&env, 0u, 0x558c20u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0xf8u) & 0xffu) << 8);
    ebx = edx;
    ecx = ecx ^ ecx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    ebx = ebx & 0xffffu;
    edx = edx & 0x7e0u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        ebx = r;
    }
    ecx = (ecx & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    ecx = ecx | ebx;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x1fu) & 0xffu);
    edi = lift_load(&env, 0u, 0x558c24u, 4);
    eax = eax + 0x2u;
    edx = edx & 0xffffu;
    lift_store(&env, 0u, 0x558c20u, 4, eax);
    ecx = ecx | edx;
    edx = lift_load(&env, 0u, 0x558c14u, 4);
    edi = edi - 1u;
    edx = edx + 0x4u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        ecx = r;
    }
    lift_store(&env, 0u, 0x558c24u, 4, edi);
    lift_store(&env, edx, 0xfffffffcu, 4, ecx);
    lift_store(&env, 0u, 0x558c14u, 4, edx);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (!fl.zf)
        goto L_47e09e;
L_47e107:
    eax = lift_load(&env, 0u, 0x558c14u, 4);
    edx = lift_load(&env, 0u, 0x558c2cu, 4);
    eax = eax + edx;
    edx = lift_load(&env, 0u, 0x558c30u, 4);
    lift_store(&env, 0u, 0x558c14u, 4, eax);
    eax = lift_load(&env, 0u, 0x558c20u, 4);
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0x14u, 4);
    edx = edx - 1u;
    lift_store(&env, 0u, 0x558c20u, 4, eax);
    lift_store(&env, ebp, 0x14u, 4, edx);
    goto L_47e089;
L_47e137:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47cfb0;
    ebx = ebx ^ ebx;
L_47e142:
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0x14u, 4), &fl);
    }
    if (fl.zf)
        goto L_47cfb0;
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, 0u, 0x558c24u, 4, eax);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.zf)
        goto L_47e1c3;
L_47e157:
    eax = lift_load(&env, 0u, 0x558c20u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0x7cu) & 0xffu) << 8);
    edx = edx & 0xffffu;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    ecx = ecx & 0x3e0u;
    ecx = ecx & 0xffffu;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        ecx = r;
    }
    ecx = ecx | edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x1fu) & 0xffu);
    edx = edx & 0xffffu;
    edx = edx | ecx;
    edi = lift_load(&env, 0u, 0x558c24u, 4);
    ecx = ((edx * 8u));
    eax = eax + 0x2u;
    edx = lift_load(&env, 0u, 0x558c14u, 4);
    edi = edi - 1u;
    edx = edx + 0x4u;
    lift_store(&env, 0u, 0x558c20u, 4, eax);
    lift_store(&env, 0u, 0x558c24u, 4, edi);
    lift_store(&env, edx, 0xfffffffcu, 4, ecx);
    lift_store(&env, 0u, 0x558c14u, 4, edx);
    {
        (void)lift_sub(32, ebx, edi, &fl);
    }
    if (!fl.zf)
        goto L_47e157;
L_47e1c3:
    edx = lift_load(&env, 0u, 0x558c14u, 4);
    eax = lift_load(&env, 0u, 0x558c2cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x558c30u, 4);
    lift_store(&env, 0u, 0x558c14u, 4, edx);
    edx = lift_load(&env, 0u, 0x558c20u, 4);
    edx = edx + eax;
    lift_store(&env, 0u, 0x558c20u, 4, edx);
    lift_store(&env, ebp, 0x14u, 4, lift_load(&env, ebp, 0x14u, 4) - 1u);
    goto L_47e142;
}

uint32_t lifted_f47eab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47EAB0_STACK + 4 + 4 * 3 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47EAB0_STACK, 3, entry);
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
    eax = lift_load(&env, ebp, 0x10u, 4);
    ecx = lift_load(&env, ebp, 0xcu, 4);
    ecx = ecx + 0xfffbu;
    {
        (void)lift_sub(32, ecx, 0x11u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_47eacc;
    {
        uint32_t i = ecx;
        switch (i)
        {
            case 0:
                goto L_47eacc;
            case 1:
                goto L_47eacc;
            case 2:
                goto L_47ead3;
            case 3:
                goto L_47eacc;
            case 4:
                goto L_47eaeb;
            case 5:
                goto L_47eacc;
            case 6:
                goto L_47eb2f;
            case 7:
                goto L_47eacc;
            case 8:
                goto L_47eacc;
            case 9:
                goto L_47eacc;
            case 10:
                goto L_47eacc;
            case 11:
                goto L_47eacc;
            case 12:
                goto L_47eb1b;
            case 13:
                goto L_47eacc;
            case 14:
                goto L_47eacc;
            case 15:
                goto L_47eb43;
            case 16:
                goto L_47eacc;
            case 17:
                goto L_47eb03;
            default:
                return 0u;
        }
    }
L_47eacc:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
L_47ead3:
    ecx = lift_load(&env, 0u, 0x558cccu, 4);
    ebx = lift_load(&env, ecx, 0x1c8u, 4);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_47eaeb:
    ecx = lift_load(&env, 0u, 0x558cccu, 4);
    ebx = lift_load(&env, ecx, 0x1c8u, 4);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_47eb03:
    ecx = lift_load(&env, 0u, 0x558cccu, 4);
    ebx = lift_load(&env, ecx, 0x1c8u, 4);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x10u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_47eb1b:
    ecx = lift_load(&env, 0u, 0x558cccu, 4);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47ed10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_47eb2f:
    ecx = lift_load(&env, 0u, 0x558cccu, 4);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47eeb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_47eb43:
    ecx = lift_load(&env, 0u, 0x558cccu, 4);
    ebx = lift_load(&env, ecx, 0x1c8u, 4);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x18u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
