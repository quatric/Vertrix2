#include "render_row.h"
#include <stdlib.h>
#include <string.h>

static uint32_t read32(const uint8_t *pixel)
{
    return (uint32_t)pixel[0] | (uint32_t)pixel[1] << 8 | (uint32_t)pixel[2] << 16 |
           (uint32_t)pixel[3] << 24;
}

static int binary_row32(uint8_t *storage, size_t size, size_t source_offset,
                        size_t destination_offset, uint16_t width, uint32_t flags,
                        const VertrixRenderPreparation *prepared,
                        const VertrixPaletteTables *tables, const uint8_t *advances,
                        size_t advance_count, int sampled, int binary, int copy)
{
    size_t bytes = (size_t)width * 4;
    if (source_offset > size || destination_offset > size ||
        (!sampled && bytes > size - source_offset) || bytes > size - destination_offset ||
        (width && !storage))
    {
        return 0;
    }
    if (!width)
    {
        return !sampled;
    }
    if (sampled)
    {
        if (!advances || advance_count < width)
        {
            return 0;
        }
        size_t cursor = source_offset;
        for (uint32_t column = 0; column < width; ++column)
        {
            size_t step = (size_t)advances[column] * 4;
            if (cursor > size || size - cursor < 4 || step > SIZE_MAX - cursor)
            {
                return 0;
            }
            cursor += step;
        }
    }
    uint8_t *staging = copy ? malloc(size) : storage;
    if (!staging)
    {
        return 0;
    }
    if (copy)
    {
        memcpy(staging, storage, size);
    }
    for (uint32_t column = 0; column < width; ++column)
    {
        uint32_t source = read32(staging + source_offset);
        source_offset += sampled ? (size_t)advances[column] * 4 : 4;
        if (binary && !(source >> 24))
        {
            continue;
        }
        uint8_t *target = staging + destination_offset + column * 4;
        uint32_t result;
        if (binary == 2)
        {
            result = vertrix_surface_alpha_pixel(source, read32(target));
        }
        else if (!vertrix_render_pixel32(flags, source, read32(target), prepared, tables, &result))
        {
            if (copy)
            {
                free(staging);
            }
            return 0;
        }
        for (uint32_t byte = 0; byte < 4; ++byte)
        {
            target[byte] = (uint8_t)(result >> (byte * 8));
        }
    }
    if (copy)
    {
        memcpy(storage, staging, size);
        free(staging);
    }
    return 1;
}

int vertrix_render_binary_row32(uint8_t *storage, size_t size, size_t source_offset,
                                size_t destination_offset, uint16_t width, uint32_t flags,
                                const VertrixRenderPreparation *prepared,
                                const VertrixPaletteTables *tables)
{
    return binary_row32(storage, size, source_offset, destination_offset, width, flags, prepared,
                        tables, NULL, 0, 0, 1, 1);
}

int vertrix_render_row32(uint8_t *storage, size_t size, size_t source_offset,
                         size_t destination_offset, uint16_t width, uint32_t flags,
                         const VertrixRenderPreparation *prepared,
                         const VertrixPaletteTables *tables)
{
    return binary_row32(storage, size, source_offset, destination_offset, width, flags, prepared,
                        tables, NULL, 0, 0, 0, 1);
}

int vertrix_render_sample_binary_row32(uint8_t *storage, size_t size, size_t source_offset,
                                       size_t destination_offset, uint16_t width, uint32_t flags,
                                       const VertrixRenderPreparation *prepared,
                                       const VertrixPaletteTables *tables, const uint8_t *advances,
                                       size_t advance_count)
{
    return binary_row32(storage, size, source_offset, destination_offset, width, flags, prepared,
                        tables, advances, advance_count, 1, 1, 1);
}

int vertrix_render_sample_row32(uint8_t *storage, size_t size, size_t source_offset,
                                size_t destination_offset, uint16_t width, uint32_t flags,
                                const VertrixRenderPreparation *prepared,
                                const VertrixPaletteTables *tables, const uint8_t *advances,
                                size_t advance_count)
{
    return binary_row32(storage, size, source_offset, destination_offset, width, flags, prepared,
                        tables, advances, advance_count, 1, 0, 1);
}

static int image32(uint8_t *storage, size_t size, size_t source_offset, size_t destination_offset,
                   uint32_t source_stride, uint32_t destination_stride, uint16_t width,
                   uint16_t height, uint32_t flags, const VertrixRenderPreparation *prepared,
                   const VertrixPaletteTables *tables, const uint8_t *horizontal,
                   size_t horizontal_count, const uint8_t *vertical, size_t vertical_count,
                   int binary, int sampled)
{
    if (!storage || (sampled && (!width || !height || !horizontal || !vertical ||
                                 horizontal_count < width || vertical_count < height)))
    {
        return 0;
    }
    if (!width || !height)
    {
        return 1;
    }
    uint8_t *staging = malloc(size);
    if (!staging)
    {
        return 0;
    }
    memcpy(staging, storage, size);
    for (uint32_t row = 0; row < height; ++row)
    {
        if (!binary_row32(staging, size, source_offset, destination_offset, width, flags, prepared,
                          tables, horizontal, horizontal_count, sampled, binary, 0))
        {
            free(staging);
            return 0;
        }
        uint64_t step = sampled ? (uint64_t)vertical[row] * source_stride : source_stride;
        if (step > SIZE_MAX - source_offset || destination_stride > SIZE_MAX - destination_offset)
        {
            free(staging);
            return 0;
        }
        source_offset += (size_t)step;
        destination_offset += destination_stride;
    }
    memcpy(storage, staging, size);
    free(staging);
    return 1;
}

