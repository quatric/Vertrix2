/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md) that did NOT pass
 * tools/verify_lifted.py: unverified, used only when explicitly enabled. */
#include "lift_runtime.h"

#include "lifted_unverified.h"

uint32_t lifted_f42a200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F42A200_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F42A200_STACK, 0, entry);
L_429dc3:
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
    return env.failed ? 0u : eax;
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
    edi = eax;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe8u, 1, ((eax >> 8) & 0xffu));
L_42a212:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x1cu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_429dc3;
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
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    edx = ((eax * 4u));
    ecx = ecx - edx;
    edx = ecx;
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x278u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_42a265;
    ecx = 0x4u;
    ecx = ecx - edx;
    ecx = ecx - 1u;
L_42a24e:
    ebx = eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        ebx = r;
    }
    ebx = ebx + edi;
    esi = lift_load(&env, ebx, (edx * 4u) + 0x15cu, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_42a269;
    lift_store(&env, ebp, 0xffffffe8u, 1, lift_load(&env, ebp, 0xffffffe8u, 1) + 1u);
    goto L_42a212;
L_42a265:
    ecx = edx;
    goto L_42a24e;
L_42a269:
    edx = lift_load(&env, 0u, 0x4f9060u, 4);
    edx = edx + lift_load(&env, edi, 0x27cu, 4);
    {
        uint32_t r = lift_imul(32, ecx, edx, &fl);
        ecx = r;
    }
    edx = lift_load(&env, edi, 0xcu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx + ecx;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    ecx = lift_load(&env, edi, 0x280u, 4);
    edx = lift_load(&env, 0u, 0x4f9064u, 4);
    edx = edx + ecx;
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    edx = lift_load(&env, edi, 0x14u, 4);
    ebx = lift_load(&env, 0u, 0x4f9064u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx + eax;
    ecx = lift_load(&env, 0u, 0x4f9060u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    eax = esi;
    ebx = lift_load(&env, ebp, 0xffffffe2u, 4);
    edx = lift_load(&env, ebp, 0xffffffdeu, 4);
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
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ebx = (ebp + 0xffffffdcu);
    edx = (ebp + 0xffffffd8u);
    eax = esi;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_42a2f8;
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = lift_load(&env, 0u, 0x4f9060u, 4);
    eax = eax - edx;
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = ecx + eax;
    eax = lift_load(&env, 0u, 0x4f9064u, 4);
    eax = eax - ebx;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = edx + eax;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
L_42a2f8:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, esi, 0xeu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
    lift_store(&env, ebp, 0xffffffe8u, 1, lift_load(&env, ebp, 0xffffffe8u, 1) + 1u);
    goto L_42a212;
}

uint32_t lifted_object_construct_labeled_box(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_CONSTRUCT_LABELED_BOX_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_CONSTRUCT_LABELED_BOX_STACK, 0,
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
    esp = esp - 0x20u;
    ecx = eax;
    eax = (ebp + 0xffffffccu);
    edx = 0x4ec1ecu;
    ebx = 0x518360u;
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
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    lift_store(&env, ebp, 0xffffffe4u, 1, ((eax >> 8) & 0xffu));
    eax = ecx;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    eax = eax + 0x15cu;
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    ecx = (eax + 0xfffffea4u);
    eax = 0x2u;
    edx = 0x5110b7u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = (ecx + 0x15cu);
    lift_store(&env, ecx, 0x158u, 4, 0x518404u);
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x160u, 1, 0x0u);
    lift_store(&env, ecx, 0x162u, 2, 0x0u);
    lift_store(&env, ecx, 0x164u, 2, 0x0u);
    lift_store(&env, ecx, 0x166u, 2, 0x0u);
    lift_store(&env, ecx, 0x168u, 2, 0x0u);
    lift_store(&env, ecx, 0x16au, 2, 0x0u);
    lift_store(&env, ecx, 0x16cu, 2, 0x0u);
    lift_store(&env, ecx, 0x16eu, 2, 0x0u);
    lift_store(&env, ecx, 0x170u, 2, 0x0u);
    lift_store(&env, ecx, 0x94u, 1, 0x0u);
    lift_store(&env, ecx, 0x95u, 1, 0x3u);
    lift_store(&env, ecx, 0x172u, 2, 0x0u);
    lift_store(&env, ecx, 0x17au, 2, 0xff9cu);
    lift_store(&env, ecx, 0x17cu, 2, 0xff9cu);
    lift_store(&env, ecx, 0x174u, 4, esi);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    env.chain = eax;
    eax = ecx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_object_label_text(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_LABEL_TEXT_STACK + 4 + 4 * 3 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_LABEL_TEXT_STACK, 3, entry);
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
    esp = esp - 0x14u;
    esi = eax;
    lift_store(&env, ebp, 0xfffffff8u, 1, (ebx & 0xffu));
    ebx = ecx;
    ecx = (eax + 0x15cu);
    eax = ecx;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff8u, 1)) & 0xffu);
    lift_store(&env, esi, 0x160u, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, esi, 0x164u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xcu, 4);
    lift_store(&env, esi, 0x166u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, esi, 0x168u, 2, (eax & 0xffffu));
    eax = (ebp + 0xfffffff4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xfffffff0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffecu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe8u);
    lift_store(&env, esi, 0x162u, 2, (ebx & 0xffffu));
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    edx = lift_load(&env, esi, 0x160u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x44u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ecx, 0x0u, 4);
    ebx = lift_load(&env, esi, 0x162u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x166u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, esi, 0x164u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    esp += 28u;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, esi, 0xeu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, esi, 0xf4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, esi, 0xf8u, 4, eax);
    esp = (ebp + 0xfffffffcu);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ccf3b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCF3B_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCF3B_STACK, 0, entry);
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
    esp = esp - 0x24u;
    ecx = eax;
    esi = ebx;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x518f20u);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x14u, 4, 0x1u);
    lift_store(&env, esp, 0x18u, 4, 0x0u);
    lift_store(&env, esp, 0x1cu, 4, ebx);
    lift_store(&env, esp, 0x20u, 4, ecx);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    ebx = lift_load(&env, ebx, 0x4u, 4);
    esi = lift_load(&env, esi, 0x10u, 4);
L_4ccf93:
    {
        (void)lift_sub(32, edx, lift_load(&env, esp, 0x18u, 4), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ccfd1;
    lift_store(&env, esp, 0x14u, 4, 0x0u);
    ecx = lift_load(&env, esp, 0x20u, 4);
    eax = (esp + 0x14u);
    edx = edx ^ edx;
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    eax = lift_call(&env, 0x4ce9fdu, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, esp, 0x0u, 4);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    env.chain = eax;
    eax = ecx;
    esp = esp + 0x24u;
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
    return env.failed ? 0u : eax;
L_4ccfd1:
    eax = ecx;
    eax = lift_call(&env, ebx, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x18u, 4, lift_load(&env, esp, 0x18u, 4) + 1u);
    ecx = ecx + esi;
    goto L_4ccf93;
}
