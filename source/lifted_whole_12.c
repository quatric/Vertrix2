/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_12.h"

uint32_t lifted_f4bf940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4BF940_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4BF940_STACK, 0, entry);
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
    esp = esp - 0x16cu;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x1a0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4bf9ed;
L_4bf95e:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, eax, 0x1b8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4bfa80;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = lift_load(&env, edx, 0x18u, 4);
    ebx = lift_load(&env, ecx, 0x4u, 4);
    esi = lift_load(&env, ecx, 0x0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4bf992;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    esi = lift_load(&env, ecx, 0x0u, 4);
    ebx = lift_load(&env, ecx, 0x4u, 4);
L_4bf992:
    esi = esi + 1u;
    ebx = ebx - 1u;
    edi = lift_load(&env, esi, 0xffffffffu, 1);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4bf9ae;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    esi = lift_load(&env, ecx, 0x0u, 4);
    ebx = lift_load(&env, ecx, 0x4u, 4);
L_4bf9ae:
    eax = eax ^ eax;
    ebx = ebx - 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
    {
        (void)lift_sub(32, edi, 0xffu, &fl);
    }
    if (fl.zf)
        goto L_4bfa64;
L_4bf9c3:
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x35u);
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, edi);
    eax = lift_load(&env, edx, 0x0u, 4);
    edi = lift_load(&env, ebp, 0xffffffa8u, 4);
    lift_store(&env, eax, 0x1cu, 4, edi);
    edi = lift_load(&env, edx, 0x0u, 4);
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4bf9df:
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    lift_store(&env, edx, 0x1a0u, 4, eax);
    lift_store(&env, ecx, 0x0u, 4, esi);
    lift_store(&env, ecx, 0x4u, 4, ebx);
L_4bf9ed:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, eax, 0x1a0u, 4);
    {
        (void)lift_sub(32, eax, 0xd6u, &fl);
    }
    if (!fl.cf)
        goto L_4c039b;
    {
        (void)lift_sub(32, eax, 0xcau, &fl);
    }
    if (!fl.cf)
        goto L_4c0712;
    {
        (void)lift_sub(32, eax, 0xc4u, &fl);
    }
    if (!fl.cf)
        goto L_4c074b;
    {
        (void)lift_sub(32, eax, 0xc1u, &fl);
    }
    if (!fl.cf)
        goto L_4c0782;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.cf)
        goto L_4c07b5;
L_4bfa2b:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x44u);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = lift_load(&env, eax, 0x1a0u, 4);
    lift_store(&env, edx, 0x18u, 4, eax);
L_4bfa48:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4bfa52:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x1a0u, 4, 0x0u);
    goto L_4bf95e;
L_4bfa64:
    {
        (void)lift_sub(32, eax, 0xd8u, &fl);
    }
    if (!fl.zf)
        goto L_4bf9c3;
    goto L_4bf9df;
L_4bfa74:
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
L_4bfa80:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bf770u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bf9ed;
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
L_4bfa9a:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x3du);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c03ed;
L_4bfaae:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4be0b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bfa52;
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
L_4bfac8:
    edx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4be0b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bfa52;
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
L_4bfae9:
    ebx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4be0b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bfa52;
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
L_4bfb0a:
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ecx, 0x18u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    ebx = lift_load(&env, eax, 0x0u, 4);
    esi = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, ecx, 0x1b8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4bfc94;
L_4bfb28:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4bfca8;
L_4bfb30:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    esi = esi - 1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4bfb55;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
L_4bfb55:
    eax = eax ^ eax;
    edx = lift_load(&env, ebp, 0xffffffa0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    esi = esi - 1u;
    edx = edx + eax;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffa0u, 4, edx);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4bfb7c;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
L_4bfb7c:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x67u);
    eax = lift_load(&env, ecx, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    edi = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    esi = esi - 1u;
    eax = eax + eax;
    edi = lift_load(&env, ebp, 0xffffffa0u, 4);
    eax = eax + 0x6u;
    ebx = ebx + 1u;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.zf)
        goto L_4bfcc2;
L_4bfbb5:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0xbu);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4bfbc4:
    edi = edi ^ edi;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, edi);
    lift_store(&env, ecx, 0x148u, 4, eax);
