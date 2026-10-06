#include "bonus_effects.h"
#include "actor_storage.h"
#include "board_conversions.h"
#include "board_markers.h"

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
    HANDLER_APPLY = 0x451f10,
    PLAYER_KIND = 0x3dc,
    PLAYER_FIRST_COUNT = 0x43c,
    PLAYER_SECOND_COUNT = 0x440,
    BOARD_SLOTS = 0x220,
    BOARD_KINDS = 0x1de,
    BOARD_MARKERS = 0xb94,
    EFFECT_SOUND = 11,
    LOCAL_SECOND_COUNT = 0x24,
    HANDLER_PLAYER = 0x453280,
    HANDLER_OPPONENT = 0x452050,
    HANDLER_FLASH = 0x44f040,
    HANDLER_MATCH_PLAYER = 0x452fc0,
    PLAYER_EXTRA = 0x3b4,
    PLAYER_PENDING = 0x170,
    PIECE_HANDLE = 0xa60,
    PIECE_CHILDREN = 0x15c,
    CHILD_KIND = 0x15c,
    PLAYER_SOUND_ARG = 0x3f8,
    PLAYER_SPEED = 0x3cc,
    PLAYER_RECEIVED = 0x424,
    PLAYER_RECEIVED_STATE = 0x428,
    SOUND_PAIR = 3,
    HANDLER_SPEED = 0x453c90,
    PLAYER_STATE = 0x4c8,
    SOUND_GATE = 6,
    SOUND_DROP = 5,
    PLAYER_NEGATED = 0x3bc,
    PLAYER_VALUE = 0x3c0,
    PLAYER_PROGRESS = 0x17c,
    PLAYER_PROGRESS_STEP = 0x3c8,
    PLAYER_SHAPE = 0x3c4,
    PLAYER_MODE_BYTE = 0x4cd,
    PLAYER_ARM_FIRST = 0x4d0,
    PLAYER_ARM_SECOND = 0x4d4,
    PLAYER_ARM_THIRD = 0x4d8,
    SOUND_ARMED = 9,
    SOUND_COMPARE = 11,
    PLAYER_STONE_ARG = 0x3e0,
    HANDLER_STONE_APPLY = 0x4534e0,
    HANDLER_STONE_CLEAR = 0x453570,
    HANDLER_FIELD = 0x44c860
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

/* 0x436a10 on one board: snapshot the kinds of its 65 slots into +0x1de, then mark the cells of
 * the wanted kind at +0xb94 and report how many. */
static int mark_kind(const VertrixEffectServices *services, void *board, size_t size,
                     uint32_t wanted, uint32_t *count)
{
    uint32_t slots[VERTRIX_MARKER_CELLS];
    uint8_t kinds[VERTRIX_MARKER_CELLS];
    uint8_t markers[VERTRIX_MARKER_CELLS];
    unsigned cell;
    for (cell = 0; cell < VERTRIX_MARKER_CELLS; ++cell)
    {
        if (!vertrix_actor_storage_read(board, size, BOARD_SLOTS + 4u * cell, DWORD_WIDTH,
                                        &slots[cell]))
        {
            return 0;
        }
    }
    if (!vertrix_board_snapshot_kinds(slots, VERTRIX_MARKER_CELLS, services->resolve,
                                      services->resolve_context, kinds))
    {
        return 0;
    }
    *count = vertrix_board_markers_kind(kinds, wanted, markers);
    for (cell = 0; cell < VERTRIX_MARKER_CELLS; ++cell)
    {
        if (!vertrix_actor_storage_write(board, size, BOARD_KINDS + cell, BYTE_WIDTH,
                                         kinds[cell]) ||
            !vertrix_actor_storage_write(board, size, BOARD_MARKERS + cell, BYTE_WIDTH,
                                         markers[cell]))
        {
            return 0;
        }
    }
    return 1;
}

