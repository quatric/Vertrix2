/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_44.h"

uint32_t lifted_palette_cube(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PALETTE_CUBE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PALETTE_CUBE_STACK, 0, entry);
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
    esp = esp - 0x18u;
    edi = eax;
    edx = edx ^ edx;
    lift_store(&env, esp, 0x10u, 4, edx);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0x10u, 1)) & 0xffu);
    {
        uint32_t a = (eax & 0xffu);
        uint32_t r = lift_shl(8, a, 0x3u, &fl);
        eax = (eax & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, esp, 0xcu, 4, edx);
    lift_store(&env, esp, 0x14u, 1, (eax & 0xffu));
    ebp = 0x4u;
L_480cc5:
    eax = lift_load(&env, esp, 0xcu, 4);
    ebx = ebx ^ ebx;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0x14u, 1)) & 0xffu);
    lift_store(&env, esp, 0x4u, 4, ebx);
    lift_store(&env, esp, 0x0u, 4, eax);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, esp, 0x4u, 1)) & 0xffu) << 8);
    lift_store(&env, esp, 0x8u, 4, ebx);
    {
        uint32_t a = ((ecx >> 8) & 0xffu);
        uint32_t r = lift_shl(8, a, 0x3u, &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
L_480ce1:
    esi = lift_load(&env, esp, 0x0u, 4);
    ebx = (ebx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu)) & 0xffu) << 8);
    eax = eax ^ eax;
    edx = lift_load(&env, esp, 0x8u, 4);
    ebx = (ebx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    esi = esi | edx;
    {
        uint32_t a = (ebx & 0xffu);
        uint32_t r = lift_shl(8, a, 0x4u, &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
L_480cf3:
    edx = esi;
    edx = edx | eax;
    edx = (edx + (edx * 2u));
    lift_store(&env, edx, edi + 0x0u, 1, (ecx & 0xffu));
    lift_store(&env, edx, edi + 0x1u, 1, ((ebx >> 8) & 0xffu));
    eax = eax + 1u;
    lift_store(&env, edx, edi + 0x2u, 1, (ebx & 0xffu));
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) + 0x10u) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.cf)
        goto L_480cf3;
    ebx = lift_load(&env, esp, 0x8u, 4);
    esi = lift_load(&env, esp, 0x4u, 4);
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + 0x8u) & 0xffu) << 8);
    ebx = ebx + ebp;
    esi = esi + 1u;
    lift_store(&env, esp, 0x8u, 4, ebx);
    lift_store(&env, esp, 0x4u, 4, esi);
    {
        (void)lift_sub(32, esi, 0x8u, &fl);
    }
    if (fl.cf)
        goto L_480ce1;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esp, 0x14u, 1)) & 0xffu) << 8);
    edx = lift_load(&env, esp, 0xcu, 4);
    ecx = lift_load(&env, esp, 0x10u, 4);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) + 0x8u) & 0xffu) << 8);
    edx = edx + 0x20u;
    ecx = ecx + 1u;
    lift_store(&env, esp, 0x14u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, esp, 0xcu, 4, edx);
    lift_store(&env, esp, 0x10u, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0x8u, &fl);
    }
    if (fl.cf)
        goto L_480cc5;
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

uint32_t lifted_f491050(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F491050_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F491050_STACK, 0, entry);
    esp = esp - 0x4u;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_load(&env, 0u, 0x5bb764u, 4);
    ecx = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx & 0xfc0000u;
    edx = edx & 0xfc00u;
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        edx = r;
    }
    eax = eax & 0xfcu;
    edx = edx | ecx;
    eax = eax | edx;
    edx = lift_load(&env, 0u, 0x54b800u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = lift_load(&env, edx, (eax * 4u) + 0x0u, 4);
    lift_store(&env, 0u, 0x54d5d4u, 4, eax);
    eax = eax ^ eax;
    edx = lift_load(&env, 0u, 0x54cdc8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x54d5d4u, 1)) & 0xffu);
    eax = lift_load(&env, edx, (eax * 4u) + 0x0u, 4);
    lift_store(&env, 0u, 0x54d5d0u, 4, eax);
    eax = lift_load(&env, 0u, 0x54d5d4u, 4);
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        eax = r;
    }
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5dcu, 2)) & 0xffffu);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x54d5d0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        edx = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x0u, 1)) & 0xffu);
    ebx = lift_load(&env, 0u, 0x54d5d4u, 4);
    ecx = ecx ^ ecx;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ebx = r;
    }
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5deu, 2)) & 0xffffu);
    ecx = ecx + ebx;
    edx = edx & 0xffu;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ecx = r;
    }
    edx = edx | ecx;
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5d4u, 2)) & 0xffffu);
    ebx = ebx ^ ebx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | (((ecx & 0xffu)) & 0xffu);
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5e0u, 2)) & 0xffffu);
    ecx = ecx + ebx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        ecx = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    ecx = ecx | edx;
    edx = lift_load(&env, 0u, 0x5bb768u, 4);
    lift_store(&env, edx, 0x0u, 4, ecx);
    ebx = lift_load(&env, edx, 0x0u, 4);
    ecx = ecx & 0xfc0000u;
    ebx = ebx & 0xfc00u;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ebx = r;
    }
    ecx = ecx | ebx;
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx & 0xfcu;
    ebx = ebx | ecx;
    ecx = lift_load(&env, 0u, 0x54b804u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ebx = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, ebx + 0x0u, 1)) & 0xffu);
    ebx = lift_load(&env, 0u, 0x54cdccu, 4);
    ecx = ecx & 0xffu;
    ecx = lift_load(&env, ebx, (ecx * 4u) + 0x0u, 4);
    ecx = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, 0u, 0x54d5d4u, 4, ecx);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x18u, &fl);
        ecx = r;
    }
    ecx = ecx & 0xffu;
    ebx = ebx ^ ebx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    ecx = lift_load(&env, 0u, 0x54d5d4u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ecx = r;
    }
    lift_store(&env, esp, 0xcu, 4, ecx);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        ebx = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esp, 0xcu, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        ecx = r;
    }
    ebx = ebx | ecx;
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x54d5d4u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x8u, &fl);
        ecx = r;
    }
    ecx = ecx & 0xffu;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, eax + 0x0u, 1)) & 0xffu);
    eax = eax & 0xffu;
    eax = eax | ebx;
    lift_store(&env, edx, 0x0u, 4, eax);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    {
        uint32_t r = lift_add(32, esp, 0x4u, &fl);
        esp = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dae80(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DAE80_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DAE80_STACK, 0, entry);
    eax = 0xdu;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, eax, 0x4u, 4, edx);
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}
