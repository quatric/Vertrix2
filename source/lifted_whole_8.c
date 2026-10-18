/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_8.h"

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
