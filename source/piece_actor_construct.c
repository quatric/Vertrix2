#include "piece_actor_construct.h"
#include "timing.h"
#include <string.h>

int vertrix_piece_actor_construct(void *parent, size_t parent_size, void *children,
                                  size_t children_size, const uint32_t frames[7],
                                  const uint32_t handles[7], uint8_t side, int difficulty,
                                  int level, uint16_t row_height)
{
    VertrixPiecePlacement placement = {138, 248, 488, 248, 14, 202, row_height};
    return vertrix_piece_actor_construct_placed(parent, parent_size, children, children_size,
                                                frames, handles, side, difficulty, level,
                                                &placement);
}

static int16_t placement_word(uint32_t value)
{
    uint32_t word = value & UINT32_C(0xffff);
    return (int16_t)(word < 32768 ? (int32_t)word : (int32_t)word - 65536);
}

int vertrix_piece_actor_construct_placed(void *parent, size_t parent_size, void *children,
                                         size_t children_size, const uint32_t frames[7],
                                         const uint32_t handles[7], uint8_t side, int difficulty,
                                         int level, const VertrixPiecePlacement *placement)
{
    if (!parent || parent_size < 0x18c || !frames || !placement || difficulty < 0 ||
        difficulty > 2 || level < 0 || level > 9)
    {
        return 0;
    }
    VertrixPiecePlacement geometry = *placement;
    uint32_t selected[7], identities[7];
    memcpy(selected, frames, sizeof(selected));
    size_t count = 0;
    for (size_t i = 0; i < 7; ++i)
    {
        count += selected[i] != UINT32_MAX;
    }
    size_t required = count * VERTRIX_ACTOR_BASE_SIZE;
    if (count)
    {
        if (!children || children_size < required || !handles)
        {
            return 0;
        }
        uintptr_t a = (uintptr_t)parent, b = (uintptr_t)children;
        if ((a <= b && b - a < 0x18c) || (b < a && a - b < required))
        {
            return 0;
        }
        memcpy(identities, handles, count * sizeof(*handles));
        for (size_t i = 0; i < count; ++i)
        {
            if (!identities[i])
            {
                return 0;
            }
            for (size_t j = 0; j < i; ++j)
            {
                if (identities[i] == identities[j])
                {
                    return 0;
                }
            }
        }
    }
    uint8_t next_parent[0x18c], next_children[7][VERTRIX_ACTOR_BASE_SIZE];
    memcpy(next_parent, parent, sizeof(next_parent));
    if (count)
    {
        memcpy(next_children, children, required);
    }
    uint32_t x = side ? geometry.right_x : geometry.left_x;
    uint32_t y = side ? geometry.right_y : geometry.left_y;
    VertrixPieceChildBounds bounds = {placement_word(x), placement_word(x + geometry.width - 1),
                                      placement_word(y), placement_word(y + geometry.height - 1)};
    VertrixMotion motion = {0};
    vertrix_motion_level(&motion, difficulty, level);
    vertrix_actor_storage_write(next_parent, sizeof(next_parent), 0xe, 2, (uint16_t)x);
    vertrix_actor_storage_write(next_parent, sizeof(next_parent), 0x16, 2,
                                y - (uint32_t)count * geometry.row_height);
    vertrix_actor_storage_write(next_parent, sizeof(next_parent), 0xc0, 4, motion.period);
    vertrix_actor_storage_write(next_parent, sizeof(next_parent), 0x1a, 2, motion.step);
    vertrix_actor_storage_write(next_parent, sizeof(next_parent), 0xe0, 4, 300);
    vertrix_actor_storage_write(next_parent, sizeof(next_parent), 0x8e, 1, 3);
    vertrix_actor_storage_write(next_parent, sizeof(next_parent), 0xa8, 2, (uint16_t)bounds.x_min);
    vertrix_actor_storage_write(next_parent, sizeof(next_parent), 0xaa, 2, (uint16_t)bounds.x_max);
    vertrix_actor_storage_write(next_parent, sizeof(next_parent), 0xac, 2, (uint16_t)bounds.y_min);
    vertrix_actor_storage_write(next_parent, sizeof(next_parent), 0xae, 2, (uint16_t)bounds.y_max);
    for (size_t i = 0; i < count; ++i)
    {
        vertrix_piece_child_construct(next_children[i], sizeof(next_children[i]), selected[i],
                                      &bounds, i + 1 == count);
        vertrix_actor_storage_write(next_parent, sizeof(next_parent), 0x15c + i * 4, 4,
                                    identities[i]);
    }
    vertrix_actor_storage_write(next_parent, sizeof(next_parent), 0x188, 4, (uint32_t)count);
    if (count)
    {
        memcpy(children, next_children, required);
    }
    memcpy(parent, next_parent, sizeof(next_parent));
    return 1;
}

