#include "quantizers.h"

/* The image decoder's colour converter and two pass colour quantizer setups. */

/* The decoder's error `code` with the value `value` when `has_value` is set, raised by its error
 * method +0. */
static void decoder_error(Port *port, uint32_t decoder, uint32_t code, int has_value,
                          uint32_t value, uint32_t edx, uint32_t ebx, uint32_t edi, uint32_t ebp)
{
    uint32_t errors = port_u32(port, decoder, 0);
    port_set32(port, errors, 0x14, code);
    if (has_value)
    {
        port_set32(port, port_u32(port, decoder, 0), 0x18, value);
    }
    errors = port_u32(port, decoder, 0);
    port_call_with(port, port_u32(port, errors, 0), decoder, edx, ebx, errors, decoder, edi, ebp);
}

/* Original 0x4c96a0: the decoder eax's two pass quantizer: 0x2c bytes from its pool +4 (method +0)
 * kept at +0x1cc with the methods 0x4c9550 and 0x4c9690 and +0x20, +0x28 cleared; with other than
 * 3 components (+0x78) the error 0x2f is raised; the histogram of 32 rows of 0x1000 bytes (pool
 * methods +0 and +4) at +0x18 with +0x1c 1; with a colour count wanted (+0x6c) the count +0x60
 * is checked to 8 to 256 (errors 0x38 and 0x39) and the colour map of 3 rows (pool method +8)
 * kept at +0x10 with the count at +0x14, else +0x10 is cleared; with dithering +0x58 set to 2 the
 * error rows of (+0x70 + 2) * 6 bytes are made (+0x20) and the dither table built (0x4c9030). */
uint32_t vertrix_port_quantizer_two_pass_make_4c96a0(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x20
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t pool;
    uint32_t quantizer;
    uint32_t histogram;
    uint32_t count;
    uint32_t rows;
    uint32_t eax;
    uint32_t offset;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    pool = port_u32(&port, decoder, 4);
    quantizer = port_call_with(&port, port_u32(&port, pool, 0), decoder, 1, 0x2c, pool, decoder,
                               entry->edi, ebp);
    port_set32(&port, decoder, 0x1cc, quantizer);
    port_set32(&port, quantizer, 0, 0x4c9550);
    port_set32(&port, quantizer, 0xc, 0x4c9690);
    port_set32(&port, quantizer, 0x20, 0);
    port_set32(&port, quantizer, 0x28, 0);
    port_set32(&port, ebp, -0x18u, quantizer);
    if (port_u32(&port, decoder, 0x78) != 3)
    {
        decoder_error(&port, decoder, 0x2f, 0, 0, port_u32(&port, decoder, 0x78), 0x2c, entry->edi,
                      ebp);
    }
    pool = port_u32(&port, decoder, 4);
    histogram = port_call_with(&port, port_u32(&port, pool, 0), decoder, 1, 0x80, pool, decoder,
                               entry->edi, ebp);
    port_set32(&port, quantizer, 0x18, histogram);
    for (offset = 0; offset < 0x80; offset += 4)
    {
        pool = port_u32(&port, decoder, 4);
        eax = port_call_with(&port, port_u32(&port, pool, 4), decoder, 1, 0x1000, offset, decoder,
                             pool, ebp);
        port_set32(&port, port_u32(&port, port_u32(&port, ebp, -0x18u), 0x18), offset, eax);
    }
    quantizer = port_u32(&port, ebp, -0x18u);
    port_set32(&port, quantizer, 0x1c, 1);
    if (port_u32(&port, decoder, 0x6c) == 0)
    {
        port_set32(&port, quantizer, 0x10, 0);
    }
    else
    {
        count = port_u32(&port, decoder, 0x60);
        port_set32(&port, ebp, -0x1cu, count);
        if ((int32_t)count < 8)
        {
            decoder_error(&port, decoder, 0x38, 1, 8, vertrix_lift_edx, 0x1000,
                          port_u32(&port, quantizer, 0x18), ebp);
        }
        if ((int32_t)port_u32(&port, ebp, -0x1cu) > 0x100)
        {
            decoder_error(&port, decoder, 0x39, 1, 0x100, vertrix_lift_edx, 0x1000,
                          port_u32(&port, port_u32(&port, ebp, -0x18u), 0x18), ebp);
        }
        pool = port_u32(&port, decoder, 4);
        eax = port_call_with(&port, port_u32(&port, pool, 8), decoder, 1,
                             port_u32(&port, ebp, -0x1cu), 3, decoder, pool, ebp);
        quantizer = port_u32(&port, ebp, -0x18u);
        port_set32(&port, quantizer, 0x10, eax);
        port_set32(&port, quantizer, 0x14, port_u32(&port, ebp, -0x1cu));
    }
    eax = port_u32(&port, decoder, 0x58);
    if (eax == 0)
    {
        return port_return(&port, eax, entry->edx);
    }
    port_set32(&port, decoder, 0x58, 2);
    rows = (port_u32(&port, decoder, 0x70) + 2) * 6;
    pool = port_u32(&port, decoder, 4);
    quantizer = port_u32(&port, ebp, -0x18u);
    eax = port_call_with(&port, port_u32(&port, pool, 4), decoder, 1, rows, quantizer, decoder,
                         pool, ebp);
    port_set32(&port, quantizer, 0x20, eax);
    eax = port_call_with(&port, 0x4c9030, decoder, vertrix_lift_edx, rows, quantizer, decoder, pool,
                         ebp);
    return port_return(&port, eax, entry->edx);
}

