#include "board_conversions.h"
#include "actor_fields.h"
#include "actor_storage.h"
#include "board_actions.h"
#include "board_markers.h"

enum
{
    COLUMNS = 5,
    ROWS = 13,
    CELL_COUNT = COLUMNS * ROWS,
    COLUMN_STRIDE = 0x34,
    GRID_BLOCKS = 0x220,
    GRID_COMPANIONS = 0x87c,
    MARKERS = 0xb94,
    MARKER_PENDING = 1,
    MARKER_STARTED = 2,
    STEPS = 5,
    POWER = 0x4e,
    POWER_RETIRED = 0x64,
    BYTE_44 = 0x44,
    BYTE_93 = 0x93,
    DWORD_58 = 0x58,
    OBJECT_D0 = 0xd0,
    OBJECT_FRAME = 0xb8,
    KIND_BYTE = 0x15c,
    REPLACE_OLD_HANDLER = 0x44d480,
    REPLACE_OLD_BYTE_44 = 0x10,
    REPLACE_NEW_HANDLER = 0x44d5f0,
    SCALED_OLD_HANDLER = 0x44e6e0,
    SCALED_NEW_HANDLER = 0x44c860,
    SCALED_KIND = 6,
    SCALED_RANDOM_MODE = -2,
    SCALED_RANDOM_LIMIT = 5,
    SCALED_DIVISOR = 12,
    MIRROR_BLOCK_HANDLER = 0x44d8b0,
    MIRROR_NEW_HANDLER = 0x44da70,
    SCATTER_HANDLER = 0x44e120,
    SCATTER_ORIGIN_X = 0x3c,
    SCATTER_ORIGIN_Y = 0x9c,
    SCATTER_CENTRE = 12,
    SCATTER_DRAW = 8,
    SCATTER_DRAW_BASE = 3,
    SCATTER_STEPS = 2,
    SCATTER_FULL_TURN = 360,
    SCATTER_DELAY = 300,
    BOARD_ORIGIN_X = 0xc,
    BOARD_ORIGIN_Y = 0x14,
    OBJECT_ORIGIN_X = 0xc,
    OBJECT_ORIGIN_Y = 0x14,
    OBJECT_HEADING = 0x24,
    OBJECT_SPEED = 0x28,
    DWORD_5C = 0x5c,
    DWORD_60 = 0x60,
    DWORD_64 = 0x64,
    DWORD_68 = 0x68,
    DWORD_6C = 0x6c,
    PRIME_DRAW = 0x30,
    PRIME_VALUE = 0x30,
    SPLIT_HANDLER = 0x44e250,
    SPLIT_STEPS = 2,
    SPLIT_POWER_B = 0x4f,
    SPLIT_POWER_B_VALUE = 0x32,
    SPLIT_WORD_50 = 0x50,
    SPLIT_WORD_50_VALUE = 0x14,
    SPLIT_TARGET = 0x10,
    SPLIT_TARGET_ROW = 0x12,
    SPLIT_LEFT_OFFSET = 24,
    SPLIT_RIGHT_OFFSET = 125,
    SPLIT_ROW_DRAW = 3,
    SPLIT_DISTANCE_WORD = 0x4a,
    SPLIT_DISTANCE_PERCENT = 100,
    SPLIT_DISTANCE_DIVISOR = 60,
    SPLIT_WORD_4C = 0x4c,
    SPLIT_WORD_4C_VALUE = 10,
    ACTIVE_PIECE = 0xa60,
    PIECE_CHILDREN = 0x15c,
    PIECE_SAVED_CHILDREN = 0x170,
    PIECE_CHILD_COUNT = 3,
    CHILD_OLD_HANDLER = 0x44f7e0,
    CHILD_NEW_HANDLER = 0x44f880,
    CHILD_OLD_STEPS = 1,
    COUNTED_OLD_HANDLER = 0x44e380,
    COUNTED_NEW_HANDLER = 0x44e4a0,
    COUNTED_DRAW = 5,
    MARKER_TAKEN = 2,
    MOTION_STEPS = 4,
    MOTION_WORD_48 = 0x48,
    MOTION_WORD_4A = 0x4a,
    MOTION_WORD_4C = 0x4c,
    MOTION_RISE = 100,
    MOTION_FALL = 0xff9c,
    MOTION_PHASE = 10,
    MOTION_MODE1_PHASE = 8,
    MOTION_MODE1_HANDLER = 0x44f240,
    MOTION_DWORD_80 = 0x80,
    MOTION_DWORD_84 = 0x84,
    MOTION_DWORD_88 = 0x88,
    MOTION_BYTE_8C = 0x8c,
    MOTION_BYTE_94 = 0x94,
    MOTION_BYTE_52 = 0x52,
    MOTION_DRAW_88 = 5,
    MOTION_DRAW_88_BASE = 2,
    MOTION_DRAW_HANDLER = 2,
    MOTION_MODE2_FIRST = 0x44f390,
    MOTION_MODE2_SECOND = 0x44f3e0,
    SWIRL_HANDLER = 0x44de20,
    SWIRL_ANGLE_STEP = 72,
    SWIRL_WORD_28 = 8,
    SWIRL_WORD_28_OFFSET = 0x28,
    SWIRL_DELAY = 0x12c,
    SWIRL_WORD_18 = 0x18,
    SWIRL_WORD_12 = 0x12,
    SWIRL_WORD_1A = 0x1a,
    SWIRL_WORD_VALUE = 5,
    SWIRL_BYTE_4F = 0x4f,
    SWIRL_WORD_50 = 0x50,
    SWIRL_ORIGIN_X = 60,
    SWIRL_ORIGIN_Y = 12,
    SPIN_OLD_HANDLER = 0x44cfd0,
    SPIN_NEW_HANDLER = 0x44ccd0,
    SPIN_DRAW = 8,
    SPIN_BIAS = 4,
    SPIN_WRAP = 7,
    SPIN_STEPS_DRAW = 4,
    SPIN_KIND_DRAW = 5,
    SPIN_STONE_KIND = 5,
    SPIN_NEW_POWER = 0x32,
    SPIN_BYTE_44 = 0x44,
    SPIN_BYTE_45 = 0x45,
    SPIN_WORD_46 = 0x46,
    SPIN_OLD_BYTE_44 = 0x10,
    SPIN_NEW_BYTE_45 = 0x10,
    SPIN_START_X = 8,
    SPIN_START_Y = 0xa,
    SPIN_WORD_24 = 0x24,
    SPIN_PERIOD = 0xc0,
    SPIN_DWORD_5C = 4,
    SPIN_DWORD_68 = 2,
    KINDS_SNAPSHOT = 0x1de,
    KIND_LIMIT = 5,
    PICK_LIMIT = 3,
    PICK_OUTPUTS = 5,
    MARKER_KIND_FIRST = 2,
    MARKER_KIND_SECOND = 1,
    COLLAPSE_BOTTOM_ROW = 12,
    COLLAPSE_START_X = 8,
    COLLAPSE_START_Y = 0xa,
    COLLAPSE_TARGET_X = 0x10,
    COLLAPSE_TARGET_Y = 0x18,
    COLLAPSE_BYTE_95 = 0x95,
    COLLAPSE_POWER = 0x32,
    RANDOM_OLD_HANDLER = 0x44e510,
    RANDOM_NEW_HANDLER = 0x44e590,
    OBJECT_X = 0xe,
    OBJECT_Y = 0x16
};

typedef struct
{
    uint32_t handle;
    void *storage;
    size_t size;
} Object;

static int open_object(const VertrixFactoryServices *services, uint32_t handle, Object *object)
{
    object->handle = handle;
    return services->resolve(handle, &object->storage, &object->size, services->context);
}

static int object_write(const Object *object, size_t offset, unsigned width, uint32_t value)
{
    return vertrix_actor_storage_write(object->storage, object->size, offset, width, value);
}

static int object_read(const Object *object, size_t offset, unsigned width, uint32_t *value)
{
    return vertrix_actor_storage_read(object->storage, object->size, offset, width, value);
}

static size_t cell_offset(size_t grid, uint32_t column, uint32_t row)
{
    return grid + COLUMN_STRIDE * (size_t)column + 4 * (size_t)row;
}

/* Retire the block of a cell: move it to the companion grid, clearing the block grid. */
static int retire_block(void *board, size_t board_size, uint32_t column, uint32_t row,
                        uint32_t *block)
{
    size_t blocks_at = cell_offset(GRID_BLOCKS, column, row);
    size_t companions_at = cell_offset(GRID_COMPANIONS, column, row);
    return vertrix_actor_storage_read(board, board_size, blocks_at, 4, block) &&
           vertrix_actor_storage_write(board, board_size, companions_at, 4, *block) &&
           vertrix_actor_storage_write(board, board_size, blocks_at, 4, 0);
}

