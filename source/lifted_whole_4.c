/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_4.h"

uint32_t lifted_f4b2a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B2A00_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B2A00_STACK, 0, entry);
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
    esp = esp - 0x6cu;
    esi = eax;
    lift_store(&env, ebp, 0xffffffa0u, 4, edx);
    edx = edx ^ edx;
    edi = (eax + 0x15cu);
    lift_store(&env, ebp, 0xffffff9cu, 4, edx);
    edi = lift_load(&env, edi, 0x0u, 4);
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffacu, 4, edi);
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
    eax = (ecx + 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, esi, 0x304u, 4);
    edi = eax;
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b2aef;
    {
        (void)lift_sub(32, ecx, lift_load(&env, esi, 0x2fcu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4b2aef;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x161u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe0u, 1, (eax & 0xffu));
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffecu, 1, ((eax >> 8) & 0xffu));
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b2aef;
L_4b2a69:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    eax = eax + eax;
    ebx = ebx ^ ebx;
    ecx = (esi + eax);
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x162u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    edx = edx + eax;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    lift_store(&env, edi, eax + 0x0u, 1, 0x0u);
    eax = (ebp + 0xffffffc8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffb0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff88u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff84u);
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
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    eax = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
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
    eax = lift_load(&env, ebp, 0xffffff84u, 4);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b2c74;
L_4b2ad9:
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu) << 8);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) + 1u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    lift_store(&env, ebp, 0xffffffecu, 1, ((edx >> 8) & 0xffu));
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.cf)
        goto L_4b2a69;
L_4b2aef:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x300u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b2c7b;
    ebx = ebx ^ ebx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x161u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffd4u, 2, (ebx & 0xffffu));
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe4u, 1, (eax & 0xffu));
    lift_store(&env, ebp, 0xffffffe8u, 1, ((ebx >> 8) & 0xffu));
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b2ba0;
L_4b2b18:
    ecx = ecx ^ ecx;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    edx = edx ^ edx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, (ecx * 2u) + 0x162u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, esi, (ecx * 2u) + 0x22au, 2)) & 0xffffu);
    edx = edx + eax;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, (ecx * 2u) + 0x22au, 2)) & 0xffffu);
    lift_store(&env, edi, eax + 0x0u, 1, 0x0u);
    eax = (ebp + 0xffffffb4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffc0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff94u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff8cu);
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
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    eax = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
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
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + 1u;
    ecx = ecx + eax;
    lift_store(&env, ebp, 0xffffffd4u, 2, (ecx & 0xffffu));
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu) << 8);
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + 1u) & 0xffu) << 8);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe8u, 1, ((ecx >> 8) & 0xffu));
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.cf)
        goto L_4b2b18;
L_4b2ba0:
    edx = lift_load(&env, esi, 0xf6u, 4);
    eax = lift_load(&env, ebp, 0xffffffd2u, 4);
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
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x2f6u, 2)) & 0xffffu);
    edx = edx - eax;
    eax = edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x2f8u, 2)) & 0xffffu);
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
    edx = eax;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b2c7b;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x16u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) + lift_load(&env, esi, 0x2f6u, 2)) & 0xffffu);
L_4b2be8:
    eax = eax + edx;
    lift_store(&env, ebp, 0xffffffccu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xeu, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, esi, 0x2f2u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    eax = eax + ecx;
    lift_store(&env, ebp, 0xffffffd8u, 1, (edx & 0xffu));
    lift_store(&env, ebp, 0xffffffbcu, 2, (eax & 0xffffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x161u, 1)) & 0xffu);
    edx = lift_load(&env, esi, 0x2fcu, 4);
    lift_store(&env, ebp, 0xffffffdcu, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b2c55;
    {
        (void)lift_sub(32, edx, lift_load(&env, esi, 0x304u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4b2c8b;
    ebx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = lift_load(&env, esi, 0xf2u, 4);
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x2f2u, 2)) & 0xffffu);
    eax = eax - ebx;
    eax = eax - edx;
    edx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x2f4u, 2)) & 0xffffu);
    edx = edx - eax;
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b2c55;
    lift_store(&env, ebp, 0xffffffbcu, 2, lift_load(&env, ebp, 0xffffffbcu, 2) + (eax & 0xffffu));
