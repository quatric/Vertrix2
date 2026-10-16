/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_10.h"

uint32_t lifted_palette_rgb(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PALETTE_RGB_STACK + 4 + 4 * 2 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PALETTE_RGB_STACK, 2, entry);
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
    edi = edx;
    esi = ebx;
    ebp = ecx;
    ebx = 0x10101010u;
    eax = eax & 0xffffu;
    ecx = 0x3f701010u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6775u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546840u, 4, eax);
    eax = eax ^ eax;
    ebx = 0x10101010u;
    eax = (eax & 0xffff0000u) | (((edi & 0xffffu)) & 0xffffu);
    ecx = 0x3f701010u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6775u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546844u, 4, eax);
    eax = eax ^ eax;
    ebx = 0x10101010u;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3f701010u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6775u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x546844u, 4);
    lift_store(&env, 0u, 0x546848u, 4, eax);
    eax = lift_load(&env, 0u, 0x546840u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.zf || fl.sf != fl.of)
        goto L_474760;
    esi = lift_load(&env, 0u, 0x546840u, 4);
L_4745ee:
    edx = lift_load(&env, 0u, 0x546848u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.zf || fl.sf != fl.of)
        goto L_47476b;
L_474601:
    eax = lift_load(&env, 0u, 0x546840u, 4);
    edx = lift_load(&env, 0u, 0x546844u, 4);
    lift_store(&env, 0u, 0x54685cu, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_474776;
    esi = lift_load(&env, 0u, 0x546840u, 4);
L_474623:
    edx = lift_load(&env, 0u, 0x546848u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_474781;
    edx = esi;
L_474638:
    eax = lift_load(&env, 0u, 0x54685cu, 4);
    lift_store(&env, 0u, 0x546858u, 4, edx);
    lift_store(&env, 0u, 0x546854u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_47478c;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x54685cu, 4);
    esi = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d81feu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546850u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_474796;
L_47466f:
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x54684cu, 4, edx);
    lift_store(&env, 0u, 0x54686cu, 4, edx);
L_47467d:
    ecx = 0x40590000u;
    eax = lift_load(&env, 0u, 0x546850u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x40590000u;
    lift_store(&env, 0u, 0x546850u, 4, eax);
    eax = lift_load(&env, 0u, 0x546854u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546854u, 4, eax);
    eax = lift_load(&env, 0u, 0x54684cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0x0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x546850u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546850u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546864u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb57cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_4748e6;
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, eax, 0x0u, 2, (esi & 0xffffu));
L_474710:
    eax = lift_load(&env, 0u, 0x546854u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546854u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546868u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb57cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_4748f8;
    eax = lift_load(&env, esp, 0x14u, 4);
    lift_store(&env, eax, 0x0u, 2, (esi & 0xffffu));
    eax = lift_load(&env, 0u, 0x54686cu, 4);
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
L_474760:
    esi = lift_load(&env, 0u, 0x546844u, 4);
    goto L_4745ee;
L_47476b:
    esi = lift_load(&env, 0u, 0x546848u, 4);
    goto L_474601;
L_474776:
    esi = lift_load(&env, 0u, 0x546844u, 4);
    goto L_474623;
L_474781:
    edx = lift_load(&env, 0u, 0x546848u, 4);
    goto L_474638;
L_47478c:
    lift_store(&env, 0u, 0x546850u, 4, eax);
    goto L_47466f;
L_474796:
    eax = 0x1u;
    edx = lift_load(&env, 0u, 0x54685cu, 4);
    lift_store(&env, 0u, 0x54686cu, 4, eax);
    eax = lift_load(&env, 0u, 0x546840u, 4);
    lift_store(&env, 0u, 0x546860u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.zf)
        goto L_474860;
    eax = lift_load(&env, 0u, 0x546844u, 4);
    edx = lift_load(&env, 0u, 0x54685cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.zf)
        goto L_47489f;
    eax = lift_load(&env, 0u, 0x546848u, 4);
    edx = lift_load(&env, 0u, 0x54685cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8082u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (!fl.zf)
        goto L_474835;
    eax = lift_load(&env, 0u, 0x546840u, 4);
    edx = lift_load(&env, 0u, 0x546844u, 4);
    ecx = 0x404e0000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    eax = esi;
    edi = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    ecx = edx;
    eax = ebx;
    edx = edi;
    ebx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x406e0000u;
L_474824:
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_47482b:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54684cu, 4, eax);
L_474835:
    eax = lift_load(&env, 0u, 0x54684cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_47467d;
    edx = 0x43b40000u;
    eax = lift_load(&env, 0u, 0x54684cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d80a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54684cu, 4, eax);
    goto L_47467d;
L_474860:
    eax = lift_load(&env, 0u, 0x546844u, 4);
    edx = lift_load(&env, 0u, 0x546848u, 4);
    ecx = 0x404e0000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = esi;
    ebx = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edi = edx;
    eax = ecx;
    edx = ebx;
    ebx = esi;
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_47482b;
L_47489f:
    eax = lift_load(&env, 0u, 0x546848u, 4);
    edx = lift_load(&env, 0u, 0x546840u, 4);
    ecx = 0x404e0000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    eax = esi;
    ebx = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    edi = edx;
    eax = ecx;
    edx = ebx;
    ebx = esi;
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb652u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x405e0000u;
    goto L_474824;
L_4748e6:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    edx = lift_load(&env, esp, 0x10u, 4);
    eax = eax + 1u;
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    goto L_474710;
L_4748f8:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    edx = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x54686cu, 4);
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

uint32_t lifted_palette_color(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PALETTE_COLOR_STACK + 4 + 4 * 2 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PALETTE_COLOR_STACK, 2, entry);
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
    esi = ebx;
    edi = ecx;
    eax = eax & 0xffffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54687cu, 4, eax);
    eax = eax ^ eax;
    ebx = 0x47ae147bu;
    eax = (eax & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    ecx = 0x3f847ae1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6775u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546880u, 4, eax);
    eax = eax ^ eax;
    ebx = 0x47ae147bu;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3f847ae1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d6775u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x546880u, 4);
    lift_store(&env, 0u, 0x546884u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_474bc5;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x54687cu, 4), 0x43b40000u, &fl);
    }
    if (!fl.zf)
        goto L_47498d;
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x54687cu, 4, ebx);
L_47498d:
    ebx = 0x11111111u;
    eax = lift_load(&env, 0u, 0x54687cu, 4);
    ecx = 0x3f911111u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54687cu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54689cu, 2, (eax & 0xffffu));
    eax = eax & 0xffffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x54687cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546888u, 4, eax);
    eax = lift_load(&env, 0u, 0x546884u, 4);
    edx = lift_load(&env, 0u, 0x546880u, 4);
    lift_store(&env, 0u, 0x54688cu, 4, eax);
    eax = 0x3f800000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546884u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x546888u, 4);
    lift_store(&env, 0u, 0x546898u, 4, eax);
    eax = 0x3f800000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546880u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x3f800000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546884u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x546888u, 4);
    lift_store(&env, 0u, 0x546890u, 4, eax);
    eax = lift_load(&env, 0u, 0x546880u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = 0x3f800000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546884u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d8177u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x54689cu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x546894u, 4, eax);
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_474bd9;
    eax = lift_load(&env, 0u, 0x54688cu, 4);
    lift_store(&env, 0u, 0x546870u, 4, eax);
    eax = lift_load(&env, 0u, 0x546890u, 4);
    lift_store(&env, 0u, 0x546874u, 4, eax);
    eax = lift_load(&env, 0u, 0x546898u, 4);
