#ifndef VERTRIX_PLAYER_ACTIONS_H
#define VERTRIX_PLAYER_ACTIONS_H
#include "actor_gate.h"
#include "particle_spawn.h"
#include "player_slots.h"
/* Actions of a player object: it embeds an event stack at +0x19c and refers to its board object
 * through the dword +0x15c. Object handles are original address tokens resolved by the caller. */

/* Original0x43bb60: push an event describing the player on the embedded stack. The record takes
 * bytes +0x4c4 and +0x4c5, dword +0x4c8, byte +0x4cc, dwords +0x194, +0x198, byte +0x4cd and dword
 * +0x154 of the player, and from the board object dwords +0xb80, +0xc0, words +0x12 and +0x1a and
 * dwords +0xb84, +0xb88. A full stack drops the event (the original returns without storing).
 * Returns zero when storage is short or the board does not resolve. */
int vertrix_player_push_event(void *player, size_t size, VertrixObjectStorage resolve,
                              void *context);

/* Original0x43b7c0: draw levels below 10 until one differs from the current level (dword +0x17c),
 * then set it with 0x43b810. Returns the result of vertrix_player_set_level, or -1 when storage is
 * short. */
int vertrix_player_randomize_level(void *player, size_t size, VertrixSpawnDraw draw,
                                   void *draw_context, VertrixLevelNotify notify,
                                   void *notify_context);

/* State changes of a player (byte +0x4cc) that push an event and switch the handler token at
 * +0x154. The opponent is the object whose handle is the dword +0x3b0. All return zero when storage
 * is short or an object does not resolve; the changes of earlier steps remain, as in the original.
 */

/* Original0x43bc90: when the opponent's byte +0x4c4 is not 1 and its byte +0x4cc is 1 or 4, push
 * the event, set +0x4cc = 5 and handler 0x452070. *changed tells whether that happened. */
int vertrix_player_enter_452070(void *player, size_t size, VertrixObjectStorage resolve,
                                void *context, uint32_t *changed);

/* Original0x43bce0: push the event, set +0x4cc = 5 and handler 0x452370. */
int vertrix_player_enter_452370(void *player, size_t size, VertrixObjectStorage resolve,
                                void *context);

/* Original0x43ccb0: when the opponent's byte +0x4cc is 1, push the event, set +0x4cc = 5 and
 * handler 0x4520b0. *changed tells whether that happened. */
int vertrix_player_enter_4520b0(void *player, size_t size, VertrixObjectStorage resolve,
                                void *context, uint32_t *changed);

/* Original0x43bd00: set +0x4cc = 4 and handler 0x4523d0 on the player; then push the event for the
 * opponent and set its +0x4cc = 4 and handler 0x4523b0. */
int vertrix_player_enter_4523d0(void *player, size_t size, VertrixObjectStorage resolve,
                                void *context);

/* The three globals 0x540f80, 0x540f78 and 0x540f7c the original leaves behind in 0x43b6a0. */
typedef struct
{
    uint32_t selector;
    uint32_t low;
    uint32_t width;
} VertrixPlayerDrawGlobals;

/* Original0x43b6a0: pick a value from the tables at 0x4f8d38 and 0x4f8d84. selector =
 * 0x4f8d38[dword +0x488 of the player]; the low bound is the dword at 0x4f8d84 + 40 * low_row +
 * 240 * level + 4 * selector and the width the same with width_row (level is the original dword
 * 0x532bbc). The result is low (16 bits) plus a draw below width (16 bits), or low alone when width
 * is zero (the original 0x482770). Tables are read through read. Returns zero when the player is
 * short or a table cannot be read. */
int vertrix_player_draw_table_value(const void *player, size_t size, uint32_t low_row,
                                    uint32_t width_row, uint32_t level, VertrixMemoryRead read,
                                    void *read_context, VertrixSpawnDraw draw, void *draw_context,
                                    VertrixPlayerDrawGlobals *globals, uint32_t *result);
#endif
