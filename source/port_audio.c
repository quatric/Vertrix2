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
    SAMPLE_MIN = 0x8000
};

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
