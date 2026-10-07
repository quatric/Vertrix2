/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md) that did NOT pass
 * tools/verify_lifted.py: unverified, used only when explicitly enabled. */
#include "lift_runtime.h"

#include "lifted_unverified.h"

uint32_t lifted_f418270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F418270_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F418270_STACK, 0, entry);
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
    {
        uint32_t v = 0x540020u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edx = lift_load(&env, 0u, 0x540044u, 4);
    edx = edx + ebx;
    {
        uint32_t v = 0x540020u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x540044u, 4, edx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x4u, 4);
    edx = edx ^ edx;
    eax = lift_load(&env, eax, 0x1cu, 4);
    eax = lift_call(&env, 0x41a040u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f41a040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41A040_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41A040_STACK, 0, entry);
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
    ecx = eax;
    ebx = edx;
    edx = lift_load(&env, 0u, 0x54004cu, 4);
    eax = lift_call(&env, 0x4182c0u, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (!fl.zf)
        goto L_41a061;
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41a061;
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
    return env.failed ? 0u : eax;
L_41a061:
    ebx = lift_load(&env, 0u, 0x540048u, 4);
    eax = ecx;
    lift_store(&env, 0u, 0x54004cu, 4, esi);
    eax = lift_call(&env, 0x41a2b0u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

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

uint32_t lifted_player_mode_in_group_a(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PLAYER_MODE_IN_GROUP_A_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PLAYER_MODE_IN_GROUP_A_STACK, 0,
               entry);
L_43bd74:
    eax = eax ^ eax;
    return env.failed ? 0u : eax;
    eax = lift_load(&env, eax, 0x4c8u, 4);
    {
        (void)lift_sub(32, eax, 0x25u, &fl);
    }
    if (fl.zf)
        goto L_43d3c9;
    {
        (void)lift_sub(32, eax, 0x26u, &fl);
    }
    if (fl.zf)
        goto L_43d3c9;
    {
        (void)lift_sub(32, eax, 0x27u, &fl);
    }
    if (!fl.zf)
        goto L_43bd74;
L_43d3c9:
    eax = 0x1u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_player_mode_in_group_b(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services,
                                       const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PLAYER_MODE_IN_GROUP_B_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PLAYER_MODE_IN_GROUP_B_STACK, 0,
               entry);
L_43bd74:
    eax = eax ^ eax;
    return env.failed ? 0u : eax;
    eax = lift_load(&env, eax, 0x4c8u, 4);
    {
        (void)lift_sub(32, eax, 0x32u, &fl);
    }
    if (fl.zf)
        goto L_43d3e9;
    {
        (void)lift_sub(32, eax, 0x33u, &fl);
    }
    if (fl.zf)
        goto L_43d3e9;
    {
        (void)lift_sub(32, eax, 0x34u, &fl);
    }
    if (!fl.zf)
        goto L_43bd74;
L_43d3e9:
    eax = 0x1u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_font_measure(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_FONT_MEASURE_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_FONT_MEASURE_STACK, 1, entry);
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
    esp = esp - 0x38u;
    lift_store(&env, ebp, 0xfffffff0u, 1, (eax & 0xffu));
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    lift_store(&env, ebp, 0xfffffff4u, 1, (ebx & 0xffu));
    edi = ecx;
    eax = (ebp + 0xffffffc0u);
    edx = 0x4ec1ecu;
    ecx = 0x514f2cu;
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
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
    lift_store(&env, ebp, 0xffffffc8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, edi, 0x0u, 4, ebx);
    edx = 0x50e12cu;
    lift_store(&env, eax, 0x0u, 4, ebx);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_440747;
L_440666:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4407f5;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_44080e;
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_44069f;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
L_44069f:
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
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    lift_store(&env, esi, 0x44u, 1, (eax & 0xffu));
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
    lift_store(&env, esi, 0x8eu, 1, 0x0u);
    lift_store(&env, esi, 0x8fu, 1, 0x1u);
    eax = eax + 0x541988u;
    lift_store(&env, esi, 0x91u, 1, 0x0u);
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esi, 0xf4u, 4, edx);
    ebx = (ebp + 0xffffffd8u);
    eax = lift_load(&env, eax, 0x4u, 4);
    edx = (ebp + 0xffffffd4u);
    lift_store(&env, esi, 0xf8u, 4, eax);
    eax = esi;
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_440723;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    ebx = lift_load(&env, edi, 0x0u, 4);
    ebx = ebx + eax;
    lift_store(&env, edi, 0x0u, 4, ebx);
    esi = (ebx + 0x1u);
    lift_store(&env, edi, 0x0u, 4, esi);
    edx = lift_load(&env, ebp, 0x8u, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x0u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_440723;
    lift_store(&env, edx, 0x0u, 4, eax);
L_440723:
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_44073a;
    ebx = lift_load(&env, ebx, 0x158u, 4);
    edx = 0x2u;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
L_44073a:
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffccu, 4, esi);
L_44073f:
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) + 1u);
    goto L_440666;
L_440747:
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_440807;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
L_440760:
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
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    edx = lift_load(&env, ebp, 0xffffffedu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x44u, 1, (eax & 0xffu));
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        eax = r;
    }
    eax = eax + edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax - edx;
    lift_store(&env, esi, 0x8eu, 1, 0x0u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x8fu, 1, 0x1u);
    eax = eax + 0x541988u;
    lift_store(&env, esi, 0x91u, 1, 0x0u);
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esi, 0xf4u, 4, edx);
    ebx = (ebp + 0xffffffd8u);
    eax = lift_load(&env, eax, 0x4u, 4);
    edx = (ebp + 0xffffffd4u);
    lift_store(&env, esi, 0xf8u, 4, eax);
    eax = esi;
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4407df;
    lift_store(&env, edi, 0x0u, 4, 0x0u);
    edx = lift_load(&env, ebp, 0x8u, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
L_4407df:
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4407f5;
    ebx = lift_load(&env, esi, 0x158u, 4);
    edx = 0x2u;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
L_4407f5:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
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
    return env.failed ? 0u : eax;
L_440807:
    esi = ebx;
    goto L_440760;
L_44080e:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffedu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x43f420u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_44073f;
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_44084a;
    ecx = 0x3u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
L_44084a:
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
        uint32_t v = edx;
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
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    lift_store(&env, esi, 0x8eu, 1, 0x0u);
    ebx = (ebp + 0xffffffd8u);
    lift_store(&env, esi, 0x8fu, 1, 0x1u);
    edx = (ebp + 0xffffffd4u);
    lift_store(&env, esi, 0x44u, 1, (eax & 0xffu));
    eax = esi;
    lift_store(&env, esi, 0x91u, 1, 0x0u);
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4408ab;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    esi = lift_load(&env, edi, 0x0u, 4);
    esi = esi + eax;
    lift_store(&env, edi, 0x0u, 4, esi);
    eax = (esi + 0x1u);
    lift_store(&env, edi, 0x0u, 4, eax);
    edx = lift_load(&env, ebp, 0x8u, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x0u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4408ab;
    lift_store(&env, edx, 0x0u, 4, eax);
L_4408ab:
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_44073a;
    ebx = lift_load(&env, ebx, 0x158u, 4);
    edx = 0x2u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffccu, 4, esi);
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) + 1u);
    goto L_440666;
}

uint32_t lifted_text_layout(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_TEXT_LAYOUT_STACK + 4 + 4 * 4 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_TEXT_LAYOUT_STACK, 4, entry);
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
    edi = edx;
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, esi, 0x0u, 2, 0x0u);
    lift_store(&env, edx, 0x0u, 2, 0x0u);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, esp, 0xcu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4409f0;
L_4409ab:
    eax = lift_load(&env, esp, 0x14u, 4);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, esp, 0x18u, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4409dd;
    eax = lift_load(&env, esp, 0x16u, 4);
    edx = lift_load(&env, esp, 0x12u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = eax - edx;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ecx & 0xffffu);
    eax = eax + 1u;
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
    lift_store(&env, edi, 0x0u, 2, (eax & 0xffffu));
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4409eb;
L_4409dd:
    eax = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, esi, 0x0u, 2, lift_load(&env, esi, 0x0u, 2) + (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x14u, 4);
    lift_store(&env, edi, 0x0u, 2, lift_load(&env, edi, 0x0u, 2) + (eax & 0xffffu));
L_4409eb:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
L_4409f0:
    edx = lift_load(&env, esp, 0xau, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = eax - edx;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    eax = eax + 1u;
    eax = eax - edx;
    eax = eax + 1u;
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
    lift_store(&env, esi, 0x0u, 2, (eax & 0xffffu));
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4409eb;
    goto L_4409ab;
}

uint32_t lifted_object_corner_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_CORNER_CALL_STACK + 4 + 4 * 4 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_CORNER_CALL_STACK, 4, entry);
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
    esp = esp - 0x28u;
    edi = eax;
    eax = (ebp + 0xffffffd0u);
    esi = 0x4ec1ecu;
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
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ecx & 0xffffu);
    eax = 0x514f58u;
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = (ebp + 0xfffffff0u);
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ebx & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xfffffff4u);
    esi = esi ^ esi;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe8u);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe4u);
    esi = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x44u, 1)) & 0xffu);
    esi = lift_load(&env, ebp, 0x10u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xau, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0x6u, 4);
    esi = (uint32_t)(int32_t)(int8_t)(uint8_t)(edx & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = eax;
    eax = esi;
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    esp += 28u;
    eax = lift_load(&env, ebp, 0x14u, 4);
    edx = lift_load(&env, ebp, 0x10u, 4);
    ecx = lift_load(&env, ebp, 0xffffffeeu, 4);
    ebx = lift_load(&env, ebp, 0xfffffff2u, 4);
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
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = edi;
    edx = esi;
    eax = lift_call(&env, 0x440a20u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f45dca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F45DCA0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F45DCA0_STACK, 0, entry);
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
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x104u;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c4eu, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x5449c4u;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c4fu, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x5449e0u;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x53bd09u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x4fc188u;
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x5449fcu;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x5449fcu;
    ebx = lift_load(&env, 0u, 0x5466c4u, 4);
    edx = lift_load(&env, 0u, 0x4fbf28u, 4);
    eax = lift_call(&env, 0x487790u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x5449fcu;
    edx = lift_load(&env, 0u, 0x4fbf28u, 4);
    eax = lift_call(&env, 0x4877d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x5449fcu;
    ebx = lift_load(&env, 0u, 0x4fbf48u, 4);
    edx = lift_load(&env, 0u, 0x4fbf4cu, 4);
    eax = lift_call(&env, 0x487790u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x5449fcu;
    edx = lift_load(&env, 0u, 0x4fbf4cu, 4);
    eax = lift_call(&env, 0x4877d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x5449fcu;
    ebx = lift_load(&env, 0u, 0x4fbf50u, 4);
    edx = lift_load(&env, 0u, 0x4fbf54u, 4);
    eax = lift_call(&env, 0x487790u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x5449fcu;
    edx = lift_load(&env, 0u, 0x4fbf54u, 4);
    eax = lift_call(&env, 0x4877d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x5449fcu;
    ebx = lift_load(&env, 0u, 0x4fbf94u, 4);
    edx = lift_load(&env, 0u, 0x4fbf98u, 4);
    eax = lift_call(&env, 0x487790u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x5449fcu;
    edx = lift_load(&env, 0u, 0x4fbf98u, 4);
    eax = lift_call(&env, 0x4877d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x5449fcu;
    ebx = lift_load(&env, 0u, 0x4fbf84u, 4);
    edx = lift_load(&env, 0u, 0x4fbf88u, 4);
    eax = lift_call(&env, 0x487790u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x5449fcu;
    edx = lift_load(&env, 0u, 0x4fbf88u, 4);
    eax = lift_call(&env, 0x4877d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c4du, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x544a18u;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c51u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x544c10u;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c53u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x4fc188u;
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x544c48u;
    ebx = ebx ^ ebx;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c52u, 1)) & 0xffu);
    eax = 0x1u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    edx = 0x4fc188u;
    ebx = ebx + 0x533650u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = (ebp + 0xfffffef4u);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x544c2cu;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c54u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x544c64u;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c55u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x544d0cu;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c56u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x4fc188u;
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x544c80u;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c57u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x544c9cu;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c58u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x544cb8u;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c59u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x544cd4u;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c5au, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x4fc188u;
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x544cf0u;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    ebx = 0x533650u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c5bu, 1)) & 0xffu);
    edx = 0x4fc188u;
    ebx = lift_load(&env, ebx, (eax * 4u) + 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x546500u;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c5cu, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x54651cu;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c5du, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x546538u;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x45ec00u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    ebx = ebx ^ ebx;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x45e400u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c50u, 1)) & 0xffu);
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x45eac0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x45e3c0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    ebx = ebx + 0x533650u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    edx = 0x4fc188u;
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x546650u;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    ebx = 0x533650u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c5eu, 1)) & 0xffu);
    edx = 0x4fc188u;
    ebx = lift_load(&env, ebx, (eax * 4u) + 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x54666cu;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x513c5fu, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x533650u;
    edx = 0x4fc188u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffef4u);
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xfffffef4u);
    eax = 0x546688u;
    eax = lift_call(&env, 0x4873d0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x45e490u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x45e530u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    eax = lift_call(&env, 0x418270u, eax, edx, ebx, ecx, 0, esp);
    esp = (ebp + 0xfffffff8u);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4726d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4726D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4726D0_STACK, 0, entry);
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
    esp = esp - 0x134u;
    esi = lift_load(&env, 0u, 0x540f8cu, 4);
    eax = lift_load(&env, esi, 0x3b8u, 4);
    ebx = lift_load(&env, 0u, 0x540f90u, 4);
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    eax = lift_load(&env, ebx, 0x3b8u, 4);
    edx = lift_load(&env, esi, 0x178u, 4);
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_472714;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532bc4u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4728ef;
L_472714:
    lift_store(&env, ebp, 0xffffffc8u, 4, 0x3u);
L_47271b:
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_472720:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
L_47272b:
    eax = lift_load(&env, esi, 0x488u, 4);
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
    eax = eax ^ eax;
    edx = edx ^ edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff98u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((ecx & 0xffu)) & 0xffu);
    eax = lift_call(&env, 0x4178d0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4728f7;
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffc8u, 4), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4728f7;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, ebp + 0xfffffeb8u, 4, 0x1u);
L_472762:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = ecx + 1u;
    edi = edi + 1u;
    eax = eax + 0x4u;
    edx = edx + 0x4u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    {
        (void)lift_sub(32, edi, 0x4u, &fl);
    }
    if (fl.cf)
        goto L_47272b;
    edi = lift_load(&env, ebp, 0xffffffc0u, 4);
    edi = edi + 0x10u;
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x70u, &fl);
    }
    if (!fl.zf)
        goto L_472720;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x4c4u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_472908;
L_472797:
    eax = 0x10u;
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
L_4727a1:
    ecx = edi;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        ecx = r;
    }
L_4727a9:
    ecx = ecx + 0x4u;
    edx = edx ^ edx;
    lift_store(&env, ecx, ebp + 0xfffffeb4u, 4, edx);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (!fl.zf)
        goto L_4727a9;
    ecx = lift_load(&env, ebp, 0xffffffacu, 4);
    ecx = ecx + 0x10u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffacu, 4, ecx);
    {
        (void)lift_sub(32, edi, 0x7u, &fl);
    }
    if (fl.cf)
        goto L_4727a1;
