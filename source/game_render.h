#ifndef VERTRIX_GAME_RENDER_H
#define VERTRIX_GAME_RENDER_H
#include "assets.h"
#include "game_art.h"
#include "game_session.h"
#include "menu.h"
#include "surface.h"

/* Draw a session into a 32-bit frame whose channels follow the masks the artwork and block set
 * were loaded with: the character's decor, the board at its original screen position on a
 * translucent panel, the 24x24 block frames, the character head and the original number and
 * letter fonts. tick is a millisecond counter that selects the block animation frame. */
void vertrix_game_render(VertrixSurface *frame, const VertrixSession *session,
                         const VertrixBlockSet *blocks, const VertrixGameArt *art, uint32_t tick);

/* The versus screen: both sides of the stage's decor, the second player on the mirrored objects
 * (board at 334, tube at 472, head at 578, next strip at 478). */
void vertrix_versus_render(VertrixSurface *frame, const VertrixSession *first,
                           const VertrixSession *second, const VertrixBlockSet *blocks,
                           const VertrixGameArt *art, uint32_t tick);

/* Advance the idle animations of the heads (second is NULL in a single-player game). */
void vertrix_game_heads_update(VertrixGameArt *art, const VertrixSession *first,
                               const VertrixSession *second, uint32_t elapsed);

enum
{
    VERTRIX_TITLE_ITEMS = 4
};

/* The menu pages on the original Main_Screen decor: the rows of the current page (title, one and
 * two players, options) in boxes, the selected one brighter. The boxes are a stand-in for the
 * original menu objects, whose layout is not recovered; the texts are the original's. */
void vertrix_menu_render(VertrixSurface *frame, const VertrixGameArt *art, const VertrixMenu *menu);

/* The rows of the current page over what is already drawn (the in-game page). */
void vertrix_menu_overlay(VertrixSurface *frame, const VertrixGameArt *art,
                          const VertrixMenu *menu);

#endif
