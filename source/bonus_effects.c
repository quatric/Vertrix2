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
    HANDLER_FIELD = 0x44c860,
    BOARD_FLAG_FOURTH = 0xb90,
    BOARD_FLAG_SLIDE = 0xb8c,
    SOUND_ONE = 1,
    SOUND_TWELVE = 12,
    GLOBAL_DIFFICULTY = 0x532bbc,
    TABLE_SLIDE = 0x4f7c78,
    HANDLER_FIELD_BIND = 0x455510,
    HANDLER_FIELD_NEXT = 0x455580,
    PLAYER_SLIDE_ARG = 0x3e4,
    PLAYER_SLIDE_COUNT = 0x444,
    BOARD_SLIDE_WORD = 0x1a,
    BOARD_SLIDE_POSITION = 0x58,
    BOARD_SLIDE_RATE = 0x18,
    SLIDE_LIMIT = 24,
    TABLE_SLIDE_DWORD = 0x4f7cfc,
    TABLE_SLIDE_WORD = 0x4f7d08,
    HANDLER_SLIDE_WAIT = 0x455f10,
    HANDLER_SLIDE_ADVANCE = 0x455f80,
    HANDLER_SLIDE_END = 0x456060,
    SOUND_TWO = 2,
    PLAYER_STEP_ARG = 0x424,
    PLAYER_STEP_COUNT = 0x428,
    HANDLER_FIELD_END = 0x453ef0,
    PLAYER_COUNTED_ARG = 0x434,
    PLAYER_COUNTED_LEFT = 0x438,
    TABLE_COUNTED_START = 0x4f7c54,
    TABLE_COUNTED_STEP = 0x4f7c60,
    GLOBAL_SOUND_START = 0x4f8190,
    GLOBAL_SOUND_STEP = 0x4f8194,
    HANDLER_COUNTED_START = 0x4548e0,
    BOARD_SLIDE_RATE_B = 0x10,
    PLAYER_STEP_B_ARG = 0x42c,
    PLAYER_STEP_B_COUNT = 0x430,
    HANDLER_FIELD_END_B = 0x454200,
    TABLE_CYCLE_ENTRY = 0x4f7c84,
    TABLE_CYCLE_ROWS = 0x4f7c90,
    PLAYER_CYCLE_KIND = 0x3ec,
    PLAYER_CYCLE_COUNT = 0x448,
    BOARD_CYCLE_FIRST = 0x64,
    BOARD_CYCLE_SECOND = 0x68,
    BOARD_CYCLE_THIRD = 0x6c,
    HANDLER_CYCLE_STEP = 0x4546a0,
    HANDLER_CYCLE_END = 0x454760,
    CYCLE_LIMIT = 10,
    TABLE_MARKED_START = 0x4f7c6c,
    HANDLER_MARKED_END = 0x454fc0,
    HANDLER_GATE_CLEAR = 0x4552b0,
    HANDLER_FINISH = 0x452160,
    HANDLER_NEXT_TOKEN = 0x455e00,
    PLAYER_COUNT_ARG = 0x400,
    PLAYER_COUNT_TOTAL = 0x420,
    TABLE_COUNT_START = 0x4f7d2c,
    HANDLER_COUNT_WAIT = 0x45b590,
    HANDLER_COUNT_STEP = 0x45b5f0,
    OBJECT_VALUE = 0x14c,
    OBJECT_FLAG15C = 0x15c,
    OBJECT_FLAG15D = 0x15d,
    OBJECT_SETTLE_WORD = 0x10,
    OBJECT_SETTLE_WORD_B = 0x18,
    OBJECT_SRC_A = 0x8,
    OBJECT_SRC_B = 0xa,
    OBJECT_FLAG93 = 0x93,
    OBJECT_BYTE4F = 0x4f,
    OBJECT_WORD50 = 0x50,
    OBJECT_BYTE45 = 0x45,
    OBJECT_WORD46 = 0x46,
    GLOBAL_FLIP = 0x5589dc,
    GLOBAL_SELECTION = 0x532b98,
    HANDLER_WAIT_NEXT = 0x456390,
    HANDLER_WAIT_FLIP = 0x456570,
    GLOBAL_OBJECT_VALUE = 0x532a60,
    HANDLER_OBJECT_POLL = 0x456170,
    POINT_LIST = 0x54d640,
    POINT_KIND = 0x74,
    OBJECT_WORD_A = 0x4a,
    OBJECT_WORD_B = 0x4c,
    OBJECT_STATE = 0x48,
    GLOBAL_POINTER_X = 0x558944,
    GLOBAL_POINTER_Y = 0x558946,
    GLOBAL_POINTER_OFF = 0x558958,
    POINTER_OFF_VALUE = 0x7d00,
    LOCAL_FIRST = 0x1c,
    LOCAL_SECOND = 0x18,
    LOCAL_THIRD = 0x14,
    PLAYER_CHAIN = 0x184,
    HANDLER_ARMED_CLEAR = 0x455320,
    HANDLER_ARMED_GATE = 0x4553a0,
    SOUND_KINDS = 11,
    KIND_FIVE = 5,
    LOCAL_KIND_FIRST = 0x1c,
    LOCAL_KIND_SECOND = 0x18,
    LOCAL_KIND_THIRD = 0x20,
    HANDLER_BURST_END = 0x454970
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

/* routine (original address), token bound to the opponent, source, destination and cleared dword
 * offsets (zero for none), clear_b90, call count and calls (target, on_opponent, set_edx, edx). */
const VertrixAttack vertrix_attacks[VERTRIX_ATTACK_COUNT] = {
    {0x453c00,
     0x453c90,
     0x3cc,
     0x424,
     0x428,
     0,
     4,
     {{0x43ac00, 0, 0, 0x0},
      {0x43bb60, 1, 1, 0x4},
      {0x43bae0, 1, 0, 0x0},
      {0x4ac8f0, 1, 1, 0x453c90}}},
    {0x453f40,
     0x453fd0,
     0x3d0,
     0x42c,
     0x430,
     0,
     4,
     {{0x43ac00, 0, 0, 0x0},
      {0x43bb60, 1, 1, 0x4},
      {0x43bae0, 1, 0, 0x0},
      {0x4ac8f0, 1, 1, 0x453fd0}}},
    {0x454250,
     0x4542e0,
     0x3d0,
     0x42c,
     0x430,
     0,
     4,
     {{0x43ac00, 0, 0, 0x0},
      {0x43bb60, 1, 1, 0x4},
      {0x43bae0, 1, 0, 0x0},
      {0x4ac8f0, 1, 1, 0x4542e0}}},
    {0x454560,
     0x454600,
     0x3e8,
     0x3ec,
     0x0,
     0,
     7,
     {{0x43ac00, 0, 0, 0x0},
      {0x43ce00, 1, 0, 0x0},
      {0x43bb60, 1, 1, 0x4},
      {0x43bae0, 1, 0, 0x0},
      {0x43baf0, 1, 1, 0x1},
      {0x43b860, 1, 1, 0x0},
      {0x4ac8f0, 1, 1, 0x454600}}},
    {0x4547b0,
     0x454830,
     0x3d4,
     0x434,
     0x0,
     0,
     3,
     {{0x43bb60, 1, 1, 0x4}, {0x43bae0, 1, 0, 0x0}, {0x4ac8f0, 1, 1, 0x454830}}},
    {0x4549d0,
     0x454a50,
     0x3d8,
     0x438,
     0x0,
     0,
     3,
     {{0x43bb60, 1, 1, 0x4}, {0x43bae0, 1, 0, 0x0}, {0x4ac8f0, 1, 1, 0x454a50}}},
    {0x454c30,
     0x454cb0,
     0x3d8,
     0x438,
     0x0,
     0,
     3,
     {{0x43bb60, 1, 1, 0x4}, {0x43bae0, 1, 0, 0x0}, {0x4ac8f0, 1, 1, 0x454cb0}}},
    {0x454e90,
     0x454f00,
     0x0,
     0x0,
     0x0,
     0,
     3,
     {{0x43bb60, 1, 1, 0x4}, {0x43bae0, 1, 0, 0x0}, {0x4ac8f0, 1, 1, 0x454f00}}},
    {0x455020,
     0x4550a0,
     0x0,
     0x0,
     0x0,
     1,
     3,
     {{0x43bb60, 1, 1, 0x4}, {0x43bae0, 1, 0, 0x0}, {0x4ac8f0, 1, 1, 0x4550a0}}},
    {0x455b20,
     0x455b90,
     0x0,
     0x0,
     0x0,
     0,
     3,
     {{0x43bb60, 1, 1, 0x4}, {0x43bae0, 1, 0, 0x0}, {0x4ac8f0, 1, 1, 0x455b90}}},
    {0x455ca0,
     0x455d10,
     0x0,
     0x0,
     0x0,
     0,
     3,
     {{0x43bb60, 1, 1, 0x4}, {0x43bae0, 1, 0, 0x0}, {0x4ac8f0, 1, 1, 0x455d10}}},
    {0x45b9c0,
     0x45ba30,
     0x0,
     0x0,
     0x0,
     0,
     3,
     {{0x43bb60, 1, 1, 0x4}, {0x43bae0, 1, 0, 0x0}, {0x4ac8f0, 1, 1, 0x45ba30}}}};

uint32_t vertrix_effect_attack(const VertrixEffectServices *services, uint32_t player,
                               uint32_t entry_edx, const VertrixAttack *attack)
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
    uint32_t value = 0;
    uint32_t vtable;
    uint32_t edx = entry_edx;
    unsigned index;
    if (!services || !services->calls || !attack ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &own_board) ||
        !resolve_object(services, opponent, &opponent_storage, &opponent_size) ||
        !vertrix_actor_storage_read(opponent_storage, opponent_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &opponent_board) ||
        !resolve_object(services, own_board, &own_storage, &own_size) ||
        !resolve_object(services, opponent_board, &opponent_board_storage, &opponent_board_size))
    {
        return 0;
    }
    for (index = 0; index < attack->count; ++index)
    {
        const VertrixAttackCall *call = &attack->calls[index];
        if (call->set_edx)
        {
            edx = call->edx;
        }
        vertrix_call(services->calls, call->target, call->on_opponent ? opponent : player, edx,
                     player, opponent, 0);
    }
    if ((attack->source && !vertrix_actor_storage_read(player_storage, player_size, attack->source,
                                                       DWORD_WIDTH, &value)) ||
        (attack->cleared && !vertrix_actor_storage_write(opponent_storage, opponent_size,
                                                         attack->cleared, DWORD_WIDTH, 0)) ||
        (attack->destination &&
         !vertrix_actor_storage_write(opponent_storage, opponent_size, attack->destination,
                                      DWORD_WIDTH, value)) ||
        !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size, BOARD_FLAG_FIRST,
                                     DWORD_WIDTH, 1) ||
        !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size, BOARD_FLAG_SECOND,
                                     DWORD_WIDTH, 1) ||
        !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size, BOARD_FLAG_THIRD,
                                     DWORD_WIDTH, 1) ||
        (attack->clear_b90 &&
         !vertrix_actor_storage_write(opponent_board_storage, opponent_board_size,
                                      BOARD_FLAG_FOURTH, DWORD_WIDTH, 0)) ||
        !vertrix_actor_storage_read(own_storage, own_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    if (services->virtual_call)
    {
        services->virtual_call(services->virtual_context, own_board, SLOT_RELEASE, 0);
    }
    return vertrix_call(services->calls, 0x43bbf0, player, edx, player, vtable, 0);
}

