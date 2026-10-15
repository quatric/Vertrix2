/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_13.h"

uint32_t lifted_f415860(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F415860_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F415860_STACK, 0, entry);
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
    esp = esp - 0x348u;
    eax = (ebp + 0xffffffd4u);
    edx = 0x4ec1ecu;
    ecx = 0x513a20u;
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
    eax = (ebp + 0xfffffed0u);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    ebx = 0x50d3bcu;
    edx = 0x4fd310u;
    lift_store(&env, ebp, 0xffffffdcu, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x45f540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffca4u);
    esi = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4290c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xfffffca4u);
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x429660u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = lift_load(&env, 0u, 0x532b4cu, 4);
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, 0u, 0x532b54u, 4);
    lift_store(&env, edx, 0x4u, 4, eax);
    eax = lift_load(&env, 0u, 0x532b58u, 4);
    lift_store(&env, edx, 0x8u, 4, eax);
    eax = lift_load(&env, 0u, 0x532b5cu, 4);
    lift_store(&env, edx, 0xcu, 4, eax);
    eax = lift_load(&env, 0u, 0x532b60u, 4);
    lift_store(&env, edx, 0x10u, 4, eax);
    eax = lift_load(&env, 0u, 0x532b64u, 4);
    lift_store(&env, edx, 0x14u, 4, eax);
    eax = lift_load(&env, 0u, 0x532b80u, 4);
    lift_store(&env, edx, 0x44u, 4, eax);
    eax = lift_load(&env, 0u, 0x532b84u, 4);
    lift_store(&env, edx, 0x48u, 4, eax);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b6cu, 2)) & 0xffffu);
    lift_store(&env, edx, 0x18u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b6eu, 2)) & 0xffffu);
    lift_store(&env, edx, 0x1au, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b70u, 2)) & 0xffffu);
    lift_store(&env, edx, 0x1cu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b72u, 2)) & 0xffffu);
    lift_store(&env, edx, 0x1eu, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b74u, 2)) & 0xffffu);
    lift_store(&env, edx, 0x20u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b76u, 2)) & 0xffffu);
    lift_store(&env, edx, 0x22u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b78u, 2)) & 0xffffu);
    lift_store(&env, edx, 0x24u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b7au, 2)) & 0xffffu);
    lift_store(&env, edx, 0x26u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b7cu, 2)) & 0xffffu);
    lift_store(&env, edx, 0x28u, 2, (eax & 0xffffu));
    eax = lift_load(&env, 0u, 0x532b88u, 4);
    lift_store(&env, edx, 0x4cu, 4, eax);
    eax = lift_load(&env, 0u, 0x532b98u, 4);
    lift_store(&env, edx, 0x2cu, 4, eax);
    eax = lift_load(&env, 0u, 0x532b9cu, 4);
    lift_store(&env, edx, 0x30u, 4, eax);
    eax = lift_load(&env, 0u, 0x532ba0u, 4);
    lift_store(&env, edx, 0x34u, 4, eax);
    eax = lift_load(&env, 0u, 0x532ba4u, 4);
    lift_store(&env, edx, 0x38u, 4, eax);
    eax = lift_load(&env, 0u, 0x532ba8u, 4);
    lift_store(&env, edx, 0x3cu, 4, eax);
    eax = lift_load(&env, 0u, 0x532bacu, 4);
    lift_store(&env, edx, 0x40u, 4, eax);
    eax = lift_load(&env, 0u, 0x532bb4u, 4);
    lift_store(&env, edx, 0x50u, 4, eax);
    eax = lift_load(&env, 0u, 0x532bb8u, 4);
    lift_store(&env, edx, 0x54u, 4, eax);
    eax = eax ^ eax;
L_4159b0:
    edx = edx + 0x4u;
    ecx = lift_load(&env, 0u, (eax * 4u) + 0x533294u, 4);
    eax = eax + 1u;
    lift_store(&env, edx, 0x54u, 4, ecx);
    {
        (void)lift_sub(32, eax, 0x5u, &fl);
    }
    if (fl.cf)
        goto L_4159b0;
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = 0x5332a8u;
    ecx = ecx + 0x6cu;
    ebx = (edx + 0x14u);
L_4159d1:
    edi = ecx;
    esi = lift_load(&env, edx, 0x0u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4159d6:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4159ee;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4159d6;
L_4159ee:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    edx = edx + 0x4u;
    ecx = ecx + 0x4u;
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4159d1;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, 0u, 0x532bd4u, 4);
    lift_store(&env, edx, 0x80u, 4, eax);
    eax = lift_load(&env, 0u, 0x532bd8u, 4);
    lift_store(&env, edx, 0x84u, 4, eax);
    eax = lift_load(&env, 0u, 0x532bdcu, 4);
    lift_store(&env, edx, 0x88u, 4, eax);
    eax = lift_load(&env, 0u, 0x532be0u, 4);
    lift_store(&env, edx, 0x8cu, 4, eax);
    eax = lift_load(&env, 0u, 0x532be4u, 4);
    lift_store(&env, edx, 0x90u, 4, eax);
    edi = (edx + 0x94u);
    esi = lift_load(&env, 0u, 0x532be8u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_415a40:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_415a58;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_415a40;
L_415a58:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    esi = lift_load(&env, 0u, 0x532becu, 4);
    edi = (edx + 0xf8u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_415a66:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_415a7e;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_415a66;
L_415a7e:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    esi = lift_load(&env, 0u, 0x532bf0u, 4);
    edi = (edx + 0x15cu);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_415a8c:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_415aa4;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_415a8c;
L_415aa4:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    esi = lift_load(&env, 0u, 0x532bf4u, 4);
    edi = (edx + 0x1c0u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_415ab2:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_415aca;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_415ab2;
L_415aca:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    edx = (ebp + 0xfffffed0u);
    eax = (ebp + 0xfffffca4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x429460u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = edi ^ edi;
    eax = (ebp + 0xfffffca4u);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x429350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
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
}

uint32_t lifted_f4212a0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4212A0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4212A0_STACK, 0, entry);
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
    esp = esp - 0x28u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = (ebp + 0xffffffc4u);
    edx = 0x4ec1ecu;
    ecx = 0x5141b4u;
    ebx = 0x540578u;
    esi = 0x513e60u;
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
    lift_store(&env, ebp, 0xffffffc8u, 4, edx);
    lift_store(&env, ebp, 0xffffffccu, 4, ecx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    edx = edi;
    eax = 0x5405a8u;
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d66cdu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4217e7;
L_421301:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x540598u, 1), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4218a6;
L_42130e:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7d10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x41dec0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x532928u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471e10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x419490u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x471a70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
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
    edi = edi ^ edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4719f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x54059cu, 4, edi);
    lift_store(&env, 0u, 0x5404a4u, 4, edi);
L_42135c:
    edx = lift_load(&env, 0u, 0x54d5f4u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, 0u, 0x54d5f8u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x54059cu, 4);
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    {
        uint32_t v = 0xeu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edx ^ edx;
    ecx = 0x46u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47bd80u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    esi = lift_load(&env, 0u, 0x5404a4u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        esi = r;
    }
    esi = esi + 0x540578u;
    edi = 0x5404b0u;
    esi = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_42139a:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4213b2;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_42139a;
L_4213b2:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    eax = lift_load(&env, 0u, 0x54059cu, 4);
    edx = lift_load(&env, 0u, 0x5404a4u, 4);
    ebx = lift_load(&env, 0u, 0x5405a4u, 4);
    eax = eax + 0x2u;
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4218c6;
    ecx = 0x2u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edi;
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    ebx = ecx;
L_4213de:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4429a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    esi = lift_load(&env, 0u, 0x54d5f4u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = lift_load(&env, 0u, 0x54d5f8u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = 0x2du;
    edx = 0x48u;
    {
        uint32_t v = 0xeu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x54059cu, 4);
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x47bd80u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    ebx = lift_load(&env, 0u, 0x5404a4u, 4);
    edx = lift_load(&env, 0u, 0x5405a0u, 4);
    eax = lift_load(&env, 0u, 0x532928u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4125e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5404a8u, 4, eax);
    eax = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca070u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x5404a8u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0x2u;
    {
        uint32_t v = 0x50dde8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = (ebp + 0xffffffe4u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cdfb0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = esp + 0xcu;
    edi = 0x5404b0u;
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_421459:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_421471;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_421459;
L_421471:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    eax = lift_load(&env, 0u, 0x54059cu, 4);
    ecx = 0x4au;
    eax = eax + 0x2u;
    ebx = 0x3u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edi;
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4429a0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ecx = 0x1u;
    eax = (ebp + 0xffffffe4u);
    ebx = lift_load(&env, 0u, 0x54059cu, 4);
    edx = edx ^ edx;
    ebx = ebx + 0x12u;
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    lift_store(&env, 0u, 0x54059cu, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = lift_load(&env, 0u, 0x5404a4u, 4);
    edi = edi + ecx;
    lift_store(&env, ebp, 0xffffffd0u, 4, ecx);
    lift_store(&env, 0u, 0x5404a4u, 4, edi);
    {
        (void)lift_sub(32, edi, 0x8u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_42135c;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4194b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x486da0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x5b9c50u;
    edx = 0x5du;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x487020u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_421534;
    edx = 0x1du;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4218da;
L_421512:
    ebx = lift_load(&env, 0u, 0x5405a0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_421525;
    esi = (ebx + 0xffffffffu);
    lift_store(&env, 0u, 0x5405a0u, 4, esi);
L_421525:
    edx = 0x5du;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_421534:
    edx = 0x62u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_42158c;
    edx = 0x1du;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_42191c;
L_42155e:
    eax = lift_load(&env, 0u, 0x532928u, 4);
    eax = lift_load(&env, eax, 0x5bcu, 4);
    edx = lift_load(&env, 0u, 0x5405a0u, 4);
    eax = eax - 1u;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_42157d;
    ecx = (edx + 0x1u);
    lift_store(&env, 0u, 0x5405a0u, 4, ecx);
L_42157d:
    edx = 0x62u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_42158c:
    edx = 0x5fu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4215e0;
    edx = 0x2au;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_42195e;
L_4215b6:
    ecx = ecx ^ ecx;
L_4215b8:
    ebx = lift_load(&env, 0u, 0x5405a4u, 4);
    edx = lift_load(&env, 0u, 0x5405a0u, 4);
    eax = lift_load(&env, 0u, 0x532928u, 4);
    ecx = ecx + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x412510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ecx, 0x2u, &fl);
    }
    if (fl.cf)
        goto L_4215b8;
L_4215e0:
    edx = 0x60u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_421630;
    edx = 0x2au;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4219ec;
L_42160a:
    ecx = ecx ^ ecx;
L_42160c:
    ebx = lift_load(&env, 0u, 0x5405a4u, 4);
    edx = lift_load(&env, 0u, 0x5405a0u, 4);
    eax = lift_load(&env, 0u, 0x532928u, 4);
    ecx = ecx + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x412430u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ecx, 0x2u, &fl);
    }
    if (fl.cf)
        goto L_42160c;
L_421630:
    edx = 0x2u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_42165a;
    edx = 0x2u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    lift_store(&env, 0u, 0x5405a4u, 4, edx);
L_42165a:
    edx = 0x3u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_421687;
    edx = 0x3u;
    eax = 0x54d640u;
    ecx = 0x1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5405a4u, 4, ecx);
L_421687:
    edx = 0x4u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4216b4;
    edx = 0x4u;
    eax = 0x54d640u;
    ebx = 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5405a4u, 4, ebx);
L_4216b4:
    edx = 0x5u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4216e1;
    edx = 0x5u;
    eax = 0x54d640u;
    esi = 0x3u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5405a4u, 4, esi);
L_4216e1:
    edx = 0x6u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_42170e;
    edx = 0x6u;
    eax = 0x54d640u;
    edi = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5405a4u, 4, edi);
L_42170e:
    edx = 0x7u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_42173a;
    edx = 0x7u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5405a4u, 4, 0x5u);
L_42173a:
    edx = 0x8u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_421766;
    edx = 0x8u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5405a4u, 4, 0x6u);
