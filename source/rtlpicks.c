#include "rtlpicks.h"

/* Random picks from tables, guarded constructions, device releases, row copies and orbit points. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* A random one (0x4826c0 of 0x598d30 with the count) of the indices 0..0x12 whose dword in the
 * table `table` is 0, listed in the frame; 0 when there is none. edx kept. */
static uint32_t random_empty(PORT_SIGNATURE, uint32_t table)
{
    enum
    {
        BELOW = 0x60
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t count = 0;
    uint32_t offset = 0;
    uint32_t index;
    uint32_t pick;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    for (index = 0; index < 0x13; index++)
    {
        if (port_u32(&port, index * 4, table) == 0)
        {
            offset += 4;
            count++;
            port_set32(&port, offset + ebp, -0x60u, index);
        }
    }
    if (count == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    pick =
        port_call_with(&port, 0x4826c0, 0x598d30, count & 0xffff, count, 0x4c, 0, entry->edi, ebp);
    pick = port_u32(&port, ebp, (pick & 0xffff) * 4 - 0x5c);
    return port_return(&port, pick, entry->edx);
}

/* Original 0x417e60: a random empty slot of the table 0x5344a4 (19 dwords). */
uint32_t vertrix_port_table_random_empty_417e60(PORT_SIGNATURE)
{
    return random_empty(calls, services, globals, entry, 0x5344a4);
}

/* Original 0x417ed0: a random empty slot of the table 0x5344f0 (19 dwords). */
uint32_t vertrix_port_table_random_empty_417ed0(PORT_SIGNATURE)
{
    return random_empty(calls, services, globals, entry, 0x5344f0);
}

/* Original 0x476160: under the guard record 0x516500 the string edx emptied (0x4ca060, called with
 * eax the entry's offset bx * 12) and set (0x4ca370) to the entry bx of the 12-byte table 0x4fd800;
 * eax edx. */
uint32_t vertrix_port_string_table_assign_476160(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t string = entry->edx;
    uint32_t record = ebp - 0x20;
    uint32_t name = (entry->ebx & 0xffff) * 12 + 0x4fd800;
    uint32_t empty;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x1cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x18u, 0x516500);
    port_set32(&port, ebp, -0x14u, 0);
    empty = port_call_with(&port, 0x4ca060, (entry->ebx & 0xffff) * 12, 0x4ec1ec, name, 0x516500,
                           string, 0, ebp);
    port_set32(&port, string, 0, port_u32(&port, empty, 0));
    port_call_with(&port, 0x4ca370, string, name, name, 0x516500, string, 0, ebp);
    port.env.chain = port_u32(&port, ebp, -0x20u);
    return port_return(&port, string, vertrix_lift_edx);
}

/* Original 0x47e9b0: the device eax closed: 0x47f3d0; its object (+0) told to stop (method +0x60
 * with 0); the buffer +0x1bc stopped (method +0x24 with 0), released (+8) and cleared; 0x47ea20;
 * then the object released and cleared. eax as the last call leaves it, edx kept. */
uint32_t vertrix_port_device_close_47e9b0(PORT_SIGNATURE)
{
    Port port;
    uint32_t device = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = entry->esi;
    uint32_t object;
    uint32_t args[2];
    port_open(&port, calls, services, globals, entry);
    eax = port_call_with(&port, 0x47f3d0, device, entry->edx, device, ecx, esi, entry->edi,
                         entry->ebp);
    object = port_u32(&port, device, 0);
    edx = object;
    if (object != 0)
    {
        edx = port_u32(&port, object, 0);
        args[0] = object;
        args[1] = 0;
        eax = call_frame(&port, port_u32(&port, edx, 0x60), object, edx, device, ecx, esi,
                         entry->edi, entry->ebp, args, 2);
        edx = vertrix_lift_edx;
    }
    ecx = port_u32(&port, device, 0x1bc);
    if (ecx != 0)
    {
        edx = port_u32(&port, ecx, 0);
        args[0] = ecx;
        args[1] = 0;
        eax = call_frame(&port, port_u32(&port, edx, 0x24), eax, edx, device, ecx, esi, entry->edi,
                         entry->ebp, args, 2);
        edx = vertrix_lift_edx;
    }
    esi = port_u32(&port, device, 0x1bc);
    if (esi != 0)
    {
        edx = port_u32(&port, esi, 0);
        args[0] = esi;
        eax = call_frame(&port, port_u32(&port, edx, 8), eax, edx, device, ecx, esi, entry->edi,
                         entry->ebp, args, 1);
        edx = vertrix_lift_edx;
        port_set32(&port, device, 0x1bc, 0);
    }
    eax = port_call_with(&port, 0x47ea20, device, edx, device, ecx, esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    object = port_u32(&port, device, 0);
    if (object != 0)
    {
        edx = port_u32(&port, object, 0);
        args[0] = object;
        eax = call_frame(&port, port_u32(&port, edx, 8), eax, edx, device, ecx, esi, object,
                         entry->ebp, args, 1);
        port_set32(&port, device, 0, 0);
    }
    return port_return(&port, eax, entry->edx);
}

/* Original 0x47f280: the entry edx of the chain 0x47fbb0 gives in edx for the list +0xc of eax:
 * the 16 bytes 0x47fbb0 left in the frame go to +0xa4 first, then that entry's +8 (16 bytes) and
 * 1, or 0 when the chain is shorter; edx the entry (0 when none). */
uint32_t vertrix_port_object_pick_entry_47f280(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t object = entry->eax;
    uint32_t buffer = ebp - 0x24;
    uint32_t wanted = entry->edx;
    uint32_t node;
    uint32_t index;
    uint32_t i;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x14u, object);
    port_call_with(&port, 0x47fbb0, object, port_u32(&port, object, 0xc), wanted, entry->ecx,
                   buffer, object, ebp);
    node = vertrix_lift_edx;
    for (i = 0; i < 16; i += 4)
    {
        port_set32(&port, object + 0xa4 + i, 0, port_u32(&port, buffer + i, 0));
    }
    for (index = 0; node != 0 && !port.env.failed; index++)
    {
        if (index == wanted)
        {
            uint32_t target = port_u32(&port, ebp, -0x14u) + 0xa4;
            for (i = 0; i < 16; i += 4)
            {
                port_set32(&port, target + i, 0, port_u32(&port, node + 8 + i, 0));
            }
            return port_return(&port, 1, node);
        }
        node = port_u32(&port, node, 0x60);
    }
    return port_return(&port, 0, node);
}

/* Original 0x4896f0: the path edx copied (two bytes a step, to its terminator) to 0x5ba0e0, split
 * by 0x4daae8 (with 0x5ba1e8 and 0x5ba1f0, ecx 0 and a 0 stack argument), then the string eax set
 * to the part 0x5ba1e8 (0x4ca370) and given the part 0x5ba1f0 (0x4ca600). */
uint32_t vertrix_port_path_split_a_4896f0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t from = entry->edx;
    uint32_t to = 0x5ba0e0;
    uint32_t args[1] = {0};
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->esi);
    port_set32(&port, ebp, -0x10u, entry->edi);
    port_set32(&port, ebp, -0x14u, entry->eax);
    port_set32(&port, ebp, -0x18u, to);
    for (;;)
    {
        uint32_t c = port_u8(&port, from, 0);
        port_set8(&port, to, 0, c);
        if (c == 0 || port.env.failed)
        {
            break;
        }
        c = port_u8(&port, from, 1);
        from += 2;
        port_set8(&port, to, 1, c);
        to += 2;
        if (c == 0)
        {
            break;
        }
    }
    call_frame(&port, 0x4daae8, 0x5ba0e0, 0x5ba1e8, 0x5ba1f0, 0, from, 0x5ba0e0, ebp, args, 1);
    port_call_with(&port, 0x4ca370, port_u32(&port, ebp, -0x14u), 0x5ba1e8, 0x5ba1f0, 0, from,
                   0x5ba0e0, ebp);
    result = port_call_with(&port, 0x4ca600, port_u32(&port, ebp, -0x14u), 0x5ba1f0, 0x5ba1f0, 0,
                            from, 0x5ba0e0, ebp);
    return port_return(&port, result, vertrix_lift_edx);
}