const VertrixCheckBind vertrix_check_binds[VERTRIX_CHECK_BIND_COUNT] = {
    {0x4554a0, 0x4372c0, 0x437350, VERTRIX_CHECK_FIELD, 0x455510},
    {0x455600, 0x437240, 0x437350, VERTRIX_CHECK_FIELD, 0x455510},
    {0x455670, 0x4375a0, 0x4375f0, VERTRIX_CHECK_BOARD, 0x455700},
    {0x455790, 0x4375a0, 0x4378c0, VERTRIX_CHECK_SLIDE, 0x455830},
    {0x4558e0, 0x4375a0, 0x437be0, VERTRIX_CHECK_BOARD, 0x455970},
    {0x455a00, 0x4375a0, 0x437d70, VERTRIX_CHECK_BOARD, 0x455a90}};

uint32_t vertrix_effect_check_bind(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_edx, const VertrixCheckBind *check)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t vtable;
    uint32_t result;
    uint32_t ebx;
    uint32_t ecx;
    int ended = 0;
    if (!services || !services->calls || !check ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    ebx = check->kind == VERTRIX_CHECK_SLIDE ? player : board;
    ecx = check->kind == VERTRIX_CHECK_SLIDE ? board : player;
    vertrix_call(services->calls, check->first, board, entry_edx, ebx, ecx, 0);
    if (vertrix_call(services->calls, check->second, board, entry_edx, ebx, ecx, 0) == 1)
    {
        if (check->kind == VERTRIX_CHECK_FIELD)
        {
            vertrix_call(services->calls, 0x43c0e0, player, SOUND_COMPARE, ebx, ecx, 0);
            vertrix_call(services->calls, 0x4ac8f0, player, check->token, ebx, ecx, 0);
        }
        else
        {
            vertrix_call(services->calls, 0x43c0e0, player, SOUND_ONE, ebx, ecx, 0);
            vertrix_call(services->calls, 0x43c0e0, player, SOUND_TWELVE, ebx, ecx, 0);
            vertrix_call(services->calls, 0x4ac8f0, player, check->token, ebx, ecx, 0);
            if (check->kind == VERTRIX_CHECK_SLIDE)
            {
                uint32_t mode;
                uint32_t entry;
                if (!services->global)
                {
                    return 0;
                }
                mode = services->global(GLOBAL_DIFFICULTY, services->global_context);
                entry = services->global(TABLE_SLIDE + 4u * mode, services->global_context);
                vertrix_call(services->calls, 0x4ac7b0, board, entry, ebx, ecx, 0);
                vertrix_call(services->calls, 0x4ac510, board, entry, ebx, ecx, 0);
            }
            if (!vertrix_actor_storage_write(board_storage, board_size, BOARD_FLAG_SLIDE,
                                             DWORD_WIDTH, 1))
            {
                return 0;
            }
        }
    }
    else
    {
        ended = 1;
        vertrix_call(services->calls, 0x43acd0,
                     check->kind == VERTRIX_CHECK_SLIDE ? player : player, entry_edx, ebx, ecx, 0);
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    return ended ? vertrix_call(services->calls, 0x43bbf0, player, vtable, ebx, ecx, 0) : result;
}

uint32_t vertrix_effect_field_bind(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t vtable;
    uint32_t edx = HANDLER_FIELD;
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
        edx = SOUND_ONE;
        vertrix_call(services->calls, 0x43c0e0, player, edx, player, board, 0);
        edx = HANDLER_FIELD_NEXT;
        vertrix_call(services->calls, 0x437460, board, edx, player, board, 0);
        vertrix_call(services->calls, 0x4ac8f0, player, edx, player, board, 0);
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    return services->virtual_call
               ? (uint32_t)services->virtual_call(services->virtual_context, board, SLOT_RELEASE, 0)
               : 0;
}

uint32_t vertrix_effect_slide_begin(const VertrixEffectServices *services, uint32_t player)
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
    if (!services || !services->calls || !services->global ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_SLIDE_ARG, DWORD_WIDTH,
                                    &argument) ||
        !vertrix_actor_storage_write(player_storage, player_size, PLAYER_SLIDE_COUNT, DWORD_WIDTH,
                                     0) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    if (vertrix_call(services->calls, 0x438910, board, 0, argument, board, 0) == 1)
    {
        uint32_t mode = services->global(GLOBAL_DIFFICULTY, services->global_context);
        uint32_t entry = services->global(TABLE_SLIDE_DWORD + 4u * mode, services->global_context);
        uint32_t word = services->global(TABLE_SLIDE_WORD + 4u * mode, services->global_context);
        vertrix_call(services->calls, 0x4ac7b0, board, entry, argument, board, 0);
        if (!vertrix_actor_storage_write(board_storage, board_size, BOARD_SLIDE_WORD, 2,
                                         word & 0xffffu) ||
            !vertrix_actor_storage_write(board_storage, board_size, BOARD_SLIDE_POSITION,
                                         DWORD_WIDTH, 0))
        {
            return 0;
        }
        vertrix_call(services->calls, 0x4ac510, board, HANDLER_SLIDE_WAIT, argument, board, 0);
        vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_SLIDE_WAIT, argument, board, 0);
        vertrix_call(services->calls, 0x43d2b0, player, HANDLER_SLIDE_WAIT, argument, board, 0);
        vertrix_call(services->calls, 0x4300b0, board, HANDLER_SLIDE_WAIT, argument, board, 0);
    }
    else
    {
        ended = 1;
        vertrix_call(services->calls, 0x43acd0, player, 0, argument, board, 0);
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    return ended ? vertrix_call(services->calls, 0x43bbf0, player, vtable, argument, board, 0)
                 : result;
}

/* The slot 1 call every slide handler ends with; returns its result. */
static uint32_t release_board(const VertrixEffectServices *services, uint32_t board,
                              void *board_storage, size_t board_size)
{
    uint32_t vtable;
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    return services->virtual_call
               ? (uint32_t)services->virtual_call(services->virtual_context, board, SLOT_RELEASE, 0)
               : 0;
}

uint32_t vertrix_effect_slide_wait(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_edx)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    vertrix_call(services->calls, 0x4ac500, board, entry_edx, player, board, 0);
    if (vertrix_call(services->calls, 0x4ac520, board, entry_edx, player, board, 0) == 1)
    {
        vertrix_call(services->calls, 0x4ac5b0, board, entry_edx, player, board, 0);
    }
    if (vertrix_call(services->calls, 0x430090, board, entry_edx, player, board, 0) == 1)
    {
        vertrix_call(services->calls, 0x43c0e0, player, SOUND_TWO, player, board, 0);
        vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_SLIDE_ADVANCE, player, board, 0);
    }
    return release_board(services, board, board_storage, board_size);
}

uint32_t vertrix_effect_slide_advance(const VertrixEffectServices *services, uint32_t player,
                                      uint32_t entry_ebx, uint32_t entry_edx)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t position;
    uint32_t count;
    uint32_t argument;
    uint32_t rate;
    uint32_t edx = entry_edx;
    uint32_t ebx = entry_ebx;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    vertrix_call(services->calls, 0x4ac500, board, edx, ebx, board, 0);
    if (vertrix_call(services->calls, 0x4ac520, board, edx, ebx, board, 0) == 1)
    {
        edx = vertrix_call(services->calls, 0x4ac540, board, edx, ebx, board, 0);
        vertrix_call(services->calls, 0x4ac5b0, board, edx, ebx, board, 0);
        if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_SLIDE_RATE, DWORD_WIDTH,
                                        &rate) ||
            !vertrix_actor_storage_read(board_storage, board_size, BOARD_SLIDE_POSITION,
                                        DWORD_WIDTH, &position))
        {
            return 0;
        }
        edx = (uint32_t)((int32_t)edx * ((int32_t)rate >> 16));
        if (!vertrix_actor_storage_write(board_storage, board_size, BOARD_SLIDE_POSITION,
                                         DWORD_WIDTH, position + edx))
        {
            return 0;
        }
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_SLIDE_POSITION, DWORD_WIDTH,
                                    &position))
    {
        return 0;
    }
    if ((int32_t)position < SLIDE_LIMIT)
    {
        vertrix_call(services->calls, 0x42f2e0, board, edx, ebx, board, 0);
        return release_board(services, board, board_storage, board_size);
    }
    vertrix_call(services->calls, 0x42f760, board, edx, ebx, board, 0);
    if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_SLIDE_COUNT, DWORD_WIDTH,
                                    &count) ||
        !vertrix_actor_storage_write(player_storage, player_size, PLAYER_SLIDE_COUNT, DWORD_WIDTH,
                                     count + 1) ||
        !vertrix_actor_storage_read(board_storage, board_size, BOARD_SLIDE_POSITION, DWORD_WIDTH,
                                    &position))
    {
        return 0;
    }
    count += 1;
    while ((int32_t)position >= SLIDE_LIMIT)
    {
        position -= SLIDE_LIMIT;
        if (!vertrix_actor_storage_write(board_storage, board_size, BOARD_SLIDE_POSITION,
                                         DWORD_WIDTH, position))
        {
            return 0;
        }
    }
    if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_SLIDE_ARG, DWORD_WIDTH,
                                    &argument) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_SLIDE_COUNT, DWORD_WIDTH,
                                    &count))
    {
        return 0;
    }
    if (vertrix_call(services->calls, 0x438910, board, count, argument, board, 0) != 0)
    {
        vertrix_call(services->calls, 0x43c0e0, player, SOUND_TWO, argument, board, 0);
    }
    else
    {
        vertrix_call(services->calls, 0x430100, board, HANDLER_SLIDE_END, argument, board, 0);
        vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_SLIDE_END, argument, board, 0);
    }
    return release_board(services, board, board_storage, board_size);
}

uint32_t vertrix_effect_slide_end(const VertrixEffectServices *services, uint32_t player,
                                  uint32_t entry_ebx)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t vtable;
    uint32_t ebx = entry_ebx;
    uint32_t result;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    vertrix_call(services->calls, 0x4ac500, board, board, ebx, player, 0);
    ebx = 0;
    if (vertrix_call(services->calls, 0x4ac520, board, board, ebx, player, 0) == 1)
    {
        vertrix_call(services->calls, 0x4ac5b0, board, board, ebx, player, 0);
    }
    if (vertrix_call(services->calls, 0x430090, board, board, ebx, player, 0) == 1)
    {
        ebx = 1;
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    return ebx == 1 ? vertrix_call(services->calls, 0x43bbf0, player, board, ebx, player, 0)
                    : result;
}

const VertrixSlideStart vertrix_slide_starts[VERTRIX_SLIDE_START_COUNT] = {
    {0x453c90, 0x4314a0, 0x424, 0x428, 0x4f7c0c, 0x4f7c18, 0x1a, 0x453d50},
    {0x453fd0, 0x431780, 0x42c, 0x430, 0x4f7c3c, 0x4f7c48, 0x12, 0x454090},
    {0x4542e0, 0x431930, 0x42c, 0x430, 0x4f7c3c, 0x4f7c48, 0x12, 0x4543a0}};