uint32_t vertrix_effect_convert_blocks(const VertrixEffectServices *services, uint32_t player,
                                       uint32_t frame)
{
    void *player_storage;
    void *opponent_storage;
    void *own_storage;
    void *opponent_board_storage;
    size_t player_size;
    size_t opponent_size;
    size_t own_size;
    size_t opponent_board_size;
    uint32_t opponent;
    uint32_t own_board;
    uint32_t opponent_board;
    uint32_t kind;
    uint32_t vtable;
    uint32_t first;
    uint32_t second;
    uint32_t last_old = 0;
    uint32_t left_ebx;
    uint32_t left_ecx;
    uint32_t result;
    uint32_t left_edx = frame - LOCAL_SECOND_COUNT;
    if (!services || !services->calls || !services->factory ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &own_board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_KIND, DWORD_WIDTH, &kind) ||
        !resolve_object(services, opponent, &opponent_storage, &opponent_size) ||
        !vertrix_actor_storage_read(opponent_storage, opponent_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &opponent_board) ||
        !resolve_object(services, own_board, &own_storage, &own_size) ||
        !resolve_object(services, opponent_board, &opponent_board_storage, &opponent_board_size) ||
        !mark_kind(services, own_storage, own_size, kind, &first) ||
        !mark_kind(services, opponent_board_storage, opponent_board_size, kind, &second))
    {
        return 0;
    }
    if (first == second)
    {
        vertrix_call(services->calls, 0x43acd0, player, left_edx, 1, player, 0);
    }
    else
    {
        vertrix_call(services->calls, first > second ? 0x43ac00 : 0x43acd0, player, left_edx,
                     second, player, 0);
        vertrix_call(services->calls, 0x43c0e0, opponent, EFFECT_SOUND, second, player, 0);
        if (!vertrix_actor_storage_write(player_storage, player_size, PLAYER_FIRST_COUNT,
                                         DWORD_WIDTH, first) ||
            !vertrix_actor_storage_write(player_storage, player_size, PLAYER_SECOND_COUNT,
                                         DWORD_WIDTH, second) ||
            !vertrix_boards_convert_counts_traced(own_storage, own_size, opponent_board_storage,
                                                  opponent_board_size, first, second,
                                                  services->factory, &last_old))
        {
            return 0;
        }
        /* 0x436b40 leaves ebx and ecx as its loops did: the last old block of the second board
         * and its count, else the first count twice, else the kind and zero. */
        if (second > 0)
        {
            left_ebx = last_old;
            left_ecx = second;
        }
        else if (first > 0)
        {
            left_ebx = first;
            left_ecx = first;
        }
        else
        {
            left_ebx = kind;
            left_ecx = 0;
        }
        vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_PLAYER, left_ebx, left_ecx, 0);
        vertrix_call(services->calls, 0x43bb60, opponent, HANDLER_PLAYER, left_ebx, left_ecx, 0);
        if (!vertrix_actor_storage_write(opponent_board_storage, opponent_board_size,
                                         BOARD_FLAG_FIRST, DWORD_WIDTH, 1) ||
            !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size,
                                         BOARD_FLAG_SECOND, DWORD_WIDTH, 1) ||
            !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size,
                                         BOARD_FLAG_THIRD, DWORD_WIDTH, 1))
        {
            return 0;
        }
        vertrix_call(services->calls, 0x4ac8f0, opponent, HANDLER_OPPONENT, left_ebx, left_ecx, 0);
    }
    if (!vertrix_actor_storage_read(own_storage, own_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       own_board, SLOT_RELEASE, 0)
                                    : 0;
    if (first == second)
    {
        return vertrix_call(services->calls, 0x43bbf0, player, vtable, 1, player, 0);
    }
    return result;
}

static uint32_t sign_extend_byte(uint32_t value)
{
    return (uint32_t)(int32_t)(int8_t)value;
}

/* The three kinds of the active piece's children, as 0x452e00 reads them. */
static int piece_kinds(const VertrixEffectServices *services, void *board, size_t size,
                       uint32_t kinds[3])
{
    uint32_t piece_handle;
    void *piece;
    size_t piece_size;
    unsigned slot;
    if (!vertrix_actor_storage_read(board, size, PIECE_HANDLE, DWORD_WIDTH, &piece_handle) ||
        !resolve_object(services, piece_handle, &piece, &piece_size))
    {
        return 0;
    }
    for (slot = 0; slot < 3; ++slot)
    {
        uint32_t child;
        void *child_storage;
        size_t child_size;
        uint32_t kind;
        if (!vertrix_actor_storage_read(piece, piece_size, PIECE_CHILDREN + 4u * slot, DWORD_WIDTH,
                                        &child) ||
            !resolve_object(services, child, &child_storage, &child_size) ||
            !vertrix_actor_storage_read(child_storage, child_size, CHILD_KIND, BYTE_WIDTH, &kind))
        {
            return 0;
        }
        kinds[slot] = sign_extend_byte(kind);
    }
    return 1;
}

