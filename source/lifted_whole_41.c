/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_41.h"

uint32_t lifted_mixer_pcm8_stereo(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_MIXER_PCM8_STEREO_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_MIXER_PCM8_STEREO_STACK, 0, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
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
    edi = lift_load(&env, ebp, 0x8u, 4);
    ecx = lift_load(&env, ebp, 0xcu, 4);
    esi = lift_load(&env, ebp, 0x10u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x15u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x10u, &fl);
    }
    if (fl.cf)
        goto L_401764;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x78u, &fl);
    }
    if (fl.cf)
        goto L_40135c;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x88u, &fl);
    }
    if (fl.cf)
        goto L_4019e0;
    {
        (void)lift_sub(8, (eax & 0xffu), 0xf0u, &fl);
    }
    if (!fl.cf)
        goto L_401760;
L_40135c:
    lift_store(&env, 0u, 0x4f4010u, 4, ecx);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = lift_load(&env, esi, 0x4u, 4);
    edx = lift_load(&env, esi, 0x8u, 4);
    ebx = lift_load(&env, esi, 0x14u, 1);
    ecx = lift_load(&env, esi, 0x15u, 1);
    esi = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_imul(32, ecx, ebx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x8u, &fl);
        ecx = r;
    }
    ebx = ebx - ecx;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        ebx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        ecx = r;
    }
    ebx = ebx + lift_load(&env, 0u, 0x52f910u, 4);
    ecx = ecx + lift_load(&env, 0u, 0x52f910u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ebx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = ebp;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        eax = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        ebp = r;
    }
    esi = esi + eax;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x4f4014u, 4, eax);
    lift_store(&env, 0u, 0x4f4018u, 4, edx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    eax = lift_load(&env, 0u, 0x4f4010u, 4);
    edx = eax;
    eax = eax & 0xfu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        edx = r;
    }
    edi = (edi + (eax * 8u) + 0xffffff80u);
    lift_store(&env, 0u, 0x4f4010u, 4, edx);
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4016e6;
            case 1:
                goto L_4016b5;
            case 2:
                goto L_401684;
            case 3:
                goto L_401653;
            case 4:
                goto L_401622;
            case 5:
                goto L_4015f1;
            case 6:
                goto L_4015c0;
            case 7:
                goto L_40158f;
            case 8:
                goto L_40155e;
            case 9:
                goto L_40152d;
            case 10:
                goto L_4014fc;
            case 11:
                goto L_4014cb;
            case 12:
                goto L_40149a;
            case 13:
                goto L_401469;
            case 14:
                goto L_401438;
            case 15:
                goto L_401407;
            default:
                return 0u;
        }
    }
