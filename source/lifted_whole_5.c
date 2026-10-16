/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_5.h"

uint32_t lifted_wave_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_WAVE_LOAD_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_WAVE_LOAD_STACK, 0, entry);
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
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4b7ea1;
    eax = 0x2u;
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
L_4b7ea1:
    eax = 0x1u;
    lift_store(&env, edx, 0x0u, 4, 0x0u);
    edx = 0x18u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b7eca;
    eax = 0x8u;
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
L_4b7eca:
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bd850u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bd854u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bd858u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x5bd854u, 4);
    ecx = lift_load(&env, 0u, 0x5bd854u, 4);
    eax = eax & 0x1u;
    ecx = ecx + eax;
    ebx = lift_load(&env, 0u, 0x5bd850u, 4);
    lift_store(&env, 0u, 0x5bd854u, 4, ecx);
    {
        (void)lift_sub(32, ebx, 0x46464952u, &fl);
    }
    if (!fl.zf)
        goto L_4b807e;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bd858u, 4), 0x45564157u, &fl);
    }
    if (!fl.zf)
        goto L_4b807e;
    ebx = 0x10u;
    eax = 0x5bd868u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x5bd854u, 4);
    {
        uint32_t r = lift_sub(32, edx, 0x4u, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x5bd854u, 4, edx);
    if (fl.zf)
        goto L_4b8070;
L_4b7f6a:
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bd860u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bd864u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x5bd864u, 4);
    edx = lift_load(&env, 0u, 0x5bd864u, 4);
    eax = eax & 0x1u;
    edx = edx + eax;
    ecx = lift_load(&env, 0u, 0x5bd854u, 4);
    lift_store(&env, 0u, 0x5bd864u, 4, edx);
    eax = (edx + 0x8u);
    ecx = ecx - eax;
    ebx = lift_load(&env, 0u, 0x5bd860u, 4);
    lift_store(&env, 0u, 0x5bd854u, 4, ecx);
    {
        (void)lift_sub(32, ebx, 0x20746d66u, &fl);
    }
    if (!fl.zf)
        goto L_4b8093;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd868u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd86au;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bd86cu;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bd870u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd874u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd876u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x5bd864u, 4);
    eax = esi;
    edx = edx - 0x10u;
L_4b805e:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aa90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bd854u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b7f6a;
L_4b8070:
    eax = 0xbu;
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
L_4b807e:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b8170u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0xbu;
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
L_4b8093:
    {
        (void)lift_sub(32, ebx, 0x61746164u, &fl);
    }
    if (!fl.zf)
        goto L_4b815f;
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x5bd868u, 2), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b807e;
    eax = lift_load(&env, 0u, 0x5bd864u, 4);
    lift_store(&env, edi, 0x8u, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd86cu, 2)) & 0xffffu);
    lift_store(&env, edi, 0x16u, 2, 0x0u);
    lift_store(&env, edi, 0x14u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x5bd876u, 2), 0x8u, &fl);
    }
    if (fl.zf)
        goto L_4b80cf;
    lift_store(&env, edi, 0x16u, 1, lift_load(&env, edi, 0x16u, 1) | 0x1u);
L_4b80cf:
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x5bd86au, 2), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4b80dd;
    lift_store(&env, edi, 0x17u, 1, lift_load(&env, edi, 0x17u, 1) | 0x1u);
L_4b80dd:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ac50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b814d;
    ebx = 0x1u;
    eax = esi;
    ecx = lift_load(&env, edi, 0x8u, 4);
    edx = lift_load(&env, edi, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(8, lift_load(&env, edi, 0x16u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b8120;
    edx = lift_load(&env, edi, 0x8u, 4);
    eax = eax ^ eax;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b8120;
L_4b810a:
    esi = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, esi, eax + 0x0u, 1, lift_load(&env, esi, eax + 0x0u, 1) ^ 0x80u);
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, lift_load(&env, edi, 0x8u, 4), &fl);
    }
    if (fl.cf)
        goto L_4b810a;
L_4b8120:
    eax = edi;
    ebx = lift_load(&env, edi, 0x8u, 4);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40acd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, eax, 0x0u, 4, edi);
    ebx = lift_load(&env, 0u, 0x598dacu, 4);
    eax = lift_load(&env, edi, 0x8u, 4);
    ebx = ebx + eax;
    lift_store(&env, 0u, 0x598dacu, 4, ebx);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_4b814d:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b8170u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edx;
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
L_4b815f:
    eax = esi;
    goto L_4b805e;
}

uint32_t lifted_f4b826f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B826F_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B826F_STACK, 0, entry);
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
    esp = esp - 0x28u;
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    edx = 0x158u;
    eax = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b82a6;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x8u);
    goto L_4b8fb0;
L_4b82a6:
    ecx = 0x11u;
    ebx = 0x1u;
    edx = 0x5bd880u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x14u;
    ebx = 0x1u;
    edx = 0x5bd891u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bd8a5u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x14u;
    ebx = 0x1u;
    edx = 0x5bd8a6u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd8bau;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bd8bcu;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd8c0u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd8c2u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd8c4u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd8c6u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd8c8u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd8cau;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd8ccu;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd8ceu;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x100u;
    ebx = 0x1u;
    edx = 0x5bd8d0u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x5bd8bcu, 4);
    edx = edx - 0x114u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aa90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x11u;
    edi = 0x511143u;
    esi = 0x5bd880u;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_string(&env, 4, 1, 2, &eax, &ecx, &esi, &edi, &fl);
    if (fl.zf)
        goto L_4b842d;
    {
        uint32_t r = lift_sbb(32, eax, eax, &fl);
        eax = r;
    }
    eax = eax - 0xffffffffu - fl.cf;
L_4b842d:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b843c;
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x5bd8bau, 2), 0x104u, &fl);
    }
    if (fl.zf)
        goto L_4b843e;
L_4b843c:
    goto L_4b844d;
L_4b843e:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd8c0u, 2)) & 0xffffu);
    {
        (void)lift_sub(32, eax, 0x100u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b844f;
L_4b844d:
    goto L_4b845e;
L_4b844f:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd8c6u, 2)) & 0xffffu);
    {
        (void)lift_sub(32, eax, 0x100u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b8460;
L_4b845e:
    goto L_4b846f;
L_4b8460:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd8c8u, 2)) & 0xffffu);
    {
        (void)lift_sub(32, eax, 0x80u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b8471;
L_4b846f:
    goto L_4b847e;
L_4b8471:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd8c4u, 2)) & 0xffffu);
    {
        (void)lift_sub(32, eax, 0x20u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b8492;
L_4b847e:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ef90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0xbu);
    goto L_4b8fb0;
L_4b8492:
    ebx = 0x14u;
    edx = 0x5bd891u;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x5bd8cau, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4b84b4;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x20u, 1, lift_load(&env, eax, 0x20u, 1) | 0x1u);
L_4b84b4:
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd8c0u, 2)) & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x22u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd8c2u, 2)) & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x24u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd8c4u, 2)) & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x26u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd8c6u, 2)) & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x28u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd8c8u, 2)) & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x2au, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd8ccu, 2)) & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x2cu, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd8ceu, 2)) & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x2eu, 2, (edx & 0xffffu));
    lift_store(&env, ebp, 0xffffffe4u, 4, 0x0u);
    goto L_4b8522;
L_4b851f:
    lift_store(&env, ebp, 0xffffffe4u, 4, lift_load(&env, ebp, 0xffffffe4u, 4) + 1u);
L_4b8522:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x22u, 2)) & 0xffffu);
    eax = eax & 0xffffu;
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b8547;
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = edx + lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x5bd8d0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x30u, 1, (eax & 0xffu));
    goto L_4b851f;
L_4b8547:
    lift_store(&env, ebp, 0xffffffe4u, 4, 0x0u);
    goto L_4b8553;
L_4b8550:
    lift_store(&env, ebp, 0xffffffe4u, 4, lift_load(&env, ebp, 0xffffffe4u, 4) + 1u);
L_4b8553:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x26u, 2)) & 0xffffu);
    eax = eax & 0xffffu;
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b8573;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, eax, 0x130u, 1, 0x7fu);
    goto L_4b8550;
L_4b8573:
    edx = 0xcu;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x28u, 2)) & 0xffffu);
    eax = eax & 0xffffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x150u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x150u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b85b4;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ef90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x8u);
    goto L_4b8fb0;
L_4b85b4:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x2au, 2)) & 0xffffu);
    eax = eax & 0xffffu;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b8607;
    edx = 0xfcu;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x2au, 2)) & 0xffffu);
    eax = eax & 0xffffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x154u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x154u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b8605;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ef90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x8u);
    goto L_4b8fb0;
L_4b8605:
    goto L_4b8614;
L_4b8607:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x154u, 4, 0x0u);
L_4b8614:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = lift_load(&env, eax, 0x150u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, 0x0u);
    goto L_4b8630;
L_4b8629:
    lift_store(&env, ebp, 0xffffffe4u, 4, lift_load(&env, ebp, 0xffffffe4u, 4) + 1u);
    lift_store(&env, ebp, 0xffffffd8u, 4, lift_load(&env, ebp, 0xffffffd8u, 4) + 0xcu);
L_4b8630:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x28u, 2)) & 0xffffu);
    eax = eax & 0xffffu;
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b8768;
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bd9d0u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bd9d4u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd9d5u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd9d7u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x5bd9d0u, 4);
    edx = edx - 0x9u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aa90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bd9d4u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b86cf;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ef90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0xbu);
    goto L_4b8fb0;
L_4b86cf:
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bd9d4u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, eax, 0x0u, 2, (edx & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x26u, 2)) & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, eax, 0x2u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd9d5u, 2)) & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, eax, 0x4u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd9d7u, 2)) & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, eax, 0x6u, 2, (edx & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x6u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b8763;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x6u, 2)) & 0xffffu);
    eax = eax & 0xffffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, eax, 0x8u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b8747;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ef90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x8u);
    goto L_4b8fb0;
L_4b8747:
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, eax, 0x6u, 2)) & 0xffffu);
    ebx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = lift_load(&env, eax, 0x8u, 4);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b8763:
    goto L_4b8629;
L_4b8768:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = lift_load(&env, eax, 0x154u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, 0x0u);
    goto L_4b8787;
L_4b877d:
    lift_store(&env, ebp, 0xffffffe4u, 4, lift_load(&env, ebp, 0xffffffe4u, 4) + 1u);
    lift_store(&env, ebp, 0xffffffdcu, 4, lift_load(&env, ebp, 0xffffffdcu, 4) + 0xfcu);
L_4b8787:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x2au, 2)) & 0xffffu);
    eax = eax & 0xffffu;
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b8fa1;
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bd9e0u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x16u;
    ebx = 0x1u;
    edx = 0x5bd9e4u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bd9fau;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bd9fbu;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x5bd9fbu, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b8a14;
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bd9fdu;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x60u;
    ebx = 0x1u;
    edx = 0x5bda01u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4b8840;
L_4b883d:
    lift_store(&env, ebp, 0xffffffe8u, 4, lift_load(&env, ebp, 0xffffffe8u, 4) + 1u);
L_4b8840:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0xcu, &fl);
    }
    if (!fl.cf)
        goto L_4b8867;
    ecx = 0x4u;
    ebx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = 0x5bda61u;
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4b883d;
L_4b8867:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4b8873;
L_4b8870:
    lift_store(&env, ebp, 0xffffffe8u, 4, lift_load(&env, ebp, 0xffffffe8u, 4) + 1u);
L_4b8873:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0xcu, &fl);
    }
    if (!fl.cf)
        goto L_4b889a;
    ecx = 0x4u;
    ebx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = 0x5bda91u;
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4b8870;
L_4b889a:
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdac1u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdac2u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdac3u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdac4u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdac5u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdac6u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdac7u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdac8u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdac9u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdacau;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdacbu;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdaccu;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdacdu;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdaceu;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bdacfu;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x2u;
    ebx = 0x1u;
    edx = 0x5bdad1u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5bd9e0u, 4, lift_load(&env, 0u, 0x5bd9e0u, 4) - 0xd6u);
L_4b8a14:
    edx = lift_load(&env, 0u, 0x5bd9e0u, 4);
    edx = edx - 0x1du;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aa90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdac1u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b8a38;
    lift_store(&env, 0u, 0x5bdac1u, 1, 0xcu);
L_4b8a38:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdac2u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b8a4b;
    lift_store(&env, 0u, 0x5bdac2u, 1, 0xcu);
L_4b8a4b:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd9fbu, 2)) & 0xffffu);
    {
        (void)lift_sub(32, eax, 0x10u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b8a64;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdac1u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b8a66;
L_4b8a64:
    goto L_4b8a72;
L_4b8a66:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdac2u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0xcu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b8a86;
L_4b8a72:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ef90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0xbu);
    goto L_4b8fb0;
L_4b8a86:
    ebx = 0x16u;
    edx = 0x5bd9e4u;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4b8aa4;
L_4b8aa1:
    lift_store(&env, ebp, 0xffffffe8u, 4, lift_load(&env, ebp, 0xffffffe8u, 4) + 1u);
L_4b8aa4:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x60u, &fl);
    }
    if (!fl.cf)
        goto L_4b8adf;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = edx + lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x5bda01u, 1)) & 0xffu);
    lift_store(&env, edx, 0x20u, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x20u, 1)) & 0xffu);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd9fbu, 2)) & 0xffffu);
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b8add;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x20u, 1, 0x0u);
L_4b8add:
    goto L_4b8aa1;
L_4b8adf:
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd9fbu, 2)) & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0x80u, 2, (edx & 0xffffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdacbu, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0x82u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdaccu, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0x83u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdacdu, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0x84u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdaceu, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0x85u, 1, (edx & 0xffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bdacfu, 2)) & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0x86u, 2, (edx & 0xffffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdac1u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xb8u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdac3u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xb9u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdac4u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xbau, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdac5u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xbbu, 1, (edx & 0xffu));
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x5bdac9u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4b8b8c;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xbcu, 1, lift_load(&env, eax, 0xbcu, 1) | 0x1u);
L_4b8b8c:
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x5bdac9u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b8b9f;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xbcu, 1, lift_load(&env, eax, 0xbcu, 1) | 0x2u);
L_4b8b9f:
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x5bdac9u, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4b8bb2;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xbcu, 1, lift_load(&env, eax, 0xbcu, 1) | 0x4u);
L_4b8bb2:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4b8bbe;
L_4b8bbb:
    lift_store(&env, ebp, 0xffffffe8u, 4, lift_load(&env, ebp, 0xffffffe8u, 4) + 1u);
L_4b8bbe:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0xb8u, 1)) & 0xffu);
    eax = eax & 0xffu;
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffe8u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b8c16;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0x5bda61u, 2)) & 0xffffu);
    lift_store(&env, eax, 0x88u, 2, (edx & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = lift_load(&env, eax, 0x5bda61u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax & 0xffffu;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0x8au, 2, (edx & 0xffffu));
    goto L_4b8bbb;
L_4b8c16:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdac2u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xf0u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdac6u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xf1u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdac7u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xf2u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdac8u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xf3u, 1, (edx & 0xffu));
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x5bdacau, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4b8c65;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xf4u, 1, lift_load(&env, eax, 0xf4u, 1) | 0x1u);
L_4b8c65:
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x5bdacau, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b8c78;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xf4u, 1, lift_load(&env, eax, 0xf4u, 1) | 0x2u);
L_4b8c78:
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x5bdacau, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4b8c8b;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xf4u, 1, lift_load(&env, eax, 0xf4u, 1) | 0x4u);
L_4b8c8b:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4b8c97;
L_4b8c94:
    lift_store(&env, ebp, 0xffffffe8u, 4, lift_load(&env, ebp, 0xffffffe8u, 4) + 1u);
