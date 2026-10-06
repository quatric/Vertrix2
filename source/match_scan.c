#include "match_scan.h"
#include "actor_fields.h"
#include "actor_storage.h"
#include "board_markers.h"
#include "game.h"
#include <stdio.h>
#include <string.h>

enum
{
    DWORD_WIDTH = 4,
    WORD_WIDTH = 2,
    BYTE_WIDTH = 1,
    SCAN_COLUMNS = 5,
    SCAN_ROWS = 13,
    SCAN_CELLS = 65,
    SCAN_KINDS = 0x1de,
    SCAN_SLOTS = 0x220,
    SCAN_KIND_ROW = 0xd,
    SCAN_CELL_ROW = 0x34,
    SCAN_TAP_ROW = 0xd0,
    SCAN_TAP_STEP = 0x10,
    SCAN_TAP_COUNT = 4,
    SCAN_CELL_OBJECT = 0x324,
    SCAN_LIST = 0xbdc,
    SCAN_KIND_BYTE = 0x15c,
    SCAN_TOUCH_BYTE = 0x15d,
    SCAN_CLEAR_EVENT = 0x4504e0,
    SCAN_EFFECT_EVENT = 0x450450,
    SCAN_BURST_EVENT = 0x450330,
    SCAN_SPECIAL_KIND = 7,
    SCAN_DISPATCH_BASE = 0x4fb7b0,
};

static int read_dword(const void *storage, size_t size, size_t offset, uint32_t *value)
{
    return vertrix_actor_storage_read(storage, size, offset, DWORD_WIDTH, value);
}

static int write_dword(void *storage, size_t size, size_t offset, uint32_t value)
{
    return vertrix_actor_storage_write(storage, size, offset, DWORD_WIDTH, value);
}

static int write_byte(void *storage, size_t size, size_t offset, uint32_t value)
{
    return vertrix_actor_storage_write(storage, size, offset, BYTE_WIDTH, value);
}

static int touch_cell(const VertrixFactoryServices *services, uint32_t cell, uint32_t event)
{
    void *storage;
    size_t size;
    if (!services->resolve(cell, &storage, &size, services->context) ||
        !vertrix_actor_set_period_steps(storage, size, 1) ||
        !vertrix_actor_storage_write(storage, size, SCAN_TOUCH_BYTE, BYTE_WIDTH, 1) ||
        !vertrix_actor_set_handler(storage, size, event))
    {
        return 0;
    }
    return 1;
}

