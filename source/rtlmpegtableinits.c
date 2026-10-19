#include "rtlmpegtableinits.h"

/* Builds the MPEG layer III decoder's tables, as mpg123's init_layer3 does: the gain powers, the
 * 4/3 powers, the alias reduction coefficients, the IMDCT windows and cosines, the intensity
 * stereo ratios and the scale factor band maps. Doubles are computed by the runtime's soft-float
 * routines and stored as floats. */

enum
{
    /* The runtime's doubles: from an integer, product, quotient, sum, power, square root, sine,
     * cosine, tangent, to a float, and a float negated. */
    FROM_INT = 0x4d6768,
    MUL = 0x4db507,
    DIV = 0x4eb652,
    ADD = 0x4db350,
    POW = 0x4c9921,
    SQRT = 0x4c9b10,
    SIN = 0x4c9daf,
    COS = 0x4c9dd6,
    TAN = 0x4c9e00,
    TO_FLOAT = 0x4eb606,
    NEGATE = 0x4eb5b4,

    GAIN_POWERS = 0x523298, /* gainpow2[256 + i] for i from -256 */
    GAIN_COUNT = 378,
    GAIN_FIRST = -46,
    POWERS_4_3 = 0x524288,
    POWERS_4_3_COUNT = 0x200f,
    ALIAS_CI = 0x4f5e28, /* the eight doubles Ci */
    ALIAS_CS = 0x5238a0,
    ALIAS_CA = 0x523880,
    ALIASES = 8,

    /* win[4][36] at 0x523b00 (0x90 bytes a window), and win1, the odd lines negated. */
    WINDOWS = 0x523b00,
    WINDOWS_ODD = 0x5238c0,
    WINDOW_BYTES = 0x90,
    WINDOW_LENGTHS = 0x4f5e68, /* the count of each window copied */

    COS9 = 0x52c2c4,
    TFCOS36 = 0x52c2e8,
    TFCOS12 = 0x524274,
    COS6_1 = 0x524284,
    COS6_2 = 0x524280,
    SHORT_WINDOW = 0x523c20,
    COS1 = 0x523d40,

    TAN1_1 = 0x523218,
    TAN2_1 = 0x523198,
    TAN1_2 = 0x523258,
    TAN2_2 = 0x5231d8,
    POW1_1 = 0x523118,
    POW2_1 = 0x523018,
    POW1_2 = 0x523098,
    POW2_2 = 0x522f98,

    /* The nine sample rates' band info: long and short indices and differences. */
    BAND_INFO = 0x4f5918,
    BAND_INFO_BYTES = 0x90,
    BAND_LONG_DIFF = 0x2e,
    BAND_SHORT_INDEX = 0x5a,
    BAND_SHORT_DIFF = 0x76,
    BANDS = 9,

    MAP_MIXED = 0x521210,
    MAP_MIXED_BYTES = 0x260,
    MAP_SHORT = 0x51fc20,
    MAP_SHORT_BYTES = 0x270,
    MAP_LONG = 0x522770,
    MAP_LONG_BYTES = 0xb0,
    MAP = 0x524208,     /* map[9][3] */
    MAP_END = 0x523e60, /* mapend[9][3] */
    LONG_LIMIT = 0x523ecc,
    LONG_LIMIT_BYTES = 0x5c,
    SHORT_LIMIT = 0x522da0,
    SHORT_LIMIT_BYTES = 0x38,

    /* The scale factor length tables (i_slen2, n_slen2). */
    I_SLEN2 = 0x51f7f0,
    N_SLEN2 = 0x51f020,
};

/* vertrix_mpeg_tables_memo: the decoder calls the routine again for every MP3 file, and every call
 * with the same registers builds the same tables (the soft-float routines depend only on their
 * operands and the helper cache, set by then; a host check over all 63 calls of the startup found
 * the memory after each repeat equal to the memory before it). So the first call's stores are
 * kept, and a repeat replays them instead of computing them again. */
enum
{
    MEMO_STORES = 16384
};

static struct
{
    int recording;
    int ready;
    uint32_t eax, edx, ebx, ecx;
    LiftFlags flags;
    unsigned count;
    uint32_t address[MEMO_STORES];
    uint32_t value[MEMO_STORES];
} memo;

