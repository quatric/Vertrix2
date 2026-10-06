#include "game_session.h"

#include "score.h"
#include <string.h>

enum
{
    LEVEL_STEP = 12,
    LEVEL_MAX = VERTRIX_SESSION_LEVELS - 1,
    MATCH_THRESHOLD = 2,
    POWER_NEED_THREE = 0x24,
    POWER_RANDOM_SPEED = 0x31,
    CLEAR_FLASH_MS = 300,
    GAUGE_STEP_MS = 150,
    GAUGE_WAIT_MS = 1000,
    /* The defaults of a first run (settings_defaults.c, copied to the match by 0x41bbc3): the
     * speed choice 5 becomes the player's +0x17c (0x43a90d), the mode choice 1 is the race, won at
     * the limit 10 of 0x4157c5. */
    ALERT_WAIT_MS = 500,
    MIX_PERIOD_MS = 180,
    DEFAULT_SPEED = 5,
    RACE_LIMIT = 10,
    DEFAULT_RANGE_FIRST = 40,
    DEFAULT_RANGE_LAST = 80
};

static const int USE_FIGURES = 1;

/* 0x4f7c0c and 0x4f7c3c: tick of the sliding bonuses in units of 12 ms; 0x4f7c18 and 0x4f7c48:
 * the pixels each tick moves (a cell is 24), per difficulty. */
static const uint8_t RISE_TICK[6] = {4, 4, 4, 2, 2, 2};
static const uint8_t COLUMN_PIXELS[6] = {2, 2, 2, 15, 15, 15};
static const uint8_t ROW_PIXELS = 2;

static uint32_t slide_tick_ms(const VertrixSession *session)
{
    return 12u * RISE_TICK[session->difficulty < 6 ? session->difficulty : 0];
}

static uint32_t column_slide_ms(const VertrixSession *session)
{
    uint32_t pixels = COLUMN_PIXELS[session->difficulty < 6 ? session->difficulty : 0];
    return (VERTRIX_CELL_SIZE + pixels - 1) / pixels * slide_tick_ms(session);
}

/* 0x4f7c90: the freeze durations in units of 12 ms, five per difficulty. */
static const uint16_t FREEZE_STEPS[3][5] = {
    {700, 800, 900, 1000, 800}, {700, 800, 900, 1000, 800}, {700, 800, 900, 1000, 800}};

void vertrix_session_random_speed(VertrixSession *session);

static void spawn_piece(VertrixSession *session)
{
    VertrixSpawnDetails details;
    uint8_t blocks[VERTRIX_PIECE_BLOCKS];
    memcpy(blocks, session->next, sizeof blocks);
    if (!vertrix_spawn_initialize(session->board, &session->preferred_column, 0, 0, blocks,
                                  &session->piece, &session->descent, &details, &session->random,
                                  session->ranges, (int)session->difficulty, (int)session->level))
    {
        session->phase = VERTRIX_PHASE_OVER;
        return;
    }
    session->details = details;
    session->spawned++;
    vertrix_piece(&session->random, session->power, session->next);
    if (session->power == POWER_RANDOM_SPEED)
    {
        vertrix_session_random_speed(session);
    }
    session->piece.failed = session->piece.failed ? 1 : 0;
    session->phase = session->piece.failed ? VERTRIX_PHASE_OVER : VERTRIX_PHASE_PLAYING;
}

void vertrix_session_start(VertrixSession *session, uint32_t seed, uint32_t difficulty,
                           const VertrixAnimationRange ranges[7])
{
    vertrix_session_start_options(session, seed, difficulty, ranges, DEFAULT_SPEED, RACE_LIMIT);
}

void vertrix_session_start_options(VertrixSession *session, uint32_t seed, uint32_t difficulty,
                                   const VertrixAnimationRange ranges[7], uint32_t speed,
                                   uint32_t race_limit)
{
    memset(session, 0, sizeof *session);
    memset(session->board, EMPTY, sizeof session->board);
    vertrix_random_seed(&session->random, seed);
    for (unsigned i = 0; i < 7; i++)
    {
        session->ranges[i].first = ranges ? ranges[i].first : DEFAULT_RANGE_FIRST;
        session->ranges[i].last = ranges ? ranges[i].last : DEFAULT_RANGE_LAST;
    }
    session->difficulty = difficulty > 2 ? 2 : difficulty;
    session->preferred_column = 2;
    session->threshold = MATCH_THRESHOLD;
    session->level = speed > LEVEL_MAX ? LEVEL_MAX : speed;
    session->race_limit = race_limit;
    session->alert_wait = -1;
    session->level_counter = LEVEL_STEP;
    session->gauge_shown = LEVEL_STEP;
    vertrix_gauge_tube_init(&session->tube);
    vertrix_piece(&session->random, 0, session->next);
    spawn_piece(session);
}