L_4b8c97:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0xf0u, 1)) & 0xffu);
    eax = eax & 0xffu;
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffe8u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b8cef;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edx, 0x5bda91u, 2)) & 0xffffu);
    lift_store(&env, eax, 0xc0u, 2, (edx & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = lift_load(&env, eax, 0x5bda91u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax & 0xffffu;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xc2u, 2, (edx & 0xffffu));
    goto L_4b8c94;
L_4b8cef:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x80u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b8d40;
    edx = 0x3cu;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x80u, 2)) & 0xffffu);
    eax = eax & 0xffffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xf8u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xf8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b8d40;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ef90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x8u);
    goto L_4b8fb0;
L_4b8d40:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_load(&env, eax, 0xf8u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4b8d5c;
L_4b8d55:
    lift_store(&env, ebp, 0xffffffe8u, 4, lift_load(&env, ebp, 0xffffffe8u, 4) + 1u);
    lift_store(&env, ebp, 0xffffffe0u, 4, lift_load(&env, ebp, 0xffffffe0u, 4) + 0x3cu);
L_4b8d5c:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd9fbu, 2)) & 0xffffu);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffe8u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b8f0d;
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bdad8u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bdadcu;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x4u;
    ebx = 0x1u;
    edx = 0x5bdae0u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdae4u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdae5u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdae6u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdae7u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdae8u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x1u;
    ebx = 0x1u;
    edx = 0x5bdae9u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x16u;
    ebx = 0x1u;
    edx = 0x5bdaeau;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x5bd9fdu, 4);
    edx = edx - 0x28u;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48aa90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x16u;
    edx = 0x5bdaeau;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x5bdad8u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x2cu, 4, edx);
    edx = lift_load(&env, 0u, 0x5bdadcu, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x30u, 4, edx);
    eax = lift_load(&env, 0u, 0x5bdadcu, 4);
    eax = eax + lift_load(&env, 0u, 0x5bdae0u, 4);
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, edx, 0x34u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x38u, 2, 0x20abu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdae4u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x20u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdae7u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x21u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdae8u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x22u, 1, (edx & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bdae5u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x23u, 1, (edx & 0xffu));
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x5bdae6u, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4b8ee8;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x3au, 1, lift_load(&env, eax, 0x3au, 1) | 0x1u);
L_4b8ee8:
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x5bdae6u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4b8ef8;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x3au, 1, lift_load(&env, eax, 0x3au, 1) | 0x10u);
L_4b8ef8:
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x5bdae6u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b8f08;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x3au, 1, lift_load(&env, eax, 0x3au, 1) | 0x20u);
L_4b8f08:
    goto L_4b8d55;
L_4b8f0d:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_load(&env, eax, 0xf8u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4b8f29;
L_4b8f22:
    lift_store(&env, ebp, 0xffffffe8u, 4, lift_load(&env, ebp, 0xffffffe8u, 4) + 1u);
    lift_store(&env, ebp, 0xffffffe0u, 4, lift_load(&env, ebp, 0xffffffe0u, 4) + 0x3cu);
L_4b8f29:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bd9fbu, 2)) & 0xffffu);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffe8u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b8f9c;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x2cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b8f9a;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax + 0x24u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ac50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b8f63;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40ef90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    goto L_4b8fb0;
L_4b8f63:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = lift_load(&env, eax, 0x2cu, 4);
    ebx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = lift_load(&env, eax, 0x24u, 4);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48a930u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax + 0x24u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b8fbcu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = lift_load(&env, eax, 0x2cu, 4);
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax + 0x24u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x40acd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b8f9a:
    goto L_4b8f22;
L_4b8f9c:
    goto L_4b877d;
L_4b8fa1:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x0u);
L_4b8fb0:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
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

uint32_t lifted_f4bcea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4BCEA0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4BCEA0_STACK, 0, entry);
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
    edx = eax;
    edi = lift_load(&env, eax, 0x1b4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x14u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4bd18d;
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
L_4bcecc:
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x18u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4bd103;
    ebx = lift_load(&env, edx, 0x20u, 4);
    ecx = edx;
    {
        (void)lift_sub(32, ebx, 0xffdcu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bd0a3;
L_4bcee7:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x29u);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, 0xffdcu);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4bceff:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0xd4u, 4), 0x8u, &fl);
    }
    if (fl.zf)
        goto L_4bcf22;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0xfu);
    eax = lift_load(&env, ecx, 0x0u, 4);
    edx = lift_load(&env, ecx, 0xd4u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4bcf22:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x24u, 4), 0xau, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bcf48;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x1au);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = lift_load(&env, ecx, 0x24u, 4);
    lift_store(&env, edx, 0x18u, 4, eax);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x1cu, 4, 0xau);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4bcf48:
    lift_store(&env, ecx, 0x134u, 4, 0x1u);
    lift_store(&env, ecx, 0x138u, 4, 0x1u);
    ebx = lift_load(&env, ecx, 0xd8u, 4);
    esi = lift_load(&env, ecx, 0x24u, 4);
    edx = edx ^ edx;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bcfc3;
L_4bcf6b:
    esi = lift_load(&env, ebx, 0x8u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bcf7b;
    {
        (void)lift_sub(32, esi, 0x4u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bd0b5;
L_4bcf7b:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x12u);
    esi = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4bcf8a:
    eax = lift_load(&env, ecx, 0x134u, 4);
    esi = lift_load(&env, ebx, 0x8u, 4);
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bd0ce;
L_4bcf9b:
    lift_store(&env, ecx, 0x134u, 4, eax);
    eax = lift_load(&env, ecx, 0x138u, 4);
    esi = lift_load(&env, ebx, 0xcu, 4);
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bd0d5;
L_4bcfb2:
    lift_store(&env, ecx, 0x138u, 4, eax);
    edx = edx + 1u;
    eax = lift_load(&env, ecx, 0x24u, 4);
    ebx = ebx + 0x54u;
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bcf6b;
L_4bcfc3:
    lift_store(&env, ecx, 0x13cu, 4, 0x8u);
    ebx = lift_load(&env, ecx, 0xd8u, 4);
    edx = lift_load(&env, ecx, 0x24u, 4);
    esi = esi ^ esi;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bd060;
L_4bcfe0:
    lift_store(&env, ebx, 0x24u, 4, 0x8u);
    eax = lift_load(&env, ecx, 0x1cu, 4);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, ebx, 0x8u, 4), &fl);
        eax = r;
    }
    edx = lift_load(&env, ecx, 0x134u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x1cu, 4, eax);
    eax = lift_load(&env, ecx, 0x20u, 4);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, ebx, 0xcu, 4), &fl);
        eax = r;
    }
    edx = lift_load(&env, ecx, 0x138u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x20u, 4, eax);
    eax = lift_load(&env, ecx, 0x1cu, 4);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, ebx, 0x8u, 4), &fl);
        eax = r;
    }
    edx = lift_load(&env, ecx, 0x134u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x28u, 4, eax);
    eax = lift_load(&env, ecx, 0x20u, 4);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, ebx, 0xcu, 4), &fl);
        eax = r;
    }
    edx = lift_load(&env, ecx, 0x138u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x30u, 4, 0x1u);
    lift_store(&env, ebx, 0x4cu, 4, 0x0u);
    lift_store(&env, ebx, 0x2cu, 4, eax);
    esi = esi + 1u;
    eax = lift_load(&env, ecx, 0x24u, 4);
    ebx = ebx + 0x54u;
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bcfe0;
L_4bd060:
    edx = lift_load(&env, ecx, 0x138u, 4);
    eax = lift_load(&env, ecx, 0x20u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x140u, 4, eax);
    edx = lift_load(&env, ecx, 0x24u, 4);
    {
        (void)lift_sub(32, edx, lift_load(&env, ecx, 0x148u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bd0dc;
L_4bd082:
    eax = lift_load(&env, ecx, 0x1b4u, 4);
    lift_store(&env, eax, 0x10u, 4, 0x1u);
    lift_store(&env, edi, 0x18u, 4, 0x0u);
L_4bd096:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
L_4bd0a3:
    {
        (void)lift_sub(32, lift_load(&env, edx, 0x1cu, 4), 0xffdcu, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4bcee7;
    goto L_4bceff;
L_4bd0b5:
    esi = lift_load(&env, ebx, 0xcu, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bcf7b;
    {
        (void)lift_sub(32, esi, 0x4u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4bcf7b;
    goto L_4bcf8a;
L_4bd0ce:
    eax = esi;
    goto L_4bcf9b;
L_4bd0d5:
    eax = esi;
    goto L_4bcfb2;
L_4bd0dc:
    ebx = lift_load(&env, ecx, 0xdcu, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4bd082;
    eax = lift_load(&env, ecx, 0x1b4u, 4);
    lift_store(&env, eax, 0x10u, 4, ebx);
    lift_store(&env, edi, 0x18u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
L_4bd103:
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4bd118;
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x23u);
    ecx = lift_load(&env, edx, 0x0u, 4);
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4bd118:
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bcbc0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
L_4bd12c:
    ebx = lift_load(&env, edi, 0x18u, 4);
    lift_store(&env, edi, 0x14u, 4, 0x1u);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4bd166;
    eax = lift_load(&env, edx, 0x1b8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4bd096;
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x3bu);
    ecx = lift_load(&env, edx, 0x0u, 4);
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
L_4bd166:
    eax = lift_load(&env, edx, 0x98u, 4);
    esi = lift_load(&env, edx, 0x90u, 4);
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bd096;
    lift_store(&env, edx, 0x98u, 4, esi);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
L_4bd18d:
    ecx = lift_load(&env, eax, 0x1b8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.cf)
        goto L_4bd096;
    if (fl.cf || fl.zf)
        goto L_4bcecc;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4bd12c;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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

uint32_t lifted_f4bd9e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4BD9E0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4BD9E0_STACK, 0, entry);
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
    esp = esp - 0x64u;
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    lift_store(&env, ebp, 0xffffff98u, 4, edx);
    lift_store(&env, ebp, 0xffffff9cu, 4, ebx);
    lift_store(&env, ebp, 0xffffffa0u, 4, ecx);
    eax = lift_load(&env, eax, 0x1a8u, 4);
    edx = lift_load(&env, eax, 0x30u, 4);
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4bdc49;
L_4bda08:
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    eax = lift_load(&env, eax, 0x44u, 4);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.cf)
        goto L_4bdda1;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bdc42;
L_4bda1f:
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    lift_store(&env, eax, 0x34u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = lift_load(&env, eax, 0x13cu, 4);
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    eax = eax - 1u;
    lift_store(&env, edx, 0x48u, 4, eax);
    eax = lift_load(&env, edx, 0x4cu, 4);
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x140u, 4), &fl);
    }
    if (fl.zf)
        goto L_4bdcd7;
L_4bda4b:
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    lift_store(&env, eax, 0x44u, 4, 0x1u);
L_4bda55:
    esi = lift_load(&env, ebp, 0xffffffa4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffa0u, 4);
    ebx = lift_load(&env, ebp, 0xffffff9cu, 4);
    edi = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = lift_load(&env, esi, 0x1b0u, 4);
    eax = lift_load(&env, eax, 0x40u, 4);
    ecx = lift_load(&env, ebp, 0xffffffb0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffb0u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = eax + edx;
    ecx = lift_load(&env, ecx, 0x48u, 4);
    ebx = ebx + 0x34u;
    edx = lift_load(&env, eax, 0x38u, 4);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x4u, 4), eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    eax = lift_load(&env, eax, 0x34u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x48u, 4), &fl);
    }
    if (fl.cf)
        goto L_4bdc42;
    ebx = lift_load(&env, edx, 0x4cu, 4);
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4bdc09;
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    esi = esi ^ esi;
    edx = lift_load(&env, edx, 0xd8u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    eax = lift_load(&env, eax, 0x1a8u, 4);
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, esi);
    edi = lift_load(&env, edx, 0x24u, 4);
    eax = lift_load(&env, eax, 0x13cu, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bdc09;
    edx = (eax + ebx);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    eax = eax + 0x2u;
    lift_store(&env, ebp, 0xffffffacu, 4, edx);
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
L_4bdaf1:
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = lift_load(&env, edx, 0xcu, 4);
    {
        uint32_t r = lift_imul(32, edx, lift_load(&env, eax, 0x24u, 4), &fl);
        edx = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffbcu, 4);
    ebx = lift_load(&env, ecx, 0x13cu, 4);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_load(&env, eax, 0x38u, 4);
    eax = eax + esi;
    esi = lift_load(&env, ebp, 0xffffffb8u, 4);
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    esi = lift_load(&env, esi, 0x3cu, 4);
    eax = eax ^ eax;
    esi = esi + edi;
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    esi = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bdbe0;
    eax = ecx;
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, ebp, 0xffffffacu, 4), &fl);
        eax = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t r = lift_imul(32, ecx, ebx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    eax = (esi + ecx);
    ebx = (edx + ecx);
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    edi = ecx;
    lift_store(&env, ebp, 0xffffff94u, 4, ecx);
    edi = 0u - edi;
    lift_store(&env, ebp, 0xffffff94u, 4, edi);
    ecx = (edi + esi);
    edi = lift_load(&env, ebp, 0xffffffb4u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xfffffff0u, 4, esi);
    esi = esi + edi;
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    esi = lift_load(&env, ebp, 0xffffff94u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    esi = esi + edx;
    lift_store(&env, ebp, 0xffffffecu, 4, esi);
    edx = edx + edi;
L_4bdb84:
    edi = lift_load(&env, ebp, 0xffffffecu, 4);
    esi = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, edi, 0x0u, 4, esi);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, ecx, 0x0u, 4, esi);
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    ebx = ebx + 0x4u;
    esi = lift_load(&env, esi, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, ebx, 0xfffffffcu, 4, esi);
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    ecx = ecx + 0x4u;
    edx = edx + 0x4u;
    esi = lift_load(&env, esi, 0x0u, 4);
    edi = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, eax, 0xfffffffcu, 4, esi);
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    edi = edi + 0x4u;
    esi = esi + 0x4u;
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    lift_store(&env, ebp, 0xfffffff0u, 4, esi);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = lift_load(&env, ebp, 0xffffffecu, 4);
    esi = esi + 0x4u;
    edi = edi + 0x4u;
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    esi = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, edi);
    esi = esi + 1u;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, esi);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bdb84;
L_4bdbe0:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = eax + 0x4u;
    edx = edx + 1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    eax = edx;
    edx = lift_load(&env, ebp, 0xffffffbcu, 4);
    ecx = ecx + 0x54u;
    ebx = lift_load(&env, edx, 0x24u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bdaf1;
L_4bdc09:
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x40u, 1)) & 0xffu);
    lift_store(&env, eax, 0x30u, 4, 0x0u);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ 0x1u) & 0xffu);
    lift_store(&env, eax, 0x40u, 1, (edx & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = lift_load(&env, eax, 0x13cu, 4);
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    eax = eax + 1u;
    lift_store(&env, edx, 0x34u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = lift_load(&env, eax, 0x13cu, 4);
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, edx, 0x44u, 4, 0x2u);
    lift_store(&env, edx, 0x48u, 4, eax);
L_4bdc42:
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
L_4bdc49:
    eax = lift_load(&env, eax, 0x40u, 4);
    ebx = lift_load(&env, ebp, 0xffffffb0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = eax + ebx;
    ecx = lift_load(&env, ecx, 0x1acu, 4);
    edx = lift_load(&env, eax, 0x38u, 4);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bdc42;
    esi = lift_load(&env, ebx, 0x4cu, 4);
    lift_store(&env, ebx, 0x30u, 4, 0x1u);
    esi = esi + 1u;
    lift_store(&env, ebx, 0x4cu, 4, esi);
    goto L_4bda08;
L_4bdc7d:
    esi = lift_load(&env, ebp, 0xffffffa4u, 4);
    edi = lift_load(&env, ebp, 0xffffffa0u, 4);
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ebp, 0xffffff98u, 4);
    ebx = lift_load(&env, ebp, 0xffffffb0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffb0u, 4);
    ebx = ebx + 0x34u;
    eax = lift_load(&env, eax, 0x40u, 4);
    edi = lift_load(&env, ebp, 0xffffffb0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    esi = lift_load(&env, esi, 0x1b0u, 4);
    eax = eax + edi;
    ecx = lift_load(&env, ecx, 0x48u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x38u, 4);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x4u, 4), eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    eax = lift_load(&env, edi, 0x34u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edi, 0x48u, 4), &fl);
    }
    if (fl.cf)
        goto L_4bdc42;
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    lift_store(&env, edi, 0x44u, 4, 0x0u);
    ebx = lift_load(&env, ebp, 0xffffffa0u, 4);
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x0u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4bdc42;
    goto L_4bda1f;
