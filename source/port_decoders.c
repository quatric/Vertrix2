#include "port_decoders.h"

/* The image decoder's input steps, the Adobe marker, the pass counter, the row buffers of the
 * upsampler and the buffered row controller. */

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

/* The decoder's error exit (method +0 of its handler +0) after the code `code` and the value
 * `value` (+0x18), when not 0; edx the handler or, with `edx_decoder`, the decoder. */
static uint32_t decoder_error(Port *port, uint32_t decoder, uint32_t code, int with_value,
                              uint32_t value, int edx_decoder, uint32_t ebx, uint32_t ecx,
                              uint32_t esi, uint32_t edi, uint32_t ebp)
{
    uint32_t handler = port_u32(port, decoder, 0);
    port_set32(port, handler, 0x14, code);
    if (with_value)
    {
        port_set32(port, port_u32(port, decoder, 0), 0x18, value);
    }
    handler = port_u32(port, decoder, 0);
    return port_call_with(port, port_u32(port, handler, 0), decoder,
                          edx_decoder ? decoder : handler, ebx, ecx, esi, edi, ebp);
}

/* Original 0x4b97c0: the input step by the state +0x14: 0xca starts (0x4c17da) and, with a
 * header only (+0x40), ends in 0xcf with 1; 0xcb reads markers (method +0 of +0x1b4, after the
 * progress hook +8) until it gives 0 or 2, counting the passes on 1 or 3, then starts the output
 * (+0x98 from +0x90, 0x4b98b0); 0xcc goes straight on; others are an error 0x14. */
uint32_t vertrix_port_decoder_consume_input_4b97c0(PORT_SIGNATURE)
{
    Port port;
    uint32_t decoder = entry->eax;
    uint32_t state;
    uint32_t ebx = entry->ebx;
    uint32_t ecx;
    uint32_t edi = entry->edi;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    state = port_u32(&port, decoder, 0x14);
    ecx = state;
    if (state == 0xca)
    {
        port_call_with(&port, 0x4c17da, decoder, decoder, ebx, ecx, entry->esi, edi, entry->ebp);
        decoder = vertrix_lift_edx;
        if (port_u32(&port, decoder, 0x40) != 0)
        {
            port_set32(&port, decoder, 0x14, 0xcf);
            return port_return(&port, 1, entry->edx);
        }
        port_set32(&port, decoder, 0x14, 0xcb);
        state = 0xcb;
    }
    if (state == 0xcb)
    {
        if (port_u32(&port, port_u32(&port, decoder, 0x1b4), 0x10) != 0)
        {
            for (;;)
            {
                uint32_t progress = port_u32(&port, decoder, 8);
                if (progress != 0)
                {
                    ebx = progress;
                    ecx = progress;
                    port_call_with(&port, port_u32(&port, progress, 0), decoder, decoder, ebx, ecx,
                                   entry->esi, edi, entry->ebp);
                    decoder = vertrix_lift_edx;
                }
                ecx = port_u32(&port, decoder, 0x1b4);
                result = port_call_with(&port, port_u32(&port, ecx, 0), decoder, decoder, ebx, ecx,
                                        entry->esi, edi, entry->ebp);
                decoder = vertrix_lift_edx;
                if (result == 0)
                {
                    return port_return(&port, 0, entry->edx);
                }
                if (result == 2)
                {
                    break;
                }
                if (port_u32(&port, decoder, 8) != 0 && (result == 3 || result == 1))
                {
                    uint32_t passes;
                    ecx = port_u32(&port, decoder, 8);
                    edi = port_u32(&port, ecx, 4) + 1;
                    port_set32(&port, ecx, 4, edi);
                    passes = port_u32(&port, decoder, 8);
                    ebx = port_u32(&port, passes, 8);
                    if ((int32_t)edi >= (int32_t)ebx)
                    {
                        port_set32(&port, passes, 8, ebx + port_u32(&port, decoder, 0x140));
                    }
                }
            }
        }
        port_set32(&port, decoder, 0x98, port_u32(&port, decoder, 0x90));
    }
    else if (state != 0xcc)
    {
        ecx = port_u32(&port, decoder, 0);
        decoder_error(&port, decoder, 0x14, 1, state, 1, ebx, ecx, entry->esi, edi, entry->ebp);
        decoder = vertrix_lift_edx;
    }
    return port_return(
        &port,
        port_call_with(&port, 0x4b98b0, decoder, decoder, ebx, ecx, entry->esi, edi, entry->ebp),
        entry->edx);
}

