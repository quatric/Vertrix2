/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_5.h"

uint32_t lifted_f4c8500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C8500_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C8500_STACK, 0, entry);
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
    esp = esp - 0x84cu;
    lift_store(&env, esp, 0x780u, 4, eax);
    lift_store(&env, esp, 0x784u, 4, edx);
    lift_store(&env, esp, 0x788u, 4, ebx);
    lift_store(&env, esp, 0x78cu, 4, ecx);
    eax = lift_load(&env, eax, 0x1ccu, 4);
    eax = lift_load(&env, eax, 0x18u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x790u, 4, eax);
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        eax = r;
    }
    ecx = ebx;
    eax = eax + 0x4u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        ecx = r;
    }
    lift_store(&env, esp, 0x794u, 4, eax);
    eax = ecx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, esp, 0x78cu, 4);
    eax = eax + 0x2u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        ebx = r;
    }
    lift_store(&env, esp, 0x798u, 4, eax);
    eax = ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        eax = r;
    }
    eax = eax + 0x4u;
    lift_store(&env, esp, 0x79cu, 4, eax);
    eax = lift_load(&env, esp, 0x794u, 4);
    lift_store(&env, esp, 0x7a0u, 4, eax);
    eax = lift_load(&env, esp, 0x798u, 4);
    lift_store(&env, esp, 0x7a4u, 4, eax);
    eax = lift_load(&env, esp, 0x79cu, 4);
    lift_store(&env, esp, 0x7a8u, 4, eax);
    eax = (esp + 0x600u);
    ebp = lift_load(&env, esp, 0x780u, 4);
    lift_store(&env, esp, 0x7acu, 4, eax);
    eax = lift_load(&env, ebp, 0x84u, 4);
    lift_store(&env, esp, 0x7b0u, 4, eax);
    eax = lift_load(&env, esp, 0x794u, 4);
    eax = eax + 0x18u;
    lift_store(&env, esp, 0x7b4u, 4, eax);
    eax = lift_load(&env, esp, 0x794u, 4);
    eax = eax + lift_load(&env, esp, 0x7b4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x7c0u, 4, eax);
    eax = lift_load(&env, esp, 0x798u, 4);
    eax = eax + 0x1cu;
    lift_store(&env, esp, 0x7b8u, 4, eax);
    eax = lift_load(&env, esp, 0x798u, 4);
    eax = eax + lift_load(&env, esp, 0x7b8u, 4);
    lift_store(&env, esp, 0x784u, 4, edx);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x788u, 4, ecx);
    lift_store(&env, esp, 0x7c4u, 4, eax);
    eax = lift_load(&env, esp, 0x79cu, 4);
    lift_store(&env, esp, 0x78cu, 4, ebx);
    eax = eax + 0x18u;
    ecx = 0x7fffffffu;
    lift_store(&env, esp, 0x7bcu, 4, eax);
    eax = lift_load(&env, esp, 0x79cu, 4);
    edx = lift_load(&env, esp, 0x7bcu, 4);
    lift_store(&env, esp, 0x7ccu, 4, ecx);
    eax = eax + edx;
    ebx = lift_load(&env, esp, 0x7b0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
    }
    edx = edx ^ edx;
    lift_store(&env, esp, 0x7c8u, 4, eax);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c87f3;
    edi = edi ^ edi;