L_4bfbd2:
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffc0u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4bfd04;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4bfbf7;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
L_4bfbf7:
    eax = eax ^ eax;
    esi = esi - 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4bfc19;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
L_4bfc19:
    eax = eax ^ eax;
    esi = esi - 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffff94u, 4, eax);
    eax = eax ^ eax;
    edx = lift_load(&env, ecx, 0xd8u, 4);
L_4bfc2a:
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ecx, 0x24u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4bfce8;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4bfcdc;
L_4bfc44:
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    lift_store(&env, ecx, (eax * 4u) + 0x14cu, 4, edx);
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax & 0xfu;
    lift_store(&env, edx, 0x14u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    eax = eax & 0xfu;
    lift_store(&env, edx, 0x18u, 4, eax);
    eax = lift_load(&env, ecx, 0x0u, 4);
    edi = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, eax, 0x18u, 4, edi);
    edi = lift_load(&env, edx, 0x14u, 4);
    lift_store(&env, eax, 0x1cu, 4, edi);
    edx = lift_load(&env, edx, 0x18u, 4);
    lift_store(&env, eax, 0x20u, 4, edx);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x68u);
    edi = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 4, lift_load(&env, ebp, 0xffffffb4u, 4) + 1u);
    goto L_4bfbd2;
L_4bfc94:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x3eu);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4bfb28;
L_4bfca8:
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    goto L_4bfb30;
L_4bfcc2:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bfbb5;
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4bfbb5;
    goto L_4bfbc4;
L_4bfcdc:
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = eax + 1u;
    edx = edx + 0x54u;
    goto L_4bfc2a;
L_4bfce8:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x5u);
    eax = lift_load(&env, ecx, 0x0u, 4);
    edi = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, eax, 0x18u, 4, edi);
    edi = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4bfc44;
L_4bfd04:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4bfd1d;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
L_4bfd1d:
    eax = eax ^ eax;
    esi = esi - 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ebx = ebx + 1u;
    lift_store(&env, ecx, 0x190u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4bfd42;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
L_4bfd42:
    eax = eax ^ eax;
    esi = esi - 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ebx = ebx + 1u;
    lift_store(&env, ecx, 0x194u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4bfd67;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
L_4bfd67:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        edx = r;
    }
    eax = eax & 0xfu;
    edx = edx & 0xfu;
    lift_store(&env, ecx, 0x19cu, 4, eax);
    lift_store(&env, ecx, 0x198u, 4, edx);
    eax = lift_load(&env, ecx, 0x0u, 4);
    edx = lift_load(&env, ecx, 0x190u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    edx = lift_load(&env, ecx, 0x194u, 4);
    lift_store(&env, eax, 0x1cu, 4, edx);
    edx = lift_load(&env, ecx, 0x198u, 4);
    lift_store(&env, eax, 0x20u, 4, edx);
    edx = lift_load(&env, ecx, 0x19cu, 4);
    lift_store(&env, eax, 0x24u, 4, edx);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x69u);
    edi = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0x1b8u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x0u);
    edi = lift_load(&env, ecx, 0x90u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ecx, 0x90u, 4, edi);
    {
        uint32_t a = esi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        esi = r;
    }
    lift_store(&env, eax, 0x0u, 4, ebx);
    lift_store(&env, eax, 0x4u, 4, esi);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x1a0u, 4, 0x0u);
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
L_4bfdfd:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x55u);
    ecx = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x1a0u, 4, 0x0u);
    eax = 0x2u;
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
L_4bfe35:
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebx, 0x18u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c005f;
L_4bfe54:
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    edi = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = (edx + 0x1u);
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    if (fl.zf)
        goto L_4c007f;
L_4bfe74:
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    edi = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = eax ^ eax;
    ecx = ecx - 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    esi = (edx + 0x1u);
    edi = edi + eax;
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    eax = (edi + 0xfffffffeu);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
L_4bfe96:
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c0144;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4bfec3;
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
L_4bfec3:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x50u);
    eax = lift_load(&env, ebx, 0x0u, 4);
    edi = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = 0x1u;
    lift_store(&env, eax, 0x18u, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = edi - 1u;
    eax = eax + 1u;
    esi = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = ebx;
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffff80u, 1, ((eax >> 8) & 0xffu));
L_4bfefe:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4bff1f;
    edi = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    eax = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
