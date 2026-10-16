/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_9.h"

uint32_t lifted_board_spin_marked(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_BOARD_SPIN_MARKED_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_BOARD_SPIN_MARKED_STACK, 0, entry);
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
    esp = esp - 0x2cu;
    esi = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x436030u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x436070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_43800d;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4383dc;
L_43800d:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = edi ^ edi;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4381f6;
L_43801a:
    edx = 0x8u;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax & 0xffffu;
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = eax + 0x4u;
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x7u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_438042;
    edx = (eax + 0xfffffff9u);
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
L_438042:
    ecx = (ebp + 0xffffffd0u);
    ebx = (ebp + 0xffffffccu);
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4360b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffffccu, 4), 0x34u, &fl);
        eax = r;
    }
    edx = (esi + eax);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    ebx = lift_load(&env, edx, (eax * 4u) + 0x220u, 4);
    lift_store(&env, edx, (eax * 4u) + 0x87cu, 4, ebx);
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffffccu, 4), 0x34u, &fl);
        eax = r;
    }
    edx = (esi + eax);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, edx, (eax * 4u) + 0x220u, 4, 0x0u);
    edx = 0x44cfd0u;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4u;
    eax = 0x598d30u;
    lift_store(&env, ebx, 0x4eu, 1, 0x64u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    edx = edx + 0x4u;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    lift_store(&env, ebx, 0x93u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x44u, 1, 0x10u);
    lift_store(&env, ebx, 0x45u, 1, 0x0u);
    lift_store(&env, ebx, 0x46u, 2, 0x1u);
    lift_store(&env, ebx, 0x58u, 4, 0x0u);
    lift_store(&env, ebx, 0x5cu, 4, 0x4u);
    lift_store(&env, ebx, 0x60u, 4, 0x1u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0xeu, 2)) & 0xffffu);
    lift_store(&env, ebx, 0x64u, 4, 0x0u);
    lift_store(&env, ebx, 0x8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x16u, 2)) & 0xffffu);
    lift_store(&env, ebx, 0xau, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    lift_store(&env, ebx, 0x68u, 4, 0x2u);
    edx = 0x5u;
    lift_store(&env, ebx, 0x24u, 2, (eax & 0xffffu));
    eax = 0x598d30u;
    lift_store(&env, ebx, 0x6cu, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x430800u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffffccu, 4), 0x34u, &fl);
        ecx = r;
    }
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    ecx = ecx + esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    ecx = ecx + edx;
    lift_store(&env, ecx, 0x220u, 4, eax);
    ecx = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0xeu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x16u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    eax = ecx;
    edx = lift_load(&env, ebx, 0xd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    edx = lift_load(&env, ebx, 0xc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x93u, 1, 0x1u);
    lift_store(&env, ecx, 0x4eu, 1, 0x32u);
    eax = ecx;
    edx = lift_load(&env, ebx, 0xb8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x44ccd0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
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
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    lift_store(&env, ecx, 0x45u, 1, 0x10u);
    lift_store(&env, ecx, 0x46u, 2, 0x1u);
    lift_store(&env, ecx, 0x58u, 4, 0x0u);
    lift_store(&env, ecx, 0x5cu, 4, 0x4u);
    lift_store(&env, ecx, 0x60u, 4, 0x1u);
    lift_store(&env, ecx, 0x64u, 4, 0x0u);
    lift_store(&env, ecx, 0x68u, 4, 0x2u);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, ecx, 0x6cu, 4, 0x1u);
    edi = edi + 1u;
    lift_store(&env, ecx, 0x24u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffe8u, 4), &fl);
    }
    if (fl.cf)
        goto L_43801a;
