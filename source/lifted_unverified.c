/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md) that did NOT pass
 * tools/verify_lifted.py: unverified, used only when explicitly enabled. */
#include "lift_runtime.h"

#include "lifted_unverified.h"

uint32_t lifted_f41fe10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F41FE10_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F41FE10_STACK, 0, entry);
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
    esp = esp - 0x118u;
    esi = lift_load(&env, 0u, 0x532a64u, 4);
    ecx = eax;
    eax = (ebp + 0xffffffd8u);
    edx = 0x4ec1ecu;
    ebx = 0x514130u;
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
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    eax = ecx;
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ab90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ac20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ac40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ac70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a9e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4719e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f9f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x532a64u, 4);
    esi = esi + 1u;
    edi = lift_load(&env, 0u, (esi * 4u) + 0x4f9afcu, 4);
    {
        (void)lift_sub(32, esi, 0x14u, &fl);
    }
    if (!fl.cf)
        goto L_41fec6;
L_41fe99:
    edx = edx ^ edx;
L_41fe9b:
    eax = ((esi * 4u));
    ebx = lift_load(&env, eax, 0x53bd0cu, 4);
    lift_store(&env, 0u, 0x532a64u, 4, esi);
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_41fed4;
    esi = esi + 1u;
    {
        (void)lift_sub(32, esi, 0x14u, &fl);
    }
    if (fl.cf)
        goto L_41fe9b;
    eax = 0x1u;
    esi = ebx;
    lift_store(&env, 0u, 0x53d944u, 4, eax);
    goto L_41fe9b;
L_41fec6:
    eax = 0x1u;
    esi = esi ^ esi;
    lift_store(&env, 0u, 0x53d944u, 4, eax);
    goto L_41fe99;
L_41fed4:
    eax = lift_load(&env, eax, 0x53d948u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x5332c0u;
    edx = 0x4fc290u;
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = (ebp + 0xfffffed4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xfffffed4u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41a960u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f770u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471340u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x13u;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax & 0xffffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4713c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x46f440u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532a98u, 4);
    lift_store(&env, 0u, 0x532a58u, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aa20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ab00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ab60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aaa0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0xc8u, 1, 0x1u);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_41ffbc;
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_41ffca;
    {
        (void)lift_sub(32, edi, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_41ffd8;
    {
        (void)lift_sub(32, edi, 0x3u, &fl);
    }
    if (fl.zf)
        goto L_41ffe6;
    {
        (void)lift_sub(32, edi, 0x4u, &fl);
    }
    if (fl.zf)
        goto L_41fff4;
    {
        (void)lift_sub(32, edi, 0x5u, &fl);
    }
    if (fl.zf)
        goto L_420002;
    {
        (void)lift_sub(32, edi, 0x6u, &fl);
    }
    if (fl.zf)
        goto L_420010;
    {
        (void)lift_sub(32, edi, 0x7u, &fl);
    }
    if (fl.zf)
        goto L_420021;
L_41ff97:
    edx = 0x41fb40u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    env.chain = eax;
    esi = lift_load(&env, 0u, 0x532a64u, 4);
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
L_41ffbc:
    edx = 0x422c50u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_41ff97;
L_41ffca:
    edx = 0x4220d0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_41ff97;
L_41ffd8:
    edx = 0x4223d0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_41ff97;
L_41ffe6:
    edx = 0x422800u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_41ff97;
L_41fff4:
    edx = 0x423600u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_41ff97;
L_420002:
    edx = 0x4237d0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_41ff97;
L_420010:
    edx = 0x423bc0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_41ff97;
L_420021:
    edx = 0x423fb0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_41ff97;
}

uint32_t lifted_f423960(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F423960_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F423960_STACK, 0, entry);
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
    esp = esp - 0x28u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = (ebp + 0xffffffc4u);
    edx = 0x4ec1ecu;
    ecx = 0x514210u;
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
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, 0u, 0x5405fcu, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_423b63;
L_4239a3:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7d10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = 0x9u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41d670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54676cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5eb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4239cb;
    eax = lift_load(&env, eax, 0x58u, 4);
L_4239cb:
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x540600u, 4), 0x1e0u, &fl);
    }
    if (!fl.zf)
        goto L_423a04;
    edx = lift_load(&env, 0u, 0x558c80u, 4);
    ecx = lift_load(&env, edx, 0x8u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, edx, 0x4u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47ce10u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
L_423a04:
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, esi, lift_load(&env, 0u, 0x540600u, 4), &fl);
    }
    if (fl.zf)
        goto L_423b00;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6775u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    edx = 0x407e0000u;
    eax = eax ^ eax;
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = edi ^ edi;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_423a80;
L_423a3e:
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    edx = lift_load(&env, 0u, 0x558c80u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edi = edi + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47ce10u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = esi;
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d80a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        (void)lift_sub(32, edi, ecx, &fl);
    }
    if (fl.cf)
        goto L_423a3e;
L_423a80:
    eax = 0x1e0u;
    eax = eax - lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6775u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    ecx = edx;
    edx = 0x407e0000u;
    eax = eax ^ eax;
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_sub(32, edi, 0x1e0u, &fl);
    }
    if (!fl.cf)
        goto L_423b00;
L_423ab2:
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = edi;
    ebx = ebx ^ ebx;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x558c88u, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47ce10u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = esi;
    edi = edi + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d80a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        (void)lift_sub(32, edi, 0x1e0u, &fl);
    }
    if (fl.cf)
        goto L_423ab2;
L_423b00:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41d6d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486da0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487020u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, 0u, 0x540600u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41d660u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41de80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ddf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472360u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_423b8d;
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
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
L_423b63:
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    esi = 0x1e0u;
    lift_store(&env, 0u, 0x5405fcu, 1, (edx & 0xffu));
    lift_store(&env, 0u, 0x540600u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472570u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41d640u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4239a3;
L_423b8d:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472330u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41ac80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418830u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5405fcu, 1, ((edx >> 8) & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
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

uint32_t lifted_f43e2a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F43E2A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F43E2A0_STACK, 0, entry);
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
    esp = esp - 0x4u;
    esi = eax;
    ecx = edx;
    ebx = eax;
    eax = eax + 0x708u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_43e2b8:
    eax = lift_load(&env, ebx, 0x15cu, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x44u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_43e2f3;
L_43e2c4:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = ebx + 0x4u;
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (!fl.zf)
        goto L_43e2b8;
    edx = 0x3u;
    eax = (esi + 0x864u);
    ebx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b2380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, esi, 0x870u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_43e300;
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
L_43e2f3:
    edi = lift_load(&env, eax, 0x158u, 4);
    edx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_43e2c4;
L_43e300:
    eax = ebx;
    ebx = lift_load(&env, ebx, 0x158u, 4);
    edx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
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
}

uint32_t lifted_f43e320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F43E320_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F43E320_STACK, 0, entry);
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
    edi = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c8eu, 2)) & 0xffffu);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    lift_store(&env, 0u, 0x540fe8u, 2, (eax & 0xffffu));
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
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5b9c90u, 2)) & 0xffffu);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((ecx & 0xffffu)) & 0xffffu);
    lift_store(&env, 0u, 0x540fecu, 2, (eax & 0xffffu));
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
    lift_store(&env, 0u, 0x540feau, 2, (ecx & 0xffffu));
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x540feeu, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x540fdcu, 4, edx);
L_43e371:
    eax = lift_load(&env, 0u, 0x540fdcu, 4);
    eax = lift_load(&env, edi, (eax * 4u) + 0x15cu, 4);
    lift_store(&env, 0u, 0x540fe4u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_43e3be;
L_43e386:
    eax = lift_load(&env, 0u, 0x540fdcu, 4);
    eax = eax + 1u;
    lift_store(&env, 0u, 0x540fdcu, 4, eax);
    {
        (void)lift_sub(32, eax, 0x1c2u, &fl);
    }
    if (fl.cf)
        goto L_43e371;
    edx = 0x1u;
    eax = (edi + 0x870u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b23c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3u;
    eax = (edi + 0x864u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b23c0u, eax, edx, ebx, ecx, 0, esp);
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
L_43e3be:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x540fe4u, 4);
    ecx = 0x3ff00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac560u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    esi = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb57cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf != fl.of)
        goto L_43e409;
    eax = lift_load(&env, 0u, 0x540fe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = esi;
    eax = lift_load(&env, 0u, 0x540fe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad720u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_43e409;
    edx = lift_load(&env, 0u, 0x540fe4u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43e740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43e409:
    ecx = lift_load(&env, 0u, 0x540fe4u, 4);
    edx = 0xc8u;
    eax = lift_load(&env, ecx, 0x58u, 4);
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x540ff8u, 4, edx);
    if (fl.zf)
        goto L_43e4b1;
    edx = lift_load(&env, ecx, 0x6u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    esi = lift_load(&env, 0u, 0x540ff8u, 4);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, esi, &eax, &edx, &fl);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x540fecu, 2)) & 0xffffu);
    eax = eax + edx;
    edx = lift_load(&env, ecx, 0x8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, esi, &eax, &edx, &fl);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x540feeu, 2)) & 0xffffu);
    eax = eax + edx;
    edx = esi;
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edx = r;
    }
    esi = 0xc8u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, esi, &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    eax = (edx + 0xffffffffu);
    lift_store(&env, 0u, 0x541004u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_43e490;
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    goto L_43e386;
L_43e490:
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x540fe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x540fe4u, 4);
    lift_store(&env, eax, 0x44u, 1, 0x10u);
    goto L_43e386;
