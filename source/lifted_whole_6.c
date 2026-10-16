/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_6.h"

uint32_t lifted_f4d7140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D7140_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D7140_STACK, 0, entry);
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
    esi = eax;
    edi = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0xd0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce760u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d7197;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x58u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d7197;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x4cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d7174;
    edx = esi;
    edi = lift_load(&env, eax, 0x0u, 4);
    ecx = lift_load(&env, esi, 0x58u, 4);
    ebx = lift_load(&env, esi, 0x4cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x18u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4d7181;
L_4d7174:
    edx = esi;
    edi = lift_load(&env, eax, 0x0u, 4);
    ecx = lift_load(&env, esi, 0x58u, 4);
    ebx = lift_load(&env, esi, 0x40u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x14u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4d7181:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d7197;
    edx = 0xffffffffu;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d70e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d7197:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d71c9;
    {
        (void)lift_and(8, lift_load(&env, esi, 0x25u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4d71c9;
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
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19c4u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d71c9;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cce60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
L_4d71c9:
    eax = ebx;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_rtl_sign_compare(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_SIGN_COMPARE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_SIGN_COMPARE_STACK, 0, entry);
    {
        uint32_t r = lift_xor(32, eax, edx, &fl);
        eax = r;
    }
    if (fl.sf)
        goto L_4d8092;
    eax = eax ^ edx;
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4d809b;
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = edx ^ eax;
    {
        uint32_t a = edx;
        edx = (~a) & lift_mask(4);
    }
L_4d8092:
    eax = eax - eax;
    {
        uint32_t r = lift_add(32, edx, edx, &fl);
        edx = r;
    }
    eax = eax + eax + fl.cf;
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
L_4d809b:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d80d5(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D80D5_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D80D5_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx - ecx;
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) + (ecx & 0xffu) + fl.cf) & 0xffu);
    ecx = (ecx & 0xffff00ffu) | ((((ecx & 0xffu)) & 0xffu) << 8);
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) + (ecx & 0xffu)) & 0xffu);
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) + (ecx & 0xffu)) & 0xffu);
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) + ((ecx >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_rol(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_adc(8, (ecx & 0xffu), 0x0u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_rol(32, a, 0x8u, &fl);
        edx = r;
    }
    ebx = (ebx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    ebx = (ebx & 0xffff00ffu) | ((((edx & 0xffu)) & 0xffu) << 8);
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    fl.cf = 1;
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = (edx & 0xffffff00u) | ((0x0u) & 0xffu);
    fl.cf = 1;
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    ecx = (ecx & 0xffff00ffu) | ((((ebx & 0xffu)) & 0xffu) << 8);
    {
        uint32_t r = lift_sub(8, (ebx & 0xffu), ((ebx >> 8) & 0xffu), &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    if (fl.zf)
        goto L_4d811d;
    if (!fl.cf)
        goto L_4d810e;
    ecx = (ecx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    ebx = (ebx & 0xffffff00u) | ((0u - (ebx & 0xffu)) & 0xffu);
    {
        uint32_t t = edx;
        edx = eax;
        eax = t;
    }
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) ^ 0x4u) & 0xffu);
L_4d810e:
    {
        uint32_t t = (ecx & 0xffu);
        ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
        ebx = (ebx & 0xffffff00u) | ((t) & 0xffu);
    }
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x20u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4d8119;
    edx = edx - edx;
    goto L_4d811b;
L_4d8119:
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, (ecx & 0xffu), &fl);
        edx = r;
    }
L_4d811b:
    {
        uint32_t t = (ecx & 0xffu);
        ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
        ebx = (ebx & 0xffffff00u) | ((t) & 0xffu);
    }
L_4d811d:
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_shr(8, a, 0x1u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    if (fl.cf)
        goto L_4d8133;
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    if (!fl.cf)
        goto L_4d8131;
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = ((ecx >> 8) & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    if (!fl.zf)
        goto L_4d8131;
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_ror(8, a, 0x1u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    goto L_4d8170;
L_4d8131:
    goto L_4d8146;
L_4d8133:
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_shr(8, a, 0x1u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    if (!fl.cf)
        goto L_4d813f;
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) + 1u) & 0xffu);
    eax = 0u - eax;
    goto L_4d8146;
L_4d813f:
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4d8146;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d8146:
    {
        uint32_t r = lift_add(32, eax, 0x80u, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    if (!fl.cf)
        goto L_4d8153;
    {
        uint32_t a = ((ecx >> 8) & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    goto L_4d815d;
L_4d8153:
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    if (fl.cf)
        goto L_4d815d;
    {
        uint32_t a = ((ecx >> 8) & 0xffu);
        uint32_t r = lift_dec(8, a, &fl, 1);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    if (!fl.zf)
        goto L_4d8153;
    goto L_4d8169;
L_4d815d:
    eax = (eax & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_ror(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_ror(8, a, 0x1u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
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
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d8169:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    goto L_4e236e;
L_4d8170:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    goto L_4e23b5;
L_4e236e:
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e23b5:
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae94u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x84u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    eax = eax & 0x80000000u;
    {
        uint32_t r = lift_or(32, eax, 0x7f800000u, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d8198(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8198_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8198_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    ecx = ecx + ecx + fl.cf;
    {
        uint32_t r = lift_add(32, edx, edx, &fl);
        edx = r;
    }
    ecx = ecx + 0x0u + fl.cf;
    {
        uint32_t a = ecx;
        uint32_t r = lift_ror(32, a, 0x1u, &fl);
        ecx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rol(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_rol(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - 0x7fu) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) - 0x7fu) & 0xffu);
    {
        uint32_t r = lift_add(8, (edx & 0xffu), (eax & 0xffu), &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    if (!fl.of)
        goto L_4d81b7;
    if (fl.sf)
        goto L_4d81f6;
    goto L_4d81f0;
L_4d81b7:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x81u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4d81f0;
    {
        uint32_t r = lift_add(8, (edx & 0xffu), 0x80u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    ecx = (ecx & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    edx = (edx & 0xffffff00u) | ((0x0u) & 0xffu);
    fl.cf = 1;
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    fl.cf = 1;
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    lift_mul1(32, edx, &eax, &edx, &fl);
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (fl.sf)
        goto L_4d81d5;
    edx = edx + edx;
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) - 1u) & 0xffu);
L_4d81d5:
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_adc(32, edx, 0x0u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_adc(8, (ecx & 0xffu), 0x0u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    if (fl.zf)
        goto L_4d81f6;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x9u, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | (((ecx & 0xffu)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_ror(32, a, 0x8u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d81f0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    goto L_4e236e;
L_4d81f6:
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    goto L_4e23b5;
L_4e236e:
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e23b5:
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae94u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x84u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    eax = eax & 0x80000000u;
    {
        uint32_t r = lift_or(32, eax, 0x7f800000u, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_rtl_single_divide_software_full(const VertrixCalls *calls,
                                                const VertrixFactoryServices *services,
                                                const VertrixGlobals *globals,
                                                const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_SINGLE_DIVIDE_SOFTWARE_FULL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_SINGLE_DIVIDE_SOFTWARE_FULL_STACK,
               0, entry);
    {
        uint32_t r = lift_add(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4d8230;
    goto L_4e23a9;
L_4d8230:
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx + ecx + fl.cf;
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4d8239;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d8239:
    ecx = ecx + 0x0u + fl.cf;
    {
        uint32_t a = ecx;
        uint32_t r = lift_ror(32, a, 0x1u, &fl);
        ecx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rol(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_rol(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - 0x7fu) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) - 0x7fu) & 0xffu);
    {
        uint32_t r = lift_sub(8, (eax & 0xffu), (edx & 0xffu), &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    if (!fl.of)
        goto L_4d8255;
    if (!fl.sf)
        goto L_4d8299;
    {
        uint32_t r = lift_add(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    goto L_4d829f;
L_4d8255:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x81u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4d8299;
    {
        uint32_t r = lift_add(8, (eax & 0xffu), 0x7fu, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    ecx = (ecx & 0xffff00ffu) | ((((eax & 0xffu)) & 0xffu) << 8);
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    edx = (edx & 0xffffff00u) | ((0x0u) & 0xffu);
    fl.cf = 1;
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    fl.cf = 1;
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = edx;
    edx = eax;
    eax = eax - eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    lift_div1(32, ecx, &eax, &edx, &fl);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (fl.sf)
        goto L_4d827b;
    eax = eax + eax;
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) - 1u) & 0xffu) << 8);
L_4d827b:
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, eax, 0x0u, &fl);
        eax = r;
    }
    if (!fl.cf)
        goto L_4d828b;
    {
        uint32_t a = ((ecx >> 8) & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    if (!fl.zf)
        goto L_4d828b;
    eax = ecx;
    goto L_4d829f;
L_4d828b:
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x9u, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_ror(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d8299:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    goto L_4e236e;
L_4d829f:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    goto L_4e23b5;
L_4e236e:
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e23a9:
    eax = 0x83u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e23c6;
L_4e23b5:
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae94u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x84u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
L_4e23c6:
    eax = eax & 0x80000000u;
    {
        uint32_t r = lift_or(32, eax, 0x7f800000u, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_destroy_g(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_DESTROY_G_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_DESTROY_G_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x30u;
    ecx = eax;
    {
        (void)lift_and(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4d8baf;
    lift_store(&env, esp, 0x20u, 4, 0x1u);
    edx = 0x516f80u;
    lift_store(&env, esp, 0x0u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4d8c13;
L_4d8baf:
    lift_store(&env, eax, 0x0u, 4, 0x51a1b4u);
    lift_store(&env, esp, 0x24u, 4, eax);
    eax = (esp + 0x14u);
    lift_store(&env, esp, 0x28u, 1, (edx & 0xffu));
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
    lift_store(&env, esp, 0x18u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x1cu, 4, 0x51a128u);
    eax = ecx;
    lift_store(&env, esp, 0x20u, 4, 0x3u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8b30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    {
        (void)lift_and(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4d8c09;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4d8c09:
    eax = lift_load(&env, esp, 0x14u, 4);
    env.chain = eax;
L_4d8c13:
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x30u, &fl);
        esp = r;
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

uint32_t lifted_node_pool_take_initialised(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_NODE_POOL_TAKE_INITIALISED_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_NODE_POOL_TAKE_INITIALISED_STACK, 0,
               entry);
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
    esi = eax;
    ebp = edx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4d8c60;
    {
        uint32_t v = 0xcu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x18u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax + 0x14u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e23e0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    ecx = lift_load(&env, esi, 0x18u, 4);
    ecx = ecx - 1u;
    {
        uint32_t r = lift_imul(32, ecx, 0xcu, &fl);
        edx = r;
    }
    eax = eax + 0x4u;
    eax = eax + edx;
    edx = ecx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4d8c60;
L_4d8c4e:
    ecx = lift_load(&env, esi, 0x10u, 4);
    lift_store(&env, eax, 0x0u, 4, ecx);
    edx = edx - 1u;
    lift_store(&env, esi, 0x10u, 4, eax);
    eax = eax - 0xcu;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4d8c4e;
L_4d8c60:
    edi = lift_load(&env, esi, 0x10u, 4);
    eax = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, esi, 0x10u, 4, eax);
    lift_store(&env, edi, 0x4u, 4, ebp);
    lift_store(&env, edi, 0x0u, 4, ebx);
    ebx = 0x4u;
    lift_store(&env, esi, 0xcu, 4, lift_load(&env, esi, 0xcu, 4) + 1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = (edi + 0x8u);
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d9ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D9AE0_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D9AE0_STACK, 1, entry);
    edx = lift_load(&env, esp, 0x4u, 4);
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x41u, &fl);
    }
    if (fl.cf)
        goto L_4d9d50;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x7du, &fl);
    }
    if (fl.cf)
        goto L_4d9c6a;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0xb7u, &fl);
    }
    if (fl.cf)
        goto L_4d9bd4;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x10bu, &fl);
    }
    if (fl.cf)
        goto L_4d9ba0;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0x3e4u, &fl);
    }
    if (fl.cf)
        goto L_4d9b90;
    if (fl.cf || fl.zf)
        goto L_4d9b60;
    {
        (void)lift_sub(32, edx, 0x3e5u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9b60;
    {
        (void)lift_sub(32, edx, 0x3e7u, &fl);
    }
    if (fl.zf)
        goto L_4d9b48;
    goto L_4d9b88;
L_4d9b38:
    eax = 0x2u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9b40:
    eax = 0x3u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9b48:
    eax = 0x5u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9b50:
    eax = 0x6u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9b58:
    eax = 0x7u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9b60:
    eax = 0xau;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9b68:
    eax = 0xbu;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9b70:
    eax = 0xcu;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9b78:
    eax = 0xeu;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9b80:
    eax = 0x8u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9b88:
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9b90:
    {
        (void)lift_sub(32, edx, 0x3e3u, &fl);
    }
    if (fl.zf)
        goto L_4d9b60;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9ba0:
    {
        (void)lift_sub(32, edx, 0xc1u, &fl);
    }
    if (fl.cf)
        goto L_4d9bc4;
    if (fl.cf || fl.zf)
        goto L_4d9b50;
    {
        (void)lift_sub(32, edx, 0xceu, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0xd0u, &fl);
    }
    if (fl.zf)
        goto L_4d9b40;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9bc4:
    {
        (void)lift_sub(32, edx, 0xbfu, &fl);
    }
    if (fl.zf)
        goto L_4d9b50;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9bd4:
    {
        (void)lift_sub(32, edx, 0x9au, &fl);
    }
    if (fl.cf)
        goto L_4d9c22;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0xa7u, &fl);
    }
    if (fl.cf)
        goto L_4d9c0e;
    if (fl.cf || fl.zf)
        goto L_4d9b70;
    {
        (void)lift_sub(32, edx, 0xaau, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0xb6u, &fl);
    }
    if (fl.zf)
        goto L_4d9b50;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9c0e:
    {
        (void)lift_sub(32, edx, 0xa1u, &fl);
    }
    if (fl.zf)
        goto L_4d9b40;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9c22:
    {
        (void)lift_sub(32, edx, 0x84u, &fl);
    }
    if (fl.cf)
        goto L_4d9c56;
    if (fl.cf || fl.zf)
        goto L_4d9e6a;
    {
        (void)lift_sub(32, edx, 0x90u, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0x91u, &fl);
    }
    if (fl.zf)
        goto L_4d9b58;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9c56:
    {
        (void)lift_sub(32, edx, 0x83u, &fl);
    }
    if (fl.zf)
        goto L_4d9e6a;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9c6a:
    {
        (void)lift_sub(32, edx, 0x58u, &fl);
    }
    if (fl.cf)
        goto L_4d9ce0;
    if (fl.cf || fl.zf)
        goto L_4d9b60;
    {
        (void)lift_sub(32, edx, 0x71u, &fl);
    }
    if (fl.cf)
        goto L_4d9cad;
    if (fl.cf || fl.zf)
        goto L_4d9ee7;
    {
        (void)lift_sub(32, edx, 0x75u, &fl);
    }
    if (fl.cf)
        goto L_4d9c9c;
    if (fl.cf || fl.zf)
        goto L_4d9b60;
    {
        (void)lift_sub(32, edx, 0x7bu, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    eax = 0x3u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9c9c:
    {
        (void)lift_sub(32, edx, 0x72u, &fl);
    }
    if (fl.zf)
        goto L_4d9b50;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9cad:
    {
        (void)lift_sub(32, edx, 0x6cu, &fl);
    }
    if (fl.cf)
        goto L_4d9ccf;
    if (fl.cf || fl.zf)
        goto L_4d9b70;
    {
        (void)lift_sub(32, edx, 0x6fu, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
L_4d9cc7:
    eax = 0xdu;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9ccf:
    {
        (void)lift_sub(32, edx, 0x6bu, &fl);
    }
    if (fl.zf)
        goto L_4d9b38;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9ce0:
    {
        (void)lift_sub(32, edx, 0x47u, &fl);
    }
    if (fl.cf)
        goto L_4d9d27;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x52u, &fl);
    }
    if (fl.cf)
        goto L_4d9d16;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x55u, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0x56u, &fl);
    }
    if (fl.zf)
        goto L_4d9b48;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9d16:
    {
        (void)lift_sub(32, edx, 0x50u, &fl);
    }
    if (fl.zf)
        goto L_4d9b48;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9d27:
    {
        (void)lift_sub(32, edx, 0x43u, &fl);
    }
    if (fl.cf)
        goto L_4d9b50;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0x44u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9ee7;
    {
        (void)lift_sub(32, edx, 0x46u, &fl);
    }
    if (fl.zf)
        goto L_4d9b40;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9d50:
    {
        (void)lift_sub(32, edx, 0x1au, &fl);
    }
    if (fl.cf)
        goto L_4d9e42;
    if (fl.cf || fl.zf)
        goto L_4d9b50;
    {
        (void)lift_sub(32, edx, 0x34u, &fl);
    }
    if (fl.cf)
        goto L_4d9dcd;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0x3au, &fl);
    }
    if (fl.cf)
        goto L_4d9da4;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x3cu, &fl);
    }
    if (fl.cf)
        goto L_4d9b60;
    if (fl.cf || fl.zf)
        goto L_4d9b50;
    {
        (void)lift_sub(32, edx, 0x3eu, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b80;
    {
        (void)lift_sub(32, edx, 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4d9b48;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9da4:
    {
        (void)lift_sub(32, edx, 0x36u, &fl);
    }
    if (fl.cf)
        goto L_4d9b40;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x37u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0x39u, &fl);
    }
    if (fl.zf)
        goto L_4d9b60;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9dcd:
    {
        (void)lift_sub(32, edx, 0x21u, &fl);
    }
    if (fl.cf)
        goto L_4d9e14;
    if (fl.cf || fl.zf)
        goto L_4d9b70;
    {
        (void)lift_sub(32, edx, 0x24u, &fl);
    }
    if (fl.cf)
        goto L_4d9e03;
    if (fl.cf || fl.zf)
        goto L_4d9ee7;
    {
        (void)lift_sub(32, edx, 0x26u, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b78;
    {
        (void)lift_sub(32, edx, 0x27u, &fl);
    }
    if (fl.zf)
        goto L_4d9cc7;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9e03:
    {
        (void)lift_sub(32, edx, 0x22u, &fl);
    }
    if (fl.zf)
        goto L_4d9b40;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9e14:
    {
        (void)lift_sub(32, edx, 0x1du, &fl);
    }
    if (fl.cf)
        goto L_4d9e35;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x1eu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9e6a;
    {
        (void)lift_sub(32, edx, 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4d9b68;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9e35:
    {
        (void)lift_sub(32, edx, 0x1bu, &fl);
    }
    if (fl.zf)
        goto L_4d9e6a;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9e42:
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.cf)
        goto L_4d9e92;
    if (fl.cf || fl.zf)
        goto L_4d9b58;
    {
        (void)lift_sub(32, edx, 0x15u, &fl);
    }
    if (fl.cf)
        goto L_4d9e72;
    if (fl.cf || fl.zf)
        goto L_4d9b60;
    {
        (void)lift_sub(32, edx, 0x17u, &fl);
    }
    if (fl.cf)
        goto L_4d9b60;
    if (fl.cf || fl.zf)
        goto L_4d9b60;
    {
        (void)lift_sub(32, edx, 0x18u, &fl);
    }
L_4d9e6a:
    eax = 0x9u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9e72:
    {
        (void)lift_sub(32, edx, 0x12u, &fl);
    }
    if (fl.cf)
        goto L_4d9b40;
    if (fl.cf || fl.zf)
        goto L_4d9b38;
    {
        (void)lift_sub(32, edx, 0x13u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    eax = 0xau;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9e92:
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_4d9ed3;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0xbu, &fl);
    }
    if (fl.cf)
        goto L_4d9ec2;
    if (fl.cf || fl.zf)
        goto L_4d9b50;
    {
        (void)lift_sub(32, edx, 0xcu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0xfu, &fl);
    }
    if (fl.zf)
        goto L_4d9b40;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9ec2:
    {
        (void)lift_sub(32, edx, 0x6u, &fl);
    }
    if (fl.zf)
        goto L_4d9b38;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9ed3:
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (fl.cf)
        goto L_4d9eef;
    if (fl.cf || fl.zf)
        goto L_4d9b38;
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9b40;
L_4d9ee7:
    eax = 0x4u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d9eef:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4d9b88;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_exception_chain_step(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_EXCEPTION_CHAIN_STEP_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_EXCEPTION_CHAIN_STEP_STACK, 0, entry);
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
    esp = esp - 0x1cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0f8bu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x10u, 4, eax);
    eax = env.chain;
    lift_store(&env, esp, 0x14u, 4, eax);
    ecx = eax;
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, esp, 0x18u, 4, eax);
    edx = lift_load(&env, ecx, 0xcu, 4);
    eax = lift_load(&env, ecx, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0a95u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ecx;
    ebx = lift_load(&env, eax, 0x4u, 4);
    eax = (esp + 0x10u);
    ebx = ebx - 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0eafu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (esp + 0x10u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0ec7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (esp + 0x10u);
    eax = esp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0b7cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0b9eu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, ecx, 0xcu, 4, eax);
    {
        uint32_t r = lift_add(32, esp, 0x1cu, &fl);
        esp = r;
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

uint32_t lifted_rtl_stack_pair_call(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_STACK_PAIR_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_STACK_PAIR_CALL_STACK, 0, entry);
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
    esp = esp - 0x4u;
    eax = (esp + 0x18u);
    ebx = esp;
    edx = lift_load(&env, esp, 0x14u, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e2434u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
    }
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

uint32_t lifted_f4db131(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DB131_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DB131_STACK, 0, entry);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    edx = lift_load(&env, eax, 0x4u, 4);
    ebx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4db177;
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4db16c;
    {
        uint32_t r = lift_add(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4db1f7;
L_4db150:
    lift_store(&env, eax, 0x8u, 2, 0xffffu);
    lift_store(&env, eax, 0x4u, 4, 0x0u);
    lift_store(&env, eax, 0x0u, 4, 0x0u);
L_4db163:
    {
        uint32_t r = lift_or(8, lift_load(&env, eax, 0x7u, 1), 0xc0u, &fl);
        lift_store(&env, eax, 0x7u, 1, r);
    }
    goto L_4db1f7;
L_4db16c:
    {
        (void)lift_sub(16, (ecx & 0xffffu), 0x7fffu, &fl);
    }
    if (fl.zf)
        goto L_4db1f7;
L_4db177:
    edx = ecx;
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0x7fu) & 0xffu) << 8);
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x7fffu, &fl);
    }
    if (fl.zf)
        goto L_4db163;
    {
        uint32_t r = lift_add(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.cf)
        goto L_4db163;
    {
        uint32_t a = (ecx & 0xffffu);
        uint32_t r = lift_shr(16, a, 0x1u, &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4db194;
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t r = lift_add(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.cf)
        goto L_4db150;
L_4db194:
    edx = lift_load(&env, eax, 0x4u, 4);
    edi = edi - edi;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) - 0x3fffu) & 0xffffu);
    {
        uint32_t a = (ecx & 0xffffu);
        uint32_t r = lift_sar(16, a, 0x1u, &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.cf)
        goto L_4db1aa;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edi = r;
    }
L_4db1aa:
    {
        uint32_t r = lift_add(16, (ecx & 0xffffu), 0x3fffu, &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, eax, 0x8u, 2, (ecx & 0xffffu));
    ecx = edx;
    eax = ebx;
    esi = edx;
    fl.cf = 1;
    {
        uint32_t a = esi;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        esi = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    if (fl.zf)
        goto L_4db1dd;
    edx = edx - 1u;
L_4db1c0:
    lift_div1(32, esi, &eax, &edx, &fl);
    esi = esi - 1u;
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4db1d2;
    esi = esi + 1u;
    {
        uint32_t r = lift_add(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        esi = r;
    }
    edx = ecx;
    eax = ebx;
    goto L_4db1c0;
L_4db1d2:
    esi = esi + 1u;
    ecx = eax;
    eax = edi;
    lift_div1(32, esi, &eax, &edx, &fl);
    esi = esi + ecx;
    goto L_4db1e6;
L_4db1dd:
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.zf)
        goto L_4db1ef;
    {
        uint32_t t = edx;
        edx = eax;
        eax = t;
    }
    eax = edi;
    lift_div1(32, esi, &eax, &edx, &fl);
L_4db1e6:
    {
        uint32_t r = lift_sub(32, edx, edx, &fl);
        edx = r;
    }
    fl.cf = 1;
    {
        uint32_t a = esi;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        esi = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, eax, edx, &fl);
        eax = r;
    }
L_4db1ef:
    {
        uint32_t r = lift_adc(32, edx, esi, &fl);
        edx = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    lift_store(&env, esi, 0x0u, 4, eax);
    lift_store(&env, esi, 0x4u, 4, edx);
L_4db1f7:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dc2f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DC2F0_STACK + 4 + 4 * 3 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DC2F0_STACK, 3, entry);
    {
        uint32_t v = ebx;
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
    eax = (esp + 0x2cu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x2cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1918u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        uint32_t v = 0x5u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x2cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a04u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dc32b;
    goto L_4dc37f;
L_4dc31b:
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a04u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dc37f;
L_4dc32b:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1980u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (eax & 0xffffu);
    {
        (void)lift_sub(32, eax, 0xffffu, &fl);
    }
    if (fl.zf)
        goto L_4dc31b;
    {
        uint32_t v = 0xfffffff0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19f0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, 0x10000000u, &fl);
    }
    if (fl.zf)
        goto L_4dc31b;
    eax = esp;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = (esp + 0x18u);
    esi = (esp + 0x34u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19f8u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    {
        uint32_t v = lift_load(&env, esp, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a68u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dc31b;
    eax = ebx;
    goto L_4dc381;
L_4dc37f:
    eax = eax ^ eax;
L_4dc381:
    {
        uint32_t r = lift_add(32, esp, 0x18u, &fl);
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
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dd430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DD430_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DD430_STACK, 0, entry);
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dd3e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dee00;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4dee00:
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
    esp = esp - 0xcu;
    esi = eax;
    edi = (eax + 0x1cu);
    {
        (void)lift_sub(32, lift_load(&env, edi, 0xcu, 4), 0x0u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, esp, 0x0u, 4, eax);
    if (fl.zf)
        goto L_4dee63;
L_4dee1d:
    ecx = (esp + 0x8u);
    ebx = (esp + 0x4u);
    edx = esp;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0x8u, 4);
    eax = eax + lift_load(&env, esi, 0x3cu, 4);
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x40u, 4), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4dee48;
    lift_store(&env, eax, 0x4u, 4, 0x0u);
L_4dee48:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dee5d;
    eax = lift_load(&env, esp, 0x8u, 4);
    ebx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dee5d:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dee1d;
L_4dee63:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4def90u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ddc30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DDC30_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DDC30_STACK, 0, entry);
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ddbe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dee00;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4dee00:
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
    esp = esp - 0xcu;
    esi = eax;
    edi = (eax + 0x1cu);
    {
        (void)lift_sub(32, lift_load(&env, edi, 0xcu, 4), 0x0u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, esp, 0x0u, 4, eax);
    if (fl.zf)
        goto L_4dee63;
L_4dee1d:
    ecx = (esp + 0x8u);
    ebx = (esp + 0x4u);
    edx = esp;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0x8u, 4);
    eax = eax + lift_load(&env, esi, 0x3cu, 4);
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x40u, 4), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4dee48;
    lift_store(&env, eax, 0x4u, 4, 0x0u);
L_4dee48:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dee5d;
    eax = lift_load(&env, esp, 0x8u, 4);
    ebx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dee5d:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dee1d;
L_4dee63:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4def90u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_rtl_segment_dispatch(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_SEGMENT_DISPATCH_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_SEGMENT_DISPATCH_STACK, 0, entry);
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
    ebx = eax;
    ecx = edx;
    edx = 0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dee8e;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb4d4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_4dee8e:
    edx = ecx;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6250u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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

uint32_t lifted_f4e0ae5(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0AE5_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0AE5_STACK, 0, entry);
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
    esi = eax;
    ebx = edx;
L_4e0aee:
    eax = lift_load(&env, esi, 0x0u, 4);
    edx = ebx;
    edi = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0a95u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    {
        (void)lift_sub(32, ebx, lift_load(&env, esi, 0x8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4e0b5e;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e0b5e;
    ecx = lift_load(&env, eax, 0x4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - 1u) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0xdu, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e0b75;
    eax = (eax & 0xffu);
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4e0b1e;
            case 1:
                goto L_4e0b5e;
            case 2:
                goto L_4e0b5e;
            case 3:
                goto L_4e0b5e;
            case 4:
                goto L_4e0b23;
            case 5:
                goto L_4e0b5e;
            case 6:
                goto L_4e0b5e;
            case 7:
                goto L_4e0b5e;
            case 8:
                goto L_4e0b5e;
            case 9:
                goto L_4e0b5e;
            case 10:
                goto L_4e0b5e;
            case 11:
                goto L_4e0b5e;
            case 12:
                goto L_4e0b5e;
            case 13:
                goto L_4e0b3c;
            default:
                return 0u;
        }
    }
L_4e0b1e:
    ebx = lift_load(&env, ecx, 0x4u, 4);
    goto L_4e0aee;
L_4e0b23:
    eax = (edi + 0x10u);
    edx = lift_load(&env, ecx, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6bffu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e0b37;
    ebx = lift_load(&env, ecx, 0x8u, 4);
    goto L_4e0aee;
L_4e0b37:
    ebx = lift_load(&env, ecx, 0xcu, 4);
    goto L_4e0aee;
L_4e0b3c:
    edi = edi + 0x10u;
    edx = lift_load(&env, ecx, 0x4u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6bffu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e0b69;
    {
        (void)lift_and(8, lift_load(&env, esi, 0xdu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e0b5d;
    eax = edi;
    edx = lift_load(&env, ecx, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6c1du, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e0b5d:
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
L_4e0b5e:
    eax = ebp;
    lift_store(&env, esi, 0x4u, 4, ebx);
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
L_4e0b69:
    ebx = ebx - 1u;
    {
        (void)lift_sub(32, ebx, lift_load(&env, esi, 0x8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4e0b5e;
    ebx = ebx - 1u;
    goto L_4e0aee;
L_4e0b75:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e0b5e;
}

uint32_t lifted_f4e0ec7(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0EC7_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0EC7_STACK, 0, entry);
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
    esi = eax;
    edi = edx;
    eax = (esp + 0x14u);
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
    lift_store(&env, esp, 0x18u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x1cu, 4, 0x51bbacu);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e0f11;
L_4e0f00:
    eax = lift_load(&env, esp, 0x14u, 4);
    env.chain = eax;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e0f11:
    eax = lift_load(&env, esi, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e37feu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, eax, 0x0u, 1);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e0f84;
L_4e0f22:
    ebp = lift_load(&env, edx, 0xcu, 4);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4e0f76;
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x6u;
    eax = (esp + 0x8u);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edi;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e36d2u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esp, 0x28u, 4, 0x1u);
    eax = (esi + 0x24u);
    edx = edx ^ edx;
    lift_store(&env, esi, 0xcu, 1, 0x6u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebp, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x18u, 4, 0x0u);
    eax = (esp + 0x8u);
    edx = edx ^ edx;
    lift_store(&env, esp, 0x28u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e36e4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x28u, 4, 0x0u);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
L_4e0f76:
    edx = esi;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0e69u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e0f00;
L_4e0f84:
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4e0f22;
    goto L_4e0f76;
}

uint32_t lifted_f4e2434(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E2434_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E2434_STACK, 0, entry);
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
    esi = eax;
    eax = lift_load(&env, eax, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esi, 0x8u, 4);
    ecx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e2469;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4e2462;
    eax = lift_load(&env, esi, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e2462:
    lift_store(&env, eax, 0xcu, 4, 0x1u);
L_4e2469:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esi, 0xcu, 1)) & 0xffu) << 8);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) & 0xcfu) & 0xffu) << 8);
    ebp = lift_load(&env, esi, 0xcu, 4);
    lift_store(&env, esi, 0xcu, 1, ((eax >> 8) & 0xffu));
    eax = lift_load(&env, esi, 0x8u, 4);
    ecx = lift_load(&env, eax, 0x8u, 4);
    ebp = ebp & 0x30u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4e2489;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3b60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e2489:
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esi, 0xdu, 1)) & 0xffu);
    edi = edi ^ edi;
    {
        (void)lift_and(8, (ecx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4e24a7;
    ecx = (ecx & 0xffff00ffu) | ((((ecx & 0xffu)) & 0xffu) << 8);
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) & 0xfau) & 0xffu) << 8);
    eax = (eax & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
    lift_store(&env, esi, 0xdu, 1, ((ecx >> 8) & 0xffu));
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) | 0x1u) & 0xffu);
    edi = 0x1u;
    lift_store(&env, esi, 0xdu, 1, (eax & 0xffu));
L_4e24a7:
    ecx = 0x4e2420u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4e24d1;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esi, 0xdu, 1)) & 0xffu) << 8);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) & 0xfau) & 0xffu) << 8);
    ebx = (ebx & 0xffffff00u) | ((((eax >> 8) & 0xffu)) & 0xffu);
    lift_store(&env, esi, 0xdu, 1, ((eax >> 8) & 0xffu));
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | 0x4u) & 0xffu);
    eax = esi;
    lift_store(&env, esi, 0xdu, 1, (ebx & 0xffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3ce0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e24d1:
    {
        (void)lift_and(8, lift_load(&env, esi, 0xcu, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4e24dc;
    edx = 0xffffffffu;
L_4e24dc:
    edi = lift_load(&env, esi, 0xcu, 4);
    edi = edi | ebp;
    eax = lift_load(&env, esi, 0x10u, 4);
    lift_store(&env, esi, 0xcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e3ce0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3CE0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3CE0_STACK, 0, entry);
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
    eax = lift_load(&env, eax, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0xdu, 1)) & 0xffu) << 8);
    ebp = ebp ^ ebp;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4e3d79;
    ebx = (ebx & 0xffff00ffu) | (((((eax >> 8) & 0xffu)) & 0xffu) << 8);
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) & 0xefu) & 0xffu) << 8);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0xcu, 1)) & 0xffu);
    lift_store(&env, ecx, 0xdu, 1, ((ebx >> 8) & 0xffu));
    {
        (void)lift_and(8, (eax & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e3db4;
    edi = lift_load(&env, ecx, 0x8u, 4);
    ebx = lift_load(&env, edi, 0x8u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e3db4;
    esi = lift_load(&env, ecx, 0x4u, 4);
    edi = ebx;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4e3db4;
L_4e3d2d:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4e3db4;
    ebx = esi;
    edx = edi;
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3bf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e3d55;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0xcu, 1)) & 0xffu);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | 0x20u) & 0xffu);
    ebp = eax;
    lift_store(&env, ecx, 0xcu, 1, (ebx & 0xffu));
    goto L_4e3d71;
L_4e3d55:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e3d71;
    eax = 0xcu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0xcu, 1)) & 0xffu) << 8);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) | 0x20u) & 0xffu) << 8);
    ebp = 0xffffffffu;
    lift_store(&env, ecx, 0xcu, 1, ((eax >> 8) & 0xffu));
