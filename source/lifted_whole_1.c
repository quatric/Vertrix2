/* Routines lifted from the original by tools/lift.py (see docs/LIFTED.md), each verified
 * against the original by tools/verify_lifted.py. */
#include "lift_runtime.h"

#include "lifted_whole_1.h"

uint32_t lifted_font_maps_initialize(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_FONT_MAPS_INITIALIZE_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_FONT_MAPS_INITIALIZE_STACK, 0, entry);
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
    esp = esp - 0x88u;
    ecx = 0x541988u;
    ebx = 0x1eu;
    edx = 0x23u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff74u, 1, 0x41u);
L_43fc79:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff74u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_43fcac;
    lift_store(&env, ebp, 0xffffffd8u, 1, 0x30u);
L_43fc8a:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fcc8;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x1au;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd8u, 1, lift_load(&env, ebp, 0xffffffd8u, 1) + 1u);
    goto L_43fc8a;
L_43fcac:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x11u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x541988u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff74u, 1, lift_load(&env, ebp, 0xffffff74u, 1) + 1u);
    goto L_43fc79;
L_43fcc8:
    ebx = 0x1eu;
    edx = 0x23u;
    eax = ecx;
    ecx = 0x541b94u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 1, 0x41u);
L_43fce9:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd4u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fd0c;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x35u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x541b94u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 1, lift_load(&env, ebp, 0xffffffd4u, 1) + 1u);
    goto L_43fce9;
L_43fd0c:
    lift_store(&env, ebp, 0xffffffd0u, 1, 0x30u);
L_43fd10:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffd0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fd32;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx - 0xau;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd0u, 1, lift_load(&env, ebp, 0xffffffd0u, 1) + 1u);
    goto L_43fd10;
L_43fd32:
    ebx = 0x1eu;
    edx = 0x23u;
    eax = ecx;
    ecx = 0x541da0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffccu, 1, 0x41u);
L_43fd53:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffccu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fd76;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x35u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x541da0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffccu, 1, lift_load(&env, ebp, 0xffffffccu, 1) + 1u);
    goto L_43fd53;
L_43fd76:
    lift_store(&env, ebp, 0xffffffc8u, 1, 0x30u);
L_43fd7a:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffc8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fd9c;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x1au;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc8u, 1, lift_load(&env, ebp, 0xffffffc8u, 1) + 1u);
    goto L_43fd7a;
L_43fd9c:
    ebx = 0x1eu;
    edx = 0x23u;
    eax = ecx;
    ecx = 0x541facu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc4u, 1, 0x41u);
L_43fdbd:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffc4u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fde0;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x11u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x541facu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc4u, 1, lift_load(&env, ebp, 0xffffffc4u, 1) + 1u);
    goto L_43fdbd;
L_43fde0:
    lift_store(&env, ebp, 0xffffffc0u, 1, 0x30u);
L_43fde4:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffc0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fe06;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x1au;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffc0u, 1, lift_load(&env, ebp, 0xffffffc0u, 1) + 1u);
    goto L_43fde4;
L_43fe06:
    ebx = 0x1eu;
    edx = 0x1cu;
    eax = ecx;
    ecx = 0x5421b8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffbcu, 1, 0x41u);
L_43fe27:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffbcu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fe4a;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x35u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x5421b8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffbcu, 1, lift_load(&env, ebp, 0xffffffbcu, 1) + 1u);
    goto L_43fe27;
L_43fe4a:
    lift_store(&env, ebp, 0xffffffb8u, 1, 0x30u);
L_43fe4e:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffb8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fe70;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x24u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb8u, 1, lift_load(&env, ebp, 0xffffffb8u, 1) + 1u);
    goto L_43fe4e;
L_43fe70:
    ebx = 0x1eu;
    edx = 0x1cu;
    eax = ecx;
    ecx = 0x543a48u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 1, 0x41u);
L_43fe91:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffb4u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43feb4;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x35u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x543a48u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb4u, 1, lift_load(&env, ebp, 0xffffffb4u, 1) + 1u);
    goto L_43fe91;
