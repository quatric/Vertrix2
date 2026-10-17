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
