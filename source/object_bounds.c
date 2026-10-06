#include "object_bounds.h"

#include "actor_storage.h"

enum
{
    DWORD_WIDTH = 4,
    FIXED_SHIFT = 16,
    OBJECT_LEFT = 0xc,
    OBJECT_TOP = 0x14,
    OBJECT_WIDTH = 0xf4,
    OBJECT_HEIGHT = 0xf8,
    OBJECT_LEFT_INSET_OWNER = 0x17c,
    OBJECT_RIGHT_INSET_OWNER = 0x180,
    OWNER_INSET_RECORD = 0xb4,
    RECORD_INSET = 4
};

static int read_field(const VertrixFactoryServices *services, uint32_t handle, uint32_t offset,
                      uint32_t *value)
{
    void *storage;
    size_t size;
    return services->resolve(handle, &storage, &size, services->context) &&
           vertrix_actor_storage_read(storage, size, offset, DWORD_WIDTH, value);
}

static int read_inset(const VertrixFactoryServices *services, uint32_t object, uint32_t owner_field,
                      uint32_t *inset)
{
    uint32_t owner;
    uint32_t record;
    return read_field(services, object, owner_field, &owner) &&
           read_field(services, owner, OWNER_INSET_RECORD, &record) &&
           read_field(services, record, RECORD_INSET, inset);
}

uint32_t vertrix_object_contains_point(const VertrixFactoryServices *services, uint32_t object,
                                       int32_t x, int32_t y)
{
    uint32_t left_raw, top_raw, width, height, left_inset, right_inset;
    int32_t left, top, right, bottom;
    if (!read_inset(services, object, OBJECT_LEFT_INSET_OWNER, &left_inset) ||
        !read_inset(services, object, OBJECT_RIGHT_INSET_OWNER, &right_inset) ||
        !read_field(services, object, OBJECT_LEFT, &left_raw) ||
        !read_field(services, object, OBJECT_TOP, &top_raw) ||
        !read_field(services, object, OBJECT_WIDTH, &width) ||
        !read_field(services, object, OBJECT_HEIGHT, &height))
    {
        return 0;
    }
    left = (int32_t)left_raw >> FIXED_SHIFT;
    top = (int32_t)top_raw >> FIXED_SHIFT;
    right = (int32_t)(width + (uint32_t)left - right_inset) - 1;
    bottom = (int32_t)(height + (uint32_t)top) - 1;
    return x >= (int32_t)(left_inset + (uint32_t)left) && y >= top && x <= right && y <= bottom;
}