/* Original 0x4b98b0: the output start: outside the state 0xcc the pass starts (method +0 of
 * +0x1a4), the row +0x8c is 0 and the state 0xcc; then while the passes (+0x1a4's +8) go on, the
 * rows up to +0x74 are read (the progress hook +8 told the row and the count, method +4 of +0x1a8
 * on +0x8c) until a read gives nothing (0), a full pass finishes (methods +4 and +0 of +0x1a4);
 * at the end the state is 0xcd, or 0xce with buffered output (+0x44), and 1. */
uint32_t vertrix_port_decoder_output_start_4b98b0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t edi = entry->edi;
    uint32_t passes;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    if (port_u32(&port, decoder, 0x14) != 0xcc)
    {
        passes = port_u32(&port, decoder, 0x1a4);
        port_call_with(&port, port_u32(&port, passes, 0), decoder, passes, ebx, ecx, decoder, edi,
                       ebp);
        port_set32(&port, decoder, 0x8c, 0);
        port_set32(&port, decoder, 0x14, 0xcc);
    }
    port_set32(&port, ebp, -0x18u, decoder + 0x8c);
    for (;;)
    {
        if (port_u32(&port, port_u32(&port, decoder, 0x1a4), 8) == 0)
        {
            port_set32(&port, decoder, 0x14, (port_u32(&port, decoder, 0x44) != 0) + 0xcd);
            return port_return(&port, 1, entry->edx);
        }
        while (port_u32(&port, decoder, 0x8c) < port_u32(&port, decoder, 0x74))
        {
            uint32_t progress = port_u32(&port, decoder, 8);
            uint32_t row;
            uint32_t reader;
            if (progress != 0)
            {
                port_set32(&port, progress, 4, port_u32(&port, decoder, 0x8c));
                port_set32(&port, port_u32(&port, decoder, 8), 8, port_u32(&port, decoder, 0x74));
                progress = port_u32(&port, decoder, 8);
                port_call_with(&port, port_u32(&port, progress, 0), decoder, progress, ebx, ecx,
                               decoder, edi, ebp);
            }
            ebx = port_u32(&port, ebp, -0x18u);
            row = port_u32(&port, decoder, 0x8c);
            edi = port_u32(&port, decoder, 0x1a8);
            ecx = 0;
            port_set32(&port, ebp, -0x1cu, row);
            reader = port_u32(&port, edi, 4);
            port_call_with(&port, reader, decoder, 0, ebx, 0, decoder, edi, ebp);
            if (port_u32(&port, decoder, 0x8c) == port_u32(&port, ebp, -0x1cu))
            {
                return port_return(&port, 0, entry->edx);
            }
        }
        passes = port_u32(&port, decoder, 0x1a4);
        port_call_with(&port, port_u32(&port, passes, 4), decoder, passes, ebx, ecx, decoder, edi,
                       ebp);
        passes = port_u32(&port, decoder, 0x1a4);
        port_call_with(&port, port_u32(&port, passes, 0), decoder, passes, ebx, ecx, decoder, edi,
                       ebp);
        port_set32(&port, decoder, 0x8c, 0);
    }
}

/* Original 0x4bf190: the Adobe marker of dx (ebx bytes, ecx the bytes left): with 12 bytes and
 * "Adobe" the version (+0x18), the flags (+0x1c, +0x20) and the transform (+0x24) are traced
 * (0x4c) and +0x124 1, +0x128 the transform; otherwise the unknown marker 0x4e of ecx + ebx
 * bytes. */
