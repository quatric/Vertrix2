#include "rtlarrays.h"

/* Array construction and the settings file reload. */

/* Original 0x417690: the settings path for the current slot (0x5330a8 by 0x532ba4, else the default
 * 0x50d65c when 0x45f590 rejects it) formatted with 0x4fcce0 into the frame (0x45f540), then
 * 0x478ae0, 0x478910 of it with 1, 0x478b40 of 0x532b98 and 0x4828f0 of 0x532b9c (its eax); edx as
 * restored from the frame. */
uint32_t vertrix_port_settings_reload_417690(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x110
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t buffer = ebp - 0x10c;
    uint32_t ebx;
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ebx);
    port_set32(&port, ebp, -8, entry->edx);
    ebx = port_u32(&port, port_u32(&port, 0, 0x532ba4) * 4 + 0x5330a8, 0);
    port_call_with(&port, 0x45f540, buffer, 0x4fcce0, ebx, entry->ecx, entry->esi, entry->edi, ebp);
    eax = port_call_with(&port, 0x45f590, buffer, vertrix_lift_edx, ebx, entry->ecx, entry->esi,
                         entry->edi, ebp);
    if (eax == 0)
    {
        ebx = 0x50d65c;
        eax = port_call_with(&port, 0x45f540, buffer, 0x4fcce0, ebx, entry->ecx, entry->esi,
                             entry->edi, ebp);
    }
    port_call_with(&port, 0x478ae0, eax, vertrix_lift_edx, ebx, entry->ecx, entry->esi, entry->edi,
                   ebp);
    port_call_with(&port, 0x478910, buffer, 1, ebx, entry->ecx, entry->esi, entry->edi, ebp);
    port_call_with(&port, 0x478b40, port_u32(&port, 0, 0x532b98), vertrix_lift_edx, ebx, entry->ecx,
                   entry->esi, entry->edi, ebp);
    eax = port_call_with(&port, 0x4828f0, port_u32(&port, 0, 0x532b9c), vertrix_lift_edx, ebx,
                         entry->ecx, entry->esi, entry->edi, ebp);
    return port_return(&port, eax, port_u32(&port, ebp, -8));
}

/* Original 0x4e87c1: edx elements of the array eax constructed in turn by the type ebx's routine
 * +4 (edx 0; size +0x10) under the guard record 0x51c060, then the frame record handed to
 * 0x4ce9fd; eax the array. */
uint32_t vertrix_port_rtl_array_construct_4e87c1(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x30
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t esp = entry->esp - 0x30;
    uint32_t array = entry->eax;
    uint32_t count = entry->edx;
    uint32_t routine;
    uint32_t size;
    uint32_t place = array;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x2c, entry->ecx);
    port_set32(&port, esp, 0x28, entry->esi);
    port_set32(&port, esp, 0x24, entry->edi);
    port_set32(&port, esp, 0, port.env.chain);
    port.env.chain = esp;
    port_set32(&port, esp, 4, 0x4ec1ec);
    port_set32(&port, esp, 8, 0x51c060);
    port_set32(&port, esp, 0xc, 0);
    port_set32(&port, esp, 0x14, 1);
    port_set32(&port, esp, 0x18, 0);
    port_set32(&port, esp, 0x1c, entry->ebx);
    port_set32(&port, esp, 0x20, array);
    port_set32(&port, esp, 0xc, 1);
    routine = port_u32(&port, entry->ebx, 4);
    size = port_u32(&port, entry->ebx, 0x10);
    while (count > port_u32(&port, esp, 0x18) && !port.env.failed)
    {
        port_call_with(&port, routine, place, 0, routine, place, count, size, entry->ebp);
        port_set32(&port, esp, 0x18, port_u32(&port, esp, 0x18) + 1);
        place += size;
    }
    port_set32(&port, esp, 0x14, 0);
    array = port_u32(&port, esp, 0x20);
    port_set32(&port, esp, 0xc, 0);
    port_call_with(&port, 0x4ce9fd, esp + 0x14, 0, routine, array, count, size, entry->ebp);
    port_set32(&port, esp, 0xc, 0);
    port.env.chain = port_u32(&port, esp, 0);
    return port_return(&port, array, vertrix_lift_edx);
}
