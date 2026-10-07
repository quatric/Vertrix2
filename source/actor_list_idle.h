#ifndef VERTRIX_ACTOR_LIST_IDLE_H
#define VERTRIX_ACTOR_LIST_IDLE_H
#include "board_cells.h"

/* Idle checks over the five actor handle arrays of the original game screen. Each array is a
 * pointer/count global pair (0x546720/0x546724, 0x54675c/0x546760, 0x546748/0x54674c,
 * 0x546734/0x546738, 0x546770/0x546774); this module receives the handles themselves.
 * Objects are resolved through VertrixObjectStorage; an unresolvable object returns 0 and leaves
 * the result untouched. */

/* Original variants 0x471c90, 0x471cd0, 0x471d10, 0x471d50, 0x472360: result 1 when every actor's
 * handler token (+0x154) is zero, else 0. Scanning stops at the first busy actor. */
int vertrix_actor_list_all_idle(const uint32_t *handles, uint32_t count,
                                VertrixObjectStorage resolve, void *context, uint32_t *idle);

/* Original 0x471c40: result 1 when every actor either has owner token +0x14c equal to owner or
 * a zero handler token (+0x154), else 0. */
int vertrix_actor_list_idle_except(const uint32_t *handles, uint32_t count, uint32_t owner,
                                   VertrixObjectStorage resolve, void *context, uint32_t *idle);
#endif
