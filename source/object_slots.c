#include "object_slots.h"
#include "actor_fields.h"
#include "actor_storage.h"
#include "object_access.h"

enum
{
    ARENA_FIRST = 0x15c,
    ARENA_SLOTS = 450,
    ARENA_PAIRS_FIRST = 0x864,
    ARENA_PAIRS_SLOTS = 3,
    ARENA_LAST_FIRST = 0x870,
    ARENA_LAST_SLOTS = 1,
    BOARD_PIECE = 0xa60,
    PIECE_FIRST_LIST = 0x15c,
    PIECE_SECOND_LIST = 0x170,
    PIECE_CHILDREN = 3,
    EFFECT_SLOTS = 500,
    EFFECT_SLOTS_FIRST = 0x15c,
    EFFECT_EXTRA_SLOTS = 8,
    EFFECT_EXTRA_FIRST = 0x92c,
    DESTROY_FLAG = 2,
    MARKER_CLASS = 0x158,
    MARKER_CLASS_TOKEN = 0x5145a4,
    MARKER_BYTE_A = 0x94,
    MARKER_BYTE_B = 0x95,
    MARKER_B_VALUE = 3,
    MARKER_KIND = 0x15c,
    MARKER_FLAG = 0x160,
    MARKER_STORAGE = 0x164,
    LIST_OBJECT = 0x468,
    LIST_COUNT = 8,
    TRIPLE_FIRST = 8,
    RECORD_SIZE = 0x60,
    ACTOR_LINK = 0x14c
};

int vertrix_object_release_slots(void *storage, size_t size, size_t offset, uint32_t count,
                                 VertrixBoardDestroy destroy, void *context)
{
    if (!storage || offset > size || (size_t)count * 4 > size - offset)
    {
        return 0;
    }
    for (uint32_t slot = 0; slot < count; ++slot)
    {
        uint32_t handle;
        size_t at = offset + (size_t)slot * 4;
        vertrix_actor_storage_read(storage, size, at, 4, &handle);
        if (handle != 0)
        {
            destroy(handle, DESTROY_FLAG, context);
        }
        vertrix_actor_storage_write(storage, size, at, 4, 0);
    }
    return 1;
}

int vertrix_piece_release_children(void *storage, size_t size, int second_list,
                                   VertrixBoardDestroy destroy, void *context)
{
    return vertrix_object_release_slots(storage, size,
                                        second_list ? PIECE_SECOND_LIST : PIECE_FIRST_LIST,
                                        PIECE_CHILDREN, destroy, context);
}

int vertrix_effects_release_all(void *storage, size_t size, VertrixBoardDestroy destroy,
                                void *context)
{
    return vertrix_object_release_slots(storage, size, EFFECT_SLOTS_FIRST, EFFECT_SLOTS, destroy,
                                        context) &&
           vertrix_object_release_slots(storage, size, EFFECT_EXTRA_FIRST, EFFECT_EXTRA_SLOTS,
                                        destroy, context);
}

int vertrix_arena_release_all(void *storage, size_t size, VertrixBoardDestroy destroy,
                              void *context)
{
    return vertrix_object_release_slots(storage, size, ARENA_FIRST, ARENA_SLOTS, destroy,
                                        context) &&
           vertrix_object_release_slots(storage, size, ARENA_PAIRS_FIRST, ARENA_PAIRS_SLOTS,
                                        destroy, context) &&
           vertrix_object_release_slots(storage, size, ARENA_LAST_FIRST, ARENA_LAST_SLOTS, destroy,
                                        context);
}

int vertrix_board_release_piece_children(const void *board, size_t board_size,
                                         VertrixObjectStorage resolve, VertrixBoardDestroy destroy,
                                         void *context)
{
    uint32_t piece;
    void *storage;
    size_t size;
    if (!vertrix_actor_storage_read(board, board_size, BOARD_PIECE, 4, &piece))
    {
        return 0;
    }
    return piece == 0 || (resolve(piece, &storage, &size, context) &&
                          vertrix_piece_release_children(storage, size, 1, destroy, context));
}

int vertrix_marker_actor_construct(void *storage, size_t size)
{
    if (!storage || size < MARKER_STORAGE || !vertrix_actor_storage_construct(storage, size))
    {
        return 0;
    }
    return vertrix_actor_storage_write(storage, size, MARKER_CLASS, 4, MARKER_CLASS_TOKEN) &&
           vertrix_actor_storage_write(storage, size, MARKER_BYTE_A, 1, 0) &&
           vertrix_actor_storage_write(storage, size, MARKER_BYTE_B, 1, MARKER_B_VALUE) &&
           vertrix_actor_storage_write(storage, size, MARKER_KIND, 1, 0xff) &&
           vertrix_actor_storage_write(storage, size, MARKER_FLAG, 4, 1);
}

uint32_t vertrix_object_address_plus_4(uint32_t object)
{
    return object + 4;
}

int vertrix_object_list_filled(const void *storage, size_t size, VertrixObjectStorage resolve,
                               void *context, uint32_t *filled)
{
    uint32_t list, count;
    if (!vertrix_actor_storage_read(storage, size, LIST_OBJECT, 4, &list) ||
        !vertrix_object_read(list, resolve, context, LIST_COUNT, 4, &count))
    {
        return 0;
    }
    *filled = count != 0;
    return 1;
}

int vertrix_object_triple(const void *storage, size_t size, uint32_t values[3])
{
    uint32_t read[3];
    for (int i = 0; i < 3; ++i)
    {
        if (!vertrix_actor_storage_read(storage, size, TRIPLE_FIRST + 4 * (size_t)i, 4, &read[i]))
        {
            return 0;
        }
    }
    for (int i = 0; i < 3; ++i)
    {
        values[i] = read[i];
    }
    return 1;
}

