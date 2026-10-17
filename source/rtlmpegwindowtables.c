#include "rtlmpegwindowtables.h"

/* Builds the MP3 IMDCT window tables from sines when the reader is reset. */

enum
{
    /* Five cosine tables of 16, 8, 4, 2 and 1 entries, each for a length of 64 >> n, written
     * through the table pointers at 0x4f5f90. */
    COSINE_TABLES = 0x4f5f90,
    COSINE_SIZES = 5,
    COSINE_COUNT = 0x10,
    COSINE_LENGTH = 0x40,

    /* The window: 512 coefficients from the integers at 0x4f5fa4, each stored twice (+0, +0x40)
     * in the rows from 0x52e784, 0x80 bytes apart; a row ending at 0x52efc4 or beyond is not
     * written. Every 32 entries the rows wrap back (0xffc), every 64 the sign flips. */
    WINDOW = 0x52e784,
    WINDOW_END = 0x52efc4,
    WINDOW_SOURCE = 0x4f5fa4,
    WINDOW_HALF = 0x100,
    WINDOW_COUNT = 0x200,
    ROW = 0x80,
    COPY = 0x40,
    WRAP = 0xffc,

    /* The high dwords of the doubles: 2.0, 1.0, 2^-16, and pi (low 0x54442d18). */
    TWO = 0x40000000,
    ONE = 0x3ff00000,
    SCALE = 0x3ef00000,
    PI_LOW = 0x54442d18,
    PI_HIGH = 0x400921fb,

    FROM_INTEGER = 0x4d6768,
    MULTIPLY = 0x4db507,
    ADD = 0x4db350,
    DIVIDE = 0x4eb652,
    COSINE = 0x4c9dd6,
    TO_SINGLE = 0x4eb606
};

/* The registers the software doubles go through (eax:edx and ebx:ecx), and the ones the helpers
 * also read: each helper gets what the original leaves in them (docs/NATIVE-PORTS.md). */
typedef struct
{
    uint32_t eax;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t esi;
    uint32_t edi;
    uint32_t ebp;
} Doubles;

static void helper(Port *port, uint32_t target, Doubles *d)
{
    d->eax = port_call_with(port, target, d->eax, d->edx, d->ebx, d->ecx, d->esi, d->edi, d->ebp);
    d->edx = vertrix_lift_edx;
}

/* One window coefficient: the integer at `source` times 2^-16 times the sign, as a single. The
 * original keeps the scaled value in two different register pairs in its two halves
 * (`second_half`), which changes what the helpers see in ebx and ecx. */
static uint32_t window_value(Port *port, Doubles *d, uint32_t source, uint32_t sign,
                             int second_half)
{
    d->eax = port_u32(port, source, 0);
    helper(port, FROM_INTEGER, d);
    d->ebx = 0;
    d->ecx = SCALE;
    helper(port, MULTIPLY, d);
    const uint32_t scaled_low = d->eax;
    const uint32_t scaled_high = d->edx;
    if (second_half)
    {
        d->ecx = scaled_low;
        d->ebx = scaled_high;
    }
    else
    {
        d->ecx = scaled_high;
    }
    d->eax = sign;
    helper(port, FROM_INTEGER, d);
    d->ebx = d->eax;
    d->ecx = d->edx;
    d->eax = scaled_low;
    d->edx = scaled_high;
    helper(port, MULTIPLY, d);
    helper(port, TO_SINGLE, d);
    return d->eax;
}

/* After each coefficient: the rows wrap every 32 entries and the sign flips every 64, using
 * idiv's quotient and remainder registers as the original does. */
static void window_step(Doubles *d, uint32_t index, uint32_t *row, uint32_t *sign)
{
    d->ecx = 0x20;
    d->eax = index / 0x20;
    d->edx = index % 0x20;
    if (d->edx == 0x1f)
    {
        *row -= WRAP;
    }
    d->ecx = 0x40;
    d->eax = index / 0x40;
    d->edx = index % 0x40;
    if (d->edx == 0x3f)
    {
        *sign = 0u - *sign;
    }
}

