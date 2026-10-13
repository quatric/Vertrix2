#include "port_imdct.h"

enum
{
    SINGLE_MULTIPLY = 0x4d8177,
    SINGLE_SUBTRACT = 0x4d809c,
    SINGLE_ADD = 0x4d80a6,
    SAMPLES = 18,
    OUTPUT_STEP = 0x80,
    /* The window's second half: the overlap's weights. */
    WINDOW_OVERLAP = 18,
    /* The cosines (singles). */
    COS_A = 0x52c2c8,
    COS_B = 0x52c2cc,
    COS_C = 0x52c2d0,
    COS_D = 0x52c2d4,
    COS_E = 0x52c2d8,
    COS_F = 0x52c2dc,
    COS_G = 0x52c2e0,
    COS_H = 0x52c2e4,
    /* The butterflies' twiddles. */
    TWIDDLE_0 = 0x52c2e8,
    TWIDDLE_1 = 0x52c2ec,
    TWIDDLE_2 = 0x52c2f0,
    TWIDDLE_3 = 0x52c2f4,
    TWIDDLE_4 = 0x52c2f8,
    TWIDDLE_5 = 0x52c2fc,
    TWIDDLE_6 = 0x52c300,
    TWIDDLE_7 = 0x52c304,
    TWIDDLE_8 = 0x52c308
};

typedef struct Imdct
{
    Port port;
    uint32_t input;
    uint32_t previous;
    uint32_t overlap;
    uint32_t window;
    uint32_t output;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t result;
    uint32_t edx;
} Imdct;

static uint32_t op(Imdct *m, uint32_t target, uint32_t eax, uint32_t edx)
{
    m->result = port_call(&m->port, target, eax, edx, m->ebx, m->ecx);
    m->edx = vertrix_lift_edx;
    return m->result;
}

static uint32_t mul(Imdct *m, uint32_t a, uint32_t b)
{
    return op(m, SINGLE_MULTIPLY, a, b);
}

static uint32_t add(Imdct *m, uint32_t a, uint32_t b)
{
    return op(m, SINGLE_ADD, a, b);
}

static uint32_t sub(Imdct *m, uint32_t a, uint32_t b)
{
    return op(m, SINGLE_SUBTRACT, a, b);
}

static uint32_t in(Imdct *m, unsigned index)
{
    return port_u32(&m->port, m->input, index * 4);
}

static uint32_t constant(Imdct *m, uint32_t address)
{
    return port_u32(&m->port, 0, address);
}

static uint32_t weight(Imdct *m, unsigned index)
{
    return port_u32(&m->port, m->window, index * 4);
}

/* sum + y and sum - y, windowed: the first into the overlap at j and 17 - j, the second into the
 * output at 17 - j and j, each plus the previous block's overlap there. */
static void half(Imdct *m, uint32_t sum, uint32_t y, unsigned j)
{
    unsigned k = SAMPLES - 1 - j;
    uint32_t u = add(m, sum, y);
    uint32_t v;
    uint32_t product;
    port_set32(&m->port, m->overlap, j * 4, mul(m, u, weight(m, WINDOW_OVERLAP + j)));
    port_set32(&m->port, m->overlap, k * 4, mul(m, u, weight(m, WINDOW_OVERLAP + k)));
    v = sub(m, sum, y);
    /* The previous overlap is read after each product, as the original does. */
    product = mul(m, v, weight(m, k));
    port_set32(&m->port, m->output, k * OUTPUT_STEP,
               add(m, port_u32(&m->port, m->previous, k * 4), product));
    product = mul(m, v, weight(m, j));
    port_set32(&m->port, m->output, j * OUTPUT_STEP,
               add(m, port_u32(&m->port, m->previous, j * 4), product));
}

/* The butterfly of the even part (a, c) and the odd part (b, d). */
static void butterfly(Imdct *m, uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t first,
                      uint32_t second, unsigned j_first, unsigned j_second)
{
    uint32_t sum = add(m, a, b);
    half(m, sum, mul(m, add(m, c, d), constant(m, first)), j_first);
    sum = sub(m, b, a);
    half(m, sum, mul(m, sub(m, d, c), constant(m, second)), j_second);
}

/* x[first] * p, then base, x[first + 8] * q and x[first + 12] * r added or subtracted in the
 * original's order: form 0 adds all three, 1 subtracts the first two, 2 the first and last. */
static uint32_t even_term(Imdct *m, unsigned first, uint32_t base, uint32_t p, uint32_t q,
                          uint32_t r, int form)
{
    uint32_t x = mul(m, in(m, first), constant(m, p));
    switch (form)
    {
        case 0:
            x = add(m, x, base);
            x = add(m, x, mul(m, in(m, first + 8), constant(m, q)));
            return add(m, x, mul(m, in(m, first + 12), constant(m, r)));
        case 1:
            x = sub(m, x, base);
            x = sub(m, x, mul(m, in(m, first + 8), constant(m, q)));
            return add(m, x, mul(m, in(m, first + 12), constant(m, r)));
        default:
            x = sub(m, x, base);
            x = add(m, x, mul(m, in(m, first + 8), constant(m, q)));
            return sub(m, x, mul(m, in(m, first + 12), constant(m, r)));
    }
}

/* x[first - 4] and x[first] * p, x[first + 4] * q, base and x[first + 12] * r: form 0 adds them
 * all, 1 subtracts the first two products, 2 the first and last. */
static uint32_t odd_term(Imdct *m, unsigned first, uint32_t base, uint32_t p, uint32_t q,
                         uint32_t r, int form)
{
    uint32_t x;
    switch (form)
    {
        case 0:
            x = add(m, in(m, first - 4), mul(m, in(m, first), constant(m, p)));
            x = add(m, add(m, x, mul(m, in(m, first + 4), constant(m, q))), base);
            return add(m, x, mul(m, in(m, first + 12), constant(m, r)));
        case 1:
            x = sub(m, in(m, first - 4), mul(m, in(m, first), constant(m, p)));
            x = add(m, sub(m, x, mul(m, in(m, first + 4), constant(m, q))), base);
            return add(m, x, mul(m, in(m, first + 12), constant(m, r)));
        default:
            x = sub(m, in(m, first - 4), mul(m, in(m, first), constant(m, p)));
            x = add(m, add(m, x, mul(m, in(m, first + 4), constant(m, q))), base);
            return sub(m, x, mul(m, in(m, first + 12), constant(m, r)));
    }
}

