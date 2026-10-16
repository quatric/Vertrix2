#include "port_rtlwalks.h"

/* Window walks, AI slot choice, device stream opens and text reads. */

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

/* Original 0x4cbe80: the field +4 of the record 0x4ce780 gives. */
uint32_t vertrix_port_rtl_record_field_4cbe80(PORT_SIGNATURE)
{
    Port port;
    uint32_t record;
    port_open(&port, calls, services, globals, entry);
    record = port_forward(&port, entry, 0x4ce780, entry->eax, entry->edx, entry->ebx, entry->ecx);
    return port_return(&port, port_u32(&port, record, 4), vertrix_lift_edx);
}

/* Original 0x429000: the slot after the best of the 0x425e00 candidates of the list edx (with ebx)
 * by the score byte (ebx's table indexed by each kind, compared signed), ties by the kind's
 * priority (0x4f9318, signed), then a coin (0x4826c0 of 0x598d48 with 2 giving 1); 0 when the best
 * is the last or there is exactly one. edx as the comparisons leave it. */
uint32_t vertrix_port_ai_find_best_slot_429000(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t list = entry->edx;
    uint32_t count;
    uint32_t edx;
    uint32_t best;
    uint32_t i;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    count = port_call_with(&port, 0x425e00, list, entry->ebx, entry->ebx, entry->ecx, entry->esi,
                           list, ebp);
    edx = vertrix_lift_edx;
    if (count == 1)
    {
        return port_return(&port, 0, edx);
    }
    for (i = 0; i < count && !port.env.failed; i++)
    {
        uint32_t kind = port_u32(&port, list + i * 4, 0);
        port_set8(&port, i + ebp, -0x14u, port_u8(&port, edx, kind));
        kind = port_u32(&port, list + i * 4, 0);
        port_set8(&port, i + 1 + ebp, -0x1du, port_u8(&port, kind, 0x4f9318));
    }
    best = 0;
    for (i = 1; i < count && !port.env.failed; i++)
    {
        int8_t a = (int8_t)port_u8(&port, i + ebp, -0x14u);
        int8_t b = (int8_t)port_u8(&port, best + ebp, -0x14u);
        if (a > b)
        {
            best = i;
            continue;
        }
        if (a != b)
        {
            continue;
        }
        a = (int8_t)port_u8(&port, i + ebp, -0x1cu);
        b = (int8_t)port_u8(&port, best + ebp, -0x1cu);
        edx = (edx & 0xffff00ffu) | ((uint32_t)(uint8_t)b << 8);
        if (a > b)
        {
            best = i;
            continue;
        }
        if (a != b)
        {
            continue;
        }
        if ((port_call_with(&port, 0x4826c0, 0x598d48, 2, best, i, count, list, ebp) & 0xffff) == 1)
        {
            best = i;
        }
        edx = vertrix_lift_edx;
    }
    if (best + 1 == count)
    {
        return port_return(&port, 0, edx);
    }
    return port_return(&port, best + 1, edx);
}

/* The stream of the device eax opened (0x47f790 and 0x47f830): its name +0x3c widened into the
 * frame (0x47fc10, ecx -1), a 0x18-byte description (0x4eb5c0) of size 0x18, flags 1 and that
 * name handed to the object's method +0x50 with 0, 0 and 0x80000000; on success +0x44 set to
 * `mode` and 1, else 0x480080 of the error and 0. 0 when the device has no object. edx kept. */
