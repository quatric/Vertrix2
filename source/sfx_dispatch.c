#include "sfx_dispatch.h"
#include "actor_storage.h"

enum
{
    PLAYER_SIDE_OFFSET = 0x0,
    PLAYER_SIDE_SIZE = 4
};

uint32_t vertrix_sfx_allocate_channel_p1(VertrixSfxChannelBusyCheck is_free, void *context)
{
    for (uint32_t channel = 0; channel < 4; ++channel)
    {
        if (is_free && is_free(channel, context) == 1)
        {
            return channel;
        }
    }
    return VERTRIX_SFX_P1_BASE_CHANNEL;
}

uint32_t vertrix_sfx_allocate_channel_p2(VertrixSfxChannelBusyCheck is_free, void *context)
{
    for (uint32_t channel = 4; channel < 8; ++channel)
    {
        if (is_free && is_free(channel, context) == 1)
        {
            return channel;
        }
    }
    return VERTRIX_SFX_P2_BASE_CHANNEL;
}

int vertrix_sfx_dispatch_event(const void *player, size_t size, uint32_t effect,
                               VertrixSfxPlayCallback play, void *context)
{
    if (effect == VERTRIX_SFX_NONE || !player || size < PLAYER_SIDE_SIZE)
    {
        return 0;
    }

    uint32_t side = 0;
    if (!vertrix_actor_storage_read(player, size, PLAYER_SIDE_OFFSET, 4, &side))
    {
        return 0;
    }

    if (side == 1 || side == 2)
    {
        if (play)
        {
            play(effect, side, context);
        }
        return 1;
    }

    return 0;
}

int vertrix_sfx_dispatch_secondary(const void *player, size_t size, uint32_t effect,
                                   VertrixSfxPlayCallback play, void *context)
{
    return vertrix_sfx_dispatch_event(player, size, effect, play, context);
}
