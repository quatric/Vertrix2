#ifndef VERTRIX_PLAYER_PIECE_H
#define VERTRIX_PLAYER_PIECE_H
#include "piece_actor_construct.h"
#include "piece_actor_layout.h"
/* Called with an actor identity for the original virtual destructor (slot 0,
 * flag 2) at [actor + 0x158]. The destructor itself is a separate recovery. */
typedef int (*VertrixPlayerActorDestroy)(uint32_t handle, void *context);
/* Original432160. Player handle b78 nonzero: succeed without any change.
 * Otherwise construct the supplied parent storage (original42aab0), build the
 * piece through original42acf0 and publish parent_handle at b78. Heap allocation
 * is supplied as caller storage and a nonzero identity. The player needs 0xb7c
 * bytes. All failures, including parent/children overlap, preserve every
 * caller buffer. */
int vertrix_player_piece_create(void *player, size_t player_size, uint32_t parent_handle,
                                void *parent, size_t parent_size, void *children,
                                size_t children_size, const uint32_t frames[7],
                                const uint32_t handles[7], uint8_t side, int difficulty, int level,
                                const VertrixPiecePlacement *placement);
/* Original4321b0. b78 zero succeeds unchanged. Otherwise read the frame at b8 of
 * the last active child (count188 1..7, handle at158+count*4), store it at b7c,
 * destroy the piece and clear b78. Resolution keeps parent and child storage
 * live. Failure before destruction preserves the player. */
int vertrix_player_piece_release(void *player, size_t player_size,
                                 VertrixActorStorageResolve resolve, void *resolve_context,
                                 VertrixPlayerActorDestroy destroy, void *destroy_context);
/* Original432110. b70 zero succeeds unchanged. Otherwise copy dword168 of the
 * preview actor to b74, destroy it and clear b70. */
int vertrix_player_preview_release(void *player, size_t player_size,
                                   VertrixActorStorageResolve resolve, void *resolve_context,
                                   VertrixPlayerActorDestroy destroy, void *destroy_context);
/* Original425e20: construct a player piece object (base fields 0x4abd70) with
 * class token 0x5144d4 and level dword +0x178 = 0. The player caller
 * allocates 0x218 bytes and stores the result at +0x450. Short storage is
 * preserved and returns zero. */
int vertrix_player_piece_initialize(void *piece, size_t piece_size);
#endif
