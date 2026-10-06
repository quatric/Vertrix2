#include "render_geometry.h"
#include "render_tables.h"
#include "scale_tables.h"

static int16_t word(int32_t value)
{
    uint32_t bits = (uint32_t)value & 65535;
    return (int16_t)(bits < 32768 ? (int32_t)bits : (int32_t)bits - 65536);
}

int vertrix_resource_measure(uint16_t width, uint16_t height, uint8_t mode, int32_t *measured_width,
                             int32_t *measured_height)
{
    if (mode > 16 || !measured_width || !measured_height)
    {
        return 0;
    }
    uint32_t x = width;
    uint32_t y = height;
    if (mode != 16)
    {
        x = (width >> 4) * mode + resource_remainder[mode][width & 15];
        y = (height >> 4) * mode + resource_remainder[mode][height & 15];
    }
    *measured_width = word((int32_t)x);
    *measured_height = word((int32_t)y);
    return 1;
}

VertrixBoardClip vertrix_board_clip(int16_t origin_x, int16_t origin_y)
{
    return (VertrixBoardClip){origin_x, word((int32_t)origin_x + 119), origin_y,
                              word((int32_t)origin_y + 311)};
}

int vertrix_board_cell_center(int16_t cell_x, int16_t cell_y, int32_t width, int32_t height,
                              int16_t *x, int16_t *y)
{
    if (!x || !y)
    {
        return 0;
    }
    uint32_t centered_x = (uint32_t)(int32_t)cell_x + ((24u - (uint32_t)width) >> 1);
    uint32_t centered_y = (uint32_t)(int32_t)cell_y + ((24u - (uint32_t)height) >> 1);
    *x = word((int32_t)(centered_x & 65535));
    *y = word((int32_t)(centered_y & 65535));
    return 1;
}

int vertrix_board_cell_position(int16_t origin_x, int16_t origin_y, uint32_t column, uint32_t row,
                                int8_t offset_x, int8_t offset_y, int16_t *x, int16_t *y)
{
    if (column >= 5 || row >= 13 || !x || !y)
    {
        return 0;
    }
    *x = word((int32_t)origin_x + (int32_t)column * 24 + offset_x);
    *y = word((int32_t)origin_y + (int32_t)row * 24 + offset_y);
    return 1;
}

int vertrix_resource_measure_state(const VertrixResourceDimensions *descriptor,
                                   VertrixResourceDimensions fallback, uint8_t object_mode,
                                   uint8_t screen_override, uint8_t screen_unscaled,
                                   uint8_t screen_mode, int32_t *width, int32_t *height)
{
    VertrixResourceDimensions source = descriptor ? *descriptor : fallback;
    uint8_t mode = object_mode;
    if (screen_override)
    {
        mode = screen_unscaled ? 16 : screen_mode;
    }
    return vertrix_resource_measure(source.width, source.height, mode, width, height);
}

int vertrix_resource_bounds(uint16_t source_width, uint16_t source_height, int16_t anchor_x,
                            int16_t anchor_y, uint8_t mode, int16_t position_x, int16_t position_y,
                            int32_t *x, int32_t *y, int32_t *width, int32_t *height)
{
    if (!x || !y || !width || !height || mode > 16 ||
        (mode != 16 && (!source_width || !source_height)))
    {
        return 0;
    }
    int32_t w, h;
    vertrix_resource_measure(source_width, source_height, mode, &w, &h);
    if (mode != 16)
    {
        anchor_x = word(w * anchor_x / source_width);
        anchor_y = word(h * anchor_y / source_height);
    }
    *x = (int32_t)position_x - anchor_x;
    *y = (int32_t)position_y - anchor_y;
    *width = w;
    *height = h;
    return 1;
}

