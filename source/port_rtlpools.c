#include "port_rtlpools.h"

/* JPEG row expansion and sample arrays, form refreshes and stream records. */

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

/* Original 0x444a80: as 0x444970 (the actor eax timed, stepped, placed and shaded by its y over
 * its scale), but at the path's end it is told 3 (0x4ac7b0), its y word +0x28 doubled, its shade
 * set to 0x10 and the handler 0x444b50 given (0x4ac8f0). edx kept. */
uint32_t vertrix_port_actor_shade_rise_444a80(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t actor = entry->eax;
    uint32_t eax;
    uint32_t edx;
    uint32_t steps;
    uint32_t done;
    uint32_t scale;
    LiftFlags flags = {0};
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ebx);
    port_set32(&port, ebp, -8u, entry->ecx);
    port_set32(&port, ebp, -0xcu, entry->edx);
    port_set32(&port, ebp, -0x10u, entry->esi);
    port_forward(&port, entry, 0x4ac500, actor, entry->edx, entry->ebx, actor);
    eax = port_forward(&port, entry, 0x4ac520, actor, vertrix_lift_edx, entry->ebx, actor);
    if (eax != 1)
    {
        return port_return(&port, eax, entry->edx);
    }
    steps = port_forward(&port, entry, 0x4ac540, actor, vertrix_lift_edx, entry->ebx, actor);
    port_forward(&port, entry, 0x4ac5b0, actor, vertrix_lift_edx, steps, actor);
    port_forward(&port, entry, 0x4ad060, actor, steps, steps, actor);
    done = port_forward(&port, entry, 0x4ad5e0, actor, steps, steps, actor);
    port_call_with(&port, 0x4ad260, actor, ebp - 0x18, ebp - 0x14, actor, done, entry->edi, ebp);
    port_set16(&port, actor, 0xe, port_u32(&port, ebp, -0x18u));
    port_set16(&port, actor, 0x16, port_u32(&port, ebp, -0x14u));
    eax = (uint32_t)((int32_t)port_u32(&port, actor, 0x28) >> 16) << 4;
    scale = port_u32(&port, actor, 0x70);
    edx = 0;
    lift_div1(32, scale, &eax, &edx, &flags);
    edx = 0x13 - eax;
    eax = edx;
    if ((int32_t)edx >= 0x10)
    {
        eax = 0x10;
    }
    port_set8(&port, actor, 0x44, eax);
    eax = port_u8(&port, actor, 0x44);
    if ((int32_t)eax <= 0)
    {
        eax = 0;
    }
    port_set8(&port, actor, 0x44, eax);
    if (done != 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_call_with(&port, 0x4ac7b0, actor, 3, scale, actor, done, entry->edi, ebp);
    edx = (vertrix_lift_edx & 0xffff0000u) | port_u16(&port, actor, 0x28);
    edx += edx;
    port_set16(&port, actor, 0x28, edx);
    port_set8(&port, actor, 0x44, 0x10);
    eax = port_call_with(&port, 0x4ac8f0, actor, 0x444b50, scale, actor, done, entry->edi, ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4c3780: the component edx (+4 into the decoder eax's +0x1c4 table: its expansions
 * +0x8c across, +0x96 down) of the input rows ebx expanded into the output rows ecx: each input
 * byte repeated across over the width +0x70, each row then copied down (0x4c9860), for the
 * decoder's +0x138 rows. */
uint32_t vertrix_port_jpeg_expand_rows_4c3780(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t component;
    uint32_t across;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t args[2];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x18u, port_u32(&port, entry->ecx, 0));
    component = port_u32(&port, decoder, 0x1c4) + port_u32(&port, entry->edx, 4);
    across = port_u8(&port, component, 0x8c);
    port_set32(&port, ebp, -0x1cu, port_u8(&port, component, 0x96));
    port_set32(&port, ebp, -0x10u, 0);
    if ((int32_t)port_u32(&port, decoder, 0x138) <= 0)
    {
        return port_return(&port, decoder, edx);
    }
    port_set32(&port, ebp, -0x14u, entry->ebx);
    port_set32(&port, ebp, -0x20u, port_u32(&port, ebp, -0x1cu) - 1);
    do
    {
        uint32_t row = port_u32(&port, ebp, -0x10u);
        uint32_t out = port_u32(&port, row * 4 + port_u32(&port, ebp, -0x18u), 0);
        uint32_t in = port_u32(&port, port_u32(&port, ebp, -0x14u), 0);
        uint32_t end = port_u32(&port, decoder, 0x70) + out;
        edx = end;
        port_set32(&port, ebp, -0xcu, end);
        while (out < end && !port.env.failed)
        {
            uint32_t c;
            in++;
            edx = across;
            c = port_u8(&port, in, -1u);
            if ((int32_t)across > 0)
            {
                do
                {
                    out++;
                    edx--;
                    port_set8(&port, out, -1u, c);
                } while ((int32_t)edx > 0 && !port.env.failed);
            }
            end = port_u32(&port, ebp, -0xcu);
        }
        if ((int32_t)port_u32(&port, ebp, -0x1cu) > 1)
        {
            uint32_t rows = port_u32(&port, ebp, -0x18u);
            args[0] = port_u32(&port, ebp, -0x20u);
            args[1] = port_u32(&port, decoder, 0x70);
            call_frame(&port, 0x4c9860, rows, row, rows, row + 1, across, decoder, ebp, args, 2);
            edx = vertrix_lift_edx;
        }
        port_set32(&port, ebp, -0x14u, port_u32(&port, ebp, -0x14u) + 4);
        eax = port_u32(&port, ebp, -0x1cu);
        port_set32(&port, ebp, -0x10u, row + eax);
    } while ((int32_t)port_u32(&port, ebp, -0x10u) < (int32_t)port_u32(&port, decoder, 0x138) &&
             !port.env.failed);
    return port_return(&port, eax, edx);
}

/* Original 0x4c4f60: the JPEG sample array of ecx rows of ebx bytes from the pool edx: the row
 * pointers (0x4c4d20) and the rows in chunks of at most 999999984 / ebx rows (0x4c4ea0; the
 * error 0x46 through the error manager when that is 0), the chunk size kept at +0x50 of the
 * memory manager +4. eax the row pointers. */
uint32_t vertrix_port_jpeg_alloc_sarray_4c4f60(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t memory;
    uint32_t eax = 0x3b9ac9f0;
    uint32_t edx = 0;
    uint32_t rows = entry->ecx;
    uint32_t done;
    LiftFlags flags = {0};
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0x1cu, entry->edx);
    port_set32(&port, ebp, -0xcu, entry->ebx);
    port_set32(&port, ebp, -0x18u, rows);
    memory = port_u32(&port, decoder, 4);
    lift_div1(32, entry->ebx, &eax, &edx, &flags);
    edx = eax;
    if ((int32_t)eax <= 0)
    {
        uint32_t manager;
        port_set32(&port, port_u32(&port, decoder, 0), 0x14, 0x46);
        manager = port_u32(&port, decoder, 0);
        port_call_with(&port, port_u32(&port, manager, 0), decoder, edx, manager, memory,
                       entry->esi, decoder, ebp);
        edx = vertrix_lift_edx;
    }
    rows = port_u32(&port, ebp, -0x18u);
    port_set32(&port, ebp, -0x14u, (int32_t)edx >= (int32_t)rows ? rows : edx);
    port_set32(&port, memory, 0x50, port_u32(&port, ebp, -0x14u));
    eax = port_call_with(&port, 0x4c4d20, decoder, port_u32(&port, ebp, -0x1cu), rows << 2, memory,
                         rows, decoder, ebp);
    port_set32(&port, ebp, -0x10u, eax);
    edx = vertrix_lift_edx;
    done = 0;
    if (port_u32(&port, ebp, -0x18u) == 0)
    {
        return port_return(&port, eax, edx);
    }
    do
    {
        uint32_t chunk = port_u32(&port, ebp, -0x18u) - done;
        uint32_t row;
        if (chunk > port_u32(&port, ebp, -0x14u))
        {
            chunk = port_u32(&port, ebp, -0x14u);
        }
        port_set32(&port, ebp, -0x14u, chunk);
        row = port_call_with(&port, 0x4c4ea0, decoder, port_u32(&port, ebp, -0x1cu),
                             port_u32(&port, ebp, -0xcu) * chunk, chunk, done, decoder, ebp);
        edx = chunk;
        if (chunk != 0)
        {
            uint32_t offset = done * 4;
            do
            {
                port_set32(&port, offset + port_u32(&port, ebp, -0x10u), 0, row);
                done++;
                edx--;
                offset += 4;
                row += port_u32(&port, ebp, -0xcu);
            } while (edx != 0 && !port.env.failed);
        }
    } while (done < port_u32(&port, ebp, -0x18u) && !port.env.failed);
    return port_return(&port, port_u32(&port, ebp, -0x10u), edx);
}

