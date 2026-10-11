#ifndef VERTRIX_PORT_ACTOR_H
#define VERTRIX_PORT_ACTOR_H
#include "port.h"

/* Clean ports of the actor routines (port.h). An actor keeps its frame index at +0xb8, its elapsed
 * time at +0xbc, its time scale at +0xc0 and the next actor of its chain at +0x108. Elsewhere an
 * object steps a value at +0x58 toward +0x5c by the speed at +0x60. */

/* Original 0x4ac500 (eax = actor): add the frame time (the global 0x5bd834) to the actor's elapsed
 * time. Returns the actor; edx is unchanged. */
uint32_t vertrix_port_actor_advance_elapsed(PORT_SIGNATURE);

/* Original 0x4ade60 (eax = first actor, edx = the paint argument): for each actor of the chain,
 * 0x4ac8a0 (the image lookup) and then 0x4af8c0 (the paint, edx the argument); both are called
 * with ebx the argument and ecx the actor, and the lookup with edx the paint's edx after the first
 * actor. Returns the last paint's eax and edx (the actor, 0, and edx unchanged for no chain). */
uint32_t vertrix_port_actor_chain_walk(PORT_SIGNATURE);

/* Original 0x4ae140: 0x4ade60 with the same registers. Returns its eax and edx. */
uint32_t vertrix_port_actor_chain_walk_call(PORT_SIGNATURE);

/* Original 0x4af8c0 (eax = actor, edx = the paint argument): store the argument at 0x5bc010 and
 * ask 0x4ae3e0 (edx the actor's +0x144) whether to paint; when it answers non-zero, 0x4af560
 * paints the actor (edx the gate's edx). Both are called with ebx passed on and ecx the actor.
 * Returns the last call's eax and edx. */
uint32_t vertrix_port_actor_chain_paint(PORT_SIGNATURE);

/* Original 0x4ac710 (eax = actor, edx = index): store the frame index. eax and edx are
 * unchanged. */
uint32_t vertrix_port_actor_set_frame_index(PORT_SIGNATURE);

/* Original 0x4ac510 (eax = actor): clear the elapsed time. eax and edx are unchanged. */
uint32_t vertrix_port_actor_clear_elapsed(PORT_SIGNATURE);

/* Original 0x4ac560 (eax = actor): the elapsed time over the time scale as singles: 0x4d81fe on
 * the elapsed time (0x4d74a6) and the scale (0x4d74a6, or 1.0 when that is 0). The calls have ebx
 * passed on and ecx the actor. Returns the quotient; edx is unchanged. */
uint32_t vertrix_port_actor_scaled_time(PORT_SIGNATURE);

/* Original 0x4aca00 (ebx = value, ecx = goal, one stack argument: the speed as a signed integer):
 * move the value toward the goal by the speed converted to a single (0x4d74d1), multiplied by
 * 0x4d8177 with the converter's edx and truncated (0x4d67a8), stopping at the goal (signed
 * comparisons). Returns the new value, with edx the last call's (unchanged at the goal). */
uint32_t vertrix_port_step_toward(PORT_SIGNATURE);

/* Original 0x4ad720 (eax = object): 0x4aca00 on the value +0x58, goal +0x5c and speed +0x60; the
 * result is stored at +0x58. Returns 1 when it differs from the goal (read again after the call)
 * and 0 otherwise, with edx the call's. */
uint32_t vertrix_port_object_step_field(PORT_SIGNATURE);

/* Original 0x4adf20 (eax = actor, dx, bx and cx three 16-bit coordinates, five stack arguments):
 * store the coordinates at +0x08, +0x0a, +0x0c and again at +0x0e, +0x16, +0x1e, and the first
 * four arguments at +0xb0 (the resource), +0xb8 (the frame index), +0xb4 (the image) and +0x154
 * (the hook). Returns the actor, with edx the fourth argument. */
uint32_t vertrix_port_actor_initialize(PORT_SIGNATURE);

/* Original 0x4adf70 (eax = actor): when the global 0x5bb710 is 1, clear the actor's +0x120. eax
 * and edx are unchanged. */
uint32_t vertrix_port_actor_reset_marker(PORT_SIGNATURE);

/* Original 0x4ae150 (eax = first actor): 0x4adf70 (edx the actor) and then 0x4ade20 on the
 * reset's edx. Returns the walk's eax; edx is unchanged. */
uint32_t vertrix_port_actor_chain_update_call(PORT_SIGNATURE);

/* Original 0x4ade20 (eax = first actor): for each actor of the chain, 0x4ad870 (eax and edx the
 * actor, ecx the first actor) and, when the FIRST actor has a hook at +0x154, that hook the same
 * way. The next actor is +0x108 of the edx the last call leaves. Returns the last call's eax (0
 * for no chain); edx is unchanged. */
uint32_t vertrix_port_actor_chain_update(PORT_SIGNATURE);

/* Original 0x4adfb0 (eax = actor): its value: the dword at 0x5bb714 indexed by the signed word at
 * +0x148, or +0x120 when that word is -1. edx is unchanged. */
uint32_t vertrix_port_actor_value(PORT_SIGNATURE);

/* Original 0x4ae0f0 (eax = actor): unless +0x124 is set, the routine at +0x08 of the record at
 * +0x158 (ecx that record). Returns its eax and edx (the actor and edx unchanged otherwise). */
uint32_t vertrix_port_actor_idle_call(PORT_SIGNATURE);

/* Original 0x4ac520 (eax = actor): 1 when the elapsed time has reached the time scale (unsigned),
 * otherwise 0. edx is unchanged. */
uint32_t vertrix_port_actor_elapsed_done(PORT_SIGNATURE);

/* Original 0x4ac130 (eax = actor, edx = mode), the actor's destructor. With mode bit 4, 0x4ccb9f
 * finalizes the actor (edx its type 0x517b10) and 0x4ca040 frees what it returns (edx 0); otherwise
 * the idle record (+0x158) is reset to 0x517af4 and, with mode bit 2, 0x4ca050 frees the actor
 * (ebx 0x4ec1ec) under a guard record in the frame. The calls have ecx the actor. Returns the actor
 * and the last call's edx (the mode when nothing is called). */
uint32_t vertrix_port_actor_base_destroy(PORT_SIGNATURE);

/* Original 0x4ae010 (eax = actor, edx = surface): when the actor's +0x124 and its value (0x4adfb0)
 * are both 1, its +0x138 is 1 and its spot size (+0x12c by +0x130) is not empty, 0x47ce10 draws
 * the spot on the surface (edx 0x4adfb0's edx, ebx and ecx the spot's x and y: the high words of
 * +0x126 and +0x128, stack arguments x, y, width and height); with +0x140 1 it draws it again on
 * the screen's surface ([0x544070]+0x274, edx +0x278). Returns the last eax compared or call's
 * eax, with edx entry ebx before 0x4adfb0 and the last call's after. */
uint32_t vertrix_port_actor_spot_draw(PORT_SIGNATURE);

/* Original 0x4abd70 (eax = actor): reset the actor's fields to their initial values (the table
 * in port_actor.c, stored in the original's order). eax and edx are unchanged. */
uint32_t vertrix_port_actor_reset(PORT_SIGNATURE);

/* Original 0x4ae0c0 (eax = actor): when +0x124 and the actor's value (0x4adfb0, ecx the actor)
 * are both 1, the routine at +0x08 of the record at +0x158 (ebx that record, ecx the actor).
 * Returns the last value compared or the routine's eax, with edx unchanged before 0x4adfb0 and
 * the last call's after. */
uint32_t vertrix_port_actor_value_idle_call(PORT_SIGNATURE);

#endif