uint32_t vertrix_effect_slide_start(const VertrixEffectServices *services, uint32_t player,
                                    const VertrixSlideStart *start)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t first;
    uint32_t second;
    uint32_t vtable;
    uint32_t result;
    int ended = 0;
    if (!services || !services->calls || !services->global || !start ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, start->second_offset, DWORD_WIDTH,
                                    &second) ||
        !vertrix_actor_storage_read(player_storage, player_size, start->first_offset, DWORD_WIDTH,
                                    &first) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    if (vertrix_call(services->calls, start->check, board, first, second, board, 0) == 1)
    {
        uint32_t mode = services->global(GLOBAL_DIFFICULTY, services->global_context);
        uint32_t entry = services->global(start->dword_table + 4u * mode, services->global_context);
        uint32_t word = services->global(start->word_table + 4u * mode, services->global_context);
        vertrix_call(services->calls, 0x4ac7b0, board, entry, second, board, 0);
        if (!vertrix_actor_storage_write(board_storage, board_size, start->word_offset, 2,
                                         word & 0xffffu) ||
            !vertrix_actor_storage_write(board_storage, board_size, BOARD_SLIDE_POSITION,
                                         DWORD_WIDTH, 0))
        {
            return 0;
        }
        vertrix_call(services->calls, 0x4ac510, board, start->token, second, board, 0);
        vertrix_call(services->calls, 0x4ac8f0, player, start->token, second, board, 0);
        vertrix_call(services->calls, 0x43c0e0, player, SOUND_TWO, second, board, 0);
    }
    else
    {
        ended = 1;
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    return ended ? vertrix_call(services->calls, 0x43bbf0, player, vtable, second, board, 0)
                 : result;
}

uint32_t vertrix_effect_field_end(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t vtable;
    uint32_t result;
    uint32_t ebx = 0;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    if (vertrix_call(services->calls, 0x42eca0, board, HANDLER_FIELD, ebx, board, 0) != 0)
    {
        ebx = 1;
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    return ebx == 1 ? vertrix_call(services->calls, 0x43bbf0, player, vtable, ebx, board, 0)
                    : result;
}

uint32_t vertrix_effect_slide_step(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_ebx, uint32_t entry_ecx, uint32_t entry_edx)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t extra;
    uint32_t position;
    uint32_t rate;
    uint32_t pending;
    uint32_t count;
    uint32_t argument;
    uint32_t ebx = entry_ebx;
    uint32_t ecx = entry_ecx;
    uint32_t edx = entry_edx;
    const VertrixCalls *calls;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_EXTRA, DWORD_WIDTH,
                                    &extra) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac500, board, edx, ebx, ecx, 0);
    if (vertrix_call(calls, 0x4ac520, board, edx, ebx, ecx, 0) == 1)
    {
        edx = vertrix_call(calls, 0x4ac540, board, edx, ebx, ecx, 0);
        vertrix_call(calls, 0x4ac5b0, board, edx, ebx, ecx, 0);
        if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_SLIDE_RATE, DWORD_WIDTH,
                                        &rate) ||
            !vertrix_actor_storage_read(board_storage, board_size, BOARD_SLIDE_POSITION,
                                        DWORD_WIDTH, &position))
        {
            return 0;
        }
        edx = (uint32_t)((int32_t)edx * ((int32_t)rate >> 16));
        if (!vertrix_actor_storage_write(board_storage, board_size, BOARD_SLIDE_POSITION,
                                         DWORD_WIDTH, position + edx))
        {
            return 0;
        }
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_SLIDE_POSITION, DWORD_WIDTH,
                                    &position))
    {
        return 0;
    }
    if ((int32_t)position < SLIDE_LIMIT)
    {
        vertrix_call(calls, 0x42f210, board, edx, ebx, ecx, 0);
        if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_STEP_COUNT, DWORD_WIDTH,
                                        &ebx) ||
            !vertrix_actor_storage_read(player_storage, player_size, PLAYER_STEP_ARG, DWORD_WIDTH,
                                        &edx))
        {
            return 0;
        }
        vertrix_call(calls, 0x42f280, board, edx, ebx, ecx, 0);
        return release_board(services, board, board_storage, board_size);
    }
    if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_STEP_COUNT, DWORD_WIDTH,
                                    &ebx) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_STEP_ARG, DWORD_WIDTH,
                                    &edx))
    {
        return 0;
    }
    vertrix_call(calls, 0x42f3d0, board, edx, ebx, ecx, 0);
    vertrix_call(calls, 0x42f310, board, edx, ebx, ecx, 0);
    if (vertrix_call(calls, 0x4320c0, board, edx, ebx, ecx, 0) == 1)
    {
        if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_PENDING, DWORD_WIDTH,
                                        &pending))
        {
            return 0;
        }
        if (pending == 1 && vertrix_call(calls, 0x431d60, board, edx, ebx, ecx, 0) == 0)
        {
            uint32_t kinds[3];
            if (!piece_kinds(services, board_storage, board_size, kinds))
            {
                return 0;
            }
            edx = kinds[0];
            ebx = kinds[1];
            ecx = kinds[2];
            vertrix_call(calls, 0x43a560, extra, edx, ebx, ecx, 0);
            if (!vertrix_actor_storage_write(player_storage, player_size, PLAYER_PENDING,
                                             DWORD_WIDTH, 0))
            {
                return 0;
            }
        }
        if (vertrix_call(calls, 0x432010, board, edx, ebx, ecx, 0) == 0)
        {
            edx = vertrix_call(calls, 0x431340, board, edx, ebx, ecx, 0);
            vertrix_call(calls, 0x431d80, board, edx, ebx, ecx, 0);
            vertrix_call(calls, 0x42eb60, board, edx, ebx, ecx, 0);
        }
    }
    if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_STEP_COUNT, DWORD_WIDTH,
                                    &count) ||
        !vertrix_actor_storage_write(player_storage, player_size, PLAYER_STEP_COUNT, DWORD_WIDTH,
                                     count + 1) ||
        !vertrix_actor_storage_read(board_storage, board_size, BOARD_SLIDE_POSITION, DWORD_WIDTH,
                                    &position))
    {
        return 0;
    }
    while ((int32_t)position >= SLIDE_LIMIT)
    {
        position -= SLIDE_LIMIT;
        if (!vertrix_actor_storage_write(board_storage, board_size, BOARD_SLIDE_POSITION,
                                         DWORD_WIDTH, position))
        {
            return 0;
        }
    }
    if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_STEP_COUNT, DWORD_WIDTH,
                                    &ebx) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_STEP_ARG, DWORD_WIDTH,
                                    &argument))
    {
        return 0;
    }
    edx = argument;
    if (vertrix_call(calls, 0x4314a0, board, edx, ebx, ecx, 0) == 0)
    {
        vertrix_call(calls, 0x4ac8f0, player, HANDLER_FIELD_END, ebx, ecx, 0);
    }
    else
    {
        vertrix_call(calls, 0x43c0e0, player, SOUND_TWO, ebx, ecx, 0);
    }
    return release_board(services, board, board_storage, board_size);
}

