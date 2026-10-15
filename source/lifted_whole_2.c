/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_2.h"

uint32_t lifted_f44dbb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F44DBB0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F44DBB0_STACK, 0, entry);
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
    lift_store(&env, eax, 0x95u, 1, 0x4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac1f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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
        goto L_44dbe1;
L_44dbd5:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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
L_44dbe1:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    esi = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ebx;
    lift_store(&env, ecx, 0x45u, 1, 0x10u);
    eax = ecx;
    lift_store(&env, ecx, 0x46u, 2, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4acc10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ebx;
    lift_store(&env, ecx, 0x4au, 2, 0x32u);
    eax = ecx;
    lift_store(&env, ecx, 0x4cu, 2, 0x5u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0x46u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0xfu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_44dc2a;
    lift_store(&env, ecx, 0x52u, 1, 0x1u);
L_44dc2a:
    eax = lift_load(&env, ecx, 0x46u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0x1eu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_44dc39;
    lift_store(&env, ecx, 0x52u, 1, 0x2u);
L_44dc39:
    {
        (void)lift_sub(16, lift_load(&env, ecx, 0x48u, 2), 0x32u, &fl);
    }
    if (!fl.zf)
        goto L_44dc44;
    lift_store(&env, ecx, 0x52u, 1, 0x3u);
L_44dc44:
    edx = esi;
    lift_store(&env, ecx, 0x4fu, 1, 0x0u);
    eax = ecx;
    lift_store(&env, ecx, 0x50u, 2, 0x4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_44dbd5;
    edx = 0x44dc80u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_block_orbit_update(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_BLOCK_ORBIT_UPDATE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_BLOCK_ORBIT_UPDATE_STACK, 0, entry);
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
    esp = esp - 0x1cu;
    esi = eax;
    lift_store(&env, eax, 0x95u, 1, 0x3u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac1f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    edx = 0x5u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_44de65;
L_44de54:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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
L_44de65:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    edi = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x8u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xau, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe8u, 2, (eax & 0xffffu));
    eax = esi;
    ecx = (ebp + 0xffffffd0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffd8u);
    ebx = 0x5u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x30u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad1c0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (eax & 0xffffff00u) | ((0x10u) & 0xffu);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - ((eax >> 8) & 0xffu)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) + (edx & 0xffu)) & 0xffu);
    eax = eax & 0xffu;
    {
        (void)lift_sub(32, eax, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_44dfa3;
L_44dec0:
    edx = (ebp + 0xffffffdcu);
    ebx = ebx ^ ebx;
    ecx = (ecx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    eax = esi;
    ebx = (ebp + 0xffffffe0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe2u, 4);
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = edx - eax;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 2, (edx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffffe6u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx - eax;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 2, (edx & 0xffffu));
    lift_store(&env, esi, 0x18u, 2, (edx & 0xffffu));
    edx = edi;
    lift_store(&env, esi, 0x10u, 2, (eax & 0xffffu));
    eax = esi;
    lift_store(&env, esi, 0x45u, 1, (ecx & 0xffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4aca60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4acab0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4acc10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_44df75;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_44df75;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_44df75;
    edx = 0x44dfb0u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x64u, 4, 0x30u);
    lift_store(&env, esi, 0x6cu, 4, 0x5u);
    lift_store(&env, esi, 0x18u, 2, 0x0u);
    lift_store(&env, esi, 0x12u, 2, 0x6u);
    lift_store(&env, esi, 0x1au, 2, 0x6u);
    lift_store(&env, esi, 0x28u, 2, 0xfu);
    lift_store(&env, esi, 0x4au, 2, 0x64u);
    lift_store(&env, esi, 0x4cu, 2, 0x5u);
L_44df75:
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad6e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_44de54;
    edx = 0x44c860u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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
L_44dfa3:
    eax = 0x10u;
    goto L_44dec0;
}

uint32_t lifted_f44dfb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F44DFB0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F44DFB0_STACK, 0, entry);
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
    edx = 0x5u;
    lift_store(&env, eax, 0x95u, 1, 0x3u);
    ecx = 0x30u;
    lift_store(&env, eax, 0x94u, 1, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac1f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_44e004;
L_44dff3:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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
L_44e004:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    edi = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_44e02c;
    {
        (void)lift_sub(16, lift_load(&env, esi, 0x4au, 2), 0x64u, &fl);
    }
    if (!fl.zf)
        goto L_44e02c;
    lift_store(&env, esi, 0x52u, 1, 0x2u);
L_44e02c:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xau, 2)) & 0xffffu);
    edx = edi;
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4acab0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x16u, 2)) & 0xffffu);
    lift_store(&env, esi, 0xau, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x8u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xau, 2)) & 0xffffu);
    edx = edi;
    lift_store(&env, ebp, 0xffffffe4u, 2, (eax & 0xffffu));
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edi;
    eax = esi;
    ecx = (ebp + 0xffffffc8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffccu);
    edx = lift_load(&env, esi, 0x64u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = edx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad1c0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = edx ^ edx;
    lift_div1(32, ecx, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = (eax & 0xffffff00u) | ((0x10u) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - lift_load(&env, ebp, 0xffffffdcu, 1)) & 0xffu);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu) << 8);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) + (eax & 0xffu)) & 0xffu) << 8);
    lift_store(&env, esi, 0x44u, 1, ((eax >> 8) & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x44u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_44e118;
L_44e0a5:
    ebx = ebx ^ ebx;
    lift_store(&env, esi, 0x44u, 1, (eax & 0xffu));
    edx = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    eax = esi;
    ebx = (ebp + 0xffffffd4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe6u, 4);
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = edx - eax;
    lift_store(&env, esi, 0xeu, 2, (edx & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe2u, 4);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    eax = eax - edx;
    edx = edi;
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad6e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_44e0fb;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_44dff3;
L_44e0fb:
    edx = 0x44c860u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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
L_44e118:
    eax = 0x10u;
    goto L_44e0a5;
}

uint32_t lifted_f44e920(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F44E920_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F44E920_STACK, 0, entry);
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
    esp = esp - 0x8u;
    ecx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac1f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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
        goto L_44e956;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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
L_44e956:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4acc10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_44e97d;
    edx = 0x44e9f0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_44e97d:
    ebx = (ebp + 0xffffffe8u);
    edx = edx ^ edx;
    eax = ecx;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    edx = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x18u;
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, ecx, 0x6u, 4);
    edx = edx - esi;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    eax = eax + edx;
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = 0x18u;
    edi = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ecx, 0x8u, 4);
    eax = eax - edi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    eax = eax + edx;
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    eax = eax ^ eax;
    edx = 0x10u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    edx = edx - eax;
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = eax;
    lift_store(&env, ecx, 0x48u, 2, (eax & 0xffffu));
    edx = 0u - edx;
    lift_store(&env, ecx, 0x48u, 2, (edx & 0xffffu));
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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
}

