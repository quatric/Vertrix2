#include "ai_player.h"

#include <string.h>

enum
{
    MIN_LEVEL = 2,
    ROTATIONS = 3,
    COLUMNS = VERTRIX_REACH_COLUMNS,
    ROWS_PER_COLUMN = VERTRIX_BOARD_ROWS,
    CELLS = COLUMNS * ROWS_PER_COLUMN,
    EMPTY_CELL = 0xff,
    BYTE_MASK = 0xff,
    WORD_MASK = 0xffff
};

int vertrix_ai_search_native(const uint8_t board[CELLS], uint32_t a, uint32_t b, uint32_t c,
                             uint32_t start, uint32_t row, uint32_t level, uint32_t *column,
                             uint32_t *rotation)
{
    const uint32_t colours[ROTATIONS][ROTATIONS] = {{a, c, b}, {b, a, c}, {c, b, a}};
    uint8_t reach[COLUMNS];
    uint8_t best[COLUMNS] = {0};
    uint8_t kind[COLUMNS] = {0};
    int failed = 1;
    if (level <= MIN_LEVEL || !vertrix_ai_row_reach(board, start, row, reach))
    {
        return 0;
    }
    for (uint32_t x = 0; x < COLUMNS; x++)
    {
        uint8_t cells[CELLS];
        int32_t cell = ROWS_PER_COLUMN - 1;
        uint32_t base = x * ROWS_PER_COLUMN;
        if (!reach[x])
        {
            continue;
        }
        memcpy(cells, board, sizeof cells);
        while (cell >= 0 && cells[base + (uint32_t)cell] != EMPTY_CELL)
        {
            cell--;
        }
        if (cell < 0)
        {
            continue;
        }
        for (uint32_t r = 0; r < ROTATIONS; r++)
        {
            uint8_t mask[CELLS];
            int reward;
            cells[base + (uint32_t)cell] = (uint8_t)colours[r][0];
            if (cell > 0)
            {
                cells[base + (uint32_t)cell - 1] = (uint8_t)colours[r][1];
            }
            if (cell > 1)
            {
                cells[base + (uint32_t)cell - 2] = (uint8_t)colours[r][2];
            }
            if (vertrix_figure_pass((uint8_t(*)[ROWS])cells, (uint8_t(*)[ROWS])mask, &reward, 0))
            {
                uint32_t word = (uint32_t)reward & WORD_MASK;
                failed = 0;
                if (word > best[x])
                {
                    best[x] = (uint8_t)(word & BYTE_MASK);
                    kind[x] = (uint8_t)r;
                }
            }
        }
    }
    if (failed)
    {
        return 0;
    }
    uint32_t chosen = 0;
    for (uint32_t x = 1; x < COLUMNS; x++)
    {
        if (best[x] > best[chosen])
        {
            chosen = x;
        }
    }
    *column = chosen;
    *rotation = kind[chosen];
    return 1;
}

enum
{
    FULL_HEIGHT = 13,
    CENTER = 2,
    CENTER_MIN_EMPTY = 3,
    OUTER_PAIRS = 2,
    ABSENT = 0xfe,
    TIE_DIVISOR = 2,
    KIND_DIVISOR = 3,
    PAIR_LEVEL = 1,
    NEIGHBOUR_LEVEL = 2,
    EXTRA_LEVEL = 4
};

/* One neighbour test: the colour of cell `colour` (a real colour: signed byte above -1) is looked
 * for among the piece's colours when cell `empty` is empty (0xff); the rotation is the colour's
 * position plus `shift`. */
typedef struct
{
    uint8_t condition;
    uint8_t empty;
    uint8_t value;
    uint8_t kinds[3];
    uint8_t extra;
} NeighbourTest;

/* Neighbour cells at the landing row r: the left column's rows r-3 .. r+1, then the right
 * column's. */
