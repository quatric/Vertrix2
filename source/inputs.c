#include "inputs.h"

/* The mouse device setup, the back buffer blit, the guarded text copy, and the ranged random. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x477b10: the input object eax's mouse for the window edx: DirectInput is made
 * (0x4f080c, version 0x800, the interface 0x51d690, of the module 0x4ce740 +8) into +4, the
 * device of the GUID 0x51d530 (method +0xc) into +0x30, its format 0x51ebec (+0x2c), its
 * cooperation 5 with the window's handle +0x1c (+0x34), its buffer of 512 (+0x18), the swapped
 * buttons (slot 0x4f19e4, 23) into +0x38, the state cleared (0x477c90) and acquired (+0x1c);
 * +0xc and the result are 1 on success, 0 on any failure. */
uint32_t vertrix_port_mouse_setup_477b10(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t input = entry->eax;
    uint32_t window = entry->edx;
    uint32_t module;
    uint32_t object;
    uint32_t device;
    uint32_t methods;
    uint32_t handle;
    uint32_t eax;
    uint32_t index;
    uint32_t args[12];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, window);
    for (index = 0; index < 4; ++index)
    {
        port_set32(&port, ebp, -0x24u + index * 4, port_u32(&port, 0, 0x51d530 + index * 4));
    }
    module = port_call_with(&port, 0x4ce740, input, window, input, entry->ecx, 0x51d540, ebp - 0x14,
                            ebp);
    args[0] = port_u32(&port, module, 8);
    args[1] = 0x800;
    args[2] = 0x51d690;
    args[3] = input + 4;
    args[4] = 0;
    port_set32(&port, input, 0xc, 0);
    eax = call_frame(&port, 0x4f080c, args[0], input + 4, input, entry->ecx, 0x51d540, ebp - 0x14,
                     ebp, args, 5);
    if ((int32_t)eax < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    object = port_u32(&port, input, 4);
    methods = port_u32(&port, object, 0);
    args[0] = object;
    args[1] = ebp - 0x24;
    args[2] = input + 0x30;
    args[3] = 0;
    eax = call_frame(&port, port_u32(&port, methods, 0xc), object, methods, input, ebp - 0x24,
                     0x51d540, ebp - 0x14, ebp, args, 4);
    if ((int32_t)eax < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    device = port_u32(&port, input, 0x30);
    methods = port_u32(&port, device, 0);
    args[0] = device;
    args[1] = 0x51ebec;
    eax = call_frame(&port, port_u32(&port, methods, 0x2c), device, methods, input, ebp - 0x24,
                     0x51d540, ebp - 0x14, ebp, args, 2);
    if ((int32_t)eax < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    device = port_u32(&port, input, 0x30);
    methods = port_u32(&port, device, 0);
    handle = port_u32(&port, ebp, -0x14u);
    if (handle != 0)
    {
        handle = port_u32(&port, handle, 0x1c);
    }
    args[0] = device;
    args[1] = handle;
    args[2] = 5;
    eax = call_frame(&port, port_u32(&port, methods, 0x34), device, handle, input, methods,
                     0x51d540, ebp - 0x14, ebp, args, 3);
    if ((int32_t)eax < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set32(&port, ebp, -0x38u, 0x14);
    port_set32(&port, ebp, -0x34u, 0x10);
    port_set32(&port, ebp, -0x30u, 0);
    port_set32(&port, ebp, -0x28u, 0x200);
    port_set32(&port, ebp, -0x2cu, 0);
    device = port_u32(&port, input, 0x30);
    methods = port_u32(&port, device, 0);
    args[0] = device;
    args[1] = 1;
    args[2] = ebp - 0x38;
    eax = call_frame(&port, port_u32(&port, methods, 0x18), device, ebp - 0x38, input, methods,
                     0x10, 0, ebp, args, 3);
    if ((int32_t)eax < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    args[0] = 0x17;
    port_set32(
        &port, input, 0x38,
        call_frame(&port, 0x4f19e4, eax, vertrix_lift_edx, input, methods, 0x10, 0, ebp, args, 1));
    port_call_with(&port, 0x477c90, input, 0, input, methods, 0x10, 0, ebp);
    device = port_u32(&port, input, 0x30);
    args[0] = device;
    eax = call_frame(&port, port_u32(&port, port_u32(&port, device, 0), 0x1c), device,
                     port_u32(&port, device, 0), input, methods, 0x10, 0, ebp, args, 1);
    if (eax != 0)
    {
        port_set32(&port, input, 0xc, 0);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set32(&port, input, 0xc, 1);
    return port_return(&port, 1, vertrix_lift_edx);
}

/* Original 0x47f4b0: the screen eax's flip by blit: with a surface +0 and a source (0x47f320),
 * a description of 0x48 bytes (0x4eb5c0) filled by the screen's method +0x20 of +0x1c8, the
 * source's +0x48 surface (method +0x14) blitted (method +0x18, wait) to the rectangle +4 and
 * released (method +8); success clears +0x30 and gives 1, failure is reported (0x480080), sets
 * +0x30 and gives 0. */
uint32_t vertrix_port_screen_blit_47f4b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x64
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t screen = entry->eax;
    uint32_t source;
    uint32_t object;
    uint32_t methods;
    uint32_t surface;
    uint32_t result;
    uint32_t args[12];
    unsigned index;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, 0);
    if (port_u32(&port, screen, 0) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    source =
        port_call_with(&port, 0x47f320, screen, 0, entry->ebx, entry->ecx, entry->esi, screen, ebp);
    if (source == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_call_with(&port, 0x4eb5c0, ebp - 0x60, vertrix_lift_edx, 0x48, source, entry->esi, screen,
                   ebp);
    port_set32(&port, ebp, -0x60u, 0x48);
    methods = port_u32(&port, screen, 0x1c8);
    port_call_with(&port, port_u32(&port, methods, 0x20), screen, vertrix_lift_edx, methods, source,
                   ebp - 0x48, screen, ebp);
    object = port_u32(&port, source, 0x48);
    methods = port_u32(&port, object, 0);
    args[0] = object;
    args[1] = ebp - 0x18;
    if ((int32_t)call_frame(&port, port_u32(&port, methods, 0x14), object, vertrix_lift_edx,
                            ebp - 0x18, methods, ebp - 0x48, screen, ebp, args, 2) < 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    object = port_u32(&port, screen, 0);
    methods = port_u32(&port, object, 0);
    args[0] = object;
    args[1] = ebp - 0x60;
    args[2] = port_u32(&port, ebp, -0x18u);
    args[3] = port_u32(&port, screen, 4);
    for (index = 4; index < 11; ++index)
    {
        args[index] = 0;
    }
    args[11] = 0x80000000u;
    result = call_frame(&port, port_u32(&port, methods, 0x18), object, args[2], ebp - 0x60, methods,
                        args[3], screen, ebp, args, 12);
    surface = port_u32(&port, ebp, -0x18u);
    if (surface != 0)
    {
        args[0] = surface;
        call_frame(&port, port_u32(&port, port_u32(&port, surface, 0), 8),
                   port_u32(&port, surface, 0), vertrix_lift_edx, result, surface, args[3], screen,
                   ebp, args, 1);
        port_set32(&port, ebp, -0x18u, 0);
    }
    if ((int32_t)result >= 0)
    {
        port_set32(&port, screen, 0x30, 0);
        return port_return(&port, 1, entry->edx);
    }
    port_call_with(&port, 0x480080, screen, result, result, surface, args[3], screen, ebp);
    port_set32(&port, screen, 0x30, 1);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x47fce0: the text copy 0x47fc10 when edx, ebx and ecx are all given. */
uint32_t vertrix_port_text_copy_checked_47fce0(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    if (entry->edx == 0 || entry->ebx == 0 || entry->ecx == 0)
    {
        return port_return(&port, entry->eax, entry->edx);
    }
    eax = port_call_with(&port, 0x47fc10, entry->eax, entry->edx, entry->ebx, entry->ecx,
                         entry->esi, entry->edi, entry->ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x482770: the base dx plus a random below bx (0x4826c0 on the generator eax), or the
 * base alone with a range of 0. */
uint32_t vertrix_port_random_from_482770(PORT_SIGNATURE)
{
    Port port;
    uint32_t base = entry->edx & 0xffff;
    uint32_t value;
    port_open(&port, calls, services, globals, entry);
    if ((entry->ebx & 0xffff) == 0)
    {
        return port_return(&port, base, entry->edx);
    }
    value = port_call_with(&port, 0x4826c0, entry->eax, entry->ebx & 0xffff, entry->ebx, entry->edx,
                           entry->esi, entry->edi, entry->ebp) &
            0xffff;
    return port_return(&port, base + value, value);
}
