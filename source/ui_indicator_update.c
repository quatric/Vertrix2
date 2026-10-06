#include "ui_indicator_update.h"
#include "linked_indicator.h"
#include <string.h>

typedef struct
{
    size_t native;
    size_t original;
    unsigned width;
} IndicatorField;

#define FIELD(member, original, width)                                                             \
    {                                                                                              \
        offsetof(VertrixLinkedIndicator, member), original, width                                  \
    }
static const IndicatorField fields[] = {
    FIELD(threshold, 0x58, 4),     FIELD(source, 0x134, 4),      FIELD(handler, 0x154, 4),
    FIELD(timer.counter, 0xbc, 4), FIELD(timer.period, 0xc0, 4), FIELD(amount, 0x4e, 1),
    FIELD(target, 0x4f, 1),        FIELD(stage, 0x52, 1),        FIELD(step, 0x50, 2)};
#undef FIELD

int vertrix_ui_indicator_storage_update(void *storage, size_t size, int linked_present,
                                        uint32_t linked_value, uint32_t linked_state,
                                        uint32_t elapsed)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE)
    {
        return 0;
    }
    VertrixLinkedIndicator indicator = {0};
    uint8_t *native = (uint8_t *)&indicator;
    for (size_t i = 0; i < sizeof(fields) / sizeof(fields[0]); ++i)
    {
        uint32_t value;
        vertrix_actor_storage_read(storage, size, fields[i].original, fields[i].width, &value);
        if (fields[i].width == 1)
        {
            native[fields[i].native] = (uint8_t)value;
        }
        else if (fields[i].width == 2)
        {
            int16_t word = (int16_t)(value < 32768 ? (int32_t)value : (int32_t)value - 65536);
            memcpy(native + fields[i].native, &word, sizeof(word));
        }
        else
        {
            memcpy(native + fields[i].native, &value, sizeof(value));
        }
    }
    if (!vertrix_linked_indicator_update(&indicator, linked_present, linked_value, linked_state,
                                         elapsed))
    {
        return 0;
    }
    for (size_t i = 0; i < sizeof(fields) / sizeof(fields[0]); ++i)
    {
        uint32_t value;
        if (fields[i].width == 1)
        {
            value = native[fields[i].native];
        }
        else if (fields[i].width == 2)
        {
            int16_t word;
            memcpy(&word, native + fields[i].native, sizeof(word));
            value = (uint16_t)word;
        }
        else
        {
            memcpy(&value, native + fields[i].native, sizeof(value));
        }
        vertrix_actor_storage_write(storage, size, fields[i].original, fields[i].width, value);
    }
    return 1;
}

int vertrix_ui_indicator_storage_update_list(void *storage, size_t size,
                                             const VertrixObjectList *list,
                                             VertrixActorStorageResolve resolve, void *context,
                                             uint32_t elapsed)
{
    int present;
    uint32_t value, state;
    if (!vertrix_actor_linked_values(storage, size, list, resolve, context, &present, &value,
                                     &state))
    {
        return 0;
    }
    return vertrix_ui_indicator_storage_update(storage, size, present, value, state, elapsed);
}