L_4e3d71:
    edi = edi + edx;
    {
        uint32_t r = lift_sub(32, esi, edx, &fl);
        esi = r;
    }
    if (!fl.zf)
        goto L_4e3d2d;
    goto L_4e3db4;
L_4e3d79:
    eax = lift_load(&env, ecx, 0x8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e3db4;
    lift_store(&env, ecx, 0xcu, 1, lift_load(&env, ecx, 0xcu, 1) & 0xefu);
    {
        (void)lift_and(8, lift_load(&env, ecx, 0xdu, 1), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4e3db4;
    eax = lift_load(&env, ecx, 0x4u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e3da4;
    edx = eax;
    ebx = 0x1u;
    edx = 0u - edx;
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0150u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e3da4:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e3db4;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0xcu, 1)) & 0xffu);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | 0x20u) & 0xffu);
    ebp = eax;
    lift_store(&env, ecx, 0xcu, 1, (ebx & 0xffu));
L_4e3db4:
    eax = lift_load(&env, ecx, 0x8u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    lift_store(&env, ecx, 0x0u, 4, eax);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4e3ddf;
    eax = lift_load(&env, ecx, 0x8u, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x10u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e3ddf;
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e3ddf;
    ebp = eax;
L_4e3ddf:
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebp;
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

uint32_t lifted_f4e4110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E4110_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E4110_STACK, 0, entry);
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
    esi = eax;
    lift_store(&env, esp, 0x0u, 4, edx);
    eax = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, esp, 0x4u, 4, eax);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esi, 0x10u, 1)) & 0xffu) << 8);
    ebp = ebp ^ ebp;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) & 0xfdu) & 0xffu) << 8);
    edi = edi ^ edi;
    lift_store(&env, esi, 0x10u, 1, ((eax >> 8) & 0xffu));
