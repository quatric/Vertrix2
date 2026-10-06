#include "wave_load.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    BYTE_WIDTH = 1,
    OFFSET_RIFF = 0,
    OFFSET_SIZE = 4,
    OFFSET_FORM = 8,
    OFFSET_CHUNK = 0x10,
    OFFSET_CHUNK_SIZE = 0x14,
    OFFSET_TAG = 0x18,
    OFFSET_CHANNELS = 0x1a,
    OFFSET_RATE = 0x1c,
    OFFSET_BYTE_RATE = 0x20,
    OFFSET_ALIGNMENT = 0x24,
    OFFSET_BITS = 0x26,
    CLEARED_SIZE = 0x10,
    ID_RIFF = 0x46464952,
    ID_WAVE = 0x45564157,
    ID_FORMAT = 0x20746d66,
    ID_DATA = 0x61746164,
    TAG_PCM = 1,
    BITS_EIGHT = 8,
    ALLOCATE = 0x4ec160,
    READ = 0x48a930,
    SKIP = 0x48aa90,
    RELEASE = 0x4b8170,
    BUFFER = 0x40ac50,
    REGISTER = 0x40acd0,
    ALLOCATE_FLAGS = 1,
    OBJECT_SIZE = 0x18,
    HEADER_SIZE = 4,
    FORMAT_HEADER = 0x10,
    FIELD_BUFFER = 0,
    FIELD_SIZE = 8,
    FIELD_RATE = 0x14,
    FIELD_FLAGS = 0x16,
    FIELD_STEREO = 0x17,
    SIGN_FLIP = 0x80,
    ERROR_NO_POINTER = 2,
    ERROR_NO_MEMORY = 8,
    ERROR_FORMAT = 0xb
};

typedef struct Wave
{
    const VertrixFactoryServices *services;
    int ok;
} Wave;

static uint32_t get(Wave *w, uint32_t handle, size_t offset, unsigned width)
{
    void *storage;
    size_t size;
    uint32_t value = 0;
    if (!w->services->resolve(handle, &storage, &size, w->services->context) ||
        !vertrix_actor_storage_read(storage, size, offset, width, &value))
    {
        w->ok = 0;
    }
    return value;
}

static void put(Wave *w, uint32_t handle, size_t offset, unsigned width, uint32_t value)
{
    void *storage;
    size_t size;
    if (!w->services->resolve(handle, &storage, &size, w->services->context) ||
        !vertrix_actor_storage_write(storage, size, offset, width, value))
    {
        w->ok = 0;
    }
}

static uint32_t state_get(Wave *w, size_t offset, unsigned width)
{
    return get(w, VERTRIX_WAVE_STATE, offset, width);
}

static void state_put(Wave *w, size_t offset, unsigned width, uint32_t value)
{
    put(w, VERTRIX_WAVE_STATE, offset, width, value);
}

static uint32_t read_into(const VertrixCalls *calls, uint32_t stream, size_t offset, uint32_t count)
{
    return vertrix_call(calls, READ, stream, VERTRIX_WAVE_STATE + (uint32_t)offset, 1, count, 0);
}