uint32_t vertrix_effect_board_match(const VertrixEffectServices *services, uint32_t player,
                                    uint32_t entry_ebx)
{
    void *player_storage;
    void *opponent_storage;
    void *own_storage;
    void *opponent_board_storage;
    size_t player_size;
    size_t opponent_size;
    size_t own_size;
    size_t opponent_board_size;
    uint32_t opponent;
    uint32_t own_board;
    uint32_t opponent_board;
    uint32_t extra;
    uint32_t pending;
    uint32_t vtable;
    uint32_t result;
    uint32_t ebx = entry_ebx;
    uint32_t ecx = player;
    const VertrixCalls *calls;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &own_board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !resolve_object(services, opponent, &opponent_storage, &opponent_size) ||
        !vertrix_actor_storage_read(opponent_storage, opponent_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &opponent_board) ||
        !vertrix_actor_storage_read(opponent_storage, opponent_size, PLAYER_EXTRA, DWORD_WIDTH,
                                    &extra) ||
        !resolve_object(services, own_board, &own_storage, &own_size) ||
        !vertrix_actor_storage_read(own_storage, own_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    calls = services->calls;
    if (vertrix_call(calls, 0x438cd0, own_board, opponent_board, ebx, ecx, 0))
    {
        vertrix_call(calls, 0x43acd0, player, opponent_board, ebx, 1, 0);
        if (services->virtual_call)
        {
            services->virtual_call(services->virtual_context, own_board, SLOT_RELEASE, 0);
        }
        return vertrix_call(calls, 0x43bbf0, player, vtable, ebx, 1, 0);
    }
    vertrix_call(calls,
                 vertrix_call(calls, 0x43ab60, player, opponent_board, ebx, ecx, 0) == 1 ? 0x43ac00
                                                                                         : 0x43acd0,
                 player, opponent_board, ebx, ecx, 0);
    vertrix_call(calls, 0x43c0e0, opponent, EFFECT_SOUND, ebx, ecx, 0);
    if (!resolve_object(services, opponent_board, &opponent_board_storage, &opponent_board_size))
    {
        return 0;
    }
    if (vertrix_call(calls, 0x4320c0, opponent_board, EFFECT_SOUND, ebx, ecx, 0) == 1 &&
        vertrix_call(calls, 0x4330d0, opponent_board, own_board, ebx, ecx, 0) == 1)
    {
        if (!vertrix_actor_storage_read(opponent_storage, opponent_size, PLAYER_PENDING,
                                        DWORD_WIDTH, &pending))
        {
            return 0;
        }
        if (pending == 1)
        {
            uint32_t kinds[3];
            if (!piece_kinds(services, opponent_board_storage, opponent_board_size, kinds))
            {
                return 0;
            }
            ebx = kinds[1];
            ecx = kinds[2];
            vertrix_call(calls, 0x43a560, extra, kinds[0], ebx, ecx, 0);
            if (!vertrix_actor_storage_write(opponent_storage, opponent_size, PLAYER_PENDING,
                                             DWORD_WIDTH, 0))
            {
                return 0;
            }
        }
        vertrix_call(calls, 0x431d80, opponent_board, 2, ebx, ecx, 0);
        vertrix_call(calls, 0x42ee20, opponent_board, 2, ebx, ecx, 0);
    }
    vertrix_call(calls, 0x42eda0, own_board, HANDLER_FLASH, ebx, ecx, 0);
    vertrix_call(calls, 0x42eda0, opponent_board, HANDLER_FLASH, ebx, ecx, 0);
    vertrix_call(calls, 0x42ee80, own_board, 5, ebx, ecx, 0);
    vertrix_call(calls, 0x42ee80, opponent_board, 5, ebx, ecx, 0);
    vertrix_call(calls, 0x433040, own_board, opponent_board, ebx, ecx, 0);
    vertrix_call(calls, 0x43bb60, opponent, opponent_board, ebx, ecx, 0);
    if (!vertrix_actor_storage_write(opponent_board_storage, opponent_board_size, BOARD_FLAG_FIRST,
                                     DWORD_WIDTH, 1) ||
        !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size, BOARD_FLAG_SECOND,
                                     DWORD_WIDTH, 1) ||
        !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size, BOARD_FLAG_THIRD,
                                     DWORD_WIDTH, 1))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ac8f0, opponent, HANDLER_OPPONENT, ebx, ecx, 0);
    vertrix_call(calls, 0x4ac8f0, player, HANDLER_MATCH_PLAYER, ebx, ecx, 0);
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       own_board, SLOT_RELEASE, 0)
                                    : 0;
    return result;
}

