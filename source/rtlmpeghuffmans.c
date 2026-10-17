#include "rtlmpeghuffmans.h"

/* MPEG layer III: decodes a granule's Huffman-coded spectrum and scales it (mpg123's
 * III_dequantize_sample), for short blocks band by band through the scale factor band map, for
 * long blocks with the pre-emphasis table. */

enum
{
    /* max[4], kept in the emulated frame: it is indexed by the window the band map gives. */
    BELOW = 0xb0,
    MAX = 0xac,
    ARGUMENT_PART2BITS = 4,

    GR_PART2_3_LENGTH = 4,
    GR_BIG_VALUES = 8,
    GR_BLOCK_TYPE = 0x10,
    GR_MIXED_BLOCK = 0x14,
    GR_TABLE_SELECT = 0x18,
    GR_MAXBAND = 0x30,
    GR_MAXBANDL = 0x3c,
    GR_MAXB = 0x40,
    GR_REGION1START = 0x44,
    GR_REGION2START = 0x48,
    GR_PREFLAG = 0x4c,
    GR_COUNT1TABLE_SELECT = 0x54,
    GR_SCALEFAC_SCALE = 0x50,
    GR_FULL_GAIN = 0x58,
    GR_POW2GAIN = 0x64,

    /* struct newhuff: linbits, table. */
    HT = 0x4f5808,
    HTC = 0x4f5908,
    HUFF_BYTES = 8,
    HUFF_TABLE = 4,
    ISPOW = 0x524288,
    PRETAB1 = 0x4f5ee0,
    PRETAB2 = 0x4f5f38,
    MAP = 0x524208,
    MAP_END = 0x523e60,
    LONG_LIMIT = 0x523ecc,
    LONG_LIMIT_BYTES = 0x5c,
    SHORT_LIMIT = 0x522da0,
    SHORT_LIMIT_BYTES = 0x38,
    XR_BYTES = 0x900,

    GETBITS = 0x404610,
    GET1BIT = 0x4046e0,
    FLOAT_MUL = 0x4d8177,
    FLOAT_NEGATE = 0x4eb5b4
};

typedef struct
{
    Port *port;
    uint32_t gr;
    uint32_t scf;
    uint32_t shift;
    int32_t part2remain;
} Granule;

static int32_t s16(Port *port, uint32_t at)
{
    return (int16_t)port_u16(port, at, 0);
}

static uint32_t getbits(Granule *g, uint32_t count)
{
    return port_call(g->port, GETBITS, count, 0, 0, 0);
}

static uint32_t get1bit(Granule *g)
{
    return port_call(g->port, GET1BIT, 0, 0, 0, 0);
}

/* Walks a Huffman tree to its value (x << 4 | y), a bit a node. */
static int32_t huffman(Granule *g, uint32_t table)
{
    uint32_t val = table;
    int32_t y;
    while ((y = s16(g->port, val)) < 0 && !g->port->env.failed)
    {
        val += 2;
        if (get1bit(g))
        {
            val -= (uint32_t)(2 * y);
        }
        g->part2remain--;
    }
    return y;
}

/* The count1 quadruple: its four bits, or 0 when the bits ran out. */
static int32_t quadruple(Granule *g, uint32_t table)
{
    uint32_t val = table;
    int32_t a;
    while ((a = s16(g->port, val)) < 0 && !g->port->env.failed)
    {
        val += 2;
        g->part2remain--;
        if (g->part2remain < 0)
        {
            g->part2remain++;
            return 0;
        }
        if (get1bit(g))
        {
            val -= (uint32_t)(2 * a);
        }
    }
    return a;
}

/* ispow[n] * v, negated by the sign bit; the multiply sees xrpnt in ebx and the original's ecx. */
static uint32_t scaled(Granule *g, uint32_t n, uint32_t v, uint32_t xrpnt, uint32_t ecx)
{
    uint32_t value = port_u32(g->port, ISPOW + 4 * n, 0);
    if (get1bit(g))
    {
        value = port_call(g->port, FLOAT_NEGATE, value, 0, 0, 0);
    }
    return port_call(g->port, FLOAT_MUL, value, v, xrpnt, ecx);
}