int vertrix_sprite_clip(int16_t x, int16_t y, uint16_t width, uint16_t height,
                        VertrixBoardClip clip, VertrixSpriteClip *output)
{
    if (!output || !width || !height)
    {
        return 0;
    }
    VertrixSpriteClip result = {
        {x, word((int32_t)x + width - 1), y, word((int32_t)y + height - 1)}, width, height, 0, 0};
    if (x > clip.right || result.bounds.right < clip.left || y > clip.bottom ||
        result.bounds.bottom < clip.top)
    {
        return 0;
    }
    if (y < clip.top)
    {
        result.source_offset += (uint32_t)((int32_t)clip.top - y) * (uint32_t)(int32_t)word(width);
        result.bounds.top = clip.top;
        result.clipped = 1;
    }
    if (x < clip.left)
    {
        result.source_offset += (uint32_t)((int32_t)clip.left - x);
        result.bounds.left = clip.left;
        result.clipped = 1;
    }
    if (result.bounds.bottom > clip.bottom)
    {
        result.bounds.bottom = clip.bottom;
        result.clipped = 1;
    }
    if (result.bounds.right > clip.right)
    {
        result.bounds.right = clip.right;
        result.clipped = 1;
    }
    if (result.clipped)
    {
        result.width = (uint16_t)((int32_t)result.bounds.right - result.bounds.left + 1);
        result.height = (uint16_t)((int32_t)result.bounds.bottom - result.bounds.top + 1);
    }
    if (!result.width || !result.height)
    {
        return 0;
    }
    *output = result;
    return 1;
}

int vertrix_sprite_clip_mode(int16_t x, int16_t y, uint16_t width, uint16_t height, uint8_t mode,
                             uint16_t target_width, uint16_t target_height,
                             VertrixBoardClip object_clip, VertrixBoardClip cached_clip,
                             VertrixSpriteClip *output)
{
    if (!output || !width || !height)
    {
        return 0;
    }
    if (mode == 2)
    {
        *output =
            (VertrixSpriteClip){{x, word((int32_t)x + width - 1), y, word((int32_t)y + height - 1)},
                                width,
                                height,
                                0,
                                0};
        return 1;
    }
    VertrixBoardClip clip = cached_clip;
    if (mode == 0 || mode == 1)
    {
        clip = (VertrixBoardClip){0, word((int32_t)target_width - 1), 0,
                                  word((int32_t)target_height - 1)};
    }
    else if (mode == 3)
    {
        clip = object_clip;
    }
    return vertrix_sprite_clip(x, y, width, height, clip, output);
}

int vertrix_sprite_draw32(const VertrixSurface *source, VertrixSurface *target, int16_t x,
                          int16_t y, uint8_t clip_mode, VertrixBoardClip object_clip,
                          VertrixBoardClip cached_clip, int transparent)
{
    if (!source || !target || source->bytes_per_pixel != 4 || target->bytes_per_pixel != 4 ||
        source->width > 65535 || source->height > 65535 || target->width > 65535 ||
        target->height > 65535)
    {
        return -1;
    }
    VertrixSpriteClip clipped;
    if (!vertrix_sprite_clip_mode(x, y, (uint16_t)source->width, (uint16_t)source->height,
                                  clip_mode, (uint16_t)target->width, (uint16_t)target->height,
                                  object_clip, cached_clip, &clipped))
    {
        return 0;
    }
    int32_t sx = (int32_t)clipped.bounds.left - x;
    int32_t sy = (int32_t)clipped.bounds.top - y;
    if (sx < 0 || sy < 0 || clipped.bounds.left < 0 || clipped.bounds.top < 0)
    {
        return -1;
    }
    if (transparent == 2)
    {
        return vertrix_surface_binary32(source, (uint32_t)sx, (uint32_t)sy, target,
                                        (uint32_t)clipped.bounds.left, (uint32_t)clipped.bounds.top,
                                        clipped.width, clipped.height)
                   ? 1
                   : -1;
    }
    int valid =
        transparent
            ? vertrix_surface_alpha32(source, (uint32_t)sx, (uint32_t)sy, target,
                                      (uint32_t)clipped.bounds.left, (uint32_t)clipped.bounds.top,
                                      clipped.width, clipped.height)
            : vertrix_surface_copy32(source, (uint32_t)sx, (uint32_t)sy, target,
                                     (uint32_t)clipped.bounds.left, (uint32_t)clipped.bounds.top,
                                     clipped.width, clipped.height);
    return valid ? 1 : -1;
}