/* Original 0x4c5400: the JPEG virtual array edx moved between memory and its backing store (write
 * when ebx is set, method +0x34, else read +0x30): its rows from the first undone +0x18 in steps
 * of +0x14, each step clipped to the rows in use +0x10, the first unread +0x1c and the total +4,
 * with the byte offset growing by rows * +8. */
uint32_t vertrix_port_jpeg_sarray_io_4c5400(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t array = entry->edx;
    uint32_t done = 0;
    uint32_t eax;
    uint32_t edx = entry->edx;
    uint32_t args[1];
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->ecx);
    port_set32(&port, ebp, -8u, entry->esi);
    port_set32(&port, ebp, -0xcu, entry->edi);
    port_set32(&port, ebp, -0x18u, entry->eax);
    port_set32(&port, ebp, -0x24u, entry->ebx);
    eax = port_u32(&port, array, 8);
    port_set32(&port, ebp, -0x20u, eax);
    eax = port_u32(&port, array, 0x18) * port_u32(&port, ebp, -0x20u);
    port_set32(&port, ebp, -0x10u, eax);
    if ((int32_t)port_u32(&port, array, 0x10) <= 0)
    {
        return port_return(&port, eax, edx);
    }
    port_set32(&port, ebp, -0x1cu, array + 0x30);
    do
    {
        uint32_t ecx;
        uint32_t bytes;
        eax = port_u32(&port, array, 0x10) - done;
        ecx = port_u32(&port, array, 0x14);
        if ((int32_t)eax > (int32_t)ecx)
        {
            eax = ecx;
        }
        edx = port_u32(&port, array, 0x18) + done;
        ecx = port_u32(&port, array, 0x1c) - edx;
        if ((int32_t)eax >= (int32_t)ecx)
        {
            eax = ecx;
        }
        ecx = port_u32(&port, array, 4) - edx;
        edx = ecx;
        if ((int32_t)eax >= (int32_t)ecx)
        {
            eax = ecx;
        }
        if ((int32_t)eax <= 0)
        {
            break;
        }
        bytes = port_u32(&port, ebp, -0x20u) * eax;
        port_set32(&port, ebp, -0x14u, bytes);
        args[0] = bytes;
        call_frame(&port, port_u32(&port, array, port_u32(&port, ebp, -0x24u) != 0 ? 0x34 : 0x30),
                   port_u32(&port, ebp, -0x18u), port_u32(&port, ebp, -0x1cu),
                   port_u32(&port, port_u32(&port, array, 0), done * 4),
                   port_u32(&port, ebp, -0x10u), array, done, ebp, args, 1);
        port_set32(&port, ebp, -0x10u, port_u32(&port, ebp, -0x10u) + port_u32(&port, ebp, -0x14u));
        eax = port_u32(&port, array, 0x14);
        edx = port_u32(&port, array, 0x10);
        done += eax;
    } while ((int32_t)done < (int32_t)edx && !port.env.failed);
    return port_return(&port, eax, edx);
}

