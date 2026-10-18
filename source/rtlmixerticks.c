#include "rtlmixerticks.h"

enum
{
    /* The channel: its key-on byte (0 once released) and change flags (+1: 1 pitch, 2 volume, 4
     * panning), volume (+0x14) and the volume played (+0x18), panning (+0x1c) and the panning
     * played (+0x20), period (+0x28) and the period played (+0x2c), the instrument (+0x34), the
     * fadeout volume and its step (+0x78, +0x7c). */
    CHANNEL_KEY_ON = 0,
    CHANNEL_FLAGS = 1,
    FLAG_PERIOD = 1,
    FLAG_VOLUME = 2,
    FLAG_PANNING = 4,
    CHANNEL_VOLUME = 0x14,
    CHANNEL_VOLUME_OUT = 0x18,
    CHANNEL_PANNING = 0x1c,
    CHANNEL_PANNING_OUT = 0x20,
    CHANNEL_PERIOD = 0x28,
    CHANNEL_PERIOD_OUT = 0x2c,
    CHANNEL_INSTRUMENT = 0x34,
    CHANNEL_FADE = 0x78,
    CHANNEL_FADE_STEP = 0x7c,
    FADE_FULL = 0x7fff,

    /* An envelope's state in the channel: tick, value (8.8), point and step per tick; the volume
     * envelope's at +0x80, the panning envelope's at +0x90. */
    STATE_TICK = 0,
    STATE_VALUE = 4,
    STATE_POINT = 8,
    STATE_STEP = 0xc,
    VOLUME_STATE = 0x80,
    PANNING_STATE = 0x90,

    /* The instrument's envelopes: points (x, y words) from +0x88 (volume) and +0xc0 (panning),
     * then the point count, sustain point, loop start and loop end bytes and the flags (1 on, 2
     * sustain, 4 loop) at +0x30.. from the points. */
    VOLUME_POINTS = 0x88,
    PANNING_POINTS = 0xc0,
    ENVELOPE_COUNT = 0x30,
    ENVELOPE_SUSTAIN = 0x31,
    ENVELOPE_LOOP_START = 0x32,
    ENVELOPE_LOOP_END = 0x33,
    ENVELOPE_FLAGS = 0x34,
    ENVELOPE_ON = 1,
    ENVELOPE_SUSTAIN_ON = 2,
    ENVELOPE_LOOP_ON = 4,
    ENVELOPE_TOP = 0x4000,

    /* The instrument's vibrato: type, depth and rate bytes; the channel's vibrato depth (8.8),
     * its sweep and position. */
    INSTRUMENT_VIBRATO_TYPE = 0x82,
    INSTRUMENT_VIBRATO_DEPTH = 0x84,
    INSTRUMENT_VIBRATO_RATE = 0x85,
    CHANNEL_VIBRATO_POSITION = 0xa0,
    CHANNEL_VIBRATO_DEPTH = 0xa4,
    CHANNEL_VIBRATO_SWEEP = 0xa8,
    VIBRATO_SQUARE = 0x40,
    PERIOD_LOWEST = 1,
    PERIOD_HIGHEST = 0x7cff,

    /* The sine table: a signed byte per position, read as the top byte of the dword at
     * 0x4f7341 + position. */
    SINE_DWORDS = 0x4f7341,

    CENTRE = 0x80,
    PANNING_CENTRE = 0x2000
};

/* One envelope's step (0x40e070..0x40e0ec for volume, 0x40e122..0x40e19e for panning): the
 * next point's tick reached, the envelope stops at its sustain point while the key is on, else
 * loops back from its loop end, takes the point's value and the step towards the next point (0
 * at the last or when the points share a tick); between points the value moves by its step,
 * kept within 0..0x4000. */
