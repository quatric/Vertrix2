#include "port_joysticks.h"

/* The joystick device's setup. */

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

/* Original 0x476aa0: the input object eax's joystick for the window edx: DirectInput is made
 * (0x4f080c, version 0x800, the interface 0x51d690, of the module 0x4ce740 +8) into +0xc with +4
 * cleared; the game controllers are enumerated (method +0x10, class 4, the callback 0x477190
 * with the GUID at ebp-0x20, 0x55386c the object's +0xb4 and 0x553868 cleared); the device is
 * made (+0xc) into +0x10, its format 0x51e7dc (+0x2c) and cooperation 5 with the window's handle
 * +0x1c (+0x34). With a device it is unacquired (+0x20), its axes 0 and 4 ranged -1000..1000
 * (+0x18 of 4, the header at ebp-0x4c) and dead zoned 5000 (+0x18 of 5 at ebp-0x34) and it is
 * acquired (+0x1c): on success +4 is 1 and its capabilities are read (+0xc into ebp-0x78, 0x2c
 * bytes), giving 1; any failure gives 0 (+4 0 after a failed acquire). */
uint32_t vertrix_port_joystick_setup_476aa0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x7c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t input = entry->eax;
    uint32_t esi = entry->edx;
    uint32_t edi = entry->edi;
    uint32_t module;
    uint32_t object;
    uint32_t methods;
    uint32_t device;
    uint32_t ecx;
    uint32_t args[5];
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    module = port_call_with(&port, 0x4ce740, input, esi, input, entry->ecx, esi, edi, ebp);
    args[0] = port_u32(&port, module, 8);
    args[1] = 0x800;
    args[2] = 0x51d690;
    args[3] = input + 0xc;
    args[4] = 0;
    port_set32(&port, input, 4, 0);
    if ((int32_t)call_frame(&port, 0x4f080c, input + 0xc, args[0], input, entry->ecx, esi, edi, ebp,
                            args, 5) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set32(&port, 0, 0x55386c, port_u32(&port, input, 0xb4));
    port_set32(&port, 0, 0x553868, 0);
    object = port_u32(&port, input, 0xc);
    methods = port_u32(&port, object, 0);
    args[0] = object;
    args[1] = 4;
    args[2] = 0x477190;
    args[3] = ebp - 0x20;
    args[4] = 1;
    if ((int32_t)call_frame(&port, port_u32(&port, methods, 0x10), object, methods, input,
                            ebp - 0x20, esi, edi, ebp, args, 5) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    object = port_u32(&port, input, 0xc);
    ecx = port_u32(&port, object, 0);
    args[0] = object;
    args[1] = ebp - 0x20;
    args[2] = input + 0x10;
    args[3] = 0;
    if ((int32_t)call_frame(&port, port_u32(&port, ecx, 0xc), object, ebp - 0x20, input, ecx, esi,
                            edi, ebp, args, 4) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    device = port_u32(&port, input, 0x10);
    methods = port_u32(&port, device, 0);
    args[0] = device;
    args[1] = 0x51e7dc;
    if ((int32_t)call_frame(&port, port_u32(&port, methods, 0x2c), device, methods, input, ecx, esi,
                            edi, ebp, args, 2) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    device = port_u32(&port, input, 0x10);
    methods = port_u32(&port, device, 0);
    if (esi != 0)
    {
        esi = port_u32(&port, esi, 0x1c);
    }
    args[0] = device;
    args[1] = esi;
    args[2] = 5;
    object = call_frame(&port, port_u32(&port, methods, 0x34), device, methods, input, ecx, esi,
                        edi, ebp, args, 3);
    if ((int32_t)object < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    device = port_u32(&port, input, 0x10);
    if (device == 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    methods = port_u32(&port, device, 0);
    args[0] = device;
    call_frame(&port, port_u32(&port, methods, 0x20), object, methods, input, device, 0x18, 0x10,
               ebp, args, 1);
    port_set32(&port, ebp, -0x4cu, 0x18);
    port_set32(&port, ebp, -0x48u, 0x10);
    port_set32(&port, ebp, -0x40u, 1);
    port_set32(&port, ebp, -0x3cu, 0xfffffc18u);
    port_set32(&port, ebp, -0x38u, 0x3e8);
    port_set32(&port, ebp, -0x44u, 0);
    device = port_u32(&port, input, 0x10);
    methods = port_u32(&port, device, 0);
    args[0] = device;
    args[1] = 4;
    args[2] = ebp - 0x4c;
    if ((int32_t)call_frame(&port, port_u32(&port, methods, 0x18), device, methods, input,
                            ebp - 0x4c, 0, 0x10, ebp, args, 3) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set32(&port, ebp, -0x44u, 4);
    device = port_u32(&port, input, 0x10);
    methods = port_u32(&port, device, 0);
    args[0] = device;
    args[1] = 4;
    args[2] = ebp - 0x4c;
    if ((int32_t)call_frame(&port, port_u32(&port, methods, 0x18), device, ebp - 0x4c, input,
                            ebp - 0x4c, methods, 4, ebp, args, 3) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set32(&port, ebp, -0x34u, 0x14);
    port_set32(&port, ebp, -0x30u, 0x10);
    port_set32(&port, ebp, -0x28u, 1);
    port_set32(&port, ebp, -0x24u, 0x1388);
    port_set32(&port, ebp, -0x2cu, 0);
    device = port_u32(&port, input, 0x10);
    methods = port_u32(&port, device, 0);
    args[0] = device;
    args[1] = 5;
    args[2] = ebp - 0x34;
    if ((int32_t)call_frame(&port, port_u32(&port, methods, 0x18), device, ebp - 0x34, input,
                            methods, 0x1388, 0, ebp, args, 3) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set32(&port, ebp, -0x2cu, 4);
    device = port_u32(&port, input, 0x10);
    methods = port_u32(&port, device, 0);
    if ((int32_t)call_frame(&port, port_u32(&port, methods, 0x18), device, ebp - 0x34, input,
                            methods, 0x1388, 0, ebp, args, 3) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    device = port_u32(&port, input, 0x10);
    ecx = methods;
    methods = port_u32(&port, device, 0);
    args[0] = device;
    if (call_frame(&port, port_u32(&port, methods, 0x1c), device, methods, input, ecx, 0x1388, 0,
                   ebp, args, 1) != 0)
    {
        port_set32(&port, input, 4, 0);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set32(&port, input, 4, 1);
    port_set32(&port, ebp, -0x78u, 0x2c);
    device = port_u32(&port, input, 0x10);
    methods = port_u32(&port, device, 0);
    args[0] = device;
    args[1] = ebp - 0x78;
    if ((int32_t)call_frame(&port, port_u32(&port, methods, 0xc), device, methods, ebp - 0x78, ecx,
                            0x1388, 0, ebp, args, 2) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    return port_return(&port, 1, vertrix_lift_edx);
}
