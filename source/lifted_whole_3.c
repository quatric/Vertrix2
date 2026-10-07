/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_3.h"

uint32_t lifted_f4b54d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B54D0_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B54D0_STACK, 1, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = eax;
    lift_store(&env, eax, 0xeu, 2, (edx & 0xffffu));
    lift_store(&env, eax, 0x16u, 2, (ebx & 0xffffu));
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | (((ecx & 0xffffu)) & 0xffffu);
    lift_store(&env, esi, 0xf4u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esp, 0x8u, 2)) & 0xffffu);
    lift_store(&env, esi, 0xf8u, 4, eax);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b5500(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B5500_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B5500_STACK, 0, entry);
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
    ecx = eax;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x15cu, 2)) & 0xffffu);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4b5519;
L_4b5513:
    eax = ebx;
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
    return env.failed ? 0u : eax;
L_4b5519:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x15cu, 2)) & 0xffffu);
    eax = 0x54d640u;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b5513;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x15cu, 2)) & 0xffffu);
    ebx = 0x1u;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b5550(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B5550_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B5550_STACK, 0, entry);
    eax = lift_call(&env, 0x4b17b0u, eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b5580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B5580_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B5580_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    edx = eax;
    eax = (ebp + 0xffffffccu);
    ecx = 0x4ec1ecu;
    ebx = 0x5181b0u;
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
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    {
        uint32_t r = lift_xor(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    lift_store(&env, ebp, 0xffffffe4u, 1, ((eax >> 8) & 0xffu));
    eax = edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    edx = eax;
    lift_store(&env, eax, 0x158u, 4, 0x518244u);
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b5628;
L_4b55e5:
    lift_store(&env, edx, 0x184u, 4, 0x0u);
    lift_store(&env, edx, 0x188u, 4, 0x0u);
    lift_store(&env, edx, 0x180u, 4, 0x0u);
    lift_store(&env, edx, 0x190u, 4, 0x1u);
    lift_store(&env, edx, 0x18cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    env.chain = eax;
    eax = edx;
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
    return env.failed ? 0u : eax;
L_4b5628:
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0, esp);
    goto L_4b55e5;
}

uint32_t lifted_f4b5c60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B5C60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B5C60_STACK, 0, entry);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, eax, 0x158u, 4, 0x5182c4u);
    lift_store(&env, eax, 0x15cu, 2, 0x0u);
    lift_store(&env, eax, 0x160u, 4, 0x0u);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b5d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B5D40_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B5D40_STACK, 0, entry);
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
    ecx = eax;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x15cu, 2)) & 0xffffu);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4b5d59;
L_4b5d53:
    eax = ebx;
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
    return env.failed ? 0u : eax;
L_4b5d59:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x15cu, 2)) & 0xffffu);
    eax = 0x54d640u;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b5d53;
    edx = lift_load(&env, ecx, 0x160u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4b5d86;
    ebx = 0x1u;
    eax = ebx;
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
    return env.failed ? 0u : eax;
L_4b5d86:
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x15cu, 2)) & 0xffffu);
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    ebx = 0x1u;
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b5db0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B5DB0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B5DB0_STACK, 0, entry);
    eax = lift_call(&env, 0x4d8650u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, eax, 0x0u, 4, 0x518344u);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b5dc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B5DC0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B5DC0_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x40u, &fl);
        esp = r;
    }
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4b5e3d;
    edx = 0x4ec1ecu;
    esi = 0x518300u;
    lift_store(&env, eax, 0x0u, 4, 0x518344u);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = (eax & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffdcu, 1, ((eax >> 8) & 0xffu));
    eax = (ebp + 0xffffffc4u);
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
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, esi);
    eax = ecx;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    eax = lift_call(&env, 0x4d86d0u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b5e29;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
L_4b5e29:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
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
    return env.failed ? 0u : eax;
L_4b5e3d:
    ebx = 0x1u;
    edx = 0x516390u;
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebp, 0xffffffd0u, 4, esi);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b5e70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B5E70_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B5E70_STACK, 0, entry);
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
    ecx = 0x1u;
    esi = lift_load(&env, eax, 0x8u, 4);
    ebx = edx;
    edx = esi;
    eax = lift_call(&env, 0x4d88a0u, eax, edx, ebx, ecx, 0, esp);
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
        ecx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b6460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B6460_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B6460_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x34u, &fl);
        esp = r;
    }
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4b64fa;
    edx = 0x4ec1ecu;
    esi = 0x518374u;
    lift_store(&env, eax, 0x158u, 4, 0x518404u);
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
    eax = (ecx + 0x15cu);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    ecx = (eax + 0xfffffea4u);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = ecx;
    eax = lift_call(&env, 0x4ac130u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    ecx = eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b64e6;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
L_4b64e6:
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
    return env.failed ? 0u : eax;
L_4b64fa:
    ebx = 0x1u;
    edx = 0x518420u;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b6560(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B6560_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B6560_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x174u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b657a;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x17au, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, eax, 0x17cu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b6581;
L_4b657a:
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4b6581:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b6690(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B6690_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B6690_STACK, 1, entry);
    lift_store(&env, eax, 0x16au, 2, (edx & 0xffffu));
    lift_store(&env, eax, 0x16cu, 2, (ebx & 0xffffu));
    lift_store(&env, eax, 0x16eu, 2, (ecx & 0xffffu));
    edx = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x170u, 2, (edx & 0xffffu));
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b66c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B66C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B66C0_STACK, 0, entry);
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
    esi = (esi & 0xffff0000u) | ((lift_load(&env, eax, 0x16au, 2)) & 0xffffu);
    ecx = 0x1u;
    {
        (void)lift_sub(16, (edx & 0xffffu), (esi & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b66ee;
    {
        (void)lift_sub(16, (ebx & 0xffffu), lift_load(&env, eax, 0x16eu, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b66ee;
    {
        (void)lift_sub(16, (edx & 0xffffu), lift_load(&env, eax, 0x16cu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b66ee;
    {
        (void)lift_sub(16, (ebx & 0xffffu), lift_load(&env, eax, 0x170u, 2), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b66f0;
L_4b66ee:
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
L_4b66f0:
    eax = ecx;
    lift_store(&env, 0u, 0x5bd828u, 4, ecx);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b6700(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B6700_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B6700_STACK, 0, entry);
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
    ecx = eax;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x172u, 2)) & 0xffffu);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4b6719;
L_4b6713:
    eax = ebx;
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
    return env.failed ? 0u : eax;
L_4b6719:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x172u, 2)) & 0xffffu);
    eax = 0x54d640u;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b6713;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x172u, 2)) & 0xffffu);
    ebx = 0x1u;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b6800(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B6800_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B6800_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    esi = eax;
    edi = edx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, esi, 0x14u, 4);
    ebx = lift_load(&env, esi, 0xcu, 4);
    {
        uint32_t r = lift_add(32, eax, 0x15cu, &fl);
        eax = r;
    }
    edx = lift_load(&env, esi, 0x15du, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = edi;
    ecx = ebx;
    eax = lift_call(&env, 0x440ca0u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    eax = esi;
    eax = lift_call(&env, 0x4b6560u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4b684e;
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
    return env.failed ? 0u : eax;
L_4b684e:
    eax = lift_load(&env, esi, 0x178u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, eax, 0x0u, 4);
    ecx = lift_load(&env, esi, 0x14u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, esi, 0x175u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, esi, 0xcu, 4);
    edx = lift_load(&env, esi, 0x15du, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    eax = edi;
    eax = lift_call(&env, 0x440fc0u, eax, edx, ebx, ecx, 6, esp);
    esp += 24u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b6890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B6890_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B6890_STACK, 0, entry);
    eax = lift_call(&env, 0x4ae010u, eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b69f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B69F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B69F0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    ecx = edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x44u, 1)) & 0xffu);
    eax = lift_load(&env, eax, 0x15du, 4);
    edx = 0x5110b8u;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x440610u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b6a10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B6A10_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B6A10_STACK, 0, entry);
    eax = lift_load(&env, eax, 0x15du, 4);
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x43f460u, eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b6ea0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B6EA0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B6EA0_STACK, 0, entry);
    eax = lift_call(&env, 0x4d8650u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, eax, 0x0u, 4, 0x518574u);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b6f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B6F70_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B6F70_STACK, 0, entry);
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
    ecx = 0x1u;
    esi = lift_load(&env, eax, 0x8u, 4);
    ebx = edx;
    edx = esi;
    eax = lift_call(&env, 0x4d88a0u, eax, edx, ebx, ecx, 0, esp);
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
        ecx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b7600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B7600_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B7600_STACK, 0, entry);
    eax = lift_call(&env, 0x4d8650u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, eax, 0x0u, 4, 0x518694u);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b76d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B76D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B76D0_STACK, 0, entry);
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
    esi = eax;
    edi = lift_load(&env, eax, 0x8u, 4);
    eax = 0x4u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b76fe;
L_4b76e7:
    ecx = 0x1u;
    ebx = eax;
    edx = edi;
    eax = esi;
    eax = lift_call(&env, 0x4d88a0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4b76fe:
    eax = lift_call(&env, 0x4ca090u, eax, edx, ebx, ecx, 0, esp);
    goto L_4b76e7;
}

uint32_t lifted_f4b78d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B78D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B78D0_STACK, 0, entry);
    eax = lift_call(&env, 0x4d8650u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, eax, 0x0u, 4, 0x518704u);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b78e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B78E0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B78E0_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x40u, &fl);
        esp = r;
    }
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4b7972;
    edx = 0x4ec1ecu;
    esi = 0x5186b0u;
    edi = 0x3u;
    lift_store(&env, eax, 0x0u, 4, 0x518704u);
    eax = (eax & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffdcu, 1, ((eax >> 8) & 0xffu));
    eax = (ebp + 0xffffffc4u);
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
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, esi);
    eax = ecx;
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    eax = lift_call(&env, 0x4b7b00u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = ecx;
    eax = lift_call(&env, 0x4d86d0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    ecx = eax;
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b795e;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
L_4b795e:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
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
    return env.failed ? 0u : eax;
L_4b7972:
    ebx = 0x1u;
    edx = 0x518720u;
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebp, 0xffffffd0u, 4, esi);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b79a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B79A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B79A0_STACK, 0, entry);
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
    ecx = 0x1u;
    esi = lift_load(&env, eax, 0x8u, 4);
    ebx = edx;
    edx = esi;
    eax = lift_call(&env, 0x4d88a0u, eax, edx, ebx, ecx, 0, esp);
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
        ecx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b7a80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B7A80_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B7A80_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4b79c0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4b7a8f;
    ecx = lift_load(&env, eax, 0x8u, 4);
L_4b7a8f:
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b7b80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B7B80_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B7B80_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, 0u, 0x5328bcu, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4b7b8e;
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
    return env.failed ? 0u : eax;
L_4b7b8e:
    {
        uint32_t v = 0x5328c0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x55608cu, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b7bad;
    eax = 0x55608cu;
    eax = lift_call(&env, 0x4774e0u, eax, edx, ebx, ecx, 0, esp);
L_4b7bad:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5588f8u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b7bc0;
    eax = 0x5588f8u;
    eax = lift_call(&env, 0x477f10u, eax, edx, ebx, ecx, 0, esp);
L_4b7bc0:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5536c8u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b7bd3;
    eax = 0x5536c8u;
    eax = lift_call(&env, 0x476d70u, eax, edx, ebx, ecx, 0, esp);
L_4b7bd3:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x553798u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b7be6;
    eax = 0x553798u;
    eax = lift_call(&env, 0x476d70u, eax, edx, ebx, ecx, 0, esp);
L_4b7be6:
    {
        uint32_t v = 0x5328c0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b7c90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B7C90_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B7C90_STACK, 0, entry);
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
    eax = 0x5bd82cu;
    eax = lift_call(&env, 0x484500u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, 0u, 0x5bd848u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1724u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ebx = lift_load(&env, 0u, 0x5bd840u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5bd83cu, 4, ecx);
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b8170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B8170_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B8170_STACK, 0, entry);
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
    eax = lift_call(&env, 0x40aca0u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    eax = edx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b9050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B9050_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B9050_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x1cu, &fl);
        esp = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    ecx = 0x5bdb00u;
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
L_4b9065:
    esi = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    esi = lift_load(&env, esi, 0x4ff8acu, 4);
L_4b9070:
    edx = 0x8000u;
    eax = 0x10u;
L_4b907a:
    {
        uint32_t a = ecx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ecx = r;
    }
    {
        (void)lift_and(32, esi, edx, &fl);
    }
    ebx = (ebx & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    lift_store(&env, ecx, 0xffffffffu, 1, (ebx & 0xffu));
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    if (!fl.zf)
        goto L_4b907a;
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    {
        (void)lift_sub(32, edi, 0x40u, &fl);
    }
    if (fl.cf)
        goto L_4b9070;
    ebx = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        uint32_t r = lift_add(32, ebx, 0x4u, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_4b9065;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
L_4b90a2:
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
L_4b90b0:
    {
        uint32_t r = lift_xor(8, (edx & 0xffu), (edx & 0xffu), &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b90cd;
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = edi;
    {
        uint32_t r = lift_add(32, ecx, esi, &fl);
        ecx = r;
    }
L_4b90bd:
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x5bdb00u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b90c8;
    {
        uint32_t a = (edx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
L_4b90c8:
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.cf)
        goto L_4b90bd;
L_4b90cd:
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    lift_store(&env, ebx, 0x5c1affu, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, esi, 0x10u, &fl);
    }
    if (fl.cf)
        goto L_4b90b0;
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t r = lift_add(32, edx, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0x10u, &fl);
    }
    if (fl.cf)
        goto L_4b90a2;
    eax = 0x5bdb00u;
    esi = 0x1u;
    {
        uint32_t r = lift_add(32, eax, 0x400u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    ecx = (ecx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
L_4b9106:
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = 0x3ffu;
    ebx = 0x400u;
    ecx = (ecx & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, esi, 0x5c1c00u, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = esi;
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4b9130:
    {
        (void)lift_sub(8, (eax & 0xffu), lift_load(&env, edi, 0x0u, 1), &fl);
    }
    if (fl.zf)
        goto L_4b9167;
    lift_store(&env, esi, 0x0u, 1, (ecx & 0xffu));
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    ecx = (ecx & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
L_4b9139:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_4b9130;
    esi = lift_load(&env, ebp, 0xffffffd4u, 4);
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t r = lift_add(32, esi, 0x400u, &fl);
        esi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    {
        (void)lift_sub(32, edi, 0x10u, &fl);
    }
    if (fl.cf)
        goto L_4b9106;
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
    return env.failed ? 0u : eax;
L_4b9167:
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    goto L_4b9139;
}

uint32_t lifted_f4b9310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B9310_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B9310_STACK, 0, entry);
    eax = lift_call(&env, 0x4b91b0u, eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b9330(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B9330_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B9330_STACK, 0, entry);
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
    ecx = eax;
    eax = lift_load(&env, eax, 0x24u, 4);
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (!fl.cf)
        goto L_4b951a;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b9525;
    lift_store(&env, ecx, 0x28u, 4, eax);
    lift_store(&env, ecx, 0x2cu, 4, eax);
L_4b9351:
    lift_store(&env, ecx, 0x30u, 4, 0x1u);
    lift_store(&env, ecx, 0x34u, 4, 0x1u);
    lift_store(&env, ecx, 0x38u, 4, 0x0u);
    lift_store(&env, ecx, 0x3cu, 4, 0x3ff00000u);
    lift_store(&env, ecx, 0x40u, 4, 0x0u);
    lift_store(&env, ecx, 0x44u, 4, 0x0u);
    lift_store(&env, ecx, 0x48u, 4, 0x0u);
    lift_store(&env, ecx, 0x4cu, 4, 0x1u);
    lift_store(&env, ecx, 0x50u, 4, 0x1u);
    lift_store(&env, ecx, 0x54u, 4, 0x0u);
    lift_store(&env, ecx, 0x58u, 4, 0x2u);
    lift_store(&env, ecx, 0x5cu, 4, 0x1u);
    lift_store(&env, ecx, 0x60u, 4, 0x100u);
    lift_store(&env, ecx, 0x88u, 4, 0x0u);
    lift_store(&env, ecx, 0x64u, 4, 0x0u);
    lift_store(&env, ecx, 0x68u, 4, 0x0u);
    lift_store(&env, ecx, 0x6cu, 4, 0x0u);
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
    return env.failed ? 0u : eax;
L_4b93d0:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x118u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b93f0;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x124u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b9430;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x128u, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b9403;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b940c;
L_4b93f0:
    lift_store(&env, ecx, 0x28u, 4, 0x3u);
L_4b93f7:
    lift_store(&env, ecx, 0x2cu, 4, 0x2u);
    goto L_4b9351;
L_4b9403:
    lift_store(&env, ecx, 0x28u, 4, 0x2u);
    goto L_4b93f7;
L_4b940c:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x72u);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x128u, 1)) & 0xffu);
    lift_store(&env, edx, 0x18u, 4, eax);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    edx = 0xffffffffu;
    eax = ecx;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    goto L_4b93f0;
L_4b9430:
    edx = lift_load(&env, ecx, 0xd8u, 4);
    ebx = lift_load(&env, edx, 0x0u, 4);
    eax = lift_load(&env, edx, 0x54u, 4);
    edx = lift_load(&env, edx, 0xa8u, 4);
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b945f;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4b945f;
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4b945f;
    lift_store(&env, ecx, 0x28u, 4, edx);
    lift_store(&env, ecx, 0x2cu, 4, 0x2u);
    goto L_4b9351;
L_4b945f:
    {
        (void)lift_sub(32, ebx, 0x52u, &fl);
    }
    if (!fl.zf)
        goto L_4b9481;
    {
        (void)lift_sub(32, eax, 0x47u, &fl);
    }
    if (!fl.zf)
        goto L_4b9481;
    {
        (void)lift_sub(32, edx, 0x42u, &fl);
    }
    if (!fl.zf)
        goto L_4b9481;
    lift_store(&env, ecx, 0x28u, 4, 0x2u);
    lift_store(&env, ecx, 0x2cu, 4, 0x2u);
    goto L_4b9351;
L_4b9481:
    esi = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, esi, 0x18u, 4, ebx);
    lift_store(&env, esi, 0x1cu, 4, eax);
    lift_store(&env, esi, 0x20u, 4, edx);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x6fu);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x1u;
    eax = ecx;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x28u, 4, 0x3u);
    lift_store(&env, ecx, 0x2cu, 4, 0x2u);
    goto L_4b9351;
L_4b94b4:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x124u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b950b;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x128u, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b94de;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4b94e7;
L_4b94cb:
    lift_store(&env, ecx, 0x28u, 4, 0x5u);
L_4b94d2:
    lift_store(&env, ecx, 0x2cu, 4, 0x4u);
    goto L_4b9351;
L_4b94de:
    lift_store(&env, ecx, 0x28u, 4, 0x4u);
    goto L_4b94d2;
L_4b94e7:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x72u);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_load(&env, ecx, 0x0u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x128u, 1)) & 0xffu);
    lift_store(&env, eax, 0x18u, 4, edx);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    edx = 0xffffffffu;
    eax = ecx;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    goto L_4b94cb;
L_4b950b:
    lift_store(&env, ecx, 0x28u, 4, eax);
    lift_store(&env, ecx, 0x2cu, 4, 0x4u);
    goto L_4b9351;
L_4b951a:
    if (fl.cf || fl.zf)
        goto L_4b93d0;
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4b94b4;
L_4b9525:
    lift_store(&env, ecx, 0x28u, 4, 0x0u);
    lift_store(&env, ecx, 0x2cu, 4, 0x0u);
    goto L_4b9351;
}

uint32_t lifted_f4b98b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B98B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B98B0_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x8u, &fl);
        esp = r;
    }
    esi = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x14u, 4), 0xccu, &fl);
    }
    if (!fl.zf)
        goto L_4b9944;
L_4b98ca:
    eax = (esi + 0x8cu);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
L_4b98d3:
    eax = lift_load(&env, esi, 0x1a4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b9986;
L_4b98e3:
    eax = lift_load(&env, esi, 0x8cu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, esi, 0x74u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4b9962;
    eax = lift_load(&env, esi, 0x8u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4b9910;
    edx = eax;
    eax = lift_load(&env, esi, 0x8cu, 4);
    lift_store(&env, edx, 0x4u, 4, eax);
    edx = lift_load(&env, esi, 0x8u, 4);
    eax = lift_load(&env, esi, 0x74u, 4);
    lift_store(&env, edx, 0x8u, 4, eax);
    edx = lift_load(&env, esi, 0x8u, 4);
    eax = esi;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
L_4b9910:
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, esi, 0x8cu, 4);
    edi = lift_load(&env, esi, 0x1a8u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = esi;
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, esi, 0x8cu, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_4b98e3;
    {
        uint32_t r = lift_xor(32, eax, edx, &fl);
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
    return env.failed ? 0u : eax;
L_4b9944:
    edx = lift_load(&env, eax, 0x1a4u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esi, 0x8cu, 4, 0x0u);
    lift_store(&env, esi, 0x14u, 4, 0xccu);
    goto L_4b98ca;
L_4b9962:
    edx = lift_load(&env, esi, 0x1a4u, 4);
    eax = esi;
    eax = lift_call(&env, lift_load(&env, edx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, esi, 0x1a4u, 4);
    eax = esi;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esi, 0x8cu, 4, 0x0u);
    goto L_4b98d3;
L_4b9986:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x44u, 4), 0x0u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0xcdu, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x14u, 4, eax);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b9cb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B9CB0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B9CB0_STACK, 0, entry);
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
    ebx = eax;
    ecx = lift_load(&env, eax, 0x18u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b9cd2;
L_4b9cbd:
    esi = lift_load(&env, ecx, 0x4u, 4);
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b9ce1;
    edi = lift_load(&env, ecx, 0x0u, 4);
    eax = lift_load(&env, ecx, 0x4u, 4);
    {
        uint32_t r = lift_add(32, edi, edx, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x0u, 4, edi);
    lift_store(&env, ecx, 0x4u, 4, eax);
L_4b9cd2:
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
    return env.failed ? 0u : eax;
L_4b9ce1:
    eax = ebx;
    eax = lift_call(&env, 0x4b9c20u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_sub(32, edx, esi, &fl);
        edx = r;
    }
    goto L_4b9cbd;
}

uint32_t lifted_f4b9cf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B9CF0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B9CF0_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    ecx = eax;
    esi = edx;
    edx = lift_load(&env, eax, 0x18u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4b9d44;
L_4b9d05:
    ecx = lift_load(&env, ecx, 0x18u, 4);
    lift_store(&env, ecx, 0x8u, 4, 0x4b9c10u);
    lift_store(&env, ecx, 0xcu, 4, 0x4b9c20u);
    lift_store(&env, ecx, 0x10u, 4, 0x4b9cb0u);
    lift_store(&env, ecx, 0x14u, 4, 0x4c0860u);
    lift_store(&env, ecx, 0x18u, 4, 0x4b9ce0u);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    lift_store(&env, ecx, 0x0u, 4, 0x0u);
    lift_store(&env, ecx, 0x1cu, 4, esi);
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
    return env.failed ? 0u : eax;
L_4b9d44:
    edi = lift_load(&env, eax, 0x4u, 4);
    ebx = 0x28u;
    eax = lift_call(&env, lift_load(&env, edi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    ebx = 0x1000u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    edi = lift_load(&env, ecx, 0x4u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ecx, 0x18u, 4, eax);
    eax = ecx;
    eax = lift_call(&env, lift_load(&env, edi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edi = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, edi, 0x20u, 4, eax);
    goto L_4b9d05;
}

uint32_t lifted_f4b9d70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B9D70_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B9D70_STACK, 0, entry);
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
    ecx = lift_load(&env, eax, 0x148u, 4);
    edx = lift_load(&env, eax, 0x1acu, 4);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b9db3;
    ecx = lift_load(&env, eax, 0x140u, 4);
    ebx = lift_load(&env, eax, 0x94u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b9dbc;
    eax = lift_load(&env, eax, 0x14cu, 4);
    eax = lift_load(&env, eax, 0xcu, 4);
L_4b9d9e:
    lift_store(&env, edx, 0x1cu, 4, eax);
L_4b9da1:
    lift_store(&env, edx, 0x14u, 4, 0x0u);
    lift_store(&env, edx, 0x18u, 4, 0x0u);
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
    return env.failed ? 0u : eax;
L_4b9db3:
    lift_store(&env, edx, 0x1cu, 4, 0x1u);
    goto L_4b9da1;
L_4b9dbc:
    eax = lift_load(&env, eax, 0x14cu, 4);
    eax = lift_load(&env, eax, 0x48u, 4);
    goto L_4b9d9e;
}

uint32_t lifted_f4b9dd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B9DD0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B9DD0_STACK, 0, entry);
    lift_store(&env, eax, 0x94u, 4, 0x0u);
    eax = lift_call(&env, 0x4b9d70u, eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4b9de0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B9DE0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B9DE0_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x18u, &fl);
        esp = r;
    }
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = lift_load(&env, eax, 0x1acu, 4);
    edx = lift_load(&env, eax, 0x10u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4b9f22;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x50u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b9f5a;
    edi = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    ebx = lift_load(&env, eax, 0xdcu, 4);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4b9f5a;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xa0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b9f5a;
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x70u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b9f39;
L_4b9e3c:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = lift_load(&env, edi, 0x70u, 4);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    edx = lift_load(&env, eax, 0x24u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b9f14;
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
L_4b9e61:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, eax, 0x4cu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4b9f5a;
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b9f5a;
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x2u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b9f5a;
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x10u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b9f5a;
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x20u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b9f5a;
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x12u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b9f5a;
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x4u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b9f5a;
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    ebx = lift_load(&env, ebx, 0xa0u, 4);
    {
        uint32_t r = lift_add(32, ebx, eax, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b9f5a;
    eax = (ebx + 0x4u);
    edx = (edi + 0x4u);
    {
        uint32_t r = lift_add(32, ebx, 0x18u, &fl);
        ebx = r;
    }
L_4b9ed0:
    ecx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, edx, 0x0u, 4, ecx);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4b9edd;
    esi = 0x1u;
L_4b9edd:
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, edx, 0x4u, &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4b9ed0;
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t r = lift_add(32, edi, 0x18u, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_add(32, ecx, 0x100u, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x54u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    ecx = lift_load(&env, edx, 0x24u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b9e61;
L_4b9f14:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4b9f5a;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0xcu, 4, 0x4ba7b0u);
L_4b9f22:
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, eax, 0x9cu, 4, 0x0u);
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
    return env.failed ? 0u : eax;
L_4b9f39:
    edx = lift_load(&env, eax, 0x24u, 4);
    ebx = ((edx * 4u));
    ecx = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t r = lift_sub(32, ebx, edx, &fl);
        ebx = r;
    }
    edx = 0x1u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        ebx = r;
    }
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, edi, 0x70u, 4, eax);
    goto L_4b9e3c;
L_4b9f5a:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0xcu, 4, 0x4ba470u);
    goto L_4b9f22;
}

uint32_t lifted_f4b9f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B9F70_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B9F70_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x4cu, &fl);
        esp = r;
    }
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xffffffa8u, 4, edx);
    eax = lift_load(&env, eax, 0x1acu, 4);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, eax, 0x15cu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, eax, 0x140u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    edx = lift_load(&env, ebp, 0xffffffc4u, 4);
    eax = lift_load(&env, eax, 0x18u, 4);
    ecx = lift_load(&env, edx, 0x1cu, 4);
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ba176;
    eax = (edx + 0x20u);
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
L_4b9fc0:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    eax = lift_load(&env, eax, 0x14u, 4);
    ebx = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ba15a;