uint32_t lifted_f44e9f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F44E9F0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F44E9F0_STACK, 0, entry);
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
    esp = esp - 0x8u;
    ecx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac1f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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
        goto L_44ea26;
L_44ea15:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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
L_44ea26:
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
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x8u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0xau, 2)) & 0xffffu);
    edx = ebx;
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4aca60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    edx = ebx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4acab0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    edx = edx ^ edx;
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    ebx = (ebp + 0xffffffe8u);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    eax = ecx;
    edx = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x18u;
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, ecx, 0x6u, 4);
    eax = eax - ebx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    eax = eax + edx;
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = 0x18u;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ecx, 0x8u, 4);
    eax = eax - ebx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    eax = eax + edx;
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_44ea15;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_44ea15;
    edx = 0x44c860u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x45u, 1, 0x10u);
    lift_store(&env, ecx, 0x46u, 2, 0x1u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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
}

uint32_t lifted_f44eaf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F44EAF0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F44EAF0_STACK, 0, entry);
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
    esp = esp - 0x8u;
    ecx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac1f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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
        goto L_44eb26;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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
L_44eb26:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4acc10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_44eb5f;
    edx = 0x44c860u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x93u, 1, 0x0u);
    lift_store(&env, ecx, 0x4eu, 1, 0x32u);
    lift_store(&env, ecx, 0x95u, 1, 0x1u);
L_44eb5f:
    ebx = (ebp + 0xffffffe8u);
    edx = edx ^ edx;
    eax = ecx;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    edx = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x18u;
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, ecx, 0x6u, 4);
    edx = edx - esi;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    eax = eax + edx;
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = 0x18u;
    edi = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ecx, 0x8u, 4);
    eax = eax - edi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    eax = eax + edx;
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    eax = eax ^ eax;
    edx = 0x10u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    edx = edx - eax;
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = eax;
    lift_store(&env, ecx, 0x48u, 2, (eax & 0xffffu));
    edx = 0u - edx;
    lift_store(&env, ecx, 0x48u, 2, (edx & 0xffffu));
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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
}

uint32_t lifted_f450e70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F450E70_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F450E70_STACK, 0, entry);
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
    ecx = eax;
    esi = lift_load(&env, 0u, 0x540f8cu, 4);
    ebx = lift_load(&env, 0u, 0x540f90u, 4);
    edx = edx ^ edx;
    eax = esi;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d3b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_450ed0;
L_450e9a:
    eax = esi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43b860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43b860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43cd30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    edx = 0x450df0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43cd30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
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
L_450ed0:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d3b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_450e9a;
    eax = ecx;
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
        goto L_450eff;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_450e9a;
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
L_450eff:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad6e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_450e9a;
    edi = lift_load(&env, 0u, 0x4f89acu, 4);
    eax = lift_load(&env, ecx, 0x58u, 4);
    {
        uint32_t r = lift_imul(32, eax, edi, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    edi = lift_load(&env, ecx, 0x5cu, 4);
    lift_div1(32, edi, &eax, &edx, &fl);
    edi = eax;
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43b860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edi;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43b860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_450e9a;
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

uint32_t lifted_f450ff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F450FF0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F450FF0_STACK, 0, entry);
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
    ecx = eax;
    esi = eax;
    edi = lift_load(&env, eax, 0x15cu, 4);
    eax = lift_load(&env, eax, 0x3b0u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = lift_load(&env, ecx, 0x3b4u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x4c5u, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_45124a;
    edx = lift_load(&env, edi, 0xa60u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_451260;
L_451033:
    ebx = lift_load(&env, edi, 0xbd8u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4511bb;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ad70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x168u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4510c2;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431100u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4512f3;
    eax = lift_load(&env, esi, 0x4c8u, 4);
    {
        (void)lift_sub(32, eax, 0x2bu, &fl);
    }
    if (!fl.zf)
        goto L_4510af;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x160u, 2)) & 0xffffu);
    eax = 0x54d640u;
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
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x160u, 2)) & 0xffffu);
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476280u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4510af:
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x168u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4510c2:
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x16au, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_45113f;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431140u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4512ff;
    eax = lift_load(&env, esi, 0x4c8u, 4);
    {
        (void)lift_sub(32, eax, 0x2bu, &fl);
    }
    if (!fl.zf)
        goto L_45112c;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x162u, 2)) & 0xffffu);
    eax = 0x54d640u;
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
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = edx ^ edx;
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x162u, 2)) & 0xffffu);
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476280u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_45112c:
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x16au, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_45113f:
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x16cu, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_45118a;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431180u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_451177;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4311a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ad50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_451177:
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x16cu, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_45118a:
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x16eu, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4511bb;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431390u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, esi, 0x16eu, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4511bb:
    edx = lift_load(&env, edi, 0x158u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, edi, 0xa60u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_45138e;
    {
        (void)lift_sub(32, lift_load(&env, edi, 0xbd8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_451333;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x170u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_45130b;
L_4511ed:
    lift_store(&env, esi, 0x184u, 4, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x188u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d3b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, esi, 0x44cu, 4, eax);
    eax = lift_load(&env, esi, 0x4c8u, 4);
    {
        (void)lift_sub(32, eax, 0x23u, &fl);
    }
    if (!fl.zf)
        goto L_451329;
    edx = 0x4513f0u;
L_45122d:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bae0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_451240:
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
L_45124a:
    edx = 0x4513d0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
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
L_451260:
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x16eu, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_451288;
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x16eu, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_451288:
    ecx = (ebp + 0xffffffe4u);
    ebx = (ebp + 0xffffffe8u);
    edx = (ebp + 0xffffffe0u);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43a5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ebp, 0xffffffe5u, 4);
    edx = lift_load(&env, ebp, 0xffffffddu, 4);
    ecx = lift_load(&env, esi, 0x17cu, 4);
    eax = edi;
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffe1u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431d90u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, esi, 0x4c8u, 4);
    {
        (void)lift_sub(32, eax, 0x31u, &fl);
    }
    if (!fl.zf)
        goto L_4512cb;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43b7c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4512cb:
    eax = lift_load(&env, esi, 0x4c8u, 4);
    {
        (void)lift_sub(32, eax, 0x2cu, &fl);
    }
    if (!fl.zf)
        goto L_4512dd;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431fb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4512dd:
    eax = esi;
    lift_store(&env, esi, 0x170u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ad50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_451033;
L_4512f3:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ad50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4510af;
L_4512ff:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ad50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_45112c;
L_45130b:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43a520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x170u, 4, 0x1u);
    goto L_4511ed;
L_451329:
    edx = 0x451690u;
    goto L_45122d;
L_451333:
    eax = esi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bb00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4513d0u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x4c5u, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_451369;
    lift_store(&env, 0u, 0x532a3cu, 4, 0x1u);
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
L_451369:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43acd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f81c8u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43c0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esi, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4713d0u, eax, edx, ebx, ecx, 0, esp);
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
L_45138e:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x170u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_451240;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431d60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_451240;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43a520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43d260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x170u, 4, 0x1u);
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

