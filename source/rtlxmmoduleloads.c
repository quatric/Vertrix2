#include "rtlxmmoduleloads.h"

/* Loads an XM (FastTracker 2) module: its header, patterns, instruments and samples, each read
 * into globals first and then copied into a 0x158-byte module record. */

enum
{
    /* The file header. */
    HEADER_ID = 0x5bd880,
    HEADER_ID_BYTES = 0x11,
    EXPECTED_ID = 0x511143, /* "Extended Module: " */
    HEADER_NAME = 0x5bd891,
    HEADER_EOF_MARK = 0x5bd8a5,
    HEADER_TRACKER = 0x5bd8a6,
    HEADER_VERSION = 0x5bd8ba,
    HEADER_SIZE = 0x5bd8bc,
    HEADER_SONG_LENGTH = 0x5bd8c0,
    HEADER_RESTART = 0x5bd8c2,
    HEADER_CHANNELS = 0x5bd8c4,
    HEADER_PATTERNS = 0x5bd8c6,
    HEADER_INSTRUMENTS = 0x5bd8c8,
    HEADER_FLAGS = 0x5bd8ca,
    HEADER_TEMPO = 0x5bd8cc,
    HEADER_BPM = 0x5bd8ce,
    HEADER_ORDERS = 0x5bd8d0,
    HEADER_ORDER_BYTES = 0x100,
    /* The header size counts from its own field: these are the bytes of it read. */
    HEADER_READ = 0x114,
    XM_VERSION = 0x104,
    MAX_SONG_LENGTH = 0x100,
    MAX_PATTERNS = 0x100,
    MAX_INSTRUMENTS = 0x80,
    MAX_CHANNELS = 0x20,

    /* The module record. */
    MODULE_BYTES = 0x158,
    MODULE_NAME_BYTES = 0x14,
    MODULE_FLAGS = 0x20,
    MODULE_SONG_LENGTH = 0x22,
    MODULE_RESTART = 0x24,
    MODULE_CHANNELS = 0x26,
    MODULE_PATTERNS = 0x28,
    MODULE_INSTRUMENTS = 0x2a,
    MODULE_TEMPO = 0x2c,
    MODULE_BPM = 0x2e,
    MODULE_ORDERS = 0x30,
    MODULE_PANNING = 0x130,
    MODULE_PATTERN_LIST = 0x150,
    MODULE_INSTRUMENT_LIST = 0x154,
    CENTRE = 0x7f,

    /* A pattern's header, and its 12-byte record. */
    PATTERN_HEADER_SIZE = 0x5bd9d0,
    PATTERN_PACKING = 0x5bd9d4,
    PATTERN_ROWS = 0x5bd9d5,
    PATTERN_DATA_BYTES = 0x5bd9d7,
    PATTERN_HEADER_READ = 9,
    PATTERN_BYTES = 0xc,
    PATTERN_PACKING_OUT = 0,
    PATTERN_CHANNELS = 2,
    PATTERN_ROWS_OUT = 4,
    PATTERN_SIZE = 6,
    PATTERN_DATA = 8,

    /* An instrument's header. */
    INSTRUMENT_SIZE = 0x5bd9e0,
    INSTRUMENT_NAME = 0x5bd9e4,
    INSTRUMENT_NAME_BYTES = 0x16,
    INSTRUMENT_TYPE = 0x5bd9fa,
    INSTRUMENT_SAMPLES = 0x5bd9fb,
    SAMPLE_HEADER_SIZE = 0x5bd9fd,
    NOTE_SAMPLES = 0x5bda01,
    NOTES = 0x60,
    VOLUME_ENVELOPE = 0x5bda61,
    PANNING_ENVELOPE = 0x5bda91,
    ENVELOPE_POINTS = 0xc,
    VOLUME_POINTS = 0x5bdac1,
    PANNING_POINTS = 0x5bdac2,
    VOLUME_SUSTAIN = 0x5bdac3,  /* then loop start and end */
    PANNING_SUSTAIN = 0x5bdac6, /* the same */
    VOLUME_TYPE = 0x5bdac9,
    PANNING_TYPE = 0x5bdaca,
    VIBRATO = 0x5bdacb, /* type, sweep, depth, rate */
    FADEOUT = 0x5bdacf,
    RESERVED = 0x5bdad1,
    /* The bytes of the header read before the sample header size, and of all of it read. */
    INSTRUMENT_SHORT_READ = 0x1d,
    INSTRUMENT_LONG_EXTRA = 0xd6,
    MAX_SAMPLES = 0x10,

