#include "port_pointers.h"

/* The pointer's press on an actor. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    uint32_t result;
    vertrix_lift_in_esi = esi;
    vertrix_lift_in_edi = edi;
    vertrix_lift_in_ebp = ebp;
    result = lift_call_arguments(&port->env, target, eax, edx, ebx, ecx, stack, count);
    vertrix_lift_in_esi = vertrix_lift_in_edi = vertrix_lift_in_ebp = 0;
    return result;
}

/* Original 0x4473b0: the actor eax under the pointer: pressed (0x4b6700) it is held (+0x93 1,
 * +0x4e 0x64, +0x52 7, +0x94 0, +0x95 3, +0x44 0x10, the state 0x447600), its owner +0x14c
 * told (0x471bf0) and the sound 0x4f819c of 0x533164 played on both channels 0 and 4 (0x482a60
 * at the volume 0x532b9c); else, over the pointer 0x558944, 0x558946 (or 0x7d00 while 0x558958
 * is set; 0x4b0b70) it grows (+0x28, ecx 0) or shrinks (0x4b6590 of 10), moves (0x4ac500) and,
 * once it lands (0x4ac520 gives 1), takes its stride (0x4ac540, 0x4ac5b0) and its place
 * (0x4b65a0, 0x4ac980 by the speed, 0x4b6540); with the key 0x74 ready (0x476480 of 0x54d640) at a
 * place (0x4764a0) over it (0x4b0b70) it takes +0x44 0x10 and the state 0x447560. The registers but
 * eax kept. */
uint32_t vertrix_port_actor_pointer_press_4473b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t edi = entry->edi;
    uint32_t args[1];
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t sound;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    eax = port_call_with(&port, 0x4b6700, actor, entry->edx, actor, entry->ecx, actor, edi, ebp);
    if (eax != 0)
    {
        port_set8(&port, actor, 0x93, 1);
        port_set8(&port, actor, 0x4e, 0x64);
        port_set8(&port, actor, 0x52, 7);
        port_set8(&port, actor, 0x94, 0);
        port_set8(&port, actor, 0x95, 3);
        port_set8(&port, actor, 0x44, 0x10);
        port_call_with(&port, 0x4ac8f0, actor, 0x447600, actor, entry->ecx, actor, edi, ebp);
        port_call_with(&port, 0x471bf0, port_u32(&port, actor, 0x14c), vertrix_lift_edx, actor,
                       entry->ecx, actor, edi, ebp);
        sound = port_u32(&port, 0, 0x4f819c);
        port_call_with(&port, 0x482a60, 0, port_u32(&port, 0, sound * 4 + 0x533164),
                       port_u32(&port, 0, 0x532b9c), entry->ecx, actor, edi, ebp);
        sound = port_u32(&port, 0, 0x4f819c);
        eax = port_call_with(&port, 0x482a60, 4, port_u32(&port, 0, sound * 4 + 0x533164),
                             port_u32(&port, 0, 0x532b9c), entry->ecx, actor, edi, ebp);
        return port_return(&port, eax, entry->edx);
    }
    ebx = port_u32(&port, 0, 0x558958) != 0
              ? 0x7d00
              : (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, 0x558946);
    ecx = port_u32(&port, 0, 0x558958);
    edx = ecx != 0 ? 0x7d00 : (uint32_t)(int32_t)(int16_t)port_u16(&port, 0, 0x558944);
    if ((port_call_with(&port, 0x4b0b70, actor, edx, ebx, ecx, actor, edi, ebp) & 0xff) == 0)
    {
        ebx = 0xa;
        ecx = (uint32_t)(int32_t)(int16_t)port_call_with(&port, 0x4b6590, actor, vertrix_lift_edx,
                                                         ebx, ecx, actor, edi, ebp);
    }
    else
    {
        ebx = 0x28;
        ecx = 0;
    }
    port_call_with(&port, 0x4ac500, actor, vertrix_lift_edx, ebx, ecx, actor, edi, ebp);
    if (port_call_with(&port, 0x4ac520, actor, vertrix_lift_edx, ebx, ecx, actor, edi, ebp) == 1)
    {
        edx = port_call_with(&port, 0x4ac540, actor, vertrix_lift_edx, ebx, ecx, actor, edi, ebp);
        port_call_with(&port, 0x4ac5b0, actor, edx, ebx, ecx, actor, edi, ebp);
        args[0] = ebx;
        ebx = (uint32_t)(int32_t)(int16_t)port_call_with(&port, 0x4b65a0, actor, vertrix_lift_edx,
                                                         ebx, ecx, actor, edi, ebp);
        edx = (uint32_t)(int32_t)(int16_t)call_frame(&port, 0x4ac980, actor, vertrix_lift_edx, ebx,
                                                     ecx, actor, edi, ebp, args, 1);
        port_call_with(&port, 0x4b6540, actor, edx, ebx, ecx, actor, edi, ebp);
    }
    eax = port_call_with(&port, 0x476480, 0x54d640, 0x74, ebx, ecx, actor, edi, ebp);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    args[0] = ebp - 0x1c;
    call_frame(&port, 0x4764a0, 0x54d640, 0x74, ebp - 0x18, ebp - 0x14, actor, edi, ebp, args, 1);
    ebx = (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x14u);
    eax = port_call_with(&port, 0x4b0b70, actor,
                         (uint32_t)(int32_t)(int16_t)port_u16(&port, ebp, -0x18u), ebx, ebp - 0x14,
                         actor, edi, ebp);
    if ((eax & 0xff) == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_set8(&port, actor, 0x44, 0x10);
    eax = port_call_with(&port, 0x4ac8f0, actor, 0x447560, ebx, ebp - 0x14, actor, edi, ebp);
    return port_return(&port, eax, entry->edx);
}
