#include "player_piece.h"
#include <string.h>

int vertrix_player_piece_create(void *player, size_t player_size, uint32_t parent_handle,
                                void *parent, size_t parent_size, void *children,
                                size_t children_size, const uint32_t frames[7],
                                const uint32_t handles[7], uint8_t side, int difficulty, int level,
                                const VertrixPiecePlacement *placement)
{
    uint32_t existing;
    if (!vertrix_actor_storage_read(player, player_size, 0xb78, 4, &existing))
    {
        return 0;
    }
    if (existing)
    {
        return 1;
    }
    if (!parent_handle || !parent || parent_size < 0x18c)
    {
        return 0;
    }
    if (children)
    {
        uintptr_t a = (uintptr_t)parent, b = (uintptr_t)children;
        if (children_size && ((a <= b && b - a < 0x18c) || (b < a && a - b < children_size)))
        {
            return 0;
        }
    }
    uint8_t staged[0x18c];
    memcpy(staged, parent, sizeof(staged));
    if (!vertrix_piece_actor_parent_construct(staged, sizeof(staged)) ||
        !vertrix_piece_actor_construct_placed(staged, sizeof(staged), children, children_size,
                                              frames, handles, side, difficulty, level, placement))
    {
        return 0;
    }
    memcpy(parent, staged, sizeof(staged));
    return vertrix_actor_storage_write(player, player_size, 0xb78, 4, parent_handle);
}

static int release_actor(void *player, size_t player_size, size_t handle_offset, size_t keep_offset,
                         int last_child, VertrixActorStorageResolve resolve, void *resolve_context,
                         VertrixPlayerActorDestroy destroy, void *destroy_context)
{
    uint32_t handle, kept;
    if (!vertrix_actor_storage_read(player, player_size, handle_offset, 4, &handle) ||
        !vertrix_actor_storage_read(player, player_size, keep_offset, 4, &kept))
    {
        return 0;
    }
    if (!handle)
    {
        return 1;
    }
    const void *actor;
    size_t actor_size;
    uint32_t value;
    if (!resolve || !destroy || !resolve(handle, &actor, &actor_size, resolve_context) || !actor)
    {
        return 0;
    }
    if (last_child)
    {
        uint32_t count, child_handle;
        if (!vertrix_actor_storage_read(actor, actor_size, 0x188, 4, &count) || count < 1 ||
            count > 7 ||
            !vertrix_actor_storage_read(actor, actor_size, 0x158 + count * 4, 4, &child_handle) ||
            !child_handle)
        {
            return 0;
        }
        const void *child;
        size_t child_size;
        if (!resolve(child_handle, &child, &child_size, resolve_context) || !child ||
            !vertrix_actor_storage_read(child, child_size, 0xb8, 4, &value))
        {
            return 0;
        }
    }
    else if (!vertrix_actor_storage_read(actor, actor_size, 0x168, 4, &value))
    {
        return 0;
    }
    vertrix_actor_storage_write(player, player_size, keep_offset, 4, value);
    if (!destroy(handle, destroy_context))
    {
        return 0;
    }
    return vertrix_actor_storage_write(player, player_size, handle_offset, 4, 0);
}

int vertrix_player_piece_release(void *player, size_t player_size,
                                 VertrixActorStorageResolve resolve, void *resolve_context,
                                 VertrixPlayerActorDestroy destroy, void *destroy_context)
{
    return release_actor(player, player_size, 0xb78, 0xb7c, 1, resolve, resolve_context, destroy,
                         destroy_context);
}

int vertrix_player_preview_release(void *player, size_t player_size,
                                   VertrixActorStorageResolve resolve, void *resolve_context,
                                   VertrixPlayerActorDestroy destroy, void *destroy_context)
{
    return release_actor(player, player_size, 0xb70, 0xb74, 0, resolve, resolve_context, destroy,
                         destroy_context);
}

int vertrix_player_piece_initialize(void *piece, size_t piece_size)
{
    enum
    {
        PIECE_CLASS = 0x5144d4,
        PIECE_LEVEL = 0x178
    };
    if (!piece || !vertrix_actor_storage_construct(piece, piece_size))
    {
        return 0;
    }
    if (!vertrix_actor_storage_write(piece, piece_size, 0x158, 4, PIECE_CLASS))
    {
        return 0;
    }
    return vertrix_actor_storage_write(piece, piece_size, PIECE_LEVEL, 4, 0);
}
