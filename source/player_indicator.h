#ifndef VERTRIX_PLAYER_INDICATOR_H
#define VERTRIX_PLAYER_INDICATOR_H
#include "timer.h"
typedef struct
{
    uint32_t value, state, handler;
    VertrixTimer primary, secondary;
} VertrixPlayerIndicator;
/* Original variants 0x44fe80, 0x44fed0, 0x44ff30, 0x44ff60: Player state is field18c.
 * notify reports the43c0e0 request on primary expiry; caller performs audio.
 * Invalid state preserves outputs. No player-state mutation occurs here. */
int vertrix_player_indicator_update(VertrixPlayerIndicator *indicator, uint32_t player_state,
                                    uint32_t elapsed, int *notify);
typedef struct
{
    uint32_t value, state, target, handler;
    VertrixTimer primary, secondary;
} VertrixPlayerCountdown;
/* Original variants 0x450750, 0x4507e0, 0x450830: player_value is field180; player_flag
 * represents3ac and is cleared only when it equals1 and countdown state reaches its target. */
int vertrix_player_countdown_update(VertrixPlayerCountdown *countdown, uint32_t player_value,
                                    uint32_t *player_flag, uint32_t elapsed);
#endif