static void table_set32(Port *port, uint32_t base, uint32_t offset, uint32_t value)
{
    port_set32(port, base, offset, value);
    if (memo.recording)
    {
        if (memo.count == MEMO_STORES)
        {
            memo.recording = 0;
            return;
        }
        memo.address[memo.count] = base + offset;
        memo.value[memo.count] = value;
        memo.count++;
    }
}

/* A double as the runtime passes it: low and high words. */
typedef struct
{
    uint32_t lo, hi;
} Double;

static const Double ONE = {0, 0x3ff00000};
static const Double HALF = {0, 0x3fe00000};
static const Double TWO = {0, 0x40000000};
static const Double MINUS_QUARTER = {0, 0xbfd00000};
static const Double FOUR_THIRDS = {0x55555554, 0x3ff55555};
static const Double PI = {0x54442d18, 0x400921fb};
static const Double PI_72 = {0x4ae74487, 0x3fa65718};
static const Double PI_24 = {0x382d7365, 0x3fc0c152};
static const Double PI_18 = {0x4ae74489, 0x3fc65718};
static const Double SQRT2 = {0x667f3bcc, 0x3ff6a09e};
static const Double D12 = {0, 0x40280000};
static const Double D24 = {0, 0x40380000};
static const Double D36 = {0, 0x40420000};
static const Double D72 = {0, 0x40520000};

/* The routines read ebx:ecx even when they take one operand: what the original leaves there, the
 * last second operand passed (or a loop counter). The conversion from an integer returns its high
 * word in edx, which a routine that leaves edx as it was hands back unchanged: the edx the original
 * last left. */
typedef struct
{
    Port *port;
    uint32_t edx, ebx, ecx;
} Math;

static Double pair(Math *m, uint32_t lo)
{
    m->edx = vertrix_lift_edx;
    return (Double){lo, m->edx};
}

static Double binary(Math *m, uint32_t routine, Double a, Double b)
{
    m->ebx = b.lo;
    m->ecx = b.hi;
    return pair(m, port_call(m->port, routine, a.lo, a.hi, b.lo, b.hi));
}

static Double unary(Math *m, uint32_t routine, Double a)
{
    return pair(m, port_call(m->port, routine, a.lo, a.hi, m->ebx, m->ecx));
}

static Double from_int(Math *m, uint32_t n)
{
    return pair(m, port_call(m->port, FROM_INT, n, m->edx, m->ebx, m->ecx));
}

static Double mul(Math *m, Double a, Double b)
{
    return binary(m, MUL, a, b);
}

static Double divide(Math *m, Double a, Double b)
{
    return binary(m, DIV, a, b);
}

static Double add(Math *m, Double a, Double b)
{
    return binary(m, ADD, a, b);
}

static Double power(Math *m, Double a, Double b)
{
    return binary(m, POW, a, b);
}

static uint32_t to_float(Math *m, Double value)
{
    const uint32_t single = port_call(m->port, TO_FLOAT, value.lo, value.hi, m->ebx, m->ecx);
    m->edx = vertrix_lift_edx;
    return single;
}

static void store(Math *m, uint32_t at, Double value)
{
    table_set32(m->port, at, 0, to_float(m, value));
}

/* cos(n * pi / divisor) */
static Double cos_pi(Math *m, uint32_t n, Double divisor)
{
    return unary(m, COS, divide(m, mul(m, from_int(m, n), PI), divisor));
}

/* 0.5 * sin(n * step) */
static Double half_sin(Math *m, uint32_t n, Double step)
{
    return mul(m, unary(m, SIN, mul(m, from_int(m, n), step)), HALF);
}

static void powers(Math *m)
{
    for (int32_t k = 0; k < GAIN_COUNT; k++)
    {
        const Double exponent = mul(m, from_int(m, (uint32_t)(GAIN_FIRST + k)), MINUS_QUARTER);
        store(m, GAIN_POWERS + 4 * k, power(m, TWO, exponent));
    }
    for (uint32_t i = 0; i < POWERS_4_3_COUNT; i++)
    {
        store(m, POWERS_4_3 + 4 * i, power(m, from_int(m, i), FOUR_THIRDS));
    }
    for (uint32_t i = 0; i < ALIASES; i++)
    {
        const Double ci = {port_u32(m->port, ALIAS_CI, 8 * i),
                           port_u32(m->port, ALIAS_CI, 8 * i + 4)};
        const Double sq = unary(m, SQRT, add(m, mul(m, ci, ci), ONE));
        store(m, ALIAS_CS + 4 * i, divide(m, ONE, sq));
        store(m, ALIAS_CA + 4 * i, divide(m, ci, sq));
        /* The original's offset and its loop bound. */
        m->edx = 4 * i;
        m->ecx = 4 * i + 4;
    }
}

