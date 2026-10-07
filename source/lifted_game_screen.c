/* Lifted from the original routine at 0x46c9d0 by tools/lift.py: every instruction of the original
 * is translated in order (registers, frame, flags and gotos) and every unrecovered callee goes
 * through the call boundary with the registers and stack arguments the original holds there.
 * Verified against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_game_screen.h"

uint32_t lifted_game_screen(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            const VertrixGlobals *globals, uint32_t frame, uint32_t eax,
                            uint32_t edx, uint32_t ebx, uint32_t ecx, const uint32_t *arguments,
                            const uint8_t *garbage, uint32_t chain)
{
    uint8_t local[LIFTED_GAME_SCREEN_LOCALS + 8 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0};
    uint32_t esi = 0;
    uint32_t edi = 0;
    lift_begin(&env, calls, services, globals, frame, local, LIFTED_GAME_SCREEN_LOCALS, 0, garbage,
               arguments, chain);
    lift_local_write(&env, -92, 4, eax);
    lift_local_write(&env, -88, 4, edx);
    lift_local_write(&env, -84, 4, ebx);
    eax = (frame + 0xffffff8cu);
    edx = 0x4ec1ecu;
    ecx = 0x516018u;
    env.stack[env.sp++] = env.chain;
    lift_store(&env, eax, 0x0u, 4, env.stack[--env.sp]);
    env.chain = eax;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = 0x4ecu;
    lift_local_write(&env, -112, 4, edx);
    lift_local_write(&env, -108, 4, ecx);
    lift_local_write(&env, -104, 4, ebx);
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_46e6ab;
    esi = ebx;
L_46ca1d:
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x0u, 4, 0x1u);
    eax = lift_call(&env, 0x43aab0u, eax, edx, ebx, ecx, 0);
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x450f60u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = lift_load(&env, 0u, 0x532a68u, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x488u, 4, eax);
    eax = esi;
    eax = lift_call(&env, 0x43bae0u, eax, edx, ebx, ecx, 0);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, esi, 0x470u, 4, 0x3u);
    lift_store(&env, 0u, (eax * 4u) + 0x540f88u, 4, esi);
    lift_store(&env, esi, 0x168u, 2, 0xcau);
    lift_store(&env, esi, 0x16au, 2, 0xcbu);
    edi = esi;
    lift_store(&env, esi, 0x16cu, 2, 0xc8u);
    eax = lift_load(&env, 0u, 0x532a7cu, 4);
    lift_store(&env, esi, 0x16eu, 2, 0xc9u);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_46e6c5;
    lift_store(&env, esi, 0x160u, 2, 0x0u);
    lift_store(&env, esi, 0x162u, 2, 0x0u);
    lift_store(&env, esi, 0x164u, 2, 0x0u);
    lift_store(&env, esi, 0x166u, 2, 0x0u);
L_46cace:
    eax = edi;
    eax = lift_call(&env, 0x43ab30u, eax, edx, ebx, ecx, 0);
    eax = lift_load(&env, 0u, 0x532aa4u, 4);
    edx = edi;
    lift_store(&env, edi, 0x174u, 4, eax);
    eax = 0x54671cu;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = lift_load(&env, edi, 0x15cu, 4);
    edx = lift_local_read(&env, -88, 4);
    lift_store(&env, eax, 0xce4u, 4, edx);
    eax = 0x4ecu;
    lift_local_write(&env, -76, 4, edi);
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46cb21;
    ebx = 0x3u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_local_write(&env, -104, 4, ebx);
    eax = lift_call(&env, 0x43a6f0u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, esi);
L_46cb21:
    esi = eax;
    edx = 0x1u;
    eax = esi;
    lift_store(&env, esi, 0x0u, 4, 0x2u);
    eax = lift_call(&env, 0x43aab0u, eax, edx, ebx, ecx, 0);
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x450f60u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = lift_load(&env, 0u, 0x532a6cu, 4);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x488u, 4, eax);
    eax = esi;
    eax = lift_call(&env, 0x43bae0u, eax, edx, ebx, ecx, 0);
    eax = lift_load(&env, esi, 0x0u, 4);
    lift_store(&env, esi, 0x470u, 4, 0x3u);
    lift_store(&env, 0u, (eax * 4u) + 0x540f88u, 4, esi);
    lift_store(&env, esi, 0x168u, 2, 0xceu);
    lift_store(&env, esi, 0x16au, 2, 0xcfu);
    edi = esi;
    lift_store(&env, esi, 0x16cu, 2, 0xccu);
    eax = lift_load(&env, 0u, 0x532a80u, 4);
    lift_store(&env, esi, 0x16eu, 2, 0xcdu);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_46e743;
    lift_store(&env, esi, 0x160u, 2, 0x0u);
    lift_store(&env, esi, 0x162u, 2, 0x0u);
    lift_store(&env, esi, 0x164u, 2, 0x0u);
    lift_store(&env, esi, 0x166u, 2, 0x0u);
L_46cbd7:
    eax = edi;
    eax = lift_call(&env, 0x43ab30u, eax, edx, ebx, ecx, 0);
    eax = lift_load(&env, 0u, 0x532aa8u, 4);
    edx = edi;
    lift_store(&env, edi, 0x174u, 4, eax);
    eax = 0x54671cu;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = lift_load(&env, edi, 0x15cu, 4);
    edx = lift_local_read(&env, -84, 4);
    lift_store(&env, eax, 0xce4u, 4, edx);
    eax = lift_local_read(&env, -76, 4);
    lift_store(&env, eax, 0x3b0u, 4, edi);
    lift_store(&env, edi, 0x3b0u, 4, eax);
    eax = 0x284u;
    lift_local_write(&env, -72, 4, edi);
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46cc39;
    ebx = 0x5u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_local_write(&env, -104, 4, ebx);
    eax = lift_call(&env, 0x429880u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, esi);
L_46cc39:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    ebx = lift_load(&env, 0u, 0x4f8ac2u, 4);
    env.stack[env.sp++] = 0x0u;
    edx = lift_load(&env, 0u, 0x4f8abeu, 4);
    eax = esi;
    env.stack[env.sp++] = 0x0u;
    lift_store(&env, esi, 0x0u, 4, 0x3u);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x4u, 4, 0x1u);
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = lift_load(&env, 0u, 0x4f8accu, 4);
    eax = lift_load(&env, 0u, 0x4f8ac8u, 4);
    ecx = lift_load(&env, 0u, 0x4f9060u, 4);
    edi = lift_load(&env, 0u, 0x4f9064u, 4);
    {
        uint32_t r = lift_sub(32, eax, ecx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, edx, edi, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x27cu, 4, eax);
    lift_store(&env, esi, 0x280u, 4, edx);
    edx = lift_load(&env, 0u, 0x532a65u, 4);
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x429bf0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    eax = lift_call(&env, 0x42a200u, eax, edx, ebx, ecx, 0);
    edx = esi;
    eax = 0x54671cu;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = lift_local_read(&env, -76, 4);
    lift_store(&env, eax, 0x3b8u, 4, esi);
    eax = 0x284u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46cce3;
    ebx = 0x7u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_local_write(&env, -104, 4, ebx);
    eax = lift_call(&env, 0x429880u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, esi);
L_46cce3:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    ebx = lift_load(&env, 0u, 0x4f8ad2u, 4);
    env.stack[env.sp++] = 0x0u;
    edx = lift_load(&env, 0u, 0x4f8aceu, 4);
    eax = esi;
    env.stack[env.sp++] = 0x0u;
    lift_store(&env, esi, 0x0u, 4, 0x4u);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x4u, 4, 0x2u);
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = lift_load(&env, 0u, 0x4f8adcu, 4);
    eax = lift_load(&env, 0u, 0x4f8ad8u, 4);
    ecx = lift_load(&env, 0u, 0x4f9060u, 4);
    edi = lift_load(&env, 0u, 0x4f9064u, 4);
    {
        uint32_t r = lift_sub(32, eax, ecx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_sub(32, edx, edi, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x27cu, 4, eax);
    lift_store(&env, esi, 0x280u, 4, edx);
    edx = lift_load(&env, 0u, 0x532a69u, 4);
    eax = esi;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x278u, 4, 0x0u);
    eax = lift_call(&env, 0x429bf0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    eax = lift_call(&env, 0x42a200u, eax, edx, ebx, ecx, 0);
    edx = esi;
    eax = 0x54671cu;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = lift_local_read(&env, -72, 4);
    lift_local_write(&env, -44, 4, edi);
    lift_store(&env, eax, 0x3b8u, 4, esi);
L_46cd79:
    eax = 0x194u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46cd8c;
    eax = lift_call(&env, 0x43d3f0u, eax, edx, ebx, ecx, 0);
L_46cd8c:
    esi = eax;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_46e7fa;
    lift_store(&env, eax, 0x0u, 4, 0xbu);
    lift_store(&env, eax, 0x4u, 4, 0x1u);
L_46cda3:
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a1cu, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8a14u, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a10u, 2)) & 0xffffu);
    env.stack[env.sp++] = eax;
    eax = lift_load(&env, 0u, 0x4f8a1au, 4);
    ecx = lift_load(&env, 0u, 0x4f8a16u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x184u, 4, 0x0u);
    env.stack[env.sp++] = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a18u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x188u, 4, 0x2u);
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
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ebx = lift_load(&env, edi, 0x54682du, 4);
    env.stack[env.sp++] = eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b5700u, eax, edx, ebx, ecx, 3);
    edx = lift_local_read(&env, -44, 4);
    eax = lift_local_read(&env, -92, 4);
    ebx = esi;
    edx = lift_load(&env, edx, 0x4fd608u, 4);
    eax = lift_call(&env, 0x4123d0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_46e806;
    eax = lift_load(&env, 0u, 0x4f8a14u, 4);
    ecx = lift_load(&env, 0u, 0x4f8a10u, 4);
    ebx = lift_load(&env, 0u, 0x4f8a1au, 4);
    edx = lift_load(&env, 0u, 0x4f8a16u, 4);
    env.stack[env.sp++] = eax;
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
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1);
L_46ce5e:
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x148u, 2, 0x2u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    edx = lift_local_read(&env, -44, 4);
    {
        uint32_t r = lift_add(32, edx, 0x4u, &fl);
        edx = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_local_write(&env, -44, 4, edx);
    {
        (void)lift_sub(32, edi, 0x4u, &fl);
    }
    if (fl.cf)
        goto L_46cd79;
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46cea9;
    ecx = 0x9u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_local_write(&env, -104, 4, ecx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, ebx);
L_46cea9:
    esi = eax;
    ecx = lift_load(&env, 0u, 0x4fbf60u, 4);
    ebx = lift_load(&env, 0u, 0x4f8a1au, 4);
    edx = lift_load(&env, 0u, 0x4f8a16u, 4);
    eax = esi;
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
    eax = lift_call(&env, 0x4710d0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x4u, 4, 0xbu);
    lift_store(&env, esi, 0x48u, 2, 0xff9cu);
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    edx = 0x1u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adfa0u, eax, edx, ebx, ecx, 0);
    edx = 0x44fc60u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    lift_local_write(&env, -64, 4, edi);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
L_46cf1b:
    eax = 0x194u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46cf2e;
    eax = lift_call(&env, 0x43d3f0u, eax, edx, ebx, ecx, 0);
L_46cf2e:
    esi = eax;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_46e821;
    lift_store(&env, eax, 0x0u, 4, 0x9u);
    lift_store(&env, eax, 0x4u, 4, 0x1u);
L_46cf45:
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a24u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8a14u, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a10u, 2)) & 0xffffu);
    env.stack[env.sp++] = eax;
    eax = lift_load(&env, 0u, 0x4f8a22u, 4);
    lift_store(&env, esi, 0x184u, 4, 0x0u);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x188u, 4, 0x2u);
    env.stack[env.sp++] = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a20u, 2)) & 0xffffu);
    ebx = lift_load(&env, edi, 0x54682du, 4);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    ecx = lift_load(&env, 0u, 0x4f8a1eu, 4);
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
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = eax;
    edx = lift_load(&env, 0u, 0x532bc0u, 4);
    eax = esi;
    eax = lift_call(&env, 0x4b5700u, eax, edx, ebx, ecx, 3);
    edx = lift_local_read(&env, -64, 4);
    eax = lift_local_read(&env, -92, 4);
    ebx = esi;
    edx = lift_load(&env, edx, 0x4fd628u, 4);
    eax = lift_call(&env, 0x4123d0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_46e82d;
    eax = lift_load(&env, 0u, 0x4f8a14u, 4);
    ecx = lift_load(&env, 0u, 0x4f8a10u, 4);
    ebx = lift_load(&env, 0u, 0x4f8a22u, 4);
    edx = lift_load(&env, 0u, 0x4f8a1eu, 4);
    env.stack[env.sp++] = eax;
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
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1);
L_46d004:
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x148u, 2, 0x4u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    edx = lift_local_read(&env, -64, 4);
    {
        uint32_t r = lift_add(32, edx, 0x4u, &fl);
        edx = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_local_write(&env, -64, 4, edx);
    {
        (void)lift_sub(32, edi, 0x4u, &fl);
    }
    if (fl.cf)
        goto L_46cf1b;
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46d04f;
    ecx = 0xbu;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_local_write(&env, -104, 4, ecx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, ebx);
L_46d04f:
    esi = eax;
    ecx = lift_load(&env, 0u, 0x4fbf60u, 4);
    ebx = lift_load(&env, 0u, 0x4f8a22u, 4);
    edx = lift_load(&env, 0u, 0x4f8a1eu, 4);
    eax = esi;
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
    eax = lift_call(&env, 0x4710d0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x4u, 4, 0x9u);
    lift_store(&env, esi, 0x48u, 2, 0xff9cu);
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    edx = 0x1u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adfa0u, eax, edx, ebx, ecx, 0);
    edx = 0x44fad0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    lift_local_write(&env, -48, 4, edi);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
L_46d0c1:
    eax = 0x194u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46d0d4;
    eax = lift_call(&env, 0x43d3f0u, eax, edx, ebx, ecx, 0);
L_46d0d4:
    esi = eax;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_46e848;
    lift_store(&env, eax, 0x0u, 4, 0xcu);
    lift_store(&env, eax, 0x4u, 4, 0x2u);
L_46d0eb:
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a34u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8a14u, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a10u, 2)) & 0xffffu);
    env.stack[env.sp++] = eax;
    eax = lift_load(&env, 0u, 0x4f8a32u, 4);
    lift_store(&env, esi, 0x184u, 4, 0x0u);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x188u, 4, 0x2u);
    env.stack[env.sp++] = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a30u, 2)) & 0xffffu);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    ebx = lift_load(&env, edi, 0x54682du, 4);
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
    ecx = lift_load(&env, 0u, 0x4f8a2eu, 4);
    env.stack[env.sp++] = eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b5700u, eax, edx, ebx, ecx, 3);
    edx = lift_local_read(&env, -48, 4);
    eax = lift_local_read(&env, -92, 4);
    ebx = esi;
    edx = lift_load(&env, edx, 0x4fd618u, 4);
    eax = lift_call(&env, 0x4123d0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_46e854;
    eax = lift_load(&env, 0u, 0x4f8a14u, 4);
    ecx = lift_load(&env, 0u, 0x4f8a10u, 4);
    ebx = lift_load(&env, 0u, 0x4f8a32u, 4);
    edx = lift_load(&env, 0u, 0x4f8a2eu, 4);
    env.stack[env.sp++] = eax;
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
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1);
L_46d1a6:
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x148u, 2, 0x3u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    edx = lift_local_read(&env, -48, 4);
    {
        uint32_t r = lift_add(32, edx, 0x4u, &fl);
        edx = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_local_write(&env, -48, 4, edx);
    {
        (void)lift_sub(32, edi, 0x4u, &fl);
    }
    if (fl.cf)
        goto L_46d0c1;
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46d1f1;
    ecx = 0xdu;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_local_write(&env, -104, 4, ecx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, ebx);
L_46d1f1:
    esi = eax;
    ecx = lift_load(&env, 0u, 0x4fbf60u, 4);
    ebx = lift_load(&env, 0u, 0x4f8a32u, 4);
    edx = lift_load(&env, 0u, 0x4f8a2eu, 4);
    eax = esi;
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
    eax = lift_call(&env, 0x4710d0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x4u, 4, 0xcu);
    lift_store(&env, esi, 0x48u, 2, 0xff9cu);
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    edx = 0x1u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adfa0u, eax, edx, ebx, ecx, 0);
    edx = 0x44fc60u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    lift_local_write(&env, -40, 4, edi);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
L_46d263:
    eax = 0x194u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46d276;
    eax = lift_call(&env, 0x43d3f0u, eax, edx, ebx, ecx, 0);
L_46d276:
    esi = eax;
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_46e86f;
    lift_store(&env, eax, 0x0u, 4, 0xau);
    lift_store(&env, eax, 0x4u, 4, 0x2u);
L_46d28d:
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a2cu, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8a14u, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a10u, 2)) & 0xffffu);
    env.stack[env.sp++] = eax;
    eax = lift_load(&env, 0u, 0x4f8a2au, 4);
    ecx = lift_load(&env, 0u, 0x4f8a26u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x184u, 4, 0x0u);
    env.stack[env.sp++] = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a28u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x188u, 4, 0x2u);
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
    edx = lift_load(&env, 0u, 0x532bc0u, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ebx = lift_load(&env, edi, 0x54682du, 4);
    env.stack[env.sp++] = eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b5700u, eax, edx, ebx, ecx, 3);
    edx = lift_local_read(&env, -40, 4);
    eax = lift_local_read(&env, -92, 4);
    ebx = esi;
    edx = lift_load(&env, edx, 0x4fd638u, 4);
    eax = lift_call(&env, 0x4123d0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_46e87b;
    eax = lift_load(&env, 0u, 0x4f8a14u, 4);
    ecx = lift_load(&env, 0u, 0x4f8a10u, 4);
    ebx = lift_load(&env, 0u, 0x4f8a2au, 4);
    edx = lift_load(&env, 0u, 0x4f8a26u, 4);
    env.stack[env.sp++] = eax;
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
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1);
L_46d34c:
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x148u, 2, 0x5u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    edx = lift_local_read(&env, -40, 4);
    {
        uint32_t r = lift_add(32, edx, 0x4u, &fl);
        edx = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_local_write(&env, -40, 4, edx);
    {
        (void)lift_sub(32, edi, 0x4u, &fl);
    }
    if (fl.cf)
        goto L_46d263;
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46d397;
    ecx = 0xfu;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_local_write(&env, -104, 4, ecx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, ebx);
L_46d397:
    esi = eax;
    ecx = lift_load(&env, 0u, 0x4fbf60u, 4);
    ebx = lift_load(&env, 0u, 0x4f8a2au, 4);
    edx = lift_load(&env, 0u, 0x4f8a26u, 4);
    eax = esi;
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
    eax = lift_call(&env, 0x4710d0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x4u, 4, 0xau);
    lift_store(&env, esi, 0x48u, 2, 0xff9cu);
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    edx = 0x1u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adfa0u, eax, edx, ebx, ecx, 0);
    edx = 0x44fad0u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x194u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46d427;
    esi = 0x11u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_local_write(&env, -104, 4, esi);
    eax = lift_call(&env, 0x4b5580u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, edi);
L_46d427:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    lift_store(&env, esi, 0x0u, 4, 0x7u);
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x4u, 4, 0x1u);
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8ae4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8aecu, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8ae8u, 2)) & 0xffffu);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ebx = lift_load(&env, 0u, 0x4f9c09u, 4);
    env.stack[env.sp++] = eax;
    eax = lift_load(&env, 0u, 0x4f8ae2u, 4);
    lift_store(&env, esi, 0x184u, 4, 0x1u);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x188u, 4, 0x8u);
    env.stack[env.sp++] = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8ae0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    ecx = lift_load(&env, 0u, 0x4f8adeu, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = eax;
    eax = esi;
    lift_store(&env, esi, 0x44u, 1, 0x10u);
    eax = lift_call(&env, 0x4b5700u, eax, edx, ebx, ecx, 3);
    edx = 0x450cd0u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    edx = 0x5u;
    eax = esi;
    ebx = esi;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    edx = 0x28u;
    eax = lift_local_read(&env, -92, 4);
    eax = lift_call(&env, 0x4123d0u, eax, edx, ebx, ecx, 0);
    eax = lift_load(&env, 0u, 0x4f8aecu, 4);
    ecx = lift_load(&env, 0u, 0x4f8ae8u, 4);
    ebx = lift_load(&env, 0u, 0x4f8ae2u, 4);
    edx = lift_load(&env, 0u, 0x4f8adeu, 4);
    env.stack[env.sp++] = eax;
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
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1);
    edx = lift_load(&env, 0u, 0x532aa4u, 4);
    eax = esi;
    eax = lift_call(&env, 0x4b58a0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x194u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46d53d;
    edx = 0x13u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_local_write(&env, -104, 4, edx);
    eax = lift_call(&env, 0x4b5580u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, ecx);
L_46d53d:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    lift_store(&env, esi, 0x0u, 4, 0x8u);
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x4u, 4, 0x2u);
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8af4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8afcu, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8af8u, 2)) & 0xffffu);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ecx = lift_load(&env, 0u, 0x4f8aeeu, 4);
    env.stack[env.sp++] = eax;
    eax = lift_load(&env, 0u, 0x4f8af2u, 4);
    lift_store(&env, esi, 0x184u, 4, 0x1u);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    lift_store(&env, esi, 0x188u, 4, 0x8u);
    env.stack[env.sp++] = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8af0u, 2)) & 0xffffu);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x4f9c09u, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = eax;
    eax = esi;
    lift_store(&env, esi, 0x44u, 1, 0x10u);
    eax = lift_call(&env, 0x4b5700u, eax, edx, ebx, ecx, 3);
    edx = 0x450cd0u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    edx = 0x5u;
    eax = esi;
    ebx = esi;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    edx = 0x29u;
    eax = lift_local_read(&env, -92, 4);
    eax = lift_call(&env, 0x4123d0u, eax, edx, ebx, ecx, 0);
    ebx = lift_load(&env, 0u, 0x4f8afcu, 4);
    ecx = lift_load(&env, 0u, 0x4f8af8u, 4);
    edx = lift_load(&env, 0u, 0x4f8aeeu, 4);
    eax = esi;
    env.stack[env.sp++] = ebx;
    ebx = lift_load(&env, 0u, 0x4f8af2u, 4);
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
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1);
    edx = lift_load(&env, 0u, 0x532aa8u, 4);
    eax = esi;
    eax = lift_call(&env, 0x4b58a0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x174u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46d654;
    esi = 0x15u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_local_write(&env, -104, 4, esi);
    eax = lift_call(&env, 0x42b150u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, edi);
L_46d654:
    ecx = eax;
    edx = 0x44fe80u;
    lift_store(&env, ecx, 0x0u, 4, 0xdu);
    eax = ecx;
    lift_store(&env, ecx, 0x4u, 4, 0x1u);
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = ecx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adfa0u, eax, edx, ebx, ecx, 0);
    edx = 0x1f4u;
    eax = ecx;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0);
    edx = 0x1f4u;
    eax = ecx;
    eax = lift_call(&env, 0x4ac860u, eax, edx, ebx, ecx, 0);
    eax = ecx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x42b370u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = ecx;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x174u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46d6c8;
    edx = 0x17u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_local_write(&env, -104, 4, edx);
    eax = lift_call(&env, 0x42b150u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, ecx);
L_46d6c8:
    ecx = eax;
    edx = 0x44fe80u;
    lift_store(&env, ecx, 0x0u, 4, 0xeu);
    eax = ecx;
    lift_store(&env, ecx, 0x4u, 4, 0x2u);
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = ecx;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adfa0u, eax, edx, ebx, ecx, 0);
    edx = 0x1f4u;
    eax = ecx;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0);
    edx = 0x1f4u;
    eax = ecx;
    eax = lift_call(&env, 0x4ac860u, eax, edx, ebx, ecx, 0);
    edx = 0x1u;
    eax = ecx;
    eax = lift_call(&env, 0x42b370u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = ecx;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    edx = 0x5u;
    eax = 0x598d30u;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0);
    edx = 0x5u;
    lift_local_write(&env, -20, 1, (eax & 0xffu));
    eax = 0x598d30u;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0);
    edx = 0x5u;
    lift_local_write(&env, -24, 1, (eax & 0xffu));
    eax = 0x598d30u;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -16, 1, (eax & 0xffu));
    eax = 0x16cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46d765;
    eax = lift_call(&env, 0x43a160u, eax, edx, ebx, ecx, 0);
L_46d765:
    edi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    lift_local_write(&env, -80, 4, edi);
    eax = edi;
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, edi, 0x0u, 4, 0x5u);
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    env.stack[env.sp++] = 0xcu;
    eax = lift_load(&env, 0u, 0x4f8b0eu, 4);
    ecx = lift_load(&env, 0u, 0x4f8b06u, 4);
    ebx = lift_load(&env, 0u, 0x4f8b02u, 4);
    edx = lift_load(&env, 0u, 0x4f8afeu, 4);
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
    env.stack[env.sp++] = eax;
    eax = lift_load(&env, 0u, 0x4f8b0au, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
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
    env.stack[env.sp++] = eax;
    eax = edi;
    esi = edi;
    eax = lift_call(&env, 0x43a310u, eax, edx, ebx, ecx, 3);
    ebx = 0x44c3d0u;
    ecx = (edi + 0xcu);
L_46d7c7:
    edx = ebx;
    eax = lift_load(&env, esi, 0x15cu, 4);
    {
        uint32_t r = lift_add(32, esi, 0x4u, &fl);
        esi = r;
    }
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_sub(32, esi, ecx, &fl);
    }
    if (!fl.zf)
        goto L_46d7c7;
    ecx = lift_local_read(&env, -19, 4);
    ebx = lift_local_read(&env, -27, 4);
    edx = lift_local_read(&env, -23, 4);
    eax = lift_local_read(&env, -80, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x43a4f0u, eax, edx, ebx, ecx, 0);
    eax = lift_local_read(&env, -80, 4);
    edx = 0x5u;
    eax = lift_call(&env, 0x43a520u, eax, edx, ebx, ecx, 0);
    eax = 0x598d30u;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0);
    edx = 0x5u;
    ebx = eax;
    eax = 0x598d30u;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0);
    edx = 0x5u;
    lift_local_write(&env, -28, 2, (eax & 0xffffu));
    eax = 0x598d30u;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0);
    ecx = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    eax = lift_local_read(&env, -31, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        eax = r;
    }
    edx = (uint32_t)(int32_t)(int8_t)(uint8_t)(ebx & 0xffu);
    ebx = eax;
    eax = lift_local_read(&env, -80, 4);
    eax = lift_call(&env, 0x43a4f0u, eax, edx, ebx, ecx, 0);
    edx = lift_local_read(&env, -80, 4);
    eax = 0x54671cu;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    edx = lift_local_read(&env, -76, 4);
    eax = lift_local_read(&env, -80, 4);
    lift_store(&env, edx, 0x3b4u, 4, eax);
    eax = 0x16cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46d872;
    eax = lift_call(&env, 0x43a160u, eax, edx, ebx, ecx, 0);
L_46d872:
    lift_local_write(&env, -56, 4, eax);
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    edi = lift_local_read(&env, -56, 4);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    env.stack[env.sp++] = 0x0u;
    eax = edi;
    lift_store(&env, edi, 0x0u, 4, 0x6u);
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    env.stack[env.sp++] = 0xcu;
    eax = lift_load(&env, 0u, 0x4f8b22u, 4);
    ecx = lift_load(&env, 0u, 0x4f8b1au, 4);
    ebx = lift_load(&env, 0u, 0x4f8b16u, 4);
    edx = lift_load(&env, 0u, 0x4f8b12u, 4);
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
    env.stack[env.sp++] = eax;
    eax = lift_load(&env, 0u, 0x4f8b1eu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
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
    env.stack[env.sp++] = eax;
    eax = edi;
    esi = edi;
    eax = lift_call(&env, 0x43a310u, eax, edx, ebx, ecx, 3);
    ebx = 0x44c3d0u;
    ecx = (edi + 0xcu);
L_46d8d5:
    edx = ebx;
    eax = lift_load(&env, esi, 0x15cu, 4);
    {
        uint32_t r = lift_add(32, esi, 0x4u, &fl);
        esi = r;
    }
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_sub(32, esi, ecx, &fl);
    }
    if (!fl.zf)
        goto L_46d8d5;
    ecx = lift_local_read(&env, -19, 4);
    ebx = lift_local_read(&env, -27, 4);
    edx = lift_local_read(&env, -23, 4);
    eax = edi;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ecx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x43a4f0u, eax, edx, ebx, ecx, 0);
    eax = edi;
    edx = 0x5u;
    eax = lift_call(&env, 0x43a520u, eax, edx, ebx, ecx, 0);
    eax = 0x598d30u;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0);
    edx = 0x5u;
    ecx = eax;
    eax = 0x598d30u;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0);
    edx = 0x5u;
    ebx = eax;
    eax = 0x598d30u;
    eax = lift_call(&env, 0x4826c0u, eax, edx, ebx, ecx, 0);
    ebx = (uint32_t)(int32_t)(int8_t)(uint8_t)(ebx & 0xffu);
    eax = (uint32_t)(int32_t)(int8_t)(uint8_t)(eax & 0xffu);
    edx = (uint32_t)(int32_t)(int8_t)(uint8_t)(ecx & 0xffu);
    ecx = eax;
    eax = edi;
    eax = lift_call(&env, 0x43a4f0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = edi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = lift_local_read(&env, -72, 4);
    lift_store(&env, eax, 0x3b4u, 4, edi);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
L_46d963:
    ecx = lift_load(&env, 0u, 0x4f8b0cu, 4);
    {
        uint32_t r = lift_imul(32, ecx, edi, &fl);
        ecx = r;
    }
    edx = lift_load(&env, 0u, 0x4f8b08u, 4);
    ebx = lift_load(&env, 0u, 0x4f8b00u, 4);
    eax = lift_load(&env, 0u, 0x4f8b0cu, 4);
    esi = lift_load(&env, 0u, 0x4f8b04u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, ecx, esi, &fl);
        ecx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    eax = 0x15cu;
    {
        uint32_t r = lift_add(32, edx, ebx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46d9a0;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
L_46d9a0:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x457170u;
    env.stack[env.sp++] = 0x0u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ecx & 0xffffu);
    env.stack[env.sp++] = 0x0u;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0);
    eax = (edi + 0x64u);
    edx = 0x1u;
    lift_store(&env, esi, 0x0u, 4, eax);
    eax = esi;
    eax = lift_call(&env, 0x4ac470u, eax, edx, ebx, ecx, 0);
    edx = 0x1u;
    eax = esi;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x4eu, 1, 0x28u);
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x2u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_sub(32, edi, 0x3u, &fl);
    }
    if (fl.cf)
        goto L_46d963;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
L_46da15:
    edx = lift_load(&env, 0u, 0x4f8b1cu, 4);
    eax = lift_load(&env, 0u, 0x4f8b14u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    eax = lift_load(&env, 0u, 0x4f8b20u, 4);
    {
        uint32_t r = lift_imul(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, lift_load(&env, 0u, 0x4f8b18u, 4), &fl);
        eax = r;
    }
    ecx = lift_load(&env, 0u, 0x4f8b20u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, ecx, eax, &fl);
        ecx = r;
    }
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46da4f;
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
L_46da4f:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x4572b0u;
    env.stack[env.sp++] = 0x0u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(ecx & 0xffffu);
    env.stack[env.sp++] = 0x0u;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0);
    eax = (edi + 0x67u);
    edx = 0x1u;
    lift_store(&env, esi, 0x0u, 4, eax);
    eax = esi;
    eax = lift_call(&env, 0x4ac470u, eax, edx, ebx, ecx, 0);
    edx = 0x1u;
    eax = esi;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x4eu, 1, 0x28u);
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x2u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_sub(32, edi, 0x3u, &fl);
    }
    if (fl.cf)
        goto L_46da15;
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46dae5;
    ebx = 0x19u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_local_write(&env, -104, 4, ebx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, esi);
L_46dae5:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    ebx = lift_load(&env, 0u, 0x4f8982u, 4);
    edx = lift_load(&env, 0u, 0x4f897eu, 4);
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x1u;
    lift_store(&env, esi, 0x0u, 4, 0xfu);
    eax = esi;
    lift_store(&env, esi, 0x4u, 4, 0x1u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    edx = 0x44c5a0u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x4eu, 1, 0x0u);
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    ecx = 0x140u;
    eax = lift_call(&env, 0x4ac950u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x58u, 4, 0x0u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    env.stack[env.sp++] = 0x0u;
    ebx = lift_load(&env, 0u, 0x4f898cu, 4);
    edi = lift_load(&env, 0u, 0x4f8984u, 4);
    edx = lift_load(&env, 0u, 0x4f8988u, 4);
    eax = lift_load(&env, 0u, 0x4f8980u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, ebx, edi, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    eax = 0xfu;
    {
        uint32_t a = ebx;
        uint32_t r = lift_dec(32, a, &fl, 1);
        ebx = r;
    }
    eax = lift_call(&env, 0x46e8b0u, eax, edx, ebx, ecx, 1);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46dbd5;
    edx = 0x1bu;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_local_write(&env, -104, 4, edx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, ecx);
L_46dbd5:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    ebx = lift_load(&env, 0u, 0x4f8992u, 4);
    edx = lift_load(&env, 0u, 0x4f898eu, 4);
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x1u;
    lift_store(&env, esi, 0x0u, 4, 0x10u);
    eax = esi;
    lift_store(&env, esi, 0x4u, 4, 0x2u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    edx = 0x44c5a0u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x4eu, 1, 0x0u);
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    ecx = 0x140u;
    eax = lift_call(&env, 0x4ac950u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x58u, 4, 0x0u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    env.stack[env.sp++] = 0x1u;
    eax = lift_load(&env, 0u, 0x4f899cu, 4);
    ebx = lift_load(&env, 0u, 0x4f8994u, 4);
    edx = lift_load(&env, 0u, 0x4f8998u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    esi = lift_load(&env, 0u, 0x4f8990u, 4);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    ebx = (eax + 0xffffffffu);
    {
        uint32_t r = lift_add(32, edx, esi, &fl);
        edx = r;
    }
    eax = 0x10u;
    eax = lift_call(&env, 0x46e8b0u, eax, edx, ebx, ecx, 1);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46dcc7;
    edi = 0x1du;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_local_write(&env, -104, 4, edi);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, edx);
L_46dcc7:
    ecx = eax;
    edx = 0xau;
    eax = ecx;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    edx = 0x450df0u;
    eax = ecx;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = ecx;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46dd10;
    ecx = 0x1fu;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_local_write(&env, -104, 4, ecx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, ebx);
L_46dd10:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    ebx = lift_load(&env, 0u, 0x4f8a02u, 4);
    edx = lift_load(&env, 0u, 0x4f89feu, 4);
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x1u;
    lift_store(&env, esi, 0x0u, 4, 0x11u);
    eax = esi;
    lift_store(&env, esi, 0x4u, 4, 0x1u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    edx = 0x450d40u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x93u, 1, 0x0u);
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    lift_store(&env, esi, 0x95u, 1, 0x2u);
    lift_store(&env, esi, 0xa8u, 2, 0x0u);
    lift_store(&env, esi, 0xaau, 2, 0x0u);
    lift_store(&env, esi, 0xacu, 2, 0x0u);
    edx = 0x5449fcu;
    lift_store(&env, esi, 0xaeu, 2, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0);
    edx = lift_load(&env, 0u, 0x4fbf80u, 4);
    eax = esi;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46dded;
    esi = 0x21u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_local_write(&env, -104, 4, esi);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, edi);
L_46dded:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    ebx = lift_load(&env, 0u, 0x4f8a0au, 4);
    edx = lift_load(&env, 0u, 0x4f8a06u, 4);
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x1u;
    lift_store(&env, esi, 0x0u, 4, 0x12u);
    eax = esi;
    lift_store(&env, esi, 0x4u, 4, 0x2u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    edx = 0x450d40u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x93u, 1, 0x0u);
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    lift_store(&env, esi, 0x95u, 1, 0x2u);
    lift_store(&env, esi, 0xa8u, 2, 0x0u);
    lift_store(&env, esi, 0xaau, 2, 0x0u);
    lift_store(&env, esi, 0xacu, 2, 0x0u);
    edx = 0x5449fcu;
    lift_store(&env, esi, 0xaeu, 2, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0);
    edx = lift_load(&env, 0u, 0x4fbf80u, 4);
    eax = esi;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46deca;
    edx = 0x23u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_local_write(&env, -104, 4, edx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, ecx);
L_46deca:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x3e8u;
    lift_store(&env, esi, 0x0u, 4, 0x17u);
    eax = esi;
    lift_store(&env, esi, 0x4u, 4, 0x1u);
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0);
    edx = 0x96u;
    eax = esi;
    eax = lift_call(&env, 0x4ac860u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x58u, 4, 0x0u);
    edx = 0x450750u;
    lift_store(&env, esi, 0x64u, 4, 0xcu);
    eax = esi;
    lift_store(&env, esi, 0x70u, 4, 0xcu);
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46df61;
    ebx = 0x25u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_local_write(&env, -104, 4, ebx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, esi);
L_46df61:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x3e8u;
    lift_store(&env, esi, 0x0u, 4, 0x18u);
    eax = esi;
    lift_store(&env, esi, 0x4u, 4, 0x2u);
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0);
    edx = 0x96u;
    eax = esi;
    eax = lift_call(&env, 0x4ac860u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x58u, 4, 0x0u);
    edx = 0x450750u;
    lift_store(&env, esi, 0x64u, 4, 0xcu);
    eax = esi;
    lift_store(&env, esi, 0x70u, 4, 0xcu);
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    lift_local_write(&env, -52, 4, edi);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x40u;
    edx = 0x1b9u;
    lift_local_write(&env, -36, 4, eax);
    lift_local_write(&env, -32, 4, edx);
L_46dfea:
    ecx = lift_local_read(&env, -92, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edi, 0x4f8bb8u, 2)) & 0xffffu);
    env.stack[env.sp++] = ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d74u, 2)) & 0xffffu);
    ebx = lift_load(&env, 0u, 0x4fbfacu, 4);
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d70u, 2)) & 0xffffu);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edi, 0x4f8b88u, 2)) & 0xffffu);
    env.stack[env.sp++] = 0xffffffffu;
    {
        uint32_t r = lift_add(32, eax, esi, &fl);
        eax = r;
    }
    ecx = lift_local_read(&env, -36, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2);
    ebx = lift_load(&env, 0u, 0x4f8c4cu, 4);
    lift_store(&env, eax, 0x4u, 4, 0x17u);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d74u, 2)) & 0xffffu);
    lift_store(&env, eax, 0x124u, 4, 0x0u);
    esi = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edi, 0x4f8bb8u, 2)) & 0xffffu);
    env.stack[env.sp++] = ebx;
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d70u, 2)) & 0xffffu);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edi, 0x4f8b88u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    ecx = lift_load(&env, 0u, 0x4f8c48u, 4);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adfa0u, eax, edx, ebx, ecx, 0);
    eax = lift_local_read(&env, -52, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    edx = 0xau;
    lift_store(&env, esi, 0x58u, 4, eax);
    eax = esi;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0);
    edx = 0x1f4u;
    eax = esi;
    eax = lift_call(&env, 0x4ac860u, eax, edx, ebx, ecx, 0);
    edx = 0x450860u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46e0c6;
    esi = 0x27u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_local_write(&env, -104, 4, esi);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, edx);
L_46e0c6:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d74u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edi, 0x4f8bb8u, 2)) & 0xffffu);
    env.stack[env.sp++] = 0x0u;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d70u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    env.stack[env.sp++] = 0x0u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edi, 0x4f8b88u, 2)) & 0xffffu);
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    env.stack[env.sp++] = 0x0u;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0xau;
    eax = esi;
    lift_store(&env, esi, 0x4u, 4, 0x17u);
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0);
    edx = lift_local_read(&env, -32, 4);
    eax = esi;
    eax = lift_call(&env, 0x4ac860u, eax, edx, ebx, ecx, 0);
    edx = 0x450a10u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adfa0u, eax, edx, ebx, ecx, 0);
    eax = lift_local_read(&env, -52, 4);
    edx = 0x546618u;
    lift_store(&env, esi, 0x7cu, 4, 0x0u);
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    lift_local_write(&env, -68, 4, eax);
    lift_store(&env, esi, 0x58u, 4, eax);
    eax = esi;
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0);
    eax = esi;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0);
    edx = esi;
    eax = 0x54671cu;
    ecx = lift_local_read(&env, -92, 4);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    ebx = lift_load(&env, 0u, 0x4fbfacu, 4);
    esi = (esi & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d74u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edi, 0x4f8c18u, 2)) & 0xffffu);
    env.stack[env.sp++] = ecx;
    {
        uint32_t r = lift_add(32, eax, esi, &fl);
        eax = r;
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d70u, 2)) & 0xffffu);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edi, 0x4f8be8u, 2)) & 0xffffu);
    env.stack[env.sp++] = 0xffffffffu;
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    ecx = lift_local_read(&env, -36, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2);
    esi = eax;
    lift_store(&env, eax, 0x4u, 4, 0x18u);
    ebx = lift_load(&env, 0u, 0x4f8c4cu, 4);
    lift_store(&env, eax, 0x124u, 4, 0x0u);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d74u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edi, 0x4f8c18u, 2)) & 0xffffu);
    env.stack[env.sp++] = ebx;
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d70u, 2)) & 0xffffu);
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edi, 0x4f8be8u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    ecx = lift_load(&env, 0u, 0x4f8c48u, 4);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x4adfa0u, eax, edx, ebx, ecx, 0);
    eax = lift_local_read(&env, -68, 4);
    edx = 0xau;
    lift_store(&env, esi, 0x58u, 4, eax);
    eax = esi;
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0);
    edx = 0x1f4u;
    eax = esi;
    eax = lift_call(&env, 0x4ac860u, eax, edx, ebx, ecx, 0);
    edx = 0x450860u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46e255;
    esi = 0x29u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_local_write(&env, -104, 4, esi);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, edx);
L_46e255:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d74u, 2)) & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edi, 0x4f8c18u, 2)) & 0xffffu);
    env.stack[env.sp++] = 0x0u;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d70u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    env.stack[env.sp++] = 0x0u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, edi, 0x4f8be8u, 2)) & 0xffffu);
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    env.stack[env.sp++] = 0x0u;
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0xau;
    eax = esi;
    lift_store(&env, esi, 0x4u, 4, 0x18u);
    eax = lift_call(&env, 0x4ac7d0u, eax, edx, ebx, ecx, 0);
    edx = lift_local_read(&env, -32, 4);
    eax = esi;
    eax = lift_call(&env, 0x4ac860u, eax, edx, ebx, ecx, 0);
    edx = 0x450a10u;
    eax = esi;
    {
        uint32_t r = lift_add(32, edi, 0x4u, &fl);
        edi = r;
    }
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    ecx = lift_local_read(&env, -52, 4);
    eax = lift_call(&env, 0x4adfa0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x7cu, 4, 0x0u);
    {
        uint32_t a = ecx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ecx = r;
    }
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    edx = 0x546618u;
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    eax = esi;
    lift_store(&env, esi, 0x58u, 4, ecx);
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0);
    eax = esi;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0);
    eax = esi;
    lift_local_write(&env, -52, 4, ecx);
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0);
    edx = esi;
    eax = 0x54671cu;
    esi = lift_local_read(&env, -36, 4);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = lift_local_read(&env, -32, 4);
    lift_local_write(&env, -104, 4, ebx);
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    {
        uint32_t r = lift_sub(32, eax, 0x28u, &fl);
        eax = r;
    }
    lift_local_write(&env, -36, 4, esi);
    lift_local_write(&env, -32, 4, eax);
    {
        (void)lift_sub(32, ecx, 0xcu, &fl);
    }
    if (fl.cf)
        goto L_46dfea;
    edx = lift_local_read(&env, -92, 4);
    ecx = 0x4cu;
    ebx = lift_load(&env, 0u, 0x4fbfa8u, 4);
    eax = lift_load(&env, 0u, 0x4f8c4eu, 4);
    env.stack[env.sp++] = edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = lift_load(&env, 0u, 0x4f8c52u, 4);
    env.stack[env.sp++] = 0xffffffffu;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2);
    ecx = lift_local_read(&env, -92, 4);
    ebx = lift_load(&env, 0u, 0x4fbfa8u, 4);
    edx = lift_load(&env, 0u, 0x4f8c5au, 4);
    eax = lift_load(&env, 0u, 0x4f8c56u, 4);
    env.stack[env.sp++] = ecx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    env.stack[env.sp++] = 0xffffffffu;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = 0x4du;
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46e39b;
    ebx = 0x2bu;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_local_write(&env, -104, 4, ebx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, esi);
L_46e39b:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x4u, 4, 0x1u);
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x45aa70u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46e3f6;
    edi = 0x2du;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_local_write(&env, -104, 4, edi);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, edx);
L_46e3f6:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    ebx = lift_load(&env, 0u, 0x4f8a5au, 4);
    env.stack[env.sp++] = 0x0u;
    edx = lift_load(&env, 0u, 0x4f8a56u, 4);
    eax = esi;
    env.stack[env.sp++] = 0x0u;
    lift_store(&env, esi, 0x0u, 4, 0x13u);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x4u, 4, 0x1u);
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d68u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a60u, 2)) & 0xffffu);
    lift_store(&env, esi, 0xa8u, 2, (eax & 0xffffu));
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a68u, 2)) & 0xffffu);
    lift_store(&env, esi, 0xaau, 2, (ecx & 0xffffu));
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a64u, 2)) & 0xffffu);
    lift_store(&env, esi, 0xaeu, 2, (edx & 0xffffu));
    edx = 0x544a34u;
    eax = esi;
    lift_store(&env, esi, 0xacu, 2, (ebx & 0xffffu));
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0);
    edx = lift_load(&env, 0u, 0x532a68u, 4);
    eax = esi;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0);
    eax = esi;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x4eu, 1, 0x64u);
    edx = 0x46u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x150u, 4, 0x1u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    edx = 0x45abd0u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    ecx = lift_load(&env, 0u, 0x4f8a74u, 4);
    ebx = lift_load(&env, 0u, 0x4f8a6au, 4);
    edx = lift_load(&env, 0u, 0x533d6au, 4);
    eax = esi;
    env.stack[env.sp++] = ecx;
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
    ecx = lift_load(&env, 0u, 0x4f8a70u, 4);
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1);
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46e51e;
    ebx = 0x2fu;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_local_write(&env, -104, 4, ebx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, esi);
L_46e51e:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x0u;
    eax = esi;
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x4u, 4, 0x2u);
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x45aa70u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_46e896;
L_46e568:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    ebx = lift_load(&env, 0u, 0x4f8a7au, 4);
    env.stack[env.sp++] = 0x0u;
    edx = lift_load(&env, 0u, 0x4f8a76u, 4);
    eax = esi;
    env.stack[env.sp++] = 0x0u;
    lift_store(&env, esi, 0x0u, 4, 0x14u);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x4u, 4, 0x2u);
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a80u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x8eu, 1, 0x3u);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a84u, 2)) & 0xffffu);
    lift_store(&env, esi, 0xa8u, 2, (eax & 0xffffu));
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a88u, 2)) & 0xffffu);
    lift_store(&env, esi, 0xaau, 2, (edx & 0xffffu));
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8a8cu, 2)) & 0xffffu);
    lift_store(&env, esi, 0xacu, 2, (ebx & 0xffffu));
    edx = 0x544a34u;
    eax = esi;
    lift_store(&env, esi, 0xaeu, 2, (ecx & 0xffffu));
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0);
    edx = lift_load(&env, 0u, 0x532a6cu, 4);
    eax = esi;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0);
    eax = esi;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x4eu, 1, 0x64u);
    lift_store(&env, esi, 0x4au, 2, 0x64u);
    lift_store(&env, esi, 0x4cu, 2, 0x32u);
    edx = 0x46u;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x150u, 4, 0x1u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    edx = 0x45abd0u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    ecx = lift_load(&env, 0u, 0x4f8a9cu, 4);
    ebx = lift_load(&env, 0u, 0x4f8a92u, 4);
    edx = lift_load(&env, 0u, 0x4f8a8eu, 4);
    eax = esi;
    env.stack[env.sp++] = ecx;
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
    ecx = lift_load(&env, 0u, 0x4f8a98u, 4);
    lift_store(&env, esi, 0x124u, 4, 0x1u);
    eax = lift_call(&env, 0x4ae110u, eax, edx, ebx, ecx, 1);
    eax = 0x54671cu;
    edx = esi;
    lift_store(&env, esi, 0x13cu, 4, 0x0u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = lift_call(&env, 0x4726d0u, eax, edx, ebx, ecx, 0);
    eax = lift_local_read(&env, -76, 4);
    eax = lift_load(&env, eax, 0x3b8u, 4);
    eax = lift_call(&env, 0x429d50u, eax, edx, ebx, ecx, 0);
    eax = lift_local_read(&env, -72, 4);
    eax = lift_load(&env, eax, 0x3b8u, 4);
    eax = lift_call(&env, 0x429d50u, eax, edx, ebx, ecx, 0);
    eax = lift_local_read(&env, -116, 4);
    env.chain = eax;
    return env.failed ? 0u : eax;
L_46e6ab:
    esi = 0x1u;
    lift_local_write(&env, -60, 4, eax);
    lift_local_write(&env, -104, 4, esi);
    eax = lift_call(&env, 0x43a6f0u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, ebx);
    esi = eax;
    goto L_46ca1d;
L_46e6c5:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a80u, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_46e707;
L_46e6ce:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b6cu, 2)) & 0xffffu);
    lift_store(&env, esi, 0x160u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b6eu, 2)) & 0xffffu);
    lift_store(&env, esi, 0x162u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b70u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x164u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b72u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x166u, 2, (eax & 0xffffu));
    goto L_46cace;
L_46e707:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a74u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_46e6ce;
    lift_store(&env, esi, 0x454u, 4, 0x1u);
    lift_store(&env, esi, 0x160u, 2, 0x6eu);
    lift_store(&env, esi, 0x162u, 2, 0x6fu);
    lift_store(&env, esi, 0x164u, 2, 0x6cu);
    lift_store(&env, esi, 0x166u, 2, 0x6du);
    goto L_46cace;
L_46e743:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a7cu, 4), 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_46e785;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b6cu, 2)) & 0xffffu);
    lift_store(&env, esi, 0x160u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b6eu, 2)) & 0xffffu);
    lift_store(&env, esi, 0x162u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b70u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x164u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b72u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x166u, 2, (eax & 0xffffu));
    goto L_46cbd7;
L_46e785:
    {
        (void)lift_sub(32, lift_load(&env, 0u, 0x532a78u, 4), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_46e7c1;
    lift_store(&env, esi, 0x454u, 4, 0x1u);
    lift_store(&env, esi, 0x160u, 2, 0xc6u);
    lift_store(&env, esi, 0x162u, 2, 0xc7u);
    lift_store(&env, esi, 0x164u, 2, 0xc4u);
    lift_store(&env, esi, 0x166u, 2, 0xc5u);
    goto L_46cbd7;
L_46e7c1:
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b74u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x160u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b76u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x162u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b78u, 2)) & 0xffffu);
    lift_store(&env, esi, 0x164u, 2, (eax & 0xffffu));
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x532b7au, 2)) & 0xffffu);
    lift_store(&env, esi, 0x166u, 2, (eax & 0xffffu));
    goto L_46cbd7;
L_46e7fa:
    lift_store(&env, eax, 0x4u, 4, 0xbu);
    goto L_46cda3;
L_46e806:
    edx = 0x44fc00u;
    eax = esi;
    lift_store(&env, esi, 0x138u, 4, 0x0u);
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    goto L_46ce5e;
L_46e821:
    lift_store(&env, eax, 0x4u, 4, 0x9u);
    goto L_46cf45;
L_46e82d:
    edx = 0x44fa70u;
    eax = esi;
    lift_store(&env, esi, 0x138u, 4, 0x0u);
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    goto L_46d004;
L_46e848:
    lift_store(&env, eax, 0x4u, 4, 0xcu);
    goto L_46d0eb;
L_46e854:
    edx = 0x44fc00u;
    eax = esi;
    lift_store(&env, esi, 0x138u, 4, 0x0u);
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    goto L_46d1a6;
L_46e86f:
    lift_store(&env, eax, 0x4u, 4, 0xau);
    goto L_46d28d;
L_46e87b:
    edx = 0x44fa70u;
    eax = esi;
    lift_store(&env, esi, 0x138u, 4, 0x0u);
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0);
    goto L_46d34c;
L_46e896:
    edi = 0x31u;
    lift_local_write(&env, -60, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_local_write(&env, -104, 4, edi);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -104, 4, edx);
    goto L_46e568;
}