uint32_t vertrix_effect_pair_sound(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_edx)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t opponent;
    uint32_t board;
    uint32_t argument;
    uint32_t vtable;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_SOUND_ARG, DWORD_WIDTH,
                                    &argument) ||
        !resolve_object(services, board, &board_storage, &board_size) ||
        !vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    if (vertrix_call(services->calls, 0x43d3b0, player, entry_edx, board, player, 0) == 1)
    {
        vertrix_call(services->calls, 0x43acd0, player, entry_edx, board, player, 0);
    }
    else
    {
        vertrix_call(services->calls, 0x43c0e0, player, SOUND_PAIR, board, player, 0);
        vertrix_call(services->calls, 0x43ccf0, player, argument, board, player, 0);
        vertrix_call(services->calls, 0x43ccf0, opponent, argument, board, player, 0);
    }
    if (services->virtual_call)
    {
        services->virtual_call(services->virtual_context, board, SLOT_RELEASE, 0);
    }
    return vertrix_call(services->calls, 0x43bbf0, player, vtable, board, player, 0);
}

uint32_t vertrix_effect_copy_speed(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_edx)
{
    void *player_storage;
    void *opponent_storage;
    void *own_storage;
    void *opponent_board_storage;
    size_t player_size;
    size_t opponent_size;
    size_t own_size;
    size_t opponent_board_size;
    uint32_t opponent;
    uint32_t own_board;
    uint32_t opponent_board;
    uint32_t speed;
    uint32_t vtable;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &own_board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_SPEED, DWORD_WIDTH,
                                    &speed) ||
        !resolve_object(services, opponent, &opponent_storage, &opponent_size) ||
        !vertrix_actor_storage_read(opponent_storage, opponent_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &opponent_board) ||
        !resolve_object(services, own_board, &own_storage, &own_size) ||
        !resolve_object(services, opponent_board, &opponent_board_storage, &opponent_board_size) ||
        !vertrix_actor_storage_read(own_storage, own_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    vertrix_call(services->calls, 0x43ac00, player, entry_edx, player, opponent, 0);
    vertrix_call(services->calls, 0x43bb60, opponent, 4, player, opponent, 0);
    vertrix_call(services->calls, 0x43bae0, opponent, 4, player, opponent, 0);
    vertrix_call(services->calls, 0x4ac8f0, opponent, HANDLER_SPEED, player, opponent, 0);
    if (!vertrix_actor_storage_write(opponent_storage, opponent_size, PLAYER_RECEIVED_STATE,
                                     DWORD_WIDTH, 0) ||
        !vertrix_actor_storage_write(opponent_storage, opponent_size, PLAYER_RECEIVED, DWORD_WIDTH,
                                     speed) ||
        !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size, BOARD_FLAG_FIRST,
                                     DWORD_WIDTH, 1) ||
        !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size, BOARD_FLAG_SECOND,
                                     DWORD_WIDTH, 1) ||
        !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size, BOARD_FLAG_THIRD,
                                     DWORD_WIDTH, 1))
    {
        return 0;
    }
    if (services->virtual_call)
    {
        services->virtual_call(services->virtual_context, own_board, SLOT_RELEASE, 0);
    }
    return vertrix_call(services->calls, 0x43bbf0, player, HANDLER_SPEED, player, vtable, 0);
}

