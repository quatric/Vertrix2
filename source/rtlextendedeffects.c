#include "rtlextendedeffects.h"

/* The module player's extended effects (Exy): fine slides, glissando, waveforms, finetune, pattern
 * loop, panning, retrigger, fine volume slides, note cut, note delay and pattern delay. */

enum
{
    CHANNEL_FLAGS = 1,
    CHANNEL_PARAMETER = 4,
    CHANNEL_NOTE = 7,
    CHANNEL_FINETUNE = 8,
    CHANNEL_INSTRUMENT_PERIODS = 0xc,
    CHANNEL_VOLUME = 0x10,
    CHANNEL_OUTPUT_VOLUME = 0x14,
    CHANNEL_PANNING = 0x1c,
    CHANNEL_PERIOD = 0x24,
    CHANNEL_OUTPUT_PERIOD = 0x28,
    CHANNEL_WAVEFORMS = 0x3c,
    CHANNEL_GLISSANDO = 0x3d,
    CHANNEL_FINE_UP = 0x6a,
    CHANNEL_FINE_DOWN = 0x6b,
    CHANNEL_LOOP_ROW = 0xac,
    CHANNEL_LOOP_COUNT = 0xb0,
    /* Flag bits: 1 period changed, 2 volume changed, 4 panning changed, 0x10 kept by a delay. */
    FLAG_PERIOD = 1,
    FLAG_VOLUME = 2,
    FLAG_PANNING = 4,
    FLAG_KEPT = 0x10,

    PERIOD_MIN = 1,
    PERIOD_MAX = 0x7cff,
    VOLUME_MAX = 0x40,

    /* The player: the tick in the row, the row, the loop target and the jump state. */
    TICK = 0x531b4c,
    ROW = 0x531b50,
    ORDER = 0x531b5c,
    JUMP_FLAGS = 0x531b44,
    JUMP_ROW = 0x531b74,
    JUMP_ORDER = 0x531b70,
    PATTERN_DELAY = 0x531b78,
    JUMP_LOOP = 1,
    JUMP_DELAY = 4,

    NOTE_PERIOD = 0x40ce80,
    RETRIGGER = 0x40e670
};

static void set_flag(Port *port, uint32_t channel, uint32_t flag)
{
    port_set8(port, channel, CHANNEL_FLAGS, port_u8(port, channel, CHANNEL_FLAGS) | flag);
}

/* E1x and E2x: a fine slide of the period by the remembered step (x times 4 when given). */
static uint32_t fine_slide(Port *port, uint32_t channel, uint32_t memory, uint32_t x, int up)
{
    if (x != 0)
    {
        port_set8(port, channel, memory, (x << 2) & 0xff);
    }
    const uint32_t step = port_u8(port, channel, memory);
    const int32_t period = (int32_t)port_u32(port, channel, CHANNEL_PERIOD);
    const int32_t slid = up ? period - (int32_t)step : period + (int32_t)step;
    port_set32(port, channel, CHANNEL_PERIOD, (uint32_t)slid);
    if (up ? slid < PERIOD_MIN : slid > PERIOD_MAX)
    {
        port_set32(port, channel, CHANNEL_PERIOD, up ? PERIOD_MIN : PERIOD_MAX);
    }
    const uint32_t result = port_u32(port, channel, CHANNEL_PERIOD);
    port_set32(port, channel, CHANNEL_OUTPUT_PERIOD, result);
    set_flag(port, channel, FLAG_PERIOD);
    return result;
}

/* Sets the volume after a fine slide; returns it. */
static uint32_t volume_changed(Port *port, uint32_t channel)
{
    const uint32_t volume = port_u32(port, channel, CHANNEL_VOLUME);
    port_set32(port, channel, CHANNEL_OUTPUT_VOLUME, volume);
    set_flag(port, channel, FLAG_VOLUME);
    return volume;
}

static uint32_t retrigger(Port *port, uint32_t channel)
{
    return port_call(port, RETRIGGER, channel, 0, 0, 0);
}

/* Original 0x40d540 (eax = the channel). Most effects act on the row's first tick only. Returns
 * the eax the original leaves, which its callers read: the value an effect stores, else the
 * effect's high nibble; edx is the caller's. */