uint32_t vertrix_port_decoder_adobe_marker_4bf190(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0xc
    };
    static const uint8_t adobe[5] = {0x41, 0x64, 0x6f, 0x62, 0x65};
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t data = entry->edx;
    uint32_t handler;
    uint32_t result;
    unsigned index;
    int match = entry->ebx >= 0xc;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    for (index = 0; match && index < 5; index++)
    {
        match = port_u8(&port, data, index) == adobe[index];
    }
    if (!match)
    {
        handler = port_u32(&port, decoder, 0);
        port_set32(&port, handler, 0x14, 0x4e);
        port_set32(&port, port_u32(&port, decoder, 0), 0x18, entry->ecx + entry->ebx);
        handler = port_u32(&port, decoder, 0);
        result = port_call_with(&port, port_u32(&port, handler, 4), decoder, 1, entry->ebx, handler,
                                decoder, entry->edi, ebp);
        return port_return(&port, result, vertrix_lift_edx);
    }
    {
        uint32_t version = (port_u8(&port, data, 5) << 8) + port_u8(&port, data, 6);
        uint32_t first = (port_u8(&port, data, 7) << 8) + port_u8(&port, data, 8);
        uint32_t second = (port_u8(&port, data, 9) << 8) + port_u8(&port, data, 0xa);
        uint32_t transform = port_u8(&port, data, 0xb);
        port_set32(&port, ebp, -8u, first);
        handler = port_u32(&port, decoder, 0);
        port_set32(&port, handler, 0x18, version);
        port_set32(&port, handler, 0x20, second);
        port_set32(&port, handler, 0x24, transform);
        port_set32(&port, handler, 0x1c, port_u32(&port, ebp, -8u));
        port_set32(&port, port_u32(&port, decoder, 0), 0x14, 0x4c);
        handler = port_u32(&port, decoder, 0);
        result = port_call_with(&port, port_u32(&port, handler, 4), decoder, 1, handler, transform,
                                decoder, entry->edi, ebp);
        port_set32(&port, decoder, 0x124, 1);
        port_set8(&port, decoder, 0x128, transform);
        return port_return(&port, result, vertrix_lift_edx);
    }
}

/* Original 0x4c16dc: the pass end: with a quantizer (+0x54) its finish (method +8 of +0x1cc), and
 * the pass count (+0xc of +0x1a4) rises. */
uint32_t vertrix_port_decoder_pass_finish_4c16dc(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t master;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x1cu, decoder);
    port_set32(&port, ebp, -0x18u, port_u32(&port, decoder, 0x1a4));
    if (port_u32(&port, decoder, 0x54) != 0)
    {
        uint32_t quantizer = port_u32(&port, decoder, 0x1cc);
        port_call_with(&port, port_u32(&port, quantizer, 8), decoder, quantizer, entry->ebx,
                       entry->ecx, entry->esi, entry->edi, ebp);
    }
    master = port_u32(&port, ebp, -0x18u);
    port_set32(&port, master, 0xc, port_u32(&port, master, 0xc) + 1);
    return port_return(&port, master, entry->edx);
}

/* Original 0x4c1d40: the merged upsampler's rows: with a spare row (+0x24) it is copied out
 * (0x4c9860 from +0x20, one row of +0x28) and the out row (stack word 2) advances by one;
 * otherwise up to two rows (the rows left +0x2c and the room) are made (method +0xc on the in row
 * at ebx into the rows of the stack words 1 and 2, the second into +0x20 when only one fits). A
 * finished group (+0x24 0) advances the in row. ret 0xc. */
uint32_t vertrix_port_decoder_merged_rows_4c1d40(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x1c
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0xc];
    uint32_t ebp = entry->esp - 4;
    uint32_t rows;
    uint32_t done;
    uint32_t limit;
    uint32_t sampler;
    uint32_t edi;
    uint32_t edx;
    uint32_t eax;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    rows = port_u32(&port, ebp, 8);
    done = port_u32(&port, ebp, 0xc);
    limit = port_u32(&port, ebp, 0x10);
    port_set32(&port, ebp, -0x10u, entry->eax);
    port_set32(&port, ebp, -0xcu, entry->ebx);
    sampler = port_u32(&port, entry->eax, 0x1c4);
    if (port_u32(&port, sampler, 0x24) != 0)
    {
        uint32_t copy[2];
        copy[0] = 1;
        copy[1] = port_u32(&port, sampler, 0x28);
        edi = 1;
        call_frame(&port, 0x4c9860, sampler + 0x20, 0, port_u32(&port, done, 0) * 4 + rows, 0,
                   sampler, 1, ebp, copy, 2);
        port_set32(&port, sampler, 0x24, 0);
    }
    else
    {
        uint32_t room;
        edi = 2;
        if (port_u32(&port, sampler, 0x2c) < edi)
        {
            edi = port_u32(&port, sampler, 0x2c);
        }
        room = limit - port_u32(&port, done, 0);
        if (edi > room)
        {
            edi = room;
        }
        port_set32(&port, ebp, -0x18u, port_u32(&port, rows + port_u32(&port, done, 0) * 4, 0));
        if (edi <= 1)
        {
            port_set32(&port, ebp, -0x14u, port_u32(&port, sampler, 0x20));
            port_set32(&port, sampler, 0x24, 1);
        }
        else
        {
            port_set32(&port, ebp, -0x14u, port_u32(&port, rows + port_u32(&port, done, 0) * 4, 4));
        }
        port_call_with(&port, port_u32(&port, sampler, 0xc), entry->eax, entry->edx,
                       port_u32(&port, entry->ebx, 0), ebp - 0x18, sampler, edi, ebp);
    }
    edx = vertrix_lift_edx;
    port_set32(&port, done, 0, port_u32(&port, done, 0) + edi);
    port_set32(&port, sampler, 0x2c, port_u32(&port, sampler, 0x2c) - edi);
    eax = done;
    if (port_u32(&port, sampler, 0x24) == 0)
    {
        eax = port_u32(&port, ebp, -0xcu);
        port_set32(&port, eax, 0, port_u32(&port, eax, 0) + 1);
    }
    return port_return(&port, eax, edx);
}