L_4381f6:
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = edi ^ edi;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4383d7;
L_438203:
    edx = 0x8u;
    eax = 0x598d30u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax & 0xffffu;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = eax + 0x4u;
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x7u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_43822b;
    eax = eax - 0x7u;
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
L_43822b:
    ecx = (ebp + 0xffffffd8u);
    ebx = (ebp + 0xffffffd4u);
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x436100u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffffd4u, 4), 0x34u, &fl);
        eax = r;
    }
    edx = (esi + eax);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    ebx = lift_load(&env, edx, (eax * 4u) + 0x220u, 4);
    lift_store(&env, edx, (eax * 4u) + 0x87cu, 4, ebx);
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffffd4u, 4), 0x34u, &fl);
        eax = r;
    }
    edx = (esi + eax);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, edx, (eax * 4u) + 0x220u, 4, 0x0u);
    edx = 0x44cfd0u;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4u;
    eax = 0x598d30u;
    lift_store(&env, ebx, 0x4eu, 1, 0x64u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    edx = edx + 0x4u;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    lift_store(&env, ebx, 0x93u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x44u, 1, 0x10u);
    lift_store(&env, ebx, 0x45u, 1, 0x0u);
    lift_store(&env, ebx, 0x46u, 2, 0x1u);
    lift_store(&env, ebx, 0x58u, 4, 0x0u);
    lift_store(&env, ebx, 0x5cu, 4, 0x4u);
    lift_store(&env, ebx, 0x60u, 4, 0x1u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0xeu, 2)) & 0xffffu);
    lift_store(&env, ebx, 0x64u, 4, 0x0u);
    lift_store(&env, ebx, 0x8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x16u, 2)) & 0xffffu);
    lift_store(&env, ebx, 0xau, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, ebx, 0x68u, 4, 0x2u);
    edx = 0x5u;
    lift_store(&env, ebx, 0x24u, 2, (eax & 0xffffu));
    eax = esi;
    lift_store(&env, ebx, 0x6cu, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x430800u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffffd4u, 4), 0x34u, &fl);
        edx = r;
    }
    ecx = (esi + edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    ecx = ecx + edx;
    lift_store(&env, ecx, 0x220u, 4, eax);
    ecx = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0xeu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x16u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x16u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    lift_store(&env, ecx, 0x8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    lift_store(&env, ecx, 0xau, 2, (eax & 0xffffu));
    eax = ecx;
    edx = lift_load(&env, ebx, 0xd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    edx = lift_load(&env, ebx, 0xc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x93u, 1, 0x1u);
    lift_store(&env, ecx, 0x4eu, 1, 0x32u);
    eax = ecx;
    edx = lift_load(&env, ebx, 0xb8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x44ccd0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
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
    lift_store(&env, ecx, 0x44u, 1, 0x0u);
    lift_store(&env, ecx, 0x45u, 1, 0x10u);
    lift_store(&env, ecx, 0x46u, 2, 0x1u);
    lift_store(&env, ecx, 0x58u, 4, 0x0u);
    lift_store(&env, ecx, 0x5cu, 4, 0x4u);
    lift_store(&env, ecx, 0x60u, 4, 0x1u);
    lift_store(&env, ecx, 0x64u, 4, 0x0u);
    lift_store(&env, ecx, 0x68u, 4, 0x2u);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ecx, 0x6cu, 4, 0x1u);
    edi = edi + 1u;
    lift_store(&env, ecx, 0x24u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffdcu, 4), &fl);
    }
    if (fl.cf)
        goto L_438203;
L_4383d7:
    eax = 0x1u;
L_4383dc:
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

uint32_t lifted_f480080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F480080_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F480080_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x80158290u, &fl);
    }
    if (!fl.cf)
        goto L_4802bf;
    {
        (void)lift_sub(32, edx, 0x80158120u, &fl);
    }
    if (!fl.cf)
        goto L_480526;
    {
        (void)lift_sub(32, edx, 0x80158030u, &fl);
    }
    if (!fl.cf)
        goto L_480642;
    {
        (void)lift_sub(32, edx, 0x80004002u, &fl);
    }
    if (!fl.cf)
        goto L_4806c8;
    {
        (void)lift_sub(32, edx, 0x15800eu, &fl);
    }
    if (!fl.cf)
        goto L_480710;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4802fd;
    eax = 0x50f0b0u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4800ce:
    eax = 0x50f0b5u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4800d5:
    eax = 0x50f0c4u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4800dc:
    eax = 0x50f0d6u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4800e3:
    eax = 0x50f0ecu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4800ea:
    eax = 0x50f104u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4800f1:
    eax = 0x50f120u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4800f8:
    eax = 0x50f13au;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4800ff:
    eax = 0x50f153u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480106:
    eax = 0x50f169u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48010d:
    eax = 0x50f17du;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480114:
    eax = 0x50f194u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48011b:
    eax = 0x50f1acu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480122:
    eax = 0x50f1c9u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480129:
    eax = 0x50f1dbu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480130:
    eax = 0x50f1f1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480137:
    eax = 0x50f203u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48013e:
    eax = 0x50f217u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480145:
    eax = 0x50f22bu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48014c:
    eax = 0x50f243u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480153:
    eax = 0x50f25fu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48015a:
    eax = 0x50f278u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480161:
    eax = 0x50f294u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480168:
    eax = 0x50f2a5u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48016f:
    eax = 0x50f2b4u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480176:
    eax = 0x50f2c9u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48017d:
    eax = 0x50f2d8u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480184:
    eax = 0x50f2f6u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48018b:
    eax = 0x50f313u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480192:
    eax = 0x50f32cu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480199:
    eax = 0x50f348u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801a0:
    eax = 0x50f362u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801a7:
    eax = 0x50f378u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801ae:
    eax = 0x50f394u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801b5:
    eax = 0x50f3abu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801bc:
    eax = 0x50f3bfu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801c3:
    eax = 0x50f3d3u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801ca:
    eax = 0x50f3e8u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801d1:
    eax = 0x50f402u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801d8:
    eax = 0x50f419u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801df:
    eax = 0x50f431u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801e6:
    eax = 0x50f446u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801ed:
    eax = 0x50f45au;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801f4:
    eax = 0x50f471u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4801fb:
    eax = 0x50f486u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480202:
    eax = 0x50f49cu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480209:
    eax = 0x50f4b3u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480210:
    eax = 0x50f4c8u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480217:
    eax = 0x50f4dau;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48021e:
    eax = 0x50f4f0u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480225:
    eax = 0x50f4feu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48022c:
    eax = 0x50f512u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480233:
    eax = 0x50f526u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48023a:
    eax = 0x50f539u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480241:
    eax = 0x50f558u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480248:
    eax = 0x50f56au;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48024f:
    eax = 0x50f57cu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480256:
    eax = 0x50f58bu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48025d:
    eax = 0x50f59bu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480264:
    eax = 0x50f5b0u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48026b:
    eax = 0x50f5c3u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480272:
    eax = 0x50f5d2u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480279:
    eax = 0x50f5eeu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480280:
    eax = 0x50f600u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480287:
    eax = 0x50f618u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48028e:
    eax = 0x50f632u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480295:
    eax = 0x50f646u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_48029c:
    eax = 0x50f659u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4802a3:
    eax = 0x50f66au;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4802aa:
    eax = 0x50f67au;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4802b1:
    eax = 0x50f68fu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4802b8:
    eax = 0x50f6a2u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4802bf:
    if (fl.cf || fl.zf)
        goto L_480192;
    {
        (void)lift_sub(32, edx, 0x80158470u, &fl);
    }
    if (!fl.cf)
        goto L_480319;
    {
        (void)lift_sub(32, edx, 0x80158380u, &fl);
    }
    if (!fl.cf)
        goto L_480441;
    {
        (void)lift_sub(32, edx, 0x80158330u, &fl);
    }
    if (!fl.cf)
        goto L_4804c7;
    {
        (void)lift_sub(32, edx, 0x80158310u, &fl);
    }
    if (!fl.cf)
        goto L_48050f;
    {
        (void)lift_sub(32, edx, 0x80158300u, &fl);
    }
    if (fl.zf)
        goto L_480199;
