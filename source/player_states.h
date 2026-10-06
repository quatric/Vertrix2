#ifndef VERTRIX_PLAYER_STATES_H
#define VERTRIX_PLAYER_STATES_H
#include <stdint.h>

#include "regs_call.h"

/* The player state handlers of the object at +0x15c (the board) that run after a piece locks.
 * Every handler takes the player (eax) and the caller's edx and ebx, hands unrecovered routines
 * to the call boundary with the registers the original holds, and ends with the board's virtual
 * call [[board + 0x158] + 4] (the table pointer in edx, or in ebx for 0x451520 and 0x451630).
 * Each returns the eax of that call, zero when a storage does not resolve. */

/* Original 0x451490 and 0x451730: 0x4ac500 and 0x4ac520 on the board; when that is one,
 * 0x4ac540 gives a step count n, 0x4ac5b0 follows (edx = n) and 0x4342f0 runs n times with edx
 * counting down from n - 1. Then 0x433e20: a non-zero result ends. Otherwise 0x451490 calls
 * 0x4323d0(edx = 0x451520) and 0x4ac8f0 on the player (handler token 0x451520), 0x451730 calls
 * 0x4ac8f0 with 0x4517c0. */
uint32_t vertrix_state_steps_451490(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player, uint32_t edx,
                                    uint32_t ebx);
uint32_t vertrix_state_steps_451730(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player, uint32_t edx,
                                    uint32_t ebx);

/* Original 0x451520 (ebx = the player): 0x4334b0 on the board, a non-zero result ends; otherwise
 * the low byte of 0x433550 is stored at board +0x838, 0x433e20 takes the token 0x451580 in edx
 * and 0x4ac8f0 sets the handler 0x451580 on the player. */
uint32_t vertrix_state_gate_451520(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, uint32_t player, uint32_t edx);

/* Original 0x451580 (ebx = the player): 0x4ac500, 0x4ac520; when that is one 0x4ac540 gives n,
 * 0x4ac5b0 follows (edx = n) and for n down to one steps 0x433840 runs while the byte at board
 * +0x838 is positive (decrementing it each time). A non-zero byte ends. With the byte zero
 * 0x433840, 0x42eee0 (token 0x451630), 0x4ac8f0 on the player and sound 0x43c0e0 with the dword
 * 0x4f81ac follow. */
uint32_t vertrix_state_drain_451580(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player, uint32_t edx);

/* Original 0x451630 (ebx = the player): 0x42eca0 and 0x42ecc0 on the board with edx = 0x44c860;
 * a zero result of either ends. Otherwise 0x42ebe0 takes the token 0x4517c0 and 0x4ac8f0 sets
 * the handler 0x4517c0 on the player. */
uint32_t vertrix_state_check_451630(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player);

/* Original 0x451690 (ebx = the player, esi = the player): the byte at player +0x4cd selects
 * the branch. A non-zero byte with 0x4322f0 on the board equal to one plays the sound 0x4f8184,
 * runs 0x42eee0, 0x4334a0 (the sign extended byte), 0x43bad0(edx = 0), 0x4ac7b0 (the dword
 * 0x4f7be8[dword 0x532bbc]) and sets the handler 0x451730. Otherwise, when the board dword
 * +0xbd8 is zero the sound 0x4f819c plays, and the handler 0x451920 is set. */
uint32_t vertrix_state_start_451690(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player, uint32_t edx);

/* Original 0x451dd0 (eax = player, edx the caller's register): 0x42a1b0 on the choice grid
 * (+0x3b8) with the board in ebx; a non-zero result ends, otherwise 0x4ac8f0 sets the handler
 * 0x451e20 on the player. Both end with the board's virtual call through [board + 0x158] held in
 * ecx. */
uint32_t vertrix_state_choice_check(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player, uint32_t edx);

/* Original 0x451e20 (eax = player, ecx the caller's register, frame the token for ebp). The
 * choice grid (+0x3b8) is asked about the cell (+0x194, +0x198) with 0x42a190. Unless that is
 * one, 0x43acd0 runs on the player (ecx = 1, flag set). If it is one and 0x43ccb0 is zero,
 * 0x42a170 gives two bytes (stored through the pointers frame - 0x1c and frame - 0x18, the call
 * site's out_value and out_ecx) for 0x43c140(player, edx = second, ebx = first); when that is
 * zero 0x43acd0 runs with ebx = 1 (flag set). The board's virtual call follows, and a set flag
 * ends with 0x43bbf0 on the player. Returns the last eax. */
uint32_t vertrix_state_choice_apply(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t frame, uint32_t player,
                                    uint32_t ecx);