    /* An instrument's 0xfc-byte record. */
    INSTRUMENT_BYTES = 0xfc,
    INSTRUMENT_NOTE_SAMPLES = 0x20,
    INSTRUMENT_SAMPLE_COUNT = 0x80,
    INSTRUMENT_VIBRATO = 0x82,
    INSTRUMENT_FADEOUT = 0x86,
    INSTRUMENT_VOLUME = 0x88,  /* the points; their count, sustain, loop and type at 0xb8 */
    INSTRUMENT_PANNING = 0xc0, /* the same at 0xf0 */
    ENVELOPE_COUNT = 0x30,
    INSTRUMENT_SAMPLE_LIST = 0xf8,

    /* A sample's header. */
    SAMPLE_LENGTH = 0x5bdad8,
    SAMPLE_LOOP_START = 0x5bdadc,
    SAMPLE_LOOP_LENGTH = 0x5bdae0,
    SAMPLE_VOLUME = 0x5bdae4,
    SAMPLE_FINETUNE = 0x5bdae5,
    SAMPLE_TYPE = 0x5bdae6,
    SAMPLE_PANNING = 0x5bdae7,
    SAMPLE_NOTE = 0x5bdae8,
    SAMPLE_RESERVED = 0x5bdae9,
    SAMPLE_NAME = 0x5bdaea,
    SAMPLE_NAME_BYTES = 0x16,
    SAMPLE_HEADER_READ = 0x28,

    /* A sample's 0x3c-byte record; the driver's sample is at +0x24. */
    SAMPLE_BYTES = 0x3c,
    SAMPLE_OUT_VOLUME = 0x20,
    SAMPLE_OUT_PANNING = 0x21,
    SAMPLE_OUT_NOTE = 0x22,
    SAMPLE_OUT_FINETUNE = 0x23,
    SAMPLE_DRIVER = 0x24,
    SAMPLE_OUT_LENGTH = 0x2c,
    SAMPLE_OUT_LOOP_START = 0x2c + 4,
    SAMPLE_OUT_LOOP_END = 0x2c + 8,
    SAMPLE_OUT_RATE = 0x38,
    SAMPLE_OUT_FLAGS = 0x3a,
    SAMPLE_RATE = 0x20ab,

    NO_MEMORY = 8,
    BAD_FILE = 0xb,

    CALLOC = 0x4ec160,
    GETMEM = 0x4e7c90,
    STRNCPY = 0x4eb860,
    FREE = 0x40ef90,
    STREAM_READ = 0x48a930,
    STREAM_SKIP = 0x48aa90,
    SAMPLE_LOAD = 0x40ac50,
    SAMPLE_SIGN = 0x4b8fbc,
    SAMPLE_WRITE = 0x40acd0
};

static void read(Port *port, uint32_t stream, uint32_t to, uint32_t bytes)
{
    port_call(port, STREAM_READ, stream, to, 1, bytes);
}

/* Skips `bytes`; ecx is still the size of the last read. */
static void skip(Port *port, uint32_t stream, uint32_t bytes, uint32_t last_read)
{
    port_call(port, STREAM_SKIP, stream, bytes, 0, last_read);
}

static void or8(Port *port, uint32_t at, uint32_t offset, uint32_t bits)
{
    port_set8(port, at, offset, port_u8(port, at, offset) | bits);
}

/* Header checks: the id, version 1.04 and the limits of the module record. */
static int header_valid(Port *port)
{
    for (uint32_t i = 0; i < HEADER_ID_BYTES; i++)
    {
        if (port_u8(port, HEADER_ID, i) != port_u8(port, EXPECTED_ID, i))
        {
            return 0;
        }
    }
    return port_u16(port, HEADER_VERSION, 0) == XM_VERSION &&
           port_u16(port, HEADER_SONG_LENGTH, 0) <= MAX_SONG_LENGTH &&
           port_u16(port, HEADER_PATTERNS, 0) <= MAX_PATTERNS &&
           port_u16(port, HEADER_INSTRUMENTS, 0) <= MAX_INSTRUMENTS &&
           port_u16(port, HEADER_CHANNELS, 0) <= MAX_CHANNELS;
}

