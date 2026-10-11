/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_27.h"

uint32_t lifted_f47e890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F47E890_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F47E890_STACK, 0, entry);
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
    ebx = eax;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x51693cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x1bcu, 4, 0x0u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x1c0u, 4, 0x0u);
    {
        uint32_t v = 0x51690cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x1c4u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f175cu, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_47e8ff;
L_47e8d4:
    ecx = lift_load(&env, ebx, 0x0u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_47e973;
L_47e8de:
    esi = lift_load(&env, ebx, 0x1bcu, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_47e8f8;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, esi, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, ebx, 0x1bcu, 4, 0x0u);
L_47e8f8:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
L_47e8ff:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x47eab0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x0u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_47e8d4;
    eax = (ebx + 0x1bcu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5169bcu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x51699cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f175cu, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_47e8d4;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (ebx + 0x1c0u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x47eb60u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x1bcu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0xcu, 4), eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_47e8d4;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x1c0u, 4), 0x0u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    lift_store(&env, ebx, 0x1c4u, 4, eax);
    eax = 0x1u;
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
L_47e973:
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ecx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, ebx, 0x0u, 4, 0x0u);
    goto L_47e8de;
}

uint32_t lifted_f488c50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F488C50_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F488C50_STACK, 0, entry);
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
    esp = esp - 0x4cu;
    esi = eax;
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    eax = (ebp + 0xffffffb8u);
    edx = 0x4ec1ecu;
    ecx = 0x517038u;
    edi = 0x3u;
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
    ebx = ebx ^ ebx;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ebp, 0xffffffc8u, 1)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffbcu, 4, edx);
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffc4u, 4, ebx);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) & 0xfeu) & 0xffu) << 8);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    lift_store(&env, ebp, 0xffffffc8u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, ebp, 0xffffffdcu, 1, (edx & 0xffu));
    eax = (ebp + 0xffffffa4u);
    edx = 0x517494u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffb4u);
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x4u;
    edi = 0x1u;
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    lift_store(&env, ebp, 0xffffffacu, 4, ebx);
    ebx = 0xffffffffu;
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    edx = edx ^ edx;
    eax = (ebp + 0xffffffb4u);
    lift_store(&env, ebp, 0xffffffb0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    ecx = (ebp + 0xffffffa4u);
    eax = lift_load(&env, esi, 0x0u, 4);
    ebx = 0x8000u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = esi;
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x28u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_488d51;
    edi = 0x1u;
L_488cff:
    ecx = 0x517494u;
    eax = (ebp + 0xffffffa4u);
    ebx = 0x8u;
    esi = 0x517454u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffa4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    lift_store(&env, ebp, 0xffffffdcu, 1, (edx & 0xffu));
    eax = (ebp + 0xffffffb4u);
    lift_store(&env, ebp, 0xffffffc4u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edx = (ebp + 0xffffffa4u);
    lift_store(&env, ebp, 0xffffffd0u, 1, (eax & 0xffu));
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffa4u, 4, esi);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
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
L_488d51:
    edx = (ebp + 0xffffffa4u);
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x488d80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc4u, 4, 0x1u);
    goto L_488cff;
}
