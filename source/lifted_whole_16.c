/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_16.h"

uint32_t lifted_ai_search(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_AI_SEARCH_STACK + 4 + 4 * 6 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_AI_SEARCH_STACK, 6, entry);
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
    esp = esp - 0x188u;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    eax = (eax & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    edx = lift_load(&env, ebp, 0x1cu, 4);
    lift_store(&env, ebp, 0xfffffff4u, 1, ((eax >> 8) & 0xffu));
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4270cf;
L_4270c4:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
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
L_4270cf:
    ebx = 0x5u;
    eax = (ebp + 0xffffffc0u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x5u;
    eax = (ebp + 0xffffffb8u);
    edx = edx ^ edx;
    ecx = 0x41u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    edi = (ebp + 0xffffff74u);
    eax = eax + 0x184u;
    ebx = (ebp + 0xffffffc8u);
    esi = eax;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
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
    ecx = lift_load(&env, ebp, 0x18u, 4);
    edx = (ebp + 0xffffff74u);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    ecx = lift_load(&env, ebp, 0x14u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4261b0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = ebx ^ ebx;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
L_42713b:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, ebp + 0xffffffc8u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_427315;
    ecx = 0x41u;
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = (ebp + 0xffffff74u);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
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
    esi = 0xcu;
    edx = edx + esi;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffff74u, 1)) & 0xffu);
    eax = edx;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0xffu, &fl);
    }
    if (fl.zf)
        goto L_42718f;
L_42717f:
    esi = esi - 1u;
    eax = eax - 1u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_42718f;
    {
        (void)lift_sub(8, lift_load(&env, eax, ebp + 0xffffff74u, 1), 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_42717f;
L_42718f:
    {
        (void)lift_sub(32, esi, 0xffffffffu, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427315;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff74u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4271b5;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff73u, 1, (edx & 0xffu));
L_4271b5:
    {
        (void)lift_sub(32, esi, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4271c9;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff72u, 1, (edx & 0xffu));
L_4271c9:
    eax = (ebp + 0xfffffff0u);
    edx = edx ^ edx;
    ebx = ebx ^ ebx;
    ecx = ecx ^ ecx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x10u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff0u, 2, (edx & 0xffffu));
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebp + 0xfffffe70u);
    eax = (ebp + 0xffffff74u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x434ee0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_427216;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffffc0u, 1)) & 0xffu);
    edx = edx ^ edx;
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) ^ (ecx & 0xffu)) & 0xffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xfffffff0u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (ecx & 0xffu));
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427216;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    lift_store(&env, edx, ebp + 0xffffffc0u, 1, (eax & 0xffu));
    lift_store(&env, edx, ebp + 0xffffffb8u, 1, (ecx & 0xffu));
L_427216:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff74u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427233;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff73u, 1, (edx & 0xffu));
L_427233:
    {
        (void)lift_sub(32, esi, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427247;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff72u, 1, (edx & 0xffu));
L_427247:
    eax = (ebp + 0xfffffff0u);
    edx = (ebp + 0xfffffe70u);
    ebx = ebx ^ ebx;
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xfffffff0u, 2, (ebx & 0xffffu));
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    eax = (ebp + 0xffffff74u);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x10u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x434ee0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_427297;
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (eax & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, ebp + 0xffffffc0u, 1)) & 0xffu);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xfffffff0u, 2)) & 0xffffu);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427297;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    lift_store(&env, edx, ebp + 0xffffffc0u, 1, (eax & 0xffu));
    eax = edx;
    lift_store(&env, eax, ebp + 0xffffffb8u, 1, 0x1u);
L_427297:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff74u, 1, (edx & 0xffu));
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4272b4;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    lift_store(&env, eax, ebp + 0xffffff73u, 1, (edx & 0xffu));
L_4272b4:
    {
        (void)lift_sub(32, esi, 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4272c6;
    esi = esi + lift_load(&env, ebp, 0xffffffecu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    lift_store(&env, esi, ebp + 0xffffff72u, 1, (eax & 0xffu));
L_4272c6:
    eax = (ebp + 0xfffffff0u);
    edx = (ebp + 0xfffffe70u);
    ebx = ebx ^ ebx;
    ecx = ecx ^ ecx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0x10u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff0u, 2, (ecx & 0xffffu));
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff74u);
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x434ee0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_427315;
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xfffffff4u, 1, ((edx >> 8) & 0xffu));
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffffc0u, 1)) & 0xffu);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xfffffff0u, 2)) & 0xffffu);
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_427315;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    ebx = (ebx & 0xffffff00u) | ((0x2u) & 0xffu);
    lift_store(&env, edx, ebp + 0xffffffc0u, 1, (eax & 0xffu));
    lift_store(&env, edx, ebp + 0xffffffb8u, 1, (ebx & 0xffu));
L_427315:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = eax + 0xdu;
    edx = edx + 1u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_42713b;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xfffffff4u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_42735d;
    eax = 0x1u;
    edx = edx ^ edx;