/* The row group's start of 0x4c3220, 0x4c33a0 and 0x4c3470: the buffer (+8) is opened (method
 * +0x1c of +4 on +0x10 rows from the row +0x14, `write` or not, the stack word) into +0xc. */
static uint32_t buffer_open(Port *port, uint32_t decoder, uint32_t control, uint32_t first,
                            uint32_t write, uint32_t ebp)
{
    uint32_t memory = port_u32(port, decoder, 4);
    uint32_t argument[1];
    uint32_t result;
    argument[0] = write;
    result = call_frame(port, port_u32(port, memory, 0x1c), decoder, port_u32(port, control, 8),
                        first, port_u32(port, control, 0x10), control, memory, ebp, argument, 1);
    port_set32(port, control, 0xc, result);
    return result;
}

/* Original 0x4c3220: the buffered row controller's pass start by the mode dl: 0 the direct pass
 * (0x4c3320 with a quantizer, opening the buffer when absent, otherwise the upsampler's step),
 * 2 the reading pass 0x4c3470 and 3 the writing pass 0x4c33a0 (both need the buffer +8, error 4);
 * others are error 4. The rows +0x14 and +0x18 are 0. */
uint32_t vertrix_port_decoder_buffer_pass_start_4c3220(PORT_SIGNATURE)
{
    Port port;
    uint32_t decoder = entry->eax;
    uint32_t mode = entry->edx;
    uint32_t control;
    uint32_t edx = mode;
    port_open(&port, calls, services, globals, entry);
    control = port_u32(&port, decoder, 0x1b0);
    if (mode == 0)
    {
        if (port_u32(&port, decoder, 0x54) != 0)
        {
            port_set32(&port, control, 4, 0x4c3320);
            if (port_u32(&port, control, 0xc) == 0)
            {
                buffer_open(&port, decoder, control, 0, 1, entry->ebp);
                edx = vertrix_lift_edx;
            }
        }
        else
        {
            port_set32(&port, control, 4, port_u32(&port, port_u32(&port, decoder, 0x1c4), 4));
        }
    }
    else if (mode == 2 || mode == 3)
    {
        if (port_u32(&port, control, 8) == 0)
        {
            decoder_error(&port, decoder, 4, 0, 0, 0, entry->ebx, entry->ecx, control, entry->edi,
                          entry->ebp);
            edx = vertrix_lift_edx;
        }
        port_set32(&port, control, 4, mode == 3 ? 0x4c33a0 : 0x4c3470);
    }
    else
    {
        decoder_error(&port, decoder, 4, 0, 0, 0, entry->ebx, entry->ecx, control, entry->edi,
                      entry->ebp);
        edx = vertrix_lift_edx;
    }
    port_set32(&port, control, 0x18, 0);
    port_set32(&port, control, 0x14, port_u32(&port, control, 0x18));
    return port_return(&port, port_u32(&port, control, 0x18), edx);
}

/* Original 0x4c33a0: the writing pass: the group (+0x18 rows into the buffer +0xc, opened at
 * +0x14 for writing when empty) is filled by the upsampler (method +4 of +0x1c4 with the buffer,
 * +0x18 and +0x10) and the new rows quantized (method +4 of +0x1cc) into the out rows (stack word
 * 1 advanced); a full group moves +0x14 on and empties +0x18. ret 0xc. */
