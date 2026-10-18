#include "rtlsundry.h"

/* Sundry runtime library and decoder routines. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4ec180: memcmp of ebx bytes at eax and edx (`repe cmpsb`): 0 when equal, else -1 or 1
 * by the first differing bytes; edx kept. */
uint32_t vertrix_port_rtl_memory_compare_4ec180(PORT_SIGNATURE)
{
    Port port;
    uint32_t at;
    uint32_t result = 0;
    port_open(&port, calls, services, globals, entry);
    for (at = 0; at != entry->ebx && !port.env.failed; at++)
    {
        uint32_t left = port_u8(&port, entry->eax, at);
        uint32_t right = port_u8(&port, entry->edx, at);
        if (left != right)
        {
            result = left < right ? 0xffffffffu : 1;
            break;
        }
    }
    return port_return(&port, result, entry->edx);
}

/* Original 0x4bc6c0: the decoder eax's entropy decoder (0xe8 bytes, pool 1, from the memory
 * manager +4's method +0) kept in +0x1bc with its methods 0x4bba40 and 0x4bc1e0 and the four
 * table pointers +0x28 and +0x38 cleared; eax past them, edx kept. */
uint32_t vertrix_port_jpeg_entropy_init_4bc6c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t cinfo = entry->eax;
    uint32_t memory;
    uint32_t decoder;
    uint32_t place;
    port_open(&port, calls, services, globals, entry);
    memory = port_u32(&port, cinfo, 4);
    decoder = port_call_with(&port, port_u32(&port, memory, 0), cinfo, 1, 0xe8, memory, cinfo,
                             entry->edi, entry->ebp);
    port_set32(&port, cinfo, 0x1bc, decoder);
    port_set32(&port, decoder, 0, 0x4bba40);
    port_set32(&port, decoder, 4, 0x4bc1e0);
    place = decoder;
    do
    {
        place += 4;
        port_set32(&port, place, 0x34, 0);
        port_set32(&port, place, 0x24, port_u32(&port, place, 0x34));
    } while (place != decoder + 0x10 && !port.env.failed);
    return port_return(&port, place, entry->edx);
}

/* Original 0x4c3e60: the object eax's class method +0xc words its message into the frame, printed
 * by 0x4dabe0 to the stream 0x505268 with the format 0x511155; edx as restored from the frame. */
uint32_t vertrix_port_jpeg_output_message_4c3e60(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xd4
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t methods;
    uint32_t args[3];
    uint32_t eax;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ecx);
    port_set32(&port, ebp, -8, entry->edx);
    methods = port_u32(&port, entry->eax, 0);
    port_call_with(&port, port_u32(&port, methods, 0xc), entry->eax, ebp - 0xd0, entry->ebx,
                   methods, entry->esi, entry->edi, ebp);
    args[0] = 0x505268;
    args[1] = 0x511155;
    args[2] = ebp - 0xd0;
    eax = call_frame(&port, 0x4dabe0, ebp - 0xd0, vertrix_lift_edx, entry->ebx, methods, entry->esi,
                     entry->edi, ebp, args, 3);
    return port_return(&port, eax, port_u32(&port, ebp, -8));
}

/* Original 0x4e8650: the list 0x5c8aa0 (next +0) freed node by node (0x4ea190), each node's block
 * +8 first when it has a size +0xc; edx kept. */
uint32_t vertrix_port_rtl_list_free_4e8650(PORT_SIGNATURE)
{
    Port port;
    uint32_t eax = entry->eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    port_open(&port, calls, services, globals, entry);
    edx = port_u32(&port, 0, 0x5c8aa0);
    while (edx != 0 && !port.env.failed)
    {
        ecx = port_u32(&port, edx, 0xc);
        ebx = port_u32(&port, edx, 0);
        if (ecx != 0)
        {
            port_call_with(&port, 0x4ea190, port_u32(&port, edx, 8), edx, ebx, ecx, entry->esi,
                           entry->edi, entry->ebp);
            edx = vertrix_lift_edx;
        }
        eax =
            port_call_with(&port, 0x4ea190, edx, edx, ebx, ecx, entry->esi, entry->edi, entry->ebp);
        edx = ebx;
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x424180: a guard record (0x513f54) linked into the exception chain and unlinked again;
 * eax 0x418970, edx kept. */
uint32_t vertrix_port_guard_noop_424180(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4, entry->ebx);
    port_set32(&port, ebp, -8, entry->ecx);
    port_set32(&port, ebp, -0xc, entry->edx);
    port_set32(&port, ebp, -0x20, port.env.chain);
    port_set32(&port, ebp, -0x1c, 0x4ec1ec);
    port_set32(&port, ebp, -0x18, 0x513f54);
    port_set32(&port, ebp, -0x14, 0);
    port.env.chain = port_u32(&port, ebp, -0x20);
    return port_return(&port, 0x418970, port_u32(&port, ebp, -0xc));
}

/* Original 0x4e5808: the lock 0x5c8930 left once (its count +0xc down); reaching 0 clears its
 * owner +8 and releases its section +0 (0x4f1c40); edx kept. */
uint32_t vertrix_port_rtl_lock_leave_4e5808(PORT_SIGNATURE)
{
    Port port;
    uint32_t lock = 0x5c8930;
    uint32_t count;
    uint32_t eax = lock;
    uint32_t args[1];
    port_open(&port, calls, services, globals, entry);
    count = port_u32(&port, lock, 0xc);
    if (count != 0)
    {
        port_set32(&port, lock, 0xc, count - 1);
        if (count - 1 == 0)
        {
            args[0] = port_u32(&port, lock, 0);
            port_set32(&port, lock, 8, 0);
            eax = call_frame(&port, 0x4f1c40, lock, count, 0, entry->ecx, args[0], entry->edi,
                             entry->ebp, args, 1);
        }
    }
    return port_return(&port, eax, entry->edx);
}
