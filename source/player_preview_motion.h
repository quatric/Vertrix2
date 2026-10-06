#ifndef VERTRIX_PLAYER_PREVIEW_MOTION_H
#define VERTRIX_PLAYER_PREVIEW_MOTION_H
#include "actor_storage.h"
/* Original42b000: nonzero178 suppresses changes. Otherwise set178=1, use
 * difficulty0..2 fast timing and clear primary counter. Invalid required
 * difficulty/storage preserves actor bytes. */
int vertrix_player_preview_motion_start(void *player, size_t size, int difficulty);
/* Original42b050 signed-word comparison: current y16 is greater than limitae.
 * Invalid storage/output preserves output. */
int vertrix_player_preview_below_limit(const void *player, size_t size, int *below);
#endif