enum
{
    L3,
    L2,
    L1,
    L0,
    LP,
    R3,
    R2,
    R1,
    R0,
    RP,
    NEIGHBOUR_CELLS
};

/* Original 0x4263cb..0x4267a9 in order: the first test whose condition cell holds a colour while
 * its partner cell is empty (0xff) compares the value cell with the piece colours (the first
 * match decides, the rotation listed for it). Tests marked extra run only at level 4. */
static const NeighbourTest TESTS[] = {
    {L2, R2, L2, {0, 1, 2}, 0}, {R2, L2, R2, {0, 1, 2}, 0}, {L1, R1, L1, {2, 0, 1}, 0},
    {R1, L1, R1, {2, 0, 1}, 0}, {L0, R0, L0, {1, 2, 0}, 0}, {R1, L1, R0, {1, 2, 0}, 0},
    {L3, R1, L3, {0, 1, 2}, 1}, {R1, L3, R1, {0, 1, 2}, 1}, {L2, R0, L2, {2, 0, 1}, 1},
    {R0, L2, R0, {2, 0, 1}, 1}, {L1, RP, L1, {1, 2, 0}, 1}, {RP, L1, RP, {1, 2, 0}, 1},
    {R3, L1, R3, {0, 1, 2}, 1}, {L1, R3, L1, {0, 1, 2}, 1}, {R2, L0, R2, {2, 0, 1}, 1},
    {L0, R2, L0, {2, 0, 1}, 1}, {R1, LP, R1, {1, 2, 0}, 1}, {LP, R1, LP, {1, 2, 0}, 1}};

static int is_colour(uint8_t value)
{
    return (int8_t)value > -1;
}

