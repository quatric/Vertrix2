#include "port_vibratos.h"

/* The mixer's vibrato and volume slide effects. */

/* Original 0x40d090: the vibrato of the channel eax. Outside a tick (0x531b4c 0) the depth +0x44
 * (the low nibble of byte +4, when set) and the speed +0x48 (four times the high nibble, when
 * set) are taken; the result is the high nibble, times four when set. On a tick the wave of the
 * position +0x40 (bits 2 to 6) by the shape +0x3c (0 the sine 0x4f7304, 1 a ramp of eight a step
 * turned down by bit 7, 2 square 0xff, 3 none) times the depth over 32 moves the period +0x24
 * into +0x28 (down by bit 7 to at least 1, else up to at most 0x7cff), byte +1 gains bit 0 and
 * the position steps by the speed, the result. */
uint32_t vertrix_port_mixer_vibrato_40d090(PORT_SIGNATURE)
{
    Port port;
    uint32_t channel = entry->eax;
    uint32_t step;
    uint32_t wave;
    uint32_t period;
    int32_t moved;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x531b4c) == 0)
    {
        if ((port_u8(&port, channel, 4) & 0xf) != 0)
        {
            port_set32(&port, channel, 0x44, port_u8(&port, channel, 4) & 0xf);
        }
        wave = port_u8(&port, channel, 4) >> 4;
        if (wave == 0)
        {
            return port_return(&port, 0, entry->edx);
        }
        port_set32(&port, channel, 0x48, wave << 2);
        return port_return(&port, wave << 2, entry->edx);
    }
    step = ((uint32_t)((int32_t)port_u32(&port, channel, 0x40) >> 2)) & 0x1f;
    switch (port_u8(&port, channel, 0x3c) & 3)
    {
        case 0:
            wave = port_u8(&port, 0, 0x4f7304 + step);
            break;
        case 1:
            wave = step * 8;
            if ((port_u8(&port, channel, 0x40) & 0x80) != 0)
            {
                wave ^= 0xff;
            }
            break;
        case 2:
            wave = 0xff;
            break;
        default:
            wave = 0;
            break;
    }
    wave = (uint32_t)((int32_t)(wave * port_u32(&port, channel, 0x44)) >> 5);
    period = port_u32(&port, channel, 0x24);
    if ((port_u8(&port, channel, 0x40) & 0x80) != 0)
    {
        moved = (int32_t)(period - wave);
        port_set32(&port, channel, 0x28, (uint32_t)(moved < 1 ? 1 : moved));
    }
    else
    {
        moved = (int32_t)(period + wave);
        port_set32(&port, channel, 0x28, (uint32_t)(moved > 0x7cff ? 0x7cff : moved));
    }
    port_set8(&port, channel, 1, port_u8(&port, channel, 1) | 1);
    step = port_u32(&port, channel, 0x48);
    port_set32(&port, channel, 0x40, port_u32(&port, channel, 0x40) + step);
    return port_return(&port, step, entry->edx);
}

/* Original 0x40d250: the volume slide of the channel eax. Outside a tick (0x531b4c 0) a nonzero
 * byte +4 is kept at +0x68; on a tick the volume +0x10 rises by its high nibble to at most 0x40,
 * or without one falls by its low nibble to at least 0, +0x14 follows and byte +1 gains bit 1.
 * The channel. */
uint32_t vertrix_port_mixer_volume_slide_40d250(PORT_SIGNATURE)
{
    Port port;
    uint32_t channel = entry->eax;
    uint32_t slide;
    int32_t volume;
    port_open(&port, calls, services, globals, entry);
    if (port_u32(&port, 0, 0x531b4c) == 0)
    {
        if (port_u8(&port, channel, 4) != 0)
        {
            port_set8(&port, channel, 0x68, port_u8(&port, channel, 4));
        }
        return port_return(&port, channel, entry->edx);
    }
    slide = port_u8(&port, channel, 0x68);
    if ((slide >> 4) != 0)
    {
        volume = (int32_t)(port_u32(&port, channel, 0x10) + (slide >> 4));
        port_set32(&port, channel, 0x10, (uint32_t)(volume > 0x40 ? 0x40 : volume));
    }
    else
    {
        volume = (int32_t)(port_u32(&port, channel, 0x10) - (slide & 0xf));
        port_set32(&port, channel, 0x10, (uint32_t)(volume < 0 ? 0 : volume));
    }
    port_set32(&port, channel, 0x14, port_u32(&port, channel, 0x10));
    port_set8(&port, channel, 1, port_u8(&port, channel, 1) | 2);
    return port_return(&port, channel, entry->edx);
}