L_4727c8:
    edi = lift_load(&env, ebx, 0x178u, 4);
    {
        (void)lift_sub(32, edi, 0x3u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4729cc;
L_4727d7:
    lift_store(&env, ebp, 0xffffffc4u, 4, 0x3u);
L_4727de:
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffbcu, 4, ecx);
L_4727e3:
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
L_4727ee:
    eax = lift_load(&env, ebx, 0x488u, 4);
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
    eax = eax ^ eax;
    edx = edx ^ edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff98u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((ecx & 0xffu)) & 0xffu);
    eax = lift_call(&env, 0x4178d0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4729e1;
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffc4u, 4), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4729e1;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, eax, ebp + 0xffffff28u, 4, 0x1u);
L_472825:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = ecx + 1u;
    edi = edi + 1u;
    eax = eax + 0x4u;
    edx = edx + 0x4u;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    {
        (void)lift_sub(32, edi, 0x4u, &fl);
    }
    if (fl.cf)
        goto L_4727ee;
    edi = lift_load(&env, ebp, 0xffffffbcu, 4);
    edi = edi + 0x10u;
    lift_store(&env, ebp, 0xffffffbcu, 4, edi);
    {
        (void)lift_sub(32, edi, 0x70u, &fl);
    }
    if (!fl.zf)
        goto L_4727e3;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x4c4u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4729f2;
L_47285a:
    eax = 0x10u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
L_472864:
    ecx = edx;
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        ecx = r;
    }
L_47286c:
    ecx = ecx + 0x4u;
    edi = edi ^ edi;
    lift_store(&env, ecx, ebp + 0xffffff24u, 4, edi);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (!fl.zf)
        goto L_47286c;
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = eax + 0x10u;
    edx = edx + 1u;
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    {
        (void)lift_sub(32, edx, 0x7u, &fl);
    }
    if (fl.cf)
        goto L_472864;
L_47288b:
    eax = esi;
    eax = lift_call(&env, 0x43d3b0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_472ab6;
L_47289b:
    esi = 0x10u;
    ebx = ebx ^ ebx;
    edi = edi ^ edi;
L_4728a4:
    ecx = ebx;
    edx = esi;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        ecx = r;
    }
L_4728ab:
    ecx = ecx + 0x4u;
    lift_store(&env, ecx, ebp + 0xffffff24u, 4, edi);
    lift_store(&env, ecx, ebp + 0xfffffeb4u, 4, edi);
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4728ab;
    ebx = ebx + 1u;
    esi = esi + 0x10u;
    {
        (void)lift_sub(32, ebx, 0x7u, &fl);
    }
    if (fl.cf)
        goto L_4728a4;
L_4728c9:
    edx = (ebp + 0xfffffeb8u);
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = lift_call(&env, 0x429df0u, eax, edx, ebx, ecx, 0, esp);
    edx = (ebp + 0xffffff28u);
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    eax = lift_call(&env, 0x429df0u, eax, edx, ebx, ecx, 0, esp);
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
L_4728ef:
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    goto L_47271b;
L_4728f7:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = edx ^ edx;
    lift_store(&env, eax, ebp + 0xfffffeb8u, 4, edx);
    goto L_472762;
L_472908:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x4c5u, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_472797;
    ecx = ecx ^ ecx;
    edi = 0x10u;
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffa8u, 4, edi);
L_472923:
    edi = lift_load(&env, ebp, 0xffffffb4u, 4);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
L_47292f:
    eax = lift_load(&env, esi, 0x488u, 4);
    {
        uint32_t r = lift_imul(32, eax, 0x1cu, &fl);
        eax = r;
    }
    edx = (eax + ecx);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x4f9320u, 1)) & 0xffu);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, edx, 0x4f9538u, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_47297a;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_47297a;
    eax = eax & 0xffu;
    eax = eax - 1u;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x4c4u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4729a0;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x4f9750u, 1)) & 0xffu);
L_47296d:
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_47297a;
    edx = edx ^ edx;
    lift_store(&env, edi, ebp + 0xfffffeb8u, 4, edx);
L_47297a:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    edi = edi + 0x4u;
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf)
        goto L_47292f;
    edx = lift_load(&env, ebp, 0xffffffa8u, 4);
    edi = lift_load(&env, ebp, 0xffffffb4u, 4);
    edx = edx + 0x10u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffa8u, 4, edx);
    lift_store(&env, ebp, 0xffffffb4u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x7u, &fl);
    }
    if (!fl.cf)
        goto L_4727c8;
    goto L_472923;
L_4729a0:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x4c5u, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4729b5;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x4f9788u, 1)) & 0xffu);
    goto L_47296d;
L_4729b5:
    eax = ebx;
    eax = lift_call(&env, 0x43d3d0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47296d;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x4f97c0u, 1)) & 0xffu);
    goto L_47296d;
L_4729cc:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532bc4u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4727d7;
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    goto L_4727de;
L_4729e1:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = edx ^ edx;
    lift_store(&env, eax, ebp + 0xffffff28u, 4, edx);
    goto L_472825;
L_4729f2:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x4c5u, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_47285a;
    ecx = ecx ^ ecx;
    edi = 0x10u;
    lift_store(&env, ebp, 0xffffffb8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffb0u, 4, edi);
L_472a0d:
    edi = lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
L_472a19:
    eax = lift_load(&env, ebx, 0x488u, 4);
    {
        uint32_t r = lift_imul(32, eax, 0x1cu, &fl);
        eax = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x4f9320u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x4f9538u, 1)) & 0xffu);
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_472a64;
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_472a64;
    edx = edx & 0xffu;
    edx = edx - 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x4c4u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_472a8a;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x4f9750u, 1)) & 0xffu);
L_472a57:
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_472a64;
    edx = edx ^ edx;
    lift_store(&env, edi, ebp + 0xffffff28u, 4, edx);
L_472a64:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    edi = edi + 0x4u;
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf)
        goto L_472a19;
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    edi = lift_load(&env, ebp, 0xffffffb8u, 4);
    edx = edx + 0x10u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffb0u, 4, edx);
    lift_store(&env, ebp, 0xffffffb8u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x7u, &fl);
    }
    if (!fl.cf)
        goto L_47288b;
    goto L_472a0d;
L_472a8a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x4c5u, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_472a9f;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x4f9788u, 1)) & 0xffu);
    goto L_472a57;
L_472a9f:
    eax = esi;
    eax = lift_call(&env, 0x43d3d0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_472a57;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x4f97c0u, 1)) & 0xffu);
    goto L_472a57;
L_472ab6:
    eax = ebx;
    eax = lift_call(&env, 0x43d3b0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_47289b;
    goto L_4728c9;
}

uint32_t lifted_f47c520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47C520_STACK + 4 + 4 * 7 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47C520_STACK, 7, entry);
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
    esp = esp - 0x58u;
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edi = ebx;
    esi = ecx;
    edx = lift_load(&env, ebp, 0x10u, 4);
    ebx = lift_load(&env, ebp, 0x14u, 4);
    ecx = lift_load(&env, ebp, 0x18u, 4);
    eax = (ebp + 0xffffffccu);
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
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x4ec1ecu);
    lift_store(&env, ebp, 0xffffffd4u, 4, 0x51684cu);
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x20u, 4), 0xff000000u, &fl);
    }
    if (fl.zf)
        goto L_47c6df;
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, edi);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, ebp, 0xcu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    {
        (void)lift_sub(32, edi, ecx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_47c6df;
    {
        (void)lift_sub(32, edx, lift_load(&env, ebp, 0x8u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_47c6df;
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0x1cu, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_47c6df;
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0xcu, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_47c6df;
    {
        (void)lift_sub(32, esi, ebx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_47c5a8;
    esi = ebx;
L_47c5a8:
    {
        (void)lift_sub(32, edi, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_47c5ae;
    edi = edx;
L_47c5ae:
    eax = lift_load(&env, ebp, 0xcu, 4);
    edx = lift_load(&env, ebp, 0x1cu, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_47c5bb;
    lift_store(&env, ebp, 0xcu, 4, edx);
L_47c5bb:
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0x8u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_47c5c3;
    lift_store(&env, ebp, 0x8u, 4, ecx);
L_47c5c3:
    eax = lift_load(&env, ebp, 0x8u, 4);
    eax = eax - edi;
    eax = eax + 1u;
    lift_store(&env, 0u, 0x558b84u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xcu, 4);
    eax = eax - esi;
    eax = eax + 1u;
    lift_store(&env, 0u, 0x558b86u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x558b82u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_47c6df;
    eax = lift_load(&env, 0u, 0x558b84u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_47c6df;
    eax = (ebp + 0xffffffa0u);
    ecx = 0xffu;
    ebx = 0xff00u;
    edx = 0xff0000u;
    eax = lift_call(&env, 0x481b20u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    {
        uint32_t v = 0xff000000u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = (ebp + 0xffffffa0u);
    eax = lift_call(&env, 0x481bc0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47c6f1;
    ebx = lift_load(&env, ebp, 0x20u, 4);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = (ebp + 0xffffffa0u);
    eax = lift_call(&env, 0x481e10u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ebp, 0x20u, 4, eax);
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (!fl.zf)
        goto L_47c65f;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, 0u, 0x558b82u, 4);
    ebx = edx;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edx = edi;
    eax = lift_call(&env, 0x47c3b0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
L_47c65f:
    eax = lift_load(&env, ebp, 0xcu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xfffffff0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_47c683;
    ebx = lift_load(&env, ebp, 0x20u, 4);
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, 0u, 0x558b82u, 4);
    edx = edi;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    ebx = lift_load(&env, ebp, 0xcu, 4);
    eax = lift_call(&env, 0x47c3b0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
L_47c683:
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffecu, 4), &fl);
    }
    if (!fl.zf)
        goto L_47c6a6;
    edx = lift_load(&env, ebp, 0x20u, 4);
    ecx = 0x1u;
    eax = lift_load(&env, 0u, 0x558b84u, 4);
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
    ebx = esi;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edi;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    eax = lift_call(&env, 0x47c3b0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
L_47c6a6:
    eax = lift_load(&env, ebp, 0x8u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffe0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_47c6cd;
    ebx = lift_load(&env, ebp, 0x20u, 4);
    ecx = 0x1u;
    eax = lift_load(&env, 0u, 0x558b84u, 4);
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
    edx = lift_load(&env, ebp, 0x8u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = esi;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    eax = lift_call(&env, 0x47c3b0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
L_47c6cd:
    eax = (ebp + 0xffffffa0u);
    esi = esi ^ esi;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    eax = lift_call(&env, 0x481b30u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
L_47c6df:
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
    return env.failed ? 0u : eax;
L_47c6f1:
    eax = (ebp + 0xffffffa0u);
    edx = edx ^ edx;
    eax = lift_call(&env, 0x481b30u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f485550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F485550_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F485550_STACK, 0, entry);
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
    esp = esp - 0x10u;
    ebx = eax;
L_48555d:
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x48u, 4), eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_sub(32, eax, 0x8876021cu, &fl);
    }
    if (fl.zf)
        goto L_48555d;
    esi = esi ^ esi;
L_485571:
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x21u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5b99c8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, lift_load(&env, edx, 0x64u, 4), eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    lift_store(&env, 0u, 0x5b99c4u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x887601c2u, &fl);
    }
    if (fl.zf)
        goto L_4855e1;
    esi = esi ^ esi;
L_485591:
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x11u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5b99c8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x6cu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, lift_load(&env, edx, 0x64u, 4), eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    lift_store(&env, 0u, 0x5b99c4u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x887601c2u, &fl);
    }
    if (!fl.zf)
        goto L_4855ff;
    eax = lift_load(&env, ebx, 0x6cu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x6cu, 4), eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4855c7;
    eax = ebx;
    eax = lift_call(&env, 0x487080u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485591;
L_4855c7:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x80u, 4), eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
L_4855d5:
    eax = eax ^ eax;
L_4855d7:
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
L_4855e1:
    eax = lift_load(&env, ebx, 0x64u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x6cu, 4), eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4855d5;
    eax = ebx;
    eax = lift_call(&env, 0x487080u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485571;
    goto L_4855d7;
L_4855ff:
    edx = edx ^ edx;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x3eu, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = eax ^ eax;
    {
        uint32_t v = 0x10u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x40u, 2)) & 0xffffu);
    ecx = (ebp + 0xffffffdcu);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = lift_load(&env, ebx, 0x6cu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, lift_load(&env, edx, 0x1cu, 4), eax, edx, ebx, ecx, 6, esp);
    esp += 24u;
    lift_store(&env, 0u, 0x5b99c4u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_485676;
L_485639:
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x34u, 4), eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_sub(32, eax, 0x8876021cu, &fl);
    }
    if (fl.zf)
        goto L_485639;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x6cu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x80u, 4), eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x80u, 4), eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
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
    return env.failed ? 0u : eax;
L_485676:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1000000u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xffffffdcu);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, ebx, 0x6cu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x68u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, lift_load(&env, ecx, 0x14u, 4), eax, edx, ebx, ecx, 6, esp);
    esp += 24u;
    goto L_485639;
}

uint32_t lifted_f486da0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F486DA0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F486DA0_STACK, 0, entry);
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
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, eax, 0x68u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x80u, 4), eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, 0u, 0x5b9bc8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4873d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4873D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4873D0_STACK, 0, entry);
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
    esp = esp - 0x12cu;
    ecx = eax;
    eax = (ebp + 0xffffffd8u);
    ebx = 0x4ec1ecu;
    esi = 0x516d6cu;
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
    eax = (ebp + 0xfffffec4u);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    eax = lift_call(&env, 0x48a620u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
    ebx = lift_load(&env, 0u, 0x5466c8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (ebp + 0xfffffec4u);
    eax = lift_call(&env, 0x48a710u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4874c2;
    edx = (ebp + 0xffffffecu);
    eax = (ebp + 0xfffffec4u);
    eax = lift_call(&env, 0x482bb0u, eax, edx, ebx, ecx, 0, esp);
    eax = eax ^ eax;
    ebx = ebx ^ ebx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    edx = 0x4u;
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, ecx, 0x4u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_487490;
    edx = edx ^ edx;
L_487460:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, edx, eax + 0x0u, 4, 0x0u);
    eax = (ebp + 0xfffffec4u);
    eax = lift_call(&env, 0x482d00u, eax, edx, ebx, ecx, 0, esp);
    esi = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, edx, esi + 0x0u, 4, eax);
    ebx = ebx + 1u;
    esi = lift_load(&env, ecx, 0x4u, 4);
    edx = edx + 0x4u;
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.cf)
        goto L_487460;
L_487490:
    eax = (ebp + 0xfffffec4u);
    eax = lift_call(&env, 0x48a8c0u, eax, edx, ebx, ecx, 0, esp);
    edi = edi ^ edi;
    edx = edx ^ edx;
    eax = (ebp + 0xfffffec4u);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
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
    return env.failed ? 0u : eax;
L_4874c2:
    eax = (ebp + 0xfffffec4u);
    edx = edx ^ edx;
    eax = lift_call(&env, 0x48a670u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_array_list_build(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ARRAY_LIST_BUILD_STACK + 4 + 4 * 10 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ARRAY_LIST_BUILD_STACK, 10, entry);
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
    edi = eax;
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    lift_store(&env, eax, 0x4u, 4, edx);
    eax = edx;
    edx = 0x4u;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    ecx = lift_load(&env, edi, 0x4u, 4);
    edx = edx ^ edx;
    lift_store(&env, edi, 0x0u, 4, eax);
    lift_store(&env, ebp, 0xfffffff4u, 4, edx);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_487630;
    esi = esi ^ esi;
L_4875cf:
    eax = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, esi, eax + 0x0u, 4, 0x0u);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0x2cu, 1)) & 0xffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0x25u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0x21u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0x20u, 1)) & 0xffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, ebp, 0x1cu, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0x18u, 4);
    edx = lift_load(&env, ebp, 0x14u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0x10u, 4);
    ebx = lift_load(&env, ebp, 0x8u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0xcu, 4);
    esi = esi + 0x4u;
    eax = lift_call(&env, 0x483060u, eax, edx, ebx, ecx, 8, esp);
    esp += 32u;
    edx = lift_load(&env, edi, 0x0u, 4);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, edx, esi + 0xfffffffcu, 4, eax);
    ebx = ebx + 1u;
    edx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.cf)
        goto L_4875cf;