/* Original 0x4c2280: the decoder eax's colour converter: 0x30 bytes from its pool +4 (method +0)
 * kept at +0x1c4 with the methods 0x4c1d20 and +8 cleared and the row width +0x70 * +0x78 at
 * +0x28; for the colour space +0x138 2 the methods 0x4c1d40 and 0x4c2000 and a row buffer of that
 * width (pool method +4) at +0x20, else 0x4c1e10 and 0x4c1e40 and +0x20 cleared; then the four
 * tables of 256 (pool method +0) at +0x10, +0x14, +0x18 and +0x1c hold the scaled colour
 * difference terms. */
uint32_t vertrix_port_colour_converter_make_4c2280(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x24
    };
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t pool;
    uint32_t converter;
    uint32_t red;
    uint32_t blue;
    uint32_t green;
    uint32_t mixed;
    uint32_t offset;
    unsigned index;
    port_open_frame(&port, calls, services, globals, entry, BELOW);
    pool = port_u32(&port, decoder, 4);
    converter = port_call_with(&port, port_u32(&port, pool, 0), decoder, 1, 0x30, pool, decoder,
                               entry->edi, ebp);
    port_set32(&port, decoder, 0x1c4, converter);
    port_set32(&port, converter, 0, 0x4c1d20);
    port_set32(&port, converter, 8, 0);
    port_set32(&port, converter, 0x28,
               port_u32(&port, decoder, 0x70) * port_u32(&port, decoder, 0x78));
    if (port_u32(&port, decoder, 0x138) == 2)
    {
        port_set32(&port, converter, 4, 0x4c1d40);
        port_set32(&port, converter, 0xc, 0x4c2000);
        pool = port_u32(&port, decoder, 4);
        port_set32(&port, converter, 0x20,
                   port_call_with(&port, port_u32(&port, pool, 4), decoder, 1,
                                  port_u32(&port, converter, 0x28), converter, decoder, pool, ebp));
    }
    else
    {
        port_set32(&port, converter, 4, 0x4c1e10);
        port_set32(&port, converter, 0xc, 0x4c1e40);
        port_set32(&port, converter, 0x20, 0);
    }
    for (index = 0; index < 4; ++index)
    {
        pool = port_u32(&port, decoder, 4);
        port_set32(&port, converter, 0x10 + index * 4,
                   port_call_with(&port, port_u32(&port, pool, 0), decoder, 1, 0x400, converter,
                                  decoder, pool, ebp));
    }
    green = 0x5b6900;
    blue = 0xff1daf00u;
    red = 0xff4d0b80u;
    mixed = 0x2c0d00;
    for (offset = 0; offset < 0x400; offset += 4)
    {
        port_set32(&port, ebp, -0x20u, (uint32_t)((int32_t)red >> 16));
        port_set32(&port, port_u32(&port, converter, 0x10), offset, (uint32_t)((int32_t)red >> 16));
        port_set32(&port, ebp, -0x20u, (uint32_t)((int32_t)blue >> 16));
        port_set32(&port, port_u32(&port, converter, 0x14), offset,
                   (uint32_t)((int32_t)blue >> 16));
        blue += 0x1c5a2;
        port_set32(&port, port_u32(&port, converter, 0x18), offset, green);
        port_set32(&port, port_u32(&port, converter, 0x1c), offset, mixed + 0x8000);
        green -= 0xb6d2;
        mixed -= 0x581a;
        red += 0x166e9;
    }
    port_set32(&port, ebp, -0x18u, mixed);
    port_set32(&port, ebp, -0x1cu, red);
    return port_return(&port, 0x400, entry->edx);
}
