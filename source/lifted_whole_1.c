/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_1.h"

uint32_t lifted_f4314a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4314A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4314A0_STACK, 0, entry);
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
    esp = esp - 0x30u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    ecx = edx;
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ec00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417da0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    {
        (void)lift_sub(32, ebx, 0x6u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4314ce;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4314d8;
L_4314ce:
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
L_4314d8:
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = 0x41u;
    edx = edx + 0x1deu;
    eax = eax + 0x220u;
    ecx = ecx + ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4327e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    edi = edi ^ edi;
    eax = eax - ecx;
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    ecx = eax;
    eax = ((edx * 4u));
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax - 0xdu;
    lift_store(&env, ebp, 0xffffffccu, 4, edi);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = ecx + edx;
    eax = eax + 0xdu;
    lift_store(&env, ebp, 0xffffffc8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
L_43152c:
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    edx = edx + lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x4f9800u, 1)) & 0xffu);
    {
        (void)lift_sub(32, ecx, 0x4u, &fl);
    }
    if (!fl.cf)
        goto L_431549;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, edx, 0x4f9801u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xfffffff0u, 1, ((eax >> 8) & 0xffu));
L_431549:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4315da;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = edx + 1u;
    lift_store(&env, edi, 0x980u, 1, 0x5u);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
L_43155f:
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = edi + 1u;
    ebx = ebx + 0xdu;
    esi = esi + 0xdu;
    eax = eax + 0xdu;
    edx = edx + 1u;
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_43152c;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4314ce;
    ebx = 0x6u;
    esi = lift_load(&env, ebp, 0xffffffd4u, 4);
    edi = lift_load(&env, ebp, 0xffffffd0u, 4);
    ebx = ebx - esi;
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = ebx + edi;
    edi = ecx;
    eax = (ecx + 0x14u);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
L_4315ab:
    {
        (void)lift_sub(8, lift_load(&env, edi, 0x980u, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_431685;
    lift_store(&env, ecx, 0x988u, 4, 0x0u);
L_4315c2:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    ecx = ecx + 0x4u;
    edi = edi + 1u;
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (!fl.zf)
        goto L_4315ab;
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
L_4315da:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_431671;
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = (ebx & 0xffffff00u) | ((0xffu) & 0xffu);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4315ff;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edi, 0x97fu, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4315ff;
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebx, 0x1eau, 1)) & 0xffu);
L_4315ff:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = (ebx & 0xffff00ffu) | (((0xffu) & 0xffu) << 8);
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.cf)
        goto L_43164f;
L_431609:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    edx = 0x5u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x1eau, 1)) & 0xffu);
    esi = edi;
    lift_store(&env, ebp, 0xffffffecu, 1, (eax & 0xffu));
    eax = 0x598d30u;
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x980u, 1, (eax & 0xffu));
L_43162e:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x980u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_431660;
L_431638:
    edx = 0x5u;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x980u, 1, (eax & 0xffu));
    goto L_43162e;
L_43164f:
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xfffffff0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_431609;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, eax, 0x1eau, 1)) & 0xffu) << 8);
    goto L_431609;
L_431660:
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_431638;
    {
        (void)lift_sub(8, (edx & 0xffu), lift_load(&env, ebp, 0xffffffecu, 1), &fl);
    }
    if (fl.zf)
        goto L_431638;
    lift_store(&env, ebp, 0xffffffe4u, 4, lift_load(&env, ebp, 0xffffffe4u, 4) + 1u);
    goto L_43155f;
L_431671:
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_43155f;
    lift_store(&env, edi, 0x980u, 1, 0xffu);
    goto L_43155f;
L_431685:
    edx = lift_load(&env, edi, 0x97du, 4);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x430800u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x44f700u;
    esi = eax;
    lift_store(&env, ecx, 0x988u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0x4f97f8u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4315c2;
}

uint32_t lifted_f432a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F432A30_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F432A30_STACK, 0, entry);
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
    edi = (eax + 0x1deu);
    ebx = 0x41u;
    ecx = (eax + 0x220u);
    edx = edi;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4327e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffed0u);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4328e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_432ad5;
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
L_432a79:
    esi = lift_load(&env, ebp, 0xffffffd4u, 4);
    ebx = 0xbu;
    esi = esi + 0x2cu;
    edi = 0xcu;
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    esi = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    esi = esi + ebx;
L_432a94:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, ebp + 0xfffffed0u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_432adf;
L_432aa1:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = edi - 1u;
    esi = esi - 1u;
    eax = eax - 0x4u;
    edx = edx - 1u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_432a94;
    ebx = lift_load(&env, ebp, 0xffffffd4u, 4);
    esi = lift_load(&env, ebp, 0xffffffd8u, 4);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = ebx + 0x34u;
    esi = esi + 0xdu;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_432a79;
L_432ad5:
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
L_432adf:
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1deu, 1)) & 0xffu);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x1dfu, 1, (eax & 0xffu));
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = edi;
    eax = ecx;
    lift_store(&env, esi, 0x1deu, 1, 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432ba0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    goto L_432aa1;
}

uint32_t lifted_board_swap_slots(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_BOARD_SWAP_SLOTS_STACK + 4 + 4 * 2 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_BOARD_SWAP_SLOTS_STACK, 2, entry);
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
    edi = ebx;
    ebx = ecx;
    eax = ((edx * 4u));
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = ((edi * 4u));
    eax = eax + esi;
    edx = lift_load(&env, esp, 0xcu, 4);
    ecx = ecx + eax;
    eax = ((edx * 4u));
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, esp, 0x10u, 4);
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
    eax = eax + ebx;
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    esi = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, ecx, 0x0u, 4, edx);
    lift_store(&env, eax, 0x0u, 4, esi);
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

uint32_t lifted_f433840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F433840_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F433840_STACK, 0, entry);
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
    esp = esp - 0x84u;
    esi = eax;
    edx = 0x1u;
    ebx = 0x41u;
    lift_store(&env, ebp, 0xffffff90u, 4, edx);
    edx = (eax + 0x1deu);
    ecx = ecx ^ ecx;
    eax = eax + 0x220u;
    lift_store(&env, ebp, 0xffffff94u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4327e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    ecx = 0xdu;
    lift_store(&env, ebp, 0xffffffdcu, 1, ((eax >> 8) & 0xffu));
L_43387c:
    ebx = lift_load(&env, ebp, 0xffffff94u, 4);
    edx = ecx;
    {
        uint32_t r = lift_imul(32, ebx, 0xdu, &fl);
        eax = r;
    }
L_433884:
    eax = eax + 1u;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) ^ (ebx & 0xffu)) & 0xffu);
    lift_store(&env, eax, 0x54080fu, 1, (ebx & 0xffu));
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_433884;
    edi = lift_load(&env, ebp, 0xffffff94u, 4);
    edi = edi + 1u;
    ecx = ecx + 0xdu;
    lift_store(&env, ebp, 0xffffff94u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_43387c;
    ecx = 0xffffffffu;
    edx = edx ^ edx;
    edi = 0xfffffff3u;
    lift_store(&env, ebp, 0xffffff94u, 4, edx);
    lift_store(&env, ebp, 0xffffff74u, 4, esi);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff94u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffff78u, 4, ecx);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - 1u) & 0xffu);
    lift_store(&env, ebp, 0xffffffacu, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 1, (eax & 0xffu));
    eax = 0xdu;
    lift_store(&env, ebp, 0xffffffbcu, 4, edi);
    lift_store(&env, ebp, 0xffffff7cu, 4, eax);
L_4338d4:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff94u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) + 1u) & 0xffu);
    lift_store(&env, ebp, 0xffffffe4u, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    {
        uint32_t r = lift_imul(32, eax, 0xdu, &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffff78u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    {
        uint32_t r = lift_imul(32, ecx, 0xdu, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff98u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff7cu, 4);
    lift_store(&env, ebp, 0xffffff70u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffd4u, 1, (edx & 0xffu));
    edx = lift_load(&env, ebp, 0xffffff7cu, 4);
    lift_store(&env, ebp, 0xffffff6cu, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffd8u, 1, (edx & 0xffu));
    edx = lift_load(&env, ebp, 0xffffffbcu, 4);
    lift_store(&env, ebp, 0xffffff68u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 1, (edx & 0xffu));
    edx = lift_load(&env, ebp, 0xffffffbcu, 4);
    lift_store(&env, ebp, 0xffffffa8u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    lift_store(&env, ebp, 0xffffffa0u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff78u, 4);
    edi = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, ebp, 0xffffffb8u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff74u, 4);
    lift_store(&env, ebp, 0xffffff8cu, 4, eax);
    lift_store(&env, ebp, 0xffffff9cu, 4, edx);
L_433951:
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = eax + lift_load(&env, ebp, 0xffffff98u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x1deu, 1), 0x6u, &fl);
    }
    if (fl.zf)
        goto L_433b28;
L_433964:
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = eax + 1u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433951;
    ecx = lift_load(&env, ebp, 0xffffff74u, 4);
    ebx = lift_load(&env, ebp, 0xffffff78u, 4);
    edi = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    edx = lift_load(&env, ebp, 0xffffff7cu, 4);
    ecx = ecx + 0xdu;
    ebx = ebx + 1u;
    edi = edi + 0xdu;
    eax = eax + 0xdu;
    edx = edx + 0xdu;
    lift_store(&env, ebp, 0xffffff74u, 4, ecx);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffff78u, 4, ebx);
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) + 1u) & 0xffu);
    lift_store(&env, ebp, 0xffffffacu, 4, edi);
    lift_store(&env, ebp, 0xffffffe0u, 1, (ecx & 0xffu));
    ecx = lift_load(&env, ebp, 0xffffff94u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    lift_store(&env, ebp, 0xffffff94u, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4338d4;
    lift_store(&env, ebp, 0xffffff80u, 4, esi);
    eax = (esi + 0x104u);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    ebx = (ebx & 0xffff00ffu) | (((0xffu) & 0xffu) << 8);
    ebx = (ebx & 0xffffff00u) | ((((ebx >> 8) & 0xffu)) & 0xffu);
L_4339d6:
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffff98u, 4, edi);
    edi = lift_load(&env, ebp, 0xffffff80u, 4);
    ecx = (edi + 0x4u);
L_4339e1:
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = ecx;
    eax = eax + edi;
L_4339eb:
    eax = eax + 1u;
    lift_store(&env, eax, 0x733u, 1, (ebx & 0xffu));
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_4339eb;
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = eax + 1u;
    ecx = ecx + 0x4u;
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4339e1;
    ecx = lift_load(&env, ebp, 0xffffff80u, 4);
    ecx = ecx + 0x34u;
    edi = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, ebp, 0xffffff80u, 4, ecx);
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (!fl.zf)
        goto L_4339d6;
    eax = 0x5u;
    edx = edx ^ edx;
    ecx = ecx ^ edi;
    lift_store(&env, ebp, 0xffffff94u, 4, eax);
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    lift_store(&env, ebp, 0xffffff94u, 4, edx);
L_433a27:
    ebx = ebx ^ ebx;
    edi = lift_load(&env, ebp, 0xffffff84u, 4);
    lift_store(&env, ebp, 0xffffff98u, 4, ebx);
