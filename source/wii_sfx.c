#include "wii_sfx.h"

#include <asndlib.h>
#include <mad.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

enum
{
    ALIGNMENT = 32,
    RIFF_HEADER = 12,
    CHUNK_HEADER = 8,
    FORMAT_BYTES = 16,
    PCM = 1,
    SILENCE_8_BIT = 0x80
};

struct VertrixWiiSfx
{
    void *samples;
    uint32_t size;
    uint32_t rate;
    int format;
};

static uint32_t read_le32(const uint8_t *bytes)
{
    return (uint32_t)bytes[0] | (uint32_t)bytes[1] << 8 | (uint32_t)bytes[2] << 16 |
           (uint32_t)bytes[3] << 24;
}

static uint32_t read_le16(const uint8_t *bytes)
{
    return (uint32_t)bytes[0] | (uint32_t)bytes[1] << 8;
}

static int voice_format(uint32_t channels, uint32_t bits)
{
    if (bits == 8)
    {
        return channels == 1 ? VOICE_MONO_8BIT_U : VOICE_STEREO_8BIT_U;
    }
    return channels == 1 ? VOICE_MONO_16BIT_LE : VOICE_STEREO_16BIT_LE;
}

/* Decode a whole MPEG layer III file to 16 bit samples with libmad. */
static VertrixWiiSfx *mp3_decode(const uint8_t *file, uint32_t total)
{
    struct mad_stream stream;
    struct mad_frame frame;
    struct mad_synth synth;
    int16_t *pcm = NULL;
    size_t used = 0;
    size_t capacity = 0;
    uint32_t channels = 0;
    uint32_t rate = 0;
    VertrixWiiSfx *sfx = NULL;
    mad_stream_init(&stream);
    mad_frame_init(&frame);
    mad_synth_init(&synth);
    mad_stream_buffer(&stream, file, total);
    for (;;)
    {
        if (mad_frame_decode(&frame, &stream))
        {
            if (MAD_RECOVERABLE(stream.error))
            {
                continue;
            }
            break;
        }
        mad_synth_frame(&synth, &frame);
        if (!channels)
        {
            channels = synth.pcm.channels;
            rate = synth.pcm.samplerate;
        }
        size_t count = (size_t)synth.pcm.length * channels;
        if (used + count > capacity)
        {
            size_t grown = capacity ? capacity * 2 : 32768;
            int16_t *bigger = realloc(pcm, grown * sizeof *pcm);
            if (!bigger)
            {
                break;
            }
            pcm = bigger;
            capacity = grown;
        }
        for (unsigned i = 0; i < synth.pcm.length; i++)
        {
            for (uint32_t c = 0; c < channels; c++)
            {
                mad_fixed_t sample = synth.pcm.samples[c][i];
                sample = sample > MAD_F_ONE - 1 ? MAD_F_ONE - 1
                         : sample < -MAD_F_ONE  ? -MAD_F_ONE
                                                : sample;
                /* ASND reads little-endian 16 bit samples. */
                int16_t value = (int16_t)(sample >> (MAD_F_FRACBITS - 15));
                pcm[used++] = (int16_t)((uint16_t)value >> 8 | (uint16_t)value << 8);
            }
        }
    }
    if (pcm && used && channels && channels <= 2)
    {
        uint32_t length = (uint32_t)(used * sizeof *pcm);
        uint32_t padded = (length + ALIGNMENT - 1) / ALIGNMENT * ALIGNMENT;
        sfx = calloc(1, sizeof *sfx);
        if (sfx && (sfx->samples = memalign(ALIGNMENT, padded)))
        {
            memset(sfx->samples, 0, padded);
            memcpy(sfx->samples, pcm, length);
            sfx->size = padded;
            sfx->rate = rate;
            sfx->format = voice_format(channels, 16);
        }
        else
        {
            free(sfx);
            sfx = NULL;
        }
    }
    free(pcm);
    mad_synth_finish(&synth);
    mad_frame_finish(&frame);
    mad_stream_finish(&stream);
    return sfx;
}

VertrixWiiSfx *vertrix_wii_sfx_load(VertrixVf *archive, const char *name)
{
    uint32_t index;
    uint32_t total;
    uint32_t channels = 0;
    uint32_t bits = 0;
    uint32_t rate = 0;
    uint32_t format = 0;
    uint8_t *file = NULL;
    VertrixWiiSfx *sfx = NULL;
    if (!vertrix_vf_find(archive, name, &index) || !vertrix_vf_size(archive, index, &total) ||
        total < RIFF_HEADER + CHUNK_HEADER || !(file = malloc(total)) ||
        !vertrix_vf_read(archive, index, 0, file, total))
    {
        free(file);
        return NULL;
    }
    if (memcmp(file, "RIFF", 4) || memcmp(file + 8, "WAVE", 4))
    {
        sfx = mp3_decode(file, total);
        free(file);
        return sfx;
    }
    for (uint32_t at = RIFF_HEADER; at + CHUNK_HEADER <= total;)
    {
        uint32_t size = read_le32(file + at + 4);
        const uint8_t *body = file + at + CHUNK_HEADER;
        uint32_t room = total - at - CHUNK_HEADER;
        if (!memcmp(file + at, "fmt ", 4) && size >= FORMAT_BYTES && room >= FORMAT_BYTES)
        {
            format = read_le16(body);
            channels = read_le16(body + 2);
            rate = read_le32(body + 4);
            bits = read_le16(body + 14);
        }
        else if (!memcmp(file + at, "data", 4) && format == PCM &&
                 (channels == 1 || channels == 2) && (bits == 8 || bits == 16) && rate)
        {
            uint32_t length = size < room ? size : room;
            uint32_t padded = (length + ALIGNMENT - 1) / ALIGNMENT * ALIGNMENT;
            sfx = calloc(1, sizeof *sfx);
            if (sfx)
            {
                sfx->samples = memalign(ALIGNMENT, padded);
            }
            if (!sfx || !sfx->samples)
            {
                free(sfx);
                free(file);
                return NULL;
            }
            memset(sfx->samples, bits == 8 ? SILENCE_8_BIT : 0, padded);
            memcpy(sfx->samples, body, length);
            sfx->size = padded;
            sfx->rate = rate;
            sfx->format = voice_format(channels, bits);
            break;
        }
        at += CHUNK_HEADER + size + (size & 1);
    }
    free(file);
    return sfx;
}

int vertrix_wii_sfx_play(const VertrixWiiSfx *sfx, int voice, unsigned volume)
{
    if (!sfx)
    {
        return 0;
    }
    if (volume > 255)
    {
        volume = 255;
    }
    return ASND_SetVoice(voice, sfx->format, (int)sfx->rate, 0, sfx->samples, (int)sfx->size,
                         (int)volume, (int)volume, NULL) == SND_OK;
}

void vertrix_wii_sfx_free(VertrixWiiSfx *sfx)
{
    if (sfx)
    {
        free(sfx->samples);
        free(sfx);
    }
}
