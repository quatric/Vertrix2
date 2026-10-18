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
