/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_40.h"

uint32_t lifted_f4056c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4056C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4056C0_STACK, 0, entry);
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
    esp = esp - 0x88u;
    esi = edx;
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    edi = (ebp + 0xffffff6cu);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    ecx = (ebp + 0xffffffecu);
    ebx = (ebp + 0xffffff6cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x405720u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = esi + lift_load(&env, eax, 0x0u, 4);
    eax = eax ^ eax;
L_4056f3:
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edi, 0x0u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x0u, 2, (edx & 0xffffu));
    esi = esi + 0x2u;
    edi = edi + 0x4u;
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0x20u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4056f3;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t r = lift_add(32, lift_load(&env, eax, 0x0u, 4), 0x40u, &fl);
        lift_store(&env, eax, 0x0u, 4, r);
    }
    eax = ecx;
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

uint32_t lifted_f409f00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F409F00_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F409F00_STACK, 0, entry);
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
    esp = esp - 0x5cu;
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    lift_store(&env, ebp, 0xffffffb0u, 4, edx);
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    lift_store(&env, ebp, 0xfffffff4u, 4, edx);
    eax = lift_load(&env, 0u, 0x51f01cu, 4);
    edx = (eax + 0x125cu);
    lift_store(&env, ebp, 0xffffff9cu, 4, edx);
    eax = eax + 0x365cu;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    edx = ((ebx * 4u));
    eax = eax + edx;
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = ((edx * 8u));
    eax = eax + edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x9u, &fl);
        eax = r;
    }
    edi = lift_load(&env, ebp, 0xffffff9cu, 4);
    edi = edi + eax;
    esi = ((ebx * 8u));
    esi = esi + ebx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        esi = r;
    }
    edi = edi + esi;
    edx = 0u - edx;
    edx = edx + 1u;
    eax = ((edx * 8u));
    eax = eax + edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x9u, &fl);
        eax = r;
    }
    eax = eax + lift_load(&env, ebp, 0xffffff9cu, 4);
    esi = esi + eax;
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x14u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40a048;
L_409f7f:
    ebx = lift_load(&env, ebp, 0xffffffc0u, 4);
    ebx = lift_load(&env, ebx, 0x10u, 4);
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    eax = eax + 0x4u;
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
    edx = (esi + 0x48u);
    eax = (edi + 0x48u);
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    ecx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = ((ecx * 8u));
    eax = eax + ecx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffb4u, 4);
    ecx = ecx + eax;
    lift_store(&env, ebp, 0xffffffa4u, 4, ecx);
    eax = eax + 0x48u;
    ecx = lift_load(&env, ebp, 0xffffffb4u, 4);
    ecx = ecx + eax;
    {
        (void)lift_sub(32, ebx, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_40a09b;
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
L_409fd7:
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x40u, 4), &fl);
    }
    if (!fl.cf)
        goto L_40a13c;
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x523c20u;
    ebx = esi;
    edx = edi;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4095d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x5239e0u;
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4095d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, ebp, 0xffffffe4u, 4, lift_load(&env, ebp, 0xffffffe4u, 4) + 0x90u);
    lift_store(&env, ebp, 0xffffffd4u, 4, lift_load(&env, ebp, 0xffffffd4u, 4) + 0x90u);
    lift_store(&env, ebp, 0xfffffff0u, 4, lift_load(&env, ebp, 0xfffffff0u, 4) + 0x2u);
    lift_store(&env, ebp, 0xffffffe8u, 4, lift_load(&env, ebp, 0xffffffe8u, 4) + 0x8u);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) + 0x8u);
    lift_store(&env, ebp, 0xffffffd8u, 4, lift_load(&env, ebp, 0xffffffd8u, 4) + 0x90u);
    edi = edi + 0x90u;
    lift_store(&env, ebp, 0xffffffdcu, 4, lift_load(&env, ebp, 0xffffffdcu, 4) + 0x90u);
    esi = esi + 0x90u;
    goto L_409fd7;