L_4bdcd7:
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    edi = edi ^ edi;
    eax = lift_load(&env, edx, 0x1a8u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    edi = lift_load(&env, edx, 0xd8u, 4);
    edx = lift_load(&env, edx, 0x24u, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bda4b;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
L_4bdcfe:
    ecx = lift_load(&env, edi, 0xcu, 4);
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, edi, 0x24u, 4), &fl);
        ecx = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffc0u, 4);
    esi = lift_load(&env, ebx, 0x13cu, 4);
    edx = ecx;
    eax = ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, esi, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    edx = edx ^ edx;
    eax = lift_load(&env, edi, 0x2cu, 4);
    lift_div1(32, ecx, &eax, &edx, &fl);
    ebx = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4bdd29;
    ebx = ecx;
L_4bdd29:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4bdd43;
    edx = (ebx + 0xffffffffu);
    ecx = lift_load(&env, ebp, 0xffffffc4u, 4);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = eax + 1u;
    lift_store(&env, edx, 0x48u, 4, eax);
L_4bdd43:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = lift_load(&env, eax, 0x40u, 4);
    esi = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + esi;
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = lift_load(&env, eax, 0x38u, 4);
    eax = eax + edx;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    esi = lift_load(&env, eax, 0x0u, 4);
    esi = esi + ebx;
    ebx = lift_load(&env, ebp, 0xffffffc4u, 4);
    edx = edx ^ edx;
    ebx = ebx + ebx;
    eax = esi;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bdd7b;
L_4bdd6d:
    eax = eax + 0x4u;
    ecx = lift_load(&env, esi, 0xfffffffcu, 4);
    edx = edx + 1u;
    lift_store(&env, eax, 0xfffffffcu, 4, ecx);
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bdd6d;
L_4bdd7b:
    ecx = lift_load(&env, ebp, 0xffffffc8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = lift_load(&env, ebp, 0xffffffc0u, 4);
    edi = edi + 0x54u;
    ecx = ecx + 0x4u;
    ebx = ebx + 1u;
    esi = lift_load(&env, edx, 0x24u, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4bda4b;
    goto L_4bdcfe;
L_4bdda1:
    if (fl.cf || fl.zf)
        goto L_4bda55;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4bdc7d;
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

uint32_t lifted_f4be0b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4BE0B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4BE0B0_STACK, 0, entry);
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
    esp = esp - 0xcu;
    ecx = eax;
    eax = lift_load(&env, eax, 0x18u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    esi = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    esi = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, ecx, 0xdcu, 4, edx);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    lift_store(&env, ecx, 0xe0u, 4, ebx);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4be350;
L_4be0e0:
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (eax + 0x1u);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    {
        uint32_t a = esi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        esi = r;
    }
    if (fl.zf)
        goto L_4be369;
L_4be0f7:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = esi - 1u;
    eax = eax ^ eax;
    edi = (edx + 0x1u);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff0u, 4, edi);
    ebx = ebx + eax;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4be382;
L_4be10f:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ecx, 0xd4u, 4, eax);
    eax = (edx + 0x1u);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    {
        uint32_t a = esi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        esi = r;
    }
    if (fl.zf)
        goto L_4be39b;
L_4be129:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = eax ^ eax;
    esi = esi - 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    edx = edx + 1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    lift_store(&env, ecx, 0x20u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4be3b4;
L_4be143:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = eax ^ eax;
    edi = (edx + 0x1u);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, ecx, 0x20u, 4);
    esi = esi - 1u;
    edx = edx + eax;
    lift_store(&env, ebp, 0xfffffff0u, 4, edi);
    lift_store(&env, ecx, 0x20u, 4, edx);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4be3cd;
L_4be161:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    edi = (edx + 0x1u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xfffffff0u, 4, edi);
    lift_store(&env, ecx, 0x1cu, 4, eax);
    {
        uint32_t a = esi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        esi = r;
    }
    if (fl.zf)
        goto L_4be3ea;
L_4be17b:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = esi - 1u;
    eax = eax ^ eax;
    edi = lift_load(&env, ecx, 0x1cu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    edx = edx + 1u;
    edi = edi + eax;
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    lift_store(&env, ecx, 0x1cu, 4, edi);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4be1ab;
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4be348;
    eax = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
L_4be1ab:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ecx, 0x24u, 4, eax);
    edx = edx + 1u;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    edx = lift_load(&env, ecx, 0x1a0u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    edx = lift_load(&env, ecx, 0x1cu, 4);
    lift_store(&env, eax, 0x1cu, 4, edx);
    edx = lift_load(&env, ecx, 0x20u, 4);
    lift_store(&env, eax, 0x20u, 4, edx);
    edx = lift_load(&env, ecx, 0x24u, 4);
    lift_store(&env, eax, 0x24u, 4, edx);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x64u);
    edi = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0x1b8u, 4);
    esi = esi - 1u;
    edi = lift_load(&env, eax, 0x10u, 4);
    ebx = ebx - 0x8u;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4be20b;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x3au);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4be20b:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x20u, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4be407;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x1cu, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4be407;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x24u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4be407;
L_4be229:
    edx = lift_load(&env, ecx, 0x24u, 4);
    eax = ((edx * 4u));
    eax = eax - edx;
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.zf)
        goto L_4be248;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0xbu);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4be248:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0xd8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4be277;
    edx = lift_load(&env, ecx, 0x24u, 4);
    ebx = ((edx * 4u));
    ebx = ebx + edx;
    eax = ecx;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    edi = lift_load(&env, ecx, 0x4u, 4);
    ebx = ebx + edx;
    edx = 0x1u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0xd8u, 4, eax);
L_4be277:
    ebx = lift_load(&env, ecx, 0xd8u, 4);
    edx = edx ^ edx;
    edi = lift_load(&env, ecx, 0x24u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4be32b;
L_4be28d:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ebx, 0x4u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4be41b;
L_4be29b:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    edi = (edx + 0x1u);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff0u, 4, edi);
    lift_store(&env, ebx, 0x0u, 4, eax);
    {
        uint32_t a = esi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        esi = r;
    }
    if (fl.zf)
        goto L_4be438;
L_4be2b1:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    esi = esi - 1u;
    edx = eax;
    eax = eax & 0xfu;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        edx = r;
    }
    lift_store(&env, ebx, 0xcu, 4, eax);
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = edx & 0xfu;
    eax = eax + 1u;
    lift_store(&env, ebx, 0x8u, 4, edx);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4be455;
L_4be2d9:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x10u, 4, eax);
    edx = edx + 1u;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    edx = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    edx = lift_load(&env, ebx, 0x8u, 4);
    lift_store(&env, eax, 0x1cu, 4, edx);
    edx = lift_load(&env, ebx, 0xcu, 4);
    lift_store(&env, eax, 0x20u, 4, edx);
    edx = lift_load(&env, ebx, 0x10u, 4);
    lift_store(&env, eax, 0x24u, 4, edx);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x65u);
    edx = 0x1u;
    edi = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    esi = esi - 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx + 0x54u;
    edi = edi + 1u;
    edx = lift_load(&env, ecx, 0x24u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    {
        (void)lift_sub(32, edi, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4be28d;
L_4be32b:
    eax = lift_load(&env, ecx, 0x1b8u, 4);
    lift_store(&env, eax, 0x10u, 4, 0x1u);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
    lift_store(&env, eax, 0x4u, 4, esi);
    eax = 0x1u;
L_4be348:
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
L_4be350:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4be348;
    eax = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    goto L_4be0e0;
L_4be369:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4be348;
    eax = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    goto L_4be0f7;
L_4be382:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4be348;
    eax = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    goto L_4be10f;
L_4be39b:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4be348;
    eax = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    goto L_4be129;
L_4be3b4:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4be348;
    eax = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    goto L_4be143;
L_4be3cd:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4be348;
    eax = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    goto L_4be161;
L_4be3ea:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4be348;
    eax = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    goto L_4be17b;
L_4be407:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x20u);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4be229;
L_4be41b:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4be348;
    eax = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    goto L_4be29b;
L_4be438:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4be348;
    eax = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    goto L_4be2b1;
L_4be455:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4be348;
    eax = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    goto L_4be2d9;
}

uint32_t lifted_f4bef10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4BEF10_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4BEF10_STACK, 0, entry);
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
    ecx = ecx + ebx;
    {
        (void)lift_sub(32, ebx, 0xeu, &fl);
    }
    if (fl.cf)
        goto L_4bf09f;
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x4au, &fl);
    }
    if (!fl.zf)
        goto L_4bf09f;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x1u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x46u, &fl);
    }
    if (!fl.zf)
        goto L_4bf09f;
    {
        (void)lift_sub(8, lift_load(&env, edi, 0x2u, 1), 0x49u, &fl);
    }
    if (!fl.zf)
        goto L_4bf09f;
    {
        (void)lift_sub(8, (edx & 0xffu), lift_load(&env, edi, 0x3u, 1), &fl);
    }
    if (!fl.zf)
        goto L_4bf09f;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, edi, 0x4u, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4bf09f;
    lift_store(&env, esi, 0x118u, 4, 0x1u);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x5u, 1)) & 0xffu);
    lift_store(&env, esi, 0x11cu, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x6u, 1)) & 0xffu);
    lift_store(&env, esi, 0x11du, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x7u, 1)) & 0xffu);
    lift_store(&env, esi, 0x11eu, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x8u, 1)) & 0xffu);
    ebx = eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ebx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x9u, 1)) & 0xffu);
    ebx = ebx + eax;
    lift_store(&env, esi, 0x120u, 2, (ebx & 0xffffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0xau, 1)) & 0xffu);
    ebx = eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ebx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0xbu, 1)) & 0xffu);
    ebx = ebx + eax;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esi, 0x11cu, 1)) & 0xffu) << 8);
    lift_store(&env, esi, 0x122u, 2, (ebx & 0xffffu));
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4befdb;
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x77u);
    eax = eax ^ eax;
    ebx = lift_load(&env, esi, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x11cu, 1)) & 0xffu);
    lift_store(&env, ebx, 0x18u, 4, eax);
    eax = eax ^ eax;
    ebx = lift_load(&env, esi, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x11du, 1)) & 0xffu);
    lift_store(&env, ebx, 0x1cu, 4, eax);
    ebx = lift_load(&env, esi, 0x0u, 4);
    edx = 0xffffffffu;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4befdb:
    ebx = ebx ^ ebx;
    eax = lift_load(&env, esi, 0x0u, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x11cu, 1)) & 0xffu);
    lift_store(&env, eax, 0x18u, 4, ebx);
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x11du, 1)) & 0xffu);
    lift_store(&env, eax, 0x1cu, 4, ebx);
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, esi, 0x120u, 2)) & 0xffffu);
    lift_store(&env, eax, 0x20u, 4, ebx);
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, esi, 0x122u, 2)) & 0xffffu);
    lift_store(&env, eax, 0x24u, 4, ebx);
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x11eu, 1)) & 0xffu);
    lift_store(&env, eax, 0x28u, 4, ebx);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x57u);
    ebx = lift_load(&env, esi, 0x0u, 4);
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    eax = eax ^ eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edi, 0xcu, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0xdu, 1)) & 0xffu);
    {
        uint32_t r = lift_or(32, eax, ebx, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4bf062;
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x5au);
    ebx = ebx ^ ebx;
    eax = lift_load(&env, esi, 0x0u, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edi, 0xcu, 1)) & 0xffu);
    lift_store(&env, eax, 0x18u, 4, ebx);
    eax = eax ^ eax;
    ebx = lift_load(&env, esi, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0xdu, 1)) & 0xffu);
    lift_store(&env, ebx, 0x1cu, 4, eax);
    ebx = lift_load(&env, esi, 0x0u, 4);
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4bf062:
    ebx = ebx ^ ebx;
    eax = eax ^ eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edi, 0xcu, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0xdu, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, ebx, eax, &fl);
        ebx = r;
    }
    eax = ((ebx * 4u));
    ecx = ecx - 0xeu;
    eax = eax - ebx;
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bf082;
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
L_4bf082:
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x58u);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, ecx);
    ecx = lift_load(&env, esi, 0x0u, 4);
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4bf09f:
    {
        (void)lift_sub(32, ebx, 0x6u, &fl);
    }
    if (fl.cf)
        goto L_4bf16f;
    {
        (void)lift_sub(8, lift_load(&env, edi, 0x0u, 1), 0x4au, &fl);
    }
    if (!fl.zf)
        goto L_4bf16f;
    {
        (void)lift_sub(8, lift_load(&env, edi, 0x1u, 1), 0x46u, &fl);
    }
    if (!fl.zf)
        goto L_4bf16f;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edi, 0x2u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x58u, &fl);
    }
    if (!fl.zf)
        goto L_4bf16f;
    {
        (void)lift_sub(8, (ebx & 0xffu), lift_load(&env, edi, 0x3u, 1), &fl);
    }
    if (!fl.zf)
        goto L_4bf16f;
    {
        (void)lift_sub(8, lift_load(&env, edi, 0x4u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4bf16f;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x5u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x11u, &fl);
    }
    if (!fl.cf)
        goto L_4bf167;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x10u, &fl);
    }
    if (!fl.zf)
        goto L_4bf140;
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x6cu);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, ecx);
    ecx = lift_load(&env, esi, 0x0u, 4);
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4bf106:
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x6du);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, ecx);
    ecx = lift_load(&env, esi, 0x0u, 4);
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4bf123:
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x6eu);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, ecx);
    ecx = lift_load(&env, esi, 0x0u, 4);
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4bf140:
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x59u);
    eax = eax ^ eax;
    ebx = lift_load(&env, esi, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x5u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x18u, 4, eax);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x1cu, 4, ecx);
    ecx = lift_load(&env, esi, 0x0u, 4);
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4bf167:
    if (fl.cf || fl.zf)
        goto L_4bf106;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x13u, &fl);
    }
    if (fl.zf)
        goto L_4bf123;
    goto L_4bf140;