L_487630:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_find_succeeded(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_FIND_SUCCEEDED_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_FIND_SUCCEEDED_STACK, 0, entry);
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
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x118u;
    edx = (ebp + 0xfffffee0u);
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
    eax = lift_call(&env, 0x4d9060u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    esp = (ebp + 0xfffffff8u);
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
        ebp = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4aa660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4AA660_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4AA660_STACK, 0, entry);
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
    esp = esp - 0x4u;
    edx = lift_load(&env, 0u, 0x5bb774u, 4);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    esi = lift_load(&env, 0u, 0x5bb778u, 4);
    ebp = lift_load(&env, 0u, 0x54d5d0u, 4);
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x5bb752u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4aa7c7;
L_4aa690:
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aa7a7;
L_4aa6a0:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    eax = esi;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xe0u) & 0xffu);
    ecx = edx;
    ecx = ecx & 0xffu;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
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
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x3u) & 0xffu);
    edx = edx & 0xffu;
    edx = edx | ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    esi = edx;
    ecx = edx;
    esi = esi & 0xfc0000u;
    ecx = ecx & 0xfc00u;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        esi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    edx = edx & 0xfcu;
    ecx = ecx | esi;
    edx = edx | ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        edx = r;
    }
    ecx = ((edx * 4u));
    edx = lift_load(&env, 0u, 0x54b800u, 4);
    edx = lift_load(&env, ecx, edx + 0x0u, 4);
    lift_store(&env, 0u, 0x54d5d4u, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x54d5d4u, 1)) & 0xffu);
    ecx = ((edx * 4u));
    edx = lift_load(&env, 0u, 0x54cdc8u, 4);
    ebp = lift_load(&env, ecx, edx + 0x0u, 4);
    ecx = lift_load(&env, 0u, 0x54d5d4u, 4);
    edx = lift_load(&env, 0u, 0x54d5d4u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x0u, 4, ecx);
    edi = (edx & 0xffu);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    edx = ebp;
    esi = (ecx & 0xffu);
    edi = lift_load(&env, edx, edi + 0x0u, 1);
    esi = lift_load(&env, edx, esi + 0x0u, 1);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        esi = r;
    }
    esi = esi | edi;
    edi = edi ^ edi;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5d4u, 2)) & 0xffffu);
    ecx = edi;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ecx = r;
    }
    edi = (ecx & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, edi + 0x0u, 1)) & 0xffu);
    edx = edx & 0xffu;
    edx = edx | esi;
    edi = edx;
    esi = edx;
    edi = edi & 0xe00000u;
    esi = esi & 0xe000u;
    {
        uint32_t a = edi;
        uint32_t r = lift_shr(32, a, 0xau, &fl);
        edi = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x5u, &fl);
        esi = r;
    }
    esi = esi | edi;
    edi = edx;
    edi = edi & 0xc0u;
    esi = esi | edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        esi = r;
    }
    lift_store(&env, esp, 0x0u, 4, esi);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    esi = (eax + 0x1u);
    lift_store(&env, eax, 0x0u, 1, (ecx & 0xffu));
    {
        uint32_t a = (ebx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ebx = (ebx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4aa6a0;
L_4aa7a7:
    eax = esi;
    esi = lift_load(&env, 0u, 0x5bb7c8u, 4);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t a = (edi & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb752u, 2, (edi & 0xffffu));
    if (!fl.zf)
        goto L_4aa690;
L_4aa7c7:
    lift_store(&env, 0u, 0x54d5d0u, 4, ebp);
    lift_store(&env, 0u, 0x5bb778u, 4, esi);
    lift_store(&env, 0u, 0x5bc016u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bb774u, 4, edx);
    esp = esp + 0x4u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4aa950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4AA950_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4AA950_STACK, 0, entry);
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
    esp = esp - 0x4u;
    edx = lift_load(&env, 0u, 0x5bb774u, 4);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    esi = lift_load(&env, 0u, 0x5bb778u, 4);
    edi = lift_load(&env, 0u, 0x54d5ecu, 4);
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x5bb752u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4aaa15;
L_4aa97f:
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aa9f7;
L_4aa98b:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xe0u) & 0xffu);
    eax = esi;
    esi = (edx & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        esi = r;
    }
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x1cu) & 0xffu);
    edx = edx & 0xffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        edx = r;
    }
    esi = esi | edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x3u) & 0xffu);
    edx = edx & 0xffu;
    esi = esi | edx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        esi = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        esi = r;
    }
    esi = esi & 0x7f7f7fu;
    edx = (edi + esi);
    ecx = edx;
    esi = edx;
    ecx = ecx & 0xe00000u;
    esi = esi & 0xe000u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0xau, &fl);
        ecx = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x5u, &fl);
        esi = r;
    }
    esi = esi | ecx;
    ecx = edx;
    ecx = ecx & 0xc0u;
    ecx = ecx | esi;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        ecx = r;
    }
    lift_store(&env, esp, 0x0u, 4, ecx);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    esi = (eax + 0x1u);
    lift_store(&env, eax, 0x0u, 1, (ecx & 0xffu));
    {
        uint32_t a = (ebx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ebx = (ebx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4aa98b;
L_4aa9f7:
    eax = esi;
    esi = lift_load(&env, 0u, 0x5bb7c8u, 4);
    {
        uint32_t r = lift_add(32, esi, eax, &fl);
        esi = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    {
        uint32_t a = (eax & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb752u, 2, (eax & 0xffffu));
    if (!fl.zf)
        goto L_4aa97f;
L_4aaa15:
    lift_store(&env, 0u, 0x54d5ecu, 4, edi);
    lift_store(&env, 0u, 0x5bb778u, 4, esi);
    lift_store(&env, 0u, 0x5bc016u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bb774u, 4, edx);
    esp = esp + 0x4u;
    {
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4aabe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4AABE0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4AABE0_STACK, 0, entry);
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
    esp = esp - 0x4u;
    edx = lift_load(&env, 0u, 0x5bb774u, 4);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    esi = lift_load(&env, 0u, 0x5bb778u, 4);
    ebp = lift_load(&env, 0u, 0x54d5d0u, 4);
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x5bb752u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4aad62;
L_4aac10:
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aad42;
L_4aac20:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    eax = esi;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xe0u) & 0xffu);
    ecx = edx;
    ecx = ecx & 0xffu;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
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
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0x3u) & 0xffu);
    edx = edx & 0xffu;
    edx = edx | ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    ecx = lift_load(&env, 0u, 0x54d5ecu, 4);
    edx = edx & 0x7f7f7fu;
    edx = edx + ecx;
    esi = edx;
    ecx = edx;
    esi = esi & 0xfc0000u;
    ecx = ecx & 0xfc00u;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        esi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    edx = edx & 0xfcu;
    ecx = ecx | esi;
    edx = edx | ecx;
    ecx = lift_load(&env, 0u, 0x54b800u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        edx = r;
    }
    edx = lift_load(&env, ecx, (edx * 4u) + 0x0u, 4);
    lift_store(&env, 0u, 0x54d5d4u, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x54d5d4u, 1)) & 0xffu);
    ecx = ((edx * 4u));
    edx = lift_load(&env, 0u, 0x54cdc8u, 4);
    ebp = lift_load(&env, ecx, edx + 0x0u, 4);
    edx = lift_load(&env, 0u, 0x54d5d4u, 4);
    ecx = ecx ^ ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        edx = r;
    }
    ecx = (ecx & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    edx = ebp;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, edx + 0x0u, 1)) & 0xffu);
    edi = ecx;
    ecx = lift_load(&env, 0u, 0x54d5d4u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ecx = r;
    }
    edi = edi & 0xffu;
    lift_store(&env, esp, 0x0u, 4, ecx);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        edi = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    esi = lift_load(&env, ecx, edx + 0x0u, 1);
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5d4u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ecx = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        esi = r;
    }
    lift_store(&env, esp, 0x0u, 4, ecx);
    esi = esi | edi;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, edx + 0x0u, 1)) & 0xffu);
    edx = edx & 0xffu;
    edx = edx | esi;
    edi = edx;
    ecx = edx;
    esi = edx;
    edi = edi & 0xe00000u;
    ecx = ecx & 0xe000u;
    {
        uint32_t a = edi;
        uint32_t r = lift_shr(32, a, 0xau, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x5u, &fl);
        ecx = r;
    }
    esi = esi & 0xc0u;
    ecx = ecx | edi;
    ecx = ecx | esi;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        ecx = r;
    }
    lift_store(&env, esp, 0x0u, 4, ecx);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    esi = (eax + 0x1u);
    lift_store(&env, eax, 0x0u, 1, (ecx & 0xffu));
    {
        uint32_t a = (ebx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ebx = (ebx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4aac20;
L_4aad42:
    eax = esi;
    esi = lift_load(&env, 0u, 0x5bb7c8u, 4);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t a = (edi & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb752u, 2, (edi & 0xffffu));
    if (!fl.zf)
        goto L_4aac10;
L_4aad62:
    lift_store(&env, 0u, 0x54d5d0u, 4, ebp);
    lift_store(&env, 0u, 0x5bb778u, 4, esi);
    lift_store(&env, 0u, 0x5bc016u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bb774u, 4, edx);
    esp = esp + 0x4u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_actor_gate(const VertrixCalls *calls, const VertrixFactoryServices *services,
                           const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_GATE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_GATE_STACK, 0, entry);
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
    esp = esp - 0xcu;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68eu, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = lift_load(&env, eax, 0x13cu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4aec54;
L_4ae40c:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    eax = lift_load(&env, eax, 0xb4u, 4);
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb734u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4af1fc;
    ebx = lift_load(&env, 0u, 0x5bc010u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4aec63;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x27u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb731u, 1, (edx & 0xffu));
    edx = ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebx, 0xcu, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0xdu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb732u, 1, (ebx & 0xffu));
    lift_store(&env, 0u, 0x5bb733u, 1, (edx & 0xffu));
    {
        (void)lift_sub(8, (edx & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4aec63;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0xeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a4u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bb740u, 2, (edx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0x16u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a6u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bb742u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (edx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0x1eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7aeu, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0xcu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b0u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x10u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b2u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b4u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x26u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bbfffu, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x93u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb739u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb790u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, 0u, 0x5bb7b6u, 2, (edx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x94u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x8fu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc00cu, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, 0u, 0x5bc005u, 1, (edx & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x95u, 1)) & 0xffu);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, 0u, 0x5bc00du, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x8eu, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x4eu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bbffeu, 1, (edx & 0xffu));
    lift_store(&env, 0u, 0x5bc00eu, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x64u, &fl);
    }
    if (!fl.zf)
        goto L_4ae552;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) ^ (ebx & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x5bb739u, 1, (ebx & 0xffu));
L_4ae552:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x8cu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb73au, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x80u, 1)) & 0xffu);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, 0u, 0x5bb7b8u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4ae5db;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x208u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb744u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x20cu, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb746u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x214u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    ebx = ebx - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x216u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x226u, 2)) & 0xffffu);
    ecx = ecx - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (ebx & 0xffffu));
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bb7aeu, 2, (edx & 0xffffu));
L_4ae5db:
    ebx = (ebx & 0xffff00ffu) | (((0xdu) & 0xffu) << 8);
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, 0u, 0x5bb730u, 1, ((ebx >> 8) & 0xffu));
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4ae668;
    eax = lift_load(&env, 0u, 0x5bb73eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aec6a;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb740u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb744u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ae619;
    eax = ebx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb740u, 2, (eax & 0xffffu));
L_4ae619:
    eax = lift_load(&env, 0u, 0x5bb740u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aec78;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb742u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb746u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ae644;
    eax = edx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb742u, 2, (eax & 0xffffu));
L_4ae644:
    edx = lift_load(&env, 0u, 0x5bb742u, 4);
    eax = lift_load(&env, 0u, 0x5bb740u, 4);
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
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = lift_load(&env, 0u, 0x5bb73eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb73cu, 4, edx);
L_4ae668:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4aec86;
L_4ae672:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x44u, 1)) & 0xffu);
L_4ae678:
    lift_store(&env, 0u, 0x5bb738u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bb738u, 1), 0x10u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, 0u, 0x5bb694u, 4, eax);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4aecc8;
L_4ae69d:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x52u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x48u, 2)) & 0xffffu);
L_4ae6af:
    lift_store(&env, 0u, 0x5bc002u, 2, (eax & 0xffffu));
L_4ae6b5:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb694u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4aed56;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb74cu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb74eu, 2, (eax & 0xffffu));
L_4ae6da:
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74cu, 2)) & 0xffffu);
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aec63;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    {
        (void)lift_and(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aec63;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b0u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb750u, 2, (ebx & 0xffffu));
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    edx = edx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb752u, 2, (ecx & 0xffffu));
    ebx = ebx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    ecx = ebx;
    lift_store(&env, 0u, 0x5bb7a0u, 2, (edx & 0xffffu));
    ecx = ecx - eax;
    eax = edx;
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) + lift_load(&env, 0u, 0x5bb74cu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ebx & 0xffffu));
    eax = eax - 1u;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb748u, 2, (eax & 0xffffu));
    eax = ecx;
    eax = eax + ebx;
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ecx & 0xffffu));
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bbff4u, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bb74au, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bbffeu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bbff2u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ae80a;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4aee2d;
    ebx = ebx ^ ebx;
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    lift_store(&env, 0u, 0x5bbff6u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bbffau, 2, (ebx & 0xffffu));
L_4ae7a7:
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    edx = edx - 1u;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bbff8u, 2, (edx & 0xffffu));
L_4ae7b8:
    lift_store(&env, 0u, 0x5bbffcu, 2, (eax & 0xffffu));
L_4ae7be:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff8u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4aec63;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aec63;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffcu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4aec63;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffau, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aec63;
L_4ae80a:
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x5bc014u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bbffeu, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ae8f4;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffau, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ae86e;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb694u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ae85a;
    edx = lift_load(&env, 0u, 0x5bbff8u, 4);
    eax = lift_load(&env, 0u, 0x5bb7a0u, 4);
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
    eax = lift_load(&env, 0u, 0x5bb74au, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb790u, 4, lift_load(&env, 0u, 0x5bb790u, 4) + eax);
L_4ae85a:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffau, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, (edx & 0xffu));
L_4ae86e:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ae8b3;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb694u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ae89f;
    edx = lift_load(&env, 0u, 0x5bbff4u, 4);
    eax = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    lift_store(&env, 0u, 0x5bb790u, 4, lift_load(&env, 0u, 0x5bb790u, 4) + edx);
L_4ae89f:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff6u, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, ((edx >> 8) & 0xffu));
L_4ae8b3:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffcu, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ae8d4;
    ebx = (ebx & 0xffffff00u) | ((0x1u) & 0xffu);
    lift_store(&env, 0u, 0x5bb74au, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, (ebx & 0xffu));
L_4ae8d4:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff8u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ae8f4;
    lift_store(&env, 0u, 0x5bb748u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, 0x1u);
