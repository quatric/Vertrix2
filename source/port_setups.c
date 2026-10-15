#include "port_setups.h"

/* The marquee's row of sixteen sprites and the keyboard device's setup. */

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

static uint32_t sign16(uint32_t value)
{
    return (uint32_t)(int32_t)(int16_t)value;
}

/* Original 0x46e8b0: the marquee of sixteen sprites (ret 4): each of 0x15c bytes (0x4ca000,
 * 0x4abd70) is set up (0x4adf20 with five zero arguments), its +0xe and +0x16 cleared, given 1
 * (0x4ac470), the speed 2 (0x4ac7b0), the frames 0x54651c (0x4ac8d0) from the frame 2i
 * (0x4ac710), shown (+0x94; 0x4ac8a0), its step -0x10 at +0x48, 4 at +0x95, 0x32 at +0x4e, 0x16i
 * at +0x24 and +0x93 set, placed (0x4ad510) at the words ebx, edx and ecx, its +0x28 4 with the
 * argument 1 (else -4), sized 0xc+i square (0x4ac860), +0x30 0x140, +0x32 5 and +0x44 cleared,
 * the state 0x444850 (0x4ac8f0), its owner eax at +4, and listed (0x4b5e70 on 0x54671c). The
 * last list call's eax and 0x20. */
uint32_t vertrix_port_marquee_build_46e8b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t edx = 0x10;
    uint32_t ebx = 0;
    uint32_t ecx = 0x16;
    uint32_t esi = entry->esi;
    uint32_t edi = 0xc;
    uint32_t eax = 0;
    uint32_t zeros[5] = {0, 0, 0, 0, 0};
    uint32_t index;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, -0x24u, entry->eax);
    port_set32(&port, ebp, -0x20u, entry->edx);
    port_set32(&port, ebp, -0x2cu, entry->ebx);
    port_set32(&port, ebp, -0x14u, entry->ecx);
    port_set32(&port, ebp, -0x28u, 0x10);
    port_set32(&port, ebp, -0x1cu, 0x16);
    port_set32(&port, ebp, -0x18u, 0);
    port_set32(&port, ebp, -0xcu, 0);
    for (index = 0; index < 0x10; ++index)
    {
        port_set32(&port, ebp, -0x10u, 0xc + index);
        eax = port_call_with(&port, 0x4ca000, 0x15c, edx, ebx, ecx, esi, edi, ebp);
        if (eax != 0)
        {
            eax = port_call_with(&port, 0x4abd70, eax, vertrix_lift_edx, ebx, ecx, esi, edi, ebp);
        }
        esi = eax;
        call_frame(&port, 0x4adf20, esi, 0, 0, 0, esi, edi, ebp, zeros, 5);
        port_set16(&port, esi, 0xe, 0);
        port_set16(&port, esi, 0x16, 0);
        port_call_with(&port, 0x4ac470, esi, 1, 0, 0, esi, edi, ebp);
        port_call_with(&port, 0x4ac7b0, esi, 2, 0, 0, esi, edi, ebp);
        port_call_with(&port, 0x4ac8d0, esi, 0x54651c, 0, 0, esi, edi, ebp);
        port_call_with(&port, 0x4ac710, esi, index * 2, 0, 0, esi, edi, ebp);
        port_set8(&port, esi, 0x94, 1);
        port_call_with(&port, 0x4ac8a0, esi, vertrix_lift_edx, 0, 0, esi, edi, ebp);
        port_set16(&port, esi, 0x48, (uint32_t)-0x10);
        port_set8(&port, esi, 0x95, 4);
        port_set8(&port, esi, 0x4e, 0x32);
        port_set16(&port, esi, 0x24, index * 0x16);
        port_set8(&port, esi, 0x93, 1);
        port_call_with(&port, 0x4ad510, esi, sign16(entry->ecx), sign16(entry->edx),
                       sign16(entry->ebx), esi, edi, ebp);
        edi = esi;
        port_set16(&port, esi, 0x28, port_u32(&port, ebp, 8) == 1 ? 4 : 0xfffc);
        port_call_with(&port, 0x4ac860, esi, 0xc + index, index, 0xc + index, esi, esi, ebp);
        port_set16(&port, esi, 0x30, 0x140);
        port_set16(&port, esi, 0x32, 5);
        port_set8(&port, esi, 0x44, 0);
        port_call_with(&port, 0x4ac8f0, esi, 0x444850, index, 0xc + index, esi, esi, ebp);
        port_set32(&port, esi, 4, entry->eax);
        ebx = index + 1;
        ecx = 0xc + index + 1;
        eax = port_call_with(&port, 0x4b5e70, 0x54671c, esi, ebx, ecx, esi, esi, ebp);
        edx = (index + 1) * 2;
        port_set32(&port, ebp, -0x10u, ecx);
        port_set32(&port, ebp, -0x18u, ebx);
        port_set32(&port, ebp, -0xcu, edx);
    }
    return port_return(&port, eax, edx);
}

