#include "record_stream.h"
#include "actor_storage.h"
#include "record_slots.h"

enum
{
    STATE_OFFSET = 0,
    DATA_OFFSET = 4,
    CLEARED_OFFSET = 0x50,
    COMPLEMENT_OFFSET = 0x70,
    COMPLEMENT_COUNT = 20
};

int vertrix_saved_block_load(void *object, size_t object_size, void *stream, size_t stream_size,
                             VertrixMemoryRead read, void *read_context, VertrixStreamFetch fetch,
                             void *fetch_context)
{
    uint8_t *bytes = object;
    uint32_t length, complete, state;
    if (!object || object_size < VERTRIX_SAVED_BLOCK_SIZE ||
        !vertrix_range_start(stream, stream_size, read, read_context) ||
        !vertrix_range_block_second(stream, stream_size, read, read_context, &length))
    {
        return 0;
    }
    if (length != VERTRIX_SAVED_BLOCK_SIZE)
    {
        return 1;
    }
    if (!vertrix_stream_read_exact(stream, stream_size, sizeof(uint32_t), 1, bytes + STATE_OFFSET,
                                   fetch, fetch_context, &complete) ||
        !vertrix_stream_read_exact(stream, stream_size, VERTRIX_SAVED_BLOCK_DATA, 1,
                                   bytes + DATA_OFFSET, fetch, fetch_context, &complete))
    {
        return 0;
    }
    for (int i = 0; i < COMPLEMENT_COUNT; ++i)
    {
        bytes[COMPLEMENT_OFFSET + i] = (uint8_t)(0xff - bytes[COMPLEMENT_OFFSET + i]);
    }
    if (!vertrix_actor_storage_read(object, object_size, STATE_OFFSET, 4, &state))
    {
        return 0;
    }
    if (state == VERTRIX_SAVED_BLOCK_STATE_LOADED)
    {
        return vertrix_actor_storage_write(object, object_size, STATE_OFFSET, 4,
                                           VERTRIX_SAVED_BLOCK_STATE_READY) &&
               vertrix_actor_storage_write(object, object_size, CLEARED_OFFSET, 4, 0);
    }
    return 1;
}

int vertrix_record_table_load(void *table, size_t table_size, void *stream, size_t stream_size,
                              VertrixMemoryRead read, void *read_context, VertrixStreamFetch fetch,
                              void *fetch_context)
{
    uint8_t *bytes = table;
    uint32_t saved, count, complete;
    if (!table || table_size < VERTRIX_RECORD_STORAGE_SIZE ||
        !vertrix_actor_storage_read(table, table_size, VERTRIX_RECORD_OWNER_OFFSET, 4, &saved) ||
        !vertrix_range_start(stream, stream_size, read, read_context) ||
        !vertrix_stream_read_exact(stream, stream_size, 2 * sizeof(uint32_t), 1,
                                   bytes + VERTRIX_RECORD_COUNT_OFFSET, fetch, fetch_context,
                                   &complete) ||
        !vertrix_actor_storage_read(table, table_size, VERTRIX_RECORD_OWNER_OFFSET, 4, &count) ||
        count > VERTRIX_RECORD_SLOTS ||
        !vertrix_stream_read_exact(stream, stream_size, VERTRIX_RECORD_SIZE, count, bytes, fetch,
                                   fetch_context, &complete))
    {
        return 0;
    }
    return vertrix_actor_storage_write(table, table_size, VERTRIX_RECORD_OWNER_OFFSET, 4, saved);
}