L_4ae8f4:
    edx = edx ^ edx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bc014u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb79cu, 4, edx);
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4ae967;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) - lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    eax = eax + 1u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb750u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    eax = eax - edx;
    eax = eax + 1u;
    edx = lift_load(&env, 0u, 0x5bb74au, 4);
    lift_store(&env, 0u, 0x5bb752u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x5bb74eu, 4);
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
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb79cu, 4, edx);
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aec63;
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x5bb752u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4aec63;
L_4ae967:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb694u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4aeab0;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb738u, 1)) & 0xffu);
    edx = 0x5c1c00u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        eax = r;
    }
    edx = edx + eax;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, 0u, 0x5bc014u, 1)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb7d4u, 4, edx);
    lift_store(&env, 0u, 0x5bb7d8u, 4, edx);
    {
        (void)lift_and(8, ((ecx >> 8) & 0xffu), ((ecx >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4aea50;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68au, 2, (eax & 0xffffu));
    if (fl.zf)
        goto L_4aea06;
    ecx = ecx ^ ecx;
    lift_store(&env, 0u, 0x5bb690u, 2, (ecx & 0xffffu));
L_4ae9c0:
    eax = lift_load(&env, 0u, 0x5bb7d4u, 4);
    eax = eax + 1u;
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xffffffffu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb7d4u, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb690u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68au, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb690u, 2, (eax & 0xffffu));
    {
        uint32_t a = (edx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edx = (edx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68au, 2, (edx & 0xffffu));
    if (!fl.zf)
        goto L_4ae9c0;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb790u, 4, lift_load(&env, 0u, 0x5bb790u, 4) + eax);
L_4aea06:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff2u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(16, (eax & 0xffffu), (ecx & 0xffffu), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68au, 2, (eax & 0xffffu));
    if (fl.zf)
        goto L_4aea50;
L_4aea1e:
    eax = lift_load(&env, 0u, 0x5bb7d8u, 4);
    eax = eax + 1u;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xffffffffu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb7d8u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb790u, 4);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68au, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb790u, 4, eax);
    {
        uint32_t a = (edx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edx = (edx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68au, 2, (edx & 0xffffu));
    if (!fl.zf)
        goto L_4aea1e;
L_4aea50:
    eax = lift_load(&env, 0u, 0x5bb7d4u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, 0u, 0x5bb7ccu, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7e0u, 2, (ecx & 0xffffu));
    {
        uint32_t a = (eax & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68au, 2, (eax & 0xffffu));
    if (fl.zf)
        goto L_4aeab0;
L_4aea73:
    eax = lift_load(&env, 0u, 0x5bb7ccu, 4);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7e0u, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68au, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = eax + 1u;
    {
        uint32_t r = lift_add(32, ebx, edx, &fl);
        ebx = r;
    }
    lift_store(&env, 0u, 0x5bb7ccu, 4, eax);
    lift_store(&env, 0u, 0x5bb7e0u, 2, (ebx & 0xffffu));
    {
        uint32_t a = (ecx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68au, 2, (ecx & 0xffffu));
    if (!fl.zf)
        goto L_4aea73;
L_4aeab0:
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, 0u, 0x5bb68eu, 2, (esi & 0xffffu));
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x5bc016u, 2, (edi & 0xffffu));
    lift_store(&env, 0u, 0x5bbff0u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4af21c;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x274u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4af21c;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bc005u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4af21c;
    ebx = lift_load(&env, 0u, 0x5bb74eu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    eax = 0x5bb7ecu;
    ebx = ebx + ebx;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a6u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b2u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    eax = eax - edx;
    eax = eax + ebx;
    eax = eax - 1u;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7aau, 2, (eax & 0xffffu));
    eax = eax - ecx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a8u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, 0u, 0x5bb7aau, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4aeb49;
    lift_store(&env, 0u, 0x5bb7aau, 2, (edx & 0xffffu));
L_4aeb49:
    eax = lift_load(&env, 0u, 0x5bb7a8u, 4);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68eu, 2)) & 0xffffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aee93;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aau, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb746u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aeb82;
    eax = ebx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb7aau, 2, (eax & 0xffffu));
L_4aeb82:
    eax = lift_load(&env, 0u, 0x5bb7a6u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aeea1;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a8u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb746u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aebad;
    eax = edx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb7a8u, 2, (eax & 0xffffu));
L_4aebad:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aau, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) - lift_load(&env, 0u, 0x5bb7a8u, 2)) & 0xffffu);
    eax = eax + 1u;
    lift_store(&env, 0u, 0x5bb7acu, 2, (eax & 0xffffu));
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb68cu, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb68au, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x544070u, 4);
    ecx = lift_load(&env, 0u, 0x5bb79eu, 4);
    edx = lift_load(&env, eax, 0x274u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x214u, 2)) & 0xffffu);
    edx = edx + ecx;
    eax = eax & 0xffffu;
    ecx = (edx + eax);
    edx = lift_load(&env, 0u, 0x5bb742u, 4);
    eax = lift_load(&env, 0u, 0x5bb7a8u, 4);
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
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    ecx = ecx + eax;
    eax = lift_load(&env, 0u, 0x5bb7aau, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb7ccu, 4, ecx);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4aef1f;
    ebx = (ebx & 0xffffff00u) | ((0x3u) & 0xffu);
L_4aec25:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68au, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb750u, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4aef74;
    eax = lift_load(&env, 0u, 0x5bb7ccu, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x0u, 1), (ebx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4aeeaf;
L_4aec45:
    lift_store(&env, 0u, 0x5bb7ccu, 4, lift_load(&env, 0u, 0x5bb7ccu, 4) + 1u);
    lift_store(&env, 0u, 0x5bb68au, 2, lift_load(&env, 0u, 0x5bb68au, 2) + 1u);
    goto L_4aec25;
L_4aec54:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    goto L_4ae40c;
L_4aec63:
    eax = eax ^ eax;
    goto L_4af1fc;
L_4aec6a:
    ecx = ecx ^ ecx;
    lift_store(&env, 0u, 0x5bb740u, 2, (ecx & 0xffffu));
    goto L_4ae619;
L_4aec78:
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x5bb742u, 2, (ebx & 0xffffu));
    goto L_4ae644;
L_4aec86:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x91u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ae672;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x220u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4aecaf;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x221u, 1)) & 0xffu);
    goto L_4ae678;
L_4aecaf:
    eax = lift_load(&env, eax, 0x270u, 4);
    edx = lift_load(&env, 0u, 0x5bb73cu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) + 1u) & 0xffu);
    goto L_4ae678;
L_4aecc8:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x92u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ae69d;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x222u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4aed05;
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x223u, 1)) & 0xffffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x224u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc002u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    goto L_4ae6b5;
L_4aed05:
    eax = lift_load(&env, eax, 0x26cu, 4);
    ebx = lift_load(&env, 0u, 0x5bb73cu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + ebx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc004u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bc004u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bc004u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x7u) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - 0x5u) & 0xffu);
    edx = (edx & 0xffff0000u) | (((uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu)) & 0xffffu);
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    lift_store(&env, 0u, 0x5bc002u, 2, (edx & 0xffffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4aed4e;
    {
        uint32_t r = lift_imul(32, edx, 0x28u, &fl);
        eax = r;
    }
    goto L_4ae6af;
L_4aed4e:
    {
        uint32_t r = lift_imul(32, edx, 0x14u, &fl);
        eax = r;
    }
    goto L_4ae6af;
L_4aed56:
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    eax = eax ^ eax;
    edx = ecx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb738u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x5bb74cu, 2, (edx & 0xffffu));
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = ecx;
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((ecx >> 8) & 0xffu)) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xfu) & 0xffu);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = edx & 0xffffu;
    edx = edx + ebx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x5c1b00u, 1)) & 0xffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74cu, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    ebx = ebx + edx;
    lift_store(&env, 0u, 0x5bb74cu, 2, (ebx & 0xffffu));
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    edx = ebx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb74eu, 2, (eax & 0xffffu));
    eax = ebx;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax & 0xffffu;
    eax = eax + edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x5c1b00u, 1)) & 0xffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x5bb74au, 4);
    lift_store(&env, 0u, 0x5bb74eu, 2, (edx & 0xffffu));
    edx = lift_load(&env, 0u, 0x5bb7aeu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
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
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    edx = lift_load(&env, 0u, 0x5bb74cu, 4);
    lift_store(&env, 0u, 0x5bb7b0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x5bb7b0u, 4);
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
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    lift_store(&env, 0u, 0x5bb7b2u, 2, (eax & 0xffffu));
    goto L_4ae6da;
L_4aee2d:
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4aee4b;
    ecx = ecx ^ ecx;
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    lift_store(&env, 0u, 0x5bbff6u, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bbffau, 2, (ecx & 0xffffu));
    goto L_4ae7a7;
L_4aee4b:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4ae7be;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xa8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaau, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xacu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbffau, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0xaeu, 2)) & 0xffffu);
    goto L_4ae7b8;
L_4aee93:
    ecx = ecx ^ ecx;
    lift_store(&env, 0u, 0x5bb7aau, 2, (ecx & 0xffffu));
    goto L_4aeb82;
L_4aeea1:
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x5bb7a8u, 2, (ebx & 0xffffu));
    goto L_4aebad;
L_4aeeaf:
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7acu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7d0u, 4, eax);
    {
        (void)lift_and(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4aeedf;
L_4aeec0:
    eax = lift_load(&env, 0u, 0x5bb7d0u, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x0u, 1), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4aeedf;
    edx = lift_load(&env, 0u, 0x5bb742u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = eax - edx;
    esi = esi - 1u;
    lift_store(&env, 0u, 0x5bb7d0u, 4, eax);
    {
        (void)lift_and(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4aeec0;
L_4aeedf:
    {
        (void)lift_and(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4aec45;
    edx = 0x1u;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68cu, 2)) & 0xffffu);
    eax = lift_load(&env, 0u, 0x5bb688u, 4);
    ecx = ecx + edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb68cu, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, (eax * 2u) + 0x5bb7ecu, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bb7ccu, 4, lift_load(&env, 0u, 0x5bb7ccu, 4) + 1u);
    lift_store(&env, 0u, 0x5bb68au, 2, lift_load(&env, 0u, 0x5bb68au, 2) + 1u);
    goto L_4aec25;
L_4aef1f:
    ecx = 0x1u;
L_4aef24:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68au, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bb750u, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4aef74;
    eax = lift_load(&env, 0u, 0x5bb7ccu, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x0u, 1), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4aef5b;
L_4aef3d:
    ebx = lift_load(&env, 0u, 0x5bb7ccu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68au, 2)) & 0xffffu);
    ebx = ebx + 1u;
    edx = edx + 1u;
    lift_store(&env, 0u, 0x5bb7ccu, 4, ebx);
    lift_store(&env, 0u, 0x5bb68au, 2, (edx & 0xffffu));
    goto L_4aef24;
L_4aef5b:
    eax = lift_load(&env, 0u, 0x5bb688u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, (eax * 2u) + 0x5bb7ecu, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bb68cu, 2, lift_load(&env, 0u, 0x5bb68cu, 2) + (ecx & 0xffffu));
    goto L_4aef3d;
L_4aef74:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68cu, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb68eu, 2, (esi & 0xffffu));
    lift_store(&env, 0u, 0x5bc016u, 2, (edi & 0xffffu));
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4af213;
L_4aef98:
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff0u, 1, (ecx & 0xffu));
L_4aefae:
    eax = lift_load(&env, 0u, 0x544070u, 4);
    ecx = lift_load(&env, 0u, 0x5bb79eu, 4);
    edx = lift_load(&env, eax, 0x274u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edx = lift_load(&env, edx, 0x0u, 4);
    ecx = ecx + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x214u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x216u, 2)) & 0xffffu);
    ecx = ecx + edx;
    edx = lift_load(&env, 0u, 0x5bb748u, 4);
    eax = eax & 0xffffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x5bb742u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    edx = 0x5bb7ecu;
    ecx = ecx + eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7e4u, 4, ecx);
    lift_store(&env, 0u, 0x5bbfecu, 4, edx);
    lift_store(&env, 0u, 0x5bb68cu, 2, (eax & 0xffffu));
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4af09a;
L_4af01b:
    eax = lift_load(&env, 0u, 0x5bbfecu, 4);
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4af06e;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    edx = lift_load(&env, 0u, 0x5bb7e4u, 4);
    lift_store(&env, eax, 0x0u, 2, 0x0u);
    lift_store(&env, 0u, 0x5bb7e8u, 4, edx);
    {
        (void)lift_and(16, (edi & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4af06e;
L_4af043:
    eax = lift_load(&env, 0u, 0x5bb7e8u, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x0u, 1), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4af06e;
    ecx = lift_load(&env, 0u, 0x5bb742u, 4);
    edx = lift_load(&env, 0u, 0x5bbfecu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(32, eax, ecx, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    lift_store(&env, 0u, 0x5bb7e8u, 4, eax);
    lift_store(&env, edx, 0x0u, 2, (ebx & 0xffffu));
    {
        uint32_t a = (edi & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4af043;
L_4af06e:
    ecx = lift_load(&env, 0u, 0x5bb7e4u, 4);
    ebx = lift_load(&env, 0u, 0x5bbfecu, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68cu, 2)) & 0xffffu);
    ecx = ecx + 1u;
    {
        uint32_t r = lift_add(32, ebx, 0x2u, &fl);
        ebx = r;
    }
    lift_store(&env, 0u, 0x5bb7e4u, 4, ecx);
    lift_store(&env, 0u, 0x5bbfecu, 4, ebx);
    {
        uint32_t a = (eax & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb68cu, 2, (eax & 0xffffu));
    if (!fl.zf)
        goto L_4af01b;
L_4af09a:
    eax = lift_load(&env, 0u, 0x544070u, 4);
    ecx = lift_load(&env, 0u, 0x5bb79eu, 4);
    edx = lift_load(&env, eax, 0x274u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edx = lift_load(&env, edx, 0x0u, 4);
    ecx = ecx + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x214u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x216u, 2)) & 0xffffu);
    ecx = ecx + edx;
    edx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    eax = eax & 0xffffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, 0u, 0x5bb742u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    ecx = ecx + eax;
    lift_store(&env, 0u, 0x5bb7e4u, 4, ecx);
    lift_store(&env, 0u, 0x5bb7e8u, 4, ecx);
L_4af0ee:
    eax = lift_load(&env, 0u, 0x5bb790u, 4);
    edx = lift_load(&env, 0u, 0x5bb734u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = lift_load(&env, edx, 0x0u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    lift_store(&env, 0u, 0x5bb764u, 4, edx);
    lift_store(&env, 0u, 0x5bb76cu, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb798u, 2, (edx & 0xffffu));
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7c0u, 4, edx);
    edx = lift_load(&env, 0u, 0x5bb796u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = lift_load(&env, 0u, 0x5bb796u, 4);
    lift_store(&env, 0u, 0x5bb7bcu, 4, edx);
    edx = lift_load(&env, 0u, 0x5bb74eu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = ecx - edx;
    edx = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, 0u, 0x5bb7c4u, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb732u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edx, ecx, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x5bb794u, 4, ecx);
    ecx = lift_load(&env, eax, 0x18u, 4);
    edx = edx + ecx;
    lift_store(&env, 0u, 0x5bb68eu, 2, (esi & 0xffffu));
    lift_store(&env, 0u, 0x5bb7c8u, 4, edx);
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, 0u, 0x5bb732u, 1)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bc016u, 2, (edi & 0xffffu));
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4af23d;
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, 0u, 0x5bb768u, 4, eax);
    lift_store(&env, 0u, 0x5bb770u, 4, eax);
L_4af1b1:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x13cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4af1e9;
    eax = lift_load(&env, 0u, 0x5bb750u, 4);
    ecx = lift_load(&env, 0u, 0x5bb74eu, 4);
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4af1e9:
    eax = 0x1u;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68eu, 2)) & 0xffffu);
L_4af1fc:
    lift_store(&env, 0u, 0x5bc016u, 2, (edi & 0xffffu));
    lift_store(&env, 0u, 0x5bb68eu, 2, (esi & 0xffffu));
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
    return env.failed ? 0u : eax;