L_421766:
    edx = 0x9u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_421793;
    edx = 0x9u;
    eax = 0x54d640u;
    ecx = 0x7u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x5405a4u, 4, ecx);
L_421793:
    edx = 0x3du;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4217bd;
    edx = 0x3du;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4192a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4217bd:
    edx = 0x1u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_421a85;
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
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
L_4217e7:
    edx = 0x50ddaeu;
    ecx = 0x2u;
    eax = ebx;
    esi = 0x4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x50ddb5u;
    eax = 0x54057cu;
    ebx = 0x3u;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x50ddbau;
    eax = 0x540580u;
    edi = 0x5u;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x50ddc2u;
    eax = 0x540584u;
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x50ddccu;
    eax = 0x540588u;
    lift_store(&env, ebp, 0xffffffe0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x50ddd3u;
    eax = 0x54058cu;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x6u;
    edx = 0x50ddd8u;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = 0x540590u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x7u;
    eax = 0x540594u;
    lift_store(&env, ebp, 0xffffffe0u, 4, edx);
    edx = 0x50dde1u;
    ecx = 0x8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x4f9d80u;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec1f7u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_421301;
L_4218a6:
    ebx = ebx ^ ebx;
    edx = (edx & 0xffffff00u) | ((0x1u) & 0xffu);
    lift_store(&env, 0u, 0x5405a4u, 4, ebx);
    lift_store(&env, 0u, 0x5405a0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b7cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, 0u, 0x540598u, 1, (edx & 0xffu));
    goto L_42130e;
L_4218c6:
    ecx = 0x2u;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = edi;
    ebx = ebx ^ ebx;
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    goto L_4213de;
L_4218da:
    edx = 0x57u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_421512;
    edx = 0x5du;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x5405a4u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_421534;
    ecx = (edx + 0xffffffffu);
    lift_store(&env, 0u, 0x5405a4u, 4, ecx);
    goto L_421534;
L_42191c:
    edx = 0x57u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_42155e;
    edx = 0x62u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = lift_load(&env, 0u, 0x5405a4u, 4);
    {
        (void)lift_sub(32, edi, 0x7u, &fl);
    }
    if (!fl.cf)
        goto L_42158c;
    eax = (edi + 0x1u);
    lift_store(&env, 0u, 0x5405a4u, 4, eax);
    goto L_42158c;
L_42195e:
    edx = 0x36u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4215b6;
    edx = 0x1du;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4219af;
L_421988:
    ebx = lift_load(&env, 0u, 0x5405a0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_42199b;
    esi = (ebx + 0xffffffffu);
    lift_store(&env, 0u, 0x5405a0u, 4, esi);
L_42199b:
    edx = 0x5fu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4215e0;
L_4219af:
    edx = 0x57u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_421988;
    ebx = lift_load(&env, 0u, 0x5405a4u, 4);
    edx = lift_load(&env, 0u, 0x5405a0u, 4);
    eax = lift_load(&env, 0u, 0x532928u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x412510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x5fu;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4215e0;
L_4219ec:
    edx = 0x36u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_42160a;
    edx = 0x1du;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_421a48;
L_421a16:
    eax = lift_load(&env, 0u, 0x532928u, 4);
    eax = lift_load(&env, eax, 0x5bcu, 4);
    edi = lift_load(&env, 0u, 0x5405a0u, 4);
    eax = eax - 1u;
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_421a34;
    eax = (edi + 0x1u);
    lift_store(&env, 0u, 0x5405a0u, 4, eax);
L_421a34:
    edx = 0x60u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_421630;
L_421a48:
    edx = 0x57u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_421a16;
    ebx = lift_load(&env, 0u, 0x5405a4u, 4);
    edx = lift_load(&env, 0u, 0x5405a0u, 4);
    eax = lift_load(&env, 0u, 0x532928u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x412430u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x60u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476320u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_421630;
L_421a85:
    edx = 0x1u;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4762e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffff00ffu) | (((((edx >> 8) & 0xffu) ^ ((edx >> 8) & 0xffu)) & 0xffu) << 8);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, 0u, 0x540598u, 1, ((edx >> 8) & 0xffu));
    edx = 0x421ac0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x418840u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc4u, 4);
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
}

uint32_t lifted_f4bf3e0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4BF3E0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4BF3E0_STACK, 0, entry);
    goto L_4bf3e0;
L_4bf342:
    eax = 0x1u;
L_4bf347:
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
L_4bf3e0:
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
    esp = esp - 0x1cu;
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = lift_load(&env, eax, 0x1b8u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    eax = lift_load(&env, eax, 0xa4u, 4);
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xffffffd8u, 4, edx);
    eax = lift_load(&env, eax, 0x18u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    edi = lift_load(&env, eax, 0x0u, 4);
    esi = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4bf55c;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4bf521;
L_4bf426:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x0u, 1)) & 0xffu);
    esi = esi - 1u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x8u, &fl);
        eax = r;
    }
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4bf44c;
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bf347;
    edi = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
L_4bf44c:
    eax = eax ^ eax;
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x0u, 1)) & 0xffu);
    ebx = ebx + eax;
    esi = esi - 1u;
    lift_store(&env, ebp, 0xffffffd8u, 4, ebx);
    eax = (ebx + 0xfffffffeu);
    edi = edi + 1u;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4bf553;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = lift_load(&env, eax, 0x1a0u, 4);
    {
        (void)lift_sub(32, ebx, 0xfeu, &fl);
    }
    if (!fl.zf)
        goto L_4bf53c;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_load(&env, eax, 0x60u, 4);
L_4bf483:
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffd0u, 4), &fl);
    }
    if (!fl.cf)
        goto L_4bf491;
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
L_4bf491:
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffd0u, 4);
    edx = 0x1u;
    ecx = lift_load(&env, ecx, 0x4u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = ebx + 0x14u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x0u, 4, 0x0u);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0x1a0u, 1)) & 0xffu);
    lift_store(&env, eax, 0x4u, 1, (edx & 0xffu));
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, eax, 0x8u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    lift_store(&env, eax, 0xcu, 4, edx);
    edx = (eax + 0x14u);
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    lift_store(&env, eax, 0x10u, 4, edx);
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, edx, 0xa8u, 4, 0x0u);
    ebx = lift_load(&env, ebp, 0xffffffd0u, 4);
    lift_store(&env, edx, 0xa4u, 4, eax);
    edx = edx ^ edx;
L_4bf4ea:
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (!fl.cf)
        goto L_4bf590;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, eax, 0x0u, 4, edi);
    lift_store(&env, eax, 0x4u, 4, esi);
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xa8u, 4, edx);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4bf575;
L_4bf507:
    {
        (void)lift_sub(32, edx, ebx, &fl);
    }
    if (!fl.cf)
        goto L_4bf4ea;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4bf4ea;
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, edi, 0x0u, 1)) & 0xffu);
    edi = edi + 1u;
    esi = esi - 1u;
    lift_store(&env, ecx, 0x0u, 1, (eax & 0xffu));
    eax = (ecx + 0x1u);
    edx = edx + 1u;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    goto L_4bf507;
L_4bf521:
    edx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bf347;
    edi = lift_load(&env, edx, 0x0u, 4);
    esi = lift_load(&env, edx, 0x4u, 4);
    goto L_4bf426;
L_4bf53c:
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = ((ebx * 4u));
    eax = eax + edx;
    eax = lift_load(&env, eax, 0xfffffce4u, 4);
    goto L_4bf483;
L_4bf553:
    ebx = ebx ^ ebx;
    edx = edx ^ edx;
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    goto L_4bf4ea;
L_4bf55c:
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_load(&env, ecx, 0x10u, 4);
    edx = lift_load(&env, edx, 0xa8u, 4);
    eax = eax + edx;
    ebx = lift_load(&env, ecx, 0xcu, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    goto L_4bf4ea;
L_4bf575:
    ecx = lift_load(&env, ebp, 0xffffffe4u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0xcu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4bf347;
    edi = lift_load(&env, ecx, 0x0u, 4);
    esi = lift_load(&env, ecx, 0x4u, 4);
    goto L_4bf507;
L_4bf590:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4bf5c4;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = lift_load(&env, eax, 0x130u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4bf650;
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x130u, 4, edx);
L_4bf5b0:
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = lift_load(&env, eax, 0x10u, 4);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = lift_load(&env, eax, 0x8u, 4);
    eax = eax - ebx;
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
L_4bf5c4:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0xa4u, 4, 0x0u);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, eax, 0x1a0u, 4);
    {
        (void)lift_sub(32, eax, 0xe0u, &fl);
    }
    if (!fl.cf)
        goto L_4bf68a;