L_474a90:
    lift_store(&env, 0u, 0x546878u, 4, eax);
L_474a95:
    ecx = 0x406fe000u;
    eax = lift_load(&env, 0u, 0x546870u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x406fe000u;
    lift_store(&env, 0u, 0x546870u, 4, eax);
    eax = lift_load(&env, 0u, 0x546874u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x406fe000u;
    lift_store(&env, 0u, 0x546874u, 4, eax);
    eax = lift_load(&env, 0u, 0x546878u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb606u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x546878u, 4, eax);
    eax = lift_load(&env, 0u, 0x546870u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546870u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5468a0u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb57cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_474c9c;
    lift_store(&env, edi, 0x0u, 2, (esi & 0xffffu));
L_474b36:
    eax = lift_load(&env, 0u, 0x546874u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546874u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5468a4u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb57cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_474caa;
    eax = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, eax, 0x0u, 2, (esi & 0xffffu));
L_474b7b:
    eax = lift_load(&env, 0u, 0x546878u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d67b2u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    ecx = 0x3fe00000u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d74a6u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, 0u, 0x546878u, 4);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d809cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5468a8u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb526u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb57cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    if (fl.sf == fl.of)
        goto L_474cbc;
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, eax, 0x0u, 2, (esi & 0xffffu));
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
L_474bc5:
    lift_store(&env, 0u, 0x546878u, 4, eax);
    lift_store(&env, 0u, 0x546874u, 4, eax);
    lift_store(&env, 0u, 0x546870u, 4, eax);
    goto L_474a95;
L_474bd9:
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_474bfa;
    edx = lift_load(&env, 0u, 0x54688cu, 4);
    lift_store(&env, 0u, 0x546870u, 4, eax);
    eax = lift_load(&env, 0u, 0x546898u, 4);
    lift_store(&env, 0u, 0x546874u, 4, edx);
    goto L_474a90;
L_474bfa:
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_474c23;
    eax = lift_load(&env, 0u, 0x54688cu, 4);
    lift_store(&env, 0u, 0x546874u, 4, eax);
    eax = lift_load(&env, 0u, 0x546890u, 4);
    lift_store(&env, 0u, 0x546878u, 4, eax);
    eax = lift_load(&env, 0u, 0x546898u, 4);
    lift_store(&env, 0u, 0x546870u, 4, eax);
    goto L_474a95;
L_474c23:
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_474c49;
    edx = lift_load(&env, 0u, 0x54688cu, 4);
    lift_store(&env, 0u, 0x546874u, 4, eax);
    eax = lift_load(&env, 0u, 0x546898u, 4);
    lift_store(&env, 0u, 0x546878u, 4, edx);
    lift_store(&env, 0u, 0x546870u, 4, eax);
    goto L_474a95;
L_474c49:
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_474c72;
    eax = lift_load(&env, 0u, 0x54688cu, 4);
    lift_store(&env, 0u, 0x546878u, 4, eax);
    eax = lift_load(&env, 0u, 0x546890u, 4);
    lift_store(&env, 0u, 0x546870u, 4, eax);
    eax = lift_load(&env, 0u, 0x546898u, 4);
    lift_store(&env, 0u, 0x546874u, 4, eax);
    goto L_474a95;
L_474c72:
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_474a95;
    edx = lift_load(&env, 0u, 0x54688cu, 4);
    lift_store(&env, 0u, 0x546878u, 4, eax);
    eax = lift_load(&env, 0u, 0x546898u, 4);
    lift_store(&env, 0u, 0x546870u, 4, edx);
    lift_store(&env, 0u, 0x546874u, 4, eax);
    goto L_474a95;
L_474c9c:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    eax = eax + 1u;
    lift_store(&env, edi, 0x0u, 2, (eax & 0xffffu));
    goto L_474b36;
L_474caa:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    edx = lift_load(&env, esp, 0xcu, 4);
    eax = eax + 1u;
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    goto L_474b7b;
L_474cbc:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    edx = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
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

uint32_t lifted_surface_fade(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_SURFACE_FADE_STACK + 4 + 4 * 2 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_SURFACE_FADE_STACK, 2, entry);
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
    esp = esp - 0xb0u;
    esi = eax;
    lift_store(&env, ebp, 0xffffff50u, 4, edx);
    lift_store(&env, ebp, 0xffffff8cu, 4, ebx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0xcu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff0u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0xdu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x558a79u, 1, (eax & 0xffu));
    eax = lift_load(&env, esi, 0x4u, 4);
    lift_store(&env, ebp, 0xffffff74u, 4, eax);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_47a081;
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
L_47a081:
    ebx = ebx ^ ebx;
    edx = lift_load(&env, ebp, 0x8u, 4);
    ebx = (ebx & 0xffffff00u) | ((((eax >> 8) & 0xffu)) & 0xffu);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0x8u, 4);
    ebx = lift_load(&env, ebp, 0xffffff8cu, 4);
    edi = eax;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffff88u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x558a79u, 1)) & 0xffu);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = esi;
    lift_store(&env, edi, 0xdu, 1, (eax & 0xffu));
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffff50u, 4);
    ecx = ecx ^ ecx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47ce10u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    ecx = 0x64u;
    edx = lift_load(&env, ebp, 0xcu, 4);
    ebx = lift_load(&env, ebp, 0xffffff8cu, 4);
    ecx = ecx - edx;
    edx = lift_load(&env, ebp, 0xffffff74u, 4);
    {
        uint32_t r = lift_imul(32, edx, ebx, &fl);
        edx = r;
    }
    eax = lift_load(&env, ebp, 0xcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ecx = r;
    }
    ebx = 0x558cf0u;
    eax = eax + 0x558cf0u;
    ebx = ebx + ecx;
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffff90u, 4, ebx);
    ecx = ecx - 1u;
    ebx = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, ebp, 0xffffff4cu, 4, ecx);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    ebx = ebx - 1u;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_47a377;
    lift_store(&env, 0u, 0x55f1f0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff90u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x55f1f4u, 4, eax);
    eax = lift_load(&env, esi, 0x0u, 4);
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffff50u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    esi = esi ^ esi;
    edx = edx + eax;
    lift_store(&env, ebp, 0xffffffc8u, 4, esi);
    lift_store(&env, ebp, 0xffffffa0u, 4, edx);
    eax = lift_load(&env, edi, 0x0u, 4);
    edi = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47a366;
    eax = lift_load(&env, ebp, 0xffffff4cu, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff74u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffb0u, 4, ebx);
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
L_47a159:
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffff70u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    lift_store(&env, ebp, 0xffffff84u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47a33e;
L_47a178:
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    ecx = ecx ^ ecx;
    esi = esi ^ esi;
    ebx = ebx ^ ebx;
    edi = edi ^ edi;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47a1a5;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = eax - lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    ebx = (ebx & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edi = 0x1u;
    esi = edx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        esi = r;
    }
L_47a1a5:
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffb0u, 4), &fl);
    }
    if (!fl.cf)
        goto L_47a1e2;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    ebx = ebx + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    esi = esi + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    ecx = ecx + eax;
