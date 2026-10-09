#include "s3m_pattern.h"

#include "actor_storage.h"

enum
{
    BYTE_WIDTH = 1,
    WORD_WIDTH = 2,
    DWORD_WIDTH = 4,
    RECORD_ZERO = 0,
    RECORD_CHANNELS = 2,
    RECORD_ROWS = 4,
    RECORD_SIZE = 6,
    RECORD_POINTER = 8,
    ROWS = 0x40,
    ROW_STRIDE = 5,
    ROW_BYTES = 0xa0,
    MEMORY = 0xa0,
    MEMORY_BYTES = 0x20,
    BYTES_PER_CHANNEL = 0x180,
    ALLOCATE = 0x4e7c90,
    REALLOC = 0x4ec0e0,
    FAILURE = 8,
    CHANNEL_MASK = 0x1f,
    HAS_NOTE = 0x20,
    HAS_VOLUME = 0x40,
    HAS_COMMAND = 0x80,
    NOTE_NONE = 0xff,
    NOTE_OFF = 0xfe,
    XM_NOTE_OFF = 0x61,
    XM_NOTE_LAST = 0x60,
    VOLUME_NONE = 0xff,
    VOLUME_LIMIT = 0x40,
    VOLUME_BIAS = 0x10,
    FLAG_BASE = 0x80,
    FLAG_NOTE = 1,
    FLAG_INSTRUMENT = 2,
    FLAG_VOLUME = 4,
    FLAG_COMMAND = 8,
    FLAG_PARAMETER = 0x10,
    LOW_NIBBLE = 0xf,
    HIGH_NIBBLE = 0xf0,
    WORD_MASK = 0xffff,
    LETTER_BASE = 0x40,
    BYTE_MASK = 0xff
};

/* The pseudo call the lifted routines store an absolute address through (LIFT_GLOBAL_STORE in
 * lift_runtime.h): eax the address, edx the value, one stack argument the width. */
static const uint32_t GLOBAL_STORE = 0xf0000000u;

/* 0x50c80c: the commands whose zero parameter repeats the channel's last one. */
static const char MEMORY_LETTERS[] = "DEFGKLQ";

/* 0x410244: the S3M stereo control SAx as an XM panning parameter (8xx). */
static const uint8_t PANNING[8] = {0, 0xff, 0, 0xff, 0x40, 0xc0, 0x80, 0x80};

typedef struct Convert
{
    const VertrixCalls *calls;
    const VertrixFactoryServices *services;
    const VertrixGlobals *globals;
    int ok;
} Convert;

static uint32_t get(Convert *v, uint32_t handle, size_t offset, unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!v->services->resolve(handle, &storage, &size, v->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, width, &value))
    {
        if (v->globals == NULL)
        {
            v->ok = 0;
            return 0;
        }
        value = v->globals->read(handle + (uint32_t)offset, v->globals->context);
        value &= width == DWORD_WIDTH ? 0xffffffffu : (1u << (8 * width)) - 1;
    }
    return value;
}

static void put(Convert *v, uint32_t handle, size_t offset, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!v->services->resolve(handle, &storage, &size, v->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, width, value))
    {
        uint32_t stack[1] = {width};
        if (v->globals == NULL)
        {
            v->ok = 0;
            return;
        }
        vertrix_calln(v->calls, GLOBAL_STORE, handle + (uint32_t)offset, value, 0, 0, stack, 1,
                      NULL);
    }
}

/* 0x4ec1d0 against 0x50c80c (only the low byte of the letter is compared). */
static int remembered(uint32_t command)
{
    uint32_t letter = (command + LETTER_BASE) & BYTE_MASK;
    for (const char *p = MEMORY_LETTERS; *p != '\0'; p++)
    {
        if ((uint32_t)(uint8_t)*p == letter)
        {
            return 1;
        }
    }
    return 0;
}

/* 0x410329..0x410709: S3M S command (Sxy) to the XM extended command. */
static void special(uint32_t *command, uint32_t *parameter)
{
    uint32_t high = *parameter & HIGH_NIBBLE;
    uint32_t low = *parameter & LOW_NIBBLE;
    static const uint8_t EXTENDED[16] = {0x00, 0x30, 0x50, 0x70, 0x40, 0,    0,    0,
                                         0x80, 0,    0,    0x60, 0xc0, 0xd0, 0xe0, 0};
    if (high == 0xa0)
    {
        if (low > 7)
        {
            *command = 0;
            *parameter = 0;
            return;
        }
        *command = 8;
        *parameter = PANNING[low];
        return;
    }
    if (high == 0 || EXTENDED[high >> 4] != 0)
    {
        *command = 0xe;
        *parameter = EXTENDED[high >> 4] | low;
        return;
    }
    *command = 0;
    *parameter = 0;
}