L_4bf16f:
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x4du);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, ecx);
    ecx = lift_load(&env, esi, 0x0u, 4);
    edx = 0x1u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c2000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C2000_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C2000_STACK, 0, entry);
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
    esp = esp - 0x38u;
    lift_store(&env, esp, 0xcu, 4, eax);
    esi = ebx;
    eax = edx;
    ebx = ecx;
    ecx = lift_load(&env, esp, 0xcu, 4);
    ecx = lift_load(&env, ecx, 0x1c4u, 4);
    edi = lift_load(&env, ecx, 0x10u, 4);
    lift_store(&env, esp, 0x18u, 4, edi);
    edi = lift_load(&env, ecx, 0x14u, 4);
    lift_store(&env, esp, 0x1cu, 4, edi);
    edi = lift_load(&env, ecx, 0x18u, 4);
    ecx = lift_load(&env, ecx, 0x1cu, 4);
    lift_store(&env, esp, 0x10u, 4, edi);
    lift_store(&env, esp, 0x14u, 4, ecx);
    edi = ((esi * 8u));
    ecx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx + edi;
    edi = lift_load(&env, ecx, 0x0u, 4);
    ecx = lift_load(&env, ecx, 0x4u, 4);
    lift_store(&env, esp, 0x30u, 4, ecx);
    ecx = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    edx = lift_load(&env, esp, 0xcu, 4);
    eax = lift_load(&env, eax, (esi * 4u) + 0x0u, 4);
    ecx = lift_load(&env, ecx, (esi * 4u) + 0x0u, 4);
    lift_store(&env, esp, 0x24u, 4, eax);
    eax = lift_load(&env, esp, 0xcu, 4);
    edx = lift_load(&env, edx, 0x144u, 4);
    lift_store(&env, esp, 0x20u, 4, ecx);
    eax = lift_load(&env, eax, 0x70u, 4);
    esi = lift_load(&env, ebx, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebx, 0x4u, 4);
    lift_store(&env, esp, 0x28u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c21d0;
L_4c2082:
    ebx = lift_load(&env, esp, 0x20u, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = lift_load(&env, esp, 0x24u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ebp = (ebx + 0x1u);
    ebx = lift_load(&env, esp, 0x24u, 4);
    eax = eax & 0xffu;
    ebx = ebx + 1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x24u, 4, ebx);
    ebx = lift_load(&env, esp, 0x18u, 4);
    ebx = lift_load(&env, ebx, eax + 0x0u, 4);
    lift_store(&env, esp, 0x20u, 4, ebp);
    lift_store(&env, esp, 0x0u, 4, ebx);
    ebx = lift_load(&env, esp, 0x8u, 4);
    ebp = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    ebp = ebp + ebx;
    lift_store(&env, esp, 0x34u, 4, ebp);
    ebp = lift_load(&env, esp, 0x10u, 4);
    ebp = ebp + eax;
    eax = lift_load(&env, esp, 0x34u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esp, 0x34u, 4, eax);
    eax = lift_load(&env, ebp, 0x0u, 4);
    ebp = lift_load(&env, esp, 0x34u, 4);
    ebp = ebp + eax;
    eax = ebp;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x4u, 4, eax);
    ebx = ebx + lift_load(&env, esp, 0x1cu, 4);
    eax = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, esp, 0x2cu, 4, eax);
    eax = eax ^ eax;
    ebp = lift_load(&env, esp, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x0u, 1)) & 0xffu);
    ebp = ebp + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0x0u, 1)) & 0xffu);
    ebp = lift_load(&env, esp, 0x4u, 4);
    ebp = ebp + eax;
    lift_store(&env, esi, 0x0u, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0x0u, 1)) & 0xffu);
    lift_store(&env, esi, 0x1u, 1, (ebx & 0xffu));
    eax = eax + lift_load(&env, esp, 0x2cu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x0u, 1)) & 0xffu);
    lift_store(&env, esi, 0x2u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    ebp = lift_load(&env, esp, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x1u, 1)) & 0xffu);
    ebp = ebp + eax;
    ebp = ebp + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    ebp = lift_load(&env, esp, 0x4u, 4);
    ebp = ebp + eax;
    ebp = ebp + edx;
    lift_store(&env, esi, 0x3u, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    eax = eax + lift_load(&env, esp, 0x2cu, 4);
    lift_store(&env, esi, 0x4u, 1, (ebx & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x0u, 1)) & 0xffu);
    ebx = lift_load(&env, esp, 0x30u, 4);
    lift_store(&env, esi, 0x5u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    ebp = lift_load(&env, esp, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ebp = ebp + eax;
    ebx = ebx + 1u;
    ebp = ebp + edx;
    lift_store(&env, esp, 0x30u, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    ebp = lift_load(&env, esp, 0x4u, 4);
    ebp = ebp + eax;
    lift_store(&env, ecx, 0x0u, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0x0u, 1)) & 0xffu);
    eax = eax + lift_load(&env, esp, 0x2cu, 4);
    lift_store(&env, ecx, 0x1u, 1, (ebx & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x0u, 1)) & 0xffu);
    ebx = lift_load(&env, esp, 0x30u, 4);
    lift_store(&env, ecx, 0x2u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    ebp = lift_load(&env, esp, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ebp = ebp + eax;
    ebx = ebx + 1u;
    ebp = ebp + edx;
    lift_store(&env, esp, 0x30u, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    ebp = lift_load(&env, esp, 0x4u, 4);
    ebp = ebp + eax;
    ebp = ebp + edx;
    lift_store(&env, ecx, 0x3u, 1, (ebx & 0xffu));
    edi = edi + 1u;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    ebp = lift_load(&env, esp, 0x2cu, 4);
    esi = esi + 0x3u;
    eax = eax + ebp;
    lift_store(&env, ecx, 0x4u, 1, (ebx & 0xffu));
    ecx = ecx + 0x3u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x0u, 1)) & 0xffu);
    edi = edi + 1u;
    lift_store(&env, ecx, 0x2u, 1, (eax & 0xffu));
    eax = lift_load(&env, esp, 0x28u, 4);
    esi = esi + 0x3u;
    eax = eax - 1u;
    ecx = ecx + 0x3u;
    lift_store(&env, esp, 0x28u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4c2082;
L_4c21d0:
    eax = lift_load(&env, esp, 0xcu, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x70u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4c21e1;
    {
        uint32_t r = lift_add(32, esp, 0x38u, &fl);
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
L_4c21e1:
    ebx = lift_load(&env, esp, 0x20u, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ebx = lift_load(&env, esp, 0x24u, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ebx = lift_load(&env, esp, 0x18u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ebx, eax + 0x0u, 4);
    lift_store(&env, esp, 0x0u, 4, ebx);
    ebx = lift_load(&env, esp, 0x8u, 4);
    ebp = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    ebp = ebp + ebx;
    lift_store(&env, esp, 0x34u, 4, ebp);
    ebp = lift_load(&env, esp, 0x10u, 4);
    ebp = ebp + eax;
    eax = lift_load(&env, esp, 0x34u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + lift_load(&env, ebp, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x4u, 4, eax);
    eax = eax ^ eax;
    ebp = lift_load(&env, esp, 0x1cu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x0u, 1)) & 0xffu);
    edi = lift_load(&env, esp, 0x0u, 4);
    ebx = ebx + ebp;
    edi = edi + eax;
    ebp = lift_load(&env, ebx, 0x0u, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, edi + 0x0u, 1)) & 0xffu);
    edi = lift_load(&env, esp, 0x4u, 4);
    edi = edi + eax;
    lift_store(&env, esi, 0x0u, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, edi + 0x0u, 1)) & 0xffu);
    eax = eax + ebp;
    lift_store(&env, esi, 0x1u, 1, (ebx & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x0u, 1)) & 0xffu);
    ebx = lift_load(&env, esp, 0x30u, 4);
    lift_store(&env, esi, 0x2u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    ebx = lift_load(&env, esp, 0x0u, 4);
    ebx = ebx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, ebx + 0x0u, 1)) & 0xffu);
    lift_store(&env, ecx, 0x0u, 1, (ebx & 0xffu));
    ebx = lift_load(&env, esp, 0x4u, 4);
    ebx = ebx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, ebx + 0x0u, 1)) & 0xffu);
    eax = eax + ebp;
    lift_store(&env, ecx, 0x1u, 1, (ebx & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x0u, 1)) & 0xffu);
    lift_store(&env, ecx, 0x2u, 1, (eax & 0xffu));
    {
        uint32_t r = lift_add(32, esp, 0x38u, &fl);
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

uint32_t lifted_f4c3be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C3BE0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C3BE0_STACK, 0, entry);
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
    esi = eax;
    ecx = lift_load(&env, eax, 0x4u, 4);
    ebx = 0xa0u;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x1c4u, 4, eax);
    lift_store(&env, eax, 0x0u, 4, 0x4c35f0u);
    lift_store(&env, eax, 0x4u, 4, 0x4c3610u);
    lift_store(&env, eax, 0x8u, 4, 0x0u);
    edx = lift_load(&env, esi, 0x12cu, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4c3d07;
L_4c3c27:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x4cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c3d1b;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x13cu, 4), 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c3d1b;
    eax = 0x1u;
L_4c3c43:
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = lift_load(&env, esi, 0xd8u, 4);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, esi, 0x24u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c3cfd;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
L_4c3c68:
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, edx, 0x8u, 4);
    {
        uint32_t r = lift_imul(32, edx, lift_load(&env, eax, 0x24u, 4), &fl);
        edx = r;
    }
    ebx = lift_load(&env, esi, 0x13cu, 4);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, edx, 0xcu, 4);
    edi = lift_load(&env, eax, 0x24u, 4);
    {
        uint32_t r = lift_imul(32, edx, edi, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    edi = eax;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = lift_load(&env, esi, 0x134u, 4);
    ebx = lift_load(&env, esi, 0x138u, 4);
    lift_store(&env, eax, 0x64u, 4, edi);
    lift_store(&env, ebp, 0xffffffd0u, 4, 0x1u);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x30u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c3d22;
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffe0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4c3d2e;
    {
        (void)lift_sub(32, edi, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4c3d2e;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x34u, 4, 0x4c3760u);
L_4c3cd2:
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    edi = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = edx + 1u;
    ecx = ecx + 0x4u;
    ebx = ebx + 1u;
    edi = edi + 0x54u;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    edx = lift_load(&env, esi, 0x24u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c3c68;
L_4c3cfd:
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
L_4c3d07:
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x19u);
    edx = lift_load(&env, esi, 0x0u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c3c27;
L_4c3d1b:
    eax = eax ^ eax;
    goto L_4c3c43;
L_4c3d22:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x34u, 4, 0x4c3770u);
    goto L_4c3cd2;
L_4c3d2e:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax + eax;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4c3d98;
    {
        (void)lift_sub(32, edi, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4c3d98;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c3d8c;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x28u, 4), 0x2u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c3d8c;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x34u, 4, 0x4c3950u);
L_4c3d54:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c3cd2;
    edi = lift_load(&env, esi, 0x4u, 4);
    edx = lift_load(&env, esi, 0x134u, 4);
    eax = lift_load(&env, esi, 0x70u, 4);
    ecx = lift_load(&env, esi, 0x138u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    ebx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, edx, 0xcu, 4, eax);
    goto L_4c3cd2;
L_4c3d8c:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x34u, 4, 0x4c3850u);
    goto L_4c3d54;
L_4c3d98:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax + eax;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4c3ddc;
    eax = (edi + edi);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4c3ddc;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c3dcd;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x28u, 4), 0x2u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c3dcd;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x34u, 4, 0x4c3a30u);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, eax, 0x8u, 4, 0x1u);
    goto L_4c3d54;
L_4c3dcd:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x34u, 4, 0x4c38b0u);
    goto L_4c3d54;
L_4c3ddc:
    edx = ecx;
    eax = ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, ebp, 0xffffffe0u, 4), &eax, &edx, &fl);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4c3e2b;
    edx = ebx;
    eax = ebx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4c3e2b;
    edx = ecx;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_store(&env, eax, 0x34u, 4, 0x4c3780u);
    eax = ecx;
    lift_idiv1(32, lift_load(&env, ebp, 0xffffffe0u, 4), &eax, &edx, &fl);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, edx, 0x8cu, 1, (eax & 0xffu));
    edx = ebx;
    eax = ebx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, edx, 0x96u, 1, (eax & 0xffu));
    goto L_4c3d54;
L_4c3e2b:
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x26u);
    edx = lift_load(&env, esi, 0x0u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c3d54;
}

uint32_t lifted_f4c4000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C4000_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C4000_STACK, 1, entry);
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
    esp = esp - 0x14cu;
    lift_store(&env, esp, 0x120u, 4, ecx);
    eax = lift_load(&env, eax, 0x144u, 4);
    ecx = 0x8u;
    eax = eax + 0x80u;
    lift_store(&env, esp, 0x100u, 4, ecx);
    lift_store(&env, esp, 0x13cu, 4, eax);
    eax = ebx;
    ebx = lift_load(&env, edx, 0x50u, 4);
    edx = esp;
L_4c4035:
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x10u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c419e;
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x20u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c419e;
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x30u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c419e;
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x40u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c419e;
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x50u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c419e;
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x60u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c419e;
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x70u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c419e;
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, eax, 0x0u, 2);
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, ebx, 0x0u, 4), &fl);
        ecx = r;
    }
    edx = edx + 0x4u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    lift_store(&env, edx, 0xfffffffcu, 4, ecx);
    lift_store(&env, edx, 0x1cu, 4, ecx);
    lift_store(&env, edx, 0x3cu, 4, ecx);
    lift_store(&env, edx, 0x5cu, 4, ecx);
    lift_store(&env, edx, 0x7cu, 4, ecx);
    lift_store(&env, edx, 0x9cu, 4, ecx);
    eax = eax + 0x2u;
    lift_store(&env, edx, 0xbcu, 4, ecx);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0xdcu, 4, ecx);
L_4c40b5:
    ebp = lift_load(&env, esp, 0x100u, 4);
    ebp = ebp - 1u;
    lift_store(&env, esp, 0x100u, 4, ebp);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c4035;
    edx = lift_load(&env, esp, 0x120u, 4);
    lift_store(&env, esp, 0x138u, 4, edx);
    edx = edx + 0x20u;
    eax = esp;
    lift_store(&env, esp, 0x124u, 4, edx);
L_4c40e6:
    edx = lift_load(&env, esp, 0x138u, 4);
    ebx = lift_load(&env, esp, 0x15cu, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, eax, 0x4u, 4);
    edx = edx + ebx;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4c448c;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c448c;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c448c;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c448c;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x14u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c448c;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x18u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c448c;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x1cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c448c;
    ecx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx + 0x10u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x5u, &fl);
        ecx = r;
    }
    ebx = lift_load(&env, esp, 0x13cu, 4);
    ecx = ecx & 0x3ffu;
    ecx = ecx + ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x0u, 1, (ebx & 0xffu));
    lift_store(&env, edx, 0x1u, 1, (ebx & 0xffu));
    lift_store(&env, edx, 0x2u, 1, (ebx & 0xffu));
    lift_store(&env, edx, 0x3u, 1, (ebx & 0xffu));
    lift_store(&env, edx, 0x4u, 1, (ebx & 0xffu));
    lift_store(&env, edx, 0x5u, 1, (ebx & 0xffu));
    lift_store(&env, edx, 0x6u, 1, (ebx & 0xffu));
    eax = eax + 0x20u;
    lift_store(&env, edx, 0x7u, 1, (ebx & 0xffu));
