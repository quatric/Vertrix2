#include "rtlmpegsideinfos.h"

/* mpg123's III_get_side_info_1: reads an MPEG-1 layer III frame's side information. */

enum
{
    ARGUMENT_VERSION = 4,
    /* With this version the gain table is shifted by four entries. */
    SHIFTED_VERSION = 3,
    TAB_SHIFT = 4,

    SIDE_MAIN_DATA_BEGIN = 0,
    SIDE_PRIVATE_BITS = 4,
    SIDE_CHANNELS = 8,
    CHANNEL_BYTES = 0xd0,
    GRANULE_BYTES = 0x68,

    /* gr_info_s. */
    GRANULE_SCFSI = 0,
    GRANULE_PART2_3_LENGTH = 4,
    GRANULE_BIG_VALUES = 8,
    GRANULE_SCALEFAC_COMPRESS = 0xc,
    GRANULE_BLOCK_TYPE = 0x10,
    GRANULE_MIXED_BLOCK_FLAG = 0x14,
    GRANULE_TABLE_SELECT = 0x18,
    GRANULE_REGION1START = 0x44,
    GRANULE_REGION2START = 0x48,
    GRANULE_PREFLAG = 0x4c,
    GRANULE_SCALEFAC_SCALE = 0x50,
    GRANULE_COUNT1TABLE_SELECT = 0x54,
    GRANULE_FULL_GAIN = 0x58,
    GRANULE_POW2GAIN = 0x64,
    BIG_VALUES_LIMIT = 288,

    /* gainpow2 + 256, and the long-block band starts of each rate (0x90 bytes per rate). */
    GAINPOW2_END = 0x523698,
    BAND_LONG_INDEX = 0x4f591a,
    BAND_INFO_BYTES = 0x90,

    GETBITS = 0x404610,
    GETBITS_FAST = 0x404680,
    GET1BIT = 0x4046e0,
    RUN_ERROR = 0x4eb4d4
};

static uint32_t getbits(Port *port, uint32_t count)
{
    return port_call(port, GETBITS, count, 0, 0, 0);
}

static uint32_t getbits_fast(Port *port, uint32_t count)
{
    return port_call(port, GETBITS_FAST, count, 0, 0, 0);
}

static uint32_t get1bit(Port *port)
{
    return port_call(port, GET1BIT, 0, 0, 0, 0);
}

static uint32_t long_index(Port *port, uint32_t sfreq, uint32_t index)
{
    return (uint32_t)((int32_t)(int16_t)port_u16(port, BAND_LONG_INDEX,
                                                 sfreq * BAND_INFO_BYTES + index * 2) >>
                      1);
}