/* One value of a big-value pair, with its linbits escape, stored (scaled by v) at xrpnt; returns
 * whether it was nonzero. The multiply sees in ecx the pair's y: for the y itself the escaped
 * value, or y times `scale` (4 in a long block, its table offset). */
static int big_value(Granule *g, uint32_t h, int32_t value, int is_y, int32_t y, uint32_t scale,
                     uint32_t v, uint32_t xrpnt)
{
    if (value == 15)
    {
        const uint32_t linbits = port_u32(g->port, h, 0);
        g->part2remain -= (int32_t)linbits + 1;
        value += (int32_t)getbits(g, linbits);
        const uint32_t ecx = (uint32_t)(is_y ? value : y);
        port_set32(g->port, xrpnt, 0, scaled(g, (uint32_t)value, v, xrpnt, ecx));
        return 1;
    }
    if (value != 0)
    {
        const uint32_t ecx = is_y ? (uint32_t)y * scale : (uint32_t)y;
        port_set32(g->port, xrpnt, 0, scaled(g, (uint32_t)value, v, xrpnt, ecx));
        g->part2remain--;
        return 1;
    }
    port_set32(g->port, xrpnt, 0, 0);
    return 0;
}

static uint32_t pow2gain(Granule *g, uint32_t index)
{
    return port_u32(g->port, port_u32(g->port, g->gr, GR_POW2GAIN), 4 * (index << g->shift));
}

/* A short-block band from the map: mc, xrpnt, window and band; v and step for its window. */
typedef struct
{
    uint32_t m, mc, xrpnt, lwin, cb, v, step;
} Band;

static void next_short_band(Granule *g, Band *b, uint32_t xr)
{
    Port *port = g->port;
    b->mc = port_u32(port, b->m, 0);
    b->xrpnt = xr + 4 * port_u32(port, b->m, 4);
    b->lwin = port_u32(port, b->m, 8);
    b->cb = port_u32(port, b->m, 0xc);
    b->m += 0x10;
    const uint32_t scale = port_u32(port, g->scf, 0);
    g->scf += 4;
    if (b->lwin == 3)
    {
        b->v = pow2gain(g, scale);
        b->step = 1;
    }
    else
    {
        const uint32_t gain = port_u32(port, g->gr, GR_FULL_GAIN + 4 * b->lwin);
        b->v = port_u32(port, gain, 4 * (scale << g->shift));
        b->step = 3;
    }
}

static void set_max(Granule *g, uint32_t max, uint32_t lwin, uint32_t cb)
{
    port_set32(g->port, max + 4 * lwin, 0, cb);
}