L_4b2c55:
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
L_4b2c58:
    lift_store(&env, ebp, 0xffffffd0u, 2, (eax & 0xffffu));
L_4b2c5c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), lift_load(&env, ebp, 0xffffffdcu, 1), &fl);
    }
    if (fl.cf)
        goto L_4b2ca4;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
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
L_4b2c74:
    eax = edx;
    goto L_4b2ad9;
L_4b2c7b:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x16u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x2f6u, 2)) & 0xffffu);
    goto L_4b2be8;
L_4b2c8b:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xeu, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0xf4u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, esi, 0x2f4u, 2)) & 0xffffu);
    eax = eax + edx;
    eax = eax - ebx;
    eax = eax - 1u;
    goto L_4b2c58;
L_4b2ca4:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    eax = eax + eax;
    ebx = ebx ^ ebx;
    ecx = (esi + eax);
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x162u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    edx = edx + eax;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    lift_store(&env, edi, eax + 0x0u, 1, 0x0u);
    eax = (ebp + 0xffffffb8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffc4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff98u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff90u);
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
    eax = lift_load(&env, ebp, 0xffffffcau, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    ecx = eax;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffbau, 4);
    ebx = lift_load(&env, ebp, 0xffffffceu, 4);
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
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
    eax = lift_load(&env, esi, 0x15du, 4);
    edx = lift_load(&env, ebp, 0xffffffa8u, 4);
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
    ecx = lift_load(&env, esi, 0x304u, 4);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b2d62;
    {
        (void)lift_sub(32, ecx, lift_load(&env, esi, 0x2fcu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4b2d62;
    ecx = lift_load(&env, ebp, 0xffffffa4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    edx = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x440a20u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_4b2d48:
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    eax = eax + 1u;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) + 1u) & 0xffu);
    edx = edx + eax;
    lift_store(&env, ebp, 0xffffffd8u, 1, (ebx & 0xffu));
    lift_store(&env, ebp, 0xffffffccu, 2, (edx & 0xffffu));
    goto L_4b2c5c;
L_4b2d62:
    eax = lift_load(&env, ebp, 0xffffffcau, 4);
    ecx = lift_load(&env, ebp, 0xffffffceu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, ebp, 0xffffffbau, 4);
    edx = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
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
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x440ca0u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    goto L_4b2d48;
}

uint32_t lifted_f4b2d90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B2D90_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B2D90_STACK, 0, entry);
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
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    edi = lift_load(&env, eax, 0x15cu, 4);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffacu, 4, edi);
    lift_store(&env, ebp, 0xffffffb0u, 4, edx);
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
    edx = 0x1u;
    eax = (ecx + 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    ecx = lift_load(&env, eax, 0x304u, 4);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b2e84;
    {
        (void)lift_sub(32, ecx, lift_load(&env, eax, 0x2fcu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4b2e84;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x161u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 1, (eax & 0xffu));
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd8u, 1, ((eax >> 8) & 0xffu));
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b2e84;
    edi = lift_load(&env, ebp, 0xffffffacu, 4);
L_4b2dfc:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    ecx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = eax + eax;
    ebx = ebx ^ ebx;
    ecx = ecx + eax;
    edx = edx ^ edx;
    eax = esi;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x162u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    edx = edx + edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    lift_store(&env, esi, eax + 0x0u, 1, 0x0u);
    eax = (ebp + 0xffffffbcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffb4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff90u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff8cu);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x44u, 1)) & 0xffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    eax = lift_load(&env, edx, 0x15du, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    eax = lift_load(&env, ebp, 0xffffff8cu, 4);
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b3035;
L_4b2e6e:
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu) << 8);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) + 1u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    lift_store(&env, ebp, 0xffffffd8u, 1, ((edx >> 8) & 0xffu));
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.cf)
        goto L_4b2dfc;
