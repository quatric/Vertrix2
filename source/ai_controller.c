#include "ai_controller.h"

enum
{
    SKILLS = 19,
    TOP_RATING = 12,
    LEVEL_RATING_HIGH = 7,
    LEVEL_RATING_LOW = 3,
    PIECE_PIXEL_REACH = 0x47,
    THRESHOLD = 2, /* player +0x4dc */
    MODE = 0       /* player +0x4c8 */
};

/* The table at 0x4f8cec read by 0x425ef0. */
static const uint8_t RATING[SKILLS] = {9, 3, 10, 7, 8, 9, 10, 5, 12, 11, 9, 6, 2, 7, 9, 8, 6, 5, 7};

static uint16_t draw(void *context, uint16_t divisor)
{
    return vertrix_random_modulo((VertrixRandom *)context, divisor);
}

/* Original 0x425ef0: the level of the planner follows the skill's rating. */
void vertrix_ai_controller_init(VertrixAiController *ai, uint32_t skill)
{
    uint32_t rating = RATING[skill % SKILLS];
    *ai = (VertrixAiController){0};
    ai->skill = skill % SKILLS;
    ai->level = rating == TOP_RATING         ? 4
                : rating > LEVEL_RATING_HIGH ? 3
                : rating <= LEVEL_RATING_LOW ? 1
                                             : 2;
    ai->previous = 0xffffffffu;
}

static void plan(VertrixAiController *ai, VertrixSession *session)
{
    VertrixAiSettings settings = {ai->level, THRESHOLD, 0, MODE};
    uint8_t board[COLS * ROWS];
    uint32_t column = ai->column;
    uint32_t rotation = ai->rotations;
    uint32_t start = (uint32_t)(session->piece.x / VERTRIX_CELL_SIZE);
    uint32_t row = (uint32_t)((int16_t)(session->piece.y + PIECE_PIXEL_REACH) / VERTRIX_CELL_SIZE);
    for (int x = 0; x < COLS; x++)
    {
        for (int y = 0; y < ROWS; y++)
        {
            board[x * ROWS + y] = session->board[x][y];
        }
    }
    if (vertrix_ai_plan(board, session->piece.blocks[0], session->piece.blocks[1],
                        session->piece.blocks[2], start, row, &settings, &ai->previous, draw,
                        &session->random, &column, &rotation))
    {
        ai->column = column;
        ai->rotations = rotation;
    }
}

static uint32_t reaction(const VertrixAiController *ai, VertrixSession *session)
{
    return vertrix_ai_reaction_time(ai->skill, session->difficulty, session->level, draw,
                                    &session->random);
}

void vertrix_ai_controller_update(VertrixAiController *ai, VertrixSession *session,
                                  uint32_t elapsed)
{
    VertrixAiKeys keys;
    if (session->phase != VERTRIX_PHASE_PLAYING || session->paused || !session->piece.active)
    {
        return;
    }
    if (ai->spawned != session->spawned)
    {
        ai->spawned = session->spawned;
        ai->planned = 0;
        ai->dropping = 0;
    }
    if (!ai->planned)
    {
        plan(ai, session);
        ai->planned = 1;
        ai->counter = 0;
        ai->period = reaction(ai, session);
        return;
    }
    ai->counter += elapsed;
    if (ai->counter < ai->period)
    {
        return;
    }
    ai->counter = 0;
    ai->period = reaction(ai, session);
    vertrix_ai_steer(ai->level, session->piece.x / VERTRIX_CELL_SIZE, (int32_t)ai->column,
                     &ai->rotations, ai->dropping, &keys);
    if (keys.left)
    {
        vertrix_session_move(session, 0);
    }
    if (keys.right)
    {
        vertrix_session_move(session, 1);
    }
    if (keys.permute)
    {
        vertrix_session_cycle(session);
    }
    if (keys.drop)
    {
        ai->dropping = 1;
        vertrix_session_drop(session);
    }
}