/* Original 0x4c9860 (ret 8: rows, bytes): `bytes` copied (rep movsd, rep movsb) from each row
 * pointer of eax from index edx on to each row pointer of ebx from index ecx on. eax the byte
 * count and edx 0 after a copy; with no rows eax and edx (the rows) as given. */
uint32_t vertrix_port_rtl_copy_rows_4c9860(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8 + 2 * 4];
    uint32_t ebp = entry->esp - 4;
    uint32_t source;
    uint32_t target = entry->ebx + (entry->ecx << 2);
    int32_t rows;
    uint32_t bytes;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 2);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    rows = (int32_t)port_u32(&port, ebp, 8);
    port_set32(&port, ebp, -0xcu, entry->eax);
    bytes = port_u32(&port, ebp, 0xc);
    port_set32(&port, ebp, -0x10u, bytes);
    source = entry->eax + (entry->edx << 2);
    port_set32(&port, ebp, -0xcu, source);
    if (rows <= 0)
    {
        return port_return(&port, entry->eax, (uint32_t)rows);
    }
    do
    {
        uint32_t from;
        uint32_t to;
        uint32_t place = port_u32(&port, ebp, -0xcu);
        uint32_t i;
        bytes = port_u32(&port, ebp, -0x10u);
        rows--;
        to = port_u32(&port, target, 0);
        target += 4;
        from = port_u32(&port, place, 0);
        port_set32(&port, ebp, -0xcu, place + 4);
        for (i = 0; i < (bytes >> 2); i++)
        {
            port_set32(&port, to + i * 4, 0, port_u32(&port, from + i * 4, 0));
        }
        for (i = bytes & ~3u; i < (bytes & ~3u) + (bytes & 3); i++)
        {
            port_set8(&port, to + i, 0, port_u8(&port, from + i, 0));
        }
    } while (rows > 0 && !port.env.failed);
    return port_return(&port, bytes, 0);
}

