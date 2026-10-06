#include "ui_companion_actor.h"
#include "actor_style_storage.h"
#include "ui_actor_storage.h"

enum
{
    COMPANION_SIZE = 0x15c,
    COMPANION_ALLOCATE = 0x4ca000,
    COMPANION_GATE_OFFSET = 0x5cc,
    COMPANION_RECORD_STRIDE = 12,
    COMPANION_SENTINEL_FLAG = 0x110,
    COMPANION_LIST = 0x54671c,
    COMPANION_APPEND = 0x4b5e70
};

int vertrix_ui_companion_actor_construct(void *storage, size_t size, int16_t x, int16_t y,
                                         uint32_t linked_identity, uint32_t source, size_t index)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || index >= 3)
    {
        return 0;
    }
    vertrix_actor_storage_construct(storage, size);
    const size_t x_offsets[2] = {8, 0xe};
    const size_t y_offsets[2] = {0xa, 0x16};
    for (size_t i = 0; i < 2; ++i)
    {
        vertrix_actor_storage_write(storage, size, x_offsets[i], 2, (uint16_t)x);
        vertrix_actor_storage_write(storage, size, y_offsets[i], 2, (uint16_t)y);
    }
    vertrix_actor_storage_write(storage, size, 0xc, 2, 0);
    vertrix_actor_storage_write(storage, size, 0x1e, 2, 0);
    vertrix_actor_storage_write(storage, size, 0xb0, 4, 0x5449fc);
    vertrix_actor_storage_write(storage, size, 0xb8, 4, source + (uint32_t)index);
    vertrix_actor_storage_write(storage, size, 0xb4, 4, 0);
    vertrix_actor_storage_write(storage, size, 0x154, 4, 0);
    vertrix_actor_storage_write(storage, size, 0xc0, 4, 12);
    vertrix_actor_storage_write(storage, size, 0x4e, 1, 0);
    vertrix_actor_storage_write(storage, size, 0x93, 1, 1);
    vertrix_actor_storage_write(storage, size, 0x48, 2, 0);
    vertrix_actor_storage_write(storage, size, 4, 4, linked_identity);
    vertrix_actor_storage_write(storage, size, 0x134, 4, 0);
    vertrix_actor_storage_write(storage, size, 0x58, 4, (uint32_t)index + 1);
    vertrix_actor_storage_write(storage, size, 0x7c, 4, 0);
    return 1;
}

uint32_t vertrix_ui_companion_spawn(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services, uint16_t x, uint16_t y,
                                    uint32_t frame, uint32_t index, uint32_t sentinel,
                                    const uint8_t *config, size_t config_size)
{
    uint32_t gate;
    uint32_t actor;
    void *storage;
    size_t size;
    if (index > (0xffffffff - COMPANION_GATE_OFFSET - 4) / 4 ||
        COMPANION_GATE_OFFSET + index * 4 + 4 > config_size ||
        index > (0xffffffff - COMPANION_RECORD_STRIDE) / COMPANION_RECORD_STRIDE ||
        index * COMPANION_RECORD_STRIDE + COMPANION_RECORD_STRIDE > config_size)
    {
        return 0;
    }
    gate = (uint32_t)config[COMPANION_GATE_OFFSET + index * 4] |
           ((uint32_t)config[COMPANION_GATE_OFFSET + index * 4 + 1] << 8) |
           ((uint32_t)config[COMPANION_GATE_OFFSET + index * 4 + 2] << 16) |
           ((uint32_t)config[COMPANION_GATE_OFFSET + index * 4 + 3] << 24);
    if (gate != 1)
    {
        return 0;
    }
    actor = vertrix_call(calls, COMPANION_ALLOCATE, COMPANION_SIZE, index, frame, index, 0);
    if (!services->resolve(actor, &storage, &size, services->context) ||
        !vertrix_actor_storage_construct(storage, size) ||
        !vertrix_ui_actor_place(storage, size, (int16_t)x, (int16_t)y, frame) ||
        !vertrix_actor_storage_style(storage, size, config + index * COMPANION_RECORD_STRIDE))
    {
        return 0;
    }
    if (index == sentinel &&
        !vertrix_actor_storage_write(storage, size, COMPANION_SENTINEL_FLAG, 1, 1))
    {
        return 0;
    }
    vertrix_call(calls, COMPANION_APPEND, COMPANION_LIST, actor, actor, sentinel, 0);
    return actor;
}