L_43e4b1:
    lift_store(&env, ecx, 0xeu, 2, 0x0u);
    lift_store(&env, ecx, 0x16u, 2, 0x0u);
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    goto L_43e386;
}

uint32_t lifted_f452520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F452520_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F452520_STACK, 0, entry);
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
    edx = lift_load(&env, eax, 0x3b0u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    esi = lift_load(&env, eax, 0x15cu, 4);
    eax = lift_load(&env, edx, 0x3b4u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = esi;
    edi = lift_load(&env, edx, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4525b2;
L_45255f:
    ebx = lift_load(&env, esi, 0x58u, 4);
    {
        (void)lift_sub(32, ebx, 0x18u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4526ba;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f760u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x444u, 4, lift_load(&env, eax, 0x444u, 4) + 1u);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f410u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, eax, 0x428u, 4, lift_load(&env, eax, 0x428u, 4) + 1u);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4320c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4525d0;
L_45259e:
    eax = lift_load(&env, esi, 0x58u, 4);
    {
        (void)lift_sub(32, eax, 0x18u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_452660;
    edx = (eax + 0xffffffe8u);
    lift_store(&env, esi, 0x58u, 4, edx);
    goto L_45259e;
L_4525b2:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esi, 0x18u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x58u, 4, lift_load(&env, esi, 0x58u, 4) + edx);
    goto L_45255f;
L_4525d0:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x170u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_452635;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431d60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_452635;
    eax = lift_load(&env, edi, 0xa60u, 4);
    edx = lift_load(&env, eax, 0x15cu, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x15cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 1, (edx & 0xffu));
    edx = lift_load(&env, eax, 0x160u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x15cu, 1)) & 0xffu);
    eax = lift_load(&env, eax, 0x164u, 4);
    ebx = (uint32_t)(int32_t)(int8_t)(uint8_t)(edx & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x15cu, 1)) & 0xffu);
    edx = lift_load(&env, ebp, 0xffffffe5u, 4);
    ecx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43a560u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, eax, 0x170u, 4, 0x0u);
L_452635:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432010u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_45259e;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431340u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42eb60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_45259e;
L_452660:
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = edi;
    ebx = lift_load(&env, ebx, 0x3f0u, 4);
    edx = lift_load(&env, edx, 0x428u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4316c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4526aa;
    edx = 0x4526e0u;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_45268a:
    edx = lift_load(&env, esi, 0x158u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, edi, 0x158u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_4526aa:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, 0u, 0x4f8188u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43c0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_45268a;
L_4526ba:
    eax = edi;
    lift_store(&env, edi, 0x58u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f2b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f2e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_45268a;
}

uint32_t lifted_state_pair_453050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_STATE_PAIR_453050_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_STATE_PAIR_453050_STACK, 0, entry);
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
    esp = esp - 0x4u;
    edi = eax;
    esi = lift_load(&env, eax, 0x3b0u, 4);
    edx = edx ^ edx;
    ebx = lift_load(&env, eax, 0x15cu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    eax = ebx;
    edx = 0x44c860u;
    ecx = lift_load(&env, esi, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42eca0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4530f4;
    edx = 0x44c860u;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ecc0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4530f4;
    edx = 0x44c860u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42eca0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4530f4;
    edx = 0x44c860u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ecc0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4530f4;
    edx = 0x44c860u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42edf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_45310f;
L_4530c8:
    edx = 0x44c940u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42edf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4530df;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42eb60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4530df:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ebe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ebe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x1u);
L_4530f4:
    edx = lift_load(&env, ebx, 0x158u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_453121;
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
L_45310f:
    edx = 0x44c940u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42edf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4530c8;
    goto L_4530f4;
L_453121:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bbf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bbf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0xb8cu, 4, 0x0u);
    lift_store(&env, ecx, 0xb8cu, 4, 0x0u);
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

uint32_t lifted_palette_tables_build(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PALETTE_TABLES_BUILD_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PALETTE_TABLES_BUILD_STACK, 0, entry);
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
    esp = esp - 0x19cu;
    eax = (ebp + 0xffffff64u);
    edx = 0x4ec1ecu;
    ecx = 0x516430u;
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
    eax = 0x40000u;
    lift_store(&env, ebp, 0xffffff68u, 4, edx);
    lift_store(&env, ebp, 0xffffff6cu, 4, ecx);
    lift_store(&env, ebp, 0xffffff70u, 4, ebx);
    edx = 0x4u;
    lift_store(&env, ebp, 0xffffff9cu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    lift_store(&env, 0u, 0x54b800u, 4, eax);
    eax = 0x40000u;
    lift_store(&env, ebp, 0xffffff98u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54b804u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x474cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_475104:
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0xcu, &fl);
        eax = r;
    }
    eax = eax & 0xffu;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    lift_store(&env, ebp, 0xffffffbcu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x3fu) & 0xffu);
    eax = eax & 0xffu;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    lift_store(&env, ebp, 0xffffffb8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff9cu, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x3fu) & 0xffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    ecx = (ebp + 0xffffffa4u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd0u, 2, (eax & 0xffffu));
    eax = (ebp + 0xffffffb0u);
    edx = edx ^ edx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffacu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffc0u, 2)) & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffc8u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffb4u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x474560u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4754b1;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffa4u, 2, (edx & 0xffffu));
L_475172:
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe0u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, ebp, 0xffffffe8u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, ebp, 0xffffffdcu, 1, ((eax >> 8) & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffb0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, 0x65u, &fl);
        eax = r;
    }
    esi = 0x100u;
    ecx = 0x5468b0u;
    edi = esi;
    ecx = ecx + eax;
    eax = eax ^ eax;
    ebx = esi;
    lift_store(&env, ebp, 0xffffff7cu, 4, eax);
L_4751a4:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffff88u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffbau, 4);
    edx = lift_load(&env, ebp, 0xffffff88u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;
    eax = eax ^ edx;
    eax = eax - edx;
    {
        (void)lift_sub(16, (eax & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4751cb;
    esi = eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe0u, 1, (eax & 0xffu));
L_4751cb:
    edx = lift_load(&env, ebp, 0xffffffb6u, 4);
    eax = eax ^ eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    edx = edx - eax;
    eax = edx;
    edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;
    eax = eax ^ edx;
    eax = eax - edx;
    {
        (void)lift_sub(16, (eax & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4751ee;
    edi = eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 1, (eax & 0xffu));
L_4751ee:
    edx = lift_load(&env, ebp, 0xffffffceu, 4);
    eax = eax ^ eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    edx = edx - eax;
    eax = edx;
    edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;
    eax = eax ^ edx;
    eax = eax - edx;
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_475211;
    ebx = eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffdcu, 1, (eax & 0xffu));
L_475211:
    eax = lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = eax + 1u;
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffff7cu, 4, eax);
    {
        (void)lift_sub(32, eax, 0x65u, &fl);
    }
    if (fl.cf)
        goto L_4751a4;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    edx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x18u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx | eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffdcu, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    eax = eax | edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffc4u, 2)) & 0xffffu);
    ecx = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = eax | edx;
    edx = lift_load(&env, 0u, 0x54b800u, 4);
    esi = lift_load(&env, ebp, 0xffffff9cu, 4);
    edx = edx + ecx;
    esi = esi + 1u;
    ebx = (ecx + 0x4u);
    lift_store(&env, edx, 0x0u, 4, eax);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = lift_load(&env, 0u, 0x54b804u, 4);
    lift_store(&env, ebp, 0xffffff98u, 4, ebx);
    edx = edx + eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffff9cu, 4, esi);
    lift_store(&env, edx, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, esi, 0x40000u, &fl);
    }
    if (fl.cf)
        goto L_475104;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffff84u, 4, eax);
    lift_store(&env, ebp, 0xffffff78u, 4, eax);