L_4af213:
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4aef98;
L_4af21c:
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bc016u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, 0u, 0x5bbff0u, 1)) & 0xffu) << 8);
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb68eu, 2)) & 0xffffu);
    {
        (void)lift_and(8, ((ecx >> 8) & 0xffu), ((ecx >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4aefae;
    goto L_4af0ee;
L_4af23d:
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4af271;
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4af1b1;
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, 0u, 0x5bb778u, 4, eax);
    lift_store(&env, 0u, 0x5bb77cu, 4, eax);
    goto L_4af1b1;
L_4af271:
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, 0u, 0x5bb780u, 4, eax);
    lift_store(&env, 0u, 0x5bb784u, 4, eax);
    goto L_4af1b1;
}

uint32_t lifted_actor_chain_paint(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_ACTOR_CHAIN_PAINT_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_ACTOR_CHAIN_PAINT_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    lift_store(&env, 0u, 0x5bc010u, 4, edx);
    edx = lift_load(&env, eax, 0x144u, 4);
    eax = lift_call(&env, 0x4ae3e0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4af8da;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
L_4af8da:
    eax = ecx;
    eax = lift_call(&env, 0x4af560u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b17e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B17E0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B17E0_STACK, 0, entry);
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
    esi = eax;
    edi = edx;
    edx = lift_load(&env, eax, 0x13cu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4b1d35;
L_4b17f6:
    eax = lift_load(&env, esi, 0xb4u, 4);
    lift_store(&env, 0u, 0x5bb734u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b1d44;
    ebx = lift_load(&env, 0u, 0x5bc010u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4b1d30;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0xcu, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0xdu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb732u, 1, (edx & 0xffu));
    lift_store(&env, 0u, 0x5bb733u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a4u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb740u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x16u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a6u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb742u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x1eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7aeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xf4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b4u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xf8u, 2)) & 0xffffu);
    ebx = (ebx & 0xffffff00u) | ((0x4u) & 0xffu);
    lift_store(&env, 0u, 0x5bb7b6u, 2, (eax & 0xffffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x8eu, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x5bbffeu, 1, (eax & 0xffu));
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb739u, 1, (edx & 0xffu));
    lift_store(&env, 0u, 0x5bb790u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x94u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb731u, 1, (ebx & 0xffu));
    lift_store(&env, 0u, 0x5bc00cu, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x8cu, 1)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((0x64u) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb73au, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x80u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc00eu, 1, ((edx >> 8) & 0xffu));
    lift_store(&env, 0u, 0x5bb7b8u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4b1941;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x208u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb744u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x20cu, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb746u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x214u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    ebx = ebx - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x216u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x226u, 2)) & 0xffffu);
    ecx = ecx - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (ebx & 0xffffu));
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bb7aeu, 2, (edx & 0xffffu));
L_4b1941:
    lift_store(&env, 0u, 0x5bb730u, 1, 0xdu);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4b19ca;
    eax = lift_load(&env, 0u, 0x5bb73eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1d4b;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb740u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb744u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b197b;
    eax = ebx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb740u, 2, (eax & 0xffffu));
L_4b197b:
    eax = lift_load(&env, 0u, 0x5bb740u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1d59;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb742u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb746u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b19a6;
    eax = edx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb742u, 2, (eax & 0xffffu));
L_4b19a6:
    edx = lift_load(&env, 0u, 0x5bb742u, 4);
    eax = lift_load(&env, 0u, 0x5bb740u, 4);
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
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = lift_load(&env, 0u, 0x5bb73eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb73cu, 4, edx);
L_4b19ca:
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1d67;
L_4b19d3:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x44u, 1)) & 0xffu);
L_4b19d6:
    lift_store(&env, 0u, 0x5bb738u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bb738u, 1), 0x10u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, 0u, 0x5bb70cu, 4, eax);
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1da6;
L_4b19f8:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x52u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x48u, 2)) & 0xffffu);
L_4b1a04:
    lift_store(&env, 0u, 0x5bc002u, 2, (eax & 0xffffu));
L_4b1a0a:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb70cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1e31;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb74cu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb74eu, 2, (eax & 0xffffu));
L_4b1a2f:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74cu, 2)) & 0xffffu);
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb750u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74cu, 2)) & 0xffffu);
    ebx = ebx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    eax = eax + ecx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb748u, 2, (eax & 0xffffu));
    eax = ebx;
    lift_store(&env, 0u, 0x5bb752u, 2, (edx & 0xffffu));
    eax = eax + edx;
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ebx & 0xffffu));
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bbff4u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bb74au, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bbffeu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bbff2u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b1b35;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1eb5;
    ebx = ebx ^ ebx;
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    lift_store(&env, 0u, 0x5bbff6u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bbffau, 2, (ebx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    edx = edx - 1u;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bbff8u, 2, (edx & 0xffffu));
L_4b1ae3:
    lift_store(&env, 0u, 0x5bbffcu, 2, (eax & 0xffffu));
L_4b1ae9:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff8u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b1d44;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1d44;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffcu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b1d44;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffau, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1d44;
L_4b1b35:
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x5bc014u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bbffeu, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b1f27;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffau, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b1b9b;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb70cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1b87;
    eax = lift_load(&env, 0u, 0x5bbff8u, 4);
    edx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = eax - edx;
    edx = eax;
    eax = lift_load(&env, 0u, 0x5bb74au, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb790u, 4, lift_load(&env, 0u, 0x5bb790u, 4) + eax);
L_4b1b87:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffau, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, (edx & 0xffu));
L_4b1b9b:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b1be8;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb70cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1bd4;
    edx = lift_load(&env, 0u, 0x5bbff4u, 4);
    eax = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    ebx = lift_load(&env, 0u, 0x5bb790u, 4);
    edx = edx - eax;
    ebx = ebx + edx;
    lift_store(&env, 0u, 0x5bb790u, 4, ebx);
L_4b1bd4:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff6u, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, ((edx >> 8) & 0xffu));
L_4b1be8:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffcu, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b1c08;
    lift_store(&env, 0u, 0x5bb74au, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, 0x1u);
L_4b1c08:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff8u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b1f27;
    lift_store(&env, 0u, 0x5bb748u, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, 0x1u);
L_4b1c2c:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) - lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    eax = eax + 1u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb750u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    eax = eax - edx;
    eax = eax + 1u;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb752u, 2, (eax & 0xffffu));
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
L_4b1c6f:
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb798u, 2, (edx & 0xffffu));
    edx = lift_load(&env, 0u, 0x5bb796u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = lift_load(&env, 0u, 0x5bb796u, 4);
    lift_store(&env, 0u, 0x5bb7bcu, 4, edx);
    edx = lift_load(&env, 0u, 0x5bb74eu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = ecx - edx;
    edx = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, 0u, 0x5bb7c4u, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb732u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edx, ecx, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x5bb794u, 4, ecx);
    ecx = lift_load(&env, eax, 0x18u, 4);
    edx = edx + ecx;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, 0u, 0x5bb732u, 1)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb7c8u, 4, edx);
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4b1f39;
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, 0u, 0x5bb768u, 4, eax);
    lift_store(&env, 0u, 0x5bb770u, 4, eax);
L_4b1cf7:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x13cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1d2b;
    eax = lift_load(&env, 0u, 0x5bb750u, 4);
    ecx = lift_load(&env, 0u, 0x5bb74eu, 4);
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4b1d2b:
    eax = 0x1u;
L_4b1d30:
    {
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
    return env.failed ? 0u : eax;
L_4b1d35:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    goto L_4b17f6;
L_4b1d44:
    eax = eax ^ eax;
    {
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
    return env.failed ? 0u : eax;
L_4b1d4b:
    ecx = ecx ^ ecx;
    lift_store(&env, 0u, 0x5bb740u, 2, (ecx & 0xffffu));
    goto L_4b197b;
L_4b1d59:
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x5bb742u, 2, (ebx & 0xffffu));
    goto L_4b19a6;
L_4b1d67:
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x91u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b19d3;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x220u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1d8d;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x221u, 1)) & 0xffu);
    goto L_4b19d6;
L_4b1d8d:
    eax = lift_load(&env, eax, 0x270u, 4);
    edx = lift_load(&env, 0u, 0x5bb73cu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) + 1u) & 0xffu);
    goto L_4b19d6;
L_4b1da6:
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x92u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b19f8;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x222u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1de0;
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x223u, 1)) & 0xffffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x224u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc002u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    goto L_4b1a0a;
L_4b1de0:
    eax = lift_load(&env, eax, 0x26cu, 4);
    ecx = lift_load(&env, 0u, 0x5bb73cu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + ecx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc004u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bc004u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bc004u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x7u) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - 0x5u) & 0xffu);
    edx = (edx & 0xffff0000u) | (((uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu)) & 0xffffu);
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    lift_store(&env, 0u, 0x5bc002u, 2, (edx & 0xffffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1e29;
    {
        uint32_t r = lift_imul(32, edx, 0x28u, &fl);
        eax = r;
    }
    goto L_4b1a04;
L_4b1e29:
    {
        uint32_t r = lift_imul(32, edx, 0x14u, &fl);
        eax = r;
    }
    goto L_4b1a04;
L_4b1e31:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    edx = eax;
    eax = eax ^ eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb738u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    ecx = ecx ^ ecx;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) & 0xfu) & 0xffu);
    lift_store(&env, 0u, 0x5bb74cu, 2, (edx & 0xffffu));
    edx = eax;
    ecx = (ecx & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, edx + 0x5c1b00u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb74cu, 2, lift_load(&env, 0u, 0x5bb74cu, 2) + (ebx & 0xffffu));
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, eax, ecx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb74eu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    eax = eax & 0xffffu;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x5c1b00u, 1)) & 0xffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edi = edi + eax;
    lift_store(&env, 0u, 0x5bb74eu, 2, (edi & 0xffffu));
    goto L_4b1a2f;
L_4b1eb5:
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4b1eeb;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    edx = edx - 1u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff8u, 2, (edx & 0xffffu));
    eax = eax - 1u;
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5bbffcu, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bbffau, 2, (edx & 0xffffu));
    goto L_4b1ae9;
L_4b1eeb:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4b1ae9;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xa8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xaau, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xacu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbffau, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xaeu, 2)) & 0xffffu);
    goto L_4b1ae3;
L_4b1f27:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bc014u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1c2c;
    goto L_4b1c6f;
L_4b1f39:
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b1f6d;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1cf7;
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, 0u, 0x5bb778u, 4, eax);
    lift_store(&env, 0u, 0x5bb77cu, 4, eax);
    goto L_4b1cf7;
L_4b1f6d:
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
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
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, 0u, 0x5bb780u, 4, eax);
    lift_store(&env, 0u, 0x5bb784u, 4, eax);
    goto L_4b1cf7;
}

uint32_t lifted_f4b6240(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B6240_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B6240_STACK, 0, entry);
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
    edi = eax;
    ecx = edx;
    eax = lift_load(&env, eax, 0x8u, 4);
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x5bd822u, 2, (eax & 0xffffu));
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b6290;
L_4b6258:
    edx = edx ^ edx;
    eax = lift_load(&env, edi, 0x4u, 4);
    edx = (edx & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    eax = lift_load(&env, eax, (edx * 4u) + 0x0u, 4);
    lift_store(&env, 0u, (edx * 4u) + 0x5bc01cu, 4, eax);
    lift_store(&env, 0u, 0x5bd824u, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x16u, 2)) & 0xffffu);
    ebx = ebx + 1u;
    lift_store(&env, 0u, (edx * 2u) + 0x5bd01cu, 2, (eax & 0xffffu));
    {
        (void)lift_sub(16, (ebx & 0xffffu), lift_load(&env, 0u, 0x5bd822u, 2), &fl);
    }
    if (fl.cf)
        goto L_4b6258;
L_4b6290:
    edi = 0x7d00u;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd822u, 2)) & 0xffffu);
    ebx = ebx ^ ebx;
    {
        (void)lift_and(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b62c5;
L_4b62a3:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    eax = eax + eax;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x5bd01cu, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (edx & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b62b8;
    edi = edx;
L_4b62b8:
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd822u, 2)) & 0xffffu);
    ebx = ebx + 1u;
    {
        (void)lift_sub(16, (ebx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.cf)
        goto L_4b62a3;
L_4b62c5:
    {
        (void)lift_sub(16, (edi & 0xffffu), 0x7d00u, &fl);
    }
    if (fl.zf)
        goto L_4b633b;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd822u, 2)) & 0xffffu);
    ebx = ebx ^ ebx;
    {
        (void)lift_and(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b6290;
L_4b62da:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, (eax * 2u) + 0x5bd01cu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bd81cu, 2, (edi & 0xffffu));
    {
        (void)lift_sub(16, (edx & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4b6322;
    eax = lift_load(&env, 0u, (eax * 4u) + 0x5bc01cu, 4);
    esi = lift_load(&env, eax, 0x158u, 4);
    edx = ecx;
    lift_store(&env, 0u, 0x5bd820u, 2, (ebx & 0xffffu));
    eax = lift_call(&env, lift_load(&env, esi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd820u, 2)) & 0xffffu);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    lift_store(&env, 0u, (eax * 2u) + 0x5bd01cu, 2, 0x7d00u);
L_4b6322:
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd81cu, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd822u, 2)) & 0xffffu);
    ebx = ebx + 1u;
    {
        (void)lift_sub(16, (ebx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.cf)
        goto L_4b62da;
    goto L_4b6290;
L_4b633b:
    lift_store(&env, 0u, 0x5bd81cu, 2, (edi & 0xffffu));
    lift_store(&env, 0u, 0x5bd820u, 2, (ebx & 0xffffu));
    {
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
    return env.failed ? 0u : eax;
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

uint32_t lifted_f4b68a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B68A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B68A0_STACK, 0, entry);
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
    esp = esp - 0x10u;
    esi = eax;
    eax = lift_call(&env, 0x4ae150u, eax, edx, ebx, ecx, 0, esp);
    eax = (ebp + 0xffffffe8u);
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
    eax = (ebp + 0xffffffe4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe0u);
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
    eax = (esi + 0x15cu);
    ecx = lift_load(&env, esi, 0x164u, 4);
    ebx = lift_load(&env, esi, 0x162u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, esi, 0x160u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x166u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
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
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4408e0u, eax, edx, ebx, ecx, 7, esp);
    esp += 28u;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, esi, 0xeu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, esi, 0xf4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, esi, 0xf8u, 4, eax);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca5a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA5A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA5A0_STACK, 0, entry);
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
    ecx = edx;
    edx = ebx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ca5fb;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebx + 0xfffffff4u);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x1u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ca5c1;
    edi = lift_load(&env, eax, 0x4u, 4);
    edi = edi + ecx;
    {
        (void)lift_sub(32, edi, lift_load(&env, eax, 0x8u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ca5db;
L_4ca5c1:
    ebx = lift_load(&env, esi, 0x0u, 4);
    edi = (ebx + 0xfffffff4u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    edx = lift_load(&env, edi, 0x4u, 4);
    eax = lift_call(&env, 0x4ca3f0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4ca150u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
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
    return env.failed ? 0u : eax;
L_4ca5db:
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = eax + ebx;
    ebx = ecx;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0xfffffff8u, 4, lift_load(&env, eax, 0xfffffff8u, 4) + ecx);
    eax = eax - 0xcu;
    edx = lift_load(&env, esi, 0x0u, 4);
    eax = (edx + 0xfffffff4u);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, edx, eax + 0x0u, 1, 0x0u);
L_4ca5fb:
    {
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

uint32_t lifted_f4cdbe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CDBE0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CDBE0_STACK, 0, entry);
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
    esp = esp - 0x10u;
    lift_store(&env, esp, 0x4u, 4, eax);
    lift_store(&env, esp, 0xcu, 4, edx);
    esi = ebx;
    eax = lift_load(&env, ebx, 0x0u, 4);
    edi = edi ^ edi;
    lift_store(&env, esp, 0x0u, 4, eax);
    ebx = edx;
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc16;
    goto L_4cdf71;
L_4cdc04:
    eax = ebx;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cdf71;
L_4cdc16:
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x25u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc29;
    eax = ebx;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x25u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc34;
L_4cdc29:
    eax = ebx;
    eax = lift_call(&env, 0x4e105au, eax, edx, ebx, ecx, 0, esp);
    edi = edi + eax;
    goto L_4cdc04;
L_4cdc34:
    edx = edx ^ edx;
    ebp = ebp ^ ebp;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc4d;
    goto L_4cdc7a;
L_4cdc3f:
    eax = ebx;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cdc7a;
L_4cdc4d:
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x23u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc57;
    edi = edi + 0x2u;
    goto L_4cdc3f;
L_4cdc57:
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x2au, &fl);
    }
    if (!fl.zf)
        goto L_4cdc66;
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    ebp = lift_load(&env, eax, 0xfffffffcu, 4);
    goto L_4cdc3f;
L_4cdc66:
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x2du, &fl);
    }
    if (fl.zf)
        goto L_4cdc3f;
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x2bu, &fl);
    }
    if (fl.zf)
        goto L_4cdc3f;
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x30u, &fl);
    }
    if (fl.zf)
        goto L_4cdc3f;
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4cdc3f;
L_4cdc7a:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4cdca8;
    eax = ebx;
    eax = lift_call(&env, 0x4d6710u, eax, edx, ebx, ecx, 0, esp);
    ebp = eax;
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc9c;
    goto L_4cdca8;