/* Slides with fine and extra fine forms: E and F (0x410497 and 0x4104dd). */
static void porta(uint32_t *command, uint32_t *parameter, uint32_t extended, uint32_t normal)
{
    uint32_t high = *parameter & HIGH_NIBBLE;
    if (high == HIGH_NIBBLE)
    {
        *command = 0xe;
        *parameter = (*parameter & LOW_NIBBLE) | extended;
    }
    else if (high == 0xe0)
    {
        *command = 0x21;
        *parameter = (*parameter & LOW_NIBBLE) | extended;
    }
    else
    {
        *command = normal;
    }
}

/* Volume slide D (0x410438). */
static void volume_slide(uint32_t *command, uint32_t *parameter)
{
    uint32_t p = *parameter;
    if ((p & HIGH_NIBBLE) == 0)
    {
        *command = 0xa;
        *parameter = p & LOW_NIBBLE;
    }
    else if ((p & LOW_NIBBLE) == 0)
    {
        *command = 0xa;
        *parameter = p & HIGH_NIBBLE;
    }
    else if ((p & HIGH_NIBBLE) == HIGH_NIBBLE)
    {
        *command = 0xe;
        *parameter = (p & LOW_NIBBLE) | 0xb0;
    }
    else if ((p & LOW_NIBBLE) == LOW_NIBBLE)
    {
        *command = 0xe;
        *parameter = (p >> 4) | 0xa0;
    }
    else
    {
        *command = 0;
        *parameter = 0;
    }
}

/* The jump table at 0x4101d8, indexed by the command letter minus '@'. */
static void translate(uint32_t *command, uint32_t *parameter)
{
    switch (*command)
    {
        case 1: /* A: speed */
            if (*parameter < 0x20)
            {
                *command = 0xf;
                return;
            }
            break;
        case 2: /* B */
            *command = 0xb;
            return;
        case 3: /* C */
            *command = 0xd;
            return;
        case 4:
            volume_slide(command, parameter);
            return;
        case 5:
            porta(command, parameter, 0x20, 2);
            return;
        case 6:
            porta(command, parameter, 0x10, 1);
            return;
        case 7: /* G */
            *command = 3;
            return;
        case 8: /* H */
            *command = 4;
            return;
        case 9: /* I */
            *command = 0x1d;
            return;
        case 10: /* J: arpeggio keeps its parameter as XM effect zero */
            *command = 0;
            return;
        case 11: /* K */
            *command = 6;
            return;
        case 12: /* L */
            *command = 5;
            return;
        case 15: /* O */
            *command = 9;
            return;
        case 17: /* Q */
            *command = 0x1b;
            return;
        case 18: /* R */
            *command = 7;
            return;
        case 19:
            special(command, parameter);
            return;
        case 20: /* T: tempo */
            if (*parameter >= 0x20)
            {
                *command = 0xf;
                return;
            }
            break;
        case 21: /* U */
            *command = 0x1e;
            return;
        case 22: /* V */
            *command = 0x10;
            return;
        case 24: /* X: panning */
            *command = 8;
            if (*parameter > 0x80)
            {
                *parameter = 0x80;
            }
            else if (*parameter == 0x80)
            {
                *parameter = 0xff;
            }
            else
            {
                *parameter += *parameter;
            }
            return;
        case 26: /* Z */
            *command = 0x23;
            return;
        default:
            break;
    }
    *command = 0;
    *parameter = 0;
}

static uint32_t convert_note(uint32_t note)
{
    uint32_t value;
    if (note == NOTE_OFF)
    {
        return XM_NOTE_OFF;
    }
    if (note == NOTE_NONE)
    {
        return 0;
    }
    value = (note >> 4) * 12 + (note & LOW_NIBBLE) + 1;
    return value > XM_NOTE_LAST ? 0 : value;
}

static void clear(Convert *v, size_t offset, size_t count)
{
    for (size_t i = 0; i < count && v->ok; i++)
    {
        put(v, VERTRIX_S3M_ROW, offset + i, BYTE_WIDTH, 0);
    }
}