L_47a1e2:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffff70u, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47a222;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, eax, 0xfffffffcu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    ebx = ebx + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0xfffffffcu, 2)) & 0xffffu);
    eax = eax - 0x4u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    esi = esi + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    ecx = ecx + eax;
L_47a222:
    eax = lift_load(&env, ebp, 0xffffff70u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffb4u, 4), &fl);
    }
    if (!fl.cf)
        goto L_47a262;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    ebx = ebx + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x4u, 1)) & 0xffu);
    esi = esi + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    ecx = ecx + eax;
L_47a262:
    eax = ebx;
    edx = edx ^ edx;
    lift_div1(32, edi, &eax, &edx, &fl);
    ebx = eax;
    edx = edx ^ edx;
    eax = esi;
    lift_div1(32, edi, &eax, &edx, &fl);
    esi = eax;
    edx = edx ^ edx;
    eax = ecx;
    lift_div1(32, edi, &eax, &edx, &fl);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        ebx = r;
    }
    ecx = eax;
    eax = esi;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = eax | ebx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = eax | ecx;
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    edx = lift_load(&env, 0u, 0x55f1f0u, 4);
    esi = lift_load(&env, ecx, edx + 0x0u, 1);
    ecx = eax;
    ebx = ebx ^ ebx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | (((ecx & 0xffu)) & 0xffu);
    ecx = lift_load(&env, 0u, 0x55f1f4u, 4);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, ebx + 0x0u, 1)) & 0xffu);
    ebx = ebx & 0xffu;
    edi = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = esi + ebx;
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, edi, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ebx = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        esi = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, ebx + 0x0u, 1)) & 0xffu);
    ebx = ebx & 0xffu;
    lift_store(&env, ebp, 0xffffff7cu, 4, ebx);
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ebx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, ebx + 0x0u, 1)) & 0xffu);
    edi = lift_load(&env, ebp, 0xffffff7cu, 4);
    ebx = ebx & 0xffu;
    ebx = ebx + edi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ebx = r;
    }
    ebx = ebx | esi;
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = lift_load(&env, esi, 0x0u, 1);
    edx = edx + esi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    edx = edx & 0xffu;
    eax = eax & 0xffu;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    eax = eax & 0xffu;
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0xffffff84u, 4);
    eax = eax | ebx;
    edi = (edx + 0x4u);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ebp, 0xffffff70u, 4);
    lift_store(&env, ebp, 0xffffff84u, 4, edi);
    eax = eax + 0x4u;
    edx = edx + 1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffff70u, 4, edx);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.cf)
        goto L_47a178;
L_47a33e:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffa4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffa0u, 4);
    esi = lift_load(&env, ebp, 0xffffffc8u, 4);
    edi = lift_load(&env, ebp, 0x8u, 4);
    esi = esi + 1u;
    ecx = ecx + eax;
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    lift_store(&env, ebp, 0xffffffa4u, 4, ecx);
    ebx = ebx + eax;
    lift_store(&env, ebp, 0xffffffc8u, 4, esi);
    lift_store(&env, ebp, 0xffffffa0u, 4, ebx);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.cf)
        goto L_47a159;
L_47a366:
    eax = lift_load(&env, ebp, 0xffffff88u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_47a377:
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_47a366;
    lift_store(&env, 0u, 0x55f1f0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff90u, 4);
    edx = edx + edx;
    lift_store(&env, 0u, 0x55f1f4u, 4, eax);
    eax = lift_load(&env, esi, 0x0u, 4);
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffff50u, 4);
    eax = eax + eax;
    edx = edx + eax;
    eax = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff74u, 4);
    eax = eax + eax;
    lift_store(&env, ebp, 0xffffff54u, 4, edx);
    lift_store(&env, ebp, 0xffffff94u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x558a79u, 1)) & 0xffu);
    eax = eax + eax;
    {
        (void)lift_sub(8, (edx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_47a79e;
    edx = edx ^ edx;
    ecx = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, ebp, 0xffffff6cu, 4, edx);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47a366;
    edx = lift_load(&env, ebp, 0xffffff4cu, 4);
    lift_store(&env, ebp, 0xffffff58u, 4, eax);
    lift_store(&env, ebp, 0xffffff68u, 4, ebx);
    lift_store(&env, ebp, 0xffffff64u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff94u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    lift_store(&env, ebp, 0xffffff98u, 4, edx);
L_47a3f2:
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff54u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47a6de;
L_47a411:
    eax = lift_load(&env, ebp, 0xffffff6cu, 4);
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    esi = esi ^ esi;
    edi = edi ^ edi;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47a47c;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax - lift_load(&env, ebp, 0xffffffbcu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0xf8u) & 0xffu) << 8);
    ecx = edx;
    ecx = ecx & 0xffffu;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        ecx = r;
    }
    edx = edx & 0x7e0u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1fu) & 0xffu);
    edx = edx | ecx;
    eax = eax & 0xffffu;
    eax = eax | edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    esi = (edx & 0xffu);
    edx = edx ^ edx;
    edi = 0x1u;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    ecx = ecx ^ ecx;
    ebx = edx;
    ecx = (ecx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ebx = r;
    }