static void short_blocks(Granule *g, uint32_t xr, uint32_t sfreq, const int32_t l[3], int32_t l3,
                         uint32_t max)
{
    Port *port = g->port;
    const int mixed = port_u32(port, g->gr, GR_MIXED_BLOCK) != 0;
    port_set32(port, max, 0xc, 0xffffffffu);
    for (uint32_t k = 0; k < 3; k++)
    {
        port_set32(port, max, 4 * k, mixed ? 2 : 0xffffffffu);
    }
    const uint32_t which = mixed ? 0 : 4;
    Band b = {port_u32(port, MAP + 12 * sfreq + which, 0), 0, xr, 0, 0, 0, 0};
    const uint32_t me = port_u32(port, MAP_END + 12 * sfreq + which, 0);
    for (uint32_t i = 0; i < 2; i++)
    {
        const uint32_t h = HT + HUFF_BYTES * port_u32(port, g->gr, GR_TABLE_SELECT + 4 * i);
        for (int32_t lp = l[i]; lp != 0 && !port->env.failed; lp--, b.mc--)
        {
            if (b.mc == 0)
            {
                next_short_band(g, &b, xr);
            }
            int32_t y = huffman(g, port_u32(port, h, HUFF_TABLE));
            const int32_t x = y >> 4;
            y &= 0xf;
            if (big_value(g, h, x, 0, y, 1, b.v, b.xrpnt))
            {
                set_max(g, max, b.lwin, b.cb);
            }
            b.xrpnt += 4 * b.step;
            if (big_value(g, h, y, 1, y, 1, b.v, b.xrpnt))
            {
                set_max(g, max, b.lwin, b.cb);
            }
            b.xrpnt += 4 * b.step;
        }
    }
    const uint32_t htc = HTC + HUFF_BYTES * port_u32(port, g->gr, GR_COUNT1TABLE_SELECT);
    for (; l3 != 0 && g->part2remain > 0 && !port->env.failed; l3--)
    {
        const int32_t a = quadruple(g, port_u32(port, htc, HUFF_TABLE));
        for (uint32_t i = 0; i < 4; i++)
        {
            if (!(i & 1))
            {
                if (b.mc == 0)
                {
                    next_short_band(g, &b, xr);
                }
                b.mc--;
            }
            if (a & (8 >> i))
            {
                set_max(g, max, b.lwin, b.cb);
                g->part2remain--;
                if (g->part2remain < 0)
                {
                    g->part2remain++;
                    break;
                }
                port_set32(port, b.xrpnt, 0,
                           get1bit(g) ? port_call(port, FLOAT_NEGATE, b.v, 0, 0, 0) : b.v);
            }
            else
            {
                port_set32(port, b.xrpnt, 0, 0);
            }
            b.xrpnt += 4 * b.step;
        }
    }
    /* The bands left: zeros, two at a time. */
    while (b.m < me && !port->env.failed)
    {
        if (b.mc == 0)
        {
            b.mc = port_u32(port, b.m, 0);
            b.xrpnt = xr + 4 * port_u32(port, b.m, 4);
            b.step = port_u32(port, b.m, 8) == 3 ? 1 : 3;
            b.m += 0x10;
        }
        port_set32(port, b.xrpnt, 0, 0);
        b.mc--;
        b.xrpnt += 4 * b.step;
        port_set32(port, b.xrpnt, 0, 0);
        b.xrpnt += 4 * b.step;
    }
    int32_t m[4];
    for (uint32_t k = 0; k < 4; k++)
    {
        m[k] = (int32_t)port_u32(port, max, 4 * k);
        port_set32(port, g->gr, GR_MAXBAND + 4 * k, (uint32_t)(m[k] + 1));
    }
    int32_t rmax = m[0] > m[1] ? m[0] : m[1];
    rmax = (rmax > m[2] ? rmax : m[2]) + 1;
    port_set32(
        port, g->gr, GR_MAXB,
        rmax != 0
            ? port_u32(port, SHORT_LIMIT + SHORT_LIMIT_BYTES * sfreq, 4 * (uint32_t)rmax)
            : port_u32(port, LONG_LIMIT + LONG_LIMIT_BYTES * sfreq, 4 * (uint32_t)(m[3] + 1)));
}

