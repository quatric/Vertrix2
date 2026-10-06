#ifndef VERTRIX_GAME_TEXT_H
#define VERTRIX_GAME_TEXT_H
#include "font_binding.h"
#include "font_run.h"
#include "vf.h"

enum
{
    VERTRIX_TEXT_FONTS = 19
};

/* The original's text system: the 548 glyph resources of 0x43eab0 and the 19 font maps 0x43fc50
 * builds at 0x541988 (+ id * 0x20c). Fonts 4, 16, 17 and 18 are the big game digits and their
 * stencil layers, 6 is FontGame_7. */
typedef struct
{
    VertrixFontBank bank;
    VertrixFontMap maps[VERTRIX_TEXT_FONTS];
} VertrixGameText;

/* masks are the graphics color masks of the frame the glyphs are drawn into. text must be zero
 * initialized. */
int vertrix_game_text_load(VertrixGameText *text, VertrixVf *archive, const uint32_t masks[3]);
void vertrix_game_text_free(VertrixGameText *text);

/* Where a text of the given font is placed inside the inclusive box (0x4408e0: measure with
 * 0x440610, then center with 0x440990) and the glyph placements (0x440a20). Returns the number of
 * glyphs, or -1 when the text cannot be measured. */
int vertrix_game_text_place(const VertrixGameText *text, unsigned font, const char *string,
                            int16_t left, int16_t right, int16_t top, int16_t bottom,
                            VertrixFontPlacement *placements, size_t capacity);

#endif