L_47528a:
    eax = lift_load(&env, ebp, 0xffffff84u, 4);
    ecx = 0xfeu;
    edx = edx ^ edx;
    lift_div1(32, ecx, &eax, &edx, &fl);
    ebx = 0x64u;
    lift_store(&env, ebp, 0xffffffacu, 4, ebx);
    lift_store(&env, ebp, 0xffffffb0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffa4u, 2, (eax & 0xffffu));
    eax = (ebp + 0xffffffc8u);
    ebx = 0x64u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffc0u);
    ecx = (ebp + 0xffffffb4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax ^ eax;
    edx = ebx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffa4u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x474910u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffb0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, ecx, 0x65u, &fl);
        ecx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) ^ (ebx & 0xffu)) & 0xffu);
    lift_store(&env, ebp, 0xffffffccu, 2, (eax & 0xffffu));
    lift_store(&env, ebp, 0xffffffd4u, 1, (ebx & 0xffu));
    lift_store(&env, ebp, 0xffffffe4u, 1, (ebx & 0xffu));
    lift_store(&env, ebp, 0xffffffd8u, 1, (ebx & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    ebx = 0x100u;
    lift_store(&env, ebp, 0xffffffa0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    esi = ebx;
    lift_store(&env, ebp, 0xffffffa8u, 2, (eax & 0xffffu));
    eax = eax ^ eax;
    edi = ebx;
    lift_store(&env, ebp, 0xffffff7cu, 4, eax);
    ecx = ecx + 0x5468b0u;
L_475302:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffff88u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffcau, 4);
    edx = lift_load(&env, ebp, 0xffffff88u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;
    eax = eax ^ edx;
    eax = eax - edx;
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_475329;
    ebx = eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffd4u, 1, (eax & 0xffu));
L_475329:
    edx = lift_load(&env, ebp, 0xffffff9eu, 4);
    eax = eax ^ eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    edx = edx - eax;
    eax = edx;
    edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;
    eax = eax ^ edx;
    eax = eax - edx;
    {
        (void)lift_sub(16, (eax & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_47534c;
    esi = eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe4u, 1, (eax & 0xffu));
L_47534c:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffff88u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa6u, 4);
    edx = lift_load(&env, ebp, 0xffffff88u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = (eax & 0x80000000u) ? 0xffffffffu : 0u;
    eax = eax ^ edx;
    eax = eax - edx;
    {
        (void)lift_sub(16, (eax & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.sf == fl.of)
        goto L_475373;
    edi = eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffd8u, 1, (eax & 0xffu));
L_475373:
    eax = lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = eax + 1u;
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffff7cu, 4, eax);
    {
        (void)lift_sub(32, eax, 0x65u, &fl);
    }
    if (fl.cf)
        goto L_475302;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    edx = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x18u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx | eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    edx = edx | eax;
    eax = eax ^ eax;
    ecx = lift_load(&env, ebp, 0xffffff84u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffb0u, 2)) & 0xffffu);
    ecx = ecx + 0x167u;
    eax = eax | edx;
    edx = lift_load(&env, ebp, 0xffffff78u, 4);
    lift_store(&env, ebp, 0xffffff84u, 4, ecx);
    ebx = (edx + 0x4u);
    lift_store(&env, edx, 0x54c1d4u, 4, eax);
    lift_store(&env, ebp, 0xffffff78u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x3fcu, &fl);
    }
    if (!fl.zf)
        goto L_47528a;
    edi = 0x64u;
    eax = eax ^ eax;
L_4753e4:
    eax = eax + 0x4u;
    edx = lift_load(&env, eax, 0x54c1d0u, 4);
    lift_store(&env, eax, 0x54c9c8u, 4, edi);
    lift_store(&env, eax, 0x54c5ccu, 4, edx);
    {
        (void)lift_sub(32, eax, 0x3fcu, &fl);
    }
    if (!fl.zf)
        goto L_4753e4;
    edx = 0x5468b0u;
    eax = eax ^ eax;
L_475407:
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x54b86cu, 4, edx);
    {
        (void)lift_sub(32, eax, 0x320u, &fl);
    }
    if (!fl.zf)
        goto L_475407;
    eax = eax ^ eax;
L_475419:
    lift_store(&env, eax, 0x54bb90u, 4, edx);
    eax = eax + 0x4u;
    edx = edx + 0x65u;
    {
        (void)lift_sub(32, eax, 0x324u, &fl);
    }
    if (!fl.zf)
        goto L_475419;
    ecx = 0x54b798u;
    eax = eax ^ eax;
L_475433:
    eax = eax + 0x4u;
    lift_store(&env, eax, 0x54beb0u, 4, ecx);
    {
        (void)lift_sub(32, eax, 0x320u, &fl);
    }
    if (!fl.zf)
        goto L_475433;
    ebx = 0xc8u;
    esi = 0x54c9ccu;
    eax = 0x54c1d4u;
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffff7cu, 4, ebx);
    lift_store(&env, 0u, 0x54d1d0u, 4, esi);
    lift_store(&env, ebp, 0xffffff7cu, 4, edi);
L_475466:
    edx = lift_load(&env, ebp, 0xffffff7cu, 4);
    lift_store(&env, 0u, (edx * 4u) + 0x54d1d4u, 4, eax);
    edx = edx + 1u;
    eax = eax + 0x4u;
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    {
        (void)lift_sub(32, edx, 0xffu, &fl);
    }
    if (fl.cf)
        goto L_475466;
    ebx = 0x54bb90u;
    esi = 0x54d1d0u;
    eax = lift_load(&env, ebp, 0xffffff64u, 4);
    lift_store(&env, 0u, 0x54cdc8u, 4, ebx);
    lift_store(&env, 0u, 0x54cdccu, 4, esi);
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
L_4754b1:
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffa4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, edx, 0xfeu, &fl);
        edx = r;
    }
    ecx = 0x167u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffa4u, 2, (eax & 0xffffu));
    goto L_475172;
}

uint32_t lifted_f47e890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47E890_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47E890_STACK, 0, entry);
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
    ebx = eax;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x51693cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x1bcu, 4, 0x0u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x1c0u, 4, 0x0u);
    {
        uint32_t v = 0x51690cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x1c4u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f175cu, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_47e8ff;
L_47e8d4:
    ecx = lift_load(&env, ebx, 0x0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_47e973;
L_47e8de:
    esi = lift_load(&env, ebx, 0x1bcu, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_47e8f8;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, esi, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, ebx, 0x1bcu, 4, 0x0u);
L_47e8f8:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
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
L_47e8ff:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x47eab0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x0u, 4);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_47e8d4;
    eax = (ebx + 0x1bcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5169bcu;
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
        uint32_t v = 0x51699cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f175cu, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_47e8d4;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebx + 0x1c0u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x47eb60u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x1bcu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0xcu, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_47e8d4;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x1c0u, 4), 0x0u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    lift_store(&env, ebx, 0x1c4u, 4, eax);
    eax = 0x1u;
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
L_47e973:
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ecx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, ebx, 0x0u, 4, 0x0u);
    goto L_47e8de;
}

uint32_t lifted_render_weights_build(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RENDER_WEIGHTS_BUILD_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RENDER_WEIGHTS_BUILD_STACK, 0, entry);
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
    esp = esp - 0x24u;
    edx = 0x100u;
    ebp = ebp ^ ebp;
    lift_store(&env, esp, 0x4u, 4, edx);
    lift_store(&env, esp, 0x8u, 4, ebp);
L_480748:
    edi = lift_load(&env, esp, 0x8u, 4);
    ebx = ebp;
    esi = lift_load(&env, esp, 0x4u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_imul(32, ebp, 0x0u, &fl);
        ecx = r;
    }