int vertrix_piece_actor_construct_empty(void *actor, size_t actor_size)
{
    enum
    {
        EMPTY_SIZE = 0x174,
        EMPTY_CLASS = 0x514894
    };
    if (!actor || actor_size < EMPTY_SIZE || !vertrix_actor_storage_construct(actor, actor_size))
    {
        return 0;
    }
    return vertrix_actor_storage_write(actor, actor_size, 0x158, 4, EMPTY_CLASS) &&
           vertrix_actor_storage_write(actor, actor_size, 0x170, 4, 0) &&
           vertrix_actor_storage_write(actor, actor_size, 0x15c, 4, 0) &&
           vertrix_actor_storage_write(actor, actor_size, 0x160, 4, 0) &&
           vertrix_actor_storage_write(actor, actor_size, 0x164, 4, 0);
}

int vertrix_piece_actor_construct_slots(void *actor, size_t actor_size)
{
    enum
    {
        SLOTS_SIZE = 0x274,
        SLOTS_CLASS = 0x514624,
        SLOT_ROWS = 7,
        SLOT_COLUMNS = 4,
        SLOT_ROW_STRIDE = 16
    };
    uint32_t row;
    uint32_t column;
    if (!actor || actor_size < SLOTS_SIZE || !vertrix_actor_storage_construct(actor, actor_size) ||
        !vertrix_actor_storage_write(actor, actor_size, 0x158, 4, SLOTS_CLASS) ||
        !vertrix_actor_storage_write(actor, actor_size, 0x274, 1, 0xff) ||
        !vertrix_actor_storage_write(actor, actor_size, 0x278, 4, 1))
    {
        return 0;
    }
    for (row = 0; row < SLOT_ROWS; ++row)
    {
        for (column = 0; column < SLOT_COLUMNS; ++column)
        {
            if (!vertrix_actor_storage_write(actor, actor_size,
                                             0x15c + SLOT_ROW_STRIDE * row + 4 * column, 4, 0) ||
                !vertrix_actor_storage_write(actor, actor_size,
                                             0x1cc + SLOT_ROW_STRIDE * row + 4 * column, 4, 0) ||
                !vertrix_actor_storage_write(actor, actor_size, 0x23c + 4 * row + column, 1, 0) ||
                !vertrix_actor_storage_write(actor, actor_size, 0x258 + 4 * row + column, 1, 0))
            {
                return 0;
            }
        }
    }
    return 1;
}

int vertrix_piece_actor_spawn(void *board, size_t size, int32_t kind, VertrixPieceAllocate allocate,
                              VertrixPieceFinish finish, VertrixObjectStorage resolve,
                              void *context)
{
    enum
    {
        SLOT_FIELD = 0xb70,
        ACTOR_SIZE = 0x174
    };
    uint32_t slot;
    uint32_t actor;
    void *storage;
    size_t storage_size;
    int8_t signed_kind = (int8_t)(kind & 0xff);
    if (!vertrix_actor_storage_read(board, size, SLOT_FIELD, 4, &slot))
    {
        return 0;
    }
    if (slot != 0)
    {
        return 1;
    }
    actor = allocate(ACTOR_SIZE, context);
    if (actor != 0)
    {
        if (!resolve(actor, &storage, &storage_size, context) ||
            !vertrix_piece_actor_construct_empty(storage, storage_size))
        {
            return 0;
        }
    }
    if (!vertrix_actor_storage_write(board, size, SLOT_FIELD, 4, actor))
    {
        return 0;
    }
    finish(actor, signed_kind, context);
    return 1;
}