L_4bf5e5:
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x5bu);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    edx = lift_load(&env, edx, 0x0u, 4);
    eax = lift_load(&env, eax, 0x1a0u, 4);
    lift_store(&env, edx, 0x18u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    ebx = ebx + ecx;
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, eax, 0x1cu, 4, ebx);
    ecx = lift_load(&env, ecx, 0x0u, 4);
    edx = 0x1u;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x4u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4bf61f:
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    lift_store(&env, eax, 0x0u, 4, edi);
    ebx = lift_load(&env, ebp, 0xffffffd8u, 4);
    lift_store(&env, eax, 0x4u, 4, esi);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4bf342;
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = lift_load(&env, ebx, 0x18u, 4);
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x10u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
L_4bf650:
    ecx = lift_load(&env, edx, 0x0u, 4);
    eax = edx;
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4bf660;
L_4bf658:
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4bf658;
L_4bf660:
    edx = lift_load(&env, ebp, 0xffffffd4u, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
    goto L_4bf5b0;
L_4bf66a:
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bef10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4bf61f;
L_4bf67a:
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4bf190u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4bf61f;
L_4bf68a:
    if (fl.cf || fl.zf)
        goto L_4bf66a;
    {
        (void)lift_sub(32, eax, 0xeeu, &fl);
    }
    if (fl.zf)
        goto L_4bf67a;
    goto L_4bf5e5;
}