static void read_header(Port *port, uint32_t stream)
{
    static const struct
    {
        uint32_t to, bytes;
    } FIELDS[] = {{HEADER_ID, HEADER_ID_BYTES},
                  {HEADER_NAME, 0x14},
                  {HEADER_EOF_MARK, 1},
                  {HEADER_TRACKER, 0x14},
                  {HEADER_VERSION, 2},
                  {HEADER_SIZE, 4},
                  {HEADER_SONG_LENGTH, 2},
                  {HEADER_RESTART, 2},
                  {HEADER_CHANNELS, 2},
                  {HEADER_PATTERNS, 2},
                  {HEADER_INSTRUMENTS, 2},
                  {HEADER_FLAGS, 2},
                  {HEADER_TEMPO, 2},
                  {HEADER_BPM, 2},
                  {HEADER_ORDERS, HEADER_ORDER_BYTES}};
    for (unsigned i = 0; i < sizeof FIELDS / sizeof FIELDS[0]; i++)
    {
        read(port, stream, FIELDS[i].to, FIELDS[i].bytes);
    }
    skip(port, stream, port_u32(port, HEADER_SIZE, 0) - HEADER_READ, HEADER_ORDER_BYTES);
}

static void fill_module(Port *port, uint32_t module)
{
    port_call(port, STRNCPY, module, HEADER_NAME, MODULE_NAME_BYTES, 0);
    if (port_u8(port, HEADER_FLAGS, 0) & 1)
    {
        or8(port, module, MODULE_FLAGS, 1);
    }
    port_set16(port, module, MODULE_SONG_LENGTH, port_u16(port, HEADER_SONG_LENGTH, 0));
    port_set16(port, module, MODULE_RESTART, port_u16(port, HEADER_RESTART, 0));
    port_set16(port, module, MODULE_CHANNELS, port_u16(port, HEADER_CHANNELS, 0));
    port_set16(port, module, MODULE_PATTERNS, port_u16(port, HEADER_PATTERNS, 0));
    port_set16(port, module, MODULE_INSTRUMENTS, port_u16(port, HEADER_INSTRUMENTS, 0));
    port_set16(port, module, MODULE_TEMPO, port_u16(port, HEADER_TEMPO, 0));
    port_set16(port, module, MODULE_BPM, port_u16(port, HEADER_BPM, 0));
    for (uint32_t i = 0; i < port_u16(port, module, MODULE_SONG_LENGTH); i++)
    {
        port_set8(port, module + i, MODULE_ORDERS, port_u8(port, HEADER_ORDERS, i));
    }
    for (uint32_t i = 0; i < port_u16(port, module, MODULE_CHANNELS); i++)
    {
        port_set8(port, module + i, MODULE_PANNING, CENTRE);
    }
}

/* Reads every pattern's header and packed data; returns 0 or an error. */
static uint32_t read_patterns(Port *port, uint32_t stream, uint32_t module)
{
    uint32_t pattern = port_u32(port, module, MODULE_PATTERN_LIST);
    for (uint32_t i = 0; i < port_u16(port, module, MODULE_PATTERNS) && !port->env.failed;
         i++, pattern += PATTERN_BYTES)
    {
        read(port, stream, PATTERN_HEADER_SIZE, 4);
        read(port, stream, PATTERN_PACKING, 1);
        read(port, stream, PATTERN_ROWS, 2);
        read(port, stream, PATTERN_DATA_BYTES, 2);
        skip(port, stream, port_u32(port, PATTERN_HEADER_SIZE, 0) - PATTERN_HEADER_READ, 2);
        if (port_u8(port, PATTERN_PACKING, 0) != 0)
        {
            return BAD_FILE;
        }
        port_set16(port, pattern, PATTERN_PACKING_OUT, port_u8(port, PATTERN_PACKING, 0));
        port_set16(port, pattern, PATTERN_CHANNELS, port_u16(port, module, MODULE_CHANNELS));
        port_set16(port, pattern, PATTERN_ROWS_OUT, port_u16(port, PATTERN_ROWS, 0));
        port_set16(port, pattern, PATTERN_SIZE, port_u16(port, PATTERN_DATA_BYTES, 0));
        const uint32_t size = port_u16(port, pattern, PATTERN_SIZE);
        if (size != 0)
        {
            port_set32(port, pattern, PATTERN_DATA, port_call(port, GETMEM, size, 0, 0, 0));
            if (port_u32(port, pattern, PATTERN_DATA) == 0)
            {
                return NO_MEMORY;
            }
            read(port, stream, port_u32(port, pattern, PATTERN_DATA), size);
        }
    }
    return 0;
}

