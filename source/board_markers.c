#include "board_markers.h"
#include "actor_storage.h"
#include <string.h>

/* Original0x4328e0, recovered in board.c. */
int board_falling_mask(const uint8_t board[5][13], uint8_t mask[5][13]);

enum
{
    COLUMNS = 5,
    ROWS = 13,
    EMPTY_KIND = 0xff,
    STONE_KIND = 5,
    BOMB_KIND = 6,
    KIND_BYTE = 0x15c,
    MODE_ORDINARY = 0,
    MODE_NO_STONES = 1,
    MODE_ALL = 2,
    POWER_BOMBS = 5,
    POWER_OTHERS = 6
};

int vertrix_board_snapshot_kinds(const uint32_t *slots, uint32_t count,
                                 VertrixObjectStorage resolve, void *context, uint8_t *kinds)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        void *storage;
        size_t size;
        uint32_t kind = EMPTY_KIND;
        if (slots[i] != 0 && (!resolve(slots[i], &storage, &size, context) ||
                              !vertrix_actor_storage_read(storage, size, KIND_BYTE, 1, &kind)))
        {
            return 0;
        }
        kinds[i] = (uint8_t)kind;
    }
    return 1;
}

void vertrix_board_clear_mask(uint32_t mask[VERTRIX_MARKER_CELLS])
{
    memset(mask, 0, VERTRIX_MARKER_CELLS * sizeof mask[0]);
}

void vertrix_board_markers_for_mode(const uint8_t kinds[VERTRIX_MARKER_CELLS], uint32_t mode,
                                    uint8_t markers[VERTRIX_MARKER_CELLS])
{
    for (int i = 0; i < VERTRIX_MARKER_CELLS; ++i)
    {
        uint8_t kind = kinds[i];
        int selected;
        if (kind == EMPTY_KIND)
        {
            selected = 0;
        }
        else if (kind == STONE_KIND)
        {
            selected = mode == MODE_ALL;
        }
        else if (kind == BOMB_KIND)
        {
            selected = mode == MODE_ALL || mode == MODE_NO_STONES;
        }
        else
        {
            selected = mode == MODE_ALL || mode == MODE_NO_STONES || mode == MODE_ORDINARY;
        }
        markers[i] = (uint8_t)selected;
    }
}

void vertrix_board_markers_top(const uint8_t kinds[VERTRIX_MARKER_CELLS],
                               uint8_t markers[VERTRIX_MARKER_CELLS])
{
    memset(markers, 0, VERTRIX_MARKER_CELLS);
    for (int column = 0; column < COLUMNS; ++column)
    {
        const uint8_t *cells = &kinds[column * ROWS];
        int row = 0;
        while (row < ROWS && cells[row] == EMPTY_KIND)
        {
            ++row;
        }
        if (row < ROWS && cells[row] != STONE_KIND)
        {
            markers[column * ROWS + row] = 1;
        }
    }
}

uint32_t vertrix_board_marker_count(const uint8_t markers[VERTRIX_MARKER_CELLS], uint8_t kind)
{
    uint32_t count = 0;
    for (int i = 0; i < VERTRIX_MARKER_CELLS; ++i)
    {
        count += markers[i] == kind;
    }
    return count;
}

int vertrix_board_marker_nth_by_column(const uint8_t markers[VERTRIX_MARKER_CELLS], uint8_t kind,
                                       uint32_t n, uint32_t *column, uint32_t *row)
{
    uint32_t seen = 0;
    for (int c = 0; c < COLUMNS; ++c)
    {
        for (int r = 0; r < ROWS; ++r)
        {
            if (markers[c * ROWS + r] == kind && seen++ == n)
            {
                *column = (uint32_t)c;
                *row = (uint32_t)r;
                return 1;
            }
        }
    }
    return 0;
}

int vertrix_board_marker_nth_by_row(const uint8_t markers[VERTRIX_MARKER_CELLS], uint8_t kind,
                                    uint32_t n, uint32_t *column, uint32_t *row)
{
    uint32_t seen = 0;
    for (int r = 0; r < ROWS; ++r)
    {
        for (int c = 0; c < COLUMNS; ++c)
        {
            if (markers[c * ROWS + r] == kind && seen++ == n)
            {
                *column = (uint32_t)c;
                *row = (uint32_t)r;
                return 1;
            }
        }
    }
    return 0;
}

void vertrix_board_markers_checker(const uint8_t kinds[VERTRIX_MARKER_CELLS], int include_stones,
                                   uint8_t markers[VERTRIX_MARKER_CELLS])
{
    for (int i = 0; i < VERTRIX_MARKER_CELLS; ++i)
    {
        int block = kinds[i] != EMPTY_KIND && (include_stones || kinds[i] != STONE_KIND);
        markers[i] = (uint8_t)(i % 2 == 0 && block);
    }
}

