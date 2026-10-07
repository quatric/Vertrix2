#ifndef VERTRIX_SPRITE_ACTOR_STORAGE_H
#define VERTRIX_SPRITE_ACTOR_STORAGE_H
#include "actor_storage.h"
/* Original fragment 0x471100: actor initialization before list registration. Configuration
 * contains index*12 style records and dword availability at5cc+index*4. Only
 * availability1 creates an actor. Disabled/invalid inputs preserve storage.
 * Resource5449fc is an identity token. Caller allocates and registers storage. */
int vertrix_sprite_actor_storage_construct(void *storage, size_t size, int16_t x, int16_t y,
                                           uint32_t frame, const void *configuration,
                                           size_t configuration_size, uint32_t index,
                                           uint32_t sentinel);
#endif