/* The instrument header past its sample count, read only when it has samples. */
static void read_instrument_samples_header(Port *port, uint32_t stream)
{
    read(port, stream, SAMPLE_HEADER_SIZE, 4);
    read(port, stream, NOTE_SAMPLES, NOTES);
    for (uint32_t i = 0; i < ENVELOPE_POINTS; i++)
    {
        read(port, stream, VOLUME_ENVELOPE + i * 4, 4);
    }
    for (uint32_t i = 0; i < ENVELOPE_POINTS; i++)
    {
        read(port, stream, PANNING_ENVELOPE + i * 4, 4);
    }
    /* The point counts, sustain and loop points, envelope types and vibrato: a byte each. */
    for (uint32_t at = VOLUME_POINTS; at < FADEOUT; at++)
    {
        read(port, stream, at, 1);
    }
    read(port, stream, FADEOUT, 2);
    read(port, stream, RESERVED, 2);
    port_set32(port, INSTRUMENT_SIZE, 0,
               port_u32(port, INSTRUMENT_SIZE, 0) - INSTRUMENT_LONG_EXTRA);
}

/* An envelope: its points, count, sustain and loop points, and the type's three flags. */
static void copy_envelope(Port *port, uint32_t instrument, uint32_t out, uint32_t points,
                          uint32_t count, uint32_t sustain, uint32_t type)
{
    const uint32_t at = instrument + out + ENVELOPE_COUNT;
    port_set8(port, at, 0, port_u8(port, count, 0));
    for (uint32_t k = 0; k < 3; k++)
    {
        port_set8(port, at, 1 + k, port_u8(port, sustain, k));
    }
    for (uint32_t bit = 1; bit <= 4; bit <<= 1)
    {
        if (port_u8(port, type, 0) & bit)
        {
            or8(port, at, 4, bit);
        }
    }
    for (uint32_t i = 0; i < port_u8(port, at, 0); i++)
    {
        port_set16(port, instrument + out, i * 4, port_u16(port, points, i * 4));
        port_set16(port, instrument + out, i * 4 + 2, port_u32(port, points, i * 4) >> 16);
    }
}

static void fill_instrument(Port *port, uint32_t instrument)
{
    port_call(port, STRNCPY, instrument, INSTRUMENT_NAME, INSTRUMENT_NAME_BYTES, 0);
    const uint32_t samples = port_u16(port, INSTRUMENT_SAMPLES, 0);
    for (uint32_t i = 0; i < NOTES; i++)
    {
        const uint32_t sample = port_u8(port, NOTE_SAMPLES, i);
        port_set8(port, instrument + i, INSTRUMENT_NOTE_SAMPLES, sample < samples ? sample : 0);
    }
    port_set16(port, instrument, INSTRUMENT_SAMPLE_COUNT, samples);
    for (uint32_t k = 0; k < 4; k++)
    {
        port_set8(port, instrument, INSTRUMENT_VIBRATO + k, port_u8(port, VIBRATO, k));
    }
    port_set16(port, instrument, INSTRUMENT_FADEOUT, port_u16(port, FADEOUT, 0));
    copy_envelope(port, instrument, INSTRUMENT_VOLUME, VOLUME_ENVELOPE, VOLUME_POINTS,
                  VOLUME_SUSTAIN, VOLUME_TYPE);
    copy_envelope(port, instrument, INSTRUMENT_PANNING, PANNING_ENVELOPE, PANNING_POINTS,
                  PANNING_SUSTAIN, PANNING_TYPE);
}