void vertrix_board_markers_stones(const uint8_t kinds[VERTRIX_MARKER_CELLS],
                                  uint8_t markers[VERTRIX_MARKER_CELLS])
{
    for (int i = 0; i < VERTRIX_MARKER_CELLS; ++i)
    {
        markers[i] = kinds[i] == STONE_KIND;
    }
}

uint32_t vertrix_board_markers_kind(const uint8_t kinds[VERTRIX_MARKER_CELLS], uint32_t wanted,
                                    uint8_t markers[VERTRIX_MARKER_CELLS])
{
    uint32_t count = 0;
    for (int i = 0; i < VERTRIX_MARKER_CELLS; ++i)
    {
        markers[i] = kinds[i] != EMPTY_KIND && (uint32_t)(int32_t)(int8_t)kinds[i] == wanted;
        count += markers[i];
    }
    return count;
}

void vertrix_board_markers_for_power(const uint8_t kinds[VERTRIX_MARKER_CELLS], uint32_t mode,
                                     uint8_t markers[VERTRIX_MARKER_CELLS])
{
    for (int i = 0; i < VERTRIX_MARKER_CELLS; ++i)
    {
        uint8_t kind = kinds[i];
        if (kind == EMPTY_KIND || kind == STONE_KIND)
        {
            markers[i] = 0;
        }
        else if (kind == BOMB_KIND)
        {
            markers[i] = mode == POWER_BOMBS;
        }
        else
        {
            markers[i] = mode == POWER_BOMBS || mode == POWER_OTHERS;
        }
    }
}

int vertrix_board_marker_in_column(const uint8_t markers[VERTRIX_MARKER_CELLS], uint8_t kind,
                                   uint32_t column, uint32_t n, uint32_t *found_column,
                                   uint32_t *found_row)
{
    uint32_t seen = 0;
    if (column >= COLUMNS)
    {
        return 0;
    }
    for (int row = ROWS - 1; row >= 0; --row)
    {
        if (markers[column * ROWS + row] == kind && seen++ == n)
        {
            *found_column = column;
            *found_row = (uint32_t)row;
            return 1;
        }
    }
    return 0;
}

int vertrix_board_any_bottom(const uint32_t *slots, int32_t first, int32_t second,
                             VertrixObjectStorage resolve, void *context,
                             uint8_t kinds[VERTRIX_MARKER_CELLS], uint32_t *occupied)
{
    *occupied = 0;
    if (first >= second)
    {
        return 1;
    }
    if (!vertrix_board_snapshot_kinds(slots, VERTRIX_MARKER_CELLS, resolve, context, kinds))
    {
        return 0;
    }
    for (int column = 0; column < COLUMNS; ++column)
    {
        if (kinds[column * ROWS + ROWS - 1] != EMPTY_KIND)
        {
            *occupied = 1;
        }
    }
    return 1;
}

int vertrix_board_any_block(const uint32_t *slots, int32_t first, int32_t second,
                            VertrixObjectStorage resolve, void *context,
                            uint8_t kinds[VERTRIX_MARKER_CELLS], uint32_t *occupied)
{
    *occupied = 0;
    if (first >= second)
    {
        return 1;
    }
    if (!vertrix_board_snapshot_kinds(slots, VERTRIX_MARKER_CELLS, resolve, context, kinds))
    {
        return 0;
    }
    for (int i = 0; i < VERTRIX_MARKER_CELLS; ++i)
    {
        if (kinds[i] != EMPTY_KIND)
        {
            *occupied = 1;
        }
    }
    return 1;
}

void vertrix_board_markers_equal(const uint8_t kinds[VERTRIX_MARKER_CELLS], int32_t wanted,
                                 uint8_t markers[VERTRIX_MARKER_CELLS])
{
    for (int i = 0; i < VERTRIX_MARKER_CELLS; ++i)
    {
        markers[i] = (int32_t)(int8_t)kinds[i] == wanted;
    }
}

int vertrix_board_mark_filled(const uint32_t slots[VERTRIX_MARKER_CELLS],
                              VertrixObjectStorage resolve, void *context,
                              uint8_t kinds[VERTRIX_MARKER_CELLS],
                              uint8_t markers[VERTRIX_MARKER_CELLS])
{
    if (!vertrix_board_snapshot_kinds(slots, VERTRIX_MARKER_CELLS, resolve, context, kinds))
    {
        return 0;
    }
    for (int cell = 0; cell < VERTRIX_MARKER_CELLS; ++cell)
    {
        markers[cell] = kinds[cell] != EMPTY_KIND;
    }
    return 1;
}