L_47a47c:
    eax = lift_load(&env, ebp, 0xffffff6cu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffff68u, 4), &fl);
    }
    if (fl.cf)
        goto L_47a717;
L_47a48e:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd8u, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47a519;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0xfffffffeu, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0xf8u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff80u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0xfffffffeu, 2)) & 0xffffu);
    edx = edx & 0x7e0u;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    eax = eax - 0x2u;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff80u, 4);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx | lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1fu) & 0xffu);
    eax = eax & 0xffffu;
    eax = eax | edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    esi = esi + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    ebx = ebx + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    ecx = ecx + eax;
L_47a519:
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffff64u, 4), &fl);
    }
    if (!fl.cf)
        goto L_47a5a7;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x2u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0xf8u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff80u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x2u, 2)) & 0xffffu);
    edx = edx & 0x7e0u;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x2u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff80u, 4);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx | lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1fu) & 0xffu);
    eax = eax & 0xffffu;
    eax = eax | edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    esi = esi + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    ebx = ebx + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    ecx = ecx + eax;
L_47a5a7:
    eax = esi;
    edx = edx ^ edx;
    lift_div1(32, edi, &eax, &edx, &fl);
    esi = eax;
    edx = edx ^ edx;
    eax = ebx;
    lift_div1(32, edi, &eax, &edx, &fl);
    ebx = eax;
    edx = edx ^ edx;
    eax = ecx;
    lift_div1(32, edi, &eax, &edx, &fl);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        esi = r;
    }
    ecx = eax;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ebx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    ebx = ebx | esi;
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    ecx = ecx | ebx;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) & 0xf8u) & 0xffu) << 8);
    ebx = eax;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = ebx & 0xffffu;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        ebx = r;
    }
    eax = eax & 0x7e0u;
    eax = eax & 0xffffu;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebx = ebx | eax;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx ^ edx;
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1fu) & 0xffu);
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    edx = edx | ebx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x55f1f0u, 4);
    eax = eax & 0xffu;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, eax + 0x0u, 1)) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, ebp, 0xffffff7cu, 4, eax);
    eax = ecx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffff80u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff80u, 1)) & 0xffu);
    esi = (eax & 0xffu);
    eax = lift_load(&env, 0u, 0x55f1f4u, 4);
    edi = lift_load(&env, ebp, 0xffffff7cu, 4);
    esi = lift_load(&env, esi, eax + 0x0u, 1);
    esi = esi + edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffff7cu, 4, esi);
    esi = esi ^ esi;
    esi = (esi & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        esi = r;
    }
    esi = lift_load(&env, esi, ebx + 0x0u, 1);
    lift_store(&env, ebp, 0xffffff80u, 4, esi);
    esi = esi ^ esi;
    esi = (esi & 0xffff0000u) | (((ecx & 0xffffu)) & 0xffffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        esi = r;
    }
    edi = lift_load(&env, ebp, 0xffffff80u, 4);
    esi = lift_load(&env, esi, eax + 0x0u, 1);
    esi = esi + edi;
    edi = lift_load(&env, ebp, 0xffffff7cu, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        esi = r;
    }
    esi = esi | edi;
    edx = edx & 0xffu;
    edx = edx + ebx;
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((ecx & 0xffu)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x0u, 1)) & 0xffu);
    eax = eax & 0xffu;
    eax = eax + ebx;
    eax = eax | esi;
    ecx = eax;
    edx = eax;
    ecx = ecx & 0xf80000u;
    edx = edx & 0xfc00u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x5u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = eax & 0xf8u;
    edx = edx | ecx;
    ebx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax | edx;
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x3u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    eax = (edx + 0x2u);
    ecx = ecx + 1u;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    edx = edx + 0x2u;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.cf)
        goto L_47a411;
L_47a6de:
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    ecx = lift_load(&env, ebp, 0xffffffa8u, 4);
    ebx = lift_load(&env, ebp, 0xffffff54u, 4);
    esi = lift_load(&env, ebp, 0xffffff6cu, 4);
    edi = lift_load(&env, ebp, 0x8u, 4);
    esi = esi + 1u;
    ecx = ecx + eax;
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    lift_store(&env, ebp, 0xffffffa8u, 4, ecx);
    ebx = ebx + eax;
    lift_store(&env, ebp, 0xffffff6cu, 4, esi);
    lift_store(&env, ebp, 0xffffff54u, 4, ebx);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (!fl.cf)
        goto L_47a366;
    goto L_47a3f2;
L_47a717:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax + lift_load(&env, ebp, 0xffffff58u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0xf8u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff80u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = edx & 0x7e0u;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff80u, 4);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx | lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1fu) & 0xffu);
    eax = eax & 0xffffu;
    eax = eax | edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    esi = esi + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    ebx = ebx + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    ecx = ecx + eax;
    goto L_47a48e;
L_47a79e:
    esi = esi ^ esi;
    edi = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, ebp, 0xffffffc4u, 4, esi);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47a366;
    edx = lift_load(&env, ebp, 0xffffff4cu, 4);
    lift_store(&env, ebp, 0xffffff5cu, 4, eax);
    lift_store(&env, ebp, 0xffffffacu, 4, ebx);
    lift_store(&env, ebp, 0xffffff60u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff94u, 4);
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    lift_store(&env, ebp, 0xffffff78u, 4, edx);
L_47a7cf:
    eax = lift_load(&env, ebp, 0xffffff54u, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47aaae;
L_47a7ee:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    esi = esi ^ esi;
    ebx = ebx ^ ebx;
    ecx = ecx ^ ecx;
    edi = edi ^ edi;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47a849;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = eax - lift_load(&env, ebp, 0xffffffb8u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0x7cu) & 0xffu) << 8);
    edx = edx & 0xffffu;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) & 0x3e0u) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        ecx = r;
    }
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1fu) & 0xffu);
    edx = edx | ecx;
    eax = eax & 0xffffu;
    eax = eax | edx;
    edi = 0x1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    ecx = ecx ^ ecx;
    edx = eax;
    ebx = (ebx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    esi = (eax & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ebx = r;
    }
    ecx = (ecx & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
L_47a849:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffacu, 4), &fl);
    }
    if (fl.cf)
        goto L_47aae4;
L_47a855:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_47a8e0;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0xfffffffeu, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0x7cu) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff80u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0xfffffffeu, 2)) & 0xffffu);
    edx = edx & 0x3e0u;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    eax = eax - 0x2u;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff80u, 4);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx | lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1fu) & 0xffu);
    eax = eax & 0xffffu;
    eax = eax | edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    ecx = ecx + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    ebx = ebx + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    esi = esi + eax;
