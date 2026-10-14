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