uint32_t lifted_f4cb820(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CB820_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CB820_STACK, 1, entry);
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
    lift_store(&env, esp, 0x1cu, 4, eax);
    ebp = edx;
    lift_store(&env, esp, 0x18u, 4, ebx);
    edi = ecx;
    {
        (void)lift_sub(32, ebx, 0xfffffffeu, &fl);
    }
    if (!fl.zf)
        goto L_4cb855;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce760u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, eax, 0x8u, 4);
    {
        uint32_t v = lift_load(&env, esp, 0x30u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, esp, 0x20u, 4);
    esi = lift_load(&env, eax, 0x0u, 4);
    ecx = edi;
    ebx = ebp;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, esi, 0x4u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    goto L_4cb8f5;
L_4cb855:
    esi = esi ^ esi;
    {
        (void)lift_sub(32, ebx, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4cb872;
    eax = ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = eax & 0xffffu;
    esi = (eax & 0xffffu);
    eax = lift_load(&env, esp, 0x18u, 2);
    lift_store(&env, esp, 0x18u, 4, eax);
L_4cb872:
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4cb87b;
    esi = 0x111u;
L_4cb87b:
    ebx = lift_load(&env, esp, 0x1cu, 4);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    eax = lift_load(&env, esp, 0x1cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ebx, 0x30u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4cb896;
    goto L_4cb8f3;
L_4cb890:
    ebx = lift_load(&env, ebx, 0x0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4cb8f3;
L_4cb896:
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebx, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d0b30u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cb890;
    {
        uint32_t v = lift_load(&env, esp, 0x30u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, eax, 0x10u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = (eax + 0x14u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = (esp + 0x18u);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    eax = lift_load(&env, esp, 0x18u, 4);
    lift_store(&env, esp, 0xcu, 4, eax);
    eax = lift_load(&env, esp, 0x1cu, 4);
    lift_store(&env, esp, 0x10u, 4, eax);
    eax = lift_load(&env, esp, 0x20u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, esp, 0x28u, 4);
    edx = ebp;
    {
        uint32_t v = lift_load(&env, esp, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esp, 0x1cu, 4, eax);
    {
        uint32_t v = lift_load(&env, esp, 0x14u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, esp, 0x34u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cb5a0u, eax, edx, ebx, ecx, 6, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 24u;
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
L_4cb8f3:
    eax = eax ^ eax;
L_4cb8f5:
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

uint32_t lifted_f4cfd20(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4CFD20_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4CFD20_STACK, 1, entry);
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
    esp = esp - 0x8u;
    esi = lift_load(&env, esp, 0x1cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce220u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    ebx = lift_load(&env, eax, 0x14u, 4);
    lift_store(&env, esp, 0x4u, 4, eax);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4cfde2;
    edx = esi;
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf940u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x54u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = lift_load(&env, ebx, 0x0u, 4);
    eax = ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x84u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0xfffffffcu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19f0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    edi = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cfa10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    eax = (eax & 0xffffff00u) | (((fl.zf) ? 1u : 0u) & 0xffu);
    eax = (eax & 0xffu);
    lift_store(&env, esp, 0x0u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x14u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cfdb4;
    edx = 0x4cc760u;
    eax = 0x5c7b84u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dc030u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x20u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cfdb4;
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
        uint32_t v = 0x36fu;
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cf650u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cfdb4;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edi, 0x20u, 4), eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_4cfdb4:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4cfdcd;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cfa10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
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
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ad0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    lift_store(&env, ebp, 0x0u, 4, eax);
L_4cfdcd:
    eax = lift_load(&env, esp, 0x4u, 4);
    lift_store(&env, eax, 0x14u, 4, 0x0u);
    {
        uint32_t r = lift_add(32, esp, 0x8u, &fl);
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
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4cfde2:
    {
        uint32_t v = 0xfffffffcu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19f0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4cfe2e;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x502778u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1abcu, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        uint32_t v = 0x502778u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19ccu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4cfe2e;
    {
        (void)lift_sub(32, lift_load(&env, edi, 0x28u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4cfe1e;
    eax = 0x4cfc90u;
    goto L_4cfe23;
L_4cfe1e:
    eax = 0x4cfa20u;
L_4cfe23:
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
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ad0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
L_4cfe2e:
    {
        uint32_t r = lift_add(32, esp, 0x8u, &fl);
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
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d2710(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D2710_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D2710_STACK, 0, entry);
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
    esp = esp - 0x30u;
    ebp = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cccc0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4d2729;
    esi = esi ^ esi;
    goto L_4d272c;
L_4d2729:
    esi = lift_load(&env, edx, 0x1cu, 4);
L_4d272c:
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4d276d;
    {
        (void)lift_and(32, ebx, 0x40000000u, &fl);
    }
    if (fl.zf)
        goto L_4d2744;
    {
        uint32_t v = lift_load(&env, ebp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19c8u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    goto L_4d2750;
L_4d2744:
    {
        uint32_t v = 0x4u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a04u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_4d2750:
    esi = eax;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4d276d;
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
        uint32_t v = 0x36bu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a94u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4d276d;
    esi = eax;
L_4d276d:
    eax = esp;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, ebp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19f8u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, ebx, 0x40000000u, &fl);
    }
    if (!fl.zf)
        goto L_4d27d6;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4d27a0;
    {
        uint32_t v = 0xfffffff0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19f0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        (void)lift_and(32, eax, 0x10000000u, &fl);
    }
    if (fl.zf)
        goto L_4d279e;
    {
        (void)lift_and(32, eax, 0x20000000u, &fl);
    }
    if (fl.zf)
        goto L_4d27a0;
L_4d279e:
    esi = esi ^ esi;
L_4d27a0:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x14u);
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
        uint32_t v = 0x30u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1af4u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4d27c7;
    ecx = 0x4u;
    edi = (esp + 0x20u);
    esi = (esp + 0x10u);
    lift_string(&env, 0, 4, 1, &eax, &ecx, &esi, &edi, &fl);
    goto L_4d280c;
L_4d27c7:
    eax = (esp + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19f8u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    goto L_4d280c;
L_4d27d6:
    {
        uint32_t v = lift_load(&env, ebp, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f19c8u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    ebx = eax;
    eax = (esp + 0x10u);
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
    eax = lift_call(&env, 0x4f196cu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    eax = (esp + 0x20u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f196cu, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    {
        uint32_t v = 0x2u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (esp + 0x24u);
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
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a48u, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
L_4d280c:
    edx = lift_load(&env, esp, 0x20u, 4);
    edx = edx + lift_load(&env, esp, 0x28u, 4);
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
    esi = lift_load(&env, esp, 0x8u, 4);
    esi = esi - lift_load(&env, esp, 0x0u, 4);
    ebx = eax;
    edx = esi;
    eax = esi;
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
    edx = lift_load(&env, esp, 0x24u, 4);
    edx = edx + lift_load(&env, esp, 0x2cu, 4);
    ebx = ebx - eax;
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
    edx = lift_load(&env, esp, 0xcu, 4);
    edx = edx - lift_load(&env, esp, 0x4u, 4);
    ecx = eax;
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
    ecx = ecx - eax;
    {
        (void)lift_sub(32, ebx, lift_load(&env, esp, 0x10u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4d2865;
    ebx = lift_load(&env, esp, 0x10u, 4);
    goto L_4d2874;
L_4d2865:
    eax = (ebx + esi);
    {
        (void)lift_sub(32, eax, lift_load(&env, esp, 0x18u, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4d2874;
    ebx = lift_load(&env, esp, 0x18u, 4);
    ebx = ebx - esi;
L_4d2874:
    {
        (void)lift_sub(32, ecx, lift_load(&env, esp, 0x14u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4d2880;
    ecx = lift_load(&env, esp, 0x14u, 4);
    goto L_4d2897;
L_4d2880:
    eax = lift_load(&env, esp, 0xcu, 4);
    eax = eax - lift_load(&env, esp, 0x4u, 4);
    edx = (ecx + eax);
    {
        (void)lift_sub(32, edx, lift_load(&env, esp, 0x1cu, 4), &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4d2897;
    ecx = lift_load(&env, esp, 0x1cu, 4);
    ecx = ecx - eax;
L_4d2897:
    {
        uint32_t v = 0x15u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = ebp;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccd80u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    {
        uint32_t r = lift_add(32, esp, 0x30u, &fl);
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

uint32_t lifted_f4d50d0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D50D0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D50D0_STACK, 0, entry);
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
    esp = esp - 0x104u;
    edi = edx;
    {
        uint32_t v = lift_load(&env, eax, 0x1cu, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1a98u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx ^ ebx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f179cu, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    ebp = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ce740u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4d5130;
L_4d510b:
    {
        uint32_t v = 0x104u;
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
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f179cu, eax, edx, ebx, ecx, 4, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 16u;
    edx = esp;
    ecx = lift_load(&env, esi, 0x0u, 4);
    eax = esi;
    ebx = ebx + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, ecx, 0x80u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, ebx, ebp, &fl);
    }
    if (fl.cf)
        goto L_4d510b;
L_4d5130:
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1798u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4d79c0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4D79C0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4D79C0_STACK, 0, entry);
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
    esp = esp - 0x4u;
    esi = eax;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4d7a07;
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
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esi, 0x4u, 4);
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1d08u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4d79f5;
    eax = (esi + 0xcu);
    eax = lift_load(&env, eax, 0x0u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1bbcu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9930u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
L_4d79f5:
    {
        (void)lift_sub(32, ebx, lift_load(&env, esp, 0x0u, 4), &fl);
    }
    if (fl.zf)
        goto L_4d7a07;
    eax = lift_load(&env, esi, 0xcu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xffffffffu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0xdu;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4d9a10u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
L_4d7a07:
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dabbe(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DABBE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DABBE_STACK, 0, entry);
    goto L_4e3ac0;
L_4e3ac0:
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
    esp = esp - 0x104u;
    ebx = eax;
    esi = edx;
    eax = esp;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x104u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b90u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e3aec;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    goto L_4e3b51;
L_4e3aec:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e3b19;
    eax = eax + 1u;
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e3af7;
    eax = esi;
L_4e3af7:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e3b34;
    eax = 0x5u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    {
        uint32_t r = lift_add(32, esp, 0x104u, &fl);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e3b19:
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e3b34;
    eax = 0xeu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    {
        uint32_t r = lift_add(32, esp, 0x104u, &fl);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e3b34:
    esi = esp;
    ecx = ecx + 1u;
    edi = ebx;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    eax = ebx;
L_4e3b51:
    {
        uint32_t r = lift_add(32, esp, 0x104u, &fl);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4dfac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DFAC0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DFAC0_STACK, 0, entry);
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
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x4u;
    (void)(edx);
    edi = eax;
    edx = lift_load(&env, ebx, 0x28u, 4);
    ebp = ecx;
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4dfb19;
L_4dfad4:
    edx = edx ^ edx;
    eax = esp;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, edi, 0x0u, 2)) & 0xffffu);
    edi = edi + 0x2u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e62e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4dfaf8;
    {
        (void)lift_sub(32, eax, lift_load(&env, ebx, 0x28u, 4), &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4dfb12;
    esi = esp;
L_4dfaf2:
    ecx = ecx - 1u;
    {
        (void)lift_sub(32, ecx, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4dfb00;
L_4dfaf8:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0x28u, 4), 0x0u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4dfad4;
    goto L_4dfb19;
L_4dfb00:
    edx = edx ^ edx;
    eax = ebx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, ebp, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebx, 0x28u, 4);
    eax = eax - 1u;
    esi = esi + 1u;
    lift_store(&env, ebx, 0x28u, 4, eax);
    goto L_4dfaf2;
L_4dfb12:
    lift_store(&env, ebx, 0x28u, 4, 0x0u);
L_4dfb19:
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
        (void)(v);
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

uint32_t lifted_f4dfb24(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4DFB24_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4DFB24_STACK, 0, entry);
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
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x10u;
    esi = eax;
    ecx = ebx;
    eax = 0u;
    (void)(eax);
    lift_store(&env, ebx, 0x20u, 4, 0x0u);
    lift_store(&env, ebx, 0x24u, 4, 0x0u);
    lift_store(&env, ebx, 0x28u, 4, 0x0u);
    lift_store(&env, ebx, 0x2cu, 4, 0x0u);
    lift_store(&env, ebx, 0x30u, 4, 0x0u);
    edi = esi;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebx, 0x15u, 1)) & 0xffu);
    lift_store(&env, ebx, 0x34u, 4, 0x0u);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x69u, &fl);
    }
    if (fl.cf)
        goto L_4dfb84;
    if (fl.cf || fl.zf)
        goto L_4dfbfe;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x75u, &fl);
    }
    if (fl.cf)
        goto L_4dfb7b;
    if (fl.cf || fl.zf)
        goto L_4dfb97;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4dfb97;
    goto L_4dfcdb;
L_4dfb7b:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6fu, &fl);
    }
    if (fl.zf)
        goto L_4dfb97;
    goto L_4dfcdb;
L_4dfb84:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x58u, &fl);
    }
    if (fl.cf)
        goto L_4dfcdb;
    if (fl.cf || fl.zf)
        goto L_4dfb97;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x64u, &fl);
    }
    if (fl.zf)
        goto L_4dfbfe;
    goto L_4dfcdb;
L_4dfb97:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1fu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfbbd;
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    eax = lift_load(&env, ebp, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x4u, 4, eax);
    goto L_4dfcdb;
L_4dfbbd:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4dfbd6;
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    goto L_4dfcdb;
L_4dfbd6:
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    eax = lift_load(&env, ebp, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4dfcdb;
    eax = eax ^ eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, esp, 0x8u, 2)) & 0xffffu);
    lift_store(&env, esp, 0x8u, 4, eax);
    goto L_4dfcdb;
L_4dfbfe:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1fu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfc21;
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x0u, 4, eax);
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x4u, 4, eax);
    goto L_4dfc54;
L_4dfc21:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4dfc33;
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    eax = lift_load(&env, ebp, 0xfffffffcu, 4);
    goto L_4dfc50;
L_4dfc33:
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu) << 8);
    lift_store(&env, esp, 0x8u, 4, eax);
    {
        (void)lift_and(8, ((ebx >> 8) & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4dfc54;
    eax = lift_load(&env, esp, 0x6u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
L_4dfc50:
    lift_store(&env, esp, 0x8u, 4, eax);
L_4dfc54:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1fu, 1)) & 0xffu);
    eax = eax ^ eax;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfc67;
    {
        (void)lift_and(8, lift_load(&env, esp, 0x7u, 1), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4dfc6e;
    goto L_4dfc72;
L_4dfc67:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4dfc72;
L_4dfc6e:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dfcb4;
L_4dfc72:
    eax = lift_load(&env, ecx, 0x20u, 4);
    ebx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, ebx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x2du);
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1fu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfcae;
    ebx = lift_load(&env, esp, 0x0u, 4);
    ebp = lift_load(&env, esp, 0x4u, 4);
    {
        uint32_t a = ebx;
        ebx = (~a) & lift_mask(4);
    }
    {
        uint32_t a = ebp;
        ebp = (~a) & lift_mask(4);
    }
    lift_store(&env, esp, 0x0u, 4, ebx);
    eax = (ebx + 0x1u);
    lift_store(&env, esp, 0x4u, 4, ebp);
    lift_store(&env, esp, 0x0u, 4, eax);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dfca6;
    eax = (ebp + 0x1u);
    goto L_4dfca8;
L_4dfca6:
    eax = ebp;
L_4dfca8:
    lift_store(&env, esp, 0x4u, 4, eax);
    goto L_4dfcdb;
L_4dfcae:
    lift_store(&env, esp, 0x8u, 4, 0u - lift_load(&env, esp, 0x8u, 4));
    goto L_4dfcdb;
L_4dfcb4:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4dfcca;
    eax = lift_load(&env, ecx, 0x20u, 4);
    ebx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, ebx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x2bu);
    goto L_4dfcdb;
L_4dfcca:
    {
        (void)lift_and(8, (eax & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4dfcdb;
    eax = lift_load(&env, ecx, 0x20u, 4);
    ebx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, ebx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x20u);
L_4dfcdb:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x15u, 1)) & 0xffu);
    ebx = 0xau;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x64u, &fl);
    }
    if (fl.cf)
        goto L_4dfd48;
    if (fl.cf || fl.zf)
        goto L_4dfef8;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x6fu, &fl);
    }
    if (fl.cf)
        goto L_4dfd29;
    if (fl.cf || fl.zf)
        goto L_4dfed8;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x73u, &fl);
    }
    if (fl.cf)
        goto L_4dfd1c;
    if (fl.cf || fl.zf)
        goto L_4dfdf1;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x75u, &fl);
    }
    if (fl.cf)
        goto L_4e010d;
    if (fl.cf || fl.zf)
        goto L_4dfef8;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x78u, &fl);
    }
    if (fl.zf)
        goto L_4dfe93;
    goto L_4e010d;
L_4dfd1c:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x70u, &fl);
    }
    if (fl.zf)
        goto L_4dffad;
    goto L_4e010d;
L_4dfd29:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x66u, &fl);
    }
    if (fl.cf)
        goto L_4dfdce;
    if (fl.cf || fl.zf)
        goto L_4dfd99;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x67u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4dfdce;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x69u, &fl);
    }
    if (fl.zf)
        goto L_4dfef8;
    goto L_4e010d;
L_4dfd48:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x47u, &fl);
    }
    if (fl.cf)
        goto L_4dfd84;
    if (fl.cf || fl.zf)
        goto L_4dfdce;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x53u, &fl);
    }
    if (fl.cf)
        goto L_4dfd77;
    if (fl.cf || fl.zf)
        goto L_4dfdf1;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x58u, &fl);
    }
    if (fl.cf)
        goto L_4e010d;
    if (fl.cf || fl.zf)
        goto L_4dfe93;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x63u, &fl);
    }
    if (fl.zf)
        goto L_4e0040;
    goto L_4e010d;
L_4dfd77:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x50u, &fl);
    }
    if (fl.zf)
        goto L_4dffad;
    goto L_4e010d;
