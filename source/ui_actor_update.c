#include "ui_actor_update.h"
#include <string.h>

int vertrix_ui_actor_storage_update_list(void *storage, size_t size, const VertrixObjectList *list,
                                         VertrixActorStorageResolve resolve, void *context,
                                         int16_t start_y, uint32_t elapsed,
                                         const VertrixFrameResource *resource_one,
                                         const VertrixFrameResource *resource_other, size_t budget)
{
    int present;
    uint32_t value, state;
    if (!vertrix_actor_linked_values(storage, size, list, resolve, context, &present, &value,
                                     &state))
    {
        return 0;
    }
    return vertrix_ui_actor_storage_update(storage, size, present, value, state, start_y, elapsed,
                                           resource_one, resource_other, budget);
}

typedef struct
{
    size_t native;
    uint16_t original;
    uint8_t width;
} DisplayField;

#define FIELD(member, original, width) {offsetof(VertrixLinkedAlternating, member), original, width}

static const DisplayField fields[] = {FIELD(threshold, 0x58, 4),
                                      FIELD(source, 0x134, 4),
                                      FIELD(phase, 0x7c, 4),
                                      FIELD(handler, 0x154, 4),
                                      FIELD(descriptor, 0xb4, 4),
                                      FIELD(origin_y, 0xa, 2),
                                      FIELD(y, 0x16, 2),
                                      FIELD(target_y, 0x18, 2),
                                      FIELD(step_y, 0x1a, 2),
                                      FIELD(effect, 0x48, 2),
                                      FIELD(effect_target, 0x4a, 2),
                                      FIELD(effect_step, 0x4c, 2),
                                      FIELD(delay, 0x70, 4),
                                      FIELD(delay_target, 0x74, 4),
                                      FIELD(delay_step, 0x78, 4),
                                      FIELD(primary.counter, 0xbc, 4),
                                      FIELD(primary.period, 0xc0, 4),
                                      FIELD(secondary.counter, 0xdc, 4),
                                      FIELD(secondary.period, 0xe0, 4),
                                      FIELD(animation.timer.counter, 0xcc, 4),
                                      FIELD(animation.timer.period, 0xd0, 4),
                                      FIELD(animation.frame, 0xb8, 4)};

#undef FIELD

int vertrix_ui_actor_storage_update(void *storage, size_t size, int linked_present,
                                    uint32_t linked_value, uint32_t linked_state, int16_t start_y,
                                    uint32_t elapsed, const VertrixFrameResource *resource_one,
                                    const VertrixFrameResource *resource_other, size_t budget)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || !resource_one || !resource_other ||
        resource_one == resource_other)
    {
        return 0;
    }
    uint32_t token;
    vertrix_actor_storage_read(storage, size, 0xb0, 4, &token);
    if (token != 0x546618 && token != 0x546634)
    {
        return 0;
    }
    VertrixLinkedAlternating display = {0};
    display.resource = token == 0x546618 ? resource_one : resource_other;
    if (display.resource->count > UINT32_MAX)
    {
        return 0;
    }
    display.animation.frame_count = (uint32_t)display.resource->count;
    uint8_t *native = (uint8_t *)&display;
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
    if (!vertrix_linked_alternating_update(&display, linked_present, linked_value, linked_state,
                                           start_y, elapsed, resource_one, resource_other, budget))
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
    vertrix_actor_storage_write(storage, size, 0xb0, 4,
                                display.resource == resource_one ? 0x546618 : 0x546634);
    return 1;
}