static void long_blocks(Granule *g, uint32_t xr, uint32_t sfreq, const int32_t l[3], int32_t l3)
{
    Port *port = g->port;
    uint32_t pretab = port_u32(port, g->gr, GR_PREFLAG) != 0 ? PRETAB1 : PRETAB2;
    int32_t max = -1;
    uint32_t cb = 0;
    uint32_t m = port_u32(port, MAP + 12 * sfreq, 8);
    uint32_t v = 0;
    uint32_t mc = 0;
    uint32_t xrpnt = xr;
    for (uint32_t i = 0; i < 3; i++)
    {
        const uint32_t h = HT + HUFF_BYTES * port_u32(port, g->gr, GR_TABLE_SELECT + 4 * i);
        for (int32_t lp = l[i]; lp != 0 && !port->env.failed; lp--, mc--)
        {
            if (mc == 0)
            {
                mc = port_u32(port, m, 0);
                v = pow2gain(g, port_u32(port, g->scf, 0) + port_u32(port, pretab, 0));
                g->scf += 4;
                pretab += 4;
                cb = port_u32(port, m, 4);
                m += 8;
            }
            int32_t y = huffman(g, port_u32(port, h, HUFF_TABLE));
            const int32_t x = y >> 4;
            y &= 0xf;
            if (big_value(g, h, x, 0, y, 4, v, xrpnt))
            {
                max = (int32_t)cb;
            }
            xrpnt += 4;
            if (big_value(g, h, y, 1, y, 4, v, xrpnt))
            {
                max = (int32_t)cb;
            }
            xrpnt += 4;
        }
    }
    const uint32_t htc = HTC + HUFF_BYTES * port_u32(port, g->gr, GR_COUNT1TABLE_SELECT);
    for (; l3 != 0 && g->part2remain > 0 && !port->env.failed; l3--)
    {
        const int32_t a = quadruple(g, port_u32(port, htc, HUFF_TABLE));
        for (uint32_t i = 0; i < 4; i++)
        {
            if (!(i & 1))
            {
                if (mc == 0)
                {
                    mc = port_u32(port, m, 0);
                    cb = port_u32(port, m, 4);
                    m += 8;
                    v = pow2gain(g, port_u32(port, g->scf, 0) + port_u32(port, pretab, 0));
                    g->scf += 4;
                    pretab += 4;
                }
                mc--;
            }
            if (a & (8 >> i))
            {
                max = (int32_t)cb;
                g->part2remain--;
                if (g->part2remain < 0)
                {
                    g->part2remain++;
                    break;
                }
                port_set32(port, xrpnt, 0,
                           get1bit(g) ? port_call(port, FLOAT_NEGATE, v, 0, 0, 0) : v);
            }
            else
            {
                port_set32(port, xrpnt, 0, 0);
            }
            xrpnt += 4;
        }
    }
    /* The rest of xr: zeros, two at a time. */
    uint32_t pairs = (uint32_t)((int32_t)(xr + XR_BYTES - xrpnt) >> 3);
    if (pairs != 0)
    {
        do
        {
            port_set32(port, xrpnt, 0, 0);
            port_set32(port, xrpnt, 4, 0);
            xrpnt += 8;
        } while (--pairs != 0 && !port->env.failed);
    }
    port_set32(port, g->gr, GR_MAXBANDL, (uint32_t)(max + 1));
    port_set32(port, g->gr, GR_MAXB,
               port_u32(port, LONG_LIMIT + LONG_LIMIT_BYTES * sfreq, 4 * (uint32_t)(max + 1)));
}

/* Original 0x407830 (ret 4). The x and y escapes are scaled by 0x4d8177, which sees the sample's
 * address in ebx and in ecx y, or 4 * y for a plain y of a long block. */
uint32_t vertrix_port_mpeg_huffman_decode_407830(PORT_SIGNATURE)
{
    uint8_t stack[BELOW + 8 + 4];
    Port port;
    port_open_arguments(&port, stack, calls, services, globals, entry, BELOW, 1);
    const uint32_t max = entry->esp - 4 - MAX;
    const uint32_t xr = entry->eax;
    const uint32_t gr = entry->ebx;
    const uint32_t sfreq = entry->ecx;
    Granule g = {&port, gr, entry->edx, port_u32(&port, gr, GR_SCALEFAC_SCALE) + 1,
                 (int32_t)(port_u32(&port, gr, GR_PART2_3_LENGTH) -
                           port_u32(&port, entry->esp, ARGUMENT_PART2BITS))};
    const int32_t bv = (int32_t)port_u32(&port, gr, GR_BIG_VALUES);
    const int32_t region1 = (int32_t)port_u32(&port, gr, GR_REGION1START);
    const int32_t region2 = (int32_t)port_u32(&port, gr, GR_REGION2START);
    const int32_t l3 = (int32_t)((uint32_t)(0x120 - bv)) >> 1;
    int32_t l[3];
    if (bv <= region1)
    {
        l[0] = bv;
        l[1] = 0;
        l[2] = 0;
    }
    else
    {
        l[0] = region1;
        if (bv <= region2)
        {
            l[1] = bv - region1;
            l[2] = 0;
        }
        else
        {
            l[1] = region2 - region1;
            l[2] = bv - region2;
        }
    }
    if (port_u32(&port, gr, GR_BLOCK_TYPE) == 2)
    {
        short_blocks(&g, xr, sfreq, l, l3, max);
    }
    else
    {
        long_blocks(&g, xr, sfreq, l, l3);
    }
    /* Skip the bits left in part 2 and 3. */
    while (g.part2remain > 16 && !port.env.failed)
    {
        getbits(&g, 16);
        g.part2remain -= 16;
    }
    if (g.part2remain > 0)
    {
        getbits(&g, (uint32_t)g.part2remain);
        return port_return(&port, 0, 0);
    }
    return port_return(&port, g.part2remain < 0, 0);
}
