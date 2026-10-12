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

/* Original 0x4af560 (eax = actor): paint the actor. Unless its +0x134 is 0, the draw scale
 * (0x5bb738) is 0, or nothing would change (opacity 0x5bc00e 0, blending 0x5bb739 on, no clip
 * 0x5bc002, the image format 0x5bc000 the target's 0x5bb730): the flags (0x4af370), rule
 * (0x4af2a0), traversal (0x4af530), direction (0x4af2e0) and mirror index (0x4af340) choose from
 * the tables at 0x4ff024 (the pixel operation, kept at 0x5bb72c), 0x4ff6c4 (the source, as ebx),
 * 0x4ff684 (the draw routine) and, for a plain copy, 0x4ff5e4 or the helper routines 0x4ff604
 * (actor +0x150 set). Otherwise 0x4ae250 prepares the state and the draw routine runs (eax the
 * source). With +0x140 1, 0x4ab200 marks the spot. With +0x110 1 the outline follows: 0x47c520
 * (eax [0x5bc010], edx 0x5b9c60, 7 stack arguments) draws the clip box 1 and 2 pixels in (colours
 * +0x118 and +0x114), or the box itself in +0x118 when 0x5bbffe is 2. The table row is the depth
 * 0x5bb733 (4, 2, 1, 0 as 0 to 3; ecx otherwise). Returns the last call's or test's eax; edx is
 * unchanged. */
uint32_t vertrix_port_actor_paint(PORT_SIGNATURE);

/* Original 0x4ac540: the actor's elapsed time (+0xbc) in whole steps of its time scale (+0xc0, 1
 * when 0), unsigned. edx is unchanged. */
uint32_t vertrix_port_actor_steps(PORT_SIGNATURE);

/* Original 0x4ac640: the actor's progress (+0xdc) in whole steps of its progress scale (+0xe0, 1
 * when 0), unsigned. edx is unchanged. */
uint32_t vertrix_port_actor_progress_steps(PORT_SIGNATURE);

/* Original 0x4ac5b0: take the whole steps (0x4ac540, edx the actor, ecx the scale) out of the
 * actor's elapsed time, leaving the remainder (0 when they are not below it). Returns the steps'
 * time; edx is unchanged. */
uint32_t vertrix_port_actor_steps_consume(PORT_SIGNATURE);

/* Original 0x4ac390: whether the actor's counter (+0xcc) has reached its limit (+0xd0, unsigned).
 * edx is unchanged. */
uint32_t vertrix_port_actor_counter_done(PORT_SIGNATURE);

/* Original 0x4ac370: add the frame time (0x5bd834) to the actor's counter (+0xcc). Returns the
 * actor; edx is unchanged. */
uint32_t vertrix_port_actor_counter_advance(PORT_SIGNATURE);

/* Original 0x4ac620: whether the actor's progress (+0xdc) has reached its scale (+0xe0,
 * unsigned). edx is unchanged. */
uint32_t vertrix_port_actor_progress_done(PORT_SIGNATURE);

/* Original 0x4ac600: add the frame time (0x5bd834) to the actor's progress (+0xdc). Returns the
 * actor; edx is unchanged. */
uint32_t vertrix_port_actor_progress_advance(PORT_SIGNATURE);

/* Original 0x4ae110 (eax = actor, dx, bx = x, y, ecx = width, stack = height): store the actor's
 * span (+0x128 words, +0x12c and +0x130 dwords). Returns the actor; edx is unchanged. */
uint32_t vertrix_port_actor_set_span(PORT_SIGNATURE);

/* Original 0x4ac6b0: take the whole progress steps (0x4ac640, edx the actor, ecx the scale) out of
 * the actor's progress, leaving the remainder (0 when they are not below it). Returns the steps
 * taken; edx is unchanged. */
uint32_t vertrix_port_actor_progress_consume(PORT_SIGNATURE);

/* Original 0x4ad1c0 (eax = actor, edx, ebx = distances, ecx = x out, stack = y out): the actor's
 * angle (the word +0x24) turned into offsets: the x distance times the cosine table 0x59939c and
 * the y distance times the sine table 0x598dfc (16.16 products from 0x4849e0), whole parts stored.
 * Returns the y offset, edx the y address. */
uint32_t vertrix_port_actor_polar_offset(PORT_SIGNATURE);

/* Original 0x4ac700: clear the actor's frame counter (+0xb8). Returns the actor; edx is
 * unchanged. */