L_47a8e0:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffff60u, 4), &fl);
    }
    if (!fl.cf)
        goto L_47a96e;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x2u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0x7cu) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff80u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x2u, 2)) & 0xffffu);
    edx = edx & 0x3e0u;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x2u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff80u, 4);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx | lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1fu) & 0xffu);
    eax = eax & 0xffffu;
    eax = eax | edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    ecx = ecx + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    ebx = ebx + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    esi = esi + eax;
L_47a96e:
    eax = ecx;
    edx = edx ^ edx;
    lift_div1(32, edi, &eax, &edx, &fl);
    ecx = eax;
    edx = edx ^ edx;
    eax = ebx;
    lift_div1(32, edi, &eax, &edx, &fl);
    ebx = eax;
    edx = edx ^ edx;
    eax = esi;
    lift_div1(32, edi, &eax, &edx, &fl);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ebx = r;
    }
    ebx = ebx | ecx;
    ebx = ebx | eax;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) & 0x7cu) & 0xffu) << 8);
    ecx = eax;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    ecx = ecx & 0xffffu;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        ecx = r;
    }
    eax = eax & 0x3e0u;
    eax = eax & 0xffffu;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    ecx = ecx | eax;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx ^ edx;
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1fu) & 0xffu);
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    edx = edx | ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    eax = edx;
    ecx = ecx ^ ecx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = lift_load(&env, 0u, 0x55f1f0u, 4);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    lift_store(&env, ebp, 0xffffff7cu, 4, ecx);
    ecx = ebx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffff80u, 4, ecx);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff80u, 1)) & 0xffu);
    esi = (ecx & 0xffu);
    ecx = lift_load(&env, 0u, 0x55f1f4u, 4);
    edi = lift_load(&env, ebp, 0xffffff7cu, 4);
    esi = lift_load(&env, ecx, esi + 0x0u, 1);
    esi = esi + edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffff80u, 4, esi);
    esi = esi ^ esi;
    esi = (esi & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        esi = r;
    }
    esi = lift_load(&env, esi, eax + 0x0u, 1);
    lift_store(&env, ebp, 0xffffff48u, 4, esi);
    esi = esi ^ esi;
    esi = (esi & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        esi = r;
    }
    esi = lift_load(&env, ecx, esi + 0x0u, 1);
    lift_store(&env, ebp, 0xffffff7cu, 4, esi);
    esi = lift_load(&env, ebp, 0xffffff48u, 4);
    esi = esi + lift_load(&env, ebp, 0xffffff7cu, 4);
    edi = lift_load(&env, ebp, 0xffffff80u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        esi = r;
    }
    esi = esi | edi;
    edx = edx & 0xffu;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x0u, 1)) & 0xffu);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ecx = ecx + eax;
    eax = eax ^ eax;
    edx = edx & 0xffu;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    eax = eax + edx;
    eax = eax | esi;
    ecx = eax;
    edx = eax;
    ecx = ecx & 0xf80000u;
    edx = edx & 0xf800u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x6u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x3u, &fl);
        edx = r;
    }
    eax = eax & 0xf8u;
    edx = edx | ecx;
    ebx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax | edx;
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x3u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    eax = (edx + 0x2u);
    ecx = ecx + 1u;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    edx = edx + 0x2u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.cf)
        goto L_47a7ee;
L_47aaae:
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    edx = lift_load(&env, ebp, 0xffffffa8u, 4);
    ecx = lift_load(&env, ebp, 0xffffff54u, 4);
    ebx = lift_load(&env, ebp, 0xffffffc4u, 4);
    esi = lift_load(&env, ebp, 0x8u, 4);
    ebx = ebx + 1u;
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffff78u, 4);
    lift_store(&env, ebp, 0xffffffa8u, 4, edx);
    ecx = ecx + eax;
    lift_store(&env, ebp, 0xffffffc4u, 4, ebx);
    lift_store(&env, ebp, 0xffffff54u, 4, ecx);
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (!fl.cf)
        goto L_47a366;
    goto L_47a7cf;
L_47aae4:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = eax + lift_load(&env, ebp, 0xffffff5cu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) & 0x7cu) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    edx = edx & 0x3e0u;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffecu, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffff80u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff7cu, 4);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edx = edx | lift_load(&env, ebp, 0xffffff80u, 4);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1fu) & 0xffu);
    eax = eax & 0xffffu;
    eax = eax | edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffff7cu, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff4u, 1)) & 0xffu);
    ecx = ecx + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    ebx = ebx + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    esi = esi + eax;
    goto L_47a855;
}

uint32_t lifted_f483400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F483400_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F483400_STACK, 0, entry);
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
    esp = esp - 0x38u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffc8u, 4, ecx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_483541;
L_48341c:
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x483110u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_483464;
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    edi = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
L_48344d:
    edx = edx ^ edx;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_48345f;
L_483453:
    eax = eax + 0x4u;
    edx = edx + 1u;
    lift_store(&env, eax, 0xffffffffu, 1, 0x0u);
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (fl.cf)
        goto L_483453;
L_48345f:
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, ecx, esi, &fl);
    }
    if (fl.cf)
        goto L_48344d;
L_483464:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    eax = eax - 1u;
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = eax - 1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
L_48347e:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48361e;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edi = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = edx ^ edx;
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    eax = lift_load(&env, eax, 0x0u, 4);
    edi = lift_load(&env, edi, 0x0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4834fa;
L_48349e:
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    edx = edx ^ edx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4834ec;
    ecx = lift_load(&env, ebp, 0xffffffc0u, 4);
    ecx = 0u - ecx;
    esi = (eax + ecx);
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = ecx + eax;
L_4834b4:
    ebx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu);
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4834d8;
    lift_store(&env, ebp, 0xffffffecu, 4, 0x1u);
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xfffffff0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_48354e;
L_4834d4:
    lift_store(&env, edi, 0x3u, 1, lift_load(&env, edi, 0x3u, 1) | 0xffu);
L_4834d8:
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = esi + 0x4u;
    ecx = ecx + 0x4u;
    eax = eax + 0x4u;
    edx = edx + 1u;
    edi = edi + 0x4u;
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (fl.cf)
        goto L_4834b4;
L_4834ec:
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    ebx = ebx + 1u;
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.cf)
        goto L_48349e;
