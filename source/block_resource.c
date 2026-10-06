#include "block_resource.h"

int vertrix_block_resource_last(VertrixAnimation *animation, const VertrixFrameResource *resource)
{
    if (!animation || !resource || resource->count > UINT32_MAX)
    {
        return 0;
    }
    animation->frame_count = (uint32_t)resource->count;
    animation->frame = animation->frame_count - 1u;
    return 1;
}

int vertrix_block_resource_attach(VertrixAnimation *animation,
                                  const VertrixFrameResource **attached,
                                  const VertrixFrameResource *resource)
{
    if (!animation || !attached || (resource && resource->count > UINT32_MAX))
    {
        return 0;
    }
    animation->timer.counter = 0;
    animation->frame = 0;
    animation->frame_count = resource ? (uint32_t)resource->count : 0;
    *attached = resource;
    return 1;
}

int vertrix_block_resource_bind(const VertrixAnimation *animation,
                                const VertrixFrameResource *resource, size_t traversal_budget,
                                uint32_t *descriptor)
{
    if (!animation || !descriptor)
    {
        return 0;
    }
    if (!resource)
    {
        return 1;
    }
    return vertrix_frame_resource_get(resource, animation->frame, traversal_budget, descriptor);
}

int vertrix_block_resource_update(VertrixAnimation *animation, const VertrixFrameResource *resource,
                                  size_t traversal_budget, uint32_t elapsed, uint32_t *descriptor)
{
    if (!animation || !resource || !descriptor || resource->count != animation->frame_count)
    {
        return 0;
    }
    VertrixAnimation next = *animation;
    uint32_t selected;
    if (vertrix_animation_tick(&next, elapsed, VERTRIX_ANIMATION_FORWARD_LOOP) < 0 ||
        !vertrix_frame_resource_get(resource, next.frame, traversal_budget, &selected))
    {
        return 0;
    }
    *animation = next;
    *descriptor = selected;
    return 1;
}