uint32_t vertrix_port_decoder_buffer_write_4c33a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0xc];
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t control;
    uint32_t before;
    uint32_t after;
    uint32_t edx;
    uint32_t sampler;
    uint32_t fill[3];
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, ebp, -0xcu, decoder);
    port_set32(&port, ebp, -0x1cu, entry->edx);
    port_set32(&port, ebp, -0x18u, entry->ebx);
    port_set32(&port, ebp, -0x14u, entry->ecx);
    control = port_u32(&port, decoder, 0x1b0);
    if (port_u32(&port, control, 0x18) == 0)
    {
        buffer_open(&port, decoder, control, port_u32(&port, control, 0x14), 1, ebp);
    }
    before = port_u32(&port, control, 0x18);
    port_set32(&port, ebp, -0x10u, before);
    fill[0] = port_u32(&port, control, 0xc);
    fill[1] = control + 0x18;
    fill[2] = port_u32(&port, control, 0x10);
    sampler = port_u32(&port, decoder, 0x1c4);
    call_frame(&port, port_u32(&port, sampler, 4), decoder, entry->edx, entry->ebx, entry->ecx,
               control, sampler, ebp, fill, 3);
    edx = vertrix_lift_edx;
    before = port_u32(&port, ebp, -0x10u);
    after = port_u32(&port, control, 0x18);
    if (after > before)
    {
        uint32_t quantizer = port_u32(&port, decoder, 0x1cc);
        uint32_t count = after - before;
        port_set32(&port, ebp, -0x20u, count);
        port_call_with(&port, port_u32(&port, quantizer, 4), decoder,
                       before * 4 + port_u32(&port, control, 0xc), 0, count, control, quantizer,
                       ebp);
        edx = port_u32(&port, ebp, 0xc);
        port_set32(&port, edx, 0, port_u32(&port, edx, 0) + port_u32(&port, ebp, -0x20u));
    }
    after = port_u32(&port, control, 0x18);
    if (after >= port_u32(&port, control, 0x10))
    {
        uint32_t rows = port_u32(&port, control, 0x10);
        port_set32(&port, control, 0x18, 0);
        port_set32(&port, control, 0x14, port_u32(&port, control, 0x14) + rows);
    }
    return port_return(&port, after, edx);
}

/* Original 0x4c3470: the reading pass: the group (the buffer +0xc opened at +0x14 for reading
 * when +0x18 is 0) gives up to the rows left of it, of the out rows (stack words 1 and 2) and of
 * the image (+0x74) to the quantizer (method +4 of +0x1cc); the out row advances and a full group
 * moves +0x14 on. ret 0xc. */
uint32_t vertrix_port_decoder_buffer_read_4c3470(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x14
    };
    Port port;
    uint8_t stack[BELOW + 8 + 0xc];
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t control;
    uint32_t count;
    uint32_t done;
    uint32_t quantizer;
    uint32_t total;
    uint32_t edx;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 3);
    port_set32(&port, ebp, -0x10u, decoder);
    control = port_u32(&port, decoder, 0x1b0);
    if (port_u32(&port, control, 0x18) == 0)
    {
        buffer_open(&port, decoder, control, port_u32(&port, control, 0x14), 0, ebp);
    }
    done = port_u32(&port, ebp, 0xc);
    count = port_u32(&port, control, 0x10) - port_u32(&port, control, 0x18);
    port_set32(&port, ebp, -0xcu, count);
    if (port_u32(&port, ebp, 0x10) - port_u32(&port, done, 0) < count)
    {
        port_set32(&port, ebp, -0xcu, port_u32(&port, ebp, 0x10) - port_u32(&port, done, 0));
    }
    if (port_u32(&port, decoder, 0x74) - port_u32(&port, control, 0x14) <
        port_u32(&port, ebp, -0xcu))
    {
        port_set32(&port, ebp, -0xcu,
                   port_u32(&port, decoder, 0x74) - port_u32(&port, control, 0x14));
    }
    quantizer = port_u32(&port, decoder, 0x1cc);
    port_call_with(&port, port_u32(&port, quantizer, 4), decoder,
                   port_u32(&port, control, 0x18) * 4 + port_u32(&port, control, 0xc),
                   port_u32(&port, done, 0) * 4 + port_u32(&port, ebp, 8),
                   port_u32(&port, ebp, -0xcu), control, quantizer, ebp);
    count = port_u32(&port, ebp, -0xcu);
    port_set32(&port, done, 0, port_u32(&port, done, 0) + count);
    total = port_u32(&port, control, 0x18) + count;
    port_set32(&port, control, 0x18, total);
    edx = done;
    if (total >= port_u32(&port, control, 0x10))
    {
        edx = port_u32(&port, control, 0x14) + port_u32(&port, control, 0x10);
        port_set32(&port, control, 0x18, 0);
        port_set32(&port, control, 0x14, edx);
    }
    return port_return(&port, count, edx);
}