uint32_t lifted_state_drain_451580(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_STATE_DRAIN_451580_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_STATE_DRAIN_451580_STACK, 0, entry);
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
    ecx = lift_load(&env, eax, 0x15cu, 4);
    ebx = eax;
    eax = ecx;
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
        goto L_4515b8;
L_45159f:
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x838u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4515ee;
    edx = lift_load(&env, ecx, 0x158u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
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
L_4515b8:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
L_4515cc:
    if (fl.cf || fl.zf)
        goto L_45159f;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x838u, 1)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4515df;
L_4515da:
    edx = edx - 1u;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    goto L_4515cc;
L_4515df:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x838u, 1, lift_load(&env, ecx, 0x838u, 1) - 1u);
    goto L_4515da;
L_4515ee:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    edx = 0x451630u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42eee0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f81acu, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43c0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ecx, 0x158u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_object_post_lock(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_OBJECT_POST_LOCK_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_OBJECT_POST_LOCK_STACK, 0, entry);
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
    esi = eax;
    edi = eax;
    eax = lift_load(&env, eax, 0x15cu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = (ebp + 0xffffffe4u);
    ebx = (ebp + 0xffffffdcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe0u);
    ecx = ecx ^ ecx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x4dcu, 1)) & 0xffu);
    edx = (ebp + 0xffffffd8u);
    ecx = (ecx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432480u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_45186b;
    eax = lift_load(&env, esi, 0x44cu, 4);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_45184b;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ba70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_451854;
    edx = 0x451a60u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bae0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ba80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_451832:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, edx, 0x158u, 4);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
L_45184b:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x452250u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_451832;
L_451854:
    edx = 0x450ff0u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bae0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_451832;
L_45186b:
    eax = lift_load(&env, esi, 0x4c8u, 4);
    {
        (void)lift_sub(32, eax, 0x24u, &fl);
    }
    if (!fl.zf)
        goto L_45188a;
    edx = lift_load(&env, 0u, 0x4f8194u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43c0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ce00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_45188a:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ba70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43b9c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ba90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, edi, 0x184u, 4);
    eax = eax + 1u;
    lift_store(&env, edi, 0x184u, 4, eax);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, edi, 0x188u, 4, lift_load(&env, edi, 0x188u, 4) + edx);
    eax = lift_load(&env, edi, 0x184u, 4);
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4518d3;
    edx = lift_load(&env, 0u, 0x4f81b4u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43c0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4518d3:
    eax = lift_load(&env, edi, 0x184u, 4);
    {
        (void)lift_sub(32, eax, 0x6u, &fl);
    }
    if (!fl.zf)
        goto L_4518eb;
    edx = lift_load(&env, 0u, 0x4f81b4u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43c0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4518eb:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_45190f;
    edx = lift_load(&env, 0u, 0x4f81acu, 4);
L_4518f7:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43c0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4518fe:
    edx = 0x4520f0u;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_451832;
L_45190f:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe0u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4518fe;
    edx = lift_load(&env, 0u, 0x532d88u, 4);
    goto L_4518f7;
}

uint32_t lifted_f452370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F452370_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F452370_STACK, 0, entry);
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
    ecx = lift_load(&env, eax, 0x3b0u, 4);
    esi = eax;
    edx = edx ^ edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x4c5u, 1)) & 0xffu);
    eax = lift_load(&env, eax, 0x15cu, 4);
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4523b1;
L_45238e:
    edx = 0x1u;
L_452393:
    ecx = lift_load(&env, eax, 0x158u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4523bc;
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
L_4523b1:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x3f4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_452393;
    goto L_45238e;
L_4523bc:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bbf0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_effect_board_match(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_EFFECT_BOARD_MATCH_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_EFFECT_BOARD_MATCH_STACK, 0, entry);
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
    ecx = eax;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    edi = lift_load(&env, ecx, 0x15cu, 4);
    edx = edx ^ edx;
    eax = lift_load(&env, eax, 0x3b0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    esi = lift_load(&env, eax, 0x15cu, 4);
    eax = lift_load(&env, eax, 0x3b4u, 4);
    edx = esi;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x438cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_452e70;
    eax = ecx;
    ecx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43acd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
L_452e4f:
    edx = lift_load(&env, edi, 0x158u, 4);
    eax = edi;
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, esi, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_452faa;
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
L_452e70:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ab60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_452f9e;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ac00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_452e87:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, 0u, 0x4f81acu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43c0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4320c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_452f20;
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4330d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_452f20;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x170u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_452f0d;
    ecx = lift_load(&env, esi, 0xa60u, 4);
    eax = lift_load(&env, ecx, 0x15cu, 4);
    edx = lift_load(&env, ecx, 0x160u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x15cu, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x15cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 1, (eax & 0xffu));
    eax = lift_load(&env, ecx, 0x164u, 4);
    ebx = (uint32_t)(int32_t)(int8_t)(uint8_t)(edx & 0xffu);
    edx = lift_load(&env, ebp, 0xffffffe5u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x15cu, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    ecx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43a560u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, eax, 0x170u, 4, 0x0u);
L_452f0d:
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ee20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_452f20:
    edx = 0x44f040u;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42eda0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x44f040u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42eda0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5u;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ee80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42ee80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = esi;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x433040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bb60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0xb80u, 4, 0x1u);
    edx = 0x452050u;
    lift_store(&env, esi, 0xb84u, 4, 0x1u);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, esi, 0xb88u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x452fc0u;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_452e4f;
L_452f9e:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43acd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_452e87;
L_452faa:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bbf0u, eax, edx, ebx, ecx, 0, esp);
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
}

uint32_t lifted_f453d50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F453D50_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F453D50_STACK, 0, entry);
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
    esp = esp - 0x8u;
    edi = eax;
    esi = lift_load(&env, eax, 0x15cu, 4);
    eax = lift_load(&env, eax, 0x3b4u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_453e98;
L_453d83:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x58u, 4), 0x18u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_453ec8;
    eax = esi;
    ebx = lift_load(&env, edi, 0x428u, 4);
    edx = lift_load(&env, edi, 0x424u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f3d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f310u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4320c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_453e38;
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x170u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_453e16;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431d60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_453e16;
    eax = lift_load(&env, esi, 0xa60u, 4);
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
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43a560u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edi, 0x170u, 4, 0x0u);
L_453e16:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432010u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_453e38;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431340u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42eb60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_453e38:
    lift_store(&env, edi, 0x428u, 4, lift_load(&env, edi, 0x428u, 4) + 1u);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x58u, 4), 0x18u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_453e60;