const VertrixStateGate vertrix_state_gates[VERTRIX_STATE_GATE_COUNT] = {
    {0x4535d0, VERTRIX_GATE_OPPONENT, 0x23, 0x43cf30},
    {0x453620, VERTRIX_GATE_SELF_SOUND, 0x22, 0x43cf70},
    {0x453670, VERTRIX_GATE_SELF_SOUND, 0x30, 0x43ce30},
    {0x4536c0, VERTRIX_GATE_SELF_BOARD, 0x32, 0x43ce70},
    {0x453710, VERTRIX_GATE_SELF_BOARD, 0x33, 0x43ce70},
    {0x453760, VERTRIX_GATE_SELF_BOARD, 0x34, 0x43ce70},
    {0x4537b0, VERTRIX_GATE_OPPONENT, 0x2f, 0x43ceb0},
    {0x453800, VERTRIX_GATE_OPPONENT, 0x31, 0x43cef0},
    {0x453850, VERTRIX_GATE_OPPONENT, 0x24, 0x43cfb0},
    {0x4538a0, VERTRIX_GATE_OPPONENT, 0x28, 0x43cff0},
    {0x4538f0, VERTRIX_GATE_SELF_SOUND, 0x29, 0x43d030},
    {0x453940, VERTRIX_GATE_SELF_SOUND, 0x2a, 0x43d070},
    {0x453990, VERTRIX_GATE_OPPONENT, 0x2d, 0x43d0b0},
    {0x4539e0, VERTRIX_GATE_OPPONENT, 0x2e, 0x43d0f0},
    {0x453a30, VERTRIX_GATE_SELF_BOARD, 0x2b, 0x43cd60},
    {0x453a80, VERTRIX_GATE_OPPONENT, 0x2c, 0x43cda0}};

uint32_t vertrix_effect_state_gate(const VertrixEffectServices *services, uint32_t player,
                                   const VertrixStateGate *gate)
{
    void *player_storage;
    void *opponent_storage;
    void *board_storage;
    size_t player_size;
    size_t opponent_size;
    size_t board_size;
    uint32_t opponent = 0;
    uint32_t board;
    uint32_t state;
    uint32_t vtable;
    uint32_t eax = player;
    uint32_t edx;
    uint32_t ebx;
    uint32_t ecx;
    if (!services || !services->calls || !gate ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size) ||
        !vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    if (gate->kind == VERTRIX_GATE_OPPONENT)
    {
        if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                        &opponent) ||
            !resolve_object(services, opponent, &opponent_storage, &opponent_size) ||
            !vertrix_actor_storage_read(opponent_storage, opponent_size, PLAYER_STATE, DWORD_WIDTH,
                                        &state))
        {
            return 0;
        }
        edx = board;
        ebx = player;
        ecx = opponent;
    }
    else
    {
        if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_STATE, DWORD_WIDTH,
                                        &state))
        {
            return 0;
        }
        if (gate->kind == VERTRIX_GATE_SELF_BOARD)
        {
            edx = player;
            ebx = player;
            ecx = board;
        }
        else
        {
            edx = state;
            ebx = board;
            ecx = player;
        }
    }
    if (state == gate->state)
    {
        vertrix_call(services->calls, 0x43acd0, eax, edx, ebx, ecx, 0);
    }
    else
    {
        if (gate->kind == VERTRIX_GATE_SELF_SOUND)
        {
            edx = SOUND_GATE;
            vertrix_call(services->calls, 0x43c0e0, eax, edx, ebx, ecx, 0);
        }
        else
        {
            vertrix_call(services->calls, 0x43ac00, eax, edx, ebx, ecx, 0);
        }
        if (gate->kind == VERTRIX_GATE_OPPONENT)
        {
            eax = opponent;
        }
        vertrix_call(services->calls, gate->callee, eax, edx, ebx, ecx, 0);
    }
    if (services->virtual_call)
    {
        services->virtual_call(services->virtual_context, board, SLOT_RELEASE, 0);
    }
    switch (gate->kind)
    {
        case VERTRIX_GATE_OPPONENT:
            return vertrix_call(services->calls, 0x43bbf0, player, board, player, vtable, 0);
        case VERTRIX_GATE_SELF_BOARD:
            return vertrix_call(services->calls, 0x43bbf0, player, vtable, player, board, 0);
        default:
            return vertrix_call(services->calls, 0x43bbf0, player, vtable, board, player, 0);
    }
}

