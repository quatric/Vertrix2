#include "port_audio.h"

enum
{
    SYNTH_WINDOW = 0x404730,
    SYNTH_FILTER = 0x405720,
    SYNTH_TRANSFORM = 0x405680,
    SAMPLES = 32,
    SAMPLE_BYTES = 2,
    DECODER = 0x51f01c,
    DECODER_PHASE = 0x476c,
    DECODER_LEFT = 0x366c,
    DECODER_RIGHT = 0x3eec,
    BUFFER_SECOND = 0x440,
    BUFFER_ROW = 0x40,
    WINDOW_END = 0x52e7c4,
    WINDOW_ROW = 0x80,
    OUTPUT_STEP = 0x4056b0,
    OUTPUT_ADVANCE = 0x80,
    TAPS = 16,
    ROW_EFFECT = 3,
    MIXER_MODE = 0x52fc1c,
    OUTPUT_STEREO = 0x401054,
    OUTPUT_MONO = 0x401010,
    ROW_PARAMETER = 4,
    EFFECTS = 0x24,
    EFFECT_TABLE = 0x4f7444,
    DCT_POINTS = 32,
    /* Pointers to the cosine tables of the transform's five passes. */
    DCT_COSINES = 0x4f5f90,
    /* esi, edi, ebp and 0xc bytes of locals. */
    DCT_FRAME = 0x18,
    DCT_TABLE_SLOT = 1,
    PHASES = 16,
    SINGLE_MULTIPLY = 0x4d8177,
    SINGLE_SUBTRACT = 0x4d809c,
    SINGLE_ADD = 0x4d80a6,
    SINGLE_NEGATE = 0x4eb5b4,
    SINGLE_TO_DOUBLE = 0x4eb526,
    DOUBLE_COMPARE = 0x4eb57c,
    SINGLE_TO_INT32 = 0x4d67a8,
    /* The high dwords of 32767.0 and -32768.0 (their low dwords are 0). */
    SAMPLE_MAX_HIGH = 0x40dfffc0,
    SAMPLE_MIN_HIGH = 0xc0e00000,
    SAMPLE_MAX = 0x7fff,
    SAMPLE_MIN = 0x8000,
    BIT_POSITION = 0x51f014,
    BIT_OFFSET = 0x51f018,
    BITS_WINDOW = 16,
    BITS_WINDOW24 = 24,
    MIXER_FLAGS = 0x52fc1d,
    MIXER_STEREO = 1,
    MIXER_RENDER = 0x52fc34,
    MIXER_RENDER_RAMP = 0x52fc38,
    CHANNEL_POSITION = 4,
    CHANNEL_STEP = 8,
    CHANNEL_LOOP_START = 0xc,
    CHANNEL_LOOP_END = 0x10,
    CHANNEL_STATE = 0x16,
    CHANNEL_STOPPED = 1,
    CHANNEL_RAMP = 2,
    CHANNEL_LOOP = 4,
    CHANNEL_PING_PONG = 8,
    CHANNEL_BACKWARD = 0x10
};

/* 0x404730's state: the work buffers, which its helpers also see in ebx and ecx. */
typedef struct Dct
{
    Port port;
    uint32_t first;
    uint32_t second;
    uint32_t result;
    uint32_t edx;
    /* The original's esp: its first local is pass 1's table, the third pass 4's first cosine. */
    uint32_t frame;
} Dct;

static uint32_t dct_call(Dct *dct, uint32_t target, uint32_t eax, uint32_t edx)
{
    dct->result = port_call(&dct->port, target, eax, edx, dct->first, dct->second);
    dct->edx = vertrix_lift_edx;
    return dct->result;
}

static uint32_t dct_at(Dct *dct, uint32_t buffer, unsigned index)
{
    return port_u32(&dct->port, buffer, index * 4);
}

static void dct_set(Dct *dct, uint32_t buffer, unsigned index, uint32_t value)
{
    port_set32(&dct->port, buffer, index * 4, value);
}

/* to[low] = from[low] + from[high]; to[high] = (from[low] - from[high]) * cosine, the difference
 * the other way round when `reversed`. The cosine is read from `table` (at `index`) after the
 * difference, or given in `cosine` when `table` is 0. */