L_453e44:
    ebx = lift_load(&env, esi, 0x58u, 4);
    ebx = ebx - 0x18u;
    lift_store(&env, esi, 0x58u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x18u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_453e44;
L_453e60:
    eax = esi;
    ebx = lift_load(&env, edi, 0x428u, 4);
    edx = lift_load(&env, edi, 0x424u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4314a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_453eb9;
    edx = 0x453ef0u;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_453e83:
    edx = lift_load(&env, esi, 0x158u, 4);
    eax = esi;
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
L_453e98:
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
    goto L_453d83;
L_453eb9:
    edx = lift_load(&env, 0u, 0x4f8188u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43c0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_453e83;
L_453ec8:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    ebx = lift_load(&env, edi, 0x428u, 4);
    edx = lift_load(&env, edi, 0x424u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42f280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_453e83;
}

uint32_t lifted_effect_attack_454e90(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_EFFECT_ATTACK_454E90_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_EFFECT_ATTACK_454E90_STACK, 0, entry);
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
    edx = 0x4u;
    ecx = lift_load(&env, eax, 0x3b0u, 4);
    edi = lift_load(&env, eax, 0x15cu, 4);
    eax = ecx;
    esi = lift_load(&env, ecx, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bb60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bae0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x454f00u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0xb80u, 4, 0x1u);
    lift_store(&env, esi, 0xb84u, 4, 0x1u);
    lift_store(&env, esi, 0xb88u, 4, 0x1u);
    ecx = lift_load(&env, edi, 0x158u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bbf0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4550a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4550A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4550A0_STACK, 0, entry);
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
    ecx = eax;
    edi = eax;
    esi = lift_load(&env, eax, 0x15cu, 4);
    eax = lift_load(&env, eax, 0x3b4u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = lift_load(&env, ecx, 0x3b0u, 4);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = esi;
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4320c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_455136;
    ecx = (ebp + 0xffffffe0u);
    ebx = (ebp + 0xffffffe8u);
    edx = (ebp + 0xffffffe4u);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43a5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_45522e;
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), lift_load(&env, ebp, 0xffffffe8u, 1), &fl);
    }
    if (!fl.zf)
        goto L_45522e;
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), lift_load(&env, ebp, 0xffffffe0u, 1), &fl);
    }
    if (!fl.zf)
        goto L_45522e;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43acd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
L_455117:
    edx = lift_load(&env, esi, 0x158u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd8u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_45528a;
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
L_455136:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bad0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431c10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.zf)
        goto L_4551e8;
L_45514f:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431d60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_455227;
    eax = esi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431c10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    edx = 0x1u;
    lift_store(&env, edi, 0x4d0u, 4, eax);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431c10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    edx = 0x2u;
    lift_store(&env, edi, 0x4d4u, 4, eax);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431c10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    edx = 0x4553a0u;
    lift_store(&env, edi, 0x4d8u, 4, eax);
L_4551b7:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x5u;
    eax = esi;
    ebx = ecx;
    edx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4368e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ac00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f81acu, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43c0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_455117;
L_4551e8:
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431c10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_45514f;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x431c10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_45514f;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43acd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    goto L_455117;
L_455227:
    edx = 0x4552b0u;
    goto L_4551b7;
L_45522e:
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xffffffe4u, 1), 0x5u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, edi, 0x4d0u, 4, eax);
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xffffffe8u, 1), 0x5u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, edi, 0x4d4u, 4, eax);
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xffffffe0u, 1), 0x5u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    edx = 0x455320u;
    lift_store(&env, edi, 0x4d8u, 4, eax);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43ac00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4f81acu, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43c0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_455117;
L_45528a:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bbf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0xb90u, 4, 0x0u);
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

uint32_t lifted_effect_attack_455b20(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_EFFECT_ATTACK_455B20_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_EFFECT_ATTACK_455B20_STACK, 0, entry);
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
    edx = 0x4u;
    ecx = lift_load(&env, eax, 0x3b0u, 4);
    edi = lift_load(&env, eax, 0x15cu, 4);
    eax = ecx;
    esi = lift_load(&env, ecx, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bb60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bae0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x455b90u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0xb80u, 4, 0x1u);
    lift_store(&env, esi, 0xb84u, 4, 0x1u);
    lift_store(&env, esi, 0xb88u, 4, 0x1u);
    ecx = lift_load(&env, edi, 0x158u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bbf0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_effect_attack_455ca0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_EFFECT_ATTACK_455CA0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_EFFECT_ATTACK_455CA0_STACK, 0, entry);
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
    edx = 0x4u;
    ecx = lift_load(&env, eax, 0x3b0u, 4);
    edi = lift_load(&env, eax, 0x15cu, 4);
    eax = ecx;
    esi = lift_load(&env, ecx, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bb60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bae0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x455d10u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0xb80u, 4, 0x1u);
    lift_store(&env, esi, 0xb84u, 4, 0x1u);
    lift_store(&env, esi, 0xb88u, 4, 0x1u);
    ecx = lift_load(&env, edi, 0x158u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bbf0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4570b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4570B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4570B0_STACK, 0, entry);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac390u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_457115;
L_4570c9:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_457109;
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = lift_load(&env, 0u, 0x540f8cu, 4);
    {
        (void)lift_sub(32, edx, 0x64u, &fl);
    }
    if (!fl.zf)
        goto L_457149;
    lift_store(&env, eax, 0x4d0u, 4, 0x0u);
L_4570e4:
    eax = ecx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac950u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x457170u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_457109:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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
L_457115:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac3b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac420u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
L_457129:
    if (fl.cf || fl.zf)
        goto L_4570c9;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac780u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_457140;
    ebx = 0x1u;
L_45713b:
    edx = edx - 1u;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    goto L_457129;
L_457140:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_45713b;
L_457149:
    {
        (void)lift_sub(32, edx, 0x65u, &fl);
    }
    if (!fl.zf)
        goto L_45715a;
    lift_store(&env, eax, 0x4d4u, 4, 0x0u);
    goto L_4570e4;
L_45715a:
    {
        (void)lift_sub(32, edx, 0x66u, &fl);
    }
    if (!fl.zf)
        goto L_4570e4;
    lift_store(&env, eax, 0x4d8u, 4, 0x0u);
    goto L_4570e4;
}

uint32_t lifted_f4571f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4571F0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4571F0_STACK, 0, entry);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac390u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_457255;
L_457209:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_457249;
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = lift_load(&env, 0u, 0x540f90u, 4);
    {
        (void)lift_sub(32, edx, 0x67u, &fl);
    }
    if (!fl.zf)
        goto L_457289;
    lift_store(&env, eax, 0x4d0u, 4, 0x0u);
L_457224:
    eax = ecx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac950u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4572b0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_457249:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
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
L_457255:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac3b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac420u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
L_457269:
    if (fl.cf || fl.zf)
        goto L_457209;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac780u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_457280;
    ebx = 0x1u;
L_45727b:
    edx = edx - 1u;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    goto L_457269;