int vertrix_ai_fallback(const uint8_t board[CELLS], uint32_t p0, uint32_t p1, uint32_t p2,
                        uint32_t start, uint32_t row, uint32_t level, uint32_t *previous,
                        VertrixAiRandom random, void *context, uint32_t *column, uint32_t *rotation)
{
    uint8_t reach[COLUMNS];
    uint8_t heights[COLUMNS];
    const uint32_t piece[3] = {p0, p1, p2};
    uint32_t viable = 0, chosen, kind = 0xffffffffu;
    if (!vertrix_ai_row_reach(board, start, row, reach))
    {
        return 0;
    }
    for (uint32_t x = 0; x < COLUMNS; x++)
    {
        uint32_t empty = 0;
        heights[x] = FULL_HEIGHT;
        if (!reach[x])
        {
            continue;
        }
        while (empty < ROWS_PER_COLUMN && board[x * ROWS_PER_COLUMN + empty] == EMPTY_CELL)
        {
            empty++;
        }
        heights[x] = (uint8_t)(FULL_HEIGHT - empty);
        if (x == CENTER && empty <= CENTER_MIN_EMPTY)
        {
            heights[x] = FULL_HEIGHT;
        }
        else if (heights[x] != FULL_HEIGHT)
        {
            viable++;
        }
    }
    if (!viable)
    {
        chosen = CENTER;
    }
    else
    {
        uint32_t best = 0, left = 0, right = COLUMNS - 1;
        uint32_t low;
        int32_t pick = -1;
        while (heights[best] == FULL_HEIGHT)
        {
            best++;
        }
        low = heights[best];
        for (uint32_t x = best + 1; x < COLUMNS; x++)
        {
            if (reach[x] && heights[x] < low)
            {
                best = x;
                low = heights[x];
            }
        }
        for (; pick == -1 && left < OUTER_PAIRS; left++, right--)
        {
            int tie = 0;
            if (heights[left] == low)
            {
                pick = (int32_t)left;
            }
            if (heights[right] == low)
            {
                if (pick == -1)
                {
                    pick = (int32_t)right;
                }
                else
                {
                    tie = 1;
                }
            }
            if (tie)
            {
                if (right == *previous)
                {
                    pick = (int32_t)*previous;
                }
                else if (left != *previous && random(context, TIE_DIVISOR) == 1)
                {
                    pick = (int32_t)right;
                }
            }
        }
        if (pick == -1 && best == CENTER)
        {
            pick = CENTER;
        }
        *previous = (uint32_t)pick;
        chosen = (uint32_t)pick;
    }
    if (level > PAIR_LEVEL)
    {
        if (p0 == p1)
        {
            kind = 0;
        }
        else if (p1 == p2)
        {
            kind = 1;
        }
        else if (p2 == p0)
        {
            kind = 2;
        }
    }
    if (kind == 0xffffffffu && level > NEIGHBOUR_LEVEL)
    {
        int32_t r = (int32_t)ROWS_PER_COLUMN - 1 - (int32_t)heights[chosen];
        if (r > NEIGHBOUR_LEVEL)
        {
            uint8_t cells[NEIGHBOUR_CELLS];
            for (int i = 0; i < NEIGHBOUR_CELLS; i++)
            {
                cells[i] = ABSENT;
            }
            if (chosen != 0)
            {
                const uint8_t *left = board + (chosen - 1) * ROWS_PER_COLUMN;
                cells[L2] = left[r - 2];
                cells[L1] = left[r - 1];
                cells[L0] = left[r];
                if (r > 3)
                {
                    cells[L3] = left[r - 3];
                }
                if (r < ROWS_PER_COLUMN - 1)
                {
                    cells[LP] = left[r + 1];
                }
            }
            if (chosen != COLUMNS - 1)
            {
                const uint8_t *right = board + (chosen + 1) * ROWS_PER_COLUMN;
                cells[R2] = right[r - 2];
                cells[R1] = right[r - 1];
                cells[R0] = right[r];
                if (r > 3)
                {
                    cells[R3] = right[r - 3];
                }
            }
            for (size_t t = 0; kind == 0xffffffffu && t < sizeof TESTS / sizeof TESTS[0]; t++)
            {
                const NeighbourTest *test = &TESTS[t];
                if ((test->extra && level != EXTRA_LEVEL) || !is_colour(cells[test->condition]) ||
                    cells[test->empty] != EMPTY_CELL || !is_colour(cells[test->value]))
                {
                    continue;
                }
                for (uint32_t i = 0; i < 3; i++)
                {
                    if ((uint32_t)(int32_t)(int8_t)cells[test->value] == piece[i])
                    {
                        kind = test->kinds[i];
                        break;
                    }
                }
            }
        }
    }
    if (kind == 0xffffffffu)
    {
        kind = random(context, KIND_DIVISOR);
    }
    *column = chosen;
    *rotation = kind;
    return 1;
}

static int mask_sum(const uint8_t mask[CELLS])
{
    int sum = 0;
    for (int i = 0; i < CELLS; i++)
    {
        sum += mask[i];
    }
    return sum;
}

static int line_found(const uint8_t cells[CELLS], uint8_t mask[CELLS], uint32_t threshold)
{
    int reward = 0;
    return vertrix_line_pass((const uint8_t(*)[ROWS_PER_COLUMN])cells,
                             (uint8_t(*)[ROWS_PER_COLUMN])mask, (int)(threshold & BYTE_MASK),
                             &reward);
}

static void remove_marked(uint8_t cells[CELLS], const uint8_t mask[CELLS])
{
    for (int i = 0; i < CELLS; i++)
    {
        if (mask[i] == 1)
        {
            cells[i] = EMPTY_CELL;
        }
    }
}

/* Piece colours from the bottom up for each rotation: the cell at the landing row, the one above
 * and the one above that (original 0x426b86 and its replays). */
static void place_rotation(uint8_t cells[CELLS], uint32_t base, int32_t row, uint32_t rotation,
                           const uint32_t piece[3])
{
    static const uint8_t ORDER[ROTATIONS][ROTATIONS] = {{2, 1, 0}, {0, 2, 1}, {1, 0, 2}};
    cells[base + (uint32_t)row] = (uint8_t)piece[ORDER[rotation][0]];
    if (row > 0)
    {
        cells[base + (uint32_t)row - 1] = (uint8_t)piece[ORDER[rotation][1]];
    }
    if (row > 1)
    {
        cells[base + (uint32_t)row - 2] = (uint8_t)piece[ORDER[rotation][2]];
    }
}

