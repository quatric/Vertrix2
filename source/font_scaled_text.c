#include "font_draw.h"
#include "render_geometry.h"
#include <stdlib.h>

int vertrix_font_draw_text_scaled(const VertrixFontBank *bank, const VertrixFontMap *map,
                                  const uint8_t *text, size_t storage, int16_t x, int16_t y,
                                  uint8_t mode, uint8_t screen_override, uint8_t screen_unscaled,
                                  uint8_t screen_mode, VertrixSurface *target, size_t *drawn,
                                  int16_t *final_x)
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
    uint8_t effective = screen_override ? (screen_unscaled ? 16 : screen_mode) : mode;
    size_t count;
    int16_t end;
    int success = 0;
    if (!vertrix_font_run_scaled(bank, map, text, storage, x, y, mode, screen_override,
                                 screen_unscaled, screen_mode, placements, length, &count, &end))
    {
        goto done;
    }
    for (size_t i = 0; i < count; i++)
    {
        const VertrixImage *image = &bank->glyphs[placements[i].descriptor];
        VertrixFontGlyphBounds bounds;
        if (image->width > 1024 || image->height > 1024 ||
            !vertrix_font_glyph_bounds(bank, &placements[i], effective, &bounds))
        {
            goto done;
        }
        VertrixSpriteClip clipped;
        VertrixBoardClip unused = {0};
        if (vertrix_sprite_clip_mode(bounds.x, bounds.y, bounds.width, bounds.height, 0,
                                     (uint16_t)target->width, (uint16_t)target->height, unused,
                                     unused, &clipped))
        {
            int32_t columns = (int32_t)clipped.bounds.left - bounds.x;
            int32_t rows = (int32_t)clipped.bounds.top - bounds.y;
            if (columns < 0 || rows < 0 || columns > 1024 || rows > 1024 ||
                clipped.bounds.left < 0 || clipped.bounds.top < 0 ||
                (uint32_t)columns + clipped.width > bounds.width ||
                (uint32_t)rows + clipped.height > bounds.height)
            {
                goto done;
            }
        }
    }
    size_t rendered = 0;
    for (size_t i = 0; i < count; i++)
    {
        int result = vertrix_font_draw_glyph_scaled(bank, &placements[i], effective, target);
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