L_4e412f:
    ebx = lift_load(&env, esp, 0x0u, 4);
    edx = (ebx + 0x1u);
    lift_store(&env, esp, 0x0u, 4, edx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(32, ebx, 0xffu, &fl);
        ebx = r;
    }
    if (fl.zf)
        goto L_4e43a8;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) + 1u) & 0xffu);
    eax = eax & 0xffu;
    {
        (void)lift_and(8, lift_load(&env, eax, 0x507d58u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e4166;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e44c8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi + eax;
    goto L_4e4372;
L_4e4166:
    {
        (void)lift_sub(32, ebx, 0x25u, &fl);
    }
    if (fl.zf)
        goto L_4e4190;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e4100u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e4371;
    {
        (void)lift_and(8, lift_load(&env, esi, 0x10u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e43a8;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e4108u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e43a8;
L_4e4190:
    eax = lift_load(&env, esp, 0x0u, 4);
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e43c4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    lift_store(&env, esp, 0x0u, 4, eax);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e41a9;
    eax = eax + 1u;
    lift_store(&env, esp, 0x0u, 4, eax);
L_4e41a9:
    {
        (void)lift_sub(32, ebx, 0x64u, &fl);
    }
    if (fl.cf)
        goto L_4e421c;
    if (fl.cf || fl.zf)
        goto L_4e4284;
    {
        (void)lift_sub(32, ebx, 0x6fu, &fl);
    }
    if (fl.cf)
        goto L_4e41f5;
    if (fl.cf || fl.zf)
        goto L_4e42b5;
    {
        (void)lift_sub(32, ebx, 0x73u, &fl);
    }
    if (fl.cf)
        goto L_4e41e7;
    if (fl.cf || fl.zf)
        goto L_4e4308;
    {
        (void)lift_sub(32, ebx, 0x75u, &fl);
    }
    if (fl.cf)
        goto L_4e4372;
    if (fl.cf || fl.zf)
        goto L_4e42cc;
    {
        (void)lift_sub(32, ebx, 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4e42e0;
    goto L_4e4372;
L_4e41e7:
    {
        (void)lift_sub(32, ebx, 0x70u, &fl);
    }
    if (fl.zf)
        goto L_4e42e0;
    goto L_4e4372;
L_4e41f5:
    {
        (void)lift_sub(32, ebx, 0x69u, &fl);
    }
    if (fl.cf)
        goto L_4e420e;
    if (fl.cf || fl.zf)
        goto L_4e429e;
    {
        (void)lift_sub(32, ebx, 0x6eu, &fl);
    }
    if (fl.zf)
        goto L_4e4348;
    goto L_4e4372;
L_4e420e:
    {
        (void)lift_sub(32, ebx, 0x67u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e42f7;
    goto L_4e4372;
L_4e421c:
    {
        (void)lift_sub(32, ebx, 0x47u, &fl);
    }
    if (fl.cf)
        goto L_4e425d;
    if (fl.cf || fl.zf)
        goto L_4e42f7;
    {
        (void)lift_sub(32, ebx, 0x58u, &fl);
    }
    if (fl.cf)
        goto L_4e424f;
    if (fl.cf || fl.zf)
        goto L_4e42e0;
    {
        (void)lift_sub(32, ebx, 0x5bu, &fl);
    }
    if (fl.cf)
        goto L_4e4372;
    if (fl.cf || fl.zf)
        goto L_4e4315;
    {
        (void)lift_sub(32, ebx, 0x63u, &fl);
    }
    if (fl.zf)
        goto L_4e4328;
    goto L_4e4372;
L_4e424f:
    {
        (void)lift_sub(32, ebx, 0x53u, &fl);
    }
    if (fl.zf)
        goto L_4e4304;
    goto L_4e4372;
L_4e425d:
    {
        (void)lift_sub(32, ebx, 0x43u, &fl);
    }
    if (fl.cf)
        goto L_4e4276;
    if (fl.cf || fl.zf)
        goto L_4e4324;
    {
        (void)lift_sub(32, ebx, 0x45u, &fl);
    }
    if (fl.zf)
        goto L_4e42f7;
    goto L_4e4372;
L_4e4276:
    {
        (void)lift_sub(32, ebx, 0x25u, &fl);
    }
    if (fl.zf)
        goto L_4e4357;
    goto L_4e4372;
L_4e4284:
    ecx = 0x1u;
    ebx = 0xau;
    edx = (esp + 0x4u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e4bb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e4333;
L_4e429e:
    ecx = 0x1u;
    edx = (esp + 0x4u);
    eax = esi;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e4bb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e4333;
L_4e42b5:
    ecx = 0x1u;
    ebx = 0x8u;
    edx = (esp + 0x4u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e4bb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e4333;
L_4e42cc:
    ebx = 0xau;
    edx = (esp + 0x4u);
    eax = esi;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e4bb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e4333;
L_4e42e0:
    ecx = 0x1u;
    ebx = 0x10u;
    edx = (esp + 0x4u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e4bb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e4333;
L_4e42f7:
    edx = (esp + 0x4u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e48d8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e4333;
L_4e4304:
    lift_store(&env, esi, 0x10u, 1, lift_load(&env, esi, 0x10u, 1) | 0x20u);
L_4e4308:
    edx = (esp + 0x4u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e45f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e4333;
L_4e4315:
    ebx = esp;
    edx = (esp + 0x4u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e47ecu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e4333;
L_4e4324:
    lift_store(&env, esi, 0x10u, 1, lift_load(&env, esi, 0x10u, 1) | 0x20u);
L_4e4328:
    edx = (esp + 0x4u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e4508u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e4333:
    ebx = eax;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e43a8;
    edi = edi + ebx;
    {
        (void)lift_and(8, lift_load(&env, esi, 0x10u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e4372;
    ebp = ebp + 1u;
    goto L_4e4372;
L_4e4348:
    edx = (esp + 0x4u);
    ebx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e4748u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e4372;
L_4e4357:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e4100u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e4371;
    {
        (void)lift_and(8, lift_load(&env, esi, 0x10u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e43a8;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e4108u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e43a8;
L_4e4371:
    edi = edi + 1u;
L_4e4372:
    {
        (void)lift_and(8, lift_load(&env, esi, 0x10u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e412f;
    eax = lift_load(&env, esp, 0x0u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x25u, &fl);
    }
    if (!fl.zf)
        goto L_4e43a8;
    ebx = (eax + 0x1u);
    edx = esi;
    eax = ebx;
    lift_store(&env, esp, 0x0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e43c4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x0u, 4, eax);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x6eu, &fl);
    }
    if (!fl.zf)
        goto L_4e43a8;
    edx = (esp + 0x4u);
    ebx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e4748u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e43a8:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4e43b9;
    {
        (void)lift_and(8, lift_load(&env, esi, 0x10u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e43b9;
    eax = 0xffffffffu;
    goto L_4e43bb;
L_4e43b9:
    eax = ebp;
L_4e43bb:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e43c4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E43C4_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E43C4_STACK, 0, entry);
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
    edi = edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x10u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) | 0x1u) & 0xffu);
    lift_store(&env, edi, 0x10u, 1, (edx & 0xffu));
    edx = (edx & 0xffff00ffu) | ((((edx & 0xffu)) & 0xffu) << 8);
    lift_store(&env, edi, 0xcu, 4, 0xffffffffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0x3u) & 0xffu) << 8);
    lift_store(&env, edi, 0x10u, 1, ((edx >> 8) & 0xffu));
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x2au, &fl);
    }
    if (!fl.zf)
        goto L_4e43f1;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, edi, 0x10u, 1)) & 0xffu) << 8);
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) & 0xfeu) & 0xffu) << 8);
    eax = eax + 1u;
    lift_store(&env, edi, 0x10u, 1, ((ebx >> 8) & 0xffu));
L_4e43f1:
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) + 1u) & 0xffu);
    edx = edx & 0xffu;
    {
        (void)lift_and(8, lift_load(&env, edx, 0x507d58u, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4e442d;
    edx = edx ^ edx;
L_4e440a:
    {
        uint32_t r = lift_imul(32, edx, 0xau, &fl);
        edx = r;
    }
    ebx = ebx - 0x30u;
    edx = edx + ebx;
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x1u, 1)) & 0xffu);
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) + 1u) & 0xffu);
    esi = (ecx & 0xffu);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, esi, 0x507d58u, 1)) & 0xffu) << 8);
    eax = eax + 1u;
    {
        (void)lift_and(8, ((ecx >> 8) & 0xffu), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4e440a;
    lift_store(&env, edi, 0xcu, 4, edx);
L_4e442d:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (eax + 0x1u);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x4eu, &fl);
    }
    if (!fl.zf)
        goto L_4e4444;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, edi, 0x10u, 1)) & 0xffu) << 8);
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) | 0x8u) & 0xffu) << 8);
    eax = edx;
    lift_store(&env, edi, 0x10u, 1, ((ecx >> 8) & 0xffu));
    goto L_4e4454;
