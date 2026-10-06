#include "event_frame_draw.h"
#include "actor_storage.h"
#include "event_stack.h"
#include <string.h>

enum
{
    MIN_ITEM_SIZE = 0x28,
    ITEM_OFFSET_0 = 0x0,
    ITEM_OFFSET_4 = 0x4,
    ITEM_OFFSET_8 = 0x8,
    ITEM_OFFSET_FLAGS = 0x27,
    EVENT_STRUCT_SIZE = 0x2c
};

static int prepare_event(const void *item, size_t size, uint8_t event[EVENT_STRUCT_SIZE],
                         uint32_t *p_ecx, uint32_t *p_edi)
{
    if (!item || size < MIN_ITEM_SIZE)
    {
        return 0;
    }

    uint32_t val0 = 0, val4 = 0, val8 = 0, flags = 0;
    if (!vertrix_actor_storage_read(item, size, ITEM_OFFSET_0, 4, &val0) ||
        !vertrix_actor_storage_read(item, size, ITEM_OFFSET_4, 4, &val4) ||
        !vertrix_actor_storage_read(item, size, ITEM_OFFSET_8, 4, &val8) ||
        !vertrix_actor_storage_read(item, size, ITEM_OFFSET_FLAGS, 1, &flags))
    {
        return 0;
    }

    memset(event, 0, EVENT_STRUCT_SIZE);
    memcpy(event + 0x0, &val0, 4);
    memcpy(event + 0x4, &val4, 4);
    memcpy(event + 0x8, &val8, 4);
    uint8_t b_flags = (uint8_t)flags;
    event[0xc] = b_flags;

    /* 0x478cd0: map key index */
    uint32_t key = (uint32_t)(uint8_t)(b_flags << 3);
    vertrix_event_key_index(event, EVENT_STRUCT_SIZE, key);

    /* 0x478da0: scale fields */
    uint32_t scaled = val4 * (uint32_t)b_flags;
    memcpy(event + 0x14, &scaled, 4);
    vertrix_event_scale_fields(event, EVENT_STRUCT_SIZE);

    *p_ecx = val4;
    *p_edi = val8;
    return 1;
}

int vertrix_event_frame_draw_direct(const void *item, size_t size, uint32_t edx, uint32_t ebx,
                                    uint32_t ecx, VertrixDrawDirectCallback draw, void *context)
{
    if (!draw)
    {
        return 0;
    }

    uint8_t event[EVENT_STRUCT_SIZE];
    uint32_t item_ecx = 0, item_edi = 0;
    if (!prepare_event(item, size, event, &item_ecx, &item_edi))
    {
        return 0;
    }

    uint32_t stack[4] = {ebx, ecx, item_ecx, item_edi};
    draw(event, edx, 0, 0, stack, context);
    return 1;
}

int vertrix_event_frame_draw_blend(const void *item, size_t size, uint32_t edx, uint32_t ebx,
                                   uint32_t ecx, uint32_t extra, VertrixDrawBlendCallback blend,
                                   void *context)
{
    if (!blend)
    {
        return 0;
    }

    uint8_t event[EVENT_STRUCT_SIZE];
    uint32_t item_ecx = 0, item_edi = 0;
    if (!prepare_event(item, size, event, &item_ecx, &item_edi))
    {
        return 0;
    }

    uint32_t stack[5] = {ebx, ecx, item_ecx, item_edi, extra};
    blend(event, edx, 0, 0, stack, context);
    return 1;
}

int vertrix_event_frame_draw_scaled(const void *item, size_t size, uint32_t edx, uint32_t ebx,
                                    uint32_t ecx, const uint32_t args[5],
                                    VertrixDrawScaledCallback draw_scaled, void *context)
{
    if (!draw_scaled || !args)
    {
        return 0;
    }

    uint8_t event[EVENT_STRUCT_SIZE];
    uint32_t item_ecx = 0, item_edi = 0;
    if (!prepare_event(item, size, event, &item_ecx, &item_edi))
    {
        return 0;
    }

    uint32_t stack[5] = {ebx, ecx, args[2], args[3], args[4]};
    draw_scaled(event, edx, args[0], args[1], stack, context);
    return 1;
}