L_4c4172:
    esi = lift_load(&env, esp, 0x138u, 4);
    esi = esi + 0x4u;
    edi = lift_load(&env, esp, 0x124u, 4);
    lift_store(&env, esp, 0x138u, 4, esi);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4c40e6;
    {
        uint32_t r = lift_add(32, esp, 0x14cu, &fl);
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
L_4c419e:
    ecx = lift_load(&env, eax, 0x1eu, 4);
    esi = lift_load(&env, ebx, 0x40u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, esi, ecx, &fl);
        esi = r;
    }
    ecx = lift_load(&env, eax, 0x5eu, 4);
    lift_store(&env, esp, 0x110u, 4, esi);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, ebx, 0xc0u, 4), &fl);
        ecx = r;
    }
    esi = lift_load(&env, esp, 0x110u, 4);
    esi = esi + ecx;
    {
        uint32_t r = lift_imul(32, esi, 0x1151u, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_imul(32, ecx, 0xffffc4dfu, &fl);
        ecx = r;
    }
    ebp = lift_load(&env, esp, 0x110u, 4);
    lift_store(&env, esp, 0x10cu, 4, esi);
    edi = (esi + ecx);
    {
        uint32_t r = lift_imul(32, ebp, 0x187eu, &fl);
        esi = r;
    }
    ecx = lift_load(&env, esp, 0x10cu, 4);
    ebp = lift_load(&env, ebx, 0x0u, 4);
    esi = esi + ecx;
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, eax, 0x0u, 2);
    {
        uint32_t r = lift_imul(32, ebp, ecx, &fl);
        ebp = r;
    }
    ecx = lift_load(&env, eax, 0x3eu, 4);
    lift_store(&env, esp, 0x110u, 4, ebp);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, ecx, lift_load(&env, ebx, 0x80u, 4), &fl);
        ecx = r;
    }
    ebp = lift_load(&env, esp, 0x110u, 4);
    ebp = ebp + ecx;
    {
        uint32_t a = ebp;
        uint32_t r = lift_shl(32, a, 0xdu, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x148u, 4, ebp);
    ebp = lift_load(&env, esp, 0x110u, 4);
    ebp = ebp - ecx;
    ecx = ebp;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0xdu, &fl);
        ecx = r;
    }
    lift_store(&env, esp, 0x140u, 4, ecx);
    ecx = lift_load(&env, esp, 0x148u, 4);
    ecx = ecx + esi;
    lift_store(&env, esp, 0x104u, 4, ecx);
    ecx = lift_load(&env, esp, 0x148u, 4);
    ecx = ecx - esi;
    lift_store(&env, esp, 0x130u, 4, ecx);
    ecx = lift_load(&env, esp, 0x140u, 4);
    ecx = ecx + edi;
    lift_store(&env, esp, 0x108u, 4, ecx);
    ecx = lift_load(&env, esp, 0x140u, 4);
    ecx = ecx - edi;
    lift_store(&env, esp, 0x128u, 4, ecx);
    ecx = lift_load(&env, eax, 0x6eu, 4);
    esi = lift_load(&env, ebx, 0xe0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, esi, ecx, &fl);
        esi = r;
    }
    ecx = lift_load(&env, eax, 0x4eu, 4);
    lift_store(&env, esp, 0x148u, 4, esi);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    esi = lift_load(&env, ebx, 0xa0u, 4);
    {
        uint32_t r = lift_imul(32, esi, ecx, &fl);
        esi = r;
    }
    edi = lift_load(&env, eax, 0x2eu, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_imul(32, edi, lift_load(&env, ebx, 0x60u, 4), &fl);
        edi = r;
    }
    lift_store(&env, esp, 0x140u, 4, esi);
    esi = lift_load(&env, eax, 0xeu, 4);
    ebp = lift_load(&env, ebx, 0x20u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_imul(32, esi, ebp, &fl);
        esi = r;
    }
    ecx = lift_load(&env, esp, 0x148u, 4);
    ebp = lift_load(&env, esp, 0x140u, 4);
    ecx = ecx + esi;
    ebp = ebp + esi;
    {
        uint32_t r = lift_imul(32, esi, 0x300bu, &fl);
        esi = r;
    }
    lift_store(&env, esp, 0x10cu, 4, ecx);
    ecx = lift_load(&env, esp, 0x140u, 4);
    ecx = ecx + edi;
    lift_store(&env, esp, 0x110u, 4, ecx);
    ecx = lift_load(&env, esp, 0x148u, 4);
    ecx = ecx + edi;
    {
        uint32_t r = lift_imul(32, edi, 0x6254u, &fl);
        edi = r;
    }
    lift_store(&env, esp, 0x118u, 4, ebp);
    ebp = ebp + ecx;
    {
        uint32_t r = lift_imul(32, ecx, 0xffffc13bu, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, ebp, 0x25a1u, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x11cu, 4, ebp);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x148u, 4), 0x98eu, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x148u, 4, ebp);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x140u, 4), 0x41b3u, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x140u, 4, ebp);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x10cu, 4), 0xffffe333u, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x10cu, 4, ebp);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x110u, 4), 0xffffadfdu, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x110u, 4, ebp);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x118u, 4), 0xfffff384u, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x118u, 4, ebp);
    ebp = lift_load(&env, esp, 0x11cu, 4);
    lift_store(&env, esp, 0x118u, 4, lift_load(&env, esp, 0x118u, 4) + ebp);
    ecx = ecx + ebp;
    ebp = lift_load(&env, esp, 0x10cu, 4);
    ebp = ebp + ecx;
    lift_store(&env, esp, 0x148u, 4, lift_load(&env, esp, 0x148u, 4) + ebp);
    ebp = lift_load(&env, esp, 0x110u, 4);
    ebp = ebp + lift_load(&env, esp, 0x118u, 4);
    lift_store(&env, esp, 0x140u, 4, lift_load(&env, esp, 0x140u, 4) + ebp);
    ecx = ecx + lift_load(&env, esp, 0x110u, 4);
    ebp = lift_load(&env, esp, 0x118u, 4);
    edi = edi + ecx;
    ecx = lift_load(&env, esp, 0x10cu, 4);
    ecx = ecx + ebp;
    esi = esi + ecx;
    ecx = lift_load(&env, esp, 0x104u, 4);
    ecx = ecx + esi;
    ecx = ecx + 0x400u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0xbu, &fl);
        ecx = r;
    }
    lift_store(&env, edx, 0x0u, 4, ecx);
    ecx = lift_load(&env, esp, 0x104u, 4);
    ecx = ecx - esi;
    ecx = ecx + 0x400u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0xbu, &fl);
        ecx = r;
    }
    lift_store(&env, edx, 0xe0u, 4, ecx);
    ecx = lift_load(&env, esp, 0x108u, 4);
    ecx = ecx + edi;
    ecx = ecx + 0x400u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0xbu, &fl);
        ecx = r;
    }
    lift_store(&env, edx, 0x20u, 4, ecx);
    ecx = lift_load(&env, esp, 0x108u, 4);
    ecx = ecx - edi;
    ecx = ecx + 0x400u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0xbu, &fl);
        ecx = r;
    }
    esi = lift_load(&env, esp, 0x140u, 4);
    lift_store(&env, edx, 0xc0u, 4, ecx);
    ecx = lift_load(&env, esp, 0x128u, 4);
    ecx = ecx + esi;
    ecx = ecx + 0x400u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0xbu, &fl);
        ecx = r;
    }
    lift_store(&env, edx, 0x40u, 4, ecx);
    ecx = lift_load(&env, esp, 0x128u, 4);
    ecx = ecx - esi;
    ecx = ecx + 0x400u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0xbu, &fl);
        ecx = r;
    }
    ebp = lift_load(&env, esp, 0x148u, 4);
    lift_store(&env, edx, 0xa0u, 4, ecx);
    ecx = lift_load(&env, esp, 0x130u, 4);
    ecx = ecx + ebp;
    ecx = ecx + 0x400u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0xbu, &fl);
        ecx = r;
    }
    lift_store(&env, edx, 0x60u, 4, ecx);
    ecx = lift_load(&env, esp, 0x130u, 4);
    ecx = ecx - ebp;
    ecx = ecx + 0x400u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0xbu, &fl);
        ecx = r;
    }
    lift_store(&env, edx, 0x80u, 4, ecx);
    eax = eax + 0x2u;
    ebx = ebx + 0x4u;
    edx = edx + 0x4u;
    goto L_4c40b5;
L_4c448c:
    ecx = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, esp, 0x110u, 4, ecx);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x110u, 4), 0x187eu, &fl);
        edi = r;
    }
    ebx = lift_load(&env, esp, 0x110u, 4);
    ecx = lift_load(&env, eax, 0x18u, 4);
    ebx = ebx + ecx;
    {
        uint32_t r = lift_imul(32, ebx, 0x1151u, &fl);
        ebx = r;
    }
    lift_store(&env, esp, 0x114u, 4, ecx);
    {
        uint32_t r = lift_imul(32, ecx, 0xffffc4dfu, &fl);
        ecx = r;
    }
    esi = lift_load(&env, eax, 0x10u, 4);
    ecx = ecx + ebx;
    edi = edi + ebx;
    ebx = lift_load(&env, eax, 0x0u, 4);
    ebx = ebx + esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0xdu, &fl);
        ebx = r;
    }
    ebp = lift_load(&env, eax, 0x10u, 4);
    lift_store(&env, esp, 0x144u, 4, ebx);
    ebx = ebx + edi;
    esi = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esp, 0x104u, 4, ebx);
    ebx = lift_load(&env, esp, 0x144u, 4);
    esi = esi - ebp;
    ebx = ebx - edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0xdu, &fl);
        esi = r;
    }
    lift_store(&env, esp, 0x12cu, 4, ebx);
    ebx = (esi + ecx);
    esi = esi - ecx;
    ecx = lift_load(&env, eax, 0x1cu, 4);
    edi = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, esp, 0x144u, 4, ecx);
    lift_store(&env, esp, 0x108u, 4, ebx);
    ebx = lift_load(&env, esp, 0x144u, 4);
    ebx = ebx + edi;
    {
        uint32_t r = lift_imul(32, ebx, 0xffffe333u, &fl);
        ebx = r;
    }
    lift_store(&env, esp, 0x134u, 4, esi);
    esi = lift_load(&env, eax, 0x14u, 4);
    ecx = lift_load(&env, eax, 0xcu, 4);
    ebp = (esi + ecx);
    lift_store(&env, esp, 0x110u, 4, ebp);
    ebp = lift_load(&env, esp, 0x144u, 4);
    ebp = ebp + ecx;
    {
        uint32_t r = lift_imul(32, ecx, 0x6254u, &fl);
        ecx = r;
    }
    lift_store(&env, esp, 0x114u, 4, ebp);
    ebp = (esi + edi);
    {
        uint32_t r = lift_imul(32, esi, 0x41b3u, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_imul(32, edi, 0x300bu, &fl);
        edi = r;
    }
    lift_store(&env, esp, 0x118u, 4, ebp);
    ebp = lift_load(&env, esp, 0x114u, 4);
    ebp = ebp + lift_load(&env, esp, 0x118u, 4);
    {
        uint32_t r = lift_imul(32, ebp, 0x25a1u, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x11cu, 4, ebp);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x144u, 4), 0x98eu, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x144u, 4, ebp);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x110u, 4), 0xffffadfdu, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x110u, 4, ebp);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x114u, 4), 0xffffc13bu, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x114u, 4, ebp);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x118u, 4), 0xfffff384u, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x118u, 4, ebp);
    ebp = lift_load(&env, esp, 0x11cu, 4);
    lift_store(&env, esp, 0x114u, 4, lift_load(&env, esp, 0x114u, 4) + ebp);
    lift_store(&env, esp, 0x118u, 4, lift_load(&env, esp, 0x118u, 4) + ebp);
    ebp = lift_load(&env, esp, 0x114u, 4);
    ebp = ebp + ebx;
    lift_store(&env, esp, 0x144u, 4, lift_load(&env, esp, 0x144u, 4) + ebp);
    ebp = lift_load(&env, esp, 0x110u, 4);
    ebp = ebp + lift_load(&env, esp, 0x118u, 4);
    esi = esi + ebp;
    ebp = lift_load(&env, esp, 0x110u, 4);
    ebp = ebp + lift_load(&env, esp, 0x114u, 4);
    ecx = ecx + ebp;
    ebx = ebx + lift_load(&env, esp, 0x118u, 4);
    edi = edi + ebx;
    ebx = lift_load(&env, esp, 0x104u, 4);
    ebx = ebx + edi;
    ebx = ebx + 0x20000u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x12u, &fl);
        ebx = r;
    }
    ebp = lift_load(&env, esp, 0x13cu, 4);
    ebx = ebx & 0x3ffu;
    ebp = ebp + ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x0u, 1, (ebx & 0xffu));
    ebx = lift_load(&env, esp, 0x104u, 4);
    ebx = ebx - edi;
    ebx = ebx + 0x20000u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x12u, &fl);
        ebx = r;
    }
    edi = lift_load(&env, esp, 0x13cu, 4);
    ebx = ebx & 0x3ffu;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edi, ebx + 0x0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x7u, 1, (ebx & 0xffu));
    ebx = lift_load(&env, esp, 0x108u, 4);
    ebx = ebx + ecx;
    ebx = ebx + 0x20000u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x12u, &fl);
        ebx = r;
    }
    ebx = ebx & 0x3ffu;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edi, ebx + 0x0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x1u, 1, (ebx & 0xffu));
    ebx = lift_load(&env, esp, 0x108u, 4);
    ebx = ebx - ecx;
    ecx = (ebx + 0x20000u);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x12u, &fl);
        ecx = r;
    }
    ecx = ecx & 0x3ffu;
    ecx = ecx + edi;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    ecx = lift_load(&env, esp, 0x134u, 4);
    ecx = ecx + esi;
    ecx = ecx + 0x20000u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x12u, &fl);
        ecx = r;
    }
    ecx = ecx & 0x3ffu;
    ecx = ecx + edi;
    lift_store(&env, edx, 0x6u, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x2u, 1, (ebx & 0xffu));
    ecx = lift_load(&env, esp, 0x134u, 4);
    ecx = ecx - esi;
    ecx = ecx + 0x20000u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x12u, &fl);
        ecx = r;
    }
    ecx = ecx & 0x3ffu;
    ecx = ecx + edi;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    ecx = lift_load(&env, esp, 0x12cu, 4);
    lift_store(&env, edx, 0x5u, 1, (ebx & 0xffu));
    ecx = ecx + lift_load(&env, esp, 0x144u, 4);
    ecx = ecx + 0x20000u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x12u, &fl);
        ecx = r;
    }
    ecx = ecx & 0x3ffu;
    ecx = ecx + edi;
    ebp = edi;
    edi = lift_load(&env, esp, 0x144u, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    ecx = lift_load(&env, esp, 0x12cu, 4);
    ecx = ecx - edi;
    ecx = ecx + 0x20000u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x12u, &fl);
        ecx = r;
    }
    ecx = ecx & 0x3ffu;
    ecx = ecx + ebp;
    lift_store(&env, edx, 0x3u, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    eax = eax + 0x20u;
    lift_store(&env, edx, 0x4u, 1, (ebx & 0xffu));
    goto L_4c4172;
}

uint32_t lifted_f4c4730(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C4730_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C4730_STACK, 1, entry);
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
    esp = esp - 0xa8u;
    esi = eax;
    lift_store(&env, esp, 0x9cu, 4, ecx);
    eax = edx;
    edx = ebx;
    ecx = lift_load(&env, esi, 0x144u, 4);
    ecx = ecx + 0x80u;
    ebx = esp;
    lift_store(&env, esp, 0xa4u, 4, ecx);
    ecx = lift_load(&env, eax, 0x50u, 4);
    eax = 0x8u;
