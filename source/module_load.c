#include "module_load.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    BYTE_WIDTH = 1,
    OPEN = 0x40c1c0,
    SELECT = 0x40c1f0,
    ALLOCATE = 0x4ec160,
    CLOSE = 0x40c1e0,
    READ = 0x40c220,
    READ_WORD = 0x40c360,
    READ_BYTE = 0x40c320,
    FREE = 0x40ef90,
    EVENT_PACK = 0x40f1a0,
    BUFFER = 0x40ac50,
    REGISTER = 0x40acd0,
    MODULE_SIZE = 0x158,
    TITLE_SIZE = 0x14,
    SAMPLES = 0x1f,
    HEADER_SIZE = 30,
    NAME_SIZE = 0x16,
    SCRATCH_TITLE = 0,
    SCRATCH_SAMPLES = 0x14,
    SCRATCH_LENGTH = 0x3b6,
    SCRATCH_RESTART = 0x3b7,
    SCRATCH_PATTERNS = 0x3b8,
    SCRATCH_SIGNATURE = 0x438,
    SCRATCH_COPY = 0x43c,
    PATTERN_ENTRIES = 0x80,
    SIGNATURE_SIZE = 4,
    SIGNATURE_ENTRY = 8,
    SIGNATURE_COUNT = 20,
    COMPARE = 0x4ec180,
    COPY = 0x4eb5e0,
    FIELD_CHANNELS = 0x26,
    FIELD_PATTERNS = 0x28,
    FIELD_SAMPLES = 0x2a,
    FIELD_PATTERN_TABLE = 0x30,
    FIELD_CHANNEL_MARKS = 0x130,
    FIELD_PATTERN_ARRAY = 0x150,
    FIELD_SAMPLE_ARRAY = 0x154,
    PATTERN_SIZE = 12,
    SAMPLE_SIZE = 0xfc,
    SOUND_SIZE = 0x3c,
    ERROR_NO_MEMORY = 8,
    ERROR_OPEN = 0xa,
    ERROR_FORMAT = 0xb,
    ENTRY_FLAG = 0x80,
    ENTRY_SOUND = 0xf8,
    MAX_VOLUME = 0x40
};

typedef struct Module
{
    const VertrixFactoryServices *services;
    int ok;
} Module;

static uint32_t get(Module *m, uint32_t handle, size_t offset, unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!m->services->resolve(handle, &storage, &size, m->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, width, &value))
    {
        m->ok = 0;
    }
    return value;
}

static void put(Module *m, uint32_t handle, size_t offset, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!m->services->resolve(handle, &storage, &size, m->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, width, value))
    {
        m->ok = 0;
    }
}

static uint32_t scratch_get(Module *m, size_t offset, unsigned width)
{
    return get(m, VERTRIX_MODULE_SCRATCH, offset, width);
}

/* 0x4eb860: copy up to count bytes of a text, stopping at a zero, then pad with zeros. */
static void copy_text(Module *m, uint32_t destination, size_t destination_offset, size_t source,
                      uint32_t count)
{
    uint32_t i = 0;
    while (i < count && m->ok)
    {
        uint32_t value = scratch_get(m, source + i, BYTE_WIDTH);
        if (value == 0)
        {
            break;
        }
        put(m, destination, destination_offset + i, BYTE_WIDTH, value);
        i++;
    }
    for (; i < count && m->ok; i++)
    {
        put(m, destination, destination_offset + i, BYTE_WIDTH, 0);
    }
}

static int fail(const VertrixCalls *calls, uint32_t module, uint32_t edx, uint32_t ebx,
                uint32_t ecx, uint32_t *result, uint32_t code)
{
    uint32_t answer = vertrix_call(calls, FREE, module, edx, ebx, ecx, 0);
    vertrix_call(calls, CLOSE, answer, edx, ebx, ecx, 0);
    *result = code;
    return 1;
}

