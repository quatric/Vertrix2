#ifndef VERTRIX_BONUS_EFFECTS_H
#define VERTRIX_BONUS_EFFECTS_H
#include "block_factory.h"
#include "board_cells.h"
#include "call_glue.h"
#include "choice_grid.h"
#include "virtual_call.h"

/* Services of the bonus effect handlers behind the dispatcher 0x43c140. Objects are original
 * address tokens resolved to storage by resolve; every callee that is not recovered here goes
 * through calls with the registers it receives in the original (the entry ebp is the token frame,
 * as in vertrix_board_view_setup); virtual calls name a slot (vtable offset / 4) of an object
 * handle; draw is the original random draw 0x4826c0. */
typedef struct
{
    const VertrixCalls *calls;
    VertrixObjectStorage resolve;
    void *resolve_context;
    VertrixVirtualCall virtual_call;
    void *virtual_context;
    VertrixChoiceDraw draw;
    void *draw_context;
    const VertrixFactoryServices *factory;
    /* Reads a dword of the original's static data or globals (0x532bbc, tables) at the boundary. */
    uint32_t (*global)(uint32_t address, void *context);
    void *global_context;
} VertrixEffectServices;

/* Original 0x453ad0 (eax = player, the effect behind dispatcher id 3): reads the opponent
 * (+0x3b0), the player's board (+0x15c), the opponent's board (+0x15c) and the opponent's choice
 * grid object (+0x3b8). A cell drawn from the grid (0x429fe0, recovered as
 * vertrix_choice_grid_pick_cell) makes the opponent take it: 0x43acd0 on the player, the row and
 * column stored as dwords at the opponent's +0x194 and +0x198, 0x43bb60 and 0x4ac8f0 on the
 * opponent with the handler token 0x451f10, and the dwords +0xb80, +0xb84 and +0xb88 of the
 * opponent's board set to one. Without a cell only 0x43ac00 runs on the player. Both paths then
 * call slot 1 of the player's board and end with 0x43bbf0 on the player. Returns the result of
 * 0x43bbf0, zero when an object does not resolve (nothing is done after that point). */
uint32_t vertrix_effect_forced_choice(const VertrixEffectServices *services, uint32_t player,
                                      uint32_t frame);

/* Original 0x453150 (eax = player, the effect behind dispatcher ids 4 and 5; the player's +0x3dc
 * is the wanted block kind, 5 or 6): marks the blocks of that kind on the player's board and on
 * the opponent's (0x436a10, which also snapshots the kinds) and counts them as a and b. Equal
 * counts only call 0x43acd0 on the player. Otherwise 0x43ac00 (a > b, unsigned) or 0x43acd0 runs
 * on the player, the sound 11 plays for the opponent (0x43c0e0), a and b are stored at the
 * player's +0x43c and +0x440, a markers of the player's board and b of the opponent's are
 * converted (0x436b40, vertrix_boards_convert_counts_traced), 0x4ac8f0 takes the handler token
 * 0x453280 for the player, 0x43bb60 runs on the opponent, the opponent board's +0xb80, +0xb84
 * and +0xb88 become one and 0x4ac8f0 takes 0x452050 for the opponent. Slot 1 of the player's
 * board is then called. With equal counts the result is 0x43bbf0 on the player, otherwise the
 * result of that slot. Zero when an object does not resolve. frame is the entry ebp token. */
uint32_t vertrix_effect_convert_blocks(const VertrixEffectServices *services, uint32_t player,
                                       uint32_t frame);

/* Original 0x452e00 (eax = player, the effect behind dispatcher id 1). Everything not recovered
 * here, and the recovered board routines whose results steer the flow, are boundary calls with the
 * registers the original holds; entry_ebx is the caller's ebx, which the original passes on to its
 * first calls. With the opponent's +0x3b0 board and the player's board (+0x15c each) 0x438cd0
 * decides: non-zero only calls 0x43acd0 (ecx 1) and slot 1 of the player's board, then returns
 * 0x43bbf0. Otherwise 0x43ab60 chooses 0x43ac00 (result 1) or 0x43acd0 on the player; sound 11
 * goes to the opponent (0x43c0e0); when 0x4320c0 on the opponent's board and 0x4330d0 (opponent's
 * board, player's board) both return 1 and the opponent's +0x170 is 1, the kinds of the three
 * children of the opponent board's active piece (+0xa60) go, sign-extended, to 0x43a560 with the
 * opponent's +0x3b4 and +0x170 is cleared; then 0x431d80 and 0x42ee20 follow on the opponent's
 * board, 0x42eda0 (0x44f040) and 0x42ee80 (5) on both boards, 0x433040, 0x43bb60 on the opponent,
 * its board's +0xb80, +0xb84 and +0xb88 are set to one, and 0x4ac8f0 takes 0x452050 for the
 * opponent and 0x452fc0 for the player. Slot 1 of the player's board is called last and its result
 * returned. Zero when an object does not resolve. */