int vertrix_s3m_pattern(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        const VertrixGlobals *globals, uint32_t channels, uint32_t source,
                        uint32_t length, uint32_t map, uint32_t record, uint32_t *result)
{
    Convert v = {calls, services, globals, 1};
    uint32_t base, out, ecx = map, size, reallocated;
    uint32_t end = source + length;
    uint32_t cursor = source;
    put(&v, record, RECORD_ZERO, WORD_WIDTH, 0);
    put(&v, record, RECORD_CHANNELS, WORD_WIDTH, channels & WORD_MASK);
    put(&v, record, RECORD_ROWS, WORD_WIDTH, ROWS);
    put(&v, record, RECORD_SIZE, WORD_WIDTH, 0);
    if (!v.ok)
    {
        return 0;
    }
    base = vertrix_call(calls, ALLOCATE, channels * BYTES_PER_CHANNEL, channels, length, map, 0);
    put(&v, record, RECORD_POINTER, DWORD_WIDTH, base);
    if (!v.ok)
    {
        return 0;
    }
    if (base == 0)
    {
        *result = FAILURE;
        return 1;
    }
    out = base;
    clear(&v, MEMORY, MEMORY_BYTES);
    for (uint32_t row = 0; row < ROWS && v.ok; row++)
    {
        clear(&v, 0, ROW_BYTES);
        while (cursor < end && v.ok)
        {
            uint32_t flag = get(&v, source, cursor++ - source, BYTE_WIDTH);
            uint32_t note = NOTE_NONE, instrument = 0, volume = VOLUME_NONE;
            uint32_t command = 0, channel;
            if (flag == 0)
            {
                break;
            }
            ecx = 0;
            if (flag & HAS_NOTE)
            {
                note = get(&v, source, cursor++ - source, BYTE_WIDTH);
                instrument = get(&v, source, cursor++ - source, BYTE_WIDTH);
            }
            if (flag & HAS_VOLUME)
            {
                volume = get(&v, source, cursor++ - source, BYTE_WIDTH);
            }
            if (flag & HAS_COMMAND)
            {
                command = get(&v, source, cursor++ - source, BYTE_WIDTH);
                ecx = get(&v, source, cursor++ - source, BYTE_WIDTH);
            }
            channel = get(&v, map, flag & CHANNEL_MASK, BYTE_WIDTH);
            if (channel >= channels)
            {
                continue;
            }
            note = convert_note(note);
            if (ecx != 0)
            {
                put(&v, VERTRIX_S3M_ROW, MEMORY + channel, BYTE_WIDTH, ecx);
            }
            else if (remembered(command))
            {
                ecx = get(&v, VERTRIX_S3M_ROW, MEMORY + channel, BYTE_WIDTH);
            }
            if (command <= 26)
            {
                translate(&command, &ecx);
            }
            else
            {
                command = 0;
                ecx = 0;
            }
            if (note != 0)
            {
                put(&v, VERTRIX_S3M_ROW, channel * ROW_STRIDE, BYTE_WIDTH, note);
            }
            if (instrument != 0)
            {
                put(&v, VERTRIX_S3M_ROW, channel * ROW_STRIDE + 1, BYTE_WIDTH, instrument);
            }
            if (volume <= VOLUME_LIMIT)
            {
                put(&v, VERTRIX_S3M_ROW, channel * ROW_STRIDE + 2, BYTE_WIDTH,
                    volume + VOLUME_BIAS);
            }
            if ((command | ecx) != 0)
            {
                put(&v, VERTRIX_S3M_ROW, channel * ROW_STRIDE + 3, BYTE_WIDTH, command);
                put(&v, VERTRIX_S3M_ROW, channel * ROW_STRIDE + 4, BYTE_WIDTH, ecx);
            }
        }
        for (uint32_t channel = 0; channel < channels && v.ok; channel++)
        {
            uint32_t parts[5], flag = FLAG_BASE;
            static const uint8_t BITS[5] = {FLAG_NOTE, FLAG_INSTRUMENT, FLAG_VOLUME, FLAG_COMMAND,
                                            FLAG_PARAMETER};
            for (unsigned i = 0; i < 5; i++)
            {
                parts[i] = get(&v, VERTRIX_S3M_ROW, channel * ROW_STRIDE + i, BYTE_WIDTH);
                flag |= parts[i] != 0 ? BITS[i] : 0;
            }
            ecx = parts[4];
            put(&v, base, out++ - base, BYTE_WIDTH, flag);
            for (unsigned i = 0; i < 5; i++)
            {
                if (parts[i] != 0)
                {
                    put(&v, base, out++ - base, BYTE_WIDTH, parts[i]);
                }
            }
        }
    }
    if (!v.ok)
    {
        return 0;
    }
    size = (out - base) & WORD_MASK;
    put(&v, record, RECORD_SIZE, WORD_WIDTH, size);
    base = get(&v, record, RECORD_POINTER, DWORD_WIDTH);
    if (!v.ok)
    {
        return 0;
    }
    reallocated = vertrix_call(calls, REALLOC, base, size, ROWS, ecx, 0);
    put(&v, record, RECORD_POINTER, DWORD_WIDTH, reallocated);
    if (!v.ok)
    {
        return 0;
    }
    *result = reallocated == 0 ? FAILURE : 0;
    return 1;
}
