#include "port_devicelists.h"

/* The list of input devices kept by their GUIDs. */

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

/* rep movsd then rep movsb of `count` bytes from `from` to `to`. */
static void device_copy(Port *port, uint32_t to, uint32_t from, uint32_t count)
{
    uint32_t i;
    for (i = 0; i < count >> 2; i++)
    {
        port_set32(port, to + i * 4, 0, port_u32(port, from + i * 4, 0));
    }
    for (i = count & ~3u; i < count; i++)
    {
        port_set8(port, to + i, 0, port_u8(port, from + i, 0));
    }
}

/* Original 0x47eeb0: under the lock 0x558c9c (the imports 0x4f1b48 and 0x4f1c40) the device of
 * the enumeration edx (its object +4, its description +0xc) joins the list +0xc of eax unless one
 * there has its GUID (+8, 16 bytes; repe cmpsb, the registers left as it leaves them). The record
 * of 0x64 bytes (0x4ca000, cleared by 0x4eb5c0) takes the object's information (method +0x14 into
 * +0x48), the description's first 0x48 bytes with +0x30..+0x47 cleared, its data (+0x40, +0x44
 * bytes) at +0x50, a copy of its name +0x30 (0x4d8580, 0x4c9ff0, 0x4d85a0) at +0x4c and the old
 * head at +0x60. On a failed information call the record's object is released (+8). Returns 0. */
uint32_t vertrix_port_device_list_add_47eeb0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t owner = entry->eax;
    uint32_t record = entry->edx;
    uint32_t description;
    uint32_t args[2];
    uint32_t eax;
    uint32_t edx = 0;
    uint32_t ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t edi = entry->edi;
    uint32_t node;
    uint32_t memory;
    uint32_t object;
    uint32_t methods;
    uint32_t name;
    uint32_t size;
    uint32_t held;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x20u, owner);
    port_set32(&port, ebp, -0x28u, record);
    description = port_u32(&port, record, 0xc);
    port_set32(&port, ebp, -0x24u, 0);
    port_set32(&port, ebp, -0x1cu, description);
    args[0] = 0x558c9c;
    eax = description;
    call_frame(&port, 0x4f1b48, eax, 0, owner, ecx, esi, edi, ebp, args, 1);
    for (node = port_u32(&port, owner, 0xc); node != 0; node = port_u32(&port, node, 0x60))
    {
        uint32_t a = 0;
        uint32_t b = 0;
        edx = description + 8;
        ecx = 0x10;
        esi = edx;
        edi = node + 8;
        eax = 0;
        while (ecx != 0)
        {
            a = port_u8(&port, esi, 0);
            b = port_u8(&port, edi, 0);
            esi++;
            edi++;
            ecx--;
            if (a != b)
            {
                break;
            }
        }
        if (a == b)
        {
            port_set32(&port, ebp, -0x18u, 0);
            ebx = node;
            goto leave;
        }
        eax = a < b ? 0xffffffffu : 1;
    }
    ebx = 0;
    memory = port_call_with(&port, 0x4ca000, 0x64, edx, 0, ecx, esi, edi, ebp);
    port_set32(&port, ebp, -0x14u, memory);
    port_set32(&port, ebp, -0x18u, memory);
    eax = memory;
    edx = vertrix_lift_edx;
    if (memory == 0)
    {
        goto leave;
    }
    port_call_with(&port, 0x4eb5c0, memory, 0, 0x64, ecx, esi, edi, ebp);
    object = port_u32(&port, record, 4);
    methods = port_u32(&port, object, 0);
    args[0] = object;
    args[1] = memory + 0x48;
    ebx = 0x64;
    ecx = methods;
    eax = call_frame(&port, port_u32(&port, methods, 0x14), object, memory + 0x48, ebx, ecx, esi,
                     edi, ebp, args, 2);
    edx = vertrix_lift_edx;
    if ((int32_t)eax < 0)
    {
        goto leave;
    }
    port_call_with(&port, 0x4eb5c0, memory, 0, 0x48, 0x48, description, memory, ebp);
    device_copy(&port, memory, description, 0x48);
    for (size = 0x20; size >= 0xc; size -= 4)
    {
        port_set32(&port, memory + 0x50, 0u - size, 0);
    }
    size = port_u32(&port, description, 0x44);
    port_call_with(&port, 0x4eb5c0, memory + 0x50, 0, size, description, description, memory + 0x50,
                   ebp);
    edx = vertrix_lift_edx;
    size = port_u32(&port, description, 0x44);
    esi = port_u32(&port, description, 0x40);
    device_copy(&port, memory + 0x50, esi, size);
    esi += size;
    edi = memory + 0x50;
    ecx = 0;
    name = port_u32(&port, description, 0x30);
    ebx = name;
    if (name != 0)
    {
        eax = port_call_with(&port, 0x4d8580, name, edx, ebx, 0, esi, edi, ebp);
        eax = port_call_with(&port, 0x4c9ff0, eax * 2 + 2, vertrix_lift_edx, ebx, 0, esi, edi, ebp);
        port_set32(&port, ebp, -0x24u, eax);
        if (eax != 0)
        {
            port_call_with(&port, 0x4d85a0, eax, port_u32(&port, description, 0x30), ebx, 0, esi,
                           edi, ebp);
        }
    }
    memory = port_u32(&port, ebp, -0x18u);
    port_set32(&port, memory, 0x4c, port_u32(&port, ebp, -0x24u));
    port_set32(&port, memory, 0x60, port_u32(&port, owner, 0xc));
    port_set32(&port, ebp, -0x18u, 0);
    port_set32(&port, owner, 0xc, memory);
    eax = owner;
    edx = memory;
leave:
    args[0] = 0x558c9c;
    eax = call_frame(&port, 0x4f1c40, eax, edx, ebx, ecx, esi, edi, ebp, args, 1);
    held = port_u32(&port, ebp, -0x18u);
    if (held == 0)
    {
        return port_return(&port, 0, held);
    }
    object = port_u32(&port, held, 0x48);
    if (object == 0)
    {
        return port_return(&port, 0, held);
    }
    methods = port_u32(&port, object, 0);
    args[0] = object;
    call_frame(&port, port_u32(&port, methods, 8), eax, methods, ebx, object, esi, edi, ebp, args,
               1);
    port_set32(&port, port_u32(&port, ebp, -0x18u), 0x48, 0);
    return port_return(&port, 0, vertrix_lift_edx);
}

/* Original 0x47fe80: with the device +0x1bc of eax and its effect +0x1c0 both set, the effect is
 * started (method +0x20 with 4 and 0); otherwise eax is returned. ebx, ecx and edx kept. */
uint32_t vertrix_port_device_effect_start_47fe80(PORT_SIGNATURE)
{
    Port port;
    uint32_t owner = entry->eax;
    uint32_t device;
    uint32_t effect;
    uint32_t methods;
    uint32_t args[4];
    port_open(&port, calls, services, globals, entry);
    device = port_u32(&port, owner, 0x1bc);
    if (device == 0 || port_u32(&port, owner, 0x1c0) == 0)
    {
        return port_return(&port, owner, entry->edx);
    }
    effect = port_u32(&port, owner, 0x1c0);
    methods = port_u32(&port, device, 0);
    args[0] = device;
    args[1] = effect;
    args[2] = 4;
    args[3] = 0;
    return port_return(&port,
                       port_forward_stack(&port, entry, port_u32(&port, methods, 0x20), owner,
                                          device, effect, methods, entry->esi, args, 4),
                       entry->edx);
}
