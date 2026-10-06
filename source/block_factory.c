#include "block_factory.h"
#include "actor_fields.h"
#include "actor_storage.h"

enum
{
    BLOCK_SIZE = 0x160,
    BLOCK_CLASS = 0x158,
    BLOCK_CLASS_TOKEN = 0x514914,
    BLOCK_TYPE = 0x15d,
    BLOCK_KIND = 0x15c,
    BLOCK_EMPTY_KIND = 0xff,
    RESOURCE_BASE = 0x544ac0,
    RESOURCE_STRIDE = 28,
    STEP_DRAW_LIMIT = 10,
    ATTACH_RESOURCE = 0xb0,
    ATTACH_FRAME = 0xb8,
    ATTACH_CC = 0xcc,
    INIT_X = 8,
    INIT_Y = 0xa,
    INIT_Z = 0xc,
    INIT_X_COPY = 0xe,
    INIT_Y_COPY = 0x16,
    INIT_Z_COPY = 0x1e,
    INIT_BANK = 0xb0,
    INIT_FRAME = 0xb8,
    INIT_IMAGE = 0xb4,
    INIT_HANDLER = 0x154
};

int vertrix_actor_attach_resource(void *actor, size_t size, uint32_t resource)
{
    uint32_t probe;
    return vertrix_actor_storage_read(actor, size, ATTACH_RESOURCE, 4, &probe) &&
           vertrix_actor_storage_write(actor, size, ATTACH_CC, 4, 0) &&
           vertrix_actor_storage_write(actor, size, ATTACH_FRAME, 4, 0) &&
           vertrix_actor_storage_write(actor, size, ATTACH_RESOURCE, 4, resource);
}

int vertrix_actor_initialize(void *actor, size_t size, uint16_t x, uint16_t y, uint16_t z,
                             uint32_t bank, uint32_t frame, uint32_t image, uint32_t handler)
{
    uint32_t probe;
    return vertrix_actor_storage_read(actor, size, INIT_HANDLER, 4, &probe) &&
           vertrix_actor_storage_write(actor, size, INIT_X, 2, x) &&
           vertrix_actor_storage_write(actor, size, INIT_Y, 2, y) &&
           vertrix_actor_storage_write(actor, size, INIT_Z, 2, z) &&
           vertrix_actor_storage_write(actor, size, INIT_X_COPY, 2, x) &&
           vertrix_actor_storage_write(actor, size, INIT_Y_COPY, 2, y) &&
           vertrix_actor_storage_write(actor, size, INIT_Z_COPY, 2, z) &&
           vertrix_actor_storage_write(actor, size, INIT_BANK, 4, bank) &&
           vertrix_actor_storage_write(actor, size, INIT_FRAME, 4, frame) &&
           vertrix_actor_storage_write(actor, size, INIT_IMAGE, 4, image) &&
           vertrix_actor_storage_write(actor, size, INIT_HANDLER, 4, handler);
}

int vertrix_block_construct(void *storage, size_t size)
{
    if (!storage || size < BLOCK_SIZE || !vertrix_actor_storage_construct(storage, size))
    {
        return 0;
    }
    return vertrix_actor_storage_write(storage, size, BLOCK_CLASS, 4, BLOCK_CLASS_TOKEN) &&
           vertrix_actor_storage_write(storage, size, BLOCK_TYPE, 1, 0) &&
           vertrix_actor_storage_write(storage, size, BLOCK_KIND, 1, BLOCK_EMPTY_KIND);
}

int vertrix_block_construct_kind_one(void *storage, size_t size)
{
    if (!storage || size < BLOCK_SIZE || !vertrix_actor_storage_construct(storage, size))
    {
        return 0;
    }
    return vertrix_actor_storage_write(storage, size, BLOCK_CLASS, 4, 0x514b14) &&
           vertrix_actor_storage_write(storage, size, BLOCK_KIND, 1, 1) &&
           vertrix_actor_storage_write(storage, size, BLOCK_TYPE, 1, 0) &&
           vertrix_actor_storage_write(storage, size, 0x94, 1, 0) &&
           vertrix_actor_storage_write(storage, size, 0x95, 1, 3);
}

int vertrix_block_create(uint8_t kind, uint32_t d0, uint32_t steps, uint32_t handler,
                         const VertrixFactoryServices *services, uint32_t *handle)
{
    void *storage;
    size_t size;
    uint32_t block = services->allocate(BLOCK_SIZE, services->context);
    if (block == 0 || !services->resolve(block, &storage, &size, services->context) ||
        !vertrix_block_construct(storage, size) ||
        !vertrix_actor_initialize(storage, size, 0, 0, 0, 0, 0, 0, handler) ||
        !vertrix_actor_set_d0(storage, size, d0) ||
        !vertrix_actor_set_period_steps(storage, size, steps) ||
        !vertrix_actor_attach_resource(
            storage, size, RESOURCE_BASE + (uint32_t)((int32_t)(int8_t)kind * RESOURCE_STRIDE)) ||
        !vertrix_actor_storage_write(storage, size, BLOCK_KIND, 1, kind))
    {
        return 0;
    }
    *handle = block;
    return 1;
}

int vertrix_block_spawn(const void *board, size_t board_size, uint32_t index,
                        const VertrixFactoryServices *services, uint32_t *handle)
{
    void *storage;
    size_t size;
    uint32_t lo, hi;
    if (!services->range(index, &lo, &hi, services->context))
    {
        return 0;
    }
    uint32_t steps = (uint32_t)services->draw(STEP_DRAW_LIMIT, services->context) + 1;
    uint16_t divisor = (uint16_t)(hi - lo + 1);
    uint32_t delay = (uint32_t)(services->draw(divisor, services->context) & 0xffff) + lo;
    uint32_t block;
    if (!vertrix_block_create((uint8_t)index, delay, steps, 0, services, &block) ||
        !services->resolve(block, &storage, &size, services->context) ||
        !vertrix_board_set_actor_clip(board, board_size, storage, size))
    {
        return 0;
    }
    *handle = block;
    return 1;
}
