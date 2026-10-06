#include "display_object.h"
#include "guest_bytes.h"
#include <string.h>

enum
{
    HEAD_OFFSET = 0xc,
    NEXT_OFFSET = 0x60,
    NODE_KEY_OFFSET = 8,
    KEY_OFFSET = 0xa4,
    KEY_SIZE = 16,
    NODE_SIZE = 0x64,
    READY_STORAGE = 0x14,
    PAIR_FIRST = 4,
    PAIR_SECOND = 8,
    SLOT_RELEASE = 2,
    SLOT_NOTIFY = 8,
    INTERFACE_OFFSET = 0x1bc,
    VALUE_OFFSET = 0x1c0
};

static int node_bytes(uint32_t handle, VertrixObjectStorage resolve, void *context,
                      const uint8_t **bytes)
{
    void *storage;
    size_t size;
    if (!resolve(handle, &storage, &size, context) || size < NODE_SIZE)
    {
        return 0;
    }
    *bytes = storage;
    return 1;
}

int vertrix_display_chain_count(const uint8_t *object, size_t size, VertrixObjectStorage resolve,
                                void *context, uint32_t *count)
{
    if (!object || size < HEAD_OFFSET + 4)
    {
        return 0;
    }
    uint32_t total = 0;
    uint32_t node = vertrix_guest_get32(object, HEAD_OFFSET);
    while (node != 0)
    {
        const uint8_t *bytes;
        if (!node_bytes(node, resolve, context, &bytes))
        {
            return 0;
        }
        node = vertrix_guest_get32(bytes, NEXT_OFFSET);
        total += 1;
    }
    *count = total;
    return 1;
}

int vertrix_display_chain_find(const uint8_t *object, size_t size, VertrixObjectStorage resolve,
                               void *context, uint32_t *handle, uint32_t *index)
{
    if (!object || size < KEY_OFFSET + KEY_SIZE)
    {
        return 0;
    }
    uint32_t found = 0;
    uint32_t position = 0xffffffffu;
    uint32_t node = vertrix_guest_get32(object, HEAD_OFFSET);
    for (uint32_t i = 0; node != 0; ++i)
    {
        const uint8_t *bytes;
        if (!node_bytes(node, resolve, context, &bytes))
        {
            return 0;
        }
        if (memcmp(object + KEY_OFFSET, bytes + NODE_KEY_OFFSET, KEY_SIZE) == 0)
        {
            found = node;
            position = i;
            break;
        }
        node = vertrix_guest_get32(bytes, NEXT_OFFSET);
    }
    *handle = found;
    *index = position;
    return 1;
}

int vertrix_display_ready(const uint8_t *object, size_t size)
{
    if (!object || size < READY_STORAGE)
    {
        return 0;
    }
    return vertrix_guest_get32(object, 0) != 0 && vertrix_guest_get32(object, 0x10) != 0;
}

int vertrix_display_release_pair(uint8_t *object, size_t size, VertrixVirtualCall call,
                                 void *context)
{
    if (!object || size < 0xc)
    {
        return 0;
    }
    static const uint8_t fields[2] = {PAIR_FIRST, PAIR_SECOND};
    for (int i = 0; i < 2; ++i)
    {
        uint32_t handle = vertrix_guest_get32(object, fields[i]);
        if (handle != 0)
        {
            call(context, handle, SLOT_RELEASE, handle);
            vertrix_guest_set32(object, fields[i], 0);
        }
    }
    return 1;
}

int vertrix_display_notify(const uint8_t *object, size_t size, uint32_t mode,
                           VertrixDisplayCall call, void *context)
{
    if (!object || size < VALUE_OFFSET + 4)
    {
        return 0;
    }
    uint32_t handle = vertrix_guest_get32(object, INTERFACE_OFFSET);
    uint32_t value = vertrix_guest_get32(object, VALUE_OFFSET);
    if (handle != 0 && value != 0)
    {
        call(context, handle, SLOT_NOTIFY, value, mode, 0);
    }
    return 1;
}
