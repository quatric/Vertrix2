#include "settings_defaults.h"
#include "actor_storage.h"
#include <string.h>

enum
{
    PERCENT = 100,
    PERCENT_SHIFT = 6,
    KEY_COUNT = 9,
    KEYS_OFFSET = 0x1c,
    SCALE_FIRST_OFFSET = 0x30,
    SCALE_SECOND_OFFSET = 0x34,
    SCALED_FIRST_OFFSET = 0x54,
    SCALED_SECOND_OFFSET = 0x58,
    GLOBALS_OFFSET = 0x38,
    LIMITS_OFFSET = 0x5c,
    CLASS_OFFSET = 0x228
};

typedef struct
{
    size_t offset;
    uint32_t value;
} Dword;

typedef struct
{
    size_t offset;
    const char *text;
} Text;

static const uint16_t KEYS[KEY_COUNT] = {95, 96, 93, 98, 114, 115, 116, 117, 57};
static const uint32_t LIMITS[5] = {100000, 100000, 50000, 10000, 5000};
static const Dword NUMBERS[] = {{0x0, 2},
                                {0x4, 20},
                                {0x8, 1},
                                {0xc, 5},
                                {0x10, 0},
                                {0x14, 1},
                                {0x18, 200},
                                {SCALE_FIRST_OFFSET, 48},
                                {SCALE_SECOND_OFFSET, 64},
                                {0x48, 0},
                                {0x4c, 0},
                                {0x50, 0},
                                {0x84, 1},
                                {0x88, 5},
                                {0x8c, 0},
                                {0x90, 1},
                                {0x94, 0}};
static const Text TEXTS[] = {
    {0x70, "CED"}, {0x74, "D.T"},  {0x78, "ED"},     {0x7c, "BRT"},
    {0x80, "E.T"}, {0x98, "TEST"}, {0xfc, "PLAYER"}, {0x160, "000.000.000.000"},
    {0x1c4, ""}};

static uint32_t scaled(uint32_t value)
{
    return (value * PERCENT) >> PERCENT_SHIFT;
}

int vertrix_settings_defaults(void *storage, size_t size, const VertrixSettingsGlobals *globals)
{
    uint8_t *bytes = storage;
    if (!storage || size < VERTRIX_SETTINGS_SIZE ||
        !vertrix_actor_storage_write(storage, size, CLASS_OFFSET, 4, VERTRIX_SETTINGS_CLASS))
    {
        return 0;
    }
    for (size_t i = 0; i < sizeof(NUMBERS) / sizeof(NUMBERS[0]); ++i)
    {
        if (!vertrix_actor_storage_write(storage, size, NUMBERS[i].offset, 4, NUMBERS[i].value))
        {
            return 0;
        }
    }
    for (size_t i = 0; i < KEY_COUNT; ++i)
    {
        if (!vertrix_actor_storage_write(storage, size, KEYS_OFFSET + 2 * i, 2, KEYS[i]))
        {
            return 0;
        }
    }
    const uint32_t copied[4] = {globals->first, globals->second, globals->third, globals->fourth};
    for (size_t i = 0; i < 4; ++i)
    {
        if (!vertrix_actor_storage_write(storage, size, GLOBALS_OFFSET + 4 * i, 4, copied[i]))
        {
            return 0;
        }
    }
    for (size_t i = 0; i < 5; ++i)
    {
        if (!vertrix_actor_storage_write(storage, size, LIMITS_OFFSET + 4 * i, 4, LIMITS[i]))
        {
            return 0;
        }
    }
    if (!vertrix_actor_storage_write(storage, size, SCALED_FIRST_OFFSET, 4, scaled(48)) ||
        !vertrix_actor_storage_write(storage, size, SCALED_SECOND_OFFSET, 4, scaled(64)))
    {
        return 0;
    }
    for (size_t i = 0; i < sizeof(TEXTS) / sizeof(TEXTS[0]); ++i)
    {
        memcpy(bytes + TEXTS[i].offset, TEXTS[i].text, strlen(TEXTS[i].text) + 1);
    }
    return 1;
}