/* Original 0x451f50 (eax = player, ecx the caller's register, frame the token for ebp). Like
 * 0x451e20 the choice grid is asked about the cell (+0x194, +0x198) with 0x42a190. Unless that is
 * one the flag is set. Otherwise 0x42a140 takes the cell, 0x4ac8f0 sets the handler 0x451dd0,
 * 0x43bae0(edx = 4, ecx = frame - 0x18) and 0x42a170 (stack pointer frame - 0x1c) give two
 * dwords, 0x43bd90 (edx and ebx the low bytes, ecx = frame - 0x34, stack frame - 0x30 and 0)
 * stores two more, and 0x43c0e0 plays them as sounds on the player and on the opponent (+0x3b0).
 * The board's virtual call follows (ebx = the flag) and a set flag ends with 0x43bbf0 on the
 * player. Returns the last eax. */
uint32_t vertrix_state_choice_take(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, uint32_t frame, uint32_t player,
                                   uint32_t ecx);

/* Original 0x452160 (eax = player, edx the caller's register, ecx = the player, ebx = the board).
 * 0x4328a0 on the board: one sets the board period from the dword 0x4f7bf4[dword 0x532bbc], the
 * word +0x1a from the word 0x4f7c00[...], clears +0x58, 0x4ac510 and sets the handler 0x452770.
 * Otherwise a player +0x44c of one runs 0x452250; else 0x43ba70 equal to one starts the bonus
 * (handler 0x451a60, 0x43bae0(edx = 2) and 0x43ba80) and any other result sets the handler
 * 0x450ff0 (0x43bae0 with edx = 0). All end with the board's virtual call. */
uint32_t vertrix_state_match_452160(const VertrixCalls *calls,
                                    const VertrixFactoryServices *services,
                                    const VertrixGlobals *globals, uint32_t player, uint32_t edx);

/* Original 0x452440 (eax = player; ebx = the dword +0x3f0, ecx = the board). 0x4316c0 on the
 * opponent's board (+0x15c of +0x3b0) with the opponent's +0x428 in edx: one sets the board period
 * from 0x4f7c24[dword 0x532bbc], the word +0x1a from 0x4f7c30[...], clears +0x58, 0x4ac510, sets
 * the handler 0x452520 on the player and plays the sound 0x4f8188 for the opponent; anything else
 * sets the flag. Both boards then take their virtual call and a set flag ends with 0x43bbf0 on
 * the player and on the opponent. */
uint32_t vertrix_state_attack_452440(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services,
                                     const VertrixGlobals *globals, uint32_t player);

/* Original 0x452770 (eax = player, edx the caller's register). 0x4328a0 on the board (+0x15c)
 * not one sets the handler 0x451920. Otherwise 0x4ac500, then 0x4ac590 with edx = the board dword
 * +0x18 shifted right by 16 (arithmetic); a nonzero result runs 0x4ac510 and adds it to +0x58.
 * A +0x58 of 0x18 or more (signed) runs 0x432a30 and loses 0x18 until it is below 0x18, a smaller
 * one runs 0x432b10. All end with the board's virtual call. */
uint32_t vertrix_state_advance_452770(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, uint32_t player, uint32_t edx);

/* Original 0x453050 (eax = player). The board (+0x15c) and the opponent's board (+0x15c of +0x3b0)
 * are asked in turn with 0x42eca0, 0x42ecc0 (board, then the opponent's) and 0x42edf0 about the
 * descriptor 0x44c860; a zero ends the check, a failing 0x42edf0 on 0x44c860 is rescued by one on
 * 0x44c940. When everything holds, 0x42eb60 runs on the opponent's board if that one also takes
 * 0x44c940, 0x42ebe0 runs on both boards and the flag is set. The board's virtual call follows,
 * and a set flag ends with 0x43bbf0 on the player and the opponent and zeroes +0xb8c of both
 * boards. */
uint32_t vertrix_state_pair_453050(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, uint32_t player);

/* Original 0x453320 (eax = player; ebx and ecx are the caller's registers). 0x43c0e0 plays the
 * sound dword 0x4f81ac on the opponent (+0x3b0), 0x436aa0 takes the dword +0x3dc for the player's
 * board and the opponent's, 0x436d80 (edx = the opponent's board, ebx = +0x3dc, ecx = +0x43c,
 * stack +0x440) combines them, then the handler 0x4533b0 is set and the board's virtual call
 * runs. */
uint32_t vertrix_state_combine_453320(const VertrixCalls *calls,
                                      const VertrixFactoryServices *services,
                                      const VertrixGlobals *globals, uint32_t player, uint32_t ebx,
                                      uint32_t ecx);

/* Original 0x4533b0 (eax = player). The board (+0x15c) and the opponent's board answer 0x42eca0
 * and 0x42ecc0 about the descriptor 0x44c860 (board, board, opponent's, opponent's); a zero ends
 * the check. When all hold 0x42ebe0 runs on both boards (the second with ebx = 1) and the flag is
 * set. The board's virtual call follows with ebx = the board's table; a set flag ends with
 * 0x43bbf0 on the player and the opponent. */
uint32_t vertrix_state_pair_4533b0(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services,
                                   const VertrixGlobals *globals, uint32_t player);
#endif
