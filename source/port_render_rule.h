#ifndef VERTRIX_PORT_RENDER_RULE_H
#define VERTRIX_PORT_RENDER_RULE_H
#include "port.h"

/* Clean ports of the routines that choose how an actor is drawn (port.h). The drawing state is in
 * globals the actor gate (0x4ae3e0) fills: the blend kind byte 0x5bc00d, the opacity byte 0x5bc00e
 * (0x32 for half), the flags 0x5bb739 (blend on), 0x5bb73a (mirror), 0x5bc00c (outline kind) and
 * the clip word 0x5bc002, and the bytes 0x5bc000 and 0x5bb730 (the image and target formats). */

/* Original 0x4af370 (edx = 1 for a plain copy): the drawing flags. 0x80000 when mirrored; then
 * 0x100000 for a plain copy, 1 when blending is off, and otherwise 8 (half opacity) or 0x10 plus
 * the blend kind's bit: 0x100 for none, 0x200 << (kind - 1) for kinds 1 to 3, and 0x1000 << (kind
 * - 4) for kinds 4 to 10, which count as half opacity (8). The copy, unblended and kinds 4 to 10
 * cases mark the pixel as plain. Differing formats add 4, and a plain pixel then 0x20, 0x40 or
 * 0x80 for outline kind 0, 1 or 2; a clip adds 2. The blend kind and opacity bytes are stored back.
 * Returns the flags, with edx 1 for a plain pixel (the outline kind when it was read) and 0
 * otherwise. */
uint32_t vertrix_port_render_flags(PORT_SIGNATURE);

/* Original 0x4af2a0 (edx = drawing flags): the first of the 0x5c rules at 0x4fed44 (dword pairs:
 * the flags required, then flags allowed besides them) that the flags satisfy, or 0x5c. edx is the
 * last rule's required flags. */
uint32_t vertrix_port_render_rule(PORT_SIGNATURE);

/* Original 0x4af530: the traversal flags: 1, or 2 when the byte 0x5bbfff is not 1; plus 4 when the
 * byte 0x5bb738 is not 0x10 and 8 when the byte 0x5bbff0 is 1. edx is unchanged. */
uint32_t vertrix_port_render_traversal_flags(PORT_SIGNATURE);

/* Original 0x4af340 (edx = mirror flags): 0, 1, 2 or 3 for 0, 8, 4 or 0xc, and 4 otherwise. edx
 * is unchanged. */
uint32_t vertrix_port_render_mirror_index(PORT_SIGNATURE);

/* Original 0x4af2e0 (edx = direction flags): 0 to 7 for 2, 1, 6, 5, 0xa, 9, 0xe and 0xd, and 8
 * otherwise. edx is unchanged. */
uint32_t vertrix_port_render_direction_index(PORT_SIGNATURE);

#endif