uint32_t vertrix_port_actor_clear_frame_counter(PORT_SIGNATURE);

/* Original 0x4ac380: clear the actor's counter (+0xcc). Returns the actor; edx is unchanged. */
uint32_t vertrix_port_actor_clear_counter(PORT_SIGNATURE);

/* Original 0x4ac8d0 (eax = actor, edx = resource): clear its counters (0x4ac380, 0x4ac700, ecx the
 * actor) and store the resource (+0xb0, the edx those leave). Returns the last call's eax and
 * edx. */
uint32_t vertrix_port_actor_attach(PORT_SIGNATURE);

/* Original 0x4ad060 (eax = actor, edx = steps): turn the actor's angle (the word +0x24) by its
 * turn (+0x28) that many times, wrapped into 0 to 359 (a negative angle as its unsigned word plus
 * 360). Returns 1 when it never wrapped, else 0, also kept at 0x5bb5f4 with the steps taken at
 * 0x5bb5f8 (left when there is no turn). edx is the last angle read or remainder. */
uint32_t vertrix_port_actor_turn(PORT_SIGNATURE);

/* Original 0x4b68a0 (eax = text actor): lay its text out: 0x4ae150, then 0x4408e0 with the layout
 * fields (+0x15c to +0x168), the scale byte (+0x44) and four locals for the results, which become
 * the actor's position (+0xe, +0x16) and size (+0xf4, +0xf8). Returns the height; edx is
 * unchanged. */
uint32_t vertrix_port_actor_text_layout(PORT_SIGNATURE);

/* Original 0x4b6890: 0x4ae010 with the same registers. */
uint32_t vertrix_port_actor_spot_draw_call(PORT_SIGNATURE);

/* Original 0x443260 (eax = actor): put the actor at the saved position (words 0x558944 and
 * 0x558946), or off screen at 0x7d00 when 0x558958 is set, then tick its animation (0x4ac1f0)
 * and look up its image (0x4ac8a0), each given the edx the previous call leaves. Returns the last
 * call's eax; edx is unchanged. */
uint32_t vertrix_port_actor_place_saved(PORT_SIGNATURE);

/* Original 0x4b5560 (eax = actor): 0x4adf70, then the actor's hook (+0x154) when it has one (on
 * the edx that leaves). Returns the last call's eax; edx is unchanged. */
uint32_t vertrix_port_actor_update_hook(PORT_SIGNATURE);

/* Original 0x4b6560 (eax = timer): whether it is running: not armed (+0x174 is 0), or its count
 * (word +0x17a) not past its limit (word +0x17c). edx is unchanged. */
uint32_t vertrix_port_timer_running(PORT_SIGNATURE);

/* Original 0x4b65d0 (eax = actor, edx = text, bl = alignment, cx and the three stack words = the
 * box): set the actor's text (+0x15c, 0x4ca370), alignment and box, lay it out (0x4408e0) and
 * store its place (+0xe, +0x16) and size (+0xf4, +0xf8). Returns the height, edx from the layout.
 */
uint32_t vertrix_port_actor_set_text(PORT_SIGNATURE);

/* Original 0x4b6800 (eax = actor, edx = surface): draw the actor's text (0x440ca0) at its place,
 * then, unless its timer is running (0x4b6560), its cursor (0x440fc0, with the timer byte +0x178
 * and word +0x17a). Returns the last call's eax and edx. */
uint32_t vertrix_port_actor_draw_text(PORT_SIGNATURE);

/* Original 0x4b5550: calls 0x4b17b0 with the same registers. */
uint32_t vertrix_port_actor_paint_call(PORT_SIGNATURE);

/* Original 0x4b17b0 (eax = actor, edx = target surface): set the target (0x5bc010) and, when the
 * gate 0x4b17e0 (edx the actor's +0x144) passes, paint (0x4b1fa0). Returns the last call's eax and
 * edx. */
uint32_t vertrix_port_actor_paint_target(PORT_SIGNATURE);

/* Original 0x4b3340 (eax = actor, edx = surface): paint it (0x4b5550), then its attached actor
 * (+0x160) through its table's draw (+8). Returns the last call's eax and edx. */
uint32_t vertrix_port_actor_paint_attached(PORT_SIGNATURE);

/* Original 0x4b3380 (eax = actor): its table's (+0x158) draw (+8). */
uint32_t vertrix_port_actor_draw_call(PORT_SIGNATURE);

