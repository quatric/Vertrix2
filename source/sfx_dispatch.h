#ifndef VERTRIX_SFX_DISPATCH_H
#define VERTRIX_SFX_DISPATCH_H

#include <stddef.h>
#include <stdint.h>

enum
{
    VERTRIX_SFX_NONE = 0x000f4240, /* 1,000,000 sentinel */
    VERTRIX_SFX_P1_BASE_CHANNEL = 0,
    VERTRIX_SFX_P2_BASE_CHANNEL = 4,
    VERTRIX_SFX_DEFAULT_VOLUME = 48
};

typedef int (*VertrixSfxChannelBusyCheck)(uint32_t channel, void *context);
typedef void (*VertrixSfxPlayCallback)(uint32_t effect, uint32_t side, void *context);

/* Original 0x4174f0: allocate first free channel among 0..3 for player 1.
 * If all are busy, falls back to channel 0. */
uint32_t vertrix_sfx_allocate_channel_p1(VertrixSfxChannelBusyCheck is_free, void *context);

/* Original 0x417550: allocate first free channel among 4..7 for player 2.
 * If all are busy, falls back to channel 4. */
uint32_t vertrix_sfx_allocate_channel_p2(VertrixSfxChannelBusyCheck is_free, void *context);

/* Original 0x43c0e0: dispatches an effect to player 1 (side 1) or player 2 (side 2).
 * Sentinel effect 0xf4240 (1,000,000) is ignored.
 * Returns 1 if dispatched, 0 if ignored or invalid player. */
int vertrix_sfx_dispatch_event(const void *player, size_t size, uint32_t effect,
                               VertrixSfxPlayCallback play, void *context);

/* Original 0x43c110: secondary effect dispatcher for player 1 / 2.
 * Same sentinel check, routes to alternative playback handlers. */
int vertrix_sfx_dispatch_secondary(const void *player, size_t size, uint32_t effect,
                                   VertrixSfxPlayCallback play, void *context);

#endif