L_43feb4:
    lift_store(&env, ebp, 0xffffffb0u, 1, 0x30u);
L_43feb8:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffb0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fedd;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x1d6u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffb0u, 1, lift_load(&env, ebp, 0xffffffb0u, 1) + 1u);
    goto L_43feb8;
L_43fedd:
    ebx = 0x1eu;
    edx = 0x1cu;
    eax = ecx;
    ecx = 0x543c54u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffacu, 1, 0x41u);
L_43fefe:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffacu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43ff21;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x35u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x543c54u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffacu, 1, lift_load(&env, ebp, 0xffffffacu, 1) + 1u);
    goto L_43fefe;
L_43ff21:
    lift_store(&env, ebp, 0xffffffa8u, 1, 0x30u);
L_43ff25:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43ff4a;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x1e0u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffa8u, 1, lift_load(&env, ebp, 0xffffffa8u, 1) + 1u);
    goto L_43ff25;
L_43ff4a:
    ebx = 0x1eu;
    edx = 0x1cu;
    eax = ecx;
    ecx = 0x543e60u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffa4u, 1, 0x41u);
L_43ff6b:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa4u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43ff8e;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax - 0x35u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x543e60u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffa4u, 1, lift_load(&env, ebp, 0xffffffa4u, 1) + 1u);
    goto L_43ff6b;
L_43ff8e:
    lift_store(&env, ebp, 0xffffffa0u, 1, 0x30u);
L_43ff92:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffa0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43ffb7;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x1eau;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffa0u, 1, lift_load(&env, ebp, 0xffffffa0u, 1) + 1u);
    goto L_43ff92;
L_43ffb7:
    ebx = 0xcu;
    edx = 0xdu;
    eax = ecx;
    ecx = 0x5423c4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f480u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff9cu, 1, 0x41u);
L_43ffd8:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff9cu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_43fffd;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x29u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x5423c4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff9cu, 1, lift_load(&env, ebp, 0xffffff9cu, 1) + 1u);
    goto L_43ffd8;
L_43fffd:
    lift_store(&env, ebp, 0xffffffe4u, 1, 0x30u);
L_440001:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440023;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x54u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe4u, 1, lift_load(&env, ebp, 0xffffffe4u, 1) + 1u);
    goto L_440001;
L_440023:
    ebx = 0x10u;
    edx = 0xeu;
    eax = ecx;
    ecx = 0x5425d0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f630u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 1, 0x30u);
L_440044:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440069;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x5eu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x5425d0u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe0u, 1, lift_load(&env, ebp, 0xffffffe0u, 1) + 1u);
    goto L_440044;
L_440069:
    lift_store(&env, ebp, 0xffffffdcu, 1, 0x41u);
L_44006d:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffdcu, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_44008f;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x57u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffdcu, 1, lift_load(&env, ebp, 0xffffffdcu, 1) + 1u);
    goto L_44006d;
L_44008f:
    edx = 0x6u;
    eax = 0x546538u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4877f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, eax, 0x8u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    edx = edx + edx;
    ebx = (edx + 0x1eu);
    edx = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t a = edx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        edx = r;
    }
    ecx = 0x5427dcu;
    edx = edx + edx;
    eax = ecx;
    edx = edx + 0x23u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff8cu, 1, 0x41u);
L_4400c2:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff8cu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4400e7;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x71u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x5427dcu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff8cu, 1, lift_load(&env, ebp, 0xffffff8cu, 1) + 1u);
    goto L_4400c2;
L_4400e7:
    lift_store(&env, ebp, 0xffffff88u, 1, 0x30u);
L_4400eb:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff88u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440110;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x9cu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff88u, 1, lift_load(&env, ebp, 0xffffff88u, 1) + 1u);
    goto L_4400eb;
