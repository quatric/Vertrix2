#include "actor_render_geometry.h"
#include <string.h>

int vertrix_actor_render_geometry(const void *storage, size_t size, const VertrixSpriteFrame *frame,
                                  uint16_t target_width, uint16_t target_height,
                                  VertrixBoardClip cached_clip, VertrixActorRenderGeometry *output)
{
    if (!storage || size < VERTRIX_ACTOR_BASE_SIZE || !frame || !output ||
        frame->image.width > 65535 || frame->image.height > 65535)
    {
        return -1;
    }
    uint8_t direct[VERTRIX_ACTOR_BASE_SIZE];
    memcpy(direct, storage, sizeof(direct));
    direct[0x91] = 0;
    VertrixActorRenderGeometry result = {0};
    result.scale = direct[0x44];
    if (!vertrix_actor_image_bounds(direct, sizeof(direct), &frame->image, frame->metadata[3],
                                    frame->metadata[4], 0, 16, &result.bounds))
    {
        return -1;
    }
    uint32_t displacement;
    vertrix_actor_storage_read(direct, sizeof(direct), 0x1e, 2, &displacement);
    uint32_t y = ((uint32_t)result.bounds.y - displacement) & 65535u;
    result.bounds.y = y < 32768u ? (int32_t)y : (int32_t)y - 65536;
    if (!result.bounds.width || !result.bounds.height)
    {
        return 0;
    }
    int visible = vertrix_actor_image_clip(direct, sizeof(direct), &result.bounds, target_width,
                                           target_height, cached_clip, &result.clip);
    if (visible != 1)
    {
        return visible;
    }
    if (!vertrix_actor_image_clip_offset(&result.bounds, &result.clip, (uint16_t)frame->image.width,
                                         result.scale, &result.source_offset))
    {
        return -1;
    }
    *output = result;
    return 1;
}
