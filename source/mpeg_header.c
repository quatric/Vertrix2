#include "mpeg_header.h"

enum
{
    SAMPLE_RATE_INVALID = 3,
    SAMPLE_RATE_EXTENSION_OFFSET = 6,
    SAMPLE_RATE_LSF_STEP = 3,
    LAYER_BASE = 4,
    LAYER_THREE = 3,
    LAYER_ONE = 1,
    LAYER_TWO = 2,
    MODE_MONO = 3,
    BITRATE_ROW_DWORDS = 48,
    INVALID_CODE = 1
};

static uint32_t field(uint32_t word, unsigned shift, uint32_t mask)
{
    return (word >> shift) & mask;
}

static void decode_version(VertrixMpegHeader *header, uint32_t word)
{
    if ((word & VERTRIX_MPEG_EXTENSION_BIT) != 0)
    {
        header->lsf = (word & VERTRIX_MPEG_VERSION_BIT) == 0;
        header->extension = 0;
    }
    else
    {
        header->lsf = 1;
        header->extension = 1;
    }
}

static void decode_fields(VertrixMpegHeader *header, uint32_t word, uint32_t sample_rate_bits)
{
    header->layer = LAYER_BASE - field(word, 17, 3);
    header->sample_rate = sample_rate_bits;
    if (header->extension != 0)
    {
        header->sample_rate += SAMPLE_RATE_EXTENSION_OFFSET;
    }
    else
    {
        header->sample_rate += header->lsf * SAMPLE_RATE_LSF_STEP;
    }
    header->protection = field(word, 16, 1) ^ 1;
    header->bitrate = field(word, 12, 0xf);
    header->padding = field(word, 9, 1);
    header->private_bit = field(word, 8, 1);
    header->mode = field(word, 6, 3);
    header->mode_extension = field(word, 4, 3);
    header->copyright = field(word, 3, 1);
    header->original = field(word, 2, 1);
    header->emphasis = word & 3;
    header->channels = (header->mode != MODE_MONO) + 1;
}

uint32_t vertrix_mpeg_header_decode(VertrixMpegHeader *header, uint32_t word,
                                    const uint32_t *bitrates, const uint32_t *sample_rates,
                                    VertrixMpegInvalid invalid, void *context)
{
    uint32_t sample_rate_bits = field(word, 10, 3);
    decode_version(header, word);
    if (sample_rate_bits == SAMPLE_RATE_INVALID)
    {
        invalid(INVALID_CODE, context);
    }
    decode_fields(header, word, sample_rate_bits);
    if (header->bitrate == 0)
    {
        return 0;
    }
    if (header->layer == LAYER_ONE || header->layer == LAYER_TWO)
    {
        return 1;
    }
    if (header->layer != LAYER_THREE)
    {
        return 0;
    }
    uint32_t divisor = sample_rates[header->sample_rate] << (header->lsf & 31);
    if (divisor == 0)
    {
        return 0;
    }
    uint32_t rate = bitrates[header->lsf * BITRATE_ROW_DWORDS + header->bitrate];
    int32_t size = (int32_t)(rate * VERTRIX_MPEG_FRAME_FACTOR) / (int32_t)divisor;
    header->frame_size = size + (int32_t)header->padding - 4;
    return 1;
}
