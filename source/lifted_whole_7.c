/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_7.h"

uint32_t lifted_f4eccb9(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4ECCB9_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4ECCB9_STACK, 0, entry);
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
    edi = eax;
    esi = edx;
    lift_store(&env, ebp, 0xffffffdcu, 4, ebx);
    lift_store(&env, edx, 0x14u, 4, 0x0u);
    eax = (eax & 0xffff0000u) | ((lift_load(&env, eax, 0x8u, 2)) & 0xffffu);
    lift_store(&env, ebp, 0xffffffd8u, 2, (eax & 0xffffu));
    eax = lift_load(&env, edi, 0x4u, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, eax);
    eax = lift_load(&env, edi, 0x0u, 4);
    lift_store(&env, ebp, 0xffffffd0u, 4, eax);
    {
        (void)lift_and(8, lift_load(&env, ebp, 0xffffffd9u, 1), 0x80u, &fl);
    }
    if (fl.zf)
        goto L_4eccf3;
    lift_store(&env, edx, 0x14u, 4, 0xffffffffu);
L_4eccf3:
    lift_store(&env, ebp, 0xffffffd9u, 1, lift_load(&env, ebp, 0xffffffd9u, 1) & 0x7fu);
    lift_store(&env, esi, 0x1cu, 4, 0x0u);
    lift_store(&env, esi, 0x20u, 4, 0x0u);
    lift_store(&env, esi, 0x24u, 4, 0x0u);
    eax = (ebp + 0xffffffd0u);
    lift_store(&env, esi, 0x28u, 4, 0x0u);
    edi = edi ^ edi;
    lift_store(&env, esi, 0x18u, 4, 0x0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4edf7fu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x4u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_4ece51;
    {
        uint32_t i = eax;
        switch (i)
        {
            case 0:
                goto L_4ecd35;
            case 1:
                goto L_4ecd71;
            case 2:
                goto L_4ecd43;
            case 3:
                goto L_4ecd61;
            case 4:
                goto L_4ecd35;
            default:
                return 0u;
        }
    }
L_4ecd35:
    lift_store(&env, esi, 0x14u, 4, 0x0u);
L_4ecd3c:
    ecx = ecx ^ ecx;
    goto L_4ece51;
L_4ecd43:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0x0u, 1, 0x6eu);
    lift_store(&env, eax, 0x1u, 1, 0x61u);
    lift_store(&env, eax, 0x2u, 1, 0x6eu);
L_4ecd51:
    lift_store(&env, eax, 0x3u, 1, 0x0u);
    lift_store(&env, esi, 0x1cu, 4, 0x3u);
    goto L_4ed08e;
L_4ecd61:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    lift_store(&env, eax, 0x0u, 1, 0x69u);
    lift_store(&env, eax, 0x1u, 1, 0x6eu);
    lift_store(&env, eax, 0x2u, 1, 0x66u);
    goto L_4ecd51;
L_4ecd71:
    ecx = ecx ^ ecx;
    ecx = (ecx & 0xffff0000u) | ((lift_load(&env, ebp, 0xffffffd8u, 2)) & 0xffffu);
    ecx = ecx - 0x3ffeu;
    {
        uint32_t r = lift_imul(32, ecx, 0x7597u, &fl);
        edx = r;
    }
    ebx = 0x186a0u;
    eax = edx;
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1fu, &fl);
        edx = r;
    }
    lift_idiv1(32, ebx, &eax, &edx, &fl);
    ecx = (eax + 0xfffffffcu);
    {
        (void)lift_and(32, ecx, ecx, &fl);
    }
    if (fl.zf)
        goto L_4ece51;
    if (fl.sf == fl.of)
        goto L_4ecdab;
    ecx = 0u - ecx;
    ecx = ecx + 0x3u;
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) & 0xfcu) & 0xffu);
    ecx = 0u - ecx;
    goto L_4ece45;
