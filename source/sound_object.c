#include "sound_object.h"
#include "guest_bytes.h"

enum
{
    SLOT_RELEASE = 2,
    SLOT_CHECK = 7,
    SLOT_STOP = 8,
    SIMPLE_VTABLE = 0x5165c4,
    BANK_VTABLE = 0x5166d4,
    SLIDER_VTABLE = 0x516804,
    SLIDER_DEFAULT = 200,
    RANGE_LIMIT = 0x1800000,
    BANK_ENTRIES_FIRST = 0x24,
    BANK_ENTRIES_LAST = 0xa0,
    BANK_COUNTERS = 0xa4,
    KEYS_STORAGE_SIZE = 0xcc,
    KEYS_MODE = 0xb4,
    KEYS_FIRST = 0xb8,
    KEY_MODE_PRIMARY = 0,
    KEY_MODE_ALTERNATE = 1
};

typedef struct
{
    size_t owner;
    size_t playing;
    size_t buffer;
    size_t secondary;
    size_t status;
    size_t size;
} ReleaseLayout;

static const ReleaseLayout PRIMARY_LAYOUT = {8, 4, 0x10, 0xc, 0, 0x14};
static const ReleaseLayout STREAM_LAYOUT = {4, 0x10, 0xc, 8, 0, 0x14};
static const ReleaseLayout LOOPED_LAYOUT = {8, 0xc, 0x30, 4, 0, 0x34};

int vertrix_sound_simple_clear(uint8_t *object, size_t size)
{
    if (!object || size < VERTRIX_SOUND_SIMPLE_SIZE)
    {
        return 0;
    }
    vertrix_guest_set32(object, 0x18, SIMPLE_VTABLE);
    vertrix_guest_set8(object, 0, 0);
    vertrix_guest_set32(object, 4, 0);
    vertrix_guest_set32(object, 8, 0);
    vertrix_guest_set32(object, 0xc, 0);
    vertrix_guest_set16(object, 0x10, 0);
    vertrix_guest_set32(object, 0x14, 0);
    return 1;
}

int vertrix_sound_simple_set(uint8_t *object, size_t size, uint8_t kind, uint32_t first,
                             uint32_t second, uint32_t third)
{
    if (!object || size < VERTRIX_SOUND_SIMPLE_SIZE)
    {
        return 0;
    }
    vertrix_guest_set16(object, 0x10, 0);
    vertrix_guest_set32(object, 0x14, 0);
    vertrix_guest_set8(object, 0, kind);
    vertrix_guest_set32(object, 4, first);
    vertrix_guest_set32(object, 8, second);
    vertrix_guest_set32(object, 0xc, third);
    return 1;
}

int vertrix_sound_bank_clear_tail(uint8_t *object, size_t size)
{
    if (!object || size < VERTRIX_SOUND_BANK_SIZE)
    {
        return 0;
    }
    for (size_t offset = BANK_COUNTERS; offset < BANK_COUNTERS + 16; offset += 4)
    {
        vertrix_guest_set32(object, offset, 0);
    }
    for (size_t offset = BANK_ENTRIES_FIRST; offset <= BANK_ENTRIES_LAST; offset += 4)
    {
        vertrix_guest_set32(object, offset, 0);
    }
    return 1;
}

int vertrix_sound_bank_clear(uint8_t *object, size_t size)
{
    if (!object || size < VERTRIX_SOUND_BANK_SIZE)
    {
        return 0;
    }
    vertrix_guest_set32(object, 0xcc, BANK_VTABLE);
    vertrix_guest_set8(object, 8, 0);
    static const uint8_t cleared[] = {4, 0x1c, 0x20, 0x14, 0x18, 0x10, 0xc};
    for (size_t i = 0; i < sizeof cleared; ++i)
    {
        vertrix_guest_set32(object, cleared[i], 0);
    }
    return vertrix_sound_bank_clear_tail(object, size);
}

int vertrix_sound_slider_clear(uint8_t *object, size_t size)
{
    if (!object || size < VERTRIX_SOUND_SLIDER_SIZE)
    {
        return 0;
    }
    vertrix_guest_set32(object, 0x74, SLIDER_VTABLE);
    vertrix_guest_set8(object, 8, 0);
    vertrix_guest_set32(object, 0xc, 0);
    vertrix_guest_set32(object, 0x44, SLIDER_DEFAULT);
    static const uint8_t words[] = {0x3c, 0x3e, 0x40, 0x42, 0x4c, 0x4e, 0x48, 0x4a};
    for (size_t i = 0; i < sizeof words; ++i)
    {
        vertrix_guest_set16(object, words[i], 0);
    }
    static const uint8_t dwords[] = {0x60, 0x64, 0x68, 0x6c, 0x70, 0x54, 0x58};
    for (size_t i = 0; i < sizeof dwords; ++i)
    {
        vertrix_guest_set32(object, dwords[i], 0);
    }
    static const uint8_t trailing[] = {0x5c, 0x5e, 0x50, 0x52};
    for (size_t i = 0; i < sizeof trailing; ++i)
    {
        vertrix_guest_set16(object, trailing[i], 0);
    }
    return 1;
}

