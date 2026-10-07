/* Lifted from the original routine at 0x46b810 by tools/lift.py: every instruction of the original
 * is translated in order (registers, stack, flags and gotos) and every unrecovered callee goes
 * through the call boundary with the registers and stack arguments the original holds there.
 * Verified against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_hud_decor.h"

uint32_t lifted_hud_decor(const VertrixCalls *calls, const VertrixFactoryServices *services,
                          const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_HUD_DECOR_STACK + 4 + 4 * 0 + 4];
    LiftEnv env;
    LiftFlags fl = {0, 0, 0, 0, 0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t ebp = entry->ebp;
    uint32_t esp = entry->esp;
    (void)fl;
    (void)eax;
    (void)edx;
    (void)ebx;
    (void)ecx;
    (void)esi;
    (void)edi;
    (void)ebp;
    lift_begin(&env, calls, services, globals, stack, LIFTED_HUD_DECOR_STACK, 0, entry);
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
        uint32_t r = lift_sub(32, esp, 0x2cu, &fl);
        esp = r;
    }
    lift_store(&env, ebp, 0xffffffdcu, 4, eax);
    esi = edx;
    ebx = lift_load(&env, 0u, 0x5466c4u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_xor(32, ecx, ecx, &fl);
        ecx = r;
    }
    eax = lift_load(&env, 0u, 0x4f888au, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f888eu, 4);
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = lift_load(&env, 0u, 0x4fbf28u, 4);
    edx = lift_load(&env, 0u, 0x4f8896u, 4);
    eax = lift_load(&env, 0u, 0x4f8892u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = 0x1u;
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = 0x2u;
    edx = lift_load(&env, 0u, 0x4f889eu, 4);
    eax = lift_load(&env, 0u, 0x4f889au, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x4fbf2cu, 4);
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x3u;
    ebx = lift_load(&env, 0u, 0x4fbf2cu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f88a6u, 4);
    eax = lift_load(&env, 0u, 0x4f88a2u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x6au;
    ebx = lift_load(&env, 0u, 0x4fbfdcu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f893au, 4);
    eax = lift_load(&env, 0u, 0x4f8936u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x6bu;
    ebx = lift_load(&env, 0u, 0x4fbfdcu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f894au, 4);
    eax = lift_load(&env, 0u, 0x4f8946u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x6cu;
    ebx = lift_load(&env, 0u, 0x4fbfd8u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8932u, 4);
    eax = lift_load(&env, 0u, 0x4f892eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x6du;
    ebx = lift_load(&env, 0u, 0x4fbfd8u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8942u, 4);
    eax = lift_load(&env, 0u, 0x4f893eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x4u;
    ebx = lift_load(&env, 0u, 0x4fbf30u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f88bau, 4);
    eax = lift_load(&env, 0u, 0x4f88b6u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x5u;
    ebx = lift_load(&env, 0u, 0x4fbf38u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f88cau, 4);
    eax = lift_load(&env, 0u, 0x4f88c6u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x6u;
    ebx = lift_load(&env, 0u, 0x4fbf34u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f88b2u, 4);
    eax = lift_load(&env, 0u, 0x4f88aeu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x7u;
    ebx = lift_load(&env, 0u, 0x4fbf3cu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f88c2u, 4);
    eax = lift_load(&env, 0u, 0x4f88beu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x58u;
    ebx = lift_load(&env, 0u, 0x4fbf38u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f88dau, 4);
    eax = lift_load(&env, 0u, 0x4f88d6u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x59u;
    ebx = lift_load(&env, 0u, 0x4fbf30u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f88eau, 4);
    eax = lift_load(&env, 0u, 0x4f88e6u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x5au;
    ebx = lift_load(&env, 0u, 0x4fbf3cu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f88d2u, 4);
    eax = lift_load(&env, 0u, 0x4f88ceu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x5bu;
    ebx = lift_load(&env, 0u, 0x4fbf34u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f88e2u, 4);
    eax = lift_load(&env, 0u, 0x4f88deu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x62u;
    ebx = lift_load(&env, 0u, 0x4fbfd0u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f88fau, 4);
    eax = lift_load(&env, 0u, 0x4f88f6u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x63u;
    ebx = lift_load(&env, 0u, 0x4fbfd0u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f892au, 4);
    eax = lift_load(&env, 0u, 0x4f8926u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x64u;
    ebx = lift_load(&env, 0u, 0x4fbfc8u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f88f2u, 4);
    eax = lift_load(&env, 0u, 0x4f88eeu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x65u;
    ebx = lift_load(&env, 0u, 0x4fbfc8u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8922u, 4);
    eax = lift_load(&env, 0u, 0x4f891eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x66u;
    ebx = lift_load(&env, 0u, 0x4fbfd4u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f890au, 4);
    eax = lift_load(&env, 0u, 0x4f8906u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x67u;
    ebx = lift_load(&env, 0u, 0x4fbfd4u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f891au, 4);
    eax = lift_load(&env, 0u, 0x4f8916u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x68u;
    ebx = lift_load(&env, 0u, 0x4fbfccu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8902u, 4);
    eax = lift_load(&env, 0u, 0x4f88feu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x69u;
    ebx = lift_load(&env, 0u, 0x4fbfccu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8912u, 4);
    eax = lift_load(&env, 0u, 0x4f890eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x8u;
    ebx = lift_load(&env, 0u, 0x4fbf44u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8952u, 4);
    eax = lift_load(&env, 0u, 0x4f894eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x9u;
    ebx = lift_load(&env, 0u, 0x4fbf44u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f895au, 4);
    eax = lift_load(&env, 0u, 0x4f8956u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0xau;
    ebx = lift_load(&env, 0u, 0x4fbf40u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8962u, 4);
    eax = lift_load(&env, 0u, 0x4f895eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0xbu;
    ebx = lift_load(&env, 0u, 0x4fbf40u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f896au, 4);
    eax = lift_load(&env, 0u, 0x4f8966u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x10u;
    ebx = lift_load(&env, 0u, 0x4fbf5cu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f89b2u, 4);
    eax = lift_load(&env, 0u, 0x4f89aeu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x11u;
    ebx = lift_load(&env, 0u, 0x4fbf5cu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f89bau, 4);
    eax = lift_load(&env, 0u, 0x4f89b6u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x12u;
    ebx = lift_load(&env, 0u, 0x4fbf58u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f89cau, 4);
    eax = lift_load(&env, 0u, 0x4f89c6u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x13u;
    ebx = lift_load(&env, 0u, 0x4fbf58u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f89d2u, 4);
    eax = lift_load(&env, 0u, 0x4f89ceu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x14u;
    ebx = lift_load(&env, 0u, 0x4fbf50u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f89eau, 4);
    eax = lift_load(&env, 0u, 0x4f89e6u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x15u;
    ebx = lift_load(&env, 0u, 0x4fbf54u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f89f2u, 4);
    eax = lift_load(&env, 0u, 0x4f89eeu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x16u;
    ebx = lift_load(&env, 0u, 0x4fbf48u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f89dau, 4);
    eax = lift_load(&env, 0u, 0x4f89d6u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x17u;
    ebx = lift_load(&env, 0u, 0x4fbf4cu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f89e2u, 4);
    eax = lift_load(&env, 0u, 0x4f89deu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x18u;
    ebx = lift_load(&env, 0u, 0x4fbf60u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8a1au, 4);
    eax = lift_load(&env, 0u, 0x4f8a16u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x19u;
    ebx = lift_load(&env, 0u, 0x4fbf60u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8a22u, 4);
    eax = lift_load(&env, 0u, 0x4f8a1eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x1au;
    ebx = lift_load(&env, 0u, 0x4fbf60u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8a2au, 4);
    eax = lift_load(&env, 0u, 0x4f8a26u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x1bu;
    ebx = lift_load(&env, 0u, 0x4fbf60u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8a32u, 4);
    eax = lift_load(&env, 0u, 0x4f8a2eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x1cu;
    ebx = lift_load(&env, 0u, 0x4fbf6cu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8aa2u, 4);
    eax = lift_load(&env, 0u, 0x4f8a9eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x1du;
    ebx = lift_load(&env, 0u, 0x4fbf6cu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8aaau, 4);
    eax = lift_load(&env, 0u, 0x4f8aa6u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x1eu;
    ebx = lift_load(&env, 0u, 0x4fbf70u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8ab2u, 4);
    eax = lift_load(&env, 0u, 0x4f8aaeu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x1fu;
    ebx = lift_load(&env, 0u, 0x4fbf70u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8abau, 4);
    eax = lift_load(&env, 0u, 0x4f8ab6u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    lift_store(&env, ebp, 0xffffffe4u, 4, eax);
L_46be31:
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    eax = edi;
    {
        uint32_t a = eax;
        uint32_t r = lift_sub(32, 0, a, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x3u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_46be3f:
    ebx = 0x1u;
    {
        (void)lift_sub(32, esi, 0xffffffffu, &fl);
    }
    if (fl.zf)
        goto L_46c441;
L_46be4d:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_46becc;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t r = lift_imul(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8accu, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8ac4u, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8ac8u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, edi, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x4fbf64u, 4);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8ac0u, 2)) & 0xffffu);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    ecx = 0x2au;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t r = lift_imul(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8accu, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8ac4u, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8ac8u, 2)) & 0xffffu);
    {
        uint32_t r = lift_imul(32, eax, edi, &fl);
        eax = r;
    }
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x4fbf68u, 4);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8ac0u, 2)) & 0xffffu);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    ecx = 0x2cu;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
L_46becc:
    ebx = 0x1u;
    {
        (void)lift_sub(32, esi, 0xffffffffu, &fl);
    }
    if (!fl.zf)
        goto L_46c45f;
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x532a6cu, 1)) & 0xffu);
    eax = lift_call(&env, 0x4178d0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.zf)
        goto L_46c45f;
L_46bef3:
    ecx = lift_load(&env, ebp, 0xffffffd4u, 4);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t a = edi;
        uint32_t r = lift_inc(32, a, &fl, 1);
        edi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ecx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffd4u, 4, ecx);
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    {
        (void)lift_sub(32, edi, 0x4u, &fl);
    }
    if (fl.cf)
        goto L_46be3f;
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    {
        (void)lift_sub(32, ebx, 0x7u, &fl);
    }
    if (fl.cf)
        goto L_46be31;
    edx = 0x20u;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_call(&env, 0x4126f0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_46bfdf;
    eax = 0x180u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46bf44;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
L_46bf44:
    edi = eax;
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
    eax = edi;
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
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8cc4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8cccu, 2), &fl);
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
    eax = lift_load(&env, 0u, 0x4f8cc2u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ebx = (ebx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8cc8u, 2)) & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8cc0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ecx = lift_load(&env, 0u, 0x4f8cbeu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x532a68u, 4);
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x4f9c07u, 4);
    {
        uint32_t r = lift_add(32, eax, 0x5345d4u, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = edi;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    edx = 0x20u;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = edi;
    lift_store(&env, ebp, 0xffffffc8u, 4, edi);
    eax = lift_call(&env, 0x4123d0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, edi, 0x44u, 1, 0x10u);
    {
        (void)lift_sub(32, esi, 0x20u, &fl);
    }
    if (!fl.zf)
        goto L_46bfd2;
    lift_store(&env, edi, 0x110u, 1, 0x1u);
L_46bfd2:
    edx = lift_load(&env, ebp, 0xffffffc8u, 4);
    eax = 0x54671cu;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
L_46bfdf:
    edx = 0x21u;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_call(&env, 0x4126f0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_46c0a3;
    eax = 0x180u;
    eax = lift_call(&env, 0x4ca000u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_46c008;
    eax = lift_call(&env, 0x4b6350u, eax, edx, ebx, ecx, 0, esp);
L_46c008:
    edi = eax;
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
    eax = edi;
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
    eax = lift_call(&env, 0x4adf20u, eax, edx, ebx, ecx, 5, esp);
    esp += 20u;
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8cd4u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8cdcu, 2), &fl);
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
    eax = lift_load(&env, 0u, 0x4f8cd2u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8cd8u, 2)) & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = (eax & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8cd0u, 2)) & 0xffffu);
    {
        uint32_t r = lift_add(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_dec(32, a, &fl, 1);
        eax = r;
    }
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    ebx = lift_load(&env, 0u, 0x4f9c07u, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, 0u, 0x532a6cu, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_sar(32, a, 0x18u, &fl);
        ebx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x2u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, 0u, 0x4f8cceu, 4);
    {
        uint32_t r = lift_add(32, eax, 0x5345d4u, &fl);
        eax = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        ecx = r;
    }
    edx = lift_load(&env, eax, 0x0u, 4);
    eax = edi;
    eax = lift_call(&env, 0x4b65d0u, eax, edx, ebx, ecx, 3, esp);
    esp += 12u;
    edx = 0x21u;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = edi;
    lift_store(&env, ebp, 0xffffffccu, 4, edi);
    eax = lift_call(&env, 0x4123d0u, eax, edx, ebx, ecx, 0, esp);
    lift_store(&env, edi, 0x44u, 1, 0x10u);
    {
        (void)lift_sub(32, esi, 0x21u, &fl);
    }
    if (!fl.zf)
        goto L_46c096;
    lift_store(&env, edi, 0x110u, 1, 0x1u);
L_46c096:
    edx = lift_load(&env, ebp, 0xffffffccu, 4);
    eax = 0x54671cu;
    eax = lift_call(&env, 0x4b5e70u, eax, edx, ebx, ecx, 0, esp);
L_46c0a3:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = 0x2eu;
    ebx = lift_load(&env, 0u, 0x4fbf84u, 4);
    edx = lift_load(&env, 0u, 0x4f8b5au, 4);
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
    eax = lift_load(&env, 0u, 0x4f8b56u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = 0x2fu;
    ebx = lift_load(&env, 0u, 0x4fbf88u, 4);
    eax = lift_load(&env, 0u, 0x4f8b5eu, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = lift_load(&env, 0u, 0x4f8b62u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = lift_load(&env, 0u, 0x4fbf8cu, 4);
    edx = lift_load(&env, 0u, 0x4f8b6au, 4);
    eax = lift_load(&env, 0u, 0x4f8b66u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = 0x30u;
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = 0x31u;
    edx = lift_load(&env, 0u, 0x4f8b72u, 4);
    eax = lift_load(&env, 0u, 0x4f8b6eu, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x4fbf8cu, 4);
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x5eu;
    ebx = lift_load(&env, 0u, 0x4fbf90u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8b6au, 4);
    eax = lift_load(&env, 0u, 0x4f8b66u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x5fu;
    ebx = lift_load(&env, 0u, 0x4fbf90u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8b72u, 4);
    eax = lift_load(&env, 0u, 0x4f8b6eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x32u;
    ebx = lift_load(&env, 0u, 0x4fbf94u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8b7au, 4);
    eax = lift_load(&env, 0u, 0x4f8b76u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x33u;
    ebx = lift_load(&env, 0u, 0x4fbf98u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8b82u, 4);
    eax = lift_load(&env, 0u, 0x4f8b7eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x5cu;
    ebx = lift_load(&env, 0u, 0x4fbf9cu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8b7au, 4);
    eax = lift_load(&env, 0u, 0x4f8b76u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x5du;
    ebx = lift_load(&env, 0u, 0x4fbf9cu, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8b82u, 4);
    eax = lift_load(&env, 0u, 0x4f8b7eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    eax = 0x34u;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
L_46c21a:
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    ebx = lift_load(&env, 0u, 0x4fbfa4u, 4);
    eax = lift_load(&env, edi, 0x4f8b86u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = lift_load(&env, edi, 0x4f8bb6u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = lift_load(&env, 0u, 0x4fbfa4u, 4);
    edx = lift_load(&env, edi, 0x4f8c16u, 4);
    eax = lift_load(&env, edi, 0x4f8be6u, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = lift_load(&env, ebp, 0xffffffe8u, 4);
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ebx = lift_load(&env, ebp, 0xffffffe8u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_inc(32, a, &fl, 1);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, edi, 0x4u, &fl);
        edi = r;
    }
    lift_store(&env, ebp, 0xffffffe8u, 4, ebx);
    {
        (void)lift_sub(32, edi, 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_46c21a;
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = 0x60u;
    ebx = lift_load(&env, 0u, 0x4fbfa0u, 4);
    edx = lift_load(&env, 0u, 0x4f8b7au, 4);
    eax = lift_load(&env, 0u, 0x4f8b76u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x61u;
    ebx = lift_load(&env, 0u, 0x4fbfa0u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8b82u, 4);
    eax = lift_load(&env, 0u, 0x4f8b7eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
    edx = 0x4fu;
    ecx = 0x4eu;
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
L_46c2ce:
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    edx = lift_load(&env, edi, 0x4f8c66u, 4);
    eax = lift_load(&env, edi, 0x4f8c5eu, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x4fbfb0u, 4);
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = lift_load(&env, ebp, 0xffffffc4u, 4);
    ebx = lift_load(&env, 0u, 0x4fbfb4u, 4);
    edx = lift_load(&env, edi, 0x4f8c76u, 4);
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
    eax = lift_load(&env, edi, 0x4f8c6eu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(32, edi, 0x4u, &fl);
        edi = r;
    }
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    edx = lift_load(&env, ebp, 0xffffffc4u, 4);
    ecx = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        uint32_t r = lift_add(32, edx, 0x2u, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_add(32, ecx, 0x2u, &fl);
        ecx = r;
    }
    lift_store(&env, ebp, 0xffffffc4u, 4, edx);
    lift_store(&env, ebp, 0xffffffd8u, 4, ecx);
    {
        (void)lift_sub(32, ecx, 0x52u, &fl);
    }
    if (!fl.zf)
        goto L_46c2ce;
    edi = 0x53u;
    lift_store(&env, ebp, 0xffffffe0u, 4, ecx);
    lift_store(&env, ebp, 0xffffffd0u, 4, edi);
    {
        uint32_t r = lift_xor(32, edi, edi, &fl);
        edi = r;
    }
L_46c33f:
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = lift_load(&env, ebp, 0xffffffe0u, 4);
    ebx = lift_load(&env, 0u, 0x4fbfb8u, 4);
    eax = lift_load(&env, edi, 0x4f8c7eu, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    edx = lift_load(&env, edi, 0x4f8c86u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = lift_load(&env, 0u, 0x4fbfb8u, 4);
    edx = lift_load(&env, edi, 0x4f8c96u, 4);
    eax = lift_load(&env, edi, 0x4f8c8eu, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, ebp, 0xffffffd0u, 4);
    {
        uint32_t r = lift_add(32, edi, 0x4u, &fl);
        edi = r;
    }
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ebx = lift_load(&env, ebp, 0xffffffd0u, 4);
    eax = lift_load(&env, ebp, 0xffffffe0u, 4);
    {
        uint32_t r = lift_add(32, ebx, 0x2u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_add(32, eax, 0x2u, &fl);
        eax = r;
    }
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    {
        (void)lift_sub(32, eax, 0x56u, &fl);
    }
    if (!fl.zf)
        goto L_46c33f;
    ecx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ebx = lift_load(&env, 0u, 0x4fbfbcu, 4);
    edx = lift_load(&env, 0u, 0x4f8ca2u, 4);
    eax = lift_load(&env, 0u, 0x4f8c9eu, 4);
    {
        uint32_t v = ecx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        edx = r;
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0x10u, &fl);
        eax = r;
    }
    ecx = 0x56u;
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    ecx = 0x57u;
    edx = lift_load(&env, 0u, 0x4f8caau, 4);
    eax = lift_load(&env, 0u, 0x4f8ca6u, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = lift_load(&env, 0u, 0x4fbfc0u, 4);
    edi = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x22u;
    ebx = lift_load(&env, 0u, 0x4fbfc4u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8cb2u, 4);
    eax = lift_load(&env, 0u, 0x4f8caeu, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    ecx = 0x23u;
    ebx = lift_load(&env, 0u, 0x4fbfc4u, 4);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edx = lift_load(&env, 0u, 0x4f8cbau, 4);
    eax = lift_load(&env, 0u, 0x4f8cb6u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
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
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
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
L_46c441:
    {
        uint32_t r = lift_xor(32, edx, edx, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_xor(32, eax, eax, &fl);
        eax = r;
    }
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, 0u, 0x532a68u, 1)) & 0xffu);
    eax = lift_call(&env, 0x4178d0u, eax, edx, ebx, ecx, 0, esp);
    {
        (void)lift_sub(32, eax, esi, &fl);
    }
    if (!fl.zf)
        goto L_46be4d;
    goto L_46becc;
L_46c45f:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_46bef3;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    edx = (edx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8adcu, 2)) & 0xffffu);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t r = lift_imul(32, eax, edx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8ad4u, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8ad8u, 2)) & 0xffffu);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t r = lift_imul(32, eax, ecx, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x4fbf64u, 4);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8ad0u, 2)) & 0xffffu);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    ecx = 0x2bu;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        uint32_t v = edx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_imul(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8adcu, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    {
        uint32_t r = lift_add(16, (eax & 0xffffu), lift_load(&env, 0u, 0x4f8ad4u, 2), &fl);
        eax = (eax & 0xffff0000u) | ((r) & 0xffffu);
    }
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8ad8u, 2)) & 0xffffu);
    edx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        uint32_t r = lift_imul(32, eax, ecx, &fl);
        eax = r;
    }
    ebx = lift_load(&env, 0u, 0x4fbf68u, 4);
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, 0u, 0x4f8ad0u, 2)) & 0xffffu);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_add(32, eax, ecx, &fl);
        eax = r;
    }
    ecx = 0x2du;
    eax = (uint32_t)(int32_t)(int16_t)(uint16_t)eax;
    eax = lift_call(&env, 0x471100u, eax, edx, ebx, ecx, 2, esp);
    esp += 8u;
    goto L_46bef3;
}