L_433a2f:
    {
        (void)lift_sub(8, lift_load(&env, edi, 0x540810u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_433a4e;
    ecx = 0x540810u;
    eax = esi;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff98u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff94u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433180u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_433a4e:
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = eax + 1u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433a2f;
    ecx = lift_load(&env, ebp, 0xffffff84u, 4);
    ebx = lift_load(&env, ebp, 0xffffff94u, 4);
    ecx = ecx + 0xdu;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    lift_store(&env, ebp, 0xffffff94u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433a27;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42eee0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffccu, 4, esi);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
L_433a7f:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    edx = edx ^ edx;
    eax = eax + esi;
    lift_store(&env, ebp, 0xffffff88u, 4, edx);
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
L_433a92:
    ebx = lift_load(&env, ebp, 0xffffffc0u, 4);
    edi = lift_load(&env, ebp, 0xffffffb0u, 4);
    eax = lift_load(&env, ebp, 0xffffff88u, 4);
    ecx = ecx ^ ecx;
    edi = edi + eax;
L_433a9f:
    edx = (edi + ecx);
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x734u, 1), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_433ad2;
    edx = lift_load(&env, edx, 0x731u, 4);
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x430850u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, eax, 0x48u, 2, 0x0u);
    lift_store(&env, eax, 0x93u, 1, 0x1u);
    lift_store(&env, eax, 0x4eu, 1, 0x3cu);
    lift_store(&env, ebx, 0x324u, 4, eax);
L_433ad2:
    ecx = ecx + 1u;
    ebx = ebx + 0x4u;
    {
        (void)lift_sub(32, ecx, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433a9f;
    edx = lift_load(&env, ebp, 0xffffff88u, 4);
    ecx = lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = edx + 0x4u;
    ecx = ecx + 0x10u;
    lift_store(&env, ebp, 0xffffff88u, 4, edx);
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    {
        (void)lift_sub(32, edx, 0x34u, &fl);
    }
    if (!fl.zf)
        goto L_433a92;
    edi = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    edi = edi + edx;
    eax = eax + 0xd0u;
    lift_store(&env, ebp, 0xffffffc8u, 4, edi);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        (void)lift_sub(32, edi, 0x104u, &fl);
    }
    if (!fl.zf)
        goto L_433a7f;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xffffffdcu, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_433e03;
    eax = lift_load(&env, ebp, 0xffffff90u, 4);
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
L_433b28:
    lift_store(&env, edi, 0x540810u, 1, 0x1u);
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x838u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_433b4b;
    ebx = lift_load(&env, ebp, 0xffffff95u, 4);
    edx = lift_load(&env, ebp, 0xffffff91u, 4);
    eax = esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_433b4b:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x839u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_433dd7;
L_433b59:
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433b87;
    ecx = lift_load(&env, ebp, 0xffffff8cu, 4);
    ecx = ecx + lift_load(&env, ebp, 0xffffff98u, 4);
L_433b66:
    edx = edx ^ edx;
    ebx = lift_load(&env, ebp, 0xffffff94u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    ebx = ebx - edx;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_433b87;
    ecx = ecx - 0xdu;
    edx = (edx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    eax = eax - 1u;
    lift_store(&env, ecx, 0x54081du, 1, ((edx >> 8) & 0xffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_433b66;
L_433b87:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_433ba1;
    ebx = (ebx & 0xffffff00u) | ((0x1u) & 0xffu);
    edx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    lift_store(&env, ebp, 0xffffffdcu, 1, (ebx & 0xffu));
    ebx = lift_load(&env, ebp, 0xffffff95u, 4);
    eax = esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_433ba1:
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_433bd1;
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
    ecx = ecx + lift_load(&env, ebp, 0xffffff98u, 4);
L_433baf:
    edx = edx ^ edx;
    ebx = lift_load(&env, ebp, 0xffffff94u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    edx = edx + ebx;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_433bd1;
    ecx = ecx + 0xdu;
    ebx = (ebx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    eax = eax + 1u;
    lift_store(&env, ecx, 0x540803u, 1, ((ebx >> 8) & 0xffu));
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_433baf;
L_433bd1:
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.zf)
        goto L_433beb;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
    ebx = lift_load(&env, ebp, 0xffffff95u, 4);
    edx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    lift_store(&env, ebp, 0xffffffdcu, 1, (ecx & 0xffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_433beb:
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, esi, 0x839u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_433dec;
L_433bfa:
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = eax - 1u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433c26;
    ecx = lift_load(&env, ebp, 0xffffffa0u, 4);
    ecx = ecx + eax;
L_433c07:
    edx = edx ^ edx;
    ebx = lift_load(&env, ebp, 0xffffff98u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    ebx = ebx - edx;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_433c26;
    ecx = ecx - 1u;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = eax - 1u;
    lift_store(&env, ecx, 0x540811u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_433c07;
L_433c26:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_433c40;
    edx = (edx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    ebx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    lift_store(&env, ebp, 0xffffffdcu, 1, ((edx >> 8) & 0xffu));
    edx = lift_load(&env, ebp, 0xffffff91u, 4);
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_433c40:
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_433c6e;
    ecx = lift_load(&env, ebp, 0xffffffa4u, 4);
    ecx = ecx + eax;
L_433c4e:
    edx = edx ^ edx;
    ebx = lift_load(&env, ebp, 0xffffff98u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    edx = edx + ebx;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_433c6e;
    ecx = ecx + 1u;
    ebx = (ebx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = eax + 1u;
    lift_store(&env, ecx, 0x54080fu, 1, (ebx & 0xffu));
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_433c4e;
L_433c6e:
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (fl.zf)
        goto L_433c88;
    ebx = (ebx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    edx = lift_load(&env, ebp, 0xffffff91u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 1, ((ebx >> 8) & 0xffu));
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    ebx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_433c88:
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x839u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_433964;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffff94u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_433d30;
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = eax - 1u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433ccb;
    ecx = lift_load(&env, ebp, 0xffffffa8u, 4);
    ecx = ecx + eax;
L_433cac:
    edx = edx ^ edx;
    ebx = lift_load(&env, ebp, 0xffffff98u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    ebx = ebx - edx;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_433ccb;
    ecx = ecx - 1u;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = eax - 1u;
    lift_store(&env, ecx, 0x540811u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_433cac;
L_433ccb:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_433ce5;
    edx = (edx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    ebx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    lift_store(&env, ebp, 0xffffffdcu, 1, ((edx >> 8) & 0xffu));
    edx = lift_load(&env, ebp, 0xffffffe5u, 4);
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_433ce5:
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_433d16;
    ecx = lift_load(&env, ebp, 0xffffff68u, 4);
    ecx = ecx + eax;
L_433cf6:
    edx = edx ^ edx;
    ebx = lift_load(&env, ebp, 0xffffff98u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    edx = edx + ebx;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_433d16;
    ecx = ecx + 1u;
    ebx = (ebx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = eax + 1u;
    lift_store(&env, ecx, 0x54080fu, 1, (ebx & 0xffu));
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_433cf6;
L_433d16:
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (fl.zf)
        goto L_433d30;
    ebx = (ebx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    edx = lift_load(&env, ebp, 0xffffffd5u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 1, ((ebx >> 8) & 0xffu));
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    ebx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_433d30:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffff94u, 4), 0x4u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_433964;
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = eax - 1u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433d69;
    ecx = lift_load(&env, ebp, 0xffffff6cu, 4);
    ecx = ecx + eax;
L_433d4a:
    edx = edx ^ edx;
    ebx = lift_load(&env, ebp, 0xffffff98u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    ebx = ebx - edx;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_433d69;
    ecx = ecx - 1u;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = eax - 1u;
    lift_store(&env, ecx, 0x540811u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_433d4a;
L_433d69:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_433d83;
    edx = (edx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    ebx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    lift_store(&env, ebp, 0xffffffdcu, 1, ((edx >> 8) & 0xffu));
    edx = lift_load(&env, ebp, 0xffffffd1u, 4);
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_433d83:
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_433db4;
    ecx = lift_load(&env, ebp, 0xffffff70u, 4);
    ecx = ecx + eax;
L_433d94:
    edx = edx ^ edx;
    ebx = lift_load(&env, ebp, 0xffffff98u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    edx = edx + ebx;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_433db4;
    ecx = ecx + 1u;
    ebx = (ebx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = eax + 1u;
    lift_store(&env, ecx, 0x54080fu, 1, (ebx & 0xffu));
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_433d94;
L_433db4:
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (fl.zf)
        goto L_433964;
    ebx = (ebx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    edx = lift_load(&env, ebp, 0xffffffe1u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 1, ((ebx >> 8) & 0xffu));
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    ebx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_433964;
L_433dd7:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_433b59;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_433b59;
    goto L_433beb;
L_433dec:
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_433bfa;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_433bfa;
    goto L_433c88;
L_433e03:
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffff90u, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffff90u, 4);
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

uint32_t lifted_f433e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F433E20_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F433E20_STACK, 0, entry);
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
    esp = esp - 0x70u;
    esi = eax;
    edx = 0x1u;
    ebx = 0x41u;
    lift_store(&env, ebp, 0xffffff9cu, 4, edx);
    edx = (eax + 0x1deu);
    ecx = ecx ^ ecx;
    eax = eax + 0x220u;
    lift_store(&env, ebp, 0xffffffa0u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4327e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    ecx = 0xdu;
    lift_store(&env, ebp, 0xffffffe8u, 1, ((eax >> 8) & 0xffu));
L_433e59:
    ebx = lift_load(&env, ebp, 0xffffffa0u, 4);
    edx = ecx;
    {
        uint32_t r = lift_imul(32, ebx, 0xdu, &fl);
        eax = r;
    }
L_433e61:
    eax = eax + 1u;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) ^ (ebx & 0xffu)) & 0xffu);
    lift_store(&env, eax, 0x540857u, 1, (ebx & 0xffu));
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_433e61;
    edi = lift_load(&env, ebp, 0xffffffa0u, 4);
    edi = edi + 1u;
    ecx = ecx + 0xdu;
    lift_store(&env, ebp, 0xffffffa0u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433e59;
    ecx = 0xffffffffu;
    edi = 0xfffffff3u;
    eax = 0xdu;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd0u, 4, esi);
    lift_store(&env, ebp, 0xffffffa0u, 4, edx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    lift_store(&env, ebp, 0xffffff84u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
L_433ea0:
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_imul(32, eax, 0xdu, &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    {
        uint32_t r = lift_imul(32, ecx, 0xdu, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, edx);
    lift_store(&env, ebp, 0xffffffb8u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, edx);
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff84u, 4);
    lift_store(&env, ebp, 0xffffffb0u, 4, edx);
    lift_store(&env, ebp, 0xffffffacu, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffff80u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    ebx = lift_load(&env, ebp, 0xffffff84u, 4);
    lift_store(&env, ebp, 0xffffffa8u, 4, edx);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
L_433ee8:
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffa4u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x1deu, 1), 0x6u, &fl);
    }
    if (fl.zf)
        goto L_4340a5;
L_433efb:
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = eax + 1u;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433ee8;
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffd4u, 4);
    edi = lift_load(&env, ebp, 0xffffff84u, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    ecx = ecx + 0xdu;
    ebx = ebx + 1u;
    edi = edi + 0xdu;
    eax = eax + 0xdu;
    edx = edx + 0xdu;
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    lift_store(&env, ebp, 0xffffff84u, 4, edi);
    ecx = lift_load(&env, ebp, 0xffffffa0u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    lift_store(&env, ebp, 0xffffffa0u, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433ea0;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    eax = (esi + 0x104u);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    ebx = (ebx & 0xffff00ffu) | (((0xffu) & 0xffu) << 8);
    ebx = (ebx & 0xffffff00u) | ((((ebx >> 8) & 0xffu)) & 0xffu);
L_433f53:
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffa4u, 4, edi);
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = (edi + 0x4u);
L_433f5e:
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = ecx;
    eax = eax + edi;
L_433f68:
    eax = eax + 1u;
    lift_store(&env, eax, 0x733u, 1, (ebx & 0xffu));
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_433f68;
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = eax + 1u;
    ecx = ecx + 0x4u;
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433f5e;
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = ecx + 0x34u;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (!fl.zf)
        goto L_433f53;
    eax = 0x5u;
    edx = edx ^ edx;
    ecx = ecx ^ edi;
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
    lift_store(&env, ebp, 0xffffff88u, 4, ecx);
    lift_store(&env, ebp, 0xffffffa0u, 4, edx);
L_433fa4:
    ebx = ebx ^ ebx;
    edi = lift_load(&env, ebp, 0xffffff88u, 4);
    lift_store(&env, ebp, 0xffffffa4u, 4, ebx);
L_433fac:
    {
        (void)lift_sub(8, lift_load(&env, edi, 0x540858u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_433fcb;
    ecx = 0x540858u;
    eax = esi;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433180u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_433fcb:
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = eax + 1u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433fac;
    ecx = lift_load(&env, ebp, 0xffffff88u, 4);
    ebx = lift_load(&env, ebp, 0xffffffa0u, 4);
    ecx = ecx + 0xdu;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffff88u, 4, ecx);
    lift_store(&env, ebp, 0xffffffa0u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_433fa4;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42eee0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    lift_store(&env, ebp, 0xffffff94u, 4, eax);
L_433ffc:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffff90u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    edx = edx ^ edx;
    eax = eax + esi;
    lift_store(&env, ebp, 0xffffff8cu, 4, edx);
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
L_43400f:
    ebx = lift_load(&env, ebp, 0xffffff90u, 4);
    edi = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = lift_load(&env, ebp, 0xffffff8cu, 4);
    ecx = ecx ^ ecx;
    edi = edi + eax;
L_43401c:
    edx = (edi + ecx);
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x734u, 1), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_43404f;
    edx = lift_load(&env, edx, 0x731u, 4);
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x430850u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, eax, 0x48u, 2, 0x0u);
    lift_store(&env, eax, 0x93u, 1, 0x1u);
    lift_store(&env, eax, 0x4eu, 1, 0x3cu);
    lift_store(&env, ebx, 0x324u, 4, eax);
L_43404f:
    ecx = ecx + 1u;
    ebx = ebx + 0x4u;
    {
        (void)lift_sub(32, ecx, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_43401c;
    edx = lift_load(&env, ebp, 0xffffff8cu, 4);
    ecx = lift_load(&env, ebp, 0xffffff90u, 4);
    edx = edx + 0x4u;
    ecx = ecx + 0x10u;
    lift_store(&env, ebp, 0xffffff8cu, 4, edx);
    lift_store(&env, ebp, 0xffffff90u, 4, ecx);
    {
        (void)lift_sub(32, edx, 0x34u, &fl);
    }
    if (!fl.zf)
        goto L_43400f;
    edi = lift_load(&env, ebp, 0xffffff94u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edi = edi + edx;
    eax = eax + 0xd0u;
    lift_store(&env, ebp, 0xffffff94u, 4, edi);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_sub(32, edi, 0x104u, &fl);
    }
    if (!fl.zf)
        goto L_433ffc;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xffffffe8u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4342d7;
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
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
L_4340a5:
    ecx = (ecx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    lift_store(&env, ebx, 0x540858u, 1, ((ecx >> 8) & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x839u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), ((ecx >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4342ab;
L_4340bb:
    eax = lift_load(&env, ebp, 0xffffff80u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4340e9;
    ecx = lift_load(&env, ebp, 0xffffffc4u, 4);
    ecx = ecx + lift_load(&env, ebp, 0xffffffa4u, 4);
L_4340c8:
    edx = edx ^ edx;
    edi = lift_load(&env, ebp, 0xffffffa0u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    edi = edi - edx;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4340e9;
    ecx = ecx - 0xdu;
    edx = (edx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    eax = eax - 1u;
    lift_store(&env, ecx, 0x540865u, 1, ((edx >> 8) & 0xffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4340c8;
L_4340e9:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4340f2;
    lift_store(&env, ebp, 0xffffffe8u, 1, 0x1u);
L_4340f2:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_434122;
    ecx = lift_load(&env, ebp, 0xffffffc0u, 4);
    ecx = ecx + lift_load(&env, ebp, 0xffffffa4u, 4);
    edi = lift_load(&env, ebp, 0xffffffa0u, 4);
L_434103:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    edx = edx + edi;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_434122;
    ecx = ecx + 0xdu;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = eax + 1u;
    lift_store(&env, ecx, 0x54084bu, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_434103;
L_434122:
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.zf)
        goto L_43412b;
    lift_store(&env, ebp, 0xffffffe8u, 1, 0x1u);
L_43412b:
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esi, 0x839u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4342c0;
L_43413a:
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = eax - 1u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_434166;
    ecx = lift_load(&env, ebp, 0xffffffacu, 4);
    ecx = ecx + eax;
L_434147:
    edx = edx ^ edx;
    edi = lift_load(&env, ebp, 0xffffffa4u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    edi = edi - edx;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_434166;
    ecx = ecx - 1u;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = eax - 1u;
    lift_store(&env, ecx, 0x540859u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_434147;
L_434166:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_43416f;
    lift_store(&env, ebp, 0xffffffe8u, 1, 0x1u);
L_43416f:
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43419d;
    ecx = lift_load(&env, ebp, 0xffffffb0u, 4);
    edi = lift_load(&env, ebp, 0xffffffa4u, 4);
    ecx = ecx + eax;
L_434180:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    edx = edx + edi;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_43419d;
    ecx = ecx + 1u;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = eax + 1u;
    lift_store(&env, ecx, 0x540857u, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_434180;
L_43419d:
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (fl.zf)
        goto L_4341a6;
    lift_store(&env, ebp, 0xffffffe8u, 1, 0x1u);
L_4341a6:
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x839u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_433efb;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffa0u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_43422c;
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = eax - 1u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4341ec;
    ecx = lift_load(&env, ebp, 0xffffff7cu, 4);
    ecx = ecx + eax;
L_4341cd:
    edx = edx ^ edx;
    edi = lift_load(&env, ebp, 0xffffffa4u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    edi = edi - edx;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4341ec;
    ecx = ecx - 1u;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = eax - 1u;
    lift_store(&env, ecx, 0x540859u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4341cd;
L_4341ec:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4341f5;
    lift_store(&env, ebp, 0xffffffe8u, 1, 0x1u);
L_4341f5:
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_434223;
    ecx = lift_load(&env, ebp, 0xffffffb4u, 4);
    edi = lift_load(&env, ebp, 0xffffffa4u, 4);
    ecx = ecx + eax;
L_434206:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    edx = edx + edi;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_434223;
    ecx = ecx + 1u;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = eax + 1u;
    lift_store(&env, ecx, 0x540857u, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_434206;
L_434223:
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (fl.zf)
        goto L_43422c;
    lift_store(&env, ebp, 0xffffffe8u, 1, 0x1u);
L_43422c:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffa0u, 4), 0x4u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_433efb;
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = eax - 1u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_434262;
    ecx = lift_load(&env, ebp, 0xffffffb8u, 4);
    ecx = ecx + eax;
L_434243:
    edx = edx ^ edx;
    edi = lift_load(&env, ebp, 0xffffffa4u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    edi = edi - edx;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_434262;
    ecx = ecx - 1u;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = eax - 1u;
    lift_store(&env, ecx, 0x540859u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_434243;
L_434262:
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_43426b;
    lift_store(&env, ebp, 0xffffffe8u, 1, 0x1u);
L_43426b:
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_434299;
    ecx = lift_load(&env, ebp, 0xffffffbcu, 4);
    edi = lift_load(&env, ebp, 0xffffffa4u, 4);
    ecx = ecx + eax;
L_43427c:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x838u, 1)) & 0xffu);
    edx = edx + edi;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_434299;
    ecx = ecx + 1u;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = eax + 1u;
    lift_store(&env, ecx, 0x540857u, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_43427c;
L_434299:
    {
        (void)lift_sub(32, eax, 0xdu, &fl);
    }
    if (fl.zf)
        goto L_433efb;
    lift_store(&env, ebp, 0xffffffe8u, 1, 0x1u);
    goto L_433efb;
L_4342ab:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4340bb;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4340bb;
    goto L_43412b;
L_4342c0:
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_43413a;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_43413a;
    goto L_4341a6;
L_4342d7:
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffff9cu, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
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

uint32_t lifted_board_swap_marked(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_BOARD_SWAP_MARKED_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_BOARD_SWAP_MARKED_STACK, 0, entry);
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
    esp = esp - 0x18u;
    esi = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x436030u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (!fl.cf)
        goto L_436175;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
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
L_436175:
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = 0x598d30u;
    ecx = (ebp + 0xffffffd8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    ebx = (ebp + 0xffffffd4u);
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4360b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = ((edx * 4u));
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = eax + esi;
    eax = eax + edx;
    edi = edi - 1u;
    lift_store(&env, eax, 0xb94u, 1, 0x2u);
    edx = edx ^ edx;
    eax = 0x598d30u;
    edx = (edx & 0xffff0000u) | (((edi & 0xffffu)) & 0xffffu);
    ecx = (ebp + 0xffffffe0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    ebx = (ebp + 0xffffffdcu);
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4360b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = ((eax * 4u));
    ecx = ecx - eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    ecx = ecx + eax;
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = ecx + esi;
    ecx = ecx + ebx;
    lift_store(&env, ecx, 0xb94u, 1, 0x2u);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = ((eax * 4u));
    ecx = ecx - eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    ecx = ecx + eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = ecx + esi;
    ebx = lift_load(&env, ecx, (eax * 4u) + 0x220u, 4);
    lift_store(&env, ecx, (eax * 4u) + 0x87cu, 4, ebx);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = ((eax * 4u));
    ecx = ecx - eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    ecx = ecx + eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = ecx + esi;
    lift_store(&env, ecx, (eax * 4u) + 0x220u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = ((eax * 4u));
    ecx = ecx - eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    ecx = ecx + eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = ecx + esi;
    edi = lift_load(&env, ecx, (eax * 4u) + 0x220u, 4);
    lift_store(&env, ecx, (eax * 4u) + 0x87cu, 4, edi);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = ((eax * 4u));
    ecx = ecx - eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    ecx = ecx + eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = ecx + esi;
    edx = 0x44d1e0u;
    lift_store(&env, ecx, (eax * 4u) + 0x220u, 4, 0x0u);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5u;
    eax = ebx;
    lift_store(&env, ebx, 0x4eu, 1, 0x64u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x44d1e0u;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5u;
    eax = edi;
    lift_store(&env, edi, 0x4eu, 1, 0x64u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x15cu, 1)) & 0xffu);
    edx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x430800u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = ((eax * 4u));
    ecx = ecx - eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    ecx = ecx + eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = esi;
    eax = eax + ecx;
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    ecx = ecx + eax;
    lift_store(&env, ecx, 0x220u, 4, edx);
    ecx = edx;
    eax = ecx;
    edx = lift_load(&env, ebx, 0xd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    edx = lift_load(&env, ebx, 0xb8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x15cu, 1)) & 0xffu);
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x15cu, 1)) & 0xffu);
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x53bcc8u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), lift_load(&env, edx, 0x53bcc8u, 1), &fl);
    }
    if (!fl.zf)
        goto L_43642d;
    edx = 0x44c860u;
L_436375:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x15cu, 1)) & 0xffu);
    edx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x430800u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = ((eax * 4u));
    ecx = ecx - eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    ecx = ecx + eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    ecx = ecx + esi;
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ecx, (esi * 4u) + 0x220u, 4, edx);
    esi = edx;
    eax = esi;
    edx = lift_load(&env, edi, 0xd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    edx = lift_load(&env, edi, 0xb8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x15cu, 1)) & 0xffu);
    edx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x15cu, 1)) & 0xffu);
    ecx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x53bcc8u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), lift_load(&env, ecx, 0x53bcc8u, 1), &fl);
    }
    if (!fl.zf)
        goto L_436437;
    edx = 0x44c860u;
L_436417:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
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
L_43642d:
    edx = 0x44d330u;
    goto L_436375;
L_436437:
    edx = 0x44d330u;
    goto L_436417;
}

uint32_t lifted_board_collapse_marked(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_BOARD_COLLAPSE_MARKED_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_BOARD_COLLAPSE_MARKED_STACK, 0, entry);
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
    esp = esp - 0x20u;
    esi = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x436030u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x436070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_438788;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_438788;
    edx = edx ^ edx;
    ecx = (esi + 0x34u);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    ebx = ebx ^ ebx;
L_438575:
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x34u, &fl);
        eax = r;
    }
    edx = ecx;
    edi = (esi + eax);
L_43857e:
    edi = edi + 0x4u;
    eax = lift_load(&env, edi, 0x21cu, 4);
    lift_store(&env, edi, 0x878u, 4, eax);
    lift_store(&env, edi, 0x21cu, 4, ebx);
    {
        (void)lift_sub(32, edi, edx, &fl);
    }
    if (!fl.zf)
        goto L_43857e;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = eax + 1u;
    ecx = ecx + 0x34u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_438575;
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
L_4385ae:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = (ebp + 0xffffffd4u);
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (ebp + 0xffffffd0u);
    eax = esi;
    edi = 0xcu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4388a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_438646;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + 0x30u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
L_4385d9:
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffffd0u, 4), 0x34u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + esi;
    eax = lift_load(&env, eax, (edx * 4u) + 0x87cu, 4);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, edx, 0x220u, 4, eax);
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffffd0u, 4), 0x34u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffe6u, 4);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    lift_store(&env, eax, (edx * 4u) + 0x87cu, 4, 0x0u);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edi & 0xffffu);
    eax = esi;
    edx = lift_load(&env, edx, 0x220u, 4);
    edi = edi - 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x438470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = (ebp + 0xffffffd4u);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax - 0x4u;
    edx = edx + 1u;
    ebx = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = esi;
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4388a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4385d9;
L_438646:
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = esi;
    ecx = ecx ^ ecx;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ebp + 0xffffffd4u);
    ebx = (ebp + 0xffffffd0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x438830u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4386e4;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = ((edi * 4u));
    eax = eax + edx;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
L_438676:
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffffd0u, 4), 0x34u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + esi;
    eax = lift_load(&env, eax, (edx * 4u) + 0x87cu, 4);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, edx, 0x220u, 4, eax);
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffffd0u, 4), 0x34u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffe6u, 4);
    edx = (esi + eax);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    lift_store(&env, edx, (eax * 4u) + 0x87cu, 4, 0x0u);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edi & 0xffffu);
    eax = esi;
    edx = lift_load(&env, edx, 0x220u, 4);
    edi = edi - 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x438470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = (ebp + 0xffffffd4u);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax - 0x4u;
    edx = edx + 1u;
    ebx = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = esi;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x438830u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_438676;
L_4386e4:
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = ecx + 0x34u;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_4385ae;
    eax = eax ^ eax;
    ebx = (esi + 0x34u);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
L_438705:
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x34u, &fl);
        eax = r;
    }
    ecx = ebx;
    eax = eax + esi;
L_43870d:
    edi = lift_load(&env, eax, 0x220u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_43872f;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edi, 0x8u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, edi, 0x10u, 2), &fl);
    }
    if (!fl.zf)
        goto L_438794;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edi, 0xau, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, edi, 0x18u, 2), &fl);
    }
    if (!fl.zf)
        goto L_438794;
L_43872f:
    eax = eax + 0x4u;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.cf)
        goto L_43870d;
    edi = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = edi + 1u;
    ebx = ebx + 0x34u;
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_438705;
    ebx = (ebx & 0xffffff00u) | ((0x32u) & 0xffu);
    edx = edx ^ edx;
    ecx = (esi + 0x34u);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
L_43874f:
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x34u, &fl);
        eax = r;
    }
    edx = ecx;
    eax = eax + esi;
L_438757:
    edi = lift_load(&env, eax, 0x220u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_438772;
    lift_store(&env, edi, 0x93u, 1, 0x0u);
    lift_store(&env, edi, 0x95u, 1, 0x1u);
    lift_store(&env, edi, 0x4eu, 1, (ebx & 0xffu));
L_438772:
    eax = eax + 0x4u;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_438757;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = eax + 1u;
    ecx = ecx + 0x34u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_43874f;
L_438788:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
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
L_438794:
    eax = 0x1u;
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

uint32_t lifted_board_clear_marked_extra(const VertrixCalls *calls,
                                         const VertrixFactoryServices *services,
                                         const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_BOARD_CLEAR_MARKED_EXTRA_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_BOARD_CLEAR_MARKED_EXTRA_STACK, 0,
               entry);
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
    esp = esp - 0x14u;
    ecx = (eax + 0x34u);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = eax + 0x104u;
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
L_4398df:
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = esi;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
L_4398ed:
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0xb94u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_439917;
    eax = lift_load(&env, esi, 0xbdcu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_43990d;
    edi = lift_load(&env, eax, 0x158u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43990d:
    lift_store(&env, ecx, 0xbdcu, 4, 0x0u);
L_439917:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx + 1u;
    ecx = ecx + 0x4u;
    esi = esi + 0x4u;
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4398ed;
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    edi = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = ecx + 0x34u;
    ebx = ebx + 0xdu;
    esi = esi + 0x34u;
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4398df;
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

uint32_t lifted_f43a6f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F43A6F0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F43A6F0_STACK, 0, entry);
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
    esp = esp - 0x24u;
    edx = eax;
    eax = (ebp + 0xffffffc8u);
    ecx = 0x4ec1ecu;
    ebx = 0x514bd0u;
    edi = 0x1u;
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
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    lift_store(&env, ebp, 0xffffffe0u, 1, ((eax >> 8) & 0xffu));
    eax = edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax + 0x19cu;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481f30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (eax + 0xfffffe64u);
    lift_store(&env, ebp, 0xffffffd4u, 4, 0x2u);
    eax = 0xd00u;
    lift_store(&env, edx, 0x158u, 4, 0x514cb4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_43a928;
L_43a76e:
    lift_store(&env, edx, 0x15cu, 4, eax);
    eax = 0x218u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_43a79a;
    esi = 0x5u;
    edi = 0x2u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x425e20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
L_43a79a:
    lift_store(&env, edx, 0x450u, 4, eax);
    eax = 0x14u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_43a7c6;
    ecx = 0x7u;
    ebx = 0x2u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487920u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
L_43a7c6:
    lift_store(&env, edx, 0x468u, 4, eax);
    eax = 0x20u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_43a945;
L_43a7de:
    lift_store(&env, edx, 0x190u, 1, 0x0u);
    lift_store(&env, edx, 0x170u, 4, 0x0u);
    lift_store(&env, edx, 0x174u, 4, 0x0u);
    lift_store(&env, edx, 0x178u, 4, 0x0u);
    lift_store(&env, edx, 0x18cu, 4, 0x0u);
    lift_store(&env, edx, 0x180u, 4, 0xcu);
    lift_store(&env, edx, 0x488u, 4, 0x0u);
    lift_store(&env, edx, 0x4c4u, 1, 0x0u);
    lift_store(&env, edx, 0x4c5u, 1, 0x1u);
    lift_store(&env, edx, 0x4c8u, 4, 0x0u);
    lift_store(&env, edx, 0x4ccu, 1, 0x0u);
    lift_store(&env, edx, 0x4cdu, 1, 0x0u);
    lift_store(&env, edx, 0x194u, 4, 0x0u);
    lift_store(&env, edx, 0x198u, 4, 0x0u);
    lift_store(&env, edx, 0x3b0u, 4, 0x0u);
    lift_store(&env, edx, 0x3b4u, 4, 0x0u);
    lift_store(&env, edx, 0x4d0u, 4, 0x0u);
    lift_store(&env, edx, 0x4d4u, 4, 0x0u);
    lift_store(&env, edx, 0x4d8u, 4, 0x0u);
    lift_store(&env, edx, 0x184u, 4, 0x0u);
    lift_store(&env, edx, 0x4dcu, 1, 0x2u);
    lift_store(&env, edx, 0x4e0u, 4, 0x0u);
    lift_store(&env, edx, 0x3f4u, 4, 0x0u);
    lift_store(&env, edx, 0x44cu, 4, 0x0u);
    lift_store(&env, edx, 0x454u, 4, 0x0u);
    lift_store(&env, edx, 0x464u, 4, 0x0u);
    lift_store(&env, edx, 0x4e4u, 4, 0x0u);
    lift_store(&env, edx, 0x3f8u, 4, 0x0u);
    lift_store(&env, edx, 0x4e8u, 4, 0x0u);
    lift_store(&env, edx, 0x474u, 4, 0x1u);
    lift_store(&env, edx, 0x3acu, 4, 0x0u);
    lift_store(&env, edx, 0x46cu, 4, eax);
    eax = lift_load(&env, 0u, 0x532bc0u, 4);
    lift_store(&env, edx, 0x17cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    env.chain = eax;
    eax = edx;
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
L_43a928:
    ecx = 0x3u;
    ebx = 0x2u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42e870u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    goto L_43a76e;
L_43a945:
    esi = 0x9u;
    edi = 0x2u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x425d30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    goto L_43a7de;
}

uint32_t lifted_f43ad70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F43AD70_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F43AD70_STACK, 0, entry);
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
    esp = esp - 0x18u;
    esi = eax;
    eax = lift_load(&env, eax, 0x454u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_43adad;
    eax = lift_load(&env, esi, 0x450u, 4);
    edx = lift_load(&env, eax, 0x178u, 4);
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_43adb7;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esi, 0x450u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_43ae20;
L_43adad:
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
L_43adb7:
    ecx = (ebp + 0xffffffe0u);
    ebx = (ebp + 0xffffffe8u);
    edx = (ebp + 0xffffffe4u);
    eax = lift_load(&env, esi, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431fa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffddu, 4);
    ecx = lift_load(&env, ebp, 0xffffffe5u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe1u, 4);
    edx = esi;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ecx = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = lift_load(&env, esi, 0x450u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x425f60u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, esi, 0x450u, 4);
    lift_store(&env, eax, 0x178u, 4, 0x0u);
    eax = lift_load(&env, esi, 0x450u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43b5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esi, 0x458u, 4);
    eax = lift_load(&env, esi, 0x450u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_43adad;
L_43ae20:
    eax = lift_load(&env, esi, 0x450u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43b5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esi, 0x458u, 4);
    eax = lift_load(&env, esi, 0x450u, 4);
    ecx = (ebp + 0xffffffdcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    ebx = (ebp + 0xffffffd8u);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    edx = (ebp + 0xffffffd4u);
    eax = lift_load(&env, esi, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431b20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_43adad;
    edx = lift_load(&env, esi, 0x450u, 4);
    edi = lift_load(&env, edx, 0x160u, 4);
    {
        (void)lift_sub(32, edi, 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_43afac;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = lift_load(&env, edx, 0x168u, 4);
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_43af33;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x160u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4761d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x160u, 2)) & 0xffffu);
L_43aebd:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476280u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_43aec2:
    edx = lift_load(&env, esi, 0x450u, 4);
    edi = lift_load(&env, edx, 0x16cu, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43af67;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x168u, 4), &fl);
    }
    if (!fl.zf)
        goto L_43adad;
    eax = lift_load(&env, esi, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_43adad;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x166u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4761d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x166u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476280u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
L_43af33:
    if (fl.sf == fl.of)
        goto L_43aec2;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x162u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4761d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x162u, 2)) & 0xffffu);
    goto L_43aebd;
L_43af67:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    ebx = (edi + 0xffffffffu);
    ecx = ecx ^ ecx;
    lift_store(&env, edx, 0x16cu, 4, ebx);
    edx = edx ^ edx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x164u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4761d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x164u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476280u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
L_43afac:
    {
        (void)lift_sub(32, edi, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_43b0e1;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = lift_load(&env, edx, 0x168u, 4);
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43b01b;
    if (fl.sf != fl.of)
        goto L_43b057;
    edi = lift_load(&env, edx, 0x16cu, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_43b093;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (edi + 0xffffffffu);
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    lift_store(&env, edx, 0x16cu, 4, eax);
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x164u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4761d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x164u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476280u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
L_43b01b:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x160u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4761d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x160u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476280u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
L_43b057:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x162u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4761d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x162u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476280u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
L_43b093:
    eax = lift_load(&env, esi, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_43adad;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x166u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4761d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x166u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476280u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
L_43b0e1:
    ecx = lift_load(&env, edx, 0x16cu, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43b150;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    ebx = lift_load(&env, edx, 0x168u, 4);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43b01b;
    if (fl.sf != fl.of)
        goto L_43b057;
    eax = lift_load(&env, esi, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_43adad;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x166u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4761d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x166u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476280u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
L_43b150:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ecx + 0xffffffffu);
    ebx = ebx ^ ebx;
    ecx = ecx ^ ecx;
    lift_store(&env, edx, 0x16cu, 4, eax);
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x164u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4761d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x54d640u;
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x164u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476280u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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

uint32_t lifted_f43c140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F43C140_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F43C140_STACK, 0, entry);
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
    edi = 0x1u;
    ecx = ecx ^ ecx;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43c166;
    ecx = 0x452e00u;
L_43c156:
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c166:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_43c180;
    ecx = 0x452d70u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c180:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_43c1a4;
    ecx = 0x453150u;
    lift_store(&env, eax, 0x3dcu, 4, 0x5u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c1a4:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_43c1c8;
    ecx = 0x453150u;
    lift_store(&env, eax, 0x3dcu, 4, 0x6u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c1c8:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_43c1e2;
    ecx = 0x453ad0u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c1e2:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x6u, &fl);
    }
    if (!fl.zf)
        goto L_43c206;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ecx = 0x452880u;
    lift_store(&env, esi, 0x3c0u, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c206:
    {
        (void)lift_sub(8, (edx & 0xffu), 0xcu, &fl);
    }
    if (!fl.zf)
        goto L_43c220;
    ecx = 0x4528e0u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c220:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x7u, &fl);
    }
    if (!fl.zf)
        goto L_43c291;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43c249;
    ecx = 0x4547b0u;
    lift_store(&env, eax, 0x3d4u, 4, 0x0u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c249:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_43c269;
    ecx = 0x4547b0u;
    lift_store(&env, eax, 0x3d4u, 4, edi);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c269:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_43c156;
    ecx = 0x4547b0u;
    lift_store(&env, eax, 0x3d4u, 4, 0x2u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c291:
    {
        (void)lift_sub(8, (edx & 0xffu), 0xbu, &fl);
    }
    if (!fl.zf)
        goto L_43c2ab;
    ecx = 0x455ca0u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c2ab:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_43c2d1;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    eax = eax - edi;
    ecx = 0x454560u;
    lift_store(&env, esi, 0x3e8u, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c2d1:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x9u, &fl);
    }
    if (!fl.zf)
        goto L_43c2f5;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ecx = 0x452d10u;
    lift_store(&env, esi, 0x3c8u, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c2f5:
    {
        (void)lift_sub(8, (edx & 0xffu), 0xau, &fl);
    }
    if (!fl.zf)
        goto L_43c30f;
    ecx = 0x455b20u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c30f:
    {
        (void)lift_sub(8, (edx & 0xffu), 0xdu, &fl);
    }
    if (!fl.zf)
        goto L_43c343;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x190u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_43c33c;
    ecx = 0x453f40u;
L_43c322:
    lift_store(&env, esi, 0x3d0u, 4, 0x0u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c33c:
    ecx = 0x454250u;
    goto L_43c322;
L_43c343:
    {
        (void)lift_sub(8, (edx & 0xffu), 0xeu, &fl);
    }
    if (!fl.zf)
        goto L_43c3b4;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43c36c;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x0u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c36c:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_43c38c;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, edi);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c38c:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_43c156;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x2u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c3b4:
    {
        (void)lift_sub(8, (edx & 0xffu), 0xfu, &fl);
    }
    if (!fl.zf)
        goto L_43c429;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43c3dd;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x3u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c3dd:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_43c401;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x4u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c401:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_43c156;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x5u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c429:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x10u, &fl);
    }
    if (!fl.zf)
        goto L_43c49e;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43c452;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x6u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c452:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_43c476;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x7u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c476:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_43c156;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x8u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c49e:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x14u, &fl);
    }
    if (!fl.zf)
        goto L_43c513;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43c4db;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x190u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_43c4d4;
    ecx = 0x453f40u;
L_43c4ba:
    lift_store(&env, esi, 0x3d0u, 4, 0x1u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c4d4:
    ecx = 0x454250u;
    goto L_43c4ba;
L_43c4db:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_43c156;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x190u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_43c50c;
    ecx = 0x453f40u;
L_43c4f2:
    lift_store(&env, esi, 0x3d0u, 4, 0x2u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c50c:
    ecx = 0x454250u;
    goto L_43c4f2;
L_43c513:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x13u, &fl);
    }
    if (!fl.zf)
        goto L_43c588;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43c53c;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x9u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c53c:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_43c560;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0xau);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c560:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_43c156;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0xbu);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c588:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x15u, &fl);
    }
    if (!fl.zf)
        goto L_43c66d;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43c5b5;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0xcu);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c5b5:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_43c5d9;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0xdu);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c5d9:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_43c5fd;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0xeu);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c5fd:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_43c621;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0xfu);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c621:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_43c645;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x10u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c645:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x6u, &fl);
    }
    if (!fl.zf)
        goto L_43c156;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x11u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c66d:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x16u, &fl);
    }
    if (!fl.zf)
        goto L_43c752;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43c69a;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x12u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c69a:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_43c6be;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x13u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c6be:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_43c6e2;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x14u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c6e2:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_43c706;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x16u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c706:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_43c72a;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x15u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c72a:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x6u, &fl);
    }
    if (!fl.zf)
        goto L_43c156;
    ecx = 0x453c00u;
    lift_store(&env, eax, 0x3ccu, 4, 0x17u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c752:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x17u, &fl);
    }
    if (!fl.zf)
        goto L_43c76c;
    ecx = 0x45b9c0u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c76c:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x12u, &fl);
    }
    if (!fl.zf)
        goto L_43c823;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43c799;
    ecx = 0x4549d0u;
    lift_store(&env, eax, 0x3d8u, 4, 0x5u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c799:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_43c7bd;
    ecx = 0x4549d0u;
    lift_store(&env, eax, 0x3d8u, 4, 0x7u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c7bd:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_43c7e1;
    ecx = 0x4549d0u;
    lift_store(&env, eax, 0x3d8u, 4, 0x9u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c7e1:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_43c805;
    ecx = 0x454c30u;
    lift_store(&env, eax, 0x3d8u, 4, 0x5u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c805:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_43c156;
    ecx = 0x454e90u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c823:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x11u, &fl);
    }
    if (!fl.zf)
        goto L_43c83d;
    ecx = 0x455020u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c83d:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x18u, &fl);
    }
    if (!fl.zf)
        goto L_43c861;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ecx = 0x452830u;
    lift_store(&env, esi, 0x3bcu, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c861:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x19u, &fl);
    }
    if (!fl.zf)
        goto L_43c93a;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_43c89a;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x7u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_43c89a;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ecx = 0x455e50u;
    lift_store(&env, esi, 0x3e4u, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c89a:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x7u, &fl);
    }
    if (!fl.zf)
        goto L_43c8b4;
    ecx = 0x4554a0u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c8b4:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_43c156;
    edx = 0x4u;
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
        goto L_43c8e8;
    ecx = 0x455670u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c8e8:
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43c902;
    ecx = 0x455790u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c902:
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_43c91c;
    ecx = 0x4558e0u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c91c:
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_43c156;
    ecx = 0x455a00u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c93a:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1du, &fl);
    }
    if (!fl.zf)
        goto L_43c95e;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ecx = 0x45b4c0u;
    lift_store(&env, esi, 0x400u, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c95e:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1cu, &fl);
    }
    if (!fl.zf)
        goto L_43c978;
    ecx = 0x455600u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c978:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1au, &fl);
    }
    if (!fl.zf)
        goto L_43c99c;
    ecx = 0x453460u;
    lift_store(&env, eax, 0x3e0u, 4, 0xfffffffeu);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c99c:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1bu, &fl);
    }
    if (!fl.zf)
        goto L_43c9c0;
    ecx = 0x453460u;
    lift_store(&env, eax, 0x3e0u, 4, 0x6u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c9c0:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1eu, &fl);
    }
    if (!fl.zf)
        goto L_43c9e4;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ecx = 0x452a30u;
    lift_store(&env, esi, 0x3c4u, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43c9e4:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1fu, &fl);
    }
    if (!fl.zf)
        goto L_43ca08;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ecx = 0x452b00u;
    lift_store(&env, esi, 0x3c4u, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43ca08:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_43ca2c;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ecx = 0x452bb0u;
    lift_store(&env, esi, 0x3c4u, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43ca2c:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x21u, &fl);
    }
    if (!fl.zf)
        goto L_43ca50;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ecx = 0x452c60u;
    lift_store(&env, esi, 0x3c4u, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43ca50:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x23u, &fl);
    }
    if (!fl.zf)
        goto L_43ca6a;
    ecx = 0x4535d0u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43ca6a:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_43ca84;
    ecx = 0x453670u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43ca84:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x32u, &fl);
    }
    if (!fl.zf)
        goto L_43caa8;
    ecx = 0x4536c0u;
    lift_store(&env, eax, 0x3fcu, 4, 0x0u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43caa8:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x33u, &fl);
    }
    if (!fl.zf)
        goto L_43cac8;
    ecx = 0x453710u;
    lift_store(&env, eax, 0x3fcu, 4, edi);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cac8:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x34u, &fl);
    }
    if (!fl.zf)
        goto L_43caec;
    ecx = 0x453760u;
    lift_store(&env, eax, 0x3fcu, 4, 0x2u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43caec:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2fu, &fl);
    }
    if (!fl.zf)
        goto L_43cb06;
    ecx = 0x4537b0u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cb06:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x31u, &fl);
    }
    if (!fl.zf)
        goto L_43cb20;
    ecx = 0x453800u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cb20:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x22u, &fl);
    }
    if (!fl.zf)
        goto L_43cb3a;
    ecx = 0x453620u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cb3a:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x24u, &fl);
    }
    if (!fl.zf)
        goto L_43cb54;
    ecx = 0x453850u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cb54:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x28u, &fl);
    }
    if (!fl.zf)
        goto L_43cb6e;
    ecx = 0x4538a0u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cb6e:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x29u, &fl);
    }
    if (!fl.zf)
        goto L_43cb88;
    ecx = 0x4538f0u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cb88:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2au, &fl);
    }
    if (!fl.zf)
        goto L_43cba2;
    ecx = 0x453940u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cba2:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_43cbbc;
    ecx = 0x453990u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cbbc:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2eu, &fl);
    }
    if (!fl.zf)
        goto L_43cbd6;
    ecx = 0x4539e0u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cbd6:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x25u, &fl);
    }
    if (!fl.zf)
        goto L_43cbfa;
    ecx = 0x453b90u;
    lift_store(&env, eax, 0x3f8u, 4, 0x0u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cbfa:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x26u, &fl);
    }
    if (!fl.zf)
        goto L_43cc1a;
    ecx = 0x453b90u;
    lift_store(&env, eax, 0x3f8u, 4, edi);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cc1a:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x27u, &fl);
    }
    if (!fl.zf)
        goto L_43cc3a;
    ecx = 0x453b90u;
    lift_store(&env, eax, 0x3f8u, 4, 0x2u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cc3a:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2bu, &fl);
    }
    if (!fl.zf)
        goto L_43cc50;
    ecx = 0x453a30u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cc50:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2cu, &fl);
    }
    if (!fl.zf)
        goto L_43cc66;
    ecx = 0x453a80u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cc66:
    edi = edi ^ edi;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43cc74;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
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
L_43cc74:
    edx = ecx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
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