/* Original 0x4d5930: under the guard record 0x519840 a list in the frame (0x4d8340 with 0xa) of
 * the form eax's controls (+0x70 chain, next +0, control +8) whose method +0xd4 accepts them
 * (0x4d8510), then each listed one refreshed (method +0x5c, after 0x4d1840 when its +0x78 is
 * set); the list freed (0x4d83f0). eax the restored chain, edx kept. */
uint32_t vertrix_port_form_controls_refresh_4d5930(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x3c
    };
    Port port;
    uint32_t esp = entry->esp - BELOW;
    uint32_t record = esp + 0x1c;
    uint32_t form = entry->eax;
    uint32_t node;
    uint32_t ebx = entry->ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t eax;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, esp, 0x38, entry->ebx);
    port_set32(&port, esp, 0x34, entry->ecx);
    port_set32(&port, esp, 0x30, entry->edx);
    port_set32(&port, record, 0, port.env.chain);
    port.env.chain = record;
    port_set32(&port, esp, 0x20, 0x4ec1ec);
    port_set32(&port, esp, 0x24, 0x519840);
    port_set32(&port, esp, 0x28, 0);
    port_forward(&port, entry, 0x4d8340, esp, 0xa, ebx, form);
    port_set32(&port, esp, 0x28, 1);
    node = port_u32(&port, form + 0x6c, 4);
    ecx = node;
    while (ecx != 0 && !port.env.failed)
    {
        uint32_t control = port_u32(&port, ecx, 8);
        ebx = port_u32(&port, control, 0);
        ecx = port_u32(&port, ecx, 0);
        if (port_forward(&port, entry, port_u32(&port, ebx, 0xd4), control, control, ebx, ecx) != 0)
        {
            port_forward(&port, entry, 0x4d8510, esp, vertrix_lift_edx, ebx, ecx);
        }
    }
    edx = port_u32(&port, esp, 4);
    while (edx != 0 && !port.env.failed)
    {
        eax = port_u32(&port, edx, 8);
        edx = port_u32(&port, edx, 0);
        if (port_u32(&port, eax, 0x78) != 0)
        {
            eax = port_forward(&port, entry, 0x4d1840, eax, edx, ebx, ecx);
            edx = vertrix_lift_edx;
        }
        ecx = port_u32(&port, eax, 0);
        port_forward(&port, entry, port_u32(&port, ecx, 0x5c), eax, edx, ebx, ecx);
        edx = vertrix_lift_edx;
    }
    port_set32(&port, esp, 0x28, 0);
    port_forward(&port, entry, 0x4d83f0, esp, 0, ebx, ecx);
    eax = port_u32(&port, record, 0);
    port.env.chain = eax;
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4e7d80: a stream record taken under the lock hooks 0x507cb0/0x507cb4: the free list
 * 0x5c7764's head (its record +4 keeping the mode bits 0x4003 with 3), else a static record of
 * 0x505234..0x50543c (0x1a bytes) not in use (+0xc bits 0..1) with a 0x1d-byte block (0x4e7c90),
 * else a 0x37-byte block holding both (mode 0x4003); cleared (0x4eb5c0), its block linked into the
 * list 0x5c7760. On a failed allocation error 5 (0x4dae70) and 0. edx kept. */