L_4802fd:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x50f6b4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x558c90u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b24u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    eax = 0x558c90u;
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_480319:
    if (fl.cf || fl.zf)
        goto L_48021e;
    {
        (void)lift_sub(32, edx, 0x80158560u, &fl);
    }
    if (!fl.cf)
        goto L_48034d;
    {
        (void)lift_sub(32, edx, 0x80158510u, &fl);
    }
    if (!fl.cf)
        goto L_4803e2;
    {
        (void)lift_sub(32, edx, 0x80158490u, &fl);
    }
    if (!fl.cf)
        goto L_48042a;
    {
        (void)lift_sub(32, edx, 0x80158480u, &fl);
    }
    if (fl.zf)
        goto L_480225;
    goto L_4802fd;
L_48034d:
    if (fl.cf || fl.zf)
        goto L_480272;
    {
        (void)lift_sub(32, edx, 0x80158610u, &fl);
    }
    if (!fl.cf)
        goto L_480371;
    {
        (void)lift_sub(32, edx, 0x80158580u, &fl);
    }
    if (!fl.cf)
        goto L_4803b9;
    {
        (void)lift_sub(32, edx, 0x80158570u, &fl);
    }
    if (fl.zf)
        goto L_480279;
    goto L_4802fd;
L_480371:
    if (fl.cf || fl.zf)
        goto L_480295;
    {
        (void)lift_sub(32, edx, 0x80158630u, &fl);
    }
    if (!fl.cf)
        goto L_480390;
    {
        (void)lift_sub(32, edx, 0x80158620u, &fl);
    }
    if (fl.zf)
        goto L_48029c;
    goto L_4802fd;
L_480390:
    if (fl.cf || fl.zf)
        goto L_4802a3;
    {
        (void)lift_sub(32, edx, 0x80158640u, &fl);
    }
    if (fl.cf)
        goto L_4802fd;
    if (fl.cf || fl.zf)
        goto L_4802aa;
    {
        (void)lift_sub(32, edx, 0x80158650u, &fl);
    }
    if (fl.zf)
        goto L_4802b8;
    goto L_4802fd;
L_4803b9:
    if (fl.cf || fl.zf)
        goto L_480280;
    {
        (void)lift_sub(32, edx, 0x80158590u, &fl);
    }
    if (fl.cf)
        goto L_4802fd;
    if (fl.cf || fl.zf)
        goto L_480287;
    {
        (void)lift_sub(32, edx, 0x80158600u, &fl);
    }
    if (fl.zf)
        goto L_48028e;
    goto L_4802fd;
L_4803e2:
    if (fl.cf || fl.zf)
        goto L_480241;
    {
        (void)lift_sub(32, edx, 0x80158530u, &fl);
    }
    if (!fl.cf)
        goto L_480401;
    {
        (void)lift_sub(32, edx, 0x80158520u, &fl);
    }
    if (fl.zf)
        goto L_480248;
    goto L_4802fd;
L_480401:
    if (fl.cf || fl.zf)
        goto L_48024f;
    {
        (void)lift_sub(32, edx, 0x80158540u, &fl);
    }
    if (fl.cf)
        goto L_4802fd;
    if (fl.cf || fl.zf)
        goto L_480256;
    {
        (void)lift_sub(32, edx, 0x80158550u, &fl);
    }
    if (fl.zf)
        goto L_48025d;
    goto L_4802fd;
L_48042a:
    if (fl.cf || fl.zf)
        goto L_48022c;
    {
        (void)lift_sub(32, edx, 0x80158500u, &fl);
    }
    if (fl.zf)
        goto L_48023a;
    goto L_4802fd;
L_480441:
    if (fl.cf || fl.zf)
        goto L_4801d1;
    {
        (void)lift_sub(32, edx, 0x80158420u, &fl);
    }
    if (!fl.cf)
        goto L_480468;
    {
        (void)lift_sub(32, edx, 0x80158400u, &fl);
    }
    if (!fl.cf)
        goto L_4804b0;
    {
        (void)lift_sub(32, edx, 0x80158390u, &fl);
    }
    if (fl.zf)
        goto L_4801d8;
    goto L_4802fd;
L_480468:
    if (fl.cf || fl.zf)
        goto L_4801f4;
    {
        (void)lift_sub(32, edx, 0x80158440u, &fl);
    }
    if (!fl.cf)
        goto L_480487;
    {
        (void)lift_sub(32, edx, 0x80158430u, &fl);
    }
    if (fl.zf)
        goto L_480202;
    goto L_4802fd;
L_480487:
    if (fl.cf || fl.zf)
        goto L_480209;
    {
        (void)lift_sub(32, edx, 0x80158450u, &fl);
    }
    if (fl.cf)
        goto L_4802fd;
    if (fl.cf || fl.zf)
        goto L_480210;
    {
        (void)lift_sub(32, edx, 0x80158460u, &fl);
    }
    if (fl.zf)
        goto L_480217;
    goto L_4802fd;
L_4804b0:
    if (fl.cf || fl.zf)
        goto L_4801df;
    {
        (void)lift_sub(32, edx, 0x80158410u, &fl);
    }
    if (fl.zf)
        goto L_4801ed;
    goto L_4802fd;
L_4804c7:
    if (fl.cf || fl.zf)
        goto L_4801ae;
    {
        (void)lift_sub(32, edx, 0x80158350u, &fl);
    }
    if (!fl.cf)
        goto L_4804e6;
    {
        (void)lift_sub(32, edx, 0x80158340u, &fl);
    }
    if (fl.zf)
        goto L_4801b5;
    goto L_4802fd;
L_4804e6:
    if (fl.cf || fl.zf)
        goto L_4801bc;
    {
        (void)lift_sub(32, edx, 0x80158360u, &fl);
    }
    if (fl.cf)
        goto L_4802fd;
    if (fl.cf || fl.zf)
        goto L_4801c3;
    {
        (void)lift_sub(32, edx, 0x80158370u, &fl);
    }
    if (fl.zf)
        goto L_4801ca;
    goto L_4802fd;
