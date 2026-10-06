#include "xm.h"
#include "audio.h"
#include <stdlib.h>
#include <string.h>

int vertrix_xm_event(const unsigned char *data, size_t size, size_t *cursor, VertrixXmEvent *output)
{
    if (!cursor || !output || *cursor > size || (!data && size))
    {
        return 0;
    }
    VertrixXmEvent event = {0};
    if (!data)
    {
        *output = event;
        return 1;
    }
    size_t position = *cursor;
    if (position == size)
    {
        return 0;
    }
    uint8_t flags = 31;
    if (data[position] & 128)
    {
        flags = data[position++] & 31;
    }
    unsigned char fields[5] = {0};
    for (unsigned field = 0; field < 5; ++field)
    {
        if (flags & (1u << field))
        {
            if (position == size)
            {
                return 0;
            }
            fields[field] = data[position++];
        }
    }
    event = (VertrixXmEvent){fields[0], fields[1], fields[2], fields[3], fields[4]};
    *output = event;
    *cursor = position;
    return 1;
}

int vertrix_xm_seek_row(const unsigned char *data, size_t size, int32_t row, int32_t channels,
                        size_t *cursor)
{
    if (!cursor || (!data && size))
    {
        return 0;
    }
    size_t position = 0;
    if (data && row > 0 && channels > 0)
    {
        uint64_t events = (uint64_t)(uint32_t)row * (uint32_t)channels;
        if (events > size)
        {
            return 0;
        }
        for (uint64_t index = 0; index < events; index++)
        {
            VertrixXmEvent event;
            if (!vertrix_xm_event(data, size, &position, &event))
            {
                return 0;
            }
        }
    }
    *cursor = position;
    return 1;
}

static uint16_t word(const unsigned char *data)
{
    return (uint16_t)((uint16_t)data[0] | ((uint16_t)data[1] << 8));
}

static uint32_t dword(const unsigned char *data)
{
    return (uint32_t)data[0] | ((uint32_t)data[1] << 8) | ((uint32_t)data[2] << 16) |
           ((uint32_t)data[3] << 24);
}

static int header_read(VertrixVf *archive, const char *name, VertrixXmHeader *output,
                       uint32_t *index, uint32_t *size, uint32_t *patterns_offset)
{
    unsigned char data[336];
    if (!archive || !name || !output || !vertrix_vf_find(archive, name, index) ||
        !vertrix_vf_size(archive, *index, size) || *size < sizeof(data) ||
        !vertrix_vf_read(archive, *index, 0, data, sizeof(data)) ||
        memcmp(data, "Extended Module: ", 17) || word(data + 58) != 0x104)
    {
        return 0;
    }
    uint32_t header_size = dword(data + 60);
    if (header_size < 276 || header_size > *size - 60 || word(data + 64) > 256 ||
        word(data + 68) > 32 || word(data + 70) > 256 || word(data + 72) > 128)
    {
        return 0;
    }
    VertrixXmHeader header = {0};
    memcpy(header.name, data + 17, 20);
    header.song_length = word(data + 64);
    header.restart = word(data + 66);
    header.channels = word(data + 68);
    header.patterns = word(data + 70);
    header.instruments = word(data + 72);
    header.flags = word(data + 74);
    header.speed = word(data + 76);
    header.bpm = word(data + 78);
    memcpy(header.order, data + 80, 256);
    *patterns_offset = 60 + header_size;
    *output = header;
    return 1;
}

int vertrix_xm_header(VertrixVf *archive, const char *name, VertrixXmHeader *output)
{
    uint32_t index, size, offset;
    return header_read(archive, name, output, &index, &size, &offset);
}

void vertrix_xm_pattern_free(VertrixXmPattern *pattern)
{
    if (pattern)
    {
        free(pattern->packed);
        memset(pattern, 0, sizeof(*pattern));
    }
}

int vertrix_xm_pattern_load(VertrixVf *archive, const char *name, uint32_t pattern,
                            VertrixXmPattern *output)
{
    if (!output || output->packed || output->channels || output->rows || output->packed_size)
    {
        return 0;
    }
    VertrixXmHeader song;
    uint32_t index, size, offset;
    if (!header_read(archive, name, &song, &index, &size, &offset) || pattern >= song.patterns)
    {
        return 0;
    }
    for (uint32_t current = 0; current <= pattern; ++current)
    {
        unsigned char data[9];
        if (size - offset < sizeof(data) ||
            !vertrix_vf_read(archive, index, offset, data, sizeof(data)))
        {
            return 0;
        }
        uint32_t length = dword(data);
        uint16_t packed_size = word(data + 7);
        if (length < 9 || length > size - offset || data[4] || packed_size > size - offset - length)
        {
            return 0;
        }
        offset += length;
        if (current == pattern)
        {
            VertrixXmPattern loaded = {song.channels, word(data + 5), packed_size, NULL};
            if (packed_size)
            {
                loaded.packed = malloc(packed_size);
                if (!loaded.packed)
                {
                    return 0;
                }
                if (!vertrix_vf_read(archive, index, offset, loaded.packed, packed_size))
                {
                    vertrix_xm_pattern_free(&loaded);
                    return 0;
                }
                size_t cursor = 0;
                for (uint32_t cell = 0; cell < (uint32_t)loaded.rows * song.channels; ++cell)
                {
                    VertrixXmEvent event;
                    if (!vertrix_xm_event(loaded.packed, packed_size, &cursor, &event))
                    {
                        vertrix_xm_pattern_free(&loaded);
                        return 0;
                    }
                }
            }
            *output = loaded;
            return 1;
        }
        offset += packed_size;
    }
    return 0;
}