int vertrix_render_scale_advances(uint8_t mode, uint32_t start, uint32_t count, uint8_t *output)
{
    if (mode < 1 || mode > 15 || start > 1024 || count > 1024 - start || (!output && count))
    {
        return 0;
    }
    for (uint32_t i = 0; i < count; ++i)
    {
        output[i] = scale_advances[mode - 1][start + i];
    }
    return 1;
}

int vertrix_render_scale_clip_offset(uint8_t mode, uint16_t source_width, uint16_t skipped_columns,
                                     uint16_t skipped_rows, uint32_t initial_offset,
                                     uint32_t *output)
{
    if (mode < 1 || mode > 15 || skipped_columns > 1024 || skipped_rows > 1024 || !output)
    {
        return 0;
    }
    uint32_t rows = 0;
    uint32_t columns = 0;
    for (uint32_t i = 0; i < skipped_rows; ++i)
    {
        rows = (rows + scale_advances[mode - 1][i]) & 65535;
    }
    for (uint32_t i = 0; i < skipped_columns; ++i)
    {
        columns += scale_advances[mode - 1][i];
    }
    *output = initial_offset + rows * source_width + columns;
    return 1;
}

static int draw_scaled32(const VertrixSurface *source, VertrixSurface *target, int16_t x, int16_t y,
                         uint8_t scale, uint8_t clip_mode, VertrixBoardClip object_clip,
                         VertrixBoardClip cached_clip, int binary, uint16_t effect)
{
    if (!source || !target || source->bytes_per_pixel != 4 || target->bytes_per_pixel != 4 ||
        !source->width || !source->height || source->width > 65535 || source->height > 65535 ||
        source->stride != source->width * 4 || target->width > 65535 || target->height > 65535 ||
        scale < 1 || scale > 15 ||
        (effect && effect != 1 && (effect < 3 || effect > 8) && (effect < 256 || effect > 356)))
    {
        return -1;
    }
    int32_t width, height;
    vertrix_resource_measure((uint16_t)source->width, (uint16_t)source->height, scale, &width,
                             &height);
    if (width < 0 || height < 0)
    {
        return -1;
    }
    VertrixSpriteClip clipped;
    if (!vertrix_sprite_clip_mode(x, y, (uint16_t)width, (uint16_t)height, clip_mode,
                                  (uint16_t)target->width, (uint16_t)target->height, object_clip,
                                  cached_clip, &clipped))
    {
        return 0;
    }
    int32_t columns = (int32_t)clipped.bounds.left - x;
    int32_t rows = (int32_t)clipped.bounds.top - y;
    if (columns < 0 || rows < 0 || columns > 1024 || rows > 1024 || clipped.bounds.left < 0 ||
        clipped.bounds.top < 0)
    {
        return -1;
    }
    uint8_t horizontal[1024];
    uint8_t vertical[1024];
    uint32_t offset;
    if (!vertrix_render_scale_advances(scale, (uint32_t)columns, clipped.width, horizontal) ||
        !vertrix_render_scale_advances(scale, (uint32_t)rows, clipped.height, vertical) ||
        !vertrix_render_scale_clip_offset(scale, (uint16_t)source->width, (uint16_t)columns,
                                          (uint16_t)rows, 0, &offset))
    {
        return -1;
    }
    if (effect >= 256)
    {
        return vertrix_surface_sample_weighted32(
                   source, offset % source->width, offset / source->width, target,
                   (uint32_t)clipped.bounds.left, (uint32_t)clipped.bounds.top, horizontal,
                   clipped.width, vertical, clipped.height, clipped.width, clipped.height,
                   (uint8_t)(effect - 256), binary)
                   ? 1
                   : -1;
    }
    if (effect)
    {
        return vertrix_surface_sample_effect32(
                   source, offset % source->width, offset / source->width, target,
                   (uint32_t)clipped.bounds.left, (uint32_t)clipped.bounds.top, horizontal,
                   clipped.width, vertical, clipped.height, clipped.width, clipped.height, effect,
                   binary)
                   ? 1
                   : -1;
    }
    if (binary)
    {
        return vertrix_surface_sample_binary32(
                   source, offset % source->width, offset / source->width, target,
                   (uint32_t)clipped.bounds.left, (uint32_t)clipped.bounds.top, horizontal,
                   clipped.width, vertical, clipped.height, clipped.width, clipped.height)
                   ? 1
                   : -1;
    }
    return vertrix_surface_sample32(source, offset % source->width, offset / source->width, target,
                                    (uint32_t)clipped.bounds.left, (uint32_t)clipped.bounds.top,
                                    horizontal, clipped.width, vertical, clipped.height,
                                    clipped.width, clipped.height)
               ? 1
               : -1;
}