uint32_t vertrix_effect_board_match(const VertrixEffectServices *services, uint32_t player,
                                    uint32_t entry_ebx);

/* Original 0x453b90 (eax = player): 0x43d3b0 decides. Result 1 only calls 0x43acd0 on the player;
 * otherwise sound 3 (the dword at 0x4f818c) goes to the player (0x43c0e0) and 0x43ccf0 runs on the
 * player and on the opponent (+0x3b0) with the player's +0x3f8. Slot 1 of the player's board
 * (+0x15c) is then called and 0x43bbf0 on the player returned. entry_edx is the caller's edx,
 * which 0x43d3b0 and 0x43acd0 receive. Zero when an object does not resolve. */
uint32_t vertrix_effect_pair_sound(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_edx);

/* Original 0x453c00 (eax = player): 0x43ac00 on the player (edx = entry_edx), then 0x43bb60 and
 * 0x43bae0 with edx 4 and 0x4ac8f0 with the handler token 0x453c90 on the opponent, the opponent's
 * +0x428 cleared and its +0x424 set to the player's +0x3cc, the opponent board's +0xb80, +0xb84
 * and +0xb88 set to one, slot 1 of the player's board and 0x43bbf0 on the player. Zero when an
 * object does not resolve. */
uint32_t vertrix_effect_copy_speed(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_edx);

/* The sixteen small handlers 0x4535d0..0x453a80. Each reads a state dword (+0x4c8) of the opponent
 * (VERTRIX_GATE_OPPONENT) or of the player. When it equals state, 0x43acd0 runs on the player;
 * otherwise 0x43ac00 does (not in the self-sound kind) and then callee, with the registers the
 * original holds: opponent kind
 * (eax opponent, edx the player's board), self-board kind (eax and edx the player, ecx the player's
 * board) and self-sound kind (0x43c0e0 plays sound 6 instead of 0x43ac00; callee receives it in
 * edx). Every handler ends with slot 1 of the player's board and 0x43bbf0 on the player, whose
 * result is returned. Zero when an object does not resolve. */
typedef enum
{
    VERTRIX_GATE_OPPONENT,
    VERTRIX_GATE_SELF_BOARD,
    VERTRIX_GATE_SELF_SOUND
} VertrixGateKind;

typedef struct
{
    uint32_t handler;
    VertrixGateKind kind;
    uint32_t state;
    uint32_t callee;
} VertrixStateGate;

#define VERTRIX_STATE_GATE_COUNT 16
extern const VertrixStateGate vertrix_state_gates[VERTRIX_STATE_GATE_COUNT];

/* Original variants 0x4535d0, 0x453620, 0x453670, 0x4536c0, 0x453710, 0x453760, 0x4537b0, 0x453800,
 * 0x453850, 0x4538a0, 0x4538f0, 0x453940, 0x453990, 0x4539e0, 0x453a30, 0x453a80: Complete callable
 * handlers verified by tools/verify_bonus_effects.py; the recovered table or selector supplies each
 * entry points parameters. */
uint32_t vertrix_effect_state_gate(const VertrixEffectServices *services, uint32_t player,
                                   const VertrixStateGate *gate);

/* Original 0x452830 (eax = player): 0x43b800 with the negated +0x3bc of the player decides. Result
 * 1 plays sound 5 (the dword at 0x4f8194, 0x43c0e0), anything else calls 0x43acd0. Then slot 1 of
 * the player's board and 0x43bbf0 on the player, whose result is returned. */
uint32_t vertrix_effect_negated_gate(const VertrixEffectServices *services, uint32_t player);

/* Original 0x452880 (eax = player): 0x43b800 on the opponent with the player's +0x3c0. Result 1
 * plays sound 6 (0x4f8198) and calls 0x43ac00, anything else calls 0x43acd0 (edx still the +0x3c0
 * value); then slot 1 of the board and 0x43bbf0. */
uint32_t vertrix_effect_value_gate(const VertrixEffectServices *services, uint32_t player);

