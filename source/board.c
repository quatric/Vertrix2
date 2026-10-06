#include "game.h"

#include <string.h>

/* Board placement in 0x00431c60; coordinates come from 0x00431ae0.
 * Placed graphics objects also reset +0x93, +0x4e, and +0x48 at runtime. */
int board_lock(uint8_t board[COLS][ROWS], int32_t column, int32_t top, const uint8_t blocks[3],
               uint8_t discarded[3])
{
    for (int i = 0; i < 3; i++)
    {
        int64_t row = (int64_t)top + i;
        discarded[i] = row < 0 || row >= ROWS;
        if (!discarded[i])
        {
            board[column][row] = blocks[i];
        }
    }
    return top > -3;
}
/* Original 0x0042f310: columns without an incoming object do not move. */
void board_rise(uint8_t board[COLS][ROWS], uint8_t incoming[COLS], uint8_t evicted[COLS])
{
    for (int column = 0; column < COLS; column++)
    {
        evicted[column] = EMPTY;
        if (incoming[column] == EMPTY)
        {
            continue;
        }
        evicted[column] = board[column][0];
        for (int row = 0; row < ROWS - 1; row++)
        {
            board[column][row] = board[column][row + 1];
        }
        board[column][ROWS - 1] = incoming[column];
        incoming[column] = EMPTY;
    }
}

/* Original pointer-board transitions 0x0042f580 and 0x0042f620,
 * represented by block types. Empty incoming rows leave the board unchanged. */
void board_shift(uint8_t board[COLS][ROWS], uint8_t incoming[ROWS], uint8_t evicted[ROWS],
                 int right)
{
    for (int row = 0; row < ROWS; row++)
    {
        evicted[row] = EMPTY;
        if (incoming[row] == EMPTY)
        {
            continue;
        }
        evicted[row] = board[right ? COLS - 1 : 0][row];
        if (right)
        {
            for (int column = COLS - 1; column > 0; column--)
            {
                board[column][row] = board[column - 1][row];
            }
            board[0][row] = incoming[row];
        }
        else
        {
            for (int column = 0; column < COLS - 1; column++)
            {
                board[column][row] = board[column + 1][row];
            }
            board[COLS - 1][row] = incoming[row];
        }
        incoming[row] = EMPTY;
    }
}
/* Original 0x00431ae0: signed 16-bit positions, 32-bit subtraction,
 * and signed division toward zero, including coordinates outside the board. */
void board_pixel_cell(int16_t origin_x, int16_t origin_y, int16_t pixel_x, int16_t pixel_y,
                      int32_t *column, int32_t *row)
{
    *column = ((int32_t)pixel_x - origin_x) / 24;
    *row = ((int32_t)pixel_y - origin_y) / 24;
}

/* CXObjectDamier's column-major byte board; original routine 0x004328e0. */
int board_falling_mask(const uint8_t board[COLS][ROWS], uint8_t mask[COLS][ROWS])
{
    int any = 0;
    memset(mask, 0, COLS * ROWS);
    for (int x = 0; x < COLS; x++)
    {
        int y = ROWS - 1;
        while (y >= 0 && board[x][y] != EMPTY)
        {
            y--;
        }
        for (; y >= 0; y--)
        {
            if (board[x][y] != EMPTY)
            {
                mask[x][y] = 1;
                any = 1;
            }
        }
    }
    return any;
}

/* Byte-board collapse used by the original AI, 0x00432980. */
void board_collapse(uint8_t board[COLS][ROWS])
{
    uint8_t falling[COLS][ROWS];
    if (!board_falling_mask(board, falling))
    {
        return;
    }
    for (int x = 0; x < COLS; x++)
    {
        for (int y = ROWS - 2; y >= 0; y--)
        {
            if (!falling[x][y])
            {
                continue;
            }
            int dest = y + 1;
            while (dest < ROWS && board[x][dest] == EMPTY)
            {
                dest++;
            }
            board[x][dest - 1] = board[x][y];
            board[x][y] = EMPTY;
        }
    }
}

/* Blast-area construction in 0x00433e20, before graphics objects are created.
 * The radius comparison is strict. Pattern 4 adds vertical arms in the two
 * neighboring columns; the original does not use a circular distance test. */
void board_blast_mask(const uint8_t board[COLS][ROWS], uint8_t mask[COLS][ROWS], uint8_t pattern,
                      uint8_t radius)
{
    memset(mask, 0, COLS * ROWS);
    for (int x = 0; x < COLS; x++)
    {
        for (int y = 0; y < ROWS; y++)
        {
            if (board[x][y] != BOMB)
            {
                continue;
            }
            mask[x][y] = 1;
            for (int xx = 0; xx < COLS; xx++)
            {
                for (int yy = 0; yy < ROWS; yy++)
                {
                    int dx = xx - x;
                    int dy = yy - y;
                    int adx = dx < 0 ? -dx : dx;
                    int ady = dy < 0 ? -dy : dy;
                    int horizontal =
                        (pattern == 1 || pattern == 3 || pattern == 4) && dy == 0 && adx < radius;
                    int vertical =
                        (pattern == 2 || pattern == 3 || pattern == 4) && dx == 0 && ady < radius;
                    int wide = pattern == 4 && adx == 1 && dy != 0 && ady < radius;
                    if (horizontal || vertical || wide)
                    {
                        mask[xx][yy] = 1;
                    }
                }
            }
        }
    }
}

/* AI estimator 0x00434300 intentionally counts full rows/columns, independent
 * of the animation radius. Preserve this distinction from the live blast. */
void board_bomb_estimate(const uint8_t board[COLS][ROWS], uint8_t pattern, int *stones, int *total)
{
    uint8_t mask[COLS][ROWS];
    board_blast_mask(board, mask, pattern, 255);
    *stones = 0;
    *total = 0;
    for (int x = 0; x < COLS; x++)
    {
        for (int y = 0; y < ROWS; y++)
        {
            if (mask[x][y] && board[x][y] != EMPTY)
            {
                (*total)++;
                if (board[x][y] == STONE)
                {
                    (*stones)++;
                }
            }
        }
    }
}