L_4e4444:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x46u, &fl);
    }
    if (!fl.zf)
        goto L_4e4454;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edi, 0x10u, 1)) & 0xffu);
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) | 0x4u) & 0xffu);
    eax = edx;
    lift_store(&env, edi, 0x10u, 1, (ecx & 0xffu));
L_4e4454:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ebx = (eax + 0x1u);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x68u, &fl);
    }
    if (fl.cf)
        goto L_4e4471;
    if (fl.cf || fl.zf)
        goto L_4e4482;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x6cu, &fl);
    }
    if (fl.cf)
        goto L_4e44c3;
    if (fl.cf || fl.zf)
        goto L_4e448c;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x77u, &fl);
    }
    if (fl.zf)
        goto L_4e448c;
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
L_4e4471:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x49u, &fl);
    }
    if (fl.cf)
        goto L_4e44c3;
    if (fl.cf || fl.zf)
        goto L_4e44ab;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x4cu, &fl);
    }
    if (fl.zf)
        goto L_4e449b;
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
L_4e4482:
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, edi, 0x10u, 1)) & 0xffu) << 8);
    {
        uint32_t r = lift_or(8, ((edx >> 8) & 0xffu), 0x10u, &fl);
        edx = (edx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    eax = ebx;
    goto L_4e44c0;
L_4e448c:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edi, 0x10u, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (edx & 0xffu), 0x20u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, edi, 0x10u, 1, (edx & 0xffu));
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
L_4e449b:
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edi, 0x10u, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (ecx & 0xffu), 0x40u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    eax = ebx;
    lift_store(&env, edi, 0x10u, 1, (ecx & 0xffu));
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
L_4e44ab:
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x1u, 1), 0x36u, &fl);
    }
    if (!fl.zf)
        goto L_4e44c3;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x2u, 1), 0x34u, &fl);
    }
    if (!fl.zf)
        goto L_4e44c3;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, edi, 0x10u, 1)) & 0xffu) << 8);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) | 0x40u) & 0xffu) << 8);
    {
        uint32_t r = lift_add(32, eax, 0x3u, &fl);
        eax = r;
    }