uint32_t lifted_piece(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PIECE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PIECE_STACK, 0, entry);
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
    edx = lift_load(&env, eax, 0x4c8u, 4);
    {
        (void)lift_sub(32, edx, 0x2eu, &fl);
    }
    if (!fl.zf)
        goto L_43d1fd;
    edx = (ebp + 0xfffffff4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffecu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), lift_load(&env, ebp, 0xfffffff4u, 1), &fl);
    }
    if (!fl.zf)
        goto L_43d1d0;
L_43d1b1:
    edx = (ebp + 0xffffffecu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), lift_load(&env, ebp, 0xfffffff4u, 1), &fl);
    }
    if (fl.zf)
        goto L_43d1b1;
L_43d1d0:
    edx = (ebp + 0xfffffff0u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), lift_load(&env, ebp, 0xfffffff4u, 1), &fl);
    }
    if (fl.zf)
        goto L_43d1d0;
    {
        (void)lift_sub(8, (eax & 0xffu), lift_load(&env, ebp, 0xffffffecu, 1), &fl);
    }
    if (fl.zf)
        goto L_43d1d0;
L_43d1e7:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    lift_store(&env, ebx, 0x0u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    lift_store(&env, ecx, 0x0u, 1, (eax & 0xffu));
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
L_43d1fd:
    edx = (ebp + 0xfffffff4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esi, 0x4c8u, 4);
    {
        (void)lift_sub(32, edx, 0x2au, &fl);
    }
    if (!fl.zf)
        goto L_43d22a;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff0u, 1, (eax & 0xffu));
    lift_store(&env, ebp, 0xffffffecu, 1, (eax & 0xffu));
