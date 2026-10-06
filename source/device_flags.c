#include "device_flags.h"
#include <stddef.h>

static int is_open(const VertrixDeviceState *device)
{
    return (device->flags & VERTRIX_DEVICE_OPEN_BIT) != 0;
}

uint32_t vertrix_device_mark_dirty(VertrixDeviceState *device)
{
    if (!is_open(device))
    {
        return VERTRIX_DEVICE_CLOSED;
    }
    device->flags &= VERTRIX_DEVICE_MODE_MASK;
    device->flags |= VERTRIX_DEVICE_DIRTY_BIT;
    return VERTRIX_DEVICE_OK;
}

uint32_t vertrix_device_set_limit(VertrixDeviceState *device, uint32_t limit)
{
    if (!is_open(device))
    {
        return VERTRIX_DEVICE_CLOSED;
    }
    if (limit > VERTRIX_DEVICE_MAX_LIMIT)
    {
        return VERTRIX_DEVICE_INVALID;
    }
    device->limit = limit;
    if ((device->flags & VERTRIX_DEVICE_LOCKED_BIT) == 0)
    {
        device->flags |= VERTRIX_DEVICE_DIRTY_BIT;
    }
    return VERTRIX_DEVICE_OK;
}

uint32_t vertrix_device_set_pair(VertrixDeviceState *device, uint32_t first, uint32_t second)
{
    if (!is_open(device))
    {
        return VERTRIX_DEVICE_CLOSED;
    }
    device->first = first;
    device->second = second;
    device->flags |= VERTRIX_DEVICE_PARAMS_BIT;
    return VERTRIX_DEVICE_OK;
}

uint32_t vertrix_device_get_values(const VertrixDeviceState *device, uint32_t *first,
                                   uint32_t *second)
{
    if (!is_open(device))
    {
        return VERTRIX_DEVICE_CLOSED;
    }
    if (first == NULL || second == NULL)
    {
        return VERTRIX_DEVICE_INVALID;
    }
    *first = device->value5c;
    *second = device->value50;
    return VERTRIX_DEVICE_OK;
}

uint32_t vertrix_device_get_locked(const VertrixDeviceState *device, uint32_t *locked)
{
    if (!is_open(device))
    {
        return VERTRIX_DEVICE_CLOSED;
    }
    if (locked == NULL)
    {
        return VERTRIX_DEVICE_INVALID;
    }
    *locked = (device->flags & VERTRIX_DEVICE_LOCKED_BIT) != 0;
    return VERTRIX_DEVICE_OK;
}

uint32_t vertrix_device_lock(VertrixDeviceState *device, const uint32_t *items,
                             VertrixDeviceLockItem lock_item, void *context)
{
    if (!is_open(device))
    {
        return VERTRIX_DEVICE_CLOSED;
    }
    device->flags |= VERTRIX_DEVICE_LOCKED_BIT;
    for (int32_t i = 0; i < device->count; ++i)
    {
        lock_item(items[i], 0, context);
    }
    return VERTRIX_DEVICE_OK;
}
