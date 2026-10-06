#ifndef VERTRIX_OBJECT_EVENTS_H
#define VERTRIX_OBJECT_EVENTS_H
#include "block_factory.h"
#include "call_glue.h"
#include "player_slots.h"
#include "random.h"
#include "sfx_dispatch.h"
#include <stddef.h>
#include <stdint.h>

enum
{
    VERTRIX_EVENT_RELATED = 0x3b0,
    VERTRIX_EVENT_RELATED_DONE = 0x4c5,
    VERTRIX_EVENT_RELATED_STATE = 0x464,
    VERTRIX_EVENT_HANDLER_4513D0 = 0x4513d0,
    VERTRIX_EVENT_HANDLER_450FF0 = 0x450ff0,
    VERTRIX_EVENT_HANDLER_4522C0 = 0x4522c0,
    VERTRIX_EVENT_HANDLER_451AA0 = 0x451aa0,
    VERTRIX_EVENT_HANDLER_4520F0 = 0x4520f0,
    VERTRIX_EVENT_BONUS_START = 0x451a60,
    VERTRIX_EVENT_COUNT = 0x188,
    VERTRIX_EVENT_SAVED_COUNT = 0x3f0,
    VERTRIX_EVENT_SAVED_STEP = 0x3f4,
    VERTRIX_EVENT_RNG_STATE = 0x598d30,
    VERTRIX_EVENT_SIDE = 0x64,
    VERTRIX_EVENT_SIDE_BYTE = 0x58,
    VERTRIX_EVENT_DRAW_BYTE = 0x52,
    VERTRIX_EVENT_OFFSET_WORD = 0xc,
    VERTRIX_EVENT_CURSOR = 0x15c,
    VERTRIX_EVENT_TABLE_SLOT = 0x158,
    VERTRIX_EVENT_OPPONENT_STATE = 0x4cc,
    VERTRIX_EVENT_OPPONENT_STEP = 0x3f4,
    VERTRIX_EVENT_CURSOR_FLAG0 = 0xb80,
    VERTRIX_EVENT_CURSOR_FLAG1 = 0xb84,
    VERTRIX_EVENT_CURSOR_FLAG2 = 0xb88,
    VERTRIX_EVENT_VIEW_SETUP = 0x43bbf0,
    VERTRIX_EVENT_ENTER_452370 = 0x43bce0,
    VERTRIX_EVENT_ENTER_4523D0 = 0x43bd00
};

/* Original 0x457810: after 0x4ac370 and 0x4ac390 (which must return one), run 0x4ac3b0, 0x4ac380
 * and 0x4ac810, flip the dword at +0x64, draw 13 into the byte at +0x52, run 0x4ac950 on the
 * 0x43f420 verdict for the signed low byte of the flipped side and the byte at +0x58, then draw 11
 * minus five into the word at +0xc. Returns the eax of the last call minus five, or the first
 * verdict when it is not one. */
uint32_t vertrix_object_flip_side(const VertrixCalls *calls, uint32_t object, void *storage,
                                  size_t size);

/* Original 0x450f80: zero when the related object (+0x3b0) has its byte at +0x4c5 set; otherwise
 * run 0x4ac8f0 with 0x4513d0 and, unless the related state is one and the object byte at +0x4c5 is
 * clear, 0x43bb00, then set *flag (global 0x532a3c) and return one. */
uint32_t vertrix_object_start_hold(const VertrixCalls *calls,
                                   const VertrixFactoryServices *services, uint32_t object,
                                   void *storage, size_t size, uint32_t *flag);

/* Original 0x452250: 0x4ac8f0 with 0x450ff0 and 0x43bae0 on zero; when the related object's byte
 * at +0x4c5 is set and the count at +0x188 is not zero, 0x43bb60, save the count at +0x3f0 with a
 * zero step at +0x3f4, 0x43bae0 on four and 0x4ac8f0 with 0x4522c0. */
uint32_t vertrix_object_arm_hold(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                 uint32_t object, void *storage, size_t size);

/* Supplied boundary for the cursor view method called as [cursor + 0x158 + 4]
 * with the cursor handle. The table is the dword at cursor + 0x158. Returns
 * the method's eax, which 0x4522c0 returns unless it takes the 0x43bbf0 tail. */
typedef uint32_t (*VertrixCursorMethod)(uint32_t cursor, uint32_t table, void *context);