uint32_t vertrix_port_imdct_long(PORT_SIGNATURE)
{
    Imdct m;
    unsigned i;
    uint32_t six, seven, twelve, thirteen;
    uint32_t a, b, c, d, x;
    port_open(&m.port, calls, services, globals, entry);
    m.input = entry->eax;
    m.previous = entry->edx;
    m.overlap = entry->ebx;
    m.window = entry->ecx;
    m.ebx = entry->ebx;
    m.ecx = entry->ecx;
    m.output = entry->arguments[0];
    m.edx = entry->edx;
    /* x[i] += x[i - 1] from the top, then the odd ones x[i] += x[i - 2]. */
    for (i = SAMPLES - 1; i != 0; i--)
    {
        port_set32(&m.port, m.input, i * 4, add(&m, in(&m, i), in(&m, i - 1)));
    }
    for (i = SAMPLES - 1; i > 1; i -= 2)
    {
        port_set32(&m.port, m.input, i * 4, add(&m, in(&m, i), in(&m, i - 2)));
    }
    six = mul(&m, in(&m, 6), constant(&m, COS_C));
    twelve = mul(&m, in(&m, 12), constant(&m, COS_F));
    seven = mul(&m, in(&m, 7), constant(&m, COS_C));
    thirteen = mul(&m, in(&m, 13), constant(&m, COS_F));

    a = even_term(&m, 2, six, COS_A, COS_E, COS_G, 0);
    c = even_term(&m, 3, seven, COS_A, COS_E, COS_G, 0);
    b = odd_term(&m, 4, twelve, COS_B, COS_D, COS_H, 0);
    d = odd_term(&m, 5, thirteen, COS_B, COS_D, COS_H, 0);
    butterfly(&m, a, b, c, d, TWIDDLE_0, TWIDDLE_8, 9, 17);

    x = sub(&m, sub(&m, in(&m, 2), in(&m, 10)), in(&m, 14));
    a = mul(&m, x, constant(&m, COS_C));
    x = sub(&m, sub(&m, in(&m, 3), in(&m, 11)), in(&m, 15));
    c = mul(&m, x, constant(&m, COS_C));
    x = mul(&m, sub(&m, sub(&m, in(&m, 4), in(&m, 8)), in(&m, 16)), constant(&m, COS_F));
    b = add(&m, sub(&m, x, in(&m, 12)), in(&m, 0));
    x = mul(&m, sub(&m, sub(&m, in(&m, 5), in(&m, 9)), in(&m, 17)), constant(&m, COS_F));
    d = add(&m, sub(&m, x, in(&m, 13)), in(&m, 1));
    butterfly(&m, a, b, c, d, TWIDDLE_1, TWIDDLE_7, 10, 16);

    a = even_term(&m, 2, six, COS_E, COS_G, COS_A, 1);
    c = even_term(&m, 3, seven, COS_E, COS_G, COS_A, 1);
    b = odd_term(&m, 4, twelve, COS_H, COS_B, COS_D, 1);
    d = odd_term(&m, 5, thirteen, COS_H, COS_B, COS_D, 1);
    butterfly(&m, a, b, c, d, TWIDDLE_2, TWIDDLE_6, 11, 15);

    a = even_term(&m, 2, six, COS_G, COS_A, COS_E, 2);
    c = even_term(&m, 3, seven, COS_G, COS_A, COS_E, 2);
    b = odd_term(&m, 4, twelve, COS_D, COS_H, COS_B, 2);
    d = odd_term(&m, 5, thirteen, COS_D, COS_H, COS_B, 2);
    butterfly(&m, a, b, c, d, TWIDDLE_3, TWIDDLE_5, 12, 14);

    x = add(&m, sub(&m, in(&m, 0), in(&m, 4)), in(&m, 8));
    a = add(&m, sub(&m, x, in(&m, 12)), in(&m, 16));
    x = add(&m, sub(&m, in(&m, 1), in(&m, 5)), in(&m, 9));
    x = add(&m, sub(&m, x, in(&m, 13)), in(&m, 17));
    half(&m, a, mul(&m, x, constant(&m, TWIDDLE_4)), 13);
    return port_return(&m.port, m.result, m.edx);
}