/* Original 0x4528e0 (eax = player): 0x43b7c0 on the opponent decides, with the opponent's +0x17c
 * read before and after it (a, b). Anything but 1 calls 0x43acd0. With 1 and a > b (unsigned)
 * sound 5 plays and 0x43acd0 follows; with a <= b sound 6 plays and 0x43ac00 follows. Then slot 1
 * of the board and 0x43bbf0. */
uint32_t vertrix_effect_progress_gate(const VertrixEffectServices *services, uint32_t player);

/* Original 0x452a30, 0x452b00, 0x452bb0 and 0x452c60 (index 1 to 4; eax = player): 0x43bad0 with
 * the index, then the common arming step 0x452960 with the handler token 0x452a50, 0x452b20,
 * 0x452bd0 or 0x452c80. The step reads the player's state byte (+0x4cd) and +0x3c4 (p) and stores
 * the dwords +0x4d0, +0x4d4 and +0x4d8: state 1 sets (0, 0, 1) for p = 1 and (1, 0, 1) for p = 2;
 * state 2 sets (1, 1, 1) for p = 1; state 3 sets (0, 0, 1) for p = 1; state 4 sets (1, 1, 1) for
 * p = 1; all others (0, 0, 0). It binds the handler to the player (0x4ac8f0), calls slot 1 of the
 * player's board and plays sound 9 (the dword at 0x4f81a4, 0x43c0e0); the result is that of the
 * sound. entry_ebx is the caller's ebx; the step's ebx is its low byte replaced by the state
 * byte until +0x3c4 is read. */
/* Original variants 0x452a30, 0x452b00, 0x452bb0, 0x452c60:
 * Complete callable handlers verified by tools/verify_bonus_effects.py;
 * the recovered table or selector supplies the parameters for each entry point. */
uint32_t vertrix_effect_arm_handler(const VertrixEffectServices *services, uint32_t player,
                                    uint32_t entry_ebx, unsigned index);

/* The handlers 0x452a50, 0x452b20, 0x452bd0 and 0x452c80 (which 0 to 3; eax = player) armed by the
 * step above. With +0x4d0, +0x4d4 and +0x4d8 all zero and +0x3c4 equal to one, 0x43a5f0 runs with
 * the opponent's +0x3b4 and three stack arguments (0x452a50 and 0x452bd0: edx and ebx -1, ecx 6,
 * stack 0, 0, 1; 0x452b20 and 0x452c80: 6, 6, 6, stack 1, 1, 1); 0x452a50 does the same with edx 6,
 * ebx -1, ecx 6, stack 1, 0, 1 for +0x3c4 equal to two. Slot 1 of the board follows; only when all
 * three dwords were zero 0x43bbf0 runs on the player and its result is returned, otherwise the
 * result of the slot. */
/* Original variants 0x452a50, 0x452b20, 0x452bd0, 0x452c80:
 * Complete callable handlers verified by tools/verify_bonus_effects.py;
 * the recovered table or selector supplies the parameters for each entry point. */
uint32_t vertrix_effect_armed_handler(const VertrixEffectServices *services, uint32_t player,
                                      uint32_t entry_ebx, unsigned which);

/* Original 0x452d10 (eax = player): 0x43b720 on the opponent with the negated +0x3c8 of the player.
 * Result 1 plays sound 5 and calls 0x43ac00, anything else calls 0x43acd0; then slot 1 and
 * 0x43bbf0. */
uint32_t vertrix_effect_progress_update_gate(const VertrixEffectServices *services,
                                             uint32_t player);

/* Original 0x452d70 (eax = player): compares the player's +0x17c (a) with the opponent's (b), both
 * unsigned. Equal: 0x43acd0 only. Otherwise 0x43acd0 (a < b) or 0x43ac00 (a > b), then 0x43b810 on
 * the player with b and on the opponent with a, and sound 11 for the opponent. Then slot 1 of the
 * board and 0x43bbf0. */
uint32_t vertrix_effect_progress_compare(const VertrixEffectServices *services, uint32_t player);

/* Original 0x453460 (eax = player): 0x436fe0 on the player's board (edx = entry_edx), then 0x437060
 * with the player's +0x3e0. Result 1 plays sound 11 (0x4f81ac) and binds 0x4534e0 (0x4ac8f0);
 * anything else calls 0x43acd0 and makes the handler end with 0x43bbf0. Slot 1 of the board comes
 * between. Returns 0x43bbf0 in the second case, else the result of the slot. */
uint32_t vertrix_effect_stone_arm(const VertrixEffectServices *services, uint32_t player,
                                  uint32_t entry_edx);