/* The tail the three handlers share: slot 1 of the board, then 0x43bbf0 on the player. */
static uint32_t finish_with_board(const VertrixEffectServices *services, uint32_t player,
                                  uint32_t board, uint32_t vtable, uint32_t ebx, uint32_t ecx)
{
    if (services->virtual_call)
    {
        services->virtual_call(services->virtual_context, board, SLOT_RELEASE, 0);
    }
    return vertrix_call(services->calls, 0x43bbf0, player, vtable, ebx, ecx, 0);
}

uint32_t vertrix_effect_negated_gate(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t value;
    uint32_t board;
    uint32_t vtable;
    uint32_t negated;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_NEGATED, DWORD_WIDTH,
                                    &value) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size) ||
        !vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    negated = 0u - value;
    if (vertrix_call(services->calls, 0x43b800, player, negated, board, player, 0) == 1)
    {
        vertrix_call(services->calls, 0x43c0e0, player, SOUND_DROP, board, player, 0);
    }
    else
    {
        vertrix_call(services->calls, 0x43acd0, player, negated, board, player, 0);
    }
    return finish_with_board(services, player, board, vtable, board, player);
}

uint32_t vertrix_effect_value_gate(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t value;
    uint32_t opponent;
    uint32_t board;
    uint32_t vtable;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_VALUE, DWORD_WIDTH,
                                    &value) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size) ||
        !vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    if (vertrix_call(services->calls, 0x43b800, opponent, value, board, player, 0) == 1)
    {
        vertrix_call(services->calls, 0x43c0e0, player, SOUND_GATE, board, player, 0);
        vertrix_call(services->calls, 0x43ac00, player, SOUND_GATE, board, player, 0);
    }
    else
    {
        vertrix_call(services->calls, 0x43acd0, player, value, board, player, 0);
    }
    return finish_with_board(services, player, board, vtable, board, player);
}

uint32_t vertrix_effect_progress_gate(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *opponent_storage;
    void *board_storage;
    size_t player_size;
    size_t opponent_size;
    size_t board_size;
    uint32_t opponent;
    uint32_t board;
    uint32_t vtable;
    uint32_t before;
    uint32_t after;
    uint32_t sound;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, opponent, &opponent_storage, &opponent_size) ||
        !vertrix_actor_storage_read(opponent_storage, opponent_size, PLAYER_PROGRESS, DWORD_WIDTH,
                                    &before) ||
        !resolve_object(services, board, &board_storage, &board_size) ||
        !vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    if (vertrix_call(services->calls, 0x43b7c0, opponent, opponent, board, player, 0) != 1)
    {
        vertrix_call(services->calls, 0x43acd0, player, opponent, board, player, 0);
    }
    else
    {
        if (!vertrix_actor_storage_read(opponent_storage, opponent_size, PLAYER_PROGRESS,
                                        DWORD_WIDTH, &after))
        {
            return 0;
        }
        if (before > after)
        {
            sound = SOUND_DROP;
            vertrix_call(services->calls, 0x43c0e0, player, sound, board, player, 0);
            vertrix_call(services->calls, 0x43acd0, player, sound, board, player, 0);
        }
        else
        {
            sound = SOUND_GATE;
            vertrix_call(services->calls, 0x43c0e0, player, sound, board, player, 0);
            vertrix_call(services->calls, 0x43ac00, player, sound, board, player, 0);
        }
    }
    return finish_with_board(services, player, board, vtable, board, player);
}

static const uint32_t arm_handlers[4] = {0x452a50, 0x452b20, 0x452bd0, 0x452c80};