L_4b9fd4:
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    edx = lift_load(&env, edx, 0x164u, 4);
    eax = lift_load(&env, eax, 0x20u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x7u, &fl);
        edx = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_call(&env, 0x4c98f0u, eax, edx, ebx, ecx, 0, esp);
    ebx = lift_load(&env, ebx, 0x1bcu, 4);
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ba1b5;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x148u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ba148;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
L_4ba020:
    esi = lift_load(&env, ebp, 0xffffffbcu, 4);
    esi = lift_load(&env, esi, 0x14cu, 4);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x30u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ba1c8;
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = lift_load(&env, esi, 0x4u, 4);
    edi = lift_load(&env, edi, 0x1c0u, 4);
    eax = lift_load(&env, edi, (ebx * 4u) + 0x4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        (void)lift_sub(32, ecx, lift_load(&env, ebp, 0xffffffb4u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ba1d8;
    ebx = lift_load(&env, esi, 0x34u, 4);
L_4ba055:
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    ebx = lift_load(&env, esi, 0x4u, 4);
    edi = lift_load(&env, ebp, 0xffffffa8u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    eax = lift_load(&env, esi, 0x24u, 4);
    {
        uint32_t r = lift_add(32, edi, ebx, &fl);
        edi = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffb0u, 4);
    {
        uint32_t r = lift_imul(32, ebx, eax, &fl);
        ebx = r;
    }
    edx = lift_load(&env, esi, 0x40u, 4);
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    edi = lift_load(&env, edi, 0x0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, edi, ebx, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    ebx = lift_load(&env, esi, 0x38u, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ba127;
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
L_4ba098:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edi = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, edi, lift_load(&env, eax, 0x94u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ba1e0;
L_4ba0aa:
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ba0f5;
    ebx = lift_load(&env, ebp, 0xffffffd4u, 4);
    edi = lift_load(&env, ebp, 0xffffffc4u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, edi, ebx, &fl);
        edi = r;
    }
L_4ba0c7:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = esi;
    ebx = lift_load(&env, edi, 0x20u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t r = lift_add(32, edi, 0x4u, &fl);
        edi = r;
    }
    eax = lift_call(&env, lift_load(&env, ebp, 0xffffffd8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, esi, 0x24u, 4);
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ba0c7;
L_4ba0f5:
    edi = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
    ebx = lift_load(&env, esi, 0x24u, 4);
    eax = lift_load(&env, esi, 0x34u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, edi, eax, &fl);
        edi = r;
    }
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    ebx = lift_load(&env, esi, 0x38u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ba098;
L_4ba127:
    ebx = lift_load(&env, ebp, 0xffffffbcu, 4);
    esi = lift_load(&env, ebp, 0xffffffb8u, 4);
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t r = lift_add(32, ebx, 0x4u, &fl);
        ebx = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    edi = lift_load(&env, edx, 0x148u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, ebx);
    lift_store(&env, ebp, 0xffffffb8u, 4, esi);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ba020;
L_4ba148:
    esi = lift_load(&env, ebp, 0xffffffb4u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    edi = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, esi);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4b9fd4;
L_4ba15a:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffb0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x0u);
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    esi = lift_load(&env, eax, 0x1cu, 4);
    lift_store(&env, ebp, 0xffffffb0u, 4, ebx);
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b9fc0;
L_4ba176:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edi = lift_load(&env, eax, 0x9cu, 4);
    edx = lift_load(&env, eax, 0x94u, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    lift_store(&env, eax, 0x9cu, 4, edi);
    lift_store(&env, eax, 0x94u, 4, edx);
    eax = edx;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x140u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4ba1f1;
    eax = edx;
    eax = lift_call(&env, 0x4b9d70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x3u;
L_4ba1ac:
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
    return env.failed ? 0u : eax;
L_4ba1b5:
    edx = lift_load(&env, ebp, 0xffffffc4u, 4);
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    lift_store(&env, edx, 0x18u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    lift_store(&env, edx, 0x14u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    goto L_4ba1ac;
L_4ba1c8:
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = lift_load(&env, esi, 0x3cu, 4);
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    goto L_4ba127;
L_4ba1d8:
    ebx = lift_load(&env, esi, 0x44u, 4);
    goto L_4ba055;
L_4ba1e0:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, esi, 0x48u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ba0aa;
    goto L_4ba0f5;
L_4ba1f1:
    edx = lift_load(&env, edx, 0x1b4u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    eax = 0x4u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c07d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C07D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C07D0_STACK, 0, entry);
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
    ecx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x1a0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c083c;
L_4c07de:
    edx = lift_load(&env, ecx, 0x1b8u, 4);
    eax = lift_load(&env, edx, 0x14u, 4);
    ebx = lift_load(&env, ecx, 0x1a0u, 4);
    {
        uint32_t r = lift_add(32, eax, 0xd0u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4c0849;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x62u);
    eax = lift_load(&env, ecx, 0x1b8u, 4);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, edx, 0x18u, 4, eax);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x3u;
    eax = ecx;
    eax = lift_call(&env, lift_load(&env, ebx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x1a0u, 4, 0x0u);
L_4c0823:
    eax = lift_load(&env, ecx, 0x1b8u, 4);
    edx = lift_load(&env, eax, 0x14u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    {
        uint32_t r = lift_and(32, edx, 0x7u, &fl);
        edx = r;
    }
    lift_store(&env, eax, 0x14u, 4, edx);
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
L_4c083c:
    eax = lift_call(&env, 0x4bf770u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4c07de;
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
    return env.failed ? 0u : eax;
L_4c0849:
    ebx = lift_load(&env, ecx, 0x18u, 4);
    eax = ecx;
    edx = lift_load(&env, edx, 0x14u, 4);
    eax = lift_call(&env, lift_load(&env, ebx, 0x14u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4c0823;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c0990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C0990_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C0990_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0xd8u, 4, 0x0u);
    lift_store(&env, eax, 0x90u, 4, 0x0u);
    edx = lift_load(&env, eax, 0x1b8u, 4);
    lift_store(&env, eax, 0x1a0u, 4, 0x0u);
    lift_store(&env, edx, 0xcu, 4, 0x0u);
    lift_store(&env, edx, 0x10u, 4, 0x0u);
    lift_store(&env, edx, 0x18u, 4, 0x0u);
    lift_store(&env, edx, 0xa4u, 4, 0x0u);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c0b51(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C0B51_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C0B51_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x8u, &fl);
        esp = r;
    }
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c0b77;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x12cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c0b83;
L_4c0b77:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4c0c82;
L_4c0b83:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x28u, 4), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4c0b95;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x24u, 4), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4c0b97;
L_4c0b95:
    goto L_4c0ba0;
L_4c0b97:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x2cu, 4), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4c0ba2;
L_4c0ba0:
    goto L_4c0bab;
L_4c0ba2:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x78u, 4), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4c0bb7;
L_4c0bab:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4c0c82;
L_4c0bb7:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4c0bd5;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x5cu, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4c0bd7;
L_4c0bd5:
    goto L_4c0be9;
L_4c0bd7:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xb0u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4c0beb;
L_4c0be9:
    goto L_4c0bfa;
L_4c0beb:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xcu, 4), 0x2u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c0bfc;
L_4c0bfa:
    goto L_4c0c0b;
L_4c0bfc:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x60u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4c0c0d;
L_4c0c0b:
    goto L_4c0c1f;
L_4c0c0d:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xb4u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4c0c28;
L_4c0c1f:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4c0c82;
L_4c0c28:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    edx = lift_load(&env, eax, 0x24u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, edx, lift_load(&env, eax, 0x13cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4c0c56;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    edx = lift_load(&env, eax, 0x78u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, edx, lift_load(&env, eax, 0x13cu, 4), &fl);
    }
    if (fl.zf)
        goto L_4c0c58;
L_4c0c56:
    goto L_4c0c72;
L_4c0c58:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, eax, 0xd8u, 4);
    edx = lift_load(&env, eax, 0xccu, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, edx, lift_load(&env, eax, 0x13cu, 4), &fl);
    }
    if (fl.zf)
        goto L_4c0c7b;
L_4c0c72:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x0u);
    goto L_4c0c82;
L_4c0c7b:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x1u);
L_4c0c82:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c1d20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C1D20_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C1D20_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x1c4u, 4);
    lift_store(&env, edx, 0x24u, 4, 0x0u);
    eax = lift_load(&env, eax, 0x74u, 4);
    lift_store(&env, edx, 0x2cu, 4, eax);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c3220(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C3220_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C3220_STACK, 0, entry);
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
    esi = lift_load(&env, eax, 0x1b0u, 4);
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (!fl.cf)
        goto L_4c32f0;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4c32f7;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x54u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c3276;
    edi = lift_load(&env, esi, 0xcu, 4);
    lift_store(&env, esi, 0x4u, 4, 0x4c3320u);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4c3261;
L_4c324f:
    lift_store(&env, esi, 0x18u, 4, 0x0u);
    eax = lift_load(&env, esi, 0x18u, 4);
    lift_store(&env, esi, 0x14u, 4, eax);
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
    return env.failed ? 0u : eax;
L_4c3261:
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, eax, 0x4u, 4);
    ecx = lift_load(&env, esi, 0x10u, 4);
    edx = lift_load(&env, esi, 0x8u, 4);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = lift_call(&env, lift_load(&env, edi, 0x1cu, 4), eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esi, 0xcu, 4, eax);
    goto L_4c324f;
L_4c3276:
    eax = lift_load(&env, eax, 0x1c4u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, esi, 0x4u, 4, eax);
    lift_store(&env, esi, 0x18u, 4, 0x0u);
    eax = lift_load(&env, esi, 0x18u, 4);
    lift_store(&env, esi, 0x14u, 4, eax);
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
    return env.failed ? 0u : eax;
L_4c3294:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c32b3;
L_4c329a:
    lift_store(&env, esi, 0x4u, 4, 0x4c33a0u);
    lift_store(&env, esi, 0x18u, 4, 0x0u);
    eax = lift_load(&env, esi, 0x18u, 4);
    lift_store(&env, esi, 0x14u, 4, eax);
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
    return env.failed ? 0u : eax;
L_4c32b3:
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, edx, 0x14u, 4, 0x4u);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    goto L_4c329a;
L_4c32c2:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c32e1;
L_4c32c8:
    lift_store(&env, esi, 0x4u, 4, 0x4c3470u);
    lift_store(&env, esi, 0x18u, 4, 0x0u);
    eax = lift_load(&env, esi, 0x18u, 4);
    lift_store(&env, esi, 0x14u, 4, eax);
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
    return env.failed ? 0u : eax;
L_4c32e1:
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, edx, 0x14u, 4, 0x4u);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    goto L_4c32c8;
L_4c32f0:
    if (fl.cf || fl.zf)
        goto L_4c32c2;
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4c3294;
L_4c32f7:
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, edx, 0x14u, 4, 0x4u);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esi, 0x18u, 4, 0x0u);
    eax = lift_load(&env, esi, 0x18u, 4);
    lift_store(&env, esi, 0x14u, 4, eax);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c33a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C33A0_STACK + 4 + 4 * 3 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C33A0_STACK, 3, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x18u, &fl);
        esp = r;
    }
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    esi = lift_load(&env, eax, 0x1b0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x18u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c3432;
L_4c33c0:
    edi = lift_load(&env, ebp, 0xfffffff4u, 4);
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, esi, 0x18u, 4);
    ecx = lift_load(&env, esi, 0x10u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esi + 0x18u);
    ebx = lift_load(&env, esi, 0xcu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, edi, 0x1c4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edi = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = lift_load(&env, esi, 0x18u, 4);
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c341f;
    edx = edi;
    {
        uint32_t r = lift_sub(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    edi = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, esi, 0xcu, 4);
    edi = lift_load(&env, edi, 0x1ccu, 4);
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, ebp, 0xcu, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t r = lift_add(32, lift_load(&env, edx, 0x0u, 4), eax, &fl);
        lift_store(&env, edx, 0x0u, 4, r);
    }
L_4c341f:
    eax = lift_load(&env, esi, 0x18u, 4);
    ebx = lift_load(&env, esi, 0x10u, 4);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.cf)
        goto L_4c344b;
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
    return env.failed ? 0u : eax;
L_4c3432:
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, eax, 0x4u, 4);
    ecx = lift_load(&env, esi, 0x10u, 4);
    ebx = lift_load(&env, esi, 0x14u, 4);
    edx = lift_load(&env, esi, 0x8u, 4);
    eax = lift_call(&env, lift_load(&env, edi, 0x1cu, 4), eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esi, 0xcu, 4, eax);
    goto L_4c33c0;
L_4c344b:
    edi = lift_load(&env, esi, 0x14u, 4);
    lift_store(&env, esi, 0x18u, 4, 0x0u);
    {
        uint32_t r = lift_add(32, edi, ebx, &fl);
        edi = r;
    }
    lift_store(&env, esi, 0x14u, 4, edi);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c35f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C35F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C35F0_STACK, 0, entry);
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
    edx = lift_load(&env, eax, 0x1c4u, 4);
    ecx = lift_load(&env, eax, 0x138u, 4);
    lift_store(&env, edx, 0x5cu, 4, ecx);
    eax = lift_load(&env, eax, 0x74u, 4);
    lift_store(&env, edx, 0x60u, 4, eax);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c3e40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C3E40_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C3E40_STACK, 0, entry);
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
    ecx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, ecx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    eax = lift_call(&env, 0x4b91b0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffu;
    eax = lift_call(&env, 0x4eb4d4u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c3f80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C3F80_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C3F80_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, edx, 0x6cu, 4, 0x0u);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x0u);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c5a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C5A00_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C5A00_STACK, 0, entry);
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
    ecx = 0x1u;