L_4b2e84:
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x300u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b304c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x161u, 1)) & 0xffu);
    edi = edi ^ edi;
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe4u, 1, (eax & 0xffu));
    lift_store(&env, ebp, 0xffffffdcu, 1, ((ebx >> 8) & 0xffu));
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b2f30;
L_4b2eac:
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffdcu, 1)) & 0xffu);
    ebx = lift_load(&env, ebp, 0xffffff9cu, 4);
    ecx = ecx + ecx;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    ecx = ecx + ebx;
    edx = edx ^ edx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x162u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    edx = edx + eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    lift_store(&env, esi, eax + 0x0u, 1, 0x0u);
    eax = (ebp + 0xffffffb8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffd0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff98u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff94u);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x44u, 1)) & 0xffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    eax = lift_load(&env, edx, 0x15du, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffdcu, 1)) & 0xffu) << 8);
    eax = eax + 1u;
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + 1u) & 0xffu) << 8);
    edi = edi + eax;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffdcu, 1, ((ecx >> 8) & 0xffu));
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.cf)
        goto L_4b2eac;
L_4b2f30:
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    edx = lift_load(&env, edx, 0xf6u, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)(edi & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx - eax;
    ecx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x2f6u, 2)) & 0xffffu);
    eax = eax - edx;
    edx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x2f8u, 2)) & 0xffffu);
    edx = edx - eax;
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
    edi = eax;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b303c;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) + lift_load(&env, ecx, 0x2f6u, 2)) & 0xffffu);
    edi = edi + eax;
L_4b2f7f:
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xeu, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, edx, 0x2f2u, 2)) & 0xffffu);
    eax = eax + ebx;
    lift_store(&env, ebp, 0xffffffc8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x161u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe0u, 1, (eax & 0xffu));
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    lift_store(&env, ebp, 0xffffffd4u, 1, (edx & 0xffu));
    edx = lift_load(&env, eax, 0x2fcu, 4);
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b2ff6;
    {
        (void)lift_sub(32, edx, lift_load(&env, eax, 0x304u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4b305c;
    ebx = lift_load(&env, ebp, 0xffffffb0u, 4);
    ecx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = lift_load(&env, eax, 0xf2u, 4);
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x2f2u, 2)) & 0xffffu);
    eax = eax - ebx;
    eax = eax - edx;
    edx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x2f4u, 2)) & 0xffffu);
    edx = edx - eax;
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b2ff6;
    lift_store(&env, ebp, 0xffffffc8u, 2, lift_load(&env, ebp, 0xffffffc8u, 2) + (eax & 0xffffu));
L_4b2ff6:
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
L_4b2ff9:
    lift_store(&env, ebp, 0xffffffc4u, 2, (eax & 0xffffu));
L_4b2ffd:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), lift_load(&env, ebp, 0xffffffe0u, 1), &fl);
    }
    if (fl.cf)
        goto L_4b3078;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = lift_load(&env, eax, 0x14u, 4);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edi & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx - eax;
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        (void)lift_sub(32, edx, lift_load(&env, eax, 0xf8u, 4), &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.cf || fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
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
L_4b3035:
    eax = edx;
    goto L_4b2e6e;
L_4b303c:
    edi = (edi & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) + lift_load(&env, ecx, 0x2f6u, 2)) & 0xffffu);
    goto L_4b2f7f;
L_4b304c:
    edi = (edi & 0xffff0000u) | ((lift_load(&env, eax, 0x16u, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) + lift_load(&env, eax, 0x2f6u, 2)) & 0xffffu);
    goto L_4b2f7f;
L_4b305c:
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xeu, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, edx, 0xf4u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, edx, 0x2f4u, 2)) & 0xffffu);
    eax = eax + ecx;
    eax = eax - ebx;
    eax = eax - 1u;
    goto L_4b2ff9;
L_4b3078:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    ecx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = eax + eax;
    ebx = ebx ^ ebx;
    ecx = ecx + eax;
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x162u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    edx = edx + eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x22au, 2)) & 0xffffu);
    lift_store(&env, esi, eax + 0x0u, 1, 0x0u);
    eax = (ebp + 0xffffffc0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffccu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffa4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffa0u);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    ebx = lift_load(&env, ebp, 0xffffffc2u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x44u, 1)) & 0xffu);
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
    eax = lift_load(&env, ebp, 0xffffffc6u, 4);
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edi & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
    eax = lift_load(&env, edx, 0x15du, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0xffffffa8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) + 1u) & 0xffu);
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffd4u, 1, (ebx & 0xffu));
    edi = edi + eax;
    goto L_4b2ffd;
}
