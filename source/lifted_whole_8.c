/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_8.h"

uint32_t lifted_f424990(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F424990_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F424990_STACK, 0, entry);
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
    edx = lift_load(&env, 0u, 0x532a84u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_424d9d;
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x54061cu, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4249d6;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41d640u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x540620u, 4, edx);
    lift_store(&env, 0u, 0x532bd0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    ecx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x425ae0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54062cu, 4, ecx);
L_4249d6:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7d10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41d670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41df00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54061cu, 1, (ecx & 0xffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac1c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a44u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_424a09;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471b80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424a09:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532b40u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_424a17;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472d90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424a17:
    eax = lift_load(&env, 0u, 0x532b40u, 4);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_424a2d;
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x532b44u, 4), &fl);
    }
    if (fl.zf)
        goto L_424d6a;
L_424a2d:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x540620u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_424a46;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x540620u, 4, ebx);
L_424a46:
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4854a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_424a79;
    edx = lift_load(&env, 0u, 0x558c88u, 4);
    eax = lift_load(&env, 0u, 0x558c84u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x558c84u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424a79:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aaf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a44u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_424aa7;
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471ba0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424aa7:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41d6d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41dd60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486da0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487020u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41d660u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41de80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424ad7:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a38u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_424aef;
    eax = esi;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aca0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x540620u, 4, edx);
L_424aef:
    ecx = lift_load(&env, 0u, 0x532a44u, 4);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4251f7;
    {
        (void)lift_sub(32, ecx, lift_load(&env, 0u, 0x532a40u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4251f7;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471b90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x532a44u, 4, eax);
L_424b16:
    edx = lift_load(&env, 0u, 0x54062cu, 4);
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_424d57;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_424bd8;
    edx = 0x1u;
    eax = 0x54d640u;
    ecx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x532a24u, 4, ecx);
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) ^ ((ecx >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x54061cu, 1, ((ecx >> 8) & 0xffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4657f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5588f8u;
    edx = 0x7fu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477d70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, 0u, 0x4f88acu, 4);
    eax = 0x5588f8u;
    ebx = ebx + 0xbu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x74u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476120u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x75u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476120u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532a98u, 4);
    edx = lift_load(&env, 0u, 0x4f8188u, 4);
    ebx = lift_load(&env, 0u, 0x532b9cu, 4);
    lift_store(&env, 0u, 0x532a60u, 4, eax);
    edx = lift_load(&env, 0u, (edx * 4u) + 0x533164u, 4);
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x482a60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4254a0u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424bd8:
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b7cu, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_424c36;
    edx = edx ^ edx;
    eax = 0x54d640u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b7cu, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a7cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_424c36;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a80u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_424c36;
    lift_store(&env, 0u, 0x532bd0u, 4, 0x1u);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    edx = 0x425260u;
    lift_store(&env, 0u, 0x54061cu, 1, (eax & 0xffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x46f220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424c36:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532b3cu, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_425213;
L_424c43:
    edx = 0x3eu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_424c6a;
    edx = 0x3eu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471e60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424c6a:
    edx = 0x42u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_424c91;
    edx = 0x42u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471e80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424c91:
    edx = 0x3fu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_424cd3;
    edx = 0x3fu;
    eax = 0x54d640u;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ebx;
    eax = ebx;
    lift_store(&env, 0u, 0x532a3cu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x2u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424cd3:
    edx = 0x40u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_424d15;
    edx = 0x40u;
    eax = 0x54d640u;
    edi = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = edi;
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x532a3cu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x2u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424d15:
    edx = 0x41u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_424d57;
    edx = 0x41u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x1u;
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x532a3cu, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471ea0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424d57:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a3cu, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_42522f;
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
L_424d6a:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x415530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x415550u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x472d50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5588f8u;
    edx = 0x4259d0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(8, (edx & 0xffu), (edx & 0xffu), &fl);
        edx = (edx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, 0u, 0x54061cu, 1, (edx & 0xffu));
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
L_424d9d:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x54061cu, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_424df3;
    eax = esi;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41d640u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x540620u, 4, ecx);
    lift_store(&env, 0u, 0x532bd0u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x425ae0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a24u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_424de4;
    eax = 0x5bb4ecu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb524u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424de4:
    eax = eax ^ eax;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    lift_store(&env, 0u, 0x532a24u, 4, eax);
    lift_store(&env, 0u, 0x54061cu, 1, (edx & 0xffu));
L_424df3:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7d10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41d670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41df00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb508u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_424fd1;
    edx = 0x5bb524u;
    eax = 0x5bb594u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d3e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x473af0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb524u;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f172cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5bb594u;
    lift_store(&env, 0u, 0x5bb534u, 4, eax);
    lift_store(&env, 0u, 0x5bb548u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4737d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c0f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424e58:
    eax = lift_load(&env, 0u, 0x5bb50cu, 4);
    ecx = lift_load(&env, 0u, 0x5bb508u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (!fl.zf)
        goto L_424e6e;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x473960u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424e6e:
    eax = 0x5bb254u;
    ebx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48c370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac1c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5bb710u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ebx, lift_load(&env, 0u, 0x532a44u, 4), &fl);
    }
    if (!fl.zf)
        goto L_424e9a;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471b80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424e9a:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x540620u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_424eb3;
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x540620u, 4, edx);
L_424eb3:
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4854a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_424ee6;
    edx = lift_load(&env, 0u, 0x558c88u, 4);
    eax = lift_load(&env, 0u, 0x558c84u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x558c84u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x485520u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424ee6:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41aaf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486d00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a44u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_424f14;
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471ba0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424f14:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41d6d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41dd60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486da0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487020u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487060u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41d660u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41de80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f172cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = lift_load(&env, 0u, 0x5bb548u, 4);
    edx = eax;
    ecx = lift_load(&env, 0u, 0x5bb550u, 4);
    edx = edx - edi;
    ebx = lift_load(&env, 0u, 0x5bb508u, 4);
    ecx = ecx + edx;
    edx = lift_load(&env, 0u, 0x5bb534u, 4);
    lift_store(&env, 0u, 0x5bb54cu, 4, eax);
    eax = eax - edx;
    ebx = ebx + 1u;
    lift_store(&env, 0u, 0x540624u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb518u, 4);
    {
        uint32_t r = lift_imul(32, eax, ebx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb508u, 4, ebx);
    lift_store(&env, 0u, 0x540628u, 4, eax);
    eax = lift_load(&env, 0u, 0x540624u, 4);
    edi = lift_load(&env, 0u, 0x540628u, 4);
    lift_store(&env, 0u, 0x5bb550u, 4, ecx);
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (!fl.cf)
        goto L_424fb7;
    edx = lift_load(&env, 0u, 0x540624u, 4);
    eax = edi;
    eax = eax - edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7db0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_424fb7:
    eax = lift_load(&env, 0u, 0x5bb508u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x5bb50cu, 4), &fl);
    }
    if (fl.zf)
        goto L_424fe2;
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x54062cu, 4, ebx);
    goto L_424ad7;
L_424fd1:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f172cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5bb548u, 4, eax);
    goto L_424e58;
L_424fe2:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x424790u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_424ffb;
    {
        uint32_t r = lift_xor(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
        ebx = (ebx & 0xffffff00u) | ((r) & 0xffu);
    }
    lift_store(&env, 0u, 0x54061cu, 1, (ebx & 0xffu));
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
L_424ffb:
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x424890u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4251d8;
    edx = 0x5bb55cu;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48bca0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5bb594u;
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48be70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x5bb570u, 4);
    lift_store(&env, 0u, 0x5bb538u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f172cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x5bb534u, 4);
    eax = eax - edx;
    ebx = lift_load(&env, 0u, 0x5bb50cu, 4);
    lift_store(&env, 0u, 0x540624u, 4, eax);
    edx = edx ^ edx;
    eax = lift_load(&env, 0u, 0x5bb550u, 4);
    lift_div1(32, ebx, &eax, &edx, &fl);
    lift_store(&env, 0u, 0x5bb550u, 4, eax);
    eax = 0x5bb254u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x480030u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5bb254u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x480070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = lift_load(&env, 0u, 0x5bb550u, 4);
    lift_store(&env, 0u, 0x5bb53cu, 4, eax);
    lift_div1(32, edi, &eax, &edx, &fl);
    eax = eax + 1u;
    lift_store(&env, 0u, 0x5bb544u, 4, eax);
    {
        (void)lift_sub(32, eax, 0xffu, &fl);
    }
    if (!fl.cf)
        goto L_4251e6;
L_42508e:
    lift_store(&env, 0u, 0x5bb544u, 4, eax);
    eax = 0x5bb4ecu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48d480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb594u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4ecu, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb595u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4edu, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb596u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4eeu, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb597u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4efu, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb598u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4f0u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb599u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4f1u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb59au, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4f2u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb59bu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4f3u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb564u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4f4u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb565u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4f5u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb566u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4f6u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb567u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4f7u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb568u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4f8u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb569u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4f9u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb56au, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb4fau, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb56bu, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x5bb588u, 4);
    lift_store(&env, 0u, 0x5bb4fbu, 1, (eax & 0xffu));
    eax = lift_load(&env, 0u, 0x5bb5c0u, 4);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4251f0;
L_425150:
    edx = lift_load(&env, 0u, 0x5bb5c0u, 4);
    {
        uint32_t r = lift_imul(32, edx, lift_load(&env, 0u, 0x5bb5b4u, 4), &fl);
        edx = r;
    }
    ebx = lift_load(&env, 0u, 0x5bb57cu, 4);
    lift_store(&env, 0u, 0x5bb518u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb588u, 4);
    {
        uint32_t r = lift_imul(32, eax, ebx, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_425176;
    eax = edx;
L_425176:
    ebx = lift_load(&env, 0u, 0x5bb518u, 4);
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5bb50cu, 4, eax);
    lift_div1(32, ebx, &eax, &edx, &fl);
    lift_store(&env, 0u, 0x5bb50cu, 4, eax);
    {
        uint32_t r = lift_imul(32, eax, ebx, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, eax, 0x3e8u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4251a3;
    eax = 0x1u;
    lift_store(&env, 0u, 0x5bb518u, 4, eax);
    lift_store(&env, 0u, 0x5bb50cu, 4, eax);
L_4251a3:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a08u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4251c9;
    eax = lift_load(&env, 0u, 0x5bb53cu, 4);
    ebx = lift_load(&env, 0u, 0x5bb518u, 4);
    lift_store(&env, 0u, 0x532a10u, 4, eax);
    eax = lift_load(&env, 0u, 0x5bb50cu, 4);
    {
        uint32_t r = lift_imul(32, eax, ebx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x532a14u, 4, eax);
L_4251c9:
    lift_store(&env, 0u, 0x54062cu, 4, 0x1u);
    goto L_424ad7;
L_4251d8:
    {
        uint32_t r = lift_xor(8, ((edx >> 8) & 0xffu), ((edx >> 8) & 0xffu), &fl);
        edx = (edx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    lift_store(&env, 0u, 0x54061cu, 1, ((edx >> 8) & 0xffu));
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
L_4251e6:
    eax = 0xffu;
    goto L_42508e;
L_4251f0:
    eax = edx;
    goto L_425150;
L_4251f7:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a44u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_424b16;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a3cu, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_42522f;
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
L_425213:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532b38u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_424c43;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a3cu, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_42522f;
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
L_42522f:
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x54061cu, 1, ((eax >> 8) & 0xffu));
    eax = 0x5588f8u;
    edx = 0x425810u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
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

uint32_t lifted_player_preview_frames(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PLAYER_PREVIEW_FRAMES_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PLAYER_PREVIEW_FRAMES_STACK, 0, entry);
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
    ecx = edx;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x425de0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, esi, 0x188u, 4);
    edx = edx ^ edx;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_42b0d0;
    eax = esi;
L_42b0ad:
    ebx = lift_load(&env, eax, 0x15cu, 4);
    ecx = ecx + 0x4u;
    ebx = lift_load(&env, ebx, 0xb8u, 4);
    lift_store(&env, ecx, 0xfffffffcu, 4, ebx);
    edx = edx + 1u;
    edi = lift_load(&env, esi, 0x188u, 4);
    eax = eax + 0x4u;
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (fl.cf)
        goto L_42b0ad;
L_42b0d0:
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

uint32_t lifted_scene_layout(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_SCENE_LAYOUT_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_SCENE_LAYOUT_STACK, 0, entry);
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
    esp = esp - 0xb0u;
    ecx = eax;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff68u, 4, edx);
    lift_store(&env, ebp, 0xffffff50u, 4, edx);
    lift_store(&env, ebp, 0xffffff6cu, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff50u, 4);
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    {
        uint32_t r = lift_imul(32, edx, 0x18u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffff94u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
L_430966:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    lift_store(&env, ebp, 0xffffff78u, 4, edi);
    {
        uint32_t r = lift_imul(32, edi, 0x18u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, ebp, 0xffffff70u, 4, eax);
L_430989:
    esi = lift_load(&env, ebp, 0xffffff70u, 4);
    esi = esi + lift_load(&env, ebp, 0xffffff78u, 4);
    ebx = lift_load(&env, esi, 0x220u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_431065;
L_4309a3:
    esi = lift_load(&env, ebp, 0xffffff78u, 4);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    esi = esi + 0x4u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffff78u, 4, esi);
    esi = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = eax + 1u;
    esi = esi + 0x18u;
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    lift_store(&env, ebp, 0xffffffccu, 4, esi);
    {
        (void)lift_sub(32, edi, 0xdu, &fl);
    }
    if (fl.cf)
        goto L_430989;
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    edi = lift_load(&env, ebp, 0xffffffd4u, 4);
    ebx = lift_load(&env, ebp, 0xffffff94u, 4);
    esi = lift_load(&env, ebp, 0xffffff50u, 4);
    edx = edx + 0x34u;
    edi = edi + 0x18u;
    ebx = ebx + 0xdu;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    lift_store(&env, ebp, 0xffffff94u, 4, ebx);
    lift_store(&env, ebp, 0xffffff50u, 4, esi);
    {
        (void)lift_sub(32, esi, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_430966;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffff50u, 4, eax);
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffff50u, 4), 0x18u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffff3cu, 4, ecx);
    lift_store(&env, ebp, 0xffffff40u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
L_430a17:
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    lift_store(&env, ebp, 0xffffff74u, 4, edi);
    {
        uint32_t r = lift_imul(32, edi, 0x18u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff40u, 4);
    lift_store(&env, ebp, 0xffffff7cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff3cu, 4);
    lift_store(&env, ebp, 0xffffff54u, 4, eax);
L_430a43:
    esi = lift_load(&env, ebp, 0xffffff54u, 4);
    esi = esi + lift_load(&env, ebp, 0xffffff74u, 4);
    eax = lift_load(&env, esi, 0x87cu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_430aec;
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = eax;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffff7cu, 4);
    edx = edx + ebx;
    eax = (eax & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x15cu, 1)) & 0xffffu);
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffff7cu, 4);
    lift_store(&env, esi, 0xeu, 2, (edx & 0xffffu));
    ebx = lift_load(&env, ebp, 0xffffffb4u, 4);
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x19du, 1)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    eax = eax + ebx;
    eax = eax + edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x44u, 1)) & 0xffu);
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(8, (edx & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_430aec;
    ebx = (ebp + 0xffffff6cu);
    edx = (ebp + 0xffffff68u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x18u;
    edx = lift_load(&env, ebp, 0xffffff68u, 4);
    eax = eax - edx;
    edx = eax;
    eax = lift_load(&env, esi, 0xcu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax + edx;
    lift_store(&env, esi, 0xeu, 2, (eax & 0xffffu));
    edx = 0x18u;
    ebx = lift_load(&env, ebp, 0xffffff6cu, 4);
    eax = lift_load(&env, esi, 0x14u, 4);
    edx = edx - ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    eax = eax + edx;
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
L_430aec:
    esi = lift_load(&env, ebp, 0xffffff74u, 4);
    eax = lift_load(&env, ebp, 0xffffff7cu, 4);
    esi = esi + 0x4u;
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffff74u, 4, esi);
    esi = lift_load(&env, ebp, 0xffffffb4u, 4);
    eax = eax + 1u;
    esi = esi + 0x18u;
    lift_store(&env, ebp, 0xffffff7cu, 4, eax);
    lift_store(&env, ebp, 0xffffffb4u, 4, esi);
    {
        (void)lift_sub(32, edi, 0xdu, &fl);
    }
    if (fl.cf)
        goto L_430a43;
    edx = lift_load(&env, ebp, 0xffffff3cu, 4);
    edi = lift_load(&env, ebp, 0xffffffd8u, 4);
    ebx = lift_load(&env, ebp, 0xffffff40u, 4);
    esi = lift_load(&env, ebp, 0xffffff50u, 4);
    edx = edx + 0x34u;
    edi = edi + 0x18u;
    ebx = ebx + 0xdu;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffff3cu, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, edi);
    lift_store(&env, ebp, 0xffffff40u, 4, ebx);
    lift_store(&env, ebp, 0xffffff50u, 4, esi);
    {
        (void)lift_sub(32, esi, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_430a17;
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffff50u, 4, eax);
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffff50u, 4), 0x18u, &fl);
        eax = r;
    }
    edi = ecx;
    lift_store(&env, ebp, 0xffffff8cu, 4, ecx);
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
L_430b6f:
    edx = lift_load(&env, edi, 0x988u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_430c06;
    ebx = lift_load(&env, ebp, 0xffffffbcu, 4);
    eax = lift_load(&env, ebp, 0xffffff8cu, 4);
    esi = edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x99cu, 1)) & 0xffffu);
    edx = edx + ebx;
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffff8cu, 4);
    lift_store(&env, esi, 0xeu, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x9a1u, 1)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    eax = eax + 0x138u;
    eax = eax + edx;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, esi, 0x44u, 1)) & 0xffu) << 8);
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_430c06;
    ebx = (ebp + 0xffffff6cu);
    edx = (ebp + 0xffffff68u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x18u;
    ebx = lift_load(&env, ebp, 0xffffff68u, 4);
    eax = lift_load(&env, esi, 0xcu, 4);
    edx = edx - ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    eax = eax + edx;
    lift_store(&env, esi, 0xeu, 2, (eax & 0xffffu));
    eax = 0x18u;
    edx = lift_load(&env, ebp, 0xffffff6cu, 4);
    eax = eax - edx;
    edx = eax;
    eax = lift_load(&env, esi, 0x14u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax + edx;
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
L_430c06:
    esi = lift_load(&env, ebp, 0xffffffbcu, 4);
    ebx = lift_load(&env, ebp, 0xffffff8cu, 4);
    esi = esi + 0x18u;
    edi = edi + 0x4u;
    lift_store(&env, ebp, 0xffffffbcu, 4, esi);
    esi = lift_load(&env, ebp, 0xffffff50u, 4);
    ebx = ebx + 1u;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffff8cu, 4, ebx);
    lift_store(&env, ebp, 0xffffff50u, 4, esi);
    {
        (void)lift_sub(32, esi, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_430b6f;
    edi = edi ^ edi;
    {
        uint32_t r = lift_imul(32, edi, 0x18u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffff48u, 4, ecx);
    lift_store(&env, ebp, 0xffffff44u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
L_430c43:
    eax = lift_load(&env, ebp, 0xffffff48u, 4);
    edx = lift_load(&env, eax, 0x9e8u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_430ce4;
    eax = lift_load(&env, ebp, 0xffffff44u, 4);
    esi = edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x9a6u, 1)) & 0xffffu);
    edx = edx - 0x18u;
    edx = edx + eax;
    lift_store(&env, esi, 0xeu, 2, (edx & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffff44u, 4);
    eax = (eax & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x9b3u, 1)) & 0xffffu);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x44u, 1)) & 0xffu);
    lift_store(&env, esi, 0x16u, 2, (edx & 0xffffu));
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_430ce4;
    ebx = (ebp + 0xffffff6cu);
    edx = (ebp + 0xffffff68u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x18u;
    ebx = lift_load(&env, ebp, 0xffffff68u, 4);
    eax = lift_load(&env, esi, 0xcu, 4);
    edx = edx - ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    eax = eax + edx;
    lift_store(&env, esi, 0xeu, 2, (eax & 0xffffu));
    eax = 0x18u;
    edx = lift_load(&env, ebp, 0xffffff6cu, 4);
    eax = eax - edx;
    edx = eax;
    eax = lift_load(&env, esi, 0x14u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax + edx;
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
L_430ce4:
    ebx = lift_load(&env, ebp, 0xffffff48u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = lift_load(&env, ebp, 0xffffff44u, 4);
    edi = edi + 1u;
    ebx = ebx + 0x4u;
    edx = edx + 0x18u;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffff48u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    lift_store(&env, ebp, 0xffffff44u, 4, esi);
    {
        (void)lift_sub(32, edi, 0xdu, &fl);
    }
    if (fl.cf)
        goto L_430c43;
    edi = edi ^ edi;
    {
        uint32_t r = lift_imul(32, edi, 0x18u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffff88u, 4, ecx);
    lift_store(&env, ebp, 0xffffff98u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
L_430d21:
    eax = lift_load(&env, ebp, 0xffffff88u, 4);
    edx = lift_load(&env, eax, 0xa2cu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_430db7;
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    esi = edx;
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x9c0u, 1)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    eax = eax + 0x78u;
    eax = eax + edx;
    lift_store(&env, esi, 0xeu, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    ebx = lift_load(&env, ebp, 0xffffffd0u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x9cdu, 1)) & 0xffffu);
    edx = edx + ebx;
    edx = edx + eax;
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, esi, 0x44u, 1)) & 0xffu) << 8);
    lift_store(&env, esi, 0x16u, 2, (edx & 0xffffu));
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_430db7;
    ebx = (ebp + 0xffffff6cu);
    edx = (ebp + 0xffffff68u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x18u;
    ebx = lift_load(&env, ebp, 0xffffff68u, 4);
    eax = lift_load(&env, esi, 0xcu, 4);
    edx = edx - ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    eax = eax + edx;
    lift_store(&env, esi, 0xeu, 2, (eax & 0xffffu));
    edx = 0x18u;
    edx = edx - lift_load(&env, ebp, 0xffffff6cu, 4);
    eax = lift_load(&env, esi, 0x14u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax + edx;
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
L_430db7:
    edx = lift_load(&env, ebp, 0xffffff88u, 4);
    esi = lift_load(&env, ebp, 0xffffffd0u, 4);
    ebx = lift_load(&env, ebp, 0xffffff98u, 4);
    edi = edi + 1u;
    edx = edx + 0x4u;
    esi = esi + 0x18u;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffff88u, 4, edx);
    lift_store(&env, ebp, 0xffffffd0u, 4, esi);
    lift_store(&env, ebp, 0xffffff98u, 4, ebx);
    {
        (void)lift_sub(32, edi, 0xdu, &fl);
    }
    if (fl.cf)
        goto L_430d21;
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffff50u, 4, esi);
    {
        uint32_t r = lift_imul(32, lift_load(&env, ebp, 0xffffff50u, 4), 0x18u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffa8u, 4, ecx);
    lift_store(&env, ebp, 0xffffff4cu, 4, ecx);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
L_430df5:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = lift_load(&env, ebp, 0xffffff4cu, 4);
    edi = edi ^ edi;
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    lift_store(&env, ebp, 0xffffff64u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffff4cu, 4);
    edx = lift_load(&env, ebp, 0xffffffa8u, 4);
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
    lift_store(&env, ebp, 0xffffff80u, 4, eax);
    lift_store(&env, ebp, 0xffffff90u, 4, eax);
    lift_store(&env, ebp, 0xffffff84u, 4, edx);
    {
        uint32_t r = lift_imul(32, edi, 0x18u, &fl);
        eax = r;
    }
L_430e2c:
    edx = lift_load(&env, ebp, 0xffffff84u, 4);
    edx = edx + esi;
    ebx = lift_load(&env, edx, 0x324u, 4);
    lift_store(&env, ebp, 0xffffff58u, 4, edx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_430e96;
    edx = lift_load(&env, ebp, 0xffffffa0u, 4);
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, edx, 0x15cu, 1)) & 0xffffu);
    ebx = lift_load(&env, ebp, 0xffffffb0u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    edx = edx + ebx;
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ebx = ebx + edx;
    edx = lift_load(&env, ebp, 0xffffff58u, 4);
    edx = lift_load(&env, edx, 0x324u, 4);
    lift_store(&env, edx, 0xeu, 2, (ebx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffffa0u, 4);
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, edx, 0x19du, 1)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = edx + eax;
    ebx = ebx + edx;
    edx = lift_load(&env, ebp, 0xffffff58u, 4);
    edx = lift_load(&env, edx, 0x324u, 4);
    lift_store(&env, edx, 0x16u, 2, (ebx & 0xffffu));
L_430e96:
    edx = lift_load(&env, ebp, 0xffffff84u, 4);
    edx = edx + esi;
    ebx = lift_load(&env, edx, 0x328u, 4);
    lift_store(&env, ebp, 0xffffff5cu, 4, edx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_430f07;
    edx = lift_load(&env, ebp, 0xffffff80u, 4);
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, edx, 0x15cu, 1)) & 0xffffu);
    ebx = lift_load(&env, ebp, 0xffffffb8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    edx = edx + ebx;
    edx = edx + lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = edx + 0xcu;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff5cu, 4);
    edx = lift_load(&env, edx, 0x328u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, edx, 0xeu, 2, (ebx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffff80u, 4);
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, edx, 0x19du, 1)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = edx + eax;
    ebx = ebx + edx;
    edx = lift_load(&env, ebp, 0xffffff5cu, 4);
    edx = lift_load(&env, edx, 0x328u, 4);
    lift_store(&env, edx, 0x16u, 2, (ebx & 0xffffu));
