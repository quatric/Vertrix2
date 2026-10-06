#include "piece_children.h"
#include "actor_fields.h"
#include "object_access.h"
#include <string.h>

enum
{
    PIECE_LEFT = 0xa8,
    PIECE_ANCHOR = 0xaa,
    PIECE_ARMED = 0x170,
    ARM_STORAGE = 0x174,
    ARM_WORD = 0x1a,
    REMEMBERED_KINDS = 0x168,
    PIECE_VARIANT = 0x168,
    VARIANT_RESOURCE_ZERO = 0x544ba0,
    VARIANT_RESOURCE_ONE = 0x544bbc,
    LIST_FIRST = 0x15c,
    LIST_SECOND = 0x170,
    CHILD_KIND = 0x15c,
    CHILD_FIELD_58 = 0x58,
    PIECE_X = 0xe,
    PIECE_Y = 0x16,
    PIECE_OFFSET_X = 0x16c,
    PIECE_OFFSET_Y = 0x16d,
    ROW_HEIGHT = 24,
    RESOURCE_BASE = 0x544ac0,
    RESOURCE_STRIDE = 28,
    SELECTED_HANDLER = 0x44c4c0,
    PIECE_KIND_DWORD = 0x15c,
    PIECE_CLASS_DWORD = 0x160,
    PIECE_TABLE_DWORD = 0x164,
    PIECE_RESET_DWORD = 0x180
};

static const uint32_t child_handlers[VERTRIX_PIECE_CHILD_COUNT] = {0x44c4c0, 0x44c3e0, 0x44c450};

/* Tables at 0x4f8cec and 0x4f8d38, one dword per kind index. */
static const uint32_t kind_table[VERTRIX_KIND_TABLE_COUNT] = {9, 3, 10, 7, 8, 9, 10, 5, 12, 11,
                                                              9, 6, 2,  7, 9, 8, 6,  5, 7};
static const uint32_t second_table[VERTRIX_KIND_TABLE_COUNT] = {5, 3, 2, 4, 7, 6, 8, 6, 9, 6,
                                                                8, 4, 2, 8, 5, 4, 8, 8, 7};

static int child_handle(uint32_t piece, int index, VertrixObjectStorage resolve, void *context,
                        uint32_t *handle)
{
    return vertrix_object_read(piece, resolve, context, LIST_FIRST + 4 * (size_t)index, 4, handle);
}

int vertrix_piece_child_kinds(uint32_t piece, VertrixObjectStorage resolve, void *context,
                              uint8_t kinds[VERTRIX_PIECE_CHILD_COUNT])
{
    for (int i = 0; i < VERTRIX_PIECE_CHILD_COUNT; ++i)
    {
        uint32_t handle;
        uint32_t kind;
        if (!child_handle(piece, i, resolve, context, &handle) ||
            !vertrix_object_read(handle, resolve, context, CHILD_KIND, 1, &kind))
        {
            return 0;
        }
        kinds[i] = (uint8_t)kind;
    }
    return 1;
}

/* Shared tail of one child's setup (0x43a41f..0x43a462). */
static int setup_child(uint32_t child, uint8_t kind, uint32_t handler, VertrixPieceAttach attach,
                       VertrixObjectStorage resolve, void *context)
{
    void *storage;
    size_t size;
    uint32_t resource = RESOURCE_BASE + (uint32_t)((int32_t)(int8_t)kind * RESOURCE_STRIDE);
    if (!resolve(child, &storage, &size, context))
    {
        return 0;
    }
    attach(child, resource, context);
    return vertrix_actor_storage_write(storage, size, CHILD_KIND, 1, kind) &&
           vertrix_actor_set_handler(storage, size, handler) &&
           vertrix_actor_storage_write(storage, size, CHILD_FIELD_58, 4, 0) &&
           vertrix_actor_clear_counter(storage, size);
}