L_48050f:
    if (fl.cf || fl.zf)
        goto L_4801a0;
    {
        (void)lift_sub(32, edx, 0x80158320u, &fl);
    }
    if (fl.zf)
        goto L_4801a7;
    goto L_4802fd;
L_480526:
    if (fl.cf || fl.zf)
        goto L_48010d;
    {
        (void)lift_sub(32, edx, 0x80158200u, &fl);
    }
    if (!fl.cf)
        goto L_48055d;
    {
        (void)lift_sub(32, edx, 0x80158160u, &fl);
    }
    if (!fl.cf)
        goto L_4805e3;
    {
        (void)lift_sub(32, edx, 0x80158140u, &fl);
    }
    if (!fl.cf)
        goto L_48062b;
    {
        (void)lift_sub(32, edx, 0x80158130u, &fl);
    }
    if (fl.zf)
        goto L_480114;
    goto L_4802fd;
L_48055d:
    if (fl.cf || fl.zf)
        goto L_48014c;
    {
        (void)lift_sub(32, edx, 0x80158240u, &fl);
    }
    if (!fl.cf)
        goto L_480584;
    {
        (void)lift_sub(32, edx, 0x80158220u, &fl);
    }
    if (!fl.cf)
        goto L_4805cc;
    {
        (void)lift_sub(32, edx, 0x80158210u, &fl);
    }
    if (fl.zf)
        goto L_480153;
    goto L_4802fd;
L_480584:
    if (fl.cf || fl.zf)
        goto L_48016f;
    {
        (void)lift_sub(32, edx, 0x80158260u, &fl);
    }
    if (!fl.cf)
        goto L_4805a3;
    {
        (void)lift_sub(32, edx, 0x80158250u, &fl);
    }
    if (fl.zf)
        goto L_480176;
    goto L_4802fd;
L_4805a3:
    if (fl.cf || fl.zf)
        goto L_48017d;
    {
        (void)lift_sub(32, edx, 0x80158270u, &fl);
    }
    if (fl.cf)
        goto L_4802fd;
    if (fl.cf || fl.zf)
        goto L_480184;
    {
        (void)lift_sub(32, edx, 0x80158280u, &fl);
    }
    if (fl.zf)
        goto L_48018b;
    goto L_4802fd;
L_4805cc:
    if (fl.cf || fl.zf)
        goto L_48015a;
    {
        (void)lift_sub(32, edx, 0x80158230u, &fl);
    }
    if (fl.zf)
        goto L_480161;
    goto L_4802fd;
L_4805e3:
    if (fl.cf || fl.zf)
        goto L_480129;
    {
        (void)lift_sub(32, edx, 0x80158175u, &fl);
    }
    if (!fl.cf)
        goto L_480602;
    {
        (void)lift_sub(32, edx, 0x80158170u, &fl);
    }
    if (fl.zf)
        goto L_480130;
    goto L_4802fd;
L_480602:
    if (fl.cf || fl.zf)
        goto L_480137;
    {
        (void)lift_sub(32, edx, 0x80158180u, &fl);
    }
    if (fl.cf)
        goto L_4802fd;
    if (fl.cf || fl.zf)
        goto L_48013e;
    {
        (void)lift_sub(32, edx, 0x80158190u, &fl);
    }
    if (fl.zf)
        goto L_480145;
    goto L_4802fd;
L_48062b:
    if (fl.cf || fl.zf)
        goto L_48011b;
    {
        (void)lift_sub(32, edx, 0x80158150u, &fl);
    }
    if (fl.zf)
        goto L_480122;
    goto L_4802fd;
L_480642:
    if (fl.cf || fl.zf)
        goto L_4800ce;
    {
        (void)lift_sub(32, edx, 0x80158070u, &fl);
    }
    if (!fl.cf)
        goto L_480669;
    {
        (void)lift_sub(32, edx, 0x80158050u, &fl);
    }
    if (!fl.cf)
        goto L_4806b1;
    {
        (void)lift_sub(32, edx, 0x80158040u, &fl);
    }
    if (fl.zf)
        goto L_4800d5;
    goto L_4802fd;
L_480669:
    if (fl.cf || fl.zf)
        goto L_4800ea;
    {
        (void)lift_sub(32, edx, 0x80158090u, &fl);
    }
    if (!fl.cf)
        goto L_480688;
    {
        (void)lift_sub(32, edx, 0x80158080u, &fl);
    }
    if (fl.zf)
        goto L_4800f1;
    goto L_4802fd;
L_480688:
    if (fl.cf || fl.zf)
        goto L_4800f8;
    {
        (void)lift_sub(32, edx, 0x80158100u, &fl);
    }
    if (fl.cf)
        goto L_4802fd;
    if (fl.cf || fl.zf)
        goto L_4800ff;
    {
        (void)lift_sub(32, edx, 0x80158110u, &fl);
    }
    if (fl.zf)
        goto L_480106;
    goto L_4802fd;
L_4806b1:
    if (fl.cf || fl.zf)
        goto L_4800dc;
    {
        (void)lift_sub(32, edx, 0x80158060u, &fl);
    }
    if (fl.zf)
        goto L_4800e3;
    goto L_4802fd;
L_4806c8:
    if (fl.cf || fl.zf)
        goto L_480233;
    {
        (void)lift_sub(32, edx, 0x80004005u, &fl);
    }
    if (!fl.cf)
        goto L_4806e7;
    {
        (void)lift_sub(32, edx, 0x80004003u, &fl);
    }
    if (fl.zf)
        goto L_4801fb;
    goto L_4802fd;
L_4806e7:
    if (fl.cf || fl.zf)
        goto L_480168;
    {
        (void)lift_sub(32, edx, 0x8007000eu, &fl);
    }
    if (fl.cf)
        goto L_4802fd;
    if (fl.cf || fl.zf)
        goto L_480264;
    {
        (void)lift_sub(32, edx, 0x80070057u, &fl);
    }
    if (fl.zf)
        goto L_4801e6;
    goto L_4802fd;
