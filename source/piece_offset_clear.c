#include "piece_offset_clear.h"
#include <string.h>

static int clear_offset(void *storage, size_t size, uint32_t token, size_t offset, uint32_t *result)
{
    if (!storage || size <= offset || !result)
        return 0;
    ((uint8_t *)storage)[offset] = 0;
    *result = token;
    return 1;
}

int vertrix_board_piece_clear_offset_x_full(void *storage, size_t size, uint32_t token,
                                            uint32_t *result)
{
    return clear_offset(storage, size, token, 0xa64, result);
}
int vertrix_board_piece_clear_offset_y_full(void *storage, size_t size, uint32_t token,
                                            uint32_t *result)
{
    return clear_offset(storage, size, token, 0xa65, result);
}
int vertrix_board_cell_values_clear_full(void *storage, size_t size, uint32_t token,
                                         uint32_t *result)
{
    if (!storage || size < 0x1de || !result)
        return 0;
    memset((uint8_t *)storage + 0x19d, 0, 65);
    *result = token + 65u;
    return 1;
}
int vertrix_board_cell_values_fill_full(void *storage, size_t size, uint32_t token, uint32_t edx,
                                        uint32_t *eax_result, uint32_t *edx_result)
{
    if (!storage || size < 0x1de || !eax_result || !edx_result)
        return 0;
    memset((uint8_t *)storage + 0x19d, (int)(edx & 255u), 65);
    *eax_result = token + 65u;
    *edx_result = token + 65u;
    return 1;
}