uint32_t vertrix_port_mpeg_antialias(PORT_SIGNATURE)
{
    enum
    {
        FIXED_MULTIPLY = 0x4d8177,
        FIXED_SUBTRACT = 0x4d809c,
        FIXED_ADD = 0x4d80a6,
        ALIAS_CS = 0x5238a0,
        ALIAS_CA = 0x523880
    };
    Port port;
    uint32_t granule = entry->edx;
    uint32_t forward = entry->eax;
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t count;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, granule, 0x10) == 2)
    {
        if (port_u32(&port, granule, 0x14) == 0)
        {
            return port_return(&port, eax, edx);
        }
        count = 1;
    }
    else
    {
        count = port_u32(&port, granule, 0x40) - 1;
    }
    forward += 0x48;
    eax = count;
    while (count != 0)
    {
        uint32_t cs = ALIAS_CS;
        uint32_t ca = ALIAS_CA;
        uint32_t back = forward;
        int32_t step;
        for (step = 7; step >= 0; step--)
        {
            uint32_t lower;
            uint32_t upper;
            uint32_t product;
            back -= 4;
            lower = port_u32(&port, back, 0);
            upper = port_u32(&port, forward, 0);
            product = port_call(&port, FIXED_MULTIPLY, lower, port_u32(&port, cs, 0), upper, lower);
            edx = port_call(&port, FIXED_MULTIPLY, upper, port_u32(&port, ca, 0), upper, lower);
            port_set32(&port, back, 0,
                       port_call(&port, FIXED_SUBTRACT, product, edx, upper, lower));
            product = port_call(&port, FIXED_MULTIPLY, upper, port_u32(&port, cs, 0), upper, lower);
            edx = port_call(&port, FIXED_MULTIPLY, lower, port_u32(&port, ca, 0), product, lower);
            cs += 4;
            ca += 4;
            eax = port_call(&port, FIXED_ADD, product, edx, product, lower);
            edx = vertrix_lift_edx;
            port_set32(&port, forward, 0, eax);
            forward += 4;
        }
        count--;
        forward += 0x28;
    }
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_mpeg_scale_factors(PORT_SIGNATURE)
{
    enum
    {
        BIT_READ = 0x404680,
        SLEN_TABLE = 0x51f020,
        SLEN_TABLE_HALF = 0x51f820,
        BAND_COUNTS = 0x4f5e98
    };
    Port port;
    uint32_t out = entry->eax;
    uint32_t granule = entry->edx;
    uint32_t edx = entry->edx;
    uint32_t total = 0;
    uint32_t lengths;
    uint32_t kind = 0;
    uint32_t counts;
    uint32_t end;
    uint32_t i;
    port_open(&port, calls, services, globals, entry);
    lengths = entry->ebx == 0
                  ? port_u32(&port, port_u32(&port, granule, 0xc) * 4, SLEN_TABLE)
                  : port_u32(&port, (port_u32(&port, granule, 0xc) >> 1) * 4, SLEN_TABLE_HALF);
    port_set32(&port, granule, 0x4c, (lengths >> 15) & 1);
    if (port_u32(&port, granule, 0x10) == 2)
    {
        kind = port_u32(&port, granule, 0x14) != 0 ? 2 : 1;
    }
    counts = kind * 24 + BAND_COUNTS + ((lengths >> 12) & 7) * 4;
    end = counts + 4;
    for (; counts != end; counts++)
    {
        uint32_t bits = lengths & 7;
        uint32_t bands = port_u8(&port, counts, 0);
        lengths >>= 3;
        if (bits != 0)
        {
            for (edx = 0; (int32_t)edx < (int32_t)port_u8(&port, counts, 0); edx++)
            {
                port_set32(&port, out, 0, port_call(&port, BIT_READ, bits, edx, bits, out));
                edx = vertrix_lift_edx;
                out += 4;
            }
            total += port_u8(&port, counts, 0) * bits;
        }
        else
        {
            for (i = 0; (int32_t)i < (int32_t)bands; i++)
            {
                port_set32(&port, out, 0, 0);
                out += 4;
                bands = port_u8(&port, counts, 0);
            }
            edx = bands;
        }
    }
    kind = kind * 2 + 1;
    for (i = 0; (int32_t)i < (int32_t)kind; i++)
    {
        port_set32(&port, out, 0, 0);
        out += 4;
    }
    return port_return(&port, total, edx);
}

uint32_t vertrix_port_mpeg_decode_frame(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x10,
        ARGUMENTS = 2,
        DECODER = 0x51f01c,
        FRAME_DATA = 0x51f014,
        FRAME_BIT = 0x51f018
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    uint32_t ebp = entry->esp - 4;
    uint32_t decoder = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t copied;
    uint32_t reader;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    port_set32(&port, ebp, 0, entry->ebp);
    port_set32(&port, ebp, -4u, entry->esi);
    port_set32(&port, ebp, -8u, entry->edi);
    port_set32(&port, ebp, -0xcu, entry->ecx);
    port_set32(&port, 0, DECODER, decoder);
    if ((int32_t)port_u32(&port, ebp, 8) < 0x1200)
    {
        return port_return(&port, 0xffffffffu, edx);
    }
    if (edx != 0)
    {
        uint32_t found = port_call(&port, 0x405e00, decoder, edx, ebx, ecx);
        edx = vertrix_lift_edx;
        if (found == 0)
        {
            return port_return(&port, 0xffffffffu, edx);
        }
    }
    if (port_u32(&port, decoder, 0xc) == 0)
    {
        if ((int32_t)port_u32(&port, decoder, 8) < 4)
        {
            return port_return(&port, 1, edx);
        }
        port_call(&port, 0x405f30, decoder, edx, ebx, ecx);
        port_call(&port, 0x404480, decoder + 0x14, port_u32(&port, decoder, 0x3664), ebx, ecx);
        edx = vertrix_lift_edx;
        port_set32(&port, decoder, 0xc, port_u32(&port, decoder, 0x58));
    }
    if ((int32_t)port_u32(&port, decoder, 0x58) > (int32_t)port_u32(&port, decoder, 8))
    {
        return port_return(&port, 1, edx);
    }
    /* The frame goes to one of two 0x900-byte buffers, alternating. */
    port_set32(&port, 0, FRAME_DATA,
               port_u32(&port, decoder, 0x3668) * 0x900 + decoder + 0x5c + 0x200);
    port_set32(&port, decoder, 0x3668, (port_u32(&port, decoder, 0x3668) + 1) & 1);
    edx = decoder + 0x5c;
    ecx = 0;
    port_set32(&port, 0, FRAME_BIT, 0);
    copied = 0;
    if ((int32_t)port_u32(&port, decoder, 0xc) > 0)
    {
        do
        {
            uint32_t want;
            reader = port_u32(&port, decoder, 4);
            ecx = port_u32(&port, reader, 4) - port_u32(&port, reader, 8);
            want = port_u32(&port, decoder, 0xc) - copied;
            if ((int32_t)want <= (int32_t)ecx)
            {
                ecx = want;
            }
            reader = port_u32(&port, decoder, 4);
            edx = port_u32(&port, reader, 0) + port_u32(&port, reader, 8);
            ebx = ecx;
            port_call(&port, 0x4eb5e0, port_u32(&port, 0, FRAME_DATA) + copied, edx, ebx, ecx);
            edx = vertrix_lift_edx;
            copied += ecx;
            reader = port_u32(&port, decoder, 4);
            port_set32(&port, reader, 8, port_u32(&port, reader, 8) + ecx);
            port_set32(&port, decoder, 8, port_u32(&port, decoder, 8) - ecx);
            reader = port_u32(&port, decoder, 4);
            edx = port_u32(&port, reader, 8);
            if (edx == port_u32(&port, reader, 4))
            {
                port_call(&port, 0x405ea0, decoder, edx, ebx, ecx);
                edx = vertrix_lift_edx;
            }
        } while ((int32_t)copied < (int32_t)port_u32(&port, decoder, 0xc));
    }
    port_set32(&port, port_u32(&port, ebp, 0xc), 0, 0);
    if (port_u32(&port, decoder, 0x30) != 0)
    {
        port_call(&port, 0x404610, 0x10, edx, ebx, ecx);
        edx = vertrix_lift_edx;
    }
    port_call(&port, 0x40a190, decoder + 0x14, port_u32(&port, ebp, -0xcu),
              port_u32(&port, ebp, 0xc), ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, decoder, 0x10, port_u32(&port, decoder, 0xc));
    port_set32(&port, decoder, 0xc, 0);
    return port_return(&port, 0, edx);
}