L_4bff1f:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = edx + 1u;
    edi = edi - 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    lift_store(&env, edx, ebp + 0xffffff7fu, 1, (eax & 0xffu));
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax ^ eax;
    edi = edi + 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffff7fu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    esi = esi + eax;
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bfefe;
    lift_store(&env, ebp, 0xffffffd0u, 4, lift_load(&env, ebp, 0xffffffd0u, 4) - 0x11u);
    eax = eax ^ eax;
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff81u, 1)) & 0xffu);
    lift_store(&env, edx, 0x18u, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff82u, 1)) & 0xffu);
    lift_store(&env, edx, 0x1cu, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff83u, 1)) & 0xffu);
    lift_store(&env, edx, 0x20u, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff84u, 1)) & 0xffu);
    lift_store(&env, edx, 0x24u, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff85u, 1)) & 0xffu);
    lift_store(&env, edx, 0x28u, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff86u, 1)) & 0xffu);
    lift_store(&env, edx, 0x2cu, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff87u, 1)) & 0xffu);
    lift_store(&env, edx, 0x30u, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff88u, 1)) & 0xffu);
    lift_store(&env, edx, 0x34u, 4, eax);
    eax = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x56u);
    edi = lift_load(&env, ebx, 0x0u, 4);
    edx = 0x2u;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff89u, 1)) & 0xffu);
    lift_store(&env, edx, 0x18u, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff8au, 1)) & 0xffu);
    lift_store(&env, edx, 0x1cu, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff8bu, 1)) & 0xffu);
    lift_store(&env, edx, 0x20u, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff8cu, 1)) & 0xffu);
    lift_store(&env, edx, 0x24u, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff8du, 1)) & 0xffu);
    lift_store(&env, edx, 0x28u, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff8eu, 1)) & 0xffu);
    lift_store(&env, edx, 0x2cu, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff8fu, 1)) & 0xffu);
    lift_store(&env, edx, 0x30u, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff90u, 1)) & 0xffu);
    lift_store(&env, edx, 0x34u, 4, eax);
    eax = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x56u);
    edi = lift_load(&env, ebx, 0x0u, 4);
    edx = 0x2u;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, esi, 0x100u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c009f;
L_4c0008:
    eax = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x8u);
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c0017:
    edi = edi ^ edi;
L_4c0019:
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c00ad;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c0042;
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
L_4c0042:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = edi + 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, edi, ebp + 0xfffffe7fu, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = edx + 1u;
    eax = eax - 1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    goto L_4c0019;
