#include "frame_resource.h"

int vertrix_frame_resource_get(const VertrixFrameResource *resource, uint32_t index, size_t budget,
                               uint32_t *descriptor)
{
    if (!descriptor)
    {
        return 0;
    }
    while (budget--)
    {
        if (!resource || index >= resource->count)
        {
            return 0;
        }
        if (resource->kind != 1)
        {
            if (!resource->frames)
            {
                return 0;
            }
            *descriptor = resource->frames[index];
            return 1;
        }
        if (!resource->children || !resource->indices)
        {
            return 0;
        }
        const VertrixFrameResource *child = resource->children[index];
        index = resource->indices[index];
        resource = child;
    }
    return 0;
}