L_4dfd84:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x45u, &fl);
    }
    if (fl.cf)
        goto L_4dfd8c;
    if (fl.cf || fl.zf)
        goto L_4dfdce;
    goto L_4dfd99;
L_4dfd8c:
    {
        (void)lift_sub(8, (eax & 0xffu), 0x43u, &fl);
    }
    if (fl.zf)
        goto L_4e00cc;
    goto L_4e010d;
L_4dfd99:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4dfdce;
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    lift_store(&env, esp, 0x8u, 4, eax);
    ebx = ecx;
    edx = eax;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df978u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xffffffffu;
    edx = 0u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x28u, 4, eax);
    goto L_4e0120;
L_4dfdce:
    ebx = ecx;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dfa74u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dfa7cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0u;
    edi = (esi + 0x1u);
    (void)(eax);
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4dfdf1:
    lift_store(&env, esi, 0x0u, 1, 0x0u);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    {
        (void)lift_and(8, (eax & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4dfe18;
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x8u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    eax = lift_load(&env, ebp, 0xfffffff8u, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xfffffffcu, 2)) & 0xffffu);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4dfe12;
    {
        (void)lift_and(16, (edx & 0xffffu), (edx & 0xffffu), &fl);
    }
    if (fl.zf)
        goto L_4dfe40;
L_4dfe12:
    (void)(edx);
    edi = eax;
    goto L_4dfe40;
L_4dfe18:
    {
        (void)lift_and(8, (eax & 0xffu), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4dfe2c;
    esi = lift_load(&env, edx, 0x0u, 4);
    esi = esi + 0x4u;
    lift_store(&env, edx, 0x0u, 4, esi);
    eax = lift_load(&env, esi, 0xfffffffcu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dfe40;
    goto L_4dfe3a;
L_4dfe2c:
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = lift_load(&env, ebx, 0xfffffffcu, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4dfe40;
L_4dfe3a:
    edx = 0u;
    edi = eax;
    (void)(edx);
L_4dfe40:
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x53u, &fl);
    }
    if (!fl.zf)
        goto L_4dfe4e;
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4dfe54;
    goto L_4dfe62;
L_4dfe4e:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4dfe62;
L_4dfe54:
    edx = 0u;
    eax = edi;
    ebx = lift_load(&env, ecx, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df8a8u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4dfe6e;
L_4dfe62:
    edx = 0u;
    eax = edi;
    ebx = lift_load(&env, ecx, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dfe6e:
    edx = lift_load(&env, ecx, 0x8u, 4);
    lift_store(&env, ecx, 0x28u, 4, eax);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4e0120;
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e0120;
    lift_store(&env, ecx, 0x28u, 4, edx);
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4dfe93:
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfed3;
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1fu, 1), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfeae;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dfeb5;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dfed3;
    goto L_4dfeb5;
L_4dfeae:
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4dfed3;
L_4dfeb5:
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x30u);
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    edx = (esi + eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x15u, 1)) & 0xffu);
    lift_store(&env, edx, 0x0u, 1, (eax & 0xffu));
L_4dfed3:
    ebx = 0x10u;
L_4dfed8:
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x6fu, &fl);
    }
    if (!fl.zf)
        goto L_4dfef8;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    ebx = 0x8u;
    {
        (void)lift_and(8, (edx & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dfef8;
    eax = lift_load(&env, ecx, 0x20u, 4);
    edx = (eax + 0x1u);
    lift_store(&env, ecx, 0x20u, 4, edx);
    lift_store(&env, esi, eax + 0x0u, 1, 0x30u);
L_4dfef8:
    edx = 0u;
    eax = lift_load(&env, ecx, 0x20u, 4);
    (void)(edx);
    eax = eax + esi;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, ecx, 0x1fu, 1)) & 0xffu) << 8);
    edi = eax;
    {
        (void)lift_and(8, ((edx >> 8) & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4dff41;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff26;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x0u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff26;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff26;
    lift_store(&env, eax, 0x0u, 1, 0x0u);
    eax = eax ^ eax;
    goto L_4dff7f;
L_4dff26:
    edx = lift_load(&env, ecx, 0x20u, 4);
    eax = esp;
    edx = edx + esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e63b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x58u, &fl);
    }
    if (!fl.zf)
        goto L_4dff71;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e012cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4dff71;
L_4dff41:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff56;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x8u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dff56;
    lift_store(&env, eax, 0x0u, 1, 0x0u);
    eax = eax ^ eax;
    goto L_4dff7f;
L_4dff56:
    edx = lift_load(&env, ecx, 0x20u, 4);
    eax = lift_load(&env, esp, 0x8u, 4);
    edx = edx + esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e64a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x58u, &fl);
    }
    if (!fl.zf)
        goto L_4dff71;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e012cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dff71:
    ebx = 0xffffffffu;
    edx = 0u;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4dff7f:
    lift_store(&env, ecx, 0x28u, 4, eax);
    edx = eax;
    eax = lift_load(&env, ecx, 0x8u, 4);
    {
        (void)lift_sub(32, edx, eax, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4dff90;
    eax = eax - edx;
    lift_store(&env, ecx, 0x24u, 4, eax);
L_4dff90:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x8u, 4), 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_4e0120;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dfa7cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4dffad:
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x4u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4dffc9;
    {
        (void)lift_and(8, lift_load(&env, ecx, 0x1eu, 1), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4dffc2;
    lift_store(&env, ecx, 0x4u, 4, 0xdu);
    goto L_4dffc9;
L_4dffc2:
    lift_store(&env, ecx, 0x4u, 4, 0x8u);
L_4dffc9:
    lift_store(&env, ecx, 0x1eu, 1, lift_load(&env, ecx, 0x1eu, 1) & 0xf9u);
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    ebp = lift_load(&env, eax, 0xfffffffcu, 4);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4e0008;
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    ebx = 0x4u;
    eax = lift_load(&env, eax, 0xfffffffcu, 4);
    edx = esi;
    eax = eax & 0xffffu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df914u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x8u;
    edx = (esi + 0x5u);
    eax = ebp;
    lift_store(&env, esi, 0x4u, 1, 0x3au);
    goto L_4e0011;
L_4e0008:
    ebx = 0x8u;
    edx = esi;
    eax = ebp;
L_4e0011:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df914u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(8, lift_load(&env, ecx, 0x15u, 1), 0x50u, &fl);
    }
    if (!fl.zf)
        goto L_4e0023;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e012cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e0023:
    ebx = 0xffffffffu;
    edx = 0u;
    eax = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4df884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x20u, 4, eax);
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4e0040:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, ecx, 0x1eu, 1)) & 0xffu);
    lift_store(&env, ecx, 0x20u, 4, 0x1u);
    {
        (void)lift_and(8, (ebx & 0xffu), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4e00b4;
    ebx = lift_load(&env, edx, 0x0u, 4);
    ebx = ebx + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebx);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebx, 0xfffffffcu, 2)) & 0xffffu);
    edx = edx ^ edx;
    edx = (edx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = (esp + 0xcu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e62e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4e0120;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0xcu, 1)) & 0xffu);
    ebp = lift_load(&env, 0u, 0x5c8950u, 4);
    lift_store(&env, esi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_and(32, ebp, ebp, &fl);
    }
    if (fl.zf)
        goto L_4e0120;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0xcu, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x5c8961u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | (((eax & 0xffu) & 0x1u) & 0xffu);
    {
        uint32_t r = lift_and(32, eax, 0xffu, &fl);
        eax = r;
    }
    if (fl.zf)
        goto L_4e0120;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esp, 0xdu, 1)) & 0xffu);
    lift_store(&env, esi, 0x1u, 1, (eax & 0xffu));
    lift_store(&env, ecx, 0x20u, 4, lift_load(&env, ecx, 0x20u, 4) + 1u);
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4e00b4:
    eax = lift_load(&env, edx, 0x0u, 4);
    eax = eax + 0x4u;
    lift_store(&env, edx, 0x0u, 4, eax);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0xfffffffcu, 1)) & 0xffu);
    lift_store(&env, esi, 0x0u, 1, (eax & 0xffu));
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4e00cc:
    ebp = lift_load(&env, edx, 0x0u, 4);
    ebp = ebp + 0x4u;
    lift_store(&env, edx, 0x0u, 4, ebp);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, ebp, 0xfffffffcu, 2)) & 0xffffu);
    edx = edx & 0xffffu;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e62e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_sub(32, eax, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_4e00fa;
    lift_store(&env, ecx, 0x20u, 4, eax);
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4e00fa:
    lift_store(&env, ecx, 0x20u, 4, 0x0u);
    edx = 0u;
    eax = edi;
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
        (void)(v);
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
L_4e010d:
    lift_store(&env, ecx, 0x4u, 4, 0x0u);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ecx, 0x15u, 1)) & 0xffu);
    lift_store(&env, esi, 0x0u, 1, (eax & 0xffu));
    lift_store(&env, ecx, 0x20u, 4, 0x1u);
L_4e0120:
    edx = 0u;
    eax = edi;
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
        (void)(v);
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

uint32_t lifted_f4e3ac0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E3AC0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E3AC0_STACK, 0, entry);
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
    esp = esp - 0x104u;
    ebx = eax;
    esi = edx;
    eax = esp;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x104u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1b90u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    ecx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e3aec;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e0884u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    goto L_4e3b51;
L_4e3aec:
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e3b19;
    eax = eax + 1u;
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e3af7;
    eax = esi;