/* Original 0x40a590 (eax = the window's scale, a signed integer). For each of the five cosine
 * tables n and each i below 16 >> n, stores the single 1 / (2 cos(pi (2i + 1) / (64 >> n))).
 * Then the 512 window coefficients, the first 256 from 0x4f5fa4 forwards and the rest from
 * 0x4f5fa4 + 0x400 backwards, starting with the negated scale as the sign. Returns the caller's
 * edx; no caller reads eax. */
uint32_t vertrix_port_window_tables_40a590(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    Doubles d = {entry->eax, 0, entry->ebx, entry->ecx, entry->esi, entry->edi, entry->ebp};

    for (uint32_t n = 0; n < COSINE_SIZES && !port.env.failed; n++)
    {
        d.ecx = (d.ecx & 0xffffff00u) | n;
        const uint32_t count = COSINE_COUNT >> n;
        const uint32_t length = COSINE_LENGTH >> n;
        uint32_t out = port_u32(&port, COSINE_TABLES + n * 4, 0);
        d.eax = out;
        for (d.esi = 0; d.esi < count && !port.env.failed; d.esi++)
        {
            d.eax = d.esi;
            helper(&port, FROM_INTEGER, &d);
            d.ebx = 0;
            d.ecx = TWO;
            helper(&port, MULTIPLY, &d);
            d.ebx = 0;
            d.ecx = ONE;
            helper(&port, ADD, &d);
            d.ebx = PI_LOW;
            d.ecx = PI_HIGH;
            helper(&port, MULTIPLY, &d);
            const uint32_t angle_low = d.eax;
            const uint32_t angle_high = d.edx;
            d.ecx = angle_low;
            d.ebx = angle_high;
            d.eax = length;
            helper(&port, FROM_INTEGER, &d);
            d.edi = d.eax;
            d.ebp = d.edx;
            d.eax = angle_low;
            d.edx = angle_high;
            d.ebx = d.edi;
            d.ecx = d.ebp;
            helper(&port, DIVIDE, &d);
            helper(&port, COSINE, &d);
            d.ebx = 0;
            d.ecx = TWO;
            helper(&port, MULTIPLY, &d);
            d.ebx = d.eax;
            d.ecx = d.edx;
            d.eax = 0;
            d.edx = ONE;
            helper(&port, DIVIDE, &d);
            helper(&port, TO_SINGLE, &d);
            port_set32(&port, out, 0, d.eax);
            out += 4;
            d.edi = out;
        }
        d.edx = n + 1;
    }

    uint32_t sign = 0u - entry->eax;
    uint32_t row = WINDOW;
    d.edi = row;
    d.esi = 0;
    d.ebp = 0;
    for (; d.esi < WINDOW_HALF && !port.env.failed; d.esi++)
    {
        if (row < WINDOW_END)
        {
            const uint32_t value = window_value(&port, &d, WINDOW_SOURCE + d.esi * 4, sign, 0);
            port_set32(&port, row, 0, value);
            port_set32(&port, row, COPY, value);
        }
        window_step(&d, d.esi, &row, &sign);
        d.ebp++;
        row += ROW;
        d.edi = row;
    }
    uint32_t source = d.ebp * 4;
    for (; d.esi < WINDOW_COUNT && !port.env.failed; d.esi++)
    {
        if (row < WINDOW_END)
        {
            const uint32_t value = window_value(&port, &d, WINDOW_SOURCE + source, sign, 1);
            port_set32(&port, row, 0, value);
            port_set32(&port, row, COPY, value);
        }
        window_step(&d, d.esi, &row, &sign);
        source -= 4;
        d.ebp--;
        row += ROW;
        d.edi = row;
    }
    return port_return(&port, 0, entry->edx);
}
