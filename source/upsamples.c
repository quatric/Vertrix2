#include "upsamples.h"

/* The image decoder's separate upsampling step and its small pool allocation. */

static uint32_t call_frame(Port *port, uint32_t target, uint32_t eax, uint32_t edx, uint32_t ebx,
                           uint32_t ecx, uint32_t esi, uint32_t edi, uint32_t ebp,
                           const uint32_t *stack, unsigned count)
{
    return port_call_registers(port, target, eax, edx, ebx, ecx, esi, edi, ebp, stack, count);
}

/* Original 0x4c3610: the upsampler +0x1c4 of the decoder eax (ret 0xc, the output rows, the
 * output row counter and the rows available): when its row group is used up (+0x5c reaching
 * +0x138) every component (+0x24 of them, +0xd8 of 0x54 bytes) is upsampled by its method +0x34
 * from the input rows edx at the group counter [ebx] times its +0x64 into +0xc, and +0x5c
 * cleared; then as many rows as are left (+0x60), wanted and room for are converted (the colour
 * converter +0x1c8's +4) into the output at the counter, which, +0x5c and +0x60 step on; a used
 * up group steps [ebx]. */
uint32_t vertrix_port_separate_upsample_4c3610(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x28
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0xc];
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t input = entry->edx;
    uint32_t group = entry->ebx;
    uint32_t upsampler;
    uint32_t component;
    uint32_t number;
    uint32_t rows;
    uint32_t room;
    uint32_t converter;
    uint32_t counter;
    uint32_t args[1];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, ebp, -0x1cu, decoder);
    port_set32(&port, ebp, -0x20u, group);
    upsampler = port_u32(&port, decoder, 0x1c4);
    port_set32(&port, ebp, -0x24u, upsampler);
    if ((int32_t)port_u32(&port, decoder, 0x138) <= (int32_t)port_u32(&port, upsampler, 0x5c))
    {
        port_set32(&port, ebp, -0x18u, 0);
        component = port_u32(&port, decoder, 0xd8);
        port_set32(&port, ebp, -0x10u, input);
        port_set32(&port, ebp, -0x14u, upsampler + 0xc);
        port_set32(&port, ebp, -0xcu, upsampler);
        if ((int32_t)port_u32(&port, decoder, 0x24) > 0)
        {
            number = 0;
            do
            {
                port_call_with(
                    &port, port_u32(&port, upsampler, 0x34 + number * 4), decoder, component,
                    port_u32(&port, input, number * 4) +
                        port_u32(&port, group, 0) * port_u32(&port, upsampler, 0x64 + number * 4) *
                            4,
                    upsampler + 0xc + number * 4, component + 0x54, upsampler + number * 4, ebp);
                component += 0x54;
                ++number;
                port_set32(&port, ebp, -0x18u, number);
                port_set32(&port, ebp, -0x10u, input + number * 4);
                port_set32(&port, ebp, -0x14u, upsampler + 0xc + number * 4);
                port_set32(&port, ebp, -0xcu, upsampler + number * 4);
            } while ((int32_t)number < (int32_t)port_u32(&port, decoder, 0x24));
        }
        port_set32(&port, upsampler, 0x5c, 0);
    }
    rows = port_u32(&port, decoder, 0x138) - port_u32(&port, upsampler, 0x5c);
    if (rows > port_u32(&port, upsampler, 0x60))
    {
        rows = port_u32(&port, upsampler, 0x60);
    }
    counter = port_u32(&port, ebp, 0xc);
    room = port_u32(&port, ebp, 0x10) - port_u32(&port, counter, 0);
    port_set32(&port, ebp, 0x10, room);
    if (rows > room)
    {
        rows = room;
    }
    converter = port_u32(&port, decoder, 0x1c8);
    args[0] = rows;
    call_frame(&port, port_u32(&port, converter, 4), decoder, upsampler + 0xc,
               port_u32(&port, upsampler, 0x5c),
               port_u32(&port, counter, 0) * 4 + port_u32(&port, ebp, 8), rows, converter, ebp,
               args, 1);
    port_set32(&port, counter, 0, port_u32(&port, counter, 0) + rows);
    port_set32(&port, upsampler, 0x60, port_u32(&port, upsampler, 0x60) - rows);
    port_set32(&port, upsampler, 0x5c, port_u32(&port, upsampler, 0x5c) + rows);
    if ((int32_t)port_u32(&port, upsampler, 0x5c) >= (int32_t)port_u32(&port, decoder, 0x138))
    {
        port_set32(&port, group, 0, port_u32(&port, group, 0) + 1);
        return port_return(&port, group, decoder);
    }
    return port_return(&port, upsampler, decoder);
}