/* One pair of IMDCTs (two 18-sample subbands) for 0x409f00. */
static void hybrid_pair(Port *port, uint32_t target, uint32_t samples, uint32_t previous,
                        uint32_t overlap, uint32_t window, uint32_t second_window, uint32_t output)
{
    uint32_t argument = output;
    port_call_stack(port, target, samples, previous, overlap, window, &argument, 1);
    argument = output + 4;
    port_call_stack(port, target, samples + 0x48, previous + 0x48, overlap + 0x48, second_window,
                    &argument, 1);
}

uint32_t vertrix_port_mpeg_hybrid(PORT_SIGNATURE)
{
    enum
    {
        DECODER = 0x51f01c,
        IMDCT_LONG = 0x4088e0,
        IMDCT_SHORT = 0x4095d0,
        LONG_WINDOWS = 0x523b00,
        LONG_WINDOWS_ODD = 0x5238c0,
        SHORT_WINDOW = 0x523c20,
        SHORT_WINDOW_ODD = 0x5239e0
    };
    Port port;
    uint32_t samples = entry->eax;
    uint32_t output = entry->edx;
    uint32_t granule = entry->ecx;
    uint32_t channel = entry->ebx;
    uint32_t decoder;
    uint32_t base;
    uint32_t slot;
    uint32_t side;
    uint32_t previous;
    uint32_t overlap;
    uint32_t count = 0;
    uint32_t block;
    uint32_t eax;
    uint32_t edx;
    uint32_t end;
    port_open(&port, calls, services, globals, entry);
    decoder = port_u32(&port, 0, DECODER);
    base = decoder + 0x125c;
    slot = decoder + 0x365c + channel * 4;
    side = port_u32(&port, slot, 0);
    /* The two overlap buffers of the channel swap roles every granule. */
    previous = base + side * 0x1200 + channel * 0x900;
    overlap = channel * 0x900 + base + (1 - side) * 0x1200;
    port_set32(&port, slot, 0, 1 - side);
    if (port_u32(&port, granule, 0x14) != 0)
    {
        /* Mixed blocks: the two lowest subbands use the long windows. */
        count = 2;
        hybrid_pair(&port, IMDCT_LONG, samples, previous, overlap, LONG_WINDOWS, LONG_WINDOWS_ODD,
                    output);
        previous += 0x90;
        overlap += 0x90;
        output += 8;
    }
    block = port_u32(&port, granule, 0x10);
    while (count < port_u32(&port, granule, 0x40))
    {
        if (block == 2)
        {
            hybrid_pair(&port, IMDCT_SHORT, samples + count * 0x48, previous, overlap, SHORT_WINDOW,
                        SHORT_WINDOW_ODD, output);
        }
        else
        {
            hybrid_pair(&port, IMDCT_LONG, samples + count * 0x48, previous, overlap,
                        LONG_WINDOWS + block * 0x90, LONG_WINDOWS_ODD + block * 0x90, output);
        }
        count += 2;
        output += 8;
        previous += 0x90;
        overlap += 0x90;
    }
    /* The subbands left over take the previous overlap alone, which is then cleared. */
    edx = granule;
    end = output + 0x900;
    eax = end;
    while ((int32_t)count < 0x20)
    {
        eax = output;
        do
        {
            edx = port_u32(&port, previous, 0);
            previous += 4;
            port_set32(&port, eax, 0, edx);
            port_set32(&port, overlap, 0, 0);
            overlap += 4;
            eax += 0x80;
        } while (eax != end);
        count++;
        end += 4;
        output += 4;
    }
    return port_return(&port, eax, edx);
}

/* The registers 0x407280 carries across its bit reads: each read takes the count in eax and
 * hands on edx, ebx and ecx as they are. */
typedef struct SideRegisters
{
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
} SideRegisters;

static uint32_t side_read(Port *port, SideRegisters *r, uint32_t target, uint32_t eax)
{
    eax = port_call(port, target, eax, r->edx, r->ebx, r->ecx);
    r->edx = vertrix_lift_edx;
    return eax;
}

