#include "actor_render_draw.h"
#include "actor_render_style.h"
#include <stdlib.h>
#include <string.h>

int vertrix_actor_render_draw32(const void *storage, size_t size, const VertrixSpriteFrame *frame,
                                VertrixSurface *target, VertrixBoardClip cached_clip,
                                const VertrixRenderWeights *weights,
                                const VertrixRenderColorBank *bank,
                                const VertrixPaletteTables *tables,
                                VertrixRenderPreparation *prepared)
{
    if (!target || !target->data || target->bytes_per_pixel != 4 || target->width > 65535 ||
        target->height > 65535 || !frame || !frame->image.rgba || !prepared ||
        (frame->metadata[9] >> 24) != 4)
    {
        return -1;
    }
    VertrixActorRenderStyle style;
    if (!vertrix_actor_render_style(storage, size, &style) || style.clip_flag)
    {
        return -1;
    }
    VertrixActorRenderGeometry geometry;
    int visible = vertrix_actor_render_geometry(storage, size, frame, (uint16_t)target->width,
                                                (uint16_t)target->height, cached_clip, &geometry);
    if (visible != 1)
    {
        return visible;
    }
    if (geometry.clip.bounds.left < 0 || geometry.clip.bounds.top < 0 ||
        (uint32_t)geometry.clip.bounds.left + geometry.clip.width > target->width ||
        (uint32_t)geometry.clip.bounds.top + geometry.clip.height > target->height)
    {
        return -1;
    }
    uint64_t source_size = (uint64_t)frame->image.width * frame->image.height * 4;
    uint64_t target_offset = (uint64_t)geometry.clip.bounds.top * target->stride +
                             (uint64_t)geometry.clip.bounds.left * 4;
    if (source_size > SIZE_MAX || target_offset > target->size ||
        target->size > SIZE_MAX - (size_t)source_size)
    {
        return -1;
    }
    size_t row_bytes = (size_t)geometry.clip.width * 4;
    uint64_t target_end =
        target_offset + (uint64_t)(geometry.clip.height - 1) * target->stride + row_bytes;
    if (target_end > target->size)
    {
        return -1;
    }
    /* Disjoint destination rows can be staged tightly. Overlapping rows retain
     * the original stride and shared backing so forward traversal stays exact. */
    int compact = target->stride >= row_bytes;
    size_t destination_size = compact ? row_bytes * geometry.clip.height : target->size;
    size_t destination_offset = compact ? 0 : (size_t)target_offset;
    size_t total = (size_t)source_size + destination_size;
    uint8_t *backing = malloc(total);
    uint8_t *horizontal = NULL;
    uint8_t *vertical = NULL;
    if (!backing)
    {
        return -1;
    }
    if (geometry.scale != 16)
    {
        horizontal = malloc(geometry.clip.width);
        vertical = malloc(geometry.clip.height);
        uint16_t columns =
            (uint16_t)((uint32_t)geometry.clip.bounds.left - (uint32_t)geometry.bounds.x);
        uint16_t rows =
            (uint16_t)((uint32_t)geometry.clip.bounds.top - (uint32_t)geometry.bounds.y);
        if (!horizontal || !vertical ||
            !vertrix_render_scale_advances(geometry.scale, columns, geometry.clip.width,
                                           horizontal) ||
            !vertrix_render_scale_advances(geometry.scale, rows, geometry.clip.height, vertical))
        {
            free(horizontal);
            free(vertical);
            free(backing);
            return -1;
        }
    }
    memcpy(backing, frame->image.rgba, (size_t)source_size);
    if (compact)
    {
        for (uint16_t row = 0; row < geometry.clip.height; ++row)
        {
            memcpy(backing + (size_t)source_size + row * row_bytes,
                   target->data + (size_t)target_offset + (size_t)row * target->stride, row_bytes);
        }
    }
    else
    {
        memcpy(backing + (size_t)source_size, target->data, target->size);
    }
    VertrixRenderImageRequest request = {0};
    request.source_stride = frame->image.width * 4;
    request.destination_stride = compact ? (uint32_t)row_bytes : target->stride;
    request.width = geometry.clip.width;
    request.height = geometry.clip.height;
    request.scale = geometry.scale;
    request.binary_flag = (uint8_t)(frame->metadata[9] >> 16);
    uint32_t resource;
    vertrix_actor_storage_read(storage, size, 0x134, 4, &resource);
    vertrix_actor_storage_read(storage, size, 0x150, 4, &request.alpha_override);
    VertrixRenderPreparation result = *prepared;
    int success = vertrix_render_prepared32(
        backing, total, (size_t)geometry.source_offset * 4,
        (size_t)source_size + destination_offset, &request, resource, style.flags, style.cycle,
        weights, bank, tables, &result, horizontal, request.width, vertical, request.height);
    if (success)
    {
        if (compact)
        {
            for (uint16_t row = 0; row < geometry.clip.height; ++row)
            {
                memcpy(target->data + (size_t)target_offset + (size_t)row * target->stride,
                       backing + (size_t)source_size + row * row_bytes, row_bytes);
            }
        }
        else
        {
            memcpy(target->data, backing + (size_t)source_size, target->size);
        }
        *prepared = result;
    }
    free(horizontal);
    free(vertical);
    free(backing);
    return success ? 1 : -1;
}
