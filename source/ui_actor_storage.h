#ifndef VERTRIX_UI_ACTOR_STORAGE_H
#define VERTRIX_UI_ACTOR_STORAGE_H
#include "actor_storage.h"
/* Base constructor4abd70 then original position and alternating setup46e0c8/
 * 46e257. side0=left, side1=right; pair0..11. Descriptor is a mapped identity
 * token, not a pointer. Allocation and scene-list registration are external.
 * Invalid parameters preserve all storage. */
int vertrix_ui_actor_storage_construct(void *storage, size_t size, size_t pair, unsigned side,
                                       int16_t offset_x, int16_t offset_y, uint32_t descriptor);

/* Original0x4710d0: initialize the actor (via 0x4adf20) with the sign-extended
 * x/y words, z = 0, bank 0x5449fc, the frame dword and zero image/handler,
 * then clear byte +0x8e and set byte +0x8f. Short storage preserves everything
 * and returns zero. */
int vertrix_ui_actor_place(void *actor, size_t size, int16_t x, int16_t y, uint32_t frame);
#endif