L_457280:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_45727b;
L_457289:
    {
        (void)lift_sub(32, edx, 0x68u, &fl);
    }
    if (!fl.zf)
        goto L_45729a;
    lift_store(&env, eax, 0x4d4u, 4, 0x0u);
    goto L_457224;
L_45729a:
    {
        (void)lift_sub(32, edx, 0x69u, &fl);
    }
    if (!fl.zf)
        goto L_457224;
    lift_store(&env, eax, 0x4d8u, 4, 0x0u);
    goto L_457224;
}

uint32_t lifted_ui_center_on_anchor(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_UI_CENTER_ON_ANCHOR_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_UI_CENTER_ON_ANCHOR_STACK, 0, entry);
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
    esp = esp - 0x8u;
    ecx = eax;
    edx = edx ^ edx;
    ebx = (ebp + 0xfffffff0u);
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    edx = (ebp + 0xffffffecu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ecx, 0x6u, 4);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    edx = edx - ebx;
    lift_store(&env, ecx, 0xeu, 2, (edx & 0xffffu));
    edx = lift_load(&env, ecx, 0x8u, 4);
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    edx = edx - ebx;
    ebx = edx;
    edx = lift_load(&env, ecx, 0xau, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, edx, ebx, &fl);
        edx = r;
    }
    lift_store(&env, ecx, 0x16u, 2, (edx & 0xffffu));
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

uint32_t lifted_f457a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F457A00_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F457A00_STACK, 0, entry);
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
    ecx = eax;
    eax = lift_load(&env, eax, 0x2eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = ecx;
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
        goto L_457a33;
L_457a29:
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
L_457a33:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    esi = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x8u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0xau, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    ebx = (ebp + 0xffffffe0u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x8u, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, ecx, 0xau, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    lift_store(&env, ecx, 0x2cu, 2, (eax & 0xffffu));
    eax = ecx;
    lift_store(&env, ecx, 0x2eu, 2, (edi & 0xffffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffe8u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ecx, 0x28u, 4);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_457b26;
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    lift_store(&env, ecx, 0x48u, 2, 0x0u);
L_457aa7:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, esi, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x2au, 2, lift_load(&env, ecx, 0x2au, 2) - (eax & 0xffffu));
    eax = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_457ac2;
    lift_store(&env, ecx, 0x2au, 2, 0x0u);
L_457ac2:
    edx = esi;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x457890u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ecx, 0xau, 2, (edi & 0xffffu));
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_457a29;
    edx = 0x457b70u;
    lift_store(&env, ecx, 0x44u, 1, 0x10u);
    eax = ecx;
    lift_store(&env, ecx, 0x93u, 1, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x48u, 2, 0x0u);
    lift_store(&env, ecx, 0x4au, 2, 0x0u);
    lift_store(&env, ecx, 0x4cu, 2, 0x1u);
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
L_457b26:
    eax = ebx;
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_div1(32, lift_load(&env, ebp, 0xffffffdcu, 4), &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_457b52;
L_457b3e:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_457b59;
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    goto L_457aa7;
L_457b52:
    eax = 0x10u;
    goto L_457b3e;
L_457b59:
    eax = eax ^ eax;
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    goto L_457aa7;
}

uint32_t lifted_f457f40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F457F40_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F457F40_STACK, 0, entry);
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
    ecx = eax;
    eax = lift_load(&env, eax, 0x2eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = ecx;
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
        goto L_457f73;
L_457f69:
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
L_457f73:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    esi = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x8u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0xau, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    ebx = (ebp + 0xffffffe0u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x8u, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, ecx, 0xau, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    lift_store(&env, ecx, 0x2cu, 2, (eax & 0xffffu));
    eax = ecx;
    lift_store(&env, ecx, 0x2eu, 2, (edi & 0xffffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffe8u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ecx, 0x28u, 4);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_45806a;
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    lift_store(&env, ecx, 0x48u, 2, 0x0u);
L_457fe7:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, esi, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x2au, 2, lift_load(&env, ecx, 0x2au, 2) - (eax & 0xffffu));
    eax = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_458002;
    lift_store(&env, ecx, 0x2au, 2, 0x0u);
L_458002:
    edx = esi;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x457890u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ecx, 0xau, 2, (edi & 0xffffu));
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_457f69;
    lift_store(&env, ecx, 0x44u, 1, 0x10u);
    lift_store(&env, ecx, 0x4au, 2, 0x32u);
    edx = 0x45a0c0u;
    lift_store(&env, ecx, 0x4cu, 2, 0x2u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4725f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4580b0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
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
L_45806a:
    eax = ebx;
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_div1(32, lift_load(&env, ebp, 0xffffffdcu, 4), &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_458096;
L_458082:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_45809d;
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    goto L_457fe7;
L_458096:
    eax = 0x10u;
    goto L_458082;
L_45809d:
    eax = eax ^ eax;
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    goto L_457fe7;
}

uint32_t lifted_f4585c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4585C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4585C0_STACK, 0, entry);
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
    esp = esp - 0x8u;
    ecx = eax;
    edi = lift_load(&env, eax, 0x2eu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x457810u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    lift_store(&env, ecx, 0xcu, 2, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_458602;
L_4585f1:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x457890u, eax, edx, ebx, ecx, 0, esp);
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
L_458602:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    esi = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    ebx = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffe4u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, ebx, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4586d0;
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    lift_store(&env, ecx, 0x48u, 2, 0x0u);
L_458640:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, esi, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x2au, 2, lift_load(&env, ecx, 0x2au, 2) - (eax & 0xffffu));
    eax = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_45865b;
    lift_store(&env, ecx, 0x2au, 2, 0x0u);
L_45865b:
    edx = esi;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4585f1;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x2cu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x2eu, 2)) & 0xffffu);
    edx = 0x14u;
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    eax = ecx;
    lift_store(&env, ecx, 0x44u, 1, 0x10u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x458260u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x93u, 1, 0x0u);
    lift_store(&env, ecx, 0x48u, 2, 0x0u);
    lift_store(&env, ecx, 0x4au, 2, 0x64u);
    lift_store(&env, ecx, 0x4cu, 2, 0x5u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x457890u, eax, edx, ebx, ecx, 0, esp);
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
L_4586d0:
    eax = ebx;
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_div1(32, edi, &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4586fb;
L_4586e7:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_458702;
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    goto L_458640;
L_4586fb:
    eax = 0x10u;
    goto L_4586e7;
L_458702:
    eax = eax ^ eax;
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    goto L_458640;
}

uint32_t lifted_f458a70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F458A70_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F458A70_STACK, 0, entry);
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
        goto L_458a96;