static uint32_t dct_pair(Dct *dct, uint32_t from, uint32_t to, unsigned low, unsigned high,
                         int reversed, uint32_t table, unsigned index, uint32_t cosine)
{
    uint32_t difference;
    dct_set(dct, to, low,
            dct_call(dct, SINGLE_ADD, dct_at(dct, from, low), dct_at(dct, from, high)));
    difference =
        reversed ? dct_call(dct, SINGLE_SUBTRACT, dct_at(dct, from, high), dct_at(dct, from, low))
                 : dct_call(dct, SINGLE_SUBTRACT, dct_at(dct, from, low), dct_at(dct, from, high));
    if (table == DCT_TABLE_SLOT)
    {
        /* The first pass's table is kept in the frame and read back for each cosine; but for the
         * first and last pair, the difference is parked in the frame meanwhile. */
        if (index != 0 && index != DCT_POINTS / 2 - 1)
        {
            port_set32(&dct->port, dct->frame, 4, difference);
        }
        cosine = port_u32(&dct->port, port_u32(&dct->port, dct->frame, 0), index * 4);
    }
    else if (table != 0)
    {
        cosine = port_u32(&dct->port, table, index * 4);
    }
    dct_set(dct, to, high, dct_call(dct, SINGLE_MULTIPLY, difference, cosine));
    return dct->result;
}

/* One butterfly pass over groups of `size`, every other group's differences reversed. */
static void dct_pass(Dct *dct, uint32_t from, uint32_t to, unsigned size, uint32_t table)
{
    unsigned base;
    unsigned i;
    for (base = 0; base < DCT_POINTS; base += size)
    {
        int reversed = size < DCT_POINTS && (base / size) & 1;
        for (i = 0; i < size / 2; i++)
        {
            dct_pair(dct, from, to, base + i, base + size - 1 - i, reversed, table, i, 0);
        }
    }
}

/* out[offset] = first[a] + first[b]. */
static void dct_sum(Dct *dct, uint32_t out, uint32_t offset, unsigned a, unsigned b)
{
    port_set32(&dct->port, out, offset,
               dct_call(dct, SINGLE_ADD, dct_at(dct, dct->first, a), dct_at(dct, dct->first, b)));
}

static void dct_accumulate(Dct *dct, unsigned a, unsigned b)
{
    dct_set(dct, dct->first, a,
            dct_call(dct, SINGLE_ADD, dct_at(dct, dct->first, a), dct_at(dct, dct->first, b)));
}

static uint32_t dct_copy(Dct *dct, uint32_t out, uint32_t offset, unsigned index)
{
    uint32_t value = dct_at(dct, dct->first, index);
    port_set32(&dct->port, out, offset, value);
    return value;
}

