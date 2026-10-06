#ifndef VERTRIX_UI_PREVIEW_PAIR_H
#define VERTRIX_UI_PREVIEW_PAIR_H
#include "sprite_actor_image.h"
/* Complete companion/border setup and final binding from42b3f3..42b586.
 * Caller supplies distinct live actor storage and the resolved interface and
 * generated border banks. Allocation, parent attachment and scene insertion
 * remain caller-owned. Invalid setup preserves both actors. */
int vertrix_ui_preview_pair_construct(void *companion, size_t companion_size, void *border,
                                      size_t border_size, size_t index, uint8_t side,
                                      uint32_t linked_identity, uint32_t source,
                                      const VertrixUiSpriteBank *interface_bank,
                                      const VertrixUiSpriteBank *border_bank);
#endif
