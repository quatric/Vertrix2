#ifndef VERTRIX_PLAYER_SLOTS_H
#define VERTRIX_PLAYER_SLOTS_H
#include "board_cells.h"
#include "piece.h"
#include "piece_actor_construct.h"
/* Small routines on the player object: the cursor child at +0x15c, the level dword at +0x178
 * of a board object, the mode dword at +0x4c8 and the first-turn decision. */

/* Original0x43d3b0 and 0x43d3d0: 1 when the mode dword at +0x4c8 is 0x25..0x27 (group A) or
 * 0x32..0x34 (group B), else 0. Returns -1 for short storage. */
int vertrix_player_mode_in_group_a(const void *player, size_t size);
int vertrix_player_mode_in_group_b(const void *player, size_t size);

/* Original0x43aab0: store side in byte +0x190, then position the cursor child (handle at +0x15c)
 * at (186, 130) for side 0 or (334, 130) otherwise (words +0xe and +0x16, constants at
 * 0x4f8a48..0x4f8a54), set its dword +0x4 to the player's dword +0x0 and its dword +0xce8 to the
 * player handle, and copy the side byte to byte +0x17c of the object handled at +0x450.
 * Returns zero for an unresolvable object. */
int vertrix_player_set_side(void *player, size_t size, uint32_t handle, uint8_t side,
                            VertrixObjectStorage resolve, void *context);

/* Supplied boundary for the original level change notification 0x431400. */
typedef void (*VertrixLevelNotify)(uint32_t child, uint32_t level, void *context);

/* Original0x43b810: clamp the requested level to 0..9 (negative gives 0), store it in dword
 * +0x17c and, when it changed, notify the cursor child. Returns 1 when the level changed, 0 when
 * not, -1 for an unresolvable object. */
int vertrix_player_set_level(void *player, size_t size, int32_t level, VertrixLevelNotify notify,
                             void *context);

/* Original 0x431400 (eax = holder, edx = level): refresh the side child at
 * holder +0xa60. A null child returns the holder; a nonzero dword at child
 * +0x168 also returns the holder (already set up). Otherwise the delay
 * table (original 0x4f7d50, dword at level + alter * 10) sets the period
 * (0x4ac7d0), the frame table (original 0x4f7dc8, word at level * 2 + alter
 * * 20) sets the word at +0x1a, and the counter clears (0x4ac510). Returns
 * the child handle on the full path, zero when storage is short or an
 * object does not resolve. */
uint32_t vertrix_player_level_side(VertrixObjectStorage resolve, void *context, uint32_t holder,
                                   void *storage, size_t size, uint32_t level, uint32_t alter,
                                   const uint32_t *delay_table, const uint16_t *frame_table);

/* Original shared globals of the first-turn decision 0x43b1a0, in their original order:
 * 0x532bc8 (game flag), 0x532b34 (last index) and the outputs 0x540f44, 0x540f48, 0x540f4c and
 * 0x540f50. */
typedef struct
{
    uint32_t mode_flag;
    uint32_t last_index;
    uint32_t candidate;
    uint32_t level;
    uint32_t draw;
    uint32_t drawn;
} VertrixTurnGlobals;

/* Supplied boundary for the original random draw 0x4826c0. */
typedef uint16_t (*VertrixTurnDraw)(uint16_t divisor, void *context);

/* Original0x43b1a0: with the flag set and the last index minus one equal to the player's dword
 * +0x178, or when the opponent object (handle at +0x3b0) has a signed level +0x178 above the
 * player's plus one, draw below 2 and answer whether it was 1; otherwise answer 1. Updates the
 * globals as the original does. Returns -1 for an unresolvable object. */
int vertrix_player_first_turn(const void *player, size_t size, VertrixTurnGlobals *globals,
                              VertrixObjectStorage resolve, VertrixTurnDraw draw, void *context);

/* Supplied boundary for the original refresh 0x4726d0. The original leaves the
 * player handle in eax across the call; the native version passes it explicitly. */
typedef void (*VertrixRefreshNotify)(uint32_t player, void *context);