L_4c866e:
    eax = lift_load(&env, ebp, 0x88u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x0u, 1)) & 0xffu);
    eax = lift_load(&env, esp, 0x7b4u, 4);
    esi = ecx;
    esi = esi - eax;
    esi = esi + esi;
    {
        uint32_t r = lift_imul(32, esi, esi, &fl);
        esi = r;
    }
    ebx = ecx;
    eax = lift_load(&env, esp, 0x7a0u, 4);
    ebx = ebx - eax;
    ebx = ebx + ebx;
    {
        uint32_t r = lift_imul(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c8b51;
    eax = ebx;
L_4c86a5:
    ecx = esi;
L_4c86a7:
    ebx = lift_load(&env, ebp, 0x88u, 4);
    ebx = lift_load(&env, ebx, 0x4u, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, ebx + 0x0u, 1)) & 0xffu);
    ebx = ebx & 0xffu;
    esi = ebx;
    esi = esi - lift_load(&env, esp, 0x7b8u, 4);
    lift_store(&env, esp, 0x80cu, 4, esi);
    esi = ebx;
    esi = esi - lift_load(&env, esp, 0x7a4u, 4);
    lift_store(&env, esp, 0x810u, 4, esi);
    esi = lift_load(&env, esp, 0x80cu, 4);
    esi = (esi + (esi * 2u));
    lift_store(&env, esp, 0x81cu, 4, esi);
    esi = lift_load(&env, esp, 0x810u, 4);
    esi = (esi + (esi * 2u));
    lift_store(&env, esp, 0x820u, 4, esi);
    esi = lift_load(&env, esp, 0x81cu, 4);
    {
        uint32_t r = lift_imul(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, esp, 0x82cu, 4, esi);
    esi = lift_load(&env, esp, 0x820u, 4);
    {
        uint32_t r = lift_imul(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, esp, 0x830u, 4, esi);
    esi = lift_load(&env, esp, 0x82cu, 4);
    esi = esi + ecx;
    lift_store(&env, esp, 0x838u, 4, esi);
    {
        (void)lift_sub(32, ebx, lift_load(&env, esp, 0x7a4u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c8b79;
    esi = lift_load(&env, esp, 0x830u, 4);
    ebx = lift_load(&env, esp, 0x838u, 4);
    eax = eax + esi;
L_4c874a:
    ecx = lift_load(&env, ebp, 0x88u, 4);
    ecx = lift_load(&env, ecx, 0x8u, 4);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, edx + 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    esi = ecx;
    esi = esi - lift_load(&env, esp, 0x7bcu, 4);
    lift_store(&env, esp, 0x814u, 4, esi);
    esi = ecx;
    esi = esi - lift_load(&env, esp, 0x7a8u, 4);
    lift_store(&env, esp, 0x818u, 4, esi);
    esi = lift_load(&env, esp, 0x814u, 4);
    {
        uint32_t r = lift_imul(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, esp, 0x824u, 4, esi);
    esi = lift_load(&env, esp, 0x818u, 4);
    {
        uint32_t r = lift_imul(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, esp, 0x828u, 4, esi);
    esi = lift_load(&env, esp, 0x824u, 4);
    esi = esi + ebx;
    lift_store(&env, esp, 0x834u, 4, esi);
    {
        (void)lift_sub(32, ecx, lift_load(&env, esp, 0x7a8u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c8bac;
    ebx = lift_load(&env, esp, 0x828u, 4);
    ecx = lift_load(&env, esp, 0x834u, 4);
    eax = eax + ebx;
L_4c87cb:
    esi = lift_load(&env, esp, 0x7ccu, 4);
    lift_store(&env, esp, edi + 0x0u, 4, eax);
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c87e0;
    lift_store(&env, esp, 0x7ccu, 4, ecx);
L_4c87e0:
    esi = lift_load(&env, esp, 0x7b0u, 4);
    edx = edx + 1u;
    edi = edi + 0x4u;
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c866e;
L_4c87f3:
    edi = lift_load(&env, esp, 0x7b0u, 4);
    ecx = ecx ^ ecx;
    edx = edx ^ edx;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c882d;
    esi = lift_load(&env, esp, 0x7acu, 4);
    ebp = lift_load(&env, esp, 0x7ccu, 4);
    edi = lift_load(&env, esp, 0x7b0u, 4);
    eax = eax ^ eax;
L_4c8819:
    {
        (void)lift_sub(32, ebp, lift_load(&env, esp, eax + 0x0u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c8825;
    ebx = ecx;
    ebx = ebx + esi;
    ecx = ecx + 1u;
    lift_store(&env, ebx, 0x0u, 1, (edx & 0xffu));
L_4c8825:
    edx = edx + 1u;
    eax = eax + 0x4u;
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c8819;
L_4c882d:
    eax = lift_load(&env, esp, 0x780u, 4);
    lift_store(&env, esp, 0x7d0u, 4, eax);
    eax = lift_load(&env, esp, 0x794u, 4);
    lift_store(&env, esp, 0x7d4u, 4, eax);
    eax = lift_load(&env, esp, 0x798u, 4);
    ebx = (esp + 0x600u);
    lift_store(&env, esp, 0x7d8u, 4, eax);
    eax = lift_load(&env, esp, 0x79cu, 4);
    edx = (esp + 0x400u);
    lift_store(&env, esp, 0x7dcu, 4, eax);
    eax = (esp + 0x700u);
    lift_store(&env, esp, 0x7e0u, 4, ecx);
    lift_store(&env, esp, 0x7e4u, 4, eax);
    eax = 0x7fu;
L_4c888d:
    eax = eax - 1u;
    lift_store(&env, edx, 0x0u, 4, 0x7fffffffu);
    edx = edx + 0x4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c888d;
    edi = edi ^ edi;
    ebp = lift_load(&env, esp, 0x7e0u, 4);
    lift_store(&env, esp, 0x848u, 4, edi);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c8a92;
    lift_store(&env, esp, 0x83cu, 4, ebx);
L_4c88ba:
    edx = lift_load(&env, esp, 0x83cu, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, esp, 0x7d0u, 4);
    lift_store(&env, esp, 0x7f0u, 4, eax);
    edx = lift_load(&env, edx, 0x88u, 4);
    esi = lift_load(&env, esp, 0x7f0u, 4);
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + esi;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ecx = lift_load(&env, esp, 0x7d4u, 4);
    eax = eax & 0xffu;
    ecx = ecx - eax;
    ecx = ecx + ecx;
    eax = ecx;
    {
        uint32_t r = lift_imul(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, esp, 0x7f4u, 4, ecx);
    ecx = lift_load(&env, edx, 0x4u, 4);
    ecx = ecx + esi;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    ebx = lift_load(&env, esp, 0x7d8u, 4);
    ecx = ecx & 0xffu;
    ebx = ebx - ecx;
    ecx = (ebx + (ebx * 2u));
    lift_store(&env, esp, 0x800u, 4, ecx);
    {
        uint32_t r = lift_imul(32, ecx, ecx, &fl);
        ecx = r;
    }
    edx = lift_load(&env, edx, 0x8u, 4);
    ebx = lift_load(&env, esp, 0x7f4u, 4);
    edx = edx + esi;
    ebx = ebx + ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    lift_store(&env, esp, 0x7f4u, 4, ebx);
    ecx = lift_load(&env, esp, 0x7dcu, 4);
    edx = edx & 0xffu;
    ecx = ecx - edx;
    edx = ecx;
    {
        uint32_t r = lift_imul(32, edx, ecx, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x804u, 4, ecx);
    edi = ecx;
    ecx = lift_load(&env, esp, 0x800u, 4);
    ebp = (ebx + edx);
    {
        uint32_t r = lift_imul(32, ecx, 0x18u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        eax = r;
    }
    eax = eax + 0x100u;
    lift_store(&env, esp, 0x7f8u, 4, eax);
    edx = edx + 0x90u;
    ebx = 0x3u;
    lift_store(&env, esp, 0x800u, 4, edx);
    edx = edi;
    lift_store(&env, esp, 0x7f4u, 4, ebp);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x7e8u, 4, ebx);
    edx = edx + 0x40u;
    edi = lift_load(&env, esp, 0x7e4u, 4);
    lift_store(&env, esp, 0x804u, 4, edx);
    edx = (esp + 0x400u);
L_4c89b2:
    eax = lift_load(&env, esp, 0x800u, 4);
    lift_store(&env, esp, 0x7fcu, 4, eax);
    eax = 0x7u;
    ebp = lift_load(&env, esp, 0x7f4u, 4);
    lift_store(&env, esp, 0x7ecu, 4, eax);
L_4c89d3:
    esi = lift_load(&env, esp, 0x804u, 4);
    ecx = 0x3u;
    eax = ebp;
L_4c89e1:
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x0u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c89f0;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esp, 0x7f0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x0u, 4, eax);
    lift_store(&env, edi, 0x0u, 1, (ebx & 0xffu));
L_4c89f0:
    edx = edx + 0x4u;
    edi = edi + 1u;
    ecx = ecx - 1u;
    eax = eax + esi;
    esi = esi + 0x80u;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c89e1;
    ecx = lift_load(&env, esp, 0x7ecu, 4);
    esi = lift_load(&env, esp, 0x7fcu, 4);
    ecx = ecx - 1u;
    ebp = ebp + esi;
    eax = (esi + 0x120u);
    lift_store(&env, esp, 0x7ecu, 4, ecx);
    lift_store(&env, esp, 0x7fcu, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c89d3;
    eax = lift_load(&env, esp, 0x7f8u, 4);
    esi = lift_load(&env, esp, 0x7f4u, 4);
    esi = esi + eax;
    ebp = (eax + 0x200u);
    eax = lift_load(&env, esp, 0x7e8u, 4);
    lift_store(&env, esp, 0x7f4u, 4, esi);
    eax = eax - 1u;
    lift_store(&env, esp, 0x7f8u, 4, ebp);
    lift_store(&env, esp, 0x7e8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c89b2;
    eax = lift_load(&env, esp, 0x83cu, 4);
    edx = lift_load(&env, esp, 0x848u, 4);
    ecx = lift_load(&env, esp, 0x7e0u, 4);
    eax = eax + 1u;
    edx = edx + 1u;
    lift_store(&env, esp, 0x83cu, 4, eax);
    lift_store(&env, esp, 0x848u, 4, edx);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c88ba;
L_4c8a92:
    edx = lift_load(&env, esp, 0x78cu, 4);
    eax = lift_load(&env, esp, 0x784u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x808u, 4, edx);
    edx = lift_load(&env, esp, 0x790u, 4);
    edx = edx + eax;
    ebx = lift_load(&env, esp, 0x788u, 4);
    lift_store(&env, esp, 0x840u, 4, edx);
    edx = lift_load(&env, esp, 0x790u, 4);
    edi = (esp + 0x700u);
    edx = edx + 0x10u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        ebx = r;
    }
    eax = eax + edx;
    lift_store(&env, esp, 0x788u, 4, ebx);
    lift_store(&env, esp, 0x844u, 4, eax);
L_4c8ae8:
    ebp = lift_load(&env, esp, 0x788u, 4);
    {
        uint32_t a = ebp;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        ebp = r;
    }
    ebx = lift_load(&env, esp, 0x840u, 4);
    esi = ebp;
    ebp = ebp + 0x200u;
L_4c8b01:
    eax = lift_load(&env, ebx, 0x0u, 4);
    edx = lift_load(&env, esp, 0x808u, 4);
    eax = eax + esi;
    edx = edx + eax;
    eax = eax ^ eax;
L_4c8b10:
    edi = edi + 1u;
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) ^ ((ecx >> 8) & 0xffu)) & 0xffu) << 8);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edi, 0xffffffffu, 1)) & 0xffu);
    edx = edx + 0x2u;
    ecx = ecx + 1u;
    eax = eax + 1u;
    lift_store(&env, edx, 0xfffffffeu, 2, (ecx & 0xffffu));
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c8b10;
    esi = esi + 0x40u;
    {
        (void)lift_sub(32, esi, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4c8b01;
    esi = lift_load(&env, esp, 0x840u, 4);
    esi = esi + 0x4u;
    ebp = lift_load(&env, esp, 0x844u, 4);
    lift_store(&env, esp, 0x840u, 4, esi);
    {
        (void)lift_sub(32, esi, ebp, &fl);
    }
    if (!fl.zf)
        goto L_4c8ae8;
    {
        uint32_t r = lift_add(32, esp, 0x84cu, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4c8b51:
    {
        (void)lift_sub(32, ecx, lift_load(&env, esp, 0x7b4u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c8b63;
    eax = esi;
    ecx = ebx;
    goto L_4c86a7;
L_4c8b63:
    eax = eax ^ eax;
    {
        (void)lift_sub(32, ecx, lift_load(&env, esp, 0x7c0u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c86a5;
    ecx = ebx;
    goto L_4c86a7;
L_4c8b79:
    ecx = ecx + lift_load(&env, esp, 0x830u, 4);
    {
        (void)lift_sub(32, ebx, lift_load(&env, esp, 0x7b8u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c8b97;
    eax = eax + lift_load(&env, esp, 0x82cu, 4);
L_4c8b90:
    ebx = ecx;
    goto L_4c874a;
L_4c8b97:
    {
        (void)lift_sub(32, ebx, lift_load(&env, esp, 0x7c4u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c8b90;
    ebx = lift_load(&env, esp, 0x838u, 4);
    goto L_4c874a;
L_4c8bac:
    ebx = ebx + lift_load(&env, esp, 0x828u, 4);
    {
        (void)lift_sub(32, ecx, lift_load(&env, esp, 0x7bcu, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c8bca;
    eax = eax + lift_load(&env, esp, 0x824u, 4);
L_4c8bc3:
    ecx = ebx;
    goto L_4c87cb;
L_4c8bca:
    {
        (void)lift_sub(32, ecx, lift_load(&env, esp, 0x7c8u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c8bc3;
    ecx = lift_load(&env, esp, 0x834u, 4);
    goto L_4c87cb;
}

uint32_t lifted_f4cd56c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CD56C_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CD56C_STACK, 0, entry);
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
    esp = esp - 0x20u;
    edi = eax;
    lift_store(&env, esp, 0x1cu, 4, edx);
    ebp = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0250u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cd597;
    eax = 0xbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0xffffffffu;
    goto L_4cd795;
L_4cd597:
    esi = edx;
    ebx = (esp + 0x14u);
    esi = esi & 0x7u;
    edx = (esp + 0x10u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0960u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (esp + 0xcu);
    eax = ebp;
    ebx = ebx ^ ebx;
    eax = eax | esi;
    ebp = 0x80u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0994u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xcu;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esp, 0x1cu, 1)) & 0xffu) << 8);
    lift_store(&env, esp, 0x4u, 4, ebx);
    lift_store(&env, esp, 0x0u, 4, edx);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x80u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x507d04u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cd61b;
    edx = 0x5123a8u;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e09f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cd61b;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x2000u;
    ecx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507d04u, 4), eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
    goto L_4cd745;
L_4cd61b:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esp, 0x1cu, 1)) & 0xffu);
    {
        (void)lift_and(8, (edx & 0xffu), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4cd69a;
    edx = lift_load(&env, ecx, 0x0u, 4);
    edx = edx + 0x4u;
    lift_store(&env, ecx, 0x0u, 4, edx);
    eax = lift_load(&env, edx, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x14u, 4, eax);
    lift_store(&env, ecx, 0x0u, 4, 0x0u);
    eax = lift_load(&env, 0u, 0x507d54u, 4);
    ebx = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t a = eax;
        eax = (~a) & lift_mask(4);
    }
    ebx = ebx & eax;
    lift_store(&env, esp, 0x14u, 4, ebx);
    {
        (void)lift_and(8, lift_load(&env, esp, 0x15u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4cd660;
    {
        (void)lift_and(8, lift_load(&env, esp, 0x14u, 1), 0x80u, &fl);
    }
    if (!fl.zf)
        goto L_4cd660;
    ebp = 0x1u;
L_4cd660:
    {
        (void)lift_and(8, lift_load(&env, esp, 0x1du, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4cd674;
    edx = 0x1u;
    lift_store(&env, esp, 0x18u, 4, edx);
    eax = edx;
    goto L_4cd6ab;
L_4cd674:
    {
        (void)lift_and(8, lift_load(&env, esp, 0x1cu, 1), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4cd68a;
    lift_store(&env, esp, 0x18u, 4, 0x2u);
    eax = 0x1u;
    goto L_4cd6ab;
L_4cd68a:
    ecx = 0x4u;
    eax = 0x3u;
    lift_store(&env, esp, 0x18u, 4, ecx);
    goto L_4cd6ab;
L_4cd69a:
    {
        (void)lift_and(8, (edx & 0xffu), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4cd6a6;
    eax = 0x5u;
    goto L_4cd6ab;
L_4cd6a6:
    eax = 0x3u;
L_4cd6ab:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0xcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, esp, 0x1cu, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, esp, 0x24u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b34u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    ebx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4cd703;
    {
        (void)lift_and(8, lift_load(&env, esp, 0x1cu, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4cd6f2;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = lift_load(&env, esp, 0x20u, 4);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x1cu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, esp, 0x24u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b34u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    ebx = eax;
L_4cd6f2:
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4cd703;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4cd703:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    edi = lift_load(&env, 0u, 0x507c34u, 4);
    ecx = eax;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.cf)
        goto L_4cd737;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x5u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0xffffffffu;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4cd737:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0a30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cd745;
    edx = 0x2000u;
L_4cd745:
    {
        (void)lift_sub(32, esi, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4cd74f;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) | 0x3u) & 0xffu);
    goto L_4cd760;
L_4cd74f:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4cd758;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) | 0x1u) & 0xffu);
    goto L_4cd760;
L_4cd758:
    {
        (void)lift_sub(32, esi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4cd760;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) | 0x2u) & 0xffu);
L_4cd760:
    {
        (void)lift_and(8, lift_load(&env, esp, 0x1cu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4cd76a;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) | 0x80u) & 0xffu);
L_4cd76a:
    eax = edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esp, 0x1du, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) | 0x40u) & 0xffu);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4cd77e;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4cd78c;
    goto L_4cd78a;
L_4cd77e:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x505440u, 4), 0x200u, &fl);
    }
    if (!fl.zf)
        goto L_4cd78c;
L_4cd78a:
    edx = eax;
L_4cd78c:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0228u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
L_4cd795:
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cd7dc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CD7DC_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CD7DC_STACK, 0, entry);
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
    edx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bedu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cd813;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cd813;
    ebx = lift_load(&env, edx, 0x4u, 4);
    {
        (void)lift_sub(32, ebx, lift_load(&env, edx, 0x8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4cd813;
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - 1u) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0xfu, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4cd80e;
    eax = (eax & 0xffu);
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4cd80e;
            case 1:
                goto L_4cd813;
            case 2:
                goto L_4cd813;
            case 3:
                goto L_4cd813;
            case 4:
                goto L_4cd80e;
            case 5:
                goto L_4cd813;
            case 6:
                goto L_4cd813;
            case 7:
                goto L_4cd813;
            case 8:
                goto L_4cd813;
            case 9:
                goto L_4cd813;
            case 10:
                goto L_4cd813;
            case 11:
                goto L_4cd813;
            case 12:
                goto L_4cd813;
            case 13:
                goto L_4cd80e;
            case 14:
                goto L_4cd813;
            case 15:
                goto L_4cd813;
            default:
                return 0u;
        }
    }
L_4cd80e:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4cd813:
    eax = ecx;
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

uint32_t lifted_f4cfa20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CFA20_STACK + 4 + 4 * 4 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CFA20_STACK, 4, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x84u;
    eax = (esp + 0x50u);
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
    lift_store(&env, esp, 0x54u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x58u, 4, 0x5194d4u);
    lift_store(&env, esp, 0x5cu, 4, 0x0u);
    {
        uint32_t v = 0x502778u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x90u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19ccu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    lift_store(&env, esp, 0x74u, 4, eax);
    lift_store(&env, esp, 0x80u, 4, 0x0u);
    eax = esp;
    lift_store(&env, esp, 0x5cu, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9f06u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4cfc08;
    ebx = 0x1u;
    eax = lift_load(&env, esp, 0x90u, 4);
    {
        (void)lift_sub(32, eax, 0x20u, &fl);
    }
    if (fl.cf)
        goto L_4cfbbf;
    if (fl.cf || fl.zf)
        goto L_4cfb58;
    {
        (void)lift_sub(32, eax, 0x82u, &fl);
    }
    if (fl.cf)
        goto L_4cfbc8;
    if (fl.cf || fl.zf)
        goto L_4cfb93;
    {
        (void)lift_sub(32, eax, 0x110u, &fl);
    }
    if (!fl.zf)
        goto L_4cfbc8;
    eax = lift_load(&env, esp, 0x8cu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = eax;
    eax = (esp + 0x7cu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x64u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf4a0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    eax = lift_load(&env, esp, 0x98u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x98u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x98u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x98u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x84u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f18f0u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        uint32_t v = lift_load(&env, esp, 0x7cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esp, 0x84u, 4, eax);
    eax = (esp + 0x64u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf4d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    goto L_4cfc63;
L_4cfb2d:
    eax = lift_load(&env, esp, 0x98u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x98u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x94u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf560u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    goto L_4cfbc8;
L_4cfb58:
    eax = lift_load(&env, esp, 0x98u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax & 0xffffu;
    eax = (eax & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, esp, 0x9cu, 2);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x94u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf5d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
    ebx = eax;
    goto L_4cfbc8;
L_4cfb93:
    eax = lift_load(&env, esp, 0x74u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xfffffffcu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x94u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ad0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        uint32_t v = 0x502778u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x90u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a7cu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    goto L_4cfbc8;
L_4cfbbf:
    {
        (void)lift_sub(32, eax, 0x6u, &fl);
    }
    if (fl.zf)
        goto L_4cfb2d;
L_4cfbc8:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4cfc63;
    eax = lift_load(&env, esp, 0x98u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x98u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x98u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x98u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x84u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f18f0u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    lift_store(&env, esp, 0x80u, 4, eax);
    goto L_4cfc63;
L_4cfc08:
    lift_store(&env, esp, 0x5cu, 4, 0x3u);
    eax = lift_load(&env, esp, 0x8cu, 4);
    lift_store(&env, esp, 0x34u, 4, eax);
    eax = lift_load(&env, esp, 0x90u, 4);
    lift_store(&env, esp, 0x38u, 4, eax);
    eax = lift_load(&env, esp, 0x94u, 4);
    lift_store(&env, esp, 0x3cu, 4, eax);
    eax = lift_load(&env, esp, 0x98u, 4);
    lift_store(&env, esp, 0x40u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cbe80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, eax, 0x0u, 4);
    ebx = (esp + 0x34u);
    edx = lift_load(&env, esp, 0x78u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x70u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x80u, 4, eax);
    eax = lift_load(&env, esp, 0x78u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4da6b6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4cfc63:
    lift_store(&env, esp, 0x5cu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x80u, 4);
    lift_store(&env, esp, 0x70u, 4, eax);
    eax = lift_load(&env, esp, 0x50u, 4);
    env.chain = eax;
    eax = lift_load(&env, esp, 0x70u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x84u, &fl);
        esp = r;
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

uint32_t lifted_f4d01a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D01A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D01A0_STACK, 0, entry);
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
    esp = esp - 0x30u;
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4d01d6;
    lift_store(&env, esp, 0x20u, 4, 0x1u);
    edx = 0x518ed0u;
    lift_store(&env, esp, 0x0u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4d028c;
L_4d01d6:
    lift_store(&env, eax, 0x0u, 4, 0x519664u);
    lift_store(&env, esp, 0x24u, 4, eax);
    eax = (esp + 0x14u);
    lift_store(&env, esp, 0x28u, 1, (ebx & 0xffu));
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
    lift_store(&env, esp, 0x18u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x1cu, 4, 0x5194f0u);
    lift_store(&env, esp, 0x20u, 4, 0x3u);
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x1cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d023c;
    {
        (void)lift_sub(32, ecx, 0x5c5c6cu, &fl);
    }
    if (fl.zf)
        goto L_4d023c;
    {
        (void)lift_sub(32, ecx, 0x5c5ca8u, &fl);
    }
    if (fl.zf)
        goto L_4d023c;
    {
        (void)lift_sub(32, ecx, 0x5c5ce4u, &fl);
    }
    if (fl.zf)
        goto L_4d023c;
    {
        (void)lift_sub(32, ecx, 0x5c5d20u, &fl);
    }
    if (fl.zf)
        goto L_4d023c;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d0410u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4d023c:
    eax = lift_load(&env, ecx, 0x34u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d024d;
    esi = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4d024d:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x38u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d0262;
    eax = lift_load(&env, ecx, 0x38u, 4);
    {
        (void)lift_sub(32, ecx, lift_load(&env, eax, 0x24u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d0262;
    lift_store(&env, eax, 0x24u, 4, 0x0u);
L_4d0262:
    edx = 0x1u;
    eax = ecx;
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cb4f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4d0282;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4d0282:
    eax = lift_load(&env, esp, 0x14u, 4);
    env.chain = eax;
L_4d028c:
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x30u, &fl);
        esp = r;
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

uint32_t lifted_f4d4700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D4700_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D4700_STACK, 0, entry);
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
    esp = esp - 0x8u;
    ebx = eax;
    lift_store(&env, esp, 0x0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cccc0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, 0x40000000u, &fl);
    }
    if (fl.zf)
        goto L_4d471b;
    edx = ebx;
    goto L_4d4724;
L_4d471b:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d1930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
L_4d4724:
    esi = edx;
    {
        (void)lift_and(8, lift_load(&env, esp, 0x0u, 1), 0xcu, &fl);
    }
    if (fl.zf)
        goto L_4d4780;
    {
        (void)lift_and(8, lift_load(&env, esp, 0x0u, 1), 0x8u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
    lift_store(&env, esp, 0x4u, 4, eax);
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cce00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d476d;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d476d;
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4d476d;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x86u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebx, 0x25u, 1, lift_load(&env, ebx, 0x25u, 1) | 0x2u);
    {
        uint32_t v = lift_load(&env, edx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    lift_store(&env, ebx, 0x25u, 1, lift_load(&env, ebx, 0x25u, 1) & 0xfdu);
    goto L_4d4780;
L_4d476d:
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
        uint32_t v = 0x86u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
L_4d4780:
    {
        uint32_t v = 0x5u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1978u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a04u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d47c7;
L_4d4797:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d4390u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d47b7;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x36du;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
L_4d47b7:
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a04u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d4797;
L_4d47c7:
    {
        uint32_t r = lift_add(32, esp, 0x8u, &fl);
        esp = r;
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

uint32_t lifted_f4d5ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D5AB0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D5AB0_STACK, 0, entry);
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
    ebp = esp;
    esp = esp - 0x11cu;
    edi = eax;
    esi = ebx;
    lift_store(&env, ebp, 0xfffffffcu, 4, ecx);
    eax = (ebp + 0xffffffe4u);
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
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x4ec1ecu);
    lift_store(&env, ebp, 0xffffffecu, 4, 0x51984cu);
    eax = edi;
    lift_store(&env, ebp, 0xfffffff0u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cba60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d5afb;
    {
        uint32_t r = lift_xor(32, esi, ebx, &fl);
        esi = r;
    }
    goto L_4d5bc4;
L_4d5afb:
    eax = (ebp + 0xfffffff8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xfffffff0u, 4, 0x1u);
    edi = ebx;
    eax = lift_load(&env, ebx, 0x4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x8u, 4), 0xfffffdf8u, &fl);
    }
    if (!fl.zf)
        goto L_4d5b1e;
    {
        (void)lift_and(8, lift_load(&env, ebx, 0x64u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4d5b30;
L_4d5b1e:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0xfffffdeeu, &fl);
    }
    if (!fl.zf)
        goto L_4d5b3b;
    {
        (void)lift_and(8, lift_load(&env, edi, 0xb4u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4d5b3b;
L_4d5b30:
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1980u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = (eax & 0xffffu);
L_4d5b3b:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d5b65;
    {
        uint32_t v = 0x100u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xfffffee4u);
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
    eax = lift_call(&env, 0x4db950u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        uint32_t v = 0xau;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xfffffee4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xfffffff8u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db980u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
L_4d5b65:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0xfffffdf8u, &fl);
    }
    if (!fl.zf)
        goto L_4d5b80;
    {
        uint32_t v = 0x50u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0xfffffff8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx + 0x10u;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1d20u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    goto L_4d5b90;
L_4d5b80:
    ebx = 0x50u;
    edx = lift_load(&env, ebp, 0xfffffff8u, 4);
    eax = (edi + 0x10u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca770u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4d5b90:
    {
        uint32_t v = 0x13u;
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
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xfffffffcu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    {
        uint32_t v = lift_load(&env, esi, 0x0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ad8u, eax, edx, ebx, ecx, 7, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 28u;
    esi = 0x1u;
    eax = (ebp + 0xfffffff8u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xfffffff0u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4d5bc4:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    env.chain = eax;
    eax = esi;
    esp = ebp;
    ebp = lift_load(&env, esp, 0u, 4);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}
