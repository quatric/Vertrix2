#include "board_tiles.h"
#include "actor_storage.h"

enum
{
    GRID_COLUMN_STRIDE = VERTRIX_TILE_ROWS,
    OUTPUT_COLUMN_STRIDE = 52,
    OUTPUT_ROW_STRIDE = 4,
    LAST_COLUMN = VERTRIX_TILE_COLUMNS - 1,
    LAST_ROW = VERTRIX_TILE_ROWS - 1,
    UP_LEFT = 0,
    UP = 1,
    UP_RIGHT = 2,
    RIGHT = 3,
    DOWN_RIGHT = 4,
    DOWN = 5,
    DOWN_LEFT = 6,
    LEFT = 7,
    RESULT_FIRST = 8
};

/* A neighbour flag: set outside the grid and for a nonzero cell. */
static uint8_t flag(const uint8_t *grid, int outside, int column, int row)
{
    return (uint8_t)(outside || grid[column * GRID_COLUMN_STRIDE + row] != 0);
}

int vertrix_board_tile_cell(void *output, size_t output_size, const uint8_t *grid, size_t grid_size,
                            uint8_t column, uint8_t row,
                            const uint8_t tables[VERTRIX_TILE_TABLES][VERTRIX_TILE_TABLE_SIZE],
                            VertrixTileScratch *scratch)
{
    uint8_t *s = scratch->scratch;
    int c = column;
    int r = row;
    size_t at = VERTRIX_TILE_OUTPUT + (size_t)OUTPUT_COLUMN_STRIDE * column +
                (size_t)OUTPUT_ROW_STRIDE * row;
    if (column > LAST_COLUMN || row > LAST_ROW ||
        grid_size < (size_t)GRID_COLUMN_STRIDE * VERTRIX_TILE_COLUMNS ||
        output_size < at + OUTPUT_ROW_STRIDE)
    {
        return 0;
    }
    s[UP_LEFT] = flag(grid, c == 0 || r == 0, c - 1, r - 1);
    s[UP] = flag(grid, r == 0, c, r - 1);
    s[UP_RIGHT] = flag(grid, c == LAST_COLUMN || r == 0, c + 1, r - 1);
    s[RIGHT] = flag(grid, c == LAST_COLUMN, c + 1, r);
    s[DOWN_RIGHT] = flag(grid, c == LAST_COLUMN || r == LAST_ROW, c + 1, r + 1);
    s[DOWN] = flag(grid, r == LAST_ROW, c, r + 1);
    s[DOWN_LEFT] = flag(grid, c == 0 || r == LAST_ROW, c - 1, r + 1);
    s[LEFT] = flag(grid, c == 0, c - 1, r);
    s[RESULT_FIRST] = tables[0][(s[UP] + 2 * s[UP_LEFT] + 4 * s[LEFT]) & 0xff];
    s[RESULT_FIRST + 1] = tables[1][(s[RIGHT] + 2 * s[UP_RIGHT] + 4 * s[UP]) & 0xff];
    s[RESULT_FIRST + 2] = tables[2][(s[LEFT] + 2 * s[DOWN_LEFT] + 4 * s[DOWN]) & 0xff];
    s[RESULT_FIRST + 3] = tables[3][(s[DOWN] + 2 * s[DOWN_RIGHT] + 4 * s[RIGHT]) & 0xff];
    for (int i = 0; i < VERTRIX_TILE_TABLES; ++i)
    {
        if (!vertrix_actor_storage_write(output, output_size, at + (size_t)i, 1,
                                         s[RESULT_FIRST + i]))
        {
            return 0;
        }
    }
    return 1;
}