static void windows(Math *m)
{
    for (uint32_t k = 0; k < 18; k++)
    {
        const uint32_t i = 2 * k;
        uint32_t single;
        Double value = divide(m, half_sin(m, i + 1, PI_72), cos_pi(m, i + 19, D72));
        single = to_float(m, value);
        table_set32(m->port, WINDOWS + 0x90 + 4 * k, 0, single);
        table_set32(m->port, WINDOWS + 4 * k, 0, single);
        value = divide(m, half_sin(m, i + 37, PI_72), cos_pi(m, i + 55, D72));
        single = to_float(m, value);
        table_set32(m->port, WINDOWS + 0x1f8 + 4 * k, 0, single);
        table_set32(m->port, WINDOWS + 0x48 + 4 * k, 0, single);
    }
    for (uint32_t k = 0; k < 6; k++)
    {
        const uint32_t i = 2 * k;
        const uint32_t at = 4 * k;
        store(m, WINDOWS + 0xd8 + at, divide(m, HALF, cos_pi(m, i + 55, D72)));
        store(m, WINDOWS + 0x1e0 + at, divide(m, HALF, cos_pi(m, i + 43, D72)));
        const Double c = cos_pi(m, i + 67, D72);
        store(m, WINDOWS + 0xf0 + at, divide(m, half_sin(m, i + 13, PI_24), c));
        table_set32(m->port, WINDOWS + 0x1b0 + at, 0, 0);
        table_set32(m->port, WINDOWS + 0x108 + at, 0, 0);
        m->edx = 0; /* the zero stored */
        const Double d = cos_pi(m, i + 31, D72);
        store(m, WINDOWS + 0x1c8 + at, divide(m, half_sin(m, i + 1, PI_24), d));
    }
}

static void cosines(Math *m)
{
    for (uint32_t i = 0; i < 9; i++)
    {
        store(m, COS9 + 4 * i, unary(m, COS, mul(m, from_int(m, i), PI_18)));
    }
    for (uint32_t k = 0; k < 9; k++)
    {
        store(m, TFCOS36 + 4 * k, divide(m, HALF, cos_pi(m, 2 * k + 1, D36)));
    }
    for (uint32_t k = 0; k < 3; k++)
    {
        store(m, TFCOS12 + 4 * k, divide(m, HALF, cos_pi(m, 2 * k + 1, D12)));
    }
    store(m, COS6_1, unary(m, COS, (Double){0x382d7366, 0x3fe0c152}));
    store(m, COS6_2, unary(m, COS, (Double){0x382d7367, 0x3ff0c152}));
    m->ecx = 0;
    for (uint32_t j = 0; j < 12; j++)
    {
        const Double s = half_sin(m, 2 * j + 1, PI_24);
        store(m, SHORT_WINDOW + 4 * j, divide(m, s, cos_pi(m, 2 * j + 7, D24)));
        m->edx = 4 * j;
        for (uint32_t i = 0; i < 6; i++)
        {
            const uint32_t n = 2 * j + 7 + i * (4 * j + 14);
            store(m, COS1 + 24 * j + 4 * i, unary(m, COS, mul(m, from_int(m, n), PI_24)));
        }
    }
}

/* win1: each window with its odd lines negated. Leaves ecx as the original does: 1, or the last
 * odd line count reached. */
static void odd_windows(Math *m)
{
    for (uint32_t k = 0; k < 4; k++)
    {
        const int32_t count = (int32_t)port_u32(m->port, WINDOW_LENGTHS, 4 * k);
        const uint32_t window = k * WINDOW_BYTES;
        for (int32_t i = 0; i < count; i += 2)
        {
            table_set32(m->port, WINDOWS_ODD + window + 4 * i, 0,
                        port_u32(m->port, WINDOWS + window + 4 * i, 0));
        }
        int32_t i = 1;
        for (; i < count; i += 2)
        {
            table_set32(m->port, WINDOWS_ODD + window + 4 * i, 0,
                        port_call(m->port, NEGATE, port_u32(m->port, WINDOWS + window + 4 * i, 0),
                                  0, 0, 0));
        }
        m->ebx = 4 * k;
        m->ecx = (uint32_t)i;
    }
    m->edx = 0;
}