static void granule(Port *port, uint32_t g, uint32_t ms_stereo, uint32_t sfreq, uint32_t tab_shift)
{
    port_set32(port, g, GRANULE_PART2_3_LENGTH, getbits(port, 12));
    port_set32(port, g, GRANULE_BIG_VALUES, getbits_fast(port, 9));
    if (port_u32(port, g, GRANULE_BIG_VALUES) > BIG_VALUES_LIMIT)
    {
        port_set32(port, g, GRANULE_BIG_VALUES, BIG_VALUES_LIMIT);
    }
    uint32_t pow2gain = GAINPOW2_END - getbits_fast(port, 8) * 4 + tab_shift * 4;
    port_set32(port, g, GRANULE_POW2GAIN, pow2gain);
    if (ms_stereo != 0)
    {
        port_set32(port, g, GRANULE_POW2GAIN, pow2gain + 8);
    }
    port_set32(port, g, GRANULE_SCALEFAC_COMPRESS, getbits_fast(port, 4));
    if (get1bit(port) != 0)
    {
        /* Window switching. */
        port_set32(port, g, GRANULE_BLOCK_TYPE, getbits_fast(port, 2));
        port_set32(port, g, GRANULE_MIXED_BLOCK_FLAG, get1bit(port));
        port_set32(port, g, GRANULE_TABLE_SELECT, getbits_fast(port, 5));
        port_set32(port, g, GRANULE_TABLE_SELECT + 4, getbits_fast(port, 5));
        port_set32(port, g, GRANULE_TABLE_SELECT + 8, 0);
        for (uint32_t i = 0; i < 3; i++)
        {
            port_set32(port, g, GRANULE_FULL_GAIN + i * 4,
                       (getbits_fast(port, 3) << 5) + port_u32(port, g, GRANULE_POW2GAIN));
        }
        if (port_u32(port, g, GRANULE_BLOCK_TYPE) == 0)
        {
            /* "Blocktype == 0 and window-switching == 1 not allowed": the runtime error, with
             * the edx and ecx the original leaves. */
            port_call(port, RUN_ERROR, 1, g + GRANULE_SCALEFAC_COMPRESS, 0, g);
        }
        port_set32(port, g, GRANULE_REGION1START, 36 >> 1);
        port_set32(port, g, GRANULE_REGION2START, 576 >> 1);
    }
    else
    {
        for (uint32_t i = 0; i < 3; i++)
        {
            port_set32(port, g, GRANULE_TABLE_SELECT + i * 4, getbits_fast(port, 5));
        }
        const uint32_t r0c = getbits_fast(port, 4);
        const uint32_t r1c = getbits_fast(port, 3);
        port_set32(port, g, GRANULE_REGION1START, long_index(port, sfreq, r0c));
        port_set32(port, g, GRANULE_REGION2START, long_index(port, sfreq, r0c + r1c + 1));
        port_set32(port, g, GRANULE_BLOCK_TYPE, 0);
        port_set32(port, g, GRANULE_MIXED_BLOCK_FLAG, 0);
    }
    port_set32(port, g, GRANULE_PREFLAG, get1bit(port));
    port_set32(port, g, GRANULE_SCALEFAC_SCALE, get1bit(port));
    port_set32(port, g, GRANULE_COUNT1TABLE_SELECT, get1bit(port));
}

/* Original 0x407020 (eax = the side info, edx = the channel count, ebx = ms_stereo, ecx = the
 * sampling rate index, stack: the version, 3 shifting the gain table). */
uint32_t vertrix_port_mpeg1_side_info_407020(PORT_SIGNATURE)
{
    uint8_t stack[8 + 4];
    Port port;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 1);
    const uint32_t si = entry->eax;
    const int32_t stereo = (int32_t)entry->edx;
    const uint32_t ms_stereo = entry->ebx;
    const uint32_t sfreq = entry->ecx;
    const uint32_t tab_shift =
        port_u32(&port, entry->esp, ARGUMENT_VERSION) == SHIFTED_VERSION ? TAB_SHIFT : 0;

    port_set32(&port, si, SIDE_MAIN_DATA_BEGIN, getbits(&port, 9));
    port_set32(&port, si, SIDE_PRIVATE_BITS, getbits_fast(&port, stereo == 1 ? 5 : 3));
    for (int32_t ch = 0; ch < stereo && !port.env.failed; ch++)
    {
        const uint32_t channel = si + SIDE_CHANNELS + (uint32_t)ch * CHANNEL_BYTES;
        port_set32(&port, channel, GRANULE_SCFSI, 0xffffffffu);
        port_set32(&port, channel, GRANULE_BYTES + GRANULE_SCFSI, getbits_fast(&port, 4));
    }
    for (uint32_t gr = 0; gr < 2 && !port.env.failed; gr++)
    {
        for (int32_t ch = 0; ch < stereo && !port.env.failed; ch++)
        {
            granule(&port, si + SIDE_CHANNELS + (uint32_t)ch * CHANNEL_BYTES + gr * GRANULE_BYTES,
                    ms_stereo, sfreq, tab_shift);
        }
    }
    return port_return(&port, 0, 0);
}