uint32_t vertrix_effect_arm_handler(const VertrixEffectServices *services, uint32_t player,
                                    uint32_t entry_ebx, unsigned index)
{
    void *player_storage;
    size_t player_size;
    uint32_t board;
    uint32_t mode;
    uint32_t shape = 0;
    uint32_t first = 0;
    uint32_t second = 0;
    uint32_t third = 0;
    uint32_t ebx;
    if (!services || !services->calls || index < 1 || index > 4 ||
        !resolve_object(services, player, &player_storage, &player_size))
    {
        return 0;
    }
    vertrix_call(services->calls, 0x43bad0, player, index, entry_ebx, player, 0);
    /* The state the call may have changed is read afterwards, as the original does. */
    if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_MODE_BYTE, BYTE_WIDTH,
                                    &mode))
    {
        return 0;
    }
    ebx = (entry_ebx & 0xffffff00u) | mode;
    if (mode >= 1 && mode <= 4)
    {
        if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_SHAPE, DWORD_WIDTH,
                                        &shape))
        {
            return 0;
        }
        ebx = shape;
        if ((mode == 1 || mode == 3) && shape == 1)
        {
            third = 1;
        }
        else if (mode == 1 && shape == 2)
        {
            first = 1;
            third = 1;
        }
        else if ((mode == 2 || mode == 4) && shape == 1)
        {
            first = 1;
            second = 1;
            third = 1;
        }
    }
    if (!vertrix_actor_storage_write(player_storage, player_size, PLAYER_ARM_FIRST, DWORD_WIDTH,
                                     first) ||
        !vertrix_actor_storage_write(player_storage, player_size, PLAYER_ARM_SECOND, DWORD_WIDTH,
                                     second) ||
        !vertrix_actor_storage_write(player_storage, player_size, PLAYER_ARM_THIRD, DWORD_WIDTH,
                                     third))
    {
        return 0;
    }
    vertrix_call(services->calls, 0x4ac8f0, player, arm_handlers[index - 1], ebx, player, 0);
    if (services->virtual_call)
    {
        services->virtual_call(services->virtual_context, board, SLOT_RELEASE, 0);
    }
    return vertrix_call(services->calls, 0x43c0e0, player, SOUND_ARMED, ebx, player, 0);
}

uint32_t vertrix_effect_armed_handler(const VertrixEffectServices *services, uint32_t player,
                                      uint32_t entry_ebx, unsigned which)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t extra;
    uint32_t first;
    uint32_t second;
    uint32_t third;
    uint32_t shape;
    uint32_t vtable;
    uint32_t ebx = entry_ebx;
    uint32_t armed = 0;
    uint32_t result;
    if (!services || !services->calls || which > 3 ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_EXTRA, DWORD_WIDTH,
                                    &extra) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_ARM_FIRST, DWORD_WIDTH,
                                    &first) ||
        !resolve_object(services, board, &board_storage, &board_size) ||
        !vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    if (first == 0)
    {
        if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_ARM_SECOND, DWORD_WIDTH,
                                        &second))
        {
            return 0;
        }
        if (second == 0)
        {
            if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_ARM_THIRD,
                                            DWORD_WIDTH, &third) ||
                !vertrix_actor_storage_read(player_storage, player_size, PLAYER_SHAPE, DWORD_WIDTH,
                                            &shape))
            {
                return 0;
            }
            if (third == 0)
            {
                uint32_t stack[3];
                uint32_t edx;
                int call = 0;
                if (shape == 1)
                {
                    call = 1;
                    if (which == 1 || which == 3)
                    {
                        ebx = 6;
                        edx = 6;
                        stack[0] = stack[1] = stack[2] = 1;
                    }
                    else
                    {
                        ebx = 0xffffffffu;
                        edx = 0xffffffffu;
                        stack[0] = 0;
                        stack[1] = third;
                        stack[2] = 1;
                    }
                }
                else if (shape == 2 && which == 0)
                {
                    call = 1;
                    ebx = 0xffffffffu;
                    edx = 6;
                    stack[0] = 1;
                    stack[1] = third;
                    stack[2] = 1;
                }
                if (call)
                {
                    vertrix_call3(services->calls, 0x43a5f0, extra, edx, ebx, 6, stack);
                }
                armed = 1;
            }
        }
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    if (armed)
    {
        return vertrix_call(services->calls, 0x43bbf0, player, 1, ebx, vtable, 0);
    }
    return result;
}

uint32_t vertrix_effect_progress_update_gate(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t step;
    uint32_t opponent;
    uint32_t board;
    uint32_t vtable;
    uint32_t negated;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_PROGRESS_STEP, DWORD_WIDTH,
                                    &step) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size) ||
        !vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    negated = 0u - step;
    if (vertrix_call(services->calls, 0x43b720, opponent, negated, board, player, 0) == 1)
    {
        vertrix_call(services->calls, 0x43c0e0, player, SOUND_DROP, board, player, 0);
        vertrix_call(services->calls, 0x43ac00, player, SOUND_DROP, board, player, 0);
    }
    else
    {
        vertrix_call(services->calls, 0x43acd0, player, negated, board, player, 0);
    }
    return finish_with_board(services, player, board, vtable, board, player);
}

