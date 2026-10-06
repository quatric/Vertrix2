#ifndef VERTRIX_HUD_DRAW_H
#define VERTRIX_HUD_DRAW_H
#include "game_text.h"
#include "gauge_tube.h"
#include "palette_tables.h"
#include "render_color_bank.h"
#include "render_weights.h"
#include "surface.h"
#include "ui_sprite_bank.h"
#include "vf.h"

enum
{
    VERTRIX_HUD_ITEMS = 122,
    VERTRIX_HUD_ITEM_BYTES = 12,
    VERTRIX_HUD_CHARACTERS = 18
};

/* The game screen's damier pieces drawn exactly as the original builder 0x46b810 does: through
 * the recovered actor renderer, styled by the character's Filtre/<name>.flt items. */
typedef struct
{
    VertrixRenderWeights *weights;
    VertrixPaletteTables tables;
    VertrixRenderColorBank bank;
    VertrixUiSpriteBank damier;
    uint8_t items[VERTRIX_HUD_ITEMS][VERTRIX_HUD_ITEM_BYTES];
} VertrixHud;

/* Filtre file name of a character (FiltreFileName.ini order), or NULL. */
const char *vertrix_hud_filter_name(unsigned character);

/* Load the damier frames and the character's filter items. masks is the frame order the pieces
 * are drawn in; the renderer's palette tables expect red 0xff0000, green 0xff00, blue 0xff.
 * hud must be zero initialized. */
int vertrix_hud_load(VertrixHud *hud, VertrixVf *archive, unsigned character);

/* Draw every piece in creation order (fixed pieces, the bonus slot grids of the two players'
 * characters, fixed pieces) onto a 32-bit surface whose pixels are the little-endian dwords
 * 0x00RRGGBB. Returns the number of pieces drawn. */
int vertrix_hud_draw(const VertrixHud *hud, unsigned first, unsigned second,
                     VertrixSurface *target);

void vertrix_hud_free(VertrixHud *hud);

/* The two glow sprites of the level tube beads (builder 0x45e490): the damier bead shape stamped
 * with Circle.spr frame 9 through 0x4831b0, keeping the shape (lit, resource 0x546618) or cutting
 * it out (spent, 0x546634). */
typedef struct
{
    VertrixSpriteFrame lit;
    VertrixSpriteFrame spent;
} VertrixTubeArt;

int vertrix_hud_tube_art_build(const VertrixHud *hud, VertrixVf *archive, VertrixTubeArt *art);
void vertrix_tube_art_free(VertrixTubeArt *art);

/* Draw one player's tube (x = 156 for the first player, 472 for the second) over a surface in R,
 * G, B, A byte order. */
void vertrix_hud_tube_draw(const VertrixHud *hud, const VertrixTubeArt *art,
                           const VertrixGaugeTube *tube, int x, VertrixSurface *target);

/* Draw the dim overlay over a number box (top-left x, y) with the effect offset it is animated by,
 * on a surface in R, G, B, A byte order. */
void vertrix_hud_overlay_draw(const VertrixHud *hud, int x, int y, int16_t offset,
                              VertrixSurface *target);

/* Draw a text element: the string centered in the inclusive box, in the font's glyphs, styled by
 * filter item `item`, onto a surface in R, G, B, A byte order. Returns the glyphs drawn. */
int vertrix_hud_text_draw(const VertrixHud *hud, const VertrixGameText *text, unsigned font,
                          const char *string, int left, int top, int right, int bottom,
                          unsigned item, VertrixSurface *target);

#endif
