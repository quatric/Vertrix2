#include "rtlwavestreamloads.h"

/* Loads a WAV file from a stream into a new sample. */

enum
{
    /* The RIFF header and the current chunk, read into globals. */
    RIFF_ID = 0x5bd850,
    RIFF_REMAINING = 0x5bd854,
    RIFF_FORM = 0x5bd858,
    CHUNK_ID = 0x5bd860,
    CHUNK_SIZE = 0x5bd864,
    /* The 'fmt ' chunk: format tag, channels, sample rate, byte rate, block align, bits. */
    FORMAT = 0x5bd868,
    FORMAT_BYTES = 0x10,
    FORMAT_TAG = 0x5bd868,
    FORMAT_CHANNELS = 0x5bd86a,
    FORMAT_RATE = 0x5bd86c,
    FORMAT_BYTE_RATE = 0x5bd870,
    FORMAT_ALIGN = 0x5bd874,
    FORMAT_BITS = 0x5bd876,

    ID_RIFF = 0x46464952,
    ID_WAVE = 0x45564157,
    ID_FMT = 0x20746d66,
    ID_DATA = 0x61746164,
    WAVE_FORMAT_PCM = 1,

    /* The sample, as for 0x48b2f0: its data, byte count, rate and flags (+0x16 bit 0 16-bit,
     * +0x17 bit 0 stereo). */
    SAMPLE_BYTES = 0x18,
    SAMPLE_DATA = 0,
    SAMPLE_LENGTH = 8,
    SAMPLE_RATE = 0x14,
    SAMPLE_FLAGS = 0x16,
    SAMPLE_CHANNEL_FLAGS = 0x17,
    LOADED_BYTES = 0x598dac,

    NO_OUTPUT = 2,
    NO_MEMORY = 8,
    BAD_FILE = 0xb,

    CALLOC = 0x4ec160,
    MEMSET = 0x4eb5c0,
    STREAM_READ = 0x48a930,
    STREAM_SKIP = 0x48aa90,
    SAMPLE_FREE = 0x4b8170,
    SAMPLE_LOAD = 0x40ac50,
    SAMPLE_WRITE = 0x40acd0
};

static void read(Port *port, uint32_t stream, uint32_t to, uint32_t bytes)
{
    port_call(port, STREAM_READ, stream, to, 1, bytes);
}

/* A RIFF size, rounded up to even. */
static void round_size(Port *port, uint32_t global)
{
    const uint32_t size = port_u32(port, global, 0);
    port_set32(port, global, 0, size + (size & 1));
}

/* The data chunk: needs PCM, then loads the samples (8-bit ones made signed) and hands them to the
 * driver. */
static uint32_t load_data(Port *port, uint32_t stream, uint32_t sample, uint32_t out)
{
    if (port_u16(port, FORMAT_TAG, 0) != WAVE_FORMAT_PCM)
    {
        port_call(port, SAMPLE_FREE, sample, 0, 0, 0);
        return BAD_FILE;
    }
    port_set32(port, sample, SAMPLE_LENGTH, port_u32(port, CHUNK_SIZE, 0));
    port_set16(port, sample, SAMPLE_FLAGS, 0);
    port_set16(port, sample, SAMPLE_RATE, port_u16(port, FORMAT_RATE, 0));
    if (port_u16(port, FORMAT_BITS, 0) != 8)
    {
        port_set8(port, sample, SAMPLE_FLAGS, port_u8(port, sample, SAMPLE_FLAGS) | 1);
    }
    if (port_u16(port, FORMAT_CHANNELS, 0) != 1)
    {
        port_set8(port, sample, SAMPLE_CHANNEL_FLAGS,
                  port_u8(port, sample, SAMPLE_CHANNEL_FLAGS) | 1);
    }
    const uint32_t status = port_call(port, SAMPLE_LOAD, sample, 0, 0, 0);
    if (status != 0)
    {
        /* The original keeps the status in edx across 0x4b8170, which saves edx. */
        port_call(port, SAMPLE_FREE, sample, 0, 0, 0);
        return status;
    }
    read(port, stream, port_u32(port, sample, SAMPLE_DATA), port_u32(port, sample, SAMPLE_LENGTH));
    if ((port_u8(port, sample, SAMPLE_FLAGS) & 1) == 0)
    {
        for (uint32_t at = 0; at < port_u32(port, sample, SAMPLE_LENGTH) && !port->env.failed; at++)
        {
            const uint32_t data = port_u32(port, sample, SAMPLE_DATA);
            port_set8(port, data, at, port_u8(port, data, at) ^ 0x80);
        }
    }
    port_call(port, SAMPLE_WRITE, sample, 0, port_u32(port, sample, SAMPLE_LENGTH), 0);
    port_set32(port, out, 0, sample);
    port_set32(port, LOADED_BYTES, 0,
               port_u32(port, LOADED_BYTES, 0) + port_u32(port, sample, SAMPLE_LENGTH));
    return 0;
}

