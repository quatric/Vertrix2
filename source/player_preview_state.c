#include "player_preview_state.h"
#include <string.h>

int vertrix_player_preview_mode(const void *player, size_t size, uint32_t *mode)
{
    return vertrix_actor_storage_read(player, size, 0x180, 4, mode);
}

int vertrix_player_preview_toggle(void *player, size_t size)
{
    uint32_t value;
    if (!vertrix_actor_storage_read(player, size, 0x184, 4, &value))
    {
        return 0;
    }
    return vertrix_actor_storage_write(player, size, 0x184, 4, UINT32_C(1) - value);
}

int vertrix_player_preview_set_mode(void *player, size_t size, uint32_t mode)
{
    uint32_t previous;
    if (!player || size < 0x188 || !vertrix_actor_storage_read(player, size, 0x180, 4, &previous))
    {
        return 0;
    }
    if (mode == 1 && previous == 0)
    {
        vertrix_actor_storage_write(player, size, 0x184, 4, 1);
    }
    else if (mode != 1 && previous == 1)
    {
        vertrix_actor_storage_write(player, size, 0x184, 4, 0);
    }
    return vertrix_actor_storage_write(player, size, 0x180, 4, mode);
}

int vertrix_player_preview_frame(const void *player, size_t size,
                                 VertrixActorStorageResolve resolve, void *context, uint32_t *frame)
{
    uint32_t count, handle;
    if (!resolve || !frame || !vertrix_actor_storage_read(player, size, 0x188, 4, &count) ||
        count < 1 || count > 3 ||
        !vertrix_actor_storage_read(player, size, 0x158 + count * 4, 4, &handle) || !handle)
    {
        return 0;
    }
    const void *actor;
    size_t actor_size;
    return resolve(handle, &actor, &actor_size, context) &&
           vertrix_actor_storage_read(actor, actor_size, 0xb8, 4, frame);
}

int vertrix_player_preview_frames(const void *player, size_t size,
                                  VertrixActorStorageResolve resolve, void *context,
                                  uint32_t *frames, size_t capacity)
{
    uint32_t count;
    if (!frames || capacity < 7 || !vertrix_actor_storage_read(player, size, 0x188, 4, &count) ||
        count > 3 || (count && !resolve))
    {
        return 0;
    }
    uint32_t next[7];
    for (size_t i = 0; i < 7; ++i)
    {
        next[i] = UINT32_MAX;
    }
    for (size_t i = 0; i < count; ++i)
    {
        uint32_t handle;
        const void *actor;
        size_t actor_size;
        if (!vertrix_actor_storage_read(player, size, 0x15c + i * 4, 4, &handle) || !handle ||
            !resolve(handle, &actor, &actor_size, context) ||
            !vertrix_actor_storage_read(actor, actor_size, 0xb8, 4, &next[i]))
        {
            return 0;
        }
    }
    memcpy(frames, next, sizeof(next));
    return 1;
}