uint32_t vertrix_port_mpeg_side_info(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x18,
        ARGUMENTS = 1,
        READ_BITS = 0x404610,
        READ_SMALL = 0x404680,
        READ_BIT = 0x4046e0,
        GAIN_TABLE = 0x523698,
        BAND_BOUNDS = 0x4f5918
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4 * ARGUMENTS];
    SideRegisters r;
    uint32_t ebp = entry->esp - 4;
    uint32_t info = entry->eax;
    int32_t channels = (int32_t)entry->edx;
    uint32_t stereo = entry->ebx;
    uint32_t rate = entry->ecx;
    uint32_t table;
    uint32_t gain_bias;
    uint32_t channel;
    uint32_t end;
    uint32_t eax;
    int32_t index;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, ARGUMENTS);
    r.edx = entry->edx;
    r.ebx = entry->ebx;
    eax = port_u32(&port, ebp, 8) == 3 ? 4 : 0;
    r.ecx = eax;
    port_set32(&port, info, 0, side_read(&port, &r, READ_BITS, 8));
    if (channels == 1)
    {
        eax = side_read(&port, &r, READ_BIT, port_u32(&port, info, 0));
    }
    else
    {
        eax = side_read(&port, &r, READ_SMALL, 2);
    }
    port_set32(&port, info, 4, eax);
    if (channels <= 0)
    {
        return port_return(&port, eax, r.edx);
    }
    r.edx = rate;
    table = rate * 0x90;
    gain_bias = r.ecx << 2;
    r.ecx = gain_bias;
    channel = info + 8;
    for (index = 0; index < channels; index++)
    {
        uint32_t edx;
        r.ecx = channel;
        port_set32(&port, channel, 4, side_read(&port, &r, READ_BITS, 0xc));
        eax = side_read(&port, &r, READ_SMALL, 9);
        port_set32(&port, channel, 8, eax);
        if (eax > 0x120)
        {
            port_set32(&port, channel, 8, 0x120);
        }
        eax = side_read(&port, &r, READ_SMALL, 8);
        r.edx = GAIN_TABLE - (eax << 2) + gain_bias;
        port_set32(&port, channel, 0x64, r.edx);
        if (stereo != 0)
        {
            port_set32(&port, channel, 0x64, r.edx + 8);
        }
        eax = side_read(&port, &r, READ_BITS, 9);
        port_set32(&port, channel, 0xc, eax);
        eax = side_read(&port, &r, READ_BIT, eax);
        end = channel + 0xc;
        if (eax == 0)
        {
            /* Long blocks: three table selects, then the region counts as band bounds. */
            uint32_t first;
            r.edx = channel;
            r.ebx = 5;
            do
            {
                eax = side_read(&port, &r, READ_SMALL, r.ebx);
                port_set32(&port, r.edx, 0x18, eax);
                r.edx += 4;
            } while (r.edx != end);
            r.edx = side_read(&port, &r, READ_SMALL, 4);
            eax = side_read(&port, &r, READ_SMALL, 3);
            first = port_u32(&port, r.edx * 2 + table, BAND_BOUNDS);
            r.ebx = (uint32_t)((int32_t)first >> 17);
            port_set32(&port, channel, 0x44, r.ebx);
            eax = (uint32_t)((int32_t)port_u32(&port, (eax + r.edx) * 2 + table, BAND_BOUNDS + 2) >>
                             17);
            port_set32(&port, channel, 0x48, eax);
            port_set32(&port, channel, 0x10, 0);
            port_set32(&port, channel, 0x14, 0);
        }
        else
        {
            /* Window switching: block type, mixed flag, two table selects, three subblock
             * gains. */
            port_set32(&port, channel, 0x10, side_read(&port, &r, READ_SMALL, 2));
            eax = side_read(&port, &r, READ_BIT, port_u32(&port, channel, 0x10));
            port_set32(&port, channel, 0x14, eax);
            port_set32(&port, channel, 0x18, side_read(&port, &r, READ_SMALL, 5));
            port_set32(&port, channel, 0x1c, side_read(&port, &r, READ_SMALL, 5));
            port_set32(&port, channel, 0x20, 0);
            r.edx = channel;
            do
            {
                eax = side_read(&port, &r, READ_SMALL, 3);
                r.ebx = port_u32(&port, channel, 0x64);
                eax = (eax << 5) + r.ebx;
                port_set32(&port, r.edx, 0x58, eax);
                r.edx += 4;
            } while (r.edx != end);
            if (port_u32(&port, channel, 0x10) == 0)
            {
                eax = side_read(&port, &r, 0x4eb4d4, 1);
            }
            if (port_u32(&port, channel, 0x10) == 2)
            {
                port_set32(&port, channel, 0x44, 0x12);
            }
            else
            {
                port_set32(&port, channel, 0x44, rate == 8 ? 0x36 : 0x1b);
            }
            port_set32(&port, channel, 0x48, 0x120);
        }
        eax = side_read(&port, &r, READ_BIT, eax);
        port_set32(&port, channel, 0x50, eax);
        eax = side_read(&port, &r, READ_BIT, eax);
        port_set32(&port, channel, 0x54, eax);
        channel += 0xd0;
        edx = (uint32_t)index + 1;
        r.edx = edx;
    }
    return port_return(&port, eax, r.edx);
}