L_430f07:
    edx = lift_load(&env, ebp, 0xffffff84u, 4);
    edx = edx + esi;
    ebx = lift_load(&env, edx, 0x32cu, 4);
    lift_store(&env, ebp, 0xffffff60u, 4, edx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_430f7a;
    edx = lift_load(&env, ebp, 0xffffff90u, 4);
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, edx, 0x15cu, 1)) & 0xffffu);
    ebx = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    edx = edx + ebx;
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ebx = ebx + edx;
    edx = lift_load(&env, ebp, 0xffffff60u, 4);
    edx = lift_load(&env, edx, 0x32cu, 4);
    lift_store(&env, edx, 0xeu, 2, (ebx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffff90u, 4);
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, edx, 0x19du, 1)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = edx + eax;
    edx = edx + ebx;
    edx = edx + 0xcu;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff60u, 4);
    edx = lift_load(&env, edx, 0x32cu, 4);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, edx, 0x16u, 2, (ebx & 0xffffu));
L_430f7a:
    edx = lift_load(&env, ebp, 0xffffff84u, 4);
    edx = edx + esi;
    ebx = lift_load(&env, edx, 0x330u, 4);
    lift_store(&env, ebp, 0xffffff9cu, 4, edx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_430fed;
    edx = lift_load(&env, ebp, 0xffffff64u, 4);
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, edx, 0x15cu, 1)) & 0xffffu);
    ebx = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    edx = edx + ebx;
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ebx = ebx + edx;
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    edx = lift_load(&env, edx, 0x330u, 4);
    ebx = ebx + 0xcu;
    lift_store(&env, edx, 0xeu, 2, (ebx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffff64u, 4);
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, edx, 0x19du, 1)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = edx + eax;
    edx = edx + ebx;
    edx = edx + 0xcu;
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    edx = lift_load(&env, edx, 0x330u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, edx, 0x16u, 2, (ebx & 0xffffu));
L_430fed:
    edx = lift_load(&env, ebp, 0xffffffa0u, 4);
    ebx = lift_load(&env, ebp, 0xffffff80u, 4);
    esi = esi + 0x10u;
    eax = eax + 0x18u;
    edi = edi + 1u;
    edx = edx + 1u;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffa0u, 4, edx);
    lift_store(&env, ebp, 0xffffff80u, 4, ebx);
    edx = lift_load(&env, ebp, 0xffffff90u, 4);
    ebx = lift_load(&env, ebp, 0xffffff64u, 4);
    edx = edx + 1u;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffff90u, 4, edx);
    lift_store(&env, ebp, 0xffffff64u, 4, ebx);
    {
        (void)lift_sub(32, edi, 0xdu, &fl);
    }
    if (fl.cf)
        goto L_430e2c;
    esi = lift_load(&env, ebp, 0xffffffa8u, 4);
    edi = lift_load(&env, ebp, 0xffffff4cu, 4);
    eax = lift_load(&env, ebp, 0xffffff50u, 4);
    esi = esi + 0xd0u;
    edi = edi + 0xdu;
    eax = eax + 1u;
    lift_store(&env, ebp, 0xffffffa8u, 4, esi);
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xffffff4cu, 4, edi);
    esi = esi + 0x18u;
    lift_store(&env, ebp, 0xffffff50u, 4, eax);
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_430df5;
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
L_431065:
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    esi = ebx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0xeu, 2)) & 0xffffu);
    ebx = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = (eax & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x15cu, 1)) & 0xffffu);
    edx = edx + ebx;
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, esi, 0xeu, 2, (edx & 0xffffu));
    ebx = lift_load(&env, ebp, 0xffffffccu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ecx, 0x16u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x19du, 1)) & 0xffffu);
    edx = edx + ebx;
    edx = edx + eax;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esi, 0x44u, 1)) & 0xffu) << 8);
    lift_store(&env, esi, 0x16u, 2, (edx & 0xffffu));
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4309a3;
    ebx = (ebp + 0xffffff6cu);
    edx = (ebp + 0xffffff68u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b14c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x18u;
    edx = lift_load(&env, ebp, 0xffffff68u, 4);
    eax = eax - edx;
    edx = eax;
    eax = lift_load(&env, esi, 0xcu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax + edx;
    lift_store(&env, esi, 0xeu, 2, (eax & 0xffffu));
    edx = 0x18u;
    ebx = lift_load(&env, ebp, 0xffffff6cu, 4);
    eax = lift_load(&env, esi, 0x14u, 4);
    edx = edx - ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    eax = eax + edx;
    lift_store(&env, esi, 0x16u, 2, (eax & 0xffffu));
    goto L_4309a3;
}

uint32_t lifted_pattern_tables(const VertrixCalls *calls, const VertrixFactoryServices *services,
                               const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_PATTERN_TABLES_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_PATTERN_TABLES_STACK, 0, entry);
    goto L_441f20;
L_441eea:
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
L_441f20:
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
    esp = esp - 0x30u;
    edi = eax;
    ecx = 0x1u;
    edx = edx ^ edx;
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffbcu, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 1, ((eax >> 8) & 0xffu));
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    ebx = 0xbu;
    edx = edx ^ edx;
    eax = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    lift_store(&env, 0u, 0x5440f6u, 1, (edx & 0xffu));
    edx = (edx & 0xffff00ffu) | (((0x4u) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffffc4u, 4, ebx);
    lift_store(&env, 0u, 0x5440f7u, 1, ((edx >> 8) & 0xffu));
L_441f67:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffdcu, 2)) & 0xffffu);
    {
        (void)lift_sub(32, eax, 0x6u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_441ff4;
    esi = esi ^ esi;
L_441f78:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    {
        (void)lift_sub(32, eax, 0x100u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_441eea;
    eax = eax ^ eax;
L_441f8a:
    ecx = ecx ^ ecx;
    edx = edx ^ edx;
    ecx = (ecx & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x4fba48u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.zf)
        goto L_441fa1;
    eax = eax + 1u;
    {
        (void)lift_sub(32, eax, 0x73u, &fl);
    }
    if (fl.cf)
        goto L_441f8a;
L_441fa1:
    {
        (void)lift_sub(32, eax, 0x73u, &fl);
    }
    if (fl.zf)
        goto L_4420f8;
L_441faa:
    edx = edx ^ edx;
    ecx = lift_load(&env, 0u, (eax * 4u) + 0x54414cu, 4);
    edx = (edx & 0xffff0000u) | (((esi & 0xffffu)) & 0xffffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x544318u, 1)) & 0xffu);
    esi = esi + 1u;
    lift_store(&env, 0u, (edx * 4u) + 0x54438cu, 4, ecx);
    lift_store(&env, edx, 0x544790u, 1, (eax & 0xffu));
    goto L_441f78;
L_441fcc:
    edx = lift_load(&env, ebp, 0xffffffc4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffccu, 4);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) ^ (ebx & 0xffu)) & 0xffu);
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffe4u, 1, (ebx & 0xffu));
    ecx = ecx + 0xbu;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = edx + 0xbu;
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    goto L_441f67;
L_441ff4:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
L_441ffa:
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffc8u, 4), &fl);
    }
    if (!fl.cf)
        goto L_441fcc;
    ecx = lift_load(&env, ebp, 0xffffffccu, 4);
    esi = esi ^ esi;
L_442007:
    edx = lift_load(&env, ebp, 0xffffffbcu, 4);
    ebx = ecx;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478f10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_442020;
    ebx = lift_load(&env, ebp, 0xffffffc0u, 4);
    ecx = ecx + 1u;
    esi = esi + 1u;
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.cf)
        goto L_442007;
L_442020:
    {
        (void)lift_sub(32, esi, 0xau, &fl);
    }
    if (!fl.zf)
        goto L_4420da;
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xffffffe4u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_442034;
L_44202f:
    lift_store(&env, ebp, 0xffffffbcu, 4, lift_load(&env, ebp, 0xffffffbcu, 4) + 1u);
    goto L_441ffa;
L_442034:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffbcu, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5440f6u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffe8u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_44204c;
    lift_store(&env, 0u, 0x5440f6u, 1, (eax & 0xffu));
L_44204c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), lift_load(&env, 0u, 0x5440f7u, 1), &fl);
    }
    if (fl.cf)
        goto L_4420b1;
L_442057:
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffd8u, 2)) & 0xffffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    lift_store(&env, ecx, 0x544318u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, eax, 0xau, &fl);
        eax = r;
    }
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    lift_store(&env, 0u, (ecx * 4u) + 0x54414cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
L_442087:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
L_44208f:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, ecx, eax, &fl);
    }
    if (!fl.cf)
        goto L_4420b8;
    edx = edx ^ edx;
    ebx = lift_load(&env, ebp, 0xffffffd0u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe0u, 2)) & 0xffffu);
    eax = edi;
    edx = edx + ecx;
    esi = esi + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478f10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = ecx + 1u;
    lift_store(&env, esi, 0xffffffffu, 1, (eax & 0xffu));
    goto L_44208f;
L_4420b1:
    lift_store(&env, 0u, 0x5440f7u, 1, (eax & 0xffu));
    goto L_442057;
L_4420b8:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + 1u;
    edx = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_442087;
    esi = lift_load(&env, ebp, 0xffffffd8u, 4);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) ^ (ebx & 0xffu)) & 0xffu);
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffffe4u, 1, (ebx & 0xffu));
    lift_store(&env, ebp, 0xffffffd8u, 4, esi);
    lift_store(&env, ebp, 0xffffffbcu, 4, lift_load(&env, ebp, 0xffffffbcu, 4) + 1u);
    goto L_441ffa;
L_4420da:
    {
        (void)lift_sub(8, lift_load(&env, ebp, 0xffffffe4u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_44202f;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    lift_store(&env, ebp, 0xffffffe4u, 1, (ecx & 0xffu));
    lift_store(&env, ebp, 0xffffffe0u, 2, (eax & 0xffffu));
    lift_store(&env, ebp, 0xffffffbcu, 4, lift_load(&env, ebp, 0xffffffbcu, 4) + 1u);
    goto L_441ffa;
L_4420f8:
    eax = 0x53u;
    goto L_441faa;
}

uint32_t lifted_display_ready(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_DISPLAY_READY_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_DISPLAY_READY_STACK, 0, entry);
    goto L_47f410;
L_47ed00:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_47f410:
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_47ed00;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_47ed00;
    eax = 0x1u;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f48b970(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F48B970_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F48B970_STACK, 0, entry);
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
    edx = lift_load(&env, 0u, 0x5bb4a4u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_48ba7b;
L_48b982:
    esi = lift_load(&env, 0u, 0x5bb47cu, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_48b99b;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb47cu, 4, eax);
L_48b99b:
    edx = lift_load(&env, 0u, 0x5bb480u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_48b9b5;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, 0u, 0x5bb480u, 4, ebx);
L_48b9b5:
    esi = lift_load(&env, 0u, 0x5bb484u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_48b9ce;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb484u, 4, eax);
L_48b9ce:
    edx = lift_load(&env, 0u, 0x5bb488u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_48b9e8;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, 0u, 0x5bb488u, 4, ebx);
L_48b9e8:
    esi = lift_load(&env, 0u, 0x5bb48cu, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_48ba01;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb48cu, 4, eax);
L_48ba01:
    edx = lift_load(&env, 0u, 0x5bb490u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_48ba1b;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, 0u, 0x5bb490u, 4, ebx);
L_48ba1b:
    esi = lift_load(&env, 0u, 0x5bb494u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_48ba34;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb494u, 4, eax);
L_48ba34:
    edx = lift_load(&env, 0u, 0x5bb498u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_48ba4e;
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, 0u, 0x5bb498u, 4, ebx);
L_48ba4e:
    esi = lift_load(&env, 0u, 0x5bb49cu, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_48ba67;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb49cu, 4, eax);
L_48ba67:
    edx = lift_load(&env, 0u, 0x5bb4a0u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_48ba90;
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
L_48ba7b:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, 0u, 0x5bb4a4u, 4, ebx);
    goto L_48b982;
L_48ba90:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b2cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, 0u, 0x5bb4a0u, 4, ebx);
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
}

uint32_t lifted_f4b17e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B17E0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B17E0_STACK, 0, entry);
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
    edx = lift_load(&env, eax, 0x13cu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4b1d35;
L_4b17f6:
    eax = lift_load(&env, esi, 0xb4u, 4);
    lift_store(&env, 0u, 0x5bb734u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4b1d44;
    ebx = lift_load(&env, 0u, 0x5bc010u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4b1d30;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebx, 0xcu, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0xdu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb732u, 1, (edx & 0xffu));
    lift_store(&env, 0u, 0x5bb733u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a4u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb740u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x16u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a6u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bb742u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x1eu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7aeu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xf4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7b4u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xf8u, 2)) & 0xffffu);
    ebx = (ebx & 0xffffff00u) | ((0x4u) & 0xffu);
    lift_store(&env, 0u, 0x5bb7b6u, 2, (eax & 0xffffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x8eu, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) ^ (edx & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x5bbffeu, 1, (eax & 0xffu));
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bb739u, 1, (edx & 0xffu));
    lift_store(&env, 0u, 0x5bb790u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x94u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb731u, 1, (ebx & 0xffu));
    lift_store(&env, 0u, 0x5bc00cu, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x8cu, 1)) & 0xffu);
    edx = (edx & 0xffff00ffu) | (((0x64u) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb73au, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x80u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc00eu, 1, ((edx >> 8) & 0xffu));
    lift_store(&env, 0u, 0x5bb7b8u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4b1941;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x208u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb744u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x20cu, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb746u, 2, (edx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x214u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    ebx = ebx - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x216u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x226u, 2)) & 0xffffu);
    ecx = ecx - edx;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (ebx & 0xffffu));
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bb7aeu, 2, (edx & 0xffffu));
L_4b1941:
    lift_store(&env, 0u, 0x5bb730u, 1, 0xdu);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4b19ca;
    eax = lift_load(&env, 0u, 0x5bb73eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1d4b;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb740u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb744u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b197b;
    eax = ebx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb740u, 2, (eax & 0xffffu));
L_4b197b:
    eax = lift_load(&env, 0u, 0x5bb740u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1d59;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb742u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb746u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b19a6;
    eax = edx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb742u, 2, (eax & 0xffffu));
L_4b19a6:
    edx = lift_load(&env, 0u, 0x5bb742u, 4);
    eax = lift_load(&env, 0u, 0x5bb740u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    eax = lift_load(&env, 0u, 0x5bb73eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = edx + eax;
    lift_store(&env, 0u, 0x5bb73cu, 4, edx);
L_4b19ca:
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1d67;
L_4b19d3:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x44u, 1)) & 0xffu);
L_4b19d6:
    lift_store(&env, 0u, 0x5bb738u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bb738u, 1), 0x10u, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, 0u, 0x5bb70cu, 4, eax);
    {
        (void)lift_sub(32, edi, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1da6;
L_4b19f8:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x52u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0x48u, 2)) & 0xffffu);
L_4b1a04:
    lift_store(&env, 0u, 0x5bc002u, 2, (eax & 0xffffu));
