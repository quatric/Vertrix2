#include "wii_mp3.h"
#include <gccore.h>
#include <limits.h>
#include <mad.h>
#include <stdlib.h>
#include <string.h>

static int16_t pcm16(mad_fixed_t sample)
{
    int64_t rounded = (int64_t)sample + ((int64_t)1 << (MAD_F_FRACBITS - 16));
    if (rounded >= MAD_F_ONE)
    {
        return 32767;
    }
    if (rounded < -MAD_F_ONE)
    {
        return -32768;
    }
    return (int16_t)(rounded >> (MAD_F_FRACBITS - 15));
}

void vertrix_wii_mp3_free(VertrixWiiMp3 *audio)
{
    if (audio)
    {
        free(audio->allocation);
        memset(audio, 0, sizeof(*audio));
    }
}

int vertrix_wii_mp3_load(VertrixVf *archive, const char *name, VertrixWiiMp3 *output)
{
    if (!archive || !name || !output || output->samples || output->allocation ||
        output->sample_rate || output->channels || output->sample_frames || output->byte_count ||
        output->padded_size)
    {
        return 0;
    }
    uint32_t index, size;
    if (!vertrix_vf_find(archive, name, &index) || !vertrix_vf_size(archive, index, &size) ||
        !size || size > INT_MAX - MAD_BUFFER_GUARD)
    {
        return 0;
    }
    unsigned char *encoded = calloc(1, (size_t)size + MAD_BUFFER_GUARD);
    if (!encoded)
    {
        return 0;
    }
    if (!vertrix_vf_read(archive, index, 0, encoded, size))
    {
        free(encoded);
        return 0;
    }
    struct mad_stream stream;
    struct mad_frame frame;
    struct mad_synth synth;
    mad_stream_init(&stream);
    mad_frame_init(&frame);
    mad_synth_init(&synth);
    mad_stream_buffer(&stream, encoded, size + MAD_BUFFER_GUARD);
    unsigned char *pcm = NULL;
    size_t used = 0, capacity = 0;
    uint32_t rate = 0, channels = 0, attempts = 0;
    int valid = 1;
    for (;;)
    {
        if (++attempts > size)
        {
            valid = 0;
            break;
        }
        if (mad_frame_decode(&frame, &stream))
        {
            if (stream.error == MAD_ERROR_BUFLEN)
            {
                break;
            }
            if (stream.error == MAD_ERROR_LOSTSYNC)
            {
                continue;
            }
            valid = 0;
            break;
        }
        mad_synth_frame(&synth, &frame);
        if (!rate)
        {
            rate = synth.pcm.samplerate;
            channels = synth.pcm.channels;
        }
        if (!rate || channels < 1 || channels > 2 || rate != synth.pcm.samplerate ||
            channels != synth.pcm.channels || !synth.pcm.length)
        {
            valid = 0;
            break;
        }
        size_t added = (size_t)synth.pcm.length * channels * 2;
        if (added > (size_t)INT_MAX - 31 - used)
        {
            valid = 0;
            break;
        }
        size_t required = used + added;
        if (required > capacity)
        {
            size_t expanded = capacity ? capacity * 2 : 8192;
            if (expanded < required)
            {
                expanded = required;
            }
            unsigned char *grown = realloc(pcm, expanded);
            if (!grown)
            {
                valid = 0;
                break;
            }
            pcm = grown;
            capacity = expanded;
        }
        for (unsigned i = 0; i < synth.pcm.length; ++i)
        {
            for (unsigned channel = 0; channel < channels; ++channel)
            {
                uint16_t sample = (uint16_t)pcm16(synth.pcm.samples[channel][i]);
                pcm[used++] = (unsigned char)(sample >> 8);
                pcm[used++] = (unsigned char)sample;
            }
        }
    }
    mad_synth_finish(&synth);
    mad_frame_finish(&frame);
    mad_stream_finish(&stream);
    free(encoded);
    if (!valid || !used)
    {
        free(pcm);
        return 0;
    }
    uint32_t padded = ((uint32_t)used + 31) & ~31u;
    void *allocation = malloc((size_t)padded + 31);
    if (!allocation)
    {
        free(pcm);
        return 0;
    }
    unsigned char *samples = (unsigned char *)(((uintptr_t)allocation + 31) & ~(uintptr_t)31);
    memset(samples, 0, padded);
    memcpy(samples, pcm, used);
    free(pcm);
    DCFlushRange(samples, padded);
    *output =
        (VertrixWiiMp3){samples,        allocation, rate, channels, (uint32_t)used / (channels * 2),
                        (uint32_t)used, padded};
    return 1;
}