/* Original 0x4534e0 (eax = player): when 0x42eca0 and 0x42ecc0 (board, 0x44c860) are both non-zero,
 * 0x4371b0 runs with the player's +0x3e0. Result 1 binds 0x453570 (0x4ac8f0) and plays sound 5
 * (0x4f8194); any other result makes the handler end with 0x43bbf0 after slot 1 of the board. With
 * a zero test the result of the slot is returned. */
uint32_t vertrix_effect_stone_apply(const VertrixEffectServices *services, uint32_t player);

/* Original 0x453570 (eax = player): when 0x42eca0 and 0x42ecc0 are both non-zero, 0x42ebe0 runs on
 * the board and the handler ends with 0x43bbf0 after slot 1; otherwise it returns the slot's
 * result. */
uint32_t vertrix_effect_stone_clear(const VertrixEffectServices *services, uint32_t player);

/* The attack handlers that bind a follow-up handler to the opponent: 0x453c00, 0x453f40, 0x454250,
 * 0x454560, 0x4547b0, 0x4549d0, 0x454c30, 0x454e90, 0x455020, 0x455b20, 0x455ca0 and 0x45b9c0
 * (eax = player). Each runs its calls in order (ebx the player, ecx the opponent, edx carried from
 * call to call, the entry edx for the first when set_edx is zero), the last being 0x4ac8f0 of the
 * handler token on the opponent, then copies a dword of the player to the opponent (and clears
 * another), sets the dwords +0xb80, +0xb84 and +0xb88 (and +0xb90 to zero when clear_b90) of the
 * opponent board, calls slot 1 of the player's board and returns 0x43bbf0 on the player (edx the
 * carried edx, ecx the vtable). Zero when an object does not resolve. */
typedef struct
{
    uint32_t target;
    int on_opponent;
    int set_edx;
    uint32_t edx;
} VertrixAttackCall;

typedef struct
{
    uint32_t routine;
    uint32_t handler;
    uint32_t source;
    uint32_t destination;
    uint32_t cleared;
    int clear_b90;
    unsigned count;
    VertrixAttackCall calls[8];
} VertrixAttack;

#define VERTRIX_ATTACK_COUNT 12
extern const VertrixAttack vertrix_attacks[VERTRIX_ATTACK_COUNT];

/* Original variants 0x453f40, 0x454250, 0x454560, 0x4547b0, 0x4549d0, 0x454c30, 0x454e90, 0x455020,
 * 0x455b20, 0x455ca0, 0x45b9c0: Complete callable handlers verified by
 * tools/verify_bonus_effects.py; the recovered table or selector supplies each entry points
 * parameters. */
uint32_t vertrix_effect_attack(const VertrixEffectServices *services, uint32_t player,
                               uint32_t entry_edx, const VertrixAttack *attack);

/* The check-and-bind handlers 0x4554a0, 0x455600, 0x455670, 0x455790, 0x4558e0 and 0x455a00
 * (eax = player). The two checks run on the player's board with the entry edx (first, second);
 * a second result of 1 plays sounds and binds the follow-up handler token to the player, anything
 * else calls 0x43acd0 and makes the handler end with 0x43bbf0 on the player after slot 1 of the
 * board (edx the vtable). Kinds: VERTRIX_CHECK_FIELD plays sound 11 (0x4f81ac); VERTRIX_CHECK_BOARD
 * plays sounds 1 (0x4f8184) and 12 (0x4f81b0), binds the token and sets the board's +0xb8c to one;
 * VERTRIX_CHECK_SLIDE does the same with the register roles of the board and the player swapped,
 * and calls 0x4ac7b0 with the table entry 0x4f7c78[dword 0x532bbc] and 0x4ac510 on the board
 * before +0xb8c. Returns 0x43bbf0 when it ended with it, else the result of slot 1. */
typedef enum
{
    VERTRIX_CHECK_FIELD,
    VERTRIX_CHECK_BOARD,
    VERTRIX_CHECK_SLIDE
} VertrixCheckKind;

typedef struct
{
    uint32_t routine;
    uint32_t first;
    uint32_t second;
    VertrixCheckKind kind;
    uint32_t token;
} VertrixCheckBind;

#define VERTRIX_CHECK_BIND_COUNT 6
extern const VertrixCheckBind vertrix_check_binds[VERTRIX_CHECK_BIND_COUNT];

