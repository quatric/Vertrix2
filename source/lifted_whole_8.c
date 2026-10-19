/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_8.h"

uint32_t lifted_f4e6c37(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6C37_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6C37_STACK, 0, entry);
    goto L_4e6c37;
L_4e078c:
    ebx = eax;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c7b90u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e07af;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x507ce4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e07c6;
    edx = 0xffu;
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ce4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e07c6;
L_4e07af:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6b2cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xfu;
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6bacu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cd8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e07c6:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b4cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
    edx = lift_load(&env, 0u, 0x5c7b94u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e07ed;
    eax = edx;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5c7b94u, 4, ebx);
L_4e07ed:
    ecx = lift_load(&env, 0u, 0x5c7b98u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4e0806;
    eax = ecx;
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5c7b98u, 4, esi);
L_4e0806:
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
L_4e6c37:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax + lift_load(&env, 0u, 0x5c5c54u, 4);
    eax = lift_load(&env, eax, 0x14u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e6c5e;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, eax, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x512eacu;
L_4e6c51:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dee73u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e6c5e:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0f8bu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e6c51;
    eax = 0x1u;
    goto L_4e078c;
}

uint32_t lifted_f4edc0e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDC0E_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EDC0E_STACK, 0, entry);
    goto L_4edc0e;
L_4edb72:
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edb8e;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4edb8e;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4edb8e;
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4edb8e;
    esi = 0xffffffffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        edx = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edb8e:
    esi = (esi & 0xffff0000u) | (((esi & 0xffffu) - 1u) & 0xffffu);
    {
        uint32_t r = lift_add(32, esi, 0x10000u, &fl);
        esi = r;
    }
    if (fl.cf)
        goto L_4edbb0;
    if (fl.of)
        goto L_4edbb0;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edba4;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
