#ifndef VERTRIX_UI_PLAYER_PREVIEWS_H
#define VERTRIX_UI_PLAYER_PREVIEWS_H
#include "ui_preview_pair.h"
#define VERTRIX_UI_PREVIEW_ACTORS 6
/* Original 0x42b150 base constructor and preview-parent class initialization.
 * Clear the six owned preview handles, preserve all other untouched bytes.
 * Invalid storage below174 bytes remains unchanged. */
int vertrix_ui_player_preview_parent_construct(void *player, size_t player_size);
/* Original42b370 three-pair construction and player attachment. Storage order
 * is companion0,border0,companion1,border1,companion2,border2. Caller owns the
 * actors and supplies distinct nonzero handle identities for its resolver.
 * Parent handles occupy15c..170; linked identity comes from parent field0.
 * Caller registers actors with the scene separately. Preserve all outputs on
 * invalid input or binding failure; parent and actors must not overlap. */
int vertrix_ui_player_previews_construct(void *player, size_t player_size, void *actors,
                                         size_t actors_size,
                                         const uint32_t handles[VERTRIX_UI_PREVIEW_ACTORS],
                                         uint8_t side, uint32_t source,
                                         const VertrixUiSpriteBank *interface_bank,
                                         const VertrixUiSpriteBank *border_bank);
#endif