L_4834fa:
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    edi = lift_load(&env, ebp, 0xffffffe4u, 4);
    esi = esi ^ esi;
    edx = lift_load(&env, edx, 0x0u, 4);
    ecx = lift_load(&env, ecx, 0x0u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_483539;
L_48350d:
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    eax = eax ^ eax;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_483531;
    edi = lift_load(&env, ebp, 0xfffffff4u, 4);
L_483519:
    ebx = lift_load(&env, ecx, 0x0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        ebx = r;
    }
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_483526;
    lift_store(&env, edx, 0x3u, 1, 0x0u);
L_483526:
    edx = edx + 0x4u;
    eax = eax + 1u;
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.cf)
        goto L_483519;
L_483531:
    edi = lift_load(&env, ebp, 0xffffffe4u, 4);
    esi = esi + 1u;
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.cf)
        goto L_48350d;
L_483539:
    lift_store(&env, ebp, 0xffffffdcu, 4, lift_load(&env, ebp, 0xffffffdcu, 4) - 1u);
    goto L_48347e;
L_483541:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x483110u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    goto L_48341c;
L_48354e:
    ebx = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu);
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4834d4;
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0xffffffe8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4834d4;
    ebx = lift_load(&env, ecx, 0x0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu);
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4834d4;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4834d4;
    ebx = lift_load(&env, eax, 0xfffffffcu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu);
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4834d4;
    {
        (void)lift_sub(32, edx, lift_load(&env, ebp, 0xffffffc4u, 4), &fl);
    }
    if (fl.zf)
        goto L_4834d4;
    ebx = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu);
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4834d4;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffc8u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_48360f;
    ebx = lift_load(&env, esi, 0xfffffffcu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu);
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4834d4;
    ebx = lift_load(&env, esi, 0x4u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu);
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4834d4;
    ebx = lift_load(&env, ecx, 0xfffffffcu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu);
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4834d4;
    ebx = lift_load(&env, ecx, 0x4u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu);
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4834d4;
L_48360f:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4834d4;
    goto L_4834d8;
L_48361e:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_48362e;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
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
L_48362e:
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4830f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
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

uint32_t lifted_f483790(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F483790_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F483790_STACK, 0, entry);
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
    esp = esp - 0x60u;
    ebx = eax;
    eax = lift_load(&env, eax, 0x4u, 4);
    ecx = 0x64u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = lift_load(&env, ebx, 0x8u, 4);
    ecx = ecx - edx;
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x27u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4837c2;
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
L_4837c2:
    ecx = 0x558cf0u;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    ecx = ecx + edx;
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, 0u, 0x55f1f0u, 4, ecx);
    ecx = 0x558cf0u;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    ecx = ecx + edx;
    lift_store(&env, 0u, 0x55f1f4u, 4, ecx);
    edx = lift_load(&env, ebx, 0x0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, ebp, 0xffffffb0u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        uint32_t r = lift_imul(32, edx, ecx, &fl);
        edx = r;
    }
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_imul(32, ecx, edx, &fl);
        ecx = r;
    }
    edx = 0x1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    edi = eax;
    esi = lift_load(&env, ebx, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
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
    ecx = lift_load(&env, ebp, 0xffffffacu, 4);
    esi = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, edx);
    ecx = ecx - 1u;
    esi = esi - 1u;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0x26u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_483ae3;
    edx = edx ^ edx;
    ebx = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, ebp, 0xffffff98u, 4, edx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_483a81;
    lift_store(&env, ebp, 0xffffffbcu, 4, esi);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    lift_store(&env, ebp, 0xffffffc4u, 4, ecx);
    lift_store(&env, ebp, 0xffffff94u, 4, eax);
L_483858:
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_483a5c;
L_483874:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ebp, 0xffffff94u, 4);
    ebx = ebx ^ ebx;
    ecx = ecx ^ ecx;
    esi = esi ^ esi;
    eax = eax - edx;
    edx = lift_load(&env, ebp, 0xffffff98u, 4);
    edi = edi ^ edi;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4838b1;
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4838b1;
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ecx = r;
    }
    esi = (ecx & 0xffu);
    ecx = ecx ^ ecx;
    edi = 0x1u;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ecx = r;
    }
L_4838b1:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, ebp, 0xffffff98u, 4);
    {
        (void)lift_sub(32, edx, lift_load(&env, ebp, 0xffffffc4u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4838f7;
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4838f7;
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffecu, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    esi = esi + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ecx = ecx + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    ebx = ebx + eax;
L_4838f7:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax - 0x4u;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_48393c;
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_48393c;
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffecu, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    esi = esi + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ecx = ecx + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    ebx = ebx + eax;
L_48393c:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax + 0x4u;
    {
        (void)lift_sub(32, edx, lift_load(&env, ebp, 0xffffffbcu, 4), &fl);
    }
    if (!fl.cf)
        goto L_483982;
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_483982;
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffecu, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    esi = esi + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ecx = ecx + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    ebx = ebx + eax;
L_483982:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_483a38;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_483a92;
    eax = esi;
    edx = edx ^ edx;
    lift_div1(32, edi, &eax, &edx, &fl);
    esi = eax;
    edx = edx ^ edx;
    eax = ecx;
    lift_div1(32, edi, &eax, &edx, &fl);
    ecx = eax;
    edx = edx ^ edx;
    eax = ebx;
    lift_div1(32, edi, &eax, &edx, &fl);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        esi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ecx = r;
    }
    ecx = ecx | esi;
    ebx = eax;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx | ecx;
    eax = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx ^ ecx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = lift_load(&env, 0u, 0x55f1f0u, 4);
    edi = lift_load(&env, ecx, eax + 0x0u, 1);
    ecx = ebx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ecx = r;
    }
    esi = (ecx & 0xffu);
    ecx = lift_load(&env, 0u, 0x55f1f4u, 4);
    esi = lift_load(&env, ecx, esi + 0x0u, 1);
    esi = esi + edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        esi = r;
    }
    esi = esi | 0xff000000u;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, ebp, 0xffffffa4u, 4, esi);
    esi = esi ^ esi;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        esi = r;
    }
    edi = lift_load(&env, esi, eax + 0x0u, 1);
    esi = esi ^ esi;
    esi = (esi & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        esi = r;
    }
    esi = lift_load(&env, ecx, esi + 0x0u, 1);
    esi = esi + edi;
    edi = lift_load(&env, ebp, 0xffffffa4u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        esi = r;
    }
    edi = edi | esi;
    esi = lift_load(&env, edx, 0x0u, 1);
    esi = lift_load(&env, esi, eax + 0x0u, 1);
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    eax = eax & 0xffu;
    eax = eax + esi;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax | edi;
    lift_store(&env, edx, 0x0u, 4, eax);
