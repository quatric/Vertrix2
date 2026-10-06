#ifndef VERTRIX_SPAWN_H
#define VERTRIX_SPAWN_H

#include "descent.h"
#include "game.h"
#include "random.h"

typedef struct
{
    uint32_t column;
    int16_t x;
    int16_t y;
} VertrixSpawn;

/* preferred_column is original board +0xa68, valid 0..4. */
VertrixSpawn vertrix_spawn_position(const uint8_t board[COLS][ROWS], uint32_t preferred_column,
                                    int16_t origin_x, int16_t origin_y);

typedef struct
{
    uint32_t first;
    uint32_t last;
} VertrixAnimationRange;

typedef struct
{
    VertrixTimer animation[3];
    VertrixTimer primary[3];
    uint32_t blink_mode;
} VertrixSpawnDetails;

/* Original spawn and constructor initialization. Animation-delay ranges are the original
 * loaded delay ranges (+0x53bcd0), not sprite frame counts. Returns 0 before
 * mutation on invalid inputs. preferred_column resets to 2 after spawning.
 * Renderer object ownership/resource attachment remains a platform concern. */
int vertrix_spawn_initialize(const uint8_t board[COLS][ROWS], uint32_t *preferred_column,
                             int16_t origin_x, int16_t origin_y, const uint8_t blocks[3],
                             VertrixFallingPiece *piece, VertrixDescentState *state,
                             VertrixSpawnDetails *details, VertrixRandom *random,
                             const VertrixAnimationRange animation_ranges[7], int difficulty,
                             int level);

#endif
