#include "collision.h"
#include "recovered.h"

/* Original 0x00431b80, called by the piece update at 0x0042fc2f.
 * Preserve its unsigned comparison and low-word coordinate conversion. */
int vertrix_down_clear(const uint8_t board[COLS][ROWS], int16_t origin_x, int16_t origin_y,
                       int16_t piece_x, int16_t piece_y)
{
    int32_t bottom = (int32_t)piece_y + 72;
    if ((uint32_t)bottom < (uint32_t)(int32_t)origin_y)
    {
        return 1;
    }
    uint16_t bits = (uint16_t)bottom;
    int32_t pixel = bits < 32768 ? bits : (int32_t)bits - 65536;
    int32_t column, row;
    board_pixel_cell(origin_x, origin_y, piece_x, (int16_t)pixel, &column, &row);
    return row < ROWS && board[column][row] == EMPTY;
}

int vertrix_side_shift_contact(const uint8_t board[COLS][ROWS], uint32_t pattern, int16_t origin_x,
                               int16_t origin_y, int16_t piece_x, int16_t piece_y, int right)
{
    return vertrix_side_contact(board, side_shift_masks[pattern], origin_x, origin_y, piece_x,
                                piece_y, right);
}

/* Original 0x0042f030 (left) and 0x0042f120 (right). */
int vertrix_side_contact(const uint8_t board[COLS][ROWS], const uint8_t row_mask[ROWS],
                         int16_t origin_x, int16_t origin_y, int16_t piece_x, int16_t piece_y,
                         int right)
{
    int32_t column, top, bottom, ignored;
    board_pixel_cell(origin_x, origin_y, piece_x, piece_y, &column, &top);
    /* The original coordinate helper consumes only the low signed word. */
    uint16_t bottom_bits = (uint16_t)((uint16_t)piece_y + 71);
    int32_t bottom_pixel = bottom_bits < 32768 ? bottom_bits : (int32_t)bottom_bits - 65536;
    board_pixel_cell(origin_x, origin_y, piece_x, (int16_t)bottom_pixel, &ignored, &bottom);
    int boundary = right ? COLS - 1 : 0;
    int32_t neighbor = column + (right ? 1 : -1);
    for (int32_t row = top; row <= bottom; row++)
    {
        if (row < 0)
        {
            continue;
        }
        if (row_mask[row] && (column == boundary || board[neighbor][row] != EMPTY))
        {
            return 1;
        }
    }
    return 0;
}