/* Original 0x4c4d20: the memory manager's small allocation of ebx bytes (rounded up to 8; over
 * 0x3b9ac9f0 is out of memory, 0x4c4d00 of 1) from the pool edx (0 or 1, else the error 0xe) of
 * the decoder eax: the first block of the pool's list (+0x34) with room, else a new one
 * (0x4c5bb0) of the size, its header of 16 and the pool's first (0x4fffb0) or later (0x4fffb8)
 * slop, held under 1000000000 and halved while the allocation fails (below 50, 0x4c4d00 of 2),
 * counted at +0x4c and linked at the list's end. The space, in eax and edx. */
uint32_t vertrix_port_pool_allocate_small_4c4d20(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t pool = entry->edx;
    uint32_t size = entry->ebx;
    uint32_t manager;
    uint32_t block;
    uint32_t previous = 0;
    uint32_t slop;
    uint32_t total;
    uint32_t space;
    uint32_t error;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x18u, pool);
    port_set32(&port, ebp, -0x10u, size);
    manager = port_u32(&port, decoder, 4);
    port_set32(&port, ebp, -0x1cu, manager);
    if (size > 0x3b9ac9f0)
    {
        port_call_with(&port, 0x4c4d00, decoder, 1, size, decoder, entry->esi, entry->edi, ebp);
    }
    if ((size & 7) != 0)
    {
        size += 8 - (size & 7);
        port_set32(&port, ebp, -0x10u, size);
    }
    if ((int32_t)pool < 0 || (int32_t)pool >= 2)
    {
        error = port_u32(&port, decoder, 0);
        port_set32(&port, error, 0x14, 0xe);
        port_set32(&port, error, 0x18, pool);
        error = port_u32(&port, decoder, 0);
        port_call_with(&port, port_u32(&port, error, 0), decoder, error, size, decoder, pool,
                       entry->edi, ebp);
    }
    block = port_u32(&port, manager, 0x34 + pool * 4);
    while (block != 0 && size > port_u32(&port, block, 8))
    {
        previous = block;
        block = port_u32(&port, block, 0);
    }
    if (block == 0)
    {
        port_set32(&port, ebp, -0x14u, size + 0x10);
        slop = port_u32(&port, 0, (previous != 0 ? 0x4fffb8 : 0x4fffb0) + pool * 4);
        if (slop > 0x3b9aca00 - (size + 0x10))
        {
            slop = 0x3b9aca00 - (size + 0x10);
        }
        for (;;)
        {
            total = size + 0x10 + slop;
            block = port_call_with(&port, 0x4c5bb0, decoder, total, slop, decoder, total, previous,
                                   ebp);
            if (block != 0)
            {
                break;
            }
            slop >>= 1;
            if (slop < 0x32)
            {
                port_call_with(&port, 0x4c4d00, decoder, 2, slop, decoder, total, previous, ebp);
            }
        }
        port_set32(&port, manager, 0x4c, port_u32(&port, manager, 0x4c) + total);
        port_set32(&port, block, 0, 0);
        port_set32(&port, block, 4, 0);
        port_set32(&port, block, 8, size + slop);
        if (previous != 0)
        {
            port_set32(&port, previous, 0, block);
        }
        else
        {
            port_set32(&port, manager, 0x34 + pool * 4, block);
        }
    }
    space = block + 0x10 + port_u32(&port, block, 4);
    port_set32(&port, block, 4, port_u32(&port, block, 4) + size);
    port_set32(&port, block, 8, port_u32(&port, block, 8) - size);
    return port_return(&port, space, space);
}
