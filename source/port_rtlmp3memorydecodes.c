#include "port_rtlmp3memorydecodes.h"

/* Decodes a whole MP3 stream into memory: allocates a 400,000-byte buffer, resets the reader,
 * decodes frames 0x2000 bytes at a time (0x405f70) and appends each frame's output, then wraps the
 * result in a new 0x18-byte sample. */

enum
{
    /* The routine's frame under its return slot. Its callees reach three of its locals by
     * address, so they keep the original's places below the saved ebp. */
    BELOW = 0x679c,
    DECODER = 0x6798,
    FRAME_OUTPUT = 0x2028,
    FRAME_SIZE = 0x24,
    FRAME_BYTES = 0x2000,
    BUFFER_BYTES = 400000,
    DECODE_FAILED = 0xffffffffu,
    LOAD_FAILED = 0xb,

    /* The decoder (0x405d60): its MPEG header (+0x14, 0x404480), the header's sample rate index,
     * and the word table of rates it indexes (dword strides, MPEG-HEADER.md). */
    DECODER_HEADER = 0x14,
    DECODER_RATE_INDEX = 0x38,
    SAMPLE_RATES = 0x4f41ac,

    /* The sample: its data, byte count, loop bounds, rate and flags (bit 0: 16-bit samples). */
    SAMPLE_BYTES = 0x18,
    SAMPLE_DATA = 0,
    SAMPLE_LENGTH = 8,
    SAMPLE_LOOP_START = 0xc,
    SAMPLE_LOOP_END = 0x10,
    SAMPLE_RATE = 0x14,
    SAMPLE_FLAGS = 0x16,
    SAMPLE_16_BIT = 1,

    /* The bytes of every sample loaded so far. */
    LOADED_BYTES = 0x598dac,

    CALLOC = 0x4ec160,
    FREE = 0x4ea190,
    READER_RESET = 0x405d60,
    STREAM_DATA = 0x48aa70,
    STREAM_POSITION = 0x48aa80,
    DECODE_FRAME = 0x405f70,
    RETURNS_AT_ONCE = 0x404580,
    SAMPLE_LOAD = 0x40ac50,
    SAMPLE_WRITE = 0x40acd0
};

/* 0x405f70: decode the next frame into the frame output, its byte count into the frame size.
 * The first call hands over the stream's data and position, the later ones nothing (the decoder
 * reads on from where it is). Returns 0, 1 when the input runs out, -1 on an error. */
static uint32_t decode_frame(Port *port, uint32_t decoder, uint32_t position, uint32_t data,
                             uint32_t output, uint32_t size)
{
    const uint32_t stack[2] = {FRAME_BYTES, size};
    return port_call_stack(port, DECODE_FRAME, decoder, position, data, output, stack, 2);
}

static void release(Port *port, uint32_t block)
{
    port_call(port, FREE, block, 0, 0, 0);
}

/* Original 0x48b2f0 (eax = stream, edx = where the sample goes): decode the stream frame by frame
 * into a 400,000-byte buffer (no bound is checked), then make a 0x18-byte sample of it: the byte
 * count, the stream's sample rate, 16-bit, no loop. 0x40ac50 allocates and registers the sample's
 * data; the buffer is copied there and written to the driver (0x40acd0), and the bytes are added
 * to 0x598dac. Returns 0, or 0xb (nothing stored) when decoding fails or there is no memory for
 * the sample. When 0x40ac50 fails the original frees the buffer and the sample and clears the
 * result, then goes on as if it had not: it fills, stores and counts the freed sample and frees
 * the buffer a second time. */
uint32_t vertrix_port_mp3_decode_to_memory_48b2f0(PORT_SIGNATURE)
{
    /* Static: 26 KB is too much for the Wii thread stack, and the routine is not reentered (its
     * callees decode one MP3 frame and never call back). */
    static uint8_t stack[BELOW + 8];
    Port port;
    port_open_stack(&port, stack, calls, services, globals, entry, BELOW);
    const uint32_t frame = entry->esp - 4;
    const uint32_t decoder = frame - DECODER;
    const uint32_t output = frame - FRAME_OUTPUT;
    const uint32_t size = frame - FRAME_SIZE;
    const uint32_t stream = entry->eax;
    const uint32_t result = entry->edx;

    const uint32_t buffer = port_call(&port, CALLOC, 1, BUFFER_BYTES, 0, 0);
    port_call(&port, READER_RESET, decoder, 0, 0, 0);
    const uint32_t data = port_call(&port, STREAM_DATA, stream, 0, 0, 0);
    const uint32_t position = port_call(&port, STREAM_POSITION, stream, 0, 0, 0);
    uint32_t status = decode_frame(&port, decoder, position, data, output, size);
    /* The original calls 0x404580 on the header here: it returns at once. */
    port_call(&port, RETURNS_AT_ONCE, decoder + DECODER_HEADER, 0, 0, 0);

    uint32_t length = 0;
    while (status == 0 && !port.env.failed)
    {
        const uint32_t bytes = port_u32(&port, size, 0);
        port_copy(&port, buffer + length, output, bytes);
        length += bytes;
        status = decode_frame(&port, decoder, 0, 0, output, size);
    }

    uint32_t sample = 0;
    if (status != DECODE_FAILED)
    {
        sample = port_call(&port, CALLOC, 1, SAMPLE_BYTES, 0, 0);
    }
    if (sample == 0)
    {
        release(&port, buffer);
        return port_return(&port, LOAD_FAILED, 0);
    }
    const uint32_t rate_index = port_u32(&port, decoder, DECODER_RATE_INDEX);
    port_set16(&port, sample, SAMPLE_FLAGS, SAMPLE_16_BIT);
    port_set32(&port, sample, SAMPLE_LOOP_START, 0);
    port_set16(&port, sample, SAMPLE_RATE, port_u16(&port, SAMPLE_RATES + rate_index * 4, 0));
    port_set32(&port, sample, SAMPLE_LENGTH, length);
    port_set32(&port, sample, SAMPLE_LOOP_END, 0);
    if (port_call(&port, SAMPLE_LOAD, sample, 0, 0, 0) != 0)
    {
        release(&port, buffer);
        release(&port, sample);
        port_set32(&port, result, 0, 0);
    }
    port_copy(&port, port_u32(&port, sample, SAMPLE_DATA), buffer, length);
    port_call(&port, SAMPLE_WRITE, sample, 0, length, 0);
    port_set32(&port, result, 0, sample);
    release(&port, buffer);
    port_set32(&port, LOADED_BYTES, 0,
               port_u32(&port, LOADED_BYTES, 0) + port_u32(&port, sample, SAMPLE_LENGTH));
    return port_return(&port, 0, 0);
}