L_4e3af7:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e3b34;
    eax = 0x5u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    {
        uint32_t r = lift_add(32, esp, 0x104u, &fl);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e3b19:
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e3b34;
    eax = 0xeu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dae70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = eax ^ eax;
    {
        uint32_t r = lift_add(32, esp, 0x104u, &fl);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4e3b34:
    esi = esp;
    ecx = ecx + 1u;
    edi = ebx;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    eax = ebx;
L_4e3b51:
    {
        uint32_t r = lift_add(32, esp, 0x104u, &fl);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e63b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E63B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E63B0_STACK, 0, entry);
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
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esp = esp - 0x44u;
    esi = eax;
    lift_store(&env, esp, 0x3cu, 4, edx);
    edi = (esp + 0x34u);
    ebp = (esp + 0x1u);
    eax = 0u;
    lift_store(&env, esp, 0x40u, 4, edx);
    (void)(eax);
    edx = edx ^ edx;
    {
        uint32_t r = lift_xor(8, ((eax >> 8) & 0xffu), ((eax >> 8) & 0xffu), &fl);
        eax = (eax & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_string(&env, 0, 4, 0, &eax, &ecx, &esi, &edi, &fl);
    lift_store(&env, esp, 0x24u, 4, ebx);
    lift_store(&env, esp, 0x28u, 4, edx);
    lift_store(&env, esp, 0x0u, 1, ((eax >> 8) & 0xffu));
L_4e63df:
    edi = (esp + 0x2cu);
    esi = (esp + 0x34u);
    ebx = (esp + 0x24u);
    eax = (esp + 0x34u);
    edx = lift_load(&env, eax, 0x4u, 4);
    eax = lift_load(&env, eax, 0x0u, 4);
    ecx = lift_load(&env, ebx, 0x4u, 4);
    ebx = lift_load(&env, ebx, 0x0u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e88bfu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x4u, 4, edx);
    lift_store(&env, esi, 0x0u, 4, eax);
    lift_store(&env, edi, 0x4u, 4, ecx);
    lift_store(&env, edi, 0x0u, 4, ebx);
    eax = lift_load(&env, esp, 0x2cu, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, eax, 0x50979cu, 1)) & 0xffu);
    lift_store(&env, ebp, 0x0u, 1, (eax & 0xffu));
    ebx = lift_load(&env, esp, 0x34u, 4);
    ebp = ebp + 1u;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e63df;
    {
        (void)lift_sub(32, lift_load(&env, esp, 0x38u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e63df;
L_4e6425:
    ebx = lift_load(&env, esp, 0x40u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffffu, 1)) & 0xffu);
    ebp = ebp - 1u;
    esi = (ebx + 0x1u);
    lift_store(&env, ebx, 0x0u, 1, (eax & 0xffu));
    lift_store(&env, esp, 0x40u, 4, esi);
    {
        (void)lift_and(8, (eax & 0xffu), (eax & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4e6425;
    eax = lift_load(&env, esp, 0x3cu, 4);
    {
        uint32_t r = lift_add(32, esp, 0x44u, &fl);
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
        (void)(v);
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

uint32_t lifted_f4e65b0(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E65B0_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E65B0_STACK, 0, entry);
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
    edi = eax;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
    ecx = ecx - ecx;
    ecx = ecx - 1u;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    {
        uint32_t a = ecx;
        ecx = (~a) & lift_mask(4);
    }
    ecx = ecx - 1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    ecx = ecx + 1u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e65ee;
    edi = eax;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
L_4e65ee:
    eax = edx;
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
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e6b50(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6B50_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6B50_STACK, 0, entry);
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        (void)lift_sub(32, lift_load(&env, eax, 0x0u, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e6b5a;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, eax, 0x0u, 4), eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
L_4e6b5a:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4e6b5c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6B5C_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6B5C_STACK, 0, entry);
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
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = 0x51c440u;
    edx = (edx & 0xffff00ffu) | ((((eax & 0xffu)) & 0xffu) << 8);
L_4e6b68:
    eax = 0x51c308u;
    ebx = esi;
    edx = (edx & 0xffffff00u) | ((((edx >> 8) & 0xffu)) & 0xffu);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e6b8f;
L_4e6b75:
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e6b85;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, eax, 0x1u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, (edx & 0xffu), ((ecx >> 8) & 0xffu), &fl);
    }
    if (fl.cf)
        goto L_4e6b85;
    ebx = eax;
    edx = (edx & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
L_4e6b85:
    eax = eax + 0x6u;
    {
        (void)lift_sub(32, eax, 0x51c440u, &fl);
    }
    if (fl.cf)
        goto L_4e6b75;
L_4e6b8f:
    {
        (void)lift_sub(32, ebx, 0x51c440u, &fl);
    }
    if (fl.zf)
        goto L_4e6ba4;
    eax = (ebx + 0x2u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6b50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebx, 0x0u, 1, 0x2u);
    goto L_4e6b68;
L_4e6ba4:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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

uint32_t lifted_f4e6bac(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E6BAC_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E6BAC_STACK, 0, entry);
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
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    esi = 0x51c46au;
    ecx = (ecx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = (edx & 0xffff00ffu) | ((((edx & 0xffu)) & 0xffu) << 8);
L_4e6bb9:
    eax = 0x51c440u;
    ebx = esi;
    edx = (edx & 0xffffff00u) | (((ecx & 0xffu)) & 0xffu);
    {
        (void)lift_sub(32, esi, eax, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e6be0;
L_4e6bc6:
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4e6bd6;
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, eax, 0x1u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, (edx & 0xffu), ((ecx >> 8) & 0xffu), &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e6bd6;
    ebx = eax;
    edx = (edx & 0xffffff00u) | ((((ecx >> 8) & 0xffu)) & 0xffu);
L_4e6bd6:
    eax = eax + 0x6u;
    {
        (void)lift_sub(32, eax, 0x51c46au, &fl);
    }
    if (fl.cf)
        goto L_4e6bc6;
L_4e6be0:
    {
        (void)lift_sub(32, ebx, 0x51c46au, &fl);
    }
    if (fl.zf)
        goto L_4e6bfa;
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), lift_load(&env, ebx, 0x1u, 1), &fl);
    }
    if (fl.cf)
        goto L_4e6bf5;
    eax = (ebx + 0x2u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e6b50u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e6bf5:
    lift_store(&env, ebx, 0x0u, 1, 0x2u);
    goto L_4e6bb9;
L_4e6bfa:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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

uint32_t lifted_f4e7f18(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E7F18_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E7F18_STACK, 0, entry);
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
    ebp = eax;
    lift_store(&env, esp, 0x0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9d10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        ebx = r;
    }
    edi = ebp;
    ebx = ebx | eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9e30u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4e7f3b:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e7f53;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e7f3b;
L_4e7f53:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
    ecx = ecx - ecx;
    ecx = ecx - 1u;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    {
        uint32_t a = ecx;
        ecx = (~a) & lift_mask(4);
    }
    ecx = ecx - 1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    esi = (ecx + ebp);
    edx = (esi + 0x4u);
    lift_store(&env, esi, 0x0u, 1, 0x74u);
    ecx = esi;
L_4e7f6f:
    eax = ebx;
    eax = eax & 0xfu;
    edx = edx - 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7f0cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        ebx = r;
    }
    lift_store(&env, edx, 0x1u, 1, (eax & 0xffu));
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4e7f6f;
    eax = lift_load(&env, esp, 0x0u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax & 0xfu;
    lift_store(&env, esi, 0x5u, 1, 0x5fu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7f0cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x6u, 1, (eax & 0xffu));
    eax = lift_load(&env, esp, 0x0u, 4);
    eax = eax & 0xfu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e7f0cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x8u, 1, 0x2eu);
    lift_store(&env, esi, 0x9u, 1, 0x74u);
    lift_store(&env, esi, 0xau, 1, 0x6du);
    lift_store(&env, esi, 0xbu, 1, 0x70u);
    lift_store(&env, esi, 0xcu, 1, 0x0u);
    lift_store(&env, esi, 0x7u, 1, (eax & 0xffu));
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

uint32_t lifted_f4e843c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E843C_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E843C_STACK, 0, entry);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cc8u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ba0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, 0u, 0x5c8aa0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4e8464;
L_4e8459:
    {
        (void)lift_sub(32, eax, lift_load(&env, ebx, 0x4u, 4), &fl);
    }
    if (fl.zf)
        goto L_4e8464;
    ebx = lift_load(&env, ebx, 0x0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4e8459;
L_4e8464:
    {
        (void)lift_sub(32, lift_load(&env, ebx, 0xcu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e848f;
    edx = lift_load(&env, 0u, 0x509768u, 4);
    eax = lift_load(&env, ebx, 0x8u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec0e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e84dc;
    edx = 0x1u;
    eax = 0x513020u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e628cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e84dc;
L_4e848f:
    eax = 0x1u;
    edx = lift_load(&env, 0u, 0x509768u, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ec160u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_4e84b4;
    edx = 0x1u;
    eax = 0x513048u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e628cu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4e84b4:
    esi = lift_load(&env, ebx, 0x8u, 4);
    edi = ebp;
    ecx = lift_load(&env, esi, 0xf0u, 4);
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    lift_store(&env, ebx, 0xcu, 4, 0x1u);
L_4e84dc:
    lift_store(&env, ebx, 0x8u, 4, ebp);
    eax = lift_load(&env, 0u, 0x509768u, 4);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0x52u, 1, 0x1u);
    esi = lift_load(&env, 0u, 0x507c98u, 4);
    lift_store(&env, ebp, 0x53u, 1, 0x0u);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, ebp, 0xf0u, 4, eax);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4f1ce0u, eax, edx, ebx, ecx, 2, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, 0u, 0x507cccu, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ebp;
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

uint32_t lifted_f4e969c(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E969C_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E969C_STACK, 0, entry);
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
    ebp = eax;
    lift_store(&env, esp, 0x0u, 4, edx);
    lift_store(&env, esp, 0x10u, 4, ebx);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x3au, &fl);
    }
    if (!fl.zf)
        goto L_4e96b2;
    ebp = ebp + 1u;
L_4e96b2:
    esi = ebp;
L_4e96b4:
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    {
        (void)lift_and(8, (edx & 0xffu), (edx & 0xffu), &fl);
    }
    if (fl.zf)
        goto L_4e96d7;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2cu, &fl);
    }
    if (fl.zf)
        goto L_4e96d7;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2du, &fl);
    }
    if (fl.zf)
        goto L_4e96d7;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2bu, &fl);
    }
    if (fl.zf)
        goto L_4e96d7;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x30u, &fl);
    }
    if (fl.cf)
        goto L_4e96d4;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x39u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4e96d7;
L_4e96d4:
    ebp = ebp + 1u;
    goto L_4e96b4;