/* Original variants 0x4554a0, 0x455600, 0x455670, 0x455790, 0x4558e0, 0x455a00:
 * Complete callable handlers verified by tools/verify_bonus_effects.py;
 * the recovered table or selector supplies the parameters for each entry point. */
uint32_t vertrix_effect_check_bind(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_edx, const VertrixCheckBind *check);

/* Original 0x455510 (eax = player): when 0x42eca0 and 0x42ecc0 (board, 0x44c860) are both
 * non-zero, plays sound 1, calls 0x437460 on the board with the token 0x455580 and binds the same
 * token to the player (0x4ac8f0). Slot 1 of the board is called last and its result returned. */
uint32_t vertrix_effect_field_bind(const VertrixEffectServices *services, uint32_t player);

/* Original 0x455e50 (eax = player): 0x438910 on the player's board with the player's +0x3e4 and a
 * zero count (the player's +0x444 is cleared first) decides. Result 1: 0x4ac7b0 with the table
 * entry 0x4f7cfc[dword 0x532bbc], the word 0x4f7d08[dword 0x532bbc] stored at the board's +0x1a,
 * the board's +0x58 cleared, 0x4ac510 on the board, the handler token 0x455f10 bound to the player
 * (0x4ac8f0), then 0x43d2b0 on the player and 0x4300b0 on the board. Anything else calls 0x43acd0
 * and makes the handler end with 0x43bbf0. Slot 1 of the board comes between. */
uint32_t vertrix_effect_slide_begin(const VertrixEffectServices *services, uint32_t player);

/* Original 0x455f10 (eax = player; edx the caller's): 0x4ac500, 0x4ac520 on the board (result 1
 * adds 0x4ac5b0), then 0x430090. Result 1 plays sound 2 (0x4f8188) and binds 0x455f80. Returns the
 * result of slot 1 of the board. */
uint32_t vertrix_effect_slide_wait(const VertrixEffectServices *services, uint32_t player,
                                   uint32_t entry_edx);

/* Original 0x455f80 (eax = player; edx and ebx the caller's): the board's +0x58 advances by
 * 0x4ac540 times the high half of its +0x18 when 0x4ac520 reports one. Below 24 (signed)
 * 0x42f2e0 runs on the board; otherwise 0x42f760, the player's +0x444 grows by one, +0x58 is
 * reduced below 24 by repeated 24s, and 0x438910 with +0x3e4 and the count decides: non-zero
 * plays sound 2, zero calls 0x430100 with 0x456060 and binds 0x456060. Returns the result of slot
 * 1 of the board. */
uint32_t vertrix_effect_slide_advance(const VertrixEffectServices *services, uint32_t player,
                                      uint32_t entry_ebx, uint32_t entry_edx);

/* Original 0x456060 (eax = player; ebx the caller's): 0x4ac500, 0x4ac520 (result 1 adds 0x4ac5b0)
 * and 0x430090 on the board; a 0x430090 result of 1 makes the handler end with 0x43bbf0 on the
 * player after slot 1 of the board, otherwise the slot's result is returned. */
uint32_t vertrix_effect_slide_end(const VertrixEffectServices *services, uint32_t player,
                                  uint32_t entry_ebx);

/* The follow-up handlers 0x453c90, 0x453fd0 and 0x4542e0 (eax = player). The check callee runs on
 * the player's board with edx the player's dword at first_offset and ebx the one at second_offset.
 * Result 1 calls 0x4ac7b0 with the table entry dword_table[dword 0x532bbc], stores the word
 * word_table[dword 0x532bbc] at the board's word_offset, clears the board's +0x58, calls 0x4ac510
 * with the token, binds the token to the player (0x4ac8f0) and plays sound 2 (0x43c0e0). Anything
 * else makes the handler end with 0x43bbf0 on the player. Slot 1 of the board comes between. */
typedef struct
{
    uint32_t routine;
    uint32_t check;
    uint32_t first_offset;
    uint32_t second_offset;
    uint32_t dword_table;
    uint32_t word_table;
    uint32_t word_offset;
    uint32_t token;
} VertrixSlideStart;

#define VERTRIX_SLIDE_START_COUNT 3
extern const VertrixSlideStart vertrix_slide_starts[VERTRIX_SLIDE_START_COUNT];

/* Original variants 0x453c90, 0x453fd0, 0x4542e0:
 * Complete callable handlers verified by tools/verify_bonus_effects.py;
 * the recovered table or selector supplies the parameters for each entry point. */
uint32_t vertrix_effect_slide_start(const VertrixEffectServices *services, uint32_t player,
                                    const VertrixSlideStart *start);
#endif