uint32_t vertrix_effect_counted_start(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t opponent;
    uint32_t argument;
    uint32_t vtable;
    uint32_t result;
    uint32_t edx;
    int ended = 0;
    if (!services || !services->calls || !services->global ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_COUNTED_ARG, DWORD_WIDTH,
                                    &argument) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    vertrix_call(services->calls, 0x435e80, board, argument, player, board, 0);
    if (vertrix_call(services->calls, 0x436150, board, argument, player, board, 0) == 1)
    {
        uint32_t mode = services->global(GLOBAL_DIFFICULTY, services->global_context);
        uint32_t entry =
            services->global(TABLE_COUNTED_START + 4u * mode, services->global_context);
        vertrix_call(services->calls, 0x4ac7b0, board, entry, player, board, 0);
        vertrix_call(services->calls, 0x4ac510, board, HANDLER_COUNTED_START, player, board, 0);
        vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_COUNTED_START, player, board, 0);
        edx = services->global(GLOBAL_SOUND_START, services->global_context);
        vertrix_call(services->calls, 0x43c0e0, player, edx, player, board, 0);
        vertrix_call(services->calls, 0x43ac00, opponent, edx, player, board, 0);
    }
    else
    {
        ended = 1;
        vertrix_call(services->calls, 0x43acd0, opponent, argument, player, board, 0);
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

const VertrixCountedStep vertrix_counted_steps[VERTRIX_COUNTED_STEP_COUNT] = {
    {0x454a50, 0x435e80, 1, 0x436440, 0x454b20}, {0x454cb0, 0x435f30, 0, 0x4365c0, 0x454d80}};

uint32_t vertrix_effect_counted_step(const VertrixEffectServices *services, uint32_t player,
                                     const VertrixCountedStep *step)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t opponent;
    uint32_t left;
    uint32_t vtable;
    uint32_t result;
    int ended = 0;
    if (!services || !services->calls || !services->global || !step ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    vertrix_call(services->calls, step->first, board, step->first_edx, player, board, 0);
    if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_COUNTED_LEFT, DWORD_WIDTH,
                                    &left))
    {
        return 0;
    }
    if ((int32_t)left > 0 &&
        vertrix_call(services->calls, step->check, board, 5, player, board, 0) == 1)
    {
        uint32_t mode = services->global(GLOBAL_DIFFICULTY, services->global_context);
        uint32_t entry = services->global(TABLE_COUNTED_STEP + 4u * mode, services->global_context);
        uint32_t sound;
        if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_COUNTED_LEFT,
                                        DWORD_WIDTH, &left) ||
            !vertrix_actor_storage_write(player_storage, player_size, PLAYER_COUNTED_LEFT,
                                         DWORD_WIDTH, left - 1))
        {
            return 0;
        }
        vertrix_call(services->calls, 0x4ac7b0, board, entry, player, board, 0);
        vertrix_call(services->calls, 0x4ac510, board, step->token, player, board, 0);
        vertrix_call(services->calls, 0x4ac8f0, player, step->token, player, board, 0);
        sound = services->global(GLOBAL_SOUND_STEP, services->global_context);
        vertrix_call(services->calls, 0x43c0e0, player, sound, player, board, 0);
        vertrix_call(services->calls, 0x43ac00, opponent, sound, player, board, 0);
    }
    else
    {
        ended = 1;
        vertrix_call(services->calls, 0x43acd0, opponent, 1, player, board, 0);
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

const VertrixSlideStepB vertrix_slide_steps_b[VERTRIX_SLIDE_STEP_B_COUNT] = {
    {0x454090, 0, 0x42f440, 0x42f520, 0x42f6e0, 0x42f580, 0x432040, 0x431780, 0x454200},
    {0x4543a0, 1, 0x42f4b0, 0x42f550, 0x42f720, 0x42f620, 0x432080, 0x431930, 0x454510}};

uint32_t vertrix_effect_slide_step_b(const VertrixEffectServices *services, uint32_t player,
                                     uint32_t entry_ebx, uint32_t entry_ecx, uint32_t entry_edx,
                                     const VertrixSlideStepB *step)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t extra;
    uint32_t position;
    uint32_t rate;
    uint32_t pending;
    uint32_t count;
    uint32_t ebx = entry_ebx;
    uint32_t ecx = entry_ecx;
    uint32_t edx = entry_edx;
    uint32_t pre_edx;
    const VertrixCalls *calls;
    if (!services || !services->calls || !step ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_EXTRA, DWORD_WIDTH,
                                    &extra) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac500, board, edx, ebx, ecx, 0);
    if (vertrix_call(calls, 0x4ac520, board, edx, ebx, ecx, 0) == 1)
    {
        edx = vertrix_call(calls, 0x4ac540, board, edx, ebx, ecx, 0);
        vertrix_call(calls, 0x4ac5b0, board, edx, ebx, ecx, 0);
        if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_SLIDE_RATE_B, DWORD_WIDTH,
                                        &rate) ||
            !vertrix_actor_storage_read(board_storage, board_size, BOARD_SLIDE_POSITION,
                                        DWORD_WIDTH, &position))
        {
            return 0;
        }
        edx = (uint32_t)((int32_t)edx * ((int32_t)rate >> 16));
        if (!vertrix_actor_storage_write(board_storage, board_size, BOARD_SLIDE_POSITION,
                                         DWORD_WIDTH,
                                         step->negative ? position - edx : position + edx))
        {
            return 0;
        }
    }
    pre_edx = edx;
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_SLIDE_POSITION, DWORD_WIDTH,
                                    &position) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_STEP_B_COUNT, DWORD_WIDTH,
                                    &ebx) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_STEP_B_ARG, DWORD_WIDTH,
                                    &edx))
    {
        return 0;
    }
    if (step->negative ? (int32_t)position > -SLIDE_LIMIT : (int32_t)position < SLIDE_LIMIT)
    {
        vertrix_call(calls, step->small_first, board, pre_edx, entry_ebx, entry_ecx, 0);
        vertrix_call(calls, step->small_second, board, edx, ebx, entry_ecx, 0);
        return release_board(services, board, board_storage, board_size);
    }
    vertrix_call(calls, step->big_first, board, edx, ebx, ecx, 0);
    vertrix_call(calls, step->big_second, board, edx, ebx, ecx, 0);
    if (vertrix_call(calls, 0x4320c0, board, edx, ebx, ecx, 0) == 1 &&
        vertrix_call(calls, step->check, board, edx, ebx, ecx, 0) == 1)
    {
        if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_PENDING, DWORD_WIDTH,
                                        &pending))
        {
            return 0;
        }
        if (pending == 1)
        {
            uint32_t kinds[3];
            if (!piece_kinds(services, board_storage, board_size, kinds))
            {
                return 0;
            }
            edx = kinds[0];
            ebx = kinds[1];
            ecx = kinds[2];
            vertrix_call(calls, 0x43a560, extra, edx, ebx, ecx, 0);
            if (!vertrix_actor_storage_write(player_storage, player_size, PLAYER_PENDING,
                                             DWORD_WIDTH, 0))
            {
                return 0;
            }
        }
        vertrix_call(calls, 0x42eb60, board, edx, ebx, ecx, 0);
    }
    if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_STEP_B_COUNT, DWORD_WIDTH,
                                    &count) ||
        !vertrix_actor_storage_write(player_storage, player_size, PLAYER_STEP_B_COUNT, DWORD_WIDTH,
                                     count + 1) ||
        !vertrix_actor_storage_read(board_storage, board_size, BOARD_SLIDE_POSITION, DWORD_WIDTH,
                                    &position))
    {
        return 0;
    }
    while (step->negative ? (int32_t)position <= -SLIDE_LIMIT : (int32_t)position >= SLIDE_LIMIT)
    {
        position = step->negative ? position + SLIDE_LIMIT : position - SLIDE_LIMIT;
        if (!vertrix_actor_storage_write(board_storage, board_size, BOARD_SLIDE_POSITION,
                                         DWORD_WIDTH, position))
        {
            return 0;
        }
    }
    if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_STEP_B_COUNT, DWORD_WIDTH,
                                    &ebx) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_STEP_B_ARG, DWORD_WIDTH,
                                    &edx))
    {
        return 0;
    }
    if (vertrix_call(calls, step->tail, board, edx, ebx, ecx, 0) == 0)
    {
        vertrix_call(calls, 0x4ac8f0, player, step->token, ebx, ecx, 0);
    }
    else
    {
        vertrix_call(calls, 0x43c0e0, player, SOUND_TWO, ebx, ecx, 0);
    }
    return release_board(services, board, board_storage, board_size);
}

uint32_t vertrix_effect_cycle_start(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t kind;
    uint32_t mode;
    uint32_t entry;
    if (!services || !services->calls || !services->global ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    mode = services->global(GLOBAL_DIFFICULTY, services->global_context);
    entry = services->global(TABLE_CYCLE_ENTRY + 4u * mode, services->global_context);
    vertrix_call(services->calls, 0x4ac7b0, board, entry, board, player, 0);
    mode = services->global(GLOBAL_DIFFICULTY, services->global_context);
    if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_CYCLE_KIND, DWORD_WIDTH,
                                    &kind))
    {
        return 0;
    }
    entry = services->global(TABLE_CYCLE_ROWS + 20u * mode + 4u * kind, services->global_context);
    vertrix_call(services->calls, 0x43b930, player, entry, board, player, 0);
    if (!vertrix_actor_storage_write(player_storage, player_size, PLAYER_CYCLE_COUNT, DWORD_WIDTH,
                                     0) ||
        !vertrix_actor_storage_write(board_storage, board_size, BOARD_CYCLE_FIRST, DWORD_WIDTH,
                                     0) ||
        !vertrix_actor_storage_write(board_storage, board_size, BOARD_CYCLE_SECOND, DWORD_WIDTH,
                                     4) ||
        !vertrix_actor_storage_write(board_storage, board_size, BOARD_CYCLE_THIRD, DWORD_WIDTH, 1))
    {
        return 0;
    }
    entry = services->global(GLOBAL_SOUND_STEP, services->global_context);
    vertrix_call(services->calls, 0x43c0e0, player, entry, board, player, 0);
    if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_CYCLE_KIND, BYTE_WIDTH,
                                    &kind))
    {
        return 0;
    }
    vertrix_call(services->calls, 0x438960, board, kind, board, player, 0);
    vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_CYCLE_STEP, board, player, 0);
    return release_board(services, board, board_storage, board_size);
}

uint32_t vertrix_effect_cycle_step(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_edx)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t kind;
    uint32_t count;
    uint32_t edx = entry_edx;
    const VertrixCalls *calls;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac500, board, edx, player, board, 0);
    if (vertrix_call(calls, 0x4ac520, board, edx, player, board, 0) == 1)
    {
        edx = vertrix_call(calls, 0x4ac540, board, edx, player, board, 0);
        vertrix_call(calls, 0x4ac5b0, board, edx, player, board, 0);
        if (vertrix_call(calls, 0x4ad750, board, edx, player, board, 0) == 0)
        {
            if (!vertrix_actor_storage_write(board_storage, board_size, BOARD_CYCLE_FIRST,
                                             DWORD_WIDTH, 0) ||
                !vertrix_actor_storage_read(player_storage, player_size, PLAYER_CYCLE_KIND,
                                            DWORD_WIDTH, &kind))
            {
                return 0;
            }
            if (kind == 1)
            {
                if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_CYCLE_COUNT,
                                                BYTE_WIDTH, &edx))
                {
                    return 0;
                }
                vertrix_call(calls, 0x438c60, board, edx, player, board, 0);
                if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_CYCLE_COUNT,
                                                DWORD_WIDTH, &count) ||
                    !vertrix_actor_storage_write(player_storage, player_size, PLAYER_CYCLE_COUNT,
                                                 DWORD_WIDTH, count + 1) ||
                    ((int32_t)(count + 1) >= CYCLE_LIMIT &&
                     !vertrix_actor_storage_write(player_storage, player_size, PLAYER_CYCLE_COUNT,
                                                  DWORD_WIDTH, 0)))
                {
                    return 0;
                }
            }
        }
    }
    if (vertrix_call(calls, 0x43b970, player, edx, player, board, 0) == 0)
    {
        if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_CYCLE_KIND, BYTE_WIDTH,
                                        &edx))
        {
            return 0;
        }
        vertrix_call(calls, 0x438b90, board, edx, player, board, 0);
        vertrix_call(calls, 0x4ac8f0, player, HANDLER_CYCLE_END, player, board, 0);
    }
    return release_board(services, board, board_storage, board_size);
}

uint32_t vertrix_effect_burst_step(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_ecx, uint32_t entry_edx)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t edx = entry_edx;
    uint32_t ecx = entry_ecx;
    const VertrixCalls *calls;
    if (!services || !services->calls || !services->global ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac500, board, edx, board, ecx, 0);
    if (vertrix_call(calls, 0x4ac520, board, edx, board, ecx, 0) != 1)
    {
        return release_board(services, board, board_storage, board_size);
    }
    edx = vertrix_call(calls, 0x4ac540, board, edx, board, ecx, 0);
    ecx = edx;
    vertrix_call(calls, 0x4ac5b0, board, edx, board, ecx, 0);
    if (edx != 0)
    {
        do
        {
            if (vertrix_call(calls, 0x436150, board, edx, board, ecx, 0) != 1)
            {
                break;
            }
            edx = services->global(GLOBAL_SOUND_START, services->global_context);
            ecx -= 1;
            vertrix_call(calls, 0x43c0e0, player, edx, board, ecx, 0);
        } while (ecx != 0);
    }
    if (ecx != 0)
    {
        vertrix_call(calls, 0x4ac8f0, player, HANDLER_BURST_END, board, ecx, 0);
    }
    return release_board(services, board, board_storage, board_size);
}

const VertrixBurstStep vertrix_burst_steps[VERTRIX_BURST_STEP_COUNT] = {
    {0x454b20, 0x436440, 0x454bd0}, {0x454d80, 0x4365c0, 0x454e30}};

uint32_t vertrix_effect_counted_burst_step(const VertrixEffectServices *services, uint32_t player,
                                           uint32_t entry_ebx, uint32_t entry_edx,
                                           const VertrixBurstStep *step)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t left;
    uint32_t edx = entry_edx;
    uint32_t ebx = entry_ebx;
    const VertrixCalls *calls;
    if (!services || !services->calls || !services->global || !step ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac500, board, edx, ebx, player, 0);
    if (vertrix_call(calls, 0x4ac520, board, edx, ebx, player, 0) != 1)
    {
        return release_board(services, board, board_storage, board_size);
    }
    edx = vertrix_call(calls, 0x4ac540, board, edx, ebx, player, 0);
    ebx = edx;
    vertrix_call(calls, 0x4ac5b0, board, edx, ebx, player, 0);
    if (edx != 0)
    {
        for (;;)
        {
            if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_COUNTED_LEFT,
                                            DWORD_WIDTH, &left))
            {
                return 0;
            }
            if ((int32_t)left <= 0 ||
                vertrix_call(calls, step->check, board, 5, ebx, player, 0) != 1)
            {
                break;
            }
            edx = services->global(GLOBAL_SOUND_STEP, services->global_context);
            if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_COUNTED_LEFT,
                                            DWORD_WIDTH, &left))
            {
                return 0;
            }
            ebx -= 1;
            if (!vertrix_actor_storage_write(player_storage, player_size, PLAYER_COUNTED_LEFT,
                                             DWORD_WIDTH, left - 1))
            {
                return 0;
            }
            vertrix_call(calls, 0x43c0e0, player, edx, ebx, player, 0);
            if (ebx == 0)
            {
                break;
            }
        }
    }
    if (ebx != 0)
    {
        vertrix_call(calls, 0x4ac8f0, player, step->token, ebx, player, 0);
    }
    return release_board(services, board, board_storage, board_size);
}