L_4e96d7:
    ebx = ebp;
    ebx = ebx - esi;
    {
        (void)lift_sub(32, ebx, 0x80u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4e96e8;
    ebx = 0x80u;
L_4e96e8:
    edi = lift_load(&env, esp, 0x0u, 4);
    ecx = ebx;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    ebx = ebx + edi;
    eax = (ebp + 0x1u);
    esi = esi ^ esi;
    lift_store(&env, ebx, 0x0u, 1, 0x0u);
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2du, &fl);
    }
    if (!fl.zf)
        goto L_4e9719;
    esi = 0x1u;
    goto L_4e971e;
L_4e9719:
    {
        (void)lift_sub(8, (edx & 0xffu), 0x2bu, &fl);
    }
    if (!fl.zf)
        goto L_4e9720;
L_4e971e:
    ebp = eax;
L_4e9720:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x30u, &fl);
    }
    if (fl.cf)
        goto L_4e97a8;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x39u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e97a8;
    edx = (esp + 0xcu);
    edi = edi ^ edi;
    eax = ebp;
    lift_store(&env, esp, 0x4u, 4, edi);
    lift_store(&env, esp, 0x8u, 4, edi);
    lift_store(&env, esp, 0xcu, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ebp = eax;
    {
        (void)lift_sub(8, (edx & 0xffu), 0x3au, &fl);
    }
    if (!fl.zf)
        goto L_4e9774;
    edx = (esp + 0x8u);
    eax = eax + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (edx & 0xffff00ffu) | (((lift_load(&env, eax, 0x0u, 1)) & 0xffu) << 8);
    ebp = eax;
    {
        (void)lift_sub(8, ((edx >> 8) & 0xffu), 0x3au, &fl);
    }
    if (!fl.zf)
        goto L_4e9774;
    edx = (esp + 0x4u);
    eax = eax + 1u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e9670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebp = eax;
L_4e9774:
    ebx = lift_load(&env, esp, 0xcu, 4);
    eax = ebx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax - ebx;
    edx = lift_load(&env, esp, 0x8u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = edx + eax;
    eax = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x4u, &fl);
        eax = r;
    }
    eax = eax - edx;
    edx = lift_load(&env, esp, 0x4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = edx + eax;
    eax = lift_load(&env, esp, 0x10u, 4);
    lift_store(&env, eax, 0x0u, 4, edx);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_4e97a8;
    ebx = edx;
    ebx = 0u - ebx;
    lift_store(&env, eax, 0x0u, 4, ebx);
L_4e97a8:
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
}