L_458a8d:
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
L_458a96:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    esi = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    ebx = (ebp + 0xffffffecu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffe8u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, edx, 0xa0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_458b4e;
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    lift_store(&env, ecx, 0x48u, 2, 0x0u);
L_458ad8:
    ebx = (ebp + 0xffffffe4u);
    edx = edx ^ edx;
    eax = ecx;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = (ebp + 0xffffffe0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = lift_load(&env, ebp, 0xffffffe6u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx - eax;
    lift_store(&env, ecx, 0xeu, 2, (edx & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, ebp, 0xffffffeau, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx - eax;
    eax = ecx;
    lift_store(&env, ecx, 0x16u, 2, (edx & 0xffffu));
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad750u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_458b29;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x2au, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x64u, 4, eax);
    edx = edx + esi;
    lift_store(&env, ecx, 0x2au, 2, (edx & 0xffffu));
L_458b29:
    edx = esi;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x44u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_458a8d;
    eax = ecx;
    edx = edx ^ edx;
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
L_458b4e:
    eax = edx;
    ebx = 0xa0u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    lift_div1(32, ebx, &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_458b7c;
L_458b68:
    lift_store(&env, ecx, 0x44u, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_458b83;
    lift_store(&env, ecx, 0x44u, 1, (edx & 0xffu));
    goto L_458ad8;
L_458b7c:
    edx = 0x10u;
    goto L_458b68;
L_458b83:
    edx = edx ^ edx;
    lift_store(&env, ecx, 0x44u, 1, (edx & 0xffu));
    goto L_458ad8;
}

uint32_t lifted_f4594a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4594A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4594A0_STACK, 0, entry);
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
        goto L_4594c8;
L_4594be:
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
L_4594c8:
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
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x8u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0xau, 2)) & 0xffffu);
    edx = ebx;
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4aca60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edx = ebx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4acab0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    edx = ebx;
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    eax = ecx;
    ebx = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = ecx;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    edx = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ecx, 0x6u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = edx - eax;
    lift_store(&env, ecx, 0xeu, 2, (edx & 0xffffu));
    eax = lift_load(&env, ecx, 0x8u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    eax = eax - edx;
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4595dc;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4594be;
    lift_store(&env, ecx, 0x12u, 2, lift_load(&env, ecx, 0x12u, 2) - 0x2u);
    edx = lift_load(&env, ecx, 0x10u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_459573;
    edx = 0x1u;
L_459573:
    eax = lift_load(&env, ecx, 0x70u, 4);
    lift_store(&env, ecx, 0x12u, 2, (edx & 0xffffu));
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
    lift_store(&env, ecx, 0x1au, 2, 0x4u);
    lift_store(&env, ecx, 0x70u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4595ef;
    edx = 0x1u;
L_459596:
    lift_store(&env, ecx, 0x48u, 2, 0x50u);
    lift_store(&env, ecx, 0x70u, 4, edx);
    edx = 0x1c7u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x70u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x4au, 2, 0x0u);
    edx = edx - eax;
    eax = ecx;
    lift_store(&env, ecx, 0x18u, 2, (edx & 0xffffu));
    edx = 0x2u;
    lift_store(&env, ecx, 0x4cu, 2, 0x5u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4acc10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4593b0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
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
L_4595dc:
    eax = ecx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
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
L_4595ef:
    edx = eax;
    goto L_459596;
}

uint32_t lifted_title_letter_count_call(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_TITLE_LETTER_COUNT_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_TITLE_LETTER_COUNT_CALL_STACK, 0,
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
    esp = esp - 0x1cu;
    ecx = eax;
    eax = (ebp + 0xffffffd0u);
    edx = 0x4ec1ecu;
    ebx = 0x51536cu;
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
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    eax = ecx;
    edi = lift_load(&env, ecx, 0x2eu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_459c47;
L_459c2d:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x457890u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
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
L_459c47:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    esi = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    ebx = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffe8u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, ebx, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_459cfd;
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    lift_store(&env, ecx, 0x48u, 2, 0x0u);
L_459c85:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, esi, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x2au, 2, lift_load(&env, ecx, 0x2au, 2) - (eax & 0xffffu));
    eax = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_459ca0;
    lift_store(&env, ecx, 0x2au, 2, 0x0u);
L_459ca0:
    edx = esi;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_459c2d;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x2cu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x44u, 1, 0x10u);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x2eu, 2)) & 0xffffu);
    edi = lift_load(&env, ecx, 0x4u, 4);
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_459d33;
    edx = lift_load(&env, 0u, 0x4f81b8u, 4);
    edx = edx + lift_load(&env, ecx, 0x58u, 4);
    eax = (edx + 0xffffffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x459ec0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_459c2d;
L_459cfd:
    eax = ebx;
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_div1(32, edi, &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_459d28;
L_459d14:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_459d2f;
L_459d20:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    goto L_459c85;
L_459d28:
    eax = 0x10u;
    goto L_459d14;
L_459d2f:
    eax = eax ^ eax;
    goto L_459d20;
L_459d33:
    edx = lift_load(&env, 0u, 0x4f81b8u, 4);
    edx = edx + lift_load(&env, ecx, 0x58u, 4);
    eax = (edx + 0xffffffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417290u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x459ec0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_459c2d;
}

uint32_t lifted_title_letter_fight_count_call(const VertrixCalls *calls,
                                              const VertrixFactoryServices *services,
                                              const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_TITLE_LETTER_FIGHT_COUNT_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_TITLE_LETTER_FIGHT_COUNT_CALL_STACK, 0,
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
    esp = esp - 0x8u;
    ecx = eax;
    edi = lift_load(&env, eax, 0x2eu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_45a2c5;
L_45a2b4:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x457890u, eax, edx, ebx, ecx, 0, esp);
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
L_45a2c5:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    esi = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    ebx = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffe4u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, ebx, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_45a39e;
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    lift_store(&env, ecx, 0x48u, 2, 0x0u);
L_45a303:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, esi, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x2au, 2, lift_load(&env, ecx, 0x2au, 2) - (eax & 0xffffu));
    eax = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_45a31e;
    lift_store(&env, ecx, 0x2au, 2, 0x0u);
L_45a31e:
    edx = esi;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_45a2b4;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x2cu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x2eu, 2)) & 0xffffu);
    edx = 0x32u;
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x4f81c4u, 4);
    lift_store(&env, ecx, 0x44u, 1, 0x10u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4171e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x32u;
    eax = lift_load(&env, 0u, 0x4f81c4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x48u, 2, 0x0u);
    edx = 0x45a3e0u;
    lift_store(&env, ecx, 0x4au, 2, 0x96u);
    eax = ecx;
    lift_store(&env, ecx, 0x4cu, 2, 0x5u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x457890u, eax, edx, ebx, ecx, 0, esp);
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
L_45a39e:
    eax = ebx;
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_div1(32, edi, &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_45a3c9;
L_45a3b5:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_45a3d0;
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    goto L_45a303;
L_45a3c9:
    eax = 0x10u;
    goto L_45a3b5;
L_45a3d0:
    eax = eax ^ eax;
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    goto L_45a303;
}

uint32_t lifted_title_letter_fight_fly_call(const VertrixCalls *calls,
                                            const VertrixFactoryServices *services,
                                            const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_TITLE_LETTER_FIGHT_FLY_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_TITLE_LETTER_FIGHT_FLY_CALL_STACK, 0,
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
    esp = esp - 0x10u;
    ecx = eax;
    edi = lift_load(&env, eax, 0x2eu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_45a51e;
L_45a514:
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
L_45a51e:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    esi = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    ebx = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffe8u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_45a5d5;
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    lift_store(&env, ecx, 0x48u, 2, 0x0u);
L_45a55c:
    ebx = (ebp + 0xffffffe0u);
    edx = edx ^ edx;
    eax = ecx;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    edx = (ebp + 0xffffffdcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_load(&env, ebp, 0xffffffe6u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax - edx;
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = lift_load(&env, ebp, 0xffffffe2u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, esi, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x16u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x2au, 2)) & 0xffffu);
    edx = edx + eax;
    eax = ecx;
    lift_store(&env, ecx, 0x2au, 2, (edx & 0xffffu));
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x44u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_45a514;
    eax = ecx;
    edx = edx ^ edx;
    esi = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x532a40u, 4, esi);
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
L_45a5d5:
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    lift_div1(32, edi, &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_45a600;
L_45a5ec:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_45a607;
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    goto L_45a55c;
L_45a600:
    eax = 0x10u;
    goto L_45a5ec;
L_45a607:
    eax = eax ^ eax;
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    goto L_45a55c;
}

uint32_t lifted_title_letter_wave_count_call(const VertrixCalls *calls,
                                             const VertrixFactoryServices *services,
                                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_TITLE_LETTER_WAVE_COUNT_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_TITLE_LETTER_WAVE_COUNT_CALL_STACK, 0,
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
    esp = esp - 0x8u;
    ecx = eax;
    edi = lift_load(&env, eax, 0x2eu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_45a655;
L_45a644:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x457890u, eax, edx, ebx, ecx, 0, esp);
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
L_45a655:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    esi = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    ebx = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffe4u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, ebx, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_45a710;
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    lift_store(&env, ecx, 0x48u, 2, 0x0u);
L_45a693:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, esi, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x2au, 2, lift_load(&env, ecx, 0x2au, 2) - (eax & 0xffffu));
    eax = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_45a6ae;
    lift_store(&env, ecx, 0x2au, 2, 0x0u);
L_45a6ae:
    edx = esi;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_45a644;
    lift_store(&env, ecx, 0x44u, 1, 0x10u);
    lift_store(&env, ecx, 0x48u, 2, 0x0u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x2cu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x4au, 2, 0x32u);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x2eu, 2)) & 0xffffu);
    edx = 0x45a750u;
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    eax = ecx;
    lift_store(&env, ecx, 0x4cu, 2, 0x2u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x457890u, eax, edx, ebx, ecx, 0, esp);
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
L_45a710:
    eax = ebx;
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_div1(32, edi, &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_45a73b;
L_45a727:
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x44u, 1)) & 0xffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_45a742;
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    goto L_45a693;
L_45a73b:
    eax = 0x10u;
    goto L_45a727;