/* The calls that give a replacement block its timing from the block it replaces. */
static int inherit_timing(const Object *replacement, const Object *old)
{
    uint32_t d0, frame;
    return object_read(old, OBJECT_D0, 4, &d0) &&
           vertrix_actor_set_d0(replacement->storage, replacement->size, d0) &&
           vertrix_actor_set_period_steps(replacement->storage, replacement->size, STEPS) &&
           object_read(old, OBJECT_FRAME, 4, &frame) &&
           vertrix_actor_set_frame_index(replacement->storage, replacement->size, frame);
}

static int inherit_period_and_frame(const Object *replacement, const Object *old)
{
    uint32_t frame;
    return vertrix_actor_set_period_steps(replacement->storage, replacement->size, STEPS) &&
           object_read(old, OBJECT_FRAME, 4, &frame) &&
           vertrix_actor_set_frame_index(replacement->storage, replacement->size, frame);
}

int vertrix_board_replace_marked(void *board, size_t board_size, uint32_t index,
                                 const VertrixFactoryServices *services)
{
    uint8_t *markers = (uint8_t *)board + MARKERS;
    if (!board || board_size < MARKERS + CELL_COUNT)
    {
        return 0;
    }
    uint32_t pending = vertrix_board_marker_count(markers, MARKER_PENDING);
    for (uint32_t done = 0; done < pending; ++done)
    {
        uint32_t column, row, old_handle, new_handle;
        Object old, replacement;
        if (!vertrix_board_marker_nth_by_row(markers, MARKER_PENDING, 0, &column, &row))
        {
            return 0;
        }
        markers[column * ROWS + row] = MARKER_STARTED;
        if (!retire_block(board, board_size, column, row, &old_handle) ||
            !open_object(services, old_handle, &old) ||
            !vertrix_actor_set_handler(old.storage, old.size, REPLACE_OLD_HANDLER) ||
            !object_write(&old, POWER, 1, POWER_RETIRED) ||
            !vertrix_actor_set_period_steps(old.storage, old.size, STEPS) ||
            !object_write(&old, BYTE_44, 1, REPLACE_OLD_BYTE_44) ||
            !vertrix_block_spawn(board, board_size, index, services, &new_handle) ||
            !vertrix_actor_storage_write(board, board_size, cell_offset(GRID_BLOCKS, column, row),
                                         4, new_handle) ||
            !open_object(services, new_handle, &replacement) ||
            !inherit_timing(&replacement, &old) ||
            !vertrix_actor_clear_counter(replacement.storage, replacement.size) ||
            !vertrix_actor_clear_cc(replacement.storage, replacement.size) ||
            !vertrix_actor_clear_counter(old.storage, old.size) ||
            !vertrix_actor_clear_cc(old.storage, old.size) ||
            !vertrix_actor_set_handler(replacement.storage, replacement.size,
                                       REPLACE_NEW_HANDLER) ||
            !object_write(&replacement, BYTE_44, 1, 0))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_board_replace_marked_scaled(void *board, size_t board_size, int32_t mode,
                                        const VertrixFactoryServices *services)
{
    const uint8_t *markers = (const uint8_t *)board + MARKERS;
    if (!board || board_size < MARKERS + CELL_COUNT ||
        (mode != SCALED_KIND && mode != SCALED_RANDOM_MODE))
    {
        return 0;
    }
    uint32_t pending = vertrix_board_marker_count(markers, MARKER_PENDING);
    for (uint32_t n = 0; n < pending; ++n)
    {
        uint32_t column, row, old_handle, new_handle, d0;
        uint32_t kind = SCALED_KIND;
        Object old, replacement;
        if (!vertrix_board_marker_nth_by_row(markers, MARKER_PENDING, n, &column, &row) ||
            !retire_block(board, board_size, column, row, &old_handle) ||
            !open_object(services, old_handle, &old) ||
            !vertrix_actor_set_handler(old.storage, old.size, SCALED_OLD_HANDLER) ||
            !object_write(&old, POWER, 1, POWER_RETIRED) ||
            !vertrix_actor_set_period_steps(old.storage, old.size, STEPS))
        {
            return 0;
        }
        if (mode == SCALED_RANDOM_MODE)
        {
            kind = services->draw(SCALED_RANDOM_LIMIT, services->context);
        }
        if (!vertrix_block_spawn(board, board_size, kind, services, &new_handle) ||
            !vertrix_actor_storage_write(board, board_size, cell_offset(GRID_BLOCKS, column, row),
                                         4, new_handle) ||
            !open_object(services, new_handle, &replacement) ||
            !object_read(&old, OBJECT_D0, 4, &d0) ||
            !object_write(&replacement, DWORD_58, 4, d0 / SCALED_DIVISOR) ||
            !vertrix_actor_set_d0_steps(replacement.storage, replacement.size, 1) ||
            !inherit_period_and_frame(&replacement, &old) ||
            !object_write(&replacement, POWER, 1, 0) ||
            !object_write(&replacement, BYTE_93, 1, 1) ||
            !object_write(&replacement, BYTE_44, 1, 0) ||
            !vertrix_actor_clear_counter(replacement.storage, replacement.size) ||
            !vertrix_actor_clear_cc(replacement.storage, replacement.size) ||
            !vertrix_actor_clear_counter(old.storage, old.size) ||
            !vertrix_actor_clear_cc(old.storage, old.size) ||
            !vertrix_actor_set_handler(replacement.storage, replacement.size, SCALED_NEW_HANDLER))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_board_mirror_marked(void *board, size_t board_size,
                                const VertrixFactoryServices *services)
{
    const uint8_t *markers = (const uint8_t *)board + MARKERS;
    if (!board || board_size < MARKERS + CELL_COUNT)
    {
        return 0;
    }
    uint32_t pending = vertrix_board_marker_count(markers, MARKER_PENDING);
    for (uint32_t n = 0; n < pending; ++n)
    {
        uint32_t column, row, block_handle, kind, new_handle;
        Object block, mirror;
        if (!vertrix_board_marker_nth_by_row(markers, MARKER_PENDING, n, &column, &row) ||
            !vertrix_actor_storage_read(board, board_size, cell_offset(GRID_BLOCKS, column, row), 4,
                                        &block_handle) ||
            !open_object(services, block_handle, &block) ||
            !vertrix_actor_set_handler(block.storage, block.size, MIRROR_BLOCK_HANDLER) ||
            !object_write(&block, POWER, 1, POWER_RETIRED) ||
            !vertrix_actor_set_period_steps(block.storage, block.size, STEPS) ||
            !object_read(&block, KIND_BYTE, 1, &kind) || !object_write(&block, BYTE_93, 1, 1) ||
            !object_write(&block, POWER, 1, POWER_RETIRED) ||
            !vertrix_block_spawn(board, board_size, (uint32_t)(int32_t)(int8_t)kind, services,
                                 &new_handle) ||
            !vertrix_actor_storage_write(
                board, board_size, cell_offset(GRID_COMPANIONS, column, row), 4, new_handle) ||
            !open_object(services, new_handle, &mirror) ||
            !vertrix_actor_set_d0_steps(mirror.storage, mirror.size, 1) ||
            !inherit_period_and_frame(&mirror, &block) || !object_write(&mirror, POWER, 1, 0) ||
            !object_write(&mirror, BYTE_93, 1, 1) || !object_write(&mirror, BYTE_44, 1, 0) ||
            !vertrix_actor_clear_counter(mirror.storage, mirror.size) ||
            !vertrix_actor_clear_cc(mirror.storage, mirror.size) ||
            !vertrix_actor_clear_counter(block.storage, block.size) ||
            !vertrix_actor_clear_cc(block.storage, block.size) ||
            !vertrix_actor_set_handler(mirror.storage, mirror.size, MIRROR_NEW_HANDLER))
        {
            return 0;
        }
    }
    return 1;
}

static int16_t high_word(uint32_t value)
{
    return (int16_t)(value >> 16);
}

static int scatter_block(const Object *block, const uint16_t *angle_table, int16_t origin_x,
                         int16_t origin_y, const VertrixFactoryServices *services)
{
    uint32_t x, y;
    int valid = 1;
    if (!object_read(block, OBJECT_ORIGIN_X, 4, &x) || !object_read(block, OBJECT_ORIGIN_Y, 4, &y))
    {
        return 0;
    }
    uint16_t target_x = (uint16_t)(high_word(x) + SCATTER_CENTRE);
    uint16_t target_y = (uint16_t)(high_word(y) + SCATTER_CENTRE);
    uint32_t distance =
        vertrix_point_distance((uint16_t)origin_x, (uint16_t)origin_y, target_x, target_y, &valid);
    if (!valid || !vertrix_actor_set_words_2a(block->storage, block->size, (uint16_t)distance,
                                              (uint16_t)origin_x, (uint16_t)origin_y))
    {
        return 0;
    }
    uint16_t heading = vertrix_point_heading(angle_table, (uint16_t)origin_x, (uint16_t)origin_y,
                                             target_x, target_y, &valid);
    uint16_t speed =
        (uint16_t)(services->draw(SCATTER_DRAW, services->context) + SCATTER_DRAW_BASE);
    return valid && object_write(block, OBJECT_HEADING, 2, heading % SCATTER_FULL_TURN) &&
           object_write(block, OBJECT_SPEED, 2, speed) &&
           vertrix_actor_set_handler(block->storage, block->size, SCATTER_HANDLER) &&
           object_write(block, POWER, 1, POWER_RETIRED) &&
           vertrix_actor_set_period_steps(block->storage, block->size, SCATTER_STEPS) &&
           object_write(block, BYTE_93, 1, 1) && object_write(block, DWORD_58, 4, 0) &&
           object_write(block, DWORD_5C, 4, SCATTER_DELAY) && object_write(block, DWORD_60, 4, 1) &&
           object_write(block, DWORD_64, 4, 0) && object_write(block, DWORD_68, 4, 1) &&
           object_write(block, DWORD_6C, 4, 1) &&
           vertrix_actor_clear_counter(block->storage, block->size) &&
           vertrix_actor_clear_cc(block->storage, block->size);
}

int vertrix_board_scatter_marked(void *board, size_t board_size,
                                 const uint16_t angle_table[VERTRIX_RATIO_TABLE_SIZE],
                                 const VertrixFactoryServices *services)
{
    const uint8_t *markers = (const uint8_t *)board + MARKERS;
    uint32_t board_x, board_y;
    if (!board || board_size < MARKERS + CELL_COUNT ||
        !vertrix_actor_storage_read(board, board_size, BOARD_ORIGIN_X, 4, &board_x) ||
        !vertrix_actor_storage_read(board, board_size, BOARD_ORIGIN_Y, 4, &board_y))
    {
        return 0;
    }
    uint32_t pending = vertrix_board_marker_count(markers, MARKER_PENDING);
    int16_t origin_x = (int16_t)(high_word(board_x) + SCATTER_ORIGIN_X);
    int16_t origin_y = (int16_t)(high_word(board_y) + SCATTER_ORIGIN_Y);
    for (uint32_t n = 0; n < pending; ++n)
    {
        uint32_t column, row, handle;
        Object block;
        if (!vertrix_board_marker_nth_by_row(markers, MARKER_PENDING, n, &column, &row) ||
            !retire_block(board, board_size, column, row, &handle) ||
            !open_object(services, handle, &block) ||
            !scatter_block(&block, angle_table, origin_x, origin_y, services))
        {
            return 0;
        }
    }
    return pending != 0;
}

int vertrix_board_prime_companions(void *board, size_t board_size,
                                   const VertrixFactoryServices *services)
{
    if (!board || board_size < MARKERS)
    {
        return 0;
    }
    for (uint32_t row = 0; row < ROWS; ++row)
    {
        services->draw(PRIME_DRAW, services->context);
        for (uint32_t column = 0; column < COLUMNS; ++column)
        {
            uint32_t handle;
            Object block;
            if (!vertrix_actor_storage_read(board, board_size,
                                            cell_offset(GRID_COMPANIONS, column, row), 4, &handle))
            {
                return 0;
            }
            if (handle != 0 && (!open_object(services, handle, &block) ||
                                !object_write(&block, DWORD_68, 4, PRIME_VALUE)))
            {
                return 0;
            }
        }
    }
    return 1;
}

/* The distance word of a flying half: |target - x| * 100 / 60, where the signed difference is cut
 * to 16 bits before the multiplication and the division is unsigned. */
static uint32_t split_distance(int16_t target, int16_t x)
{
    int32_t difference = (int32_t)target - x;
    uint32_t magnitude = (uint32_t)(difference < 0 ? -difference : difference);
    int16_t cut = (int16_t)magnitude;
    return ((uint32_t)((int32_t)cut * SPLIT_DISTANCE_PERCENT)) / SPLIT_DISTANCE_DIVISOR;
}

static int split_common(const Object *half)
{
    return vertrix_actor_set_handler(half->storage, half->size, SPLIT_HANDLER) &&
           object_write(half, POWER, 1, POWER_RETIRED) &&
           vertrix_actor_set_period_steps(half->storage, half->size, SPLIT_STEPS) &&
           object_write(half, BYTE_93, 1, 1) &&
           vertrix_actor_clear_counter(half->storage, half->size) &&
           vertrix_actor_clear_cc(half->storage, half->size) &&
           object_write(half, POWER, 1, POWER_RETIRED) &&
           object_write(half, SPLIT_POWER_B, 1, SPLIT_POWER_B_VALUE) &&
           object_write(half, SPLIT_WORD_50, 2, SPLIT_WORD_50_VALUE);
}

static int split_distance_store(const Object *half, uint32_t target, uint32_t x)
{
    return object_write(half, SPLIT_DISTANCE_WORD, 2,
                        split_distance((int16_t)target, (int16_t)x)) &&
           object_write(half, SPLIT_WORD_4C, 2, SPLIT_WORD_4C_VALUE);
}

static int split_one(void *board, size_t board_size, uint32_t column, uint32_t row,
                     const VertrixFactoryServices *services)
{
    uint32_t handle, board_x, kind, d0, frame, x, y, target, target_row, new_handle;
    Object old, half;
    if (!vertrix_actor_storage_read(board, board_size, OBJECT_X, 2, &board_x) ||
        !retire_block(board, board_size, column, row, &handle) ||
        !open_object(services, handle, &old) || !split_common(&old) ||
        !object_write(&old, SPLIT_TARGET, 2, board_x - SPLIT_LEFT_OFFSET) ||
        !object_write(&old, SPLIT_TARGET_ROW, 2,
                      services->draw(SPLIT_ROW_DRAW, services->context) + 1) ||
        !object_read(&old, OBJECT_X, 2, &x) || !object_read(&old, SPLIT_TARGET, 2, &target) ||
        !split_distance_store(&old, target, x) || !object_read(&old, KIND_BYTE, 1, &kind) ||
        !vertrix_block_spawn(board, board_size, (uint32_t)(int32_t)(int8_t)kind, services,
                             &new_handle) ||
        !vertrix_actor_storage_write(board, board_size, cell_offset(GRID_BLOCKS, column, row), 4,
                                     new_handle) ||
        !open_object(services, new_handle, &half) || !object_read(&old, OBJECT_X, 2, &x) ||
        !object_read(&old, OBJECT_Y, 2, &y) || !object_write(&half, OBJECT_X, 2, x) ||
        !object_write(&half, OBJECT_Y, 2, y) || !object_read(&old, OBJECT_D0, 4, &d0) ||
        !vertrix_actor_set_d0(half.storage, half.size, d0) ||
        !vertrix_actor_set_period_steps(half.storage, half.size, SPLIT_STEPS) ||
        !object_write(&half, BYTE_93, 1, 1) || !object_read(&old, OBJECT_FRAME, 4, &frame) ||
        !vertrix_actor_set_frame_index(half.storage, half.size, frame) || !split_common(&half) ||
        !object_write(&half, SPLIT_TARGET, 2, board_x + SPLIT_RIGHT_OFFSET) ||
        !object_read(&old, SPLIT_TARGET_ROW, 2, &target_row) ||
        !object_write(&half, SPLIT_TARGET_ROW, 2, target_row) ||
        !object_read(&half, SPLIT_TARGET, 2, &target) || !split_distance_store(&half, target, x))
    {
        return 0;
    }
    return 1;
}

int vertrix_board_split_marked(void *board, size_t board_size,
                               const VertrixFactoryServices *services)
{
    const uint8_t *markers = (const uint8_t *)board + MARKERS;
    if (!board || board_size < MARKERS + CELL_COUNT)
    {
        return 0;
    }
    uint32_t pending = vertrix_board_marker_count(markers, MARKER_PENDING);
    for (uint32_t n = 0; n < pending; ++n)
    {
        uint32_t column, row;
        if (!vertrix_board_marker_nth_by_row(markers, MARKER_PENDING, n, &column, &row) ||
            !split_one(board, board_size, column, row, services))
        {
            return 0;
        }
    }
    return pending != 0;
}

static int replace_child(void *board, size_t board_size, const Object *piece, uint32_t slot,
                         uint32_t kind, const VertrixFactoryServices *services)
{
    uint32_t handle, new_handle, d0, frame;
    Object old, replacement;
    size_t child = PIECE_CHILDREN + sizeof(uint32_t) * slot;
    if (!object_read(piece, child, 4, &handle) ||
        !object_write(piece, PIECE_SAVED_CHILDREN + sizeof(uint32_t) * slot, 4, handle) ||
        !object_write(piece, child, 4, 0))
    {
        return 0;
    }
    if (handle == 0)
    {
        return 1;
    }
    return open_object(services, handle, &old) &&
           vertrix_actor_set_handler(old.storage, old.size, CHILD_OLD_HANDLER) &&
           object_write(&old, POWER, 1, POWER_RETIRED) &&
           vertrix_actor_set_period_steps(old.storage, old.size, STEPS) &&
           vertrix_block_spawn(board, board_size, kind, services, &new_handle) &&
           object_write(piece, child, 4, new_handle) &&
           open_object(services, new_handle, &replacement) &&
           object_read(&old, OBJECT_D0, 4, &d0) &&
           vertrix_actor_set_d0(replacement.storage, replacement.size, d0) &&
           vertrix_actor_set_d0_steps(old.storage, old.size, CHILD_OLD_STEPS) &&
           vertrix_actor_set_period_steps(replacement.storage, replacement.size, STEPS) &&
           object_read(&old, OBJECT_FRAME, 4, &frame) &&
           vertrix_actor_set_frame_index(replacement.storage, replacement.size, frame) &&
           vertrix_actor_clear_counter(replacement.storage, replacement.size) &&
           vertrix_actor_clear_cc(replacement.storage, replacement.size) &&
           vertrix_actor_clear_counter(old.storage, old.size) &&
           vertrix_actor_clear_cc(old.storage, old.size) &&
           vertrix_actor_set_handler(replacement.storage, replacement.size, CHILD_NEW_HANDLER);
}

int vertrix_piece_replace_children(void *board, size_t board_size, const uint32_t kinds[3],
                                   const VertrixFactoryServices *services)
{
    uint32_t piece_handle;
    Object piece;
    if (!board || !vertrix_actor_storage_read(board, board_size, ACTIVE_PIECE, 4, &piece_handle) ||
        !open_object(services, piece_handle, &piece))
    {
        return 0;
    }
    for (uint32_t slot = 0; slot < PIECE_CHILD_COUNT; ++slot)
    {
        if (!replace_child(board, board_size, &piece, slot, kinds[slot], services))
        {
            return 0;
        }
    }
    return 1;
}

/* One step of 0x436b40 on a board: the first pending marker is taken. */
static int convert_first_marker(void *board, size_t board_size,
                                const VertrixFactoryServices *services, uint32_t *retired)
{
    uint8_t *markers = (uint8_t *)board + MARKERS;
    uint32_t column, row, handle, new_handle, d0, frame;
    Object old, replacement;
    if (!vertrix_board_marker_nth_by_row(markers, MARKER_PENDING, 0, &column, &row))
    {
        return 0;
    }
    markers[column * ROWS + row] = MARKER_TAKEN;
    if (!retire_block(board, board_size, column, row, &handle) ||
        !open_object(services, handle, &old) ||
        !vertrix_actor_set_handler(old.storage, old.size, COUNTED_OLD_HANDLER) ||
        !object_write(&old, POWER, 1, POWER_RETIRED) ||
        !vertrix_actor_set_period_steps(old.storage, old.size, STEPS))
    {
        return 0;
    }
    if (retired)
    {
        *retired = handle;
    }
    uint32_t kind = (uint16_t)services->draw(COUNTED_DRAW, services->context);
    return vertrix_block_spawn(board, board_size, kind, services, &new_handle) &&
           vertrix_actor_storage_write(board, board_size, cell_offset(GRID_BLOCKS, column, row), 4,
                                       new_handle) &&
           open_object(services, new_handle, &replacement) &&
           object_read(&old, OBJECT_D0, 4, &d0) &&
           vertrix_actor_set_d0(replacement.storage, replacement.size, d0) &&
           vertrix_actor_set_period_steps(replacement.storage, replacement.size, STEPS) &&
           object_read(&old, OBJECT_FRAME, 4, &frame) &&
           vertrix_actor_set_frame_index(replacement.storage, replacement.size, frame) &&
           vertrix_actor_clear_counter(replacement.storage, replacement.size) &&
           vertrix_actor_clear_cc(replacement.storage, replacement.size) &&
           vertrix_actor_clear_counter(old.storage, old.size) &&
           vertrix_actor_clear_cc(old.storage, old.size) &&
           vertrix_actor_set_handler(replacement.storage, replacement.size, COUNTED_NEW_HANDLER);
}

int vertrix_boards_convert_counts_traced(void *first, size_t first_size, void *second,
                                         size_t second_size, uint32_t count_first,
                                         uint32_t count_second,
                                         const VertrixFactoryServices *services,
                                         uint32_t *last_second_old)
{
    if (!first || !second || first_size < MARKERS + CELL_COUNT ||
        second_size < MARKERS + CELL_COUNT)
    {
        return 0;
    }
    for (uint32_t n = 0; n < count_first; ++n)
    {
        if (!convert_first_marker(first, first_size, services, NULL))
        {
            return 0;
        }
    }
    for (uint32_t n = 0; n < count_second; ++n)
    {
        if (!convert_first_marker(second, second_size, services, last_second_old))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_boards_convert_counts(void *first, size_t first_size, void *second, size_t second_size,
                                  uint32_t count_first, uint32_t count_second,
                                  const VertrixFactoryServices *services)
{
    return vertrix_boards_convert_counts_traced(first, first_size, second, second_size, count_first,
                                                count_second, services, NULL);
}

/* One round of 0x436d80 on a board: a drawn pending marker, if any. */
static int convert_drawn_marker(void *board, size_t board_size, uint32_t kind,
                                const VertrixFactoryServices *services)
{
    uint8_t *markers = (uint8_t *)board + MARKERS;
    uint32_t pending = vertrix_board_marker_count(markers, MARKER_PENDING);
    uint32_t column, row, handle, new_handle, d0, frame;
    Object old, replacement;
    if (pending == 0)
    {
        return 1;
    }
    uint32_t pick = (uint16_t)services->draw((uint16_t)pending, services->context);
    if (!vertrix_board_marker_nth_by_row(markers, MARKER_PENDING, pick, &column, &row))
    {
        return 0;
    }
    markers[column * ROWS + row] = MARKER_TAKEN;
    return retire_block(board, board_size, column, row, &handle) &&
           open_object(services, handle, &old) &&
           vertrix_actor_set_handler(old.storage, old.size, RANDOM_OLD_HANDLER) &&
           object_write(&old, POWER, 1, POWER_RETIRED) &&
           vertrix_actor_set_period_steps(old.storage, old.size, STEPS) &&
           vertrix_block_spawn(board, board_size, kind, services, &new_handle) &&
           vertrix_actor_storage_write(board, board_size, cell_offset(GRID_BLOCKS, column, row), 4,
                                       new_handle) &&
           open_object(services, new_handle, &replacement) &&
           object_read(&old, OBJECT_D0, 4, &d0) &&
           vertrix_actor_set_d0(replacement.storage, replacement.size, d0) &&
           vertrix_actor_set_period_steps(replacement.storage, replacement.size, STEPS) &&
           object_read(&old, OBJECT_FRAME, 4, &frame) &&
           vertrix_actor_set_frame_index(replacement.storage, replacement.size, frame) &&
           vertrix_actor_clear_counter(replacement.storage, replacement.size) &&
           vertrix_actor_clear_cc(replacement.storage, replacement.size) &&
           vertrix_actor_clear_counter(old.storage, old.size) &&
           vertrix_actor_clear_cc(old.storage, old.size) &&
           vertrix_actor_set_handler(replacement.storage, replacement.size, RANDOM_NEW_HANDLER) &&
           object_write(&replacement, BYTE_44, 1, 0);
}

int vertrix_boards_convert_random(void *first, size_t first_size, void *second, size_t second_size,
                                  uint32_t kind, uint32_t count_first, uint32_t count_second,
                                  const VertrixFactoryServices *services)
{
    if (!first || !second || first_size < MARKERS + CELL_COUNT ||
        second_size < MARKERS + CELL_COUNT)
    {
        return 0;
    }
    for (uint32_t n = 0; n < count_first; ++n)
    {
        if (!convert_drawn_marker(first, first_size, kind, services))
        {
            return 0;
        }
    }
    for (uint32_t n = 0; n < count_second; ++n)
    {
        if (!convert_drawn_marker(second, second_size, kind, services))
        {
            return 0;
        }
    }
    return 1;
}

static int collapse_kind(void *board, size_t board_size, uint8_t kind, uint32_t column,
                         int32_t *target, const VertrixFactoryServices *services)
{
    const uint8_t *markers = (const uint8_t *)board + MARKERS;
    uint32_t found_column, found_row;
    for (uint32_t n = 0;
         vertrix_board_marker_in_column(markers, kind, column, n, &found_column, &found_row); ++n)
    {
        uint32_t handle;
        Object block;
        size_t companion = cell_offset(GRID_COMPANIONS, found_column, found_row);
        if (!vertrix_actor_storage_read(board, board_size, companion, 4, &handle) ||
            !vertrix_actor_storage_write(board, board_size,
                                         cell_offset(GRID_BLOCKS, column, (uint32_t)*target), 4,
                                         handle) ||
            !vertrix_actor_storage_write(board, board_size, companion, 4, 0) ||
            !open_object(services, handle, &block) ||
            !vertrix_actor_start_slide(board, board_size, block.storage, block.size,
                                       (int32_t)(int16_t)column, (int32_t)(int16_t)*target))
        {
            return 0;
        }
        --*target;
    }
    return 1;
}

/* Whether some block of the block grid still has to travel from its start to its target. */
static int collapse_any_sliding(const void *board, size_t board_size,
                                const VertrixFactoryServices *services, uint32_t *sliding)
{
    *sliding = 0;
    for (uint32_t column = 0; column < COLUMNS; ++column)
    {
        for (uint32_t row = 0; row < ROWS; ++row)
        {
            uint32_t handle, start_x, target_x, start_y, target_y;
            Object block;
            if (!vertrix_actor_storage_read(board, board_size,
                                            cell_offset(GRID_BLOCKS, column, row), 4, &handle))
            {
                return 0;
            }
            if (handle == 0)
            {
                continue;
            }
            if (!open_object(services, handle, &block) ||
                !object_read(&block, COLLAPSE_START_X, 2, &start_x) ||
                !object_read(&block, COLLAPSE_TARGET_X, 2, &target_x) ||
                !object_read(&block, COLLAPSE_START_Y, 2, &start_y) ||
                !object_read(&block, COLLAPSE_TARGET_Y, 2, &target_y))
            {
                return 0;
            }
            if (start_x != target_x || start_y != target_y)
            {
                *sliding = 1;
                return 1;
            }
        }
    }
    return 1;
}

int vertrix_board_collapse_marked(void *board, size_t board_size,
                                  const VertrixFactoryServices *services, uint32_t *moving)
{
    const uint8_t *markers = (const uint8_t *)board + MARKERS;
    *moving = 0;
    if (!board || board_size < MARKERS + CELL_COUNT)
    {
        return 0;
    }
    if (vertrix_board_marker_count(markers, MARKER_KIND_SECOND) == 0 ||
        vertrix_board_marker_count(markers, MARKER_KIND_FIRST) == 0)
    {
        return 1;
    }
    for (uint32_t column = 0; column < COLUMNS; ++column)
    {
        for (uint32_t row = 0; row < ROWS; ++row)
        {
            uint32_t handle;
            if (!vertrix_actor_storage_read(board, board_size,
                                            cell_offset(GRID_BLOCKS, column, row), 4, &handle) ||
                !vertrix_actor_storage_write(
                    board, board_size, cell_offset(GRID_COMPANIONS, column, row), 4, handle) ||
                !vertrix_actor_storage_write(board, board_size,
                                             cell_offset(GRID_BLOCKS, column, row), 4, 0))
            {
                return 0;
            }
        }
    }
    for (uint32_t column = 0; column < COLUMNS; ++column)
    {
        int32_t target = COLLAPSE_BOTTOM_ROW;
        if (!collapse_kind(board, board_size, MARKER_KIND_FIRST, column, &target, services) ||
            !collapse_kind(board, board_size, MARKER_KIND_SECOND, column, &target, services))
        {
            return 0;
        }
    }
    if (!collapse_any_sliding(board, board_size, services, moving))
    {
        return 0;
    }
    if (*moving)
    {
        return 1;
    }
    for (uint32_t column = 0; column < COLUMNS; ++column)
    {
        for (uint32_t row = 0; row < ROWS; ++row)
        {
            uint32_t handle;
            Object block;
            if (!vertrix_actor_storage_read(board, board_size,
                                            cell_offset(GRID_BLOCKS, column, row), 4, &handle))
            {
                return 0;
            }
            if (handle != 0 &&
                (!open_object(services, handle, &block) || !object_write(&block, BYTE_93, 1, 0) ||
                 !object_write(&block, COLLAPSE_BYTE_95, 1, 1) ||
                 !object_write(&block, POWER, 1, COLLAPSE_POWER)))
            {
                return 0;
            }
        }
    }
    return 1;
}

int vertrix_board_pick_kinds(void *board, size_t board_size, const VertrixFactoryServices *services,
                             uint32_t out[5], uint32_t *count)
{
    uint32_t slots[CELL_COUNT];
    uint8_t kinds[CELL_COUNT];
    uint32_t seen[KIND_LIMIT] = {0};
    uint32_t list[PICK_OUTPUTS] = {0};
    uint32_t length = 0;
    if (!board || board_size < KINDS_SNAPSHOT + CELL_COUNT)
    {
        return 0;
    }
    for (uint32_t cell = 0; cell < CELL_COUNT; ++cell)
    {
        if (!vertrix_actor_storage_read(board, board_size, GRID_BLOCKS + 4 * (size_t)cell, 4,
                                        &slots[cell]))
        {
            return 0;
        }
    }
    if (!vertrix_board_snapshot_kinds(slots, CELL_COUNT, services->resolve, services->context,
                                      kinds))
    {
        return 0;
    }
    for (uint32_t cell = 0; cell < CELL_COUNT; ++cell)
    {
        int8_t kind = (int8_t)kinds[cell];
        if (!vertrix_actor_storage_write(board, board_size, KINDS_SNAPSHOT + cell, 1, kinds[cell]))
        {
            return 0;
        }
        if (kind >= 0 && kind < KIND_LIMIT)
        {
            ++seen[kind];
        }
    }
    for (uint32_t kind = 0; kind < KIND_LIMIT; ++kind)
    {
        if (seen[kind] > 0)
        {
            list[length++] = kind;
        }
    }
    if (length > 1)
    {
        for (uint32_t i = 0; i < length; ++i)
        {
            uint32_t pick = (uint16_t)services->draw((uint16_t)length, services->context);
            uint32_t kept = list[i];
            list[i] = list[pick];
            list[pick] = kept;
        }
    }
    *count = length > PICK_LIMIT ? PICK_LIMIT : length;
    for (uint32_t i = 0; i < PICK_OUTPUTS; ++i)
    {
        out[i] = list[i];
    }
    return 1;
}

/* The dwords 0x44cfd0/0x44ccd0 blocks share: +0x58..+0x6c = 0, 4, 1, 0, 2, 1 and word +0x46 = 1. */
static int spin_dwords(const Object *block)
{
    return object_write(block, SPIN_WORD_46, 2, 1) && object_write(block, DWORD_58, 4, 0) &&
           object_write(block, DWORD_5C, 4, SPIN_DWORD_5C) && object_write(block, DWORD_60, 4, 1) &&
           object_write(block, DWORD_64, 4, 0) && object_write(block, DWORD_68, 4, SPIN_DWORD_68) &&
           object_write(block, DWORD_6C, 4, 1);
}

static int spin_one(void *board, size_t board_size, uint8_t kind, uint32_t n, int draw_kind,
                    const VertrixFactoryServices *services)
{
    const uint8_t *markers = (const uint8_t *)board + MARKERS;
    uint32_t column, row, handle, new_handle, x, y, d0, period, frame;
    Object old, replacement;
    uint32_t draw = (uint16_t)services->draw(SPIN_DRAW, services->context);
    uint32_t spin = draw + SPIN_BIAS;
    if (spin > SPIN_WRAP)
    {
        spin -= SPIN_WRAP;
    }
    if (!vertrix_board_marker_nth_by_row(markers, kind, n, &column, &row) ||
        !retire_block(board, board_size, column, row, &handle) ||
        !open_object(services, handle, &old) ||
        !vertrix_actor_set_handler(old.storage, old.size, SPIN_OLD_HANDLER) ||
        !object_write(&old, POWER, 1, POWER_RETIRED))
    {
        return 0;
    }
    uint32_t steps = (uint16_t)services->draw(SPIN_STEPS_DRAW, services->context) + SPIN_BIAS;
    if (!vertrix_actor_set_period_steps(old.storage, old.size, steps) ||
        !object_write(&old, BYTE_93, 1, 1) || !vertrix_actor_clear_counter(old.storage, old.size) ||
        !vertrix_actor_clear_cc(old.storage, old.size) ||
        !object_write(&old, SPIN_BYTE_44, 1, SPIN_OLD_BYTE_44) ||
        !object_write(&old, SPIN_BYTE_45, 1, 0) || !spin_dwords(&old) ||
        !object_read(&old, OBJECT_X, 2, &x) || !object_read(&old, OBJECT_Y, 2, &y) ||
        !object_write(&old, SPIN_START_X, 2, x) || !object_write(&old, SPIN_START_Y, 2, y) ||
        !object_write(&old, SPIN_WORD_24, 2, spin))
    {
        return 0;
    }
    uint32_t kind_draw = SPIN_STONE_KIND;
    if (draw_kind)
    {
        kind_draw = (uint16_t)services->draw(SPIN_KIND_DRAW, services->context);
    }
    return vertrix_block_spawn(board, board_size, kind_draw, services, &new_handle) &&
           vertrix_actor_storage_write(board, board_size, cell_offset(GRID_BLOCKS, column, row), 4,
                                       new_handle) &&
           open_object(services, new_handle, &replacement) && object_read(&old, OBJECT_X, 2, &x) &&
           object_read(&old, OBJECT_Y, 2, &y) && object_write(&replacement, OBJECT_X, 2, x) &&
           object_write(&replacement, OBJECT_Y, 2, y) &&
           object_write(&replacement, SPIN_START_X, 2, x) &&
           object_write(&replacement, SPIN_START_Y, 2, y) && object_read(&old, OBJECT_D0, 4, &d0) &&
           vertrix_actor_set_d0(replacement.storage, replacement.size, d0) &&
           object_read(&old, SPIN_PERIOD, 4, &period) &&
           vertrix_actor_set_period(replacement.storage, replacement.size, period) &&
           object_write(&replacement, BYTE_93, 1, 1) &&
           object_write(&replacement, POWER, 1, SPIN_NEW_POWER) &&
           object_read(&old, OBJECT_FRAME, 4, &frame) &&
           vertrix_actor_set_frame_index(replacement.storage, replacement.size, frame) &&
           vertrix_actor_set_handler(replacement.storage, replacement.size, SPIN_NEW_HANDLER) &&
           vertrix_actor_clear_counter(replacement.storage, replacement.size) &&
           vertrix_actor_clear_cc(replacement.storage, replacement.size) &&
           object_write(&replacement, SPIN_BYTE_44, 1, 0) &&
           object_write(&replacement, SPIN_BYTE_45, 1, SPIN_NEW_BYTE_45) &&
           spin_dwords(&replacement) && object_write(&replacement, SPIN_WORD_24, 2, draw);
}

int vertrix_board_spin_marked(void *board, size_t board_size,
                              const VertrixFactoryServices *services, uint32_t *result)
{
    const uint8_t *markers = (const uint8_t *)board + MARKERS;
    if (!board || board_size < MARKERS + CELL_COUNT)
    {
        return 0;
    }
    uint32_t first = vertrix_board_marker_count(markers, MARKER_KIND_SECOND);
    uint32_t second = vertrix_board_marker_count(markers, MARKER_KIND_FIRST);
    *result = first != 0 || second != 0;
    for (uint32_t n = 0; n < first; ++n)
    {
        if (!spin_one(board, board_size, MARKER_KIND_SECOND, n, 1, services))
        {
            return 0;
        }
    }
    for (uint32_t n = 0; n < second; ++n)
    {
        if (!spin_one(board, board_size, MARKER_KIND_FIRST, n, 0, services))
        {
            return 0;
        }
    }
    return 1;
}

static int swirl_block(const void *board, size_t board_size, const Object *block, uint32_t column)
{
    uint32_t board_x, y;
    return vertrix_actor_storage_read(board, board_size, OBJECT_X, 2, &board_x) &&
           vertrix_actor_set_handler(block->storage, block->size, SWIRL_HANDLER) &&
           object_write(block, POWER, 1, POWER_RETIRED) &&
           vertrix_actor_set_period_steps(block->storage, block->size, SCATTER_STEPS) &&
           object_write(block, BYTE_93, 1, 1) &&
           object_write(block, SPIN_WORD_24, 2, (column * SWIRL_ANGLE_STEP) % SCATTER_FULL_TURN) &&
           object_write(block, SWIRL_WORD_28_OFFSET, 2, SWIRL_WORD_28) &&
           object_write(block, DWORD_58, 4, 0) && object_write(block, DWORD_5C, 4, SWIRL_DELAY) &&
           object_write(block, DWORD_60, 4, 1) && object_write(block, SWIRL_WORD_18, 2, 0) &&
           object_write(block, SPIN_WORD_46, 2, 1) &&
           object_write(block, POWER, 1, POWER_RETIRED) &&
           object_write(block, SWIRL_BYTE_4F, 1, 0) && object_write(block, SWIRL_WORD_50, 2, 1) &&
           object_write(block, SWIRL_WORD_12, 2, SWIRL_WORD_VALUE) &&
           object_write(block, SPIN_START_X, 2, board_x + SWIRL_ORIGIN_X) &&
           object_read(block, OBJECT_Y, 2, &y) &&
           object_write(block, SWIRL_WORD_1A, 2, SWIRL_WORD_VALUE) &&
           object_write(block, SPIN_START_Y, 2, y + SWIRL_ORIGIN_Y) &&
           vertrix_actor_clear_counter(block->storage, block->size) &&
           vertrix_actor_clear_cc(block->storage, block->size);
}

int vertrix_board_swirl_marked(void *board, size_t board_size,
                               const VertrixFactoryServices *services)
{
    const uint8_t *markers = (const uint8_t *)board + MARKERS;
    if (!board || board_size < MARKERS + CELL_COUNT)
    {
        return 0;
    }
    uint32_t pending = vertrix_board_marker_count(markers, MARKER_PENDING);
    for (uint32_t n = 0; n < pending; ++n)
    {
        uint32_t column, row, handle;
        Object block;
        if (!vertrix_board_marker_nth_by_row(markers, MARKER_PENDING, n, &column, &row) ||
            !retire_block(board, board_size, column, row, &handle) ||
            !open_object(services, handle, &block) ||
            !swirl_block(board, board_size, &block, column))
        {
            return 0;
        }
    }
    for (uint32_t row = 0; row < ROWS && pending != 0; ++row)
    {
        uint32_t offset = (uint16_t)services->draw(SCATTER_FULL_TURN, services->context);
        for (uint32_t column = 0; column < COLUMNS; ++column)
        {
            uint32_t handle, angle;
            Object block;
            if (!vertrix_actor_storage_read(board, board_size,
                                            cell_offset(GRID_COMPANIONS, column, row), 4, &handle))
            {
                return 0;
            }
            if (handle != 0 && (!open_object(services, handle, &block) ||
                                !object_read(&block, SPIN_WORD_24, 2, &angle) ||
                                !object_write(&block, SPIN_WORD_24, 2,
                                              ((angle + offset) & 0xffff) % SCATTER_FULL_TURN)))
            {
                return 0;
            }
        }
    }
    return pending != 0;
}

/* The even / odd handler pairs of the modes 0, 3 and 4. */
static const uint32_t MOTION_HANDLERS[5][2] = {
    {0x44f120, 0x44f180}, {0, 0}, {0, 0}, {0x44f4a0, 0x44f500}, {0x44f5d0, 0x44f630}};

static int motion_pair(const Object *block, uint32_t handler, int odd)
{
    return object_write(block, MOTION_WORD_4C, 2, MOTION_PHASE) &&
           object_write(block, MOTION_WORD_48, 2, 0) &&
           object_write(block, MOTION_WORD_4A, 2, odd ? MOTION_FALL : MOTION_RISE) &&
           vertrix_actor_set_handler(block->storage, block->size, handler);
}

static int motion_block(const Object *block, uint8_t mode, int odd,
                        const VertrixFactoryServices *services)
{
    if (!vertrix_actor_set_period_steps(block->storage, block->size, MOTION_STEPS) ||
        !vertrix_actor_clear_counter(block->storage, block->size))
    {
        return 0;
    }
    switch (mode)
    {
        case 0:
            return motion_pair(block, MOTION_HANDLERS[0][odd], odd);
        case 1:
            return object_write(block, MOTION_WORD_4C, 2, MOTION_MODE1_PHASE) &&
                   object_write(block, MOTION_WORD_48, 2, 0) &&
                   object_write(block, MOTION_WORD_4A, 2, MOTION_FALL) &&
                   vertrix_actor_set_handler(block->storage, block->size, MOTION_MODE1_HANDLER);
        case 2:
        {
            if (!object_write(block, MOTION_DWORD_80, 4, 0) ||
                !object_write(block, MOTION_DWORD_84, 4, 0))
            {
                return 0;
            }
            uint32_t extra =
                (uint16_t)services->draw(MOTION_DRAW_88, services->context) + MOTION_DRAW_88_BASE;
            if (!object_write(block, MOTION_DWORD_88, 4, extra) ||
                !object_write(block, MOTION_BYTE_8C, 1, 1))
            {
                return 0;
            }
            uint16_t pick = services->draw(MOTION_DRAW_HANDLER, services->context);
            return vertrix_actor_set_handler(block->storage, block->size,
                                             pick == 0 ? MOTION_MODE2_FIRST : MOTION_MODE2_SECOND);
        }
        case 3:
        case 4:
            return object_write(block, MOTION_BYTE_94, 1, 0) &&
                   object_write(block, MOTION_BYTE_52, 1, mode == 4) &&
                   motion_pair(block, MOTION_HANDLERS[mode][odd], odd);
        default:
            return 1;
    }
}

int vertrix_board_set_motion(void *board, size_t board_size, uint8_t mode,
                             const VertrixFactoryServices *services)
{
    int odd = 0;
    if (!board || board_size < MARKERS)
    {
        return 0;
    }
    for (uint32_t row = 0; row < ROWS; ++row)
    {
        for (uint32_t column = 0; column < COLUMNS; ++column)
        {
            uint32_t handle;
            Object block;
            if (!vertrix_actor_storage_read(board, board_size,
                                            cell_offset(GRID_BLOCKS, column, row), 4, &handle))
            {
                return 0;
            }
            if (handle != 0 && (!open_object(services, handle, &block) ||
                                (mode <= 4 && !motion_block(&block, mode, odd, services))))
            {
                return 0;
            }
            odd = !odd;
        }
    }
    return 1;
}

enum
{
    STONE_COLLECTION = 0x988,
    STONE_COLLECTION_SIZE = 5,
    STONE_KIND_BYTES = 0x980,
    STONE_KIND_VALUE = 5,
    STONE_HANDLER = 0x44f700,
    STONE_PERIOD_STEPS = 4,
    DESTROY_FLAG = 2
};

int vertrix_board_place_stones(void *board, size_t board_size, int32_t low, int32_t high,
                               const VertrixFactoryServices *services, VertrixBoardDestroy destroy,
                               void *destroy_context, uint32_t *placed)
{
    uint32_t slots[CELL_COUNT];
    uint8_t kinds[CELL_COUNT];
    *placed = 0;
    for (uint32_t i = 0; i < STONE_COLLECTION_SIZE; ++i)
    {
        uint32_t handle;
        size_t at = STONE_COLLECTION + 4 * (size_t)i;
        if (!vertrix_actor_storage_read(board, board_size, at, 4, &handle))
        {
            return 0;
        }
        if (handle != 0)
        {
            destroy(handle, DESTROY_FLAG, destroy_context);
            vertrix_actor_storage_write(board, board_size, at, 4, 0);
        }
    }
    if (low >= high)
    {
        return 1;
    }
    for (uint32_t cell = 0; cell < CELL_COUNT; ++cell)
    {
        if (!vertrix_actor_storage_read(board, board_size, GRID_BLOCKS + 4 * (size_t)cell, 4,
                                        &slots[cell]))
        {
            return 0;
        }
    }
    if (!vertrix_board_snapshot_kinds(slots, CELL_COUNT, services->resolve, services->context,
                                      kinds))
    {
        return 0;
    }
    for (uint32_t cell = 0; cell < CELL_COUNT; ++cell)
    {
        if (!vertrix_actor_storage_write(board, board_size, KINDS_SNAPSHOT + cell, 1, kinds[cell]))
        {
            return 0;
        }
    }
    for (uint32_t i = 0; i < STONE_COLLECTION_SIZE; ++i)
    {
        if (!vertrix_actor_storage_write(board, board_size, STONE_KIND_BYTES + i, 1,
                                         STONE_KIND_VALUE))
        {
            return 0;
        }
    }
    for (uint32_t i = 0; i < STONE_COLLECTION_SIZE; ++i)
    {
        uint32_t handle;
        Object block;
        if (!vertrix_block_spawn(board, board_size, STONE_KIND_VALUE, services, &handle) ||
            !vertrix_actor_storage_write(board, board_size, STONE_COLLECTION + 4 * (size_t)i, 4,
                                         handle) ||
            !open_object(services, handle, &block) ||
            !vertrix_actor_set_handler(block.storage, block.size, STONE_HANDLER) ||
            !vertrix_actor_set_period_steps(block.storage, block.size, STONE_PERIOD_STEPS))
        {
            return 0;
        }
    }
    *placed = 1;
    return 1;
}

enum
{
    DEAL_WIDTH = 13,
    DEAL_DRAW_LIMIT = 5,
    DEAL_EMPTY = 0xff,
    DEAL_PATTERN_STONE = 2,
    DEAL_PATTERN_DRAW = 1,
    DEAL_STONE_VALUE = 5,
    DEAL_HANDLER = 0x44f700
};

typedef struct
{
    size_t collection;
    size_t values;
    size_t kinds;
} DealRow;

static int deal_row(void *board, size_t board_size, int32_t a, int32_t b,
                    const VertrixDealTable *table, const VertrixFactoryServices *services,
                    VertrixBoardDestroy destroy, void *destroy_context, uint32_t *dealt,
                    const DealRow *row)
{
    uint32_t slots[CELL_COUNT];
    uint8_t kinds[CELL_COUNT];
    uint32_t any = 0;
    uint32_t counted = 0;
    size_t first = (size_t)DEAL_WIDTH * ((uint32_t)a + (uint32_t)b);
    *dealt = 0;
    for (uint32_t i = 0; i < DEAL_WIDTH; ++i)
    {
        uint32_t handle;
        size_t at = row->collection + 4 * (size_t)i;
        if (!vertrix_actor_storage_read(board, board_size, at, 4, &handle))
        {
            return 0;
        }
        if (handle != 0)
        {
            destroy(handle, DESTROY_FLAG, destroy_context);
            vertrix_actor_storage_write(board, board_size, at, 4, 0);
        }
    }
    if ((uint32_t)a > UINT32_MAX / DEAL_WIDTH ||
        (size_t)DEAL_WIDTH * (uint32_t)a + DEAL_WIDTH > table->pattern_size)
    {
        return 0;
    }
    for (uint32_t i = 0; i < DEAL_WIDTH; ++i)
    {
        any |= table->pattern[(size_t)DEAL_WIDTH * (uint32_t)a + i] != 0;
    }
    if (b >= 1 || any <= (uint32_t)b)
    {
        return 1;
    }
    if (first + DEAL_WIDTH > table->pattern_size)
    {
        return 0;
    }
    for (uint32_t cell = 0; cell < CELL_COUNT; ++cell)
    {
        if (!vertrix_actor_storage_read(board, board_size, GRID_BLOCKS + 4 * (size_t)cell, 4,
                                        &slots[cell]))
        {
            return 0;
        }
    }
    if (!vertrix_board_snapshot_kinds(slots, CELL_COUNT, services->resolve, services->context,
                                      kinds))
    {
        return 0;
    }
    for (uint32_t cell = 0; cell < CELL_COUNT; ++cell)
    {
        if (!vertrix_actor_storage_write(board, board_size, KINDS_SNAPSHOT + cell, 1, kinds[cell]))
        {
            return 0;
        }
    }
    for (uint32_t i = 0; i < DEAL_WIDTH; ++i)
    {
        uint8_t pattern = table->pattern[first + i];
        uint32_t previous = DEAL_EMPTY;
        uint32_t value;
        if (pattern == DEAL_PATTERN_STONE)
        {
            ++counted;
            if (!vertrix_actor_storage_write(board, board_size, row->values + i, 1,
                                             DEAL_STONE_VALUE))
            {
                return 0;
            }
        }
        else if (pattern == DEAL_PATTERN_DRAW)
        {
            if (i > 0 &&
                !vertrix_actor_storage_read(board, board_size, row->values + i - 1, 1, &previous))
            {
                return 0;
            }
            do
            {
                value = services->draw(DEAL_DRAW_LIMIT, services->context) & 0xff;
            } while (value == previous || value == kinds[row->kinds + i - KINDS_SNAPSHOT]);
            if (!vertrix_actor_storage_write(board, board_size, row->values + i, 1, value))
            {
                return 0;
            }
            ++counted;
        }
        else if (pattern == 0 &&
                 !vertrix_actor_storage_write(board, board_size, row->values + i, 1, DEAL_EMPTY))
        {
            return 0;
        }
    }
    if (counted == 0)
    {
        return 1;
    }
    for (uint32_t i = 0; i < DEAL_WIDTH; ++i)
    {
        uint32_t value, handle;
        Object block;
        if (!vertrix_actor_storage_read(board, board_size, row->values + i, 1, &value))
        {
            return 0;
        }
        if (value == DEAL_EMPTY)
        {
            vertrix_actor_storage_write(board, board_size, row->collection + 4 * (size_t)i, 4, 0);
            continue;
        }
        if (!vertrix_block_spawn(board, board_size, (uint32_t)(int32_t)(int8_t)value, services,
                                 &handle) ||
            !vertrix_actor_storage_write(board, board_size, row->collection + 4 * (size_t)i, 4,
                                         handle) ||
            !open_object(services, handle, &block) ||
            !vertrix_actor_set_handler(block.storage, block.size, DEAL_HANDLER) ||
            !vertrix_actor_set_period_steps(block.storage, block.size, table->period_steps))
        {
            return 0;
        }
    }
    *dealt = 1;
    return 1;
}

int vertrix_board_deal_first_row(void *board, size_t board_size, int32_t a, int32_t b,
                                 const VertrixDealTable *table,
                                 const VertrixFactoryServices *services,
                                 VertrixBoardDestroy destroy, void *destroy_context,
                                 uint32_t *dealt)
{
    static const DealRow row = {0x9e8, 0x9da, KINDS_SNAPSHOT};
    return deal_row(board, board_size, a, b, table, services, destroy, destroy_context, dealt,
                    &row);
}

int vertrix_board_deal_second_row(void *board, size_t board_size, int32_t a, int32_t b,
                                  const VertrixDealTable *table,
                                  const VertrixFactoryServices *services,
                                  VertrixBoardDestroy destroy, void *destroy_context,
                                  uint32_t *dealt)
{
    static const DealRow row = {0xa2c, 0xa1c, KINDS_SNAPSHOT + COLUMN_STRIDE};
    return deal_row(board, board_size, a, b, table, services, destroy, destroy_context, dealt,
                    &row);
}

enum
{
    REACH_MODE = 0x839,
    REACH_KIND = 6,
    REACH_LAST_COLUMN = COLUMNS - 1,
    REACH_LAST_ROW = ROWS - 1,
    REACH_MODE_SIDES_A = 1,
    REACH_MODE_BOTH = 3,
    REACH_MODE_ALL = 4,
    REACH_MODE_ROWS = 2
};

static int reach_extends(int32_t position, int32_t last, int32_t distance)
{
    return position - distance >= 0 || position + distance <= last;
}

int vertrix_board_marker_reach(void *board, size_t board_size,
                               const VertrixFactoryServices *services, uint32_t *reach)
{
    uint32_t slots[CELL_COUNT];
    uint8_t kinds[CELL_COUNT];
    uint32_t mode;
    uint32_t distance = 0;
    int changed = 1;
    for (uint32_t cell = 0; cell < CELL_COUNT; ++cell)
    {
        if (!vertrix_actor_storage_read(board, board_size, GRID_BLOCKS + 4 * (size_t)cell, 4,
                                        &slots[cell]))
        {
            return 0;
        }
    }
    if (!vertrix_board_snapshot_kinds(slots, CELL_COUNT, services->resolve, services->context,
                                      kinds))
    {
        return 0;
    }
    for (uint32_t cell = 0; cell < CELL_COUNT; ++cell)
    {
        if (!vertrix_actor_storage_write(board, board_size, KINDS_SNAPSHOT + cell, 1, kinds[cell]))
        {
            return 0;
        }
    }
    if (!vertrix_actor_storage_read(board, board_size, REACH_MODE, 1, &mode))
    {
        return 0;
    }
    while (changed)
    {
        changed = 0;
        ++distance;
        for (int32_t column = 0; column < COLUMNS; ++column)
        {
            for (int32_t row = 0; row < ROWS; ++row)
            {
                if (kinds[column * ROWS + row] != REACH_KIND)
                {
                    continue;
                }
                if ((mode == REACH_MODE_SIDES_A || mode == REACH_MODE_BOTH ||
                     mode == REACH_MODE_ALL) &&
                    reach_extends(column, REACH_LAST_COLUMN, (int32_t)distance))
                {
                    changed = 1;
                }
                if ((mode == REACH_MODE_ROWS || mode == REACH_MODE_BOTH ||
                     mode == REACH_MODE_ALL) &&
                    reach_extends(row, REACH_LAST_ROW, (int32_t)distance))
                {
                    changed = 1;
                }
                if (mode == REACH_MODE_ALL && (column > 0 || column < REACH_LAST_COLUMN) &&
                    reach_extends(row, REACH_LAST_ROW, (int32_t)distance))
                {
                    changed = 1;
                }
            }
        }
    }
    *reach = distance;
    return 1;
}

enum
{
    SWAP_OLD_HANDLER = 0x44d1e0,
    SWAP_POWER_VALUE = 0x64,
    SWAP_SAME_CLASS_HANDLER = 0x44c860,
    SWAP_OTHER_CLASS_HANDLER = 0x44d330,
    SWAP_MIN_MARKERS = 2,
    MARKER_SWAPPED = 2
};

typedef struct
{
    uint32_t column;
    uint32_t row;
    uint32_t block;
    Object old;
} SwapCell;

/* The kind byte of an object as a signed table index. */
static int swap_kind(const Object *object, int32_t *kind)
{
    uint32_t value;
    if (!object_read(object, KIND_BYTE, 1, &value))
    {
        return 0;
    }
    *kind = (int8_t)value;
    return 1;
}

/* Replacement of one cell: the new block of kind takes the cell of the retired block. */
static int swap_replace(void *board, size_t board_size, const VertrixFactoryServices *services,
                        const SwapCell *cell, int32_t kind, const uint8_t *kind_class,
                        size_t kind_class_size)
{
    uint32_t handle, d0, frame;
    int32_t old_kind, new_kind;
    Object replacement;
    if (!vertrix_block_spawn(board, board_size, (uint32_t)kind, services, &handle) ||
        !vertrix_actor_storage_write(
            board, board_size, cell_offset(GRID_BLOCKS, cell->column, cell->row), 4, handle) ||
        !open_object(services, handle, &replacement) ||
        !object_read(&cell->old, OBJECT_D0, 4, &d0) ||
        !vertrix_actor_set_d0(replacement.storage, replacement.size, d0) ||
        !vertrix_actor_set_period_steps(replacement.storage, replacement.size, STEPS) ||
        !object_read(&cell->old, OBJECT_FRAME, 4, &frame) ||
        !vertrix_actor_set_frame_index(replacement.storage, replacement.size, frame) ||
        !vertrix_actor_clear_counter(replacement.storage, replacement.size) ||
        !vertrix_actor_clear_cc(replacement.storage, replacement.size) ||
        !vertrix_actor_clear_counter(cell->old.storage, cell->old.size) ||
        !vertrix_actor_clear_cc(cell->old.storage, cell->old.size) ||
        !swap_kind(&cell->old, &old_kind) || !swap_kind(&replacement, &new_kind) || old_kind < 0 ||
        new_kind < 0 || (size_t)old_kind >= kind_class_size || (size_t)new_kind >= kind_class_size)
    {
        return 0;
    }
    return vertrix_actor_set_handler(replacement.storage, replacement.size,
                                     kind_class[old_kind] == kind_class[new_kind]
                                         ? SWAP_SAME_CLASS_HANDLER
                                         : SWAP_OTHER_CLASS_HANDLER);
}

static int swap_pick(void *board, size_t board_size, const VertrixFactoryServices *services,
                     uint8_t markers[CELL_COUNT], uint32_t count, SwapCell *cell)
{
    uint32_t draw = services->draw((uint16_t)count, services->context);
    if (!vertrix_board_marker_nth_by_row(markers, MARKER_PENDING, draw, &cell->column, &cell->row))
    {
        return 0;
    }
    markers[cell->column * ROWS + cell->row] = MARKER_SWAPPED;
    return vertrix_actor_storage_write(
        board, board_size, MARKERS + (size_t)cell->column * ROWS + cell->row, 1, MARKER_SWAPPED);
}

int vertrix_board_swap_marked(void *board, size_t board_size, const uint8_t *kind_class,
                              size_t kind_class_size, const VertrixFactoryServices *services,
                              uint32_t *swapped)
{
    uint8_t markers[CELL_COUNT];
    SwapCell first, second;
    uint32_t count, kind_first, kind_second;
    *swapped = 0;
    for (uint32_t cell = 0; cell < CELL_COUNT; ++cell)
    {
        uint32_t value;
        if (!vertrix_actor_storage_read(board, board_size, MARKERS + cell, 1, &value))
        {
            return 0;
        }
        markers[cell] = (uint8_t)value;
    }
    count = vertrix_board_marker_count(markers, MARKER_PENDING);
    if (count < SWAP_MIN_MARKERS)
    {
        return 1;
    }
    if (!swap_pick(board, board_size, services, markers, count, &first) ||
        !swap_pick(board, board_size, services, markers, count - 1, &second))
    {
        return 0;
    }
    if (!retire_block(board, board_size, first.column, first.row, &first.block) ||
        !retire_block(board, board_size, second.column, second.row, &second.block) ||
        !open_object(services, first.block, &first.old) ||
        !open_object(services, second.block, &second.old))
    {
        return 0;
    }
    if (!vertrix_actor_set_handler(first.old.storage, first.old.size, SWAP_OLD_HANDLER) ||
        !object_write(&first.old, POWER, 1, SWAP_POWER_VALUE) ||
        !vertrix_actor_set_period_steps(first.old.storage, first.old.size, STEPS) ||
        !vertrix_actor_set_handler(second.old.storage, second.old.size, SWAP_OLD_HANDLER) ||
        !object_write(&second.old, POWER, 1, SWAP_POWER_VALUE) ||
        !vertrix_actor_set_period_steps(second.old.storage, second.old.size, STEPS))
    {
        return 0;
    }
    kind_first = 0;
    kind_second = 0;
    if (!object_read(&second.old, KIND_BYTE, 1, &kind_second) ||
        !swap_replace(board, board_size, services, &first, (int8_t)kind_second, kind_class,
                      kind_class_size) ||
        !object_read(&first.old, KIND_BYTE, 1, &kind_first) ||
        !swap_replace(board, board_size, services, &second, (int8_t)kind_first, kind_class,
                      kind_class_size))
    {
        return 0;
    }
    *swapped = 1;
    return 1;
}