static uint32_t device_open(PORT_SIGNATURE, uint32_t mode)
{
    enum
    {
        BELOW = 0x22c
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t device = entry->eax;
    uint32_t name = ebp - 0x228;
    uint32_t description = ebp - 0x28;
    uint32_t object;
    uint32_t methods;
    uint32_t args[5];
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    if (port_u32(&port, device, 0) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    port_call_with(&port, 0x47fc10, device, name, port_u32(&port, device, 0x3c), 0xffffffffu,
                   device, entry->edi, ebp);
    port_call_with(&port, 0x4eb5c0, description, 0, 0x18, 0x18, device, entry->edi, ebp);
    port_set32(&port, description, 0, 0x18);
    port_set32(&port, ebp, -0x24u, 1);
    port_set32(&port, ebp, -0x20u, name);
    object = port_u32(&port, device, 0);
    methods = port_u32(&port, object, 0);
    args[0] = object;
    args[1] = description;
    args[2] = 0;
    args[3] = 0;
    args[4] = 0x80000000u;
    result = call_frame(&port, port_u32(&port, methods, 0x50), object, methods, description, 0x18,
                        device, entry->edi, ebp, args, 5);
    if ((int32_t)result >= 0)
    {
        port_set32(&port, device, 0x44, mode);
        return port_return(&port, 1, entry->edx);
    }
    port_call_with(&port, 0x480080, device, result, description, 0x18, device, entry->edi, ebp);
    return port_return(&port, 0, entry->edx);
}

/* Original 0x47f790: the device's stream opened with +0x44 set to 0. */
uint32_t vertrix_port_device_stream_open_47f790(PORT_SIGNATURE)
{
    return device_open(calls, services, globals, entry, 0);
}

/* Original 0x47f830: the device's stream opened with +0x44 set to 1. */
uint32_t vertrix_port_device_stream_open_47f830(PORT_SIGNATURE)
{
    return device_open(calls, services, globals, entry, 1);
}

/* Original 0x4db8c0: the text 0x4db950 reads from edx (stack arguments edx, buffer, size) into the
 * string eax: through a 0x100-byte frame buffer (0x4ca370) when it fits with 2 to spare, else into
 * the string grown 0x100 bytes at a time (0x4ca670, 0x4ca670's buffer) until it does, then sized
 * by 0x4ca6c0 with -1. 1 when the last read gave more than 0 (signed), else 0. */
uint32_t vertrix_port_rtl_read_into_4db8c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x114
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - BELOW;
    uint32_t string = entry->eax;
    uint32_t source = entry->edx;
    uint32_t args[3];
    uint32_t got;
    uint32_t size;
    uint32_t ebx;
    uint32_t ecx;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x110, entry->ebx);
    port_set32(&port, esp, 0x10c, entry->ecx);
    port_set32(&port, esp, 0x108, entry->esi);
    port_set32(&port, esp, 0x104, entry->edi);
    port_set32(&port, esp, 0x100, entry->ebp);
    args[0] = source;
    args[1] = esp;
    args[2] = 0x100;
    got = call_frame(&port, 0x4db950, esp, source, entry->ebx, entry->ecx, entry->esi, string,
                     source, args, 3);
    if (0x100 - got > 2)
    {
        port_call_with(&port, 0x4ca370, string, esp, got, entry->ecx, entry->esi, string, source);
        return port_return(&port, (int32_t)got > 0, vertrix_lift_edx);
    }
    size = 0x100;
    ebx = 0xff;
    ecx = entry->ecx;
    do
    {
        uint32_t buffer;
        size += 0x100;
        ebx += 0x100;
        buffer = call_frame(&port, 0x4ca670, string, ebx, ebx, ecx, size, string, source, NULL, 0);
        args[0] = source;
        args[1] = buffer;
        args[2] = size;
        got = call_frame(&port, 0x4db950, buffer, vertrix_lift_edx, ebx, ecx, size, string, source,
                         args, 3);
        ecx = got;
    } while ((int32_t)(size - got) <= 2 && !port.env.failed);
    port_call_with(&port, 0x4ca6c0, string, 0xffffffffu, ebx, got, size, string, source);
    return port_return(&port, (int32_t)got > 0, vertrix_lift_edx);
}

/* Original 0x4d21d0: the window eax closed: after 0x4ce740 and 0x4dc030 (0x5c5c28, 0x4ccc40) of
 * its record, 0x4de810 of 0x5c7944 when it is the record's +0x1c; unless the application's byte
 * +0x14 is set and when 0x4cbe80's form is this window's (+0x1c), the hook +0x1c of 0x4dc030
 * (0x5c7b84, 0x4cc760); then 0x4d1ae0 (0x15, 0, 0, 1, 1 for its handle +0x1c) unless 0x4cccc0 has
 * bit 30, and 0x4cf850. edx kept. */