L_480758:
    lift_store(&env, esp, 0x20u, 4, 0x64u);
    eax = ecx;
    edx = edx ^ edx;
    lift_div1(32, lift_load(&env, esp, 0x20u, 4), &eax, &edx, &fl);
    ebx = ebx + 1u;
    ecx = ecx + edi;
    lift_store(&env, ebx, 0x558cefu, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (!fl.zf)
        goto L_480758;
    ebx = lift_load(&env, esp, 0x4u, 4);
    esi = lift_load(&env, esp, 0x8u, 4);
    ebp = ebp + 1u;
    ebx = ebx + 0x100u;
    esi = esi + 1u;
    lift_store(&env, esp, 0x4u, 4, ebx);
    lift_store(&env, esp, 0x8u, 4, esi);
    {
        (void)lift_sub(32, ebp, 0x65u, &fl);
    }
    if (fl.cf)
        goto L_480748;
    edi = 0x400u;
    ebp = ebp ^ ebp;
    lift_store(&env, esp, 0x0u, 4, edi);
    lift_store(&env, esp, 0x14u, 4, ebp);
L_4807a0:
    esi = lift_load(&env, esp, 0x14u, 4);
    ecx = ebp;
    edi = lift_load(&env, esp, 0x0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, ebp, 0x0u, &fl);
        ebx = r;
    }
L_4807af:
    lift_store(&env, esp, 0x20u, 4, 0x64u);
    eax = ebx;
    edx = edx ^ edx;
    lift_div1(32, lift_load(&env, esp, 0x20u, 4), &eax, &edx, &fl);
    ecx = ecx + 0x2u;
    ebx = ebx + esi;
    lift_store(&env, ecx, 0x55f1f6u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (!fl.zf)
        goto L_4807af;
    edx = lift_load(&env, esp, 0x0u, 4);
    ecx = lift_load(&env, esp, 0x14u, 4);
    ebp = ebp + 1u;
    edx = edx + 0x400u;
    ecx = ecx + 1u;
    lift_store(&env, esp, 0x0u, 4, edx);
    lift_store(&env, esp, 0x14u, 4, ecx);
    {
        (void)lift_sub(32, ebp, 0x65u, &fl);
    }
    if (fl.cf)
        goto L_4807a0;
    esi = 0x100u;
    ebx = ebx ^ ebx;
    ebp = 0xff00u;
    lift_store(&env, esp, 0x1cu, 4, ebx);
    lift_store(&env, esp, 0x18u, 4, esi);
    lift_store(&env, esp, 0x10u, 4, ebx);
    lift_store(&env, esp, 0xcu, 4, ebp);
L_480806:
    ecx = lift_load(&env, esp, 0x1cu, 4);
    esi = lift_load(&env, esp, 0xcu, 4);
    ebp = lift_load(&env, esp, 0x10u, 4);
    eax = lift_load(&env, esp, 0x1cu, 4);
    edi = lift_load(&env, esp, 0x18u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, eax, 0x0u, &fl);
        ebx = r;
    }
L_480820:
    lift_store(&env, esp, 0x20u, 4, 0xffu);
    eax = ebx;
    edx = edx ^ edx;
    lift_div1(32, lift_load(&env, esp, 0x20u, 4), &eax, &edx, &fl);
    ecx = ecx + 1u;
    esi = esi + 1u;
    ebx = ebx + ebp;
    lift_store(&env, ecx, 0x5785ffu, 1, (eax & 0xffu));
    lift_store(&env, esi, 0x5885ffu, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (!fl.zf)
        goto L_480820;
    edx = lift_load(&env, esp, 0x18u, 4);
    ecx = lift_load(&env, esp, 0x10u, 4);
    ebx = lift_load(&env, esp, 0xcu, 4);
    esi = lift_load(&env, esp, 0x1cu, 4);
    edx = edx + 0x100u;
    ecx = ecx + 1u;
    ebx = ebx - 0x100u;
    esi = esi + 1u;
    lift_store(&env, esp, 0x18u, 4, edx);
    lift_store(&env, esp, 0x10u, 4, ecx);
    lift_store(&env, esp, 0xcu, 4, ebx);
    lift_store(&env, esp, 0x1cu, 4, esi);
    {
        (void)lift_sub(32, esi, 0x100u, &fl);
    }
    if (fl.cf)
        goto L_480806;
    {
        uint32_t r = lift_add(32, esp, 0x24u, &fl);
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
}

uint32_t lifted_palette_cube(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PALETTE_CUBE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PALETTE_CUBE_STACK, 0, entry);
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
    edi = eax;
    edx = edx ^ edx;
    lift_store(&env, esp, 0x10u, 4, edx);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0x10u, 1)) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_shl(8, a, 0x3u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, esp, 0xcu, 4, edx);
    lift_store(&env, esp, 0x14u, 1, (eax & 0xffu));
    ebp = 0x4u;
L_480cc5:
    eax = lift_load(&env, esp, 0xcu, 4);
    ebx = ebx ^ ebx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x14u, 1)) & 0xffu);
    lift_store(&env, esp, 0x4u, 4, ebx);
    lift_store(&env, esp, 0x0u, 4, eax);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, esp, 0x4u, 1)) & 0xffu) << 8);
    lift_store(&env, esp, 0x8u, 4, ebx);
    {
        uint32_t a = ((ecx >> 8) & 0xffu);
        uint32_t r = lift_shl(8, a, 0x3u, &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
L_480ce1:
    esi = lift_load(&env, esp, 0x0u, 4);
    ebx = (ebx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu)) & 0xffu) << 8);
    eax = eax ^ eax;
    edx = lift_load(&env, esp, 0x8u, 4);
    ebx = (ebx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    esi = esi | edx;
    {
        uint32_t a = (ebx & 0xffu);
        uint32_t r = lift_shl(8, a, 0x4u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
L_480cf3:
    edx = esi;
    edx = edx | eax;
    edx = (edx + (edx * 2u));
    lift_store(&env, edx, edi + 0x0u, 1, (ecx & 0xffu));
    lift_store(&env, edx, edi + 0x1u, 1, ((ebx >> 8) & 0xffu));
    eax = eax + 1u;
    lift_store(&env, edx, edi + 0x2u, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) + 0x10u) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.cf)
        goto L_480cf3;
    ebx = lift_load(&env, esp, 0x8u, 4);
    esi = lift_load(&env, esp, 0x4u, 4);
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + 0x8u) & 0xffu) << 8);
    ebx = ebx + ebp;
    esi = esi + 1u;
    lift_store(&env, esp, 0x8u, 4, ebx);
    lift_store(&env, esp, 0x4u, 4, esi);
    {
        (void)lift_sub(32, esi, 0x8u, &fl);
    }
    if (fl.cf)
        goto L_480ce1;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esp, 0x14u, 1)) & 0xffu) << 8);
    edx = lift_load(&env, esp, 0xcu, 4);
    ecx = lift_load(&env, esp, 0x10u, 4);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) + 0x8u) & 0xffu) << 8);
    edx = edx + 0x20u;
    ecx = ecx + 1u;
    lift_store(&env, esp, 0x14u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, esp, 0xcu, 4, edx);
    lift_store(&env, esp, 0x10u, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0x8u, &fl);
    }
    if (fl.cf)
        goto L_480cc5;
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
}

