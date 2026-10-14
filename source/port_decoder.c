#include "port_decoder.h"

/* Picture decoder input, buffer setup, restart markers, upsampling and a runtime lookup. */

/* A call handing the callee esi, edi and ebp as given and `count` stack dwords. */
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

/* Original 0x4b9c20: the decoder's source (+0x18) refills its buffer (+0x20) with up to 0x1000
 * bytes of the stream +0x1c (0x48a9d0); at the stream's end it warns (0x2a, when +0x24 is set,
 * by the error handler +0 of +0), warns 0x78 (its +4 with -1) and supplies the end marker ff d9
 * (0x48a8a0 with 2). The buffer start (+0) and count (+4) are set, +0x24 0. 1. */
uint32_t vertrix_port_decoder_fill_input_4b9c20(PORT_SIGNATURE)
{
    Port port;
    uint32_t decoder = entry->eax;
    uint32_t source;
    uint32_t count;
    uint32_t ecx = 0x1000;
    port_open(&port, calls, services, globals, entry);
    source = port_u32(&port, decoder, 0x18);
    count = port_call_with(&port, 0x48a9d0, port_u32(&port, source, 0x1c),
                           port_u32(&port, source, 0x20), 1, ecx, source, decoder, entry->ebp);
    if (count == 0)
    {
        uint32_t handler;
        if (port_u32(&port, source, 0x24) != 0)
        {
            port_set32(&port, port_u32(&port, decoder, 0), 0x14, 0x2a);
            handler = port_u32(&port, decoder, 0);
            port_call_with(&port, port_u32(&port, handler, 0), decoder, handler, 1, ecx, source,
                           decoder, entry->ebp);
        }
        port_set32(&port, port_u32(&port, decoder, 0), 0x14, 0x78);
        ecx = port_u32(&port, decoder, 0);
        port_call_with(&port, port_u32(&port, ecx, 4), decoder, 0xffffffffu, 1, ecx, source,
                       decoder, entry->ebp);
        port_set8(&port, port_u32(&port, source, 0x20), 0, 0xff);
        port_set8(&port, port_u32(&port, source, 0x20), 1, 0xd9);
        port_call_with(&port, 0x48a8a0, port_u32(&port, source, 0x1c), 2, 1, ecx, source, decoder,
                       entry->ebp);
        count = vertrix_lift_edx;
    }
    port_set32(&port, source, 0x24, 0);
    port_set32(&port, source, 4, count);
    port_set32(&port, source, 0, port_u32(&port, source, 0x20));
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4bb9b0: the decoder's coefficient controller (0x54 bytes from its allocator +4,
 * methods 0x4bb870) at +0x1c0; each component (+0x24 of them, 0x54 apart from +0xd8) takes a
 * cleared 0x100 byte table (+0x50) and the controller's slot for it -1. */
uint32_t vertrix_port_decoder_coefficients_setup_4bb9b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t allocator;
    uint32_t controller;
    uint32_t component;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    allocator = port_u32(&port, decoder, 4);
    controller = port_call_with(&port, port_u32(&port, allocator, 0), decoder, 1, 0x54, decoder,
                                allocator, entry->edi, ebp);
    port_set32(&port, decoder, 0x1c0, controller);
    port_set32(&port, controller, 0, 0x4bb870);
    port_set32(&port, ebp, -0x1cu, 0);
    component = port_u32(&port, decoder, 0xd8);
    result = controller;
    if ((int32_t)port_u32(&port, decoder, 0x24) <= 0)
    {
        return port_return(&port, result, entry->edx);
    }
    port_set32(&port, ebp, -0x18u, controller);
    do
    {
        uint32_t table;
        uint32_t slot;
        allocator = port_u32(&port, decoder, 4);
        table = port_call_with(&port, port_u32(&port, allocator, 0), decoder, 1, 0x100, decoder,
                               component, allocator, ebp);
        port_set32(&port, component, 0x50, table);
        port_call_with(&port, 0x4eb5c0, table, 0, 0x100, decoder, component, allocator, ebp);
        slot = port_u32(&port, ebp, -0x18u);
        component += 0x54;
        port_set32(&port, slot, 0x2c, 0xffffffffu);
        port_set32(&port, ebp, -0x18u, slot + 4);
        result = port_u32(&port, ebp, -0x1cu) + 1;
        port_set32(&port, ebp, -0x1cu, result);
    } while ((int32_t)result < (int32_t)port_u32(&port, decoder, 0x24));
    return port_return(&port, result, entry->edx);
}

/* Original 0x4c07d0: the decoder's restart marker: without one (+0x1a0) read (0x4bf770 gives 0)
 * nothing; the expected one (0xd0 plus the marker reader's +0x14) is taken (warning 0x62 with
 * the number by the handler's +4 with 3) and cleared; another goes to the source's resync (+0x14
 * of +0x18), which must give 1. The next number (mod 8) is expected. 1. */
