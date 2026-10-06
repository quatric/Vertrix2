#ifndef VERTRIX_GAME_ART_H
#define VERTRIX_GAME_ART_H
#include "game_text.h"
#include "head_anim.h"
#include "hud_draw.h"
#include "image.h"
#include "random.h"

/* A bordered bitmap font sheet: glyph cells on a regular grid whose lines use the border color
 * (the pixel at x = 0, y = 1) over the key color (the pixel at 0, 0), which is transparent. */
typedef struct
{
    VertrixImage image;
    uint32_t pitch_x;
    uint32_t pitch_y;
    uint32_t per_row;
} VertrixGlyphSheet;

/* Original artwork of one character's game screen, every image in the frame's channel order. */
typedef struct
{
    VertrixImage background;
    VertrixImage title;
    VertrixImage head;
    char name[24];         /* the character's name in capitals, the font has no lower case */
    int32_t head_center_x; /* HeadFileName.ini: pixels from the head's left edge to its centre */
    int32_t head_center_y;
    int32_t head_offset_x; /* the still head's top-left in the full-size head (Head_<name>.ini) */
    int32_t head_offset_y;
    VertrixImage head2; /* the second player's head in a versus match (empty otherwise) */
    char name2[24];
    int32_t head2_center_x;
    int32_t head2_center_y;
    int32_t head2_offset_x;
    int32_t head2_offset_y;
    int versus;
    VertrixImage head_rows[2][VERTRIX_HEAD_ROWS]; /* animation frames; row 0 is head / head2 */
    VertrixHeadScript scripts[2];
    VertrixRandom head_random;
    VertrixGlyphSheet big_numbers;
    VertrixGlyphSheet small_numbers;
    VertrixGlyphSheet letters;
    VertrixGameText *text;   /* the original text system the HUD numbers and names use */
    VertrixHud *hud;         /* kept to draw the animated tube beads each frame */
    VertrixTubeArt tube_art; /* the glow sprites of those beads */
} VertrixGameArt;

void vertrix_game_art_free(VertrixGameArt *art);

#endif