uint32_t vertrix_effect_progress_compare(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *opponent_storage;
    void *board_storage;
    size_t player_size;
    size_t opponent_size;
    size_t board_size;
    uint32_t opponent;
    uint32_t board;
    uint32_t a;
    uint32_t b;
    uint32_t vtable;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_PROGRESS, DWORD_WIDTH,
                                    &a) ||
        !resolve_object(services, opponent, &opponent_storage, &opponent_size) ||
        !vertrix_actor_storage_read(opponent_storage, opponent_size, PLAYER_PROGRESS, DWORD_WIDTH,
                                    &b) ||
        !resolve_object(services, board, &board_storage, &board_size) ||
        !vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    if (a == b)
    {
        vertrix_call(services->calls, 0x43acd0, player, b, player, opponent, 0);
    }
    else
    {
        vertrix_call(services->calls, a < b ? 0x43acd0 : 0x43ac00, player, b, player, opponent, 0);
        vertrix_call(services->calls, 0x43b810, player, b, player, opponent, 0);
        vertrix_call(services->calls, 0x43b810, opponent, a, player, opponent, 0);
        vertrix_call(services->calls, 0x43c0e0, opponent, SOUND_COMPARE, player, opponent, 0);
    }
    return finish_with_board(services, player, board, vtable, player, opponent);
}

uint32_t vertrix_effect_stone_arm(const VertrixEffectServices *services, uint32_t player,
                                  uint32_t entry_edx)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t argument;
    uint32_t vtable;
    uint32_t result;
    int ended = 0;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    vertrix_call(services->calls, 0x436fe0, board, entry_edx, board, player, 0);
    if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_STONE_ARG, DWORD_WIDTH,
                                    &argument))
    {
        return 0;
    }
    if (vertrix_call(services->calls, 0x437060, board, argument, board, player, 0) == 1)
    {
        vertrix_call(services->calls, 0x43c0e0, player, SOUND_COMPARE, board, player, 0);
        vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_STONE_APPLY, board, player, 0);
    }
    else
    {
        ended = 1;
        vertrix_call(services->calls, 0x43acd0, player, argument, board, player, 0);
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    return ended ? vertrix_call(services->calls, 0x43bbf0, player, vtable, board, player, 0)
                 : result;
}

/* Both tests 0x42eca0 and 0x42ecc0 of the board against the field handler are non-zero. */
static int field_tests(const VertrixEffectServices *services, uint32_t player, uint32_t board)
{
    return vertrix_call(services->calls, 0x42eca0, board, HANDLER_FIELD, player, board, 0) != 0 &&
           vertrix_call(services->calls, 0x42ecc0, board, HANDLER_FIELD, player, board, 0) != 0;
}

uint32_t vertrix_effect_stone_apply(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t argument;
    uint32_t vtable;
    uint32_t result;
    int ended = 0;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    if (field_tests(services, player, board))
    {
        if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_STONE_ARG, DWORD_WIDTH,
                                        &argument))
        {
            return 0;
        }
        if (vertrix_call(services->calls, 0x4371b0, board, argument, player, board, 0) == 1)
        {
            vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_STONE_CLEAR, player, board, 0);
            vertrix_call(services->calls, 0x43c0e0, player, SOUND_DROP, player, board, 0);
        }
        else
        {
            ended = 1;
        }
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    return ended ? vertrix_call(services->calls, 0x43bbf0, player, vtable, player, board, 0)
                 : result;
}

uint32_t vertrix_effect_stone_clear(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t vtable;
    uint32_t result;
    int ended = 0;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    if (field_tests(services, player, board))
    {
        ended = 1;
        vertrix_call(services->calls, 0x42ebe0, board, HANDLER_FIELD, player, board, 0);
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    return ended ? vertrix_call(services->calls, 0x43bbf0, player, vtable, player, board, 0)
                 : result;
}
