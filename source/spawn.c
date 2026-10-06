#include "spawn.h"

#include <string.h>

static int16_t signed_word(uint16_t value)
{
    return (int16_t)(value < 32768 ? value : (int32_t)value - 65536);
}

/* Original 0x00431d90 through the constructor call at 0x00431e28.
 * An occupied preferred top cell falls back to column 2; the original
 * does not reject a spawn because column 2 is occupied. */
VertrixSpawn vertrix_spawn_position(const uint8_t board[COLS][ROWS], uint32_t preferred_column,
                                    int16_t origin_x, int16_t origin_y)
{
    VertrixSpawn spawn;
    spawn.column = preferred_column;
    if (spawn.column != 2 && board[spawn.column][0] != EMPTY)
    {
        spawn.column = 2;
    }
    spawn.x = signed_word((uint16_t)((uint16_t)origin_x + spawn.column * 24));
    spawn.y = signed_word((uint16_t)((uint16_t)origin_y - 72));
    return spawn;
}

static uint32_t spawn_animation_period(VertrixRandom *random, VertrixAnimationRange range)
{
    uint16_t width = (uint16_t)(range.last - range.first + 1);
    return range.first + vertrix_random_modulo(random, width);
}

int vertrix_spawn_initialize(const uint8_t board[COLS][ROWS], uint32_t *preferred_column,
                             int16_t origin_x, int16_t origin_y, const uint8_t blocks[3],
                             VertrixFallingPiece *piece, VertrixDescentState *state,
                             VertrixSpawnDetails *details, VertrixRandom *random,
                             const VertrixAnimationRange animation_ranges[7], int difficulty,
                             int level)
{
    if (*preferred_column >= COLS || difficulty < 0 || difficulty > 2 || level < 0 || level > 9)
    {
        return 0;
    }
    for (unsigned i = 0; i < 7; i++)
    {
        if (animation_ranges[i].last < animation_ranges[i].first ||
            animation_ranges[i].last - animation_ranges[i].first >= 65535)
        {
            return 0;
        }
    }
    for (unsigned i = 0; i < 3; i++)
    {
        if (blocks[i] >= 7)
        {
            return 0;
        }
    }
    VertrixSpawn spawn = vertrix_spawn_position(board, *preferred_column, origin_x, origin_y);
    piece->x = spawn.x;
    piece->y = spawn.y;
    piece->active = 1;
    if (spawn.column == 2 && board[2][0] != EMPTY)
    {
        piece->failed = 1;
    }
    memcpy(piece->blocks, blocks, sizeof(piece->blocks));
    memset(state, 0, sizeof(*state));
    memset(details, 0, sizeof(*details));
    for (unsigned i = 0; i < 3; i++)
    {
        /* The original constructor initializes temporary colors 0, 1 and 2. */
        (void)spawn_animation_period(random, animation_ranges[i]);
        (void)vertrix_random_modulo(random, 10);
    }
    vertrix_motion_level(&state->motion, difficulty, level);
    state->blink.period = 400;
    details->blink_mode = 1;
    for (unsigned i = 0; i < 3; i++)
    {
        details->animation[i].period = spawn_animation_period(random, animation_ranges[blocks[i]]);
        details->primary[i].period = 12u * (vertrix_random_modulo(random, 10) + 1u);
    }
    *preferred_column = 2;
    return 1;
}