L_43d219:
    edx = lift_load(&env, esi, 0x4c8u, 4);
    {
        (void)lift_sub(32, edx, 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_43d1e7;
    lift_store(&env, ebp, 0xfffffff0u, 1, 0x5u);
    goto L_43d1e7;
L_43d22a:
    edx = (ebp + 0xffffffecu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, esi, 0x4c8u, 4);
    {
        (void)lift_sub(32, edx, 0x29u, &fl);
    }
    if (!fl.zf)
        goto L_43d247;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff0u, 1, (eax & 0xffu));
    goto L_43d219;
L_43d247:
    edx = (ebp + 0xfffffff0u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_43d219;
}

uint32_t lifted_board_particles_setup(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_BOARD_PARTICLES_SETUP_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_BOARD_PARTICLES_SETUP_STACK, 0, entry);
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
    esp = esp - 0x1cu;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = edx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4816f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_43e5bc;
L_43e4f1:
    edi = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (edi + 0x708u);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
L_43e4fd:
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_43e510;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43e510:
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
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43e740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xc8u;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax & 0xffffu;
    edi = edi + 0x4u;
    lift_store(&env, esi, 0x58u, 4, eax);
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, edi, 0x158u, 4, esi);
    {
        (void)lift_sub(32, edi, ecx, &fl);
    }
    if (!fl.zf)
        goto L_43e4fd;
    eax = 0x15cu;
    edi = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_43e72d;
