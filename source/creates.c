#include "creates.h"

/* The screen object's construction, the screen's palette message callback, and the COM object's
 * creation with its settings. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x47e4f0: the screen object eax's construction: under a guard record (0x516880) its
 * three texts +0x1c, +0x3c and +0x40 are made (0x4ca070), the methods 0x516a54 set at +0x1c8, COM
 * started (CoInitializeEx 0x4f1764 of 0, 0), the texts given 0x50ead8, 0x50ead9 and 0x50eada
 * (0x4ca370), +0x30 and +0x44 set and +0x34 and +0x38 cleared, the rectangle (0x47fbb0) copied to
 * +0xa4, the other fields cleared (+0xb8 set, +0x18 1), the block reset (0x47f070), the critical
 * sections 0x558c9c and 0x558cb4 made (0x4f1c30) and 0x558ccc cleared. The object. */
uint32_t vertrix_port_screen_construct_47e4f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x48
    };
    static const uint32_t cleared[] = {0xb4, 0,    4,     8,     0xc,   0x20, 0x24,
                                       0x28, 0x2c, 0x1bc, 0x1c0, 0x1c4, 0x14, 0x10};
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t args[2];
    unsigned index;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x44u, port.env.chain);
    port_set32(&port, ebp, -0x40u, 0x4ec1ec);
    port_set32(&port, ebp, -0x3cu, 0x516880);
    port_set32(&port, ebp, -0x38u, 0);
    port_set32(&port, ebp, -0x20u, screen);
    port_set8(&port, ebp, -0x1cu, 0);
    eax = port_call_with(&port, 0x4ca070, screen + 0x1c, 2, screen, 3, 0, 1, ebp);
    port_set32(&port, ebp, -0x38u, 1);
    eax = port_call_with(&port, 0x4ca070, eax + 0x20, vertrix_lift_edx, screen, 3, 0, 1, ebp);
    edx = vertrix_lift_edx;
    port_set32(&port, ebp, -0x38u, edx);
    eax = port_call_with(&port, 0x4ca070, eax + 4, edx, screen, 3, 0, 1, ebp);
    port_set32(&port, ebp, -0x38u, 3);
    screen = eax - 0x40;
    port_set32(&port, screen, 0x1c8, 0x516a54);
    args[0] = 0;
    args[1] = 0;
    call_frame(&port, 0x4f1764, eax, vertrix_lift_edx, screen, 3, 0, 1, ebp, args, 2);
    port_call_with(&port, 0x4ca370, screen + 0x1c, 0x50ead8, screen, 3, 0, 1, ebp);
    port_set32(&port, screen, 0x30, 1);
    port_call_with(&port, 0x4ca370, screen + 0x3c, 0x50ead9, screen, 3, 0, 1, ebp);
    port_call_with(&port, 0x4ca370, screen + 0x40, 0x50eada, screen, 3, 0, 1, ebp);
    port_set32(&port, screen, 0x44, 1);
    port_set32(&port, screen, 0x34, 0);
    port_set32(&port, screen, 0x38, 0);
    port_call_with(&port, 0x47fbb0, screen, vertrix_lift_edx, screen, 3, ebp - 0x30, 1, ebp);
    for (index = 0; index < 4; ++index)
    {
        port_set32(&port, screen, 0xa4 + index * 4, port_u32(&port, ebp, -0x30u + index * 4));
    }
    for (index = 0; index < sizeof cleared / sizeof cleared[0]; ++index)
    {
        port_set32(&port, screen, cleared[index], 0);
    }
    port_set32(&port, screen, 0x18, 1);
    port_set8(&port, screen, 0xb8, 1);
    eax = port_call_with(&port, 0x47f070, screen, vertrix_lift_edx, screen, 3, ebp - 0x20,
                         screen + 0xb4, ebp);
    args[0] = 0x558c9c;
    eax = call_frame(&port, 0x4f1c30, eax, vertrix_lift_edx, screen, 3, ebp - 0x20, screen + 0xb4,
                     ebp, args, 1);
    args[0] = 0x558cb4;
    call_frame(&port, 0x4f1c30, eax, vertrix_lift_edx, screen, 3, 0, screen + 0xb4, ebp, args, 1);
    port_set32(&port, 0, 0x558ccc, 0);
    return port_return(&port, screen, entry->edx);
}

/* Original 0x47eb60: the screen's window message callback (ret 0xc): for the message 0x8002 the
 * screen 0x558ccc's device +0 is given its +0x1bc and the argument's +4 (method +0x8c, with 1);
 * otherwise 0. */
uint32_t vertrix_port_screen_message_47eb60(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0xc];
    uint32_t ebp = entry->esp - 4;
    uint32_t screen;
    uint32_t device;
    uint32_t methods;
    uint32_t result;
    uint32_t args[4];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    if (port_u32(&port, ebp, 0xc) != 0x8002)
    {
        return port_return(&port, 0, port_u32(&port, ebp, 0xc));
    }
    screen = port_u32(&port, 0, 0x558ccc);
    device = port_u32(&port, screen, 0);
    methods = port_u32(&port, device, 0);
    args[0] = device;
    args[1] = port_u32(&port, port_u32(&port, ebp, 0x10), 4);
    args[2] = port_u32(&port, screen, 0x1bc);
    args[3] = 1;
    result = call_frame(&port, port_u32(&port, methods, 0x8c), device, port_u32(&port, ebp, 0x10),
                        args[2], methods, args[1], entry->edi, ebp, args, 4);
    return port_return(&port, result, vertrix_lift_edx);
}

