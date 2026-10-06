#include "node_pool.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    POOL_USED = 0xc,
    POOL_FREE = 0x10,
    POOL_BLOCKS = 0x14,
    POOL_PER_BLOCK = 0x18,
    BLOCK_ALLOCATE = 0x4e23e0,
    PAIR_NODE_SIZE = 12,
    QUAD_NODE_SIZE = 16,
    NODE_NEXT_FIELD = 0,
    NODE_FIRST_FIELD = 4,
    NODE_CLEARED_FIELD = 8,
    NODE_SECOND_CLEARED_FIELD = 12,
    BLOCK_HEADER = 4,
    INITIALISE_PREPARE = 0x4ca060,
    INITIALISE_STORE = 0x4eb5e0,
    INITIALISE_EBX = 4
};

typedef struct Nodes
{
    const VertrixFactoryServices *services;
    uint32_t block;
    void *block_storage;
    size_t block_size;
} Nodes;

static int locate(const Nodes *nodes, uint32_t address, void **storage, size_t *size,
                  size_t *offset)
{
    if (nodes->block != 0 && address >= nodes->block && address - nodes->block < nodes->block_size)
    {
        *storage = nodes->block_storage;
        *size = nodes->block_size;
        *offset = address - nodes->block;
        return 1;
    }
    *offset = 0;
    return nodes->services->resolve(address, storage, size, nodes->services->context);
}

static int load(const Nodes *nodes, uint32_t address, size_t field, uint32_t *value)
{
    void *storage;
    size_t size, offset;
    return locate(nodes, address, &storage, &size, &offset) &&
           vertrix_actor_storage_read(storage, size, offset + field, DWORD_WIDTH, value);
}

static int store(const Nodes *nodes, uint32_t address, size_t field, uint32_t value)
{
    void *storage;
    size_t size, offset;
    return locate(nodes, address, &storage, &size, &offset) &&
           vertrix_actor_storage_write(storage, size, offset + field, DWORD_WIDTH, value);
}

/* Pops the head node, first refilling an empty free list. *ecx follows the original's register. */
static int pop_node(const VertrixCalls *calls, const VertrixFactoryServices *services,
                    Nodes *nodes_out, uint32_t pool, uint32_t node_size, uint32_t ebx, uint32_t edx,
                    uint32_t *ecx, uint32_t *edx_out, uint32_t *node)
{
    Nodes nodes = {services, 0, NULL, 0};
    uint32_t head, per_block, next;
    *edx_out = edx;
    if (!load(&nodes, pool, POOL_FREE, &head))
    {
        return 0;
    }
    if (head == 0)
    {
        uint32_t stack[3];
        uint32_t block, last;
        if (!load(&nodes, pool, POOL_PER_BLOCK, &per_block))
        {
            return 0;
        }
        stack[0] = pool + POOL_BLOCKS;
        stack[1] = per_block;
        stack[2] = node_size;
        block = vertrix_call3(calls, BLOCK_ALLOCATE, pool + POOL_BLOCKS, edx, ebx, *ecx, stack);
        if (!services->resolve(block, &nodes.block_storage, &nodes.block_size, services->context))
        {
            return 0;
        }
        nodes.block = block;
        last = per_block - 1;
        *ecx = last;
        *edx_out = last;
        if ((int32_t)last >= 0)
        {
            uint32_t address = block + BLOCK_HEADER + node_size * last;
            do
            {
                *ecx = head;
                if (!store(&nodes, address, NODE_NEXT_FIELD, head))
                {
                    return 0;
                }
                head = address;
                address -= node_size;
                --*edx_out;
            } while ((int32_t)*edx_out >= 0);
            if (!store(&nodes, pool, POOL_FREE, head))
            {
                return 0;
            }
        }
    }
    if (!load(&nodes, head, NODE_NEXT_FIELD, &next) || !store(&nodes, pool, POOL_FREE, next))
    {
        return 0;
    }
    *nodes_out = nodes;
    *node = head;
    return 1;
}

int vertrix_node_pool_take_pair(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t pool, uint32_t key, uint32_t value, uint32_t ecx,
                                uint32_t *node)
{
    Nodes nodes;
    uint32_t edx;
    if (!pop_node(calls, services, &nodes, pool, PAIR_NODE_SIZE, key, value, &ecx, &edx, node))
    {
        return 0;
    }
    uint32_t used;
    if (!store(&nodes, *node, NODE_FIRST_FIELD, value) ||
        !store(&nodes, *node, NODE_NEXT_FIELD, key) || !load(&nodes, pool, POOL_USED, &used) ||
        !store(&nodes, pool, POOL_USED, used + 1) || !store(&nodes, *node, NODE_CLEARED_FIELD, 0))
    {
        return 0;
    }
    return 1;
}

int vertrix_node_pool_take_initialised(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t pool,
                                       uint32_t key, uint32_t value, uint32_t ecx, uint32_t *node)
{
    Nodes nodes;
    uint32_t edx, used, next, prepared;
    if (!pop_node(calls, services, &nodes, pool, PAIR_NODE_SIZE, key, value, &ecx, &edx, node))
    {
        return 0;
    }
    if (!load(&nodes, pool, POOL_FREE, &next) || !store(&nodes, *node, NODE_FIRST_FIELD, value) ||
        !store(&nodes, *node, NODE_NEXT_FIELD, key) || !load(&nodes, pool, POOL_USED, &used) ||
        !store(&nodes, pool, POOL_USED, used + 1))
    {
        return 0;
    }
    prepared = vertrix_call(calls, INITIALISE_PREPARE, next, edx, INITIALISE_EBX, ecx, 0);
    vertrix_call(calls, INITIALISE_STORE, *node + NODE_CLEARED_FIELD, prepared, INITIALISE_EBX, ecx,
                 0);
    return 1;
}