L_4b1a0a:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb70cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1e31;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb74cu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb74eu, 2, (eax & 0xffffu));
L_4b1a2f:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74cu, 2)) & 0xffffu);
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb750u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7aeu, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74cu, 2)) & 0xffffu);
    ebx = ebx - eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    eax = eax + ecx;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bb748u, 2, (eax & 0xffffu));
    eax = ebx;
    lift_store(&env, 0u, 0x5bb752u, 2, (edx & 0xffffu));
    eax = eax + edx;
    lift_store(&env, 0u, 0x5bb7a2u, 2, (ebx & 0xffffu));
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bbff4u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bb74au, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bbffeu, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bbff2u, 2, (eax & 0xffffu));
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b1b35;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1eb5;
    ebx = ebx ^ ebx;
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    lift_store(&env, 0u, 0x5bbff6u, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bbffau, 2, (ebx & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    edx = edx - 1u;
    eax = eax - 1u;
    lift_store(&env, 0u, 0x5bbff8u, 2, (edx & 0xffffu));
L_4b1ae3:
    lift_store(&env, 0u, 0x5bbffcu, 2, (eax & 0xffffu));
L_4b1ae9:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff8u, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b1d44;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1d44;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffcu, 2), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4b1d44;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffau, 2), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1d44;
L_4b1b35:
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) ^ (eax & 0xffu)) & 0xffu);
    lift_store(&env, 0u, 0x5bc014u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bbffeu, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b1f27;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbffau, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b1b9b;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb70cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1b87;
    eax = lift_load(&env, 0u, 0x5bbff8u, 4);
    edx = lift_load(&env, 0u, 0x5bb7a0u, 4);
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
    eax = eax - edx;
    edx = eax;
    eax = lift_load(&env, 0u, 0x5bb74au, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb790u, 4, lift_load(&env, 0u, 0x5bb790u, 4) + eax);
L_4b1b87:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffau, 2)) & 0xffffu);
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    lift_store(&env, 0u, 0x5bb7a2u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, (edx & 0xffu));
L_4b1b9b:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), lift_load(&env, 0u, 0x5bbff6u, 2), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4b1be8;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5bb70cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1bd4;
    edx = lift_load(&env, 0u, 0x5bbff4u, 4);
    eax = lift_load(&env, 0u, 0x5bb79eu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x5bb790u, 4);
    edx = edx - eax;
    ebx = ebx + edx;
    lift_store(&env, 0u, 0x5bb790u, 4, ebx);
L_4b1bd4:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff6u, 2)) & 0xffffu);
    edx = (edx & 0xffff00ffu) | (((0x1u) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb7a0u, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, ((edx >> 8) & 0xffu));
L_4b1be8:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbffcu, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b1c08;
    lift_store(&env, 0u, 0x5bb74au, 2, (ebx & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, 0x1u);
L_4b1c08:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bbff8u, 2)) & 0xffffu);
    {
        (void)lift_sub(16, (eax & 0xffffu), (ecx & 0xffffu), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4b1f27;
    lift_store(&env, 0u, 0x5bb748u, 2, (ecx & 0xffffu));
    lift_store(&env, 0u, 0x5bc014u, 1, 0x1u);
L_4b1c2c:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb748u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | (((eax & 0xffffu) - lift_load(&env, 0u, 0x5bb7a0u, 2)) & 0xffffu);
    eax = eax + 1u;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7a2u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb750u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74au, 2)) & 0xffffu);
    eax = eax - edx;
    eax = eax + 1u;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb750u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb752u, 2, (eax & 0xffffu));
    {
        (void)lift_and(16, (ebx & 0xffffu), (ebx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4b1d44;
L_4b1c6f:
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bb798u, 2, (edx & 0xffffu));
    edx = lift_load(&env, 0u, 0x5bb796u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = lift_load(&env, 0u, 0x5bb796u, 4);
    lift_store(&env, 0u, 0x5bb7bcu, 4, edx);
    edx = lift_load(&env, 0u, 0x5bb74eu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = ecx - edx;
    edx = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, 0u, 0x5bb7c4u, 4, edx);
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb732u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edx, ecx, &fl);
        edx = r;
    }
    lift_store(&env, 0u, 0x5bb794u, 4, ecx);
    ecx = lift_load(&env, eax, 0x18u, 4);
    edx = edx + ecx;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, 0u, 0x5bb732u, 1)) & 0xffu) << 8);
    lift_store(&env, 0u, 0x5bb7c8u, 4, edx);
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x4u, &fl);
    }
    if (!fl.zf)
        goto L_4b1f39;
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5bb768u, 4, eax);
    lift_store(&env, 0u, 0x5bb770u, 4, eax);
L_4b1cf7:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x13cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1d2b;
    eax = lift_load(&env, 0u, 0x5bb750u, 4);
    ecx = lift_load(&env, 0u, 0x5bb74eu, 4);
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
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
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4b1d2b:
    eax = 0x1u;
L_4b1d30:
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
L_4b1d35:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    goto L_4b17f6;
L_4b1d44:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4b1d4b:
    ecx = ecx ^ ecx;
    lift_store(&env, 0u, 0x5bb740u, 2, (ecx & 0xffffu));
    goto L_4b197b;
L_4b1d59:
    ebx = ebx ^ ebx;
    lift_store(&env, 0u, 0x5bb742u, 2, (ebx & 0xffffu));
    goto L_4b19a6;
L_4b1d67:
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x91u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b19d3;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x220u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1d8d;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x221u, 1)) & 0xffu);
    goto L_4b19d6;
L_4b1d8d:
    eax = lift_load(&env, eax, 0x270u, 4);
    edx = lift_load(&env, 0u, 0x5bb73cu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) + 1u) & 0xffu);
    goto L_4b19d6;
L_4b1da6:
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x92u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4b19f8;
    eax = lift_load(&env, 0u, 0x544070u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x222u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1de0;
    edx = (edx & 0xffff0000u) |
          (((uint32_t)(int32_t)(int8_t)(uint8_t)lift_load(&env, eax, 0x223u, 1)) & 0xffffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x224u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc002u, 2, (edx & 0xffffu));
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    goto L_4b1a0a;
L_4b1de0:
    eax = lift_load(&env, eax, 0x26cu, 4);
    ecx = lift_load(&env, 0u, 0x5bb73cu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + ecx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bc004u, 1, (eax & 0xffu));
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bc004u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bc000u, 1, (eax & 0xffu));
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bc004u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x7u) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - 0x5u) & 0xffu);
    edx = (edx & 0xffff0000u) | (((uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu)) & 0xffffu);
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    lift_store(&env, 0u, 0x5bc002u, 2, (edx & 0xffffu));
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4b1e29;
    {
        uint32_t r = lift_imul(32, edx, 0x28u, &fl);
        eax = r;
    }
    goto L_4b1a04;
L_4b1e29:
    {
        uint32_t r = lift_imul(32, edx, 0x14u, &fl);
        eax = r;
    }
    goto L_4b1a04;
L_4b1e31:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    edx = eax;
    eax = eax ^ eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        edx = r;
    }
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x5bb738u, 1)) & 0xffu);
    {
        uint32_t r = lift_imul(32, edx, eax, &fl);
        edx = r;
    }
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b4u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) ^ ((ebx >> 8) & 0xffu)) & 0xffu) << 8);
    ecx = ecx ^ ecx;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) & 0xfu) & 0xffu);
    lift_store(&env, 0u, 0x5bb74cu, 2, (edx & 0xffffu));
    edx = eax;
    ecx = (ecx & 0xffff0000u) | (((ebx & 0xffffu)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        edx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, edx + 0x5c1b00u, 1)) & 0xffu);
    lift_store(&env, 0u, 0x5bb74cu, 2, lift_load(&env, 0u, 0x5bb74cu, 2) + (ebx & 0xffffu));
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_imul(32, eax, ecx, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x5bb74eu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb7b6u, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0xfu) & 0xffu);
    eax = eax & 0xffffu;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x5c1b00u, 1)) & 0xffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x5bb74eu, 2)) & 0xffffu);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    edi = edi + eax;
    lift_store(&env, 0u, 0x5bb74eu, 2, (edi & 0xffffu));
    goto L_4b1a2f;
L_4b1eb5:
    {
        (void)lift_and(8, (ebx & 0xffu), (ebx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4b1eeb;
    eax = eax ^ eax;
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x5bc010u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    edx = edx - 1u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff8u, 2, (edx & 0xffffu));
    eax = eax - 1u;
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5bbffcu, 2, (eax & 0xffffu));
    lift_store(&env, 0u, 0x5bbffau, 2, (edx & 0xffffu));
    goto L_4b1ae9;
L_4b1eeb:
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x3u, &fl);
    }
    if (!fl.zf)
        goto L_4b1ae9;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xa8u, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff6u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xaau, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbff8u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xacu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x5bbffau, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esi, 0xaeu, 2)) & 0xffffu);
    goto L_4b1ae3;
L_4b1f27:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x5bc014u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4b1c2c;
    goto L_4b1c6f;
L_4b1f39:
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b1f6d;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4b1cf7;
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5bb778u, 4, eax);
    lift_store(&env, 0u, 0x5bb77cu, 4, eax);
    goto L_4b1cf7;
L_4b1f6d:
    ebx = lift_load(&env, 0u, 0x5bb7a0u, 4);
    edx = lift_load(&env, 0u, 0x5bb79eu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x478eb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5bb780u, 4, eax);
    lift_store(&env, 0u, 0x5bb784u, 4, eax);
    goto L_4b1cf7;
}

uint32_t lifted_f4b3140(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4B3140_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4B3140_STACK, 0, entry);
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
        goto L_4b31e0;
    edx = 0x4ec1ecu;
    esi = 0x517c10u;
    lift_store(&env, eax, 0x158u, 4, 0x517c64u);
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
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    eax = lift_load(&env, ecx, 0x160u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4b31aa;
    if (fl.zf)
        goto L_4b31aa;
    esi = lift_load(&env, eax, 0x158u, 4);
    edx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b31aa:
    edx = edx ^ edx;
    eax = ecx;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    edx = 0x1u;
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5420u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4b31cc;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca050u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4b31cc:
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
L_4b31e0:
    edi = 0x1u;
    edx = 0x517c80u;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
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

uint32_t lifted_f4bb870(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4BB870_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4BB870_STACK, 0, entry);
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
    esp = esp - 0x10u;
    esi = eax;
    edx = edx ^ edx;
    eax = lift_load(&env, eax, 0x1c0u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    lift_store(&env, ebp, 0xffffffe4u, 4, edx);
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
    edx = lift_load(&env, esi, 0x24u, 4);
    edi = lift_load(&env, esi, 0xd8u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bb8f4;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
L_4bb89e:
    eax = lift_load(&env, edi, 0x24u, 4);
    eax = eax - 1u;
    {
        (void)lift_sub(32, eax, 0x7u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4bb939;
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4bb8b2;
            case 1:
                goto L_4bb8fe;
            case 2:
                goto L_4bb939;
            case 3:
                goto L_4bb90d;
            case 4:
                goto L_4bb939;
            case 5:
                goto L_4bb939;
            case 6:
                goto L_4bb939;
            case 7:
                goto L_4bb921;
            default:
                return 0u;
        }
    }
L_4bb8b2:
    eax = 0x4c4cc0u;
L_4bb8b7:
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
L_4bb8bf:
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, edx, 0x4u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x30u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4bb8da;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, ebx, lift_load(&env, edx, 0x2cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4bb955;
L_4bb8da:
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = edi + 0x54u;
    edx = lift_load(&env, esi, 0x24u, 4);
    ecx = ecx + 0x4u;
    ebx = ebx + 1u;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bb89e;
L_4bb8f4:
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
L_4bb8fe:
    ecx = 0x4c4b00u;
    ebx = ebx ^ ebx;
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    goto L_4bb8bf;
L_4bb90d:
    eax = 0x4c4730u;
    goto L_4bb8b7;
L_4bb914:
    ecx = 0x4c4000u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, ecx);
    goto L_4bb8bf;
L_4bb921:
    eax = lift_load(&env, esi, 0x48u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bb914;
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x30u);
    edx = lift_load(&env, esi, 0x0u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4bb8bf;
L_4bb939:
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x7u);
    eax = lift_load(&env, esi, 0x0u, 4);
    edx = lift_load(&env, edi, 0x24u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    edx = lift_load(&env, esi, 0x0u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4bb8bf;
L_4bb955:
    ebx = lift_load(&env, edi, 0x4cu, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4bb8da;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, edx, 0x2cu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bb98d;
    eax = ebx;
    edx = lift_load(&env, edi, 0x50u, 4);
    ebx = ebx + 0x80u;
L_4bb975:
    ecx = ecx ^ ecx;
    edx = edx + 0x4u;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, eax, 0x0u, 2)) & 0xffffu);
    eax = eax + 0x2u;
    lift_store(&env, edx, 0xfffffffcu, 4, ecx);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.zf)
        goto L_4bb8da;
    goto L_4bb975;
L_4bb98d:
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x30u);
    edx = lift_load(&env, esi, 0x0u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4bb8da;
}

uint32_t lifted_f4bbf30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4BBF30_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4BBF30_STACK, 0, entry);
    goto L_4bbf30;
L_4bbf24:
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
L_4bbf30:
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
    esp = esp - 0x10u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    ecx = lift_load(&env, eax, 0x10u, 4);
    esi = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, ecx, 0x1a0u, 4);
    ebx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4bbfd6;
    edi = 0xffu;
L_4bbf5f:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xfffffff4u, 4), 0x19u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4bc004;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4bbfb6;
L_4bbf6d:
    eax = eax ^ eax;
    ebx = ebx - 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    esi = esi + 1u;
    {
        (void)lift_sub(32, eax, 0xffu, &fl);
    }
    if (!fl.zf)
        goto L_4bbfa5;
L_4bbf7a:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4bbf92;
    ebx = lift_load(&env, ecx, 0x18u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bbf24;
    ebx = lift_load(&env, ecx, 0x18u, 4);
    esi = lift_load(&env, ebx, 0x0u, 4);
    ebx = lift_load(&env, ebx, 0x4u, 4);
L_4bbf92:
    eax = eax ^ eax;
    ebx = ebx - 1u;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    esi = esi + 1u;
    {
        (void)lift_sub(32, eax, 0xffu, &fl);
    }
    if (fl.zf)
        goto L_4bbf7a;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bbfd0;
    eax = edi;
L_4bbfa5:
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        edx = r;
    }
    edx = edx | eax;
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) + 0x8u);
    goto L_4bbf5f;
L_4bbfb6:
    ebx = lift_load(&env, ecx, 0x18u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bbf24;
    ebx = lift_load(&env, ecx, 0x18u, 4);
    esi = lift_load(&env, ebx, 0x0u, 4);
    ebx = lift_load(&env, ebx, 0x4u, 4);
    goto L_4bbf6d;
L_4bbfd0:
    lift_store(&env, ecx, 0x1a0u, 4, eax);
L_4bbfd6:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xfffffff4u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bc004;
    eax = lift_load(&env, ecx, 0x1bcu, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4bc027;
L_4bbfea:
    ecx = 0x19u;
    edi = lift_load(&env, ebp, 0xfffffff4u, 4);
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        uint32_t r = lift_sub(32, ecx, edi, &fl);
        ecx = r;
    }
    edx = 0x19u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xfffffff4u, 4, edx);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
L_4bc004:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, eax, 0x0u, 4, esi);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, eax, 0x4u, 4, ebx);
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, edx, 0x8u, 4, eax);
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, edx, 0xcu, 4, eax);
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
L_4bc027:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x75u);
    edi = lift_load(&env, ecx, 0x0u, 4);
    edx = 0xffffffffu;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ecx, 0x1bcu, 4);
    lift_store(&env, eax, 0x8u, 4, 0x1u);
    goto L_4bbfea;
}