int vertrix_ai_chain_search(const uint8_t board[CELLS], uint32_t p0, uint32_t p1, uint32_t p2,
                            uint32_t threshold, uint32_t start, uint32_t row, uint32_t level,
                            uint32_t *column, uint32_t *rotation)
{
    const uint32_t piece[3] = {p0, p1, p2};
    uint8_t reach[COLUMNS];
    uint8_t best[COLUMNS] = {0};
    uint8_t kind[COLUMNS] = {0};
    uint8_t second[COLUMNS] = {0};
    uint8_t third[COLUMNS] = {0};
    int none = 1;
    int32_t chosen = -1;
    int32_t pick = -1;
    int32_t score = -1;
    if (!vertrix_ai_row_reach(board, start, row, reach))
    {
        return 0;
    }
    for (uint32_t x = 0; x < COLUMNS; x++)
    {
        uint8_t cells[CELLS];
        uint8_t mask[CELLS];
        uint32_t base = x * ROWS_PER_COLUMN;
        int32_t landing = ROWS_PER_COLUMN - 1;
        if (!reach[x])
        {
            continue;
        }
        memcpy(cells, board, sizeof cells);
        while (landing >= 0 && cells[base + (uint32_t)landing] != EMPTY_CELL)
        {
            landing--;
        }
        if (landing < 0)
        {
            continue;
        }
        for (uint32_t r = 0; r < ROTATIONS; r++)
        {
            int sum;
            place_rotation(cells, base, landing, r, piece);
            memset(mask, 0, sizeof mask);
            if (line_found(cells, mask, threshold))
            {
                sum = mask_sum(mask);
                if (sum > best[x])
                {
                    best[x] = (uint8_t)sum;
                    none = 0;
                    kind[x] = (uint8_t)r;
                }
            }
        }
        if (best[x] == 0 || level <= MIN_LEVEL)
        {
            continue;
        }
        memcpy(cells, board, sizeof cells);
        place_rotation(cells, base, landing, kind[x], piece);
        memset(mask, 0, sizeof mask);
        line_found(cells, mask, threshold);
        remove_marked(cells, mask);
        board_collapse((uint8_t(*)[ROWS_PER_COLUMN])cells);
        memset(mask, 0, sizeof mask);
        if (!line_found(cells, mask, threshold))
        {
            continue;
        }
        second[x] = (uint8_t)mask_sum(mask);
        if (level != EXTRA_LEVEL)
        {
            continue;
        }
        remove_marked(cells, mask);
        board_collapse((uint8_t(*)[ROWS_PER_COLUMN])cells);
        memset(mask, 0, sizeof mask);
        while (line_found(cells, mask, threshold))
        {
            third[x] = (uint8_t)(third[x] + mask_sum(mask));
            remove_marked(cells, mask);
            board_collapse((uint8_t(*)[ROWS_PER_COLUMN])cells);
        }
    }
    if (none)
    {
        return 0;
    }
    if (level == EXTRA_LEVEL)
    {
        for (int32_t x = 0; x < COLUMNS; x++)
        {
            int32_t total = third[x] + second[x] + best[x];
            if (third[x] != 0 && total > score)
            {
                score = total;
                pick = x;
            }
        }
    }
    if (pick == -1 && level > MIN_LEVEL)
    {
        for (int32_t x = 0; x < COLUMNS; x++)
        {
            int32_t total = second[x] + best[x];
            if (second[x] != 0 && total > score)
            {
                score = total;
                pick = x;
            }
        }
    }
    if (pick == -1 && level > PAIR_LEVEL)
    {
        chosen = 0;
        for (int32_t x = 1; x < COLUMNS; x++)
        {
            if (best[x] > best[chosen])
            {
                chosen = x;
            }
        }
    }
    else
    {
        for (int32_t left = 0, right = COLUMNS - 1; chosen == -1 && left < OUTER_PAIRS;
             left++, right--)
        {
            if (best[left] > 0)
            {
                chosen = left;
            }
            else if (best[right] > 0)
            {
                chosen = right;
            }
        }
        if (chosen == -1)
        {
            chosen = CENTER;
        }
    }
    *column = (uint32_t)chosen;
    *rotation = kind[chosen];
    return 1;
}

