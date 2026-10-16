/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_4.h"

uint32_t lifted_f485700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F485700_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F485700_STACK, 0, entry);
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
    esi = ebx;
    edi = 0x5b9a48u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_48570a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485722;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48570a;
L_485722:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    esi = ecx;
    {
        (void)lift_sub(32, ecx, 0x8876019au, &fl);
    }
    if (!fl.cf)
        goto L_48666c;
    {
        (void)lift_sub(32, ecx, 0x887600d7u, &fl);
    }
    if (!fl.cf)
        goto L_486a3e;
    {
        (void)lift_sub(32, ecx, 0x8876005fu, &fl);
    }
    if (!fl.cf)
        goto L_486bbf;
    {
        (void)lift_sub(32, ecx, 0x88760005u, &fl);
    }
    if (!fl.cf)
        goto L_486c82;
    {
        (void)lift_sub(32, ecx, 0x800401f0u, &fl);
    }
    if (!fl.cf)
        goto L_486cd8;
    {
        (void)lift_sub(32, ecx, 0x80004001u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_48651c;
    {
        (void)lift_sub(32, ecx, 0x80004005u, &fl);
    }
    if (fl.zf)
        goto L_4859f4;
L_48577b:
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
L_48577e:
    esi = 0x50fe91u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48578c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4857a4;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48578c;
L_4857a4:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4857a8:
    esi = 0x50feaau;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4857b6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4857ce;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4857b6;
L_4857ce:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4857d2:
    esi = 0x50fec0u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4857e0:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4857f8;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4857e0;
L_4857f8:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4857fc:
    esi = 0x50fedau;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48580a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485822;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48580a;
L_485822:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485826:
    esi = 0x50fef4u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485834:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48584c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485834;
L_48584c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485850:
    esi = 0x50ff1bu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48585e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485876;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48585e;
L_485876:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48587a:
    esi = 0x50ff31u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485888:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4858a0;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485888;
L_4858a0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4858a4:
    esi = 0x50ff44u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4858b2:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4858ca;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4858b2;
L_4858ca:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4858ce:
    esi = 0x50ff59u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4858dc:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4858f4;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4858dc;
L_4858f4:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4858f8:
    esi = 0x50ff72u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485906:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48591e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485906;
L_48591e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485922:
    esi = 0x50ff87u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485930:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485948;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485930;
L_485948:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48594c:
    esi = 0x50ff9fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48595a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485972;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48595a;
L_485972:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485976:
    esi = 0x50ffb6u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485984:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48599c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485984;
L_48599c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4859a0:
    esi = 0x50ffd5u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4859ae:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4859c6;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4859ae;
L_4859c6:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4859ca:
    esi = 0x50ffe5u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4859d8:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4859f0;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4859d8;
L_4859f0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4859f4:
    esi = 0x510003u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485a02:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485a1a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485a02;
L_485a1a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485a1e:
    esi = 0x510011u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485a2c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485a44;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485a2c;
L_485a44:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485a48:
    esi = 0x510023u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485a56:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485a6e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485a56;
L_485a6e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485a72:
    esi = 0x51004du;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485a80:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485a98;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485a80;
L_485a98:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485a9c:
    esi = 0x510065u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485aaa:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485ac2;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485aaa;
L_485ac2:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485ac6:
    esi = 0x51007fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485ad4:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485aec;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485ad4;
L_485aec:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485af0:
    esi = 0x510091u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485afe:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485b16;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485afe;
L_485b16:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485b1a:
    esi = 0x5100a7u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485b28:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485b40;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485b28;
L_485b40:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485b44:
    esi = 0x5100c3u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485b52:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485b6a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485b52;
L_485b6a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485b6e:
    esi = 0x5100d5u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485b7c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485b94;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485b7c;
L_485b94:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485b98:
    esi = 0x5100e9u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485ba6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485bbe;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485ba6;
L_485bbe:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485bc2:
    esi = 0x5100fdu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485bd0:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485be8;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485bd0;
L_485be8:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485bec:
    esi = 0x51012cu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485bfa:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485c12;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485bfa;
L_485c12:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485c16:
    esi = 0x51013eu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485c24:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485c3c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485c24;
L_485c3c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485c40:
    esi = 0x510157u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485c4e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485c66;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485c4e;
L_485c66:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485c6a:
    esi = 0x51016cu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485c78:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485c90;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485c78;
L_485c90:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485c94:
    esi = 0x510177u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485ca2:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485cba;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485ca2;
L_485cba:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485cbe:
    esi = 0x510187u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485ccc:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485ce4;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485ccc;
L_485ce4:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485ce8:
    esi = 0x510195u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485cf6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485d0e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485cf6;
L_485d0e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485d12:
    esi = 0x5101a6u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485d20:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485d38;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485d20;
L_485d38:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485d3c:
    esi = 0x5101beu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485d4a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485d62;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485d4a;
L_485d62:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485d66:
    esi = 0x5101d2u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485d74:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485d8c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485d74;
L_485d8c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485d90:
    esi = 0x5101e3u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485d9e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485db6;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485d9e;
L_485db6:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485dba:
    esi = 0x5101f6u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485dc8:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485de0;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485dc8;
L_485de0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485de4:
    esi = 0x510243u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485df2:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485e0a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485df2;
L_485e0a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485e0e:
    esi = 0x51025du;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485e1c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485e34;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485e1c;
L_485e34:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485e38:
    esi = 0x51026fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485e46:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485e5e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485e46;
L_485e5e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485e62:
    esi = 0x510285u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485e70:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485e88;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485e70;
L_485e88:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485e8c:
    esi = 0x510294u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485e9a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485eb2;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485e9a;
L_485eb2:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485eb6:
    esi = 0x5102a0u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485ec4:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485edc;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485ec4;
L_485edc:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485ee0:
    esi = 0x5102adu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485eee:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485f06;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485eee;
L_485f06:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485f0a:
    esi = 0x5102beu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485f18:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485f30;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485f18;
L_485f30:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485f34:
    esi = 0x5102cfu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485f42:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485f5a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485f42;
L_485f5a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485f5e:
    esi = 0x5102e3u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485f6c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485f84;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485f6c;
L_485f84:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485f88:
    esi = 0x5102f5u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485f96:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485fae;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485f96;
L_485fae:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485fb2:
    esi = 0x51031fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485fc0:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_485fd8;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485fc0;
L_485fd8:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_485fdc:
    esi = 0x510332u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_485fea:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486002;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_485fea;
L_486002:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486006:
    esi = 0x510345u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486014:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48602c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486014;
L_48602c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486030:
    esi = 0x510357u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48603e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486056;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48603e;
L_486056:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48605a:
    esi = 0x51036au;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486068:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486080;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486068;
L_486080:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486084:
    esi = 0x510382u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486092:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4860aa;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486092;
L_4860aa:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4860ae:
    esi = 0x510395u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4860bc:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4860d4;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4860bc;
L_4860d4:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4860d8:
    esi = 0x5103aeu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4860e6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4860fe;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4860e6;
L_4860fe:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486102:
    esi = 0x5103c0u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486110:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486128;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486110;
L_486128:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48612c:
    esi = 0x5103d3u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48613a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486152;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48613a;
L_486152:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486156:
    esi = 0x5103e2u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486164:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48617c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486164;
L_48617c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486180:
    esi = 0x5103f7u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48618e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4861a6;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48618e;
L_4861a6:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4861aa:
    esi = 0x510407u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4861b8:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4861d0;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4861b8;
L_4861d0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4861d4:
    esi = 0x51042fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4861e2:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4861fa;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4861e2;
L_4861fa:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4861fe:
    esi = 0x51043fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48620c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486224;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48620c;
L_486224:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486228:
    esi = 0x510451u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486236:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48624e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486236;
L_48624e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486252:
    esi = 0x510464u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486260:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486278;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486260;
L_486278:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48627c:
    esi = 0x510474u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48628a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4862a2;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48628a;
L_4862a2:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4862a6:
    esi = 0x510486u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4862b4:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4862cc;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4862b4;
L_4862cc:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4862d0:
    esi = 0x51049du;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4862de:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4862f6;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4862de;
L_4862f6:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4862fa:
    esi = 0x5104b3u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486308:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486320;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486308;
L_486320:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486324:
    esi = 0x5104d6u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486332:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48634a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486332;
L_48634a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48634e:
    esi = 0x5104eeu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48635c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486374;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48635c;
L_486374:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486378:
    esi = 0x510500u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486386:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48639e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486386;
L_48639e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4863a2:
    esi = 0x510537u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4863b0:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4863c8;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4863b0;
L_4863c8:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4863cc:
    esi = 0x510554u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4863da:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4863f2;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4863da;
L_4863f2:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4863f6:
    esi = 0x510572u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486404:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48641c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486404;
L_48641c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486420:
    esi = 0x510584u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48642e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486446;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48642e;
L_486446:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48644a:
    esi = 0x51059cu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486458:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486470;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486458;
L_486470:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486474:
    esi = 0x5105aeu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486482:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48649a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486482;
L_48649a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48649e:
    esi = 0x5105c7u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4864ac:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4864c4;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4864ac;
L_4864c4:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4864c8:
    esi = 0x5105dau;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4864d6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4864ee;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4864d6;
L_4864ee:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4864f2:
    esi = 0x5105ebu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486500:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486518;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486500;
L_486518:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48651c:
    esi = 0x5105fdu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48652a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486542;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48652a;
L_486542:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486546:
    esi = 0x51060fu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486554:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48656c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486554;
L_48656c:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486570:
    esi = 0x510627u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48657e:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486596;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48657e;
L_486596:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48659a:
    esi = 0x51063du;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4865a8:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4865c0;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4865a8;
L_4865c0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4865c4:
    esi = 0x510653u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4865d2:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4865ea;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4865d2;
L_4865ea:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4865ee:
    esi = 0x510671u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4865fc:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486614;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4865fc;
L_486614:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486618:
    esi = 0x510687u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486626:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48663e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486626;
L_48663e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486642:
    esi = 0x510697u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486650:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486668;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486650;
L_486668:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48666c:
    if (fl.cf || fl.zf)
        goto L_4863a2;
    {
        (void)lift_sub(32, ecx, 0x8876023bu, &fl);
    }
    if (!fl.cf)
        goto L_4866bf;
    {
        (void)lift_sub(32, ecx, 0x88760219u, &fl);
    }
    if (!fl.cf)
        goto L_4868c4;
    {
        (void)lift_sub(32, ecx, 0x887601ccu, &fl);
    }
    if (!fl.cf)
        goto L_4869c1;
    {
        (void)lift_sub(32, ecx, 0x887601b3u, &fl);
    }
    if (!fl.cf)
        goto L_486a17;
    {
        (void)lift_sub(32, ecx, 0x887601a4u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_4863cc;
    {
        (void)lift_sub(32, ecx, 0x887601aeu, &fl);
    }
    if (fl.zf)
        goto L_4863f6;
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
L_4866bf:
    if (fl.cf || fl.zf)
        goto L_485a48;
    {
        (void)lift_sub(32, ecx, 0x88760248u, &fl);
    }
    if (!fl.cf)
        goto L_48671b;
    {
        (void)lift_sub(32, ecx, 0x88760241u, &fl);
    }
    if (!fl.cf)
        goto L_486802;
    {
        (void)lift_sub(32, ecx, 0x8876023eu, &fl);
    }
    if (!fl.cf)
        goto L_486888;
    {
        (void)lift_sub(32, ecx, 0x8876023cu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485f88;
    esi = 0x51030du;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4866ff:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486717;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4866ff;
L_486717:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48671b:
    if (fl.cf || fl.zf)
        goto L_486180;
    {
        (void)lift_sub(32, ecx, 0x8876024eu, &fl);
    }
    if (!fl.cf)
        goto L_48676b;
    {
        (void)lift_sub(32, ecx, 0x8876024bu, &fl);
    }
    if (!fl.cf)
        goto L_4867c6;
    {
        (void)lift_sub(32, ecx, 0x88760249u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485826;
    esi = 0x510212u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48674f:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486767;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48674f;
L_486767:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_48676b:
    if (fl.cf || fl.zf)
        goto L_48659a;
    {
        (void)lift_sub(32, ecx, 0x8876026cu, &fl);
    }
    if (!fl.cf)
        goto L_486794;
    {
        (void)lift_sub(32, ecx, 0x8876024fu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485ee0;
    {
        (void)lift_sub(32, ecx, 0x88760250u, &fl);
    }
    if (fl.zf)
        goto L_485c16;
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
L_486794:
    if (fl.cf || fl.zf)
        goto L_48594c;
    {
        (void)lift_sub(32, ecx, 0x88760294u, &fl);
    }
    if (!fl.cf)
        goto L_4867b1;
    {
        (void)lift_sub(32, ecx, 0x88760280u, &fl);
    }
    if (fl.zf)
        goto L_48587a;
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
L_4867b1:
    if (fl.cf || fl.zf)
        goto L_4858a4;
    {
        (void)lift_sub(32, ecx, 0x887602a8u, &fl);
    }
    if (fl.zf)
        goto L_4861aa;
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
L_4867c6:
    if (fl.cf || fl.zf)
        goto L_486618;
    {
        (void)lift_sub(32, ecx, 0x8876024cu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485a72;
    esi = 0x51041bu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4867e6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4867fe;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4867e6;
L_4867fe:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486802:
    if (fl.cf || fl.zf)
        goto L_486324;
    {
        (void)lift_sub(32, ecx, 0x88760244u, &fl);
    }
    if (!fl.cf)
        goto L_486846;
    {
        (void)lift_sub(32, ecx, 0x88760242u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485f34;
    esi = 0x510116u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48682a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486842;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48682a;
L_486842:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486846:
    if (fl.cf || fl.zf)
        goto L_4860ae;
    {
        (void)lift_sub(32, ecx, 0x88760246u, &fl);
    }
    if (fl.cf)
        goto L_4859ca;
    if (fl.cf || fl.zf)
        goto L_486102;
    esi = 0x50ff07u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_48686c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486884;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48686c;
L_486884:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486888:
    if (fl.cf || fl.zf)
        goto L_4857a8;
    {
        (void)lift_sub(32, ecx, 0x8876023fu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485cbe;
    esi = 0x51021du;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4868a8:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4868c0;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4868a8;
L_4868c0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4868c4:
    if (fl.cf || fl.zf)
        goto L_4865c4;
    {
        (void)lift_sub(32, ecx, 0x88760234u, &fl);
    }
    if (!fl.cf)
        goto L_4868ff;
    {
        (void)lift_sub(32, ecx, 0x88760231u, &fl);
    }
    if (!fl.cf)
        goto L_486985;
    {
        (void)lift_sub(32, ecx, 0x8876021cu, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_4865ee;
    {
        (void)lift_sub(32, ecx, 0x88760230u, &fl);
    }
    if (fl.zf)
        goto L_486642;
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
L_4868ff:
    if (fl.cf || fl.zf)
        goto L_486378;
    {
        (void)lift_sub(32, ecx, 0x88760237u, &fl);
    }
    if (!fl.cf)
        goto L_486943;
    {
        (void)lift_sub(32, ecx, 0x88760235u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485e0e;
    esi = 0x510522u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486927:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48693f;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486927;
L_48693f:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486943:
    if (fl.cf || fl.zf)
        goto L_4858ce;
    {
        (void)lift_sub(32, ecx, 0x88760239u, &fl);
    }
    if (fl.cf)
        goto L_485d12;
    if (fl.cf || fl.zf)
        goto L_485eb6;
    esi = 0x510038u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_486969:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_486981;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_486969;
L_486981:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_486985:
    if (fl.cf || fl.zf)
        goto L_485b1a;
    {
        (void)lift_sub(32, ecx, 0x88760232u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_485976;
    esi = 0x51022eu;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    edi = edi - 1u;
L_4869a5:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4869bd;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4869a5;
L_4869bd:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
L_4869c1:
    if (fl.cf || fl.zf)
        goto L_486474;
    {
        (void)lift_sub(32, ecx, 0x887601eau, &fl);
    }
    if (!fl.cf)
        goto L_4869f0;
    {
        (void)lift_sub(32, ecx, 0x887601d6u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_48649e;
    {
        (void)lift_sub(32, ecx, 0x887601e0u, &fl);
    }
    if (fl.zf)
        goto L_4864c8;
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
L_4869f0:
    if (fl.cf || fl.zf)
        goto L_4864f2;
    {
        (void)lift_sub(32, ecx, 0x887601feu, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_486546;
    {
        (void)lift_sub(32, ecx, 0x88760208u, &fl);
    }
    if (fl.zf)
        goto L_486570;
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
L_486a17:
    if (fl.cf || fl.zf)
        goto L_485850;
    {
        (void)lift_sub(32, ecx, 0x887601b8u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_486420;
    {
        (void)lift_sub(32, ecx, 0x887601c2u, &fl);
    }
    if (fl.zf)
        goto L_48644a;
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
L_486a3e:
    if (fl.cf || fl.zf)
        goto L_485d66;
    {
        (void)lift_sub(32, ecx, 0x8876013cu, &fl);
    }
    if (!fl.cf)
        goto L_486a85;
    {
        (void)lift_sub(32, ecx, 0x887600fau, &fl);
    }
    if (!fl.cf)
        goto L_486b42;
    {
        (void)lift_sub(32, ecx, 0x887600e1u, &fl);
    }
    if (!fl.cf)
        goto L_486b98;
    {
        (void)lift_sub(32, ecx, 0x887600dcu, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_485d90;
    {
        (void)lift_sub(32, ecx, 0x887600deu, &fl);
    }
    if (fl.zf)
        goto L_485de4;
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
L_486a85:
    if (fl.cf || fl.zf)
        goto L_486030;
    {
        (void)lift_sub(32, ecx, 0x8876015eu, &fl);
    }
    if (!fl.cf)
        goto L_486aba;
    {
        (void)lift_sub(32, ecx, 0x8876014au, &fl);
    }
    if (!fl.cf)
        goto L_486b1b;
    {
        (void)lift_sub(32, ecx, 0x8876013du, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_48605a;
    {
        (void)lift_sub(32, ecx, 0x88760140u, &fl);
    }
    if (fl.zf)
        goto L_486084;
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
L_486aba:
    if (fl.cf || fl.zf)
        goto L_486228;
    {
        (void)lift_sub(32, ecx, 0x8876017eu, &fl);
    }
    if (!fl.cf)
        goto L_486ae9;
    {
        (void)lift_sub(32, ecx, 0x88760168u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_486252;
    {
        (void)lift_sub(32, ecx, 0x8876017cu, &fl);
    }
    if (fl.zf)
        goto L_4862a6;
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
L_486ae9:
    if (fl.cf || fl.zf)
        goto L_4862d0;
    {
        (void)lift_sub(32, ecx, 0x88760183u, &fl);
    }
    if (!fl.cf)
        goto L_486b06;
    {
        (void)lift_sub(32, ecx, 0x88760180u, &fl);
    }
    if (fl.zf)
        goto L_4862fa;
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
L_486b06:
    if (fl.cf || fl.zf)
        goto L_48634e;
    {
        (void)lift_sub(32, ecx, 0x88760190u, &fl);
    }
    if (fl.zf)
        goto L_4858f8;
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
L_486b1b:
    if (fl.cf || fl.zf)
        goto L_4860d8;
    {
        (void)lift_sub(32, ecx, 0x8876014fu, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_4861d4;
    {
        (void)lift_sub(32, ecx, 0x88760154u, &fl);
    }
    if (fl.zf)
        goto L_4861fe;
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
L_486b42:
    if (fl.cf || fl.zf)
        goto L_485f0a;
    {
        (void)lift_sub(32, ecx, 0x88760118u, &fl);
    }
    if (!fl.cf)
        goto L_486b71;
    {
        (void)lift_sub(32, ecx, 0x887600ffu, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_48612c;
    {
        (void)lift_sub(32, ecx, 0x88760104u, &fl);
    }
    if (fl.zf)
        goto L_485f5e;
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
L_486b71:
    if (fl.cf || fl.zf)
        goto L_485fb2;
    {
        (void)lift_sub(32, ecx, 0x88760122u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_485fdc;
    {
        (void)lift_sub(32, ecx, 0x88760136u, &fl);
    }
    if (fl.zf)
        goto L_486006;
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
L_486b98:
    if (fl.cf || fl.zf)
        goto L_485e38;
    {
        (void)lift_sub(32, ecx, 0x887600e6u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_485e62;
    {
        (void)lift_sub(32, ecx, 0x887600f0u, &fl);
    }
    if (fl.zf)
        goto L_485e8c;
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
L_486bbf:
    if (fl.cf || fl.zf)
        goto L_485a9c;
    {
        (void)lift_sub(32, ecx, 0x88760096u, &fl);
    }
    if (!fl.cf)
        goto L_486bfa;
    {
        (void)lift_sub(32, ecx, 0x88760078u, &fl);
    }
    if (!fl.cf)
        goto L_486c5b;
    {
        (void)lift_sub(32, ecx, 0x88760064u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_485ac6;
    {
        (void)lift_sub(32, ecx, 0x8876006eu, &fl);
    }
    if (fl.zf)
        goto L_485af0;
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
L_486bfa:
    if (fl.cf || fl.zf)
        goto L_485bec;
    {
        (void)lift_sub(32, ecx, 0x887600b4u, &fl);
    }
    if (!fl.cf)
        goto L_486c29;
    {
        (void)lift_sub(32, ecx, 0x887600a0u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_485c40;
    {
        (void)lift_sub(32, ecx, 0x887600aau, &fl);
    }
    if (fl.zf)
        goto L_485c6a;
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
L_486c29:
    if (fl.cf || fl.zf)
        goto L_485c94;
    {
        (void)lift_sub(32, ecx, 0x887600d2u, &fl);
    }
    if (!fl.cf)
        goto L_486c46;
    {
        (void)lift_sub(32, ecx, 0x887600cdu, &fl);
    }
    if (fl.zf)
        goto L_485ce8;
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
L_486c46:
    if (fl.cf || fl.zf)
        goto L_485d3c;
    {
        (void)lift_sub(32, ecx, 0x887600d4u, &fl);
    }
    if (fl.zf)
        goto L_485dba;
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
L_486c5b:
    if (fl.cf || fl.zf)
        goto L_485b44;
    {
        (void)lift_sub(32, ecx, 0x88760082u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_485b6e;
    {
        (void)lift_sub(32, ecx, 0x88760091u, &fl);
    }
    if (fl.zf)
        goto L_485bc2;
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
L_486c82:
    if (fl.cf || fl.zf)
        goto L_48577e;
    {
        (void)lift_sub(32, ecx, 0x88760028u, &fl);
    }
    if (!fl.cf)
        goto L_486cb1;
    {
        (void)lift_sub(32, ecx, 0x8876000au, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_4857d2;
    {
        (void)lift_sub(32, ecx, 0x88760014u, &fl);
    }
    if (fl.zf)
        goto L_4857fc;
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
L_486cb1:
    if (fl.cf || fl.zf)
        goto L_485922;
    {
        (void)lift_sub(32, ecx, 0x88760037u, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_4859a0;
    {
        (void)lift_sub(32, ecx, 0x8876005au, &fl);
    }
    if (fl.zf)
        goto L_485a1e;
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
L_486cd8:
    if (fl.cf || fl.zf)
        goto L_486156;
    {
        (void)lift_sub(32, ecx, 0x8007000eu, &fl);
    }
    if (fl.cf)
        goto L_48577b;
    if (fl.cf || fl.zf)
        goto L_48627c;
    {
        (void)lift_sub(32, ecx, 0x80070057u, &fl);
    }
    if (fl.zf)
        goto L_485b98;
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

uint32_t lifted_path_last_separator(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PATH_LAST_SEPARATOR_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PATH_LAST_SEPARATOR_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    eax = edx;
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4885b3;
L_4885a9:
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x5cu, &fl);
    }
    if (fl.zf)
        goto L_4885b3;
    eax = eax - 1u;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4885a9;
L_4885b3:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f48be70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48BE70_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48BE70_STACK, 0, entry);
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
    esi = eax;
    ebx = edx;
    {
        uint32_t v = 0x5328f0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ecx = (esi + 0x200u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d5f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_48bef4;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_48bef4;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x0u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x1u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x1u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x2u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x2u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x3u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x3u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x4u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x4u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x5u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x5u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x6u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x6u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x7u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x7u, 1, (edx & 0xffu));
    edx = lift_load(&env, eax, 0x20u, 4);
    lift_store(&env, ebx, 0x20u, 4, edx);
    edx = lift_load(&env, eax, 0x2cu, 4);
    lift_store(&env, ebx, 0x2cu, 4, edx);
    edx = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, ebx, 0x14u, 4, edx);
    eax = lift_load(&env, eax, 0x18u, 4);
    edx = edx ^ edx;
    lift_store(&env, ebx, 0x18u, 4, eax);
    ebx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_48bef4:
    eax = (esi + 0x200u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d5f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_48bf14;
    {
        uint32_t v = 0x5328f0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
L_48bf14:
    edx = lift_load(&env, 0u, 0x5bb4a0u, 4);
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
    {
        uint32_t v = 0x5328f0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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

uint32_t lifted_f4b0b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B0B70_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B0B70_STACK, 0, entry);
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
    esp = esp - 0x38u;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb700u, 2)) & 0xffffu);
    esi = lift_load(&env, 0u, 0x5bb764u, 4);
    edi = lift_load(&env, 0u, 0x5bb7d4u, 4);
    ebp = lift_load(&env, 0u, 0x5bb7d8u, 4);
    lift_store(&env, esp, 0x4u, 4, eax);
    lift_store(&env, esp, 0x2cu, 2, (edx & 0xffffu));
    lift_store(&env, esp, 0x30u, 2, (ebx & 0xffffu));
    eax = lift_load(&env, eax, 0xb4u, 4);
    lift_store(&env, 0u, 0x5bb734u, 4, eax);
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a4u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb740u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x16u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a6u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb742u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x8eu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bbffeu, 1, (eax & 0xffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x1eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7aeu, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    edx = lift_load(&env, 0u, 0x5bb734u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x44u, 1)) & 0xffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb738u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4b0ef2;
    eax = edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0xcu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x10u, 2)) & 0xffffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x27u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb7b2u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bb731u, 1, (eax & 0xffu));
L_4b0c3b:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bb738u, 1), 0x10u, &fl);
    }
    if (!fl.zf)
        goto L_4b0fc5;
    edx = lift_load(&env, 0u, 0x5bb734u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4b0f07;
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xf4u, 2)) & 0xffffu);
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5bb7b4u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, 0u, 0x5bb6e6u, 2, (edx & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xf8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e4u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bb7b6u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb6e0u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbfffu, 1, ((edx >> 8) & 0xffu));
    lift_store(&env, 0u, 0x5bb6e2u, 2, (eax & 0xffffu));
L_4b0ca8:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b0u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    edx = edx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (edx & 0xffffu));
    ebx = ebx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6ecu, 2, (edx & 0xffffu));
    ebx = ebx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6eeu, 2, (ebx & 0xffffu));
    edx = edx + eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (edx & 0xffffu));
    ebx = ebx + eax;
    eax = edx;
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) + lift_load(&env, 0u, 0x5bb6e0u, 2)) & 0xffffu);
    eax = eax - 1u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb748u, 2, (eax & 0xffffu));
    eax = ebx;
    eax = eax + edx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb74au, 2, (eax & 0xffffu));
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bbffeu, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b0e07;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    eax = eax - 1u;
    lift_store(&env, esp, 0x24u, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    eax = eax - 1u;
    lift_store(&env, esp, 0x1cu, 4, eax);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, 0u, 0x5bbffeu, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b0f58;
    eax = eax ^ eax;
L_4b0d49:
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x1cu, 4);
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5bbff8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x24u, 4);
    lift_store(&env, 0u, 0x5bbffau, 2, (edx & 0xffffu));
L_4b0d66:
    lift_store(&env, 0u, 0x5bbffcu, 2, (eax & 0xffffu));
L_4b0d6c:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff8u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0faf;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b0faf;
    {
        (void)lift_sub(16, (ebx & 0xffffu), lift_load(&env, 0u, 0x5bbffcu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0faf;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffau, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b0faf;
    {
        (void)lift_sub(16, (ebx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b0dbc;
    ebx = edx;
L_4b0dbc:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff6u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b0dd5;
    lift_store(&env, 0u, 0x5bb7a0u, 2, (edx & 0xffffu));
L_4b0dd5:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffcu, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b0dee;
    lift_store(&env, 0u, 0x5bb74au, 2, (edx & 0xffffu));
L_4b0dee:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff8u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b0e07;
    lift_store(&env, 0u, 0x5bb748u, 2, (edx & 0xffffu));
L_4b0e07:
    eax = lift_load(&env, esp, 0x2cu, 4);
    lift_store(&env, 0u, 0x5bb6e8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x30u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6eau, 2, (eax & 0xffffu));
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, esp, 0x2cu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0fba;
    {
        (void)lift_sub(16, (ebx & 0xffffu), lift_load(&env, esp, 0x30u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0fba;
    eax = lift_load(&env, esp, 0x2cu, 4);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb748u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0fba;
    eax = lift_load(&env, esp, 0x30u, 4);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb74au, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0fba;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bbfffu, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b14a8;
    edx = lift_load(&env, esp, 0x2eu, 4);
    eax = lift_load(&env, 0u, 0x5bb6ecu, 4);
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
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = lift_load(&env, 0u, 0x5bb734u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = edx + eax;
    eax = lift_load(&env, esp, 0x2au, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb6eau, 4);
    esi = lift_load(&env, esp, 0x8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    esi = esi - eax;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    esi = esi + edx;
    eax = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0x8u, 1)) & 0xffu);
L_4b0eba:
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4b14a8;
L_4b0ec2:
    lift_store(&env, esp, 0x34u, 1, (eax & 0xffu));
L_4b0ec6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0x34u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bb7d8u, 4, ebp);
    lift_store(&env, 0u, 0x5bb7d4u, 4, edi);
    lift_store(&env, 0u, 0x5bb764u, 4, esi);
    lift_store(&env, 0u, 0x5bb700u, 2, (ecx & 0xffffu));
    {
        uint32_t r = lift_add(32, esp, 0x38u, &fl);
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
L_4b0ef2:
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5bb7b2u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bb7b0u, 2, (edx & 0xffffu));
    goto L_4b0c3b;
L_4b0f07:
    eax = edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0x4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b4u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b6u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x1cu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x20u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e2u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x14u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e4u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x18u, 2)) & 0xffffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x25u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb6e6u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bbfffu, 1, (eax & 0xffu));
    goto L_4b0ca8;
L_4b0f58:
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4b0f63;
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    goto L_4b0d49;
L_4b0f63:
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4b0d6c;
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xa8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaau, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xacu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbffau, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaeu, 2)) & 0xffffu);
    goto L_4b0d66;
L_4b0faf:
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, esp, 0x34u, 1, ((edx >> 8) & 0xffu));
    goto L_4b0ec6;
L_4b0fba:
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    lift_store(&env, esp, 0x34u, 1, (edx & 0xffu));
    goto L_4b0ec6;
L_4b0fc5:
    eax = lift_load(&env, 0u, 0x5bb734u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4b0fba;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b4u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b6u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x1cu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x20u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e2u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x14u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e4u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x18u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6e6u, 2, (edx & 0xffffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x25u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bbfffu, 1, (edx & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x27u, 1)) & 0xffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb731u, 1, (eax & 0xffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    eax = eax - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e4u, 2)) & 0xffffu);
    edx = edx + eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    ebx = ebx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e6u, 2)) & 0xffffu);
    ebx = ebx - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e0u, 2)) & 0xffffu);
    ebx = ebx + eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    eax = eax + edx;
    eax = eax - 1u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb748u, 2, (eax & 0xffffu));
    eax = ebx;
    eax = eax + edx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb74au, 2, (eax & 0xffffu));
    eax = eax ^ eax;
    edx = edx ^ edx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb738u, 1)) & 0xffu);
    lift_store(&env, esp, 0x18u, 4, eax);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb6f8u, 2, (eax & 0xffffu));
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, esp, 0xcu, 4, edx);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    edx = lift_load(&env, esp, 0x8u, 4);
    eax = eax & 0xffffu;
    eax = eax + edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x5c1b00u, 1)) & 0xffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f8u, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx + eax;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb6f8u, 2, (edx & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    edx = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb6fau, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    edx = lift_load(&env, esp, 0x8u, 4);
    eax = eax & 0xffffu;
    eax = eax + edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x5c1b00u, 1)) & 0xffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6fau, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx + eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6fau, 2, (edx & 0xffffu));
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b13fa;
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b13fa;
    eax = lift_load(&env, 0u, 0x5bb7a2u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x10u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb79eu, 4);
    edx = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx - eax;
    eax = edx;
    edx = lift_load(&env, 0u, 0x5bb6f6u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0xcu, 4, edx);
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x18u, 4), &eax, &edx, &fl);
    edx = lift_load(&env, esp, 0x10u, 4);
    edx = edx - eax;
    eax = lift_load(&env, 0u, 0x5bb7a4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x8u, 4, eax);
    lift_store(&env, 0u, 0x5bb6f0u, 2, (edx & 0xffffu));
    edx = lift_load(&env, esp, 0x8u, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    edx = edx - eax;
    eax = edx;
    edx = lift_load(&env, 0u, 0x5bb7acu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x10u, 4, edx);
    eax = eax - edx;
    edx = lift_load(&env, 0u, 0x5bb6f8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x14u, 4, edx);
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x0u, 4), &eax, &edx, &fl);
    edx = lift_load(&env, esp, 0x8u, 4);
    edx = edx - eax;
    eax = edx;
    eax = eax - lift_load(&env, esp, 0x10u, 4);
    edx = lift_load(&env, 0u, 0x5bb6deu, 4);
    lift_store(&env, 0u, 0x5bb6f2u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0xcu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x18u, 4), &eax, &edx, &fl);
    edx = lift_load(&env, 0u, 0x5bb6e0u, 4);
    lift_store(&env, 0u, 0x5bb6fcu, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x0u, 4), &eax, &edx, &fl);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6fcu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6feu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f0u, 2)) & 0xffffu);
    eax = eax + edx;
    eax = eax - 1u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6feu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6f4u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f2u, 2)) & 0xffffu);
    eax = eax + edx;
    eax = eax - 1u;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bbffeu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb6f6u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b1333;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    eax = eax - 1u;
    lift_store(&env, esp, 0x20u, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    eax = eax - 1u;
    lift_store(&env, esp, 0x28u, 4, eax);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1405;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x28u, 4);
    edx = edx ^ edx;
L_4b1272:
    lift_store(&env, 0u, 0x5bbff8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x20u, 4);
    lift_store(&env, 0u, 0x5bbffau, 2, (edx & 0xffffu));
L_4b1283:
    lift_store(&env, 0u, 0x5bbffcu, 2, (eax & 0xffffu));
L_4b1289:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff8u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b1468;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f4u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1468;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f2u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffcu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b1468;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f6u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffau, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1468;
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, 0u, 0x5bb6f2u, 2), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b12e8;
    lift_store(&env, 0u, 0x5bb6f2u, 2, (edx & 0xffffu));
L_4b12e8:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f0u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff6u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b1301;
    lift_store(&env, 0u, 0x5bb6f0u, 2, (edx & 0xffffu));
L_4b1301:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f6u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffcu, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b131a;
    lift_store(&env, 0u, 0x5bb6f6u, 2, (edx & 0xffffu));
L_4b131a:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f4u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff8u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b1333;
    lift_store(&env, 0u, 0x5bb6f4u, 2, (edx & 0xffffu));
L_4b1333:
    eax = lift_load(&env, esp, 0x2cu, 4);
    lift_store(&env, 0u, 0x5bb6e8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x30u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb6eau, 2, (eax & 0xffffu));
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, esp, 0x2cu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0faf;
    eax = lift_load(&env, esp, 0x30u, 4);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb6f2u, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b0faf;
    eax = lift_load(&env, esp, 0x2cu, 4);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb6f4u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0faf;
    eax = lift_load(&env, esp, 0x30u, 4);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb6f6u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b0faf;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bbfffu, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b14a8;
    edi = lift_load(&env, 0u, 0x5bb738u, 1);
    esi = lift_load(&env, 0u, 0x5bb734u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        edi = r;
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6f2u, 2)) & 0xffffu);
    edi = edi + 0x5c1c00u;
    esi = lift_load(&env, esi, 0x0u, 4);
    ebp = edi;
    {
        uint32_t r = lift_sub(16, (eax & 0xffffu), (ecx & 0xffffu), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    ecx = eax;
    if (!fl.zf)
        goto L_4b146f;
L_4b13c5:
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb6e8u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(16, (ecx & 0xffffu), lift_load(&env, 0u, 0x5bb6f0u, 2), &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4b13f0;
L_4b13d5:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    ebp = ebp + 1u;
    {
        uint32_t r = lift_add(32, esi, edx, &fl);
        esi = r;
    }
    {
        uint32_t a = (ecx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4b13d5;
L_4b13f0:
    eax = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        eax = r;
    }
    goto L_4b0eba;
L_4b13fa:
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, esp, 0x34u, 1, ((eax >> 8) & 0xffu));
    goto L_4b0ec6;
L_4b1405:
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4b141c;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x28u, 4);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    goto L_4b1272;
L_4b141c:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4b1289;
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xa8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaau, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xacu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbffau, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaeu, 2)) & 0xffffu);
    goto L_4b1283;
L_4b1468:
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    goto L_4b0ec2;
L_4b146f:
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb702u, 2, (eax & 0xffffu));
L_4b1477:
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb702u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edi, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, 0u, 0x5bb702u, 2, (eax & 0xffffu));
    {
        uint32_t a = (ecx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4b1477;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    esi = esi + eax;
    goto L_4b13c5;
L_4b14a8:
    lift_store(&env, esp, 0x34u, 1, 0x1u);
    goto L_4b0ec6;
}

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
