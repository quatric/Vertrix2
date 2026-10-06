#ifndef VERTRIX_MATCH_SCAN_H
#define VERTRIX_MATCH_SCAN_H
#include <stddef.h>
#include <stdint.h>

#include "actor_gate.h"
#include "actor_spawn.h"
#include "call_glue.h"
#include "game.h"

/* The match scan 0x432480: kinds snapshot, figure and line passes, the cell
 * timer/event sweep, then the per-cell reward loop with effect actors for
 * kind 7 and a virtual dispatch otherwise. image holds the 65 line-pass
 * board bytes (the original global 0x5407b8, of which the scan refreshes
 * five from the snapshot) and mask the 65 shared mask dwords (the original
 * global 0x5406b0). dispatch_index is the value of the original global
 * 0x532a70 selecting the virtual method from the table at 0x4fb7b0.
 * flag_a/flag_b are the two out-words (the caller's frame), reward and
 * mult the chain reward and score multiplier. Returns one when a figure or
 * line matched or any cell was swept, zero only when nothing happened. */
uint32_t vertrix_match_scan(const VertrixCalls *calls, const VertrixFactoryServices *services,
                            VertrixMemoryRead read, void *read_context, uint32_t player,
                            void *player_storage, size_t player_size, uint8_t side,
                            uint32_t *flag_a, uint32_t *flag_b, uint32_t *reward, uint32_t *mult,
                            uint8_t image[COLS][ROWS], uint32_t mask[65], uint32_t dispatch_index,
                            const VertrixMatchBurstHooks *hooks);

#endif