uint32_t lifted_f484520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F484520_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F484520_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, eax, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f486e20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F486E20_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F486E20_STACK, 0, entry);
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
    ecx = lift_load(&env, 0u, 0x558c7cu, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_486ea0;
L_486e34:
    ebx = lift_load(&env, 0u, 0x558c84u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_486e45;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4872b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_486e45:
    eax = lift_load(&env, esi, 0x60u, 4);
    {
        uint32_t v = 0x8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_486ea9;
L_486e50:
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x50u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_486e6c;
    ebx = 0x5106a7u;
    edx = 0x1u;
    ecx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_486e6c:
    edi = lift_load(&env, esi, 0x6cu, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_486e80;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, edi, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x6cu, 4, 0x0u);
L_486e80:
    eax = lift_load(&env, esi, 0x64u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_486e94;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x64u, 4, 0x0u);
L_486e94:
    edx = lift_load(&env, esi, 0x60u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_486eae;
    {
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
L_486ea0:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4872b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_486e34;
L_486ea9:
    edx = lift_load(&env, edx, 0x1cu, 4);
    goto L_486e50;
L_486eae:
    eax = edx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, edx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4cu, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, esi, 0x60u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x60u, 4, 0x0u);
    {
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x483060u, eax, edx, ebx, ecx, 8, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f488c50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F488C50_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F488C50_STACK, 0, entry);
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
    esp = esp - 0x4cu;
    esi = eax;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    eax = (ebp + 0xffffffb8u);
    edx = 0x4ec1ecu;
    ecx = 0x517038u;
    edi = 0x3u;
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
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffc8u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffbcu, 4, edx);
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffc4u, 4, ebx);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) & 0xfeu) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    lift_store(&env, ebp, 0xffffffc8u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, ebp, 0xffffffdcu, 1, (edx & 0xffu));
    eax = (ebp + 0xffffffa4u);
    edx = 0x517494u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffb4u);
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x4u;
    edi = 0x1u;
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    lift_store(&env, ebp, 0xffffffacu, 4, ebx);
    ebx = 0xffffffffu;
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    edx = edx ^ edx;
    eax = (ebp + 0xffffffb4u);
    lift_store(&env, ebp, 0xffffffb0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    ecx = (ebp + 0xffffffa4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    ebx = 0x8000u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = esi;
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x28u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_488d51;
    edi = 0x1u;
L_488cff:
    ecx = 0x517494u;
    eax = (ebp + 0xffffffa4u);
    ebx = 0x8u;
    esi = 0x517454u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffa4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    lift_store(&env, ebp, 0xffffffdcu, 1, (edx & 0xffu));
    eax = (ebp + 0xffffffb4u);
    lift_store(&env, ebp, 0xffffffc4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edx = (ebp + 0xffffffa4u);
    lift_store(&env, ebp, 0xffffffd0u, 1, (eax & 0xffu));
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, esi);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    env.chain = eax;
    eax = edi;
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
L_488d51:
    edx = (ebp + 0xffffffa4u);
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x488d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc4u, 4, 0x1u);
    goto L_488cff;
}

uint32_t lifted_f48ac10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48AC10_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48AC10_STACK, 0, entry);
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
    esp = esp - 0xc8u;
    ecx = lift_load(&env, eax, 0x0u, 4);
    ebx = ecx;
    edx = (ebp + 0xffffff2cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = (ecx + 0x84u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9f45u, eax, edx, ebx, ecx, 0, esp);
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
}

uint32_t lifted_f491050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F491050_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F491050_STACK, 0, entry);
    esp = esp - 0x4u;
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
    eax = lift_load(&env, 0u, 0x5bb764u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx & 0xfc0000u;
    edx = edx & 0xfc00u;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = eax & 0xfcu;
    edx = edx | ecx;
    eax = eax | edx;
    edx = lift_load(&env, 0u, 0x54b800u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = lift_load(&env, edx, (eax * 4u) + 0x0u, 4);
    lift_store(&env, 0u, 0x54d5d4u, 4, eax);
    eax = eax ^ eax;
    edx = lift_load(&env, 0u, 0x54cdc8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x54d5d4u, 1)) & 0xffu);
    eax = lift_load(&env, edx, (eax * 4u) + 0x0u, 4);
    lift_store(&env, 0u, 0x54d5d0u, 4, eax);
    eax = lift_load(&env, 0u, 0x54d5d4u, 4);
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        eax = r;
    }
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5dcu, 2)) & 0xffffu);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x54d5d0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x0u, 1)) & 0xffu);
    ebx = lift_load(&env, 0u, 0x54d5d4u, 4);
    ecx = ecx ^ ecx;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ebx = r;
    }
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5deu, 2)) & 0xffffu);
    ecx = ecx + ebx;
    edx = edx & 0xffu;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ecx = r;
    }
    edx = edx | ecx;
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5d4u, 2)) & 0xffffu);
    ebx = ebx ^ ebx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | (((ecx & 0xffu)) & 0xffu);
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5e0u, 2)) & 0xffffu);
    ecx = ecx + ebx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        ecx = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    ecx = ecx | edx;
    edx = lift_load(&env, 0u, 0x5bb768u, 4);
    lift_store(&env, edx, 0x0u, 4, ecx);
    ebx = lift_load(&env, edx, 0x0u, 4);
    ecx = ecx & 0xfc0000u;
    ebx = ebx & 0xfc00u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ebx = r;
    }
    ecx = ecx | ebx;
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx & 0xfcu;
    ebx = ebx | ecx;
    ecx = lift_load(&env, 0u, 0x54b804u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ebx = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, ebx + 0x0u, 1)) & 0xffu);
    ebx = lift_load(&env, 0u, 0x54cdccu, 4);
    ecx = ecx & 0xffu;
    ecx = lift_load(&env, ebx, (ecx * 4u) + 0x0u, 4);
    ecx = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, 0u, 0x54d5d4u, 4, ecx);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        ecx = r;
    }
    ecx = ecx & 0xffu;
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    ecx = lift_load(&env, 0u, 0x54d5d4u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ecx = r;
    }
    lift_store(&env, esp, 0xcu, 4, ecx);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        ebx = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0xcu, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ecx = r;
    }
    ebx = ebx | ecx;
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5d4u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ecx = r;
    }
    ecx = ecx & 0xffu;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    eax = eax & 0xffu;
    eax = eax | ebx;
    lift_store(&env, edx, 0x0u, 4, eax);
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
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_render_sample32(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RENDER_SAMPLE32_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RENDER_SAMPLE32_STACK, 0, entry);
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
    ebx = lift_load(&env, 0u, 0x5bb770u, 4);
    esi = lift_load(&env, 0u, 0x5bb76cu, 4);
    ecx = eax;