L_480710:
    if (fl.cf || fl.zf)
        goto L_48026b;
    {
        (void)lift_sub(32, edx, 0x80004001u, &fl);
    }
    if (fl.zf)
        goto L_4802b1;
    goto L_4802fd;
}

uint32_t lifted_string_append_calls(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_STRING_APPEND_CALLS_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_STRING_APPEND_CALLS_STACK, 0, entry);
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
    edx = 0x5109ceu;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    edx = (ebx + ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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

uint32_t lifted_text_wrap(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_TEXT_WRAP_STACK + 4 + 4 * 10 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_TEXT_WRAP_STACK, 10, entry);
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
    esp = esp - 0x60u;
    esi = lift_load(&env, ebp, 0xcu, 4);
    edi = lift_load(&env, ebp, 0x10u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    lift_store(&env, ebp, 0xffffffacu, 4, edx);
    lift_store(&env, ebp, 0xfffffff4u, 1, (ebx & 0xffu));
    eax = (ebp + 0xffffff98u);
    edx = 0x4ec1ecu;
    ebx = 0x517b68u;
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
    lift_store(&env, ebp, 0xffffff9cu, 4, edx);
    lift_store(&env, ebp, 0xffffffa0u, 4, ebx);
    eax = eax ^ eax;
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = lift_load(&env, ebp, 0xffffffacu, 4);
    ebx = ebx + 0x15cu;
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    lift_store(&env, edx, 0x160u, 1, (eax & 0xffu));
    eax = edx;
    lift_store(&env, edx, 0xeu, 2, (ecx & 0xffffu));
    edx = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, eax, 0x16u, 2, (edx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)(esi & 0xffffu);
    lift_store(&env, edx, 0xf4u, 4, eax);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)(edi & 0xffffu);
    lift_store(&env, edx, 0xf8u, 4, eax);
    eax = lift_load(&env, ebp, 0x14u, 4);
    lift_store(&env, edx, 0x2f2u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0x18u, 4);
    lift_store(&env, edx, 0x2f4u, 2, (eax & 0xffffu));
    eax = edx;
    edx = lift_load(&env, ebp, 0x1cu, 4);
    lift_store(&env, eax, 0x2f6u, 2, (edx & 0xffffu));
    edx = lift_load(&env, ebp, 0x20u, 4);
    lift_store(&env, eax, 0x2f8u, 2, (edx & 0xffffu));
    edx = lift_load(&env, ebp, 0x24u, 4);
    lift_store(&env, eax, 0x2fcu, 4, edx);
    edx = lift_load(&env, ebp, 0x28u, 4);
    lift_store(&env, eax, 0x300u, 4, edx);
    edx = lift_load(&env, ebp, 0x2cu, 4);
    edi = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, eax, 0x304u, 4, edx);
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
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    lift_store(&env, eax, 0x161u, 1, 0x0u);
    eax = lift_load(&env, ebp, 0x14u, 4);
    eax = eax + lift_load(&env, ebp, 0x18u, 4);
    esi = esi - eax;
    lift_store(&env, ebp, 0xffffffecu, 4, esi);
    lift_store(&env, ebp, 0xffffffb4u, 4, 0x1u);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b26bf;
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = edx;
    ecx = ecx + edx;
L_4b26b4:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4b27ca;
L_4b26bf:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + 0x15cu;
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = eax + edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
L_4b26d5:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffd8u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4b28f6;
    edi = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = ecx ^ ecx;
    esi = eax;
    lift_store(&env, ebp, 0xfffffff0u, 2, (ecx & 0xffffu));
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (!fl.cf)
        goto L_4b276d;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    edi = (esi + eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
L_4b2700:
    {
        (void)lift_sub(8, lift_load(&env, edi, 0x0u, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4b276d;
    edx = 0x511083u;
    eax = (ebp + 0xffffffb8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    eax = (ebp + 0xffffffb8u);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edi, 0x0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca630u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffc0u);
    ecx = (ebp + 0xffffffbcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = ebx ^ ebx;
    edi = edi + 1u;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x44u, 1)) & 0xffu);
    eax = lift_load(&env, eax, 0x15du, 4);
    edx = lift_load(&env, ebp, 0xffffffb8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    esi = esi + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x440610u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = edx + eax;
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xfffffff0u, 2, (edx & 0xffffu));
    edx = edx ^ edx;
    eax = (ebp + 0xffffffb8u);
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffa4u, 4, ecx);
    {
        (void)lift_sub(32, edi, ebx, &fl);
    }
    if (fl.cf)
        goto L_4b2700;
L_4b276d:
    eax = eax ^ eax;
    edx = lift_load(&env, ebp, 0xffffffeeu, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe8u, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    edx = edx + eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b27df;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x161u, 1)) & 0xffu);
    eax = eax + eax;
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    esi = (esi & 0xffff0000u) | ((lift_load(&env, eax, 0x162u, 2)) & 0xffffu);
    edx = edx - esi;
    lift_store(&env, eax, 0x22au, 2, (edx & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = 0x1u;
    edi = edi ^ edi;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x161u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) + 1u) & 0xffu);
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    lift_store(&env, eax, 0x161u, 1, (ebx & 0xffu));
    goto L_4b26d5;
L_4b27ca:
    edi = lift_load(&env, ebp, 0xffffffe4u, 4);
    edi = edi + 1u;
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.cf)
        goto L_4b26b4;
    goto L_4b26bf;
L_4b27df:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffb4u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b2803;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x161u, 1)) & 0xffu);
    eax = eax + eax;
    ecx = ecx ^ ecx;
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    lift_store(&env, eax, 0x162u, 2, (edx & 0xffffu));
L_4b2803:
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    ecx = ecx ^ ecx;
    ebx = ebx + eax;
    lift_store(&env, ebp, 0xfffffff0u, 2, (ecx & 0xffffu));
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (!fl.cf)
        goto L_4b2885;
