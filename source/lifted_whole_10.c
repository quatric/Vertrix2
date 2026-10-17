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