static void envelope(Port *port, uint32_t channel, uint32_t instrument, uint32_t state,
                     uint32_t points)
{
    const uint32_t settings = instrument + points;
    const uint32_t flags = settings + ENVELOPE_FLAGS;
    const uint32_t x =
        port_u16(port, settings + 4 * port_u32(port, channel, state + STATE_POINT), 0);
    const uint32_t tick = port_u32(port, channel, state + STATE_TICK) + 1;
    port_set32(port, channel, state + STATE_TICK, tick);
    if ((int32_t)x > (int32_t)tick)
    {
        const uint32_t moved = port_u32(port, channel, state + STATE_VALUE) +
                               port_u32(port, channel, state + STATE_STEP);
        port_set32(port, channel, state + STATE_VALUE, moved);
        uint32_t value = moved;
        if ((int32_t)moved < 0)
        {
            value = 0;
        }
        else if ((int32_t)moved > ENVELOPE_TOP)
        {
            value = ENVELOPE_TOP;
        }
        port_set32(port, channel, state + STATE_VALUE, value);
        return;
    }
    if ((port_u8(port, flags, 0) & ENVELOPE_SUSTAIN_ON) != 0 &&
        port_u8(port, settings, ENVELOPE_SUSTAIN) == port_u32(port, channel, state + STATE_POINT) &&
        port_u8(port, channel, CHANNEL_KEY_ON) != 0)
    {
        const uint32_t point = port_u32(port, channel, state + STATE_POINT);
        port_set32(port, channel, state + STATE_TICK, port_u16(port, settings + 4 * point, 0));
        const uint32_t at = port_u32(port, channel, state + STATE_POINT);
        port_set32(port, channel, state + STATE_VALUE, port_u16(port, settings + 4 * at, 2) << 8);
        return;
    }
    if ((port_u8(port, flags, 0) & ENVELOPE_LOOP_ON) != 0 &&
        port_u8(port, settings, ENVELOPE_LOOP_END) == port_u32(port, channel, state + STATE_POINT))
    {
        port_set32(port, channel, state + STATE_POINT,
                   port_u8(port, settings, ENVELOPE_LOOP_START));
    }
    port_set32(port, channel, state + STATE_TICK,
               port_u16(port, settings + 4 * port_u32(port, channel, state + STATE_POINT), 0));
    port_set32(port, channel, state + STATE_VALUE,
               port_u16(port, settings + 4 * port_u32(port, channel, state + STATE_POINT), 2) << 8);
    const uint32_t point = port_u32(port, channel, state + STATE_POINT);
    if ((int32_t)(point + 1) >= (int32_t)port_u8(port, settings, ENVELOPE_COUNT))
    {
        port_set32(port, channel, state + STATE_STEP, 0);
        return;
    }
    const uint32_t at = settings + 4 * port_u32(port, channel, state + STATE_POINT);
    const uint32_t span = port_u16(port, at, 4) - port_u16(port, at, 0);
    if ((int32_t)span > 0)
    {
        const uint32_t rise = (port_u16(port, at, 6) - port_u16(port, at, 2)) << 8;
        port_set32(port, channel, state + STATE_STEP, (uint32_t)((int32_t)rise / (int32_t)span));
    }
    else
    {
        port_set32(port, channel, state + STATE_STEP, 0);
    }
    port_set32(port, channel, state + STATE_POINT,
               port_u32(port, channel, state + STATE_POINT) + 1);
}

static int envelope_on(Port *port, uint32_t instrument, uint32_t points)
{
    return instrument != 0 &&
           (port_u8(port, instrument + points, ENVELOPE_FLAGS) & ENVELOPE_ON) != 0;
}

/* The vibrato waveform at a position (0x40e259's table): sine, square, ramp down, ramp up, or 0
 * for another type. */
static uint32_t waveform(Port *port, uint32_t type, uint32_t position)
{
    switch (type)
    {
        case 0:
            return (uint32_t)((int32_t)port_u32(port, SINE_DWORDS + position, 0) >> 24);
        case 1:
            return (position & 0x80) != 0 ? VIBRATO_SQUARE : 0u - VIBRATO_SQUARE;
        case 2:
            return (((position >> 1) + 0x40) & 0x7f) - 0x40;
        case 3:
            return ((0x40 - (position >> 1)) & 0x7f) - 0x40;
        default:
            return 0;
    }
}

/* Original 0x40e030 (eax = a channel): the mixer's per-tick instrument update. A released note
 * fades (its fadeout volume less its step, stopping at 0). With the volume envelope on, the
 * envelope steps and the volume played is volume * envelope * fadeout >> 29 (flag 2); else the
 * volume scaled by the fadeout unless that is full. With the panning envelope on, the panning
 * played moves from the panning by the envelope's offset from the middle, scaled by the room to
 * the nearer edge (flag 4); else the panning. With instrument vibrato its depth sweeps up (key on)
 * to the instrument's, the position advances by the rate and the period played is the period plus
 * waveform * depth >> 14, kept within 1..0x7cff (flag 1); else the period. Returns that period;
 * the caller's edx is kept. */
