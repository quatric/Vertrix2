/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_28.h"

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
