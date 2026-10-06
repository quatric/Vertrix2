#include "ui_player_previews.h"
#include <string.h>

int vertrix_ui_player_preview_parent_construct(void *player, size_t player_size)
{
    if (!player || player_size < 0x174)
    {
        return 0;
    }
    vertrix_actor_storage_construct(player, player_size);
    vertrix_actor_storage_write(player, player_size, 0x158, 4, 0x514814);
    for (size_t i = 0; i < VERTRIX_UI_PREVIEW_ACTORS; ++i)
    {
        vertrix_actor_storage_write(player, player_size, 0x15c + i * 4, 4, 0);
    }
    return 1;
}

int vertrix_ui_player_previews_construct(void *player, size_t player_size, void *actors,
                                         size_t actors_size,
                                         const uint32_t handles[VERTRIX_UI_PREVIEW_ACTORS],
                                         uint8_t side, uint32_t source,
                                         const VertrixUiSpriteBank *interface_bank,
                                         const VertrixUiSpriteBank *border_bank)
{
    const size_t required = VERTRIX_UI_PREVIEW_ACTORS * VERTRIX_ACTOR_BASE_SIZE;
    if (!player || player_size < 0x174 || !actors || actors_size < required || !handles)
    {
        return 0;
    }
    uintptr_t parent_address = (uintptr_t)player, actor_address = (uintptr_t)actors;
    if ((parent_address <= actor_address && actor_address - parent_address < 0x174) ||
        (actor_address < parent_address && parent_address - actor_address < required))
    {
        return 0;
    }
    uint32_t identities[VERTRIX_UI_PREVIEW_ACTORS];
    memcpy(identities, handles, sizeof(identities));
    for (size_t i = 0; i < VERTRIX_UI_PREVIEW_ACTORS; ++i)
    {
        if (!identities[i])
        {
            return 0;
        }
        for (size_t j = 0; j < i; ++j)
        {
            if (identities[i] == identities[j])
            {
                return 0;
            }
        }
    }
    uint32_t linked;
    vertrix_actor_storage_read(player, player_size, 0, 4, &linked);
    uint8_t next[VERTRIX_UI_PREVIEW_ACTORS][VERTRIX_ACTOR_BASE_SIZE];
    memcpy(next, actors, sizeof(next));
    for (size_t i = 0; i < 3; ++i)
    {
        if (!vertrix_ui_preview_pair_construct(next[i * 2], sizeof(next[0]), next[i * 2 + 1],
                                               sizeof(next[0]), i, side, linked, source,
                                               interface_bank, border_bank))
        {
            return 0;
        }
    }
    memcpy(actors, next, sizeof(next));
    for (size_t i = 0; i < 3; ++i)
    {
        vertrix_actor_storage_write(player, player_size, 0x15c + i * 4, 4, identities[i * 2]);
        vertrix_actor_storage_write(player, player_size, 0x168 + i * 4, 4, identities[i * 2 + 1]);
    }
    return 1;
}
