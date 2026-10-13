#ifndef VERTRIX_PORT_LAYOUT_H
#define VERTRIX_PORT_LAYOUT_H
#include "port.h"

/* Clean ports of the actor layout (port.h). */

/* Original 0x4ad870 (eax = actor): place the actor against its anchor (+0x104, an actor with an
 * image at +0xb4). The anchor's position is clamped to the screen ([0x544070] +0x208 by +0x20c)
 * and its index in the screen's scale map kept at 0x5bb648; the scale is the anchor's +0x44, or
 * with its +0x91 set the screen's (+0x221, or 1 + the map byte when +0x220 is set). The actor's
 * alignment bytes (+0xfc horizontal, +0xfd vertical: 0 centre, 1 to 3 edges) and offsets (+0xfe,
 * +0x100) then give its +0xe, +0x16 and +0x1e from the anchor's image (scaled by sixteenths with
 * the table at 0x5c1b00 when the scale is not 16). The working values live in the globals
 * 0x5bb638 to 0x5bb688; bx, cx, si and di are stored back to 0x5bb666, 0x5bb664, 0x5bb684 and
 * 0x5bb656 as the original leaves them. Returns the actor (the anchor when it has no image); edx
 * is unchanged. */
uint32_t vertrix_port_actor_layout(PORT_SIGNATURE);

/* Original 0x471820(eax = panel, edx = side, ebx = width; stack: an offset, a dword; ret 8): set
 * a panel sliding in sideways: its x (+0xe) moves to +0x10 and its start (+0xe, +0x14) to the
 * left of the screen for side 1, else past its right; +0x16 is copied to +0x18 and +0x1c and the
 * steps (+0x12, +0x1a) are 8. */
uint32_t vertrix_port_ui_slide_sideways(PORT_SIGNATURE);

/* Original 0x484700(eax = x0, edx = y0, ebx = x1, ecx = y1): the heading from the first point to
 * the second in degrees: the distance by Newton's method, the angle from the table lookup of
 * |dx| / distance (0x4849f0, 0x4845d0), mirrored for negative dx and positive dy. Its working
 * values stay at 0x598dd8 to 0x598df8. */
uint32_t vertrix_port_point_heading(PORT_SIGNATURE);

/* Original 0x4b6350(eax = object): construct a labeled box under a guard record: the base object
 * (0x4abd70), its table 0x518404, its label string at +0x15c set to 0x5110b7, its fields cleared
 * with +0x95 = 3 and +0x17a, +0x17c = -100. Returns the box; keeps edx. */
uint32_t vertrix_port_object_construct_labeled_box(PORT_SIGNATURE);

/* Original 0x4b3210(eax = object, edx = text, ebx = x offset, ecx = y offset; two stack arguments,
 * the right and bottom alignment flags): keep the label settings (+0x160 to +0x16c) and draw the
 * label's text at the object's position (0x4b65d0) under a guard record. */
uint32_t vertrix_port_object_place_label(PORT_SIGNATURE);

/* Original 0x4b5420(eax = object, edx = mode): a box destructor: mode 4 destroys an array (element
 * destructor 0x518190); otherwise the table 0x518174 is set and the base destructor 0x4ac130 runs
 * under a guard record, mode 2 freeing it (0x4ca050). */
uint32_t vertrix_port_object_destroy_call(PORT_SIGNATURE);

/* Original 0x4b6460(eax = box, edx = mode): the labeled box destructor: as 0x4b5420 with the table
 * 0x518404 and element destructor 0x518420, the label string (+0x15c) destroyed first
 * (0x4ca210). */
uint32_t vertrix_port_object_destroy_d(PORT_SIGNATURE);

/* Original 0x489fa0(eax = parser, edx = mode): the parser destructor: mode 4 destroys an array
 * (element destructor 0x513f10); otherwise the table 0x517644 (+0x14) is set and, under a guard
 * record, its list (0x48a2d0) and base (0x4b78e0) are destroyed, mode 2 freeing it. */
uint32_t vertrix_port_parser_destroy(PORT_SIGNATURE);

/* Original 0x441450(eax = panel, edx = mode): a screen panel destructor: mode 4 destroys an array
 * (element destructor 0x515100); otherwise the table 0x5150f4 (+0x27c) is set and, under a guard
 * record, its three embedded objects are destroyed (0x4b5dc0), mode 2 freeing it. */
uint32_t vertrix_port_screen_panel_destroy(PORT_SIGNATURE);

/* Original 0x460a40(eax, edx, ebx, ecx; five stack arguments): a label box (0x45fe10) with the
 * handlers 0x443460 and 0x4486f0, laid out (0x471820) and added to the list 0x54671c (0x4b5e70).
 * Returns the box. */
uint32_t vertrix_port_label_box_place(PORT_SIGNATURE);

#endif