L_440110:
    eax = ecx;
    edx = 0x9u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f550u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x546538u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4877f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, eax, 0x8u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    eax = eax + eax;
    ebx = ebx + ebx;
    edx = (eax + 0x23u);
    ebx = ebx + 0x1eu;
    eax = 0x5429e8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xe2u;
    edx = 0x47u;
    eax = 0x5429e8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xe3u;
    edx = 0x4fu;
    eax = 0x5429e8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x9u;
    eax = 0x546538u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4877f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = lift_load(&env, eax, 0x8u, 4);
    eax = lift_load(&env, eax, 0x4u, 4);
    {
        uint32_t a = eax;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        eax = r;
    }
    {
        uint32_t a = ebx;
        uint32_t r = lift_shr(32, a, 0x1u, &fl);
        ebx = r;
    }
    eax = eax + eax;
    ebx = ebx + ebx;
    edx = (eax + 0x23u);
    ebx = ebx + 0x1eu;
    eax = 0x542bf4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xe4u;
    edx = 0x56u;
    eax = 0x542bf4u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xe5u;
    edx = 0x53u;
    eax = 0x542bf4u;
    ecx = 0x542e00u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0xeu;
    edx = 0x12u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 1, 0x41u);
L_4401db:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff84u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440200;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0xb1u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x542e00u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff84u, 1, lift_load(&env, ebp, 0xffffff84u, 1) + 1u);
    goto L_4401db;
L_440200:
    lift_store(&env, ebp, 0xffffff80u, 1, 0x30u);
L_440204:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff80u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440229;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0xdcu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff80u, 1, lift_load(&env, ebp, 0xffffff80u, 1) + 1u);
    goto L_440204;
L_440229:
    ebx = 0xcu;
    edx = 0xdu;
    eax = ecx;
    ecx = 0x54300cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f710u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff7cu, 1, 0x41u);
L_44024d:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff7cu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440278;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0xe1u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x54300cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff7cu, 1, lift_load(&env, ebp, 0xffffff7cu, 1) + 1u);
    goto L_44024d;
L_440278:
    lift_store(&env, ebp, 0xffffff78u, 1, 0x30u);
L_44027f:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff78u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4402aa;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x10cu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff78u, 1, lift_load(&env, ebp, 0xffffff78u, 1) + 1u);
    goto L_44027f;
L_4402aa:
    ebx = 0xeu;
    edx = 0x12u;
    eax = ecx;
    ecx = 0x543218u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f7f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff98u, 1, 0x41u);
L_4402cb:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff98u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4402f0;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x111u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x543218u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff98u, 1, lift_load(&env, ebp, 0xffffff98u, 1) + 1u);
    goto L_4402cb;
L_4402f0:
    lift_store(&env, ebp, 0xffffff94u, 1, 0x30u);
L_4402f4:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff94u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440319;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x13cu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff94u, 1, lift_load(&env, ebp, 0xffffff94u, 1) + 1u);
    goto L_4402f4;
L_440319:
    ebx = 0xcu;
    edx = 0xdu;
    eax = ecx;
    ecx = 0x543424u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f8d0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff90u, 1, 0x41u);
L_44033a:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff90u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_44035f;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x141u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x543424u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff90u, 1, lift_load(&env, ebp, 0xffffff90u, 1) + 1u);
    goto L_44033a;
L_44035f:
    lift_store(&env, ebp, 0xffffff70u, 1, 0x30u);
L_440366:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff70u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440391;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x16cu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff70u, 1, lift_load(&env, ebp, 0xffffff70u, 1) + 1u);
    goto L_440366;
L_440391:
    ebx = 0xeu;
    edx = 0x12u;
    eax = ecx;
    ecx = 0x543630u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43f9b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff6cu, 1, 0x41u);
L_4403b5:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffff6cu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_4403e0;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x171u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x543630u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffff6cu, 1, lift_load(&env, ebp, 0xffffff6cu, 1) + 1u);
    goto L_4403b5;
L_4403e0:
    lift_store(&env, ebp, 0xfffffff0u, 1, 0x30u);