L_4cdc8e:
    eax = ebx;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cdca8;
L_4cdc9c:
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, ebx, 0x0u, 1);
    eax = lift_call(&env, 0x4e1060u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cdc8e;
L_4cdca8:
    lift_store(&env, esp, 0x8u, 4, 0x0u);
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x2eu, &fl);
    }
    if (!fl.zf)
        goto L_4cdd0a;
    eax = ebx;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x2au, &fl);
    }
    if (!fl.zf)
        goto L_4cdce0;
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = ecx;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    goto L_4cdd0a;
L_4cdce0:
    eax = lift_call(&env, 0x4d6710u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cdcfe;
    goto L_4cdd0a;
L_4cdcf0:
    eax = ebx;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cdd0a;
L_4cdcfe:
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, ebx, 0x0u, 1);
    eax = lift_call(&env, 0x4e1060u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cdcf0;
L_4cdd0a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ecx = ecx ^ ecx;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x4eu, &fl);
    }
    if (fl.cf)
        goto L_4cdd5b;
    if (fl.cf || fl.zf)
        goto L_4cdd4d;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x68u, &fl);
    }
    if (fl.cf)
        goto L_4cdd69;
    if (fl.cf || fl.zf)
        goto L_4cdd27;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6cu, &fl);
    }
    if (fl.zf)
        goto L_4cdd3a;
    goto L_4cdd69;
L_4cdd27:
    eax = ebx;
    ecx = 0x10000u;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    goto L_4cdd69;
L_4cdd3a:
    eax = ebx;
    ecx = 0x20000u;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    goto L_4cdd69;
L_4cdd4d:
    eax = ebx;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    goto L_4cdd69;
L_4cdd5b:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x46u, &fl);
    }
    if (fl.cf)
        goto L_4cdd69;
    if (fl.cf || fl.zf)
        goto L_4cdd4d;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x4cu, &fl);
    }
    if (fl.zf)
        goto L_4cdd4d;
L_4cdd69:
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, ebx, 0x0u, 1);
    eax = eax | ecx;
    {
        (void)lift_sub(32, eax, 0x10053u, &fl);
    }
    if (fl.cf)
        goto L_4cde4a;
    if (fl.cf || fl.zf)
        goto L_4cddf0;
    {
        (void)lift_sub(32, eax, 0x20043u, &fl);
    }
    if (fl.cf)
        goto L_4cde34;
    if (fl.cf || fl.zf)
        goto L_4cdda5;
    {
        (void)lift_sub(32, eax, 0x20063u, &fl);
    }
    if (fl.cf)
        goto L_4cde2b;
    if (fl.cf || fl.zf)
        goto L_4cdda5;
    {
        (void)lift_sub(32, eax, 0x20073u, &fl);
    }
    if (fl.zf)
        goto L_4cde10;
    goto L_4cde81;
L_4cdda5:
    edx = 0x2u;
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    goto L_4cde89;
L_4cddb2:
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t v = lift_load(&env, eax, 0xfffffffcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1d24u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cddcb;
    eax = 0x1u;
L_4cddcb:
    edx = eax;
    goto L_4cde81;
L_4cddd2:
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cdde9;
    eax = 0x1u;
L_4cdde9:
    edx = eax;
    goto L_4cde81;
L_4cddf0:
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t v = lift_load(&env, eax, 0xfffffffcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1d24u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cde09;
    eax = 0x1u;
L_4cde09:
    edx = eax;
    goto L_4cde81;
L_4cde10:
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cde27;
    eax = 0x1u;
L_4cde27:
    edx = eax;
    goto L_4cde81;
L_4cde2b:
    {
        (void)lift_sub(32, eax, 0x20053u, &fl);
    }
    if (fl.zf)
        goto L_4cde10;
    goto L_4cde81;
L_4cde34:
    {
        (void)lift_sub(32, eax, 0x10063u, &fl);
    }
    if (fl.cf)
        goto L_4cde81;
    if (fl.cf || fl.zf)
        goto L_4cdda5;
    {
        (void)lift_sub(32, eax, 0x10073u, &fl);
    }
    if (fl.zf)
        goto L_4cddf0;
    goto L_4cde81;
L_4cde4a:
    {
        (void)lift_sub(32, eax, 0x63u, &fl);
    }
    if (fl.cf)
        goto L_4cde6d;
    if (fl.cf || fl.zf)
        goto L_4cdda5;
    {
        (void)lift_sub(32, eax, 0x73u, &fl);
    }
    if (fl.cf)
        goto L_4cde81;
    if (fl.cf || fl.zf)
        goto L_4cddb2;
    {
        (void)lift_sub(32, eax, 0x10043u, &fl);
    }
    if (fl.zf)
        goto L_4cdda5;
    goto L_4cde81;
L_4cde6d:
    {
        (void)lift_sub(32, eax, 0x43u, &fl);
    }
    if (fl.cf)
        goto L_4cde81;
    if (fl.cf || fl.zf)
        goto L_4cdda5;
    {
        (void)lift_sub(32, eax, 0x53u, &fl);
    }
    if (fl.zf)
        goto L_4cddd2;
L_4cde81:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4cdf03;
L_4cde89:
    {
        (void)lift_sub(32, edx, ebp, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4cde8f;
    ebp = edx;
L_4cde8f:
    edx = ebp;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cdf6a;
    {
        (void)lift_sub(32, ebp, lift_load(&env, esp, 0x8u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4cdf6a;
    edx = lift_load(&env, esp, 0x8u, 4);
    edi = edi + edx;
    goto L_4cdc04;
L_4cdeb1:
    ebp = ebp + lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    {
        (void)lift_sub(32, ebp, 0x20u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cdec9;
    edx = 0x20u;
    edi = edi + edx;
    goto L_4cdc04;
L_4cdec9:
    edx = ebp;
    edi = edi + edx;
    goto L_4cdc04;
L_4cded2:
    edx = ebp;
    edi = edi + edx;
    goto L_4cdc04;
L_4cdedb:
    edx = lift_load(&env, esp, 0x8u, 4);
    edx = edx + ebp;
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    {
        (void)lift_sub(32, edx, 0x20u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cdf6a;
    edx = 0x20u;
    edi = edi + edx;
    goto L_4cdc04;
L_4cdef9:
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x4u);
    edi = edi + edx;
    goto L_4cdc04;
L_4cdf03:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x67u, &fl);
    }
    if (fl.cf)
        goto L_4cdf37;
    if (fl.cf || fl.zf)
        goto L_4cdf41;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6fu, &fl);
    }
    if (fl.cf)
        goto L_4cdf26;
    if (fl.cf || fl.zf)
        goto L_4cdeb1;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x75u, &fl);
    }
    if (fl.cf)
        goto L_4cdf1b;
    if (fl.cf || fl.zf)
        goto L_4cdeb1;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x78u, &fl);
    }
    goto L_4cdf64;
L_4cdf1b:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x70u, &fl);
    }
    if (fl.zf)
        goto L_4cdedb;
    edi = edi + edx;
    goto L_4cdc04;
L_4cdf26:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x69u, &fl);
    }
    if (fl.cf)
        goto L_4cdf6a;
    if (fl.cf || fl.zf)
        goto L_4cdeb1;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6eu, &fl);
    }
    if (fl.zf)
        goto L_4cdef9;
    edi = edi + edx;
    goto L_4cdc04;
L_4cdf37:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x64u, &fl);
    }
    if (fl.cf)
        goto L_4cdf5c;
    if (fl.cf || fl.zf)
        goto L_4cdeb1;
L_4cdf41:
    ebp = ebp + lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, esi, 0x0u, 4, lift_load(&env, esi, 0x0u, 4) + 0x8u);
    {
        (void)lift_sub(32, ebp, 0x80u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cded2;
    edx = 0x80u;
    edi = edi + edx;
    goto L_4cdc04;
L_4cdf5c:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x47u, &fl);
    }
    if (fl.cf)
        goto L_4cdf6a;
    if (fl.cf || fl.zf)
        goto L_4cdf41;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x58u, &fl);
    }
L_4cdf64:
    if (fl.zf)
        goto L_4cdeb1;
L_4cdf6a:
    edi = edi + edx;
    goto L_4cdc04;
L_4cdf71:
    eax = lift_load(&env, esp, 0x4u, 4);
    edx = edi;
    eax = lift_call(&env, 0x4ca670u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, esp, 0x4u, 4);
    ebx = esp;
    edx = lift_load(&env, esp, 0xcu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, 0x4cd0a4u, eax, edx, ebx, ecx, 0, esp);
    edx = 0xffffffffu;
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = lift_call(&env, 0x4ca6c0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x0u, 4, 0x0u);
    esp = esp + 0x10u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cdfb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CDFB0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CDFB0_STACK, 0, entry);
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
    ebx = (esp + 0x18u);
    edx = lift_load(&env, esp, 0x14u, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, esp, 0x0u, 4, ebx);
    ebx = esp;
    eax = lift_call(&env, 0x4cdbe0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x0u, 4, 0x0u);
    esp = esp + 0x4u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ce740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CE740_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CE740_STACK, 0, entry);