uint32_t vertrix_port_synth_dct(PORT_SIGNATURE)
{
    Dct dct;
    uint32_t low = entry->eax;
    uint32_t high = entry->edx;
    uint32_t samples = entry->arguments[0];
    uint32_t table;
    uint32_t cosine_a;
    uint32_t cosine_b;
    unsigned base;
    unsigned i;
    port_open_frame(&dct.port, calls, services, globals, entry, DCT_FRAME);
    dct.frame = entry->esp - DCT_FRAME;
    port_set32(&dct.port, entry->esp, -4u, entry->esi);
    port_set32(&dct.port, entry->esp, -8u, entry->edi);
    port_set32(&dct.port, entry->esp, -12u, entry->ebp);
    dct.first = entry->ebx;
    dct.second = entry->ecx;
    dct.edx = entry->edx;
    /* Pass 1, samples into the first buffer: 16 pairs from the ends inwards. */
    port_set32(&dct.port, dct.frame, 0, port_u32(&dct.port, 0, DCT_COSINES));
    for (i = 0; i < DCT_POINTS / 2; i++)
    {
        dct_pair(&dct, samples, dct.first, i, DCT_POINTS - 1 - i, 0, DCT_TABLE_SLOT, i, 0);
    }
    /* Passes 2 and 3: halves of 16 and quarters of 8, the odd ones reversed. */
    dct_pass(&dct, dct.first, dct.second, 16, port_u32(&dct.port, 0, DCT_COSINES + 4));
    dct_pass(&dct, dct.second, dct.first, 8, port_u32(&dct.port, 0, DCT_COSINES + 8));
    /* Pass 4, groups of 4 with two cosines read once. */
    table = port_u32(&dct.port, 0, DCT_COSINES + 12);
    port_set32(&dct.port, dct.frame, 8, port_u32(&dct.port, table, 0));
    cosine_b = port_u32(&dct.port, table, 4);
    for (base = 0; base < DCT_POINTS; base += 4)
    {
        int reversed = (base / 4) & 1;
        dct_pair(&dct, dct.first, dct.second, base, base + 3, reversed, 0, 0,
                 port_u32(&dct.port, dct.frame, 8));
        dct_pair(&dct, dct.first, dct.second, base + 1, base + 2, reversed, 0, 0, cosine_b);
    }
    /* Pass 5, pairs with one cosine, each group of 8 then folded. */
    cosine_a = port_u32(&dct.port, port_u32(&dct.port, 0, DCT_COSINES + 16), 0);
    for (base = 0; base < DCT_POINTS; base += 8)
    {
        uint32_t product;
        dct_pair(&dct, dct.second, dct.first, base, base + 1, 0, 0, 0, cosine_a);
        product = dct_pair(&dct, dct.second, dct.first, base + 2, base + 3, 1, 0, 0, cosine_a);
        dct_set(&dct, dct.first, base + 2,
                dct_call(&dct, SINGLE_ADD, dct_at(&dct, dct.first, base + 2), product));
        dct_pair(&dct, dct.second, dct.first, base + 4, base + 5, 0, 0, 0, cosine_a);
        product = dct_pair(&dct, dct.second, dct.first, base + 6, base + 7, 1, 0, 0, cosine_a);
        dct_set(&dct, dct.first, base + 6,
                dct_call(&dct, SINGLE_ADD, dct_at(&dct, dct.first, base + 6), product));
        dct_set(&dct, dct.first, base + 4,
                dct_call(&dct, SINGLE_ADD, dct_at(&dct, dct.first, base + 4), dct.result));
        dct_accumulate(&dct, base + 6, base + 5);
        dct_accumulate(&dct, base + 5, base + 7);
    }
    /* The outputs: the first 8 copied, */
    dct_copy(&dct, low, 0x400, 0);
    dct_copy(&dct, low, 0x300, 4);
    dct_copy(&dct, low, 0x200, 2);
    dct_copy(&dct, low, 0x100, 6);
    port_set32(&dct.port, high, 0, dct_copy(&dct, low, 0, 1));
    dct_copy(&dct, high, 0x100, 5);
    dct_copy(&dct, high, 0x200, 3);
    dct_copy(&dct, high, 0x300, 7);
    /* the next 8 summed in place, */
    {
        static const struct
        {
            uint8_t a, b, high;
            uint16_t offset;
        } middle[] = {{8, 12, 0, 0x380}, {12, 10, 0, 0x280}, {10, 14, 0, 0x180}, {14, 9, 0, 0x80},
                      {9, 13, 1, 0x80},  {13, 11, 1, 0x180}, {11, 15, 1, 0x280}};
        for (i = 0; i < sizeof middle / sizeof middle[0]; i++)
        {
            dct_accumulate(&dct, middle[i].a, middle[i].b);
            port_set32(&dct.port, middle[i].high ? high : low, middle[i].offset, dct.result);
        }
        dct_copy(&dct, high, 0x380, 15);
    }
    /* and the last 16 from pairwise sums. */
    {
        static const struct
        {
            uint8_t a, b, first, second;
            uint16_t first_offset, second_offset;
        } last[] = {{24, 28, 16, 20, 0x3c0, 0x340},
                    {28, 26, 20, 18, 0x2c0, 0x240},
                    {26, 30, 18, 22, 0x1c0, 0x140},
                    {30, 25, 22, 17, 0xc0, 0x40},
                    {25, 29, 17, 21, 0x40 | 0x8000, 0xc0 | 0x8000},
                    {29, 27, 21, 19, 0x140 | 0x8000, 0x1c0 | 0x8000},
                    {27, 31, 19, 23, 0x240 | 0x8000, 0x2c0 | 0x8000}};
        for (i = 0; i < sizeof last / sizeof last[0]; i++)
        {
            uint32_t out = last[i].first_offset & 0x8000 ? high : low;
            dct_accumulate(&dct, last[i].a, last[i].b);
            dct_sum(&dct, out, last[i].first_offset & 0x7fff, last[i].first, last[i].a);
            dct_sum(&dct, out, last[i].second_offset & 0x7fff, last[i].a, last[i].second);
        }
        dct_sum(&dct, high, 0x340, 23, 31);
    }
    return port_return(&dct.port, dct_copy(&dct, high, 0x3c0, 31), dct.edx);
}