uint32_t vertrix_port_mpeg_imdct_short(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x68,
        FIXED_MULTIPLY = 0x4d8177,
        FIXED_SUBTRACT = 0x4d809c,
        FIXED_ADD = 0x4d80a6
    };
    Port port;
    uint8_t stack[BELOW + 8 + 4];
    /* The original's 0x5c bytes of locals: the butterfly's intermediate values, then the saved
     * edx (21) and eax (22). None is passed by address. */
    uint32_t local[23] = {0};
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi = 0;
    uint32_t edi = 0;
    uint32_t ebp = 0;
    uint32_t output;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    output = port_u32(&port, entry->esp, 4);
    local[22] = eax;
    local[21] = edx;
    esi = output;
    eax = port_u32(&port, edx, 0x0);
    port_set32(&port, esi, 0x0, eax);
    eax = port_u32(&port, edx, 0x4);
    port_set32(&port, esi, 0x80, eax);
    eax = port_u32(&port, edx, 0x8);
    port_set32(&port, esi, 0x100, eax);
    eax = port_u32(&port, edx, 0xc);
    port_set32(&port, esi, 0x180, eax);
    eax = port_u32(&port, edx, 0x10);
    port_set32(&port, esi, 0x200, eax);
    eax = port_u32(&port, edx, 0x14);
    port_set32(&port, esi, 0x280, eax);
    eax = local[22];
    eax = port_u32(&port, eax, 0x3c);
    local[3] = eax;
    eax = local[22];
    eax = port_u32(&port, eax, 0x30);
    local[2] = eax;
    eax = local[3];
    edx = local[2];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[3] = eax;
    edi = local[22];
    edi = port_u32(&port, edi, 0x24);
    eax = local[2];
    edx = edi;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[2] = eax;
    eax = local[22];
    eax = port_u32(&port, eax, 0x18);
    local[1] = eax;
    eax = edi;
    edx = local[1];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edi = eax;
    ebp = local[22];
    ebp = port_u32(&port, ebp, 0xc);
    eax = local[1];
    edx = ebp;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[1] = eax;
    eax = local[22];
    eax = port_u32(&port, eax, 0x0);
    local[0] = eax;
    eax = ebp;
    edx = local[0];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    ebp = eax;
    eax = local[3];
    edx = edi;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[3] = eax;
    eax = edi;
    edx = ebp;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edi = eax;
    eax = local[1];
    edx = port_u32(&port, 0u, 0x524284);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[1] = eax;
    eax = edi;
    edx = port_u32(&port, 0u, 0x524284);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edi = eax;
    eax = local[0];
    edx = local[2];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[5] = eax;
    eax = ebp;
    edx = local[3];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = port_u32(&port, 0u, 0x524278);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[6] = eax;
    eax = local[5];
    edx = local[6];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[4] = eax;
    eax = local[5];
    edx = local[6];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[5] = eax;
    eax = local[4];
    edx = port_u32(&port, ecx, 0x28);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[7] = eax;
    eax = local[21];
    eax = port_u32(&port, eax, 0x40);
    edx = local[7];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x800, eax);
    eax = local[4];
    edx = port_u32(&port, ecx, 0x1c);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[7] = eax;
    eax = local[21];
    eax = port_u32(&port, eax, 0x34);
    edx = local[7];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x680, eax);
    eax = local[5];
    edx = port_u32(&port, ecx, 0x4);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[7] = eax;
    eax = local[21];
    eax = port_u32(&port, eax, 0x1c);
    edx = local[7];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x380, eax);
    eax = local[5];
    edx = port_u32(&port, ecx, 0x10);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[7] = eax;
    eax = local[21];
    eax = port_u32(&port, eax, 0x28);
    edx = local[7];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x500, eax);
    eax = local[2];
    edx = port_u32(&port, 0u, 0x524280);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = local[0];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[0] = eax;
    edx = local[1];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[2] = eax;
    eax = local[0];
    edx = local[1];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[0] = eax;
    eax = local[3];
    edx = port_u32(&port, 0u, 0x524280);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = ebp;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    ebp = eax;
    edx = edi;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = port_u32(&port, 0u, 0x524274);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[3] = eax;
    eax = ebp;
    edx = edi;
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = port_u32(&port, 0u, 0x52427c);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    ebp = eax;
    eax = local[2];
    edx = local[3];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edi = eax;
    eax = local[2];
    edx = local[3];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[2] = eax;
    eax = local[0];
    edx = ebp;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[1] = eax;
    eax = local[0];
    edx = ebp;
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[0] = eax;
    eax = local[1];
    edx = port_u32(&port, ecx, 0x2c);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = local[21];
    eax = port_u32(&port, eax, 0x44);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x880, eax);
    eax = local[1];
    edx = port_u32(&port, ecx, 0x18);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = local[21];
    eax = port_u32(&port, eax, 0x30);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x600, eax);
    eax = edi;
    edx = port_u32(&port, ecx, 0x20);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = local[21];
    eax = port_u32(&port, eax, 0x38);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x700, eax);
    eax = edi;
    edx = port_u32(&port, ecx, 0x24);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = local[21];
    eax = port_u32(&port, eax, 0x3c);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x780, eax);
    eax = local[0];
    edx = port_u32(&port, ecx, 0x0);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = local[21];
    eax = port_u32(&port, eax, 0x18);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x300, eax);
    eax = local[0];
    edx = port_u32(&port, ecx, 0x14);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = local[21];
    eax = port_u32(&port, eax, 0x2c);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x580, eax);
    eax = local[2];
    edx = port_u32(&port, ecx, 0x8);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = local[21];
    eax = port_u32(&port, eax, 0x20);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x400, eax);
    eax = local[2];
    edx = port_u32(&port, ecx, 0xc);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = local[21];
    eax = port_u32(&port, eax, 0x24);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x480, eax);
    edx = local[22];
    edx = edx + 0x4;
    local[22] = edx;
    eax = port_u32(&port, edx, 0x3c);
    local[17] = eax;
    eax = port_u32(&port, edx, 0x30);
    local[20] = eax;
    eax = local[17];
    edx = local[20];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[17] = eax;
    edi = local[22];
    edi = port_u32(&port, edi, 0x24);
    eax = local[20];
    edx = edi;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[20] = eax;
    eax = local[22];
    eax = port_u32(&port, eax, 0x18);
    local[9] = eax;
    eax = edi;
    edx = local[9];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edi = eax;
    eax = local[22];
    eax = port_u32(&port, eax, 0xc);
    local[8] = eax;
    eax = local[9];
    edx = local[8];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[9] = eax;
    ebp = local[22];
    ebp = port_u32(&port, ebp, 0x0);
    eax = local[8];
    edx = ebp;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[8] = eax;
    eax = local[17];
    edx = edi;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[17] = eax;
    eax = edi;
    edx = local[8];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edi = eax;
    eax = local[9];
    edx = port_u32(&port, 0u, 0x524284);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[9] = eax;
    eax = edi;
    edx = port_u32(&port, 0u, 0x524284);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edi = eax;
    eax = ebp;
    edx = local[20];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[11] = eax;
    eax = local[8];
    edx = local[17];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = port_u32(&port, 0u, 0x524278);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[12] = eax;
    eax = local[11];
    edx = local[12];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[10] = eax;
    eax = local[11];
    edx = local[12];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[11] = eax;
    edx = port_u32(&port, ecx, 0x28);
    eax = local[10];
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x10, eax);
    edx = port_u32(&port, ecx, 0x1c);
    eax = local[10];
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x4, eax);
    eax = local[11];
    edx = port_u32(&port, ecx, 0x4);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = port_u32(&port, esi, 0x680);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x680, eax);
    eax = local[11];
    edx = port_u32(&port, ecx, 0x10);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = port_u32(&port, esi, 0x800);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x800, eax);
    eax = local[20];
    edx = port_u32(&port, 0u, 0x524280);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = ebp;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    ebp = eax;
    edx = local[9];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[20] = eax;
    eax = ebp;
    edx = local[9];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    ebp = eax;
    eax = local[17];
    edx = port_u32(&port, 0u, 0x524280);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = local[8];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[8] = eax;
    edx = edi;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = port_u32(&port, 0u, 0x524274);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[17] = eax;
    eax = local[8];
    edx = edi;
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = port_u32(&port, 0u, 0x52427c);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[8] = eax;
    eax = local[20];
    edx = local[17];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edi = eax;
    eax = local[20];
    edx = local[17];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[20] = eax;
    eax = ebp;
    edx = local[8];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[9] = eax;
    eax = ebp;
    edx = local[8];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    ebp = eax;
    edx = port_u32(&port, ecx, 0x2c);
    eax = local[9];
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x14, eax);
    edx = port_u32(&port, ecx, 0x18);
    eax = local[9];
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x0, eax);
    edx = port_u32(&port, ecx, 0x20);
    eax = edi;
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x8, eax);
    edx = port_u32(&port, ecx, 0x24);
    eax = edi;
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0xc, eax);
    eax = ebp;
    edx = port_u32(&port, ecx, 0x0);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = port_u32(&port, esi, 0x600);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x600, eax);
    eax = ebp;
    edx = port_u32(&port, ecx, 0x14);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = port_u32(&port, esi, 0x880);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x880, eax);
    eax = local[20];
    edx = port_u32(&port, ecx, 0x8);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = port_u32(&port, esi, 0x700);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x700, eax);
    eax = local[20];
    edx = port_u32(&port, ecx, 0xc);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = port_u32(&port, esi, 0x780);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, esi, 0x780, eax);
    port_set32(&port, ebx, 0x44, 0x0);
    eax = port_u32(&port, ebx, 0x44);
    port_set32(&port, ebx, 0x40, eax);
    port_set32(&port, ebx, 0x3c, eax);
    port_set32(&port, ebx, 0x38, eax);
    port_set32(&port, ebx, 0x34, eax);
    port_set32(&port, ebx, 0x30, eax);
    esi = local[22];
    esi = esi + 0x4;
    local[22] = esi;
    eax = port_u32(&port, esi, 0x3c);
    local[16] = eax;
    eax = port_u32(&port, esi, 0x30);
    local[19] = eax;
    eax = local[16];
    edx = local[19];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[16] = eax;
    esi = port_u32(&port, esi, 0x24);
    eax = local[19];
    edx = esi;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[19] = eax;
    eax = local[22];
    eax = port_u32(&port, eax, 0x18);
    local[18] = eax;
    eax = esi;
    edx = local[18];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    esi = eax;
    edi = local[22];
    edi = port_u32(&port, edi, 0xc);
    eax = local[18];
    edx = edi;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[18] = eax;
    ebp = local[22];
    ebp = port_u32(&port, ebp, 0x0);
    eax = edi;
    edx = ebp;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edi = eax;
    eax = local[16];
    edx = esi;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[16] = eax;
    eax = esi;
    edx = edi;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    esi = eax;
    eax = local[18];
    edx = port_u32(&port, 0u, 0x524284);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[18] = eax;
    eax = esi;
    edx = port_u32(&port, 0u, 0x524284);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    esi = eax;
    eax = ebp;
    edx = local[19];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[14] = eax;
    eax = edi;
    edx = local[16];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = port_u32(&port, 0u, 0x524278);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[15] = eax;
    eax = local[14];
    edx = local[15];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[13] = eax;
    eax = local[14];
    edx = local[15];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[14] = eax;
    edx = port_u32(&port, ecx, 0x28);
    eax = local[13];
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x28, eax);
    edx = port_u32(&port, ecx, 0x1c);
    eax = local[13];
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x1c, eax);
    eax = local[14];
    edx = port_u32(&port, ecx, 0x4);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = port_u32(&port, ebx, 0x4);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x4, eax);
    eax = local[14];
    edx = port_u32(&port, ecx, 0x10);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = port_u32(&port, ebx, 0x10);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x10, eax);
    eax = local[19];
    edx = port_u32(&port, 0u, 0x524280);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = ebp;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    ebp = eax;
    edx = local[18];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[19] = eax;
    eax = ebp;
    edx = local[18];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    ebp = eax;
    eax = local[16];
    edx = port_u32(&port, 0u, 0x524280);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = edi;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edi = eax;
    edx = esi;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = port_u32(&port, 0u, 0x524274);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[16] = eax;
    eax = edi;
    edx = esi;
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = port_u32(&port, 0u, 0x52427c);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edi = eax;
    eax = local[19];
    edx = local[16];
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    esi = eax;
    eax = local[19];
    edx = local[16];
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[19] = eax;
    eax = ebp;
    edx = edi;
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    local[18] = eax;
    eax = ebp;
    edx = edi;
    eax = port_call(&port, FIXED_SUBTRACT, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    ebp = eax;
    edx = port_u32(&port, ecx, 0x2c);
    eax = local[18];
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x2c, eax);
    edx = port_u32(&port, ecx, 0x18);
    eax = local[18];
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x18, eax);
    edx = port_u32(&port, ecx, 0x20);
    eax = esi;
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x20, eax);
    edx = port_u32(&port, ecx, 0x24);
    eax = esi;
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x24, eax);
    eax = ebp;
    edx = port_u32(&port, ecx, 0x0);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = port_u32(&port, ebx, 0x0);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x0, eax);
    eax = ebp;
    edx = port_u32(&port, ecx, 0x14);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = port_u32(&port, ebx, 0x14);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x14, eax);
    eax = local[19];
    edx = port_u32(&port, ecx, 0x8);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = port_u32(&port, ebx, 0x8);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0x8, eax);
    eax = local[19];
    edx = port_u32(&port, ecx, 0xc);
    eax = port_call(&port, FIXED_MULTIPLY, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    edx = eax;
    eax = port_u32(&port, ebx, 0xc);
    eax = port_call(&port, FIXED_ADD, eax, edx, ebx, ecx);
    edx = vertrix_lift_edx;
    port_set32(&port, ebx, 0xc, eax);
    (void)edi;
    (void)ebp;
    (void)esi;
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_mpeg_decode_granules(PORT_SIGNATURE)
{
    enum
    {
        BELOW = 0x2a0,
        SIDE = 0x29c, /* below ebp: the side info (two granules of two 0xd0-byte channels) */
        GRANULE = 0x294,
        SECOND = 0x1c4,
        SCALES = 0xf4, /* below ebp: the scale factors */
        SAMPLES = 0x52c30c,
        SAMPLES_RIGHT = 0x52cc0c,
        HYBRID = 0x52d50c,
        HYBRID_RIGHT = 0x52de0c,
        FIXED_SUBTRACT = 0x4d809c,
        FIXED_ADD = 0x4d80a6
    };
    Port port;
    uint8_t stack[BELOW + 8];
    uint32_t ebp = entry->esp - 4;
    uint32_t header = entry->eax;
    uint32_t output = entry->edx;
    uint32_t count = entry->ebx;
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx = entry->ebx;
    uint32_t ecx = entry->ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t mode;
    int32_t single;
    uint32_t rate;
    int32_t channels;
    uint32_t mid_side = 0;
    uint32_t intensity = 0;
    uint32_t granules;
    uint32_t total = 0;
    uint32_t first;
    uint32_t second;
    uint32_t offset;
    uint32_t end;
    uint32_t argument;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    mode = port_u32(&port, header, 0);
    single = (int32_t)port_u32(&port, header, 8);
    rate = port_u32(&port, header, 0x24);
    if (mode == 1)
    {
        channels = 1;
        single = 0;
    }
    else
    {
        channels = single < 0 ? 2 : 1;
    }
    ecx = port_u32(&port, header, 0x30);
    if (ecx == 1)
    {
        mid_side = port_u32(&port, header, 0x34) & 2;
        intensity = port_u32(&port, header, 0x34) & 1;
    }
    else
    {
        ebx = 0;
    }
    /* The side info: MPEG-1 (+0xc set) reads two granules, MPEG-2 one. */
    argument = (uint32_t)single;
    ecx = rate;
    ebx = mid_side;
    if (port_u32(&port, header, 0xc) != 0)
    {
        granules = 1;
        eax = port_call_stack(&port, 0x407280, ebp - SIDE, mode, ebx, ecx, &argument, 1);
    }
    else
    {
        granules = 2;
        eax = port_call_stack(&port, 0x407020, ebp - SIDE, mode, ebx, ecx, &argument, 1);
    }
    edx = vertrix_lift_edx;
    eax = port_call(&port, 0x4060e0, port_u32(&port, ebp, -SIDE), edx, ebx, ecx);
    edx = vertrix_lift_edx;
    if (eax == 0xffffffffu)
    {
        return port_return(&port, 0, edx);
    }
    first = ebp - GRANULE;
    second = ebp - SECOND;
    end = granules * 0x68;
    for (offset = 0; (int32_t)offset < (int32_t)end; offset += 0x68)
    {
        uint32_t channel;
        uint32_t band;
        esi = first;
        if (port_u32(&port, header, 0xc) != 0)
        {
            ebx = 0;
            eax = port_call(&port, 0x407720, ebp - SCALES, esi, ebx, ecx);
        }
        else
        {
            eax = port_call(&port, 0x4074a0, ebp - SCALES, esi, ebx, ecx);
        }
        argument = eax;
        ecx = rate;
        ebx = esi;
        eax = port_call_stack(&port, 0x407830, SAMPLES, ebp - SCALES, ebx, ecx, &argument, 1);
        edx = vertrix_lift_edx;
        if (eax != 0)
        {
            return port_return(&port, total, edx);
        }
        if (mode == 2)
        {
            uint32_t right = second;
            if (port_u32(&port, header, 0xc) != 0)
            {
                ebx = intensity;
                eax = port_call(&port, 0x407720, ebp - SCALES, second, ebx, ecx);
            }
            else
            {
                eax = port_call(&port, 0x4074a0, ebp - SCALES, second, ebx, ecx);
            }
            argument = eax;
            ecx = rate;
            ebx = right;
            eax = port_call_stack(&port, 0x407830, SAMPLES_RIGHT, ebp - SCALES, ebx, ecx, &argument,
                                  1);
            edx = vertrix_lift_edx;
            if (eax != 0)
            {
                return port_return(&port, total, edx);
            }
            if (mid_side != 0)
            {
                /* Mid/side stereo: left = m + s, right = m - s. */
                for (ecx = 0; ecx != 0x900; ecx += 4)
                {
                    edi = port_u32(&port, ecx, SAMPLES);
                    esi = port_u32(&port, ecx, SAMPLES_RIGHT);
                    port_set32(&port, ecx, SAMPLES_RIGHT,
                               port_call(&port, FIXED_SUBTRACT, edi, esi, ebx, ecx));
                    port_set32(&port, ecx, SAMPLES,
                               port_call(&port, FIXED_ADD, edi, esi, ebx, ecx));
                    edx = vertrix_lift_edx;
                }
            }
            if (intensity != 0)
            {
                uint32_t pair[2];
                pair[0] = mid_side;
                pair[1] = port_u32(&port, header, 0xc);
                ecx = rate;
                ebx = right;
                port_call_stack(&port, 0x4083a0, SAMPLES, ebp - SCALES, ebx, ecx, pair, 2);
                edx = vertrix_lift_edx;
            }
            if (mid_side != 0 || intensity != 0 || (uint32_t)single == 3)
            {
                /* Both channels decode as many big values as the larger of the two. */
                eax = port_u32(&port, right, 0x40);
                edx = offset;
                ecx = port_u32(&port, edx, ebp - GRANULE + 0x40);
                if (eax > ecx)
                {
                    port_set32(&port, edx, ebp - GRANULE + 0x40, eax);
                }
                else
                {
                    edx = right;
                    port_set32(&port, edx, 0x40, ecx);
                }
            }
            ebx = (uint32_t)single;
            if (ebx == 1)
            {
                /* The right channel alone: copied over the left. */
                edx = SAMPLES;
                esi = SAMPLES_RIGHT;
                for (eax = 0;; eax++)
                {
                    ecx = port_u32(&port, right, 0x40) * 0x12;
                    if (eax >= ecx)
                    {
                        break;
                    }
                    ecx = port_u32(&port, esi, 0);
                    port_set32(&port, edx, 0, ecx);
                    esi += 4;
                    edx += 4;
                }
            }
            else if (ebx == 3)
            {
                /* Both channels mixed into the left. */
                ecx = SAMPLES;
                edi = SAMPLES_RIGHT;
                for (esi = 0;; esi++)
                {
                    eax = port_u32(&port, right, 0x40) * 0x12;
                    if (esi >= eax)
                    {
                        break;
                    }
                    edx = port_u32(&port, edi, 0);
                    edi += 4;
                    port_set32(&port, ecx, 0,
                               port_call(&port, FIXED_ADD, port_u32(&port, ecx, 0), edx, ebx, ecx));
                    edx = vertrix_lift_edx;
                    ecx += 4;
                }
            }
        }
        /* Alias reduction and the hybrid synthesis for each channel. */
        esi = SAMPLES;
        edi = first;
        for (channel = 0; (int32_t)channel < channels; channel++)
        {
            port_call(&port, 0x408800, esi, edi, ebx, ecx);
            ecx = edi;
            ebx = channel;
            port_call(&port, 0x409f00, esi, HYBRID + channel * 0x900, ebx, ecx);
            esi += 0x900;
            edi += 0xd0;
            edx = channel + 1;
        }
        /* The polyphase synthesis of the 18 time slots. */
        esi = HYBRID;
        for (band = 0; band < 0x12; band++)
        {
            if (single < 0)
            {
                port_set32(&port, ebp, -0x54u, port_u32(&port, count, 0));
                ecx = ebp - 0x54;
                ebx = output;
                eax = port_call(&port, 0x405720, esi, 0, ebx, ecx);
                total += eax;
                ecx = count;
                ebx = output;
                eax = port_call(&port, 0x405720, HYBRID_RIGHT + (band << 7), 1, ebx, ecx);
            }
            else
            {
                ebx = count;
                eax = port_call(&port, 0x4056c0, esi, output, ebx, ecx);
            }
            edx = vertrix_lift_edx;
            total += eax;
            esi += 0x80;
        }
        first += 0x68;
        second += 0x68;
    }
    return port_return(&port, total, edx);
}