L_4ce730:
    edx = 0x4ce810u;
    eax = 0x5c5c64u;
    goto L_4dc030;
    edx = 0x4ce7c0u;
    eax = 0x5c5c60u;
    eax = lift_call(&env, 0x4dbf80u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ce730;
    eax = lift_load(&env, eax, 0x4u, 4);
    return env.failed ? 0u : eax;
L_4dc030:
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
    esp = esp - 0x54u;
    ebx = eax;
    lift_store(&env, esp, 0x44u, 4, edx);
    eax = (esp + 0x34u);
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
    lift_store(&env, esp, 0x38u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x3cu, 4, 0x51abacu);
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c77e8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc0c6;
    eax = lift_call(&env, 0x4f1c00u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_and(32, eax, 0x80000000u, &fl);
    }
    if (fl.zf)
        goto L_4dc092;
    eax = (edx & 0xffu);
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4dc092;
    edx = 0x1u;
    goto L_4dc094;
L_4dc092:
    edx = edx ^ edx;
L_4dc094:
    eax = 0x5c77b0u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dc0a2;
    eax = lift_call(&env, 0x4dbac0u, eax, edx, ebx, ecx, 0, esp);
L_4dc0a2:
    lift_store(&env, 0u, 0x5c77e8u, 4, eax);
    goto L_4dc0c6;
L_4dc0a9:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esp, 0x44u, 4, 0x3u);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = lift_call(&env, 0x4da66eu, eax, edx, ebx, ecx, 0, esp);
L_4dc0c6:
    eax = esp;
    lift_store(&env, esp, 0x40u, 4, 0x1u);
    eax = lift_call(&env, 0x4d9f06u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dc0a9;
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc0fb;
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = lift_call(&env, 0x4dbb30u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebx, 0x0u, 4, eax);
L_4dc0fb:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = lift_call(&env, 0x4dbcd0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x4cu, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc12c;
    eax = lift_call(&env, lift_load(&env, esp, 0x44u, 4), eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x4cu, 4, eax);
    ecx = lift_load(&env, esp, 0x4cu, 4);
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    edx = lift_load(&env, ebx, 0x0u, 4);
    ebx = ecx;
    eax = lift_call(&env, 0x4dbd20u, eax, edx, ebx, ecx, 0, esp);
L_4dc12c:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x4cu, 4);
    lift_store(&env, esp, 0x48u, 4, eax);
    eax = lift_load(&env, esp, 0x34u, 4);
    env.chain = eax;
    eax = lift_load(&env, esp, 0x48u, 4);
    esp = esp + 0x54u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d7c40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D7C40_STACK + 4 + 4 * 2 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D7C40_STACK, 2, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
    esp = esp - 0x164u;
    eax = (ebp + 0xffffffdcu);
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
    eax = (ebp + 0xfffffff0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x104u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffe0u, 4, 0x4ec1ecu);
    lift_store(&env, ebp, 0xffffffe4u, 4, 0x519d30u);
    {
        uint32_t v = lift_load(&env, ebp, 0xcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    eax = lift_call(&env, 0x4f1bb8u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d7ca3;
    {
        uint32_t v = 0x104u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0xcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1d20u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    ecx = ecx ^ ecx;
    goto L_4d7d54;
L_4d7ca3:
    eax = (ebp + 0xfffffff4u);
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    eax = (ebp + 0xfffffff4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x1u);
    eax = lift_call(&env, 0x4d7d70u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
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
    eax = (ebp + 0xfffffff8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xfffffffcu);
    {
        uint32_t v = eax;
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
    {
        uint32_t v = lift_load(&env, ebp, 0xfffffff4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c04u, eax, edx, ebx, ecx, 8, esp);
    esp += 32u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d7cf9;
    eax = (ebp + 0xfffffff4u);
    edx = edx ^ edx;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    ecx = ecx ^ ecx;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
    eax = ecx;
    esp = ebp;
    ebp = lift_load(&env, esp, 0u, 4);
    esp += 4u;
    return env.failed ? 0u : eax;
L_4d7cf9:
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xfffffff8u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4d7d09;
    {
        uint32_t v = lift_load(&env, ebp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1904u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4d7d09:
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xfffffff8u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4d7d3e;
    eax = (ebp + 0xfffffe9cu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0xcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b60u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4d7d3e;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b5cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = (ebp + 0xfffffec8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0xfffffff0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1d1cu, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
L_4d7d3e:
    ecx = 0x1u;
    eax = (ebp + 0xfffffff4u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
L_4d7d54:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    env.chain = eax;
    eax = ecx;
    esp = ebp;
    ebp = lift_load(&env, esp, 0u, 4);
    esp += 4u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d9060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D9060_STACK + 4 + 4 * 2 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D9060_STACK, 2, entry);
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
    esp = esp - 0x14cu;
    esi = lift_load(&env, esp, 0x15cu, 4);
    {
        uint32_t v = lift_load(&env, esp, 0x158u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esi + 0x12u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d7c40u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d908c;
    lift_store(&env, esi, 0x12u, 1, 0x0u);
    goto L_4d9136;
L_4d908c:
    eax = esp;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x15cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b60u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4d90af;
    eax = eax ^ eax;
    esp = esp + 0x14cu;
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
    return env.failed ? 0u : eax;
L_4d90af:
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b5cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x7fu) & 0xffu);
    lift_store(&env, esi, 0x10u, 1, (eax & 0xffu));
    ebx = 0xffffffffu;
    eax = lift_load(&env, esp, 0x20u, 4);
    edx = (esp + 0x4u);
    lift_store(&env, esi, 0xcu, 4, eax);
    eax = (esp + 0x140u);
    eax = lift_call(&env, 0x4e3470u, eax, edx, ebx, ecx, 0, esp);
    ebx = 0xffffffffu;
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = (esp + 0xcu);
    lift_store(&env, esi, 0x0u, 4, eax);
    eax = (esp + 0x144u);
    eax = lift_call(&env, 0x4e3470u, eax, edx, ebx, ecx, 0, esp);
    edx = (esi + 0x8u);
    eax = lift_load(&env, eax, 0x0u, 4);
    ebx = 0xffffffffu;
    lift_store(&env, edx, 0x0u, 4, eax);
    edx = (esp + 0x14u);
    eax = (esp + 0x148u);
    eax = lift_call(&env, 0x4e3470u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    eax = (esi + 0x4u);
    edx = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
    edx = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4d9123;
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esi, 0x0u, 4, eax);
L_4d9123:
    eax = (esi + 0x8u);
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4d9131;
    edx = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
L_4d9131:
    eax = 0x1u;
L_4d9136:
    esp = esp + 0x14cu;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_rtl_static_init_call(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_STATIC_INIT_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_STATIC_INIT_CALL_STACK, 0, entry);
    esp = esp - 0x4u;
    edx = 0x51a560u;
    eax = esp;
    lift_store(&env, esp, 0x0u, 4, 0x5c761cu);
    eax = lift_call(&env, 0x4da71bu, eax, edx, ebx, ecx, 1, esp);
    esp = esp + 0x4u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_rtl_jump_capture(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_JUMP_CAPTURE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_JUMP_CAPTURE_STACK, 0, entry);
    lift_store(&env, eax, 0x0u, 4, ebx);
    lift_store(&env, eax, 0x4u, 4, ecx);
    lift_store(&env, eax, 0x8u, 4, edx);
    lift_store(&env, eax, 0xcu, 4, esi);
    lift_store(&env, eax, 0x10u, 4, edi);
    lift_store(&env, eax, 0x14u, 4, ebp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        lift_store(&env, eax, 0x18u, 4, v);
    }
    lift_store(&env, eax, 0x1cu, 4, esp);
    {
        uint32_t v = lift_load(&env, eax, 0x18u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x20u, 2, 0u);
    lift_store(&env, eax, 0x22u, 2, 0u);
    lift_store(&env, eax, 0x24u, 2, 0u);
    lift_store(&env, eax, 0x26u, 2, 0u);
    lift_store(&env, eax, 0x28u, 2, 0u);
    lift_store(&env, eax, 0x2au, 2, 0u);
    {
        uint32_t v = env.chain;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        lift_store(&env, eax, 0x2cu, 4, v);
    }
    eax = eax - eax;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dbb30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DBB30_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DBB30_STACK, 0, entry);
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
    esp = esp - 0x4u;
    edi = eax;
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edx = lift_load(&env, edi, 0x8u, 4);
    esi = lift_load(&env, edi, 0xcu, 4);
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4dbb5d;
    eax = lift_load(&env, edi, 0x14u, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, (esi * 8u) + 0x0u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dbc26;
L_4dbb5d:
    esi = 0x1u;
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4dbb72;
    goto L_4dbb7d;
L_4dbb68:
    esi = esi + 1u;
    eax = eax + 0x8u;
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dbb78;
    goto L_4dbb7d;
L_4dbb72:
    eax = lift_load(&env, edi, 0x14u, 4);
    eax = eax + 0x8u;
L_4dbb78:
    {
        (void)lift_and(8, lift_load(&env, eax, 0x0u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4dbb68;
L_4dbb7d:
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dbc26;
    ebp = lift_load(&env, edi, 0x8u, 4);
    ebp = ebp + 0x20u;
    eax = ((ebp * 8u));
    lift_store(&env, esp, 0x0u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x14u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbbaa;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x2002u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c0cu, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    goto L_4dbbcf;
L_4dbbaa:
    {
        uint32_t v = lift_load(&env, edi, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c20u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    eax = lift_call(&env, 0x4f1c2cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = 0x2002u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c28u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
L_4dbbcf:
    ebx = eax;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4dbbf7;
    {
        uint32_t v = lift_load(&env, edi, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c20u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c24u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = (edi + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = lift_call(&env, 0x4d9510u, eax, edx, ebx, ecx, 0, esp);
L_4dbbf7:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c24u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ecx = eax;
    ebx = ebp;
    edx = edx ^ edx;
    eax = lift_load(&env, edi, 0x8u, 4);
    ebx = ebx - lift_load(&env, edi, 0x8u, 4);
    eax = ((eax * 8u));
    ebx = ((ebx * 8u));
    eax = eax + ecx;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, edi, 0x8u, 4, ebp);
    lift_store(&env, edi, 0x14u, 4, ecx);
L_4dbc26:
    {
        (void)lift_sub(32, esi, lift_load(&env, edi, 0x10u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dbc31;
    eax = (esi + 0x1u);
    lift_store(&env, edi, 0x10u, 4, eax);
L_4dbc31:
    eax = lift_load(&env, edi, 0x14u, 4);
    edi = edi + 0x20u;
    lift_store(&env, eax, (esi * 8u) + 0x0u, 1, lift_load(&env, eax, (esi * 8u) + 0x0u, 1) | 0x1u);
    eax = (esi + 0x1u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, edi, 0xffffffecu, 4, eax);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = esi;
    esp = esp + 0x4u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dbd20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DBD20_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DBD20_STACK, 0, entry);
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
    esp = esp - 0x4u;
    esi = eax;
    lift_store(&env, esp, 0x0u, 4, edx);
    ebp = ebx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbd43;
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edi = lift_load(&env, esi, 0x4u, 4);
    goto L_4dbd4e;
L_4dbd43:
    {
        uint32_t v = lift_load(&env, eax, 0x0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1cdcu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edi = eax;
L_4dbd4e:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4dbd5e;
    eax = lift_load(&env, esp, 0x0u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edi, 0x8u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dbe43;
L_4dbd5e:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4dbe4c;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4dbdb5;
    {
        uint32_t v = 0x10u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dba80u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dbd7b;
    lift_store(&env, eax, 0x0u, 4, 0x51ac34u);
L_4dbd7b:
    lift_store(&env, eax, 0x8u, 4, 0x0u);
    lift_store(&env, eax, 0xcu, 4, 0x0u);
    edi = eax;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbd9b;
    eax = (esi + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4dbd9b:
    eax = (esi + 0x18u);
    edx = edi;
    eax = lift_call(&env, 0x4dba10u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbdb5;
    eax = (esi + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4dbdb5:
    {
        (void)lift_sub(32, lift_load(&env, edi, 0xcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbdd1;
    eax = lift_load(&env, esi, 0x10u, 4);
    eax = ((eax * 4u));
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c4cu, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    goto L_4dbde8;
L_4dbdd1:
    eax = lift_load(&env, esi, 0x10u, 4);
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = ((eax * 4u));
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, edi, 0xcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c58u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
L_4dbde8:
    lift_store(&env, edi, 0xcu, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, edi, 0xcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbe06;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbe01;
    eax = (esi + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4dbe01:
    eax = lift_call(&env, 0x4d9510u, eax, edx, ebx, ecx, 0, esp);
L_4dbe06:
    eax = lift_load(&env, esi, 0x10u, 4);
    eax = eax - lift_load(&env, edi, 0x8u, 4);
    ebx = ((eax * 4u));
    eax = lift_load(&env, edi, 0x8u, 4);
    edx = lift_load(&env, edi, 0xcu, 4);
    eax = ((eax * 4u));
    eax = eax + edx;
    edx = edx ^ edx;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, esi, 0x10u, 4);
    lift_store(&env, edi, 0x8u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4dbe40;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ce0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    goto L_4dbe43;
L_4dbe40:
    lift_store(&env, esi, 0x4u, 4, edi);
L_4dbe43:
    eax = lift_load(&env, esp, 0x0u, 4);
    ebx = lift_load(&env, edi, 0xcu, 4);
    lift_store(&env, ebx, (eax * 4u) + 0x0u, 4, ebp);
L_4dbe4c:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbe5c;
    esi = esi + 0x20u;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
L_4dbe5c:
    esp = esp + 0x4u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4df320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DF320_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DF320_STACK, 0, entry);
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
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x70u;
    esi = ebx;
    edi = ecx;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) ^ (ebx & 0xffu)) & 0xffu);
    ecx = 0x64u;
    lift_store(&env, esp, 0x6cu, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, esp, 0x0u, 4, eax);
    lift_store(&env, esp, 0x1eu, 2, (ebx & 0xffffu));
    ebx = ebx ^ ebx;
    lift_store(&env, esp, 0x1cu, 2, (ecx & 0xffffu));
    lift_store(&env, esp, 0x10u, 4, ebx);
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, edx, 0x0u, 1)) & 0xffu) << 8);
    lift_store(&env, esp, 0x68u, 4, edx);
    {
        (void)lift_and(8, ((ebx >> 8) & 0xffu), ((ebx >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4df6ba;
L_4df359:
    eax = lift_load(&env, esp, 0x68u, 4);
    ebp = lift_load(&env, esp, 0x68u, 4);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, eax, 0x0u, 1)) & 0xffu) << 8);
    ebp = ebp + 1u;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x25u, &fl);
    }
    if (fl.zf)
        goto L_4df37a;
    edx = edx ^ edx;
    eax = esp;
    edx = (edx & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
    lift_store(&env, esp, 0x68u, 4, ebp);
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    goto L_4df692;
L_4df37a:
    ebx = esp;
    eax = lift_load(&env, esi, 0x0u, 4);
    edx = (esp + 0x60u);
    lift_store(&env, esp, 0x60u, 4, eax);
    eax = ebp;
    eax = lift_call(&env, 0x4df6c8u, eax, edx, ebx, ecx, 0, esp);
    ebp = eax;
    eax = lift_load(&env, esp, 0x60u, 4);
    ebp = ebp + 1u;
    lift_store(&env, esi, 0x0u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffffu, 1)) & 0xffu);
    lift_store(&env, esp, 0x68u, 4, ebp);
    lift_store(&env, esp, 0x15u, 1, (eax & 0xffu));
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4df6ba;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6eu, &fl);
    }
    if (!fl.zf)
        goto L_4df521;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esp, 0x1eu, 1)) & 0xffu);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4df409;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4df3de;
    edx = lift_load(&env, esi, 0x0u, 4);
    edx = edx + 0x8u;
    lift_store(&env, esi, 0x0u, 4, edx);
    edx = lift_load(&env, edx, 0xfffffff8u, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    goto L_4df6ba;
L_4df3de:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4df4cf;
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, esi, 0x0u, 4, eax);
    edx = lift_load(&env, eax, 0xfffffffcu, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    goto L_4df6ba;
L_4df409:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4df49b;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4df442;
    ecx = lift_load(&env, esi, 0x0u, 4);
    ecx = ecx + 0x8u;
    lift_store(&env, esi, 0x0u, 4, ecx);
    edx = lift_load(&env, ecx, 0xfffffff8u, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    esp = esp + 0x70u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4df442:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4df471;
    ebx = lift_load(&env, esi, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, esi, 0x0u, 4, ebx);
    edx = lift_load(&env, ebx, 0xfffffffcu, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    esp = esp + 0x70u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4df471:
    edx = lift_load(&env, esi, 0x0u, 4);
    edx = edx + 0x4u;
    lift_store(&env, esi, 0x0u, 4, edx);
    edx = lift_load(&env, edx, 0xfffffffcu, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    esp = esp + 0x70u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4df49b:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4df4ca;
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax + 0x8u;
    lift_store(&env, esi, 0x0u, 4, eax);
    edx = lift_load(&env, eax, 0xfffffff8u, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    esp = esp + 0x70u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4df4ca:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4df4f8;
L_4df4cf:
    ebp = lift_load(&env, esi, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, esi, 0x0u, 4, ebp);
    edx = lift_load(&env, ebp, 0xfffffffcu, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    esp = esp + 0x70u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4df4f8:
    ecx = lift_load(&env, esi, 0x0u, 4);
    ecx = ecx + 0x4u;
    lift_store(&env, esi, 0x0u, 4, ecx);
    edx = lift_load(&env, ecx, 0xfffffffcu, 4);
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    esp = esp + 0x70u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4df521:
    ecx = (esp + 0x6cu);
    ebx = esp;
    eax = lift_load(&env, esi, 0x0u, 4);
    edx = (esp + 0x64u);
    lift_store(&env, esp, 0x64u, 4, eax);
    eax = (esp + 0x38u);
    eax = lift_call(&env, 0x4dfb24u, eax, edx, ebx, ecx, 0, esp);
    ebp = eax;
    eax = lift_load(&env, esp, 0x64u, 4);
    (void)(edx);
    lift_store(&env, esi, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x20u, 4);
    ecx = lift_load(&env, esp, 0x24u, 4);
    edx = lift_load(&env, esp, 0x28u, 4);
    eax = eax + ecx;
    ebx = lift_load(&env, esp, 0x2cu, 4);
    eax = eax + edx;
    ecx = lift_load(&env, esp, 0x30u, 4);
    eax = eax + ebx;
    edx = lift_load(&env, esp, 0x34u, 4);
    eax = eax + ecx;
    ebx = lift_load(&env, esp, 0x4u, 4);
    eax = eax + edx;
    ebx = ebx - eax;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esp, 0x1eu, 1)) & 0xffu);
    lift_store(&env, esp, 0x4u, 4, ebx);
    {
        (void)lift_and(8, (edx & 0xffu), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_4df596;
    {
        (void)lift_sub(8, lift_load(&env, esp, 0x16u, 1), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4df596;
L_4df580:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df596;
    edx = 0x20u;
    eax = esp;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x4u, 4, lift_load(&env, esp, 0x4u, 4) - 1u);
    goto L_4df580;
L_4df596:
    eax = lift_load(&env, esp, 0x20u, 4);
    ebx = (esp + 0x38u);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df5b8;
L_4df5a2:
    edx = edx ^ edx;
    eax = esp;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, esp, 0x20u, 4);
    edx = edx - 1u;
    ebx = ebx + 1u;
    lift_store(&env, esp, 0x20u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4df5a2;
L_4df5b8:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x24u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df5ce;
    edx = 0x30u;
    eax = esp;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x24u, 4, lift_load(&env, esp, 0x24u, 4) - 1u);
    goto L_4df5b8;
L_4df5ce:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esp, 0x15u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x73u, &fl);
    }
    if (!fl.zf)
        goto L_4df60a;
    {
        (void)lift_and(8, lift_load(&env, esp, 0x1eu, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4df5ed;
    ebx = esp;
    ecx = edi;
    edx = 0u;
    eax = ebp;
    eax = lift_call(&env, 0x4dfac0u, eax, edx, ebx, ecx, 0, esp);
    goto L_4df63b;
L_4df5ed:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x28u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df63b;
    edx = edx ^ edx;
    eax = esp;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, esp, 0x28u, 4);
    edx = edx - 1u;
    ebp = ebp + 1u;
    lift_store(&env, esp, 0x28u, 4, edx);
    goto L_4df5ed;
L_4df60a:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x53u, &fl);
    }
    if (!fl.zf)
        goto L_4df61e;
    ebx = esp;
    ecx = edi;
    edx = 0u;
    eax = ebp;
    eax = lift_call(&env, 0x4dfac0u, eax, edx, ebx, ecx, 0, esp);
    goto L_4df63b;
L_4df61e:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x28u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df63b;
    edx = edx ^ edx;
    eax = esp;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    ecx = lift_load(&env, esp, 0x28u, 4);
    ecx = ecx - 1u;
    ebp = ebp + 1u;
    lift_store(&env, esp, 0x28u, 4, ecx);
    goto L_4df61e;
L_4df63b:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x2cu, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df651;
    edx = 0x30u;
    eax = esp;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x2cu, 4, lift_load(&env, esp, 0x2cu, 4) - 1u);
    goto L_4df63b;
L_4df651:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x30u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df66e;
    edx = edx ^ edx;
    eax = esp;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, esp, 0x30u, 4);
    edx = edx - 1u;
    ebp = ebp + 1u;
    lift_store(&env, esp, 0x30u, 4, edx);
    goto L_4df651;
L_4df66e:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x34u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df684;
    edx = 0x30u;
    eax = esp;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x34u, 4, lift_load(&env, esp, 0x34u, 4) - 1u);
    goto L_4df66e;
L_4df684:
    {
        (void)lift_and(8, lift_load(&env, esp, 0x1eu, 1), 0x8u, &fl);
    }
    if (fl.zf)
        goto L_4df692;
L_4df68b:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4df6ab;
L_4df692:
    eax = lift_load(&env, esp, 0x68u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df359;
    eax = lift_load(&env, esp, 0x10u, 4);
    esp = esp + 0x70u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4df6ab:
    edx = 0x20u;
    eax = esp;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x4u, 4, lift_load(&env, esp, 0x4u, 4) - 1u);
    goto L_4df68b;
L_4df6ba:
    eax = lift_load(&env, esp, 0x10u, 4);
    esp = esp + 0x70u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dfac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DFAC0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DFAC0_STACK, 0, entry);
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
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x4u;
    (void)(edx);
    edi = eax;
    edx = lift_load(&env, ebx, 0x28u, 4);
    ebp = ecx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4dfb19;
L_4dfad4:
    edx = edx ^ edx;
    eax = esp;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edi, 0x0u, 2)) & 0xffffu);
    edi = edi + 0x2u;
    eax = lift_call(&env, 0x4e62e0u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4dfaf8;
    {
        (void)lift_sub(32, eax, lift_load(&env, ebx, 0x28u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4dfb12;
    esi = esp;
L_4dfaf2:
    ecx = ecx - 1u;
    {
        (void)lift_sub(32, ecx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dfb00;
L_4dfaf8:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x28u, 4), 0x0u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4dfad4;
    goto L_4dfb19;
L_4dfb00:
    edx = edx ^ edx;
    eax = ebx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    eax = lift_call(&env, ebp, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, ebx, 0x28u, 4);
    eax = eax - 1u;
    esi = esi + 1u;
    lift_store(&env, ebx, 0x28u, 4, eax);
    goto L_4dfaf2;
L_4dfb12:
    lift_store(&env, ebx, 0x28u, 4, 0x0u);
L_4dfb19:
    esp = esp + 0x4u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dfb24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DFB24_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DFB24_STACK, 0, entry);
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
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x10u;
    esi = eax;
    ecx = ebx;
    eax = 0u;
    (void)(eax);
    lift_store(&env, ebx, 0x20u, 4, 0x0u);
    lift_store(&env, ebx, 0x24u, 4, 0x0u);
    lift_store(&env, ebx, 0x28u, 4, 0x0u);
    lift_store(&env, ebx, 0x2cu, 4, 0x0u);
    lift_store(&env, ebx, 0x30u, 4, 0x0u);
    edi = esi;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x15u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x34u, 4, 0x0u);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x69u, &fl);
    }
    if (fl.cf)
        goto L_4dfb84;
    if (fl.cf || fl.zf)
        goto L_4dfbfe;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x75u, &fl);
    }
    if (fl.cf)
        goto L_4dfb7b;
    if (fl.cf || fl.zf)
        goto L_4dfb97;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4dfb97;
    goto L_4dfcdb;
L_4dfb7b:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6fu, &fl);
    }
    if (fl.zf)
        goto L_4dfb97;
    goto L_4dfcdb;
L_4dfb84:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x58u, &fl);
    }
    if (fl.cf)
        goto L_4dfcdb;
    if (fl.cf || fl.zf)
        goto L_4dfb97;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x64u, &fl);
    }
    if (fl.zf)
        goto L_4dfbfe;
    goto L_4dfcdb;
L_4dfb97:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1fu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfbbd;
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    eax = lift_load(&env, ebp, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x4u, 4, eax);
    goto L_4dfcdb;
L_4dfbbd:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4dfbd6;
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    goto L_4dfcdb;
L_4dfbd6:
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    eax = lift_load(&env, ebp, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4dfcdb;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esp, 0x8u, 2)) & 0xffffu);
    lift_store(&env, esp, 0x8u, 4, eax);
    goto L_4dfcdb;
L_4dfbfe:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1fu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfc21;
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x4u, 4, eax);
    goto L_4dfc54;
L_4dfc21:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4dfc33;
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    eax = lift_load(&env, ebp, 0xfffffffcu, 4);
    goto L_4dfc50;
L_4dfc33:
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu) << 8);
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_and(8, ((ebx >> 8) & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4dfc54;
    eax = lift_load(&env, esp, 0x6u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
L_4dfc50:
    lift_store(&env, esp, 0x8u, 4, eax);
L_4dfc54:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1fu, 1)) & 0xffu);
    eax = eax ^ eax;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfc67;
    {
        (void)lift_and(8, lift_load(&env, esp, 0x7u, 1), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4dfc6e;
    goto L_4dfc72;
L_4dfc67:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dfc72;
L_4dfc6e:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dfcb4;
L_4dfc72:
    eax = lift_load(&env, ecx, 0x20u, 4);
    ebx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, ebx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x2du);
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1fu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfcae;
    ebx = lift_load(&env, esp, 0x0u, 4);
    ebp = lift_load(&env, esp, 0x4u, 4);
    {
        uint32_t a = ebx;
        ebx = (~a) & lift_mask(4);
    }
    {
        uint32_t a = ebp;
        ebp = (~a) & lift_mask(4);
    }
    lift_store(&env, esp, 0x0u, 4, ebx);
    eax = (ebx + 0x1u);
    lift_store(&env, esp, 0x4u, 4, ebp);
    lift_store(&env, esp, 0x0u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dfca6;
    eax = (ebp + 0x1u);
    goto L_4dfca8;
L_4dfca6:
    eax = ebp;
L_4dfca8:
    lift_store(&env, esp, 0x4u, 4, eax);
    goto L_4dfcdb;
L_4dfcae:
    lift_store(&env, esp, 0x8u, 4, 0u - lift_load(&env, esp, 0x8u, 4));
    goto L_4dfcdb;
L_4dfcb4:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4dfcca;
    eax = lift_load(&env, ecx, 0x20u, 4);
    ebx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, ebx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x2bu);
    goto L_4dfcdb;
L_4dfcca:
    {
        (void)lift_and(8, (eax & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4dfcdb;
    eax = lift_load(&env, ecx, 0x20u, 4);
    ebx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, ebx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x20u);
L_4dfcdb:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x15u, 1)) & 0xffu);
    ebx = 0xau;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x64u, &fl);
    }
    if (fl.cf)
        goto L_4dfd48;
    if (fl.cf || fl.zf)
        goto L_4dfef8;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6fu, &fl);
    }
    if (fl.cf)
        goto L_4dfd29;
    if (fl.cf || fl.zf)
        goto L_4dfed8;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x73u, &fl);
    }
    if (fl.cf)
        goto L_4dfd1c;
    if (fl.cf || fl.zf)
        goto L_4dfdf1;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x75u, &fl);
    }
    if (fl.cf)
        goto L_4e010d;
    if (fl.cf || fl.zf)
        goto L_4dfef8;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4dfe93;
    goto L_4e010d;