uint32_t vertrix_port_sequence_extended_effect_40d540(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t channel = entry->eax;
    const uint32_t parameter = port_u8(&port, channel, CHANNEL_PARAMETER);
    const uint32_t effect = parameter >> 4;
    const uint32_t x = parameter & 0xf;
    const uint32_t tick = port_u32(&port, TICK, 0);
    const int first_tick = tick == 0;
    uint32_t result = effect;

    switch (effect)
    {
        case 0x1:
        case 0x2:
            if (first_tick)
            {
                result =
                    fine_slide(&port, channel, effect == 1 ? CHANNEL_FINE_UP : CHANNEL_FINE_DOWN, x,
                               effect == 1);
            }
            break;
        case 0x3:
            if (first_tick)
            {
                port_set8(&port, channel, CHANNEL_GLISSANDO, x);
                result = x;
            }
            break;
        case 0x4:
            /* The vibrato waveform, in the low nibble. */
            if (first_tick)
            {
                const uint32_t high = port_u8(&port, channel, CHANNEL_WAVEFORMS) & 0xf0;
                port_set8(&port, channel, CHANNEL_WAVEFORMS, high);
                port_set8(&port, channel, CHANNEL_WAVEFORMS, high | x);
                result = x;
            }
            break;
        case 0x5:
            if (first_tick)
            {
                const uint32_t finetune = (x << 4) - 0x80;
                port_set32(&port, channel, CHANNEL_FINETUNE, finetune);
                result =
                    port_call(&port, NOTE_PERIOD, port_u8(&port, channel, CHANNEL_NOTE),
                              port_u32(&port, channel, CHANNEL_INSTRUMENT_PERIODS), finetune, 0);
                port_set32(&port, channel, CHANNEL_OUTPUT_PERIOD, result);
                set_flag(&port, channel, FLAG_PERIOD);
            }
            break;
        case 0x6:
            if (!first_tick)
            {
                break;
            }
            if (x == 0)
            {
                result = port_u32(&port, ROW, 0);
                port_set32(&port, channel, CHANNEL_LOOP_ROW, result);
                break;
            }
            result = port_u32(&port, channel, CHANNEL_LOOP_COUNT);
            if (result == 0)
            {
                result = x;
                port_set32(&port, channel, CHANNEL_LOOP_COUNT, x);
            }
            else
            {
                port_set32(&port, channel, CHANNEL_LOOP_COUNT, result - 1);
            }
            if (port_u32(&port, channel, CHANNEL_LOOP_COUNT) != 0)
            {
                port_set32(&port, JUMP_ROW, 0, port_u32(&port, channel, CHANNEL_LOOP_ROW));
                result = port_u32(&port, ORDER, 0);
                port_set32(&port, JUMP_ORDER, 0, result);
                port_set8(&port, JUMP_FLAGS, 0, port_u8(&port, JUMP_FLAGS, 0) | JUMP_LOOP);
            }
            break;
        case 0x7:
            /* The tremolo waveform, in the high nibble. */
            if (first_tick)
            {
                const uint32_t low = port_u8(&port, channel, CHANNEL_WAVEFORMS) & 0xf;
                port_set8(&port, channel, CHANNEL_WAVEFORMS, low);
                result = (x << 4) & 0xff;
                port_set8(&port, channel, CHANNEL_WAVEFORMS, low | result);
            }
            break;
        case 0x8:
            if (first_tick)
            {
                result = x << 4;
                port_set32(&port, channel, CHANNEL_PANNING, result);
                set_flag(&port, channel, FLAG_PANNING);
            }
            break;
        case 0x9:
            /* Retrigger every x ticks. */
            if (first_tick)
            {
                result = retrigger(&port, channel);
            }
            else if (x != 0)
            {
                result = (uint32_t)((int32_t)tick / (int32_t)x);
                if ((int32_t)tick % (int32_t)x == 0)
                {
                    result = retrigger(&port, channel);
                }
            }
            break;
        case 0xa:
            if (first_tick)
            {
                const uint32_t volume = port_u32(&port, channel, CHANNEL_VOLUME) + x;
                port_set32(&port, channel, CHANNEL_VOLUME, volume);
                if ((int32_t)volume > VOLUME_MAX)
                {
                    port_set32(&port, channel, CHANNEL_VOLUME, VOLUME_MAX);
                }
                result = volume_changed(&port, channel);
            }
            break;
        case 0xb:
            if (first_tick)
            {
                const uint32_t volume = port_u32(&port, channel, CHANNEL_VOLUME) - x;
                port_set32(&port, channel, CHANNEL_VOLUME, volume);
                if ((int32_t)volume < 0)
                {
                    port_set32(&port, channel, CHANNEL_VOLUME, 0);
                }
                result = volume_changed(&port, channel);
            }
            break;
        case 0xc:
            /* Note cut on tick x. */
            result = x;
            if (x == tick)
            {
                port_set32(&port, channel, CHANNEL_OUTPUT_VOLUME, 0);
                result = port_u32(&port, channel, CHANNEL_OUTPUT_VOLUME);
                port_set32(&port, channel, CHANNEL_VOLUME, result);
                set_flag(&port, channel, FLAG_VOLUME);
            }
            break;
        case 0xd:
            /* Note delay: nothing changes until tick x, which retriggers. */
            port_set8(&port, channel, CHANNEL_FLAGS,
                      port_u8(&port, channel, CHANNEL_FLAGS) & FLAG_KEPT);
            result = x;
            if (x == tick)
            {
                result = retrigger(&port, channel);
                set_flag(&port, channel, FLAG_VOLUME | FLAG_PANNING);
            }
            break;
        case 0xe:
            if (first_tick && (port_u8(&port, JUMP_FLAGS, 0) & JUMP_DELAY) == 0)
            {
                result = x + 1;
                port_set32(&port, PATTERN_DELAY, 0, result);
                port_set8(&port, JUMP_FLAGS, 0, port_u8(&port, JUMP_FLAGS, 0) | JUMP_DELAY);
            }
            break;
        default:
            break;
    }
    return port_return(&port, result, entry->edx);
}