/* Original 0x4522c0: when the related object's byte at +0x4c5 is clear, run
 * its cursor method and then 0x43bbf0 on the object. Otherwise, when its byte
 * at +0x4cc is 1 or its dword step at +0x3f4 is not zero, run only the cursor
 * method. Otherwise run 0x43bce0, mark step 1 at +0x3f4 of the object, run
 * 0x43bd00, flag the related cursor words at +0xb80/+0xb84/+0xb88, and run
 * only the cursor method. The upper bytes of ebx at the 0x43bce0/0x43bd00
 * calls are the entry ebx passthrough (zero in the oracle and the Wii
 * call sites); only the low byte is set here. Returns the cursor method's
 * eax, or the 0x43bbf0 eax on the clear-+0x4c5 path. Zero when storage is
 * short or an object does not resolve. */
uint32_t vertrix_object_enter_attack(const VertrixCalls *calls,
                                     const VertrixFactoryServices *services, uint32_t object,
                                     void *storage, size_t size, VertrixCursorMethod method,
                                     void *context);

/* Supplied boundary for the match scan 0x432480. Runs the scan on the
 * cursor with the side byte and fills the four out-words (two flag words,
 * the chain reward and the score multiplier); returns nonzero on a match.
 * The out-words live in the caller's frame in the original. */
typedef int (*VertrixPostLockMatch)(uint32_t cursor, uint8_t side, uint32_t *flag_a,
                                    uint32_t *flag_b, uint32_t *reward, uint32_t *mult,
                                    void *context);

/* Supplied boundary for the original event-machine 0x4ac8f0. Runs the
 * handler token on the player. */
typedef void (*VertrixPostLockEvent)(uint32_t player, uint32_t handler, void *context);

/* Call log for the 0x43c0e0 effect dispatch: the player handle and the
 * effect id. The native runs the real dispatch after logging; the oracle
 * stub logs the same pair. */
typedef void (*VertrixPostLockSfx)(uint32_t player, uint32_t effect, void *context);

/* Supplied tables and globals for the post-lock handler, read live from the
 * executable in the original: four effect ids, the reward-loop effect, the
 * score difficulty, and the difficulty multiplier table. */
typedef struct
{
    uint32_t mode_effect;
    uint32_t chain_effect;
    uint32_t flag_effect;
    uint32_t alt_effect;
    uint32_t loop_effect;
    uint32_t difficulty;
    const uint32_t *mult_table;
    size_t mult_count;
} VertrixPostLockTables;

/* Full boundary set for the post-lock handler below. Randomness, side
 * allocation and object resolution follow the player-side conventions. */
typedef struct
{
    VertrixPostLockMatch match;
    VertrixCursorMethod cursor;
    VertrixPostLockEvent event;
    VertrixPostLockSfx sfx;
    VertrixPostLockTables tables;
    VertrixProgressGlobals *progress;
    VertrixProgressLetter pletter;
    VertrixRefreshNotify refresh;
    VertrixLevelNotify level_notify;
    VertrixSfxPlayCallback sfx_play;
    VertrixProgressWin win;
    VertrixSideAllocate side_alloc;
    VertrixSideDestroy side_destroy;
    VertrixRandom *random;
    VertrixObjectStorage resolve;
    void *context;
} VertrixPostLockServices;

/* Original 0x4517c0: run the match scan; without a match, arm the hold when
 * suppressed, start the bonus when the meter is ready, or spawn normally.
 * With a match, run the mode-0x24 effect plus side reset, the bonus-ready
 * check, the match reward, the score add, the chain counters (effect at
 * exactly 3 and at exactly 6), the flag-gated effects, and the tail event.
 * Every path ends by running the cursor view method and returning its eax.
 * Sub-call results are ignored as in the original; returns 0 when the entry
 * reads fail (storage preserved). */
uint32_t vertrix_object_post_lock(const VertrixCalls *calls, const VertrixFactoryServices *services,
                                  uint32_t object, void *storage, size_t size,
                                  const VertrixPostLockServices *post);

/* Original 0x451920: twin of 0x4517c0 sharing the prologue, the no-match
 * branches, the mode-0x24 prefix, the reward/score/counter sequence and the
 * cursor-method tail, but with no second effect at chain count 6 and a
 * different flag tail: flag_a == 0 plays the alt effect, otherwise the flag
 * effect (flag_b is not consulted). Same services, return and failure
 * contract as vertrix_object_post_lock. */
uint32_t vertrix_object_post_lock_twin(const VertrixCalls *calls,
                                       const VertrixFactoryServices *services, uint32_t object,
                                       void *storage, size_t size,
                                       const VertrixPostLockServices *post);
#endif