L_43e56f:
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
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43e840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, edi, 0x870u, 4, esi);
    lift_store(&env, eax, 0x968u, 4, 0x0u);
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
L_43e5bc:
    edx = lift_load(&env, eax, 0x4u, 4);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    eax = lift_load(&env, eax, 0x8u, 4);
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_43e627;
L_43e5d6:
    esi = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = ecx ^ ecx;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_43e61f;
    esi = lift_load(&env, ebp, 0xffffffd4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    esi = esi + ebx;
L_43e5ea:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = ecx;
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478f10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_43e617;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        (void)lift_sub(32, eax, 0x1eu, &fl);
    }
    if (!fl.cf)
        goto L_43e617;
    esi = esi + 0x4u;
    lift_store(&env, esi, 0x870u, 4, edi);
    edx = (eax + 0x1u);
    lift_store(&env, esi, 0x8e8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
L_43e617:
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (fl.cf)
        goto L_43e5ea;
L_43e61f:
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edi = edi + 1u;
    {
        (void)lift_sub(32, edi, ebx, &fl);
    }
    if (fl.cf)
        goto L_43e5d6;
L_43e627:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edi = edx;
    lift_store(&env, edx, 0x964u, 4, eax);
    eax = (edx + 0xcu);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
L_43e63b:
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_43e64e;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43e64e:
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
    eax = esi;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    lift_store(&env, edi, 0x864u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x544c48u;
    lift_store(&env, esi, 0xeu, 2, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x16u, 2, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xau;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    edx = edx + 0x2u;
    eax = esi;
    edi = edi + 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x64u, 4, 0x1eu);
    ebx = ebx ^ ebx;
    lift_store(&env, esi, 0x70u, 4, 0xb4u);
    eax = 0x598d30u;
    lift_store(&env, esi, 0x58u, 4, 0x0u);
    edx = edx ^ edx;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, esi, 0x70u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x64u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x60u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    edx = 0x457330u;
    lift_store(&env, esi, 0x5cu, 4, eax);
    eax = esi;
    lift_store(&env, esi, 0x4eu, 1, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf)
        goto L_43e63b;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_43e4f1;
L_43e72d:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_43e56f;
}

uint32_t lifted_f43f200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F43F200_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F43F200_STACK, 1, entry);
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
    esp = esp - 0x240u;
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    ebx = 0x5334a0u;
    esi = ((eax * 4u));
    edx = edx ^ edx;
    eax = (ebp + 0xfffffebcu);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    ebx = lift_load(&env, esi, ebx + 0x0u, 4);
    edx = 0x4fc5a8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x533578u;
    edx = 0x4fc5a8u;
    eax = (ebp + 0xfffffdb8u);
    ebx = lift_load(&env, esi, ebx + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_43f268;
L_43f25f:
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
L_43f268:
    edx = 0x50e113u;
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489b40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43f3a1;
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x473f10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43f28c:
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
L_43f28f:
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_43f25f;
    eax = (ebp + 0xfffffdb8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43f3ca;
    edx = (ebp + 0xfffffdb8u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4797f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43f2b7:
    edi = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = edx ^ edx;
    edi = edi + 1u;
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_div1(32, edi, &eax, &edx, &fl);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    esi = esi + 1u;
    edx = edx ^ edx;
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_div1(32, esi, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_43f390;
    lift_store(&env, ebp, 0xffffffc4u, 4, esi);
    {
        uint32_t r = lift_imul(32, esi, 0x0u, &fl);
        eax = r;
    }
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffccu, 4, edi);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
L_43f2fc:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edi = lift_load(&env, ebp, 0xffffffe4u, 4);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xfffffff4u, 4, esi);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_43f373;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    {
        uint32_t r = lift_imul(32, eax, 0x0u, &fl);
        edi = r;
    }
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    edi = edi + 1u;
L_43f31e:
    {
        uint32_t v = 0x4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1u;
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
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t v = edx;
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
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = edx;
    edx = edi;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    esi = esi + 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482f80u, eax, edx, ebx, ecx, 11, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 44u;
    edx = 0x5b9c60u;
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, esi, 0x5410f4u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x483ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = ebx + 1u;
    edx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    edx = edx + 1u;
    edi = edi + eax;
    lift_store(&env, ebp, 0xfffffff4u, 4, edx);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.cf)
        goto L_43f31e;
L_43f373:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffc8u, 4);
    edx = edx + eax;
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.cf)
        goto L_43f2fc;
L_43f390:
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_43f3a1:
    edx = 0x50e118u;
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489b40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43f28f;
    eax = (ebp + 0xfffffebcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48ac50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_43f28c;
L_43f3ca:
    eax = ecx;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478f10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4799f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_43f2b7;
}

uint32_t lifted_font_maps_initialize(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_FONT_MAPS_INITIALIZE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_FONT_MAPS_INITIALIZE_STACK, 0, entry);
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
    esp = esp - 0x88u;
    ecx = 0x541988u;
    ebx = 0x1eu;
    edx = 0x23u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff74u, 1, 0x41u);
L_43fc79:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff74u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_43fcac;
    lift_store(&env, ebp, 0xffffffd8u, 1, 0x30u);
L_43fc8a:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fcc8;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x1au;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd8u, 1, lift_load(&env, ebp, 0xffffffd8u, 1) + 1u);
    goto L_43fc8a;
L_43fcac:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x11u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x541988u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff74u, 1, lift_load(&env, ebp, 0xffffff74u, 1) + 1u);
    goto L_43fc79;
L_43fcc8:
    ebx = 0x1eu;
    edx = 0x23u;
    eax = ecx;
    ecx = 0x541b94u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 1, 0x41u);
L_43fce9:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fd0c;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x35u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x541b94u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 1, lift_load(&env, ebp, 0xffffffd4u, 1) + 1u);
    goto L_43fce9;
L_43fd0c:
    lift_store(&env, ebp, 0xffffffd0u, 1, 0x30u);
L_43fd10:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fd32;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx - 0xau;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 1, lift_load(&env, ebp, 0xffffffd0u, 1) + 1u);
    goto L_43fd10;
L_43fd32:
    ebx = 0x1eu;
    edx = 0x23u;
    eax = ecx;
    ecx = 0x541da0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffccu, 1, 0x41u);
L_43fd53:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fd76;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x35u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x541da0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffccu, 1, lift_load(&env, ebp, 0xffffffccu, 1) + 1u);
    goto L_43fd53;
L_43fd76:
    lift_store(&env, ebp, 0xffffffc8u, 1, 0x30u);
L_43fd7a:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffc8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fd9c;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x1au;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc8u, 1, lift_load(&env, ebp, 0xffffffc8u, 1) + 1u);
    goto L_43fd7a;
L_43fd9c:
    ebx = 0x1eu;
    edx = 0x23u;
    eax = ecx;
    ecx = 0x541facu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc4u, 1, 0x41u);
L_43fdbd:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffc4u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fde0;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x11u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x541facu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc4u, 1, lift_load(&env, ebp, 0xffffffc4u, 1) + 1u);
    goto L_43fdbd;
L_43fde0:
    lift_store(&env, ebp, 0xffffffc0u, 1, 0x30u);
L_43fde4:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffc0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fe06;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x1au;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 1, lift_load(&env, ebp, 0xffffffc0u, 1) + 1u);
    goto L_43fde4;
L_43fe06:
    ebx = 0x1eu;
    edx = 0x1cu;
    eax = ecx;
    ecx = 0x5421b8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffbcu, 1, 0x41u);
L_43fe27:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffbcu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fe4a;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x35u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x5421b8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffbcu, 1, lift_load(&env, ebp, 0xffffffbcu, 1) + 1u);
    goto L_43fe27;
L_43fe4a:
    lift_store(&env, ebp, 0xffffffb8u, 1, 0x30u);
L_43fe4e:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffb8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fe70;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x24u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb8u, 1, lift_load(&env, ebp, 0xffffffb8u, 1) + 1u);
    goto L_43fe4e;
L_43fe70:
    ebx = 0x1eu;
    edx = 0x1cu;
    eax = ecx;
    ecx = 0x543a48u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 1, 0x41u);
L_43fe91:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffb4u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43feb4;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x35u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x543a48u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 1, lift_load(&env, ebp, 0xffffffb4u, 1) + 1u);
    goto L_43fe91;
L_43feb4:
    lift_store(&env, ebp, 0xffffffb0u, 1, 0x30u);
L_43feb8:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffb0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fedd;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x1d6u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb0u, 1, lift_load(&env, ebp, 0xffffffb0u, 1) + 1u);
    goto L_43feb8;
L_43fedd:
    ebx = 0x1eu;
    edx = 0x1cu;
    eax = ecx;
    ecx = 0x543c54u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffacu, 1, 0x41u);
L_43fefe:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffacu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43ff21;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x35u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x543c54u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffacu, 1, lift_load(&env, ebp, 0xffffffacu, 1) + 1u);
    goto L_43fefe;
L_43ff21:
    lift_store(&env, ebp, 0xffffffa8u, 1, 0x30u);
L_43ff25:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43ff4a;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x1e0u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffa8u, 1, lift_load(&env, ebp, 0xffffffa8u, 1) + 1u);
    goto L_43ff25;
L_43ff4a:
    ebx = 0x1eu;
    edx = 0x1cu;
    eax = ecx;
    ecx = 0x543e60u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffa4u, 1, 0x41u);
L_43ff6b:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43ff8e;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x35u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x543e60u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffa4u, 1, lift_load(&env, ebp, 0xffffffa4u, 1) + 1u);
    goto L_43ff6b;
L_43ff8e:
    lift_store(&env, ebp, 0xffffffa0u, 1, 0x30u);
L_43ff92:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43ffb7;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x1eau;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffa0u, 1, lift_load(&env, ebp, 0xffffffa0u, 1) + 1u);
    goto L_43ff92;
L_43ffb7:
    ebx = 0xcu;
    edx = 0xdu;
    eax = ecx;
    ecx = 0x5423c4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff9cu, 1, 0x41u);
L_43ffd8:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff9cu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fffd;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x29u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x5423c4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff9cu, 1, lift_load(&env, ebp, 0xffffff9cu, 1) + 1u);
    goto L_43ffd8;
L_43fffd:
    lift_store(&env, ebp, 0xffffffe4u, 1, 0x30u);
L_440001:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440023;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x54u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 1, lift_load(&env, ebp, 0xffffffe4u, 1) + 1u);
    goto L_440001;
L_440023:
    ebx = 0x10u;
    edx = 0xeu;
    eax = ecx;
    ecx = 0x5425d0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f630u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 1, 0x30u);
L_440044:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440069;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x5eu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x5425d0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 1, lift_load(&env, ebp, 0xffffffe0u, 1) + 1u);
    goto L_440044;
L_440069:
    lift_store(&env, ebp, 0xffffffdcu, 1, 0x41u);
L_44006d:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffdcu, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_44008f;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x57u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 1, lift_load(&env, ebp, 0xffffffdcu, 1) + 1u);
    goto L_44006d;
L_44008f:
    edx = 0x6u;
    eax = 0x546538u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4877f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, eax, 0x8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    edx = edx + edx;
    ebx = (edx + 0x1eu);
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    ecx = 0x5427dcu;
    edx = edx + edx;
    eax = ecx;
    edx = edx + 0x23u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff8cu, 1, 0x41u);
L_4400c2:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff8cu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4400e7;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x71u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x5427dcu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff8cu, 1, lift_load(&env, ebp, 0xffffff8cu, 1) + 1u);
    goto L_4400c2;
L_4400e7:
    lift_store(&env, ebp, 0xffffff88u, 1, 0x30u);
L_4400eb:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff88u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440110;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x9cu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff88u, 1, lift_load(&env, ebp, 0xffffff88u, 1) + 1u);
    goto L_4400eb;
L_440110:
    eax = ecx;
    edx = 0x9u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f550u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x546538u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4877f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, eax, 0x8u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    eax = eax + eax;
    ebx = ebx + ebx;
    edx = (eax + 0x23u);
    ebx = ebx + 0x1eu;
    eax = 0x5429e8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xe2u;
    edx = 0x47u;
    eax = 0x5429e8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xe3u;
    edx = 0x4fu;
    eax = 0x5429e8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x9u;
    eax = 0x546538u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4877f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, eax, 0x8u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    eax = eax + eax;
    ebx = ebx + ebx;
    edx = (eax + 0x23u);
    ebx = ebx + 0x1eu;
    eax = 0x542bf4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xe4u;
    edx = 0x56u;
    eax = 0x542bf4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xe5u;
    edx = 0x53u;
    eax = 0x542bf4u;
    ecx = 0x542e00u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xeu;
    edx = 0x12u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 1, 0x41u);
L_4401db:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff84u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440200;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0xb1u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x542e00u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 1, lift_load(&env, ebp, 0xffffff84u, 1) + 1u);
    goto L_4401db;
L_440200:
    lift_store(&env, ebp, 0xffffff80u, 1, 0x30u);
L_440204:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff80u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440229;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0xdcu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff80u, 1, lift_load(&env, ebp, 0xffffff80u, 1) + 1u);
    goto L_440204;