static void read_sample_header(Port *port, uint32_t stream, uint32_t sample)
{
    read(port, stream, SAMPLE_LENGTH, 4);
    read(port, stream, SAMPLE_LOOP_START, 4);
    read(port, stream, SAMPLE_LOOP_LENGTH, 4);
    for (uint32_t at = SAMPLE_VOLUME; at <= SAMPLE_RESERVED; at++)
    {
        read(port, stream, at, 1);
    }
    read(port, stream, SAMPLE_NAME, SAMPLE_NAME_BYTES);
    skip(port, stream, port_u32(port, SAMPLE_HEADER_SIZE, 0) - SAMPLE_HEADER_READ,
         SAMPLE_NAME_BYTES);
    port_call(port, STRNCPY, sample, SAMPLE_NAME, SAMPLE_NAME_BYTES, 0);
    port_set32(port, sample, SAMPLE_OUT_LENGTH, port_u32(port, SAMPLE_LENGTH, 0));
    port_set32(port, sample, SAMPLE_OUT_LOOP_START, port_u32(port, SAMPLE_LOOP_START, 0));
    port_set32(port, sample, SAMPLE_OUT_LOOP_END,
               port_u32(port, SAMPLE_LOOP_START, 0) + port_u32(port, SAMPLE_LOOP_LENGTH, 0));
    port_set16(port, sample, SAMPLE_OUT_RATE, SAMPLE_RATE);
    port_set8(port, sample, SAMPLE_OUT_VOLUME, port_u8(port, SAMPLE_VOLUME, 0));
    port_set8(port, sample, SAMPLE_OUT_PANNING, port_u8(port, SAMPLE_PANNING, 0));
    port_set8(port, sample, SAMPLE_OUT_NOTE, port_u8(port, SAMPLE_NOTE, 0));
    port_set8(port, sample, SAMPLE_OUT_FINETUNE, port_u8(port, SAMPLE_FINETUNE, 0));
    /* Bit 4 (16-bit) becomes the driver's bit 0, the loop bits 0 and 1 its bits 4 and 5. */
    const uint32_t type = port_u8(port, SAMPLE_TYPE, 0);
    if (type & 0x10)
    {
        or8(port, sample, SAMPLE_OUT_FLAGS, 1);
    }
    if (type & 1)
    {
        or8(port, sample, SAMPLE_OUT_FLAGS, 0x10);
    }
    if (type & 2)
    {
        or8(port, sample, SAMPLE_OUT_FLAGS, 0x20);
    }
}

/* Reads one instrument with its sample headers and sample data; returns 0 or an error. */
static uint32_t read_instrument(Port *port, uint32_t stream, uint32_t instrument)
{
    read(port, stream, INSTRUMENT_SIZE, 4);
    read(port, stream, INSTRUMENT_NAME, INSTRUMENT_NAME_BYTES);
    read(port, stream, INSTRUMENT_TYPE, 1);
    read(port, stream, INSTRUMENT_SAMPLES, 2);
    if (port_u16(port, INSTRUMENT_SAMPLES, 0) != 0)
    {
        read_instrument_samples_header(port, stream);
    }
    skip(port, stream, port_u32(port, INSTRUMENT_SIZE, 0) - INSTRUMENT_SHORT_READ, 2);
    if (port_u8(port, VOLUME_POINTS, 0) > ENVELOPE_POINTS)
    {
        port_set8(port, VOLUME_POINTS, 0, ENVELOPE_POINTS);
    }
    if (port_u8(port, PANNING_POINTS, 0) > ENVELOPE_POINTS)
    {
        port_set8(port, PANNING_POINTS, 0, ENVELOPE_POINTS);
    }
    /* After the clamps above only the sample count can fail here. */
    if (port_u16(port, INSTRUMENT_SAMPLES, 0) > MAX_SAMPLES ||
        port_u8(port, VOLUME_POINTS, 0) > ENVELOPE_POINTS ||
        port_u8(port, PANNING_POINTS, 0) > ENVELOPE_POINTS)
    {
        return BAD_FILE;
    }
    fill_instrument(port, instrument);
    const uint32_t count = port_u16(port, instrument, INSTRUMENT_SAMPLE_COUNT);
    if (count != 0)
    {
        port_set32(port, instrument, INSTRUMENT_SAMPLE_LIST,
                   port_call(port, CALLOC, count, SAMPLE_BYTES, 0, 0));
        if (port_u32(port, instrument, INSTRUMENT_SAMPLE_LIST) == 0)
        {
            return NO_MEMORY;
        }
    }
    const uint32_t list = port_u32(port, instrument, INSTRUMENT_SAMPLE_LIST);
    for (uint32_t i = 0; i < port_u16(port, INSTRUMENT_SAMPLES, 0) && !port->env.failed; i++)
    {
        read_sample_header(port, stream, list + i * SAMPLE_BYTES);
    }
    for (uint32_t i = 0; i < port_u16(port, INSTRUMENT_SAMPLES, 0) && !port->env.failed; i++)
    {
        const uint32_t sample = list + i * SAMPLE_BYTES;
        const uint32_t length = port_u32(port, sample, SAMPLE_OUT_LENGTH);
        if (length == 0)
        {
            continue;
        }
        const uint32_t status = port_call(port, SAMPLE_LOAD, sample + SAMPLE_DRIVER, 0, 0, 0);
        if (status != 0)
        {
            return status;
        }
        read(port, stream, port_u32(port, sample, SAMPLE_DRIVER), length);
        port_call(port, SAMPLE_SIGN, sample + SAMPLE_DRIVER, 0, 0, 0);
        port_call(port, SAMPLE_WRITE, sample + SAMPLE_DRIVER, 0,
                  port_u32(port, sample, SAMPLE_OUT_LENGTH), 0);
    }
    return 0;
}