/* Original0x43bb40: store the mode dword at +0x4c8, then refresh. Returns zero
 * for short storage, preserving it. */
int vertrix_player_set_mode_and_refresh(void *player, size_t size, uint32_t handle, uint32_t mode,
                                        VertrixRefreshNotify notify, void *context);

/* Original0x43baf0: store the flag byte at +0x4c4, then refresh. Returns zero
 * for short storage, preserving it. */
int vertrix_player_set_b00_and_refresh(void *player, size_t size, uint32_t handle, uint8_t value,
                                       VertrixRefreshNotify notify, void *context);

/* Original0x43d260: generate three block types with the player mode at +0x4c8
 * (via 0x43d180) and store them in the preview piece (handle at +0x3b4) through
 * 0x43a4f0. The original bounces the kinds through globals 0x540f84..86; the
 * native version uses stack storage. Returns zero for short storage or an
 * unresolvable preview. */
int vertrix_player_generate_preview(const void *player, size_t size, VertrixRandom *random,
                                    VertrixObjectStorage resolve, void *context);

/* Original0x43b5b0: draw delay parameter 0 from the kind at +0x488, the internal
 * level at +0x17c and the supplied difficulty (original global 0x532bbc), then
 * store the drawn value at +0x458. The table lookup matches vertrix_delay;
 * only parameter 0 applies the internal-level adjustment. Same routine as
 * ai_timing's reaction_time with player-object plumbing. Returns zero for
 * short storage or out-of-range kind/difficulty, preserving storage. */
int vertrix_player_draw_delay_0(void *player, size_t size, VertrixRandom *random,
                                uint32_t difficulty);

/* Original0x43b660 / 0x43b680: as above for parameters 1 and 2 (shared helper
 * 0x43b6a0 with row pairs 2,3 and 4,5; no level adjustment), stored at +0x45c
 * and +0x460 respectively. Same preservation contract. */
int vertrix_player_draw_delay_1(void *player, size_t size, VertrixRandom *random,
                                uint32_t difficulty);
int vertrix_player_draw_delay_2(void *player, size_t size, VertrixRandom *random,
                                uint32_t difficulty);

/* Original0x43b590: draw all three delay parameters in order (0, 1, 2),
 * storing +0x458/+0x45c/+0x460. Stops at the first failure, preserving the
 * remaining fields; earlier draws and RNG consumption are retained. */
int vertrix_player_draw_all_delays(void *player, size_t size, VertrixRandom *random,
                                   uint32_t difficulty);

/* Original0x43ab30: initialize the piece at +0x450 from the kind byte at +0x488
 * (via 0x425ef0), then draw all three delay parameters. The kind byte shares
 * its address with the dword kind field; values at or above 19 read beyond the
 * tables in the original and return zero here without touching either object.
 * Short storage or an unresolvable piece likewise preserves everything. */
int vertrix_player_init_piece_and_delays(void *player, size_t size, VertrixRandom *random,
                                         uint32_t difficulty, VertrixObjectStorage resolve,
                                         void *context);

/* Supplied boundary for the original side-object destruction (resource method
 * at [side + 0x158], invoked with edx = 2). Receives the side handle for log
 * parity with the oracle stub; destruction effects are the boundary's own
 * responsibility, as with the stubbed graphics destructors elsewhere. */
typedef void (*VertrixSideDestroy)(uint32_t side, void *context);

/* Supplied boundary for the original operator new 0x4ca000. Returns the side
 * handle, or zero on allocation failure (never executed against the original,
 * which the oracle stubs; mirrored from the factory-services convention). */
typedef uint32_t (*VertrixSideAllocate)(uint32_t size, void *context);

/* Original0x43b980: when the side handle at +0x4e8 is nonzero, destroy it
 * through the supplied boundary, clear the field, and run the side reset
 * below. A null side returns at once with no other effect. Short storage
 * preserves everything and returns zero. The handle selects the player for
 * the refresh inside the reset. */
int vertrix_player_release_side(void *player, size_t size, uint32_t handle, VertrixRandom *random,
                                VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                VertrixObjectStorage resolve, void *context);

