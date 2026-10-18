#include "rtlwaits.h"

/* Frame waits, cursor capture, menu and dropped-file walks, float truncation, fault flags and the
 * mixer effect. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x40aed0 (one stack argument, popped): unless 0x52f14c is set, 0x40ab10 run every 10
 * ticks of the import 0x4f1bf8 from the call's time, sleeping (0x4f1cc8) the time left, until
 * 0x52f14c is set. eax 1 when the argument is non-zero, else 0. */
uint32_t vertrix_port_frame_wait_40aed0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx = entry->ecx;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    eax = call_frame(&port, 0x4f1bf8, entry->eax, entry->edx, entry->ebx, ecx, entry->esi,
                     entry->edi, ebp, NULL, 0);
    edx = vertrix_lift_edx;
    ebx = eax;
    if (port_u32(&port, 0, 0x52f14c) == 0)
    {
        do
        {
            eax = call_frame(&port, 0x40ab10, eax, edx, ebx, ecx, entry->esi, entry->edi, ebp, NULL,
                             0);
            edx = vertrix_lift_edx;
            ebx += 0xa;
            eax = call_frame(&port, 0x4f1bf8, eax, edx, ebx, ecx, entry->esi, entry->edi, ebp, NULL,
                             0);
            edx = ebx - eax;
            eax = edx;
            if ((int32_t)edx > 0)
            {
                uint32_t wait[1] = {edx};
                eax = call_frame(&port, 0x4f1cc8, eax, edx, ebx, ecx, entry->esi, entry->edi, ebp,
                                 wait, 1);
                edx = vertrix_lift_edx;
            }
        } while (port_u32(&port, 0, 0x52f14c) == 0 && !port.env.failed);
    }
    eax = port_u32(&port, entry->esp, 4) != 0 ? 1 : 0;
    return port_return(&port, eax, edx);
}

/* Original 0x477c30: the capture of the object eax: none without its device +0x30 (+0xc 0, eax 0);
 * otherwise the device's method +0x1c called twice and, when the second gives 0, the import
 * 0x4f1a9c with 0 and 0x4f1ae4 with 0 until it goes negative, +0xc 1 and eax 1. edx kept. */
