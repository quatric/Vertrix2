#include "game_text.h"

#include "font_stencils.h"
#include "text_layout.h"

#include <string.h>

enum
{
    SCALE_FULL = 16
};

int vertrix_game_text_load(VertrixGameText *text, VertrixVf *archive, const uint32_t masks[3])
{
    VertrixFontStencils stencils = {0};
    int ok = text && vertrix_font_bank_load(archive, masks, &text->bank);
    if (!ok)
    {
        return 0;
    }
    /* 0x43fc50 sizes fonts 7..9 from the stencil resources 6 and 9 (Circle.spr). */
    ok = vertrix_font_stencils_load(archive, masks, &stencils);
    for (size_t font = 0; ok && font < VERTRIX_TEXT_FONTS; font++)
    {
        ok = vertrix_font_map_construct(&text->maps[font]);
    }
    ok = ok &&
         vertrix_font_maps_initialize(text->maps, VERTRIX_TEXT_FONTS, stencils.frame6.image.width,
                                      stencils.frame6.image.height, stencils.frame9.image.width,
                                      stencils.frame9.image.height);
    vertrix_font_stencils_free(&stencils);
    if (!ok)
    {
        vertrix_font_bank_free(&text->bank);
    }
    return ok;
}

void vertrix_game_text_free(VertrixGameText *text)
{
    if (text)
    {
        vertrix_font_bank_free(&text->bank);
        memset(text, 0, sizeof *text);
    }
}

int vertrix_game_text_place(const VertrixGameText *text, unsigned font, const char *string,
                            int16_t left, int16_t right, int16_t top, int16_t bottom,
                            VertrixFontPlacement *placements, size_t capacity)
{
    uint32_t width, height;
    int16_t x, y;
    size_t count = 0;
    int16_t final_x;
    size_t storage = strlen(string) + 1;
    if (!text || font >= VERTRIX_TEXT_FONTS ||
        !vertrix_font_bank_measure(&text->bank, &text->maps[font], (const uint8_t *)string, storage,
                                   SCALE_FULL, 0, 0, &width, &height) ||
        !vertrix_text_layout((int16_t)width, (int16_t)height, left, right, top, bottom, &x, &y) ||
        !vertrix_font_run_scaled(&text->bank, &text->maps[font], (const uint8_t *)string, storage,
                                 x, y, SCALE_FULL, 0, 0, 0, placements, capacity, &count, &final_x))
    {
        return -1;
    }
    return (int)count;
}
