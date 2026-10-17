#include "rtlmpegstereos.h"

/* mpg123's III_i_stereo: intensity stereo for one granule. Below each band's intensity position
 * the left channel's samples are split into both channels by the ratio tables. */

enum
{
    /* The second channel's samples follow the first's 576. */
    CHANNEL = 576 * 4,
    NOT_INTENSITY = 7,
    ARGUMENT_MS_STEREO = 4,
    ARGUMENT_LSF = 8,

    /* The granule: scale factor compression, block type, mixed blocks, the three windows' last
     * bands and the last long band. */
    GRANULE_SCALEFAC_COMPRESS = 0xc,
    GRANULE_BLOCK_TYPE = 0x10,
    GRANULE_MIXED = 0x14,
    GRANULE_MAX_BAND = 0x30,
    GRANULE_MAX_BAND_LONG = 0x3c,
    SHORT_BLOCKS = 2,

    /* Band layouts per sample rate (0x90 bytes each): words of long band starts and widths,
     * short band starts and widths. */
    BAND_INFO = 0x4f5918,
    BAND_INFO_BYTES = 0x90,
    LONG_INDEX = 0,
    LONG_WIDTH = 0x2e,
    SHORT_INDEX = 0x5a,
    SHORT_WIDTH = 0x76,
    LONG_BANDS = 21,
    SHORT_BANDS = 12,
    MIXED_LONG_BANDS = 8,

    /* The ratio tables: MPEG-2 ones (two sets of 16 per table, picked by the scale factor
     * compression's low bit), MPEG-1 ones, each for the left and the right channel, with and
     * without mid/side stereo. */
    LSF_MS_LEFT = 0x523098,
    LSF_MS_RIGHT = 0x522f98,
    LSF_LEFT = 0x523118,
    LSF_RIGHT = 0x523018,
    LSF_SET_BYTES = 0x40,
    MS_LEFT = 0x523258,
    MS_RIGHT = 0x5231d8,
    LEFT = 0x523218,
    RIGHT = 0x523198,

    SINGLE_MULTIPLY = 0x4d8177
};

typedef struct
{
    uint32_t samples;
    uint32_t left;
    uint32_t right;
} Stereo;

static uint32_t band_word(Port *port, uint32_t info, uint32_t table, uint32_t band)
{
    return (uint32_t)(int32_t)(int16_t)port_u16(port, info, table + band * 2);
}

/* Split `count` samples from index `at`, `step` apart, by intensity position `position`. The
 * multiply takes the operands in eax and edx; the original also leaves the sample in ebx and its
 * address in ecx. Returns the index after the last. */
static uint32_t split(Port *port, const Stereo *stereo, uint32_t position, uint32_t at,
                      int32_t count, uint32_t step)
{
    const uint32_t left = port_u32(port, stereo->left, position * 4);
    const uint32_t right = port_u32(port, stereo->right, position * 4);
    for (; count > 0 && !port->env.failed; count--, at += step)
    {
        const uint32_t address = stereo->samples + at * 4;
        const uint32_t sample = port_u32(port, address, 0);
        port_set32(port, address, 0,
                   port_call(port, SINGLE_MULTIPLY, sample, left, sample, address));
        port_set32(port, address, CHANNEL,
                   port_call(port, SINGLE_MULTIPLY, sample, right, sample, address));
    }
    return at;
}

/* Original 0x4083a0 (eax = samples, edx = scale factors, ebx = granule, ecx = sample rate index,
 * stack: mid/side stereo, MPEG-2). For short blocks each window from its last band on, then
 * (mixed blocks whose windows all end in the first four bands) the long bands up to 8 from the
 * last long band; for long blocks the long bands from the last one on, the 22nd taking the 21st's
 * position. A band whose position is 7 is not intensity coded and is skipped. */
