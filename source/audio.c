#include "audio.h"
#include <stdlib.h>
#include <string.h>

static uint32_t le32(const unsigned char *data)
{
    return (uint32_t)data[0] | ((uint32_t)data[1] << 8) | ((uint32_t)data[2] << 16) |
           ((uint32_t)data[3] << 24);
}

static uint16_t le16(const unsigned char *data)
{
    return (uint16_t)((uint16_t)data[0] | ((uint16_t)data[1] << 8));
}

void vertrix_pcm8_free(VertrixPcm8 *audio)
{
    if (audio)
    {
        free(audio->samples);
        memset(audio, 0, sizeof(*audio));
    }
}

int vertrix_audio_pcm8(VertrixVf *archive, const char *name, VertrixPcm8 *output)
{
    if (!archive || !name || !output || output->samples || output->sample_rate ||
        output->sample_count)
    {
        return 0;
    }
    uint32_t index, size;
    unsigned char header[16];
    if (!vertrix_vf_find(archive, name, &index) || !vertrix_vf_size(archive, index, &size) ||
        size < 12 || !vertrix_vf_read(archive, index, 0, header, 12) || memcmp(header, "RIFF", 4) ||
        memcmp(header + 8, "WAVE", 4))
    {
        return 0;
    }
    uint32_t riff_size = le32(header + 4);
    if (riff_size < 4 || riff_size > size - 8)
    {
        return 0;
    }
    uint32_t end = riff_size + 8;
    uint32_t offset = 12, rate = 0, data_offset = 0, data_size = 0;
    while (offset < end)
    {
        if (end - offset < 8 || !vertrix_vf_read(archive, index, offset, header, 8))
        {
            return 0;
        }
        uint32_t length = le32(header + 4);
        offset += 8;
        if (length > end - offset)
        {
            return 0;
        }
        if (!memcmp(header, "fmt ", 4))
        {
            if (rate || length < 16 || !vertrix_vf_read(archive, index, offset, header, 16) ||
                le16(header) != 1 || le16(header + 2) != 1 || le16(header + 12) != 1 ||
                le16(header + 14) != 8)
            {
                return 0;
            }
            rate = le32(header + 4);
            if (!rate || le32(header + 8) != rate)
            {
                return 0;
            }
        }
        else if (!memcmp(header, "data", 4))
        {
            if (data_offset || !length)
            {
                return 0;
            }
            data_offset = offset;
            data_size = length;
        }
        offset += length;
        if (length & 1)
        {
            if (offset == end)
            {
                return 0;
            }
            ++offset;
        }
    }
    if (!rate || !data_offset)
    {
        return 0;
    }
    unsigned char *samples = malloc(data_size);
    if (!samples)
    {
        return 0;
    }
    if (!vertrix_vf_read(archive, index, data_offset, samples, data_size))
    {
        free(samples);
        return 0;
    }
    *output = (VertrixPcm8){rate, data_size, samples};
    return 1;
}

VertrixAudioFormat vertrix_audio_output_format(uint8_t flag_4, uint8_t flag_5, uint16_t rate)
{
    uint16_t channels = (uint16_t)(1 + (flag_5 & 1));
    uint16_t bytes = (uint16_t)(1 + (flag_4 & 1));
    uint16_t align = (uint16_t)(channels * bytes);
    return (VertrixAudioFormat){
        1, channels, rate, (uint32_t)rate * align, align, (uint16_t)(bytes * 8)};
}

uint32_t vertrix_audio_buffer_bytes(uint8_t flag_4, uint8_t flag_5, uint16_t rate)
{
    uint32_t bytes = (uint32_t)(rate / 20) * (1 + (flag_4 & 1)) * (1 + (flag_5 & 1));
    return (bytes + 15) & ~15u;
}

int vertrix_audio_delta_decode(unsigned char *samples, size_t byte_count, int sixteen_bit)
{
    if (!samples && byte_count)
    {
        return 0;
    }
    uint32_t previous = 0;
    if (sixteen_bit)
    {
        for (size_t offset = 0; offset + 1 < byte_count; offset += 2)
        {
            previous = (previous + le16(samples + offset)) & 65535;
            samples[offset] = (unsigned char)previous;
            samples[offset + 1] = (unsigned char)(previous >> 8);
        }
    }
    else
    {
        for (size_t offset = 0; offset < byte_count; ++offset)
        {
            previous = (previous + samples[offset]) & 255;
            samples[offset] = (unsigned char)previous;
        }
    }
    return 1;
}

int vertrix_audio_sample_guard(unsigned char *samples, size_t capacity, uint32_t byte_count,
                               uint32_t loop_start, uint32_t loop_end, uint8_t native_flags,
                               uint32_t updated_offset, uint32_t updated_bytes)
{
    if (!samples)
    {
        return 0;
    }
    if (native_flags & 16)
    {
        if (capacity < 4 || loop_start > capacity - 4 || loop_end > capacity - 4)
        {
            return 0;
        }
        unsigned char guard[4];
        memcpy(guard, samples + loop_start, sizeof(guard));
        memcpy(samples + loop_end, guard, sizeof(guard));
    }
    else if ((uint32_t)(updated_offset + updated_bytes) >= byte_count)
    {
        if (capacity < 4 || byte_count > capacity - 4)
        {
            return 0;
        }
        memset(samples + byte_count, 0, 4);
    }
    return 1;
}