L_4403e4:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | ((lift_load(&env, ebp, 0xfffffff0u, 1)) & 0xffu);
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_440409;
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | (((eax & 0xffu)) & 0xffu);
    edx = edx + 0x19cu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(edx & 0xffffu);
    edx = eax;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xfffffff0u, 1, lift_load(&env, ebp, 0xfffffff0u, 1) + 1u);
    goto L_4403e4;
L_440409:
    ebx = 0xcu;
    edx = 0xdu;
    eax = ecx;
    ecx = 0x54383cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43fa90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffecu, 1, 0x41u);
L_44042a:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffecu, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x5au, &fl);
    }
    if (!fl.zf && fl.sf == fl.of)
        goto L_44044f;
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x1a1u;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = 0x54383cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffecu, 1, lift_load(&env, ebp, 0xffffffecu, 1) + 1u);
    goto L_44042a;
L_44044f:
    lift_store(&env, ebp, 0xffffffe8u, 1, 0x30u);
L_440453:
    edx = edx ^ edx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe8u, 1)) & 0xffu);
    {
        (void)lift_sub(32, edx, 0x39u, &fl);
    }
    if (fl.zf || fl.sf != fl.of)
        goto L_44046c;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x43fb70u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    esp = (ebp + 0xfffffff4u);
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
L_44046c:
    eax = eax ^ eax;
    eax = (eax & 0xffffff00u) | (((edx & 0xffu)) & 0xffu);
    eax = eax + 0x1ccu;
    ebx = (uint32_t)(int32_t)(int16_t)(uint16_t)(eax & 0xffffu);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x48abf0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffe8u, 1, lift_load(&env, ebp, 0xffffffe8u, 1) + 1u);
    goto L_440453;
}

uint32_t lifted_f444e00(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F444E00_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F444E00_STACK, 0, entry);
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
    esp = esp - 0x24u;
    ecx = eax;
    eax = (ebp + 0xffffffc8u);
    edx = 0x4ec1ecu;
    ebx = 0x515160u;
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
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    esi = 0x1u;
    edi = edi ^ edi;
L_444e3b:
    edx = (ebp + 0xffffffe4u);
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_444e6b;
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffe4u, 4), &fl);
    }
    if (!fl.zf)
        goto L_444fe3;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_444e6b:
    edx = lift_load(&env, ecx, 0x160u, 4);
    eax = (ebp + 0xffffffdcu);
    edx = lift_load(&env, edx, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_444f1e;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x1cu, &fl);
    }
    if (fl.zf)
        goto L_444e9c;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x56u, &fl);
    }
    if (!fl.zf)
        goto L_444f71;
L_444e9c:
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x444c80u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ecx, 0x52u, 1, 0x9u);
    edx = 0x50e16au;
    eax = lift_load(&env, ebp, 0xffffffdcu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ccfe0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (!fl.zf)
        goto L_444ed7;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4cd0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_444ed7:
    ebx = lift_load(&env, ecx, 0x184u, 4);
    edx = ecx;
    {
        (void)lift_and(32, ebx, ebx, &fl);
    }
    if (fl.zf)
        goto L_444ef5;
    eax = lift_load(&env, ecx, 0x160u, 4);
    eax = lift_load(&env, eax, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x184u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_444ef5:
    eax = 0x54d640u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4766b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffdcu);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_444f1e:
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x444c80u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    lift_store(&env, ecx, 0x52u, 1, 0x9u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4766b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffdcu);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_444f71:
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x5fu, &fl);
    }
    if (!fl.zf)
        goto L_444f93;
L_444f77:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_444f7e:
    eax = (ebp + 0xffffffdcu);
    edx = edi;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    goto L_444e3b;
L_444f93:
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x60u, &fl);
    }
    if (fl.zf)
        goto L_444fba;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x5cu, &fl);
    }
    if (fl.zf)
        goto L_444fc3;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x61u, &fl);
    }
    if (fl.zf)
        goto L_444fcc;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0xeu, &fl);
    }
    if (fl.zf)
        goto L_444fd5;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x65u, &fl);
    }
    if (!fl.zf)
        goto L_444f7e;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4af0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_444f7e;