uint32_t vertrix_port_synth_window(PORT_SIGNATURE)
{
    /* push ebp, push ecx, 0x100 bytes of buffers, push ebx. */
    enum
    {
        BELOW = 0x10c
    };
    uint8_t stack[BELOW + 8];
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t argument = entry->ebx;
    uint32_t result;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x108u, entry->ebx);
    result = port_call_stack(&port, SYNTH_WINDOW, entry->eax, entry->edx, ebp - 0x104, ebp - 0x84,
                             &argument, 1);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_synth_samples(PORT_SIGNATURE)
{
    /* push ebp, ecx, esi and edi, then 0x88 bytes of locals. */
    enum
    {
        BELOW = 0x98
    };
    uint8_t stack[BELOW + 8];
    Port port;
    uint32_t ebp = entry->esp - 4;
    uint32_t buffer = ebp - 0x94;
    uint32_t offset_address;
    uint32_t output;
    uint32_t result;
    uint32_t edx;
    unsigned i;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    port_set32(&port, ebp, -0x10u, entry->ebx);
    port_set32(&port, ebp, -0x14u, 0);
    result = port_call(&port, SYNTH_FILTER, entry->eax, 0, buffer, ebp - 0x14);
    edx = vertrix_lift_edx;
    offset_address = port_u32(&port, ebp, -0x10u);
    output = entry->edx + port_u32(&port, offset_address, 0);
    for (i = 0; i < SAMPLES; i++)
    {
        edx = (edx & 0xffff0000u) | port_u16(&port, buffer, i * 4);
        port_set16(&port, output, i * SAMPLE_BYTES, edx);
    }
    offset_address = port_u32(&port, ebp, -0x10u);
    port_set32(&port, offset_address, 0, port_u32(&port, offset_address, 0) + SAMPLES * 2);
    return port_return(&port, result, edx);
}

/* The state of 0x405720 across its calls: the registers its helpers see (ebx and ecx carry over
 * from one call to the next, edx is the last call's) and the output. */
typedef struct Synth
{
    Port port;
    uint32_t ebx;
    uint32_t ecx;
    uint32_t edx;
    uint32_t output;
    uint32_t clipped;
} Synth;

static uint32_t synth_call(Synth *synth, uint32_t target, uint32_t eax, uint32_t edx)
{
    uint32_t result = port_call(&synth->port, target, eax, edx, synth->ebx, synth->ecx);
    synth->edx = vertrix_lift_edx;
    return result;
}

/* Store the single `sum` at the output as a 16-bit sample: 0x7fff above 32767.0 and 0x8000 below
 * -32768.0 (both counted as clipped; edx stays the compare's), otherwise 0x4d67a8's integer
 * (edx the output). The compares leave ebx 0 and ecx the high dword of the last limit. */
static void synth_sample(Synth *synth, uint32_t sum)
{
    uint32_t low = synth_call(synth, SINGLE_TO_DOUBLE, sum, synth->edx);
    uint32_t high = synth->edx;
    LiftFlags flags;
    synth->ebx = 0;
    synth->ecx = SAMPLE_MAX_HIGH;
    synth_call(synth, DOUBLE_COMPARE, low, high);
    flags = vertrix_lift_fl;
    if (!flags.zf && flags.sf == flags.of)
    {
        port_set16(&synth->port, synth->output, 0, SAMPLE_MAX);
        synth->clipped++;
        return;
    }
    synth->ecx = SAMPLE_MIN_HIGH;
    synth_call(synth, DOUBLE_COMPARE, low, high);
    flags = vertrix_lift_fl;
    if (flags.sf != flags.of)
    {
        port_set16(&synth->port, synth->output, 0, SAMPLE_MIN);
        synth->clipped++;
        return;
    }
    port_set16(&synth->port, synth->output, 0, synth_call(synth, SINGLE_TO_INT32, sum, synth->edx));
    synth->edx = synth->output;
}

