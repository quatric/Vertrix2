#include "font_binding.h"
#include "font_measure.h"

int vertrix_font_bank_glyph(const VertrixFontBank *bank, const VertrixFontMap *map, uint8_t glyph,
                            const VertrixImage **output)
{
    if (!bank || !bank->ready || !map || !output)
    {
        return 0;
    }
    int16_t index = map->glyphs[glyph];
    if (index == -1)
    {
        *output = NULL;
        return 1;
    }
    if (index < 0 || index >= 548 || !bank->glyphs[index].rgba)
    {
        return 0;
    }
    *output = &bank->glyphs[index];
    return 1;
}

typedef struct
{
    const VertrixFontBank *bank;
    const VertrixFontMap *map;
} FontBinding;

static int glyph_dimensions(uint8_t glyph, VertrixResourceDimensions *dimensions, void *context)
{
    const FontBinding *binding = context;
    const VertrixImage *image;
    if (!vertrix_font_bank_glyph(binding->bank, binding->map, glyph, &image))
    {
        return -1;
    }
    if (!image)
    {
        return 0;
    }
    dimensions->width = (uint16_t)image->width;
    dimensions->height = (uint16_t)image->height;
    return 1;
}

int vertrix_font_bank_measure(const VertrixFontBank *bank, const VertrixFontMap *map,
                              const uint8_t *text, size_t storage, uint8_t mode,
                              uint8_t screen_unscaled, uint8_t screen_mode, uint32_t *width,
                              uint32_t *height)
{
    if (!bank || !bank->ready || !map)
    {
        return 0;
    }
    FontBinding binding = {bank, map};
    VertrixResourceDimensions space = {(uint16_t)map->space_width, (uint16_t)map->space_height};
    return vertrix_font_measure(text, storage, space, mode, screen_unscaled, screen_mode,
                                glyph_dimensions, &binding, width, height);
}