uint32_t vertrix_port_rtl_stream_record_take_4e7d80(PORT_SIGNATURE)
{
    Port port;
    uint32_t block;
    uint32_t record = entry->ecx;
    uint32_t mode = entry->edi;
    uint32_t edx;
    uint32_t eax;
    port_open(&port, calls, services, globals, entry);
    port_call_with(&port, port_u32(&port, 0, 0x507cb0), entry->eax, entry->edx, entry->ebx,
                   entry->ecx, entry->esi, entry->edi, entry->ebp);
    edx = vertrix_lift_edx;
    block = port_u32(&port, 0, 0x5c7764);
    if (block != 0)
    {
        record = port_u32(&port, block, 4);
        mode = port_u32(&port, record, 0xc) & 0x4003;
        port_set32(&port, 0, 0x5c7764, port_u32(&port, block, 0));
        mode |= 3;
    }
    else
    {
        for (record = 0x505234; record < 0x50543c; record += 0x1a)
        {
            if ((port_u8(&port, record, 0xc) & 3) == 0)
            {
                break;
            }
        }
        if (record < 0x50543c)
        {
            block =
                port_call_with(&port, 0x4e7c90, 0x1d, edx, entry->ebx, record, 0, mode, entry->ebp);
            edx = vertrix_lift_edx;
            mode = 3;
        }
        else
        {
            mode = 0x4003;
            block =
                port_call_with(&port, 0x4e7c90, 0x37, edx, entry->ebx, record, 0, mode, entry->ebp);
            edx = vertrix_lift_edx;
            if (block != 0)
            {
                record = block + 0x1d;
            }
        }
        if (block == 0)
        {
            eax = port_call_with(&port, 0x4dae70, 5, edx, entry->ebx, record, 0, mode, entry->ebp);
            port_call_with(&port, port_u32(&port, 0, 0x507cb4), eax, vertrix_lift_edx, entry->ebx,
                           record, 0, mode, entry->ebp);
            return port_return(&port, 0, entry->edx);
        }
    }
    port_call_with(&port, 0x4eb5c0, record, 0, 0x1a, record, block, mode, entry->ebp);
    port_set32(&port, record, 0xc, mode);
    port_set32(&port, block, 4, record);
    eax = port_u32(&port, 0, 0x5c7760);
    port_set32(&port, record, 8, block);
    port_set32(&port, 0, 0x5c7760, block);
    port_set32(&port, block, 0, eax);
    port_call_with(&port, port_u32(&port, 0, 0x507cb4), eax, vertrix_lift_edx, 0x1a, record, block,
                   mode, entry->ebp);
    return port_return(&port, record, entry->edx);
}
