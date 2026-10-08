#include "object_list.h"
#include <string.h>

int vertrix_object_list_append(VertrixObjectList *list, uint32_t object)
{
    if (!list || !object || !list->items || list->count >= list->capacity ||
        list->capacity > SIZE_MAX / sizeof(*list->items) || list->count >= INT32_MAX)
    {
        return 0;
    }
    list->items[list->count] = object;
    list->count++;
    return 1;
}

int vertrix_object_list_find(const VertrixObjectList *list, uint32_t id,
                             VertrixObjectState identity, void *context, uint32_t *object)
{
    if (!list || !identity || !object || list->count > list->capacity ||
        list->capacity > SIZE_MAX / sizeof(*list->items) || (list->count && !list->items))
    {
        return 0;
    }
    for (size_t index = 0; index < list->count; ++index)
    {
        uint32_t value;
        if (!list->items[index] || !identity(list->items[index], &value, context))
        {
            return 0;
        }
        if (value == id)
        {
            *object = list->items[index];
            return 1;
        }
    }
    *object = 0;
    return 1;
}

static int list_valid(const VertrixObjectList *list)
{
    if (!list || list->count > list->capacity || list->capacity > SIZE_MAX / sizeof(*list->items) ||
        (list->count && !list->items))
    {
        return 0;
    }
    for (size_t index = 0; index < list->count; index++)
    {
        if (!list->items[index])
        {
            return 0;
        }
    }
    return 1;
}

int vertrix_object_list_update(VertrixObjectList *list, VertrixObjectVisit visit, void *context)
{
    if (!visit || !list_valid(list))
    {
        return 0;
    }
    size_t count = list->count;
    for (size_t index = 0; index < count; index++)
    {
        visit(list->items[index], 0, context);
    }
    return 1;
}

int vertrix_object_list_broadcast(VertrixObjectList *list, unsigned slot, uint32_t edx,
                                  uint32_t ebx, VertrixObjectCall call, void *context)
{
    if (!call || !list_valid(list))
    {
        return 0;
    }
    size_t count = list->count;
    for (size_t index = 0; index < count; index++)
    {
        call(list->items[index], slot, edx, ebx, context);
    }
    return 1;
}

int vertrix_object_list_prune(VertrixObjectList *list, uint32_t matching_state,
                              VertrixObjectState state, VertrixObjectVisit visit, void *context)
{
    if (!state || !visit || !list_valid(list))
    {
        return 0;
    }
    size_t index = 0;
    while (index < list->count)
    {
        uint32_t value;
        if (!state(list->items[index], &value, context))
        {
            return 0;
        }
        if (value != matching_state)
        {
            index++;
            continue;
        }
        visit(list->items[index], 2, context);
        size_t remaining = list->count - index - 1;
        if (remaining)
        {
            memmove(list->items + index, list->items + index + 1, remaining * sizeof(*list->items));
        }
        list->count--;
    }
    return 1;
}