int vertrix_piece_children_setup(uint32_t piece, const uint8_t kinds[VERTRIX_PIECE_CHILD_COUNT],
                                 VertrixPieceAttach attach, VertrixObjectStorage resolve,
                                 void *context)
{
    for (int i = 0; i < VERTRIX_PIECE_CHILD_COUNT; ++i)
    {
        uint32_t child;
        if (!child_handle(piece, i, resolve, context, &child) ||
            !setup_child(child, kinds[i], child_handlers[i], attach, resolve, context))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_piece_children_setup_selected(uint32_t piece,
                                          const uint8_t kinds[VERTRIX_PIECE_CHILD_COUNT],
                                          const uint32_t selected[VERTRIX_PIECE_CHILD_COUNT],
                                          VertrixPieceAttach attach, VertrixObjectStorage resolve,
                                          void *context)
{
    for (int i = 0; i < VERTRIX_PIECE_CHILD_COUNT; ++i)
    {
        uint32_t child;
        if (selected[i] != 1)
        {
            continue;
        }
        if (!child_handle(piece, i, resolve, context, &child) ||
            !setup_child(child, kinds[i], SELECTED_HANDLER, attach, resolve, context))
        {
            return 0;
        }
    }
    return 1;
}

/* One child of one list (0x42a818..0x42a89e): word arithmetic wraps at 16 bits. */
static int place_child(uint32_t piece, size_t list, int row, VertrixObjectStorage resolve,
                       void *context)
{
    uint32_t child;
    uint32_t x;
    uint32_t y;
    uint32_t offset_x;
    uint32_t offset_y;
    if (!vertrix_object_read(piece, resolve, context, list + 4 * (size_t)row, 4, &child))
    {
        return 0;
    }
    if (child == 0)
    {
        return 1;
    }
    if (!vertrix_object_read(piece, resolve, context, PIECE_OFFSET_X, 1, &offset_x) ||
        !vertrix_object_read(piece, resolve, context, PIECE_X, 2, &x) ||
        !vertrix_object_write(child, resolve, context, PIECE_X, 2,
                              (uint16_t)((int16_t)(int8_t)offset_x + (uint16_t)x)))
    {
        return 0;
    }
    if (!vertrix_object_read(piece, resolve, context, PIECE_Y, 2, &y) ||
        !vertrix_object_read(piece, resolve, context, PIECE_OFFSET_Y, 1, &offset_y))
    {
        return 0;
    }
    return vertrix_object_write(
        child, resolve, context, PIECE_Y, 2,
        (uint16_t)((uint16_t)y + (uint16_t)(ROW_HEIGHT * row) + (int16_t)(int8_t)offset_y));
}

int vertrix_piece_children_place(uint32_t piece, VertrixObjectStorage resolve, void *context)
{
    for (int i = 0; i < VERTRIX_PIECE_CHILD_COUNT; ++i)
    {
        if (!place_child(piece, LIST_FIRST, i, resolve, context) ||
            !place_child(piece, LIST_SECOND, i, resolve, context))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_piece_init_from_kind(void *storage, size_t size, uint8_t kind_index)
{
    uint32_t value;
    uint32_t class_value;
    if (kind_index >= VERTRIX_KIND_TABLE_COUNT)
    {
        return 0;
    }
    value = kind_table[kind_index];
    if (value == 12)
    {
        class_value = 4;
    }
    else if (value > 7)
    {
        class_value = 3;
    }
    else if (value <= 3)
    {
        class_value = 1;
    }
    else
    {
        class_value = 2;
    }
    return vertrix_actor_storage_write(storage, size, PIECE_KIND_DWORD, 4, value) &&
           vertrix_actor_storage_write(storage, size, PIECE_CLASS_DWORD, 4, class_value) &&
           vertrix_actor_storage_write(storage, size, PIECE_RESET_DWORD, 4, UINT32_MAX) &&
           vertrix_actor_storage_write(storage, size, PIECE_TABLE_DWORD, 4,
                                       second_table[kind_index]);
}

int vertrix_piece_children_setup_registers(uint32_t piece,
                                           const uint8_t kinds[VERTRIX_PIECE_CHILD_COUNT],
                                           VertrixPieceAttach attach, VertrixObjectStorage resolve,
                                           void *context)
{
    return vertrix_piece_children_setup(piece, kinds, attach, resolve, context);
}

int vertrix_piece_children_remember_and_setup(uint32_t piece,
                                              const uint8_t kinds[VERTRIX_PIECE_CHILD_COUNT],
                                              VertrixPieceAttach attach,
                                              VertrixObjectStorage resolve, void *context)
{
    uint8_t current[VERTRIX_PIECE_CHILD_COUNT];
    if (!vertrix_piece_child_kinds(piece, resolve, context, current))
    {
        return 0;
    }
    for (int i = 0; i < VERTRIX_PIECE_CHILD_COUNT; ++i)
    {
        if (!vertrix_object_write(piece, resolve, context, REMEMBERED_KINDS + i, 1, current[i]))
        {
            return 0;
        }
    }
    return vertrix_piece_children_setup(piece, kinds, attach, resolve, context);
}

int vertrix_piece_set_variant(uint32_t piece, uint32_t variant, VertrixPieceAttach attach,
                              VertrixObjectStorage resolve, void *context)
{
    if (!vertrix_object_write(piece, resolve, context, PIECE_VARIANT, 4, variant))
    {
        return 0;
    }
    if (variant == 0)
    {
        attach(piece, VARIANT_RESOURCE_ZERO, context);
    }
    else if (variant == 1)
    {
        attach(piece, VARIANT_RESOURCE_ONE, context);
    }
    return 1;
}

int vertrix_piece_children_restore_and_clear(uint32_t piece, VertrixPieceAttach attach,
                                             VertrixObjectStorage resolve, void *context)
{
    uint32_t kinds32[VERTRIX_PIECE_CHILD_COUNT];
    uint8_t kinds[VERTRIX_PIECE_CHILD_COUNT];
    for (int i = 0; i < VERTRIX_PIECE_CHILD_COUNT; ++i)
    {
        if (!vertrix_object_read(piece, resolve, context, REMEMBERED_KINDS + i, 1, &kinds32[i]))
        {
            return 0;
        }
        kinds[i] = (uint8_t)kinds32[i];
    }
    if (!vertrix_piece_children_setup(piece, kinds, attach, resolve, context))
    {
        return 0;
    }
    for (int i = 0; i < VERTRIX_PIECE_CHILD_COUNT; ++i)
    {
        if (!vertrix_object_write(piece, resolve, context, REMEMBERED_KINDS + i, 1, 0xff))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_piece_arm_once(void *storage, size_t size, uint32_t period, uint16_t word)
{
    uint8_t copy[ARM_STORAGE];
    uint32_t armed;
    if (!storage || size < sizeof(copy))
    {
        return 0;
    }
    memcpy(copy, storage, sizeof(copy));
    if (!vertrix_actor_storage_read(copy, sizeof(copy), PIECE_ARMED, 4, &armed))
    {
        return 0;
    }
    if (armed != 0)
    {
        return 1;
    }
    if (!vertrix_actor_storage_write(copy, sizeof(copy), PIECE_ARMED, 4, 1) ||
        !vertrix_actor_set_period(copy, sizeof(copy), period) ||
        !vertrix_actor_storage_write(copy, sizeof(copy), ARM_WORD, 2, word) ||
        !vertrix_actor_clear_counter(copy, sizeof(copy)))
    {
        return 0;
    }
    memcpy(storage, copy, sizeof(copy));
    return 1;
}

int vertrix_piece_snap_to_left(uint32_t piece, VertrixPieceAttach attach,
                               VertrixObjectStorage resolve, void *context)
{
    uint32_t x, left, flag;
    if (!vertrix_object_read(piece, resolve, context, PIECE_X, 2, &x) ||
        !vertrix_object_read(piece, resolve, context, PIECE_LEFT, 2, &left))
    {
        return 0;
    }
    if (x == left)
    {
        return 1;
    }
    if (!vertrix_object_read(piece, resolve, context, PIECE_OFFSET_X, 1, &flag) ||
        !vertrix_object_write(piece, resolve, context, PIECE_X, 2, left))
    {
        return 0;
    }
    return vertrix_piece_set_variant(piece, flag != 0, attach, resolve, context);
}

int vertrix_piece_snap_to_origin(uint32_t piece, uint32_t origin, VertrixPieceAttach attach,
                                 VertrixObjectStorage resolve, void *context)
{
    uint32_t x, anchor, flag;
    if (!vertrix_object_read(piece, resolve, context, PIECE_X, 2, &x) ||
        !vertrix_object_read(piece, resolve, context, PIECE_ANCHOR, 2, &anchor))
    {
        return 0;
    }
    if ((int32_t)(int16_t)x == (int32_t)((uint32_t)(int32_t)(int16_t)anchor - origin))
    {
        return 1;
    }
    if (!vertrix_object_read(piece, resolve, context, PIECE_OFFSET_X, 1, &flag) ||
        !vertrix_object_write(piece, resolve, context, PIECE_X, 2, anchor - origin))
    {
        return 0;
    }
    return vertrix_piece_set_variant(piece, flag == 1 ? 0 : 1, attach, resolve, context);
}

int vertrix_piece_child_slots_init(void *actor, size_t size)
{
    enum
    {
        SLOT_CLASS = 0x514b94,
        SLOT_SPAN = 0xc
    };
    uint32_t offset;
    if (!actor || !vertrix_actor_storage_construct(actor, size))
    {
        return 0;
    }
    if (!vertrix_actor_storage_write(actor, size, 0x158, 4, SLOT_CLASS))
    {
        return 0;
    }
    for (offset = 0; offset < SLOT_SPAN; offset += 4)
    {
        if (!vertrix_actor_storage_write(actor, size, 0x15c + offset, 4, 0) ||
            !vertrix_actor_storage_write(actor, size, 0x168 + offset / 4, 1, 0xff))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_piece_store_preview_kinds(void *preview, size_t size, uint8_t first, uint8_t second,
                                      uint8_t third)
{
    return vertrix_actor_storage_write(preview, size, REMEMBERED_KINDS, 1, first) &&
           vertrix_actor_storage_write(preview, size, REMEMBERED_KINDS + 1, 1, second) &&
           vertrix_actor_storage_write(preview, size, REMEMBERED_KINDS + 2, 1, third);
}