int vertrix_board_mark_stones(const uint32_t slots[VERTRIX_MARKER_CELLS],
                              VertrixObjectStorage resolve, void *context,
                              uint8_t kinds[VERTRIX_MARKER_CELLS],
                              uint8_t markers[VERTRIX_MARKER_CELLS])
{
    if (!vertrix_board_snapshot_kinds(slots, VERTRIX_MARKER_CELLS, resolve, context, kinds))
    {
        return 0;
    }
    for (int cell = 0; cell < VERTRIX_MARKER_CELLS; ++cell)
    {
        if (kinds[cell] == EMPTY_KIND)
        {
            markers[cell] = 0;
        }
        else
        {
            markers[cell] = kinds[cell] == STONE_KIND ? 1 : 2;
        }
    }
    return 1;
}

int vertrix_board_mark_stones_not_bombs(const uint32_t slots[VERTRIX_MARKER_CELLS],
                                        VertrixObjectStorage resolve, void *context,
                                        uint8_t kinds[VERTRIX_MARKER_CELLS],
                                        uint8_t markers[VERTRIX_MARKER_CELLS])
{
    if (!vertrix_board_snapshot_kinds(slots, VERTRIX_MARKER_CELLS, resolve, context, kinds))
    {
        return 0;
    }
    for (int cell = 0; cell < VERTRIX_MARKER_CELLS; ++cell)
    {
        if (kinds[cell] == EMPTY_KIND || kinds[cell] == BOMB_KIND)
        {
            markers[cell] = 0;
        }
        else
        {
            markers[cell] = kinds[cell] == STONE_KIND ? 1 : 2;
        }
    }
    return 1;
}

int vertrix_board_any_falling(const uint32_t slots[VERTRIX_MARKER_CELLS],
                              VertrixObjectStorage resolve, void *context,
                              uint8_t kinds[VERTRIX_MARKER_CELLS], uint32_t *falling)
{
    uint8_t mask[COLUMNS][ROWS];
    if (!vertrix_board_snapshot_kinds(slots, VERTRIX_MARKER_CELLS, resolve, context, kinds))
    {
        return 0;
    }
    *falling = (uint32_t)board_falling_mask((const uint8_t (*)[ROWS])kinds, mask);
    return 1;
}

int vertrix_board_mark_falling_cells(const uint32_t slots[VERTRIX_MARKER_CELLS],
                                     VertrixObjectStorage resolve, void *context,
                                     uint8_t kinds[VERTRIX_MARKER_CELLS], uint8_t board_value,
                                     uint8_t cells[VERTRIX_MARKER_CELLS])
{
    uint8_t mask[COLUMNS][ROWS];
    if (!vertrix_board_snapshot_kinds(slots, VERTRIX_MARKER_CELLS, resolve, context, kinds))
    {
        return 0;
    }
    if (board_falling_mask((const uint8_t (*)[ROWS])kinds, mask))
    {
        for (int column = 0; column < COLUMNS; ++column)
        {
            for (int row = 0; row < ROWS; ++row)
            {
                if (mask[column][row] == 1)
                {
                    cells[column * ROWS + row] = board_value;
                }
            }
        }
    }
    return 1;
}

int vertrix_board_stamp_companions(void *board, size_t board_size, VertrixRandom *random,
                                   VertrixObjectStorage resolve, void *context)
{
    enum
    {
        COMPANION_BASE = 0x87c,
        COMPANION_ROW_STRIDE = 4,
        COMPANION_COLUMN_STRIDE = 0x34,
        COMPANION_BOUND = 0x104,
        STAMP_FIELD = 0x68,
        STAMP_VALUE = 0x30,
        DRAW_DIVISOR = 0x30
    };
    uint32_t row;
    size_t address;
    if (!board || !random)
    {
        return 0;
    }
    for (row = 0; row < ROWS; ++row)
    {
        vertrix_random_modulo(random, DRAW_DIVISOR);
        for (address = COMPANION_ROW_STRIDE * row; address < COMPANION_BOUND;
             address += COMPANION_COLUMN_STRIDE)
        {
            uint32_t companion;
            void *storage;
            size_t size;
            if (!vertrix_actor_storage_read(board, board_size, COMPANION_BASE + address, 4,
                                            &companion))
            {
                return 0;
            }
            if (companion == 0)
            {
                continue;
            }
            if (!resolve(companion, &storage, &size, context) ||
                !vertrix_actor_storage_write(storage, size, STAMP_FIELD, 4, STAMP_VALUE))
            {
                return 0;
            }
        }
    }
    return 1;
}
