#include "piece_offsets.h"
#include "actor_storage.h"

static int set_offset(void *storage, size_t size, uint32_t token, uint32_t edx, size_t offset,
                      uint32_t *result)
{
    if (!result || !vertrix_actor_storage_write(storage, size, offset, 1, edx))
    {
        return 0;
    }
    *result = token;
    return 1;
}

int vertrix_piece_set_offset_x_full(void *storage, size_t size, uint32_t token, uint32_t edx,
                                    uint32_t *result)
{
    return set_offset(storage, size, token, edx, 0x16c, result);
}

int vertrix_piece_set_offset_y_full(void *storage, size_t size, uint32_t token, uint32_t edx,
                                    uint32_t *result)
{
    return set_offset(storage, size, token, edx, 0x16d, result);
}

int vertrix_board_piece_set_offset_x_full(void *storage, size_t size, uint32_t token, uint32_t edx,
                                          uint32_t *result)
{
    return set_offset(storage, size, token, edx, 0xa64, result);
}

int vertrix_board_piece_set_offset_y_full(void *storage, size_t size, uint32_t token, uint32_t edx,
                                          uint32_t *result)
{
    return set_offset(storage, size, token, edx, 0xa65, result);
}