L_483a38:
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    edi = lift_load(&env, ebp, 0xffffffccu, 4);
    ecx = ecx + 0x4u;
    ebx = ebx + 0x4u;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.cf)
        goto L_483874;
L_483a5c:
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    ecx = lift_load(&env, ebp, 0xffffffb4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffb0u, 4);
    esi = lift_load(&env, ebp, 0xffffff98u, 4);
    edi = lift_load(&env, ebp, 0xffffffacu, 4);
    esi = esi + 1u;
    ecx = ecx + eax;
    ebx = ebx + eax;
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffb0u, 4, ebx);
    lift_store(&env, ebp, 0xffffff98u, 4, esi);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.cf)
        goto L_483858;
L_483a81:
    eax = lift_load(&env, ebp, 0xffffffa8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
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
L_483a92:
    eax = esi;
    edx = edx ^ edx;
    lift_div1(32, edi, &eax, &edx, &fl);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, ebp, 0xffffffd4u, 4), &fl);
        eax = r;
    }
    edx = edx ^ edx;
    esi = 0x64u;
    lift_div1(32, esi, &eax, &edx, &fl);
    esi = eax;
    edx = edx ^ edx;
    eax = ecx;
    lift_div1(32, edi, &eax, &edx, &fl);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, ebp, 0xffffffd4u, 4), &fl);
        eax = r;
    }
    ecx = 0x64u;
    edx = edx ^ edx;
    lift_div1(32, ecx, &eax, &edx, &fl);
    ecx = eax;
    edx = edx ^ edx;
    eax = ebx;
    lift_div1(32, edi, &eax, &edx, &fl);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, ebp, 0xffffffd4u, 4), &fl);
        eax = r;
    }
    edx = edx ^ edx;
    ebx = 0x64u;
    lift_div1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        esi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ecx = r;
    }
    ecx = ecx | esi;
    ecx = ecx | eax;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0x0u, 4, ecx);
    goto L_483a38;
L_483ae3:
    ebx = ebx ^ ebx;
    edi = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_483a81;
    lift_store(&env, ebp, 0xffffffb8u, 4, esi);
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
    lift_store(&env, ebp, 0xffffffc8u, 4, ecx);
    lift_store(&env, ebp, 0xffffff90u, 4, eax);
L_483afb:
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffccu, 4);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    lift_store(&env, ebp, 0xffffff9cu, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_483c7b;
L_483b17:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    esi = esi ^ esi;
    ebx = ebx ^ ebx;
    ecx = ecx ^ ecx;
    edi = edi ^ edi;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_483b45;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = eax - lift_load(&env, ebp, 0xffffff90u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ecx = r;
    }
    edi = 0x1u;
    ecx = ecx & 0xffu;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    esi = lift_load(&env, eax, 0x0u, 1);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ebx = r;
    }
L_483b45:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffc8u, 4), &fl);
    }
    if (fl.cf)
        goto L_483ca5;
L_483b51:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffff9cu, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_483b88;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, eax, 0xfffffffcu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffecu, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    ecx = ecx + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0xfffffffcu, 2)) & 0xffffu);
    eax = eax - 0x4u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ebx = ebx + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    esi = esi + eax;
L_483b88:
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffb8u, 4), &fl);
    }
    if (!fl.cf)
        goto L_483bbf;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffecu, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    ecx = ecx + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x4u, 1)) & 0xffu);
    ebx = ebx + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    esi = esi + eax;
L_483bbf:
    eax = ecx;
    edx = edx ^ edx;
    lift_div1(32, edi, &eax, &edx, &fl);
    ecx = eax;
    edx = edx ^ edx;
    eax = ebx;
    lift_div1(32, edi, &eax, &edx, &fl);
    ebx = eax;
    edx = edx ^ edx;
    eax = esi;
    lift_div1(32, edi, &eax, &edx, &fl);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ebx = r;
    }
    ecx = ecx | ebx;
    ecx = ecx | eax;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x55f1f0u, 4);
    eax = eax & 0xffu;
    edi = lift_load(&env, ebx, eax + 0x0u, 1);
    eax = ecx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    esi = (eax & 0xffu);
    eax = lift_load(&env, 0u, 0x55f1f4u, 4);
    esi = lift_load(&env, esi, eax + 0x0u, 1);
    esi = esi + edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        esi = r;
    }
    esi = esi | 0xff000000u;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffffa4u, 4, esi);
    esi = esi ^ esi;
    esi = (esi & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        esi = r;
    }
    edi = lift_load(&env, esi, ebx + 0x0u, 1);
    esi = esi ^ esi;
    esi = (esi & 0xffff0000u) | (((ecx & 0xffffu)) & 0xffffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        esi = r;
    }
    esi = lift_load(&env, esi, eax + 0x0u, 1);
    esi = esi + edi;
    edi = lift_load(&env, ebp, 0xffffffa4u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        esi = r;
    }
    edi = edi | esi;
    esi = lift_load(&env, edx, 0x0u, 1);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, ebx + 0x0u, 1)) & 0xffu);
    ebx = ebx & 0xffu;
    ecx = ecx & 0xffu;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    eax = eax & 0xffu;
    eax = eax + ebx;
    edi = edi | eax;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    esi = (eax + 0x4u);
    lift_store(&env, eax, 0x0u, 4, edi);
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    edi = (edx + 0x4u);
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf)
        goto L_483b17;
L_483c7b:
    eax = lift_load(&env, ebp, 0xffffff90u, 4);
    esi = lift_load(&env, ebp, 0xffffffb4u, 4);
    edi = lift_load(&env, ebp, 0xffffffb0u, 4);
    edx = lift_load(&env, ebp, 0xffffffacu, 4);
    esi = esi + eax;
    edi = edi + eax;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, esi);
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffb0u, 4, edi);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.cf)
        goto L_483a81;
    goto L_483afb;
L_483ca5:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffa0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffecu, 1, (edx & 0xffu));
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    ecx = ecx + edx;
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ebx = ebx + edx;
    eax = eax & 0xffu;
    edi = edi + 1u;
    esi = esi + eax;
    goto L_483b51;
}

