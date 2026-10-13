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