uint32_t vertrix_effect_marked_start(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t opponent;
    uint32_t vtable;
    uint32_t result;
    uint32_t ebx = player;
    int ended = 0;
    if (!services || !services->calls || !services->global ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    vertrix_call(services->calls, 0x436850, board, 0, ebx, board, 0);
    if (vertrix_call(services->calls, 0x436720, board, 5, ebx, board, 0) == 1)
    {
        uint32_t mode = services->global(GLOBAL_DIFFICULTY, services->global_context);
        uint32_t entry = services->global(TABLE_MARKED_START + 4u * mode, services->global_context);
        uint32_t sound;
        vertrix_call(services->calls, 0x4ac7b0, board, entry, ebx, board, 0);
        vertrix_call(services->calls, 0x4ac510, board, HANDLER_MARKED_END, ebx, board, 0);
        vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_MARKED_END, ebx, board, 0);
        sound = services->global(GLOBAL_SOUND_STEP, services->global_context);
        vertrix_call(services->calls, 0x43c0e0, player, sound, ebx, board, 0);
        vertrix_call(services->calls, 0x43ac00, opponent, sound, ebx, board, 0);
    }
    else
    {
        ebx = 1;
        ended = 1;
        vertrix_call(services->calls, 0x43acd0, opponent, 5, ebx, board, 0);
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    return ended ? vertrix_call(services->calls, 0x43bbf0, player, vtable, ebx, board, 0) : result;
}

/* The two field tests of 0x42ed40 and 0x42ed70, as field_tests does for 0x42eca0 and 0x42ecc0. */
static int gate_tests(const VertrixEffectServices *services, uint32_t ebx, uint32_t ecx,
                      uint32_t board)
{
    return vertrix_call(services->calls, 0x42ed40, board, HANDLER_FIELD, ebx, ecx, 0) != 0 &&
           vertrix_call(services->calls, 0x42ed70, board, HANDLER_FIELD, ebx, ecx, 0) != 0;
}

uint32_t vertrix_effect_gate_clear(const VertrixEffectServices *services, uint32_t player)
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
    if (gate_tests(services, player, board, board))
    {
        ended = 1;
        vertrix_call(services->calls, 0x42eba0, board, HANDLER_FIELD, player, board, 0);
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    if (!ended)
    {
        return result;
    }
    result = vertrix_call(services->calls, 0x43bbf0, player, vtable, player, board, 0);
    return vertrix_actor_storage_write(board_storage, board_size, BOARD_FLAG_FOURTH, DWORD_WIDTH, 0)
               ? result
               : 0;
}

uint32_t vertrix_effect_armed_clear(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t extra;
    uint32_t vtable;
    uint32_t first;
    uint32_t second;
    uint32_t third;
    uint32_t result;
    int armed = 0;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_ARM_FIRST, DWORD_WIDTH,
                                    &first) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    if (first == 0 &&
        vertrix_actor_storage_read(player_storage, player_size, PLAYER_ARM_SECOND, DWORD_WIDTH,
                                   &second) &&
        second == 0 &&
        vertrix_actor_storage_read(player_storage, player_size, PLAYER_ARM_THIRD, DWORD_WIDTH,
                                   &third) &&
        third == 0)
    {
        if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_EXTRA, DWORD_WIDTH,
                                        &extra))
        {
            return 0;
        }
        armed = 1;
        vertrix_call(services->calls, 0x43a510, extra, 5, 5, 5, 0);
        vertrix_call(services->calls, 0x42eba0, board, 1, 5, 5, 0);
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    if (!armed)
    {
        return result;
    }
    result = vertrix_call(services->calls, 0x43bbf0, player, 1, 5, vtable, 0);
    return vertrix_actor_storage_write(board_storage, board_size, BOARD_FLAG_FOURTH, DWORD_WIDTH, 0)
               ? result
               : 0;
}

uint32_t vertrix_effect_armed_gate(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_ebx, uint32_t entry_ecx)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t extra;
    uint32_t vtable;
    uint32_t first;
    uint32_t second;
    uint32_t third;
    uint32_t result;
    uint32_t ebx = entry_ebx;
    uint32_t ecx = entry_ecx;
    int ended = 0;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_ARM_FIRST, DWORD_WIDTH,
                                    &first) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    if (first == 0 &&
        vertrix_actor_storage_read(player_storage, player_size, PLAYER_ARM_SECOND, DWORD_WIDTH,
                                   &second) &&
        second == 0 &&
        vertrix_actor_storage_read(player_storage, player_size, PLAYER_ARM_THIRD, DWORD_WIDTH,
                                   &third) &&
        third == 0)
    {
        if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_EXTRA, DWORD_WIDTH,
                                        &extra))
        {
            return 0;
        }
        vertrix_call(services->calls, 0x43a510, extra, 5, 5, 5, 0);
        if (gate_tests(services, 5, 5, board))
        {
            vertrix_call(services->calls, 0x42eba0, board, HANDLER_FIELD, 5, 1, 0);
            ended = 1;
            ebx = 1;
            ecx = 1;
        }
        else
        {
            vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_GATE_CLEAR, 5, 5, 0);
        }
    }
    else if (gate_tests(services, ebx, ecx, board))
    {
        vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_ARMED_CLEAR, ebx, ecx, 0);
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    if (!ended)
    {
        return result;
    }
    result = vertrix_call(services->calls, 0x43bbf0, player, vtable, ebx, ecx, 0);
    return vertrix_actor_storage_write(board_storage, board_size, BOARD_FLAG_FOURTH, DWORD_WIDTH, 0)
               ? result
               : 0;
}

/* Slot kind k of the board through 0x431c10 (edx = k), as 0x4550a0 calls it. */
static uint32_t slot_kind(const VertrixEffectServices *services, uint32_t board, uint32_t k,
                          uint32_t ebx, uint32_t ecx)
{
    return vertrix_call(services->calls, 0x431c10, board, k, ebx, ecx, 0);
}

uint32_t vertrix_effect_kinds_start(const VertrixEffectServices *services, uint32_t player,
                                    uint32_t entry_ebx, uint32_t frame)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t extra;
    uint32_t opponent;
    uint32_t vtable;
    uint32_t result;
    uint32_t ebx = entry_ebx;
    uint32_t ecx = player;
    uint32_t edx;
    int ended = 0;
    const VertrixCalls *calls;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_EXTRA, DWORD_WIDTH,
                                    &extra) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    calls = services->calls;
    if (vertrix_call(calls, 0x4320c0, board, 0, ebx, ecx, 0) != 1)
    {
        uint32_t first;
        uint32_t second;
        uint32_t third;
        uint32_t pointer_first = frame - LOCAL_KIND_FIRST;
        uint32_t pointer_second = frame - LOCAL_KIND_SECOND;
        uint32_t pointer_third = frame - LOCAL_KIND_THIRD;
        vertrix_call_out3(calls, 0x43a5b0, extra, pointer_first, pointer_second, pointer_third,
                          &first, &second, &third);
        first &= 0xffu;
        second &= 0xffu;
        third &= 0xffu;
        if (first == KIND_FIVE && second == KIND_FIVE && third == KIND_FIVE)
        {
            vertrix_call(calls, 0x43acd0, opponent, pointer_first, pointer_second, 1, 0);
            ended = 1;
            ebx = pointer_second;
            ecx = 1;
        }
        else
        {
            if (!vertrix_actor_storage_write(player_storage, player_size, PLAYER_ARM_FIRST,
                                             DWORD_WIDTH, first != KIND_FIVE) ||
                !vertrix_actor_storage_write(player_storage, player_size, PLAYER_ARM_SECOND,
                                             DWORD_WIDTH, second != KIND_FIVE) ||
                !vertrix_actor_storage_write(player_storage, player_size, PLAYER_ARM_THIRD,
                                             DWORD_WIDTH, third != KIND_FIVE))
            {
                return 0;
            }
            ebx = pointer_second;
            ecx = pointer_third;
            vertrix_call(calls, 0x4ac8f0, player, HANDLER_ARMED_CLEAR, ebx, ecx, 0);
            vertrix_call(calls, 0x43ac00, opponent, HANDLER_ARMED_CLEAR, ebx, ecx, 0);
            vertrix_call(calls, 0x43c0e0, player, SOUND_KINDS, ebx, ecx, 0);
        }
    }
    else
    {
        uint32_t first;
        uint32_t second;
        uint32_t third;
        vertrix_call(calls, 0x43bad0, player, 0, ebx, ecx, 0);
        edx = 0;
        first = slot_kind(services, board, 0, ebx, ecx);
        if (first == KIND_FIVE)
        {
            edx = 1;
            first = slot_kind(services, board, 1, ebx, ecx);
            if (first == KIND_FIVE)
            {
                edx = 2;
                first = slot_kind(services, board, 2, ebx, ecx);
                if (first == KIND_FIVE)
                {
                    ebx = 1;
                    vertrix_call(calls, 0x43acd0, opponent, 2, ebx, ecx, 0);
                    ended = 1;
                    goto finish;
                }
            }
        }
        if (vertrix_call(calls, 0x431d60, board, edx, ebx, ecx, 0) != 0)
        {
            vertrix_call(calls, 0x4ac8f0, player, HANDLER_GATE_CLEAR, ebx, ecx, 0);
        }
        else
        {
            first = slot_kind(services, board, 0, ebx, ecx);
            second = slot_kind(services, board, 1, ebx, ecx);
            third = slot_kind(services, board, 2, ebx, ecx);
            if (!vertrix_actor_storage_write(player_storage, player_size, PLAYER_ARM_FIRST,
                                             DWORD_WIDTH, first != KIND_FIVE) ||
                !vertrix_actor_storage_write(player_storage, player_size, PLAYER_ARM_SECOND,
                                             DWORD_WIDTH, second != KIND_FIVE) ||
                !vertrix_actor_storage_write(player_storage, player_size, PLAYER_ARM_THIRD,
                                             DWORD_WIDTH, third != KIND_FIVE))
            {
                return 0;
            }
            vertrix_call(calls, 0x4ac8f0, player, HANDLER_ARMED_GATE, ebx, ecx, 0);
        }
        ebx = 5;
        ecx = 5;
        vertrix_call(calls, 0x4368e0, board, 5, ebx, ecx, 0);
        vertrix_call(calls, 0x43ac00, opponent, 5, ebx, ecx, 0);
        vertrix_call(calls, 0x43c0e0, player, SOUND_KINDS, ebx, ecx, 0);
    }
finish:
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    if (!ended)
    {
        return result;
    }
    result = vertrix_call(calls, 0x43bbf0, player, vtable, ebx, ecx, 0);
    return vertrix_actor_storage_write(board_storage, board_size, BOARD_FLAG_FOURTH, DWORD_WIDTH, 0)
               ? result
               : 0;
}