L_4ecdab:
    edx = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(16, (edx & 0xffffu), 0x4019u, &fl);
    }
    if (fl.cf)
        goto L_4ecd3c;
    if (!fl.zf)
        goto L_4ecdc4;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd4u, 4), 0xbebc2000u, &fl);
    }
    if (fl.cf)
        goto L_4ecd3c;
L_4ecdc4:
    eax = lift_load(&env, ebp, 0xffffffd8u, 4);
    {
        (void)lift_sub(16, (eax & 0xffffu), 0x4034u, &fl);
    }
    if (fl.cf)
        goto L_4ecde9;
    if (!fl.zf)
        goto L_4ece42;
    ebx = lift_load(&env, ebp, 0xffffffd4u, 4);
    {
        (void)lift_sub(32, ebx, 0x8e1bc9bfu, &fl);
    }
    if (fl.cf)
        goto L_4ecde9;
    if (!fl.zf)
        goto L_4ece42;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffd0u, 4), 0x4000000u, &fl);
    }
    if (!fl.cf)
        goto L_4ece42;
L_4ecde9:
    ebx = 0x4019u;
    edx = (ebp + 0xffffffacu);
    eax = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffb4u, 2, (ebx & 0xffffu));
    ebx = 0xbebc2000u;
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffffb0u, 4, ebx);
    ebx = (ebp + 0xffffffc4u);
    lift_store(&env, ebp, 0xffffffacu, 4, ecx);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4edd24u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffc4u);
    edx = (ebp + 0xffffffc4u);
    ebx = (ebp + 0xffffffacu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ee025u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ee094u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffacu);
    eax = (ebp + 0xffffffc4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4edb48u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = (ebp + 0xffffffd0u);
    edx = (ebp + 0xffffffacu);
    eax = (ebp + 0xffffffd0u);
    ecx = 0x8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ee0dcu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4ece51;
L_4ece42:
    ecx = (ecx & 0xffffff00u) | (((ecx & 0xffu) & 0xfcu) & 0xffu);
L_4ece45:
    edx = ecx;
    eax = (ebp + 0xffffffd0u);
    edx = 0u - edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ecc60u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ece51:
    {
        (void)lift_and(8, lift_load(&env, esi, 0x8u, 1), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ece6d;
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax + ecx;
    eax = eax + 0xau;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
    eax = lift_load(&env, esi, 0x4u, 4);
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ece75;
    lift_store(&env, ebp, 0xffffffecu, 4, lift_load(&env, ebp, 0xffffffecu, 4) + eax);
    goto L_4ece75;
L_4ece6d:
    eax = lift_load(&env, esi, 0x0u, 4);
    eax = eax + 0x7u;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_4ece75:
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, esi, 0x8u, 1)) & 0xffu);
    eax = 0xfu;
    {
        (void)lift_and(8, (ebx & 0xffu), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4ece87;
    eax = 0x14u;
L_4ece87:
    {
        (void)lift_and(8, lift_load(&env, esi, 0x8u, 1), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4ece8f;
    eax = eax + eax;
L_4ece8f:
    ebx = lift_load(&env, ebp, 0xffffffecu, 4);
    eax = eax + 0x4u;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ece9c;
    lift_store(&env, ebp, 0xffffffecu, 4, eax);
L_4ece9c:
    lift_store(&env, ebp, 0xffffff6cu, 1, 0x30u);
    eax = (eax & 0xffff00ffu) | (((((eax >> 8) & 0xffu) ^ ((eax >> 8) & 0xffu)) & 0xffu) << 8);
    lift_store(&env, ebp, 0xffffff6du, 1, ((eax >> 8) & 0xffu));
    eax = (ebp + 0xffffff6du);
    lift_store(&env, ebp, 0xffffffe0u, 4, eax);
    eax = eax ^ eax;
    lift_store(&env, ebp, 0xffffffe8u, 4, eax);
L_4eceb9:
    edx = lift_load(&env, ebp, 0xffffffecu, 4);
    {
        (void)lift_and(32, edx, edx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ecf8e;
    ebx = (edx + 0xfffffff8u);
    lift_store(&env, ebp, 0xffffffecu, 4, ebx);
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf)
        goto L_4ecf22;
    {
        (void)lift_and(16, lift_load(&env, ebp, 0xffffffd8u, 2), 0x7fffu, &fl);
    }
    if (fl.zf)
        goto L_4ecf8e;
    eax = (ebp + 0xffffffd0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ee025u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edi = eax;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ecf22;
    edx = (ebp + 0xffffffb8u);
    ebx = (ebp + 0xffffffd0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ee094u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = (ebp + 0xffffffb8u);
    eax = (ebp + 0xffffffd0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ee0dcu, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x4019u;
    ebx = 0xbebc2000u;
    edx = (ebp + 0xffffffb8u);
    lift_store(&env, ebp, 0xffffffc0u, 2, (eax & 0xffffu));
    lift_store(&env, ebp, 0xffffffbcu, 4, ebx);
    eax = eax ^ eax;
    ebx = (ebp + 0xffffffd0u);
    lift_store(&env, ebp, 0xffffffb8u, 4, eax);
    eax = (ebp + 0xffffffd0u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4edb48u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ecf22:
    ebx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = edi;
    edx = lift_load(&env, ebp, 0xffffffe8u, 4);
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
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ecf33u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4ecf78;
L_4ecf78:
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
    eax = (eax & 0xffffff00u) | ((0x0u) & 0xffu);
    lift_store(&env, ebx, 0x0u, 1, (eax & 0xffu));
    lift_store(&env, ebp, 0xffffffe0u, 4, ebx);
    edx = edx + 0x8u;
    edi = edi ^ edi;
    lift_store(&env, ebp, 0xffffffe8u, 4, edx);
    goto L_4eceb9;
L_4ecf8e:
    eax = lift_load(&env, ebp, 0xffffffe8u, 4);
    edx = (ebp + 0xffffff6du);
    ecx = ecx + 0x7u;
L_4ecf9a:
    {
        (void)lift_sub(8, lift_load(&env, edx, 0x0u, 1), 0x30u, &fl);
    }
    if (!fl.zf)
        goto L_4ecfa4;
    eax = eax - 1u;
    ecx = ecx - 1u;
    edx = edx + 1u;
    goto L_4ecf9a;
L_4ecfa4:
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, esi, 0x8u, 1)) & 0xffu) << 8);
    edi = lift_load(&env, esi, 0x0u, 4);
    {
        (void)lift_and(8, ((ebx >> 8) & 0xffu), 0x2u, &fl);
    }
    if (fl.zf)
        goto L_4ecfb8;
    ecx = ecx + lift_load(&env, esi, 0x4u, 4);
    ebx = (ecx + 0x1u);
    edi = edi + ebx;
    goto L_4ecfcd;
L_4ecfb8:
    {
        (void)lift_and(8, ((ebx >> 8) & 0xffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_4ecfcd;
    ebx = lift_load(&env, esi, 0x4u, 4);
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ecfc7;
    edi = edi + 1u;
    goto L_4ecfc9;
L_4ecfc7:
    edi = edi + ebx;
L_4ecfc9:
    ecx = ecx + 1u;
    ecx = ecx - lift_load(&env, esi, 0x4u, 4);
L_4ecfcd:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed03a;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ecfdb;
    edi = eax;
L_4ecfdb:
    ebx = 0xfu;
    {
        (void)lift_and(8, lift_load(&env, esi, 0x8u, 1), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_4ecfeb;
    ebx = 0x14u;
L_4ecfeb:
    {
        (void)lift_and(8, lift_load(&env, esi, 0x8u, 1), 0x40u, &fl);
    }
    if (fl.zf)
        goto L_4ecff3;
    ebx = ebx + ebx;
L_4ecff3:
    {
        (void)lift_sub(32, edi, ebx, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ecffa;
    edi = (ebx + 0x1u);
L_4ecffa:
    lift_store(&env, ebp, 0xfffffff0u, 1, 0x30u);
    {
        (void)lift_sub(32, eax, edi, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_4ed00c;
    {
        (void)lift_sub(8, lift_load(&env, edx, edi + 0x0u, 1), 0x35u, &fl);
    }
    if (fl.cf)
        goto L_4ed00c;
    lift_store(&env, ebp, 0xfffffff0u, 1, 0x39u);
L_4ed00c:
    lift_store(&env, ebp, 0xffffffe4u, 4, edi);
    eax = (edi + edx);
L_4ed012:
    ebx = lift_load(&env, ebp, 0xffffffe4u, 4);
    ebx = ebx - 1u;
    eax = eax - 1u;
    lift_store(&env, ebp, 0xffffffe4u, 4, ebx);
    ebx = (ebx & 0xffffff00u) | ((lift_load(&env, eax, 0x0u, 1)) & 0xffu);
    ebx = (ebx & 0xffff00ffu) | (((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu) << 8);
    {
        (void)lift_sub(8, (ebx & 0xffu), ((ebx >> 8) & 0xffu), &fl);
    }
    if (!fl.zf)
        goto L_4ed026;
    edi = edi - 1u;
    goto L_4ed012;
L_4ed026:
    {
        (void)lift_sub(8, ((ebx >> 8) & 0xffu), 0x39u, &fl);
    }
    if (!fl.zf)
        goto L_4ed031;
    ebx = (ebx & 0xffff00ffu) | ((((ebx & 0xffu)) & 0xffu) << 8);
    ebx = (ebx & 0xffff00ffu) | (((((ebx >> 8) & 0xffu) + 1u) & 0xffu) << 8);
    lift_store(&env, eax, 0x0u, 1, ((ebx >> 8) & 0xffu));
L_4ed031:
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x0u, &fl);
    }
    if (fl.sf == fl.of)
        goto L_4ed03a;
    edx = edx - 1u;
    edi = edi + 1u;
    ecx = ecx + 1u;
L_4ed03a:
    {
        (void)lift_and(32, edi, edi, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4ed056;
    edi = 0x1u;
    eax = (eax & 0xffffff00u) | ((0x30u) & 0xffu);
    ecx = ecx ^ ecx;
    lift_store(&env, ebp, 0xffffff6cu, 1, (eax & 0xffu));
    edx = (ebp + 0xffffff6cu);
    lift_store(&env, esi, 0x14u, 4, ecx);
L_4ed056:
    eax = (eax & 0xffff00ffu) | (((lift_load(&env, esi, 0x8u, 1)) & 0xffu) << 8);
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x2u, &fl);
    }
    if (!fl.zf)
        goto L_4ed072;
    {
        (void)lift_and(8, ((eax >> 8) & 0xffu), 0x4u, &fl);
    }
    if (fl.zf)
        goto L_4ed081;
    {
        (void)lift_sub(32, ecx, 0xfffffffcu, &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed06c;
    {
        (void)lift_sub(32, ecx, lift_load(&env, esi, 0x0u, 4), &fl);
    }
    if (fl.sf != fl.of)
        goto L_4ed072;
L_4ed06c:
    {
        (void)lift_and(8, lift_load(&env, esi, 0x8u, 1), 0x8u, &fl);
    }
    if (fl.zf)
        goto L_4ed081;
L_4ed072:
    ebx = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    eax = esi;
    ebx = edi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ed096u, eax, edx, ebx, ecx, 1, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp += 4u;
    goto L_4ed08e;
L_4ed081:
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    {
        uint32_t v = eax;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = edi;
    eax = esi;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ed2b5u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4ed08e:
    esp = (ebp + 0xfffffff4u);
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
        ebp = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
}

uint32_t lifted_f4ee160(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F4EE160_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F4EE160_STACK, 0, entry);
    {
        uint32_t v = edi;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    edi = 0x80000000u;
    goto L_4ee1e8;
L_4ee16b:
    esi = (esi & 0xffff0000u) | (((esi & 0xffffu) - 1u) & 0xffffu);
    {
        uint32_t r = lift_add(32, esi, 0x10000u, &fl);
        esi = r;
    }
    if (fl.cf)
        goto L_4ee179;
    if (fl.of)
        goto L_4ee179;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ee179:
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4ee1b1;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4ee1b1;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4ee1b1;
    {
        (void)lift_sub(32, ecx, edx, &fl);
    }
    if (!fl.zf)
        goto L_4ee1b1;
    eax = esi;
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        eax = r;
    }
    {
        (void)lift_sub(16, (esi & 0xffffu), (eax & 0xffffu), &fl);
    }
    eax = ebx;
    if (!fl.zf)
        goto L_4ee1a5;
    {
        uint32_t r = lift_or(32, edi, edi, &fl);
        edi = r;
    }
    if (!fl.zf)
        goto L_4ee1a9;
    goto L_4ee1af;
L_4ee1a5:
    {
        uint32_t r = lift_or(32, edi, edi, &fl);
        edi = r;
    }
    if (!fl.zf)
        goto L_4ee1af;
L_4ee1a9:
    {
        uint32_t a = edx;
        uint32_t r = lift_sar(32, a, 0x1u, &fl);
        edx = r;
    }
    esi = (esi & 0xffff0000u) | ((0xffffu) & 0xffffu);
L_4ee1af:
    goto L_4ee1c6;
L_4ee1b1:
    {
        (void)lift_sub(32, edx, ecx, &fl);
    }
    if (!fl.zf)
        goto L_4ee1b7;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
L_4ee1b7:
    if (!fl.cf && !fl.zf)
        goto L_4ee1c6;
    if (!fl.zf)
        goto L_4ee1bd;
    {
        uint32_t r = lift_or(32, edi, edi, &fl);
        edi = r;
    }
L_4ee1bd:
    if (fl.zf)
        goto L_4ee1c6;
    edx = ecx;
    eax = ebx;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
L_4ee1c6:
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ee1c8:
    edx = ecx;
    eax = ebx;
    esi = esi - 0x10000u;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4ee1e0;
    {
        (void)lift_sub(32, edx, 0x80000000u, &fl);
    }
    if (!fl.zf)
        goto L_4ee1e0;
    esi = esi ^ edi;
L_4ee1e0:
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ee1e8:
    {
        uint32_t r = lift_add(16, (esi & 0xffffu), 0x1u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.cf)
        goto L_4ee16b;
    if (fl.of)
        goto L_4ee16b;
    {
        uint32_t r = lift_add(32, esi, 0xffffu, &fl);
        esi = r;
    }
    if (fl.cf)
        goto L_4ee1c8;
    if (fl.of)
        goto L_4ee1c8;
    esi = esi - 0x10000u;
    esi = esi ^ edi;
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        edi = v;
    }
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    if (!fl.zf)
        goto L_4ee22e;
    {
        uint32_t r = lift_or(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.zf)
        goto L_4ee22e;
    {
        uint32_t r = lift_add(16, (esi & 0xffffu), (esi & 0xffffu), &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (!fl.zf)
        goto L_4ee22b;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x10u, &fl);
        esi = r;
    }
    eax = ebx;
    edx = ecx;
    esi = esi + esi;
    ebx = (ebx & 0xffff0000u) | (((ebx & 0xffffu) | (esi & 0xffffu)) & 0xffffu);
    {
        uint32_t r = lift_or(32, ebx, edx, &fl);
        ebx = r;
    }
    if (fl.zf)
        goto L_4ee22a;
    {
        uint32_t a = esi;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        esi = r;
    }
L_4ee22a:
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ee22b:
    {
        uint32_t a = (esi & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        esi = (esi & 0xffff0000u) | ((r) & 0xffffu);
    }
L_4ee22e:
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (!fl.zf)
        goto L_4ee23f;
    {
        uint32_t r = lift_or(32, ebx, ebx, &fl);
        ebx = r;
    }
    if (!fl.zf)
        goto L_4ee23f;
    {
        (void)lift_and(32, esi, 0x7fff0000u, &fl);
    }
    if (!fl.zf)
        goto L_4ee23f;
    vertrix_lift_edx = edx;
    vertrix_lift_fl = fl;
    return env.failed ? 0u : eax;
L_4ee23f:
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
    ebp = ecx;
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
    ecx = (ecx & 0xffff0000u) | (((ecx & 0xffffu) + (edi & 0xffffu)) & 0xffffu);
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
        uint32_t r = lift_sub(16, (ecx & 0xffffu), (edi & 0xffffu), &fl);
        ecx = (ecx & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4ee28e;
    if (!fl.cf)
        goto L_4ee27a;
    ebp = edi;
    ecx = (ecx & 0xffff0000u) | ((0u - (ecx & 0xffffu)) & 0xffffu);
    {
        uint32_t t = ebx;
        ebx = eax;
        eax = t;
    }
    {
        uint32_t t = edx;
        edx = esi;
        esi = t;
    }
L_4ee27a:
    {
        (void)lift_sub(16, (ecx & 0xffffu), 0x40u, &fl);
    }
    if (fl.cf || fl.zf)
        goto L_4ee28e;
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t a = (ebp & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        ebp = (ebp & 0xffff0000u) | ((r) & 0xffffu);
    }
    eax = ebx;
    edx = esi;
    esi = ebp;
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
L_4ee28e:
    ecx = (ecx & 0xffff00ffu) | (((0x0u) & 0xffu) << 8);
    {
        uint32_t r = lift_or(32, ecx, ecx, &fl);
        ecx = r;
    }
    if (!fl.sf)
        goto L_4ee2a3;
    ecx = (ecx & 0xffff00ffu) | (((0xffu) & 0xffu) << 8);
    esi = 0u - esi;
    {
        uint32_t a = ebx;
        uint32_t r = lift_sub(32, 0, a, &fl);
        ebx = r;
    }
    esi = esi - 0x0u - fl.cf;
    ebp = ebp ^ 0x80000000u;
L_4ee2a3:
    edi = edi - edi;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x0u, &fl);
    }
    if (fl.zf)
        goto L_4ee2d6;
    {
        uint32_t v = ebx;
        esp -= 4u;
        lift_store(&env, esp, 0u, 4, v);
    }
    ebx = ebx - ebx;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x20u, &fl);
    }
    if (fl.cf)
        goto L_4ee2c8;
    {
        uint32_t r = lift_or(32, eax, eax, &fl);
        eax = r;
    }
    ebx = (ebx & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    edi = ebx;
    ebx = ebx - ebx;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_4ee2c4;
    edi = edi | edx;
    edx = edx - edx;
L_4ee2c4:
    eax = edx;
    edx = edx - edx;
L_4ee2c8:
    {
        uint32_t a = ebx;
        uint32_t r = lift_shrd(32, a, eax, (ecx & 0xffu), &fl);
        ebx = r;
    }
    edi = edi | ebx;
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
    {
        uint32_t v = lift_load(&env, esp, 0u, 4);
        esp += 4u;
        ebx = v;
    }
L_4ee2d6:
    {
        uint32_t r = lift_add(32, eax, ebx, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, esi, &fl);
        edx = r;
    }
    {
        uint32_t r = lift_adc(8, ((ecx >> 8) & 0xffu), 0x0u, &fl);
        ecx = (ecx & 0xffff00ffu) | (((r) & 0xffu) << 8);
    }
    if (!fl.sf)
        goto L_4ee307;
    {
        (void)lift_sub(8, (ecx & 0xffu), 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_4ee2f8;
    {
        (void)lift_and(32, edi, 0x7fffffffu, &fl);
    }
    ebx = (ebx & 0xffffff00u) | (((!fl.zf) ? 1u : 0u) & 0xffu);
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    {
        uint32_t r = lift_adc(32, eax, 0x0u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, 0x0u, &fl);
        edx = r;
    }
    ecx = (ecx & 0xffff00ffu) | (((((ecx >> 8) & 0xffu) + 0x0u + fl.cf) & 0xffu) << 8);
L_4ee2f8:
    edx = 0u - edx;
    {
        uint32_t a = eax;
        uint32_t r = lift_sub(32, 0, a, &fl);
        eax = r;
    }
    edx = edx - 0x0u - fl.cf;
    ecx = (ecx & 0xffff00ffu) | (((0x0u) & 0xffu) << 8);
    ebp = ebp ^ 0x80000000u;
L_4ee307:
    ebx = eax;
    ebx = (ebx & 0xffffff00u) | (((ebx & 0xffu) | ((ecx >> 8) & 0xffu)) & 0xffu);
    {
        uint32_t r = lift_or(32, ebx, edx, &fl);
        ebx = r;
    }
    if (fl.zf)
        goto L_4ee356;
    {
        uint32_t r = lift_or(16, (ebp & 0xffffu), (ebp & 0xffffu), &fl);
        ebp = (ebp & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4ee358;
    {
        (void)lift_sub(8, ((ecx >> 8) & 0xffu), 0x0u, &fl);
    }
    if (!fl.zf)
        goto L_4ee327;
    {
        uint32_t a = edi;
        uint32_t r = lift_rol(32, a, 0x1u, &fl);
        edi = r;
    }
    {
        uint32_t a = edi;
        uint32_t r = lift_ror(32, a, 0x1u, &fl);
        edi = r;
    }
L_4ee31d:
    {
        uint32_t a = (ebp & 0xffffu);
        uint32_t r = lift_dec(16, a, &fl, 1);
        ebp = (ebp & 0xffff0000u) | ((r) & 0xffffu);
    }
    if (fl.zf)
        goto L_4ee358;
    {
        uint32_t r = lift_adc(32, eax, eax, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, edx, &fl);
        edx = r;
    }
    if (!fl.cf)
        goto L_4ee31d;
L_4ee327:
    ebp = (ebp & 0xffff0000u) | (((ebp & 0xffffu) + 1u) & 0xffffu);
    {
        (void)lift_sub(16, (ebp & 0xffffu), 0x7fffu, &fl);
    }
    if (fl.zf)
        goto L_4ee362;
    fl.cf = 1;
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
    if (!fl.cf)
        goto L_4ee354;
    {
        uint32_t r = lift_add(32, edi, edi, &fl);
        edi = r;
    }
    if (!fl.zf)
        goto L_4ee33f;
    {
        uint32_t a = eax;
        uint32_t r = lift_ror(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = eax;
        uint32_t r = lift_rol(32, a, 0x1u, &fl);
        eax = r;
    }
L_4ee33f:
    {
        uint32_t r = lift_adc(32, eax, 0x0u, &fl);
        eax = r;
    }
    {
        uint32_t r = lift_adc(32, edx, 0x0u, &fl);
        edx = r;
    }
    if (!fl.cf)
        goto L_4ee354;
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
    ebp = (ebp & 0xffff0000u) | (((ebp & 0xffffu) + 1u) & 0xffffu);
    {
        (void)lift_sub(16, (ebp & 0xffffu), 0x7fffu, &fl);
    }
    if (fl.zf)
        goto L_4ee362;
L_4ee354:
    goto L_4ee358;
L_4ee356:
    ebp = ebx;
L_4ee358:
    {
        uint32_t r = lift_add(32, ebp, ebp, &fl);
        ebp = r;
    }
    {
        uint32_t a = (ebp & 0xffffu);
        uint32_t r = lift_rcr(16, a, 0x1u, &fl);
        ebp = (ebp & 0xffff0000u) | ((r) & 0xffffu);
    }
    esi = ebp;
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
L_4ee362:
    ebp = (ebp & 0xffff0000u) | ((0x7fffu) & 0xffffu);
    eax = eax - eax;
    edx = 0x80000000u;
    goto L_4ee358;
}