L_4dfd1c:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x70u, &fl);
    }
    if (fl.zf)
        goto L_4dffad;
    goto L_4e010d;
L_4dfd29:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x66u, &fl);
    }
    if (fl.cf)
        goto L_4dfdce;
    if (fl.cf || fl.zf)
        goto L_4dfd99;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x67u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4dfdce;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x69u, &fl);
    }
    if (fl.zf)
        goto L_4dfef8;
    goto L_4e010d;
L_4dfd48:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x47u, &fl);
    }
    if (fl.cf)
        goto L_4dfd84;
    if (fl.cf || fl.zf)
        goto L_4dfdce;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x53u, &fl);
    }
    if (fl.cf)
        goto L_4dfd77;
    if (fl.cf || fl.zf)
        goto L_4dfdf1;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x58u, &fl);
    }
    if (fl.cf)
        goto L_4e010d;
    if (fl.cf || fl.zf)
        goto L_4dfe93;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x63u, &fl);
    }
    if (fl.zf)
        goto L_4e0040;
    goto L_4e010d;
L_4dfd77:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x50u, &fl);
    }
    if (fl.zf)
        goto L_4dffad;
    goto L_4e010d;
L_4dfd84:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x45u, &fl);
    }
    if (fl.cf)
        goto L_4dfd8c;
    if (fl.cf || fl.zf)
        goto L_4dfdce;
    goto L_4dfd99;
L_4dfd8c:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x43u, &fl);
    }
    if (fl.zf)
        goto L_4e00cc;
    goto L_4e010d;
L_4dfd99:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4dfdce;
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    ebx = ecx;
    edx = eax;
    eax = esi;
    eax = lift_call(&env, 0x4df978u, eax, edx, ebx, ecx, 0, esp);
    ebx = 0xffffffffu;
    edx = 0u;
    eax = esi;
    eax = lift_call(&env, 0x4df884u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x28u, 4, eax);
    goto L_4e0120;
L_4dfdce:
    ebx = ecx;
    eax = esi;
    eax = lift_call(&env, 0x4dfa74u, eax, edx, ebx, ecx, 0, esp);
    eax = ecx;
    eax = lift_call(&env, 0x4dfa7cu, eax, edx, ebx, ecx, 0, esp);
    eax = 0u;
    edi = (esi + 0x1u);
    (void)(eax);
    edx = 0u;
    eax = edi;
    esp = esp + 0x10u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4dfdf1:
    lift_store(&env, esi, 0x0u, 1, 0x0u);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4dfe18;
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x8u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    eax = lift_load(&env, ebp, 0xfffffff8u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xfffffffcu, 2)) & 0xffffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dfe12;
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4dfe40;
L_4dfe12:
    (void)(edx);
    edi = eax;
    goto L_4dfe40;
L_4dfe18:
    {
        (void)lift_and(8, (eax & 0xffu), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4dfe2c;
    esi = lift_load(&env, edx, 0x0u, 4);
    esi = esi + 0x4u;
    lift_store(&env, edx, 0x0u, 4, esi);
    eax = lift_load(&env, esi, 0xfffffffcu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dfe40;
    goto L_4dfe3a;
L_4dfe2c:
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dfe40;
L_4dfe3a:
    edx = 0u;
    edi = eax;
    (void)(edx);
L_4dfe40:
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x53u, &fl);
    }
    if (!fl.zf)
        goto L_4dfe4e;
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4dfe54;
    goto L_4dfe62;
L_4dfe4e:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4dfe62;
L_4dfe54:
    edx = 0u;
    eax = edi;
    ebx = lift_load(&env, ecx, 0x8u, 4);
    eax = lift_call(&env, 0x4df8a8u, eax, edx, ebx, ecx, 0, esp);
    goto L_4dfe6e;
L_4dfe62:
    edx = 0u;
    eax = edi;
    ebx = lift_load(&env, ecx, 0x8u, 4);
    eax = lift_call(&env, 0x4df884u, eax, edx, ebx, ecx, 0, esp);
L_4dfe6e:
    edx = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, ecx, 0x28u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e0120;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e0120;
    lift_store(&env, ecx, 0x28u, 4, edx);
    edx = 0u;
    eax = edi;
    esp = esp + 0x10u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4dfe93:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfed3;
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1fu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfeae;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dfeb5;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dfed3;
    goto L_4dfeb5;
L_4dfeae:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dfed3;
L_4dfeb5:
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x30u);
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    edx = (esi + eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x15u, 1)) & 0xffu);
    lift_store(&env, edx, 0x0u, 1, (eax & 0xffu));
L_4dfed3:
    ebx = 0x10u;
L_4dfed8:
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x6fu, &fl);
    }
    if (!fl.zf)
        goto L_4dfef8;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    ebx = 0x8u;
    {
        (void)lift_and(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfef8;
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x30u);
L_4dfef8:
    edx = 0u;
    eax = lift_load(&env, ecx, 0x20u, 4);
    (void)(edx);
    eax = eax + esi;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ecx, 0x1fu, 1)) & 0xffu) << 8);
    edi = eax;
    {
        (void)lift_and(8, ((edx >> 8) & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dff41;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff26;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff26;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff26;
    lift_store(&env, eax, 0x0u, 1, 0x0u);
    eax = eax ^ eax;
    goto L_4dff7f;
L_4dff26:
    edx = lift_load(&env, ecx, 0x20u, 4);
    eax = esp;
    edx = edx + esi;
    eax = lift_call(&env, 0x4e63b0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x58u, &fl);
    }
    if (!fl.zf)
        goto L_4dff71;
    eax = esi;
    eax = lift_call(&env, 0x4e012cu, eax, edx, ebx, ecx, 0, esp);
    goto L_4dff71;
L_4dff41:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff56;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff56;
    lift_store(&env, eax, 0x0u, 1, 0x0u);
    eax = eax ^ eax;
    goto L_4dff7f;
L_4dff56:
    edx = lift_load(&env, ecx, 0x20u, 4);
    eax = lift_load(&env, esp, 0x8u, 4);
    edx = edx + esi;
    eax = lift_call(&env, 0x4e64a0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x58u, &fl);
    }
    if (!fl.zf)
        goto L_4dff71;
    eax = esi;
    eax = lift_call(&env, 0x4e012cu, eax, edx, ebx, ecx, 0, esp);
L_4dff71:
    ebx = 0xffffffffu;
    edx = 0u;
    eax = edi;
    eax = lift_call(&env, 0x4df884u, eax, edx, ebx, ecx, 0, esp);
L_4dff7f:
    lift_store(&env, ecx, 0x28u, 4, eax);
    edx = eax;
    eax = lift_load(&env, ecx, 0x8u, 4);
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4dff90;
    eax = eax - edx;
    lift_store(&env, ecx, 0x24u, 4, eax);
L_4dff90:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x8u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e0120;
    eax = ecx;
    eax = lift_call(&env, 0x4dfa7cu, eax, edx, ebx, ecx, 0, esp);
    edx = 0u;
    eax = edi;
    esp = esp + 0x10u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4dffad:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dffc9;
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4dffc2;
    lift_store(&env, ecx, 0x4u, 4, 0xdu);
    goto L_4dffc9;
L_4dffc2:
    lift_store(&env, ecx, 0x4u, 4, 0x8u);
L_4dffc9:
    lift_store(&env, ecx, 0x1eu, 1, lift_load(&env, ecx, 0x1eu, 1) & 0xf9u);
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    ebp = lift_load(&env, eax, 0xfffffffcu, 4);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4e0008;
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    ebx = 0x4u;
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    edx = esi;
    eax = eax & 0xffffu;
    eax = lift_call(&env, 0x4df914u, eax, edx, ebx, ecx, 0, esp);
    ebx = 0x8u;
    edx = (esi + 0x5u);
    eax = ebp;
    lift_store(&env, esi, 0x4u, 1, 0x3au);
    goto L_4e0011;
L_4e0008:
    ebx = 0x8u;
    edx = esi;
    eax = ebp;
L_4e0011:
    eax = lift_call(&env, 0x4df914u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x50u, &fl);
    }
    if (!fl.zf)
        goto L_4e0023;
    eax = esi;
    eax = lift_call(&env, 0x4e012cu, eax, edx, ebx, ecx, 0, esp);
L_4e0023:
    ebx = 0xffffffffu;
    edx = 0u;
    eax = edi;
    eax = lift_call(&env, 0x4df884u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x20u, 4, eax);
    edx = 0u;
    eax = edi;
    esp = esp + 0x10u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4e0040:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    lift_store(&env, ecx, 0x20u, 4, 0x1u);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4e00b4;
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0xfffffffcu, 2)) & 0xffffu);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = (esp + 0xcu);
    eax = lift_call(&env, 0x4e62e0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4e0120;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0xcu, 1)) & 0xffu);
    ebp = lift_load(&env, 0u, 0x5c8950u, 4);
    lift_store(&env, esi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4e0120;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0xcu, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x5c8961u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4e0120;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0xdu, 1)) & 0xffu);
    lift_store(&env, esi, 0x1u, 1, (eax & 0xffu));
    lift_store(&env, ecx, 0x20u, 4, lift_load(&env, ecx, 0x20u, 4) + 1u);
    edx = 0u;
    eax = edi;
    esp = esp + 0x10u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4e00b4:
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0xfffffffcu, 1)) & 0xffu);
    lift_store(&env, esi, 0x0u, 1, (eax & 0xffu));
    edx = 0u;
    eax = edi;
    esp = esp + 0x10u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4e00cc:
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xfffffffcu, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    eax = esi;
    eax = lift_call(&env, 0x4e62e0u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4e00fa;
    lift_store(&env, ecx, 0x20u, 4, eax);
    edx = 0u;
    eax = edi;
    esp = esp + 0x10u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4e00fa:
    lift_store(&env, ecx, 0x20u, 4, 0x0u);
    edx = 0u;
    eax = edi;
    esp = esp + 0x10u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
L_4e010d:
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x15u, 1)) & 0xffu);
    lift_store(&env, esi, 0x0u, 1, (eax & 0xffu));
    lift_store(&env, ecx, 0x20u, 4, 0x1u);
L_4e0120:
    edx = 0u;
    eax = edi;
    esp = esp + 0x10u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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
    return env.failed ? 0u : eax;
}