L_42733b:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, ebp + 0xffffffc0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), lift_load(&env, edx, ebp + 0xffffffc0u, 1), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_427347;
    edx = eax;
L_427347:
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_42733b;
    eax = lift_load(&env, ebp, 0xcu, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, ebp + 0xffffffb8u, 1)) & 0xffu);
    edx = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
L_42735d:
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xfffffff4u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4270c4;
    eax = 0x1u;
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

uint32_t lifted_f429910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F429910_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F429910_STACK, 0, entry);
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
    esp = esp - 0x3cu;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xffffffe8u, 1), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4299da;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    edx = 0x4ec1ecu;
    lift_store(&env, eax, 0x158u, 4, 0x514624u);
    ecx = 0x5145e0u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    ebx = 0x3u;
    lift_store(&env, ebp, 0xffffffe0u, 1, (eax & 0xffu));
    eax = (ebp + 0xffffffc8u);
    edi = edi ^ edi;
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
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
L_42996c:
    esi = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = ecx ^ ecx;
    esi = esi + edi;
L_429973:
    eax = (esi + ecx);
    edx = lift_load(&env, eax, 0x15cu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_429991;
    eax = edx;
    if (fl.zf)
        goto L_429991;
    ebx = lift_load(&env, edx, 0x158u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_429991:
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, ecx, 0x10u, &fl);
    }
    if (!fl.zf)
        goto L_429973;
    edi = edi + ecx;
    {
        (void)lift_sub(32, edi, 0x70u, &fl);
    }
    if (!fl.zf)
        goto L_42996c;
    edx = 0x1u;
    ecx = ecx ^ ecx;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    {
        (void)lift_and(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4299c5;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4299c5:
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    env.chain = eax;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
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
L_4299da:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    esi = 0x1u;
    edx = 0x514640u;
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
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

uint32_t lifted_f42a3c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F42A3C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F42A3C0_STACK, 0, entry);
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
    esp = esp - 0x34u;
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_42a455;
    edx = 0x4ec1ecu;
    esi = 0x51466cu;
    lift_store(&env, eax, 0x158u, 4, 0x5146f4u);
    edi = 0x3u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffe8u, 1, (ebx & 0xffu));
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
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    eax = ecx;
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42a4a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x42a480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_42a441;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42a441:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    env.chain = eax;
    eax = ecx;
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
L_42a455:
    ebx = 0x1u;
    edx = 0x514710u;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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

uint32_t lifted_f42a4c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F42A4C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F42A4C0_STACK, 0, entry);
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
    esi = eax;
    ecx = edx;
    eax = eax + 0x15cu;
    ebx = edx;
    edx = 0x3u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b2380u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3u;
    eax = (esi + 0x170u);
    ebx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b2380u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_f42b190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F42B190_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F42B190_STACK, 0, entry);
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
    esp = esp - 0x38u;
    edi = eax;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_42b25e;
    edx = 0x4ec1ecu;
    ecx = 0x5147b0u;
    lift_store(&env, edi, 0x158u, 4, 0x514814u);
    ebx = 0x3u;
    lift_store(&env, ebp, 0xffffffe4u, 1, ((eax >> 8) & 0xffu));
    eax = (ebp + 0xffffffccu);
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
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
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    ecx = edi;
    esi = (edi + 0xcu);
