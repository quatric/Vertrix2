#include "font_draw.h"
#include "render_geometry.h"
#include <stdlib.h>

int vertrix_font_glyph_bounds(const VertrixFontBank *bank, const VertrixFontPlacement *placement,
                              uint8_t scale, VertrixFontGlyphBounds *output)
{
    if (!bank || !bank->ready || !placement || placement->descriptor >= 548 || !output ||
        scale > 16)
    {
        return 0;
    }
    uint16_t index = placement->descriptor;
    const VertrixImage *image = &bank->glyphs[index];
    if (!image->rgba || !image->width || !image->height || image->width > 32767 ||
        image->height > 32767)
    {
        return 0;
    }
    int32_t x, y, width, height;
    if (!vertrix_resource_bounds((uint16_t)image->width, (uint16_t)image->height,
                                 (int16_t)(uint16_t)bank->origin_x[index],
                                 (int16_t)(uint16_t)bank->origin_y[index], scale, placement->x,
                                 placement->y, &x, &y, &width, &height))
    {
        return 0;
    }
    VertrixFontGlyphBounds bounds = {(int16_t)(uint16_t)x, (int16_t)(uint16_t)y, (uint16_t)width,
                                     (uint16_t)height};
    *output = bounds;
    return 1;
}

int vertrix_font_draw_glyph_scaled(const VertrixFontBank *bank,
                                   const VertrixFontPlacement *placement, uint8_t scale,
                                   VertrixSurface *target)
{
    VertrixFontGlyphBounds bounds;
    if (!vertrix_font_glyph_bounds(bank, placement, scale, &bounds))
    {
        return -1;
    }
    if (!bounds.width || !bounds.height)
    {
        return 0;
    }
    const VertrixImage *image = &bank->glyphs[placement->descriptor];
    if ((uint64_t)image->width * image->height * 4 > SIZE_MAX)
    {
        return -1;
    }
    VertrixSurface source = {image->rgba,      (size_t)image->width * image->height * 4,
                             image->width,     image->height,
                             image->width * 4, 4};
    VertrixBoardClip unused = {0};
    if (scale == 16)
    {
        return vertrix_sprite_draw32(&source, target, bounds.x, bounds.y, 0, unused, unused, 2);
    }
    return vertrix_sprite_draw_scaled_binary32(&source, target, bounds.x, bounds.y, scale, 0,
                                               unused, unused);
}

int vertrix_font_glyph_position(const VertrixFontBank *bank, uint16_t descriptor, int16_t x,
                                int16_t y, int16_t *draw_x, int16_t *draw_y)
{
    if (!bank || !bank->ready || descriptor >= 548 || !draw_x || !draw_y)
    {
        return 0;
    }
    *draw_x = (int16_t)(uint16_t)((uint16_t)x - (uint16_t)bank->origin_x[descriptor]);
    *draw_y = (int16_t)(uint16_t)((uint16_t)y - (uint16_t)bank->origin_y[descriptor]);
    return 1;
}

int vertrix_font_draw_glyph(const VertrixFontBank *bank, const VertrixFontPlacement *placement,
                            VertrixSurface *target)
{
    int16_t x, y;
    if (!placement || !vertrix_font_glyph_position(bank, placement->descriptor, placement->x,
                                                   placement->y, &x, &y))
    {
        return -1;
    }
    const VertrixImage *image = &bank->glyphs[placement->descriptor];
    if (!image->rgba || !image->width || !image->height || image->width > 32767 ||
        image->height > 32767 || image->width > SIZE_MAX / image->height ||
        (size_t)image->width * image->height > SIZE_MAX / 4)
    {
        return -1;
    }
    VertrixSurface source = {image->rgba,      (size_t)image->width * image->height * 4,
                             image->width,     image->height,
                             image->width * 4, 4};
    VertrixBoardClip unused = {0};
    return vertrix_sprite_draw32(&source, target, x, y, 0, unused, unused, 2);
}

int vertrix_font_draw_text(const VertrixFontBank *bank, const VertrixFontMap *map,
                           const uint8_t *text, size_t storage, uint32_t x, int16_t y,
                           VertrixSurface *target, size_t *drawn, uint32_t *final_x)
{
    if (!text || !drawn || !final_x || !target || !target->data || target->bytes_per_pixel != 4 ||
        !target->width || !target->height || target->width > 32767 || target->height > 32767 ||
        (uint64_t)target->width * 4 > target->stride ||
        (uint64_t)(target->height - 1) * target->stride + (uint64_t)target->width * 4 >
            target->size)
    {
        return 0;
    }
    size_t length = 0;
    while (length < storage && text[length])
    {
        length++;
    }
    if (length == storage || length > SIZE_MAX / sizeof(VertrixFontPlacement))
    {
        return 0;
    }
    VertrixFontPlacement *placements = length ? malloc(length * sizeof(*placements)) : NULL;
    if (length && !placements)
    {
        return 0;
    }
    size_t count;
    uint32_t end;
    int success = 0;
    if (!vertrix_font_run(bank, map, text, storage, x, y, placements, length, &count, &end))
    {
        goto done;
    }
    for (size_t i = 0; i < count; i++)
    {
        const VertrixImage *image = &bank->glyphs[placements[i].descriptor];
        int16_t dx, dy;
        VertrixSpriteClip clipped;
        VertrixBoardClip unused = {0};
        if (!image->width || !image->height || image->width > 32767 || image->height > 32767 ||
            image->width > SIZE_MAX / image->height ||
            (size_t)image->width * image->height > SIZE_MAX / 4 ||
            !vertrix_font_glyph_position(bank, placements[i].descriptor, placements[i].x,
                                         placements[i].y, &dx, &dy))
        {
            goto done;
        }
        if (vertrix_sprite_clip_mode(dx, dy, (uint16_t)image->width, (uint16_t)image->height, 0,
                                     (uint16_t)target->width, (uint16_t)target->height, unused,
                                     unused, &clipped))
        {
            int32_t sx = (int32_t)clipped.bounds.left - dx;
            int32_t sy = (int32_t)clipped.bounds.top - dy;
            if (sx < 0 || sy < 0 || clipped.bounds.left < 0 || clipped.bounds.top < 0 ||
                (uint64_t)sx + clipped.width > image->width ||
                (uint64_t)sy + clipped.height > image->height)
            {
                goto done;
            }
        }
    }
    size_t rendered = 0;
    for (size_t i = 0; i < count; i++)
    {
        int result = vertrix_font_draw_glyph(bank, &placements[i], target);
        if (result < 0)
        {
            goto done;
        }
        rendered += result != 0;
    }
    *drawn = rendered;
    *final_x = end;
    success = 1;
done:
    free(placements);
    return success;
}
