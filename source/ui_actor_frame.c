#include "ui_actor_frame.h"
#include "ui_border_update.h"
#include "ui_companion_update.h"
#include "ui_indicator_update.h"
#include <string.h>

int vertrix_ui_actor_frame_update(void *storage, size_t size, const VertrixObjectList *list,
                                  VertrixActorStorageResolve resolve, void *context,
                                  int clear_refresh, int16_t start_y, uint32_t elapsed,
                                  uint32_t *refresh_words, size_t refresh_count,
                                  const VertrixFrameResource *resource_one,
                                  const VertrixFrameResource *resource_other, size_t budget)
{
    return vertrix_ui_actor_frame_update_random(
        storage, size, list, resolve, context, clear_refresh, start_y, elapsed, refresh_words,
        refresh_count, resource_one, resource_other, budget, NULL);
}

int vertrix_ui_actor_frame_update_random(void *storage, size_t size, const VertrixObjectList *list,
                                         VertrixActorStorageResolve resolve, void *context,
                                         int clear_refresh, int16_t start_y, uint32_t elapsed,
                                         uint32_t *refresh_words, size_t refresh_count,
                                         const VertrixFrameResource *resource_one,
                                         const VertrixFrameResource *resource_other, size_t budget,
                                         VertrixRandom *random)
{
    uint32_t class_token;
    if (!vertrix_actor_storage_read(storage, size, 0x158, 4, &class_token) ||
        class_token != 0x517af4)
    {
        return 0;
    }
    return vertrix_ui_actor_base_frame_update_random(
        storage, size, list, resolve, context, clear_refresh, start_y, elapsed, refresh_words,
        refresh_count, resource_one, resource_other, budget, random);
}

int vertrix_ui_actor_base_frame_update_random(
    void *storage, size_t size, const VertrixObjectList *list, VertrixActorStorageResolve resolve,
    void *context, int clear_refresh, int16_t start_y, uint32_t elapsed, uint32_t *refresh_words,
    size_t refresh_count, const VertrixFrameResource *resource_one,
    const VertrixFrameResource *resource_other, size_t budget, VertrixRandom *random)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE)
    {
        return 0;
    }
    uint32_t interaction, child, handler;
    vertrix_actor_storage_read(storage, size, 0x104, 4, &interaction);
    vertrix_actor_storage_read(storage, size, 0x108, 4, &child);
    vertrix_actor_storage_read(storage, size, 0x154, 4, &handler);
    if (interaction || child)
    {
        return 0;
    }
    uint8_t next[VERTRIX_ACTOR_BASE_SIZE];
    memcpy(next, storage, sizeof(next));
    if (clear_refresh)
    {
        vertrix_actor_storage_write(next, sizeof(next), 0x120, 4, 0);
    }
    int success;
    switch (handler)
    {
        case 0:
            success = 1;
            break;
        case 0x450130:
        case 0x4501a0:
        case 0x450200:
        case 0x450270:
        case 0x450300:
            success = vertrix_ui_border_storage_update_list(next, sizeof(next), list, resolve,
                                                            context, elapsed, random);
            break;
        case 0x44ff90:
        case 0x44fff0:
        case 0x450040:
        case 0x4500b0:
        case 0x450100:
            success = vertrix_ui_indicator_storage_update_list(next, sizeof(next), list, resolve,
                                                               context, elapsed);
            break;
        case 0x450860:
        case 0x4508c0:
        case 0x450920:
        case 0x450960:
        case 0x4509a0:
        case 0x4509d0:
            success = vertrix_ui_companion_storage_update_list(next, sizeof(next), list, resolve,
                                                               context, start_y, elapsed,
                                                               refresh_words, refresh_count);
            break;
        case 0x450a10:
        case 0x450aa0:
        case 0x450b30:
        case 0x450b90:
        case 0x450bf0:
        case 0x450c70:
            success = vertrix_ui_actor_storage_update_list(next, sizeof(next), list, resolve,
                                                           context, start_y, elapsed, resource_one,
                                                           resource_other, budget);
            break;
        default:
            return 0;
    }
    if (!success)
    {
        return 0;
    }
    memcpy(storage, next, sizeof(next));
    return 1;
}
