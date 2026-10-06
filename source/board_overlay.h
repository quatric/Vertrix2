#ifndef VERTRIX_BOARD_OVERLAY_H
#define VERTRIX_BOARD_OVERLAY_H
#include "actor_gate.h"
#include "block_factory.h"
/* Original0x42ff50: build the board's overlay actor. d0 becomes its +0xd0 and steps its period;
 * variant zero attaches the resource 0x544d44 and class token 0x15, any other variant 0x544d60 and
 * 0x16. The actor covers the board's origin words at +0xc and +0x14 (high words, 0x77 wide and
 * 0x137 high), takes the first style record of the table at board dword +0xce4 (read through
 * read), is placed 0x138 below the board and stored at board dword +0xce0.
 * steps is the original table lookup 0x4f7cfc[dword 0x532bbc], supplied by the caller. Returns
 * zero when allocation, an object or the style table cannot be read, leaving the board untouched.
 */
int vertrix_board_create_overlay(void *board, size_t board_size, uint32_t variant, uint32_t d0,
                                 uint32_t steps, const VertrixFactoryServices *services,
                                 VertrixMemoryRead read, void *read_context);

/* Original0x43d2b0: build the overlay of the board whose handle is the player's dword +0x15c. The
 * player's mode dword at +0 selects the variant: 1 gives variant 0, 2 gives variant 1 and any other
 * mode leaves the caller's register value, fallback_variant. d0 is the original table lookup
 * 0x5347a0[dword 0x532a70], supplied by the caller. Returns zero when an object does not resolve.
 */
int vertrix_player_create_overlay(const void *player, size_t player_size, uint32_t fallback_variant,
                                  uint32_t d0, uint32_t steps,
                                  const VertrixFactoryServices *services, VertrixMemoryRead read,
                                  void *read_context);
#endif