static uint32_t synth_product(Synth *synth, uint32_t window, uint32_t buffer)
{
    return synth_call(synth, SINGLE_MULTIPLY, window, buffer);
}

uint32_t vertrix_port_synth_filter(PORT_SIGNATURE)
{
    Synth synth;
    uint32_t offset_address = entry->ecx;
    uint32_t decoder;
    uint32_t channel;
    uint32_t phase;
    uint32_t start;
    uint32_t window;
    uint32_t buffer;
    uint32_t step;
    uint32_t row;
    unsigned tap;
    port_open(&synth.port, calls, services, globals, entry);
    synth.output = port_u32(&synth.port, offset_address, 0) + entry->ebx;
    synth.clipped = 0;
    decoder = port_u32(&synth.port, 0, DECODER);
    phase = port_u32(&synth.port, decoder, DECODER_PHASE);
    if (entry->edx != 0)
    {
        /* The right channel: the second sample of each pair, at the phase the left one set. */
        synth.output += SAMPLE_BYTES;
        channel = decoder + DECODER_RIGHT;
    }
    else
    {
        phase = (phase - 1) & (PHASES - 1);
        channel = decoder + DECODER_LEFT;
    }
    /* 0x405680 transforms the subband samples into the two halves of the channel's buffer, the
     * one it writes depending on the phase. */
    synth.ebx = entry->eax;
    synth.ecx = phase;
    if (phase & 1)
    {
        buffer = channel;
        start = phase;
        port_call(&synth.port, SYNTH_TRANSFORM,
                  channel + BUFFER_SECOND + ((phase + 1) & (PHASES - 1)) * 4, channel + phase * 4,
                  synth.ebx, synth.ecx);
    }
    else
    {
        buffer = channel + BUFFER_SECOND;
        start = phase + 1;
        port_call(&synth.port, SYNTH_TRANSFORM, channel + phase * 4,
                  channel + BUFFER_SECOND + phase * 4 + 4, synth.ebx, synth.ecx);
    }
    port_set32(&synth.port, port_u32(&synth.port, 0, DECODER), DECODER_PHASE, phase);
    window = WINDOW_END - start * 4;
    step = port_u32(&synth.port, 0, OUTPUT_STEP) * 2;
    /* The first 16 samples: the window's taps against the buffer's, alternately subtracted and
     * added. */
    for (row = TAPS; row != 0;)
    {
        uint32_t sum = synth_product(&synth, port_u32(&synth.port, window, 0),
                                     port_u32(&synth.port, buffer, 0));
        for (tap = 1; tap < TAPS; tap++)
        {
            uint32_t product = synth_product(&synth, port_u32(&synth.port, window, tap * 4),
                                             port_u32(&synth.port, buffer, tap * 4));
            sum = synth_call(&synth, (tap & 1) ? SINGLE_SUBTRACT : SINGLE_ADD, sum, product);
        }
        synth_sample(&synth, sum);
        row--;
        buffer += BUFFER_ROW;
        window += WINDOW_ROW;
        synth.output += step;
        synth.ebx = row;
    }
    /* The middle sample: the even taps added. */
    {
        uint32_t sum = synth_product(&synth, port_u32(&synth.port, window, 0),
                                     port_u32(&synth.port, buffer, 0));
        synth.ecx = sum;
        for (tap = 2; tap < TAPS; tap += 2)
        {
            uint32_t product = synth_product(&synth, port_u32(&synth.port, window, tap * 4),
                                             port_u32(&synth.port, buffer, tap * 4));
            sum = synth_call(&synth, SINGLE_ADD, sum, product);
        }
        synth_sample(&synth, sum);
    }
    step = port_u32(&synth.port, 0, OUTPUT_STEP) * 2;
    buffer -= BUFFER_ROW;
    window -= WINDOW_ROW;
    synth.output += step;
    synth.edx = start * 8;
    window += synth.edx;
    /* The last 15 samples: the window read backwards from its row's end, its first tap negated,
     * every product subtracted. */
    for (row = TAPS - 1; row != 0;)
    {
        uint32_t sum =
            synth_call(&synth, SINGLE_NEGATE, port_u32(&synth.port, window, -4u), synth.edx);
        sum = synth_product(&synth, sum, port_u32(&synth.port, buffer, 0));
        for (tap = 1; tap < TAPS; tap++)
        {
            uint32_t at = tap == TAPS - 1 ? 0 : -4u - tap * 4;
            uint32_t product = synth_product(&synth, port_u32(&synth.port, window, at),
                                             port_u32(&synth.port, buffer, tap * 4));
            sum = synth_call(&synth, SINGLE_SUBTRACT, sum, product);
        }
        synth_sample(&synth, sum);
        row--;
        synth.ebx = row;
        buffer -= BUFFER_ROW;
        window -= WINDOW_ROW;
        synth.output += step;
    }
    port_set32(&synth.port, offset_address, 0,
               port_u32(&synth.port, offset_address, 0) + OUTPUT_ADVANCE);
    return port_return(&synth.port, synth.clipped, synth.edx);
}