/* Original0x43ce00: release the side, reset the mode dword to 0 (with
 * refresh), mark the reset state (via 0x43cde0), and regenerate the preview.
 * Always returns 1 on valid storage. */
int vertrix_player_reset_side(void *player, size_t size, uint32_t handle, VertrixRandom *random,
                              VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                              VertrixObjectStorage resolve, void *context);

/* Original0x43b930: release and reset as above, then allocate a 0x15c-byte
 * side object, construct it (via 0x4abd70) and set its period from the
 * supplied step count (via 0x4ac7b0, period = 12 * steps). The steps arrive in
 * edx from the caller (difficulty table 0x4f9c14) and are supplied here, as
 * with the overlay period. Allocation failure preserves the reset player and
 * returns zero without constructing. */
int vertrix_player_alloc_side(void *player, size_t size, uint32_t handle, uint32_t steps,
                              VertrixRandom *random, VertrixSideAllocate allocate,
                              VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                              VertrixObjectStorage resolve, void *context);

/* Original0x43ce30: allocate as above, mark the reset state (via 0x43cde0),
 * reset the mode dword to 0x30 (with refresh), and overwrite the state dword
 * with 4. Always returns 1 on valid storage with a successful allocation. */
int vertrix_player_setup_side(void *player, size_t size, uint32_t handle, uint32_t steps,
                              VertrixRandom *random, VertrixSideAllocate allocate,
                              VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                              VertrixObjectStorage resolve, void *context);

/* Original0x43ba80: clear the dword at +0x18c to zero. Returns zero for short
 * storage, preserving it. */
int vertrix_player_clear_field_18c(void *player, size_t size);

/* Original0x43bae0 / 0x43bad0: store the flag bytes at +0x4cc / +0x4cd (the
 * state bytes of the player_actions event machine). Returns zero for short
 * storage, preserving it. */
int vertrix_player_set_b08(void *player, size_t size, uint8_t value);
int vertrix_player_set_b14(void *player, size_t size, uint8_t value);

/* Original0x43bb00: store the B01 byte, then refresh only when it is nonzero.
 * Otherwise, when the mode is in group A, reset the opponent (handle at
 * +0x3b0); then release and reset the player itself and refresh once more.
 * The trailing refresh observes the reset's return (1). The return value is
 * a native convention; only state and event logs compare. */
int vertrix_player_conditional_reset(void *player, size_t size, uint32_t handle, uint8_t b01,
                                     VertrixRandom *random, VertrixSideDestroy destroy,
                                     VertrixRefreshNotify notify, VertrixObjectStorage resolve,
                                     void *context);

/* Original0x43cd30: when the mode dword is in group A (0x25..0x27), run the
 * side reset and refresh, returning 1; otherwise return 0 with no effect.
 * The trailing refresh observes the reset's return value (1), not the player:
 * the original falls into it with the reset's eax still live. Short storage
 * returns zero. */
int vertrix_player_gated_reset(void *player, size_t size, uint32_t handle, VertrixRandom *random,
                               VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                               VertrixObjectStorage resolve, void *context);

/* Original0x43cd60 / 0x43cda0: allocate as above with live-table steps, reset
 * the mode dword to 0x2b / 0x2c (with refresh), and mark the reset state.
 * Always return 1 on valid storage with a successful allocation. */
int vertrix_player_setup_side_2b(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context);
int vertrix_player_setup_side_2c(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context);

/* Original0x43ccf0: release the side, store the supplied value at +0x4e4 (no
 * allocation), reset the mode dword to the value plus 0x25 (32-bit wrap, with
 * refresh), mark the reset state, clear +0x18c and +0x3f4, and refresh again.
 * Callers pass either 0 or a side handle (loaded from +0x3f8): 0 selects mode
 * 0x25 and 2 selects 0x27, while a handle selects an out-of-group mode. The
 * +0x4e8 side field is only cleared by the release, never written here.
 * (Note: the text disassembly misreports this store as +0x4e8 and swaps the
 * preceding register move; the mapped-image bytes 89 91 E4 04 00 00 show
 * +0x4e4, confirmed differentially.) Always returns 1 on valid storage. */