uint32_t lifted_f4bc1e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4BC1E0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4BC1E0_STACK, 0, entry);
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
    esp = esp - 0x54u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
    eax = lift_load(&env, eax, 0x1bcu, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x114u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4bc296;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x24u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4bc296;
    ebx = eax;
    edx = ebx;
    edx = lift_load(&env, edx, 0x10u, 4);
    eax = lift_load(&env, eax, 0x10u, 4);
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
    eax = eax - edx - fl.cf;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffccu, 4);
    esi = lift_load(&env, ecx, 0x1b8u, 4);
    edi = lift_load(&env, esi, 0x18u, 4);
    edi = edi + eax;
    eax = ebx;
    lift_store(&env, esi, 0x18u, 4, edi);
    lift_store(&env, eax, 0x10u, 4, 0x0u);
    edx = lift_load(&env, ecx, 0x1b8u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bc526;
    esi = lift_load(&env, ecx, 0x148u, 4);
    edx = edx ^ edx;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bc280;
    eax = ebx;
L_4bc266:
    lift_store(&env, eax, 0x14u, 4, 0x0u);
    edx = edx + 1u;
    edi = lift_load(&env, ecx, 0x148u, 4);
    eax = eax + 0x4u;
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bc266;
L_4bc280:
    eax = lift_load(&env, ecx, 0x114u, 4);
    lift_store(&env, ebx, 0x24u, 4, eax);
    eax = lift_load(&env, ecx, 0x1a0u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bc296;
    lift_store(&env, ebx, 0x8u, 4, eax);
L_4bc296:
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4bc510;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    eax = lift_load(&env, eax, 0x18u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffff9cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = lift_load(&env, eax, 0x18u, 4);
    ebx = lift_load(&env, ebp, 0xffffffc8u, 4);
    edi = (ebp + 0xffffffb0u);
    eax = lift_load(&env, eax, 0x4u, 4);
    esi = lift_load(&env, ebp, 0xffffffc8u, 4);
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    esi = (esi + 0x14u);
    edx = lift_load(&env, edx, 0xcu, 4);
    ebx = lift_load(&env, ebx, 0x10u, 4);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    ecx = ecx ^ ecx;
    esi = lift_load(&env, eax, 0x164u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bc4e4;
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
L_4bc2f8:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    esi = lift_load(&env, ebp, 0xffffffd8u, 4);
    edi = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    esi = lift_load(&env, esi, 0x48u, 4);
    edi = lift_load(&env, edi, 0x70u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    {
        (void)lift_sub(32, ebx, 0x8u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bc533;
L_4bc315:
    ecx = (ebx + 0xfffffff8u);
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = eax;
    ecx = ecx & 0xffu;
    eax = ecx;
    eax = lift_load(&env, esi, (eax * 4u) + 0x90u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4bc55a;
    eax = 0x9u;
L_4bc33a:
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = esi;
    eax = (ebp + 0xffffff9cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bc050u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bc526;
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
L_4bc356:
    esi = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4bc3a8;
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4bc379;
    eax = (ebp + 0xffffff9cu);
    ecx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bc526;
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
L_4bc379:
    ebx = ebx - lift_load(&env, ebp, 0xffffffecu, 4);
    eax = edx;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    esi = 0x1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        esi = r;
    }
    ecx = (esi + 0xffffffffu);
    eax = eax & ecx;
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        ecx = r;
    }
    {
        (void)lift_sub(32, eax, lift_load(&env, ecx, 0x4ffcbcu, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4bc3a5;
    eax = eax + lift_load(&env, ecx, 0x4ffcfcu, 4);
L_4bc3a5:
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_4bc3a8:
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    esi = lift_load(&env, ecx, 0x98u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4bc3db;
    eax = eax + lift_load(&env, ebp, 0xffffffccu, 4);
    eax = lift_load(&env, eax, 0x168u, 4);
    esi = lift_load(&env, ebp, 0xffffffecu, 4);
    esi = esi + lift_load(&env, ebp, (eax * 4u) + 0xffffffb0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, esi);
    lift_store(&env, ebp, (eax * 4u) + 0xffffffb0u, 4, esi);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, ecx, 0x0u, 2, (eax & 0xffffu));
L_4bc3db:
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xc0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4bc5cf;
    esi = 0x1u;
L_4bc3f0:
    {
        (void)lift_sub(32, ebx, 0x8u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bc56e;
L_4bc3f9:
    ecx = (ebx + 0xfffffff8u);
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = eax;
    ecx = ecx & 0xffu;
    eax = ecx;
    eax = lift_load(&env, edi, (eax * 4u) + 0x90u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bc5b6;
    ebx = ebx - eax;
    eax = ecx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, eax + 0x490u, 1)) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_4bc42c:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_and(32, ecx, 0xfu, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    if (fl.zf)
        goto L_4bc5bf;
    esi = esi + eax;
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4bc45d;
    eax = (ebp + 0xffffff9cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bc526;
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
L_4bc45d:
    ebx = ebx - lift_load(&env, ebp, 0xffffffecu, 4);
    eax = edx;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = 0x1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = (eax + 0xffffffffu);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = eax & ecx;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, ecx, lift_load(&env, eax, 0x4ffcbcu, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4bc495;
    ecx = ecx + lift_load(&env, eax, 0x4ffcfcu, 4);
L_4bc495:
    eax = ecx;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = lift_load(&env, 0u, (esi * 4u) + 0x5000d0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + eax;
    eax = eax + ecx;
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, eax, 0x0u, 2, (ecx & 0xffffu));
L_4bc4ae:
    esi = esi + 1u;
    {
        (void)lift_sub(32, esi, 0x40u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bc3f0;
L_4bc4b8:
    edi = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = eax + 0x4u;
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    eax = ecx;
    ecx = lift_load(&env, ebp, 0xffffffccu, 4);
    edi = edi + 0x4u;
    esi = lift_load(&env, ecx, 0x164u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bc2f8;
L_4bc4e4:
    ecx = lift_load(&env, ebp, 0xffffffccu, 4);
    ecx = lift_load(&env, ecx, 0x18u, 4);
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    ecx = lift_load(&env, ebp, 0xffffffccu, 4);
    ecx = lift_load(&env, ecx, 0x18u, 4);
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    lift_store(&env, eax, 0xcu, 4, edx);
    edi = eax;
    lift_store(&env, eax, 0x10u, 4, ebx);
    esi = (ebp + 0xffffffb0u);
    edi = (edi + 0x14u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
L_4bc510:
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    ebx = 0x1u;
    {
        uint32_t r = lift_sub(32, lift_load(&env, eax, 0x24u, 4), ebx, &fl);
        lift_store(&env, eax, 0x24u, 4, r);
    }
    eax = ebx;
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
L_4bc526:
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = ebx;
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
L_4bc533:
    eax = (ebp + 0xffffff9cu);
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bc526;
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    {
        (void)lift_sub(32, ebx, 0x8u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4bc315;
    eax = 0x1u;
    goto L_4bc33a;
L_4bc55a:
    esi = esi + ecx;
    ebx = ebx - eax;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x490u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    goto L_4bc356;
L_4bc56e:
    eax = (ebp + 0xffffff9cu);
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bc526;
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    {
        (void)lift_sub(32, ebx, 0x8u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4bc3f9;
    lift_store(&env, ebp, 0xffffffe0u, 4, 0x1u);
L_4bc592:
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff9cu);
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bc050u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bc526;
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
    goto L_4bc42c;
L_4bc5b6:
    lift_store(&env, ebp, 0xffffffe0u, 4, 0x9u);
    goto L_4bc592;
L_4bc5bf:
    {
        (void)lift_sub(32, eax, 0xfu, &fl);
    }
    if (!fl.zf)
        goto L_4bc4b8;
    esi = esi + eax;
    goto L_4bc4ae;
L_4bc5cf:
    esi = 0x1u;
L_4bc5d4:
    {
        (void)lift_sub(32, ebx, 0x8u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bc64b;
L_4bc5d9:
    ecx = (ebx + 0xfffffff8u);
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = eax;
    ecx = ecx & 0xffu;
    eax = ecx;
    eax = lift_load(&env, edi, (eax * 4u) + 0x90u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bc697;
    ebx = ebx - eax;
    eax = ecx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, eax + 0x490u, 1)) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_4bc60c:
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_and(32, ecx, 0xfu, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    if (fl.zf)
        goto L_4bc6a0;
    esi = esi + eax;
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4bc63d;
    eax = (ebp + 0xffffff9cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bc526;
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
L_4bc63d:
    ebx = ebx - lift_load(&env, ebp, 0xffffffecu, 4);
    esi = esi + 1u;
    {
        (void)lift_sub(32, esi, 0x40u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bc5d4;
    goto L_4bc4b8;
L_4bc64b:
    eax = (ebp + 0xffffff9cu);
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bc526;
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    {
        (void)lift_sub(32, ebx, 0x8u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4bc5d9;
    lift_store(&env, ebp, 0xffffffe4u, 4, 0x1u);
L_4bc673:
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffff9cu);
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bc050u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bc526;
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
    goto L_4bc60c;
L_4bc697:
    lift_store(&env, ebp, 0xffffffe4u, 4, 0x9u);
    goto L_4bc673;
L_4bc6a0:
    {
        (void)lift_sub(32, eax, 0xfu, &fl);
    }
    if (!fl.zf)
        goto L_4bc4b8;
    esi = esi + eax;
    esi = esi + 1u;
    {
        (void)lift_sub(32, esi, 0x40u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bc5d4;
    goto L_4bc4b8;
}

uint32_t lifted_f4bcbc0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4BCBC0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4BCBC0_STACK, 0, entry);
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
    esp = esp - 0x14u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    edx = lift_load(&env, eax, 0x148u, 4);
    ecx = eax;
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4bcce5;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bcbe8;
    {
        (void)lift_sub(32, edx, 0x4u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bcc0b;
L_4bcbe8:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x1au);
    eax = lift_load(&env, ecx, 0x0u, 4);
    edx = lift_load(&env, ecx, 0x148u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x1cu, 4, 0x4u);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4bcc0b:
    edx = lift_load(&env, ecx, 0x134u, 4);
    eax = lift_load(&env, ecx, 0x1cu, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ecx, 0x138u, 4);
    lift_store(&env, ecx, 0x15cu, 4, eax);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    eax = lift_load(&env, ecx, 0x20u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c9820u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x164u, 4, 0x0u);
    esi = esi ^ esi;
    edi = lift_load(&env, ecx, 0x148u, 4);
    lift_store(&env, ecx, 0x160u, 4, eax);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bcd4a;
    edi = ecx;
L_4bcc55:
    ebx = lift_load(&env, edi, 0x14cu, 4);
    eax = lift_load(&env, ebx, 0x8u, 4);
    lift_store(&env, ebx, 0x34u, 4, eax);
    eax = lift_load(&env, ebx, 0xcu, 4);
    lift_store(&env, ebx, 0x38u, 4, eax);
    eax = lift_load(&env, ebx, 0x34u, 4);
    edx = lift_load(&env, ebx, 0x38u, 4);
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, ebx, 0x3cu, 4, eax);
    edx = lift_load(&env, ebx, 0x24u, 4);
    eax = lift_load(&env, ebx, 0x34u, 4);
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, ebx, 0x40u, 4, eax);
    edx = edx ^ edx;
    eax = lift_load(&env, ebx, 0x1cu, 4);
    lift_div1(32, lift_load(&env, ebx, 0x34u, 4), &eax, &edx, &fl);
    eax = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4bcc90;
    eax = lift_load(&env, ebx, 0x34u, 4);
L_4bcc90:
    lift_store(&env, ebx, 0x44u, 4, eax);
    edx = edx ^ edx;
    eax = lift_load(&env, ebx, 0x20u, 4);
    lift_div1(32, lift_load(&env, ebx, 0x38u, 4), &eax, &edx, &fl);
    eax = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4bcca4;
    eax = lift_load(&env, ebx, 0x38u, 4);
L_4bcca4:
    lift_store(&env, ebx, 0x48u, 4, eax);
    edx = lift_load(&env, ebx, 0x3cu, 4);
    eax = lift_load(&env, ecx, 0x164u, 4);
    eax = eax + edx;
    {
        (void)lift_sub(32, eax, 0xau, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4bcdea;
L_4bccbb:
    eax = edx;
    edx = edx - 1u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bcdd3;
    eax = lift_load(&env, ecx, 0x164u, 4);
    ebx = ((eax * 4u));
    eax = eax + 1u;
    lift_store(&env, ecx, 0x164u, 4, eax);
    eax = (ecx + ebx);
    lift_store(&env, eax, 0x168u, 4, esi);
    goto L_4bccbb;
L_4bcce5:
    ebx = lift_load(&env, eax, 0x14cu, 4);
    edx = ecx;
    eax = lift_load(&env, ebx, 0x1cu, 4);
    lift_store(&env, edx, 0x15cu, 4, eax);
    eax = lift_load(&env, ebx, 0x20u, 4);
    lift_store(&env, edx, 0x160u, 4, eax);
    eax = lift_load(&env, ebx, 0x24u, 4);
    esi = lift_load(&env, ebx, 0xcu, 4);
    lift_store(&env, ebx, 0x40u, 4, eax);
    edx = edx ^ edx;
    eax = lift_load(&env, ebx, 0x20u, 4);
    lift_div1(32, esi, &eax, &edx, &fl);
    lift_store(&env, ebx, 0x34u, 4, 0x1u);
    lift_store(&env, ebx, 0x38u, 4, 0x1u);
    lift_store(&env, ebx, 0x3cu, 4, 0x1u);
    lift_store(&env, ebx, 0x44u, 4, 0x1u);
    eax = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4bcd33;
    eax = esi;
L_4bcd33:
    lift_store(&env, ebx, 0x48u, 4, eax);
    lift_store(&env, ecx, 0x164u, 4, 0x1u);
    lift_store(&env, ecx, 0x168u, 4, 0x0u);
L_4bcd4a:
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    ebx = lift_load(&env, eax, 0x148u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bcd96;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
L_4bcd62:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, eax, 0x14cu, 4);
    ebx = lift_load(&env, eax, 0x4cu, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4bcdfe;
L_4bcd79:
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = esi + 0x4u;
    edi = edi + 1u;
    ecx = lift_load(&env, edx, 0x148u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    {
        (void)lift_sub(32, edi, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bcd62;
L_4bcd96:
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = lift_load(&env, edx, 0x1bcu, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = lift_load(&env, edx, 0x1acu, 4);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = lift_load(&env, eax, 0x1acu, 4);
    edx = lift_load(&env, edx, 0x1b4u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
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
L_4bcdd3:
    esi = esi + 1u;
    eax = lift_load(&env, ecx, 0x148u, 4);
    edi = edi + 0x4u;
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4bcd4a;
    goto L_4bcc55;
L_4bcdea:
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0xdu);
    ebx = lift_load(&env, ecx, 0x0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4bccbb;
L_4bcdfe:
    ecx = lift_load(&env, eax, 0x10u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bce0a;
    {
        (void)lift_sub(32, ecx, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bce6b;
L_4bce0a:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x34u);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x18u, 4, ecx);
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4bce28:
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = 0x84u;
    esi = lift_load(&env, esi, 0x4u, 4);
    edx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = eax;
    esi = lift_load(&env, esi, (ecx * 4u) + 0xa4u, 4);
    ecx = 0x84u;
    edx = eax;
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
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, eax, 0x4cu, 4, edx);
    goto L_4bcd79;
L_4bce6b:
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = ((ecx * 4u));
    eax = eax + esi;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xa4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4bce0a;
    goto L_4bce28;
}

uint32_t lifted_f4c17da(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C17DA_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C17DA_STACK, 0, entry);
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
    esp = esp - 0x34u;
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    ecx = lift_load(&env, eax, 0x4u, 4);
    ebx = 0x1cu;
    edx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    edx = lift_load(&env, ebp, 0xffffffb8u, 4);
    lift_store(&env, edx, 0x1a4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    lift_store(&env, eax, 0x0u, 4, 0x4c14b7u);
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    lift_store(&env, eax, 0x4u, 4, 0x4c16dcu);
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    lift_store(&env, eax, 0x8u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = lift_load(&env, eax, 0x1a4u, 4);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c0c8fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    ecx = lift_load(&env, eax, 0x4u, 4);
    ebx = 0x580u;
    edx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    lift_store(&env, ebp, 0xffffffd8u, 4, lift_load(&env, ebp, 0xffffffd8u, 4) + 0x100u);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, edx, 0x144u, 4, eax);
    ebx = 0x100u;
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = eax - 0x100u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 4, 0x0u);
    goto L_4c1897;
L_4c1894:
    lift_store(&env, ebp, 0xffffffdcu, 4, lift_load(&env, ebp, 0xffffffdcu, 4) + 1u);
L_4c1897:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0xffu, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c18ad;
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = edx + lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffdcu, 1)) & 0xffu);
    lift_store(&env, edx, 0x0u, 1, (eax & 0xffu));
    goto L_4c1894;
L_4c18ad:
    lift_store(&env, ebp, 0xffffffd8u, 4, lift_load(&env, ebp, 0xffffffd8u, 4) + 0x80u);
    lift_store(&env, ebp, 0xffffffdcu, 4, 0x80u);
    goto L_4c18c0;
L_4c18bd:
    lift_store(&env, ebp, 0xffffffdcu, 4, lift_load(&env, ebp, 0xffffffdcu, 4) + 1u);
L_4c18c0:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0x200u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c18d4;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0x0u, 1, 0xffu);
    goto L_4c18bd;
L_4c18d4:
    ebx = 0x180u;
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = eax + 0x200u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = 0x80u;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    esi = lift_load(&env, eax, 0x144u, 4);
    edi = lift_load(&env, ebp, 0xffffffd8u, 4);
    edi = edi + 0x380u;
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
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = lift_load(&env, eax, 0x70u, 4);
    edx = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        uint32_t r = lift_imul(32, eax, lift_load(&env, edx, 0x78u, 4), &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffccu, 4), &fl);
    }
    if (fl.zf)
        goto L_4c1943;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x46u);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c1943:
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, eax, 0xcu, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c0b51u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, eax, 0x10u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, eax, 0x18u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x54u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1983;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x40u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c19a1;
L_4c1983:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, eax, 0x64u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, eax, 0x68u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, eax, 0x6cu, 4, 0x0u);
L_4c19a1:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x54u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1a83;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x44u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c19cd;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x2fu);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c19cd:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x78u, 4), 0x3u, &fl);
    }
    if (fl.zf)
        goto L_4c1a03;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, eax, 0x64u, 4, 0x1u);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, eax, 0x68u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, eax, 0x6cu, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, eax, 0x88u, 4, 0x0u);
    goto L_4c1a3a;
L_4c1a03:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x88u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1a1b;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, eax, 0x68u, 4, 0x1u);
    goto L_4c1a3a;
L_4c1a1b:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x5cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1a30;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, eax, 0x6cu, 4, 0x1u);
    goto L_4c1a3a;
L_4c1a30:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    lift_store(&env, eax, 0x64u, 4, 0x1u);
L_4c1a3a:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x64u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1a5a;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c6c80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, eax, 0x1ccu, 4);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, eax, 0x14u, 4, edx);
L_4c1a5a:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x6cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c1a6c;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x68u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1a83;
L_4c1a6c:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c96a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, eax, 0x1ccu, 4);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
L_4c1a83:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x44u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c1abd;
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1a9f;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c2280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c1aaf;
L_4c1a9f:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bb6c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c3be0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c1aaf:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, eax, 0x6cu, 4);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c3540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c1abd:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bb9b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xe0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1ae9;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x1u);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c1b07;
L_4c1ae9:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xdcu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1aff;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c31a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4c1b07;
L_4c1aff:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bc6c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c1b07:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = lift_load(&env, eax, 0x1b4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c1b1f;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x40u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1b28;
L_4c1b1f:
    lift_store(&env, ebp, 0xffffffe0u, 4, 0x1u);
    goto L_4c1b2f;
L_4c1b28:
    lift_store(&env, ebp, 0xffffffe0u, 4, 0x0u);
L_4c1b2f:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bb040u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x44u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c1b53;
    edx = edx ^ edx;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bdde0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c1b53:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x18u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, eax, 0x1b4u, 4);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1b80;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x40u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1b82;
L_4c1b80:
    goto L_4c1b91;
L_4c1b82:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = lift_load(&env, eax, 0x1b4u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x10u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c1b96;
L_4c1b91:
    goto L_4c1c17;
L_4c1b96:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xdcu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1bb3;
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = lift_load(&env, eax, 0x24u, 4);
    eax = (eax + (eax * 2u));
    eax = eax + 0x2u;
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    goto L_4c1bbc;
L_4c1bb3:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = lift_load(&env, eax, 0x24u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
L_4c1bbc:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, eax, 0x4u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, eax, 0x140u, 4);
    {
        uint32_t r = lift_imul(32, edx, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
        edx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, eax, 0x8u, 4, edx);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, eax, 0xcu, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x6cu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c1bfe;
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x3u);
    goto L_4c1c05;
L_4c1bfe:
    lift_store(&env, ebp, 0xffffffe8u, 4, 0x2u);
L_4c1c05:
    eax = lift_load(&env, ebp, 0xffffffc0u, 4);
    edx = lift_load(&env, eax, 0x8u, 4);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, edx, 0x10u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
    {
        uint32_t a = lift_load(&env, eax, 0xcu, 4);
        uint32_t r = lift_inc(32, a, &fl, 1);
        lift_store(&env, eax, 0xcu, 4, r);
    }
L_4c1c17:
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

uint32_t lifted_f4c29c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C29C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C29C0_STACK, 0, entry);
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
    esp = esp - 0x40u;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    ecx = edx;
    eax = lift_load(&env, eax, 0x1bcu, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = lift_load(&env, eax, 0x194u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = lift_load(&env, eax, 0x19cu, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x114u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c2a12;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    ebx = lift_load(&env, eax, 0x28u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4c2a12;
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c26f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c2a3f;
L_4c2a12:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c2a34;
    eax = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c2a4a;
    edx = (eax + 0xffffffffu);
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
L_4c2a2b:
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    lift_store(&env, edx, 0x14u, 4, eax);
L_4c2a34:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    ebx = 0x1u;
    {
        uint32_t r = lift_sub(32, lift_load(&env, eax, 0x28u, 4), ebx, &fl);
        lift_store(&env, eax, 0x28u, 4, r);
    }
L_4c2a3f:
    eax = ebx;
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
L_4c2a4a:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = lift_load(&env, eax, 0x18u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = lift_load(&env, eax, 0x18u, 4);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    ebx = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    edi = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
    esi = lift_load(&env, ebp, 0xffffffd0u, 4);
    edx = lift_load(&env, edx, 0xcu, 4);
    ebx = lift_load(&env, ebx, 0x10u, 4);
    eax = lift_load(&env, ecx, 0x0u, 4);
    esi = lift_load(&env, esi, 0x190u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edi = lift_load(&env, edi, 0x3cu, 4);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c2b65;
L_4c2a8f:
    {
        (void)lift_sub(32, ebx, 0x8u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c2b8a;
L_4c2a98:
    ecx = (ebx + 0xfffffff8u);
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = eax;
    ecx = ecx & 0xffu;
    eax = ecx;
    eax = lift_load(&env, edi, (eax * 4u) + 0x90u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c2bdb;
    ebx = ebx - eax;
    eax = ecx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, eax + 0x490u, 1)) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
L_4c2acb:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t r = lift_and(32, eax, 0xfu, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    if (fl.zf)
        goto L_4c2be4;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    esi = esi + eax;
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c2b05;
    eax = (ebp + 0xffffffb0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c2bce;
    edx = lift_load(&env, ebp, 0xffffffb8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffbcu, 4);
L_4c2b05:
    ebx = ebx - lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    eax = 0x1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffc4u, 4);
    eax = eax - 1u;
    ecx = ecx & eax;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(32, ecx, lift_load(&env, eax, 0x4ffd3cu, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c2b35;
    ecx = ecx + lift_load(&env, eax, 0x4ffd7cu, 4);
L_4c2b35:
    eax = ecx;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = lift_load(&env, 0u, (esi * 4u) + 0x5000d0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = eax + eax;
    eax = eax + ecx;
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    lift_store(&env, eax, 0x0u, 2, (ecx & 0xffffu));
L_4c2b59:
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    esi = esi + 1u;
    {
        (void)lift_sub(32, esi, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c2a8f;
L_4c2b65:
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
    ecx = lift_load(&env, ecx, 0x18u, 4);
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
    ecx = lift_load(&env, ecx, 0x18u, 4);
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, eax, 0xcu, 4, edx);
    lift_store(&env, eax, 0x10u, 4, ebx);
    goto L_4c2a2b;
L_4c2b8a:
    eax = (ebp + 0xffffffb0u);
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c2bce;
    ebx = lift_load(&env, ebp, 0xffffffbcu, 4);
    edx = lift_load(&env, ebp, 0xffffffb8u, 4);
    {
        (void)lift_sub(32, ebx, 0x8u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c2a98;
    lift_store(&env, ebp, 0xffffffe0u, 4, 0x1u);
L_4c2bae:
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (ebp + 0xffffffb0u);
    ecx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bc050u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c2bce;
    edx = lift_load(&env, ebp, 0xffffffb8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffbcu, 4);
    goto L_4c2acb;
L_4c2bce:
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = ebx;
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
L_4c2bdb:
    lift_store(&env, ebp, 0xffffffe0u, 4, 0x9u);
    goto L_4c2bae;
L_4c2be4:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, eax, 0xfu, &fl);
    }
    if (!fl.zf)
        goto L_4c2bf3;
    esi = esi + eax;
    goto L_4c2b59;
L_4c2bf3:
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    eax = 0x1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4c2c3e;
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c2c1d;
    eax = (ebp + 0xffffffb0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c2bce;
    edx = lift_load(&env, ebp, 0xffffffb8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffbcu, 4);
L_4c2c1d:
    ebx = ebx - lift_load(&env, ebp, 0xffffffe4u, 4);
    esi = edx;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    eax = 0x1u;
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        esi = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    eax = eax - 1u;
    ecx = lift_load(&env, ebp, 0xffffffc8u, 4);
    esi = esi & eax;
    ecx = ecx + esi;
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    lift_store(&env, ebp, 0xffffffc8u, 4, ecx);
L_4c2c3e:
    lift_store(&env, ebp, 0xffffffc8u, 4, lift_load(&env, ebp, 0xffffffc8u, 4) - 1u);
    goto L_4c2b65;
}

uint32_t lifted_f4c2d60(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C2D60_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C2D60_STACK, 0, entry);
    goto L_4c2d60;
L_4c2d33:
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
L_4c2d60:
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
    esp = esp - 0x15cu;
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    eax = lift_load(&env, eax, 0x1bcu, 4);
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    ecx = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = lift_load(&env, eax, 0x194u, 4);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, 0x19cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    eax = 0x1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffc8u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = 0xffffffffu;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, 0x19cu, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x114u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c2dd0;
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x28u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c2dd0;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c26f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c2d33;
L_4c2dd0:
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    esi = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4c3176;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    lift_store(&env, ebp, 0xffffffa4u, 4, eax);
    eax = lift_load(&env, eax, 0x18u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffff94u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = lift_load(&env, eax, 0x18u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    eax = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    edi = lift_load(&env, ebp, 0xffffffb0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffb0u, 4);
    eax = lift_load(&env, eax, 0x3cu, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, esi);
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    edi = lift_load(&env, edi, 0xcu, 4);
    ebx = lift_load(&env, ebx, 0x10u, 4);
    eax = lift_load(&env, eax, 0x190u, 4);
    edx = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4c3096;
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffc4u, 4, esi);
    lift_store(&env, ebp, 0xffffffb4u, 4, eax);
L_4c2e41:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffb8u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c3096;
    {
        (void)lift_sub(32, ebx, 0x8u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c2ff4;
    eax = (ebp + 0xffffff94u);
    edx = edi;
    ecx = ecx ^ ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4c2e93;
L_4c2e66:
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = edx ^ edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
L_4c2e71:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c318a;
    ecx = lift_load(&env, eax, ebp + 0xfffffe90u, 4);
    edi = lift_load(&env, ebp, 0xffffffd0u, 4);
    ecx = ecx + ecx;
    edi = edi - 1u;
    ecx = ecx + ebx;
    eax = eax - 0x4u;
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    lift_store(&env, ecx, 0x0u, 2, (edx & 0xffffu));
    goto L_4c2e71;
L_4c2e93:
    ebx = lift_load(&env, ebp, 0xffffffa0u, 4);
    edi = lift_load(&env, ebp, 0xffffff9cu, 4);
    {
        (void)lift_sub(32, ebx, 0x8u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c2ff4;
    eax = 0x1u;
L_4c2ea7:
    ecx = lift_load(&env, ebp, 0xffffffc0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edi;
    eax = (ebp + 0xffffff94u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bc050u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c2e66;
    edi = lift_load(&env, ebp, 0xffffff9cu, 4);
    ebx = lift_load(&env, ebp, 0xffffffa0u, 4);
L_4c2ec2:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    esi = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
    {
        uint32_t r = lift_and(32, esi, 0xfu, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    if (fl.zf)
        goto L_4c303f;
    {
        (void)lift_sub(32, esi, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4c2efb;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffc8u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x76u);
    ecx = lift_load(&env, ecx, 0x0u, 4);
    edx = 0xffffffffu;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c2efb:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c2f1d;
    ecx = 0x1u;
    eax = (ebp + 0xffffff94u);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c2e66;
    edi = lift_load(&env, ebp, 0xffffff9cu, 4);
    ebx = lift_load(&env, ebp, 0xffffffa0u, 4);
L_4c2f1d:
    ebx = ebx - 1u;
    eax = edi;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    {
        (void)lift_and(8, (eax & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4c3037;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
L_4c2f2f:
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
L_4c2f32:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
L_4c2f41:
    esi = lift_load(&env, ebp, 0xffffffecu, 4);
    esi = lift_load(&env, esi, 0x5000d0u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = esi + esi;
    esi = esi + eax;
    {
        (void)lift_sub(16, lift_load(&env, esi, 0x0u, 2), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c30eb;
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c2f7d;
    ecx = 0x1u;
    eax = (ebp + 0xffffff94u);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c2e66;
    edi = lift_load(&env, ebp, 0xffffff9cu, 4);
    ebx = lift_load(&env, ebp, 0xffffffa0u, 4);
L_4c2f7d:
    ebx = ebx - 1u;
    eax = edi;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    {
        (void)lift_and(8, (eax & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4c2fa0;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, esi, 0x0u, 2);
    {
        (void)lift_and(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_4c2fa0;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c30e3;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
L_4c2f9d:
    lift_store(&env, esi, 0x0u, 2, lift_load(&env, esi, 0x0u, 2) + (eax & 0xffffu));
L_4c2fa0:
    ecx = lift_load(&env, ebp, 0xffffffecu, 4);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    ecx = ecx + 0x4u;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c2f41;
L_4c2fb7:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4c2fec;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, 0u, (eax * 4u) + 0x5000d0u, 4);
    esi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = (eax + eax);
    ecx = ecx + esi;
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ecx, 0x0u, 2, (edx & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffffc4u, 4);
    lift_store(&env, edx, ebp + 0xfffffe94u, 4, eax);
    eax = (edx + 0x4u);
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    edx = edx + 1u;
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    lift_store(&env, ebp, 0xffffffd0u, 4, edx);
L_4c2fec:
    lift_store(&env, ebp, 0xffffffe8u, 4, lift_load(&env, ebp, 0xffffffe8u, 4) + 1u);
    goto L_4c2e41;
L_4c2ff4:
    ecx = (ebx + 0xfffffff8u);
    eax = edi;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    eax = eax & 0xffu;
    edx = lift_load(&env, ebp, 0xffffffc0u, 4);
    esi = ((eax * 4u));
    esi = esi + edx;
    esi = lift_load(&env, esi, 0x90u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4c302d;
    eax = eax + edx;
    ebx = ebx - esi;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x490u, 1)) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    goto L_4c2ec2;
L_4c302d:
    eax = 0x9u;
    goto L_4c2ea7;
L_4c3037:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    goto L_4c2f2f;
L_4c303f:
    {
        (void)lift_sub(32, eax, 0xfu, &fl);
    }
    if (fl.zf)
        goto L_4c2f32;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa8u, 1)) & 0xffu);
    eax = 0x1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffa8u, 4);
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4c3096;
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c3078;
    eax = (ebp + 0xffffff94u);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c2e66;
    edi = lift_load(&env, ebp, 0xffffff9cu, 4);
    ebx = lift_load(&env, ebp, 0xffffffa0u, 4);
L_4c3078:
    ebx = ebx - lift_load(&env, ebp, 0xffffffa8u, 4);
    edx = edi;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    eax = 0x1u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        edx = r;
    }
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa8u, 1)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    eax = eax - 1u;
    edx = edx & eax;
    lift_store(&env, ebp, 0xffffffa8u, 4, edx);
    eax = edx;
    lift_store(&env, ebp, 0xffffffacu, 4, lift_load(&env, ebp, 0xffffffacu, 4) + eax);
L_4c3096:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffacu, 4), 0x0u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c314d;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
L_4c30b2:
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffbcu, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c314a;
    esi = lift_load(&env, eax, 0x5000d0u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    esi = esi + esi;
    esi = esi + eax;
    {
        (void)lift_sub(16, lift_load(&env, esi, 0x0u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c30ff;
L_4c30d1:
    ecx = lift_load(&env, ebp, 0xffffffccu, 4);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = ecx + 0x4u;
    esi = esi + 1u;
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    lift_store(&env, ebp, 0xffffffe8u, 4, esi);
    goto L_4c30b2;
L_4c30e3:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    goto L_4c2f9d;
L_4c30eb:
    edx = lift_load(&env, ebp, 0xffffffa8u, 4);
    edx = edx - 1u;
    lift_store(&env, ebp, 0xffffffa8u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c2fb7;
    goto L_4c2fa0;
L_4c30ff:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c3121;
    ecx = 0x1u;
    eax = (ebp + 0xffffff94u);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bbf30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c2e66;
    edi = lift_load(&env, ebp, 0xffffff9cu, 4);
    ebx = lift_load(&env, ebp, 0xffffffa0u, 4);
L_4c3121:
    ebx = ebx - 1u;
    eax = edi;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, (ecx & 0xffu), &fl);
        eax = r;
    }
    {
        (void)lift_and(8, (eax & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4c30d1;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, esi, 0x0u, 2);
    {
        (void)lift_and(32, eax, edx, &fl);
    }
    if (!fl.zf)
        goto L_4c30d1;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c3142;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, esi, 0x0u, 2, lift_load(&env, esi, 0x0u, 2) + (eax & 0xffffu));
    goto L_4c30d1;
L_4c3142:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, esi, 0x0u, 2, lift_load(&env, esi, 0x0u, 2) + (eax & 0xffffu));
    goto L_4c30d1;
L_4c314a:
    lift_store(&env, ebp, 0xffffffacu, 4, lift_load(&env, ebp, 0xffffffacu, 4) - 1u);
L_4c314d:
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    edx = lift_load(&env, edx, 0x18u, 4);
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    edx = lift_load(&env, edx, 0x18u, 4);
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    lift_store(&env, edx, 0x4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    lift_store(&env, eax, 0xcu, 4, edi);
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    lift_store(&env, eax, 0x10u, 4, ebx);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    lift_store(&env, edx, 0x14u, 4, eax);
L_4c3176:
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    eax = 0x1u;
    {
        uint32_t r = lift_sub(32, lift_load(&env, edx, 0x28u, 4), eax, &fl);
        lift_store(&env, edx, 0x28u, 4, r);
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
L_4c318a:
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
}

uint32_t lifted_f4c6640(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C6640_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C6640_STACK, 0, entry);
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
    esi = edx;
    lift_store(&env, esp, 0x4u, 4, ecx);
    edx = lift_load(&env, eax, 0x1ccu, 4);
    lift_store(&env, esp, 0x1cu, 4, edx);
    edx = lift_load(&env, edx, 0x18u, 4);
    eax = lift_load(&env, eax, 0x70u, 4);
    ecx = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    lift_store(&env, esp, 0x24u, 4, ecx);
    ecx = lift_load(&env, edx, 0x4u, 4);
    edx = lift_load(&env, edx, 0x8u, 4);
    lift_store(&env, esp, 0x28u, 4, ecx);
    lift_store(&env, esp, 0x20u, 4, edx);
    edx = edx ^ edx;
    ecx = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, esp, 0x10u, 4, edx);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c678a;
    lift_store(&env, esp, 0xcu, 4, ebx);
    lift_store(&env, esp, 0x14u, 4, esi);
L_4c668e:
    eax = lift_load(&env, esp, 0x1cu, 4);
    eax = lift_load(&env, eax, 0x30u, 4);
    lift_store(&env, esp, 0x18u, 4, eax);
    ecx = lift_load(&env, esp, 0x1cu, 4);
    edx = lift_load(&env, esp, 0x18u, 4);
    ecx = lift_load(&env, ecx, 0x34u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    ecx = ecx + edx;
    lift_store(&env, esp, 0x30u, 4, ecx);
    ecx = lift_load(&env, esp, 0x1cu, 4);
    ecx = lift_load(&env, ecx, 0x38u, 4);
    ebx = lift_load(&env, esp, 0xcu, 4);
    ecx = ecx + edx;
    esi = esi ^ esi;
    lift_store(&env, esp, 0x0u, 4, ecx);
    ecx = lift_load(&env, esp, 0x1cu, 4);
    eax = lift_load(&env, esp, 0x14u, 4);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    ecx = lift_load(&env, ecx, 0x3cu, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx + edx;
    edx = lift_load(&env, esp, 0x8u, 4);
    lift_store(&env, esp, 0x2cu, 4, ecx);
    lift_store(&env, esp, 0x34u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c674c;
L_4c66e0:
    edi = lift_load(&env, esp, 0x30u, 4);
    edx = edx ^ edx;
    ecx = ((esi * 4u));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ebp = lift_load(&env, ecx, edi + 0x0u, 4);
    edi = lift_load(&env, esp, 0x24u, 4);
    edx = edx + ebp;
    edx = edx + edi;
    eax = eax + 1u;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    ebp = lift_load(&env, eax, 0x0u, 1);
    edi = lift_load(&env, esp, 0x0u, 4);
    ebp = ebp + lift_load(&env, ecx, edi + 0x0u, 4);
    edi = lift_load(&env, esp, 0x28u, 4);
    edi = edi + ebp;
    edx = edx & 0xffu;
    edi = lift_load(&env, edi, 0x0u, 1);
    edx = edx + edi;
    edi = lift_load(&env, esp, 0x2cu, 4);
    ecx = ecx + edi;
    edi = lift_load(&env, eax, 0x1u, 1);
    ecx = lift_load(&env, ecx, 0x0u, 4);
    ebp = lift_load(&env, esp, 0x20u, 4);
    ecx = ecx + edi;
    eax = eax + 1u;
    ecx = ecx + ebp;
    eax = eax + 1u;
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    ecx = ecx & 0xffu;
    ebx = ebx + 1u;
    edx = edx + ecx;
    lift_store(&env, ebx, 0xffffffffu, 1, (edx & 0xffu));
    edx = lift_load(&env, esp, 0x34u, 4);
    esi = esi + 1u;
    edx = edx - 1u;
    esi = esi & 0xfu;
    lift_store(&env, esp, 0x34u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4c66e0;
L_4c674c:
    eax = lift_load(&env, esp, 0x18u, 4);
    edx = lift_load(&env, esp, 0x1cu, 4);
    ebx = lift_load(&env, esp, 0xcu, 4);
    esi = lift_load(&env, esp, 0x14u, 4);
    edi = lift_load(&env, esp, 0x10u, 4);
    ebp = lift_load(&env, esp, 0x4u, 4);
    eax = eax + 1u;
    ebx = ebx + 0x4u;
    esi = esi + 0x4u;
    edi = edi + 1u;
    eax = eax & 0xfu;
    lift_store(&env, esp, 0xcu, 4, ebx);
    lift_store(&env, esp, 0x14u, 4, esi);
    lift_store(&env, esp, 0x10u, 4, edi);
    lift_store(&env, esp, 0x18u, 4, eax);
    lift_store(&env, edx, 0x30u, 4, eax);
    {
        (void)lift_sub(32, edi, ebp, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c668e;
L_4c678a:
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

uint32_t lifted_f4c8cd0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C8CD0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C8CD0_STACK, 0, entry);
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
    esp = esp - 0x88u;
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    esi = edx;
    lift_store(&env, ebp, 0xffffff80u, 4, ecx);
    eax = lift_load(&env, eax, 0x1ccu, 4);
    lift_store(&env, ebp, 0xffffff98u, 4, eax);
    eax = lift_load(&env, eax, 0x18u, 4);
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, eax, 0x70u, 4);
    lift_store(&env, ebp, 0xffffff88u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, eax, 0x144u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    eax = lift_load(&env, eax, 0x28u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    eax = lift_load(&env, eax, 0x88u, 4);
    edx = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffff9cu, 4, edx);
    edx = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffa4u, 4, edx);
    eax = lift_load(&env, eax, 0x8u, 4);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
    lift_store(&env, ebp, 0xffffff8cu, 4, edx);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c8fd9;
    eax = lift_load(&env, ebp, 0xffffff88u, 4);
    eax = eax - 1u;
    lift_store(&env, ebp, 0xffffff84u, 4, eax);
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = lift_load(&env, ebp, 0xffffff88u, 4);
    edx = edx + 1u;
    lift_store(&env, ebp, 0xffffff7cu, 4, eax);
    eax = ((edx * 4u));
    eax = eax - edx;
    lift_store(&env, ebp, 0xffffff94u, 4, ebx);
    eax = eax + eax;
    lift_store(&env, ebp, 0xffffff90u, 4, esi);
    lift_store(&env, ebp, 0xffffff78u, 4, eax);
L_4c8d66:
    eax = lift_load(&env, ebp, 0xffffff90u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x24u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c8fe0;
    ebx = 0x1u;
    eax = lift_load(&env, eax, 0x20u, 4);
    esi = 0x3u;
    lift_store(&env, ebp, 0xffffff70u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffbcu, 4, esi);
    lift_store(&env, eax, 0x24u, 4, ebx);
L_4c8da2:
    eax = lift_load(&env, ebp, 0xffffff88u, 4);
    edi = edi ^ edi;
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xfffffff4u, 4, edi);
    lift_store(&env, ebp, 0xffffffc4u, 4, edi);
    lift_store(&env, ebp, 0xffffffc8u, 4, edi);
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
    lift_store(&env, ebp, 0xffffffccu, 4, edi);
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4c8f9b;
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    eax = eax + eax;
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
L_4c8dd4:
    eax = lift_load(&env, ebp, 0xffffff70u, 4);
    eax = eax + lift_load(&env, ebp, 0xffffffb0u, 4);
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)lift_load(&env, eax, 0x0u, 2);
    edx = edx + ecx;
    edx = edx + 0x8u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        edx = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, edx);
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = lift_load(&env, eax, 0x2u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    esi = esi + edx;
    edx = lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = esi + 0x8u;
    edi = edi + eax;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        esi = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edi = edi + 0x8u;
    eax = eax + ebx;
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        edi = r;
    }
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    eax = ebx;
    {
        uint32_t a = edi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        edi = r;
    }
    eax = eax ^ ebx;
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x0u, 1)) & 0xffu);
    esi = esi + ebx;
    ecx = ecx + eax;
    eax = eax ^ eax;
    esi = lift_load(&env, esi, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x1u, 1)) & 0xffu);
    edi = edi + ebx;
    esi = esi + eax;
    eax = eax ^ eax;
    edi = lift_load(&env, edi, 0x0u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0x2u, 1)) & 0xffu);
    edi = edi + eax;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = eax + ecx;
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffa0u, 4);
    esi = esi + eax;
    edi = edi + eax;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = lift_load(&env, esi, 0x0u, 1);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        eax = r;
    }
    ebx = esi;
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x2u, &fl);
        ebx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = ebx;
    eax = eax + ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        edx = r;
    }
    eax = lift_load(&env, eax, 0x0u, 4);
    edi = lift_load(&env, edi, 0x0u, 1);
    eax = eax + edx;
    ecx = edi;
    lift_store(&env, ebp, 0xffffff74u, 4, eax);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x3u, &fl);
        ecx = r;
    }
    edx = lift_load(&env, ebp, 0xffffff74u, 4);
    eax = (ecx + ecx);
    edx = edx + eax;
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    {
        (void)lift_sub(16, lift_load(&env, edx, 0x0u, 2), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4c8eab;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c8500u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4c8eab:
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edx, 0x0u, 2)) & 0xffffu);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax - 1u;
    lift_store(&env, edx, 0x0u, 1, (eax & 0xffu));
    edx = lift_load(&env, ebp, 0xffffff9cu, 4);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x0u, 1)) & 0xffu);
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    edx = edx & 0xffu;
    ecx = ecx - edx;
    edx = lift_load(&env, ebp, 0xffffffa4u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, eax + 0x0u, 1)) & 0xffu);
    ebx = lift_load(&env, ebp, 0xffffffa8u, 4);
    edx = edx & 0xffu;
    eax = eax + ebx;
    esi = esi - edx;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    eax = eax & 0xffu;
    edx = ecx;
    edi = edi - eax;
    eax = (ecx + ecx);
    ecx = ecx + eax;
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    ebx = lift_load(&env, ebp, 0xffffffd4u, 4);
    ebx = ebx + lift_load(&env, ebp, 0xfffffff4u, 4);
    ecx = lift_load(&env, ebp, 0xffffff70u, 4);
    lift_store(&env, ecx, 0x0u, 2, (ebx & 0xffffu));
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffc0u, 4);
    ebx = ebx + eax;
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    ecx = ecx + ebx;
    edx = (ebx + eax);
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    lift_store(&env, ebp, 0xfffffff4u, 4, edx);
    edx = esi;
    eax = (esi + esi);
    ebx = lift_load(&env, ebp, 0xffffffd0u, 4);
    esi = esi + eax;
    ecx = lift_load(&env, ebp, 0xffffff70u, 4);
    ebx = ebx + esi;
    esi = esi + eax;
    lift_store(&env, ecx, 0x2u, 2, (ebx & 0xffffu));
    ecx = lift_load(&env, ebp, 0xffffffc8u, 4);
    ebx = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    ecx = ecx + esi;
    edx = edi;
    esi = esi + eax;
    eax = (edi + edi);
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    edi = edi + eax;
    ecx = lift_load(&env, ebp, 0xffffff70u, 4);
    ebx = ebx + edi;
    edi = edi + eax;
    lift_store(&env, ecx, 0x4u, 2, (ebx & 0xffffu));
    ecx = lift_load(&env, ebp, 0xffffffc4u, 4);
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = ecx + edi;
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    edi = edi + eax;
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    ecx = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = lift_load(&env, ebp, 0xffffff70u, 4);
    ecx = ecx + eax;
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, ecx);
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = ebx + eax;
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    ecx = ecx - 1u;
    edx = edx + eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    lift_store(&env, ebp, 0xffffff70u, 4, edx);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4c8dd4;
L_4c8f9b:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = lift_load(&env, ebp, 0xffffff70u, 4);
    ebx = lift_load(&env, ebp, 0xffffff94u, 4);
    esi = lift_load(&env, ebp, 0xffffff90u, 4);
    edi = lift_load(&env, ebp, 0xffffff8cu, 4);
    ebx = ebx + 0x4u;
    esi = esi + 0x4u;
    edi = edi + 1u;
    lift_store(&env, edx, 0x0u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, ebp, 0xffffff94u, 4, ebx);
    lift_store(&env, edx, 0x2u, 2, (eax & 0xffffu));
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    lift_store(&env, ebp, 0xffffff90u, 4, esi);
    lift_store(&env, edx, 0x4u, 2, (eax & 0xffffu));
    edx = lift_load(&env, ebp, 0xffffff80u, 4);
    lift_store(&env, ebp, 0xffffff8cu, 4, edi);
    {
        (void)lift_sub(32, edi, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c8d66;
L_4c8fd9:
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
L_4c8fe0:
    eax = lift_load(&env, ebp, 0xffffff7cu, 4);
    edi = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = 0xffffffffu;
    ebx = 0xfffffffdu;
    edi = edi + eax;
    eax = lift_load(&env, ebp, 0xffffff84u, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, edx);
    edx = lift_load(&env, ebp, 0xffffff78u, 4);
    eax = lift_load(&env, eax, 0x20u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, ebx);
    edx = edx + eax;
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, edi);
    lift_store(&env, ebp, 0xffffff70u, 4, edx);
    lift_store(&env, eax, 0x24u, 4, 0x0u);
    goto L_4c8da2;
}

uint32_t lifted_f4c90e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4C90E0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4C90E0_STACK, 0, entry);
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
    esp = esp - 0x80u;
    esi = eax;
    eax = lift_load(&env, eax, 0x1ccu, 4);
    lift_store(&env, ebp, 0xffffff70u, 4, eax);
    eax = lift_load(&env, eax, 0x10u, 4);
    edi = lift_load(&env, ebp, 0xffffff70u, 4);
    lift_store(&env, esi, 0x88u, 4, eax);
    edx = 0x1u;
    edi = lift_load(&env, edi, 0x14u, 4);
    ecx = lift_load(&env, esi, 0x4u, 4);
    ebx = edi;
    eax = esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    lift_store(&env, ebp, 0xffffff88u, 4, esi);
    lift_store(&env, eax, 0x4u, 4, 0x1fu);
    lift_store(&env, ebp, 0xffffff84u, 4, esi);
    lift_store(&env, eax, 0x8u, 4, 0x0u);
    ecx = eax;
    lift_store(&env, eax, 0xcu, 4, 0x3fu);
    lift_store(&env, ebp, 0xffffff6cu, 4, eax);
    lift_store(&env, eax, 0x10u, 4, 0x0u);
    edx = eax;
    lift_store(&env, eax, 0x14u, 4, 0x1fu);
    eax = esi;
    lift_store(&env, ebp, 0xffffff80u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c70f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    lift_store(&env, ebp, 0xffffff7cu, 4, ecx);
    lift_store(&env, ebp, 0xffffff9cu, 4, edx);
    {
        (void)lift_sub(32, edi, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c93c1;
L_4c9178:
    eax = lift_load(&env, ebp, 0xffffff9cu, 4);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffff74u, 4, eax);
    lift_store(&env, ebp, 0xffffff98u, 4, edx);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c9369;
    eax = lift_load(&env, ebp, 0xffffff6cu, 4);
    lift_store(&env, ebp, 0xffffffa0u, 4, eax);
L_4c9197:
    eax = lift_load(&env, ebp, 0xffffff88u, 4);
    lift_store(&env, ebp, 0xffffff94u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffff98u, 4);
    lift_store(&env, ebp, 0xffffff90u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffa8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    ecx = lift_load(&env, ebp, 0xffffff88u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    edx = lift_load(&env, ebp, 0xffffffa0u, 4);
    lift_store(&env, ebp, 0xffffffbcu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    ebx = ebx ^ ebx;
    esi = esi ^ esi;
    eax = lift_load(&env, eax, 0xcu, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    lift_store(&env, ebp, 0xffffffacu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    ecx = lift_load(&env, ecx, 0x1ccu, 4);
    eax = lift_load(&env, eax, 0x10u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffa0u, 4);
    lift_store(&env, ebp, 0xffffffb4u, 4, edx);
    ecx = lift_load(&env, ecx, 0x18u, 4);
    eax = lift_load(&env, eax, 0x14u, 4);
    edi = lift_load(&env, ebp, 0xffffffa8u, 4);
    lift_store(&env, ebp, 0xffffffc8u, 4, eax);
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c92ef;
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = eax + eax;
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
    eax = ((edx * 4u));
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    eax = eax + ecx;
    edx = edx + 0x4u;
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    lift_store(&env, ebp, 0xffffffb8u, 4, edx);
L_4c9216:
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffacu, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c92cb;
    eax = lift_load(&env, ebp, 0xffffffb8u, 4);
    edx = lift_load(&env, ebp, 0xffffffb0u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x6u, &fl);
        eax = r;
    }
    eax = eax + edx;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffbcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + 0x2u;
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffacu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffc4u, 4, eax);
    ecx = (eax + 0x2u);
    lift_store(&env, ebp, 0xffffffc4u, 4, ecx);
L_4c9253:
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
    edi = lift_load(&env, ebp, 0xffffffc0u, 4);
    eax = lift_load(&env, ebp, 0xffffffccu, 4);
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    ecx = ecx + edi;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c92b2;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = eax + 0x4u;
    edx = edx + 0x4u;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
L_4c9283:
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ecx, 0x0u, 2)) & 0xffffu);
    ecx = ecx + 0x2u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c92a8;
    edi = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        uint32_t r = lift_imul(32, edi, eax, &fl);
        edi = r;
    }
    esi = esi + edi;
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t r = lift_imul(32, edi, eax, &fl);
        edi = r;
    }
    ebx = ebx + eax;
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffe4u, 4, lift_load(&env, ebp, 0xffffffe4u, 4) + edi);
    lift_store(&env, ebp, 0xffffffe8u, 4, lift_load(&env, ebp, 0xffffffe8u, 4) + eax);
L_4c92a8:
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = edx + 0x8u;
    {
        (void)lift_sub(32, edx, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c9283;
L_4c92b2:
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
    edi = lift_load(&env, ebp, 0xffffffd4u, 4);
    edx = lift_load(&env, ebp, 0xffffffc4u, 4);
    ecx = ecx + 0x40u;
    edi = edi + 0x4u;
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    {
        (void)lift_sub(32, edi, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c9253;
L_4c92cb:
    eax = lift_load(&env, ebp, 0xffffffb0u, 4);
    edx = lift_load(&env, ebp, 0xffffffb8u, 4);
    ecx = lift_load(&env, ebp, 0xffffffb4u, 4);
    edi = lift_load(&env, ebp, 0xffffffa8u, 4);
    eax = eax + 0x4u;
    edx = edx + 0x8u;
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xffffffb0u, 4, eax);
    lift_store(&env, ebp, 0xffffffb8u, 4, edx);
    lift_store(&env, ebp, 0xffffffb4u, 4, ecx);
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c9216;
L_4c92ef:
    ecx = ebx;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        ecx = r;
    }
    edx = (esi + ecx);
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    eax = lift_load(&env, eax, 0x88u, 4);
    esi = lift_load(&env, ebp, 0xffffff90u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    eax = eax + esi;
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    edx = edx + ecx;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    eax = lift_load(&env, ebp, 0xffffff94u, 4);
    eax = lift_load(&env, eax, 0x88u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    eax = eax + esi;
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = edx + ecx;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    edx = lift_load(&env, ebp, 0xffffff94u, 4);
    edx = lift_load(&env, edx, 0x88u, 4);
    edi = lift_load(&env, ebp, 0xffffff74u, 4);
    ebx = lift_load(&env, ebp, 0xffffffa0u, 4);
    edx = lift_load(&env, edx, 0x8u, 4);
    ebx = ebx + 0x20u;
    edx = edx + esi;
    esi = lift_load(&env, ebp, 0xffffff98u, 4);
    lift_store(&env, ebp, 0xffffffa0u, 4, ebx);
    esi = esi + 1u;
    lift_store(&env, edx, 0x0u, 1, (eax & 0xffu));
    lift_store(&env, ebp, 0xffffff98u, 4, esi);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c9197;
L_4c9369:
    edx = lift_load(&env, ebp, 0xffffff88u, 4);
    eax = lift_load(&env, ebp, 0xffffff74u, 4);
    lift_store(&env, edx, 0x84u, 4, eax);
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x60u);
    eax = lift_load(&env, edx, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xffffff74u, 4);
    ecx = lift_load(&env, ebp, 0xffffff88u, 4);
    lift_store(&env, eax, 0x18u, 4, edx);
    ecx = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffff88u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffff70u, 4);
    lift_store(&env, eax, 0x1cu, 4, 0x1u);
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
L_4c93c1:
    eax = 0x2u;
    ecx = ecx + 0x20u;
    lift_store(&env, ebp, 0xffffff8cu, 4, eax);
    lift_store(&env, ebp, 0xffffffa4u, 4, ecx);
L_4c93cf:
    eax = lift_load(&env, ebp, 0xffffff8cu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffff80u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4c94cb;
    esi = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = lift_load(&env, ebp, 0xffffff7cu, 4);
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c9406;
L_4c93ee:
    {
        (void)lift_sub(32, ecx, lift_load(&env, eax, 0x1cu, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c93fe;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x18u, 4), 0x0u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c93fe;
    ebx = eax;
    ecx = lift_load(&env, eax, 0x1cu, 4);
L_4c93fe:
    edx = edx + 1u;
    eax = eax + 0x20u;
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c93ee;
L_4c9406:
    ecx = ebx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4c9178;
    ebx = lift_load(&env, ebp, 0xffffffa4u, 4);
    eax = lift_load(&env, ecx, 0x4u, 4);
    lift_store(&env, ebx, 0x4u, 4, eax);
    eax = lift_load(&env, ecx, 0xcu, 4);
    lift_store(&env, ebx, 0xcu, 4, eax);
    eax = lift_load(&env, ecx, 0x14u, 4);
    lift_store(&env, ebx, 0x14u, 4, eax);
    eax = lift_load(&env, ecx, 0x0u, 4);
    lift_store(&env, ebx, 0x0u, 4, eax);
    eax = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, ebx, 0x8u, 4, eax);
    eax = lift_load(&env, ecx, 0x10u, 4);
    lift_store(&env, ebx, 0x10u, 4, eax);
    esi = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_load(&env, ecx, 0xcu, 4);
    edi = lift_load(&env, ecx, 0x8u, 4);
    edx = lift_load(&env, ecx, 0x0u, 4);
    eax = eax - edi;
    esi = esi - edx;
    {
        uint32_t r = lift_imul(32, eax, 0xcu, &fl);
        edx = r;
    }
    edi = lift_load(&env, ecx, 0x10u, 4);
    eax = lift_load(&env, ecx, 0x14u, 4);
    eax = eax - edi;
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        esi = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edi = edx;
    lift_store(&env, ebp, 0xffffff78u, 4, eax);
    eax = 0x1u;
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c946a;
    edi = esi;
    eax = eax ^ eax;
L_4c946a:
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffff78u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c9532;
L_4c9476:
    edx = lift_load(&env, ecx, 0x14u, 4);
    eax = lift_load(&env, ecx, 0x10u, 4);
    edx = edx + eax;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x14u, 4, eax);
    eax = eax + 1u;
    lift_store(&env, ebx, 0x10u, 4, eax);
L_4c948e:
    eax = lift_load(&env, ebp, 0xffffff84u, 4);
    esi = lift_load(&env, ebp, 0xffffff9cu, 4);
    edx = ecx;
    edi = lift_load(&env, ebp, 0xffffff80u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c70f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffff84u, 4);
    edx = ebx;
    ecx = lift_load(&env, ebp, 0xffffff8cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4c70f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = esi + 1u;
    ebx = lift_load(&env, ebp, 0xffffffa4u, 4);
    ecx = ecx + 0x2u;
    lift_store(&env, ebp, 0xffffff9cu, 4, esi);
    ebx = ebx + 0x20u;
    lift_store(&env, ebp, 0xffffff8cu, 4, ecx);
    lift_store(&env, ebp, 0xffffffa4u, 4, ebx);
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c93cf;
    goto L_4c9178;
L_4c94cb:
    esi = lift_load(&env, ebp, 0xffffff9cu, 4);
    eax = lift_load(&env, ebp, 0xffffff7cu, 4);
    ecx = ecx ^ ecx;
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4c9406;
L_4c94e2:
    edi = lift_load(&env, eax, 0x18u, 4);
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4c94ed;
    ebx = eax;
    ecx = edi;
L_4c94ed:
    edx = edx + 1u;
    eax = eax + 0x20u;
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4c94e2;
    goto L_4c9406;
L_4c94fa:
    edx = lift_load(&env, ecx, 0x4u, 4);
    edi = lift_load(&env, ecx, 0x0u, 4);
    edx = edx + edi;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0x4u, 4, eax);
    eax = eax + 1u;
    lift_store(&env, ebx, 0x0u, 4, eax);
    goto L_4c948e;
L_4c9515:
    edx = lift_load(&env, ecx, 0xcu, 4);
    esi = lift_load(&env, ecx, 0x8u, 4);
    edx = edx + esi;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, ecx, 0xcu, 4, eax);
    eax = eax + 1u;
    lift_store(&env, ebx, 0x8u, 4, eax);
    goto L_4c948e;
L_4c9532:
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.cf)
        goto L_4c9540;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4c94fa;
    goto L_4c948e;
L_4c9540:
    if (fl.cf || fl.zf)
        goto L_4c9515;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4c9476;
    goto L_4c948e;
}

uint32_t lifted_f4ce740(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CE740_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CE740_STACK, 0, entry);
    goto L_4ce740;
L_4ce730:
    edx = 0x4ce810u;
    eax = 0x5c5c64u;
    goto L_4dc030;
L_4ce740:
    edx = 0x4ce7c0u;
    eax = 0x5c5c60u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbf80u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ce730;
    eax = lift_load(&env, eax, 0x4u, 4);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4dc030:
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
    esp = esp - 0x54u;
    ebx = eax;
    lift_store(&env, esp, 0x44u, 4, edx);
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
    lift_store(&env, esp, 0x3cu, 4, 0x51abacu);
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c77e8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc0c6;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, 0x80000000u, &fl);
    }
    if (fl.zf)
        goto L_4dc092;
    eax = (edx & 0xffu);
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4dc092;
    edx = 0x1u;
    goto L_4dc094;
L_4dc092:
    edx = edx ^ edx;
L_4dc094:
    eax = 0x5c77b0u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dc0a2;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbac0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dc0a2:
    lift_store(&env, 0u, 0x5c77e8u, 4, eax);
    goto L_4dc0c6;
L_4dc0a9:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esp, 0x44u, 4, 0x3u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4da66eu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dc0c6:
    eax = esp;
    lift_store(&env, esp, 0x40u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9f06u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dc0a9;
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc0fb;
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbb30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
L_4dc0fb:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    edx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbcd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x4cu, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc12c;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esp, 0x44u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x4cu, 4, eax);
    ecx = lift_load(&env, esp, 0x4cu, 4);
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    edx = lift_load(&env, ebx, 0x0u, 4);
    ebx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbd20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dc12c:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x4cu, 4);
    lift_store(&env, esp, 0x48u, 4, eax);
    eax = lift_load(&env, esp, 0x34u, 4);
    env.chain = eax;
    eax = lift_load(&env, esp, 0x48u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x54u, &fl);
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

uint32_t lifted_f4ce760(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CE760_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CE760_STACK, 0, entry);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4ce7e0u;
    eax = eax + 0x1034u;
    goto L_4dc030;
L_4dc030:
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
    esp = esp - 0x54u;
    ebx = eax;
    lift_store(&env, esp, 0x44u, 4, edx);
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
    lift_store(&env, esp, 0x3cu, 4, 0x51abacu);
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c77e8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc0c6;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, 0x80000000u, &fl);
    }
    if (fl.zf)
        goto L_4dc092;
    eax = (edx & 0xffu);
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4dc092;
    edx = 0x1u;
    goto L_4dc094;
L_4dc092:
    edx = edx ^ edx;
L_4dc094:
    eax = 0x5c77b0u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dc0a2;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbac0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dc0a2:
    lift_store(&env, 0u, 0x5c77e8u, 4, eax);
    goto L_4dc0c6;
L_4dc0a9:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esp, 0x44u, 4, 0x3u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4da66eu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dc0c6:
    eax = esp;
    lift_store(&env, esp, 0x40u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9f06u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dc0a9;
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc0fb;
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbb30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
L_4dc0fb:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    edx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbcd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x4cu, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc12c;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esp, 0x44u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x4cu, 4, eax);
    ecx = lift_load(&env, esp, 0x4cu, 4);
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    edx = lift_load(&env, ebx, 0x0u, 4);
    ebx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbd20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dc12c:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x4cu, 4);
    lift_store(&env, esp, 0x48u, 4, eax);
    eax = lift_load(&env, esp, 0x34u, 4);
    env.chain = eax;
    eax = lift_load(&env, esp, 0x48u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x54u, &fl);
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

uint32_t lifted_f4dbd20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DBD20_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DBD20_STACK, 0, entry);
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
    esp = esp - 0x4u;
    esi = eax;
    lift_store(&env, esp, 0x0u, 4, edx);
    ebp = ebx;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbd43;
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edi = lift_load(&env, esi, 0x4u, 4);
    goto L_4dbd4e;
L_4dbd43:
    {
        uint32_t v = lift_load(&env, eax, 0x0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1cdcu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edi = eax;
L_4dbd4e:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4dbd5e;
    eax = lift_load(&env, esp, 0x0u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, edi, 0x8u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dbe43;
L_4dbd5e:
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4dbe4c;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4dbdb5;
    {
        uint32_t v = 0x10u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dba80u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dbd7b;
    lift_store(&env, eax, 0x0u, 4, 0x51ac34u);
L_4dbd7b:
    lift_store(&env, eax, 0x8u, 4, 0x0u);
    lift_store(&env, eax, 0xcu, 4, 0x0u);
    edi = eax;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbd9b;
    eax = (esi + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4dbd9b:
    eax = (esi + 0x18u);
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dba10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbdb5;
    eax = (esi + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4dbdb5:
    {
        (void)lift_sub(32, lift_load(&env, edi, 0xcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbdd1;
    eax = lift_load(&env, esi, 0x10u, 4);
    eax = ((eax * 4u));
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c4cu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    goto L_4dbde8;
L_4dbdd1:
    eax = lift_load(&env, esi, 0x10u, 4);
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = ((eax * 4u));
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, edi, 0xcu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c58u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
L_4dbde8:
    lift_store(&env, edi, 0xcu, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, edi, 0xcu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dbe06;
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbe01;
    eax = (esi + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4dbe01:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dbe06:
    eax = lift_load(&env, esi, 0x10u, 4);
    eax = eax - lift_load(&env, edi, 0x8u, 4);
    ebx = ((eax * 4u));
    eax = lift_load(&env, edi, 0x8u, 4);
    edx = lift_load(&env, edi, 0xcu, 4);
    eax = ((eax * 4u));
    eax = eax + edx;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, esi, 0x10u, 4);
    lift_store(&env, edi, 0x8u, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4dbe40;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x0u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ce0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    goto L_4dbe43;
L_4dbe40:
    lift_store(&env, esi, 0x4u, 4, edi);
L_4dbe43:
    eax = lift_load(&env, esp, 0x0u, 4);
    ebx = lift_load(&env, edi, 0xcu, 4);
    lift_store(&env, ebx, (eax * 4u) + 0x0u, 4, ebp);
L_4dbe4c:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x0u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dbe5c;
    esi = esi + 0x20u;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4dbe5c:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dc030(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DC030_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DC030_STACK, 0, entry);
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
    esp = esp - 0x54u;
    ebx = eax;
    lift_store(&env, esp, 0x44u, 4, edx);
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
    lift_store(&env, esp, 0x3cu, 4, 0x51abacu);
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c77e8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc0c6;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c00u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, 0x80000000u, &fl);
    }
    if (fl.zf)
        goto L_4dc092;
    eax = (edx & 0xffu);
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4dc092;
    edx = 0x1u;
    goto L_4dc094;
L_4dc092:
    edx = edx ^ edx;
L_4dc094:
    eax = 0x5c77b0u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dc0a2;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbac0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dc0a2:
    lift_store(&env, 0u, 0x5c77e8u, 4, eax);
    goto L_4dc0c6;
L_4dc0a9:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esp, 0x44u, 4, 0x3u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4da66eu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dc0c6:
    eax = esp;
    lift_store(&env, esp, 0x40u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9f06u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dc0a9;
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b48u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc0fb;
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbb30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 4, eax);
L_4dc0fb:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    edx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbcd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x4cu, 4, eax);
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dc12c;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esp, 0x44u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esp, 0x4cu, 4, eax);
    ecx = lift_load(&env, esp, 0x4cu, 4);
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    edx = lift_load(&env, ebx, 0x0u, 4);
    ebx = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dbd20u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dc12c:
    eax = lift_load(&env, 0u, 0x5c77e8u, 4);
    eax = eax + 0x20u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1c40u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esp, 0x40u, 4, 0x0u);
    eax = lift_load(&env, esp, 0x4cu, 4);
    lift_store(&env, esp, 0x48u, 4, eax);
    eax = lift_load(&env, esp, 0x34u, 4);
    env.chain = eax;
    eax = lift_load(&env, esp, 0x48u, 4);
    {
        uint32_t r = lift_add(32, esp, 0x54u, &fl);
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

uint32_t lifted_f4df978(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DF978_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DF978_STACK, 0, entry);
    goto L_4df978;
L_4df96e:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4df978:
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
    esp = esp - 0x4u;
    ecx = eax;
    esi = ebx;
    lift_store(&env, esp, 0x0u, 4, edx);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4df995;
    edx = 0u - edx;
    ecx = (eax + 0x1u);
    lift_store(&env, eax, 0x0u, 1, 0x2du);
    lift_store(&env, esp, 0x0u, 4, edx);
L_4df995:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4df9a2;
    lift_store(&env, esi, 0x8u, 4, 0x4u);
L_4df9a2:
    ebx = 0xau;
    eax = eax ^ eax;
    edx = ecx;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esp, 0x2u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e636cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0x0u, 1)) & 0xffu) << 8);
    ebx = ecx;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4df9c5;
L_4df9bd:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1u, 1)) & 0xffu);
    ecx = ecx + 1u;
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4df9bd;
L_4df9c5:
    {
        (void)lift_sub(32, lift_load(&env, esi, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4df9fd;
    lift_store(&env, ecx, 0x0u, 1, 0x2eu);
    eax = eax ^ eax;
    ebp = lift_load(&env, esi, 0x8u, 4);
    ecx = ecx + 1u;
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4df9fa;
L_4df9d8:
    edx = edx ^ edx;
    lift_store(&env, esp, 0x2u, 2, (edx & 0xffffu));
    edi = lift_load(&env, esp, 0x0u, 4);
    {
        uint32_t r = lift_imul(32, edi, 0xau, &fl);
        edx = r;
    }
    lift_store(&env, esp, 0x0u, 4, edx);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esp, 0x2u, 1)) & 0xffu);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) + 0x30u) & 0xffu);
    lift_store(&env, ecx, 0x0u, 1, (edx & 0xffu));
    eax = eax + 1u;
    ebp = lift_load(&env, esi, 0x8u, 4);
    ecx = ecx + 1u;
    {
        (void)lift_sub(32, eax, ebp, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4df9d8;
L_4df9fa:
    lift_store(&env, ecx, 0x0u, 1, 0x0u);
L_4df9fd:
    {
        (void)lift_and(8, lift_load(&env, esp, 0x1u, 1), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4df96e;
L_4dfa08:
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4dfa4d;
    ecx = (ebx + 0x1u);
    lift_store(&env, ebx, 0x0u, 1, 0x31u);
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x0u, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4dfa1f;
L_4dfa17:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1u, 1)) & 0xffu);
    ecx = ecx + 1u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x30u, &fl);
    }
    if (fl.zf)
        goto L_4dfa17;
L_4dfa1f:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, ecx, 0x0u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((eax >> 8) & 0xffu), 0x2eu, &fl);
    }
    if (!fl.zf)
        goto L_4dfa3e;
    lift_store(&env, ecx, 0x0u, 1, 0x30u);
    ecx = ecx + 1u;
    lift_store(&env, ecx, 0x0u, 1, ((eax >> 8) & 0xffu));
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1u, 1)) & 0xffu);
    ecx = ecx + 1u;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4dfa3e;
L_4dfa35:
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ecx, 0x1u, 1)) & 0xffu) << 8);
    ecx = ecx + 1u;
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x30u, &fl);
    }
    if (fl.zf)
        goto L_4dfa35;