L_4013d8:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x0u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, edi, 0x0u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x4u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_401407:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x8u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0xcu, 4);
    lift_store(&env, edi, 0x8u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0xcu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_401438:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x10u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x14u, 4);
    lift_store(&env, edi, 0x10u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x14u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_401469:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x18u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x1cu, 4);
    lift_store(&env, edi, 0x18u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x1cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_40149a:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x20u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x24u, 4);
    lift_store(&env, edi, 0x20u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x24u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_4014cb:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x28u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x2cu, 4);
    lift_store(&env, edi, 0x28u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x2cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_4014fc:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x30u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x34u, 4);
    lift_store(&env, edi, 0x30u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x34u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_40152d:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x38u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x3cu, 4);
    lift_store(&env, edi, 0x38u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x3cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_40155e:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x40u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x44u, 4);
    lift_store(&env, edi, 0x40u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x44u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_40158f:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x48u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x4cu, 4);
    lift_store(&env, edi, 0x48u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x4cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_4015c0:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x50u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x54u, 4);
    lift_store(&env, edi, 0x50u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x54u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_4015f1:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x58u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x5cu, 4);
    lift_store(&env, edi, 0x58u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x5cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_401622:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x60u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x64u, 4);
    lift_store(&env, edi, 0x60u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x64u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_401653:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x68u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x6cu, 4);
    lift_store(&env, edi, 0x68u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x6cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_401684:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x70u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x74u, 4);
    lift_store(&env, edi, 0x70u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x74u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_4016b5:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x78u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x7cu, 4);
    lift_store(&env, edi, 0x78u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x7cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_4016e6:
    {
        uint32_t r = lift_add(32, edi, 0x80u, &fl);
        edi = r;
    }
    {
        uint32_t a = lift_load(&env, 0u, 0x4f4010u, 4);
        uint32_t r = lift_dec(32, a, &fl, 1);
        lift_store(&env, 0u, 0x4f4010u, 4, r);
    }
    if (fl.sf == fl.of)
        goto L_4013d8;
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    {
        uint32_t r = lift_sub(32, ebp, eax, &fl);
        ebp = r;
    }
    esi = esi - edx - fl.cf;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    {
        uint32_t r = lift_sub(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_shrd(32, a, esi, 0x14u, &fl);
        ebp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    lift_store(&env, esi, 0x4u, 4, ebp);
    lift_store(&env, esi, 0x17u, 1, (ebx & 0xffu));
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
        eax = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_401760:
    edi = edi + 0x4u;
L_401764:
    lift_store(&env, 0u, 0x4f4010u, 4, ecx);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, esi, 0x4u, 4);
    ebp = lift_load(&env, esi, 0x8u, 4);
    ebx = lift_load(&env, esi, 0x14u, 1);
    esi = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        ebx = r;
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = ecx;
    ebx = ebx + lift_load(&env, 0u, 0x52f910u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ebx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        ecx = r;
    }
    edx = ebp;
    esi = esi + eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        edx = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        ebp = r;
    }
    lift_store(&env, 0u, 0x4f4018u, 4, edx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + edx + fl.cf;
    eax = lift_load(&env, 0u, 0x4f4010u, 4);
    edx = eax;
    eax = eax & 0xfu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        edx = r;
    }
    edi = (edi + (eax * 8u) + 0xffffff80u);
    lift_store(&env, 0u, 0x4f4010u, 4, edx);
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_40196e;
            case 1:
                goto L_401953;
            case 2:
                goto L_401938;
            case 3:
                goto L_40191d;
            case 4:
                goto L_401902;
            case 5:
                goto L_4018e7;
            case 6:
                goto L_4018cc;
            case 7:
                goto L_4018b1;
            case 8:
                goto L_401896;
            case 9:
                goto L_40187b;
            case 10:
                goto L_401860;
            case 11:
                goto L_401845;
            case 12:
                goto L_40182a;
            case 13:
                goto L_40180f;
            case 14:
                goto L_4017f4;
            case 15:
                goto L_4017d9;
            default:
                return 0u;
        }
    }
L_4017c0:
    edx = lift_load(&env, edi, 0x0u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x0u, 4, eax);
L_4017d9:
    edx = lift_load(&env, edi, 0x8u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x8u, 4, eax);
L_4017f4:
    edx = lift_load(&env, edi, 0x10u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x10u, 4, eax);
L_40180f:
    edx = lift_load(&env, edi, 0x18u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x18u, 4, eax);
L_40182a:
    edx = lift_load(&env, edi, 0x20u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x20u, 4, eax);
L_401845:
    edx = lift_load(&env, edi, 0x28u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x28u, 4, eax);
L_401860:
    edx = lift_load(&env, edi, 0x30u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x30u, 4, eax);
L_40187b:
    edx = lift_load(&env, edi, 0x38u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x38u, 4, eax);
L_401896:
    edx = lift_load(&env, edi, 0x40u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x40u, 4, eax);
L_4018b1:
    edx = lift_load(&env, edi, 0x48u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x48u, 4, eax);
L_4018cc:
    edx = lift_load(&env, edi, 0x50u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x50u, 4, eax);
L_4018e7:
    edx = lift_load(&env, edi, 0x58u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x58u, 4, eax);
L_401902:
    edx = lift_load(&env, edi, 0x60u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x60u, 4, eax);
L_40191d:
    edx = lift_load(&env, edi, 0x68u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x68u, 4, eax);
L_401938:
    edx = lift_load(&env, edi, 0x70u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x70u, 4, eax);
L_401953:
    edx = lift_load(&env, edi, 0x78u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x78u, 4, eax);
