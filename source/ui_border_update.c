#include "ui_border_update.h"
#include "linked_burst.h"
#include <string.h>

typedef struct
{
    size_t native;
    size_t original;
    unsigned width;
} BurstField;

#define FIELD(member, original, width) {offsetof(VertrixLinkedBurst, member), original, width}
static const BurstField fields[] = {
    FIELD(repetitions, 0x58, 4),   FIELD(source, 0x134, 4),      FIELD(handler, 0x154, 4),
    FIELD(effect, 0x48, 2),        FIELD(target, 0x4a, 2),       FIELD(step, 0x4c, 2),
    FIELD(delay, 0x70, 4),         FIELD(delay_target, 0x74, 4), FIELD(delay_step, 0x78, 4),
    FIELD(timer.counter, 0xbc, 4), FIELD(timer.period, 0xc0, 4)};
#undef FIELD

int vertrix_ui_border_storage_update(void *storage, size_t size, int linked_present,
                                     uint32_t linked_value, uint32_t elapsed, VertrixRandom *random)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || !random)
    {
        return 0;
    }
    VertrixLinkedBurst burst = {0};
    uint8_t *native = (uint8_t *)&burst;
    for (size_t i = 0; i < sizeof(fields) / sizeof(fields[0]); ++i)
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
    if (!vertrix_linked_burst_update(&burst, linked_present, linked_value, elapsed, random))
    {
        return 0;
    }
    for (size_t i = 0; i < sizeof(fields) / sizeof(fields[0]); ++i)
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

int vertrix_ui_border_storage_update_list(void *storage, size_t size, const VertrixObjectList *list,
                                          VertrixActorStorageResolve resolve, void *context,
                                          uint32_t elapsed, VertrixRandom *random)
{
    int present;
    uint32_t value, state;
    if (!vertrix_actor_linked_values(storage, size, list, resolve, context, &present, &value,
                                     &state))
    {
        return 0;
    }
    return vertrix_ui_border_storage_update(storage, size, present, value, elapsed, random);
}