enum
{
    STONE_CELL = 5,
    BOMB_CELL = 6,
    FEWEST_MODE = 0x23,
    FEWEST_START = 10000,
    HEIGHT_COLUMN = 2,
    HEIGHT_LIMIT = 8,
    STONE_WEIGHT_LEVEL = 2
};

/* Original 0x434300 (and 0x4344e0, which is its total): every bomb marks its whole row (patterns
 * 1, 3 and 4), its whole column (2, 3 and 4) and, for pattern 4, the two neighbouring columns;
 * the marked cells that are not empty count in *total and the stones among them in *stones. */
static void blast_estimate(const uint8_t board[CELLS], uint8_t pattern, int *stones, int *total)
{
    uint8_t mask[CELLS] = {0};
    *stones = 0;
    *total = 0;
    for (uint32_t x = 0; x < COLUMNS; x++)
    {
        for (uint32_t y = 0; y < ROWS_PER_COLUMN; y++)
        {
            if (board[x * ROWS_PER_COLUMN + y] != BOMB_CELL)
            {
                continue;
            }
            if (pattern == 1 || pattern == 3 || pattern == 4)
            {
                for (uint32_t k = 0; k < COLUMNS; k++)
                {
                    mask[k * ROWS_PER_COLUMN + y] = 1;
                }
            }
            if (pattern == 2 || pattern == 3 || pattern == 4)
            {
                memset(mask + x * ROWS_PER_COLUMN, 1, ROWS_PER_COLUMN);
            }
            if (pattern == 4)
            {
                if (x > 0)
                {
                    memset(mask + (x - 1) * ROWS_PER_COLUMN, 1, ROWS_PER_COLUMN);
                }
                if (x < COLUMNS - 1)
                {
                    memset(mask + (x + 1) * ROWS_PER_COLUMN, 1, ROWS_PER_COLUMN);
                }
            }
        }
    }
    for (int i = 0; i < CELLS; i++)
    {
        if (mask[i] == 1 && board[i] != EMPTY_CELL)
        {
            (*total)++;
            if (board[i] == STONE_CELL)
            {
                (*stones)++;
            }
        }
    }
}