void vertrix_session_move(VertrixSession *session, int right)
{
    if (session->phase == VERTRIX_PHASE_PLAYING && !session->paused)
    {
        vertrix_move_horizontal(session->board, 0, 0, &session->piece, right);
    }
}

void vertrix_session_cycle(VertrixSession *session)
{
    if (session->phase == VERTRIX_PHASE_PLAYING && !session->paused && session->piece.active)
    {
        vertrix_piece_cycle(session->piece.blocks);
    }
}

void vertrix_session_drop(VertrixSession *session)
{
    if (session->phase == VERTRIX_PHASE_PLAYING && !session->paused)
    {
        vertrix_motion_fast(&session->descent.motion, (int)session->difficulty);
    }
}

/* 0x43b9c0 adds the reward to the meter and caps it at 3; the meter object 0x44fe80 .. 0x44ff60
 * (periods 500 ms, 0x46d678) plays the alert when it reads 3. */
static void meter_add(VertrixSession *session, uint32_t reward)
{
    uint32_t before = session->meter;
    session->meter += reward;
    if (session->meter > 3)
    {
        session->meter = 3;
    }
    if (session->meter == 3 && before != 3)
    {
        session->alert_wait = ALERT_WAIT_MS;
    }
}

static void level_progress(VertrixSession *session, uint32_t reward)
{
    meter_add(session, reward);
    session->level_counter -= (int32_t)reward;
    while (session->level_counter < 1)
    {
        session->level_counter += LEVEL_STEP;
        session->progress++;
        if (session->race_limit && session->progress >= session->race_limit)
        {
            session->won = 1;
            session->events |= VERTRIX_EVENT_WIN;
        }
        session->gauge_refill = 1;
        session->events |= VERTRIX_EVENT_LEVEL_REFILL;
        if (session->level < LEVEL_MAX)
        {
            session->level++;
        }
    }
}

void vertrix_session_receive(VertrixSession *session, uint32_t rows)
{
    session->incoming += rows;
}

/* 0x43b810: the speed is clamped to 0..9, a negative request gives 0; returns 1 when it changed. */
int vertrix_session_set_speed(VertrixSession *session, int32_t speed)
{
    uint32_t old = session->level;
    session->level = speed < 0 ? 0 : speed > LEVEL_MAX ? LEVEL_MAX : (uint32_t)speed;
    return session->level != old;
}

/* 0x43b800: the speed plus a signed amount. */
int vertrix_session_add_speed(VertrixSession *session, int32_t amount)
{
    return vertrix_session_set_speed(session, (int32_t)session->level + amount);
}

/* 0x452d70, "exchange speeds": each board takes the other's speed (0x43b810 twice). */
void vertrix_session_exchange_speeds(VertrixSession *a, VertrixSession *b)
{
    uint32_t speed = a->level;
    vertrix_session_set_speed(a, (int32_t)b->level);
    vertrix_session_set_speed(b, (int32_t)speed);
}

int vertrix_session_lower_level(VertrixSession *session, uint32_t amount)
{
    uint32_t old = session->progress;
    session->progress = old > amount ? old - amount : 0;
    if (session->progress == old)
    {
        return 0;
    }
    session->events |= VERTRIX_EVENT_LASER_DOWN;
    return 1;
}

void vertrix_session_random_speed(VertrixSession *session)
{
    uint32_t old = session->level;
    uint32_t speed = old;
    do
    {
        speed = vertrix_random_range(&session->random, 0, 10);
    } while (speed == old);
    vertrix_session_set_speed(session, (int32_t)speed);
    session->events |= speed < old ? VERTRIX_EVENT_LASER_DOWN : VERTRIX_EVENT_LASER_UP;
}

/* 0x435e80: the marker grid of a mix mode over the kind snapshot (0xff empty is never marked, a
 * stone only in mode 2, a bomb in modes 1 and 2, the normal kinds in modes 0 to 2). */