int vertrix_player_adopt_side(void *player, size_t size, uint32_t handle, uint32_t value,
                              VertrixRandom *random, VertrixSideDestroy destroy,
                              VertrixRefreshNotify notify, VertrixObjectStorage resolve,
                              void *context);

/* Mode-setup family (0x43cf30/70/f0, 0x43d030/70/b0/f0): allocate the side
 * with supplied steps, reset the mode dword (with refresh), mark the reset
 * state (via 0x43cde0), and regenerate the preview. The steps come from the
 * difficulty tables (0x4f9c14, 0x4f9c20 or 0x4f9c2c by member) and are read
 * live in tests. Always return 1 on valid storage with a successful
 * allocation. */
int vertrix_player_setup_side_22(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context);
int vertrix_player_setup_side_23(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context);
int vertrix_player_setup_side_28(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context);
int vertrix_player_setup_side_29(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context);
int vertrix_player_setup_side_2a(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context);
int vertrix_player_setup_side_2d(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context);
int vertrix_player_setup_side_2e(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context);

/* Original0x43cfb0: as above for mode 0x24, but the tail writes byte +0x4dc =
 * 3 instead of regenerating the preview (overwriting the reset-state mark). */
int vertrix_player_setup_side_24(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context);

/* Original0x43ceb0: allocate as above, mark the reset state, reset the mode
 * to 0x2f, and overwrite the state dword with 1. */
int vertrix_player_setup_side_2f(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context);

/* Original0x43cef0: allocate as above, mark the reset state and reset the mode to 0x31. */
int vertrix_player_setup_side_31(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context);

/* Original0x43ce70: allocate with steps from table 0x4f9c38 indexed by the
 * dword at +0x3fc, mark the reset state, and reset the mode to that index
 * plus 0x32. The index is read from the player; the steps are supplied. */
int vertrix_player_setup_indexed(void *player, size_t size, uint32_t handle, uint32_t steps,
                                 VertrixRandom *random, VertrixSideAllocate allocate,
                                 VertrixSideDestroy destroy, VertrixRefreshNotify notify,
                                 VertrixObjectStorage resolve, void *context);

/* Original0x43ba70: 1 when the bonus meter dword at +0x18c equals 3, else 0.
 * Returns -1 for short storage. */
int vertrix_player_bonus_ready(const void *player, size_t size);

/* Original0x43ad50: store 1 in the progress dword at +0x178 of the piece
 * resolved from the handle at +0x450. Returns 1 when stored, 0 for short
 * storage or an unresolvable piece (preserved). */
int vertrix_player_reset_piece_progress(const void *player, size_t size,
                                        VertrixObjectStorage resolve, void *context);

/* Shared globals of the progress update 0x43b720, in their original order:
 * 0x532bc8 (race mode flag), 0x532b34 (race limit), 0x532a3c (loser flag
 * output) and 0x4f81b4 (win effect). */
typedef struct
{
    uint32_t mode_flag;
    uint32_t race_limit;
    uint32_t loser_flag;
    uint32_t effect;
} VertrixProgressGlobals;

/* Supplied boundaries for the 0x43b720 callees. The reset covers 0x43bb00
 * (always with b01 = 0 here); the letter covers 0x4715a0 (mode is the dword
 * at player +0); the effect covers 0x43c0e0; the win covers 0x43ac00, whose
 * return the trailing refresh observes. ebx/ecx are the race limit and the
 * player handle, forwarded to the win handler's slot method. */
typedef void (*VertrixProgressReset)(uint32_t player, uint8_t b01, void *context);
typedef void (*VertrixProgressLetter)(uint32_t mode, void *context);
typedef void (*VertrixProgressEffect)(uint32_t player, uint32_t effect, void *context);
typedef uint32_t (*VertrixProgressWin)(uint32_t player, uint32_t ebx, uint32_t ecx, void *context);

/* Original0x43b720: add delta to the progress dword at +0x178 (floor 0).
 * With the race flag set and the result at or above the race limit, run the
 * win sequence (flag +0x464, opponent-alive check at +0x4c5, reset, letter,
 * effect, state +0x474, win handler); a dead opponent records the loser flag
 * instead. Stores the result and refreshes when it changed. Returns 1 when
 * the progress changed, 0 when unchanged, -1 for short storage or an
 * unresolvable opponent. */