int vertrix_module_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                        uint32_t eax, uint32_t stream, uint32_t result_pointer, uint32_t ecx,
                        uint32_t *result)
{
    Module module = {services, 1};
    Module *m = &module;
    uint32_t object, i, j, edx, ebx, channels, patterns, array, samples, answer;
    uint32_t signature_edx = 0, signature_ecx = 0;
    if (vertrix_call(calls, OPEN, eax, result_pointer, stream, ecx, 0) != 0)
    {
        *result = ERROR_OPEN;
        return 1;
    }
    vertrix_call(calls, SELECT, stream, 0, stream, ecx, 0);
    object = vertrix_call(calls, ALLOCATE, 1, MODULE_SIZE, stream, ecx, 0);
    if (object == 0)
    {
        vertrix_call(calls, CLOSE, 0, MODULE_SIZE, stream, ecx, 0);
        *result = ERROR_NO_MEMORY;
        return 1;
    }
    vertrix_call(calls, READ, VERTRIX_MODULE_SCRATCH, TITLE_SIZE, stream, ecx, 0);
    ebx = stream;
    for (i = 0; i < SAMPLES; i++)
    {
        uint32_t entry = VERTRIX_MODULE_SCRATCH + SCRATCH_SAMPLES + HEADER_SIZE * i;
        ebx = entry;
        vertrix_call(calls, READ, entry, NAME_SIZE, ebx, i, 0);
        vertrix_call(calls, READ_WORD, entry + NAME_SIZE, NAME_SIZE, ebx, i, 0);
        vertrix_call(calls, READ_BYTE, entry + 0x18, NAME_SIZE, ebx, i, 0);
        vertrix_call(calls, READ_BYTE, entry + 0x19, NAME_SIZE, ebx, i, 0);
        vertrix_call(calls, READ_WORD, entry + 0x1a, NAME_SIZE, ebx, i, 0);
        vertrix_call(calls, READ_WORD, entry + 0x1c, NAME_SIZE, ebx, i, 0);
    }
    ecx = SAMPLES;
    vertrix_call(calls, READ_BYTE, VERTRIX_MODULE_SCRATCH + SCRATCH_LENGTH, NAME_SIZE, ebx, ecx, 0);
    vertrix_call(calls, READ_BYTE, VERTRIX_MODULE_SCRATCH + SCRATCH_RESTART, NAME_SIZE, ebx, ecx,
                 0);
    vertrix_call(calls, READ, VERTRIX_MODULE_SCRATCH + SCRATCH_PATTERNS, PATTERN_ENTRIES, ebx, ecx,
                 0);
    vertrix_call(calls, READ, VERTRIX_MODULE_SCRATCH + SCRATCH_SIGNATURE, SIGNATURE_SIZE, ebx, ecx,
                 0);
    for (i = 0; m->ok && i < SIGNATURE_COUNT; i++)
    {
        signature_edx = VERTRIX_MODULE_SIGNATURES + SIGNATURE_ENTRY * i;
        signature_ecx = i;
        if (vertrix_call(calls, COMPARE, VERTRIX_MODULE_SCRATCH + SCRATCH_SIGNATURE, signature_edx,
                         SIGNATURE_SIZE, i, 0) == 0)
        {
            put(m, object, FIELD_CHANNELS, WORD_WIDTH,
                get(m, VERTRIX_MODULE_SIGNATURES, SIGNATURE_ENTRY * i + SIGNATURE_SIZE,
                    WORD_WIDTH));
            break;
        }
    }
    if (i == SIGNATURE_COUNT)
    {
        signature_ecx = SIGNATURE_COUNT;
    }
    if (get(m, object, FIELD_CHANNELS, WORD_WIDTH) == 0)
    {
        return fail(calls, object, signature_edx, SIGNATURE_SIZE, signature_ecx, result,
                    ERROR_FORMAT) &&
               m->ok;
    }
    copy_text(m, object, 0, SCRATCH_TITLE, TITLE_SIZE);
    put(m, object, 0x20, WORD_WIDTH, 0x8000);
    put(m, object, 0x22, WORD_WIDTH, scratch_get(m, SCRATCH_LENGTH, BYTE_WIDTH));
    put(m, object, 0x24, WORD_WIDTH, scratch_get(m, SCRATCH_RESTART, BYTE_WIDTH));
    put(m, object, FIELD_SAMPLES, WORD_WIDTH, SAMPLES);
    put(m, object, 0x2c, WORD_WIDTH, 6);
    put(m, object, 0x2e, WORD_WIDTH, 0x7d);
    for (j = 0; m->ok && j < PATTERN_ENTRIES; j++)
    {
        uint32_t value = scratch_get(m, SCRATCH_PATTERNS + j, BYTE_WIDTH);
        put(m, object, FIELD_PATTERN_TABLE + j, BYTE_WIDTH, value);
        if ((int32_t)get(m, object, FIELD_PATTERNS, WORD_WIDTH) < (int32_t)value)
        {
            put(m, object, FIELD_PATTERNS, WORD_WIDTH, value);
        }
    }
    put(m, object, FIELD_PATTERNS, WORD_WIDTH, get(m, object, FIELD_PATTERNS, WORD_WIDTH) + 1);
    channels = get(m, object, FIELD_CHANNELS, WORD_WIDTH);
    for (j = 0; m->ok && j < channels; j++)
    {
        put(m, object, FIELD_CHANNEL_MARKS + j, BYTE_WIDTH,
            (j & 3) == 0 || (j & 3) == 3 ? 0 : 0xff);
    }
    ecx = channels;
    patterns = get(m, object, FIELD_PATTERNS, WORD_WIDTH);
    array = vertrix_call(calls, ALLOCATE, patterns, PATTERN_SIZE, 0, ecx, 0);
    put(m, object, FIELD_PATTERN_ARRAY, DWORD_WIDTH, array);
    if (array == 0)
    {
        return fail(calls, object, PATTERN_SIZE, 0, ecx, result, ERROR_NO_MEMORY) && m->ok;
    }
    samples = vertrix_call(calls, ALLOCATE, get(m, object, FIELD_SAMPLES, WORD_WIDTH), SAMPLE_SIZE,
                           0, ecx, 0);
    put(m, object, FIELD_SAMPLE_ARRAY, DWORD_WIDTH, samples);
    if (samples == 0)
    {
        return fail(calls, object, SAMPLE_SIZE, 0, ecx, result, ERROR_NO_MEMORY) && m->ok;
    }
    edx = SAMPLE_SIZE;
    array = get(m, object, FIELD_PATTERN_ARRAY, DWORD_WIDTH);
    for (i = 0; m->ok && i < get(m, object, FIELD_PATTERNS, WORD_WIDTH); i++)
    {
        answer = vertrix_call(calls, EVENT_PACK, get(m, object, FIELD_CHANNELS, WORD_WIDTH), array,
                              0, i, 0);
        edx = answer;
        if (answer != 0)
        {
            return fail(calls, object, answer, 0, i, result, answer) && m->ok;
        }
        array += PATTERN_SIZE;
    }
    ebx = 0;
    samples = get(m, object, FIELD_SAMPLE_ARRAY, DWORD_WIDTH);
    for (i = 0; m->ok && i < get(m, object, FIELD_SAMPLES, WORD_WIDTH); i++)
    {
        uint32_t sound, length, start, repeat, volume, value, size;
        uint32_t index = SAMPLE_SIZE * i;
        vertrix_call(calls, COPY, VERTRIX_MODULE_SCRATCH + SCRATCH_COPY,
                     VERTRIX_MODULE_SCRATCH + SCRATCH_SAMPLES + HEADER_SIZE * i, HEADER_SIZE, i, 0);
        copy_text(m, samples, index, SCRATCH_COPY, NAME_SIZE);
        edx = 0;
        ebx = 0;
        length = scratch_get(m, SCRATCH_COPY + NAME_SIZE, WORD_WIDTH);
        if (length == 0)
        {
            continue;
        }
        sound = vertrix_call(calls, ALLOCATE, 1, SOUND_SIZE, 0, i, 0);
        edx = SOUND_SIZE;
        ebx = sound;
        if (sound == 0)
        {
            return fail(calls, object, edx, ebx, i, result, ERROR_NO_MEMORY) && m->ok;
        }
        put(m, samples, index + ENTRY_FLAG, WORD_WIDTH, 1);
        put(m, samples, index + ENTRY_SOUND, DWORD_WIDTH, sound);
        put(m, sound, 0x3a, WORD_WIDTH, 0);
        edx = length * 2;
        put(m, sound, 0x2c, DWORD_WIDTH, edx);
        put(m, sound, 0x38, WORD_WIDTH, 0x20ab);
        start = scratch_get(m, SCRATCH_COPY + 0x1a, WORD_WIDTH);
        repeat = scratch_get(m, SCRATCH_COPY + 0x1c, WORD_WIDTH);
        if (repeat > 1)
        {
            edx = start;
            if (start < length)
            {
                put(m, sound, 0x3a, BYTE_WIDTH, get(m, sound, 0x3a, BYTE_WIDTH) | 0x10);
                put(m, sound, 0x30, DWORD_WIDTH, start * 2);
                put(m, sound, 0x34, DWORD_WIDTH, start * 2);
                put(m, sound, 0x34, DWORD_WIDTH, get(m, sound, 0x34, DWORD_WIDTH) + repeat * 2);
                edx = get(m, sound, 0x34, DWORD_WIDTH);
                if (edx > get(m, sound, 0x2c, DWORD_WIDTH))
                {
                    edx = get(m, sound, 0x2c, DWORD_WIDTH);
                    put(m, sound, 0x34, DWORD_WIDTH, edx);
                }
            }
        }
        volume = scratch_get(m, SCRATCH_COPY + 0x19, BYTE_WIDTH);
        edx = (edx & 0xffff00ffu) | (volume << 8);
        put(m, sound, 0x20, BYTE_WIDTH, volume > MAX_VOLUME ? MAX_VOLUME : volume);
        value = scratch_get(m, SCRATCH_COPY + 0x18, BYTE_WIDTH);
        put(m, sound, 0x23, BYTE_WIDTH, (value & 0xf) << 4);
        put(m, sound, 0x21, BYTE_WIDTH, 0x80);
        answer = vertrix_call(calls, BUFFER, sound + 0x24, edx, ebx, i, 0);
        if (answer != 0)
        {
            return fail(calls, object, answer, ebx, i, result, answer) && m->ok;
        }
        size = get(m, sound, 0x2c, DWORD_WIDTH);
        vertrix_call(calls, READ, get(m, sound, 0x24, DWORD_WIDTH), size, ebx, i, 0);
        edx = 0;
        ebx = size;
        vertrix_call(calls, REGISTER, sound + 0x24, 0, ebx, i, 0);
    }
    vertrix_call(calls, CLOSE, get(m, object, FIELD_SAMPLES, WORD_WIDTH), edx, ebx, i, 0);
    put(m, result_pointer, 0, DWORD_WIDTH, object);
    *result = 0;
    return m->ok;
}