/* Original 0x481f30: under the guard record 0x516b20 the object of class eax made by 0x4ccf3b
 * (edx 0xa, ebx 0x516ba0) given the handler 0x516b84 (+0x20c) and set up by 0x482050; eax the edx
 * 0x482050 leaves, edx kept. */
uint32_t vertrix_port_object_create_with_class_481f30(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x34
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t record = ebp - 0x30;
    uint32_t object;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, ebp, -0x2cu, 0x4ec1ec);
    port_set32(&port, ebp, -0x28u, 0x516b20);
    port_set32(&port, ebp, -0x24u, 0);
    port_set8(&port, ebp, -0x18u, 0);
    port_set32(&port, ebp, -0x1cu, entry->eax);
    object =
        port_call_with(&port, 0x4ccf3b, entry->eax, 0xa, 0x516ba0, entry->eax, 0, entry->edi, ebp);
    port_set32(&port, object, 0x20c, 0x516b84);
    port_call_with(&port, 0x482050, object, object, 0x516ba0, entry->eax, 0, entry->edi, ebp);
    port.env.chain = port_u32(&port, record, 0);
    return port_return(&port, vertrix_lift_edx, entry->edx);
}

/* Original 0x4ad3c0: the actor eax's point on its double orbit: 0x4ad210 of its angle +0x38 (the
 * word above 16 bits) into 0x5bb620/0x5bb624, then 0x4ad1c0 of the angle +0x28 plus that x (also
 * stored at 0x5bb628); the word +0x2c plus x into edx's word, +0x2e less y into ebx's word. eax
 * edx; edx the second difference over the high halves left in the registers. */
uint32_t vertrix_port_actor_double_orbit_point_4ad3c0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t args[1] = {0x5bb624};
    uint32_t angle;
    uint32_t ebx;
    uint32_t edx;
    uint32_t ecx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x10u, entry->edx);
    angle = (uint32_t)((int32_t)port_u32(&port, actor, 0x38) >> 16);
    call_frame(&port, 0x4ad210, actor, angle, angle, 0x5bb620, actor, entry->ebx, ebp, args, 1);
    angle = (uint32_t)((int32_t)port_u32(&port, actor, 0x28) >> 16);
    angle += port_u32(&port, 0, 0x5bb620);
    port_set32(&port, 0, 0x5bb628, angle);
    call_frame(&port, 0x4ad1c0, actor, angle, angle, 0x5bb620, actor, entry->ebx, ebp, args, 1);
    ebx = (angle & 0xffff0000u) | port_u16(&port, 0, 0x5bb620);
    edx = (vertrix_lift_edx & 0xffff0000u) | port_u16(&port, actor, 0x2c);
    edx += ebx;
    port_set16(&port, port_u32(&port, ebp, -0x10u), 0, edx);
    ecx = 0x5b0000u | port_u16(&port, 0, 0x5bb624);
    edx = (edx & 0xffff0000u) | port_u16(&port, actor, 0x2e);
    edx -= ecx;
    port_set16(&port, entry->ebx, 0, edx);
    return port_return(&port, port_u32(&port, ebp, -0x10u), edx);
}

/* Original 0x4bb4a0 (ret 4: rows): each byte of the decoder eax's width +0x70 from the input rows
 * edx (from index ebx on) tripled into the output rows ecx, for the given number of rows. eax and
 * edx as the last row leaves them. */
uint32_t vertrix_port_jpeg_rows_triple_4bb4a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    uint32_t esp = entry->esp - BELOW;
    uint32_t esi = entry->ecx;
    uint32_t edi = entry->ebx * 4;
    uint32_t eax;
    uint32_t edx = entry->edx;
    int32_t rows;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    port_set32(&port, esp, 0x14, entry->esi);
    port_set32(&port, esp, 0x10, entry->edi);
    port_set32(&port, esp, 0xc, entry->ebp);
    rows = (int32_t)port_u32(&port, esp, 0x1c);
    port_set32(&port, esp, 0, entry->edx);
    port_set32(&port, esp, 8, entry->ebx);
    eax = port_u32(&port, entry->eax, 0x70);
    port_set32(&port, esp, 4, eax);
    for (rows--; rows >= 0 && !port.env.failed; rows--)
    {
        uint32_t row;
        uint32_t width;
        eax = port_u32(&port, esp, 0);
        edx = edi;
        esi += 4;
        port_set32(&port, esp, 8, port_u32(&port, esp, 8) + 1);
        eax = port_u32(&port, eax, 0);
        edi += 4;
        row = port_u32(&port, edx, eax);
        edx = port_u32(&port, esp, 4);
        eax = port_u32(&port, esi, -4u);
        if (edx == 0)
        {
            continue;
        }
        width = port_u32(&port, esp, 4);
        for (edx = row;;)
        {
            uint32_t c;
            eax += 3;
            c = port_u8(&port, edx, 0);
            port_set8(&port, eax, -1u, c);
            port_set8(&port, eax, -2u, c);
            edx++;
            port_set8(&port, eax, -3u, c);
            if (edx >= width + row || port.env.failed)
            {
                break;
            }
        }
    }
    return port_return(&port, eax, edx);
}