static void mix_markers(VertrixSession *session)
{
    for (int x = 0; x < COLS; x++)
    {
        for (int y = 0; y < ROWS; y++)
        {
            uint8_t kind = session->board[x][y];
            int marked = 0;
            if (kind == EMPTY)
            {
                marked = 0;
            }
            else if (kind == STONE)
            {
                marked = session->mix_mode == 2;
            }
            else if (kind == 6)
            {
                marked = session->mix_mode == 1 || session->mix_mode == 2;
            }
            else
            {
                marked = session->mix_mode <= 2;
            }
            session->mix_marks[x][y] = (uint8_t)marked;
        }
    }
}

static uint32_t mix_count(const VertrixSession *session)
{
    uint32_t count = 0;
    for (int x = 0; x < COLS; x++)
    {
        for (int y = 0; y < ROWS; y++)
        {
            count += session->mix_marks[x][y] == 1;
        }
    }
    return count;
}

/* 0x4360b0: the n-th marker equal to one, rows first (0..12), columns within a row. */
static int mix_nth(const VertrixSession *session, uint32_t n, int *column, int *row)
{
    uint32_t seen = 0;
    for (int y = 0; y < ROWS; y++)
    {
        for (int x = 0; x < COLS; x++)
        {
            if (session->mix_marks[x][y] == 1)
            {
                if (seen == n)
                {
                    *column = x;
                    *row = y;
                    return 1;
                }
                seen++;
            }
        }
    }
    return 0;
}

/* 0x436150: draw two of the waiting markers (the first below the count, the second below the count
 * minus one), mark both as swapped and exchange the kinds of their blocks. */
static int mix_swap(VertrixSession *session)
{
    uint32_t count = mix_count(session);
    int ax = 0;
    int ay = 0;
    int bx = 0;
    int by = 0;
    if (count < 2)
    {
        return 0;
    }
    mix_nth(session, vertrix_random_modulo(&session->random, (uint16_t)count), &ax, &ay);
    session->mix_marks[ax][ay] = 2;
    mix_nth(session, vertrix_random_modulo(&session->random, (uint16_t)(count - 1)), &bx, &by);
    session->mix_marks[bx][by] = 2;
    uint8_t kind = session->board[ax][ay];
    session->board[ax][ay] = session->board[bx][by];
    session->board[bx][by] = kind;
    return 1;
}

/* 0x4f9ad8 rows 0 to 2: the column patterns (1 draws a kind, 2 is a stone). */
static const uint8_t COLUMN_PATTERN[3][ROWS] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                                                {2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2},
                                                {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}};

int vertrix_session_start_column(VertrixSession *session, int type)
{
    if (type < 0 || type > 2 || session->phase != VERTRIX_PHASE_PLAYING)
    {
        return 0;
    }
    for (int row = 0; row < ROWS; row++)
    {
        uint8_t value = EMPTY;
        if (COLUMN_PATTERN[type][row] == 2)
        {
            value = STONE;
        }
        else if (COLUMN_PATTERN[type][row] == 1)
        {
            uint8_t above = row > 0 ? session->insert_column[row - 1] : EMPTY;
            uint8_t edge = session->board[0][row];
            do
            {
                value = (uint8_t)vertrix_random_modulo(&session->random, 5);
            } while (value == above || value == edge);
        }
        session->insert_column[row] = value;
    }
    session->insert_timer = 0;
    session->events |= VERTRIX_EVENT_PUSH;
    session->phase = VERTRIX_PHASE_INSERTING;
    return 1;
}