uint32_t vertrix_port_bits_get(PORT_SIGNATURE)
{
    Port port;
    uint32_t count = entry->eax;
    uint32_t position;
    uint32_t value;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    position = port_u32(&port, 0, BIT_POSITION);
    value = (port_u8(&port, position, 0) << 8) | port_u8(&port, position, 1);
    value = port_shl(value, port_u8(&port, 0, BIT_OFFSET)) & 0xffff;
    offset = port_u32(&port, 0, BIT_OFFSET) + count;
    port_set32(&port, 0, BIT_OFFSET, offset);
    value = port_shr(value, BITS_WINDOW - count);
    offset = port_u32(&port, 0, BIT_OFFSET);
    port_set32(&port, 0, BIT_POSITION, position + (uint32_t)((int32_t)offset >> 3));
    port_set32(&port, 0, BIT_OFFSET, port_u32(&port, 0, BIT_OFFSET) & 7);
    return port_return(&port, value, entry->edx);
}

uint32_t vertrix_port_bit_get(PORT_SIGNATURE)
{
    Port port;
    uint32_t position;
    uint32_t byte;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    position = port_u32(&port, 0, BIT_POSITION);
    byte = port_shl(port_u8(&port, position, 0), port_u8(&port, 0, BIT_OFFSET)) & 0xff;
    offset = port_u32(&port, 0, BIT_OFFSET) + 1;
    port_set32(&port, 0, BIT_OFFSET, offset);
    port_set32(&port, 0, BIT_POSITION, position + (uint32_t)((int32_t)offset >> 3));
    port_set32(&port, 0, BIT_OFFSET, offset & 7);
    return port_return(&port, byte >> 7, entry->edx);
}

static uint32_t channel_state(Port *port, uint32_t channel)
{
    return port_u8(port, channel, CHANNEL_STATE);
}

static void negate_step(Port *port, uint32_t channel)
{
    port_set32(port, channel, CHANNEL_STEP, -port_u32(port, channel, CHANNEL_STEP));
}