L_4b281e:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, eax + 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4b2885;
    edx = 0x511084u;
    eax = (ebp + 0xffffffc4u);
    ebx = 0x3u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffccu);
    lift_store(&env, ebp, 0xffffffa4u, 4, ebx);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = ebx ^ ebx;
    ecx = (ebp + 0xffffffc8u);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x44u, 1)) & 0xffu);
    eax = lift_load(&env, eax, 0x15du, 4);
    edx = lift_load(&env, ebp, 0xffffffc4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    esi = esi + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x440610u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    edi = edi ^ edi;
    edx = edx + eax;
    eax = (ebp + 0xffffffc4u);
    lift_store(&env, ebp, 0xfffffff0u, 2, (edx & 0xffffu));
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffa4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffa4u, 4, edi);
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.cf)
        goto L_4b281e;
L_4b2885:
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffeeu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe8u, 2)) & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx + eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b28e3;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x161u, 1)) & 0xffu);
    eax = eax + eax;
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = (edx & 0xffff0000u) | (((edx & 0xffffu) - lift_load(&env, eax, 0x162u, 2)) & 0xffffu);
    ebx = 0x1u;
    lift_store(&env, eax, 0x22au, 2, (edx & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, eax, 0x161u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) + 1u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    lift_store(&env, eax, 0x161u, 1, ((ebx >> 8) & 0xffu));
    goto L_4b26d5;
L_4b28e3:
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx + eax;
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    goto L_4b26d5;
L_4b28f6:
    {
        (void)lift_sub(16, lift_load(&env, ebp, 0xffffffe8u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b294e;
L_4b28fd:
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffb0u, 4, esi);
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    esi = esi + 0x15cu;
L_4b290e:
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x161u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffb0u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b29ba;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edi, 0x22au, 2)) & 0xffffu);
    eax = eax - 1u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b297b;
    ebx = edi;
L_4b2932:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b2987;
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, ebx, 0x162u, 2)) & 0xffffu);
    edx = lift_load(&env, esi, 0x0u, 4);
    ecx = ecx + eax;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, edx + 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4b2987;
    eax = eax - 1u;
    goto L_4b2932;
L_4b294e:
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x161u, 1)) & 0xffu);
    eax = eax + eax;
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, eax, 0x162u, 2)) & 0xffffu);
    edx = edx - ebx;
    lift_store(&env, eax, 0x22au, 2, (edx & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0x161u, 1, lift_load(&env, eax, 0x161u, 1) + 1u);
    goto L_4b28fd;
L_4b297b:
    ecx = lift_load(&env, ebp, 0xffffffb0u, 4);
    ecx = ecx + 1u;
    edi = edi + 0x2u;
    lift_store(&env, ebp, 0xffffffb0u, 4, ecx);
    goto L_4b290e;
L_4b2987:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b29a2;
    eax = eax + 1u;
    lift_store(&env, edi, 0x22au, 2, (eax & 0xffffu));
    ecx = lift_load(&env, ebp, 0xffffffb0u, 4);
    ecx = ecx + 1u;
    edi = edi + 0x2u;
    lift_store(&env, ebp, 0xffffffb0u, 4, ecx);
    goto L_4b290e;
L_4b29a2:
    lift_store(&env, edi, 0x22au, 2, 0x0u);
    ecx = lift_load(&env, ebp, 0xffffffb0u, 4);
    ecx = ecx + 1u;
    edi = edi + 0x2u;
    lift_store(&env, ebp, 0xffffffb0u, 4, ecx);
    goto L_4b290e;
L_4b29ba:
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
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

uint32_t lifted_f4c6020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C6020_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C6020_STACK, 0, entry);
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
    esp = esp - 0x30u;
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = lift_load(&env, eax, 0x1ccu, 4);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = lift_load(&env, eax, 0x58u, 4);
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4c6128;
    ecx = ecx ^ ecx;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, ecx);
    lift_store(&env, eax, 0x1cu, 4, ecx);
L_4c6051:
    esi = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffbcu, 4);
    edx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    esi = lift_load(&env, esi, 0x4u, 4);
    ebx = ebx + 0x100u;
    ecx = lift_load(&env, ecx, 0x78u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, edx, 0x18u, 4, eax);
    eax = lift_load(&env, edx, 0x14u, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    esi = esi ^ esi;
    edi = lift_load(&env, eax, 0x78u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c6162;
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
    lift_store(&env, ebp, 0xffffffc8u, 4, esi);
L_4c6096:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    edi = lift_load(&env, ebp, 0xffffffc4u, 4);
    edx = eax;
    edi = lift_load(&env, edi, 0x20u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffbcu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c60c0;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = lift_load(&env, eax, 0x18u, 4);
    eax = eax + edx;
    lift_store(&env, eax, 0x0u, 4, lift_load(&env, eax, 0x0u, 4) + 0xffu);
L_4c60c0:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffc8u, 4);
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = lift_load(&env, eax, 0x18u, 4);
    edi = edi - 1u;
    eax = eax + ebx;
    esi = esi ^ esi;
    ecx = edi;
    eax = lift_load(&env, eax, 0x0u, 4);
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c5d60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_mul1(8, (ebx & 0xffu), &eax, &edx, &fl);
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xffffffe4u, 1, (eax & 0xffu));
L_4c60fe:
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c616c;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu) << 8);
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) + (eax & 0xffu)) & 0xffu) << 8);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffe4u, 1, ((ebx >> 8) & 0xffu));
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    ebx = eax;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c5d60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    goto L_4c60fe;
L_4c6128:
    ebx = 0x1feu;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, ebx);
    lift_store(&env, eax, 0x1cu, 4, edx);
    goto L_4c6051;
L_4c613b:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = edx + 0x4u;
    eax = eax + 0x4u;
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    ebx = lift_load(&env, edx, 0x78u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c6096;
L_4c6162:
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
L_4c616c:
    edi = edi + 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    esi = esi + 1u;
    lift_store(&env, edi, 0xffffffffu, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, esi, 0xffu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c60fe;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffbcu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c613b;
    eax = 0x1u;
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = ecx + eax;
    edx = edx - eax;
L_4c6191:
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x0u, 1, (ebx & 0xffu));
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = ecx + 1u;
    edx = edx - 1u;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebx, 0xffu, 1)) & 0xffu);
    eax = eax + 1u;
    lift_store(&env, ecx, 0xfeu, 1, (ebx & 0xffu));
    {
        (void)lift_sub(32, eax, 0x100u, &fl);
    }
    if (fl.zf)
        goto L_4c613b;
    goto L_4c6191;
}