uint32_t vertrix_port_mpeg_intensity_stereo_4083a0(PORT_SIGNATURE)
{
    uint8_t stack[8 + 8];
    Port port;
    port_open_arguments(&port, stack, calls, services, globals, entry, 0, 2);
    const uint32_t scalefac = entry->edx;
    const uint32_t granule = entry->ebx;
    const uint32_t info = BAND_INFO + entry->ecx * BAND_INFO_BYTES;
    const uint32_t ms_stereo = port_u32(&port, entry->esp, ARGUMENT_MS_STEREO);
    Stereo stereo = {entry->eax, 0, 0};
    if (port_u32(&port, entry->esp, ARGUMENT_LSF) != 0)
    {
        const uint32_t set =
            (port_u32(&port, granule, GRANULE_SCALEFAC_COMPRESS) & 1) * LSF_SET_BYTES;
        stereo.left = (ms_stereo ? LSF_MS_LEFT : LSF_LEFT) + set;
        stereo.right = (ms_stereo ? LSF_MS_RIGHT : LSF_RIGHT) + set;
    }
    else
    {
        stereo.left = ms_stereo ? MS_LEFT : LEFT;
        stereo.right = ms_stereo ? MS_RIGHT : RIGHT;
    }

    if (port_u32(&port, granule, GRANULE_BLOCK_TYPE) != SHORT_BLOCKS)
    {
        uint32_t band = port_u32(&port, granule, GRANULE_MAX_BAND_LONG);
        uint32_t at = band_word(&port, info, LONG_INDEX, band);
        for (; (int32_t)band < LONG_BANDS && !port.env.failed; band++)
        {
            const int32_t width = (int32_t)band_word(&port, info, LONG_WIDTH, band);
            const uint32_t position = port_u32(&port, scalefac, band * 4);
            at = position == NOT_INTENSITY ? at + width
                                           : split(&port, &stereo, position, at, width, 1);
        }
        const uint32_t position = port_u32(&port, scalefac, (LONG_BANDS - 1) * 4);
        if (position != NOT_INTENSITY)
        {
            split(&port, &stereo, position, at,
                  (int32_t)band_word(&port, info, LONG_WIDTH, LONG_BANDS), 1);
        }
        return port_return(&port, 0, 0);
    }

    int long_too = port_u32(&port, granule, GRANULE_MIXED) != 0;
    for (uint32_t window = 0; window < 3 && !port.env.failed; window++)
    {
        uint32_t band = port_u32(&port, granule, GRANULE_MAX_BAND + window * 4);
        if ((int32_t)band > 3)
        {
            long_too = 0;
        }
        for (; (int32_t)band < SHORT_BANDS && !port.env.failed; band++)
        {
            const uint32_t position = port_u32(
                &port, scalefac, (band * 3 + window - port_u32(&port, granule, GRANULE_MIXED)) * 4);
            if (position != NOT_INTENSITY)
            {
                const int32_t width = (int32_t)band_word(&port, info, SHORT_WIDTH, band);
                const uint32_t at = band_word(&port, info, SHORT_INDEX, band) + window;
                split(&port, &stereo, position, at, width, 3);
            }
        }
        /* The last band takes the 12th's position. */
        const uint32_t position = port_u32(
            &port, scalefac,
            ((SHORT_BANDS - 1) * 3 + window - port_u32(&port, granule, GRANULE_MIXED)) * 4);
        const int32_t width = (int32_t)band_word(&port, info, SHORT_WIDTH, SHORT_BANDS);
        const uint32_t at = band_word(&port, info, SHORT_INDEX, SHORT_BANDS) + window;
        if (position != NOT_INTENSITY)
        {
            split(&port, &stereo, position, at, width, 3);
        }
    }
    if (long_too)
    {
        uint32_t band = port_u32(&port, granule, GRANULE_MAX_BAND_LONG);
        uint32_t at = band_word(&port, info, LONG_INDEX, band);
        for (; (int32_t)band < MIXED_LONG_BANDS && !port.env.failed; band++)
        {
            const int32_t width = (int32_t)band_word(&port, info, LONG_WIDTH, band);
            const uint32_t position = port_u32(&port, scalefac, band * 4);
            at = position == NOT_INTENSITY ? at + width
                                           : split(&port, &stereo, position, at, width, 1);
        }
    }
    return port_return(&port, 0, 0);
}