L_440229:
    ebx = 0xcu;
    edx = 0xdu;
    eax = ecx;
    ecx = 0x54300cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff7cu, 1, 0x41u);
L_44024d:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440278;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0xe1u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x54300cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff7cu, 1, lift_load(&env, ebp, 0xffffff7cu, 1) + 1u);
    goto L_44024d;
L_440278:
    lift_store(&env, ebp, 0xffffff78u, 1, 0x30u);
L_44027f:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff78u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4402aa;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x10cu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff78u, 1, lift_load(&env, ebp, 0xffffff78u, 1) + 1u);
    goto L_44027f;
L_4402aa:
    ebx = 0xeu;
    edx = 0x12u;
    eax = ecx;
    ecx = 0x543218u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f7f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff98u, 1, 0x41u);
L_4402cb:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff98u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4402f0;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x111u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x543218u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff98u, 1, lift_load(&env, ebp, 0xffffff98u, 1) + 1u);
    goto L_4402cb;
L_4402f0:
    lift_store(&env, ebp, 0xffffff94u, 1, 0x30u);
L_4402f4:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff94u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440319;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x13cu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff94u, 1, lift_load(&env, ebp, 0xffffff94u, 1) + 1u);
    goto L_4402f4;
L_440319:
    ebx = 0xcu;
    edx = 0xdu;
    eax = ecx;
    ecx = 0x543424u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff90u, 1, 0x41u);
L_44033a:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff90u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_44035f;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x141u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x543424u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff90u, 1, lift_load(&env, ebp, 0xffffff90u, 1) + 1u);
    goto L_44033a;
L_44035f:
    lift_store(&env, ebp, 0xffffff70u, 1, 0x30u);
L_440366:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff70u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440391;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x16cu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff70u, 1, lift_load(&env, ebp, 0xffffff70u, 1) + 1u);
    goto L_440366;
L_440391:
    ebx = 0xeu;
    edx = 0x12u;
    eax = ecx;
    ecx = 0x543630u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f9b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff6cu, 1, 0x41u);
L_4403b5:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff6cu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4403e0;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x171u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x543630u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff6cu, 1, lift_load(&env, ebp, 0xffffff6cu, 1) + 1u);
    goto L_4403b5;
L_4403e0:
    lift_store(&env, ebp, 0xfffffff0u, 1, 0x30u);
L_4403e4:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440409;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x19cu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xfffffff0u, 1, lift_load(&env, ebp, 0xfffffff0u, 1) + 1u);
    goto L_4403e4;
L_440409:
    ebx = 0xcu;
    edx = 0xdu;
    eax = ecx;
    ecx = 0x54383cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43fa90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffecu, 1, 0x41u);
L_44042a:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_44044f;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x1a1u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x54383cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffecu, 1, lift_load(&env, ebp, 0xffffffecu, 1) + 1u);
    goto L_44042a;
L_44044f:
    lift_store(&env, ebp, 0xffffffe8u, 1, 0x30u);
L_440453:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x39u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_44046c;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43fb70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = (ebp + 0xfffffff4u);
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
L_44046c:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x1ccu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 1, lift_load(&env, ebp, 0xffffffe8u, 1) + 1u);
    goto L_440453;
}

uint32_t lifted_f440490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F440490_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F440490_STACK, 1, entry);
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
    esp = esp - 0x10u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 1, (edx & 0xffu));
    edi = ebx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff0u, 2, (ecx & 0xffffu));
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4404d9;
L_4404ad:
    eax = lift_load(&env, ebp, 0x8u, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4404e2;
    eax = lift_load(&env, ebp, 0xfffffff1u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, 0x20cu, &fl);
        eax = r;
    }
    eax = eax + 0x541988u;
    eax = lift_load(&env, eax, 0x0u, 4);
    edi = edi + eax;
L_4404cc:
    edi = edi + 1u;
L_4404cd:
    edx = lift_load(&env, ebp, 0x8u, 4);
    edx = edx + 1u;
    lift_store(&env, ebp, 0x8u, 4, edx);
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4404ad;
L_4404d9:
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
L_4404e2:
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xfffffff1u, 4);
    edx = (edx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f420u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4404cd;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_440561;
L_440506:
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
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, ebp, 0xffffffeeu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edi & 0xffffu);
    eax = esi;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    lift_store(&env, esi, 0x8eu, 1, 0x0u);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = lift_load(&env, esi, 0x158u, 4);
    eax = esi;
    lift_store(&env, esi, 0x8fu, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_440555;
    ebx = lift_load(&env, esi, 0x158u, 4);
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_440555:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) + lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    goto L_4404cc;
L_440561:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_440506;
}

uint32_t lifted_f440d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F440D50_STACK + 4 + 4 * 4 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F440D50_STACK, 4, entry);
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
    esp = esp - 0x40u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    lift_store(&env, ebp, 0xfffffff0u, 1, (edx & 0xffu));
    lift_store(&env, ebp, 0xfffffff4u, 1, (ebx & 0xffu));
    edi = ecx;
    eax = (ebp + 0xffffffb8u);
    edx = 0x4ec1ecu;
    ecx = 0x514f5cu;
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
    eax = lift_load(&env, ebp, 0xcu, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, edx);
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffc4u, 4, ebx);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_440e47;
L_440d96:
    eax = lift_load(&env, ebp, 0xcu, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_440e59;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_440db7;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_440db7:
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
    eax = lift_load(&env, ebp, 0x10u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x44u, 1)) & 0xffu);
    lift_store(&env, esi, 0x44u, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0x10u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x91u, 1)) & 0xffu);
    lift_store(&env, esi, 0x91u, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffedu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, 0x20cu, &fl);
        eax = r;
    }
    eax = eax + 0x541988u;
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esi, 0xf4u, 4, edx);
    ebx = (ebp + 0xffffffd4u);
    eax = lift_load(&env, eax, 0x4u, 4);
    edx = (ebp + 0xffffffd0u);
    lift_store(&env, esi, 0xf8u, 4, eax);
    eax = esi;
    lift_store(&env, ebp, 0xffffffecu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_440e22;
    edi = edi + lift_load(&env, ebp, 0xffffffd0u, 4);
    edi = edi + 1u;
L_440e22:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_440e36;
    ebx = lift_load(&env, eax, 0x158u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_440e36:
    esi = lift_load(&env, ebp, 0xcu, 4);
    esi = esi + 1u;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, esi, 0x0u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xcu, 4, esi);
    {
        (void)lift_and(8, ((edx >> 8) & 0xffu), ((edx >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_440d96;
L_440e47:
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    env.chain = eax;
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
L_440e59:
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffedu, 4);
    edx = (edx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f420u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    ebx = eax;
    eax = lift_load(&env, ebp, 0xcu, 4);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xfffffff1u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f420u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_440e36;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_440e36;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_440eac;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc4u, 4, ecx);
L_440eac:
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
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edi & 0xffffu);
    eax = esi;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = lift_load(&env, ebp, 0x6u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = lift_load(&env, ebp, 0x10u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x8eu, 1)) & 0xffu);
    lift_store(&env, esi, 0x8fu, 1, 0x1u);
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    lift_store(&env, esi, 0x8eu, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, esi, 0x48u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x44u, 1)) & 0xffu);
    lift_store(&env, esi, 0x44u, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0x10u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x91u, 1)) & 0xffu);
    lift_store(&env, esi, 0x91u, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0x10u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xa8u, 2)) & 0xffffu);
    lift_store(&env, esi, 0xa8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0x10u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaau, 2)) & 0xffffu);
    lift_store(&env, esi, 0xaau, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0x10u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xacu, 2)) & 0xffffu);
    lift_store(&env, esi, 0xacu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0x10u, 4);
    ebx = (ebp + 0xffffffd4u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaeu, 2)) & 0xffffu);
    edx = (ebp + 0xffffffd0u);
    lift_store(&env, esi, 0xaeu, 2, (eax & 0xffffu));
    eax = esi;
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_440f91;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = esi;
    ebx = (ebp + 0xffffffdcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac950u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffd8u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_440f91;
    ebx = lift_load(&env, esi, 0x158u, 4);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi + lift_load(&env, ebp, 0xffffffd0u, 4);
    edi = edi + 1u;
L_440f91:
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_440fa8;
    ebx = lift_load(&env, ebx, 0x158u, 4);
    edx = 0x2u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_440fa8:
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffc4u, 4, esi);
    goto L_440e36;
}

uint32_t lifted_f440fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F440FC0_STACK + 4 + 4 * 6 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F440FC0_STACK, 6, entry);
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
    lift_store(&env, ebp, 0xfffffff4u, 1, (ebx & 0xffu));
    eax = (ebp + 0xffffffccu);
    ebx = 0x4ec1ecu;
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
    eax = eax ^ eax;
    esi = 0x514f68u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = (ebp + 0xfffffff0u);
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ecx & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffecu);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe4u);
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe0u);
    ebx = lift_load(&env, ebp, 0x18u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x44u, 1)) & 0xffu);
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)(edx & 0xffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, ebp, 0x14u, 4);
    eax = lift_load(&env, ebp, 0xeu, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xau, 4);
    ebx = lift_load(&env, ebp, 0x6u, 4);
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
    ecx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    eax = lift_load(&env, ebp, 0x1au, 4);
    edx = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffeau, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0x18u, 4);
    ebx = lift_load(&env, ebp, 0xfffffff1u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffeeu, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = esi;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x440d50u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    env.chain = eax;
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

uint32_t lifted_f441600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F441600_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F441600_STACK, 0, entry);
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
    esp = esp - 0x12cu;
    esi = eax;
    eax = (ebp + 0xffffffd4u);
    edx = 0x4ec1ecu;
    ecx = 0x515058u;
    edi = 0x1u;
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
    eax = (ebp + 0xfffffec0u);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    lift_store(&env, esi, 0x268u, 4, ebx);
    lift_store(&env, esi, 0x274u, 4, ebx);
    lift_store(&env, esi, 0x278u, 4, ebx);
    lift_store(&env, esi, 0x270u, 4, ebx);
    eax = (ebp + 0xffffffe8u);
    lift_store(&env, esi, 0x26cu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, 0x2u);
    eax = (ebp + 0xffffffe8u);
    ecx = ecx ^ ecx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489640u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = 0x50e12du;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x50e132u;
    edi = eax;
    ebx = eax;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_44180c;
L_4416ad:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4419fd;
    edx = 0x5b9c60u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x474490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4416c2:
    lift_store(&env, esi, 0x268u, 4, eax);
    edx = lift_load(&env, esi, 0x268u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_441a0e;
    edi = (esi + 0x104u);
    edx = 0x50e137u;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_44170a;
    eax = edi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4816f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    lift_store(&env, esi, 0x274u, 4, eax);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4816f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x278u, 4, eax);
L_44170a:
    eax = lift_load(&env, esi, 0x268u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, esi, 0x208u, 4, eax);
    eax = lift_load(&env, esi, 0x268u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, esi, 0x220u, 1, 0x0u);
    lift_store(&env, esi, 0x222u, 1, 0x0u);
    lift_store(&env, esi, 0x20cu, 4, eax);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x208u, 2)) & 0xffffu);
    eax = eax - ecx;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    lift_store(&env, 0u, 0x544070u, 4, esi);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_441a36;
L_441757:
    lift_store(&env, esi, 0x210u, 2, (eax & 0xffffu));
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x20cu, 2)) & 0xffffu);
    eax = eax - edi;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_441a3d;
L_441779:
    lift_store(&env, esi, 0x214u, 2, 0x0u);
    lift_store(&env, esi, 0x216u, 2, 0x0u);
    lift_store(&env, esi, 0x212u, 2, (eax & 0xffffu));
    ebx = ebx ^ ebx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x208u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4417ab;
    eax = ebx;
L_4417ab:
    lift_store(&env, esi, 0x218u, 2, (eax & 0xffffu));
    edx = edx ^ edx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x20cu, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4417cb;
    eax = edx;
L_4417cb:
    lift_store(&env, esi, 0x21cu, 2, 0x1u);
    lift_store(&env, esi, 0x21eu, 2, 0x1u);
    lift_store(&env, esi, 0x226u, 2, 0x0u);
    lift_store(&env, esi, 0x228u, 1, 0x0u);
L_4417ed:
    lift_store(&env, esi, 0x21au, 2, (eax & 0xffffu));
L_4417f4:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
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
L_44180c:
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4416ad;
    edx = 0x50e138u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4417f4;
    eax = (ebp + 0xfffffec0u);
    ebx = lift_load(&env, 0u, 0x5466c8u, 4);
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_441a44;
    edx = 0x20u;
    eax = 0x1u;
    ecx = 0x20u;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    edx = eax;
    eax = (ebp + 0xfffffec0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, esi, 0x208u, 4, eax);
    eax = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, esi, 0x20cu, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x8u, 1)) & 0xffu);
    lift_store(&env, esi, 0x220u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x9u, 1)) & 0xffu);
    lift_store(&env, esi, 0x221u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0xau, 1)) & 0xffu);
    lift_store(&env, esi, 0x222u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0xbu, 1)) & 0xffu);
    lift_store(&env, esi, 0x223u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0xcu, 1)) & 0xffu);
    lift_store(&env, esi, 0x224u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0xdu, 1)) & 0xffu);
    lift_store(&env, esi, 0x228u, 1, (eax & 0xffu));
    eax = edi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edi, 0x1cu, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x441120u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_441a44;
    edx = 0x5b9c60u;
    eax = (ebp + 0xfffffec0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4741a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, esi, 0x20cu, 4);
    edx = lift_load(&env, esi, 0x208u, 4);
    lift_store(&env, esi, 0x268u, 4, eax);
    eax = (ebp + 0xfffffec0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x274u, 4, eax);
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x220u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_44191d;
    eax = (ebp + 0xfffffec0u);
    ebx = lift_load(&env, esi, 0x20cu, 4);
    edx = lift_load(&env, esi, 0x208u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x270u, 4, eax);
L_44191d:
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x222u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_441943;
    eax = (ebp + 0xfffffec0u);
    ebx = lift_load(&env, esi, 0x20cu, 4);
    edx = lift_load(&env, esi, 0x208u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x26cu, 4, eax);
L_441943:
    eax = (ebp + 0xfffffec0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a8c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x208u, 2)) & 0xffffu);
    eax = eax - edx;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_441a6e;
L_441969:
    lift_store(&env, esi, 0x210u, 2, (eax & 0xffffu));
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x20cu, 2)) & 0xffffu);
    eax = eax - ebx;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_441a75;
L_44198b:
    lift_store(&env, esi, 0x214u, 2, 0x0u);
    lift_store(&env, esi, 0x216u, 2, 0x0u);
    lift_store(&env, esi, 0x212u, 2, (eax & 0xffffu));
    ebx = ebx ^ ebx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x208u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4419bd;
    eax = ebx;
L_4419bd:
    lift_store(&env, esi, 0x218u, 2, (eax & 0xffffu));
    edx = edx ^ edx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x20cu, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4419dd;
    eax = edx;