L_45a742:
    eax = eax ^ eax;
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    goto L_45a693;
}

uint32_t lifted_title_letter_wave_fly_call(const VertrixCalls *calls,
                                           const VertrixFactoryServices *services,
                                           const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_TITLE_LETTER_WAVE_FLY_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_TITLE_LETTER_WAVE_FLY_CALL_STACK, 0,
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
    esp = esp - 0x10u;
    ecx = eax;
    edi = lift_load(&env, eax, 0x2eu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_45a93e;
L_45a934:
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
L_45a93e:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    esi = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac5b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    ebx = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffe4u);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_45a9e6;
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    lift_store(&env, ecx, 0x48u, 2, 0x0u);
L_45a978:
    ebx = (ebp + 0xffffffe0u);
    edx = edx ^ edx;
    eax = ecx;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    edx = (ebp + 0xffffffdcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = lift_load(&env, ebp, 0xffffffe2u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx - eax;
    lift_store(&env, ecx, 0xeu, 2, (edx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, ebp, 0xffffffe6u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax - edx;
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x32u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, esi, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x2au, 2)) & 0xffffu);
    edx = edx + eax;
    eax = ecx;
    lift_store(&env, ecx, 0x2au, 2, (edx & 0xffffu));
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x44u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_45a934;
    eax = ecx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
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
L_45a9e6:
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    lift_div1(32, edi, &eax, &edx, &fl);
    edx = 0x10u;
    edx = edx - eax;
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_45aa0e;
L_45a9fb:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    lift_store(&env, ecx, 0x44u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_45aa15;
    lift_store(&env, ecx, 0x44u, 1, (edx & 0xffu));
    goto L_45a978;
L_45aa0e:
    eax = 0x10u;
    goto L_45a9fb;
L_45aa15:
    edx = edx ^ edx;
    lift_store(&env, ecx, 0x44u, 1, (edx & 0xffu));
    goto L_45a978;
}

uint32_t lifted_f45ac70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F45AC70_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F45AC70_STACK, 0, entry);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    esi = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac390u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.zf)
        goto L_45ac94;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_45acdc;
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
L_45ac94:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac3b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac420u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_45acc1;
L_45acaa:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac780u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_45acd8;
    eax = ecx;
    edx = edx - 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_45acaa;
L_45acc1:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac4a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_45acdc;
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
L_45acd8:
    esi = esi ^ esi;
    goto L_45acc1;
L_45acdc:
    ebx = lift_load(&env, ecx, 0x4u, 4);
    ebx = lift_load(&env, 0u, (ebx * 4u) + 0x540f88u, 4);
    edx = 0x544a34u;
    eax = ecx;
    ebx = lift_load(&env, ebx, 0x488u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ebx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    edx = 0x45abd0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adfe0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f45ad20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F45AD20_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F45AD20_STACK, 0, entry);
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
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = ebx;
    edi = lift_load(&env, 0u, 0x532a68u, 4);
    esi = esi + 0x3bu;
    edi = lift_load(&env, 0u, (edi * 4u) + 0x534f10u, 4);
L_45ad4f:
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    eax = 0x54d640u;
    edx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_45ad75;
L_45ad64:
    ebx = ebx + 1u;
    esi = esi + 1u;
    {
        (void)lift_sub(32, ebx, 0xau, &fl);
    }
    if (!fl.zf)
        goto L_45ad4f;
L_45ad6b:
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
L_45ad75:
    eax = 0x54d640u;
    edx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ebx, edi, &fl);
    }
    if (!fl.cf)
        goto L_45ad64;
    eax = ((ebx * 4u));
    eax = eax + ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax - ebx;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    ecx = lift_load(&env, 0u, 0x532a68u, 4);
    edi = ((ebx * 8u));
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    edi = edi - ebx;
    ebx = lift_load(&env, 0u, 0x532a68u, 4);
    edx = lift_load(&env, ecx, (eax * 4u) + 0x534c18u, 4);
    eax = ((ebx * 8u));
    eax = eax + ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax - ebx;
    ebx = 0x544f90u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    ebx = ebx + eax;
    ebx = ebx + edi;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_45ae38;
    ecx = lift_load(&env, 0u, 0x4f81ccu, 4);