/* Original 0x4ac7b0 (eax = actor, edx = rate): store the rate times 12 as the time scale (+0xc0).
 * Returns that; edx is unchanged. */
uint32_t vertrix_port_actor_set_time_scale(PORT_SIGNATURE);

/* Original 0x45cdc0 (eax = object): run 0x45cff0 when its state (+0x58) is 1. */
uint32_t vertrix_port_object_run_active(PORT_SIGNATURE);

/* Original 0x45cff0 (eax = actor): a wandering actor's step: advance its progress (0x4ac600) and,
 * when a step is due (0x4ac620), consume it (0x4ac640, 0x4ac6b0) and turn (0x4ad060); when the
 * turn wrapped it picks a new turn (+0x30) and step count (0x4ac860, 5 plus a random below 5,
 * 0x4826c0 with the generator 0x598d30). It then moves by the polar offset of its speed (+0x30,
 * 0x4ad1c0) from its origin (+0xa) and re-places itself (0x4adfe0) when it moved. Registers but
 * eax are unchanged. */
uint32_t vertrix_port_actor_wander(PORT_SIGNATURE);

/* Original 0x43e740 (edx = actor): set up a star of the title: the screen size (0x5b9c8e, 0x5b9c90)
 * and its half kept at 0x541014 to 0x54101a, the actor attached to 0x544c10 (0x4ac8d0) with
 * animation 15 (0x4ac710), image 1 (0x4ac8a0) and the time scale (0x4ac7b0), and a random spot
 * around the centre (times 150), speed 200 and a random step of 1 to 3. Returns the step. */
uint32_t vertrix_port_star_setup(PORT_SIGNATURE);

/* Original 0x4ac3b0 (eax = actor): its counter (+0xcc) over its limit (+0xd0, 1 when 0). edx is
 * unchanged. */
uint32_t vertrix_port_actor_counter_steps(PORT_SIGNATURE);

/* Original 0x45ce50 (eax = actor): a title actor's frame: run it (0x45cdc0), advance its counter
 * (0x4ac500) and when due (0x4ac520) consume it (0x4ac5b0); in state 0 it is re-attached to
 * 0x546688 (0x4ac8d0, 0x4ac8a0) and re-placed (0x4adfe0). Its update becomes 0x45ceb0 (0x4ac8f0).
 * Registers but eax are unchanged. */
uint32_t vertrix_port_title_actor_frame(PORT_SIGNATURE);

/* Original 0x4b6200 (eax = list): call each actor's update (its table's +4) with edx its number
 * from 1. Registers but eax are unchanged. */
uint32_t vertrix_port_actor_list_update(PORT_SIGNATURE);

/* Original 0x4b6170 (eax = list, edx = argument): call each actor's table entry +0x14 with the
 * argument (ebx its number from 1, ecx its offset). Returns the last call's eax; edx is the count
 * when there were actors. */
uint32_t vertrix_port_actor_list_call14(PORT_SIGNATURE);

/* Original 0x4b6120: as 0x4b6170 with the table entry +0x10. */
uint32_t vertrix_port_actor_list_call10(PORT_SIGNATURE);

/* Original 0x4b60c0 (eax = list, edx, ebx = arguments): call each actor's table entry +0xc with the
 * arguments. Returns the last call's eax; edx is the count when there were actors. */
uint32_t vertrix_port_actor_list_call0c(PORT_SIGNATURE);

/* Original 0x4b23c0 (eax = array, edx = count): call each actor's update (its table's +4) in an
 * array of actor pointers, skipping empty slots. edx is the slot pointer after the last. */
uint32_t vertrix_port_actor_array_update(PORT_SIGNATURE);

/* Original 0x4b5500 (eax = actor): whether its input key (the word +0x15c) was pressed: when the
 * input 0x54d640 has it ready (0x476480) the press is taken (0x4762e0) and 1 returned, else 0. edx
 * is unchanged. */
uint32_t vertrix_port_actor_key_pressed(PORT_SIGNATURE);

/* Original 0x4ad530 (eax = actor, edx = steps): move the value (word +0x48) towards the target
 * (+0x4a) by the steps times the speed (+0x4c), stopping at it. Returns whether it is not there
 * yet; edx is the target word over the sign of the target. */
uint32_t vertrix_port_actor_approach(PORT_SIGNATURE);

