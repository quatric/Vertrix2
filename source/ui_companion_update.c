#include "ui_companion_update.h"
#include <string.h>

int vertrix_ui_companion_storage_update_list(void *storage, size_t size,
                                             const VertrixObjectList *list,
                                             VertrixActorStorageResolve resolve, void *context,
                                             int16_t start_y, uint32_t elapsed,
                                             uint32_t *refresh_words, size_t refresh_count)
{
    int present;
    uint32_t value, state;
    if (!vertrix_actor_linked_values(storage, size, list, resolve, context, &present, &value,
                                     &state))
    {
        return 0;
    }
    return vertrix_ui_companion_storage_update(storage, size, present, value, state, start_y,
                                               elapsed, refresh_words, refresh_count);
}

typedef struct
{
    size_t native;
    uint16_t original;
    uint8_t width;
} MovementField;

#define FIELD(member, original, width) {offsetof(VertrixLinkedMovement, member), original, width}

static const MovementField fields[] = {FIELD(threshold, 0x58, 4),
                                       FIELD(source, 0x134, 4),
                                       FIELD(active, 0x124, 4),
                                       FIELD(refresh, 0x120, 4),
                                       FIELD(handler, 0x154, 4),
                                       FIELD(origin_y, 0xa, 2),
                                       FIELD(y, 0x16, 2),
                                       FIELD(target_y, 0x18, 2),
                                       FIELD(step_y, 0x1a, 2),
                                       FIELD(refresh_index, 0x148, 2),
                                       FIELD(primary.counter, 0xbc, 4),
                                       FIELD(primary.period, 0xc0, 4),
                                       FIELD(secondary.counter, 0xdc, 4),
                                       FIELD(secondary.period, 0xe0, 4)};

#undef FIELD

int vertrix_ui_companion_storage_update(void *storage, size_t size, int linked_present,
                                        uint32_t linked_value, uint32_t linked_state,
                                        int16_t start_y, uint32_t elapsed, uint32_t *refresh_words,
                                        size_t refresh_count)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE)
    {
        return 0;
    }
    VertrixLinkedMovement movement = {0};
    uint8_t *native = (uint8_t *)&movement;
    for (size_t i = 0; i < sizeof(fields) / sizeof(fields[0]); i++)
    {
        uint32_t value;
        vertrix_actor_storage_read(storage, size, fields[i].original, fields[i].width, &value);
        if (fields[i].width == 2)
        {
            int16_t word = (int16_t)(value < 32768 ? (int32_t)value : (int32_t)value - 65536);
            memcpy(native + fields[i].native, &word, sizeof(word));
        }
        else
        {
            memcpy(native + fields[i].native, &value, sizeof(value));
        }
    }
    if (!vertrix_linked_movement_update(&movement, linked_present, linked_value, linked_state,
                                        start_y, elapsed, refresh_words, refresh_count))
    {
        return 0;
    }
    for (size_t i = 0; i < sizeof(fields) / sizeof(fields[0]); i++)
    {
        uint32_t value;
        if (fields[i].width == 2)
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