/* 0x4f9800: 24 pattern groups of six rows of five cells (0 empty, 1 draws a kind, 2 a stone). */
static const uint8_t ROW_PATTERN[24][6][COLS] = {{{1, 1, 1, 1, 1},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{1, 1, 1, 1, 1},
                                                  {1, 1, 1, 1, 1},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{1, 1, 1, 1, 1},
                                                  {1, 1, 1, 1, 1},
                                                  {1, 1, 1, 1, 1},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{1, 0, 1, 0, 1},
                                                  {1, 0, 1, 0, 1},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{1, 0, 1, 0, 1},
                                                  {1, 0, 1, 0, 1},
                                                  {1, 0, 1, 0, 1},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{1, 0, 1, 0, 1},
                                                  {1, 0, 1, 0, 1},
                                                  {1, 0, 1, 0, 1},
                                                  {1, 0, 1, 0, 1},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{1, 1, 1, 1, 1},
                                                  {1, 1, 1, 1, 0},
                                                  {1, 1, 1, 0, 0},
                                                  {1, 1, 0, 0, 0},
                                                  {1, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{1, 1, 1, 1, 1},
                                                  {0, 1, 1, 1, 1},
                                                  {0, 0, 1, 1, 1},
                                                  {0, 0, 0, 1, 1},
                                                  {0, 0, 0, 0, 1},
                                                  {0, 0, 0, 0, 0}},
                                                 {{1, 1, 1, 1, 1},
                                                  {0, 1, 1, 1, 0},
                                                  {0, 0, 1, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{2, 2, 1, 2, 2},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{2, 2, 2, 2, 2},
                                                  {2, 2, 2, 2, 2},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{2, 2, 2, 2, 2},
                                                  {2, 2, 2, 2, 2},
                                                  {2, 2, 2, 2, 2},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{2, 0, 2, 0, 2},
                                                  {2, 0, 2, 0, 2},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{2, 0, 2, 0, 2},
                                                  {2, 0, 2, 0, 2},
                                                  {2, 0, 2, 0, 2},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{2, 0, 2, 0, 2},
                                                  {2, 0, 2, 0, 2},
                                                  {2, 0, 2, 0, 2},
                                                  {2, 0, 2, 0, 2},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{2, 0, 0, 0, 2},
                                                  {2, 0, 0, 0, 2},
                                                  {2, 0, 0, 0, 2},
                                                  {2, 0, 0, 0, 2},
                                                  {2, 0, 0, 0, 2},
                                                  {2, 0, 0, 0, 2}},
                                                 {{0, 2, 0, 0, 0},
                                                  {0, 2, 0, 0, 0},
                                                  {0, 2, 0, 0, 0},
                                                  {0, 2, 0, 0, 0},
                                                  {0, 2, 0, 0, 0},
                                                  {0, 2, 0, 0, 0}},
                                                 {{0, 0, 0, 2, 0},
                                                  {0, 0, 0, 2, 0},
                                                  {0, 0, 0, 2, 0},
                                                  {0, 0, 0, 2, 0},
                                                  {0, 0, 0, 2, 0},
                                                  {0, 0, 0, 2, 0}},
                                                 {{2, 0, 0, 0, 0},
                                                  {1, 2, 0, 0, 0},
                                                  {1, 1, 2, 0, 0},
                                                  {1, 1, 1, 2, 0},
                                                  {1, 1, 1, 1, 2},
                                                  {0, 0, 0, 0, 0}},
                                                 {{0, 0, 0, 0, 2},
                                                  {0, 0, 0, 2, 1},
                                                  {0, 0, 2, 1, 1},
                                                  {0, 2, 1, 1, 1},
                                                  {2, 1, 1, 1, 1},
                                                  {0, 0, 0, 0, 0}},
                                                 {{0, 0, 2, 0, 0},
                                                  {0, 2, 1, 2, 0},
                                                  {2, 1, 1, 1, 2},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{2, 2, 2, 2, 2},
                                                  {0, 2, 2, 2, 2},
                                                  {0, 0, 2, 2, 2},
                                                  {0, 0, 0, 2, 2},
                                                  {0, 0, 0, 0, 2},
                                                  {0, 0, 0, 0, 0}},
                                                 {{2, 2, 2, 2, 2},
                                                  {2, 2, 2, 2, 0},
                                                  {2, 2, 2, 0, 0},
                                                  {2, 2, 0, 0, 0},
                                                  {2, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}},
                                                 {{2, 2, 2, 2, 2},
                                                  {0, 2, 2, 2, 0},
                                                  {0, 0, 2, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}}};

/* 0x417da0: the number of non-empty rows of a group; 0x4314a0 deals row `step` of it. Returns 0
 * when the row does not exist or holds no cell. */
static int deal_rise_row(VertrixSession *session)
{
    int type = session->rise_type;
    int step = session->rise_step;
    int count = 0;
    int cells = 0;
    for (int row = 0; row < 6; row++)
    {
        for (int x = 0; x < COLS; x++)
        {
            if (ROW_PATTERN[type][row][x])
            {
                count++;
                break;
            }
        }
    }
    if (step >= 6 || count <= step)
    {
        return 0;
    }
    for (int x = 0; x < COLS; x++)
    {
        uint8_t pattern = ROW_PATTERN[type][step][x];
        uint8_t value = EMPTY;
        if (pattern == 2)
        {
            value = STONE;
            cells++;
        }
        else if (pattern == 1)
        {
            uint8_t left = EMPTY;
            uint8_t right = EMPTY;
            if (x > 0)
            {
                left = session->rise_row[x - 1];
                if (left == EMPTY)
                {
                    left = session->board[x - 1][ROWS - 1];
                }
            }
            if (x < COLS - 1 && ROW_PATTERN[type][step][x + 1] == 0)
            {
                right = session->board[x + 1][ROWS - 1];
            }
            do
            {
                value = (uint8_t)vertrix_random_modulo(&session->random, 5);
            } while (value == left || value == right || value == session->board[x][ROWS - 1]);
            cells++;
        }
        session->rise_row[x] = value;
    }
    if (cells == 0)
    {
        return 0;
    }
    session->events |= VERTRIX_EVENT_PUSH;
    return 1;
}

int vertrix_session_start_rows(VertrixSession *session, int type)
{
    if (type < 0 || type > 23 || session->phase != VERTRIX_PHASE_PLAYING)
    {
        return 0;
    }
    session->rise_type = (uint8_t)type;
    session->rise_step = 0;
    session->rise_timer = 0;
    session->rise_offset = 0;
    memset(session->rise_row, EMPTY, sizeof session->rise_row);
    if (!deal_rise_row(session))
    {
        return 0;
    }
    session->phase = VERTRIX_PHASE_RISING;
    return 1;
}

/* 0x453d50 once the row has risen a cell: 0x42f3d0 lifts the falling piece a cell when its column
 * received a cell, 0x42f310 shifts every column that received one up. */
static void finish_rise_row(VertrixSession *session)
{
    if (session->piece.active)
    {
        int column = session->piece.x / VERTRIX_CELL_SIZE;
        if (column >= 0 && column < COLS &&
            ROW_PATTERN[session->rise_type][session->rise_step][column])
        {
            session->piece.y = (int16_t)(session->piece.y - VERTRIX_CELL_SIZE);
        }
    }
    for (int x = 0; x < COLS; x++)
    {
        if (session->rise_row[x] == EMPTY)
        {
            continue;
        }
        for (int y = 0; y < ROWS - 1; y++)
        {
            session->board[x][y] = session->board[x][y + 1];
        }
        session->board[x][ROWS - 1] = session->rise_row[x];
    }
    session->rise_step++;
}

static void update_rising(VertrixSession *session, uint32_t elapsed)
{
    uint32_t tick = slide_tick_ms(session);
    session->rise_timer += elapsed;
    while (session->rise_timer >= tick)
    {
        session->rise_timer -= tick;
        session->rise_offset += ROW_PIXELS;
        if (session->rise_offset < VERTRIX_CELL_SIZE)
        {
            continue;
        }
        session->rise_offset -= VERTRIX_CELL_SIZE;
        finish_rise_row(session);
        memset(session->rise_row, EMPTY, sizeof session->rise_row);
        if (!deal_rise_row(session))
        {
            session->phase = VERTRIX_PHASE_PLAYING;
            session->rise_offset = 0;
            return;
        }
    }
}

int vertrix_session_start_freeze(VertrixSession *session, int parameter)
{
    if (parameter < 1 || parameter > 3 || session->phase != VERTRIX_PHASE_PLAYING)
    {
        return 0;
    }
    session->freeze_left = 12u * FREEZE_STEPS[session->difficulty][parameter - 1];
    session->phase = VERTRIX_PHASE_FROZEN;
    return 1;
}

int vertrix_session_start_mix(VertrixSession *session, int parameter)
{
    if (parameter < 1 || parameter > 3 || session->phase != VERTRIX_PHASE_PLAYING)
    {
        return 0;
    }
    session->mix_mode = (uint8_t)(parameter - 1);
    mix_markers(session);
    if (mix_count(session) < 2)
    {
        return 0;
    }
    session->mix_timer = 0;
    session->phase = VERTRIX_PHASE_MIXING;
    return 1;
}

/* The incoming rows land: 0x4316c0 puts a row of five stones on the board (one per column) for
 * each of the sender's reward points and they fall onto the stacks. A column that cannot take a
 * stone loses the board. The moment the stones land (after the lock) is a simplification of the
 * original's two-board state machine (0x4522c0 .. 0x4527xx). */
static void land_stones(VertrixSession *session)
{
    while (session->incoming && session->phase != VERTRIX_PHASE_OVER)
    {
        session->incoming--;
        for (int x = 0; x < COLS; x++)
        {
            int y = ROWS - 1;
            while (y >= 0 && session->board[x][y] != EMPTY)
            {
                y--;
            }
            if (y < 0)
            {
                session->phase = VERTRIX_PHASE_OVER;
                break;
            }
            session->board[x][y] = STONE;
        }
        session->events |= VERTRIX_EVENT_PUSH;
    }
}

/* Match, then flash the mask; the next call after the flash removes it and collapses. */
static void resolve(VertrixSession *session)
{
    int reward = match_board(session->board, session->mask, session->threshold, USE_FIGURES);
    uint32_t cells = 0;
    if (reward == 0)
    {
        if (session->meter == 3)
        {
            /* 0x451a60 starts the bonus and 0x43ba80 empties the meter; the effects are not
             * ported, only the meter is emptied. */
            session->meter = 0;
            session->alert_wait = -1;
        }
        if (session->chain && session->chain_total)
        {
            session->outgoing += session->chain_total;
        }
        session->chain = 0;
        session->chain_total = 0;
        land_stones(session);
        if (session->phase == VERTRIX_PHASE_OVER)
        {
            return;
        }
        spawn_piece(session);
        return;
    }
    for (int x = 0; x < COLS; x++)
    {
        for (int y = 0; y < ROWS; y++)
        {
            cells += session->mask[x][y] != 0;
        }
    }
    session->chain++;
    session->chain_total += (uint32_t)reward;
    if (session->power == POWER_NEED_THREE)
    {
        /* 0x451871: the first reward ends the state with the laser down sound */
        session->events |= VERTRIX_EVENT_LASER_DOWN;
        vertrix_session_end_power(session);
    }
    {
        uint8_t figures_mask[COLS][ROWS];
        int figure_reward = 0;
        if (vertrix_figure_pass(session->board, figures_mask, &figure_reward, 1))
        {
            session->events |= VERTRIX_EVENT_FIGURE;
        }
    }
    if (session->chain == 3 || session->chain == 6)
    {
        session->events |= VERTRIX_EVENT_CHAIN;
    }
    session->score = vertrix_score_add(session->score, cells, session->difficulty);
    level_progress(session, (uint32_t)reward);
    session->clear_timer = CLEAR_FLASH_MS;
    session->phase = session->won ? VERTRIX_PHASE_WON : VERTRIX_PHASE_CLEARING;
}

/* Tube controller handlers 0x450750, 0x4507e0 and 0x450830. */
static void gauge_controller(VertrixSession *session, uint32_t elapsed)
{
    if (session->gauge_phase == 1 || session->gauge_phase == 2)
    {
        session->gauge_wait += elapsed;
        if (session->gauge_wait < GAUGE_WAIT_MS)
        {
            return;
        }
        session->gauge_wait = 0;
        if (session->gauge_phase == 1)
        {
            session->gauge_shown = LEVEL_STEP;
        }
        session->gauge_phase = session->gauge_phase == 1 ? 2 : 0;
        return;
    }
    int32_t target = session->gauge_refill ? 0 : session->level_counter;
    session->gauge_timer += elapsed;
    if (session->gauge_timer >= GAUGE_STEP_MS)
    {
        session->gauge_timer = 0;
        if (session->gauge_shown > target)
        {
            session->gauge_shown--;
        }
    }
    if (session->gauge_refill && session->gauge_shown == target)
    {
        session->gauge_refill = 0;
        session->gauge_wait = 0;
        session->gauge_phase = 1;
    }
}

void vertrix_session_gauge(VertrixSession *session, uint32_t elapsed)
{
    if (session->alert_wait >= 0 && !session->paused)
    {
        session->alert_wait -= (int32_t)elapsed;
        if (session->alert_wait < 0)
        {
            session->events |= VERTRIX_EVENT_ALERT;
            session->alert_wait = -1;
        }
    }
    gauge_controller(session, elapsed);
    vertrix_value_flash_update(&session->level_flash, session->progress, elapsed);
    vertrix_value_flash_update(&session->speed_flash, session->level, elapsed);
    /* The controller's +0x58 is one only while it waits in 0x450830 (phase 2). */
    vertrix_gauge_tube_update(&session->tube, session->gauge_phase == 2,
                              (uint32_t)session->gauge_shown, elapsed);
}

void vertrix_session_update(VertrixSession *session, uint32_t elapsed)
{
    if (session->paused || session->phase == VERTRIX_PHASE_OVER ||
        session->phase == VERTRIX_PHASE_WON)
    {
        return;
    }
    if (session->power_left)
    {
        /* 0x43b8a0: the state ends when its timer is reached */
        if (elapsed >= session->power_left)
        {
            vertrix_session_end_power(session);
        }
        else
        {
            session->power_left -= elapsed;
        }
    }
    if (session->phase == VERTRIX_PHASE_INSERTING)
    {
        session->insert_timer += elapsed;
        if (session->insert_timer < column_slide_ms(session))
        {
            return;
        }
        if (session->piece.active)
        {
            vertrix_move_horizontal(session->board, 0, 0, &session->piece, 1);
        }
        for (int row = 0; row < ROWS; row++)
        {
            if (session->insert_column[row] == EMPTY)
            {
                continue;
            }
            for (int x = COLS - 1; x > 0; x--)
            {
                session->board[x][row] = session->board[x - 1][row];
            }
            session->board[0][row] = session->insert_column[row];
        }
        session->phase = VERTRIX_PHASE_PLAYING;
        return;
    }
    if (session->phase == VERTRIX_PHASE_RISING)
    {
        update_rising(session, elapsed);
        return;
    }
    if (session->phase == VERTRIX_PHASE_FROZEN)
    {
        session->freeze_left = elapsed >= session->freeze_left ? 0 : session->freeze_left - elapsed;
        if (session->freeze_left == 0)
        {
            session->phase = VERTRIX_PHASE_PLAYING;
        }
        return;
    }
    if (session->phase == VERTRIX_PHASE_MIXING)
    {
        /* 0x4548e0: every period of 12 * [0x4f7c54 + difficulty * 4] = 180 ms swaps one pair (the
         * quotient of the elapsed time) and plays enum 4; the run ends when no pair is left. */
        session->mix_timer += elapsed;
        while (session->mix_timer >= MIX_PERIOD_MS)
        {
            session->mix_timer -= MIX_PERIOD_MS;
            if (!mix_swap(session))
            {
                session->phase = VERTRIX_PHASE_PLAYING;
                memset(session->mix_marks, 0, sizeof session->mix_marks);
                return;
            }
            session->events |= VERTRIX_EVENT_LEVEL_REFILL;
        }
        return;
    }
    if (session->phase == VERTRIX_PHASE_CLEARING)
    {
        if (elapsed < session->clear_timer)
        {
            session->clear_timer -= elapsed;
            return;
        }
        for (int x = 0; x < COLS; x++)
        {
            for (int y = 0; y < ROWS; y++)
            {
                if (session->mask[x][y])
                {
                    session->board[x][y] = EMPTY;
                }
            }
        }
        board_collapse(session->board);
        memset(session->mask, 0, sizeof session->mask);
        resolve(session);
        return;
    }
    vertrix_descent_tick(session->board, 0, 0, &session->piece, &session->descent, elapsed, 0, 0,
                         0);
    if (!session->piece.active)
    {
        if (session->piece.failed)
        {
            session->phase = VERTRIX_PHASE_OVER;
            return;
        }
        resolve(session);
    }
}

/* The speed cases of the effect dispatcher 0x43c140 (id in dl, amount in bl): 2 exchanges the
 * speeds, 6 raises the opponent's by the amount (0x452880), 0x18 lowers the player's own
 * (0x452830). Returns 1 when the id is handled here. */
int vertrix_session_apply_speed_effect(VertrixSession *self, VertrixSession *opponent, int id,
                                       uint32_t amount)
{
    switch (id)
    {
        case 2:
            vertrix_session_exchange_speeds(self, opponent);
            return 1;
        case 6:
            vertrix_session_add_speed(opponent, (int32_t)amount);
            return 1;
        case 0x18:
            vertrix_session_add_speed(self, -(int32_t)amount);
            return 1;
        default:
            return 0;
    }
}

/* 0x4f9c14, 0x4f9c20, 0x4f9c2c: the duration in units of 12 ms, one per difficulty (0 to 2);
 * 0x4f9c38: one per [0x3fc] for the states 0x32 to 0x34. */
static const uint16_t POWER_STEPS_LONG = 4000;
static const uint16_t POWER_STEPS_MEDIUM = 3000;
static const uint16_t POWER_STEPS_SHORT = 1000;
static const uint16_t POWER_STEPS_SIZED[3] = {1000, 2000, 3000};

/* The starters that regenerate the preview after setting the state (0x43d260). */
static int power_regenerates(int id)
{
    return id == 0x22 || id == 0x23 || id == 0x28 || id == 0x29 || id == 0x2a || id == 0x2d ||
           id == 0x2e;
}

void vertrix_session_end_power(VertrixSession *session)
{
    session->power = 0;
    session->power_left = 0;
    session->threshold = MATCH_THRESHOLD;
    vertrix_piece(&session->random, 0, session->next);
}

int vertrix_session_start_power(VertrixSession *session, int id)
{
    uint32_t steps;
    if (id < 0x22 || id > 0x34 || (id >= 0x25 && id <= 0x27))
    {
        return 0;
    }
    if (session->power == (uint32_t)id)
    {
        return 0;
    }
    if (id >= 0x32)
    {
        steps = POWER_STEPS_SIZED[id - 0x32];
    }
    else if (id == 0x29)
    {
        steps = POWER_STEPS_MEDIUM;
    }
    else if (id == 0x2a)
    {
        steps = POWER_STEPS_SHORT;
    }
    else
    {
        steps = POWER_STEPS_LONG;
    }
    session->power_left = 12u * steps;
    session->power = (uint32_t)id;
    session->threshold = id == POWER_NEED_THREE ? 3 : MATCH_THRESHOLD;
    if (power_regenerates(id))
    {
        vertrix_piece(&session->random, session->power, session->next);
    }
    return 1;
}

int vertrix_session_apply_effect(VertrixSession *self, VertrixSession *target, int id,
                                 int parameter)
{
    switch (id)
    {
        case 2:
            vertrix_session_exchange_speeds(self, target);
            return 1;
        case 6:
            vertrix_session_add_speed(target, parameter);
            target->events |= VERTRIX_EVENT_LASER_UP;
            return 1;
        case 7:
            vertrix_session_start_mix(target, parameter);
            return 1;
        case 8:
            vertrix_session_start_freeze(target, parameter);
            return 1;
        case 9:
            vertrix_session_lower_level(target, (uint32_t)parameter);
            return 1;
        case 12:
            vertrix_session_random_speed(target);
            return 1;
        case 13:
            vertrix_session_start_column(target, 0);
            return 1;
        case 20:
            vertrix_session_start_column(target, parameter);
            return 1;
        case 14:
        case 15:
        case 16:
            vertrix_session_start_rows(target, (id - 14) * 3 + parameter - 1);
            return 1;
        case 19:
            vertrix_session_start_rows(target, 9 + parameter - 1);
            return 1;
        case 21:
            vertrix_session_start_rows(target, 12 + parameter - 1);
            return 1;
        case 22:
        {
            /* 0x453c00 receives 18, 19, 20, 22, 21, 23 for the parameters 1 to 6 */
            static const uint8_t group[6] = {18, 19, 20, 22, 21, 23};
            if (parameter >= 1 && parameter <= 6)
            {
                vertrix_session_start_rows(target, group[parameter - 1]);
            }
            return 1;
        }
        case 0x18:
            vertrix_session_add_speed(self, -parameter);
            self->events |= VERTRIX_EVENT_LASER_DOWN;
            return 1;
        default:
            break;
    }
    if (id >= 0x22 && id <= 0x34 && !(id >= 0x25 && id <= 0x27))
    {
        /* the harmful states go to the opponent, the helpful ones to the player (0x453620 on):
         * the first four also play the laser up sound for the player */
        static const uint8_t SELF[] = {0x22, 0x29, 0x2a, 0x2b, 0x30, 0x32, 0x33, 0x34};
        static const uint8_t SOUND[] = {0x22, 0x29, 0x2a, 0x30};
        VertrixSession *holder = target;
        for (unsigned i = 0; i < sizeof SELF; i++)
        {
            holder = id == SELF[i] ? self : holder;
        }
        if (holder->power != (uint32_t)id)
        {
            for (unsigned i = 0; i < sizeof SOUND; i++)
            {
                self->events |= id == SOUND[i] ? VERTRIX_EVENT_LASER_UP : 0;
            }
            vertrix_session_start_power(holder, id);
        }
        return 1;
    }
    return 0;
}