uint32_t vertrix_port_mixer_channel(PORT_SIGNATURE)
{
    Port port;
    uint32_t channel = entry->ebx;
    uint32_t buffer = entry->eax;
    uint32_t left = entry->edx;
    /* eax, edx and ecx as the original leaves them: its result, and what the render receives. */
    uint32_t eax = entry->eax;
    uint32_t edx = entry->edx;
    uint32_t ecx = entry->ecx;
    LiftFlags flags = {0, 0, 0, 0, 0, 0};
    port_open(&port, calls, services, globals, entry);
    if (port_u8(&port, 0, MIXER_FLAGS) & MIXER_STEREO)
    {
        left >>= 1;
    }
    while (left != 0)
    {
        uint32_t state = channel_state(&port, channel);
        uint32_t run;
        edx = (edx & 0xffffff00u) | state;
        if (state & CHANNEL_STOPPED)
        {
            break;
        }
        if (state & CHANNEL_BACKWARD)
        {
            eax = port_u32(&port, channel, CHANNEL_POSITION);
            edx = port_u32(&port, channel, CHANNEL_LOOP_START);
            if ((int32_t)eax < (int32_t)edx)
            {
                /* Before the loop start: turn, wrap or stop. */
                state = channel_state(&port, channel);
                eax = (eax & 0xffff00ffu) | (state << 8);
                if (state & CHANNEL_PING_PONG)
                {
                    eax = edx - port_u32(&port, channel, CHANNEL_POSITION);
                    edx += eax;
                    port_set32(&port, channel, CHANNEL_POSITION, edx);
                    port_set8(&port, channel, CHANNEL_STATE,
                              channel_state(&port, channel) ^ CHANNEL_BACKWARD);
                    continue;
                }
                if (state & CHANNEL_LOOP)
                {
                    eax = edx - port_u32(&port, channel, CHANNEL_POSITION);
                    edx = port_u32(&port, channel, CHANNEL_LOOP_END) - eax;
                    port_set32(&port, channel, CHANNEL_POSITION, edx);
                    continue;
                }
                edx = (edx & 0xffff00ffu) | ((state | CHANNEL_STOPPED) << 8);
                port_set8(&port, channel, CHANNEL_STATE, state | CHANNEL_STOPPED);
                break;
            }
        }
        else
        {
            eax = port_u32(&port, channel, CHANNEL_POSITION);
            edx = port_u32(&port, channel, CHANNEL_LOOP_END);
            if ((int32_t)eax > (int32_t)edx)
            {
                /* Past the loop end. */
                state = channel_state(&port, channel);
                ecx = (ecx & 0xffffff00u) | state;
                if (state & CHANNEL_PING_PONG)
                {
                    eax -= edx;
                    edx -= eax;
                    port_set32(&port, channel, CHANNEL_POSITION, edx);
                    port_set8(&port, channel, CHANNEL_STATE,
                              channel_state(&port, channel) ^ CHANNEL_BACKWARD);
                    continue;
                }
                if (state & CHANNEL_LOOP)
                {
                    eax -= edx;
                    edx = port_u32(&port, channel, CHANNEL_LOOP_START) + eax;
                    port_set32(&port, channel, CHANNEL_POSITION, edx);
                    continue;
                }
                eax = (eax & 0xffffff00u) | (state | CHANNEL_STOPPED);
                port_set8(&port, channel, CHANNEL_STATE, state | CHANNEL_STOPPED);
                break;
            }
        }
        /* The samples to render: all that are left, or as many as reach the loop bound (rounded
         * up by the step, when the step passes it). */
        run = left;
        if (channel_state(&port, channel) & CHANNEL_BACKWARD)
        {
            edx = port_u32(&port, channel, CHANNEL_POSITION) -
                  port_u32(&port, channel, CHANNEL_LOOP_START);
            eax = port_u32(&port, channel, CHANNEL_STEP) * left;
            if (eax > edx)
            {
                ecx = port_u32(&port, channel, CHANNEL_STEP);
                edx += ecx;
                eax = edx;
                edx = (uint32_t)((int32_t)edx >> 31);
                lift_idiv1(32, ecx, &eax, &edx, &flags);
                run = eax;
            }
        }
        else
        {
            edx = port_u32(&port, channel, CHANNEL_LOOP_END) -
                  port_u32(&port, channel, CHANNEL_POSITION);
            eax = port_u32(&port, channel, CHANNEL_STEP) * left;
            if (eax > edx)
            {
                uint32_t step = port_u32(&port, channel, CHANNEL_STEP);
                edx += step;
                eax = edx;
                edx = (uint32_t)((int32_t)edx >> 31);
                lift_idiv1(32, step, &eax, &edx, &flags);
                run = eax;
            }
        }
        /* The render routines take (buffer, samples, channel) and step forward only: a backward
         * channel's step is negated around the call. */
        if (channel_state(&port, channel) & CHANNEL_BACKWARD)
        {
            negate_step(&port, channel);
        }
        {
            uint32_t stack[3] = {buffer, run, channel};
            if (channel_state(&port, channel) & CHANNEL_RAMP)
            {
                ecx = buffer;
                eax = port_call_stack(&port, port_u32(&port, 0, MIXER_RENDER_RAMP), eax, edx,
                                      channel, ecx, stack, 3);
            }
            else
            {
                edx = buffer;
                eax = port_call_stack(&port, port_u32(&port, 0, MIXER_RENDER), eax, edx, channel,
                                      ecx, stack, 3);
            }
            edx = vertrix_lift_edx;
        }
        if (channel_state(&port, channel) & CHANNEL_BACKWARD)
        {
            negate_step(&port, channel);
        }
        /* Four bytes a sample, both channels' samples for stereo. */
        edx = run * 4;
        ecx = buffer + edx;
        buffer = ecx;
        if (port_u8(&port, 0, MIXER_FLAGS) & MIXER_STEREO)
        {
            eax = ecx + edx;
            buffer = eax;
        }
        left -= run;
    }
    return port_return(&port, eax, edx);
}

