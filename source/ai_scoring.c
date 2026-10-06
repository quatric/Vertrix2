#include "ai_scoring.h"

enum
{
    EMPTY = 0xff,
    STONE = 5,
    BOMB = 6,
    TALL_HEIGHT = 6,
    LEVEL_OPEN = 4,
    RECORD_HEADER = 5,
    RECORD_SIZE = 5
};

typedef struct
{
    uint32_t cells;
    uint32_t stones;
    uint32_t bombs;
    uint32_t tall_columns;
    uint32_t edge_weight;
} BoardCounts;

/* Column height: 13 minus the leading empty cells. */
static int column_height(const uint8_t *column)
{
    int empty = 0;
    while (empty < VERTRIX_SCORE_ROWS && column[empty] == EMPTY)
    {
        ++empty;
    }
    return VERTRIX_SCORE_ROWS - empty;
}

/* Top-row distance score (0x42827e..0x4282e8): columns 1 and 0 from the right, then 3 and 4 from
 * the left, each stopping at the first occupied top cell. */
static uint32_t edge_weight(const uint8_t *board)
{
    uint32_t weight = 0;
    for (int column = 1; column >= 0; --column)
    {
        if (board[column * VERTRIX_SCORE_ROWS] != EMPTY)
        {
            weight += (uint32_t)column + 1;
            break;
        }
    }
    for (int column = 3; column < VERTRIX_SCORE_COLUMNS; ++column)
    {
        if (board[column * VERTRIX_SCORE_ROWS] != EMPTY)
        {
            weight += (uint32_t)(VERTRIX_SCORE_COLUMNS - column);
            break;
        }
    }
    return weight;
}

/* Level of a count against rising thresholds t1 < t2 < t3 (0 below the first). */
static uint8_t level_of(uint32_t count, uint32_t first, uint32_t second, uint32_t third,
                        uint32_t fourth)
{
    if (count < first)
    {
        return 0;
    }
    if (count < second)
    {
        return 1;
    }
    if (count < third)
    {
        return 2;
    }
    if (count < fourth)
    {
        return 3;
    }
    return 4;
}

static uint8_t stone_level(uint32_t stones)
{
    if (stones == 0)
    {
        return 0;
    }
    return level_of(stones, 0, 7, 15, 20);
}

static uint8_t tall_level(uint32_t edge, uint32_t tall)
{
    if (edge != 0)
    {
        return LEVEL_OPEN;
    }
    if (tall == 0)
    {
        return 0;
    }
    if (tall < 3)
    {
        return 1;
    }
    if (tall < 5)
    {
        return 2;
    }
    return 3;
}

static uint8_t bomb_level(uint32_t bombs)
{
    if (bombs <= 3)
    {
        return (uint8_t)bombs;
    }
    return LEVEL_OPEN;
}

static uint8_t positive_difference(uint32_t high, uint32_t low)
{
    return high > low ? (uint8_t)(high - low) : 0;
}

void vertrix_ai_compare_boards(const uint8_t a[VERTRIX_SCORE_CELLS],
                               const uint8_t b[VERTRIX_SCORE_CELLS], uint8_t player_level,
                               uint8_t out[VERTRIX_COMPARE_SIZE])
{
    BoardCounts count_a = {0, 0, 0, 0, 0};
    BoardCounts count_b = {0, 0, 0, 0, 0};
    for (int column = 0; column < VERTRIX_SCORE_COLUMNS; ++column)
    {
        if (column_height(&a[column * VERTRIX_SCORE_ROWS]) > TALL_HEIGHT)
        {
            ++count_a.tall_columns;
        }
        if (column_height(&b[column * VERTRIX_SCORE_ROWS]) > TALL_HEIGHT)
        {
            ++count_b.tall_columns;
        }
    }
    for (int i = 0; i < VERTRIX_SCORE_CELLS; ++i)
    {
        count_a.cells += a[i] != EMPTY;
        count_b.cells += b[i] != EMPTY;
        count_a.stones += a[i] == STONE;
        count_b.stones += b[i] == STONE;
        count_a.bombs += a[i] == BOMB;
    }
    count_a.edge_weight = edge_weight(a);
    count_b.edge_weight = edge_weight(b);
    uint8_t fill_a = level_of(count_a.cells, 13, 20, 26, 39);
    uint8_t fill_b = level_of(count_b.cells, 13, 20, 26, 39);
    out[0] = fill_a;
    out[5] = fill_b;
    out[0xa] = positive_difference(fill_a, fill_b);
    uint8_t tall_a = tall_level(count_a.edge_weight, count_a.tall_columns);
    uint8_t tall_b = tall_level(count_b.edge_weight, count_b.tall_columns);
    out[2] = tall_a;
    out[7] = tall_b;
    out[0xc] = positive_difference(tall_a, tall_b);
    uint8_t stones_a = stone_level(count_a.stones);
    uint8_t stones_b = stone_level(count_b.stones);
    out[3] = stones_a;
    out[8] = stones_b;
    out[0xd] = positive_difference(stones_a, stones_b);
    uint8_t bombs = bomb_level(count_a.bombs);
    out[4] = bombs;
    out[9] = stones_b;
    out[0xe] = positive_difference(bombs, stones_b);
    out[0x10] = a[0x1a] != EMPTY ? LEVEL_OPEN : 0;
    out[0x11] = b[0x1a] != EMPTY ? LEVEL_OPEN : 0;
    if (player_level == 0)
    {
        out[0x12] = b[0xd] != EMPTY ? LEVEL_OPEN : 0;
    }
    else
    {
        out[0x12] = b[0x27] != EMPTY ? LEVEL_OPEN : 0;
    }
}