uint32_t vertrix_port_rtl_window_close_4d21d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t window = entry->eax;
    uint32_t eax;
    uint32_t ecx;
    uint32_t args[6];
    port_open(&port, calls, services, globals, entry);
    eax = port_forward(&port, entry, 0x4ce740, window, entry->edx, window, entry->ecx);
    ecx = port_u32(&port, eax, 4);
    eax = port_forward(&port, entry, 0x4dc030, 0x5c5c28, 0x4ccc40, window, ecx);
    if (window == port_u32(&port, ecx, 0x1c))
    {
        eax = port_forward(&port, entry, 0x4de810, 0x5c7944, vertrix_lift_edx, window, ecx);
    }
    eax = port_forward(&port, entry, 0x4ce740, eax, vertrix_lift_edx, window, ecx);
    if (port_u8(&port, eax, 0x14) == 0)
    {
        eax = port_forward(&port, entry, 0x4cbe80, eax, vertrix_lift_edx, window, ecx);
        if (eax != 0)
        {
            eax = port_forward(&port, entry, 0x4cbe80, eax, vertrix_lift_edx, window, ecx);
            if (window == port_u32(&port, eax, 0x1c))
            {
                eax = port_forward(&port, entry, 0x4dc030, 0x5c7b84, 0x4cc760, window, ecx);
                ecx = eax;
                if (port_u32(&port, eax, 0x1c) != 0)
                {
                    eax = port_forward(&port, entry, port_u32(&port, ecx, 0x1c), eax,
                                       vertrix_lift_edx, window, ecx);
                }
            }
        }
    }
    eax = port_forward(&port, entry, 0x4cccc0, window, vertrix_lift_edx, window, ecx);
    if ((eax & 0x40000000u) == 0)
    {
        args[0] = port_u32(&port, window, 0x1c);
        args[1] = 0x15;
        args[2] = 0;
        args[3] = 0;
        args[4] = 1;
        args[5] = 1;
        port_forward_stack(&port, entry, 0x4d1ae0, eax, vertrix_lift_edx, window, ecx, entry->esi,
                           args, 6);
    }
    eax = port_forward(&port, entry, 0x4cf850, window, vertrix_lift_edx, window, ecx);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4d1a50 (stdcall: parent, class, mode): the window of the class under the parent
 * (FindWindowExA-style import 0x4f1984 with the parent and class) or, failing that, searched
 * through its children (0x4f19e8 first child, 0x4f1a04 next with 2), recursively; a found window
 * with mode 0 is checked by 0x4cf8e0, else by 0x4cf910 (whose 0 goes on searching). */
uint32_t vertrix_port_rtl_window_find_4d1a50(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10
    };
    Port port;
    uint8_t stack[BELOW + 8 + 3 * 4];
    uint32_t parent;
    uint32_t name;
    uint32_t mode;
    uint32_t found;
    uint32_t child;
    uint32_t eax;
    uint32_t args[3];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, entry->esp, -4u, entry->ebx);
    port_set32(&port, entry->esp, -8u, entry->esi);
    port_set32(&port, entry->esp, -0xcu, entry->edi);
    port_set32(&port, entry->esp, -0x10u, entry->ebp);
    parent = port_u32(&port, entry->esp, 4);
    name = port_u32(&port, entry->esp, 8);
    mode = port_u32(&port, entry->esp, 0xc);
    args[0] = parent;
    args[1] = name;
    found = call_frame(&port, 0x4f1984, entry->eax, entry->edx, entry->ebx, entry->ecx, mode, name,
                       entry->ebp, args, 2);
    eax = found;
    child = found;
    if (found != 0)
    {
        args[0] = found;
        eax = call_frame(&port, 0x4f19e8, eax, vertrix_lift_edx, child, entry->ecx, mode, name,
                         found, args, 1);
        if (eax != 0)
        {
            args[0] = child;
            args[1] = name;
            args[2] = mode;
            eax = call_frame(&port, 0x4d1a50, eax, vertrix_lift_edx, child, entry->ecx, mode, name,
                             found, args, 3);
            if (eax != 0)
            {
                return port_return(&port, eax, vertrix_lift_edx);
            }
        }
        args[0] = found;
        if (mode == 0)
        {
            eax = call_frame(&port, 0x4cf8e0, eax, vertrix_lift_edx, child, entry->ecx, mode, name,
                             found, args, 1);
            return port_return(&port, eax, vertrix_lift_edx);
        }
        eax = call_frame(&port, 0x4cf910, eax, vertrix_lift_edx, child, entry->ecx, mode, name,
                         found, args, 1);
        if (eax != 0)
        {
            return port_return(&port, eax, vertrix_lift_edx);
        }
    }
    args[0] = parent;
    eax = call_frame(&port, 0x4f19e8, eax, vertrix_lift_edx, child, entry->ecx, mode, name, found,
                     args, 1);
    child = eax;
    while (child != 0 && !port.env.failed)
    {
        args[0] = child;
        args[1] = name;
        args[2] = mode;
        eax = call_frame(&port, 0x4d1a50, eax, vertrix_lift_edx, child, entry->ecx, mode, name,
                         found, args, 3);
        if (eax != 0)
        {
            return port_return(&port, eax, vertrix_lift_edx);
        }
        args[0] = child;
        args[1] = 2;
        eax = call_frame(&port, 0x4f1a04, eax, vertrix_lift_edx, child, entry->ecx, mode, name,
                         found, args, 2);
        child = eax;
    }
    return port_return(&port, 0, vertrix_lift_edx);
}