int vertrix_wave_load(const VertrixCalls *calls, const VertrixFactoryServices *services,
                      uint32_t stream, uint32_t result_pointer, uint32_t ebx, uint32_t ecx,
                      uint32_t *result)
{
    Wave wave = {services, 1};
    Wave *w = &wave;
    uint32_t object, rounded, remaining, id, error, count, i;
    uint32_t edx = 0;
    *result = ERROR_NO_POINTER;
    if (result_pointer == 0)
    {
        return 1;
    }
    put(w, result_pointer, 0, DWORD_WIDTH, 0);
    object = vertrix_call(calls, ALLOCATE, ALLOCATE_FLAGS, OBJECT_SIZE, ebx, ecx, 0);
    if (object == 0)
    {
        *result = ERROR_NO_MEMORY;
        return w->ok;
    }
    read_into(calls, stream, OFFSET_RIFF, HEADER_SIZE);
    read_into(calls, stream, OFFSET_SIZE, HEADER_SIZE);
    read_into(calls, stream, OFFSET_FORM, HEADER_SIZE);
    remaining = state_get(w, OFFSET_SIZE, DWORD_WIDTH);
    remaining += remaining & 1;
    state_put(w, OFFSET_SIZE, DWORD_WIDTH, remaining);
    id = state_get(w, OFFSET_RIFF, DWORD_WIDTH);
    ecx = remaining;
    ebx = id;
    edx = VERTRIX_WAVE_STATE + OFFSET_FORM;
    if (id != ID_RIFF || state_get(w, OFFSET_FORM, DWORD_WIDTH) != ID_WAVE)
    {
        vertrix_call(calls, RELEASE, object, edx, ebx, ecx, 0);
        *result = ERROR_FORMAT;
        return w->ok;
    }
    for (i = 0; i < CLEARED_SIZE; i += DWORD_WIDTH)
    {
        state_put(w, OFFSET_TAG + i, DWORD_WIDTH, 0);
    }
    remaining -= HEADER_SIZE;
    state_put(w, OFFSET_SIZE, DWORD_WIDTH, remaining);
    while (w->ok && remaining != 0)
    {
        read_into(calls, stream, OFFSET_CHUNK, HEADER_SIZE);
        read_into(calls, stream, OFFSET_CHUNK_SIZE, HEADER_SIZE);
        rounded = state_get(w, OFFSET_CHUNK_SIZE, DWORD_WIDTH);
        rounded += rounded & 1;
        remaining = state_get(w, OFFSET_SIZE, DWORD_WIDTH);
        state_put(w, OFFSET_CHUNK_SIZE, DWORD_WIDTH, rounded);
        remaining -= rounded + 2 * HEADER_SIZE;
        state_put(w, OFFSET_SIZE, DWORD_WIDTH, remaining);
        id = state_get(w, OFFSET_CHUNK, DWORD_WIDTH);
        ebx = id;
        ecx = remaining;
        edx = rounded;
        if (id == ID_FORMAT)
        {
            read_into(calls, stream, OFFSET_TAG, WORD_WIDTH);
            read_into(calls, stream, OFFSET_CHANNELS, WORD_WIDTH);
            read_into(calls, stream, OFFSET_RATE, DWORD_WIDTH);
            read_into(calls, stream, OFFSET_BYTE_RATE, DWORD_WIDTH);
            read_into(calls, stream, OFFSET_ALIGNMENT, WORD_WIDTH);
            read_into(calls, stream, OFFSET_BITS, WORD_WIDTH);
            vertrix_call(calls, SKIP, stream, rounded - FORMAT_HEADER, 1, WORD_WIDTH, 0);
        }
        else if (id == ID_DATA)
        {
            uint32_t flags;
            if (state_get(w, OFFSET_TAG, WORD_WIDTH) != TAG_PCM)
            {
                vertrix_call(calls, RELEASE, object, edx, ebx, ecx, 0);
                *result = ERROR_FORMAT;
                return w->ok;
            }
            put(w, object, FIELD_SIZE, DWORD_WIDTH, rounded);
            put(w, object, FIELD_FLAGS, WORD_WIDTH, 0);
            put(w, object, FIELD_RATE, WORD_WIDTH, state_get(w, OFFSET_RATE, WORD_WIDTH));
            flags = get(w, object, FIELD_FLAGS, BYTE_WIDTH);
            if (state_get(w, OFFSET_BITS, WORD_WIDTH) != BITS_EIGHT)
            {
                put(w, object, FIELD_FLAGS, BYTE_WIDTH, flags | 1);
            }
            if (state_get(w, OFFSET_CHANNELS, WORD_WIDTH) != 1)
            {
                put(w, object, FIELD_STEREO, BYTE_WIDTH,
                    get(w, object, FIELD_STEREO, BYTE_WIDTH) | 1);
            }
            error = vertrix_call(calls, BUFFER, object, edx, ebx, ecx, 0);
            if (error != 0)
            {
                vertrix_call(calls, RELEASE, object, error, ebx, ecx, 0);
                *result = error;
                return w->ok;
            }
            count = get(w, object, FIELD_SIZE, DWORD_WIDTH);
            vertrix_call(calls, READ, stream, get(w, object, FIELD_BUFFER, DWORD_WIDTH), 1, count,
                         0);
            if ((get(w, object, FIELD_FLAGS, BYTE_WIDTH) & 1) == 0)
            {
                uint32_t buffer = get(w, object, FIELD_BUFFER, DWORD_WIDTH);
                for (i = 0; w->ok && i < get(w, object, FIELD_SIZE, DWORD_WIDTH); i++)
                {
                    put(w, buffer, i, BYTE_WIDTH, get(w, buffer, i, BYTE_WIDTH) ^ SIGN_FLIP);
                }
            }
            vertrix_call(calls, REGISTER, object, 0, get(w, object, FIELD_SIZE, DWORD_WIDTH), count,
                         0);
            put(w, result_pointer, 0, DWORD_WIDTH, object);
            put(w, VERTRIX_WAVE_TOTAL, 0, DWORD_WIDTH,
                get(w, VERTRIX_WAVE_TOTAL, 0, DWORD_WIDTH) +
                    get(w, object, FIELD_SIZE, DWORD_WIDTH));
            *result = 0;
            return w->ok;
        }
        else
        {
            vertrix_call(calls, SKIP, stream, rounded, ebx, ecx, 0);
        }
        remaining = state_get(w, OFFSET_SIZE, DWORD_WIDTH);
    }
    *result = ERROR_FORMAT;
    return w->ok;
}
