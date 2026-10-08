/* Lifted from the original routine at 0x466d60 by tools/lift.py: every instruction of the original
 * is translated in order (registers, stack, flags and gotos) and every unrecovered callee goes
 * through the call boundary with the registers and stack arguments the original holds there.
 * Verified against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_select_screen.h"

uint32_t lifted_select_screen(const VertrixCalls *calls, const VertrixFactoryServices *services,
                              const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_SELECT_SCREEN_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_SELECT_SCREEN_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x38u, &fl);
        esp = r;
    }
    eax = (ebp + 0xffffffb4u);
    edx = 0x4ec1ecu;
    ecx = 0x515be8u;
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
    edi = lift_load(&env, 0u, 0x532a7cu, 4);
    lift_store(&env, ebp, 0xffffffb8u, 4, edx);
    lift_store(&env, ebp, 0xffffffbcu, 4, ecx);
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    lift_store(&env, 0u, 0x532a9cu, 4, ebx);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_468bd1;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a80u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_468bd1;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b6cu, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b6eu, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b70u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b74u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b76u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b78u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe4u, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b72u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_468b8c;
L_466e10:
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
L_466e12:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, edx);
L_466e17:
    ecx = lift_load(&env, 0u, 0x532a84u, 4);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_466f7f;
    eax = 0x180u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_466e44;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_466e44:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x447af0u;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86a4u, 2)) & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    edx = 0x50e528u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x540017u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x52u, 1, 0x9u);
    lift_store(&env, esi, 0x44u, 1, 0x9u);
    lift_store(&env, esi, 0x4eu, 1, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x4u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54671cu;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x180u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_466eed;
    edx = 0x3u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_466eed:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x447af0u;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86a4u, 2)) & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ebx = lift_load(&env, 0u, 0x540017u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    eax = lift_load(&env, eax, 0x4u, 4);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    edx = 0x50e529u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x52u, 1, 0x9u);
    lift_store(&env, esi, 0x44u, 1, 0x9u);
    lift_store(&env, esi, 0x4eu, 1, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x4u, 4, 0x2u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54671cu;
    edx = esi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
L_466f7f:
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_466fa2;
    esi = 0x5u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
L_466fa2:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f85f8u, 4);
    ecx = lift_load(&env, 0u, 0x4f85e8u, 4);
    edx = lift_load(&env, 0u, 0x4f85fcu, 4);
    ebx = lift_load(&env, 0u, 0x4f85ecu, 4);
    {
        uint32_t v = 0x448d30u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, edx, ebx, &fl);
        edx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x8u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x44u, 1, 0x10u);
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    eax = esi;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x48u, 2, 0xff9cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85ecu, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85fcu, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85e8u, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f8u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    {
        uint32_t r = lift_add(32, ecx, edx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, ebx, eax, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0xa8u, 2, (eax & 0xffffu));
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85ecu, 2)) & 0xffffu);
    lift_store(&env, esi, 0xaau, 2, (ebx & 0xffffu));
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, esi, 0xacu, 2, (edx & 0xffffu));
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    lift_store(&env, esi, 0xaeu, 2, (ecx & 0xffffu));
    ecx = lift_load(&env, 0u, 0x4f85fcu, 4);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = edx;
    ecx = lift_load(&env, 0u, 0x4f85f8u, 4);
    edx = eax;
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x148u, 2, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4670b5;
    ebx = 0x7u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_4670b5:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f85f8u, 4);
    edx = lift_load(&env, 0u, 0x4f85e8u, 4);
    ecx = lift_load(&env, 0u, 0x4f85ecu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t v = 0x448c20u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = lift_load(&env, 0u, 0x4f85fcu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, edx, ecx, &fl);
        edx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x0u, 4, 0x13u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x44u, 1, 0x10u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85ecu, 2)) & 0xffffu);
    lift_store(&env, esi, 0x150u, 4, 0x1u);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85fcu, 2)) & 0xffffu);
    lift_store(&env, esi, 0x138u, 4, 0x0u);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f8u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85ecu, 2)) & 0xffffu);
    lift_store(&env, esi, 0x148u, 2, 0x0u);
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    lift_store(&env, esi, 0xacu, 2, (ebx & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85e8u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0xa8u, 2, (eax & 0xffffu));
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    eax = 0x54671cu;
    lift_store(&env, esi, 0xaau, 2, (edx & 0xffffu));
    edx = esi;
    lift_store(&env, esi, 0xaeu, 2, (ecx & 0xffffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4671b1;
    ebx = 0x9u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_4671b1:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f85f8u, 4);
    edx = lift_load(&env, 0u, 0x4f85e8u, 4);
    ecx = lift_load(&env, 0u, 0x4f85ecu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t v = 0x449090u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = lift_load(&env, 0u, 0x4f85fcu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, edx, ecx, &fl);
        edx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    lift_store(&env, esi, 0x95u, 1, 0x0u);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85ecu, 2)) & 0xffffu);
    lift_store(&env, esi, 0x4eu, 1, 0x46u);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85fcu, 2)) & 0xffffu);
    lift_store(&env, esi, 0x138u, 4, 0x0u);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f8u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85e8u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x148u, 2, 0x0u);
    {
        uint32_t r = lift_add(32, edx, ebx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0xa8u, 2, (eax & 0xffffu));
    eax = 0x54671cu;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85e8u, 2)) & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, ebx, ecx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0xaeu, 2, (edx & 0xffffu));
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85ecu, 2)) & 0xffffu);
    lift_store(&env, esi, 0xaau, 2, (ebx & 0xffffu));
    edx = esi;
    lift_store(&env, esi, 0xacu, 2, (ecx & 0xffffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4672b3;
    ebx = 0xbu;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_4672b3:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44a610u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x4f85eau, 4);
    edx = lift_load(&env, 0u, 0x4f85e6u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x64u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    edx = 0x544a18u;
    lift_store(&env, esi, 0x95u, 1, 0x5u);
    eax = esi;
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4fbf24u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x138u, 4, 0x0u);
    eax = lift_load(&env, 0u, 0x4f85e8u, 4);
    lift_store(&env, esi, 0x124u, 4, 0x0u);
    lift_store(&env, esi, 0x58u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f85ecu, 4);
    edx = esi;
    lift_store(&env, esi, 0x64u, 4, eax);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x148u, 2, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a7cu, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_468d80;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46738d;
    edi = 0xdu;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
L_46738d:
    esi = eax;
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
    eax = lift_load(&env, 0u, 0x4f8618u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f861cu, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x544a18u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4fbed0u, 4);
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x52u, 1, 0x0u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x94u, 1, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_467445;
    ecx = 0xfu;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
L_467445:
    esi = eax;
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
    eax = lift_load(&env, 0u, 0x4f8628u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f862cu, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x544a18u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4fbee0u, 4);
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x52u, 1, 0x0u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x94u, 1, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4674fd;
    esi = 0x11u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
L_4674fd:
    esi = eax;
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
    eax = lift_load(&env, 0u, 0x4f8620u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8624u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xau;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x544a18u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4fbed8u, 4);
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x52u, 1, 0x0u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x94u, 1, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, eax);
L_4675a3:
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4675c6;
    edx = 0x19u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_4675c6:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f85f8u, 4);
    ebx = lift_load(&env, 0u, 0x4f85f0u, 4);
    edx = lift_load(&env, 0u, 0x4f85fcu, 4);
    edi = lift_load(&env, 0u, 0x4f85f4u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x448ed0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, edx, edi, &fl);
        edx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x8u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x44u, 1, 0x10u);
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    eax = esi;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x48u, 2, 0xff9cu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f4u, 2)) & 0xffffu);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85fcu, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f0u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f8u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, ecx, edi, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, ebx, edx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0xa8u, 2, (eax & 0xffffu));
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f4u, 2)) & 0xffffu);
    lift_store(&env, esi, 0xaau, 2, (ebx & 0xffffu));
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, esi, 0xacu, 2, (edx & 0xffffu));
    lift_store(&env, esi, 0xaeu, 2, (ecx & 0xffffu));
    ecx = lift_load(&env, 0u, 0x4f85fcu, 4);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    ecx = lift_load(&env, 0u, 0x4f85f8u, 4);
    eax = esi;
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x148u, 2, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4676de;
    ebx = 0x1bu;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_4676de:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f85f8u, 4);
    edi = lift_load(&env, 0u, 0x4f85f0u, 4);
    edx = lift_load(&env, 0u, 0x4f85fcu, 4);
    ecx = lift_load(&env, 0u, 0x4f85f4u, 4);
    {
        uint32_t v = 0x448ca0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, edx, ecx, &fl);
        edx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x0u, 4, 0x14u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x44u, 1, 0x10u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x150u, 4, 0x1u);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f4u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85fcu, 2)) & 0xffffu);
    lift_store(&env, esi, 0x138u, 4, 0x0u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f0u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f8u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x148u, 2, 0x1u);
    {
        uint32_t r = lift_add(32, edx, ebx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f0u, 2)) & 0xffffu);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, esi, 0xa8u, 2, (ecx & 0xffffu));
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    lift_store(&env, esi, 0xaau, 2, (eax & 0xffffu));
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f4u, 2)) & 0xffffu);
    lift_store(&env, esi, 0xaeu, 2, (edx & 0xffffu));
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0xacu, 2, (ebx & 0xffffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4677e2;
    ebx = 0x1du;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_4677e2:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f85f8u, 4);
    edi = lift_load(&env, 0u, 0x4f85f0u, 4);
    edx = lift_load(&env, 0u, 0x4f85fcu, 4);
    ecx = lift_load(&env, 0u, 0x4f85f4u, 4);
    {
        uint32_t v = 0x449180u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, edx, ecx, &fl);
        edx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f4u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x95u, 1, 0x0u);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85fcu, 2)) & 0xffffu);
    lift_store(&env, esi, 0x4eu, 1, 0x46u);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f0u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x138u, 4, 0x0u);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f8u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f0u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x148u, 2, 0x1u);
    {
        uint32_t r = lift_add(32, ebx, edi, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, ecx, edx, &fl);
        ecx = r;
    }
    lift_store(&env, esi, 0xa8u, 2, (eax & 0xffffu));
    eax = 0x54671cu;
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f4u, 2)) & 0xffffu);
    lift_store(&env, esi, 0xaau, 2, (ecx & 0xffffu));
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    lift_store(&env, esi, 0xacu, 2, (edx & 0xffffu));
    edx = esi;
    lift_store(&env, esi, 0xaeu, 2, (ebx & 0xffffu));
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4678e4;
    ebx = 0x1fu;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_4678e4:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44a610u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x4f85f2u, 4);
    edx = lift_load(&env, 0u, 0x4f85eeu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x64u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    edx = 0x544a18u;
    lift_store(&env, esi, 0x95u, 1, 0x5u);
    eax = esi;
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4fbf24u, 4);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x138u, 4, 0x0u);
    eax = lift_load(&env, 0u, 0x4f85f0u, 4);
    lift_store(&env, esi, 0x124u, 4, 0x0u);
    lift_store(&env, esi, 0x58u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f85f4u, 4);
    edx = esi;
    lift_store(&env, esi, 0x64u, 4, eax);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x148u, 2, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a8cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_468f7b;
L_46799b:
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4679be;
    esi = 0x21u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
L_4679be:
    esi = eax;
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
    eax = lift_load(&env, 0u, 0x4f8630u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8634u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x544a18u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4fbee8u, 4);
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x52u, 1, 0x0u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x94u, 1, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_467a76;
    edx = 0x23u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_467a76:
    esi = eax;
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
    eax = lift_load(&env, 0u, 0x4f8640u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8644u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x544a18u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4fbef8u, 4);
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x52u, 1, 0x0u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x94u, 1, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_467b2e;
    ebx = 0x25u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_467b2e:
    esi = eax;
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
    eax = lift_load(&env, 0u, 0x4f8638u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f863cu, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xau;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x544a18u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4fbef0u, 4);
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x52u, 1, 0x0u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x94u, 1, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
L_467bd4:
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_467bf7;
    edx = 0x2du;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_467bf7:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x4492f0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f8608u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f860cu, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f860cu, 2)) & 0xffffu);
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8614u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8608u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x48u, 2, 0x0u);
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8610u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x4au, 2, 0x0u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8608u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x4cu, 2, 0x1u);
    {
        uint32_t r = lift_add(32, ecx, ebx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, edx, edi, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0xa8u, 2, (eax & 0xffffu));
    {
        uint32_t a = edx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        edx = r;
    }
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f860cu, 2)) & 0xffffu);
    lift_store(&env, esi, 0xaau, 2, (edx & 0xffffu));
    {
        uint32_t a = ecx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, esi, 0xacu, 2, (ebx & 0xffffu));
    eax = esi;
    lift_store(&env, esi, 0xaeu, 2, (ecx & 0xffffu));
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    edx = esi;
    lift_store(&env, esi, 0x7cu, 4, 0xffffffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a8cu, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_46918c;
L_467cdc:
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_467cff;
    esi = 0x2fu;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
L_467cff:
    esi = eax;
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
    eax = lift_load(&env, 0u, 0x4f8648u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f864cu, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x544a18u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4fbf00u, 4);
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x52u, 1, 0x0u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x94u, 1, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_467db7;
    edx = 0x31u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_467db7:
    esi = eax;
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
    eax = lift_load(&env, 0u, 0x4f8658u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f865cu, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x544a18u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4fbf10u, 4);
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x52u, 1, 0x0u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x94u, 1, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_467e6f;
    ebx = 0x33u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_467e6f:
    esi = eax;
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
    eax = lift_load(&env, 0u, 0x4f8650u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8654u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xau;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x544a18u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, 0u, 0x4fbf08u, 4);
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x52u, 1, 0x0u);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x94u, 1, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
L_467f15:
    eax = 0x180u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_467f38;
    edx = 0x3bu;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_467f38:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44a6d0u;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f860cu, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8614u, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f860au, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8610u, 2)) & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8608u, 2)) & 0xffffu);
    ecx = lift_load(&env, 0u, 0x4f8606u, 4);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    edx = 0x50e52au;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ebx = lift_load(&env, 0u, 0x540015u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f860cu, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8614u, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8610u, 2)) & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8608u, 2)) & 0xffffu);
    ecx = lift_load(&env, 0u, 0x4f860au, 4);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    edx = lift_load(&env, 0u, 0x4f8606u, 4);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6690u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = 0x8u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xffffffb0u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6540u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    edx = 0xffffffb0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6550u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, esi, 0x44u, 1, 0x0u);
    edi = esi;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = lift_load(&env, 0u, 0x4f7bb0u, 4);
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    ebx = lift_load(&env, 0u, 0x532a80u, 4);
    lift_store(&env, esi, 0x14cu, 4, eax);
    eax = 0x1u;
    lift_store(&env, esi, 0x172u, 2, 0x1u);
    {
        (void)lift_sub(32, ebx, eax, &fl);
    }
    if (!fl.zf)
        goto L_469372;
L_468048:
    lift_store(&env, edi, 0x52u, 1, 0x1u);
    lift_store(&env, edi, 0x94u, 1, 0x0u);
    lift_store(&env, edi, 0x95u, 1, 0x0u);
L_46805a:
    eax = edi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54671cu;
    edx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x16cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_468092;
    edi = 0x3du;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x429670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
L_468092:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44a570u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x4f8662u, 4);
    edx = lift_load(&env, 0u, 0x4f865eu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = lift_load(&env, 0u, 0x4f8668u, 4);
    edx = lift_load(&env, 0u, 0x4f866cu, 4);
    ecx = lift_load(&env, 0u, 0x4f867cu, 4);
    ebx = lift_load(&env, 0u, 0x4f8662u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x164u, 4, eax);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x168u, 4, edx);
    ecx = lift_load(&env, 0u, 0x4f8678u, 4);
    edx = lift_load(&env, 0u, 0x4f865eu, 4);
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x16cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_468132;
    ebx = 0x3fu;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x429670u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_468132:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44a5c0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x4f8672u, 4);
    edx = lift_load(&env, 0u, 0x4f866eu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = lift_load(&env, 0u, 0x4f8668u, 4);
    eax = lift_load(&env, 0u, 0x4f866cu, 4);
    edi = lift_load(&env, 0u, 0x4f867cu, 4);
    ecx = lift_load(&env, 0u, 0x4f8678u, 4);
    ebx = lift_load(&env, 0u, 0x4f8672u, 4);
    lift_store(&env, esi, 0x160u, 4, 0x0u);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x164u, 4, edx);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x168u, 4, eax);
    edx = lift_load(&env, 0u, 0x4f866eu, 4);
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x180u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4681dc;
    edx = 0x41u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_4681dc:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44aec0u;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = lift_load(&env, 0u, 0x4f867eu, 4);
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
    edx = 0x50e52du;
    ecx = lift_load(&env, 0u, 0x4f8696u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f869au, 4);
    ebx = lift_load(&env, 0u, 0x4f9bfdu, 4);
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
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x64u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f86e4u, 4);
    ecx = lift_load(&env, 0u, 0x4f86e0u, 4);
    lift_store(&env, esi, 0x44u, 1, 0x8u);
    ebx = lift_load(&env, 0u, 0x4f86dau, 4);
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    edx = lift_load(&env, 0u, 0x4f86d6u, 4);
    lift_store(&env, esi, 0x7cu, 4, 0x0u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
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
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x4eu, 1, 0x5au);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x180u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4682c2;
    ebx = 0x43u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_4682c2:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44b050u;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = lift_load(&env, 0u, 0x4f8682u, 4);
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
    edx = 0x50e52eu;
    ecx = lift_load(&env, 0u, 0x4f8696u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f869au, 4);
    ebx = lift_load(&env, 0u, 0x4f9bfdu, 4);
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
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f86e4u, 4);
    ecx = lift_load(&env, 0u, 0x4f86e0u, 4);
    edi = lift_load(&env, 0u, 0x4f86dcu, 4);
    edx = lift_load(&env, 0u, 0x4f86d6u, 4);
    lift_store(&env, esi, 0x44u, 1, 0x8u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x4eu, 1, 0x5au);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x180u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_468397;
    edx = 0x45u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_468397:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44b170u;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = lift_load(&env, 0u, 0x4f868eu, 4);
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
    edx = 0x50e52fu;
    ecx = lift_load(&env, 0u, 0x4f8696u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f869au, 4);
    ebx = lift_load(&env, 0u, 0x4f9bfdu, 4);
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
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x44cu;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac860u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f86f4u, 4);
    ecx = lift_load(&env, 0u, 0x4f86f0u, 4);
    lift_store(&env, esi, 0x44u, 1, 0x8u);
    ebx = lift_load(&env, 0u, 0x4f86eau, 4);
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    edx = lift_load(&env, 0u, 0x4f86e6u, 4);
    lift_store(&env, esi, 0x7cu, 4, 0x0u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
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
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x4eu, 1, 0x5au);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x180u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46847d;
    ebx = 0x47u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_46847d:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44b340u;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = lift_load(&env, 0u, 0x4f8692u, 4);
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
    edx = 0x50e530u;
    ecx = lift_load(&env, 0u, 0x4f8696u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f869au, 4);
    ebx = lift_load(&env, 0u, 0x4f9bfdu, 4);
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
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f86f4u, 4);
    ecx = lift_load(&env, 0u, 0x4f86f0u, 4);
    edi = lift_load(&env, 0u, 0x4f86ecu, 4);
    edx = lift_load(&env, 0u, 0x4f86e6u, 4);
    lift_store(&env, esi, 0x44u, 1, 0x8u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x4eu, 1, 0x5au);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x180u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_468552;
    edx = 0x49u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_468552:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44b4a0u;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = lift_load(&env, 0u, 0x4f8686u, 4);
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
    edx = 0x50e531u;
    ecx = lift_load(&env, 0u, 0x4f8696u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f869au, 4);
    ebx = lift_load(&env, 0u, 0x4f9bfdu, 4);
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
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f8704u, 4);
    ecx = lift_load(&env, 0u, 0x4f8700u, 4);
    ebx = lift_load(&env, 0u, 0x4f86fau, 4);
    lift_store(&env, esi, 0x44u, 1, 0x8u);
    edx = lift_load(&env, 0u, 0x4f86f6u, 4);
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
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
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x4eu, 1, 0x5au);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x180u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_468625;
    ebx = 0x4bu;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_468625:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44b5d0u;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = lift_load(&env, 0u, 0x4f868au, 4);
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
    edx = 0x50e532u;
    ecx = lift_load(&env, 0u, 0x4f8696u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f869au, 4);
    ebx = lift_load(&env, 0u, 0x4f9bfdu, 4);
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
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f8704u, 4);
    ecx = lift_load(&env, 0u, 0x4f8700u, 4);
    edi = lift_load(&env, 0u, 0x4f86fcu, 4);
    edx = lift_load(&env, 0u, 0x4f86f6u, 4);
    lift_store(&env, esi, 0x44u, 1, 0x8u);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x4eu, 1, 0x5au);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x180u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4686fa;
    edx = 0x4du;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_4686fa:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44b6f0u;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85a4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f85a8u, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f85a2u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f8u, 2)) & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85e8u, 2)) & 0xffffu);
    edx = 0x50e533u;
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x540016u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ecx = lift_load(&env, 0u, 0x4f85e6u, 4);
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
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, 0u, 0x4f85a8u, 4);
    ecx = lift_load(&env, 0u, 0x4f85f8u, 4);
    edx = lift_load(&env, 0u, 0x4f85e6u, 4);
    eax = esi;
    lift_store(&env, esi, 0x44u, 1, 0x8u);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x4f85a2u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x4eu, 1, 0x5au);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x180u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4687e0;
    esi = 0x4fu;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
L_4687e0:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44b810u;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85a4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f85a8u, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f85a2u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f8u, 2)) & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f0u, 2)) & 0xffffu);
    ecx = lift_load(&env, 0u, 0x4f85eeu, 4);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x540016u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = 0x50e534u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f85a8u, 4);
    ecx = lift_load(&env, 0u, 0x4f85f8u, 4);
    ebx = lift_load(&env, 0u, 0x4f85a2u, 4);
    edx = lift_load(&env, 0u, 0x4f85eeu, 4);
    lift_store(&env, esi, 0x44u, 1, 0x8u);
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
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x4eu, 1, 0x5au);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x180u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4688c5;
    edx = 0x51u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_4688c5:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44b980u;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85a4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f85a8u, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f85a2u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8610u, 2)) & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8608u, 2)) & 0xffffu);
    edx = 0x50e535u;
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x540016u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ecx = lift_load(&env, 0u, 0x4f8606u, 4);
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
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 12u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, 0u, 0x4f85a8u, 4);
    ecx = lift_load(&env, 0u, 0x4f8610u, 4);
    edx = lift_load(&env, 0u, 0x4f8606u, 4);
    eax = esi;
    lift_store(&env, esi, 0x44u, 1, 0x8u);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x4f85a2u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x4eu, 1, 0x5au);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esi = lift_load(&env, 0u, 0x532a8cu, 4);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (!fl.zf)
        goto L_4693d2;
L_468996:
    eax = 0x160u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4689b9;
    edx = 0x53u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_4689b9:
    esi = eax;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x4f86c6u, 4);
    edx = lift_load(&env, 0u, 0x4f86c2u, 4);
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
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
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, 0xfu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x0u);
    edx = 0xff000000u;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x44bac0u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f86d0u, 4);
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86c8u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(32, eax, 0x2u, &fl);
        eax = r;
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86c4u, 2)) & 0xffffu);
    ecx = lift_load(&env, 0u, 0x4f86ccu, 4);
    {
        uint32_t r = lift_sub(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, ecx, 0x4u, &fl);
        ecx = r;
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x7cu, 4, 0xffffffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x160u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_468aa1;
    ebx = 0x55u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_468aa1:
    esi = eax;
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
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x4f86b6u, 4);
    edx = lift_load(&env, 0u, 0x4f86b2u, 4);
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
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
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, 0xfu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x0u);
    edx = 0xff000000u;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x44bb30u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, 0u, 0x4f86c0u, 4);
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86b8u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86b4u, 2)) & 0xffffu);
    ecx = lift_load(&env, 0u, 0x4f86bcu, 4);
    {
        uint32_t r = lift_sub(32, eax, 0x2u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, ecx, 0x4u, &fl);
        ecx = r;
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x7cu, 4, 0xffffffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
L_468b6b:
    eax = lift_load(&env, 0u, 0x532a84u, 4);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4693e0;
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
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
L_468b8c:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffd4u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_466e10;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe0u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_466e10;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | (((edi & 0xffffu)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_466e10;
    edi = 0x1u;
    goto L_466e12;
L_468bd1:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a7cu, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_468c8f;
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a80u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_468c8f;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b74u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b76u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b78u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b6cu, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b6eu, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b70u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffd8u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b72u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_468c52;
L_468c46:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    goto L_466e17;
L_468c52:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffd0u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_468c46;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe8u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_468c46;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_468c46;
    lift_store(&env, ebp, 0xffffffdcu, 4, 0x1u);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    goto L_466e17;
L_468c8f:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b6cu, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b6eu, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b70u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b74u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffd8u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b76u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b78u, 2)) & 0xffffu);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b72u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe4u, 2)) & 0xffffu);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b7au, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_468d0f;
L_468cf3:
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
L_468cf5:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffd8u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_468d45;
L_468d05:
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, esi);
    goto L_466e17;
L_468d0f:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffd4u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_468cf3;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe0u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_468cf3;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | (((edi & 0xffffu)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_468cf3;
    edi = 0x1u;
    goto L_468cf5;
L_468d45:
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffd0u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_468d05;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffe8u, 2)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_468d05;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    eax = (eax & 0xffff0000u) | (((edx & 0xffffu)) & 0xffffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476650u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_468d05;
    lift_store(&env, ebp, 0xffffffdcu, 4, 0x1u);
    goto L_466e17;
L_468d80:
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_468da3;
    edx = 0x13u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_468da3:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x449500u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f8618u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f861cu, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x64u, 4, eax);
    eax = esi;
    lift_store(&env, esi, 0x70u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_468e3c;
    ebx = 0x15u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_468e3c:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x449660u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f8628u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f862cu, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x64u, 4, eax);
    eax = esi;
    lift_store(&env, esi, 0x70u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_468ed5;
    edx = 0x17u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_468ed5:
    edx = lift_load(&env, 0u, 0x4f8624u, 4);
    ebx = lift_load(&env, 0u, 0x532b40u, 4);
    esi = eax;
    eax = lift_load(&env, 0u, 0x4f8620u, 4);
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_468f71;
    ecx = 0x449870u;
L_468ef6:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xau;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x64u, 4, eax);
    eax = esi;
    lift_store(&env, esi, 0x70u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
    goto L_4675a3;
L_468f71:
    ecx = 0x4497c0u;
    goto L_468ef6;
L_468f7b:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a80u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_46799b;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_468fab;
    edx = 0x27u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
L_468fab:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x449aa0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f8630u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8634u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x70u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x64u, 4, eax);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_469047;
    ebx = 0x29u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
L_469047:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x449c00u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f8640u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8644u, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x70u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x64u, 4, eax);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4690e3;
    edi = 0x2bu;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
L_4690e3:
    edx = lift_load(&env, 0u, 0x4f863cu, 4);
    ecx = lift_load(&env, 0u, 0x532b40u, 4);
    esi = eax;
    eax = lift_load(&env, 0u, 0x4f8638u, 4);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_469182;
    ecx = 0x449e10u;
L_469104:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xau;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    lift_store(&env, esi, 0x70u, 4, eax);
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x64u, 4, eax);
    eax = esi;
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    goto L_467bd4;
L_469182:
    ecx = 0x449d60u;
    goto L_469104;
L_46918c:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a7cu, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_467cdc;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4691bc;
    edi = 0x35u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edx);
L_4691bc:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44a040u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f8648u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f864cu, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46924c;
    ecx = 0x37u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
L_46924c:
    esi = eax;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x44a170u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x4f8658u, 4);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f865cu, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4692dc;
    esi = 0x39u;
    lift_store(&env, ebp, 0xffffffccu, 4, eax);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffc0u, 4, esi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, edi);
L_4692dc:
    edx = lift_load(&env, 0u, 0x4f8654u, 4);
    ecx = lift_load(&env, 0u, 0x532b40u, 4);
    esi = eax;
    eax = lift_load(&env, 0u, 0x4f8650u, 4);
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_46936b;
    ecx = 0x44a340u;
L_4692f9:
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 20u;
    edx = 0x2u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0xau;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac470u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        uint32_t v = 0x0u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 4, ebx);
    goto L_467f15;
L_46936b:
    ecx = 0x44a2a0u;
    goto L_4692f9;
L_469372:
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, 0x532a7cu, 4), &fl);
    }
    if (!fl.zf)
        goto L_46938e;
    edx = lift_load(&env, 0u, 0x532a6cu, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, (edx * 4u) + 0x5344f0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_4693b3;
    goto L_468048;
L_46938e:
    edx = lift_load(&env, 0u, 0x532a68u, 4);
    {
        (void)lift_sub(32, eax, lift_load(&env, 0u, (edx * 4u) + 0x5344a4u, 4), &fl);
    }
    if (!fl.zf)
        goto L_46939f;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
L_46939f:
    edx = lift_load(&env, 0u, 0x532a6cu, 4);
    {
        (void)lift_sub(32, lift_load(&env, 0u, (edx * 4u) + 0x5344f0u, 4), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_468048;
L_4693b3:
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_468048;
    lift_store(&env, edi, 0x52u, 1, 0xdu);
    lift_store(&env, edi, 0x94u, 1, 0x0u);
    lift_store(&env, edi, 0x95u, 1, 0x1u);
    goto L_46805a;
L_4693d2:
    {
        (void)lift_sub(32, esi, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_468996;
    goto L_468b6b;
L_4693e0:
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
    eax = lift_load(&env, 0u, 0x540015u, 4);
    {
        uint32_t v = 0x8u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8738u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, 0xcu, &fl);
        eax = r;
    }
    ecx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8734u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8730u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(32, eax, 0x6u, &fl);
        eax = r;
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = lift_load(&env, 0u, 0x4f8734u, 4);
    esi = 0x280u;
    {
        uint32_t r = lift_add(32, eax, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, esi, eax, &fl);
        esi = r;
    }
    eax = esi;
    {
        uint32_t v = 0x416970u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t v = 0x50e536u;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4602a0u, eax, edx, ebx, ecx, 6, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 24u;
    esi = eax;
    eax = lift_load(&env, eax, 0x160u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, eax, 0x52u, 1, 0x0u);
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x445d80u;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54671cu;
    edx = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffb4u, 4);
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