int vertrix_ai_bomb_search(const uint8_t board[CELLS], uint32_t p0, uint32_t p1, uint32_t p2,
                           uint32_t start, uint32_t row, uint32_t level, int32_t pattern,
                           uint32_t mode, uint32_t *column, uint32_t *rotation)
{
    const uint32_t piece[3] = {p0, p1, p2};
    uint8_t reach[COLUMNS];
    int32_t best_column = 0;
    uint32_t best_kind = 0;
    int32_t best = 0;
    if (level <= PAIR_LEVEL || (p0 != BOMB_CELL && p1 != BOMB_CELL && p2 != BOMB_CELL))
    {
        return 0;
    }
    if (mode != FEWEST_MODE)
    {
        uint8_t byte = (uint8_t)pattern;
        if (byte == 2 || byte == 3)
        {
            const uint8_t *centre = board + HEIGHT_COLUMN * ROWS_PER_COLUMN;
            int32_t top = ROWS_PER_COLUMN - 1;
            int bomb = 0;
            if (centre[top] != EMPTY_CELL)
            {
                do
                {
                    if (centre[top] == BOMB_CELL)
                    {
                        bomb = 1;
                    }
                    top--;
                } while (top >= 0 && centre[top] != EMPTY_CELL);
            }
            if (!bomb && top > -1 && ROWS_PER_COLUMN - 1 - top > HEIGHT_LIMIT)
            {
                *column = HEIGHT_COLUMN;
                *rotation = 0;
                return 1;
            }
        }
    }
    if (!vertrix_ai_row_reach(board, start, row, reach))
    {
        return 0;
    }
    if (mode == FEWEST_MODE)
    {
        best = FEWEST_START;
    }
    for (uint32_t x = 0; x < COLUMNS; x++)
    {
        uint8_t cells[CELLS];
        uint32_t base = x * ROWS_PER_COLUMN;
        int32_t landing = ROWS_PER_COLUMN - 1;
        if (!reach[x])
        {
            continue;
        }
        memcpy(cells, board, sizeof cells);
        while (landing >= 0 && cells[base + (uint32_t)landing] != EMPTY_CELL)
        {
            landing--;
        }
        if (landing < 0)
        {
            continue;
        }
        for (uint32_t r = 0; r < ROTATIONS; r++)
        {
            int32_t score;
            int stones = 0;
            int total = 0;
            place_rotation(cells, base, landing, r, piece);
            blast_estimate(cells, (uint8_t)pattern, &stones, &total);
            if (mode == FEWEST_MODE)
            {
                score = total;
                if (score < best)
                {
                    best = score;
                    best_column = (int32_t)x;
                    best_kind = r;
                }
                continue;
            }
            score = level > STONE_WEIGHT_LEVEL ? stones * 2 + total : total;
            if (score > best)
            {
                best = score;
                best_column = (int32_t)x;
                best_kind = r;
            }
        }
    }
    *column = (uint32_t)best_column;
    *rotation = best_kind;
    return 1;
}

int vertrix_ai_plan(const uint8_t board[CELLS], uint32_t c1, uint32_t c2, uint32_t c3,
                    uint32_t start, uint32_t row, const VertrixAiSettings *settings,
                    uint32_t *previous, VertrixAiRandom random, void *context, uint32_t *column,
                    uint32_t *rotation)
{
    int found = 0;
    if (settings->pattern != 0)
    {
        found = vertrix_ai_bomb_search(board, c1, c2, c3, start, row, settings->level,
                                       settings->pattern, settings->mode, column, rotation);
    }
    if (!found)
    {
        found = vertrix_ai_search_native(board, c3, c1, c2, start, row, settings->level, column,
                                         rotation);
    }
    if (!found)
    {
        found = vertrix_ai_chain_search(board, c1, c2, c3, settings->threshold, start, row,
                                        settings->level, column, rotation);
    }
    if (!found)
    {
        found = vertrix_ai_fallback(board, c1, c2, c3, start, row, settings->level, previous,
                                    random, context, column, rotation);
    }
    return found;
}

void vertrix_ai_steer(uint32_t level, int32_t current, int32_t target, uint32_t *rotations_left,
                      int dropping, VertrixAiKeys *keys)
{
    memset(keys, 0, sizeof *keys);
    if (level == EXTRA_LEVEL)
    {
        keys->left = current > target;
        keys->right = current < target;
        if (*rotations_left > 0)
        {
            (*rotations_left)--;
            keys->permute = 1;
        }
        else if (current == target && !dropping)
        {
            keys->drop = 1;
        }
        return;
    }
    if (level != 3 && *rotations_left > 0)
    {
        (*rotations_left)--;
        keys->permute = 1;
        return;
    }
    if (current > target)
    {
        keys->left = 1;
    }
    else if (current < target)
    {
        keys->right = 1;
    }
    else if (*rotations_left > 0)
    {
        (*rotations_left)--;
        keys->permute = 1;
    }
    else if (!dropping)
    {
        keys->drop = 1;
    }
}
