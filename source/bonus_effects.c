#include "bonus_effects.h"
#include "actor_storage.h"

enum
{
    BYTE_WIDTH = 1,
    DWORD_WIDTH = 4,
    PLAYER_BOARD = 0x15c,
    PLAYER_OPPONENT = 0x3b0,
    PLAYER_GRID = 0x3b8,
    PLAYER_ROW = 0x194,
    PLAYER_COLUMN = 0x198,
    BOARD_VTABLE = 0x158,
    BOARD_FLAG_FIRST = 0xb80,
    BOARD_FLAG_SECOND = 0xb84,
    BOARD_FLAG_THIRD = 0xb88,
    GRID_CELLS = 0x15c,
    GRID_VALUES = 0x1cc,
    GRID_FIRST_BYTES = 0x23c,
    GRID_SECOND_BYTES = 0x258,
    LOCAL_COLUMN = 0x18,
    SLOT_RELEASE = 1,
    HANDLER_APPLY = 0x451f10
};

static int resolve_object(const VertrixEffectServices *services, uint32_t handle, void **storage,
                          size_t *size)
{
    return services->resolve && services->resolve(handle, storage, size, services->resolve_context);
}

static uint32_t enabled_cells(const VertrixChoiceGrid *grid, unsigned row)
{
    uint32_t count = 0;
    unsigned column;
    for (column = 0; column < VERTRIX_CHOICE_COLUMNS; ++column)
    {
        if (grid->values[row * VERTRIX_CHOICE_COLUMNS + column] == 1)
        {
            ++count;
        }
    }
    return count;
}

static int load_grid(const void *storage, size_t size, VertrixChoiceGrid *grid)
{
    unsigned cell;
    for (cell = 0; cell < VERTRIX_CHOICE_CELLS; ++cell)
    {
        uint32_t byte;
        if (!vertrix_actor_storage_read(storage, size, GRID_CELLS + 4u * cell, DWORD_WIDTH,
                                        &grid->cells[cell]) ||
            !vertrix_actor_storage_read(storage, size, GRID_VALUES + 4u * cell, DWORD_WIDTH,
                                        &grid->values[cell]) ||
            !vertrix_actor_storage_read(storage, size, GRID_FIRST_BYTES + cell, BYTE_WIDTH, &byte))
        {
            return 0;
        }
        grid->first_bytes[cell] = (uint8_t)byte;
        if (!vertrix_actor_storage_read(storage, size, GRID_SECOND_BYTES + cell, BYTE_WIDTH, &byte))
        {
            return 0;
        }
        grid->second_bytes[cell] = (uint8_t)byte;
    }
    return 1;
}

uint32_t vertrix_effect_forced_choice(const VertrixEffectServices *services, uint32_t player,
                                      uint32_t frame)
{
    void *player_storage;
    void *opponent_storage;
    void *grid_storage;
    void *own_board_storage;
    void *opponent_board_storage;
    size_t player_size;
    size_t opponent_size;
    size_t grid_size;
    size_t own_board_size;
    size_t opponent_board_size;
    uint32_t opponent;
    uint32_t own_board;
    uint32_t grid_handle;
    uint32_t opponent_board;
    uint32_t vtable;
    uint8_t row = 0;
    uint8_t column = 0;
    uint32_t left_edx;
    uint32_t left_ebx;
    VertrixChoiceGrid grid;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &own_board) ||
        !resolve_object(services, opponent, &opponent_storage, &opponent_size) ||
        !vertrix_actor_storage_read(opponent_storage, opponent_size, PLAYER_GRID, DWORD_WIDTH,
                                    &grid_handle) ||
        !vertrix_actor_storage_read(opponent_storage, opponent_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &opponent_board) ||
        !resolve_object(services, grid_handle, &grid_storage, &grid_size) ||
        !load_grid(grid_storage, grid_size, &grid))
    {
        return 0;
    }
    if (vertrix_choice_grid_pick_cell(&grid, &row, &column, services->draw,
                                      services->draw_context) == 1)
    {
        /* 0x429fe0 leaves edx at the column output and ebx at the number of enabled cells of the
         * chosen row (the count 0x42a080 built); the caller's later calls carry both. */
        left_edx = frame - LOCAL_COLUMN;
        left_ebx = enabled_cells(&grid, row);
        vertrix_call(services->calls, 0x43acd0, player, left_edx, left_ebx, player, 0);
        if (!vertrix_actor_storage_write(opponent_storage, opponent_size, PLAYER_ROW, DWORD_WIDTH,
                                         row) ||
            !vertrix_actor_storage_write(opponent_storage, opponent_size, PLAYER_COLUMN,
                                         DWORD_WIDTH, column))
        {
            return 0;
        }
        vertrix_call(services->calls, 0x43bb60, opponent, HANDLER_APPLY, left_ebx, player, 0);
        vertrix_call(services->calls, 0x4ac8f0, opponent, HANDLER_APPLY, left_ebx, player, 0);
        if (!resolve_object(services, opponent_board, &opponent_board_storage,
                            &opponent_board_size) ||
            !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size,
                                         BOARD_FLAG_FIRST, DWORD_WIDTH, 1) ||
            !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size,
                                         BOARD_FLAG_SECOND, DWORD_WIDTH, 1) ||
            !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size,
                                         BOARD_FLAG_THIRD, DWORD_WIDTH, 1))
        {
            return 0;
        }
    }
    else
    {
        /* With no cell the scan over rows 1 to 3 ended with edx at zero and ebx at four. */
        left_edx = 0;
        left_ebx = VERTRIX_CHOICE_COLUMNS;
        vertrix_call(services->calls, 0x43ac00, player, left_edx, left_ebx, player, 0);
    }
    if (!resolve_object(services, own_board, &own_board_storage, &own_board_size) ||
        !vertrix_actor_storage_read(own_board_storage, own_board_size, BOARD_VTABLE, DWORD_WIDTH,
                                    &vtable))
    {
        return 0;
    }
    if (services->virtual_call)
    {
        services->virtual_call(services->virtual_context, own_board, SLOT_RELEASE, 0);
    }
    return vertrix_call(services->calls, 0x43bbf0, player, vtable, left_ebx, player, 0);
}