void vertrix_xm_sample_free(VertrixXmSample *sample)
{
    if (sample)
    {
        free(sample->samples);
        memset(sample, 0, sizeof(*sample));
    }
}

int vertrix_xm_sample_load(VertrixVf *archive, const char *name, uint32_t instrument,
                           uint32_t sample, VertrixXmSample *output)
{
    if (!output || output->ready || output->samples || output->byte_count)
    {
        return 0;
    }
    VertrixXmHeader song;
    uint32_t index, size, offset;
    if (!header_read(archive, name, &song, &index, &size, &offset) ||
        instrument >= song.instruments)
    {
        return 0;
    }
    for (uint32_t pattern = 0; pattern < song.patterns; ++pattern)
    {
        unsigned char header[9];
        if (size - offset < sizeof(header) ||
            !vertrix_vf_read(archive, index, offset, header, sizeof(header)))
        {
            return 0;
        }
        uint32_t length = dword(header);
        uint32_t packed = word(header + 7);
        if (length < 9 || length > size - offset || packed > size - offset - length || header[4])
        {
            return 0;
        }
        offset += length + packed;
    }
    for (uint32_t current = 0; current <= instrument; ++current)
    {
        unsigned char header[33];
        if (size - offset < 29 || !vertrix_vf_read(archive, index, offset, header, 29))
        {
            return 0;
        }
        uint32_t length = dword(header);
        uint16_t count = word(header + 27);
        if (length < 29 || length > size - offset || count > 16)
        {
            return 0;
        }
        uint32_t sample_header_size = 0;
        if (count)
        {
            if (length < 33 || !vertrix_vf_read(archive, index, offset + 29, header + 29, 4))
            {
                return 0;
            }
            sample_header_size = dword(header + 29);
            if (sample_header_size < 40)
            {
                return 0;
            }
        }
        offset += length;
        if (current == instrument && sample >= count)
        {
            return 0;
        }
        if (count && sample_header_size > (size - offset) / count)
        {
            return 0;
        }
        uint32_t payload = offset + sample_header_size * count;
        unsigned char selected[40] = {0};
        uint32_t selected_offset = 0;
        for (uint32_t number = 0; number < count; ++number)
        {
            unsigned char sample_header[40];
            if (!vertrix_vf_read(archive, index, offset + number * sample_header_size,
                                 sample_header, sizeof(sample_header)))
            {
                return 0;
            }
            uint32_t bytes = dword(sample_header);
            if (bytes > size - payload)
            {
                return 0;
            }
            if (current == instrument && number == sample)
            {
                memcpy(selected, sample_header, sizeof(selected));
                selected_offset = payload;
            }
            payload += bytes;
        }
        if (current == instrument)
        {
            VertrixXmSample loaded = {0};
            memcpy(loaded.name, selected + 18, 22);
            loaded.byte_count = dword(selected);
            loaded.loop_start = dword(selected + 4);
            loaded.loop_length = dword(selected + 8);
            loaded.loop_end = loaded.loop_start + loaded.loop_length;
            loaded.base_frequency = 8363;
            loaded.volume = selected[12];
            loaded.finetune = (int8_t)selected[13];
            loaded.type = selected[14];
            loaded.panning = selected[15];
            loaded.relative_note = (int8_t)selected[16];
            loaded.native_flags =
                (uint8_t)(((loaded.type & 16) ? 1 : 0) | ((loaded.type & 1) ? 16 : 0) |
                          ((loaded.type & 2) ? 32 : 0));
            if (loaded.byte_count)
            {
                if ((uint64_t)loaded.byte_count + 4 > SIZE_MAX)
                {
                    return 0;
                }
                loaded.samples = calloc((size_t)loaded.byte_count + 4, 1);
                if (!loaded.samples)
                {
                    return 0;
                }
                if (!vertrix_vf_read(archive, index, selected_offset, loaded.samples,
                                     loaded.byte_count) ||
                    !vertrix_audio_delta_decode(loaded.samples, loaded.byte_count,
                                                loaded.type & 16) ||
                    !vertrix_audio_sample_guard(loaded.samples, (size_t)loaded.byte_count + 4,
                                                loaded.byte_count, loaded.loop_start,
                                                loaded.loop_end, loaded.native_flags, 0,
                                                loaded.byte_count))
                {
                    vertrix_xm_sample_free(&loaded);
                    return 0;
                }
            }
            loaded.ready = 1;
            *output = loaded;
            return 1;
        }
        offset = payload;
    }
    return 0;
}