const VertrixFieldFinish vertrix_field_finishes[VERTRIX_FIELD_FINISH_COUNT] = {
    {0x455580, 0x4374e0, 0, 0},
    {0x455700, 0x42ebe0, 1, 0},
    {0x455970, 0x42ebe0, 1, 0},
    {0x455a90, 0x42ebe0, 1, 0x42ebc0}};

uint32_t vertrix_effect_field_finish(const VertrixEffectServices *services, uint32_t player,
                                     const VertrixFieldFinish *finish)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t result;
    int ended = 0;
    if (!services || !services->calls || !finish ||
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
        if (finish->before)
        {
            vertrix_call(services->calls, finish->before, board, HANDLER_FIELD, player, board, 0);
        }
        vertrix_call(services->calls, finish->callee, board, HANDLER_FIELD, player, board, 0);
    }
    result = release_board(services, board, board_storage, board_size);
    if (!ended)
    {
        return result;
    }
    vertrix_call(services->calls, 0x43bbf0, player, HANDLER_FINISH, player, board, 0);
    vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_FINISH, player, board, 0);
    result = vertrix_call(services->calls, 0x43bae0, player, 1, player, board, 0);
    return vertrix_actor_storage_write(player_storage, player_size, PLAYER_CHAIN, DWORD_WIDTH, 0) &&
                   (!finish->clear_slide_flag ||
                    vertrix_actor_storage_write(board_storage, board_size, BOARD_FLAG_SLIDE,
                                                DWORD_WIDTH, 0))
               ? result
               : 0;
}

uint32_t vertrix_effect_field_finish_after(const VertrixEffectServices *services, uint32_t player,
                                           uint32_t entry_edx)
{
    void *player_storage;
    size_t player_size;
    uint32_t board;
    const VertrixCalls *calls;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH, &board))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac500, board, entry_edx, player, board, 0);
    if (vertrix_call(calls, 0x4ac520, board, entry_edx, player, board, 0) == 1)
    {
        vertrix_call(calls, 0x4ac540, board, entry_edx, player, board, 0);
        vertrix_call(calls, 0x4ac5b0, board, entry_edx, player, board, 0);
        vertrix_call(calls, 0x437b70, board, entry_edx, player, board, 0);
    }
    return vertrix_effect_field_finish(services, player, &vertrix_field_finishes[1]);
}

const VertrixPairCheck vertrix_pair_checks[VERTRIX_PAIR_CHECK_COUNT] = {
    {0x455b90, 0x437f60, 0x437fe0, 0x455c30}, {0x455d10, 0x4383f0, 0x438540, 0x455db0}};

uint32_t vertrix_effect_pair_check(const VertrixEffectServices *services, uint32_t player,
                                   const VertrixPairCheck *check)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t opponent;
    uint32_t vtable;
    uint32_t result;
    uint32_t ecx = player;
    uint32_t ebx;
    int ended = 0;
    if (!services || !services->calls || !check ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_OPPONENT, DWORD_WIDTH,
                                    &opponent) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    ebx = board;
    vertrix_call(services->calls, check->first, board, 0, ebx, ecx, 0);
    if (vertrix_call(services->calls, check->second, board, 0, ebx, ecx, 0) == 1)
    {
        vertrix_call(services->calls, 0x4ac8f0, player, check->token, ebx, ecx, 0);
        vertrix_call(services->calls, 0x43c0e0, player, SOUND_KINDS, ebx, ecx, 0);
        if (!vertrix_actor_storage_write(board_storage, board_size, BOARD_FLAG_SLIDE, DWORD_WIDTH,
                                         1))
        {
            return 0;
        }
        vertrix_call(services->calls, 0x43ac00, opponent, SOUND_KINDS, ebx, ecx, 0);
    }
    else
    {
        ended = 1;
        ecx = 1;
        vertrix_call(services->calls, 0x43acd0, opponent, 0, ebx, ecx, 0);
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    return ended ? vertrix_call(services->calls, 0x43bbf0, player, vtable, 1, ecx, 0) : result;
}

uint32_t vertrix_effect_field_end_slide(const VertrixEffectServices *services, uint32_t player)
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
    if (!ended)
    {
        return result;
    }
    result = vertrix_call(services->calls, 0x43bbf0, player, vtable, player, board, 0);
    return vertrix_actor_storage_write(board_storage, board_size, BOARD_FLAG_SLIDE, DWORD_WIDTH, 0)
               ? result
               : 0;
}

uint32_t vertrix_effect_field_bind_next(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    if (vertrix_call(services->calls, 0x42eca0, board, HANDLER_FIELD, player, board, 0) != 0)
    {
        vertrix_call(services->calls, 0x4387b0, board, HANDLER_NEXT_TOKEN, player, board, 0);
        vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_NEXT_TOKEN, player, board, 0);
    }
    return release_board(services, board, board_storage, board_size);
}

uint32_t vertrix_effect_field_check_end(const VertrixEffectServices *services, uint32_t player)
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
    if (vertrix_call(services->calls, 0x42eca0, board, HANDLER_FIELD, 0, board, 0) != 0)
    {
        ended = 1;
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    if (!ended)
    {
        return result;
    }
    result = vertrix_call(services->calls, 0x43bbf0, player, vtable, 1, board, 0);
    return vertrix_actor_storage_write(board_storage, board_size, BOARD_FLAG_SLIDE, DWORD_WIDTH, 0)
               ? result
               : 0;
}

/* The counting step 0x45b4c0 and 0x45b5f0 share once 0x438d50 reported one. */
static int count_advance(const VertrixEffectServices *services, uint32_t player,
                         void *player_storage, size_t player_size, uint32_t board,
                         void *board_storage, size_t board_size, uint32_t result, uint32_t ecx,
                         uint32_t *ebx_out)
{
    uint32_t total;
    uint32_t mode;
    uint32_t entry;
    uint32_t ebx;
    const VertrixCalls *calls = services->calls;
    if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_COUNT_TOTAL, DWORD_WIDTH,
                                    &total))
    {
        return 0;
    }
    ebx = total + result;
    mode = services->global(GLOBAL_DIFFICULTY, services->global_context);
    if (!vertrix_actor_storage_write(player_storage, player_size, PLAYER_COUNT_TOTAL, DWORD_WIDTH,
                                     ebx))
    {
        return 0;
    }
    entry = services->global(TABLE_COUNT_START + 4u * mode, services->global_context);
    vertrix_call(calls, 0x4ac7b0, board, entry, ebx, ecx, 0);
    if (!vertrix_actor_storage_write(board_storage, board_size, BOARD_SLIDE_POSITION, DWORD_WIDTH,
                                     0))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ac510, board, entry, ebx, ecx, 0);
    vertrix_call(calls, 0x438dd0, board, entry, ebx, ecx, 0);
    vertrix_call(calls, 0x43c0e0, player, SOUND_KINDS, ebx, ecx, 0);
    vertrix_call(calls, 0x4ac8f0, player, HANDLER_COUNT_WAIT, ebx, ecx, 0);
    if (vertrix_call(calls, 0x439080, board, HANDLER_COUNT_WAIT, ebx, ecx, 0) == 1)
    {
        vertrix_call(calls, 0x4ac8f0, player, HANDLER_COUNT_STEP, ebx, ecx, 0);
    }
    *ebx_out = ebx;
    return 1;
}

uint32_t vertrix_effect_count_start(const VertrixEffectServices *services, uint32_t player)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t argument;
    uint32_t vtable;
    uint32_t result;
    uint32_t ebx;
    int ended = 0;
    if (!services || !services->calls || !services->global ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_COUNT_ARG, DWORD_WIDTH,
                                    &argument) ||
        !vertrix_actor_storage_write(player_storage, player_size, PLAYER_COUNT_TOTAL, DWORD_WIDTH,
                                     0) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    ebx = argument;
    result = vertrix_call(services->calls, 0x438d50, board, 0, ebx, player, 0);
    if (result == 1)
    {
        if (!count_advance(services, player, player_storage, player_size, board, board_storage,
                           board_size, result, player, &ebx))
        {
            return 0;
        }
    }
    else
    {
        ended = 1;
        vertrix_call(services->calls, 0x43acd0, player, 0, ebx, player, 0);
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    return ended ? vertrix_call(services->calls, 0x43bbf0, player, vtable, ebx, player, 0) : result;
}

uint32_t vertrix_effect_count_wait(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_edx)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    if (!services || !services->calls ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    vertrix_call(services->calls, 0x4ac500, board, entry_edx, player, board, 0);
    if (vertrix_call(services->calls, 0x4ac520, board, entry_edx, player, board, 0) == 1)
    {
        vertrix_call(services->calls, 0x4ac5b0, board, entry_edx, player, board, 0);
        if (vertrix_call(services->calls, 0x439080, board, entry_edx, player, board, 0) == 1)
        {
            vertrix_call(services->calls, 0x4ac8f0, player, HANDLER_COUNT_STEP, player, board, 0);
        }
    }
    return release_board(services, board, board_storage, board_size);
}