/* Original 0x477390: the input object eax's keyboard for the window edx: DirectInput is made
 * (0x4f080c, version 0x800, the interface 0x51d690, of the module 0x4ce740 +8) into +8, the
 * device of the GUID 0x51d520 (method +0xc) into +0xc, its format 0x51e9e4 (+0x2c), its
 * cooperation 0xa with the window's handle +0x1c (+0x34), its buffer of 512 (+0x18) and acquired
 * (+0x1c); +0x10 and the result are 1 on success, 0 on any failure. */
uint32_t vertrix_port_keyboard_setup_477390(PORT_SIGNATURE)
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
    uint32_t methods;
    uint32_t handle;
    uint32_t index;
    uint32_t args[5];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x14u, window);
    for (index = 0; index < 4; ++index)
    {
        port_set32(&port, ebp, -0x24u + index * 4, port_u32(&port, 0, 0x51d520 + index * 4));
    }
    module = port_call_with(&port, 0x4ce740, input, window, input, entry->ecx, 0x51d530, ebp - 0x14,
                            ebp);
    args[0] = port_u32(&port, module, 8);
    args[1] = 0x800;
    args[2] = 0x51d690;
    args[3] = input + 8;
    args[4] = 0;
    port_set32(&port, input, 0x10, 0);
    if ((int32_t)call_frame(&port, 0x4f080c, input + 8, args[0], input, entry->ecx, 0x51d530,
                            ebp - 0x14, ebp, args, 5) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    object = port_u32(&port, input, 8);
    methods = port_u32(&port, object, 0);
    args[0] = object;
    args[1] = ebp - 0x24;
    args[2] = input + 0xc;
    args[3] = 0;
    if ((int32_t)call_frame(&port, port_u32(&port, methods, 0xc), object, methods, input,
                            ebp - 0x24, 0x51d530, ebp - 0x14, ebp, args, 4) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    object = port_u32(&port, input, 0xc);
    methods = port_u32(&port, object, 0);
    args[0] = object;
    args[1] = 0x51e9e4;
    if ((int32_t)call_frame(&port, port_u32(&port, methods, 0x2c), object, methods, input,
                            ebp - 0x24, 0x51d530, ebp - 0x14, ebp, args, 2) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    object = port_u32(&port, input, 0xc);
    methods = port_u32(&port, object, 0);
    window = port_u32(&port, ebp, -0x14u);
    handle = window != 0 ? port_u32(&port, window, 0x1c) : 0;
    args[0] = object;
    args[1] = handle;
    args[2] = 0xa;
    if ((int32_t)call_frame(&port, port_u32(&port, methods, 0x34), handle, object, input, methods,
                            window, ebp - 0x14, ebp, args, 3) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set32(&port, ebp, -0x38u, 0x14);
    port_set32(&port, ebp, -0x34u, 0x10);
    port_set32(&port, ebp, -0x30u, 0);
    port_set32(&port, ebp, -0x2cu, 0);
    port_set32(&port, ebp, -0x28u, 0x200);
    object = port_u32(&port, input, 0xc);
    methods = port_u32(&port, object, 0);
    args[0] = object;
    args[1] = 1;
    args[2] = ebp - 0x38;
    if ((int32_t)call_frame(&port, port_u32(&port, methods, 0x18), object, methods, input,
                            ebp - 0x38, 0x200, 0x14, ebp, args, 3) < 0)
    {
        return port_return(&port, 0, vertrix_lift_edx);
    }
    object = port_u32(&port, input, 0xc);
    methods = port_u32(&port, object, 0);
    args[0] = object;
    if ((int32_t)call_frame(&port, port_u32(&port, methods, 0x1c), object, methods, input,
                            ebp - 0x38, 0x200, 0x14, ebp, args, 1) < 0)
    {
        port_set32(&port, input, 0x10, 0);
        return port_return(&port, 0, vertrix_lift_edx);
    }
    port_set32(&port, input, 0x10, 1);
    return port_return(&port, 1, vertrix_lift_edx);
}
