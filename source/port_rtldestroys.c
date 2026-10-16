#include "port_rtldestroys.h"

/* Objects destroyed with their parts. */

/* Original 0x43a1a0 (guarded 0x514b50): the object eax destroyed by the flags edx. With flag 4
 * it is handed 0x514bb0 (0x4ccb9f) and 0x4ca040 run with 0. Otherwise its class becomes 0x514b94
 * (+0x158), its three parts +0x15c..+0x164 destroyed (their class's first method with 2), the
 * inherited destroy run (0x4ac130 with 1) and with flag 2 the memory freed (0x4ca050). eax the
 * object, or what 0x4ac130 gave. */
uint32_t vertrix_port_object_destroy_parts_43a1a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x4c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x34;
    uint32_t object = entry->eax;
    uint32_t flags = entry->edx & 0xff;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx;
    uint32_t part;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x14u, entry->edx);
    if (flags & 4)
    {
        port_set32(&port, ebp, -0x48u, object);
        port_set32(&port, ebp, -0x28u, 1);
        eax = port_call_with(&port, 0x4ccb9f, object, 0x514bb0, ebx, entry->ecx, 1, object, ebp);
        port_set32(&port, ebp, -0x28u, 0);
        port_call_with(&port, 0x4ca040, eax, 0, ebx, entry->ecx, 1, object, ebp);
        return port_return(&port, object, vertrix_lift_edx);
    }
    eax = (object & 0xffff00ffu) | (flags << 8);
    port_set32(&port, object, 0x158, 0x514b94);
    port_set8(&port, ebp, -0x1cu, flags);
    port_set32(&port, ebp, -0x20u, object);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    eax = record;
    port_set32(&port, ebp, -0x30u, 0x4ec1ec);
    port_set32(&port, ebp, -0x2cu, 0x514b50);
    ebx = 3;
    port_set32(&port, ebp, -0x28u, ebx);
    for (ecx = object; ecx != object + 0xc && !port.env.failed; ecx += 4)
    {
        part = port_u32(&port, ecx, 0x15c);
        ebx = part;
        if (part != 0)
        {
            eax = part;
            ebx = port_u32(&port, part, 0x158);
            eax = port_call_with(&port, port_u32(&port, ebx, 0), eax, 2, ebx, ecx, object + 0xc,
                                 object, ebp);
        }
    }
    port_set32(&port, ebp, -0x28u, 0);
    result = port_call_with(&port, 0x4ac130, object, 1, ebx, ecx, 0, object, ebp);
    edx = (vertrix_lift_edx & 0xffffff00u) | port_u8(&port, ebp, -0x14u);
    port_set32(&port, ebp, -0x28u, 0);
    if (edx & 2)
    {
        port_call_with(&port, 0x4ca050, result, edx, ebx, ecx, 0, result, ebp);
        edx = vertrix_lift_edx;
    }
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, result, edx);
}
