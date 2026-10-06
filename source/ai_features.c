#include "ai_features.h"

enum
{
    BLOCKING_ROW_LIMIT = 10,
    ENABLED = 1,
    SCORE_ROWS = 7,
    MODE_THRESHOLD = 2
};

/* Table at 0x4fb6c0: rows scored by averaging for modes up to 2. */
static const uint8_t averaged_rows[SCORE_ROWS] = {1, 1, 1, 1, 0, 0, 1};

int vertrix_ai_row_reach(const uint8_t cells[VERTRIX_REACH_COLUMNS * VERTRIX_BOARD_ROWS],
                         uint32_t start, uint32_t row, uint8_t reach[VERTRIX_REACH_COLUMNS])
{
    if (start > VERTRIX_REACH_COLUMNS || row >= VERTRIX_BOARD_ROWS)
    {
        return 0;
    }
    for (int i = 0; i < VERTRIX_REACH_COLUMNS; ++i)
    {
        reach[i] = 1;
    }
    for (int column = (int)start - 1; column >= 0; --column)
    {
        if (row < BLOCKING_ROW_LIMIT && cells[column * VERTRIX_BOARD_ROWS + row] != 0xff)
        {
            for (int blocked = column; blocked >= 0; --blocked)
            {
                reach[blocked] = 0;
            }
            break;
        }
    }
    for (int column = (int)start + 1; column < VERTRIX_REACH_COLUMNS; ++column)
    {
        if (row < BLOCKING_ROW_LIMIT && cells[column * VERTRIX_BOARD_ROWS + row] != 0xff)
        {
            for (int blocked = column; blocked < VERTRIX_REACH_COLUMNS; ++blocked)
            {
                reach[blocked] = 0;
            }
            break;
        }
    }
    return 1;
}

/* First feature (0x427c10..0x427c29): how the first pair of operands relate. */
static uint8_t pair_feature(uint32_t a, uint32_t g)
{
    if (a < g)
    {
        return 0;
    }
    if (a == 9 && g == a)
    {
        return 0;
    }
    if (a == g)
    {
        return 1;
    }
    if (g == a + 1)
    {
        return 2;
    }
    if (g == a + 2)
    {
        return 3;
    }
    return 4;
}

static uint8_t shape_feature(uint32_t b)
{
    if (b == 9 || b < 4)
    {
        return 0;
    }
    if (b == 8)
    {
        return 4;
    }
    if (b == 5)
    {
        return 2;
    }
    if (b == 4)
    {
        return 1;
    }
    return 3;
}

static uint8_t gap_feature(int32_t gap)
{
    if (gap <= 0)
    {
        return 0;
    }
    if (gap > 6)
    {
        return 4;
    }
    if (gap > 4)
    {
        return 3;
    }
    if (gap > 2)
    {
        return 2;
    }
    return 1;
}

static int32_t offset_by(int32_t value, uint32_t amount)
{
    return (int32_t)((uint32_t)value + amount);
}

/* The two threshold cascades (0x427d73 and 0x427c6a): only the first and last results can occur
 * because the middle tests follow a failed lower test, but the original order is kept. */
static uint8_t step_cascade(int32_t high, int32_t low)
{
    if (high > offset_by(low, 0xc))
    {
        return 1;
    }
    if (high > offset_by(low, 0x18))
    {
        return 2;
    }
    if (high > offset_by(low, 0x24))
    {
        return 3;
    }
    return 4;
}

void vertrix_ai_features(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint32_t e, uint32_t f,
                         uint32_t g, uint8_t out[VERTRIX_AI_FEATURE_SIZE])
{
    int32_t first = (int32_t)(12 * c + e);
    int32_t second = (int32_t)(12 * d + f);
    out[VERTRIX_AI_FEATURE_PAIR] = pair_feature(a, g);
    out[VERTRIX_AI_FEATURE_SHAPE] = shape_feature(b);
    out[VERTRIX_AI_FEATURE_GAP] = gap_feature((int32_t)(a - b));
    if (c < d)
    {
        out[VERTRIX_AI_FEATURE_STEP] = step_cascade(second, first);
        out[VERTRIX_AI_FEATURE_REACH] = 0;
    }
    else
    {
        out[VERTRIX_AI_FEATURE_STEP] = 0;
        out[VERTRIX_AI_FEATURE_REACH] = d >= c ? 0 : step_cascade(first, second);
    }
}

