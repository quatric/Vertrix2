#ifndef VERTRIX_BOARD_TILES_H
#define VERTRIX_BOARD_TILES_H
#include <stddef.h>
#include <stdint.h>

enum
{
    VERTRIX_TILE_COLUMNS = 5,
    VERTRIX_TILE_ROWS = 13,
    VERTRIX_TILE_TABLE_SIZE = 8,
    VERTRIX_TILE_TABLES = 4,
    VERTRIX_TILE_SCRATCH = 12,
    VERTRIX_TILE_OUTPUT = 0x734
};

/* The scratch bytes of the original (globals 0x5407f9..0x540804) in address order: the eight
 * neighbour flags starting at the upper left and going clockwise (up left, up, up right, right,
 * down right, down, down left, left; a flag is 1 outside the grid and for a nonzero cell), then
 * the four table results. */
typedef struct
{
    uint8_t scratch[VERTRIX_TILE_SCRATCH];
} VertrixTileScratch;

/* Original0x433180: compute the four edge tiles of the grid cell (column, row). The grid holds one
 * byte per cell, 13 rows per column. The corner neighbours and sides give the indices flag(up) +
 * 2 * flag(up left) + 4 * flag(left) and so on into the four 8 byte tables (0x4fb790, 0x4fb798,
 * 0x4fb7a0 and 0x4fb7a8). The four results are stored at +0x734 + 52 * column + 4 * row of the
 * output storage, in table order, and the scratch globals are written. column must be below 5 and
 * row below 13. Returns zero when a storage is too small. */
int vertrix_board_tile_cell(void *output, size_t output_size, const uint8_t *grid, size_t grid_size,
                            uint8_t column, uint8_t row,
                            const uint8_t tables[VERTRIX_TILE_TABLES][VERTRIX_TILE_TABLE_SIZE],
                            VertrixTileScratch *scratch);
#endif