static uint32_t load(Port *port, uint32_t stream, uint32_t module, uint32_t out)
{
    read_header(port, stream);
    if (!header_valid(port))
    {
        return BAD_FILE;
    }
    fill_module(port, module);
    port_set32(
        port, module, MODULE_PATTERN_LIST,
        port_call(port, CALLOC, port_u16(port, module, MODULE_PATTERNS), PATTERN_BYTES, 0, 0));
    if (port_u32(port, module, MODULE_PATTERN_LIST) == 0)
    {
        return NO_MEMORY;
    }
    const uint32_t instruments = port_u16(port, module, MODULE_INSTRUMENTS);
    if (instruments > 0)
    {
        port_set32(port, module, MODULE_INSTRUMENT_LIST,
                   port_call(port, CALLOC, instruments, INSTRUMENT_BYTES, 0, 0));
        if (port_u32(port, module, MODULE_INSTRUMENT_LIST) == 0)
        {
            return NO_MEMORY;
        }
    }
    else
    {
        port_set32(port, module, MODULE_INSTRUMENT_LIST, 0);
    }
    uint32_t status = read_patterns(port, stream, module);
    if (status != 0)
    {
        return status;
    }
    const uint32_t list = port_u32(port, module, MODULE_INSTRUMENT_LIST);
    for (uint32_t i = 0; i < port_u16(port, module, MODULE_INSTRUMENTS) && !port->env.failed; i++)
    {
        status = read_instrument(port, stream, list + i * INSTRUMENT_BYTES);
        if (status != 0)
        {
            return status;
        }
    }
    port_set32(port, out, 0, module);
    return 0;
}

/* Original 0x4b826f (eax = the stream, edx = where the record goes). A failure after the record is
 * allocated frees only the record, never the patterns, instruments or samples already allocated.
 * The pattern count is allocated even when 0 (calloc of nothing), and an instrument's samples are
 * allocated by its own count while the loops run on the global one. 0x48aa90 skips with the ecx
 * of the last read. */
uint32_t vertrix_port_xm_module_load_4b826f(PORT_SIGNATURE)
{
    Port port;
    port_open(&port, calls, services, globals, entry);
    const uint32_t stream = entry->eax;
    const uint32_t out = entry->edx;
    const uint32_t module = port_call(&port, CALLOC, 1, MODULE_BYTES, 0, 0);
    if (module == 0)
    {
        return port_return(&port, NO_MEMORY, 0);
    }
    const uint32_t status = load(&port, stream, module, out);
    if (status != 0)
    {
        port_call(&port, FREE, module, 0, 0, 0);
    }
    return port_return(&port, status, 0);
}