L_4419dd:
    lift_store(&env, esi, 0x21cu, 2, 0x1u);
    lift_store(&env, esi, 0x21eu, 2, 0x1u);
    lift_store(&env, esi, 0x226u, 2, 0x0u);
    goto L_4417ed;
L_4419fd:
    edx = 0x5b9c60u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48ad00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4416c2;
L_441a0e:
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffec0u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
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
L_441a36:
    eax = eax ^ eax;
    goto L_441757;
L_441a3d:
    eax = eax ^ eax;
    goto L_441779;
L_441a44:
    eax = (ebp + 0xffffffe8u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffec0u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
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
L_441a6e:
    eax = eax ^ eax;
    goto L_441969;
L_441a75:
    eax = eax ^ eax;
    goto L_44198b;
}

uint32_t lifted_f441b70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F441B70_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F441B70_STACK, 0, entry);
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
    esp = esp - 0x128u;
    ecx = eax;
    eax = (ebp + 0xffffffdcu);
    ebx = 0x4ec1ecu;
    esi = 0x51506cu;
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
    edi = edi ^ edi;
    eax = (ebp + 0xfffffec8u);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x1u);
    lift_store(&env, ecx, 0x268u, 4, edi);
    lift_store(&env, ecx, 0x274u, 4, edi);
    lift_store(&env, ecx, 0x278u, 4, edi);
    lift_store(&env, ecx, 0x270u, 4, edi);
    lift_store(&env, ecx, 0x26cu, 4, edi);
    lift_store(&env, ecx, 0x268u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_441d29;
    ebx = (ecx + 0x104u);
    edx = 0x50e13du;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x489d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_441c18;
    eax = ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4816f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    lift_store(&env, ecx, 0x274u, 4, eax);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4816f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x278u, 4, eax);
L_441c18:
    eax = lift_load(&env, ecx, 0x268u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ecx, 0x208u, 4, eax);
    eax = lift_load(&env, ecx, 0x268u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ecx, 0x20cu, 4, eax);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x208u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x544070u, 4, ecx);
    eax = eax - edx;
    lift_store(&env, ecx, 0x220u, 1, 0x0u);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    lift_store(&env, ecx, 0x222u, 1, 0x0u);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_441d46;
L_441c65:
    lift_store(&env, ecx, 0x210u, 2, (eax & 0xffffu));
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x20cu, 2)) & 0xffffu);
    eax = eax - ebx;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_441d4d;
L_441c87:
    lift_store(&env, ecx, 0x214u, 2, 0x0u);
    lift_store(&env, ecx, 0x212u, 2, (eax & 0xffffu));
    edx = edx ^ edx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x208u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    lift_store(&env, ecx, 0x216u, 2, 0x0u);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_441cb9;
    eax = edx;
L_441cb9:
    lift_store(&env, ecx, 0x218u, 2, (eax & 0xffffu));
    ebx = ebx ^ ebx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x20cu, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_441cd9;
    eax = ebx;
L_441cd9:
    lift_store(&env, ecx, 0x21cu, 2, 0x1u);
    lift_store(&env, ecx, 0x21eu, 2, 0x1u);
    lift_store(&env, ecx, 0x226u, 2, 0x0u);
    lift_store(&env, ecx, 0x228u, 1, 0x0u);
    edx = edx ^ edx;
    lift_store(&env, ecx, 0x21au, 2, (eax & 0xffffu));
    ecx = ecx ^ ecx;
    eax = (ebp + 0xfffffec8u);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
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
L_441d29:
    eax = (ebp + 0xfffffec8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
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
L_441d46:
    eax = eax ^ eax;
    goto L_441c65;
L_441d4d:
    eax = eax ^ eax;
    goto L_441c87;
}

uint32_t lifted_f443550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F443550_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F443550_STACK, 0, entry);
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
    ecx = eax;
    edx = 0x1u;
    lift_store(&env, 0u, 0x5448acu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf)
        goto L_443609;
L_44357c:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4435a8;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5448b4u, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x5448b4u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4435a8:
    ebx = 0x54489eu;
    edx = 0x54489cu;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x54489cu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x54489eu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5448a4u, 4, eax);
    eax = lift_load(&env, ecx, 0x2eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ecx, 0x64u, 4);
    lift_store(&env, 0u, 0x5448a0u, 4, eax);
    eax = lift_load(&env, 0u, 0x5448a4u, 4);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_443682;
    lift_store(&env, ecx, 0x44u, 1, 0x10u);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5448acu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_443690;
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
L_443609:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac640u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5448b4u, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac6b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0x30u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_44363d;
    edx = lift_load(&env, 0u, 0x5448b4u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad5e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5448acu, 4, eax);
    goto L_44357c;
L_44363d:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x30u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5448b0u, 2, (eax & 0xffffu));
    edx = 0u - edx;
    eax = ecx;
    lift_store(&env, ecx, 0x32u, 2, (edx & 0xffffu));
    edx = lift_load(&env, 0u, 0x5448b4u, 4);
    lift_store(&env, ecx, 0x30u, 2, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad5e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5448acu, 4, eax);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5448b0u, 2)) & 0xffffu);
    ebx = 0u - ebx;
    lift_store(&env, ecx, 0x30u, 2, (eax & 0xffffu));
    lift_store(&env, ecx, 0x32u, 2, (ebx & 0xffffu));
    goto L_44357c;
L_443682:
    esi = lift_load(&env, 0u, 0x5448a0u, 4);
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_44369e;
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
L_443690:
    eax = ecx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_44369e:
    edx = ebx;
    eax = eax - ebx;
    esi = esi - ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    edx = edx ^ ebx;
    lift_div1(32, esi, &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    lift_store(&env, 0u, 0x5448a8u, 4, edx);
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4436e0;
    eax = edx;
L_4436bf:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4436e7;
L_4436cb:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_443690;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5448acu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_443690;
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
L_4436e0:
    eax = 0x10u;
    goto L_4436bf;
L_4436e7:
    eax = eax ^ eax;
    goto L_4436cb;
}

uint32_t lifted_f444020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F444020_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F444020_STACK, 0, entry);
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
    ecx = eax;
    edx = 0x1u;
    lift_store(&env, 0u, 0x544948u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac1f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf)
        goto L_444118;
L_44405b:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4440a6;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x544950u, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x544950u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x544950u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad110u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x544950u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad6e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x544948u, 4, eax);
L_4440a6:
    ebx = 0x54493au;
    edx = 0x544938u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad440u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x544938u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x54493au, 2)) & 0xffffu);
    ebx = lift_load(&env, ecx, 0x64u, 4);
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_444105;
    eax = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ecx, 0x2eu, 4);
    lift_store(&env, 0u, 0x544940u, 4, eax);
    eax = lift_load(&env, ecx, 0x3eu, 4);
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
    edx = edx + eax;
    esi = lift_load(&env, 0u, 0x544940u, 4);
    lift_store(&env, 0u, 0x54493cu, 4, edx);
    {
        (void)lift_sub(32, esi, 0x28u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_444204;
    lift_store(&env, ecx, 0x44u, 1, 0x10u);
L_444105:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x544948u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_444269;
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
L_444118:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac640u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x544950u, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac6b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x544950u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x12u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x2cu, 2)) & 0xffffu);
    ebx = ebx + eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x1au, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    edi = (edi & 0xffff0000u) | ((lift_load(&env, ecx, 0x2eu, 2)) & 0xffffu);
    edi = edi + eax;
    eax = lift_load(&env, ecx, 0x30u, 4);
    lift_store(&env, ecx, 0x2cu, 2, (ebx & 0xffffu));
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x2eu, 2, (edi & 0xffffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_444187;
    edx = lift_load(&env, 0u, 0x544950u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad5e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_44416b:
    eax = lift_load(&env, ecx, 0x40u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4441c4;
    edx = lift_load(&env, 0u, 0x544950u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad630u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_44405b;
L_444187:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x30u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x54494cu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    eax = 0u - eax;
    edx = lift_load(&env, 0u, 0x544950u, 4);
    lift_store(&env, ecx, 0x32u, 2, (eax & 0xffffu));
    eax = ecx;
    lift_store(&env, ecx, 0x30u, 2, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad5e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x54494cu, 2)) & 0xffffu);
    edx = 0u - edx;
    lift_store(&env, ecx, 0x30u, 2, (eax & 0xffffu));
    lift_store(&env, ecx, 0x32u, 2, (edx & 0xffffu));
    goto L_44416b;
L_4441c4:
    edx = lift_load(&env, 0u, 0x544950u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x40u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x42u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x54494cu, 2, (eax & 0xffffu));
    ebx = 0u - ebx;
    lift_store(&env, ecx, 0x40u, 2, 0x0u);
    eax = ecx;
    lift_store(&env, ecx, 0x42u, 2, (ebx & 0xffffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad630u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, ecx, 0x42u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x54494cu, 2)) & 0xffffu);
    esi = 0u - esi;
    lift_store(&env, ecx, 0x40u, 2, (eax & 0xffffu));
    lift_store(&env, ecx, 0x42u, 2, (esi & 0xffffu));
    goto L_44405b;
L_444204:
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.cf)
        goto L_44421b;
    lift_store(&env, ecx, 0x44u, 1, 0x8u);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x544948u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_444269;
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
L_44421b:
    eax = (esi + 0xffffffd8u);
    ebx = (edx + 0xffffffd8u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    lift_div1(32, ebx, &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    lift_store(&env, 0u, 0x544944u, 4, edx);
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_44425b;
    eax = edx;
L_44423c:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x8u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_444262;
L_444249:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x544948u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_444269;
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
L_44425b:
    eax = 0x10u;
    goto L_44423c;
L_444262:
    eax = 0x8u;
    goto L_444249;
L_444269:
    edx = 0x443ab0u;
    lift_store(&env, ecx, 0x45u, 1, 0x0u);
    eax = ecx;
    lift_store(&env, ecx, 0x46u, 2, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
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
}

uint32_t lifted_f4443d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4443D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4443D0_STACK, 0, entry);
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
    ecx = eax;
    edx = 0x1u;
    lift_store(&env, 0u, 0x544980u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf)
        goto L_44445b;
L_4443f1:
    ebx = 0x544972u;
    edx = 0x544970u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x544970u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x544972u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x544978u, 4, eax);
    eax = lift_load(&env, ecx, 0x2eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x544974u, 4, eax);
    eax = lift_load(&env, ecx, 0x30u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_444449;
    ebx = lift_load(&env, 0u, 0x544978u, 4);
    {
        (void)lift_sub(32, ebx, 0x28u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4444d4;
    lift_store(&env, ecx, 0x44u, 1, 0x10u);
L_444449:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x544980u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_444539;
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
L_44445b:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac640u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x544988u, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac6b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0x30u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_44448f;
    edx = lift_load(&env, 0u, 0x544988u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad5e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x544980u, 4, eax);
    goto L_4443f1;
L_44448f:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x30u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x544984u, 2, (eax & 0xffffu));
    edx = 0u - edx;
    eax = ecx;
    lift_store(&env, ecx, 0x32u, 2, (edx & 0xffffu));
    edx = lift_load(&env, 0u, 0x544988u, 4);
    lift_store(&env, ecx, 0x30u, 2, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad5e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x544980u, 4, eax);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x544984u, 2)) & 0xffffu);
    ebx = 0u - ebx;
    lift_store(&env, ecx, 0x30u, 2, (eax & 0xffffu));
    lift_store(&env, ecx, 0x32u, 2, (ebx & 0xffffu));
    goto L_4443f1;
L_4444d4:
    esi = lift_load(&env, 0u, 0x544974u, 4);
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4444f0;
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x544980u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_444539;
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
L_4444f0:
    eax = (ebx + 0xffffffd8u);
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    ebx = (esi + 0xffffffd8u);
    lift_div1(32, ebx, &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    lift_store(&env, 0u, 0x54497cu, 4, edx);
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_44452e;
    eax = edx;
L_444511:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_444535;
L_44451d:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x544980u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_444539;
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
L_44452e:
    eax = 0x10u;
    goto L_444511;
L_444535:
    eax = eax ^ eax;
    goto L_44451d;
L_444539:
    eax = ecx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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

uint32_t lifted_f444a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F444A80_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F444A80_STACK, 0, entry);
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
    esp = esp - 0x8u;
    ecx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_444aa6;
L_444a9d:
    esp = (ebp + 0xfffffff0u);
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
L_444aa6:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ebx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ebx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad5e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ebp + 0xffffffecu);
    edx = (ebp + 0xffffffe8u);
    esi = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ecx, 0x28u, 4);
    ebx = lift_load(&env, ecx, 0x70u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_div1(32, ebx, &eax, &edx, &fl);
    edx = 0x13u;
    edx = edx - eax;
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_444b45;
L_444b03:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_444b4c;
L_444b0f:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_444a9d;
    edx = 0x3u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x28u, 2)) & 0xffffu);
    edx = edx + edx;
    eax = ecx;
    lift_store(&env, ecx, 0x28u, 2, (edx & 0xffffu));
    edx = 0x444b50u;
    lift_store(&env, ecx, 0x44u, 1, 0x10u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = (ebp + 0xfffffff0u);
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
L_444b45:
    eax = 0x10u;
    goto L_444b03;
L_444b4c:
    eax = eax ^ eax;
    goto L_444b0f;
}

uint32_t lifted_f444e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F444E00_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F444E00_STACK, 0, entry);
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
    esp = esp - 0x24u;
    ecx = eax;
    eax = (ebp + 0xffffffc8u);
    edx = 0x4ec1ecu;
    ebx = 0x515160u;
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
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    esi = 0x1u;
    edi = edi ^ edi;
L_444e3b:
    edx = (ebp + 0xffffffe4u);
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_444e6b;
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
    }
    if (!fl.zf)
        goto L_444fe3;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_444e6b:
    edx = lift_load(&env, ecx, 0x160u, 4);
    eax = (ebp + 0xffffffdcu);
    edx = lift_load(&env, edx, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_444f1e;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x1cu, &fl);
    }
    if (fl.zf)
        goto L_444e9c;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x56u, &fl);
    }
    if (!fl.zf)
        goto L_444f71;
L_444e9c:
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x444c80u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x52u, 1, 0x9u);
    edx = 0x50e16au;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_444ed7;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_444ed7:
    ebx = lift_load(&env, ecx, 0x184u, 4);
    edx = ecx;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_444ef5;
    eax = lift_load(&env, ecx, 0x160u, 4);
    eax = lift_load(&env, eax, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x184u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_444ef5:
    eax = 0x54d640u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4766b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffdcu);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_444f1e:
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x444c80u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    lift_store(&env, ecx, 0x52u, 1, 0x9u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4766b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffdcu);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_444f71:
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x5fu, &fl);
    }
    if (!fl.zf)
        goto L_444f93;
L_444f77:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_444f7e:
    eax = (ebp + 0xffffffdcu);
    edx = edi;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    goto L_444e3b;