L_4e44c0:
    lift_store(&env, edi, 0x10u, 1, ((edx >> 8) & 0xffu));
L_4e44c3:
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

uint32_t lifted_f4e628c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E628C_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E628C_STACK, 0, entry);
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
    ebx = eax;
    ecx = edx;
    edx = 0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e62a6;
    edx = ecx;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6250u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e62a6:
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

uint32_t lifted_f4e6c98(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6C98_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6C98_STACK, 0, entry);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e37feu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x8u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e6cca;
    edx = (edx & 0xffu);
    {
        uint32_t i = edx;
        switch (i)
        {
            case 0:
                goto L_4e6cb0;
            case 1:
                goto L_4e6cc0;
            case 2:
                goto L_4e6cca;
            case 3:
                goto L_4e6cb8;
            case 4:
                goto L_4e6cb0;
            case 5:
                goto L_4e6cca;
            case 6:
                goto L_4e6cc0;
            case 7:
                goto L_4e6cc0;
            case 8:
                goto L_4e6cb8;
            default:
                return 0u;
        }
    }
L_4e6cb0:
    ecx = lift_load(&env, eax, 0x10u, 4);
    eax = ecx;
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
L_4e6cb8:
    ecx = lift_load(&env, eax, 0x4u, 4);
    eax = ecx;
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
L_4e6cc0:
    ecx = 0x4u;
    eax = ecx;
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
L_4e6cca:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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