L_4dfa3e:
    lift_store(&env, ecx, 0x0u, 1, 0x30u);
    ecx = ecx + 1u;
    lift_store(&env, ecx, 0x0u, 1, 0x0u);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4dfa4d:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0xffffffffu, 1)) & 0xffu);
    ecx = ecx - 1u;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2eu, &fl);
    }
    if (!fl.zf)
        goto L_4dfa57;
    ecx = ecx - 1u;
L_4dfa57:
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ecx, 0x0u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x39u, &fl);
    }
    if (fl.zf)
        goto L_4dfa6c;
    ebx = (ebx & 0xffffff00u) | ((((edx >> 8) & 0xffu)) & 0xffu);
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) + 1u) & 0xffu);
    lift_store(&env, ecx, 0x0u, 1, (ebx & 0xffu));
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4dfa6c:
    lift_store(&env, ecx, 0x0u, 1, 0x30u);
    goto L_4dfa08;
}

uint32_t lifted_f4e0328(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0328_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0328_STACK, 0, entry);
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
    esp = esp - 0x4u;
    edi = lift_load(&env, 0u, 0x507c8cu, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    esi = edx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e03ed;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cd0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, edx, 0x1u, &fl);
    }
    if (fl.cf)
        goto L_4e0357;
    if (fl.cf || fl.zf)
        goto L_4e0363;
    {
        (void)lift_sub(32, edx, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e036b;
    goto L_4e0378;
L_4e0357:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4e0378;
    ecx = lift_load(&env, esp, 0x0u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xfffffff6u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    goto L_4e0371;
L_4e0363:
    ebx = lift_load(&env, esp, 0x0u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xfffffff5u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    goto L_4e0371;
L_4e036b:
    edx = lift_load(&env, esp, 0x0u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xfffffff4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4e0371:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1cb8u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_4e0378:
    ebp = lift_load(&env, 0u, 0x507c90u, 4);
    ecx = ((esi * 4u));
    edi = lift_load(&env, 0u, 0x507c8cu, 4);
    {
        (void)lift_sub(32, esi, ebp, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e0398;
    ecx = ecx + edi;
    eax = lift_load(&env, esp, 0x0u, 4);
    lift_store(&env, ecx, 0x0u, 4, eax);
    goto L_4e03e1;
L_4e0398:
    edx = (ecx + 0x4u);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x507c90u, 4);
    edi = eax;
    {
        (void)lift_sub(32, edx, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4e03c6;
    eax = ((edx * 4u));
    ebx = edi;
L_4e03b7:
    lift_store(&env, ebx, eax + 0x0u, 4, 0x0u);
    eax = eax + 0x4u;
    edx = edx + 1u;
    {
        (void)lift_sub(32, eax, ecx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e03b7;
L_4e03c6:
    eax = ((esi * 4u));
    edx = lift_load(&env, esp, 0x0u, 4);
    esi = esi + 1u;
    eax = eax + edi;
    lift_store(&env, 0u, 0x507c8cu, 4, edi);
    lift_store(&env, 0u, 0x507c90u, 4, esi);
    lift_store(&env, eax, 0x0u, 4, edx);
L_4e03e1:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cd4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = lift_load(&env, 0u, 0x507c8cu, 4);
L_4e03ed:
    edi = lift_load(&env, 0u, 0x507c8cu, 4);
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e08f0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E08F0_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E08F0_STACK, 1, entry);
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
    eax = lift_load(&env, esp, 0xcu, 4);
    ebx = 0xfffffffcu;
L_4e08fb:
    lift_store(&env, esp, ebx + 0x0u, 4, ebx);
    ebx = ebx - 0x1000u;
    {
        uint32_t r = lift_sub(32, eax, 0x1000u, &fl);
        eax = r;
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4e08fb;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e0b7c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0B7C_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0B7C_STACK, 0, entry);
    goto L_4e0b7c;
L_4e0ae5:
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
    ebx = edx;
L_4e0aee:
    eax = lift_load(&env, esi, 0x0u, 4);
    edx = ebx;
    edi = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0a95u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    {
        (void)lift_sub(32, ebx, lift_load(&env, esi, 0x8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4e0b5e;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e0b5e;
    ecx = lift_load(&env, eax, 0x4u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x0u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) - 1u) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0xdu, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e0b75;
    eax = (eax & 0xffu);
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4e0b1e;
            case 1:
                goto L_4e0b5e;
            case 2:
                goto L_4e0b5e;
            case 3:
                goto L_4e0b5e;
            case 4:
                goto L_4e0b23;
            case 5:
                goto L_4e0b5e;
            case 6:
                goto L_4e0b5e;
            case 7:
                goto L_4e0b5e;
            case 8:
                goto L_4e0b5e;
            case 9:
                goto L_4e0b5e;
            case 10:
                goto L_4e0b5e;
            case 11:
                goto L_4e0b5e;
            case 12:
                goto L_4e0b5e;
            case 13:
                goto L_4e0b3c;
            default:
                return 0u;
        }
    }
L_4e0b1e:
    ebx = lift_load(&env, ecx, 0x4u, 4);
    goto L_4e0aee;
L_4e0b23:
    eax = (edi + 0x10u);
    edx = lift_load(&env, ecx, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6bffu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e0b37;
    ebx = lift_load(&env, ecx, 0x8u, 4);
    goto L_4e0aee;
L_4e0b37:
    ebx = lift_load(&env, ecx, 0xcu, 4);
    goto L_4e0aee;
L_4e0b3c:
    edi = edi + 0x10u;
    edx = lift_load(&env, ecx, 0x4u, 4);
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6bffu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e0b69;
    {
        (void)lift_and(8, lift_load(&env, esi, 0xdu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e0b5d;
    eax = edi;
    edx = lift_load(&env, ecx, 0x4u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6c1du, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e0b5d:
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
L_4e0b5e:
    eax = ebp;
    lift_store(&env, esi, 0x4u, 4, ebx);
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
L_4e0b69:
    ebx = ebx - 1u;
    {
        (void)lift_sub(32, ebx, lift_load(&env, esi, 0x8u, 4), &fl);
    }
    if (fl.zf)
        goto L_4e0b5e;
    ebx = ebx - 1u;
    goto L_4e0aee;
L_4e0b75:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0bf8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e0b5e;
L_4e0b7c:
    lift_store(&env, eax, 0x0u, 4, edx);
    edx = lift_load(&env, edx, 0x4u, 4);
    edx = lift_load(&env, edx, 0xcu, 4);
    lift_store(&env, eax, 0x8u, 4, 0x0u);
    lift_store(&env, eax, 0xcu, 1, 0x0u);
    lift_store(&env, eax, 0x4u, 4, edx);
    edx = lift_load(&env, eax, 0x4u, 4);
    lift_store(&env, eax, 0xdu, 1, lift_load(&env, eax, 0xdu, 1) & 0xfeu);
    goto L_4e0ae5;
}

uint32_t lifted_f4e0c0c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E0C0C_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E0C0C_STACK, 0, entry);
    goto L_4e0c0c;
L_4dee73:
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
    ecx = edx;
    edx = 0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dee8e;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb4d4u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_4dee8e:
    edx = ecx;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6250u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_4e0c0c:
    lift_store(&env, edx, 0xcu, 4, eax);
    eax = lift_load(&env, edx, 0x8u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e0c1a;
    lift_store(&env, eax, 0xcu, 1, 0x3u);
L_4e0c1a:
    lift_store(&env, edx, 0x4u, 1, lift_load(&env, edx, 0x4u, 1) | 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6c37u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x1u;
    eax = 0x5127fbu;
    goto L_4dee73;
}

uint32_t lifted_f4e1200(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E1200_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E1200_STACK, 0, entry);
    goto L_4e1200;
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
L_4e1200:
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e11b0u, eax, edx, ebx, ecx, 0, esp);
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
}

uint32_t lifted_f4e3e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3E00_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3E00_STACK, 0, entry);
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
    eax = lift_load(&env, edx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca0u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, edx, 0x8u, 4);
    ecx = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e3e39;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4e3e32;
    eax = lift_load(&env, edx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0xffffffffu;
    goto L_4e3f0e;
L_4e3e32:
    lift_store(&env, eax, 0xcu, 4, 0x1u);
L_4e3e39:
    {
        (void)lift_and(8, lift_load(&env, edx, 0xcu, 1), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4e3e61;
    eax = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, edx, 0xcu, 1, lift_load(&env, edx, 0xcu, 1) | 0x20u);
    eax = lift_load(&env, edx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0xffffffffu;
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
L_4e3e61:
    eax = lift_load(&env, edx, 0x8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e3e71;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3b60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e3e71:
    ecx = 0x400u;
    {
        (void)lift_sub(32, ebx, 0xau, &fl);
    }
    if (!fl.zf)
        goto L_4e3ec2;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edx, 0xcu, 1)) & 0xffu);
    ecx = 0x600u;
    {
        (void)lift_and(8, (eax & 0xffu), 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_4e3ec2;
    lift_store(&env, edx, 0xdu, 1, lift_load(&env, edx, 0xdu, 1) | 0x10u);
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, eax, 0x0u, 1, 0xdu);
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 1u;
    eax = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, edx, 0x0u, 4, ebp);
    eax = eax + 1u;
    esi = lift_load(&env, edx, 0x14u, 4);
    lift_store(&env, edx, 0x4u, 4, eax);
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.zf)
        goto L_4e3ec2;
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3ce0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e3ec2;
    eax = lift_load(&env, edx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0xffffffffu;
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
L_4e3ec2:
    lift_store(&env, edx, 0xdu, 1, lift_load(&env, edx, 0xdu, 1) | 0x10u);
    eax = lift_load(&env, edx, 0x0u, 4);
    lift_store(&env, eax, 0x0u, 1, (ebx & 0xffu));
    edi = lift_load(&env, edx, 0x0u, 4);
    edi = edi + 1u;
    ebp = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, edx, 0x0u, 4, edi);
    ebp = ebp + 1u;
    eax = lift_load(&env, edx, 0xcu, 4);
    lift_store(&env, edx, 0x4u, 4, ebp);
    {
        (void)lift_and(32, ecx, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e3ee2;
    {
        (void)lift_sub(32, ebp, lift_load(&env, edx, 0x14u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4e3f01;
L_4e3ee2:
    eax = edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3ce0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e3f01;
    eax = lift_load(&env, edx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0xffffffffu;
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
L_4e3f01:
    eax = lift_load(&env, edx, 0x10u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ca4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_4e3f0e:
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

uint32_t lifted_f4e6c37(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6C37_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6C37_STACK, 0, entry);
    goto L_4e6c37;
L_4e078c:
    ebx = eax;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x5c7b90u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e07af;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x507ce4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e07c6;
    edx = 0xffu;
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507ce4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e07c6;
L_4e07af:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6b2cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xfu;
    eax = eax ^ eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6bacu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cd8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e07c6:
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b4cu, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
    edx = lift_load(&env, 0u, 0x5c7b94u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf)
        goto L_4e07ed;
    eax = edx;
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5c7b94u, 4, ebx);
L_4e07ed:
    ecx = lift_load(&env, 0u, 0x5c7b98u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4e0806;
    eax = ecx;
    esi = esi ^ esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5c7b98u, 4, esi);
L_4e0806:
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
L_4e6c37:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507c9cu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax + lift_load(&env, 0u, 0x5c5c54u, 4);
    eax = lift_load(&env, eax, 0x14u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e6c5e;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, eax, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x512eacu;
L_4e6c51:
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dee73u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e6c5e:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0f8bu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, eax, 0xcu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e6c51;
    eax = 0x1u;
    goto L_4e078c;
}

uint32_t lifted_f4e9a30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9A30_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9A30_STACK, 0, entry);
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
    ecx = ebx;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9b5b;
    ebx = (eax + 0xfffffffcu);
    {
        (void)lift_and(8, lift_load(&env, ebx, 0x0u, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e9b5b;
    edx = lift_load(&env, ebx, 0x0u, 4);
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xfeu) & 0xffu);
    eax = (ebx + edx);
    esi = ecx;
    {
        (void)lift_and(8, lift_load(&env, eax, 0x0u, 1), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4e9a7b;
    edi = lift_load(&env, eax, 0x0u, 4);
    edx = edx + edi;
    lift_store(&env, ebx, 0x0u, 4, edx);
    {
        (void)lift_sub(32, eax, lift_load(&env, ecx, 0xcu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4e9a67;
    lift_store(&env, ecx, 0xcu, 4, ebx);
L_4e9a67:
    edx = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    lift_store(&env, edx, 0x8u, 4, eax);
    lift_store(&env, eax, 0x4u, 4, edx);
    lift_store(&env, esi, 0x1cu, 4, lift_load(&env, esi, 0x1cu, 4) - 1u);
    goto L_4e9b0f;
L_4e9a7b:
    lift_store(&env, ebx, 0x0u, 4, edx);
    eax = lift_load(&env, ecx, 0xcu, 4);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (!fl.cf)
        goto L_4e9a9a;
    {
        (void)lift_sub(32, ebx, lift_load(&env, eax, 0x4u, 4), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e9b0f;
    eax = lift_load(&env, ecx, 0x28u, 4);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.cf)
        goto L_4e9b0f;
    goto L_4e9ab3;
L_4e9a9a:
    eax = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.cf)
        goto L_4e9b0f;
    eax = (ecx + 0x20u);
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_sub(32, ebx, edx, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e9b0f;
L_4e9ab3:
    edi = lift_load(&env, esi, 0x1cu, 4);
    eax = lift_load(&env, esi, 0x18u, 4);
    edx = edx ^ edx;
    ecx = (edi + 0x1u);
    lift_div1(32, ecx, &eax, &edx, &fl);
    ecx = eax;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (!fl.cf)
        goto L_4e9aee;
    eax = lift_load(&env, esi, 0x18u, 4);
    eax = eax - edi;
    ecx = ecx + ecx;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e9ad6;
    ecx = 0xffffffffu;
L_4e9ad6:
    eax = lift_load(&env, ebx, 0x0u, 4);
    eax = eax + ebx;
L_4e9ada:
    edx = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_and(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4e9b0f;
    {
        (void)lift_sub(32, edx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4e9aee;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) & 0xfeu) & 0xffu);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4e9ada;
L_4e9aee:
    eax = lift_load(&env, esi, 0xcu, 4);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (!fl.cf)
        goto L_4e9af8;
    eax = lift_load(&env, esi, 0x28u, 4);
L_4e9af8:
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.cf)
        goto L_4e9b0f;
    eax = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.cf)
        goto L_4e9b0f;
    eax = lift_load(&env, eax, 0x8u, 4);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (fl.cf)
        goto L_4e9b0f;
    eax = lift_load(&env, eax, 0x8u, 4);
    goto L_4e9af8;
L_4e9b0f:
    edx = lift_load(&env, eax, 0x4u, 4);
    edi = lift_load(&env, edx, 0x0u, 4);
    edi = edi + edx;
    ecx = lift_load(&env, ebx, 0x0u, 4);
    {
        (void)lift_sub(32, edi, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e9b2e;
    ebp = lift_load(&env, edx, 0x0u, 4);
    ecx = ecx + ebp;
    lift_store(&env, edx, 0x0u, 4, ecx);
    {
        (void)lift_sub(32, ebx, lift_load(&env, esi, 0xcu, 4), &fl);
    }
    if (!fl.zf)
        goto L_4e9b2a;
    lift_store(&env, esi, 0xcu, 4, edx);
L_4e9b2a:
    ebx = edx;
    goto L_4e9b3d;
L_4e9b2e:
    lift_store(&env, esi, 0x1cu, 4, lift_load(&env, esi, 0x1cu, 4) + 1u);
    lift_store(&env, ebx, 0x8u, 4, eax);
    lift_store(&env, ebx, 0x4u, 4, edx);
    lift_store(&env, edx, 0x8u, 4, ebx);
    lift_store(&env, eax, 0x4u, 4, ebx);
L_4e9b3d:
    edx = lift_load(&env, esi, 0x18u, 4);
    edx = edx - 1u;
    edi = lift_load(&env, esi, 0xcu, 4);
    lift_store(&env, esi, 0x18u, 4, edx);
    {
        (void)lift_sub(32, ebx, edi, &fl);
    }
    if (!fl.cf)
        goto L_4e9b53;
    {
        (void)lift_sub(32, ecx, lift_load(&env, esi, 0x10u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e9b53;
    lift_store(&env, esi, 0x10u, 4, ecx);
L_4e9b53:
    {
        (void)lift_sub(32, ecx, lift_load(&env, esi, 0x14u, 4), &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e9b5b;
    lift_store(&env, esi, 0x14u, 4, ecx);
L_4e9b5b:
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

uint32_t lifted_f4ed880(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ED880_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ED880_STACK, 0, entry);
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
    esi = lift_load(&env, 0u, 0x5c8af8u, 4);
    edi = lift_load(&env, 0u, 0x5c8af4u, 4);
    ebx = eax;
    eax = lift_load(&env, 0u, 0x50ba74u, 4);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.cf)
        goto L_4ed8e5;
    if (fl.cf || fl.zf)
        goto L_4ed8aa;
    {
        (void)lift_sub(32, eax, 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ed8cc;
    goto L_4ed8e5;
L_4ed8aa:
    esi = esi - 1u;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf)
        goto L_4ed8bb;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4ed8c5;
    lift_store(&env, 0u, 0x50ba74u, 4, esi);
    goto L_4ed8c5;
L_4ed8bb:
    lift_store(&env, 0u, 0x50ba74u, 4, 0x2u);
L_4ed8c5:
    eax = edi;
    goto L_4ed96e;
L_4ed8cc:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    eax = (eax & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    eax = eax & 0xffu;
    lift_store(&env, 0u, 0x50ba74u, 4, eax);
    eax = lift_load(&env, 0u, 0x5c8af0u, 4);
    goto L_4ed96e;
L_4ed8e5:
    lift_store(&env, 0u, 0x5c8af8u, 4, esi);
    lift_store(&env, 0u, 0x5c8af4u, 4, edi);
L_4ed8f1:
    eax = (esp + 0x14u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x1u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x8u);
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
    eax = lift_call(&env, 0x4f1c74u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ed95d;
    eax = esp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e8950u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4ed8f1;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esp, 0x8u, 2)) & 0xffffu);
    esi = (eax + 0xffffffffu);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esp, 0x11u, 1)) & 0xffu) << 8);
    edi = lift_load(&env, esp, 0xeu, 1);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4ed930;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4ed94b;
L_4ed930:
    ebp = 0x2u;
    eax = eax ^ eax;
    edi = edi ^ edi;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esp, 0xcu, 2)) & 0xffffu);
    lift_store(&env, 0u, 0x50ba74u, 4, ebp);
    lift_store(&env, 0u, 0x5c8af0u, 4, eax);
    goto L_4ed959;
L_4ed94b:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4ed959;
    lift_store(&env, 0u, 0x50ba74u, 4, 0x1u);
L_4ed959:
    eax = edi;
    goto L_4ed96e;
L_4ed95d:
    eax = 0xffffffffu;
    edi = lift_load(&env, 0u, 0x5c8af4u, 4);
    esi = lift_load(&env, 0u, 0x5c8af8u, 4);
L_4ed96e:
    lift_store(&env, 0u, 0x5c8af4u, 4, edi);
    lift_store(&env, 0u, 0x5c8af8u, 4, esi);
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

uint32_t lifted_f4edc0e(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDC0E_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EDC0E_STACK, 0, entry);
    goto L_4edc0e;
L_4edb72:
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edb8e;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4edb8e;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4edb8e;
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4edb8e;
    esi = 0xffffffffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        edx = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edb8e:
    esi = (esi & 0xffff0000u) | (((esi & 0xffffu) - 1u) & 0xffffu);
    {
        uint32_t r = lift_add(32, esi, 0x10000u, &fl);
        esi = r;
    }
    if (fl.cf)
        goto L_4edbb0;
    if (fl.of)
        goto L_4edbb0;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edba4;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
L_4edba4:
    if (!fl.zf)
        goto L_4edbaf;
    {
        uint32_t r = lift_or(32, esi, esi, &fl);
        esi = r;
    }
    if (!fl.sf)
        goto L_4edbaf;
    {
        uint32_t r = lift_xor(16, (esi & 0xffffu), 0x8000u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
L_4edbaf:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edbb0:
    esi = esi - 0x10000u;
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4edbbc;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
L_4edbbc:
    if (!fl.cf && !fl.zf)
        goto L_4edbdb;
    if (!fl.zf)
        goto L_4edbd4;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edbca;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
L_4edbca:
    if (fl.zf)
        goto L_4edbcd;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edbcd:
    {
        uint32_t r = lift_or(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.sf)
        goto L_4edbd4;
    esi = esi ^ edx;
L_4edbd4:
    edx = ecx;
    eax = ebx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
L_4edbdb:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edbdc:
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4edc06;
    {
        (void)lift_sub(32, ecx, 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4edc06;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edbf4;
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
L_4edbf4:
    if (!fl.zf)
        goto L_4edbff;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        ecx = r;
    }
    esi = 0xffffffffu;
    goto L_4edc06;
L_4edbff:
    {
        uint32_t r = lift_or(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.sf)
        goto L_4edc06;
    esi = esi ^ ecx;
L_4edc06:
    edx = ecx;
    eax = ebx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edc0e:
    {
        uint32_t r = lift_add(16, (esi & 0xffffu), 0x1u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.cf)
        goto L_4edb72;
    if (fl.of)
        goto L_4edb72;
    {
        uint32_t r = lift_add(32, esi, 0xffffu, &fl);
        esi = r;
    }
    if (fl.cf)
        goto L_4edbdc;
    if (fl.of)
        goto L_4edbdc;
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edc3f;
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4edc3f;
    {
        uint32_t r = lift_add(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4edc3c;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edc3c:
    {
        uint32_t a = (esi & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
L_4edc3f:
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4edc56;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4edc56;
    {
        (void)lift_and(32, esi, 0x7fff0000u, &fl);
    }
    if (!fl.zf)
        goto L_4edc56;
    eax = eax - eax;
    edx = edx - edx;
    {
        uint32_t r = lift_sub(32, esi, esi, &fl);
        esi = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edc56:
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t t = ecx;
        ecx = esi;
        esi = t;
    }
    edi = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edi = edi & 0x80007fffu;
    ecx = ecx & 0x80007fffu;
    ecx = ecx + edi;
    {
        uint32_t r = lift_sub(16, (ecx & 0xffffu), 0x3ffeu, &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.cf)
        goto L_4edc86;
    {
        (void)lift_sub(16, (ecx & 0xffffu), 0x7fffu, &fl);
    }
    if (fl.cf)
        goto L_4edc86;
    goto L_4edd16;
L_4edc86:
    {
        (void)lift_sub(16, (ecx & 0xffffu), 0xffc0u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4edc94;
    eax = eax - eax;
    edx = edx - edx;
    ecx = ecx - ecx;
    goto L_4edd0c;
L_4edc94:
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = ebp - ebp;
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    lift_mul1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t t = esi;
        esi = eax;
        eax = t;
    }
    ecx = edx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    lift_mul1(32, edx, &eax, &edx, &fl);
    edi = edx;
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_adc(32, edi, ebp, &fl);
        edi = r;
    }
    ebp = ebp + ebp + fl.cf;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    {
        uint32_t t = ebx;
        ebx = eax;
        eax = t;
    }
    lift_mul1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_adc(32, edi, edx, &fl);
        edi = r;
    }
    ebp = ebp + 0x0u + fl.cf;
    eax = ebx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edx = v;
    }
    lift_mul1(32, edx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, ebp, &fl);
        edx = r;
    }
    ebx = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ecx = v;
    }
    if (fl.sf)
        goto L_4edccb;
    {
        uint32_t r = lift_add(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_adc(32, eax, eax, &fl);
        eax = r;
    }
    edx = edx + edx + fl.cf;
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) - 1u) & 0xffffu);
L_4edccb:
    {
        uint32_t r = lift_add(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.cf)
        goto L_4edcf3;
    if (!fl.zf)
        goto L_4edcde;
    {
        uint32_t r = lift_or(32, esi, esi, &fl);
        esi = r;
    }
    ebx = (ebx & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    if (fl.cf)
        goto L_4edcde;
    esi = eax;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        esi = r;
    }
L_4edcde:
    {
        uint32_t r = lift_adc(32, eax, 0x0u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, 0x0u, &fl);
        edx = r;
    }
    if (!fl.cf)
        goto L_4edcf3;
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) + 1u) & 0xffffu);
    {
        (void)lift_sub(16, (ecx & 0xffffu), 0x7fffu, &fl);
    }
    if (fl.zf)
        goto L_4edd16;
L_4edcf3:
    {
        uint32_t r = lift_or(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4edd0c;
    if (!fl.zf)
        goto L_4edcfe;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
    goto L_4edd01;
L_4edcfe:
    ecx = (ecx & 0xffff0000u) | ((0u - (ecx & 0xffffu)) & 0xffffu);
L_4edd01:
    ebx = ebx - ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shrd(32, a, edx, (ecx & 0xffu), &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shrd(32, a, ebx, (ecx & 0xffu), &fl);
        edx = r;
    }
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) - (ecx & 0xffffu)) & 0xffffu);
L_4edd0c:
    {
        uint32_t r = lift_add(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t a = (ecx & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    esi = ecx;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edd16:
    ecx = (ecx & 0xffff0000u) | ((0x7fffu) & 0xffffu);
    edx = 0x80000000u;
    eax = eax - eax;
    goto L_4edd0c;
}

uint32_t lifted_f4eddc4(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EDDC4_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EDDC4_STACK, 0, entry);
    goto L_4eddc4;
L_4edd4e:
    esi = (esi & 0xffff0000u) | (((esi & 0xffffu) - 1u) & 0xffffu);
    {
        uint32_t r = lift_add(32, esi, 0x10000u, &fl);
        esi = r;
    }
    if (fl.cf)
        goto L_4edd6e;
    if (fl.of)
        goto L_4edd6e;
    if (!fl.sf)
        goto L_4edd6d;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edd66;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
L_4edd66:
    if (!fl.zf)
        goto L_4edd6d;
    {
        uint32_t r = lift_xor(16, (esi & 0xffffu), 0x8000u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
L_4edd6d:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edd6e:
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4edd8f;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4edd8f;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4edd8f;
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4edd8f;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        edx = r;
    }
    esi = (esi & 0xffff0000u) | ((0xffffu) & 0xffffu);
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edd8f:
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4edd95;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
L_4edd95:
    if (!fl.cf && !fl.zf)
        goto L_4edd9e;
    edx = ecx;
    eax = ebx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
L_4edd9e:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4edd9f:
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4eddbc;
    {
        (void)lift_sub(32, ecx, 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4eddbc;
    eax = esi;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x10u, &fl);
        eax = r;
    }
    esi = esi ^ eax;
    esi = esi & ecx;
    ecx = ecx - ecx;
L_4eddbc:
    edx = ecx;
    eax = ebx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4eddc4:
    {
        uint32_t r = lift_add(16, (esi & 0xffffu), 0x1u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.cf)
        goto L_4edd4e;
    if (fl.of)
        goto L_4edd4e;
    {
        uint32_t r = lift_add(32, esi, 0xffffu, &fl);
        esi = r;
    }
    if (fl.cf)
        goto L_4edd9f;
    if (fl.of)
        goto L_4edd9f;
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4ede1f;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4ede1f;
    {
        (void)lift_and(32, esi, 0x7fff0000u, &fl);
    }
    if (!fl.zf)
        goto L_4ede1f;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4ede0d;
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4ede0d;
    eax = esi;
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4ede0d;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e2371u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xc0000000u;
    {
        uint32_t r = lift_sub(32, eax, eax, &fl);
        eax = r;
    }
    esi = (esi & 0xffff0000u) | ((0xffffu) & 0xffffu);
    goto L_4ede1e;
L_4ede0d:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e237du, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x80000000u;
    eax = eax - eax;
    {
        uint32_t r = lift_or(16, (esi & 0xffffu), 0x7fffu, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
L_4ede1e:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ede1f:
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4ede30;
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4ede30;
    {
        uint32_t r = lift_add(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4ede2d;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ede2d:
    {
        uint32_t a = (esi & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
L_4ede30:
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t t = ecx;
        ecx = esi;
        esi = t;
    }
    edi = ecx;
    {
        uint32_t a = edi;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edi = edi & 0x80007fffu;
    ecx = ecx & 0x80007fffu;
    {
        uint32_t a = edi;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        ecx = r;
    }
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) + (ecx & 0xffffu)) & 0xffffu);
    {
        uint32_t a = edi;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_rol(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_or(16, (edi & 0xffffu), (edi & 0xffffu), &fl);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4ede6b;
L_4ede61:
    {
        uint32_t r = lift_add(32, eax, eax, &fl);
        eax = r;
    }
    edx = edx + edx + fl.cf;
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) - 1u) & 0xffffu);
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.sf)
        goto L_4ede61;
L_4ede6b:
    {
        uint32_t r = lift_or(16, (ecx & 0xffffu), (ecx & 0xffffu), &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4ede7a;
L_4ede70:
    {
        uint32_t r = lift_add(32, ebx, ebx, &fl);
        ebx = r;
    }
    esi = esi + esi + fl.cf;
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) - 1u) & 0xffffu);
    {
        uint32_t r = lift_or(32, esi, esi, &fl);
        esi = r;
    }
    if (!fl.sf)
        goto L_4ede70;
L_4ede7a:
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) - (ecx & 0xffffu)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (edi & 0xffffu), 0x3fffu, &fl);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.sf)
        goto L_4ede9d;
    {
        (void)lift_sub(16, (edi & 0xffffu), 0x7fffu, &fl);
    }
    if (fl.cf)
        goto L_4ede9d;
    edi = ecx;
    edi = (edi & 0xffff0000u) | ((0x7fffu) & 0xffffu);
    edx = 0x80000000u;
    eax = eax - eax;
    goto L_4edf75;
L_4ede9d:
    {
        (void)lift_sub(16, (edi & 0xffffu), 0xffc0u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4edeae;
    eax = eax - eax;
    edx = edx - edx;
    edi = edi - edi;
    goto L_4edf75;
L_4edeae:
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    ecx = esi;
    edi = edx;
    esi = eax;
    eax = eax - eax;
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4edec0;
    edx = edx - ecx;
    eax = eax + 1u;
L_4edec0:
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    lift_div1(32, ecx, &eax, &edx, &fl);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t t = ebx;
        ebx = eax;
        eax = t;
    }
    lift_mul1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t t = ecx;
        ecx = eax;
        eax = t;
    }
    {
        uint32_t t = ebx;
        ebx = edx;
        edx = t;
    }
    lift_mul1(32, edx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    edx = edx + 0x0u + fl.cf;
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xffffffecu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4edee1;
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    edx = edx + lift_load(&env, ebp, 0xfffffff4u, 4) + fl.cf;
L_4edee1:
    {
        uint32_t a = ecx;
        uint32_t r = lift_sub(32, 0, a, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_sbb(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_sbb(32, edi, edx, &fl);
        edi = r;
    }
    if (fl.zf)
        goto L_4edefb;
L_4edee9:
    {
        uint32_t r = lift_sub(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x1u, &fl);
        lift_store(&env, ebp, 0xffffffe8u, 4, r);
    }
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) - 0x0u - fl.cf);
    {
        uint32_t r = lift_add(32, ecx, ebx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_adc(32, esi, lift_load(&env, ebp, 0xfffffff4u, 4), &fl);
        esi = r;
    }
    {
        uint32_t r = lift_adc(32, edi, 0x0u, &fl);
        edi = r;
    }
    if (!fl.zf)
        goto L_4edee9;
L_4edefb:
    edi = esi;
    esi = ecx;
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        (void)lift_sub(32, ecx, edi, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4edf10;
    edi = edi - ecx;
    {
        uint32_t r = lift_add(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x1u, &fl);
        lift_store(&env, ebp, 0xffffffe8u, 4, r);
    }
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) + 0x0u + fl.cf);
L_4edf10:
    edx = edi;
    eax = esi;
    lift_div1(32, ecx, &eax, &edx, &fl);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4edf47;
    {
        uint32_t t = ebx;
        ebx = eax;
        eax = t;
    }
    lift_mul1(32, ebx, &eax, &edx, &fl);
    {
        uint32_t t = ecx;
        ecx = eax;
        eax = t;
    }
    {
        uint32_t t = ebx;
        ebx = edx;
        edx = t;
    }
    lift_mul1(32, edx, &eax, &edx, &fl);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    edx = edx + 0x0u + fl.cf;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sub(32, 0, a, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_sbb(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t r = lift_sbb(32, edi, edx, &fl);
        edi = r;
    }
    if (fl.zf)
        goto L_4edf47;
L_4edf30:
    {
        uint32_t r = lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x1u, &fl);
        lift_store(&env, ebp, 0xffffffe4u, 4, r);
    }
    {
        uint32_t r = lift_sbb(32, lift_load(&env, ebp, 0xffffffe8u, 4), 0x0u, &fl);
        lift_store(&env, ebp, 0xffffffe8u, 4, r);
    }
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) - 0x0u - fl.cf);
    {
        uint32_t r = lift_add(32, ecx, lift_load(&env, ebp, 0xfffffff0u, 4), &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_adc(32, esi, lift_load(&env, ebp, 0xfffffff4u, 4), &fl);
        esi = r;
    }
    {
        uint32_t r = lift_adc(32, edi, 0x0u, &fl);
        edi = r;
    }
    if (!fl.zf)
        goto L_4edf30;
L_4edf47:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
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
    esp = esp + 0x8u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) - 1u) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    if (!fl.cf)
        goto L_4edf59;
    {
        uint32_t a = edx;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rcr(32, a, 0x1u, &fl);
        eax = r;
    }
    edi = edi + 1u;
L_4edf59:
    {
        uint32_t r = lift_or(16, (edi & 0xffffu), (edi & 0xffffu), &fl);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4edf75;
    if (!fl.zf)
        goto L_4edf64;
    ecx = (ecx & 0xffffff00u) | ((0x1u) & 0xffu);
    goto L_4edf6a;
L_4edf64:
    edi = (edi & 0xffff0000u) | ((0u - (edi & 0xffffu)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | (((edi & 0xffffu)) & 0xffffu);
L_4edf6a:
    ebx = ebx - ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shrd(32, a, edx, (ecx & 0xffu), &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shrd(32, a, ebx, (ecx & 0xffu), &fl);
        edx = r;
    }
    edi = (edi & 0xffff0000u) | (((edi & 0xffffu) - (edi & 0xffffu)) & 0xffffu);
L_4edf75:
    {
        uint32_t r = lift_add(32, edi, edi, &fl);
        edi = r;
    }
    {
        uint32_t a = (edi & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        edi = (edi & 0xffff0000u) | ((r) & 0xffffu);
    }
    esi = edi;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
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