int vertrix_record_clear_flag(void *storage, size_t size, uint32_t index)
{
    return vertrix_actor_storage_write(storage, size, (size_t)(index & 0xffff) * RECORD_SIZE, 1, 0);
}

int vertrix_record_set_flag(void *storage, size_t size, uint32_t index)
{
    return vertrix_actor_storage_write(storage, size, (size_t)(index & 0xffff) * RECORD_SIZE, 1, 1);
}

static int actor_handler_from_ec(uint32_t handle, VertrixObjectStorage resolve, void *context)
{
    void *storage;
    size_t size;
    return resolve(handle, &storage, &size, context) &&
           vertrix_actor_handler_from_ec(storage, size);
}

int vertrix_actors_handler_from_ec(const uint32_t *handles, uint32_t count,
                                   VertrixObjectStorage resolve, void *context)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        if (!actor_handler_from_ec(handles[i], resolve, context))
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_actors_handler_from_ec_unlinked(const uint32_t *handles, uint32_t count, uint32_t link,
                                            VertrixObjectStorage resolve, void *context)
{
    for (uint32_t i = 0; i < count; ++i)
    {
        uint32_t actor_link;
        if (!vertrix_object_read(handles[i], resolve, context, ACTOR_LINK, 4, &actor_link))
        {
            return 0;
        }
        if (actor_link != link && !actor_handler_from_ec(handles[i], resolve, context))
        {
            return 0;
        }
    }
    return 1;
}

static uint32_t release_slots_full(void *storage, size_t size, size_t offset, int32_t count,
                                   uint32_t object, const VertrixCalls *runtime,
                                   VertrixMemoryRead read, void *read_context, int *ok)
{
    uint32_t result = object + (uint32_t)offset;
    *ok = 1;
    if (count == 0)
    {
        return result;
    }
    if (count < 0)
    {
        count = 1;
    }
    if (!storage || offset > size || (size_t)count > (size - offset) / 4)
    {
        *ok = 0;
        return 0;
    }
    for (int32_t slot = 0; slot < count; ++slot)
    {
        size_t at = offset + (size_t)slot * 4;
        uint32_t handle, table, entry;
        vertrix_actor_storage_read(storage, size, at, 4, &handle);
        if (handle)
        {
            if (!read || !read(handle + 0x158, 4, &table, read_context) ||
                !read(table, 4, &entry, read_context) || !entry)
            {
                *ok = 0;
                return 0;
            }
            result = vertrix_call(runtime, entry, handle, 2, table, object + (uint32_t)at, 0);
        }
        vertrix_actor_storage_write(storage, size, at, 4, 0);
    }
    return result;
}

uint32_t vertrix_object_release_slots_full(void *storage, size_t size, size_t offset, int32_t count,
                                           uint32_t object, const VertrixCalls *runtime,
                                           VertrixMemoryRead read, void *read_context)
{
    int ok;
    return release_slots_full(storage, size, offset, count, object, runtime, read, read_context,
                              &ok);
}

uint32_t vertrix_piece_release_children_full(void *storage, size_t size, int second_list,
                                             uint32_t object, const VertrixCalls *runtime,
                                             VertrixMemoryRead read, void *read_context)
{
    return vertrix_object_release_slots_full(storage, size,
                                             second_list ? PIECE_SECOND_LIST : PIECE_FIRST_LIST,
                                             PIECE_CHILDREN, object, runtime, read, read_context);
}

uint32_t vertrix_effects_release_all_full(void *storage, size_t size, uint32_t object,
                                          const VertrixCalls *runtime, VertrixMemoryRead read,
                                          void *read_context)
{
    int ok;
    release_slots_full(storage, size, EFFECT_SLOTS_FIRST, EFFECT_SLOTS, object, runtime, read,
                       read_context, &ok);
    if (!ok)
    {
        return 0;
    }
    return release_slots_full(storage, size, EFFECT_EXTRA_FIRST, EFFECT_EXTRA_SLOTS, object,
                              runtime, read, read_context, &ok);
}

uint32_t vertrix_arena_release_all_full(void *storage, size_t size, uint32_t object,
                                        const VertrixCalls *runtime, VertrixMemoryRead read,
                                        void *read_context)
{
    int ok;
    release_slots_full(storage, size, ARENA_FIRST, ARENA_SLOTS, object, runtime, read, read_context,
                       &ok);
    if (!ok)
    {
        return 0;
    }
    release_slots_full(storage, size, ARENA_PAIRS_FIRST, ARENA_PAIRS_SLOTS, object, runtime, read,
                       read_context, &ok);
    if (!ok)
    {
        return 0;
    }
    return release_slots_full(storage, size, ARENA_LAST_FIRST, ARENA_LAST_SLOTS, object, runtime,
                              read, read_context, &ok);
}

uint32_t vertrix_board_release_piece_children_full(
    const void *board, size_t board_size, uint32_t board_handle, VertrixObjectStorage resolve,
    void *resolve_context, const VertrixCalls *runtime, VertrixMemoryRead read, void *read_context)
{
    uint32_t piece;
    void *storage;
    size_t size;
    if (!vertrix_actor_storage_read(board, board_size, BOARD_PIECE, 4, &piece))
    {
        return 0;
    }
    if (!piece)
    {
        return board_handle;
    }
    if (!resolve || !resolve(piece, &storage, &size, resolve_context))
    {
        return 0;
    }
    return vertrix_piece_release_children_full(storage, size, 1, piece, runtime, read,
                                               read_context);
}

uint32_t vertrix_marker_actor_construct_full(void *storage, size_t size, uint32_t object)
{
    return vertrix_marker_actor_construct(storage, size) ? object : 0;
}