static void stereo_ratios(Math *m)
{
    for (uint32_t i = 0; i < 16; i++)
    {
        const Double t = unary(m, TAN, divide(m, mul(m, from_int(m, i), PI), D12));
        const Double sum = add(m, t, ONE);
        store(m, TAN1_1 + 4 * i, divide(m, t, sum));
        store(m, TAN2_1 + 4 * i, divide(m, ONE, sum));
        store(m, TAN1_2 + 4 * i, divide(m, mul(m, t, SQRT2), sum));
        store(m, TAN2_2 + 4 * i, divide(m, SQRT2, sum));
        m->edx = 4 * i;
        m->ebx = 0;
        for (uint32_t j = 0; j < 2; j++)
        {
            const Double base = power(m, TWO, mul(m, add(m, from_int(m, j), ONE), MINUS_QUARTER));
            Double p1 = ONE;
            Double p2 = ONE;
            if (i > 0)
            {
                if (i & 1)
                {
                    p1 = power(m, base, mul(m, add(m, from_int(m, i), ONE), HALF));
                }
                else
                {
                    p2 = power(m, base, mul(m, from_int(m, i), HALF));
                }
            }
            const uint32_t at = 4 * i + 0x40 * j;
            store(m, POW1_1 + at, p1);
            store(m, POW2_1 + at, p2);
            store(m, POW1_2 + at, mul(m, p1, SQRT2));
            store(m, POW2_2 + at, mul(m, p2, SQRT2));
            /* The next offset, and the loop counter. */
            m->edx = at + 0x40;
            m->ecx = j + 1;
        }
    }
}

static int32_t s16(Port *port, uint32_t at)
{
    return (int16_t)port_u16(port, at, 0);
}

static uint32_t put(Port *port, uint32_t at, uint32_t value)
{
    table_set32(port, at, 0, value);
    return at + 4;
}

/* Short bands from `first` on: width, start of each window's lines, window, band. */
static uint32_t short_bands(Port *port, uint32_t out, uint32_t diff, uint32_t first, uint32_t start)
{
    for (uint32_t band = first; band < 13; band++)
    {
        const int32_t width = s16(port, diff + 2 * (band - first)) >> 1;
        for (uint32_t window = 0; window < 3; window++)
        {
            out = put(port, out, (uint32_t)width);
            out = put(port, out, start + window);
            out = put(port, out, window);
            out = put(port, out, band);
        }
        start += (uint32_t)(width * 6);
    }
    return out;
}

static void band_maps(Port *port, uint32_t limit)
{
    for (uint32_t j = 0; j < BANDS; j++)
    {
        const uint32_t info = BAND_INFO + j * BAND_INFO_BYTES;
        const uint32_t ends = MAP_END + 12 * j;
        const uint32_t maps = MAP + 12 * j;
        /* Mixed blocks: eight long bands, then the short ones from band 3. */
        uint32_t out = MAP_MIXED + j * MAP_MIXED_BYTES;
        table_set32(port, maps, 0, out);
        uint32_t start = 0;
        for (uint32_t i = 0; i < 8; i++)
        {
            const int32_t diff = s16(port, info + BAND_LONG_DIFF + 2 * i);
            out = put(port, out, (uint32_t)(diff >> 1));
            out = put(port, out, start);
            out = put(port, out, 3);
            out = put(port, out, i);
            start += (uint32_t)diff;
        }
        out = short_bands(port, out, info + BAND_SHORT_DIFF + 6, 3, start);
        table_set32(port, ends, 0, out);
        /* Short blocks. */
        out = MAP_SHORT + j * MAP_SHORT_BYTES;
        table_set32(port, maps, 4, out);
        out = short_bands(port, out, info + BAND_SHORT_DIFF, 0, 0);
        table_set32(port, ends, 4, out);
        /* Long blocks: width and band. */
        out = MAP_LONG + j * MAP_LONG_BYTES;
        table_set32(port, maps, 8, out);
        for (uint32_t i = 0; i < 22; i++)
        {
            out = put(port, out, (uint32_t)(s16(port, info + BAND_LONG_DIFF + 2 * i) >> 1));
            out = put(port, out, i);
        }
        table_set32(port, ends, 8, out);
    }
    /* The last subband of each band, at most the limit. */
    for (uint32_t j = 0; j < BANDS; j++)
    {
        const uint32_t info = BAND_INFO + j * BAND_INFO_BYTES;
        for (uint32_t i = 0; i < 23; i++)
        {
            int32_t last = (s16(port, info + 2 * i) + 7) / 18 + 1;
            if (last > (int32_t)limit)
            {
                last = (int32_t)limit;
            }
            table_set32(port, LONG_LIMIT + j * LONG_LIMIT_BYTES, 4 * i, (uint32_t)last);
        }
        for (uint32_t i = 0; i < 14; i++)
        {
            int32_t last = (s16(port, info + BAND_SHORT_INDEX + 2 * i) - 1) / 18 + 1;
            if (last > (int32_t)limit)
            {
                last = (int32_t)limit;
            }
            table_set32(port, SHORT_LIMIT + j * SHORT_LIMIT_BYTES, 4 * i, (uint32_t)last);
        }
    }
}