uint32_t vertrix_port_cursor_capture_477c30(PORT_SIGNATURE)
{
    Port port;
    uint32_t object = entry->eax;
    uint32_t device;
    uint32_t vtable;
    uint32_t eax;
    uint32_t zero[1] = {0};
    port_open(&port, calls, services, globals, entry);
    device = port_u32(&port, object, 0x30);
    if (device == 0)
    {
        port_set32(&port, object, 0xc, 0);
        return port_return(&port, 0, entry->edx);
    }
    {
        uint32_t self[1] = {device};
        vtable = port_u32(&port, device, 0);
        port_forward_stack(&port, entry, port_u32(&port, vtable, 0x1c), device, vtable, object,
                           entry->ecx, entry->esi, self, 1);
    }
    device = port_u32(&port, object, 0x30);
    {
        uint32_t self[1] = {device};
        vtable = port_u32(&port, device, 0);
        eax = port_forward_stack(&port, entry, port_u32(&port, vtable, 0x1c), device, vtable,
                                 object, entry->ecx, entry->esi, self, 1);
    }
    if (eax != 0)
    {
        port_set32(&port, object, 0xc, 0);
        return port_return(&port, 0, entry->edx);
    }
    eax = port_forward_stack(&port, entry, 0x4f1a9c, eax, vertrix_lift_edx, object, entry->ecx,
                             entry->esi, zero, 1);
    do
    {
        eax = port_forward_stack(&port, entry, 0x4f1ae4, eax, vertrix_lift_edx, object, entry->ecx,
                                 entry->esi, zero, 1);
    } while ((int32_t)eax >= 0 && !port.env.failed);
    port_set32(&port, object, 0xc, 1);
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4db866: the fault flags of ebx (its low five bits, with 0x1080 unless they are 8 or
 * edx is set, then 0x1040) raised by 0x4dad2e with the operands eax and edx kept in the frame. */
uint32_t vertrix_port_rtl_flags_call_4db866(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t eax = entry->ebx & 0x1f;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -8u, entry->eax);
    port_set32(&port, ebp, -4u, entry->edx);
    if (eax != 8 && entry->edx == 0)
    {
        eax |= 0x1080;
    }
    else
    {
        eax |= 0x1040;
    }
    eax = port_call_with(&port, 0x4dad2e, eax, ebp - 8, entry->ebx, entry->ecx, entry->esi,
                         entry->edi, ebp);
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x4ee025: the extended float at eax truncated to an integer: 0 below 1, 0x80000000
 * from 2^31 on, else the top bits of the mantissa negated by the sign. edx kept. */
uint32_t vertrix_port_rtl_float_trunc_4ee025(PORT_SIGNATURE)
{
    Port port;
    uint32_t value = entry->eax;
    uint32_t exponent;
    uint32_t high;
    uint32_t result;
    int32_t shift;
    port_open(&port, calls, services, globals, entry);
    exponent = port_u16(&port, value, 8);
    shift = (int16_t)(uint16_t)((exponent & 0x7fff) - 0x3ffe);
    if (shift < 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    if (shift > 0x1f)
    {
        return port_return(&port, 0x80000000u, entry->edx);
    }
    high = port_u32(&port, value, 4);
    result = shift == 0 ? 0 : high >> (32 - shift);
    if (exponent & 0x8000)
    {
        result = 0u - result;
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4d06d0: the menu item of the id edx in the menu eax (its handle +4), searched depth
 * first: each item's submenu (import 0x4f19dc) known to 0x4e1210 is searched in turn; an item of
 * the id (0x4f19a8) gives 0x4e1230 of the menu. eax 0 when none. */
uint32_t vertrix_port_menu_find_4d06d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t menu = entry->eax;
    uint32_t id = entry->edx;
    uint32_t count;
    uint32_t index = 0;
    uint32_t eax;
    uint32_t edx;
    uint32_t ecx = entry->ecx;
    port_open(&port, calls, services, globals, entry);
    {
        uint32_t args[1] = {port_u32(&port, menu, 4)};
        count =
            call_frame(&port, 0x4f19a4, menu, id, entry->ebx, ecx, menu, id, entry->ebp, args, 1);
    }
    edx = vertrix_lift_edx;
    eax = count;
    if ((int32_t)count <= 0)
    {
        return port_return(&port, 0, edx);
    }
    do
    {
        uint32_t args[2] = {port_u32(&port, menu, 4), index};
        eax = call_frame(&port, 0x4f19dc, eax, edx, index, ecx, menu, id, count, args, 2);
        args[0] = eax;
        eax = call_frame(&port, 0x4e1210, eax, vertrix_lift_edx, index, ecx, menu, id, count, args,
                         1);
        edx = vertrix_lift_edx;
        if (eax != 0)
        {
            eax = call_frame(&port, 0x4d06d0, eax, id, index, ecx, menu, id, count, NULL, 0);
            edx = vertrix_lift_edx;
            if (eax != 0)
            {
                return port_return(&port, eax, edx);
            }
        }
        else
        {
            args[0] = port_u32(&port, menu, 4);
            args[1] = index;
            eax = call_frame(&port, 0x4f19a8, eax, edx, index, ecx, menu, id, count, args, 2);
            edx = vertrix_lift_edx;
            if (eax == id)
            {
                args[0] = port_u32(&port, menu, 4);
                eax = call_frame(&port, 0x4e1230, eax, edx, index, ecx, menu, id, count, args, 1);
                return port_return(&port, eax, vertrix_lift_edx);
            }
        }
        index++;
    } while ((int32_t)index < (int32_t)count && !port.env.failed);
    return port_return(&port, 0, edx);
}

/* Original 0x4d50d0: the files dropped on the handle edx: the window of the control eax (+0x1c,
 * import 0x4f1a98) brought up by 0x4cf8e0, each file name (0x4f179c into a 260-byte buffer) added
 * to the list +4 of 0x4ce740 by its method +0x80, and the drop released (0x4f1798). */
uint32_t vertrix_port_files_dropped_4d50d0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x118
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - BELOW;
    uint32_t drop = entry->edx;
    uint32_t eax;
    uint32_t edx;
    uint32_t ecx = entry->ecx;
    uint32_t count;
    uint32_t list;
    uint32_t index = 0;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->ecx);
    port_set32(&port, entry->esp, -0xcu, entry->esi);
    port_set32(&port, entry->esp, -0x10u, entry->edi);
    port_set32(&port, entry->esp, -0x14u, entry->ebp);
    {
        uint32_t args[1] = {port_u32(&port, entry->eax, 0x1c)};
        eax = call_frame(&port, 0x4f1a98, entry->eax, drop, entry->ebx, ecx, entry->esi, drop,
                         entry->ebp, args, 1);
        args[0] = eax;
        eax = call_frame(&port, 0x4cf8e0, eax, vertrix_lift_edx, entry->ebx, ecx, entry->esi, drop,
                         entry->ebp, args, 1);
    }
    {
        uint32_t args[4] = {drop, 0xffffffffu, 0, 0};
        count = call_frame(&port, 0x4f179c, eax, vertrix_lift_edx, 0, ecx, entry->esi, drop,
                           entry->ebp, args, 4);
    }
    eax = call_frame(&port, 0x4ce740, count, vertrix_lift_edx, 0, ecx, entry->esi, drop, count,
                     NULL, 0);
    edx = vertrix_lift_edx;
    list = port_u32(&port, eax, 4);
    while (index < count && !port.env.failed)
    {
        uint32_t args[4] = {drop, index, esp, 0x104};
        call_frame(&port, 0x4f179c, eax, esp, index, ecx, list, drop, count, args, 4);
        ecx = port_u32(&port, list, 0);
        index++;
        eax = call_frame(&port, port_u32(&port, ecx, 0x80), list, esp, index, ecx, list, drop,
                         count, NULL, 0);
        edx = vertrix_lift_edx;
    }
    {
        uint32_t args[1] = {drop};
        eax = call_frame(&port, 0x4f1798, eax, edx, index, ecx, list, drop, count, args, 1);
    }
    return port_return(&port, eax, vertrix_lift_edx);
}

/* Original 0x40d490: unless the mixer is busy (0x531b4c), the voice eax's volume +0x10 and +0x14
 * set to its byte +4 (at most 0x40) and the change bit 2 of byte +1 set. edx kept. */
uint32_t vertrix_port_mixer_set_volume_40d490(PORT_SIGNATURE)
{
    Port port;
    uint32_t voice = entry->eax;
    uint32_t volume;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x531b4c) != 0)
    {
        return port_return(&port, voice, entry->edx);
    }
    volume = port_u8(&port, voice, 4);
    port_set32(&port, voice, 0x10, volume);
    if ((int32_t)volume > 0x40)
    {
        port_set32(&port, voice, 0x10, 0x40);
    }
    port_set32(&port, voice, 0x14, port_u32(&port, voice, 0x10));
    port_set8(&port, voice, 1, port_u8(&port, voice, 1) | 2);
    return port_return(&port, voice, entry->edx);
}
