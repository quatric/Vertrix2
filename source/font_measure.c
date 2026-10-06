#include "font_measure.h"

int vertrix_font_measure(const uint8_t *text, size_t storage, VertrixResourceDimensions space,
                         uint8_t mode, uint8_t screen_unscaled, uint8_t screen_mode,
                         VertrixGlyphDimensions glyph, void *context, uint32_t *width,
                         uint32_t *height)
{
    if (!text || !storage || !glyph || !width || !height || mode > 16)
    {
        return 0;
    }
    uint32_t measured_width = 0, measured_height = 0;
    for (size_t index = 0; index < storage; ++index)
    {
        uint8_t code = text[index];
        if (!code)
        {
            if (!index)
            {
                int32_t w, h;
                if (!vertrix_resource_measure_state(&space, space, mode, 0, screen_unscaled,
                                                    screen_mode, &w, &h))
                {
                    return 0;
                }
                measured_height = (uint32_t)h;
            }
            *width = measured_width;
            *height = measured_height;
            return 1;
        }
        VertrixResourceDimensions dimensions = space;
        if (code != ' ')
        {
            int found = glyph(code, &dimensions, context);
            if (found < 0)
            {
                return 0;
            }
            if (!found)
            {
                continue;
            }
        }
        int32_t w, h;
        if (!vertrix_resource_measure_state(&dimensions, dimensions, mode, 0, screen_unscaled,
                                            screen_mode, &w, &h))
        {
            return 0;
        }
        measured_width += (uint32_t)w + 1u;
        if ((uint32_t)h > measured_height)
        {
            measured_height = (uint32_t)h;
        }
    }
    return 0;
}