L_444fba:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_444f7e;
L_444fc3:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_444f7e;
L_444fcc:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4630u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_444f7e;
L_444fd5:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4950u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_444f7e;
    goto L_444f77;
L_444fe3:
    eax = lift_load(&env, ecx, 0x160u, 4);
    edx = lift_load(&env, eax, 0x15cu, 4);
    eax = (ebp + 0xffffffe8u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3u;
    ebx = esi;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    edx = edx ^ edx;
    eax = (ebp + 0xffffffe0u);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x4u;
    eax = lift_load(&env, 0u, 0x532b3cu, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    ebx = esi;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf)
        goto L_445031;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_445031;
L_445027:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_444e3b;
L_445031:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_44504c;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe4u, 4), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_44504c;
    edx = edx ^ edx;
    eax = ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe4u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4cb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_445027;
L_44504c:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_445066;
    {
        (void)lift_sub(32, lift_load(&env, ecx, 0x0u, 4), 0x1f5u, &fl);
    }
    if (!fl.zf)
        goto L_445066;
    eax = lift_load(&env, ebp, 0xffffffe4u, 4);
    {
        (void)lift_sub(32, eax, 0x30u, &fl);
    }
    if (fl.cf)
        goto L_445027;
    {
        (void)lift_sub(32, eax, 0x39u, &fl);
    }
    if (!fl.cf && !fl.zf)
        goto L_445027;
L_445066:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_445027;
    edx = lift_load(&env, ebp, 0xffffffe0u, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4790u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_445027;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_444e3b;
}

uint32_t lifted_f445350(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, const LiftEntry *entry)
{
    uint8_t stack[LIFTED_F445350_STACK + 4 + 4 * 0 + 4];
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
    lift_begin(&env, calls, services, globals, stack, LIFTED_F445350_STACK, 0, entry);
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
    esp = esp - 0x24u;
    ecx = eax;
    eax = (ebp + 0xffffffc8u);
    edx = 0x4ec1ecu;
    ebx = 0x515190u;
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
    esi = esi ^ esi;
    lift_store(&env, ebp, 0xffffffccu, 4, edx);
    lift_store(&env, ebp, 0xffffffd0u, 4, ebx);
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    esi = 0x1u;
    edi = edi ^ edi;
L_44538b:
    edx = (ebp + 0xffffffe0u);
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x476530u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = eax;
    {
        (void)lift_and(16, (eax & 0xffffu), (eax & 0xffffu), &fl);
    }
    if (!fl.zf)
        goto L_4453bb;
    {
        (void)lift_sub(32, edi, lift_load(&env, ebp, 0xffffffe0u, 4), &fl);
    }
    if (!fl.zf)
        goto L_445530;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_4453bb:
    eax = lift_load(&env, ecx, 0x160u, 4);
    edx = lift_load(&env, eax, 0x15cu, 4);
    eax = (ebp + 0xffffffe4u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, esi);
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x1u, &fl);
    }
    if (fl.zf)
        goto L_44546b;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x1cu, &fl);
    }
    if (fl.zf)
        goto L_4453ec;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x56u, &fl);
    }
    if (!fl.zf)
        goto L_4454be;
L_4453ec:
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4451d0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = ecx;
    esi = lift_load(&env, ecx, 0x184u, 4);
    lift_store(&env, ecx, 0x52u, 1, 0x9u);
    {
        (void)lift_and(32, esi, esi, &fl);
    }
    if (fl.zf)
        goto L_44542d;
    eax = lift_load(&env, ecx, 0x160u, 4);
    eax = lift_load(&env, eax, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x184u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_44542d:
    eax = lift_load(&env, ecx, 0x160u, 4);
    edx = 0x50e16bu;
    eax = eax + 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = 0x54d640u;
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4766b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe4u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_44546b:
    eax = 0x5588f8u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x477ed0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4510u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x4451d0u;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ac8f0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    lift_store(&env, ecx, 0x52u, 1, 0x9u);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4c90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = edx ^ edx;
    eax = 0x54d640u;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4766b0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = (ebp + 0xffffffe4u);
    edx = edx ^ edx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = lift_load(&env, ebp, 0xffffffc8u, 4);
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
L_4454be:
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x5fu, &fl);
    }
    if (!fl.zf)
        goto L_4454e0;