uint32_t lifted_f4e6f60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6F60_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6F60_STACK, 0, entry);
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

uint32_t lifted_f4e7fc4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7FC4_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7FC4_STACK, 0, entry);
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
    esp = esp - 0x114u;
    ecx = eax;
    edi = edx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e7fe3;
    eax = 0xffffffffu;
    goto L_4e807a;
L_4e7fe3:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, eax, 0xdu, 1)) & 0xffu) << 8);
    esi = esi ^ esi;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4e7ff6;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3ce0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
L_4e7ff6:
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ebe60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4e8019;
    edx = eax;
    ebp = lift_load(&env, ecx, 0x10u, 4);
    ebx = ebx ^ ebx;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0150u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e8019:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4e8027;
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0fc0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = esi | eax;
L_4e8027:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0xcu, 1), 0x8u, &fl);
    }
    if (fl.zf)
        goto L_4e8042;
    eax = lift_load(&env, ecx, 0x8u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, eax, 0x8u, 4, 0x0u);
L_4e8042:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0xdu, 1), 0x8u, &fl);
    }
    if (fl.zf)
        goto L_4e8062;
    edx = lift_load(&env, ecx, 0x8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x14u, 1)) & 0xffu);
    eax = esp;
    edx = edx & 0xffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7f18u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9f00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e8062:
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4e8078;
    eax = lift_load(&env, ecx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cacu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e8078:
    eax = esi;
L_4e807a:
    {
        uint32_t r = lift_add(32, esp, 0x114u, &fl);
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
}

uint32_t lifted_f4e88bf(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E88BF_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E88BF_STACK, 0, entry);
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4e88dd;
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    if (fl.zf)
        goto L_4e88dc;
    ebx = ebx + 1u;
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e88d4;
    ecx = eax;
    eax = edx;
    edx = edx - edx;
    lift_div1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t t = ecx;
        ecx = eax;
        eax = t;
    }