L_4c005f:
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    goto L_4bfe54;
L_4c007f:
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    goto L_4bfe74;
L_4c009f:
    {
        (void)lift_sub(32, esi, lift_load(&env, ebp, 0xffffffd0u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c0008;
    goto L_4c0017;
L_4c00ad:
    lift_store(&env, ebp, 0xffffffd0u, 4, lift_load(&env, ebp, 0xffffffd0u, 4) - esi);
    {
        (void)lift_and(8, (ecx & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4c0135;
    ecx = ecx - 0x10u;
    edx = (ebx + 0xc4u);
    eax = ((ecx * 4u));
L_4c00c9:
    edx = edx + eax;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c00d4;
    {
        (void)lift_sub(32, ecx, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c00e8;
L_4c00d4:
    eax = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x1eu);
    eax = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, ecx);
    ecx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c00e8:
    {
        (void)lift_sub(32, lift_load(&env, edx, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c00f6;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b9200u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edx, 0x0u, 4, eax);
L_4c00f6:
    ecx = 0x11u;
    esi = (ebp + 0xffffff80u);
    edi = lift_load(&env, edx, 0x0u, 4);
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
    ecx = 0x100u;
    edi = lift_load(&env, edx, 0x0u, 4);
    esi = (ebp + 0xfffffe80u);
    edi = edi + 0x11u;
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
    goto L_4bfe96;
L_4c0135:
    eax = ((ecx * 4u));
    edx = (ebx + 0xb4u);
    goto L_4c00c9;
L_4c0144:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4c0157;
    eax = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0xbu);
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c0157:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, edx, 0x4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x1a0u, 4, 0x0u);
    goto L_4bf95e;
L_4c017a:
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    goto L_4c0525;
L_4c0194:
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    goto L_4c0539;
L_4c01ae:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4c01ca;
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    esi = lift_load(&env, esi, 0x4u, 4);
L_4c01ca:
    eax = eax ^ eax;
    esi = esi - 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    goto L_4c064e;
L_4c01d8:
    if (fl.zf)
        goto L_4c01e9;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0xbu);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c01e9:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x0u, 4, ebx);
    lift_store(&env, eax, 0x4u, 4, esi);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x1a0u, 4, 0x0u);
    goto L_4bf95e;
L_4c0203:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = lift_load(&env, eax, 0x18u, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    ecx = lift_load(&env, esi, 0x4u, 4);
    ebx = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4c02dc;
L_4c0219:
    edx = edx ^ edx;
    ecx = ecx - 1u;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ebx = ebx + 1u;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4c02f1;
L_4c022a:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ecx = ecx - 1u;
    edx = edx + eax;
    ebx = ebx + 1u;
    {
        (void)lift_sub(32, edx, 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4c024d;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, eax, 0x14u, 4, 0xbu);
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c024d:
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4c0264;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, esi, 0x0u, 4);
    ecx = lift_load(&env, esi, 0x4u, 4);
L_4c0264:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ecx = ecx - 1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4c0287;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, esi, 0x0u, 4);
    ecx = lift_load(&env, esi, 0x4u, 4);
L_4c0287:
    eax = eax ^ eax;
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x52u);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edi = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    lift_store(&env, ebp, 0xffffffb0u, 4, edx);
    edi = lift_load(&env, edi, 0x0u, 4);
    edx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    ebx = ebx + 1u;
    lift_store(&env, edx, 0x114u, 4, eax);
    ecx = ecx - 1u;
    lift_store(&env, esi, 0x0u, 4, ebx);
    lift_store(&env, esi, 0x4u, 4, ecx);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x1a0u, 4, 0x0u);
    goto L_4bf95e;
L_4c02dc:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, esi, 0x0u, 4);
    ecx = lift_load(&env, esi, 0x4u, 4);
    goto L_4c0219;
L_4c02f1:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, esi, 0x0u, 4);
    ecx = lift_load(&env, esi, 0x4u, 4);
    goto L_4c022a;
L_4c0309:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, eax, 0x1a0u, 4);
    edx = lift_load(&env, edx, 0x1b8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xfffffca0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bfa52;
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
L_4c033b:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, edx, 0x1b8u, 4);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x1cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bfa52;
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
L_4c035c:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x5cu);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = lift_load(&env, eax, 0x1a0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, edx, 0x18u, 4, eax);
    ecx = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x1a0u, 4, 0x0u);
    goto L_4bf95e;
