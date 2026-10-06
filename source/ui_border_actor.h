#ifndef VERTRIX_UI_BORDER_ACTOR_H
#define VERTRIX_UI_BORDER_ACTOR_H
#include "actor_storage.h"
/* Original42b3ac table selection: three positions, zero side selects left,
 * every nonzero side selects right. Invalid index/pointers preserve outputs. */
int vertrix_ui_border_actor_position(size_t index, uint8_t side, int16_t *x, int16_t *y);
/* Original base constructor plus42b4d7..42b55b border actor setup. Position and
 * linked identity come from the caller's surrounding player setup. Preserve
 * untouched bytes, bind5466a4 frame0, timer12, amount50/effect4 and anchor0.
 * Allocation, parent attachment, scene insertion and subsequent binding remain
 * separate. Invalid short/null storage remains unchanged. */
int vertrix_ui_border_actor_construct(void *storage, size_t size, int16_t x, int16_t y,
                                      uint32_t linked_identity);
#endif