typedef struct
{
    uint8_t flag;
    uint8_t mode;
} ModeFlag;

/* Own mode tests (0x427e10) and opponent mode tests, in flag byte order. */
static const ModeFlag own_flags[] = {{0x13, 0x22}, {0x14, 0x23}, {0x15, 0x2b}, {0x16, 0x29},
                                     {0x17, 0x2a}, {0x18, 0x2c}, {0x19, 0x28}, {0x1a, 0x2d},
                                     {0x1b, 0x2e}, {0x27, 0x31}, {0x28, 0x30}, {0x29, 0x2f}};
static const ModeFlag opponent_flags[] = {{0x1c, 0x22}, {0x1d, 0x23}, {0x1e, 0x2b}, {0x1f, 0x29},
                                          {0x20, 0x2a}, {0x21, 0x2c}, {0x22, 0x24}, {0x23, 0x28},
                                          {0x24, 0x2d}, {0x25, 0x2e}, {0x2b, 0x31}, {0x2c, 0x30},
                                          {0x2d, 0x2f}};
enum
{
    FLAG_ON = 4,
    OWN_GROUP_FLAG = 0x2a,
    OPPONENT_GROUP_FLAG = 0x2e,
    GROUP_FIRST = 0x32,
    GROUP_LAST = 0x34
};

static void apply_flags(const ModeFlag *table, int count, uint32_t mode,
                        uint8_t flags[VERTRIX_AI_MODE_FLAGS_SIZE])
{
    for (int i = 0; i < count; ++i)
    {
        flags[table[i].flag] = mode == table[i].mode ? FLAG_ON : 0;
    }
}

void vertrix_ai_mode_flags(uint32_t own_mode, uint32_t opponent_mode,
                           uint8_t flags[VERTRIX_AI_MODE_FLAGS_SIZE])
{
    apply_flags(own_flags, (int)(sizeof own_flags / sizeof own_flags[0]), own_mode, flags);
    flags[OWN_GROUP_FLAG] = own_mode >= GROUP_FIRST && own_mode <= GROUP_LAST ? FLAG_ON : 0;
    apply_flags(opponent_flags, (int)(sizeof opponent_flags / sizeof opponent_flags[0]),
                opponent_mode, flags);
    flags[OPPONENT_GROUP_FLAG] =
        opponent_mode >= GROUP_FIRST && opponent_mode <= GROUP_LAST ? FLAG_ON : 0;
}

static uint8_t row_score(const VertrixChoiceGrid *grid, uint32_t row, uint32_t mode)
{
    uint32_t first = 0;
    const uint32_t *values = &grid->values[row * VERTRIX_CHOICE_COLUMNS];
    const uint8_t *weights = &grid->first_bytes[row * VERTRIX_CHOICE_COLUMNS];
    while (first < VERTRIX_CHOICE_COLUMNS && values[first] == 0)
    {
        ++first;
    }
    if (first == VERTRIX_CHOICE_COLUMNS)
    {
        return 0;
    }
    if (mode > MODE_THRESHOLD || !averaged_rows[row])
    {
        uint32_t best = weights[first];
        for (uint32_t i = first + 1; i < VERTRIX_CHOICE_COLUMNS; ++i)
        {
            if (values[i] == ENABLED && weights[i] > best)
            {
                best = weights[i];
            }
        }
        return (uint8_t)best;
    }
    uint8_t sum = 0;
    int32_t count = 0;
    for (uint32_t i = 0; i < VERTRIX_CHOICE_COLUMNS; ++i)
    {
        if (values[i] == ENABLED)
        {
            sum = (uint8_t)(sum + weights[i]);
            ++count;
        }
    }
    if (count == 0)
    {
        return 0;
    }
    return (uint8_t)((int32_t)(int8_t)sum / count);
}

int vertrix_ai_choice_scores(const VertrixChoiceGrid *grid, uint32_t mode, uint8_t scores[7])
{
    for (uint32_t row = 0; row < SCORE_ROWS; ++row)
    {
        scores[row] = row_score(grid, row, mode);
    }
    for (int i = 0; i < VERTRIX_CHOICE_CELLS; ++i)
    {
        if (grid->values[i] == ENABLED && grid->first_bytes[i] != 0)
        {
            return 1;
        }
    }
    return 0;
}
