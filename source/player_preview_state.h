#ifndef VERTRIX_PLAYER_PREVIEW_STATE_H
#define VERTRIX_PLAYER_PREVIEW_STATE_H
#include "actor_lookup.h"
/* Original0x42b0e0: mode access; related operations are the wrapping 1-value toggle
 * at 0x42b0f0 and assignment with transition-dependent flag +0x184 at 0x42b110.
 * Invalid storage preserves
 * outputs. Values are original DWORDs, not restricted to boolean inputs. */
int vertrix_player_preview_mode(const void *player, size_t size, uint32_t *mode);
/* Original0x42b0f0: replace the mode DWORD with wrapping 1 - mode. */
int vertrix_player_preview_toggle(void *player, size_t size);
/* Original0x42b110: assign mode with transition-dependent flag at +0x184. */
int vertrix_player_preview_set_mode(void *player, size_t size, uint32_t mode);
/* Original 0x42b070 selects the final active preview's frameb8 using count188.
 * Valid native counts1..3 map to companion handles15c..164. Resolve stable
 * actor storage; invalid count/handle/resolution preserves the output. */
int vertrix_player_preview_frame(const void *player, size_t size,
                                 VertrixActorStorageResolve resolve, void *context,
                                 uint32_t *frame);
/* Original 0x42b090/425de0: initialize seven output DWORDs toffffffff, then copy
 * frameb8 from each active companion in slot order. Counts0..3 are supported.
 * Output is a native uint32 array; missing/invalid actor resolution preserves
 * the entire output. Resolver keeps player handles/count and actors stable. */
int vertrix_player_preview_frames(const void *player, size_t size,
                                  VertrixActorStorageResolve resolve, void *context,
                                  uint32_t *frames, size_t capacity);
#endif