int vertrix_xm_instrument_header(const uint8_t *data, size_t size, const VertrixXmInstrument *carry,
                                 VertrixXmInstrument *output)
{
    if (!data || !output || size < 29)
    {
        return 0;
    }
    uint32_t length = dword(data);
    uint16_t count = word(data + 27);
    if (length < 29 || length > size || count > 16 || (count && length < 243))
    {
        return 0;
    }
    VertrixXmInstrument next = {0};
    if (!count && carry)
    {
        next = *carry;
    }
    memset(next.name, 0, sizeof(next.name));
    for (unsigned index = 0; index < 22 && data[4 + index]; index++)
    {
        next.name[index] = (char)data[4 + index];
    }
    next.samples = count;
    if (count)
    {
        memcpy(next.mapping, data + 33, 96);
        next.waveform = data[235];
        next.sweep = data[236];
        next.depth = data[237];
        next.rate = data[238];
        next.fade_step = word(data + 239);
        VertrixXmEnvelope *envelopes[2] = {&next.volume, &next.pan};
        for (unsigned index = 0; index < 2; index++)
        {
            VertrixXmEnvelope *envelope = envelopes[index];
            uint8_t points = data[225 + index];
            envelope->count = points > 12 ? 12 : points;
            envelope->sustain = data[227 + index * 3];
            envelope->loop_start = data[228 + index * 3];
            envelope->loop_end = data[229 + index * 3];
            envelope->flags = data[233 + index] & 7;
            for (unsigned point = 0; point < envelope->count; point++)
            {
                size_t offset = 129 + index * 48 + point * 4;
                envelope->points[point].tick = word(data + offset);
                envelope->points[point].value = word(data + offset + 2);
            }
        }
    }
    for (unsigned note = 0; note < 96; note++)
    {
        if (next.mapping[note] >= count)
        {
            next.mapping[note] = 0;
        }
    }
    *output = next;
    return 1;
}

int vertrix_xm_instrument_load(VertrixVf *archive, const char *name, uint32_t instrument,
                               const VertrixXmInstrument *initial, VertrixXmInstrument *output)
{
    if (!output)
    {
        return 0;
    }
    VertrixXmHeader song;
    uint32_t index, size, offset;
    if (!header_read(archive, name, &song, &index, &size, &offset) ||
        instrument >= song.instruments)
    {
        return 0;
    }
    for (uint32_t pattern = 0; pattern < song.patterns; pattern++)
    {
        uint8_t header[9];
        if (size - offset < sizeof(header) ||
            !vertrix_vf_read(archive, index, offset, header, sizeof(header)))
        {
            return 0;
        }
        uint32_t length = dword(header);
        uint32_t packed = word(header + 7);
        if (length < 9 || length > size - offset || packed > size - offset - length || header[4])
        {
            return 0;
        }
        offset += length + packed;
    }
    VertrixXmInstrument carry = {0};
    if (initial)
    {
        carry = *initial;
    }
    for (uint32_t current = 0; current <= instrument; current++)
    {
        uint8_t prefix[29];
        if (size - offset < sizeof(prefix) ||
            !vertrix_vf_read(archive, index, offset, prefix, sizeof(prefix)))
        {
            return 0;
        }
        uint32_t length = dword(prefix);
        uint16_t count = word(prefix + 27);
        if (length < 29 || length > size - offset || count > 16 || (count && length < 243))
        {
            return 0;
        }
        uint8_t *header = malloc(length);
        if (!header)
        {
            return 0;
        }
        if (!vertrix_vf_read(archive, index, offset, header, length))
        {
            free(header);
            return 0;
        }
        uint32_t sample_header_size = count ? dword(header + 29) : 0;
        int valid = vertrix_xm_instrument_header(header, length, &carry, &carry);
        free(header);
        if (!valid)
        {
            return 0;
        }
        if (current == instrument)
        {
            *output = carry;
            return 1;
        }
        offset += length;
        if (count && (sample_header_size < 40 || sample_header_size > (size - offset) / count))
        {
            return 0;
        }
        uint32_t payload = offset + sample_header_size * count;
        for (uint32_t sample = 0; sample < count; sample++)
        {
            uint8_t bytes[4];
            if (!vertrix_vf_read(archive, index, offset + sample * sample_header_size, bytes, 4))
            {
                return 0;
            }
            uint32_t length = dword(bytes);
            if (length > size - payload)
            {
                return 0;
            }
            payload += length;
        }
        offset = payload;
    }
    return 0;
}