L_4c5a0b:
    edx = ecx;
    eax = esi;
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = lift_call(&env, 0x4c58e0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c5a0b;
    ebx = 0x54u;
    eax = esi;
    edx = lift_load(&env, esi, 0x4u, 4);
    eax = lift_call(&env, 0x4c5bc0u, eax, edx, ebx, ecx, 0, esp);
    eax = esi;
    lift_store(&env, esi, 0x4u, 4, 0x0u);
    eax = lift_call(&env, 0x4c5c20u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c5bb0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C5BB0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C5BB0_STACK, 0, entry);
    eax = edx;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c5bc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C5BC0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C5BC0_STACK, 0, entry);
    eax = edx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c5bd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C5BD0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C5BD0_STACK, 0, entry);
    eax = edx;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c5be0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C5BE0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C5BE0_STACK, 0, entry);
    eax = edx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c9820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C9820_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C9820_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = edx;
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = (eax + 0xffffffffu);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c9840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C9840_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C9840_STACK, 0, entry);
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
    ecx = eax;
    ebx = edx;
    eax = (edx + 0xffffffffu);
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    edx = ecx;
    eax = ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    eax = ecx;
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c98f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C98F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C98F0_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = edx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c9daf(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C9DAF_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C9DAF_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5054a1u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c9dc0;
    eax = lift_call(&env, 0x4db719u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4c9dc0:
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = lift_call(&env, 0x4c9b6au, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c9dd6(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C9DD6_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C9DD6_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5054a1u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c9de7;
    eax = lift_call(&env, 0x4db710u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4c9de7:
    ebx = 0x2u;
    eax = lift_call(&env, 0x4c9b6au, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c9e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C9E00_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C9E00_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5054a1u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c9e11;
    eax = lift_call(&env, 0x4db7c8u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4c9e11:
    ebx = 0x1u;
    eax = lift_call(&env, 0x4c9b6au, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4c9fe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C9FE0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C9FE0_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4d9510u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA070_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA070_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_call(&env, 0x4ca060u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebx, 0x0u, 4, eax);
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca110(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA110_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA110_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t r = lift_sub(32, eax, 0xcu, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x500818u, 4), &fl);
    }
    if (fl.zf)
        goto L_4ca141;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c34u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ca138;
    eax = lift_load(&env, ebx, 0x0u, 4);
    {
        uint32_t r = lift_sub(32, eax, 0xcu, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
L_4ca138:
    eax = lift_call(&env, 0x4ca060u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebx, 0x0u, 4, eax);
L_4ca141:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA150_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA150_STACK, 1, entry);
    eax = lift_load(&env, esp, 0x4u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x500818u, 4), &fl);
    }
    if (fl.zf)
        goto L_4ca171;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c34u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ca171;
    eax = lift_load(&env, esp, 0x4u, 4);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
L_4ca171:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca1a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA1A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA1A0_STACK, 0, entry);
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
    ecx = eax;
    ebx = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t r = lift_sub(32, ebx, 0xcu, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x0u, 4), 0x1u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ca1d0;
    eax = lift_call(&env, 0x4ca110u, eax, edx, ebx, ecx, 0, esp);
    eax = ecx;
    edx = lift_load(&env, ebx, 0x4u, 4);
    eax = lift_call(&env, 0x4ca0d0u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, ebx, 0x4u, 4);
    edx = (ebx + 0xcu);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    ecx = lift_load(&env, ecx, 0x0u, 4);
    ebx = eax;
    eax = ecx;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
L_4ca1d0:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA1E0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA1E0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t r = lift_sub(32, eax, 0xcu, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x1u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ca1f2;
    {
        (void)lift_sub(32, edx, lift_load(&env, eax, 0x8u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ca200;
L_4ca1f2:
    eax = ecx;
    eax = lift_call(&env, 0x4ca110u, eax, edx, ebx, ecx, 0, esp);
    eax = ecx;
    eax = lift_call(&env, 0x4ca0d0u, eax, edx, ebx, ecx, 0, esp);
L_4ca200:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA210_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA210_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t r = lift_sub(32, eax, 0xcu, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x500818u, 4), &fl);
    }
    if (fl.zf)
        goto L_4ca237;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c34u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ca237;
    eax = lift_load(&env, ebx, 0x0u, 4);
    {
        uint32_t r = lift_sub(32, eax, 0xcu, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
L_4ca237:
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA280_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA280_STACK, 0, entry);
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
    esi = eax;
    edi = edx;
    eax = lift_call(&env, 0x4ca060u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esi, 0x0u, 4, eax);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4ca2b2;
    eax = edi;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_and(32, eax, 0xffffu, &fl);
        eax = r;
    }
    eax = (eax & 0xffffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ca2b2;
    edx = (edi & 0xffffu);
    eax = esi;
    eax = lift_call(&env, 0x4db8c0u, eax, edx, ebx, ecx, 0, esp);
    goto L_4ca2d6;
L_4ca2b2:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4ca2d6;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1d24u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ca2d6;
    edx = eax;
    eax = esi;
    eax = lift_call(&env, 0x4ca0d0u, eax, edx, ebx, ecx, 0, esp);
    edx = edi;
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
L_4ca2d6:
    eax = esi;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca370(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA370_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA370_STACK, 0, entry);
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
    ebx = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4ca385;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1d24u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edx = eax;
L_4ca385:
    eax = esi;
    eax = lift_call(&env, 0x4ca2e0u, eax, edx, ebx, ecx, 0, esp);
    eax = esi;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA3A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA3A0_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4ca3b4;
    eax = edx;
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    goto L_4ca3b6;
L_4ca3b4:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4ca3b6:
    ebx = ((eax * 2u));
    edx = ebx;
    eax = ecx;
    eax = lift_call(&env, 0x4ca1e0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    edx = esi;
    eax = lift_load(&env, ecx, 0x0u, 4);
    eax = lift_call(&env, 0x4ca730u, eax, edx, ebx, ecx, 0, esp);
    edx = 0xffffffffu;
    eax = ecx;
    eax = lift_call(&env, 0x4ca6c0u, eax, edx, ebx, ecx, 0, esp);
    eax = ecx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca3f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA3F0_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA3F0_STACK, 1, entry);
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
    ebp = ebx;
    {
        uint32_t r = lift_add(32, edx, ecx, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4ca41c;
    eax = lift_call(&env, 0x4ca0d0u, eax, edx, ebx, ecx, 0, esp);
    ebx = edi;
    edx = ebp;
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, esp, 0x10u, 4);
    eax = lift_load(&env, esi, 0x0u, 4);
    ebx = ecx;
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
L_4ca41c:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA600_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA600_STACK, 0, entry);
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
    ebx = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4ca615;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1d24u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edx = eax;
L_4ca615:
    eax = esi;
    eax = lift_call(&env, 0x4ca5a0u, eax, edx, ebx, ecx, 0, esp);
    eax = esi;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA710_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA710_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4ca1a0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, edx, 0x0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1904u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ca970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CA970_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CA970_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    ebx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x5188d0u);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    eax = ebx;
    lift_store(&env, esp, 0x14u, 4, ebx);
    eax = lift_call(&env, 0x4cbf10u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, eax, 0x0u, 4, 0x518a94u);
    ebx = eax;
    lift_store(&env, eax, 0x70u, 4, edx);
    eax = lift_call(&env, 0x4ce780u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, eax, 0x4u, 4, ebx);
    eax = lift_call(&env, 0x4f1b9cu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebx, 0x28u, 4, eax);
    eax = lift_call(&env, 0x4f1ba0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebx, 0x2cu, 4, eax);
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, eax, 0x4u, 4, ebx);
    lift_store(&env, ebx, 0x60u, 4, 0x0u);
    lift_store(&env, ebx, 0x84u, 4, 0x0u);
    lift_store(&env, ebx, 0x88u, 4, 0x0u);
    lift_store(&env, ebx, 0x74u, 4, 0x0u);
    lift_store(&env, ebx, 0x80u, 4, 0x0u);
    lift_store(&env, ebx, 0xa0u, 4, 0x0u);
    lift_store(&env, ebx, 0x78u, 4, 0x0u);
    lift_store(&env, ebx, 0xaau, 2, 0x0u);
    lift_store(&env, ebx, 0x68u, 4, 0x0u);
    lift_store(&env, ebx, 0xa4u, 4, 0x0u);
    lift_store(&env, ebx, 0x98u, 4, 0x0u);
    lift_store(&env, ebx, 0x9cu, 4, 0x0u);
    lift_store(&env, ebx, 0x8cu, 4, 0x0u);
    lift_store(&env, ebx, 0x90u, 4, 0x0u);
    lift_store(&env, ebx, 0xacu, 4, 0x0u);
    lift_store(&env, ebx, 0xb8u, 4, 0x0u);
    lift_store(&env, ebx, 0xbcu, 4, 0x0u);
    lift_store(&env, ebx, 0xb4u, 4, 0x0u);
    lift_store(&env, ebx, 0x7cu, 4, 0x0u);
    lift_store(&env, ebx, 0xb0u, 4, 0x200u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0xaau, 2)) & 0xffffu);
    lift_store(&env, ebx, 0xa8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = ebx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cafd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CAFD0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CAFD0_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, eax, 0xa0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cafeb;
    eax = lift_load(&env, eax, 0xa0u, 4);
    edx = lift_load(&env, eax, 0x1cu, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x10u, 4), eax, edx, ebx, ecx, 0, esp);
L_4cafeb:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0xacu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cb013;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x4u, 4);
    ebx = 0x500b58u;
    edx = 0x500b48u;
    ecx = lift_load(&env, eax, 0xacu, 4);
    eax = esi;
    eax = lift_call(&env, 0x4dd040u, eax, edx, ebx, ecx, 0, esp);
L_4cb013:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cb460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CB460_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CB460_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    edx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x518c0cu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, edx);
    lift_store(&env, edx, 0x0u, 4, 0x517454u);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, edx, 0x0u, 4, 0x518cb4u);
    lift_store(&env, edx, 0x4u, 4, 0x1u);
    lift_store(&env, edx, 0x8u, 4, 0x0u);
    lift_store(&env, edx, 0xcu, 4, 0x0u);
    lift_store(&env, edx, 0x10u, 4, 0x0u);
    lift_store(&env, edx, 0x14u, 4, 0x1u);
    lift_store(&env, edx, 0x18u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = edx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cb950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CB950_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CB950_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x4u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x1u;
    eax = lift_call(&env, lift_load(&env, ecx, 0x94u, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cb970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CB970_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CB970_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x4u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = 0xffffffffu;
    eax = lift_call(&env, lift_load(&env, ecx, 0x94u, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cba60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CBA60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CBA60_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4ce220u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0xc8u, 4);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cba70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CBA70_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CBA70_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x24u, 4, 0x518d14u);
    lift_store(&env, eax, 0x1cu, 4, 0x0u);
    lift_store(&env, eax, 0x20u, 4, 0x0u);
    lift_store(&env, eax, 0x18u, 4, 0x0u);
    edx = lift_load(&env, eax, 0x1cu, 4);
    lift_store(&env, eax, 0x4u, 4, edx);
    lift_store(&env, eax, 0x0u, 4, edx);
    edx = lift_load(&env, eax, 0x20u, 4);
    lift_store(&env, eax, 0xcu, 4, edx);
    lift_store(&env, eax, 0x8u, 4, edx);
    edx = lift_load(&env, eax, 0x18u, 4);
    lift_store(&env, eax, 0x10u, 4, 0x0u);
    lift_store(&env, eax, 0x14u, 4, edx);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cbe80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CBE80_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CBE80_STACK, 0, entry);
    eax = lift_call(&env, 0x4ce780u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x4u, 4);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cbf10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CBF10_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CBF10_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    edx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x518d8cu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    eax = edx;
    lift_store(&env, esp, 0x14u, 4, edx);
    eax = lift_call(&env, 0x4cb460u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, eax, 0x0u, 4, 0x518e24u);
    lift_store(&env, eax, 0x4cu, 4, 0x0u);
    edx = eax;
    lift_store(&env, eax, 0x50u, 4, 0x0u);
    eax = lift_call(&env, 0x4cbf90u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = edx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cc0d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CC0D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CC0D0_STACK, 0, entry);
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
    ebx = eax;
    edi = 0x1u;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    goto L_4cc0e4;
L_4cc0e0:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4cc10b;
L_4cc0e4:
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
    eax = (ebx + 0x30u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a5cu, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cc10b;
    ecx = lift_load(&env, ebx, 0x0u, 4);
    edx = esi;
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, ecx, 0x64u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cc0e0;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
L_4cc10b:
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, edx, 0x60u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cc144;
    edx = (ebx + 0x30u);
    ecx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, ecx, 0x68u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cc12b;
    edi = 0x1u;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
L_4cc12b:
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
    eax = (ebx + 0x30u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a5cu, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cc10b;
    goto L_4cc0e0;
L_4cc144:
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, edx, 0x6cu, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cc200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CC200_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CC200_STACK, 0, entry);
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
    edi = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4cc300;
    esi = lift_load(&env, eax, 0x1cu, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4cc250;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x1cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cc250;
    {
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a28u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cc250;
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
        uint32_t v = 0x363u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf650u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    {
        uint32_t v = 0x1u;
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x363u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d1ae0u, eax, edx, ebx, ecx, 6, esp);
    esp += 24u;
L_4cc250:
    eax = lift_call(&env, 0x4ce780u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x8u, 4);
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cc317;
L_4cc262:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x1cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cc2e8;
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.zf)
        goto L_4cc2e8;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x88u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cc28a;
    eax = ebx;
    edx = lift_load(&env, ebx, 0x88u, 4);
    eax = lift_call(&env, 0x4ccdd0u, eax, edx, ebx, ecx, 0, esp);
L_4cc28a:
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a28u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cc2a1;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x88u, 4), 0x0u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4cc2c8;
L_4cc2a1:
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
        uint32_t v = 0x363u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf650u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    {
        uint32_t v = 0x1u;
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
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x363u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d1ae0u, eax, edx, ebx, ecx, 6, esp);
    esp += 24u;
L_4cc2c8:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x88u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4cc2de;
    eax = ebx;
    edx = lift_load(&env, ebx, 0x88u, 4);
    eax = lift_call(&env, 0x4ccdd0u, eax, edx, ebx, ecx, 0, esp);
L_4cc2de:
    lift_store(&env, ebx, 0x88u, 4, 0xffffffffu);
L_4cc2e8:
    ebx = lift_load(&env, ebx, 0x54u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4cc262;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.sf != fl.of) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
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
    return env.failed ? 0u : eax;
L_4cc300:
    if (fl.sf != fl.of)
        goto L_4cc317;
    eax = lift_call(&env, 0x4ce780u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cc317;
    eax = lift_call(&env, 0x4dec60u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4dec70u, eax, edx, ebx, ecx, 0, esp);
L_4cc317:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.sf != fl.of) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cc760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CC760_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CC760_STACK, 0, entry);
    {
        uint32_t v = 0x30u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dba80u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cc771;
    lift_store(&env, eax, 0x0u, 4, 0x518ec4u);
L_4cc771:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cc780(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CC780_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CC780_STACK, 0, entry);
    {
        uint32_t v = 0x4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dba80u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cc791;
    lift_store(&env, eax, 0x0u, 4, 0x518eb4u);
L_4cc791:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cc7c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CC7C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CC7C0_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_load(&env, eax, 0x1cu, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4ccdd0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0x1cu, 4);
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ae8u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
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
    edx = 0x5c5ca8u;
    eax = lift_load(&env, ebx, 0x1cu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = lift_call(&env, 0x4ccd80u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cc990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CC990_STACK + 4 + 4 * 3 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CC990_STACK, 3, entry);
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
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x4u, 4);
    ecx = lift_load(&env, esp, 0x14u, 4);
    esi = lift_load(&env, eax, 0x0u, 4);
    ebx = lift_load(&env, esp, 0x10u, 4);
    edx = lift_load(&env, esp, 0xcu, 4);
    eax = lift_call(&env, lift_load(&env, esi, 0x90u, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ccad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCAD0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCAD0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x78u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ccadf;
    eax = lift_load(&env, eax, 0x78u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, ecx, 0x2cu, 4), eax, edx, ebx, ecx, 0, esp);
L_4ccadf:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ccaf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCAF0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCAF0_STACK, 0, entry);
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
    ecx = eax;
    eax = edx;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0xa0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ccb09;
    ecx = lift_load(&env, edx, 0x24u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
L_4ccb09:
    ecx = lift_load(&env, ecx, 0xa0u, 4);
    ebx = lift_load(&env, ecx, 0x1cu, 4);
    eax = ecx;
    eax = lift_call(&env, lift_load(&env, ebx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ccb9f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCB9F_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCB9F_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4cea15u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ccbc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCBC0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCBC0_STACK, 0, entry);
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
    edi = edx;
    esi = ebx;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x14u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ccc03;
    eax = lift_call(&env, 0x4ce220u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x30u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ccc03;
    eax = lift_call(&env, 0x4f1ba0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x4cfe40u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ae0u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    lift_store(&env, ebx, 0x30u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ccc03;
    eax = lift_call(&env, 0x4d9510u, eax, edx, ebx, ecx, 0, esp);
L_4ccc03:
    edx = 0x4ccc40u;
    eax = 0x5c5c28u;
    eax = lift_call(&env, 0x4dc030u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dc400u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f17d8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, ebx, 0x4u, 4, eax);
    lift_store(&env, ebx, 0x8u, 4, esi);
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ccc36;
    eax = lift_call(&env, 0x4dde50u, eax, edx, ebx, ecx, 0, esp);
L_4ccc36:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ccc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCC60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCC60_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x34u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ccc7a;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1984u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
L_4ccc7a:
    eax = lift_load(&env, eax, 0x34u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, ecx, 0x70u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cccc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCCC0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCCC0_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, eax, 0x38u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cccd7;
    {
        uint32_t v = 0xfffffff0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19f0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
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
    return env.failed ? 0u : eax;
L_4cccd7:
    eax = lift_load(&env, eax, 0x38u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x74u, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cccf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCCF0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCCF0_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, eax, 0x38u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ccd07;
    {
        uint32_t v = 0xffffffecu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19f0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
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
    return env.failed ? 0u : eax;
L_4ccd07:
    eax = lift_load(&env, eax, 0x38u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x78u, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ccd20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCD20_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCD20_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x38u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ccd34;
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf480u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
L_4ccd34:
    eax = lift_load(&env, eax, 0x38u, 4);
    esi = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, esi, 0x80u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ccd50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCD50_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCD50_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x38u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ccd64;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1adcu, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
L_4ccd64:
    eax = lift_load(&env, eax, 0x38u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, ecx, 0x84u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ccdd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCDD0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCDD0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x38u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ccde4;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1af0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
L_4ccde4:
    eax = lift_load(&env, eax, 0x38u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, ecx, 0xa4u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cce00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCE00_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCE00_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, eax, 0x38u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cce15;
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a24u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
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
    return env.failed ? 0u : eax;
L_4cce15:
    eax = lift_load(&env, eax, 0x38u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0xa8u, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cce30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCE30_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCE30_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x38u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cce44;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1948u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
L_4cce44:
    eax = lift_load(&env, eax, 0x38u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, ecx, 0xacu, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cce60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CCE60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CCE60_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, eax, 0x38u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cce7b;
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1aa8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
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
    return env.failed ? 0u : eax;
L_4cce7b:
    eax = lift_load(&env, eax, 0x38u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0xb0u, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cd090(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CD090_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CD090_STACK, 0, entry);
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
    ebx = edx;
    edx = lift_load(&env, eax, 0x0u, 4);
    ecx = (edx + 0x1u);
    lift_store(&env, eax, 0x0u, 4, ecx);
    lift_store(&env, edx, 0x0u, 1, (ebx & 0xffu));
    {
        uint32_t a = lift_load(&env, eax, 0x10u, 4);
        uint32_t r = lift_inc(32, a, &fl, 1);
        lift_store(&env, eax, 0x10u, 4, r);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cd520(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CD520_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CD520_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x14u);
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, esp, 0x18u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, esp, 0x18u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cd544u, eax, edx, ebx, ecx, 4, esp);
    {
        uint32_t r = lift_add(32, esp, 0x10u, &fl);
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
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cd836(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CD836_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CD836_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    eax = lift_call(&env, 0x4e0eafu, eax, edx, ebx, ecx, 0, esp);
    edx = ecx;
    eax = lift_call(&env, 0x4e0ec7u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cd847(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CD847_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CD847_STACK, 0, entry);
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
    ecx = eax;
    edi = edx;
    esi = ebx;
L_4cd850:
    ebx = esi;
    edx = edi;
    eax = ecx;
    eax = lift_call(&env, 0x4e0eafu, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cd863;
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
    return env.failed ? 0u : eax;
L_4cd863:
    edx = ecx;
    eax = lift_call(&env, 0x4e0ec7u, eax, edx, ebx, ecx, 0, esp);
    goto L_4cd850;
}

uint32_t lifted_f4cda40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CDA40_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CDA40_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4cda50;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x507c34u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4cda62;
L_4cda50:
    eax = 0x4u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4cda62:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    eax = lift_call(&env, 0x4e0fc0u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    eax = edx;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cacu, 4), eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cda90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CDA90_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CDA90_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    esi = eax;
    lift_store(&env, esp, 0x0u, 1, (edx & 0xffu));
    eax = lift_call(&env, 0x4ca060u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esi, 0x0u, 4, eax);
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4cdabc;
    edx = ebx;
    eax = esi;
    eax = lift_call(&env, 0x4ca0d0u, eax, edx, ebx, ecx, 0, esp);
    edx = (uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, esp, 0x0u, 1);
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
L_4cdabc:
    eax = esi;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cdaf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CDAF0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CDAF0_STACK, 0, entry);
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
    ebp = esp;
    {
        uint32_t r = lift_sub(32, esp, 0x14u, &fl);
        esp = r;
    }
    esi = eax;
    edi = edx;
    eax = (ebp + 0xffffffecu);
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
    lift_store(&env, ebp, 0xfffffff0u, 4, 0x4ec1ecu);
    lift_store(&env, ebp, 0xfffffff4u, 4, 0x518f5cu);
    lift_store(&env, ebp, 0xfffffff8u, 4, 0x0u);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cdb2c;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    goto L_4cdb39;
L_4cdb2c:
    eax = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t r = lift_sub(32, eax, 0xcu, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x4u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4cdb39;
    ebx = lift_load(&env, eax, 0x4u, 4);
L_4cdb39:
    eax = edi;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t r = lift_sub(32, eax, 0xcu, &fl);
        eax = r;
    }
    edx = edi;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x4u, 4);
    eax = esi;
    {
        uint32_t r = lift_sub(32, ecx, ebx, &fl);
        ecx = r;
    }
    eax = lift_call(&env, 0x4ca240u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    env.chain = eax;
    eax = edi;
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cdb70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CDB70_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CDB70_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x14u, &fl);
        esp = r;
    }
    edi = eax;
    esi = edx;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x518f60u);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4cdbab;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    goto L_4cdbb8;
L_4cdbab:
    eax = lift_load(&env, edi, 0x0u, 4);
    {
        uint32_t r = lift_sub(32, eax, 0xcu, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x4u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4cdbb8;
    ebx = lift_load(&env, eax, 0x4u, 4);
L_4cdbb8:
    eax = esi;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = esi;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = edi;
    eax = lift_call(&env, 0x4ca240u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = esi;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cdfe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CDFE0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CDFE0_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4ca1a0u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ce017;
L_4cdff3:
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, edx, 0x0u, 1);
    eax = lift_call(&env, 0x4e10d0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ce007;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4ce009;
    ecx = edx;
    goto L_4ce009;
L_4ce007:
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
L_4ce009:
    eax = edx;
    eax = lift_call(&env, 0x4e1054u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cdff3;
L_4ce017:
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ce028;
    lift_store(&env, ecx, 0x0u, 1, 0x0u);
    eax = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t r = lift_sub(32, ecx, lift_load(&env, esi, 0x0u, 4), &fl);
        ecx = r;
    }
    lift_store(&env, eax, 0xfffffff8u, 4, ecx);
    {
        uint32_t r = lift_sub(32, eax, 0xcu, &fl);
        eax = r;
    }
L_4ce028:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ce080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CE080_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CE080_STACK, 0, entry);
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
L_4ce083:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = (edx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    {
        (void)lift_and(8, lift_load(&env, edx, 0x507d58u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ce099;
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    goto L_4ce083;
L_4ce099:
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x2bu, &fl);
    }
    if (fl.zf)
        goto L_4ce0a5;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ce0a6;
L_4ce0a5:
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
L_4ce0a6:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
L_4ce0a8:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = (ebx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, ebx, 0xffu, &fl);
        ebx = r;
    }
    {
        (void)lift_and(8, lift_load(&env, ebx, 0x507d58u, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4ce0ca;
    {
        uint32_t r = lift_imul(32, edx, 0xau, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_add(32, edx, ebx, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, edx, 0x30u, &fl);
        edx = r;
    }
    goto L_4ce0a8;
L_4ce0ca:
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4ce0d1;
    {
        uint32_t a = edx;
        uint32_t r = lift_sub(32, 0, a, &fl);
        edx = r;
    }
L_4ce0d1:
    eax = edx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ce810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CE810_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CE810_STACK, 0, entry);
    {
        uint32_t v = 0x103cu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dba80u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ce82e;
    edx = 0x1u;
    eax = lift_call(&env, 0x4ce230u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, eax, 0x0u, 4, 0x519374u);
L_4ce82e:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ce9fd(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CE9FD_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CE9FD_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cea0a;
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
L_4cea0a:
    eax = ecx;
    eax = lift_call(&env, 0x4ce9c0u, eax, edx, ebx, ecx, 0, esp);
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cf320(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CF320_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CF320_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    ecx = eax;
    eax = esp;
    ebx = 0x20u;
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
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x5194a0u);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    eax = ecx;
    lift_store(&env, esp, 0x14u, 4, ecx);
    eax = lift_call(&env, 0x4cb460u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    ecx = eax;
    lift_store(&env, eax, 0x0u, 4, 0x519664u);
    {
        uint32_t r = lift_add(32, eax, 0x1cu, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cf3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CF3A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CF3A0_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    ecx = eax;
    esi = edx;
    eax = esp;
    ebx = 0x20u;
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
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x5194acu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    eax = ecx;
    lift_store(&env, esp, 0x14u, 4, ecx);
    eax = lift_call(&env, 0x4cb460u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    ecx = eax;
    lift_store(&env, eax, 0x0u, 4, 0x519664u);
    {
        uint32_t r = lift_add(32, eax, 0x1cu, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x1cu, 4, esi);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cf420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CF420_STACK + 4 + 4 * 5 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CF420_STACK, 5, entry);
    {
        uint32_t v = lift_load(&env, esp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19f0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    edx = lift_load(&env, esp, 0xcu, 4);
    {
        uint32_t a = edx;
        edx = (~a) & lift_mask(4);
    }
    {
        uint32_t r = lift_and(32, edx, eax, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_or(32, edx, lift_load(&env, esp, 0x10u, 4), &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_4cf444;
    {
        uint32_t r = lift_xor(32, eax, edx, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
L_4cf444:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0xcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0xcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ad0u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x14u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cf477;
    eax = lift_load(&env, esp, 0x14u, 4);
    {
        uint32_t r = lift_or(8, (eax & 0xffu), 0x17u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t v = eax;
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
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ad8u, eax, edx, ebx, ecx, 7, esp);
    esp += 28u;
L_4cf477:
    eax = 0x1u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cf480(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CF480_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CF480_STACK, 4, entry);
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xffffffecu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf420u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cf5d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CF5D0_STACK + 4 + 4 * 3 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CF5D0_STACK, 3, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x10u, 4);
    {
        (void)lift_sub(32, lift_load(&env, esp, 0xcu, 4), 0xfffffffeu, &fl);
    }
    if (!fl.zf)
        goto L_4cf649;
    {
        (void)lift_sub(32, eax, 0x201u, &fl);
    }
    if (fl.zf)
        goto L_4cf5f5;
    {
        (void)lift_sub(32, eax, 0x207u, &fl);
    }
    if (fl.zf)
        goto L_4cf5f5;
    {
        (void)lift_sub(32, eax, 0x204u, &fl);
    }
    if (!fl.zf)
        goto L_4cf649;
L_4cf5f5:
    eax = lift_load(&env, esp, 0x8u, 4);
    eax = lift_call(&env, 0x4d1900u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cf616;
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f199cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ebx = eax;
L_4cf616:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4cf649;
    eax = lift_call(&env, 0x4f1994u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.zf)
        goto L_4cf649;
    eax = ebx;
    eax = lift_call(&env, 0x4cce00u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cf649;
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1aacu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4cf649:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cf850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CF850_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CF850_STACK, 0, entry);
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
    esi = eax;
    eax = lift_call(&env, 0x4ce220u, eax, edx, ebx, ecx, 0, esp);
    edi = lift_load(&env, esi, 0x0u, 4);
    ecx = lift_load(&env, eax, 0x44u, 4);
    ebx = lift_load(&env, eax, 0x40u, 4);
    edx = lift_load(&env, eax, 0x3cu, 4);
    eax = esi;
    eax = lift_call(&env, lift_load(&env, edi, 0xa4u, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cf880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CF880_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CF880_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4ce780u, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x14u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cf8bc;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4cf8bc;
    eax = 0x44u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cf8b9;
    ecx = 0x1u;
    ebx = 0x1cu;
    edx = 0x502ae8u;
    eax = lift_call(&env, 0x4decd0u, eax, edx, ebx, ecx, 0, esp);
L_4cf8b9:
    lift_store(&env, esi, 0x14u, 4, eax);
L_4cf8bc:
    eax = lift_load(&env, esi, 0x14u, 4);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cf8e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CF8E0_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CF8E0_STACK, 1, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x1u;
    edx = lift_load(&env, esp, 0x8u, 4);
    eax = lift_call(&env, 0x4cf880u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    eax = lift_call(&env, 0x4ded70u, eax, edx, ebx, ecx, 0, esp);
    edx = ecx;
    ebx = eax;
    eax = lift_call(&env, 0x4cce90u, eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cf940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CF940_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CF940_STACK, 0, entry);
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
    ecx = eax;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4cf94d;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4cf94d:
    eax = 0x1u;
    eax = lift_call(&env, 0x4cf880u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    lift_store(&env, ecx, 0x1cu, 4, edx);
    eax = lift_call(&env, 0x4df160u, eax, edx, ebx, ecx, 0, esp);
    edx = ebx;
    lift_store(&env, eax, 0x0u, 4, ecx);
    eax = ecx;
    eax = lift_call(&env, 0x4cce90u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cf980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CF980_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CF980_STACK, 0, entry);
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
    ecx = eax;
    ebx = lift_load(&env, eax, 0x1cu, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4cf9a6;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4cf880u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cf99f;
    edx = lift_load(&env, ecx, 0x1cu, 4);
    eax = lift_call(&env, 0x4df1c0u, eax, edx, ebx, ecx, 0, esp);
L_4cf99f:
    lift_store(&env, ecx, 0x1cu, 4, 0x0u);
L_4cf9a6:
    eax = ebx;
    lift_store(&env, ecx, 0x38u, 4, 0x0u);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cf9d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CF9D0_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CF9D0_STACK, 4, entry);
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x360u, &fl);
    }
    if (!fl.zf)
        goto L_4cf9e2;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4cf9e2:
    {
        uint32_t v = lift_load(&env, esp, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf910u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf650u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cfc90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CFC90_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CFC90_STACK, 4, entry);
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
    esi = lift_load(&env, esp, 0x10u, 4);
    edx = 0x4ccc40u;
    eax = 0x5c5c28u;
    eax = lift_call(&env, 0x4dc030u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cfcfb;
    {
        (void)lift_sub(32, esi, 0x135u, &fl);
    }
    if (fl.zf)
        goto L_4cfcd5;
    {
        (void)lift_sub(32, esi, 0x136u, &fl);
    }
    if (fl.zf)
        goto L_4cfcd5;
    {
        (void)lift_sub(32, esi, 0x138u, &fl);
    }
    if (fl.zf)
        goto L_4cfcd5;
    {
        (void)lift_sub(32, esi, 0x137u, &fl);
    }
    if (fl.zf)
        goto L_4cfcd5;
    {
        (void)lift_sub(32, esi, 0x134u, &fl);
    }
    if (!fl.zf)
        goto L_4cfcfb;
L_4cfcd5:
    {
        uint32_t v = lift_load(&env, ebx, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esi + 0xfffffeceu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x24u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x24u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d2540u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cfcfb;
    eax = lift_load(&env, ebx, 0x4u, 4);
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
    return env.failed ? 0u : eax;
L_4cfcfb:
    {
        uint32_t v = lift_load(&env, esp, 0x18u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x18u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x18u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cfa20u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cfe40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CFE40_STACK + 4 + 4 * 3 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CFE40_STACK, 3, entry);
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
    eax = lift_call(&env, 0x4ce220u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0xcu, 4), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4cfe6b;
    {
        uint32_t v = lift_load(&env, esp, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x30u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f18ecu, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
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
    return env.failed ? 0u : eax;
L_4cfe6b:
    esi = lift_load(&env, esp, 0x14u, 4);
    esi = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x14u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cfe88;
    {
        (void)lift_and(8, lift_load(&env, esi, 0x23u, 1), 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_4cfedc;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x14u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cfedc;
L_4cfe88:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x28u, 4), 0x8002u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
    lift_store(&env, ebx, 0x28u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c79c8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cfeac;
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cfd20u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    goto L_4cfedc;
L_4cfeac:
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, ebx, 0x24u, 4, eax);
    eax = lift_call(&env, 0x4f1ba0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x4cff20u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ae0u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    lift_store(&env, ebx, 0x2cu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cfedc;
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
L_4cfedc:
    {
        uint32_t v = lift_load(&env, esp, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x30u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f18ecu, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    esi = eax;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x14u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cff10;
    {
        uint32_t v = lift_load(&env, ebx, 0x30u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b08u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, ebx, 0x30u, 4, 0x0u);
L_4cff10:
    eax = esi;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cff80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CFF80_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CFF80_STACK, 1, entry);
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
    eax = lift_call(&env, 0x4ce220u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    esi = eax;
    eax = lift_load(&env, eax, 0x14u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0xcu, 4), &fl);
    }
    if (fl.zf)
        goto L_4cffc5;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x30u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cffbe;
    eax = lift_call(&env, 0x4f1ba0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x4cfe40u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ae0u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    lift_store(&env, ebx, 0x30u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cffbe;
    eax = lift_call(&env, 0x4d9510u, eax, edx, ebx, ecx, 0, esp);
L_4cffbe:
    eax = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, esi, 0x14u, 4, eax);
L_4cffc5:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4cffd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CFFD0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CFFD0_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4ce220u, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
    ebx = eax;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x14u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cfffd;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x30u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cfffd;
    {
        uint32_t v = lift_load(&env, esi, 0x30u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b08u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, esi, 0x30u, 4, 0x0u);
L_4cfffd:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x2cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d0014;
    {
        uint32_t v = lift_load(&env, ebx, 0x2cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b08u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, ebx, 0x2cu, 4, 0x0u);
L_4d0014:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x14u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d0026;
    lift_store(&env, ebx, 0x14u, 4, 0x0u);
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
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4d0026:
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d04f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D04F0_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D04F0_STACK, 1, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4ce220u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    eax = lift_load(&env, eax, 0xd0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d051a;
    eax = lift_load(&env, eax, 0x1cu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d051a;
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
        uint32_t v = 0x401u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
L_4d051a:
    ebx = lift_load(&env, ebx, 0x108u, 4);
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d0548;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4d0548;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1998u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4d0548;
    ecx = lift_load(&env, ebx, 0x0u, 4);
    edx = 0xffffffffu;
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, ecx, 0xe0u, 4), eax, edx, ebx, ecx, 0, esp);
L_4d0548:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d16b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D16B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D16B0_STACK, 0, entry);
    eax = lift_call(&env, 0x4cba70u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, eax, 0x24u, 4, 0x519724u);
    lift_store(&env, eax, 0x28u, 4, 0x1u);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d1840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D1840_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D1840_STACK, 0, entry);
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
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d188a;
    eax = lift_load(&env, eax, 0x1cu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d188a;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19c8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d188a;
L_4d1861:
    ecx = lift_load(&env, edx, 0x0u, 4);
    eax = edx;
    eax = lift_call(&env, lift_load(&env, ecx, 0xb4u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d1874;
    eax = edx;
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
    return env.failed ? 0u : eax;
L_4d1874:
    {
        uint32_t v = lift_load(&env, edx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19c8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d1861;
L_4d188a:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d1890(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D1890_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D1890_STACK, 1, entry);
    {
        uint32_t v = lift_load(&env, esp, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf910u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d18c5;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x20u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d18a8;
    {
        uint32_t v = lift_load(&env, eax, 0x20u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    goto L_4d18b3;
L_4d18a8:
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19c8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4d18b3:
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d18bf;
    return env.failed ? 0u : eax;
L_4d18bf:
    eax = lift_load(&env, eax, 0x1cu, 4);
    return env.failed ? 0u : eax;
L_4d18c5:
    {
        uint32_t v = 0xfffffff0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19f0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_and(32, eax, 0x40000000u, &fl);
    }
    if (fl.zf)
        goto L_4d18e7;
    {
        uint32_t v = lift_load(&env, esp, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19c8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    return env.failed ? 0u : eax;
L_4d18e7:
    {
        uint32_t v = 0x4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a04u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d1900(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D1900_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D1900_STACK, 0, entry);
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
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d190e;
    ebx = lift_load(&env, eax, 0x1cu, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4d1914;
L_4d190e:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4d1914:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d1890u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d1922;
    ebx = eax;
    goto L_4d1914;
L_4d1922:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d1930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D1930_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D1930_STACK, 0, entry);
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
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d1940;
    eax = lift_load(&env, eax, 0x1cu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d1946;
L_4d1940:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4d1946:
    ebx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    edx = ecx;
    eax = lift_call(&env, lift_load(&env, ebx, 0xb4u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d195f;
    eax = ecx;
    eax = lift_call(&env, 0x4d1840u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
L_4d195f:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4d1972;
L_4d1963:
    eax = edx;
    eax = lift_call(&env, 0x4d1840u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d1972;
    edx = eax;
    goto L_4d1963;
L_4d1972:
    eax = edx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d2020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D2020_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D2020_STACK, 1, entry);
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
        uint32_t r = lift_sub(32, esp, 0x14u, &fl);
        esp = r;
    }
    edi = lift_load(&env, esp, 0x20u, 4);
    esi = eax;
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x39u, &fl);
    }
    if (fl.cf)
        goto L_4d2127;
    if (fl.cf || fl.zf)
        goto L_4d2056;
    {
        (void)lift_sub(32, edx, 0x114u, &fl);
    }
    if (fl.cf)
        goto L_4d2112;
    if (fl.cf || fl.zf)
        goto L_4d2056;
    {
        (void)lift_sub(32, edx, 0x115u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d2056;
    {
        (void)lift_sub(32, edx, 0x210u, &fl);
    }
    if (!fl.zf)
        goto L_4d20cf;
L_4d2056:
    edx = (eax + 0xbc00u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    eax = lift_call(&env, 0x4d0c84u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    goto L_4d2163;
L_4d2069:
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_and(32, ebx, 0xffffu, &fl);
        ebx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebx & 0xffffu);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    ebx = (eax & 0xffffu);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_or(32, ebx, 0xbd110000u, &fl);
        ebx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4cb820u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d2161;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4d209d;
    lift_store(&env, edi, 0x0u, 4, 0x1u);
L_4d209d:
    eax = 0x1u;
    goto L_4d2163;
L_4d20a7:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    ebx = lift_load(&env, ecx, 0x8u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x14u, 4, ecx);
    ebx = (ebx & 0xffffu);
    ecx = (esp + 0x10u);
    {
        uint32_t r = lift_or(32, ebx, 0xbc4e0000u, &fl);
        ebx = r;
    }
    lift_store(&env, esp, 0x10u, 4, edi);
    eax = lift_call(&env, 0x4cb820u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    goto L_4d2163;
L_4d20cf:
    {
        (void)lift_sub(32, eax, 0x132u, &fl);
    }
    if (fl.cf)
        goto L_4d2161;
    {
        (void)lift_sub(32, eax, 0x138u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4d2161;
    ecx = esp;
    edx = 0xbc19u;
    lift_store(&env, esp, 0x4u, 4, ebx);
    {
        uint32_t r = lift_sub(32, eax, 0x132u, &fl);
        eax = r;
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esp, 0xcu, 4, eax);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4d0c84u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4d2163;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
    return env.failed ? 0u : eax;
L_4d2112:
    {
        (void)lift_sub(32, edx, 0x4eu, &fl);
    }
    if (fl.cf)
        goto L_4d20cf;
    if (fl.cf || fl.zf)
        goto L_4d20a7;
    {
        (void)lift_sub(32, edx, 0x111u, &fl);
    }
    if (fl.zf)
        goto L_4d2069;
    goto L_4d20cf;
L_4d2127:
    {
        (void)lift_sub(32, edx, 0x2du, &fl);
    }
    if (fl.cf)
        goto L_4d2146;
    if (fl.cf || fl.zf)
        goto L_4d2056;
    {
        (void)lift_sub(32, edx, 0x2eu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d2056;
    {
        (void)lift_sub(32, edx, 0x2fu, &fl);
    }
    if (fl.zf)
        goto L_4d2056;
    goto L_4d20cf;
L_4d2146:
    {
        (void)lift_sub(32, edx, 0x2bu, &fl);
    }
    if (fl.cf)
        goto L_4d20cf;
    edx = (eax + 0xbc00u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    eax = lift_call(&env, 0x4d0c84u, eax, edx, ebx, ecx, 5, esp);
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
    return env.failed ? 0u : eax;
L_4d2161:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4d2163:
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d2170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D2170_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D2170_STACK, 0, entry);
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
    eax = (edx & 0xffffu);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4d2181;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4d218d;
L_4d2181:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d1e80u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d2194;
L_4d218d:
    eax = esi;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
L_4d2194:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d21a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D21A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D21A0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (edx & 0xffffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d21bd;
    eax = lift_call(&env, 0x4ce220u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(8, lift_load(&env, eax, 0xe3u, 1), 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_4d21bd;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d04f0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4d21bd:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d21d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D21D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D21D0_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = 0x4ccc40u;
    ecx = lift_load(&env, eax, 0x4u, 4);
    eax = 0x5c5c28u;
    eax = lift_call(&env, 0x4dc030u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, ebx, lift_load(&env, ecx, 0x1cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d21fb;
    eax = 0x5c7944u;
    eax = lift_call(&env, 0x4de810u, eax, edx, ebx, ecx, 0, esp);
L_4d21fb:
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x14u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4d2233;
    eax = lift_call(&env, 0x4cbe80u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d2233;
    eax = lift_call(&env, 0x4cbe80u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x1cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d2233;
    edx = 0x4cc760u;
    eax = 0x5c7b84u;
    eax = lift_call(&env, 0x4dc030u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x1cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d2233;
    eax = lift_call(&env, lift_load(&env, ecx, 0x1cu, 4), eax, edx, ebx, ecx, 0, esp);
L_4d2233:
    eax = ebx;
    eax = lift_call(&env, 0x4cccc0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, 0x40000000u, &fl);
    }
    if (!fl.zf)
        goto L_4d2253;
    {
        uint32_t v = 0x1u;
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
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x15u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d1ae0u, eax, edx, ebx, ecx, 6, esp);
    esp += 24u;
L_4d2253:
    eax = ebx;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d2260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D2260_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D2260_STACK, 0, entry);
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
    esi = eax;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x14u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4d22a0;
    edx = 0x4cc760u;
    eax = 0x5c7b84u;
    eax = lift_call(&env, 0x4dc030u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    edi = eax;
    eax = lift_call(&env, 0x4cbe80u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d22a0;
    eax = lift_call(&env, 0x4cbe80u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, esi, lift_load(&env, eax, 0x1cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d22a0;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x24u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d22a0;
    eax = lift_call(&env, lift_load(&env, edi, 0x24u, 4), eax, edx, ebx, ecx, 0, esp);
L_4d22a0:
    eax = esi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4d2390u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d22b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D22B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D22B0_STACK, 0, entry);
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
    ebx = eax;
    esi = edx;
    eax = lift_call(&env, 0x4cbe80u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d22d9;
    eax = lift_call(&env, 0x4cbe80u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x1cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d22d9;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = esi;
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = lift_call(&env, 0x4cb230u, eax, edx, ebx, ecx, 0, esp);
L_4d22d9:
    eax = ebx;
    eax = lift_call(&env, 0x4cccc0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, 0x40000000u, &fl);
    }
    if (!fl.zf)
        goto L_4d2304;
    eax = lift_call(&env, 0x4cf800u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x8u, 4);
    eax = lift_load(&env, eax, 0xcu, 4);
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
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d1ae0u, eax, edx, ebx, ecx, 6, esp);
    esp += 24u;
L_4d2304:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d2310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D2310_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D2310_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_call(&env, 0x4cccc0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, 0x40000000u, &fl);
    }
    if (!fl.zf)
        goto L_4d2383;
    eax = lift_call(&env, 0x4cbe80u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d2383;
    eax = lift_call(&env, 0x4cbe80u, eax, edx, ebx, ecx, 0, esp);
    esi = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, esi, 0x78u, 4), eax, edx, ebx, ecx, 0, esp);
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d2383;
    {
        uint32_t v = 0x10u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1998u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4d2383;
    {
        uint32_t v = 0x11u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1998u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4d2383;
    {
        uint32_t v = 0x12u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1998u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4d2383;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xe146u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x111u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
L_4d2383:
    eax = ebx;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d2390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D2390_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D2390_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    esi = eax;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_sub(32, esi, lift_load(&env, eax, 0x1cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d23ae;
    eax = 0x5c7944u;
    eax = lift_call(&env, 0x4de900u, eax, edx, ebx, ecx, 0, esp);
L_4d23ae:
    eax = esi;
    eax = lift_call(&env, 0x4cccc0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, 0x40000000u, &fl);
    }
    if (!fl.zf)
        goto L_4d23e0;
    eax = lift_call(&env, 0x4cf800u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esp, 0x8u, 4, edx);
    edx = lift_load(&env, eax, 0x8u, 4);
    eax = lift_load(&env, eax, 0xcu, 4);
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
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d1ae0u, eax, edx, ebx, ecx, 6, esp);
    esp += 24u;
L_4d23e0:
    eax = esi;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 1, esp);
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d2420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D2420_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D2420_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = eax;
    eax = ecx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4d2434;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4d1e50u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d243b;
L_4d2434:
    eax = esi;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
L_4d243b:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d2440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D2440_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D2440_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = eax;
    eax = ecx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4d2454;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4d1e50u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d245b;
L_4d2454:
    eax = esi;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
L_4d245b:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d28c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D28C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D28C0_STACK, 0, entry);
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
    ebx = eax;
    esi = edx;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4d2900;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = 0xf0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = lift_load(&env, eax, 0xcu, 4);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b68u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d2900;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c48u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d2909;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c60u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edi = eax;
L_4d2900:
    edx = edi;
    eax = ebx;
    eax = lift_call(&env, 0x4d2910u, eax, edx, ebx, ecx, 0, esp);
L_4d2909:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d2a00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D2A00_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D2A00_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0xcu, &fl);
        esp = r;
    }
    ebx = eax;
    lift_store(&env, esp, 0x4u, 4, edx);
    lift_store(&env, esp, 0x8u, 4, 0x1u);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    {
        (void)lift_and(8, lift_load(&env, esp, 0x4u, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4d2a32;
    eax = lift_call(&env, 0x4cccc0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, 0x10000000u, &fl);
    }
    if (!fl.zf)
        goto L_4d2a32;
    ebp = 0x1u;
    goto L_4d2a34;
L_4d2a32:
    {
        uint32_t r = lift_xor(32, ebp, ebp, &fl);
        ebp = r;
    }
L_4d2a34:
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19c8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, esp, 0x0u, 4, eax);
    {
        uint32_t r = lift_or(8, lift_load(&env, ebx, 0x24u, 1), 0x18u, &fl);
        lift_store(&env, ebx, 0x24u, 1, r);
    }
    eax = lift_call(&env, 0x4cbe80u, eax, edx, ebx, ecx, 0, esp);
    esi = (eax + 0x30u);
L_4d2a4d:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d2adb;
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
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a5cu, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d2adb;
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4d2a8c;
    edx = 0x1u;
    eax = ebx;
    eax = lift_call(&env, 0x4ccdd0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebp, ebp, &fl);
        ebp = r;
    }
    eax = lift_call(&env, 0x4f1b14u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4d2a8c:
    {
        (void)lift_and(8, lift_load(&env, esp, 0x4u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4d2ab1;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d2ab1;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4d2ab1;
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x121u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0xcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
L_4d2ab1:
    {
        (void)lift_and(8, lift_load(&env, esp, 0x4u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4d2ad3;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x36au;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d2a4d;
L_4d2ad3:
    lift_store(&env, esp, 0x8u, 4, 0x0u);
L_4d2adb:
    eax = lift_call(&env, 0x4cbe80u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x60u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d2af9;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cb080u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = 0xffffffffu;
    goto L_4d2b70;
L_4d2af9:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4d2b27;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x4u, 4), 0x118u, &fl);
    }
    if (fl.zf)
        goto L_4d2b0f;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x4u, 4), 0x104u, &fl);
    }
    if (!fl.zf)
        goto L_4d2b27;
L_4d2b0f:
    edx = 0x1u;
    eax = ebx;
    eax = lift_call(&env, 0x4ccdd0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebp, ebp, &fl);
        ebp = r;
    }
    eax = lift_call(&env, 0x4f1b14u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4d2b27:
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, edx, 0x74u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d2b69;
    eax = lift_call(&env, 0x4cbe80u, eax, edx, ebx, ecx, 0, esp);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = esi;
    eax = lift_call(&env, lift_load(&env, ecx, 0x68u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d2b4c;
    lift_store(&env, esp, 0x8u, 4, 0x1u);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
L_4d2b4c:
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
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a5cu, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d2adb;
    goto L_4d2a4d;
L_4d2b69:
    eax = lift_load(&env, ebx, 0x2cu, 4);
    {
        uint32_t r = lift_and(8, lift_load(&env, ebx, 0x24u, 1), 0xe7u, &fl);
        lift_store(&env, ebx, 0x24u, 1, r);
    }
L_4d2b70:
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d3010(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D3010_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D3010_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4d3120u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d3020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D3020_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D3020_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4d3034;
    edx = eax;
    eax = ecx;
    eax = lift_call(&env, 0x4d3010u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d3036;
L_4d3034:
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
L_4d3036:
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d30f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D30F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D30F0_STACK, 0, entry);
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
    ebx = eax;
    esi = edx;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = eax;
    eax = lift_call(&env, 0x4de9c0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = (edi + 0x1cu);
    edx = esi;
    eax = lift_call(&env, 0x4dba10u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dea40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d3120(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D3120_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D3120_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d3139;
L_4d3127:
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_4d3132;
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
L_4d3132:
    eax = lift_load(&env, eax, 0x10u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d3127;
L_4d3139:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d3f70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D3F70_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D3F70_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x30u, &fl);
        esp = r;
    }
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4d3fa5;
    lift_store(&env, esp, 0x20u, 4, 0x1u);
    edx = 0x5199f0u;
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    goto L_4d4037;
L_4d3fa5:
    lift_store(&env, eax, 0x0u, 4, 0x5198f4u);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
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
    lift_store(&env, esp, 0x1cu, 4, 0x5197fcu);
    eax = ecx;
    lift_store(&env, esp, 0x20u, 4, 0x5u);
    eax = lift_call(&env, 0x4d4060u, eax, edx, ebx, ecx, 0, esp);
    eax = (ecx + 0xacu);
    lift_store(&env, esp, 0x20u, 4, 0x4u);
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_sub(32, eax, 0x40u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x20u, 4, 0x3u);
    eax = lift_call(&env, 0x4d83f0u, eax, edx, ebx, ecx, 0, esp);
    edx = 0x1u;
    {
        uint32_t r = lift_sub(32, eax, 0x6cu, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    eax = lift_call(&env, 0x4d01a0u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4d402d;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
L_4d402d:
    eax = lift_load(&env, esp, 0x14u, 4);
    env.chain = eax;
L_4d4037:
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x30u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d4040(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D4040_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D4040_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_call(&env, 0x4ce780u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, eax, 0x8u, &fl);
        eax = r;
    }
    edx = ebx;
    eax = lift_call(&env, 0x4dba10u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d4060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D4060_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D4060_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_call(&env, 0x4ce780u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, eax, 0x8u, &fl);
        eax = r;
    }
    edx = ebx;
    eax = lift_call(&env, 0x4dba20u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d4080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D4080_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D4080_STACK, 0, entry);
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
    ebx = eax;
    esi = edx;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, eax, 0xcu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a30u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    lift_store(&env, ebx, 0x48u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d41a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D41A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D41A0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x68u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d41b6;
    eax = lift_load(&env, ecx, 0x68u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, ecx, 0x70u, 4), eax, edx, ebx, ecx, 0, esp);
L_4d41b6:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d41c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D41C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D41C0_STACK, 0, entry);
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
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x68u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d41de;
    eax = lift_load(&env, eax, 0x68u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, ecx, 0x74u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d41de;
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
L_4d41de:
    eax = edx;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d4270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D4270_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D4270_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = eax;
    eax = lift_call(&env, 0x4d1930u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x50u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d4292;
    {
        uint32_t v = lift_load(&env, 0u, 0x5c79a4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a9cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
L_4d4292:
    eax = esi;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d42a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D42A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D42A0_STACK, 0, entry);
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
    ecx = eax;
    esi = ebx;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4d42cd;
    eax = lift_call(&env, 0x4d2d70u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d42c1;
    esi = lift_load(&env, ecx, 0x90u, 4);
    {
        uint32_t r = lift_add(32, esi, 0x10000u, &fl);
        esi = r;
    }
    goto L_4d42cd;
L_4d42c1:
    esi = lift_load(&env, ecx, 0x8cu, 4);
    {
        uint32_t r = lift_add(32, esi, 0x20000u, &fl);
        esi = r;
    }
L_4d42cd:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4d42f0;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x4u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    ebx = 0x1u;
    edx = esi;
    eax = lift_call(&env, lift_load(&env, ecx, 0x9cu, 4), eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
L_4d42f0:
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
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d4390(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D4390_STACK + 4 + 4 * 2 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D4390_STACK, 2, entry);
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
    return env.failed ? 0u : eax;
L_4d43a6:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d1890u, eax, edx, ebx, ecx, 1, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d4630(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D4630_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D4630_STACK, 0, entry);
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
    ebx = eax;
    esi = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4d4655;
    {
        (void)lift_and(8, lift_load(&env, eax, 0x24u, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4d4655;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4cce30u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1aa8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
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
    return env.failed ? 0u : eax;
L_4d4655:
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19c8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d46f0;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4d468a;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0xa0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4d468a;
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    {
        uint32_t r = lift_or(8, lift_load(&env, ebx, 0x24u, 1), 0x80u, &fl);
        lift_store(&env, ebx, 0x24u, 1, r);
    }
    eax = lift_call(&env, lift_load(&env, edx, 0x8cu, 4), eax, edx, ebx, ecx, 0, esp);
    goto L_4d46bc;
L_4d468a:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4d46bc;
    {
        (void)lift_and(8, lift_load(&env, ebx, 0x24u, 1), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4d46bc;
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    {
        uint32_t r = lift_and(8, lift_load(&env, ebx, 0x24u, 1), 0x7fu, &fl);
        lift_store(&env, ebx, 0x24u, 1, r);
    }
    eax = lift_call(&env, lift_load(&env, edx, 0x90u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4f195cu, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebx, 0x1cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d46bc;
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
        uint32_t v = 0x6u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
L_4d46bc:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4d46d9;
    {
        (void)lift_and(8, lift_load(&env, ebx, 0x24u, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4d46d9;
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
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
L_4d46d9:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4d46e4;
    edx = 0x10u;
    goto L_4d46e9;
L_4d46e4:
    edx = 0x20u;
L_4d46e9:
    eax = ebx;
    eax = lift_call(&env, 0x4d4700u, eax, edx, ebx, ecx, 0, esp);
L_4d46f0:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d49a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D49A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D49A0_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4d49eb;
    ecx = lift_load(&env, esi, 0x0u, 4);
    eax = esi;
    eax = lift_call(&env, lift_load(&env, ecx, 0xe0u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d49c4;
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4d49c4:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xe001u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x362u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a60u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    ebx = lift_load(&env, esi, 0x0u, 4);
    edx = 0x1u;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, ebx, 0xccu, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4d49eb:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d4d10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D4D10_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D4D10_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_call(&env, 0x4d5930u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x44u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d4d3c;
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19b0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_sub(32, eax, lift_load(&env, ebx, 0x44u, 4), &fl);
    }
    if (fl.zf)
        goto L_4d4d3c;
    {
        uint32_t v = lift_load(&env, ebx, 0x44u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ab4u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
L_4d4d3c:
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x1cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d4d59;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b1cu, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
L_4d4d59:
    eax = ebx;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d4e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D4E00_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D4E00_STACK, 0, entry);
    eax = lift_call(&env, 0x4d5350u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d4e27;
    eax = lift_call(&env, 0x4cf800u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, eax, 0x8u, 4);
    eax = lift_load(&env, eax, 0xcu, 4);
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
        uint32_t v = 0x114u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
L_4d4e27:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d4e30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D4E30_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D4E30_STACK, 0, entry);
    eax = lift_call(&env, 0x4d5350u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d4e57;
    eax = lift_call(&env, 0x4cf800u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, eax, 0x8u, 4);
    eax = lift_load(&env, eax, 0xcu, 4);
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
        uint32_t v = 0x115u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
L_4d4e57:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d4e60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D4E60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D4E60_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4d21a0u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, esi, 0x0u, 4);
    eax = esi;
    eax = lift_call(&env, lift_load(&env, edx, 0xf4u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x68u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d4ea1;
    eax = lift_load(&env, esi, 0x68u, 4);
    edx = (ecx & 0xffffu);
    ebx = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4d4e9c;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_and(32, ecx, 0xffffu, &fl);
        ecx = r;
    }
    {
        (void)lift_and(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4d4e9c;
    edx = 0x1u;
    goto L_4d4e9e;
L_4d4e9c:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
L_4d4e9e:
    eax = lift_call(&env, lift_load(&env, ebx, 0x5cu, 4), eax, edx, ebx, ecx, 0, esp);
L_4d4ea1:
    eax = lift_call(&env, 0x4cbe80u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, esi, lift_load(&env, eax, 0x1cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d4ed7;
    eax = esi;
    eax = lift_call(&env, 0x4d5350u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d4ec5;
    edx = lift_load(&env, esi, 0x0u, 4);
    eax = esi;
    eax = lift_call(&env, lift_load(&env, edx, 0xc4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4d5350u, eax, edx, ebx, ecx, 0, esp);
L_4d4ec5:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d4ed7;
    ecx = eax;
    esi = lift_load(&env, eax, 0x0u, 4);
    ebx = eax;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, lift_load(&env, esi, 0xe8u, 4), eax, edx, ebx, ecx, 0, esp);
L_4d4ed7:
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
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d4fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D4FD0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D4FD0_STACK, 0, entry);
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
    esi = eax;
    {
        (void)lift_and(8, lift_load(&env, eax, 0x24u, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4d4fe1;
    edx = 0x1u;
L_4d4fe1:
    eax = esi;
    eax = lift_call(&env, 0x4cce00u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d4fee;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
L_4d4fee:
    ebx = edx;
    eax = esi;
    edi = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    edx = 0x86u;
    eax = lift_call(&env, lift_load(&env, edi, 0xa4u, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d5010(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D5010_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D5010_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4d1930u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    eax = ecx;
    {
        uint32_t r = lift_and(32, eax, 0xfff0u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, lift_load(&env, edx, 0x50u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4d506e;
    goto L_4d50bb;
L_4d502f:
    {
        uint32_t r = lift_sub(32, eax, 0xf000u, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x1ef00u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x365u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d50c2;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xe147u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x111u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
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
    return env.failed ? 0u : eax;
L_4d506e:
    {
        (void)lift_sub(32, eax, 0xf040u, &fl);
    }
    if (fl.cf)
        goto L_4d5097;
    if (fl.cf || fl.zf)
        goto L_4d502f;
    {
        (void)lift_sub(32, eax, 0xf060u, &fl);
    }
    if (fl.cf)
        goto L_4d5090;
    if (fl.cf || fl.zf)
        goto L_4d502f;
    {
        (void)lift_sub(32, eax, 0xf120u, &fl);
    }
    if (fl.cf)
        goto L_4d50bb;
    if (fl.cf || fl.zf)
        goto L_4d502f;
    {
        (void)lift_sub(32, eax, 0xf130u, &fl);
    }
    goto L_4d50b5;
L_4d5090:
    {
        (void)lift_sub(32, eax, 0xf050u, &fl);
    }
    goto L_4d50b5;
L_4d5097:
    {
        (void)lift_sub(32, eax, 0xf010u, &fl);
    }
    if (fl.cf)
        goto L_4d50b0;
    if (fl.cf || fl.zf)
        goto L_4d502f;
    {
        (void)lift_sub(32, eax, 0xf020u, &fl);
    }
    if (fl.cf)
        goto L_4d50bb;
    if (fl.cf || fl.zf)
        goto L_4d502f;
    {
        (void)lift_sub(32, eax, 0xf030u, &fl);
    }
    goto L_4d50b5;
L_4d50b0:
    {
        (void)lift_sub(32, eax, 0xf000u, &fl);
    }
L_4d50b5:
    if (fl.zf)
        goto L_4d502f;
L_4d50bb:
    eax = esi;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
L_4d50c2:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d5150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D5150_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D5150_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x1cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d516e;
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x8cu, 4), eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
L_4d516e:
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d5180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D5180_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D5180_STACK, 0, entry);
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
    edi = eax;
    esi = edx;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    ebx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4d51b3;
    {
        (void)lift_sub(32, edi, lift_load(&env, ebx, 0x1cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d51b3;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dd170u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edx = 0x1u;
    eax = ebx;
    eax = lift_call(&env, 0x4ccad0u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, edx, 0x6cu, 4), eax, edx, ebx, ecx, 0, esp);
L_4d51b3:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d51c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D51C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D51C0_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x104u, &fl);
        esp = r;
    }
    edi = eax;
    ebp = edx;
    esi = ebx;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    ebx = lift_load(&env, eax, 0x4u, 4);
    eax = (esi & 0xffffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d5270;
    eax = esi;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_and(32, eax, 0xffffu, &fl);
        eax = r;
    }
    edx = (eax & 0xffffu);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4d5270;
    {
        (void)lift_sub(16, (esi & 0xffffu), lift_load(&env, ebx, 0xa8u, 2), &fl);
    }
    if (!fl.zf)
        goto L_4d5270;
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, ebx, 0xaau, 2), &fl);
    }
    if (!fl.zf)
        goto L_4d5270;
    {
        uint32_t v = 0x103u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esi & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c1cu, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    eax = esp;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c08u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = 0x103u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebx, 0xaau, 2);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c1cu, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    eax = esp;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c08u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = lift_load(&env, ebx, 0xaau, 2);
    edx = lift_load(&env, ebx, 0xa8u, 2);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_or(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, edi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x3e4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
L_4d5270:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, esp, 0x104u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d54c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D54C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D54C0_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x2cu, &fl);
        esp = r;
    }
    edi = eax;
    esi = edx;
    ebx = ecx;
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dc420u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4d564a;
    eax = esp;
    eax = lift_call(&env, 0x4cba70u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x8u, 4, esi);
    eax = lift_call(&env, 0x4ce220u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x58u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, esi, 0x4u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d54fa;
    lift_store(&env, esp, 0x20u, 4, esi);
    goto L_4d5554;
L_4d54fa:
    {
        uint32_t v = lift_load(&env, edi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19b0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d5554;
    eax = edi;
    eax = lift_call(&env, 0x4d1900u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d5554;
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19b0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ebp = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d5554;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19a4u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, esp, 0x28u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4d553c;
    goto L_4d5554;
L_4d5535:
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    {
        (void)lift_sub(32, ebx, lift_load(&env, esp, 0x28u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4d5554;
L_4d553c:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19dcu, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_sub(32, eax, lift_load(&env, esi, 0x4u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d5535;
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4e1210u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, esp, 0x20u, 4, eax);
L_4d5554:
    {
        uint32_t v = lift_load(&env, esi, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19a4u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, esp, 0x4u, 4, 0x0u);
    lift_store(&env, esp, 0x1cu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4d5585;
    goto L_4d564a;
L_4d5573:
    {
        uint32_t a = lift_load(&env, esp, 0x4u, 4);
        uint32_t r = lift_inc(32, a, &fl, 1);
        lift_store(&env, esp, 0x4u, 4, r);
    }
    eax = lift_load(&env, esp, 0x4u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x1cu, 4), &fl);
    }
    if (!fl.cf)
        goto L_4d564a;
L_4d5585:
    {
        uint32_t v = lift_load(&env, esp, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19a8u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    lift_store(&env, esp, 0x0u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d5573;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4d55db;
    {
        uint32_t v = lift_load(&env, esp, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19dcu, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4e1210u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, esp, 0xcu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d5573;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19a8u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    lift_store(&env, esp, 0x0u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d5573;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4d5573;
    eax = esp;
    edx = edi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    goto L_4d55fd;
L_4d55db:
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x3cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d55f7;
    {
        (void)lift_sub(32, eax, 0xf000u, &fl);
    }
    if (!fl.cf)
        goto L_4d55f7;
    ebx = 0x1u;
    goto L_4d55f9;
L_4d55f7:
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
L_4d55f9:
    eax = esp;
    edx = edi;
L_4d55fd:
    eax = lift_call(&env, 0x4cbc90u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esi, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19a4u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ebx = eax;
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x1cu, 4), &fl);
    }
    if (!fl.cf)
        goto L_4d5641;
    edx = lift_load(&env, esp, 0x1cu, 4);
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, lift_load(&env, esp, 0x4u, 4), edx, &fl);
        lift_store(&env, esp, 0x4u, 4, r);
    }
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x4u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d5641;
L_4d5624:
    {
        uint32_t v = lift_load(&env, esp, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19a8u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4d5641;
    {
        uint32_t a = lift_load(&env, esp, 0x4u, 4);
        uint32_t r = lift_inc(32, a, &fl, 1);
        lift_store(&env, esp, 0x4u, 4, r);
    }
    {
        (void)lift_sub(32, ebx, lift_load(&env, esp, 0x4u, 4), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4d5624;
L_4d5641:
    lift_store(&env, esp, 0x1cu, 4, ebx);
    goto L_4d5573;
L_4d564a:
    {
        uint32_t r = lift_add(32, esp, 0x2cu, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d5660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D5660_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D5660_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = eax;
    eax = lift_call(&env, 0x4d1930u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    {
        (void)lift_sub(32, ebx, 0xffffu, &fl);
    }
    if (!fl.zf)
        goto L_4d56bb;
    {
        uint32_t r = lift_and(8, lift_load(&env, esi, 0x24u, 1), 0xbfu, &fl);
        lift_store(&env, esi, 0x24u, 1, r);
    }
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x50u, 4), 0x0u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, 0xe001u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x362u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x90u, 4, eax);
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    edx = lift_load(&env, esi, 0x0u, 4);
    eax = esi;
    eax = lift_call(&env, lift_load(&env, edx, 0xd8u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d5716;
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b14u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    goto L_4d5716;
L_4d56bb:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4d56c6;
    {
        (void)lift_and(16, (ebx & 0xffffu), 0x810u, &fl);
    }
    if (fl.zf)
        goto L_4d56d2;
L_4d56c6:
    lift_store(&env, esi, 0x90u, 4, 0x0u);
    goto L_4d5712;
L_4d56d2:
    {
        (void)lift_sub(32, edx, 0xf000u, &fl);
    }
    if (fl.cf)
        goto L_4d56f8;
    {
        (void)lift_sub(32, edx, 0xf1f0u, &fl);
    }
    if (!fl.cf)
        goto L_4d56f8;
    eax = (edx + 0xffff1000u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0xef00u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x90u, 4, eax);
    goto L_4d5712;
L_4d56f8:
    {
        (void)lift_sub(32, edx, 0xff00u, &fl);
    }
    if (fl.cf)
        goto L_4d570c;
    lift_store(&env, esi, 0x90u, 4, 0xef1fu);
    goto L_4d5712;
L_4d570c:
    lift_store(&env, esi, 0x90u, 4, edx);
L_4d5712:
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0x24u, 1), 0x40u, &fl);
        lift_store(&env, ecx, 0x24u, 1, r);
    }
L_4d5716:
    eax = lift_load(&env, esi, 0x90u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, esi, 0x94u, 4), &fl);
    }
    if (fl.zf)
        goto L_4d574b;
    {
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19c8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d574b;
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
        uint32_t v = 0x36au;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a60u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
L_4d574b:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d57a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D57A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D57A0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_and(8, lift_load(&env, eax, 0x24u, 1), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4d57ab;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
L_4d57ab:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x362u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d58e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D58E0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D58E0_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    eax = lift_call(&env, 0x4d2460u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, esi, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4d5905;
    edx = lift_load(&env, ecx, 0x90u, 4);
    {
        (void)lift_sub(32, edx, lift_load(&env, ecx, 0x94u, 4), &fl);
    }
    if (fl.zf)
        goto L_4d5905;
    eax = ecx;
    eax = lift_call(&env, 0x4d5910u, eax, edx, ebx, ecx, 0, esp);
L_4d5905:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d5a70(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D5A70_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D5A70_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4d59f0u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d5a9e;
    eax = lift_call(&env, 0x4cccc0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        (void)lift_and(32, eax, 0x10000000u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    ebx = (eax & 0xffu);
    eax = esi;
    eax = lift_call(&env, 0x4d5390u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
L_4d5a9e:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d6080(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D6080_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D6080_STACK, 0, entry);
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
    ebx = eax;
    {
        (void)lift_and(8, lift_load(&env, eax, 0xb8u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4d609c;
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, eax, 0xa8u, 4);
    eax = lift_call(&env, lift_load(&env, ecx, 0xe8u, 4), eax, edx, ebx, ecx, 0, esp);
L_4d609c:
    {
        (void)lift_and(8, lift_load(&env, ebx, 0xb8u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4d60b4;
    ecx = lift_load(&env, ebx, 0x0u, 4);
    edx = 0x1u;
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, ecx, 0xe4u, 4), eax, edx, ebx, ecx, 0, esp);
L_4d60b4:
    {
        (void)lift_and(8, lift_load(&env, ebx, 0xb8u, 1), 0x8u, &fl);
    }
    if (fl.zf)
        goto L_4d60da;
    ecx = lift_load(&env, ebx, 0x0u, 4);
    edx = lift_load(&env, ebx, 0xb8u, 4);
    eax = ebx;
    {
        uint32_t r = lift_and(32, edx, 0x4u, &fl);
        edx = r;
    }
    eax = lift_call(&env, lift_load(&env, ecx, 0xccu, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, ebx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b14u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4d60da:
    edx = lift_load(&env, ebx, 0x90u, 4);
    {
        (void)lift_sub(32, edx, lift_load(&env, ebx, 0x94u, 4), &fl);
    }
    if (fl.zf)
        goto L_4d60ef;
    eax = ebx;
    eax = lift_call(&env, 0x4d5910u, eax, edx, ebx, ecx, 0, esp);
L_4d60ef:
    lift_store(&env, ebx, 0xb8u, 4, 0x0u);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d62e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D62E0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D62E0_STACK, 0, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = eax;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4d62fc;
    ecx = lift_load(&env, esi, 0x0u, 4);
    edx = 0x1u;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, ecx, 0xccu, 4), eax, edx, ebx, ecx, 0, esp);
L_4d62fc:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d6380(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D6380_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D6380_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4d63ab;
    {
        (void)lift_sub(32, edx, 0x6u, &fl);
    }
    if (fl.zf)
        goto L_4d63ab;
    {
        (void)lift_sub(32, edx, 0x7u, &fl);
    }
    if (fl.zf)
        goto L_4d63ab;
    {
        (void)lift_sub(32, edx, 0x8u, &fl);
    }
    if (fl.zf)
        goto L_4d63ab;
    {
        (void)lift_sub(32, edx, 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4d63ab;
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f199cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f18e8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4d63ab:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d63b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D63B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D63B0_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4d1840u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d63c2;
    ecx = lift_load(&env, edx, 0x6cu, 4);
L_4d63c2:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d63d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D63D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D63D0_STACK, 0, entry);
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
    ecx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, ecx, 0xd4u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d63e6;
    eax = lift_load(&env, edx, 0x78u, 4);
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
    return env.failed ? 0u : eax;
L_4d63e6:
    {
        (void)lift_sub(32, lift_load(&env, edx, 0x70u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d63fd;
    eax = lift_load(&env, edx, 0x70u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x78u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d63fd;
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
L_4d63fd:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d66cd(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D66CD_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D66CD_STACK, 0, entry);
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
    ecx = eax;
    eax = lift_load(&env, eax, 0x0u, 1);
    ebx = 0x1u;
    {
        (void)lift_and(32, eax, edx, &fl);
    }
    if (fl.zf)
        goto L_4d66e2;
    eax = ebx;
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
    return env.failed ? 0u : eax;
L_4d66e2:
    eax = 0x50817eu;
    eax = lift_call(&env, 0x4e14b0u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, ecx, 0x0u, 1);
    {
        (void)lift_and(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_4d66f7;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0x0u, 1), (edx & 0xffu), &fl);
        lift_store(&env, ecx, 0x0u, 1, r);
    }
L_4d66f7:
    eax = 0x50817eu;
    eax = lift_call(&env, 0x4e14b7u, eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d6710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D6710_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D6710_STACK, 0, entry);
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
L_4d6713:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = (edx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    {
        (void)lift_and(8, lift_load(&env, edx, 0x507d58u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4d6729;
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    goto L_4d6713;
L_4d6729:
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x2bu, &fl);
    }
    if (fl.zf)
        goto L_4d6735;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4d6736;
L_4d6735:
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
L_4d6736:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
L_4d6738:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = (ebx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, ebx, 0xffu, &fl);
        ebx = r;
    }
    {
        (void)lift_and(8, lift_load(&env, ebx, 0x507d58u, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4d675a;
    {
        uint32_t r = lift_imul(32, edx, 0xau, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_add(32, edx, ebx, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, edx, 0x30u, &fl);
        edx = r;
    }
    goto L_4d6738;
L_4d675a:
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4d6761;
    {
        uint32_t a = edx;
        uint32_t r = lift_sub(32, 0, a, &fl);
        edx = r;
    }
L_4d6761:
    eax = edx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d6768(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D6768_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D6768_STACK, 0, entry);
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.sf)
        goto L_4d6775;
    {
        uint32_t a = eax;
        uint32_t r = lift_sub(32, 0, a, &fl);
        eax = r;
    }
    edx = 0xbffu;
    goto L_4d677a;
L_4d6775:
    edx = 0x3ffu;
L_4d677a:
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4d67a5;
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        fl.zf = a == 0;
        if (a != 0)
        {
            ecx = lift_bsr(a);
        }
    }
    ecx = (ecx & 0xffff00ffu) | ((((ecx & 0xffu)) & 0xffu) << 8);
    ecx = (ecx & 0xffffff00u) | ((0x1fu) & 0xffu);
    {
        uint32_t r = lift_sub(8, (ecx & 0xffu), ((ecx >> 8) & 0xffu), &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
    ecx = ((ecx >> 8) & 0xffu);
    {
        uint32_t r = lift_add(32, ecx, edx, &fl);
        ecx = r;
    }
    edx = eax;
    {
        uint32_t r = lift_and(32, edx, 0xfffff000u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_or(32, edx, ecx, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_ror(32, a, 0xcu, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
L_4d67a5:
    {
        uint32_t r = lift_sub(32, edx, edx, &fl);
        edx = r;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d6775(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D6775_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D6775_STACK, 0, entry);
    edx = 0x3ffu;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4d67a5;
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        fl.zf = a == 0;
        if (a != 0)
        {
            ecx = lift_bsr(a);
        }
    }
    ecx = (ecx & 0xffff00ffu) | ((((ecx & 0xffu)) & 0xffu) << 8);
    ecx = (ecx & 0xffffff00u) | ((0x1fu) & 0xffu);
    {
        uint32_t r = lift_sub(8, (ecx & 0xffu), ((ecx >> 8) & 0xffu), &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
    ecx = ((ecx >> 8) & 0xffu);
    {
        uint32_t r = lift_add(32, ecx, edx, &fl);
        ecx = r;
    }
    edx = eax;
    {
        uint32_t r = lift_and(32, edx, 0xfffff000u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_or(32, edx, ecx, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_ror(32, a, 0xcu, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
L_4d67a5:
    {
        uint32_t r = lift_sub(32, edx, edx, &fl);
        edx = r;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d67a8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D67A8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D67A8_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ecx & 0xffffff00u) | ((0x9eu) & 0xffu);
    eax = lift_call(&env, 0x4d67e4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d67b2(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D67B2_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D67B2_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ecx & 0xffffff00u) | ((0x9fu) & 0xffu);
    eax = lift_call(&env, 0x4d67e4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d6a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D6A30_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D6A30_STACK, 4, entry);
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x110u, &fl);
    }
    if (!fl.zf)
        goto L_4d6a66;
    {
        uint32_t v = lift_load(&env, esp, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf910u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edx = eax;
    eax = 0x503b28u;
    eax = lift_call(&env, 0x4d3020u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d6a5e;
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0xc0u, 4), eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
L_4d6a5e:
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d6a66:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d6f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D6F10_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D6F10_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4cc870u, eax, edx, ebx, ecx, 0, esp);
    eax = (ebx + 0x54u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x50u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d1980u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = eax;
    eax = lift_call(&env, 0x4cff80u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4d6f44;
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
    return env.failed ? 0u : eax;
L_4d6f44:
    eax = lift_load(&env, esi, 0x1cu, 4);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d6f50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D6F50_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D6F50_STACK, 0, entry);
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
    ebx = eax;
    eax = lift_call(&env, 0x4cffd0u, eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
    eax = lift_call(&env, 0x4cf980u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, ebx, 0x54u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1a2cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d6f7b;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x54u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1948u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
L_4d6f7b:
    lift_store(&env, ebx, 0x54u, 4, 0x0u);
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = 0x1u;
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = lift_call(&env, 0x4cc870u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d70e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D70E0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D70E0_STACK, 0, entry);
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
    ecx = eax;
    ebx = edx;
    {
        (void)lift_and(8, lift_load(&env, eax, 0x24u, 1), 0x18u, &fl);
    }
    if (fl.zf)
        goto L_4d70f2;
    esi = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, esi, 0x78u, 4), eax, edx, ebx, ecx, 0, esp);
L_4d70f2:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ecx, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1950u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d7140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D7140_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D7140_STACK, 0, entry);
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
    edi = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edi, 0xd0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4ce760u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d7197;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x58u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d7197;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x4cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d7174;
    edx = esi;
    edi = lift_load(&env, eax, 0x0u, 4);
    ecx = lift_load(&env, esi, 0x58u, 4);
    ebx = lift_load(&env, esi, 0x4cu, 4);
    eax = lift_call(&env, lift_load(&env, edi, 0x18u, 4), eax, edx, ebx, ecx, 0, esp);
    goto L_4d7181;
L_4d7174:
    edx = esi;
    edi = lift_load(&env, eax, 0x0u, 4);
    ecx = lift_load(&env, esi, 0x58u, 4);
    ebx = lift_load(&env, esi, 0x40u, 4);
    eax = lift_call(&env, lift_load(&env, edi, 0x14u, 4), eax, edx, ebx, ecx, 0, esp);
L_4d7181:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d7197;
    edx = 0xffffffffu;
    eax = esi;
    eax = lift_call(&env, 0x4d70e0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4d7197:
    eax = esi;
    eax = lift_call(&env, 0x4cf850u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d71c9;
    {
        (void)lift_and(8, lift_load(&env, esi, 0x25u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4d71c9;
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
        uint32_t v = lift_load(&env, esi, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19c4u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4cf8e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d71c9;
    eax = lift_call(&env, 0x4cce60u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
L_4d71c9:
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d73c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D73C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D73C0_STACK, 0, entry);
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
    esi = ebx;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4d73d7;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x3cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d73d7;
    esi = lift_load(&env, eax, 0x3cu, 4);
    {
        uint32_t r = lift_add(32, esi, 0x20000u, &fl);
        esi = r;
    }
L_4d73d7:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4d73fa;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x4u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    ebx = 0x1u;
    edx = esi;
    eax = lift_call(&env, lift_load(&env, ecx, 0x9cu, 4), eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
L_4d73fa:
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
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d74a6(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D74A6_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D74A6_STACK, 0, entry);
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4d74d0;
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        fl.zf = a == 0;
        if (a != 0)
        {
            ecx = lift_bsr(a);
        }
    }
    ecx = (ecx & 0xffff00ffu) | ((((ecx & 0xffu)) & 0xffu) << 8);
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_sub(8, 0, a, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_add(8, (ecx & 0xffu), 0x17u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(8, (ecx & 0xffu), 0x1fu, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rol(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    {
        uint32_t r = lift_and(32, eax, 0x7fffffu, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_add(8, (ecx & 0xffu), 0x7fu, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, ecx, 0xffu, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x17u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_or(32, eax, ecx, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
L_4d74d0:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d82c6(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D82C6_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D82C6_STACK, 0, entry);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5054a1u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d8300;
    eax = 0x4d80b7u;
    lift_store(&env, 0u, 0x503ea0u, 4, eax);
    eax = 0x4d8188u;
    lift_store(&env, 0u, 0x503ea4u, 4, eax);
    {
        (void)lift_and(8, lift_load(&env, 0u, 0x508798u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4d82f4;
    eax = 0x4d8204u;
    goto L_4d82f9;
L_4d82f4:
    eax = 0x4d8217u;
L_4d82f9:
    lift_store(&env, 0u, 0x503ea8u, 4, eax);
    goto L_4d831e;
L_4d8300:
    eax = 0x4d80d5u;
    lift_store(&env, 0u, 0x503ea0u, 4, eax);
    eax = 0x4d8198u;
    lift_store(&env, 0u, 0x503ea4u, 4, eax);
    eax = 0x4d8227u;
    lift_store(&env, 0u, 0x503ea8u, 4, eax);
L_4d831e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d8340(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8340_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8340_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    ecx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x519fbcu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, ecx);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, ecx, 0x0u, 4, 0x51a024u);
    lift_store(&env, ecx, 0xcu, 4, 0x0u);
    lift_store(&env, ecx, 0x10u, 4, 0x0u);
    lift_store(&env, ecx, 0x14u, 4, 0x0u);
    lift_store(&env, ecx, 0x18u, 4, edx);
    eax = lift_load(&env, ecx, 0x10u, 4);
    lift_store(&env, ecx, 0x8u, 4, eax);
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d83c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D83C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D83C0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    lift_store(&env, eax, 0xcu, 4, 0x0u);
    lift_store(&env, eax, 0x10u, 4, 0x0u);
    eax = lift_load(&env, eax, 0x10u, 4);
    lift_store(&env, edx, 0x8u, 4, eax);
    lift_store(&env, edx, 0x4u, 4, eax);
    eax = lift_load(&env, edx, 0x14u, 4);
    eax = lift_call(&env, 0x4e2400u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, edx, 0x14u, 4, 0x0u);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d83f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D83F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D83F0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x30u, &fl);
        esp = r;
    }
    ecx = eax;
    {
        (void)lift_and(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4d841f;
    lift_store(&env, esp, 0x20u, 4, 0x1u);
    edx = 0x519a10u;
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    goto L_4d8483;
L_4d841f:
    lift_store(&env, eax, 0x0u, 4, 0x51a024u);
    lift_store(&env, esp, 0x24u, 4, eax);
    eax = (esp + 0x14u);
    lift_store(&env, esp, 0x28u, 1, (edx & 0xffu));
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
    lift_store(&env, esp, 0x1cu, 4, 0x519fc8u);
    eax = ecx;
    lift_store(&env, esp, 0x20u, 4, 0x3u);
    eax = lift_call(&env, 0x4d83c0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    {
        (void)lift_and(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4d8479;
    eax = ecx;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
L_4d8479:
    eax = lift_load(&env, esp, 0x14u, 4);
    env.chain = eax;
L_4d8483:
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x30u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d8490(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8490_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8490_STACK, 0, entry);
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
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4d84d0;
    {
        uint32_t v = 0xcu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x18u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, 0x14u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4e23e0u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    ecx = lift_load(&env, esi, 0x18u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, ecx, 0xcu, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = ecx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4d84d0;
L_4d84bd:
    ecx = lift_load(&env, esi, 0x10u, 4);
    lift_store(&env, eax, 0x0u, 4, ecx);
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    lift_store(&env, esi, 0x10u, 4, eax);
    {
        uint32_t r = lift_sub(32, eax, 0xcu, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4d84bd;
L_4d84d0:
    eax = lift_load(&env, esi, 0x10u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, esi, 0x10u, 4, edx);
    lift_store(&env, eax, 0x4u, 4, edi);
    lift_store(&env, eax, 0x0u, 4, ebx);
    {
        uint32_t a = lift_load(&env, esi, 0xcu, 4);
        uint32_t r = lift_inc(32, a, &fl, 1);
        lift_store(&env, esi, 0xcu, 4, r);
    }
    lift_store(&env, eax, 0x8u, 4, 0x0u);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d8540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8540_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8540_STACK, 0, entry);
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
    edx = lift_load(&env, eax, 0x4u, 4);
    ebx = lift_load(&env, edx, 0x0u, 4);
    ecx = lift_load(&env, edx, 0x8u, 4);
    lift_store(&env, eax, 0x4u, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4d855b;
    lift_store(&env, ebx, 0x4u, 4, 0x0u);
    goto L_4d855e;
L_4d855b:
    lift_store(&env, eax, 0x8u, 4, ebx);
L_4d855e:
    eax = lift_call(&env, 0x4d84f0u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d8580(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8580_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8580_STACK, 0, entry);
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
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4d8596;
L_4d858a:
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, eax, 0x2u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_and(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4d858a;
L_4d8596:
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d85f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D85F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D85F0_STACK, 0, entry);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, eax, 0xcu, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d85fc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D85FC_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D85FC_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d85f0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d861e;
    {
        uint32_t r = lift_imul(32, lift_load(&env, eax, 0x0u, 4), 0x41c64e6du, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, edx, 0x3039u, &fl);
        edx = r;
    }
    lift_store(&env, eax, 0x0u, 4, edx);
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_and(32, eax, 0x7fffu, &fl);
        eax = r;
    }
L_4d861e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d8620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8620_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8620_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = lift_call(&env, 0x4d85f0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d862e;
    lift_store(&env, eax, 0x0u, 4, edx);
L_4d862e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d8650(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8650_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8650_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    edx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51a04cu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, edx);
    lift_store(&env, edx, 0x0u, 4, 0x517454u);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, edx, 0x0u, 4, 0x51a0d4u);
    lift_store(&env, edx, 0x4u, 4, 0x0u);
    lift_store(&env, edx, 0x10u, 4, 0x0u);
    eax = lift_load(&env, edx, 0x10u, 4);
    lift_store(&env, edx, 0xcu, 4, eax);
    lift_store(&env, edx, 0x8u, 4, eax);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = edx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d86d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D86D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D86D0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x30u, &fl);
        esp = r;
    }
    ecx = eax;
    {
        (void)lift_and(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4d86ff;
    lift_store(&env, esp, 0x20u, 4, 0x1u);
    edx = 0x51a0f0u;
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    goto L_4d8764;
L_4d86ff:
    lift_store(&env, eax, 0x0u, 4, 0x51a0d4u);
    lift_store(&env, esp, 0x24u, 4, eax);
    eax = (esp + 0x14u);
    lift_store(&env, esp, 0x28u, 1, (edx & 0xffu));
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
    lift_store(&env, esp, 0x1cu, 4, 0x51a058u);
    lift_store(&env, esp, 0x20u, 4, 0x3u);
    eax = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    {
        (void)lift_and(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4d875a;
    eax = ecx;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
L_4d875a:
    eax = lift_load(&env, esp, 0x14u, 4);
    env.chain = eax;
L_4d8764:
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x30u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d8770(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8770_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8770_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4d8780;
    lift_store(&env, eax, 0x10u, 4, ebx);
L_4d8780:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4d879a;
    eax = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, esi);
    lift_store(&env, ecx, 0xcu, 4, esi);
    lift_store(&env, ecx, 0x8u, 4, esi);
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
    return env.failed ? 0u : eax;
L_4d879a:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4d87c3;
    ebx = ((esi * 4u));
    eax = ebx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4c9ff0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0xcu, 4, esi);
    lift_store(&env, ecx, 0x8u, 4, esi);
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
    return env.failed ? 0u : eax;
L_4d87c3:
    {
        (void)lift_sub(32, esi, lift_load(&env, ecx, 0xcu, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4d87f7;
    {
        (void)lift_sub(32, esi, lift_load(&env, ecx, 0x8u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4d87ef;
    ebx = esi;
    eax = lift_load(&env, ecx, 0x8u, 4);
    edx = lift_load(&env, ecx, 0x4u, 4);
    {
        uint32_t r = lift_sub(32, ebx, lift_load(&env, ecx, 0x8u, 4), &fl);
        ebx = r;
    }
    eax = ((eax * 4u));
    ebx = ((ebx * 4u));
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
L_4d87ef:
    lift_store(&env, ecx, 0x8u, 4, esi);
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
    return env.failed ? 0u : eax;
L_4d87f7:
    eax = lift_load(&env, ecx, 0x10u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d883b;
    eax = lift_load(&env, ecx, 0x8u, 4);
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sbb(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4d8821;
    {
        (void)lift_sub(32, eax, 0x400u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4d8821;
    eax = 0x400u;
    goto L_4d883b;
L_4d8821:
    eax = lift_load(&env, ecx, 0x8u, 4);
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sbb(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4d883b;
    eax = 0x4u;
L_4d883b:
    ebp = lift_load(&env, ecx, 0xcu, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    {
        (void)lift_sub(32, esi, ebp, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4d8846;
    ebp = esi;
L_4d8846:
    eax = ((ebp * 4u));
    eax = lift_call(&env, 0x4c9ff0u, eax, edx, ebx, ecx, 0, esp);
    ebx = lift_load(&env, ecx, 0x8u, 4);
    edx = lift_load(&env, ecx, 0x4u, 4);
    ebx = ((ebx * 4u));
    edi = eax;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
    ebx = esi;
    eax = lift_load(&env, ecx, 0x8u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, ebx, lift_load(&env, ecx, 0x8u, 4), &fl);
        ebx = r;
    }
    eax = ((eax * 4u));
    ebx = ((ebx * 4u));
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, edi);
    lift_store(&env, ecx, 0x8u, 4, esi);
    lift_store(&env, ecx, 0xcu, 4, ebp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d8950(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8950_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8950_STACK, 0, entry);
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
    ecx = eax;
    esi = ebx;
    eax = (edx + ebx);
    ebx = lift_load(&env, ecx, 0x8u, 4);
    {
        uint32_t r = lift_sub(32, ebx, eax, &fl);
        ebx = r;
    }
    if (fl.zf)
        goto L_4d8986;
    ebx = ((ebx * 4u));
    eax = ((eax * 4u));
    edi = lift_load(&env, ecx, 0x4u, 4);
    edx = ((edx * 4u));
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, edi, edx, &fl);
        edi = r;
    }
    edx = eax;
    eax = edi;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
L_4d8986:
    {
        uint32_t r = lift_sub(32, lift_load(&env, ecx, 0x8u, 4), esi, &fl);
        lift_store(&env, ecx, 0x8u, 4, r);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d8ab0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8AB0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8AB0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    ecx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51a11cu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, ecx);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, ecx, 0x0u, 4, 0x51a1b4u);
    lift_store(&env, ecx, 0xcu, 4, 0x0u);
    lift_store(&env, ecx, 0x10u, 4, 0x0u);
    lift_store(&env, ecx, 0x14u, 4, 0x0u);
    lift_store(&env, ecx, 0x18u, 4, edx);
    eax = lift_load(&env, ecx, 0x10u, 4);
    lift_store(&env, ecx, 0x8u, 4, eax);
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d8b80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8B80_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8B80_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x30u, &fl);
        esp = r;
    }
    ecx = eax;
    {
        (void)lift_and(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4d8baf;
    lift_store(&env, esp, 0x20u, 4, 0x1u);
    edx = 0x516f80u;
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    goto L_4d8c13;
L_4d8baf:
    lift_store(&env, eax, 0x0u, 4, 0x51a1b4u);
    lift_store(&env, esp, 0x24u, 4, eax);
    eax = (esp + 0x14u);
    lift_store(&env, esp, 0x28u, 1, (edx & 0xffu));
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
    lift_store(&env, esp, 0x1cu, 4, 0x51a128u);
    eax = ecx;
    lift_store(&env, esp, 0x20u, 4, 0x3u);
    eax = lift_call(&env, 0x4d8b30u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    {
        (void)lift_and(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4d8c09;
    eax = ecx;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
L_4d8c09:
    eax = lift_load(&env, esp, 0x14u, 4);
    env.chain = eax;
L_4d8c13:
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x30u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d8c20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D8C20_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D8C20_STACK, 0, entry);
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
    ebp = edx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4d8c60;
    {
        uint32_t v = 0xcu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x18u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, 0x14u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4e23e0u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    ecx = lift_load(&env, esi, 0x18u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, ecx, 0xcu, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = ecx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4d8c60;
L_4d8c4e:
    ecx = lift_load(&env, esi, 0x10u, 4);
    lift_store(&env, eax, 0x0u, 4, ecx);
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    lift_store(&env, esi, 0x10u, 4, eax);
    {
        uint32_t r = lift_sub(32, eax, 0xcu, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4d8c4e;
L_4d8c60:
    edi = lift_load(&env, esi, 0x10u, 4);
    eax = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, esi, 0x10u, 4, eax);
    lift_store(&env, edi, 0x4u, 4, ebp);
    lift_store(&env, edi, 0x0u, 4, ebx);
    ebx = 0x4u;
    {
        uint32_t a = lift_load(&env, esi, 0xcu, 4);
        uint32_t r = lift_inc(32, a, &fl, 1);
        lift_store(&env, esi, 0xcu, 4, r);
    }
    eax = lift_call(&env, 0x4ca060u, eax, edx, ebx, ecx, 0, esp);
    esi = (edi + 0x8u);
    edx = eax;
    eax = esi;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
    eax = edi;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d9280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D9280_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D9280_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    edx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51a344u);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, edx);
    lift_store(&env, edx, 0x0u, 4, 0x517454u);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, edx, 0x0u, 4, 0x517474u);
    lift_store(&env, edx, 0x4u, 4, 0x1u);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = edx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d92f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D92F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D92F0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    ecx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51a350u);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, ecx);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, ecx, 0x0u, 4, 0x517474u);
    lift_store(&env, ecx, 0x4u, 4, edx);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d9350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D9350_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D9350_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4d9362;
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = 0x2u;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
L_4d9362:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d9930(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D9930_STACK + 4 + 4 * 2 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D9930_STACK, 2, entry);
    eax = lift_load(&env, esp, 0x4u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d9949;
    {
        uint32_t v = lift_load(&env, esp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d9ae0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4d9a10u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
L_4d9949:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d9ae0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D9AE0_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D9AE0_STACK, 1, entry);
    edx = lift_load(&env, esp, 0x4u, 4);
    eax = edx;
    {
        (void)lift_sub(32, edx, 0x41u, &fl);
    }
    if (fl.cf)
        goto L_4d9d50;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x7du, &fl);
    }
    if (fl.cf)
        goto L_4d9c6a;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0xb7u, &fl);
    }
    if (fl.cf)
        goto L_4d9bd4;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x10bu, &fl);
    }
    if (fl.cf)
        goto L_4d9ba0;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0x3e4u, &fl);
    }
    if (fl.cf)
        goto L_4d9b90;
    if (fl.cf || fl.zf)
        goto L_4d9b60;
    {
        (void)lift_sub(32, edx, 0x3e5u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9b60;
    {
        (void)lift_sub(32, edx, 0x3e7u, &fl);
    }
    if (fl.zf)
        goto L_4d9b48;
    goto L_4d9b88;
L_4d9b38:
    eax = 0x2u;
    return env.failed ? 0u : eax;
L_4d9b40:
    eax = 0x3u;
    return env.failed ? 0u : eax;
L_4d9b48:
    eax = 0x5u;
    return env.failed ? 0u : eax;
L_4d9b50:
    eax = 0x6u;
    return env.failed ? 0u : eax;
L_4d9b58:
    eax = 0x7u;
    return env.failed ? 0u : eax;
L_4d9b60:
    eax = 0xau;
    return env.failed ? 0u : eax;
L_4d9b68:
    eax = 0xbu;
    return env.failed ? 0u : eax;
L_4d9b70:
    eax = 0xcu;
    return env.failed ? 0u : eax;
L_4d9b78:
    eax = 0xeu;
    return env.failed ? 0u : eax;
L_4d9b80:
    eax = 0x8u;
    return env.failed ? 0u : eax;
L_4d9b88:
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9b90:
    {
        (void)lift_sub(32, edx, 0x3e3u, &fl);
    }
    if (fl.zf)
        goto L_4d9b60;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9ba0:
    {
        (void)lift_sub(32, edx, 0xc1u, &fl);
    }
    if (fl.cf)
        goto L_4d9bc4;
    if (fl.cf || fl.zf)
        goto L_4d9b50;
    {
        (void)lift_sub(32, edx, 0xceu, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0xd0u, &fl);
    }
    if (fl.zf)
        goto L_4d9b40;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9bc4:
    {
        (void)lift_sub(32, edx, 0xbfu, &fl);
    }
    if (fl.zf)
        goto L_4d9b50;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9bd4:
    {
        (void)lift_sub(32, edx, 0x9au, &fl);
    }
    if (fl.cf)
        goto L_4d9c22;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0xa7u, &fl);
    }
    if (fl.cf)
        goto L_4d9c0e;
    if (fl.cf || fl.zf)
        goto L_4d9b70;
    {
        (void)lift_sub(32, edx, 0xaau, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0xb6u, &fl);
    }
    if (fl.zf)
        goto L_4d9b50;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9c0e:
    {
        (void)lift_sub(32, edx, 0xa1u, &fl);
    }
    if (fl.zf)
        goto L_4d9b40;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9c22:
    {
        (void)lift_sub(32, edx, 0x84u, &fl);
    }
    if (fl.cf)
        goto L_4d9c56;
    if (fl.cf || fl.zf)
        goto L_4d9e6a;
    {
        (void)lift_sub(32, edx, 0x90u, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0x91u, &fl);
    }
    if (fl.zf)
        goto L_4d9b58;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9c56:
    {
        (void)lift_sub(32, edx, 0x83u, &fl);
    }
    if (fl.zf)
        goto L_4d9e6a;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9c6a:
    {
        (void)lift_sub(32, edx, 0x58u, &fl);
    }
    if (fl.cf)
        goto L_4d9ce0;
    if (fl.cf || fl.zf)
        goto L_4d9b60;
    {
        (void)lift_sub(32, edx, 0x71u, &fl);
    }
    if (fl.cf)
        goto L_4d9cad;
    if (fl.cf || fl.zf)
        goto L_4d9ee7;
    {
        (void)lift_sub(32, edx, 0x75u, &fl);
    }
    if (fl.cf)
        goto L_4d9c9c;
    if (fl.cf || fl.zf)
        goto L_4d9b60;
    {
        (void)lift_sub(32, edx, 0x7bu, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    eax = 0x3u;
    return env.failed ? 0u : eax;
L_4d9c9c:
    {
        (void)lift_sub(32, edx, 0x72u, &fl);
    }
    if (fl.zf)
        goto L_4d9b50;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9cad:
    {
        (void)lift_sub(32, edx, 0x6cu, &fl);
    }
    if (fl.cf)
        goto L_4d9ccf;
    if (fl.cf || fl.zf)
        goto L_4d9b70;
    {
        (void)lift_sub(32, edx, 0x6fu, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
L_4d9cc7:
    eax = 0xdu;
    return env.failed ? 0u : eax;
L_4d9ccf:
    {
        (void)lift_sub(32, edx, 0x6bu, &fl);
    }
    if (fl.zf)
        goto L_4d9b38;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9ce0:
    {
        (void)lift_sub(32, edx, 0x47u, &fl);
    }
    if (fl.cf)
        goto L_4d9d27;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x52u, &fl);
    }
    if (fl.cf)
        goto L_4d9d16;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x55u, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0x56u, &fl);
    }
    if (fl.zf)
        goto L_4d9b48;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9d16:
    {
        (void)lift_sub(32, edx, 0x50u, &fl);
    }
    if (fl.zf)
        goto L_4d9b48;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9d27:
    {
        (void)lift_sub(32, edx, 0x43u, &fl);
    }
    if (fl.cf)
        goto L_4d9b50;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0x44u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9ee7;
    {
        (void)lift_sub(32, edx, 0x46u, &fl);
    }
    if (fl.zf)
        goto L_4d9b40;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9d50:
    {
        (void)lift_sub(32, edx, 0x1au, &fl);
    }
    if (fl.cf)
        goto L_4d9e42;
    if (fl.cf || fl.zf)
        goto L_4d9b50;
    {
        (void)lift_sub(32, edx, 0x34u, &fl);
    }
    if (fl.cf)
        goto L_4d9dcd;
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0x3au, &fl);
    }
    if (fl.cf)
        goto L_4d9da4;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x3cu, &fl);
    }
    if (fl.cf)
        goto L_4d9b60;
    if (fl.cf || fl.zf)
        goto L_4d9b50;
    {
        (void)lift_sub(32, edx, 0x3eu, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b80;
    {
        (void)lift_sub(32, edx, 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4d9b48;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9da4:
    {
        (void)lift_sub(32, edx, 0x36u, &fl);
    }
    if (fl.cf)
        goto L_4d9b40;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x37u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9b40;
    {
        (void)lift_sub(32, edx, 0x39u, &fl);
    }
    if (fl.zf)
        goto L_4d9b60;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9dcd:
    {
        (void)lift_sub(32, edx, 0x21u, &fl);
    }
    if (fl.cf)
        goto L_4d9e14;
    if (fl.cf || fl.zf)
        goto L_4d9b70;
    {
        (void)lift_sub(32, edx, 0x24u, &fl);
    }
    if (fl.cf)
        goto L_4d9e03;
    if (fl.cf || fl.zf)
        goto L_4d9ee7;
    {
        (void)lift_sub(32, edx, 0x26u, &fl);
    }
    if (fl.cf)
        goto L_4d9b88;
    if (fl.cf || fl.zf)
        goto L_4d9b78;
    {
        (void)lift_sub(32, edx, 0x27u, &fl);
    }
    if (fl.zf)
        goto L_4d9cc7;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9e03:
    {
        (void)lift_sub(32, edx, 0x22u, &fl);
    }
    if (fl.zf)
        goto L_4d9b40;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9e14:
    {
        (void)lift_sub(32, edx, 0x1du, &fl);
    }
    if (fl.cf)
        goto L_4d9e35;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0x1eu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9e6a;
    {
        (void)lift_sub(32, edx, 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4d9b68;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9e35:
    {
        (void)lift_sub(32, edx, 0x1bu, &fl);
    }
    if (fl.zf)
        goto L_4d9e6a;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9e42:
    {
        (void)lift_sub(32, edx, 0x10u, &fl);
    }
    if (fl.cf)
        goto L_4d9e92;
    if (fl.cf || fl.zf)
        goto L_4d9b58;
    {
        (void)lift_sub(32, edx, 0x15u, &fl);
    }
    if (fl.cf)
        goto L_4d9e72;
    if (fl.cf || fl.zf)
        goto L_4d9b60;
    {
        (void)lift_sub(32, edx, 0x17u, &fl);
    }
    if (fl.cf)
        goto L_4d9b60;
    if (fl.cf || fl.zf)
        goto L_4d9b60;
    {
        (void)lift_sub(32, edx, 0x18u, &fl);
    }
L_4d9e6a:
    eax = 0x9u;
    return env.failed ? 0u : eax;
L_4d9e72:
    {
        (void)lift_sub(32, edx, 0x12u, &fl);
    }
    if (fl.cf)
        goto L_4d9b40;
    if (fl.cf || fl.zf)
        goto L_4d9b38;
    {
        (void)lift_sub(32, edx, 0x13u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    eax = 0xau;
    return env.failed ? 0u : eax;
L_4d9e92:
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_4d9ed3;
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0xbu, &fl);
    }
    if (fl.cf)
        goto L_4d9ec2;
    if (fl.cf || fl.zf)
        goto L_4d9b50;
    {
        (void)lift_sub(32, edx, 0xcu, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9b48;
    {
        (void)lift_sub(32, edx, 0xfu, &fl);
    }
    if (fl.zf)
        goto L_4d9b40;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9ec2:
    {
        (void)lift_sub(32, edx, 0x6u, &fl);
    }
    if (fl.zf)
        goto L_4d9b38;
    eax = 0x1u;
    return env.failed ? 0u : eax;
L_4d9ed3:
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (fl.cf)
        goto L_4d9eef;
    if (fl.cf || fl.zf)
        goto L_4d9b38;
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d9b40;
L_4d9ee7:
    eax = 0x4u;
    return env.failed ? 0u : eax;
L_4d9eef:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4d9b88;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4da66e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DA66E_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DA66E_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x14u, &fl);
        esp = r;
    }
    eax = esp;
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
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51a92cu);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    eax = lift_call(&env, 0x4da3bau, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4da71b(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DA71B_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DA71B_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x14u, &fl);
        esp = r;
    }
    ecx = eax;
    eax = esp;
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
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51a930u);
    eax = ecx;
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    eax = lift_call(&env, 0x4da3bau, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4daca0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DACA0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DACA0_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, eax, 0x8u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4dacb6;
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4dacb6:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x10u, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (ebx & 0xffu), 0x2u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    edx = 0xffffffffu;
    lift_store(&env, eax, 0x10u, 1, (ebx & 0xffu));
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dad2e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DAD2E_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DAD2E_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = edx;
    eax = lift_call(&env, 0x4dad38u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4db6d9(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DB6D9_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DB6D9_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x8u, &fl);
        esp = r;
    }
    esi = eax;
    edi = edx;
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    ebx = eax;
    ecx = edx;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = lift_call(&env, 0x4db6a4u, eax, edx, ebx, ecx, 0, esp);
    ebx = esi;
    ecx = edi;
    eax = lift_call(&env, 0x4db507u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4db980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DB980_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DB980_STACK, 4, entry);
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
    esi = lift_load(&env, esp, 0x10u, 4);
    ebx = lift_load(&env, esp, 0x14u, 4);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x18u, 1)) & 0xffu);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4db999;
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
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4db999:
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4db9c2;
    edx = (uint32_t)(int32_t)(int8_t)(uint8_t)(ecx & 0xffu);
    eax = esi;
    eax = lift_call(&env, 0x4db9fcu, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4db9bd;
    eax = lift_load(&env, esp, 0xcu, 4);
    eax = lift_call(&env, 0x4ca180u, eax, edx, ebx, ecx, 0, esp);
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
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4db9bd:
    esi = (eax + 0x1u);
    goto L_4db999;
L_4db9c2:
    edx = (uint32_t)(int32_t)(int8_t)(uint8_t)(ecx & 0xffu);
    eax = esi;
    eax = lift_call(&env, 0x4db9fcu, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4db9dc;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1d24u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ebx = eax;
    goto L_4db9e0;
L_4db9dc:
    ebx = eax;
    {
        uint32_t r = lift_sub(32, ebx, esi, &fl);
        ebx = r;
    }
L_4db9e0:
    eax = lift_load(&env, esp, 0xcu, 4);
    edx = ebx;
    eax = lift_call(&env, 0x4ca6f0u, eax, edx, ebx, ecx, 0, esp);
    edx = esi;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dbaa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DBAA0_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DBAA0_STACK, 1, entry);
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dbab2;
    {
        uint32_t v = lift_load(&env, esp, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c54u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4dbab2:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dc000(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DC000_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DC000_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dc01d;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c77a8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dc01d;
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_load(&env, 0u, 0x5c77a8u, 4);
    eax = lift_call(&env, 0x4dbc60u, eax, edx, ebx, ecx, 0, esp);
L_4dc01d:
    eax = ecx;
    lift_store(&env, ecx, 0x0u, 4, 0x0u);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dc160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DC160_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DC160_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dc16f;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c77e8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc173;
L_4dc16f:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4dc173:
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = lift_call(&env, 0x4dbcd0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dc190(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DC190_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DC190_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dc1ad;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c77e8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dc1ad;
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = lift_call(&env, 0x4dbc60u, eax, edx, ebx, ecx, 0, esp);
L_4dc1ad:
    eax = ecx;
    lift_store(&env, ecx, 0x0u, 4, 0x0u);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dc1c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DC1C0_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DC1C0_STACK, 1, entry);
    ecx = lift_load(&env, esp, 0x4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c77a8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dc1d9;
    eax = lift_load(&env, 0u, 0x5c77a8u, 4);
    edx = ecx;
    eax = lift_call(&env, 0x4dbe70u, eax, edx, ebx, ecx, 0, esp);
L_4dc1d9:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c77e8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dc1ee;
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    edx = ecx;
    eax = lift_call(&env, 0x4dbe70u, eax, edx, ebx, ecx, 0, esp);
L_4dc1ee:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dc290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DC290_STACK + 4 + 4 * 2 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DC290_STACK, 2, entry);
    {
        uint32_t r = lift_sub(32, esp, 0xcu, &fl);
        esp = r;
    }
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc29e;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    goto L_4dc2e7;
L_4dc29e:
    {
        uint32_t v = 0xfffffff0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19f0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        uint32_t r = lift_and(32, eax, 0xfu, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x14u, 4), &fl);
    }
    if (fl.zf)
        goto L_4dc2bc;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
        esp = r;
    }
    return env.failed ? 0u : eax;
L_4dc2bc:
    {
        uint32_t v = 0xau;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x18u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1968u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    {
        uint32_t v = 0x505af0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1d18u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
L_4dc2e7:
    {
        uint32_t r = lift_add(32, esp, 0xcu, &fl);
        esp = r;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dc4b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DC4B0_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DC4B0_STACK, 1, entry);
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
    esi = lift_load(&env, esp, 0xcu, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4dc4e2;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c14u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ebx = eax;
    {
        uint32_t r = lift_and(32, ebx, 0xffu, &fl);
        ebx = r;
    }
L_4dc4ca:
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4dc4da;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c2cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    goto L_4dc4ca;
L_4dc4da:
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c18u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4dc4e2:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dd160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DD160_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DD160_STACK, 0, entry);
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x2cu, 4), 0x0u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dd170(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DD170_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DD170_STACK, 1, entry);
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x30u, 4, edx);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dd180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DD180_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DD180_STACK, 0, entry);
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x30u, 4);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dd360(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DD360_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DD360_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    edx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51afdcu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, edx);
    lift_store(&env, edx, 0x0u, 4, 0x517454u);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, edx, 0x0u, 4, 0x51b5d4u);
    lift_store(&env, edx, 0x4u, 4, 0x0u);
    lift_store(&env, edx, 0x8u, 4, 0x0u);
    lift_store(&env, edx, 0xcu, 4, 0x0u);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = edx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dd3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DD3E0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DD3E0_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4ce780u, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x1cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dd41c;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4dd41c;
    eax = 0x44u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dd419;
    ecx = 0x2u;
    ebx = 0x4u;
    edx = 0x506a78u;
    eax = lift_call(&env, 0x4decd0u, eax, edx, ebx, ecx, 0, esp);
L_4dd419:
    lift_store(&env, esi, 0x1cu, 4, eax);
L_4dd41c:
    eax = lift_load(&env, esi, 0x1cu, 4);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dd440(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DD440_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DD440_STACK, 1, entry);
    eax = 0x1u;
    edx = lift_load(&env, esp, 0x4u, 4);
    eax = lift_call(&env, 0x4dd3e0u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4ded70u, eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dd460(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DD460_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DD460_STACK, 0, entry);
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
    ecx = eax;
    ebx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4dd47f;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4dd3e0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dd47f;
    edx = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_call(&env, 0x4df1c0u, eax, edx, ebx, ecx, 0, esp);
L_4dd47f:
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    eax = lift_call(&env, lift_load(&env, edx, 0x1cu, 4), eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dd4a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DD4A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DD4A0_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x34u, &fl);
        esp = r;
    }
    ebx = eax;
    lift_store(&env, esp, 0x30u, 4, edx);
    {
        (void)lift_and(8, lift_load(&env, esp, 0x30u, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4dd4d9;
    lift_store(&env, esp, 0x20u, 4, 0x1u);
    edx = 0x519780u;
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    goto L_4dd551;
L_4dd4d9:
    lift_store(&env, eax, 0x0u, 4, 0x51b5d4u);
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
    lift_store(&env, esp, 0x1cu, 4, 0x51afe8u);
    lift_store(&env, esp, 0x20u, 4, 0x3u);
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dd52b;
    eax = ebx;
    eax = lift_call(&env, 0x4dd460u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f17dcu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4dd52b:
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    lift_store(&env, ebx, 0x0u, 4, 0x517454u);
    {
        (void)lift_and(8, lift_load(&env, esp, 0x30u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4dd547;
    eax = ebx;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
L_4dd547:
    eax = lift_load(&env, esp, 0x14u, 4);
    env.chain = eax;
L_4dd551:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ddbe0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DDBE0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DDBE0_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4ce780u, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x20u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ddc1c;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4ddc1c;
    eax = 0x44u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ddc19;
    ecx = 0x1u;
    ebx = 0x4u;
    edx = 0x506ad8u;
    eax = lift_call(&env, 0x4decd0u, eax, edx, ebx, ecx, 0, esp);
L_4ddc19:
    lift_store(&env, esi, 0x20u, 4, eax);
L_4ddc1c:
    eax = lift_load(&env, esi, 0x20u, 4);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ddc40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DDC40_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DDC40_STACK, 1, entry);
    eax = 0x1u;
    edx = lift_load(&env, esp, 0x4u, 4);
    eax = lift_call(&env, 0x4ddbe0u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4ded70u, eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ddc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DDC60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DDC60_STACK, 0, entry);
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
    ecx = eax;
    ebx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4ddc7f;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4ddbe0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ddc7f;
    edx = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_call(&env, 0x4df1c0u, eax, edx, ebx, ecx, 0, esp);
L_4ddc7f:
    eax = ebx;
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ddc90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DDC90_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DDC90_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ddc9d;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4ddc9d:
    eax = lift_call(&env, 0x4ddc60u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f17e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4de5c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DE5C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DE5C0_STACK, 0, entry);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c79bcu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4de5f1;
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19e4u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t v = 0x3u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5c7944u, 4, eax);
    eax = lift_call(&env, 0x4f19e4u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, 0u, 0x5c79ccu, 4, 0x1u);
    lift_store(&env, 0u, 0x5c7948u, 4, eax);
L_4de5f1:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4de600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DE600_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DE600_STACK, 0, entry);
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19e4u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = 0x3u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x5c7944u, 4, eax);
    eax = lift_call(&env, 0x4f19e4u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, 0u, 0x5c79ccu, 4, 0x0u);
    lift_store(&env, 0u, 0x5c7948u, 4, eax);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4de810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DE810_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DE810_STACK, 0, entry);
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
    ebx = eax;
    {
        uint32_t v = 0xfu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19e0u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    {
        uint32_t v = 0x10u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebx, 0x44u, 4, eax);
    eax = lift_call(&env, 0x4f19e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = 0x14u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebx, 0x48u, 4, eax);
    eax = lift_call(&env, 0x4f19e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = 0x12u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebx, 0x4cu, 4, eax);
    eax = lift_call(&env, 0x4f19e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = 0x6u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebx, 0x50u, 4, eax);
    eax = lift_call(&env, 0x4f19e0u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, ebx, 0x54u, 4, eax);
    eax = (ebx + 0x2cu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dc400u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = (ebx + 0x30u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dc400u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = (ebx + 0x28u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dc400u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = (ebx + 0x34u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dc400u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = lift_load(&env, ebx, 0x44u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f17d8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = lift_load(&env, ebx, 0x48u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebx, 0x2cu, 4, eax);
    eax = lift_call(&env, 0x4f17d8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = lift_load(&env, ebx, 0x4cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebx, 0x30u, 4, eax);
    eax = lift_call(&env, 0x4f17d8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = lift_load(&env, ebx, 0x54u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebx, 0x28u, 4, eax);
    eax = lift_call(&env, 0x4f17d8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, ebx, 0x34u, 4, eax);
    eax = (ebx + 0x3cu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dc400u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = (ebx + 0x38u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dc400u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = (ebx + 0x40u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dc400u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = lift_load(&env, ebx, 0x48u, 4);
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
    eax = lift_call(&env, 0x4f17d0u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    {
        uint32_t v = lift_load(&env, ebx, 0x4cu, 4);
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
    lift_store(&env, ebx, 0x3cu, 4, eax);
    eax = lift_call(&env, 0x4f17d0u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    lift_store(&env, ebx, 0x38u, 4, eax);
    {
        uint32_t v = lift_load(&env, ebx, 0x50u, 4);
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
    eax = lift_call(&env, 0x4f17d0u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    lift_store(&env, ebx, 0x40u, 4, eax);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4de900(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DE900_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DE900_STACK, 0, entry);
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
        uint32_t v = 0xbu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f19e4u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    {
        uint32_t v = 0xcu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebx, 0x8u, 4, eax);
    eax = lift_call(&env, 0x4f19e4u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    lift_store(&env, ebx, 0xcu, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x88u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4de92e;
    eax = lift_call(&env, 0x4de5c0u, eax, edx, ebx, ecx, 0, esp);
    goto L_4de933;
L_4de92e:
    eax = lift_call(&env, 0x4de600u, eax, edx, ebx, ecx, 0, esp);
L_4de933:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1974u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        uint32_t v = 0x58u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = eax;
    eax = lift_call(&env, 0x4f1808u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        uint32_t v = 0x5au;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebx, 0x18u, 4, eax);
    eax = lift_call(&env, 0x4f1808u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebx, 0x1cu, 4, eax);
    eax = lift_call(&env, 0x4f1a78u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dea40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DEA40_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DEA40_STACK, 1, entry);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c79d4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dea5b;
    {
        uint32_t r = lift_imul(32, lift_load(&env, esp, 0x4u, 4), 0x18u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x5c79d8u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4dea5b:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dea78(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DEA78_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DEA78_STACK, 0, entry);
    eax = lift_call(&env, lift_load(&env, 0u, 0x50724cu, 4), eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dec60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DEC60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DEC60_STACK, 0, entry);
    eax = lift_call(&env, 0x4ce780u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t a = lift_load(&env, eax, 0x10u, 4);
        uint32_t r = lift_inc(32, a, &fl, 1);
        lift_store(&env, eax, 0x10u, 4, r);
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4deec0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DEEC0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DEEC0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    ecx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51baecu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, ecx);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, ecx, 0x0u, 4, 0x51bb54u);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    lift_store(&env, ecx, 0x8u, 4, 0x11u);
    lift_store(&env, ecx, 0xcu, 4, 0x0u);
    lift_store(&env, ecx, 0x10u, 4, 0x0u);
    lift_store(&env, ecx, 0x14u, 4, 0x0u);
    lift_store(&env, ecx, 0x18u, 4, edx);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4def50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DEF50_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DEF50_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4def6b;
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
L_4def6b:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4def87;
    ebx = ((esi * 4u));
    eax = ebx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4c9ff0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
L_4def87:
    lift_store(&env, ecx, 0x8u, 4, esi);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4def90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DEF90_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DEF90_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4defa8;
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, edx, 0x4u, 4, 0x0u);
L_4defa8:
    lift_store(&env, edx, 0xcu, 4, 0x0u);
    eax = lift_load(&env, edx, 0x14u, 4);
    lift_store(&env, edx, 0x10u, 4, 0x0u);
    eax = lift_call(&env, 0x4e2400u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, edx, 0x14u, 4, 0x0u);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4defd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DEFD0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DEFD0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x30u, &fl);
        esp = r;
    }
    ecx = eax;
    {
        (void)lift_and(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4defff;
    lift_store(&env, esp, 0x20u, 4, 0x1u);
    edx = 0x51bb70u;
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    goto L_4df063;
L_4defff:
    lift_store(&env, eax, 0x0u, 4, 0x51bb54u);
    lift_store(&env, esp, 0x24u, 4, eax);
    eax = (esp + 0x14u);
    lift_store(&env, esp, 0x28u, 1, (edx & 0xffu));
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
    lift_store(&env, esp, 0x1cu, 4, 0x51baf8u);
    eax = ecx;
    lift_store(&env, esp, 0x20u, 4, 0x3u);
    eax = lift_call(&env, 0x4def90u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    {
        (void)lift_and(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4df059;
    eax = ecx;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
L_4df059:
    eax = lift_load(&env, esp, 0x14u, 4);
    env.chain = eax;
L_4df063:
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x30u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4df070(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DF070_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DF070_STACK, 0, entry);
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
    ebx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4df0b0;
    {
        uint32_t v = 0x10u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x18u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, 0x14u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4e23e0u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    ecx = lift_load(&env, ebx, 0x18u, 4);
    edx = (eax + 0x4u);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    eax = ecx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = ecx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4df0b0;
L_4df09d:
    ecx = lift_load(&env, ebx, 0x10u, 4);
    lift_store(&env, eax, 0x0u, 4, ecx);
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    lift_store(&env, ebx, 0x10u, 4, eax);
    {
        uint32_t r = lift_sub(32, eax, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4df09d;
L_4df0b0:
    eax = lift_load(&env, ebx, 0x10u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebx, 0x10u, 4, edx);
    {
        uint32_t a = lift_load(&env, ebx, 0xcu, 4);
        uint32_t r = lift_inc(32, a, &fl, 1);
        lift_store(&env, ebx, 0xcu, 4, r);
    }
    lift_store(&env, eax, 0x8u, 4, 0x0u);
    lift_store(&env, eax, 0xcu, 4, 0x0u);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dfa74(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DFA74_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DFA74_STACK, 0, entry);
    eax = lift_call(&env, lift_load(&env, 0u, 0x509794u, 4), eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dfa7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DFA7C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DFA7C_STACK, 0, entry);
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
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_and(8, lift_load(&env, eax, 0x1eu, 1), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_4dfab8;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x16u, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4dfab8;
    edx = lift_load(&env, eax, 0x4u, 4);
    ebx = lift_load(&env, eax, 0x20u, 4);
    ecx = lift_load(&env, eax, 0x24u, 4);
    {
        uint32_t r = lift_sub(32, edx, ebx, &fl);
        edx = r;
    }
    esi = lift_load(&env, eax, 0x28u, 4);
    {
        uint32_t r = lift_sub(32, edx, ecx, &fl);
        edx = r;
    }
    edi = lift_load(&env, eax, 0x2cu, 4);
    {
        uint32_t r = lift_sub(32, edx, esi, &fl);
        edx = r;
    }
    ebp = lift_load(&env, eax, 0x30u, 4);
    {
        uint32_t r = lift_sub(32, edx, edi, &fl);
        edx = r;
    }
    ebx = lift_load(&env, eax, 0x34u, 4);
    {
        uint32_t r = lift_sub(32, edx, ebp, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, edx, ebx, &fl);
        edx = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4dfab8;
    {
        uint32_t r = lift_add(32, ecx, edx, &fl);
        ecx = r;
    }
    lift_store(&env, eax, 0x24u, 4, ecx);
L_4dfab8:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e0150(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0150_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0150_STACK, 0, entry);
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
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e0162;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x507c34u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e0174;
L_4e0162:
    eax = 0x4u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4e0174:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = esi;
    eax = lift_call(&env, 0x4e01d0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e0195;
    {
        (void)lift_and(8, (eax & 0xffu), 0x80u, &fl);
    }
    if (!fl.zf)
        goto L_4e0195;
    {
        uint32_t r = lift_or(8, ((eax >> 8) & 0xffu), 0x80u, &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    edx = eax;
    eax = esi;
    eax = lift_call(&env, 0x4e0228u, eax, edx, ebx, ecx, 0, esp);
L_4e0195:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x507c8cu, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, edx, (esi * 4u) + 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ca8u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    ecx = eax;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, ecx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e01be;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
L_4e01be:
    eax = ecx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e01d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E01D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E01D0_STACK, 0, entry);
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
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x507c34u, 4), &fl);
    }
    if (fl.cf)
        goto L_4e01e3;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e01e3:
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e021b;
    ebx = ((eax * 4u));
    eax = lift_load(&env, 0u, 0x507c88u, 4);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, eax, 0x1u, 1)) & 0xffu);
    {
        (void)lift_and(8, (ecx & 0xffu), 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_4e021b;
    ecx = (ecx & 0xffff00ffu) | ((((ecx & 0xffu)) & 0xffu) << 8);
    {
        uint32_t r = lift_or(8, ((ecx >> 8) & 0xffu), 0x40u, &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    lift_store(&env, eax, 0x1u, 1, ((ecx >> 8) & 0xffu));
    eax = edx;
    eax = lift_call(&env, 0x4e0a30u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e021b;
    eax = lift_load(&env, 0u, 0x507c88u, 4);
    {
        uint32_t r = lift_or(8, lift_load(&env, ebx, eax + 0x1u, 1), 0x20u, &fl);
        lift_store(&env, ebx, eax + 0x1u, 1, r);
    }
L_4e021b:
    eax = lift_load(&env, 0u, 0x507c88u, 4);
    eax = lift_load(&env, eax, (edx * 4u) + 0x0u, 4);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e0250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0250_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0250_STACK, 0, entry);
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
    ecx = lift_load(&env, 0u, 0x507c8cu, 4);
    eax = lift_load(&env, 0u, 0x507c90u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x507c34u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4e026a;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    goto L_4e0299;
L_4e026a:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e0294;
    ebx = lift_load(&env, 0u, 0x507c90u, 4);
    edx = ecx;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ebx = r;
    }
L_4e027b:
    {
        (void)lift_sub(32, lift_load(&env, edx, eax + 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e028d;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x507c8cu, 4, ecx);
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
    return env.failed ? 0u : eax;
L_4e028d:
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e027b;
L_4e0294:
    eax = 0x1u;
L_4e0299:
    lift_store(&env, 0u, 0x507c8cu, 4, ecx);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e0430(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0430_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0430_STACK, 0, entry);
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
        uint32_t v = 0xfffffff6u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1be8u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e0446;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e044b;
L_4e0446:
    eax = lift_call(&env, 0x4e0490u, eax, edx, ebx, ecx, 0, esp);
L_4e044b:
    eax = lift_call(&env, 0x4e02a4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = 0xfffffff5u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1be8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e0464;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e0469;
L_4e0464:
    eax = lift_call(&env, 0x4e0490u, eax, edx, ebx, ecx, 0, esp);
L_4e0469:
    eax = lift_call(&env, 0x4e02a4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = 0xfffffff4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1be8u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e0482;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e0487;
L_4e0482:
    eax = lift_call(&env, 0x4e0490u, eax, edx, ebx, ecx, 0, esp);
L_4e0487:
    eax = lift_call(&env, 0x4e02a4u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e0508(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0508_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0508_STACK, 0, entry);
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
    edi = ebx;
    eax = edx;
    lift_store(&env, 0u, 0x5c7b90u, 4, esi);
    eax = lift_call(&env, 0x4e587cu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, 0u, 0x5c7b9cu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e0536;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e0732;
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b4cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e0536:
    eax = lift_call(&env, 0x4e0430u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4f1ba4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x509729u, 4, eax);
    lift_store(&env, 0u, 0x5c81d4u, 4, edx);
    eax = lift_call(&env, 0x4f1c00u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    ebx = eax;
    lift_store(&env, 0u, 0x50972fu, 1, (eax & 0xffu));
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_and(32, eax, 0xffffu, &fl);
        eax = r;
    }
    {
        uint32_t v = 0x104u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x509731u, 2, (eax & 0xffffu));
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_and(32, edx, 0xffffu, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x509731u, 2)) & 0xffffu);
    {
        uint32_t v = 0x5c7ba0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, 0u, 0x509733u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x509737u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x509730u, 1, (edx & 0xffu));
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    edx = lift_load(&env, 0u, 0x509737u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    ebx = 0x5c7ba0u;
    {
        uint32_t r = lift_or(32, edx, eax, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x50973bu, 4, eax);
    lift_store(&env, 0u, 0x50973fu, 4, edx);
    eax = lift_call(&env, 0x4f1bc4u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    edx = 0x5c7ca4u;
    lift_store(&env, 0u, 0x5096f0u, 4, ebx);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    ebx = 0x208u;
    ecx = 0x5c7ca4u;
    eax = lift_call(&env, 0x4e6510u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, 0u, 0x5096fcu, 4, ecx);
    eax = lift_call(&env, 0x4f1b84u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4e65b0u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5c7b94u, 4, eax);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x22u, &fl);
    }
    if (!fl.zf)
        goto L_4e0624;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, eax, 0x1u, 1)) & 0xffu) << 8);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e061c;
L_4e060e:
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e061c;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x1u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        (void)lift_sub(8, (edx & 0xffu), 0x22u, &fl);
    }
    if (!fl.zf)
        goto L_4e060e;
L_4e061c:
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e063f;
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    goto L_4e063f;
L_4e0624:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = (edx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    {
        (void)lift_and(8, lift_load(&env, edx, 0x507d58u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e063f;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e063f;
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    goto L_4e0624;
L_4e063f:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = (edx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    {
        (void)lift_and(8, lift_load(&env, edx, 0x507d58u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e0655;
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    goto L_4e063f;
L_4e0655:
    lift_store(&env, 0u, 0x5096ecu, 4, eax);
    eax = lift_call(&env, 0x4f1b88u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e06e6;
    eax = lift_call(&env, 0x4e6600u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5c7b98u, 4, eax);
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x22u, &fl);
    }
    if (!fl.zf)
        goto L_4e06a8;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, eax, 0x2u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(16, (ecx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4e069d;
L_4e068a:
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e069d;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, eax, 0x2u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x22u, &fl);
    }
    if (!fl.zf)
        goto L_4e068a;
L_4e069d:
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e06ca;
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    goto L_4e06ca;
L_4e06a8:
    ebx = 0x2u;
L_4e06ad:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = (edx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    {
        (void)lift_and(8, lift_load(&env, edx, 0x507d58u, 1), (ebx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4e06ca;
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e06ca;
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    goto L_4e06ad;
L_4e06ca:
    ebx = 0x2u;
L_4e06cf:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = (edx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    {
        (void)lift_and(8, lift_load(&env, edx, 0x507d58u, 1), (ebx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e06eb;
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    goto L_4e06cf;
L_4e06e6:
    eax = 0x5127d8u;
L_4e06eb:
    lift_store(&env, 0u, 0x5096f8u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4e072d;
    {
        uint32_t v = 0x104u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5c7eacu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = 0x5c7eacu;
    ebx = 0x208u;
    eax = lift_call(&env, 0x4f1bc4u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    edx = 0x5c7fb0u;
    lift_store(&env, 0u, 0x5096f4u, 4, esi);
    eax = edi;
    edi = 0x5c7fb0u;
    eax = lift_call(&env, 0x4e6510u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, 0u, 0x509700u, 4, edi);
L_4e072d:
    eax = 0x1u;
L_4e0732:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e081c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E081C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E081C_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = lift_call(&env, 0x4daeb8u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, edx, 0x7bu, &fl);
    }
    if (!fl.zf)
        goto L_4e0830;
    eax = 0x1u;
    goto L_4e0875;
L_4e0830:
    {
        (void)lift_sub(32, edx, 0xceu, &fl);
    }
    if (!fl.zf)
        goto L_4e0849;
    eax = 0x9u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e0849:
    {
        (void)lift_sub(32, edx, 0xb7u, &fl);
    }
    if (!fl.zf)
        goto L_4e0862;
    eax = 0x7u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e0862:
    {
        (void)lift_sub(32, edx, 0x13u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e086c;
    edx = 0x13u;
L_4e086c:
    eax = lift_load(&env, edx, 0x507ce5u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
L_4e0875:
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e0b9e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0B9E_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0B9E_STACK, 0, entry);
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
    ecx = eax;
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e0be4;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, ecx, 0x4u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e0bd9;
    eax = lift_load(&env, eax, 0x8u, 4);
    ebx = (edx + 0xffffffffu);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e0be9;
    eax = lift_call(&env, 0x4e0a95u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e0be9;
    edx = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, edx, 0x0u, 1);
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4e0be9;
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    edx = lift_load(&env, edx, 0x4u, 4);
L_4e0bd9:
    eax = ecx;
    eax = lift_call(&env, 0x4e0ae5u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
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
    return env.failed ? 0u : eax;
L_4e0be4:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e0be9:
    edx = ebx;
    goto L_4e0bd9;
}

uint32_t lifted_f4e0bed(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0BED_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0BED_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x4u, 4);
    eax = lift_call(&env, 0x4e0ae5u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e0bf8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0BF8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0BF8_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4e0f8bu, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    eax = 0x5127dcu;
    eax = lift_call(&env, 0x4e0c0cu, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e0fc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0FC0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0FC0_STACK, 0, entry);
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
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e0fd4;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x507c34u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e0fe5;
L_4e0fd4:
    eax = 0x4u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
    goto L_4e1046;
L_4e0fe5:
    edx = lift_load(&env, 0u, 0x507c8cu, 4);
    ebp = lift_load(&env, 0u, 0x507d08u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    edi = lift_load(&env, edx, (ebx * 4u) + 0x0u, 4);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4e101a;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cfcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e101a;
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507d00u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507d08u, 4), eax, edx, ebx, ecx, 0, esp);
    goto L_4e103b;
L_4e101a:
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4e103b;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e103b;
    eax = 0x4u;
    esi = 0xffffffffu;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e1044;
L_4e103b:
    eax = ebx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4e0228u, eax, edx, ebx, ecx, 0, esp);
L_4e1044:
    eax = esi;
L_4e1046:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e104e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E104E_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E104E_STACK, 0, entry);
    goto L_4e6ef0;
L_4e6ef0:
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
    ebx = eax;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
L_4e6ef6:
    eax = ebx;
    eax = lift_call(&env, 0x4e7b50u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e6f19;
    eax = ebx;
    eax = lift_call(&env, 0x4e3a50u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_4e6f0e;
    ecx = ebx;
L_4e6f0e:
    eax = ebx;
    eax = lift_call(&env, 0x4e3a90u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    goto L_4e6ef6;
L_4e6f19:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e6f22;
    eax = ecx;
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
    return env.failed ? 0u : eax;
L_4e6f22:
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e1054(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E1054_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E1054_STACK, 0, entry);
    goto L_4e3a90;
L_4e3a90:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c8950u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e3aba;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x5c8961u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (edx & 0xffu), 0x1u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4e3aba;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x1u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e3aba;
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e3aba:
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e11b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E11B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E11B0_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4ce780u, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x18u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e11ec;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e11ec;
    eax = 0x44u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e11e9;
    ecx = 0x1u;
    ebx = 0x4u;
    edx = 0x508158u;
    eax = lift_call(&env, 0x4decd0u, eax, edx, ebx, ecx, 0, esp);
L_4e11e9:
    lift_store(&env, esi, 0x18u, 4, eax);
L_4e11ec:
    eax = lift_load(&env, esi, 0x18u, 4);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e1210(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E1210_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E1210_STACK, 1, entry);
    eax = 0x1u;
    edx = lift_load(&env, esp, 0x4u, 4);
    eax = lift_call(&env, 0x4e11b0u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4ded70u, eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e1260(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E1260_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E1260_STACK, 0, entry);
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
    ecx = eax;
    ebx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e127f;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4e11b0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e127f;
    edx = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_call(&env, 0x4df1c0u, eax, edx, ebx, ecx, 0, esp);
L_4e127f:
    eax = ebx;
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e1290(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E1290_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E1290_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e129d;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e129d:
    eax = lift_call(&env, 0x4e1260u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1934u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e14b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E14B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E14B0_STACK, 0, entry);
    eax = lift_call(&env, lift_load(&env, 0u, 0x509748u, 4), eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e14b7(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E14B7_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E14B7_STACK, 0, entry);
    eax = lift_call(&env, lift_load(&env, 0u, 0x50974cu, 4), eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e14f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E14F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E14F0_STACK, 0, entry);
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
    ecx = eax;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4e1505;
    lift_store(&env, eax, 0x0u, 4, edx);
    lift_store(&env, eax, 0x4u, 4, edx);
    lift_store(&env, eax, 0x8u, 4, edx);
    eax = ecx;
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
    return env.failed ? 0u : eax;
L_4e1505:
    eax = edx;
    eax = lift_call(&env, 0x4e1620u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    eax = ecx;
    eax = lift_call(&env, 0x4e1520u, eax, edx, ebx, ecx, 0, esp);
    eax = ecx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e1590(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E1590_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E1590_STACK, 0, entry);
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
    ebx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e15a2;
    {
        uint32_t v = lift_load(&env, eax, 0x0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c18u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e15a2:
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e15b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E15B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E15B0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e15c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E15C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E15C0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x2u, 2);
    {
        (void)lift_sub(32, edx, 0xffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e15d2;
    {
        uint32_t r = lift_add(32, eax, 0x1au, &fl);
        eax = r;
    }
    goto L_4e15d5;
L_4e15d2:
    {
        uint32_t r = lift_add(32, eax, 0x12u, &fl);
        eax = r;
    }
L_4e15d5:
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x0u, 2), 0xffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e15e0;
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    goto L_4e15ec;
L_4e15e0:
    edx = eax;
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x0u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e15e0;
L_4e15ec:
    {
        (void)lift_sub(16, lift_load(&env, eax, 0x0u, 2), 0xffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e15f7;
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    goto L_4e1604;
L_4e15f7:
    edx = eax;
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x0u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e15f7;
L_4e1604:
    edx = eax;
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x0u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e1604;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e1990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E1990_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E1990_STACK, 4, entry);
    {
        uint32_t v = 0x8001u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c9cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x8u, 4, edx);
    lift_store(&env, eax, 0xcu, 4, edx);
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e19d8;
    edx = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x60u, 4, edx);
    edx = lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, eax, 0x64u, 4, edx);
    edx = lift_load(&env, esp, 0xcu, 4);
    lift_store(&env, eax, 0x68u, 4, edx);
    edx = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, eax, 0x6cu, 4, edx);
    eax = lift_call(&env, 0x4e1a20u, eax, edx, ebx, ecx, 0, esp);
L_4e19d8:
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x14u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e19e8;
    eax = lift_call(&env, 0x4cbe90u, eax, edx, ebx, ecx, 0, esp);
L_4e19e8:
    eax = 0x1u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e2371(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E2371_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E2371_STACK, 0, entry);
    eax = 0x83u;
    eax = lift_call(&env, 0x4e7280u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e239a;
L_4e239a:
    {
        uint32_t r = lift_and(32, eax, 0x80000000u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_or(32, eax, 0x7ff00000u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e237d(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E237D_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E237D_STACK, 0, entry);
    eax = 0x83u;
    eax = lift_call(&env, 0x4e7280u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e239a;
L_4e239a:
    {
        uint32_t r = lift_and(32, eax, 0x80000000u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_or(32, eax, 0x7ff00000u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e2389(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E2389_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E2389_STACK, 0, entry);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4dae94u, eax, edx, ebx, ecx, 0, esp);
    eax = 0x84u;
    eax = lift_call(&env, 0x4e7280u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    {
        uint32_t r = lift_and(32, eax, 0x80000000u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_or(32, eax, 0x7ff00000u, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e2420(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E2420_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E2420_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    eax = edx;
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = lift_call(&env, 0x4e3e00u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t a = lift_load(&env, ebx, 0x10u, 4);
        uint32_t r = lift_inc(32, a, &fl, 1);
        lift_store(&env, ebx, 0x10u, 4, r);
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e2cc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E2CC0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E2CC0_STACK, 0, entry);
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
    ecx = eax;
    ebx = eax;
    eax = lift_load(&env, eax, 0x24u, 4);
    edx = (eax + 0x2u);
    {
        (void)lift_sub(32, edx, lift_load(&env, ecx, 0x28u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e2ce7;
    edx = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    eax = 0x2u;
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    edx = eax;
    eax = ecx;
    eax = lift_call(&env, 0x4e2b60u, eax, edx, ebx, ecx, 0, esp);
L_4e2ce7:
    eax = lift_load(&env, ebx, 0x24u, 4);
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0xfffffffeu, 2)) & 0xffffu);
    lift_store(&env, ebx, 0x24u, 4, eax);
    eax = (edx & 0xffffu);
    {
        (void)lift_sub(32, eax, 0xffffu, &fl);
    }
    if (fl.zf)
        goto L_4e2d05;
    eax = (edx & 0xffffu);
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
    return env.failed ? 0u : eax;
L_4e2d05:
    eax = lift_load(&env, ecx, 0x24u, 4);
    edx = (eax + 0x4u);
    ebx = ecx;
    {
        (void)lift_sub(32, edx, lift_load(&env, ecx, 0x28u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e2d27;
    edx = lift_load(&env, ecx, 0x28u, 4);
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    eax = 0x4u;
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    edx = eax;
    eax = ecx;
    eax = lift_call(&env, 0x4e2b60u, eax, edx, ebx, ecx, 0, esp);
L_4e2d27:
    eax = lift_load(&env, ebx, 0x24u, 4);
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    edx = lift_load(&env, eax, 0xfffffffcu, 4);
    lift_store(&env, ebx, 0x24u, 4, eax);
    eax = edx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e2d40(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E2D40_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E2D40_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, eax, 0x30u, 4), 0x3ffffffeu, &fl);
    }
    if (fl.cf)
        goto L_4e2d56;
    eax = lift_load(&env, eax, 0x10u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x5u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4e7370u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
L_4e2d56:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e2f10(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E2F10_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E2F10_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x18u, &fl);
        esp = r;
    }
    ecx = eax;
    esi = edx;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51bd40u);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x14u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4e2fd8;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x34u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e2fa4;
    eax = 0x1cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e2f7d;
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    edx = lift_load(&env, ecx, 0x3cu, 4);
    lift_store(&env, esp, 0x14u, 4, eax);
    eax = lift_call(&env, 0x4deec0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
L_4e2f7d:
    ebx = 0x1u;
    edx = lift_load(&env, ecx, 0x40u, 4);
    lift_store(&env, ecx, 0x34u, 4, eax);
    eax = lift_call(&env, 0x4def50u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, ecx, 0x34u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4df160u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    lift_store(&env, ecx, 0x30u, 4, 0x1u);
L_4e2fa4:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4e304b;
    eax = ecx;
    eax = lift_call(&env, 0x4e2d40u, eax, edx, ebx, ecx, 0, esp);
    ebx = lift_load(&env, ecx, 0x30u, 4);
    eax = (ebx + 0x1u);
    lift_store(&env, ecx, 0x30u, 4, eax);
    edx = esi;
    eax = lift_load(&env, ecx, 0x34u, 4);
    eax = lift_call(&env, 0x4df160u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, eax, 0x0u, 4, ebx);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    {
        uint32_t r = lift_add(32, esp, 0x18u, &fl);
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
    return env.failed ? 0u : eax;
L_4e2fd8:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x34u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e3028;
    eax = 0x14u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e3005;
    lift_store(&env, esp, 0xcu, 4, 0x3u);
    lift_store(&env, esp, 0x14u, 4, eax);
    eax = lift_call(&env, 0x4e7540u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
L_4e3005:
    edx = 0x1u;
    ebx = lift_load(&env, ecx, 0x3cu, 4);
    lift_store(&env, ecx, 0x34u, 4, eax);
    eax = lift_call(&env, 0x4e7660u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, ecx, 0x34u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    lift_store(&env, ecx, 0x30u, 4, 0x1u);
L_4e3028:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4e304b;
    eax = ecx;
    eax = lift_call(&env, 0x4e2d40u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, ecx, 0x30u, 4);
    eax = (edx + 0x1u);
    lift_store(&env, ecx, 0x30u, 4, eax);
    ebx = esi;
    eax = lift_load(&env, ecx, 0x34u, 4);
    ecx = 0x1u;
    eax = lift_call(&env, 0x4e7790u, eax, edx, ebx, ecx, 0, esp);
L_4e304b:
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    {
        uint32_t r = lift_add(32, esp, 0x18u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e34c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E34C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E34C0_STACK, 0, entry);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e3681(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3681_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3681_STACK, 0, entry);
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
    ecx = eax;
    ebx = 0x63u;
    eax = lift_call(&env, 0x4eb860u, eax, edx, ebx, ecx, 0, esp);
    eax = ecx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e36c4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E36C4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E36C4_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x4u, 4);
    ecx = lift_load(&env, eax, 0x8u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, edx, 0x20u, 4, ecx);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e36d2(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E36D2_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E36D2_STACK, 1, entry);
    ecx = (uint32_t)(int32_t)(int8_t)(uint8_t)(ecx & 0xffu);
    eax = lift_call(&env, 0x4e3698u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x10u, 4, edx);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e36e4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E36E4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E36E4_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e36fb;
L_4e36ed:
    edx = 0x1u;
    eax = ecx;
    eax = lift_call(&env, 0x4e36c4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
L_4e36fb:
    edx = lift_load(&env, eax, 0x10u, 4);
    lift_store(&env, eax, 0x10u, 4, 0x0u);
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = lift_call(&env, 0x4e0e69u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e36ed;
}

uint32_t lifted_f4e370f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E370F_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E370F_STACK, 1, entry);
    {
        uint32_t v = lift_load(&env, esp, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (uint32_t)(int32_t)(int8_t)(uint8_t)(ecx & 0xffu);
    eax = lift_call(&env, 0x4e36d2u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e371e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E371E_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E371E_STACK, 1, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0x8u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x2u;
    eax = lift_call(&env, 0x4e370fu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    edx = eax;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e3737;
    esi = lift_load(&env, eax, 0x0u, 4);
L_4e3737:
    lift_store(&env, eax, 0x14u, 4, esi);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e373e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E373E_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E373E_STACK, 0, entry);
    edx = 0x1u;
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    edx = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, eax, 0x10u, 4);
    eax = lift_call(&env, 0x4e0ec7u, eax, edx, ebx, ecx, 0, esp);
    edx = 0x1u;
    eax = ecx;
    lift_store(&env, ecx, 0x10u, 4, 0x0u);
    eax = lift_call(&env, 0x4e36e4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e3743(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3743_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3743_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = eax;
    edx = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, eax, 0x10u, 4);
    eax = lift_call(&env, 0x4e0ec7u, eax, edx, ebx, ecx, 0, esp);
    edx = 0x1u;
    eax = ecx;
    lift_store(&env, ecx, 0x10u, 4, 0x0u);
    eax = lift_call(&env, 0x4e36e4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e37fe(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E37FE_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E37FE_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 1);
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e3812;
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    {
        (void)lift_and(8, lift_load(&env, eax, 0x3u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e3812;
    eax = lift_load(&env, eax, 0x4u, 4);
L_4e3812:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e39a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E39A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E39A0_STACK, 0, entry);
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
    ebx = eax;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
L_4e39a6:
    eax = ebx;
    eax = lift_call(&env, 0x4e7b50u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e39c7;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e39c7;
    eax = ebx;
    eax = lift_call(&env, 0x4e6f30u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.cf)
        goto L_4e39c7;
    {
        uint32_t a = ecx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ecx = r;
    }
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, ebx, eax, &fl);
        ebx = r;
    }
    goto L_4e39a6;
L_4e39c7:
    eax = ecx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e39d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E39D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E39D0_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    edx = ebx;
    eax = esi;
    eax = lift_call(&env, 0x4e39f0u, eax, edx, ebx, ecx, 0, esp);
    ebx = (eax + 0x1u);
    edx = esi;
    eax = ecx;
    eax = lift_call(&env, 0x4e7b90u, eax, edx, ebx, ecx, 0, esp);
    eax = ecx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e39f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E39F0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E39F0_STACK, 0, entry);
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
    ebx = eax;
    ecx = edx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
L_4e39f9:
    eax = ebx;
    eax = lift_call(&env, 0x4e7b50u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e3a41;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e3a41;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c8950u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e3a34;
    esi = lift_load(&env, ebx, 0x0u, 1);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x5c8961u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (eax & 0xffu), 0x1u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4e3a34;
    {
        (void)lift_sub(8, lift_load(&env, ebx, 0x1u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e3a41;
    eax = ebx;
    eax = lift_call(&env, 0x4e6f30u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    goto L_4e3a35;
L_4e3a34:
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
L_4e3a35:
    eax = ebx;
    eax = lift_call(&env, 0x4e3a90u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    ebx = eax;
    goto L_4e39f9;
L_4e3a41:
    eax = edx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e3a50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3A50_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3A50_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c8950u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e3a82;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x5c8961u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (edx & 0xffu), 0x1u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4e3a82;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x1u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_or(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e3a82:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e3a90(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3A90_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3A90_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c8950u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e3aba;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x5c8961u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (edx & 0xffu), 0x1u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4e3aba;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x1u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e3aba;
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e3aba:
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e3bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3BF0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3BF0_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    esi = eax;
    edi = edx;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e3c07;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x507c34u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e3c1b;
L_4e3c07:
    eax = 0x4u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
    goto L_4e3cd3;
L_4e3c1b:
    ebp = lift_load(&env, 0u, 0x507c8cu, 4);
    ebp = lift_load(&env, ebp, (esi * 4u) + 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = esi;
    eax = lift_call(&env, 0x4e01d0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(8, (eax & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4e3c5e;
    {
        uint32_t v = 0x2u;
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
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ca8u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e3c5e;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 1, esp);
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
L_4e3c5e:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x507d28u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e3c8f;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cfcu, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e3c8f;
    edx = edi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507d28u, 4), eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
L_4e3c8f:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x4u);
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
    eax = lift_call(&env, 0x4f1d08u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e3cb9;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 1, esp);
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
L_4e3cb9:
    {
        (void)lift_sub(32, ebx, lift_load(&env, esp, 0x0u, 4), &fl);
    }
    if (fl.zf)
        goto L_4e3cc8;
    eax = 0xcu;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
L_4e3cc8:
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, esp, 0x0u, 4);
L_4e3cd3:
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e44c8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E44C8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E44C8_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    edx = eax;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
L_4e44d3:
    eax = edx;
    eax = lift_call(&env, 0x4e4100u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x0u, 4, eax);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = (ecx & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    esi = (ecx & 0xffu);
    {
        (void)lift_and(8, lift_load(&env, esi, 0x507d58u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e44f1;
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    goto L_4e44d3;
L_4e44f1:
    {
        (void)lift_and(8, lift_load(&env, edx, 0x10u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e44fc;
    eax = lift_call(&env, 0x4e4108u, eax, edx, ebx, ecx, 0, esp);
L_4e44fc:
    eax = ebx;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e4fd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E4FD0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E4FD0_STACK, 0, entry);
    {
        (void)lift_sub(32, eax, 0x30u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e4fde;
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e4fde;
    {
        uint32_t r = lift_sub(32, eax, 0x30u, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
L_4e4fde:
    eax = lift_call(&env, 0x4e82f0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x61u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e4ff1;
    {
        (void)lift_sub(32, eax, 0x66u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e4ff1;
    {
        uint32_t r = lift_sub(32, eax, 0x57u, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
L_4e4ff1:
    eax = 0x10u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e4ff8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E4FF8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E4FF8_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = lift_load(&env, eax, 0xcu, 4);
    ebx = (eax + 0xffffffffu);
    lift_store(&env, edx, 0xcu, 4, ebx);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e5016;
    eax = edx;
    eax = lift_call(&env, 0x4e4100u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(8, lift_load(&env, edx, 0x10u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e501b;
L_4e5016:
    eax = 0xffffffffu;
L_4e501b:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5271(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5271_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5271_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x8u, &fl);
        esp = r;
    }
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    lift_store(&env, ebp, 0xfffffff8u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e5305;
    eax = lift_load(&env, ebp, 0xfffffffau, 4);
    {
        uint32_t r = lift_and(32, eax, 0x7ff0u, &fl);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, ebx, 0x3e80u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e52a1;
    ebx = 0x3e80u;
    goto L_4e52ae;
L_4e52a1:
    {
        (void)lift_sub(32, ebx, 0xffffc180u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e52ae;
    ebx = 0xffffc180u;
L_4e52ae:
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e52ba;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    goto L_4e530b;
L_4e52ba:
    {
        (void)lift_sub(32, eax, 0x7ffu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e52ed;
    ecx = lift_load(&env, ebp, 0xfffffffau, 4);
    eax = lift_call(&env, 0x4dae94u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e52db;
    eax = lift_load(&env, 0u, 0x51ab90u, 4);
    edx = lift_load(&env, 0u, 0x51ab94u, 4);
    goto L_4e530b;
L_4e52db:
    eax = lift_load(&env, 0u, 0x51ab90u, 4);
    edx = lift_load(&env, 0u, 0x51ab94u, 4);
    eax = lift_call(&env, 0x4dae4au, eax, edx, ebx, ecx, 0, esp);
    goto L_4e530b;
L_4e52ed:
    edx = lift_load(&env, ebp, 0xfffffffau, 4);
    {
        uint32_t r = lift_and(32, edx, 0x800fu, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    ebx = edx;
    lift_store(&env, ebp, 0xfffffffau, 2, (edx & 0xffffu));
    {
        uint32_t r = lift_or(32, ebx, eax, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xfffffffau, 2, (ebx & 0xffffu));
L_4e5305:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    edx = lift_load(&env, ebp, 0xfffffff8u, 4);
L_4e530b:
    esp = (ebp + 0xfffffffcu);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e532c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E532C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E532C_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5054a1u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e534d;
    edx = 0x4e5320u;
    ebx = 0x4e5328u;
    lift_store(&env, 0u, 0x50af08u, 4, edx);
    lift_store(&env, 0u, 0x50af0cu, 4, ebx);
L_4e534d:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x50af10u, 2)) & 0xffffu);
    eax = lift_call(&env, 0x4e83d2u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5678(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5678_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5678_STACK, 0, entry);
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
    edx = lift_load(&env, 0u, 0x5c8940u, 4);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e56a3;
    ebx = 0x5c8310u;
L_4e568d:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    eax = lift_call(&env, 0x4f1b3cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ecx = lift_load(&env, 0u, 0x5c8940u, 4);
    {
        uint32_t r = lift_add(32, ebx, 0x18u, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, esi, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e568d;
L_4e56a3:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e56a8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E56A8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E56A8_STACK, 0, entry);
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
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x5c8944u, 4);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e56e7;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
L_4e56bc:
    eax = lift_load(&env, 0u, 0x5c8948u, 4);
    ecx = lift_load(&env, ebx, eax + 0x0u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b3cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    eax = lift_load(&env, 0u, 0x5c8948u, 4);
    eax = lift_load(&env, ebx, eax + 0x0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edi = lift_load(&env, 0u, 0x5c8944u, 4);
    {
        uint32_t r = lift_add(32, ebx, 0x4u, &fl);
        ebx = r;
    }
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e56bc;
L_4e56e7:
    ebp = lift_load(&env, 0u, 0x5c8948u, 4);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4e56f8;
    eax = ebp;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
L_4e56f8:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e571c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E571C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E571C_STACK, 0, entry);
    eax = 0x5c81e0u;
    goto L_4e5810;
L_4e5810:
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5738(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5738_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5738_STACK, 0, entry);
    {
        uint32_t r = lift_and(32, eax, 0xfu, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x5c8200u, &fl);
        eax = r;
    }
    goto L_4e5810;
L_4e5810:
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5750(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5750_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5750_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    {
        uint32_t r = lift_and(32, eax, 0xfu, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x5c8200u, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4e5700u, eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    eax = lift_call(&env, 0x4e03fcu, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5774(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5774_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5774_STACK, 0, entry);
    eax = 0x5c8300u;
    goto L_4e5810;
L_4e5810:
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5788(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5788_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5788_STACK, 0, entry);
    eax = 0x5c81f0u;
    goto L_4e5810;
L_4e5810:
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e579c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E579C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E579C_STACK, 0, entry);
    eax = 0x5c8920u;
    goto L_4e5810;
L_4e5810:
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5808(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5808_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5808_STACK, 0, entry);
    eax = 0x5c8930u;
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5810(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5810_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5810_STACK, 0, entry);
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
    edx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e5832;
    ebx = (edx + 0xffffffffu);
    lift_store(&env, eax, 0xcu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e5832;
    esi = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, eax, 0x8u, 4, ebx);
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
L_4e5832:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e587c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E587C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E587C_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e58aa;
    eax = 0x1u;
    edx = lift_load(&env, 0u, 0x509768u, 4);
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e58aa;
    ebx = lift_load(&env, 0u, 0x509768u, 4);
    lift_store(&env, eax, 0x52u, 1, 0x1u);
    lift_store(&env, eax, 0xf0u, 4, ebx);
L_4e58aa:
    eax = edx;
    eax = lift_call(&env, 0x4e8620u, eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e58b8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E58B8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E58B8_STACK, 0, entry);
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
    ebx = lift_load(&env, 0u, 0x507c98u, 4);
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e5901;
    eax = lift_call(&env, 0x4f1cd4u, eax, edx, ebx, ecx, 0, esp);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x509731u, 2)) & 0xffffu);
    ebx = eax;
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x8000u, &fl);
    }
    if (fl.cf)
        goto L_4e5901;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x50972fu, 1), 0x4u, &fl);
    }
    if (!fl.cf)
        goto L_4e5901;
L_4e58e6:
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4e5901;
    {
        (void)lift_sub(32, ebx, 0x2u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e5901;
    lift_store(&env, 0u, 0x507c98u, 4, ebx);
    eax = lift_call(&env, 0x4f1cd4u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    goto L_4e58e6;
L_4e5901:
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x507c98u, 4, ebx);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5918(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5918_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5918_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, 0u, 0x507c98u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e592a;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e592a:
    eax = lift_call(&env, 0x4e587cu, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e5967;
    edx = ebx;
    eax = lift_load(&env, eax, 0xdau, 4);
    eax = lift_call(&env, 0x4e8510u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e5953;
    eax = ebx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e5953:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x507c98u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ce0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    eax = 0x1u;
L_4e5967:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e59f4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E59F4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E59F4_STACK, 0, entry);
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
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x4e5728u;
    ebx = 0x4e5738u;
    ecx = 0x4e5748u;
    esi = 0x4e5750u;
    edi = 0x4e5710u;
    ebp = 0x4e571cu;
    eax = 0x4e5794u;
    lift_store(&env, 0u, 0x507ca0u, 4, edx);
    lift_store(&env, 0u, 0x507ca4u, 4, ebx);
    lift_store(&env, 0u, 0x507ca8u, 4, ecx);
    lift_store(&env, 0u, 0x507cacu, 4, esi);
    lift_store(&env, 0u, 0x507cb0u, 4, edi);
    lift_store(&env, 0u, 0x507cb4u, 4, ebp);
    lift_store(&env, 0u, 0x507cc8u, 4, eax);
    edx = 0x4e579cu;
    ebx = 0x4e57acu;
    ecx = 0x4e5810u;
    esi = 0x4e5700u;
    edi = 0x4e576cu;
    ebp = 0x4e5780u;
    eax = 0x4e5774u;
    lift_store(&env, 0u, 0x507cccu, 4, edx);
    lift_store(&env, 0u, 0x509748u, 4, ebx);
    lift_store(&env, 0u, 0x50974cu, 4, ecx);
    lift_store(&env, 0u, 0x509750u, 4, esi);
    lift_store(&env, 0u, 0x507cb8u, 4, edi);
    lift_store(&env, 0u, 0x507cbcu, 4, ebp);
    lift_store(&env, 0u, 0x507cc0u, 4, eax);
    edx = 0x4e5788u;
    ebx = 0x1u;
    ecx = 0x4e57a4u;
    esi = 0x4e5808u;
    edi = 0x4e59c4u;
    lift_store(&env, 0u, 0x507cc4u, 4, edx);
    eax = lift_call(&env, 0x4e55d4u, eax, edx, ebx, ecx, 0, esp);
    edx = lift_load(&env, 0u, 0x5c7b9cu, 4);
    lift_store(&env, 0u, 0x5c8910u, 4, eax);
    lift_store(&env, 0u, 0x5c8914u, 4, ebx);
    lift_store(&env, 0u, 0x507cd0u, 4, ecx);
    lift_store(&env, 0u, 0x507cd4u, 4, esi);
    eax = lift_load(&env, edx, 0xdau, 4);
    lift_store(&env, 0u, 0x507cd8u, 4, edi);
    eax = lift_call(&env, 0x4e8510u, eax, edx, ebx, ecx, 0, esp);
    ebp = lift_load(&env, 0u, 0x5c7b9cu, 4);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x507c98u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ce0u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    lift_store(&env, 0u, 0x507c9cu, 4, 0x4e5838u);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e5cd1(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E5CD1_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E5CD1_STACK, 1, entry);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x14u, &fl);
        esp = r;
    }
    esi = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51bdccu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e5d16;
L_4e5d04:
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = esi;
    {
        uint32_t r = lift_add(32, esp, 0x14u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    return env.failed ? 0u : eax;
L_4e5d16:
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x20u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    eax = lift_call(&env, 0x4e5c2cu, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    esi = eax;
    goto L_4e5d04;
}

uint32_t lifted_f4e636c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E636C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E636C_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = edx;
    {
        (void)lift_sub(32, ebx, 0xau, &fl);
    }
    if (!fl.zf)
        goto L_4e637e;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e637e;
    {
        uint32_t a = eax;
        uint32_t r = lift_sub(32, 0, a, &fl);
        eax = r;
    }
    lift_store(&env, edx, 0x0u, 1, 0x2du);
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
L_4e637e:
    eax = lift_call(&env, 0x4e6320u, eax, edx, ebx, ecx, 0, esp);
    eax = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e6600(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6600_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6600_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    ebx = ((eax * 2u));
    eax = ebx;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e6624;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
L_4e6624:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e6cd4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6CD4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6CD4_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4e6cd5:
    edx = lift_load(&env, eax, 0x0u, 1);
    {
        (void)lift_sub(32, edx, 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4e6cf0;
    edx = lift_load(&env, eax, 0x1u, 1);
    {
        (void)lift_sub(32, edx, 0x25u, &fl);
    }
    if (!fl.zf)
        goto L_4e6cf0;
    eax = lift_load(&env, eax, 0x2u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    goto L_4e6cd5;
L_4e6cf0:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e70d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E70D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E70D0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = lift_call(&env, 0x4e9020u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e70fb;
    {
        (void)lift_sub(32, edx, 0x824fu, &fl);
    }
    if (fl.cf)
        goto L_4e70f5;
    {
        (void)lift_sub(32, edx, 0x8258u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e70f5;
    edx = 0x1u;
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e70f5:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e70fb:
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x507d58u, 1)) & 0xffu);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_and(8, (eax & 0xffu), 0x20u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7140_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7140_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = lift_call(&env, 0x4e9020u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e7168;
    {
        (void)lift_sub(32, edx, 0x8140u, &fl);
    }
    if (fl.zf)
        goto L_4e7159;
    {
        (void)lift_sub(32, edx, 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4e7162;
L_4e7159:
    edx = 0x1u;
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e7162:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e7168:
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_inc(8, a, &fl, 1);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x507d58u, 1)) & 0xffu);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_and(8, (eax & 0xffu), 0x2u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7280(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7280_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7280_STACK, 0, entry);
    eax = lift_call(&env, lift_load(&env, 0u, 0x509743u, 4), eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7540(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7540_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7540_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    edx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51bfbcu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, edx);
    lift_store(&env, edx, 0x0u, 4, 0x517454u);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, edx, 0x0u, 4, 0x51c024u);
    lift_store(&env, edx, 0x4u, 4, 0x0u);
    lift_store(&env, edx, 0x10u, 4, 0x0u);
    eax = lift_load(&env, edx, 0x10u, 4);
    lift_store(&env, edx, 0xcu, 4, eax);
    lift_store(&env, edx, 0x8u, 4, eax);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = edx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7660(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7660_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7660_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4e7670;
    lift_store(&env, eax, 0x10u, 4, ebx);
L_4e7670:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e768a;
    eax = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, esi);
    lift_store(&env, ecx, 0xcu, 4, esi);
    lift_store(&env, ecx, 0x8u, 4, esi);
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
    return env.failed ? 0u : eax;
L_4e768a:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e76b3;
    ebx = ((esi * 4u));
    eax = ebx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4c9ff0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0xcu, 4, esi);
    lift_store(&env, ecx, 0x8u, 4, esi);
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
    return env.failed ? 0u : eax;
L_4e76b3:
    {
        (void)lift_sub(32, esi, lift_load(&env, ecx, 0xcu, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e76e7;
    {
        (void)lift_sub(32, esi, lift_load(&env, ecx, 0x8u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e76df;
    ebx = esi;
    eax = lift_load(&env, ecx, 0x8u, 4);
    edx = lift_load(&env, ecx, 0x4u, 4);
    {
        uint32_t r = lift_sub(32, ebx, lift_load(&env, ecx, 0x8u, 4), &fl);
        ebx = r;
    }
    eax = ((eax * 4u));
    ebx = ((ebx * 4u));
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
L_4e76df:
    lift_store(&env, ecx, 0x8u, 4, esi);
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
    return env.failed ? 0u : eax;
L_4e76e7:
    eax = lift_load(&env, ecx, 0x10u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e772b;
    eax = lift_load(&env, ecx, 0x8u, 4);
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sbb(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e7711;
    {
        (void)lift_sub(32, eax, 0x400u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e7711;
    eax = 0x400u;
    goto L_4e772b;
L_4e7711:
    eax = lift_load(&env, ecx, 0x8u, 4);
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sbb(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e772b;
    eax = 0x4u;
L_4e772b:
    ebp = lift_load(&env, ecx, 0xcu, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    {
        (void)lift_sub(32, esi, ebp, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e7736;
    ebp = esi;
L_4e7736:
    eax = ((ebp * 4u));
    eax = lift_call(&env, 0x4c9ff0u, eax, edx, ebx, ecx, 0, esp);
    ebx = lift_load(&env, ecx, 0x8u, 4);
    edx = lift_load(&env, ecx, 0x4u, 4);
    ebx = ((ebx * 4u));
    edi = eax;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
    ebx = esi;
    eax = lift_load(&env, ecx, 0x8u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, ebx, lift_load(&env, ecx, 0x8u, 4), &fl);
        ebx = r;
    }
    eax = ((eax * 4u));
    ebx = ((ebx * 4u));
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, edi);
    lift_store(&env, ecx, 0x8u, 4, esi);
    lift_store(&env, ecx, 0xcu, 4, ebp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7850(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7850_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7850_STACK, 0, entry);
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
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    ebp = eax;
    ecx = 0xcu;
    edx = lift_load(&env, ebp, 0x10u, 4);
    eax = lift_load(&env, eax, 0x10u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    ebx = 0x51c06cu;
    edi = lift_load(&env, ebp, 0x14u, 4);
    esi = edx;
    {
        (void)lift_sub(32, edi, 0xf4fb7ea1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e7887;
    eax = 0xffffffffu;
    goto L_4e79f5;
L_4e7887:
    eax = lift_load(&env, ebp, 0x10u, 4);
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ecx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, edi, eax, &fl);
        edi = r;
    }
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e789f;
L_4e7897:
    {
        uint32_t r = lift_add(32, esi, 0xcu, &fl);
        esi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e7897;
L_4e789f:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e78b2;
    eax = 0xffffffffu;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
L_4e78b2:
    eax = (edi + 0x76cu);
    eax = lift_call(&env, 0x4e9060u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e78c6;
    ebx = 0x51c086u;
L_4e78c6:
    edx = (edi + 0x3u);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sbb(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = eax;
    eax = ((edi * 8u));
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    eax = 0x64u;
    edx = (edi + 0x63u);
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x0u, 4), &eax, &edx, &fl);
    edx = (edi + 0x12bu);
    {
        uint32_t r = lift_sub(32, ecx, eax, &fl);
        ecx = r;
    }
    edi = 0x190u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, ebx, (esi * 2u) + 0x0u, 2);
    edx = lift_load(&env, ebp, 0xcu, 4);
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edi = (eax + 0xffffffffu);
    edx = lift_load(&env, ebp, 0x8u, 4);
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebp, 0x4u, 4);
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    esi = lift_load(&env, ebp, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, esi, eax, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e7956;
L_4e794b:
    {
        uint32_t r = lift_add(32, esi, 0x15180u, &fl);
        esi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e794b;
L_4e7956:
    ecx = ebp;
    edx = esi;
    eax = edi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = lift_call(&env, 0x4e7a00u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4e960cu, eax, edx, ebx, ecx, 0, esp);
    ebx = lift_load(&env, 0u, 0x50b0dcu, 4);
    ecx = lift_load(&env, ebp, 0x20u, 4);
    {
        uint32_t r = lift_add(32, esi, ebx, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e797e;
    eax = ebp;
    eax = lift_call(&env, 0x4e91e0u, eax, edx, ebx, ecx, 0, esp);
L_4e797e:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0x20u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e798a;
    {
        uint32_t r = lift_sub(32, esi, lift_load(&env, 0u, 0x50b0e4u, 4), &fl);
        esi = r;
    }
L_4e798a:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e7997;
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
    {
        uint32_t r = lift_add(32, esi, 0x15180u, &fl);
        esi = r;
    }
    goto L_4e798a;
L_4e7997:
    {
        (void)lift_sub(32, edi, 0x63deu, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e79ae;
    eax = 0xffffffffu;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
L_4e79ae:
    if (!fl.zf)
        goto L_4e79d3;
    ebx = lift_load(&env, 0u, 0x50b0dcu, 4);
    {
        uint32_t r = lift_sub(32, esi, 0x15180u, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e79c4;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e79f3;
L_4e79c4:
    eax = 0xffffffffu;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
L_4e79d3:
    eax = (edi + 0xffff9c21u);
    edi = ((eax * 8u));
    {
        uint32_t r = lift_sub(32, edi, eax, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_add(32, edi, eax, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x7u, &fl);
        edi = r;
    }
    eax = edi;
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_sub(32, edi, eax, &fl);
        edi = r;
    }
    {
        uint32_t r = lift_add(32, esi, edi, &fl);
        esi = r;
    }
L_4e79f3:
    eax = esi;
L_4e79f5:
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7B50_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7B50_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e7b5d;
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e7b5d:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c8950u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e7b88;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x5c8961u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (edx & 0xffu), 0x1u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4e7b88;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x1u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e7b88;
    eax = 0x2u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e7b88:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7bf0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7BF0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7BF0_STACK, 0, entry);
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
    {
        (void)lift_and(8, lift_load(&env, eax, 0xdu, 1), 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_4e7c1d;
    eax = lift_load(&env, edx, 0x10u, 4);
    eax = lift_call(&env, 0x4e0a30u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e7c1d;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, edx, 0xdu, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (ebx & 0xffu), 0x20u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, edx, 0xdu, 1, (ebx & 0xffu));
    {
        (void)lift_and(8, (ebx & 0xffu), 0x7u, &fl);
    }
    if (!fl.zf)
        goto L_4e7c1d;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_or(8, (ecx & 0xffu), 0x2u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, edx, 0xdu, 1, (ecx & 0xffu));
L_4e7c1d:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7c30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7C30_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7C30_STACK, 0, entry);
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
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e7c44;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x507c34u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e7c58;
L_4e7c44:
    eax = 0x4u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4e7c58:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, 0u, 0x507c8cu, 4);
    eax = lift_load(&env, eax, (ebx * 4u) + 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1b6cu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e7c7c;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
    esi = 0xffffffffu;
L_4e7c7c:
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = esi;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7e44(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7E44_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7E44_STACK, 0, entry);
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
    ebx = eax;
    edx = 0x5c7760u;
L_4e7e4e:
    eax = lift_load(&env, edx, 0x0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e7e79;
    ecx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4e7e5f;
    edx = eax;
    goto L_4e7e4e;
L_4e7e5f:
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, 0xcu, 1)) & 0xffu);
    {
        uint32_t r = lift_or(8, (ecx & 0xffu), 0x3u, &fl);
        ecx = (ecx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, ebx, 0xcu, 1, (ecx & 0xffu));
    ebx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, edx, 0x0u, 4, ebx);
    edx = lift_load(&env, 0u, 0x5c7764u, 4);
    lift_store(&env, 0u, 0x5c7764u, 4, eax);
    lift_store(&env, eax, 0x0u, 4, edx);
L_4e7e79:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e7ef4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7EF4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7EF4_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    eax = lift_call(&env, 0x4e7fc4u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    eax = ebx;
    eax = lift_call(&env, 0x4e7e44u, eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e82d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E82D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E82D0_STACK, 0, entry);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4e82db;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4e82db;
    lift_mul1(32, ebx, &eax, &edx, &fl);
    return env.failed ? 0u : eax;
L_4e82db:
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
    lift_mul1(32, ecx, &eax, &edx, &fl);
    ecx = eax;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    lift_mul1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    lift_mul1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, edx, ecx, &fl);
        edx = r;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8310(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8310_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8310_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e831a;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e831a:
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x505234u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8400(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8400_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8400_STACK, 0, entry);
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
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4e5918u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e8420;
    edx = lift_load(&env, 0u, 0x507c98u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1cdcu, eax, edx, ebx, ecx, 1, esp);
    esp += 4u;
    ebx = eax;
L_4e8420:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e8433;
    edx = 0x1u;
    eax = 0x512ff8u;
    eax = lift_call(&env, 0x4e628cu, eax, edx, ebx, ecx, 0, esp);
L_4e8433:
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8620(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8620_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8620_STACK, 0, entry);
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
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e8644;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, eax, 0xcu, 4, 0x1u);
    eax = lift_call(&env, 0x4e6630u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4f1ba0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ebx, 0xdau, 4, eax);
L_4e8644:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e86fc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E86FC_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E86FC_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, eax, 0x4u, 4);
    edx = lift_load(&env, eax, 0x8u, 4);
    eax = lift_call(&env, 0x4e869cu, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8723;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e8719;
    lift_store(&env, 0u, 0x50aefcu, 4, edx);
    goto L_4e871c;
L_4e8719:
    lift_store(&env, ebx, 0x8u, 4, edx);
L_4e871c:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e8723;
    lift_store(&env, edx, 0x4u, 4, ebx);
L_4e8723:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e89e8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E89E8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E89E8_STACK, 0, entry);
    eax = lift_call(&env, 0x4e8978u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, 0u, 0x50af14u, 4);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e89f4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E89F4_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E89F4_STACK, 0, entry);
    eax = lift_call(&env, 0x4e8978u, eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, 0u, 0x50af18u, 4);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8aa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8AA0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8AA0_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = eax;
    eax = lift_call(&env, 0x4e8a7cu, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8ab5;
    eax = ebx;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4e8ab5:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8abc(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8ABC_STACK + 4 + 4 * 1 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8ABC_STACK, 1, entry);
    eax = lift_load(&env, esp, 0x4u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e8ace;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e8aed;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
L_4e8ace:
    eax = 0x4u;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8ae1;
    return env.failed ? 0u : eax;
L_4e8ae1:
    eax = 0x4u;
    eax = lift_call(&env, 0x4e8cc8u, eax, edx, ebx, ecx, 0, esp);
    goto L_4e8b0a;
L_4e8aed:
    eax = 0x7u;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e8b00;
    return env.failed ? 0u : eax;
L_4e8b00:
    eax = 0x7u;
    eax = lift_call(&env, 0x4e8cc8u, eax, edx, ebx, ecx, 0, esp);
L_4e8b0a:
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e8b14;
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4e8b19;
L_4e8b14:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    return env.failed ? 0u : eax;
L_4e8b19:
    eax = 0x1u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8b24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8B24_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8B24_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x4u;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    eax = 0x7u;
    eax = lift_call(&env, 0x4e8a58u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e8b45;
    {
        (void)lift_sub(32, edx, 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4e8b4f;
L_4e8b45:
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e8b56;
    {
        (void)lift_sub(32, eax, 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4e8b56;
L_4e8b4f:
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e8b56:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8d80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8D80_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8D80_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4e8b24u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e8dad;
    eax = lift_call(&env, 0x4e8b8cu, eax, edx, ebx, ecx, 0, esp);
    edx = 0x2u;
    eax = 0x4u;
    eax = lift_call(&env, 0x4e8a10u, eax, edx, ebx, ecx, 0, esp);
    edx = 0x2u;
    eax = 0x7u;
    eax = lift_call(&env, 0x4e8a10u, eax, edx, ebx, ecx, 0, esp);
L_4e8dad:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e8ff0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E8FF0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E8FF0_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
L_4e8ff6:
    eax = edx;
    eax = lift_call(&env, 0x4e7b50u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e900d;
    eax = edx;
    eax = lift_call(&env, 0x4e3a90u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    edx = eax;
    goto L_4e8ff6;
L_4e900d:
    eax = ebx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9020(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9020_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9020_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c8950u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e905b;
    edx = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x8u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x5c8961u, 1)) & 0xffu);
    {
        uint32_t r = lift_and(8, (edx & 0xffu), 0x1u, &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(32, edx, 0xffu, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4e905b;
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4ea310u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e905b;
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4e905b:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9060(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9060_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9060_STACK, 0, entry);
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
    ebx = eax;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4e9096;
    ecx = 0x64u;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_div1(32, ecx, &eax, &edx, &fl);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e9080;
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
L_4e9080:
    ecx = 0x190u;
    eax = ebx;
    lift_div1(32, ecx, &eax, &edx, &fl);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4e9096;
    eax = 0x1u;
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
    return env.failed ? 0u : eax;
L_4e9096:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e91e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E91E0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E91E0_STACK, 0, entry);
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
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x1cu, &fl);
        esp = r;
    }
    ecx = eax;
    eax = lift_load(&env, 0u, 0x50b0d8u, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e948c;
    edx = 0x50afacu;
    eax = 0x50af88u;
    ebx = lift_load(&env, ecx, 0x14u, 4);
    eax = lift_call(&env, 0x4e9194u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x14u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9222;
    edi = 0x50afacu;
    ebx = 0x50af88u;
    goto L_4e922c;
L_4e9222:
    edi = 0x50af88u;
    ebx = 0x50afacu;
L_4e922c:
    eax = lift_load(&env, ecx, 0x14u, 4);
    {
        uint32_t r = lift_add(32, eax, 0x76cu, &fl);
        eax = r;
    }
    ebp = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, 0x4e9060u, eax, edx, ebx, ecx, 0, esp);
    edx = ((ebp * 2u));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9255;
    eax = lift_load(&env, edx, 0x51c086u, 4);
    edx = lift_load(&env, edx, 0x51c084u, 4);
    goto L_4e9261;
L_4e9255:
    eax = lift_load(&env, edx, 0x51c06cu, 4);
    edx = lift_load(&env, edx, 0x51c06au, 4);
L_4e9261:
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, esp, 0x10u, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_load(&env, edi, 0x20u, 4);
    lift_store(&env, esp, 0x4u, 4, edx);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e932f;
    edx = lift_load(&env, edi, 0x10u, 4);
    {
        (void)lift_sub(32, ebp, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e928f;
    esi = 0x1u;
    goto L_4e9364;
L_4e928f:
    if (!fl.zf)
        goto L_4e9364;
    edx = lift_load(&env, ecx, 0x18u, 4);
    eax = lift_load(&env, edi, 0x18u, 4);
    {
        uint32_t r = lift_add(32, edx, 0x7u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x18u, 4, 0x7u);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x18u, 4), &eax, &edx, &fl);
    eax = lift_load(&env, ecx, 0xcu, 4);
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    edx = lift_load(&env, ecx, 0x18u, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        uint32_t r = lift_add(32, edx, 0x6u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, edx, lift_load(&env, edi, 0x18u, 4), &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x18u, 4, 0x7u);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, lift_load(&env, esp, 0x18u, 4), &eax, &edx, &fl);
    eax = lift_load(&env, ecx, 0xcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    edx = lift_load(&env, edi, 0xcu, 4);
    lift_store(&env, esp, 0xcu, 4, eax);
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_4e930b;
    eax = lift_load(&env, esp, 0x10u, 4);
    edx = lift_load(&env, esp, 0x8u, 4);
    {
        uint32_t r = lift_sub(32, eax, 0x7u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e9364;
    edx = lift_load(&env, esp, 0xcu, 4);
    esi = 0x1u;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e9364;
    goto L_4e936b;
L_4e930b:
    eax = (edx + 0xffffffffu);
    edx = ((eax * 8u));
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    eax = (edx + 0x1u);
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x8u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e9364;
    edx = lift_load(&env, esp, 0xcu, 4);
    esi = 0x1u;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e9364;
    goto L_4e936b;
L_4e932f:
    edx = lift_load(&env, edi, 0x1cu, 4);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4e9356;
    eax = lift_load(&env, ecx, 0x14u, 4);
    {
        uint32_t r = lift_add(32, eax, 0x76cu, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4e9060u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9355;
    eax = lift_load(&env, 0u, 0x51c06eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e9355;
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
L_4e9355:
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
L_4e9356:
    eax = lift_load(&env, ecx, 0x1cu, 4);
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e9364;
    esi = 0x1u;
    if (fl.zf)
        goto L_4e936b;
L_4e9364:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e9381;
L_4e936b:
    edx = edi;
    eax = ecx;
    eax = lift_call(&env, 0x4e949cu, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    esi = eax;
    {
        uint32_t r = lift_and(32, esi, 0xffu, &fl);
        esi = r;
    }
L_4e9381:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e9398;
    eax = lift_load(&env, esp, 0x14u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e948c;
    esi = eax;
    goto L_4e948c;
L_4e9398:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    edi = lift_load(&env, ebx, 0x20u, 4);
    lift_store(&env, esp, 0x0u, 4, edx);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4e9435;
    edi = lift_load(&env, ebx, 0x10u, 4);
    {
        (void)lift_sub(32, ebp, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e93b6;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    goto L_4e946d;
L_4e93b6:
    if (!fl.zf)
        goto L_4e946d;
    edx = lift_load(&env, ecx, 0x18u, 4);
    edi = lift_load(&env, ebx, 0x18u, 4);
    {
        uint32_t r = lift_add(32, edx, 0x7u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, edx, edi, &fl);
        edx = r;
    }
    edi = 0x7u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    ebp = lift_load(&env, ecx, 0xcu, 4);
    {
        uint32_t r = lift_sub(32, ebp, edx, &fl);
        ebp = r;
    }
    edx = lift_load(&env, ecx, 0x18u, 4);
    eax = lift_load(&env, ebx, 0x18u, 4);
    {
        uint32_t r = lift_add(32, edx, 0x6u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    eax = lift_load(&env, ecx, 0xcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, edx, &fl);
        eax = r;
    }
    edx = lift_load(&env, ebx, 0xcu, 4);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, edx, 0x5u, &fl);
    }
    if (!fl.zf)
        goto L_4e9417;
    edx = lift_load(&env, esp, 0x10u, 4);
    {
        uint32_t r = lift_sub(32, edx, edi, &fl);
        edx = r;
    }
    {
        (void)lift_sub(32, ebp, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e940e;
    esi = 0x1u;
    goto L_4e946d;
L_4e940e:
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e946d;
    goto L_4e9473;
L_4e9417:
    edi = (edx + 0xffffffffu);
    edx = ((edi * 8u));
    {
        uint32_t r = lift_sub(32, edx, edi, &fl);
        edx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    {
        (void)lift_sub(32, ebp, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e942f;
    esi = 0x1u;
    goto L_4e946d;
L_4e942f:
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e946d;
    goto L_4e9473;
L_4e9435:
    ebp = lift_load(&env, ebx, 0x20u, 4);
    edi = lift_load(&env, ebx, 0x1cu, 4);
    {
        (void)lift_sub(32, ebp, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4e9460;
    eax = lift_load(&env, ecx, 0x14u, 4);
    {
        uint32_t r = lift_add(32, eax, 0x76cu, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4e9060u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e945f;
    eax = lift_load(&env, 0u, 0x51c06eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e945f;
    {
        uint32_t r = lift_add(32, edi, ebp, &fl);
        edi = r;
    }
L_4e945f:
    {
        uint32_t a = edi;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edi = r;
    }
L_4e9460:
    eax = lift_load(&env, ecx, 0x1cu, 4);
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e946d;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9473;
L_4e946d:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e947e;
L_4e9473:
    edx = ebx;
    eax = ecx;
    eax = lift_call(&env, 0x4e949cu, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
L_4e947e:
    ebp = lift_load(&env, esp, 0x14u, 4);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4e948c;
    eax = ebp;
    {
        uint32_t r = lift_sub(32, eax, esi, &fl);
        eax = r;
    }
    esi = eax;
L_4e948c:
    eax = esi;
    lift_store(&env, ecx, 0x20u, 4, esi);
    {
        uint32_t r = lift_add(32, esp, 0x1cu, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9c94(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9C94_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9C94_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = lift_call(&env, 0x4e8660u, eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    eax = lift_call(&env, 0x4e9bd8u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e9ca8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9CA8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9CA8_STACK, 0, entry);
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
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t r = lift_add(32, eax, 0x7u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_and(8, (eax & 0xffu), 0xf8u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9cf4;
    lift_store(&env, edx, 0x0u, 4, eax);
    {
        uint32_t r = lift_add(32, eax, 0x3cu, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x0u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4e9cc5;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e9cc5:
    ecx = lift_load(&env, 0u, 0x50b218u, 4);
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.cf)
        goto L_4e9cd3;
    eax = ecx;
    {
        uint32_t r = lift_and(8, (eax & 0xffu), 0xfeu, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
L_4e9cd3:
    lift_store(&env, edx, 0x0u, 4, eax);
    {
        uint32_t r = lift_add(32, eax, 0xfffu, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, lift_load(&env, edx, 0x0u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4e9ce3;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4e9ce3:
    {
        uint32_t r = lift_xor(8, (eax & 0xffu), (eax & 0xffu), &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    {
        uint32_t r = lift_and(8, ((eax >> 8) & 0xffu), 0xf0u, &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    lift_store(&env, edx, 0x0u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
L_4e9cf4:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea13c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA13C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA13C_STACK, 0, entry);
    eax = lift_call(&env, lift_load(&env, 0u, 0x50b208u, 4), eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea144(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA144_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA144_STACK, 0, entry);
    eax = lift_call(&env, lift_load(&env, 0u, 0x50b20cu, 4), eax, edx, ebx, ecx, 0, esp);
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea2a8(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA2A8_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA2A8_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0xffu;
    eax = 0x5130c4u;
    eax = lift_call(&env, 0x4e628cu, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea6a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA6A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA6A0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x1u;
    eax = lift_call(&env, 0x4ea540u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ea6b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EA6B0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EA6B0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(8, (eax & 0xffu), 0x30u, &fl);
    }
    if (fl.cf)
        goto L_4ea6c3;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x39u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea6c3;
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, 0x30u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4ea6c3:
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4e82f0u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x61u, &fl);
    }
    if (fl.cf)
        goto L_4ea6e0;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x69u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea6e0;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_sub(32, eax, 0x57u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4ea6e0:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6au, &fl);
    }
    if (fl.cf)
        goto L_4ea6f2;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x72u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea6f2;
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, 0x57u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4ea6f2:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x73u, &fl);
    }
    if (fl.cf)
        goto L_4ea704;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x7au, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ea704;
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, eax, 0x57u, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4ea704:
    eax = 0x25u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eaa7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EAA7C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EAA7C_STACK, 0, entry);
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
    edi = eax;
    ebp = edx;
    esi = lift_load(&env, 0u, 0x5c81d4u, 4);
    goto L_4eab5b;
L_4eaa90:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, edi, 0x0u, 1)) & 0xffu) << 8);
    ebx = edi;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4eab58;
L_4eaa9c:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    eax = lift_call(&env, 0x4dabb0u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x0u, 1)) & 0xffu);
    eax = lift_call(&env, 0x4dabb0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (!fl.zf)
        goto L_4eab58;
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x3du, &fl);
    }
    if (!fl.zf)
        goto L_4eab4b;
    edx = lift_load(&env, 0u, 0x5c81d4u, 4);
    edi = esi;
    {
        uint32_t r = lift_sub(32, edi, edx, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        edi = r;
    }
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4eab42;
    edx = lift_load(&env, esi, 0x0u, 4);
    ecx = esi;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4eaaed;
L_4eaade:
    eax = lift_load(&env, ecx, 0x4u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    ebx = lift_load(&env, ecx, 0x4u, 4);
    {
        uint32_t r = lift_add(32, ecx, 0x4u, &fl);
        ecx = r;
    }
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4eaade;
L_4eaaed:
    esi = lift_load(&env, 0u, 0x5c81d0u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eab3a;
    eax = esi;
    {
        (void)lift_sub(8, lift_load(&env, edi, eax + 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4eab06;
    eax = edx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
L_4eab06:
    ebp = lift_load(&env, 0u, 0x5c81d4u, 4);
    esi = ecx;
    {
        uint32_t r = lift_sub(32, esi, ebp, &fl);
        esi = r;
    }
    edx = lift_load(&env, 0u, 0x5c81d0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        esi = r;
    }
    eax = ecx;
    ebx = esi;
    eax = lift_call(&env, 0x4e1140u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, 0u, 0x5c81d0u, 4, ecx);
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4eab3a;
    eax = (edi + ecx);
L_4eab2f:
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, eax, 0xffffffffu, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4eab2f;
L_4eab3a:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4eab42:
    eax = (edi + 0x1u);
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
    return env.failed ? 0u : eax;
L_4eab4b:
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebx, 0x1u, 1)) & 0xffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4eaa9c;
L_4eab58:
    {
        uint32_t r = lift_add(32, esi, 0x4u, &fl);
        esi = r;
    }
L_4eab5b:
    edx = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4eaa90;
    eax = lift_load(&env, 0u, 0x5c81d4u, 4);
    {
        uint32_t r = lift_sub(32, eax, esi, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB140_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB140_STACK, 0, entry);
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
    edi = eax;
    ebp = edx;
    esi = lift_load(&env, 0u, 0x5c81d8u, 4);
    goto L_4eb22b;
L_4eb154:
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, edi, 0x0u, 2)) & 0xffffu);
    ebx = edi;
    {
        (void)lift_and(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4eb228;
L_4eb162:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    eax = lift_call(&env, 0x4eb400u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x0u, 2)) & 0xffffu);
    eax = lift_call(&env, 0x4eb400u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(16, (ecx & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4eb228;
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x0u, 2), 0x3du, &fl);
    }
    if (!fl.zf)
        goto L_4eb215;
    edx = lift_load(&env, 0u, 0x5c81d8u, 4);
    edi = esi;
    {
        uint32_t r = lift_sub(32, edi, edx, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        edi = r;
    }
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4eb20c;
    edx = lift_load(&env, esi, 0x0u, 4);
    ecx = esi;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4eb1b7;
L_4eb1a8:
    eax = lift_load(&env, ecx, 0x4u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    ebx = lift_load(&env, ecx, 0x4u, 4);
    {
        uint32_t r = lift_add(32, ecx, 0x4u, &fl);
        ecx = r;
    }
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4eb1a8;
L_4eb1b7:
    esi = lift_load(&env, 0u, 0x5c81d0u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb204;
    eax = esi;
    {
        (void)lift_sub(8, lift_load(&env, edi, eax + 0x0u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4eb1d0;
    eax = edx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
L_4eb1d0:
    ebp = lift_load(&env, 0u, 0x5c81d8u, 4);
    esi = ecx;
    {
        uint32_t r = lift_sub(32, esi, ebp, &fl);
        esi = r;
    }
    edx = lift_load(&env, 0u, 0x5c81d0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        esi = r;
    }
    eax = ecx;
    ebx = esi;
    eax = lift_call(&env, 0x4e1140u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, 0u, 0x5c81d0u, 4, ecx);
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4eb204;
    eax = (edi + ecx);
L_4eb1f9:
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, eax, 0xffffffffu, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, edi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4eb1f9;
L_4eb204:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
L_4eb20c:
    eax = (edi + 0x1u);
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
    return env.failed ? 0u : eax;
L_4eb215:
    {
        uint32_t r = lift_add(32, edx, 0x2u, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0x2u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, ebx, 0x2u, &fl);
        ebx = r;
    }
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4eb162;
L_4eb228:
    {
        uint32_t r = lift_add(32, esi, 0x4u, &fl);
        esi = r;
    }
L_4eb22b:
    edx = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4eb154;
    eax = lift_load(&env, 0u, 0x5c81d8u, 4);
    {
        uint32_t r = lift_sub(32, eax, esi, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb250(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB250_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB250_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    eax = lift_call(&env, 0x4eb410u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4eb25f;
    {
        uint32_t r = lift_sub(32, edx, 0x21u, &fl);
        edx = r;
    }
L_4eb25f:
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb270(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB270_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB270_STACK, 0, entry);
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
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    ebx = edx;
    {
        (void)lift_sub(16, (edx & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4eb293;
L_4eb27d:
    edx = eax;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_and(16, (edi & 0xffffu), (edi & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4eb291;
    {
        (void)lift_sub(16, (ebx & 0xffffu), lift_load(&env, eax, 0x0u, 2), &fl);
    }
    if (fl.zf)
        goto L_4eb293;
    goto L_4eb27d;
L_4eb291:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4eb293:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb2a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB2A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB2A0_STACK, 0, entry);
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
    {
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    lift_store(&env, esp, 0x0u, 4, eax);
    edi = edx;
    {
        (void)lift_sub(16, lift_load(&env, 0u, 0x509731u, 2), 0x8000u, &fl);
    }
    if (!fl.cf)
        goto L_4eb2c6;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c98u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    goto L_4eb389;
L_4eb2c6:
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    ecx = (eax + 0x1u);
    eax = ecx;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    ebp = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4eb389;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4eb2eb;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    goto L_4eb316;
L_4eb2eb:
    eax = edi;
    eax = lift_call(&env, 0x4d8580u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    ecx = (eax + 0x1u);
    eax = ecx;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4eb316;
    eax = edx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
L_4eb316:
    edx = lift_load(&env, esp, 0x0u, 4);
    ebx = ecx;
    eax = ebp;
    eax = lift_call(&env, 0x4ea350u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4eb344;
    eax = ebp;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb339;
    eax = esi;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
L_4eb339:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
L_4eb344:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb36a;
    ebx = ecx;
    edx = edi;
    eax = esi;
    eax = lift_call(&env, 0x4ea350u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4eb36a;
    eax = esi;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
L_4eb36a:
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c94u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    edx = eax;
    eax = ebp;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb387;
    eax = esi;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
L_4eb387:
    eax = edx;
L_4eb389:
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb3a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB3A0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB3A0_STACK, 0, entry);
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
    esi = lift_load(&env, 0u, 0x5c81d4u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4eb3ef;
L_4eb3ae:
    edx = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t r = lift_add(32, esi, 0x4u, &fl);
        esi = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4eb3ef;
    eax = edx;
    eax = lift_call(&env, 0x4e8ff0u, eax, edx, ebx, ecx, 0, esp);
    ebx = (eax + 0x1u);
    eax = ((ebx * 2u));
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4eb3ae;
    eax = lift_call(&env, 0x4eada0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4eb3e6;
    eax = ecx;
    eax = lift_call(&env, 0x4eafb8u, eax, edx, ebx, ecx, 0, esp);
    goto L_4eb3ae;
L_4eb3e6:
    eax = ecx;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    goto L_4eb3ae;
L_4eb3ef:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb526(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB526_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB526_STACK, 0, entry);
    edx = eax;
    {
        uint32_t r = lift_and(32, edx, 0x7fffffffu, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4eb532;
    goto L_4eb57b;
L_4eb532:
    {
        (void)lift_sub(32, edx, 0x7f800000u, &fl);
    }
    if (!fl.zf)
        goto L_4eb546;
    edx = eax;
    {
        uint32_t r = lift_or(32, edx, 0x7ff00000u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    goto L_4eb57b;
L_4eb546:
    {
        (void)lift_and(32, edx, 0x7f800000u, &fl);
    }
    if (!fl.zf)
        goto L_4eb568;
    {
        uint32_t r = lift_xor(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
L_4eb553:
    {
        uint32_t r = lift_add(32, ecx, 0x800000u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, edx, edx, &fl);
        edx = r;
    }
    {
        (void)lift_and(32, edx, 0x800000u, &fl);
    }
    if (fl.zf)
        goto L_4eb553;
    {
        uint32_t r = lift_or(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, edx, ecx, &fl);
        edx = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
L_4eb568:
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_and(32, eax, 0xeu, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_ror(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, edx, 0x38000000u, &fl);
        edx = r;
    }
L_4eb57b:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb57c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB57C_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB57C_STACK, 0, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_and(32, edx, 0x7ff00000u, &fl);
    }
    if (!fl.zf)
        goto L_4eb587;
    {
        uint32_t r = lift_sub(32, edx, edx, &fl);
        edx = r;
    }
L_4eb587:
    {
        (void)lift_and(32, ecx, 0x7ff00000u, &fl);
    }
    if (!fl.zf)
        goto L_4eb591;
    {
        uint32_t r = lift_sub(32, ecx, ecx, &fl);
        ecx = r;
    }
L_4eb591:
    ebp = ecx;
    {
        uint32_t r = lift_xor(32, ebp, edx, &fl);
        ebp = r;
    }
    ebp = 0x0u;
    if (fl.sf)
        goto L_4eb5a8;
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4eb5a2;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
L_4eb5a2:
    if (fl.zf)
        goto L_4eb5b0;
    {
        uint32_t a = ecx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, ecx, &fl);
        edx = r;
    }
L_4eb5a8:
    {
        uint32_t r = lift_add(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_sbb(32, ebp, 0x0u, &fl);
        ebp = r;
    }
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebp = r;
    }
L_4eb5b0:
    eax = ebp;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb5c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB5C0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB5C0_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ebx;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (edx & 0xffff00ffu) | ((((edx & 0xffu)) & 0xffu) << 8);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((((edx >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((((edx >> 8) & 0xffu)) & 0xffu);
    eax = lift_call(&env, 0x4ec2d0u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eb606(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EB606_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EB606_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_and(32, edx, 0x7ff00000u, &fl);
    }
    if (fl.zf)
        goto L_4eb64e;
    {
        uint32_t r = lift_sub(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x20000000u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, 0x0u, &fl);
        edx = r;
    }
    if (fl.zf)
        goto L_4eb645;
    {
        (void)lift_sub(32, edx, 0x8fe00000u, &fl);
    }
    if (!fl.cf)
        goto L_4eb645;
    {
        (void)lift_sub(32, edx, 0x70200000u, &fl);
    }
    if (fl.cf)
        goto L_4eb64e;
    {
        uint32_t r = lift_sub(32, edx, 0x70000000u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_or(32, edx, ebx, &fl);
        edx = r;
    }
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4eb645:
    eax = 0x7f800000u;
    {
        uint32_t r = lift_or(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4eb64e:
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebb78(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBB78_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EBB78_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = lift_call(&env, 0x4ebb34u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebcd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBCD0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EBCD0_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_and(8, lift_load(&env, eax, 0xcu, 1), 0xefu, &fl);
        lift_store(&env, eax, 0xcu, 1, r);
    }
    edx = lift_load(&env, eax, 0x8u, 4);
    edx = lift_load(&env, edx, 0x8u, 4);
    lift_store(&env, eax, 0x4u, 4, 0x0u);
    lift_store(&env, eax, 0x0u, 4, edx);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ebe60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EBE60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EBE60_STACK, 0, entry);
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
    edx = eax;
    {
        (void)lift_and(8, lift_load(&env, eax, 0xcu, 1), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4ebe79;
    {
        (void)lift_and(8, lift_load(&env, edx, 0xdu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4ebe79;
    eax = edx;
    eax = lift_call(&env, 0x4dabd0u, eax, edx, ebx, ecx, 0, esp);
L_4ebe79:
    eax = lift_load(&env, edx, 0x10u, 4);
    eax = lift_call(&env, 0x4ec380u, eax, edx, ebx, ecx, 0, esp);
    ebx = eax;
    ecx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4ebeb4;
    eax = lift_load(&env, edx, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    esi = lift_load(&env, edx, 0x4u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4ebea9;
    {
        (void)lift_and(8, lift_load(&env, edx, 0xdu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4ebea5;
    ecx = (esi + ebx);
    goto L_4ebea9;
L_4ebea5:
    ecx = ebx;
    {
        uint32_t r = lift_sub(32, ecx, esi, &fl);
        ecx = r;
    }
L_4ebea9:
    eax = lift_load(&env, edx, 0x10u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = ecx;
L_4ebeb4:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC160_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC160_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    ebx = eax;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ec176;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
L_4ec176:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec1d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC1D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC1D0_STACK, 0, entry);
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
    ebx = (ebx & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), lift_load(&env, eax, 0x0u, 1), &fl);
    }
    if (fl.zf)
        goto L_4ec1e9;
L_4ec1d8:
    edx = eax;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        (void)lift_and(8, (ecx & 0xffu), (ecx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4ec1e7;
    {
        (void)lift_sub(8, (ebx & 0xffu), lift_load(&env, eax, 0x0u, 1), &fl);
    }
    if (fl.zf)
        goto L_4ec1e9;
    goto L_4ec1d8;
L_4ec1e7:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_4ec1e9:
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec1ec(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC1EC_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC1EC_STACK, 0, entry);
L_4e6e19:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, esp, 0x8u, 4);
    ebx = lift_load(&env, esp, 0xcu, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e6e4a;
    {
        (void)lift_and(8, lift_load(&env, edx, 0x4u, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e6e3a;
    {
        (void)lift_and(8, lift_load(&env, edx, 0x4u, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4e6e64;
    eax = lift_load(&env, ebx, 0x8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4e6e43;
L_4e6e3a:
    edx = ebx;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x4cd9f0u, eax, edx, ebx, ecx, 0, esp);
L_4e6e43:
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4e6e4a:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    ecx = lift_load(&env, 0u, 0x5c5c54u, 4);
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    eax = lift_load(&env, edx, 0x18u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, eax, 0x0u, 4, ecx);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4e6e64:
    eax = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t r = lift_and(32, eax, 0x3fffffffu, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0x25671234u, &fl);
    }
    if (!fl.zf)
        goto L_4e6e43;
    ecx = lift_load(&env, edx, 0x18u, 4);
    {
        (void)lift_sub(32, ebx, lift_load(&env, ecx, 0x2cu, 4), &fl);
    }
    if (fl.zf)
        goto L_4e6e90;
L_4e6e7a:
    eax = lift_load(&env, ecx, 0x34u, 4);
L_4e6e7d:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e6ea9;
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4e6ea9;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x2cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e6ea1;
L_4e6e8b:
    eax = lift_load(&env, eax, 0x8u, 4);
    goto L_4e6e7d;
L_4e6e90:
    lift_store(&env, ecx, 0x2cu, 4, 0x0u);
    goto L_4e6e7a;
L_4e6e99:
    edx = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, ecx, 0x2cu, 4, edx);
    goto L_4e6e8b;
L_4e6ea1:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0xcu, 1)) & 0xffu);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (!fl.cf)
        goto L_4e6eba;
L_4e6ea9:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e6ec3;
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4e6ec3;
    eax = (eax & 0xffff00ffu) | (((0x4u) & 0xffu) << 8);
L_4e6eb3:
    lift_store(&env, ecx, 0x24u, 1, ((eax >> 8) & 0xffu));
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4e6eba:
    if (fl.cf || fl.zf)
        goto L_4e6e99;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x7u, &fl);
    }
    if (fl.zf)
        goto L_4e6e99;
    goto L_4e6ea9;
L_4e6ec3:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x2cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e6eda;
L_4e6ec9:
    {
        (void)lift_sub(32, ebx, lift_load(&env, ecx, 0x30u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4e6e43;
    lift_store(&env, ecx, 0x24u, 1, 0x3u);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
L_4e6eda:
    edx = ebx;
    eax = ecx;
    eax = lift_call(&env, 0x4e8fa7u, eax, edx, ebx, ecx, 0, esp);
    eax = (eax & 0xffff00ffu) | ((((eax & 0xffu)) & 0xffu) << 8);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e6ec9;
    goto L_4e6eb3;
    goto L_4e6e19;
}

uint32_t lifted_f4ec2d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC2D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC2D0_STACK, 0, entry);
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec300;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), (edx & 0xffu), &fl);
    }
L_4ec2d6:
    {
        (void)lift_and(8, (eax & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4ec2e3;
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_ror(32, a, 0x8u, &fl);
        edx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4ec2d6;
L_4ec2e3:
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = lift_call(&env, 0x4ec307u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    {
        uint32_t r = lift_and(32, ecx, 0x3u, &fl);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec300;
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec300;
    lift_store(&env, eax, 0x1u, 1, ((edx >> 8) & 0xffu));
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    if (fl.zf)
        goto L_4ec300;
    lift_store(&env, eax, 0x2u, 1, (edx & 0xffu));
L_4ec300:
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec380(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC380_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC380_STACK, 0, entry);
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
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ec391;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x507c34u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ec3a4;
L_4ec391:
    eax = 0x4u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4ec3a4:
    edx = lift_load(&env, 0u, 0x507c8cu, 4);
    edx = lift_load(&env, edx, (ebx * 4u) + 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
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
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1ca8u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    edx = eax;
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, edx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4ec3d5;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
L_4ec3d5:
    eax = edx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC3E0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC3E0_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x4u, &fl);
        esp = r;
    }
    esi = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ec3f3;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x507c34u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ec404;
L_4ec3f3:
    eax = 0x4u;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    eax = 0xffffffffu;
    goto L_4ec472;
L_4ec404:
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x507d24u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ec437;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cfcu, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ec437;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507d24u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = edx;
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
L_4ec437:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (esp + 0x4u);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x507c8cu, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, eax, (esi * 4u) + 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4f1c78u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ec467;
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 1, esp);
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
L_4ec467:
    eax = esi;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_load(&env, esp, 0x0u, 4);
L_4ec472:
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec548(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC548_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC548_STACK, 0, entry);
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
    eax = lift_call(&env, 0x4ec578u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ec55f;
    eax = 0xffffffffu;
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
    return env.failed ? 0u : eax;
L_4ec55f:
    ebx = lift_load(&env, edx, 0x4u, 4);
    ecx = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, edx, 0x4u, 4, ebx);
    lift_store(&env, edx, 0x0u, 4, ecx);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0xffffffffu, 1)) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec578(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC578_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC578_STACK, 0, entry);
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
    ecx = eax;
    eax = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ec58e;
    eax = ecx;
    eax = lift_call(&env, 0x4e3b60u, eax, edx, ebx, ecx, 0, esp);
L_4ec58e:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0xdu, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4ec5a5;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x6u, &fl);
    }
    if (fl.zf)
        goto L_4ec5a5;
    eax = 0x2000u;
    eax = lift_call(&env, 0x4e3f28u, eax, edx, ebx, ecx, 0, esp);
L_4ec5a5:
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ecx, 0xcu, 1)) & 0xffu) << 8);
    {
        uint32_t r = lift_and(8, ((edx >> 8) & 0xffu), 0xfbu, &fl);
        edx = (edx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, ecx, 0xcu, 1, ((edx >> 8) & 0xffu));
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    eax = lift_load(&env, ecx, 0xcu, 4);
    {
        uint32_t r = lift_and(32, eax, 0x2400u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0x2400u, &fl);
    }
    if (!fl.zf)
        goto L_4ec5e8;
    ebx = lift_load(&env, ecx, 0x10u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4ec5e8;
    lift_store(&env, ecx, 0x4u, 4, ebx);
    eax = lift_call(&env, 0x4ecaa0u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4ec605;
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
    lift_store(&env, ecx, 0x4u, 4, 0x1u);
    goto L_4ec62a;
L_4ec5e8:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0xdu, 1), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4ec5f5;
    ebx = 0x1u;
    goto L_4ec5f8;
L_4ec5f5:
    ebx = lift_load(&env, ecx, 0x14u, 4);
L_4ec5f8:
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_call(&env, 0x4ec3e0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, eax);
L_4ec605:
    esi = lift_load(&env, ecx, 0x4u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ec62a;
    if (!fl.zf)
        goto L_4ec61a;
    {
        uint32_t r = lift_or(8, lift_load(&env, ecx, 0xcu, 1), 0x10u, &fl);
        lift_store(&env, ecx, 0xcu, 1, r);
    }
    eax = lift_load(&env, ecx, 0x4u, 4);
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
    return env.failed ? 0u : eax;
L_4ec61a:
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, ecx, 0xcu, 1)) & 0xffu) << 8);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    {
        uint32_t r = lift_or(8, ((ebx >> 8) & 0xffu), 0x20u, &fl);
        ebx = (ebx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    lift_store(&env, ecx, 0xcu, 1, ((ebx >> 8) & 0xffu));
L_4ec62a:
    eax = lift_load(&env, ecx, 0x4u, 4);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec8f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC8F0_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC8F0_STACK, 4, entry);
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4ecad0u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec910(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC910_STACK + 4 + 4 * 2 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC910_STACK, 2, entry);
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esp, 0x4u, 1)) & 0xffu);
    lift_store(&env, eax, 0x14u, 1, (edx & 0xffu));
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ec92d;
    eax = 0xfffffffdu;
    eax = lift_call(&env, 0x4ecb50u, eax, edx, ebx, ecx, 0, esp);
L_4ec92d:
    eax = 0x1u;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ec940(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC940_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC940_STACK, 0, entry);
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
    ebx = eax;
    {
        uint32_t v = 0x410u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4ec910u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ecaa0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECAA0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ECAA0_STACK, 0, entry);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x509718u, 4);
    eax = lift_call(&env, 0x4ed984u, eax, edx, ebx, ecx, 0, esp);
    edx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4ecabd;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4ecabd;
    eax = lift_call(&env, 0x4eda00u, eax, edx, ebx, ecx, 0, esp);
L_4ecabd:
    eax = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ecad0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECAD0_STACK + 4 + 4 * 4 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ECAD0_STACK, 4, entry);
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
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = lift_load(&env, esp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = 0xffffffffu;
    {
        uint32_t v = lift_load(&env, esp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t v = lift_load(&env, esp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = ebx;
    eax = lift_call(&env, 0x4e1990u, eax, edx, ebx, ecx, 4, esp);
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ecb34;
    edx = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, edx, 0x88u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ecb34;
    esi = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, esi, 0x54u, 4), eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ecb2b;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x1cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ecb22;
    eax = lift_load(&env, ebx, 0x1cu, 4);
    ebx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, ebx, 0x5cu, 4), eax, edx, ebx, ecx, 0, esp);
L_4ecb22:
    ebx = lift_load(&env, edi, 0x0u, 4);
    eax = edi;
    eax = lift_call(&env, lift_load(&env, ebx, 0x6cu, 4), eax, edx, ebx, ecx, 0, esp);
    goto L_4ecb32;
L_4ecb2b:
    esi = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    eax = lift_call(&env, lift_load(&env, esi, 0x58u, 4), eax, edx, ebx, ecx, 0, esp);
L_4ecb32:
    esi = eax;
L_4ecb34:
    eax = lift_call(&env, 0x4eda70u, eax, edx, ebx, ecx, 0, esp);
    eax = esi;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ecb50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECB50_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ECB50_STACK, 0, entry);
    {
        (void)lift_sub(32, eax, 0xfffffffdu, &fl);
    }
    if (!fl.zf)
        goto L_4ecb5c;
    eax = 0xffffffffu;
    goto L_4ecb87;
L_4ecb5c:
    {
        (void)lift_sub(32, eax, 0xfffffffeu, &fl);
    }
    if (fl.zf)
        goto L_4ecb87;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4ecb7b;
    eax = 0xfffffffdu;
    eax = lift_call(&env, 0x4e6f60u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    return env.failed ? 0u : eax;
L_4ecb7b:
    {
        (void)lift_sub(32, eax, 0x3a4u, &fl);
    }
    if (!fl.zf)
        goto L_4ecb87;
    eax = 0xfffffffcu;
L_4ecb87:
    eax = lift_call(&env, 0x4e6f60u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ecc60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECC60_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ECC60_STACK, 0, entry);
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
    ecx = eax;
    ebx = edx;
    {
        (void)lift_sub(32, edx, 0x1000u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ecc80;
    edx = 0x1000u;
    eax = lift_call(&env, 0x4ecc03u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_sub(32, ebx, 0x1000u, &fl);
        ebx = r;
    }
    goto L_4ecc98;
L_4ecc80:
    {
        (void)lift_sub(32, edx, 0xfffff000u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ecc98;
    edx = 0xfffff000u;
    eax = lift_call(&env, 0x4ecc03u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t r = lift_add(32, ebx, 0x1000u, &fl);
        ebx = r;
    }
L_4ecc98:
    edx = ebx;
    eax = ecx;
    eax = lift_call(&env, 0x4ecc03u, eax, edx, ebx, ecx, 0, esp);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eda00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDA00_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EDA00_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x8u, &fl);
        esp = r;
    }
    ebx = eax;
    edx = lift_load(&env, 0u, 0x507d38u, 4);
    lift_store(&env, esp, 0x4u, 1, (ebx & 0xffu));
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4eda2b;
    eax = 0x1u;
    edx = ebx;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cfcu, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, lift_load(&env, 0u, 0x507d38u, 4), eax, edx, ebx, ecx, 0, esp);
    goto L_4eda5b;
L_4eda2b:
    eax = 0x1u;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = lift_call(&env, 0x4e89f4u, eax, edx, ebx, ecx, 0, esp);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (esp + 0x4u);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (esp + 0x10u);
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
    eax = lift_call(&env, 0x4f1d04u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    eax = 0x1u;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
L_4eda5b:
    eax = ebx;
    {
        uint32_t r = lift_add(32, esp, 0x8u, &fl);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4edf7f(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDF7F_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EDF7F_STACK, 0, entry);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    {
        uint32_t r = lift_and(8, ((edx >> 8) & 0xffu), 0x7fu, &fl);
        edx = (edx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x7fffu, &fl);
    }
    if (!fl.zf)
        goto L_4edfaa;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4edfa3;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4edfa3;
    eax = 0x3u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4edfa3:
    eax = 0x2u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4edfaa:
    {
        (void)lift_and(16, lift_load(&env, eax, 0x8u, 2), 0x7fffu, &fl);
    }
    if (!fl.zf)
        goto L_4edfc8;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4edfc1;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4edfc1;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4edfc1:
    eax = 0x4u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
L_4edfc8:
    eax = 0x1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee670(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE670_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE670_STACK, 0, entry);
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
    ecx = eax;
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_call(&env, lift_load(&env, edx, 0x5cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = 0x2u;
    esi = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    ebx = 0x1u;
    eax = lift_call(&env, lift_load(&env, esi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    eax = ebx;
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee840(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE840_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE840_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x20u, &fl);
        esp = r;
    }
    ecx = eax;
    eax = esp;
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
    lift_store(&env, esp, 0x4u, 4, 0x4ec1ecu);
    lift_store(&env, esp, 0x8u, 4, 0x51c26cu);
    lift_store(&env, esp, 0xcu, 4, 0x0u);
    lift_store(&env, esp, 0x18u, 1, 0x0u);
    lift_store(&env, esp, 0x14u, 4, ecx);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    lift_store(&env, esp, 0xcu, 4, 0x1u);
    lift_store(&env, ecx, 0x0u, 4, 0x51c2d4u);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    lift_store(&env, ecx, 0x8u, 4, 0x11u);
    lift_store(&env, ecx, 0xcu, 4, 0x0u);
    lift_store(&env, ecx, 0x10u, 4, 0x0u);
    lift_store(&env, ecx, 0x14u, 4, 0x0u);
    lift_store(&env, ecx, 0x18u, 4, edx);
    eax = lift_load(&env, esp, 0x0u, 4);
    env.chain = eax;
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x20u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee8d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE8D0_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE8D0_STACK, 0, entry);
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
    ecx = eax;
    esi = edx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ee8eb;
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
L_4ee8eb:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4ee907;
    ebx = ((esi * 4u));
    eax = ebx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4c9ff0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
L_4ee907:
    lift_store(&env, ecx, 0x8u, 4, esi);
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
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee980(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE980_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE980_STACK, 0, entry);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_sub(32, esp, 0x30u, &fl);
        esp = r;
    }
    ecx = eax;
    {
        (void)lift_and(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4ee9af;
    lift_store(&env, esp, 0x20u, 4, 0x1u);
    edx = 0x51c2f0u;
    lift_store(&env, esp, 0x0u, 4, eax);
    eax = lift_call(&env, 0x4ccb9fu, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    eax = lift_call(&env, 0x4ca040u, eax, edx, ebx, ecx, 0, esp);
    goto L_4eea13;
L_4ee9af:
    lift_store(&env, eax, 0x0u, 4, 0x51c2d4u);
    lift_store(&env, esp, 0x24u, 4, eax);
    eax = (esp + 0x14u);
    lift_store(&env, esp, 0x28u, 1, (edx & 0xffu));
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
    lift_store(&env, esp, 0x1cu, 4, 0x51c278u);
    eax = ecx;
    lift_store(&env, esp, 0x20u, 4, 0x3u);
    eax = lift_call(&env, 0x4ee910u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, esp, 0x20u, 4, 0x0u);
    lift_store(&env, ecx, 0x0u, 4, 0x517454u);
    {
        (void)lift_and(8, (edx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4eea09;
    eax = ecx;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
L_4eea09:
    eax = lift_load(&env, esp, 0x14u, 4);
    env.chain = eax;
L_4eea13:
    eax = ecx;
    {
        uint32_t r = lift_add(32, esp, 0x30u, &fl);
        esp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4eea20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EEA20_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EEA20_STACK, 0, entry);
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
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4eea60;
    {
        uint32_t v = 0x10u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x18u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, 0x14u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_call(&env, 0x4e23e0u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    ecx = lift_load(&env, ebx, 0x18u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    edx = ecx;
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = ecx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4eea60;
L_4eea4e:
    ecx = lift_load(&env, ebx, 0x10u, 4);
    lift_store(&env, eax, 0x0u, 4, ecx);
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    lift_store(&env, ebx, 0x10u, 4, eax);
    {
        uint32_t r = lift_sub(32, eax, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4eea4e;
L_4eea60:
    esi = lift_load(&env, ebx, 0x10u, 4);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, ebx, 0x10u, 4, eax);
    {
        uint32_t a = lift_load(&env, ebx, 0xcu, 4);
        uint32_t r = lift_inc(32, a, &fl, 1);
        lift_store(&env, ebx, 0xcu, 4, r);
    }
    eax = lift_call(&env, 0x4ca060u, eax, edx, ebx, ecx, 0, esp);
    ebx = 0x4u;
    ecx = (esi + 0x8u);
    edx = eax;
    eax = ecx;
    eax = lift_call(&env, 0x4eb5e0u, eax, edx, ebx, ecx, 0, esp);
    eax = esi;
    lift_store(&env, esi, 0xcu, 4, 0x0u);
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
    return env.failed ? 0u : eax;
}