L_4edba4:
    if (!fl.zf)
        goto L_4edbaf;
    {
        uint32_t r = lift_or(32, esi, esi, &fl);
        esi = r;
    }
    if (!fl.sf)
        goto L_4edbaf;
    {
        uint32_t r = lift_xor(16, (esi & 0xffffu), 0x8000u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
L_4edbaf:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edbb0:
    esi = esi - 0x10000u;
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4edbbc;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
L_4edbbc:
    if (!fl.cf && !fl.zf)
        goto L_4edbdb;
    if (!fl.zf)
        goto L_4edbd4;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edbca;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
L_4edbca:
    if (fl.zf)
        goto L_4edbcd;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edbcd:
    {
        uint32_t r = lift_or(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.sf)
        goto L_4edbd4;
    esi = esi ^ edx;
L_4edbd4:
    edx = ecx;
    eax = ebx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
L_4edbdb:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edbdc:
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4edc06;
    {
        (void)lift_sub(32, ecx, 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4edc06;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edbf4;
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
L_4edbf4:
    if (!fl.zf)
        goto L_4edbff;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        ecx = r;
    }
    esi = 0xffffffffu;
    goto L_4edc06;
L_4edbff:
    {
        uint32_t r = lift_or(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.sf)
        goto L_4edc06;
    esi = esi ^ ecx;
L_4edc06:
    edx = ecx;
    eax = ebx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edc0e:
    {
        uint32_t r = lift_add(16, (esi & 0xffffu), 0x1u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.cf)
        goto L_4edb72;
    if (fl.of)
        goto L_4edb72;
    {
        uint32_t r = lift_add(32, esi, 0xffffu, &fl);
        esi = r;
    }
    if (fl.cf)
        goto L_4edbdc;
    if (fl.of)
        goto L_4edbdc;
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edc3f;
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4edc3f;
    {
        uint32_t r = lift_add(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4edc3c;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edc3c:
    {
        uint32_t a = (esi & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
L_4edc3f:
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4edc56;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4edc56;
    {
        (void)lift_and(32, esi, 0x7fff0000u, &fl);
    }
    if (!fl.zf)
        goto L_4edc56;
    eax = eax - eax;
    edx = edx - edx;
    {
        uint32_t r = lift_sub(32, esi, esi, &fl);
        esi = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edc56:
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
        uint32_t t = ecx;
        ecx = esi;
        esi = t;
    }
    edi = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edi = edi & 0x80007fffu;
    ecx = ecx & 0x80007fffu;
    ecx = ecx + edi;
    {
        uint32_t r = lift_sub(16, (ecx & 0xffffu), 0x3ffeu, &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.cf)
        goto L_4edc86;
    {
        (void)lift_sub(16, (ecx & 0xffffu), 0x7fffu, &fl);
    }
    if (fl.cf)
        goto L_4edc86;
    goto L_4edd16;
L_4edc86:
    {
        (void)lift_sub(16, (ecx & 0xffffu), 0xffc0u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4edc94;
    eax = eax - eax;
    edx = edx - edx;
    ecx = ecx - ecx;
    goto L_4edd0c;
L_4edc94:
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = ebp - ebp;
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
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_mul1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t t = esi;
        esi = eax;
        eax = t;
    }
    ecx = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    lift_mul1(32, edx, &eax, &edx, &fl);
    edi = edx;
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_adc(32, edi, ebp, &fl);
        edi = r;
    }
    ebp = ebp + ebp + fl.cf;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    {
        uint32_t t = ebx;
        ebx = eax;
        eax = t;
    }
    lift_mul1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_adc(32, edi, edx, &fl);
        edi = r;
    }
    ebp = ebp + 0x0u + fl.cf;
    eax = ebx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    lift_mul1(32, edx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, ebp, &fl);
        edx = r;
    }
    ebx = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    if (fl.sf)
        goto L_4edccb;
    {
        uint32_t r = lift_add(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_adc(32, eax, eax, &fl);
        eax = r;
    }
    edx = edx + edx + fl.cf;
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) - 1u) & 0xffffu);
L_4edccb:
    {
        uint32_t r = lift_add(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.cf)
        goto L_4edcf3;
    if (!fl.zf)
        goto L_4edcde;
    {
        uint32_t r = lift_or(32, esi, esi, &fl);
        esi = r;
    }
    ebx = (ebx & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    if (fl.cf)
        goto L_4edcde;
    esi = eax;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        esi = r;
    }
L_4edcde:
    {
        uint32_t r = lift_adc(32, eax, 0x0u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, 0x0u, &fl);
        edx = r;
    }
    if (!fl.cf)
        goto L_4edcf3;
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
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) + 1u) & 0xffffu);
    {
        (void)lift_sub(16, (ecx & 0xffffu), 0x7fffu, &fl);
    }
    if (fl.zf)
        goto L_4edd16;
L_4edcf3:
    {
        uint32_t r = lift_or(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4edd0c;
    if (!fl.zf)
        goto L_4edcfe;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
    goto L_4edd01;
L_4edcfe:
    ecx = (ecx & 0xffff0000u) | ((0u - (ecx & 0xffffu)) & 0xffffu);
L_4edd01:
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
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) - (ecx & 0xffffu)) & 0xffffu);
L_4edd0c:
    {
        uint32_t r = lift_add(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = (ecx & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    esi = ecx;
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
L_4edd16:
    ecx = (ecx & 0xffff0000u) | ((0x7fffu) & 0xffffu);
    edx = 0x80000000u;
    eax = eax - eax;
    goto L_4edd0c;
}

uint32_t lifted_f4eddc4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDDC4_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EDDC4_STACK, 0, entry);
    goto L_4eddc4;
L_4edd4e:
    esi = (esi & 0xffff0000u) | (((esi & 0xffffu) - 1u) & 0xffffu);
    {
        uint32_t r = lift_add(32, esi, 0x10000u, &fl);
        esi = r;
    }
    if (fl.cf)
        goto L_4edd6e;
    if (fl.of)
        goto L_4edd6e;
    if (!fl.sf)
        goto L_4edd6d;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edd66;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
L_4edd66:
    if (!fl.zf)
        goto L_4edd6d;
    {
        uint32_t r = lift_xor(16, (esi & 0xffffu), 0x8000u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
L_4edd6d:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edd6e:
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edd8f;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4edd8f;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4edd8f;
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4edd8f;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        edx = r;
    }
    esi = (esi & 0xffff0000u) | ((0xffffu) & 0xffffu);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edd8f:
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4edd95;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
L_4edd95:
    if (!fl.cf && !fl.zf)
        goto L_4edd9e;
    edx = ecx;
    eax = ebx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
L_4edd9e:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edd9f:
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4eddbc;
    {
        (void)lift_sub(32, ecx, 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4eddbc;
    eax = esi;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        eax = r;
    }
    esi = esi ^ eax;
    esi = esi & ecx;
    ecx = ecx - ecx;
L_4eddbc:
    edx = ecx;
    eax = ebx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4eddc4:
    {
        uint32_t r = lift_add(16, (esi & 0xffffu), 0x1u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.cf)
        goto L_4edd4e;
    if (fl.of)
        goto L_4edd4e;
    {
        uint32_t r = lift_add(32, esi, 0xffffu, &fl);
        esi = r;
    }
    if (fl.cf)
        goto L_4edd9f;
    if (fl.of)
        goto L_4edd9f;
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4ede1f;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4ede1f;
    {
        (void)lift_and(32, esi, 0x7fff0000u, &fl);
    }
    if (!fl.zf)
        goto L_4ede1f;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4ede0d;
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4ede0d;
    eax = esi;
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4ede0d;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e2371u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xc0000000u;
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    esi = (esi & 0xffff0000u) | ((0xffffu) & 0xffffu);
    goto L_4ede1e;
L_4ede0d:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e237du, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x80000000u;
    eax = eax - eax;
    {
        uint32_t r = lift_or(16, (esi & 0xffffu), 0x7fffu, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
L_4ede1e:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ede1f:
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4ede30;
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4ede30;
    {
        uint32_t r = lift_add(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4ede2d;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ede2d:
    {
        uint32_t a = (esi & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
L_4ede30:
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t t = ecx;
        ecx = esi;
        esi = t;
    }
    edi = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edi = edi & 0x80007fffu;
    ecx = ecx & 0x80007fffu;
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
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) + (ecx & 0xffffu)) & 0xffffu);
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
    {
        uint32_t r = lift_or(16, (edi & 0xffffu), (edi & 0xffffu), &fl);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4ede6b;
L_4ede61:
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    edx = edx + edx + fl.cf;
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) - 1u) & 0xffffu);
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.sf)
        goto L_4ede61;
L_4ede6b:
    {
        uint32_t r = lift_or(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4ede7a;
L_4ede70:
    {
        uint32_t r = lift_add(32, ebx, ebx, &fl);
        ebx = r;
    }
    esi = esi + esi + fl.cf;
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) - 1u) & 0xffffu);
    {
        uint32_t r = lift_or(32, esi, esi, &fl);
        esi = r;
    }
    if (!fl.sf)
        goto L_4ede70;
L_4ede7a:
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) - (ecx & 0xffffu)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (edi & 0xffffu), 0x3fffu, &fl);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.sf)
        goto L_4ede9d;
    {
        (void)lift_sub(16, (edi & 0xffffu), 0x7fffu, &fl);
    }
    if (fl.cf)
        goto L_4ede9d;
    edi = ecx;
    edi = (edi & 0xffff0000u) | ((0x7fffu) & 0xffffu);
    edx = 0x80000000u;
    eax = eax - eax;
    goto L_4edf75;
L_4ede9d:
    {
        (void)lift_sub(16, (edi & 0xffffu), 0xffc0u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4edeae;
    eax = eax - eax;
    edx = edx - edx;
    edi = edi - edi;
    goto L_4edf75;
L_4edeae:
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
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = esi;
    edi = edx;
    esi = eax;
    eax = eax - eax;
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4edec0;
    edx = edx - ecx;
    eax = eax + 1u;
L_4edec0:
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    lift_div1(32, ecx, &eax, &edx, &fl);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t t = ebx;
        ebx = eax;
        eax = t;
    }
    lift_mul1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t t = ecx;
        ecx = eax;
        eax = t;
    }
    {
        uint32_t t = ebx;
        ebx = edx;
        edx = t;
    }
    lift_mul1(32, edx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    edx = edx + 0x0u + fl.cf;
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xffffffecu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4edee1;
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    edx = edx + lift_load(&env, ebp, 0xfffffff4u, 4) + fl.cf;
L_4edee1:
    {
        uint32_t a = ecx;
        uint32_t r = lift_sub(32, 0, a, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_sbb(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_sbb(32, edi, edx, &fl);
        edi = r;
    }
    if (fl.zf)
        goto L_4edefb;
L_4edee9:
    {
        uint32_t r = lift_sub(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x1u, &fl);
        lift_store(&env, ebp, 0xffffffe8u, 4, r);
    }
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) - 0x0u - fl.cf);
    {
        uint32_t r = lift_add(32, ecx, ebx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_adc(32, esi, lift_load(&env, ebp, 0xfffffff4u, 4), &fl);
        esi = r;
    }
    {
        uint32_t r = lift_adc(32, edi, 0x0u, &fl);
        edi = r;
    }
    if (!fl.zf)
        goto L_4edee9;
L_4edefb:
    edi = esi;
    esi = ecx;
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4edf10;
    edi = edi - ecx;
    {
        uint32_t r = lift_add(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x1u, &fl);
        lift_store(&env, ebp, 0xffffffe8u, 4, r);
    }
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) + 0x0u + fl.cf);
L_4edf10:
    edx = edi;
    eax = esi;
    lift_div1(32, ecx, &eax, &edx, &fl);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4edf47;
    {
        uint32_t t = ebx;
        ebx = eax;
        eax = t;
    }
    lift_mul1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t t = ecx;
        ecx = eax;
        eax = t;
    }
    {
        uint32_t t = ebx;
        ebx = edx;
        edx = t;
    }
    lift_mul1(32, edx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    edx = edx + 0x0u + fl.cf;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sub(32, 0, a, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_sbb(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_sbb(32, edi, edx, &fl);
        edi = r;
    }
    if (fl.zf)
        goto L_4edf47;
L_4edf30:
    {
        uint32_t r = lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x1u, &fl);
        lift_store(&env, ebp, 0xffffffe4u, 4, r);
    }
    {
        uint32_t r = lift_sbb(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x0u, &fl);
        lift_store(&env, ebp, 0xffffffe8u, 4, r);
    }
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) - 0x0u - fl.cf);
    {
        uint32_t r = lift_add(32, ecx, lift_load(&env, ebp, 0xfffffff0u, 4), &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_adc(32, esi, lift_load(&env, ebp, 0xfffffff4u, 4), &fl);
        esi = r;
    }
    {
        uint32_t r = lift_adc(32, edi, 0x0u, &fl);
        edi = r;
    }
    if (!fl.zf)
        goto L_4edf30;
L_4edf47:
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
        ebx = v;
    }
    esp = esp + 0x8u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) - 1u) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    if (!fl.cf)
        goto L_4edf59;
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
    edi = edi + 1u;
L_4edf59:
    {
        uint32_t r = lift_or(16, (edi & 0xffffu), (edi & 0xffffu), &fl);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4edf75;
    if (!fl.zf)
        goto L_4edf64;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
    goto L_4edf6a;
L_4edf64:
    edi = (edi & 0xffff0000u) | ((0u - (edi & 0xffffu)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | (((edi & 0xffffu)) & 0xffffu);
L_4edf6a:
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
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) - (edi & 0xffffu)) & 0xffffu);
L_4edf75:
    {
        uint32_t r = lift_add(32, edi, edi, &fl);
        edi = r;
    }
    {
        uint32_t a = (edi & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    esi = edi;
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
}