uint32_t vertrix_effect_count_step(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_ebx, uint32_t entry_edx)
{
    void *player_storage;
    void *board_storage;
    size_t player_size;
    size_t board_size;
    uint32_t board;
    uint32_t argument;
    uint32_t total;
    uint32_t vtable;
    uint32_t result;
    uint32_t ebx = entry_ebx;
    uint32_t edx = entry_edx;
    int ended = 0;
    const VertrixCalls *calls;
    if (!services || !services->calls || !services->global ||
        !resolve_object(services, player, &player_storage, &player_size) ||
        !vertrix_actor_storage_read(player_storage, player_size, PLAYER_BOARD, DWORD_WIDTH,
                                    &board) ||
        !resolve_object(services, board, &board_storage, &board_size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac500, board, edx, ebx, board, 0);
    if (vertrix_call(calls, 0x4ac520, board, edx, ebx, board, 0) == 1)
    {
        vertrix_call(calls, 0x4ac540, board, edx, ebx, board, 0);
        vertrix_call(calls, 0x4ac5b0, board, edx, ebx, board, 0);
    }
    if (vertrix_call(calls, 0x42ec80, board, HANDLER_FIELD, ebx, board, 0) != 0 &&
        vertrix_call(calls, 0x42eca0, board, HANDLER_FIELD, ebx, board, 0) != 0)
    {
        vertrix_call(calls, 0x439190, board, HANDLER_FIELD, ebx, board, 0);
        if (!vertrix_actor_storage_read(player_storage, player_size, PLAYER_COUNT_ARG, DWORD_WIDTH,
                                        &ebx) ||
            !vertrix_actor_storage_read(player_storage, player_size, PLAYER_COUNT_TOTAL,
                                        DWORD_WIDTH, &total))
        {
            return 0;
        }
        argument = ebx;
        result = vertrix_call(calls, 0x438d50, board, total, ebx, board, 0);
        if (result == 1)
        {
            if (!count_advance(services, player, player_storage, player_size, board, board_storage,
                               board_size, result, board, &ebx))
            {
                return 0;
            }
        }
        else
        {
            ended = 1;
            ebx = argument;
        }
    }
    if (!vertrix_actor_storage_read(board_storage, board_size, BOARD_VTABLE, DWORD_WIDTH, &vtable))
    {
        return 0;
    }
    result = services->virtual_call ? (uint32_t)services->virtual_call(services->virtual_context,
                                                                       board, SLOT_RELEASE, 0)
                                    : 0;
    return ended ? vertrix_call(calls, 0x43bbf0, player, vtable, ebx, board, 0) : result;
}

uint32_t vertrix_effect_object_start(const VertrixEffectServices *services, uint32_t object,
                                     uint32_t entry_ebx)
{
    void *storage;
    size_t size;
    uint32_t value;
    uint32_t result;
    uint32_t n;
    uint32_t edx = 1;
    uint32_t first;
    uint32_t second;
    uint32_t third;
    const VertrixCalls *calls;
    if (!services || !services->calls || !services->global_write ||
        !resolve_object(services, object, &storage, &size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac7b0, object, 1, entry_ebx, object, 0);
    vertrix_call(calls, 0x4ac500, object, 1, entry_ebx, object, 0);
    result = vertrix_call(calls, 0x4ac520, object, 1, entry_ebx, object, 0);
    if (result != 1)
    {
        return result;
    }
    n = vertrix_call(calls, 0x4ac540, object, 1, entry_ebx, object, 0);
    vertrix_call(calls, 0x4ac5b0, object, 1, n, object, 0);
    first = vertrix_call(calls, 0x4aca60, object, n, n, object, 0);
    second = vertrix_call(calls, 0x4acab0, object, n, n, object, 0);
    third = vertrix_call(calls, 0x4acb00, object, n, n, object, 0);
    edx = n;
    if (first == 0 && second == 0 && third == 0)
    {
        vertrix_call(calls, 0x4ac8f0, object, HANDLER_OBJECT_POLL, n, object, 0);
        edx = 2;
        vertrix_call(calls, 0x4ac7b0, object, edx, n, object, 0);
    }
    result = vertrix_call(calls, 0x4b5500, object, edx, n, object, 0);
    if (result == 0)
    {
        return 0;
    }
    if (!vertrix_actor_storage_read(storage, size, OBJECT_VALUE, DWORD_WIDTH, &value))
    {
        return 0;
    }
    services->global_write(GLOBAL_OBJECT_VALUE, value, services->global_context);
    return value;
}

uint32_t vertrix_effect_object_poll(const VertrixEffectServices *services, uint32_t object,
                                    uint32_t entry_ebx)
{
    void *storage;
    size_t size;
    uint32_t value;
    uint32_t result;
    uint32_t edx = object;
    const VertrixCalls *calls;
    if (!services || !services->calls || !services->global_write ||
        !resolve_object(services, object, &storage, &size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac500, object, edx, entry_ebx, object, 0);
    if (vertrix_call(calls, 0x4ac520, object, edx, entry_ebx, object, 0) == 1)
    {
        vertrix_call(calls, 0x4ac510, object, edx, entry_ebx, object, 0);
    }
    edx = POINT_KIND;
    if (vertrix_call(calls, 0x476480, POINT_LIST, edx, entry_ebx, object, 0) == 0)
    {
        if (!vertrix_actor_storage_read(storage, size, OBJECT_VALUE, DWORD_WIDTH, &value))
        {
            return 0;
        }
        services->global_write(GLOBAL_OBJECT_VALUE, value, services->global_context);
        edx = HANDLER_OBJECT_POLL;
        vertrix_call(calls, 0x4ac8f0, object, edx, entry_ebx, object, 0);
    }
    result = vertrix_call(calls, 0x4b5500, object, edx, entry_ebx, object, 0);
    if (result == 0)
    {
        return 0;
    }
    if (!vertrix_actor_storage_read(storage, size, OBJECT_VALUE, DWORD_WIDTH, &value))
    {
        return 0;
    }
    services->global_write(GLOBAL_OBJECT_VALUE, value, services->global_context);
    return value;
}

const VertrixObjectBegin vertrix_object_begins[VERTRIX_OBJECT_BEGIN_COUNT] = {
    {0x456300, 0x456390}, {0x4564e0, 0x456570}, {0x4566d0, 0x456760}};

uint32_t vertrix_effect_object_begin(const VertrixEffectServices *services, uint32_t object,
                                     uint32_t entry_ebx, const VertrixObjectBegin *begin)
{
    uint32_t result;
    uint32_t n;
    uint32_t first;
    uint32_t second;
    uint32_t third;
    const VertrixCalls *calls;
    if (!services || !services->calls || !begin)
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac7b0, object, 1, entry_ebx, object, 0);
    vertrix_call(calls, 0x4ac500, object, 1, entry_ebx, object, 0);
    result = vertrix_call(calls, 0x4ac520, object, 1, entry_ebx, object, 0);
    if (result != 1)
    {
        return result;
    }
    n = vertrix_call(calls, 0x4ac540, object, 1, entry_ebx, object, 0);
    vertrix_call(calls, 0x4ac5b0, object, 1, n, object, 0);
    first = vertrix_call(calls, 0x4aca60, object, n, n, object, 0);
    second = vertrix_call(calls, 0x4acab0, object, n, n, object, 0);
    third = vertrix_call(calls, 0x4acb00, object, n, n, object, 0);
    if (first != 0 || second != 0 || third != 0)
    {
        return third;
    }
    vertrix_call(calls, 0x4ac8f0, object, begin->token, n, object, 0);
    return vertrix_call(calls, 0x4ac7b0, object, 2, n, object, 0);
}

const VertrixCursor vertrix_cursors[VERTRIX_CURSOR_COUNT] = {{0x456170, 0x456290, 1, 0},
                                                             {0x456390, 0x456490, 0, 1},
                                                             {0x456570, 0x456670, 0, 1},
                                                             {0x456760, 0x456860, 0, 1}};

uint32_t vertrix_effect_cursor(const VertrixEffectServices *services, uint32_t object,
                               uint32_t entry_ebx, uint32_t entry_edx, uint32_t frame,
                               const VertrixCursor *cursor)
{
    void *storage;
    size_t size;
    uint32_t edx = entry_edx;
    uint32_t ebx = entry_ebx;
    uint32_t ecx = object;
    uint32_t flag;
    uint32_t x;
    uint32_t y;
    uint32_t value;
    uint32_t out_first;
    uint32_t out_second;
    uint32_t out_third;
    uint32_t result;
    uint32_t last;
    const VertrixCalls *calls;
    if (!services || !services->calls || !services->global || !services->global_write || !cursor ||
        !resolve_object(services, object, &storage, &size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac500, object, edx, ebx, ecx, 0);
    if (vertrix_call(calls, 0x4ac520, object, edx, ebx, ecx, 0) == 1)
    {
        edx = vertrix_call(calls, 0x4ac540, object, edx, ebx, ecx, 0);
        vertrix_call(calls, 0x4ac5b0, object, edx, ebx, ecx, 0);
        if (!vertrix_actor_storage_write(storage, size, OBJECT_WORD_A, 2, 0) ||
            !vertrix_actor_storage_write(storage, size, OBJECT_WORD_B, 2, 5))
        {
            return 0;
        }
        vertrix_call(calls, 0x4ad530, object, edx, ebx, ecx, 0);
    }
    flag = services->global(GLOBAL_POINTER_OFF, services->global_context);
    x = flag ? POINTER_OFF_VALUE
             : (uint32_t)(int32_t)(int16_t)services->global(GLOBAL_POINTER_X,
                                                            services->global_context);
    y = flag ? POINTER_OFF_VALUE
             : (uint32_t)(int32_t)(int16_t)services->global(GLOBAL_POINTER_Y,
                                                            services->global_context);
    ebx = y;
    edx = x;
    ecx = services->global(GLOBAL_POINTER_OFF, services->global_context);
    if ((vertrix_call(calls, 0x4b0b70, object, edx, ebx, ecx, 0) & 0xffu) != 0 &&
        !vertrix_actor_storage_write(storage, size, OBJECT_STATE, 2, 0x23))
    {
        return 0;
    }
    edx = POINT_KIND;
    last = vertrix_call(calls, 0x476480, POINT_LIST, edx, ebx, ecx, 0);
    if (last == 1)
    {
        ebx = frame - LOCAL_FIRST;
        ecx = frame - (cursor->swapped ? LOCAL_THIRD : LOCAL_SECOND);
        vertrix_call_out_stack(calls, 0x4764a0, POINT_LIST, edx, ebx, ecx,
                               frame - (cursor->swapped ? LOCAL_SECOND : LOCAL_THIRD), &out_first,
                               &out_second, &out_third);
        ebx = (uint32_t)(int32_t)(int16_t)(out_second & 0xffffu);
        edx = (uint32_t)(int32_t)(int16_t)(out_first & 0xffffu);
        last = vertrix_call(calls, 0x4b0b70, object, edx, ebx, ecx, 0);
        if ((last & 0xffu) != 0)
        {
            edx = cursor->token;
            last = vertrix_call(calls, 0x4ac8f0, object, edx, ebx, ecx, 0);
            if (!vertrix_actor_storage_write(storage, size, OBJECT_STATE, 2, 0x3c))
            {
                return 0;
            }
        }
    }
    if (!cursor->poll)
    {
        return last;
    }
    result = vertrix_call(calls, 0x4b5500, object, edx, ebx, ecx, 0);
    if (result == 0)
    {
        return 0;
    }
    if (!vertrix_actor_storage_read(storage, size, OBJECT_VALUE, DWORD_WIDTH, &value))
    {
        return 0;
    }
    services->global_write(GLOBAL_OBJECT_VALUE, value, services->global_context);
    return value;
}

const VertrixObjectWait vertrix_object_waits[VERTRIX_OBJECT_WAIT_COUNT] = {
    {0x456490, 0, 0, 0x478bd0, 0x456390},
    {0x456670, 0x5589dc, 0x532b98, 0x478b40, 0x456570},
    {0x456860, 0x598da8, 0x532b9c, 0x4828f0, 0x456760}};

uint32_t vertrix_effect_object_wait(const VertrixEffectServices *services, uint32_t object,
                                    uint32_t entry_ebx, const VertrixObjectWait *wait)
{
    uint32_t edx = object;
    uint32_t result;
    const VertrixCalls *calls;
    if (!services || !services->calls || !services->global || !services->global_write || !wait)
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac500, object, edx, entry_ebx, object, 0);
    if (vertrix_call(calls, 0x4ac520, object, edx, entry_ebx, object, 0) == 1)
    {
        vertrix_call(calls, 0x4ac510, object, edx, entry_ebx, object, 0);
    }
    result = vertrix_call(calls, 0x476480, POINT_LIST, POINT_KIND, entry_ebx, object, 0);
    if (result != 0)
    {
        return result;
    }
    if (wait->flip_global)
    {
        uint32_t current = services->global(wait->flip_global, services->global_context);
        uint32_t selection;
        services->global_write(wait->flip_global, 1u - current, services->global_context);
        selection = services->global(wait->selection_global, services->global_context);
        vertrix_call(calls, wait->callee, selection, wait->token, entry_ebx, object, 0);
    }
    else
    {
        vertrix_call(calls, wait->callee, result, POINT_KIND, entry_ebx, object, 0);
    }
    return vertrix_call(calls, 0x4ac8f0, object, wait->token, entry_ebx, object, 0);
}

uint32_t vertrix_effect_actor_prepare(const VertrixEffectServices *services, uint32_t object,
                                      uint32_t entry_ebx)
{
    void *storage;
    size_t size;
    uint32_t a;
    uint32_t b;
    if (!services || !services->calls || !resolve_object(services, object, &storage, &size) ||
        !vertrix_actor_storage_read(storage, size, OBJECT_SRC_A, 2, &a) ||
        !vertrix_actor_storage_write(storage, size, OBJECT_SETTLE_WORD, 2, a) ||
        !vertrix_actor_storage_read(storage, size, OBJECT_SRC_B, 2, &b) ||
        !vertrix_actor_storage_write(storage, size, OBJECT_SETTLE_WORD_B, 2, b))
    {
        return 0;
    }
    vertrix_call(services->calls, 0x4ac8f0, object, 0x456900, entry_ebx, object, 0);
    vertrix_call(services->calls, 0x4ac7b0, object, 1, entry_ebx, object, 0);
    return vertrix_call(services->calls, 0x4ac510, object, 1, entry_ebx, object, 0);
}

uint32_t vertrix_effect_actor_settle(const VertrixEffectServices *services, uint32_t object,
                                     uint32_t entry_ebx, uint32_t entry_edx)
{
    void *storage;
    size_t size;
    uint32_t result;
    uint32_t n;
    uint32_t first;
    uint32_t second;
    uint32_t third;
    const VertrixCalls *calls;
    if (!services || !services->calls || !resolve_object(services, object, &storage, &size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac500, object, entry_edx, entry_ebx, object, 0);
    result = vertrix_call(calls, 0x4ac520, object, entry_edx, entry_ebx, object, 0);
    if (result != 1)
    {
        return result;
    }
    n = vertrix_call(calls, 0x4ac540, object, entry_edx, entry_ebx, object, 0);
    vertrix_call(calls, 0x4ac5b0, object, entry_edx, n, object, 0);
    if (!vertrix_actor_storage_write(storage, size, OBJECT_WORD_A, 2, 0) ||
        !vertrix_actor_storage_write(storage, size, OBJECT_WORD_B, 2, 5))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ad530, object, n, n, object, 0);
    first = vertrix_call(calls, 0x4aca60, object, n, n, object, 0);
    second = vertrix_call(calls, 0x4acab0, object, n, n, object, 0);
    third = vertrix_call(calls, 0x4acb00, object, n, n, object, 0);
    if (first != 0 || second != 0 || third != 0)
    {
        return third;
    }
    return vertrix_call(calls, 0x4ac8f0, object, 0, n, object, 0);
}

const VertrixActorPair vertrix_actor_pairs[VERTRIX_ACTOR_PAIR_COUNT] = {
    {0x456980, 0x64, 0x456bf0, 0, 0}, {0x456a00, 0, 0x456ca0, 1, 1}};

uint32_t vertrix_effect_actor_pair(const VertrixEffectServices *services, uint32_t object,
                                   uint32_t entry_edx, const VertrixActorPair *pair)
{
    void *storage;
    size_t size;
    uint32_t edx = entry_edx;
    uint32_t n;
    const VertrixCalls *calls;
    if (!services || !services->calls || !pair ||
        !resolve_object(services, object, &storage, &size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4adfe0, object, edx, object, object, 0);
    if (!vertrix_actor_storage_write(storage, size, OBJECT_FLAG93, 1, 1))
    {
        return 0;
    }
    vertrix_call(calls, 0x4ac500, object, edx, object, object, 0);
    if (vertrix_call(calls, 0x4ac520, object, edx, object, object, 0) == 1)
    {
        n = vertrix_call(calls, 0x4ac540, object, edx, object, object, 0);
        edx = n;
        vertrix_call(calls, 0x4ac5b0, object, edx, object, object, 0);
        if (!vertrix_actor_storage_write(storage, size, OBJECT_BYTE4F, 1, pair->byte_value) ||
            !vertrix_actor_storage_write(storage, size, OBJECT_WORD50, 2, 5))
        {
            return 0;
        }
        if (vertrix_call(calls, 0x4ad580, object, edx, object, object, 0) == 0)
        {
            edx = pair->token;
            if (!pair->flag_after &&
                !vertrix_actor_storage_write(storage, size, OBJECT_FLAG93, 1, pair->flag_value))
            {
                return 0;
            }
            vertrix_call(calls, 0x4ac8f0, object, edx, object, object, 0);
            if (pair->flag_after &&
                !vertrix_actor_storage_write(storage, size, OBJECT_FLAG93, 1, pair->flag_value))
            {
                return 0;
            }
        }
    }
    return vertrix_call(calls, 0x4ac8a0, object, edx, object, object, 0);
}

const VertrixActorRise vertrix_actor_rises[VERTRIX_ACTOR_RISE_COUNT] = {
    {0x456a80, 0xff38, 6, 0, 0x456b00}, {0x456b00, 0xc8, 0xc, 0x10, 0x456b80}};

uint32_t vertrix_effect_actor_rise(const VertrixEffectServices *services, uint32_t object,
                                   uint32_t entry_ebx, uint32_t entry_edx,
                                   const VertrixActorRise *rise)
{
    void *storage;
    size_t size;
    uint32_t n;
    uint32_t edx = entry_edx;
    uint32_t ebx = entry_ebx;
    const VertrixCalls *calls;
    if (!services || !services->calls || !rise ||
        !resolve_object(services, object, &storage, &size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4adfe0, object, edx, ebx, object, 0);
    vertrix_call(calls, 0x4ac500, object, edx, ebx, object, 0);
    if (vertrix_call(calls, 0x4ac520, object, edx, ebx, object, 0) == 1)
    {
        n = vertrix_call(calls, 0x4ac540, object, edx, ebx, object, 0);
        ebx = n;
        vertrix_call(calls, 0x4ac5b0, object, edx, ebx, object, 0);
        edx = n;
        if (!vertrix_actor_storage_write(storage, size, OBJECT_WORD_A, 2, rise->word_a) ||
            !vertrix_actor_storage_write(storage, size, OBJECT_WORD_B, 2, rise->word_b))
        {
            return 0;
        }
        vertrix_call(calls, 0x4ad530, object, edx, ebx, object, 0);
        if (!vertrix_actor_storage_write(storage, size, OBJECT_BYTE45, 1, rise->byte) ||
            !vertrix_actor_storage_write(storage, size, OBJECT_WORD46, 2, 1))
        {
            return 0;
        }
        if (vertrix_call(calls, 0x4acc10, object, edx, ebx, object, 0) == 0)
        {
            edx = rise->token;
            vertrix_call(calls, 0x4ac8f0, object, edx, ebx, object, 0);
        }
    }
    return vertrix_call(calls, 0x4ac8a0, object, edx, ebx, object, 0);
}

uint32_t vertrix_effect_actor_drop(const VertrixEffectServices *services, uint32_t object,
                                   uint32_t entry_edx)
{
    void *storage;
    size_t size;
    uint32_t edx = entry_edx;
    uint32_t n;
    const VertrixCalls *calls;
    if (!services || !services->calls || !resolve_object(services, object, &storage, &size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4adfe0, object, edx, object, object, 0);
    vertrix_call(calls, 0x4ac500, object, edx, object, object, 0);
    if (vertrix_call(calls, 0x4ac520, object, edx, object, object, 0) == 1)
    {
        n = vertrix_call(calls, 0x4ac540, object, edx, object, object, 0);
        edx = n;
        vertrix_call(calls, 0x4ac5b0, object, edx, object, object, 0);
        if (!vertrix_actor_storage_write(storage, size, OBJECT_WORD_A, 2, 0) ||
            !vertrix_actor_storage_write(storage, size, OBJECT_WORD_B, 2, 6))
        {
            return 0;
        }
        if (vertrix_call(calls, 0x4ad530, object, edx, object, object, 0) == 0)
        {
            edx = 0x456bf0;
            if (!vertrix_actor_storage_write(storage, size, OBJECT_FLAG15D, 1, 0))
            {
                return 0;
            }
            vertrix_call(calls, 0x4ac8f0, object, edx, object, object, 0);
        }
    }
    return vertrix_call(calls, 0x4ac8a0, object, edx, object, object, 0);
}

uint32_t vertrix_effect_actor_toggle(const VertrixEffectServices *services, uint32_t object,
                                     uint32_t entry_ebx, uint32_t entry_ecx)
{
    void *storage;
    size_t size;
    uint32_t a;
    uint32_t b;
    if (!services || !services->calls || !resolve_object(services, object, &storage, &size) ||
        !vertrix_actor_storage_read(storage, size, OBJECT_FLAG15C, 1, &a) ||
        !vertrix_actor_storage_read(storage, size, OBJECT_FLAG15D, 1, &b))
    {
        return 0;
    }
    if ((a & 0xffu) == 0)
    {
        return vertrix_call(services->calls, 0x4ac8f0, object, 0x456980, entry_ebx, entry_ecx, 0);
    }
    if ((b & 0xffu) == 1 && !vertrix_actor_storage_write(storage, size, OBJECT_FLAG15D, 1, 0))
    {
        return 0;
    }
    return object;
}

uint32_t vertrix_effect_actor_scale(const VertrixEffectServices *services, uint32_t object,
                                    uint32_t entry_edx)
{
    void *storage;
    size_t size;
    uint32_t result;
    uint32_t n;
    uint32_t value;
    uint32_t scaled;
    uint32_t edx = entry_edx;
    uint32_t product;
    int32_t shifted;
    int32_t quotient;
    uint32_t g1;
    uint32_t g2;
    const VertrixCalls *calls;
    if (!services || !services->calls || !services->global ||
        !resolve_object(services, object, &storage, &size))
    {
        return 0;
    }
    calls = services->calls;
    vertrix_call(calls, 0x4ac500, object, edx, object, object, 0);
    result = vertrix_call(calls, 0x4ac520, object, edx, object, object, 0);
    if (result != 1)
    {
        return result;
    }
    n = vertrix_call(calls, 0x4ac540, object, edx, object, object, 0);
    edx = n;
    vertrix_call(calls, 0x4ac5b0, object, edx, object, object, 0);
    if (!vertrix_actor_storage_write(storage, size, OBJECT_WORD_A, 2, 0xff38) ||
        !vertrix_actor_storage_write(storage, size, OBJECT_WORD_B, 2, 1))
    {
        return 0;
    }
    if (vertrix_call(calls, 0x4ad530, object, edx, object, object, 0) == 0)
    {
        vertrix_call(calls, 0x4ac8f0, object, 0, object, object, 0);
    }
    if (!vertrix_actor_storage_read(storage, size, OBJECT_WORD46, DWORD_WIDTH, &value))
    {
        return 0;
    }
    shifted = (int32_t)value >> 16;
    scaled = (uint32_t)shifted * 100u;
    quotient = (int32_t)scaled / -200;
    scaled = 100u - (uint32_t)quotient;
    g1 = services->global(GLOBAL_SELECTION, services->global_context);
    product = g1 * scaled;
    vertrix_call(calls, 0x478b40, product / 100u, product % 100u, 100, scaled, 0);
    g2 = services->global(GLOBAL_SELECTION + 4, services->global_context);
    product = g2 * scaled;
    return vertrix_call(calls, 0x4828f0, product / 100u, product % 100u, 100, scaled, 0);
}
