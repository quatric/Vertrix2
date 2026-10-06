#include "object_list_owned.h"
#include <stdlib.h>
#include <string.h>

int vertrix_owned_object_list_resize(VertrixOwnedObjectList *owned, size_t count)
{
    if (!owned || owned->list.count > owned->list.capacity ||
        owned->list.capacity > INT32_MAX / sizeof(uint32_t) ||
        count > INT32_MAX / sizeof(uint32_t) || (owned->list.capacity && !owned->list.items))
    {
        return 0;
    }
    VertrixObjectList *list = &owned->list;
    if (!count)
    {
        free(list->items);
        *list = (VertrixObjectList){0};
        return 1;
    }
    if (list->items && count <= list->capacity)
    {
        if (count > list->count)
        {
            memset(list->items + list->count, 0, (count - list->count) * sizeof(*list->items));
        }
        list->count = count;
        return 1;
    }
    size_t capacity = count;
    if (list->items)
    {
        size_t step = owned->growth_step;
        if (!step)
        {
            step = list->count / 8;
            if (step < 4)
            {
                step = 4;
            }
            if (step > 1024)
            {
                step = 1024;
            }
        }
        if (step > INT32_MAX / sizeof(*list->items) - list->capacity)
        {
            return 0;
        }
        capacity = list->capacity + step;
        if (capacity < count)
        {
            capacity = count;
        }
    }
    uint32_t *items = malloc(capacity * sizeof(*items));
    if (!items)
    {
        return 0;
    }
    if (list->count)
    {
        memcpy(items, list->items, list->count * sizeof(*items));
    }
    memset(items + list->count, 0, (count - list->count) * sizeof(*items));
    free(list->items);
    *list = (VertrixObjectList){items, count, capacity};
    return 1;
}

int vertrix_owned_object_list_append(VertrixOwnedObjectList *owned, uint32_t object)
{
    if (!owned || !object || owned->list.count == SIZE_MAX)
    {
        return 0;
    }
    size_t index = owned->list.count;
    if (!vertrix_owned_object_list_resize(owned, index + 1))
    {
        return 0;
    }
    owned->list.items[index] = object;
    return 1;
}

void vertrix_owned_object_list_free(VertrixOwnedObjectList *owned)
{
    if (!owned)
    {
        return;
    }
    free(owned->list.items);
    memset(owned, 0, sizeof(*owned));
}