L_4c039b:
    if (fl.cf || fl.zf)
        goto L_4c035c;
    {
        (void)lift_sub(32, eax, 0xe4u, &fl);
    }
    if (!fl.cf)
        goto L_4c0489;
    {
        (void)lift_sub(32, eax, 0xdcu, &fl);
    }
    if (!fl.cf)
        goto L_4c04d2;
    {
        (void)lift_sub(32, eax, 0xd9u, &fl);
    }
    if (!fl.cf)
        goto L_4c04fe;
    {
        (void)lift_sub(32, eax, 0xd7u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c035c;
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x66u);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0x1b8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4bfa9a;
L_4c03ed:
    eax = eax ^ eax;
L_4c03ef:
    edx = (ecx + eax);
    lift_store(&env, edx, 0xe4u, 1, 0x0u);
    lift_store(&env, edx, 0xf4u, 1, 0x1u);
    eax = eax + 1u;
    lift_store(&env, edx, 0x104u, 1, 0x5u);
    {
        (void)lift_sub(32, eax, 0x10u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c03ef;
    lift_store(&env, ecx, 0x114u, 4, 0x0u);
    lift_store(&env, ecx, 0x28u, 4, 0x0u);
    lift_store(&env, ecx, 0x12cu, 4, 0x0u);
    lift_store(&env, ecx, 0x118u, 4, 0x0u);
    lift_store(&env, ecx, 0x11cu, 1, 0x1u);
    lift_store(&env, ecx, 0x11du, 1, 0x1u);
    lift_store(&env, ecx, 0x11eu, 1, 0x0u);
    lift_store(&env, ecx, 0x120u, 2, 0x1u);
    lift_store(&env, ecx, 0x122u, 2, 0x1u);
    lift_store(&env, ecx, 0x124u, 4, 0x0u);
    eax = lift_load(&env, ecx, 0x1b8u, 4);
    lift_store(&env, ecx, 0x128u, 1, 0x0u);
    lift_store(&env, eax, 0xcu, 4, 0x1u);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x1a0u, 4, 0x0u);
    goto L_4bf95e;
L_4c0489:
    if (fl.cf || fl.zf)
        goto L_4c0309;
    {
        (void)lift_sub(32, eax, 0xeau, &fl);
    }
    if (fl.cf)
        goto L_4c0309;
    if (fl.cf || fl.zf)
        goto L_4c0309;
    {
        (void)lift_sub(32, eax, 0xedu, &fl);
    }
    if (fl.cf)
        goto L_4c0309;
    if (fl.cf || fl.zf)
        goto L_4c0309;
    {
        (void)lift_sub(32, eax, 0xefu, &fl);
    }
    if (fl.cf)
        goto L_4c0309;
    if (fl.cf || fl.zf)
        goto L_4c0309;
    {
        (void)lift_sub(32, eax, 0xfeu, &fl);
    }
    if (fl.zf)
        goto L_4c033b;
    goto L_4bfa2b;
L_4c04d2:
    if (fl.cf || fl.zf)
        goto L_4c0731;
    {
        (void)lift_sub(32, eax, 0xe1u, &fl);
    }
    if (!fl.cf)
        goto L_4c0309;
    {
        (void)lift_sub(32, eax, 0xddu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c0203;
    {
        (void)lift_sub(32, eax, 0xe0u, &fl);
    }
    if (fl.zf)
        goto L_4c0309;
    goto L_4bfa2b;
L_4c04fe:
    if (fl.cf || fl.zf)
        goto L_4bfdfd;
    {
        (void)lift_sub(32, eax, 0xdau, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4bfb0a;
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ecx, 0x18u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    esi = lift_load(&env, eax, 0x4u, 4);
    ebx = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4c017a;
L_4c0525:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    esi = esi - 1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4c0194;
L_4c0539:
    eax = eax ^ eax;
    edi = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    edi = edi + eax;
    esi = esi - 1u;
    lift_store(&env, ebp, 0xffffffc8u, 4, edi);
    eax = (edi + 0xfffffffeu);
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
L_4c054d:
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c01d8;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4c0571;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    ebx = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
L_4c0571:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    lift_store(&env, ebp, 0xffffffc4u, 4, lift_load(&env, ebp, 0xffffffc4u, 4) & 0xfu);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x51u);
    eax = lift_load(&env, ecx, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    eax = lift_load(&env, ecx, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, eax, 0x1cu, 4, edx);
    edx = 0x1u;
    edi = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    esi = esi - 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffc4u, 4);
    ebx = ebx + 1u;
    {
        (void)lift_sub(32, edx, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c05c5;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x1fu);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c05c5:
    edx = lift_load(&env, ebp, 0xffffffc4u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    edx = edx + ecx;
    {
        (void)lift_sub(32, lift_load(&env, edx, 0xa4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c05e3;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b91e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edx, 0xa4u, 4, eax);
L_4c05e3:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    eax = lift_load(&env, ecx, (eax * 4u) + 0xa4u, 4);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
L_4c05f2:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffa4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c01ae;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4c0618;
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    esi = lift_load(&env, esi, 0x4u, 4);
L_4c0618:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    esi = esi - 1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4c0640;
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bfa74;
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    esi = lift_load(&env, esi, 0x4u, 4);
L_4c0640:
    eax = eax ^ eax;
    edi = lift_load(&env, ebp, 0xffffffb8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    esi = esi - 1u;
    edi = edi + eax;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffb8u, 4, edi);
L_4c064e:
    eax = lift_load(&env, 0u, (edx * 4u) + 0x5000d0u, 4);
    edi = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = eax + eax;
    eax = eax + edi;
    edi = lift_load(&env, ebp, 0xffffffb8u, 4);
    edx = edx + 1u;
    lift_store(&env, eax, 0x0u, 2, (edi & 0xffffu));
    {
        (void)lift_sub(32, edx, 0x40u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c05f2;
    eax = lift_load(&env, ecx, 0x0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x68u, 4), 0x2u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c06f3;
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffbcu, 4, edi);
L_4c0679:
    edx = lift_load(&env, ebp, 0xffffffbcu, 4);
    edi = lift_load(&env, ebp, 0xffffff98u, 4);
    edx = edx + edx;
    edx = edx + edi;
    edi = edi ^ edi;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, edi);
    edi = edi ^ edi;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, edx, 0x2u, 2)) & 0xffffu);
    lift_store(&env, eax, 0x1cu, 4, edi);
    edi = edi ^ edi;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, edx, 0x4u, 2)) & 0xffffu);
    lift_store(&env, eax, 0x20u, 4, edi);
    edi = edi ^ edi;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, edx, 0x6u, 2)) & 0xffffu);
    lift_store(&env, eax, 0x24u, 4, edi);
    edi = edi ^ edi;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, edx, 0x8u, 2)) & 0xffffu);
    lift_store(&env, eax, 0x28u, 4, edi);
    edi = edi ^ edi;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, edx, 0xau, 2)) & 0xffffu);
    lift_store(&env, eax, 0x2cu, 4, edi);
    edi = edi ^ edi;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, edx, 0xcu, 2)) & 0xffffu);
    lift_store(&env, eax, 0x30u, 4, edi);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0xeu, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    lift_store(&env, eax, 0x34u, 4, edx);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x5du);
    edi = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x2u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    eax = eax + 0x8u;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    {
        (void)lift_sub(32, eax, 0x40u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c0679;
L_4c06f3:
    edi = lift_load(&env, ebp, 0xffffffc8u, 4);
    edi = edi - 0x41u;
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, edi);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c054d;
    edx = (edi + 0xffffffc0u);
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    goto L_4c054d;
L_4c0712:
    if (fl.cf || fl.zf)
        goto L_4bfae9;
    {
        (void)lift_sub(32, eax, 0xd0u, &fl);
    }
    if (!fl.cf)
        goto L_4c035c;
    {
        (void)lift_sub(32, eax, 0xcdu, &fl);
    }
    if (!fl.cf)
        goto L_4c0793;
    {
        (void)lift_sub(32, eax, 0xcbu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c0793;
L_4c0731:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bf6a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bfa52;
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
L_4c074b:
    if (fl.cf || fl.zf)
        goto L_4bfe35;
    {
        (void)lift_sub(32, eax, 0xc7u, &fl);
    }
    if (fl.cf)
        goto L_4c0793;
    if (fl.cf || fl.zf)
        goto L_4c0793;
    {
        (void)lift_sub(32, eax, 0xc8u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c0793;
    ebx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4be0b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bfa52;
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
L_4c0782:
    if (fl.cf || fl.zf)
        goto L_4bfaae;
    {
        (void)lift_sub(32, eax, 0xc2u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4bfac8;
L_4c0793:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x3cu);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, edx, 0x1a0u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    goto L_4bfa48;
L_4c07b5:
    if (fl.cf || fl.zf)
        goto L_4c035c;
    {
        (void)lift_sub(32, eax, 0xc0u, &fl);
    }
    if (fl.zf)
        goto L_4bfaae;
    goto L_4bfa2b;
}

uint32_t lifted_f4cae30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CAE30_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CAE30_STACK, 0, entry);
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
    esp = esp - 0x34u;
    ebx = eax;
    lift_store(&env, esp, 0x30u, 4, edx);
    {
        (void)lift_and(8, lift_load(&env, esp, 0x30u, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4cae69;
    lift_store(&env, esp, 0x20u, 4, 0x1u);
    edx = 0x518bc0u;
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
    goto L_4cafc5;
L_4cae69:
    lift_store(&env, eax, 0x0u, 4, 0x518a94u);
    lift_store(&env, esp, 0x24u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0x30u, 1)) & 0xffu);
    lift_store(&env, esp, 0x28u, 1, (eax & 0xffu));
    eax = (esp + 0x14u);
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
    lift_store(&env, esp, 0x1cu, 4, 0x518944u);
    lift_store(&env, esp, 0x20u, 4, 0x3u);
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x78u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caebd;
    eax = lift_load(&env, ebx, 0x78u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4caebd;
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4caebd:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0xa0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caedb;
    eax = lift_load(&env, ebx, 0xa0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4caedb;
    ecx = lift_load(&env, eax, 0x1cu, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x14u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4caedb:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x14u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4caf2e;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c5c08u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caf0a;
    if (fl.zf)
        goto L_4caf00;
    eax = lift_load(&env, 0u, 0x5c5c08u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4caf00:
    lift_store(&env, 0u, 0x5c5c08u, 4, 0x0u);
L_4caf0a:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c5c04u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caf2e;
    if (fl.zf)
        goto L_4caf24;
    eax = lift_load(&env, 0u, 0x5c5c04u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4caf24:
    lift_store(&env, 0u, 0x5c5c04u, 4, 0x0u);
L_4caf2e:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x8cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caf42;
    {
        uint32_t v = lift_load(&env, ebx, 0x8cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dc4b0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4caf42:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x90u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caf56;
    {
        uint32_t v = lift_load(&env, ebx, 0x90u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dc4b0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4caf56:
    eax = lift_load(&env, ebx, 0xa8u, 2);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4caf69;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c10u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4caf69:
    eax = lift_load(&env, ebx, 0xaau, 2);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4caf7c;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c10u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4caf7c:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0xa4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4caf99;
    eax = lift_load(&env, ebx, 0xa4u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4caf99;
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4caf99:
    edx = 0x1u;
    eax = ebx;
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cbfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(8, lift_load(&env, esp, 0x30u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4cafbb;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4cafbb:
    eax = lift_load(&env, esp, 0x14u, 4);
    env.chain = eax;
L_4cafc5:
    eax = ebx;
    {
        uint32_t r = lift_add(32, esp, 0x34u, &fl);
        esp = r;
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

uint32_t lifted_f4cd819(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CD819_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CD819_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = eax;
    eax = lift_load(&env, ebx, 0x4u, 4);
    eax = eax + lift_load(&env, esi, 0x4u, 4);
    ebx = lift_load(&env, eax, 0x4u, 1);
    {
        (void)lift_and(32, ebx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4cd82c;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4cd82c:
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + lift_load(&env, esi, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC970_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC970_STACK, 0, entry);
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
    esp = esp - 0x40u;
    esi = eax;
    ecx = ebx;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x15u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x15u, 1)) & 0xffu);
    ebx = lift_load(&env, ebx, 0x8u, 4);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x5fu) & 0xffu);
    eax = eax & 0xffu;
    {
        (void)lift_sub(32, eax, 0x47u, &fl);
    }
    if (!fl.zf)
        goto L_4ec9ba;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4ec9a0;
    ebx = 0x1u;
L_4ec9a0:
    lift_store(&env, ebp, 0xffffffbcu, 4, 0x4u);
    edi = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = 0x1u;
    edi = edi - 0x2u;
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
    goto L_4ec9d9;
L_4ec9ba:
    {
        (void)lift_sub(32, eax, 0x45u, &fl);
    }
    if (!fl.zf)
        goto L_4ec9cc;
    edi = 0x1u;
    lift_store(&env, ebp, 0xffffffbcu, 4, edi);
    lift_store(&env, ebp, 0xffffffb8u, 4, edi);
    goto L_4ec9d9;
L_4ec9cc:
    edi = 0x2u;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffbcu, 4, edi);
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
L_4ec9d9:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4ec9e3;
    lift_store(&env, ebp, 0xffffffbcu, 1, lift_load(&env, ebp, 0xffffffbcu, 1) | 0x10u);
L_4ec9e3:
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x8u;
    lift_store(&env, edx, 0x0u, 4, eax);
    edx = eax;
    eax = lift_load(&env, eax, 0xfffffff8u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = lift_load(&env, edx, 0xfffffffcu, 4);
    edx = (ebp + 0xffffffe0u);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    eax = (ebp + 0xffffffecu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e53b4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4eca0d;
    ebx = 0x6u;
L_4eca0d:
    eax = (ebp + 0xffffffe0u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
    ebx = (esi + 0x1u);
    edx = (ebp + 0xffffffb4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eccb9u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, ecx, 0x28u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ecx, 0x2cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ecx, 0x30u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ecx, 0x34u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffc8u, 4), 0x0u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4eca50;
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x2du);
    goto L_4eca79;
L_4eca50:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4eca67;
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x2bu);
    goto L_4eca79;
L_4eca67:
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4eca79;
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x20u);
L_4eca79:
    edx = 0u;
    eax = esi;
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
}