/* Original 0x45c2f0 (eax = button): a menu button's input: on a click (input 0x54d640 key 0x74,
 * 0x476480 then 0x4764a0) a hit at the saved pointer (0x558944, 0x558946, off screen while hidden,
 * 0x4b0b70) sets its update to 0x45c600 (0x4ac8f0); otherwise its own key (0x4b5500) presses it
 * (0x4ac910 with 0x45c7e0, 0x532a48 set). Registers but eax are unchanged. */
uint32_t vertrix_port_menu_button_input(PORT_SIGNATURE);

/* Original 0x45c3c0 (eax = button): a menu button's frame: when its counter is due it grows back
 * (0x4ac540, 0x4ac5b0, the approach 0x4ad530 to 0 at speed 5); under the pointer it is lit (+0x52
 * 10, value 0x23, update 0x45c480), else +0x52 is 9; then its input (0x45c2f0). Registers but eax
 * are unchanged. */
uint32_t vertrix_port_menu_button_frame(PORT_SIGNATURE);

/* Original 0x4ac740 (eax = actor): count a frame (+0xb8). Registers are unchanged. */
uint32_t vertrix_port_actor_frame_count(PORT_SIGNATURE);

/* Original 0x4ac760 (eax = actor): whether its frame count (+0xb8) reached its resource's frame
 * count (0x487860 of +0xb0). edx is unchanged. */
uint32_t vertrix_port_actor_frames_done(PORT_SIGNATURE);

/* Original 0x4ad6e0 (eax = actor, edx = steps): move the value (+0x58) towards the goal (+0x5c)
 * by the steps times the speed (+0x60), stopping at it. Returns whether it is not there yet; edx
 * is the goal. */
uint32_t vertrix_port_actor_step_value(PORT_SIGNATURE);

/* Original 0x4ac420 (eax = actor): take the whole counter steps (0x4ac3b0) out of its counter
 * (+0xcc), clearing it when they are not below it. Returns the steps times the limit; edx is
 * unchanged. */
uint32_t vertrix_port_actor_counter_consume(PORT_SIGNATURE);

/* Original 0x45d100 (eax = actor): a wandering actor's frame (0x45cff0) that, when its counter is
 * due (0x4ac500, 0x4ac520), resets it (0x4ac510), restores +0x64 from +0x68 and sets its update to
 * 0x45d1a0 (0x4ac8f0). Registers but eax are unchanged. */
uint32_t vertrix_port_wanderer_frame(PORT_SIGNATURE);

/* The layer lists 0x54671c (back), 0x546730 (middle) and 0x546744 (front): update every actor
 * (0x4b6200), or call each one's table entry +0x14 (0x4b6170) or +0x10 (0x4b6120) with eax, or
 * +0xc (0x4b60c0) with eax and edx. */
uint32_t vertrix_port_layer_back_update(PORT_SIGNATURE);   /* 0x471a70 */
uint32_t vertrix_port_layer_back_call14(PORT_SIGNATURE);   /* 0x471a50 */
uint32_t vertrix_port_layer_back_call10(PORT_SIGNATURE);   /* 0x471a40 */
uint32_t vertrix_port_layer_back_call0c(PORT_SIGNATURE);   /* 0x471a20 */
/* Original 0x471b00: the layer wrapper. */
uint32_t vertrix_port_layer_middle_update(PORT_SIGNATURE);
/* Original 0x471b60: the layer wrapper. */
uint32_t vertrix_port_layer_middle_call14(PORT_SIGNATURE);
/* Original 0x471b50: the layer wrapper. */
uint32_t vertrix_port_layer_middle_call10(PORT_SIGNATURE);
/* Original 0x471b30: the layer wrapper. */
uint32_t vertrix_port_layer_middle_call0c(PORT_SIGNATURE);
uint32_t vertrix_port_layer_front_update(PORT_SIGNATURE);  /* 0x471a80 */
uint32_t vertrix_port_layer_front_call14(PORT_SIGNATURE);  /* 0x471ae0 */
uint32_t vertrix_port_layer_front_call10(PORT_SIGNATURE);  /* 0x471ad0 */
uint32_t vertrix_port_layer_front_call0c(PORT_SIGNATURE);  /* 0x471ab0 */

/* Original 0x478460 (eax = actor): copy its place (+0x48, +0x4a) to +0x4c, +0x4e. Registers are
 * unchanged. */
uint32_t vertrix_port_actor_keep_place(PORT_SIGNATURE);

#endif
