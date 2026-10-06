#ifndef VERTRIX_HUD_LAYOUT_H
#define VERTRIX_HUD_LAYOUT_H
#include <stdint.h>

enum
{
    VERTRIX_HUD_LAYOUT_CHARACTERS = 18
};

/* One damier piece of the game screen in the original's creation (= draw) order: the actor
 * position, the sprite/damier.spr frame and the Filtre/<Character>.flt item that styles it. */
typedef struct
{
    int16_t x, y;
    uint8_t frame, item;
} VertrixHudPiece;

typedef struct
{
    const VertrixHudPiece *pieces;
    unsigned count;
} VertrixHudSegment;

/* A box set by 0x4b65d0: left, top, right, height. */
typedef struct
{
    int16_t left, top, right, height;
} VertrixHudBox;

/* The builder 0x46b810: fixed pieces, the bonus slot grid of each side (it depends on the chosen
 * character, [0x532a68] / [0x532a6c]), fixed pieces again, and the two name boxes. */
typedef struct
{
    VertrixHudSegment prefix, tail;
    const VertrixHudSegment *slots[2];
    VertrixHudBox boxes[2];
} VertrixHudLayout;

extern const VertrixHudLayout VERTRIX_HUD_LAYOUT;

#endif