int vertrix_player_progress_update(void *player, size_t size, uint32_t handle, int32_t delta,
                                   VertrixProgressGlobals *globals, VertrixProgressReset reset,
                                   VertrixProgressLetter letter, VertrixProgressEffect effect,
                                   VertrixProgressWin win, VertrixRefreshNotify notify,
                                   VertrixObjectStorage resolve, void *context);

/* Supplied boundaries for the match reward 0x43b9c0. Progress covers 0x43b720
 * (always with delta 1); level covers 0x43b800 (always with delta 1);
 * effect covers 0x43c0e0 with the supplied loop effect; refresh covers
 * 0x4726d0. */
typedef void (*VertrixRewardProgress)(uint32_t player, int32_t delta, void *context);
typedef void (*VertrixRewardLevel)(uint32_t player, int32_t delta, void *context);
typedef void (*VertrixRewardEffect)(uint32_t player, uint32_t effect, void *context);

/* Original0x43b9c0: fold the chain reward into the player. Chain is the
 * signed dword at +0x180 minus the reward; while it stays below 1, run the
 * loop (progress +1, level +1, chain +0xc, loop effect, refresh, flag +0x3ac
 * = 1). Then store the chain; with the suppress dword at +0x44c set, clear
 * the bonus meter at +0x18c, otherwise add the reward to the meter (32-bit
 * wrap) capped above 3 (unsigned). The return value is a native convention
 * (1 = stored); only state and event logs compare. Returns 0 for short
 * storage, preserving it. */
int vertrix_player_match_reward(void *player, size_t size, uint32_t handle, int32_t reward,
                                uint32_t loop_effect, VertrixRewardProgress progress,
                                VertrixRewardLevel level, VertrixRewardEffect effect,
                                VertrixRefreshNotify refresh, void *context);

/* Original0x43ba90: scale the reward by the difficulty table (dword at
 * table[difficulty], table base 0x4f80cc, difficulty from 0x532bbc), add it
 * to the score dword at +0x174 (32-bit wrap) and cap unsigned results above
 * 0x5f5e0ff (99,999,999) to the cap. The return value is a native convention
 * (1 = stored); only state compares. Returns 0 for short storage or an
 * out-of-range difficulty, preserving storage. */
int vertrix_player_add_score(void *player, size_t size, int32_t reward, uint32_t difficulty,
                             const uint32_t *table, size_t count);

/* Original0x43b800: add delta to the level dword at +0x17c (32-bit wrap)
 * and set it through 0x43b810 (clamped 0..9 with cursor notify). Returns the
 * 0x43b810 result (1 changed, 0 unchanged, -1 short storage). */
int vertrix_player_bump_level(void *player, size_t size, int32_t delta, VertrixLevelNotify notify,
                              void *context);

/* Original0x43ba60: store 12 in the chain dword at +0x180. Returns 1 when
 * stored, 0 for short storage (preserved). */
int vertrix_player_init_chain(void *player, size_t size);

/* Supplied boundary for the original event-machine 0x4ac8f0. Runs the bonus
 * handler (0x451aa0 here) on the player. */
typedef void (*VertrixBonusBegin)(uint32_t player, uint32_t handler, void *context);

/* Original0x451a60: spawn the bonus piece on the board resolved from the
 * handle at +0x15c with the kind byte extracted from the dword at +0x18d
 * (top byte, the original's unaligned-dword-plus-shift idiom), run the
 * bonus event, and reset the piece progress. The spawn runs for real
 * through vertrix_piece_actor_spawn (allocator and finish supplied); only
 * the event machine stays a boundary. Returns 1 when stored, 0 for short
 * storage or an unresolvable board or piece (preserved). */
int vertrix_player_start_bonus(void *player, size_t size, uint32_t handle,
                               VertrixPieceAllocate allocate, VertrixPieceFinish finish,
                               VertrixBonusBegin begin, VertrixObjectStorage resolve,
                               void *context);
#endif
