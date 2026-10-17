/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_16.h"

uint32_t lifted_f432480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F432480_STACK + 4 + 4 * 2 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F432480_STACK, 2, entry);
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
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffa4u, 4, ebx);
    lift_store(&env, ebp, 0xfffffff4u, 1, (ecx & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edi = 0x5407b8u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xfffffff0u, 1, (ecx & 0xffu));
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = edx ^ edx;
    ecx = 0x41u;
    lift_store(&env, ebp, 0xffffffa8u, 4, edx);
    lift_store(&env, eax, 0x0u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebx, 0x0u, 4, edx);
    eax = eax + 0x1deu;
    ebx = 0x41u;
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = lift_load(&env, ebp, 0xffffffa0u, 4);
    eax = eax + 0x220u;
    esi = lift_load(&env, ebp, 0xffffffa0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4327e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = ecx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    lift_string(&env, 0, 4, 3, &eax, &ecx, &esi, &edi, &fl);
    ecx = (ecx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_and(8, (ecx & 0xffu), 0x3u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_string(&env, 0, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    eax = 0x5406b0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x432840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xcu, 4);
    ecx = 0x1u;
    edx = 0x5406b0u;
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    eax = (ebp + 0xffffffecu);
    ebx = ebx ^ ebx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x434ee0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_43253b;
    eax = lift_load(&env, ebp, 0x8u, 4);
    ecx = 0x1u;
    lift_store(&env, eax, 0x0u, 4, 0x1u);
    eax = lift_load(&env, ebp, 0xcu, 4);
    lift_store(&env, ebp, 0xffffffa8u, 4, ecx);
    lift_store(&env, eax, 0x0u, 4, 0x1u);
L_43253b:
    ecx = (ebp + 0xffffffecu);
    edx = 0x5406b0u;
    ebx = ebx ^ ebx;
    eax = 0x5407b8u;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4346b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_43277c;
L_43255b:
    esi = esi ^ esi;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
    lift_store(&env, ebp, 0xffffffb8u, 4, esi);
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
L_43256c:
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    edx = lift_load(&env, ebp, 0xffffffb8u, 4);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    {
        uint32_t r = lift_imul(32, edx, 0x34u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    eax = eax + 0x10u;
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
L_432591:
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x324u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4325f7;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        (void)lift_sub(32, lift_load(&env, esi, eax + 0x220u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_432792;
L_4325ae:
    ecx = 0x1u;
    eax = edi;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffc4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = ecx + eax;
L_4325c3:
    edx = 0x1u;
    eax = lift_load(&env, ecx, 0x324u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0x324u, 4);
    lift_store(&env, eax, 0x15du, 1, 0x1u);
    edx = 0x4504e0u;
    eax = lift_load(&env, ecx, 0x324u, 4);
    ecx = ecx + 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4325c3;
L_4325f7:
    ebx = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = esi + 0x4u;
    edi = edi + 1u;
    ebx = ebx + 0x10u;
    eax = eax + 0x10u;
    lift_store(&env, ebp, 0xffffff9cu, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    {
        (void)lift_sub(32, edi, 0xdu, &fl);
    }
    if (fl.cf)
        goto L_432591;
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffbcu, 4);
    ebx = lift_load(&env, ebp, 0xffffffb8u, 4);
    edx = edx + 0x34u;
    ecx = ecx + 0xd0u;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffb0u, 4, edx);
    lift_store(&env, ebp, 0xffffffbcu, 4, ecx);
    lift_store(&env, ebp, 0xffffffb8u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_43256c;
    edi = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4327a5;
    lift_store(&env, ebp, 0xffffffa8u, 4, edi);
L_43264a:
    eax = eax ^ eax;
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    ecx = ecx ^ ecx;
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
L_432663:
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        uint32_t r = lift_imul(32, ebx, 0x34u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
L_43267d:
    esi = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = ((ecx * 4u));
    esi = esi + eax;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x220u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_432734;
    eax = eax + lift_load(&env, ebp, 0xffffff98u, 4);
    ebx = lift_load(&env, eax, 0x5406b0u, 4);
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_432734;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x0u, 4, lift_load(&env, eax, 0x0u, 4) + ebx);
    edx = ebx;
    eax = lift_load(&env, esi, 0x220u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esi, 0x220u, 4);
    lift_store(&env, eax, 0x15du, 1, 0x1u);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, esi, 0x220u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x1deu, 1)) & 0xffu);
    lift_store(&env, edx, 0x15cu, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x1deu, 1), 0x7u, &fl);
    }
    if (!fl.zf)
        goto L_4327bb;
    eax = lift_load(&env, ebp, 0xffffffd6u, 4);
    edi = (uint32_t)(int32_t)(int16_t)(uint16_t)(ecx & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ebx = edi;
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x430190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x450450u;
    lift_store(&env, esi, 0xbdcu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = edi;
    edx = lift_load(&env, ebp, 0xffffffa0u, 4);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4302a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_432721:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = 0x450330u;
    eax = lift_load(&env, eax, 0x220u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_432734:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ecx = ecx + 1u;
    eax = eax + 1u;
    edx = edx + 0x4u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    {
        (void)lift_sub(32, ecx, 0xdu, &fl);
    }
    if (fl.cf)
        goto L_43267d;
    ecx = lift_load(&env, ebp, 0xffffffacu, 4);
    ebx = lift_load(&env, ebp, 0xffffffb4u, 4);
    esi = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = ecx + 0xdu;
    ebx = ebx + 0x34u;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffffacu, 4, ecx);
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    {
        (void)lift_sub(32, esi, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_432663;
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
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
L_43277c:
    ebx = 0x1u;
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, ebp, 0xffffffa8u, 4, ebx);
    lift_store(&env, eax, 0x0u, 4, 0x1u);
    goto L_43255b;
L_432792:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, esi, eax + 0x5406b0u, 4, 0x1u);
    goto L_4325ae;
L_4327a5:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffa8u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_43264a;
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
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
L_4327bb:
    edx = lift_load(&env, ebp, 0xffffffd6u, 4);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    esi = lift_load(&env, 0u, 0x532a70u, 4);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ecx & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax =
        lift_call(&env, lift_load(&env, 0u, (esi * 4u) + 0x4fb7b0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_432721;
}