uint32_t vertrix_match_scan(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            VertrixMemoryRead read, void *read_context, uint32_t player,
                            void *player_storage, size_t player_size, uint8_t side,
                            uint32_t *flag_a, uint32_t *flag_b, uint32_t *reward, uint32_t *mult,
                            uint8_t image[COLS][ROWS], uint32_t mask[65], uint32_t dispatch_index,
                            const VertrixMatchBurstHooks *hooks)
{
    uint32_t slots[SCAN_CELLS];
    uint8_t kinds[COLS][ROWS];
    uint8_t board[COLS][ROWS];
    uint8_t *kinds_flat = &kinds[0][0];
    uint8_t *board_flat = &board[0][0];
    uint32_t index;
    int counter = 0;
    int gain = 0;
    uint32_t matched = 0;
    uint32_t any_cells = 0;
    uint32_t row;
    uint32_t column;
    uint32_t tap;
    *flag_a = 0;
    *flag_b = 0;
    *reward = 0;
    *mult = 0;
    for (index = 0; index < SCAN_CELLS; index++)
    {
        if (!read_dword(player_storage, player_size, SCAN_SLOTS + index * DWORD_WIDTH,
                        &slots[index]))
        {
            return 0;
        }
    }
    if (!vertrix_board_snapshot_kinds(slots, SCAN_CELLS, services->resolve, services->context,
                                      kinds_flat))
    {
        return 0;
    }
    for (index = 0; index < SCAN_CELLS; index++)
    {
        if (!vertrix_actor_storage_write(player_storage, player_size, SCAN_KINDS + index,
                                         BYTE_WIDTH, kinds_flat[index]))
        {
            return 0;
        }
    }
    vertrix_board_clear_mask(mask);
    memcpy(image, kinds_flat, SCAN_CELLS);
    for (index = 0; index < SCAN_CELLS; index++)
    {
        board_flat[index] = (uint8_t)(mask[index] != 0);
    }
    if (vertrix_figure_pass(kinds, board, &gain, 1))
    {
        matched = 1;
    }
    counter += gain;
    fprintf(stderr, "STAGE counter=%d\n", counter);
    for (index = 0; index < SCAN_CELLS; index++)
    {
        mask[index] = board_flat[index];
        if (!vertrix_actor_storage_write(player_storage, player_size, SCAN_KINDS + index,
                                         BYTE_WIDTH, kinds_flat[index]))
        {
            return 0;
        }
    }
    if (matched)
    {
        *flag_a = 1;
        *flag_b = 1;
    }
    for (index = 0; index < SCAN_CELLS; index++)
    {
        board_flat[index] = (uint8_t)(mask[index] != 0);
    }
    gain = 0;
    if (vertrix_line_pass(image, board, side, &gain))
    {
        matched = 1;
    }
    counter += gain;
    fprintf(stderr, "STAGE counter=%d\n", counter);
    for (index = 0; index < SCAN_CELLS; index++)
    {
        mask[index] = board_flat[index];
    }
    if (matched)
    {
        *flag_a = 1;
    }
    for (row = 0; row < SCAN_COLUMNS; row++)
    {
        for (column = 0; column < SCAN_ROWS; column++)
        {
            uint32_t kind_cell;
            uint32_t tap_cell;
            if (!read_dword(player_storage, player_size,
                            SCAN_SLOTS + row * SCAN_CELL_ROW + column * DWORD_WIDTH, &kind_cell) ||
                !read_dword(player_storage, player_size,
                            row * SCAN_TAP_ROW + column * SCAN_TAP_STEP + SCAN_CELL_OBJECT,
                            &tap_cell))
            {
                return 0;
            }
            if (tap_cell == 0)
            {
                continue;
            }
            if (kind_cell != 0)
            {
                mask[column + row * SCAN_ROWS] = 1;
            }
            any_cells = 1;
            for (tap = 0; tap < SCAN_TAP_COUNT; tap++)
            {
                uint32_t cell;
                if (!read_dword(player_storage, player_size,
                                row * SCAN_TAP_ROW + column * SCAN_TAP_STEP + tap * DWORD_WIDTH +
                                    SCAN_CELL_OBJECT,
                                &cell))
                {
                    return 0;
                }
                if (!touch_cell(services, cell, SCAN_CLEAR_EVENT))
                {
                    return 0;
                }
            }
        }
    }
    if (!matched && !any_cells)
    {
        return 0;
    }
    for (row = 0; row < SCAN_COLUMNS; row++)
    {
        for (column = 0; column < SCAN_ROWS; column++)
        {
            uint32_t kind_cell;
            uint32_t kind;
            void *cell_storage;
            size_t cell_size;
            if (!read_dword(player_storage, player_size,
                            SCAN_SLOTS + row * SCAN_CELL_ROW + column * DWORD_WIDTH, &kind_cell))
            {
                return 0;
            }
            if (kind_cell == 0 || mask[column + row * SCAN_ROWS] != 1)
            {
                continue;
            }
            *mult += 1;
            if (!services->resolve(kind_cell, &cell_storage, &cell_size, services->context) ||
                !vertrix_actor_set_period_steps(cell_storage, cell_size, 1) ||
                !write_byte(cell_storage, cell_size, SCAN_TOUCH_BYTE, 1) ||
                !vertrix_actor_storage_read(player_storage, player_size,
                                            SCAN_KINDS + row * SCAN_KIND_ROW + column, 1, &kind))
            {
                return 0;
            }
            if (!vertrix_actor_storage_write(cell_storage, cell_size, SCAN_KIND_BYTE, BYTE_WIDTH,
                                             kind & 0xff))
            {
                return 0;
            }
            if ((kind & 0xff) == SCAN_SPECIAL_KIND)
            {
                uint32_t effect;
                void *effect_storage;
                size_t effect_size;
                effect = vertrix_actor_spawn_match_effect(calls, services, player_storage,
                                                          player_size, row, column, column);
                if (!write_dword(player_storage, player_size,
                                 row * SCAN_CELL_ROW + column * DWORD_WIDTH + SCAN_LIST, effect) ||
                    !services->resolve(effect, &effect_storage, &effect_size, services->context) ||
                    !vertrix_actor_set_handler(effect_storage, effect_size, SCAN_EFFECT_EVENT))
                {
                    return 0;
                }
                vertrix_actor_spawn_match_burst(services, player_storage, player_size, player, row,
                                                column, hooks);
            }
            else
            {
                uint32_t method;
                if (!read(SCAN_DISPATCH_BASE + dispatch_index * DWORD_WIDTH, DWORD_WIDTH, &method,
                          read_context))
                {
                    return 0;
                }
                vertrix_call(calls, method, player, row, column, column, 0);
            }
            {
                uint32_t burst_cell;
                void *burst_storage;
                size_t burst_size;
                if (!read_dword(player_storage, player_size,
                                SCAN_SLOTS + row * SCAN_CELL_ROW + column * DWORD_WIDTH,
                                &burst_cell) ||
                    !services->resolve(burst_cell, &burst_storage, &burst_size,
                                       services->context) ||
                    !vertrix_actor_set_handler(burst_storage, burst_size, SCAN_BURST_EVENT))
                {
                    return 0;
                }
            }
        }
    }
    *reward = (uint32_t)counter & 0xffff;
    return 1;
}