L_492903:
    eax = lift_load(&env, 0u, 0x5bb7d4u, 4);
    edx = edx ^ edx;
    edi = lift_load(&env, 0u, 0x5bb7c0u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edx, edi, &fl);
        edx = r;
    }
    eax = eax + 1u;
    lift_store(&env, 0u, 0x5bb7d4u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb7c4u, 4);
    ebx = ebx + eax;
    eax = lift_load(&env, 0u, 0x5bb7d8u, 4);
    lift_store(&env, 0u, 0x5bb770u, 4, ebx);
    lift_store(&env, 0u, 0x5bb7dcu, 4, eax);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    esi = esi + edx;
    lift_store(&env, 0u, 0x5bc016u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb76cu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ecx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x5bb76cu, 4);
    ebx = lift_load(&env, 0u, 0x5bb770u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb764u, 4, esi);
    lift_store(&env, 0u, 0x5bb768u, 4, ebx);
    {
        uint32_t a = (edx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edx = (edx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb752u, 2, (edx & 0xffffu));
    if (!fl.zf)
        goto L_492903;
    {
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

uint32_t lifted_f492a70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F492A70_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F492A70_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_load(&env, 0u, 0x5bb750u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, 0u, 0x5bb7d4u, 4);
    edx = (eax + 0xfffffffeu);
    ecx = ecx + edx;
    edx = edx ^ edx;
    esi = lift_load(&env, 0u, 0x5bb7c0u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7e0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, edx, esi, &fl);
        edx = r;
    }
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb7d4u, 4, ecx);
    ecx = lift_load(&env, 0u, 0x5bb7c4u, 4);
    {
        uint32_t r = lift_imul(32, ecx, eax, &fl);
        ecx = r;
    }
    edi = lift_load(&env, 0u, 0x5bb764u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    edi = edi + edx;
    edx = lift_load(&env, 0u, 0x5bb770u, 4);
    edx = edx + ecx;
    lift_store(&env, 0u, 0x5bb770u, 4, edx);
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
    edx = lift_load(&env, 0u, 0x5bb7e8u, 4);
    esi = 0x5bb7ecu;
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb764u, 4, edi);
    lift_store(&env, 0u, 0x5bb7e8u, 4, edx);
L_492aea:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, esi, 0x0u, 2)) & 0xffffu);
    edx = esi;
    eax = eax - ecx;
    lift_store(&env, 0u, 0x5bbfecu, 4, esi);
    lift_store(&env, 0u, 0x5bc016u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x5bb7d8u, 4);
    edx = edx ^ esi;
    ecx = lift_load(&env, 0u, 0x5bb764u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = eax + 1u;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x5bb7d8u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb7d4u, 4);
    ecx = ecx + edx;
    edx = lift_load(&env, 0u, 0x5bb770u, 4);
    lift_store(&env, 0u, 0x5bb76cu, 4, ecx);
    lift_store(&env, 0u, 0x5bb7dcu, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb7e8u, 4);
    lift_store(&env, 0u, 0x5bb768u, 4, edx);
    lift_store(&env, 0u, 0x5bb7e4u, 4, eax);
    edx = edx + 0x4u;
    eax = eax + 1u;
    lift_store(&env, 0u, 0x5bb770u, 4, edx);
    lift_store(&env, 0u, 0x5bb7e8u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x5bbfecu, 4);
    eax = lift_load(&env, 0u, 0x5bb76cu, 4);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb764u, 4, eax);
    {
        uint32_t r = lift_add(32, esi, 0x2u, &fl);
        esi = r;
    }
    {
        uint32_t a = (edi & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb750u, 2, (edi & 0xffffu));
    if (!fl.zf)
        goto L_492aea;
    lift_store(&env, 0u, 0x5bbfecu, 4, esi);
    {
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

uint32_t lifted_f49a600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F49A600_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F49A600_STACK, 0, entry);
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
    ebx = lift_load(&env, 0u, 0x5bb784u, 4);
    esi = lift_load(&env, 0u, 0x5bb76cu, 4);
    ecx = eax;
L_49a613:
    eax = lift_load(&env, 0u, 0x5bb7d4u, 4);
    edx = edx ^ edx;
    edi = lift_load(&env, 0u, 0x5bb7c0u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edx, edi, &fl);
        edx = r;
    }
    eax = eax + 1u;
    lift_store(&env, 0u, 0x5bb7d4u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb7c4u, 4);
    ebx = ebx + eax;
    eax = lift_load(&env, 0u, 0x5bb7d8u, 4);
    lift_store(&env, 0u, 0x5bb784u, 4, ebx);
    lift_store(&env, 0u, 0x5bb7dcu, 4, eax);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    esi = esi + edx;
    lift_store(&env, 0u, 0x5bc016u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb76cu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ecx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x5bb76cu, 4);
    ebx = lift_load(&env, 0u, 0x5bb784u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb764u, 4, esi);
    lift_store(&env, 0u, 0x5bb780u, 4, ebx);
    {
        uint32_t a = (edx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edx = (edx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb752u, 2, (edx & 0xffffu));
    if (!fl.zf)
        goto L_49a613;
    {
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

uint32_t lifted_f49a780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F49A780_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F49A780_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_load(&env, 0u, 0x5bb750u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, 0u, 0x5bb7d4u, 4);
    edx = (eax + 0xfffffffeu);
    ecx = ecx + edx;
    edx = edx ^ edx;
    esi = lift_load(&env, 0u, 0x5bb7c0u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7e0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, edx, esi, &fl);
        edx = r;
    }
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb7d4u, 4, ecx);
    ecx = lift_load(&env, 0u, 0x5bb7c4u, 4);
    {
        uint32_t r = lift_imul(32, ecx, eax, &fl);
        ecx = r;
    }
    edi = lift_load(&env, 0u, 0x5bb764u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    edi = edi + edx;
    edx = lift_load(&env, 0u, 0x5bb784u, 4);
    edx = edx + ecx;
    lift_store(&env, 0u, 0x5bb784u, 4, edx);
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
    edx = lift_load(&env, 0u, 0x5bb7e8u, 4);
    esi = 0x5bb7ecu;
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb764u, 4, edi);
    lift_store(&env, 0u, 0x5bb7e8u, 4, edx);
L_49a7fa:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, esi, 0x0u, 2)) & 0xffffu);
    edx = esi;
    eax = eax - ecx;
    lift_store(&env, 0u, 0x5bbfecu, 4, esi);
    lift_store(&env, 0u, 0x5bc016u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x5bb7d8u, 4);
    edx = edx ^ esi;
    ecx = lift_load(&env, 0u, 0x5bb764u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = eax + 1u;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x5bb7d8u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb7d4u, 4);
    ecx = ecx + edx;
    edx = lift_load(&env, 0u, 0x5bb784u, 4);
    lift_store(&env, 0u, 0x5bb76cu, 4, ecx);
    lift_store(&env, 0u, 0x5bb7dcu, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb7e8u, 4);
    lift_store(&env, 0u, 0x5bb780u, 4, edx);
    lift_store(&env, 0u, 0x5bb7e4u, 4, eax);
    edx = edx + 0x2u;
    eax = eax + 1u;
    lift_store(&env, 0u, 0x5bb784u, 4, edx);
    lift_store(&env, 0u, 0x5bb7e8u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x5bbfecu, 4);
    eax = lift_load(&env, 0u, 0x5bb76cu, 4);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb764u, 4, eax);
    {
        uint32_t r = lift_add(32, esi, 0x2u, &fl);
        esi = r;
    }
    {
        uint32_t a = (edi & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb750u, 2, (edi & 0xffffu));
    if (!fl.zf)
        goto L_49a7fa;
    lift_store(&env, 0u, 0x5bbfecu, 4, esi);
    {
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

uint32_t lifted_f4a2650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4A2650_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4A2650_STACK, 0, entry);
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
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    ecx = eax;
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4a26b0;
L_4a2661:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb752u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bc016u, 2, (eax & 0xffffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ecx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x5bb79cu, 4);
    edx = lift_load(&env, 0u, 0x5bb764u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x5bb7c8u, 4);
    lift_store(&env, 0u, 0x5bb764u, 4, edx);
    edx = lift_load(&env, 0u, 0x5bb780u, 4);
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb780u, 4, edx);
    {
        uint32_t a = (ebx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ebx = (ebx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4a2661;
L_4a26b0:
    lift_store(&env, 0u, 0x5bb752u, 2, (ebx & 0xffffu));
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

uint32_t lifted_f4a26c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4A26C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4A26C0_STACK, 0, entry);
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
    ebx = lift_load(&env, 0u, 0x5bb784u, 4);
    esi = lift_load(&env, 0u, 0x5bb76cu, 4);
    ecx = eax;
L_4a26d3:
    eax = lift_load(&env, 0u, 0x5bb7d4u, 4);
    edx = edx ^ edx;
    edi = lift_load(&env, 0u, 0x5bb7c0u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edx, edi, &fl);
        edx = r;
    }
    eax = eax + 1u;
    lift_store(&env, 0u, 0x5bb7d4u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb7c4u, 4);
    ebx = ebx + eax;
    eax = lift_load(&env, 0u, 0x5bb7d8u, 4);
    lift_store(&env, 0u, 0x5bb784u, 4, ebx);
    lift_store(&env, 0u, 0x5bb7dcu, 4, eax);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    esi = esi + edx;
    lift_store(&env, 0u, 0x5bc016u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb76cu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ecx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x5bb76cu, 4);
    ebx = lift_load(&env, 0u, 0x5bb784u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb764u, 4, esi);
    lift_store(&env, 0u, 0x5bb780u, 4, ebx);
    {
        uint32_t a = (edx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edx = (edx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb752u, 2, (edx & 0xffffu));
    if (!fl.zf)
        goto L_4a26d3;
    {
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

uint32_t lifted_f4a2840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4A2840_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4A2840_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_load(&env, 0u, 0x5bb750u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, 0u, 0x5bb7d4u, 4);
    edx = (eax + 0xfffffffeu);
    ecx = ecx + edx;
    edx = edx ^ edx;
    esi = lift_load(&env, 0u, 0x5bb7c0u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7e0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, edx, esi, &fl);
        edx = r;
    }
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb7d4u, 4, ecx);
    ecx = lift_load(&env, 0u, 0x5bb7c4u, 4);
    {
        uint32_t r = lift_imul(32, ecx, eax, &fl);
        ecx = r;
    }
    edi = lift_load(&env, 0u, 0x5bb764u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    edi = edi + edx;
    edx = lift_load(&env, 0u, 0x5bb784u, 4);
    edx = edx + ecx;
    lift_store(&env, 0u, 0x5bb784u, 4, edx);
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
    edx = lift_load(&env, 0u, 0x5bb7e8u, 4);
    esi = 0x5bb7ecu;
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb764u, 4, edi);
    lift_store(&env, 0u, 0x5bb7e8u, 4, edx);
L_4a28ba:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, esi, 0x0u, 2)) & 0xffffu);
    edx = esi;
    eax = eax - ecx;
    lift_store(&env, 0u, 0x5bbfecu, 4, esi);
    lift_store(&env, 0u, 0x5bc016u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x5bb7d8u, 4);
    edx = edx ^ esi;
    ecx = lift_load(&env, 0u, 0x5bb764u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = eax + 1u;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x5bb7d8u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb7d4u, 4);
    ecx = ecx + edx;
    edx = lift_load(&env, 0u, 0x5bb784u, 4);
    lift_store(&env, 0u, 0x5bb76cu, 4, ecx);
    lift_store(&env, 0u, 0x5bb7dcu, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb7e8u, 4);
    lift_store(&env, 0u, 0x5bb780u, 4, edx);
    lift_store(&env, 0u, 0x5bb7e4u, 4, eax);
    edx = edx + 0x2u;
    eax = eax + 1u;
    lift_store(&env, 0u, 0x5bb784u, 4, edx);
    lift_store(&env, 0u, 0x5bb7e8u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x5bbfecu, 4);
    eax = lift_load(&env, 0u, 0x5bb76cu, 4);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb764u, 4, eax);
    {
        uint32_t r = lift_add(32, esi, 0x2u, &fl);
        esi = r;
    }
    {
        uint32_t a = (edi & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb750u, 2, (edi & 0xffffu));
    if (!fl.zf)
        goto L_4a28ba;
    lift_store(&env, 0u, 0x5bbfecu, 4, esi);
    {
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

uint32_t lifted_f4a9140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4A9140_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4A9140_STACK, 0, entry);
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
    edx = lift_load(&env, 0u, 0x5bb778u, 4);
    eax = lift_load(&env, 0u, 0x5bb764u, 4);
    ebx = lift_load(&env, eax, 0x0u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    esi = lift_load(&env, eax, 0x0u, 4);
    ebx = ebx & 0xfc0000u;
    ecx = ecx & 0xfc00u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        ebx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    esi = esi & 0xfcu;
    ecx = ecx | ebx;
    esi = esi | ecx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        esi = r;
    }
    ecx = lift_load(&env, 0u, 0x54b800u, 4);
    lift_store(&env, 0u, 0x54d5e4u, 4, esi);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, (esi * 4u) + 0x0u, 1)) & 0xffu);
    ecx = lift_load(&env, 0u, 0x54cdc8u, 4);
    eax = eax & 0xffu;
    eax = lift_load(&env, ecx, (eax * 4u) + 0x0u, 4);
    lift_store(&env, 0u, 0x54d5d0u, 4, eax);
    eax = lift_load(&env, 0u, 0x54b804u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, eax + 0x0u, 1)) & 0xffu);
    eax = eax & 0xffu;
    ecx = ((eax * 4u));
    eax = lift_load(&env, 0u, 0x54cdccu, 4);
    eax = lift_load(&env, ecx, eax + 0x0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx ^ ecx;
    lift_store(&env, 0u, 0x54d5d4u, 4, eax);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = lift_load(&env, 0u, 0x54d5d0u, 4);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    ebx = ecx;
    ebx = ebx & 0xffu;
    ecx = lift_load(&env, 0u, 0x54d5d4u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ecx = r;
    }
    ecx = ecx & 0xffu;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ecx = r;
    }
    ebx = ebx | ecx;
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5d4u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ecx = r;
    }
    ecx = ecx & 0xffu;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    eax = eax & 0xffu;
    ebx = ebx | eax;
    eax = ebx;
    {
        uint32_t a = eax;
        eax = (~a) & lift_mask(4);
    }
    ecx = eax;
    lift_store(&env, 0u, 0x5bc018u, 4, ebx);
    ecx = ecx & 0xffffffu;
    ebx = eax;
    lift_store(&env, 0u, 0x5bb774u, 4, ecx);
    ecx = eax;
    ebx = ebx & 0xe00000u;
    ecx = ecx & 0xe000u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0xau, &fl);
        ebx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x5u, &fl);
        ecx = r;
    }
    eax = eax & 0xc0u;
    ecx = ecx | ebx;
    eax = eax | ecx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        eax = r;
    }
    lift_store(&env, edx, 0x0u, 1, (eax & 0xffu));
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