uint32_t lifted_f4d06d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D06D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D06D0_STACK, 0, entry);
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
    esi = eax;
    edi = edx;
    {
        uint32_t v = lift_load(&env, eax, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19a4u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = ebx ^ ebx;
    ebp = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4d06f2;
    goto L_4d072d;
L_4d06ed:
    ebx = ebx + 1u;
    {
        (void)lift_sub(32, ebx, ebp, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4d072d;
L_4d06f2:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19dcu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1210u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d0714;
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d06d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d06ed;
    goto L_4d072f;
L_4d0714:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19a8u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (!fl.zf)
        goto L_4d06ed;
    {
        uint32_t v = lift_load(&env, esi, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e1230u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    goto L_4d072f;
L_4d072d:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4d072f:
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
}

uint32_t lifted_f4d1ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D1AE0_STACK + 4 + 4 * 6 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D1AE0_STACK, 6, entry);
    {
        uint32_t v = ebx;
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
    edi = lift_load(&env, esp, 0x18u, 4);
    esi = lift_load(&env, esp, 0x1cu, 4);
    ebp = lift_load(&env, esp, 0x20u, 4);
    {
        uint32_t v = lift_load(&env, esp, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19e8u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d1b13;
    goto L_4d1b63;
L_4d1b03:
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
    if (fl.zf)
        goto L_4d1b63;
L_4d1b13:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x28u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d1b32;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf910u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d1b3d;
    {
        uint32_t v = ebp;
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
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf650u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    goto L_4d1b3d;
L_4d1b32:
    {
        uint32_t v = ebp;
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
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
L_4d1b3d:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x24u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d1b03;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19e8u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d1b03;
    {
        uint32_t v = lift_load(&env, esp, 0x28u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x28u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
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
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d1ae0u, eax, edx, ebx, ecx, 6, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 24u;
    goto L_4d1b03;
L_4d1b63:
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
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e0c56(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0C56_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0C56_STACK, 0, entry);
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
    esp = esp - 0x3cu;
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
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x34u);
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
    lift_store(&env, esp, 0x38u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x3cu, 4, 0x51bb90u);
    eax = 0x509828u;
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e14b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x509824u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e0cbf;
    eax = lift_load(&env, 0u, 0x509820u, 4);
    lift_store(&env, 0u, 0x509838u, 4, 0x0u);
    eax = eax - 0x18u;
    lift_store(&env, 0u, 0x509824u, 4, 0x509838u);
    lift_store(&env, 0u, 0x50983cu, 4, eax);
L_4e0cbf:
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e37feu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6c98u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = (eax + 0x2bu);
    {
        (void)lift_sub(32, esi, 0x18u, &fl);
    }
    if (fl.cf)
        goto L_4e0d06;
L_4e0cda:
    esi = esi + 0x3u;
    esi = (esi & 0xffff0000u) | (((esi & 0xffffu) & 0xfffcu) & 0xffffu);
    ebx = 0x509824u;
    ebp = (esi + 0x18u);
L_4e0ce9:
    ecx = lift_load(&env, ebx, 0x0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4e0d11;
L_4e0cef:
    edx = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_load(&env, ecx, 0x0u, 4);
    edx = edx + ecx;
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e0d22;
    edx = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ecx, 0x4u, 4, lift_load(&env, ecx, 0x4u, 4) + edx);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    goto L_4e0cef;
L_4e0d06:
    esi = 0x18u;
    goto L_4e0cda;
L_4e0d0d:
    ebx = ecx;
    goto L_4e0ce9;
L_4e0d11:
    edx = 0x1u;
    eax = 0x51281du;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dee73u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e0cef;
L_4e0d22:
    {
        (void)lift_sub(32, esi, lift_load(&env, ecx, 0x4u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4e0dda;
    ebp = ecx;
    lift_store(&env, ebx, 0x0u, 4, eax);
L_4e0d2f:
    eax = 0x509828u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e14b7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0x0u, 4, esi);
    eax = lift_load(&env, esp, 0x0u, 4);
    lift_store(&env, ebp, 0x18u, 4, 0x509820u);
    eax = lift_load(&env, eax, 0x0u, 4);
    ebp = ebp + 0x4u;
    edx = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ebp, 0x0u, 4, edx);
    lift_store(&env, eax, 0x8u, 4, ebp);
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ebp, 0xcu, 1, 0x5u);
    lift_store(&env, ebp, 0x1cu, 4, 0x0u);
    lift_store(&env, ebp, 0x20u, 4, 0x0u);
    lift_store(&env, ebp, 0x8u, 4, eax);
    lift_store(&env, ebp, 0xeu, 1, lift_load(&env, ebp, 0xeu, 1) & 0xfeu);
    eax = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, ebp, 0x4u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x8u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e0e62;
    eax = (eax & 0xffu);
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4e0d8f;
            case 1:
                goto L_4e0e57;
            case 2:
                goto L_4e0e62;
            case 3:
                goto L_4e0df0;
            case 4:
                goto L_4e0e1e;
            case 5:
                goto L_4e0e62;
            case 6:
                goto L_4e0e57;
            case 7:
                goto L_4e0e57;
            case 8:
                goto L_4e0df0;
            default:
                return 0u;
        }
    }
L_4e0d8f:
    ecx = 0x5u;
    edx = lift_load(&env, esp, 0x0u, 4);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x10u);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e36d2u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esp, 0x40u, 4, 0x1u);
    edx = lift_load(&env, esp, 0x8u, 4);
    eax = (ebp + 0x24u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x1cu, 4, 0x0u);
    eax = (esp + 0xcu);
L_4e0dc1:
    edx = edx ^ edx;
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e36e4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    goto L_4e0e0a;
L_4e0dda:
    {
        (void)lift_sub(32, ebp, lift_load(&env, ecx, 0x4u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4e0d0d;
    lift_store(&env, ecx, 0x4u, 4, lift_load(&env, ecx, 0x4u, 4) - esi);
    ebp = lift_load(&env, ecx, 0x4u, 4);
    ebp = ebp + ecx;
    goto L_4e0d2f;
L_4e0df0:
    esi = lift_load(&env, esp, 0x8u, 4);
    ecx = lift_load(&env, edi, 0x4u, 4);
L_4e0df7:
    edi = (ebp + 0x24u);
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
L_4e0e0a:
    eax = lift_load(&env, esp, 0x34u, 4);
    env.chain = eax;
    eax = ebp;
    {
        uint32_t r = lift_add(32, esp, 0x48u, &fl);
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
L_4e0e1e:
    ecx = 0x5u;
    edx = lift_load(&env, esp, 0x0u, 4);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x24u);
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e36d2u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esp, 0x40u, 4, 0x3u);
    ebx = lift_load(&env, esp, 0x8u, 4);
    eax = (ebp + 0x24u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x30u, 4, 0x0u);
    eax = (esp + 0x20u);
    goto L_4e0dc1;
L_4e0e57:
    ecx = 0x4u;
    esi = lift_load(&env, esp, 0x8u, 4);
    goto L_4e0df7;
L_4e0e62:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e0e0a;
}