uint32_t vertrix_port_decoder_read_restart_4c07d0(PORT_SIGNATURE)
{
    Port port;
    uint32_t decoder = entry->eax;
    uint32_t reader;
    uint32_t marker;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, decoder, 0x1a0) == 0)
    {
        result = port_forward(&port, entry, 0x4bf770, decoder, entry->edx, entry->ebx, decoder);
        if (result == 0)
        {
            return port_return(&port, result, entry->edx);
        }
    }
    reader = port_u32(&port, decoder, 0x1b8);
    marker = port_u32(&port, decoder, 0x1a0);
    if (port_u32(&port, reader, 0x14) + 0xd0 == marker)
    {
        uint32_t handler;
        port_set32(&port, port_u32(&port, decoder, 0), 0x14, 0x62);
        port_set32(&port, port_u32(&port, decoder, 0), 0x18,
                   port_u32(&port, port_u32(&port, decoder, 0x1b8), 0x14));
        handler = port_u32(&port, decoder, 0);
        port_forward(&port, entry, port_u32(&port, handler, 4), decoder, 3, handler, decoder);
        port_set32(&port, decoder, 0x1a0, 0);
    }
    else
    {
        uint32_t source = port_u32(&port, decoder, 0x18);
        result = port_forward(&port, entry, port_u32(&port, source, 0x14), decoder,
                              port_u32(&port, reader, 0x14), source, decoder);
        if (result == 0)
        {
            return port_return(&port, result, entry->edx);
        }
    }
    reader = port_u32(&port, decoder, 0x1b8);
    port_set32(&port, reader, 0x14, (port_u32(&port, reader, 0x14) + 1) & 7);
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4c26f0: the entropy decoder (+0x1bc) restarts: its unused bits (+0x10, an eighth
 * rounded toward 0) are given back to the marker reader's discarded count (+0x18 of +0x1b8) and
 * cleared; when the reader's restart (+8) gives 1 the components' (+0x148) last values (+0x18
 * on) and +0x14 are cleared, +0x28 takes the restart interval +0x114 and, without a pending
 * marker (+0x1a0), +8 is 0. */
uint32_t vertrix_port_decoder_process_restart_4c26f0(PORT_SIGNATURE)
{
    Port port;
    uint32_t decoder = entry->eax;
    uint32_t entropy;
    uint32_t reader;
    uint32_t methods;
    uint32_t k;
    port_open(&port, calls, services, globals, entry);
    entropy = port_u32(&port, decoder, 0x1bc);
    reader = port_u32(&port, decoder, 0x1b8);
    port_set32(&port, reader, 0x18,
               port_u32(&port, reader, 0x18) +
                   (uint32_t)((int32_t)port_u32(&port, entropy, 0x10) / 8));
    port_set32(&port, entropy, 0x10, 0);
    methods = port_u32(&port, decoder, 0x1b8);
    if (port_forward_esi(&port, entry, port_u32(&port, methods, 8), decoder, methods, entropy,
                         decoder, reader) == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    for (k = 0; (int32_t)k < (int32_t)port_u32(&port, decoder, 0x148); k++)
    {
        port_set32(&port, entropy + k * 4, 0x18, 0);
    }
    port_set32(&port, entropy, 0x14, 0);
    port_set32(&port, entropy, 0x28, port_u32(&port, decoder, 0x114));
    if (port_u32(&port, decoder, 0x1a0) == 0)
    {
        port_set32(&port, entropy, 8, 0);
    }
    return port_return(&port, 1, entry->edx);
}

/* Original 0x4c38b0: each output row pair (+0x138 rows, from the rows ecx) doubles the pixels of
 * the input row (from ebx) across the width +0x70 and copies it to the next row (0x4c9860). eax
 * the decoder, edx the last row pair index plus 1 (+0x138 when none). */
uint32_t vertrix_port_decoder_upsample_double_4c38b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t rows;
    uint32_t row = 0;
    uint32_t pushed[2];
    uint32_t edx;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0xcu, decoder);
    rows = port_u32(&port, entry->ecx, 0);
    edx = port_u32(&port, decoder, 0x138);
    if ((int32_t)edx <= 0)
    {
        return port_return(&port, decoder, edx);
    }
    port_set32(&port, ebp, -0x14u, entry->ebx);
    port_set32(&port, ebp, -0x18u, rows);
    port_set32(&port, ebp, -0x10u, 1);
    do
    {
        uint32_t out = port_u32(&port, port_u32(&port, ebp, -0x18u), 0);
        uint32_t end = port_u32(&port, port_u32(&port, ebp, -0xcu), 0x70) + out;
        uint32_t in = port_u32(&port, port_u32(&port, ebp, -0x14u), 0);
        while (out < end)
        {
            uint32_t pixel = port_u8(&port, in, 0);
            out += 2;
            port_set8(&port, out, -2u, pixel);
            in++;
            port_set8(&port, out, -1u, pixel);
        }
        pushed[0] = 1;
        pushed[1] = port_u32(&port, port_u32(&port, ebp, -0xcu), 0x70);
        call_frame(&port, 0x4c9860, rows, row, rows, port_u32(&port, ebp, -0x10u), row + 2, rows,
                   ebp, pushed, 2);
        row += 2;
        port_set32(&port, ebp, -0x18u, port_u32(&port, ebp, -0x18u) + 8);
        port_set32(&port, ebp, -0x14u, port_u32(&port, ebp, -0x14u) + 4);
        edx = port_u32(&port, ebp, -0x10u) + 2;
        port_set32(&port, ebp, -0x10u, edx);
    } while ((int32_t)row < (int32_t)port_u32(&port, port_u32(&port, ebp, -0xcu), 0x138));
    return port_return(&port, port_u32(&port, ebp, -0xcu), edx);
}

/* Original 0x4d24a0: the value 0x4d1e50 finds for ebx, or 0x4cf850 on eax when there is none. */
uint32_t vertrix_port_rtl_lookup_or_default_4d24a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 8
    };
    Port port;
    uint32_t local = entry->esp - BELOW;
    uint32_t result;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (port_forward_esi(&port, entry, 0x4d1e50, entry->ebx, local, entry->ebx, entry->ecx,
                         entry->eax) != 0)
    {
        return port_return(&port, port_u32(&port, local, 0), vertrix_lift_edx);
    }
    result = port_forward_esi(&port, entry, 0x4cf850, entry->eax, vertrix_lift_edx, entry->ebx,
                              entry->ecx, entry->eax);
    return port_return(&port, result, vertrix_lift_edx);
}