int vertrix_sprite_draw_scaled32(const VertrixSurface *source, VertrixSurface *target, int16_t x,
                                 int16_t y, uint8_t scale, uint8_t clip_mode,
                                 VertrixBoardClip object_clip, VertrixBoardClip cached_clip)
{
    return draw_scaled32(source, target, x, y, scale, clip_mode, object_clip, cached_clip, 0, 0);
}

int vertrix_sprite_draw_scaled_binary32(const VertrixSurface *source, VertrixSurface *target,
                                        int16_t x, int16_t y, uint8_t scale, uint8_t clip_mode,
                                        VertrixBoardClip object_clip, VertrixBoardClip cached_clip)
{
    return draw_scaled32(source, target, x, y, scale, clip_mode, object_clip, cached_clip, 1, 0);
}

int vertrix_sprite_draw_scaled_effect32(const VertrixSurface *source, VertrixSurface *target,
                                        int16_t x, int16_t y, uint8_t scale, uint8_t clip_mode,
                                        VertrixBoardClip object_clip, VertrixBoardClip cached_clip,
                                        uint8_t effect, int binary)
{
    if (effect != 1 && (effect < 3 || effect > 8))
    {
        return -1;
    }
    return draw_scaled32(source, target, x, y, scale, clip_mode, object_clip, cached_clip, binary,
                         effect);
}

int vertrix_sprite_draw_scaled_weighted32(const VertrixSurface *source, VertrixSurface *target,
                                          int16_t x, int16_t y, uint8_t scale, uint8_t clip_mode,
                                          VertrixBoardClip object_clip,
                                          VertrixBoardClip cached_clip, uint8_t amount, int binary)
{
    if (amount > 100)
    {
        return -1;
    }
    if (amount == 0)
    {
        return 0;
    }
    return draw_scaled32(source, target, x, y, scale, clip_mode, object_clip, cached_clip, binary,
                         (uint16_t)(256 + amount));
}

VertrixRenderBinding vertrix_render_binding(uint32_t source_base, uint32_t source_offset,
                                            uint16_t source_width, uint16_t target_width,
                                            uint16_t visible_width, uint32_t target_stride,
                                            uint32_t extra_padding, uint8_t bytes_per_pixel)
{
    int32_t width = word(target_width);
    int32_t padding = width - word(visible_width);
    return (VertrixRenderBinding){source_base + source_offset * 4,
                                  source_width,
                                  width,
                                  padding,
                                  target_stride,
                                  (uint32_t)padding * bytes_per_pixel + extra_padding};
}