L_4c4763:
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x10u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c47ba;
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x20u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c47ba;
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x30u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c47ba;
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x50u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c47ba;
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x60u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c47ba;
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x70u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c47ba;
    esi = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, edx, 0x0u, 2);
    {
        uint32_t r = lift_imul(32, esi, lift_load(&env, ecx, 0x0u, 4), &fl);
        esi = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    lift_store(&env, ebx, 0x0u, 4, esi);
    lift_store(&env, ebx, 0x20u, 4, esi);
    lift_store(&env, ebx, 0x40u, 4, esi);
    lift_store(&env, ebx, 0x60u, 4, esi);
L_4c47a1:
    edx = edx + 0x2u;
    ecx = ecx + 0x4u;
    eax = eax - 1u;
    ebx = ebx + 0x4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c493c;
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4c47a1;
    goto L_4c4763;
L_4c47ba:
    esi = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, edx, 0x0u, 2);
    {
        uint32_t r = lift_imul(32, esi, lift_load(&env, ecx, 0x0u, 4), &fl);
        esi = r;
    }
    edi = lift_load(&env, edx, 0x1eu, 4);
    ebp = lift_load(&env, ecx, 0x40u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_imul(32, ebp, edi, &fl);
        ebp = r;
    }
    edi = lift_load(&env, edx, 0x5eu, 4);
    lift_store(&env, esp, 0x8cu, 4, ebp);
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_imul(32, edi, lift_load(&env, ecx, 0xc0u, 4), &fl);
        edi = r;
    }
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x8cu, 4), 0x3b21u, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_imul(32, edi, 0xffffe782u, &fl);
        edi = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0xeu, &fl);
        esi = r;
    }
    edi = edi + ebp;
    ebp = (esi + edi);
    esi = esi - edi;
    lift_store(&env, esp, 0x84u, 4, esi);
    esi = lift_load(&env, edx, 0x6eu, 4);
    edi = lift_load(&env, ecx, 0xe0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_imul(32, edi, esi, &fl);
        edi = r;
    }
    esi = lift_load(&env, edx, 0x4eu, 4);
    lift_store(&env, esp, 0x88u, 4, edi);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        esi = r;
    }
    edi = lift_load(&env, ecx, 0xa0u, 4);
    {
        uint32_t r = lift_imul(32, edi, esi, &fl);
        edi = r;
    }
    lift_store(&env, esp, 0x8cu, 4, edi);
    edi = lift_load(&env, edx, 0x2eu, 4);
    esi = lift_load(&env, ecx, 0x60u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_imul(32, edi, esi, &fl);
        edi = r;
    }
    lift_store(&env, esp, 0x80u, 4, ebp);
    esi = lift_load(&env, edx, 0xeu, 4);
    ebp = lift_load(&env, ecx, 0x20u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_imul(32, ebp, esi, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x90u, 4, ebp);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x88u, 4), 0xfffff93eu, &fl);
        esi = r;
    }
    ebp = lift_load(&env, esp, 0x8cu, 4);
    lift_store(&env, esp, 0x94u, 4, esi);
    {
        uint32_t r = lift_imul(32, ebp, 0x2e75u, &fl);
        esi = r;
    }
    ebp = lift_load(&env, esp, 0x94u, 4);
    ebp = ebp + esi;
    {
        uint32_t r = lift_imul(32, edi, 0xffffba79u, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_imul(32, edi, 0x1ccdu, &fl);
        edi = r;
    }
    ebp = ebp + esi;
    lift_store(&env, esp, 0x94u, 4, ebp);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x90u, 4), 0x21f9u, &fl);
        esi = r;
    }
    esi = esi + lift_load(&env, esp, 0x94u, 4);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x88u, 4), 0xffffefb0u, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x94u, 4, ebp);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x8cu, 4), 0xffffecc2u, &fl);
        ebp = r;
    }
    lift_store(&env, esp, 0x98u, 4, ebp);
    ebp = lift_load(&env, esp, 0x94u, 4);
    ebp = ebp + lift_load(&env, esp, 0x98u, 4);
    edi = edi + ebp;
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x90u, 4), 0x5203u, &fl);
        ebp = r;
    }
    edi = edi + ebp;
    ebp = lift_load(&env, esp, 0x80u, 4);
    ebp = ebp + edi;
    ebp = ebp + 0x800u;
    {
        uint32_t a = ebp;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        ebp = r;
    }
    lift_store(&env, ebx, 0x0u, 4, ebp);
    ebp = lift_load(&env, esp, 0x80u, 4);
    ebp = ebp - edi;
    edi = (ebp + 0x800u);
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        edi = r;
    }
    lift_store(&env, ebx, 0x60u, 4, edi);
    edi = lift_load(&env, esp, 0x84u, 4);
    edi = edi + esi;
    edi = edi + 0x800u;
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        edi = r;
    }
    lift_store(&env, ebx, 0x20u, 4, edi);
    edi = lift_load(&env, esp, 0x84u, 4);
    edi = edi - esi;
    esi = (edi + 0x800u);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        esi = r;
    }
    lift_store(&env, ebx, 0x40u, 4, esi);
    goto L_4c47a1;
L_4c493c:
    edi = lift_load(&env, esp, 0x9cu, 4);
    edx = (edi + 0x10u);
    eax = esp;
    lift_store(&env, esp, 0xa0u, 4, edx);
L_4c494f:
    ebp = lift_load(&env, esp, 0xb8u, 4);
    edx = lift_load(&env, edi, 0x0u, 4);
    ecx = lift_load(&env, eax, 0x4u, 4);
    edx = edx + ebp;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4c49bf;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c49bf;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c49bf;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x14u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c49bf;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x18u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c49bf;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x1cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c49bf;
    ecx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx + 0x10u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x5u, &fl);
        ecx = r;
    }
    ebx = lift_load(&env, esp, 0xa4u, 4);
    ecx = ecx & 0x3ffu;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, ebx + 0x0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x0u, 1, (ebx & 0xffu));
    lift_store(&env, edx, 0x1u, 1, (ebx & 0xffu));
    lift_store(&env, edx, 0x2u, 1, (ebx & 0xffu));
    eax = eax + 0x20u;
    lift_store(&env, edx, 0x3u, 1, (ebx & 0xffu));
L_4c49a5:
    esi = lift_load(&env, esp, 0xa0u, 4);
    edi = edi + 0x4u;
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4c494f;
    {
        uint32_t r = lift_add(32, esp, 0xa8u, &fl);
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
L_4c49bf:
    {
        uint32_t r = lift_imul(32, lift_load(&env, eax, 0x8u, 4), 0x3b21u, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_imul(32, lift_load(&env, eax, 0x18u, 4), 0xffffe782u, &fl);
        ebx = r;
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0xeu, &fl);
        ecx = r;
    }
    esi = esi + ebx;
    ebx = (ecx + esi);
    ecx = ecx - esi;
    lift_store(&env, esp, 0x84u, 4, ecx);
    ecx = lift_load(&env, eax, 0x1cu, 4);
    lift_store(&env, esp, 0x88u, 4, ecx);
    ecx = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, esp, 0x8cu, 4, ecx);
    ecx = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, esp, 0x90u, 4, ecx);
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x88u, 4), 0xfffff93eu, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x8cu, 4), 0x2e75u, &fl);
        ecx = r;
    }
    lift_store(&env, esp, 0x80u, 4, ebx);
    ebx = lift_load(&env, eax, 0xcu, 4);
    esi = esi + ecx;
    {
        uint32_t r = lift_imul(32, ebx, 0xffffba79u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, ebx, 0x1ccdu, &fl);
        ebx = r;
    }
    ebp = lift_load(&env, esp, 0x90u, 4);
    ecx = ecx + esi;
    {
        uint32_t r = lift_imul(32, ebp, 0x21f9u, &fl);
        esi = r;
    }
    ebp = lift_load(&env, esp, 0x88u, 4);
    ecx = ecx + esi;
    {
        uint32_t r = lift_imul(32, ebp, 0xffffefb0u, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x8cu, 4), 0xffffecc2u, &fl);
        ebp = r;
    }
    esi = esi + ebp;
    ebp = lift_load(&env, esp, 0x90u, 4);
    ebx = ebx + esi;
    {
        uint32_t r = lift_imul(32, ebp, 0x5203u, &fl);
        esi = r;
    }
    esi = esi + ebx;
    ebx = lift_load(&env, esp, 0x80u, 4);
    ebx = ebx + esi;
    ebx = ebx + 0x40000u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x13u, &fl);
        ebx = r;
    }
    ebp = lift_load(&env, esp, 0xa4u, 4);
    ebx = ebx & 0x3ffu;
    ebp = ebp + ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x0u, 1, (ebx & 0xffu));
    ebx = lift_load(&env, esp, 0x80u, 4);
    ebx = ebx - esi;
    ebx = ebx + 0x40000u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x13u, &fl);
        ebx = r;
    }
    esi = lift_load(&env, esp, 0xa4u, 4);
    ebx = ebx & 0x3ffu;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, ebx + 0x0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x3u, 1, (ebx & 0xffu));
    ebx = lift_load(&env, esp, 0x84u, 4);
    ebx = ebx + ecx;
    ebx = ebx + 0x40000u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x13u, &fl);
        ebx = r;
    }
    ebx = ebx & 0x3ffu;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, ebx + 0x0u, 1)) & 0xffu);
    lift_store(&env, edx, 0x1u, 1, (ebx & 0xffu));
    ebx = lift_load(&env, esp, 0x84u, 4);
    ebx = ebx - ecx;
    ecx = (ebx + 0x40000u);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x13u, &fl);
        ecx = r;
    }
    ecx = ecx & 0x3ffu;
    ecx = ecx + esi;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    eax = eax + 0x20u;
    lift_store(&env, edx, 0x2u, 1, (ebx & 0xffu));
    goto L_4c49a5;
}

uint32_t lifted_f4c6460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C6460_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C6460_STACK, 0, entry);
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
    esi = eax;
    lift_store(&env, esp, 0x4u, 4, ecx);
    eax = lift_load(&env, eax, 0x1ccu, 4);
    eax = lift_load(&env, eax, 0x18u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edi = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, esp, 0x14u, 4, ecx);
    eax = lift_load(&env, eax, 0x8u, 4);
    ecx = ecx ^ ecx;
    lift_store(&env, esp, 0x10u, 4, eax);
    lift_store(&env, esp, 0xcu, 4, ecx);
    eax = lift_load(&env, esi, 0x70u, 4);
    esi = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c6500;
    lift_store(&env, esp, 0x0u, 4, ebx);
    ebp = edx;
L_4c649f:
    ecx = lift_load(&env, esp, 0x0u, 4);
    ebx = lift_load(&env, esp, 0x8u, 4);
    eax = lift_load(&env, ebp, 0x0u, 4);
    ecx = lift_load(&env, ecx, 0x0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c64e3;
L_4c64af:
    edx = edx ^ edx;
    esi = lift_load(&env, esp, 0x14u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = edx + esi;
    eax = eax + 1u;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    esi = lift_load(&env, eax, 0x0u, 1);
    edx = edx & 0xffu;
    esi = lift_load(&env, edi, esi + 0x0u, 1);
    edx = edx + esi;
    esi = lift_load(&env, eax, 0x1u, 1);
    esi = esi + lift_load(&env, esp, 0x10u, 4);
    eax = eax + 1u;
    ecx = ecx + 1u;
    esi = lift_load(&env, esi, 0x0u, 1);
    ebx = ebx - 1u;
    edx = edx + esi;
    eax = eax + 1u;
    lift_store(&env, ecx, 0xffffffffu, 1, (edx & 0xffu));
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4c64af;
L_4c64e3:
    eax = lift_load(&env, esp, 0x0u, 4);
    edx = lift_load(&env, esp, 0xcu, 4);
    ecx = lift_load(&env, esp, 0x4u, 4);
    ebp = ebp + 0x4u;
    eax = eax + 0x4u;
    edx = edx + 1u;
    lift_store(&env, esp, 0x0u, 4, eax);
    lift_store(&env, esp, 0xcu, 4, edx);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c649f;
L_4c6500:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c6a20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C6A20_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C6A20_STACK, 0, entry);
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
    esp = esp - 0x20u;
    edi = eax;
    ebx = lift_load(&env, eax, 0x1ccu, 4);
    eax = lift_load(&env, ebx, 0x10u, 4);
    lift_store(&env, edi, 0x88u, 4, eax);
    eax = lift_load(&env, ebx, 0x14u, 4);
    lift_store(&env, edi, 0x84u, 4, eax);
    eax = lift_load(&env, edi, 0x58u, 4);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.cf)
        goto L_4c6c3e;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4c6c49;
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x78u, 4), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4c6a81;
    lift_store(&env, ebx, 0x4u, 4, 0x4c6460u);
L_4c6a70:
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
L_4c6a81:
    lift_store(&env, ebx, 0x4u, 4, 0x4c63a0u);
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
L_4c6a91:
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x78u, 4), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4c6bb4;
    lift_store(&env, ebx, 0x4u, 4, 0x4c6510u);
L_4c6aa2:
    ecx = lift_load(&env, ebx, 0x1cu, 4);
    lift_store(&env, ebx, 0x30u, 4, 0x0u);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4c6bc0;
L_4c6ab4:
    esi = lift_load(&env, ebx, 0x34u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4c6a70;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    eax = lift_load(&env, edi, 0x1ccu, 4);
    edx = lift_load(&env, edi, 0x78u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c6a70;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
L_4c6ad4:
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    ecx = lift_load(&env, ecx, 0x20u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c6af7;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
L_4c6aeb:
    {
        (void)lift_sub(32, ecx, lift_load(&env, eax, 0x20u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4c6bcc;
    ebx = lift_load(&env, eax, 0x34u, 4);
L_4c6af7:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4c6b8e;
    esi = lift_load(&env, ebp, 0xffffffd4u, 4);
    ebx = 0x400u;
    edx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edi = edi ^ edi;
    esi = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, edi);
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    esi = (ecx + 0xffffffffu);
    eax = eax + 0x40u;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x9u, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
L_4c6b2b:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        eax = r;
    }
    edi = lift_load(&env, ebp, 0xffffffe4u, 4);
    ecx = ecx + eax;
L_4c6b3c:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x4fffd0u, 1)) & 0xffu);
    edx = 0xffu;
    eax = eax + eax;
    edx = edx - eax;
    {
        uint32_t r = lift_imul(32, edx, 0xffu, &fl);
        edx = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c6bdd;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, esi, &eax, &edx, &fl);
L_4c6b62:
    ecx = ecx + 0x4u;
    ebx = ebx + 1u;
    lift_store(&env, ecx, 0xfffffffcu, 4, eax);
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (!fl.zf)
        goto L_4c6b3c;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = edx + 0x40u;
    ecx = ecx + 0x10u;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x10u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c6b2b;
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
L_4c6b8e:
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = (eax + 0x4u);
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x34u, 4, ebx);
    ecx = ecx + 1u;
    ebx = lift_load(&env, edx, 0x78u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c6a70;
    goto L_4c6ad4;
L_4c6bb4:
    lift_store(&env, ebx, 0x4u, 4, 0x4c6640u);
    goto L_4c6aa2;
L_4c6bc0:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c6020u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c6ab4;
L_4c6bcc:
    edx = edx + 1u;
    eax = eax + 0x4u;
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c6aeb;
    goto L_4c6af7;
L_4c6bdd:
    edx = 0u - edx;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, esi, &eax, &edx, &fl);
    eax = 0u - eax;
    goto L_4c6b62;
L_4c6bed:
    lift_store(&env, ebx, 0x4u, 4, 0x4c67a0u);
    edx = lift_load(&env, ebx, 0x44u, 4);
    lift_store(&env, ebx, 0x54u, 4, 0x0u);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4c6c35;
L_4c6c02:
    esi = lift_load(&env, edi, 0x70u, 4);
    eax = lift_load(&env, edi, 0x78u, 4);
    esi = esi + 0x2u;
    ecx = ecx ^ ecx;
    esi = esi + esi;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c6a70;
L_4c6c17:
    edx = esi;
    eax = lift_load(&env, ebx, 0x44u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c98f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx + 1u;
    eax = lift_load(&env, edi, 0x78u, 4);
    ebx = ebx + 0x4u;
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c6c17;
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
L_4c6c35:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c69c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c6c02;
L_4c6c3e:
    if (fl.cf || fl.zf)
        goto L_4c6a91;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4c6bed;
L_4c6c49:
    eax = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x30u);
    edx = lift_load(&env, edi, 0x0u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f4c70f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C70F0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C70F0_STACK, 0, entry);
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
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0xb8u;
    lift_store(&env, esp, 0x10u, 4, edx);
    eax = lift_load(&env, eax, 0x1ccu, 4);
    eax = lift_load(&env, eax, 0x18u, 4);
    lift_store(&env, esp, 0x5cu, 4, eax);
    eax = lift_load(&env, edx, 0x0u, 4);
    ebx = lift_load(&env, edx, 0xcu, 4);
    lift_store(&env, esp, 0x60u, 4, eax);
    eax = lift_load(&env, edx, 0x4u, 4);
    ebp = lift_load(&env, edx, 0x10u, 4);
    lift_store(&env, esp, 0xb0u, 4, eax);
    eax = lift_load(&env, edx, 0x8u, 4);
    ecx = lift_load(&env, esp, 0x60u, 4);
    lift_store(&env, esp, 0xb4u, 4, eax);
    eax = lift_load(&env, edx, 0x14u, 4);
    edx = lift_load(&env, esp, 0xb0u, 4);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c7518;