typedef struct
{
    uint8_t sum[VERTRIX_RECORD_SCORE_SLOTS];
    uint8_t count[VERTRIX_RECORD_SCORE_SLOTS];
    int found;
    uint32_t smallest;
} RecordState;

/* One record (0x428660..0x4286b4). Returns zero for a slot outside the sums. */
static int apply_record(RecordState *state, const uint8_t *record, const uint8_t table[256])
{
    uint8_t slot = record[0];
    uint8_t looked = table[record[1]];
    uint8_t kind = record[2];
    uint32_t rank = record[3];
    if (kind >= 2 && kind <= 5)
    {
        if (slot >= VERTRIX_RECORD_SCORE_SLOTS)
        {
            return 0;
        }
        if (kind == 2)
        {
            state->sum[slot] = (uint8_t)(state->sum[slot] + looked);
        }
        else if (kind == 3)
        {
            state->sum[slot] = (uint8_t)(state->sum[slot] - looked);
        }
        else if (kind == 4)
        {
            state->sum[slot] = (uint8_t)(state->sum[slot] + 4 - looked);
        }
        else
        {
            state->sum[slot] = (uint8_t)(looked + state->sum[slot] - 4);
        }
        state->count[slot] = (uint8_t)(state->count[slot] + 1);
    }
    else if ((kind == 0 && looked == 4) || (kind == 1 && looked == 0))
    {
        if (!state->found || rank < state->smallest)
        {
            state->smallest = rank;
        }
        state->found = 1;
    }
    return 1;
}

/* Combine the averaged slot sums (0x4286b6..0x4288c6). */
static int32_t combine_slots(RecordState *state, uint32_t mode)
{
    int first = 0;
    int32_t accumulator = 0;
    while (first < VERTRIX_RECORD_SCORE_SLOTS && state->count[first] == 0)
    {
        ++first;
    }
    if (first == VERTRIX_RECORD_SCORE_SLOTS)
    {
        return 0;
    }
    for (int i = first; i < VERTRIX_RECORD_SCORE_SLOTS; ++i)
    {
        if (state->count[i] > 0)
        {
            state->sum[i] = (uint8_t)((int32_t)(int8_t)state->sum[i] / (int32_t)state->count[i]);
        }
    }
    if (mode == 2)
    {
        int32_t used = 0;
        for (int i = first; i < VERTRIX_RECORD_SCORE_SLOTS; ++i)
        {
            if (state->count[i] > 0)
            {
                accumulator += (int32_t)(int8_t)state->sum[i] * 2;
                ++used;
            }
        }
        return used > 0 ? accumulator / used : accumulator;
    }
    if (mode > 1)
    {
        return 0;
    }
    accumulator = (int8_t)state->sum[first];
    for (int i = first + 1; i < VERTRIX_RECORD_SCORE_SLOTS; ++i)
    {
        int32_t value = (int8_t)state->sum[i];
        if (mode == 0 ? value > accumulator : value < accumulator)
        {
            accumulator = value;
        }
    }
    return accumulator * 2;
}

int vertrix_ai_record_score(const uint8_t *data, const uint8_t table[256], uint32_t max_limit,
                            int32_t *score)
{
    RecordState state = {{0}, {0}, 0, 0};
    for (uint32_t i = 0; i < data[1]; ++i)
    {
        const uint8_t *record = &data[RECORD_HEADER + RECORD_SIZE * i];
        if (max_limit >= record[4] && !apply_record(&state, record, table))
        {
            return 0;
        }
    }
    *score = state.found ? (int32_t)(2 * state.smallest) : combine_slots(&state, data[0]);
    return 1;
}
