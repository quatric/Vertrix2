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