int vertrix_sound_range_clear(uint8_t *object, size_t size)
{
    if (!object || size < VERTRIX_SOUND_RANGE_SIZE)
    {
        return 0;
    }
    vertrix_guest_set32(object, 0, 0);
    vertrix_guest_set32(object, 4, 0);
    vertrix_guest_set32(object, 8, RANGE_LIMIT);
    return 1;
}

int vertrix_sound_key_is_control(uint32_t key)
{
    uint16_t code = (uint16_t)key;
    return (code >= 0x70 && code <= 0x75) || (code >= 0xbe && code <= 0xc3);
}

int vertrix_sound_check_primary(uint8_t *object, size_t size, VertrixVirtualCall call,
                                void *context)
{
    if (!object || size < PRIMARY_LAYOUT.size)
    {
        return 0;
    }
    uint32_t buffer = vertrix_guest_get32(object, PRIMARY_LAYOUT.buffer);
    if (buffer && call(context, buffer, SLOT_CHECK, buffer) >= 0)
    {
        vertrix_guest_set32(object, PRIMARY_LAYOUT.playing, 1);
        return 1;
    }
    vertrix_guest_set32(object, PRIMARY_LAYOUT.playing, 0);
    return 0;
}

static int release_layout(const ReleaseLayout *layout, uint8_t *object, size_t size,
                          VertrixVirtualCall call, void *context)
{
    if (!object || size < layout->size)
    {
        return 0;
    }
    vertrix_guest_set32(object, layout->status, 0);
    if (vertrix_guest_get8(object, layout->owner) != 0)
    {
        return 1;
    }
    uint32_t buffer = vertrix_guest_get32(object, layout->buffer);
    if (buffer)
    {
        if (vertrix_guest_get32(object, layout->playing) == 1)
        {
            call(context, buffer, SLOT_STOP, buffer);
            vertrix_guest_set32(object, layout->playing, 0);
        }
        buffer = vertrix_guest_get32(object, layout->buffer);
        call(context, buffer, SLOT_RELEASE, buffer);
        vertrix_guest_set32(object, layout->buffer, 0);
    }
    uint32_t secondary = vertrix_guest_get32(object, layout->secondary);
    if (secondary)
    {
        call(context, secondary, SLOT_RELEASE, secondary);
        vertrix_guest_set32(object, layout->secondary, 0);
    }
    return 1;
}

int vertrix_sound_release_primary(uint8_t *object, size_t size, VertrixVirtualCall call,
                                  void *context)
{
    return release_layout(&PRIMARY_LAYOUT, object, size, call, context);
}

int vertrix_sound_release_stream(uint8_t *object, size_t size, VertrixVirtualCall call,
                                 void *context)
{
    return release_layout(&STREAM_LAYOUT, object, size, call, context);
}

int vertrix_sound_release_looped(uint8_t *object, size_t size, VertrixVirtualCall call,
                                 void *context)
{
    return release_layout(&LOOPED_LAYOUT, object, size, call, context);
}

static void select_keys(uint8_t *object, uint32_t mode)
{
    static const uint32_t primary[5] = {0x78, 0x79, 0x76, 0x77, 0x7a};
    static const uint32_t alternate[5] = {0x9c, 0x9d, 0x9a, 0x9b, 0x9e};
    const uint32_t *keys = mode == KEY_MODE_PRIMARY ? primary : alternate;
    if (mode != KEY_MODE_PRIMARY && mode != KEY_MODE_ALTERNATE)
    {
        return;
    }
    for (size_t i = 0; i < 5; ++i)
    {
        vertrix_guest_set32(object, KEYS_FIRST + 4 * i, keys[i]);
    }
}

uint32_t vertrix_sound_open_keys(uint8_t *object, size_t size, uint32_t handle, uint32_t mode,
                                 uint8_t flag, uint32_t argument, VertrixSoundBuilder build,
                                 void *context)
{
    if (!object || size < KEYS_STORAGE_SIZE)
    {
        return 0;
    }
    uint32_t result = 0;
    vertrix_guest_set32(object, KEYS_MODE, mode);
    if (flag == 0)
    {
        result = build(context, handle, argument);
    }
    vertrix_guest_set8(object, 8, flag);
    vertrix_guest_set32(object, 0, result);
    select_keys(object, mode);
    return result;
}

uint32_t vertrix_sound_open_stream(uint8_t *object, size_t size, uint32_t handle, uint8_t flag,
                                   uint32_t argument, VertrixSoundBuilder build, void *context)
{
    if (!object || size < 8)
    {
        return 0;
    }
    if (flag == 0)
    {
        build(context, handle, argument);
    }
    vertrix_guest_set32(object, 0, 1);
    vertrix_guest_set8(object, 4, flag);
    return 1;
}

uint32_t vertrix_sound_open_looped(uint8_t *object, size_t size, uint32_t handle, uint8_t flag,
                                   uint32_t argument, VertrixSoundBuilder build, void *context)
{
    if (!object || size < 9)
    {
        return 0;
    }
    uint32_t result = 0;
    if (flag == 0)
    {
        result = build(context, handle, argument);
    }
    vertrix_guest_set8(object, 8, flag);
    vertrix_guest_set32(object, 0, result);
    return result;
}