L_40196e:
    {
        uint32_t r = lift_add(32, edi, 0x80u, &fl);
        edi = r;
    }
    {
        uint32_t a = lift_load(&env, 0u, 0x4f4010u, 4);
        uint32_t r = lift_dec(32, a, &fl, 1);
        lift_store(&env, 0u, 0x4f4010u, 4, r);
    }
    if (fl.sf == fl.of)
        goto L_4017c0;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    {
        uint32_t r = lift_sub(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi - eax - fl.cf;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    {
        uint32_t r = lift_sub(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shrd(32, a, esi, 0x14u, &fl);
        ecx = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    lift_store(&env, esi, 0x4u, 4, ecx);
    lift_store(&env, esi, 0x17u, 1, (ebx & 0xffu));
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
        eax = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4019e0:
    lift_store(&env, 0u, 0x4f4010u, 4, ecx);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, esi, 0x4u, 4);
    ebp = lift_load(&env, esi, 0x8u, 4);
    ebx = lift_load(&env, esi, 0x14u, 1);
    esi = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        ebx = r;
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = ecx;
    ebx = ebx + lift_load(&env, 0u, 0x52f910u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ebx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        ecx = r;
    }
    edx = ebp;
    esi = esi + eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        edx = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        ebp = r;
    }
    lift_store(&env, 0u, 0x4f4018u, 4, edx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + edx + fl.cf;
    eax = lift_load(&env, 0u, 0x4f4010u, 4);
    edx = eax;
    eax = eax & 0xfu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        edx = r;
    }
    edi = (edi + (eax * 8u) + 0xffffff80u);
    lift_store(&env, 0u, 0x4f4010u, 4, edx);
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_401c5e;
            case 1:
                goto L_401c3c;
            case 2:
                goto L_401c1a;
            case 3:
                goto L_401bf8;
            case 4:
                goto L_401bd6;
            case 5:
                goto L_401bb4;
            case 6:
                goto L_401b92;
            case 7:
                goto L_401b70;
            case 8:
                goto L_401b4e;
            case 9:
                goto L_401b2c;
            case 10:
                goto L_401b0a;
            case 11:
                goto L_401ae8;
            case 12:
                goto L_401ac6;
            case 13:
                goto L_401aa4;
            case 14:
                goto L_401a82;
            case 15:
                goto L_401a60;
            default:
                return 0u;
        }
    }