uint32_t lifted_f4aa3c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4AA3C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4AA3C0_STACK, 0, entry);
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
    ebx = lift_load(&env, 0u, 0x5bb77cu, 4);
    esi = lift_load(&env, 0u, 0x5bb76cu, 4);
    ecx = eax;
L_4aa3d3:
    eax = lift_load(&env, 0u, 0x5bb7d4u, 4);
    edx = edx ^ edx;
    edi = lift_load(&env, 0u, 0x5bb7c0u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edx, edi, &fl);
        edx = r;
    }
    eax = eax + 1u;
    lift_store(&env, 0u, 0x5bb7d4u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb7c4u, 4);
    ebx = ebx + eax;
    eax = lift_load(&env, 0u, 0x5bb7d8u, 4);
    lift_store(&env, 0u, 0x5bb77cu, 4, ebx);
    lift_store(&env, 0u, 0x5bb7dcu, 4, eax);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    esi = esi + edx;
    lift_store(&env, 0u, 0x5bc016u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb76cu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ecx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x5bb76cu, 4);
    ebx = lift_load(&env, 0u, 0x5bb77cu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb764u, 4, esi);
    lift_store(&env, 0u, 0x5bb778u, 4, ebx);
    {
        uint32_t a = (edx & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edx = (edx & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb752u, 2, (edx & 0xffffu));
    if (!fl.zf)
        goto L_4aa3d3;
    {
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

uint32_t lifted_f4aa540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4AA540_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4AA540_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_load(&env, 0u, 0x5bb750u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, 0u, 0x5bb7d4u, 4);
    edx = (eax + 0xfffffffeu);
    ecx = ecx + edx;
    edx = edx ^ edx;
    esi = lift_load(&env, 0u, 0x5bb7c0u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7e0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, edx, esi, &fl);
        edx = r;
    }
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb7d4u, 4, ecx);
    ecx = lift_load(&env, 0u, 0x5bb7c4u, 4);
    {
        uint32_t r = lift_imul(32, ecx, eax, &fl);
        ecx = r;
    }
    edi = lift_load(&env, 0u, 0x5bb764u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    edi = edi + edx;
    edx = lift_load(&env, 0u, 0x5bb77cu, 4);
    edx = edx + ecx;
    lift_store(&env, 0u, 0x5bb77cu, 4, edx);
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
    edx = lift_load(&env, 0u, 0x5bb7e8u, 4);
    esi = 0x5bb7ecu;
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb764u, 4, edi);
    lift_store(&env, 0u, 0x5bb7e8u, 4, edx);
L_4aa5ba:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb752u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, esi, 0x0u, 2)) & 0xffffu);
    edx = esi;
    eax = eax - ecx;
    lift_store(&env, 0u, 0x5bbfecu, 4, esi);
    lift_store(&env, 0u, 0x5bc016u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x5bb7d8u, 4);
    edx = edx ^ esi;
    ecx = lift_load(&env, 0u, 0x5bb764u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = eax + 1u;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x5bb7d8u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb7d4u, 4);
    ecx = ecx + edx;
    edx = lift_load(&env, 0u, 0x5bb77cu, 4);
    lift_store(&env, 0u, 0x5bb76cu, 4, ecx);
    lift_store(&env, 0u, 0x5bb7dcu, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb7e8u, 4);
    lift_store(&env, 0u, 0x5bb778u, 4, edx);
    lift_store(&env, 0u, 0x5bb7e4u, 4, eax);
    edx = edx + 1u;
    eax = eax + 1u;
    lift_store(&env, 0u, 0x5bb77cu, 4, edx);
    lift_store(&env, 0u, 0x5bb7e8u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x5bbfecu, 4);
    eax = lift_load(&env, 0u, 0x5bb76cu, 4);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb764u, 4, eax);
    {
        uint32_t r = lift_add(32, esi, 0x2u, &fl);
        esi = r;
    }
    {
        uint32_t a = (edi & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    lift_store(&env, 0u, 0x5bb750u, 2, (edi & 0xffffu));
    if (!fl.zf)
        goto L_4aa5ba;
    lift_store(&env, 0u, 0x5bbfecu, 4, esi);
    {
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cd8b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CD8B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CD8B0_STACK, 0, entry);
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
    esp = esp - 0x14u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = edx;
    edi = ebx;
    lift_store(&env, edx, 0x4u, 4, ebx);
    eax = lift_load(&env, ebx, 0x8u, 4);
    lift_store(&env, edx, 0x8u, 4, eax);
    eax = (esp + 0x4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0b7cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0x0u, 4);
    lift_store(&env, esp, 0xcu, 4, eax);
    eax = (esp + 0x4u);
    lift_store(&env, esp, 0x11u, 1, lift_load(&env, esp, 0x11u, 1) | 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd7dcu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x14u, 4, eax);
    goto L_4cd95e;
L_4cd8ec:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4cd8f1:
    eax = lift_load(&env, esi, 0x4u, 4);
    ebx = lift_load(&env, esi, 0xcu, 4);
    edx = lift_load(&env, esi, 0x8u, 4);
L_4cd8fa:
    eax = lift_load(&env, edi, eax + 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cea15u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4cd95e;
L_4cd904:
    ebx = (esi + 0xffffffffu);
    edx = edi;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd836u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4cd95e;
L_4cd912:
    ebx = esi;
    edx = edi;
    eax = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd847u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4cd95e;
L_4cd91f:
    ecx = 0x11u;
L_4cd924:
    edx = 0x1u;
    ebx = ebp;
    eax = esi;
L_4cd92d:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd819u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4cd95e;
L_4cd934:
    ecx = 0x10u;
    goto L_4cd924;
L_4cd93b:
    ecx = 0x10u;
    ebx = ebp;
    eax = esi;
    edx = edx ^ edx;
    goto L_4cd92d;
L_4cd948:
    eax = lift_load(&env, esi, 0x4u, 4);
    ebx = lift_load(&env, edi, eax + 0x4u, 4);
    edx = lift_load(&env, edi, eax + 0x8u, 4);
    goto L_4cd8fa;
L_4cd955:
    eax = lift_load(&env, esi, 0x4u, 4);
L_4cd958:
    eax = lift_load(&env, edi, eax + 0x0u, 4);
L_4cd95b:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4cd95e:
    eax = lift_load(&env, esp, 0x8u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x0u, 4), &fl);
    }
    if (fl.zf)
        goto L_4cd9e5;
    if (!fl.cf)
        goto L_4cd972;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4cd972:
    eax = (esp + 0x4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0b9eu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (esp + 0x4u);
    esi = lift_load(&env, esp, 0x14u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd7dcu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x14u, 4, eax);
    eax = lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, edi, 0xcu, 4, eax);
    ebx = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4cd9d7;
    esi = lift_load(&env, esi, 0x4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x10u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4cd8ec;
    eax = (eax & 0xffu);
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4cd8f1;
            case 1:
                goto L_4cd8ec;
            case 2:
                goto L_4cd95e;
            case 3:
                goto L_4cd904;
            case 4:
                goto L_4cd912;
            case 5:
                goto L_4cd8ec;
            case 6:
                goto L_4cd91f;
            case 7:
                goto L_4cd934;
            case 8:
                goto L_4cd93b;
            case 9:
                goto L_4cd948;
            case 10:
                goto L_4cd955;
            case 11:
                goto L_4cd9bb;
            case 12:
                goto L_4cd9b0;
            case 13:
                goto L_4cd9c3;
            case 14:
                goto L_4cd8ec;
            case 15:
                goto L_4cd934;
            case 16:
                goto L_4cd934;
            default:
                return 0u;
        }
    }