int vertrix_node_pool_take_quad(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                uint32_t pool, uint32_t edx, uint32_t ecx, uint32_t *node,
                                uint32_t *block)
{
    Nodes nodes;
    uint32_t edx_out, used;
    if (!pop_node(calls, services, &nodes, pool, QUAD_NODE_SIZE, pool, edx, &ecx, &edx_out, node))
    {
        return 0;
    }
    *block = nodes.block;
    if (!load(&nodes, pool, POOL_USED, &used) || !store(&nodes, pool, POOL_USED, used + 1) ||
        !store(&nodes, *node, NODE_CLEARED_FIELD, 0) ||
        !store(&nodes, *node, NODE_SECOND_CLEARED_FIELD, 0))
    {
        return 0;
    }
    return 1;
}

int vertrix_node_pool_store(const VertrixFactoryServices *services, uint32_t block, uint32_t node,
                            size_t field, uint32_t value)
{
    Nodes nodes = {services, block, NULL, 0};
    if (block != 0 &&
        !services->resolve(block, &nodes.block_storage, &nodes.block_size, services->context))
    {
        return 0;
    }
    return store(&nodes, node, field, value);
}

enum
{
    MAP_BUCKETS = 4,
    MAP_BUCKET_COUNT = 8,
    MAP_LOOKUP = 0x4df0f0,
    MAP_RESIZE = 0x4def50,
    MAP_RESIZE_EBX = 1,
    MAP_NODE_HASH = 4,
    MAP_NODE_KEY = 8,
    MAP_NODE_VALUE = 0xc
};

int vertrix_map_find_or_add(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            uint32_t local, uint32_t map, uint32_t key, uint32_t *value)
{
    Nodes plain = {services, 0, NULL, 0};
    uint32_t hash, node, buckets, count, ebx = local, edx, block, head;
    node = vertrix_calln(calls, MAP_LOOKUP, map, key, local, map, NULL, 0, &hash);
    if (node != 0)
    {
        *value = node + MAP_NODE_VALUE;
        return 1;
    }
    edx = 0;
    if (!load(&plain, map, MAP_BUCKETS, &buckets))
    {
        return 0;
    }
    if (buckets == 0)
    {
        if (!load(&plain, map, MAP_BUCKET_COUNT, &count))
        {
            return 0;
        }
        ebx = MAP_RESIZE_EBX;
        edx = count;
        vertrix_call(calls, MAP_RESIZE, map, edx, ebx, map, 0);
    }
    (void)ebx;
    if (!vertrix_node_pool_take_quad(calls, services, map, edx, map, &node, &block) ||
        !load(&plain, map, MAP_BUCKETS, &buckets) ||
        !load(&plain, buckets, DWORD_WIDTH * (size_t)hash, &head))
    {
        return 0;
    }
    if (!vertrix_node_pool_store(services, block, node, MAP_NODE_HASH, hash) ||
        !vertrix_node_pool_store(services, block, node, MAP_NODE_KEY, key) ||
        !vertrix_node_pool_store(services, block, node, NODE_NEXT_FIELD, head) ||
        !vertrix_node_pool_store(services, 0, buckets, DWORD_WIDTH * (size_t)hash, node))
    {
        return 0;
    }
    *value = node + MAP_NODE_VALUE;
    return 1;
}

enum
{
    NODE_NONE = 0xffffffffu,
    NODE_BUCKET_FIELD = 4,
    NODE_KEY_FIELD = 8
};

/* The first non-empty bucket head from `bucket` on, or zero past the last bucket. */
static int next_head(const Nodes *plain, uint32_t buckets, uint32_t count, uint32_t bucket,
                     uint32_t *head)
{
    *head = 0;
    while (bucket < count)
    {
        if (!load(plain, buckets, DWORD_WIDTH * (size_t)bucket, head))
        {
            return 0;
        }
        if (*head != 0)
        {
            return 1;
        }
        bucket++;
    }
    return 1;
}

int vertrix_map_iterate(const VertrixFactoryServices *services, uint32_t map, uint32_t cursor,
                        uint32_t key_out, uint32_t value_out)
{
    Nodes plain = {services, 0, NULL, 0};
    uint32_t node, next, buckets, count, bucket, key, value;
    if (!load(&plain, cursor, 0, &node) || !load(&plain, map, MAP_BUCKETS, &buckets) ||
        !load(&plain, map, MAP_BUCKET_COUNT, &count))
    {
        return 0;
    }
    if (node == NODE_NONE)
    {
        /* the original walks off the buckets into address zero when none is occupied */
        if (!next_head(&plain, buckets, count, 0, &node) || node == 0)
        {
            return 0;
        }
    }
    if (!load(&plain, node, NODE_NEXT_FIELD, &next))
    {
        return 0;
    }
    if (next == 0)
    {
        if (!load(&plain, node, NODE_BUCKET_FIELD, &bucket) ||
            !next_head(&plain, buckets, count, bucket + 1, &next))
        {
            return 0;
        }
    }
    if (!load(&plain, node, NODE_KEY_FIELD, &key) || !load(&plain, node, MAP_NODE_VALUE, &value))
    {
        return 0;
    }
    return vertrix_node_pool_store(services, 0, cursor, 0, next) &&
           vertrix_node_pool_store(services, 0, key_out, 0, key) &&
           vertrix_node_pool_store(services, 0, value_out, 0, value);
}