L_401a40:
    edx = lift_load(&env, edi, 0x0u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 4, edx);
    edx = lift_load(&env, edi, 0x4u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x4u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401a60:
    edx = lift_load(&env, edi, 0x8u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x8u, 4, edx);
    edx = lift_load(&env, edi, 0xcu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0xcu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401a82:
    edx = lift_load(&env, edi, 0x10u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x10u, 4, edx);
    edx = lift_load(&env, edi, 0x14u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x14u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401aa4:
    edx = lift_load(&env, edi, 0x18u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x18u, 4, edx);
    edx = lift_load(&env, edi, 0x1cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x1cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401ac6:
    edx = lift_load(&env, edi, 0x20u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x20u, 4, edx);
    edx = lift_load(&env, edi, 0x24u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x24u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401ae8:
    edx = lift_load(&env, edi, 0x28u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x28u, 4, edx);
    edx = lift_load(&env, edi, 0x2cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x2cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401b0a:
    edx = lift_load(&env, edi, 0x30u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x30u, 4, edx);
    edx = lift_load(&env, edi, 0x34u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x34u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401b2c:
    edx = lift_load(&env, edi, 0x38u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x38u, 4, edx);
    edx = lift_load(&env, edi, 0x3cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x3cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401b4e:
    edx = lift_load(&env, edi, 0x40u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x40u, 4, edx);
    edx = lift_load(&env, edi, 0x44u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x44u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401b70:
    edx = lift_load(&env, edi, 0x48u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x48u, 4, edx);
    edx = lift_load(&env, edi, 0x4cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x4cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401b92:
    edx = lift_load(&env, edi, 0x50u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x50u, 4, edx);
    edx = lift_load(&env, edi, 0x54u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x54u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401bb4:
    edx = lift_load(&env, edi, 0x58u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x58u, 4, edx);
    edx = lift_load(&env, edi, 0x5cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x5cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401bd6:
    edx = lift_load(&env, edi, 0x60u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x60u, 4, edx);
    edx = lift_load(&env, edi, 0x64u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x64u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401bf8:
    edx = lift_load(&env, edi, 0x68u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x68u, 4, edx);
    edx = lift_load(&env, edi, 0x6cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x6cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401c1a:
    edx = lift_load(&env, edi, 0x70u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x70u, 4, edx);
    edx = lift_load(&env, edi, 0x74u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x74u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401c3c:
    edx = lift_load(&env, edi, 0x78u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x0u, 1)) & 0xffu);
    lift_store(&env, edi, 0x78u, 4, edx);
    edx = lift_load(&env, edi, 0x7cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x7cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_401c5e:
    {
        uint32_t r = lift_add(32, edi, 0x80u, &fl);
        edi = r;
    }
    {
        uint32_t a = lift_load(&env, 0u, 0x4f4010u, 4);
        uint32_t r = lift_dec(32, a, &fl, 1);
        lift_store(&env, 0u, 0x4f4010u, 4, r);
    }
    if (fl.sf == fl.of)
        goto L_401a40;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    {
        uint32_t r = lift_sub(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi - eax - fl.cf;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    {
        uint32_t r = lift_sub(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shrd(32, a, esi, 0x14u, &fl);
        ecx = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    lift_store(&env, esi, 0x4u, 4, ecx);
    lift_store(&env, esi, 0x17u, 1, (ebx & 0xffu));
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
        eax = v;
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

uint32_t lifted_mixer_pcm16_stereo(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_MIXER_PCM16_STEREO_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_MIXER_PCM16_STEREO_STACK, 0, entry);
    {
        uint32_t v = ebp;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = esp;
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
    edi = lift_load(&env, ebp, 0x8u, 4);
    ecx = lift_load(&env, ebp, 0xcu, 4);
    esi = lift_load(&env, ebp, 0x10u, 4);
    eax = (eax & 0xffffff00u) | ((lift_load(&env, esi, 0x15u, 1)) & 0xffu);
    {
        (void)lift_sub(8, (eax & 0xffu), 0x10u, &fl);
    }
    if (fl.cf)
        goto L_4030ac;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x78u, &fl);
    }
    if (fl.cf)
        goto L_402c4c;
    {
        (void)lift_sub(8, (eax & 0xffu), 0x88u, &fl);
    }
    if (fl.cf)
        goto L_403380;
    {
        (void)lift_sub(8, (eax & 0xffu), 0xf0u, &fl);
    }
    if (!fl.cf)
        goto L_4030a8;
L_402c4c:
    lift_store(&env, 0u, 0x4f4010u, 4, ecx);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebp = lift_load(&env, esi, 0x4u, 4);
    edx = lift_load(&env, esi, 0x8u, 4);
    ebx = lift_load(&env, esi, 0x14u, 1);
    ecx = lift_load(&env, esi, 0x15u, 1);
    esi = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        esi = r;
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    {
        uint32_t r = lift_imul(32, ecx, ebx, &fl);
        ecx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x8u, &fl);
        ecx = r;
    }
    ebx = ebx - ecx;
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        ebx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        ecx = r;
    }
    ebx = ebx + lift_load(&env, 0u, 0x52f910u, 4);
    ecx = ecx + lift_load(&env, 0u, 0x52f910u, 4);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ebx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ecx = r;
    }
    eax = ebp;
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        eax = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        ebp = r;
    }
    esi = esi + eax;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        edx = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        eax = r;
    }
    lift_store(&env, 0u, 0x4f4014u, 4, eax);
    lift_store(&env, 0u, 0x4f4018u, 4, edx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
    eax = lift_load(&env, 0u, 0x4f4010u, 4);
    edx = eax;
    eax = eax & 0xfu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        edx = r;
    }
    edi = (edi + (eax * 8u) + 0xffffff80u);
    lift_store(&env, 0u, 0x4f4010u, 4, edx);
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_40302e;
            case 1:
                goto L_402ff8;
            case 2:
                goto L_402fc2;
            case 3:
                goto L_402f8c;
            case 4:
                goto L_402f56;
            case 5:
                goto L_402f20;
            case 6:
                goto L_402eea;
            case 7:
                goto L_402eb4;
            case 8:
                goto L_402e7e;
            case 9:
                goto L_402e48;
            case 10:
                goto L_402e12;
            case 11:
                goto L_402ddc;
            case 12:
                goto L_402da6;
            case 13:
                goto L_402d70;
            case 14:
                goto L_402d3a;
            case 15:
                goto L_402d04;
            default:
                return 0u;
        }
    }
L_402cd0:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x0u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, edi, 0x0u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x4u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402d04:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x8u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0xcu, 4);
    lift_store(&env, edi, 0x8u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0xcu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402d3a:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x10u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x14u, 4);
    lift_store(&env, edi, 0x10u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x14u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402d70:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x18u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x1cu, 4);
    lift_store(&env, edi, 0x18u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x1cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402da6:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x20u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x24u, 4);
    lift_store(&env, edi, 0x20u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x24u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402ddc:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x28u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x2cu, 4);
    lift_store(&env, edi, 0x28u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x2cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402e12:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x30u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x34u, 4);
    lift_store(&env, edi, 0x30u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x34u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402e48:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x38u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x3cu, 4);
    lift_store(&env, edi, 0x38u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x3cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402e7e:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x40u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x44u, 4);
    lift_store(&env, edi, 0x40u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x44u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402eb4:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x48u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x4cu, 4);
    lift_store(&env, edi, 0x48u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x4cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402eea:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x50u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x54u, 4);
    lift_store(&env, edi, 0x50u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x54u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402f20:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x58u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x5cu, 4);
    lift_store(&env, edi, 0x58u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x5cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402f56:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x60u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x64u, 4);
    lift_store(&env, edi, 0x60u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x64u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402f8c:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x68u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x6cu, 4);
    lift_store(&env, edi, 0x68u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x6cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402fc2:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x70u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x74u, 4);
    lift_store(&env, edi, 0x70u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x74u, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_402ff8:
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = lift_load(&env, edi, 0x78u, 4);
    eax = eax + edx;
    edx = lift_load(&env, edi, 0x7cu, 4);
    lift_store(&env, edi, 0x78u, 4, eax);
    eax = lift_load(&env, 0u, (ecx * 4u) + 0x0u, 4);
    eax = eax + edx;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x7cu, 4, eax);
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    {
        uint32_t r = lift_add(32, ebp, eax, &fl);
        ebp = r;
    }
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    ecx = (ecx & 0xffffff00u) | (((ebx & 0xffu)) & 0xffu);
L_40302e:
    {
        uint32_t r = lift_add(32, edi, 0x80u, &fl);
        edi = r;
    }
    {
        uint32_t a = lift_load(&env, 0u, 0x4f4010u, 4);
        uint32_t r = lift_dec(32, a, &fl, 1);
        lift_store(&env, 0u, 0x4f4010u, 4, r);
    }
    if (fl.sf == fl.of)
        goto L_402cd0;
    eax = lift_load(&env, 0u, 0x4f4014u, 4);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    {
        uint32_t r = lift_sub(32, ebp, eax, &fl);
        ebp = r;
    }
    esi = esi - edx - fl.cf;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    {
        uint32_t r = lift_sub(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_shrd(32, a, esi, 0x14u, &fl);
        ebp = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    lift_store(&env, esi, 0x4u, 4, ebp);
    lift_store(&env, esi, 0x17u, 1, (ebx & 0xffu));
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
        eax = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4030a8:
    edi = edi + 0x4u;
L_4030ac:
    lift_store(&env, 0u, 0x4f4010u, 4, ecx);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, esi, 0x4u, 4);
    ebp = lift_load(&env, esi, 0x8u, 4);
    ebx = lift_load(&env, esi, 0x14u, 1);
    esi = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        esi = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        ebx = r;
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = ecx;
    ebx = ebx + lift_load(&env, 0u, 0x52f910u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ebx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        ecx = r;
    }
    edx = ebp;
    esi = esi + eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        edx = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        ebp = r;
    }
    lift_store(&env, 0u, 0x4f4018u, 4, edx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + edx + fl.cf;
    eax = lift_load(&env, 0u, 0x4f4010u, 4);
    edx = eax;
    eax = eax & 0xfu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        edx = r;
    }
    edi = (edi + (eax * 8u) + 0xffffff80u);
    lift_store(&env, 0u, 0x4f4010u, 4, edx);
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_40330e;
            case 1:
                goto L_4032ee;
            case 2:
                goto L_4032ce;
            case 3:
                goto L_4032ae;
            case 4:
                goto L_40328e;
            case 5:
                goto L_40326e;
            case 6:
                goto L_40324e;
            case 7:
                goto L_40322e;
            case 8:
                goto L_40320e;
            case 9:
                goto L_4031ee;
            case 10:
                goto L_4031ce;
            case 11:
                goto L_4031ae;
            case 12:
                goto L_40318e;
            case 13:
                goto L_40316e;
            case 14:
                goto L_40314e;
            case 15:
                goto L_40312e;
            default:
                return 0u;
        }
    }
L_403110:
    edx = lift_load(&env, edi, 0x0u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x0u, 4, eax);
L_40312e:
    edx = lift_load(&env, edi, 0x8u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x8u, 4, eax);
L_40314e:
    edx = lift_load(&env, edi, 0x10u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x10u, 4, eax);
L_40316e:
    edx = lift_load(&env, edi, 0x18u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x18u, 4, eax);
L_40318e:
    edx = lift_load(&env, edi, 0x20u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x20u, 4, eax);
L_4031ae:
    edx = lift_load(&env, edi, 0x28u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x28u, 4, eax);
L_4031ce:
    edx = lift_load(&env, edi, 0x30u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x30u, 4, eax);
L_4031ee:
    edx = lift_load(&env, edi, 0x38u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x38u, 4, eax);
L_40320e:
    edx = lift_load(&env, edi, 0x40u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x40u, 4, eax);
L_40322e:
    edx = lift_load(&env, edi, 0x48u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x48u, 4, eax);
L_40324e:
    edx = lift_load(&env, edi, 0x50u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x50u, 4, eax);
L_40326e:
    edx = lift_load(&env, edi, 0x58u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x58u, 4, eax);
L_40328e:
    edx = lift_load(&env, edi, 0x60u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x60u, 4, eax);
L_4032ae:
    edx = lift_load(&env, edi, 0x68u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x68u, 4, eax);
L_4032ce:
    edx = lift_load(&env, edi, 0x70u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x70u, 4, eax);
L_4032ee:
    edx = lift_load(&env, edi, 0x78u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    eax = eax + edx;
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    edx = lift_load(&env, 0u, 0x4f4018u, 4);
    esi = esi + edx + fl.cf;
    lift_store(&env, edi, 0x78u, 4, eax);
L_40330e:
    {
        uint32_t r = lift_add(32, edi, 0x80u, &fl);
        edi = r;
    }
    {
        uint32_t a = lift_load(&env, 0u, 0x4f4010u, 4);
        uint32_t r = lift_dec(32, a, &fl, 1);
        lift_store(&env, 0u, 0x4f4010u, 4, r);
    }
    if (fl.sf == fl.of)
        goto L_403110;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    {
        uint32_t r = lift_sub(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi - eax - fl.cf;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    {
        uint32_t r = lift_sub(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shrd(32, a, esi, 0x14u, &fl);
        ecx = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    lift_store(&env, esi, 0x4u, 4, ecx);
    lift_store(&env, esi, 0x17u, 1, (ebx & 0xffu));
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
        eax = v;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_403380:
    lift_store(&env, 0u, 0x4f4010u, 4, ecx);
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ecx = lift_load(&env, esi, 0x4u, 4);
    ebp = lift_load(&env, esi, 0x8u, 4);
    ebx = lift_load(&env, esi, 0x14u, 1);
    esi = lift_load(&env, esi, 0x0u, 4);
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        esi = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shl(32, a, 0xau, &fl);
        ebx = r;
    }
    {
        uint32_t v = esi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = ecx;
    ebx = ebx + lift_load(&env, 0u, 0x52f910u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x2u, &fl);
        ebx = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        ecx = r;
    }
    edx = ebp;
    esi = esi + eax;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0xcu, &fl);
        edx = r;
    }
    {
        uint32_t a = ebp;
        uint32_t r = lift_shl(32, a, 0x14u, &fl);
        ebp = r;
    }
    lift_store(&env, 0u, 0x4f4018u, 4, edx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + edx + fl.cf;
    eax = lift_load(&env, 0u, 0x4f4010u, 4);
    edx = eax;
    eax = eax & 0xfu;
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x4u, &fl);
        edx = r;
    }
    edi = (edi + (eax * 8u) + 0xffffff80u);
    lift_store(&env, 0u, 0x4f4010u, 4, edx);
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_403656;
            case 1:
                goto L_40362f;
            case 2:
                goto L_403608;
            case 3:
                goto L_4035e1;
            case 4:
                goto L_4035ba;
            case 5:
                goto L_403593;
            case 6:
                goto L_40356c;
            case 7:
                goto L_403545;
            case 8:
                goto L_40351e;
            case 9:
                goto L_4034f7;
            case 10:
                goto L_4034d0;
            case 11:
                goto L_4034a9;
            case 12:
                goto L_403482;
            case 13:
                goto L_40345b;
            case 14:
                goto L_403434;
            case 15:
                goto L_40340d;
            default:
                return 0u;
        }
    }
L_4033e8:
    edx = lift_load(&env, edi, 0x0u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x0u, 4, edx);
    edx = lift_load(&env, edi, 0x4u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x4u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_40340d:
    edx = lift_load(&env, edi, 0x8u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x8u, 4, edx);
    edx = lift_load(&env, edi, 0xcu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0xcu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_403434:
    edx = lift_load(&env, edi, 0x10u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x10u, 4, edx);
    edx = lift_load(&env, edi, 0x14u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x14u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_40345b:
    edx = lift_load(&env, edi, 0x18u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x18u, 4, edx);
    edx = lift_load(&env, edi, 0x1cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x1cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_403482:
    edx = lift_load(&env, edi, 0x20u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x20u, 4, edx);
    edx = lift_load(&env, edi, 0x24u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x24u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_4034a9:
    edx = lift_load(&env, edi, 0x28u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x28u, 4, edx);
    edx = lift_load(&env, edi, 0x2cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x2cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_4034d0:
    edx = lift_load(&env, edi, 0x30u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x30u, 4, edx);
    edx = lift_load(&env, edi, 0x34u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x34u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_4034f7:
    edx = lift_load(&env, edi, 0x38u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x38u, 4, edx);
    edx = lift_load(&env, edi, 0x3cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x3cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_40351e:
    edx = lift_load(&env, edi, 0x40u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x40u, 4, edx);
    edx = lift_load(&env, edi, 0x44u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x44u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_403545:
    edx = lift_load(&env, edi, 0x48u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x48u, 4, edx);
    edx = lift_load(&env, edi, 0x4cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x4cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_40356c:
    edx = lift_load(&env, edi, 0x50u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x50u, 4, edx);
    edx = lift_load(&env, edi, 0x54u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x54u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_403593:
    edx = lift_load(&env, edi, 0x58u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x58u, 4, edx);
    edx = lift_load(&env, edi, 0x5cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x5cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_4035ba:
    edx = lift_load(&env, edi, 0x60u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x60u, 4, edx);
    edx = lift_load(&env, edi, 0x64u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x64u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_4035e1:
    edx = lift_load(&env, edi, 0x68u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x68u, 4, edx);
    edx = lift_load(&env, edi, 0x6cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x6cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_403608:
    edx = lift_load(&env, edi, 0x70u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x70u, 4, edx);
    edx = lift_load(&env, edi, 0x74u, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x74u, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_40362f:
    edx = lift_load(&env, edi, 0x78u, 4);
    eax = lift_load(&env, 0u, (ebx * 4u) + 0x0u, 4);
    edx = edx + eax;
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, 0u, (esi * 2u) + 0x1u, 1)) & 0xffu);
    lift_store(&env, edi, 0x78u, 4, edx);
    edx = lift_load(&env, edi, 0x7cu, 4);
    edx = edx + eax;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    lift_store(&env, edi, 0x7cu, 4, edx);
    {
        uint32_t r = lift_add(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi + eax + fl.cf;
L_403656:
    {
        uint32_t r = lift_add(32, edi, 0x80u, &fl);
        edi = r;
    }
    {
        uint32_t a = lift_load(&env, 0u, 0x4f4010u, 4);
        uint32_t r = lift_dec(32, a, &fl, 1);
        lift_store(&env, 0u, 0x4f4010u, 4, r);
    }
    if (fl.sf == fl.of)
        goto L_4033e8;
    eax = lift_load(&env, 0u, 0x4f4018u, 4);
    {
        uint32_t r = lift_sub(32, ecx, ebp, &fl);
        ecx = r;
    }
    esi = esi - eax - fl.cf;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        eax = v;
    }
    {
        uint32_t r = lift_sub(32, esi, eax, &fl);
        esi = r;
    }
    {
        uint32_t a = ecx;
        uint32_t r = lift_shrd(32, a, esi, 0x14u, &fl);
        ecx = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        esi = v;
    }
    lift_store(&env, esi, 0x4u, 4, ecx);
    lift_store(&env, esi, 0x17u, 1, (ebx & 0xffu));
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
        eax = v;
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