L_4cd9b0:
    eax = lift_load(&env, esi, 0x4u, 4);
    eax = lift_load(&env, edi, eax + 0x0u, 4);
    eax = eax - 0x4u;
    goto L_4cd95b;
L_4cd9bb:
    eax = lift_load(&env, esi, 0x4u, 4);
    edx = lift_load(&env, esi, 0xcu, 4);
    goto L_4cd958;
L_4cd9c3:
    eax = lift_load(&env, esi, 0x4u, 4);
    eax = lift_load(&env, edi, eax + 0x0u, 4);
    eax = eax - 0x4u;
    edx = lift_load(&env, esi, 0xcu, 4);
    {
        uint32_t r = lift_imul(32, edx, lift_load(&env, eax, 0x0u, 4), &fl);
        edx = r;
    }
    edx = edx + 0x4u;
    goto L_4cd95b;
L_4cd9d7:
    eax = lift_load(&env, esi, 0x4u, 4);
    edx = edx ^ edx;
    eax = eax + edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4cd95e;
L_4cd9e5:
    lift_store(&env, edi, 0xcu, 4, eax);
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
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ce780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CE780_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CE780_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4ce7a0u;
    eax = eax + 0x1038u;
    goto L_4dbf80;
L_4dbf80:
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
    ebx = eax;
    esi = edx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbfba;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c77a8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbfae;
    eax = 0x5c7770u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dbfa9;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbac0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dbfa9:
    lift_store(&env, 0u, 0x5c77a8u, 4, eax);
L_4dbfae:
    eax = lift_load(&env, 0u, 0x5c77a8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbb30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
L_4dbfba:
    eax = lift_load(&env, 0u, 0x5c77a8u, 4);
    {
        uint32_t v = lift_load(&env, eax, 0x0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1cdcu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dbfd3;
    {
        (void)lift_sub(32, edi, lift_load(&env, eax, 0x8u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dbfd7;
L_4dbfd3:
    eax = eax ^ eax;
    goto L_4dbfdd;
L_4dbfd7:
    eax = lift_load(&env, eax, 0xcu, 4);
    eax = lift_load(&env, eax, (edi * 4u) + 0x0u, 4);
L_4dbfdd:
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dbff8;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, esi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x5c77a8u, 4);
    ecx = eax;
    edx = lift_load(&env, ebx, 0x0u, 4);
    ebx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbd20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dbff8:
    eax = ecx;
    {
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
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e6250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6250_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6250_STACK, 0, entry);
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
    esp = esp - 0x4u;
    edi = eax;
    esi = edx;
    edx = edx ^ edx;
    goto L_4e6260;
L_4e625f:
    edx = edx + 1u;
L_4e6260:
    ebx = eax;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    eax = eax + 1u;
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4e625f;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x507c8cu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x8u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1d08u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = esi;
    goto L_4e078c;
}

uint32_t lifted_f4e6d16(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6D16_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6D16_STACK, 0, entry);
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
    esp = esp - 0x60u;
    ebp = eax;
    edx = (esp + 0x54u);
    eax = esp;
    lift_store(&env, esp, 0x54u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6cf2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi ^ edi;
    esi = esi ^ esi;
    lift_store(&env, esp, 0x38u, 4, 0xe5671234u);
    lift_store(&env, esp, 0x3cu, 4, 0x0u);
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    lift_store(&env, esp, 0x44u, 4, 0x0u);
    lift_store(&env, esp, 0x48u, 4, 0x2u);
    eax = esp;
    lift_store(&env, esp, 0x4cu, 4, 0x0u);
    lift_store(&env, esp, 0x50u, 4, eax);
    eax = env.chain;
    ebx = eax;
L_4e6d76:
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e6d9c;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e6d8d;
    esi = lift_load(&env, esp, 0x8u, 4);
    esi = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4e6e06;
L_4e6d8d:
    eax = esi;
    lift_store(&env, ebp, 0x0u, 4, edi);
    {
        uint32_t r = lift_add(32, esp, 0x60u, &fl);
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
L_4e6d9c:
    eax = lift_load(&env, ebx, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6cd4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, eax, 0x5u, 1);
    {
        (void)lift_sub(32, edx, 0x57u, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
    edx = lift_load(&env, eax, 0x6u, 1);
    {
        (void)lift_sub(32, edx, 0x41u, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
    edx = lift_load(&env, eax, 0x7u, 1);
    {
        (void)lift_sub(32, edx, 0x54u, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
    edx = lift_load(&env, eax, 0x8u, 1);
    {
        (void)lift_sub(32, edx, 0x43u, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
    edx = lift_load(&env, eax, 0x9u, 1);
    {
        (void)lift_sub(32, edx, 0x4fu, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
    eax = lift_load(&env, eax, 0xau, 1);
    {
        (void)lift_sub(32, eax, 0x4du, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
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
    eax = (esp + 0x44u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0x10u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e6dff;
    eax = lift_load(&env, esp, 0x8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edi = ebx;
    {
        (void)lift_and(8, lift_load(&env, eax, 0x4u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e6dff;
    esi = eax;
L_4e6dff:
    ebx = lift_load(&env, ebx, 0x0u, 4);
    goto L_4e6d76;
L_4e6e06:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x5c5c54u, 4);
    esi = esi + eax;
    goto L_4e6d8d;
}