uint32_t vertrix_port_bits_get24(PORT_SIGNATURE)
{
    Port port;
    uint32_t count = entry->eax;
    uint32_t position;
    uint32_t value;
    uint32_t offset;
    port_open(&port, calls, services, globals, entry);
    if (count == 0)
    {
        return port_return(&port, 0, entry->edx);
    }
    position = port_u32(&port, 0, BIT_POSITION);
    value = (port_u8(&port, position, 0) << 16) | (port_u8(&port, position, 1) << 8) |
            port_u8(&port, position, 2);
    value = port_shl(value, port_u8(&port, 0, BIT_OFFSET)) & 0xffffff;
    port_set32(&port, 0, BIT_OFFSET, port_u32(&port, 0, BIT_OFFSET) + count);
    value = port_shr(value, BITS_WINDOW24 - count);
    offset = port_u32(&port, 0, BIT_OFFSET);
    port_set32(&port, 0, BIT_POSITION, position + (uint32_t)((int32_t)offset >> 3));
    port_set32(&port, 0, BIT_OFFSET, port_u32(&port, 0, BIT_OFFSET) & 7);
    return port_return(&port, value, entry->edx);
}

uint32_t vertrix_port_mixer_effect(PORT_SIGNATURE)
{
    Port port;
    uint32_t row = entry->eax;
    uint32_t effect;
    uint32_t result = row;
    port_open(&port, calls, services, globals, entry);
    effect = port_u8(&port, row, ROW_EFFECT);
    if ((effect != 0 || port_u8(&port, row, ROW_PARAMETER) != 0) && effect < EFFECTS)
    {
        result = port_call(&port, port_u32(&port, 0, EFFECT_TABLE + effect * 4), row, effect,
                           (entry->ebx & 0xffffff00u) | effect, entry->ecx);
    }
    return port_return(&port, result, entry->edx);
}

uint32_t vertrix_port_mixer_output(PORT_SIGNATURE)
{
    Port port;
    uint32_t arguments[3] = {entry->eax, entry->edx, entry->ebx};
    uint32_t output;
    uint32_t result;
    port_open(&port, calls, services, globals, entry);
    output = (port_u8(&port, 0, MIXER_MODE) & MIXER_STEREO) ? OUTPUT_STEREO : OUTPUT_MONO;
    result = port_call_stack(&port, output, entry->eax, entry->edx, entry->ebx, entry->ecx,
                             arguments, 3);
    return port_return(&port, result, vertrix_lift_edx);
}

uint32_t vertrix_port_mix_clamp(PORT_SIGNATURE)
{
    Port port;
    uint32_t out = entry->arguments[0];
    uint32_t in = entry->arguments[1];
    int32_t count = (int32_t)entry->arguments[2];
    port_open(&port, calls, services, globals, entry);
    do
    {
        int32_t value = (int32_t)port_u32(&port, in, 0);
        if (value < -0x8000)
        {
            value = -0x8000;
        }
        else if (value > 0x7fff)
        {
            value = 0x7fff;
        }
        port_set16(&port, out, 0, (uint32_t)value);
        in += 4;
        out += 2;
    } while (--count > 0);
    return port_return(&port, entry->eax, entry->edx);
}