L_40a048:
    lift_store(&env, ebp, 0xfffffff0u, 4, 0x2u);
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x523b00u;
    ebx = esi;
    edx = edi;
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4088e0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    eax = eax + 0x4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (esi + 0x48u);
    edx = (edi + 0x48u);
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    eax = eax + 0x48u;
    ecx = 0x5238c0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4088e0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edi = edi + 0x90u;
    esi = esi + 0x90u;
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    eax = eax + 0x8u;
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    goto L_409f7f;
L_40a09b:
    eax = ((ebx * 8u));
    eax = eax + ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    ebx = 0x523b00u;
    ebx = ebx + eax;
    lift_store(&env, ebp, 0xffffffb8u, 4, ebx);
    ebx = 0x5238c0u;
    ebx = ebx + eax;
    lift_store(&env, ebp, 0xffffffbcu, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_40a0d3:
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x40u, 4), &fl);
    }
    if (!fl.cf)
        goto L_40a13c;
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0xffffffb8u, 4);
    ebx = esi;
    edx = edi;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4088e0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0xffffffbcu, 4);
    ebx = lift_load(&env, ebp, 0xffffffc8u, 4);
    edx = lift_load(&env, ebp, 0xffffffc4u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4088e0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, ebp, 0xffffffe0u, 4, lift_load(&env, ebp, 0xffffffe0u, 4) + 0x90u);
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) + 0x90u);
    lift_store(&env, ebp, 0xfffffff0u, 4, lift_load(&env, ebp, 0xfffffff0u, 4) + 0x2u);
    lift_store(&env, ebp, 0xffffffccu, 4, lift_load(&env, ebp, 0xffffffccu, 4) + 0x8u);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) + 0x8u);
    lift_store(&env, ebp, 0xffffffc4u, 4, lift_load(&env, ebp, 0xffffffc4u, 4) + 0x90u);
    edi = edi + 0x90u;
    lift_store(&env, ebp, 0xffffffc8u, 4, lift_load(&env, ebp, 0xffffffc8u, 4) + 0x90u);
    esi = esi + 0x90u;
    goto L_40a0d3;
L_40a13c:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    eax = eax + 0x900u;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    ebx = 0x4u;
L_40a14c:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xfffffff0u, 4), 0x20u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_40a17e;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
L_40a158:
    edx = edi;
    edi = edi + 0x4u;
    edx = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
    lift_store(&env, esi, 0x0u, 4, 0x0u);
    esi = esi + 0x4u;
    eax = eax + 0x80u;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.zf)
        goto L_40a158;
    lift_store(&env, ebp, 0xfffffff0u, 4, lift_load(&env, ebp, 0xfffffff0u, 4) + 1u);
    lift_store(&env, ebp, 0xffffffd0u, 4, lift_load(&env, ebp, 0xffffffd0u, 4) + ebx);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) + ebx);
    goto L_40a14c;
L_40a17e:
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

uint32_t lifted_mixer_effect_select(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_MIXER_EFFECT_SELECT_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_MIXER_EFFECT_SELECT_STACK, 0, entry);
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
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x3u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_40dc63;
L_40dc58:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x3u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x24u, &fl);
    }
    if (fl.cf)
        goto L_40dc6c;
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
L_40dc63:
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x4u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_40dc58;
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
L_40dc6c:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    vertrix_lift_fl = fl;
    eax =
        lift_call(&env, lift_load(&env, 0u, (edx * 4u) + 0x4f7444u, 4), eax, edx, ebx, ecx, 0, esp);
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
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_rtl_square_root(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_SQUARE_ROOT_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_SQUARE_ROOT_STACK, 0, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
    esp = esp - 0x8u;
    lift_store(&env, ebp, 0xfffffff8u, 4, eax);
    lift_store(&env, ebp, 0xfffffffcu, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c9b2f;
    edx = (ebp + 0xfffffff8u);
    eax = 0x2043u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dad2eu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c9b5a;
L_4c9b2f:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5054a1u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c9b4e;
    eax = lift_load(&env, ebp, 0xfffffff8u, 4);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    ebp = esp;
    lift_x87(&env, 0x4c9b40);
    lift_x87(&env, 0x4c9b43);
    lift_x87(&env, 0x4c9b45);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    goto L_4c9b5a;
L_4c9b4e:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4c9b60;
    eax = lift_load(&env, ebp, 0xfffffff8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db10au, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c9b5a:
    lift_store(&env, ebp, 0xfffffff8u, 4, eax);
    lift_store(&env, ebp, 0xfffffffcu, 4, edx);
L_4c9b60:
    eax = lift_load(&env, ebp, 0xfffffff8u, 4);
    edx = lift_load(&env, ebp, 0xfffffffcu, 4);
    esp = ebp;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}