L_4454c4:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4600u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4454cb:
    eax = (ebp + 0xffffffe4u);
    edx = edi;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca210u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    lift_store(&env, ebp, 0xffffffd4u, 4, edi);
    goto L_44538b;
L_4454e0:
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x60u, &fl);
    }
    if (fl.zf)
        goto L_445507;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x5cu, &fl);
    }
    if (fl.zf)
        goto L_445510;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x61u, &fl);
    }
    if (fl.zf)
        goto L_445519;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0xeu, &fl);
    }
    if (fl.zf)
        goto L_445522;
    {
        (void)lift_sub(16, (ebx & 0xffffu), 0x65u, &fl);
    }
    if (!fl.zf)
        goto L_4454cb;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4af0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4454cb;
L_445507:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4454cb;
L_445510:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4454cb;
L_445519:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4630u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_4454cb;
L_445522:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4950u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_4454cb;
    goto L_4454c4;
L_445530:
    edx = lift_load(&env, ecx, 0x160u, 4);
    eax = (ebp + 0xffffffe8u);
    edx = lift_load(&env, edx, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca280u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = 0x3u;
    ebx = esi;
    lift_store(&env, ebp, 0xffffffd4u, 4, edx);
    edx = edx ^ edx;
    eax = (ebp + 0xffffffdcu);
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda90u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    ebx = 0x4u;
    eax = lift_load(&env, 0u, 0x532b3cu, 4);
    lift_store(&env, ebp, 0xffffffd4u, 4, ebx);
    ebx = esi;
    {
        (void)lift_sub(32, edi, eax, &fl);
    }
    if (!fl.zf)
        goto L_44557e;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe0u, 4), 0x40u, &fl);
    }
    if (!fl.zf)
        goto L_44557e;
L_445574:
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_44538b;
L_44557e:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_445599;
    {
        (void)lift_sub(32, lift_load(&env, ebp, 0xffffffe0u, 4), 0x20u, &fl);
    }
    if (fl.zf)
        goto L_445599;
    edx = edx ^ edx;
    eax = ecx;
    edx = (edx & 0xffffff00u) | ((lift_load(&env, ebp, 0xffffffe0u, 1)) & 0xffu);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4cb0u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_and(32, eax, eax, &fl);
    }
    if (fl.zf)
        goto L_445574;
L_445599:
    {
        (void)lift_sub(32, ebx, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_445574;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4790u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_4455bd;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_44538b;
L_4455bd:
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4660u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, ebx, &fl);
    }
    if (!fl.zf)
        goto L_445574;
    ebx = lift_load(&env, ecx, 0x184u, 4);
    edx = ecx;
    {
        (void)lift_sub(32, edi, ebx, &fl);
    }
    if (fl.zf)
        goto L_4455e6;
    eax = lift_load(&env, ecx, 0x160u, 4);
    eax = lift_load(&env, eax, 0x15cu, 4);
    vertrix_lift_fl = fl;
    eax = lift_call(&env, lift_load(&env, edx, 0x184u, 4), eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
L_4455e6:
    eax = lift_load(&env, ecx, 0x160u, 4);
    edx = 0x50e16cu;
    eax = eax + 0x15cu;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4ca370u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4620u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    edx = lift_load(&env, ebp, 0xffffffdcu, 4);
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4790u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    {
        (void)lift_sub(32, eax, 0x1u, &fl);
    }
    if (!fl.zf)
        goto L_445574;
    eax = ecx;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4b4610u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    vertrix_lift_fl = fl;
    eax = lift_call(&env, 0x4cda10u, eax, edx, ebx, ecx, 0, esp);
    edx = vertrix_lift_edx;
    fl = vertrix_lift_fl;
    goto L_44538b;
}
