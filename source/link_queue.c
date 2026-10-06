#include "link_queue.h"
#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4
};

static int read_field(uint32_t handle, size_t offset, VertrixObjectStorage resolve, void *context,
                      uint32_t *value)
{
    void *storage;
    size_t size;
    if (!resolve(handle, &storage, &size, context))
    {
        return 0;
    }
    return vertrix_actor_storage_read(storage, size, offset, DWORD_WIDTH, value);
}

static int write_field(uint32_t handle, size_t offset, uint32_t value, VertrixObjectStorage resolve,
                       void *context)
{
    void *storage;
    size_t size;
    if (!resolve(handle, &storage, &size, context))
    {
        return 0;
    }
    return vertrix_actor_storage_write(storage, size, offset, DWORD_WIDTH, value);
}

int vertrix_queue_pop(uint32_t header, VertrixObjectStorage resolve, VertrixQueueRelease release,
                      void *context)
{
    uint32_t head;
    uint32_t next;
    uint32_t payload;
    uint32_t scratch;
    if (!read_field(header, VERTRIX_QUEUE_HEAD, resolve, context, &head) || head == 0)
    {
        return 0;
    }
    if (!read_field(head, VERTRIX_NODE_NEXT, resolve, context, &next) ||
        !read_field(head, VERTRIX_NODE_PAYLOAD, resolve, context, &payload))
    {
        return 0;
    }
    if (next != 0 && !read_field(next, VERTRIX_NODE_PREVIOUS, resolve, context, &scratch))
    {
        return 0;
    }
    write_field(header, VERTRIX_QUEUE_HEAD, next, resolve, context);
    if (next != 0)
    {
        write_field(next, VERTRIX_NODE_PREVIOUS, 0, resolve, context);
    }
    else
    {
        write_field(header, VERTRIX_QUEUE_TAIL, 0, resolve, context);
    }
    release(payload, context);
    release(head, context);
    return 1;
}

static int link_node(uint32_t header, uint32_t node, uint32_t size, VertrixObjectStorage resolve,
                     void *context)
{
    uint32_t tail;
    uint32_t head;
    uint32_t total;
    if (!read_field(header, VERTRIX_QUEUE_TAIL, resolve, context, &tail) ||
        !read_field(header, VERTRIX_QUEUE_HEAD, resolve, context, &head) ||
        !read_field(header, VERTRIX_QUEUE_TOTAL, resolve, context, &total))
    {
        return 0;
    }
    if (!write_field(node, VERTRIX_NODE_NEXT, 0, resolve, context) ||
        !write_field(node, VERTRIX_NODE_PREVIOUS, tail, resolve, context) ||
        !write_field(node, VERTRIX_NODE_UNUSED, 0, resolve, context))
    {
        return 0;
    }
    if (head == 0)
    {
        write_field(header, VERTRIX_QUEUE_HEAD, node, resolve, context);
    }
    else if (!write_field(tail, VERTRIX_NODE_NEXT, node, resolve, context))
    {
        return 0;
    }
    write_field(header, VERTRIX_QUEUE_TAIL, node, resolve, context);
    write_field(header, VERTRIX_QUEUE_TOTAL, total + size, resolve, context);
    return 1;
}

uint32_t vertrix_queue_push(uint32_t header, uint32_t source, uint32_t size,
                            VertrixObjectStorage resolve, VertrixQueueAllocate allocate,
                            VertrixQueueCopy copy, VertrixQueueRelease release, void *context)
{
    uint32_t node = allocate(VERTRIX_NODE_BYTES, context);
    if (node == 0)
    {
        return 0;
    }
    uint32_t payload = allocate(size, context);
    if (!write_field(node, VERTRIX_NODE_PAYLOAD, payload, resolve, context))
    {
        return 0;
    }
    if (payload == 0)
    {
        release(node, context);
        return 0;
    }
    write_field(node, VERTRIX_NODE_SIZE, size, resolve, context);
    copy(payload, source, size, context);
    return link_node(header, node, size, resolve, context) ? node : 0;
}