/* The COM object [esi]'s release (method +8) and clearing: 0. */
static uint32_t object_drop(Port *port, uint32_t object, uint32_t place, uint32_t eax, uint32_t ebx,
                            uint32_t edi, uint32_t ebp)
{
    uint32_t args[1];
    args[0] = object;
    call_frame(port, port_u32(port, port_u32(port, object, 0), 8), eax, vertrix_lift_edx, ebx,
               port_u32(port, object, 0), place, edi, ebp, args, 1);
    port_set32(port, place, 0, 0);
    return port_return(port, 0, vertrix_lift_edx);
}

/* Original 0x47f5f0: the COM object of the class 0x5168cc and interface 0x5168dc into [edx]
 * (CoCreateInstance 0x4f175c), started with 0x51698c (method +0x34); for the name ecx with the
 * extension 0x50ee94 (0x4ccfe0) its number (0x4ce080) is set as 0x50ee95 (method +0x48, 4 bytes,
 * kind 2), and a text ebx of any length is widened (0x4c9ff0 of 2n + 2 bytes, 0x47fce0 of eax)
 * and set as 0x50ee9f (0x4d8580 counts it, kind 1). 1 on success; a failure releases the object
 * (method +8), clears [edx] and gives 0. */
uint32_t vertrix_port_object_create_47f5f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t place = entry->edx;
    uint32_t name = entry->ecx;
    uint32_t text = entry->ebx;
    uint32_t object;
    uint32_t methods;
    uint32_t number;
    uint32_t length;
    uint32_t buffer;
    uint32_t eax;
    uint32_t args[5];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0xcu, entry->eax);
    args[0] = 0x5168cc;
    args[1] = 0;
    args[2] = 1;
    args[3] = 0x5168dc;
    args[4] = place;
    if ((int32_t)call_frame(&port, 0x4f175c, entry->eax, entry->edx, text, entry->ecx, place, name,
                            ebp, args, 5) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    object = port_u32(&port, place, 0);
    methods = port_u32(&port, object, 0);
    args[0] = object;
    args[1] = 0x51698c;
    eax = call_frame(&port, port_u32(&port, methods, 0x34), object, vertrix_lift_edx, text, methods,
                     place, name, ebp, args, 2);
    if ((int32_t)eax < 0)
    {
        object = port_u32(&port, place, 0);
        if (object == 0)
        {
            return port_return(&port, 0, vertrix_lift_edx);
        }
        return object_drop(&port, object, place, eax, text, object, ebp);
    }
    if (port_call_with(&port, 0x4ccfe0, name, 0x50ee94, text, methods, place, name, ebp) != 0)
    {
        number = port_call_with(&port, 0x4ce080, name, vertrix_lift_edx, text, methods, place, name,
                                ebp) &
                 0xffff;
        port_set32(&port, ebp, -0x10u, number);
        if (number != 0)
        {
            object = port_u32(&port, place, 0);
            methods = port_u32(&port, object, 0);
            args[0] = object;
            args[1] = 0x50ee95;
            args[2] = ebp - 0x10;
            args[3] = 4;
            args[4] = 2;
            eax = call_frame(&port, port_u32(&port, methods, 0x48), object, vertrix_lift_edx, text,
                             methods, place, ebp - 0x10, ebp, args, 5);
            if ((int32_t)eax < 0)
            {
                object = port_u32(&port, place, 0);
                if (object == 0)
                {
                    return port_return(&port, 0, vertrix_lift_edx);
                }
                return object_drop(&port, object, place, eax, object, ebp - 0x10, ebp);
            }
        }
    }
    if (text == 0 || port_u8(&port, text, 0) == 0)
    {
        return port_return(&port, 1, vertrix_lift_edx);
    }
    for (length = 0; port_u8(&port, text, length) != 0; ++length)
    {
    }
    buffer = port_call_with(&port, 0x4c9ff0, length * 2 + 2, vertrix_lift_edx, text, 0xffffffffu,
                            place, text + length + 1, ebp);
    port_call_with(&port, 0x47fce0, port_u32(&port, ebp, -0xcu), buffer, text, 0xffffffffu, place,
                   buffer, ebp);
    object = port_u32(&port, place, 0);
    methods = port_u32(&port, object, 0);
    eax = port_call_with(&port, 0x4d8580, buffer, vertrix_lift_edx, methods, object, place, buffer,
                         ebp);
    args[0] = object;
    args[1] = 0x50ee9f;
    args[2] = buffer;
    args[3] = eax * 2 + 2;
    /* The kind 1 is pushed before 0x4d8580 (0x47f6e8); the lifted reference hands the method
     * only the four arguments pushed after it. */
    eax = call_frame(&port, port_u32(&port, methods, 0x48), eax * 2 + 2, vertrix_lift_edx, methods,
                     object, place, buffer, ebp, args, 4);
    if ((int32_t)eax >= 0)
    {
        return port_return(&port, 1, vertrix_lift_edx);
    }
    object = port_u32(&port, place, 0);
    if (object == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    return object_drop(&port, object, place, object, methods, buffer, ebp);
}