uint32_t lifted_f4e9e30(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4E9E30_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4E9E30_STACK, 0, entry);
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
        (void)lift_sub(8, lift_load(&env, 0u, 0x50b100u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e9eed;
    ebx = 0x50b0ecu;
    goto L_4e9e82;
L_4e9e49:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4dac40u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = eax;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4e9e7f;
    edi = eax;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
    ecx = ecx - ecx;
    ecx = ecx - 1u;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    {
        uint32_t a = ecx;
        ecx = (~a) & lift_mask(4);
    }
    ecx = ecx - 1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    {
        (void)lift_sub(32, ecx, 0x103u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4e9e7f;
    ebx = 0x103u;
    eax = 0x50b100u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ea470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4e9e89;
L_4e9e7f:
    ebx = ebx + 0x4u;
L_4e9e82:
    eax = lift_load(&env, ebx, 0x0u, 4);
    {
        (void)lift_sub(8, lift_load(&env, eax, 0x0u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e9e49;
L_4e9e89:
    {
        (void)lift_sub(8, lift_load(&env, 0u, 0x50b100u, 1), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e9ebc;
    edx = edx ^ edx;
    eax = eax ^ eax;
    edi = 0x50b100u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4e3ac0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = eax;
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
L_4e9ea3:
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 1, (eax & 0xffu));
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4e9ebb;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x1u, 1)) & 0xffu);
    esi = esi + 0x2u;
    lift_store(&env, edi, 0x1u, 1, (eax & 0xffu));
    edi = edi + 0x2u;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4e9ea3;
L_4e9ebb:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
L_4e9ebc:
    edi = 0x50b100u;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
    ecx = ecx - ecx;
    ecx = ecx - 1u;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_string(&env, 3, 1, 3, &eax, &ecx, &esi, &edi, &fl);
    {
        uint32_t a = ecx;
        ecx = (~a) & lift_mask(4);
    }
    ecx = ecx - 1u;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    eax = (ecx + 0xffffffffu);
    eax = eax + 0x50b100u;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x5cu, &fl);
    }
    if (fl.zf)
        goto L_4e9eed;
    {
        (void)lift_sub(8, (ebx & 0xffu), 0x2fu, &fl);
    }
    if (fl.zf)
        goto L_4e9eed;
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, eax, 0x0u, 1, 0x5cu);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, eax, 0x0u, 1, 0x0u);
L_4e9eed:
    eax = 0x50b100u;
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

uint32_t lifted_f4ec180(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EC180_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EC180_STACK, 0, entry);
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
    ecx = ebx;
    edi = edx;
    esi = eax;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_string(&env, 4, 1, 2, &eax, &ecx, &esi, &edi, &fl);
    if (fl.zf)
        goto L_4ec199;
    {
        uint32_t r = lift_sbb(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sbb(32, eax, 0xffffffffu, &fl);
        eax = r;
    }
L_4ec199:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
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

uint32_t lifted_f4ed096(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ED096_STACK + 4 + 4 * 1 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ED096_STACK, 1, entry);
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
    esp = esp - 0x4u;
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
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    ecx = ecx + 1u;
    lift_store(&env, ebp, 0xfffffff4u, 4, edx);
    lift_store(&env, ebp, 0xffffffe8u, 4, ecx);
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, eax, 0x8u, 1)) & 0xffu) << 8);
    edx = edx ^ edx;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4ed0d9;
    {
        (void)lift_sub(32, ebx, lift_load(&env, ebp, 0xfffffff4u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed0c5;
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        (void)lift_and(8, lift_load(&env, esi, 0x8u, 1), 0x10u, &fl);
    }
    if (!fl.zf)
        goto L_4ed0c5;
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
L_4ed0c5:
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = lift_load(&env, ebp, 0xfffffff4u, 4);
    edi = edi - esi;
    lift_store(&env, ebp, 0xfffffff4u, 4, edi);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed0d9;
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
L_4ed0d9:
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ed188;
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        (void)lift_and(8, lift_load(&env, esi, 0x8u, 1), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_4ed113;
    edi = lift_load(&env, ebp, 0x8u, 4);
    esi = edx;
    esi = esi + edi;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    edx = edx + 1u;
    lift_store(&env, esi, 0x0u, 1, 0x30u);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ed108;
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    {
        (void)lift_and(8, lift_load(&env, esi, 0x8u, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4ed113;
L_4ed108:
    ecx = lift_load(&env, ebp, 0x8u, 4);
    edi = edx;
    edi = edi + ecx;
    edx = edx + 1u;
    lift_store(&env, edi, 0x0u, 1, 0x2eu);
L_4ed113:
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, esi, 0x1cu, 4, edx);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = 0u - esi;
    {
        (void)lift_sub(32, esi, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ed12f;
    eax = edi;
    lift_store(&env, ebp, 0xffffffe8u, 4, edi);
    eax = 0u - eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
L_4ed12f:
    edi = lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, edi, 0x18u, 4, esi);
    ecx = esi;
    lift_store(&env, edi, 0x20u, 4, esi);
    ecx = 0u - ecx;
    lift_store(&env, edi, 0x20u, 4, ecx);
    edi = lift_load(&env, ebp, 0xfffffff4u, 4);
    edi = edi + esi;
    lift_store(&env, ebp, 0xfffffff4u, 4, edi);
    {
        (void)lift_sub(32, ebx, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ed150;
    ebx = edi;
L_4ed150:
    edi = lift_load(&env, ebp, 0x8u, 4);
    esi = lift_load(&env, ebp, 0xffffffecu, 4);
    ecx = ebx;
    edi = edi + edx;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, esi, 0x24u, 4, ebx);
    esi = lift_load(&env, ebp, 0xfffffff4u, 4);
    edx = edx + ebx;
    esi = esi - ebx;
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, ebx, 0x28u, 4, esi);
    goto L_4ed295;
L_4ed188:
    {
        (void)lift_sub(32, ebx, esi, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed1fc;
    esi = lift_load(&env, ebp, 0xffffffecu, 4);
    edi = lift_load(&env, ebp, 0x8u, 4);
    ecx = ebx;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, esi, 0x1cu, 4, ebx);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = edx + ebx;
    esi = esi - ebx;
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, ebx, 0x20u, 4, esi);
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = (ecx & 0xffffff00u) | ((lift_load(&env, esi, 0x8u, 1)) & 0xffu);
    lift_store(&env, esi, 0x18u, 4, ebx);
    {
        (void)lift_and(8, (ecx & 0xffu), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_4ed1ee;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xfffffff4u, 4), 0x0u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ed1d9;
    {
        (void)lift_and(8, (ecx & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4ed1ee;
L_4ed1d9:
    ecx = lift_load(&env, ebp, 0x8u, 4);
    ebx = edx;
    ebx = ebx + ecx;
    lift_store(&env, ebx, 0x0u, 1, 0x2eu);
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = edx + 1u;
    lift_store(&env, ebx, 0x24u, 4, 0x1u);
L_4ed1ee:
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, esi, 0x28u, 4, ebx);
    goto L_4ed295;
L_4ed1fc:
    edi = lift_load(&env, ebp, 0x8u, 4);
    ecx = esi;
    esi = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    edi = lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = lift_load(&env, ebp, 0xffffffe8u, 4);
    ecx = (ecx & 0xffff00ffu) | (((lift_load(&env, edi, 0x8u, 1)) & 0xffu) << 8);
    edx = edx + esi;
    ebx = ebx - esi;
    lift_store(&env, edi, 0x18u, 4, esi);
    {
        (void)lift_and(8, ((ecx >> 8) & 0xffu), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_4ed247;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xfffffff4u, 4), 0x0u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ed23a;
    {
        (void)lift_and(8, ((ecx >> 8) & 0xffu), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4ed256;
L_4ed23a:
    eax = lift_load(&env, ebp, 0x8u, 4);
    edi = edx;
    edi = edi + eax;
    edx = edx + 1u;
    lift_store(&env, edi, 0x0u, 1, 0x2eu);
    goto L_4ed256;
L_4ed247:
    esi = lift_load(&env, ebp, 0x8u, 4);
    {
        (void)lift_sub(8, lift_load(&env, esi, 0x0u, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4ed256;
    lift_store(&env, edi, 0x18u, 4, 0x0u);
L_4ed256:
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    {
        (void)lift_sub(32, ebx, ecx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ed25f;
    ebx = ecx;
L_4ed25f:
    esi = lift_load(&env, ebp, 0xffffffecu, 4);
    esi = esi + lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = lift_load(&env, ebp, 0x8u, 4);
    ecx = ebx;
    edi = edi + edx;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    esi = lift_load(&env, ebp, 0xfffffff0u, 4);
    edx = edx + ebx;
    lift_store(&env, esi, 0x1cu, 4, edx);
    esi = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = esi - ebx;
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    lift_store(&env, ebx, 0x20u, 4, esi);
L_4ed295:
    {
        uint32_t r = lift_add(32, edx, lift_load(&env, ebp, 0x8u, 4), &fl);
        edx = r;
    }
    lift_store(&env, edx, 0x0u, 1, 0x0u);
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

uint32_t lifted_f4ed2b5(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ED2B5_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ED2B5_STACK, 0, entry);
    goto L_4ed2b5;
L_4ed29b:
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
L_4ed2b5:
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
    esp = esp - 0xcu;
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
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, eax, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ed2d5;
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) + edx);
    goto L_4ed2e3;
L_4ed2d5:
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = ebx - edx;
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    ecx = (ebx + 0x1u);
    lift_store(&env, ebp, 0xffffffecu, 4, ecx);
L_4ed2e3:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = edi ^ edi;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, eax, 0x8u, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 4, edi);
    {
        (void)lift_and(8, (edx & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4ed30e;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, ebp, 0xffffffecu, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed2fe;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_4ed2fe:
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    ebx = ebx - 1u;
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed30e;
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffecu, 4, esi);
L_4ed30e:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edi = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ed32e;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    ebx = lift_load(&env, ebp, 0x8u, 4);
    edx = (eax + 0x1u);
    eax = eax + ebx;
    lift_store(&env, ebp, 0xfffffff4u, 4, edx);
    lift_store(&env, eax, 0x0u, 1, 0x30u);
    goto L_4ed3aa;
L_4ed32e:
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, edi);
    {
        (void)lift_sub(32, edi, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ed33b;
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
L_4ed33b:
    edi = lift_load(&env, ebp, 0x8u, 4);
    ebx = lift_load(&env, ebp, 0xfffffff4u, 4);
    ecx = lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    edi = edi + ebx;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    ecx = (ebx + eax);
    esi = esi + eax;
    edi = edi - eax;
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffe4u, 4, esi);
    ebx = lift_load(&env, edx, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed3aa;
    ecx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = ebx;
    esi = lift_load(&env, ebp, 0xfffffff4u, 4);
    eax = eax - ecx;
    edx = 0x30u;
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    eax = lift_load(&env, ebp, 0x8u, 4);
    ebx = lift_load(&env, ebp, 0xfffffff0u, 4);
    eax = eax + esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    edi = (esi + eax);
    lift_store(&env, ebp, 0xfffffff4u, 4, edi);
L_4ed3aa:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, edx, 0x18u, 4, eax);
    {
        (void)lift_and(8, lift_load(&env, edx, 0x8u, 1), 0x8u, &fl);
    }
    if (!fl.zf)
        goto L_4ed3d9;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffecu, 4), 0x0u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ed3c8;
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_and(8, lift_load(&env, eax, 0x8u, 1), 0x10u, &fl);
    }
    if (fl.zf)
        goto L_4ed3d9;
L_4ed3c8:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    edi = lift_load(&env, ebp, 0x8u, 4);
    esi = (eax + 0x1u);
    eax = eax + edi;
    lift_store(&env, ebp, 0xfffffff4u, 4, esi);
    lift_store(&env, eax, 0x0u, 1, 0x2eu);
L_4ed3d9:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed408;
    eax = lift_load(&env, ebp, 0x8u, 4);
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    ebx = edx;
    lift_store(&env, ebp, 0xfffffff0u, 4, edx);
    edx = 0x30u;
    ebx = 0u - ebx;
    eax = eax + ecx;
    lift_store(&env, ebp, 0xfffffff0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4eb5c0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xfffffff0u, 4);
    esi = (ecx + eax);
    lift_store(&env, ebp, 0xfffffff4u, 4, esi);
L_4ed408:
    edi = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ed458;
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffe0u, 4), &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed417;
    lift_store(&env, ebp, 0xffffffe0u, 4, edi);
L_4ed417:
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_4ed444;
    edi = lift_load(&env, ebp, 0x8u, 4);
    ecx = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = lift_load(&env, ebp, 0xffffffe4u, 4);
    edi = edi + ecx;
    ecx = ebx;
    {
        uint32_t v = 0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = 0u;
    (void)(eax);
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        (void)(v);
    }
    lift_store(&env, ebp, 0xfffffff4u, 4, lift_load(&env, ebp, 0xfffffff4u, 4) + ebx);
L_4ed444:
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    edi = lift_load(&env, ebp, 0xffffffe0u, 4);
    lift_store(&env, edx, 0x1cu, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax - edi;
    lift_store(&env, edx, 0x20u, 4, eax);
L_4ed458:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        (void)lift_sub(32, lift_load(&env, eax, 0xcu, 4), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ed477;
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    ecx = lift_load(&env, ebp, 0x8u, 4);
    ebx = (eax + 0x1u);
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = eax + ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, edx, 0xcu, 1)) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
L_4ed477:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + 1u;
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed491;
    edx = lift_load(&env, ebp, 0xfffffff4u, 4);
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, edx, eax + 0x0u, 1, 0x2bu);
    goto L_4ed4a5;
L_4ed491:
    edx = lift_load(&env, ebp, 0xfffffff4u, 4);
    edi = esi;
    lift_store(&env, ebp, 0xfffffff4u, 4, eax);
    edi = 0u - edi;
    eax = lift_load(&env, ebp, 0x8u, 4);
    lift_store(&env, ebp, 0xffffffdcu, 4, edi);
    lift_store(&env, edx, eax + 0x0u, 1, 0x2du);
L_4ed4a5:
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = lift_load(&env, ebx, 0x10u, 4);
    {
        (void)lift_sub(32, ebx, 0x3u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ed4ee;
    eax = ebx;
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4ed4ba;
            case 1:
                goto L_4ed4ca;
            case 2:
                goto L_4ed4d5;
            case 3:
                goto L_4ed4e0;
            default:
                return 0u;
        }
    }
L_4ed4ba:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0x3e8u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed4e9;
    ebx = 0x3u;
    goto L_4ed4ee;
L_4ed4ca:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0xau, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed4d5;
    ebx = 0x2u;
L_4ed4d5:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0x64u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed4e0;
    ebx = 0x3u;
L_4ed4e0:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffdcu, 4), 0x3e8u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed4ee;
L_4ed4e9:
    ebx = 0x4u;
L_4ed4ee:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x10u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x4u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed544;
    edi = edi ^ edi;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, edi);
    {
        (void)lift_sub(32, eax, 0x3e8u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed52e;
    edx = eax;
    edi = 0x3e8u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x5u, &fl);
        eax = r;
    }
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    edx = edx - eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
L_4ed52e:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = lift_load(&env, ebp, 0x8u, 4);
    ecx = (eax + 0x1u);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) + 0x30u) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
L_4ed544:
    {
        (void)lift_sub(32, ebx, 0x3u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed592;
    edi = edi ^ edi;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, edi);
    {
        (void)lift_sub(32, eax, 0x64u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed57c;
    edx = eax;
    edi = 0x64u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, edi, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x3u, &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    edx = edx - eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
L_4ed57c:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    esi = lift_load(&env, ebp, 0x8u, 4);
    ecx = (eax + 0x1u);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    eax = eax + esi;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) + 0x30u) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 4, ecx);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
L_4ed592:
    {
        (void)lift_sub(32, ebx, 0x2u, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed5da;
    edi = edi ^ edi;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, ebp, 0xfffffff0u, 4, edi);
    {
        (void)lift_sub(32, eax, 0xau, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed5c4;
    edx = eax;
    ebx = 0xau;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    lift_store(&env, ebp, 0xfffffff0u, 4, eax);
    edx = eax;
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    eax = eax + edx;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = eax + eax;
    edx = edx - eax;
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
L_4ed5c4:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    ecx = lift_load(&env, ebp, 0x8u, 4);
    ebx = (eax + 0x1u);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    eax = eax + ecx;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) + 0x30u) & 0xffu);
    lift_store(&env, ebp, 0xfffffff4u, 4, ebx);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
L_4ed5da:
    eax = lift_load(&env, ebp, 0xfffffff4u, 4);
    edi = lift_load(&env, ebp, 0x8u, 4);
    esi = (eax + 0x1u);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffdcu, 1)) & 0xffu);
    eax = eax + edi;
    edx = (edx & 0xffffff00u) | (((edx & 0xffu) + 0x30u) & 0xffu);
    lift_store(&env, eax, 0x0u, 1, (edx & 0xffu));
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = esi;
    eax = lift_load(&env, eax, 0x1cu, 4);
    {
        uint32_t r = lift_sub(32, edx, eax, &fl);
        edx = r;
    }
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    lift_store(&env, eax, 0x24u, 4, edx);
    eax = (edi + esi);
    lift_store(&env, ebp, 0xfffffff4u, 4, esi);
    lift_store(&env, eax, 0x0u, 1, 0x0u);
    goto L_4ed29b;
}