L_4e88d4:
    lift_div1(32, ebx, &eax, &edx, &fl);
    ebx = edx;
    edx = ecx;
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
L_4e88dc:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e88dd:
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (fl.cf)
        goto L_4e88fd;
    if (!fl.zf)
        goto L_4e88f5;
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e88f5;
    eax = eax - ebx;
    ebx = eax;
    ecx = ecx - ecx;
    {
        uint32_t r = lift_sub(32, edx, edx, &fl);
        edx = r;
    }
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e88f5:
    ecx = ecx - ecx;
    {
        uint32_t r = lift_sub(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t t = ebx;
        ebx = eax;
        eax = t;
    }
    {
        uint32_t t = edx;
        edx = ecx;
        ecx = t;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e88fd:
    {
        uint32_t v = ebp;
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
    esi = esi - esi;
    edi = esi;
    ebp = esi;
L_4e8906:
    {
        uint32_t r = lift_add(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_adc(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (fl.cf)
        goto L_4e891f;
    ebp = ebp + 1u;
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (fl.cf)
        goto L_4e8906;
    if (!fl.cf && !fl.zf)
        goto L_4e8917;
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e8906;
L_4e8917:
    fl.cf = 0;
L_4e8918:
    {
        uint32_t r = lift_adc(32, esi, esi, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_adc(32, edi, edi, &fl);
        edi = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebp = r;
    }
    if (fl.sf)
        goto L_4e8941;
L_4e891f:
    {
        uint32_t a = ecx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_sub(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sbb(32, edx, ecx, &fl);
        edx = r;
    }
    fl.cf = !fl.cf;
    if (fl.cf)
        goto L_4e8918;
L_4e892a:
    {
        uint32_t r = lift_add(32, esi, esi, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_adc(32, edi, edi, &fl);
        edi = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebp = r;
    }
    if (fl.sf)
        goto L_4e893d;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, ecx, &fl);
        edx = r;
    }
    if (!fl.cf)
        goto L_4e892a;
    goto L_4e8918;
L_4e893d:
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, ecx, &fl);
        edx = r;
    }
L_4e8941:
    ebx = eax;
    ecx = edx;
    eax = esi;
    edx = edi;
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

uint32_t lifted_f4e8cc8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8CC8_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8CC8_STACK, 0, entry);
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
    ebx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebx + 0xffffffffu);
    ecx = eax;
    {
        (void)lift_sub(32, edx, 0xbu, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e8d29;
    {
        uint32_t i = edx;
        switch (i)
        {
            case 0:
                goto L_4e8cf0;
            case 1:
                goto L_4e8ce4;
            case 2:
                goto L_4e8cfa;
            case 3:
                goto L_4e8cfa;
            case 4:
                goto L_4e8cfa;
            case 5:
                goto L_4e8cfa;
            case 6:
                goto L_4e8cfa;
            case 7:
                goto L_4e8cfa;
            case 8:
                goto L_4e8cfa;
            case 9:
                goto L_4e8cfa;
            case 10:
                goto L_4e8cfa;
            case 11:
                goto L_4e8cfa;
            default:
                return 0u;
        }
    }
L_4e8ce4:
    eax = 0x8cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8bd4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e8d32;
L_4e8cf0:
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e8cfa;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea2a8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e8cfa:
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e8d19;
    {
        (void)lift_sub(32, ecx, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e8d19;
    {
        (void)lift_sub(32, ecx, 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4e8d19;
    edx = 0x2u;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8a10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ecx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e8d19:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8b24u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8d32;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8b8cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e8d32;
L_4e8d29:
    eax = 0xffffffffu;
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
L_4e8d32:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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

uint32_t lifted_f4e97b4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E97B4_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E97B4_STACK, 0, entry);
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
    esp = esp - 0x10u;
    ebx = eax;
    ecx = edx;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, eax, 0x0u, 1)) & 0xffu) << 8);
    esi = 0xffffffffu;
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x4au, &fl);
    }
    if (!fl.zf)
        goto L_4e97d1;
    esi = 0x1u;
    ebx = ebx + esi;
L_4e97d1:
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x4du, &fl);
    }
    if (!fl.zf)
        goto L_4e97d9;
    ebx = ebx + 1u;
    esi = esi ^ esi;