uint32_t vertrix_port_rtl_mixer_tick_40e030(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t channel = entry->eax;
    const uint32_t instrument = port_u32(&port, channel, CHANNEL_INSTRUMENT);
    if (instrument != 0 && port_u8(&port, channel, CHANNEL_KEY_ON) == 0)
    {
        const uint32_t fade =
            port_u32(&port, channel, CHANNEL_FADE) - port_u32(&port, channel, CHANNEL_FADE_STEP);
        port_set32(&port, channel, CHANNEL_FADE, fade);
        if ((int32_t)fade < 0)
        {
            port_set32(&port, channel, CHANNEL_FADE_STEP, 0);
            port_set32(&port, channel, CHANNEL_FADE, 0);
        }
        port_set8(&port, channel, CHANNEL_FLAGS,
                  port_u8(&port, channel, CHANNEL_FLAGS) | FLAG_VOLUME);
    }
    if (envelope_on(&port, instrument, VOLUME_POINTS))
    {
        envelope(&port, channel, instrument, VOLUME_STATE, VOLUME_POINTS);
        const uint32_t level =
            (uint32_t)((int32_t)port_u32(&port, channel, VOLUME_STATE + STATE_VALUE) >> 8);
        const uint32_t played = level * port_u32(&port, channel, CHANNEL_VOLUME) *
                                port_u32(&port, channel, CHANNEL_FADE);
        port_set32(&port, channel, CHANNEL_VOLUME_OUT, (uint32_t)((int32_t)played >> 21));
        port_set8(&port, channel, CHANNEL_FLAGS,
                  port_u8(&port, channel, CHANNEL_FLAGS) | FLAG_VOLUME);
    }
    else
    {
        const uint32_t volume = port_u32(&port, channel, CHANNEL_VOLUME);
        port_set32(&port, channel, CHANNEL_VOLUME_OUT, volume);
        const uint32_t fade = port_u32(&port, channel, CHANNEL_FADE);
        if (fade != FADE_FULL)
        {
            port_set32(&port, channel, CHANNEL_VOLUME_OUT,
                       (uint32_t)((int32_t)(volume * fade) >> 15));
        }
    }
    if (envelope_on(&port, instrument, PANNING_POINTS))
    {
        envelope(&port, channel, instrument, PANNING_STATE, PANNING_POINTS);
        uint32_t room = port_u32(&port, channel, CHANNEL_PANNING) - CENTRE;
        if ((int32_t)room <= 0)
        {
            room = 0u - room;
        }
        const uint32_t scale = (CENTRE - room) << 3;
        const uint32_t offset =
            port_u32(&port, channel, PANNING_STATE + STATE_VALUE) - PANNING_CENTRE;
        port_set32(&port, channel, CHANNEL_PANNING_OUT,
                   port_u32(&port, channel, CHANNEL_PANNING) +
                       (uint32_t)((int32_t)(scale * offset) >> 16));
        port_set8(&port, channel, CHANNEL_FLAGS,
                  port_u8(&port, channel, CHANNEL_FLAGS) | FLAG_PANNING);
    }
    else
    {
        port_set32(&port, channel, CHANNEL_PANNING_OUT, port_u32(&port, channel, CHANNEL_PANNING));
    }
    if (instrument == 0 || port_u8(&port, instrument, INSTRUMENT_VIBRATO_DEPTH) == 0)
    {
        const uint32_t period = port_u32(&port, channel, CHANNEL_PERIOD);
        port_set32(&port, channel, CHANNEL_PERIOD_OUT, period);
        return port_return(&port, period, entry->edx);
    }
    if (port_u8(&port, channel, CHANNEL_KEY_ON) != 0)
    {
        const uint32_t sweep = port_u32(&port, channel, CHANNEL_VIBRATO_SWEEP);
        if (sweep != 0)
        {
            const uint32_t depth = port_u32(&port, channel, CHANNEL_VIBRATO_DEPTH) + sweep;
            port_set32(&port, channel, CHANNEL_VIBRATO_DEPTH, depth);
            const uint32_t full = port_u8(&port, instrument, INSTRUMENT_VIBRATO_DEPTH) << 8;
            if ((int32_t)full < (int32_t)depth)
            {
                port_set32(&port, channel, CHANNEL_VIBRATO_DEPTH, full);
                port_set32(&port, channel, CHANNEL_VIBRATO_SWEEP, 0);
            }
        }
    }
    port_set32(&port, channel, CHANNEL_VIBRATO_POSITION,
               port_u32(&port, channel, CHANNEL_VIBRATO_POSITION) +
                   port_u8(&port, instrument, INSTRUMENT_VIBRATO_RATE));
    const uint32_t position = port_u8(&port, channel, CHANNEL_VIBRATO_POSITION);
    const uint32_t type = port_u8(&port, instrument, INSTRUMENT_VIBRATO_TYPE);
    const uint32_t wave = waveform(&port, type, position);
    const uint32_t swing =
        (uint32_t)((int32_t)(wave * 4 * port_u32(&port, channel, CHANNEL_VIBRATO_DEPTH)) >> 16);
    uint32_t period = port_u32(&port, channel, CHANNEL_PERIOD) + swing;
    port_set32(&port, channel, CHANNEL_PERIOD_OUT, period);
    if ((int32_t)period < PERIOD_LOWEST)
    {
        period = PERIOD_LOWEST;
    }
    else if ((int32_t)period > PERIOD_HIGHEST)
    {
        period = PERIOD_HIGHEST;
    }
    port_set32(&port, channel, CHANNEL_PERIOD_OUT, period);
    port_set8(&port, channel, CHANNEL_FLAGS, port_u8(&port, channel, CHANNEL_FLAGS) | FLAG_PERIOD);
    return port_return(&port, period, entry->edx);
}