int vertrix_render_sample32(uint8_t *storage, size_t size, size_t source_offset,
                            size_t destination_offset, uint32_t source_stride,
                            uint32_t destination_stride, uint16_t width, uint16_t height,
                            uint32_t flags, const VertrixRenderPreparation *prepared,
                            const VertrixPaletteTables *tables, const uint8_t *horizontal,
                            size_t horizontal_count, const uint8_t *vertical, size_t vertical_count,
                            int binary)
{
    return image32(storage, size, source_offset, destination_offset, source_stride,
                   destination_stride, width, height, flags, prepared, tables, horizontal,
                   horizontal_count, vertical, vertical_count, binary != 0, 1);
}

int vertrix_render_image32(uint8_t *storage, size_t size, size_t source_offset,
                           size_t destination_offset, uint32_t source_stride,
                           uint32_t destination_stride, uint16_t width, uint16_t height,
                           uint32_t flags, const VertrixRenderPreparation *prepared,
                           const VertrixPaletteTables *tables, int binary)
{
    return image32(storage, size, source_offset, destination_offset, source_stride,
                   destination_stride, width, height, flags, prepared, tables, NULL, 0, NULL, 0,
                   binary != 0, 0);
}

int vertrix_render_alpha_image32(uint8_t *storage, size_t size, size_t source_offset,
                                 size_t destination_offset, uint32_t source_stride,
                                 uint32_t destination_stride, uint16_t width, uint16_t height)
{
    return image32(storage, size, source_offset, destination_offset, source_stride,
                   destination_stride, width, height, 0, NULL, NULL, NULL, 0, NULL, 0, 2, 0);
}

int vertrix_render_bound32(uint8_t *storage, size_t size, size_t source_offset,
                           size_t destination_offset, const VertrixRenderImageRequest *request,
                           const VertrixRenderPreparation *prepared,
                           const VertrixPaletteTables *tables, const uint8_t *horizontal,
                           size_t horizontal_count, const uint8_t *vertical, size_t vertical_count)
{
    if (!request)
    {
        return 0;
    }
    uint32_t flags = vertrix_render_traversal_flags(request->binary_flag, request->scale,
                                                    request->transform_flag);
    uint32_t index = vertrix_render_traversal_index(flags);
    uint32_t group = vertrix_render_traversal_group(flags & 12u);
    VertrixRenderOperation operation;
    if (!vertrix_render_operation(vertrix_render_rule(request->flags), index, group, 4,
                                  request->alpha_override, &operation) ||
        (group & 1u))
    {
        return 0;
    }
    if (operation.operation_address == 0x4ab380)
    {
        return vertrix_render_alpha_image32(storage, size, source_offset, destination_offset,
                                            request->source_stride, request->destination_stride,
                                            request->width, request->height);
    }
    uint32_t pixel_flags = operation.prepare ? request->flags : 1;
    if (group == 0)
    {
        return vertrix_render_image32(storage, size, source_offset, destination_offset,
                                      request->source_stride, request->destination_stride,
                                      request->width, request->height, pixel_flags, prepared,
                                      tables, request->binary_flag == 1);
    }
    if (group == 2)
    {
        return vertrix_render_sample32(storage, size, source_offset, destination_offset,
                                       request->source_stride, request->destination_stride,
                                       request->width, request->height, pixel_flags, prepared,
                                       tables, horizontal, horizontal_count, vertical,
                                       vertical_count, request->binary_flag == 1);
    }
    return 0;
}

int vertrix_render_prepared32(uint8_t *storage, size_t size, size_t source_offset,
                              size_t destination_offset, const VertrixRenderImageRequest *request,
                              uint32_t pixel_resource, VertrixRenderFlagState state, uint8_t cycle,
                              const VertrixRenderWeights *weights,
                              const VertrixRenderColorBank *bank,
                              const VertrixPaletteTables *tables,
                              VertrixRenderPreparation *prepared, const uint8_t *horizontal,
                              size_t horizontal_count, const uint8_t *vertical,
                              size_t vertical_count)
{
    if (!request || !prepared)
    {
        return 0;
    }
    if (!vertrix_render_pixels_enabled(pixel_resource, request->scale, state))
    {
        return 1;
    }
    VertrixRenderImageRequest resolved = *request;
    resolved.flags = vertrix_render_flags(state, 0);
    uint32_t flags = vertrix_render_traversal_flags(resolved.binary_flag, resolved.scale,
                                                    resolved.transform_flag);
    VertrixRenderOperation operation;
    if (!vertrix_render_operation(
            vertrix_render_rule(resolved.flags), vertrix_render_traversal_index(flags),
            vertrix_render_traversal_group(flags & 12u), 4, resolved.alpha_override, &operation))
    {
        return 0;
    }
    VertrixRenderPreparation result = *prepared;
    if (operation.prepare &&
        !vertrix_render_prepare(state, cycle, weights, bank, tables ? tables->hue : NULL,
                                tables ? 262144 : 0, &result))
    {
        return 0;
    }
    if (!vertrix_render_bound32(storage, size, source_offset, destination_offset, &resolved,
                                &result, tables, horizontal, horizontal_count, vertical,
                                vertical_count))
    {
        return 0;
    }
    *prepared = result;
    return 1;
}