/* Original 0x4b7e80 (eax = the stream, edx = where the sample goes): returns 0, 2 without an
 * output, 8 without memory, the status of a failed 0x40ac50, or 0xb for a file that is not a PCM
 * WAVE or has no data chunk. When the chunks run out the sample is not freed. 0x48aa90 skips a
 * chunk with the ecx the original leaves: 2 after the format chunk, else the bytes left. */
uint32_t vertrix_port_wave_stream_load_4b7e80(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t stream = entry->eax;
    const uint32_t out = entry->edx;
    if (out == 0)
    {
        return port_return(&port, NO_OUTPUT, 0);
    }
    port_set32(&port, out, 0, 0);
    const uint32_t sample = port_call(&port, CALLOC, 1, SAMPLE_BYTES, 0, 0);
    if (sample == 0)
    {
        return port_return(&port, NO_MEMORY, 0);
    }
    read(&port, stream, RIFF_ID, 4);
    read(&port, stream, RIFF_REMAINING, 4);
    read(&port, stream, RIFF_FORM, 4);
    round_size(&port, RIFF_REMAINING);
    if (port_u32(&port, RIFF_ID, 0) != ID_RIFF || port_u32(&port, RIFF_FORM, 0) != ID_WAVE)
    {
        port_call(&port, SAMPLE_FREE, sample, 0, 0, 0);
        return port_return(&port, BAD_FILE, 0);
    }
    port_call(&port, MEMSET, FORMAT, 0, FORMAT_BYTES, 0);
    port_set32(&port, RIFF_REMAINING, 0, port_u32(&port, RIFF_REMAINING, 0) - 4);
    while (port_u32(&port, RIFF_REMAINING, 0) != 0 && !port.env.failed)
    {
        read(&port, stream, CHUNK_ID, 4);
        read(&port, stream, CHUNK_SIZE, 4);
        round_size(&port, CHUNK_SIZE);
        const uint32_t size = port_u32(&port, CHUNK_SIZE, 0);
        const uint32_t remaining = port_u32(&port, RIFF_REMAINING, 0) - (size + 8);
        port_set32(&port, RIFF_REMAINING, 0, remaining);
        const uint32_t id = port_u32(&port, CHUNK_ID, 0);
        if (id == ID_FMT)
        {
            read(&port, stream, FORMAT_TAG, 2);
            read(&port, stream, FORMAT_CHANNELS, 2);
            read(&port, stream, FORMAT_RATE, 4);
            read(&port, stream, FORMAT_BYTE_RATE, 4);
            read(&port, stream, FORMAT_ALIGN, 2);
            read(&port, stream, FORMAT_BITS, 2);
            port_call(&port, STREAM_SKIP, stream, port_u32(&port, CHUNK_SIZE, 0) - FORMAT_BYTES, 0,
                      2);
        }
        else if (id == ID_DATA)
        {
            return port_return(&port, load_data(&port, stream, sample, out), 0);
        }
        else
        {
            port_call(&port, STREAM_SKIP, stream, size, 0, remaining);
        }
    }
    return port_return(&port, BAD_FILE, 0);
}