L_4c7142:
    edx = lift_load(&env, esp, 0xb0u, 4);
    ecx = lift_load(&env, esp, 0x60u, 4);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c71dd;
    lift_store(&env, esp, 0x44u, 4, edx);
    if (fl.sf != fl.of)
        goto L_4c71dd;
    edx = (ebp + ebp);
    lift_store(&env, esp, 0x7cu, 4, edx);
    edx = lift_load(&env, esp, 0xb0u, 4);
    esi = lift_load(&env, esp, 0x5cu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    edx = edx + esi;
    lift_store(&env, esp, 0x34u, 4, edx);
L_4c717b:
    edx = lift_load(&env, esp, 0xb4u, 4);
    lift_store(&env, esp, 0x9cu, 4, edx);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c7616;
    ecx = lift_load(&env, esp, 0x34u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    ecx = lift_load(&env, ecx, 0x0u, 4);
    edx = edx + ecx;
    lift_store(&env, esp, 0x90u, 4, edx);
L_4c71a3:
    edx = lift_load(&env, esp, 0x90u, 4);
    edi = lift_load(&env, esp, 0x7cu, 4);
    ecx = ebp;
    edx = edx + edi;
    {
        (void)lift_sub(32, ebp, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c75ee;
L_4c71ba:
    esi = edx;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, esi, 0x0u, 2)) & 0xffffu);
    edx = edx + 0x2u;
    {
        (void)lift_and(16, (edi & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4c75e5;
    edx = lift_load(&env, esp, 0x44u, 4);
    ecx = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, esp, 0xb0u, 4, edx);
    lift_store(&env, ecx, 0x4u, 4, edx);
L_4c71dd:
    edx = lift_load(&env, esp, 0xb4u, 4);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c7290;
    lift_store(&env, esp, 0x30u, 4, edx);
    if (fl.sf != fl.of)
        goto L_4c7290;
    edx = (ebp + ebp);
    lift_store(&env, esp, 0x70u, 4, edx);
    edx = lift_load(&env, esp, 0xb4u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x58u, 4, edx);
    edx = ebx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x20u, 4, edx);
L_4c7215:
    edx = lift_load(&env, esp, 0x60u, 4);
    esi = lift_load(&env, esp, 0xb0u, 4);
    lift_store(&env, esp, 0x8u, 4, edx);
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c766d;
    edx = lift_load(&env, esp, 0x58u, 4);
    lift_store(&env, esp, 0x84u, 4, edx);
    edx = lift_load(&env, esp, 0x60u, 4);
    esi = lift_load(&env, esp, 0x5cu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    edx = edx + esi;
    lift_store(&env, esp, 0x94u, 4, edx);
L_4c724b:
    edx = lift_load(&env, esp, 0x94u, 4);
    edi = lift_load(&env, esp, 0x84u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    ecx = lift_load(&env, esp, 0x70u, 4);
    edx = edx + edi;
    edx = edx + ecx;
    ecx = ebp;
    {
        (void)lift_sub(32, ebp, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c7644;
L_4c726d:
    esi = edx;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, esi, 0x0u, 2)) & 0xffffu);
    edx = edx + 0x2u;
    {
        (void)lift_and(16, (edi & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4c763b;
    edx = lift_load(&env, esp, 0x30u, 4);
    ecx = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, esp, 0xb4u, 4, edx);
    lift_store(&env, ecx, 0x8u, 4, edx);
L_4c7290:
    esi = lift_load(&env, esp, 0xb4u, 4);
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c732f;
    lift_store(&env, esp, 0x2cu, 4, ebx);
    if (fl.sf != fl.of)
        goto L_4c732f;
    edx = (ebp + ebp);
    lift_store(&env, esp, 0x68u, 4, edx);
    edx = ebx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x54u, 4, edx);
    edx = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x14u, 4, edx);
L_4c72c3:
    edx = lift_load(&env, esp, 0x60u, 4);
    edi = lift_load(&env, esp, 0xb0u, 4);
    lift_store(&env, esp, 0xcu, 4, edx);
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c76c4;
    edx = lift_load(&env, esp, 0x54u, 4);
    lift_store(&env, esp, 0x0u, 4, edx);
    edx = lift_load(&env, esp, 0x60u, 4);
    edi = lift_load(&env, esp, 0x5cu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    edx = edx + edi;
    lift_store(&env, esp, 0xa8u, 4, edx);
L_4c72f5:
    edx = lift_load(&env, esp, 0xa8u, 4);
    ecx = lift_load(&env, esp, 0x0u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    edx = edx + ecx;
    ecx = lift_load(&env, esp, 0x68u, 4);
    ecx = ecx + edx;
    edx = ebp;
    {
        (void)lift_sub(32, ebp, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c769b;
L_4c7313:
    esi = ecx;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, esi, 0x0u, 2)) & 0xffffu);
    ecx = ecx + 0x2u;
    {
        (void)lift_and(16, (edi & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4c7692;
    ecx = lift_load(&env, esp, 0x10u, 4);
    ebx = lift_load(&env, esp, 0x2cu, 4);
    lift_store(&env, ecx, 0xcu, 4, ebx);
L_4c732f:
    {
        (void)lift_sub(32, eax, ebp, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c73c7;
    lift_store(&env, esp, 0x28u, 4, ebp);
    {
        (void)lift_sub(32, ebp, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c73c7;
    edx = lift_load(&env, esp, 0xb4u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x74u, 4, edx);
    edx = (ebp + ebp);
    lift_store(&env, esp, 0x50u, 4, edx);
    edx = (eax + eax);
    lift_store(&env, esp, 0x1cu, 4, edx);
L_4c7360:
    edx = lift_load(&env, esp, 0x60u, 4);
    esi = lift_load(&env, esp, 0xb0u, 4);
    lift_store(&env, esp, 0xa0u, 4, edx);
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c7716;
    edx = lift_load(&env, esp, 0x50u, 4);
    esi = lift_load(&env, esp, 0x60u, 4);
    edi = lift_load(&env, esp, 0x5cu, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    lift_store(&env, esp, 0x88u, 4, edx);
    esi = esi + edi;
L_4c7392:
    ecx = lift_load(&env, esp, 0x74u, 4);
    edx = lift_load(&env, esi, 0x0u, 4);
    edx = edx + ecx;
    ecx = lift_load(&env, esp, 0x88u, 4);
    ecx = ecx + edx;
    edx = lift_load(&env, esp, 0xb4u, 4);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c76f5;
L_4c73b2:
    {
        (void)lift_sub(16, lift_load(&env, ecx, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c76e9;
    ecx = lift_load(&env, esp, 0x10u, 4);
    ebp = lift_load(&env, esp, 0x28u, 4);
    lift_store(&env, ecx, 0x10u, 4, ebp);
L_4c73c7:
    {
        (void)lift_sub(32, eax, ebp, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c7462;
    lift_store(&env, esp, 0x24u, 4, eax);
    if (fl.sf != fl.of)
        goto L_4c7462;
    edx = lift_load(&env, esp, 0xb4u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x64u, 4, edx);
    edx = (eax + eax);
    lift_store(&env, esp, 0x4cu, 4, edx);
    edx = (ebp + ebp);
    lift_store(&env, esp, 0x18u, 4, edx);
L_4c73f6:
    esi = lift_load(&env, esp, 0x60u, 4);
    {
        (void)lift_sub(32, esi, lift_load(&env, esp, 0xb0u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c7768;
    edx = lift_load(&env, esp, 0x4cu, 4);
    edi = lift_load(&env, esp, 0x5cu, 4);
    lift_store(&env, esp, 0x80u, 4, edx);
    edx = ((esi * 4u));
    edx = edx + edi;
    lift_store(&env, esp, 0x98u, 4, edx);
L_4c7426:
    edx = lift_load(&env, esp, 0x98u, 4);
    ecx = lift_load(&env, esp, 0x64u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    edi = lift_load(&env, esp, 0x80u, 4);
    edx = edx + ecx;
    ecx = lift_load(&env, esp, 0xb4u, 4);
    edx = edx + edi;
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c7747;
L_4c744d:
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c773b;
    ecx = lift_load(&env, esp, 0x10u, 4);
    eax = lift_load(&env, esp, 0x24u, 4);
    lift_store(&env, ecx, 0x14u, 4, eax);
L_4c7462:
    esi = lift_load(&env, esp, 0xb0u, 4);
    esi = esi - lift_load(&env, esp, 0x60u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_imul(32, esi, esi, &fl);
        esi = r;
    }
    edi = lift_load(&env, esp, 0xb4u, 4);
    ecx = ebx;
    ecx = ecx - edi;
    edx = ((ecx * 4u));
    edx = edx - ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_imul(32, edx, edx, &fl);
        edx = r;
    }
    ecx = eax;
    ecx = ecx - ebp;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, ecx, ecx, &fl);
        ecx = r;
    }
    edx = edx + esi;
    edx = edx + ecx;
    ecx = lift_load(&env, esp, 0x10u, 4);
    esi = esi ^ esi;
    lift_store(&env, ecx, 0x18u, 4, edx);
    edx = lift_load(&env, esp, 0x60u, 4);
    ecx = lift_load(&env, esp, 0xb0u, 4);
    lift_store(&env, esp, 0x38u, 4, edx);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c7505;
    edx = (ebp + ebp);
    lift_store(&env, esp, 0x6cu, 4, edx);
    edx = lift_load(&env, esp, 0x60u, 4);
    edi = lift_load(&env, esp, 0x5cu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    edx = edx + edi;
    lift_store(&env, esp, 0x3cu, 4, edx);
L_4c74d0:
    edx = lift_load(&env, esp, 0xb4u, 4);
    lift_store(&env, esp, 0x8cu, 4, edx);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c77cc;
L_4c74e6:
    edi = lift_load(&env, esp, 0x3cu, 4);
    edx = lift_load(&env, esp, 0x38u, 4);
    ecx = lift_load(&env, esp, 0xb0u, 4);
    edi = edi + 0x4u;
    edx = edx + 1u;
    lift_store(&env, esp, 0x3cu, 4, edi);
    lift_store(&env, esp, 0x38u, 4, edx);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c74d0;
L_4c7505:
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, eax, 0x1cu, 4, esi);
    {
        uint32_t r = lift_add(32, esp, 0xb8u, &fl);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4c7518:
    lift_store(&env, esp, 0x48u, 4, ecx);
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c7142;
    edx = (ebp + ebp);
    esi = lift_load(&env, esp, 0x5cu, 4);
    lift_store(&env, esp, 0x78u, 4, edx);
    edx = ((ecx * 4u));
    edx = edx + esi;
    lift_store(&env, esp, 0x40u, 4, edx);
L_4c753d:
    edx = lift_load(&env, esp, 0xb4u, 4);
    lift_store(&env, esp, 0xacu, 4, edx);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c7594;
    ecx = lift_load(&env, esp, 0x40u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    ecx = lift_load(&env, ecx, 0x0u, 4);
    edx = edx + ecx;
    lift_store(&env, esp, 0xa4u, 4, edx);
L_4c7561:
    edx = lift_load(&env, esp, 0xa4u, 4);
    edi = lift_load(&env, esp, 0x78u, 4);
    ecx = ebp;
    edx = edx + edi;
    {
        (void)lift_sub(32, ebp, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c75b8;
L_4c7574:
    esi = edx;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, esi, 0x0u, 2)) & 0xffffu);
    edx = edx + 0x2u;
    {
        (void)lift_and(16, (edi & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4c75de;
    edx = lift_load(&env, esp, 0x48u, 4);
    ecx = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, esp, 0x60u, 4, edx);
    lift_store(&env, ecx, 0x0u, 4, edx);
    goto L_4c7142;
L_4c7594:
    edi = lift_load(&env, esp, 0x40u, 4);
    edx = lift_load(&env, esp, 0x48u, 4);
    ecx = lift_load(&env, esp, 0xb0u, 4);
    edi = edi + 0x4u;
    edx = edx + 1u;
    lift_store(&env, esp, 0x40u, 4, edi);
    lift_store(&env, esp, 0x48u, 4, edx);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c753d;
    goto L_4c7142;
L_4c75b8:
    edx = lift_load(&env, esp, 0xa4u, 4);
    ecx = lift_load(&env, esp, 0xacu, 4);
    edx = edx + 0x40u;
    ecx = ecx + 1u;
    lift_store(&env, esp, 0xa4u, 4, edx);
    lift_store(&env, esp, 0xacu, 4, ecx);
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c7561;
    goto L_4c7594;
L_4c75de:
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c7574;
    goto L_4c75b8;
L_4c75e5:
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c71ba;
L_4c75ee:
    edx = lift_load(&env, esp, 0x90u, 4);
    ecx = lift_load(&env, esp, 0x9cu, 4);
    edx = edx + 0x40u;
    ecx = ecx + 1u;
    lift_store(&env, esp, 0x90u, 4, edx);
    lift_store(&env, esp, 0x9cu, 4, ecx);
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c71a3;
L_4c7616:
    edi = lift_load(&env, esp, 0x34u, 4);
    edx = lift_load(&env, esp, 0x44u, 4);
    ecx = lift_load(&env, esp, 0x60u, 4);
    edi = edi - 0x4u;
    edx = edx - 1u;
    lift_store(&env, esp, 0x34u, 4, edi);
    lift_store(&env, esp, 0x44u, 4, edx);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c717b;
    goto L_4c71dd;
L_4c763b:
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c726d;
L_4c7644:
    edi = lift_load(&env, esp, 0x94u, 4);
    edx = lift_load(&env, esp, 0x8u, 4);
    ecx = lift_load(&env, esp, 0xb0u, 4);
    edi = edi + 0x4u;
    edx = edx + 1u;
    lift_store(&env, esp, 0x94u, 4, edi);
    lift_store(&env, esp, 0x8u, 4, edx);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c724b;
L_4c766d:
    esi = lift_load(&env, esp, 0x58u, 4);
    edi = lift_load(&env, esp, 0x30u, 4);
    ecx = lift_load(&env, esp, 0x20u, 4);
    esi = esi + 0x40u;
    edi = edi + 1u;
    lift_store(&env, esp, 0x58u, 4, esi);
    lift_store(&env, esp, 0x30u, 4, edi);
    {
        (void)lift_sub(32, esi, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c7215;
    goto L_4c7290;
L_4c7692:
    edx = edx + 1u;
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c7313;
L_4c769b:
    edx = lift_load(&env, esp, 0xa8u, 4);
    ecx = lift_load(&env, esp, 0xcu, 4);
    esi = lift_load(&env, esp, 0xb0u, 4);
    edx = edx + 0x4u;
    ecx = ecx + 1u;
    lift_store(&env, esp, 0xa8u, 4, edx);
    lift_store(&env, esp, 0xcu, 4, ecx);
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c72f5;
L_4c76c4:
    edx = lift_load(&env, esp, 0x54u, 4);
    ecx = lift_load(&env, esp, 0x2cu, 4);
    esi = lift_load(&env, esp, 0x14u, 4);
    edx = edx - 0x40u;
    ecx = ecx - 1u;
    lift_store(&env, esp, 0x54u, 4, edx);
    lift_store(&env, esp, 0x2cu, 4, ecx);
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c72c3;
    goto L_4c732f;
L_4c76e9:
    edx = edx + 1u;
    ecx = ecx + 0x40u;
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c73b2;
L_4c76f5:
    edi = lift_load(&env, esp, 0xa0u, 4);
    ecx = lift_load(&env, esp, 0xb0u, 4);
    edi = edi + 1u;
    esi = esi + 0x4u;
    lift_store(&env, esp, 0xa0u, 4, edi);
    {
        (void)lift_sub(32, edi, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c7392;
L_4c7716:
    esi = lift_load(&env, esp, 0x50u, 4);
    edi = lift_load(&env, esp, 0x28u, 4);
    ecx = lift_load(&env, esp, 0x1cu, 4);
    esi = esi + 0x2u;
    edi = edi + 1u;
    lift_store(&env, esp, 0x50u, 4, esi);
    lift_store(&env, esp, 0x28u, 4, edi);
    {
        (void)lift_sub(32, esi, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c7360;
    goto L_4c73c7;
L_4c773b:
    ecx = ecx + 1u;
    edx = edx + 0x40u;
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c744d;
L_4c7747:
    edx = lift_load(&env, esp, 0x98u, 4);
    ecx = lift_load(&env, esp, 0xb0u, 4);
    edx = edx + 0x4u;
    esi = esi + 1u;
    lift_store(&env, esp, 0x98u, 4, edx);
    {
        (void)lift_sub(32, esi, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c7426;
L_4c7768:
    edx = lift_load(&env, esp, 0x4cu, 4);
    ecx = lift_load(&env, esp, 0x24u, 4);
    esi = lift_load(&env, esp, 0x18u, 4);
    edx = edx - 0x2u;
    ecx = ecx - 1u;
    lift_store(&env, esp, 0x4cu, 4, edx);
    lift_store(&env, esp, 0x24u, 4, ecx);
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c73f6;
    goto L_4c7462;
L_4c778d:
    ecx = lift_load(&env, esp, 0x4u, 4);
    edi = lift_load(&env, esp, 0x8cu, 4);
    ecx = ecx + 0x40u;
    edi = edi + 1u;
    lift_store(&env, esp, 0x4u, 4, ecx);
    lift_store(&env, esp, 0x8cu, 4, edi);
    {
        (void)lift_sub(32, ebx, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c74e6;
L_4c77af:
    edx = lift_load(&env, esp, 0x4u, 4);
    edx = edx + lift_load(&env, esp, 0x6cu, 4);
    ecx = ebp;
    {
        (void)lift_sub(32, ebp, eax, &fl);
    }
L_4c77bb:
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c778d;
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c77c4;
    esi = esi + 1u;
L_4c77c4:
    ecx = ecx + 1u;
    edx = edx + 0x2u;
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    goto L_4c77bb;
L_4c77cc:
    ecx = lift_load(&env, esp, 0x3cu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    ecx = lift_load(&env, ecx, 0x0u, 4);
    edx = edx + ecx;
    lift_store(&env, esp, 0x4u, 4, edx);
    goto L_4c77af;
}

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

uint32_t lifted_f4c9550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C9550_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C9550_STACK, 0, entry);
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
    esp = esp - 0x8u;
    ecx = eax;
    esi = lift_load(&env, eax, 0x1ccu, 4);
    eax = lift_load(&env, esi, 0x18u, 4);
    ebx = lift_load(&env, ecx, 0x58u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4c95b6;
L_4c956f:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4c95bf;
    lift_store(&env, esi, 0x4u, 4, 0x4c6ff0u);
    lift_store(&env, esi, 0x8u, 4, 0x4c90e0u);
    lift_store(&env, esi, 0x1cu, 4, 0x1u);
L_4c9588:
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = (ecx + 0x80u);
    edi = 0x1000u;
L_4c9596:
    edx = edi;
    eax = lift_load(&env, ecx, 0x0u, 4);
    ecx = ecx + 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c98f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4c9596;
    lift_store(&env, esi, 0x1cu, 4, 0x0u);
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
L_4c95b6:
    lift_store(&env, ecx, 0x58u, 4, 0x2u);
    goto L_4c956f;
L_4c95bf:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x58u, 4), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4c9680;
    lift_store(&env, esi, 0x4u, 4, 0x4c8cd0u);
L_4c95d0:
    lift_store(&env, esi, 0x8u, 4, 0x4c93c0u);
    ebx = lift_load(&env, ecx, 0x84u, 4);
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c95fa;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x38u);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, 0x1u);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c95fa:
    {
        (void)lift_sub(32, ebx, 0x100u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c961a;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x39u);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x18u, 4, 0x100u);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c961a:
    eax = lift_load(&env, ecx, 0x58u, 4);
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4c966d;
    edx = lift_load(&env, ecx, 0x70u, 4);
    edx = edx + eax;
    eax = ((edx * 4u));
    eax = eax - edx;
    eax = eax + eax;
    edx = lift_load(&env, esi, 0x20u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4c964e;
    edx = 0x1u;
    edi = lift_load(&env, ecx, 0x4u, 4);
    ebx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x20u, 4, eax);
L_4c964e:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, esi, 0x20u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c98f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x28u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c9666;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9030u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c9666:
    lift_store(&env, esi, 0x24u, 4, 0x0u);
L_4c966d:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x1cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c9588;
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
L_4c9680:
    lift_store(&env, esi, 0x4u, 4, 0x4c8be0u);
    goto L_4c95d0;
}

uint32_t lifted_f4ca040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA040_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA040_STACK, 0, entry);
    goto L_4ca050;
L_4ca050:
    goto L_4ea190;
L_4ea190:
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
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ea291;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, 0u, 0x5c8ad0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea1ee;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea1be;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea1be:
    edx = ecx;
    ecx = lift_load(&env, ecx, 0x4u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea1d7;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea1d7;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea1d7:
    ecx = lift_load(&env, edx, 0x8u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea1ee;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea1ee;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea1ee:
    ecx = lift_load(&env, 0u, 0x50af00u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea22c;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea204;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea204:
    edx = ecx;
    ecx = lift_load(&env, ecx, 0x4u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea219;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea219;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea219:
    ecx = lift_load(&env, edx, 0x8u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea22c;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea22c;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea22c:
    ecx = lift_load(&env, 0u, 0x50aefcu, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea28b;
L_4ea236:
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea242;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea242:
    ecx = lift_load(&env, ecx, 0x8u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4ea236;
    goto L_4ea28b;
L_4ea24b:
    eax = 0x50aefcu;
    edx = 0u;
    edx = edx & 0xffffu;
    ebx = ecx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9a30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x50af00u, 4);
    lift_store(&env, 0u, 0x5c8ad0u, 4, ecx);
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.cf)
        goto L_4ea283;
    ebx = lift_load(&env, 0u, 0x50af04u, 4);
    eax = lift_load(&env, ecx, 0x14u, 4);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ea283;
    lift_store(&env, 0u, 0x50af04u, 4, eax);
L_4ea283:
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5c8ac0u, 1, ((eax >> 8) & 0xffu));
L_4ea28b:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cc0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ea291:
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

uint32_t lifted_f4ca050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA050_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA050_STACK, 0, entry);
    goto L_4ea190;
L_4ea190:
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
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ea291;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cb8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = lift_load(&env, 0u, 0x5c8ad0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea1ee;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea1be;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea1be:
    edx = ecx;
    ecx = lift_load(&env, ecx, 0x4u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea1d7;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea1d7;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea1d7:
    ecx = lift_load(&env, edx, 0x8u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea1ee;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea1ee;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea1ee:
    ecx = lift_load(&env, 0u, 0x50af00u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea22c;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea204;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea204:
    edx = ecx;
    ecx = lift_load(&env, ecx, 0x4u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea219;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea219;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea219:
    ecx = lift_load(&env, edx, 0x8u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea22c;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea22c;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea22c:
    ecx = lift_load(&env, 0u, 0x50aefcu, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ea28b;
L_4ea236:
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea242;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = eax + ecx;
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea24b;
L_4ea242:
    ecx = lift_load(&env, ecx, 0x8u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4ea236;
    goto L_4ea28b;
L_4ea24b:
    eax = 0x50aefcu;
    edx = 0u;
    edx = edx & 0xffffu;
    ebx = ecx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9a30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x50af00u, 4);
    lift_store(&env, 0u, 0x5c8ad0u, 4, ecx);
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.cf)
        goto L_4ea283;
    ebx = lift_load(&env, 0u, 0x50af04u, 4);
    eax = lift_load(&env, ecx, 0x14u, 4);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ea283;
    lift_store(&env, 0u, 0x50af04u, 4, eax);
L_4ea283:
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5c8ac0u, 1, ((eax >> 8) & 0xffu));
L_4ea28b:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cc0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ea291:
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

uint32_t lifted_f4cb5a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CB5A0_STACK + 4 + 4 * 6 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CB5A0_STACK, 6, entry);
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
    ecx = lift_load(&env, esp, 0x34u, 4);
    ebx = lift_load(&env, esp, 0x3cu, 4);
    lift_store(&env, esp, 0x10u, 4, eax);
    edi = edx;
    edx = lift_load(&env, esp, 0x38u, 4);
    eax = lift_load(&env, esp, 0x28u, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x2cu, 4);
    lift_store(&env, esp, 0x4u, 4, eax);
    eax = lift_load(&env, esp, 0x30u, 4);
    ebp = 0x1u;
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4cb78d;
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, ebx, 0x0u, 4, eax);
    edx = (ebx + 0x4u);
    eax = lift_load(&env, esp, 0x0u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, edx, 0x4u, 4, eax);
    eax = lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, edx, 0x8u, 4, eax);
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb605:
    edx = lift_load(&env, esp, 0x10u, 4);
    edx = edx + lift_load(&env, esp, 0x4u, 4);
    ecx = esp;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ecx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb625:
    edx = esp;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb63f:
    edx = esp;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    edx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ecx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb659:
    ecx = lift_load(&env, esp, 0x10u, 4);
    ecx = ecx + lift_load(&env, esp, 0x4u, 4);
    edx = esp;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edx = edi;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, esi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb67d:
    edx = esp;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    ebx = lift_load(&env, ecx, 0x0u, 4);
    edx = lift_load(&env, ecx, 0x4u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb69a:
    edx = esp;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    ebx = lift_load(&env, ecx, 0x0u, 4);
    edx = lift_load(&env, ecx, 0x4u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb6b9:
    edx = esp;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0xcu, 4, eax);
    edx = edi;
    eax = lift_load(&env, ecx, 0x0u, 4);
    ebx = lift_load(&env, ecx, 0x4u, 4);
    ecx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esp, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb6de:
    edx = esp;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    edx = edi;
    eax = lift_load(&env, ecx, 0x0u, 4);
    ebx = lift_load(&env, ecx, 0x4u, 4);
    ecx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebp, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb701:
    edx = esp;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    edx = ecx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, edi, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x18u, 4), 0x0u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
    lift_store(&env, ecx, 0x18u, 4, ebx);
    ebp = eax;
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb72a:
    edx = esp;
    eax = esi;
    ebx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    edx = ecx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebp, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x18u, 4), 0x0u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    ebp = (eax & 0xffu);
    lift_store(&env, ecx, 0x18u, 4, 0x0u);
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb757:
    edx = esp;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    edx = ecx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb771:
    edx = esp;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    edx = ecx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebx, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb78d:
    esi = lift_load(&env, esp, 0x10u, 4);
    esi = esi + lift_load(&env, esp, 0x4u, 4);
    {
        (void)lift_sub(32, edx, 0x27u, &fl);
    }
    if (fl.cf)
        goto L_4cb7d1;
    if (fl.cf || fl.zf)
        goto L_4cb69a;
    {
        (void)lift_sub(32, edx, 0x2cu, &fl);
    }
    if (fl.cf)
        goto L_4cb7bd;
    if (fl.cf || fl.zf)
        goto L_4cb701;
    {
        (void)lift_sub(32, edx, 0x2eu, &fl);
    }
    if (fl.cf)
        goto L_4cb72a;
    if (fl.cf || fl.zf)
        goto L_4cb757;
    {
        (void)lift_sub(32, edx, 0x2fu, &fl);
    }
    if (fl.zf)
        goto L_4cb771;
    goto L_4cb810;
L_4cb7bd:
    {
        (void)lift_sub(32, edx, 0x28u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4cb6b9;
    {
        (void)lift_sub(32, edx, 0x29u, &fl);
    }
    if (fl.zf)
        goto L_4cb6de;
    goto L_4cb810;
L_4cb7d1:
    {
        (void)lift_sub(32, edx, 0xdu, &fl);
    }
    if (fl.cf)
        goto L_4cb7fc;
    if (fl.cf || fl.zf)
        goto L_4cb63f;
    {
        (void)lift_sub(32, edx, 0x23u, &fl);
    }
    if (fl.cf)
        goto L_4cb810;
    if (fl.cf || fl.zf)
        goto L_4cb625;
    {
        (void)lift_sub(32, edx, 0x26u, &fl);
    }
    if (fl.zf)
        goto L_4cb67d;
    eax = eax ^ eax;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
L_4cb7fc:
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (fl.cf)
        goto L_4cb810;
    if (fl.cf || fl.zf)
        goto L_4cb659;
    {
        (void)lift_sub(32, edx, 0xcu, &fl);
    }
    if (fl.zf)
        goto L_4cb605;
L_4cb810:
    eax = eax ^ eax;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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

uint32_t lifted_rtl_block_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_BLOCK_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_BLOCK_CALL_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ccbaa;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ccbaa:
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (eax + 0xfffffffcu);
    esi = lift_load(&env, ecx, 0x0u, 4);
    ebx = edx;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cea15u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_rtl_terminate_call(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_TERMINATE_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_TERMINATE_CALL_STACK, 0, entry);
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
    esi = eax;
    ecx = 0x4cd090u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, eax + 0x0u, 1, 0x0u);
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

uint32_t lifted_rtl_vararg_call(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_VARARG_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_VARARG_CALL_STACK, 0, entry);
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
    esp = esp - 0x4u;
    eax = (esp + 0x20u);
    ecx = esp;
    ebx = lift_load(&env, esp, 0x1cu, 4);
    edx = lift_load(&env, esp, 0x18u, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = lift_load(&env, esp, 0x14u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd56cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x25u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc34;
L_4cdc29:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e105au, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cdc9c;
    goto L_4cdca8;
L_4cdc8e:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cdca8;
L_4cdc9c:
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, ebx, 0x0u, 1);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    goto L_4cdd0a;
L_4cdce0:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cdcfe;
    goto L_4cdd0a;
L_4cdcf0:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cdd0a;
L_4cdcfe:
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, ebx, 0x0u, 1);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    goto L_4cdd69;
L_4cdd3a:
    eax = ebx;
    ecx = 0x20000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    goto L_4cdd69;
L_4cdd4d:
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1d24u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1d24u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0x4u, 4);
    ebx = esp;
    edx = lift_load(&env, esp, 0xcu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cd0a4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xffffffffu;
    eax = lift_load(&env, esp, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca6c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x0u, 4, 0x0u);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cf8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CF8D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CF8D0_STACK, 0, entry);
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf880u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dee00;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4dee00:
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
    esp = esp - 0xcu;
    esi = eax;
    edi = (eax + 0x1cu);
    {
        (void)lift_sub(32, lift_load(&env, edi, 0xcu, 4), 0x0u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, esp, 0x0u, 4, eax);
    if (fl.zf)
        goto L_4dee63;
L_4dee1d:
    ecx = (esp + 0x8u);
    ebx = (esp + 0x4u);
    edx = esp;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esp, 0x8u, 4);
    eax = eax + lift_load(&env, esi, 0x3cu, 4);
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x40u, 4), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4dee48;
    lift_store(&env, eax, 0x4u, 4, 0x0u);
L_4dee48:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dee5d;
    eax = lift_load(&env, esp, 0x8u, 4);
    ebx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dee5d:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dee1d;
L_4dee63:
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4def90u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
        esp = r;
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

uint32_t lifted_rtl_ancestor_search(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_RTL_ANCESTOR_SEARCH_STACK + 4 + 4 * 2 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_RTL_ANCESTOR_SEARCH_STACK, 2, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, esp, 0x8u, 4);
    edx = lift_load(&env, esp, 0xcu, 4);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4d43a6;
L_4d439d:
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4d43a6:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d1890u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d43b8;
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.zf)
        goto L_4d439d;
    goto L_4d43a6;
L_4d43b8:
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

uint32_t lifted_f4d5bf8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D5BF8_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D5BF8_STACK, 0, entry);
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
    ebx = edx;
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax - 0xe701u;
    edi = 0x1u;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4d5c40;
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4d5c16;
            case 1:
                goto L_4d5c1d;
            case 2:
                goto L_4d5c24;
            case 3:
                goto L_4d5c40;
            case 4:
                goto L_4d5c40;
            case 5:
                goto L_4d5c2b;
            default:
                return 0u;
        }
    }
L_4d5c16:
    eax = 0x14u;
    goto L_4d5c4c;
L_4d5c1d:
    eax = 0x90u;
    goto L_4d5c4c;
L_4d5c24:
    eax = 0x91u;
    goto L_4d5c4c;
L_4d5c2b:
    eax = 0x15u;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c79c8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d5c4c;
    edi = 0x8000u;
    goto L_4d5c4c;
L_4d5c40:
    lift_store(&env, ebx, 0x18u, 4, 0x1u);
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
L_4d5c4c:
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = lift_load(&env, ebx, 0x24u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1998u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = ebx;
    edx = edx & edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
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