uint32_t lifted_f4c6c80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C6C80_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C6C80_STACK, 0, entry);
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
    esp = esp - 0x50u;
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    ecx = lift_load(&env, eax, 0x4u, 4);
    ebx = 0x58u;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, edx, 0x1ccu, 4, eax);
    lift_store(&env, eax, 0x0u, 4, 0x4c6a20u);
    lift_store(&env, eax, 0x8u, 4, 0x4c6a80u);
    lift_store(&env, eax, 0xcu, 4, 0x4c6c70u);
    lift_store(&env, eax, 0x44u, 4, 0x0u);
    lift_store(&env, eax, 0x34u, 4, 0x0u);
    {
        (void)lift_sub(32, lift_load(&env, edx, 0x78u, 4), 0x4u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c6f49;
L_4c6cd2:
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x60u, 4), 0x100u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c6f70;
L_4c6ce2:
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
    eax = lift_load(&env, eax, 0x1ccu, 4);
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    eax = eax + 0x20u;
    ebx = 0x1u;
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    eax = lift_load(&env, edx, 0x78u, 4);
    lift_store(&env, ebp, 0xffffffb8u, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    ecx = ebx;
    edi = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = lift_load(&env, edx, 0x60u, 4);
    esi = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
L_4c6d16:
    ebx = ebx + 1u;
    eax = ecx;
    edx = ebx;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c6d27;
L_4c6d1f:
    {
        uint32_t r = lift_imul(32, edx, ebx, &fl);
        edx = r;
    }
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c6d1f;
L_4c6d27:
    {
        (void)lift_sub(32, edx, lift_load(&env, ebp, 0xffffffbcu, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c6d16;
    ebx = ebx - 1u;
    {
        (void)lift_sub(32, ebx, 0x2u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c6d50;
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x38u);
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffb8u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c6d50:
    ecx = 0x1u;
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = eax ^ eax;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c6d80;
    edx = lift_load(&env, ebp, 0xffffffb4u, 4);
    esi = lift_load(&env, ebp, 0xffffffccu, 4);
L_4c6d64:
    {
        uint32_t r = lift_imul(32, ecx, ebx, &fl);
        ecx = r;
    }
    edx = edx + 0x4u;
    eax = eax + 1u;
    lift_store(&env, edx, 0xfffffffcu, 4, ebx);
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c6d64;
L_4c6d80:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    edi = edi ^ edi;
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c6dc6;
    ebx = ebx ^ ebx;
L_4c6d90:
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x2cu, 4), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4c6fb8;
    eax = lift_load(&env, ebx, 0x4fffc0u, 4);
L_4c6da3:
    edi = lift_load(&env, ebp, 0xffffffb4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = ecx;
    edi = edi + eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    eax = ecx;
    lift_idiv1(32, lift_load(&env, edi, 0x0u, 4), &eax, &edx, &fl);
    edx = lift_load(&env, edi, 0x0u, 4);
    edx = edx + 1u;
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffbcu, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c6f94;
L_4c6dc6:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffc4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c6d80;
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    esi = lift_load(&env, eax, 0x78u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    {
        (void)lift_sub(32, esi, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4c6fbf;
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    lift_store(&env, eax, 0x18u, 4, ecx);
    edx = lift_load(&env, edx, 0x20u, 4);
    lift_store(&env, eax, 0x1cu, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    edx = lift_load(&env, edx, 0x24u, 4);
    lift_store(&env, eax, 0x20u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    edx = lift_load(&env, edx, 0x28u, 4);
    lift_store(&env, eax, 0x24u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffa8u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x5eu);
L_4c6e0d:
    ecx = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, ebp, 0xffffffa8u, 4);
    ecx = lift_load(&env, ebp, 0xffffffa8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = 0x1u;
    esi = lift_load(&env, esi, 0x4u, 4);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    ecx = lift_load(&env, ecx, 0x78u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    edi = edi ^ edi;
    edx = lift_load(&env, eax, 0x78u, 4);
    lift_store(&env, ebp, 0xffffffb0u, 4, edi);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c6f1b;
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
L_4c6e56:
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, eax, 0x20u, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = eax;
    ecx = lift_load(&env, ebp, 0xffffffc8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    edi = lift_load(&env, ebp, 0xffffffb0u, 4);
    ebx = ebx ^ ebx;
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    esi = eax;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c6efa;
    edi = edi + lift_load(&env, ebp, 0xffffffa0u, 4);
    eax = (ecx + 0xffffffffu);
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
L_4c6e96:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = eax;
    ecx = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        uint32_t r = lift_imul(32, eax, esi, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c6ee0;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
L_4c6eb9:
    edx = edx ^ edx;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c6ece;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
L_4c6ec2:
    eax = eax + 1u;
    ecx = lift_load(&env, edi, 0x0u, 4);
    edx = edx + 1u;
    lift_store(&env, ecx, eax + 0xffffffffu, 1, (ebx & 0xffu));
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c6ec2;
L_4c6ece:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = edx + eax;
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c6eb9;
L_4c6ee0:
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffc8u, 4);
    edx = edx + 0xffu;
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c6e96;
L_4c6efa:
    ecx = lift_load(&env, ebp, 0xffffffacu, 4);
    ebx = lift_load(&env, ebp, 0xffffffb0u, 4);
    edx = lift_load(&env, ebp, 0xffffffa8u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    ecx = ecx + 0x4u;
    ebx = ebx + 1u;
    esi = lift_load(&env, edx, 0x78u, 4);
    lift_store(&env, ebp, 0xffffffacu, 4, ecx);
    lift_store(&env, ebp, 0xffffffb0u, 4, ebx);
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c6e56;
L_4c6f1b:
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    lift_store(&env, edx, 0x10u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, edx, 0x14u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c6020u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x58u, 4), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4c6fd8;
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
L_4c6f49:
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x37u);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, eax, 0x18u, 4, 0x4u);
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c6cd2;
L_4c6f70:
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x39u);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, eax, 0x18u, 4, 0x100u);
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c6ce2;
L_4c6f94:
    edx = 0x1u;
    ecx = eax;
    ebx = ebx + 0x4u;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    esi = esi + edx;
    lift_store(&env, edi, 0x0u, 4, eax);
    edi = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c6d90;
    goto L_4c6dc6;
L_4c6fb8:
    eax = esi;
    goto L_4c6da3;
L_4c6fbf:
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x5fu);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, ecx);
    ecx = lift_load(&env, ebp, 0xffffffa8u, 4);
    goto L_4c6e0d;
L_4c6fd8:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c69c0u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4ec68c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC68C_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC68C_STACK, 0, entry);
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
    lift_store(&env, esp, 0xcu, 4, eax);
    edi = edx;
    ebp = ecx;
    eax = (ebx + 0xbu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xf8u) & 0xffu);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.cf)
        goto L_4ec6aa;
    eax = 0xffffffffu;
    goto L_4ec6b4;
L_4ec6aa:
    {
        (void)lift_sub(32, eax, 0x10u, &fl);
    }
    if (!fl.cf)
        goto L_4ec6b4;
    eax = 0x10u;
L_4ec6b4:
    edx = (edi + 0xfffffffcu);
    lift_store(&env, esp, 0x0u, 4, edx);
    edx = lift_load(&env, edx, 0x0u, 4);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xfeu) & 0xffu);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ec7d2;
    ecx = lift_load(&env, esp, 0x0u, 4);
    eax = eax - edx;
    ecx = ecx + edx;
L_4ec6ce:
    lift_store(&env, ebp, 0x0u, 4, eax);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ec6e2;
    ebx = 0x2u;
    goto L_4ec82f;
L_4ec6e2:
    {
        (void)lift_and(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4ec7c4;
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = lift_load(&env, ecx, 0x4u, 4);
    edx = 0u;
    lift_store(&env, esp, 0x4u, 4, eax);
    eax = 0x50aefcu;
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, esp, 0xcu, 2), &fl);
    }
    if (!fl.zf)
        goto L_4ec728;
    esi = lift_load(&env, 0u, 0x50aefcu, 4);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ec728;
L_4ec713:
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ec71f;
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax + esi;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ec728;
L_4ec71f:
    esi = lift_load(&env, esi, 0x8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ec713;
L_4ec728:
    edx = lift_load(&env, esi, 0xcu, 4);
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4ec735;
    eax = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, esi, 0xcu, 4, eax);
L_4ec735:
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0x0u, 4), &fl);
    }
    if (fl.cf)
        goto L_4ec746;
    eax = ebx;
    edx = lift_load(&env, ebp, 0x0u, 4);
    eax = eax - edx;
    {
        (void)lift_sub(32, eax, 0x10u, &fl);
    }
    if (!fl.cf)
        goto L_4ec77a;