L_42b1ea:
    ebx = lift_load(&env, ecx, 0x15cu, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_42b205;
    eax = ebx;
    if (fl.zf)
        goto L_42b205;
    ebx = lift_load(&env, ebx, 0x158u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42b205:
    eax = lift_load(&env, ecx, 0x168u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_42b21e;
    if (fl.zf)
        goto L_42b21e;
    ebx = lift_load(&env, eax, 0x158u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42b21e:
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.zf)
        goto L_42b1ea;
    edx = edx ^ edx;
    eax = edi;
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    edx = 0x1u;
    ecx = ecx ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    edi = eax;
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    {
        (void)lift_and(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_42b24a;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42b24a:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
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
L_42b25e:
    esi = 0x1u;
    edx = 0x514830u;
    lift_store(&env, ebp, 0xffffffb8u, 4, edi);
    eax = edi;
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
}

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

uint32_t lifted_f43a1a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F43A1A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F43A1A0_STACK, 0, entry);
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
    esp = esp - 0x38u;
    edi = eax;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_43a253;
    edx = 0x4ec1ecu;
    ecx = 0x514b50u;
    lift_store(&env, edi, 0x158u, 4, 0x514b94u);
    ebx = 0x3u;
    lift_store(&env, ebp, 0xffffffe4u, 1, ((eax >> 8) & 0xffu));
    eax = (ebp + 0xffffffccu);
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
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
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    ecx = edi;
    esi = (edi + 0xcu);
L_43a1fa:
    ebx = lift_load(&env, ecx, 0x15cu, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_43a215;
    eax = ebx;
    if (fl.zf)
        goto L_43a215;
    ebx = lift_load(&env, ebx, 0x158u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43a215:
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (!fl.zf)
        goto L_43a1fa;
    edx = 0x1u;
    esi = esi ^ esi;
    eax = edi;
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    edi = eax;
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    {
        (void)lift_and(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_43a23f;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43a23f:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
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
L_43a253:
    esi = 0x1u;
    edx = 0x514bb0u;
    lift_store(&env, ebp, 0xffffffb8u, 4, edi);
    eax = edi;
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
}

uint32_t lifted_f43a970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F43A970_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F43A970_STACK, 0, entry);
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
    esp = esp - 0x34u;
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_43aa7c;
    edx = 0x4ec1ecu;
    esi = 0x514c1cu;
    lift_store(&env, eax, 0x158u, 4, 0x514cb4u);
    edi = 0x4u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffe8u, 1, (ebx & 0xffu));
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
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    eax = lift_load(&env, ecx, 0x4e8u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_43a9da;
    if (fl.zf)
        goto L_43a9da;
    esi = lift_load(&env, eax, 0x158u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43a9da:
    eax = lift_load(&env, ecx, 0x15cu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_43a9f1;
    esi = lift_load(&env, eax, 0x158u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43a9f1:
    eax = lift_load(&env, ecx, 0x450u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_43aa08;
    esi = lift_load(&env, eax, 0x158u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43aa08:
    eax = lift_load(&env, ecx, 0x468u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_43aa1c;
    esi = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43aa1c:
    eax = lift_load(&env, ecx, 0x46cu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_43aa30;
    esi = lift_load(&env, eax, 0x1cu, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43aa30:
    edx = 0x3u;
    eax = (ecx + 0x19cu);
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    edx = edx ^ edx;
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x481fb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = eax - 0x19cu;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac130u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_43aa68;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_43aa68:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    env.chain = eax;
    eax = ecx;
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
L_43aa7c:
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    eax = 0x1u;
    edx = 0x514ce0u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
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

uint32_t lifted_title_letter_first_call(const VertrixCalls *calls,
                                        const VertrixFactoryServices *services,
                                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_TITLE_LETTER_FIRST_CALL_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_TITLE_LETTER_FIRST_CALL_STACK, 0,
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
    ebx = 0x516264u;
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
    eax = (ebp + 0xffffffe0u);
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_47156c;
    edx = esi;
L_471428:
    {
        uint32_t v = 0x3u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x50e62cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffe0u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_471586;
    eax = lift_load(&env, 0u, 0x4f8a48u, 4);
    lift_store(&env, edx, 0x4u, 4, 0x2u);
    edx = lift_load(&env, 0u, 0x4f8a4cu, 4);
L_471458:
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
    edi = (eax + 0x3cu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx + 0x9cu;
    ecx = ecx ^ ecx;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = edx ^ edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = lift_load(&env, 0u, 0x4f9c02u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f420u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac950u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0xcu, 2, 0x0u);
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, esi, 0x8u, 2, (edi & 0xffffu));
    lift_store(&env, esi, 0xau, 2, (eax & 0xffffu));
    edx = 0x459be0u;
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
    eax = esi;
    lift_store(&env, esi, 0xeu, 2, (edi & 0xffffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3cu;
    eax = esi;
    ecx = lift_load(&env, esi, 0x8u, 4);
    ebx = lift_load(&env, esi, 0x6u, 4);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ad510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x30u, 2, 0x3cu);
    lift_store(&env, esi, 0x24u, 2, 0x0u);
    edx = 0xau;
    lift_store(&env, esi, 0x28u, 2, 0x14u);
    eax = esi;
    lift_store(&env, esi, 0x32u, 2, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x58u, 4, 0x3u);
    lift_store(&env, esi, 0x5cu, 4, 0x0u);
    edx = esi;
    lift_store(&env, esi, 0x60u, 4, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x44u, 1, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe0u);
    esi = esi ^ esi;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
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
L_47156c:
    edx = 0x2u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    edx = eax;
    goto L_471428;
L_471586:
    eax = lift_load(&env, 0u, 0x4f8a50u, 4);
    lift_store(&env, edx, 0x4u, 4, 0x1u);
    edx = lift_load(&env, 0u, 0x4f8a54u, 4);
    goto L_471458;
}

uint32_t lifted_f487aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F487AA0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F487AA0_STACK, 0, entry);
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
    eax = lift_load(&env, eax, 0x8u, 4);
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_487ada;
    ecx = ecx ^ ecx;
L_487abb:
    eax = lift_load(&env, edi, 0x4u, 4);
    eax = lift_load(&env, ecx, eax + 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_487acf;
    esi = lift_load(&env, eax, 0xcu, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_487acf:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx + 1u;
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.cf)
        goto L_487abb;
L_487ada:
    ebx = 0xffffffffu;
    eax = edi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8770u, eax, edx, ebx, ecx, 0, esp);
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
