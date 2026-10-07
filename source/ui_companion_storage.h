#ifndef VERTRIX_UI_COMPANION_STORAGE_H
#define VERTRIX_UI_COMPANION_STORAGE_H
#include "sprite_actor_storage.h"
/* Original composition 0x471100 followed by46e022..46e0a3/46e1b2..46e232. Configuration
 * indices64+pair are shared by both sides. Parameters correspond to initialized
 * dwords4f8c48/4f8c4c; callers supply recovered/runtime values, not guesses.
 * Allocation/list registration and image descriptor binding remain external. */
int vertrix_ui_companion_storage_construct(void *storage, size_t size, size_t pair, unsigned side,
                                           int16_t offset_x, int16_t offset_y, uint32_t frame,
                                           const void *configuration, size_t configuration_size,
                                           uint32_t sentinel, uint32_t parameter_one,
                                           uint32_t parameter_other);
#endif