/* The scale factor lengths: i, j, k and l packed by three bits, with the table's tag. */
static void scale_lengths(Port *port)
{
    for (uint32_t i = 0; i < 5; i++)
    {
        for (uint32_t j = 0; j < 6; j++)
        {
            for (uint32_t k = 0; k < 6; k++)
            {
                table_set32(port, N_SLEN2 + 0x800 + 0x90 * i + 0x18 * j, 4 * k,
                            i | (j << 3) | (k << 6) | 0x3000);
            }
        }
    }
    for (uint32_t i = 0; i < 4; i++)
    {
        for (uint32_t j = 0; j < 4; j++)
        {
            for (uint32_t k = 0; k < 4; k++)
            {
                table_set32(port, N_SLEN2 + 0xad0 + 0x40 * i + 0x10 * j, 4 * k,
                            i | (j << 3) | (k << 6) | 0x4000);
            }
        }
    }
    for (uint32_t i = 0; i < 4; i++)
    {
        for (uint32_t j = 0; j < 3; j++)
        {
            const uint32_t value = i | (j << 3);
            table_set32(port, N_SLEN2 + 0xbd0 + 0xc * i, 4 * j, value | 0x5000);
            table_set32(port, I_SLEN2 + 0xc * i, 4 * j, value | 0xa000);
        }
    }
    for (uint32_t i = 0; i < 5; i++)
    {
        for (uint32_t j = 0; j < 5; j++)
        {
            for (uint32_t k = 0; k < 4; k++)
            {
                for (uint32_t l = 0; l < 4; l++)
                {
                    table_set32(port, N_SLEN2 + 0x140 * i + 0x40 * j + 0x10 * k, 4 * l,
                                i | (j << 3) | (k << 6) | (l << 9));
                }
            }
        }
    }
    for (uint32_t i = 0; i < 5; i++)
    {
        for (uint32_t j = 0; j < 5; j++)
        {
            for (uint32_t k = 0; k < 4; k++)
            {
                table_set32(port, N_SLEN2 + 0x640 + 0x50 * i + 0x10 * j, 4 * k,
                            i | (j << 3) | (k << 6) | 0x1000);
            }
        }
    }
}

/* Original 0x406170 (eax = the subband limit). The soft-float routines that take one operand still
 * read ebx:ecx, as the original leaves them; the first conversion gets the caller's ecx. */
int vertrix_mpeg_tables_memo;

uint32_t vertrix_port_mpeg_tables_init_406170(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    if (memo.ready && entry->eax == memo.eax && entry->edx == memo.edx && entry->ebx == memo.ebx &&
        entry->ecx == memo.ecx)
    {
        for (unsigned i = 0; i < memo.count; i++)
        {
            port_set32(&port, memo.address[i], 0, memo.value[i]);
        }
        vertrix_lift_fl = memo.flags;
        return port_return(&port, 0, 0);
    }
    memo.recording = vertrix_mpeg_tables_memo && !memo.ready;
    memo.count = 0;
    Math m = {&port, entry->edx, entry->ebx, entry->ecx};
    powers(&m);
    windows(&m);
    cosines(&m);
    odd_windows(&m);
    stereo_ratios(&m);
    band_maps(&port, entry->eax);
    scale_lengths(&port);
    if (memo.recording && !port.env.failed)
    {
        memo.ready = 1;
        memo.eax = entry->eax;
        memo.edx = entry->edx;
        memo.ebx = entry->ebx;
        memo.ecx = entry->ecx;
        memo.flags = vertrix_lift_fl;
    }
    memo.recording = 0;
    return port_return(&port, 0, 0);
}
