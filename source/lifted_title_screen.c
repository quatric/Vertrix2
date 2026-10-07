/* Lifted from the original routine at 0x465af0 by tools/lift.py: every instruction of the original
 * is translated in order (registers, frame, flags and gotos) and every unrecovered callee goes
 * through the call boundary with the registers and stack arguments the original holds there.
 * Verified against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_title_screen.h"

uint32_t lifted_title_screen(const VertrixCalls *calls, const VertrixFactoryServices *services,
                             const VertrixGlobals *globals, uint32_t frame, uint32_t eax,
                             uint32_t edx, uint32_t ebx, uint32_t ecx, const uint32_t *arguments,
                             const uint8_t *garbage, uint32_t chain)
{
    uint8_t local[LIFTED_TITLE_SCREEN_LOCALS + 8 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0};
    uint32_t esi = 0;
    uint32_t edi = 0;
    lift_begin(&env, calls, services, globals, frame, local, LIFTED_TITLE_SCREEN_LOCALS, 0, garbage,
               arguments, chain);
    eax = (frame + 0xffffffb8u);
    edx = 0x4ec1ecu;
    ecx = 0x515abcu;
    edi = 0xffffffe2u;
    env.stack[env.sp++] = env.chain;
    lift_store(&env, eax, 0x0u, 4, env.stack[--env.sp]);
    env.chain = eax;
    eax = lift_load(&env, 0u, 0x4f86d4u, 4);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_local_write(&env, -68, 4, edx);
    lift_local_write(&env, -44, 4, eax);
    lift_local_write(&env, -64, 4, ecx);
    esi = lift_local_read(&env, -44, 4);
    eax = lift_load(&env, 0u, 0x4f86d4u, 4);
    lift_local_write(&env, -60, 4, ebx);
    {
        uint32_t r = lift_sub(32, eax, esi, &fl);
        eax = r;
    }
    lift_local_write(&env, -24, 4, ebx);
    lift_local_write(&env, -36, 4, eax);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if ((fl.cf || fl.zf))
        goto L_465bdc;
L_465b49:
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_466cf0;
L_465b5b:
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
    edx = lift_local_read(&env, -24, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d30u, 2)) & 0xffffu);
    env.stack[env.sp++] = 0x1u;
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    ecx = 0x280u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    ecx = lift_local_read(&env, -24, 4);
    ebx = lift_local_read(&env, -44, 4);
    lift_store(&env, esi, 0x52u, 1, 0x8u);
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, (edi & 0xffffu));
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x110u, 1, 0x0u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    {
        uint32_t a = ecx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, edi, 0x6u, &fl);
        edi = r;
    }
    lift_local_write(&env, -24, 4, ecx);
    {
        (void)lift_sub(32, ecx, ebx, &fl);
    }
    if (fl.cf)
        goto L_465b49;
L_465bdc:
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    eax = lift_local_read(&env, -36, 4);
    lift_local_write(&env, -24, 4, esi);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if ((fl.cf || fl.zf))
        goto L_465c85;
L_465bec:
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_465bff;
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
L_465bff:
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
    env.stack[env.sp++] = 0x1u;
    ebx = lift_local_read(&env, -44, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d30u, 2)) & 0xffffu);
    ecx = lift_local_read(&env, -24, 4);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    ecx = 0x280u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    lift_store(&env, esi, 0x52u, 1, 0x8u);
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, (edi & 0xffffu));
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x110u, 1, 0x0u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    edx = lift_local_read(&env, -24, 4);
    ecx = lift_local_read(&env, -36, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edx = r;
    }
    {
        uint32_t r = lift_sub(32, edi, 0x6u, &fl);
        edi = r;
    }
    lift_local_write(&env, -24, 4, edx);
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (fl.cf)
        goto L_465bec;
L_465c85:
    ebx = lift_load(&env, 0u, 0x532a84u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (!fl.zf)
        goto L_465d34;
    eax = 0x180u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_466cfa;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0);
    esi = eax;
L_465cac:
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
    eax = lift_load(&env, 0u, 0x4f869eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    env.stack[env.sp++] = eax;
    env.stack[env.sp++] = eax;
    eax = lift_load(&env, 0u, 0x558c7cu, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x4u, 2)) & 0xffffu);
    edx = 0x50e506u;
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x4f9bfdu, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3);
    edx = 0x2u;
    eax = esi;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x44u, 1, 0x10u);
    lift_store(&env, esi, 0x4eu, 1, 0x32u);
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    eax = esi;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_store(&env, esi, 0x48u, 2, 0xffe2u);
    eax = lift_call(&env, 0x4ac910u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
L_465d34:
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_465d57;
    esi = 0x1u;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_local_write(&env, -60, 4, esi);
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, edi);
L_465d57:
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
    ebx = lift_load(&env, 0u, 0x4f85eau, 4);
    edx = lift_load(&env, 0u, 0x4f85e6u, 4);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85fcu, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f8u, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, 0xfu);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x52u, 1, 0x8u);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = 0xff000000u;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x1u);
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_465e03;
    edx = 0x3u;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_local_write(&env, -60, 4, edx);
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, ecx);
L_465e03:
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
    ebx = lift_load(&env, 0u, 0x4f85f2u, 4);
    edx = lift_load(&env, 0u, 0x4f85eeu, 4);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85fcu, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f8u, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, 0xfu);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x52u, 1, 0xbu);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = 0xff000000u;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x1u);
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_465eaf;
    ebx = 0x5u;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_local_write(&env, -60, 4, ebx);
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, esi);
L_465eaf:
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
    ebx = lift_load(&env, 0u, 0x4f86dau, 4);
    edx = lift_load(&env, 0u, 0x4f86d6u, 4);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86e4u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86e0u, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, 0xfff6u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x52u, 1, 0x9u);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = 0xff000000u;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x1u);
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_465f5b;
    edi = 0x7u;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_local_write(&env, -60, 4, edi);
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, edx);
L_465f5b:
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
    ebx = lift_load(&env, 0u, 0x4f86fau, 4);
    edx = lift_load(&env, 0u, 0x4f86f6u, 4);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8704u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8700u, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, 0xfff6u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x52u, 1, 0x9u);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = 0xff000000u;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x1u);
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_466007;
    ecx = 0x9u;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_local_write(&env, -60, 4, ecx);
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, ebx);
L_466007:
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
    ebx = lift_load(&env, 0u, 0x4f86eau, 4);
    edx = lift_load(&env, 0u, 0x4f86e6u, 4);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86f4u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86f0u, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, 0xfff6u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x52u, 1, 0x9u);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = 0xff000000u;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x1u);
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -24, 4, esi);
L_466095:
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
L_466097:
    eax = lift_load(&env, 0u, 0x4f9060u, 4);
    {
        uint32_t r = lift_add(32, eax, lift_load(&env, 0u, 0x4f8668u, 4), &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, lift_load(&env, 0u, 0x4f8660u, 4), &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x4f866cu, 4);
    lift_local_write(&env, -40, 4, eax);
    eax = lift_load(&env, 0u, 0x4f9064u, 4);
    esi = lift_local_read(&env, -24, 4);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, esi, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, lift_load(&env, 0u, 0x4f8664u, 4), &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    lift_local_write(&env, -28, 4, eax);
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4660f3;
    ecx = 0xbu;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_local_write(&env, -60, 4, ecx);
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, ebx);
L_4660f3:
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
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f9064u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(32, eax, 0x4u, &fl);
        eax = r;
    }
    ebx = lift_local_read(&env, -30, 4);
    edx = lift_local_read(&env, -42, 4);
    {
        uint32_t r = lift_and(32, eax, 0xffffu, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f9060u, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_sub(32, eax, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = (ecx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    lift_store(&env, esi, 0x48u, 2, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x52u, 1, 0x8u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = 0x7fu;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x1u);
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = lift_load(&env, 0u, 0x4f9060u, 4);
    {
        uint32_t r = lift_add(32, eax, lift_load(&env, 0u, 0x4f8668u, 4), &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, lift_load(&env, 0u, 0x4f8670u, 4), &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, 0u, 0x4f866cu, 4);
    lift_local_write(&env, -40, 4, eax);
    eax = lift_load(&env, 0u, 0x4f9064u, 4);
    ebx = lift_local_read(&env, -24, 4);
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_imul(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, lift_load(&env, 0u, 0x4f8674u, 4), &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    lift_local_write(&env, -28, 4, eax);
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4661dd;
    edx = 0xdu;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_local_write(&env, -60, 4, edx);
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, ecx);
L_4661dd:
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
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f9064u, 2)) & 0xffffu);
    {
        uint32_t r = lift_sub(32, eax, 0x4u, &fl);
        eax = r;
    }
    ebx = lift_local_read(&env, -30, 4);
    edx = lift_local_read(&env, -42, 4);
    {
        uint32_t r = lift_and(32, eax, 0xffffu, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f9060u, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_sub(32, eax, 0x4u, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ecx = (ecx & 0xffff0000u) | (((eax & 0xffffu)) & 0xffffu);
    eax = esi;
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    lift_store(&env, esi, 0x48u, 2, 0x0u);
    eax = esi;
    lift_store(&env, esi, 0x52u, 1, 0x8u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = 0x7fu;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x1u);
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, ebx);
    {
        (void)lift_sub(32, edi, 0x4u, &fl);
    }
    if ((fl.sf != fl.of))
        goto L_466097;
    esi = lift_local_read(&env, -24, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    lift_local_write(&env, -24, 4, esi);
    {
        (void)lift_sub(32, esi, 0x7u, &fl);
    }
    if (fl.cf)
        goto L_466095;
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_466d01;
    edx = 0xfu;
    lift_local_write(&env, -52, 4, eax);
    lift_local_write(&env, -60, 4, edx);
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, ebx);
    esi = eax;
L_4662b1:
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
    ebx = lift_load(&env, 0u, 0x4f85a2u, 4);
    edx = lift_load(&env, 0u, 0x4f85e6u, 4);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85a8u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f8u, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, 0xfff6u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = 0xff000000u;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x0u);
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_466357;
    ebx = 0x11u;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_local_write(&env, -60, 4, ebx);
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, esi);
L_466357:
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
    ebx = lift_load(&env, 0u, 0x4f85a2u, 4);
    edx = lift_load(&env, 0u, 0x4f85eeu, 4);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85a8u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85f8u, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, 0xfff6u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = 0xff000000u;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x0u);
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4663ff;
    edi = 0x13u;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_local_write(&env, -60, 4, edi);
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, edx);
L_4663ff:
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
    ebx = lift_load(&env, 0u, 0x4f85a2u, 4);
    edx = lift_load(&env, 0u, 0x4f8606u, 4);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f85a8u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8610u, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, 0xfff6u);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = 0xff000000u;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x0u);
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = lift_load(&env, 0u, 0x4f870cu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_local_write(&env, -44, 4, eax);
    edi = 0xffffffe2u;
    ecx = lift_local_read(&env, -44, 4);
    eax = lift_load(&env, 0u, 0x4f870cu, 4);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_sub(32, eax, ecx, &fl);
        eax = r;
    }
    lift_local_write(&env, -24, 4, ebx);
    lift_local_write(&env, -32, 4, eax);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if ((fl.cf || fl.zf))
        goto L_466541;
L_4664ad:
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4664c0;
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
L_4664c0:
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
    edx = lift_local_read(&env, -24, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8708u, 2)) & 0xffffu);
    env.stack[env.sp++] = 0x1u;
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    ecx = 0x280u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    lift_store(&env, esi, 0x52u, 1, 0x8u);
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, (edi & 0xffffu));
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x110u, 1, 0x0u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = lift_local_read(&env, -24, 4);
    {
        uint32_t r = lift_add(32, edi, 0x7u, &fl);
        edi = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_inc(32, a, &fl, 1);
        eax = r;
    }
    edx = lift_local_read(&env, -44, 4);
    lift_local_write(&env, -24, 4, eax);
    {
        (void)lift_sub(32, eax, edx, &fl);
    }
    if (fl.cf)
        goto L_4664ad;
L_466541:
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    ebx = lift_local_read(&env, -32, 4);
    lift_local_write(&env, -24, 4, ecx);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if ((fl.cf || fl.zf))
        goto L_4665ea;
L_466551:
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_466564;
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
L_466564:
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
    env.stack[env.sp++] = 0x1u;
    ebx = lift_local_read(&env, -44, 4);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8708u, 2)) & 0xffffu);
    ecx = lift_local_read(&env, -24, 4);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    ecx = 0x280u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    lift_store(&env, esi, 0x52u, 1, 0x8u);
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, (edi & 0xffffu));
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x110u, 1, 0x0u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    esi = lift_local_read(&env, -24, 4);
    {
        uint32_t r = lift_sub(32, edi, 0x7u, &fl);
        edi = r;
    }
    {
        uint32_t a = esi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        esi = r;
    }
    edx = lift_local_read(&env, -32, 4);
    lift_local_write(&env, -24, 4, esi);
    {
        (void)lift_sub(32, esi, edx, &fl);
    }
    if (fl.cf)
        goto L_466551;
L_4665ea:
    ecx = lift_load(&env, 0u, 0x532a8cu, 4);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_466d08;
L_4665f8:
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46661b;
    esi = 0x15u;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_local_write(&env, -60, 4, esi);
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, edi);
L_46661b:
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
    ebx = lift_load(&env, 0u, 0x4f86c6u, 4);
    edx = lift_load(&env, 0u, 0x4f86c2u, 4);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86d0u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86ccu, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, 0xffddu);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x0u);
    edx = 0xff000000u;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x1u);
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x160u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4666c3;
    edx = 0x17u;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_local_write(&env, -60, 4, edx);
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, ecx);
L_4666c3:
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
    ebx = lift_load(&env, 0u, 0x4f86b6u, 4);
    edx = lift_load(&env, 0u, 0x4f86b2u, 4);
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86c0u, 2)) & 0xffffu);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f86bcu, 2)) & 0xffffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    env.stack[env.sp++] = eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b54d0u, eax, edx, ebx, ecx, 1);
    edx = 0x2u;
    eax = esi;
    lift_store(&env, esi, 0x48u, 2, 0xffddu);
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_store(&env, esi, 0x94u, 1, 0x1u);
    edx = 0xff000000u;
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    eax = esi;
    lift_store(&env, esi, 0x110u, 1, 0x1u);
    eax = lift_call(&env, 0x4ac4e0u, eax, edx, ebx, ecx, 0);
    eax = 0x54671cu;
    edx = esi;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x180u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46676b;
    ebx = 0x19u;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_local_write(&env, -60, 4, ebx);
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, esi);
L_46676b:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x4479f0u;
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
    eax = lift_load(&env, 0u, 0x4f8712u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    env.stack[env.sp++] = eax;
    edi = (edi & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8718u, 2)) & 0xffffu);
    env.stack[env.sp++] = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8710u, 2)) & 0xffffu);
    edx = 0x50e518u;
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    ecx = lift_load(&env, 0u, 0x4f870eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x540018u, 4);
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    env.stack[env.sp++] = eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3);
    edx = 0x2u;
    eax = esi;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x44u, 1, 0x8u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x180u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46680e;
    edi = 0x1bu;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    lift_local_write(&env, -60, 4, edi);
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, edx);
L_46680e:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x4479f0u;
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
    eax = lift_load(&env, 0u, 0x4f871eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    env.stack[env.sp++] = eax;
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8724u, 2)) & 0xffffu);
    env.stack[env.sp++] = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x533d34u, 2)) & 0xffffu);
    ecx = lift_load(&env, 0u, 0x533d32u, 4);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x540018u, 4);
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
    env.stack[env.sp++] = eax;
    edx = 0x50e51cu;
    eax = esi;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3);
    edx = 0x2u;
    eax = esi;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x44u, 1, 0x8u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x180u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_4668b1;
    ecx = 0x1du;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_local_write(&env, -60, 4, ecx);
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, ebx);
L_4668b1:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    env.stack[env.sp++] = 0x4479f0u;
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
    eax = lift_load(&env, 0u, 0x4f872eu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    env.stack[env.sp++] = eax;
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8734u, 2)) & 0xffffu);
    env.stack[env.sp++] = eax;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f872cu, 2)) & 0xffffu);
    edx = 0x50e522u;
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    ecx = lift_load(&env, 0u, 0x4f872au, 4);
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
    ebx = lift_load(&env, 0u, 0x540018u, 4);
    env.stack[env.sp++] = eax;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    eax = esi;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3);
    edx = 0x2u;
    eax = esi;
    eax = lift_call(&env, 0x4ac7b0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x44u, 1, 0x8u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x4u);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, esi);
L_466936:
    eax = 0x15cu;
    edi = 0x5u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -48, 4, edi);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_466961;
    edx = 0x1fu;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_local_write(&env, -60, 4, edx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, ecx);
L_466961:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    eax = lift_load(&env, 0u, 0x4f85b0u, 4);
    ebx = lift_load(&env, 0u, 0x533d20u, 4);
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    env.stack[env.sp++] = 0x0u;
    edx = lift_local_read(&env, -48, 4);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    eax = lift_load(&env, 0u, 0x4f85b4u, 4);
    lift_local_write(&env, -40, 4, edx);
    edx = lift_load(&env, 0u, 0x4f85acu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    edx = lift_local_read(&env, -42, 4);
    lift_local_write(&env, -28, 4, eax);
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    ebx = lift_local_read(&env, -30, 4);
    eax = esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x544a18u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0);
    edx = lift_load(&env, 0u, 0x4fbf1cu, 4);
    eax = esi;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0);
    eax = esi;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x4eu, 1, 0x0u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x48u, 2, 0xffd8u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_466a14;
    ecx = 0x21u;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, ebx, ebx, &fl);
        ebx = r;
    }
    lift_local_write(&env, -60, 4, ecx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, ebx);
L_466a14:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    eax = lift_load(&env, 0u, 0x4f85c0u, 4);
    edx = lift_load(&env, 0u, 0x4f85b8u, 4);
    ecx = lift_load(&env, 0u, 0x4f85bcu, 4);
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    edx = lift_local_read(&env, -48, 4);
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    eax = lift_load(&env, 0u, 0x4f85c4u, 4);
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    lift_local_write(&env, -40, 4, edx);
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    edx = lift_local_read(&env, -42, 4);
    {
        uint32_t r = lift_add(32, eax, edi, &fl);
        eax = r;
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    lift_local_write(&env, -28, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    ebx = lift_local_read(&env, -30, 4);
    eax = esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ebx = r;
    }
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x544a18u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0);
    edx = lift_load(&env, 0u, 0x4fbf20u, 4);
    eax = esi;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0);
    eax = esi;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    lift_store(&env, esi, 0x95u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x4eu, 1, 0x0u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x48u, 2, 0xffd8u);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_466ac7;
    ebx = 0x23u;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, esi, esi, &fl);
        esi = r;
    }
    lift_local_write(&env, -60, 4, ebx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, esi);
L_466ac7:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    eax = lift_load(&env, 0u, 0x4f85b0u, 4);
    edx = lift_load(&env, 0u, 0x533d20u, 4);
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    env.stack[env.sp++] = 0x0u;
    eax = lift_load(&env, 0u, 0x4f85b4u, 4);
    lift_local_write(&env, -40, 4, edx);
    edx = lift_load(&env, 0u, 0x4f85acu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    env.stack[env.sp++] = 0x0u;
    lift_local_write(&env, -28, 4, edx);
    eax = esi;
    ebx = lift_local_read(&env, -30, 4);
    edx = lift_local_read(&env, -42, 4);
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
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x544a18u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0);
    edx = lift_load(&env, 0u, 0x4fbf1cu, 4);
    eax = esi;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0);
    eax = esi;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x0u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x4eu, 1, 0x5au);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    eax = 0x15cu;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_466b6d;
    edx = 0x25u;
    lift_local_write(&env, -52, 4, eax);
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    lift_local_write(&env, -60, 4, edx);
    eax = lift_call(&env, 0x4abd70u, eax, edx, ebx, ecx, 0);
    lift_local_write(&env, -60, 4, ecx);
L_466b6d:
    esi = eax;
    env.stack[env.sp++] = 0x0u;
    eax = lift_load(&env, 0u, 0x4f85c0u, 4);
    edx = lift_load(&env, 0u, 0x4f85b8u, 4);
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    env.stack[env.sp++] = 0x0u;
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    env.stack[env.sp++] = 0x0u;
    eax = lift_load(&env, 0u, 0x4f85c4u, 4);
    lift_local_write(&env, -40, 4, edx);
    edx = lift_load(&env, 0u, 0x4f85bcu, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    {
        uint32_t r = lift_add(32, edx, eax, &fl);
        edx = r;
    }
    env.stack[env.sp++] = 0x0u;
    lift_local_write(&env, -28, 4, edx);
    eax = esi;
    ebx = lift_local_read(&env, -30, 4);
    edx = lift_local_read(&env, -42, 4);
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
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5);
    edx = 0x544a18u;
    eax = esi;
    eax = lift_call(&env, 0x4ac8d0u, eax, edx, ebx, ecx, 0);
    edx = lift_load(&env, 0u, 0x4fbf20u, 4);
    eax = esi;
    eax = lift_call(&env, 0x4ac710u, eax, edx, ebx, ecx, 0);
    eax = esi;
    eax = lift_call(&env, 0x4ac8a0u, eax, edx, ebx, ecx, 0);
    lift_store(&env, esi, 0x93u, 1, 0x1u);
    edx = esi;
    lift_store(&env, esi, 0x95u, 1, 0x0u);
    eax = 0x54671cu;
    lift_store(&env, esi, 0x4eu, 1, 0x5au);
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0);
    esi = lift_local_read(&env, -48, 4);
    ebx = lift_load(&env, 0u, 0x4fbed0u, 4);
    edx = lift_load(&env, 0u, 0x4f861cu, 4);
    eax = lift_load(&env, 0u, 0x4f8618u, 4);
    {
        uint32_t r = lift_add(32, edx, edi, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, esi, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x465a70u, eax, edx, ebx, ecx, 0);
    ebx = lift_load(&env, 0u, 0x4fbed8u, 4);
    edx = lift_load(&env, 0u, 0x4f8624u, 4);
    eax = lift_load(&env, 0u, 0x4f8620u, 4);
    {
        uint32_t r = lift_add(32, edx, edi, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, esi, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x465a70u, eax, edx, ebx, ecx, 0);
    ebx = lift_load(&env, 0u, 0x4fbee0u, 4);
    edx = lift_load(&env, 0u, 0x4f862cu, 4);
    eax = lift_load(&env, 0u, 0x4f8628u, 4);
    {
        uint32_t r = lift_add(32, edx, edi, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, esi, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x465a70u, eax, edx, ebx, ecx, 0);
    ebx = lift_load(&env, 0u, 0x4fbf00u, 4);
    edx = lift_load(&env, 0u, 0x4f864cu, 4);
    eax = lift_load(&env, 0u, 0x4f8648u, 4);
    {
        uint32_t r = lift_add(32, edx, edi, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, esi, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x465a70u, eax, edx, ebx, ecx, 0);
    ebx = lift_load(&env, 0u, 0x4fbf08u, 4);
    edx = lift_load(&env, 0u, 0x4f8654u, 4);
    eax = lift_load(&env, 0u, 0x4f8650u, 4);
    {
        uint32_t r = lift_add(32, edx, edi, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, esi, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x465a70u, eax, edx, ebx, ecx, 0);
    ebx = lift_load(&env, 0u, 0x4fbf10u, 4);
    edx = lift_load(&env, 0u, 0x4f865cu, 4);
    eax = lift_load(&env, 0u, 0x4f8658u, 4);
    {
        uint32_t r = lift_add(32, edx, edi, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, esi, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x465a70u, eax, edx, ebx, ecx, 0);
    ebx = lift_load(&env, 0u, 0x4fbed0u, 4);
    edx = lift_load(&env, 0u, 0x4f8634u, 4);
    eax = lift_load(&env, 0u, 0x4f8630u, 4);
    {
        uint32_t r = lift_add(32, edx, edi, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, esi, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x465a70u, eax, edx, ebx, ecx, 0);
    ebx = lift_load(&env, 0u, 0x4fbed8u, 4);
    edx = lift_load(&env, 0u, 0x4f863cu, 4);
    eax = lift_load(&env, 0u, 0x4f8638u, 4);
    {
        uint32_t r = lift_add(32, edx, edi, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, esi, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x465a70u, eax, edx, ebx, ecx, 0);
    ebx = lift_load(&env, 0u, 0x4fbee0u, 4);
    edx = lift_load(&env, 0u, 0x4f8644u, 4);
    eax = lift_load(&env, 0u, 0x4f8640u, 4);
    {
        uint32_t r = lift_add(32, edx, edi, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, eax, esi, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x465a70u, eax, edx, ebx, ecx, 0);
    eax = lift_local_read(&env, -72, 4);
    env.chain = eax;
    return env.failed ? 0u : eax;
L_466cf0:
    eax = lift_call(&env, 0x4b5400u, eax, edx, ebx, ecx, 0);
    goto L_465b5b;
L_466cfa:
    esi = ebx;
    goto L_465cac;
L_466d01:
    esi = ebx;
    goto L_4662b1;
L_466d08:
    {
        (void)lift_sub(32, ecx, 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4665f8;
    goto L_466936;
}