L_4e97d9:
    edx = (esp + 0xcu);
    eax = ebx;
    lift_store(&env, ecx, 0x20u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    ebx = eax;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4e97f8;
    eax = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, ecx, 0x1cu, 4, eax);
    goto L_4e983d;
L_4e97f8:
    eax = lift_load(&env, esp, 0xcu, 4);
    eax = eax - 1u;
    lift_store(&env, ecx, 0x10u, 4, eax);
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x2eu, &fl);
    }
    if (!fl.zf)
        goto L_4e9836;
    eax = (edx + 0x1u);
    edx = (esp + 0xcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    ebx = eax;
    eax = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, ecx, 0xcu, 4, eax);
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x0u, 1), 0x2eu, &fl);
    }
    if (!fl.zf)
        goto L_4e9836;
    edx = (esp + 0xcu);
    eax = (esi + 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    eax = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, ecx, 0x18u, 4, eax);
L_4e9836:
    lift_store(&env, ecx, 0x1cu, 4, 0x0u);
L_4e983d:
    edx = 0x2u;
    esi = esi ^ esi;
    lift_store(&env, esp, 0x8u, 4, edx);
    lift_store(&env, esp, 0x0u, 4, esi);
    lift_store(&env, esp, 0x4u, 4, esi);
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x2fu, &fl);
    }
    if (!fl.zf)
        goto L_4e9886;
    edx = (esp + 0x8u);
    eax = (ebx + 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, eax, 0x0u, 1)) & 0xffu) << 8);
    ebx = eax;
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x3au, &fl);
    }
    if (!fl.zf)
        goto L_4e9886;
    edx = (esp + 0x4u);
    eax = eax + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ebx = eax;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x3au, &fl);
    }
    if (!fl.zf)
        goto L_4e9886;
    edx = esp;
    eax = eax + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
L_4e9886:
    eax = lift_load(&env, esp, 0x0u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, ecx, 0x8u, 4, eax);
    eax = ebx;
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
        esp = r;
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

uint32_t lifted_f4ea350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA350_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA350_STACK, 0, entry);
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
    esp = esp - 0xcu;
    lift_store(&env, esp, 0x4u, 4, eax);
    ebp = edx;
    lift_store(&env, esp, 0x0u, 4, ebx);
    ebx = ebx ^ ebx;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ea3db;
L_4ea36a:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ea3fd;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, ebp, 0x0u, 2)) & 0xffffu);
    {
        (void)lift_and(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4ea39d;
    edx = edx ^ edx;
    eax = (esp + 0x8u);
    edx = (edx & 0xffff0000u) | (((ecx & 0xffffu)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e62e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4ea3ff;
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x0u, 4), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea3fd;
    goto L_4ea3a6;
L_4ea39d:
    eax = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x0u, 1, 0x0u);
    goto L_4ea3fd;
L_4ea3a6:
    esi = (esp + 0x8u);
    edi = lift_load(&env, esp, 0x4u, 4);
    ecx = eax;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    ebp = ebp + 0x2u;
    ebx = ebx + edx;
    eax = lift_load(&env, esp, 0x0u, 4);
    edi = edi + edx;
    eax = eax - edx;
    lift_store(&env, esp, 0x4u, 4, edi);
    lift_store(&env, esp, 0x0u, 4, eax);
    goto L_4ea36a;
L_4ea3db:
    {
        (void)lift_sub(16, lift_load(&env, ebp, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ea3fd;
    edx = edx ^ edx;
    eax = (esp + 0x8u);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0x0u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e62e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4ea3ff;
    ebp = ebp + 0x2u;
    ebx = ebx + eax;
    goto L_4ea3db;
L_4ea3fd:
    eax = ebx;
L_4ea3ff:
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA540_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA540_STACK, 0, entry);
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
    esp = esp - 0x10u;
    lift_store(&env, esp, 0xcu, 4, eax);
    lift_store(&env, esp, 0x4u, 4, edx);
    esi = ebx;
    lift_store(&env, esp, 0x8u, 4, ecx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4ea55a;
    lift_store(&env, edx, 0x0u, 4, eax);
L_4ea55a:
    edx = lift_load(&env, esp, 0xcu, 4);
L_4ea55e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) + 1u) & 0xffu);
    eax = eax & 0xffu;
    {
        (void)lift_and(8, lift_load(&env, eax, 0x507d58u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ea573;
    edx = edx + 1u;
    goto L_4ea55e;
L_4ea573:
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, edx, 0x0u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2bu, &fl);
    }
    if (fl.zf)
        goto L_4ea57f;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ea580;
L_4ea57f:
    edx = edx + 1u;
L_4ea580:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4ea5b0;
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4ea59d;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x1u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4ea596;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x58u, &fl);
    }
    if (!fl.zf)
        goto L_4ea59d;
L_4ea596:
    esi = 0x10u;
    goto L_4ea5d0;
L_4ea59d:
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4ea5a9;
    esi = 0x8u;
    goto L_4ea5e5;
L_4ea5a9:
    esi = 0xau;
    goto L_4ea5e5;
L_4ea5b0:
    {
        (void)lift_sub(32, esi, 0x2u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ea5ba;
    {
        (void)lift_sub(32, esi, 0x24u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ea5cb;
L_4ea5ba:
    eax = 0xdu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    goto L_4ea68c;
L_4ea5cb:
    {
        (void)lift_sub(32, esi, 0x10u, &fl);
    }
    if (!fl.zf)
        goto L_4ea5e5;
L_4ea5d0:
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4ea5e5;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, edx, 0x1u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4ea5e2;
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), 0x58u, &fl);
    }
    if (!fl.zf)
        goto L_4ea5e5;
L_4ea5e2:
    edx = edx + 0x2u;
L_4ea5e5:
    lift_store(&env, esp, 0x0u, 4, edx);
    ebp = ((esi * 4u));
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) ^ (ecx & 0xffu)) & 0xffu);
    ebx = ebx ^ ebx;
L_4ea5f3:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea6b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ea61c;
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0x50b214u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ea60c;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
L_4ea60c:
    eax = ebx;
    {
        uint32_t r = lift_imul(32, ebx, esi, &fl);
        ebx = r;
    }
    ebx = ebx + edi;
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (!fl.cf)
        goto L_4ea619;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
L_4ea619:
    edx = edx + 1u;
    goto L_4ea5f3;
L_4ea61c:
    {
        (void)lift_sub(32, edx, lift_load(&env, esp, 0x0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4ea625;
    edx = lift_load(&env, esp, 0xcu, 4);
L_4ea625:
    edi = lift_load(&env, esp, 0x4u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4ea62f;
    lift_store(&env, edi, 0x0u, 4, edx);
L_4ea62f:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4ea645;
    {
        (void)lift_sub(32, ebx, 0x80000000u, &fl);
    }
    if (fl.cf)
        goto L_4ea645;
    if (!fl.zf)
        goto L_4ea649;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ea649;
L_4ea645:
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4ea683;
L_4ea649:
    eax = 0xeu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ea666;
    eax = 0xffffffffu;
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
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
L_4ea666:
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ea677;
    eax = 0x80000000u;
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
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
L_4ea677:
    eax = 0x7fffffffu;
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
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
L_4ea683:
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ea68a;
    ebx = 0u - ebx;
L_4ea68a:
    eax = ebx;
L_4ea68c:
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
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
