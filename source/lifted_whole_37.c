/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_37.h"

uint32_t lifted_f4db34a(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DB34A_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DB34A_STACK, 0, entry);
    ecx = ecx ^ 0x80000000u;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4db35a;
    {
        uint32_t r = lift_add(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (fl.zf)
        goto L_4db366;
    {
        uint32_t a = ecx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        ecx = r;
    }
L_4db35a:
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4db369;
    {
        uint32_t r = lift_add(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4db367;
    edx = ecx;
    eax = ebx;
L_4db366:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4db367:
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
L_4db369:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5054a1u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4db393;
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
    lift_x87(&env, 0x4db374);
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
    lift_x87(&env, 0x4db379);
    lift_x87(&env, 0x4db37c);
    esp = esp + 0x8u;
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
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4db392;
    {
        uint32_t r = lift_sub(32, edx, edx, &fl);
        edx = r;
    }
    eax = edx;
L_4db392:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4db393:
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    edi = edx;
    esi = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x14u, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x14u, &fl);
        ecx = r;
    }
    edi = edi & 0x800007ffu;
    ecx = ecx & 0x800007ffu;
    ebp = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        ecx = r;
    }
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) + (edi & 0xffffu)) & 0xffffu);
    {
        uint32_t a = edi;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        ecx = r;
    }
    edx = edx & 0xfffffu;
    esi = esi & 0xfffffu;
    {
        uint32_t r = lift_or(16, (edi & 0xffffu), (edi & 0xffffu), &fl);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4db3d4;
    edx = edx | 0x100000u;
L_4db3d4:
    {
        uint32_t r = lift_or(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4db3df;
    esi = esi | 0x100000u;
L_4db3df:
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    edx = edx + edx + fl.cf;
    {
        uint32_t r = lift_add(32, ebx, ebx, &fl);
        ebx = r;
    }
    esi = esi + esi + fl.cf;
    {
        uint32_t r = lift_sub(16, (ecx & 0xffffu), (edi & 0xffffu), &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4db41b;
    if (!fl.cf)
        goto L_4db3f6;
    ebp = edi;
    ecx = (ecx & 0xffff0000u) | ((0u - (ecx & 0xffffu)) & 0xffffu);
    {
        uint32_t t = ebx;
        ebx = eax;
        eax = t;
    }
    {
        uint32_t t = edx;
        edx = esi;
        esi = t;
    }
L_4db3f6:
    {
        (void)lift_sub(16, (ecx & 0xffffu), 0x36u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4db41b;
    edx = esi;
    eax = ebx;
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = edx & 0x800fffffu;
    {
        uint32_t a = ebp;
        uint32_t r = lift_ror(32, a, 0xdu, &fl);
        ebp = r;
    }
    ebp = ebp & 0x7ff00000u;
    {
        uint32_t r = lift_or(32, edx, ebp, &fl);
        edx = r;
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4db41b:
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (!fl.sf)
        goto L_4db42c;
    esi = 0u - esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sub(32, 0, a, &fl);
        ebx = r;
    }
    esi = esi - 0x0u - fl.cf;
    ebp = ebp ^ 0x80000000u;
L_4db42c:
    edi = edi - edi;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4db456;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx - ebx;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x20u, &fl);
    }
    if (fl.cf)
        goto L_4db448;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    ebx = (ebx & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    edi = ebx;
    ebx = ebx - ebx;
    eax = edx;
    edx = edx - edx;
L_4db448:
    {
        uint32_t a = ebx;
        uint32_t r = lift_shrd(32, a, eax, (ecx & 0xffu), &fl);
        ebx = r;
    }
    edi = edi | ebx;
    ebx = ebx - ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shrd(32, a, edx, (ecx & 0xffu), &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shrd(32, a, ebx, (ecx & 0xffu), &fl);
        edx = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
L_4db456:
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, esi, &fl);
        edx = r;
    }
    if (!fl.sf)
        goto L_4db47f;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x35u, &fl);
    }
    if (fl.cf)
        goto L_4db472;
    {
        (void)lift_and(32, edi, 0x7fffffffu, &fl);
    }
    ebx = (ebx & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_adc(32, eax, 0x0u, &fl);
        eax = r;
    }
    edx = edx + 0x0u + fl.cf;
L_4db472:
    edx = 0u - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sub(32, 0, a, &fl);
        eax = r;
    }
    edx = edx - 0x0u - fl.cf;
    ebp = ebp ^ 0x80000000u;
L_4db47f:
    ebx = eax;
    {
        uint32_t r = lift_or(32, ebx, edx, &fl);
        ebx = r;
    }
    if (fl.zf)
        goto L_4db4ef;
    {
        uint32_t r = lift_or(16, (ebp & 0xffffu), (ebp & 0xffffu), &fl);
        ebp = (ebp & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4db4f3;
L_4db48a:
    {
        (void)lift_and(32, edx, 0x7fe00000u, &fl);
    }
    if (!fl.zf)
        goto L_4db49c;
    {
        uint32_t a = (ebp & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ebp = (ebp & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4db4f3;
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    edx = edx + edx + fl.cf;
    goto L_4db48a;
L_4db49c:
    {
        (void)lift_and(32, edx, 0x400000u, &fl);
    }
    if (fl.zf)
        goto L_4db4b4;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    edi = edi + 0x0u + fl.cf;
    ebp = (ebp & 0xffff0000u) | (((ebp & 0xffffu) + 1u) & 0xffffu);
    {
        (void)lift_sub(16, (ebp & 0xffffu), 0x7ffu, &fl);
    }
    if (fl.zf)
        goto L_4db4fd;
L_4db4b4:
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    if (!fl.cf)
        goto L_4db4de;
    {
        uint32_t r = lift_or(32, edi, edi, &fl);
        edi = r;
    }
    ebx = (ebx & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    ebx = ebx | eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_adc(32, eax, 0x0u, &fl);
        eax = r;
    }
    edx = edx + 0x0u + fl.cf;
    {
        (void)lift_and(32, edx, 0x200000u, &fl);
    }
    if (fl.zf)
        goto L_4db4de;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    ebp = (ebp & 0xffff0000u) | (((ebp & 0xffffu) + 1u) & 0xffffu);
    {
        (void)lift_sub(16, (ebp & 0xffffu), 0x7ffu, &fl);
    }
    if (fl.zf)
        goto L_4db4fd;
L_4db4de:
    edx = edx & 0xfffffu;
    ecx = ebp;
    {
        uint32_t a = ebp;
        uint32_t r = lift_shl(32, a, 0x15u, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_add(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_or(32, edx, ebp, &fl);
        edx = r;
    }
L_4db4ef:
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4db4f3:
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4db4fd:
    eax = ebp;
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    goto L_4e2389;
L_4e2389:
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
    eax = eax | 0x7ff00000u;
    edx = eax;
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}
