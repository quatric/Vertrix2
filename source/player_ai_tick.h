#ifndef VERTRIX_PLAYER_AI_TICK_H
#define VERTRIX_PLAYER_AI_TICK_H

#include "board_cells.h"
#include <stddef.h>
#include <stdint.h>

typedef struct
{
    /* Object resolution */
    VertrixObjectStorage resolve;
    void *resolve_context;
    /* Board comparison callback (0x427850) */
    void (*compare_boards)(void *ai_obj, size_t ai_size, const void *player, size_t player_size,
                           void *context);
    void *compare_context;
    /* Piece frames callback (0x42b090) */
    int (*preview_frames)(const void *piece, size_t piece_size, uint32_t table[7], void *context);
    void *preview_context;
    /* Choose rotation callback (0x4290a0) */
    int (*choose_rotation)(void *ai_obj, size_t ai_size, const uint32_t table[7], uint32_t *chosen,
                           void *context);
    void *rotation_context;
    /* Timer callbacks (0x4ac500, 0x4ac520, 0x4ac510, 0x4ac7d0) */
    void (*timer_update)(void *ai_obj, size_t ai_size, void *context);
    int (*timer_check)(const void *ai_obj, size_t ai_size, void *context);
    void (*timer_reset)(void *ai_obj, size_t ai_size, void *context);
    void (*timer_set_period)(void *ai_obj, size_t ai_size, uint32_t period, void *context);
    void *timer_context;
    /* Delay 2 draw callback (0x43b680) */
    int (*draw_delay_2)(void *player, size_t player_size, uint32_t *delay, void *context);
    void *delay_context;
    /* Fast drop check callback (0x431490) */
    int (*check_fast_drop)(const void *board, size_t board_size, void *context);
    void *drop_context;
    /* Key inject callback (0x4761d0 / 0x476280) */
    void (*key_event)(uint16_t key, int press, void *context);
    void *key_context;
} VertrixPlayerAiTickOps;

/* Original 0x43b430: player update AI tick handler.
 * Checks AI enabled flag (+0x454).
 * If phase (+0x178) is 1: evaluates board, queries piece block kinds, selects rotation,
 * clears phase to 0, resets timer counter, and primes delay parameter 2.
 * If phase is 0: updates timer, and on period expiration:
 *   - if rotations left (+0x16c) > 0: decrements and emits permute key (+0x164).
 *   - if rotations left == 0 and not yet fast dropping: emits drop key (+0x166).
 * Returns 0 if AI disabled or invalid storage, 1 if idle, 2 if permute emitted, 3 if drop emitted.
 */
int vertrix_player_ai_tick(void *player, size_t player_size, const VertrixPlayerAiTickOps *ops);

#endif