L_444f93:
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x60u, &fl);
    }
    if (fl.zf)
        goto L_444fba;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x5cu, &fl);
    }
    if (fl.zf)
        goto L_444fc3;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x61u, &fl);
    }
    if (fl.zf)
        goto L_444fcc;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0xeu, &fl);
    }
    if (fl.zf)
        goto L_444fd5;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x65u, &fl);
    }
    if (!fl.zf)
        goto L_444f7e;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4af0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_444f7e;
L_444fba:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_444f7e;
L_444fc3:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_444f7e;
L_444fcc:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4630u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_444f7e;
L_444fd5:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4950u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_444f7e;
    goto L_444f77;
L_444fe3:
    eax = lift_load(&env, ecx, 0x160u, 4);
    edx = lift_load(&env, eax, 0x15cu, 4);
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3u;
    ebx = esi;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    edx = edx ^ edx;
    eax = (ebp + 0xffffffe0u);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x4u;
    eax = lift_load(&env, 0u, 0x532b3cu, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    ebx = esi;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf)
        goto L_445031;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_445031;
L_445027:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_444e3b;
L_445031:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_44504c;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_44504c;
    edx = edx ^ edx;
    eax = ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4cb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_445027;
L_44504c:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_445066;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x0u, 4), 0x1f5u, &fl);
    }
    if (!fl.zf)
        goto L_445066;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, eax, 0x30u, &fl);
    }
    if (fl.cf)
        goto L_445027;
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_445027;
L_445066:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_445027;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4790u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_445027;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_444e3b;
}

uint32_t lifted_f445350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F445350_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F445350_STACK, 0, entry);
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
    esp = esp - 0x24u;
    ecx = eax;
    eax = (ebp + 0xffffffc8u);
    edx = 0x4ec1ecu;
    ebx = 0x515190u;
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
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    esi = 0x1u;
    edi = edi ^ edi;
L_44538b:
    edx = (ebp + 0xffffffe0u);
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4453bb;
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffe0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_445530;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_4453bb:
    eax = lift_load(&env, ecx, 0x160u, 4);
    edx = lift_load(&env, eax, 0x15cu, 4);
    eax = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_44546b;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x1cu, &fl);
    }
    if (fl.zf)
        goto L_4453ec;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x56u, &fl);
    }
    if (!fl.zf)
        goto L_4454be;
L_4453ec:
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4451d0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ecx;
    esi = lift_load(&env, ecx, 0x184u, 4);
    lift_store(&env, ecx, 0x52u, 1, 0x9u);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_44542d;
    eax = lift_load(&env, ecx, 0x160u, 4);
    eax = lift_load(&env, eax, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x184u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_44542d:
    eax = lift_load(&env, ecx, 0x160u, 4);
    edx = 0x50e16bu;
    eax = eax + 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4766b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe4u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_44546b:
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4451d0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    lift_store(&env, ecx, 0x52u, 1, 0x9u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4766b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe4u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_4454be:
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x5fu, &fl);
    }
    if (!fl.zf)
        goto L_4454e0;
L_4454c4:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4454cb:
    eax = (ebp + 0xffffffe4u);
    edx = edi;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    goto L_44538b;
L_4454e0:
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x60u, &fl);
    }
    if (fl.zf)
        goto L_445507;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x5cu, &fl);
    }
    if (fl.zf)
        goto L_445510;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x61u, &fl);
    }
    if (fl.zf)
        goto L_445519;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0xeu, &fl);
    }
    if (fl.zf)
        goto L_445522;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x65u, &fl);
    }
    if (!fl.zf)
        goto L_4454cb;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4af0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4454cb;
L_445507:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4454cb;
L_445510:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4454cb;
L_445519:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4630u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4454cb;
L_445522:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4950u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4454cb;
    goto L_4454c4;
L_445530:
    edx = lift_load(&env, ecx, 0x160u, 4);
    eax = (ebp + 0xffffffe8u);
    edx = lift_load(&env, edx, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3u;
    ebx = esi;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    edx = edx ^ edx;
    eax = (ebp + 0xffffffdcu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x4u;
    eax = lift_load(&env, 0u, 0x532b3cu, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    ebx = esi;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf)
        goto L_44557e;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe0u, 4), 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_44557e;
L_445574:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_44538b;
L_44557e:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_445599;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe0u, 4), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_445599;
    edx = edx ^ edx;
    eax = ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4cb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_445574;
L_445599:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_445574;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4790u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4455bd;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_44538b;
L_4455bd:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4660u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_445574;
    ebx = lift_load(&env, ecx, 0x184u, 4);
    edx = ecx;
    {
        (void)lift_sub(32, edi, ebx, &fl);
    }
    if (fl.zf)
        goto L_4455e6;
    eax = lift_load(&env, ecx, 0x160u, 4);
    eax = lift_load(&env, eax, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x184u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4455e6:
    eax = lift_load(&env, ecx, 0x160u, 4);
    edx = 0x50e16cu;
    eax = eax + 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4790u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_445574;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_44538b;
}

uint32_t lifted_f445b90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F445B90_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F445B90_STACK, 0, entry);
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
    esp = esp - 0xcu;
    ebx = eax;
    esi = eax;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47e990u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_445bfd;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_445be2;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x4au, 2, 0x0u);
    eax = ebx;
    lift_store(&env, ebx, 0x4cu, 2, 0x5u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_445be2:
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f410u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_445c0c;
L_445bf0:
    lift_store(&env, esi, 0x52u, 1, 0x0u);
L_445bf4:
    esp = (ebp + 0xfffffff0u);
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
L_445bfd:
    eax = ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x52u, 1, 0x0u);
    goto L_445bf4;
L_445c0c:
    {
        uint32_t v = 0x558c9cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x558c9cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47f370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_445bf0;
    lift_store(&env, esi, 0x52u, 1, 0x9u);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x558958u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_445cf3;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x558946u, 2)) & 0xffffu);
L_445c54:
    ecx = lift_load(&env, 0u, 0x558958u, 4);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_445cfd;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x558944u, 2)) & 0xffffu);
L_445c6b:
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b0b70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_445c7f;
    lift_store(&env, esi, 0x48u, 2, 0x23u);
L_445c7f:
    edx = 0x74u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_445bf4;
    eax = (ebp + 0xffffffecu);
    ecx = (ebp + 0xffffffe8u);
    ebx = (ebp + 0xffffffe4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x74u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4764a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = lift_load(&env, ebp, 0xffffffe6u, 4);
    edx = lift_load(&env, ebp, 0xffffffe2u, 4);
    eax = esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b0b70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_445bf4;
    edx = 0x74u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x445d10u;
    eax = esi;
    lift_store(&env, esi, 0x52u, 1, 0xau);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = (ebp + 0xfffffff0u);
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
L_445cf3:
    eax = 0x7d00u;
    goto L_445c54;
L_445cfd:
    eax = 0x7d00u;
    goto L_445c6b;
}

uint32_t lifted_f44a720(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F44A720_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F44A720_STACK, 0, entry);
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
    esp = esp - 0x10u;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edi = 0x1u;
    esi = eax;
    eax = lift_load(&env, 0u, 0x532a68u, 4);
    edx = lift_load(&env, 0u, 0x532a80u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (!fl.zf)
        goto L_44a7d1;
    {
        (void)lift_sub(32, edi, lift_load(&env, eax, 0x5344a4u, 4), &fl);
    }
    if (!fl.zf)
        goto L_44a756;
    edi = edi ^ edi;
L_44a756:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418110u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
L_44a75d:
    if (!fl.zf)
        goto L_44a806;
    edi = edi ^ edi;
L_44a765:
    lift_store(&env, ecx, 0x52u, 1, 0x1u);
    lift_store(&env, ecx, 0x94u, 1, 0x0u);
    lift_store(&env, ecx, 0x95u, 1, 0x0u);
L_44a777:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_44a89b;
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_44a825;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a80u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_44a871;
L_44a79c:
    eax = lift_load(&env, 0u, 0x532a68u, 4);
    {
        (void)lift_sub(32, lift_load(&env, 0u, (eax * 4u) + 0x5344a4u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_44a7b5;
    eax = lift_load(&env, 0u, 0x4f818cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_44a7b5:
    eax = lift_load(&env, 0u, 0x532a6cu, 4);
    {
        (void)lift_sub(32, lift_load(&env, 0u, (eax * 4u) + 0x5344f0u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_44a888;
L_44a7c8:
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
L_44a7d1:
    {
        (void)lift_sub(32, edi, lift_load(&env, 0u, 0x532a7cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_44a7ea;
    eax = lift_load(&env, 0u, 0x532a6cu, 4);
    {
        (void)lift_sub(32, edi, lift_load(&env, 0u, (eax * 4u) + 0x5344f0u, 4), &fl);
    }
    goto L_44a75d;
L_44a7ea:
    {
        (void)lift_sub(32, edi, lift_load(&env, eax, 0x5344a4u, 4), &fl);
    }
    if (!fl.zf)
        goto L_44a7f4;
    edi = edi ^ edi;
L_44a7f4:
    eax = lift_load(&env, 0u, 0x532a6cu, 4);
    {
        (void)lift_sub(32, lift_load(&env, 0u, (eax * 4u) + 0x5344f0u, 4), 0x1u, &fl);
    }
    goto L_44a75d;
L_44a806:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_44a765;
    lift_store(&env, ecx, 0x52u, 1, 0xdu);
    lift_store(&env, ecx, 0x94u, 1, 0x0u);
    lift_store(&env, ecx, 0x95u, 1, 0x1u);
    goto L_44a777;
L_44a825:
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    lift_store(&env, esi, 0x4eu, 1, 0x64u);
    lift_store(&env, esi, 0x94u, 1, 0x0u);
    edx = 0x44abe0u;
    lift_store(&env, esi, 0x95u, 1, 0x3u);
    eax = esi;
    lift_store(&env, esi, 0x44u, 1, 0x10u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f819cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f819cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417290u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x532a9cu, 4, edi);
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
L_44a871:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418110u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_44a79c;
    eax = lift_load(&env, 0u, 0x4f818cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_44a888:
    eax = lift_load(&env, 0u, 0x4f818cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417290u, eax, edx, ebx, ecx, 0, esp);
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
L_44a89b:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_44a90c;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x558958u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_44a9b4;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x558946u, 2)) & 0xffffu);
L_44a8b4:
    ecx = lift_load(&env, 0u, 0x558958u, 4);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_44a9be;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x558944u, 2)) & 0xffffu);
L_44a8cb:
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b66c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_44a9c8;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf)
        goto L_44a9c8;
    eax = 0xau;
    ecx = ecx ^ ecx;
L_44a8ed:
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac980u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_44a90c:
    edx = 0x74u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_44a7c8;
    eax = (ebp + 0xffffffe8u);
    ecx = (ebp + 0xffffffe4u);
    ebx = (ebp + 0xffffffe0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x74u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4764a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = lift_load(&env, ebp, 0xffffffe2u, 4);
    edx = lift_load(&env, ebp, 0xffffffdeu, 4);
    eax = esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b66c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_44a7c8;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (fl.zf)
        goto L_44a9dc;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x532a80u, 4), &fl);
    }
    if (fl.zf)
        goto L_44a9fd;
L_44a96d:
    eax = lift_load(&env, 0u, 0x532a68u, 4);
    {
        (void)lift_sub(32, lift_load(&env, 0u, (eax * 4u) + 0x5344a4u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_44a986;
    eax = lift_load(&env, 0u, 0x4f818cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_44a986:
    eax = lift_load(&env, 0u, 0x532a6cu, 4);
    {
        (void)lift_sub(32, lift_load(&env, 0u, (eax * 4u) + 0x5344f0u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_44a99f;
L_44a995:
    eax = lift_load(&env, 0u, 0x4f818cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417290u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_44a99f:
    edx = 0x44ab00u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
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
L_44a9b4:
    eax = 0x7d00u;
    goto L_44a8b4;
L_44a9be:
    eax = 0x7d00u;
    goto L_44a8cb;
L_44a9c8:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x2u;
    goto L_44a8ed;
L_44a9dc:
    edx = 0x44ab50u;
    eax = esi;
    ecx = edi;
    lift_store(&env, esi, 0x44u, 1, 0x10u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x532a9cu, 4, ecx);
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
L_44a9fd:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418110u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_44a96d;
    eax = lift_load(&env, 0u, 0x4f818cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_44a995;
}

uint32_t lifted_f44bc50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F44BC50_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F44BC50_STACK, 0, entry);
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
    esp = esp - 0x24u;
    esi = eax;
    eax = (ebp + 0xffffffc8u);
    edx = 0x4ec1ecu;
    ecx = 0x515344u;
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
    edi = esi;
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    eax = esi;
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_44bcfb;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x4au, 2, 0x0u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x48u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, esi, 0x4au, 2)) & 0xffffu);
    lift_store(&env, esi, 0x4cu, 2, 0x5u);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_44bcd6;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_44bcd6:
    lift_store(&env, esi, 0x4fu, 1, 0x50u);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x4eu, 1)) & 0xffu);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esi, 0x4fu, 1)) & 0xffu) << 8);
    lift_store(&env, esi, 0x50u, 2, 0x7u);
    {
        (void)lift_sub(8, (eax & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_44bcfb;
    eax = esi;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_44bcfb:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_44bdb0;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x558958u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_44be1c;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x558946u, 2)) & 0xffffu);
L_44bd1d:
    ecx = lift_load(&env, 0u, 0x558958u, 4);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_44be26;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x558944u, 2)) & 0xffffu);
L_44bd34:
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b0b70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_44be30;
    edx = 0x14u;
    lift_store(&env, edi, 0x48u, 2, 0x19u);
    ecx = ecx ^ ecx;
L_44bd53:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.zf)
        goto L_44bd85;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac980u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_44bd85:
    edx = 0x74u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_44be44;
L_44bd9d:
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_44bdb0:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x93u, 1, 0x1u);
    edx = 0x44bf70u;
    lift_store(&env, edi, 0x4eu, 1, 0x50u);
    eax = edi;
    lift_store(&env, edi, 0x44u, 1, 0x10u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f819cu, 4);
    ebx = lift_load(&env, 0u, 0x532b9cu, 4);
    eax = eax ^ eax;
    edx = lift_load(&env, 0u, (edx * 4u) + 0x533164u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482a60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f819cu, 4);
    eax = 0x4u;
    ebx = lift_load(&env, 0u, 0x532b9cu, 4);
    edx = lift_load(&env, 0u, (edx * 4u) + 0x533164u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482a60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_44be1c:
    eax = 0x7d00u;
    goto L_44bd1d;
L_44be26:
    eax = 0x7d00u;
    goto L_44bd34;
L_44be30:
    eax = edi;
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6590u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    goto L_44bd53;
L_44be44:
    eax = (ebp + 0xffffffdcu);
    ecx = (ebp + 0xffffffe8u);
    ebx = (ebp + 0xffffffe0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x74u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4764a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = lift_load(&env, ebp, 0xffffffe6u, 4);
    edx = lift_load(&env, ebp, 0xffffffdeu, 4);
    eax = edi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b0b70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_44bd9d;
    eax = esi;
    edx = 0x44beb0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
    lift_store(&env, edi, 0x44u, 1, 0x10u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
}