L_4ec746:
    eax = lift_load(&env, esp, 0x4u, 4);
    edx = lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, eax, 0x8u, 4, edx);
    eax = edx;
    edx = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x4u, 4, edx);
    eax = lift_load(&env, esp, 0x0u, 4);
    lift_store(&env, eax, 0x0u, 4, lift_load(&env, eax, 0x0u, 4) + ebx);
    eax = lift_load(&env, esi, 0x1cu, 4);
    eax = eax - 1u;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    lift_store(&env, esi, 0x1cu, 4, eax);
    lift_store(&env, 0u, 0x5c8ac1u, 1, (edx & 0xffu));
    edx = lift_load(&env, ebp, 0x0u, 4);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.cf)
        goto L_4ec7b9;
    goto L_4ec82d;
L_4ec77a:
    ecx = ecx + edx;
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, ecx, 0x8u, 4, eax);
    eax = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x8u, 4, ecx);
    eax = lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, eax, 0x4u, 4, ecx);
    edx = lift_load(&env, esp, 0x0u, 4);
    eax = lift_load(&env, ebp, 0x0u, 4);
    ecx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx ^ ebx;
    ecx = ecx + eax;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, edx, 0x0u, 4, ecx);
    lift_store(&env, 0u, 0x5c8ac1u, 1, ((eax >> 8) & 0xffu));
    eax = ebx;
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
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
L_4ec7b9:
    eax = edx;
    eax = eax - ebx;
    ecx = ecx + ebx;
    goto L_4ec6ce;
L_4ec7c4:
    ebx = 0x1u;
    eax = ebx;
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
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
L_4ec7d2:
    edx = edx - eax;
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.cf)
        goto L_4ec82d;
    ebx = eax;
    ecx = lift_load(&env, esp, 0x0u, 4);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | 0x1u) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) | 0x1u) & 0xffu);
    lift_store(&env, ecx, 0x0u, 4, ebx);
    ebx = (ecx + eax);
    eax = 0x50aefcu;
    lift_store(&env, esp, 0x0u, 4, ebx);
    lift_store(&env, ebx, 0x0u, 4, edx);
    edx = 0u;
    ebx = lift_load(&env, esp, 0xcu, 4);
    {
        (void)lift_sub(16, (edx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4ec81f;
    esi = lift_load(&env, 0u, 0x50aefcu, 4);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ec81f;
L_4ec80a:
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ec816;
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax + esi;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ec81f;
L_4ec816:
    esi = lift_load(&env, esi, 0x8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ec80a;
L_4ec81f:
    lift_store(&env, esi, 0x18u, 4, lift_load(&env, esi, 0x18u, 4) + 1u);
    eax = lift_load(&env, esp, 0x0u, 4);
    eax = eax + 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ec82d:
    ebx = ebx ^ ebx;
L_4ec82f:
    eax = ebx;
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
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