L_45add9:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_45ae14;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac4a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = 0x45aea0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_45ae14:
    {
        (void)lift_sub(32, ecx, lift_load(&env, 0u, 0x4f81ccu, 4), &fl);
    }
    if (fl.zf)
        goto L_45ad6b;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417260u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417290u, eax, edx, ebx, ecx, 0, esp);
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
L_45ae38:
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_45ae47;
    ecx = lift_load(&env, 0u, 0x4f81ccu, 4);
    edx = edx ^ edx;
    goto L_45add9;
L_45ae47:
    {
        (void)lift_sub(32, edx, 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_45ae56;
    ecx = lift_load(&env, 0u, 0x4f81ccu, 4);
    edx = edx ^ edx;
    goto L_45add9;
L_45ae56:
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_45ae68;
    ecx = lift_load(&env, 0u, 0x4f81ccu, 4);
    edx = edx ^ edx;
    goto L_45add9;
L_45ae68:
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_45ae7a;
    ecx = lift_load(&env, ecx, 0x532ca4u, 4);
    edx = edx ^ edx;
    goto L_45add9;
L_45ae7a:
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_45ae8c;
    ecx = lift_load(&env, ecx, 0x532cf0u, 4);
    edx = edx ^ edx;
    goto L_45add9;
L_45ae8c:
    ecx = lift_load(&env, 0u, 0x4f81ccu, 4);
    goto L_45ae14;
}

uint32_t lifted_f45b190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F45B190_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F45B190_STACK, 0, entry);
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
    esp = esp - 0x8u;
    ecx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45afe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    esi = lift_load(&env, 0u, 0x4f81ccu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ecx, 0x64u, 4);
    eax = lift_load(&env, ecx, 0x58u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x417fc0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_45b2a8;
    edx = edx ^ edx;
    eax = 0x598d30u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe4u, 2)) & 0xffffu);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ebx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    edx = lift_load(&env, ecx, 0x64u, 4);
    eax = lift_load(&env, ecx, 0x58u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_45b1f1:
    ebx = eax;
L_45b1f3:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_45b3b4;
    eax = ((ebx * 4u));
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = lift_load(&env, ecx, 0x64u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_45b2dd;
L_45b216:
    edx = lift_load(&env, ecx, 0x58u, 4);
    esi = ((edx * 8u));
    esi = esi + edx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    esi = esi - edx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        esi = r;
    }
    esi = esi + 0x544f90u;
    ebx = ebx ^ ebx;
    edi = (esi + eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
L_45b238:
    esi = lift_load(&env, 0u, 0x4f81ccu, 4);
L_45b23e:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_45b3e3;
    eax = ecx;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edi;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac700u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac4a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    edx = 0x45b410u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_45b27a:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, esi, lift_load(&env, 0u, 0x4f81ccu, 4), &fl);
    }
    if (fl.zf)
        goto L_45b29e;
    eax = lift_load(&env, ecx, 0x70u, 4);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_45b3ed;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_45b3fe;
L_45b29e:
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
L_45b2a8:
    eax = lift_load(&env, ecx, 0x58u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_45b1f3;
    edx = edx ^ edx;
    eax = 0x598d30u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe4u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = lift_load(&env, ecx, 0x58u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4180a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_45b1f1;
L_45b2dd:
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_45b309;
    edi = lift_load(&env, ecx, 0x58u, 4);
    esi = ((edi * 8u));
    esi = esi + edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    esi = esi - edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        esi = r;
    }
    esi = esi + 0x544f90u;
    edx = edx ^ edx;
    edi = (esi + eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    goto L_45b238;
L_45b309:
    {
        (void)lift_sub(32, edx, 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_45b33b;
    edi = lift_load(&env, ecx, 0x58u, 4);
    esi = ((edi * 8u));
    esi = esi + edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    esi = esi - edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        esi = r;
    }
    esi = esi + 0x544f90u;
    edi = (esi + eax);
    eax = eax ^ eax;
    esi = lift_load(&env, 0u, 0x4f81ccu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    goto L_45b23e;
L_45b33b:
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (fl.zf)
        goto L_45b216;
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_45b37a;
    edi = lift_load(&env, ecx, 0x58u, 4);
    esi = ((edi * 8u));
    esi = esi + edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    esi = esi - edi;
    edi = 0x544f90u;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        esi = r;
    }
    edx = edx ^ edx;
    edi = edi + esi;
    esi = lift_load(&env, ecx, 0x58u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    edi = edi + eax;
    esi = lift_load(&env, 0u, (esi * 4u) + 0x532ca4u, 4);
    goto L_45b23e;
L_45b37a:
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_45b23e;
    edi = lift_load(&env, ecx, 0x58u, 4);
    esi = ((edi * 8u));
    esi = esi + edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    esi = esi - edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        esi = r;
    }
    esi = esi + 0x544f90u;
    edi = (esi + eax);
    eax = eax ^ eax;
    esi = lift_load(&env, ecx, 0x58u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    esi = lift_load(&env, 0u, (esi * 4u) + 0x532cf0u, 4);
    goto L_45b23e;
L_45b3b4:
    edx = lift_load(&env, ecx, 0x64u, 4);
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_45b3cb;
    esi = lift_load(&env, ecx, 0x58u, 4);
    esi = lift_load(&env, 0u, (esi * 4u) + 0x532ca4u, 4);
    goto L_45b23e;
L_45b3cb:
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_45b23e;
    esi = lift_load(&env, ecx, 0x58u, 4);
    esi = lift_load(&env, 0u, (esi * 4u) + 0x532cf0u, 4);
    goto L_45b23e;
L_45b3e3:
    edx = 0x45b0b0u;
    goto L_45b27a;
L_45b3ed:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4172c0u, eax, edx, ebx, ecx, 0, esp);
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
L_45b3fe:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4173d0u, eax, edx, ebx, ecx, 0, esp);
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
}

uint32_t lifted_effect_attack_45b9c0(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_EFFECT_ATTACK_45B9C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_EFFECT_ATTACK_45B9C0_STACK, 0, entry);
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
    edx = 0x4u;
    ecx = lift_load(&env, eax, 0x3b0u, 4);
    edi = lift_load(&env, eax, 0x15cu, 4);
    eax = ecx;
    esi = lift_load(&env, ecx, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bb60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bae0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x45ba30u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0xb80u, 4, 0x1u);
    lift_store(&env, esi, 0xb84u, 4, 0x1u);
    lift_store(&env, esi, 0xb88u, 4, 0x1u);
    ecx = lift_load(&env, edi, 0x158u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43bbf0u, eax, edx, ebx, ecx, 0, esp);
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
