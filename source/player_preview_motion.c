#include "player_preview_motion.h"
#include "timing.h"

int vertrix_player_preview_motion_start(void *player, size_t size, int difficulty)
{
    uint32_t state;
    if (!vertrix_actor_storage_read(player, size, 0x178, 4, &state))
    {
        return 0;
    }
    if (state)
    {
        return 1;
    }
    if (difficulty < 0 || difficulty > 2)
    {
        return 0;
    }
    VertrixMotion motion = {0};
    vertrix_motion_fast(&motion, difficulty);
    vertrix_actor_storage_write(player, size, 0x178, 4, motion.state);
    vertrix_actor_storage_write(player, size, 0xc0, 4, motion.period);
    vertrix_actor_storage_write(player, size, 0x1a, 2, motion.step);
    vertrix_actor_storage_write(player, size, 0xbc, 4, motion.counter);
    return 1;
}

int vertrix_player_preview_below_limit(const void *player, size_t size, int *below)
{
    uint32_t y, limit;
    if (!below || !vertrix_actor_storage_read(player, size, 0x16, 2, &y) ||
        !vertrix_actor_storage_read(player, size, 0xae, 2, &limit))
    {
        return 0;
    }
    *below = (y ^ UINT32_C(0x8000)) > (limit ^ UINT32_C(0x8000));
    return 1;
}
